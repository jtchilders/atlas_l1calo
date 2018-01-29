////////////////////////////////////////////////////////////////
/// L1Calo Channel Mapping Tool
/// J Taylor Childers III
/// Heidelberg Universitaet
///
/// This class decodes/encodes L1Calo COOL channel IDs following
/// the following convention:
/// 
/// Copied from coolL1Calo/src/CoolChannelId.cxx
///   \class CoolChannelId
///  Encapsulates the ID of one channel of conditions data in COOL,
///  ie the ID of a row in a table.
///
///  At present, COOL can only handle integer IDs, so we encode
///  crate, module type, module in crate, submodule, and channel
///  with module or submodule into a 32 bit quantity as follows:
///  - bits 31-24 crate number (0-7=PP, 8-11=CP, 12-13=JEP, 14-15=ROD)
///  - bits 23-20 module type (1=PPM, 2=CPM, 3=JEM, 4=CMM, 5=TCM, 6=ROD)
///  - bits 19-16 module number in crate
///  - bits 15-08 submodule number in module (if appropriate)
///  - bits 07-00 channel number in (sub)module (if appropriate)
///
///  The class can be initialized with no input, with a COOL ID directly,
///  or using hardware information:
///  For PPM:
///     MODULE_TYPE::PPM
///     Crate 0-7
///     Module 0-15
///     Submodule 0-3
///     Channel 0-3
///  For CPM:
///     MODULE_TYPE::CPM
///     Crate 8-11
///     Module 1-14
///    Using CPM CP Chip:
///     Submodule 0-7
///     Channel 0-15
///    Using CPM Serializer:
///     Submodule 0-19
///     Channel 0-8
///  For JEM:
///     MODULE_TYPE::JEM
///     Crate 12-13
///     Module 0-15
///     Channel 0-87
///  For CMM,TCM,ROD:
///     Not Yet Implemented
///  For TCPP:
///     MODULE_TYPE::TCPP
///     Crate 0-3
///     Module 0-15
///    Using output connector:
///     Submodule 0-2
///     Channel 0-14
///    Using input connector:
///     Submodule 0-3
///     Channel 0-8
///
///  If the class is initialize with no input the ID is set to 0,
///  which is an invalid channel ID. In this case, the ID must be
///  later initialized with the SetChannelId() functions.
///
///  Once the class is initialized, the GetId() function returns
///  the real binary id. There are also get functions for the hardware
///  address numbers.
///
///  For the PPM there is a GetLogicalChannel() function which returns
///  a channel number from 0-63. It returns 0 for all other MODULE_TYPE.
///
///  The GetIdAsString() and GetTypeAsString() return a string with the
///  MODULE_TYPE's ("PPM","CPM",JEM","CMM",TCM","ROD","TCPP")
///  or ID in the format: "0x%08x"
//////////////////////////////////////////////////////////////////


#ifndef L1CALOCHANNELID_H
#define L1CALOCHANNELID_H

#include <string>
#include <cstdio>
#include <iostream>


class L1CaloChannelId{
public:
   
   enum MODULE_TYPE{
      TYPE_NOT_SET = 0,
      PPM          = 1,
      CPM          = 2,
      JEM          = 3,
      CMM          = 4,
      TCM          = 5,
      ROD          = 6,
      TCPP         = 7
   };
   
   L1CaloChannelId(void):m_id(0){};
   L1CaloChannelId(const unsigned int id):m_id(id) {};
   L1CaloChannelId(const MODULE_TYPE type,const unsigned int crate,const unsigned int module,const unsigned int submodule,const unsigned int channel){
      SetChannelId(type,crate,module,submodule,channel);
   };
   
   void SetChannelId(const unsigned int id);
   void SetChannelId(const MODULE_TYPE type,const unsigned int crate,const unsigned int module,const unsigned int submodule,const unsigned int channel);
   
   unsigned int GetId(void) const {return m_id;};
   
   unsigned int GetCrate(void) const {return (m_id >> 24) & 0xff;};
   MODULE_TYPE GetModuleType(void) const {return (MODULE_TYPE)((m_id >> 20) & 0xf);};
   unsigned int GetModule(void) const {return (m_id >> 16) & 0xf;};
   unsigned int GetSubmodule(void) const {return (m_id >> 8) & 0xff;};
   unsigned int GetChannel(void) const {return (m_id & 0xff);};
   
   unsigned int GetLogicalChannel(void) const;
   
   std::string GetIdAsString(void) const {char temp[40];sprintf(temp,"%08x",m_id);return std::string(temp);};
   std::string GetTypeAsString(void) const;
   
   void Clear(void){m_id = 0;};
   
private:
   unsigned int m_id;
   
   bool IdOk(void) const;
   
