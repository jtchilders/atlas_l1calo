#include "TcppChannelMap.h"


const float        TcppChannelMap::myPI          = 3.14159265;
const float        TcppChannelMap::MAX_ETA       = 4.9;
const float        TcppChannelMap::MIN_ETA       = -4.9;
const float        TcppChannelMap::TCPP_MAX_ETA  = 1.5;
const float        TcppChannelMap::TCPP_MIN_ETA  = -1.5;
const float        TcppChannelMap::MAX_PHI       = 2.0*3.14159265;
const float        TcppChannelMap::MIN_PHI       = 0.0;

TcppChannelMap::TcppChannelMap(void){

	// Initialize variables
	ClearTcpp();
	
	FillEtaPhi();
}

TcppChannelMap::~TcppChannelMap(void){
	
}

void TcppChannelMap::ClearTcpp(void){
	
   m_currentEtaPhiId.Clear();
   m_currentDeltaEta = 999;
	m_currentDeltaPhi = 999;
	
	m_currentCrate.clear();
	m_currentModule.clear();
	m_currentOutputSubmodule.clear();
	m_currentOutputChannel.clear();
	m_currentInputSubmodule.clear();
	m_currentInputChannel.clear();
	
	m_currentOutputChannelId.clear();
	m_currentInputChannelId.clear();
	
   m_currentTileDrawer.clear();
}

void TcppChannelMap::GetInputFromOutput(const unsigned int outConnector,const unsigned int outChannel, unsigned int& inConnector,unsigned int& inChannel) const{
   inConnector = 0;
   inChannel = 0;
   
   if(outConnector == 0){
      if( 0 <= outChannel && outChannel <= 8){
         inConnector = 1;
         inChannel = 8 - outChannel;
      }
      else if( 9 <= outChannel && outChannel <= 14){
         inConnector = 0;
         inChannel = 5 - (outChannel - 9);
      }
   }
   else if(outConnector == 2){
      if( 0 <= outChannel && outChannel <= 8){
         inConnector = 3;
         inChannel = 8 - outChannel;
      }
      else if( 9 <= outChannel && outChannel <= 14){
         inConnector = 2;
         inChannel = 5 - (outChannel - 9);
      }
   }
}

void TcppChannelMap::GetOutputFromInput(const unsigned int inConnector,const unsigned int inChannel, unsigned int& outConnector,unsigned int& outChannel) const{
   outConnector = 0;
   outChannel = 0;
   
   if(inConnector == 0 || inConnector == 1)
      outConnector = 0;
   else if(inConnector == 2 || inConnector == 3)
      outConnector = 2;
   
   if(inConnector == 0 || inConnector == 2)
      outChannel = 9 + (5 - inChannel);
   else if(inConnector == 1 || inConnector == 3)
      outChannel = 8-inChannel;
}

unsigned int TcppChannelMap::GetTowerNumber(const unsigned int outChannel) const{
   return (outChannel < 9) ? outChannel + 1 : (outChannel - 9) + 1;
}


void TcppChannelMap::FillEtaPhi(void){
	
	for(unsigned int crate = MIN_CRATE;crate <= MAX_CRATE;crate++){
      for(unsigned int module = MIN_MODULE;module <= MAX_MODULE;module++){
         for(unsigned int outConnector = MIN_OUTPUT_CONNECTOR;outConnector <= MAX_OUTPUT_CONNECTOR;outConnector++){
            for(unsigned int outChannel = MIN_OUTPUT_CHANNEL;outChannel <= MAX_OUTPUT_CHANNEL;outChannel++){
					
					L1CaloChannelId id(L1CaloChannelId::TCPP,crate,module,outConnector,outChannel);
					
               const unsigned int eta = GetEtaFromChannel(crate,outChannel);
               const unsigned int phi = GetPhiFromChannel(crate,module,outConnector);
               
               EtaPhiId etaPhiId(eta,phi,CaloLayer::CaloLayer(CaloLayer::HAD));
               
               m_map_channelId_etaPhiId[id.GetId()] = etaPhiId.GetId();
               
               m_map_etaPhiId_channelId[etaPhiId.GetId()] = id;
					
				} // end for(channel)
				
			} // end for(submodule)
			
		} // end for(module)
		
	} // end for(crate)
}

