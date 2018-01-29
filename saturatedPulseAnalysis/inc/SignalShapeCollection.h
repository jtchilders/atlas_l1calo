#ifndef SIGNALSHAPECOLLECTION_H
#define SIGNALSHAPECOLLECTION_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#include "TTree.h"
#include "TGraph.h"
#include "TProfile.h"
#include "TH1F.h"
#include "TF1.h"
#include "TFile.h"
#include "TCanvas.h"

#include "L1CaloChannelMap.h"
#include "PixelMap.h"

#include "ShapeMakerTree.h"
#include "SatBcidTree.h"
#include "SignalShape.h"
#include "CaloDivision.h"

class SignalShapeCollection{
public:
   
   enum RUN_TYPE{
      TILE_RUN = 1,
      LAR_RUN = 2
   };
   
   SignalShapeCollection(std::vector<ShapeMakerTree*>* trees,RUN_TYPE runType,L1CaloChannelMap* map = 0);
   ~SignalShapeCollection(void);
   
   void SetOutputDirectory(std::string dirName){m_s_outputPath = dirName;};
   
private:
   SignalShapeCollection(void){};
   
   L1CaloChannelMap* m_l1map;
   bool m_deleteChannelMap;
   
   bool m_tileRun;
   bool m_larRun;
   
   std::vector<ShapeMakerTree*>* m_v_trees;
   
   std::string m_s_outputPath;
   
   std::string m_s_databaseFilename;
   
   PixelMap<unsigned short int>* m_pm_raw_em_satHigh;
   PixelMap<unsigned short int>* m_pm_raw_had_satHigh;
   TH1I* m_h_raw_satHigh;
   PixelMap<unsigned short int>* m_pm_raw_em_satLow;
   PixelMap<unsigned short int>* m_pm_raw_had_satLow;
   TH1I* m_h_raw_satLow;
   PixelMap<unsigned short int>* m_pm_raw_em_satLvl;
   PixelMap<unsigned short int>* m_pm_raw_had_satLvl;
   TH1I* m_h_raw_satLvl;
   
   PixelMap<unsigned short int>* m_pm_processed_em_satHigh;
   PixelMap<unsigned short int>* m_pm_processed_had_satHigh;
   TH1I* m_h_processed_satHigh;
   PixelMap<unsigned short int>* m_pm_processed_em_satLow;
   PixelMap<unsigned short int>* m_pm_processed_had_satLow;
   TH1I* m_h_processed_satLow;
   PixelMap<unsigned short int>* m_pm_processed_em_satLvl;
   PixelMap<unsigned short int>* m_pm_processed_had_satLvl;
   TH1I* m_h_processed_satLvl;
   
   PixelMap<unsigned short int>* m_pm_em_satHigh;
   PixelMap<unsigned short int>* m_pm_had_satHigh;
   TH1I* m_h_satHigh;
   PixelMap<unsigned short int>* m_pm_em_satLow;
   PixelMap<unsigned short int>* m_pm_had_satLow;
   TH1I* m_h_satLow;
   PixelMap<unsigned short int>* m_pm_em_satLvl;
   PixelMap<unsigned short int>* m_pm_had_satLvl;
   TH1I* m_h_satLvl;
   
   std::vector<TH1I*> m_v_h_satHigh;
   std::vector<TH1I*> m_v_h_satLow;
   std::vector<TH1I*> m_v_h_satLvl;
   
   PixelMap<unsigned int>* m_pm_em_errorCode;
   PixelMap<unsigned int>* m_pm_had_errorCode;
   
   
   
   TH1I* m_h_diff_satHigh;
   TH1I* m_h_diff_satLow;
   
   // TTree files
   TFile* m_treeFile;
   std::string m_s_treeFile;
   std::string m_s_treeFilename;
   
   
   std::string  m_s_rawCanvasDirectory;
   std::string  m_s_processedCanvasDirectory;
   std::string  m_s_summaryPlotsDirectory;
   std::string  m_s_rawDacVsAdcDirectory;
   std::string  m_s_processedDacVsAdcDirectory;
   std::string  m_s_rawPeakVsTs1Directory;
   std::string  m_s_rawPeakVsTs2Directory;
   std::string  m_s_processedPeakVsTs1Directory;
   std::string  m_s_processedPeakVsTs2Directory;
   
   static const unsigned int m_rawSaturation = 1020;
   
   // PPM Hardware Limits
   static const unsigned int PPM_MAX_CRATE = 7;
   static const unsigned int PPM_MIN_CRATE = 0;
   
   static const unsigned int PPM_MAX_MODULE = 15;
   static const unsigned int PPM_MIN_MODULE = 0;
   
   static const unsigned int PPM_MAX_SUBMODULE = 15;
   static const unsigned int PPM_MIN_SUBMODULE = 0;
   
   static const unsigned int PPM_MAX_CHANNEL = 3;
   static const unsigned int PPM_MIN_CHANNEL = 0;
   
   void FillCollection(void);
   bool BadChannel(L1CaloChannelId&);
};


#endif
