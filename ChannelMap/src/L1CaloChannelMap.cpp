#include "L1CaloChannelMap.h"

#include "EtaPhiId.h"

const float        L1CaloChannelMap::myPI          = 3.14159265;
const float        L1CaloChannelMap::MAX_ETA       = 4.9;
const float        L1CaloChannelMap::MIN_ETA       = -4.9;
const float        L1CaloChannelMap::MAX_PHI       = 2.0*myPI;
const float        L1CaloChannelMap::MIN_PHI       = 0.0;


L1CaloChannelMap::L1CaloChannelMap(void){
   
	m_cpmEnabled  = true;
	m_ppmEnabled  = true;
	m_jemEnabled  = true;
   m_tcppEnabled = true;
	
	m_eta      = -999;
	m_deltaEta = -999;
	m_phi      = -999;
	m_deltaPhi = -999;
	m_layer.Clear();
	m_region.Clear();
   
   m_baseEta    = -999;
   m_basePhi    = -999;
   m_integerEta = -999;
   m_integerPhi = -999;
	
}

L1CaloChannelMap::~L1CaloChannelMap(void){
	
	
}

// Specify the Eta and Phi and EM or HAD, then all the corresponding channels
// from the various subsystems are set.
void L1CaloChannelMap::SetEtaPhi(float inEta, float inPhi, CaloLayer inLayer){
   
   if( !(MIN_ETA < inEta && inEta < MAX_ETA) && !FloatIsEqualTo(inEta,MIN_ETA)){
	   std::cerr << "L1CaloChannelMap::SetEtaPhi: Eta value, " << inEta << ", is out of range: " << MIN_ETA << " to " << MAX_ETA << "\n";
	   return;
   }
   if( !(MIN_PHI < inPhi && inPhi < MAX_PHI) && !FloatIsEqualTo(inPhi,MIN_PHI)){
	   std::cerr << "L1CaloChannelMap::SetEtaPhi: Phi value, " << inPhi << ", is out of range: " << MIN_PHI << " to " << MAX_PHI << "\n";
	   return;
   }
   if( !inLayer.IsSet()){
	   std::cerr << "L1CaloChannelMap::SetEtaPhi: CaloLayer value, " << inLayer.GetLayerAsString() << ", must be EM or HAD\n";
	   return;
   }
   
   EtaPhiId m_etaPhiId(inEta,inPhi,inLayer);
   
   m_eta = m_etaPhiId.GetEta();
   m_phi = m_etaPhiId.GetPhi();
   
   m_integerEta = m_etaPhiId.GetIntegerEta();
   m_integerPhi = m_etaPhiId.GetIntegerPhi();
   
   m_etaPhiId.SetEtaPhi(m_integerEta,m_integerPhi,inLayer);
   
   m_baseEta = m_etaPhiId.GetEta();
   m_basePhi = m_etaPhiId.GetPhi();
   
   m_layer = inLayer;
   m_region = GetDetectorRegion(m_eta,inLayer);
   
   if(m_ppmEnabled){
	   PpmChannelMap::SetEtaPhi(m_eta,m_phi,m_layer);
   }
   else{
	   PpmChannelMap::ClearPpm();
   }
   
   if(m_cpmEnabled){
	   CpmChannelMap::SetEtaPhi(m_eta,m_phi,m_layer);
	   
   }
   else{
	   CpmChannelMap::ClearCpm();
   }
   
   if(m_jemEnabled){
	   JemChannelMap::SetEtaPhi(m_eta,m_phi,m_layer);
   }
   else{
	   JemChannelMap::ClearJem();
   }
   
   if(m_tcppEnabled && m_region.IsTile()){
      TcppChannelMap::SetEtaPhi(m_eta,m_phi,m_layer);
   }
   else{
      TcppChannelMap::ClearTcpp();
   }
   
   m_deltaEta = -999;
   m_deltaPhi = -999;

}

