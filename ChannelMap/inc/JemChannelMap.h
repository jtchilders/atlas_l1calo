////////////////////////////////////////////////////////////////
/// JEM Channel Mapping Tool
/// J Taylor Childers III
/// Heidelberg Universitaet
///
/// This tool can be used in two ways:
/// 1. Use SetEtaPhi() in order to specify an eta, phi, and
///    CAL layer for the system, in which case the corresponding
///    corresponding crate, module number, and channel will be 
///    selected. These can be accessed using the 
///    corresponding GetCrate(), GetJem(), etc., functions.
/// 2. Use SetChannel() in order to specify the crate,
///    module number, and channel. Then access
///    the corresponding Eta and Phi using the appropriate
///    "Get" functions.
///
///    Note: After either of the above are set, you can 
///          get the deltaEta and deltaPhi for the
///          associated channel.
///    
/// In the case of 2, the eta and phi are the coordinates
/// of the bottom left corner of the channel and the deltaEta
/// and deltaPhi are the width and height of the channel
/// as measured from that reference point.
///
/// In the case of 1, the eta and phi returned by the GetEta/GetPhi
/// functions are the original eta/phi passed to the SetEta/Phi
/// functions.
///
////////////////////////////////////////////////////////////////////

#ifndef JEMCHANNELMAP_H
#define JEMCHANNELMAP_H

#include <iostream>
#include <cmath>
#include <map>
#include <vector>

#include "L1CaloChannelId.h"
#include "EtaPhiId.h"

class JemChannelMap{

public:
   JemChannelMap(void);
   ~JemChannelMap(void);
   
   void SetEtaPhi(float,float,CaloLayer);
   void SetChannel(unsigned int,unsigned int,unsigned int);
   void SetChannelId(L1CaloChannelId);
   
   float GetEta(void){return m_currentEtaPhiId.GetEta();};
   float GetPhi(void){return m_currentEtaPhiId.GetPhi();};
   
   // need the +4.9 because conversion assumes integer eta starts at 0, which corresponds to real eta = -4.9 and delta's count from 0.0
   float GetDeltaEta(void){return m_currentDeltaId.GetEta()+4.9;}; 
   float GetDeltaPhi(void){return m_currentDeltaId.GetPhi();};
   
   
   std::vector<unsigned int>* GetCrate(void){return &m_vect_currentCrate;};
   std::vector<unsigned int>* GetModule(void){return &m_vect_currentModule;};
   std::vector<unsigned int>* GetChannel(void){return &m_vect_currentChannel;};
   
   std::vector<L1CaloChannelId>* GetChannelID(void){return &m_vect_currentChannelId;};
   
   CaloLayer GetLayer(void){return m_currentLayer;};
   
   void ClearJem(void);

private:
   
   // JEM Hardware Limits
   static const unsigned int MAX_CRATE = 13;
   static const unsigned int MIN_CRATE = 12;
   
   static const unsigned int MAX_MODULE = 15;
   static const unsigned int MIN_MODULE = 0;
   
   static const unsigned int MAX_CHANNEL = 87;
   static const unsigned int MIN_CHANNEL = 0;
   
   static const unsigned int MAX_UINT_ETA  = 97;
   static const unsigned int MIN_UINT_ETA  = 0;
   
   static const unsigned int MAX_UINT_PHI  = 63;
   static const unsigned int MIN_UINT_PHI  = 0;
   
   static const float        MAX_ETA;
   static const float        MIN_ETA;
   
   static const float        MAX_PHI;
   static const float        MIN_PHI;
   
   // eta/phi ID as a function of channel ID
   std::map<unsigned int,unsigned int> m_map_jem_eta;
   std::map<unsigned int,unsigned int> m_map_jem_phi;
   
   // delta eta/phi ID as a function of channel ID
   std::map<unsigned int,unsigned int> m_map_jem_deltaEta;
   std::map<unsigned int,unsigned int> m_map_jem_deltaPhi;
   
   // layer as a function of channel ID
   std::map<unsigned int,CaloLayer> m_map_jem_layer;
   
   // channel ID as a function of eta ID
   std::map<unsigned int,std::vector<L1CaloChannelId> > m_map_etaPhiId_channelId;
   
   unsigned int m_currentEta;
   unsigned int m_currentPhi;
   
   EtaPhiId m_currentEtaPhiId;
   
   unsigned int m_currentDeltaEta;
   unsigned int m_currentDeltaPhi;
   
   EtaPhiId m_currentDeltaId;
   
   std::vector<unsigned int> m_vect_currentCrate;
   std::vector<unsigned int> m_vect_currentModule;
   std::vector<unsigned int> m_vect_currentChannel;
   
   std::vector<L1CaloChannelId> m_vect_currentChannelId;
   
   CaloLayer m_currentLayer;
   
   void FillEtaPhi(void);
   
   void SearchForJemChannel(unsigned int,unsigned int,CaloLayer,std::vector<unsigned int>*,std::vector<unsigned int>*,std::vector<unsigned int>*);
   
   void GetJemEtaPhi(unsigned int,unsigned int,unsigned int,unsigned int&,unsigned int&,CaloLayer&);
   void GetJemChannel(unsigned int,unsigned int,CaloLayer,std::vector<L1CaloChannelId>*);
   
   void SplitJemChannels(std::vector<L1CaloChannelId>,std::vector<unsigned int>*,std::vector<unsigned int>*,std::vector<unsigned int>*);
   
   bool FloatIsEqualTo(const float x, const float y);
};


#endif
