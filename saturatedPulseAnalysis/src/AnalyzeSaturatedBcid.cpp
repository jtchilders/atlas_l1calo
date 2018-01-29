#include "AnalyzeSaturatedBcid.h"

#include "TFile.h"
#include "TDirectory.h"

AnalyzeSaturatedBcid::AnalyzeSaturatedBcid(std::vector<ShapeMakerTree*> *trees):
   m_v_inputTree(trees){
   
   m_map_raw_coolId_dacVsAdcPeakGraph = new std::map<unsigned int,DacVsAdcPeakGraph*>;
   m_map_processed_coolId_dacVsAdcPeakGraph = new std::map<unsigned int,DacVsAdcPeakGraph*>;
   
   m_map_raw_coolId_ts1_estAdcVsAdcGraph = new std::map<unsigned int,EstAdcVsAdcGraph*>;
   m_map_processed_coolId_ts1_estAdcVsAdcGraph = new std::map<unsigned int,EstAdcVsAdcGraph*>;
   
   m_map_raw_coolId_ts2_estAdcVsAdcGraph = new std::map<unsigned int,EstAdcVsAdcGraph*>;
   m_map_processed_coolId_ts2_estAdcVsAdcGraph = new std::map<unsigned int,EstAdcVsAdcGraph*>;
   
   
   m_pm_raw_em_satThreshHigh = new PixelMap<double>(TrigTower);
   m_pm_raw_em_satThreshLow  = new PixelMap<double>(TrigTower);
   m_pm_raw_had_satThreshHigh = new PixelMap<double>(TrigTower);
   m_pm_raw_had_satThreshLow  = new PixelMap<double>(TrigTower);
   
   m_pm_processed_em_satThreshHigh = new PixelMap<double>(TrigTower);
   m_pm_processed_em_satThreshLow  = new PixelMap<double>(TrigTower);
   m_pm_processed_had_satThreshHigh = new PixelMap<double>(TrigTower);
   m_pm_processed_had_satThreshLow  = new PixelMap<double>(TrigTower);
   
   m_pm_em_errorBits = new PixelMap<unsigned int>(TrigTower);
   m_pm_had_errorBits = new PixelMap<unsigned int>(TrigTower);
   
   m_pm_raw_em_satEntries = new PixelMap<unsigned short int>(TrigTower);
   m_pm_raw_had_satEntries = new PixelMap<unsigned short int>(TrigTower);
   m_pm_processed_em_satEntries = new PixelMap<unsigned short int>(TrigTower);
   m_pm_processed_had_satEntries = new PixelMap<unsigned short int>(TrigTower);
   
   m_pm_raw_em_unsatEntries = new PixelMap<unsigned short int>(TrigTower);
   m_pm_raw_had_unsatEntries = new PixelMap<unsigned short int>(TrigTower);
   m_pm_processed_em_unsatEntries = new PixelMap<unsigned short int>(TrigTower);
   m_pm_processed_had_unsatEntries = new PixelMap<unsigned short int>(TrigTower);
   
   m_raw_canvas = new CombinedCanvas;
   m_raw_canvas->SetNameBase("raw_canvas_");
   m_raw_canvas->SetTitleBase("Raw Combined Canvas for 0x");
   m_raw_canvas->SetTempFilename("temp_rawCanvases.root");
   
   m_processed_canvas = new CombinedCanvas;
   m_processed_canvas->SetNameBase("processed_canvas_");
   m_processed_canvas->SetTitleBase("Processed Combined Canvas for 0x");
   m_processed_canvas->SetTempFilename("temp_processedCanvases.root");
   
   m_l1map = new L1CaloChannelMap;
   m_l1map->SetPpmEnable(true);
   m_l1map->SetCpmEnable(true);
   m_l1map->SetJemEnable(true);
   
}

AnalyzeSaturatedBcid::~AnalyzeSaturatedBcid(void){
   
   
   m_map_raw_coolId_dacVsAdcPeakGraph->clear();
   delete m_map_raw_coolId_dacVsAdcPeakGraph;
   m_map_raw_coolId_dacVsAdcPeakGraph = 0;
   
   m_map_processed_coolId_dacVsAdcPeakGraph->clear();
   delete m_map_processed_coolId_dacVsAdcPeakGraph;
   m_map_processed_coolId_dacVsAdcPeakGraph = 0;
   
}

