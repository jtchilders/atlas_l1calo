#ifndef SATBCIDTREE_H
#define SATBCIDTREE_H

#include "TGraph.h"
#include "TF1.h"
#include "TTree.h"
#include "TFile.h"

#include "L1CaloChannelId.h"
#include "L1CaloChannelMap.h"

#include <iostream>
#include <string>

class SatBcidTree{
public:
   SatBcidTree(void);
   ~SatBcidTree(void);
   
   void SetReadMode(void)  {m_readMode = true; m_createMode=false;m_updateMode=false;};
   void SetCreateMode(void){m_readMode = false;m_createMode=true; m_updateMode=false;};
   void SetUpdateMode(void){m_readMode = false;m_createMode=false;m_updateMode=true; };
   
   void CloseFile(void);
   bool OpenFile(void);
   bool OpenFile(std::string filename);
   bool OpenFile(TFile* file);
   
   void ClearTree(void);
   
   TTree* GetTree(void){return m_tree;};
   
   void Fill(void){m_tree->Fill();};
   void Write(void);
   
   int GetEntries(void){return m_tree->GetEntries();};
   void GetEntry(int entry){m_tree->GetEntry(entry);};
   
   void DeleteEntry(void);
   unsigned int FindEntry(const L1CaloChannelId findCoolId);
   
   // Access to tree variables
   
   void SetCoolId(unsigned int id){m_t_coolId = id;};
   unsigned int GetCoolId(void){return m_t_coolId;};
   
   void SetSatHigh(unsigned int value){m_t_satHigh = value;};
   unsigned int GetSatHigh(void){return m_t_satHigh;};
   void SetSatLow(unsigned int value){m_t_satLow = value;};
   unsigned int GetSatLow(void){return m_t_satLow;};
   void SetSatLevel(unsigned int value){m_t_satLevel = value;};
   unsigned int GetSatLevel(void){return m_t_satLevel;};
   
   void SetRawDacVsAdcPeakGraph(TGraph* value){m_t_raw_dacVsAdc = value;};
   TGraph* GetRawDacVsAdcPeakGraph(void){return m_t_raw_dacVsAdc;};
   void SetRawDacVsAdcPeakFit(TF1* value){m_t_raw_dacVsAdcFit = value;};
   TF1* GetRawDacVsAdcPeakFit(void){return m_t_raw_dacVsAdcFit;};
   void SetRawPeakVsTs1Graph(TGraph* value){m_t_raw_peakVsTs1 = value;};
   TGraph* GetRawPeakVsTs1Graph(void){return m_t_raw_peakVsTs1;};
   void SetRawPeakVsTs1Fit(TF1* value){m_t_raw_ts1LinearFit = value;};
   TF1* GetRawPeakVsTs1Fit(void){return m_t_raw_ts1LinearFit;};
   void SetRawSatHigh(unsigned int value){m_t_raw_satHigh = value;};
   unsigned int GetRawSatHigh(void){return m_t_raw_satHigh;};
   void SetRawPeakVsTs2Graph(TGraph* value){m_t_raw_peakVsTs2 = value;};
   TGraph* GetRawPeakVsTs2Graph(void){return m_t_raw_peakVsTs2;};
   void SetRawPeakVsTs2Fit(TF1* value){m_t_raw_ts2LinearFit = value;};
   TF1* GetRawPeakVsTs2Fit(void){return m_t_raw_ts2LinearFit;};
   void SetRawSatLow(unsigned int value){m_t_raw_satLow = value;};
   unsigned int GetRawSatLow(void){return m_t_raw_satLow;};
   void SetRawSatLevel(unsigned int value){m_t_raw_satLevel = value;};
   unsigned int GetRawSatLevel(void){return m_t_raw_satLevel;};
   
