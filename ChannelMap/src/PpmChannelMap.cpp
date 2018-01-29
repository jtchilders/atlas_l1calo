#include "PpmChannelMap.h"

const float        PpmChannelMap::myPI          = 3.14159265;
const float        PpmChannelMap::MAX_ETA       = 4.9;
const float        PpmChannelMap::MIN_ETA       = -4.9;
const float        PpmChannelMap::MAX_PHI       = 2.0*myPI;
const float        PpmChannelMap::MIN_PHI       = 0.0;


PpmChannelMap::PpmChannelMap(void){

	// Initialize variables
	ClearPpm();
	
	FillEtaPhi();
}

PpmChannelMap::~PpmChannelMap(void){
	
}

void PpmChannelMap::ClearPpm(void){
   
	m_currentEta = 999;
	m_currentDeltaEta = 999;
	m_currentPhi = 999;
	m_currentDeltaPhi = 999;
   
   m_currentEtaPhiId.Clear();
   m_currentDeltaId.Clear();
	
	m_currentLayer.SetCaloLayer(CaloLayer::LAYER_NOT_SET);
	m_currentFcalLayer.clear();
	
	m_vect_currentCrate.clear();
	m_vect_currentModule.clear();
	m_vect_currentSubmodule.clear();
	m_vect_currentChannel.clear();
	
	m_vect_currentChannelId.clear();
	
	m_vect_isModifiedEtaAvailable.clear();
	
   
   m_currentChannelIsUsed = true;
}

