#ifndef COOLATTRIBUTECOLLECTION_H
#define COOLATTRIBUTECOLLECTION_H

#include <string>
#include <ctime>

#include "CoolKernel/StorageType.h"

#include "coolAttribute.h"

#include "TH1D.h"
#include "TH1S.h"
#include "TH1I.h"
#include "TH1F.h"
#include "TH1C.h"
#include "TDatime.h"

class coolAttributeCollection{

public:
	coolAttributeCollection();
	~coolAttributeCollection();
	
	// methods for adding a new attribute
	void push_back(coolAttribute<int> attr)
		{m_attrListInt->push_back(attr);};
	void push_back(coolAttribute<short int> attr)
		{m_attrListShort->push_back(attr);};
	void push_back(coolAttribute<unsigned int> attr)
		{m_attrListUInt->push_back(attr);};
	void push_back(coolAttribute<unsigned short int> attr)
		{m_attrListUShort->push_back(attr);};
	void push_back(coolAttribute<unsigned char> attr)
		{m_attrListUChar->push_back(attr);};
	void push_back(coolAttribute<float> attr)
		{m_attrListFloat->push_back(attr);};
	void push_back(coolAttribute<double> attr)
		{m_attrListDouble->push_back(attr);};
	void CreateNewAttribute(std::string name,cool::StorageType::TypeId type,uint coolId);
	
	// methods for adding new values to a coolAttribute object in our vectors
	int AddAttrValue(std::string name, int value, time_t start, time_t end,bool disabled = false);
	int AddAttrValue(std::string name, short value, time_t start, time_t end,bool disabled = false);
	int AddAttrValue(std::string name, uint value, time_t start, time_t end,bool disabled = false);
	int AddAttrValue(std::string name, unsigned short int value, time_t start, time_t end,bool disabled = false);
	int AddAttrValue(std::string name, unsigned char value, time_t start, time_t end,bool disabled = false);
	int AddAttrValue(std::string name, float value, time_t start, time_t end,bool disabled = false);
	int AddAttrValue(std::string name, double value, time_t start, time_t end,bool disabled = false);
	
	// methods for getting atrributes
	uint GetNumberAttrInt(void){return m_attrListInt->size();};
	coolAttribute<int>* GetAttributeInt(uint entry)
		{return &m_attrListInt->at(entry);};
	uint GetNumberAttrShort(void){return m_attrListShort->size();};
	coolAttribute<short>* GetAttributeShort(uint entry)
		{return &m_attrListShort->at(entry);};
	uint GetNumberAttrUInt(void){return m_attrListUInt->size();};
	coolAttribute<unsigned int>* GetAttributeUInt(uint entry)
		{return &m_attrListUInt->at(entry);};
	uint GetNumberAttrUShort(void){return m_attrListUShort->size();};
	coolAttribute<unsigned short int>* GetAttributeUShort(uint entry)
		{return &m_attrListUShort->at(entry);};
	uint GetNumberAttrUChar(void){return m_attrListUChar->size();};
	coolAttribute<unsigned char>* GetAttributeUChar(uint entry)
		{return &m_attrListUChar->at(entry);};
	uint GetNumberAttrFloat(void){return m_attrListFloat->size();};
	coolAttribute<float>* GetAttributeFloat(uint entry)
		{return &m_attrListFloat->at(entry);};
	uint GetNumberAttrDouble(void){return m_attrListDouble->size();};
	coolAttribute<double>* GetAttributeDouble(uint entry)
		{return &m_attrListDouble->at(entry);};
	
	uint GetNumberAttr(void){return m_attrListInt->size() + m_attrListShort->size() + m_attrListUInt->size() + m_attrListUShort->size() + m_attrListUChar->size() + m_attrListFloat->size() + m_attrListDouble->size();};
	
	// These methods provide histograms of the requested Attribute
	TH1* GetAttrHistogram(std::string name);
	
private:
	
	std::vector<coolAttribute<int> >*		 m_attrListInt;
	std::vector<coolAttribute<short int> >*		 m_attrListShort;
	std::vector<coolAttribute<uint> >*		 m_attrListUInt;
	std::vector<coolAttribute<unsigned short int> >* m_attrListUShort;
	std::vector<coolAttribute<unsigned char> >*	 m_attrListUChar;
	std::vector<coolAttribute<float> >*		 m_attrListFloat;
	std::vector<coolAttribute<double> >*		 m_attrListDouble;
	
};




#endif

