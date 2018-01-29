////////////////////////////////////////////////////////////////
/// L1Calo Channel Mapping Tool
/// J Taylor Childers III
/// Heidelberg Universitaet
///
/// This tool can be used in two ways:
/// 1. Use SetEtaPhi() in order to specify an eta, phi, and
///    CAL layer for the system, in which case the corresponding
///    crate, module number, (submodule number if needed) and channel  
///    for all subsystems will be selected. These can be 
///    accessed using the corresponding GetPpmCrate(), GetPpmNum(),
///    GetCpmCrate(), GetJemCrate(), etc., functions.
/// 2. Use SetPpmChannel(), SetCpmChannel(), or SetJemChanel() to 
///    specify the crate, module number, and channel for the
///    corresponding system. Then the corresponding Eta/Phi
///    and crate/module/channel of all other subsystems can
///    be accessed using the appropriate "Get" functions.
///
///    Note: After either of the above are set, you can 
///          get the deltaEta and deltaPhi for the
///          associated channel AND the detector Region
///          and layer.
///    
/// In the case of 2, the eta and phi are the coordinates
/// of the bottom left corner of the channel of system specified
/// and the deltaEta and deltaPhi are the width and height 
/// of the channel as measured from that reference point. In
/// this case the eta/phi global variables are filled with
/// the eta/phi coordinates of the subsystem that was originally
/// specified.
/// 
///
/// In the case of 1, the eta and phi returned by the GetEta/GetPhi
/// functions are the original eta/phi passed to the SetEta/Phi
/// functions. 
////
/// The individual cpmDeltaEta/Phi, ppmDeltaEta/Phi, 
/// or jemDeltaEta/Phi variables are filled with the corresponding
/// delta eta and phi for that subsystem.
///
/// The Get-functions (i.e. GetPpmCrate(), etc.) return pointers
/// to vectors. This is so more than
/// one channel can be returned. For instance, if a JEM channel
/// is specified, there are 4 associated PPM channels.
///
/// The EM_OR_HAD variables are an enum I made for defining the 
/// CAL layer as EM(=1) or HAD(=2) or LAYER_NOT_SET(=0).
///
/// There are also three Enable functions, SetPpmEnable(true/false),
/// etc. All subsystems are enabled by default, but in the case
/// that only one subsystem is needed, the other two can be disabled
/// to increase efficiency.
///
////////////////////////////////////////////////////////////////////

#ifndef L1CALOCHANNELMAP_H
#define L1CALOCHANNELMAP_H

#include <iostream>
#include <vector>

#include "PpmChannelMap.h"
#include "JemChannelMap.h"
#include "CpmChannelMap.h"
#include "TcppChannelMap.h"

#include "L1CaloChannelId.h"
#include "TileDrawerId.h"
#include "FcalLayer.h"
#include "CaloLayer.h"
#include "CaloDivision.h"
#include "CPMRoI.h"


