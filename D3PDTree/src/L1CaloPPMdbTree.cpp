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

// This class is for accessing the L1CaloPPMdbTree of the Top Ntuples  
// You should not have to edit this file 

#include "L1CaloPPMdbTree.h" 

L1CaloPPMdbTree::L1CaloPPMdbTree(TTree* tree){ 
  m_currentEvent = 0; 
  m_currentCoolId = 0; 
  m_currentCoolIdLocation = 0; 
  this->Init(tree); 

  m_bugFixChain = new TChain("L1CaloPPMdbTree","");
  string stringBugFix = "TTrees/RxGainBugFix.root/L1CaloPPMdbTree";
  m_bugFixChain->Add(stringBugFix.c_str());
  m_bugFix = new L1CaloPPMdbRxGainBugFixTree(m_bugFixChain);

} 

L1CaloPPMdbTree::~L1CaloPPMdbTree(){ 
  if (!fChain) return; 
  delete fChain->GetCurrentFile(); 
  delete m_BcidEnergyRangeHigh; 
  delete m_BcidEnergyRangeLow; 
  delete m_CoolId; 
  delete m_DacOffset; 
  delete m_DacSlope; 
  delete m_FirCoeff1; 
  delete m_FirCoeff2; 
  delete m_FirCoeff3; 
  delete m_FirCoeff4; 
  delete m_FirCoeff5; 
  delete m_FirStartBit; 
  delete m_FullDelayData; 
  delete m_LutNoiseCut; 
  delete m_LutOffset; 
  delete m_LutSlope; 
  delete m_LutStrategy; 
  delete m_NCaloCells; 
  delete m_PedMean; 
  delete m_PedValue; 
  delete m_RxGain; 
  delete m_RxStatus; 
  delete m_SatBcidLevel; 
  delete m_SatBcidThreshHigh; 
  delete m_SatBcidThreshLow; 
  delete m_atlasPhi; 
  delete m_eta; 
  delete m_l1caloPhi; 

  delete m_bugFix;

} 

int L1CaloPPMdbTree::GetEntry(Long64_t entry){ 
  if (!fChain) return 0;
  if(m_currentEvent == entry)
     return 0;
  else{
    m_currentEvent = entry;
    return fChain->GetEntry(entry);
  }
  return 0;
} 

Long64_t L1CaloPPMdbTree::totalEvents(){ 
  return fChain->GetEntriesFast(); 
} 

Long64_t L1CaloPPMdbTree::LoadTree(Long64_t entry){ 
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
  m_bugFix->LoadTree(entry);
  return centry; 
} 

