#include "VMESlotClass.h"

VMESlot::VMESlot(int slot){
	
	slotNum = slot;
	
	cerr << "[VMESlot::VMESlot] Setting up slot " << slotNum << endl;
	
	u_int slot_address[16];
	for(int i=0;i<16;i++)
		slot_address[i] = CRATE_BASE + SLOT_5 + SLOT_SIZE*i;
	
	SlotBaseAddr = slot_address[slotNum-5];
	slotOccupied = true;
	
	map.vmebus_address = SlotBaseAddr;
	map.window_size = SLOT_SIZE;
	map.address_modifier = VME_A32;
	map.options = 0;
	
	errCode = VME_Open();
	if(errCode != VME_SUCCESS){
		//VME_ErrorPrint(errCode);
		VME_ErrorString(errCode,errString);
		cerr << "\n[VMESlot::VMESlot] Error upon opening VME: " << errString << endl;
		
		slotOccupied = false;
		return;
	}
	
	errCode = VME_MasterMap(&map,&pMap);
	if(errCode != VME_SUCCESS){
		//VME_ErrorPrint(errCode);
		VME_ErrorString(errCode,errString);
		cerr << "\n[VMESlot::VMESlot] Error mapping vme memory: " << errString << endl;
		
		slotOccupied = false;
		return;
	}
	
	ReadFromAddress(MODULE_ID,ModuleID);
	
	if(ModuleID == 0){
		slotOccupied = false;
		cerr << "[VMESlot::VMESlot] Slot " << slot << " is not Occupied.\n ";
	}
	else
		cerr << "[VMESlot::VMESlot] done; Base Addr: 0x" << hex << SlotBaseAddr << dec << "\n ";
	
}

VMESlot::~VMESlot(void){
	
	//cerr << "[VMESlot::~VMESlot] Closing VME at Addr: 0x" << hex << SlotBaseAddr << dec << "\n";
	
	errCode = VME_MasterUnmap(pMap);
	if(errCode){
		VME_ErrorString(errCode,errString);
		cerr << "\n[VMESlot::~VMESlot] Error unmapping vme memory: " << errString << endl;
		return;
	}
	
	
	errCode = VME_Close();
	if(errCode != VME_SUCCESS){
		VME_ErrorString(errCode,errString);
		cerr << "\n[VMESlot::~VMESlot] Error upon closing VME: " << errString << endl;
		return;
	}
	
	return;
}

// For 32 bit writes
void VMESlot::WriteToAddress(u_int addr,u_int value){
	
	//cerr << "Addr: 0x" << hex << addr << "; value: " << value << dec << endl;
	
	
	if(SW_BYTESWAP)
		errCode = VME_WriteSafeUInt(pMap,addr,bswap_32(value));
	else
		errCode = VME_WriteSafeUInt(pMap,addr,value);
	
	if(errCode){
		VME_ErrorString(errCode,errString);
		cerr << "\n[VMESlot::WriteToAddress] Error upon writing vme memory: " << errString << endl;
		return;
	}
	
	//cerr << "[VMESlot::WriteToAddress 32] Writing 0x" << hex << value << dec << " to 0x" << hex << addr << dec << "; Press Enter to Continue.\n";
	//cin.get();
}

// For 8 bit writes
void VMESlot::WriteToAddress(u_int addr,unsigned char value){
	//cerr << "Addr: 0x" << hex << addr << dec << "; value: 0x" << hex << value << dec << endl;
	
	errCode = VME_WriteSafeUChar(pMap,addr,value);
	if(errCode){
		VME_ErrorString(errCode,errString);
		cerr << "\n[VMESlot::WriteToAddress] Error upon writing vme memory: " << errString << endl;
		return;
	}
	
	//cerr << "[VMESlot::WriteToAddress 8] Writing 0x" << hex << (u_int)value << dec << " to 0x" << hex << addr << dec << "; Press Enter to Continue.\n";
	//cin.get();
}

void VMESlot::ReadFromAddress(u_int addr,u_int& value){
	
	errCode = VME_ReadSafeUInt(pMap,addr,&value);
	if(errCode){
		VME_ErrorString(errCode,errString);
		cerr << "\n[VMESlot::ReadFromAddress] Error upon reading vme memory: " << errString << endl;
		return;
	}
	
	if(SW_BYTESWAP)
		value = bswap_32(value);
	
	//cerr << "[VMESlot::ReadFromAddress 32] Reading 0x" << hex << value << dec << " from 0x" << hex << addr << dec << "; Press Enter to Continue.\n";
	//cin.get();
	
}

u_int VMESlot::ReadFromAddress(u_int addr){
	
	u_int value;
	
	errCode = VME_ReadSafeUInt(pMap,addr,&value);
	if(errCode){
		VME_ErrorString(errCode,errString);
		cerr << "\n[VMESlot::ReadFromAddress] Error upon reading vme memory: " << errString << endl;
		return(errCode);
	}
	
	if(SW_BYTESWAP)
		value = bswap_32(value);
	
	//cerr << "[VMESlot::ReadFromAddress 32] Reading 0x" << hex << value << dec << " from 0x" << hex << addr << dec << "; Press Enter to Continue.\n";
	//cin.get();
	
	return value;
}

