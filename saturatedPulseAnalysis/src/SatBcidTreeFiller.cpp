#include "SatBcidTreeFiller.h"

#include "CaloDivision.h"
#include "PixelMap.h"

SatBcidTreeFiller::SatBcidTreeFiller(SatBcidTree *tree):
   m_tree(tree)
{
   // get l1calo map
   m_l1map = new L1CaloChannelMap;
   m_l1map->SetPpmEnable(true);
   m_l1map->SetCpmEnable(false);
   m_l1map->SetJemEnable(false);
   
   m_isTile = false;
   m_isLAr = false;
   
}


void SatBcidTreeFiller::FillTree(void){
   
   if(m_tree->GetEntries() <= 0){
      std::cerr << "[SatBcidTreeFiller::FillTree] ERROR, no entries in tree.\n";
      return;
   }
   
   // make sure one of the tile or lar flags have been set
   if(!m_isTile && !m_isLAr){
      std::cerr << "[SatBcidTreeFiller::FillTree] ERROR, must set one of the isTile/isLAr flags.\n";
      return;
   }
   
   
   std::cout << " FillMeans\n";
   // Loop over tree once to get eta strip information
   FillMeans();
   
   std::cout << " FillHoles\n";
   // Fill in the holes
   FillHoles();
   
   std::cout << " FillPlots\n";
   // FIll PixelMaps
   FillPlots();
   
}


void SatBcidTreeFiller::FillMeans(void){
   
   for(unsigned int i=0;i<m_tree->GetEntries();++i){
      m_tree->GetEntry(i);
      
      // if this is not a valid channel it does not need to be set
      if(!m_tree->GetIsValid()) continue;
      
      /// Setup l1calo map
      m_l1map->SetPpmChannelID(m_tree->GetCoolId());
      L1CaloChannelId id(m_tree->GetCoolId());
      CaloDivision region = m_l1map->GetDetectorRegion();
      // determine if this is a tile or larg channel
      bool isTile = region.IsTile();
      bool isLAr = region.IsLAr();
      
      // if run is for Tile and this is not a Tile channel, then skip
      if(!isTile && m_isTile) continue;
      // if run is for LAr and this is not a LAr channel, then skip
      else if(!isLAr && m_isLAr) continue;
      
      // determine if this is an EM or HAD channel
      bool isEM = region.IsEM();
      bool isHAD = region.IsHAD();
      
      // if there is a zero value for satHigh/Low/Lvl record ID for later use
      if(m_tree->GetErrorCode() != 0 || OtherBadChannels(id)){
         m_emptyChannels.push_back(id);
         
         // fill maps of satHigh/Low/Lvl for later use
         m_map_etaPhiId_satHigh[id.GetId()] = 0;
         m_map_etaPhiId_satLow [id.GetId()] = 0;
         m_map_etaPhiId_satLvl [id.GetId()] = 0;
      }
      else{
         // fill maps of satHigh/Low/Lvl for later use
         if(BadLArFEB(id)){
            // set the bad FEBs such that the satBcid will always
            // identified the second saturated ADC slice as the peak
            // this ensure the satBcid will never cause an early trigger
            m_map_etaPhiId_satHigh[id.GetId()] = 1023;
            m_map_etaPhiId_satLow [id.GetId()] = 1023;
            m_map_etaPhiId_satLvl [id.GetId()] = 1020;
         }
         else{
            m_map_etaPhiId_satHigh[id.GetId()] = m_tree->GetSatHigh();
            m_map_etaPhiId_satLow [id.GetId()] = m_tree->GetSatLow();
            m_map_etaPhiId_satLvl [id.GetId()] = m_tree->GetSatLevel();
         }
      }
   }// end for(tree entry)
   
   
}

