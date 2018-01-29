
#include "JemChannelMap.h"


const float        JemChannelMap::MAX_ETA       = 4.9;
const float        JemChannelMap::MIN_ETA       = -4.9;
const float        JemChannelMap::MAX_PHI       = 2.0*3.14159265;
const float        JemChannelMap::MIN_PHI       = 0.0;
   
JemChannelMap::JemChannelMap(void){
	
	// Initialize variables
	ClearJem();
	
	FillEtaPhi();
}

JemChannelMap::~JemChannelMap(void){
   
}

void JemChannelMap::ClearJem(void){
   m_currentEta = 999;
   m_currentDeltaEta = 999;
   m_currentPhi = 999;
   m_currentDeltaPhi = 999;
   
   m_currentEtaPhiId.Clear();
   m_currentDeltaId.Clear();
   
   m_currentLayer.Clear();
   
   m_vect_currentCrate.clear();
   m_vect_currentModule.clear();
   m_vect_currentChannel.clear();
   
   m_vect_currentChannelId.clear();
}

void JemChannelMap::FillEtaPhi(void){
	
   for(unsigned int crate=MIN_CRATE;crate <= MAX_CRATE;crate++){
      for(unsigned int jem=MIN_MODULE;jem <= MAX_MODULE;jem++){
         for(unsigned int chan=MIN_CHANNEL;chan <= MAX_CHANNEL;chan++){
            
            
            L1CaloChannelId jemId(L1CaloChannelId::JEM,crate,jem,0,chan);
            
            
            CaloLayer layer;
            if(chan % 2 == 0) // even is EM
               layer.SetCaloLayer(CaloLayer::EM);
            else // odd is HAD
               layer.SetCaloLayer(CaloLayer::HAD);
            
            m_map_jem_layer[jemId.GetId()] = layer;
            
            int eta = 999, deltaEta = 999;
            int phi = 999, deltaPhi = 999;
            if( jem == 0 || jem == 8){
	            unsigned int crateEta = 0;
	            unsigned int cratePhi = 16*(crate-MIN_CRATE);
	            
	            unsigned int jemEta = 0;
	            unsigned int jemPhi = ((unsigned int)(jem/8))*32;
	            
	            unsigned int chanEta = 0;
	            int chanPhi = 0;
	            
	            unsigned int tChan = ((int)(chan/2)); // 0 - 43
	            unsigned int ttChan = ((int)(tChan/4)); // 0 - 10
	            unsigned int tttChan = tChan - ttChan*4; // 0 - 4
	            
	            if( tttChan == 2){
		            chanEta = -29 + 49;
		            chanPhi = ttChan*2 - 2;
		            
                  eta = crateEta + jemEta + chanEta;
		            
		            if(crate == 0 && jem == 0 && ttChan == 0)
			            chanPhi = 64 - 2;
		            else if(crate == 1 && jem == 8 && ttChan == 9)
			            chanPhi = -1*(cratePhi + jemPhi); // want phi = 0
		            else if(crate == 1 && jem == 8 && ttChan == 10)
			            chanPhi = -1*(cratePhi + jemPhi) + 2; // want phi = 2
		            
		            phi = cratePhi + jemPhi + chanPhi;
                  
		            deltaEta = 2;
		            deltaPhi = 2;
		            
                  
	            }
	            else if( tttChan == 3){
		            chanEta = -27 + 49;
		            chanPhi =  ttChan*2 - 2;
		            
		            eta = crateEta + jemEta + chanEta;
                  
		            if(crate == 0 && jem == 0 && ttChan == 0)
			            chanPhi = 64 - 2;
		            else if(crate == 1 && jem == 8 && ttChan == 9)
			            chanPhi = -1*(cratePhi + jemPhi); // want phi = 0
		            else if(crate == 1 && jem == 8 && ttChan == 10)
			            chanPhi = -1*(cratePhi + jemPhi) + 2; // want phi = 2
		            
		            phi = cratePhi + jemPhi + chanPhi;
                  
                  m_map_jem_phi[jemId.GetId()] = phi;
		            
		            deltaEta = 3;
		            deltaPhi = 2;
	            }
	            else if(ttChan == 0 && tttChan == 0){ // EC Fanout V
		            chanEta = -32 + 49;
		            
		            eta = crateEta + jemEta + chanEta;
		            
		            if(crate == 0 && jem == 0)
			            chanPhi = 64 - 2;
		            else
			            chanPhi = -2;
		            
		            phi = cratePhi + jemPhi + chanPhi;
                  
		            deltaEta = 3;
		            deltaPhi = 2;
	            }
	            else if(ttChan == 2 && (tttChan == 0 || tttChan == 1)){ // FCAL Fanout B
		            chanEta = -49 + 49;
		            
		            eta = crateEta + jemEta + chanEta;
		            
		            if(crate == 0 && jem == 0 && tttChan == 0)
			            chanPhi = 64 - 4;
		            else if(crate == 1 && jem == 8 && tttChan == 1)
			            chanPhi = -1*(cratePhi+jemPhi); // want phi = 0
		            else if(tttChan == 0)
			            chanPhi = -4;
		            else if(tttChan == 1)
			            chanPhi = 16;
		            
		            phi = cratePhi + jemPhi + chanPhi;
                  
		            deltaEta = 17;
		            deltaPhi = 4;
	            }
	            else if(ttChan == 3 || ttChan == 4 || ttChan == 7 || ttChan == 8){ // EC channels C/D/G/H
		            
		            chanEta = -32 + 49;
		            
		            eta = crateEta + jemEta + chanEta;
                  
		            if(ttChan == 3){
			            if(tttChan == 0)
				            chanPhi = 2*3;
			            else if(tttChan == 1)
				            chanPhi = 2*2;
		            }
		            else if(ttChan == 4){
			            if(tttChan == 1)
				            chanPhi = 2*1;
			            else if(tttChan == 0)
				            chanPhi = 2*0;
		            }
		            else if(ttChan == 7){
			            if(tttChan == 0)
				            chanPhi = 2*7;
			            else if(tttChan == 1)
				            chanPhi = 2*6;
		            }
		            else if(ttChan == 8){
			            if(tttChan == 1)
				            chanPhi = 2*5;
			            else if(tttChan == 0)
				            chanPhi = 2*4;
		            }
		            
		            phi = cratePhi + jemPhi + chanPhi;
                  
		            deltaEta = 3;
		            deltaPhi = 2;
	            }
	            else if(ttChan == 5 || ttChan == 6){ // FCAL E/F
		            chanEta = -49 + 49;
		            
		            eta = crateEta + jemEta + chanEta;
		            
		            if(ttChan == 5){
			            if(tttChan == 0)
				            chanPhi = 4*3;
			            else if(tttChan == 1)
				            chanPhi = 4*2;
		            }
		            else if(ttChan == 6){
			            if(tttChan == 1)
				            chanPhi = 4*1;
			            else if(tttChan == 0)
				            chanPhi = 4*0;
		            }
		            
		            phi = cratePhi + jemPhi + chanPhi;
                  
		            deltaEta = 17;
		            deltaPhi = 4;
	            }
	            else if(ttChan == 9){ // EC Fanout W
                  chanEta = -32 + 49;
                  
                  eta = crateEta + jemEta + chanEta;
                  
                  if(crate == 1 && jem == 8 && tttChan == 0)
                     chanPhi = -1*(cratePhi+jemPhi); // should be phi = 0
                  else if(crate == 1 && jem == 8 && tttChan == 1)
                     chanPhi = -1*(cratePhi+jemPhi) + 2; // should be phi = 2
                  else
                     chanPhi = 16 + 2*tttChan;
                  
                  phi = cratePhi + jemPhi + chanPhi;
                  
                  deltaEta = 3;
                  deltaPhi = 2;
               }
               
               
               //if(crate == 0 && jem == 0)
               //	std::cerr << "chan: " << chan << "; " << m_map_jem_eta[jemId.GetId()] << " " << m_map_jem_phi[jemId.GetId()] << std::endl;
               
            } // end if(jem=0/8)
            else if( jem == 7 || jem == 15){
               unsigned int crateEta = 0;
               unsigned int cratePhi = 16*(crate-MIN_CRATE);
               
               unsigned int jemEta = 0;
               unsigned int jemPhi = ((int)(jem/8))*32;
               
               unsigned int chanEta = 0;
               int chanPhi = 0;
               
               unsigned int tChan = ((int)(chan/2)); // 0 - 43
               unsigned int ttChan = ((int)(tChan/4)); // 0 - 10
               unsigned int tttChan = tChan - ttChan*4; // 0 - 3
               
               if( tttChan == 0){
                  chanEta = 24 + 49;
                  chanPhi =  ttChan*2 - 2;
                  
                  eta = crateEta + jemEta + chanEta;
                  
                  if(crate == 0 && jem == 7 && ttChan == 0)
                     chanPhi = 64 - 2;
                  else if(crate == 1 && jem == 15 && ttChan == 9)
                     chanPhi = -1*(cratePhi+jemPhi); // want phi = 0
                  else if(crate == 1 && jem == 15 && ttChan == 10)
                     chanPhi = -1*(cratePhi+jemPhi) + 2; // want phi = 0
                  
                  phi = cratePhi + jemPhi + chanPhi;
                  
                  deltaEta = 3;
                  deltaPhi = 2;
               }
               else if( tttChan == 1){ // 
                  chanEta = 27 + 49;
                  chanPhi =  ttChan*2 - 2;
                  
                  eta = crateEta + jemEta + chanEta;
                  
                  if(crate == 0 && jem == 7 && ttChan == 0)
                     chanPhi = 64 - 2;
                  else if(crate == 1 && jem == 15 && ttChan == 9)
                     chanPhi = -1*(cratePhi+jemPhi); // want phi = 0
                  else if(crate == 1 && jem == 15 && ttChan == 10)
                     chanPhi = -1*(cratePhi+jemPhi) + 2; // want phi = 0
                  
                  phi = cratePhi + jemPhi + chanPhi;
                  
                  deltaEta = 2;
                  deltaPhi = 2;
               }
               else if(ttChan == 0 && tttChan == 2){ // EC Fanout V
                  chanEta = 29 + 49;
                  
                  eta = crateEta + jemEta + chanEta;
                  
                  if(crate == 0 && jem == 7)
                     chanPhi = 64 - 2;
                  else
                     chanPhi = -2;
                  
                  phi = cratePhi + jemPhi + chanPhi;
                  
                  deltaEta = 3;
                  deltaPhi = 2;
               }
               else if(ttChan == 2 && (tttChan == 2 || tttChan == 3)){ // FCAL Fanout B
                  chanEta = 32 + 49;
                  
                  eta = crateEta + jemEta + chanEta;
                  
                  if(crate == 0 && jem == 7 && tttChan == 2)
                     chanPhi = 64 - 4;
                  else if(crate == 1 && jem == 15 && tttChan == 3)
                     chanPhi = -1*(cratePhi+jemPhi); // want phi = 0
                  else if(tttChan == 2)
                     chanPhi = -4;
                  else if(tttChan == 3)
                     chanPhi = 16;
                  
                  phi = cratePhi + jemPhi + chanPhi;
                  
                  deltaEta = 17;
                  deltaPhi = 4;
               }
               else if(ttChan == 3 || ttChan == 4 || ttChan == 7 || ttChan == 8){ // EC channels C/D/G/H
                  
                  chanEta = 29 + 49;
                  
                  eta = crateEta + jemEta + chanEta;
                  
                  if(ttChan == 3){
                     if(tttChan == 2)
                        chanPhi = 2*3;
                     else if(tttChan == 3)
                        chanPhi = 2*2;
                  }
                  else if(ttChan == 4){
                     if(tttChan == 3)
                     chanPhi = 2*1;
                     else if(tttChan == 2)
                        chanPhi = 2*0;
                  }
                  else if(ttChan == 7){
                     if(tttChan == 2)
                        chanPhi = 2*7;
                     else if(tttChan == 3)
                        chanPhi = 2*6;
                  }
                  else if(ttChan == 8){
                     if(tttChan == 3)
                        chanPhi = 2*5;
                     else if(tttChan == 2)
                        chanPhi = 2*4;
                  }
                  
                  phi = cratePhi + jemPhi + chanPhi;
                  
                  deltaEta = 3;
                  deltaPhi = 2;
	            }
	            else if(ttChan == 5 || ttChan == 6){ // FCAL E/F
                  chanEta = 32 + 49;
                  
                  eta = crateEta + jemEta + chanEta;
                  
                  if(ttChan == 5){
                  if(tttChan == 2)
                     chanPhi = 4*3;
                  else if(tttChan == 3)
                     chanPhi = 4*2;
                  }
                  else if(ttChan == 6){
                     if(tttChan == 3)
                        chanPhi = 4*1;
                     else if(tttChan == 2)
                        chanPhi = 4*0;
                  }
                  
                  phi = cratePhi + jemPhi + chanPhi;
                  
                  deltaEta = 17;
                  deltaPhi = 4;
               }
               else if(ttChan == 9){ // EC Fanout W
                  chanEta = 29 + 49;
                  
                  eta = crateEta + jemEta + chanEta;
                  
                  if(crate == 1 && jem == 15 && tttChan == 2)
	                  chanPhi = -1*(cratePhi+jemPhi);
                  else if(crate == 1 && jem == 15 && tttChan == 3)
	                  chanPhi = -1*(cratePhi+jemPhi) + 2;
                  else
	                  chanPhi = 16 + 2*(tttChan-2);
                  
                  phi = cratePhi + jemPhi + chanPhi;
                  
                  deltaEta = 3;
                  deltaPhi = 2;
	            }
               
	            //if(crate == 0 && jem == 7)
	            //	std::cerr << "chan: " << chan << "; " << m_map_jem_eta[jemId.GetId()] << " " << m_map_jem_phi[jemId.GetId()] << std::endl;
            } // end if(jem=7/15)
            else{
               unsigned int crateEta = 0;
               unsigned int cratePhi = 16*(crate-MIN_CRATE);
               
               unsigned int jemEta = (-24 + 49) + (jem - ((int)(jem/8))*8 - 1)*8; 
               unsigned int jemPhi = ((int)(jem/8))*32;
               
               unsigned int chanEta = (((int)(chan/2)) - ((int)(((int)(chan/2))/4))*4)*2;
               int chanPhi = -2 + ((int)(((int)(chan/2))/4))*2;
               
               eta = crateEta + jemEta + chanEta;
               
               if(crate == 0 && ( 0 <= jem && jem <= 7 ) && ( chan < 8) )
	               chanPhi = 64 - 2;
               else if(crate == 1 && ( 8 <= jem && jem <= 15 ) && (72 <= chan && chan < 80))
	               chanPhi = -1*(cratePhi+jemPhi);
               else if(crate == 1 && ( 8 <= jem && jem <= 15 ) && (80 <= chan && chan < 88))
	               chanPhi =  -1*(cratePhi+jemPhi) + 2;
               
               phi = cratePhi + jemPhi + chanPhi;
               
               deltaEta = 2;
               deltaPhi = 2;
            }
            
            if(eta == 999 || phi == 999) continue;
            m_map_jem_eta[jemId.GetId()] = (unsigned int)eta;
            if(phi == -2) phi = 62;
            else if(phi == -4) phi = 60;
            else if(phi == 64) phi = 0;
            else if(phi == 66) phi = 2;
            m_map_jem_phi[jemId.GetId()] = (unsigned int)phi;
            m_map_jem_deltaEta[jemId.GetId()] = (unsigned int)deltaEta;
            m_map_jem_deltaPhi[jemId.GetId()] = (unsigned int)deltaPhi;
            
            EtaPhiId etaPhiId((unsigned int)eta,(unsigned int)phi,layer);
            m_map_etaPhiId_channelId[etaPhiId.GetId()].push_back(jemId.GetId());
            
//             std::cerr << "crate: " << crate << " jem: " << jem << " chan: " << chan << std::endl;
            
//             std::cerr << "eta = " << eta << ":" << etaPhiId.GetEta() << " phi = " << phi << ":" << etaPhiId.GetPhi() << " layer = " << layer.GetLayerAsString() << " id = 0x" << etaPhiId.GetIdAsString() << std::endl;
//             std::cin.get();
            
         } // end for(chan)

      } // end for(jem)
      

   } // end for(crate)

}