void VMESlot::ReadFromAddress(u_int addr,u_char& value){
	
	errCode = VME_ReadSafeUChar(pMap,addr,&value);
	if(errCode){
		VME_ErrorString(errCode,errString);
		cerr << "\n[VMESlot::ReadFromAddress] Error upon reading vme memory: " << errString << endl;
		return;
	}
	
	//cerr << "[VMESlot::ReadFromAddress 8] Reading 0x" << hex << value << dec << " from 0x" << hex << addr << dec << "; Press Enter to Continue.\n";
	//cin.get();
	
}


void VMESlot::ReadTempsAndVoltages(double* temp, double* voltage){
	
	double rawADC[23];
	
	// Read out 7 volatages followed by 16 temps
	for(int i=0;i<23;i++){
		
		u_int valueA=0,valueB=0;
		
		u_int command = 0x80 + 2*i;
		
		WriteToAddress(ATMEGA,command);
		WriteToAddress(ATMEGA,command);
		ReadFromAddress(ATMEGA,valueA);
		
		command++;
		WriteToAddress(ATMEGA,command);
		WriteToAddress(ATMEGA,command);
		ReadFromAddress(ATMEGA,valueB);
		
		rawADC[i] = (valueA & 0xff) | ((valueB & 0x03) << 8);
		
		rawADC[i] *= 2.5;
		
	}
	
	rawADC[0] = rawADC[0]* 84/33;
	rawADC[1] *= 2;
	rawADC[2] *= 2;
	
	// Volatages
	for(int i=0;i<7;i++){
		if(i==5)
			voltage[i] = (rawADC[0]-rawADC[5])*150/91 -rawADC[5];
		else
			voltage[i] = rawADC[i];
		
		//cerr << i << " Voltage: " << voltage[i] << endl;
	}
	
	// Temperatures
	for(int i=0;i<16;i++){
		temp[i] = 413 - rawADC[i+7] * 0.5;
		//cerr << i << " Temp: " << temp[i] << endl;
	}
	
}

// Load the REM FPGA from a bit file in the flash, flashLocation = 1-6
void VMESlot::LoadRemFpgaFromFlash(u_int flashLocation){
	u_int VMEConfig;
	u_int bitmask;
	u_int FlashRAMLoad;
	u_int initMask;
	bool NotDone;
	
	if( !(1 <= flashLocation && flashLocation <= 6) ){
		cerr << "[VMESlot::LoadRemFpgaFromFlash] Flash Location must be between 1 and 6\n";
		return;
	}
	
	// Set FLASH_LOAD_SEL Bit on VME Config Register
	cerr << "[VMESlot::LoadRemFpgaFromFlash] Setting Flash Load Select bit\n";
	VMEConfig=GetVMEConfig();
	
	// Set Flag for loading from flash
	bitmask = 0x00100000;
	VMEConfig &= ~bitmask;
	
	SetVMEConfig(VMEConfig);
	
	// Set FLASHSELXCVE bit on VME Status Register
	cerr << "[VMESlot::LoadRemFpgaFromFlash] Setting Flash Load Enable bit\n";
	
	// Get Flash Address
	switch(flashLocation){
	case 1:
		FlashRAMLoad = RES_PRG_XCVE1;
		break;
	case 2:
		FlashRAMLoad = RES_PRG_XCVE2;
		break;
	case 3:
		FlashRAMLoad = RES_PRG_XCVE3;
		break;
	case 4:
		FlashRAMLoad = RES_PRG_XCVE4;
		break;
	case 5:
		FlashRAMLoad = RES_PRG_XCVE5;
		break;
	case 6:
		FlashRAMLoad = RES_PRG_XCVE6;
		break;
	}
	
	
	SetFlashRAMLoad(FlashRAMLoad);
	
	usleep(500000);
	
	// Check that flash loading is complete
	initMask = 0x00008000;
	
	NotDone = true;
	uint counter=0;
	uint flashRamStatus;
	while(NotDone && counter < 10){
		sleep(1);
		if( (flashRamStatus = GetFlashRAMStatus()) & initMask)
			NotDone = false;
		else
			cerr << "[VMESlot::LoadRemFpgaFromFlash] Waiting for Flash to load. Flash RAM Status Register: 0x" << hex <<
			flashRamStatus << dec << endl;
			counter++;
	}
	if(counter >= 10)
		cerr << "[VMESlot::LoadRemFpgaFromFlash]: Load timed out. Firmware probably not loaded.\n";
	else
		cerr << "[VMESlot::LoadRemFpgaFromFlash]: Firmware should be loaded.\n";
	
	
	
}

void VMESlot::LoadCpLcdFpgaFromFlash(void){
	
	u_int VMEConfig;
	u_int bitmask;
	u_int FlashRAMLoad;
	u_int initMask;
	bool NotDone;
	
	// Set FLASH_LOAD_SEL Bit on VME Config Register
	cerr << "[VMESlot::LoadCpLcdFpgaFromFlash] Setting Flash Load Select bit\n";
	VMEConfig=GetVMEConfig();
	
	// Set Flag for loading from flash
	bitmask = 0x00100000;
	VMEConfig &= ~bitmask;
	SetVMEConfig(VMEConfig);
	
	// Set FLASHSELXC2V_1 bit on VME Status Register
	cerr << "[VMESlot::LoadCpLcdFpgaFromFlash] Setting Flash Load Enable bit\n";
	FlashRAMLoad = 0x42600000;
	SetFlashRAMLoad(FlashRAMLoad);
	
	
	usleep(300000);
	
	// Check that flash loading is complete
	initMask = 0x00002000;
	
	NotDone = true;
	while(NotDone){
		if(GetFlashRAMStatus() & initMask)
			NotDone = false;
		else
			cerr << "[VMESlot::LoadCpLcdFpgaFromFlash] Waiting for load to complete.\n";
	}
	cerr << endl;
	
	
	
}

