

#include <iostream>
#include <cmath>

#include "cbntClass.h"
#include "commandLineParser.h"
#include "PixelMap.h"

#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TEventList.h"

using namespace std;

int main(int argc, char** argv){
	
	
	#include "gStyleSetup.cxx"
	
	//gROOT->SetBatch(kTRUE);
	
	CommandLineTool* opts = new CommandLineTool(argc,argv);
	
	cbntClass *t;
	string filename = opts->GetFilename();
	
	if(!opts->IsFileList()){
		t = new cbntClass(filename);
	}
	else if(opts->IsFileList()){
		t = new cbntClass(filename,opts->IsFileList());
		
	}
	
	const int totalEvts = t->fChain->GetEntries();
	
	cerr << "Total Events: " << totalEvts << endl;
	
	TH1I *peakDiff = new TH1I("peakDiff","Difference in Peak location along eta=0;time slice",10,-5,5);
	
	//TEventList *list = new TEventList("list","list");
	
	TCanvas *canvas = new TCanvas("canvas","canvas",0,0,1000,800);
	
	//t->fChain->Draw("L1CaloPPM_hadADC[][2]+L1CaloPPM_hadADC[][3]+L1CaloPPM_hadADC[][4]","");
	
	//canvas->SaveAs("tempHisto.ps");
	//list->Print();
	
	//TFile f("evtList.root","RECREATE");
	
	//list->Write();
	
	//f.Close(); 
	
	int right = 5;
	int left = -5;
	float minMean = 45.0;
	uint onePercent = (uint)(0.01*totalEvts);
	for(int i=0;i<totalEvts;i++){
		t->GetEntry(i);
		
		if(!(i % onePercent)){
			cerr << "\r Percent Done: " << (int)((i*100)/totalEvts) << "\t";
		}
		
		// loop over trigger towers
		for(int tt=0;tt < t->L1CaloPPM_ntt;tt++){
			
			if((int)(t->L1CaloPPM_eta->at(tt)*100) == right){
				
				
				
				float ave = (t->L1CaloPPM_hadADC->at(tt)[0] + t->L1CaloPPM_hadADC->at(tt)[1] + t->L1CaloPPM_hadADC->at(tt)[2] + t->L1CaloPPM_hadADC->at(tt)[3] + t->L1CaloPPM_hadADC->at(tt)[4])/5.0;
				
				if(ave > minMean){
					//cerr << ".";
					//cerr << "\neta/phi: " << t->L1CaloPPM_eta->at(tt) << "/" << t->L1CaloPPM_phi->at(tt) << "; TT FADCs: " << t->L1CaloPPM_hadADC->at(tt)[0] << " " << t->L1CaloPPM_hadADC->at(tt)[1] << " " << t->L1CaloPPM_hadADC->at(tt)[2] << " " << t->L1CaloPPM_hadADC->at(tt)[3] << " " << t->L1CaloPPM_hadADC->at(tt)[4] << endl;
					
					// loop over trigger towers to find neighbors
					for(int tt2=0;tt2 < t->L1CaloPPM_ntt;tt2++){
						float deltaPhi = fabs(t->L1CaloPPM_phi->at(tt2) - t->L1CaloPPM_phi->at(tt));
						//cerr << "deltaPhi: " << deltaPhi << endl;
						if( (int)(t->L1CaloPPM_eta->at(tt2)*100) == left && deltaPhi < 0.4){
							
							float ave2 = (t->L1CaloPPM_hadADC->at(tt2)[0] + t->L1CaloPPM_hadADC->at(tt2)[1] + t->L1CaloPPM_hadADC->at(tt2)[2] + t->L1CaloPPM_hadADC->at(tt2)[3] + t->L1CaloPPM_hadADC->at(tt2)[4])/5.0;
							
							//cerr << "                  ave2: " << ave2 << endl;
							if(ave2 > minMean){
								cerr << "\neta/phi: " << t->L1CaloPPM_eta->at(tt) << "/" << t->L1CaloPPM_phi->at(tt) << "; TT FADCs: " << t->L1CaloPPM_hadADC->at(tt)[0] << " " << t->L1CaloPPM_hadADC->at(tt)[1] << " " << t->L1CaloPPM_hadADC->at(tt)[2] << " " << t->L1CaloPPM_hadADC->at(tt)[3] << " " << t->L1CaloPPM_hadADC->at(tt)[4] << " TT2 eta/phi: " << t->L1CaloPPM_eta->at(tt2) << "/" << t->L1CaloPPM_phi->at(tt2) << "; TT2 FADCs: " << t->L1CaloPPM_hadADC->at(tt2)[0] << " " << t->L1CaloPPM_hadADC->at(tt2)[1] << " " << t->L1CaloPPM_hadADC->at(tt2)[2] << " " << t->L1CaloPPM_hadADC->at(tt2)[3] << " " << t->L1CaloPPM_hadADC->at(tt2)[4] <<endl;
								
								uint peakTS1=9;
								uint peakTS2=9;
								uint peakValue1=0;
								uint peakValue2=0;
								for(int ts=0;ts<5;ts++){
									if(t->L1CaloPPM_hadADC->at(tt)[ts] > peakValue1){
										peakValue1 = t->L1CaloPPM_hadADC->at(tt)[ts];
										peakTS1 = ts;
									}
									if(t->L1CaloPPM_hadADC->at(tt2)[ts] > peakValue2){
										peakValue2 = t->L1CaloPPM_hadADC->at(tt2)[ts];
										peakTS2 = ts;
									}
								
								}
								
								
								peakDiff->Fill(peakTS1 - peakTS2);
								
							}
						}
						
					}
					
				}
			}
			
		} // end for(ntt)
		
	}
	
	peakDiff->Draw();
	
	canvas->SaveAs("tempHisto.ps");
	
	
	
}