void JemChannelMap::SearchForJemChannel(unsigned int inEta, unsigned int inPhi, CaloLayer inLayer,
   std::vector<unsigned int>* outCrate,std::vector<unsigned int>* outJem,std::vector<unsigned int>* outChan){
   
   if( !(MIN_UINT_ETA <= inEta && inEta < MAX_UINT_ETA)){
	   std::cerr << "JemChannelMap::SearchForJemChannel: Eta value, " << inEta << ", is out of range: " << MIN_UINT_ETA << " to " << MAX_UINT_ETA << "\n";
	   return;
   }
   if( !(MIN_UINT_PHI <= inPhi && inPhi < MAX_UINT_PHI)){
	   std::cerr << "JemChannelMap::SearchForJemChannel: Phi value, " << inPhi << ", is out of range: " << MIN_UINT_PHI << " to " << MAX_UINT_PHI << "\n";
	   return;
   }
   if( !inLayer.IsSet() ){
	   std::cerr << "JemChannelMap::SearchForJemChannel: CaloLayer value, " << inLayer.GetLayerAsString() << ", must be EM or HAD\n";
	   return;
   }
   
   unsigned int etaMin,etaMax,phiMin,phiMax;
   std::map<unsigned int,unsigned int>::iterator itEta,itPhi;
   for(unsigned int crate=MIN_CRATE;crate<MAX_CRATE;crate++){
      for(unsigned int jem=MIN_MODULE;jem<MAX_MODULE;jem++){
         for(unsigned int chan=MIN_CHANNEL;chan<MAX_CHANNEL;chan++){
            
            L1CaloChannelId jemId(L1CaloChannelId::JEM,crate,jem,0,chan);
            itEta = m_map_jem_eta.find(jemId.GetId());
            itPhi = m_map_jem_phi.find(jemId.GetId());
            
            //std::cerr << crate << " " << jem << " " << chan << std::endl;
            
            etaMin = itEta->second;
            etaMax = itEta->second + m_map_jem_deltaEta[jemId.GetId()];
            phiMin = itPhi->second;
            phiMax = itPhi->second + m_map_jem_deltaPhi[jemId.GetId()];
            
            //std::cerr << etaInRange << " " << phiInRange << " " << layerCorrect << std::endl;
            
            if((etaMin <= inEta && inEta < etaMax) 
               && (phiMin <= inPhi && inPhi < phiMax) 
               && (inLayer.GetCaloLayer() == m_map_jem_layer[jemId.GetId()].GetCaloLayer())){
               
               outCrate->push_back(crate);
               outJem->push_back(jem);
               outChan->push_back(chan);

            }
         }
      }
   }
}