void PpmChannelMap::FillEtaPhi(void){
	
	for(unsigned int crate = 0;crate < MAX_CRATE;crate++){
      for(unsigned int module = 0;module < MAX_MODULE;module++){
         for(unsigned int submodule = 0;submodule < MAX_SUBMODULE;submodule++){
            for(unsigned int channel = 0;channel < MAX_CHANNEL;channel++){
					
					L1CaloChannelId id(L1CaloChannelId::PPM,crate,module,submodule,channel);
					
					//std::cerr << crate << "\t" << module << "\t" << submodule << "\t" << channel << "\t: 0x" << hex << ppmID << dec << std::endl;
					
					if(crate == 0 || crate == 1 || crate == 6 || crate == 7){
						
						// Calculate the offsets due to each successively smaller piece of the system
						// Calculated with respect to the bottom right corner of each channel/module/crate
						
						// PPM Crate all have a phi offset of 0
						// the Eta has an offset of -1.6 for Crates 1 and 7
						unsigned int crateEta = 49;
						unsigned int cratePhi = 0;
						
						if(crate == 1 || crate == 7)
							crateEta = -16 + 49;
						
						// For the PPMs the are counted from left to right, in layers of 4 (for crates 0,1,6,7)
						unsigned int ppmEta = (module-((int)(module/4))*4)*4;
						unsigned int ppmPhi = ((int)(module/4))*16;
						
						unsigned int mcmEta;
						if( (submodule - ((int)(submodule/4))*4) == 0 || (submodule - ((int)(submodule/4))*4) == 3)
							mcmEta = 0;
						else
							mcmEta = 2;
						unsigned int mcmPhi = ((int)(submodule/2))*2;
						
						unsigned int chanEta;
						if( (channel - ((int)(channel/4))*4) == 0 || (channel - ((int)(channel/4))*4) == 1)
							chanEta = 0;
						else
							chanEta = 1;
						unsigned int chanPhi;
						if( channel == 0 || channel == 2)
							chanPhi = 0;
						else
							chanPhi = 1;
						
						m_map_tt_eta[id.GetId()] = crateEta + ppmEta + mcmEta + chanEta;
						m_map_tt_phi[id.GetId()] = cratePhi + ppmPhi + mcmPhi + chanPhi;
						
                  m_map_channelId_usedChannel[id.GetId()] = true;
                  
						m_map_tt_deltaEta[id.GetId()] = 1;
						m_map_tt_deltaPhi[id.GetId()] = 1;
						
						if(crate == 6 || crate == 7){
                     CaloLayer layer(CaloLayer::HAD);
							m_map_tt_layer[id.GetId()] = layer;
							EtaPhiId etaPhiID(crateEta + ppmEta + mcmEta + chanEta,
											cratePhi + ppmPhi + mcmPhi + chanPhi, layer);
							m_map_etaPhi_channelId[etaPhiID.GetId()].push_back(id);
						}
						else{
                     CaloLayer layer(CaloLayer::EM);
							m_map_tt_layer[id.GetId()] = layer;
							EtaPhiId etaPhiID(crateEta + ppmEta + mcmEta + chanEta,
											cratePhi + ppmPhi + mcmPhi + chanPhi, layer);
							m_map_etaPhi_channelId[etaPhiID.GetId()].push_back(id);
						}
						
						//std::cerr << "     " << m_map_tt_eta[ppmID] << ":" << m_map_tt_phi[ppmID] << std::endl;
						
					} // end if crate 0,1,6,7
					else if((crate == 2 && (module != 8 && module != 0)) || (crate == 4 && (module != 8 && module != 0))){
						
						// crate offsets
						unsigned int crateEta = 16 + 49;
						unsigned int cratePhi = 0;
						
						// ppm offsets
						unsigned int ppmEta;
						unsigned int ppmPhi;
						if(module == 4 || module == 12){
							ppmEta = 13;
							ppmPhi = module == 4 ? 0 : 32;
						}
						else{
							ppmEta = ((module - ((int)(module/4))*4)-1)*(4);
							ppmPhi = ((int)(module/4))*16;
						}
						
						unsigned int mcmEta;
						unsigned int mcmPhi;
						if(module == 4 || module == 12){
							mcmEta = 0;
							mcmPhi = submodule*2;
						}
						else{
							if(module == 3 || module == 7 || module == 11 || module == 15){
								if((submodule - ((int)(submodule/4))*4) == 0 || (submodule - ((int)(submodule/4))*4) == 3)
									mcmEta = 0;
								else
									mcmEta = 3;
							}
							else{
								if( (submodule - ((int)(submodule/4))*4) == 0 || (submodule - ((int)(submodule/4))*4) == 3)
									mcmEta = 0;
								else
									mcmEta = 2;
							}
							
							mcmPhi = ((int)(submodule/2))*2;
						}
						
						
						unsigned int chanEta = 0;
						unsigned int chanPhi = 0;
						if( module == 4 || module == 12){
							
							if((channel - ((int)(channel/4))*4) == 0){
								chanEta = 0;
								chanPhi = 0;
								
								m_map_tt_deltaEta[id.GetId()] = 2;
								m_map_tt_deltaPhi[id.GetId()] = 2;
							}
							else if((channel - ((int)(channel/4))*4) == 2){
								chanEta = 2;
								chanPhi = 0;
								
								m_map_tt_deltaEta[id.GetId()] = 1;
								m_map_tt_deltaPhi[id.GetId()] = 2;
								
							}
							// channels 1 and 3 are not used
							else{
                        m_map_channelId_usedChannel[id.GetId()] = false;
                        continue;
                     }
							
						}
						else if(module == 3 || module == 7 || module == 11 || module == 15){
							if((submodule - ((int)(submodule/4))*4) == 0 || (submodule - ((int)(submodule/4))*4) == 3){
								if((channel - ((int)(channel/4))*4) == 0 || (channel - ((int)(channel/4))*4) == 1){
									chanEta = 0;
									
									m_map_tt_deltaEta[id.GetId()] = 1;
									m_map_tt_deltaPhi[id.GetId()] = 1;
									
								}
								else if((channel - ((int)(channel/4))*4) == 2){
									chanEta = 1;
									
									m_map_tt_deltaEta[id.GetId()] = 2;
									m_map_tt_deltaPhi[id.GetId()] = 2;
									
								}
								// channel 3 is not used
								else {
                           m_map_channelId_usedChannel[id.GetId()] = false;
                           continue;
                        }
								
								if((channel - ((int)(channel/4))*4) == 0 || (channel - ((int)(channel/4))*4) == 2)
									chanPhi = 0;
								else if((channel - ((int)(channel/4))*4) == 1)
									chanPhi = 1;
								// channel 3 is not used
								else {
                           m_map_channelId_usedChannel[id.GetId()] = false;
                           continue;
                        }
							}
							else if((submodule - ((int)(submodule/4))*4) == 1 || (submodule - ((int)(submodule/4))*4) == 2){
								
								m_map_tt_deltaEta[id.GetId()] = 2;
								m_map_tt_deltaPhi[id.GetId()] = 2;
								
								if((channel - ((int)(channel/4))*4) == 0){
									chanEta = 0;
									chanPhi = 0;
								}
								// only channel 0 used
								else {
                           m_map_channelId_usedChannel[id.GetId()] = false;
                           continue;
                        }
							}
							
						}
						else {
							if( (channel - ((int)(channel/4))*4) == 0 || (channel - ((int)(channel/4))*4) == 1)
								chanEta = 0;
							else
								chanEta = 1;
							
							if((channel - ((int)(channel/4))*4) == 0 || (channel - ((int)(channel/4))*4) == 2)
								chanPhi = 0;
							else
								chanPhi = 1;
							
							m_map_tt_deltaEta[id.GetId()] = 1;
							m_map_tt_deltaPhi[id.GetId()] = 1;
							
							
						}
						
						m_map_tt_eta[id.GetId()] = crateEta + ppmEta + mcmEta + chanEta;
						m_map_tt_phi[id.GetId()] = cratePhi + ppmPhi + mcmPhi + chanPhi;
						
                  m_map_channelId_usedChannel[id.GetId()] = true;
                  
						if(crate == 2){
                     CaloLayer layer(CaloLayer::EM);
							m_map_tt_layer[id.GetId()] = layer;
							
							EtaPhiId etaPhiID(crateEta + ppmEta + mcmEta + chanEta,
											cratePhi + ppmPhi + mcmPhi + chanPhi, layer);
							m_map_etaPhi_channelId[etaPhiID.GetId()].push_back(id);
						}
						else{
                     CaloLayer layer(CaloLayer::HAD);
							m_map_tt_layer[id.GetId()] = layer;
							
							EtaPhiId etaPhiID(crateEta + ppmEta + mcmEta + chanEta,
											cratePhi + ppmPhi + mcmPhi + chanPhi, layer);
							m_map_etaPhi_channelId[etaPhiID.GetId()].push_back(id);
						}
					
					} // end if crate 2 or 4
					else if(crate == 4 && module == 0){
						
						unsigned int crateEta = 16 + 49;
						unsigned int cratePhi = 0;
						
						unsigned int ppmEta = 16;
						unsigned int ppmPhi = 0;
						
						unsigned int mcmEta = 0;
						unsigned int mcmPhi = submodule*4;
						
						unsigned int chanEta = 0;
						if(channel == 0)
							chanEta = 0;
						else if(channel == 1)
							chanEta = 12;
						else if(channel == 2)
							chanEta = 4;
						else if(channel == 3)
							chanEta = 8;
						
						unsigned int chanPhi = 0;
						
						m_map_tt_eta[id.GetId()] = crateEta + ppmEta + mcmEta + chanEta;
						m_map_tt_phi[id.GetId()] = cratePhi + ppmPhi + mcmPhi + chanPhi;
						
                  m_map_channelId_usedChannel[id.GetId()] = true;
                  
						if(channel == 1){
							
							m_map_tt_deltaEta[id.GetId()] = 5;
							m_map_tt_deltaPhi[id.GetId()] = 4;
							
						}
						else{
							
							m_map_tt_deltaEta[id.GetId()] = 4;
							m_map_tt_deltaPhi[id.GetId()] = 4;
							
						}
						
                  CaloLayer layer(CaloLayer::EM);
						m_map_tt_layer[id.GetId()] = layer;
						
						EtaPhiId etaPhiID(crateEta + ppmEta + mcmEta + chanEta,
										cratePhi + ppmPhi + mcmPhi + chanPhi, layer);
						m_map_etaPhi_channelId[etaPhiID.GetId()].push_back(id);
						
					} // end if crate 4
					else if(crate == 4 && module == 8){
						
						unsigned int crateEta = 16 + 49;
						unsigned int cratePhi = 0;
						
						unsigned int ppmEta = 16;
						unsigned int ppmPhi = 0;
						
						unsigned int mcmEta = 0;
						unsigned int mcmPhi = submodule*4;
						
						unsigned int chanEta = 0;
						if(channel == 0)
							chanEta = 0;
						else if(channel == 1)
							chanEta = 8;
						else if(channel == 2)
							chanEta = 0;
						else if(channel == 3)
							chanEta = 8;
						
						unsigned int chanPhi = 0;
						
						m_map_tt_eta[id.GetId()] = crateEta + ppmEta + mcmEta + chanEta;
						m_map_tt_phi[id.GetId()] = cratePhi + ppmPhi + mcmPhi + chanPhi;
						
                  m_map_channelId_usedChannel[id.GetId()] = true;
                  
						if(channel == 0 || channel == 2){
							
							m_map_tt_deltaEta[id.GetId()] = 8;
							m_map_tt_deltaPhi[id.GetId()] = 4;
							
						}
						else{
							
							m_map_tt_deltaEta[id.GetId()] = 9;
							m_map_tt_deltaPhi[id.GetId()] = 4;
							
						}
						
                  CaloLayer layer(CaloLayer::HAD);
						m_map_tt_layer[id.GetId()] = layer;
						
						EtaPhiId etaPhiID(crateEta + ppmEta + mcmEta + chanEta,
										cratePhi + ppmPhi + mcmPhi + chanPhi, layer);
						m_map_etaPhi_channelId[etaPhiID.GetId()].push_back(id);
						
					} // end if crate 4
					else if( (crate == 3 && (module != 8 && module != 0)) || (crate == 5 && (module != 8 && module != 0))){
						
						unsigned int crateEta = -32 + 49;
						unsigned int cratePhi = 0;
						
						unsigned int ppmEta = 0;
						unsigned int ppmPhi = 0;
						if(module == 4 || module == 12){
							ppmEta = 0;
							ppmPhi = (module == 4) ? 0 : 32;
						}
						else {
							if(module == 1 || module == 5 || module == 9 || module == 13)
								ppmEta = 3;
							else
								ppmEta = 8 + ((module - ((int)(module/4))*4)-2)*4;
							
							ppmPhi = ((int)(module/4))*16;
						}
						
						
						unsigned int mcmEta = 0;
						unsigned int mcmPhi = 0;
						if(module == 4 || module == 12){
							mcmEta = 0;
							mcmPhi = submodule*2;
						}
						else{
							
							if( (submodule - ((int)(submodule/4))*4) == 0 || (submodule - ((int)(submodule/4))*4) == 3)
								mcmEta = 0;
							else
								mcmEta = 2;
							
							mcmPhi = ((int)(submodule/2))*2;
						}
						 
						
						unsigned int chanEta = 0;
						unsigned int chanPhi = 0;
						if(module == 4 || module == 12){
							if((channel - ((int)(channel/4))*4) == 0){
								chanEta = 0;
								
								m_map_tt_deltaEta[id.GetId()] = 1;
								m_map_tt_deltaPhi[id.GetId()] = 2;
								
							}
							else if((channel - ((int)(channel/4))*4) == 2){
								chanEta = 1;
								
								m_map_tt_deltaEta[id.GetId()] = 2;
								m_map_tt_deltaPhi[id.GetId()] = 2;
								
							}
							// channels 1 and 3 are not used
							else {
                        m_map_channelId_usedChannel[id.GetId()] = false;
                        continue;
                     }
							if((channel - ((int)(channel/4))*4) == 0 || (channel - ((int)(channel/4))*4) == 2)
								chanPhi = 0;
							// channels 1 and 3 are not used
							else {
                        m_map_channelId_usedChannel[id.GetId()] = false;
                        continue;
                     }
							
						}
						else if(module == 1 || module == 5 || module == 9 || module == 13){
							if((submodule - ((int)(submodule/4))*4) == 1 || (submodule - ((int)(submodule/4))*4) == 2){
								if(channel == 0){
									chanEta = 0;
									
									m_map_tt_deltaEta[id.GetId()] = 2;
									m_map_tt_deltaPhi[id.GetId()] = 2;
									
								}
								else if(channel == 2 || channel == 3){
									chanEta = 2;
									
									m_map_tt_deltaEta[id.GetId()] = 1;
									m_map_tt_deltaPhi[id.GetId()] = 1;
									
								}
								// channel 1 is not used
								else {
                           m_map_channelId_usedChannel[id.GetId()] = false;
                           continue;
                        }
								
								if(channel == 0 || channel == 2)
									chanPhi = 0;
								else if( channel  == 3)
									chanPhi = 1;
								// channel 1 is not used
								else {
                           m_map_channelId_usedChannel[id.GetId()] = false;
                           continue;
                        }
							}
							else if((submodule - ((int)(submodule/4))*4) == 0 || (submodule - ((int)(submodule/4))*4) == 3){
								if(channel == 0){
									chanEta = 0;
									chanPhi = 0;
									
									m_map_tt_deltaEta[id.GetId()] = 2;
									m_map_tt_deltaPhi[id.GetId()] = 2;
									
								}
								// only channel 0 is used here
								else {
                           m_map_channelId_usedChannel[id.GetId()] = false;
                           continue;
                        }
							}
							
						}
						else{
							if( channel  == 0 || channel == 1)
								chanEta = 0;
							else
								chanEta = 1;
							
							if( channel  == 0 || channel == 2)
								chanPhi = 0;
							else
								chanPhi = 1;
							
							m_map_tt_deltaEta[id.GetId()] = 1;
							m_map_tt_deltaPhi[id.GetId()] = 1;
							
							
						}
						
						m_map_tt_eta[id.GetId()] = crateEta + ppmEta + mcmEta + chanEta;
						m_map_tt_phi[id.GetId()] = cratePhi + ppmPhi + mcmPhi + chanPhi;
						
                  m_map_channelId_usedChannel[id.GetId()] = true;
                  
						
						if(crate == 3){
                     CaloLayer layer(CaloLayer::EM);
							m_map_tt_layer[id.GetId()] = layer;
							
							EtaPhiId etaPhiID(crateEta + ppmEta + mcmEta + chanEta,
											cratePhi + ppmPhi + mcmPhi + chanPhi, layer);
							m_map_etaPhi_channelId[etaPhiID.GetId()].push_back(id);
						}
						else{
                     CaloLayer layer(CaloLayer::HAD);
							m_map_tt_layer[id.GetId()] = layer;
							
							EtaPhiId etaPhiID(crateEta + ppmEta + mcmEta + chanEta,
											cratePhi + ppmPhi + mcmPhi + chanPhi, layer);
							m_map_etaPhi_channelId[etaPhiID.GetId()].push_back(id);
						}
					} // end if crate 3 or 5
					else if(crate == 5 && module == 0){
						
						unsigned int crateEta = -49 + 49;
						unsigned int cratePhi = 0;
						
						unsigned int ppmEta = 0;
						unsigned int ppmPhi = 0;
						
						unsigned int mcmEta = 0;
						unsigned int mcmPhi = submodule*4;
						
						unsigned int chanEta = 0;
						if(channel == 0)
							chanEta = 0;
						else if(channel == 1)
							chanEta = 13;
						else if(channel == 2)
							chanEta = 5;
						else if(channel == 3)
							chanEta = 9;
						
						unsigned int chanPhi = 0;
						
						m_map_tt_eta[id.GetId()] = crateEta + ppmEta + mcmEta + chanEta;
						m_map_tt_phi[id.GetId()] = cratePhi + ppmPhi + mcmPhi + chanPhi;
						
                  m_map_channelId_usedChannel[id.GetId()] = true;
                  
						if(channel == 0){
							
							m_map_tt_deltaEta[id.GetId()] = 5;
							m_map_tt_deltaPhi[id.GetId()] = 4;
							
						}
						else{
							
							m_map_tt_deltaEta[id.GetId()] = 4;
							m_map_tt_deltaPhi[id.GetId()] = 4;
							
						}
						
                  CaloLayer layer(CaloLayer::EM);
						m_map_tt_layer[id.GetId()] = layer;
						
						EtaPhiId etaPhiID(crateEta + ppmEta + mcmEta + chanEta,
										cratePhi + ppmPhi + mcmPhi + chanPhi, layer);
						m_map_etaPhi_channelId[etaPhiID.GetId()].push_back(id);
						
					} // end if crate 5
					else if(crate == 5 && module == 8){
						
						unsigned int crateEta = -49 + 49;
						unsigned int cratePhi = 0;
						
						unsigned int ppmEta = 0;
						unsigned int ppmPhi = 0;
						
						unsigned int mcmEta = 0;
						unsigned int mcmPhi = submodule*4;
						
						unsigned int chanEta = 0;
						if(channel == 0)
							chanEta = 0;
						else if(channel == 1)
							chanEta = 9;
						else if(channel == 2)
							chanEta = 0;
						else if(channel == 3)
							chanEta = 9;
						
						unsigned int chanPhi = 0;
						
						m_map_tt_eta[id.GetId()] = crateEta + ppmEta + mcmEta + chanEta;
						m_map_tt_phi[id.GetId()] = cratePhi + ppmPhi + mcmPhi + chanPhi;
						
                  m_map_channelId_usedChannel[id.GetId()] = true;
                  
						if(channel == 0 || channel == 2){
							
							m_map_tt_deltaEta[id.GetId()] = 9;
							m_map_tt_deltaPhi[id.GetId()] = 4;
							
						}
						else{
							
							m_map_tt_deltaEta[id.GetId()] = 8;
							m_map_tt_deltaPhi[id.GetId()] = 4;
							
						}
						
                  CaloLayer layer(CaloLayer::HAD);
						m_map_tt_layer[id.GetId()] = layer;
						
						EtaPhiId etaPhiID(crateEta + ppmEta + mcmEta + chanEta,
										cratePhi + ppmPhi + mcmPhi + chanPhi, layer);
						m_map_etaPhi_channelId[etaPhiID.GetId()].push_back(id);
					} // end if crate 5
					else{
                  m_map_channelId_usedChannel[id.GetId()] = false;
               }
				} // end for(channel)
				
			} // end for(submodule)
			
		} // end for(module)
		
	} // end for(crate)
	//cin.get();
}