void SatBcidTreeFiller::FillHoles(void){
   
   
   for(unsigned int i=0;i<m_emptyChannels.size();++i){
      
      L1CaloChannelId id(m_emptyChannels[i]);
      m_l1map->SetPpmChannelID(id);
      float eta = m_l1map->GetEta();
      unsigned int iEta = m_l1map->GetIntegerEta();
      float phi = m_l1map->GetPhi();
      unsigned int iPhi = m_l1map->GetIntegerPhi();
      CaloLayer layer = m_l1map->GetLayer();
      CaloDivision region = m_l1map->GetDetectorRegion();
      
      EtaPhiId epId(eta,phi,layer);
      
      MeanValue satHigh,satLow,satLvl;
      
      // if the channel is in the 0.1
      if((region.IsLArEMBA() || region.IsLArEMBC()) && !BadLArFEB(id)){
         satHigh = GetCircleMean(id,m_map_etaPhiId_satHigh);
         satLow  = GetCircleMean(id,m_map_etaPhiId_satLow);
         satLvl  = GetCircleMean(id,m_map_etaPhiId_satLvl);
      }
      else if(region.IsLArFCAL1A() || region.IsLArFCAL1C()){
         satHigh = GetEtaMean(id,m_map_etaPhiId_satHigh);
         satLow  = GetEtaMean(id,m_map_etaPhiId_satLow);
         satLvl  = GetEtaMean(id,m_map_etaPhiId_satLvl);
      }
      else if(region.IsLArEMECA() || region.IsLArEMECC()){
         
         
         if( (49-25 <= iEta && iEta < 49-20) || (40+20 <= iEta && iEta < 49+25)){
            satHigh = GetEtaMean(id,m_map_etaPhiId_satHigh);
            satLow  = GetEtaMean(id,m_map_etaPhiId_satLow);
            satLvl  = GetEtaMean(id,m_map_etaPhiId_satLvl);
         }
         else if(49-25 > iEta || iEta >= 49+25){
            satHigh = GetEndcapMean(id,m_map_etaPhiId_satHigh);
            satLow  = GetEndcapMean(id,m_map_etaPhiId_satLow);
            satLvl  = GetEndcapMean(id,m_map_etaPhiId_satLvl);
         }
         
      }
      
      if(fabs(satHigh.GetMean()) > 0.0001)
         m_map_etaPhiId_satHigh[id.GetId()] = satHigh.GetIntegerMean();
      if(fabs(satLow.GetMean()) > 0.0001)
         m_map_etaPhiId_satLow[id.GetId()] = satLow.GetIntegerMean();
      if(fabs(satLvl.GetMean()) > 0.0001)
         m_map_etaPhiId_satLvl[id.GetId()] = satLvl.GetIntegerMean();
      
   }// end for(m_emptyChannels)
   
}

