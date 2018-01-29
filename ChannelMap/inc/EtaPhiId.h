////////////////////////////////////////////////////////////////////////
/// L1Calo Channel Mapping Tool
/// J Taylor Childers III
/// Heidelberg Universitaet
///
/// EtaPhiId allows eta/phi/layer information to be encoded/decoded into
/// a 32-bit number for ease of use. Use the constructers or Set functions
/// for setting the ID. Use the Set/Get functions to interact with the 
/// ID.
///
/// GetIntegerPhi() returns 0-63
/// GetIntegerEta() returns 0-97
/// 
/// GetIntegerTriggerTowerEta/Phi return the bottom left corner integer
/// eta/phi values of whatever Trigger Tower the current eta/phi setting
/// is within. So if you do SetEtaPhi(0.045,0.045,CaloLayer::EM),
/// then call GetIntegerTriggerTowerEta() you will get 49 and from
/// GetIntegerTriggerTowerPhi(), 0. This goes the same for the 0.2x0.2 and
/// other various sized Trigger Towers.
/// 
/// GetIdAsString returns a std::string of the format: "0x%08x"
///
/// Eta Phi ID:
/// Layer is at bit 31 Set as: 0 = EM and 1 = HAD 
/// Phi is at 16 to 30 Set as: 0-63
/// Eta is at 0 to 15 Set as: 0-97
////////////////////////////////////////////////////////////////////////

#ifndef ETAPHIID_H
#define ETAPHIID_H

#include <cmath>
#include <iostream>
#include <cstdio>

#include "CaloLayer.h"

class EtaPhiId{
public:
   EtaPhiId(const unsigned int eta,const unsigned int phi,const CaloLayer layer);
   EtaPhiId(const float eta, const float phi,const CaloLayer layer);
   EtaPhiId(const unsigned int id);
   EtaPhiId(EtaPhiId* id);
   EtaPhiId(void){Clear();};
   ~EtaPhiId(void){};
   
   void SetEtaPhi(const unsigned int eta,const unsigned int phi,const CaloLayer layer);
   void SetEtaPhi(const float eta, const float phi,const CaloLayer layer);
   void SetId(const unsigned int id);
   void SetId(EtaPhiId* id);
   
   unsigned int GetId(void) const {return m_id;};
   
   unsigned int GetIntegerEta(void) const {return m_uint_eta;};
   unsigned int GetIntegerPhi(void) const {return m_uint_phi;};
   
   unsigned int GetIntegerTriggerTowerEta(void) const {return m_uint_tt_eta;};
   unsigned int GetIntegerTriggerTowerPhi(void) const {return m_uint_tt_phi;};
   
   unsigned int GetIntegerJetElementEta(void) const {return m_uint_je_eta;};
   unsigned int GetIntegerJetElementPhi(void) const {return m_uint_je_phi;};
   
   float GetEta(void) const {return m_f_eta;};
   float GetPhi(void) const {return m_f_phi;};
   
   CaloLayer GetLayer(void) const {return m_layer;};
   
   std::string GetIdAsString(void) const {char temp[50];sprintf(temp,"%08x",m_id);return temp;};
   
   void Clear(void);
   
private:
   
   unsigned int m_id;
   float m_f_eta;
   float m_f_phi;
   
   unsigned int m_uint_eta;
   unsigned int m_uint_phi;
   
   unsigned int m_uint_tt_eta;
   unsigned int m_uint_tt_phi;
   
   unsigned int m_uint_je_eta;
   unsigned int m_uint_je_phi;
   
   CaloLayer m_layer;
   
   static const unsigned int MAX_UINT_ETA = 49*2;
   static const unsigned int MIN_UINT_ETA = 0;
   static const unsigned int MAX_UINT_PHI = 64;
   static const unsigned int MIN_UINT_PHI = 0;
   
   static const float myPI;
   
   unsigned int GetEtaPhiId(unsigned int eta,unsigned int phi,CaloLayer layer);
   void GetEtaPhiFromId(unsigned int id, unsigned int& eta,unsigned int& phi,CaloLayer& layer);
   
   unsigned int ftoi_eta(const float eta);
   unsigned int ftoi_phi(const float phi);
   
   float itof_eta(const unsigned int eta);
   float itof_phi(const unsigned int phi);
   
   unsigned int itoi_tt_eta(unsigned int eta,CaloLayer layer);
   unsigned int itoi_tt_phi(unsigned int phi,unsigned int eta);
   
   unsigned int ftoi_tt_eta(float eta,CaloLayer layer);
   unsigned int ftoi_tt_phi(float phi, unsigned int eta);
   
   unsigned int itoi_je_eta(unsigned int eta);
   unsigned int itoi_je_phi(unsigned int phi,unsigned int eta);
   
   bool FloatIsEqualToInt(const float x, const int y);
};

#endif