unsigned int TcppChannelMap::GetEtaFromId(const L1CaloChannelId id) const{
   return GetEtaFromChannel(id.GetCrate(),id.GetChannel());
}

unsigned int TcppChannelMap::GetEtaFromChannel(const unsigned int crate,const unsigned int outChannel) const{
   unsigned int eta = 0;
   if(crate == 2 || crate == 3)
      eta = outChannel + 49;
   else if(crate == 0 || crate == 1)
      eta = (-1)*(outChannel+1) + 49;
   
   return eta;
}

unsigned int TcppChannelMap::GetPhiFromId(const L1CaloChannelId id) const{
   return GetPhiFromChannel(id.GetCrate(),id.GetModule(),id.GetSubmodule());
}

unsigned int TcppChannelMap::GetPhiFromChannel(const unsigned int crate,const unsigned int module,const unsigned int outConnector) const{
   unsigned int phi = 0;
   
   if(crate == 0 || crate == 2){
      if( 0 <= module && module <= 7){
         const unsigned int connectorPhi = outConnector == 0 ? 0 : 1;
         phi = 0 + module*2 + connectorPhi;
      }
      else if( 8 <= module && module <= 15){
         const unsigned int connectorPhi = outConnector == 0 ? 0 : 1;
         phi = 48 + (module - 8)*2 + connectorPhi;
      }
   }
   else if(crate == 1 || crate == 3){
      const unsigned int connectorPhi = outConnector == 0 ? 0 : 1;
      phi = 16 + module*2 + connectorPhi;
   }
   
   return phi;
}

TileDrawerId TcppChannelMap::GetTileDrawerFromOutputId(const L1CaloChannelId outputId){
   TileDrawerId id;
   
   if( outputId.GetCrate() == 0){
      if(outputId.GetModule() <= 7){
         if(outputId.GetChannel() >= 9){
            id.SetId(TileDrawerId::EBC,outputId.GetModule()*2+outputId.GetSubmodule()/2);
         }
         else{
            id.SetId(TileDrawerId::LBC,outputId.GetModule()*2+outputId.GetSubmodule()/2);
         }
      }
      else{
         if(outputId.GetChannel() >= 9){
            id.SetId(TileDrawerId::EBC,48+(outputId.GetModule()-8)*2+outputId.GetSubmodule()/2);
         }
         else{
            id.SetId(TileDrawerId::LBC,48+(outputId.GetModule()-8)*2+outputId.GetSubmodule()/2);
         }
      }
      
   }
   else if(outputId.GetCrate() == 1){
      if(outputId.GetChannel() >= 9){
         id.SetId(TileDrawerId::EBC,16+outputId.GetModule()*2+outputId.GetSubmodule()/2);
      }
      else{
         id.SetId(TileDrawerId::LBC,16+outputId.GetModule()*2+outputId.GetSubmodule()/2);
      }
   }
   else if(outputId.GetCrate() == 2){
      if(outputId.GetModule() <= 7){
         if(outputId.GetChannel() >= 9){
            id.SetId(TileDrawerId::EBA,outputId.GetModule()*2+outputId.GetSubmodule()/2);
         }
         else{
            id.SetId(TileDrawerId::LBA,outputId.GetModule()*2+outputId.GetSubmodule()/2);
         }
      }
      else{
         if(outputId.GetChannel() >= 9){
            id.SetId(TileDrawerId::EBA,48+(outputId.GetModule()-8)*2+outputId.GetSubmodule()/2);
         }
         else{
            id.SetId(TileDrawerId::LBA,48+(outputId.GetModule()-8)*2+outputId.GetSubmodule()/2);
         }
      }
   }
   else if(outputId.GetCrate() == 3){
       if(outputId.GetChannel() >= 9){
         id.SetId(TileDrawerId::EBA,16+outputId.GetModule()*2+outputId.GetSubmodule()/2);
      }
      else{
         id.SetId(TileDrawerId::LBA,16+outputId.GetModule()*2+outputId.GetSubmodule()/2);
      }
   }
   
   
   return id;
}

