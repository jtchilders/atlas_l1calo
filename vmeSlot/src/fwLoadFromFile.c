#include <iostream>
#include "VMESlotClass.h"
#include <string>

using namespace std;


int main(int argc,char** argv){
	
	cerr << "This program loads the firmware bit file passed\n to the PPM REM FPGA.\n";	
	string filename;
	for(int i=0;i<argc;i++){

		if(strncmp(argv[i],"-f",2) == 0)
			filename = argv[i+1];
	}
	
	if(filename.size() == 0){
		cerr << "Usage: fwToFlash -f <filename>\n\n";
		return 0;
	}

	cerr << "Current Settings:\n";
	cerr << "File to be loaded into FPGA: " << filename << endl;
	
	VMESlot *vme;
	for(int slot=5;slot<5+16;slot++){

		if(slot != 13) continue;

		vme = new VMESlot(slot);
		if(!vme->IsSlotOccupied()){
			cerr << "Slot " << slot << " is not occupied, moving on...\n";
			continue;
		}
		
		cerr << "Loading File, " << filename << ", to Flash in crate slot " << slot << endl;
		vme->loadPprmFirmwareFromFile((char *)filename.c_str(),XCVE);
		
		sleep(1);
		uint version = vme->GetRemFpgaFirmwareVersion();
		
		cerr << "Loaded firmware version " << (version >> 16) << "." << (version & 0xffff) << " into PPM Crate Slot " << slot << endl;
					
		delete vme;
		
	}






	return 0;
}