void JemChannelMap::GetJemEtaPhi(unsigned int crate, unsigned int module, unsigned int channel, unsigned int& outEta, unsigned int& outPhi,CaloLayer& outLayer){
   
   if( !(MIN_CRATE <= crate && crate <= MAX_CRATE) ){
      std::cerr << "JemChannelMap::GetJemEtaPhi: Crate number must not correct range: " << MIN_CRATE << " to " << MAX_CRATE << std::endl;
      return;
   }
   if( !(MIN_MODULE <= module && module <= MAX_MODULE) ){
      std::cerr << "JemChannelMap::GetJemEtaPhi: JEM number must not correct range: " << MIN_MODULE << " to " << MAX_MODULE << std::endl;
      return;
   }
   if( !(MIN_CHANNEL <= channel && channel <= MAX_CHANNEL) ){
      std::cerr << "JemChannelMap::GetJemEtaPhi: Channel number must not correct range: " << MIN_CHANNEL << " to " << MAX_CHANNEL << std::endl;
      return;
   }
   
   L1CaloChannelId jemId(L1CaloChannelId::JEM,crate,module,0,channel);
   outEta = m_map_jem_eta[jemId.GetId()];
   outPhi = m_map_jem_phi[jemId.GetId()];
   outLayer = m_map_jem_layer[jemId.GetId()];
   
}

