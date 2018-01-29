
#include "SignalShape.h"

#include "TProfile.h"
#include "TH1F.h"
#include "TCanvas.h"


SignalShape::SignalShape(const L1CaloChannelId coolId,std::vector<ShapeMakerTree*>* list,L1CaloChannelMap* l1map):
   m_l1map(l1map),
   m_coolId(coolId),
   m_v_trees(list)
{
   m_l1map->SetPpmChannelID(m_coolId);
   m_region = m_l1map->GetDetectorRegion();
   
   m_isValid = false;
   m_isEnabled = false;
   m_isProcessed = false;
   
   m_raw_canvas = new CombinedCanvas(m_coolId);
   m_raw_canvas->SetNameBase("rawCanvas");
   
   m_processed_canvas = new CombinedCanvas(m_coolId);
   m_processed_canvas->SetNameBase("processedCanvas");
   
   m_raw_dacVsAdc = new DacVsAdcPeakGraph(m_coolId);
   m_raw_dacVsAdc->SetBaseGraphTitle("DAC vs. ADC Peak for Raw Signals");
   m_raw_dacVsAdc->SetBaseGraphName("raw_dacVsAdc");
   m_can_raw_dacVsAdc = new TCanvas(GetHistogramName("can_raw_dacVsAdc",m_coolId).c_str(),
                                    GetHistogramTitle("Raw DacVsAdc",m_coolId).c_str(),0,0,800,600);
   
   m_processed_dacVsAdc = new DacVsAdcPeakGraph(m_coolId);
   m_processed_dacVsAdc->SetBaseGraphTitle("DAC vs. ADC Peak for Processed Signals");
   m_processed_dacVsAdc->SetBaseGraphName("processed_dacVsAdc");
   m_processed_dacVsAdc->IsProcessed(true);
   m_can_processed_dacVsAdc = new TCanvas(GetHistogramName("processed_dacVsAdc",m_coolId).c_str(),
                                          GetHistogramTitle("Processed DacVsAdc",m_coolId).c_str(),0,0,800,600);
   
   m_errorCode = new ChanCalibErrorCode;
   m_phos4errorCode = 0;
   
   m_raw_peakVsTs1 = new EstAdcVsAdcGraph(m_coolId);
   m_raw_peakVsTs1->SetBaseGraphTitle("Raw Estimated Peak ADC vs. t_{s-1}");
   m_raw_peakVsTs1->SetBaseGraphName("raw_estAdcPeakVsTs1");
   m_raw_peakVsTs1->IsTs2(false);
   m_raw_peakVsTs1->IsProcessed(false);
   m_can_raw_peakVsTs1 = new TCanvas(GetHistogramName("can_raw_peakVsTs1",m_coolId).c_str(),
                                     GetHistogramTitle("Raw PeakVsTs1",m_coolId).c_str(),0,0,800,600);
   
   m_raw_peakVsTs2 = new EstAdcVsAdcGraph(m_coolId);
   m_raw_peakVsTs2->SetBaseGraphTitle("Raw Estimated Peak ADC vs. t_{s-2}");
   m_raw_peakVsTs2->SetBaseGraphName("raw_estAdcPeakVsTs2");
   m_raw_peakVsTs2->IsTs2(true);
   m_raw_peakVsTs2->IsProcessed(false);
   m_can_raw_peakVsTs2 = new TCanvas(GetHistogramName("can_raw_peakVsTs2",m_coolId).c_str(),
           GetHistogramTitle("Raw PeakVsTs2",m_coolId).c_str(),0,0,800,600);
   
   m_processed_peakVsTs1 = new EstAdcVsAdcGraph(m_coolId);
   m_processed_peakVsTs1->SetBaseGraphTitle("Processed Estimated Peak ADC vs. t_{s-1}");
   m_processed_peakVsTs1->SetBaseGraphName("processed_estAdcPeakVsTs1");
   m_processed_peakVsTs1->IsTs2(false);
   m_processed_peakVsTs1->IsProcessed(true);
   m_can_processed_peakVsTs1 = new TCanvas(GetHistogramName("can_processed_peakVsTs1",m_coolId).c_str(),
           GetHistogramTitle("Processed PeakVsTs1",m_coolId).c_str(),0,0,800,600);
   
   m_processed_peakVsTs2 = new EstAdcVsAdcGraph(m_coolId);
   m_processed_peakVsTs2->SetBaseGraphTitle("Processed Estimated Peak ADC vs. t_{s-2}");
   m_processed_peakVsTs2->SetBaseGraphName("processed_estAdcPeakVsTs2");
   m_processed_peakVsTs2->IsTs2(true);
   m_processed_peakVsTs2->IsProcessed(true);
   m_can_processed_peakVsTs2 = new TCanvas(GetHistogramName("can_processed_peakVsTs2",m_coolId).c_str(),
           GetHistogramTitle("Processed PeakVsTs2",m_coolId).c_str(),0,0,800,600);
   
   
   m_satHigh = 0;
   m_satLow = 0;
   m_satLvl = 0;
   m_raw_satHigh = 0;
   m_raw_satLow  = 0;
   m_raw_satLvl  = 0;
   m_processed_satHigh = 0;
   m_processed_satLow  = 0;
   m_processed_satLvl  = 0;
   
   BuildPlots();
   
}