// This makes an initial loop over all the 
void AnalyzeSaturatedBcid::PopulateGraphs(void){
   
   std::cout << "[AnalyzeSaturatedBcid::PopulateDacVsAdcPeakGraphs] Looping over tree files to fill DacVsAdcPeakGraphs.\n";
   
   TCanvas can("can","can",0,0,800,600);
   gDirectory->AddDirectory(false);
   
   
   // Loop over the trees in the vector and fill the DacVsAdcPeakGrahps
   for(unsigned int treeNumber=0;treeNumber<2;++treeNumber){
      std::cout << " Tree Number: " << treeNumber << std::endl;
      // grab pointer to current tree
      ShapeMakerTree* tree = (*m_v_inputTree)[treeNumber];
      
      // open file for current tree
      tree->OpenFile();
      
      
      m_raw_canvas->BeginRun(tree->GetRunNumber());
      m_processed_canvas->BeginRun(tree->GetRunNumber());
      
      
      // Loop over tree entries
      // Fill DacVsAdcPeakValue plots
      for(unsigned int treeEntry=0;treeEntry<tree->GetEntries();++treeEntry){
         // get current entry
         tree->GetEntry(treeEntry);
         
         // get coolId for this channel
         const unsigned int coolId = tree->GetCoolId();
         //std::cout << "Channel 0x" << std::hex << coolId << std::dec << std::endl;
         // setup l1map
         m_l1map->SetPpmChannelID(coolId);
         
         /// Fill SignalShapes into canvases
         m_raw_canvas->AddSignalShape(coolId,tree->GetRawSignalShape());
         m_processed_canvas->AddSignalShape(coolId,tree->GetProcessedSignalShape());
         
         
         
         // get an iterator to the map entry for this cool channel ID
         DacVsAdcPeakGraphItr rawGraphItr = GetItrRawDacVsAdc(coolId);
         if(rawGraphItr == m_map_raw_coolId_dacVsAdcPeakGraph->end()){
            std::cerr << "[AnalyzeSaturatedBcid::PopulateDacVsAdcPeakGraphs] Error retrieving Raw Graph Iterator for channel 0x" << std::hex << coolId << std::dec << std::endl;
            exit(0);
         }
         
         // get an iterator to the map entry for this cool channel ID
         DacVsAdcPeakGraphItr processedGraphItr = GetItrProcDacVsAdc(coolId);
         if(processedGraphItr == m_map_processed_coolId_dacVsAdcPeakGraph->end()){
            std::cerr << "[AnalyzeSaturatedBcid::PopulateDacVsAdcPeakGraphs] Error retrieving Processed Graph Iterator for channel 0x" << std::hex << coolId << std::dec << std::endl;
            exit(0);
         }
         
         // get calorimeter dac value
         const unsigned int dac = tree->GetDacForRegion(m_l1map->GetDetectorRegion());
         
         // get raw and processed peak ADC value
         float rawAdcPeak = (unsigned int)tree->GetRawMaxPeakValue();
         if(tree->GetRawFitPerformed()) 
            rawAdcPeak = (unsigned int)tree->GetRawFitPeakValue();
         
         float processedAdcPeak = 0;
         if(tree->GetIsProcessed()){
            processedAdcPeak = (unsigned int)tree->GetProcessedMaxPeakValue();
            if(tree->GetProcessedFitPerformed()){
               processedAdcPeak = (unsigned int)tree->GetProcessedFitPeakValue();
            }
         }
         
         // Fill entry in to graphs
         if((int)rawAdcPeak >= m_saturationLevel){
            rawGraphItr->second->FillSaturatedEntry(dac,rawAdcPeak,tree->GetPedestalMean());
            if(tree->GetIsProcessed()){
               processedGraphItr->second->FillSaturatedEntry(dac,processedAdcPeak,tree->GetPedestalMean());
            }
         }
         else{
            rawGraphItr->second->FillUnsaturatedEntry(dac,rawAdcPeak,tree->GetPedestalMean());
            if(tree->GetIsProcessed()){
               processedGraphItr->second->FillUnsaturatedEntry(dac,processedAdcPeak,tree->GetPedestalMean());
            }
         }
         
//          if(coolId == 0x00100001){
//             tree->GetRawSignalShape()->Draw();
//             tree->GetProcessedSignalShape()->Draw("same");
//             can.Update();
//             std::cin.get();
//          }
         
         // need to pass the peak location information to the EstAdcVsAdcGraph
         // so it can calculate the mean peak position and the t_{-1/-2} positions
         
         // get an iterator to the map entry for this cool channel ID
         EstAdcVsAdcGraphItr rawTs1GraphItr = GetItrRawAdcVsTs1(coolId);
         if(rawTs1GraphItr == m_map_raw_coolId_ts1_estAdcVsAdcGraph->end()){
            std::cerr << "[AnalyzeSaturatedBcid::PopulateDacVsAdcPeakGraphs] Error retrieving Raw T_{-1} Graph Iterator for channel 0x" << std::hex << coolId << std::dec << std::endl;
            exit(0);
         }
         
         // get an iterator to the map entry for this cool channel ID
         EstAdcVsAdcGraphItr rawTs2GraphItr = GetItrRawAdcVsTs2(coolId);
         if(rawTs2GraphItr == m_map_raw_coolId_ts2_estAdcVsAdcGraph->end()){
            std::cerr << "[AnalyzeSaturatedBcid::PopulateDacVsAdcPeakGraphs] Error retrieving Raw T_{-2} Graph Iterator for channel 0x" << std::hex << coolId << std::dec << std::endl;
            exit(0);
         }
         
         // get an iterator to the map entry for this cool channel ID
         EstAdcVsAdcGraphItr processedTs1GraphItr = GetItrProcAdcVsTs1(coolId);
         if(processedTs1GraphItr == m_map_processed_coolId_ts1_estAdcVsAdcGraph->end()){
            std::cerr << "[AnalyzeSaturatedBcid::PopulateDacVsAdcPeakGraphs] Error retrieving Processed T_{-1} Graph Iterator for channel 0x" << std::hex << coolId << std::dec << std::endl;
            exit(0);
         }
         
         // get an iterator to the map entry for this cool channel ID
         EstAdcVsAdcGraphItr processedTs2GraphItr = GetItrProcAdcVsTs2(coolId);
         if(processedTs2GraphItr == m_map_processed_coolId_ts2_estAdcVsAdcGraph->end()){
            std::cerr << "[AnalyzeSaturatedBcid::PopulateDacVsAdcPeakGraphs] Error retrieving Processed T_{-2} Graph Iterator for channel 0x" << std::hex << coolId << std::dec << std::endl;
            exit(0);
         }
         
         // if raw signal is saturated
         // fill the t_{-1} and t_{-2}
         if((int)rawAdcPeak >= m_saturationLevel){
            
            rawTs1GraphItr->second->FillTimeSlice(tree->GetRawSignalShape());
            rawTs2GraphItr->second->FillTimeSlice(tree->GetRawSignalShape());
            
            if(tree->GetIsProcessed()){
               processedTs1GraphItr->second->FillTimeSlice(tree->GetProcessedSignalShape(),tree->GetPedestalMean());
               processedTs2GraphItr->second->FillTimeSlice(tree->GetProcessedSignalShape(),tree->GetPedestalMean());
            }
         }
         // if not saturated
         // calculate mean peakBin
         else{
            if(tree->GetRawFitPerformed()){
               rawTs1GraphItr->second->FillPeakBin(tree->GetRawFitPeakBin());
               rawTs2GraphItr->second->FillPeakBin(tree->GetRawFitPeakBin());
            }
            else{
               rawTs1GraphItr->second->FillPeakBin(tree->GetRawMaxPeakBin());
               rawTs2GraphItr->second->FillPeakBin(tree->GetRawMaxPeakBin());
            }
            
            if(tree->GetIsProcessed()){
               if(tree->GetProcessedFitPerformed()){
                  processedTs1GraphItr->second->FillPeakBin(tree->GetProcessedFitPeakBin());
                  processedTs2GraphItr->second->FillPeakBin(tree->GetProcessedFitPeakBin());
               }
               else{
                  processedTs1GraphItr->second->FillPeakBin(tree->GetProcessedMaxPeakBin());
                  processedTs2GraphItr->second->FillPeakBin(tree->GetProcessedMaxPeakBin());
               }
            }
         }
         
         tree->DeleteEntry();
         
      } // end for(treeEntry)
      
      m_raw_canvas->EndRun();
      m_processed_canvas->EndRun();
      
      // close file for current tree
      tree->CloseFile();
      
   } // end for(treeNumber)
   
   // Now loop over all graphs in map and do Fitting
   
   std::cout << "[AnalyzeSaturatedBcid::PopulateDacVsAdcPeakGraphs] Looping over Raw DacVsAdcPeakGraphs.\n";
   DacVsAdcPeakGraphItr rawItr = m_map_raw_coolId_dacVsAdcPeakGraph->begin();
   for(;rawItr != m_map_raw_coolId_dacVsAdcPeakGraph->end();++rawItr){
      DacVsAdcPeakGraph *graph = rawItr->second;
      const unsigned int coolId = rawItr->first;
      m_l1map->SetPpmChannelID(coolId);
      float eta = m_l1map->GetEta();
      float phi = m_l1map->GetPhi();
      L1CaloChannelMap::CaloDivisionEnum region = m_l1map->GetDetectorRegion();
      
      graph->FillGraph();
      graph->FitGraph();
      
      
//       if(coolId == 0x00100001){
//          graph->Draw("ap");
//          graph->DrawFit("same");
//          can.Update();
//          std::cin.get();
//       }
      
      // Set Error Code if too little unsaturated data to make fit
      std::map<unsigned int,ChanCalibErrorCode>::iterator errorItr = m_map_coolId_errorCode.find(coolId);
      // if no map entry exists, create one
      if(errorItr == m_map_coolId_errorCode.end()){
         // create new error code
         ChanCalibErrorCode errorCode;
         // set error bits
         if(graph->IsTooFewPoints())
            errorCode.satBcidNeedMoreUnsat(true);
         if(graph->IsNoSaturatedData())
            errorCode.satBcidNoSatData(true);
         
         // add entry to map
         m_map_coolId_errorCode[coolId] = errorCode;
         errorItr = m_map_coolId_errorCode.find(coolId);
      }
      else{
         // set error bits
         if(graph->IsTooFewPoints())
            errorItr->second.satBcidNeedMoreUnsat(true);
         
         if(graph->IsNoSaturatedData())
            errorItr->second.satBcidNoSatData(true);
      }
      
      // if the graph reports there is no saturated data
      // then just continue, there is no need to produce additional plots
      if(graph->IsNoSaturatedData()){
         continue;
      }
      
      // need to fill EstAdcVsAdcGraph
      
      // get an iterator to the map entry for this cool channel ID
      EstAdcVsAdcGraphItr rawTs1GraphItr = GetItrRawAdcVsTs1(coolId);
      if(rawTs1GraphItr == m_map_raw_coolId_ts1_estAdcVsAdcGraph->end()){
         std::cerr << "[AnalyzeSaturatedBcid::PopulateDacVsAdcPeakGraphs] Error retrieving Raw T_{-1} Graph Iterator for channel 0x" << std::hex << coolId << std::dec << std::endl;
         exit(0);
      }
      
      // get an iterator to the map entry for this cool channel ID
      EstAdcVsAdcGraphItr rawTs2GraphItr = GetItrRawAdcVsTs2(coolId);
      if(rawTs2GraphItr == m_map_raw_coolId_ts2_estAdcVsAdcGraph->end()){
         std::cerr << "[AnalyzeSaturatedBcid::PopulateDacVsAdcPeakGraphs] Error retrieving Raw T_{-2} Graph Iterator for channel 0x" << std::hex << coolId << std::dec << std::endl;
         exit(0);
      }
      
      bool goodGraph1 = rawTs1GraphItr->second->FillGraph(graph->GetEstimatedAdcPeak());
      bool goodFit1 = rawTs1GraphItr->second->FitGraph();
      bool goodGraph2 = rawTs2GraphItr->second->FillGraph(graph->GetEstimatedAdcPeak());
      bool goodFit2 = rawTs2GraphItr->second->FitGraph();
      
      
//       if(coolId == 0x00100001){
//          rawTs1GraphItr->second->Draw("ap");
//          rawTs1GraphItr->second->DrawFit("same");
//          can.Update();
//          std::cin.get();
//       }
      
      if(rawTs1GraphItr->second->IsTooFewFitPoints() || !goodFit1 
         || rawTs2GraphItr->second->IsTooFewFitPoints() || !goodFit2){
         errorItr->second.satBcidNeedMoreUnsat(true);
      }
      
      // If EM Layer
      if(region == L1CaloChannelMap::LArFCAL1C || region == L1CaloChannelMap::LArFCAL1A
      || region == L1CaloChannelMap::LArEMECC || region == L1CaloChannelMap::LArEMECA
      || region == L1CaloChannelMap::LArOverlapA || region == L1CaloChannelMap::LArOverlapC
      || region == L1CaloChannelMap::LArEMBA || region == L1CaloChannelMap::LArEMBC
      ){
         // extract number of saturated and unsaturated entries from DacVsAdcPeak
         // to plot
         m_pm_raw_em_satEntries->SetTriggerTower(eta,phi,graph->GetSatEntries());
         m_pm_raw_em_unsatEntries->SetTriggerTower(eta,phi,graph->GetUnsatEntries());
         
         // if graph and fit OK, fill SatThreshHigh
         if(goodGraph1 && goodFit1)
            m_pm_raw_em_satThreshHigh->SetTriggerTower(eta,phi,rawTs1GraphItr->second->GetThreshold());
         
         // if graph and fit OK, fill SatThreshLow
         if(goodGraph2 && goodFit2)
            m_pm_raw_em_satThreshLow->SetTriggerTower(eta,phi,rawTs2GraphItr->second->GetThreshold());
         
         // fill errorCode
         unsigned int errorCode = errorItr->second.errorCode() >> 4;
         m_pm_em_errorBits->SetTriggerTower(eta,phi,errorCode);
         
      }
      // If HAD Layer
      else if(region != L1CaloChannelMap::Invalid){
         // extract number of saturated and unsaturated entries from DacVsAdcPeak
         // to plot
         m_pm_raw_had_satEntries->SetTriggerTower(eta,phi,graph->GetSatEntries());
         m_pm_raw_had_unsatEntries->SetTriggerTower(eta,phi,graph->GetUnsatEntries());
         
         // if graph and fit OK, fill SatThreshHigh
         if(goodGraph1 && goodFit1)
            m_pm_raw_had_satThreshHigh->SetTriggerTower(eta,phi,rawTs1GraphItr->second->GetThreshold());
         
         // if graph and fit OK, fill SatThreshLow
         if(goodGraph2 && goodFit2)
            m_pm_raw_had_satThreshLow->SetTriggerTower(eta,phi,rawTs2GraphItr->second->GetThreshold());
         
         // fill errorCode
         unsigned int errorCode = errorItr->second.errorCode() >> 4;
         m_pm_had_errorBits->SetTriggerTower(eta,phi,errorCode);
         
      }
      
      
      
      
   }
   
   std::cout << "[AnalyzeSaturatedBcid::PopulateDacVsAdcPeakGraphs] Looping over Processed DacVsAdcPeakGraphs.\n";
   DacVsAdcPeakGraphItr procItr = m_map_processed_coolId_dacVsAdcPeakGraph->begin();
   for(;procItr != m_map_processed_coolId_dacVsAdcPeakGraph->end();++procItr){
      DacVsAdcPeakGraph *graph = procItr->second;
      const unsigned int coolId = procItr->first;
      m_l1map->SetPpmChannelID(coolId);
      float eta = m_l1map->GetEta();
      float phi = m_l1map->GetPhi();
      L1CaloChannelMap::CaloDivisionEnum region = m_l1map->GetDetectorRegion();
      
      graph->FillGraph();
      graph->FitGraph();
      
//       if(coolId == 0x00100001){
//          graph->Draw("ap");
//          graph->DrawFit("same");
//          can.Update();
//          std::cin.get();
//       }
      
      // Set Error Code if too little unsaturated data to make fit
      std::map<unsigned int,ChanCalibErrorCode>::iterator errorItr = m_map_coolId_errorCode.find(coolId);
      // if no map entry exists, create one
      if(errorItr == m_map_coolId_errorCode.end()){
         ChanCalibErrorCode errorCode;
         // set error bits
         if(graph->IsTooFewPoints())
            errorCode.satBcidNeedMoreUnsat(true);
         if(graph->IsNoSaturatedData())
            errorCode.satBcidNoSatData(true);
         m_map_coolId_errorCode[coolId] = errorCode;
         errorItr = m_map_coolId_errorCode.find(coolId);
      }
      else{
         // set error bits
         if(graph->IsTooFewPoints())
            errorItr->second.satBcidNeedMoreUnsat(true);
         if(graph->IsNoSaturatedData())
            errorItr->second.satBcidNoSatData(true);
      }
      
      
      // need to fill EstAdcVsAdcGraph
      
      // get an iterator to the map entry for this cool channel ID
      EstAdcVsAdcGraphItr processedTs1GraphItr = GetItrProcAdcVsTs1(coolId);
      if(processedTs1GraphItr == m_map_processed_coolId_ts1_estAdcVsAdcGraph->end()){
         std::cerr << "[AnalyzeSaturatedBcid::PopulateDacVsAdcPeakGraphs] Error retrieving Processed T_{-1} Graph Iterator for channel 0x" << std::hex << coolId << std::dec << std::endl;
         exit(0);
      }
      
      // get an iterator to the map entry for this cool channel ID
      EstAdcVsAdcGraphItr processedTs2GraphItr = GetItrProcAdcVsTs2(coolId);
      if(processedTs2GraphItr == m_map_processed_coolId_ts2_estAdcVsAdcGraph->end()){
         std::cerr << "[AnalyzeSaturatedBcid::PopulateDacVsAdcPeakGraphs] Error retrieving Processed T_{-2} Graph Iterator for channel 0x" << std::hex << coolId << std::dec << std::endl;
         exit(0);
      }
      
      bool goodGraph1 = processedTs1GraphItr->second->FillGraph(graph->GetEstimatedAdcPeak());
      bool goodFit1 = processedTs1GraphItr->second->FitGraph();
      bool goodGraph2 = processedTs2GraphItr->second->FillGraph(graph->GetEstimatedAdcPeak());
      bool goodFit2 = processedTs2GraphItr->second->FitGraph();
      
      
//       if(coolId == 0x00100001){
//          processedTs1GraphItr->second->Draw("ap");
//          processedTs1GraphItr->second->DrawFit("same");
//          can.Update();
//          std::cin.get();
//       }
      
      // Set error code if one of the graphs/fits didn't work
      if(processedTs1GraphItr->second->IsTooFewFitPoints() || !goodFit1 
         || processedTs2GraphItr->second->IsTooFewFitPoints() || !goodFit2){
         errorItr->second.satBcidNeedMoreUnsat(true);
      }
      
      // if Cool ID corresponds to EM
      if(region == L1CaloChannelMap::LArFCAL1C || region == L1CaloChannelMap::LArFCAL1A
      || region == L1CaloChannelMap::LArEMECC || region == L1CaloChannelMap::LArEMECA
      || region == L1CaloChannelMap::LArOverlapA || region == L1CaloChannelMap::LArOverlapC
      || region == L1CaloChannelMap::LArEMBA || region == L1CaloChannelMap::LArEMBC
      ){
         // extract number of saturated and unsaturated entries from DacVsAdcPeak
         // to plot
         m_pm_processed_had_satEntries->SetTriggerTower(eta,phi,graph->GetSatEntries());
         m_pm_processed_had_unsatEntries->SetTriggerTower(eta,phi,graph->GetUnsatEntries());
         
         // if graph and fit OK, fill SatThreshHigh
         if(goodGraph1 && goodFit1)
            m_pm_processed_em_satThreshHigh->SetTriggerTower(eta,phi,processedTs1GraphItr->second->GetThreshold());
         
         // if graph and fit OK, fill SatThreshLow
         if(goodGraph2 && goodFit2)
            m_pm_processed_em_satThreshLow->SetTriggerTower(eta,phi,processedTs2GraphItr->second->GetThreshold());
         
         // fill errorCode
         unsigned int errorCode = m_pm_em_errorBits->GetTriggerTower(eta,phi);
         errorCode = (errorItr->second.errorCode() >> 4) | errorCode;
         m_pm_em_errorBits->SetTriggerTower(eta,phi,errorCode);
         
      }
      // Cool ID corresponds to HAD
      else if(region != L1CaloChannelMap::Invalid){
         // extract number of saturated and unsaturated entries from DacVsAdcPeak
         // to plot
         m_pm_processed_had_satEntries->SetTriggerTower(eta,phi,graph->GetSatEntries());
         m_pm_processed_had_unsatEntries->SetTriggerTower(eta,phi,graph->GetUnsatEntries());
         
         // if graph and fit OK, fill SatThreshHigh
         if(goodGraph1 && goodFit1)
            m_pm_processed_had_satThreshHigh->SetTriggerTower(eta,phi,processedTs1GraphItr->second->GetThreshold());
         
         // if graph and fit OK, fill SatThreshLow
         if(goodGraph2 && goodFit2)
            m_pm_processed_had_satThreshLow->SetTriggerTower(eta,phi,processedTs2GraphItr->second->GetThreshold());
         
         // fill errorCode
         unsigned int errorCode = m_pm_had_errorBits->GetTriggerTower(eta,phi);
         errorCode = (errorItr->second.errorCode() >> 4) | errorCode;
         m_pm_had_errorBits->SetTriggerTower(eta,phi,errorCode);
         
      }
      
      
      if(false){
         
         if(goodGraph1)
            processedTs1GraphItr->second->Draw("ap");
         else{
            std::cout << "  No plot for " << std::hex << coolId << std::dec << std::endl;
            continue;
         }
         if(goodFit1){
            processedTs1GraphItr->second->DrawFit("same");
//             std::cout << "  threshold: " << processedTs1GraphItr->second->GetThreshold() << std::endl;
         }
         
         can.Update();
         std::cin.get();
      }
      
   }
   
   TFile file("satBcidAnalysisOutput.root","RECREATE");
   file.AddDirectory(false);
   
   
   /// Save the histograms from the Saturated Threshold PixelMaps
   TH2D* raw_em_high = new TH2D("raw_em_satThreshHigh","Raw SatThreshHigh (EM);#eta;#phi",L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
   m_pm_raw_em_satThreshHigh->FillEtaPhiHistogram(raw_em_high);
   raw_em_high->SetMaximum(1024);
   raw_em_high->Write();
   
   TH2D* raw_em_low = new TH2D("raw_em_satThreshLow","Raw SatThreshLow (EM);#eta;#phi",L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
   m_pm_raw_em_satThreshLow->FillEtaPhiHistogram(raw_em_low);
   raw_em_low->SetMaximum(1024);
   raw_em_low->Write();
   
   TH2D* raw_had_high = new TH2D("raw_had_satThreshHigh","Raw SatThreshHigh (HAD);#eta;#phi",L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
   m_pm_raw_had_satThreshHigh->FillEtaPhiHistogram(raw_had_high);
   raw_had_high->SetMaximum(1024);
   raw_had_high->Write();
   
   TH2D* raw_had_low = new TH2D("raw_had_satThreshLow","Raw SatThreshLow (HAD);#eta;#phi",L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
   m_pm_raw_had_satThreshLow->FillEtaPhiHistogram(raw_had_low);
   raw_had_low->SetMaximum(1024);
   raw_had_low->Write();
   
   
   
   TH2D* processed_em_high = new TH2D("processed_em_satThreshHigh","Processed SatThreshHigh (EM);#eta;#phi",L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
   m_pm_processed_em_satThreshHigh->FillEtaPhiHistogram(processed_em_high);
   processed_em_high->SetMaximum(1024);
   processed_em_high->Write();
   
   TH2D* processed_em_low = new TH2D("processed_em_satThreshLow","Processed SatThreshLow (EM);#eta;#phi",L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
   m_pm_processed_em_satThreshLow->FillEtaPhiHistogram(processed_em_low);
   processed_em_low->SetMaximum(1024);
   processed_em_low->Write();
   
   TH2D* processed_had_high = new TH2D("processed_had_satThreshHigh","Processed SatThreshHigh (HAD);#eta;#phi",L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
   m_pm_processed_had_satThreshHigh->FillEtaPhiHistogram(processed_had_high);
   processed_had_high->SetMaximum(1024);
   processed_had_high->Write();
   
   TH2D* processed_had_low = new TH2D("processed_had_satThreshLow","Processed SatThreshLow (HAD);#eta;#phi",L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
   m_pm_processed_had_satThreshLow->FillEtaPhiHistogram(processed_had_low);
   processed_had_low->SetMaximum(1024);
   processed_had_low->Write();
   
   /// Save the histograms from the Error Code PixelMaps
   TH2D* em_errorBits = new TH2D("em_errorCode","Error Code (EM);#eta;#phi",L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
   m_pm_em_errorBits->FillEtaPhiHistogram(em_errorBits);
   em_errorBits->Write();
   
   TH2D* had_errorBits = new TH2D("had_errorCode","Error Code (HAD);#eta;#phi",L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
   m_pm_had_errorBits->FillEtaPhiHistogram(had_errorBits);
   had_errorBits->Write();
   
   
   /// Save the histograms from the sat/unsat entries
   TH2D* raw_em_satEntries = new TH2D("raw_em_satEntries","Number of Raw Saturated Signals (EM);#eta;#phi",L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
   m_pm_raw_em_satEntries->FillEtaPhiHistogram(raw_em_satEntries);
   raw_em_satEntries->Write();
   
   TH2D* raw_had_satEntries = new TH2D("raw_had_satEntries","Number of Raw Saturated Signals (HAD);#eta;#phi",L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
   m_pm_raw_had_satEntries->FillEtaPhiHistogram(raw_had_satEntries);
   raw_had_satEntries->Write();
   
   TH2D* processed_em_satEntries = new TH2D("processed_em_satEntries","Number of Processed Saturated Signals (EM);#eta;#phi",L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
   m_pm_processed_em_satEntries->FillEtaPhiHistogram(processed_em_satEntries);
   processed_em_satEntries->Write();
   
   TH2D* processed_had_satEntries = new TH2D("processed_had_satEntries","Number of Processed Saturated Signals (HAD);#eta;#phi",L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
   m_pm_processed_had_satEntries->FillEtaPhiHistogram(processed_had_satEntries);
   processed_had_satEntries->Write();
   
   
   TH2D* raw_em_unsatEntries = new TH2D("raw_em_unsatEntries","Number of Raw Unsaturated Signals (EM);#eta;#phi",L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
   m_pm_raw_em_unsatEntries->FillEtaPhiHistogram(raw_em_unsatEntries);
   raw_em_unsatEntries->Write();
   
   TH2D* raw_had_unsatEntries = new TH2D("raw_had_unsatEntries","Number of Raw Unsaturated Signals (HAD);#eta;#phi",L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
   m_pm_raw_had_unsatEntries->FillEtaPhiHistogram(raw_had_unsatEntries);
   raw_had_unsatEntries->Write();
   
   TH2D* processed_em_unsatEntries = new TH2D("processed_em_unsatEntries","Number of Processed Unsaturated Signals (EM);#eta;#phi",L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
   m_pm_processed_em_unsatEntries->FillEtaPhiHistogram(processed_em_unsatEntries);
   processed_em_unsatEntries->Write();
   
   TH2D* processed_had_unsatEntries = new TH2D("processed_had_unsatEntries","Number of Processed Unsaturated Signals (HAD);#eta;#phi",L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
   m_pm_processed_had_unsatEntries->FillEtaPhiHistogram(processed_had_unsatEntries);
   processed_had_unsatEntries->Write();
   
   
   /// Write out canvases
   TDirectory* rawDir = file.mkdir("RawCombinedCanvas");
   file.cd("RawCombinedCanvas");
   file.AddDirectory(false);
   m_raw_canvas->WriteCanvases(rawDir);
   
   
   file.cd();
   TDirectory* processedDir = file.mkdir("ProcessedCombinedCanvas");
   file.cd("ProcessedCombinedCanvas");
   file.AddDirectory(false);
   m_processed_canvas->WriteCanvases(processedDir);
   
   file.Close();
   
   
}


AnalyzeSaturatedBcid::DacVsAdcPeakGraphItr 
AnalyzeSaturatedBcid::GetItrRawDacVsAdc(const unsigned int coolId) const{
   std::map<unsigned int,DacVsAdcPeakGraph*> *map = m_map_raw_coolId_dacVsAdcPeakGraph;
   DacVsAdcPeakGraphItr itr = map->find(coolId);
   
   // if no entry if found create a new one.
   if(itr == map->end()){
      DacVsAdcPeakGraph *temp = new DacVsAdcPeakGraph;
      // set l1calo channel id
      temp->SetL1CaloChannelId(L1CaloChannelId::L1CaloChannelId(coolId));
      // add to map
      (*map)[coolId] = temp;
      itr = map->find(coolId);
      if(itr == map->end()){
         std::cerr << "[AnalyzeSaturatedBcid::GetDacVsAdcIterator] Could not create DacVsAdcPeakGraph in map for cool ID: 0x" << std::hex << coolId << std::dec << std::endl;
         return map->end();
      }
   }
   
   return itr;
}

AnalyzeSaturatedBcid::DacVsAdcPeakGraphItr 
AnalyzeSaturatedBcid::GetItrProcDacVsAdc(const unsigned int coolId) const{
   std::map<unsigned int,DacVsAdcPeakGraph*> *map = m_map_processed_coolId_dacVsAdcPeakGraph;
   DacVsAdcPeakGraphItr itr = map->find(coolId);
   
   // if no entry if found create a new one.
   if(itr == map->end()){
      DacVsAdcPeakGraph *temp = new DacVsAdcPeakGraph;
      // set l1calo channel id
      temp->SetL1CaloChannelId(L1CaloChannelId::L1CaloChannelId(coolId));
      // set processed
      temp->IsProcessed(true);
      // add to map
      (*map)[coolId] = temp;
      itr = map->find(coolId);
      if(itr == map->end()){
         std::cerr << "[AnalyzeSaturatedBcid::GetDacVsAdcIterator] Could not create DacVsAdcPeakGraph in map for cool ID: 0x" << std::hex << coolId << std::dec << std::endl;
         return map->end();
      }
   }
   
   return itr;
}

AnalyzeSaturatedBcid::EstAdcVsAdcGraphItr 
AnalyzeSaturatedBcid::GetItrRawAdcVsTs1(const unsigned int coolId) const{
   std::map<unsigned int,EstAdcVsAdcGraph*> *map = m_map_raw_coolId_ts1_estAdcVsAdcGraph;
   EstAdcVsAdcGraphItr itr = map->find(coolId);
   
   // if no entry if found create a new one.
   if(itr == map->end()){
      EstAdcVsAdcGraph *temp = new EstAdcVsAdcGraph;
      // set l1calo channel id
      temp->SetL1CaloChannelId(L1CaloChannelId::L1CaloChannelId(coolId));
      
      // set labels
      temp->IsTs2(false);
      temp->IsProcessed(false);
      temp->SetBaseGraphTitle("Estimated ADC Vs. ADC for t_{-1} (Raw)");
      temp->SetBaseGraphName("raw_estAdcVsTs1");
      temp->SetGraphXaxisTitle("Estimated ADC");
      temp->SetGraphYaxisTitle("ADC for t_{-1}");
      
      // add to map
      (*map)[coolId] = temp;
      itr = map->find(coolId);
      if(itr == map->end()){
         std::cerr << "[AnalyzeSaturatedBcid::GetItrRawAdcVsTs1] Could not create EstAdcVsAdcGraph in map for cool ID: 0x" << std::hex << coolId << std::dec << std::endl;
         return map->end();
      }
   }
   
   return itr;
}


AnalyzeSaturatedBcid::EstAdcVsAdcGraphItr 
AnalyzeSaturatedBcid::GetItrRawAdcVsTs2(const unsigned int coolId) const{
   std::map<unsigned int,EstAdcVsAdcGraph*> *map = m_map_raw_coolId_ts2_estAdcVsAdcGraph;
   EstAdcVsAdcGraphItr itr = map->find(coolId);
   
   // if no entry if found create a new one.
   if(itr == map->end()){
      EstAdcVsAdcGraph *temp = new EstAdcVsAdcGraph;
      // set l1calo channel id
      temp->SetL1CaloChannelId(L1CaloChannelId::L1CaloChannelId(coolId));
      
      // set labels
      temp->IsTs2(true);
      temp->IsProcessed(false);
      temp->SetBaseGraphTitle("Estimated ADC Vs. ADC for t_{-2} (Raw)");
      temp->SetBaseGraphName("raw_estAdcVsTs2");
      temp->SetGraphXaxisTitle("Estimated ADC");
      temp->SetGraphYaxisTitle("ADC for t_{-2}");
      
      // add to map
      (*map)[coolId] = temp;
      itr = map->find(coolId);
      if(itr == map->end()){
         std::cerr << "[AnalyzeSaturatedBcid::GetItrRawAdcVsTs2] Could not create EstAdcVsAdcGraph in map for cool ID: 0x" << std::hex << coolId << std::dec << std::endl;
         return map->end();
      }
   }
   
   return itr;
}

AnalyzeSaturatedBcid::EstAdcVsAdcGraphItr 
AnalyzeSaturatedBcid::GetItrProcAdcVsTs2(const unsigned int coolId) const{
   std::map<unsigned int,EstAdcVsAdcGraph*> *map = m_map_processed_coolId_ts2_estAdcVsAdcGraph;
   EstAdcVsAdcGraphItr itr = map->find(coolId);
   
   // if no entry if found create a new one.
   if(itr == map->end()){
      EstAdcVsAdcGraph *temp = new EstAdcVsAdcGraph;
      // set l1calo channel id
      temp->SetL1CaloChannelId(L1CaloChannelId::L1CaloChannelId(coolId));
      
      // set labels
      temp->IsTs2(true);
      temp->IsProcessed(true);
      temp->SetBaseGraphTitle("Estimated ADC Vs. ADC for t_{-2} (Processed)");
      temp->SetBaseGraphName("processed_estAdcVsTs2");
      temp->SetGraphXaxisTitle("Estimated ADC");
      temp->SetGraphYaxisTitle("ADC for t_{-2}");
      // add to map
      (*map)[coolId] = temp;
      itr = map->find(coolId);
      if(itr == map->end()){
         std::cerr << "[AnalyzeSaturatedBcid::GetItrProcAdcVsTs2] Could not create EstAdcVsAdcGraph in map for cool ID: 0x" << std::hex << coolId << std::dec << std::endl;
         return map->end();
      }
   }
   
   return itr;
}

AnalyzeSaturatedBcid::EstAdcVsAdcGraphItr 
AnalyzeSaturatedBcid::GetItrProcAdcVsTs1(const unsigned int coolId) const{
   std::map<unsigned int,EstAdcVsAdcGraph*> *map = m_map_processed_coolId_ts1_estAdcVsAdcGraph;
   EstAdcVsAdcGraphItr itr = map->find(coolId);
   
   // if no entry if found create a new one.
   if(itr == map->end()){
      EstAdcVsAdcGraph *temp = new EstAdcVsAdcGraph;
      // set l1calo channel id
      temp->SetL1CaloChannelId(L1CaloChannelId::L1CaloChannelId(coolId));
      
      // set labels
      temp->IsTs2(false);
      temp->IsProcessed(true);
      temp->SetBaseGraphTitle("Estimated ADC Vs. ADC for t_{-1} (Processed)");
      temp->SetBaseGraphName("processed_estAdcVsTs2");
      temp->SetGraphXaxisTitle("Estimated ADC");
      temp->SetGraphYaxisTitle("ADC for t_{-1}");
      
      // add to map
      (*map)[coolId] = temp;
      itr = map->find(coolId);
      if(itr == map->end()){
         std::cerr << "[AnalyzeSaturatedBcid::GetItrProcAdcVsTs1] Could not create EstAdcVsAdcGraph in map for cool ID: 0x" << std::hex << coolId << std::dec << std::endl;
         return map->end();
      }
   }
   
   return itr;
}



/*
void AnalyzeSaturatedBcid::PopulateEstAdcVsAdcPeakGraphs(void){
   std::cout << "[AnalyzeSaturatedBcid::PopulateEstAdcVsAdcPeakGraphs] Looping over DacVsAdcPeakGraphs to fill EstAdcVsAdcGraphs.\n";
   
   // Loop over raw first
   DacVsAdcPeakGraphItr dacAdcItr = m_map_raw_coolId_dacVsAdcPeakGraph->begin();
   
   for(;dacAdcItr != m_map_raw_coolId_dacVsAdcPeakGraph->end();++dacAdcItr){
      
      unsigned int coolId = dacAdcItr->first();
      DacVsAdcPeakGraph* dacVsAdc = dacAdcItr->second;
      
      EstAdcVsAdcGraph* ts1_graph = new EstAdcVsAdcGraph;
      ts1_graph->SetBaseGraphTitle(L1CaloChannelId::L1CaloChannelId(coolId));
      ts1_graph->SetBaseGraphName("raw_ts1_estimatedAdcVsAdc");
      ts1_graph->SetBaseGraphTitle("Estimated ADC Peak Vs. ADC for t_{-1} (RAW)");
      ts1_graph->GetGraph()->GetXaxis()->SetTitle("Estimated Peak ADC");
      ts1_graph->GetGraph()->GetYaxis()->SetTitle("ADC for t_{-1}");
      ts1_graph->SetFitBaseName("raw_ts1_fitEstAdcVsAdc");
      
      std::vector<unsigned short int>* sat_adcPeak = dacVsAdc->GetEstimatedAdcPeak();
      
      
   }
   
}*/