void SatBcidTreeFiller::FillPlots(void){
   
   PixelMap<unsigned int> em_satHigh(PixelMap<unsigned int>::TrigTower);
   PixelMap<unsigned int> had_satHigh(PixelMap<unsigned int>::TrigTower);
   
   PixelMap<unsigned int> em_satLow(PixelMap<unsigned int>::TrigTower);
   PixelMap<unsigned int> had_satLow(PixelMap<unsigned int>::TrigTower);
   
   PixelMap<unsigned int> em_satLvl(PixelMap<unsigned int>::TrigTower);
   PixelMap<unsigned int> had_satLvl(PixelMap<unsigned int>::TrigTower);
   
   typedef std::map<unsigned int,unsigned int>::iterator ITR;
   ITR itr = m_map_etaPhiId_satHigh.begin();
   ITR end = m_map_etaPhiId_satHigh.end();
   PixelMap<unsigned int> *em = &em_satHigh;
   PixelMap<unsigned int> *had = &had_satHigh;
   for(;itr != end;++itr){
      
      L1CaloChannelId id(itr->first);
      unsigned int satThresh = itr->second;
      
      m_l1map->SetPpmChannelID(id);
      CaloDivision region = m_l1map->GetDetectorRegion();
      
      if(m_l1map->GetLayer().IsEM()){
         em->SetTriggerTower(m_l1map->GetEta(),m_l1map->GetPhi(),satThresh);
      }
      else if(m_l1map->GetLayer().IsHAD()){
         // pick out FCAL layer for HAD so they are plotted correctly.
         if(region.IsLArFCAL23A() || region.IsLArFCAL23C()){
            had->SetTriggerTower(m_l1map->GetEta(),m_l1map->GetPhi(),satThresh,m_l1map->GetPpmFcalLayer()->at(0));
         }
         else{
            had->SetTriggerTower(m_l1map->GetEta(),m_l1map->GetPhi(),satThresh);
         }
      }
   }
   
   itr = m_map_etaPhiId_satLow.begin();
   end = m_map_etaPhiId_satLow.end();
   em = &em_satLow;
   had = &had_satLow;
   for(;itr != end;++itr){
      
      L1CaloChannelId id(itr->first);
      unsigned int satThresh = itr->second;
      
      m_l1map->SetPpmChannelID(id);
      CaloDivision region = m_l1map->GetDetectorRegion();
      
      if(m_l1map->GetLayer().IsEM()){
         em->SetTriggerTower(m_l1map->GetEta(),m_l1map->GetPhi(),satThresh);
      }
      else if(m_l1map->GetLayer().IsHAD()){
         // pick out FCAL layer for HAD so they are plotted correctly.
         if(region.IsLArFCAL23A() || region.IsLArFCAL23C()){
            had->SetTriggerTower(m_l1map->GetEta(),m_l1map->GetPhi(),satThresh,m_l1map->GetPpmFcalLayer()->at(0));
         }
         else{
            had->SetTriggerTower(m_l1map->GetEta(),m_l1map->GetPhi(),satThresh);
         }
      }
   }
   
   
   itr = m_map_etaPhiId_satLvl.begin();
   end = m_map_etaPhiId_satLvl.end();
   em = &em_satLvl;
   had = &had_satLvl;
   for(;itr != end;++itr){
      
      L1CaloChannelId id(itr->first);
      unsigned int satThresh = itr->second;
      
      m_l1map->SetPpmChannelID(id);
      CaloDivision region = m_l1map->GetDetectorRegion();
      
      if(m_l1map->GetLayer().IsEM()){
         em->SetTriggerTower(m_l1map->GetEta(),m_l1map->GetPhi(),satThresh);
      }
      else if(m_l1map->GetLayer().IsHAD()){
         // pick out FCAL layer for HAD so they are plotted correctly.
         if(region.IsLArFCAL23A() || region.IsLArFCAL23C()){
            had->SetTriggerTower(m_l1map->GetEta(),m_l1map->GetPhi(),satThresh,m_l1map->GetPpmFcalLayer()->at(0));
         }
         else{
            had->SetTriggerTower(m_l1map->GetEta(),m_l1map->GetPhi(),satThresh);
         }
      }
   }
   
   // Get histograms
   TH2* h_em_satHigh = em_satHigh.GetEtaPhiHistogram("h_em_satHigh","EM SatHigh");
   TH2* h_had_satHigh = had_satHigh.GetEtaPhiHistogram("h_had_satHigh","HAD SatHigh");
   
   TH2* h_em_satLow = em_satLow.GetEtaPhiHistogram("h_em_satLow","EM SatLow");
   TH2* h_had_satLow = had_satLow.GetEtaPhiHistogram("h_had_satLow","HAD SatLow");
   
   TH2* h_em_satLvl = em_satLvl.GetEtaPhiHistogram("h_em_satLvl","EM SatLvl");
   TH2* h_had_satLvl = had_satLvl.GetEtaPhiHistogram("h_had_satLvl","HAD SatLvl");
   
   TFile file("filledSatBcidPlots.root","RECREATE");
   h_em_satHigh->Write();
   h_had_satHigh->Write();
   h_em_satLow->Write();
   h_had_satLow->Write();
   h_em_satLvl->Write();
   h_had_satLvl->Write();
   
   file.Close();
}

MeanValue SatBcidTreeFiller::GetEndcapMean(L1CaloChannelId& id,std::map<unsigned int,unsigned int>& map){
   // want to calculate the mean of the two trigger towers at eta (-)2.45 so
   // they can be propagated across the rest of the Endcap till the FCAL boarder
   MeanValue temp;
   
   m_l1map->SetPpmChannelID(id);
   const unsigned int iEta = m_l1map->GetIntegerEta();
   const unsigned int iPhi = m_l1map->GetIntegerPhi();
   EtaPhiId epId(iEta,iPhi,m_l1map->GetLayer());
   
   std::vector<L1CaloChannelId> eta245;
   EtaPhiId tempId;
   unsigned int phi = 0;
   unsigned int eta = iEta > 49 ? 49 + 24 : 49 - 25;
   
   tempId.Clear();
   phi = (iPhi % 2) == 0 ? iPhi : iPhi - 1;
   tempId.SetEtaPhi(eta,phi,epId.GetLayer());
   m_l1map->SetEtaPhi(tempId.GetEta(),tempId.GetPhi(),tempId.GetLayer());
   eta245.push_back(m_l1map->GetPpmChannelID()->at(0));
   
   tempId.Clear();
   phi = (iPhi % 2) == 0 ? iPhi + 1: iPhi;
   tempId.SetEtaPhi(eta,phi,epId.GetLayer());
   m_l1map->SetEtaPhi(tempId.GetEta(),tempId.GetPhi(),tempId.GetLayer());
   eta245.push_back(m_l1map->GetPpmChannelID()->at(0));
   
   for(unsigned int i=0;i<eta245.size();++i){
      if(map[eta245[i].GetId()] != 0)
         temp.AddEntry(map[eta245[i].GetId()]);
   }
   
   return temp;
}