void JemChannelMap::GetJemChannel(unsigned int inEta, unsigned int inPhi, CaloLayer inLayer, std::vector<L1CaloChannelId>* outChanList){
   
   
   if( !(MIN_UINT_ETA <= inEta && inEta <= MAX_UINT_ETA)){
      std::cerr << "JemChannelMap::GetJemChannel: Eta value, " << inEta << ", is out of range: " << MIN_UINT_ETA << " to " << MAX_UINT_ETA << "\n";
      return;
   }
   if( !(MIN_UINT_PHI <= inPhi && inPhi <= MAX_UINT_PHI)){
      std::cerr << "JemChannelMap::GetJemChannel: Phi value, " << inPhi << ", is out of range: " << MIN_UINT_PHI << " to " << MAX_UINT_PHI << "\n";
      return;
   }
   if( !inLayer.IsSet() ){
      std::cerr << "JemChannelMap::GetJemChannel: CaloLayer value, " << inLayer.GetLayerAsString() << ", must be EM or HAD\n";
      return;
   }
   
   EtaPhiId etaPhiId(inEta,inPhi,inLayer);
   
   unsigned int baseEta = etaPhiId.GetIntegerJetElementEta();
   unsigned int basePhi = etaPhiId.GetIntegerJetElementPhi();
   
   etaPhiId.SetEtaPhi(baseEta,basePhi,inLayer);
   
   std::map<unsigned int,std::vector<L1CaloChannelId> >::iterator itJemChan = m_map_etaPhiId_channelId.find(etaPhiId.GetId());
   if(itJemChan == m_map_etaPhiId_channelId.end()){
	   std::cerr << "JemChannelMap::GetJemChannel: etaPhiID not found.\n";
	   std::cerr << "JemChannelMap::GetJemChannel: eta = " << inEta << " / " << etaPhiId.GetEta() << " phi = " << inPhi << " / " << etaPhiId.GetPhi() << "; etaPhiId: 0x" << etaPhiId.GetIdAsString() << " layer = " << inLayer.GetLayerAsString() << std::endl;
	   return;
   }
   
   *outChanList = itJemChan->second;
   
   
}

