

#include "saturatedAnalysis.h"


SaturatedAnalysis::SaturatedAnalysis(const uint time_slices): 
	m_numOfTimeSlices(time_slices),
	m_batch(true)
{
	
	m_fadcSource = new PpmFadcSim(m_numOfTimeSlices);
	m_satBcidBlock = new PpmSatBcidLogic(m_numOfTimeSlices);
	
	m_lowestLow = 0;
	m_highestLow = 0;
	m_lowestHigh = 0;
	m_highestHigh = 0;
	
	#include "gStyleSetup.cxx"
	
}

SaturatedAnalysis::~SaturatedAnalysis(){
	
	delete m_fadcSource;
	delete m_satBcidBlock;
	
	
}

void SaturatedAnalysis::FindRegSatLowHigh(int argc,char** argv){
	
	
	
	
	gROOT->SetBatch(m_batch);
	
	// Create an application incase you want to see histograms at the end
	TApplication *app;
	if(!m_batch){
		app = new TApplication("App",&argc,argv);
	}
	
// 	const uint satHigh = 767;
// 	const uint satLow  = 255;
// 	const uint satLevel = 1023;
// 	const uint fir1 = 0;
// 	const uint fir2 = 7;
// 	const uint fir3 = 15;
// 	const uint fir4 = 10;
// 	const uint fir5 = 0;
	
	// Setup fadc simulator for my run
	const uint ampMax = 12000,ampMin=900;
	m_fadcSource->SetRandomSampling(0);
	m_fadcSource->SetRandomAmplitude(0);
	m_fadcSource->SetRandomPedestal(0);
	//fadcSource->SetAmplitude(1150);
	//fadcSource->SetAmplitudeRangeMaximum(ampMax);
	//fadcSource->SetAmplitudeRangeMinimum(ampMin);
	
	// This will hold the 5 ADC slices
	vector<uint>* fadcs;
	
	
// 	LandGaussFunc* fitFunc = m_fadcSource->GetFitFunction();
	
	
// 	TH1I* histoB = new TH1I("histoB","Signal Peak for non-equal BC ID;Peak height",(ampMax-ampMin)/10,ampMin,ampMax);
// 	TH2I* histoA = new TH2I("histoA","Correlation of Saturated BC to true BC;True BC; Saturated BC",m_numOfTimeSlices,0,m_numOfTimeSlices,m_numOfTimeSlices,0,m_numOfTimeSlices);
	
	
	// Sets the range for my Register Threshold values RegSatHigh/Low
	// and how finely to increment over these ranges

	uint maxThreshold = 1024;//0x3ff;
	uint minThreshold = 0;
	uint increment = 8;//0xf;
	
	// Plot for determining the best RegSatLow
	TH1I* numEqualVsLow = new TH1I("numEqualVsLow","histo;low;filled phase space",(maxThreshold-minThreshold)/increment,minThreshold,maxThreshold);
	
	// These are used to find the range for the RegSatLow
	// which begins with the maximum found in the histo=numEqualVsLow
	uint previousMaxAmp=0;
	uint prevuousMinAmp=0;
	
	// Create a ROOT file for my histograms to be saved in
	TFile *rootFile = new TFile("satAnal.root","RECREATE");
	
	// Used to locate the Peak in the numEqualVsLow histogram
	bool pastPeak = false;
	uint numPastPeak = 0;
	vector<uint> peakLowAmp,peakHighAmp;
	
	bool closeRegion=false;
	
	// This canvas is used during my loop for debugging
	TCanvas* canvasB = new TCanvas("canvasB","canvasB",0,0,800,600);
	canvasB->SetBatch(m_batch);
	
// 	LandGaussFunc* fitFunc = new LandGaussFunc;
// 	TF1* lgFunc = new TF1("lgFunc",fitFunc,-125,225,5);
// 	
	for(uint low=minThreshold;low<maxThreshold;low+=increment)
	{
		cerr << low << endl;
		m_satBcidBlock->SetSatLowThreshold(low);
		
		char highVsAmp_name[100];
		sprintf(highVsAmp_name,"low%04i_highVsAmp",low);
		char highVsAmp_title[100];
		sprintf(highVsAmp_title,"RegSatLow = %i: (satBC-trueBC)^{2} for RegSatHigh vs. Pulse Amplitude; RegSatHigh; Amplitude (in ADC)",low);
		TH2I* highVsAmp = new TH2I(highVsAmp_name,highVsAmp_title,
			(maxThreshold-minThreshold)/increment,minThreshold,maxThreshold,
			ampMax-ampMin,ampMin,ampMax);
		highVsAmp->SetContour(64);
		
		// Record information about each RegSatLow Setting
		char lowFilename[100];
		sprintf(lowFilename,"low_%04i.txt",low);
		ofstream lowOut(lowFilename);
		if(!lowOut)
			cerr << "Error opening: " << lowFilename << endl;
		
		// used to find region of goodness for the Low Threshold
		uint previousLowAmp=0;
		uint previousHighAmp=0;
		
// 		char lowtxt[10];
// 		sprintf(lowtxt,"%i",low);
// 		TF1* lowThreshold = new TF1("lowThreshold",lowtxt,-125,250);
// 		
		for(uint high=low;high<maxThreshold;high+=increment)
		{
			//cerr << "   " << high << endl;
			m_satBcidBlock->SetSatHighThreshold(high);
			
			
// 			char hightxt[10];
// 			sprintf(hightxt,"%i",high);
// 			TF1* highThreshold = new TF1("highThreshold",hightxt,-125,250);
// 			
			
			uint counter = 0;
			for(uint amp=ampMin;amp<ampMax;amp+=1){
				
				//cerr << "     " << amp << endl;
				
				m_fadcSource->SetAmplitude(amp);
				
				m_fadcSource->ResetPipeline();
				
				// This ensures I don't accept to Peaks back to back
				bool foundPeak = false;
				
				for(uint ts=0; ts <= m_fadcSource->GetPipelineLength()-m_fadcSource->GetNumberOfTimeSlices(); ts++){
					
					fadcs = m_fadcSource->GetFadcValues();
					
					m_satBcidBlock->SetFadcSlices(fadcs);
					
					uint satBC = 999;
					if(m_satBcidBlock->IsCenterSlicePeak() && !foundPeak){
						satBC = m_numOfTimeSlices/2;
						foundPeak = true;
					}
					else if(m_satBcidBlock->IsCenterSlicePlusOnePeak() && !foundPeak){
						satBC = m_numOfTimeSlices/2 + 1;
						foundPeak = true;
					}
					
					if(satBC != 999 && m_fadcSource->GetPeakLocation() != 999){
						double efficiency = (double)satBC-(double)m_fadcSource->GetPeakLocation();
						efficiency *= efficiency;
						
						highVsAmp->Fill(high,amp,efficiency);
						
						
// 						int min = m_fadcSource->GetLowSignalWindow()*25*(-1);
// 						int max = m_fadcSource->GetHighSignalWindow()*25;
// 						int nbins = m_fadcSource->GetPipelineLength();
// 						TH1D* histo = new TH1D("histo","FADC",nbins,min,max);
// 						for(uint i=0;i<fadcs->size();i++){
// 							uint bin = m_fadcSource->GetCurrentSlice() + i;
// 							histo->SetBinContent(bin,(*fadcs)[i]);
// 							
// 						}
// 						cerr << endl;
// 						
// 						
// 						lgFunc->SetParameter(0,m_fadcSource->GetMean());
// 						lgFunc->SetParameter(1,m_fadcSource->GetAmplitude()/exp(-0.5));
// 						lgFunc->SetParameter(2,m_fadcSource->GetGaussianSigma());
// 						lgFunc->SetParameter(3,m_fadcSource->GetLandauSigma());
// 						lgFunc->SetParameter(4,m_fadcSource->GetPedestal());
// 						
// 						lgFunc->Draw();
// 						histo->Draw("same");
// 						lowThreshold->Draw("same");
// 						highThreshold->Draw("same");
// 						
// 						canvasB->Update();
// 						
// 						//canvasB->SaveAs("canvasB.ps");
// 						
// 						//cin.get();
// 						
// 						
// 						delete histo; histo = 0;
					}
					
				} //for(ts)
				
			} // for(amp)
			
// 			delete highThreshold; highThreshold = 0;
		} // for(high)
		
// 		delete lowThreshold; lowThreshold = 0;
		
// 		highVsAmp->Draw("colz");
// 		canvasB->Update();
// 		cin.get();
		
// 		if(low == minThreshold)
// 			canvasB->SaveAs("highVsAmp.ps(");
// 		else if(low + increment >= maxThreshold)
// 			canvasB->SaveAs("highVsAmp.ps)");
// 		else
// 			canvasB->SaveAs("highVsAmp.ps");
// 		
		highVsAmp->Write();
		
		////////////////////////////////////////////////////////
		// Extract the number of bins with value=zero
		// These are where the peak was correctly identified.
		
		lowOut << "High vs. Amp Output: \n";
		uint numZeros=0;
		vector<uint> firstLowAmp,firstHighAmp;
		for(uint x=1;x<highVsAmp->GetNbinsX();x++){
			
			
			double highThresh = highVsAmp->GetXaxis()->GetBinLowEdge(x);
			
			lowOut << "  For High: " << highThresh << " ";
			
			vector<uint> lowAmp;
			vector<uint> highAmp;
			bool lastWasZero=false;
			for(uint y=1;y<highVsAmp->GetNbinsY();y++){
				double value = highVsAmp->GetBinContent(x,y);
				
				
				// Count the number of zero bins in plots
				if(highThresh >= low && (int)value == 0){
					numZeros++;
					
					if(!lastWasZero){
						lastWasZero = true;
						lowAmp.push_back((uint)highVsAmp->GetYaxis()->GetBinLowEdge(y));
					}
				}
				else{
					if(lastWasZero){
						lastWasZero = false;
						highAmp.push_back((uint)highVsAmp->GetYaxis()->GetBinLowEdge(y-1));
						
					}
				}
			} // for(y)
			
			if(lowAmp.size() > 0){
				lowOut << " Low Amp: " << lowAmp[0] << " High Amp: " << highAmp[0] << " Diff: " << (highAmp[0]-lowAmp[0]) << " ";
				
			}
			
			for(uint i=1;i<lowAmp.size();i++){
				lowOut << "&& Low Amp: " << lowAmp[i] << " High Amp: " << highAmp[i] << " Diff: " << (highAmp[i]-lowAmp[i]) << " ";
				
			}
			
			lowOut << endl;
			
			// save the first low/high amplitude ranges for later.
			if((int)highThresh == low){
				firstLowAmp = lowAmp;
				firstHighAmp = highAmp;
			}
			
		} // for(x)
		
		
		//////////////////////////////////////////////////////////////////////////
		// Fill histogram with the number of bins that are zero.
		numEqualVsLow->SetBinContent(numEqualVsLow->FindBin(low),numZeros);
		
		// Here I am trying to identify the peak of this histogram
		uint previousNumZeros = 0;
		if(low > minThreshold)
			previousNumZeros = (uint)numEqualVsLow->GetBinContent(numEqualVsLow->FindBin(low-increment));
		
		//cerr << ((int)previousNumZeros-(int)numZeros) << " " << (low-increment) << " " << m_fadcSource->GetPedestal() << endl;
		if(previousNumZeros > numZeros && !pastPeak 
			&& (low-increment) > m_fadcSource->GetPedestal() + 10 )
		{
			pastPeak = true;
			numPastPeak = increment;
			cerr << "Past Peak.\n";
			m_lowestLow = low - increment;
			
			// keep track of the limits on low/high amplitudes for the peak
			peakLowAmp = firstLowAmp;
			peakHighAmp = firstHighAmp;
		}
		
		// If we are past the peak I want to start comparing the previous and current
		// Good Amplitude ranges
		
		if(pastPeak && numPastPeak >= 0 && !closeRegion){
			bool failed = false;
			for(uint i=0;i<firstLowAmp.size() && i<peakLowAmp.size();i++){
				if(firstLowAmp[i] != peakLowAmp[i])
					failed = true;
			}
			
			for(uint i=0;i<firstHighAmp.size() && i<peakHighAmp.size();i++){
				if(firstHighAmp[i] != peakHighAmp[i])
					failed = true;
			}
			
			if(!failed)
				numPastPeak += increment;
			else{
				// if numPastPeak is not zero then this is the first
				// time a failure occured after the peak was found
				// so we have exited the region of good RegSatLow
				// values
				if(numPastPeak > 0){
					m_highestLow = m_lowestLow + numPastPeak - increment;
					numPastPeak = 0;
					closeRegion = true;
				}
			}
			
		}
		
		///////////////////////////////////////////////////////////////////////////
		
		
		delete highVsAmp; highVsAmp=0;
		
		
		lowOut << endl;
		lowOut << "Total Number of Zero Bins: " << numZeros << endl << endl;
		lowOut.close();
	} // for(low) 
	
	canvasB->cd();
	canvasB->SetBatch(m_batch);
	numEqualVsLow->Draw();
	canvasB->Update();
	
	numEqualVsLow->Write();
	rootFile->Close();
	delete rootFile;
	rootFile = 0;
	
	// Now I would like to find the range for RegSatHigh
	
	rootFile = new TFile("satAnal.root");
	
	vector<uint> goodHighRange;
	for(uint low=m_lowestLow;low<m_highestLow;low+=increment){
		char histoname[100];
		sprintf(histoname,"low%04i_highVsAmp",low);
		TH2I* histo = (TH2I*)rootFile->Get(histoname);
		
		uint firstSliceNumZeroBins=0;
		uint lengthOfGoodRegion=0;
		for(uint x=1;x<histo->GetNbinsX();x++){
			
			double highThreshold = histo->GetXaxis()->GetBinLowEdge(x);
			
			uint numZeroBins=0;
			for(uint y=1;y<histo->GetNbinsY();y++){
				
				double binContents = histo->GetBinContent(x,y);
				
				if(highThreshold >= low && (int)binContents == 0){
					numZeroBins++;
					
				}
				
			} //for(y)
			
			if(firstSliceNumZeroBins == 0)
				firstSliceNumZeroBins = numZeroBins;
			else if(firstSliceNumZeroBins == numZeroBins){
				lengthOfGoodRegion += increment;
			}
			
			
		} // for(x)
		
		if(lengthOfGoodRegion > 0)
			goodHighRange.push_back(lengthOfGoodRegion);
		
	} // for(low) 2
	
	
	cerr << "Lowest Good RegSatLow: " << m_lowestLow << endl;
	cerr << "Highest Good RegSatLow: " << m_highestLow << endl;
	for(uint i=0;i<goodHighRange.size();i++)
		cerr << "Length Of Good Region For High Threshold for Low = " 
			<< (m_lowestLow+i*increment) << ": " << goodHighRange[i] << endl;
	
	canvasB->SaveAs("numBinsVsSatLowThreshold.ps");
	//exit(0);
	
	ofstream peakOut("peakOutput.txt");
	peakOut << "Lowest Good RegSatLow: " << m_lowestLow << endl;
	peakOut << "Highest Good RegSatLow: " << m_highestLow << endl;
	for(uint i=0;i<goodHighRange.size();i++)
		peakOut << "Length Of Good Region For High Threshold for Low = " 
			<< (m_lowestLow+i*increment) << ": " << goodHighRange[i] << endl;
	peakOut.close();
	
	
	
	if(!m_batch)
		app->Run();
}


