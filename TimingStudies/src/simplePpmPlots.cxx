

#include <iostream>

#include "NtupleTreeV1.h"

#include "L1CaloChannelMap.h"

#include "commandLineParser.h"

#include "PixelMap.h"


#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TStyle.h"

using namespace std;

void SimplePpmPlots(int argc, char** argv){
	
	
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
	
	PixelMap *pmEmAdcPeakTsSum = new PixelMap;
	pmEmAdcPeakTsSum->SetPixelSize(TrigTower);
// 	pmEmAdcPeakTsSum->SetDetectorLayer(EM);
	PixelMap *pmEmAdcPeakTsCounter = new PixelMap;
	pmEmAdcPeakTsCounter->SetPixelSize(TrigTower);
// 	pmEmAdcPeakTsCounter->SetDetectorLayer(EM);
	
	
	PixelMap *pmHadAdcPeakTsSum = new PixelMap;
	pmHadAdcPeakTsSum->SetPixelSize(TrigTower);
// 	pmHadAdcPeakTsSum->SetDetectorLayer(HAD);
	PixelMap *pmHadAdcPeakTsCounter = new PixelMap;
	pmHadAdcPeakTsCounter->SetPixelSize(TrigTower);
// 	pmHadAdcPeakTsCounter->SetDetectorLayer(HAD);
	
	const uint MIN_ADC = 50;
	
	for(int i=0;i<totalEvts;i++){
		
		t->GetEntry(i);
		
		if( !(i % (int(totalEvts*0.01) + 1)))
		cerr << "\r Percent Done: " << int(((float)i/(float)totalEvts)*100) << "\t";
		
		// Loop of trigger towers
		for(int tt=0;tt<t->L1CaloPPM_ntt;tt++){
			
			float eta = t->L1CaloPPM_eta->at(tt);
			float phi = t->L1CaloPPM_phi->at(tt);
			
			// Loop over time slice of EM ADC
			uint adcPeakValue=0;
			uint adcPeakSlice=9;
			for(int slice=0;slice<t->L1CaloPPM_emADC->at(tt).size();slice++){
				uint ADC = t->L1CaloPPM_emADC->at(tt)[slice];
				if(adcPeakValue < ADC && ADC > MIN_ADC){
					
					adcPeakValue = ADC;
					adcPeakSlice = slice;
					
				}
				
			}
			
			if( adcPeakSlice != 9){
				pmEmAdcPeakTsSum->SetTriggerTower(eta,phi,pmEmAdcPeakTsSum->GetTriggerTower(eta,phi)+adcPeakSlice);
				pmEmAdcPeakTsCounter->SetTriggerTower(eta,phi,pmEmAdcPeakTsCounter->GetTriggerTower(eta,phi)+1);
			}
			
			// Loop over time slice of HAD ADC
			adcPeakValue=0;
			adcPeakSlice=9;
			for(int slice=0;slice<t->L1CaloPPM_hadADC->at(tt).size();slice++){
				uint ADC = t->L1CaloPPM_hadADC->at(tt)[slice];
				if(adcPeakValue < ADC && ADC > MIN_ADC){
					
					adcPeakValue = ADC;
					adcPeakSlice = slice;
					
				}
				
			}
			
			if( adcPeakSlice != 9){
				pmHadAdcPeakTsSum->SetTriggerTower(eta,phi,pmHadAdcPeakTsSum->GetTriggerTower(eta,phi)+adcPeakSlice);
				pmHadAdcPeakTsCounter->SetTriggerTower(eta,phi,pmHadAdcPeakTsCounter->GetTriggerTower(eta,phi)+1);
			}
			
		}
		
		
	}// end for(entries)
	
	PixelMap *pmEmAdcPeakTsAve = new PixelMap;
	pmEmAdcPeakTsAve->SetPixelSize(TrigTower);
	
	map<uint,uint>::iterator itrSum = pmEmAdcPeakTsSum->GetTtBeginItr();
	map<uint,uint>::iterator itrCounter = pmEmAdcPeakTsCounter->GetTtBeginItr();
	while(itrSum != pmEmAdcPeakTsSum->GetTtEndItr() && itrCounter != pmEmAdcPeakTsCounter->GetTtEndItr()){
		
		if(itrCounter->second == 0){
			if(itrSum->second > 0) cerr << "Counter equal zero, but not Sum: " << itrSum->second << "; " << itrSum->first << endl;
			itrSum++;
			itrCounter++;
			continue;
		}
		
		double average = (double)itrSum->second/(double)itrCounter->second;
		cerr << "Sum: " << itrSum->second << "; Counter: " << itrCounter->second << "; Ave: " << average << endl;
		if(average - (uint)average > 0.5) itrSum->second = (uint)average + 1;
		else itrSum->second = (uint)average;
		
		pmEmAdcPeakTsAve->SetTriggerTower(itrSum->first,(uint)average);
		itrSum++;
		itrCounter++;
	}
	
	TH2D* histoA = new TH2D("histoA","Average Time Slice of ADC Peak;#eta;#phi",L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
	pmEmAdcPeakTsAve->FillEtaPhiHistogram(histoA);
	
	
	PixelMap *pmHadAdcPeakTsAve = new PixelMap;
	pmHadAdcPeakTsAve->SetPixelSize(TrigTower);
	
	itrSum = pmHadAdcPeakTsSum->GetTtBeginItr();
	itrCounter = pmHadAdcPeakTsCounter->GetTtBeginItr();
	while(itrSum != pmHadAdcPeakTsSum->GetTtEndItr() && itrCounter != pmHadAdcPeakTsCounter->GetTtEndItr()){
		
		if(itrCounter->second == 0){
			if(itrSum->second > 0) cerr << "Counter equal zero, but not Sum: " << itrSum->second << "; " << itrSum->first << endl;
			itrSum++;
			itrCounter++;
			continue;
		}
		
		double average = (double)itrSum->second/(double)itrCounter->second;
		cerr << "Sum: " << itrSum->second << "; Counter: " << itrCounter->second << "; Ave: " << average << endl;
		if(average - (uint)average > 0.5) itrSum->second = (uint)average + 1;
		else itrSum->second = (uint)average;
		
		pmHadAdcPeakTsAve->SetTriggerTower(itrSum->first,(uint)average);
		itrSum++;
		itrCounter++;
	}
	
	TH2D* histoB = new TH2D("histoB","Average Time Slice of ADC Peak;#eta;#phi",L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
	pmHadAdcPeakTsAve->FillEtaPhiHistogram(histoB);
	
	
	PixelMap *pmDiffEmHadAdcPeakTsAve = new PixelMap;
	pmDiffEmHadAdcPeakTsAve->SetPixelSize(TrigTower);
	
	map<uint,uint>::iterator itrEm = pmEmAdcPeakTsAve->GetTtBeginItr();
	map<uint,uint>::iterator itrHad= pmHadAdcPeakTsAve->GetTtBeginItr();
	while(itrEm != pmEmAdcPeakTsAve->GetTtEndItr() && itrHad != pmHadAdcPeakTsAve->GetTtEndItr()){
		
		
		pmDiffEmHadAdcPeakTsAve->SetTriggerTower(itrEm->first,(uint)((itrEm->second - itrHad->second)+5));
		itrEm++;
		itrHad++;
	}
	
	TH2D* histoC = new TH2D("histoC","Diff. in EM/Had Average Time Slice of ADC Peak;#eta;#phi",L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
	pmDiffEmHadAdcPeakTsAve->FillEtaPhiHistogram(histoC);
	
	
	TCanvas *canvas = new TCanvas("canvas","canvas",0,0,1000,800);
	canvas->SetBatch(kTRUE);
	//canvas->Divide(2,2);
	//histoA->Draw("colz");
	
	int colorsA[5] = {kMagenta,kBlue,kGreen,kOrange,kRed};
	gStyle->SetPalette(5,colorsA);
	int colorsB[10] = {kViolet,kMagenta,kBlue,kCyan,kTeal,kGreen,kYellow,kOrange,kPink,kRed};
	
	histoA->Draw("colz");
	
	
	canvas->SaveAs("canvas.ps(");
	
	histoB->Draw("colz");
	
	canvas->SaveAs("canvas.ps");
	
	gStyle->SetPalette(10,colorsB);
	
	histoC->Draw("colz");
	
	canvas->SaveAs("canvas.ps)");
	
	
	exit(0);

}

