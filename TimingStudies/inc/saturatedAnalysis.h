#ifndef SATURATEDANALYSIS_H
#define SATURATEDANALYSIS_H

#include "PpmFadcSim.h"
#include "PpmSatBcidLogic.h"
#include "LandGaus.h"
#include "cbntClass.h"
#include "commandLineParser.h"

#include "TH2I.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TF1.h"
#include "TProfile2D.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TProfile.h"
#include "TApplication.h"
#include "TROOT.h"
#include "TFile.h"

#include <iostream>
#include <fstream>

using namespace std;

typedef unsigned int uint;

class SaturatedAnalysis{
public:
	SaturatedAnalysis(const uint time_slices=5);
	~SaturatedAnalysis();
	
	
	void FindRegSatLowHigh(int,char**);
	void CalculateBcDetectionEfficiency(int,char**);
	void TestEfficiencyStability(int,char**);
	void fadcPlotter(int,char**);
	
	void SetBatch(bool batch){m_batch=batch;};
	
	void SetLowestRegSatLow(const uint low){m_lowestLow=low;};
	uint GetLowestRegSatLow(void){return m_lowestLow;};
	
	void SetHighestRegSatLow(const uint low){m_highestLow=low;};
	uint GetHighestRegSatLow(void){return m_highestLow;};
	
	void SetLowestRegSatHigh(const uint high){m_lowestHigh=high;};
	uint GetLowestRegSatHigh(void){return m_lowestHigh;};
	
	void SetHighestRegSatHigh(const uint high){m_highestHigh=high;};
	uint GetHighestRegSatHigh(void){return m_highestHigh;};
	
private:
	PpmFadcSim*		m_fadcSource;
	PpmSatBcidLogic* 	m_satBcidBlock;
	
	const uint		m_numOfTimeSlices;
	bool			m_batch;
	
	uint			m_lowestLow;
	uint			m_highestLow;
	uint			m_lowestHigh;
	uint			m_highestHigh;
};



#endif


