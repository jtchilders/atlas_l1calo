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

// This class is for accessing the L1CaloPPMdbTree of the Top Ntuples  
// You should not have to edit this file 

#include "L1CaloPPMdbRxGainBugFixTree.h" 

L1CaloPPMdbRxGainBugFixTree::L1CaloPPMdbRxGainBugFixTree(TTree* tree){ 
  m_currentEvent = 0; 
  m_currentCoolId = 0; 
  m_currentCoolIdLocation = 0; 
  this->Init(tree); 
} 

L1CaloPPMdbRxGainBugFixTree::~L1CaloPPMdbRxGainBugFixTree(){ 
  if (!fChain) return; 
  delete fChain->GetCurrentFile(); 
  delete m_CoolId; 
  delete m_RxGain; 
  delete m_RxStatus; 
} 

int L1CaloPPMdbRxGainBugFixTree::GetEntry(Long64_t entry){ 
  if (!fChain) return 0; 
  return fChain->GetEntry(entry); 
} 

Long64_t L1CaloPPMdbRxGainBugFixTree::totalEvents(){ 
  return fChain->GetEntriesFast(); 
} 

Long64_t L1CaloPPMdbRxGainBugFixTree::LoadTree(Long64_t entry){ 
  m_currentEvent = entry; 
  if (!fChain) return -5; 
  Long64_t centry = fChain->LoadTree(entry); 
  if (centry < 0) return centry; 
  if (!fChain->InheritsFrom(TChain::Class()))  return centry; 
  TChain *chain = (TChain*)fChain; 
  if (chain->GetTreeNumber() != fCurrent) { 
    fCurrent = chain->GetTreeNumber(); 
  } 
  centry = fChain->GetEntry(entry); 
  return centry; 
} 

void L1CaloPPMdbRxGainBugFixTree::Init(TTree* tree){ 
  m_CoolId = 0; 
  m_RxGain = 0; 
  m_RxStatus = 0; 

  if (!tree) return; 
  fChain = tree; 
  fCurrent = -1; 
  fChain->SetMakeClass(1); 

  fChain->SetBranchAddress("CoolId", &m_CoolId, &b_CoolId); 
  fChain->SetBranchAddress("RxGain", &m_RxGain, &b_RxGain); 
  fChain->SetBranchAddress("RxStatus", &m_RxStatus, &b_RxStatus); 
} 

unsigned int L1CaloPPMdbRxGainBugFixTree::findCoolId(unsigned int& coolId){ 
  if(m_currentCoolId == coolId){return m_currentCoolIdLocation;} 
  unsigned int location(0); 
  for(vector<unsigned int>::iterator i=m_CoolId->begin();i!=m_CoolId->end();++i){ 
    if((*i) == coolId){ 
      m_currentCoolId = (*i); 
      m_currentCoolIdLocation = location; 
      return m_currentCoolIdLocation; 
    } 
    location++; 
  } 
  return location; 
} 

vector<double>  L1CaloPPMdbRxGainBugFixTree::RxGain(unsigned int& coolId){ 
  return m_RxGain->at(this->findCoolId(coolId)); 
} 

vector<int>  L1CaloPPMdbRxGainBugFixTree::RxStatus(unsigned int& coolId){ 
  return m_RxStatus->at(this->findCoolId(coolId)); 
} 