SignalShape::~SignalShape(void){
   
   if(m_errorCode != 0){
      delete m_errorCode;
      m_errorCode = 0;
   }
   
   if(m_raw_canvas != 0){
      delete m_raw_canvas;
      m_raw_canvas = 0;
   }
   
   if(m_processed_canvas != 0){
      delete m_processed_canvas;
      m_processed_canvas = 0;
   }
   
   if(m_raw_dacVsAdc != 0){
      delete m_raw_dacVsAdc;
      m_raw_dacVsAdc = 0;
   }
   
   if(m_processed_dacVsAdc != 0){
      delete m_processed_dacVsAdc;
      m_processed_dacVsAdc = 0;
   }
   
   if(m_raw_peakVsTs1 != 0){
      delete m_raw_peakVsTs1;
      m_raw_peakVsTs1 = 0;
   }
   
   if(m_raw_peakVsTs2 != 0){
      delete m_raw_peakVsTs2;
      m_raw_peakVsTs2 = 0;
   }
   
   if(m_processed_peakVsTs1 != 0){
      delete m_processed_peakVsTs1;
      m_processed_peakVsTs1 = 0;
   }
   
   if(m_processed_peakVsTs2 != 0){
      delete m_processed_peakVsTs2;
      m_processed_peakVsTs2 = 0;
   }
   
   if(m_can_raw_dacVsAdc != 0){
      delete m_can_raw_dacVsAdc;
      m_can_raw_dacVsAdc = 0;
   }
   
   if(m_can_processed_dacVsAdc != 0){
      delete m_can_processed_dacVsAdc;
      m_can_processed_dacVsAdc = 0;
   }
   
   if(m_can_raw_peakVsTs1 != 0){
      delete m_can_raw_peakVsTs1;
      m_can_raw_peakVsTs1 = 0;
   }
   
   if(m_can_raw_peakVsTs2 != 0){
      delete m_can_raw_peakVsTs2;
      m_can_raw_peakVsTs2 = 0;
   }
   
   if(m_can_processed_peakVsTs1 != 0){
      delete m_can_processed_peakVsTs1;
      m_can_processed_peakVsTs1 = 0;
   }
   
   if(m_can_processed_peakVsTs2 != 0){
      delete m_can_processed_peakVsTs2;
      m_can_processed_peakVsTs2 = 0;
   }
   
}