// Given an Eta/Phi/Layer a list of the channel ids associated with this coordinate are added to outChanList
void PpmChannelMap::GetPpmChannel(unsigned int inEta,unsigned int inPhi,CaloLayer inLayer,std::vector<L1CaloChannelId>* outChanList){
	
	if(!inLayer.IsSet()){
		std::cerr << "PpmChannelMap::GetPpmChannel: CaloLayer value, " << inLayer.GetLayerAsString() << ", must be 'EM' or 'HAD'\n";
		return;
	}
	if( !(inEta < MAX_UINT_ETA)){
		std::cerr << "PpmChannelMap::GetPpmChannel: Eta value, " << inEta << ", is out of range: 0 to " << MAX_UINT_ETA << "\n";
		return;
	}
	if( !(inPhi < MAX_UINT_PHI)){
		std::cerr << "PpmChannelMap::GetPpmChannel: Phi value, " << inPhi << ", is out of range: 0 to " << MAX_UINT_PHI << "\n";
		return;
	}
	
	EtaPhiId etaPhiID(inEta,inPhi,inLayer);
	std::map<unsigned int,std::vector<L1CaloChannelId> >::iterator  itPpmChan = m_map_etaPhi_channelId.find(etaPhiID.GetId());
	if(itPpmChan == m_map_etaPhi_channelId.end()){
		std::cerr << "PpmChannelMap::GetPpmChannel: eta/phi ID not found.\n";
		std::cerr << "PpmChannelMap::GetPpmChannel: eta/phi = " << inEta << "/" << inPhi << "; layer = " << inLayer.GetLayerAsString() << std::endl;
		return;
	}
	
	*outChanList = itPpmChan->second;
	
}