///////////////////////////////////////////////
/// This can be used when using modified
/// m_eta coordinates in the hadronic FCAL2/3
/// m_regions, See PpmChannelMap::SetModifiedEtaPhi()
/// for more dm_etails. Only the PPM Set Eta Phi
/// is different here, otherwise same as SetEtaPhi()
///////////////////////////////////////////////
void L1CaloChannelMap::SetPpmFcal23etaPhi(float inEta,float inPhi,CaloLayer inLayer){
	
   if( !(MIN_ETA < inEta && inEta < MAX_ETA) && !FloatIsEqualTo(inEta,MIN_ETA)){
      std::cerr << "L1CaloChannelMap::SetPpmFcal23m_etaPhi: Eta value, " << inEta << ", is out of range: " << MIN_ETA << " to " << MAX_ETA << "\n";
      return;
   }
   if( !(MIN_PHI < inPhi && inPhi < MAX_PHI) && !FloatIsEqualTo(inPhi,MIN_PHI)){
      std::cerr << "L1CaloChannelMap::SetPpmFcal23m_etaPhi: Phi value, " << inPhi << ", is out of range: " << MIN_PHI << " to " << MAX_PHI << "\n";
      return;
   }
   if( !inLayer.IsSet()){
      std::cerr << "L1CaloChannelMap::SetPpmFcal23m_etaPhi: CaloLayer value, " << inLayer.GetLayerAsString() << ", must be EM or HAD\n";
      return;
   }
	
   EtaPhiId m_etaPhiId(inEta,inPhi,inLayer);
   
   m_eta = m_etaPhiId.GetEta();
   m_phi = m_etaPhiId.GetPhi();
   
   m_integerEta = m_etaPhiId.GetIntegerEta();
   m_integerPhi = m_etaPhiId.GetIntegerPhi();
   
   m_etaPhiId.SetEtaPhi(m_integerEta,m_integerPhi,inLayer);
   
   m_baseEta = m_etaPhiId.GetEta();
   m_basePhi = m_etaPhiId.GetPhi();
   
   m_layer = inLayer;
   m_region = GetDetectorRegion(m_eta,inLayer);
   
	if(m_ppmEnabled){
		PpmChannelMap::SetModifiedEtaPhi(m_eta,m_phi,m_layer);
	}
	else{
		PpmChannelMap::ClearPpm();
	}
	
	if(m_cpmEnabled){
		CpmChannelMap::SetEtaPhi(m_eta,m_phi,m_layer);
		
	}
	else{
		CpmChannelMap::ClearCpm();
	}
	
	if(m_jemEnabled){
		JemChannelMap::SetEtaPhi(m_eta,m_phi,m_layer);
	}
	else{
		JemChannelMap::ClearJem();
	}
	
   if(m_tcppEnabled && m_region.IsTile()){
      TcppChannelMap::SetEtaPhi(m_eta,m_phi,m_layer);
   }
   else{
      TcppChannelMap::ClearTcpp();
   }
   
	
	m_deltaEta = -999;
	m_deltaPhi = -999;
}

void L1CaloChannelMap::SetPpmChannelID(unsigned int id){
   L1CaloChannelId newId(id);
   SetPpmChannelID(newId);
}

void L1CaloChannelMap::SetPpmChannelID(L1CaloChannelId id){
	
	if(!m_ppmEnabled){
		std::cerr << "L1CaloChannelMap::SetPpmChannelID: PPM Disabled!\n";
		return;
	}
	
	PpmChannelMap::SetChannelID(id);
   
   if(!PpmChannelMap::IsChannelUsed()){
//       std::cerr << "L1CaloChannelMap::SetPpmChannel: This PPM Channel is valid, but not used in the system.\n";
      return;
   }
   
	m_eta = PpmChannelMap::GetEta();
   m_phi = PpmChannelMap::GetPhi();
   m_layer = PpmChannelMap::GetLayer();
   
   EtaPhiId m_etaPhiId(m_eta,m_phi,m_layer);
   
   m_integerEta = m_etaPhiId.GetIntegerEta();
   m_integerPhi = m_etaPhiId.GetIntegerPhi();
   
   m_etaPhiId.SetEtaPhi(m_integerEta,m_integerPhi,m_layer);
   
   m_baseEta = m_etaPhiId.GetEta();
	m_basePhi = m_etaPhiId.GetPhi();
   
   m_deltaEta = PpmChannelMap::GetDeltaEta();
	m_deltaPhi = PpmChannelMap::GetDeltaPhi();
	
   m_region = GetDetectorRegion(m_eta,m_layer);
   
	if(m_cpmEnabled){
		CpmChannelMap::SetEtaPhi(m_eta,m_phi,m_layer);
	}
	else{
		CpmChannelMap::ClearCpm();
	}
	
	if(m_jemEnabled){
		JemChannelMap::SetEtaPhi(m_eta,m_phi,m_layer);
	}
	else{
		JemChannelMap::ClearJem();
	}
	
   if(m_tcppEnabled && m_region.IsTile()){
      TcppChannelMap::SetEtaPhi(m_eta,m_phi,m_layer);
   }
   else{
      TcppChannelMap::ClearTcpp();
   }
   
}