MeanValue SatBcidTreeFiller::GetEtaMean(L1CaloChannelId& id,std::map<unsigned int,unsigned int>& map){
   // want to calculate the mean of the trigger towers immediate above and below the current
   // trigger tower
   // 1
   // X
   // 2
   // where X is the passed trigger tower
   MeanValue temp;
   
   m_l1map->SetPpmChannelID(id);
   const unsigned int iEta = m_l1map->GetIntegerEta();
   const unsigned int iPhi = m_l1map->GetIntegerPhi();
   EtaPhiId epId(iEta,iPhi,m_l1map->GetLayer());
   
   std::vector<L1CaloChannelId> updown;
   EtaPhiId tempId;
   unsigned int phi = 0;
   
   // get channel above
   tempId.Clear();
   if(iEta < 49 - 32 || iEta >= 49 + 32){ // FCAL
      // for FCAL it is just as easy to adjust MCM number to change phi
      if(id.GetSubmodule() == 0xf)
         m_l1map->SetPpmChannel(id.GetCrate(),id.GetModule(),0,id.GetChannel());
      else
         m_l1map->SetPpmChannel(id.GetCrate(),id.GetModule(),id.GetSubmodule()+1,id.GetChannel());
   }
   else{
      if(iEta < 49 - 25 || iEta >= 49 + 25) // ENDCAP
         phi = (iPhi == 62) ? 0 : iPhi + 2;
      else // BARREL
         phi = (iPhi == 63) ? 0 : iPhi + 1;
      tempId.SetEtaPhi(iEta,phi,epId.GetLayer());
      m_l1map->SetEtaPhi(tempId.GetEta(),tempId.GetPhi(),tempId.GetLayer());
   }
   updown.push_back(m_l1map->GetPpmChannelID()->at(0));
   
   // get channel below
   tempId.Clear();
   if(iEta < 49 - 32 || iEta >= 49 + 32){ // FCAL
      // for FCAL it is just as easy to adjust MCM number to change phi
      if(id.GetSubmodule() == 0)
         m_l1map->SetPpmChannel(id.GetCrate(),id.GetModule(),0xf,id.GetChannel());
      else
         m_l1map->SetPpmChannel(id.GetCrate(),id.GetModule(),id.GetSubmodule()-1,id.GetChannel());
   }
   else{
      if(iEta < 49 - 25 || iEta >= 49 + 25) // ENDCAP
         phi = (iPhi == 0) ? 62 : iPhi - 2;
      else // BARREL
         phi = (iPhi == 0) ? 63 : iPhi - 1;
      tempId.SetEtaPhi(iEta,phi,epId.GetLayer());
      m_l1map->SetEtaPhi(tempId.GetEta(),tempId.GetPhi(),tempId.GetLayer());
   }
   updown.push_back(m_l1map->GetPpmChannelID()->at(0));
   
   for(unsigned int i=0;i<updown.size();++i){
      temp.AddEntry(map[updown[i].GetId()]);
   }
   
   return temp;
}