// Given an Eta+/-deltaEta and Phi+/-deltaPhi and layer, the outChanList is filled will all PPM Channel IDs that
// fall in this range.
void PpmChannelMap::GetPpmChannels(unsigned int inEta,unsigned int inDeltaEta,unsigned int inPhi,
	unsigned int inDeltaPhi,CaloLayer inLayer,std::vector<L1CaloChannelId>* outChanList){
	
	if(!inLayer.IsSet()){
		std::cerr << "PpmChannelMap::GetPpmChannel: CaloLayer value, " << inLayer.GetLayerAsString() << ", must be 'EM' or 'HAD'\n";
		return;
	}
	if( !(inEta < MAX_UINT_ETA)){
		std::cerr << "PpmChannelMap::GetPpmChannel: Eta value, " << inEta << ", is out of range: 0 to " << MAX_UINT_ETA << "\n";
		return;
	}
	if( !(inPhi < MAX_UINT_PHI)){
		std::cerr << "PpmChannelMap::GetPpmChannel: Phi value, " << inPhi << ", is out of range: 0 to " << MAX_UINT_PHI << "\n";
		return;
	}
	
	unsigned int etaMin = inEta;
	unsigned int etaMax = inEta + inDeltaEta;
	unsigned int phiMin = inPhi;
	unsigned int phiMax = inPhi + inDeltaPhi;
	
	unsigned int tempEta,tempPhi;
	bool repeat;
	std::map<unsigned int,std::vector<L1CaloChannelId> >::iterator itPpmChan;
	for(unsigned int x=etaMin;x<etaMax;x++){
		
		for(unsigned int y=phiMin;y<phiMax;y++){
         
         EtaPhiId etaPhiId(x,y,inLayer);
         tempEta = etaPhiId.GetIntegerTriggerTowerEta();
			tempPhi = etaPhiId.GetIntegerTriggerTowerPhi();
			
			itPpmChan = m_map_etaPhi_channelId.find(etaPhiId.GetId());
			if(itPpmChan == m_map_etaPhi_channelId.end()){
				std::cerr << "PpmChannelMap::GetPpmChannels: etaPhiID not found.\n";
            std::cerr << "PpmChannelMap::GetPpmChannels: eta/phi = " << etaPhiId.GetEta() << "/" << etaPhiId.GetPhi() << "; layer = " << inLayer.GetLayerAsString() << std::endl;
				continue;
			}
			
			
			repeat = false;
			for(unsigned int i=0;i< outChanList->size();i++){
				for(unsigned int j=0;j<itPpmChan->second.size();j++){
					if(outChanList->at(i).GetId() == itPpmChan->second[j].GetId()){
						repeat = true;
						break;
					}
				}
				if(repeat) break;
			}
			if(repeat) continue;
			
			for(unsigned int i=0;i<itPpmChan->second.size();i++){
				outChanList->push_back(itPpmChan->second[i]);
			}
		}
	}
	
}

// takes a vector of channel ids and places them in vectors of crate/mod/submod/channel 
void PpmChannelMap::SplitPpmChannels(std::vector<L1CaloChannelId> inChanList,std::vector<unsigned int>* outCrate,std::vector<unsigned int>* outPpm,
	std::vector<unsigned int>* outMcm,std::vector<unsigned int>* outChan){
	
	if(inChanList.size() <= 0){
		std::cerr << "PpmChannelMap::SplitPpmChannels: Channel list has no entries.\n";
		return;
	}
	
	for(unsigned int i=0;i<inChanList.size();i++){
		outCrate->push_back(inChanList[i].GetCrate());
		outPpm->push_back(inChanList[i].GetModule());
		outMcm->push_back(inChanList[i].GetSubmodule());
		outChan->push_back(inChanList[i].GetChannel());
	}
}

