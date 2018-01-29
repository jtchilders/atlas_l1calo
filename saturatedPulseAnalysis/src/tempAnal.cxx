
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TTree.h"
#include "TProfile.h"
#include "TH1F.h"
#include "TF1.h"
#include "TApplication.h"

#include "L1CaloChannelMap.h"
#include "SatBcidTree.h"
#include "PixelMap.h"

int main(int argc, char** argv){
   
   
   /// Setup the gStyle environment
   #include "gStyleSetup.h"
   
   std::string filename = argv[1];
   
   TApplication app("app",&argc,argv);
   
   L1CaloChannelMap map;
   map.SetPpmEnable(true);
   map.SetCpmEnable(false);
   map.SetJemEnable(false);
   
   TCanvas can("can","can",0,0,800,600);
   
   PixelMap<float> pm_em_slopeSigma(PixelMap<float>::TrigTower);
   PixelMap<float> pm_had_slopeSigma(PixelMap<float>::TrigTower);
   
   
   TH1F em_slopeSigma("em_slopeSigma","EM Slope Sigma;sigma",1000,0.,1.);
   TH1F had_slopeSigma("had_slopeSigma","HAD Slope Sigma;sigma",1000,0.,1.);
   
   SatBcidTree tree;
   tree.SetReadMode();
   tree.OpenFile(filename);
   
   for(int i=0;i<tree.GetEntries();++i){
      tree.GetEntry(i);
      
      if(!tree.GetIsEnabled()) continue;
      if(!tree.GetIsValid()) continue;
      
      const unsigned int id = tree.GetCoolId();
      map.SetPpmChannelID(id);
      CaloDivision region = map.GetDetectorRegion();
      float eta = map.GetEta();
      float phi = map.GetPhi();
      bool  isEM = region.IsEM();
      bool isHAD = region.IsHAD();
      FcalLayer fcal = map.GetPpmFcalLayer()->at(0);
      
      if(isEM){
         pm_em_slopeSigma.SetTriggerTower(eta,phi,tree.GetRawDacVsAdcSlopeSigma(),fcal);
         em_slopeSigma.Fill(tree.GetRawDacVsAdcSlopeSigma());
      }
      else if(isHAD){
         pm_had_slopeSigma.SetTriggerTower(eta,phi,tree.GetRawDacVsAdcSlopeSigma(),fcal);
         had_slopeSigma.Fill(tree.GetRawDacVsAdcSlopeSigma());
      }
      
      if(tree.GetProcessedDacVsAdcSlopeSigma() > 0.07){
         can.cd();
         tree.GetProcessedDacVsAdcPeakGraph()->Draw("ap");
         tree.GetProcessedDacVsAdcPeakFit()->Draw("same");
         can.Update();
         std::cout << "   id: " << map.GetPpmChannelID()->at(0).GetIdAsString() << "  slope sigma: " << tree.GetProcessedDacVsAdcSlopeSigma() << " rawSatLvl: " << tree.GetProcessedSatLevel() << std::endl;
         std::cin.get();
      }
   }
   
   TH2F* hpm_em_slopeSigma = (TH2F*)pm_em_slopeSigma.GetEtaPhiHistogram("em_slopeSigma","EM Slope Sigma;#eta;#phi");
   TH2F* hpm_had_slopeSigma = (TH2F*)pm_had_slopeSigma.GetEtaPhiHistogram("had_slopeSigma","HAD Slope Sigma;#eta;#phi");
   
   
   
   can.Divide(2,2);
   can.cd(1);
   hpm_em_slopeSigma->Draw("colz");
   can.cd(2);
   em_slopeSigma.Draw();
   can.cd(3);
   hpm_had_slopeSigma->Draw("colz");
   can.cd(4);
   had_slopeSigma.Draw();
   
   app.Run();
   
}


