#ifndef SIGNALSHAPE_H
#define SIGNALSHAPE_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

#include "TGraph.h"
#include "TF1.h"
#include "TCanvas.h"

#include "L1CaloChannelMap.h"
#include "L1CaloChannelId.h"
#include "DacVsAdcPeakGraph.h"
#include "EstAdcVsAdcGraph.h"
#include "CombinedCanvas.h"
#include "ShapeMakerTree.h"
#include "SatBcidTree.h"
#include "MeanValue.h"
#include "CaloDivision.h"

#include "ChanCalibErrorCode.h"


class SignalShape{
public:
   SignalShape(const L1CaloChannelId coolId,std::vector<ShapeMakerTree*>* list,L1CaloChannelMap* l1map);
   ~SignalShape(void);
   
   DacVsAdcPeakGraph* GetRawDacVsAdcGraph(void){return m_raw_dacVsAdc;};
   DacVsAdcPeakGraph* GetProcessedDacVsAdcGraph(void){return m_processed_dacVsAdc;};
   
   EstAdcVsAdcGraph* GetRawPeakVsTs1Graph(void){return m_raw_peakVsTs1;};
   EstAdcVsAdcGraph* GetRawPeakVsTs2Graph(void){return m_raw_peakVsTs2;};
   
   EstAdcVsAdcGraph* GetProcessedPeakVsTs1Graph(void){return m_processed_peakVsTs1;};
   EstAdcVsAdcGraph* GetProcessedPeakVsTs2Graph(void){return m_processed_peakVsTs2;};
   
   bool IsEnabled(void){return m_isEnabled;};
   bool IsValid(void){return m_isValid;};
   bool IsProcessed(void){return m_isProcessed;};
   
   const L1CaloChannelId GetCoolId(void){return m_coolId;};
   
   CombinedCanvas* GetRawCanvas(void){return m_raw_canvas;};
   CombinedCanvas* GetProcessedCanvas(void){return m_processed_canvas;};
   
   unsigned int GetAnalogueSaturationLevel(void){return m_raw_dacVsAdc->GetAnalogueSaturationLevel();};
   
   MeanValue* GetMeanPedestal(void){return &m_meanPedestal;};
   
   unsigned int GetRawPeakBin(void){return m_raw_dacVsAdc->GetMeanPeakBin()->GetIntegerMean();};
   unsigned int GetProcessedPeakBin(void){return m_processed_dacVsAdc->GetMeanPeakBin()->GetIntegerMean();};
   
   std::string GetDataBaseString(void);
   
   void FillSatBcidTree(SatBcidTree* tree);
   
   ChanCalibErrorCode* GetErrorCode(void){return m_errorCode;};
   
   unsigned short int GetRawSatHigh(void){return m_raw_satHigh;};
   unsigned short int GetRawSatLow (void){return m_raw_satLow ;};
   unsigned short int GetRawSatLvl (void){return m_raw_satLvl ;};
   
   unsigned short int GetProcessedSatHigh(void){return m_processed_satHigh;};
   unsigned short int GetProcessedSatLow (void){return m_processed_satLow ;};
   unsigned short int GetProcessedSatLvl (void){return m_processed_satLvl ;};
   
   unsigned short int GetSatHigh(void){return m_satHigh;};
   unsigned short int GetSatLow (void){return m_satLow ;};
   unsigned short int GetSatLvl (void){return m_satLvl ;};
   
   TCanvas* GetRawDacVsAdcCanvas(void){return m_can_raw_dacVsAdc;};
   TCanvas* GetProcessedDacVsAdcCanvas(void){return m_can_processed_dacVsAdc;};
   
   TCanvas* GetRawPeakVsTs1Canvas(void){return m_can_raw_peakVsTs1;};
   TCanvas* GetProcessedPeakVsTs1Canvas(void){return m_can_processed_peakVsTs1;};
   
   TCanvas* GetRawPeakVsTs2Canvas(void){return m_can_raw_peakVsTs2;};
   TCanvas* GetProcessedPeakVsTs2Canvas(void){return m_can_processed_peakVsTs2;};
private:
   SignalShape(void){};
   
   L1CaloChannelMap* m_l1map;
   CaloDivision m_region;
   
   std::vector<ShapeMakerTree*>* m_v_trees;
   
   const L1CaloChannelId m_coolId;
   
   ChanCalibErrorCode* m_errorCode;
   unsigned int m_phos4errorCode;
   
   CombinedCanvas *m_raw_canvas;
   CombinedCanvas *m_processed_canvas;
   
   DacVsAdcPeakGraph* m_raw_dacVsAdc;
   DacVsAdcPeakGraph* m_processed_dacVsAdc;
   TCanvas* m_can_raw_dacVsAdc;
   TCanvas* m_can_processed_dacVsAdc;
   
   EstAdcVsAdcGraph* m_raw_peakVsTs1;
   EstAdcVsAdcGraph* m_processed_peakVsTs1;
   TCanvas* m_can_raw_peakVsTs1;
   TCanvas* m_can_processed_peakVsTs1;
   
   EstAdcVsAdcGraph* m_raw_peakVsTs2;
   EstAdcVsAdcGraph* m_processed_peakVsTs2;
   TCanvas* m_can_raw_peakVsTs2;
   TCanvas* m_can_processed_peakVsTs2;
   
   MeanValue m_meanPedestal;
   
   unsigned short int m_raw_satHigh;
   unsigned short int m_raw_satLow;
   unsigned short int m_raw_satLvl;
   unsigned short int m_processed_satHigh;
   unsigned short int m_processed_satLow;
   unsigned short int m_processed_satLvl;
   
   unsigned short int m_satHigh;
   unsigned short int m_satLow;
   unsigned short int m_satLvl;
   
   bool m_isEnabled;
   bool m_isValid;
   bool m_isProcessed;
   
   static const unsigned int m_rawSaturation = 1020;
   
   void BuildPlots(void);
   
   std::string GetHistogramName(const std::string base,const L1CaloChannelId coolId) const;
   std::string GetHistogramTitle(const std::string base,const L1CaloChannelId coolId) const;
   
   bool DoNotUseDacForRegion(unsigned int dac, CaloDivision& region);
   
   bool IsChannelDisabled(const unsigned int runNumber,const L1CaloChannelId id) const;
   
   int GetOffset(unsigned int runNumber) const;
   
   TH1* GetOffsetPlot(TH1* histo,const int& offset) const;
   
};




#endif