void L1CaloPPMdbTree::Init(TTree* tree){ 
  m_BcidEnergyRangeHigh = 0; 
  m_BcidEnergyRangeLow = 0; 
  m_CoolId = 0; 
  m_DacOffset = 0; 
  m_DacSlope = 0; 
  m_FirCoeff1 = 0; 
  m_FirCoeff2 = 0; 
  m_FirCoeff3 = 0; 
  m_FirCoeff4 = 0; 
  m_FirCoeff5 = 0; 
  m_FirStartBit = 0; 
  m_FullDelayData = 0; 
  m_LutNoiseCut = 0; 
  m_LutOffset = 0; 
  m_LutSlope = 0; 
  m_LutStrategy = 0; 
  m_NCaloCells = 0; 
  m_PedMean = 0; 
  m_PedValue = 0; 
  m_RxGain = 0; 
  m_RxStatus = 0; 
  m_SatBcidLevel = 0; 
  m_SatBcidThreshHigh = 0; 
  m_SatBcidThreshLow = 0; 
  m_atlasPhi = 0; 
  m_eta = 0; 
  m_l1caloPhi = 0; 

  if (!tree) return; 
  fChain = tree; 
  fCurrent = -1; 
  fChain->SetMakeClass(1); 

  fChain->SetBranchAddress("BcidEnergyRangeHigh", &m_BcidEnergyRangeHigh, &b_BcidEnergyRangeHigh); 
  fChain->SetBranchAddress("BcidEnergyRangeLow", &m_BcidEnergyRangeLow, &b_BcidEnergyRangeLow); 
  fChain->SetBranchAddress("CoolId", &m_CoolId, &b_CoolId); 
  fChain->SetBranchAddress("DacOffset", &m_DacOffset, &b_DacOffset); 
  fChain->SetBranchAddress("DacSlope", &m_DacSlope, &b_DacSlope); 
  fChain->SetBranchAddress("FirCoeff1", &m_FirCoeff1, &b_FirCoeff1); 
  fChain->SetBranchAddress("FirCoeff2", &m_FirCoeff2, &b_FirCoeff2); 
  fChain->SetBranchAddress("FirCoeff3", &m_FirCoeff3, &b_FirCoeff3); 
  fChain->SetBranchAddress("FirCoeff4", &m_FirCoeff4, &b_FirCoeff4); 
  fChain->SetBranchAddress("FirCoeff5", &m_FirCoeff5, &b_FirCoeff5); 
  fChain->SetBranchAddress("FirStartBit", &m_FirStartBit, &b_FirStartBit); 
  fChain->SetBranchAddress("FullDelayData", &m_FullDelayData, &b_FullDelayData); 
  fChain->SetBranchAddress("LutNoiseCut", &m_LutNoiseCut, &b_LutNoiseCut); 
  fChain->SetBranchAddress("LutOffset", &m_LutOffset, &b_LutOffset); 
  fChain->SetBranchAddress("LutSlope", &m_LutSlope, &b_LutSlope); 
  fChain->SetBranchAddress("LutStrategy", &m_LutStrategy, &b_LutStrategy); 
  fChain->SetBranchAddress("NCaloCells", &m_NCaloCells, &b_NCaloCells); 
  fChain->SetBranchAddress("PedMean", &m_PedMean, &b_PedMean); 
  fChain->SetBranchAddress("PedValue", &m_PedValue, &b_PedValue); 
  fChain->SetBranchAddress("RxGain", &m_RxGain, &b_RxGain); 
  fChain->SetBranchAddress("RxStatus", &m_RxStatus, &b_RxStatus); 
  fChain->SetBranchAddress("SatBcidLevel", &m_SatBcidLevel, &b_SatBcidLevel); 
  fChain->SetBranchAddress("SatBcidThreshHigh", &m_SatBcidThreshHigh, &b_SatBcidThreshHigh); 
  fChain->SetBranchAddress("SatBcidThreshLow", &m_SatBcidThreshLow, &b_SatBcidThreshLow); 
  fChain->SetBranchAddress("atlasPhi", &m_atlasPhi, &b_atlasPhi); 
  fChain->SetBranchAddress("eta", &m_eta, &b_eta); 
  fChain->SetBranchAddress("l1caloPhi", &m_l1caloPhi, &b_l1caloPhi); 
} 

unsigned int L1CaloPPMdbTree::findCoolId(unsigned int& coolId){
  if(m_currentCoolId == coolId){return m_currentCoolIdLocation;}
  else if(m_currentCoolId < coolId){
     for(unsigned int i=m_currentCoolIdLocation+1;i<m_CoolId->size();++i){
        if(m_CoolId->at(i) == coolId){ 
           m_currentCoolId = m_CoolId->at(i);
           m_currentCoolIdLocation = i; 
           return m_currentCoolIdLocation; 
        }
     }
  }
  else if(m_currentCoolId > coolId){
     for(unsigned int i=0;i<m_CoolId->size();++i){
        if(m_CoolId->at(i) == coolId){ 
           m_currentCoolId = m_CoolId->at(i);
           m_currentCoolIdLocation = i; 
           return m_currentCoolIdLocation; 
        }
     }
  }
  return 0; 
} 

int L1CaloPPMdbTree::BcidEnergyRangeHigh(unsigned int& coolId){ 
  return m_BcidEnergyRangeHigh->at(this->findCoolId(coolId)); 
} 

int L1CaloPPMdbTree::BcidEnergyRangeLow(unsigned int& coolId){ 
  return m_BcidEnergyRangeLow->at(this->findCoolId(coolId)); 
} 

