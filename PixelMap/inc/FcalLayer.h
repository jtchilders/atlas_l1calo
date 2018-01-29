////////////////////////////////////////////////////////////////////
/// L1Calo Channel Mapping Tool
/// J Taylor Childers III
/// Heidelberg Universitaet
///
/// FcalLayer class provides the FCAL enum. It's pretty straight forward.
///
////////////////////////////////////////////////////////////////////



#ifndef FCALLAYER_H
#define FCALLAYER_H

#include <string>

class FcalLayer{
public:
   
   enum FCAL_LAYER{
      LAYER_NOT_SET = 0,
      FCAL1         = 1,
      FCAL2         = 2,
      FCAL3         = 3
   };
   
   FcalLayer(FCAL_LAYER layer):m_layer(layer){};
   FcalLayer(void):m_layer(LAYER_NOT_SET){};
   ~FcalLayer(void){};
   
   void SetFcalLayer(FCAL_LAYER layer){m_layer = layer;};
   FCAL_LAYER GetFcalLayer(void) const {return m_layer;};
   
   std::string GetLayerAsString(void) const {return (m_layer == FCAL1) ? "FCAL1" : (m_layer == FCAL2 ? "FCAL2" : (m_layer == FCAL3 ? "FCAL3" : "LAYER_NOT_SET") );};
   
   bool IsSet(void) const {return (m_layer == LAYER_NOT_SET) ? false : true;};
   
   void Clear(void){m_layer = LAYER_NOT_SET;};
   
private:
   FCAL_LAYER m_layer;
   
};

#endif