MeanValue SatBcidTreeFiller::GetCircleMean(L1CaloChannelId& id,std::map<unsigned int,unsigned int>& map){
   
   // want to calculate the mean of the 8 trigger towers surrounding this tower
   // should only be used in 0.1x0.1 trigger tower channels so -2.35 to 2.35 in eta
   MeanValue temp;
   
   // first make EtaPhiId for all channels to include:
   //  1 2 3
   //  4 X 5
   //  6 7 8
   // Where X is the passed EtaPhiId
   std::vector<L1CaloChannelId> circle;
   // must make sure to wrap phi on top and bottom
   // also don't want to include bad LArFEB channels
   
   m_l1map->SetPpmChannelID(id);
   const unsigned int iEta = m_l1map->GetIntegerEta();
   const unsigned int iPhi = m_l1map->GetIntegerPhi();
   EtaPhiId epId(iEta,iPhi,m_l1map->GetLayer());
   
   if(!(49 - 24 <= epId.GetIntegerEta() && epId.GetIntegerEta() < 49 + 24)){
      std::cerr << "[SatBcidTreeFiller::GetCircleMean] ERROR, out of eta range: " << epId.GetEta() << std::endl;
      return temp;
   }
   
   EtaPhiId tempId;
   unsigned int phi = 0;
   tempId.Clear();
   phi = (iPhi == 63) ? 0 : iPhi+1;
   tempId.SetEtaPhi(iEta-1,phi,epId.GetLayer());
   m_l1map->SetEtaPhi(tempId.GetEta(),tempId.GetPhi(),tempId.GetLayer());
   if(!BadLArFEB(m_l1map->GetPpmChannelID()->at(0)))
      circle.push_back(m_l1map->GetPpmChannelID()->at(0));
   
   tempId.Clear();
   tempId.SetEtaPhi(iEta,phi,epId.GetLayer());
   m_l1map->SetEtaPhi(tempId.GetEta(),tempId.GetPhi(),tempId.GetLayer());
   if(!BadLArFEB(m_l1map->GetPpmChannelID()->at(0)))
      circle.push_back(m_l1map->GetPpmChannelID()->at(0));
   
   tempId.Clear();
   tempId.SetEtaPhi(iEta-1,phi,epId.GetLayer());
   m_l1map->SetEtaPhi(tempId.GetEta(),tempId.GetPhi(),tempId.GetLayer());
   if(!BadLArFEB(m_l1map->GetPpmChannelID()->at(0)))
      circle.push_back(m_l1map->GetPpmChannelID()->at(0));
   
   tempId.Clear();
   tempId.SetEtaPhi(iEta-1,iPhi,epId.GetLayer());
   m_l1map->SetEtaPhi(tempId.GetEta(),tempId.GetPhi(),tempId.GetLayer());
   if(!BadLArFEB(m_l1map->GetPpmChannelID()->at(0)))
      circle.push_back(m_l1map->GetPpmChannelID()->at(0));
   
   tempId.Clear();
   tempId.SetEtaPhi(iEta+1,iPhi,epId.GetLayer());
   m_l1map->SetEtaPhi(tempId.GetEta(),tempId.GetPhi(),tempId.GetLayer());
   if(!BadLArFEB(m_l1map->GetPpmChannelID()->at(0)))
      circle.push_back(m_l1map->GetPpmChannelID()->at(0));
   
   tempId.Clear();
   phi = (iPhi == 0) ? 63 : iPhi-1;
   tempId.SetEtaPhi(iEta+1,phi,epId.GetLayer());
   m_l1map->SetEtaPhi(tempId.GetEta(),tempId.GetPhi(),tempId.GetLayer());
   if(!BadLArFEB(m_l1map->GetPpmChannelID()->at(0)))
      circle.push_back(m_l1map->GetPpmChannelID()->at(0));
   
   tempId.Clear();
   tempId.SetEtaPhi(iEta,phi,epId.GetLayer());
   m_l1map->SetEtaPhi(tempId.GetEta(),tempId.GetPhi(),tempId.GetLayer());
   if(!BadLArFEB(m_l1map->GetPpmChannelID()->at(0)))
      circle.push_back(m_l1map->GetPpmChannelID()->at(0));
   
   tempId.Clear();
   tempId.SetEtaPhi(iEta-1,phi,epId.GetLayer());
   m_l1map->SetEtaPhi(tempId.GetEta(),tempId.GetPhi(),tempId.GetLayer());
   if(!BadLArFEB(m_l1map->GetPpmChannelID()->at(0)))
      circle.push_back(m_l1map->GetPpmChannelID()->at(0));
   
   // sum channels
   for(unsigned int i=0;i<circle.size();++i){
      if(map[circle[i].GetId()] != 0)
         temp.AddEntry(map[circle[i].GetId()]);
   }
   
   return temp;
}