void VMESlot::LoadJemLcdFpgaFromFlash(void){
	
	u_int VMEConfig;
	u_int bitmask;
	u_int FlashRAMLoad;
	u_int initMask;
	bool NotDone;
	
	// Set FLASH_LOAD_SEL Bit on VME Config Register
	cerr << "[VMESlot::LoadJemLcdFpgaFromFlash] Setting Flash Load Select bit\n";
	VMEConfig=GetVMEConfig();
	
	// Set Flag for loading from flash
	bitmask = 0x00100000;
	VMEConfig &= ~bitmask;
	SetVMEConfig(VMEConfig);
	
	// Set FLASHSELXC2V_2 bit on VME Status Register
	cerr << "[VMESlot::LoadJemLcdFpgaFromFlash] Setting Flash Load Enable bit\n";
	
	FlashRAMLoad = 0x04680000;
	
	SetFlashRAMLoad(FlashRAMLoad);
	
	usleep(300000);
	
	initMask = 0x00000400;
	
	// Check that flash loading is complete
	NotDone = true;
	while(NotDone){
		if(GetFlashRAMStatus() & initMask)
			NotDone = false;
		else
			cerr << "[VMESlot::LoadJemLcdFpgaFromFlash] Waiting for load to complete.\n";
	}
	cerr << endl;
}


void VMESlot::ClearRemFPGA(void)
{
   unsigned int data32 = 0;
   
   cerr << "[VMESlot::ClearRemFPGA] Clearing REM FPGA.\n";
   
   // erase code
   WriteToAddress(FLASHLOADXIL,FLASHRESETXCVE);
   //usleep(300000);
  
   // wait until done
   while (1)
   {
      ReadFromAddress( VMESTATREG,data32);
      if ( ( data32 & XCVE_PRG_INIT ) )
         break;
   }
   
   
} 

void VMESlot::ClearLcdFPGAs(void){
	
	unsigned int data32 = 0;
   
  	
	cerr << "[VMESlot::ClearLcdFPGAs] Clearing LVDS board FPGAs.\n";
   
   WriteToAddress((u_int)FLASHLOADXIL,(u_int)FLASHRESETXC2V);
   //usleep(300000);
   
   // wait until done
   while (1)
   {
      ReadFromAddress( VMESTATREG,data32);
      if ( ( data32 & XCVE_PRG_INIT ) )
         break;
   }
   
}


//********************************************************************
//              xilGetShort
//********************************************************************
unsigned short VMESlot::xilGetShort ( unsigned char *ptr )
{
   unsigned short wert;
   unsigned char *wertptr = (unsigned char*)&wert;

   *wertptr = *(ptr+1);
   *(wertptr+1) = *ptr;

 return (wert);
}


//********************************************************************
//              xilGetInt
//********************************************************************
unsigned int VMESlot::xilGetInt ( unsigned char *ptr )
{
   unsigned int wert;
   unsigned char *wertptr = (unsigned char*)&wert;

   *(wertptr)   = *(ptr+3);
   *(wertptr+1) = *(ptr+2);
   *(wertptr+2) = *(ptr+1);
   *(wertptr+3) = *(ptr);

 return(wert);
} 


