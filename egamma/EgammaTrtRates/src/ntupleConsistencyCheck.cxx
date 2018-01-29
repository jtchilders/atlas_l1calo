
#include <iostream>
#include <map>
#include <vector>
#include <fstream>

#include "TrigEgammaNtuple_v1.h"
#include "TrigEgammaNtuple_v2.h"

#include "tclap/CmdLine.h"

#include "TFile.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TH1I.h"
#include "TLegend.h"
#include "TH1.h"

#include "RateHisto.h"

// Run Number: 160472
// LUMI: 202

int main(int argc,char **argv){
   
   #include "gStyleSetup.h"
   
   TH1::AddDirectory(0);
   
   std::string inputFilename_v1;
   std::string inputFilename_v2;
   try{
      // Define the command line object.
      TCLAP::CmdLine cmd("Test differing MakeClasses for egamma ntuples", ' ', "0.1");
      
      TCLAP::ValueArg<std::string> inputFile_v1("1","fileV1","Root file that contain tree version 1.",true,"","string");
      cmd.add(inputFile_v1);
      TCLAP::ValueArg<std::string> inputFile_v2("2","fileV2","Root file that contain tree version 2.",true,"","string");
      cmd.add(inputFile_v2);
      
      cmd.parse(argc,argv);
      
      inputFilename_v1 = inputFile_v1.getValue();
      
      inputFilename_v2 = inputFile_v2.getValue();
      
   } catch (TCLAP::ArgException &e)  // catch any exceptions
   { std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl; }
   
   
   TFile *inFile_v1 = new TFile(inputFilename_v1.c_str(),"READ");
   TrigEgammaNtuple_v1 *tv1 = new TrigEgammaNtuple_v1(inFile_v1,"output_v1.root");
   tv1->Init();
   tv1->LoadTree(0);
   
   TH1I *h_v1_numEvts = new TH1I("h_v1_numEvts","Number of events passing a trigger for Tree V1",10,0,10);
   TH1I *h_v2_numEvts = new TH1I("h_v2_numEvts","Number of events passing a trigger for Tree V2",10,0,10);
   std::vector<std::string> binNames;
   binNames.push_back("L1_EM3");
   binNames.push_back("L2_e5_medium");
   binNames.push_back("EF_e5_medium");
   binNames.push_back("L1_EM5");
   binNames.push_back("L2_e10_medium");
   binNames.push_back("EF_e10_medium");
   binNames.push_back("L1_EM10");
   binNames.push_back("L2_e15_medium");
   binNames.push_back("EF_e15_medium");
   binNames.push_back("All Events");
   for(unsigned int i=0;i<10;++i){
      h_v1_numEvts->GetXaxis()->SetBinLabel(i+1,binNames[i].c_str());
      h_v2_numEvts->GetXaxis()->SetBinLabel(i+1,binNames[i].c_str());
   }
   
   const Long64_t totalEntries_v1 = tv1->GetEntries();
   const Long64_t onePercent_v1 = (Long64_t)((float)totalEntries_v1*0.01 + 1.0); 
   for(Long64_t i=0;i<totalEntries_v1;++i){
      
      if( !(i % onePercent_v1) ){
         std::cout << " PercentDone: " << (int)(((float)i/(float)totalEntries_v1)*100.0) << std::endl;
      }
      
      
      tv1->LoadTree(i);
      
      if(tv1->EventPassedTrig(tv1->Trigger_L1passed,"L1_EM3")) h_v1_numEvts->Fill(0.5);
      if(tv1->EventPassedTrig(tv1->Trigger_L2passed,"L2_e5_medium")) h_v1_numEvts->Fill(1.5);
      if(tv1->EventPassedTrig(tv1->Trigger_L2passed,"EF_e5_medium")) h_v1_numEvts->Fill(2.5);
      if(tv1->EventPassedTrig(tv1->Trigger_L1passed,"L1_EM5")) h_v1_numEvts->Fill(3.5);
      if(tv1->EventPassedTrig(tv1->Trigger_L2passed,"L2_e10_medium")) h_v1_numEvts->Fill(4.5);
      if(tv1->EventPassedTrig(tv1->Trigger_L2passed,"EF_e10_medium")) h_v1_numEvts->Fill(5.5);
      if(tv1->EventPassedTrig(tv1->Trigger_L1passed,"L1_EM10")) h_v1_numEvts->Fill(6.5);
      if(tv1->EventPassedTrig(tv1->Trigger_L2passed,"L2_e15_medium")) h_v1_numEvts->Fill(7.5);
      if(tv1->EventPassedTrig(tv1->Trigger_L2passed,"EF_e15_medium")) h_v1_numEvts->Fill(8.5);
      
      h_v1_numEvts->Fill(9.5);
      
      
   }// end for(i)
   
   delete tv1;
   tv1 = 0;
   
   inFile_v1->Close();
   delete inFile_v1;
   inFile_v1 = 0;
   
   
   TFile *inFile_v2 = new TFile(inputFilename_v2.c_str(),"READ");
   TrigEgammaNtuple_v2 *tv2 = new TrigEgammaNtuple_v2(inFile_v2,"output_v2.root");
   tv2->Init();
   tv2->fChainMetadata->GetEntry(0);
   
   std::cout << "size: " << tv2->fChainMetadata->GetEntries() << std::endl; 
   std::cout << " size: " << tv2->Trigger_L1ChainName->size() << std::endl;
   
   std::vector<int> L2trigPTpassed;
   L2trigPTpassed.resize(tv2->Trigger_L2ChainName->size(),0);
   std::vector<int> EFtrigPTpassed;
   EFtrigPTpassed.resize(tv2->Trigger_EFChainName->size(),0);
   
   const Long64_t totalEntries_v2 = tv2->GetEntries();
   const Long64_t onePercent_v2 = (Long64_t)((float)totalEntries_v2*0.01 + 1.0); 
   for(Long64_t i=0;i<totalEntries_v2;++i){
      
      if( !(i % onePercent_v2) ){
         std::cout << " PercentDone: " << (int)(((float)i/(float)totalEntries_v2)*100.0) << std::endl;
      }
      
      tv2->LoadTree(i);
      
      if(tv2->EventPassedTrig("L1_EM3"))        h_v2_numEvts->Fill(0.5);
      if(tv2->EventPassedTrig("L2_e5_medium"))  h_v2_numEvts->Fill(1.5);
      if(tv2->EventPassedTrig("EF_e5_medium"))  h_v2_numEvts->Fill(2.5);
      if(tv2->EventPassedTrig("L1_EM5"))        h_v2_numEvts->Fill(3.5);
      if(tv2->EventPassedTrig("L2_e10_medium")) h_v2_numEvts->Fill(4.5);
      if(tv2->EventPassedTrig("EF_e10_medium")) h_v2_numEvts->Fill(5.5);
      if(tv2->EventPassedTrig("L1_EM10"))       h_v2_numEvts->Fill(6.5);
      if(tv2->EventPassedTrig("L2_e15_medium")) h_v2_numEvts->Fill(7.5);
      if(tv2->EventPassedTrig("EF_e15_medium")) h_v2_numEvts->Fill(8.5);
      
      h_v2_numEvts->Fill(9.5);
      
      for(unsigned int trig=0;trig<tv2->Trigger_L2ChainName->size();++trig){
         if(tv2->EventPassedTrig_PT(tv2->Trigger_L2ChainName->at(trig)))
            L2trigPTpassed[trig]++;
      }
      
      for(unsigned int trig=0;trig<tv2->Trigger_EFChainName->size();++trig){
         if(tv2->EventPassedTrig_PT(tv2->Trigger_EFChainName->at(trig)))
            EFtrigPTpassed[trig]++;
      }
      
//       std::vector<std::string>* chainName = tv2->Trigger_L1ChainName;
//       for(unsigned int i=0;i<chainName->size();++i){
// //          float prescale = tv2->GetPrescaled(chainName->at(i));
// //          std::cout << " " << chainName->at(i) << " prescale = " << prescale << std::endl;
//          
//          bool passThrough = tv2->EventPassedTrig_PT(chainName->at(i));
//          std::cout << " " << chainName->at(i) << " passedThrough: " << (int)passThrough << std::endl;
//          
//          std::cin.get();
//       }
      
//       chainName = tv2->Trigger_L2ChainName;
//       for(unsigned int i=0;i<chainName->size();++i){
// //          float prescale = tv2->GetPrescaled(chainName->at(i));
// //          std::cout << " " << chainName->at(i) << " prescale = " << prescale << std::endl;
//          
//          bool passThrough = tv2->EventPassedTrig_PT(chainName->at(i));
//          std::cout << " " << chainName->at(i) << " passedThrough: " << (int)passThrough << std::endl;
//          
//          std::cin.get();
//       }
      
//       chainName = tv2->Trigger_EFChainName;
//       for(unsigned int i=0;i<chainName->size();++i){
// //          float prescale = tv2->GetPrescaled(chainName->at(i));
// //          std::cout << " " << chainName->at(i) << " prescale = " << prescale << std::endl;
//          
//          bool passThrough = tv2->EventPassedTrig_PT(chainName->at(i));
//          std::cout << " " << chainName->at(i) << " passedThrough: " << (int)passThrough << std::endl;
//          
//          std::cin.get();
//       }
      
      
   }// end for(i)
   
   
   for(unsigned int i=0;i<L2trigPTpassed.size();++i){
      if(L2trigPTpassed[i] > 0)
         std::cout << "PT passed by " << tv2->Trigger_L2ChainName->at(i) << std::endl;
   }
   
   for(unsigned int i=0;i<EFtrigPTpassed.size();++i){
      if(EFtrigPTpassed[i] > 0)
         std::cout << "PT passed by " << tv2->Trigger_EFChainName->at(i) << std::endl;
   }
      
   delete tv2;
   tv2 = 0;
   
   inFile_v2->Close();
   delete inFile_v2;
   inFile_v2 = 0;
   
   TCanvas can("can","can",0,0,800,600);
   can.Divide(2,1);
   can.cd(1);
   h_v1_numEvts->SetLabelSize(0.05);
   h_v1_numEvts->Draw();
   h_v1_numEvts->SetMarkerSize(2);
   h_v1_numEvts->Draw("textsame");
   can.cd(2);
   h_v2_numEvts->SetLabelSize(0.05);
   h_v2_numEvts->Draw();
   h_v2_numEvts->SetMarkerSize(2);
   h_v2_numEvts->Draw("textsame");
   can.SaveAs("numberOfEvts.ps");
   
   TFile file("ntupleTest.root","RECREATE");
   h_v1_numEvts->Write();
   h_v2_numEvts->Write();
   file.Close();
   
   delete h_v1_numEvts;
   h_v1_numEvts = 0;
   
   delete h_v2_numEvts;
   h_v2_numEvts = 0;
   
   
   std::cout << "done.\n";
   
}
