//  *************************************************************************** 
//  *                                                                         * 
//  *   This program is free software; you can redistribute it and/or modify  * 
//  *   it under the terms of the GNU General Public License as published by  * 
//  *   the Free Software Foundation; either version 2 of the License, or     * 
//  *   (at your option) any later version.                                   * 
//  *                                                                         * 
//  *   Author: John Morris (john.morris@cern.ch)                             * 
//  *           Queen Mary University of London                               * 
//  *   File Generated on Wed Aug 18 11:26:42 2010                            * 
//  *                                                                         * 
//  ***************************************************************************/ 

// This class is for accessing the L1CaloPPMdbTree of the L1Calo Ntuples  
// You should not have to edit this file 

#ifndef _L1CALO_NTUPLE_L1CALOPPMDBRXGAINBUGFIXTREE_H_ 
#define _L1CALO_NTUPLE_L1CALOPPMDBRXGAINBUGFIXTREE_H_ 

#include <TROOT.h> 
#include <TChain.h> 
#include <TFile.h> 
#include <vector> 
using std::vector; 
#include <string> 
using std::string; 

class L1CaloPPMdbRxGainBugFixTree{ 
  public: 
    explicit L1CaloPPMdbRxGainBugFixTree(TTree* tree); 
    ~L1CaloPPMdbRxGainBugFixTree(); 
    Long64_t totalEvents(); 
    Long64_t LoadTree(Long64_t entry); 

    // public inline member functions -- Use these to get access to the TTree variables 
   vector<double>   RxGain(unsigned int& coolId); 
   vector<int>   RxStatus(unsigned int& coolId); 


    inline Long64_t currentEvent() const {return m_currentEvent;} 

  protected: 
    Int_t    GetEntry(Long64_t entry); 
    void     Init(TTree *tree); 
    unsigned int findCoolId(unsigned int& coolId); 

  private: 
    L1CaloPPMdbRxGainBugFixTree(); 
    L1CaloPPMdbRxGainBugFixTree(const L1CaloPPMdbRxGainBugFixTree& rhs);  
    void operator=(const L1CaloPPMdbRxGainBugFixTree& rhs); 

    TTree          *fChain; 
    int             fCurrent; 

    Long64_t m_currentEvent; 
    unsigned int m_currentCoolId; 
    unsigned int m_currentCoolIdLocation; 

    vector<unsigned int>*  m_CoolId; 
    vector<vector<double> >*  m_RxGain; 
    vector<vector<int> >*  m_RxStatus; 

    TBranch*  b_CoolId; 
    TBranch*  b_RxGain; 
    TBranch*  b_RxStatus; 
}; 
#endif 