void SaturatedAnalysis::CalculateBcDetectionEfficiency(int argc,char** argv){
	
	gROOT->SetBatch(m_batch);
	
	// Create an application incase you want to see histograms at the end
	TApplication *app;
	if(!m_batch){
		app = new TApplication("App",&argc,argv);
	}
	
	// Setup fadc simulator for my run
	const uint ampMax = 12000,ampMin=900;
	m_fadcSource->SetRandomSampling(0);
	m_fadcSource->SetRandomAmplitude(0);
	m_fadcSource->SetRandomPhysicsRate(1);
	//fadcSource->SetAmplitude(1150);
	//fadcSource->SetAmplitudeRangeMaximum(ampMax);
	//fadcSource->SetAmplitudeRangeMinimum(ampMin);
	
	
	// Sets the range for my Register Threshold values RegSatHigh/Low
	// and how finely to increment over these ranges
	uint maxThreshold = 1024;//0x3ff;
	uint minThreshold = 0;
	uint increment = 8;//0xf;
	

	uint maxEvts = (uint)5e5;
	
	TH2D* eff_highVsLow = new TH2D("eff_highVsLow",
		"Efficiency for varying SatLow/SatHigh; SatLow; SatHigh",
		(maxThreshold-minThreshold)/increment,minThreshold,maxThreshold,
		(maxThreshold-minThreshold)/increment,minThreshold,maxThreshold);
	eff_highVsLow->SetContour(64);
	
	LandGaussFunc* fitFunc = new LandGaussFunc;
	TF1* fit = new TF1("fit",fitFunc,-25,150,5);
	TCanvas *canvas = new TCanvas("canvas","canvas",0,0,800,600);
	canvas->SetBatch(m_batch);
	
	for(uint low=minThreshold;low<maxThreshold;low+=increment)
	{
		cerr << low << endl;
		m_satBcidBlock->SetSatLowThreshold(low);
		
		for(uint high=low;high<maxThreshold;high+=increment)
		{
			cerr << "   " << high << endl;
			m_satBcidBlock->SetSatHighThreshold(high);
			
			
			
			uint numOfCorrectBcids=0;
			for(uint evt=0;evt<maxEvts;evt++){
				
				m_fadcSource->ResetPipeline();
				
				// This counter ensures we don't accept two events in a row
				bool foundPeak = false;
				
				for(uint ts=0; ts < m_fadcSource->GetPipelineLength()-m_fadcSource->GetNumberOfTimeSlices(); ts++){
					
					// This will hold the 5 ADC slices
					vector<uint>* fadcs = m_fadcSource->GetFadcValues();
					
					// pass them to the saturated BCID logic
					m_satBcidBlock->SetFadcSlices(fadcs);
					
					
					uint satBC = 999;
					if(m_satBcidBlock->IsCenterSlicePeak() && !foundPeak){
						satBC = m_numOfTimeSlices/2;
						foundPeak = true;
					}
					else if(m_satBcidBlock->IsCenterSlicePlusOnePeak() && !foundPeak){
						satBC = m_numOfTimeSlices/2 + 1;
						foundPeak = true;
					}
					
					
					if(satBC != 999 && m_fadcSource->GetPeakLocation() != 999){
						if(satBC == m_fadcSource->GetPeakLocation())
							numOfCorrectBcids++;
					}
					
				} //for(ts)
				
// 				cerr << m_fadcSource->GetMean() << " " <<
// 					m_fadcSource->GetAmplitude() << " " << 
// 					m_fadcSource->GetGaussianSigma() << " " << 
// 					m_fadcSource->GetLandauSigma() << " " << 
// 					m_fadcSource->GetPedestal() << endl;
// 				
// 				fit->SetParameters(m_fadcSource->GetMean(),
// 					m_fadcSource->GetAmplitude()/exp(-0.5),
// 					m_fadcSource->GetGaussianSigma(),
// 					m_fadcSource->GetLandauSigma(),
// 					m_fadcSource->GetPedestal());
// 				fit->Draw();
// 				canvas->Update();
// 				cin.get();
				
				
				
			} // for(evt)
			
			eff_highVsLow->Fill(low,high,((double)numOfCorrectBcids/(double)maxEvts));
			
			//cerr <<  "    Efficiency: " << (double)((double)numOfCorrectBcids/(double)maxEvts) << endl;
			
		} // for(high)
		
		
	} // for(low)
	
	
	TCanvas *canvasA = new TCanvas("canvasA","canvasA",0,0,800,600);
	canvasA->SetBatch(m_batch);
	
	eff_highVsLow->Draw("colz");
	
	canvasA->SaveAs("eff_highVsLow.ps");
	TFile file("eff_highVsLow.root","RECREATE");
	
	eff_highVsLow->Write();
	
	file.Close();
	
	if(!m_batch)
		app->Run();
	
}