//********************************************************************
//              xilinxFromFileToFlash
//********************************************************************
bool VMESlot::xilinxFromFileToFlashOLD( char *bitfile, u_int flashLocation)
{
   register int i;
   register unsigned char k;
   unsigned char *p, *psav=0, data;
   unsigned short *p1, wert;
   unsigned long *p2;
   int size, path, filesize;
   unsigned int adr32, data32, sectoradr, sectorcnt;
   unsigned char data8;
	
	if( !(1 <= flashLocation && flashLocation <=6)){
		cerr << "[VMESlot::xilinxFromFileToFlash]: Flash Location must be 1 to 6.\n";
		return false;
	}
	
	// Get Flash Address
	u_int flashadr;
	switch(flashLocation){
	case 1:
		flashadr = FLASH_BASE_XCVE1;
		break;
	case 2:
		flashadr = FLASH_BASE_XCVE2;
		break;
	case 3:
		flashadr = FLASH_BASE_XCVE3;
		break;
	case 4:
		flashadr = FLASH_BASE_XCVE4;
		break;
	case 5:
		flashadr = FLASH_BASE_XCVE5;
		break;
	case 6:
		flashadr = FLASH_BASE_XCVE6;
		break;
	}

   if ( ( path = open( bitfile, O_RDONLY ) ) == -1 )
   {
      std::cerr << "[VMESlot::xilinxFromFileToFlash]: \tERROR! Cannot open " << bitfile << std::endl;
      return false;
   }

   if ( ( size = lseek( path, 0, 2 ) ) == -1 )
   {
      std::cerr << "[VMESlot::xilinxFromFileToFlash]: \tERROR! lseek can't get size " << bitfile << std::endl;
      return false;
   }

   filesize = size;
   if ( lseek( path, 0, 0 ) == -1 )
   {
      std::cerr << "[VMESlot::xilinxFromFileToFlash]: \tERROR! lseek can't go top of " << bitfile << std::endl;
      return false;
   }

   if ( ( p = (unsigned char*)malloc(size) ) == 0 )
   {
      std::cerr << "[VMESlot::xilinxFromFileToFlash]: \tERROR! Cannnot malloc "
                << size << " bytes for file " << bitfile << std::endl;
      return false;
   }

   psav = p;
   if ( read( path, p, size ) != size )
   {
      std::cerr << "[VMESlot::xilinxFromFileToFlash]: \tERROR! error in read file to memory " << bitfile << std::endl;
      return false;
   }

   if ( path )
           close( path );


   p1 = (unsigned short *) p;
   p += ( xilGetShort( (unsigned char*) p1 ) + 2 );
   p1 = (unsigned short *) p;
   p += ( xilGetShort( (unsigned char*) p1 ) + 1 );

   std::cout << "[VMESlot::xilinxFromFileToFlash]: Check Progamm Xilinx Header: " << "\n\t" << std::endl;

   for ( i=0; i < 4; i++ )
   {
      if ( *p != 0x61+i )
      {
         std::cerr << "[VMESlot::xilinxFromFileToFlash]: \tERROR! Bad Format in "
                   << bitfile << " " << (0x61+i) << " != " << *p << std::endl;
         free(psav);
         return false;
      }

      p++;
      p1 = (unsigned short *) p;
      std::cout << " " << p+2;
      p += ( xilGetShort( (unsigned char*) p1 ) + 2 );
   }
   std::cout << std::endl;


   if( *p != (0x61+i) )
   {
      std::cerr << "[VMESlot::xilinxFromFileToFlash]: \tERROR! Bad Format in "
                 << bitfile << " " << (0x61+i) << " != " << *p << std::endl;
      free(psav);
      return false;
   }


   p++;
   p2 = (unsigned long *) p;
   size = xilGetInt( ( unsigned char*) p2 );
   p += sizeof(long);


   for ( i=0; i < size; i++ )
   {
      data = 0;
      wert = *(p+i) << 7;
      for ( k=0x80; k > 0; k >>= 1 ) // swap bits 1->8, 2->7 usw.
      {
         data |= ( wert & k );
         wert >>= 2;
      }

      *(p+i) = data;
   }


   // Write Bitsream to Flashram
   //      vmewrite8(vmehandle, xildat, p, size, NOADDRINC);  Wr. to Xil no ADR inc 
   // Check Error and Reset XCVE

   //Flashram Reset
   data8 = 0x00;
   WriteToAddress( FLASHRAMRES,data8);
   usleep(10000);

   sectoradr = flashadr & 0xffff0000;

   if ( size % 0x10000 )
      sectorcnt = ( size / 0x10000 ) + 1;
   else
      sectorcnt = size / 0x10000;


   // Flashram Sector Erase
   unsigned int flashramLocation = ( ( flashadr & 0xf00000 ) >> 20 ) + 1;
   std::cerr << "[VMESlot::xilinxFromFileToFlash]:\tErasing the flashram location nr." << flashramLocation << " for the PPM in SlotNr " << slotNum << "..... ";

   for ( unsigned int m = 0; m < sectorcnt; m++ )
   {
      adr32 = 0xaaa;
      WriteToAddress(FLASHRAMADR,adr32);
      data8 = 0xaa;
      WriteToAddress(FLASHRAMDAT,data8);
      adr32 = 0x555;
      WriteToAddress(FLASHRAMADR,adr32);
      data8 = 0x55;
      WriteToAddress(FLASHRAMDAT,data8);
      adr32 = 0xaaa;
      WriteToAddress(FLASHRAMADR,adr32);
      data8 = 0x80;
      WriteToAddress(FLASHRAMDAT,data8);
      adr32 = 0xaaa;
      WriteToAddress(FLASHRAMADR,adr32);
      data8 = 0xaa;
      WriteToAddress(FLASHRAMDAT,data8);
      adr32 = 0x555;
      WriteToAddress(FLASHRAMADR,adr32);
      data8 = 0x55;
      WriteToAddress(FLASHRAMDAT,data8);

      //Sector to Erase
      adr32 = sectoradr + (m<<16);
      WriteToAddress(FLASHRAMADR,adr32);
      data8 = 0x30;
      WriteToAddress(FLASHRAMDAT,data8);
      std::cerr << "\n\tSector= " << m << "\tSectorNr= 0x" << hex << adr32 << dec;

      while( 1 ) // BUSY for ca. 0.5  sec !!!!
      {
         ReadFromAddress(FLASHSTATUS,data32);
         if ( ( data32 & 0x00000001 ) )
            break;

         usleep(10000);
      }
   }

   std::cerr << std::endl;
   std::cerr << "DONE!" << std::endl;


   // Flashram Program

   std::cerr << "[VMESlot::xilinxFromFileToFlash]:\tLoading <" << bitfile << "> in the flashramLocation nr." << flashramLocation << " of PPM in SlotNr " << slotNum << "..... ";
   std::cout << "\n\tWill download " << std::dec << size << " bytes ..." << std::endl;

   u_int onePercent = (u_int)(size*0.01);
   u_int tempAddr=0;
   u_char tempData8=0;
   for ( i=0; i < size; i++ )
   {
      if(!(i%(onePercent+1)))
          cerr << "\r Percent Done: " << (int)(i*100/size) << "\t";
	 

      adr32 = 0xaaa;
      WriteToAddress(FLASHRAMADR,adr32);
      data8 = 0xaa;
      WriteToAddress(FLASHRAMDAT,data8);
      adr32 = 0x555;
      WriteToAddress(FLASHRAMADR,adr32);
      data8 = 0x55;
      WriteToAddress(FLASHRAMDAT,data8);
      adr32 = 0xaaa;
      WriteToAddress(FLASHRAMADR,adr32);
      data8 = 0xa0;
      WriteToAddress(FLASHRAMDAT,data8);
      adr32 = flashadr+i;
      WriteToAddress(FLASHRAMADR,adr32);
      //usleep(50);
      data8 = *(p+i);
      //printf("adr=%08x dat=%02x\n", adr32, data8);
      WriteToAddress(FLASHRAMDAT,data8);
      //usleep(50);
      
      while( 1 )
      {
         ReadFromAddress(FLASHSTATUS,data32);
         if ( ( data32 & 0x00000001 ) )
            break;
      }
      
      ReadFromAddress(FLASHRAMADR,tempAddr);
      if(tempAddr != adr32)
          cerr << "[VMESlot::xilinxFromFileToFlash] Address readback not matched: 0x" << hex << adr32 << dec << "\n";
      
      ReadFromAddress(FLASHRAMDAT,tempData8);
      if(tempData8 != data8){
          cerr << "[VMESlot::xilinxFromFileToFlash] 8 bit Data readback not matched; Addr: 0x" << hex << adr32 << "; Data: 0x" << (u_int)data8 << dec
	  << "\n";
	  
          adr32 = 0xaaa;
          WriteToAddress(FLASHRAMADR,adr32);
          data8 = 0xaa;
          WriteToAddress(FLASHRAMDAT,data8);
          adr32 = 0x555;
          WriteToAddress(FLASHRAMADR,adr32);
          data8 = 0x55;
          WriteToAddress(FLASHRAMDAT,data8);
          adr32 = 0xaaa;
          WriteToAddress(FLASHRAMADR,adr32);
          data8 = 0xa0;
          WriteToAddress(FLASHRAMDAT,data8);
          adr32 = flashadr+i;
          WriteToAddress(FLASHRAMADR,adr32);
          //usleep(50);
          data8 = *(p+i);
          //printf("adr=%08x dat=%02x\n", adr32, data8);
          WriteToAddress(FLASHRAMDAT,data8);
          //usleep(50);
	  
	  ReadFromAddress(FLASHRAMADR,tempAddr);
          if(tempAddr != adr32)
              cerr << "[VMESlot::xilinxFromFileToFlash] 2nd Address readback not matched: 0x" << hex << adr32 << dec << "\n";
          
	  tempData8 = (u_char)0;
	  ReadFromAddress(FLASHRAMDAT,tempData8);
	  if(tempData8 != data8)
              cerr << "[VMESlot::xilinxFromFileToFlash] 2nd 8 bit Data readback not matched; Addr: 0x" << hex << adr32 << "; Data: 0x" <<
	      (u_int)data8 << dec
	  << "\n";
      }
      
      //if ( !(i % 10000) )
         //std::cout << "\n" << i << std::endl;
   }
   std::cerr << "DONE!" << std::endl;
   std::cout << "\nNr of bytes downloaded: " << i << "\n" << std::endl;

   if ( psav )
      free(psav);

 return true;
} 



