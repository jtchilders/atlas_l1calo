
#include "EtaPhiId.h"

const float EtaPhiId::myPI = 3.14159265;

EtaPhiId::EtaPhiId(const unsigned int eta,const unsigned int phi,const CaloLayer layer){
   Clear();
   SetEtaPhi(eta,phi,layer);
}

EtaPhiId::EtaPhiId(const float eta, const float phi,const CaloLayer layer){
   Clear();
   SetEtaPhi(eta,phi,layer);
}

EtaPhiId::EtaPhiId(const unsigned int id){
   Clear();
   SetId(id);
}

EtaPhiId::EtaPhiId(EtaPhiId* id){
   Clear();
   SetId(id);
}

void EtaPhiId::Clear(void){
   m_id = 0;
   
   m_f_eta = 0;
   m_f_phi = 0;
   
   m_uint_eta = 0;
   m_uint_phi = 0;
   
   m_uint_tt_eta = 0;
   m_uint_tt_phi = 0;
   
   m_uint_je_eta = 0;
   m_uint_je_phi = 0;
   
   m_layer.Clear();
}

// Converts integer Eta Phi and layer to an EtaPhiId
unsigned int EtaPhiId::GetEtaPhiId(unsigned int eta,unsigned int phi,CaloLayer layer){
	unsigned int tempLayer = 0;
   if(layer.GetCaloLayer() == CaloLayer::EM) tempLayer = 0;
   else if (layer.GetCaloLayer() == CaloLayer::HAD) tempLayer = 1;
	unsigned int id = ((tempLayer & 0x1) << 31) | ((phi & 0x7fff) << 16) | (eta & 0xffff);
	return id;
}

// Converts an EtaPhiId to the corresponding integer eta/phi/layer
void EtaPhiId::GetEtaPhiFromId(unsigned int id, unsigned int& eta,unsigned int& phi,CaloLayer& layer){
	eta = (id & 0xffff);
	phi = (id >> 16) & 0x7fff;
	const unsigned int tempLayer = (id >> 31) & 0x1;
   
   if(tempLayer == 0) layer.SetCaloLayer(CaloLayer::EM);
   else if(tempLayer == 1) layer.SetCaloLayer(CaloLayer::HAD);
}

void EtaPhiId::SetEtaPhi(const unsigned int eta,const unsigned int phi,const CaloLayer layer){
   m_uint_eta = eta;
   m_uint_phi = phi;
   
   if(m_uint_eta >= MAX_UINT_ETA){
      std::cerr << "EtaPhiId::SetEtaPhi(I): ERROR integer eta outside allowable range of " << MIN_UINT_ETA << " to " << MAX_UINT_ETA << ", eta = " << m_uint_eta << std::endl;
      return;
   }
   
   if(m_uint_phi >= MAX_UINT_PHI){
      std::cerr << "EtaPhiId::SetEtaPhi(I): ERROR integer phi outside allowable range of " << MIN_UINT_PHI << " to " << MAX_UINT_PHI << ", phi = " << m_uint_phi << std::endl;
      return;
   }
   
   m_layer = layer;
   
   if(!m_layer.IsSet()){
      std::cerr << "EtaPhiId::SetEtaPhi(I): ERROR Layer not set.\n";
      return;
   }
   
   m_id = GetEtaPhiId(m_uint_eta,m_uint_phi,m_layer);
   
   m_uint_tt_eta = itoi_tt_eta(m_uint_eta,m_layer);
   m_uint_tt_phi = itoi_tt_phi(m_uint_phi,m_uint_eta);
   
   m_uint_je_eta = itoi_je_eta(m_uint_eta);
   m_uint_je_phi = itoi_je_phi(m_uint_phi,m_uint_eta);
   
   m_f_eta = itof_eta(eta);
   m_f_phi = itof_phi(phi);
   
}

void EtaPhiId::SetEtaPhi(const float eta, const float phi,const CaloLayer layer){
   m_f_eta = eta;
   m_f_phi = phi;
   
   m_layer = layer;
   
   if(!m_layer.IsSet()){
      std::cerr << "EtaPhiId::SetEtaPhi(F): ERROR Layer not set.\n";
      return;
   }
   
   m_uint_eta = ftoi_eta(eta);
   m_uint_phi = ftoi_phi(phi);
   
   if(m_uint_eta >= MAX_UINT_ETA){
      std::cerr << "EtaPhiId::SetEtaPhi(F): ERROR integer eta outside allowable range of " << MIN_UINT_ETA << " to " << MAX_UINT_ETA << ", eta = " << m_uint_eta << std::endl;
      return;
   }
   
   if(m_uint_phi >= MAX_UINT_PHI){
      std::cerr << "EtaPhiId::SetEtaPhi(F): ERROR integer phi outside allowable range of " << MIN_UINT_PHI << " to " << MAX_UINT_PHI << ", phi = " << m_uint_phi << std::endl;
      return;
   }
   
   m_id = GetEtaPhiId(m_uint_eta,m_uint_phi,m_layer);
   
   m_uint_tt_eta = itoi_tt_eta(m_uint_eta,m_layer);
   m_uint_tt_phi = itoi_tt_phi(m_uint_phi,m_uint_eta);
   
   m_uint_je_eta = itoi_je_eta(m_uint_eta);
   m_uint_je_phi = itoi_je_phi(m_uint_phi,m_uint_eta);
   
}

