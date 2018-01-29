//  *************************************************************************** 
//  *                                                                         * 
//  *   This program is free software; you can redistribute it and/or modify  * 
//  *   it under the terms of the GNU General Public License as published by  * 
//  *   the Free Software Foundation; either version 2 of the License, or     * 
//  *   (at your option) any later version.                                   * 
//  *                                                                         * 
//  *   Author: John Morris (john.morris@cern.ch)                             * 
//  *           Queen Mary University of London                               * 
//  *   File Generated on Wed Aug 18 09:54:58 2010                            * 
//  *                                                                         * 
//  ***************************************************************************/ 

// This class is for accessing the L1CaloPPMdbTree of the L1Calo Ntuples  
// You should not have to edit this file 

#ifndef _L1CALO_NTUPLE_L1CALOPPMDBTREE_H_ 
#define _L1CALO_NTUPLE_L1CALOPPMDBTREE_H_ 

#include <TROOT.h> 
#include <TChain.h> 
#include <TFile.h> 
#include <vector> 
using std::vector; 
#include <string> 
using std::string; 
#include <iostream>
using std::cout;

#include "L1CaloPPMdbRxGainBugFixTree.h"

class L1CaloPPMdbTree{ 
  public: 
    explicit L1CaloPPMdbTree(TTree* tree); 
    ~L1CaloPPMdbTree(); 
    Long64_t totalEvents(); 
    Long64_t LoadTree(Long64_t entry); 

    // public inline member functions -- Use these to get access to the TTree variables 
   int  BcidEnergyRangeHigh(unsigned int& coolId); 
   int  BcidEnergyRangeLow(unsigned int& coolId); 
   double  DacOffset(unsigned int& coolId); 
   double  DacSlope(unsigned int& coolId); 
   int  FirCoeff1(unsigned int& coolId); 
   int  FirCoeff2(unsigned int& coolId); 
   int  FirCoeff3(unsigned int& coolId); 
   int  FirCoeff4(unsigned int& coolId); 
   int  FirCoeff5(unsigned int& coolId); 
   int  FirStartBit(unsigned int& coolId); 
   int  FullDelayData(unsigned int& coolId); 
   int  LutNoiseCut(unsigned int& coolId); 
   int  LutOffset(unsigned int& coolId); 
   int  LutSlope(unsigned int& coolId); 
   int  LutStrategy(unsigned int& coolId); 
   int  NCaloCells(unsigned int& coolId); 
   double  PedMean(unsigned int& coolId); 
   int  PedValue(unsigned int& coolId); 
   vector<double>   RxGain(unsigned int& coolId); 
   vector<int>   RxStatus(unsigned int& coolId); 
   int  SatBcidLevel(unsigned int& coolId); 
   int  SatBcidThreshHigh(unsigned int& coolId); 
   int  SatBcidThreshLow(unsigned int& coolId); 
   double  atlasPhi(unsigned int& coolId); 
   double  eta(unsigned int& coolId); 
   double  l1caloPhi(unsigned int& coolId); 


    inline Long64_t currentEvent() const {return m_currentEvent;} 
    Int_t    GetEntry(Long64_t entry); 
    
  //protected: 
    void     Init(TTree *tree); 
    unsigned int findCoolId(unsigned int& coolId); 

  //private: 
    L1CaloPPMdbTree(); 
    L1CaloPPMdbTree(const L1CaloPPMdbTree& rhs);  
    void operator=(const L1CaloPPMdbTree& rhs); 

    L1CaloPPMdbRxGainBugFixTree* m_bugFix;
    TChain* m_bugFixChain;

    TTree          *fChain; 
    int             fCurrent; 

    Long64_t m_currentEvent; 
    unsigned int m_currentCoolId; 
    unsigned int m_currentCoolIdLocation; 

    vector<int>*  m_BcidEnergyRangeHigh; 
    vector<int>*  m_BcidEnergyRangeLow; 
    vector<unsigned int>*  m_CoolId; 
    vector<double>*  m_DacOffset; 
    vector<double>*  m_DacSlope; 
    vector<int>*  m_FirCoeff1; 
    vector<int>*  m_FirCoeff2; 
    vector<int>*  m_FirCoeff3; 
    vector<int>*  m_FirCoeff4; 
    vector<int>*  m_FirCoeff5; 
    vector<int>*  m_FirStartBit; 
    vector<int>*  m_FullDelayData; 
    vector<int>*  m_LutNoiseCut; 
    vector<int>*  m_LutOffset; 
    vector<int>*  m_LutSlope; 
    vector<int>*  m_LutStrategy; 
    vector<int>*  m_NCaloCells; 
    vector<double>*  m_PedMean; 
    vector<int>*  m_PedValue; 
    vector<vector<double> >*  m_RxGain; 
    vector<vector<int> >*  m_RxStatus; 
    vector<int>*  m_SatBcidLevel; 
    vector<int>*  m_SatBcidThreshHigh; 
    vector<int>*  m_SatBcidThreshLow; 
    vector<double>*  m_atlasPhi; 
    vector<double>*  m_eta; 
    vector<double>*  m_l1caloPhi; 

    TBranch*  b_BcidEnergyRangeHigh; 
    TBranch*  b_BcidEnergyRangeLow; 
    TBranch*  b_CoolId; 
    TBranch*  b_DacOffset; 
    TBranch*  b_DacSlope; 
    TBranch*  b_FirCoeff1; 
    TBranch*  b_FirCoeff2; 
    TBranch*  b_FirCoeff3; 
    TBranch*  b_FirCoeff4; 
    TBranch*  b_FirCoeff5; 
    TBranch*  b_FirStartBit; 
    TBranch*  b_FullDelayData; 
    TBranch*  b_LutNoiseCut; 
    TBranch*  b_LutOffset; 
    TBranch*  b_LutSlope; 
    TBranch*  b_LutStrategy; 
    TBranch*  b_NCaloCells; 
    TBranch*  b_PedMean; 
    TBranch*  b_PedValue; 
    TBranch*  b_RxGain; 
    TBranch*  b_RxStatus; 
    TBranch*  b_SatBcidLevel; 
    TBranch*  b_SatBcidThreshHigh; 
    TBranch*  b_SatBcidThreshLow; 
    TBranch*  b_atlasPhi; 
    TBranch*  b_eta; 
    TBranch*  b_l1caloPhi; 
}; 
#endif 

