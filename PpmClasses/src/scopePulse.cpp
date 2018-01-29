#include "scopePulse.h"


void ScopePulse::FillPulse(void){
	
	m_pulseVoltages.clear();
	
	std::ifstream inFile(m_filename.c_str());
	if(!inFile.is_open()){
		std::cerr << "[ScopePulse::FillPulse] Error opening file: " << m_filename << std::endl;
		return;
	}
	
	char line[500];
	
	// Get the number of entries
	inFile.getline(line,500);
	m_entries = atoi(line);
	// Get the time resolution
	inFile >> m_resolution_sec;
	inFile.getline(line,500);
	// Get the trigger threshold
	inFile.getline(line,500);
	m_trigThresh_mV = atoi(line);
	// Get the DC offset
	inFile.getline(line,500);
	m_dcOffset_V = atoi(line);
	
	for(uint i=0;i<m_entries;i++){
		
		double voltage = 0;
		
		inFile >> voltage;
		
		m_pulseVoltages.push_back(voltage);
	}
	
}