void L1CaloChannelMap::SetPpmChannel(unsigned int crate,unsigned int module,unsigned int submodule,unsigned int channel){

	if(!m_ppmEnabled){
		std::cerr << "L1CaloChannelMap::SetPpmChannel: PPM Disabled!\n";
		return;
	}
	
	PpmChannelMap::SetChannel(crate,module,submodule,channel);
	
   if(!PpmChannelMap::IsChannelUsed()){
//       std::cerr << "L1CaloChannelMap::SetPpmChannel: This PPM Channel is valid, but not used in the system.\n";
      return;
   }
   
   m_eta = PpmChannelMap::GetEta();
   m_phi = PpmChannelMap::GetPhi();
   m_layer = PpmChannelMap::GetLayer();
   
   EtaPhiId m_etaPhiId(m_eta,m_phi,m_layer);
   
   m_integerEta = m_etaPhiId.GetIntegerEta();
   m_integerPhi = m_etaPhiId.GetIntegerPhi();
   
   m_etaPhiId.SetEtaPhi(m_integerEta,m_integerPhi,m_layer);
   
   m_baseEta = m_etaPhiId.GetEta();
   m_basePhi = m_etaPhiId.GetPhi();
   
   m_deltaEta = PpmChannelMap::GetDeltaEta();
   m_deltaPhi = PpmChannelMap::GetDeltaPhi();
   
   m_region = GetDetectorRegion(m_eta,m_layer);
   
	if(m_cpmEnabled){
		CpmChannelMap::SetEtaPhi(m_eta,m_phi,m_layer);
	}
	else{
		CpmChannelMap::ClearCpm();
	}
	
	if(m_jemEnabled){
		JemChannelMap::SetEtaPhi(m_eta,m_phi,m_layer);
	}
	else{
		JemChannelMap::ClearJem();
	}
	
   if(m_tcppEnabled && m_region.IsTile()){
      TcppChannelMap::SetEtaPhi(m_eta,m_phi,m_layer);
   }
   else{
      TcppChannelMap::ClearTcpp();
   }
   
}


void L1CaloChannelMap::SetCpmChannelWithSerializer(unsigned int crate,unsigned int module,unsigned int submodule,unsigned int channel){
	
	if(!m_cpmEnabled){
		std::cerr << "L1CaloChannelMap::SetCpmChannel: CPM Disabled!\n";
		return;
	}
	
	CpmChannelMap::SetChannelSerializer(crate,module,submodule,channel);
	
   if(!CpmChannelMap::IsChannelUsed()){
      std::cerr << "L1CaloChannelMap::SetCpmChannel: This CPM Channel is valid, but not used in the system.\n";
      return;
   }
   
   m_eta = CpmChannelMap::GetEta();
   m_phi = CpmChannelMap::GetPhi();
   
   m_layer = CpmChannelMap::GetLayer();
   
   EtaPhiId m_etaPhiId(m_eta,m_phi,m_layer);
   
   m_integerEta = m_etaPhiId.GetIntegerEta();
   m_integerPhi = m_etaPhiId.GetIntegerPhi();
   
   m_etaPhiId.SetEtaPhi(m_integerEta,m_integerPhi,m_layer);
   
   m_baseEta = m_etaPhiId.GetEta();
   m_basePhi = m_etaPhiId.GetPhi();
   
   m_deltaEta = CpmChannelMap::GetDeltaEta();
   m_deltaPhi = CpmChannelMap::GetDeltaPhi();
   
   m_region = GetDetectorRegion(m_eta,m_layer);
   
	if(m_jemEnabled){
		JemChannelMap::SetEtaPhi(m_eta,m_phi,m_layer);
	}
	else{
		JemChannelMap::ClearJem();
	}
	
	if(m_ppmEnabled){
		PpmChannelMap::SetEtaPhi(m_eta,m_phi,m_layer);
	}
	else{
		PpmChannelMap::ClearPpm();
	}
	
   if(m_tcppEnabled && m_region.IsTile()){
      TcppChannelMap::SetEtaPhi(m_eta,m_phi,m_layer);
   }
   else{
      TcppChannelMap::ClearTcpp();
   }
   
}

