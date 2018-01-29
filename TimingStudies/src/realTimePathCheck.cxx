
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>

#include "cbntClass.h"
#include "L1CaloChannelMap.h"
#include "PixelMap.h"

#include "commandLineParser.h"

#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TPaveText.h"

using namespace std;

int main(int argc,char** argv){
	
	
	#include "gStyleSetup.cxx"
	
	//gROOT->SetBatch(true);
	
	CommandLineTool *opt = new CommandLineTool(argc,argv);
	
	cbntClass *t;
	
	if(!opt->IsFileList()){
		t = new cbntClass(opt->GetFilename());
	}
	else if(opt->IsFileList()){
		t = new cbntClass(opt->GetFilename(),opt->IsFileList());
		
	}
	
	const int totalEvts = t->fChain->GetEntries();
	
	cerr << "Total Events: " << totalEvts << endl;
	
	L1CaloChannelMap *map = new L1CaloChannelMap;
	map->SetCpmEnable(false);
	map->SetJemEnable(false);
	map->SetPpmEnable(true);
	
	
	TPaveText *chanListA = new TPaveText(0.1,0.9,0.9,0.1,"NDC");
	chanListA->AddText("EM Inconsistent MCMs:\n");
	TPaveText *chanListB = new TPaveText(0.1,0.9,0.9,0.1,"NDC");
	chanListB->AddText("HAD Inconsistent MCMs:\n");
	TPaveText *chanListC = new TPaveText(0.1,0.9,0.9,0.1,"NDC");
	chanListC->AddText("EM Inconsistent MCMs:\n");
	TPaveText *chanListD = new TPaveText(0.1,0.9,0.9,0.1,"NDC");
	chanListD->AddText("HAD Inconsistent MCMs:\n");
	

	TH1D *histoEMlutSum = new TH1D("histoEMlutSum","EM LUT Sum; #Sigma LUT",150,0,700);
	TH1D *histoEMjetEl = new TH1D("histoEMjetEl","EM Jet Element Energy; Jet Element Energy [GeV]",150,0,700);
	TH2D *histoEMjetElvsLUTSum = new TH2D("histoEMjetElvsLUTSum","EM Jet Element vs LUT;#Sigma LUT; Jet Element",100,0,750,100,0,750);
	TH2D *histoEMjemIncon = new TH2D("histoEMjemIncon","EM Inconsistancies;#eta;#phi",98,-4.9,4.9,64,0,6.4);
	TH2D *histoEMjemCon = new TH2D("histoEMjemCon","EM Consistent Data;#eta;#phi",98,-4.9,4.9,64,0,6.4);
	
	TH1D *histoHADlutSum = new TH1D("histoHADlutSum","HAD LUT Sum; #Sigma LUT",150,0,700);
	TH1D *histoHADjetEl = new TH1D("histoHADjetEl","HAD Jet Element Energy; Jet Element Energy [GeV]",150,0,700);
	TH2D *histoHADjetElvsLUTSum = new TH2D("histoHADjetElvsLUTSum","HAD Jet Element vs LUT;#Sigma LUT;emJetEl",100,0,750,100,0,750);
	TH2D *histoHADjemIncon = new TH2D("histoHADjemIncon","HAD Inconsistent Data;#eta;#phi",98,-4.9,4.9,64,0,6.4);
	TH2D *histoHADjemCon = new TH2D("histoHADjemCon","HAD Consistent Data;#eta;#phi",98,-4.9,4.9,64,0,6.4);
	
	TH1D *histoEMlut = new TH1D("histoEMlut","EM LUT;LUT",150,0,300);
	TH1D *histoEMCpmTT = new TH1D("histoEMCpmTT","EM CPM Trigger Tower Energy;EM CPM TT [GeV]",150,0,300);
	TH2D *histoEMCpmTTvsLUT = new TH2D("histoEMCpmTTvsLUT","EM CPM TT vs PPM LUT;PPM LUT; CPM TT",100,0,300,100,0,300);
	TH2D *histoEMCpmIncon = new TH2D("histoEMCpmIncon","EM Inconsistencies;#eta;#phi",98,-4.9,4.9,64,0,6.4);
	TH2D *histoEMCpmCon = new TH2D("histoEMCpmCon","EM Consistencies;#eta;#phi",98,-4.9,4.9,64,0,6.4);
	
	TH1D *histoHADlut = new TH1D("histoHADlut","HAD LUT;LUT",150,0,300);
	TH1D *histoHADCpmTT = new TH1D("histoHADCpmTT","HAD CPM Trigger Tower Energy;EM CPM TT [GeV]",150,0,300);
	TH2D *histoHADCpmTTvsLUT = new TH2D("histoHADCpmTTvsLUT","HAD CPM TT vs PPM LUT;PPM LUT; CPM TT",100,0,300,100,0,300);
	TH2D *histoHADCpmIncon = new TH2D("histoHADCpmIncon","HAD Inconsistencies;#eta;#phi",98,-4.9,4.9,64,0,6.4);
	TH2D *histoHADCpmCon = new TH2D("histoHADCpmCon","HAD Consistencies;#eta;#phi",98,-4.9,4.9,64,0,6.4);
	
	
	
	PixelMap<uint> *emLUTsumPM = new PixelMap<uint>(JetEl);
	PixelMap<uint> *emJetElPM = new PixelMap<uint>(JetEl);
	PixelMap<uint> *hadLUTsumPM = new PixelMap<uint>(JetEl);
	PixelMap<uint> *hadJetElPM = new PixelMap<uint>(JetEl);
	
	PixelMap<uint> *emLutPM = new PixelMap<uint>(TrigTower);
	PixelMap<uint> *emCpmTtPM = new PixelMap<uint>(TrigTower);
	PixelMap<uint> *hadLutPM = new PixelMap<uint>(TrigTower);
	PixelMap<uint> *hadCpmTtPM = new PixelMap<uint>(TrigTower);
	
	
	PixelMap<uint> *emConsistentJemPpmPM = new PixelMap<uint>(JetEl);
	PixelMap<uint> *emInconsistentJemPpmPM = new PixelMap<uint>(JetEl);
	
	PixelMap<uint> *hadConsistentJemPpmPM = new PixelMap<uint>(JetEl);
	PixelMap<uint> *hadInconsistentJemPpmPM = new PixelMap<uint>(JetEl);
	
	PixelMap<uint> *emConsistentCpmPpmPM = new PixelMap<uint>(TrigTower);
	PixelMap<uint> *emInconsistentCpmPpmPM = new PixelMap<uint>(TrigTower);
	
	PixelMap<uint> *hadConsistentCpmPpmPM = new PixelMap<uint>(TrigTower);
	PixelMap<uint> *hadInconsistentCpmPpmPM = new PixelMap<uint>(TrigTower);
	
	for(int i=0;i<totalEvts;i++){
	
		t->GetEntry(i);
	
		if( !(i % (int(totalEvts*0.01) + 1)))
		cerr << "\r Percent Done: " << int(((float)i/(float)totalEvts)*100) << "\t";
    		
		//cerr << "----------+++++++++++++++--------------\n";
		
		emLUTsumPM->ClearPixelMap(JetEl);
		
		emJetElPM->ClearPixelMap(JetEl);
		
		hadLUTsumPM->ClearPixelMap(JetEl);
		
		hadJetElPM->ClearPixelMap(JetEl);
		
		emLutPM->ClearPixelMap(TrigTower);
		
		emCpmTtPM->ClearPixelMap(TrigTower);
		
		hadLutPM->ClearPixelMap(TrigTower);
		
		hadCpmTtPM->ClearPixelMap(TrigTower);
		
		// Loop over the number of trigger towers with data for this event
		for(uint tt=0;tt<t->L1CaloPPM_ntt;tt++){
			
			// Grab the eta/phi location for this PPM trigger tower.
			float eta = t->L1CaloPPM_eta->at(tt);
			float phi = t->L1CaloPPM_phi->at(tt);
			
			
// 			if( 2.7 < eta && eta < 2.9){
// 				cerr << "EM LUT: " << t->L1CaloPPM_emLUT->at(j)[0] << "; eta:phi = " << eta << ":" << phi << endl;
// 			}
			
			// Only book trigger towers with EM data
			if(t->L1CaloPPM_emIsFilled->at(tt)){
				
				// only want non-zero data
				if(t->L1CaloPPM_emLUT->at(tt)[0] != 0){
					
					uint tempLUT = t->L1CaloPPM_emLUT->at(tt)[0];
					// EM LUT Plot
					histoEMlut->Fill(tempLUT);
					
					emLutPM->SetTriggerTower(eta,phi,tempLUT);
					
					// Calculating LUT Sum for each Jet Element
					uint value = emLUTsumPM->GetJetEl(eta,phi);
					value += tempLUT;
					//cerr << eta << ":" << phi << " -- " << value << " " << tempLUT << endl;
					emLUTsumPM->SetJetEl(eta,phi,value);
					
					
				}
				
			}
      			
			// Only book trigger towers with hadronic data
			if(t->L1CaloPPM_hadIsFilled->at(tt)){
				// only want non-zero data
				if(t->L1CaloPPM_hadLUT->at(tt)[0] != 0){
					
					uint tempLUT = t->L1CaloPPM_hadLUT->at(tt)[0];
					
					// HAD LUT Plot
					histoHADlut->Fill(tempLUT);
					
					hadLutPM->SetTriggerTower(eta,phi,tempLUT);
					
					//cerr << "HAD LUT: eta = " << eta << "; phi = " << phi << "; LUT = " << tempLUT << endl;
					
					// Calculating LUT Sum for each Jet Element
					uint value = hadLUTsumPM->GetJetEl(eta,phi);
					value += tempLUT;
					hadLUTsumPM->SetJetEl(eta,phi,value);
				}
			}
		}// end for(ntt)
    		
    		// Loop over the Jet Elements for this events
		for(uint je=0;je<t->L1CaloJEM_JetEl_n;je++){
			
			// Grab the eta/phi for this Jet Element
			float eta = t->L1CaloJEM_JetEl_eta->at(je);
			float phi = t->L1CaloJEM_JetEl_phi->at(je);
			
			uint emJetEl = t->L1CaloJEM_JetEl_emEnergy->at(je);
			
			// only want non-zero data for some plots
			if(emJetEl != 0){
				// Plot the Jet Element
				histoEMjetEl->Fill(emJetEl);
				
				emJetElPM->SetJetEl(eta,phi,emJetEl);
				
				// Compare with PPM
				if(emJetEl != emLUTsumPM->GetJetEl(eta,phi))
					emInconsistentJemPpmPM->SetJetEl(eta,phi,emInconsistentJemPpmPM->GetJetEl(eta,phi)+1);
				else
					emConsistentJemPpmPM->SetJetEl(eta,phi,emConsistentJemPpmPM->GetJetEl(eta,phi)+1);
				
			}
			
			uint hadJetEl = t->L1CaloJEM_JetEl_hadEnergy->at(je);
			
			// only want non-zero data for some plots
			if(hadJetEl != 0){
				// Plot the Jet Element
				histoHADjetEl->Fill(hadJetEl);
				
				hadJetElPM->SetJetEl(eta,phi,hadJetEl);
				
				// Compare with PPM
				if(hadJetEl != hadLUTsumPM->GetJetEl(eta,phi))
					hadInconsistentJemPpmPM->SetJetEl(eta,phi,hadInconsistentJemPpmPM->GetJetEl(eta,phi)+1);
				else
					hadConsistentJemPpmPM->SetJetEl(eta,phi,hadConsistentJemPpmPM->GetJetEl(eta,phi)+1);
			}
			
		} // end for(JetEl_n)
		
		// Loop over all the Cluster Tower elements
		for(int ct=0;ct < t->L1CaloCPM_Towers_n; ct++){
			
			// Grab the eta phi for this tower
			float eta = t->L1CaloCPM_Towers_eta->at(ct);
			float phi = t->L1CaloCPM_Towers_phi->at(ct);
			
			//int emLut = emLutPM->GetPixel(eta,phi);
			int emCpmTt = t->L1CaloCPM_Towers_emEnergy->at(ct);
			
			// Only want non-zero data for some plots
			if(emCpmTt != 0){
				// Plot of EM CPM Trigger Tower
				histoEMCpmTT->Fill(emCpmTt);
				
				// Fill the Trigger Tower for later comparison to PPM
				emCpmTtPM->SetTriggerTower(eta,phi,emCpmTt);
				
				// Compare with PPM
				if(emCpmTt != emLutPM->GetTriggerTower(eta,phi))
					emInconsistentCpmPpmPM->SetTriggerTower(eta,phi,emInconsistentCpmPpmPM->GetTriggerTower(eta,phi)+1);
				else
					emConsistentCpmPpmPM->SetTriggerTower(eta,phi,emConsistentCpmPpmPM->GetTriggerTower(eta,phi)+1);
				
			}
			
			int hadCpmTt = t->L1CaloCPM_Towers_hadEnergy->at(ct);
			 
			if(hadCpmTt != 0)
			//cerr << "Tower TT eta/phi: " << eta << ":" << phi <<  "; HAD Energy: " << hadCpmTt << endl;
			
			if( hadCpmTt != 0){
				// Plot of HAD CPM Trigger Tower
				histoHADCpmTT->Fill(hadCpmTt);
				
				// Fill the Trigger Tower for later comparison to PPM
				hadCpmTtPM->SetTriggerTower(eta,phi,hadCpmTt);
				
				// Compare with PPM
				if(hadCpmTt != hadLutPM->GetTriggerTower(eta,phi))
					hadInconsistentCpmPpmPM->SetTriggerTower(eta,phi,hadInconsistentCpmPpmPM->GetTriggerTower(eta,phi)+1);
				else
					hadConsistentCpmPpmPM->SetTriggerTower(eta,phi,hadConsistentCpmPpmPM->GetTriggerTower(eta,phi)+1);
				
			}
			
		}// end for(CPM TT)
		
		// Loop over the Trigger Towers for the CPM to PPM comparison Plots
		for(int tt=0;tt<t->L1CaloPPM_ntt;tt++){
			
			// Grab the eta/phi location for this PPM trigger tower.
			float eta = t->L1CaloPPM_eta->at(tt);
			float phi = t->L1CaloPPM_phi->at(tt);
			
			// Compare hadronic part if filled
			if(t->L1CaloPPM_hadIsFilled->at(tt)){
				
				uint Lut = t->L1CaloPPM_hadLUT->at(tt)[0];
				if(Lut > 0){
					uint hadLut = hadLutPM->GetTriggerTower(eta,phi);
					uint hadCpmTower = hadCpmTtPM->GetTriggerTower(eta,phi);
					
					uint hadLutSum = hadLUTsumPM->GetJetEl(eta,phi);
					uint hadJetEl = hadJetElPM->GetJetEl(eta,phi);
					
					if( Lut != hadLut)
						cerr << "realTimePathCheck: Error: Mapping incorrect because LUTs not equal.\n";
					
					if(hadLut != hadCpmTower){
	hadInconsistentCpmPpmPM->SetTriggerTower(eta,phi,hadInconsistentCpmPpmPM->GetTriggerTower(eta,phi)+1);
					
					}
					
					if(hadLutSum != hadJetEl){
	hadInconsistentJemPpmPM->SetJetEl(eta,phi,hadInconsistentJemPpmPM->GetJetEl(eta,phi)+1);
					
					}
				}
			}
			
			if(t->L1CaloPPM_hadIsFilled->at(tt)){
				
				uint Lut = t->L1CaloPPM_emLUT->at(tt)[0];
				if(Lut > 0){
					uint emLut = emLutPM->GetTriggerTower(eta,phi);
					uint emCpmTower = emCpmTtPM->GetTriggerTower(eta,phi);
					
					uint emLutSum = emLUTsumPM->GetJetEl(eta,phi);
					uint emJetEl = emJetElPM->GetJetEl(eta,phi);
					
					if( Lut != emLut)
						cerr << "realTimePathCheck: Error: Mapping incorrect because LUTs not equal..\n";
					
					if(emLut != emCpmTower){
	emInconsistentCpmPpmPM->SetTriggerTower(eta,phi,emInconsistentCpmPpmPM->GetTriggerTower(eta,phi)+1);
					}
					
					if(emLutSum != emJetEl){
	emInconsistentJemPpmPM->SetJetEl(eta,phi,emInconsistentJemPpmPM->GetJetEl(eta,phi)+1);
					}
					
				}
			}
			
			
		}// end for(TT)
		
	}// end for(entry)
	
	emConsistentJemPpmPM->FillEtaPhiHistogram(histoEMjemCon);
	emInconsistentJemPpmPM->FillEtaPhiHistogram(histoEMjemIncon);
	
	hadConsistentJemPpmPM->FillEtaPhiHistogram(histoHADjemCon);
	hadInconsistentJemPpmPM->FillEtaPhiHistogram(histoHADjemIncon);
	
	emConsistentCpmPpmPM->FillEtaPhiHistogram(histoEMCpmCon);
	emInconsistentCpmPpmPM->FillEtaPhiHistogram(histoEMCpmIncon);
	
	hadConsistentCpmPpmPM->FillEtaPhiHistogram(histoHADCpmCon);
	hadInconsistentCpmPpmPM->FillEtaPhiHistogram(histoHADCpmIncon);
	
	
	TCanvas *canvasA = new TCanvas("canvasA","EM JemEl vs LUT",0,0,1000,800);
	//canvasA->SetBatch(true);
	canvasA->Divide(3,2);
	canvasA->Update();
	
	canvasA->cd(2);
	canvasA->cd(2)->SetLogy(1);
	histoEMjetEl->Draw();
	//histoEMjetEl->Print();
	
	canvasA->cd(1);
	canvasA->cd(1)->SetLogy(1);
	//histoEMlutSum->SetMaximum(histoEMjetEl->GetMaximum());
	histoEMlutSum->Draw();
	
	
	canvasA->cd(3);
	histoEMjetElvsLUTSum->Draw("colz");
	
	canvasA->cd(4);
	histoEMjemIncon->GetYaxis()->SetNdivisions(16);
	histoEMjemIncon->GetXaxis()->SetNdivisions(12);
	canvasA->cd(4)->SetGridx(1);
	canvasA->cd(4)->SetGridy(1);
	histoEMjemIncon->Draw("colz");
	
	canvasA->cd(5);
	canvasA->cd(5)->SetGridx(1);
	canvasA->cd(5)->SetGridy(1);
	histoEMjemCon->GetYaxis()->SetNdivisions(16);
	histoEMjemCon->GetXaxis()->SetNdivisions(12);
	histoEMjemCon->Draw("colz");
	
	canvasA->cd(6);
	chanListA->Draw();
	
	
	canvasA->Print("canvas.ps(");
	
	TCanvas *canvasB = new TCanvas("canvasB","HAD JemEl vs LUT",0,0,1000,800);
	//canvasB->SetBatch(true);
	canvasB->Divide(3,2);
	canvasB->Update();
	
	canvasB->cd(2);
	canvasB->cd(2)->SetLogy(1);
	histoHADjetEl->Draw();
	
	canvasB->cd(1);
	canvasB->cd(1)->SetLogy(1);
	//histoHADlutSum->SetMaximum(histoHADjetEl->GetMaximum());
	histoHADlutSum->Draw();
	
	canvasB->cd(3);
	histoHADjetElvsLUTSum->Draw("colz");
	
	canvasB->cd(4);
	canvasB->cd(4)->SetGridx(1);
	canvasB->cd(4)->SetGridy(1);
	histoHADjemIncon->GetYaxis()->SetNdivisions(16);
	histoHADjemIncon->GetXaxis()->SetNdivisions(12);
	histoHADjemIncon->Draw("colz");
	
	canvasB->cd(5);
	canvasB->cd(5)->SetGridx(1);
	canvasB->cd(5)->SetGridy(1);
	histoHADjemCon->GetYaxis()->SetNdivisions(16);
	histoHADjemCon->GetXaxis()->SetNdivisions(12);
	histoHADjemCon->Draw("colz");
	
	canvasB->cd(6);
	chanListB->Draw();
	
	canvasB->Print("canvas.ps");
	
	TCanvas *canvasC = new TCanvas("canvasC","EM CPM vs LUT",0,0,1000,800);
	//canvasC->SetBatch(true);
	canvasC->Divide(3,2);
	canvasC->Update();
	
	canvasC->cd(2);
	canvasC->cd(2)->SetLogy(1);
	histoEMCpmTT->Draw();
	
	canvasC->cd(1);
	canvasC->cd(1)->SetLogy(1);
	//histoEMlut->SetMaximum(histoEMCpmTT->GetMaximum());
	histoEMlut->Draw();
	
	canvasC->cd(3);
	histoEMCpmTTvsLUT->Draw("colz");
	
	canvasC->cd(4);
	canvasC->cd(4)->SetGridx(1);
	canvasC->cd(4)->SetGridy(1);
	histoEMCpmIncon->GetYaxis()->SetNdivisions(16);
	histoEMCpmIncon->GetXaxis()->SetNdivisions(12);
	histoEMCpmIncon->Draw("colz");
	
	canvasC->cd(5);
	canvasC->cd(5)->SetGridx(1);
	canvasC->cd(5)->SetGridy(1);
	histoEMCpmCon->GetYaxis()->SetNdivisions(16);
	histoEMCpmCon->GetXaxis()->SetNdivisions(12);
	histoEMCpmCon->Draw("colz");
	
	canvasC->cd(6);
	chanListC->Draw();
	
	canvasC->Print("canvas.ps");
	
	TCanvas *canvasD = new TCanvas("canvasD","HAD CPM vs LUT",0,0,1000,800);
	//canvasD->SetBatch(true);
	canvasD->Divide(3,2);
	canvasD->Update();
	
	canvasD->cd(2);
	canvasD->cd(2)->SetLogy(1);
	histoHADCpmTT->Draw();
	
	canvasD->cd(1);
	canvasD->cd(1)->SetLogy(1);
	//histoHADlut->SetMaximum(histoHADCpmTT->GetMaximum());
	histoHADlut->Draw();
	
	canvasD->cd(3);
	histoHADCpmTTvsLUT->Draw("colz");
	
	canvasD->cd(4);
	canvasD->cd(4)->SetGridx(1);
	canvasD->cd(4)->SetGridy(1);
	histoHADCpmIncon->GetYaxis()->SetNdivisions(16);
	histoHADCpmIncon->GetXaxis()->SetNdivisions(12);
	histoHADCpmIncon->Draw("colz");
	
	canvasD->cd(5);
	canvasD->cd(5)->SetGridx(1);
	canvasD->cd(5)->SetGridy(1);
	histoHADCpmCon->GetYaxis()->SetNdivisions(16);
	histoHADCpmCon->GetXaxis()->SetNdivisions(12);
	histoHADCpmCon->Draw("colz");
	
	canvasD->cd(6);
	chanListD->Draw();
	
	canvasD->Print("canvas.ps)");
	
	
	
	return 0;
    
}

