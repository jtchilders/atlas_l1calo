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

#ifndef _L1CALO_NTUPLE_L1CALOPPMTREE_H_ 
#define _L1CALO_NTUPLE_L1CALOPPMTREE_H_ 

#include <TROOT.h> 
#include <TChain.h> 
#include <TFile.h> 
#include <vector> 
using std::vector; 
#include <string> 
using std::string; 
#include <map> 
using std::map; 

class L1CaloPPMTree{ 
  public: 
    explicit L1CaloPPMTree(TTree* tree); 
    ~L1CaloPPMTree(); 
    Long64_t totalEvents(); 
    Long64_t LoadTree(Long64_t entry); 

    // public inline member functions -- Use these to get access to the TTree variables 
    inline UInt_t  EventNumber() const {b_EventNumber->GetEntry(m_currentEvent);return m_EventNumber;} 
    inline UInt_t  RunNumber() const {b_RunNumber->GetEntry(m_currentEvent);return m_RunNumber;} 
    inline UInt_t  bcid() const {b_bcid->GetEntry(m_currentEvent);return m_bcid;} 
    inline UInt_t  detmask0() const {b_detmask0->GetEntry(m_currentEvent);return m_detmask0;} 
    inline UInt_t  detmask1() const {b_detmask1->GetEntry(m_currentEvent);return m_detmask1;} 
    inline vector<vector<int> >*  emADC() const {b_emADC->GetEntry(m_currentEvent);return m_emADC;} 
    inline vector<int>*  emADCPeak() const {b_emADCPeak->GetEntry(m_currentEvent);return m_emADCPeak;} 
    inline vector<int>*  emBCID() const {b_emBCID->GetEntry(m_currentEvent);return m_emBCID;} 
    inline vector<vector<int> >*  emBCIDext() const {b_emBCIDext->GetEntry(m_currentEvent);return m_emBCIDext;} 
    inline vector<vector<int> >*  emBCIDvec() const {b_emBCIDvec->GetEntry(m_currentEvent);return m_emBCIDvec;} 
    inline vector<int>*  emBadCalo() const {b_emBadCalo->GetEntry(m_currentEvent);return m_emBadCalo;} 
    inline vector<double>*  emCaloQuality() const {b_emCaloQuality->GetEntry(m_currentEvent);return m_emCaloQuality;} 
    inline vector<unsigned int>*  emCoolId() const {b_emCoolId->GetEntry(m_currentEvent);return m_emCoolId;} 
    inline vector<int>*  emDeadChannel() const {b_emDeadChannel->GetEntry(m_currentEvent);return m_emDeadChannel;} 
    inline vector<int>*  emEnergy() const {b_emEnergy->GetEntry(m_currentEvent);return m_emEnergy;} 
    inline vector<int>*  emError() const {b_emError->GetEntry(m_currentEvent);return m_emError;} 
    inline vector<int>*  emIsSaturated() const {b_emIsSaturated->GetEntry(m_currentEvent);return m_emIsSaturated;} 
    inline vector<vector<int> >*  emLUT() const {b_emLUT->GetEntry(m_currentEvent);return m_emLUT;} 
    inline vector<int>*  emPeak() const {b_emPeak->GetEntry(m_currentEvent);return m_emPeak;} 
    inline vector<double>*  emTTCellsEnergy() const {b_emTTCellsEnergy->GetEntry(m_currentEvent);return m_emTTCellsEnergy;} 
    inline vector<double>*  emTTCellsEt() const {b_emTTCellsEt->GetEntry(m_currentEvent);return m_emTTCellsEt;} 
    inline vector<vector<int> >*  hadADC() const {b_hadADC->GetEntry(m_currentEvent);return m_hadADC;} 
    inline vector<int>*  hadADCPeak() const {b_hadADCPeak->GetEntry(m_currentEvent);return m_hadADCPeak;} 
    inline vector<int>*  hadBCID() const {b_hadBCID->GetEntry(m_currentEvent);return m_hadBCID;} 
    inline vector<vector<int> >*  hadBCIDext() const {b_hadBCIDext->GetEntry(m_currentEvent);return m_hadBCIDext;} 
    inline vector<vector<int> >*  hadBCIDvec() const {b_hadBCIDvec->GetEntry(m_currentEvent);return m_hadBCIDvec;} 
    inline vector<int>*  hadBadCalo() const {b_hadBadCalo->GetEntry(m_currentEvent);return m_hadBadCalo;} 
    inline vector<double>*  hadCaloQuality() const {b_hadCaloQuality->GetEntry(m_currentEvent);return m_hadCaloQuality;} 
    inline vector<unsigned int>*  hadCoolId() const {b_hadCoolId->GetEntry(m_currentEvent);return m_hadCoolId;} 
    inline vector<int>*  hadDeadChannel() const {b_hadDeadChannel->GetEntry(m_currentEvent);return m_hadDeadChannel;} 
    inline vector<int>*  hadEnergy() const {b_hadEnergy->GetEntry(m_currentEvent);return m_hadEnergy;} 
    inline vector<int>*  hadError() const {b_hadError->GetEntry(m_currentEvent);return m_hadError;} 
    inline vector<int>*  hadIsSaturated() const {b_hadIsSaturated->GetEntry(m_currentEvent);return m_hadIsSaturated;} 
    inline vector<vector<int> >*  hadLUT() const {b_hadLUT->GetEntry(m_currentEvent);return m_hadLUT;} 
    inline vector<int>*  hadPeak() const {b_hadPeak->GetEntry(m_currentEvent);return m_hadPeak;} 
    inline vector<double>*  hadTTCellsEnergy() const {b_hadTTCellsEnergy->GetEntry(m_currentEvent);return m_hadTTCellsEnergy;} 
    inline vector<double>*  hadTTCellsEt() const {b_hadTTCellsEt->GetEntry(m_currentEvent);return m_hadTTCellsEt;} 
    inline vector<double>*  hadTileCellsEnergy() const {b_hadTileCellsEnergy->GetEntry(m_currentEvent);return m_hadTileCellsEnergy;} 
    inline UInt_t  lbn() const {b_lbn->GetEntry(m_currentEvent);return m_lbn;} 
    inline UInt_t  timestamp() const {b_timestamp->GetEntry(m_currentEvent);return m_timestamp;} 
    inline UInt_t  timestamp_ns() const {b_timestamp_ns->GetEntry(m_currentEvent);return m_timestamp_ns;} 

