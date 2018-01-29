#include "taylorsPackage/hwChangeList.h"


void HwChangeList::Init(void){
	m_hwChangeList = new std::vector<HardwareChange*>;
	
}

HwChangeList::~HwChangeList(void){
	
	for(unsigned int i=0;i<m_hwChangeList->size();i++){
		delete m_hwChangeList->at(i);
		m_hwChangeList->at(i) = 0;
		
	}
	m_hwChangeList->clear();
	delete m_hwChangeList;m_hwChangeList=0;
}

void HwChangeList::ReadChangesFromFile(void){
	
	if(m_filename.empty()){
		std::cerr << "[HwChangeList::ReadChangesFromFile]: Error, must set filename.\n";
		return;
	}
	
	std::ifstream fin(m_filename.c_str());
	if(!fin.is_open()){
		std::cerr << "[HwChangeList::ReadChangesFromFile]: Error opening: " << m_filename << std::endl;
		return;
	}
	
	while(!fin.eof()){
		
		unsigned int coolId=0,yr=0,mon=0,day=0,hr=0,min=0,sec=0;
		
		fin >> coolId >> yr >> mon >> day >> hr >> min >> sec;
		char line[500];
		fin.getline(line,500);
		
		HardwareChange* hwc = new HardwareChange;
		hwc->SetCoolId(coolId);
		hwc->SetChangeTime(yr,mon,day,hr,min,sec);
		m_hwChangeList->push_back(hwc);
	}
	
	fin.close();
	
	
	
}