void L1CaloChannelMap::SetCpmChannelWithCpChip(unsigned int crate,unsigned int module,unsigned int submodule,unsigned int channel){
	
	if(!m_cpmEnabled){
		std::cerr << "L1CaloChannelMap::SetCpmChannel: CPM Disabled!\n";
		return;
	}
	
	CpmChannelMap::SetChannelCpChip(crate,module,submodule,channel);
	
   if(!CpmChannelMap::IsChannelUsed()){
      std::cerr << "L1CaloChannelMap::SetCpmChannel: This CPM Channel is valid, but not used in the system.\n";
      return;
   }
   
   m_eta = CpmChannelMap::GetEta();
   m_phi = CpmChannelMap::GetPhi();
   
   m_layer = CpmChannelMap::GetLayer();
   
   EtaPhiId m_etaPhiId(m_eta,m_phi,m_layer);
   
   m_integerEta = m_etaPhiId.GetIntegerEta();
   m_integerPhi = m_etaPhiId.GetIntegerPhi();
   
   m_etaPhiId.SetEtaPhi(m_integerEta,m_integerPhi,m_layer);
   
   m_baseEta = m_etaPhiId.GetEta();
   m_basePhi = m_etaPhiId.GetPhi();
   
   m_deltaEta = CpmChannelMap::GetDeltaEta();
   m_deltaPhi = CpmChannelMap::GetDeltaPhi();
   
   m_region = GetDetectorRegion(m_eta,m_layer);
   
	if(m_jemEnabled){
		JemChannelMap::SetEtaPhi(m_eta,m_phi,m_layer);
	}
	else{
		JemChannelMap::ClearJem();
	}
	
	if(m_ppmEnabled){
		PpmChannelMap::SetEtaPhi(m_eta,m_phi,m_layer);
	}
	else{
		PpmChannelMap::ClearPpm();
	}
	
   if(m_tcppEnabled && m_region.IsTile()){
      TcppChannelMap::SetEtaPhi(m_eta,m_phi,m_layer);
   }
   else{
      TcppChannelMap::ClearTcpp();
   }
   
}

void L1CaloChannelMap::SetCpmRoI(CPMRoI& roi,CaloLayer& layer){
   
   if(!m_cpmEnabled){
      std::cerr << "L1CaloChannelMap::SetCpmRoI: CPM Disabled!\n";
      return;
   }
   
   CpmChannelMap::SetCPMRoI(roi,layer);
   
   if(!CpmChannelMap::IsChannelUsed()){
      std::cerr << "L1CaloChannelMap::SetCpmChannel: This CPM Channel is valid, but not used in the system.\n";
      return;
   }
   
   m_eta = CpmChannelMap::GetEta();
   m_phi = CpmChannelMap::GetPhi();
   
   m_layer = CpmChannelMap::GetLayer();
   
   EtaPhiId m_etaPhiId(m_eta,m_phi,m_layer);
   
   m_integerEta = m_etaPhiId.GetIntegerEta();
   m_integerPhi = m_etaPhiId.GetIntegerPhi();
   
   m_etaPhiId.SetEtaPhi(m_integerEta,m_integerPhi,m_layer);
   
   m_baseEta = m_etaPhiId.GetEta();
   m_basePhi = m_etaPhiId.GetPhi();
   
   m_deltaEta = CpmChannelMap::GetDeltaEta();
   m_deltaPhi = CpmChannelMap::GetDeltaPhi();
   
   m_region = GetDetectorRegion(m_eta,m_layer);
   
   if(m_jemEnabled){
      JemChannelMap::SetEtaPhi(m_eta,m_phi,m_layer);
   }
   else{
      JemChannelMap::ClearJem();
   }
   
   if(m_ppmEnabled){
      PpmChannelMap::SetEtaPhi(m_eta,m_phi,m_layer);
   }
   else{
      PpmChannelMap::ClearPpm();
   }
   
   if(m_tcppEnabled && m_region.IsTile()){
      TcppChannelMap::SetEtaPhi(m_eta,m_phi,m_layer);
   }
   else{
      TcppChannelMap::ClearTcpp();
   }
   
   
}

