#include "Attribute.h"

#include <typeinfo>


Attribute::Attribute(void){
   m_uint      = 0;
   m_usint     = 0;
   m_int       = 0;
   m_sint      = 0;
   m_float     = 0.;
   m_double    = 0.;
   m_char      = 0;
   m_uchar     = 0;
   
   m_dataType = NOT_DEFINED;
}

template<class T> 
void Attribute::SetValue(T value){
   
   switch (typeid(value)){
   // UNSIGNED INT
   case typeid(unsigned int):
      m_dataType = UNSIGNED_INT;
      m_dataTypeName = "unsigned";
      m_uint      = value;
      m_usint     = 0;
      m_int       = 0;
      m_sint      = 0;
      m_char      = 0;
      m_uchar     = 0;
      m_double    = 0.;
      m_float     = 0.;
      m_string.clear();
      break;
   // UNSIGNED SHORT
   case typeid(unsigned short):
      m_dataType = UNSIGNED_SHORT;
      m_dataTypeName = "unsigned short";
      m_uint      = 0;
      m_usint     = value;
      m_int       = 0;
      m_sint      = 0;
      m_char      = 0;
      m_uchar     = 0;
      m_double    = 0.;
      m_float     = 0.;
      m_string.clear();
      break;
   // INT
   case typeid(int):
      m_dataType = INT;
      m_dataTypeName = "int";
      m_uint      = 0;
      m_usint     = 0;
      m_int       = value;
      m_sint      = 0;
      m_char      = 0;
      m_uchar     = 0;
      m_double    = 0.;
      m_float     = 0.;
      m_string.clear();
     break;
   // SHORT
   case typeid(short):
      m_dataType = SHORT;
      m_dataTypeName = "short";
      m_uint      = 0;
      m_usint     = 0;
      m_int       = 0;
      m_sint      = value;
      m_char      = 0;
      m_uchar     = 0;
      m_double    = 0.;
      m_float     = 0.;
      m_string.clear();
      break;
   // CHAR
   case typeid(char):
      m_dataType = CHAR;
      m_dataTypeName = "char";
      m_uint      = 0;
      m_usint     = 0;
      m_int       = 0;
      m_sint      = 0;
      m_char      = value;
      m_uchar     = 0;
      m_double    = 0.;
      m_float     = 0.;
      m_string.clear();
      break;
   // UNSIGNED_CHAR
   case typeid(unsigned char):
      m_dataType = UNSIGNED_CHAR;
      m_dataTypeName = "unsigned char";
      m_uint      = 0;
      m_usint     = 0;
      m_int       = 0;
      m_sint      = 0;
      m_char      = 0;
      m_uchar     = value;
      m_double    = 0.;
      m_float     = 0.;
      m_string.clear();
      break;
   // DOUBLE
   case typeid(double):
      m_dataType = DOUBLE;
      m_dataTypeName = "double";
      m_uint      = 0;
      m_usint     = 0;
      m_int       = 0;
      m_sint      = 0;
      m_char      = 0;
      m_uchar     = 0;
      m_double    = value;
      m_float     = 0.;
      m_string.clear();
      break;
   // FLOAT
   case typeid(float):
      m_dataType = FLOAT;
      m_dataTypeName = "float";
      m_uint      = 0;
      m_usint     = 0;
      m_int       = 0;
      m_sint      = 0;
      m_char      = 0;
      m_uchar     = 0;
      m_double    = 0.;
      m_float     = value;
      m_string.clear();
      break;
   // STRING
   case typeid(std::string):
      m_dataType = STRING;
      m_dataTypeName = "string";
      m_uint      = 0;
      m_usint     = 0;
      m_int       = 0;
      m_sint      = 0;
      m_char      = 0;
      m_uchar     = 0;
      m_double    = 0.;
      m_float     = 0.;
      m_string    = value;
      break;
   default:
      m_dataType = NOT_DEFINED;
      m_dataTypeName = "";
      m_uint      = 0;
      m_usint     = 0;
      m_int       = 0;
      m_sint      = 0;
      m_char      = 0;
      m_uchar     = 0;
      m_double    = 0.;
      m_float     = 0.;
      m_string.clear();
      break;
   }// end switch
   
}