void TcppChannelMap::SetOutputChannelId(const L1CaloChannelId id){
	SetOutputChannel(id.GetCrate(),id.GetModule(),id.GetSubmodule(),id.GetChannel());
}

void TcppChannelMap::SetOutputChannel(const unsigned int inCrate,const unsigned int inModule,const unsigned int inSubmodule,const unsigned int inChannel){
	
	if(!CheckOutputChannel(inCrate,inModule,inSubmodule,inChannel)){
      std::cerr << "TcppChannelMap::SetOutputChannel: ERROR Incorrect channel information.\n";
      return;
   }
   
	ClearTcpp();
	
	L1CaloChannelId outputId(L1CaloChannelId::TCPP,inCrate,inModule,inSubmodule,inChannel);
   
	m_currentOutputChannelId.push_back(outputId);
   FillCurrentChannelFromOutputId(&m_currentOutputChannelId);
	
   std::map<unsigned int,unsigned int>::iterator iter;
   iter = m_map_channelId_etaPhiId.find(outputId.GetId());
   if(iter == m_map_channelId_etaPhiId.end()){
      std::cerr << "TcppChannelMap::SetOutputChannel: Channel ID, 0x" << outputId.GetIdAsString() << ", not found.\n";
      return;
   }
   m_currentEtaPhiId.SetId(iter->second);
   
	m_currentDeltaEta = 1;
	m_currentDeltaPhi = 1;
	
}

void TcppChannelMap::SetInputChannelId(const L1CaloChannelId id){
	SetInputChannel(id.GetCrate(),id.GetModule(),id.GetSubmodule(),id.GetChannel());
}

void TcppChannelMap::SetInputChannel(const unsigned int inCrate,const unsigned int inModule,const unsigned int inSubmodule,const unsigned int inChannel){
	
   if(!CheckInputChannel(inCrate,inModule,inSubmodule,inChannel)){
      std::cerr << "TcppChannelMap::SetInputChannel: ERROR Incorrect channel Information.\n";
      return;
   }
   
	ClearTcpp();
	
	L1CaloChannelId inputId(L1CaloChannelId::TCPP,inCrate,inModule,inSubmodule,inChannel);
	
   unsigned int outSubmodule=0,outChannel=0;
   GetOutputFromInput(inSubmodule,inChannel,outSubmodule,outChannel);
   
   L1CaloChannelId outputId(L1CaloChannelId::TCPP,inCrate,inModule,outSubmodule,outChannel);
   
   m_currentOutputChannelId.push_back(outputId);
   
   FillCurrentChannelFromOutputId(&m_currentOutputChannelId);
   
   std::map<unsigned int,unsigned int>::iterator iter;
   iter = m_map_channelId_etaPhiId.find(outputId.GetId());
   if(iter == m_map_channelId_etaPhiId.end()){
      std::cerr << "TcppChannelMap::SetInputChannel: Channel ID, 0x" << outputId.GetIdAsString() << ", not found.\n";
      std::cerr << "TcppChannelMap::SetInputChannel: This was derived from your passed Input Id, 0x" << inputId.GetIdAsString() << std::endl;
      return;
   }
   m_currentEtaPhiId.SetId(iter->second);
   
	m_currentDeltaEta = 1;
	m_currentDeltaPhi = 1;
	
}

