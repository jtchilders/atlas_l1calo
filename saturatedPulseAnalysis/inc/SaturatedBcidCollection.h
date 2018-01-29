#ifndef SATURATEDBCIDCOLLECTION_H
#define SATURATEDBCIDCOLLECTION_H

#include <map>

#include "SaturatedBcid.h"
#include "EtaPhiId.h"

class SaturatedBcidCollection{
public:
   SaturatedBcidCollection(void){};
   
   typedef std::map<unsigned int,SaturatedBcid>::const_iterator itr;
   
   void push_back(const EtaPhiId id,const SaturatedBcid entry);
   
   void clear(void){m_map_etaPhiId_satBcid.clear();};
   
   itr findSameEta(const EtaPhiId epId) const;
   
   itr end(void) const {return m_map_etaPhiId_satBcid.end();};
   itr begin(void) const {return m_map_etaPhiId_satBcid.begin();};
   
private:
   std::map<unsigned int,SaturatedBcid> m_map_etaPhiId_satBcid;
   
   static const unsigned int MAX_PHI = 63;
   
};



#endif

