#include "L1CaloChannelId.h"

void L1CaloChannelId::SetChannelId(const unsigned int id){
   m_id = id;
   
   if(!IdOk()){
      std::cerr << "L1CaloChannelId::SetChannelId: ERROR id has incorrect values. setting it to zero.\n";
      m_id = 0;
   }
   
};

void L1CaloChannelId::SetChannelId(const MODULE_TYPE type,const unsigned int crate,const unsigned int module,const unsigned int submodule,const unsigned int channel){
   
   m_id = ((crate & 0xff) << 24) | ((type & 0xf) << 20) | ((module & 0xf) << 16) | ((submodule & 0xff) << 8) | (channel & 0xff);
   
   if(!IdOk()){
      std::cerr << "L1CaloChannelId::SetChannelId: ERROR id has incorrect values. setting it to zero.\n";
      m_id = 0;
   }
   
};

std::string L1CaloChannelId::GetTypeAsString(void) const{
   MODULE_TYPE type = GetModuleType();
   if(type == PPM)
      return "PPM";
   else if(type == CPM)
      return "CPM";
   else if(type == JEM)
      return "JEM";
   else if(type == CMM)
      return "CMM";
   else if(type == TCM)
      return "TCM";
   else if(type == ROD)
      return "ROD";
   else if(type == TCPP)
      return "TCPP";
   
   return "TYPE_NOT_SET";
}

