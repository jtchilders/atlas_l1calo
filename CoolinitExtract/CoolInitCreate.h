#ifndef COOLINITCREATE_H
#define COOLINITCREATE_H

#include <map>
#include <vector>
#include <string>

#include "Attribute.h"

class CoolInitCreate{
public:
   CoolInitCreate(void);
   
   
   void CreateAttribute(std::string& name,Attribute::DataType& type);
   
   template<class T> void SetAttribute(unsigned int& id,std::string& name,T& value);
   template<class T> T GetAttribute(unsigned int& id,std::string& name);
   
   
private:
   std::map<unsigned int,ChannelEntry*> *m_id_entry;
   
   std::vector<Attribute*> *m_templateChannelEntry;
   
};


#endif