    inline Long64_t currentEvent() const {return m_currentEvent;} 

  protected: 
    Int_t    GetEntry(Long64_t entry); 
    void     Init(TTree *tree); 

  private: 
    L1CaloPPMTree(); 
    L1CaloPPMTree(const L1CaloPPMTree& rhs);  
    void operator=(const L1CaloPPMTree& rhs); 

    TTree          *fChain; 
    int             fCurrent; 

    Long64_t m_currentEvent; 

    UInt_t  m_EventNumber; 
    UInt_t  m_RunNumber; 
    UInt_t  m_bcid; 
    UInt_t  m_detmask0; 
    UInt_t  m_detmask1; 
    vector<vector<int> >*  m_emADC; 
    vector<int>*  m_emADCPeak; 
    vector<int>*  m_emBCID; 
    vector<vector<int> >*  m_emBCIDext; 
    vector<vector<int> >*  m_emBCIDvec; 
    vector<int>*  m_emBadCalo; 
    vector<double>*  m_emCaloQuality; 
    vector<unsigned int>*  m_emCoolId; 
    vector<int>*  m_emDeadChannel; 
    vector<int>*  m_emEnergy; 
    vector<int>*  m_emError; 
    vector<int>*  m_emIsSaturated; 
    vector<vector<int> >*  m_emLUT; 
    vector<int>*  m_emPeak; 
    vector<double>*  m_emTTCellsEnergy; 
    vector<double>*  m_emTTCellsEt; 
    vector<vector<int> >*  m_hadADC; 
    vector<int>*  m_hadADCPeak; 
    vector<int>*  m_hadBCID; 
    vector<vector<int> >*  m_hadBCIDext; 
    vector<vector<int> >*  m_hadBCIDvec; 
    vector<int>*  m_hadBadCalo; 
    vector<double>*  m_hadCaloQuality; 
    vector<unsigned int>*  m_hadCoolId; 
    vector<int>*  m_hadDeadChannel; 
    vector<int>*  m_hadEnergy; 
    vector<int>*  m_hadError; 
    vector<int>*  m_hadIsSaturated; 
    vector<vector<int> >*  m_hadLUT; 
    vector<int>*  m_hadPeak; 
    vector<double>*  m_hadTTCellsEnergy; 
    vector<double>*  m_hadTTCellsEt; 
    vector<double>*  m_hadTileCellsEnergy; 
    UInt_t  m_lbn; 
    UInt_t  m_timestamp; 
    UInt_t  m_timestamp_ns; 

    TBranch*  b_EventNumber; 
    TBranch*  b_RunNumber; 
    TBranch*  b_bcid; 
    TBranch*  b_detmask0; 
    TBranch*  b_detmask1; 
    TBranch*  b_emADC; 
    TBranch*  b_emADCPeak; 
    TBranch*  b_emBCID; 
    TBranch*  b_emBCIDext; 
    TBranch*  b_emBCIDvec; 
    TBranch*  b_emBadCalo; 
    TBranch*  b_emCaloQuality; 
    TBranch*  b_emCoolId; 
    TBranch*  b_emDeadChannel; 
    TBranch*  b_emEnergy; 
    TBranch*  b_emError; 
    TBranch*  b_emIsSaturated; 
    TBranch*  b_emLUT; 
    TBranch*  b_emPeak; 
    TBranch*  b_emTTCellsEnergy; 
    TBranch*  b_emTTCellsEt; 
    TBranch*  b_hadADC; 
    TBranch*  b_hadADCPeak; 
    TBranch*  b_hadBCID; 
    TBranch*  b_hadBCIDext; 
    TBranch*  b_hadBCIDvec; 
    TBranch*  b_hadBadCalo; 
    TBranch*  b_hadCaloQuality; 
    TBranch*  b_hadCoolId; 
    TBranch*  b_hadDeadChannel; 
    TBranch*  b_hadEnergy; 
    TBranch*  b_hadError; 
    TBranch*  b_hadIsSaturated; 
    TBranch*  b_hadLUT; 
    TBranch*  b_hadPeak; 
    TBranch*  b_hadTTCellsEnergy; 
    TBranch*  b_hadTTCellsEt; 
    TBranch*  b_hadTileCellsEnergy; 
    TBranch*  b_lbn; 
    TBranch*  b_timestamp; 
    TBranch*  b_timestamp_ns; 
}; 
#endif 

