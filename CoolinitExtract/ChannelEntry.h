#ifndef CHANNELENTRY_H
#define CHANNELENTRY_H

#include <vector>

#include "Attribute.h"

class ChannelEntry{
public:
   ChannelEntry(void);
   
   push_back(Attribute *attr){m_attributeList->push_back(attr);};
   
   std::vector<Attribute*>* GetAttributeList(void){return m_attributeList;};
   
   std::string GetFolderName(void){return m_folderName;};
   void SetFolderName(std::string name){m_folderName = name;};
   
   unsigned int GetChannelId(void){return m_chanId;};
   void SetChannelId(unsigned int id){m_chanId = id;};
   
private:
   std::vector<Attribute*>* m_attributeList;
   
   std::string m_folderName;
   unsigned int m_chanId;
};

#endif
