#ifndef SHAPEMAKERTREE_H
#define SHAPEMAKERTREE_H

#include "TProfile.h"
#include "TH1F.h"
#include "TF1.h"
#include "TTree.h"
#include "TFile.h"

#include "L1CaloChannelId.h"
#include "L1CaloChannelMap.h"

#include <iostream>
#include <string>

class ShapeMakerTree{
public:
   ShapeMakerTree(void);
   ShapeMakerTree(std::string filename);
   ~ShapeMakerTree(void);
   
   // File IO Control
   void SetFilename(std::string name){m_s_treeFilename = name;};
   bool OpenFile(void);
   void CloseFile(void);
   
   void GetEntry(unsigned int entry){ClearTree();m_tree->GetEntry(entry);};
   
   void DeleteEntry(void);
   
   unsigned int GetEntries(void) const {return m_tree->GetEntries();};
   
   void ClearTree(void);
   
   unsigned int FindEntry(const L1CaloChannelId findCoolId);
   
   unsigned int GetCurrentEntry(void) const {return m_currentEntry;};
   
   bool GetUseNewTree(void) const {return m_useNewTree;};
   
   void Print(void) const;
   
   TTree* GetTree(void){return m_tree;};
   
   unsigned int GetRunNumber(void){return m_runNumber;};
   void SetRunNumber(unsigned int num){m_runNumber = num;};
   
   unsigned int GetDacForRegion(const CaloDivision& region) const;
   
   unsigned int GetDacBarrel(void){return m_dacBarrel;};
   void SetDacBarrel(unsigned int dac){m_dacBarrel = dac;};
   
   unsigned int GetDacEmec(void){return m_dacEmec;};
   void SetDacEmec(unsigned int dac){m_dacEmec = dac;};
   
   unsigned int GetDacFcal(void){return m_dacFcal;};
   void SetDacFcal(unsigned int dac){m_dacFcal = dac;};
   
   unsigned int GetDacHec(void){return m_dacHec;};
   void SetDacHec(unsigned int dac){m_dacHec = dac;};
   
   bool IsTileRun(void){return m_tileRun;};
   void SetTileRun(bool value){m_tileRun = value;};
   
   bool IsLArRun(void){return m_larRun;};
   void SetLArRun(bool value){m_larRun = value;};
   
   // Access to tree variables
   
   unsigned int GetCoolId(void) const {return m_t_coolId;};
   unsigned int GetCurrentFullDelayData(void) const {return m_t_currentFullDelayData;};
   
   bool GetIsEnabled(void) const {return m_t_isEnabled;};
   bool GetIsValid(void) const {return m_t_isValid;};
   
   float GetPedestalMean(void) const {return m_t_pedestalMean;};
   float GetPedestalSigma(void) const {return m_t_pedestalSigma;};
   
   TProfile* GetRawSignalShape(void) const {return m_t_rawSignalShape;};
   TH1F* GetProcessedSignalShape(void) const {return m_t_processedSignalShape;};
   
   float GetRisingSlopeMean(void) const {return m_t_risingSlopeMean;};
   float GetRisingSlopeSigma(void) const {return m_t_risingSlopeSigma;};
   
   unsigned int GetNewFullDelayData(void) const {return m_t_newFullDelayData;};
   
   float GetRawPeakValue(void) const {return m_t_rawPeakValue;};
   unsigned int GetRawPeakBin(void) const {return m_t_rawPeakBin;};
   
   float GetProcessedPeakValue(void) const {return m_t_processedPeakValue;};
   unsigned int GetProcessedPeakBin(void) const {return m_t_processedPeakBin;};
   
   unsigned int GetRawMaxFullDelayData(void) const {return m_t_rawMaxFullDelayData;};
   unsigned int GetRawFitFullDelayData(void) const {return m_t_rawFitFullDelayData;};
   float GetRawMaxPeakValue(void) const {return m_t_rawMaxPeakValue;};
   unsigned int GetRawMaxPeakBin(void) const {return m_t_rawMaxPeakBin;};
   float GetRawFitPeakValue(void) const {return m_t_rawFitPeakValue;};
   unsigned int GetRawFitPeakBin(void) const {return m_t_rawFitPeakBin;};
   TF1* GetRawFit(void) const {return m_t_rawFit;};
   bool GetRawFitPerformed(void) const {return m_t_rawFitPerformed;};
   
