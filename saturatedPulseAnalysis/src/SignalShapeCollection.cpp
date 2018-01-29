
#include "SignalShapeCollection.h"

#include "SaturatedBcid.h"
#include "SaturatedBcidCollection.h"
#include "FcalLayer.h"
#include "CaloDivision.h"
#include "TDirectory.h"

SignalShapeCollection::SignalShapeCollection(std::vector<ShapeMakerTree*>* trees,RUN_TYPE runType,L1CaloChannelMap* map)
{
   if(map == 0){
      m_l1map = new L1CaloChannelMap;
      m_l1map->SetPpmEnable(true);
      m_l1map->SetCpmEnable(false);
      m_l1map->SetJemEnable(false);
      m_l1map->SetTcppEnable(false);
      m_deleteChannelMap = true;
   }
   else{
      m_l1map = map;
   }
   
   if(runType == TILE_RUN){
      m_tileRun = true;
      m_larRun = false;
   }
   else if(runType == LAR_RUN){
      m_tileRun = false;
      m_larRun = true;
   }
   else{
      std::cerr << "[SignalShapeCollection::SignalShapeCollection] ERROR, Run Type must be TILE_RUN or LAR_RUN.\n";
      return;
   }
   
   m_v_trees = trees;
   
   m_s_outputPath = ".";
   
   m_s_treeFile = "signalAnalysis.root";
   m_s_treeFilename = m_s_outputPath + "/" + m_s_treeFile;
   
   m_s_rawCanvasDirectory          = "combinedRawCanvas";
   m_s_processedCanvasDirectory    = "combinedProcessedCanvas";
   m_s_summaryPlotsDirectory       = "Summary";
   m_s_rawDacVsAdcDirectory        = "rawDacVsAdc";
   m_s_processedDacVsAdcDirectory  = "processedDacVsAdc";
   m_s_rawPeakVsTs1Directory       = "rawPeakVsTs1";
   m_s_rawPeakVsTs2Directory       = "rawPeakVsTs2";
   m_s_processedPeakVsTs1Directory = "processedPeakVsTs1";
   m_s_processedPeakVsTs2Directory = "processedPeakVsTs2";
   
   m_s_databaseFilename = "satBcidDatabaseFile.txt";
   
   /// Raw Plots
   
   PixelMap<unsigned short int>::pixel_size triggerTower = PixelMap<unsigned short int>::TrigTower;
   m_pm_raw_em_satHigh = new PixelMap<unsigned short int>(triggerTower);
   m_pm_raw_em_satLow  = new PixelMap<unsigned short int>(triggerTower);
   m_pm_raw_em_satLvl  = new PixelMap<unsigned short int>(triggerTower);
   m_pm_raw_had_satHigh = new PixelMap<unsigned short int>(triggerTower);
   m_pm_raw_had_satLow  = new PixelMap<unsigned short int>(triggerTower);
   m_pm_raw_had_satLvl  = new PixelMap<unsigned short int>(triggerTower);
   
   m_h_raw_satHigh = new TH1I("raw_satHigh","SatHigh Derived from Raw Signal Shapes;satHigh",1024,0,1024);
   m_h_raw_satLow = new TH1I("raw_satLow","SatLow Derived from Raw Signal Shapes;satLow",1024,0,1024);
   m_h_raw_satLvl = new TH1I("raw_satLvl","SatLvl Derived from Raw Signal Shapes;satLvl",1024,0,1024);
   
   /// Processed Plots
   
   m_pm_processed_em_satHigh = new PixelMap<unsigned short int>(triggerTower);
   m_pm_processed_em_satLow  = new PixelMap<unsigned short int>(triggerTower);
   m_pm_processed_em_satLvl  = new PixelMap<unsigned short int>(triggerTower);
   m_pm_processed_had_satHigh = new PixelMap<unsigned short int>(triggerTower);
   m_pm_processed_had_satLow  = new PixelMap<unsigned short int>(triggerTower);
   m_pm_processed_had_satLvl  = new PixelMap<unsigned short int>(triggerTower);
   
   m_h_processed_satHigh = new TH1I("processed_satHigh","SatHigh Derived from Processed Signal Shapes;satHigh",1024,0,1024);
   m_h_processed_satLow = new TH1I("processed_satLow","SatLow Derived from Processed Signal Shapes;satLow",1024,0,1024);
   m_h_processed_satLvl = new TH1I("processed_satLvl","SatLvl Derived from Processed Signal Shapes;satLvl",1024,0,1024);
   
   /// Others
   
   m_pm_em_satHigh  = new PixelMap<unsigned short int>(triggerTower);
   m_pm_em_satLow   = new PixelMap<unsigned short int>(triggerTower);
   m_pm_em_satLvl   = new PixelMap<unsigned short int>(triggerTower);
   m_pm_had_satHigh = new PixelMap<unsigned short int>(triggerTower);
   m_pm_had_satLow  = new PixelMap<unsigned short int>(triggerTower);
   m_pm_had_satLvl  = new PixelMap<unsigned short int>(triggerTower);
   
   /// Error code plots
   PixelMap<unsigned int>::pixel_size triggerTower2 = PixelMap<unsigned int>::TrigTower;
   m_pm_em_errorCode  = new PixelMap<unsigned int>(triggerTower2);
   m_pm_had_errorCode = new PixelMap<unsigned int>(triggerTower2);
   
   /// global values
   m_h_satHigh = new TH1I("satHigh","Final SatHigh;satHigh",1024,0,1024);
   m_h_satLow = new TH1I("satLow","Final SatLow;satLow",1024,0,1024);
   m_h_satLvl = new TH1I("satLvl","Final SatLvl;satLvl",1024,0,1024);
   
   m_h_diff_satHigh = new TH1I("diff_satHigh","Raw SatHigh - Processed SatHigh;Raw-Processed SatHigh",1024,0,1024);
   m_h_diff_satLow = new TH1I("diff_satLow","Raw SatLow - Processed SatLow;Raw-Processed SatLow",1024,0,1024);
   
   
   for(unsigned int i=0;i<(unsigned int)CaloDivision::NUM_DIVISIONS;++i){
      CaloDivision div((CaloDivision::CaloDivisionEnum)i);
      std::string name = "satHigh_" + div.GetString();
      std::string title = "SatHigh for " + div.GetString();
      TH1I* histo = new TH1I(name.c_str(),title.c_str(),1024,0,1024);
      m_v_h_satHigh.push_back(histo);
      
      name = "satLow_" + div.GetString();
      title = "SatLow for " + div.GetString();
      histo = new TH1I(name.c_str(),title.c_str(),1024,0,1024);
      m_v_h_satLow.push_back(histo);
      
      name = "satLvl_" + div.GetString();
      title = "SatLevel for " + div.GetString();
      histo = new TH1I(name.c_str(),title.c_str(),1024,0,1024);
      m_v_h_satLvl.push_back(histo);
   }
   
   // Fill Collection of signal shapes
   FillCollection();
}