void SignalShape::BuildPlots(void){
   
//    std::cout << "SignalShape::BuildPlots: Building Channel 0x" << m_coolId.GetIdAsString() << std::endl;
   
   /// //////////////////////////////////////////////////////
   /// 1st Loop over tree files to fill DacVsAdcPeak plots
   /// //////////////////////////////////////////////////////
   
   MeanValue m_meanPedestal;
   m_meanPedestal.WithErrors(true);
   unsigned short int baseFullDelayData = 0;
   for(unsigned int treeNum=0;treeNum<m_v_trees->size();++treeNum){
      
      ShapeMakerTree* tree = m_v_trees->at(treeNum);
      tree->ClearTree();
      tree->OpenFile();
      const unsigned int runNumber = tree->GetRunNumber();
            
      unsigned int treeEntry = tree->FindEntry(m_coolId);
      if(tree->GetCoolId() != m_coolId.GetId()){
         std::cerr << "SignalShape::BuildPlots: ERROR cool ID not found in TTree: " << m_coolId.GetIdAsString() << std::endl;
         // must close the tree file:
         tree->CloseFile();
         continue;
      }

      // for some runs, an offset is needed to line up the pulses
      // due to different types of readout
      const int ns_offset = GetOffset(runNumber);
      const bool isOffset = ns_offset != 0 ? true : false;

      //std::cerr << "\n----->  A runNumber= " << runNumber << " treeEntry = " << treeEntry << std::endl;
      //tree->Print();
      //std::cout << "pedestal: " << tree->GetPedestalMean() << " " << tree->GetPedestalSigma() << std::endl;

      if(tree->GetIsValid()) m_isValid = true;
      if(tree->GetIsEnabled()) m_isEnabled = true;
      if(tree->GetIsProcessed()) m_isProcessed = true;
      
      // if there is an offset, refill the signal plots so that the signals are lined up
      // with the 15+1 readout scheme
      TH1* rawSignalShape = 0;
      if(isOffset){
         rawSignalShape = GetOffsetPlot((TH1*)tree->GetRawSignalShape(),ns_offset);
      }
      else rawSignalShape = tree->GetRawSignalShape();
      
      TH1* processedSignalShape = 0;
      if(isOffset) processedSignalShape = GetOffsetPlot((TH1*)tree->GetProcessedSignalShape(),ns_offset);
      else processedSignalShape = tree->GetProcessedSignalShape();
      
      /// ////////////////////////////////////////////////
      /// Add signal shapes to combined canvases
      /// ////////////////////////////////////////////////
      
      m_raw_canvas->AddSignalShape(tree->GetRunNumber(),rawSignalShape);
      if(tree->GetIsProcessed())
         m_processed_canvas->AddSignalShape(tree->GetRunNumber(),processedSignalShape);
      
      /// Extract PHOS4 analysis errorCode
      // use a bitwise OR so that it records any error occuring along the way
      m_phos4errorCode |= tree->GetErrorCode();
      
      // extract mean/sigma pedestal
      m_meanPedestal.AddEntry(tree->GetPedestalMean(),tree->GetPedestalSigma());
      
      /// ////////////////////////////////////////////////
      /// Create DAC Vs. ADC Peak Graphs
      /// ////////////////////////////////////////////////
      const unsigned int currentDAC = tree->GetDacForRegion(m_region);
      
      // if the dac is out of range for this region we should skip it
      // because there will be no signal to analyze
      if(DoNotUseDacForRegion(currentDAC,m_region)){
         // need to delete the entry so it doesn't leave things in memory
         tree->DeleteEntry();
         // must close the tree file:
         tree->CloseFile();
         
         if(isOffset){
            delete rawSignalShape;
            rawSignalShape = 0;
            delete processedSignalShape;
            processedSignalShape = 0;
         }
         
         std::cout << "[SignalShape::BuildPlots] Skipping run " << runNumber << " because of bad dac for region.\n";
         continue;
      }
      
      // skip channel if the signal shape is empty.
      // cutting on Max peak value to check for signal
      if(tree->GetRawMaxPeakValue() < (tree->GetPedestalMean()+5*tree->GetPedestalSigma())){
         // need to delete the entry so it doesn't leave things in memory
         tree->DeleteEntry();
         // must close the tree file:
         tree->CloseFile();
         
         if(isOffset){
            delete rawSignalShape;
            rawSignalShape = 0;
            delete processedSignalShape;
            processedSignalShape = 0;
         }
         std::cout << "[SignalShape::BuildPlots] Skipping run " << runNumber << " because there is no signal.\n";
         continue;
      }
      
      
      // Check if a fitted value is available, if not use the maximum peak value
      float raw_peakValue = 0;
      unsigned int raw_peakBin = 0;
      if(tree->GetRawFitPerformed()){
         raw_peakValue = tree->GetRawFitPeakValue();
         raw_peakBin   = tree->GetRawFitPeakBin();
      }
      else{
         raw_peakValue = tree->GetRawMaxPeakValue();
         raw_peakBin   = tree->GetRawMaxPeakBin();
      }
      
      // if there is an offset, add it to the peakBin
      if(isOffset)
         raw_peakBin += ns_offset;
      
      /// fill variables
      std::string cloneName=tree->GetRawSignalShape()->GetName();
      cloneName += "_";
      cloneName += m_raw_dacVsAdc->GetEntries();
      m_raw_dacVsAdc->Fill(currentDAC,raw_peakValue,raw_peakBin,tree->GetPedestalMean(),(TH1*)rawSignalShape->Clone(cloneName.c_str()));
      
//       if(m_coolId.GetId() == 0x051e0e01)
//       std::cout << " Filling: dac: " << currentDAC << " peakValue: " << raw_peakValue << " peakBin: " << raw_peakBin << " ped: " << tree->GetPedestalMean() << std::endl;
      
      // now for processed if the processed is available
      if(m_isProcessed){
         
         float processed_peakValue = 0;
         unsigned int processed_peakBin = 0;
         if(tree->GetProcessedFitPerformed()){
            processed_peakValue = tree->GetProcessedFitPeakValue();
            processed_peakBin   = tree->GetProcessedFitPeakBin();
         }
         else{
            processed_peakValue = tree->GetProcessedMaxPeakValue();
            processed_peakBin   = tree->GetProcessedMaxPeakBin();
         }
         
         // if there is an offset, add it to the peak bin
         if(isOffset) processed_peakBin += ns_offset;
         
         /// fill variables
         cloneName=tree->GetProcessedSignalShape()->GetName();
         cloneName += "_";
         cloneName += m_processed_dacVsAdc->GetEntries();
         m_processed_dacVsAdc->Fill(currentDAC,processed_peakValue,processed_peakBin,tree->GetPedestalMean(),(TH1*)processedSignalShape->Clone(cloneName.c_str()));
         
      }
      
      // need to delete the entry so it doesn't leave things in memory
      tree->DeleteEntry();
      // must close the tree file:
      tree->CloseFile();
      
      if(isOffset){
         delete rawSignalShape;
         rawSignalShape = 0;
         delete processedSignalShape;
         processedSignalShape = 0;
      }
      
   }// end(treeNum)
   
   /// Build histogram/fit
   m_raw_dacVsAdc->Build();
   
   // check for errors
   bool raw_tooFewSatPoints = false;
   bool raw_noSatPoints = false;
   if(m_raw_dacVsAdc->IsTooFewPoints()){
      raw_tooFewSatPoints =true;
   }
   if(m_raw_dacVsAdc->IsNoSaturatedData()){
      raw_noSatPoints = true;
   }
   
   // Fill processed graph and make fit
   bool processed_tooFewSatPoints = false;
   bool processed_noSatPoints = false;
   if(m_isProcessed){
      
      /// Build histo/fit
      m_processed_dacVsAdc->Build();
      
      if(m_processed_dacVsAdc->IsTooFewPoints()){
         processed_tooFewSatPoints = true;
      }
      if(m_processed_dacVsAdc->IsNoSaturatedData()){
         processed_noSatPoints = true;
      }
      
   }
   
   // set error codes
   if(raw_tooFewSatPoints && processed_tooFewSatPoints){
      m_errorCode->satBcidTooFewSatPeaks(true);
   }
   
   if(raw_noSatPoints && processed_noSatPoints){
      m_errorCode->satBcidNoSatPeaks(true);
   }
   
   /// ////////////////////////////////////////////////////
   /// Fill Estimated ADC Peak vs. t_{s-1/2}
   /// ////////////////////////////////////////////////////
   
   // fill mean peakBin values so t_{s-1/2} can be correctly identified
   m_raw_peakVsTs1->SetMeanPeakBin(m_raw_dacVsAdc->GetMeanPeakBin()->GetIntegerMean());
   m_raw_peakVsTs2->SetMeanPeakBin(m_raw_dacVsAdc->GetMeanPeakBin()->GetIntegerMean());
   m_processed_peakVsTs1->SetMeanPeakBin(m_processed_dacVsAdc->GetMeanPeakBin()->GetIntegerMean());
   m_processed_peakVsTs2->SetMeanPeakBin(m_processed_dacVsAdc->GetMeanPeakBin()->GetIntegerMean());
   
   // fill mean pedestal values
   m_raw_peakVsTs1->SetMeanPedestal(m_meanPedestal.GetIntegerMean());
   m_raw_peakVsTs2->SetMeanPedestal(m_meanPedestal.GetIntegerMean());
   m_processed_peakVsTs1->SetMeanPedestal(m_meanPedestal.GetIntegerMean());
   m_processed_peakVsTs2->SetMeanPedestal(m_meanPedestal.GetIntegerMean());
   
   // fill analogue saturation
   m_raw_peakVsTs1->SetAnalogueSaturationLevel(m_raw_dacVsAdc->GetAnalogueSaturationLevel());
   m_raw_peakVsTs2->SetAnalogueSaturationLevel(m_raw_dacVsAdc->GetAnalogueSaturationLevel());
   m_processed_peakVsTs1->SetAnalogueSaturationLevel(m_processed_dacVsAdc->GetAnalogueSaturationLevel());
   m_processed_peakVsTs2->SetAnalogueSaturationLevel(m_processed_dacVsAdc->GetAnalogueSaturationLevel());
   
   
   /// fill raw graphs and fits
   // if there were no saturated points in the previous plots then these plots can't be made
   bool raw_tooFewSatSlices1 = false;
   bool raw_noSatSlices1 = false;
   bool raw_tooFewSatSlices2 = false;
   bool raw_noSatSlices2 = false;
   if(!raw_noSatPoints){
      
      
//       if(m_coolId.GetId() == 0x051e0e01){
//          std::cout << "  estAdcVsTs1:\n";
//          for(unsigned int i=0;i<m_raw_dacVsAdc->GetTs1EstAdcPeak()->size();++i){
//             std::cout << m_raw_dacVsAdc->GetTs1EstAdcPeak()->at(i) << " " << m_raw_dacVsAdc->GetTs1()->at(i) << "   " << ((float)m_raw_dacVsAdc->GetTs1()->at(i)/(float)m_raw_dacVsAdc->GetTs1EstAdcPeak()->at(i)) << std::endl;
//          }
//             
//       }
      
      
      m_raw_peakVsTs1->Build(m_raw_dacVsAdc->GetTs1EstAdcPeak(),m_raw_dacVsAdc->GetTs1(),m_raw_dacVsAdc->GetSaturatedDac());
      
      if(m_raw_peakVsTs1->IsTooFewSatSlices())
         raw_tooFewSatSlices1 = true;
      if(m_raw_peakVsTs1->IsNoSatSlices())
         raw_noSatSlices1 = true;
      m_raw_peakVsTs2->Build(m_raw_dacVsAdc->GetTs2EstAdcPeak(),m_raw_dacVsAdc->GetTs2(),m_raw_dacVsAdc->GetSaturatedDac());
      
      if(m_raw_peakVsTs2->IsTooFewSatSlices())
         raw_tooFewSatSlices2 = true;
      if(m_raw_peakVsTs2->IsNoSatSlices())
         raw_noSatSlices2 = true;
   }
   /// fill processed graphs and fits
   
   bool processed_tooFewSatSlices1 = false;
   bool processed_noSatSlices1 = false;
   bool processed_tooFewSatSlices2 = false;
   bool processed_noSatSlices2 = false;
   if(!processed_noSatPoints){
      
m_processed_peakVsTs1->Build(m_processed_dacVsAdc->GetTs1EstAdcPeak(),m_processed_dacVsAdc->GetTs1(),m_processed_dacVsAdc->GetSaturatedDac());
      
      if(m_processed_peakVsTs1->IsTooFewSatSlices())
         processed_tooFewSatSlices1 = true;
      if(m_processed_peakVsTs1->IsNoSatSlices())
         processed_noSatSlices1 = true;
      
      
m_processed_peakVsTs2->Build(m_processed_dacVsAdc->GetTs2EstAdcPeak(),m_processed_dacVsAdc->GetTs2(),m_processed_dacVsAdc->GetSaturatedDac());
      
      if(m_processed_peakVsTs2->IsTooFewSatSlices())
         processed_tooFewSatSlices2 = true;
      if(m_processed_peakVsTs2->IsNoSatSlices())
         processed_noSatSlices2 = true;
   }
   
   // set the error flag if the associated task failed in both the raw and processed
   if(raw_tooFewSatSlices1 && processed_tooFewSatSlices1)
      m_errorCode->satBcidTooFewSatSlices1(true);
   if(raw_noSatSlices1 && processed_noSatSlices1)
      m_errorCode->satBcidNoSatSlices1(true);
   if(raw_tooFewSatSlices2 && processed_tooFewSatSlices2)
      m_errorCode->satBcidTooFewSatSlices2(true);
   if(raw_noSatSlices2 && processed_noSatSlices2)
      m_errorCode->satBcidNoSatSlices2(true);
   
   
   /// ////////////////////////////////////////////////////
   /// Select SatLvl, SatHigh, and SatLow
   /// ////////////////////////////////////////////////////
   
   // if the processed graph/fit were OK then use the values
   // derived from the processed data
   
   // Set SatHigh
   m_satHigh = 0;
   m_raw_satHigh = 0;
   m_processed_satHigh = 0;
   
   // if the graph/fit worked then fill the raw satHigh
   if(!raw_tooFewSatSlices1 && !raw_noSatSlices1){
      m_raw_satHigh = (unsigned)m_raw_peakVsTs1->GetThreshold();
   }
   
   // if the graph/fit worked then fill the satLow and make it the global value
   if(!processed_tooFewSatSlices1 && !processed_noSatSlices1){
      m_processed_satHigh = (unsigned)m_processed_peakVsTs1->GetThreshold();
      m_satHigh = m_processed_satHigh;
   }
   // otherwise make the raw value the global
   else if(!raw_tooFewSatSlices1 && !raw_noSatSlices1){
      m_satHigh = m_raw_satHigh;
   }
   
   
   // Set SatLow
   // Set the Sat Low/High for processed/raw if there were no errors
   // Set the global SatLow/High using the processed first, raw second
   m_satLow = 0;
   m_raw_satLow = 0;
   m_processed_satLow = 0;
   if(!raw_tooFewSatSlices2 && !raw_noSatSlices2){
      m_raw_satLow = (unsigned)m_raw_peakVsTs2->GetThreshold();
   }
   if(!processed_tooFewSatSlices2 && !processed_noSatSlices2){
      m_processed_satLow = (unsigned)m_processed_peakVsTs2->GetThreshold();
      m_satLow = m_processed_satLow;
   }
   else if(!raw_tooFewSatSlices2 && !raw_noSatSlices2){
      m_satLow = m_raw_satLow;
   }
   
   // Set SatLvl
   m_satLvl = 0;
   m_raw_satLvl = 0;
   m_processed_satLvl = 0;
   m_raw_satLvl = m_raw_dacVsAdc->GetAnalogueSaturationLevel();
   if(m_isProcessed){
      m_processed_satLvl = m_processed_dacVsAdc->GetAnalogueSaturationLevel();
      m_satLvl = m_processed_satLvl;
   }
   else{
      m_satLvl = m_raw_satLvl;
   }
   
//    if(m_coolId.GetId() == 0x051e0e01){
//    TCanvas can("can","can",0,0,800,600);
//    can.Divide(3,2);
//    can.cd(1);
//    m_raw_dacVsAdc->Draw("ap");
//    m_raw_dacVsAdc->DrawFit("same");
//    can.cd(2);
//    m_raw_peakVsTs1->Draw("ap");
//    m_raw_peakVsTs1->DrawFit("same");
//    can.cd(3);
//    m_raw_peakVsTs2->Draw("ap");
//    m_raw_peakVsTs2->DrawFit("same");
//    can.cd(4);
//    m_processed_dacVsAdc->Draw("ap");
//    m_processed_dacVsAdc->DrawFit("same");
//    can.cd(5);
//    m_processed_peakVsTs1->Draw("ap");
//    m_processed_peakVsTs1->DrawFit("same");
//    can.cd(6);
//    m_processed_peakVsTs2->Draw("ap");
//    m_processed_peakVsTs2->DrawFit("same");
//    can.Update();
//    
//    std::cout << "      satLvl: " << m_satLvl << " satHigh: " << m_satHigh << " satLow: " << m_satLow << std::endl;
//    std::cout << "  raw satLvl: " << m_raw_satLvl << " satHigh: " << m_raw_satHigh << " satLow: " << m_raw_satLow << std::endl;
//    std::cout << " proc satLvl: " << m_processed_satLvl << " satHigh: " << m_processed_satHigh << " satLow: " << m_processed_satLow << std::endl;
//    
//    std::cin.get();
//    }
   
   /// Setup canvases
   
   /// RAW DAC vs ADC Peak with raw satBcid values
   m_can_raw_dacVsAdc->cd();
   m_raw_dacVsAdc->Draw("ap");
   m_raw_dacVsAdc->DrawFit("same");
   TF1 fitSatLvl("fitSatLvl","pol1",0,100000);
   fitSatLvl.SetLineColor(kGreen);
   fitSatLvl.SetParameter(1,0.);
   fitSatLvl.SetParameter(0,m_raw_satLvl);
   fitSatLvl.DrawCopy("same");
   TF1 fitSatHigh("fitSatHigh","pol1",0,100000);
   fitSatHigh.SetLineColor(kBlue);
   fitSatHigh.SetParameter(1,0.);
   fitSatHigh.SetParameter(0,m_raw_satHigh);
   fitSatHigh.DrawCopy("same");
   TF1 fitSatLow("fitSatLow","pol1",0,100000);
   fitSatLow.SetLineColor(kViolet);
   fitSatLow.SetParameter(1,0.);
   fitSatLow.SetParameter(0,m_raw_satLow);
   fitSatLow.DrawCopy("same");
   m_can_raw_dacVsAdc->Update();
   
   /// Processed DAC vs ADC Peak with processed satBcid values
   m_can_processed_dacVsAdc->cd();
   m_processed_dacVsAdc->Draw("ap");
   m_processed_dacVsAdc->DrawFit("same");
   fitSatLvl.SetParameter(0,m_processed_satLvl);
   fitSatLvl.DrawCopy("same");
   fitSatHigh.SetParameter(0,m_processed_satHigh);
   fitSatHigh.DrawCopy("same");
   fitSatLow.SetParameter(0,m_processed_satLow);
   fitSatLow.DrawCopy("same");
   m_can_processed_dacVsAdc->Update();
   
   /// Raw peak vs ts1 with raw satBcid values
   m_can_raw_peakVsTs1->cd();
   m_raw_peakVsTs1->Draw("ap");
   m_raw_peakVsTs1->DrawFit("same");
   fitSatHigh.SetParameter(0,m_raw_satHigh);
   fitSatHigh.DrawCopy("same");
   m_raw_peakVsTs1->DrawAxis("same");
   m_can_raw_peakVsTs1->Update();
   
   /// Processed peak vs ts1 with processed satBcid values
   m_can_processed_peakVsTs1->cd();
   m_processed_peakVsTs1->Draw("ap");
   m_processed_peakVsTs1->DrawFit("same");
   fitSatHigh.SetParameter(0,m_processed_satHigh);
   fitSatHigh.DrawCopy("same");
   m_processed_peakVsTs1->DrawAxis("same");
   m_can_processed_peakVsTs1->Update();
   
   /// Raw peak vs ts2 with raw satBcid values
   m_can_raw_peakVsTs2->cd();
   m_raw_peakVsTs2->Draw("ap");
   m_raw_peakVsTs2->DrawFit("same");
   fitSatLow.SetParameter(0,m_raw_satLow);
   fitSatLow.DrawCopy("same");
   m_raw_peakVsTs2->DrawAxis("same");
   m_can_raw_peakVsTs2->Update();
   
   /// Processed peak vs ts2 with processed satBcid values
   m_can_processed_peakVsTs2->cd();
   m_processed_peakVsTs2->Draw("ap");
   m_processed_peakVsTs2->DrawFit("same");
   fitSatLow.SetParameter(0,m_processed_satLow);
   fitSatLow.DrawCopy("same");
   m_processed_peakVsTs2->DrawAxis("same");
   m_can_processed_peakVsTs2->Update();
   
}


