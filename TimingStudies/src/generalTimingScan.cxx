

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
#include "TMath.h"

using namespace std;

int main(int argc, char** argv){
	
	
	gROOT->SetBatch(kTRUE);
	
	#include "gStyleSetup.cxx"
	
	CommandLineTool* opts = new CommandLineTool(argc,argv);
	
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
	
	TH1I* peakDiff = new TH1I("peakDiff","Difference in Peak location along eta=0;time slice",10,-5,5);
	
	//TEventList *list = new TEventList("list","list");
	
	TCanvas* canvas = new TCanvas("canvas","canvas",0,0,1000,800);
	
	PixelMap<uint>* pmHadPeakSum  = new PixelMap<uint>(TrigTower);
	PixelMap<uint>* pmHadPeakSum2 = new PixelMap<uint>(TrigTower);
	PixelMap<uint>* pmHadPeakN    = new PixelMap<uint>(TrigTower);
	
	PixelMap<uint>* pmEmPeakSum   = new PixelMap<uint>(TrigTower);
	PixelMap<uint>* pmEmPeakSum2  = new PixelMap<uint>(TrigTower);
	PixelMap<uint>* pmEmPeakN     = new PixelMap<uint>(TrigTower);
	
	double minAve = 45.0;
	double minRms = 2.5;
	uint onePercent = (uint)(0.01*totalEvts);
	for(int i=0;i<totalEvts;i++){
		t->GetEntry(i);
		
		if(!(i % onePercent)){
			cerr << "\r Percent Done: " << (int)((i*100)/totalEvts) << "\t";
		}
		
		// loop over trigger towers
		for(int tt=0;tt < t->L1CaloPPM_ntt;tt++){
			
			float eta = t->L1CaloPPM_eta->at(tt);
			float phi = t->L1CaloPPM_phi->at(tt);
			
			if(t->L1CaloPPM_hadIsFilled){
				double ADCs[5] = {t->L1CaloPPM_hadADC->at(tt)[0],t->L1CaloPPM_hadADC->at(tt)[1], t->L1CaloPPM_hadADC->at(tt)[2],t->L1CaloPPM_hadADC->at(tt)[3],t->L1CaloPPM_hadADC->at(tt)[4]};
				double ave = TMath::Mean(5,ADCs);
				double rms = TMath::RMS(5,ADCs);
				
				if(rms > minRms && ave > minAve){
					
					uint tsPeak=9;
					uint tsValue=0;
					for(int ts=0;ts<t->L1CaloPPM_hadADC->at(tt).size();ts++){
						if(t->L1CaloPPM_hadADC->at(tt)[ts] > tsValue){
							tsPeak = ts;
							tsValue = t->L1CaloPPM_hadADC->at(tt)[ts];
						}
						
					} // for(ts)
					
					if(tsPeak != 9){
						uint newSum = pmHadPeakSum->GetTriggerTower(eta,phi) + tsPeak;
						pmHadPeakSum->SetTriggerTower(eta,phi,newSum);
						
						uint newSum2 = pmHadPeakSum2->GetTriggerTower(eta,phi) + tsPeak*tsPeak;
						pmHadPeakSum2->SetTriggerTower(eta,phi,newSum2);
						
						uint newN = pmHadPeakN->GetTriggerTower(eta,phi) + 1;
						pmHadPeakN->SetTriggerTower(eta,phi,newN);
						
						//cerr << "tsPeak: " << tsPeak << "; tsValue: " << tsValue << "; oldSum: " << oldSum << "; oldSum2: " << oldSum2 << "; oldN: " << oldN << "; ADCs: " << t->L1CaloPPM_hadADC->at(tt)[0] << " " << t->L1CaloPPM_hadADC->at(tt)[1] << " " << t->L1CaloPPM_hadADC->at(tt)[2] << " " << t->L1CaloPPM_hadADC->at(tt)[3] << " " << t->L1CaloPPM_hadADC->at(tt)[4] << "; Mean: " << ave << "; RMS: " << rms << endl;
					}
					
				} //if(ave)
				
			} //if(had)
			
			if(t->L1CaloPPM_emIsFilled){
				double ADCs[5] = {t->L1CaloPPM_emADC->at(tt)[0],t->L1CaloPPM_emADC->at(tt)[1], t->L1CaloPPM_emADC->at(tt)[2],t->L1CaloPPM_emADC->at(tt)[3],t->L1CaloPPM_emADC->at(tt)[4]};
				double ave = TMath::Mean(5,ADCs);
				double rms = TMath::RMS(5,ADCs);
				
				if(rms > minRms && ave > minAve){
					
					uint tsPeak=9;
					uint tsValue=0;
					for(int ts=0;ts<t->L1CaloPPM_emADC->at(tt).size();ts++){
						if(t->L1CaloPPM_emADC->at(tt)[ts] > tsValue){
							tsPeak = ts;
							tsValue = t->L1CaloPPM_emADC->at(tt)[ts];
						}
						
					} // for(ts)
					
					if(tsPeak != 9){
						uint newSum = pmEmPeakSum->GetTriggerTower(eta,phi) + tsPeak;
						pmEmPeakSum->SetTriggerTower(eta,phi,newSum);
						
						uint newSum2 = pmEmPeakSum2->GetTriggerTower(eta,phi) + tsPeak*tsPeak;
						pmEmPeakSum2->SetTriggerTower(eta,phi,newSum2);
						
						uint newN = pmEmPeakN->GetTriggerTower(eta,phi) + 1;
						pmEmPeakN->SetTriggerTower(eta,phi,newN);
						
						
					}
				} //if(ave)
				
			} //if(em)
			
			
		} // end for(ntt)
		
	} // end for(totalEvts)
	
	
	TH2F* hadPeakAveTs = new TH2F("hadPeakAveTs","HAD Average Time Slice of Peak;eta;phi",L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0.0,2.0*PI);
	TH2F* hadPeakAveTsSigma = new TH2F("hadPeakAveTsSigma","HAD Sigma of the Average Time Slice of Peak;eta;phi",L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0.,2.*PI);
	
	{
	
	PixelMap<float>* pmHadPeakAveTs = new PixelMap<float>(TrigTower);
	PixelMap<float>* pmHadPeakAveTsSigma = new PixelMap<float>(TrigTower);
	
	map<uint,uint>::iterator itHadSumBegin = pmHadPeakSum->GetTtBeginItr();
	map<uint,uint>::iterator itHadSumEnd = pmHadPeakSum->GetTtEndItr();
	
	map<uint,uint>::iterator itHadSum2Begin = pmHadPeakSum2->GetTtBeginItr();
	map<uint,uint>::iterator itHadSum2End = pmHadPeakSum2->GetTtEndItr();
	
	map<uint,uint>::iterator itHadNBegin = pmHadPeakN->GetTtBeginItr();
	map<uint,uint>::iterator itHadNEnd = pmHadPeakN->GetTtEndItr();
	
	for(;itHadSumBegin != itHadSumEnd;itHadSumBegin++,itHadSum2Begin++,itHadNBegin++){
		uint Sum  = itHadSumBegin->second;
		uint Sum2 = itHadSum2Begin->second;
		uint Count    = itHadNBegin->second;
		
		//cerr << "Sum = " << Sum << "; Count = " << Count << "; Sum2 = " << Sum2 << endl;
		
		
		
		double ave;
		double sigma;
		if(Count != 0){
			ave   = (double)Sum/(double)Count;
			if(Count != 1)
				sigma = sqrt((1.0/(double)Count)*(double)Sum2 - (double)ave*(double)ave);
			else
				sigma = 0;
		}
		else{
			ave   = 0;
			sigma = 0;
		}
		//cerr << "ave: " << ave << "; sigma: " << sigma << endl;
		
		uint etaPhiID = itHadSumBegin->first;
		uint eta=0,phi=0;
		pmHadPeakSum->GetEtaPhiFromID(etaPhiID,eta,phi);
		float fEta = pmHadPeakSum->itofEta(eta);
		float fPhi = pmHadPeakSum->itofPhi(phi);
		
		pmHadPeakAveTs->SetTriggerTower(fEta,fPhi,ave);
		pmHadPeakAveTsSigma->SetTriggerTower(fEta,fPhi,sigma);
		
	}
	
	pmHadPeakAveTs->FillEtaPhiHistogram(hadPeakAveTs);
	pmHadPeakAveTsSigma->FillEtaPhiHistogram(hadPeakAveTsSigma);
	
	delete pmHadPeakAveTs; pmHadPeakAveTs = 0;
	delete pmHadPeakAveTsSigma; pmHadPeakAveTsSigma = 0;
	
	}
	
	TH2F* emPeakAveTs = new TH2F("emPeakAveTs","EM Average Time Slice of Peak;eta;phi",L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0.,2.*PI);
	TH2F* emPeakAveTsSigma = new TH2F("emPeakAveTsSigma","EM Sigma of the Average Time Slice of Peak;eta;phi",L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0.,2.*PI);
	
	{
	
	PixelMap<float>* pmEmPeakAveTs = new PixelMap<float>(TrigTower);
	PixelMap<float>* pmEmPeakAveTsSigma = new PixelMap<float>(TrigTower);
	
	map<uint,uint>::iterator itEmSumBegin = pmEmPeakSum->GetTtBeginItr();
	map<uint,uint>::iterator itEmSumEnd = pmEmPeakSum->GetTtEndItr();
	
	map<uint,uint>::iterator itEmSum2Begin = pmEmPeakSum2->GetTtBeginItr();
	map<uint,uint>::iterator itEmSum2End = pmEmPeakSum2->GetTtEndItr();
	
	map<uint,uint>::iterator itEmNBegin = pmEmPeakN->GetTtBeginItr();
	map<uint,uint>::iterator itEmNEnd = pmEmPeakN->GetTtEndItr();
	
	for(;itEmSumBegin != itEmSumEnd;itEmSumBegin++,itEmSum2Begin++,itEmNBegin++){
		uint Sum  = itEmSumBegin->second;
		uint Sum2 = itEmSum2Begin->second;
		uint Count    = itEmNBegin->second;
		
		double ave;
		double sigma;
		if(Count != 0){
			ave   = (double)Sum/(double)Count;
			if(Count != 1)
				sigma = sqrt((1.0/(double)Count)*(double)Sum2 - (double)ave*(double)ave);
			else
				sigma = 0;
		}
		else{
			ave   = 0;
			sigma = 0;
		}
		//cerr << "ave: " << ave << "; sigma: " << sigma << endl;
		
		uint etaPhiID = itEmSumBegin->first;
		uint eta=0,phi=0;
		pmEmPeakSum->GetEtaPhiFromID(etaPhiID,eta,phi);
		float fEta = pmEmPeakSum->itofEta(eta);
		float fPhi = pmEmPeakSum->itofPhi(phi);
		
		pmEmPeakAveTs->SetTriggerTower(fEta,fPhi,ave);
		pmEmPeakAveTsSigma->SetTriggerTower(fEta,fPhi,sigma);
		
	}
	
	pmEmPeakAveTs->FillEtaPhiHistogram(emPeakAveTs);
	pmEmPeakAveTsSigma->FillEtaPhiHistogram(emPeakAveTsSigma);
	
	delete pmEmPeakAveTs; pmEmPeakAveTs = 0;
	delete pmEmPeakAveTsSigma; pmEmPeakAveTsSigma = 0;
	
	}
	
	hadPeakAveTs->Draw("colz");
	canvas->SaveAs("tempHisto.ps(");
	
	hadPeakAveTsSigma->Draw("colz");
	canvas->SaveAs("tempHisto.ps");
	
	emPeakAveTs->Draw("colz");
	canvas->SaveAs("tempHisto.ps");
	
	emPeakAveTsSigma->Draw("colz");
	canvas->SaveAs("tempHisto.ps)");
	
	
}