   // PPM Hardware Limits
   static const unsigned int PPM_MAX_CRATE = 7;
   static const unsigned int PPM_MIN_CRATE = 0;
   
   static const unsigned int PPM_MAX_MODULE = 15;
   static const unsigned int PPM_MIN_MODULE = 0;
   
   static const unsigned int PPM_MAX_SUBMODULE = 15;
   static const unsigned int PPM_MIN_SUBMODULE = 0;
   
   static const unsigned int PPM_MAX_CHANNEL = 3;
   static const unsigned int PPM_MIN_CHANNEL = 0;
   
   // CPM Hardware Limits
   static const unsigned int CPM_MAX_CRATE = 11;
   static const unsigned int CPM_MIN_CRATE = 8;
   
   static const unsigned int CPM_MAX_MODULE = 14;
   static const unsigned int CPM_MIN_MODULE = 1;
   // CPM has two different ways to number the SUBMODULE and CHANNEL
   static const unsigned int CPM_MAX_SUBMODULE_CHIP = 7;
   static const unsigned int CPM_MIN_SUBMODULE_CHIP = 0;
   
   static const unsigned int CPM_MAX_CHANNEL_CHIP = 15;
   static const unsigned int CPM_MIN_CHANNEL_CHIP = 0;
   
   static const unsigned int CPM_MAX_SUBMODULE_SERIAL = 19;
   static const unsigned int CPM_MIN_SUBMODULE_SERIAL = 0;
   
   static const unsigned int CPM_MAX_CHANNEL_SERIAL = 8;
   static const unsigned int CPM_MIN_CHANNEL_SERIAL = 0;
   
   // JEM Hardware Limits
   static const unsigned int JEM_MAX_CRATE = 13;
   static const unsigned int JEM_MIN_CRATE = 12;
   
   static const unsigned int JEM_MAX_MODULE = 15;
   static const unsigned int JEM_MIN_MODULE = 0;
   
   static const unsigned int JEM_MAX_CHANNEL = 87;
   static const unsigned int JEM_MIN_CHANNEL = 0;
   
   // CMM Hardware Limits
   static const unsigned int CMM_MAX_MODULE = 1;
   static const unsigned int CMM_MIN_MODULE = 0;
   
   // static const unsigned int CMM_MAX_SUBMODULE = 15;
   // static const unsigned int CMM_MIN_SUBMODULE = 0;
   
   // static const unsigned int CMM_MAX_CHANNEL = 3;
   // static const unsigned int CMM_MIN_CHANNEL = 0;
   
   // TCM Hardware Limits
   // static const unsigned int TCM_MAX_CRATE = 8;
   // static const unsigned int TCM_MIN_CRATE = 11;
   
   // static const unsigned int TCM_MAX_MODULE = 14;
   // static const unsigned int TCM_MIN_MODULE = 1;
   
   // static const unsigned int TCM_MAX_SUBMODULE = 15;
   // static const unsigned int TCM_MIN_SUBMODULE = 0;
   
   // static const unsigned int TCM_MAX_CHANNEL = 3;
   // static const unsigned int TCM_MIN_CHANNEL = 0;
   
   // ROD Hardware Limits
   static const unsigned int ROD_MAX_CRATE = 14;
   static const unsigned int ROD_MIN_CRATE = 15;
   
   // static const unsigned int ROD_MAX_MODULE = 14;
   // static const unsigned int ROD_MIN_MODULE = 1;
   
   // static const unsigned int ROD_MAX_SUBMODULE = 15;
   // static const unsigned int ROD_MIN_SUBMODULE = 0;
   
   // static const unsigned int ROD_MAX_CHANNEL = 3;
   // static const unsigned int ROD_MIN_CHANNEL = 0;
   
   static const unsigned int TCPP_MAX_CRATE = 3;
   static const unsigned int TCPP_MIN_CRATE = 0;
   
   static const unsigned int TCPP_MAX_MODULE = 15;
   static const unsigned int TCPP_MIN_MODULE = 0;
   
   static const unsigned int TCPP_MAX_OUTPUT_CONNECTOR = 2;
   static const unsigned int TCPP_MIN_OUTPUT_CONNECTOR = 0;
   
   static const unsigned int TCPP_MAX_OUTPUT_CHANNEL = 14;
   static const unsigned int TCPP_MIN_OUTPUT_CHANNEL = 0;
   
   static const unsigned int TCPP_MAX_INPUT_CONNECTOR = 3;
   static const unsigned int TCPP_MIN_INPUT_CONNECTOR = 0;
   
   static const unsigned int TCPP_MAX_INPUT_CHANNEL = 8;
   static const unsigned int TCPP_MIN_INPUT_CHANNEL = 0;
   
};

#endif

