#include <iostream>

#include "FcalLayer.h"

int main(void){
   FcalLayer layer;
   
   std::cout << "Layer set: " << (int)layer.IsSet() << " FCAL_LAYER: " << layer.GetFcalLayer() << " = " << layer.GetLayerAsString() << std::endl;
   
   layer.SetFcalLayer(FcalLayer::FCAL1);
   std::cout << "Layer set: " << (int)layer.IsSet() << " FCAL_LAYER: " << layer.GetFcalLayer() << " = " << layer.GetLayerAsString() << std::endl;
   
   layer.SetFcalLayer(FcalLayer::FCAL2);
   std::cout << "Layer set: " << (int)layer.IsSet() << " FCAL_LAYER: " << layer.GetFcalLayer() << " = " << layer.GetLayerAsString() << std::endl;
   
   layer.SetFcalLayer(FcalLayer::FCAL3);
   std::cout << "Layer set: " << (int)layer.IsSet() << " FCAL_LAYER: " << layer.GetFcalLayer() << " = " << layer.GetLayerAsString() << std::endl;
   
   
   
   return 0;
}

