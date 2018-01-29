
#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>

#include "TApplication.h"
#include "TCanvas.h"
#include "TProfile.h"
#include "TH1I.h"
#include "TH2I.h"
#include "TFile.h"
#include "TStyle.h"
#include "TList.h"
#include "TKey.h"
#include "TF1.h"
#include "TGraph.h"

#include "PpmFadcSim.h"
#include "PpmSatBcidLogic.h"

#include <tclap/CmdLine.h>

int main(int argc, char** argv){
	
	/// Setup the gStyle environment
	#include "gStyleSetup.h"
	
	bool randAmp = false;
	
	TCLAP::CmdLine* cmd;
	try{
		cmd = new TCLAP::CmdLine("Simulated Landau Gaussian pulse shapes are used to perform a simple Monte Carlo study.",' ',"0.1");
		
		// Defining the arguments that are allowed
		
		
		TCLAP::SwitchArg randomAmplitudeArg("a","randAmpl","Use random amplitude",false);
		
		cmd->add(randomAmplitudeArg);
		
		cmd->parse(argc,argv);
		
		randAmp = randomAmplitudeArg.getValue();
	}
	catch (TCLAP::ArgException &e){
		std::cerr << "command line parse error: " << e.error() << " for arg " << e.argId() << std::endl;
		return 0;
	}
	
	TApplication app("app",&argc,argv);
	
	TCanvas can("can","can",0,0,1200,600);
// 	can.Divide(2);
	
	const unsigned int numTimeSlice = 5;
	
	// Setup fadc simulator for my run
	const unsigned int ampMax = 2000,ampMin=900,ampIncrement = 1;
	PpmFadcSim* fadcSim = new PpmFadcSim(numTimeSlice);
	
// 	TGraph* ampVsTS1 = new TGraph("ampVsTS1","Amplitude vs S_{-1};Amplitude;S_{-1}",ampMax-ampMin,ampMin,ampMax,1124,-100,1024);
	
   const unsigned int numEntries = (unsigned int)((ampMax - ampMin)/ampIncrement);
   int* ampX = new int[numEntries];
   int* t1Y  = new int[numEntries];
   unsigned int currentEntry = 0;
   
	for(unsigned int amp=ampMin;amp<ampMax;amp+=ampIncrement){
		std::cerr << "amp: " << amp << std::endl;
		
		fadcSim->SetAmplitude(amp);
		
		for(unsigned int ts=0; ts < fadcSim->GetPipelineLength()-fadcSim->GetNumberOfTimeSlices(); ts++){
			
			std::vector<unsigned int>* fadcs = fadcSim->GetFadcReadout();
			
			TH1I histo("histo","histo",fadcSim->GetPipelineLength(),0,fadcSim->GetPipelineLength()*25.0);
			for(unsigned int i=0;i<fadcs->size();i++)
				histo.Fill((i+fadcSim->GetCurrentSlice())*25.0,fadcs->at(i));
			
			unsigned int peakTS = fadcSim->GetPeakLocation();
			if(peakTS == 999) continue;
			
			TF1* fit = new TF1("fit",fadcSim->GetFitFunction(),0,fadcSim->GetPipelineLength()*25.0,5);
			fit->SetParameter(0,fadcSim->GetMean());
			fit->SetParameter(1,fadcSim->GetAmplitude()/exp(-0.5));
			fit->SetParameter(2,fadcSim->GetGaussianSigma());
			fit->SetParameter(3,fadcSim->GetLandauSigma());
			fit->SetParameter(4,fadcSim->GetPedestal());
			
			if((peakTS == 2 && fadcs->at(2) < 0x3ff) ||
				(fadcs->at(1) < 0x3ff && fadcs->at(2) == 0x3ff)){
// 				ampVsTS1->Fill(amp,fadcs->at(1));
            ampX[currentEntry] = amp;
            t1Y[currentEntry]  = fadcs->at(1);
            currentEntry++;
			}
// 			fit->Draw();
// 			histo.Draw("same");
// 			can.Update();
			
// 			satBcid->SetFadcSlices(fadcs);
// 			
// 			unsigned int satBC = 999;
// 			if(m_satBcidBlock->IsCenterSlicePeak() && !foundPeak){
// 				satBC = m_numOfTimeSlices/2;
// 				foundPeak = true;
// 			}
// 			else if(m_satBcidBlock->IsCenterSlicePlusOnePeak() && !foundPeak){
// 				satBC = m_numOfTimeSlices/2 + 1;
// 				foundPeak = true;
// 			}
// 			
// 			if(satBC != 999 && m_fadcSource->GetPeakLocation() != 999){
// 				
// 				
// 				
// 			}
			
			//std::cin.get();
			
		}
      
      std::cerr << currentEntry << " " << (amp-ampMin) << std::endl;
	}
	
   TFile outputFile("ampVsTS1.root","RECREATE");
	
   TGraph ampVsTS1(currentEntry,ampX,t1Y);
   ampVsTS1.SetName("ampVsTS1");
   ampVsTS1.SetTitle("Simulated Amplitude Vs. S_{-1};Amplitude;S_{-1}");
   
	ampVsTS1.Draw("A*");
   
   ampVsTS1.Write();
   
   outputFile.Close();
	
	app.Run();
	
	// Sets the range for my Register Threshold values RegSatHigh/Low
	// and how finely to increment over these ranges
// 	uint maxThreshold = 1024;//0x3ff;
// 	uint minThreshold = 0;
// 	uint increment = 8;//0xf;
// 	
// 	for(uint low=minThreshold;low<maxThreshold;low+=increment)
// 	{
// 		satBcid->SetSatLowThreshold(low);
// 		
// 		
// 		
// 		for(uint high=low;high<maxThreshold;high+=increment)
// 		{
// 			m_satBcidBlock->SetSatHighThreshold(high);
// 			
// 		}
// 		
// 		
// 		
// 	}
	
	
}



