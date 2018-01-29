#ifndef PPRMDEFS_H
#define PPRMDEFS_H

#define CRATE_BASE 0xC0000000
#define SLOT_5 0x02800000

#define SLOT_SIZE 0x00800000

//---------------------------------
//         PPRM DEFINES
//---------------------------------

// XILINX POS.
#define XCVE               0x00
#define XC2V_1             0x01
#define XC2V_2             0x02
#define XC2V_1_1           0x03
#define XC2V_2_1           0x04

// VME StatusReg Masks
#define	XCVE_PRG_INIT      0x00002000
#define	XCVE_PRG_DONE      0x00001000
#define	XC2V_PRG_INIT1     0x00000800
#define	XC2V_PRG_DONE1     0x00000400
#define	XC2V_PRG_INIT2     0x00000200
#define	XC2V_PRG_DONE2     0x00000100

// VME ConfigReg Masks
#define PWRONOFF           0x80000000
#define XCVERESET          0x40000000
#define ATMEGARESET        0x20000000
#define JTAGENABLE         0x10000000
#define JTAGRST            0x08000000
#define JTAGTMS            0x04000000
#define JTAGTDO            0x02000000
#define JTAGTCK            0x01000000
#define VMECANPRGSEL       0x00800000
#define VMECANRESET        0x00400000
#define CONFIGFREE         0x00200000
#define VMEXILINXLOAD      0x00100000

// FLASH StatusReg Masks
#define FLASHXCVEINIT      0x00008000
#define FLASHXCVEDONE      0x00004000
#define FLASHXC2VINIT1     0x00002000
#define FLASHXC2VDONE1_0   0x00001000
#define FLASHXC2VDONE1     0x00000800
#define FLASHXC2VINIT2     0x00000400
#define FLASHXC2VDONE2_0   0x00000200
#define FLASHXC2VDONE2     0x00000100
#define FLASHXCVE_OK       0x00000080
#define FLASHXC2V1_OK      0x00000040
#define FLASHXC2V2_OK      0x00000020
#define FLASHXILPRGBUSY    0x00000010
#define FLASHFREE2         0x00000008
#define FLASHFREE3         0x00000004
#define FLASHPRGXILBUSY    0x00000002
#define FLASHRAMBUSY       0x00000001

// FLASHLOADXILINX
#define FLASHRESETXCVE     0x80000000
#define FLASHRESETXC2V     0x40000000
#define FLASHSELXCVE       0x01000000
#define FLASHSELXC2V_1     0x02000000
#define FLASHSELXC2V_2     0x04000000

// RESET XILINXE
#define RES_XCVE           0x80000000
#define RES_XC2V           0x40000000

// RESET & PROGRAM XCVE
#define RES_PRG_XCVE1      0x81000000
#define RES_PRG_XCVE2      0x81100000
#define RES_PRG_XCVE3      0x81200000
#define RES_PRG_XCVE4      0x81300000
#define RES_PRG_XCVE5      0x81400000
#define RES_PRG_XCVE6      0x81500000
// RESET XC2V1/2 & PROGRAM XC2V1 (CP1 & CP2)
#define RES_PRG_XC2V1_0    0x42600000
#define RES_PRG_XC2V1_1    0x42640000
// PROGRAM XCVE (CP1 CP2)
#define PRG_XC2V1_0        0x04600000
#define PRG_XC2V1_1        0x04640000
// PROGRAM XC2V2 (JP1 JP2)
#define PRG_XC2V2_0         0x04680000
#define PRG_XC2V2_1         0x046C0000


// FLASH BASE ADDRESSES for XCVE
#define FLASH_BASE_XCVE1    0x00000000
#define FLASH_BASE_XCVE2    0x00100000
#define FLASH_BASE_XCVE3    0x00200000
#define FLASH_BASE_XCVE4    0x00300000
#define FLASH_BASE_XCVE5    0x00400000
#define FLASH_BASE_XCVE6    0x00500000
// FLASH BASE ADDRESSES for XC2V1's (CP1 & CP2)
#define FLASH_BASE_XC2V1_0  0x00600000
#define FLASH_BASE_XC2V1_1  0x00640000
// FLASH BASE ADDRESSES for XC2V1's (JP1 & JP2)
#define FLASH_BASE_XC2V2_0  0x00680000
#define FLASH_BASE_XC2V2_1  0x006C0000


//---------------------------------
// CPLD Register Address mapping
//---------------------------------

// XCR3256XL (FLASHLOADER CPLD)
#define MODULE_ID           0x00000000
#define FLASHRAMADR         0x00010000
#define FLASHRAMDAT         0x00020003
#define FLASHRAMRES         0x00030003
#define FLASHLOADXIL        0x00040000
#define FLASHSTATUS         0x00050000
// XC95288XL (VME CPLD)
#define VMECONFREG          0x00100000
#define VMESTATREG          0x00110000
#define XCVEREPROG          0x00120003
#define XCVEPROGDAT         0x00130003
#define XC2VREPROG          0x00140003
#define XC2VPROGDAT1        0x00150003
#define XC2VPROGDAT2        0x00160003
#define ATMEGA              0x00170000


