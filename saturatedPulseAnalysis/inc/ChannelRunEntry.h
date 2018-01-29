#ifndef CHANNELRUNENTRY_H
#define CHANNELRUNENTRY_H

#include <iostream>
#include <cmath>

#include "TProfile.h"
#include "TH1F.h"

#define CRE_MIN_PEDESTAL 960
#define CRE_MAX_PEDESTAL 1000

#define CRE_NS_PER_BC 25

class ChannelRunEntry{
public:
   ChannelRunEntry(void){ClearEntry();};
   ChannelRunEntry(const ChannelRunEntry &entry);
   
   void ClearEntry(void);
   
   void SetRunNumber(const unsigned int number){m_runNumber = number;};
   unsigned int GetRunNumber(void) const {return m_runNumber;};
   
   void SetFullDelayData(const unsigned int delay){m_fullDelayData = delay;};
   unsigned int GetFullDelayData(void) const {return m_fullDelayData;};
   void SetNewFullDelayData(unsigned int delay){m_newFullDelayData = delay;};
   unsigned int GetNewFullDelayData(void) const {return m_newFullDelayData;};
   
   void SetPedestalMean(float mean){m_pedestalMean = mean;};
   float GetPedestalMean(void) const {return m_pedestalMean;};
   void SetPedestalSigma(float sigma){m_pedestalSigma = sigma;};
   float GetPedestalSigma(void) const {return m_pedestalSigma;};
   
   void SetRawSignalShape(TProfile* raw);
   TProfile* GetRawSignalShape(void) const {return m_rawSignalShape;};
   void SetRawPeakBin(unsigned int bin){m_rawPeakBin = bin;};
   unsigned int GetRawPeakBin(void) const {return m_rawPeakBin;};
   void SetRawPeakValue(float value){m_rawPeakValue = value;};
   float GetRawPeakValue(void) const {return m_rawPeakValue;};
   
   void ExtractRawSlice12(void);
   void SetRawSlice1(float value){m_rawSlice1 = value;};
   float GetRawSlice1(void){return m_rawSlice1;};
   void SetRawSlice2(float value){m_rawSlice2 = value;};
   float GetRawSlice2(void){return m_rawSlice2;};
   
   void ExtractProcessedSlice12(void);
   void SetProcessedSignalShape(TProfile* processed);
   TProfile* GetProcessedSignalShape(void) const {return m_processedSignalShape;};
   void SetProcessedPeakBin(unsigned int bin){m_processedPeakBin = bin;};
   unsigned int GetProcessedPeakBin(void) const {return m_processedPeakBin;};
   void SetProcessedPeakValue(float value){m_processedPeakValue = value;};
   float GetProcessedPeakValue(void) const {return m_processedPeakValue;};
   
   void SetProcessedSlice1(float value){m_processedSlice1 = value;};
   float GetProcessedSlice1(void){return m_processedSlice1;};
   void SetProcessedSlice2(float value){m_processedSlice2 = value;};
   float GetProcessedSlice2(void){return m_processedSlice2;};
   
   void SetRisingSlopeMean(float mean){m_risingSlopeMean = mean;};
   float GetRisingSlopeMean(void) const {return m_risingSlopeMean;};
   void SetRisingSlopeSigma(float sigma){m_risingSlopeSigma = sigma;};
   float GetRisingSlopeSigma(void) const {return m_risingSlopeSigma;};
   
   void SetIsProcessed(bool isProcessed){m_isProcessed = isProcessed;};
   bool GetIsProcessed(void) const {return m_isProcessed;};
   
   void SetCaloDacValue(unsigned int value){m_caloDacValue = value;};
   unsigned int GetCaloDacValue(void) const {return m_caloDacValue;};
   
   void CalculateEffectivePeakValue(std::vector<float> par, std::vector<float> parError);
   float GetEffectivePeakValue(void){return m_effectivePeakValue;};
   float GetEffectivePeakError(void){return m_effectivePeakError;};
   
   
private:
   unsigned int m_runNumber;
   
   unsigned int m_fullDelayData;
   unsigned int m_newFullDelayData;
   
   float m_pedestalMean;
   float m_pedestalSigma;
   
   TProfile* m_rawSignalShape;
   unsigned int m_rawPeakBin;
   float m_rawPeakValue;
   
   float m_rawSlice1;
   float m_rawSlice2;
   
   TProfile* m_processedSignalShape;
   unsigned int m_processedPeakBin;
   float m_processedPeakValue;
   
   float m_processedSlice1;
   float m_processedSlice2;
   
   float m_risingSlopeMean;
   float m_risingSlopeSigma;
   
   bool m_isProcessed;
   
   unsigned int m_caloDacValue;
   
   float m_effectivePeakValue;
   float m_effectivePeakError;
   
   const static unsigned int m_minPedestal = CRE_MIN_PEDESTAL;
   const static unsigned int m_maxPedestal = CRE_MAX_PEDESTAL;
   
   const static unsigned int m_nsStepsPerBc = CRE_NS_PER_BC;
   
};

#endif