//********************************************************************
//              xilinxFromFileToFlash
//********************************************************************
bool VMESlot::xilinxFromFileToFlashNEW(char *bitfile, uint flashLocation)
{
   register int i;
   register unsigned char k;
   unsigned char *p, *psav=0, data;
   unsigned short *p1, wert;
   unsigned long *p2;
   int m, n, size, path, filesize;
   unsigned int adr32, data32, sectoradr, sectorcnt, p_offset;
   unsigned char data8, endflag;

  	
	if( !(1 <= flashLocation && flashLocation <=6)){
		cerr << "[VMESlot::xilinxFromFileToFlash]: Flash Location must be 1 to 6.\n";
		return false;
	}
	
	// Get Flash Address
	u_int flashadr;
	switch(flashLocation){
	case 1:
		flashadr = FLASH_BASE_XCVE1;
		break;
	case 2:
		flashadr = FLASH_BASE_XCVE2;
		break;
	case 3:
		flashadr = FLASH_BASE_XCVE3;
		break;
	case 4:
		flashadr = FLASH_BASE_XCVE4;
		break;
	case 5:
		flashadr = FLASH_BASE_XCVE5;
		break;
	case 6:
		flashadr = FLASH_BASE_XCVE6;
		break;
	}

	 // get flash ram location
   	unsigned int flashLocNr = ( ( flashadr & 0x00f00000 ) >> 20 );
	ostringstream flashLocLabel;
	flashLocLabel.str("");


   switch ( flashLocNr )
   {
      case 0: flashLocLabel << "FIRST" ; break;
      case 1: flashLocLabel << "SECOND"; break;
      case 2: flashLocLabel << "THIRD" ; break;
      case 3: flashLocLabel << "FOURTH"; break;
      case 4: flashLocLabel << "FIFTH" ; break;
      case 5: flashLocLabel << "SIXTH" ; break;
   }


   if ( ( path = open( bitfile, O_RDONLY ) ) == -1 )
   {
      std::cerr << "[VMESlot::xilinxFromFileToFlash]: \tERROR! Cannot open " << bitfile << std::endl;
      return false;
   }

   if ( ( size = lseek( path, 0, 2 ) ) == -1 )
   {
      std::cerr << "[VMESlot::xilinxFromFileToFlash]: \tERROR! lseek can't get size " << bitfile << std::endl;
      return false;
   }

   filesize = size;
   if ( lseek( path, 0, 0 ) == -1 )
   {
      std::cerr << "[VMESlot::xilinxFromFileToFlash]: \tERROR! lseek can't go top of " << bitfile << std::endl;
      return false;
   }

   if ( ( p = (unsigned char*)malloc(size) ) == 0 )
   {
      std::cerr << "[VMESlot::xilinxFromFileToFlash]: \tERROR! Cannnot malloc "
                << size << " bytes for file " << bitfile << std::endl;
      return false;
   }

   psav = p;
   if ( read( path, p, size ) != size )
   {
      std::cerr << "[VMESlot::xilinxFromFileToFlash]: \tERROR! error in read file to memory " << bitfile << std::endl;
      return false;
   }

   if ( path )
           close( path );


   p1 = (unsigned short *) p;
   p += ( xilGetShort( (unsigned char*) p1 ) + 2 );
   p1 = (unsigned short *) p;
   p += ( xilGetShort( (unsigned char*) p1 ) + 1 );


   std::cout << "\tXilinx Bitfile: " << bitfile << std::endl;
   std::cout << "\tCheck Xilinx Header: " << std::endl;


   for ( i=0; i < 4; i++ )
   {
      if ( *p != 0x61+i )
      {
         std::cerr << "[VMESlot::xilinxFromFileToFlash]: \tERROR! Bad Format in "
                   << bitfile << " " << (0x61+i) << " != " << *p << std::endl;
         free(psav);
         return false;
      }

      p++;
      p1 = (unsigned short *) p;
      std::cout << " " << p+2;
      p += ( xilGetShort( (unsigned char*) p1 ) + 2 );
   }
   std::cout << std::endl;


   if( *p != (0x61+i) )
   {
      std::cerr << "[VMESlot::xilinxFromFileToFlash]: \tERROR! Bad Format in "
                 << bitfile << " " << (0x61+i) << " != " << *p << std::endl;
      free(psav);
      return false;
   }


   p++;
   p2 = (unsigned long *) p;
   size = xilGetInt( ( unsigned char*) p2 );
   p += sizeof(long);


   for ( i=0; i < size; i++ )
   {
      data = 0;
      wert = *(p+i) << 7;
      
      for ( k=0x80; k > 0; k >>= 1 ) // swap bits 1->8, 2->7 usw.
      {
         data |= ( wert & k );
         wert >>= 2;
      }
      

      *(p+i) = wert;
   }


   // Write Bitsream to Flashram
   //      vmewrite8(vmehandle, xildat, p, size, NOADDRINC);  Wr. to Xil no ADR inc 
   // Check Error and Reset XCVE

   //Flashram Reset
   SetATMEGA( (uint)'R');
   data8 = 0x00;
   WriteToAddress( FLASHRAMRES,data8);
   usleep(10000);

   sectoradr = flashadr & 0xffff0000;

   if ( size % 0x10000 )
      sectorcnt = ( size / 0x10000 ) + 1;
   else
      sectorcnt = size / 0x10000;




   std::cerr << "\n[VMESlot::xilinxFromFileToFlash]:\tPPM in SlotNr " << slotNum << std::endl;
   std::cerr << "\t* Loading bitfile <" << bitfile << "> in the " << flashLocLabel.str().c_str()
             << " location of the FlashRram;" << std::endl;
   std::cerr << "\t* erase & load sector by sector." << std::endl;


   for ( unsigned int i = 0; i < sectorcnt; i++ )
   {

      // Flashram Sector Erase
      SetATMEGA( (uint)'E');

      adr32 = 0xaaa;
      WriteToAddress(FLASHRAMADR,adr32);
      data8 = 0xaa;
      WriteToAddress(FLASHRAMDAT,data8);
      adr32 = 0x555;
      WriteToAddress(FLASHRAMADR,adr32);
      data8 = 0x55;
      WriteToAddress(FLASHRAMDAT,data8);
      adr32 = 0xaaa;
      WriteToAddress(FLASHRAMADR,adr32);
      data8 = 0x80;
      WriteToAddress(FLASHRAMDAT,data8);
      adr32 = 0xaaa;
      WriteToAddress(FLASHRAMADR,adr32);
      data8 = 0xaa;
      WriteToAddress(FLASHRAMDAT,data8);
      adr32 = 0x555;
      WriteToAddress(FLASHRAMADR,adr32);
      data8 = 0x55;
      WriteToAddress(FLASHRAMDAT,data8);
      
      //Sector to Erase
      adr32 = sectoradr + ( i << 16 );
      WriteToAddress(FLASHRAMADR,adr32);
      data8 = 0x30;
      WriteToAddress(FLASHRAMDAT,data8);
      std::cout << "\t\tSectorNr. " << i << ":\t" << std::hex << std::showbase << adr32 << std::dec << std::endl;
	
      usleep(500000);
      
      while( 1 ) // BUSY for ca. 0.5  sec !!!!
      {
         ReadFromAddress(FLASHSTATUS,data32);
         if ( ( data32 & 0x00000001 ) )
            break;

         usleep(10000);
      }

//    std::cerr << "DONE!" << std::endl;


      // Flashram Program

      SetATMEGA((uint)'L');

      endflag = 0;
      for ( m=0; m < 0x800; m++ ) // 0x800 * 32 Byte = 1 Sector = 64K to to FlashRamBuffer
      {
         adr32 = 0xaaa;
         WriteToAddress(FLASHRAMADR,adr32);
      	 data8 = 0xaa;
         WriteToAddress(FLASHRAMDAT,data8);
      	 adr32 = 0x555;
         WriteToAddress(FLASHRAMADR,adr32);
       	 data8 = 0x55;
         WriteToAddress(FLASHRAMDAT,data8);
      	 adr32 = sectoradr + (i << 16);
         WriteToAddress(FLASHRAMADR,adr32);
      	 data8 = 0x25;
         WriteToAddress(FLASHRAMDAT,data8);
      	 adr32 = sectoradr + (i << 16);
         WriteToAddress(FLASHRAMADR,adr32);
      	 data8 = 31; // n - 1 count in Buffer
         WriteToAddress(FLASHRAMDAT,data8);
      	 
         for ( n=0; n < 32; n++ ) // write 32 data to FlashRamBuffer
         {
            p_offset = (i << 16) + (m*32) + n;
            adr32 = flashadr + p_offset;
            WriteToAddress(FLASHRAMADR,adr32);
      	    
            if ( p_offset > (unsigned) size ) // check end of data in ptr p
            {
               data8 = 0xff;
               endflag = 1;
            }

            else
            {
               data8 = *(p + p_offset);
            }

            //printf("Flashdata = %02x\n", data8);
            WriteToAddress(FLASHRAMDAT,data8);
      	    
         }

         // write Buffer to FlashRam
         adr32 = sectoradr + (i << 16);
         WriteToAddress(FLASHRAMADR,adr32);
      	 data8 = 0x29;
         WriteToAddress(FLASHRAMDAT,data8);
      	 
	 usleep(500000);
         while(1) // BUSY wait for ready
         {
            ReadFromAddress(FLASHSTATUS,data32);
            if ( ( data32 & 0x00000001 ) )
                break;
         }

         if ( endflag )
            break;
      }
   }


   //std::cout << "\n" << i << std::endl;
   SetATMEGA( (uint)'D');
   std::cerr << "DONE!" << std::endl;

   if ( psav )
      free(psav);

 return true;
}