void SaturatedAnalysis::TestEfficiencyStability(int argc,char** argv){
	
	gROOT->SetBatch(m_batch);
	
	// Create an application incase you want to see histograms at the end
	TApplication *app;
	if(!m_batch){
		app = new TApplication("App",&argc,argv);
	}
	
	// Setup fadc simulator for my run
	const uint ampMax = 12000,ampMin=900;
	m_fadcSource->SetRandomSampling(0);
	m_fadcSource->SetRandomAmplitude(0);
	m_fadcSource->SetRandomPhysicsRate(1);
	//fadcSource->SetAmplitude(1150);
	//fadcSource->SetAmplitudeRangeMaximum(ampMax);
	//fadcSource->SetAmplitudeRangeMinimum(ampMin);
	
	vector<uint>* fadcs;
	uint satBC =  999;
	const uint centerSlice = m_numOfTimeSlices/2;
	
	TCanvas *canvas = new TCanvas("canvas","canvas",0,0,800,600);
	canvas->SetBatch(m_batch);
	
	uint minEvts = (uint)1e1;
	uint maxEvts = (uint)1e4;
	uint evtIncrement = (uint)1e1;
	
	TH1D* efficiency = new TH1D("efficiency","Efficiency vs number of sample events; number of events;efficiency",(maxEvts-minEvts)/evtIncrement,minEvts,maxEvts);
	
	uint low = 400;
	cerr << low;
	m_satBcidBlock->SetSatLowThreshold(low);
	
	uint high = 500;
	cerr << "   " << high << endl;
	m_satBcidBlock->SetSatHighThreshold(high);
	
	TFile* ampRoot = new TFile("AmplitudeDist.root","RECREATE");
	
	for(uint numEvts=minEvts;numEvts<=maxEvts;numEvts+=evtIncrement){
		uint numOfCorrectBcids=0;
		
		cerr << "numEvts: " << numEvts << endl;
		
		char name[100];
		sprintf(name,"amp_%07i",numEvts);
		TH1D* amplitude = new TH1D(name,"amplitude distribution",500,0,10000);
		
		for(uint evt=0;evt<numEvts;evt++){
			
			m_fadcSource->ResetPipeline();
			
			// This counter ensures we don't accept two events in a row
			bool foundPeak = false;
			
			for(uint ts=0; ts < m_fadcSource->GetPipelineLength()-m_fadcSource->GetNumberOfTimeSlices(); ts++){
				
				// This will hold the 5 ADC slices
				fadcs = m_fadcSource->GetFadcValues();
				
				// pass them to the saturated BCID logic
				m_satBcidBlock->SetFadcSlices(fadcs);
				
				
				satBC = 999;
				if(m_satBcidBlock->IsCenterSlicePeak() && !foundPeak){
					satBC = centerSlice;
					foundPeak = true;
				}
				else if(m_satBcidBlock->IsCenterSlicePlusOnePeak() && !foundPeak){
					satBC = centerSlice + 1;
					foundPeak = true;
				}
				
				
				if(satBC != 999 && m_fadcSource->GetPeakLocation() != 999 
					&& satBC == m_fadcSource->GetPeakLocation()){
					numOfCorrectBcids++;
					
					amplitude->Fill(m_fadcSource->GetAmplitude());
					
				}
				
			} //for(ts)
			
			
			
		} // for(evt)
		
		amplitude->Write();
		delete amplitude; amplitude = 0;
		
		
		efficiency->SetBinContent(efficiency->FindBin(numEvts),(double)numOfCorrectBcids/(double)numEvts);
		
		cerr << "Efficiency: " << (double)((double)numOfCorrectBcids/(double)numEvts) << endl;
	} // for(numEvts)
	
	ampRoot->Close();
	delete ampRoot; ampRoot = 0;
	
	TCanvas *canvasA = new TCanvas("canvasA","canvasA",0,0,800,600);
	canvasA->SetBatch(m_batch);
	
	efficiency->Draw();
	
	TFile file("efficiency.root","RECREATE");
	
	efficiency->Write();
	
	file.Close();
	
	if(!m_batch)
		app->Run();
	
}