void JemChannelMap::SplitJemChannels(std::vector<L1CaloChannelId> inChanList,std::vector<unsigned int>* outCrate, std::vector<unsigned int>* outModule,std::vector<unsigned int>* outChannel){
   for(unsigned int i=0;i<inChanList.size();i++){
      outCrate->push_back(inChanList[i].GetCrate());
      outModule->push_back(inChanList[i].GetModule());
      outChannel->push_back(inChanList[i].GetChannel());
   }
}

void JemChannelMap::SetEtaPhi(float inEta, float inPhi, CaloLayer inLayer){
   if( !(MIN_ETA < inEta && inEta < MAX_ETA) && !FloatIsEqualTo(inEta,MIN_ETA)){
      std::cerr << "JemChannelMap::SetEtaPhi: Eta value, " << inEta << ", is out of range: " << MIN_ETA << " to " << MAX_ETA << "\n";
      return;
   }
   if( !(MIN_PHI < inPhi && inPhi < MAX_PHI) && !FloatIsEqualTo(inPhi,MIN_PHI)){
      std::cerr << "JemChannelMap::SetEtaPhi: Phi value, " << inPhi << ", is out of range: " << MIN_PHI << " to " << MAX_PHI << "\n";
      return;
   }
   if( !inLayer.IsSet() ){
      std::cerr << "JemChannelMap::SetEtaPhi: CaloLayer value, " << inLayer.GetLayerAsString() << ", must be EM or HAD\n";
      return;
   }
   
   ClearJem();
   
   EtaPhiId etaPhiId(inEta,inPhi,inLayer);
   
   m_currentEta = etaPhiId.GetIntegerEta();
   m_currentPhi = etaPhiId.GetIntegerPhi();
   m_currentLayer = inLayer;
   
   m_currentEtaPhiId.SetEtaPhi(m_currentEta,m_currentPhi,m_currentLayer);
   
   GetJemChannel(m_currentEta,m_currentPhi,m_currentLayer,&m_vect_currentChannelId);
   if(m_vect_currentChannelId.size() <= 0){
      std::cerr << "JemChannelMap::SetEtaPhi: Error in GetJemChannel.\n";
      return;
   }
   
   SplitJemChannels(m_vect_currentChannelId,&m_vect_currentCrate,&m_vect_currentModule,&m_vect_currentChannel);
   
   L1CaloChannelId jemId(L1CaloChannelId::JEM,m_vect_currentCrate[0],m_vect_currentModule[0],0,m_vect_currentChannel[0]);
   
   m_currentDeltaEta = m_map_jem_deltaEta[jemId.GetId()];
   m_currentDeltaPhi = m_map_jem_deltaPhi[jemId.GetId()];
   
   m_currentDeltaId.SetEtaPhi(m_currentDeltaEta,m_currentDeltaPhi,m_currentLayer);
}

