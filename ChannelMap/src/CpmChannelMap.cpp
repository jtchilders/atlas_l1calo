#include "CpmChannelMap.h"

const float        CpmChannelMap::myPI = 3.14159265;
const float        CpmChannelMap::MAX_ETA       = 4.9;
const float        CpmChannelMap::MIN_ETA       = -4.9;
const float        CpmChannelMap::MAX_CPM_ETA   = 2.5;
const float        CpmChannelMap::MIN_CPM_ETA   = -2.5;
const float        CpmChannelMap::MAX_PHI       = 2.0*myPI;
const float        CpmChannelMap::MIN_PHI       = 0.0;

CpmChannelMap::CpmChannelMap(void){
	
   // create eta phi id
   m_currentEtaPhiId = new EtaPhiId;
   // create vector of channel ids
   m_currentChannelId = new std::vector<L1CaloChannelId>;
   
	//Initialize variables
	ClearCpm();
	
	FillEtaPhi();
}

CpmChannelMap::~CpmChannelMap(void){
   delete m_currentEtaPhiId;
   m_currentEtaPhiId = 0;
   
   delete m_currentChannelId;
   m_currentChannelId = 0;
}

void CpmChannelMap::ClearCpm(void){
	
   m_currentEtaPhiId->Clear();
   m_currentDeltaEta = 0;
   m_currentDeltaPhi = 0;
   m_currentChannelId->clear();
   
   m_currentCrate.clear();
   m_currentModule.clear();
   m_currentSubmoduleSerializer.clear();
   m_currentChannelSerializer.clear();
   m_currentSubmoduleChip.clear();
   m_currentChannelChip.clear();
   
   m_currentChannelUsed = true;
}