void EtaPhiId::SetId(const unsigned int id){
   m_id = id;
   
   unsigned int eta=0,phi=0;
   CaloLayer layer;
   GetEtaPhiFromId(m_id,eta,phi,layer);
   SetEtaPhi(eta,phi,layer);
}

void EtaPhiId::SetId(EtaPhiId* id){
   unsigned int intId = id->GetId();
   SetId(intId);
}

// Converts a float version of eta (-4.9 to 4.9) to 
// an unsigned integer ranging from 0 to 97, which
// is a representation of the 0.1 eta steps between
// -49 and 49 (I just use all positive integers)
unsigned int EtaPhiId::ftoi_eta(const float eta){

   float inEtaShifted = eta + 4.9;
   unsigned int outEta = (unsigned int)floor(inEtaShifted*10.0);
   if(FloatIsEqualToInt(inEtaShifted*10.0,(int)(outEta+1))) outEta++;
   if(FloatIsEqualToInt(inEtaShifted,0)) outEta = 0;
   
   
   if( outEta > MAX_UINT_ETA)
      outEta = 999;
   
   return outEta;
}

// Converts a float version of phi (0.0 to 2*myPI) to
// an unsigned integer ranging from 0 to 63
unsigned int EtaPhiId::ftoi_phi(const float phi){
   unsigned int outPhi = 0;
   
   const float onePhiUnit = (2.0*myPI)/64.0;
   
   const float phiUnits = phi/onePhiUnit;
   
   outPhi = (unsigned int)floor(phiUnits);
   if(FloatIsEqualToInt(phiUnits,(int)(phiUnits+1))) outPhi++;
   
   
   if(outPhi > MAX_UINT_PHI)
      outPhi = 999;
   
   
   return outPhi;
}

// Converts Integer Eta 0-97 back to float
// of -4.9 to 4.9 in 0.1 steps
float EtaPhiId::itof_eta(const unsigned int eta){
   if(eta == 49) return 0.0;
	else return (float)eta/10.0 - 4.9;
}

// Converts integer phi 0-64 to real phi 0-2*pi
float EtaPhiId::itof_phi(const unsigned int phi){
   return phi*(2.0*myPI/64.0);
}

// Converts an arbitrary integer representations of Eta from 0 - 97 to
// the more specific Eta that represents the eta for the trigger tower
// corresponding to the initial eta. This means if the input eta is 
// part of a trigger tower that is 0.2x0.2 it returns the eta that
// corresponds to the trigger towers location.
unsigned int EtaPhiId::itoi_tt_eta(unsigned int eta,CaloLayer layer){
	
	unsigned int outEta=999;
	if( (/*-49 + 49 <= eta &&*/ eta < -32 + 49) ){
		if(layer.GetCaloLayer() == CaloLayer::EM){
			if( (/*-49 + 49 <= eta &&*/ eta < -44 + 49) ){
				outEta = -49 + 49;
			}
			else if( (-44 + 49 <= eta && eta < -40 + 49)){
				outEta = -44 + 49;
			}
			else if( (-40 + 49 <= eta && eta < -36 + 49)){
				outEta = -40 + 49;
			}
			else if( (-36 + 49 <= eta && eta < -32 + 49)){
				outEta = -36 + 49;
			}
		}
		else if(layer.GetCaloLayer() == CaloLayer::HAD){
			if( (/*-49 + 49 <= eta &&*/ eta < -40 + 49) ){
				outEta = -49 + 49;
			}
			else if( (-40 + 49 <= eta && eta < -32 + 49)){
				outEta = -40 + 49;
			}
		}
	}
	else if( (-32 + 49 <= eta && eta < -31 + 49) ){
		outEta = -32 + 49;
	}
	else if( (-31 + 49 <= eta && eta < -25 + 49) ){
		if( (-31 + 49 <= eta && eta < -29 + 49) ){
			outEta = -31 + 49;
		}
		else if( (-29 + 49 <= eta && eta < -27 + 49) ){
			outEta = -29 + 49;
		}
		else if( (-27 + 49 <= eta && eta < -25 + 49) ){
			outEta = -27 + 49;
		}
		
	}
	else if( (-25 + 49 <= eta && eta < 25 + 49) ){
		outEta = eta;
	}
	else if( (25 + 49 <= eta && eta < 31 + 49) ){
		if( (25 + 49 <= eta && eta < 27 + 49) ){
			outEta = 25 + 49;
		}
		else if( (27 + 49 <= eta && eta < 29 + 49) ){
			outEta = 27 + 49;
		}
		else if( (29 + 49 <= eta && eta < 31 + 49) ){
			outEta = 29 + 49;
		}
		
	}
	else if( (31 + 49 <= eta && eta < 32 + 49) ){
		outEta = 31 + 49;
	}
	else if( (32 + 49 <= eta && eta < 49 + 49) ){
		if(layer.GetCaloLayer() == CaloLayer::EM){
			if( (32 + 49 <= eta && eta < 36 + 49) ){
				outEta = 32 + 49;
			}
			else if( (36 + 49 <= eta && eta < 40 + 49)){
				outEta = 36 + 49;
			}
			else if( (40 + 49 <= eta && eta < 44 + 49)){
				outEta = 40 + 49;
			}
			else if( (44 + 49 <= eta && eta < 49 + 49)){
				outEta = 44 + 49;
			}
		}
		else if(layer.GetCaloLayer() == CaloLayer::HAD){
			if( (32 + 49 <= eta && eta < 40 + 49) ){
				outEta = 32 + 49;
			}
			else if( (40 + 49 <= eta && eta < 49 + 49)){
				outEta = 40 + 49;
			}
		}
	}
	
	return outEta;
}

