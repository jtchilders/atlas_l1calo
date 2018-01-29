#ifndef PPMSATBCIDLOGIC_H
#define PPMSATBCIDLOGIC_H

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

class PpmSatBcidLogic{
public:
	PpmSatBcidLogic(unsigned int);
	~PpmSatBcidLogic(){};
	void Init(void);
	
	void SetFadcSlices(const vector<unsigned int>*);
	
	bool IsCenterSlicePeak(void){return centerIsPeak;};
	bool IsCenterSlicePlusOnePeak(void){return centerPlusOneIsPeak;};
	unsigned int GetPeakBcNumber(void){return peakBc;};
	
	
	void SetSaturationLevel(unsigned int lvl){satLvl = lvl;};
	unsigned int GetSaturationLevel(void){return satLvl;};
	
	void SetSatHighThreshold(unsigned int lvl){satHigh = lvl;};
	unsigned int GetSatHighThreshold(void){return satHigh;};
	
	void SetSatLowThreshold(unsigned int lvl){satLow = lvl;};
	unsigned int GetSatLowThreshold(void){return satLow;};
	
	void SetDefaults();
	
private:
	vector<unsigned int> *fadcValues;
	
	unsigned int satLvl;
	unsigned int satHigh;
	unsigned int satLow;
	
	bool centerIsPeak;
	bool centerPlusOneIsPeak;
	unsigned int peakBc;
	const unsigned int numTimeSlices;
	const unsigned int centerSlice;
	
};

#endif