   void SetProcessedDacVsAdcPeakGraph(TGraph* value){m_t_processed_dacVsAdc = value;};
   TGraph* GetProcessedDacVsAdcPeakGraph(void){return m_t_processed_dacVsAdc;};
   void SetProcessedDacVsAdcPeakFit(TF1* value){m_t_processed_dacVsAdcFit = value;};
   TF1* GetProcessedDacVsAdcPeakFit(void){return m_t_processed_dacVsAdcFit;};
   void SetProcessedPeakVsTs1Graph(TGraph* value){m_t_processed_peakVsTs1 = value;};
   TGraph* GetProcessedPeakVsTs1Graph(void){return m_t_processed_peakVsTs1;};
   void SetProcessedPeakVsTs1Fit(TF1* value){m_t_processed_ts1LinearFit = value;};
   TF1* GetProcessedPeakVsTs1Fit(void){return m_t_processed_ts1LinearFit;};
   void SetProcessedSatHigh(unsigned int value){m_t_processed_satHigh = value;};
   unsigned int GetProcessedSatHigh(void){return m_t_processed_satHigh;};
   void SetProcessedPeakVsTs2Graph(TGraph* value){m_t_processed_peakVsTs2 = value;};
   TGraph* GetProcessedPeakVsTs2Graph(void){return m_t_processed_peakVsTs2;};
   void SetProcessedPeakVsTs2Fit(TF1* value){m_t_processed_ts2LinearFit = value;};
   TF1* GetProcessedPeakVsTs2Fit(void){return m_t_processed_ts2LinearFit;};
   void SetProcessedSatLow(unsigned int value){m_t_processed_satLow = value;};
   unsigned int GetProcessedSatLow(void){return m_t_processed_satLow;};
   void SetProcessedSatLevel(unsigned int value){m_t_processed_satLevel = value;};
   unsigned int GetProcessedSatLevel(void){return m_t_processed_satLevel;};
   
   void SetIsEnabled(bool value){m_t_isEnabled = value;};
   bool GetIsEnabled(void){return m_t_isEnabled;};
   void SetIsValid(bool value){m_t_isValid = value;};
   bool GetIsValid(void){return m_t_isValid;};
   void SetIsProcessed(bool value){m_t_isProcessed = value;};
   bool GetIsProcessed(void){return m_t_isProcessed;};
   
   void SetPedestalMean(float value){m_t_pedestalMean = value;};
   float GetPedestalMean(void){return m_t_pedestalMean;};
   void SetPedestalSigma(float value){m_t_pedestalSigma = value;};
   float GetPedestalSigma(void){return m_t_pedestalSigma;};
   
   void SetRawDacVsAdcSlopeMean(float value){m_t_raw_dacVsAdcSlopeMean = value;};
   float GetRawDacVsAdcSlopeMean(void){return m_t_raw_dacVsAdcSlopeMean;};
   void SetRawDacVsAdcSlopeSigma(float value){m_t_raw_dacVsAdcSlopeSigma = value;};
   float GetRawDacVsAdcSlopeSigma(void){return m_t_raw_dacVsAdcSlopeSigma;};
   void SetProcessedDacVsAdcSlopeMean(float value){m_t_processed_dacVsAdcSlopeMean = value;};
   float GetProcessedDacVsAdcSlopeMean(void){return m_t_processed_dacVsAdcSlopeMean;};
   void SetProcessedDacVsAdcSlopeSigma(float value){m_t_processed_dacVsAdcSlopeSigma = value;};
   float GetProcessedDacVsAdcSlopeSigma(void){return m_t_processed_dacVsAdcSlopeSigma;};
   
   void SetRawPeakBin(unsigned int value){m_t_raw_peakBin = value;};
   unsigned int GetRawPeakBin(void){return m_t_raw_peakBin;};
   void SetProcessedPeakBin(unsigned int value){m_t_processed_peakBin = value;};
   unsigned int GetProcessedPeakBin(void){return m_t_processed_peakBin;};
   
   void SetErrorCode(unsigned int value){m_t_errorCode = value;}; 
   unsigned int GetErrorCode(void) const {return m_t_errorCode;};
   
   void SetPhos4ErrorCode(unsigned int value){m_t_phos4errorCode = value;}; 
   unsigned int GetPhos4ErrorCode(void) const {return m_t_phos4errorCode;};
   
private:
   
   bool m_readMode;
   bool m_createMode;
   bool m_updateMode;
   
   std::string m_s_treeFilename;
   TFile* m_treeFile;
   
   TTree* m_tree;
   std::string m_s_treename;
   
