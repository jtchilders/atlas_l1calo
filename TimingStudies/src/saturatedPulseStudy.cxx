

#include <iostream>
#include <fstream>
#include <cmath>

#include "cbntClass.h"
#include "commandLineParser.h"
#include "PixelMap.h"

#include "TH2I.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TEventList.h"
#include "TMath.h"
#include "TF1.h"
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
	
	TCanvas *canvasA = new TCanvas("canvasA","canvasA",0,0,1000,800);
	canvasA->Update();
	canvasA->SetLogy(1);
	TCanvas *canvasB = new TCanvas("canvasB","canvasB",0,0,1000,800);
	canvasB->Update();
	
	const uint satHigh = 767;
	const uint satLow  = 255;
	const uint satLevel = 1023;
	const uint fir1 = 0;
	const uint fir2 = 7;
	const uint fir3 = 15;
	const uint fir4 = 10;
	const uint fir5 = 0;
	
	TF1 *fSatHigh = new TF1("satHigh","767",0,5);
	TF1 *fSatLow = new TF1("satLow","255",0,5);
	TF1 *fSatLevel = new TF1("satLevel","1023",0,5);
	TH1I *hAdcSlices = new TH1I("hAdcSlices","ADC",5,0,5);
	hAdcSlices->SetMinimum(10);
	hAdcSlices->SetMaximum(1200);
	
	TH1I *hBcidBit = new TH1I("hBcidBit","Various PPM BCID Bits",3,0,3);
	{
	char axisNames[3][30] = {"Ext","Sat","Peak"};
	for(int i=0;i<3;i++) hBcidBit->GetXaxis()->SetBinLabel(i+1,axisNames[i]);
	}
	
	TProfile *hAveSignal = new TProfile("hAveSignal","",5,0,5);
	
	TH2I *hBcidBits2 = new TH2I("hBcidBits2","calculated bcids and real",5,0,5,4,0,4);
	{
	char axisNames[4][30] = {"calcSat","realSat","calcPeak","realPeak"};
	for(uint i=0;i<4;i++) hBcidBits2->GetYaxis()->SetBinLabel(i+1,axisNames[i]);
	}
	
	
	
	
	//TH2I *hBcidBitCompare = new TH2I("hBcidBitCompare","
	
	PixelMap<uint> *pmHadFailedChannels = new PixelMap<uint>(TrigTower);
	//PixelMap<uint> *pmEmFailedChannels  = new PixelMap<uint>(TrigTower);
	
	uint onePercent = (uint)(0.01*totalEvts);
	if(onePercent == 0) onePercent = 1;
	for(int i=0;i<totalEvts;i++){
		
		t->GetEntry(i);
		
		if(!(i % onePercent)){
			cerr << "\r Percent Done: " << (int)((i*100)/totalEvts) << "\t";
		}
		
		// loop over trigger towers
		for(int tt=0;tt < t->L1CaloPPM_ntt;tt++){
			
			float eta = t->L1CaloPPM_eta->at(tt);
			float phi = t->L1CaloPPM_phi->at(tt);
			
			if( !(-1.5 <= eta && eta < 1.5) ) continue;
			
			
			if(t->L1CaloPPM_hadIsFilled->at(tt)){
				
				
				const uint firCalc[5] = {t->L1CaloPPM_hadADC->at(tt)[0]*fir3+t->L1CaloPPM_hadADC->at(tt)[1]*fir4,
					t->L1CaloPPM_hadADC->at(tt)[0]*fir2+t->L1CaloPPM_hadADC->at(tt)[1]*fir3+t->L1CaloPPM_hadADC->at(tt)[2]*fir4,
					t->L1CaloPPM_hadADC->at(tt)[1]*fir2+t->L1CaloPPM_hadADC->at(tt)[2]*fir3+t->L1CaloPPM_hadADC->at(tt)[3]*fir4,
					t->L1CaloPPM_hadADC->at(tt)[2]*fir2+t->L1CaloPPM_hadADC->at(tt)[3]*fir3+t->L1CaloPPM_hadADC->at(tt)[4]*fir4,
					t->L1CaloPPM_hadADC->at(tt)[3]*fir3+t->L1CaloPPM_hadADC->at(tt)[4]*fir4};
				
				//cerr << firCalc[0] << " " << firCalc[1] << " " << firCalc[2] << " " << firCalc[3] << " " << firCalc[4] << "\n";
				
				uint tsLow=9,tsHigh=9,tsSatLvl=9,tsPeak=9,lastTS=9,lastValue=0;
				for(int ts = 0;ts < t->L1CaloPPM_hadADC->at(tt).size(); ts++){
					if(t->L1CaloPPM_hadADC->at(tt)[ts] > satLow && tsLow == 9)
						tsLow=ts;
					
					if(t->L1CaloPPM_hadADC->at(tt)[ts] > satHigh && tsHigh == 9)
						tsHigh=ts;
					
					if(t->L1CaloPPM_hadADC->at(tt)[ts] >= satLevel && tsSatLvl == 9)
						tsSatLvl=ts;
					
					hAdcSlices->SetBinContent(ts+1,t->L1CaloPPM_hadADC->at(tt)[ts]);
					
					if(firCalc[ts] > lastValue){
						lastTS = ts;
						lastValue = firCalc[ts];
					}
					
					hAveSignal->Fill(ts,t->L1CaloPPM_hadADC->at(tt)[ts]);
				
				}
				
				tsPeak = lastTS;
				
				uint tsBcid=9;
				if( tsHigh == tsSatLvl && tsSatLvl != 9)
					tsBcid = tsSatLvl + 1;
				else{
					if(tsLow == tsHigh - 1 && tsHigh == tsSatLvl - 1 && tsSatLvl != 9)
						tsBcid = tsSatLvl;
					else if( tsLow == tsHigh && tsHigh == tsSatLvl - 1 && tsSatLvl != 9)
						tsBcid = tsSatLvl + 1;
					
				}
				
				if(tsBcid != 9)
					hBcidBits2->Fill(tsBcid,0);
				if(tsPeak != 9)
					hBcidBits2->Fill(tsPeak,2);
				
				const uint extBcid = (t->L1CaloPPM_hadBCID->at(tt) & 0x1) ? 1 : 0;
				const uint satBcid = (t->L1CaloPPM_hadBCID->at(tt) & 0x2) ? 1 : 0;
				const uint peakBcid = (t->L1CaloPPM_hadBCID->at(tt) & 0x4) ? 1 : 0;
				
				if(satBcid)
					hBcidBits2->Fill(2,1);
				if(peakBcid)
					hBcidBits2->Fill(2,3);
				
				if(extBcid) // Ext BCID
					hBcidBit->Fill(0);
				if(satBcid) // Sat BCID
					hBcidBit->Fill(1);
				if(peakBcid) // Peak Finder
					hBcidBit->Fill(2);
				
				
				
				
				cerr << "tsLow: " << tsLow << "; tsHigh: " << tsHigh << "; tsSatLvl: " << tsSatLvl << "; tsBcid: " << tsBcid << "; satBcid: " << satBcid << ";  tsPeak: " << tsPeak << "; peakBCID: " << peakBcid << "; LUT: " << t->L1CaloPPM_hadLUT->at(tt)[0] << endl;
				
				
				hAdcSlices->Draw();
				fSatLow->Draw("same");
				fSatHigh->Draw("same");
				fSatLevel->Draw("same");
				canvasB->Update();
				if(t->L1CaloPPM_hadLUT->at(tt)[0])
					cin.get();
				
				
				
			}
			/*
			if(t->L1CaloPPM_emIsFilled->at(tt)){
				
				
				const uint firCalc[5] = {t->L1CaloPPM_emADC->at(tt)[0]*fir3+t->L1CaloPPM_emADC->at(tt)[1]*fir4,
					t->L1CaloPPM_emADC->at(tt)[0]*fir2+t->L1CaloPPM_emADC->at(tt)[1]*fir3+t->L1CaloPPM_emADC->at(tt)[2]*fir4,
					t->L1CaloPPM_emADC->at(tt)[1]*fir2+t->L1CaloPPM_emADC->at(tt)[2]*fir3+t->L1CaloPPM_emADC->at(tt)[3]*fir4,
					t->L1CaloPPM_emADC->at(tt)[2]*fir2+t->L1CaloPPM_emADC->at(tt)[3]*fir3+t->L1CaloPPM_emADC->at(tt)[4]*fir4,
					t->L1CaloPPM_emADC->at(tt)[3]*fir3+t->L1CaloPPM_emADC->at(tt)[4]*fir4};
				
				//cerr << firCalc[0] << " " << firCalc[1] << " " << firCalc[2] << " " << firCalc[3] << " " << firCalc[4] << "\n";
				
				uint tsLow=9,tsHigh=9,tsSatLvl=9,tsPeak=9,lastTS=9,lastValue=0;
				for(int ts = 0;ts < t->L1CaloPPM_emADC->at(tt).size(); ts++){
					if(t->L1CaloPPM_emADC->at(tt)[ts] > satLow && tsLow == 9)
						tsLow=ts;
					
					if(t->L1CaloPPM_emADC->at(tt)[ts] > satHigh && tsHigh == 9)
						tsHigh=ts;
					
					if(t->L1CaloPPM_emADC->at(tt)[ts] >= satLevel && tsSatLvl == 9)
						tsSatLvl=ts;
					
					hAdcSlices->SetBinContent(ts+1,t->L1CaloPPM_emADC->at(tt)[ts]);
					
					if(firCalc[ts] > lastValue){
						lastTS = ts;
						lastValue = firCalc[ts];
					}
					
					hAveSignal->Fill(ts,t->L1CaloPPM_emADC->at(tt)[ts]);
				
				}
				
				tsPeak = lastTS;
				
				uint tsBcid=9;
				if( tsHigh == tsSatLvl && tsSatLvl != 9)
					tsBcid = tsSatLvl + 1;
				else{
					if(tsLow == tsHigh - 1 && tsHigh == tsSatLvl - 1 && tsSatLvl != 9)
						tsBcid = tsSatLvl;
					else if( tsLow == tsHigh && tsHigh == tsSatLvl - 1 && tsSatLvl != 9)
						tsBcid = tsSatLvl + 1;
					
				}
				
				if(tsBcid != 9)
					hBcidBits2->Fill(tsBcid,0);
				if(tsPeak != 9)
					hBcidBits2->Fill(tsPeak,2);
				
				const uint extBcid = (t->L1CaloPPM_emBCID->at(tt) & 0x1) ? 1 : 0;
				const uint satBcid = (t->L1CaloPPM_emBCID->at(tt) & 0x2) ? 1 : 0;
				const uint peakBcid = (t->L1CaloPPM_emBCID->at(tt) & 0x4) ? 1 : 0;
				
				if(satBcid)
					hBcidBits2->Fill(2,1);
				if(peakBcid)
					hBcidBits2->Fill(2,3);
				
				if(extBcid) // Ext BCID
					hBcidBit->Fill(0);
				if(satBcid) // Sat BCID
					hBcidBit->Fill(1);
				if(peakBcid) // Peak Finder
					hBcidBit->Fill(2);
				
				
				
				
				cerr << "tsLow: " << tsLow << "; tsHigh: " << tsHigh << "; tsSatLvl: " << tsSatLvl << "; tsBcid: " << tsBcid << "; satBcid: " << satBcid << ";  tsPeak: " << tsPeak << "; peakBCID: " << peakBcid << "; LUT: " << t->L1CaloPPM_emLUT->at(tt)[0] << endl;
				
				
				hAdcSlices->Draw();
				fSatLow->Draw("same");
				fSatHigh->Draw("same");
				fSatLevel->Draw("same");
				canvasB->Update();
				if(t->L1CaloPPM_emLUT->at(tt)[0])
					cin.get();
				
				
// 				bool noSatTS=true;
// 				for(int ts=0;ts<t->L1CaloPPM_emADC->at(tt).size();ts++){
// 					if(t->L1CaloPPM_emADC->at(tt)[ts] >= 1023)
// 						noSatTS=false;
// 					
// 					//histo->Fill(ts,t->L1CaloPPM_emADC->at(tt)[ts]);
// 				}
// 				if(noSatTS)
// 					pmHadFailedChannels->SetTriggerTower(eta,phi,pmHadFailedChannels->GetTriggerTower(eta,phi)+1);
// 				
				
				
			}
			*/
			
		} // end for(ntt)
		
	} // end for(totalEvts)
	
	canvasA->cd();
	/*
	TH2I *hHadFailedChannels = new TH2I("hHadFailedChannels","HAD: Failed Channels (never reach 1023);eta;phi",
			L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
	pmHadFailedChannels->FillEtaPhiHistogram(hHadFailedChannels);
	hHadFailedChannels->SetMinimum(0);
	
	hHadFailedChannels->Draw("colz");
	canvasA->cd()->SetGridx(1);
	canvasA->cd()->SetGridy(1);
	*/
	
	hAveSignal->Draw();
	
	canvasA->SaveAs("tempHistoA.ps");
	
	
	canvasB->cd();
	
	hBcidBits2->Draw("colz");
	/*
	TH2I *hEmFailedChannels = new TH2I("hEmFailedChannels","EM: Failed Channels (never reach 1023);eta;phi",
			L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
	pmEmFailedChannels->FillEtaPhiHistogram(hEmFailedChannels);
	hEmFailedChannels->SetMinimum(0);
	
	hEmFailedChannels->Draw("colz");
	canvasB->cd()->SetGridx(1);
	canvasB->cd()->SetGridy(1);
	*/
	canvasB->SaveAs("tempHistoB.ps");
	
	
	/*
	map<uint,uint>::iterator itHadStart,itHadEnd,itEmStart,itEmEnd;
	itHadStart = pmHadFailedChannels->GetTtBeginItr();
	itHadEnd = pmHadFailedChannels->GetTtEndItr();
	itEmStart = pmEmFailedChannels->GetTtBeginItr();
	itEmEnd = pmEmFailedChannels->GetTtEndItr();
	
	ofstream *fout = new ofstream("failedChannels.txt");
	
	for(;itEmStart!=itEmEnd;itEmStart++){
		uint eta,phi;
		pmEmFailedChannels->GetEtaPhiFromID(itEmStart->first,eta,phi);
		
		//cerr << hex << itEmStart->first << dec << " " << ((int)eta-49) << " " << phi << " " << itEmEnd->second << endl;
		
		*fout << ((int)eta-49) << "\t" << phi << "\t" << itEmStart->second << endl;
		
	}
	
	fout->close();
	*/
	app->Run();
}

