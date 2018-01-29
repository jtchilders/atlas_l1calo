#include <iostream>

#include "L1CaloChannelMap.h"
#include "L1CaloChannelId.h"
#include "CaloLayer.h"

using namespace std;


/////////////////////////////////////
/// Just a quick demonstration of
/// how to use the code
////////////////////////////////////

int main(void){
	
	const float myPI = 3.14159265;
	L1CaloChannelMap *map = new L1CaloChannelMap();
	
	int choice=0;
	cout << "\nWant to specify Eta/Phi(1) or System Channel(2): ";
	cin >> choice;
	
	// Test Get Eta Phi for all parts
	while(choice == 1){
		
		int emHad;
		cout << "\nEnter EM(1)/HAD(2): ";
		cin >> emHad;
      CaloLayer layer;
      if(emHad == 1)
         layer.SetEM();
      else if(emHad == 2)
         layer.SetHAD();
		
		float eta;
		cout << "\nEnter Eta: ";
		cin >> eta;
		
		float phi;
		cout << "\nEnter Phi (in units of 0.1: 0-63): ";
		cin >> phi;
		phi = phi*(2.0*myPI/64.0);
		
		map->SetEtaPhi(eta,phi,layer);
		
		cerr << endl;
      for(unsigned int i=0;i<map->GetPpmCrate()->size();i++)
			cout << "PPM - Crate: " << map->GetPpmCrate()->at(i) << " Ppm: " << map->GetPpmModule()->at(i) << " Mcm: " << map->GetPpmSubmodule()->at(i) << " Channel: " << map->GetPpmChannel()->at(i) << endl;
		
		cerr << endl;
      for(unsigned int i=0;i<map->GetCpmCrate()->size();i++)
			cout << "CPM - Crate: " << map->GetCpmCrate()->at(i) << " Cpm: " << map->GetCpmModule()->at(i) << " Serializer Chip: " << map->GetCpmSerializerSubmodule()->at(i) << " Serializer Channel: " << map->GetCpmSerializerChannel()->at(i) << " Cp Chip: " << map->GetCpmCpChipSubmodule()->at(i) << " Cp Channel: " << map->GetCpmCpChipChannel()->at(i) << endl;
		
		cerr << endl;
		for(unsigned int i=0;i<map->GetJemCrate()->size();i++)
			cout << "JEM - Crate: " << map->GetJemCrate()->at(i) << " Jem: " << map->GetJemModule()->at(i) << " Channel: " << map->GetJemChannel()->at(i) << endl;
		
      cerr << endl;
		for(unsigned int i=0;i<map->GetTcppCrate()->size();i++)
         cout << "TCPP - Crate: " << map->GetTcppCrate()->at(i) << " Tcpp: " << map->GetTcppModule()->at(i) << " OutputSubmodule: " << map->GetTcppOutputSubmodule()->at(i) << " OutputChannel: " << map->GetTcppOutputChannel()->at(i) << " InputSubmodule: " << map->GetTcppInputSubmodule()->at(i) << " InputChannel: " << map->GetTcppInputChannel()->at(i) << " TileDrawer: " << map->GetTcppTileDrawer()->at(i).GetIdAsString() << endl;
      
      cerr << endl;
      cout << "Eta/Phi: " << map->GetEta() << " / " << map->GetPhi() << "; DetectorRegion: " << map->GetDetectorRegion().GetString() << endl;
      cerr << endl;
		
	}
	
	// Test Get(PPM/JEM/CPM)Channel functions
	unsigned int crate,module,submodule,channel;
	while(choice == 2){
		int subsystem=0;
		cout << "\nWhat System do you want to specify? PPM(1)/CPM(2)/JEM(3): ";
		cin >> subsystem;
		
		switch(subsystem){
		case 1:
			crate=999;
			cout << "\n Enter PPM Crate (0-7): ";
			cin >> crate;
			
			module=999;
			cout << "\n Enter PPM Module (0-15): ";
			cin >> module;
			
			submodule=999;
			cout << "\n Enter PPM Submodule (0-15): ";
			cin >> submodule;
			
			channel=999;
			cout << "\n Enter PPM Channel (0-3): ";
			cin >> channel;
			
			map->SetPpmChannel(crate,module,submodule,channel);
			
			break;
		case 2:
      {
			
			crate=999;
			cout << "\n Enter CPM Crate (8-11): ";
			cin >> crate;
			
			module=999;
			cout << "\n Enter CPM Module (1-14): ";
			cin >> module;
			
			submodule=999;
			cout << "\n Enter CPM Serializer Submodule (0-19): ";
			cin >> submodule;
			
			channel=999;
			cout << "\n Enter CPM Serializer Channel (0-7): ";
			cin >> channel;
			
			map->SetCpmChannelWithSerializer(crate,module,submodule,channel);
			
			break;
      }
		case 3:
			crate=999;
			cout << "\n Enter JEM Crate (12-13): ";
			cin >> crate;
			
			module=999;
			cout << "\n Enter JEM Module (0-15): ";
			cin >> module;
			
			channel=999;
			cout << "\n Enter JEM Channel (0-87): ";
			cin >> channel;
			
			map->SetJemChannel(crate,module,channel);
			
			break;
		}
		
		
      cerr << endl;
      for(unsigned int i=0;i<map->GetPpmCrate()->size();i++)
         cout << "PPM - Crate: " << map->GetPpmCrate()->at(i) << " Ppm: " << map->GetPpmModule()->at(i) << " Mcm: " << map->GetPpmSubmodule()->at(i) << " Channel: " << map->GetPpmChannel()->at(i) << endl;
      
      cerr << endl;
      for(unsigned int i=0;i<map->GetCpmCrate()->size();i++)
         cout << "CPM - Crate: " << map->GetCpmCrate()->at(i) << " Cpm: " << map->GetCpmModule()->at(i) << " Serializer Chip: " << map->GetCpmSerializerSubmodule()->at(i) << " Serializer Channel: " << map->GetCpmSerializerChannel()->at(i) << " Cp Chip: " << map->GetCpmCpChipSubmodule()->at(i) << " Cp Channel: " << map->GetCpmCpChipChannel()->at(i) << endl;
      
		cerr << endl;
      for(unsigned int i=0;i<map->GetJemCrate()->size();i++)
			cout << "JEM - Crate: " << map->GetJemCrate()->at(i) << " Jem: " << map->GetJemModule()->at(i) << " Channel: " << map->GetJemChannel()->at(i) << endl;
      
      cerr << endl;
      for(unsigned int i=0;i<map->GetTcppCrate()->size();i++)
         cout << "TCPP - Crate: " << map->GetTcppCrate()->at(i) << " Tcpp: " << map->GetTcppModule()->at(i) << " OutputSubmodule: " << map->GetTcppOutputSubmodule()->at(i) << " OutputChannel: " << map->GetTcppOutputChannel()->at(i) << " InputSubmodule: " << map->GetTcppInputSubmodule()->at(i) << " InputChannel: " << map->GetTcppInputChannel()->at(i) << " TileDrawer: " << map->GetTcppTileDrawer()->at(i).GetIdAsString() << endl;
      
		cerr << endl;
		cout << "Eta/Phi: " << map->GetEta() << " / " << map->GetPhi() << "; DetectorRegion: " << map->GetDetectorRegion().GetString() << endl;
		cerr << endl;
	}
	
	
	
	return 0;
}


