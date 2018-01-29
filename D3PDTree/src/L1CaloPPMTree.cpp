//  *************************************************************************** 
//  *                                                                         * 
//  *   This program is free software; you can redistribute it and/or modify  * 
//  *   it under the terms of the GNU General Public License as published by  * 
//  *   the Free Software Foundation; either version 2 of the License, or     * 
//  *   (at your option) any later version.                                   * 
//  *                                                                         * 
//  *   Author: John Morris (john.morris@cern.ch)                             * 
//  *           Queen Mary University of London                               * 
//  *   File Generated on Wed Aug 18 09:54:59 2010                            * 
//  *                                                                         * 
//  ***************************************************************************/ 

// This class is for accessing the L1CaloPPMTree of the L1Calo Ntuples  
// You should not have to edit this file 

#include "L1CaloPPMTree.h" 

L1CaloPPMTree::L1CaloPPMTree(TTree* tree){ 
  m_currentEvent = 0; 
  this->Init(tree); 
} 

L1CaloPPMTree::~L1CaloPPMTree(){ 
  if (!fChain) return; 
  delete fChain->GetCurrentFile(); 
  delete m_emADC; 
  delete m_emADCPeak; 
  delete m_emBCID; 
  delete m_emBCIDext; 
  delete m_emBCIDvec; 
  delete m_emBadCalo; 
  delete m_emCaloQuality; 
  delete m_emCoolId; 
  delete m_emDeadChannel; 
  delete m_emEnergy; 
  delete m_emError; 
  delete m_emIsSaturated; 
  delete m_emLUT; 
  delete m_emPeak; 
  delete m_emTTCellsEnergy; 
  delete m_emTTCellsEt; 
  delete m_hadADC; 
  delete m_hadADCPeak; 
  delete m_hadBCID; 
  delete m_hadBCIDext; 
  delete m_hadBCIDvec; 
  delete m_hadBadCalo; 
  delete m_hadCaloQuality; 
  delete m_hadCoolId; 
  delete m_hadDeadChannel; 
  delete m_hadEnergy; 
  delete m_hadError; 
  delete m_hadIsSaturated; 
  delete m_hadLUT; 
  delete m_hadPeak; 
  delete m_hadTTCellsEnergy; 
  delete m_hadTTCellsEt; 
  delete m_hadTileCellsEnergy; 
} 

int L1CaloPPMTree::GetEntry(Long64_t entry){ 
  if (!fChain) return 0; 
  return fChain->GetEntry(entry); 
} 

Long64_t L1CaloPPMTree::totalEvents(){ 
  return fChain->GetEntriesFast(); 
} 

Long64_t L1CaloPPMTree::LoadTree(Long64_t entry){ 
  m_currentEvent = entry; 
  if (!fChain) return -5; 
  Long64_t centry = fChain->LoadTree(entry); 
  if (centry < 0) return centry; 
  if (!fChain->InheritsFrom(TChain::Class()))  return centry; 
  TChain *chain = (TChain*)fChain; 
  if (chain->GetTreeNumber() != fCurrent) { 
    fCurrent = chain->GetTreeNumber(); 
  } 
  return centry; 
} 