// Given a hardware address this fills the appropriate eta/phi/layer coordinate.
void PpmChannelMap::GetPpmEtaPhi(unsigned int inCrate,unsigned int inPpm,unsigned int inMcm,
	unsigned int inChan,unsigned int& outEta,unsigned int& outPhi,CaloLayer& outLayer){
	
	if( !(inCrate < MAX_CRATE)){
		std::cerr << "PpmChannelMap::GetEtaPhi: Crate number " << inCrate << " is not in correct range: 0 to " << (MAX_CRATE-1) << std::endl;
		return;
	}
	if( !(inPpm < MAX_MODULE) ){
		std::cerr << "PpmChannelMap::GetEtaPhi: PPM number " << inPpm << " is not in correct range: 0 to " << (MAX_MODULE-1) << std::endl;
		return;
	}
	if( !(inMcm < MAX_SUBMODULE) ){
		std::cerr << "PpmChannelMap::GetEtaPhi: MCM number " << inMcm << "is not in correct range: 0 to " << (MAX_SUBMODULE-1) << std::endl;
		return;
	}
	if( !(inChan < MAX_CHANNEL) ){
		std::cerr << "PpmChannelMap::GetEtaPhi: Channel number " << inChan << " is not in correct range: 0 to " << (MAX_CHANNEL-1) << std::endl;
		return;
	}
	
	L1CaloChannelId id(L1CaloChannelId::PPM,inCrate,inPpm,inMcm,inChan);
	
	outEta = m_map_tt_eta[id.GetId()];
	outPhi = m_map_tt_phi[id.GetId()];
	outLayer = m_map_tt_layer[id.GetId()];
}

// Set the channel using L1CaloChannelId
void PpmChannelMap::SetChannelID(L1CaloChannelId id){
	SetChannel(id.GetCrate(),id.GetModule(),id.GetSubmodule(),id.GetChannel());
}

// Given a crate/module/submodule/channel the eta/phi/layer are set
void PpmChannelMap::SetChannel(unsigned int inCrate,unsigned int inPpm,unsigned int inMcm,unsigned int inChan){
	
	if( !(inCrate < MAX_CRATE)){
		std::cerr << "PpmChannelMap::SetChannel: Crate number " << inCrate << " is not in correct range: " << MIN_CRATE << " to " << (MAX_CRATE-1) << std::endl;
		return;
	}
	if( !(inPpm < MAX_MODULE) ){
		std::cerr << "PpmChannelMap::SetChannel: PPM number " << inPpm << " is not in correct range: " << MIN_MODULE << " to " << (MAX_MODULE-1) << std::endl;
		return;
	}
	if( !(inMcm < MAX_SUBMODULE) ){
		std::cerr << "PpmChannelMap::SetChannel: MCM number " << inMcm << "is not in correct range: " << MIN_SUBMODULE << " to " << (MAX_SUBMODULE-1) << std::endl;
		return;
	}
	if( !(inChan < MAX_CHANNEL) ){
		std::cerr << "PpmChannelMap::SetChannel: Channel number " << inChan << " is not in correct range: " << MIN_CHANNEL << " to " << (MAX_CHANNEL-1) << std::endl;
		return;
	}
	ClearPpm();
	
	L1CaloChannelId id(L1CaloChannelId::PPM,inCrate,inPpm,inMcm,inChan);
	
   std::map<unsigned int,bool>::iterator chanToUsedItr;
   chanToUsedItr = m_map_channelId_usedChannel.find(id.GetId());
   if(chanToUsedItr == m_map_channelId_usedChannel.end()){
      std::cerr << "PpmChannelMap::SetChannel: Cool Id: 0x" << id.GetIdAsString() << " not found.\n";
      return;
   }
   else if(!chanToUsedItr->second){
      m_currentChannelIsUsed = false;
      return;
   }
   
   m_vect_currentCrate.push_back(inCrate);
   m_vect_currentModule.push_back(inPpm);
   m_vect_currentSubmodule.push_back(inMcm);
   m_vect_currentChannel.push_back(inChan);
   
	m_vect_currentChannelId.push_back(id);
	
	m_currentEta = m_map_tt_eta[id.GetId()];
	m_currentPhi = m_map_tt_phi[id.GetId()];
   
	m_currentDeltaEta = m_map_tt_deltaEta[id.GetId()];
	m_currentDeltaPhi = m_map_tt_deltaPhi[id.GetId()];
	
	m_currentLayer = m_map_tt_layer[id.GetId()];
	
   m_currentEtaPhiId.SetEtaPhi(m_currentEta,m_currentPhi,m_currentLayer);
   m_currentDeltaId.SetEtaPhi(m_currentDeltaEta,m_currentDeltaPhi,m_currentLayer);
   
	// Catch FCAL Layers
	if( ((m_vect_currentCrate[0] == 5 || m_vect_currentCrate[0] == 4) && m_vect_currentModule[0] == 8)){
		
		// FCAL2
		if(m_vect_currentChannel[0] == 0 || m_vect_currentChannel[0] == 3)
			m_currentFcalLayer.push_back(FcalLayer::FcalLayer(FcalLayer::FCAL2));
		
		// FCAL3
		else if(m_vect_currentChannel[0] == 1 || m_vect_currentChannel[0] == 2)
			m_currentFcalLayer.push_back(FcalLayer::FcalLayer(FcalLayer::FCAL3));
		
		m_vect_isModifiedEtaAvailable.push_back(true);
	}
	// FCAL1
	else if( ((m_vect_currentCrate[0] == 5 || m_vect_currentCrate[0] == 4) && m_vect_currentModule[0] == 0)){
		m_currentFcalLayer.push_back(FcalLayer::FcalLayer(FcalLayer::FCAL1));
		m_vect_isModifiedEtaAvailable.push_back(false);
	}
	// Not an FCAL Region
	else{
		m_currentFcalLayer.push_back(FcalLayer::FcalLayer(FcalLayer::LAYER_NOT_SET));
		m_vect_isModifiedEtaAvailable.push_back(false);
	}
	
}


////////////////////////////////////////////////////////////////////
/// FCAL is only set if SetChannel(s) functions are used
/// not if SetEtaPhi is used.
/// Returns the eta value or 999.9 if fails
/// The convention here is to put the FCAL2 at 3.2 and 3.6
/// and -3.6 and -4.0
/// then the FCAL3 at 4.0 and 4.4 and -4.4 and -4.9
////////////////////////////////////////////////////////////////////
float PpmChannelMap::GetModifiedEta(void){
	float eta = 999.9;
   FcalLayer layer = GetFcalLayer()->at(0);
   EtaPhiId etaPhiId(GetEta(),GetPhi(),CaloLayer::CaloLayer(CaloLayer::HAD));
	if(layer.GetFcalLayer() == FcalLayer::FCAL2){
		unsigned int iOutEta = 0;
		unsigned int iEta = etaPhiId.GetIntegerEta();
		if( iEta < -40 + 49 ){ // C side outer bin
			iOutEta = -40 + 49;
		}
		else if( -40 + 49 <= iEta && iEta < -32 + 49 ){ // C side inner bin
			iOutEta = -36 + 49;
		}
		else if( 32 + 49 <= iEta && iEta < 40 + 49 ){ // A side inner bin
			iOutEta = 32 + 49;
		}
		else if( 40 + 49 <= iEta && iEta < 49 + 49 ){ // A side outer bin
			iOutEta = 36 + 49;
		}
      EtaPhiId newId(iOutEta,etaPhiId.GetIntegerPhi(),CaloLayer::CaloLayer(CaloLayer::HAD));
		eta = newId.GetEta();
		return eta;
	}
	else if(layer.GetFcalLayer() == FcalLayer::FCAL3){
		unsigned int iOutEta = 0;
		unsigned int iEta = etaPhiId.GetIntegerEta();
		if( iEta < -40 + 49 ){ // C side outer bin
			iOutEta = -49 + 49;
		}
		else if( -40 + 49 <= iEta && iEta < -32 + 49 ){ // C side inner bin
			iOutEta = -44 + 49;
		}
		else if( 32 + 49 <= iEta && iEta < 40 + 49 ){ // A side inner bin
			iOutEta = 40 + 49;
		}
		else if( 40 + 49 <= iEta && iEta < 49 + 49 ){ // A side outer bin
			iOutEta = 44 + 49;
		}
		EtaPhiId newId(iOutEta,etaPhiId.GetIntegerPhi(),CaloLayer::CaloLayer(CaloLayer::HAD));
		eta = newId.GetEta();
		return eta;
	}
	
	return eta;
}

