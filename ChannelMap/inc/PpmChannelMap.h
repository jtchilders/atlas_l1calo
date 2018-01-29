////////////////////////////////////////////////////////////////
/// PPM Channel Mapping Tool
/// J Taylor Childers III
/// Heidelberg Universitaet
///
/// This tool can be used in three ways:
/// 1. Use SetEtaPhi() in order to specify an eta, phi, and
///    CAL layer for the system, in which case the corresponding
///    corresponding crate, module number, mcm, and channel  
///    will be selected. These can be accessed using the 
///    corresponding GetCrate(), GetPpm(), etc., functions.
/// 2. Use SetChannel() in order to specify the crate,
///    module number, mcm, and channel. Then access
///    the corresponding Eta and Phi using the appropriate
///    "Get" functions.
/// 3. Use SetChannelID() in order to specify l1calo COOL ID.
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


#ifndef PPMCHANNELMAP_H
#define PPMCHANNELMAP_H

#include <iostream>
#include <cmath>
#include <map>
#include <vector>

#include "CaloLayer.h"
#include "FcalLayer.h"
#include "EtaPhiId.h"
#include "L1CaloChannelId.h"

class PpmChannelMap{

public:
   PpmChannelMap();
   ~PpmChannelMap();
   
   void SetEtaPhi(float,float,CaloLayer);
   void SetModifiedEtaPhi(float,float,CaloLayer);
   void SetEtaPhi(float,float,float,float,CaloLayer);
   
   void SetChannel(unsigned int,unsigned int,unsigned int,unsigned int);
   void SetChannelID(unsigned int);
   void SetChannelID(L1CaloChannelId id);
   
   bool IsChannelUsed(void){return m_currentChannelIsUsed;};
   
   
   float GetEta(void){return m_currentEtaPhiId.GetEta();};
   float GetModifiedEta(void); // this is for FCAL2/3 combined layers
   unsigned int GetModifiedIntegerEta(void); // this is for the FCAL2/3 combined layers
   std::vector<bool>* IsModifiedEtaAvailable(void){return &m_vect_isModifiedEtaAvailable;}; // tells if GetModifiedEta can be used
   // need the +49 because conversion assumes integer eta starts at 0, which corresponds to real eta = -4.9
   float GetDeltaEta(void){return m_currentDeltaId.GetEta()+49;};
   float GetPhi(void){return m_currentEtaPhiId.GetPhi();};
   float GetDeltaPhi(void){return m_currentDeltaId.GetPhi();};
   
   CaloLayer GetLayer(void){return m_currentLayer;};
   std::vector<FcalLayer> *GetFcalLayer(void){return &m_currentFcalLayer;};
   
   std::vector<unsigned int>* GetCrate(void){return &m_vect_currentCrate;};
   std::vector<unsigned int>* GetModule(void){return &m_vect_currentModule;};
   std::vector<unsigned int>* GetSubmodule(void){return &m_vect_currentSubmodule;};
   std::vector<unsigned int>* GetChannel(void){return &m_vect_currentChannel;};
   
   std::vector<L1CaloChannelId>* GetChannelID(void){return &m_vect_currentChannelId;};
   
   void ClearPpm(void);

private:
   
   static const float        myPI;
   
   static const unsigned int MAX_CRATE     = 8;
   static const unsigned int MIN_CRATE     = 0;
   
   static const unsigned int MAX_MODULE    = 16;
   static const unsigned int MIN_MODULE    = 0;
   
   static const unsigned int MAX_SUBMODULE = 16;
   static const unsigned int MIN_SUBMODULE = 0;
   
   static const unsigned int MAX_CHANNEL   = 4;
   static const unsigned int MIN_CHANNEL   = 0;
   
   static const unsigned int MAX_UINT_ETA  = 98;
   static const unsigned int MIN_UINT_ETA  = 0;
   
   static const unsigned int MAX_UINT_PHI  = 64;
   static const unsigned int MIN_UINT_PHI  = 0;
   
   static const float        MAX_ETA;
   static const float        MIN_ETA;
   
   static const float        MAX_PHI;
   static const float        MIN_PHI;
   
   std::map<unsigned int,unsigned int> m_map_tt_eta;
   std::map<unsigned int,unsigned int> m_map_tt_phi;
   
   std::map<unsigned int,unsigned int> m_map_tt_deltaEta;
   std::map<unsigned int,unsigned int> m_map_tt_deltaPhi;
   
   std::map<unsigned int,CaloLayer> m_map_tt_layer;
   
   std::map<unsigned int,std::vector<L1CaloChannelId> > m_map_etaPhi_channelId;
   
   std::map<unsigned int,bool> m_map_channelId_usedChannel;
   bool m_currentChannelIsUsed;
   
   unsigned int m_currentEta;
   unsigned int m_currentDeltaEta;
   unsigned int m_currentPhi;
   unsigned int m_currentDeltaPhi;
   
   EtaPhiId m_currentEtaPhiId;
   EtaPhiId m_currentDeltaId;
   
   std::vector<unsigned int> m_vect_currentCrate;
   std::vector<unsigned int> m_vect_currentModule;
   std::vector<unsigned int> m_vect_currentSubmodule;
   std::vector<unsigned int> m_vect_currentChannel;
   
   std::vector<L1CaloChannelId> m_vect_currentChannelId;
   
   std::vector<bool> m_vect_isModifiedEtaAvailable;
   
   CaloLayer m_currentLayer;
   std::vector<FcalLayer> m_currentFcalLayer;
   
   void FillEtaPhi(void);
   
   void GetPpmChannel(unsigned int,unsigned int,CaloLayer,std::vector<L1CaloChannelId>*);
   
   void GetPpmChannels(unsigned int,unsigned int,unsigned int,unsigned int,CaloLayer,std::vector<L1CaloChannelId>*);
   
   void SplitPpmChannels(std::vector<L1CaloChannelId>,std::vector<unsigned int>*,std::vector<unsigned int>*,std::vector<unsigned int>*,std::vector<unsigned int>*);
   
   void GetPpmEtaPhi(unsigned int,unsigned int,unsigned int,unsigned int,unsigned int&,unsigned int&,CaloLayer&);
   
   bool FloatIsEqualTo(const float x, const float y);
};


#endif
