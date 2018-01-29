#include "taylorsPackage/coolAttributeCollection.h"


coolAttributeCollection::coolAttributeCollection(void){
	m_attrListInt    = new std::vector<coolAttribute<int> >;
	m_attrListShort  = new std::vector<coolAttribute<short int> >;
	m_attrListUInt   = new std::vector<coolAttribute<unsigned int> >;
	m_attrListUShort = new std::vector<coolAttribute<unsigned short int> >;
	m_attrListUChar  = new std::vector<coolAttribute<unsigned char> >;
	m_attrListFloat  = new std::vector<coolAttribute<float> >;
	m_attrListDouble = new std::vector<coolAttribute<double> >;
	
	
}

coolAttributeCollection::~coolAttributeCollection(void){
	
	delete m_attrListInt;     m_attrListInt = 0;
	delete m_attrListShort;   m_attrListShort = 0;
	delete m_attrListUInt;    m_attrListUInt = 0;
	delete m_attrListUShort;  m_attrListUShort = 0;
	delete m_attrListUChar;   m_attrListUChar = 0;
	delete m_attrListFloat;   m_attrListFloat = 0;
	delete m_attrListDouble;  m_attrListDouble = 0;
	
}

void coolAttributeCollection::CreateNewAttribute(std::string name, cool::StorageType::TypeId type, uint coolId){
	switch(type){
	case cool::StorageType::UInt32:
	{
		coolAttribute<uint> tempUInt;
		tempUInt.SetName(name);
		tempUInt.SetStorageType(type);
		tempUInt.SetCoolId(coolId);
		m_attrListUInt->push_back(tempUInt);
		break;
	}
	case cool::StorageType::Int32:
	{
		coolAttribute<int> tempInt;
		tempInt.SetName(name);
		tempInt.SetStorageType(type);
		tempInt.SetCoolId(coolId);
		m_attrListInt->push_back(tempInt);
		break;
	}
	case cool::StorageType::UInt16:
	{
		coolAttribute<unsigned short int> tempUShort;
		tempUShort.SetName(name);
		tempUShort.SetStorageType(type);
		tempUShort.SetCoolId(coolId);
		m_attrListUShort->push_back(tempUShort);
		break;
	}
	case cool::StorageType::Int16:
	{
		coolAttribute<short int> tempShort;
		tempShort.SetName(name);
		tempShort.SetStorageType(type);
		tempShort.SetCoolId(coolId);
		m_attrListShort->push_back(tempShort);
		break;
	}
	case cool::StorageType::UChar:
	{
		coolAttribute<unsigned char> tempUChar;
		tempUChar.SetName(name);
		tempUChar.SetStorageType(type);
		tempUChar.SetCoolId(coolId);
		m_attrListUChar->push_back(tempUChar);
		break;
	}
	case cool::StorageType::Float:
	{
		coolAttribute<float> tempFloat;
		tempFloat.SetName(name);
		tempFloat.SetStorageType(type);
		tempFloat.SetCoolId(coolId);
		m_attrListFloat->push_back(tempFloat);
		break;
	}
	case cool::StorageType::Double:
	{
		coolAttribute<double> tempDouble;
		tempDouble.SetName(name);
		tempDouble.SetStorageType(type);
		tempDouble.SetCoolId(coolId);
		m_attrListDouble->push_back(tempDouble);
		break;
	}
	default:
		std::cerr << "[CoolChanHistory::AddAttribute] Error: invalid storage type passed.\n";
		break;
	}
	
	
}

int coolAttributeCollection::AddAttrValue(std::string name, uint value, time_t start, time_t end,bool disabled){
	bool entryNotFound = true;
	for(uint entry=0;entry<m_attrListUInt->size();entry++){
		if(m_attrListUInt->at(entry).GetName()->find(name) != std::string::npos){
			coolAttributeSinglet<uint> temp(value,start,end);
			temp.SetDisabled(disabled);
			m_attrListUInt->at(entry).push_back(temp);
			entryNotFound = false;
			break;
		}
		
	}
	
	if(entryNotFound){
		//std::cerr << "[coolAttributeCollection::AddAttrValue(uint)] Entry not found, attribute value not added.\n";
		return -1;
	}
	
	return 0;
	
}


int coolAttributeCollection::AddAttrValue(std::string name, int value, time_t start, time_t end,bool disabled){
	bool entryNotFound = true;
	for(uint entry=0;entry<m_attrListInt->size();entry++){
		if(m_attrListInt->at(entry).GetName()->find(name) != std::string::npos){
			coolAttributeSinglet<int> temp(value,start,end);
			temp.SetDisabled(disabled);
			m_attrListInt->at(entry).push_back(temp);
			entryNotFound = false;
			break;
		}
		
	}
	
	if(entryNotFound){
		//std::cerr << "[coolAttributeCollection::AddAttrValue(int)] Entry not found, attribute value not added.\n";
		return -1;
	}
	
	return 0;
}

int coolAttributeCollection::AddAttrValue(std::string name, short value, time_t start, time_t end,bool disabled){
	bool entryNotFound = true;
	for(uint entry=0;entry<m_attrListShort->size();entry++){
		if(m_attrListShort->at(entry).GetName()->find(name) != std::string::npos){
			coolAttributeSinglet<short> temp(value,start,end);
			temp.SetDisabled(disabled);
			m_attrListShort->at(entry).push_back(temp);
			entryNotFound = false;
			break;
		}
		
	}
	
	if(entryNotFound){
		//std::cerr << "[coolAttributeCollection::AddAttrValue(short)] Entry not found, attribute value not added.\n";
		return -1;
	}
	
	return 0;
}