void SaturatedAnalysis::fadcPlotter(int argc,char** argv){
	
	
	cerr << "1\n";
	
	TApplication *app;
	if(!m_batch){
		app = new TApplication("App",&argc,argv);
	}
	
	
	CommandLineTool* opts = new CommandLineTool(app->Argc(),app->Argv());
	
	cbntClass *t;
	string filename = opts->GetFilename();
	
	if(!opts->IsFileList()){
		cerr << "Creating with " << filename.c_str() << endl;
		t = new cbntClass(filename);
	}
	else if(opts->IsFileList()){
		t = new cbntClass(filename,opts->IsFileList());
		
	}
	
	PpmSatBcidLogic* satBcid = new PpmSatBcidLogic(5);
	satBcid->SetDefaults();
	
	char satHighStr[10];
	sprintf(satHighStr,"%i",satBcid->GetSatHighThreshold());
	TF1* satHighLine = new TF1("satHighLine",satHighStr,-100,200);
	char satLowStr[10];
	sprintf(satLowStr,"%i",satBcid->GetSatLowThreshold());
	TF1* satLowLine = new TF1("satLowLine",satLowStr,-100,200);
	
	
	const uint numEvts = t->fChain->GetEntries();
	
	TCanvas* canvas = new TCanvas("canvas","canvas",0,0,600,400);
	
	for(uint evt=0;evt<numEvts;evt++){
		
		t->GetEntry(evt);
		
		for(uint tt=0;tt<t->L1CaloPPM_ntt;tt++){
			TH1D* histo = new TH1D("histo","FADCs;BC;FADC",5,0,5);
			
			
			if(t->L1CaloPPM_emIsFilled->at(tt) && 0){
				
				for(uint slice=0;slice<t->L1CaloPPM_emADC->at(tt).size();slice++){
					histo->SetBinContent(slice+1,t->L1CaloPPM_emADC->at(tt)[slice]);
					
				}
				
				histo->Draw();
				satLowLine->Draw("same");
				satHighLine->Draw("same");
				canvas->Update();
				cin.get();
				
			}
			
			delete histo; histo = 0;
			
			histo = new TH1D("histo","FADCs;BC;FADC",5,0,5);
			histo->SetMinimum(0);
			
			
			if(t->L1CaloPPM_hadIsFilled->at(tt) &&
				((t->L1CaloPPM_hadBCID->at(tt) & 0x2))){
				vector<uint> fadcs;
				for(uint slice=0;slice<t->L1CaloPPM_hadADC->at(tt).size();slice++){
					histo->SetBinContent(slice+1,t->L1CaloPPM_hadADC->at(tt)[slice]);
					fadcs.push_back(t->L1CaloPPM_hadADC->at(tt)[slice]);
				}
				
				satBcid->SetFadcSlices(&fadcs);
				
				if(satBcid->IsCenterSlicePeak())
					cerr << "Center Slice is Peak\n";
				else if(satBcid->IsCenterSlicePlusOnePeak())
					cerr << "Center + 1 is Peak\n";
				
				cerr << "    ExtBCID: " << (uint)(t->L1CaloPPM_hadBCID->at(tt) & 0x1) << endl;
				cerr << "    SatBCID: " << (uint)((t->L1CaloPPM_hadBCID->at(tt) & 0x2) >> 1) << endl;
				cerr << "    PeakFinder: " << (uint)((t->L1CaloPPM_hadBCID->at(tt) & 0x4) >> 2) << endl;
				
				histo->Draw();
				satLowLine->Draw("same");
				satHighLine->Draw("same");
				canvas->Update();
				cin.get();
				
				
			}
			
			
			
			delete histo; histo = 0;
			
		} // for(tt)
		
		
	} // for(evt)
	
	
	
	if(!m_batch){
		app->Run();
	}
	
}