void TcppChannelMap::SetEtaPhi(float inEta,float inPhi,CaloLayer inLayer){
	
	if(!CheckEtaPhiRange(inEta,inPhi,inLayer)){
      std::cerr << "TcppChannelMap::SetEtaPhi: ERROR Incorrect eta/phi range or layer.\n";
      return;
   }
	// The CPM Covers a smaller eta range than the rest of the system
   // so if outside this range nothing is done and no error is thrown.
   if( !(TCPP_MIN_ETA < inEta && inEta < TCPP_MAX_ETA) && !FloatIsEqualTo(inEta,TCPP_MIN_ETA)){
      ClearTcpp();
      return;
   }
   
   // Only continue if HAD layer
   if(!inLayer.IsHAD()) return;
   
	ClearTcpp();
	
   m_currentEtaPhiId.SetEtaPhi(inEta,inPhi,inLayer);
   
   std::map<unsigned int,L1CaloChannelId>::iterator epChanIdIter;
   
   epChanIdIter = m_map_etaPhiId_channelId.find(m_currentEtaPhiId.GetId());
   if(epChanIdIter == m_map_etaPhiId_channelId.end()){
      std::cerr << "TcppChannelMap::SetEtaPhi: ERROR Cannot find eta/phi ID: 0x" << m_currentEtaPhiId.GetIdAsString() << "\n";
      EtaPhiId tempId(m_currentEtaPhiId.GetIntegerEta(),m_currentEtaPhiId.GetIntegerPhi(),m_currentEtaPhiId.GetLayer());
      std::cerr << "TcppChannelMap::SetEtaPhi: Corresponds to eta: " << tempId.GetEta() << " phi: " << tempId.GetPhi() << " layer: " << tempId.GetLayer().GetLayerAsString() << std::endl;
      return;
   }
   
   m_currentOutputChannelId.push_back(epChanIdIter->second);
   
	m_currentDeltaEta = 1;
	m_currentDeltaPhi = 1;
   
   FillCurrentChannelFromOutputId(&m_currentOutputChannelId);
}


void TcppChannelMap::SetEtaPhi(float inEta,float inDeltaEta,float inPhi,float inDeltaPhi,CaloLayer inLayer){
	
   if(!CheckDeltaEtaPhiRange(inEta,inDeltaEta,inPhi,inDeltaPhi,inLayer)){
      std::cerr << "TcppChannelMap::SetEtaPhi(delta): ERROR Incorrect eta/phi range or layer.\n";
      return;
   }
   
   // The TCPP Covers a smaller eta range than the rest of the system
   // so if outside this range nothing is done and no error is thrown.
   if( !(TCPP_MIN_ETA < inEta && (inEta+inDeltaEta) < TCPP_MAX_ETA) && !FloatIsEqualTo(inEta,TCPP_MIN_ETA)  && !FloatIsEqualTo(inEta+inDeltaEta,TCPP_MAX_ETA) ){
      ClearTcpp();
      return;
   }
   
   // Only continue if HAD layer
   if(inLayer.GetCaloLayer() != CaloLayer::HAD) return;
   
	ClearTcpp();
	
   m_currentEtaPhiId.SetEtaPhi(inEta,inPhi,inLayer);
   
   EtaPhiId deltaEtaPhiId(inDeltaEta,inDeltaPhi,inLayer);
   
   m_currentDeltaEta = deltaEtaPhiId.GetIntegerEta() - 49;
	m_currentDeltaPhi = deltaEtaPhiId.GetIntegerPhi();
	
   FindChannels(m_currentEtaPhiId.GetIntegerTriggerTowerEta(),m_currentDeltaEta,m_currentEtaPhiId.GetIntegerTriggerTowerPhi(),m_currentDeltaPhi,m_currentOutputChannelId);
   
   FillCurrentChannelFromOutputId(&m_currentOutputChannelId);
	
}

