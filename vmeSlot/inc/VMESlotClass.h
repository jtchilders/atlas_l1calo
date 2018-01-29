#ifndef __VMESLOTCLASS_H__
#define __VMESLOTCLASS_H__

#include <iostream>
#include <sstream>
#include <unistd.h>
#include <cstdio>
#include <fcntl.h>

#include <byteswap.h>

#include "PprmDefs.h"

#define SW_BYTESWAP 0

using namespace std;

extern "C"{
#include "rcc_error/rcc_error.h"
#include "vme_rcc/vme_rcc.h"
}
class VMESlot{
public:
	VMESlot(int);
	~VMESlot(void);
	
	void WriteToAddress(u_int addr,u_int value);
	void WriteToAddress(u_int addr,unsigned char value);
	void ReadFromAddress(u_int addr,u_int& value);
	u_int ReadFromAddress(u_int addr);
	void ReadFromAddress(u_int addr,u_char& value);
	
	
	void ReadTempsAndVoltages(double* temp, double* voltage);
	
	u_int GetModuleID(void){return ModuleID;};
	
	u_int GetVMEConfig(void){return ReadFromAddress(VMECONFREG);};
	void SetVMEConfig(u_int value){WriteToAddress(VMECONFREG,value);};
	
	u_int GetVMEStatus(void){return ReadFromAddress(VMESTATREG);};
	void SetVMEStatus(u_int value){WriteToAddress(VMESTATREG,value);};
	
	u_int GetFlashRAMStatus(void){return ReadFromAddress(FLASHSTATUS);};
	
	void SetFlashRAMLoad(u_int value){WriteToAddress(FLASHLOADXIL,value);};
	
	u_int GetATMEGA(void){ReadFromAddress(ATMEGA); return ReadFromAddress(ATMEGA);};
	void SetATMEGA(u_int value){WriteToAddress(ATMEGA,value);};
	
	u_int GetRemFpgaFirmwareVersion(void){return ReadFromAddress(XCVEVERSION);};
	
	void ClearRemFPGA(void);
	void ClearLcdFPGAs(void);
	
	void LoadRemFpgaFromFlash(u_int flashLocation);
	void LoadCpLcdFpgaFromFlash(void);
	void LoadJemLcdFpgaFromFlash(void);
	
	bool xilinxFromFileToFlashOLD(char *bitfile,unsigned int flashadr);
	bool xilinxFromFileToFlashNEW(char *bitfile,unsigned int flashadr);
	bool loadPprmFirmwareFromFile( char *bitfile,char xilpos);
	
	bool IsSlotOccupied(){return slotOccupied;};
	
private:
	VME_MasterMap_t map;
	int pMap;
	u_int SlotBaseAddr;
	u_int slotNum;
	bool slotOccupied;
	
	u_int ModuleID;
	
	VME_ErrorCode_t errCode;
	char errString[VME_MAXSTRING];
	
	unsigned short xilGetShort ( unsigned char *ptr );
	unsigned int xilGetInt ( unsigned char *ptr );
	
	
};



#endif
