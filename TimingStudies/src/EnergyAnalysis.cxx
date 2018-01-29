
#include <iostream>
#include <fstream>

#include "NtupleTreeV1.h"

#include "L1CaloChannelMap.h"
#include "PixelMap.h"

#include "commandLineParser.h"
#include "PpmROBuffer.h"

#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "TF1.h"

using namespace std;

void EnergyAnalysis(int argc, char** argv){
	
	
	#include "gStyleSetup.cxx"
	
	gROOT->SetBatch(kTRUE);
	
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
	
	map<uint,PpmROBuffer*> mRob;
	map<uint,PpmROBuffer*>::iterator it;
	map<uint,TProfile*> mProfSignal;
	map<uint,TProfile*>::iterator itProf;
	
	uint chanID=0;
	for(int i=0;i<totalEvts;i++){
		
		t->GetEntry(i);
		
		if( !(i % (int(totalEvts*0.01) + 1)))
			cerr << "\r Percent Done: " << int(((float)i/(float)totalEvts)*100) << "\t";
		
		// Loop of trigger towers
		for(int tt=0;tt<t->L1CaloPPM_ntt;tt++){
			
			if(!t->L1CaloPPM_emIsFilled->at(tt)) continue;
			
			chanID = t->L1CaloPPM_emChannelId->at(tt);
			
			itProf = mProfSignal.find(chanID);
			if(itProf == mProfSignal.end()){
				char name[200],title[200];
				sprintf(name,"profSignal_%i",chanID);
				sprintf(title,"Profile of Signal for ChanID: ",chanID);
				mProfSignal[chanID] = new TProfile(name,title,150,0,150);
				itProf = mProfSignal.find(chanID);
				if(itProf == mProfSignal.end())
					cerr << "error\n";
			}
			
			uint stepNumber = t->L1CaloRODHeader_stepNumber->at(0);
				
			for(int slice=0;slice<t->L1CaloPPM_emADC->at(tt).size();slice++){
				uint ADC = t->L1CaloPPM_emADC->at(tt)[slice];
				
				itProf->second->Fill(stepNumber*5+slice,ADC);
				
				//cerr << "step: " << stepNumber << " slice: " << slice << " Old Value: " << oldValue << " New Value: " << it->second->GetValue(stepNumber,slice) << " Counter: " << it->second->GetCounter(stepNumber,slice) << endl;
			}
		}
		
	}// end for(entries)
	
	
	L1CaloChannelMap* l1Map = new L1CaloChannelMap;
	l1Map->SetCpmEnable(false);
	l1Map->SetJemEnable(false);
	
	PixelMap *pmEM = new PixelMap;
	pmEM->ClearPixelMap();
	pmEM->SetPixelSize(TrigTower);
	
	TCanvas *canvasA= new TCanvas("canvasA","canvas A",0,0,800,600);
	canvasA->Divide(8,8);
	canvasA->SetBatch(kTRUE);
	
	TH2D *histoEinEMB = new TH2D("histoEinEMB","Energy for EMB;Energy",50,-4.9,4.9,250,0,2000);
	TH1D *histoEinEMB_1D = new TH1D("histoEinEMB_1D","Energy for EMB;Energy",250,0,1000);
	
	
	for(int crate=0;crate<8;crate++){
		for(int mod=0;mod<16;mod++){
			for(int submod=0;submod<16;submod++){
				for(int chan=0;chan<4;chan++){
					
					l1Map->SetPpmChannel(crate,mod,submod,chan);
					if( l1Map->GetEmHad() == HAD) continue;
					
					char name[200],title[200];
					sprintf(name,"histoSignal_%i",submod*4 + chan);
					sprintf(title,"Signal pp%i-ppm%i-mcm%i-ch%i",crate,mod,submod,chan);
					uint chanID = ((crate & 0xff) << 24) | ((0x1) << 20) | ((mod & 0xf) << 16) | ((submod & 0xff) << 8) | (chan & 0xff);
					
					itProf = mProfSignal.find(chanID);
					if(itProf == mProfSignal.end()){
						//cerr << "chanID not found.\n";
						continue;
					}
					
					itProf->second->SetName(name);
					itProf->second->SetTitle(title);
					const uint maxValue = (uint)itProf->second->GetBinContent(itProf->second->GetMaximumBin());
					//cerr << "MaxValue: " << maxValue << endl;
					
					//if( !(-2.55 < l1Map->GetEta() && l1Map->GetEta() < 2.55)) continue;
					
					if(l1Map->GetEmHad() == EM){
						float theta = 2.0*atan(exp(-(l1Map->GetEta()+l1Map->GetDeltaEta()/2.0)));
						uint Energy = 0;
						uint transEnergy = 0;
						
						if(l1Map->GetDetectorRegion() == LArEMBA || l1Map->GetDetectorRegion() == LArEMBC
							|| l1Map->GetDetectorRegion() == LArEMECA || l1Map->GetDetectorRegion() == LArEMECC
							|| l1Map->GetDetectorRegion() == LArFCAL1A || l1Map->GetDetectorRegion() == LArFCAL1C
							|| l1Map->GetDetectorRegion() == LArOverlapA || l1Map->GetDetectorRegion() == LArOverlapC){
							transEnergy = maxValue;
							Energy = (uint)( ((float)transEnergy)/sin(theta) );
							//cerr << "   A: Et = " << transEnergy << "Eta = " << l1Map->GetEta() << " Theta = " << theta << " sinTheta = " << sin(theta) << " E = " << Energy << endl;
							
						}
						else{
							//cerr << "   Here: " << l1Map->GetDetectorRegionString(l1Map->GetDetectorRegion()) << endl;
							Energy = maxValue;
						}
						//cerr << "      Energy: " << Energy << endl;
						
						if(l1Map->GetDetectorRegion() == LArEMBA || l1Map->GetDetectorRegion() == LArEMBC){
							histoEinEMB->Fill(l1Map->GetEta(),Energy);
							pmEM->SetTriggerTower(l1Map->GetEta(),l1Map->GetPhi(),Energy);
							histoEinEMB_1D->Fill(Energy);
						}
						
					}
					
					canvasA->cd(1+ submod*4 + chan);
					itProf->second->Draw("P");
				}
				
			}
			
			if(crate == 0 && mod == 0)
				canvasA->SaveAs("SignalPlots.ps(");
			else if(crate == 7 && mod == 15)
				canvasA->SaveAs("SignalPlots.ps)");
			else
				canvasA->SaveAs("SignalPlots.ps");
			
		}
		
	}
	
	TCanvas *canvasB = new TCanvas("canvasB","canvas B",0,0,800,600);
	canvasB->SetBatch(kTRUE);
	
	TH2D *histo2Dmap = new TH2D("histo2Dmap","Average ADC Peak per Trigger Tower;#eta;#phi",L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
	
	pmEM->FillEtaPhiHistogram(histo2Dmap);
	
	histo2Dmap->Draw("colz");
	
	canvasB->SaveAs("PeakAve.ps(");
	
	histoEinEMB->Draw("colz");
	
	canvasB->SaveAs("PeakAve.ps");
	
	histoEinEMB_1D->Draw();
	TF1 *fitA = new TF1("fitA", "gaus",600,780);
	fitA->SetParameter(0,60);
	fitA->SetParameter(2,680);
	fitA->SetParameter(3,40);
	TF1 *fitB = new TF1("fitB", "gaus",780,950);
	fitB->SetParameter(0,60);
	fitB->SetParameter(2,840);
	fitB->SetParameter(3,40);
	
	histoEinEMB_1D->Fit(fitA,"R");
	histoEinEMB_1D->Fit(fitB,"R+");
	
	
	TF1 *fit = new TF1("fit","gaus(0)+gaus(3)",500,1000);
	double pars[6];
	fitA->GetParameters(pars);
	fitB->GetParameters(pars+3);
	fit->SetParameters(pars);
	fit->SetLineColor(kBlue);
	
	histoEinEMB_1D->Fit(fit,"R+");
	fit->Draw("same");
	fit->Print();
	
	histoEinEMB_1D->Draw();
	
	canvasB->SaveAs("PeakAve.ps)");
	
	TFile f("histo.root","new");
	
	histoEinEMB_1D->Write();
	
	f.Close();
	
	exit(0);

}