void L1CaloPPMTree::Init(TTree* tree){ 
  m_EventNumber = 0; 
  m_RunNumber = 0; 
  m_bcid = 0; 
  m_detmask0 = 0; 
  m_detmask1 = 0; 
  m_emADC = 0; 
  m_emADCPeak = 0; 
  m_emBCID = 0; 
  m_emBCIDext = 0; 
  m_emBCIDvec = 0; 
  m_emBadCalo = 0; 
  m_emCaloQuality = 0; 
  m_emCoolId = 0; 
  m_emDeadChannel = 0; 
  m_emEnergy = 0; 
  m_emError = 0; 
  m_emIsSaturated = 0; 
  m_emLUT = 0; 
  m_emPeak = 0; 
  m_emTTCellsEnergy = 0; 
  m_emTTCellsEt = 0; 
  m_hadADC = 0; 
  m_hadADCPeak = 0; 
  m_hadBCID = 0; 
  m_hadBCIDext = 0; 
  m_hadBCIDvec = 0; 
  m_hadBadCalo = 0; 
  m_hadCaloQuality = 0; 
  m_hadCoolId = 0; 
  m_hadDeadChannel = 0; 
  m_hadEnergy = 0; 
  m_hadError = 0; 
  m_hadIsSaturated = 0; 
  m_hadLUT = 0; 
  m_hadPeak = 0; 
  m_hadTTCellsEnergy = 0; 
  m_hadTTCellsEt = 0; 
  m_hadTileCellsEnergy = 0; 
  m_lbn = 0; 
  m_timestamp = 0; 
  m_timestamp_ns = 0; 

  if (!tree) return; 
  fChain = tree; 
  fCurrent = -1; 
  fChain->SetMakeClass(1); 

  fChain->SetBranchAddress("EventNumber", &m_EventNumber, &b_EventNumber); 
  fChain->SetBranchAddress("RunNumber", &m_RunNumber, &b_RunNumber); 
  fChain->SetBranchAddress("bcid", &m_bcid, &b_bcid); 
  fChain->SetBranchAddress("detmask0", &m_detmask0, &b_detmask0); 
  fChain->SetBranchAddress("detmask1", &m_detmask1, &b_detmask1); 
  fChain->SetBranchAddress("emADC", &m_emADC, &b_emADC); 
  fChain->SetBranchAddress("emADCPeak", &m_emADCPeak, &b_emADCPeak); 
  fChain->SetBranchAddress("emBCID", &m_emBCID, &b_emBCID); 
  fChain->SetBranchAddress("emBCIDext", &m_emBCIDext, &b_emBCIDext); 
  fChain->SetBranchAddress("emBCIDvec", &m_emBCIDvec, &b_emBCIDvec); 
  fChain->SetBranchAddress("emBadCalo", &m_emBadCalo, &b_emBadCalo); 
  fChain->SetBranchAddress("emCaloQuality", &m_emCaloQuality, &b_emCaloQuality); 
  fChain->SetBranchAddress("emCoolId", &m_emCoolId, &b_emCoolId); 
  fChain->SetBranchAddress("emDeadChannel", &m_emDeadChannel, &b_emDeadChannel); 
  fChain->SetBranchAddress("emEnergy", &m_emEnergy, &b_emEnergy); 
  fChain->SetBranchAddress("emError", &m_emError, &b_emError); 
  fChain->SetBranchAddress("emIsSaturated", &m_emIsSaturated, &b_emIsSaturated); 
  fChain->SetBranchAddress("emLUT", &m_emLUT, &b_emLUT); 
  fChain->SetBranchAddress("emPeak", &m_emPeak, &b_emPeak); 
  fChain->SetBranchAddress("emTTCellsEnergy", &m_emTTCellsEnergy, &b_emTTCellsEnergy); 
  fChain->SetBranchAddress("emTTCellsEt", &m_emTTCellsEt, &b_emTTCellsEt); 
  fChain->SetBranchAddress("hadADC", &m_hadADC, &b_hadADC); 
  fChain->SetBranchAddress("hadADCPeak", &m_hadADCPeak, &b_hadADCPeak); 
  fChain->SetBranchAddress("hadBCID", &m_hadBCID, &b_hadBCID); 
  fChain->SetBranchAddress("hadBCIDext", &m_hadBCIDext, &b_hadBCIDext); 
  fChain->SetBranchAddress("hadBCIDvec", &m_hadBCIDvec, &b_hadBCIDvec); 
  fChain->SetBranchAddress("hadBadCalo", &m_hadBadCalo, &b_hadBadCalo); 
  fChain->SetBranchAddress("hadCaloQuality", &m_hadCaloQuality, &b_hadCaloQuality); 
  fChain->SetBranchAddress("hadCoolId", &m_hadCoolId, &b_hadCoolId); 
  fChain->SetBranchAddress("hadDeadChannel", &m_hadDeadChannel, &b_hadDeadChannel); 
  fChain->SetBranchAddress("hadEnergy", &m_hadEnergy, &b_hadEnergy); 
  fChain->SetBranchAddress("hadError", &m_hadError, &b_hadError); 
  fChain->SetBranchAddress("hadIsSaturated", &m_hadIsSaturated, &b_hadIsSaturated); 
  fChain->SetBranchAddress("hadLUT", &m_hadLUT, &b_hadLUT); 
  fChain->SetBranchAddress("hadPeak", &m_hadPeak, &b_hadPeak); 
  fChain->SetBranchAddress("hadTTCellsEnergy", &m_hadTTCellsEnergy, &b_hadTTCellsEnergy); 
  fChain->SetBranchAddress("hadTTCellsEt", &m_hadTTCellsEt, &b_hadTTCellsEt); 
  fChain->SetBranchAddress("hadTileCellsEnergy", &m_hadTileCellsEnergy, &b_hadTileCellsEnergy); 
  fChain->SetBranchAddress("lbn", &m_lbn, &b_lbn); 
  fChain->SetBranchAddress("timestamp", &m_timestamp, &b_timestamp); 
  fChain->SetBranchAddress("timestamp_ns", &m_timestamp_ns, &b_timestamp_ns); 
} 