// Here I fill the maps of cpm id to eta and phi and layer
// I use the Serializers for my base id for the std::map's
void CpmChannelMap::FillEtaPhi(void){
   
   for(unsigned int crate=MIN_CRATE;crate<=MAX_CRATE;crate++){
      for(unsigned int module=MIN_MODULE;module<=MAX_MODULE;module++){
         for(unsigned int submodule=MIN_SUBMODULE_SERIAL;submodule<=MAX_SUBMODULE_SERIAL;submodule++){
            for(unsigned int channel=MIN_CHANNEL_SERIAL;channel<=MAX_CHANNEL_SERIAL;channel++){
            
            L1CaloChannelId chanId(L1CaloChannelId::CPM,crate,module,submodule,channel);
            
            CaloLayer layer;
            if( (submodule % 2) == 0 ) // even serializer = EM layer
               layer.SetCaloLayer(CaloLayer::EM);
            else // odd serializer = HAD layer
               layer.SetCaloLayer(CaloLayer::HAD);
            
            // eta contribution from the crate bottom left corner
            unsigned int crateEta = -25 + 49;
            // phi contribution from the crate bottom left corner
            unsigned int cratePhi = 16*(crate-MIN_CRATE);
            
            int eta=999,phi=999;
            // long skinny Eta coverage modules
            if(module == MIN_MODULE){
	            
               if(channel == 3 || channel == 7){
                  // eta contribution from the module bottom left corner
                  unsigned int moduleEta = 0;
                  // phi contribution from the module bottom left corner
                  unsigned int modulePhi = 0;
                  
                  // eta contribution from the submodule bottom left corner
                  unsigned int submoduleEta = 0;
                  // phi contribution from the submodule bottom left corner
                  int submodulePhi = (submodule/2)*2 - 2;
                  
                  // eta contributions from the channel bottom left corner
                  unsigned int channelEta = 0;
                  // phi contributions from the channel bottom left corner
                  unsigned int channelPhi = 0;
                  if(channel == 7) channelPhi = 1;
                  
                  eta = crateEta + moduleEta + submoduleEta + channelEta;
                  phi = cratePhi + modulePhi + submodulePhi + channelPhi;
                  
               }
            }
            else if(module == MAX_MODULE){
            
               if(channel == 0 || channel == 4){
                  // eta contribution from the module bottom left corner
                  unsigned int moduleEta = (24 + 49) - (-25 + 49);
                  // phi contribution from the module bottom left corner
                  unsigned int modulePhi = 0;
                  
                  // eta contribution from the submodule bottom left corner
                  unsigned int submoduleEta = 0;
                  // phi contribution from the submodule bottom left corner
                  int submodulePhi = (submodule/2)*2 - 2;
                  
                  // eta contributions from the channel bottom left corner
                  unsigned int channelEta = 0;
                  // phi contributions from the channel bottom left corner
                  unsigned int channelPhi = 0;
                  if(channel == 4) channelPhi = 1;
                  
                  eta = crateEta + moduleEta + submoduleEta + channelEta;
                  phi = cratePhi + modulePhi + submodulePhi + channelPhi;
               }
            }
            else{
	            // eta contribution from the module bottom left corner
	            unsigned int moduleEta = 1 + (module-MIN_MODULE-1)*4;
	            // phi contribution from the module bottom left corner
               unsigned int modulePhi = 0;
	            
               // eta contribution from the submodule bottom left corner
	            unsigned int submoduleEta = 0;
               // phi contribution from the submodule bottom left corner
               int submodulePhi = (submodule/2)*2 - 2;
               
               // eta contribution from the channel bottom left corner
               unsigned int channelEta = channel % 4;
               // phi contribution from the channel bottom left corner
               unsigned int channelPhi = channel/4;
               
                  eta = crateEta + moduleEta + submoduleEta + channelEta;
                  phi = cratePhi + modulePhi + submodulePhi + channelPhi;
                  
            }
            
            if(phi == -1) phi = 63;
            else if(phi == -2) phi = 62;
            else if(phi == 64) phi = 0;
            else if(phi == 65) phi = 1;
            
            EtaPhiId epId;
            if(eta != 999 && phi != 999){
               epId.SetEtaPhi((unsigned int)eta,(unsigned int)phi,layer);
            
//             std::cerr << "0x" << epId.GetIdAsString() <<  " " << epId.GetEta() << " " << epId.GetPhi() <<  " " << eta << " " << phi << std::endl;
            
               m_map_etaPhiId_channelId[epId.GetId()].push_back(chanId.GetId());
               m_map_channelId_etaPhiId[chanId.GetId()] = epId.GetId();
               m_map_channelId_usedChannel[chanId.GetId()] = true;
            }
            else{
               m_map_channelId_usedChannel[chanId.GetId()] = false;
            }
            
            }// end(chan)
         }// end(layer)
      }// end(cpm)
   }// end(crate)
}

