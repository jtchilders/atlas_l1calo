
#include <iostream>
#include <fstream>

#include "cbntClass.h"

#include "L1CaloChannelMap.h"
#include "PixelMap.h"
#include "LandGaus.h"

#include "commandLineParser.h"
#include "PpmROBufferList.h"

#include "TH1D.h"
#include "TF1.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TProfile.h"
#include "TApplication.h"

using namespace std;

int main(int argc, char** argv){
	
	
	#include "gStyleSetup.cxx"
	
	
	TApplication *app = new TApplication("App",&argc,argv);
	
	//gROOT->SetBatch(kTRUE);
	
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
	
	
	const int totalEvts = t->fChain->GetEntries();
	
	cerr << "Total Events: " << totalEvts << endl;
	
	const uint numOfTimeSlices = 5;
	PpmROBufferList* rob = new PpmROBufferList(numOfTimeSlices);
	
	TCanvas *canvas = new TCanvas("canvas","canvas",0,0,800,600);
	
	uint chanID=0;
	int lastStep=-1;
	for(int i=0;i<totalEvts;i++){
		
		t->GetEntry(i);
		
		if( !(i % (int(totalEvts*0.01) + 1)))
			cerr << "\r Percent Done: " << int(((float)i/(float)totalEvts)*100) << "\t";
		
		// Loop of trigger towers
		for(int tt=0;tt<t->L1CaloPPM_ntt;tt++){
			
			if(!t->L1CaloPPM_hadIsFilled->at(tt)) continue;
			
			chanID = t->L1CaloPPM_hadChannelId->at(tt);
			
			uint stepNumber = t->L1CaloRODHeader_stepNumber->at(0);
			
			for(int slice=0;slice<t->L1CaloPPM_hadADC->at(tt).size();slice++){
				uint ADC = t->L1CaloPPM_hadADC->at(tt)[slice];
				
				if(stepNumber < (uint)(128/t->L1CaloPPM_hadADC->at(tt).size()) + 1)
					rob->SetValue(chanID,stepNumber,slice,ADC);
				else
					rob->SetValue(chanID,stepNumber-(128/t->L1CaloPPM_hadADC->at(tt).size() + 1),slice,ADC);
				
// 				cerr << "step: " << stepNumber << " slice: " << slice << " ADC: " << ADC;
// 				cerr << "    " <<  t->L1CaloPPM_hadCrate->at(tt) << " " << t->L1CaloPPM_hadModule->at(tt) << " " << t->L1CaloPPM_hadSubmodule->at(tt) << " " << t->L1CaloPPM_hadChannel->at(tt) << endl;
				
				
				
 			}
			
			cin.get();
			
		}
		
	}// end for(entries)
	
	map<uint,uint> robValue;
	uint slotAve=0;
	uint slotCounter=0;
	
	LandGaussFunc* fitFunc = new LandGaussFunc;
	TF1* fit = new TF1("fit",fitFunc,0,128,4);
	
	
	for(int crate=6;crate<8;crate++){
		for(int mod=0;mod<16;mod++){
			for(int submod=0;submod<16;submod++){
				for(int chan=0;chan<4;chan++){
					
					uint maxValue=0;
					uint maxSlot=0;
					
					uint chanID = ((crate & 0xff) << 24) | ((0x1) << 20) | ((mod & 0xf) << 16) | ((submod & 0xff) << 8) | (chan & 0xff);
					
					//cerr << "ChanID: " << chanID << endl;
					//cerr << "Crate: " << crate << " ppm: " << mod << " mcm: " << submod << " chan: " << chan << endl;
					
					if(rob->GetPpmROBuffer(chanID) == (PpmROBuffer*)0) continue;
					
					TProfile *prof = rob->GetPpmROBuffer(chanID)->GetProfile();
					prof->Draw("");
					canvas->Update();
					
					for(uint i=0;i<128;i++)
						cerr << i << " " << rob->GetPpmROBuffer(chanID)->GetValue(i) << endl;
					
					cin.get();
					
				}
				
			}
			
		}
		
	}
	
	app->Run();
	//exit(0);
	
	return 0;
}