// Similar to itoi_tt_phi but for the phi coordinates.
unsigned int EtaPhiId::itoi_tt_phi(unsigned int phi,unsigned int eta){
	unsigned int outPhi=999;
	if( (/*-49 + 49 <= eta &&*/ eta < -32 + 49) ){
		outPhi = phi - (phi % 4);
	}
	else if( (-32 + 49 <= eta && eta < -25 + 49) ){
		outPhi = phi - (phi % 2);
	}
	else if( (-25 + 49 <= eta && eta < 25 + 49) ){
		outPhi = phi;
	}
	else if( (25 + 49 <= eta && eta < 32 + 49) ){
		outPhi = phi - (phi % 2);
	}
	else if( (32 + 49 <= eta && eta < 49 + 49) ){
		outPhi = phi - (phi % 4);
	}
	
	return outPhi;
}


unsigned int EtaPhiId::ftoi_tt_eta(float eta,CaloLayer layer){
	
	float shiftedEta = eta + 4.9;
	unsigned int tempEta = (unsigned int)floor(shiftedEta*10.0);
	
	if(fabs(shiftedEta*10.0 - (unsigned int)(tempEta+1)) < 0.01) tempEta++;
	if(fabs(shiftedEta) < 0.01) tempEta = 0;
	
	unsigned int outEta = itoi_tt_eta(tempEta,layer);
	
	return outEta;
}

unsigned int EtaPhiId::ftoi_tt_phi(float phi, unsigned int eta)
{
	
	float fPhi = phi/(2.0*myPI/64.0);
	unsigned int tempPhi = (unsigned int)floor(fPhi);
	if(fabs(fPhi - ((unsigned int)fPhi+1)) < 0.01) tempPhi++;
	
	unsigned int outPhi = itoi_tt_phi(tempPhi,eta);
	
	return outPhi;
}

// converts eta in 0-97 steps to the eta of the bottom left corner of
// the jet element in which it resides.
unsigned int EtaPhiId::itoi_je_eta(unsigned int eta){
   
   // FCAL Jet Elements first
   if( -49 + 49 <= eta && eta < -32 + 49){ // C-Side
      return -49 + 49;
   }
   else if( 32 + 49 <= eta && eta < 49 + 49){ // A-Side
      return 32 + 49;
   }
   // End Cap region
   else if(-32 + 49 <= eta && eta < -29 + 49){ // C-side
      return -32 + 49;
   }
   else if(-29 + 49 <= eta && eta < -27 + 49){ // C-side
      return -29 + 49;
   }
   else if(-27 + 49 <= eta && eta < -24 + 49){ // C-side
      return -27 + 49;
   }
   else if( 24 + 49 <= eta && eta < 27 + 49){ // A-side
      return 24 + 49;
   }
   else if( 27 + 49 <= eta && eta < 29 + 49){ // A-side
      return 27 + 49;
   }
   else if( 29 + 49 <= eta && eta < 32 + 49){ // A-side
      return 29 + 49;
   }
   // Other
   else if( -24 + 49 <= eta && eta < 24 + 49){
      return -24 + 49 + ((int)((eta-24)/2))*2;
   }
   
   return 999;
}

// converts phi in 0-63 steps to the phi of the bottom left corner of
// the jet element in which it resides.
unsigned int EtaPhiId::itoi_je_phi(unsigned int phi,unsigned int eta){
   
   // FCAL Jet Elements first
   if( (-49 + 49 <= eta && eta < -32 + 49) || ( 32 + 49 <= eta && eta < 49 + 49)){
      return (int)(phi/4)*4;
   }
   // Other
   else if( -32 + 49 <= eta && eta < 32 + 49){
      return (int)(phi/2)*2;
   }
   
   return 999;
}

// Compares a float to an integer and returns true if
// they are approximately equal
bool EtaPhiId::FloatIsEqualToInt(const float x, const int y){
   if(fabs(x-(float)y) < 0.005){
      return true;
   }
   return false;
}