void CpmChannelMap::GetCpmChannels(unsigned int inEta,unsigned int inDeltaEta,unsigned int inPhi,unsigned int inDeltaPhi,CaloLayer inLayer,std::vector<L1CaloChannelId>* outChanList){
	
	if( !(MIN_UINT_ETA <= inEta && (inEta + inDeltaEta) <= MAX_UINT_ETA)){
		std::cerr << "CpmChannelMap::GetCpmChannel: Eta value, " << inEta << ", or (Eta + delta Eta) value, " << (inEta+inDeltaEta) << ", is out of range: " << MIN_UINT_ETA << " to " << MAX_UINT_ETA << "\n";
		return;
	}
	else if( !(-25 + 49 <= inEta && inEta < 25 + 49) ){
		//std::cerr << "CpmChannelMap::GetChannel: Eta value, " << itofEta(inEta) << ", inside L1Calo, but outside CPM allowable range: -2.5 to 2.5\n";
		return;
	}
	if( !(MIN_UINT_PHI <= inPhi && (inPhi + inDeltaPhi) <= MAX_UINT_PHI)){
		std::cerr << "CpmChannelMap::GetCpmChannel: Phi value, " << inPhi << ", or (Phi + delta Phi) value, " <<  (inPhi+inDeltaPhi) << ", is out of range: " << MIN_UINT_PHI << " to " << MAX_UINT_PHI << "\n";
		return;
	}
	if( !inLayer.IsSet() ){
		std::cerr << "CpmChannelMap::GetCpmChannel: EM_OR_HAD Value, " << inLayer.GetLayerAsString() << ", must be EM or HAD\n";
		return;
	}
	
	unsigned int etaMin = inEta;
	unsigned int etaMax = inEta + inDeltaEta;
	unsigned int phiMin = inPhi;
	unsigned int phiMax = inPhi + inDeltaPhi;
	
	
	bool repeat;
	std::map<unsigned int,std::vector<L1CaloChannelId> >::iterator etaToChanItr;
	
	for(unsigned int x=etaMin;x<etaMax;x++){
		
		if(x >= 25+49) break;
		
		for(unsigned int y=phiMin;y<phiMax;y++){
			
         EtaPhiId etaPhiId(x,y,inLayer);
			
			etaToChanItr = m_map_etaPhiId_channelId.find(etaPhiId.GetId());
			
			if(etaToChanItr == m_map_etaPhiId_channelId.end()){
				
				std::cerr << "CpmChannelMap::GetCpmChannels: etaPhiID, 0x" << etaPhiId.GetIdAsString() << ", not found.\n";
				std::cerr << "CpmChannelMap::GetCpmChannels: Eta = " << etaPhiId.GetEta() << "; Phi = " <<  etaPhiId.GetPhi() << "; Layer = " << etaPhiId.GetLayer().GetLayerAsString() << std::endl;
				continue;
			}
			
         repeat = false;
			for(unsigned int i=0;i< outChanList->size();i++){
				for(unsigned int j=0;j<etaToChanItr->second.size();j++){
					if(outChanList->at(i).GetId() == etaToChanItr->second[j].GetId()){
						repeat = true;
						break;
					}
				}
				if(repeat) break;
			}
			if(repeat) continue;
			
			for(unsigned int i=0;i<etaToChanItr->second.size();i++){
				outChanList->push_back(etaToChanItr->second[i]);
			}
		}
	}
	
}

void CpmChannelMap::SetEtaPhi(float inEta,float inPhi,CaloLayer inLayer){
   
   if( !(MIN_ETA < inEta && inEta < MAX_ETA) && !FloatIsEqualTo(inEta,MIN_ETA)){
      std::cerr << "CpmChannelMap::SetEtaPhi: Eta value, " << inEta << ", is out of range: " << MIN_ETA << " to " << MAX_ETA << "\n";
      return;
   }
   // The CPM Covers a smaller eta range than the rest of the system
   // so if outside this range nothing is done and no error is thrown.
   if( !(MIN_CPM_ETA < inEta && inEta < MAX_CPM_ETA) && !FloatIsEqualTo(inEta,MIN_CPM_ETA)){
      ClearCpm();
      return;
   }
   if( !(MIN_PHI < inPhi && inPhi < MAX_PHI) && !FloatIsEqualTo(inPhi,MIN_PHI)){
      std::cerr << "CpmChannelMap::SetEtaPhi: Phi value, " << inPhi << ", is out of range: " << MIN_PHI << " to " << MAX_PHI << "\n";
      return;
   }
   if(!inLayer.IsSet()){
      std::cerr << "CpmChannelMap::SetEtaPhi: CaloLayer Value, " << inLayer.GetLayerAsString() << ", must be EM or HAD\n";
      return;
   }
   
   ClearCpm();
   
   EtaPhiId etaPhiId(inEta,inPhi,inLayer);
   
   std::map<unsigned int,unsigned int>::iterator chanToEtaItr;
   std::map<unsigned int,std::vector<L1CaloChannelId> >::iterator etaToChanItr;
   
   etaToChanItr = m_map_etaPhiId_channelId.find(etaPhiId.GetId());
   if(etaToChanItr == m_map_etaPhiId_channelId.end()){
      std::cerr << "CpmChannelMap::SetEtaPhi: ERROR Eta Phi ID, " << etaPhiId.GetIdAsString() << ", not found.\n";
      std::cerr << "CpmChannelMap::SetEtaPhi: corresponds to eta = " << etaPhiId.GetEta() << " / " << etaPhiId.GetIntegerEta() << " phi = " << etaPhiId.GetPhi() << " / " << etaPhiId.GetIntegerPhi() << "; layer = " << etaPhiId.GetLayer().GetLayerAsString() << std::endl;
      return;
   }
   
   *m_currentChannelId = etaToChanItr->second;
   
   FillCurrentChannelFromId(m_currentChannelId);
   
   chanToEtaItr = m_map_channelId_etaPhiId.find(m_currentChannelId->at(0).GetId());
   if(chanToEtaItr == m_map_channelId_etaPhiId.end()){
      std::cerr << "CpmChannelMap::SetEtaPhi: ERROR Cool ID, " << m_currentChannelId->at(0).GetIdAsString() << ", not found.\n";
      return;
   }
   
   m_currentEtaPhiId->SetId(chanToEtaItr->second);
   
   m_currentDeltaEta = 1;
   m_currentDeltaPhi = 1;
   
}