////////////////////////////////////////////////////////////////////
/// FCAL is only set if SetChannel(s) functions are used
///   not if SetEtaPhi is used.
/// Returns the integer eta value (0-98 in 0.1 eta units) 
///   or 999 if fails
/// The convention here is to put the FCAL2 at 3.2 and 3.6
///   and -3.6 and -4.0
///   then the FCAL3 at 4.0 and 4.4 and -4.4 and -4.9
////////////////////////////////////////////////////////////////////
unsigned int PpmChannelMap::GetModifiedIntegerEta(void){
   FcalLayer layer = GetFcalLayer()->at(0);
   EtaPhiId etaPhiId(GetEta(),GetPhi(),CaloLayer::CaloLayer(CaloLayer::HAD));
   if(layer.GetFcalLayer() == FcalLayer::FCAL2){
      unsigned int iOutEta = 0;
      unsigned int iEta = etaPhiId.GetIntegerEta();
      if( iEta < -40 + 49 ){ // C side outer bin
         iOutEta = -40 + 49;
      }
      else if( -40 + 49 <= iEta && iEta < -32 + 49 ){ // C side inner bin
         iOutEta = -36 + 49;
      }
      else if( 32 + 49 <= iEta && iEta < 40 + 49 ){ // A side inner bin
         iOutEta = 32 + 49;
      }
      else if( 40 + 49 <= iEta && iEta < 49 + 49 ){ // A side outer bin
         iOutEta = 36 + 49;
      }
      return iOutEta;
   }
   else if(layer.GetFcalLayer() == FcalLayer::FCAL3){
      unsigned int iOutEta = 0;
      unsigned int iEta = etaPhiId.GetIntegerEta();
      if( iEta < -40 + 49 ){ // C side outer bin
         iOutEta = -49 + 49;
      }
      else if( -40 + 49 <= iEta && iEta < -32 + 49 ){ // C side inner bin
         iOutEta = -44 + 49;
      }
      else if( 32 + 49 <= iEta && iEta < 40 + 49 ){ // A side inner bin
         iOutEta = 40 + 49;
      }
      else if( 40 + 49 <= iEta && iEta < 49 + 49 ){ // A side outer bin
         iOutEta = 44 + 49;
      }
      return iOutEta;
   }
   
   return 999;
}

/////////////////////////////////////////////////////
/// If you are in a hadronic FCAL region and want to
/// specify Eta using the modified way then use this
/// function. This means you moving FCAL2, originally
/// at -4.9, -4.0, 3.2, and 4.0, to -4.0, -3.6, 3.2,
/// and 3.6 respectively. And moving FCAL3, originally
/// at -4.9, -4.0, 3.2, and 4.0, to -4.9, -4.4, 4.0,
/// and 4.4 respectively. That way you can fit all 
/// FCAL regions for the hadronic layer on one plot.
////////////////////////////////////////////////////////
void PpmChannelMap::SetModifiedEtaPhi(float inEta, float inPhi,CaloLayer inLayer){
	
	if( !(MIN_ETA < inEta && inEta < MAX_ETA)){
		std::cerr << "PpmChannelMap::SetModifiedEtaPhi: Eta value, " << inEta << ", is out of range: " << MIN_ETA << " to " << MAX_ETA << "\n";
		return;
	}
	if( !(MIN_PHI < inPhi && inPhi < MAX_PHI)){
		std::cerr << "PpmChannelMap::SetModifiedEtaPhi: Phi value, " << inPhi << ", is out of range: " << MIN_PHI << " to " << MAX_PHI << "\n";
		return;
	}
	if( !inLayer.IsSet()){
		std::cerr << "PpmChannelMap::SetModifiedEtaPhi: Layer incorrect, " << inLayer.GetLayerAsString() << ", must be EM or HAD\n";
		return;
	}
	
	// Clear mappings
	ClearPpm();
	
	FcalLayer fcalLayer;
   EtaPhiId etaPhiId(inEta,inPhi,inLayer);
	unsigned int iEta = etaPhiId.GetIntegerEta();
	
	if(iEta < -44 + 49){ // outer FCAL3 C side
		m_currentEta = -49 + 49;
		fcalLayer.SetFcalLayer(FcalLayer::FCAL3);
	}
	else if(-44 + 49 <= iEta && iEta < -40 + 49){ // inner FCAL3 C side
		m_currentEta = -40 + 49;
		fcalLayer.SetFcalLayer(FcalLayer::FCAL3);
	}
	else if(-40 + 49 <= iEta && iEta < -36 + 49){ // outer FCAL2 C side
		m_currentEta = -49 + 49;
		fcalLayer.SetFcalLayer(FcalLayer::FCAL2);
	}
	else if(-36 + 49 <= iEta && iEta < -32 + 49){ // inner FCAL2 C side
		m_currentEta = -40 + 49;
		fcalLayer.SetFcalLayer(FcalLayer::FCAL2);
	}
	else if(32 + 49 <= iEta && iEta < 36 + 49){ // inner FCAL2 A side
		m_currentEta = 32 + 49;
		fcalLayer.SetFcalLayer(FcalLayer::FCAL2);
	}
	else if(36 + 49 <= iEta && iEta < 40 + 49){ // outer FCAL2 A side
		m_currentEta = 40 + 49;
		fcalLayer.SetFcalLayer(FcalLayer::FCAL2);
	}
	else if(40 + 49 <= iEta && iEta < 44 + 49){ // inner FCAL3 A side
		m_currentEta = 32 + 49;
		fcalLayer.SetFcalLayer(FcalLayer::FCAL3);
	}
	else if(44 + 49 <= iEta && iEta < 49 + 49){ // outer FCAL3 A side
		m_currentEta = 40 + 49;
		fcalLayer.SetFcalLayer(FcalLayer::FCAL3);
	}
	else{
      
		iEta = etaPhiId.GetIntegerTriggerTowerEta();
		m_currentEta = iEta;
		fcalLayer.SetFcalLayer(FcalLayer::LAYER_NOT_SET);
	}
	
	m_currentPhi = etaPhiId.GetIntegerTriggerTowerPhi();;
	m_currentLayer = inLayer;
	
   m_currentEtaPhiId.SetEtaPhi(m_currentEta,m_currentPhi,m_currentLayer);
   m_currentDeltaId.SetEtaPhi(m_currentDeltaEta,m_currentDeltaPhi,m_currentLayer);
   
	//std::cerr << "inEta: " << inEta << " eta: " << m_currentEta << " inPhi: " << inPhi << " phi: " << m_currentPhi << std::endl;
	
	// get the corresponding PPM Channel IDs for this integer eta/phi
	GetPpmChannel(m_currentEta,m_currentPhi,m_currentLayer,&m_vect_currentChannelId);
	if(m_vect_currentChannelId.size() == 0){
		std::cerr << "PpmChannelMap::SetModifiedEtaPhi: Error in GetPpmChannel()\n";
		std::cerr << "PpmChannelMap::SetModifiedEtaPhi: Passed Eta/Phi = " << inEta << "/" << inPhi << "; layer = " << inLayer.GetLayerAsString() << std::endl;
		std::cerr << "PpmChannelMap::SetModifiedEtaPhi: Integer Eta/Phi = " << m_currentEta << "/" << m_currentPhi << std::endl;
		return;
	}
	
	// split these into crate/ppm/mcm/channel information
	SplitPpmChannels(m_vect_currentChannelId,&m_vect_currentCrate,&m_vect_currentModule,&m_vect_currentSubmodule,&m_vect_currentChannel);
	
	L1CaloChannelId ppmId(L1CaloChannelId::PPM,m_vect_currentCrate[0],m_vect_currentModule[0],m_vect_currentSubmodule[0],m_vect_currentChannel[0]);
	
	// extract one id to get the deltaEta
	m_currentDeltaEta = m_map_tt_deltaEta[ppmId.GetId()];
	m_currentDeltaPhi = m_map_tt_deltaPhi[ppmId.GetId()];
	
   m_currentDeltaId.SetEtaPhi(m_currentDeltaEta,m_currentDeltaPhi,m_currentLayer);
   
	// Set FCAL Layer
	for(unsigned int i=0;i<m_vect_currentChannelId.size();i++){
		if( ((m_vect_currentCrate[i] == 5 || m_vect_currentCrate[i] == 4) && m_vect_currentModule[i] == 8)){
		
			// FCAL2
			if(m_vect_currentChannel[i] == 0 || m_vect_currentChannel[i] == 3)
				m_currentFcalLayer.push_back(FcalLayer::FcalLayer(FcalLayer::FCAL2));
			
			// FCAL3
			else if(m_vect_currentChannel[i] == 1 || m_vect_currentChannel[i] == 2)
				m_currentFcalLayer.push_back(FcalLayer::FcalLayer(FcalLayer::FCAL3));
			
			m_vect_isModifiedEtaAvailable.push_back(true);
		}
		// FCAL1
		else if( ((m_vect_currentCrate[i] == 5 || m_vect_currentCrate[i] == 4) && m_vect_currentModule[i] == 0)){
			m_currentFcalLayer.push_back(FcalLayer::FcalLayer(FcalLayer::FCAL1));
			m_vect_isModifiedEtaAvailable.push_back(false);
		}
		// Not an FCAL Region
		else{
			m_currentFcalLayer.push_back(FcalLayer::FcalLayer(FcalLayer::LAYER_NOT_SET));
			m_vect_isModifiedEtaAvailable.push_back(false);
		}
	}
	
	// In the end we have the information to get a single channel so we
	// choose the channel from the channels returned which corresponds
	// the FCAL region that was initially returned;
	if(!fcalLayer.IsSet()){
		for(unsigned int i=0;i<m_currentFcalLayer.size();i++){
			if(fcalLayer.GetFcalLayer() == m_currentFcalLayer[i].GetFcalLayer()){
				SetChannel(m_vect_currentCrate[i],m_vect_currentModule[i],m_vect_currentSubmodule[i],m_vect_currentChannel[i]);
				return;
			}
		}
	}
	
}