void TcppChannelMap::FindChannels(const unsigned int inEta,const unsigned int inDeltaEta,const unsigned int inPhi,const unsigned int inDeltaPhi,std::vector<L1CaloChannelId>& id){
   
   for(unsigned int eta = inEta;eta<inEta+inDeltaEta;++eta){
      for(unsigned int phi = inPhi;phi<inPhi+inDeltaPhi;++phi){
         EtaPhiId ep(inEta,inPhi,CaloLayer::CaloLayer(CaloLayer::HAD));
         
         std::map<unsigned int,L1CaloChannelId>::iterator iter;
         
         iter = m_map_etaPhiId_channelId.find(ep.GetId());
         if(iter == m_map_etaPhiId_channelId.end()){
            std::cerr << "TcppChannelMap::FindChannels: EtaPhiId, 0x" << m_currentEtaPhiId.GetIdAsString() << ", was not found.\n";
            std::cerr << "TcppChannelMap::FindChannels: corresponds to eta/phi = "  << m_currentEtaPhiId.GetEta() << "/" << m_currentEtaPhiId.GetPhi() << " layer = " << m_currentEtaPhiId.GetLayer().GetLayerAsString() << "\n";
            return;
         }
         
         id.push_back(iter->second);
      }
   }
   
}


void TcppChannelMap::FillCurrentChannelFromOutputId(std::vector<L1CaloChannelId>* id){
   for(unsigned int i=0;i<id->size();i++){
      m_currentCrate.push_back((*id)[i].GetCrate());
      m_currentModule.push_back((*id)[i].GetModule());
      m_currentOutputSubmodule.push_back((*id)[i].GetSubmodule());
      m_currentOutputChannel.push_back((*id)[i].GetChannel());
      
      unsigned int inputSubmodule=0,inputChannel=0;
      GetInputFromOutput(m_currentOutputSubmodule.back(),m_currentOutputChannel.back(),inputSubmodule,inputChannel);
      
      m_currentInputSubmodule.push_back(inputSubmodule);
      m_currentInputChannel.push_back(inputChannel);
      
      L1CaloChannelId inputId(L1CaloChannelId::TCPP,(*id)[i].GetCrate(),(*id)[i].GetModule(),inputSubmodule,inputChannel);
      m_currentInputChannelId.push_back(inputId);
      
      m_currentTowerNumber.push_back(GetTowerNumber((*id)[i].GetChannel()));
      
      m_currentTileDrawer.push_back(GetTileDrawerFromOutputId((*id)[i]));
   }
   
}

bool TcppChannelMap::CheckInputChannel(const unsigned int& inCrate,const unsigned int& inModule,const unsigned int& inSubmodule,const unsigned int& inChannel) const {
	if( !(inCrate <= MAX_CRATE)){
		std::cerr << "TcppChannelMap::CheckInputChannel: Crate number " << inCrate << " is not in correct range: " << MIN_CRATE << " to " << MAX_CRATE << std::endl;
		return false;
	}
	if( !(inModule <= MAX_MODULE) ){
		std::cerr << "TcppChannelMap::CheckInputChannel: Module number " << inModule << " is not in correct range: " << MIN_MODULE << " to " << MAX_MODULE << std::endl;
		return false;
	}
	if( !(inSubmodule <= MAX_INPUT_CONNECTOR) ){
		std::cerr << "TcppChannelMap::CheckInputChannel: Submodule number " << inSubmodule << "is not in correct range: " << MIN_INPUT_CONNECTOR << " to " << MAX_INPUT_CONNECTOR << std::endl;
		return false;
	}
	if( !(inChannel <= MAX_INPUT_CHANNEL) ){
		std::cerr << "TcppChannelMap::CheckInputChannel: Channel number " << inChannel << " is not in correct range: " << MIN_INPUT_CHANNEL << " to " << MAX_INPUT_CHANNEL << std::endl;
		return false;
	}
   
   return true;
}