void CpmChannelMap::SetEtaPhi(float inEta,float inDeltaEta,float inPhi,float inDeltaPhi,CaloLayer inLayer){
   
   if( !(MIN_ETA < inEta && (inEta+inDeltaEta) < MAX_ETA) && !FloatIsEqualTo(inEta,MIN_ETA) && !FloatIsEqualTo(inEta+inDeltaEta,MAX_ETA)) {
      std::cerr << "CpmChannelMap::SetEtaPhi: Eta value, " << inEta << ", or (Eta+deltaEta) value, " << (inEta+inDeltaEta) << ", is out of range: " << MIN_ETA << " to " << MAX_ETA << "\n";
      return;
   }
   // The CPM Covers a smaller eta range than the rest of the system
   // so if outside this range nothing is done and no error is thrown.
   if( !(MIN_CPM_ETA < inEta && (inEta+inDeltaEta) < MAX_CPM_ETA) && !FloatIsEqualTo(inEta,MIN_CPM_ETA)  && !FloatIsEqualTo(inEta+inDeltaEta,MAX_CPM_ETA) ){
      ClearCpm();
      return;
   }
   if( !(MIN_PHI < inPhi && ((inPhi+inDeltaPhi) < MAX_PHI) ) && !FloatIsEqualTo(inPhi,MIN_PHI) && !FloatIsEqualTo(inPhi+inDeltaPhi,MAX_PHI)) {
      std::cerr << "CpmChannelMap::SetEtaPhi: Phi value, " << inPhi << ", or (Eta+deltaEta) value, " << (inPhi+inDeltaPhi) << ", is out of range: " << MIN_PHI << " to " << MAX_PHI << "\n";
      return;
   }
   if(!inLayer.IsSet()){
      std::cerr << "CpmChannelMap::SetEtaPhi: CaloLayer Value, " << inLayer.GetLayerAsString() << ", must be EM or HAD\n";
      return;
   }
   
   ClearCpm();
   
   m_currentEtaPhiId->SetEtaPhi(inEta,inPhi,inLayer);
   
   EtaPhiId deltaEtaPhiId(inDeltaEta,inDeltaPhi,inLayer);
   
   m_currentDeltaEta = deltaEtaPhiId.GetIntegerEta() - 49;
   m_currentDeltaPhi = deltaEtaPhiId.GetIntegerPhi();
   
   GetCpmChannels(m_currentEtaPhiId->GetIntegerEta(),m_currentDeltaEta,m_currentEtaPhiId->GetIntegerPhi(),m_currentDeltaPhi,inLayer,m_currentChannelId);
   if(m_currentChannelId->size() <= 0){
      //std::cerr << "CpmChannelMap::SetEtaPhi: Error in GetCpmChannel().\n";
      return;
   }
   
   FillCurrentChannelFromId(m_currentChannelId);
   
}

