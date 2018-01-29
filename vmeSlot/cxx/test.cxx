
//#include "VME_memRegisters.h"
#include "VMESlotClass.h"

#include "TH2F.h"
#include "TCanvas.h"
#include "TStyle.h"

void test(void){
	
	
	char filename[200] = "xcv1000e30.bit";
	
	VMESlot vme(13);
	
	
	vme.ClearRemFPGA();
	
	sleep(1);
	
	vme.LoadRemFpgaFromFlash(1);
	
	cerr << "VME Status: 0x" << hex << vme.GetVMEStatus() << dec << endl;

	sleep(1);

	vme.ClearRemFPGA();

	sleep(1);

	vme.LoadRemFpgaFromFlash(2);

	u_int vers = vme.GetRemFpgaFirmwareVersion();
	
	u_int upperNum = ((vers & 0xffff0000) >> 16);
	u_int lowerNum = (vers & 0xffff);
	
	cerr << "REM Version: " << upperNum << "." << lowerNum << "(0x" << hex << vers << dec << ")" << endl;
	
	exit(0);
	
	
	
}