SignalShapeCollection::~SignalShapeCollection(void){
   if(m_deleteChannelMap){
      delete m_l1map;
      m_l1map = 0;
   }
   
   delete m_h_raw_satHigh;
   m_h_raw_satHigh = 0;
   
   delete m_h_raw_satLow;
   m_h_raw_satLow = 0;
   
   delete m_h_raw_satLvl;
   m_h_raw_satLvl = 0;
   
   delete m_h_processed_satHigh;
   m_h_processed_satHigh = 0;
   
   delete m_h_processed_satLow;
   m_h_processed_satLow = 0;
   
   delete m_h_processed_satLvl;
   m_h_processed_satLvl = 0;
   
   delete m_h_diff_satHigh;
   m_h_diff_satHigh = 0;
   
   delete m_h_diff_satLow;
   m_h_diff_satLow = 0;
   
   delete m_pm_em_errorCode;
   m_pm_em_errorCode = 0;
   
   delete m_pm_had_errorCode;
   m_pm_had_errorCode = 0;
   
}

void SignalShapeCollection::FillCollection(void){
   
   // open file where the output TTree will be saved
   m_treeFile = new TFile(m_s_treeFilename.c_str(),"RECREATE");
   if(!m_treeFile->IsOpen()){
      std::cerr << "[SignalShapeCollection::SignalShapeCollection] ERROR cannot open file, " << m_s_treeFilename << std::endl;
      return;
   }
   m_treeFile->mkdir(m_s_rawCanvasDirectory.c_str());
   m_treeFile->mkdir(m_s_processedCanvasDirectory.c_str());
   m_treeFile->mkdir(m_s_summaryPlotsDirectory.c_str());
   m_treeFile->mkdir(m_s_rawDacVsAdcDirectory.c_str());
   m_treeFile->mkdir(m_s_processedDacVsAdcDirectory.c_str());
   m_treeFile->mkdir(m_s_rawPeakVsTs1Directory.c_str());
   m_treeFile->mkdir(m_s_rawPeakVsTs2Directory.c_str());
   m_treeFile->mkdir(m_s_processedPeakVsTs1Directory.c_str());
   m_treeFile->mkdir(m_s_processedPeakVsTs2Directory.c_str());
   
   // for the directories holding canvases, I want subdirectories
   // organized by paritition
   for(int i=0;i<(int)CaloDivision::NUM_DIVISIONS;++i){
      
      CaloDivision region((CaloDivision::CaloDivisionEnum)i);
      
      m_treeFile->cd(m_s_rawCanvasDirectory.c_str());
      gDirectory->mkdir(region.GetString().c_str());
      
      m_treeFile->cd(m_s_processedCanvasDirectory.c_str());
      gDirectory->mkdir(region.GetString().c_str());
      
      m_treeFile->cd(m_s_rawDacVsAdcDirectory.c_str());
      gDirectory->mkdir(region.GetString().c_str());
      
      m_treeFile->cd(m_s_processedDacVsAdcDirectory.c_str());
      gDirectory->mkdir(region.GetString().c_str());
      
      m_treeFile->cd(m_s_rawPeakVsTs1Directory.c_str());
      gDirectory->mkdir(region.GetString().c_str());
      
      m_treeFile->cd(m_s_rawPeakVsTs2Directory.c_str());
      gDirectory->mkdir(region.GetString().c_str());
      
      m_treeFile->cd(m_s_processedPeakVsTs1Directory.c_str());
      gDirectory->mkdir(region.GetString().c_str());
      
      m_treeFile->cd(m_s_processedPeakVsTs2Directory.c_str());
      gDirectory->mkdir(region.GetString().c_str());
      
      m_treeFile->cd(m_s_summaryPlotsDirectory.c_str());
      gDirectory->mkdir(region.GetString().c_str());
   }
   
   // I close the TFile after setting it up so that it can be opened and closed in the loop below
   // I decided to do this because of ROOT memory management
   m_treeFile->Close();
   delete m_treeFile;
   m_treeFile = 0;
   
   // create saturated bcid collection to store satbcid thresholds
   // so they can be searched later and used to fill disabled channels
   SaturatedBcidCollection* satBcidColl = new SaturatedBcidCollection;
   // I will keep a list of disabled channels which will need to be 
   // set to something useful later
   std::vector<SignalShape*> disabledChannels;
   
   // open database text file for output
   std::ofstream satBcidDB(m_s_databaseFilename.c_str(),std::fstream::trunc);
   
   // loop over the PPM hardware and create SignalShapes
   bool firstLoop = true;
   for(unsigned int crate = PPM_MIN_CRATE;crate<=PPM_MAX_CRATE;++crate){
   for(unsigned int module = PPM_MIN_MODULE;module<=PPM_MAX_MODULE;++module){
   for(unsigned int submodule = PPM_MIN_SUBMODULE;submodule<=PPM_MAX_SUBMODULE;++submodule){
   for(unsigned int channel = PPM_MIN_CHANNEL;channel<=PPM_MAX_CHANNEL;++channel){
      
      std::cout << "crate: " << crate << " module: " << module << " submodule: " << submodule << " channel: " << channel << "\n";
      
      // Set current channel information
      L1CaloChannelId id(L1CaloChannelId::PPM,crate,module,submodule,channel);
      m_l1map->SetPpmChannelID(id);
      
      // check if this is a LAr or Tile Channel
      CaloDivision region = m_l1map->GetDetectorRegion();
      // skip if this is a Tile Run and a LAr Channel
      if(m_tileRun && !m_larRun && region.IsLAr()) continue;
      // skip if this is a LAr Run and a TIle Channel
      if(!m_tileRun && m_larRun && region.IsTile()) continue;
      
      
      // if this channel is not used then skip it.
      if(!m_l1map->IsPpmChannelUsed()){
         std::cout << "[SignalShapeCollection::FillCollection] Skipping unused channel, 0x" << id.GetIdAsString() << std::endl;
         continue;
      }
      
      // Open file for Updating
      m_treeFile = new TFile(m_s_treeFilename.c_str(),"UPDATE");
      
      SatBcidTree* satTree = new SatBcidTree;
      // if this is the first loop we need to open satBcidTree in Create mode
      if(firstLoop){
         satTree->SetCreateMode();
         firstLoop = false;
      }
      else{ // after first loop use update mode
         satTree->SetUpdateMode();
      }
      if(!satTree->OpenFile(m_treeFile)){
         std::cerr << "[SignalShapeCollection::FillCollection] ERROR, tree file, " << m_s_treeFilename << ", could not be opened by SatBcidTree class.\n";
      }
      
      // if this channel is a known offender skip it 
      // if(BadChannel(id)) continue;      
      
      // set some location values
      bool isEM = region.IsEM();
      bool isHAD = region.IsHAD();
      float eta = m_l1map->GetEta();
      float phi = m_l1map->GetPhi();
      FcalLayer fcal = m_l1map->GetPpmFcalLayer()->at(0);
      
      
//       EtaPhiId epId(m_l1map->GetEta(),m_l1map->GetPhi(),m_l1map->GetEmHad());
      
      // set the tree file as the current working root directory
      m_treeFile->cd();
      
      
      // most of the work is done here.
      SignalShape* shape = new SignalShape(id,m_v_trees,m_l1map);
      
      // now extract info/plots into the output TTree
      shape->FillSatBcidTree(satTree);
      
      // get canvases and write to file
      m_treeFile->cd(m_s_rawCanvasDirectory.c_str());
      gDirectory->cd(m_l1map->GetDetectorRegionString().c_str());
      shape->GetRawCanvas()->GetCanvas()->Write();
      if(shape->IsProcessed()){
         m_treeFile->cd(m_s_processedCanvasDirectory.c_str());
         gDirectory->cd(m_l1map->GetDetectorRegionString().c_str());
         shape->GetProcessedCanvas()->GetCanvas()->Write();
      }
      
      m_treeFile->cd(m_s_rawDacVsAdcDirectory.c_str());
      gDirectory->cd(m_l1map->GetDetectorRegionString().c_str());
      shape->GetRawDacVsAdcCanvas()->Write();
      
      m_treeFile->cd(m_s_processedDacVsAdcDirectory.c_str());
      gDirectory->cd(m_l1map->GetDetectorRegionString().c_str());
      shape->GetProcessedDacVsAdcCanvas()->Write();
      
      m_treeFile->cd(m_s_rawPeakVsTs1Directory.c_str());
      gDirectory->cd(m_l1map->GetDetectorRegionString().c_str());
      shape->GetRawPeakVsTs1Canvas()->Write();
      
      m_treeFile->cd(m_s_rawPeakVsTs2Directory.c_str());
      gDirectory->cd(m_l1map->GetDetectorRegionString().c_str());
      shape->GetRawPeakVsTs2Canvas()->Write();
      
      m_treeFile->cd(m_s_processedPeakVsTs1Directory.c_str());
      gDirectory->cd(m_l1map->GetDetectorRegionString().c_str());
      shape->GetProcessedPeakVsTs1Canvas()->Write();
      
      m_treeFile->cd(m_s_processedPeakVsTs2Directory.c_str());
      gDirectory->cd(m_l1map->GetDetectorRegionString().c_str());
      shape->GetProcessedPeakVsTs2Canvas()->Write();
      
      
      ///  Fill Histograms
      
      /// RAW
      
      if(isEM){
         m_pm_raw_em_satHigh->SetTriggerTower(eta,phi,shape->GetRawSatHigh(),fcal);
         m_pm_raw_em_satLow->SetTriggerTower(eta,phi,shape->GetRawSatLow(),fcal);
         m_pm_raw_em_satLvl->SetTriggerTower(eta,phi,shape->GetRawSatLvl(),fcal);
         
         m_pm_em_errorCode->SetTriggerTower(eta,phi,shape->GetErrorCode()->errorCode(),fcal);
      }
      else if(isHAD){
         m_pm_raw_had_satHigh->SetTriggerTower(eta,phi,shape->GetRawSatHigh(),fcal);
         m_pm_raw_had_satLow->SetTriggerTower(eta,phi,shape->GetRawSatLow(),fcal);
         m_pm_raw_had_satLvl->SetTriggerTower(eta,phi,shape->GetRawSatLvl(),fcal);
         
         m_pm_had_errorCode->SetTriggerTower(eta,phi,shape->GetErrorCode()->errorCode(),fcal);
      }
      
      if(shape->GetRawSatHigh() != 0)
         m_h_raw_satHigh->Fill(shape->GetRawSatHigh());
      if(shape->GetRawSatLow() != 0)
         m_h_raw_satLow->Fill(shape->GetRawSatLow());
      if(shape->GetRawSatLvl() != 0)
         m_h_raw_satLvl->Fill(shape->GetRawSatLvl());
      
      /// Processed
      
      if(isEM){
         m_pm_processed_em_satHigh->SetTriggerTower(eta,phi,shape->GetProcessedSatHigh(),fcal);
         m_pm_processed_em_satLow->SetTriggerTower(eta,phi,shape->GetProcessedSatLow(),fcal);
         m_pm_processed_em_satLvl->SetTriggerTower(eta,phi,shape->GetProcessedSatLvl(),fcal);
         
      }
      else if(isHAD){
         m_pm_processed_had_satHigh->SetTriggerTower(eta,phi,shape->GetProcessedSatHigh(),fcal);
         m_pm_processed_had_satLow->SetTriggerTower(eta,phi,shape->GetProcessedSatLow(),fcal);
         m_pm_processed_had_satLvl->SetTriggerTower(eta,phi,shape->GetProcessedSatLvl(),fcal);
      }
      
      if(shape->GetProcessedSatHigh() != 0)
         m_h_processed_satHigh->Fill(shape->GetProcessedSatHigh());
      if(shape->GetProcessedSatLow() != 0)
         m_h_processed_satLow->Fill(shape->GetProcessedSatLow());
      if(shape->GetProcessedSatLvl() != 0)
         m_h_processed_satLvl->Fill(shape->GetProcessedSatLvl());
      
      /// Other
      
      if(isEM){
         m_pm_em_satHigh->SetTriggerTower(eta,phi,shape->GetSatHigh(),fcal);
         m_pm_em_satLow->SetTriggerTower(eta,phi,shape->GetSatLow(),fcal);
         m_pm_em_satLvl->SetTriggerTower(eta,phi,shape->GetSatLvl(),fcal);
         
      }
      else if(isHAD){
         m_pm_had_satHigh->SetTriggerTower(eta,phi,shape->GetSatHigh(),fcal);
         m_pm_had_satLow->SetTriggerTower(eta,phi,shape->GetSatLow(),fcal);
         m_pm_had_satLvl->SetTriggerTower(eta,phi,shape->GetSatLvl(),fcal);
      }
      
      
      if(shape->GetSatHigh() != 0 && !BadChannel(id)){
         m_h_satHigh->Fill(shape->GetSatHigh());
         m_v_h_satHigh[(int)region.GetDivision()]->Fill(shape->GetSatHigh());
      }
      if(shape->GetSatLow() != 0 && !BadChannel(id)){
         m_h_satLow->Fill(shape->GetSatLow());
         m_v_h_satLow[(int)region.GetDivision()]->Fill(shape->GetSatLow());
      }
      if(shape->GetSatLvl() != 0 && !BadChannel(id)){
         m_h_satLvl->Fill(shape->GetSatLvl());
         m_v_h_satLvl[(int)region.GetDivision()]->Fill(shape->GetSatLvl());
      }
      
      
      m_h_diff_satHigh->Fill(shape->GetRawSatHigh()-shape->GetProcessedSatHigh());
      m_h_diff_satLow->Fill(shape->GetRawSatLow()-shape->GetProcessedSatLow());
      
      m_treeFile->cd();
      satTree->Write();
      delete satTree;
      satTree = 0;
      
      delete shape;
      shape = 0;
      
      m_treeFile->Close();
      delete m_treeFile;
      m_treeFile = 0;
      
   } // end for(channel)
   } // end for(submodule)
   } // end for(module)
   } // end for(crate)
   
   std::cout << "[SignalShapeCollection::FillCollection] Adding Summary Plots to file: " << m_s_treeFilename << std::endl;
   
   // now I need to re-open the tree file for writing all other canvases, etc.
   m_treeFile = new TFile(m_s_treeFilename.c_str(),"UPDATE");
   if(!m_treeFile->IsOpen()){
      std::cerr << "[SignalShapeCollection::FillCollection] ERROR, cannot open file, " << m_s_treeFilename << ", for updating summary plots.\n";
   }
   
   
   m_treeFile->cd(m_s_summaryPlotsDirectory.c_str());
   
   m_h_raw_satHigh->Write();
   m_h_raw_satLow->Write();
   m_h_raw_satLvl->Write();
   
   m_h_processed_satHigh->Write();
   m_h_processed_satLow->Write();
   m_h_processed_satLvl->Write();
   
   m_h_satHigh->Write();
   m_h_satLow->Write();
   m_h_satLvl->Write();
   
   m_h_diff_satHigh->Write();
   m_h_diff_satLow->Write();
   
   /// Write PixelMaps
   
   /// RAW EM
   TH2* raw_em_satHigh = m_pm_raw_em_satHigh->GetEtaPhiHistogram("raw_em_satHigh","Raw (EM) SatHigh;#eta;#phi");
   raw_em_satHigh->SetMaximum(1024);
   raw_em_satHigh->Write();
   TH2* raw_em_satLow = m_pm_raw_em_satLow->GetEtaPhiHistogram("raw_em_satLow","Raw (EM) SatLow;#eta;#phi");
   raw_em_satLow->SetMaximum(1024);
   raw_em_satLow->Write();
   TH2* raw_em_satLvl = m_pm_raw_em_satLvl->GetEtaPhiHistogram("raw_em_satLvl","Raw (EM) SatLvl;#eta;#phi");
   raw_em_satLvl->SetMaximum(1024);
   raw_em_satLvl->Write();
   /// RAW HAD
   TH2* raw_had_satHigh = m_pm_raw_had_satHigh->GetEtaPhiHistogram("raw_had_satHigh","Raw (HAD) SatHigh;#eta;#phi");
   raw_had_satHigh->SetMaximum(1024);
   raw_had_satHigh->Write();
   TH2* raw_had_satLow = m_pm_raw_had_satLow->GetEtaPhiHistogram("raw_had_satLow","Raw (HAD) SatLow;#eta;#phi");
   raw_had_satLow->SetMaximum(1024);
   raw_had_satLow->Write();
   TH2* raw_had_satLvl = m_pm_raw_had_satLvl->GetEtaPhiHistogram("raw_had_satLvl","Raw (HAD) SatLvl;#eta;#phi");
   raw_had_satLvl->SetMaximum(1024);
   raw_had_satLvl->Write();
   
   /// PROCESSED EM
   TH2* processed_em_satHigh = m_pm_processed_em_satHigh->GetEtaPhiHistogram("processed_em_satHigh","Processed (EM) SatHigh;#eta;#phi");
   processed_em_satHigh->SetMaximum(1024);
   processed_em_satHigh->Write();
   TH2* processed_em_satLow = m_pm_processed_em_satLow->GetEtaPhiHistogram("processed_em_satLow","Processed (EM) SatLow;#eta;#phi");
   processed_em_satLow->SetMaximum(1024);
   processed_em_satLow->Write();
   TH2* processed_em_satLvl = m_pm_processed_em_satLvl->GetEtaPhiHistogram("processed_em_satLvl","Processed (EM) SatLvl;#eta;#phi");
   processed_em_satLvl->SetMaximum(1024);
   processed_em_satLvl->Write();
   /// PROCESSED HAD
   TH2* processed_had_satHigh = m_pm_processed_had_satHigh->GetEtaPhiHistogram("processed_had_satHigh","Processed (HAD) SatHigh;#eta;#phi");
   processed_had_satHigh->SetMaximum(1024);
   processed_had_satHigh->Write();
   TH2* processed_had_satLow = m_pm_processed_had_satLow->GetEtaPhiHistogram("processed_had_satLow","Processed (HAD) SatLow;#eta;#phi");
   processed_had_satLow->SetMaximum(1024);
   processed_had_satLow->Write();
   TH2* processed_had_satLvl = m_pm_processed_had_satLvl->GetEtaPhiHistogram("processed_had_satLvl","Processed (HAD) SatLvl;#eta;#phi");
   processed_had_satLvl->SetMaximum(1024);
   processed_had_satLvl->Write();
   
   /// GLOBAL EM
   TH2* em_satHigh = m_pm_em_satHigh->GetEtaPhiHistogram("em_satHigh"," (EM) SatHigh;#eta;#phi");
   em_satHigh->SetMaximum(1024);
   em_satHigh->Write();
   TH2* em_satLow = m_pm_em_satLow->GetEtaPhiHistogram("em_satLow"," (EM) SatLow;#eta;#phi");
   em_satLow->SetMaximum(1024);
   em_satLow->Write();
   TH2* em_satLvl = m_pm_em_satLvl->GetEtaPhiHistogram("em_satLvl"," (EM) SatLvl;#eta;#phi");
   em_satLvl->SetMaximum(1024);
   em_satLvl->Write();
   /// GLOBAL HAD
   TH2* had_satHigh = m_pm_had_satHigh->GetEtaPhiHistogram("had_satHigh"," (HAD) SatHigh;#eta;#phi");
   had_satHigh->SetMaximum(1024);
   had_satHigh->Write();
   TH2* had_satLow = m_pm_had_satLow->GetEtaPhiHistogram("had_satLow"," (HAD) SatLow;#eta;#phi");
   had_satLow->SetMaximum(1024);
   had_satLow->Write();
   TH2* had_satLvl = m_pm_had_satLvl->GetEtaPhiHistogram("had_satLvl"," (HAD) SatLvl;#eta;#phi");
   had_satLvl->SetMaximum(1024);
   had_satLvl->Write();
   
   /// ERROR CODES EM
   TH2* em_errorCode = m_pm_em_errorCode->GetEtaPhiHistogram("em_errorCode","Error Code (EM);#eta;#phi");
   em_errorCode->Write();
   /// ERROR CODES HAD
   TH2* had_errorCode = m_pm_had_errorCode->GetEtaPhiHistogram("had_errorCode","Error Code (HAD);#eta;#phi");
   had_errorCode->Write();
   
   
   /// DIVISION HISTOGRAM
   for(unsigned int i=0;i<m_v_h_satHigh.size();++i){
      CaloDivision div((CaloDivision::CaloDivisionEnum)i);
      m_treeFile->cd(m_s_summaryPlotsDirectory.c_str());
      gDirectory->cd(div.GetString().c_str());
      m_v_h_satHigh[i]->Write();
      m_v_h_satLow[i]->Write();
      m_v_h_satLvl[i]->Write();
   }
   
   m_treeFile->Close();
   delete m_treeFile;
   m_treeFile = 0;
   
   std::cout << "[SignalShapeCollection::FillCollection] Done.\n";
   
}