unsigned int SatBcidTreeFiller::GetIntegerEta(unsigned int inEta){
   // input eta is from 0-98 in units of 0.1 eta where 0 is
   // the left most eta bin -4.9 to -4.4, then counting upward to 4.9
   
   unsigned int outEta = 999;
   
   if                        (inEta < 49 -44) outEta = 0; // -4.9 <= eta < -4.4
   else if(49 -44 <= inEta && inEta < 49 -40) outEta = 1; // -4.4 <= eta < -4.0
   else if(49 -40 <= inEta && inEta < 49 -36) outEta = 2; // -4.0 <= eta < -3.6
   else if(49 -36 <= inEta && inEta < 49 -32) outEta = 3; // -3.6 <= eta < -3.2
   else if(49 -32 <= inEta && inEta < 49 -31) outEta = 4; // -3.2 <= eta < -3.1
   else if(49 -31 <= inEta && inEta < 49 -29) outEta = 5; // -3.1 <= eta < -2.9
   else if(49 -29 <= inEta && inEta < 49 -27) outEta = 6; // -2.9 <= eta < -2.7
   else if(49 -27 <= inEta && inEta < 49 -25) outEta = 7; // -2.7 <= eta < -2.5
   else if(49 -25 <= inEta && inEta < 49 +25){            // -2.5 <= eta < +2.5
      outEta = 8;
      outEta += inEta - (49-25); // goes from 8 to 57
   }
   else if(49 +25 <= inEta && inEta < 49 +27) outEta = 58; // +2.5 <= eta < +2.7
   else if(49 +27 <= inEta && inEta < 49 +29) outEta = 59; // +2.7 <= eta < +2.9
   else if(49 +29 <= inEta && inEta < 49 +31) outEta = 60; // +2.9 <= eta < +3.1
   else if(49 +31 <= inEta && inEta < 49 +32) outEta = 61; // +3.1 <= eta < +3.2
   else if(49 +32 <= inEta && inEta < 49 +36) outEta = 62; // +3.2 <= eta < +3.6
   else if(49 +36 <= inEta && inEta < 49 +40) outEta = 63; // +3.6 <= eta < +4.0
   else if(49 +40 <= inEta && inEta < 49 +44) outEta = 64; // +4.0 <= eta < +4.4
   else if(49 +44 <= inEta && inEta < 49 +49) outEta = 65; // +4.4 <= eta < +4.9
   
   return outEta;
}

bool SatBcidTreeFiller::BadLArFEB(L1CaloChannelId& id){
   
   switch(id.GetId()){
   // FEB BarC H06 FT05
      case 0x1170400:
      case 0x1170401:
      case 0x1170402:
      case 0x1170403:
      case 0x1170500:
      case 0x1170501:
      case 0x1170502:
      case 0x1170503:
      case 0x1160400:
      case 0x1160401:
      case 0x1160402:
      case 0x1160403:
      case 0x1160500:
      case 0x1160501:
      case 0x1160502:
      case 0x1160503:
      case 0x1150400:
      case 0x1150401:
      case 0x1150402:
      case 0x1150403:
      case 0x1150500:
      case 0x1150501:
      case 0x1150502:
      case 0x1150503:
      case 0x1140500:
      case 0x1140501:
      case 0x1140502:
      case 0x1140503:
         return true;
   }
   
   return false;
   
}

bool SatBcidTreeFiller::BadLArFEB(EtaPhiId& epId){
   
   m_l1map->SetEtaPhi(epId.GetEta(),epId.GetPhi(),epId.GetLayer());
   L1CaloChannelId id(m_l1map->GetPpmChannelID()->at(0));
   return BadLArFEB(id);
   
}

bool SatBcidTreeFiller::OtherBadChannels(L1CaloChannelId& id){
   
   switch(id.GetId()){
      case 0x03150203: // random signal shapes
      case 0x03110500: // finds analogue sat but shouldn't 
      case 0x04100f03: // random signal shapes 
      case 0x05160b00: // badly reconstructed signals
      case 0x05160b01: // badly reconstructed signals
      case 0x05160b02: // badly reconstructed signals
      case 0x05160b03: // badly reconstructed signals
      case 0x041f0500: // badly reconstructed signals
      case 0x001e0803: // badly reconstructed signals
         return true;
   }
   
   return false;
}
