////////////////////////////////////////////////////////////////
/// TCPP Channel Mapping Tool
/// J Taylor Childers III
/// Heidelberg Universitaet
///
/// This tool can be used in two ways:
/// 1. Use SetEtaPhi() in order to specify an eta, phi, and
///    CAL layer for the system, in which case the corresponding
///    corresponding crate, module number, mcm, and channel  
///    will be selected. These can be accessed using the 
///    corresponding GetCrate(), GetPpm(), etc., functions.
/// 2. Use SetChannel() in order to specify the crate,
///    module number, mcm, and channel. Then access
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


#ifndef TCPPCHANNELMAP_H
#define TCPPCHANNELMAP_H

#include <iostream>
#include <cmath>
#include <map>
#include <vector>

#include "L1CaloChannelId.h"
#include "CaloLayer.h"
#include "EtaPhiId.h"
#include "TileDrawerId.h"

class TcppChannelMap{

public:
	TcppChannelMap();
	~TcppChannelMap();
	
	void SetEtaPhi(float,float,CaloLayer);
	void SetEtaPhi(float,float,float,float,CaloLayer);
	
	void SetOutputChannel(const unsigned int,const unsigned int,const unsigned int,const unsigned int);
	void SetOutputChannelId(const L1CaloChannelId id);
	
   void SetInputChannel(const unsigned int,const unsigned int,const unsigned int,const unsigned int);
   void SetInputChannelId(const L1CaloChannelId id);
	
	float GetEta(void){return m_currentEtaPhiId.GetEta();};
	float GetDeltaEta(void){return ((float)((int)m_currentDeltaEta - 49))/10.0;};
	float GetPhi(void){return m_currentEtaPhiId.GetPhi();};
	float GetDeltaPhi(void){return ((float)m_currentDeltaPhi)*((2.0*myPI)/(64.0));};
	
	CaloLayer GetLayer(void){return m_currentEtaPhiId.GetLayer();};
	
	std::vector<unsigned int>* GetCrate(void){return &m_currentCrate;};
	std::vector<unsigned int>* GetModule(void){return &m_currentModule;};
	std::vector<unsigned int>* GetOutputSubmodule(void){return &m_currentOutputSubmodule;};
	std::vector<unsigned int>* GetOutputChannel(void){return &m_currentOutputChannel;};
	std::vector<unsigned int>* GetInputSubmodule(void){return &m_currentInputSubmodule;};
	std::vector<unsigned int>* GetInputChannel(void){return &m_currentInputChannel;};
	
	std::vector<L1CaloChannelId>* GetOutputChannelId(void){return &m_currentOutputChannelId;};
	std::vector<L1CaloChannelId>* GetInputChannelId(void){return &m_currentInputChannelId;};
	
   std::vector<TileDrawerId>* GetTileDrawer(void){return &m_currentTileDrawer;};
   
	void ClearTcpp(void);
	
private:
	
   static const unsigned int MAX_UINT_ETA  = 97;
   static const unsigned int MIN_UINT_ETA  = 0;
   
   static const unsigned int MAX_UINT_PHI  = 63;
   static const unsigned int MIN_UINT_PHI  = 0;
   
   static const float        MAX_ETA;
   static const float        MIN_ETA;
   
   static const float        TCPP_MAX_ETA;
   static const float        TCPP_MIN_ETA;
   
   static const float        MAX_PHI;
   static const float        MIN_PHI;
   
   static const float        myPI;
   
   static const unsigned int MAX_CRATE = 3;
   static const unsigned int MIN_CRATE = 0;
   
   static const unsigned int MAX_MODULE = 15;
   static const unsigned int MIN_MODULE = 0;
   
   static const unsigned int MAX_OUTPUT_CONNECTOR = 2;
   static const unsigned int MIN_OUTPUT_CONNECTOR = 0;
   
   static const unsigned int MAX_OUTPUT_CHANNEL = 14;
   static const unsigned int MIN_OUTPUT_CHANNEL = 0;
   
   static const unsigned int MAX_INPUT_CONNECTOR = 3;
   static const unsigned int MIN_INPUT_CONNECTOR = 0;
   
   static const unsigned int MAX_INPUT_CHANNEL = 8;
   static const unsigned int MIN_INPUT_CHANNEL = 0;
   
	std::map<unsigned int,unsigned int> m_map_channelId_etaPhiId;
	std::map<unsigned int,L1CaloChannelId> m_map_etaPhiId_channelId;
	
	
   EtaPhiId m_currentEtaPhiId;
   
	unsigned int m_currentDeltaEta;
	unsigned int m_currentDeltaPhi;
	
	std::vector<unsigned int> m_currentCrate;
	std::vector<unsigned int> m_currentModule;
	std::vector<unsigned int> m_currentOutputSubmodule;
	std::vector<unsigned int> m_currentOutputChannel;
	std::vector<unsigned int> m_currentInputSubmodule;
	std::vector<unsigned int> m_currentInputChannel;
   
   std::vector<unsigned int> m_currentTowerNumber;
	
   std::vector<TileDrawerId> m_currentTileDrawer;
   
	std::vector<L1CaloChannelId> m_currentOutputChannelId;
	std::vector<L1CaloChannelId> m_currentInputChannelId;
	
	void FillEtaPhi(void);
   
   void GetInputFromOutput(const unsigned int outConnector,const unsigned int outChannel, unsigned int& inConnector,unsigned int& inChannel) const;
   void GetOutputFromInput(const unsigned int inConnector,const unsigned int inChannel, unsigned int& outConnector,unsigned int& outChannel) const;
   unsigned int GetTowerNumber(const unsigned int outChannel) const;
   unsigned int GetEtaFromId(const L1CaloChannelId id) const;
	unsigned int GetEtaFromChannel(const unsigned int crate,const unsigned int outChannel) const;
   unsigned int GetPhiFromId(const L1CaloChannelId id) const;
   unsigned int GetPhiFromChannel(const unsigned int crate,const unsigned int module,const unsigned int outConnector) const;
   
   bool CheckOutputChannel(const unsigned int& inCrate,const unsigned int& inModule,const unsigned int& inSubmodule,const unsigned int& inChannel) const;
   bool CheckInputChannel(const unsigned int& inCrate,const unsigned int& inModule,const unsigned int& inSubmodule,const unsigned int& inChannel) const;
   bool CheckEtaPhiRange(const float& inEta, const float& inPhi,CaloLayer& inLayer) const;
   bool CheckDeltaEtaPhiRange(const float& inEta,const float& inDeltaEta,const float& inPhi,const float& inDeltaPhi,CaloLayer& inLayer) const;
   
   TileDrawerId GetTileDrawerFromOutputId(const L1CaloChannelId outputId);
   
   void FindChannels(const unsigned int inEta,const unsigned int inDeltaEta,const unsigned int inPhi,const unsigned int inDeltaPhi,std::vector<L1CaloChannelId>& id);
   void FillCurrentChannelFromOutputId(std::vector<L1CaloChannelId>* id);
   bool FloatIsEqualTo(const float x, const float y) const;
};


#endif
