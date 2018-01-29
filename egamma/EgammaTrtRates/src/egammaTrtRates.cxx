
#include <iostream>
#include <map>
#include <vector>
#include <fstream>

#include "TrigEgammaNtuple_v1.h"

#include "tclap/CmdLine.h"

#include "TFile.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TH1I.h"
#include "TLegend.h"

#include "RateHisto.h"

int main(int argc,char **argv){
   
   #include "gStyleSetup.h"
   
   std::string inputFilename;
   try{
      // Define the command line object.
      TCLAP::CmdLine cmd("Creating Rate Histograms for Egamma chains", ' ', "0.1");
      
      TCLAP::ValueArg<std::string> inputFileList("f","file","Text file with input root file on separate lines.",true,"","string");
      cmd.add(inputFileList);
      
      cmd.parse(argc,argv);
      
      inputFilename = inputFileList.getValue();
      
   } catch (TCLAP::ArgException &e)  // catch any exceptions
   { std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl; }
   
   
   /// Extract data from file list
   /// file should contain on each row:
   /// </path/filename.root>
   ///
   std::vector<std::string> fileList;
   
   std::ifstream fin(inputFilename.c_str());
   if(!fin){
      std::cerr << "ERROR Opening file: " << inputFilename << std::endl;
      return 0;
   }
   
   // extract TTrees from files
   while(!fin.eof()){
      
      char buffer[500];
      
      fin.getline(buffer,500);
      
      std::string filename(buffer);
      
      std::cout << filename << std::endl;
      
      if(filename.size() > 0)
         fileList.push_back(filename);
      
      
   }
   
   std::vector<TFile*> tfileList;
   
   TFile *inFile = new TFile(fileList[0].c_str(),"READ");
   tfileList.push_back(inFile);
   TrigEgammaNtuple_v1 *tree = new TrigEgammaNtuple_v1(inFile,"output.root");
   for(unsigned int i=1;i<fileList.size();++i){
      inFile = new TFile(fileList[i].c_str(),"READ");
      tree->addFile(inFile);
      tfileList.push_back(inFile);
   }
   tree->Init();
   tree->LoadTree(0);
   
   RateHisto rh_L1_EM5("rh_L1_EM5","Rate Histogram");
   
   RateHisto rh_EF_e10_medium("rh_EF_e10_medium","Rate Histogram");
   RateHisto rh_L2_e10_medium("rh_L2_e10_medium","Rate Histogram");
   
   RateHisto rh_EF_e10_medium_TRT("rh_EF_e10_medium_TRT","Rate Histogram");
   RateHisto rh_L2_e10_medium_TRT("rh_L2_e10_medium_TRT","Rate Histogram");
   
   RateHisto rh_EF_e10_medium_SiTrk("rh_EF_e10_medium_SiTrk","Rate Histogram");
   RateHisto rh_L2_e10_medium_SiTrk("rh_L2_e10_medium_SiTrk","Rate Histogram");
   
   RateHisto rh_EF_e10_medium_IDTrkNoCut("rh_EF_e10_medium_IDTrkNoCut","Rate Histogram");
   RateHisto rh_L2_e10_medium_IDTrkNoCut("rh_L2_e10_medium_IDTrkNoCut","Rate Histogram");
   
   TH1I *h_eta = new TH1I("h_eta","EFegamma_TrackIndex >= 0;EFegamma_eta",240,-3.,3.);
   TH1I *h_eta_SCT_Pix = new TH1I("h_eta_SCT_Pix","EFegamma_nPix+nSCT > 0;EFegamma_eta",240,-3.,3.);
   h_eta_SCT_Pix->SetLineColor(kBlue);
   TH1I *h_eta_nTRT = new TH1I("h_eta_nTRT","EFegamma_nPix+nSCT == 0 && nTRT>0;EFegamma_eta",240,-3.,3.);
   h_eta_nTRT->SetLineColor(kRed);
   TH1I *h_eta_nTRThigh = new TH1I("h_eta_nTRThigh","EFegamma_nPix+nSCT == 0 && nTRThigh>0;EFegamma_eta",240,-3.,3.);
   h_eta_nTRThigh->SetLineColor(kGreen);
   
   TLegend leg(0.6,0.9,0.95,0.75);
   leg.AddEntry(h_eta,"TrackIndex >= 0");
   leg.AddEntry(h_eta_SCT_Pix,"TI >= 0 && nSCT+nPix > 0 && All");
   leg.AddEntry(h_eta_nTRT,"TI>=0 && nTRT>0 && TRTOnly");
   leg.AddEntry(h_eta_nTRThigh,"TI>=0 && nTRThigh>0 && TRTOnly");
   
   if(tree->Event_run_number == 160387){
      
      rh_L1_EM5.SetPrescale(0,154,-1);
      rh_L1_EM5.SetPrescale(155,394,1);
      
      rh_EF_e10_medium.SetPrescale(0,154,-1);
      rh_EF_e10_medium.SetPrescale(155,394,1);
      
      rh_L2_e10_medium.SetPrescale(0,154,-1);
      rh_L2_e10_medium.SetPrescale(155,394,1);
      
      rh_EF_e10_medium_TRT.SetPrescale(0,154,-1);
      rh_EF_e10_medium_TRT.SetPrescale(155,394,1);
      
      rh_L2_e10_medium_TRT.SetPrescale(0,154,-1);
      rh_L2_e10_medium_TRT.SetPrescale(155,159,4);
      rh_L2_e10_medium_TRT.SetPrescale(160,394,1);
      
      rh_EF_e10_medium_SiTrk.SetPrescale(0,154,-1);
      rh_EF_e10_medium_SiTrk.SetPrescale(155,394,1);
      
      rh_L2_e10_medium_SiTrk.SetPrescale(0,37,-1);
      rh_L2_e10_medium_SiTrk.SetPrescale(38,45,-1);
      rh_L2_e10_medium_SiTrk.SetPrescale(46,49,-1);
      rh_L2_e10_medium_SiTrk.SetPrescale(50,60,-1);
      rh_L2_e10_medium_SiTrk.SetPrescale(61,154,-1);
      rh_L2_e10_medium_SiTrk.SetPrescale(155,159,30);
      rh_L2_e10_medium_SiTrk.SetPrescale(160,172,20);
      rh_L2_e10_medium_SiTrk.SetPrescale(173,174,15);
      rh_L2_e10_medium_SiTrk.SetPrescale(175,191,20);
      rh_L2_e10_medium_SiTrk.SetPrescale(192,194,15);
      rh_L2_e10_medium_SiTrk.SetPrescale(195,305,15);
      rh_L2_e10_medium_SiTrk.SetPrescale(306,311,10);
      rh_L2_e10_medium_SiTrk.SetPrescale(312,394,15);
      
      rh_EF_e10_medium_IDTrkNoCut.SetPrescale(0,154,-1);
      rh_EF_e10_medium_IDTrkNoCut.SetPrescale(155,394,1);
      
      rh_L2_e10_medium_IDTrkNoCut.SetPrescale(0,154,-1);
      rh_L2_e10_medium_IDTrkNoCut.SetPrescale(155,394,1);
      
   }
   
   const Long64_t totalEntries = tree->GetEntries();
   const Long64_t onePercent = (Long64_t)((float)totalEntries*0.01 + 1.0); 
   for(Long64_t i=0;i<totalEntries;++i){
      
      if( !(i % onePercent) ){
         std::cout << " PercentDone: " << (int)(((float)i/(float)totalEntries)*100.0) << std::endl;
      }
      
      
      tree->LoadTree(i);
      
//       std::map<string,bool>::iterator begin = tree->Trigger_EFpassed->begin();
//       
//       for(;begin!=tree->Trigger_EFpassed->end();++begin){
//          std::cout << begin->first << " == " << (int)begin->second << std::endl;
//       }
      
      // if it passed EF_e10_medium trigger
      if((*tree->Trigger_EFpassed)["EF_e10_medium"]){
         rh_EF_e10_medium.IncrementLumiblock(tree->Event_lumiBlock);
      }
      // if it passed L2_e10_medium trigger
      if((*tree->Trigger_L2passed)["L2_e10_medium"]){
         rh_L2_e10_medium.IncrementLumiblock(tree->Event_lumiBlock);
      }
      // if it passed EF_e10_medium_TRT trigger
      if((*tree->Trigger_EFpassed)["EF_e10_medium_TRT"]){
         rh_EF_e10_medium_TRT.IncrementLumiblock(tree->Event_lumiBlock);
      }
      // if it passed L2_e10_medium_TRT trigger
      if((*tree->Trigger_L2passed)["L2_e10_medium_TRT"]){
         rh_L2_e10_medium_TRT.IncrementLumiblock(tree->Event_lumiBlock);
      }
      // if it passed L1_EM5 trigger
      if((*tree->Trigger_L1passed)["L1_EM5"]){
         rh_L1_EM5.IncrementLumiblock(tree->Event_lumiBlock);
      }
      // if it passed EF_e10_medium_TRT trigger
      if((*tree->Trigger_EFpassed)["EF_e10_medium_SiTrk"]){
         rh_EF_e10_medium_SiTrk.IncrementLumiblock(tree->Event_lumiBlock);
      }
      // if it passed L2_e10_medium_TRT trigger
      if((*tree->Trigger_L2passed)["L2_e10_medium_SiTrk"]){
         rh_L2_e10_medium_SiTrk.IncrementLumiblock(tree->Event_lumiBlock);
      }
      // if it passed EF_e10_medium_IDTrkNoCut trigger
      if((*tree->Trigger_EFpassed)["EF_e10_medium_IDTrkNoCut"]){
         rh_EF_e10_medium_IDTrkNoCut.IncrementLumiblock(tree->Event_lumiBlock);
      }
      // if it passed L2_e10_medium_IDTrkNoCut trigger
      if((*tree->Trigger_L2passed)["L2_e10_medium_IDTrkNoCut"]){
         rh_L2_e10_medium_IDTrkNoCut.IncrementLumiblock(tree->Event_lumiBlock);
      }
      
      
      for(unsigned int n=0;n<tree->EFegamma_nEGamma;++n){
         
         if(tree->EFegamma_TrackIndex->at(n) >= 0){
            
            std::string slice = tree->EFTrackParticle_slice->at(tree->EFegamma_TrackIndex->at(n));
            
            bool isTRTOnly = slice.find("HLT_InDetTrigParticleCreationTRTOnly_Electron_EFID") != std::string::npos;
            bool isOther = slice.find("HLT_InDetTrigParticleCreation_Electron_EFID") != std::string::npos;
            
            
            h_eta->Fill(tree->EFegamma_eta->at(n));
            
            if(isTRTOnly && tree->EFegamma_nTRT->at(n) > 0)
               h_eta_nTRT->Fill(tree->EFegamma_eta->at(n));
            
            if(isTRTOnly && tree->EFegamma_nTRThigh->at(n) > 0)
               h_eta_nTRThigh->Fill(tree->EFegamma_eta->at(n));
            
            if(tree->EFegamma_nSCT->at(n) + tree->EFegamma_nPix->at(n) > 0 && isOther)
               h_eta_SCT_Pix->Fill(tree->EFegamma_eta->at(n));
               
         }
      }
      
      
   }// end for(i)
   
   rh_EF_e10_medium.BuildHisto();
   rh_EF_e10_medium.SetLineColor(kRed);
   rh_L2_e10_medium.BuildHisto();
   rh_L2_e10_medium.SetLineColor(kGreen);
   
   rh_EF_e10_medium_TRT.BuildHisto();
   rh_EF_e10_medium_TRT.SetLineColor(kRed);
   rh_L2_e10_medium_TRT.BuildHisto();
   rh_L2_e10_medium_TRT.SetLineColor(kGreen);
   
   rh_L1_EM5.BuildHisto();
   rh_L1_EM5.SetLineColor(kBlue);
   
   rh_L2_e10_medium_SiTrk.BuildHisto();
   rh_L2_e10_medium_SiTrk.SetLineColor(kGreen);
   rh_EF_e10_medium_SiTrk.BuildHisto();
   rh_EF_e10_medium_SiTrk.SetLineColor(kRed);
   
   rh_EF_e10_medium_IDTrkNoCut.BuildHisto();
   rh_EF_e10_medium_IDTrkNoCut.SetLineColor(kRed);
   rh_L2_e10_medium_IDTrkNoCut.BuildHisto();
   rh_L2_e10_medium_IDTrkNoCut.SetLineColor(kGreen);
   
   TCanvas can("can","can",0,0,1400,1000);
   can.SetLogy(true);
   
   rh_L1_EM5.GetHisto()->Draw();
   rh_L2_e10_medium.GetHisto()->Draw("same");
   rh_EF_e10_medium.GetHisto()->Draw("same");
   
   TLegend legend(0.65,0.9,0.9,0.7,"Trigger Chains");
   legend.AddEntry(rh_L1_EM5.GetHisto(),"L1_EM5","l");
   legend.AddEntry(rh_L2_e10_medium.GetHisto(),"L2_e10_medium","l");
   legend.AddEntry(rh_EF_e10_medium.GetHisto(),"EF_e10_medium","l");
   legend.Draw("same");
   
   can.SaveAs("can.ps(");
   
   rh_L1_EM5.GetPrescaleCorrectedHisto()->Draw();
   rh_L2_e10_medium.GetPrescaleCorrectedHisto()->Draw("same");
   rh_EF_e10_medium.GetPrescaleCorrectedHisto()->Draw("same");
   
   legend.Clear();
   legend.SetHeader("Trigger Chains");
   legend.AddEntry(rh_L1_EM5.GetHisto(),"L1_EM5","l");
   legend.AddEntry(rh_L2_e10_medium.GetPrescaleCorrectedHisto(),"L2_e10_medium","l");
   legend.AddEntry(rh_EF_e10_medium.GetPrescaleCorrectedHisto(),"EF_e10_medium","l");
   legend.Draw("same");
   
   can.SaveAs("can.ps");
   
   rh_L1_EM5.GetHisto()->Draw();
   rh_L2_e10_medium_TRT.GetHisto()->Draw("same");
   rh_EF_e10_medium_TRT.GetHisto()->Draw("same");
   
   TLegend legend_TRT(0.65,0.9,0.9,0.7,"Trigger Chains");
   legend_TRT.AddEntry(rh_L1_EM5.GetHisto(),"L1_EM5","l");
   legend_TRT.AddEntry(rh_L2_e10_medium_TRT.GetHisto(),"L2_e10_medium_TRT","l");
   legend_TRT.AddEntry(rh_EF_e10_medium_TRT.GetHisto(),"EF_e10_medium_TRT","l");
   legend_TRT.Draw("same");
   
   can.SaveAs("can.ps");
   
   rh_L1_EM5.GetPrescaleCorrectedHisto()->Draw();
   rh_L2_e10_medium_TRT.GetPrescaleCorrectedHisto()->Draw("same");
   rh_EF_e10_medium_TRT.GetPrescaleCorrectedHisto()->Draw("same");
   
   legend_TRT.Clear();
   legend_TRT.SetHeader("Trigger Chains");
   legend_TRT.AddEntry(rh_L1_EM5.GetHisto(),"L1_EM5","l");
   legend_TRT.AddEntry(rh_L2_e10_medium_TRT.GetPrescaleCorrectedHisto(),"L2_e10_medium_TRT","l");
   legend_TRT.AddEntry(rh_EF_e10_medium_TRT.GetPrescaleCorrectedHisto(),"EF_e10_medium_TRT","l");
   legend_TRT.Draw("same");
   
   can.SaveAs("can.ps");
   
   rh_L1_EM5.GetHisto()->Draw();
   rh_L2_e10_medium_SiTrk.GetHisto()->Draw("same");
   rh_EF_e10_medium_SiTrk.GetHisto()->Draw("same");
   
   TLegend legend_SiTrk(0.65,0.9,0.9,0.7,"Trigger Chains");
   legend_SiTrk.AddEntry(rh_L1_EM5.GetHisto(),"L1_EM5","l");
   legend_SiTrk.AddEntry(rh_L2_e10_medium_SiTrk.GetHisto(),"L2_e10_medium_SiTrk","l");
   legend_SiTrk.AddEntry(rh_EF_e10_medium_SiTrk.GetHisto(),"EF_e10_medium_SiTrk","l");
   legend_SiTrk.Draw("same");
   
   can.SaveAs("can.ps");
   
   rh_L1_EM5.GetPrescaleCorrectedHisto()->Draw();
   rh_L2_e10_medium_SiTrk.GetPrescaleCorrectedHisto()->Draw("same");
   rh_EF_e10_medium_SiTrk.GetPrescaleCorrectedHisto()->Draw("same");
   
   legend_SiTrk.Clear();
   legend_SiTrk.SetHeader("Trigger Chains");
   legend_SiTrk.AddEntry(rh_L1_EM5.GetHisto(),"L1_EM5","l");
   legend_SiTrk.AddEntry(rh_L2_e10_medium_SiTrk.GetPrescaleCorrectedHisto(),"L2_e10_medium_SiTrk","l");
   legend_SiTrk.AddEntry(rh_EF_e10_medium_SiTrk.GetPrescaleCorrectedHisto(),"EF_e10_medium_SiTrk","l");
   legend_SiTrk.Draw("same");
   
   can.SaveAs("can.ps");
   
   rh_L1_EM5.GetHisto()->Draw();
   rh_L2_e10_medium_IDTrkNoCut.GetHisto()->Draw("same");
   rh_EF_e10_medium_IDTrkNoCut.GetHisto()->Draw("same");
   
   TLegend legend_IDTrkNoCut(0.65,0.9,0.9,0.7,"Trigger Chains");
   legend_IDTrkNoCut.AddEntry(rh_L1_EM5.GetHisto(),"L1_EM5","l");
   legend_IDTrkNoCut.AddEntry(rh_L2_e10_medium_IDTrkNoCut.GetHisto(),"rh_L2_e10_medium_IDTrkNoCut","l");
   legend_IDTrkNoCut.AddEntry(rh_EF_e10_medium_IDTrkNoCut.GetHisto(),"rh_EF_e10_medium_IDTrkNoCut","l");
   legend_IDTrkNoCut.Draw("same");
   
   can.SaveAs("can.ps");
   
   rh_L1_EM5.GetPrescaleCorrectedHisto()->Draw();
   rh_L2_e10_medium_IDTrkNoCut.GetPrescaleCorrectedHisto()->Draw("same");
   rh_EF_e10_medium_IDTrkNoCut.GetPrescaleCorrectedHisto()->Draw("same");
   
   legend_IDTrkNoCut.Clear();
   legend_IDTrkNoCut.SetHeader("Trigger Chains");
   legend_IDTrkNoCut.AddEntry(rh_L1_EM5.GetHisto(),"L1_EM5","l");
   legend_IDTrkNoCut.AddEntry(rh_L2_e10_medium_IDTrkNoCut.GetPrescaleCorrectedHisto(),"rh_L2_e10_medium_IDTrkNoCut","l");
   legend_IDTrkNoCut.AddEntry(rh_EF_e10_medium_IDTrkNoCut.GetPrescaleCorrectedHisto(),"rh_EF_e10_medium_IDTrkNoCut","l");
   legend_IDTrkNoCut.Draw("same");
   
   can.SaveAs("can.ps)");
   
   /// Ouput to file
   TFile file("rateOutput.root","RECREATE");
   rh_L1_EM5.GetHisto()->Write();
   rh_L2_e10_medium.GetHisto()->Write();
   rh_EF_e10_medium.GetHisto()->Write();
   rh_L2_e10_medium_TRT.GetHisto()->Write();
   rh_EF_e10_medium_TRT.GetHisto()->Write();
   rh_L2_e10_medium_SiTrk.GetHisto()->Write();
   rh_EF_e10_medium_SiTrk.GetHisto()->Write();
   rh_L2_e10_medium_IDTrkNoCut.GetHisto()->Write();
   rh_EF_e10_medium_IDTrkNoCut.GetHisto()->Write();
   
   rh_L1_EM5.GetPrescaleCorrectedHisto()->Write();
   rh_L2_e10_medium.GetPrescaleCorrectedHisto()->Write();
   rh_EF_e10_medium.GetPrescaleCorrectedHisto()->Write();
   rh_L2_e10_medium_TRT.GetPrescaleCorrectedHisto()->Write();
   rh_EF_e10_medium_TRT.GetPrescaleCorrectedHisto()->Write();
   rh_L2_e10_medium_SiTrk.GetPrescaleCorrectedHisto()->Write();
   rh_EF_e10_medium_SiTrk.GetPrescaleCorrectedHisto()->Write();
   rh_L2_e10_medium_IDTrkNoCut.GetPrescaleCorrectedHisto()->Write();
   rh_EF_e10_medium_IDTrkNoCut.GetPrescaleCorrectedHisto()->Write();
   
   h_eta->Write();
   h_eta_nTRT->Write();
   h_eta_nTRThigh->Write();
   h_eta_SCT_Pix->Write();
   
   TCanvas plotCan("plotCan","",0,0,800,600);
   h_eta->Draw();
   h_eta_SCT_Pix->Draw("same");
   h_eta_nTRT->Draw("same");
   h_eta_nTRThigh->Draw("same");
   leg.Draw("same");
   plotCan.SaveAs("plotCan.ps");
   plotCan.Write();
   
   file.Close();
   
   
}
