////////////////////////////////////////////////////////////////
/// CPM Channel Mapping Tool
/// J Taylor Childers III
/// Heidelberg Universitaet
///
/// This tool can be used in two ways:
/// 1. Use SetEtaPhi() in order to specify an eta, phi, and
///    CAL layer for the system, in which case the corresponding
///    corresponding crate, module number, and channel will be 
///    selected. These can be accessed using the 
///    corresponding GetCrate(), GetCpm(), etc., functions.
/// 2. Use SetChannel() in order to specify the crate,
///    module number, CAL layer, and channel. Then access
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
/// ************************ IMPORTANT *****************************
/// It should be noted that the channel ids are currently only 
/// using serial channel numbering, not CP Chip.
/// ****************************************************************
///
/// Added functionality for CPMRoI usage on 13 Aug 2010:
/// SetCPMRoI() functions can now be used to interpret the CPMRoI
/// object used in athena. Keep in mind, an RoI is associated with
/// an EM channel summed with a HAD channel so there are two
/// channels associated with this RoI. To get them you must do the
/// following:
/// SetCPMRoI(roi,CaloLayer::EM);
/// L1CaloChannelId em_cpm_id = GetChannelId()->at(0);
/// SetCPMRoI(roi,CaloLayer::HAD);
/// L1CaloChannelId had_cpm_id = GetChannelId()->at(0);
/// now you have the two channels associated with this RoI.
////////////////////////////////////////////////////////////////////


#ifndef CPMCHANNELMAP_H
#define CPMCHANNELMAP_H

#include <iostream>
#include <cmath>
#include <map>
#include <vector>

#include "L1CaloChannelId.h"
#include "EtaPhiId.h"
#include "CaloLayer.h"
#include "CPMRoI.h"


class CpmChannelMap{
public:
   CpmChannelMap();
   ~CpmChannelMap();
   
   void SetEtaPhi(float,float,CaloLayer);
   void SetEtaPhi(float,float,float,float,CaloLayer);
   void SetChannelSerializer(unsigned int crate,unsigned int module,unsigned int submodule,unsigned int channel);
   void SetChannelCpChip(unsigned int crate,unsigned int module,unsigned int submodule, unsigned int channel);
   void SetCPMRoI(CPMRoI&,CaloLayer&);
   void SetCPMRoI(unsigned int crate,unsigned int module,unsigned int submodule,unsigned int location,CaloLayer&);
   void SetCPMRoI(unsigned int roiWord,CaloLayer&);
   
   bool IsChannelUsed(void){return m_currentChannelUsed;};
   
   float GetEta(void){return m_currentEtaPhiId->GetEta();};
   float GetPhi(void){return m_currentEtaPhiId->GetPhi();};
   
   // need the +4.9 because conversion assumes integer eta starts at 0, which corresponds to real eta = -4.9
   float GetDeltaEta(void){return (float)m_currentDeltaEta/10.0;};
   float GetDeltaPhi(void){return (float)m_currentDeltaPhi*(2.0*myPI/64.0);};
   
   std::vector<unsigned int>* GetCrate(void){return &m_currentCrate;};
   std::vector<unsigned int>* GetModule(void){return &m_currentModule;};
   std::vector<unsigned int>* GetSerializerSubmodule(void){return &m_currentSubmoduleSerializer;};
   std::vector<unsigned int>* GetSerializerChannel(void){return &m_currentChannelSerializer;};
   std::vector<unsigned int>* GetCpChipSubmodule(void){return &m_currentSubmoduleChip;};
   std::vector<unsigned int>* GetCpChipChannel(void){return &m_currentChannelChip;};
   
   std::vector<L1CaloChannelId>* GetChannelID(void){return m_currentChannelId;};
   
   CaloLayer GetLayer(void){return m_currentEtaPhiId->GetLayer();};
   
   void ClearCpm(void);

private:
   

   // CPM Hardware Limits
   static const unsigned int MAX_CRATE = 11;
   static const unsigned int MIN_CRATE = 8;
   
   static const unsigned int MAX_MODULE = 14;
   static const unsigned int MIN_MODULE = 1;
   
   // CPM has two different ways to number the SUBMODULE and CHANNEL
   static const unsigned int MAX_SUBMODULE_CHIP = 7;
   static const unsigned int MIN_SUBMODULE_CHIP = 0;
   
   static const unsigned int MAX_CHANNEL_CHIP = 15;
   static const unsigned int MIN_CHANNEL_CHIP = 0;
   
   static const unsigned int MAX_SUBMODULE_SERIAL = 19;
   static const unsigned int MIN_SUBMODULE_SERIAL = 0;
   
   static const unsigned int MAX_CHANNEL_SERIAL = 7;
   static const unsigned int MIN_CHANNEL_SERIAL = 0;
   
   // static const unsigned int CPM_MAX_CRATE    = 4;
   // static const unsigned int CPM_MAX_CPM      = 14;
   // static const unsigned int CPM_MAX_LAYER    = 2;
   // static const unsigned int CPM_MAX_CHAN     = 76;
   
   static const unsigned int MAX_UINT_ETA  = 97;
   static const unsigned int MIN_UINT_ETA  = 0;
   
   static const unsigned int MAX_UINT_PHI  = 63;
   static const unsigned int MIN_UINT_PHI  = 0;
   
   static const float        MAX_ETA;
   static const float        MIN_ETA;
   
   static const float        MAX_CPM_ETA;
   static const float        MIN_CPM_ETA;
   
   static const float        MAX_PHI;
   static const float        MIN_PHI;
   
   static const float        myPI;
   
   std::map<unsigned int,unsigned int> m_map_channelId_etaPhiId;
   std::map<unsigned int,std::vector<L1CaloChannelId> > m_map_etaPhiId_channelId;
   
   std::map<unsigned int,bool> m_map_channelId_usedChannel;
   
   EtaPhiId *m_currentEtaPhiId;
   unsigned int m_currentDeltaEta;
   unsigned int m_currentDeltaPhi;
   std::vector<L1CaloChannelId> *m_currentChannelId;
   
   bool m_currentChannelUsed;
   
   std::vector<unsigned int> m_currentCrate;
   std::vector<unsigned int> m_currentModule;
   std::vector<unsigned int> m_currentSubmoduleSerializer;
   std::vector<unsigned int> m_currentChannelSerializer;
   std::vector<unsigned int> m_currentSubmoduleChip;
   std::vector<unsigned int> m_currentChannelChip;
   
   void FillEtaPhi(void);
   
   void GetCpmChannels(unsigned int,unsigned int,unsigned int,unsigned int,CaloLayer,std::vector<L1CaloChannelId>*);
   
   void FillCurrentChannelFromId(std::vector<L1CaloChannelId>* id);
   
   bool FloatIsEqualTo(const float x, const float y);
   
   unsigned int GetCpChipFromSerializerChip(unsigned int schip){return (unsigned int)(schip/2)-1;};
   unsigned int GetCpChipChannelFromSerializerChip(unsigned int schip,unsigned int schannel)
      {return ((schip % 2) == 0) ? schannel : schannel + 8;};
   
   unsigned int GetSerializerChipFromCpChip(unsigned int cpChip,unsigned int cpChannel)
      {return cpChannel >= 8 ? (cpChip+1)*2 + 1 : (cpChip+1)*2;};
   unsigned int GetSerializerChipChannelFromCpChip(unsigned int cpChannel)
      {return cpChannel >= 8 ? cpChannel-8 : cpChannel;};
};

#endif
