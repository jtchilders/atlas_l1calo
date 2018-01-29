#ifndef PPMROBUFFER_H
#define PPMROBUFFER_H

#include <iostream>
#include <vector>

#include "TProfile.h"

using namespace std;

class PpmROBuffer{
public:
	PpmROBuffer(const unsigned int time_slices);
	~PpmROBuffer(void){delete m_prof;m_prof=0;};
	
	void SetValue(unsigned int step,unsigned int slice,unsigned int value) {m_slotValue[step*m_numTimeSlices+slice] = value;m_prof->Fill(step*m_numTimeSlices+slice,value);};
	void SetValue(unsigned int slot,unsigned int value) {m_slotValue[slot] = value;m_prof->Fill(slot,value);};
	unsigned int GetValue(unsigned int slot) {return m_slotValue[slot];};
	unsigned int GetValue(unsigned int step,unsigned int slice) {return m_slotValue[step*m_numTimeSlices+slice];};
	
	void Clear(void){m_slotValue.clear();m_prof->Reset();};
	
	TProfile* GetProfile(void){return m_prof;};
	
private:
	unsigned int m_maxSteps;
	unsigned int m_maxMemSlots;
	unsigned int m_numTimeSlices;
	
	const unsigned int m_maxBufferLength;
	
	vector<unsigned int> m_slotValue; // holds the ADC in the given readout buffer memory location
	
	TProfile* m_prof; // holds a profile plot of the signal shape
	
};



#endif