void L1CaloChannelMap::SetCpmRoI(unsigned int crate,unsigned int module,unsigned int submodule,unsigned int location,CaloLayer& layer){
   CPMRoI temp(crate,module,submodule,location,0,0);
   L1CaloChannelMap::SetCPMRoI(temp,layer);
}

void L1CaloChannelMap::SetCpmRoI(unsigned int roiword,CaloLayer& layer){
   CPMRoI temp(roiword);
   L1CaloChannelMap::SetCPMRoI(temp,layer);
}

void L1CaloChannelMap::SetJemChannel(unsigned int crate,unsigned int module,unsigned int channel){
	
	if(!m_jemEnabled){
		std::cerr << "L1CaloChannelMap::SetJemChannel: JEM Disabled!\n";
		return;
	}
	
	JemChannelMap::SetChannel(crate,module,channel);
	
   m_eta = JemChannelMap::GetEta();
   m_phi = JemChannelMap::GetPhi();
   m_layer = JemChannelMap::GetLayer();
   
   EtaPhiId m_etaPhiId(m_eta,m_phi,m_layer);
   
   m_integerEta = m_etaPhiId.GetIntegerEta();
   m_integerPhi = m_etaPhiId.GetIntegerPhi();
   
   m_etaPhiId.SetEtaPhi(m_integerEta,m_integerPhi,m_layer);
   
   m_baseEta = m_etaPhiId.GetEta();
   m_basePhi = m_etaPhiId.GetPhi();
   
   m_deltaEta = JemChannelMap::GetDeltaEta();
   m_deltaPhi = JemChannelMap::GetDeltaPhi();
   
   m_region = GetDetectorRegion(m_eta,m_layer);
   
	//std::cerr << "L1CALO: " << m_eta << "+/-" << m_deltaEta << "; " << m_phi << "+/-" << m_deltaPhi << std::endl;
	
	if(m_ppmEnabled){
		PpmChannelMap::SetEtaPhi(m_eta,m_deltaEta,m_phi,m_deltaPhi,m_layer);
	}
	else{
		PpmChannelMap::ClearPpm();
	}
	
	if(m_cpmEnabled){
		CpmChannelMap::SetEtaPhi(m_eta,m_deltaEta,m_phi,m_deltaPhi,m_layer);
	}
	else{
		CpmChannelMap::ClearCpm();
	}
	
   if(m_tcppEnabled && m_region.IsTile()){
      TcppChannelMap::SetEtaPhi(m_eta,m_phi,m_layer);
   }
   else{
      TcppChannelMap::ClearTcpp();
   }
   
}


CaloDivision L1CaloChannelMap::GetDetectorRegion(float inEta,CaloLayer inLayer){
	
   EtaPhiId m_etaPhiId(inEta,0.0,inLayer);
   
	unsigned int tempEta = m_etaPhiId.GetIntegerEta();
	
	CaloDivision temp;
	if (inLayer.IsEM()) {
		if      (tempEta < -32 + 49) { temp.SetLArFCAL1C(); }
		else if (tempEta < -15 + 49) { temp.SetLArEMECC(); }
		else if (tempEta < -14 + 49) { temp.SetLArOverlapC(); }
		else if (tempEta <   0 + 49) { temp.SetLArEMBC(); }
		else if (tempEta <  14 + 49) { temp.SetLArEMBA(); }
		else if (tempEta <  15 + 49) { temp.SetLArOverlapA(); }
		else if (tempEta <  32 + 49) { temp.SetLArEMECA(); }
		else                         { temp.SetLArFCAL1A(); }
	}
	else if(inLayer.IsHAD()){
		if      (tempEta < -32 + 49) { temp.SetLArFCAL23C(); }
		else if (tempEta < -15 + 49) { temp.SetLArHECC(); }
		else if (tempEta <  -9 + 49) { temp.SetTileEBC(); }
		else if (tempEta <   0 + 49) { temp.SetTileLBC(); }
		else if (tempEta <   9 + 49) { temp.SetTileLBA(); }
      else if (tempEta <  15 + 49) { temp.SetTileEBA(); }
		else if (tempEta <  32 + 49) { temp.SetLArHECA(); }
		else                         { temp.SetLArFCAL23A(); }
	}
	
	return temp;
}


// Compares a float to a float and returns true if
// they are approximately equal
bool L1CaloChannelMap::FloatIsEqualTo(const float x, const float y){
   if(fabs(x-y) < 0.005){
      return true;
   }
   return false;
}

