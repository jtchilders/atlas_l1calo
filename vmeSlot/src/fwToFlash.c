#include <iostream>
#include "VMESlotClass.h"
#include <string>

using namespace std;


int main(int argc,char** argv){
	
	cerr << "This program copies the file passed to the\n specified PPM flash memory location.\n";	
	string filename;
	uint memoryLocation=1;
	for(int i=0;i<argc;i++){

		if(strncmp(argv[i],"-f",2) == 0)
			filename = argv[i+1];
		else if(strncmp(argv[i],"-m",2) == 0)
			memoryLocation = atoi(argv[i+1]);
	}
	
	if(filename.size() == 0){
		cerr << "Usage: fwToFlash -f <filename> -m <memory location 1-6>\n";
		cerr << "       if the memory location isn't specified, 1 is used\n";
		return 0;
	}

	cerr << "Current Settings:\n";
	cerr << "File to be uploaded: " << filename << endl;
	cerr << "Flash Memory Slot: " << memoryLocation << endl;
	cerr << "Is this correct? (yes/no): ";
	char input[40];
	cin >> input;

	if(strncmp(input,"yes",3) != 0) return 0;


	VMESlot *vme;
	for(int slot=5;slot<5+16;slot++){

		if(slot != 13) continue;

		vme = new VMESlot(slot);
		if(!vme->IsSlotOccupied()){
			cerr << "Slot " << slot << " is not occupied, moving on...\n";
			continue;
		}
		
		cerr << "Loading File, " << filename << ", to Flash in crate slot " << slot << endl;
		vme->xilinxFromFileToFlashNEW((char*)filename.c_str(),memoryLocation);
					
		delete vme;
		
	}






	return 0;
}
