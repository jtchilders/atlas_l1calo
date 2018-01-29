////////////////////////////////////////////////////////////////
/// Tree Package: used to defind data type held in Branch     //
/// Developed by: Taylor Childers                             //
/// Feel free to email with questions                         //
////////////////////////////////////////////////////////////////
#ifndef DATATYPE_H
#define DATATYPE_H

#include <string>

#include "TH1C.h"
#include "TH1S.h"
#include "TH1I.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TH2C.h"
#include "TH2S.h"
#include "TH2I.h"
#include "TH2F.h"
#include "TH2D.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "TF1.h"

class DataType{
public:
   
   enum DATA_TYPE{
      ULONG64 = 0,
      ULONG,
      LONG64,
      LONG,
      UINT,
      INT,
      USHORT,
      SHORT,
      UCHAR,
      CHAR,
      DOUBLE,
      DOUBLE32,
      FLOAT,
      FLOAT16,
      BOOL,
      RTH1C,
      RTH1S,
      RTH1I,
      RTH1F,
      RTH1D,
      RTH2C,
      RTH2S,
      RTH2I,
      RTH2F,
      RTH2D,
      RTPROFILE,
      RTPROFILE2D,
      RTF1,
      NO_TYPE_SET
   };
   
   DataType(void){Clear();};
   DataType(DATA_TYPE type){dataType(type);};
   ~DataType(void){};
   
   void operator=(const DataType& type){m_dataType = type.dataType();};
   
   DATA_TYPE dataType(void) const {return m_dataType;};
   void dataType(DATA_TYPE type){m_dataType = type;};
   
   bool IsSet     (void) const {if(m_dataType == NO_TYPE_SET) return false;return true;};
   
   bool IsULONG64 (void) const {if(m_dataType == ULONG64)  return true;return false;};
   bool IsULONG   (void) const {if(m_dataType == ULONG)    return true;return false;};
   bool IsLONG64  (void) const {if(m_dataType == LONG64)   return true;return false;};
   bool IsLONG    (void) const {if(m_dataType == LONG)     return true;return false;};
   bool IsUINT    (void) const {if(m_dataType == UINT)     return true;return false;};
   bool IsINT     (void) const {if(m_dataType == INT)      return true;return false;};
   bool IsUSHORT  (void) const {if(m_dataType == USHORT)   return true;return false;};
   bool IsSHORT   (void) const {if(m_dataType == SHORT)    return true;return false;};
   bool IsUCHAR   (void) const {if(m_dataType == UCHAR)    return true;return false;};
   bool IsCHAR    (void) const {if(m_dataType == CHAR)     return true;return false;};
   bool IsDOUBLE  (void) const {if(m_dataType == DOUBLE)   return true;return false;};
   bool IsDOUBLE32(void) const {if(m_dataType == DOUBLE32) return true;return false;};
   bool IsFLOAT   (void) const {if(m_dataType == FLOAT)    return true;return false;};
   bool IsFLOAT16 (void) const {if(m_dataType == FLOAT16)  return true;return false;};
   bool IsBOOL    (void) const {if(m_dataType == BOOL)     return true;return false;};
   bool IsTH1C    (void) const {if(m_dataType == RTH1C)     return true;return false;};
   bool IsTH1S    (void) const {if(m_dataType == RTH1S)     return true;return false;};
   bool IsTH1I    (void) const {if(m_dataType == RTH1I)     return true;return false;};
   bool IsTH1F    (void) const {if(m_dataType == RTH1F)     return true;return false;};
   bool IsTH1D    (void) const {if(m_dataType == RTH1D)     return true;return false;};
   bool IsTH2C    (void) const {if(m_dataType == RTH2C)     return true;return false;};
   bool IsTH2S    (void) const {if(m_dataType == RTH2S)     return true;return false;};
   bool IsTH2I    (void) const {if(m_dataType == RTH2I)     return true;return false;};
   bool IsTH2F    (void) const {if(m_dataType == RTH2F)     return true;return false;};
   bool IsTH2D    (void) const {if(m_dataType == RTH2D)     return true;return false;};
   bool IsTPROFILE(void) const {if(m_dataType == RTPROFILE) return true;return false;};
   bool IsTPROFILE2D(void) const {if(m_dataType == RTPROFILE2D)return true;return false;};
   bool IsTF1     (void) const {if(m_dataType == RTF1)      return true;return false;};
   
   bool IsNumerical(void) const {
      if(IsULONG64()
      || IsULONG()
      || IsLONG64()
      || IsLONG()
      || IsUINT()
      || IsINT()
      || IsUSHORT()
      || IsSHORT()
      || IsUCHAR()
      || IsCHAR()
      || IsDOUBLE()
      || IsDOUBLE32()
      || IsFLOAT()
      || IsFLOAT16()
      || IsBOOL()      ) return true;
      
      return false;
   }
   
   bool IsROOT(void) const {
      if(IsTH1C()
      || IsTH1S()
      || IsTH1I()
      || IsTH1F()
      || IsTH1D()
      || IsTH2C()
      || IsTH2S()
      || IsTH2I()
      || IsTH2F()
      || IsTH2D()
      || IsTPROFILE()
      || IsTPROFILE2D()
      || IsTF1()      ) return true;
      
      return false;
   }
   
   std::string GetString(void) const {
      switch(m_dataType){
      case ULONG64:
         return "ULONG64";
      case ULONG:
         return "ULONG";
      case LONG64:
         return "LONG64";
      case LONG:
         return "LONG";
      case UINT:
         return "UINT";
      case INT:
         return "INT";
      case USHORT:
         return "USHORT";
      case SHORT:
         return "SHORT";
      case UCHAR:
         return "UCHAR";
      case CHAR:
         return "CHAR";
      case DOUBLE:
         return "DOUBLE";
      case DOUBLE32:
         return "DOUBLE32";
      case FLOAT:
         return "FLOAT";
      case FLOAT16:
         return "FLOAT16";
      case BOOL:
         return "BOOL";
      case RTH1C:
         return "TH1C";
      case RTH1S:
         return "TH1S";
      case RTH1I:
         return "TH1I";
      case RTH1F:
         return "TH1F";
      case RTH1D:
         return "TH1D";
      case RTH2C:
         return "TH2C";
      case RTH2S:
         return "TH2S";
      case RTH2I:
         return "TH2I";
      case RTH2F:
         return "TH2F";
      case RTH2D:
         return "TH2D";
      case RTPROFILE:
         return "TPROFILE";
      case RTPROFILE2D:
         return "TPROFILE2D";
      case RTF1:
         return "TF1";
      case NO_TYPE_SET:
         return "NO_TYPE_SET";
      }
      return "NO_TYPE_SET";
   }
   
   void Clear(void){m_dataType = NO_TYPE_SET;};
private:
   DATA_TYPE m_dataType;
};

#endif
