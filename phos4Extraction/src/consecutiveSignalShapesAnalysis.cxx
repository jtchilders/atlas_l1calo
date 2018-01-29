
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
	
	std::vector<std::string> inputFilenames;
	
	TCLAP::CmdLine* cmd;
	try{
		cmd = new TCLAP::CmdLine("This program will take many root file containing profile histograms of phos4 pulse shapes and perform an analysis of the signals.",' ',"0.1");
		
		// Defining the arguments that are allowed
		
		// Require input filename
		TCLAP::MultiArg<std::string> inputFilenameArg("n","inputFilename","Input ROOT filename with pulse shape profile plots",true,"string");
		cmd->add(inputFilenameArg);
		
		cmd->parse(argc,argv);
		
		inputFilenames = inputFilenameArg.getValue();
		
	}
	catch (TCLAP::ArgException &e){
		std::cerr << "command line parse error: " << e.error() << " for arg " << e.argId() << std::endl;
		return 0;
	}
	
	TApplication app("app",&argc,argv);
	
	// Open each file as a root file
	std::vector<TFile*> inputFiles;
	for(unsigned int i=0;i<inputFilenames.size();i++){
		TFile* inputFile = new TFile(inputFilenames[i].c_str(),"READ");
		inputFiles.push_back(inputFile);
	}
	
	// Get the key lists from the files
	std::vector<TList*> keyLists;
	for(unsigned int i=0;i<inputFilenames.size();i++){
		TList* keyList = inputFiles[i]->GetListOfKeys();
		if(keyList->GetEntries() == 0){
			std::cerr << inputFilenames[i] << " has no histograms in it.\n";
			return 0;
		}
		
		keyLists.push_back(keyList);
	}
	
	
	unsigned int selectedChannel = 0x06120101;
	TCanvas can("can","can",0,0,1200,600);
	can.Divide(2);
	
	/////////////////////////
	/// For the moment I am assuming that the key from each file
	/// is the same such that Key == 0 refers to the same cool ID
	/// in all files
	///////////////////////////
	
	// Loop over the Profiles in this file
	for(int key=0;key<keyLists[0]->GetEntries();key++){
		
		if( !(key % (int(keyLists[0]->GetEntries()*0.01) + 1)))
			std::cerr << "\r Percent Done: " << int(((float)key/(float)keyLists[0]->GetEntries())*100) << "\t";
		
		
		// grab the actual histogram pointer.
		std::vector<TProfile*> profs;
		for(unsigned int i=0;i<inputFilenames.size();i++){
			TKey* histoKey = (TKey*)keyLists[i]->At(key);
			
			TProfile* prof = (TProfile*)histoKey->ReadObj();
			profs.push_back(prof);
		}
		
		// need to extract the cool ID
		std::string histoName = profs[0]->GetName();
		unsigned int coolIdLocation = histoName.find('_')+1;
		std::string strCoolId = histoName.substr(coolIdLocation,8);
		unsigned int coolID = 0;
		sscanf(strCoolId.c_str(),"%x",&coolID);
		
		TProfile tmpProf("tmpProf","Change in y values for each bin;time step(ns)",
				profs[0]->GetNbinsX()-1,0,profs[0]->GetNbinsX()-1);
		for(unsigned int bin=1;bin<profs[0]->GetNbinsX();bin++){
			
			for(unsigned int i=1;i<inputFilenames.size();i++){
				if(profs[i]->GetBinContent(bin) != 0x3ff){
					double dy = profs[i]->GetBinContent(bin) - profs[i-1]->GetBinContent(bin);
					
					if(i==1)
						dy = dy/13.0;
					if(i==2)
						dy = dy/12.0;
					if(i==3)
						dy = dy/13.0;
					if(i==4)
						dy = dy/12.0;
					if(i==5)
						dy = dy/25.0;
					if(i==6)
						dy = dy/25.0;
					if(i==7)
						dy = dy/50.0;
					
					tmpProf.Fill(bin-1,dy);
					
					if(bin == 152)
						std::cerr << dy << " " << profs[i]->GetBinContent(bin) << " " << profs[i-1]->GetBinContent(bin) << "\n";
				}
			}
		}
		can.cd(1);
		profs[6]->SetMarkerColor(kRed);
		profs[5]->SetMarkerColor(kOrange);
		profs[4]->SetMarkerColor(kYellow);
		profs[3]->SetMarkerColor(kGreen);
		profs[2]->SetMarkerColor(kCyan);
		profs[1]->SetMarkerColor(kBlue);
		profs[0]->SetMarkerColor(kViolet);
		
		profs[7]->Draw();
		profs[6]->Draw("same");
		profs[5]->Draw("same");
		profs[4]->Draw("same");
		profs[3]->Draw("same");
		profs[2]->Draw("same");
		profs[1]->Draw("same");
		profs[0]->Draw("same");
		
		can.cd(2);
		
		tmpProf.DrawCopy();
		
		can.Update();
		
		std::cin.get();
		
	}
	
// 	char outputFilename[100];
// 	sprintf(outputFilename,"riseTimeDist.r%08d.root",runNumber);
// 	TFile* outputFile = new TFile(outputFilename,"RECREATE");
// 	
// 	riseTimeDist->Write();
// 	peakValueDist->Write();
// 	
// 	outputFile->Close();
// 	outputFile->Delete();
	
	
	
	app.Run();
	
}