void JemChannelMap::SetChannelId(L1CaloChannelId id){
	SetChannel(id.GetCrate(),id.GetModule(),id.GetChannel());
}

void JemChannelMap::SetChannel(unsigned int inCrate, unsigned int inModule, unsigned int inChannel){
   
   if( !(MIN_CRATE <= inCrate && inCrate <= MAX_CRATE) ){
      std::cerr << "JemChannelMap::SetChannel: Crate number must not correct range: " << MIN_CRATE << " to " << MAX_CRATE << std::endl;
      return;
   }
   if( !(MIN_MODULE <= inModule && inModule <= MAX_MODULE) ){
      std::cerr << "JemChannelMap::SetChannel: JEM number must not correct range: " << MIN_MODULE << " to " << MAX_MODULE << std::endl;
      return;
   }
   if( !(MIN_CHANNEL <= inChannel && inChannel <= MAX_CHANNEL) ){
      std::cerr << "JemChannelMap::SetChannel: Channel number must not correct range: " << MIN_CHANNEL << " to " << MAX_CHANNEL << std::endl;
      return;
   }
   
   
   ClearJem();
   
   m_vect_currentCrate.push_back(inCrate);
   m_vect_currentModule.push_back(inModule);
   m_vect_currentChannel.push_back(inChannel);
   
   GetJemEtaPhi(m_vect_currentCrate[0],m_vect_currentModule[0],m_vect_currentChannel[0],m_currentEta,m_currentPhi,m_currentLayer);
   
   m_currentEtaPhiId.SetEtaPhi(m_currentEta,m_currentPhi,m_currentLayer);
   
   L1CaloChannelId jemId(L1CaloChannelId::JEM,m_vect_currentCrate[0],m_vect_currentModule[0],0,m_vect_currentChannel[0]);
   
   m_vect_currentChannelId.push_back(jemId);
   
   m_currentDeltaEta = m_map_jem_deltaEta[jemId.GetId()];
   m_currentDeltaPhi = m_map_jem_deltaPhi[jemId.GetId()];
   
   m_currentDeltaId.SetEtaPhi(m_currentDeltaEta,m_currentDeltaPhi,m_currentLayer);
}


// Compares a float to a float and returns true if
// they are approximately equal
bool JemChannelMap::FloatIsEqualTo(const float x, const float y){
   if(fabs(x-y) < 0.005){
      return true;
   }
   return false;
}