std::string SignalShape::GetHistogramName(const std::string base,const L1CaloChannelId coolId) const{
   std::string output = base;
   output += "_";
   output += coolId.GetIdAsString();
   return output;
}

std::string SignalShape::GetHistogramTitle(const std::string base,const L1CaloChannelId coolId) const{
   std::string output = base;
   output += " 0x";
   output += coolId.GetIdAsString();
   return output;
}

bool SignalShape::DoNotUseDacForRegion(unsigned int dac,CaloDivision& region){
   
   // the maximum DAC value that produces a signal seems to be 6000
   // so ignore higher values because there will be no signal
   if( (region.IsLArHECA() || region.IsLArHECC()) 
        && dac > 6000){
      return true;
   }
   else return false;
}

std::string SignalShape::GetDataBaseString(void){
   char temp[600];
   unsigned int errorCode=0,
      extBcidNegEdge=1,
      extBcidThreshold=100,
      bcidEnergyLow=511,
      bcidEnergyHigh=895;
   
   sprintf(temp,"Calib1.PprSatBcidResults,ModuleId:unsigned:%08x,ErrorCode:unsigned:%i,Histograms:string:%s,InBcidNegedge:unsigned short:%i,ExtBcidThreshold:unsigned short:%i,SatBcidThresholdLow:unsigned short:%i,SatBcidThresholdHigh:unsigned short:%i,SatBcidLevel:unsigned short:%i,BcidEnergyRangeLow:unsigned short:%i,BcidEnergyRangeHigh:unsigned short:%i",m_coolId.GetId(),errorCode,"Not Yet Set",extBcidNegEdge,extBcidThreshold,m_satLow,m_satHigh,m_satLvl,bcidEnergyLow,bcidEnergyHigh);

   return std::string(temp);
}


