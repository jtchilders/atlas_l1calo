

#include <iostream>

#include "NtupleTreeV1.h"

#include "L1CaloChannelMap.h"

#include "commandLineParser.h"

#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TStyle.h"

using namespace std;

void BasicAnalysis(int argc, char** argv){
	
	
	#include "gStyleSetup.cxx"
	
	//gROOT->SetBatch(kTRUE);
	
	CommandLineTool* opts = new CommandLineTool(argc,argv);
	
	NtupleTreeV1 *t;
	string filename = opts->GetFilename();
	
	if(!opts->IsFileList()){
		t = new NtupleTreeV1(filename);
	}
	else if(opts->IsFileList()){
		t = new NtupleTreeV1(filename,opts->IsFileList());
		
	}
	
	const int totalEvts = t->fChain->GetEntries();
	
	cerr << "Total Events: " << totalEvts << endl;
	
	TH2D *histoA = new TH2D("histoA","BCN Mismatch;Event Number; Crate + 0.25*sLink",1500,0,15000,32,0,8);
	TH2D *histoB = new TH2D("histoB","gLink Error;Event Number; Crate + 0.25*sLink",1500,0,15000,32,0,8);
	TH2D *histoC = new TH2D("histoC","gLink Timeout Error;Event Number; Crate + 0.25*sLink",1500,0,15000,32,0,8);
	TH2D *histoD = new TH2D("histoD","ROD Fifo Overflow;Event Number; Crate + 0.25*sLink",1500,0,15000,32,0,8);
	
	
	for(int i=0;i<totalEvts;i++){
		
		t->GetEntry(i);
		
		if( !(i % (int(totalEvts*0.01) + 1)))
		cerr << "\r Percent Done: " << int(((float)i/(float)totalEvts)*100) << "\t";
		
		//cerr << t->EventNumber << endl;
		
		for(int i=0;i<t->L1CaloRODHeader_nHeaders;i++){
			
			//cerr << "crate: " << t->L1CaloRODHeader_crate->at(i) << "; sLink: " << t->L1CaloRODHeader_sLink->at(i) << "; bcnMismatch: " << t->L1CaloRODHeader_bcnMismatch->at(i) << endl;
			
			if(0 <= t->L1CaloRODHeader_crate->at(i) && t->L1CaloRODHeader_crate->at(i) <= 7){
				if(t->L1CaloRODHeader_bcnMismatch->at(i))
					histoA->Fill(t->EventNumber-113000,
						t->L1CaloRODHeader_crate->at(i) + 0.25*t->L1CaloRODHeader_sLink->at(i));
				
				if(t->L1CaloRODHeader_gLinkError->at(i))
					histoB->Fill(t->EventNumber-113000,
						t->L1CaloRODHeader_crate->at(i) + 0.25*t->L1CaloRODHeader_sLink->at(i));
				
				if(t->L1CaloRODHeader_gLinkTimeout->at(i))
					histoC->Fill(t->EventNumber-113000,
						t->L1CaloRODHeader_crate->at(i) + 0.25*t->L1CaloRODHeader_sLink->at(i));
				
				if(t->L1CaloRODHeader_rodFifoOverflow->at(i))
					histoD->Fill(t->EventNumber-113000,
						t->L1CaloRODHeader_crate->at(i) + 0.25*t->L1CaloRODHeader_sLink->at(i));
				
			}
			
		} // end nHeaders
		
		
	}// end for(entries)
	
	
	TCanvas *canvas = new TCanvas("canvas","canvas",0,0,1000,800);
	//canvas->SetBatch(kTRUE);
	canvas->Divide(2,2);
	//histoA->Draw("colz");
	
	
	canvas->cd(1);
	histoA->Draw("colz");
	
	canvas->cd(2);
	histoB->Draw("colz");
	
	canvas->cd(3);
	histoC->Draw("colz");
	
	canvas->cd(4);
	histoD->Draw("colz");
	
	canvas->SaveAs("canvas.ps");
	
	
	//exit(0);

}

