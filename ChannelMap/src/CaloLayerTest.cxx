#include <iostream>

#include "CaloLayer.h"

int main(void){
   
   CaloLayer layer;
   
   std::cout << "Layer set: " << (int)layer.IsSet() << " EM_OR_HAD: " << layer.GetCaloLayer() << " = " << layer.GetLayerAsString() << std::endl;
   
   layer.SetCaloLayer(CaloLayer::EM);
   std::cout << "Layer set: " << (int)layer.IsSet() << " EM_OR_HAD: " << layer.GetCaloLayer() << " = " << layer.GetLayerAsString() << std::endl;
   
   layer.SetCaloLayer(CaloLayer::HAD);
   std::cout << "Layer set: " << (int)layer.IsSet() << " EM_OR_HAD: " << layer.GetCaloLayer() << " = " << layer.GetLayerAsString() << std::endl;
   
   return 0;
}