int coolAttributeCollection::AddAttrValue(std::string name, unsigned short int value, time_t start, time_t end,bool disabled){
	bool entryNotFound = true;
	for(uint entry=0;entry<m_attrListUShort->size();entry++){
		if(m_attrListUShort->at(entry).GetName()->find(name) != std::string::npos){
			coolAttributeSinglet<unsigned short int> temp(value,start,end);
			temp.SetDisabled(disabled);
			m_attrListUShort->at(entry).push_back(temp);
			entryNotFound = false;
			break;
		}
		
	}
	
	if(entryNotFound){
		//std::cerr << "[coolAttributeCollection::AddAttrValue(ushort)] Entry not found, attribute value not added.\n";
		return -1;
	}
	
	return 0;
}

int coolAttributeCollection::AddAttrValue(std::string name, unsigned char value, time_t start, time_t end,bool disabled){
	bool entryNotFound = true;
	for(uint entry=0;entry<m_attrListUChar->size();entry++){
		if(m_attrListUChar->at(entry).GetName()->find(name) != std::string::npos){
			coolAttributeSinglet<unsigned char> temp(value,start,end);
			temp.SetDisabled(disabled);
			m_attrListUChar->at(entry).push_back(temp);
			entryNotFound = false;
			break;
		}
		
	}
	
	if(entryNotFound){
		//std::cerr << "[coolAttributeCollection::AddAttrValue(uchar)] Entry not found, attribute value not added.\n";
		return -1;
	}
	
	return 0;
}

int coolAttributeCollection::AddAttrValue(std::string name, float value, time_t start, time_t end,bool disabled){
	bool entryNotFound = true;
	for(uint entry=0;entry<m_attrListFloat->size();entry++){
		if(m_attrListFloat->at(entry).GetName()->find(name) != std::string::npos){
			coolAttributeSinglet<float> temp(value,start,end);
			temp.SetDisabled(disabled);
			m_attrListFloat->at(entry).push_back(temp);
			entryNotFound = false;
			break;
		}
		
	}
	
	if(entryNotFound){
		//std::cerr << "[coolAttributeCollection::AddAttrValue(float)] Entry not found, attribute value not added.\n";
		return -1;
	}
	
	return 0;
}

int coolAttributeCollection::AddAttrValue(std::string name, double value, time_t start, time_t end,bool disabled){
	bool entryNotFound = true;
	for(uint entry=0;entry<m_attrListDouble->size();entry++){
		if(m_attrListDouble->at(entry).GetName()->find(name) != std::string::npos){
			coolAttributeSinglet<double> temp(value,start,end);
			temp.SetDisabled(disabled);
			m_attrListDouble->at(entry).push_back(temp);
			entryNotFound = false;
			break;
		}
		
	}
	
	if(entryNotFound){
		//std::cerr << "[coolAttributeCollection::AddAttrValue(double)] Entry not found, attribute value not added.\n";
		return -1;
	}
	
	return 0;
}

TH1* coolAttributeCollection::GetAttrHistogram(std::string name){
	
	// Need to find the appropriate attribute
	for(uint entry=0;entry<m_attrListInt->size();entry++){
		
		coolAttribute<int> attr = (*m_attrListInt)[entry];
		
		if(attr.GetName()->find(name) != std::string::npos)
			return attr.GetHistogram();
	}
	
	for(uint entry=0;entry<m_attrListShort->size();entry++){
		
		coolAttribute<short> attr = (*m_attrListShort)[entry];
		
		if(attr.GetName()->find(name) != std::string::npos)
			return attr.GetHistogram();
	}
	
	for(uint entry=0;entry<m_attrListUInt->size();entry++){
		
		coolAttribute<uint> attr = (*m_attrListUInt)[entry];
		
		if(attr.GetName()->find(name) != std::string::npos)
			return attr.GetHistogram();
	}
	
	for(uint entry=0;entry<m_attrListUShort->size();entry++){
		
		coolAttribute<unsigned short> attr = (*m_attrListUShort)[entry];
		
		if(attr.GetName()->find(name) != std::string::npos)
			return attr.GetHistogram();
	}
	
	for(uint entry=0;entry<m_attrListUChar->size();entry++){
		
		coolAttribute<unsigned char> attr = (*m_attrListUChar)[entry];
		
		if(attr.GetName()->find(name) != std::string::npos)
			return attr.GetHistogram();
	}
	
	for(uint entry=0;entry<m_attrListFloat->size();entry++){
		
		coolAttribute<float> attr = (*m_attrListFloat)[entry];
		
		if(attr.GetName()->find(name) != std::string::npos)
			return attr.GetHistogram();
	}
	
	for(uint entry=0;entry<m_attrListDouble->size();entry++){
		
		coolAttribute<double> attr = (*m_attrListDouble)[entry];
		
		if(attr.GetName()->find(name) != std::string::npos)
			return attr.GetHistogram();
	}
	
	return (TH1*)0;
	
	
}

