#ifndef HWCHANGELIST_H
#define HWCHANGELIST_H


#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include "taylorsPackage/hardwareChange.h"

class HwChangeList{
public:
	HwChangeList() {Init();};
	HwChangeList(std::string filename) {Init();SetFilename(filename);};
	~HwChangeList();
	
	void Init(void);
	
	void ReadChangesFromFile(void);
	
	HardwareChange* operator[](unsigned int entry){return (*m_hwChangeList)[entry];};
	unsigned int size(void){return m_hwChangeList->size();};
	
	std::vector<HardwareChange*>::iterator begin(){return m_hwChangeList->begin();};
	std::vector<HardwareChange*>::iterator end(){return m_hwChangeList->end();};
	
	std::string GetFilename(void){return m_filename;};
	void SetFilename(std::string filename){m_filename=filename;};
	
private:
	
	std::vector<HardwareChange*>*        m_hwChangeList;
	
	std::string                          m_filename;
};


#endif
