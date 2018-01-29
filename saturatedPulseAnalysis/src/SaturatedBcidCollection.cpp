#include "SaturatedBcidCollection.h"


void SaturatedBcidCollection::push_back(const EtaPhiId id, const SaturatedBcid entry){
   m_map_etaPhiId_satBcid[id.GetId()] = entry;
}

SaturatedBcidCollection::itr SaturatedBcidCollection::findSameEta(const EtaPhiId epId) const{
   
   const unsigned int startPhi = epId.GetIntegerPhi();
   
   itr outItr;
   
   // Start by counting down from the current phi because usually
   // the map is filled from lowest phi to highest phi
   for(unsigned int phi = startPhi-1;phi>=0;--phi){
      EtaPhiId temp(epId.GetIntegerEta(),phi,epId.GetLayer());
      outItr = m_map_etaPhiId_satBcid.find(temp.GetId());
      if(outItr == m_map_etaPhiId_satBcid.end())
         continue;
      else
         return outItr;
   }
   
   // now try looking in the top half just in case
   for(unsigned int phi = startPhi+1;phi<=MAX_PHI;++phi){
      EtaPhiId temp(epId.GetIntegerEta(),phi,epId.GetLayer());
      outItr = m_map_etaPhiId_satBcid.find(temp.GetId());
      if(outItr == m_map_etaPhiId_satBcid.end())
         continue;
      else
         return outItr;
   }
   
   
   return m_map_etaPhiId_satBcid.end();
}
