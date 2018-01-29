#ifndef SATBCIDTREEFILLER_H
#define SATBCIDTREEFILLER_H

#include <iostream>
#include <vector>
#include <map>

#include "SatBcidTree.h"
#include "MeanValue.h"
#include "L1CaloChannelMap.h"
#include "L1CaloChannelId.h"
#include "EtaPhiId.h"

class SatBcidTreeFiller{
public:
   SatBcidTreeFiller(SatBcidTree *tree);
   ~SatBcidTreeFiller(void){};
   
   bool isTile(void){return m_isTile;};
   void isTile(bool value){m_isTile = value;};
   
   bool isLAr(void){return m_isLAr;};
   void isLAr(bool value){m_isLAr = value;};
   
   void FillTree(void);
private:
   SatBcidTree* m_tree;
   
   L1CaloChannelMap* m_l1map;
   
   std::vector<L1CaloChannelId> m_emptyChannels;
   
   std::map<unsigned int,unsigned int> m_map_etaPhiId_satHigh;
   std::map<unsigned int,unsigned int> m_map_etaPhiId_satLow;
   std::map<unsigned int,unsigned int> m_map_etaPhiId_satLvl;
   
   bool m_isLAr;
   bool m_isTile;
   
   void FillMeans(void);
   void FillHoles(void);
   void FillPlots(void);
   MeanValue GetCircleMean(L1CaloChannelId& id,std::map<unsigned int,unsigned int>& map);
   MeanValue GetEtaMean(L1CaloChannelId& id,std::map<unsigned int,unsigned int>& map);
   MeanValue GetEndcapMean(L1CaloChannelId& id,std::map<unsigned int,unsigned int>& map);
   unsigned int GetIntegerEta(unsigned int inEta);
   
   bool BadLArFEB(L1CaloChannelId& id);
   bool BadLArFEB(EtaPhiId& epId);
   bool OtherBadChannels(L1CaloChannelId& id);
         
   static const unsigned int m_NUM_ETA_BINS = 66;
   static const unsigned int m_MAX_ETA_BIN  = 65;
   static const unsigned int m_MIN_ETA_BIN  =  0;
   
   static const float myPI = 3.14159265;
};



#endif
