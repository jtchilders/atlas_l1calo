#include <iostream>
#include "VMESlotClass.h"
#include <string>

using namespace std;


int main(int argc,char** argv){
	
	cerr << "This program copies the file passed to the\n specified PPM flash memory location.\n";	
	string filename;
	uint memoryLocation=1;
	for(int i=0;i<argc;i++){

		if(strncmp(argv[i],"-m",2) == 0)
			memoryLocation = atoi(argv[i+1]);
		else
			memoryLocation = 1;
	}
	
/*
	if(filename.size() == 0){
		cerr << "Usage: fwToFlash -m <memory location 1-6>\n";
		cerr << "       if the memory location isn't specified, 1 is used\n";
		return 0;
	}
*/

	cerr << "Current Settings:\n";
	cerr << "Loading Firmware from Flash Memory Slot: " << memoryLocation << endl;
	
	VMESlot *vme;
	for(int slot=5;slot<5+16;slot++){
		
		if(slot != 13) continue;
		
		
		vme = new VMESlot(slot);
		if(!vme->IsSlotOccupied()){
			cerr << "Slot " << slot << " is not occupied, moving on...\n";
			continue;
		}
		
		cerr << "Loading Firmware in PPM slot " << slot << " << from flash memory slot: " << memoryLocation << endl;
		
		vme->LoadRemFpgaFromFlash(memoryLocation);
		sleep(1);
		uint version = vme->GetRemFpgaFirmwareVersion();
		
		cerr << "Loaded firmware version " << (version >> 16) << "." << (version & 0xffff) << " into PPM Crate Slot " << slot << " and Flash Memory slot: " << memoryLocation << endl;
					
		delete vme;
		
	}






	return 0;
}