// Register of REM Firmware Version
#define XCVEVERSION         0x007fffd0

//***** ReM FPGA (Xilinx) Address mapping
#define XCVEBASE            0x00200000

#define XCVESRAM            0x00200000
#define XCVESRAM_MAX        0x005ffffC

//***** FPGA Register Address mapping

// ASIC readout blocks: 512 entries/SerInterface
// xxx1_0000_0000_0000_00mm_mmrr; m=mcm, r=readout channels
// xxx100_0000_0000_0000_mmmm_rr00; m=mcm, r=readout channels
// addresses for MCM#1 : 0x100000:ROB1_status, 0x100001:ROB1
//                       0x100002:ROB2_status, 0x100003:ROB2
#define RO_BLOCK_BASE       0x00600000

#define ROSTATE_1_OFF       0x00000000
#define ROBLOCK_1_OFF       0x00000001
#define ROSTATE_2_OFF       0x00000002
#define ROBLOCK_2_OFF       0x00000003

//DLL+PHOS4 status bits
#define PPMSTAT             0x007FFEFC

#define ROFIFOCTRL          0x007FFFd8
#define GENPULSE            0x007FFF84
#define LOCALTRIG           0x007FFF80

#define ANIN4_H             0x007FFF34
#define ANIN4_L             0x007FFF30
#define ANIN3_H             0x007FFF24
#define ANIN3_L             0x007FFF20
#define ANIN2_H             0x007FFF14
#define ANIN2_L             0x007FFF10
#define ANIN1_H             0x007FFF04
#define ANIN1_L             0x007FFF00


#define MCM_01              0x00200000
#define MCM_02              0x00202000
#define MCM_03              0x00204000
#define MCM_04              0x00206000
#define MCM_05              0x00208000
#define MCM_06              0x0020A000
#define MCM_07              0x0020C000
#define MCM_08              0x0020E000
#define MCM_09              0x00210000
#define MCM_10              0x00212000
#define MCM_11              0x00214000
#define MCM_12              0x00216000
#define MCM_13              0x00218000
#define MCM_14              0x0021A000
#define MCM_15              0x0021C000
#define MCM_16              0x0021E000

#define TTCRX               0x00220000


//***** MCM Funktion Offsets

#define DAC_1               0x00
#define DAC_2               0x01
#define DAC_3               0x02
#define DAC_4               0x03
#define PHOS4_1             0x04
#define PHOS4_2             0x05
#define PHOS4_3             0x06
#define PHOS4_4             0x07


//---------------------------------
//      PPRM BOARD STRUCT
//---------------------------------

typedef struct pprm {
unsigned int                baseadr;
volatile unsigned int       *module_id; // XCR3256XL Registers
volatile unsigned int       *flashramadr;
volatile unsigned int       *flashramdat;
volatile unsigned int       *flashramres;
volatile unsigned int       *flashloadxil;
volatile unsigned int       *flashstatus;
volatile unsigned int       *vmeconfreg;  // XC95288XL Registers
volatile unsigned int       *vmestatreg;
volatile unsigned int       *xcvereprog;
volatile unsigned int       *xcveprogdat;
volatile unsigned int       *xc2vreprog;
volatile unsigned int       *xc2vprogdat1;
volatile unsigned int       *xc2vprogdat2;
volatile unsigned int       *atmega;
volatile unsigned int       *xcvebase;
volatile unsigned int       *xcvesram;
volatile unsigned int       *xcvesram_max;
volatile unsigned int       *ro_block_base;
volatile unsigned int       *ppmstat;
volatile unsigned int       *mcm_01;
volatile unsigned int       *mcm_02;
volatile unsigned int       *mcm_03;
volatile unsigned int       *mcm_04;
volatile unsigned int       *mcm_05;
volatile unsigned int       *mcm_06;
volatile unsigned int       *mcm_07;
volatile unsigned int       *mcm_08;
volatile unsigned int       *mcm_09;
volatile unsigned int       *mcm_10;
volatile unsigned int       *mcm_11;
volatile unsigned int       *mcm_12;
volatile unsigned int       *mcm_13;
volatile unsigned int       *mcm_14;
volatile unsigned int       *mcm_15;
volatile unsigned int       *mcm_16;
volatile unsigned int       *ttcrx;
volatile unsigned int       *anin1_l;
volatile unsigned int       *anin1_h;
volatile unsigned int       *anin2_l;
volatile unsigned int       *anin2_h;
volatile unsigned int       *anin3_l;
volatile unsigned int       *anin3_h;
volatile unsigned int       *anin4_l;
volatile unsigned int       *anin4_h;
volatile unsigned int       *rofifoctrl;
volatile unsigned int       *localtrig;
volatile unsigned int       *genpulse;
} PPRM;

#endif // PPRMDEFS_H