void PpmChannelMap::SetEtaPhi(float inEta,float inPhi,CaloLayer inLayer){
   
   if( !(MIN_ETA < inEta && inEta < MAX_ETA) && !FloatIsEqualTo(inEta,MIN_ETA)){
	   std::cerr << "PpmChannelMap::SetModifiedEtaPhi: Eta value, " << inEta << ", is out of range: " << MIN_ETA << " to " << MAX_ETA << "\n";
	   return;
   }
   if( !(MIN_PHI < inPhi && inPhi < MAX_PHI) && !FloatIsEqualTo(inPhi,MIN_PHI)){
	   std::cerr << "PpmChannelMap::SetModifiedEtaPhi: Phi value, " << inPhi << ", is out of range: " << MIN_PHI << " to " << MAX_PHI << "\n";
	   return;
   }
   if( !inLayer.IsSet()){
	   std::cerr << "PpmChannelMap::SetModifiedEtaPhi: Layer incorrect, " << inLayer.GetLayerAsString() << ", must be EM or HAD\n";
	   return;
   }
   
   ClearPpm();
   
   
   
   EtaPhiId etaPhiId(inEta,inPhi,inLayer);
   
   m_currentEta = etaPhiId.GetIntegerTriggerTowerEta();
   m_currentPhi = etaPhiId.GetIntegerTriggerTowerPhi();
   m_currentLayer = inLayer;
   
   m_currentEtaPhiId.SetEtaPhi(m_currentEta,m_currentPhi,m_currentLayer);
   
   //std::cerr << "PpmChannelMap::SetEtaPhi: inEta: " << inEta << " eta: " << m_currentEta << " inPhi: " << inPhi << " phi: " << m_currentPhi << std::endl;
   
   GetPpmChannel(m_currentEta,m_currentPhi,m_currentLayer,&m_vect_currentChannelId);
   if(m_vect_currentChannelId.size() == 0){
	   std::cerr << "PpmChannelMap::SetEtaPhi: Error in GetPpmChannel()\n";
	   std::cerr << "PpmChannelMap::SetEtaPhi: Passed Eta/Phi = " << inEta << "/" << inPhi << "; layer = " << inLayer.GetLayerAsString() << std::endl;
	   std::cerr << "PpmChannelMap::SetEtaPhi: Integer Eta/Phi = " << m_currentEta << "/" << m_currentPhi << std::endl;
	   return;
   }
   
   SplitPpmChannels(m_vect_currentChannelId,&m_vect_currentCrate,&m_vect_currentModule,&m_vect_currentSubmodule,&m_vect_currentChannel);
   
   L1CaloChannelId ppmId(L1CaloChannelId::PPM,m_vect_currentCrate[0],m_vect_currentModule[0],m_vect_currentSubmodule[0],m_vect_currentChannel[0]);
   
   //std::cerr << hex << "0x" << ppmID << dec << std::endl;
   
   m_currentDeltaEta = m_map_tt_deltaEta[ppmId.GetId()];
   m_currentDeltaPhi = m_map_tt_deltaPhi[ppmId.GetId()];
   
   m_currentDeltaId.SetEtaPhi(m_currentDeltaEta,m_currentDeltaPhi,m_currentLayer);
   
   // Set FCAL Layer
   for(unsigned int i=0;i<m_vect_currentChannelId.size();i++){
	   if( ((m_vect_currentCrate[i] == 5 || m_vect_currentCrate[i] == 4) && m_vect_currentModule[i] == 8)){
	   
		   // FCAL2
		   if(m_vect_currentChannel[i] == 0 || m_vect_currentChannel[i] == 3)
			   m_currentFcalLayer.push_back(FcalLayer::FcalLayer(FcalLayer::FCAL2));
		   
		   // FCAL3
		   else if(m_vect_currentChannel[i] == 1 || m_vect_currentChannel[i] == 2)
			   m_currentFcalLayer.push_back(FcalLayer::FcalLayer(FcalLayer::FCAL3));
		   
		   m_vect_isModifiedEtaAvailable.push_back(true);
	   }
	   // FCAL1
	   else if( ((m_vect_currentCrate[i] == 5 || m_vect_currentCrate[i] == 4) && m_vect_currentModule[i] == 0)){
		   m_currentFcalLayer.push_back(FcalLayer::FcalLayer(FcalLayer::FCAL1));
		   m_vect_isModifiedEtaAvailable.push_back(false);
	   }
	   // Not an FCAL Region
	   else{
		   m_currentFcalLayer.push_back(FcalLayer::FcalLayer(FcalLayer::LAYER_NOT_SET));
		   m_vect_isModifiedEtaAvailable.push_back(false);
	   }
   }
   
   
   
   //std::cerr << m_currentEta << " " << m_currentPhi << " " << m_currentLayer << " " << m_vect_currentCrate << " " << m_vect_currentModule << std::endl;
}