class L1CaloChannelMap : private PpmChannelMap, 
                         private JemChannelMap, 
                         private CpmChannelMap,
                         private TcppChannelMap
{
public:
   
	L1CaloChannelMap();
	~L1CaloChannelMap();
	
   /// Setter Functions
	void SetEtaPhi(float,float,CaloLayer);
	
	void SetPpmChannel(unsigned int,unsigned int,unsigned int,unsigned int);
	void SetCpmChannelWithSerializer(unsigned int,unsigned int,unsigned int,unsigned int);
   void SetCpmChannelWithCpChip(unsigned int,unsigned int,unsigned int,unsigned int);
	void SetJemChannel(unsigned int,unsigned int,unsigned int);
	
   void SetCpmRoI(CPMRoI&,CaloLayer&);
   void SetCpmRoI(unsigned int crate,unsigned int module,unsigned int submodule,unsigned int location,CaloLayer&);
   void SetCpmRoI(unsigned int,CaloLayer&);
   
	void SetPpmChannelID(L1CaloChannelId);
   void SetPpmChannelID(unsigned int);
	
	void SetCpmEnable(bool inEnabled){m_cpmEnabled = inEnabled;};
	void SetPpmEnable(bool inEnabled){m_ppmEnabled = inEnabled;};
   void SetJemEnable(bool inEnabled){m_jemEnabled = inEnabled;};
   void SetTcppEnable(bool inEnabled){m_tcppEnabled = inEnabled;};
   
   /// Getter Functions
   // For CPM
	std::vector<unsigned int>* GetCpmCrate(void){return CpmChannelMap::GetCrate();};
	std::vector<unsigned int>* GetCpmModule(void){return CpmChannelMap::GetModule();};
	std::vector<unsigned int>* GetCpmSerializerSubmodule(void){return CpmChannelMap::GetSerializerSubmodule();};
   std::vector<unsigned int>* GetCpmSerializerChannel(void){return CpmChannelMap::GetSerializerChannel();};
	std::vector<unsigned int>* GetCpmCpChipSubmodule(void){return CpmChannelMap::GetCpChipSubmodule();};
   std::vector<unsigned int>* GetCpmCpChipChannel(void){return CpmChannelMap::GetCpChipChannel();};
	float GetCpmDeltaEta(void){return CpmChannelMap::GetDeltaEta();};
	float GetCpmDeltaPhi(void){return CpmChannelMap::GetDeltaPhi();};
   bool IsCpmChannelUsed(void){return CpmChannelMap::IsChannelUsed();};
   
   // For PPM
	std::vector<unsigned int>* GetPpmCrate(void){return PpmChannelMap::GetCrate();};
	std::vector<unsigned int>* GetPpmModule(void){return PpmChannelMap::GetModule();};
	std::vector<unsigned int>* GetPpmSubmodule(void){return PpmChannelMap::GetSubmodule();};
	std::vector<unsigned int>* GetPpmChannel(void){return PpmChannelMap::GetChannel();};
	std::vector<FcalLayer>* GetPpmFcalLayer(void){return PpmChannelMap::GetFcalLayer();};
	float GetPpmDeltaEta(void){return PpmChannelMap::GetDeltaEta();};
	float GetPpmDeltaPhi(void){return PpmChannelMap::GetDeltaPhi();};
	std::vector<L1CaloChannelId>* GetPpmChannelID(void){return PpmChannelMap::GetChannelID();};
   bool IsPpmChannelUsed(void){return PpmChannelMap::IsChannelUsed();};
	
	float GetPpmFcal23eta(void){return PpmChannelMap::GetModifiedEta();};
   unsigned int GetPpmFcal23integerEta(void){return PpmChannelMap::GetModifiedIntegerEta();};
   std::vector<bool>* IsFcal23region(void){return PpmChannelMap::IsModifiedEtaAvailable();};
	
	void SetPpmFcal23etaPhi(float inEta,float inPhi,CaloLayer inLayer);
	
   // For JEM
	std::vector<unsigned int>* GetJemCrate(void){return JemChannelMap::GetCrate();};
	std::vector<unsigned int>* GetJemModule(void){return JemChannelMap::GetModule();};
	std::vector<unsigned int>* GetJemChannel(void){return JemChannelMap::GetChannel();};
	float GetJemDeltaEta(void){return JemChannelMap::GetDeltaEta();};
	float GetJemDeltaPhi(void){return JemChannelMap::GetDeltaPhi();};
	
   // For Tile Crate Patch Panels (TCPP)
   std::vector<unsigned int>* GetTcppCrate(void){return TcppChannelMap::GetCrate();};
   std::vector<unsigned int>* GetTcppModule(void){return TcppChannelMap::GetModule();};
   std::vector<unsigned int>* GetTcppOutputSubmodule(void){return TcppChannelMap::GetOutputSubmodule();};
   std::vector<unsigned int>* GetTcppOutputChannel(void){return TcppChannelMap::GetOutputChannel();};
   std::vector<unsigned int>* GetTcppInputSubmodule(void){return TcppChannelMap::GetInputSubmodule();};
   std::vector<unsigned int>* GetTcppInputChannel(void){return TcppChannelMap::GetInputChannel();};
   std::vector<L1CaloChannelId>* GetTcppOutputChannelId(void){return TcppChannelMap::GetOutputChannelId();};
   std::vector<L1CaloChannelId>* GetTcppInputChannelId(void){return TcppChannelMap::GetInputChannelId();};
   std::vector<TileDrawerId>* GetTcppTileDrawer(void){return TcppChannelMap::GetTileDrawer();};
   
   // For Eta/Phi
	float GetEta(void){return m_eta;};
	float GetDeltaEta(void){return m_deltaEta;};
	float GetPhi(void){return m_phi;};
	float GetDeltaPhi(void){return m_deltaPhi;};
	CaloLayer GetLayer(void){return m_layer;};
   
   float GetBaseEta(void){return m_baseEta;};
   float GetBasePhi(void){return m_basePhi;};
   
   unsigned int   GetIntegerEta(void){return m_integerEta;};
   unsigned int   GetIntegerPhi(void){return m_integerPhi;};
	
   // For Detector region
	CaloDivision GetDetectorRegion(void){return m_region;};
   std::string GetDetectorRegionString(void){return m_region.GetString();};
private:

   static const unsigned int MAX_UINT_ETA  = 98;
   static const unsigned int MIN_UINT_ETA  = 0;
   
   static const unsigned int MAX_UINT_PHI  = 64;
   static const unsigned int MIN_UINT_PHI  = 0;
   
   static const float        MAX_ETA;
   static const float        MIN_ETA;
   
   static const float        MAX_PHI;
   static const float        MIN_PHI;
   
   static const float        myPI;

	bool m_cpmEnabled;
	bool m_ppmEnabled;
	bool m_jemEnabled;
   bool m_tcppEnabled;
	
	float m_eta;
	float m_deltaEta;
	float m_phi;
	float m_deltaPhi;
	CaloLayer m_layer;
   
   float m_baseEta;
   float m_basePhi;
   unsigned int   m_integerEta;
   unsigned int   m_integerPhi;
	
	CaloDivision m_region;
	
	CaloDivision GetDetectorRegion(float,CaloLayer);
	
   bool FloatIsEqualTo(const float x, const float y);
};

#endif

