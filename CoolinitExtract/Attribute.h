#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <string>

class Attribute{
public:
   Attribute(void);
   
   enum DataType{
      UNSIGNED_INT = 0,
      UNSIGNED_SHORT,
      INT,
      SHORT,
      CHAR,
      UNSIGNED_CHAR,
      DOUBLE,
      FLOAT,
      STRING,
      TOTAL_DATA_TYPES,
      NOT_DEFINED
   };
   
   template<class T> void SetValue(T value);
   template<class T> T GetValue(void);
   
   void SetName(std::string name){m_name = name;};
   std::string GetName(void){return m_name;};
   
   std::string GetDataTypeName(void){return m_dataTypeName;};
   DataType GetDataType(void){return m_dataType;};
   
private:
   
   unsigned int m_uint;
   unsigned short int m_usint;
   int m_int;
   short int m_sint;
   float m_float;
   double m_double;
   char m_char;
   unsigned char m_uchar;
   std::string m_string;
   
   std::string m_name;
   std::string m_dataTypeName;
   
   DataType m_dataType;
   
};


#endif