void SignalShape::FillSatBcidTree(SatBcidTree* tree){
   
   tree->SetCoolId(m_coolId.GetId());
   
   tree->SetErrorCode(m_errorCode->errorCode());
   tree->SetPhos4ErrorCode(m_phos4errorCode);
   
   tree->SetSatHigh(m_satHigh);
   tree->SetSatLow(m_satLow);
   tree->SetSatLevel(m_satLvl);
   
   tree->SetIsValid(m_isValid);
   tree->SetIsEnabled(m_isEnabled);
   tree->SetIsProcessed(m_isProcessed);
   
   tree->SetRawDacVsAdcPeakGraph(m_raw_dacVsAdc->GetGraph());
   tree->SetRawDacVsAdcPeakFit(m_raw_dacVsAdc->GetFit());
   tree->SetRawPeakVsTs1Graph(m_raw_peakVsTs1->GetGraph());
   tree->SetRawPeakVsTs1Fit(m_raw_peakVsTs1->GetFit());
   tree->SetRawSatHigh(m_raw_satHigh);
   tree->SetRawPeakVsTs2Graph(m_raw_peakVsTs2->GetGraph());
   tree->SetRawPeakVsTs2Fit(m_raw_peakVsTs2->GetFit());
   tree->SetRawSatLow(m_raw_satLow);
   tree->SetRawSatLevel(m_raw_satLvl);
   
   tree->SetProcessedDacVsAdcPeakGraph(m_processed_dacVsAdc->GetGraph());
   tree->SetProcessedDacVsAdcPeakFit(m_processed_dacVsAdc->GetFit());
   tree->SetProcessedPeakVsTs1Graph(m_processed_peakVsTs1->GetGraph());
   tree->SetProcessedPeakVsTs1Fit(m_processed_peakVsTs1->GetFit());
   tree->SetProcessedSatHigh(m_processed_satHigh);
   tree->SetProcessedPeakVsTs2Graph(m_processed_peakVsTs2->GetGraph());
   tree->SetProcessedPeakVsTs2Fit(m_processed_peakVsTs2->GetFit());
   tree->SetProcessedSatLow(m_processed_satLow);
   tree->SetProcessedSatLevel(m_processed_satLvl);
   
   tree->SetPedestalMean(m_meanPedestal.GetMean());
   tree->SetPedestalSigma(m_meanPedestal.GetSigma());
   
   tree->SetRawDacVsAdcSlopeMean(m_raw_dacVsAdc->GetMeanSlope()->GetMean());
   tree->SetRawDacVsAdcSlopeSigma(m_raw_dacVsAdc->GetMeanSlope()->GetSigma());
   
   tree->SetProcessedDacVsAdcSlopeMean(m_processed_dacVsAdc->GetMeanSlope()->GetMean());
   tree->SetProcessedDacVsAdcSlopeSigma(m_processed_dacVsAdc->GetMeanSlope()->GetSigma());
   
   tree->SetRawPeakBin(m_raw_dacVsAdc->GetMeanPeakBin()->GetIntegerMean());
   tree->SetProcessedPeakBin(m_processed_dacVsAdc->GetMeanPeakBin()->GetIntegerMean());
   
   
   tree->Fill();
   
}

