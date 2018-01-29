#include <iostream>
#include <vector>

//#include "PixelMap.h"
#include "src/PixelMap.cpp"

#include "TCanvas.h"
#include "TH2D.h"
#include "TFile.h"
#include "TStyle.h"

using namespace std;

int main(void){
	
	//#include "../gStyleSetup.cxx"
	
	PixelMap<double> pm(PixelMap<double>::TrigTower,true);
	pm.SetProfileMode(true);
	
	TCanvas *canvas = new TCanvas("canvas","eta vs phi",0,0,800,600);
	canvas->Divide(2);
	gStyle->SetPalette(1);
	gStyle->SetOptStat(0);
	
	std::vector<TH2D*> histo;
	const unsigned int value[10] = {4,5,4,6,5,7,5,4,5,3}; // Sum = 48, Sum2 = 242, mean = 4.8, sigma = 1.08
   
   const unsigned int L1CALO_ETA_TT = 98;
   const unsigned int L1CALO_PHI_TT = 64;

	for(int i=0;i<L1CALO_ETA_TT;i++){
		
		pm.ClearPixelMap(PixelMap<double>::TrigTower);
		pm.SetProfileMode(1);
		
		for(int j=0;j<L1CALO_PHI_TT;j++){
			
// 			std::cerr << "eta: " << i << " phi: " << j << std::endl;
			
			//pm->SetTriggerTower(pm->itofEta(i),pm->itofPhi(j),j+1);
			unsigned int sum=0,sum2=0,n=0;
			for(unsigned int k=0;k<10;k++){
				if(!(-32+49<= i && i < 32+49)){
					sum += value[k] * j;
					sum2 += (value[k]*j)*(value[k]*j);
					n++;
					if(!pm.SetTriggerTower(pm.itofEta(i),pm.itofPhi(j),value[k]*j,FcalLayer::FcalLayer(FcalLayer::FCAL2)))
						std::cerr << "Failed to SetTriggerTower.\n";
					if(!pm.SetTriggerTower(pm.itofEta(i),pm.itofPhi(j),value[k]*j,FcalLayer::FcalLayer(FcalLayer::FCAL3)))
						std::cerr << "Failed to SetTriggerTower.\n";
					
				}
				else
					if(!pm.SetTriggerTower(pm.itofEta(i),pm.itofPhi(j),value[k]*j))
						cerr << "Failed to SetTriggerTower.\n";
					
			}
			
// 			std::cerr << "sum: " << sum << " sum2: " << sum2 << " n: " << n << std::endl;
//  			std::cerr << "Mean: " << ((double)sum/(double)n) << " Sigma: " << sqrt( (1.0/(double)n)*(double)sum2 - ((double)sum/(double)n)*((double)sum/(double)n)) << std::endl;
// 			
// 			if(!(-32+49<= i && i < 32+49)){
// 				
// 				std::cerr << "Mean 1: " << pm.GetTriggerTowerMean(pm.itofEta(i),pm.itofPhi(j),FCAL2) << std::endl;
// 				std::cerr << "  Sigma 1: " << pm.GetTriggerTowerSigma(pm.itofEta(i),pm.itofPhi(j),FCAL2) << std::endl;
// 				
// 				std::cerr << " Mean 2: " << pm.GetTriggerTowerMean(pm.itofEta(i),pm.itofPhi(j),FCAL3) << std::endl;
// 				std::cerr << "   Sigma 2: " << pm.GetTriggerTowerSigma(pm.itofEta(i),pm.itofPhi(j),FCAL3) << std::endl;
// 				
// 			}
// 			else{
// 				std::cerr << "Mean: " << pm.GetTriggerTowerMean(pm.itofEta(i),pm.itofPhi(j)) << std::endl;
// 				std::cerr << "  Sigma: " << pm.GetTriggerTowerSigma(pm.itofEta(i),pm.itofPhi(j)) << std::endl;
// 				
// 			}
//  			
			
		}
		/*
		for(int j=-49+49;j<-32+49;j++)
			pm->SetTriggerTower(pm->itofEta(j),pm->itofPhi(i),j+1,FCAL2);
		for(int j=-49+49;j<-32+49;j++)
			pm->SetTriggerTower(pm->itofEta(j),pm->itofPhi(i),j+1,FCAL3);
		for(int j=-32 + 49;j<32+49;j++)
			pm->SetTriggerTower(pm->itofEta(j),pm->itofPhi(i),j+1);
		for(int j=32+49;j<49+49;j++)
			pm->SetTriggerTower(pm->itofEta(j),pm->itofPhi(i),j+1,FCAL2);
		for(int j=32+49;j<49+49;j++)
			pm->SetTriggerTower(pm->itofEta(j),pm->itofPhi(i),j+1,FCAL3);
		*/
		
		histo.clear();
		char title[100];
		sprintf(title,"#eta vs #phi for %i Mean;#eta;#phi",i);
		histo.push_back(new TH2D("histo_1",title,L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2.0*pm.GetPI()));
		sprintf(title,"#eta vs #phi for %i Sigma;#eta;#phi",i);
		histo.push_back(new TH2D("histo_2",title,L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2.0*pm.GetPI()));
		
		pm.FillEtaPhiHistograms(histo);
		
		histo[0]->SetContour(64);
		histo[1]->SetContour(64);
		
		canvas->cd(1);
		histo[0]->Draw("colz");
		canvas->cd(2);
		histo[1]->Draw("colz");
		
		if(i==0)
			canvas->SaveAs("canvas.ps(");
		else if(i==L1CALO_ETA_TT-1)
			canvas->SaveAs("canvas.ps)");
		else
			canvas->SaveAs("canvas.ps");
		
		histo[0]->Delete();
		histo[1]->Delete();
		
// 		std::cin.get();
		
	}
	
	
	return 0;
}