void CpmChannelMap::SetChannelCpChip(unsigned int crate,unsigned int module,unsigned int submodule,unsigned int channel){
   if( !(MIN_CRATE <= crate && crate <= MAX_CRATE) ){
      std::cerr << "CpmChannelMap::SetChannelCpChip: Crate number, " << crate << ", outside allowable range: " << MIN_CRATE << " - " << MAX_CRATE << std::endl;
      return;
   }
   if( !(MIN_MODULE <= module && module <= MAX_MODULE) ){
      std::cerr << "CpmChannelMap::SetChannelCpChip: CPM number, " << module << ", outside allowable range: " << MIN_MODULE <<  " - " << MAX_MODULE << std::endl;
      return;
   }
   if( !(MIN_SUBMODULE_CHIP <= submodule && submodule <= MAX_SUBMODULE_CHIP) ){
      std::cerr << "CpmChannelMap::SetChannelCpChip: Submodule number, " << submodule << ", outside allowable range: " << MIN_SUBMODULE_CHIP <<  " - " << MAX_SUBMODULE_CHIP << std::endl;
      return;
   }
   if( !(MIN_CHANNEL_CHIP <= channel && channel <= MAX_CHANNEL_CHIP) ){
      std::cerr << "CpmChannelMap::SetChannelCpChip: Channel number, " << channel << ", outside allowable range: " << MIN_CHANNEL_CHIP <<  " - " << MAX_CHANNEL_CHIP << std::endl;
      return;
   }
   
   unsigned int serialChip = GetSerializerChipFromCpChip(submodule,channel);
   unsigned int serialChannel = GetSerializerChipChannelFromCpChip(channel);
   
   SetChannelSerializer(crate,module,serialChip,serialChannel);
   
}

void CpmChannelMap::SetChannelSerializer(unsigned int crate,unsigned int module,unsigned int submodule,unsigned int channel){
   
   if( !(MIN_CRATE <= crate && crate <= MAX_CRATE) ){
      std::cerr << "CpmChannelMap::SetChannelSerializer: Crate number, " << crate << ", outside allowable range: " << MIN_CRATE << " - " << MAX_CRATE << std::endl;
      return;
   }
   if( !(MIN_MODULE <= module && module <= MAX_MODULE) ){
      std::cerr << "CpmChannelMap::SetChannelSerializer: CPM number, " << module << ", outside allowable range: " << MIN_MODULE <<  " - " << MAX_MODULE << std::endl;
      return;
   }
   if( !(MIN_SUBMODULE_SERIAL <= submodule && submodule <= MAX_SUBMODULE_SERIAL) ){
      std::cerr << "CpmChannelMap::SetChannelSerializer: Submodule number, " << submodule << ", outside allowable range: " << MIN_SUBMODULE_SERIAL <<  " - " << MAX_SUBMODULE_SERIAL << std::endl;
      return;
   }
   if( !(MIN_CHANNEL_SERIAL <= channel && channel <= MAX_CHANNEL_SERIAL) ){
      std::cerr << "CpmChannelMap::SetChannelSerializer: Channel number, " << channel << ", outside allowable range: " << MIN_CHANNEL_SERIAL <<  " - " << MAX_CHANNEL_SERIAL << std::endl;
      return;
   }
   
   ClearCpm();
   
   L1CaloChannelId chanId(L1CaloChannelId::CPM,crate,module,submodule,channel);
   
   
   std::map<unsigned int,unsigned int>::iterator chanToEtaItr;
   std::map<unsigned int,std::vector<L1CaloChannelId> >::iterator etaToChanItr;
   std::map<unsigned int,bool>::iterator chanToUsedItr;
   
   chanToUsedItr = m_map_channelId_usedChannel.find(chanId.GetId());
   if(chanToUsedItr == m_map_channelId_usedChannel.end()){
      std::cerr << "CpmChannelMap::SetChannelSerializer: ERROR Cool ID, " << chanId.GetIdAsString() << ", not found.\n";
      return;
   }
   else if(!chanToUsedItr->second){
      m_currentChannelUsed = false;
      return;
   }
   
   chanToEtaItr = m_map_channelId_etaPhiId.find(chanId.GetId());
   if(chanToEtaItr == m_map_channelId_etaPhiId.end()){
      std::cerr << "CpmChannelMap::SetChannelSerializer: ERROR Cool ID, " << chanId.GetIdAsString() << ", not found.\n";
      return;
   }
   
   m_currentEtaPhiId->SetId(chanToEtaItr->second);
   
   m_currentDeltaEta = 1;
   m_currentDeltaPhi = 1;
   
   etaToChanItr = m_map_etaPhiId_channelId.find(m_currentEtaPhiId->GetId());
   if(etaToChanItr == m_map_etaPhiId_channelId.end()){
      std::cerr << "CpmChannelMap::SetChannelSerializer: ERROR Eta Phi ID, " << m_currentEtaPhiId->GetIdAsString() << ", not found.\n";
      std::cerr << "CpmChannelMap::SetChannelSerializer: corresponds to eta/phi = " << m_currentEtaPhiId->GetEta() << "/" << m_currentEtaPhiId->GetPhi() << "; layer = " << m_currentEtaPhiId->GetLayer().GetLayerAsString() << std::endl;
      return;
   }
   
   *m_currentChannelId = etaToChanItr->second;
   
   FillCurrentChannelFromId(m_currentChannelId);
   
}