   unsigned int GetProcessedMaxFullDelayData(void) const {return m_t_processedMaxFullDelayData;};
   unsigned int GetProcessedFitFullDelayData(void) const {return m_t_processedFitFullDelayData;};
   float GetProcessedMaxPeakValue(void) const {return m_t_processedMaxPeakValue;};
   unsigned int GetProcessedMaxPeakBin(void) const {return m_t_processedMaxPeakBin;};
   float GetProcessedFitPeakValue(void) const {return m_t_processedFitPeakValue;};
   unsigned int GetProcessedFitPeakBin(void) const {return m_t_processedFitPeakBin;};
   TF1* GetProcessedFit(void) const {return m_t_processedFit;};
   bool GetProcessedFitPerformed(void) const {return m_t_processedFitPerformed;};
   
   unsigned int GetErrorCode(void) const {return m_t_errorCode;};
   
   bool GetIsProcessed(void) const {return m_t_isProcessed;};
   
private:
   
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
   
   bool m_tileRun;
   bool m_larRun;
   
   void Initialize(void);
   void SetBranchAddresses(void);
   
   // TTree branches
   unsigned int m_t_coolId;
   std::string  m_t_s_coolId;
   unsigned int m_t_currentFullDelayData;
   std::string  m_t_s_currentFullDelayData;
   bool         m_t_isEnabled;
   std::string  m_t_s_isEnabled;
   bool         m_t_isValid;
   std::string  m_t_s_isValid;
   float        m_t_pedestalMean;
   std::string  m_t_s_pedestalMean;
   float        m_t_pedestalSigma;
   std::string  m_t_s_pedestalSigma;
   TProfile*    m_t_rawSignalShape;
   std::string  m_t_s_rawSignalShape;
   TH1F*        m_t_processedSignalShape;
   std::string  m_t_s_processedSignalShape;
   float        m_t_risingSlopeMean;
   std::string  m_t_s_risingSlopeMean;
   float        m_t_risingSlopeSigma;
   std::string  m_t_s_risingSlopeSigma;
   
   // old tree branches
   unsigned int m_t_newFullDelayData;
   std::string  m_t_s_newFullDelayData;
   
   float        m_t_rawPeakValue;
   std::string  m_t_s_rawPeakValue;
   unsigned int m_t_rawPeakBin;
   std::string  m_t_s_rawPeakBin;
   
   float        m_t_processedPeakValue;
   std::string  m_t_s_processedPeakValue;
   unsigned int m_t_processedPeakBin;
   std::string  m_t_s_processedPeakBin;
   
   // new tree branches
   unsigned int m_t_rawMaxFullDelayData;
   std::string  m_t_s_rawMaxFullDelayData;
   unsigned int m_t_rawFitFullDelayData;
   std::string  m_t_s_rawFitFullDelayData;
   float        m_t_rawMaxPeakValue;
   std::string  m_t_s_rawMaxPeakValue;
   unsigned int m_t_rawMaxPeakBin;
   std::string  m_t_s_rawMaxPeakBin;
   float        m_t_rawFitPeakValue;
   std::string  m_t_s_rawFitPeakValue;
   unsigned int m_t_rawFitPeakBin;
   std::string  m_t_s_rawFitPeakBin;
   TF1*         m_t_rawFit;
   std::string  m_t_s_rawFit;
   bool         m_t_rawFitPerformed;
   std::string  m_t_s_rawFitPerformed;
   
   unsigned int m_t_processedMaxFullDelayData;
   std::string  m_t_s_processedMaxFullDelayData;
   unsigned int m_t_processedFitFullDelayData;
   std::string  m_t_s_processedFitFullDelayData;
   float        m_t_processedMaxPeakValue;
   std::string  m_t_s_processedMaxPeakValue;
   unsigned int m_t_processedMaxPeakBin;
   std::string  m_t_s_processedMaxPeakBin;
   float        m_t_processedFitPeakValue;
   std::string  m_t_s_processedFitPeakValue;
   unsigned int m_t_processedFitPeakBin;
   std::string  m_t_s_processedFitPeakBin;
   TF1*         m_t_processedFit;
   std::string  m_t_s_processedFit;
   bool         m_t_processedFitPerformed;
   std::string  m_t_s_processedFitPerformed;
   
   unsigned int m_t_errorCode;
   std::string  m_t_s_errorCode;
   
   bool m_t_isProcessed;
   std::string m_t_s_isProcessed;
   
};


#endif