bool L1CaloChannelId::IdOk(void) const{
   
   switch(GetModuleType()){
   
   case PPM:
      if( !(PPM_MIN_CRATE <= GetCrate() && GetCrate() <= PPM_MAX_CRATE) ){
         std::cerr << "L1CaloChannelId::SetChannelId: ERROR PPM Crate value, " << GetCrate() << ", outside allowable range " << PPM_MIN_CRATE << " to " << PPM_MAX_CRATE << ".\n";
         return false;
      }
      if( !(PPM_MIN_MODULE <= GetModule() && GetModule() <= PPM_MAX_MODULE) ){
         std::cerr << "L1CaloChannelId::SetChannelId: ERROR PPM Module value, " << GetModule() << ", outside allowable range " << PPM_MIN_MODULE << " to " << PPM_MAX_MODULE << ".\n";
         return false;
      }
      if( !(PPM_MIN_SUBMODULE <= GetSubmodule() && GetSubmodule() <= PPM_MAX_SUBMODULE) ){
         std::cerr << "L1CaloChannelId::SetChannelId: ERROR PPM Submodule value, " << GetSubmodule() << ", outside allowable range " << PPM_MIN_SUBMODULE << " to " << PPM_MAX_SUBMODULE << ".\n";
         return false;
      }
      if( !(PPM_MIN_CHANNEL <= GetChannel() && GetChannel() <= PPM_MAX_CHANNEL) ){
         std::cerr << "L1CaloChannelId::SetChannelId: ERROR PPM Channel value, " << GetChannel() << ", outside allowable range " << PPM_MIN_CHANNEL << " to " << PPM_MAX_CHANNEL << ".\n";
         return false;
      }
      return true;
      break;
   
   case CPM:
      if( !(CPM_MIN_CRATE <= GetCrate() && GetCrate() <= CPM_MAX_CRATE) ){
         std::cerr << "L1CaloChannelId::SetChannelId: ERROR CPM Crate value, " << GetCrate() << ", outside allowable range " << CPM_MIN_CRATE << " to " << CPM_MAX_CRATE << ".\n";
         return false;
      }
      if( !(CPM_MIN_MODULE <= GetModule() && GetModule() <= CPM_MAX_MODULE) ){
         std::cerr << "L1CaloChannelId::SetChannelId: ERROR CPM Module value, " << GetModule() << ", outside allowable range " << CPM_MIN_MODULE << " to " << CPM_MAX_MODULE << ".\n";
         return false;
      }
      if( !(CPM_MIN_SUBMODULE_CHIP <= GetSubmodule() && GetSubmodule() <= CPM_MAX_SUBMODULE_CHIP) && 
          !(CPM_MIN_SUBMODULE_SERIAL <= GetSubmodule() && GetSubmodule() <= CPM_MAX_SUBMODULE_SERIAL) ){
         std::cerr << "L1CaloChannelId::SetChannelId: ERROR CPM Submodule value, " << GetSubmodule() << ", outside allowable range " << CPM_MIN_SUBMODULE_CHIP << " to " << CPM_MAX_SUBMODULE_CHIP << " for Chip counting, or " << CPM_MIN_SUBMODULE_SERIAL << " to " << CPM_MAX_SUBMODULE_SERIAL << " for Serial counting.\n";
         return false;
      }
      if( !(CPM_MIN_CHANNEL_CHIP <= GetChannel() && GetChannel() <= CPM_MAX_CHANNEL_CHIP) && 
          !(CPM_MIN_CHANNEL_SERIAL < GetChannel() && GetChannel() <=  CPM_MAX_CHANNEL_SERIAL) ){
         std::cerr << "L1CaloChannelId::SetChannelId: ERROR CPM Channel value, " << GetChannel() << ", outside allowable range " << CPM_MIN_CHANNEL_CHIP << " to " << CPM_MAX_CHANNEL_CHIP << " for Chip counting, or " << CPM_MIN_CHANNEL_SERIAL << " to " << CPM_MAX_CHANNEL_SERIAL << " for Serial counting.\n";
         return false;
      }
      return true;
      break;
   
   case JEM:
      if( !(JEM_MIN_CRATE <= GetCrate() && GetCrate() <= JEM_MAX_CRATE) ){
         std::cerr << "L1CaloChannelId::SetChannelId: ERROR JEM Crate value, " << GetCrate() << ", outside allowable range " << JEM_MIN_CRATE << " to " << JEM_MAX_CRATE << ".\n";
         return false;
      }
      if( !(JEM_MIN_MODULE <= GetModule() && GetModule() <= JEM_MAX_MODULE) ){
         std::cerr << "L1CaloChannelId::SetChannelId: ERROR JEM Module value, " << GetModule() << ", outside allowable range " << JEM_MIN_MODULE << " to " << JEM_MAX_MODULE << ".\n";
         return false;
      }
      if( !(JEM_MIN_CHANNEL <= GetChannel() && GetChannel() <= JEM_MAX_CHANNEL) ){
         std::cerr << "L1CaloChannelId::SetChannelId: ERROR JEM Channel value, " << GetChannel() << ", outside allowable range " << JEM_MIN_CHANNEL << " to " << JEM_MAX_CHANNEL << ".\n";
         return false;
      }
      return true;
      break;
   case TCPP:
      if( !(TCPP_MIN_CRATE <= GetCrate() && GetCrate() <= TCPP_MAX_CRATE) ){
         std::cerr << "L1CaloChannelId::SetChannelId: ERROR TCPP Crate value, " << GetCrate() << ", outside allowable range " << TCPP_MIN_CRATE << " to " << TCPP_MAX_CRATE << ".\n";
         return false;
      }
      if( !(TCPP_MIN_MODULE <= GetModule() && GetModule() <= TCPP_MAX_MODULE) ){
         std::cerr << "L1CaloChannelId::SetChannelId: ERROR TCPP Module value, " << GetModule() << ", outside allowable range " << TCPP_MIN_MODULE << " to " << TCPP_MAX_MODULE << ".\n";
         return false;
      }
      if( !(TCPP_MIN_OUTPUT_CONNECTOR <= GetSubmodule() && GetSubmodule() <= TCPP_MAX_OUTPUT_CONNECTOR) &&
          !(TCPP_MIN_INPUT_CONNECTOR <= GetSubmodule() && GetSubmodule() <= TCPP_MAX_INPUT_CONNECTOR) ){
         std::cerr << "L1CaloChannelId::SetChannelId: ERROR TCPP Submodule value, " << GetSubmodule() << ", outside allowable range " << TCPP_MIN_OUTPUT_CONNECTOR << " to " << TCPP_MAX_OUTPUT_CONNECTOR << " for output connector counting, or " << TCPP_MIN_INPUT_CONNECTOR << " to " << TCPP_MAX_INPUT_CONNECTOR << " for input connector counting.\n";
         return false;
      }
      if( !(TCPP_MIN_OUTPUT_CHANNEL <= GetChannel() && GetChannel() <= TCPP_MAX_OUTPUT_CHANNEL) && 
          !(TCPP_MIN_INPUT_CHANNEL < GetChannel() && GetChannel() <=  TCPP_MAX_INPUT_CHANNEL) ){
         std::cerr << "L1CaloChannelId::SetChannelId: ERROR CPM Channel value, " << GetChannel() << ", outside allowable range " << TCPP_MAX_OUTPUT_CHANNEL << " to " << TCPP_MAX_OUTPUT_CHANNEL << " for output connector counting, or " << TCPP_MIN_INPUT_CHANNEL << " to " << TCPP_MAX_INPUT_CHANNEL << " for input connector counting.\n";
         return false;
      }
      return true;
      break;
   case CMM:
   case TCM:
   case ROD:
   case TYPE_NOT_SET:
   default:
      return false;
   }
   
   return false;
}

unsigned int L1CaloChannelId::GetLogicalChannel(void) const{
   if(GetModuleType() == PPM){
      return GetChannel() + GetModule()*(PPM_MAX_CHANNEL+1);
   }
   
   return 0;
}

