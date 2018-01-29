
#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>

#include "TApplication.h"
#include "TCanvas.h"
#include "TProfile.h"
#include "TH1I.h"
#include "TFile.h"
#include "TStyle.h"
#include "TList.h"
#include "TKey.h"


#include <tclap/CmdLine.h>

int main(int argc, char** argv){
	
	/// Setup the gStyle environment
	#include "gStyleSetup.h"
	
	std::string inputFilename;
	unsigned int runNumber = 0;
	
	TCLAP::CmdLine* cmd;
	try{
		cmd = new TCLAP::CmdLine("This program will take a root file containing profile histograms of phos4 pulse shapes and perform an analysis.",' ',"0.1");
		
		// Defining the arguments that are allowed
		
		// Require input filename
		TCLAP::ValueArg<std::string> inputFilenameArg("n","inputFilename","Input ROOT filename with pulse shape profile plots",true,"data.root","string");
		cmd->add(inputFilenameArg);
		
		TCLAP::ValueArg<unsigned int> runNumberArg("r","runNumber","Run number associated with input file",true,1,"integer");
		cmd->add(runNumberArg);
		
		cmd->parse(argc,argv);
		
		inputFilename = inputFilenameArg.getValue();
		
		runNumber = runNumberArg.getValue();
	}
	catch (TCLAP::ArgException &e){
		std::cerr << "command line parse error: " << e.error() << " for arg " << e.argId() << std::endl;
		return 0;
	}
	
// 	TApplication app("app",&argc,argv);
	
	TFile* inputFile = new TFile(inputFilename.c_str(),"READ");
	
	TList* keyList = inputFile->GetListOfKeys();
	
	if(keyList->GetEntries() == 0){
		std::cerr << inputFile << " has no histograms in it.\n";
		return 0;
	}
	
	unsigned int selectedChannel = 0x06120101;
// 	TCanvas can("can","can",0,0,1200,600);
// 	can.Divide(2);
	
	TH1D* riseTimeDist = new TH1D("riseTimeDist","Rise Time for trigger towers;Rise Time (ns)",100,20,70);
	TH1D* peakValueDist = new TH1D("peakValueDist","Distribution of Signal Peaks",1024,0,1024);
	
	// Loop over the Profiles in this file
	for(int key=0;key<keyList->GetEntries();key++){
		
		if( !(key % (int(keyList->GetEntries()*0.01) + 1)))
			std::cerr << "\r Percent Done: " << int(((float)key/(float)keyList->GetEntries())*100) << "\t";
		
		
		// grab the actual histogram pointer.
		TKey* histoKey = (TKey*)keyList->At(key);
		TProfile* prof = (TProfile*)histoKey->ReadObj();
		
		// need to extract the cool ID
		std::string histoName = prof->GetName();
		unsigned int coolIdLocation = histoName.find('_')+1;
		std::string strCoolId = histoName.substr(coolIdLocation,8);
		unsigned int coolID = 0;
		sscanf(strCoolId.c_str(),"%x",&coolID);
		
		// find the peak location
		unsigned int peakBin = 0;
		double peakValue = 0;
		for(unsigned int bin=1;bin<prof->GetNbinsX();bin++){
			if(peakValue < prof->GetBinContent(bin)){
				peakBin = bin;
				peakValue = prof->GetBinContent(bin);
			}
		}
		
		// find the 10% and 90% of the peak height
		double timeAt10=0;
		unsigned int bin10=0;
		double timeAt90=0;
		unsigned int bin90=0;
		
		const double pedestal = 40; // assume pedestal is 40!!
		const double peakHeight = peakValue - pedestal;
		const double valueAt10 = peakHeight*0.10;
		const double valueAt90 = peakHeight*0.90;
		
// 		TH1D histo("histo","histo",400,0,100);
		double sum=0,sum2=0;
		unsigned int n=0;
		for(unsigned int bin=1;bin<prof->GetNbinsX();bin++){
			double y2 = prof->GetBinContent(bin);
			double y1 = 0;
			if(bin > 1) y1 = prof->GetBinContent(bin-1);
			
			double x2 = (double)bin;
			double x1 = double(bin-1);
			
			double dydx = (y2 - y1)/(x2 - x1);
			double intercept = y2 - dydx*x2;
			
			if(valueAt10 <= y2 && y2 <= valueAt90 && bin < peakBin){
// 				histo.Fill(fabs(dydx));
				
				sum += dydx;
				sum2 += dydx*dydx;
				n++;
			}
			
			if(y2 > valueAt10 && bin10 == 0){
				if( fabs(valueAt10 - y2) < fabs(valueAt10 - y1) ){
					bin10 = bin;
				}
				else
					bin10 = bin - 1;
				
				
				timeAt10 = (valueAt10 - intercept)/dydx;
			}
			
			if(y2 > valueAt90 && bin90 == 0){
				if( fabs(valueAt10 - y2) < fabs(valueAt10 - y1) ){
					bin90 = bin;
				}
				else
					bin90 = bin - 1;
				
				timeAt90 = (valueAt90 - intercept)/dydx;
			}
			
		}
		
		double riseTime = timeAt90 - timeAt10;
		
		double meanSlope = (n==0) ? 0 : sum/(double)n;
		double sigmaSlope = (n==0) ? 0 : sqrt((1.0/(double)n)*sum2-meanSlope*meanSlope);
		
// 		std::cerr << "mean Slope: " << meanSlope << " +/- " << sigmaSlope << std::endl;
		
		// Only include sigmas within a reasonable range
		if(2.0 < sigmaSlope && sigmaSlope < 10.0){
			riseTimeDist->Fill(riseTime);
			peakValueDist->Fill(peakValue);
			
// 			if(riseTime < 35.0){
// 				
// 				std::cerr << "Rise Time: " << riseTime << " meanSlope: " << meanSlope << " +/- " << sigmaSlope << std::endl;
// 				can.cd(1);
// 				prof->Draw();
// 				
// 		// 		can.cd(2);
// 		// 		histo.Draw();
// 				can.Update();
// 				
// 				
// 				std::cin.get();
// 			}
		}
// 		else{
// 			std::cerr << "Rise Time: " << riseTime << " meanSlope: " << meanSlope << " +/- " << sigmaSlope << std::endl;
// 			can.cd(1);
// 			prof->Draw();
// 			
// 	// 		can.cd(2);
// 	// 		histo.Draw();
// 			can.Update();
// 			
// 			
// 			std::cin.get();
// 			
// 		}
		
		
	}
	
	char outputFilename[100];
	sprintf(outputFilename,"riseTimeDist.r%08d.root",runNumber);
	TFile* outputFile = new TFile(outputFilename,"RECREATE");
	
	riseTimeDist->Write();
	peakValueDist->Write();
	
	outputFile->Close();
	outputFile->Delete();
	
	
	
	
	
}



