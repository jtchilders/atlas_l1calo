
#include <iostream>
#include <string>
#include <cmath>

#include "TApplication.h"
#include "TCanvas.h"
#include "TProfile.h"
#include "TH1I.h"
#include "TFile.h"
#include "TStyle.h"

#include "cbntClass.h"

#include <tclap/CmdLine.h>

int main(int argc, char** argv){
	
	/// Setup the gStyle environment
	#include "gStyleSetup.h"
	
	std::string inputFilename;
	bool isFileList = false;
	bool largOnly = false;
	bool tileOnly = false;
	bool emOnly = false;
	bool hadOnly = false;
	unsigned int runNumber = 0;
	
	TCLAP::CmdLine* cmd;
	try{
		cmd = new TCLAP::CmdLine("This program will take a root cbnt containing a PHOS4 scan and output a root file containing all the profile histograms of the signals from each trigger tower.",' ',"0.1");
		
		// Defining the arguments that are allowed
		
		// Require input filename
		TCLAP::ValueArg<std::string> inputFilenameArg("n","inputFilename","Input CBNT filename from PHOS4 scan",true,"data.root","string");
		cmd->add(inputFilenameArg);
		
		TCLAP::ValueArg<int> runNumberArg("r","runNumber","Run number for the CBNT file.",true,1,"integer");
		cmd->add(runNumberArg);
		
		// is this file a list of files?
		TCLAP::SwitchArg isFileListArg("f","fileList","Input filename is not a data file, but a list of data files.",false);
		
		cmd->add(isFileListArg);
		
		// should I only do Larg or Tile?
		TCLAP::SwitchArg largOnlyArg("l","largOnly","Only run on LArg channels",false);
		TCLAP::SwitchArg tileOnlyArg("t","tileOnly","Only run on Tile channels",false);
		cmd->xorAdd(largOnlyArg,tileOnlyArg);
		
		cmd->parse(argc,argv);
		
		inputFilename = inputFilenameArg.getValue();
		
		isFileList = isFileListArg.getValue();
		
		largOnly = largOnlyArg.getValue();
		tileOnly = tileOnlyArg.getValue();
		// if tileOnly is set the hadOnly is set to true
		if(tileOnly){
			hadOnly = true;
		}
		
		runNumber = runNumberArg.getValue();
		
	}
	catch (TCLAP::ArgException &e){
		std::cerr << "command line parse error: " << e.error() << " for arg " << e.argId() << std::endl;
		std::cerr << "help: " << (unsigned int)cmd->hasHelpAndVersion() << std::endl;
		return 0;
	}
	
// 	TApplication app("app",&argc,argv);
	
	
	/// get the ROOT TTree
	cbntClass *t;
	
	if(!isFileList){
		std::cerr << "Creating cbntClass with " << inputFilename.c_str() << std::endl;
		t = new cbntClass(inputFilename);
	}
	else if(isFileList){
		t = new cbntClass(inputFilename,isFileList);
		
	}
	
	const int totalEvts = t->fChain->GetEntries();
	
	std::cerr << "Total Events: " << totalEvts << std::endl;
	
	// For each coolId I want a profile of the signal shape
	std::map<unsigned int,TProfile*>* mProf = new std::map<uint,TProfile*>;
	
	unsigned int globalNumTimeSlices = 0;
	unsigned int globalNumPhos4Steps = 0;
	const unsigned int numNanosecPerTimeSlice = 25;
	const unsigned int numSteps = 27;
	
	const unsigned int selectedChannel = 0x06100000;
	std::map<unsigned int,TH1I*>* mTh1 = new std::map<unsigned int,TH1I*>;
	
// 	TCanvas can("can","Canvas",0,0,800,600);
// 	TH1I* histo;
// 	
	
	for(int i=0;i<totalEvts;i++){
		
		//if( i%10 ) continue;
		
		t->GetEntry(i);
		
		if( !(i % (int(totalEvts*0.01) + 1)))
			std::cerr << "\r Percent Done: " << int(((float)i/(float)totalEvts)*100) << "\t";
		
		// Read in the number of time slices read out during this run. Only need to do this once
		// These are used at the end.
		if( i == 0){
			globalNumTimeSlices = t->L1CaloPPM_hadADC->at(0).size();
			globalNumPhos4Steps = t->L1CaloPPM_hadADC->at(0).size()*numNanosecPerTimeSlice;
		}
		
		// Loop of trigger towers
		for(int tt=0;tt<t->L1CaloPPM_ntt;tt++){
			
			/// Process Exclusions
			
			// if only Tile channels are wanted
			if(tileOnly){
				if( fabs(t->L1CaloPPM_eta->at(tt)) > 1.5) continue;
				
			}
			
			// get the current time step being read out 0 to 24 ns
			uint timeStep = t->L1CaloRODHeader_stepNumber->at(0) % 25;
// 			std::cerr << "timeStep: " << timeStep << std::endl;
			
			// Fill the Hadronic channels if they are filled
			if(t->L1CaloPPM_hadIsFilled->at(tt) && !emOnly){
				
				// if only larg channels are wanted
				if(largOnly){
					if( t->L1CaloPPM_eta->at(tt) < 1.5) continue;
				}
				
				const unsigned int numTimeSlices = t->L1CaloPPM_hadADC->at(tt).size();
				const unsigned int numPhos4Steps = numTimeSlices*numNanosecPerTimeSlice;
				
				
				unsigned int chanID = t->L1CaloPPM_hadChannelId->at(tt);
				
// 				if(chanID == selectedChannel){
// 					char title[100];
// 					sprintf(title,"Evt: %05d Step #%02d",i,t->L1CaloRODHeader_stepNumber->at(0));
// 					histo = new TH1I("histo",title,numTimeSlices,0,numTimeSlices);
// 					
// 				}
				
				// get iterator to the appropriate profile plot
				// if one doesn't exist create it
				std::map<uint,TProfile*>::iterator itr = mProf->find(chanID);
				if(itr == mProf->end()){
					char name[100];
					sprintf(name,"prof_%08x",chanID);
					char title[100];
					sprintf(title,"Profile of PHOS4 Steps in %08x",chanID);
					(*mProf)[chanID] = new TProfile(name,title,numPhos4Steps,0,numPhos4Steps,0,1024);
					itr =  mProf->find(chanID);
				}
				
				// Loop over the FADC slices
				for(unsigned int slice=0;slice<t->L1CaloPPM_hadADC->at(tt).size();slice++){
					unsigned int ADC = t->L1CaloPPM_hadADC->at(tt)[slice];
					
					unsigned int binNumber = slice*numNanosecPerTimeSlice+timeStep;
					if(selectedChannel == chanID && binNumber == 155){
						std::cerr << "binNumber: " << binNumber <<  " ADC: " << ADC << std::endl;
						
					}
					
					// fill the profile associated with this cool ID
					itr->second->Fill(binNumber+0.001,ADC);
					
					// fill the 1D histogram of each bin in the selected channels profile
					if(selectedChannel == chanID){
						// get iterator to the appropriate profile plot
						// if one doesn't exist create it
						std::map<uint,TH1I*>::iterator itrTh1 = mTh1->find(binNumber);
						if(itrTh1 == mTh1->end()){
							char nameTh1[100];
							sprintf(nameTh1,"crossSection_%03d",binNumber);
							char titleTh1[100];
							sprintf(titleTh1,"Cross Section of Profile for 0x%08x for step %03d",chanID,binNumber);
							(*mTh1)[binNumber] = new TH1I(nameTh1,titleTh1,1024,0,1024);
							itrTh1 =  mTh1->find(binNumber);
						}
						
						itrTh1->second->Fill(ADC);
						
// 						histo->Fill(slice+0.001,ADC);
						
					}
					
				}
				
// 				if(selectedChannel == chanID && timeStep == 17){
// 					
// 					histo->Draw();
// 					can.Update();
// 					
// // 					if(timeStep == 17)
// 					cin.get();
// 					
// 				}
// 				
// 				if(chanID == selectedChannel){
// 					delete histo;
// 					
// 				}
			}
			
			// Fill the Electromagnetic channels if they are filled
			if(t->L1CaloPPM_emIsFilled->at(tt) && !hadOnly){
				const unsigned int numTimeSlices = t->L1CaloPPM_emADC->at(tt).size();
				const unsigned int numPhos4Steps = numTimeSlices*numNanosecPerTimeSlice;
				
				unsigned int chanID = t->L1CaloPPM_emChannelId->at(tt);
				
				// get iterator to the appropriate profile plot
				// if one doesn't exist create it
				std::map<unsigned int,TProfile*>::iterator itr = mProf->find(chanID);
				if(itr == mProf->end()){
					char name[100];
					sprintf(name,"prof_%08x",t->L1CaloPPM_emChannelId->at(tt));
					char title[100];
					sprintf(title,"Profile of PHOS4 Steps in %08x",t->L1CaloPPM_emChannelId->at(tt));
					(*mProf)[chanID] = new TProfile(name,title,numPhos4Steps,0,numPhos4Steps,0,1024);
					itr =  mProf->find(chanID);
				}
				
				for(unsigned int slice=0;slice<t->L1CaloPPM_emADC->at(tt).size();slice++){
					unsigned int ADC = t->L1CaloPPM_emADC->at(tt)[slice];
					
					unsigned int binNumber = slice*25+timeStep;
					
					// fill the profile histogram for associated cool ID
					itr->second->Fill(binNumber,ADC);
					
				}
			}
			
			
		}
		
	}// end for(entries)
	
	// now I want to loop over the histograms and output the profiles to a root file
	
	// need an output file for the profiles
	char outputFile[100];
	sprintf(outputFile,"signalProfiles.r%08d.root",runNumber);
	TFile* profOutFile =  new TFile(outputFile,"RECREATE");
	
	// Want some summary plots
// 	std::string adcPeakDistName = "adcPeakDist";
// 	TH1I* adcPeakDist = new TH1I(adcPeakDistName.c_str(),"Distribution of ADC Peak Values;Peak ADC",1024,0,1024);
// 	
	std::map<unsigned int,TProfile*>::iterator itrBegin = mProf->begin();
	std::map<unsigned int,TProfile*>::iterator itrEnd = mProf->end();
	std::map<unsigned int,TProfile*>::iterator itr = itrBegin;
	
	for(itr = itrBegin;itr != itrEnd;itr++){
		itr->second->Write(itr->second->GetName(),TObject::kOverwrite);
		
// 		unsigned int peakValue = 0;
// 		// need to locate the peak adc value
// 		for(unsigned int bin=1;bin<itr->second->GetNbinsX();bin++){
// 			
// 			if(peakValue < itr->second->GetBinContent(bin)){
// 				peakValue = (unsigned int)itr->second->GetBinContent(bin);
// 			}
// 			
// 		}
// 		
// 		adcPeakDist->Fill(peakValue);
		
	}
	
// 	adcPeakDist->Write(adcPeakDist->GetName(),TObject::kOverwrite);
	
	
	profOutFile->Close();
	profOutFile->Delete();
	
	
	char th1OutputFile[100];
	sprintf(th1OutputFile,"th1OfProfile.r%08d.root",runNumber);
	TFile* th1OfProfile = new TFile(th1OutputFile,"RECREATE");
	std::map<unsigned int,TH1I*>::iterator itrTh1Begin = mTh1->begin();
	std::map<unsigned int,TH1I*>::iterator itrTh1End = mTh1->end();
	std::map<unsigned int,TH1I*>::iterator itrTh1 = itrTh1Begin;
	
	for(itrTh1 = itrTh1Begin;itrTh1 != itrTh1End;itrTh1++){
		itrTh1->second->Write(itrTh1->second->GetName(),TObject::kOverwrite);
	}
	th1OfProfile->Close();
	th1OfProfile->Delete();
	
// 	adcPeakDist->Delete();
	
// 	delete t;
	
// 	for(itr = itrBegin;itr != itrEnd;itr++){
// 		
// 		itr->second->Delete();
// 	}
// 	
// 	
// 	delete mProf;
// 	
	
	
	
	return 0;
}

