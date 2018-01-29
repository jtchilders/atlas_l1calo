#include <iostream>

#include "EtaPhiId.h"

int main(void){
   
   EtaPhiId id;
   
   float eta=0,phi=0;
   
   while(1){
      std::cout << "Enter Eta: ";
      std::cin >> eta;
      
      std::cout << "Enter Phi: ";
      std::cin >> phi;
      
      unsigned int tempLayer = 0;
      std::cout << "Enter EM(1) or HAD(2): ";
      std::cin >> tempLayer;
      
      CaloLayer layer;
      if(tempLayer == 1)
         layer.SetCaloLayer(CaloLayer::EM);
      else if(tempLayer == 2)
         layer.SetCaloLayer(CaloLayer::HAD);
      
      id.SetEtaPhi(eta,phi,layer);
      
      std::cout << "eta: " << id.GetEta() << " eta as an integer: " << id.GetIntegerEta() << " left side of TT as integer: " << id.GetIntegerTriggerTowerEta() << std::endl;
      std::cout << " phi: " << id.GetPhi() << " phi as an integer: " << id.GetIntegerPhi() << " bottom of TT as integer: " << id.GetIntegerTriggerTowerPhi() << std::endl;
      std::cout << " layer: " << layer.GetLayerAsString() << std::endl;
      std::cout << std::endl;
   }
   return 0;
}