   bool m_useNewTree;
   
   unsigned int m_currentEntry;
   
   unsigned int m_runNumber;
   unsigned int m_dacBarrel;
   unsigned int m_dacEmec;
   unsigned int m_dacFcal;
   unsigned int m_dacHec;
   
   void Initialize(void);
   void CrateBranches(void);
   void SetBranchAddresses(void);
   
   // TTree entries
   unsigned int m_t_coolId;
   std::string  m_t_s_coolId;
   
   unsigned int m_t_phos4errorCode;
   std::string  m_t_s_phos4errorCode;
   
   unsigned int m_t_errorCode;
   std::string  m_t_s_errorCode;
   
   unsigned int m_t_satHigh;
   std::string  m_t_s_satHigh;
   unsigned int m_t_satLow;
   std::string  m_t_s_satLow;
   unsigned int m_t_satLevel;
   std::string  m_t_s_satLevel;
   
   TGraph*      m_t_raw_dacVsAdc;
   std::string  m_t_s_raw_dacVsAdc;
   TF1*         m_t_raw_dacVsAdcFit;
   std::string  m_t_s_raw_dacVsAdcFit;
   
   TGraph*      m_t_processed_dacVsAdc;
   std::string  m_t_s_processed_dacVsAdc;
   TF1*         m_t_processed_dacVsAdcFit;
   std::string  m_t_s_processed_dacVsAdcFit;
   
   TGraph*      m_t_raw_peakVsTs1;
   std::string  m_t_s_raw_peakVsTs1;
   TF1*         m_t_raw_ts1LinearFit;
   std::string  m_t_s_raw_ts1LinearFit;
   
   unsigned int m_t_raw_satHigh;
   std::string  m_t_s_raw_satHigh;
   
   TGraph*      m_t_raw_peakVsTs2;
   std::string  m_t_s_raw_peakVsTs2;
   TF1*         m_t_raw_ts2LinearFit;
   std::string  m_t_s_raw_ts2LinearFit;
   
   unsigned int m_t_raw_satLow;
   std::string  m_t_s_raw_satLow;
   
   unsigned int m_t_raw_satLevel;
   std::string  m_t_s_raw_satLevel;
   
   TGraph*      m_t_processed_peakVsTs1;
   std::string  m_t_s_processed_peakVsTs1;
   TF1*         m_t_processed_ts1LinearFit;
   std::string  m_t_s_processed_ts1LinearFit;
   
   unsigned int m_t_processed_satHigh;
   std::string  m_t_s_processed_satHigh;
   
   TGraph*      m_t_processed_peakVsTs2;
   std::string  m_t_s_processed_peakVsTs2;
   TF1*         m_t_processed_ts2LinearFit;
   std::string  m_t_s_processed_ts2LinearFit;
   
   unsigned int m_t_processed_satLow;
   std::string  m_t_s_processed_satLow;
   
   unsigned int m_t_processed_satLevel;
   std::string  m_t_s_processed_satLevel;
   
   bool         m_t_isEnabled;
   std::string  m_t_s_isEnabled;
   bool         m_t_isValid;
   std::string  m_t_s_isValid;
   bool         m_t_isProcessed;
   std::string  m_t_s_isProcessed;
   
   float        m_t_pedestalMean;
   std::string  m_t_s_pedestalMean;
   float        m_t_pedestalSigma;
   std::string  m_t_s_pedestalSigma;
   
   float        m_t_raw_dacVsAdcSlopeMean;
   std::string  m_t_s_raw_dacVsAdcSlopeMean;
   float        m_t_raw_dacVsAdcSlopeSigma;
   std::string  m_t_s_raw_dacVsAdcSlopeSigma;
   
   float        m_t_processed_dacVsAdcSlopeMean;
   std::string  m_t_s_processed_dacVsAdcSlopeMean;
   float        m_t_processed_dacVsAdcSlopeSigma;
   std::string  m_t_s_processed_dacVsAdcSlopeSigma;
   
   unsigned int m_t_raw_peakBin;
   std::string  m_t_s_raw_peakBin;
   unsigned int m_t_processed_peakBin;
   std::string  m_t_s_processed_peakBin;
   
};


#endif
