#ifndef PPMFADCSIM_H
#define PPMFADCSIM_H

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>

#include "LandGaus.h"

#include "TH1D.h"
#include "TF1.h"

using namespace std;

class PpmFadcSim{
public:
	PpmFadcSim(unsigned int);
	~PpmFadcSim(){};
	void Init(void);
	
	vector<unsigned int>* GetFadcWindow(void){return fadcValues;};
	vector<unsigned int>* GetFadcValues(void);
	
	void SetXvalue(double xValue){*x =xValue;};
	double GetXvalue(void){return *x;};
	
	void SetMean(double mean) {par[0] = mean;};
	double GetMean(void){return par[0];};
	
	void SetAmplitude(double amp){par[1] = amp/exp(-0.5);};
	double GetAmplitude(void){return par[1]*exp(-0.5);};
	
	void SetGaussianSigma(double sigma){par[2] = sigma;};
	double GetGaussianSigma(void){return par[2];};
	
	void SetLandauSigma(double sigma){par[3] = sigma;};
	double GetLandauSigma(void){return par[3];};
	
	void SetPedestal(double pedestal){par[4] = pedestal;};
	double GetPedestal(void){return par[4];};
	
	void SetDefaultParameters(void);
	
	void SetRandomSampling(bool setting){randomSampling=setting;};
	
	void SetRandomAmplitude(bool setting){randomAmplitude=setting;};
	void SetAmplitudeRangeMaximum(unsigned int max){ampMax = max;};
	void SetAmplitudeRangeMinimum(unsigned int min){ampMin = min;};
	
	void SetRandomPedestal(bool setting){randomPedestal=setting;};
	
	double SimulatePpmFadcSlices(void);
	
	unsigned int GetNumberOfTimeSlices(void){return numTimeSlices;};
	double GetOffset(void){return currentOffset;};
	unsigned int GetCurrentSlice(void){return currentSlice;};
	
	unsigned int GetPipelineLength(void){return lowSignalWindow+highSignalWindow;};
	unsigned int GetLowSignalWindow(void){return lowSignalWindow;};
	unsigned int GetHighSignalWindow(void){return highSignalWindow;};
	
	unsigned int GetPeakLocation(void){return peakLocation;};
	
	LandGaussFunc* GetFitFunction(void){return fitFunc;};
	
	void SetRandomSeed(unsigned int seed){randomSeed = seed;useSeed = true;};
	
	void ResetPipeline(void);
	
	void SetPedestalGaussianAmplitude(double amp){gaussianAmplitude = amp;};
	double GetPedestalGaussianAmplitude(void){return gaussianAmplitude;};
	
	void SetPedestalGaussianSigma(double sigma){gaussianSigma = sigma;};
	double GetPedestalGaussianSigma(void){return gaussianAmplitude;};
	
	void SetupGaussianHistogram(void);
	
	void SetRandomPhysicsRate(bool setting){randomPhysicsRate = setting;};
	
	void SetPowerLawIndex(double index){powerLawIndex = index;};
	double GetPowerLawIndex(void){return powerLawIndex;};
	
	void SetupPowerLawSpectrum(void);
	
private:
	const unsigned int numTimeSlices; // number of time slices being readout
	const unsigned int centerSlice; // the center slice of the set nubmer of time slices
	unsigned int peakLocation; // true peak location among the number of time slices being readout
	
	const unsigned int lowSignalWindow; // number of time slices to readout before start of pulse (before bc=0)
	const unsigned int highSignalWindow; // number of time slices to readout after start of pulse (after bc=0)
	vector<unsigned int>* fadcPipeline; // full pipeline of adc values
	vector<unsigned int>* fadcValues; // only the time slices that are being looked at
	
	int currentSlice; // current slice in the pipeline window at which the readout will be taken
	double currentOffset; // current timing offset from -15 to 15 ns
	
	bool needReset; // resets the pipeline and resimulates the pipeline signal
	
	bool randomSampling;
	bool randomAmplitude;
	unsigned int ampMax;
	unsigned int ampMin;
	
	LandGaussFunc *fitFunc;
	double *x;
	double par[5]; // {Mean,Amp,Gsigma,Lsigma,Pedestal}
	
	static const unsigned int adcSatLvl = 0x3ff;
	
	unsigned int randomSeed;
	bool useSeed;
	
	bool randomPedestal;
	TH1D* gaussianPedestal;
	TF1* gaussianFit;
	double gaussianAmplitude;
	double gaussianSigma;
	
	bool randomPhysicsRate;
	TH1D* powerLawSpectrum;
	TF1* powerLawFunc;
	double powerLawIndex;
	unsigned int minEnergy;
	unsigned int maxEnergy;
	
	
	
};

#endif