bool SignalShapeCollection::BadChannel(L1CaloChannelId& id){
   
   switch(id.GetId()){
   // FEB BarC H06 FT05
   case 0x1170400:
   case 0x1170401:
   case 0x1170402:
   case 0x1170403:
   case 0x1170500:
   case 0x1170501:
   case 0x1170502:
   case 0x1170503:
   case 0x1160400:
   case 0x1160401:
   case 0x1160402:
   case 0x1160403:
   case 0x1160500:
   case 0x1160501:
   case 0x1160502:
   case 0x1160503:
   case 0x1150400:
   case 0x1150401:
   case 0x1150402:
   case 0x1150403:
   case 0x1150500:
   case 0x1150501:
   case 0x1150502:
   case 0x1150503:
   case 0x1140500:
   case 0x1140501:
   case 0x1140502:
   case 0x1140503:
   
   case 0x03150203: // random signal shapes
   case 0x03110500: // finds analogue sat but shouldn't 
   case 0x04100f03: // random signal shapes 
   case 0x05160b00: // badly reconstructed signals
   case 0x05160b01: // badly reconstructed signals
   case 0x05160b02: // badly reconstructed signals
   case 0x05160b03: // badly reconstructed signals
   case 0x041f0500: // badly reconstructed signals
   case 0x001e0803: // badly reconstructed signals
      return true;
   }
   
   
   return false;
   
}