int SignalShape::GetOffset(unsigned int runNumber) const{
   
   // these runs were taken with 9+3 readout instead of 15+1
   // so a nano-second offset must be applied
   int offset = 0;
   switch(runNumber){
      case 164057:
      case 164062:
      case 164066:
      case 164072:
      case 164081:
      case 164087:
      case 164093:
      case 164096:
         switch(m_coolId.GetId()){
            case 0x05120c02:
            case 0x04110401:
            case 0x04110902:
            case 0x04120a01:
            case 0x041d0200:
            case 0x041d0601:
            case 0x051e0400:
               offset = 100;
               break;
            case 0x00100a00:
            case 0x00110100:
            case 0x00110101:
            case 0x00110102:
            case 0x00110103:
            case 0x00150e02:
            case 0x00170100:
            case 0x00170101:
            case 0x00170e00:
            case 0x00170e01:
            case 0x001d0e02:
            case 0x01120001:
            case 0x01120002:
            case 0x01120700:
            case 0x01150002:
            case 0x01160300:
            case 0x02110600:
            case 0x02110700:
            case 0x02160c00:
            case 0x02170e00:
            case 0x021a0903:
            case 0x021a0e00:
            case 0x03150203:
            case 0x03160000:
            case 0x03160c02:
            case 0x03160c03:
            case 0x03170c03:
            case 0x03190503:
            case 0x031a0f02:
            case 0x031b0002:
            case 0x031b0301:
            case 0x031d0d00:
            case 0x031b0e00:
            case 0x031f0b00:
            case 0x04110200:
            case 0x04110601:
            case 0x04110602:
            case 0x04110a02:
            case 0x04110a03:
            case 0x04110d00:
            case 0x04110e00:
            case 0x04120a03:
            case 0x04120c01:
            case 0x04120c02:
            case 0x04120d01:
            case 0x04120e00:
            case 0x04120f00:
            case 0x04120f02:
            case 0x04130402:
            case 0x04190600:
            case 0x041a0300:
            case 0x041a0301:
            case 0x041a0502:
            case 0x041a0600:
            case 0x041a0c00:
            case 0x041a0e00:
            case 0x041d0902:
            case 0x041d0a00:
            case 0x041d0d00:
            case 0x05120c03:
            case 0x05120f02:
            case 0x05160300:
            case 0x05160401:
            case 0x05190a02:
            case 0x05190a03:
            case 0x051a0603:
            case 0x051e0201:
            case 0x051e0402:
            case 0x051e0701:
            case 0x051e0d01:
            case 0x051e0d02:
            case 0x051e0e00:
            case 0x061b0103:
               offset = 75;
               break;
            case 0x001a0100:
            case 0x001b0402:
            case 0x001b0801:
            case 0x001b0901:
            case 0x001e0803:
            case 0x01110800:
            case 0x01110801:
            case 0x01110802:
            case 0x01110803:
            case 0x01110e00:
            case 0x01110e01:
            case 0x01140901:
            case 0x02120a02:
            case 0x02120a03:
            case 0x02130d03:
            case 0x02160d03:
            case 0x021a0d00:
            case 0x021d0b00:
            case 0x031a0f00:
            case 0x031f0b02:
            case 0x04110901:
            case 0x04110903:
            case 0x04170f01:
            case 0x04190201:
            case 0x051b0400:
            case 0x051e0403:
            case 0x051a0b00:
            case 0x051a0b01:
            case 0x051b0301:
            case 0x051b0b02:
            case 0x051f0302:
            case 0x07180c01:
               offset = 25;
               break;
            case 0x01120702:
            case 0x01150000:
            case 0x03150700:
            case 0x051e0501:
            case 0x051e0702:
            case 0x051f0502:
               offset = 0;
               break;
            case 0x03170903:
            case 0x05160b03:
               offset = -25;
               break;
            default:
               offset = 50;
               break;
         }
         break;
      default:
         offset = 0;
         break;
   };
   
   return offset;
}


TH1* SignalShape::GetOffsetPlot(TH1* histo,const int& offset) const{
   
   std::string newName = "adjusted_";
   newName += histo->GetName();
   TH1 *newHisto = new TH1F(newName.c_str(),histo->GetTitle(),15*25,0,15*25);
   
   for(unsigned int xbin=1;xbin<=15*25;++xbin){
      if(xbin+offset < 1) continue; // can't fill bins less than 1
      if(xbin+offset > 15*25) continue; // can't fill bins more than 15*25
      float binContent = histo->GetBinContent(xbin);
      newHisto->SetBinContent(xbin+offset,binContent);
      float binError = histo->GetBinError(xbin);
      newHisto->SetBinError(xbin+offset,binError);
   }
   
   return newHisto;
}