void PpmChannelMap::SetEtaPhi(float inEta,float inDeltaEta,float inPhi,float inDeltaPhi,CaloLayer inLayer){
	
	
	if( !(MIN_ETA < inEta && (inEta+inDeltaEta) < MAX_ETA) && !FloatIsEqualTo(inEta,MIN_ETA) && !FloatIsEqualTo(inEta+inDeltaEta,MAX_ETA) ) {
		std::cerr << "PpmChannelMap::SetEtaPhi: Eta value, " << inEta << ", or (Eta+deltaEta) value, " << (inEta+inDeltaEta) << ", is out of range: " << MIN_ETA << " to " << MAX_ETA << "\n";
		return;
	}
	if( !(MIN_PHI < inPhi && (inPhi+inDeltaPhi) < MAX_PHI) && !FloatIsEqualTo(inPhi,MIN_PHI) && !FloatIsEqualTo(inPhi+inDeltaPhi,MAX_PHI) ) {
		std::cerr << "PpmChannelMap::SetEtaPhi: Phi value, " << inPhi << ", or (Eta+deltaEta) value, " << (inPhi+inDeltaPhi) << ", is out of range: " << MIN_PHI << " to " << MAX_PHI << "\n";
		return;
	}
	if(!inLayer.IsSet()){
		std::cerr << "PpmChannelMap::SetEtaPhi: Layer incorrect, " << inLayer.GetLayerAsString() << ", must be EM or HAD\n";
		return;
	}
	
	ClearPpm();
	
	//std::cerr << "PPM: " << inEta << "+/-" << inDeltaEta << "; " << inPhi << "+/-" << inDeltaPhi << std::endl;
	
   EtaPhiId etaPhiId(inEta,inPhi,inLayer);
   EtaPhiId deltaEtaPhiId(inDeltaEta,inDeltaPhi,inLayer);
   
	m_currentEta = etaPhiId.GetIntegerTriggerTowerEta();
	// need the -49 because conversion assumes integer eta starts at 0, which corresponds to real eta = -4.9
	m_currentDeltaEta = deltaEtaPhiId.GetIntegerEta() - 49;
	m_currentPhi = etaPhiId.GetIntegerTriggerTowerEta();
	m_currentDeltaPhi = deltaEtaPhiId.GetIntegerPhi();
	m_currentLayer = inLayer;
	//std::cerr << "PPM: " << m_currentEta << "+/-" << m_currentDeltaEta << "; " << m_currentPhi << "+/-" << m_currentDeltaPhi << std::endl;
	
   m_currentEtaPhiId.SetEtaPhi(m_currentEta,m_currentPhi,m_currentLayer);
   m_currentDeltaId.SetEtaPhi(m_currentDeltaEta,m_currentDeltaPhi,m_currentLayer);
   
	GetPpmChannels(m_currentEta,m_currentDeltaEta,m_currentPhi,m_currentDeltaPhi,m_currentLayer,&m_vect_currentChannelId);
	
	if(m_vect_currentChannelId.size() == 0){
		std::cerr << "PpmChannelMap::SetEtaPhi: Error in GetPpmChannel()\n";
		return;
	}
	
	SplitPpmChannels(m_vect_currentChannelId,&m_vect_currentCrate,&m_vect_currentModule,&m_vect_currentSubmodule,&m_vect_currentChannel);
	
	L1CaloChannelId ppmId(L1CaloChannelId::PPM,m_vect_currentCrate[0],m_vect_currentModule[0],m_vect_currentSubmodule[0],m_vect_currentChannel[0]);
	
	//std::cerr << hex << "0x" << ppmID << dec << std::endl;
	
	m_currentDeltaEta = m_map_tt_deltaEta[ppmId.GetId()];
	m_currentDeltaPhi = m_map_tt_deltaPhi[ppmId.GetId()];
	
   m_currentDeltaId.SetEtaPhi(m_currentDeltaEta,m_currentDeltaPhi,m_currentLayer);
   
	// Set FCAL Layer
	for(unsigned int i=0;i<m_vect_currentChannelId.size();i++){
		if( ((m_vect_currentCrate[i] == 5 || m_vect_currentCrate[i] == 4) && m_vect_currentModule[i] == 8)){
		
			// FCAL2
			if(m_vect_currentChannel[i] == 0 || m_vect_currentChannel[i] == 3)
				m_currentFcalLayer.push_back(FcalLayer::FcalLayer(FcalLayer::FCAL2));
			
			// FCAL3
			else if(m_vect_currentChannel[i] == 1 || m_vect_currentChannel[i] == 2)
				m_currentFcalLayer.push_back(FcalLayer::FcalLayer(FcalLayer::FCAL3));
			
			m_vect_isModifiedEtaAvailable.push_back(true);
			
		}
		// FCAL1
		else if( ((m_vect_currentCrate[i] == 5 || m_vect_currentCrate[i] == 4) && m_vect_currentModule[i] == 0)){
			m_currentFcalLayer.push_back(FcalLayer::FcalLayer(FcalLayer::FCAL1));
			m_vect_isModifiedEtaAvailable.push_back(false);
		}
		// Not FCAL Layer
		else{
			m_currentFcalLayer.push_back(FcalLayer::FcalLayer(FcalLayer::LAYER_NOT_SET));
			m_vect_isModifiedEtaAvailable.push_back(false);
		}
	}
	
}

// Compares a float to a float and returns true if
// they are approximately equal
bool PpmChannelMap::FloatIsEqualTo(const float x, const float y){
   if(fabs(x-y) < 0.005){
      return true;
   }
   return false;
}



