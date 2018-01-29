#include "PpmFadcSim.h"



PpmFadcSim::PpmFadcSim(unsigned int time_slices): numTimeSlices(time_slices), centerSlice(time_slices/2)
					, lowSignalWindow(3),highSignalWindow(time_slices+1){
	
	Init();
	
};

void PpmFadcSim::Init(void){
	
	fadcPipeline = new vector<unsigned int>;
	
	fadcValues = new vector<unsigned int>;
	
	LandGaussFunc *fitFunc = new LandGaussFunc;
	
	SetDefaultParameters();
	currentSlice = 0;
	peakLocation = 999;
	needReset = true;
	SetRandomAmplitude(false);
	SetRandomSampling(false);
	SetRandomPedestal(false);
	randomSeed = 0;
	useSeed = false;
	
	gaussianAmplitude = 10;
	gaussianSigma = 1.4;
	
	gaussianFit = new TF1("gaussianFit","gaus",30,50);
	gaussianPedestal = new TH1D("gaussianPedestal","gausPedestal",200,30,50);
	
	SetupGaussianHistogram();
	
	minEnergy = 250;
	maxEnergy = 2500;
	powerLawIndex = -4;
	powerLawFunc = new TF1("powerLawFunc","TMath::Power(x,[0])",minEnergy,maxEnergy);
	powerLawSpectrum = new TH1D("powerLawSpectrum","Power Law Rate Spectrum", maxEnergy-minEnergy,minEnergy,maxEnergy);
	
	SetupPowerLawSpectrum();
	
}

void PpmFadcSim::SetupGaussianHistogram(void){
	
	gaussianPedestal->Reset();
	
	gaussianFit->SetParameters(gaussianAmplitude,GetPedestal(),gaussianSigma);
	gaussianPedestal->FillRandom("gaussianFit",(int)1e5);
	
}

void PpmFadcSim::SetupPowerLawSpectrum(void){
	powerLawSpectrum->Reset();
	
	powerLawFunc->SetParameter(0,powerLawIndex);
	powerLawSpectrum->FillRandom("powerLawFunc",(int)1e6);
	
}


void PpmFadcSim::SetDefaultParameters(void){
	SetMean((double)centerSlice*25.);
	SetAmplitude(750.0);
	SetGaussianSigma(23.5);
	SetLandauSigma(15.5);
	SetPedestal(40.);
	
	//cerr << "Here: " << par[0] << " " << par[1] << " " << par[2] << " " << par[3] << " " << par[4] << endl;
	
};

double PpmFadcSim::SimulatePpmFadcSlices(void){
	
	fadcPipeline->clear();
	
	// Set the random timing sampling
	if(!randomSampling){
		currentOffset = 0;
	}
	else{
		if(useSeed)
			srand(randomSeed);
		else
			srand ( time(NULL) );
		
		currentOffset = rand() % 30 - 15;
	}
	double timeStep = currentOffset - (double)lowSignalWindow*25.0;
	
	// Set the random Amplitude
	if(randomAmplitude && !randomPhysicsRate){
		if(useSeed)
			srand(randomSeed);
		else
			srand ( time(NULL) );
		
		unsigned int randomAmp = (unsigned int)(rand() % (ampMax - ampMin)) + ampMin;
// 		cerr << "Setting Amp: " << randomAmp << endl;
		SetAmplitude(randomAmp);
	}
	else if(!randomAmplitude && randomPhysicsRate){
		unsigned int tempAmp = (unsigned int)powerLawSpectrum->GetRandom()*4;
// 		cerr << "tempAmp: " << tempAmp << endl;
		SetAmplitude(tempAmp);
		
	}
	else if(randomAmplitude && randomPhysicsRate){
		cerr << "[PpmFadcSim::SimulatePpmFadcSlices]: Error: Cannot have both Random Amplitude AND Random Physics Rate set\n";
		return -999;
	}
	
	
	// Set the random Pedestal
	if(randomPedestal){
		// divide by 4 to get ADC value
		double pedestal = (double)gaussianPedestal->GetRandom();
		SetPedestal(pedestal);
	}
	
	
	for(unsigned int timeslice=0;timeslice<GetPipelineLength();timeslice++,timeStep+=25.){
		unsigned int adc = (unsigned int)(*fitFunc)(&timeStep,par);
		
		if(adc >= adcSatLvl) adc = adcSatLvl;
		fadcPipeline->push_back(adc);
		//cerr << timeStep << " " << adc << endl;
	}
	
	currentSlice = 0;
	
	return currentOffset;
}


void PpmFadcSim::ResetPipeline(void){
	currentSlice = 0;
	peakLocation = 999;
	SimulatePpmFadcSlices();
}

vector<unsigned int>* PpmFadcSim::GetFadcValues(void){
	
	if( (currentSlice + numTimeSlices) > GetPipelineLength()){
		cerr << "[PpmFadcSim::GetFadcValues] Error: Need to reset pipeline.\n";
		return (vector<unsigned int>*)0;
	}
	
	fadcValues->clear();
	
	bool peakWasSet=false;
	for(unsigned int i=0,j=currentSlice;i<numTimeSlices;i++,j++){
		fadcValues->push_back(fadcPipeline->at(j));
		
		double delta = (int)j - (int)lowSignalWindow;
		//cerr << i << " " << j << " " << delta << " " << (par[0]-currentOffset) << endl;
		if((delta*25.0 < (GetMean()-currentOffset) && (GetMean()-currentOffset) < ((delta+1.0)*25.0) && ( fabs( (delta+1.0)*25.0 - (GetMean()-currentOffset) ) > 0.05)) || fabs(delta*25.0 - (GetMean()-currentOffset)) < 0.005){
			peakLocation = i;
			peakWasSet=true;
		}
	}
	if(!peakWasSet){
		peakLocation = 999;
	}
	
	currentSlice++;
	
	return fadcValues;
}


