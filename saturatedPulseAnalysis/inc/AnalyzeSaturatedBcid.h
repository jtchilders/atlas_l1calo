#ifndef ANALYZESATURATEDBCID_H
#define ANALYZESATURATEDBCID_H

#include <vector>
#include <map>

#include "TCanvas.h"

#include "ShapeMakerTree.h"
#include "DacVsAdcPeakGraph.h"
#include "EstAdcVsAdcGraph.h"
#include "L1CaloChannelMap.h"
#include "L1CaloChannelId.h"
#include "ChanCalibErrorCode.h"
#include "CombinedCanvas.h"

#include "PixelMap.h"

class AnalyzeSaturatedBcid{
public:
   AnalyzeSaturatedBcid(std::vector<ShapeMakerTree*> *trees);
   ~AnalyzeSaturatedBcid(void);
   
   void PopulateGraphs(void);
   
private:
   AnalyzeSaturatedBcid(void){};
   
   std::vector<ShapeMakerTree*> *m_v_inputTree;
   
   L1CaloChannelMap *m_l1map;
   
   CombinedCanvas* m_raw_canvas;
   CombinedCanvas* m_processed_canvas;
   
   typedef std::map<unsigned int,DacVsAdcPeakGraph*>::iterator DacVsAdcPeakGraphItr;
   std::map<unsigned int,DacVsAdcPeakGraph*> *m_map_raw_coolId_dacVsAdcPeakGraph;
   std::map<unsigned int,DacVsAdcPeakGraph*> *m_map_processed_coolId_dacVsAdcPeakGraph;
   
   DacVsAdcPeakGraphItr GetItrRawDacVsAdc(const unsigned int coolId) const;
   DacVsAdcPeakGraphItr GetItrProcDacVsAdc(const unsigned int coolId) const;
   
   typedef std::map<unsigned int,EstAdcVsAdcGraph*>::iterator EstAdcVsAdcGraphItr;
   std::map<unsigned int,EstAdcVsAdcGraph*> *m_map_raw_coolId_ts1_estAdcVsAdcGraph;
   std::map<unsigned int,EstAdcVsAdcGraph*> *m_map_processed_coolId_ts1_estAdcVsAdcGraph;
   std::map<unsigned int,EstAdcVsAdcGraph*> *m_map_raw_coolId_ts2_estAdcVsAdcGraph;
   std::map<unsigned int,EstAdcVsAdcGraph*> *m_map_processed_coolId_ts2_estAdcVsAdcGraph;
   
   EstAdcVsAdcGraphItr GetItrRawAdcVsTs1(const unsigned int coolId) const;
   EstAdcVsAdcGraphItr GetItrRawAdcVsTs2(const unsigned int coolId) const;
   EstAdcVsAdcGraphItr GetItrProcAdcVsTs2(const unsigned int coolId) const;
   EstAdcVsAdcGraphItr GetItrProcAdcVsTs1(const unsigned int coolId) const;
   
   PixelMap<double>* m_pm_raw_em_satThreshHigh;
   PixelMap<double>* m_pm_raw_em_satThreshLow;
   PixelMap<double>* m_pm_raw_had_satThreshHigh;
   PixelMap<double>* m_pm_raw_had_satThreshLow;
   
   PixelMap<double>* m_pm_processed_em_satThreshHigh;
   PixelMap<double>* m_pm_processed_em_satThreshLow;
   PixelMap<double>* m_pm_processed_had_satThreshHigh;
   PixelMap<double>* m_pm_processed_had_satThreshLow;
   
   PixelMap<unsigned int>* m_pm_em_errorBits;
   PixelMap<unsigned int>* m_pm_had_errorBits;
   
   PixelMap<unsigned short int>* m_pm_raw_em_satEntries;
   PixelMap<unsigned short int>* m_pm_raw_had_satEntries;
   PixelMap<unsigned short int>* m_pm_processed_em_satEntries;
   PixelMap<unsigned short int>* m_pm_processed_had_satEntries;
   
   PixelMap<unsigned short int>* m_pm_raw_em_unsatEntries;
   PixelMap<unsigned short int>* m_pm_raw_had_unsatEntries;
   PixelMap<unsigned short int>* m_pm_processed_em_unsatEntries;
   PixelMap<unsigned short int>* m_pm_processed_had_unsatEntries;
   
   
   std::map<unsigned int,ChanCalibErrorCode> m_map_coolId_errorCode;
   
   
   static const unsigned short int m_saturationLevel = 1020;
   
   
};




#endif

