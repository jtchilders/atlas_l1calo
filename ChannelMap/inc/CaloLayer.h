////////////////////////////////////////////////////////////////
/// L1Calo Channel Mapping Tool
/// J Taylor Childers III
/// Heidelberg Universitaet
///
/// 
///
////////////////////////////////////////////////////////////////

#ifndef CALOLAYER_H
#define CALOLAYER_H

#include <string>

class CaloLayer{
public:
   
   enum EM_OR_HAD{
      LAYER_NOT_SET = 0,
      EM            = 1,
      HAD           = 2
   };
   
   CaloLayer(EM_OR_HAD layer):m_layer(layer){};
   CaloLayer(void):m_layer(LAYER_NOT_SET){};
   ~CaloLayer(void){};
   
   void SetCaloLayer(EM_OR_HAD layer){m_layer = layer;};
   EM_OR_HAD GetCaloLayer(void) const {return m_layer;};
   
   std::string GetLayerAsString(void) const {return (m_layer == EM) ? "EM" : (m_layer == HAD ? "HAD" : "LAYER_NOT_SET");};
   
   bool IsSet(void) const {return (m_layer == LAYER_NOT_SET) ? false : true;};
   bool IsEM(void) const {if(m_layer == EM) return true; return false;};
   bool IsHAD(void) const {if(m_layer == HAD) return true; return false;};
   
   void SetEM(void){m_layer = EM;};
   void SetHAD(void){m_layer = HAD;};
   
   void Clear(void){m_layer = LAYER_NOT_SET;};
   
   bool operator==(const CaloLayer& layer) const {if(layer.GetCaloLayer() == m_layer) return true; return false;};
   bool operator!=(const CaloLayer& layer) const {if(layer.GetCaloLayer() != m_layer) return true; return false;};
private:
   EM_OR_HAD m_layer;
   
};

#endif

