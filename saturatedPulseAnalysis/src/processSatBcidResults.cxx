
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "tclap/CmdLine.h"

#include "SatBcidTree.h"
#include "SatBcidTreeFiller.h"
#include "CaloDivision.h"
#include "FcalLayer.h"
#include "L1CaloChannelMap.h"
#include "PixelMap.h"

#include "TApplication.h"
#include "TStyle.h"
#include "TH1I.h"
#include "TCanvas.h"
#include "TPaveText.h"

int main(int argc, char** argv){
   
   
   #include "gStyleSetup.h"
   
   TH1::AddDirectory(false);
   
   std::string inputFilename;
   try{
      // Define the command line object.
      TCLAP::CmdLine cmd("Review SatBcid output root file, flag bad results, fill empty trigger towers, and produce final plots and database file.", ' ', "0.1");
      
      TCLAP::ValueArg<std::string> inputFileList("f","file","ROOT file with SatBcidTree.",true,"","string");
      cmd.add(inputFileList);
      
      cmd.parse(argc,argv);
      
      inputFilename = inputFileList.getValue();
      
   } catch (TCLAP::ArgException &e)  // catch any exceptions
   { std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl; }
   
   
//    TApplication app("app",&argc,argv);
   
   /// Extract Tree from file
   TFile *file = new TFile(inputFilename.c_str(),"READ");
   SatBcidTree *tree = new SatBcidTree;
   tree->SetReadMode();
   tree->OpenFile(file);
   
   /// Extract Mean satBcid register values from
   /// summary plots
   
   std::vector<float> satHighMean;
   std::vector<float> satHighSigma;
   
   std::vector<float> satLowMean;
   std::vector<float> satLowSigma;
   
   std::vector<float> satLvlMean;
   std::vector<float> satLvlSigma;
   
   std::string summaryDir = "Summary";
   for(unsigned int i=0;i<CaloDivision::NUM_DIVISIONS;++i){
      CaloDivision div((CaloDivision::CaloDivisionEnum)i);
      file->cd(summaryDir.c_str());
      gDirectory->cd(div.GetString().c_str());
      
      std::string satHighHistoName = "satHigh_" + div.GetString();
      std::string satLowHistoName = "satLow_" + div.GetString();
      std::string satLvlHistoName = "satLvl_" + div.GetString();
      
      TH1I *h_satHigh = (TH1I*)gDirectory->Get(satHighHistoName.c_str());
      TH1I *h_satLow  = (TH1I*)gDirectory->Get(satLowHistoName.c_str());
      TH1I *h_satLvl  = (TH1I*)gDirectory->Get(satLvlHistoName.c_str());
      
      satHighMean.push_back(h_satHigh->GetMean());
      satHighSigma.push_back(h_satHigh->GetRMS());
      
      satLowMean.push_back(h_satLow->GetMean());
      satLowSigma.push_back(h_satLow->GetRMS());
      
      satLvlMean.push_back(h_satLvl->GetMean());
      satLvlSigma.push_back(h_satLvl->GetRMS());
   }
   
   /// Now loop over tree and find channels with outliers
   
   L1CaloChannelMap *l1map = new L1CaloChannelMap;
   l1map->SetCpmEnable(false);
   l1map->SetJemEnable(false);
   l1map->SetTcppEnable(false);
   
   const unsigned int sigmaFactor = 3;
   std::vector<unsigned int> satHighOutlier;
   std::vector<unsigned int> satLowOutlier;
   std::vector<unsigned int> satLvlOutlier;
   
   PixelMap<unsigned int> *pm_em_satHighOutliers = new PixelMap<unsigned int>(PixelMap<unsigned int>::TrigTower);
   PixelMap<unsigned int> *pm_em_satLowOutliers = new PixelMap<unsigned int>(PixelMap<unsigned int>::TrigTower);
   PixelMap<unsigned int> *pm_em_satLvlOutliers = new PixelMap<unsigned int>(PixelMap<unsigned int>::TrigTower);
   PixelMap<unsigned int> *pm_had_satHighOutliers = new PixelMap<unsigned int>(PixelMap<unsigned int>::TrigTower);
   PixelMap<unsigned int> *pm_had_satLowOutliers = new PixelMap<unsigned int>(PixelMap<unsigned int>::TrigTower);
   PixelMap<unsigned int> *pm_had_satLvlOutliers = new PixelMap<unsigned int>(PixelMap<unsigned int>::TrigTower);
   
   // output file for satLow,satHigh,satLevel values
   std::ofstream satInfoFile("satSetting.txt");
   
   
   for(unsigned entry=0;entry<tree->GetEntries();++entry){
      tree->GetEntry(entry);
      
      l1map->SetPpmChannelID(tree->GetCoolId());
      CaloDivision region = l1map->GetDetectorRegion();
      
      
      int satHigh = (int)tree->GetSatHigh();
      int satLow  = (int)tree->GetSatLow();
      int satLvl  = (int)tree->GetSatLevel();
      
      int satHighMax = (unsigned int)(satHighMean[(int)region.GetDivision()] +
            (float)sigmaFactor*satHighSigma[(int)region.GetDivision()]);
      int satHighMin = (unsigned int)(satHighMean[(int)region.GetDivision()] -
            (float)sigmaFactor*satHighSigma[(int)region.GetDivision()]);
      
      // output sat info
      satInfoFile <<  std::hex << tree->GetCoolId() << std::dec << " " << tree->GetSatLow() << " " << tree->GetSatHigh() << " " << tree->GetSatLevel() << std::endl;
      
      if(!(satHighMin <= satHigh && satHigh <= satHighMax)){
         if(satHigh != 0)
            satHighOutlier.push_back(tree->GetCoolId());
         if(region.IsEM()){
            if(satHigh == 0)
               pm_em_satHighOutliers->SetTriggerTower(l1map->GetEta(),l1map->GetPhi(),1);
            else
               pm_em_satHighOutliers->SetTriggerTower(l1map->GetEta(),l1map->GetPhi(),2);
         }
         else if(region.IsHAD()){
            if(region.IsLArFCAL23C() || region.IsLArFCAL23A()){
               FcalLayer fcal = l1map->GetPpmFcalLayer()->at(0);
               if(satHigh == 0)
                  pm_had_satHighOutliers->SetTriggerTower(l1map->GetEta(),l1map->GetPhi(),1,fcal);
               else
                  pm_had_satHighOutliers->SetTriggerTower(l1map->GetEta(),l1map->GetPhi(),2,fcal);
            }
            else{
               if(satHigh == 0)
                  pm_had_satHighOutliers->SetTriggerTower(l1map->GetEta(),l1map->GetPhi(),1);
               else
                  pm_had_satHighOutliers->SetTriggerTower(l1map->GetEta(),l1map->GetPhi(),2);
            }
         }
      }
      
      int satLowMax = (unsigned int)(satLowMean[(int)region.GetDivision()] +
            (float)sigmaFactor*satLowSigma[(int)region.GetDivision()]);
      int satLowMin = (unsigned int)(satLowMean[(int)region.GetDivision()] -
            (float)sigmaFactor*satLowSigma[(int)region.GetDivision()]);
      
      if(!(satLowMin <= satLow && satLow <= satLowMax)){
         if(satLow != 0)
            satLowOutlier.push_back(tree->GetCoolId());
         if(region.IsEM()){
            if(satLow == 0)
               pm_em_satLowOutliers->SetTriggerTower(l1map->GetEta(),l1map->GetPhi(),1);
            else
               pm_em_satLowOutliers->SetTriggerTower(l1map->GetEta(),l1map->GetPhi(),2);
         }
         else if(region.IsHAD()){
            if(region.IsLArFCAL23C() || region.IsLArFCAL23A()){
               FcalLayer fcal = l1map->GetPpmFcalLayer()->at(0);
               if(satLow == 0)
                  pm_had_satLowOutliers->SetTriggerTower(l1map->GetEta(),l1map->GetPhi(),1,fcal);
               else
                  pm_had_satLowOutliers->SetTriggerTower(l1map->GetEta(),l1map->GetPhi(),2,fcal);
            }
            else{
               if(satLow == 0)
                  pm_had_satLowOutliers->SetTriggerTower(l1map->GetEta(),l1map->GetPhi(),1);
               else
                  pm_had_satLowOutliers->SetTriggerTower(l1map->GetEta(),l1map->GetPhi(),2);
            }
         }
      }
      
      int satLvlMax = (unsigned int)(satLvlMean[(int)region.GetDivision()] +
            (float)sigmaFactor*satLvlSigma[(int)region.GetDivision()]);
      int satLvlMin = (unsigned int)(satLvlMean[(int)region.GetDivision()] -
            (float)sigmaFactor*satLvlSigma[(int)region.GetDivision()]);
      
      if(!(satLvlMin <= satLvl && satLvl <= satLvlMax)){
         if(satLow != 0)
            satLvlOutlier.push_back(tree->GetCoolId());
         if(region.IsEM()){
            if(satLow == 0)
               pm_em_satLvlOutliers->SetTriggerTower(l1map->GetEta(),l1map->GetPhi(),1);
            else
               pm_em_satLvlOutliers->SetTriggerTower(l1map->GetEta(),l1map->GetPhi(),2);
         }
         else if(region.IsHAD()){
            if(region.IsLArFCAL23C() || region.IsLArFCAL23A()){
               FcalLayer fcal = l1map->GetPpmFcalLayer()->at(0);
               if(satLow == 0)
                  pm_had_satLvlOutliers->SetTriggerTower(l1map->GetEta(),l1map->GetPhi(),1,fcal);
               else
                  pm_had_satLvlOutliers->SetTriggerTower(l1map->GetEta(),l1map->GetPhi(),2,fcal);
            }
            else{
               if(satLow == 0)
                  pm_had_satLvlOutliers->SetTriggerTower(l1map->GetEta(),l1map->GetPhi(),1);
               else
                  pm_had_satLvlOutliers->SetTriggerTower(l1map->GetEta(),l1map->GetPhi(),2);
            }
         }
      }
      
   }//end for(tree)
   
   // close satinfo file
   satInfoFile.close();
   
   TCanvas *estAdcVsTs1Plots = new TCanvas("estAdcVsTs1Plots","estAdcVsTs1 Plots",0,0,800,600);
   TCanvas *estAdcVsTs2Plots = new TCanvas("estAdcVsTs2Plots","estAdcVsTs2 Plots",0,0,800,600);
   TCanvas *dacVsAdcPeakPlots = new TCanvas("dacVsAdcPeakPlots","dacVsAdcPeak Plots",0,0,800,600);
   TCanvas *diagnoseOutliersRaw = new TCanvas("diagnoseOutliersRaw","diagnoseOutliersRaw Plots",0,0,800,600);
   TCanvas *diagnoseOutliersProcessed = new TCanvas("diagnoseOutliersProcessed","diagnoseOutliersProcessed Plots",0,0,800,600);
   
   // Add outlier plots as the first 2 pages
   // for SatHigh
   estAdcVsTs1Plots->cd();
   TH2* em_satHighOutliers = pm_em_satHighOutliers->GetEtaPhiHistogram("em_satHighOutliers","(EM) SatHigh outliers");
   em_satHighOutliers->Draw("colz");
   estAdcVsTs1Plots->SaveAs("estAdcVsTs1Plots.ps(");
   TH2* had_satHighOutliers = pm_had_satHighOutliers->GetEtaPhiHistogram("had_satHighOutliers","(HAD) SatHigh outliers");
   had_satHighOutliers->Draw("colz");
   estAdcVsTs1Plots->SaveAs("estAdcVsTs1Plots.ps");
   
   // for SatLow
   estAdcVsTs2Plots->cd();
   TH2* em_satLowOutliers = pm_em_satLowOutliers->GetEtaPhiHistogram("em_satLowOutliers","(EM) SatLow outliers");
   em_satLowOutliers->Draw("colz");
   estAdcVsTs2Plots->SaveAs("estAdcVsTs2Plots.ps(");
   TH2* had_satLowOutliers = pm_had_satLowOutliers->GetEtaPhiHistogram("had_satLowOutliers","(HAD) SatLow outliers");
   had_satLowOutliers->Draw("colz");
   estAdcVsTs2Plots->SaveAs("estAdcVsTs2Plots.ps");
   
   // for SatLvl
   dacVsAdcPeakPlots->cd();
   TH2* em_satLvlOutliers = pm_em_satLvlOutliers->GetEtaPhiHistogram("em_satLvlOutliers","(EM) SatLevel outliers");
   em_satLvlOutliers->Draw("colz");
   dacVsAdcPeakPlots->SaveAs("dacVsAdcPeakPlots.ps(");
   TH2* had_satLvlOutliers = pm_had_satLvlOutliers->GetEtaPhiHistogram("em_satLvlOutliers","(EM) SatLevel outliers");
   had_satLvlOutliers->Draw("colz");
   dacVsAdcPeakPlots->SaveAs("dacVsAdcPeakPlots.ps");
   
   // for all
   diagnoseOutliersRaw->Divide(2,3);
   diagnoseOutliersRaw->cd(1);
   em_satHighOutliers->Draw("colz");
   diagnoseOutliersRaw->cd(2);
   had_satHighOutliers->Draw("colz");
   diagnoseOutliersRaw->cd(3);
   em_satLowOutliers->Draw("colz");
   diagnoseOutliersRaw->cd(4);
   had_satLowOutliers->Draw("colz");
   diagnoseOutliersRaw->cd(5);
   em_satLvlOutliers->Draw("colz");
   diagnoseOutliersRaw->cd(6);
   had_satLvlOutliers->Draw("colz");
   diagnoseOutliersRaw->SaveAs("diagnoseOutliersRaw.ps(");
   
   diagnoseOutliersProcessed->Divide(2,3);
   diagnoseOutliersProcessed->cd(1);
   em_satHighOutliers->Draw("colz");
   diagnoseOutliersProcessed->cd(2);
   had_satHighOutliers->Draw("colz");
   diagnoseOutliersProcessed->cd(3);
   em_satLowOutliers->Draw("colz");
   diagnoseOutliersProcessed->cd(4);
   had_satLowOutliers->Draw("colz");
   diagnoseOutliersProcessed->cd(5);
   em_satLvlOutliers->Draw("colz");
   diagnoseOutliersProcessed->cd(6);
   had_satLvlOutliers->Draw("colz");
   diagnoseOutliersProcessed->SaveAs("diagnoseOutliersProcessed.ps(");
   
   // Now fill each plot on a per channel basis
   for(unsigned int crate=0;crate<6;++crate){
      for(unsigned int module=0;module<16;++module){
         std::cout << " crate: " << crate << " module: " <<  module << std::endl;
         estAdcVsTs1Plots->Clear();
         estAdcVsTs1Plots->Divide(8,8);
         estAdcVsTs2Plots->Clear();
         estAdcVsTs2Plots->Divide(8,8);
         dacVsAdcPeakPlots->Clear();
         dacVsAdcPeakPlots->Divide(8,8);
         
         for(unsigned int submodule=0;submodule<16;++submodule){
            for(unsigned int channel=0;channel<4;++channel){
               L1CaloChannelId id(L1CaloChannelId::PPM,crate,module,submodule,channel);
               
               unsigned int padNum = submodule*4 + channel + 1;
               
               l1map->SetPpmChannelID(id);
//                CaloDivision div = l1mpa->GetDetectorRegion();
//                if(div.IsTile()) continue;
               
               if(!l1map->IsPpmChannelUsed()){
                  estAdcVsTs1Plots->cd(padNum);
                  TPaveText text(0.05,0.95,0.95,0.05,"NDC");
                  text.SetShadowColor(kWhite);
                  text.AddText(id.GetIdAsString().c_str());
                  text.AddText("Unused");
                  text.DrawClone();
                  estAdcVsTs2Plots->cd(padNum);
                  text.DrawClone();
                  dacVsAdcPeakPlots->cd(padNum);
                  text.DrawClone();
                  
                  continue;
               }
               
               // find tree entry for this channel
               const unsigned int entry = tree->FindEntry(id);
               if(entry == 0 && id.GetId() != 0x00100000){
                  estAdcVsTs1Plots->cd(padNum);
                  TPaveText text(0.05,0.95,0.95,0.05,"NDC");
                  text.SetShadowColor(kWhite);
                  text.AddText(id.GetIdAsString().c_str());
                  text.AddText("Not Found");
                  text.DrawClone();
                  estAdcVsTs2Plots->cd(padNum);
                  text.DrawClone();
                  dacVsAdcPeakPlots->cd(padNum);
                  text.DrawClone();
                  
                  continue;
               }
               
               // set pad
               estAdcVsTs1Plots->cd(padNum);
               // draw estAdcVsTs1Plot in pad
               if(tree->GetProcessedPeakVsTs1Graph()->GetN() > 0){
                  
                  // check to see if this channel was an outlier
                  for(unsigned int i=0;i<satHighOutlier.size();++i){
                     if(satHighOutlier[i] == id.GetId()){
                        estAdcVsTs1Plots->cd(padNum)->SetFillColor(kYellow);
                        break;
                     }
                  }
                  
                  tree->GetProcessedPeakVsTs1Graph()->Draw("ap");
                  tree->GetProcessedPeakVsTs1Fit()->Draw("same");
               }
               else{
                  TPaveText text(0.05,0.95,0.95,0.05,"NDC");
                  text.SetShadowColor(kWhite);
                  text.AddText(id.GetIdAsString().c_str());
                  text.AddText("Empty");
                  text.DrawClone();
               }
               
               // set pad
               estAdcVsTs2Plots->cd(padNum);
               // draw estAdcVsTs1Plot in pad
               if(tree->GetProcessedPeakVsTs2Graph()->GetN() > 0){
                  tree->GetProcessedPeakVsTs2Graph()->Draw("ap");
                  tree->GetProcessedPeakVsTs2Fit()->Draw("same");
               }
               else{
                  TPaveText text(0.05,0.95,0.95,0.05,"NDC");
                  text.SetShadowColor(kWhite);
                  text.AddText(id.GetIdAsString().c_str());
                  text.AddText("Empty");
                  text.DrawClone();
               }
               
               // set pad
               dacVsAdcPeakPlots->cd(padNum);
               // draw estAdcVsTs1Plot in pad
               if(tree->GetProcessedDacVsAdcPeakGraph()->GetN() > 0){
                  tree->GetProcessedDacVsAdcPeakGraph()->Draw("ap");
                  tree->GetProcessedDacVsAdcPeakFit()->Draw("same");
               }
               else{
                  TPaveText text(0.05,0.95,0.95,0.05,"NDC");
                  text.SetShadowColor(kWhite);
                  text.AddText(id.GetIdAsString().c_str());
                  text.AddText("Empty");
                  text.DrawClone();
               }
               
            }// end for(channel)
         }// end for(submodule)
         
         estAdcVsTs1Plots->SaveAs("estAdcVsTs1Plots.ps");
         estAdcVsTs2Plots->SaveAs("estAdcVsTs2Plots.ps");
         dacVsAdcPeakPlots->SaveAs("dacVsAdcPeakPlots.ps");
         
      }// end for(module)
   }// end for(crate)
   
   // Then add the outliers at the end of each file
   
   diagnoseOutliersRaw->Clear();
   diagnoseOutliersRaw->Divide(4,4);
   diagnoseOutliersProcessed->Clear();
   diagnoseOutliersProcessed->Divide(4,4);
   
   estAdcVsTs1Plots->Clear();
   estAdcVsTs1Plots->Divide(4,4);
   
   std::cout << "satHighOutlier: " << satHighOutlier.size() << std::endl;
   for(unsigned int i=0;i<satHighOutlier.size();++i){
      
      unsigned int padNum = (i % 16) + 1;
      
      if(padNum == 1 && i > 0){
         estAdcVsTs1Plots->SaveAs("estAdcVsTs1Plots.ps");
         estAdcVsTs1Plots->Clear();
         estAdcVsTs1Plots->Divide(4,4);
      }
      
      L1CaloChannelId id(satHighOutlier[i]);
      tree->FindEntry(id);
      
      l1map->SetPpmChannelID(id);
      CaloDivision region = l1map->GetDetectorRegion();
      
      estAdcVsTs1Plots->cd(padNum);
      tree->GetProcessedPeakVsTs1Graph()->Draw("ap");
      tree->GetProcessedPeakVsTs1Fit()->Draw("same");
      
      //////////////////////////
      // fill diagnosis plots
      
      unsigned int padNum2 = (i % 4)*4 + 1;
      
      if(padNum2 == 1 && i > 0){
         diagnoseOutliersRaw->SaveAs("diagnoseOutliersRaw.ps");
         diagnoseOutliersRaw->Clear();
         diagnoseOutliersRaw->Divide(4,4);
         diagnoseOutliersProcessed->SaveAs("diagnoseOutliersProcessed.ps");
         diagnoseOutliersProcessed->Clear();
         diagnoseOutliersProcessed->Divide(4,4);
      }
      
      // would like to fill signal shapes to first pad
      // for raw
      file->cd();
      file->cd("combinedRawCanvas");
      gDirectory->cd(region.GetString().c_str());
      std::string canvasName = "rawCanvas_" + id.GetIdAsString();
      TCanvas *can = (TCanvas*)gDirectory->Get(canvasName.c_str());
      TList *list = can->GetListOfPrimitives();
      diagnoseOutliersRaw->cd(padNum2);
      for(unsigned int entry=0;entry<list->GetEntries();++entry){
         TH1F* hist = (TH1F*)list->At(entry);
         hist->SetMarkerSize(.4);
         if(entry == 0)
            hist->Draw();
         else 
            hist->Draw("same");
      }
      
      // for processed
      file->cd();
      file->cd("combinedProcessedCanvas");
      gDirectory->cd(region.GetString().c_str());
      canvasName = "processedCanvas_" + id.GetIdAsString();
      can = (TCanvas*)gDirectory->Get(canvasName.c_str());
      list = can->GetListOfPrimitives();
      diagnoseOutliersProcessed->cd(padNum2);
      for(unsigned int entry=0;entry<list->GetEntries();++entry){
         TH1F* hist = (TH1F*)list->At(entry);
         hist->SetMarkerSize(.4);
         if(entry == 0)
            hist->Draw();
         else 
            hist->Draw("same");
      }
      
      // now the dac vs adcPeak
      padNum2++;
      
      // for raw
      diagnoseOutliersRaw->cd(padNum2);
      tree->GetRawDacVsAdcPeakGraph()->Draw("ap");
      tree->GetRawDacVsAdcPeakFit()->Draw("same");
      // draw satLvl
      TF1 lineRawSatLvl("lineRawSatLvl","pol1",0,10000);
      lineRawSatLvl.SetParameter(1,0);
      lineRawSatLvl.SetParameter(0,tree->GetRawSatLevel());
      lineRawSatLvl.SetLineColor(kRed);
      lineRawSatLvl.DrawCopy("same");
      // draw satLow
      TF1 lineRawSatLow("lineRawSatLow","pol1",0,10000);
      lineRawSatLow.SetParameter(1,0);
      lineRawSatLow.SetParameter(0,tree->GetRawSatLow());
      lineRawSatLow.SetLineColor(kGreen);
      lineRawSatLow.DrawCopy("same");
      // draw satLow
      TF1 lineRawSatHigh("lineRawSatHigh","pol1",0,10000);
      lineRawSatHigh.SetParameter(1,0);
      lineRawSatHigh.SetParameter(0,tree->GetRawSatHigh());
      lineRawSatHigh.SetLineColor(kBlue);
      lineRawSatHigh.DrawCopy("same");
      
      
      // for processed
      diagnoseOutliersProcessed->cd(padNum2);
      tree->GetProcessedDacVsAdcPeakGraph()->Draw("ap");
      tree->GetProcessedDacVsAdcPeakFit()->Draw("same");
      // draw satLvl
      TF1 lineProcessedSatLvl("lineProcessedSatLvl","pol1",0,10000);
      lineProcessedSatLvl.SetParameter(1,0);
      lineProcessedSatLvl.SetParameter(0,tree->GetProcessedSatLevel());
      lineProcessedSatLvl.SetLineColor(kRed);
      lineProcessedSatLvl.DrawCopy("same");
      // draw satLow
      TF1 lineProcessedSatLow("lineProcessedSatLow","pol1",0,10000);
      lineProcessedSatLow.SetParameter(1,0);
      lineProcessedSatLow.SetParameter(0,tree->GetProcessedSatLow());
      lineProcessedSatLow.SetLineColor(kGreen);
      lineProcessedSatLow.DrawCopy("same");
      // draw satLow
      TF1 lineProcessedSatHigh("lineProcessedSatHigh","pol1",0,10000);
      lineProcessedSatHigh.SetParameter(1,0);
      lineProcessedSatHigh.SetParameter(0,tree->GetProcessedSatHigh());
      lineProcessedSatHigh.SetLineColor(kBlue);
      lineProcessedSatHigh.DrawCopy("same");
      
      // now the estimate peak vs ts-1
      padNum2++;
      
      // for raw
      diagnoseOutliersRaw->cd(padNum2);
      tree->GetRawPeakVsTs1Graph()->Draw("ap");
      tree->GetRawPeakVsTs1Fit()->Draw("same");
      // draw satLvl
      lineRawSatLvl.DrawCopy("same");
      // draw satLow
      lineRawSatLow.DrawCopy("same");
      // draw satLow
      lineRawSatHigh.DrawCopy("same");
      
      
      // for processed
      diagnoseOutliersProcessed->cd(padNum2);
      tree->GetProcessedPeakVsTs1Graph()->Draw("ap");
      tree->GetProcessedPeakVsTs1Fit()->Draw("same");
      // draw satLvl
      lineProcessedSatLvl.DrawCopy("same");
      // draw satLow
      lineProcessedSatLow.DrawCopy("same");
      // draw satLow
      lineProcessedSatHigh.DrawCopy("same");
      
      
      // now the estimate peak vs ts-2
      padNum2++;
      
      // for raw
      diagnoseOutliersRaw->cd(padNum2);
      tree->GetRawPeakVsTs2Graph()->Draw("ap");
      tree->GetRawPeakVsTs2Fit()->Draw("same");
      // draw satLvl
      lineRawSatLvl.DrawCopy("same");
      // draw satLow
      lineRawSatLow.DrawCopy("same");
      // draw satLow
      lineRawSatHigh.DrawCopy("same");
      
      // for processed
      diagnoseOutliersProcessed->cd(padNum2);
      tree->GetProcessedPeakVsTs2Graph()->Draw("ap");
      tree->GetProcessedPeakVsTs2Fit()->Draw("same");
      // draw satLvl
      lineProcessedSatLvl.DrawCopy("same");
      // draw satLow
      lineProcessedSatLow.DrawCopy("same");
      // draw satLow
      lineProcessedSatHigh.DrawCopy("same");
      
      
   }
   estAdcVsTs1Plots->SaveAs("estAdcVsTs1Plots.ps)");
   diagnoseOutliersRaw->SaveAs("diagnoseOutliersRaw.ps");
   diagnoseOutliersProcessed->SaveAs("diagnoseOutliersProcessed.ps");
   
   diagnoseOutliersRaw->Clear();
   diagnoseOutliersRaw->Divide(4,4);
   diagnoseOutliersProcessed->Clear();
   diagnoseOutliersProcessed->Divide(4,4);
   
   estAdcVsTs2Plots->Clear();
   estAdcVsTs2Plots->Divide(4,4);
   
   std::cout << "satLowOutlier: " << satLowOutlier.size() << std::endl;
   unsigned int padNum2 = 0;
   for(unsigned int i=0;i<satLowOutlier.size();++i){
      
      unsigned int padNum = (i % 16) + 1;
      
      if(padNum == 1 && i > 0){
         estAdcVsTs2Plots->SaveAs("estAdcVsTs2Plots.ps");
         estAdcVsTs2Plots->Clear();
         estAdcVsTs2Plots->Divide(4,4);
      }
      
      L1CaloChannelId id(satLowOutlier[i]);
      tree->FindEntry(id);
      
      l1map->SetPpmChannelID(id);
      CaloDivision region = l1map->GetDetectorRegion();
      
      estAdcVsTs2Plots->cd(padNum);
      tree->GetProcessedPeakVsTs2Graph()->Draw("ap");
      tree->GetProcessedPeakVsTs2Fit()->Draw("same");
      
      //////////////////////////
      // fill diagnosis plots
      
      
      // don't include duplicates
      bool skipChannel = false;
      for(unsigned int k=0;k<satHighOutlier.size() && !skipChannel;++k){
         if(satHighOutlier[k] == satLowOutlier[i]){
            skipChannel = true;
            break;
         }
      }
      if(skipChannel) continue;
      
      if(padNum2 == 16)
         padNum2 = 1;
      else
         padNum2++;
      
      if(padNum2 == 1 && i > 0){
         diagnoseOutliersRaw->SaveAs("diagnoseOutliersRaw.ps");
         diagnoseOutliersRaw->Clear();
         diagnoseOutliersRaw->Divide(4,4);
         diagnoseOutliersProcessed->SaveAs("diagnoseOutliersProcessed.ps");
         diagnoseOutliersProcessed->Clear();
         diagnoseOutliersProcessed->Divide(4,4);
      }
      
      // would like to fill signal shapes to first pad
      // for raw
      file->cd();
      file->cd("combinedRawCanvas");
      gDirectory->cd(region.GetString().c_str());
      std::string canvasName = "rawCanvas_" + id.GetIdAsString();
      TCanvas *can = (TCanvas*)gDirectory->Get(canvasName.c_str());
      TList *list = can->GetListOfPrimitives();
      diagnoseOutliersRaw->cd(padNum2);
      for(unsigned int entry=0;entry<list->GetEntries();++entry){
         TH1F* hist = (TH1F*)list->At(entry);
         hist->SetMarkerSize(.4);
         if(entry == 0)
            hist->Draw();
         else 
            hist->Draw("same");
      }
      
      // for processed
      file->cd();
      file->cd("combinedProcessedCanvas");
      gDirectory->cd(region.GetString().c_str());
      canvasName = "processedCanvas_" + id.GetIdAsString();
      can = (TCanvas*)gDirectory->Get(canvasName.c_str());
      list = can->GetListOfPrimitives();
      diagnoseOutliersProcessed->cd(padNum2);
      for(unsigned int entry=0;entry<list->GetEntries();++entry){
         TH1F* hist = (TH1F*)list->At(entry);
         hist->SetMarkerSize(.4);
         if(entry == 0)
            hist->Draw();
         else 
            hist->Draw("same");
      }
      
      // now the dac vs adcPeak
      padNum2++;
      
      // for raw
      diagnoseOutliersRaw->cd(padNum2);
      tree->GetRawDacVsAdcPeakGraph()->Draw("ap");
      tree->GetRawDacVsAdcPeakFit()->Draw("same");
      // draw satLvl
      TF1 lineRawSatLvl("lineRawSatLvl","pol1",0,10000);
      lineRawSatLvl.SetParameter(1,0);
      lineRawSatLvl.SetParameter(0,tree->GetRawSatLevel());
      lineRawSatLvl.SetLineColor(kRed);
      lineRawSatLvl.DrawCopy("same");
      // draw satLow
      TF1 lineRawSatLow("lineRawSatLow","pol1",0,10000);
      lineRawSatLow.SetParameter(1,0);
      lineRawSatLow.SetParameter(0,tree->GetRawSatLow());
      lineRawSatLow.SetLineColor(kGreen);
      lineRawSatLow.DrawCopy("same");
      // draw satLow
      TF1 lineRawSatHigh("lineRawSatHigh","pol1",0,10000);
      lineRawSatHigh.SetParameter(1,0);
      lineRawSatHigh.SetParameter(0,tree->GetRawSatHigh());
      lineRawSatHigh.SetLineColor(kBlue);
      lineRawSatHigh.DrawCopy("same");
      
      
      // for processed
      diagnoseOutliersProcessed->cd(padNum2);
      tree->GetProcessedDacVsAdcPeakGraph()->Draw("ap");
      tree->GetProcessedDacVsAdcPeakFit()->Draw("same");
      // draw satLvl
      TF1 lineProcessedSatLvl("lineProcessedSatLvl","pol1",0,10000);
      lineProcessedSatLvl.SetParameter(1,0);
      lineProcessedSatLvl.SetParameter(0,tree->GetProcessedSatLevel());
      lineProcessedSatLvl.SetLineColor(kRed);
      lineProcessedSatLvl.DrawCopy("same");
      // draw satLow
      TF1 lineProcessedSatLow("lineProcessedSatLow","pol1",0,10000);
      lineProcessedSatLow.SetParameter(1,0);
      lineProcessedSatLow.SetParameter(0,tree->GetProcessedSatLow());
      lineProcessedSatLow.SetLineColor(kGreen);
      lineProcessedSatLow.DrawCopy("same");
      // draw satLow
      TF1 lineProcessedSatHigh("lineProcessedSatHigh","pol1",0,10000);
      lineProcessedSatHigh.SetParameter(1,0);
      lineProcessedSatHigh.SetParameter(0,tree->GetProcessedSatHigh());
      lineProcessedSatHigh.SetLineColor(kBlue);
      lineProcessedSatHigh.DrawCopy("same");
      
      // now the estimate peak vs ts-1
      padNum2++;
      
      // for raw
      diagnoseOutliersRaw->cd(padNum2);
      tree->GetRawPeakVsTs1Graph()->Draw("ap");
      tree->GetRawPeakVsTs1Fit()->Draw("same");
      // draw satLvl
      lineRawSatLvl.DrawCopy("same");
      // draw satLow
      lineRawSatLow.DrawCopy("same");
      // draw satLow
      lineRawSatHigh.DrawCopy("same");
      
      
      // for processed
      diagnoseOutliersProcessed->cd(padNum2);
      tree->GetProcessedPeakVsTs1Graph()->Draw("ap");
      tree->GetProcessedPeakVsTs1Fit()->Draw("same");
      // draw satLvl
      lineProcessedSatLvl.DrawCopy("same");
      // draw satLow
      lineProcessedSatLow.DrawCopy("same");
      // draw satLow
      lineProcessedSatHigh.DrawCopy("same");
      
      
      // now the estimate peak vs ts-2
      padNum2++;
      
      // for raw
      diagnoseOutliersRaw->cd(padNum2);
      tree->GetRawPeakVsTs2Graph()->Draw("ap");
      tree->GetRawPeakVsTs2Fit()->Draw("same");
      // draw satLvl
      lineRawSatLvl.DrawCopy("same");
      // draw satLow
      lineRawSatLow.DrawCopy("same");
      // draw satLow
      lineRawSatHigh.DrawCopy("same");
      
      // for processed
      diagnoseOutliersProcessed->cd(padNum2);
      tree->GetProcessedPeakVsTs2Graph()->Draw("ap");
      tree->GetProcessedPeakVsTs2Fit()->Draw("same");
      // draw satLvl
      lineProcessedSatLvl.DrawCopy("same");
      // draw satLow
      lineProcessedSatLow.DrawCopy("same");
      // draw satLow
      lineProcessedSatHigh.DrawCopy("same");
      
   }
   estAdcVsTs2Plots->SaveAs("estAdcVsTs2Plots.ps)");
   diagnoseOutliersRaw->SaveAs("diagnoseOutliersRaw.ps");
   diagnoseOutliersProcessed->SaveAs("diagnoseOutliersProcessed.ps");
   
   diagnoseOutliersRaw->Clear();
   diagnoseOutliersRaw->Divide(4,4);
   diagnoseOutliersProcessed->Clear();
   diagnoseOutliersProcessed->Divide(4,4);
   
   dacVsAdcPeakPlots->Clear();
   dacVsAdcPeakPlots->Divide(4,4);
   
   std::cout << "satLvlOutlier: " << satLvlOutlier.size() << std::endl;
   padNum2 = 0;
   for(unsigned int i=0;i<satLvlOutlier.size();++i){
      
      unsigned int padNum = (i % 16) + 1;
      
      if(padNum == 1 && i > 0){
         dacVsAdcPeakPlots->SaveAs("dacVsAdcPeakPlots.ps");
         dacVsAdcPeakPlots->Clear();
         dacVsAdcPeakPlots->Divide(4,4);
      }
      
      L1CaloChannelId id(satLvlOutlier[i]);
      tree->FindEntry(id);
      
      l1map->SetPpmChannelID(id);
      CaloDivision region = l1map->GetDetectorRegion();
      
      dacVsAdcPeakPlots->cd(padNum);
      tree->GetProcessedDacVsAdcPeakGraph()->Draw("ap");
      tree->GetProcessedDacVsAdcPeakFit()->Draw("same");
      
      //////////////////////////
      // fill diagnosis plots
      
      // don't include duplicates
      bool skipChannel = false;
      for(unsigned int k=0;k<satHighOutlier.size() && !skipChannel;++k){
         if(satHighOutlier[k] == satLvlOutlier[i]){
            skipChannel = true;
            break;
         }
      }
      for(unsigned int k=0;k<satLowOutlier.size() && !skipChannel;++k){
         if(satLowOutlier[k] == satLvlOutlier[i]){
            skipChannel = true;
            break;
         }
      }
      if(skipChannel) continue;
      
      if(padNum2 == 16)
         padNum2 = 1;
      else
         padNum2++;
      
      if(padNum == 1 && i > 0){
         diagnoseOutliersRaw->SaveAs("diagnoseOutliersRaw.ps");
         diagnoseOutliersRaw->Clear();
         diagnoseOutliersRaw->Divide(4,4);
         diagnoseOutliersProcessed->SaveAs("diagnoseOutliersProcessed.ps");
         diagnoseOutliersProcessed->Clear();
         diagnoseOutliersProcessed->Divide(4,4);
      }
      
      // would like to fill signal shapes to first pad
      // for raw
      file->cd();
      file->cd("combinedRawCanvas");
      gDirectory->cd(region.GetString().c_str());
      std::string canvasName = "rawCanvas_" + id.GetIdAsString();
      TCanvas *can = (TCanvas*)gDirectory->Get(canvasName.c_str());
      TList *list = can->GetListOfPrimitives();
      diagnoseOutliersRaw->cd(padNum2);
      for(unsigned int entry=0;entry<list->GetEntries();++entry){
         TH1F* hist = (TH1F*)list->At(entry);
         hist->SetMarkerSize(.4);
         if(entry == 0)
            hist->Draw();
         else 
            hist->Draw("same");
      }
      
      // for processed
      file->cd();
      file->cd("combinedProcessedCanvas");
      gDirectory->cd(region.GetString().c_str());
      canvasName = "processedCanvas_" + id.GetIdAsString();
      can = (TCanvas*)gDirectory->Get(canvasName.c_str());
      list = can->GetListOfPrimitives();
      diagnoseOutliersProcessed->cd(padNum2);
      for(unsigned int entry=0;entry<list->GetEntries();++entry){
         TH1F* hist = (TH1F*)list->At(entry);
         hist->SetMarkerSize(.4);
         if(entry == 0)
            hist->Draw();
         else 
            hist->Draw("same");
      }
      
      // now the dac vs adcPeak
      padNum2++;
      
      // for raw
      diagnoseOutliersRaw->cd(padNum2);
      tree->GetRawDacVsAdcPeakGraph()->Draw("ap");
      tree->GetRawDacVsAdcPeakFit()->Draw("same");
      // draw satLvl
      TF1 lineRawSatLvl("lineRawSatLvl","pol1",0,10000);
      lineRawSatLvl.SetParameter(1,0);
      lineRawSatLvl.SetParameter(0,tree->GetRawSatLevel());
      lineRawSatLvl.SetLineColor(kRed);
      lineRawSatLvl.DrawCopy("same");
      // draw satLow
      TF1 lineRawSatLow("lineRawSatLow","pol1",0,10000);
      lineRawSatLow.SetParameter(1,0);
      lineRawSatLow.SetParameter(0,tree->GetRawSatLow());
      lineRawSatLow.SetLineColor(kGreen);
      lineRawSatLow.DrawCopy("same");
      // draw satLow
      TF1 lineRawSatHigh("lineRawSatHigh","pol1",0,10000);
      lineRawSatHigh.SetParameter(1,0);
      lineRawSatHigh.SetParameter(0,tree->GetRawSatHigh());
      lineRawSatHigh.SetLineColor(kBlue);
      lineRawSatHigh.DrawCopy("same");
      
      
      // for processed
      diagnoseOutliersProcessed->cd(padNum2);
      tree->GetProcessedDacVsAdcPeakGraph()->Draw("ap");
      tree->GetProcessedDacVsAdcPeakFit()->Draw("same");
      // draw satLvl
      TF1 lineProcessedSatLvl("lineProcessedSatLvl","pol1",0,10000);
      lineProcessedSatLvl.SetParameter(1,0);
      lineProcessedSatLvl.SetParameter(0,tree->GetProcessedSatLevel());
      lineProcessedSatLvl.SetLineColor(kRed);
      lineProcessedSatLvl.DrawCopy("same");
      // draw satLow
      TF1 lineProcessedSatLow("lineProcessedSatLow","pol1",0,10000);
      lineProcessedSatLow.SetParameter(1,0);
      lineProcessedSatLow.SetParameter(0,tree->GetProcessedSatLow());
      lineProcessedSatLow.SetLineColor(kGreen);
      lineProcessedSatLow.DrawCopy("same");
      // draw satLow
      TF1 lineProcessedSatHigh("lineProcessedSatHigh","pol1",0,10000);
      lineProcessedSatHigh.SetParameter(1,0);
      lineProcessedSatHigh.SetParameter(0,tree->GetProcessedSatHigh());
      lineProcessedSatHigh.SetLineColor(kBlue);
      lineProcessedSatHigh.DrawCopy("same");
      
      // now the estimate peak vs ts-1
      padNum2++;
      
      // for raw
      diagnoseOutliersRaw->cd(padNum2);
      tree->GetRawPeakVsTs1Graph()->Draw("ap");
      tree->GetRawPeakVsTs1Fit()->Draw("same");
      // draw satLvl
      lineRawSatLvl.DrawCopy("same");
      // draw satLow
      lineRawSatLow.DrawCopy("same");
      // draw satLow
      lineRawSatHigh.DrawCopy("same");
      
      
      // for processed
      diagnoseOutliersProcessed->cd(padNum2);
      tree->GetProcessedPeakVsTs1Graph()->Draw("ap");
      tree->GetProcessedPeakVsTs1Fit()->Draw("same");
      // draw satLvl
      lineProcessedSatLvl.DrawCopy("same");
      // draw satLow
      lineProcessedSatLow.DrawCopy("same");
      // draw satLow
      lineProcessedSatHigh.DrawCopy("same");
      
      
      // now the estimate peak vs ts-2
      padNum2++;
      
      // for raw
      diagnoseOutliersRaw->cd(padNum2);
      tree->GetRawPeakVsTs2Graph()->Draw("ap");
      tree->GetRawPeakVsTs2Fit()->Draw("same");
      // draw satLvl
      lineRawSatLvl.DrawCopy("same");
      // draw satLow
      lineRawSatLow.DrawCopy("same");
      // draw satLow
      lineRawSatHigh.DrawCopy("same");
      
      // for processed
      diagnoseOutliersProcessed->cd(padNum2);
      tree->GetProcessedPeakVsTs2Graph()->Draw("ap");
      tree->GetProcessedPeakVsTs2Fit()->Draw("same");
      // draw satLvl
      lineProcessedSatLvl.DrawCopy("same");
      // draw satLow
      lineProcessedSatLow.DrawCopy("same");
      // draw satLow
      lineProcessedSatHigh.DrawCopy("same");
      
      
   }
   dacVsAdcPeakPlots->SaveAs("dacVsAdcPeakPlots.ps)");
   diagnoseOutliersRaw->SaveAs("diagnoseOutliersRaw.ps)");
   diagnoseOutliersProcessed->SaveAs("diagnoseOutliersProcessed.ps)");
   
   std::cout << " End.\n";
   
   return 0;
}




