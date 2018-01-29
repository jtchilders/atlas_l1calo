#include "PpmSatBcidLogic.h"

PpmSatBcidLogic::PpmSatBcidLogic(unsigned int time_slices): numTimeSlices(time_slices), centerSlice(time_slices/2){
	
	Init();
	SetDefaults();
}


void PpmSatBcidLogic::Init(void){
	centerIsPeak = false;
	centerPlusOneIsPeak = false;
	peakBc = 999;
	
}

void PpmSatBcidLogic::SetDefaults(void){
	satLvl = 0x3ff;
	satHigh = 0x2ff;
	satLow = 0xff;
}


void PpmSatBcidLogic::SetFadcSlices(const vector<unsigned int>* fadc){
	
	fadcValues = const_cast<vector<unsigned int>*>(fadc);
	
	if(fadcValues->at(centerSlice) < satLvl){
		Init();
		return;
	}
	else{ 
		if(fadcValues->at(centerSlice-1) <= satHigh){
			peakBc = centerSlice + 1;
			centerIsPeak = false;
			centerPlusOneIsPeak = true;
			return;
		}
		else{
			if(fadcValues->at(centerSlice-2) <= satLow){
				peakBc = centerSlice + 1;
				centerIsPeak = false;
				centerPlusOneIsPeak = true;
				return;
			}
			else{
				peakBc = centerSlice;
				centerIsPeak = true;
				centerPlusOneIsPeak = false;
				return;
			}
		}
	}
	
	
}