//********************************************************************
//              xilinxSoftLoader
//      (method to load f/w for only one PPM)
//********************************************************************
bool VMESlot::loadPprmFirmwareFromFile( char *bitfile, char xilpos)
{
   register int i;
   register unsigned char k;
   unsigned char *p, *psav=0, data8;
   unsigned short *p1, wert;
   unsigned long *p2;
   int size, path = 0;
   unsigned int data32;
   bool errflg = true;

   unsigned int xildat = 0;
   unsigned int xilprg = 0;

   if ( xilpos == XCVE )
   {
      xildat = XCVEPROGDAT;
      xilprg = XCVEREPROG;
   }


   if ( xilpos == XC2V_1 || xilpos == XC2V_1_1 )
   {
      xildat = XC2VPROGDAT1;
      xilprg = XC2VREPROG;
   }


   if ( xilpos == XC2V_2 || xilpos == XC2V_2_1 )
   {
      xildat = XC2VPROGDAT2;
      xilprg = XC2VREPROG;
   }

   if ( ( path = open( bitfile, O_RDONLY ) ) == -1 )
   {
      std::cerr << "[VMESlot::xilinxSoftLoader]: \tERROR! Cannot open " << bitfile << std::endl;
      return false;
   }


   if ( ( size = lseek(path, 0, 2) ) == -1 )
   {
      std::cerr << "[VMESlot::xilinxSoftLoader]: \tERROR! lseek can't get size " << bitfile << std::endl;
      return false;
   }


   if ( lseek(path, 0, 0) == -1 )
   {
      std::cerr << "[VMESlot::xilinxSoftLoader]: \tERROR! lseek can't go top of " << bitfile << std::endl;
      return false;
   }


   if ( ( p = (unsigned char*)malloc(size) ) == 0 )
   {
      std::cerr << "[VMESlot::xilinxSoftLoader]: \tERROR! Can't malloc " << size << " bytes for file " << bitfile << std::endl;
      return false;
   }


   psav = p;
   if ( read(path, p, size) != size )
   {
      std::cerr << "[VMESlot::xilinxSoftLoader]: \tERROR! error in read file to memory " << bitfile << std::endl;
      return false;
   }


   if ( path )
      close( path );


   data8 = 0;
   if ( xilpos == XCVE ) // Clear XCVE Xilinx
      WriteToAddress((unsigned int)xilprg,data8);

   if ( xilpos == XC2V_1 ) // Clear XC2V_1 & XC2V_2 Xilinx
      WriteToAddress((unsigned int)xilprg,data8);


   // Wait Xilinx Ready
   while (1)
   {
      ReadFromAddress((unsigned int)VMESTATREG,data32);
      if ( xilpos == XCVE )
      {
         if ( ( data32 & XCVE_PRG_INIT ) )
            break;
      }

      if ( xilpos == XC2V_1 || xilpos == XC2V_1_1 )
      {
         if ( data32 & XC2V_PRG_INIT1 )
            break;
      }

      if ( xilpos == XC2V_2 || xilpos == XC2V_2_1 )
      {
         if ( data32 & XC2V_PRG_INIT2 )
            break;
      }
   }


   p1 = (unsigned short *) p;
   p += ( xilGetShort( (unsigned char*) p1 ) + 2 );
   p1 = (unsigned short *) p;
   p += (xilGetShort( (unsigned char*) p1 ) + 1 );

   cerr << "\t\tProgram Xilinx: ";
   for ( i=0; i < 4; i++ )
   {
      if( *p != (0x61+i) )
      {
         std::cerr << "[VMESlot::xilinxSoftLoader]: \tERROR! Bad Format in "
                   << bitfile << " " << (0x61+i) << " != " << *p << std::endl;
         free(psav);
         return false;
      }

      p++;
      p1 = (unsigned short *) p;
      cerr << " ";
      cerr << (const char*) (p+2);
      p += ( xilGetShort( (unsigned char*) p1 ) + 2 );
   }
   cerr << "\n";

   if ( *p != (0x61+i) )
   {
      std::cerr << "[VMESlot::xilinxSoftLoader]: \tERROR! Bad Format in "
                << bitfile << " " << (0x61+i) << " != " << *p << std::endl;
      free(psav);
      return false;
   }


   p++;
   p2 = (unsigned long *) p;
   size = xilGetInt( (unsigned char*) p2 );
   p += sizeof(long);

   for ( i=0; i < size; i++ )
   {
      data8 = 0;
      wert = *(p+i) << 7;
      for ( k=0x80; k > 0; k >>= 1) // swap bits 1->8, 2->7 usw.
      {
         data8 |= (wert & k);
         wert >>= 2;
      }

      *(p+i) = data8;
   }


   // Write Bitstream to Xilinx
   for(int i=0;i<size;i++)
   	WriteToAddress((unsigned int)xildat,*(p+i)); // Wr. to Xil no ADR inc


   // Check Error and Reset XCVE
   if ( xilpos == XCVE )
   {
      // Hardware Reset XCVE on
      ReadFromAddress((unsigned int)VMECONFREG,data32);
      data32 |= XCVERESET;
      WriteToAddress((unsigned int)VMECONFREG,data32);
      // Wait 20ms
      usleep(20000);

      // Check Error
      ReadFromAddress((unsigned int)VMESTATREG,data32);

      if ( ( data32 & XCVE_PRG_INIT ) == 0)
      {
              std::cerr << "[VMESlot::xilinxSoftLoader] \tERROR! XCVE_PRG_INIT ERROR XILINX DOWNLOAD !!!!" << std::endl;
              errflg = false;
      }

      if ( ( data32 & XCVE_PRG_DONE ) == 0)
      {
              std::cerr << "[VMESlot::xilinxSoftLoader] \tERROR! XCVE_PRG_DONE XILINX DOWNLOAD !!!!" << std::endl;
              errflg = false;
      }

      // Hardware Reset XCVE off
      ReadFromAddress((unsigned int)VMECONFREG,data32);
      data32 &= ~XCVERESET;
      WriteToAddress((unsigned int)VMECONFREG,data32);
   }

   else if ( xilpos == XC2V_1 )
   {
      usleep(20000);
      ReadFromAddress((unsigned int)VMESTATREG,data32);
      if ( ( data32 & XC2V_PRG_INIT1 ) == 0 )
      {
         std::cerr << "[VMESlot::xilinxSoftLoader] \tERROR! XC2V_PRG_INIT1 ERROR XILINX DOWNLOAD !!!!" << std::endl;
         errflg = false;
      }
   }

   else if ( xilpos == XC2V_1_1 )
   {
      usleep(20000);
      ReadFromAddress((unsigned int)VMESTATREG,data32);
      if ( ( data32 & XC2V_PRG_INIT1 ) == 0 )
      {
              std::cerr << "[VMESlot::xilinxSoftLoader] \tERROR! XC2V_PRG_INIT1 ERROR XILINX DOWNLOAD !!!!" << std::endl;
              errflg = false;
      }

      if ( ( data32 & XC2V_PRG_DONE1 ) == 0 )
      {
              std::cerr << "[VMESlot::xilinxSoftLoader] \tERROR! XC2V_PRG_DONE1 ERROR XILINX DOWNLOAD !!!!" << std::endl;
              errflg = false;
      }
   }

   else if ( xilpos == XC2V_2 )
   {
      usleep(20000);
      ReadFromAddress((unsigned int)VMESTATREG,data32);
      if ( ( data32 & XC2V_PRG_INIT2 ) == 0 )
      {
         std::cerr << "[VMESlot::xilinxSoftLoader] \tERROR! XC2V_PRG_INIT2 ERROR XILINX DOWNLOAD !!!!" << std::endl;
         errflg = false;
      }
   }

   else if ( xilpos == XC2V_2_1 )
   {
      usleep(20000);
      ReadFromAddress((unsigned int)VMESTATREG,data32);
      
      if ( ( data32 & XC2V_PRG_INIT2 ) == 0 )
      {
         std::cerr << "[VMESlot::xilinxSoftLoader] \tERROR! XC2V_PRG_INIT2 ERROR XILINX DOWNLOAD !!!!" << std::endl;
         errflg = false;
      }

      if ( ( data32 & XC2V_PRG_DONE2 ) == 0 )
      {
         std::cerr << "[VMESlot::xilinxSoftLoader] \tERROR! XC2V_PRG_DONE2 ERROR XILINX DOWNLOAD !!!!" << std::endl;
         errflg = false;
      }
   }


   if ( !errflg )
      std::cerr << "[VMESlot::xilinxSoftLoader] \tERROR! Xilinx Download %s !!!\n" << bitfile << std::endl;
   else
      cerr << "\t\tOK Xilinx Download!\n";

   if( psav )
      free( psav );

 return ( errflg );
} 