void CpmChannelMap::FillCurrentChannelFromId(std::vector<L1CaloChannelId>* id){
   for(unsigned int i=0;i<id->size();i++){
      m_currentCrate.push_back((*id)[i].GetCrate());
      m_currentModule.push_back((*id)[i].GetModule());
      m_currentSubmoduleSerializer.push_back((*id)[i].GetSubmodule());
      m_currentChannelSerializer.push_back((*id)[i].GetChannel());
      
      m_currentSubmoduleChip.push_back(GetCpChipFromSerializerChip((*id)[i].GetSubmodule()));
      m_currentChannelChip.push_back(GetCpChipChannelFromSerializerChip((*id)[i].GetSubmodule(),(*id)[i].GetChannel()));
   }
   
}


void CpmChannelMap::SetCPMRoI(unsigned int roiWord,CaloLayer& layer){
   CPMRoI temp(roiWord);
   SetCPMRoI(temp,layer);
}

void CpmChannelMap::SetCPMRoI(unsigned int crate,unsigned int module,unsigned int submodule,unsigned int location,CaloLayer& layer){
   CPMRoI temp(crate,module,submodule,location,0,0);
   SetCPMRoI(temp,layer);
}

// When using this method it should be understood that for one CPM RoI
// there are two channels associated, an EM and a HAD channel.
// To get both you must call SetCPMRoI twice:
// SetCPMRoI(roi,CaloLayer::EM); // Then grab and save channel id
// SetCPMRoI(roi,CaloLayer::HAD); // again grab and save the channel id
void CpmChannelMap::SetCPMRoI(CPMRoI& roi,CaloLayer& layer){
   
   // need to decode location in RoI to useful hardware terms.
   // Location translates to 1 eta/phi position for both 
   // EM + HAD so there are two corresponding CP chip channels
   // 
   // For one CP Chip:
   // 2 3 6 7 (top) => eta,phi = (0,0.1) (0.1,0.1) (0.2,0.1) (0.3,0.1)
   // 0 1 4 5 (bot) => eta,phi = (0,0)   (0.1,0)   (0.2,0)   (0.3,0)
   unsigned int location = roi.location();
   unsigned int em_chipChannel=0;
   // I use the EM chip channel for this location to set the channel
        if(location == 0) em_chipChannel = 0;
   else if(location == 1) em_chipChannel = 1;
   else if(location == 2) em_chipChannel = 4;
   else if(location == 3) em_chipChannel = 5;
   else if(location == 4) em_chipChannel = 2;
   else if(location == 5) em_chipChannel = 3;
   else if(location == 6) em_chipChannel = 6;
   else if(location == 7) em_chipChannel = 7;
   
   unsigned int had_chipChannel = em_chipChannel + 8;
   // now I set the chip channel
   unsigned int shiftedCrate = roi.crate() + 8; // needed since I use 8-11 for my CPM crate number and RoI uses 0-3
   if(layer.GetCaloLayer() == CaloLayer::EM)
      SetChannelCpChip(shiftedCrate,roi.cpm(),roi.chip(),em_chipChannel);
   else if(layer.GetCaloLayer() == CaloLayer::HAD){
      SetChannelCpChip(shiftedCrate,roi.cpm(),roi.chip(),had_chipChannel);
   }
}

// Compares a float to a float and returns true if
// they are approximately equal
bool CpmChannelMap::FloatIsEqualTo(const float x, const float y){
   if(fabs(x-y) < 0.005){
      return true;
   }
   return false;
}

