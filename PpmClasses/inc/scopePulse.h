#ifndef SCOPEPULSE_H
#define SCOPEPULSE_H


#include <string>
#include <vector>
#include <fstream>
#include <iostream>


class ScopePulse{

public:
	ScopePulse(){};
	ScopePulse(std::string filename){SetFilename(filename);};
	ScopePulse(char* filename){SetFilename(filename);};
	~ScopePulse(){};
	
	void FillPulse(void);
	
	std::string GetFilename(void){return m_filename;};
	void SetFilename(std::string filename){m_filename=filename;};
	void SetFilename(char* filename){m_filename=filename;};
	
	std::vector<double>* GetPulseVector(void){return &m_pulseVoltages;};
	double GetVoltageValue(uint entry){return m_pulseVoltages[entry];};
	
	uint GetEntries(void){return m_entries;};
	double GetResolution(void){return m_resolution_sec;};
	double GetTrigThreshold(void){return m_trigThresh_mV;};
	double GetDCoffset(void){return m_dcOffset_V;};
	
private:
	std::string m_filename;
	
	std::vector<double> m_pulseVoltages;
	
	uint m_entries;
	double m_resolution_sec;
	double m_trigThresh_mV;
	double m_dcOffset_V;
	
};



#endif

