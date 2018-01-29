
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <cmath>

#include "TrigEgammaNtuple_v1.h"

#include "tclap/CmdLine.h"

#include "TFile.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TH1I.h"
#include "TH2I.h"
#include "TLegend.h"
#include "TProfile.h"


int main(int argc,char **argv){
   
   #include "gStyleSetup.h"
   
   std::string inputFilename;
   try{
      // Define the command line object.
      TCLAP::CmdLine cmd("Analyze TRT track chains", ' ', "0.1");
      
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
   
   const float PI = 3.14159265;
   
   // L2_e10_medium plots
   TH1I h_L2_e10_medium_E("h_L2_e10_medium_E","Energy of L2 reconstructed electrons passing L2_e10_medium;E(MeV)",500,0,500000);
   TH1I h_L2_e10_medium_eta("h_L2_e10_medium_eta","#eta distribution of L2 reconstructed electrons passing L2_e10_medium;#eta",60,-3.0,3.0);
   
   TH2I h_L2_e10_medium_dEta_dPhi("h_L2_e10_medium_dEta_dPhi","#Delta#eta vs. #Delta#phi for electron - derived cluster passing L2_e10_medium;#Delta#eta;#Delta#phi",100,-0.5,0.5,100,-0.5,0.5);
   
   // EF_e10_medium plots
   TH1I h_EF_e10_medium_E("h_EF_e10_medium_E","Energy of EF reconstructed electrons passing EF_e10_medium;E(MeV)",500,0,500000);
   TH1I h_EF_e10_medium_eta("h_EF_e10_medium_eta","#eta distribution of EF reconstructed electrons passing EF_e10_medium;#eta",60,-3.0,3.0);
   
   TH2I h_EF_e10_medium_dEta_dPhi("h_EF_e10_medium_dEta_dPhi","#Delta#eta vs. #Delta#phi for electron - derived cluster passing EF_e10_medium;#Delta#eta;#Delta#phi",100,-0.5,0.5,100,-0.5,0.5);
   
   // L2_e10_medium_TRT plots
   TH1I h_L2_e10_medium_TRT_trtHits("h_L2_e10_medium_TRT_trtHits","Number of TRT Hits for L2_e10_medium_TRT",60,0,60);
   TProfile h_L2_e10_medium_TRT_trtHits_eta("h_L2_e10_medium_TRT_trtHits_eta","Number of TRT Hits for L2_e10_medium_TRT vs. #eta;#eta;num. TRT hits",60,-3.0,3.0);
   TH2I h_L2_e10_medium_TRT_trtHits_eta_2d("h_L2_e10_medium_TRT_trtHits_eta_2d","Number of TRT Hits for L2_e10_medium_TRT vs. #eta;#eta;num. TRT hits",60,-3.0,3.0,60,0.,60.);
   TH1I h_L2_e10_medium_TRT_trtHighHits("h_L2_e10_medium_TRT_trtHighHits","Number of TRT High Threshold Hits for L2_e10_medium_TRT",20,0,20);
   TProfile h_L2_e10_medium_TRT_trtHighHits_eta("h_L2_e10_medium_TRT_trtHighHits_eta","Number of TRT High Threshold Hits for L2_e10_medium_TRT vs. #eta;#eta;num. TRT high threshold hits",60,-3.0,3.0);
   TH2I h_L2_e10_medium_TRT_trtHighHits_eta_2d("h_L2_e10_medium_TRT_trtHighHits_eta_2d", "Number of TRT High Threshold Hits for L2_e10_medium_TRT vs. #eta;#eta;num. TRT high threshold hits",60,-3.0,3.0,60,0.,60.);
   TH1I h_L2_e10_medium_TRT_E("h_L2_e10_medium_TRT_E","Energy of L2 reconstructed electrons passing L2_e10_medium_TRT;E(MeV)",500,0,500000);
   TProfile h_L2_e10_medium_TRT_frac_eta("h_L2_e10_medium_TRT_frac_eta","Ratio of TRT High Threshold Hits to Normal Hits for L2_e10_medium_TRT vs. #eta;#eta;ratio",60,-3.0,3.0);
   TH2I h_L2_e10_medium_TRT_frac_eta_2d("h_L2_e10_medium_TRT_frac_eta_2d","Ratio of TRT High Threshold Hits to Normal Hits for L2_e10_medium_TRT vs. #eta;#eta;ratio",60,-3.0,3.0,100,0.,1.);
   TH1I h_L2_e10_medium_TRT_eta("h_L2_e10_medium_TRT_eta","#eta distribution of L2 reconstructed electrons passing L2_e10_medium_TRT;#eta",60,-3.0,3.0);
   
   TH2I h_L2_e10_medium_TRT_electronClusterEtaPhi("h_L2_e10_medium_TRT_electronClusterEtaPhi","L2 Electron #eta/#phi hit map passing L2_e10_medium_TRT;#eta;#phi",60,-3.0,3.0,64,-PI,PI);
   TH2I h_L2_e10_medium_TRT_hitsVsHighHits("h_L2_e10_medium_TRT_hitsVsHighHits","Num. TRT hits vs. TRT high threshold hits for electrons passing L2_e10_medium_TRT;hits;high threshold hits",50,0,50,50,0,50);
   TH2I h_L2_e10_medium_TRT_dEta_dPhi("h_L2_e10_medium_TRT_dEta_dPhi","#Delta#eta vs. #Delta#phi for electron - derived cluster passing L2_e10_medium_TRT;#Delta#eta;#Delta#phi",100,-0.5,0.5,100,-0.5,0.5);
   
   
   TH2I h_L2_e10_medium_AND_TRT_hitsVsHighHits("h_L2_e10_medium_AND_TRT_hitsVsHighHits","Num. TRT hits vs. TRT high threshold hits for electrons passing L2_e10_medium and _TRT;hits;high threshold hits",50,0,50,50,0,50);
   
   // EF_e10_medium_TRT plots
   TH1I h_EF_e10_medium_TRT_trtHits("h_EF_e10_medium_TRT_trtHits","Number of TRT Hits for EF_e10_medium_TRT",60,0,60);
   TProfile h_EF_e10_medium_TRT_trtHits_eta("h_EF_e10_medium_TRT_trtHits_eta","Number of TRT Hits for EF_e10_medium_TRT vs. #eta;#eta;num. TRT hits",60,-3.0,3.0);
   TH2I h_EF_e10_medium_TRT_trtHits_eta_2d("h_EF_e10_medium_TRT_trtHits_eta_2d","Number of TRT Hits for EF_e10_medium_TRT vs. #eta;#eta;num. TRT hits",60,-3.0,3.0,60,0.,60.);
   TH1I h_EF_e10_medium_TRT_trtHighHits("h_EF_e10_medium_TRT_trtHighHits","Number of TRT High Threshold Hits for EF_e10_medium_TRT",20,0,20);
   TProfile h_EF_e10_medium_TRT_trtHighHits_eta("h_EF_e10_medium_TRT_trtHighHits_eta","Number of TRT High Threshold Hits for EF_e10_medium_TRT vs. #eta;#eta;num. TRT high threshold hits",60,-3.0,3.0);
   TH2I h_EF_e10_medium_TRT_trtHighHits_eta_2d("h_EF_e10_medium_TRT_trtHighHits_eta_2d", "Number of TRT High Threshold Hits for EF_e10_medium_TRT vs. #eta;#eta;num. TRT high threshold hits",60,-3.0,3.0,60,0.,60.);
   TH1I h_EF_e10_medium_TRT_E("h_EF_e10_medium_TRT_E","Energy of EF reconstructed electrons passing EF_e10_medium_TRT;E(MeV)",500,0,500000);
   TProfile h_EF_e10_medium_TRT_frac_eta("h_EF_e10_medium_TRT_frac_eta","Ratio of TRT High Threshold Hits to Normal Hits for EF_e10_medium_TRT vs. #eta;#eta;ratio",60,-3.0,3.0);
   TH2I h_EF_e10_medium_TRT_frac_eta_2d("h_EF_e10_medium_TRT_frac_eta_2d","Ratio of TRT High Threshold Hits to Normal Hits for EF_e10_medium_TRT vs. #eta;#eta;ratio",60,-3.0,3.0,100,0.,1.);
   TH1I h_EF_e10_medium_TRT_eta("h_EF_e10_medium_TRT_eta","#eta distribution of EF reconstructed electrons passing EF_e10_medium_TRT;#eta",60,-3.0,3.0);
   TH1I h_EF_e10_medium_TRT_a0("h_EF_e10_medium_TRT_a0","a0 distribution of EF reconstructed electrons passing EF_e10_medium_TRT;a0",1000,-10.0,10.0);
   TH1I h_EF_e10_medium_TRT_z0("h_EF_e10_medium_TRT_z0","z0 distribution of EF reconstructed electrons passing EF_e10_medium_TRT;z0",1000,-10.0,10.0);
   TH1I h_EF_e10_medium_TRT_phi0("h_EF_e10_medium_TRT_phi0","phi0 distribution of EF reconstructed electrons passing EF_e10_medium_TRT;phi0",64,-PI,PI);
   
   TH2I h_EF_e10_medium_TRT_electronClusterEtaPhi("h_EF_e10_medium_TRT_electronClusterEtaPhi","EF egamma electron #eta/#phi hit map passing EF_e10_medium_TRT;#eta;#phi",60,-3.0,3.0,64,-PI,PI);
   TH2I h_EF_e10_medium_TRT_hitsVsHighHits("h_EF_e10_medium_TRT_hitsVsHighHits","Num. TRT hits vs. TRT high threshold hits for electrons passing EF_e10_medium_TRT;hits;high threshold hits",50,0,50,50,0,50);
   TH2I h_EF_e10_medium_TRT_dEta_dPhi("h_EF_e10_medium_TRT_dEta_dPhi","#Delta#eta vs. #Delta#phi for electron - derived cluster passing EF_e10_medium_TRT;#Delta#eta;#Delta#phi",100,-0.5,0.5,100,-0.5,0.5);
   
   TH2I h_EF_e10_medium_TRT_z0_a0("h_EF_e10_medium_TRT_z0_a0","z0 vs. a0 for EF_e10_medium_TRT;z0;a0",200,-10.,10.,200,-10.,10.);
   TH2I h_EF_e10_medium_TRT_trtHits_trtHitsOut("h_EF_e10_medium_TRT_trtHits_trtHitsOut","TRT hits vs. outliers for EF_e10_medium_TRT;z0;a0",60,0.,60.,60,0.,60.);
   TH2I h_EF_e10_medium_TRT_trtHighHits_trtHighHitsOut("h_EF_e10_medium_TRT_trtHighHits_trtHighHitsOut","TRT High hits vs. outliers for EF_e10_medium_TRT;z0;a0",60,0.,60.,60,0.,60.);
   
   TH2I h_EF_e10_medium_AND_TRT_hitsVsHighHits("h_EF_e10_medium_AND_TRT_hitsVsHighHits","Num. TRT hits vs. TRT high threshold hits for electrons passing EF_e10_medium and _TRT;hits;high threshold hits",50,0,50,50,0,50);
   TH1I h_EF_e10_medium_AND_TRT_a0("h_EF_e10_medium_AND_TRT_a0","a0 distribution of EF reconstructed electrons passing EF_e10_medium_TRT;a0",1000,-10.0,10.0);
   TH1I h_EF_e10_medium_AND_TRT_z0("h_EF_e10_medium_AND_TRT_z0","z0 distribution of EF reconstructed electrons passing EF_e10_medium AND _TRT;z0",1000,-10.0,10.0);
   TH1I h_EF_e10_medium_AND_TRT_phi0("h_EF_e10_medium_AND_TRT_phi0","phi0 distribution of EF reconstructed electrons passing EF_e10_medium AND _TRT;phi0",64,-PI,PI);
   TH2I h_EF_e10_medium_AND_TRT_frac_eta_2d("h_EF_e10_medium_AND_TRT_frac_eta_2d", "Ratio of TRT High Threshold Hits to Hits for EF_e10_medium AND _TRT vs. #eta;#eta;ratio",60,-3.0,3.0,100,0.,1.);
   
   TH2I h_EF_e10_medium_TRT_E_hits("h_EF_e10_medium_TRT_E_hits","EF_e10_medium_TRT: electron E vs. TRT hits;E(GeV);TRT Hits",250,0,250,60,0,60);
   TH2I h_EF_e10_medium_TRT_E_highHits("h_EF_e10_medium_TRT_E_highHits","EF_e10_medium_TRT: electron E vs. TRT high threshold hits;E(GeV);TRT High Threshold Hits",250,0,250,60,0,60);
   TH2I h_EF_e10_medium_TRT_E_hitsRatio("h_EF_e10_medium_TRT_E_hitsRatio","EF_e10_medium_TRT: electron E vs. ratio of TRT high threshold hits to hits;E(GeV);TRT High Threshold/Hits",250,0,250,100,0,1);
   
   TH2I h_EF_e10_medium_TRT_clustIndex_Repeat("h_EF_e10_medium_TRT_clustIndex_Repeat","Number of electrons per cluster;cluster;num. electrons",30,0,30,30,0,30);
   
   // EF_e10_medium_TRT2 plots
   TH1I h_EF_e10_medium_TRT2_trtHits("h_EF_e10_medium_TRT2_trtHits","Number of TRT Hits for EF_e10_medium_TRT2",60,0,60);
   TProfile h_EF_e10_medium_TRT2_trtHits_eta("h_EF_e10_medium_TRT2_trtHits_eta","Number of TRT Hits for EF_e10_medium_TRT2 vs. #eta;#eta;num. TRT hits",60,-3.0,3.0);
   TH2I h_EF_e10_medium_TRT2_trtHits_eta_2d("h_EF_e10_medium_TRT2_trtHits_eta_2d","Number of TRT Hits for EF_e10_medium_TRT2 vs. #eta;#eta;num. TRT hits",60,-3.0,3.0,60,0.,60.);
   TH1I h_EF_e10_medium_TRT2_trtHighHits("h_EF_e10_medium_TRT2_trtHighHits","Number of TRT High Threshold Hits for EF_e10_medium_TRT2",20,0,20);
   TProfile h_EF_e10_medium_TRT2_trtHighHits_eta("h_EF_e10_medium_TRT2_trtHighHits_eta","Number of TRT High Threshold Hits for EF_e10_medium_TRT2 vs. #eta;#eta;num. TRT high threshold hits",60,-3.0,3.0);
   TH2I h_EF_e10_medium_TRT2_trtHighHits_eta_2d("h_EF_e10_medium_TRT2_trtHighHits_eta_2d", "Number of TRT High Threshold Hits for EF_e10_medium_TRT2 vs. #eta;#eta;num. TRT high threshold hits",60,-3.0,3.0,60,0.,60.);
   TH1I h_EF_e10_medium_TRT2_E("h_EF_e10_medium_TRT2_E","Energy of EF reconstructed electrons passing EF_e10_medium_TRT2;E(MeV)",500,0,500000);
   TProfile h_EF_e10_medium_TRT2_frac_eta("h_EF_e10_medium_TRT2_frac_eta","Ratio of TRT High Threshold Hits to Normal Hits for EF_e10_medium_TRT2 vs. #eta;#eta;ratio",60,-3.0,3.0);
   TH2I h_EF_e10_medium_TRT2_frac_eta_2d("h_EF_e10_medium_TRT2_frac_eta_2d","Ratio of TRT High Threshold Hits to Normal Hits for EF_e10_medium_TRT2 vs. #eta;#eta;ratio",60,-3.0,3.0,100,0.,1.);
   TH1I h_EF_e10_medium_TRT2_eta("h_EF_e10_medium_TRT2_eta","#eta distribution of EF reconstructed electrons passing EF_e10_medium_TRT2;#eta",60,-3.0,3.0);
   TH1I h_EF_e10_medium_TRT2_a0("h_EF_e10_medium_TRT2_a0","a0 distribution of EF reconstructed electrons passing EF_e10_medium_TRT2;a0",1000,-10.0,10.0);
   TH1I h_EF_e10_medium_TRT2_z0("h_EF_e10_medium_TRT2_z0","z0 distribution of EF reconstructed electrons passing EF_e10_medium_TRT2;z0",1000,-10.0,10.0);
   TH1I h_EF_e10_medium_TRT2_phi0("h_EF_e10_medium_TRT2_phi0","phi0 distribution of EF reconstructed electrons passing EF_e10_medium_TRT2;phi0",64,-PI,PI);
   
   TH2I h_EF_e10_medium_TRT2_electronClusterEtaPhi("h_EF_e10_medium_TRT2_electronClusterEtaPhi","EF egamma electron #eta/#phi hit map passing L2_e10_medium_TRT2;#eta;#phi",60,-3.0,3.0,64,-PI,PI);
   TH2I h_EF_e10_medium_TRT2_hitsVsHighHits("h_EF_e10_medium_TRT2_hitsVsHighHits","Num. TRT hits vs. TRT high threshold hits for electrons passing EF_e10_medium_TRT2;hits;high threshold hits",50,0,50,50,0,50);
   TH2I h_EF_e10_medium_TRT2_dEta_dPhi("h_EF_e10_medium_TRT2_dEta_dPhi","#Delta#eta vs. #Delta#phi for electron - derived cluster passing EF_e10_medium_TRT2;#Delta#eta;#Delta#phi",100,-0.5,0.5,100,-0.5,0.5);
   
   TH2I h_EF_e10_medium_TRT2_z0_a0("h_EF_e10_medium_TRT2_z0_a0","z0 vs. a0 for EF_e10_medium_TRT2;z0;a0",200,-10.,10.,200,-10.,10.);
   
   
   TH2I h_EF_e10_medium_TRT2_E_hits("h_EF_e10_medium_TRT2_E_hits","EF_e10_medium_TRT2: electron E vs. TRT hits;E(GeV);TRT Hits",250,0,250,60,0,60);
   TH2I h_EF_e10_medium_TRT2_E_highHits("h_EF_e10_medium_TRT2_E_highHits","EF_e10_medium_TRT2: electron E vs. TRT high threshold hits;E(GeV);TRT High Threshold Hits",250,0,250,60,0,60);
   TH2I h_EF_e10_medium_TRT2_E_hitsRatio("h_EF_e10_medium_TRT2_E_hitsRatio","EF_e10_medium_TRT2: electron E vs. ratio of TRT high threshold hits to hits;E(GeV);TRT High Threshold/Hits",250,0,250,100,0,1);
   
   TH2I h_EF_e10_medium_AND_TRT2_hitsVsHighHits("h_EF_e10_medium_AND_TRT2_hitsVsHighHits","Num. TRT hits vs. TRT high threshold hits for electrons passing EF_e10_medium and _TRT2;hits;high threshold hits",50,0,50,50,0,50);
   
   TH1I h_EF_e10_medium_AND_TRT2_a0("h_EF_e10_medium_AND_TRT2_a0","a0 distribution of EF reconstructed electrons passing EF_e10_medium_TRT2;a0",1000,-10.0,10.0);
   TH1I h_EF_e10_medium_AND_TRT2_z0("h_EF_e10_medium_AND_TRT2_z0","z0 distribution of EF reconstructed electrons passing EF_e10_medium AND _TRT2;z0",1000,-10.0,10.0);
   
   
   
   enum{
      L1_EM5=0,
      L2_e10_medium,
      L2_e10_medium_SiTrk,
      L2_e10_medium_IDTrkNoCut,
      L2_e10_medium_TRT,
      EF_e10_medium,
      EF_e10_medium_SiTrk,
      EF_e10_medium_IDTrkNoCut,
      EF_e10_medium_TRT,
      EF_e10_medium_TRT2,
      TOTAL_ENUM
   };
   
   TH2I h_chainHitsOverlap("h_chainHitsOverlap","Event Overlap within HLT chains",TOTAL_ENUM,0,TOTAL_ENUM,TOTAL_ENUM,0,TOTAL_ENUM);
   char binLabels[TOTAL_ENUM][50] = {"L1_EM5","L2_e10_medium","L2_e10_medium_SiTrk",
      "L2_e10_medium_IDTrkNoCut","L2_e10_medium_TRT","EF_e10_medium","EF_e10_medium_SiTrk",
      "EF_e10_medium_IDTrkNoCut","EF_e10_medium_TRT","EF_e10_medium_TRT2"};
      for(unsigned int i=0;i<TOTAL_ENUM;i++){
      h_chainHitsOverlap.GetXaxis()->SetBinLabel(i+1,binLabels[i]);
      h_chainHitsOverlap.GetYaxis()->SetBinLabel(i+1,binLabels[i]);
   }
   
//    const float fracTRTHits1Cut = 0.1;
//    const float fracTRTHits2Cut = 0.08;
//    const float fracTRTHits3Cut = 0.12;
//    std::vector<float> etaRange;
//    etaRange.push_back(0.00);
//    etaRange.push_back(0.80);
//    etaRange.push_back(1.37);
//    etaRange.push_back(1.50);
//    etaRange.push_back(1.52);
//    etaRange.push_back(1.80);
//    etaRange.push_back(2.00);
//    etaRange.push_back(2.35);
//    etaRange.push_back(2.50);
   
   const Long64_t totalEntries = tree->GetEntries();
   const Long64_t onePercent = (Long64_t)((float)totalEntries*0.01 + 1.0);
   for(Long64_t entry=0;entry<totalEntries;++entry){
      
      if( !(entry % onePercent) ){
         std::cout << " PercentDone: " << (int)(((float)entry/(float)totalEntries)*100.0) << std::endl;
      }
      
      tree->LoadTree(entry);
      
      
      for(unsigned int electron=0;electron<tree->OFFegamma_nEGamma;++electron){
         if(tree->OFFegamma_isElectron->at(electron))
            std::cout << "  electron: " << electron << std::endl;
         else if(tree->OFFegamma_isPhoton->at(electron))
            std::cout << "  photon: " << electron << std::endl;
         std::cout << "    eta: " << tree->OFFegamma_eta->at(electron) << " phi: " << tree->OFFegamma_phi->at(electron) << std::endl;
         std::cout << "    E: " << tree->OFFegamma_e->at(electron) << std::endl;
         std::cout << "    pid: " << tree->OFFegamma_PID->at(electron) << " author: " << tree->OFFegamma_author->at(electron) << std::endl;
         int clusterIndex = tree->OFFegamma_ClusIndex->at(electron);
         std::cout << "   ClusterIndex: " << clusterIndex << " of " << tree->OFFCaloCluster_nClus << std::endl;
         if(clusterIndex >= 0){
            std::cout << "    eta: " << tree->OFFCaloCluster_eta->at(clusterIndex) << " phi: " << tree->OFFCaloCluster_phi->at(clusterIndex) << std::endl;
            std::cout << "    E: " << tree->OFFCaloCluster_energy->at(clusterIndex) << std::endl;
         }
         int trackIndex = tree->OFFegamma_TrackIndex->at(electron);
         std::cout << "   TrackIndex: " << trackIndex << " of " << tree->OFFTrackParticle_nTrack << std::endl;
         if(trackIndex >= 0){
            std::cout << "    eta: " << tree->OFFTrackParticle_eta->at(trackIndex) << " phi: " << tree->OFFTrackParticle_phi->at(trackIndex) << std::endl;
            std::cout << "    slice: " << tree->OFFTrackParticle_slice->at(trackIndex) << std::endl;
         }
         std::cout << "   OFFegamma_trigChain: " << std::endl;
         for(unsigned int i=0;i<tree->OFFegamma_trigChain->at(electron).size();++i){
            std::cout << "   " << tree->OFFegamma_trigChain->at(electron)[i] << std::endl;
         }
         std::cout << "   OFFegamma_trigDec: " << std::endl;
         for(unsigned int i=0;i<tree->OFFegamma_trigDec->at(electron).size();++i){
            std::cout << "   " << tree->OFFegamma_trigDec->at(electron)[i] << std::endl;
         }
         std::cin.get();
      }// OFFegamma
      
      
      if((*tree->Trigger_L2passed)["L2_e10_medium"]){
         
         for(unsigned int electron=0;electron<tree->TrigElectron_nTrigElectron;++electron){
            
            // if this electron did not pass the trigger, skip it.
            if(!tree->ObjPassedTrigger(tree->TrigElectron_trigRes.at(electron),"L2_e10_medium"))
               continue;
            
            // if there is no associated track, skip electron
            const int trackIndex = tree->TrigElectron_TrackIndex->at(electron);
            if(trackIndex == -1) continue;
            
            const int clusterIndex = tree->TrigElectron_ClusIndex->at(electron);
            const float clusterEta  = tree->TrigEMCluster_eta->at(clusterIndex);
            const float clusterPhi  = tree->TrigEMCluster_phi->at(clusterIndex);
            
            const float electronEta = tree->TrigElectron_Eta->at(electron);
            const float electronPhi = tree->TrigElectron_Phi->at(electron);
            
            const float electronE = tree->TrigElectron_E->at(electron);
            h_L2_e10_medium_E.Fill(electronE);
            h_L2_e10_medium_eta.Fill(electronEta);
            
            const float dEta = electronEta-clusterEta;
            const float dPhi = electronPhi-clusterPhi;
            h_L2_e10_medium_dEta_dPhi.Fill(dEta,dPhi);
            
         }
      }// end if(L2_e10_medium)
      
      if((*tree->Trigger_EFpassed)["EF_e10_medium"]){
         
         for(unsigned int electron=0;electron<tree->EFegamma_nEGamma;++electron){
            
            //only electrons please
            if(!tree->EFegamma_isElectron->at(electron)) continue;
            
            // if this electron did not pass the electronger, skip it.
            if(!tree->ObjPassedTrigger(tree->EFegamma_trigRes.at(electron),"EF_e10_medium"))
               continue;
            
            // if there is no associated track, skip electron
            const int trackIndex = tree->EFegamma_TrackIndex->at(electron);
            if(trackIndex == -1) continue;
            
            const int clusterIndex = tree->EFegamma_ClusIndex->at(electron);
            const float clusterEta  = tree->EFCaloCluster_eta->at(clusterIndex);
            const float clusterPhi  = tree->EFCaloCluster_phi->at(clusterIndex);
            
            const float electronEta = tree->EFegamma_eta->at(electron);
            const float electronPhi = tree->EFegamma_phi->at(electron);
            
            const float electronE = tree->EFegamma_e->at(electron);
            
            h_EF_e10_medium_E.Fill(electronE);
            h_EF_e10_medium_eta.Fill(electronEta);
            
            const float dEta = electronEta-clusterEta;
            const float dPhi = electronPhi-clusterPhi;
            h_EF_e10_medium_dEta_dPhi.Fill(dEta,dPhi);
         }// end for(electron)
         
         
      }// end if(EF_e10_medium)
      
      
      // did this event pass L2_e10_medium_TRT
      if((*tree->Trigger_L2passed)["L2_e10_medium_TRT"]){
         
         for(unsigned int electron=0;electron<tree->TrigElectron_nTrigElectron;++electron){
            
            // if this electron did not pass the trigger, skip it.
            if(!tree->ObjPassedTrigger(tree->TrigElectron_trigRes.at(electron),"L2_e10_medium_TRT"))
               continue;
            
            // if there is no associated  track, skip electron
            const int trackIndex = tree->TrigElectron_TrackIndex->at(electron);
            if(trackIndex == -1) continue;
            
            const int clusterIndex  = tree->TrigElectron_ClusIndex->at(electron);
            const float clusterEta   = tree->TrigEMCluster_eta->at(clusterIndex);
            const float clusterPhi   = tree->TrigEMCluster_phi->at(clusterIndex);
            const float electronEta = tree->TrigElectron_Eta->at(electron);
            const float electronPhi = tree->TrigElectron_Phi->at(electron);
            const float electronE   = tree->TrigElectron_E->at(electron);
            const int trtHits       = tree->TrigInDetTrack_NStrawHits->at(trackIndex);
            const int trtHighHits   = tree->TrigInDetTrack_NTRHits->at(trackIndex);
            
            h_L2_e10_medium_TRT_trtHits.Fill(trtHits);
            h_L2_e10_medium_TRT_trtHighHits.Fill(trtHighHits);
            h_L2_e10_medium_TRT_electronClusterEtaPhi.Fill(electronEta,electronPhi);
            h_L2_e10_medium_TRT_E.Fill(electronE);
            
            h_L2_e10_medium_TRT_trtHits_eta.Fill(electronEta,trtHits);
            h_L2_e10_medium_TRT_trtHits_eta_2d.Fill(electronEta,trtHits);
            h_L2_e10_medium_TRT_trtHighHits_eta.Fill(electronEta,trtHighHits);
            h_L2_e10_medium_TRT_trtHighHits_eta_2d.Fill(electronEta,trtHighHits);
            
            float ratio = 0;
            if(trtHits != 0)
               ratio = (float)trtHighHits/(float)trtHits;
            h_L2_e10_medium_TRT_frac_eta.Fill(electronEta,ratio);
            h_L2_e10_medium_TRT_frac_eta_2d.Fill(electronEta,ratio);
            
            h_L2_e10_medium_TRT_eta.Fill(electronEta);
            
            h_L2_e10_medium_TRT_hitsVsHighHits.Fill(trtHits,trtHighHits);
            
            const float dEta = electronEta-clusterEta;
            const float dPhi = electronPhi-clusterPhi;
            h_L2_e10_medium_TRT_dEta_dPhi.Fill(dEta,dPhi);
         }// end for(electron)
      }// end if(L2_e10_medium_TRT)
      
      
      // did this event pass EF_e10_medium_TRT
      if((*tree->Trigger_EFpassed)["EF_e10_medium_TRT"]){
         
         vector<int> ePerCluster;
         ePerCluster.resize(tree->EFCaloCluster_nClus,0);
         for(unsigned int electron=0;electron<tree->EFegamma_nEGamma;++electron){
            
            //only electrons please
            if(!tree->EFegamma_isElectron->at(electron)) continue;
            
            // skip electrons with no associated track
            const int trackIndex = tree->EFegamma_TrackIndex->at(electron);
            if(trackIndex == -1) continue;
            
            // if this electron did not pass the electron trigger, skip it.
            if(!tree->ObjPassedTrigger(tree->EFegamma_trigRes.at(electron),"EF_e10_medium_TRT"))
               continue;
            
            const int clusterIndex  = tree->EFegamma_ClusIndex->at(electron);
            ePerCluster[clusterIndex]++;
            const float clusterEta   = tree->EFCaloCluster_eta->at(clusterIndex);
            const float clusterPhi   = tree->EFCaloCluster_phi->at(clusterIndex);
            const float electronEta = tree->EFegamma_eta->at(electron);
            const float electronPhi = tree->EFegamma_phi->at(electron);
            const float electronE   = tree->EFegamma_e->at(electron);
            const int trtHits       = tree->EFegamma_nTRT->at(electron);
            const int trtHighHits   = tree->EFegamma_nTRThigh->at(electron);
            const float a0          = tree->EFTrackParticle_a0->at(trackIndex);
            const float z0          = tree->EFTrackParticle_z0->at(trackIndex);
            const float phi0        = tree->EFTrackParticle_phi0->at(trackIndex);
            const int trtHitsOut    = tree->EFTrackParticle_TRT_out->at(trackIndex);
            const int trtHighHitsOut = tree->EFTrackParticle_TRT_highOut->at(trackIndex);
            
            h_EF_e10_medium_TRT_trtHits.Fill(trtHits);
            h_EF_e10_medium_TRT_trtHighHits.Fill(trtHighHits);
            h_EF_e10_medium_TRT_E.Fill(electronE);
            
            h_EF_e10_medium_TRT_electronClusterEtaPhi.Fill(electronEta,electronPhi);
            
            h_EF_e10_medium_TRT_trtHits_eta.Fill(electronEta,trtHits);
            h_EF_e10_medium_TRT_trtHighHits_eta.Fill(electronEta,trtHighHits);
            h_EF_e10_medium_TRT_trtHits_eta_2d.Fill(electronEta,trtHits);
            h_EF_e10_medium_TRT_trtHighHits_eta_2d.Fill(electronEta,trtHighHits);
            
            
            float ratio = 0;
            if(trtHits > 0)
               ratio = (float)trtHighHits/(float)trtHits;
            if(ratio != 0){
               h_EF_e10_medium_TRT_frac_eta.Fill(electronEta,ratio);
               h_EF_e10_medium_TRT_frac_eta_2d.Fill(electronEta,ratio);
               h_EF_e10_medium_TRT_E_hitsRatio.Fill(electronE/1000.,ratio);

            }
            
            h_EF_e10_medium_TRT_eta.Fill(electronEta);
            
            h_EF_e10_medium_TRT_hitsVsHighHits.Fill(trtHits,trtHighHits);
            
            const float dEta = electronEta-clusterEta;
            const float dPhi = electronPhi-clusterPhi;
            h_EF_e10_medium_TRT_dEta_dPhi.Fill(dEta,dPhi);
            
            h_EF_e10_medium_TRT_a0.Fill(a0);
            h_EF_e10_medium_TRT_z0.Fill(z0);
            h_EF_e10_medium_TRT_phi0.Fill(phi0);
            
            h_EF_e10_medium_TRT_z0_a0.Fill(z0,a0);
            h_EF_e10_medium_TRT_trtHits_trtHitsOut.Fill(trtHits,trtHitsOut);
            h_EF_e10_medium_TRT_trtHighHits_trtHighHitsOut.Fill(trtHighHits,trtHighHitsOut);
            
            h_EF_e10_medium_TRT_E_hits.Fill(electronE/1000.,trtHits);
            h_EF_e10_medium_TRT_E_highHits.Fill(electronE/1000.,trtHighHits);
            
            
         }
         
         for(unsigned int clusterIndex=0;clusterIndex<ePerCluster.size();clusterIndex++)
            if(ePerCluster[clusterIndex] > 0)
               h_EF_e10_medium_TRT_clustIndex_Repeat.Fill(clusterIndex,ePerCluster[clusterIndex]);
         
      }// end if(EF_e10_medium_TRT)
      
      
      // EF_e10_medium_TRT2
      bool passed_EF_e10_medium_TRT2=false;
      if((*tree->Trigger_EFpassed)["EF_e10_medium_TRT"]){
         
         for(unsigned int electron=0;electron<tree->EFegamma_nEGamma;++electron){
            
            //only electrons please
            if(!tree->EFegamma_isElectron->at(electron)) continue;
            
            // skip electrons with no associated track
            const int trackIndex = tree->EFegamma_TrackIndex->at(electron);
            if(trackIndex == -1) continue;
            
            // if this electron did not pass the electron trigger, skip it.
            if(!tree->ObjPassedTrigger(tree->EFegamma_trigRes.at(electron),"EF_e10_medium_TRT"))
               continue;
            
            const int trtHits = tree->EFegamma_nTRT->at(electron);
            const int trtHighHits = tree->EFegamma_nTRThigh->at(electron);
            const float electronEta  = tree->EFegamma_eta->at(electron);
            const float feta = fabs(electronEta);
            float ratio = 0;
            if(trtHits > 0)
               ratio = (float)trtHighHits/(float)trtHits;
            
            // make across the board cut at ratio >= 0.1
            if( trtHits == 0 || trtHighHits == 0 ) continue;
            else if(      (0.7 >  feta               && trtHits < 25)
                  || (0.7 <= feta && feta < 1.4 && trtHits < 14)
                  || (1.4 <= feta && feta < 1.8 && trtHits < 25)
                  || (1.8 <= feta               && trtHits < 14)) continue;
            else if( ( 0.8 < feta && ratio < 0.09) 
                  || ( feta <= 0.8 && ratio < 0.05) ) continue;
            else passed_EF_e10_medium_TRT2 = true;
            
            
            const int clusterIndex = tree->EFegamma_ClusIndex->at(electron);
            const float clusterEta   = tree->EFCaloCluster_eta->at(clusterIndex);
            const float clusterPhi   = tree->EFCaloCluster_phi->at(clusterIndex);
            const float electronPhi  = tree->EFegamma_phi->at(electron);
            const float electronE    = tree->EFegamma_e->at(electron);
            const float a0           = tree->EFTrackParticle_a0->at(trackIndex);
            const float z0           = tree->EFTrackParticle_z0->at(trackIndex);
            const float phi0         = tree->EFTrackParticle_phi0->at(trackIndex);
            const int trtHitsOut     = tree->EFTrackParticle_TRT_out->at(trackIndex);
            const int trtHighHitsOut = tree->EFTrackParticle_TRT_highOut->at(trackIndex);
            
            if(ratio != 0){
               h_EF_e10_medium_TRT2_frac_eta.Fill(electronEta,ratio);
               h_EF_e10_medium_TRT2_frac_eta_2d.Fill(electronEta,ratio);
               h_EF_e10_medium_TRT2_E_hitsRatio.Fill(electronE/1000.,ratio);
            }
            h_EF_e10_medium_TRT2_trtHits.Fill(trtHits);
            h_EF_e10_medium_TRT2_trtHighHits.Fill(trtHighHits);
            h_EF_e10_medium_TRT2_E.Fill(electronE);
            
            h_EF_e10_medium_TRT2_electronClusterEtaPhi.Fill(electronEta,electronPhi);
            
            h_EF_e10_medium_TRT2_trtHits_eta.Fill(electronEta,trtHits);
            h_EF_e10_medium_TRT2_trtHighHits_eta.Fill(electronEta,trtHighHits);
            h_EF_e10_medium_TRT2_trtHits_eta_2d.Fill(electronEta,trtHits);
            h_EF_e10_medium_TRT2_trtHighHits_eta_2d.Fill(electronEta,trtHighHits);
            
            h_EF_e10_medium_TRT2_eta.Fill(electronEta);
            
            h_EF_e10_medium_TRT2_hitsVsHighHits.Fill(trtHits,trtHighHits);
            
            const float dEta = electronEta-clusterEta;
            const float dPhi = electronPhi-clusterPhi;
            h_EF_e10_medium_TRT2_dEta_dPhi.Fill(dEta,dPhi);
            
            h_EF_e10_medium_TRT2_a0.Fill(a0);
            h_EF_e10_medium_TRT2_z0.Fill(z0);
            h_EF_e10_medium_TRT2_phi0.Fill(phi0);
            
            h_EF_e10_medium_TRT2_z0_a0.Fill(z0,a0);
            
            h_EF_e10_medium_TRT2_E_hits.Fill(electronE/1000.,trtHits);
            h_EF_e10_medium_TRT2_E_highHits.Fill(electronE/1000.,trtHighHits);
         } 
      }// end if(EF_e10_medium_TRT2)
      
      
      if((*tree->Trigger_L2passed)["L2_e10_medium"] &&
           (*tree->Trigger_L2passed)["L2_e10_medium_TRT"])
      {
         // I don't want to double count so I keep track of the cluster
         // that each electron is associated with.
         std::vector<bool> usedCluster(tree->TrigElectron_nTrigElectron,false);
         
         for(unsigned int emcl=0;emcl<tree->TrigElectron_nTrigElectron;++emcl){
            // if there is no associated  track, skip electron
            int trackIndex = tree->TrigElectron_TrackIndex->at(emcl);
            if(trackIndex == -1) continue;
            
            int clusterIndex = tree->TrigElectron_ClusIndex->at(emcl);
            if(usedCluster[clusterIndex]) continue;
            else usedCluster[clusterIndex] = true;
            
            const int trtHits = tree->TrigInDetTrack_NStrawHits->at(trackIndex);
            const int trtHighHits = tree->TrigInDetTrack_NTRHits->at(trackIndex);
            
            if(trtHits>0 && trtHighHits>0)
               h_L2_e10_medium_AND_TRT_hitsVsHighHits.Fill(trtHits,trtHighHits);
         }// end for(emcl)
      }// end if(L2_e10_medium && L2_e10_medium_TRT)
      
      if((*tree->Trigger_EFpassed)["EF_e10_medium"] &&
           (*tree->Trigger_EFpassed)["EF_e10_medium_TRT"])
      {
         // I don't want to double count so I keep track of the cluster
         // that each electron is associated with.
         std::vector<bool> usedCluster(tree->EFegamma_nEGamma,false);
         
         for(unsigned int trig=0;trig<tree->EFegamma_nEGamma;++trig){
            
            //only electrons please
            if(!tree->EFegamma_isElectron->at(trig)) continue;
            
            const int clusterIndex = tree->EFegamma_ClusIndex->at(trig);
            if(usedCluster[clusterIndex]) continue;
            else usedCluster[clusterIndex] = true;
            
            // skip electrons without tracks
            const int trackIndex = tree->EFegamma_TrackIndex->at(trig);
            if(trackIndex == -1) continue;
            
            const int trtHits = tree->EFegamma_nTRT->at(trig);
            const int trtHighHits = tree->EFegamma_nTRThigh->at(trig);
            float ratio = 0;
            if(trtHits != 0)
               ratio = (float)trtHighHits/(float)trtHits;
            const float eta = tree->EFegamma_eta->at(trig);
            
            if(trtHits>0 && trtHighHits>0){
               h_EF_e10_medium_AND_TRT_hitsVsHighHits.Fill(trtHits,trtHighHits);
               h_EF_e10_medium_AND_TRT_a0.Fill(tree->EFTrackParticle_a0->at(trackIndex));
               h_EF_e10_medium_AND_TRT_z0.Fill(tree->EFTrackParticle_z0->at(trackIndex));
               h_EF_e10_medium_AND_TRT_phi0.Fill(tree->EFTrackParticle_phi0->at(trackIndex));
               h_EF_e10_medium_AND_TRT_frac_eta_2d.Fill(eta,ratio);
            }
         } // end for(trig)
      } // end if(EF_e10_medium && EF_e10_medium_TRT)
      
      
      std::vector<int> chain(TOTAL_ENUM,0);
      // make plot of overlapping entries vs. chain
      if((*tree->Trigger_L1passed)["L1_EM5"])
         chain[L1_EM5] = 1;
      if((*tree->Trigger_L2passed)["L2_e10_medium"])
         chain[L2_e10_medium] = 1;
      if((*tree->Trigger_L2passed)["L2_e10_medium_SiTrk"])
         chain[L2_e10_medium_SiTrk] = 1;
      if((*tree->Trigger_L2passed)["L2_e10_medium_IDTrkNoCut"])
         chain[L2_e10_medium_IDTrkNoCut] = 1;
      if((*tree->Trigger_L2passed)["L2_e10_medium_TRT"])
         chain[L2_e10_medium_TRT] = 1;
      if((*tree->Trigger_EFpassed)["EF_e10_medium"])
         chain[EF_e10_medium] = 1;
      if((*tree->Trigger_EFpassed)["EF_e10_medium_SiTrk"])
         chain[EF_e10_medium_SiTrk] = 1;
      if((*tree->Trigger_EFpassed)["EF_e10_medium_IDTrkNoCut"])
         chain[EF_e10_medium_IDTrkNoCut] = 1;
      if((*tree->Trigger_EFpassed)["EF_e10_medium_TRT"])
         chain[EF_e10_medium_TRT] = 1;
      if(passed_EF_e10_medium_TRT2)
         chain[EF_e10_medium_TRT2] = 1;
      
      for(unsigned int i=0;i<chain.size();++i){
         for(unsigned int j=0;j<chain.size();++j){
            if(chain[i] == 1 && chain[j] == 1)
               h_chainHitsOverlap.Fill(i,j);
         }
      }
      
   }// end for(entry)
   
   TFile file("trtTrackTest.root","RECREATE");
   
   h_chainHitsOverlap.Write();
   
   // L2_e10_medium plots
   file.mkdir("L2_e10_medium");
   file.cd("L2_e10_medium");
   h_L2_e10_medium_E.Write();
   h_L2_e10_medium_eta.Write();
   h_L2_e10_medium_dEta_dPhi.Write();
   
   
   // EF_e10_medium plots
   file.mkdir("EF_e10_medium");
   file.cd("EF_e10_medium");
   h_EF_e10_medium_E.SetLineColor(kRed);
   h_EF_e10_medium_E.Write();
   h_EF_e10_medium_eta.SetLineColor(kRed);
   h_EF_e10_medium_eta.Write();
   h_EF_e10_medium_dEta_dPhi.Write();
   
   
   // L2_e10_medium_TRT plots
   file.mkdir("L2_e10_medium_TRT");
   file.cd("L2_e10_medium_TRT");
   h_L2_e10_medium_TRT_trtHits.Write();
   h_L2_e10_medium_TRT_trtHighHits.Write();
   h_L2_e10_medium_TRT_electronClusterEtaPhi.Write();
   h_L2_e10_medium_TRT_E.Write();
   h_L2_e10_medium_TRT_trtHits_eta.Write();
   h_L2_e10_medium_TRT_trtHits_eta_2d.Write();
   h_L2_e10_medium_TRT_trtHighHits_eta.Write();
   h_L2_e10_medium_TRT_trtHighHits_eta_2d.Write();
   h_L2_e10_medium_TRT_frac_eta.Write();
   h_L2_e10_medium_TRT_frac_eta_2d.Write();
   h_L2_e10_medium_TRT_eta.Write();
   h_L2_e10_medium_TRT_hitsVsHighHits.Write();
   h_L2_e10_medium_TRT_dEta_dPhi.Write();
   
   // EF_e10_medium_TRT plots
   file.mkdir("EF_e10_medium_TRT");
   file.cd("EF_e10_medium_TRT");
   h_EF_e10_medium_TRT_trtHits.SetLineColor(kRed);
   h_EF_e10_medium_TRT_trtHits.Write();
   h_EF_e10_medium_TRT_trtHighHits.SetLineColor(kRed);
   h_EF_e10_medium_TRT_trtHighHits.Write();
   h_EF_e10_medium_TRT_electronClusterEtaPhi.Write();
   h_EF_e10_medium_TRT_E.SetLineColor(kRed);
   h_EF_e10_medium_TRT_E.Write();
   h_EF_e10_medium_TRT_trtHits_eta.SetMarkerColor(kRed);
   h_EF_e10_medium_TRT_trtHits_eta.SetLineColor(kRed);
   h_EF_e10_medium_TRT_trtHits_eta.Write();
   h_EF_e10_medium_TRT_trtHits_eta_2d.Write();
   h_EF_e10_medium_TRT_trtHighHits_eta.SetMarkerColor(kRed);
   h_EF_e10_medium_TRT_trtHighHits_eta.SetLineColor(kRed);
   h_EF_e10_medium_TRT_trtHighHits_eta.Write();
   h_EF_e10_medium_TRT_trtHighHits_eta_2d.Write();
   h_EF_e10_medium_TRT_frac_eta.SetMarkerColor(kRed);
   h_EF_e10_medium_TRT_frac_eta.SetLineColor(kRed);
   h_EF_e10_medium_TRT_frac_eta.Write();
   h_EF_e10_medium_TRT_frac_eta_2d.Write();
   h_EF_e10_medium_TRT_eta.SetLineColor(kRed);
   h_EF_e10_medium_TRT_eta.Write();
   h_EF_e10_medium_TRT_hitsVsHighHits.Write();
   h_EF_e10_medium_TRT_dEta_dPhi.Write();
   h_EF_e10_medium_TRT_a0.SetLineColor(kRed);
   h_EF_e10_medium_TRT_a0.Write();
   h_EF_e10_medium_TRT_z0.SetLineColor(kRed);
   h_EF_e10_medium_TRT_z0.Write();
   h_EF_e10_medium_TRT_phi0.SetLineColor(kRed);
   h_EF_e10_medium_TRT_phi0.Write();
   h_EF_e10_medium_TRT_z0_a0.Write();
   h_EF_e10_medium_TRT_trtHits_trtHitsOut.Write();
   h_EF_e10_medium_TRT_E_hits.Write();
   h_EF_e10_medium_TRT_E_highHits.Write();
   h_EF_e10_medium_TRT_E_hitsRatio.Write();
   h_EF_e10_medium_TRT_clustIndex_Repeat.Write();
   
   // EF_e10_medium_TRT2 plots
   file.mkdir("EF_e10_medium_TRT2");
   file.cd("EF_e10_medium_TRT2");
   h_EF_e10_medium_TRT2_trtHits.SetLineColor(kRed);
   h_EF_e10_medium_TRT2_trtHits.Write();
   h_EF_e10_medium_TRT2_trtHighHits.SetLineColor(kRed);
   h_EF_e10_medium_TRT2_trtHighHits.Write();
   h_EF_e10_medium_TRT2_electronClusterEtaPhi.Write();
   h_EF_e10_medium_TRT2_E.SetLineColor(kRed);
   h_EF_e10_medium_TRT2_E.Write();
   h_EF_e10_medium_TRT2_trtHits_eta.SetMarkerColor(kRed);
   h_EF_e10_medium_TRT2_trtHits_eta.SetLineColor(kRed);
   h_EF_e10_medium_TRT2_trtHits_eta.Write();
   h_EF_e10_medium_TRT2_trtHits_eta_2d.Write();
   h_EF_e10_medium_TRT2_trtHighHits_eta.SetMarkerColor(kRed);
   h_EF_e10_medium_TRT2_trtHighHits_eta.SetLineColor(kRed);
   h_EF_e10_medium_TRT2_trtHighHits_eta.Write();
   h_EF_e10_medium_TRT2_trtHighHits_eta_2d.Write();
   h_EF_e10_medium_TRT2_frac_eta.SetMarkerColor(kRed);
   h_EF_e10_medium_TRT2_frac_eta.SetLineColor(kRed);
   h_EF_e10_medium_TRT2_frac_eta.Write();
   h_EF_e10_medium_TRT2_frac_eta_2d.Write();
   h_EF_e10_medium_TRT2_eta.SetLineColor(kRed);
   h_EF_e10_medium_TRT2_eta.Write();
   h_EF_e10_medium_TRT2_hitsVsHighHits.Write();
   h_EF_e10_medium_TRT2_dEta_dPhi.Write();
   h_EF_e10_medium_TRT2_a0.SetLineColor(kRed);
   h_EF_e10_medium_TRT2_a0.Write();
   h_EF_e10_medium_TRT2_z0.SetLineColor(kRed);
   h_EF_e10_medium_TRT2_z0.Write();
   h_EF_e10_medium_TRT2_phi0.SetLineColor(kRed);
   h_EF_e10_medium_TRT2_phi0.Write();
   h_EF_e10_medium_TRT2_z0_a0.Write();
   h_EF_e10_medium_TRT2_E_hits.Write();
   h_EF_e10_medium_TRT2_E_highHits.Write();
   h_EF_e10_medium_TRT2_E_hitsRatio.Write();
   
   
   // L2_e10_medium and L2_e10_medium_TRT plots
   file.mkdir("L2_e10_medium_AND_TRT");
   file.cd("L2_e10_medium_AND_TRT");
   h_L2_e10_medium_AND_TRT_hitsVsHighHits.Write();
   
   // EF_e10_medium and EF_e10_medium_TRT plots
   file.mkdir("EF_e10_medium_AND_TRT");
   file.cd("EF_e10_medium_AND_TRT");
   h_EF_e10_medium_AND_TRT_hitsVsHighHits.Write();
   h_EF_e10_medium_AND_TRT_a0.Write();
   h_EF_e10_medium_AND_TRT_z0.Write();
   h_EF_e10_medium_AND_TRT_phi0.Write();
   h_EF_e10_medium_AND_TRT_frac_eta_2d.Write();
   
   
   file.Close();
}