bool TcppChannelMap::CheckOutputChannel(const unsigned int& inCrate,const unsigned int& inModule,const unsigned int& inSubmodule,const unsigned int& inChannel) const {
   if( !(inCrate <= MAX_CRATE)){
      std::cerr << "TcppChannelMap::CheckOutputChannel: Crate number " << inCrate << " is not in correct range: " << MIN_CRATE << " to " << MAX_CRATE << std::endl;
      return false;
   }
   if( !(inModule <= MAX_MODULE) ){
      std::cerr << "TcppChannelMap::CheckOutputChannel: Module number " << inModule << " is not in correct range: " << MIN_MODULE << " to " << MAX_MODULE << std::endl;
      return false;
   }
   if( !(inSubmodule <= MAX_OUTPUT_CONNECTOR) ){
      std::cerr << "TcppChannelMap::CheckOutputChannel: Submodule number " << inSubmodule << "is not in correct range: " << MIN_OUTPUT_CONNECTOR << " to " << MAX_OUTPUT_CONNECTOR << std::endl;
      return false;
   }
   if( !(inChannel <= MAX_OUTPUT_CHANNEL) ){
      std::cerr << "TcppChannelMap::CheckOutputChannel: Channel number " << inChannel << " is not in correct range: " << MIN_OUTPUT_CHANNEL << " to " << MAX_OUTPUT_CHANNEL << std::endl;
      return false;
   }

   return true;
}

bool TcppChannelMap::CheckEtaPhiRange(const float& inEta, const float& inPhi,CaloLayer& inLayer) const {
if( !(MIN_ETA < inEta && inEta < MAX_ETA) && !FloatIsEqualTo(inEta,MIN_ETA)){
      std::cerr << "TcppChannelMap::CheckEtaPhiRange: Eta value, " << inEta << ", is out of range: " << MIN_ETA << " to " << MAX_ETA << "\n";
      return false;
   }
   if( !(MIN_PHI < inPhi && inPhi < MAX_PHI) && !FloatIsEqualTo(inPhi,MIN_PHI)){
      std::cerr << "TcppChannelMap::CheckEtaPhiRange: Phi value, " << inPhi << ", is out of range: " << MIN_PHI << " to " << MAX_PHI << "\n";
      return false;
   }
   if(!inLayer.IsSet()){
      std::cerr << "TcppChannelMap::CheckEtaPhiRange: CaloLayer Value, " << inLayer.GetLayerAsString() << ", must be EM or HAD\n";
      return false;
   }
   
   return true;
}

bool TcppChannelMap::CheckDeltaEtaPhiRange(const float& inEta,const float& inDeltaEta,const float& inPhi,const float& inDeltaPhi,CaloLayer& inLayer) const {
   if( !(MIN_ETA < inEta && (inEta+inDeltaEta) < MAX_ETA) && !FloatIsEqualTo(inEta,MIN_ETA) && !FloatIsEqualTo(inEta+inDeltaEta,MAX_ETA)) {
      std::cerr << "TcppChannelMap::CheckDeltaEtaPhiRange: Eta value, " << inEta << ", or (Eta+deltaEta) value, " << (inEta+inDeltaEta) << ", is out of range: " << MIN_ETA << " to " << MAX_ETA << "\n";
      return false;
   }
   if( !(MIN_PHI < inPhi && ((inPhi+inDeltaPhi) < MAX_PHI) ) && !FloatIsEqualTo(inPhi,MIN_PHI) && !FloatIsEqualTo(inPhi+inDeltaPhi,MAX_PHI)) {
      std::cerr << "TcppChannelMap::CheckDeltaEtaPhiRange: Phi value, " << inPhi << ", or (Eta+deltaEta) value, " << (inPhi+inDeltaPhi) << ", is out of range: " << MIN_PHI << " to " << MAX_PHI << "\n";
      return false;
   }
   if(!inLayer.IsSet()){
      std::cerr << "TcppChannelMap::CheckDeltaEtaPhiRange: CaloLayer Value, " << inLayer.GetLayerAsString() << ", must be EM or HAD\n";
      return false;
   }
   
   return true;
}

// Compares a float to a float and returns true if
// they are approximately equal
bool TcppChannelMap::FloatIsEqualTo(const float x, const float y) const{
   if(fabs(x-y) < 0.005){
      return true;
   }
   return false;
}