double L1CaloPPMdbTree::DacOffset(unsigned int& coolId){ 
  return m_DacOffset->at(this->findCoolId(coolId)); 
} 

double L1CaloPPMdbTree::DacSlope(unsigned int& coolId){ 
  return m_DacSlope->at(this->findCoolId(coolId)); 
} 

int L1CaloPPMdbTree::FirCoeff1(unsigned int& coolId){ 
  return m_FirCoeff1->at(this->findCoolId(coolId)); 
} 

int L1CaloPPMdbTree::FirCoeff2(unsigned int& coolId){ 
  return m_FirCoeff2->at(this->findCoolId(coolId)); 
} 

int L1CaloPPMdbTree::FirCoeff3(unsigned int& coolId){ 
  return m_FirCoeff3->at(this->findCoolId(coolId)); 
} 

int L1CaloPPMdbTree::FirCoeff4(unsigned int& coolId){ 
  return m_FirCoeff4->at(this->findCoolId(coolId)); 
} 

int L1CaloPPMdbTree::FirCoeff5(unsigned int& coolId){ 
  return m_FirCoeff5->at(this->findCoolId(coolId)); 
} 

int L1CaloPPMdbTree::FirStartBit(unsigned int& coolId){ 
  return m_FirStartBit->at(this->findCoolId(coolId)); 
} 

int L1CaloPPMdbTree::FullDelayData(unsigned int& coolId){ 
  return m_FullDelayData->at(this->findCoolId(coolId)); 
} 

int L1CaloPPMdbTree::LutNoiseCut(unsigned int& coolId){ 
  return m_LutNoiseCut->at(this->findCoolId(coolId)); 
} 

int L1CaloPPMdbTree::LutOffset(unsigned int& coolId){ 
  return m_LutOffset->at(this->findCoolId(coolId)); 
} 

int L1CaloPPMdbTree::LutSlope(unsigned int& coolId){ 
  return m_LutSlope->at(this->findCoolId(coolId)); 
} 

int L1CaloPPMdbTree::LutStrategy(unsigned int& coolId){ 
  return m_LutStrategy->at(this->findCoolId(coolId)); 
} 

int L1CaloPPMdbTree::NCaloCells(unsigned int& coolId){ 
  return m_NCaloCells->at(this->findCoolId(coolId)); 
} 

double L1CaloPPMdbTree::PedMean(unsigned int& coolId){ 
  return m_PedMean->at(this->findCoolId(coolId)); 
} 

int L1CaloPPMdbTree::PedValue(unsigned int& coolId){ 
  return m_PedValue->at(this->findCoolId(coolId)); 
} 

vector<double>  L1CaloPPMdbTree::RxGain(unsigned int& coolId){ 
  return m_bugFix->RxGain(coolId);
} 

vector<int>  L1CaloPPMdbTree::RxStatus(unsigned int& coolId){ 
  return m_bugFix->RxStatus(coolId); 
} 

int L1CaloPPMdbTree::SatBcidLevel(unsigned int& coolId){ 
  return m_SatBcidLevel->at(this->findCoolId(coolId)); 
} 

int L1CaloPPMdbTree::SatBcidThreshHigh(unsigned int& coolId){ 
  return m_SatBcidThreshHigh->at(this->findCoolId(coolId)); 
} 

int L1CaloPPMdbTree::SatBcidThreshLow(unsigned int& coolId){ 
  return m_SatBcidThreshLow->at(this->findCoolId(coolId)); 
} 

double L1CaloPPMdbTree::atlasPhi(unsigned int& coolId){ 
  return m_atlasPhi->at(this->findCoolId(coolId)); 
} 

double L1CaloPPMdbTree::eta(unsigned int& coolId){ 
  return m_eta->at(this->findCoolId(coolId)); 
} 

double L1CaloPPMdbTree::l1caloPhi(unsigned int& coolId){ 
  return m_l1caloPhi->at(this->findCoolId(coolId)); 
} 


