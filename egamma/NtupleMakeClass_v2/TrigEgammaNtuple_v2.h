#ifndef TrigEgammaNtuple_v2_h
#define TrigEgammaNtuple_v2_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <cmath>

using namespace std;

class TrigEgammaNtuple_v2 {
  public :
    
   bool hasInfo;
   bool hasTrigger;
   bool hasL1;
   bool hasL2Cluster;
   bool hasL2Electron;
   bool hasL2Photon;
   bool hasL2Track;
   bool hasEFCluster;
   bool hasEFegamma;
   bool hasEFTrack;
   bool hasOFFCluster;
   bool hasOFFegamma;
   bool hasOFFTrack;
   bool hasTruth;
   
   TChain *fChainTruth;
   TChain *fChainInfo;
   TChain *fChainTrigger;
   TChain *fChainL1;
   TChain *fChainL2Cluster;
   TChain *fChainL2Electron;
   TChain *fChainL2Photon;
   TChain *fChainL2Track;
   TChain *fChainEFCluster;
   TChain *fChainEFegamma;
   TChain *fChainEFTrack;
   TChain *fChainOFFCluster;
   TChain *fChainOFFegamma;
   TChain *fChainOFFTrack;
   TChain *fChainMetadata;

   Long64_t nEntry;
   
   Int_t fCurrentInfo;
   Int_t fCurrentCluster;
   Int_t fCurrentElectron;
   Int_t fCurrentPhoton;
 
   // Declaration of leaf types
   
   // Event Info Leaf
   UInt_t          Event_run_number;
   UInt_t          Event_evt_number;
   UInt_t          Event_time_stamp;
   UInt_t          Event_time_stamp_ns_offset;
   UInt_t          Event_lumiBlock;
   UInt_t          Event_bc_id;
   UInt_t          Event_det_mask0;
   UInt_t          Event_det_mask1;
   Double_t        Event_deltaT_Calo;
   Double_t        Event_deltaT_MBTS;
   Bool_t          Event_passed_MBTS;
   Bool_t          Event_Trigger_present;
   UInt_t          Event_Trigger_status_element;
   UInt_t          Event_Trigger_extended_lvl1_id;
   UInt_t          Event_Trigger_lvl1_trig_type;
   UInt_t          Event_Trigger_nlvl1_trig_info;
   vector<unsigned int> *Event_Trigger_lvl1_trig_info;
   UInt_t          Event_Trigger_nlvl2_trig_info;
   vector<unsigned int> *Event_Trigger_lvl2_trig_info;
   UInt_t          Event_Trigger_nevt_filter_info;
   vector<unsigned int> *Event_Trigger_evt_filter_info;
   Double_t        MET_et;
   Double_t        MET_phi;
   
   // Trigger Event info Leaf
   vector<bool> *Trigger_L1passed;
   vector<bool> *Trigger_L2passed;
   vector<bool> *Trigger_EFpassed;
   vector<bool> *Trigger_L1passed_PT;
   vector<bool> *Trigger_L2passed_PT;
   vector<bool> *Trigger_EFpassed_PT;
   vector<int>  *Trigger_L1prescale;
   vector<int>  *Trigger_L2prescale;
   vector<int>  *Trigger_EFprescale;

   // chain Name in metadata
   vector<string> *Trigger_L1ChainName;
   vector<string> *Trigger_L2ChainName;
   vector<string> *Trigger_EFChainName;

   //Truth Leaf
   Int_t           truth_npart;
   vector<float>   *truth_px;
   vector<float>   *truth_py;
   vector<float>   *truth_pz;
   vector<float>   *truth_e;
   vector<float>   *truth_phi;
   vector<float>   *truth_eta;
   vector<float>   *truth_pt;
   vector<long>    *truth_status;
   vector<long>    *truth_PDGId;
   vector<long>    *truth_MotherPDGId;
   vector<long>    *truth_barcode;
   vector<float>   *truth_charge;
   vector<long>    *truth_prod_vtx;
   vector<long>    *truth_end_vtx;

   //L1 cluster
   UInt_t          L1ROI_nClus;
   vector<float>   *L1ROI_eta;
   vector<float>   *L1ROI_phi;
   vector<float>   *L1ROI_Core;
   vector<float>   *L1ROI_EMet;
   vector<float>   *L1ROI_EMiso;
   vector<float>   *L1ROI_Hadiso;
   vector<float>   *L1ROI_Hadcore;
   vector<unsigned int> *L1ROI_ROIword;
   vector<vector<string> > *L1ROI_trigChain;
   vector<vector<int> > *L1ROI_trigDec;
   vector<map<string,bool> > L1ROI_trigRes;

   // TrigEmCluster Leaf
   UInt_t          TrigEMCluster_nClus;
   std::vector<float>   *TrigEMCluster_energy;
   vector<string>  *TrigEMCluster_coll;
   vector<float>   *TrigEMCluster_et;
   vector<vector<double> > *TrigEMCluster_energyInSample;
   vector<float>   *TrigEMCluster_eta;
   vector<float>   *TrigEMCluster_phi;
   vector<float>   *TrigEMCluster_e237;
   vector<float>   *TrigEMCluster_e277;
   vector<float>   *TrigEMCluster_fracs1;
   vector<float>   *TrigEMCluster_weta2;
   vector<float>   *TrigEMCluster_ehad1;
   vector<float>   *TrigEMCluster_Eta1;
   vector<float>   *TrigEMCluster_emaxs1;
   vector<float>   *TrigEMCluster_e2tsts1;
   vector<unsigned int> *TrigEMCluster_quality;
   vector<vector<string> > *TrigEMCluster_trigChain;
   vector<vector<int> > *TrigEMCluster_trigDec;
   vector<map<string,bool> > TrigEMCluster_trigRes;

   // TrigElectron Leaf
   UInt_t          TrigElectron_nTrigElectron;
   vector<int>     *TrigElectron_roiId;
   vector<int>     *TrigElectron_roiWord;
   vector<bool>    *TrigElectron_isValid;
   vector<int>     *TrigElectron_charge;
   vector<int>     *TrigElectron_trackAlgo;
   vector<float>   *TrigElectron_Zvtx;
   vector<float>   *TrigElectron_err_Zvtx;
   vector<float>   *TrigElectron_Pt_track;
   vector<float>   *TrigElectron_err_Pt;
   vector<float>   *TrigElectron_trkEtaAtCalo;
   vector<float>   *TrigElectron_err_Eta;
   vector<float>   *TrigElectron_trkPhiAtCalo;
   vector<float>   *TrigElectron_err_Phi;
   vector<int>     *TrigElectron_TrackIndex;
   vector<float>   *TrigElectron_EtOverPt;
   vector<float>   *TrigElectron_trkClusDeta;
   vector<float>   *TrigElectron_trkClusDphi;
   vector<int>     *TrigElectron_ClusIndex;
   vector<float>   *TrigElectron_caloEta;
   vector<float>   *TrigElectron_caloPhi;
   vector<float>   *TrigElectron_Rcore;
   vector<float>   *TrigElectron_Eratio;
   vector<float>   *TrigElectron_EThad;
   vector<float>   *TrigElectron_E;
   vector<float>   *TrigElectron_Pt;
   vector<float>   *TrigElectron_Phi;
   vector<float>   *TrigElectron_Eta;
   vector<vector<string> >  *TrigElectron_trigChain;
   vector<vector<int> >  *TrigElectron_trigDec;
   vector<map<string,bool> > TrigElectron_trigRes;

   // TrigPhoton Leaf
   UInt_t          TrigPhoton_nTrigPhoton;
   vector<int>     *TrigPhoton_roiID;
   vector<bool>    *TrigPhoton_isValid;
   vector<float>   *TrigPhoton_Et;
   vector<float>   *TrigPhoton_HadEt;
   vector<float>   *TrigPhoton_energyRatio;
   vector<float>   *TrigPhoton_rCore;
   vector<float>   *TrigPhoton_dPhi;
   vector<float>   *TrigPhoton_dEta;
   vector<int>     *TrigPhoton_ClusIndex;
   vector<float>   *TrigPhoton_E;
   vector<float>   *TrigPhoton_Phi;
   vector<float>   *TrigPhoton_Eta;
   vector<vector<string> >  *TrigPhoton_trigChain;
   vector<vector<int> >  *TrigPhoton_trigDec;
   vector<map<string,bool> > TrigPhoton_trigRes;

   // TrigInDetTrack Leaf
   UInt_t          TrigInDetTrack_nTrack;
   vector<int>     *TrigInDetTrack_AlgoId;
   vector<float>   *TrigInDetTrack_chi2;
   vector<string>  *TrigInDetTrack_slice;
   vector<int>     *TrigInDetTrack_NStrawHits;
   vector<int>     *TrigInDetTrack_NStraw;
   vector<int>     *TrigInDetTrack_NStrawTime;
   vector<int>     *TrigInDetTrack_NTRHits;
   vector<int>     *TrigInDetTrack_NSiSpacePoints;
   vector<int>     *TrigInDetTrack_BL_hits;
   vector<int>     *TrigInDetTrack_Pixel_hits;
   vector<int>     *TrigInDetTrack_SCT_hits;
   vector<float>   *TrigInDetTrack_a0;
   vector<float>   *TrigInDetTrack_z0;
   vector<float>   *TrigInDetTrack_phi0;
   vector<float>   *TrigInDetTrack_eta;
   vector<float>   *TrigInDetTrack_pT;
   vector<float>   *TrigInDetTrack_ea0;
   vector<float>   *TrigInDetTrack_ez0;
   vector<float>   *TrigInDetTrack_ephi0;
   vector<float>   *TrigInDetTrack_eeta;
   vector<float>   *TrigInDetTrack_epT;
   vector<float>   *TrigInDetTrack_end_a0;
   vector<float>   *TrigInDetTrack_end_z0;
   vector<float>   *TrigInDetTrack_end_phi0;
   vector<float>   *TrigInDetTrack_end_eta;
   vector<float>   *TrigInDetTrack_end_pT;
   vector<float>   *TrigInDetTrack_end_ea0;
   vector<float>   *TrigInDetTrack_end_ez0;
   vector<float>   *TrigInDetTrack_end_ephi0;
   vector<float>   *TrigInDetTrack_end_eeta;
   vector<float>   *TrigInDetTrack_end_epT;
   vector<vector<string> >  *TrigInDetTrack_trigChain;
   vector<vector<int> >  *TrigInDetTrack_trigDec;
   vector<map<string,bool> > TrigInDetTrack_trigRes;

   // EFCaloCluster Leaf
   UInt_t          EFCaloCluster_nClus;
   vector<double>  *EFCaloCluster_energy;
   vector<double>  *EFCaloCluster_eta;
   vector<double>  *EFCaloCluster_phi;
   vector<double>  *EFCaloCluster_m;
   vector<double>  *EFCaloCluster_pt;
   vector<string>  *EFCaloCluster_coll;
   vector<int>     *EFCaloCluster_nSamples;
   vector<vector<double> > *EFCaloCluster_EInSample;
   vector<vector<double> > *EFCaloCluster_EtaInSample;
   vector<vector<double> > *EFCaloCluster_PhiInSample;
   vector<double>  *EFCaloCluster_BasicEnergy;
   vector<double>  *EFCaloCluster_Time;
   vector<int>     *EFCaloCluster_ClusterSize;
   vector<int>     *EFCaloCluster_EtaSize;
   vector<int>     *EFCaloCluster_PhiSize;
   vector<double>  *EFCaloCluster_eta0;
   vector<double>  *EFCaloCluster_phi0;
   vector<vector<double> > *EFCaloCluster_EMax;
   vector<vector<double> > *EFCaloCluster_EtaMax;
   vector<vector<double> > *EFCaloCluster_PhiMax;
   vector<vector<double> > *EFCaloCluster_EBe;
   vector<vector<double> > *EFCaloCluster_EtaBe;
   vector<vector<double> > *EFCaloCluster_PhiBe;
   vector<vector<string> > *EFCaloCluster_trigChain;
   vector<vector<int> > *EFCaloCluster_trigDec;
   vector<map<string,bool> > EFCaloCluster_trigRes;

   // EFtrack particle Leaf
   UInt_t          EFTrackParticle_nTrack;
   vector<string>  *EFTrackParticle_slice;
   vector<double>  *EFTrackParticle_pt;
   vector<double>  *EFTrackParticle_phi;
   vector<double>  *EFTrackParticle_eta;
   vector<double>  *EFTrackParticle_charge;
   vector<double>  *EFTrackParticle_chi2;
   vector<int>     *EFTrackParticle_BL_hits;
   vector<int>     *EFTrackParticle_Pixel_hits;
   vector<int>     *EFTrackParticle_SCT_hits;
   vector<int>     *EFTrackParticle_TRT_hits;
   vector<int>     *EFTrackParticle_TRT_out;
   vector<int>     *EFTrackParticle_TRT_tubeHits;
   vector<int>     *EFTrackParticle_TRT_highHits;
   vector<int>     *EFTrackParticle_TRT_highOut;
   vector<float>   *EFTrackParticle_eProb;
   vector<float>   *EFTrackParticle_a0;
   vector<float>   *EFTrackParticle_z0;
   vector<float>   *EFTrackParticle_phi0;
   vector<float>   *EFTrackParticle_eOVERt;
   vector<vector<string> > *EFTrackParticle_trigChain;
   vector<vector<int> > *EFTrackParticle_trigDec;
   vector<map<string,bool> > EFTrackParticle_trigRes;
   
   // EFegamma particle Leaf
   UInt_t          EFegamma_nEGamma;
   vector<double>  *EFegamma_e;
   vector<double>  *EFegamma_et;
   vector<double>  *EFegamma_pt;
   vector<double>  *EFegamma_phi;
   vector<double>  *EFegamma_eta;
   vector<double>  *EFegamma_m;
   vector<double>  *EFegamma_PID;
   vector<unsigned int> *EFegamma_author;
   vector<int>     *EFegamma_isem;
   vector<int>     *EFegamma_isemse;
   vector<int>     *EFegamma_TrackIndex;
   vector<int>     *EFegamma_ClusIndex;
   vector<int>     *EFegamma_charge;
   vector<double>  *EFegamma_etaBE2;
   vector<double>  *EFegamma_Eclu;
   vector<double>  *EFegamma_e233;
   vector<double>  *EFegamma_e237;
   vector<double>  *EFegamma_e277;
   vector<double>  *EFegamma_ethad;
   vector<double>  *EFegamma_ethad1;
   vector<double>  *EFegamma_weta1;
   vector<double>  *EFegamma_weta2;
   vector<double>  *EFegamma_f1;
   vector<double>  *EFegamma_e2tsts1;
   vector<double>  *EFegamma_emaxs1;
   vector<double>  *EFegamma_emins1;
   vector<double>  *EFegamma_wtots1;
   vector<double>  *EFegamma_fracs1;
   vector<double>  *EFegamma_etcone20;
   vector<double>  *EFegamma_dEta;
   vector<double>  *EFegamma_dPhi;
   vector<double>  *EFegamma_eOVERp;
   vector<int>     *EFegamma_nBL;
   vector<int>     *EFegamma_nPix;
   vector<int>     *EFegamma_nSCT;
   vector<int>     *EFegamma_nTRThigh;
   vector<int>     *EFegamma_nTRThighOut;
   vector<int>     *EFegamma_nTRT;
   vector<int>     *EFegamma_nTRTOut;
   vector<double>  *EFegamma_trkPt;
   vector<double>  *EFegamma_trkCosTh;
   vector<double>  *EFegamma_trkSinTh;
   vector<double>  *EFegamma_trkD0;
   vector<bool>    *EFegamma_isElectron;
   vector<bool>    *EFegamma_isPhoton;
   vector<vector<string> > *EFegamma_trigChain;
   vector<vector<int> > *EFegamma_trigDec;
   vector<map<string,bool> > EFegamma_trigRes;
   
   // OFFCaloCluster Leaf
   UInt_t          OFFCaloCluster_nClus;
   vector<double>  *OFFCaloCluster_energy;
   vector<double>  *OFFCaloCluster_eta;
   vector<double>  *OFFCaloCluster_phi;
   vector<double>  *OFFCaloCluster_m;
   vector<double>  *OFFCaloCluster_pt;
   vector<string>  *OFFCaloCluster_coll;
   vector<int>     *OFFCaloCluster_nSamples;
   vector<vector<double> > *OFFCaloCluster_EInSample;
   vector<vector<double> > *OFFCaloCluster_EtaInSample;
   vector<vector<double> > *OFFCaloCluster_PhiInSample;
   vector<vector<double> > *OFFCaloCluster_EInSampleRaw;
   vector<vector<double> > *OFFCaloCluster_EtaInSampleRaw;
   vector<vector<double> > *OFFCaloCluster_PhiInSampleRaw;
   vector<double>  *OFFCaloCluster_BasicEnergy;
   vector<double>  *OFFCaloCluster_Time;
   vector<int>     *OFFCaloCluster_ClusterSize;
   vector<int>     *OFFCaloCluster_EtaSize;
   vector<int>     *OFFCaloCluster_PhiSize;
   vector<double>     *OFFCaloCluster_nCell;  
   vector<double>  *OFFCaloCluster_eta0;
   vector<double>  *OFFCaloCluster_phi0;
   vector<double>  *OFFCaloCluster_eRaw;
   vector<double>  *OFFCaloCluster_etaRaw;
   vector<double>  *OFFCaloCluster_phiRaw;
   vector<vector<double> > *OFFCaloCluster_EMax;
   vector<vector<double> > *OFFCaloCluster_EtaMax;
   vector<vector<double> > *OFFCaloCluster_PhiMax;
   vector<vector<double> > *OFFCaloCluster_EBe;
   vector<vector<double> > *OFFCaloCluster_EtaBe;
   vector<vector<double> > *OFFCaloCluster_PhiBe;
   vector<vector<string> > *OFFCaloCluster_trigChain;
   vector<vector<int> > *OFFCaloCluster_trigDec;

   // OFFtrack particle Leaf
   UInt_t          OFFTrackParticle_nTrack;
   vector<string>  *OFFTrackParticle_slice;
   vector<double>  *OFFTrackParticle_pt;
   vector<double>  *OFFTrackParticle_phi;
   vector<double>  *OFFTrackParticle_eta;
   vector<double>  *OFFTrackParticle_charge;
   vector<double>  *OFFTrackParticle_chi2;
   vector<int>     *OFFTrackParticle_BL_hits;
   vector<int>     *OFFTrackParticle_Pixel_hits;
   vector<int>     *OFFTrackParticle_SCT_hits;
   vector<int>     *OFFTrackParticle_TRT_hits;
   vector<int>     *OFFTrackParticle_TRT_out;
   vector<int>     *OFFTrackParticle_TRT_tubeHits;
   vector<int>     *OFFTrackParticle_TRT_highHits;
   vector<int>     *OFFTrackParticle_TRT_highOut;
   vector<float>   *OFFTrackParticle_eProb;
   vector<float>   *OFFTrackParticle_a0;
   vector<float>   *OFFTrackParticle_z0;
   vector<float>   *OFFTrackParticle_phi0;
   vector<float>   *OFFTrackParticle_eOVERt;
   vector<vector<string> > *OFFTrackParticle_trigChain;
   vector<vector<int> > *OFFTrackParticle_trigDec;
   
   // OFFegamma particle Leaf
   UInt_t          OFFegamma_nEGamma;
   vector<double>  *OFFegamma_e;
   vector<double>  *OFFegamma_et;
   vector<double>  *OFFegamma_pt;
   vector<double>  *OFFegamma_phi;
   vector<double>  *OFFegamma_eta;
   vector<double>  *OFFegamma_m;
   vector<double>  *OFFegamma_PID;
   vector<unsigned int> *OFFegamma_author;
   vector<int>     *OFFegamma_isem;
   vector<int>     *OFFegamma_isemse;
   vector<bool>    *OFFegamma_isLoose;
   vector<bool>    *OFFegamma_isMedium;
   vector<bool>    *OFFegamma_isTight;
   vector<int>     *OFFegamma_TrackIndex;
   vector<int>     *OFFegamma_ClusIndex;
   vector<int>     *OFFegamma_charge;
   vector<double>  *OFFegamma_etaBE2;
   vector<double>  *OFFegamma_Eclu;
   vector<double>  *OFFegamma_e233;
   vector<double>  *OFFegamma_e237;
   vector<double>  *OFFegamma_e277;
   vector<double>  *OFFegamma_ethad;
   vector<double>  *OFFegamma_ethad1;
   vector<double>  *OFFegamma_weta1;
   vector<double>  *OFFegamma_weta2;
   vector<double>  *OFFegamma_f1;
   vector<double>  *OFFegamma_e2tsts1;
   vector<double>  *OFFegamma_emaxs1;
   vector<double>  *OFFegamma_emins1;
   vector<double>  *OFFegamma_wtots1;
   vector<double>  *OFFegamma_fracs1;
   vector<double>  *OFFegamma_etcone20;
   vector<double>  *OFFegamma_dEta;
   vector<double>  *OFFegamma_dPhi;
   vector<double>  *OFFegamma_eOVERp;
   vector<int>     *OFFegamma_nBL;
   vector<int>     *OFFegamma_nPix;
   vector<int>     *OFFegamma_nSCT;
   vector<int>     *OFFegamma_nTRThigh;
   vector<int>     *OFFegamma_nTRThighOut;
   vector<int>     *OFFegamma_nTRT;
   vector<int>     *OFFegamma_nTRTOut;
   vector<double>  *OFFegamma_trkPt;
   vector<double>  *OFFegamma_trkCosTh;
   vector<double>  *OFFegamma_trkSinTh;
   vector<double>  *OFFegamma_trkD0;
   vector<string>  *OFFegamma_MCtype;
   vector<string>  *OFFegamma_MCorig;
   vector<string>  *OFFegamma_MCorigMother;
   vector<bool>    *OFFegamma_isElectron;
   vector<bool>    *OFFegamma_isPhoton;
   vector<vector<string> > *OFFegamma_trigChain;
   vector<vector<int> > *OFFegamma_trigDec;

   /////////////////////////////////////////////////////////////////////////////////////////
   ////////////////////////////////////////////////////////////////////////////////////////

   // Event Info Branches
   TBranch        *b_Event_run_number;   //!
   TBranch        *b_Event_evt_number;   //!
   TBranch        *b_Event_time_stamp;   //!
   TBranch        *b_Event_time_stamp_ns_off;   //!
   TBranch        *b_Event_lumiBlock;   //!
   TBranch        *b_Event_bc_id;   //!
   TBranch        *b_Event_det_mask0;   //!
   TBranch        *b_Event_det_mask1;   //!
   TBranch        *b_Event_deltaT_Calo;   //!
   TBranch        *b_Event_deltaT_MBTS;   //!
   TBranch        *b_Event_passed_MBTS;   //!
   TBranch        *b_Event_Trigger_present;   //!
   TBranch        *b_Event_Trigger_status_element;   //!
   TBranch        *b_Event_Trigger_extended_lvl1_id;   //!
   TBranch        *b_Event_Trigger_lvl1_trig_type;   //!
   TBranch        *b_Event_Trigger_nlvl1_trig_info;   //!
   TBranch        *b_Event_Trigger_lvl1_trig_info;   //!
   TBranch        *b_Event_Trigger_nlvl2_trig_info;   //!
   TBranch        *b_Event_Trigger_lvl2_trig_info;   //!
   TBranch        *b_Event_Trigger_nevt_filter_info;   //!
   TBranch        *b_Event_Trigger_evt_filter_info;   //!
   TBranch        *b_MET_et;
   TBranch        *b_MET_phi;
   
   // Trigger Event info Branches
   TBranch        *b_Trigger_L1passed;   //!
   TBranch        *b_Trigger_L2passed;   //!
   TBranch        *b_Trigger_EFpassed;   //!  
   TBranch        *b_Trigger_L1passed_PT;   //!
   TBranch        *b_Trigger_L2passed_PT;   //!
   TBranch        *b_Trigger_EFpassed_PT;   //!  
   TBranch        *b_Trigger_L1prescale;   //!
   TBranch        *b_Trigger_L2prescale;   //!
   TBranch        *b_Trigger_EFprescale;   //!  
   
   // Trigger Event info in Metadata
   TBranch        *b_Trigger_L1ChainName;   //!
   TBranch        *b_Trigger_L2ChainName;   //!
   TBranch        *b_Trigger_EFChainName;   //!  

   // Truth leaf
   TBranch        *b_truth_npart;   //!
   TBranch        *b_truth_px;   //!
   TBranch        *b_truth_py;   //!
   TBranch        *b_truth_pz;   //!
   TBranch        *b_truth_e;   //!
   TBranch        *b_truth_phi;   //!
   TBranch        *b_truth_eta;   //!
   TBranch        *b_truth_pt;   //!
   TBranch        *b_truth_status;   //!
   TBranch        *b_truth_PDGId;   //!
   TBranch        *b_truth_MotherPDGId;   //!
   TBranch        *b_truth_barcode;   //!
   TBranch        *b_truth_charge;   //!
   TBranch        *b_truth_prod_vtx;   //!
   TBranch        *b_truth_end_vtx;   //!

   // L1 cluster
   TBranch        *b_L1ROI_nClus;   //!
   TBranch        *b_L1ROI_eta;   //!
   TBranch        *b_L1ROI_phi;   //!
   TBranch        *b_L1ROI_Core;   //!
   TBranch        *b_L1ROI_EMet;   //!
   TBranch        *b_L1ROI_EMiso;   //!
   TBranch        *b_L1ROI_Hadiso;   //!
   TBranch        *b_L1ROI_Hadcore;   //!
   TBranch        *b_L1ROI_ROIword;   //!
   TBranch        *b_L1ROI_trigChain;   //!
   TBranch        *b_L1ROI_trigDec;   //!

   // TrigEmCluster Leaf
   TBranch        *b_TrigEMCluster_nClus;   //!
   TBranch        *b_TrigEMCluster_energy;   //!
   TBranch        *b_TrigEMCluster_coll;   //!
   TBranch        *b_TrigEMCluster_et;   //!
   TBranch        *b_TrigEMCluster_energyInSample;   //!
   TBranch        *b_TrigEMCluster_eta;   //!
   TBranch        *b_TrigEMCluster_phi;   //!
   TBranch        *b_TrigEMCluster_e237;   //!
   TBranch        *b_TrigEMCluster_e277;   //!
   TBranch        *b_TrigEMCluster_fracs1;   //!
   TBranch        *b_TrigEMCluster_weta2;   //!
   TBranch        *b_TrigEMCluster_ehad1;   //!
   TBranch        *b_TrigEMCluster_Eta1;   //!
   TBranch        *b_TrigEMCluster_emaxs1;   //!
   TBranch        *b_TrigEMCluster_e2tsts1;   //!
   TBranch        *b_TrigEMCluster_quality;   //!
   TBranch        *b_TrigEMCluster_trigChain;   //!
   TBranch        *b_TrigEMCluster_trigDec;   //!

   // TrigElectron Leaf
   TBranch        *b_TrigElectron_nTrigElectron;   //!
   TBranch        *b_TrigElectron_roiId;   //!
   TBranch        *b_TrigElectron_roiWord;   //!
   TBranch        *b_TrigElectron_isValid;   //!
   TBranch        *b_TrigElectron_charge;   //!
   TBranch        *b_TrigElectron_trackAlgo;   //!
   TBranch        *b_TrigElectron_Zvtx;   //!
   TBranch        *b_TrigElectron_err_Zvtx;   //!
   TBranch        *b_TrigElectron_Pt_track;   //!
   TBranch        *b_TrigElectron_err_Pt;   //!
   TBranch        *b_TrigElectron_trkEtaAtCalo;   //!
   TBranch        *b_TrigElectron_err_Eta;   //!
   TBranch        *b_TrigElectron_trkPhiAtCalo;   //!
   TBranch        *b_TrigElectron_err_Phi;   //!
   TBranch        *b_TrigElectron_TrackIndex;   //!
   TBranch        *b_TrigElectron_EtOverPt;   //!
   TBranch        *b_TrigElectron_trkClusDeta;   //!
   TBranch        *b_TrigElectron_trkClusDphi;   //!
   TBranch        *b_TrigElectron_ClusIndex;   //!
   TBranch        *b_TrigElectron_caloEta;   //!
   TBranch        *b_TrigElectron_caloPhi;   //!
   TBranch        *b_TrigElectron_Rcore;   //!
   TBranch        *b_TrigElectron_Eratio;   //!
   TBranch        *b_TrigElectron_EThad;   //!
   TBranch        *b_TrigElectron_E;   //!
   TBranch        *b_TrigElectron_Pt;   //!
   TBranch        *b_TrigElectron_Phi;   //!
   TBranch        *b_TrigElectron_Eta;   //!
   TBranch        *b_TrigElectron_trigChain;   //!
   TBranch        *b_TrigElectron_trigDec;   //!

   // TrigPhoton Leaf
   TBranch        *b_TrigPhoton_nTrigPhoton;   //!
   TBranch        *b_TrigPhoton_roiID;   //!
   TBranch        *b_TrigPhoton_isValid;   //!
   TBranch        *b_TrigPhoton_Et;   //!
   TBranch        *b_TrigPhoton_HadEt;   //!
   TBranch        *b_TrigPhoton_energyRatio;   //!
   TBranch        *b_TrigPhoton_rCore;   //!
   TBranch        *b_TrigPhoton_dPhi;   //!
   TBranch        *b_TrigPhoton_dEta;   //!
   TBranch        *b_TrigPhoton_ClusIndex;   //!
   TBranch        *b_TrigPhoton_E;   //!
   TBranch        *b_TrigPhoton_Phi;   //!
   TBranch        *b_TrigPhoton_Eta;   //!
   TBranch        *b_TrigPhoton_trigChain;   //!
   TBranch        *b_TrigPhoton_trigDec;   //!

   // TrigInDetTrack Leaf
   TBranch        *b_TrigInDetTrack_nTrack;   //!
   TBranch        *b_TrigInDetTrack_AlgoId;   //!
   TBranch        *b_TrigInDetTrack_chi2;   //!
   TBranch        *b_TrigInDetTrack_slice;   //!
   TBranch        *b_TrigInDetTrack_NStrawHits;   //!
   TBranch        *b_TrigInDetTrack_NStraw;   //!
   TBranch        *b_TrigInDetTrack_NStrawTime;   //!
   TBranch        *b_TrigInDetTrack_NTRHits;   //!
   TBranch        *b_TrigInDetTrack_NSiSpacePoints;   //!
   TBranch        *b_TrigInDetTrack_BL_hits;   //!
   TBranch        *b_TrigInDetTrack_Pixel_hits;   //!
   TBranch        *b_TrigInDetTrack_SCT_hits;   //!
   TBranch        *b_TrigInDetTrack_a0;   //!
   TBranch        *b_TrigInDetTrack_z0;   //!
   TBranch        *b_TrigInDetTrack_phi0;   //!
   TBranch        *b_TrigInDetTrack_eta;   //!
   TBranch        *b_TrigInDetTrack_pT;   //!
   TBranch        *b_TrigInDetTrack_ea0;   //!
   TBranch        *b_TrigInDetTrack_ez0;   //!
   TBranch        *b_TrigInDetTrack_ephi0;   //!
   TBranch        *b_TrigInDetTrack_eeta;   //!
   TBranch        *b_TrigInDetTrack_epT;   //!
   TBranch        *b_TrigInDetTrack_end_a0;   //!
   TBranch        *b_TrigInDetTrack_end_z0;   //!
   TBranch        *b_TrigInDetTrack_end_phi0;   //!
   TBranch        *b_TrigInDetTrack_end_eta;   //!
   TBranch        *b_TrigInDetTrack_end_pT;   //!
   TBranch        *b_TrigInDetTrack_end_ea0;   //!
   TBranch        *b_TrigInDetTrack_end_ez0;   //!
   TBranch        *b_TrigInDetTrack_end_ephi0;   //!
   TBranch        *b_TrigInDetTrack_end_eeta;   //!
   TBranch        *b_TrigInDetTrack_end_epT;   //!
   TBranch        *b_TrigInDetTrack_trigChain;   //!
   TBranch        *b_TrigInDetTrack_trigDec;   //!

   // EF caloCluster Leaf
   TBranch        *b_EFCaloCluster_nClus;   //!
   TBranch        *b_EFCaloCluster_energy;   //!
   TBranch        *b_EFCaloCluster_eta;   //!
   TBranch        *b_EFCaloCluster_phi;   //!
   TBranch        *b_EFCaloCluster_m;   //!
   TBranch        *b_EFCaloCluster_pt;   //!
   TBranch        *b_EFCaloCluster_coll;   //!
   TBranch        *b_EFCaloCluster_nSamples;   //!
   TBranch        *b_EFCaloCluster_EInSample;   //!
   TBranch        *b_EFCaloCluster_EtaInSample;   //!
   TBranch        *b_EFCaloCluster_PhiInSample;   //!
   TBranch        *b_EFCaloCluster_BasicEnergy;   //!
   TBranch        *b_EFCaloCluster_Time;   //!
   TBranch        *b_EFCaloCluster_ClusterSize;   //!
   TBranch        *b_EFCaloCluster_EtaSize;   //!
   TBranch        *b_EFCaloCluster_PhiSize;   //!
   TBranch        *b_EFCaloCluster_eta0;   //!
   TBranch        *b_EFCaloCluster_phi0;   //!
   TBranch        *b_EFCaloCluster_EMax;   //!
   TBranch        *b_EFCaloCluster_EtaMax;   //!
   TBranch        *b_EFCaloCluster_PhiMax;   //!
   TBranch        *b_EFCaloCluster_EBe;   //!
   TBranch        *b_EFCaloCluster_EtaBe;   //!
   TBranch        *b_EFCaloCluster_PhiBe;   //!
   TBranch        *b_EFCaloCluster_trigChain;   //!
   TBranch        *b_EFCaloCluster_trigDec;   //!

   // EF TrackParticle Leaf
   TBranch        *b_EFTrackParticle_nTrack;   //!
   TBranch        *b_EFTrackParticle_slice;   //!
   TBranch        *b_EFTrackParticle_pt;   //!
   TBranch        *b_EFTrackParticle_phi;   //!
   TBranch        *b_EFTrackParticle_eta;   //!
   TBranch        *b_EFTrackParticle_charge;   //!
   TBranch        *b_EFTrackParticle_chi2;   //!
   TBranch        *b_EFTrackParticle_BL_hits;   //!
   TBranch        *b_EFTrackParticle_Pixel_hits;   //!
   TBranch        *b_EFTrackParticle_SCT_hits;   //!
   TBranch        *b_EFTrackParticle_TRT_hits;   //!
   TBranch        *b_EFTrackParticle_TRT_out;   //!
   TBranch        *b_EFTrackParticle_TRT_tubeHits;   //!
   TBranch        *b_EFTrackParticle_TRT_highHits;   //!
   TBranch        *b_EFTrackParticle_TRT_highOut;   //!
   TBranch        *b_EFTrackParticle_eProb;   //!
   TBranch        *b_EFTrackParticle_a0;   //!
   TBranch        *b_EFTrackParticle_z0;   //!
   TBranch        *b_EFTrackParticle_phi0;   //!
   TBranch        *b_EFTrackParticle_eOVERt;   //!
   TBranch        *b_EFTrackParticle_trigChain;   //!
   TBranch        *b_EFTrackParticle_trigDec;   //!
   
   // EF egamma branches
   TBranch        *b_EFegamma_nEGamma;   //!
   TBranch        *b_EFegamma_e;   //!
   TBranch        *b_EFegamma_et;   //!
   TBranch        *b_EFegamma_pt;   //!
   TBranch        *b_EFegamma_phi;   //!
   TBranch        *b_EFegamma_eta;   //!
   TBranch        *b_EFegamma_m;   //!
   TBranch        *b_EFegamma_PID;   //!
   TBranch        *b_EFegamma_author;   //!
   TBranch        *b_EFegamma_isem;   //!
   TBranch        *b_EFegamma_isemse;   //!
   TBranch        *b_EFegamma_TrackIndex;   //!
   TBranch        *b_EFegamma_ClusIndex;   //!
   TBranch        *b_EFegamma_charge;   //!
   TBranch        *b_EFegamma_etaBE2;   //!
   TBranch        *b_EFegamma_Eclu;   //!
   TBranch        *b_EFegamma_e233;   //!
   TBranch        *b_EFegamma_e237;   //!
   TBranch        *b_EFegamma_e277;   //!
   TBranch        *b_EFegamma_ethad;   //!
   TBranch        *b_EFegamma_ethad1;   //!
   TBranch        *b_EFegamma_weta1;   //!
   TBranch        *b_EFegamma_weta2;   //!
   TBranch        *b_EFegamma_f1;   //!
   TBranch        *b_EFegamma_e2tsts1;   //!
   TBranch        *b_EFegamma_emaxs1;   //!
   TBranch        *b_EFegamma_emins1;   //!
   TBranch        *b_EFegamma_wtots1;   //!
   TBranch        *b_EFegamma_fracs1;   //!
   TBranch        *b_EFegamma_etcone20;   //!
   TBranch        *b_EFegamma_dEta;   //!
   TBranch        *b_EFegamma_dPhi;   //!
   TBranch        *b_EFegamma_eOVERp;   //!
   TBranch        *b_EFegamma_nBL;   //!
   TBranch        *b_EFegamma_nPix;   //!
   TBranch        *b_EFegamma_nSCT;   //!
   TBranch        *b_EFegamma_nTRThigh;   //!
   TBranch        *b_EFegamma_nTRThighOut;   //!
   TBranch        *b_EFegamma_nTRT;   //!
   TBranch        *b_EFegamma_nTRTOut;   //!
   TBranch        *b_EFegamma_trkPt;   //!
   TBranch        *b_EFegamma_trkCosTh;   //!
   TBranch        *b_EFegamma_trkSinTh;   //!
   TBranch        *b_EFegamma_trkD0;   //!
   TBranch        *b_EFegamma_isElectron;   //!
   TBranch        *b_EFegamma_isPhoton;   //!
   TBranch        *b_EFegamma_trigChain;   //!
   TBranch        *b_EFegamma_trigDec;   //!
   
     // OFF caloCluster Leaf
   TBranch        *b_OFFCaloCluster_nClus;   //!
   TBranch        *b_OFFCaloCluster_energy;   //!
   TBranch        *b_OFFCaloCluster_eta;   //!
   TBranch        *b_OFFCaloCluster_phi;   //!
   TBranch        *b_OFFCaloCluster_m;   //!
   TBranch        *b_OFFCaloCluster_pt;   //!
   TBranch        *b_OFFCaloCluster_coll;   //!
   TBranch        *b_OFFCaloCluster_nSamples;   //!
   TBranch        *b_OFFCaloCluster_EInSample;   //!
   TBranch        *b_OFFCaloCluster_EtaInSample;   //!
   TBranch        *b_OFFCaloCluster_PhiInSample;   //!
   TBranch        *b_OFFCaloCluster_EInSampleRaw;   //!
   TBranch        *b_OFFCaloCluster_EtaInSampleRaw;   //!
   TBranch        *b_OFFCaloCluster_PhiInSampleRaw;   //!
   TBranch        *b_OFFCaloCluster_BasicEnergy;   //!
   TBranch        *b_OFFCaloCluster_Time;   //!
   TBranch        *b_OFFCaloCluster_ClusterSize;   //!
   TBranch        *b_OFFCaloCluster_EtaSize;   //!
   TBranch        *b_OFFCaloCluster_PhiSize;   //!
   TBranch        *b_OFFCaloCluster_nCell;   //!
   TBranch        *b_OFFCaloCluster_eta0;   //!
   TBranch        *b_OFFCaloCluster_phi0;   //!
   TBranch        *b_OFFCaloCluster_etaRaw;   //!
   TBranch        *b_OFFCaloCluster_phiRaw;   //!
   TBranch        *b_OFFCaloCluster_eRaw;   //!
   TBranch        *b_OFFCaloCluster_EMax;   //!
   TBranch        *b_OFFCaloCluster_EtaMax;   //!
   TBranch        *b_OFFCaloCluster_PhiMax;   //!
   TBranch        *b_OFFCaloCluster_EBe;   //!
   TBranch        *b_OFFCaloCluster_EtaBe;   //!
   TBranch        *b_OFFCaloCluster_PhiBe;   //!
   TBranch        *b_OFFCaloCluster_trigChain;   //!
   TBranch        *b_OFFCaloCluster_trigDec;   //!

   // OFF TrackParticle Leaf
   TBranch        *b_OFFTrackParticle_nTrack;   //!
   TBranch        *b_OFFTrackParticle_slice;   //!
   TBranch        *b_OFFTrackParticle_pt;   //!
   TBranch        *b_OFFTrackParticle_phi;   //!
   TBranch        *b_OFFTrackParticle_eta;   //!
   TBranch        *b_OFFTrackParticle_charge;   //!
   TBranch        *b_OFFTrackParticle_chi2;   //!
   TBranch        *b_OFFTrackParticle_BL_hits;   //!
   TBranch        *b_OFFTrackParticle_Pixel_hits;   //!
   TBranch        *b_OFFTrackParticle_SCT_hits;   //!
   TBranch        *b_OFFTrackParticle_TRT_hits;   //!
   TBranch        *b_OFFTrackParticle_TRT_out;   //!
   TBranch        *b_OFFTrackParticle_TRT_tubeHits;   //!
   TBranch        *b_OFFTrackParticle_TRT_highHits;   //!
   TBranch        *b_OFFTrackParticle_TRT_highOut;   //!
   TBranch        *b_OFFTrackParticle_eProb;   //!
   TBranch        *b_OFFTrackParticle_a0;   //!
   TBranch        *b_OFFTrackParticle_z0;   //!
   TBranch        *b_OFFTrackParticle_phi0;   //!
   TBranch        *b_OFFTrackParticle_eOVERt;   //!
   TBranch        *b_OFFTrackParticle_trigChain;   //!
   TBranch        *b_OFFTrackParticle_trigDec;   //!
   
   // OFF egamma branches
   TBranch        *b_OFFegamma_nEGamma;   //!
   TBranch        *b_OFFegamma_e;   //!
   TBranch        *b_OFFegamma_et;   //!
   TBranch        *b_OFFegamma_pt;   //!
   TBranch        *b_OFFegamma_phi;   //!
   TBranch        *b_OFFegamma_eta;   //!
   TBranch        *b_OFFegamma_m;   //!
   TBranch        *b_OFFegamma_PID;   //!
   TBranch        *b_OFFegamma_author;   //!
   TBranch        *b_OFFegamma_isem;   //!
   TBranch        *b_OFFegamma_isemse;   //!
   TBranch        *b_OFFegamma_isLoose;   //!
   TBranch        *b_OFFegamma_isMedium;  //!
   TBranch        *b_OFFegamma_isTight;   //!
   TBranch        *b_OFFegamma_TrackIndex;   //!
   TBranch        *b_OFFegamma_ClusIndex;   //!
   TBranch        *b_OFFegamma_charge;   //!
   TBranch        *b_OFFegamma_etaBE2;   //!
   TBranch        *b_OFFegamma_Eclu;   //!
   TBranch        *b_OFFegamma_e233;   //!
   TBranch        *b_OFFegamma_e237;   //!
   TBranch        *b_OFFegamma_e277;   //!
   TBranch        *b_OFFegamma_ethad;   //!
   TBranch        *b_OFFegamma_ethad1;   //!
   TBranch        *b_OFFegamma_weta1;   //!
   TBranch        *b_OFFegamma_weta2;   //!
   TBranch        *b_OFFegamma_f1;   //!
   TBranch        *b_OFFegamma_e2tsts1;   //!
   TBranch        *b_OFFegamma_emaxs1;   //!
   TBranch        *b_OFFegamma_emins1;   //!
   TBranch        *b_OFFegamma_wtots1;   //!
   TBranch        *b_OFFegamma_fracs1;   //!
   TBranch        *b_OFFegamma_etcone20;   //!
   TBranch        *b_OFFegamma_dEta;   //!
   TBranch        *b_OFFegamma_dPhi;   //!
   TBranch        *b_OFFegamma_eOVERp;   //!
   TBranch        *b_OFFegamma_nBL;   //!
   TBranch        *b_OFFegamma_nPix;   //!
   TBranch        *b_OFFegamma_nSCT;   //!
   TBranch        *b_OFFegamma_nTRThigh;   //!
   TBranch        *b_OFFegamma_nTRThighOut;   //!
   TBranch        *b_OFFegamma_nTRT;   //!
   TBranch        *b_OFFegamma_nTRTOut;   //!
   TBranch        *b_OFFegamma_trkPt;   //!
   TBranch        *b_OFFegamma_trkCosTh;   //!
   TBranch        *b_OFFegamma_trkSinTh;   //!
   TBranch        *b_OFFegamma_trkD0;   //!
   TBranch        *b_OFFegamma_MCtype;   //!
   TBranch        *b_OFFegamma_MCorig;   //!
   TBranch        *b_OFFegamma_MCorigMother;   //!
   TBranch        *b_OFFegamma_isElectron;   //!
   TBranch        *b_OFFegamma_isPhoton;   //!
   TBranch        *b_OFFegamma_trigChain;   //!
   TBranch        *b_OFFegamma_trigDec;   //!
   
   std::string m_inputFirst;
   std::string m_outPutFile;

   TrigEgammaNtuple_v2(TFile *file, std::string outFile);
   virtual ~TrigEgammaNtuple_v2();

   virtual void     addFile(TFile *f);
   virtual void     setName(std::string name) { m_inputFirst=name;};
   virtual void     Init();
   
   virtual Int_t    GetEntries();
   virtual Long64_t LoadTree(Long64_t entry);

   virtual void     Loop();
   virtual Bool_t   CheckTrees();
   virtual void     SetnEntries(Long64_t en);
   virtual void     FillTriggerMap(vector<vector<string> > *names,  vector<vector<int> > *dec,vector<map<string,bool> >& omap); 
      
   virtual void     DumpTrigger(std::string level, bool verbose);
   virtual void     DumpL1(unsigned int i, bool verbose);
   virtual void     DumpL2Cluster(unsigned int i, bool verbose);
   virtual void     DumpL2Photon(unsigned int i, bool verbose);
   virtual void     DumpL2Track(unsigned int i, bool verbose);
   virtual void     DumpL2Electron(unsigned int i, bool verbose);
  
   virtual void     DumpCluster(unsigned int i, bool off, bool verbose);
   virtual void     DumpEgamma(unsigned int i,bool off, bool verbose);
   
   bool EventPassedTrig(string trig);
   bool EventPassedTrig_PT(string trig);
   int  GetPrescaled(string trig);
   bool ObjInTrigger(map<string,bool> list, std::string trig);
   bool ObjPassedTrigger(map<string,bool> list, std::string trig);
   
   string     thisTriggerL1;
   string     thisTriggerL2;
   string     thisTriggerEF;
   int thisIndexL1;
   int thisIndexL2;
   int thisIndexEF;
};
#endif

#ifdef TrigEgammaNtuple_v2_cxx
TrigEgammaNtuple_v2::TrigEgammaNtuple_v2(TFile *file, std::string outFile)
{
  thisTriggerL1="NONE";
  thisTriggerL2="NONE";
  thisTriggerEF="NONE";
  thisIndexL1=-1;
  thisIndexL2=-1;
  thisIndexEF=-1;

  m_outPutFile=outFile;
  if (file ==0) {
    TFile *file = (TFile*)gROOT->GetListOfFiles()->FindObject("TrigEgamma.root");
    if (!file) {
      file = new TFile("TrigEgamma_all.root");
      file->cd("TrigEgamma.root:/EGamma");
    } else {
      std::cout << std::endl << "ERROR, no imput file provided and reference file: TrigEgamma.root is missing" << std::endl << std::endl;
    }
  } else {
    if (!file->cd("EGamma")) {
      std::cout << "ERROR: The file does not contain the main folder EGamma" << std::endl;
      exit(-1);
    }
  }
  nEntry=-1;
  std::string folderName=file->GetName();

  //to disable some information and speed up running ..
  bool useInfo      =true;
  bool useTrigger   =true;
  bool useL1        =true;
  bool useL2Cluster =true;
  bool useL2Electron=true;
  bool useL2Photon  =true;
  bool useL2Track   =true; 
  bool useEFCluster =true;
  bool useEFegamma  =true;
  bool useEFTrack   =true;
  bool useOFFCluster=true;
  bool useOFFegamma =true;
  bool useOFFTrack  =true;
  bool useTruth     =true;

  fChainInfo= new TChain("EGamma/EventInfo");
  TTree* fInfo =0;
  fInfo = (TTree*)gDirectory->Get("EventInfo");
  if (!fInfo || !useInfo) {
    hasInfo=false;
    std::cout << "Event informations are not present in the file" << std::endl;
  } else {
    fChainInfo->Add(folderName.c_str());
    hasInfo=true;
  }

  fChainTruth= new TChain("EGamma/MC_Truth");
  TTree* fTruth =0;
  fTruth = (TTree*)gDirectory->Get("MC_Truth");
  if (!fTruth || !useTruth) {
    hasTruth=false;
    std::cout << "Truth informations are not present in the file" << std::endl;
  } else {
    fChainTruth->Add(folderName.c_str());
    hasTruth=true;
  }

  fChainTrigger= new TChain("EGamma/TriggerInfo");
  TTree* fTrigger =0;
  fTrigger = (TTree*)gDirectory->Get("TriggerInfo");
  if (!fTrigger || !useTrigger) {
    hasTrigger=false;
    std::cout << "Trigger Event informations are not present in the file" << std::endl;
  } else {
    fChainTrigger->Add(folderName.c_str());
    hasTrigger=true;
  }

  fChainMetadata= new TChain("EGamma/Metadata");
  TTree* fTriggerM =0;
  fTriggerM = (TTree*)gDirectory->Get("Metadata");
  if (!fTriggerM || !useTrigger) {
    hasTrigger=false;
    cout << "Metadata informations are not present in the file" << endl;
  } else {
    fChainMetadata->Add(folderName.c_str());
  }

  fChainL1= new TChain("EGamma/L1_Cluster");
  TTree* fL1 =0;
  fL1 = (TTree*)gDirectory->Get("L1_Cluster");
  if (!fL1 || !useL1) {
    hasL1=false;
    std::cout << "L1 cluster informations are not present in the file" << std::endl;
  } else {
    fChainL1->Add(folderName.c_str());
    hasL1=true;
  }

  fChainL2Cluster= new TChain("EGamma/L2_Cluster");
  TTree* fCluster =0;
  fCluster = (TTree*)gDirectory->Get("L2_Cluster");
  if (!fCluster || !useL2Cluster) {
    hasL2Cluster=false;
    std::cout << "TrigEmCluster informations are not present in the file" << std::endl;
  } else {
    fChainL2Cluster->Add(folderName.c_str());
    hasL2Cluster=true;
  }  

  fChainL2Electron = new TChain("EGamma/L2_Electron");
  TTree* fElectron =0;
  fElectron = (TTree*)gDirectory->Get("L2_Electron");
  if (!fElectron || !useL2Electron ) {
    hasL2Electron=false;
    std::cout << "Trig Electron information are not present in the file" << std::endl;
  } else {
    hasL2Electron=true;
    fChainL2Electron->Add(folderName.c_str());
  }  

  fChainL2Photon = new TChain("EGamma/L2_Photon");
  TTree* fPhoton =0;
  fPhoton = (TTree*)gDirectory->Get("L2_Photon");
  if (!fPhoton || !useL2Photon ) {
    hasL2Photon=false;
    std::cout << "Trig Photon information are not present in the file" << std::endl;
  } else {
    hasL2Photon=true;
    fChainL2Photon->Add(folderName.c_str());
  }
  
  fChainL2Track = new TChain("EGamma/L2_Track");
  TTree* fTrack =0;
  fTrack = (TTree*)gDirectory->Get("L2_Track");
  if (!fTrack || !useL2Track ) {
    hasL2Track=false;
    std::cout << "Trig Track information are not present in the file" << std::endl;
  } else {
    hasL2Track=true;
    fChainL2Track->Add(folderName.c_str());
  }
  
  fChainEFCluster= new TChain("EGamma/EF_Cluster");
  TTree* fClusterEF =0;
  fClusterEF = (TTree*)gDirectory->Get("EF_Cluster");
  if (!fClusterEF || !useEFCluster ) {
    hasEFCluster=false;
    std::cout << "EFCaloCluster informations are not present in the file" << std::endl;
  } else {
    fChainEFCluster->Add(folderName.c_str());
    hasEFCluster=true;
  }  
  
  fChainEFTrack = new TChain("EGamma/EF_Track");
  TTree* fTrackEF =0;
  fTrackEF = (TTree*)gDirectory->Get("EF_Track");
  if (!fTrackEF || !useEFTrack) {
    hasEFTrack=false;
    std::cout << "EFTrackParticle information are not present in the file" << std::endl;
  } else {
    hasEFTrack=true;
    fChainEFTrack->Add(folderName.c_str());
  }
  
  fChainEFegamma = new TChain("EGamma/EF_egamma");
  TTree* fegammaEF =0;
  fegammaEF = (TTree*)gDirectory->Get("EF_egamma");
  if (!fegammaEF || !useEFegamma ) {
    hasEFegamma=false;
    std::cout << "EFegamma information are not present in the file" << std::endl;
  } else {
    hasEFegamma=true;
    fChainEFegamma->Add(folderName.c_str());
  }
  
  fChainOFFCluster= new TChain("EGamma/OFF_Cluster");
  TTree* fClusterOFF =0;
  fClusterOFF = (TTree*)gDirectory->Get("OFF_Cluster");
  if (!fClusterOFF || !useOFFCluster ) {
    hasOFFCluster=false;
    std::cout << "OFFCaloCluster informations are not present in the file" << std::endl;
  } else {
    fChainOFFCluster->Add(folderName.c_str());
    hasOFFCluster=true;
  }  
  
  fChainOFFTrack = new TChain("EGamma/OFF_Track");
  TTree* fTrackOFF =0;
  fTrackOFF = (TTree*)gDirectory->Get("OFF_Track");
  if (!fTrackOFF || !useOFFTrack ) {
    hasOFFTrack=false;
    std::cout << "OFFTrackParticle information are not present in the file" << std::endl;
  } else {
    hasOFFTrack=true;
    fChainOFFTrack->Add(folderName.c_str());
  }
  
  fChainOFFegamma = new TChain("EGamma/OFF_egamma");
  TTree* fegammaOFF =0;
  fegammaOFF = (TTree*)gDirectory->Get("OFF_egamma");
  if (!fegammaOFF || !useOFFegamma ) {
    hasOFFegamma=false;
    std::cout << "OFFegamma information are not present in the file" << std::endl;
  } else {
    hasOFFegamma=true;
    fChainOFFegamma->Add(folderName.c_str());
  }
}

void TrigEgammaNtuple_v2::SetnEntries(Long64_t en) 
{
  nEntry=en;
}

void TrigEgammaNtuple_v2::addFile(TFile *f)
{
  if (f!=0) {
    TDirectory* dir=0;
    dir=(TDirectory*)f->Get("EGamma");
    if (!dir) {
      std::cout << "The file does not contain tha main diractory 'EGamma' " << std::endl;
      exit(-1);
    }
    std::string folderName=f->GetName();
    if (hasInfo) {
      TTree* fInfo =0;
      fInfo = (TTree*)dir->Get("EventInfo");
      if (!fInfo) {
	std::cout << "Event informations are not present in this file but are present in the others" << std::endl;
	exit(-1);
      } else {
	fChainInfo->Add(folderName.c_str());
      }
    }
    
    if (hasTruth) {
      TTree* fTruth =0;
      fTruth = (TTree*)dir->Get("MC_Truth");
      if (!fTruth) {
	std::cout << "Event informations are not present in this file but are present in the others" << std::endl;
	exit(-1);
      } else {
	fChainTruth->Add(folderName.c_str());
      }
    }

    if (hasTrigger) {
      TTree* fTrigger =0;
      fTrigger = (TTree*)dir->Get("TriggerInfo");
      if (!fTrigger) {
	std::cout << "Trigger Event informations are not present in this file but are present in the others" << std::endl;
	exit(-1);
      } else {
	fChainTrigger->Add(folderName.c_str());
      }

      TTree* fTriggerM =0;
      fTriggerM = (TTree*)dir->Get("Metadata");
      if (!fTriggerM) {
	cout << "Metadata informations are not present in this file but are present in the others" << endl;
	exit(-1);
      } else {
	fChainMetadata->Add(folderName.c_str());
      }
    }

    if (hasL1) {
      TTree* fL1 =0;
      fL1 = (TTree*)dir->Get("L1_Cluster");
      if (!fL1) {
	std::cout << "L1 Cluster informations are not present in this file but are present in the others" << std::endl;
	exit(-1);
      } else {
	fChainL1->Add(folderName.c_str());
      }
    }

    if (hasL2Cluster) {
      TTree* fCluster =0;
      fCluster = (TTree*)dir->Get("L2_Cluster");
      if (!fCluster) {
	std::cout << "TrigEMCluster informations are not present in this file but are present in the others" << std::endl;
	exit(-1);
      } else {
	fChainL2Cluster->Add(folderName.c_str());
      }
    }
    
    if (hasL2Electron) {
      TTree* fElectron =0;
      fElectron = (TTree*)dir->Get("L2_Electron");
      if (!fElectron) {
	std::cout << "TrigElectorn information are not present in this file but are present in the others" << std::endl;
	exit(-1);
      } else {
	fChainL2Electron->Add(folderName.c_str());
      }
    }
    
    if (hasL2Photon) {
      TTree* fPhoton =0;
      fPhoton = (TTree*)dir->Get("L2_Photon");
      if (!fPhoton) {
	std::cout << "TrigPhoton information are not present in this file but are present in the others" << std::endl;
	exit(-1);
      } else {
	fChainL2Photon->Add(folderName.c_str());
      }
    }

    if (hasL2Track) {
      TTree* fTrack =0;
      fTrack = (TTree*)dir->Get("L2_Track");
      if (!fTrack) {
	std::cout << "TrigInDetTrackinformation are not present in this file but are present in the others" << std::endl;
	exit(-1);
      } else {
	fChainL2Track->Add(folderName.c_str());
      }
    }

    if (hasEFCluster) {
      TTree* fCluster =0;
      fCluster = (TTree*)dir->Get("EF_Cluster");
      if (!fCluster) {
	std::cout << "EFCaloCluster informations are not present in this file but are present in the others" << std::endl;
	exit(-1);
      } else {
	fChainEFCluster->Add(folderName.c_str());
      }
    }
    
    if (hasEFTrack) {
      TTree* fTrack =0;
      fTrack = (TTree*)dir->Get("EF_Track");
      if (!fTrack) {
	std::cout << "EFTrackParticle information are not present in this file but are present in the others" << std::endl;
	exit(-1);
      } else {
	fChainEFTrack->Add(folderName.c_str());
      }
    }
    
    if (hasEFegamma) {
      TTree* fegamma =0;
      fegamma = (TTree*)dir->Get("EF_egamma");
      if (!fegamma) {
	std::cout << "EFegamma information are not present in this file but are present in the others" << std::endl;
	exit(-1);
      } else {
	fChainEFegamma->Add(folderName.c_str());
      }
    }

    if (hasOFFCluster) {
      TTree* fCluster =0;
      fCluster = (TTree*)dir->Get("OFF_Cluster");
      if (!fCluster) {
	std::cout << "OFFCaloCluster informations are not present in this file but are present in the others" << std::endl;
	exit(-1);
      } else {
	fChainOFFCluster->Add(folderName.c_str());
      }
    }
    
    if (hasOFFTrack) {
      TTree* fTrack =0;
      fTrack = (TTree*)dir->Get("OFF_Track");
      if (!fTrack) {
	std::cout << "OFFTrackParticle information are not present in this file but are present in the others" << std::endl;
	exit(-1);
      } else {
	fChainOFFTrack->Add(folderName.c_str());
      }
    }
    
    if (hasOFFegamma) {
      TTree* fegamma =0;
      fegamma = (TTree*)dir->Get("OFF_egamma");
      if (!fegamma) {
	std::cout << "OFFegamma information are not present in this file but are present in the others" << std::endl;
	exit(-1);
      } else {
	fChainOFFegamma->Add(folderName.c_str());
      }
    }


    delete f;
  } else {
    std::cout << "File is Empty" << std::endl;
  }
}


TrigEgammaNtuple_v2::~TrigEgammaNtuple_v2()
{
  // ?????
}

Bool_t TrigEgammaNtuple_v2::CheckTrees() 
{
  if (fChainInfo || fChainTrigger || fChainL1 || fChainMetadata || fChainL2Cluster || 
      fChainL2Electron || fChainL2Photon || fChainL2Track || fChainEFCluster || fChainEFegamma ||
      fChainEFTrack || fChainOFFCluster || fChainOFFegamma || fChainOFFTrack) return  kTRUE;
  else return kFALSE;
}


Long64_t  TrigEgammaNtuple_v2::LoadTree(Long64_t entry)
{
  Long64_t centryInfo=-9999;
  Long64_t GentryInfo=-9999;
  if (hasInfo) {
    centryInfo=fChainInfo->LoadTree(entry);
    GentryInfo=fChainInfo->GetEntry(entry);
  }
  //  cout << "GentryInfo: " << GentryInfo << " | " << centryInfo << endl;

  Long64_t centryTruth=-9999;
  Long64_t GentryTruth=-9999;
  if (hasTruth) {
    centryTruth=fChainTruth->LoadTree(entry);
    GentryTruth=fChainTruth->GetEntry(entry);
  }
  //  cout << "GentryTruth: " << GentryTruth << " | " << centryTruth << endl;
  
  Long64_t centryTrigger=-9999;
  Long64_t GentryTrigger=-9999;
  if (hasTrigger) {
    centryTrigger=fChainInfo->LoadTree(entry);
    GentryTrigger=fChainTrigger->GetEntry(entry);
  }
  //  cout << "GentryTrigger: " << GentryTrigger << " | " << centryTrigger << endl;

  Long64_t centryL1=-9999;
  Long64_t GentryL1=-9999;
  if (hasL1) {
    centryL1=fChainL1->LoadTree(entry);
    GentryL1=fChainL1->GetEntry(entry);
    FillTriggerMap(L1ROI_trigChain,L1ROI_trigDec,L1ROI_trigRes);
  }
  //  cout << "GentryL1: " << GentryL1 << " | " << centryL1 << endl;

  Long64_t centryL2Cluster=-9999;
  Long64_t GentryL2Cluster=-9999;
  if (hasL2Cluster) {
    centryL2Cluster=fChainL2Cluster->LoadTree(entry);
    GentryL2Cluster=fChainL2Cluster->GetEntry(entry);
    FillTriggerMap(TrigEMCluster_trigChain,TrigEMCluster_trigDec,TrigEMCluster_trigRes);
  }  
  //  cout << "GentryL2Cluster: " << GentryL2Cluster << " | " << centryL2Cluster << endl;

  Long64_t centryL2Electron=-9999;
  Long64_t GentryL2Electron=-9999;
  if (hasL2Electron) {
    centryL2Electron=fChainL2Electron->LoadTree(entry);
    GentryL2Electron=fChainL2Electron->GetEntry(entry);
    if (!hasL2Cluster) {
      for (unsigned int i=0;i<TrigElectron_ClusIndex->size();i++) {
	(*TrigElectron_ClusIndex)[i]=-1;
      }
    }
    if (!hasL2Track) {
      for (unsigned int i=0;i<TrigElectron_TrackIndex->size();i++) {
	(*TrigElectron_TrackIndex)[i]=-1;
      }
    }
    FillTriggerMap(TrigElectron_trigChain,TrigElectron_trigDec,TrigElectron_trigRes);
  }
  //  cout << "GentryL2Electron: " << GentryL2Electron << " | " << centryL2Electron << endl;
  
  Long64_t centryL2Photon=-9999;
  Long64_t GentryL2Photon=-9999;
  if (hasL2Photon) {
    centryL2Photon=fChainL2Photon->LoadTree(entry);
    GentryL2Photon=fChainL2Photon->GetEntry(entry);
    if (!hasL2Cluster) {
      for (unsigned int i=0;i<TrigPhoton_ClusIndex->size();i++) {
	(*TrigPhoton_ClusIndex)[i]=-1;
      }
    }
    FillTriggerMap(TrigPhoton_trigChain,TrigPhoton_trigDec,TrigPhoton_trigRes);
  }
  //  cout << "GentryL2Photon: " << GentryL2Photon << " | " << centryL2Photon << endl;

  Long64_t centryL2Track=-9999;
  Long64_t GentryL2Track=-9999;
  if (hasL2Track) {
    centryL2Track=fChainL2Track->LoadTree(entry);
    GentryL2Track=fChainL2Track->GetEntry(entry);
    FillTriggerMap(TrigInDetTrack_trigChain,TrigInDetTrack_trigDec,TrigInDetTrack_trigRes);
  }
  //  cout << "GentryL2Track: " << GentryL2Track << " | " << centryL2Track << endl;

  Long64_t centryEFCluster=-9999;
  Long64_t GentryEFCluster=-9999;
  if (hasEFCluster) {
    centryEFCluster=fChainEFCluster->LoadTree(entry);
    GentryEFCluster=fChainEFCluster->GetEntry(entry);
    FillTriggerMap(EFCaloCluster_trigChain,EFCaloCluster_trigDec,EFCaloCluster_trigRes);
  } 
  //  cout << "GentryEFCluster: " << GentryEFCluster << " | " << centryEFCluster << endl;  

  Long64_t centryEFTrack=-9999;
  Long64_t GentryEFTrack=-9999;
  if (hasEFTrack) {
    centryEFTrack=fChainEFTrack->LoadTree(entry);
    GentryEFTrack=fChainEFTrack->GetEntry(entry);
    FillTriggerMap(EFTrackParticle_trigChain,EFTrackParticle_trigDec,EFTrackParticle_trigRes);
  }
  //  cout << "GentryEFTrack: " << GentryEFTrack << " | " << centryEFTrack << endl;  

  Long64_t centryEFegamma=-9999;
  Long64_t GentryEFegamma=-9999;
  if (hasEFegamma) {
    centryEFegamma=fChainEFegamma->LoadTree(entry);
    GentryEFegamma=fChainEFegamma->GetEntry(entry);
    if (!hasEFCluster) {
      for (unsigned int i=0;i<EFegamma_ClusIndex->size();i++) {
	(*EFegamma_ClusIndex)[i]=-1;
      }
    }
    if (!hasEFTrack) {
      for (unsigned int i=0;i<EFegamma_TrackIndex->size();i++) {
	(*EFegamma_TrackIndex)[i]=-1;
      }
    }
    FillTriggerMap(EFegamma_trigChain,EFegamma_trigDec,EFegamma_trigRes);
  }
  //  cout << "GentryEFegamma: " << GentryEFegamma << " | " << centryEFegamma << endl;  
  
  Long64_t centryOFFCluster=-9999;
  Long64_t GentryOFFCluster=-9999;
  if (hasOFFCluster) {
    centryOFFCluster=fChainOFFCluster->LoadTree(entry);
    GentryOFFCluster=fChainOFFCluster->GetEntry(entry);
  } 
  //  cout << "GentryOFFCluster: " << GentryOFFCluster << " | " << centryOFFCluster << endl;  

  Long64_t centryOFFTrack=-9999;
  Long64_t GentryOFFTrack=-9999;
  if (hasOFFTrack) {
    centryOFFTrack=fChainOFFTrack->LoadTree(entry);
    GentryOFFTrack=fChainOFFTrack->GetEntry(entry);
  }
  //  cout << "GentryOFFTrack: " << GentryOFFTrack << " | " << centryOFFTrack << endl;  

  Long64_t centryOFFegamma=-9999;
  Long64_t GentryOFFegamma=-9999;
  if (hasOFFegamma) {
    centryOFFegamma=fChainOFFegamma->LoadTree(entry);
    GentryOFFegamma=fChainOFFegamma->GetEntry(entry);
    if (!hasOFFCluster) {
      for (unsigned int i=0;i<OFFegamma_ClusIndex->size();i++) {
	(*OFFegamma_ClusIndex)[i]=-1;
      }
    }
    if (!hasOFFTrack) {
      for (unsigned int i=0;i<OFFegamma_TrackIndex->size();i++) {
	(*OFFegamma_TrackIndex)[i]=-1;
      }
    }
  }
  //  cout << "GentryOFFegamma: " << GentryOFFegamma << " | " << centryOFFegamma << endl;  
 
  
  Long64_t centry=centryInfo;
  if (centry<centryTrigger)   centry=centryTrigger;
  if (centry<centryL1)        centry=centryL1;
  if (centry<centryL2Cluster) centry=centryL2Cluster;
  if (centry<centryL2Electron)centry=centryL2Electron;
  if (centry<centryL2Photon)  centry=centryL2Photon;
  if (centry<centryL2Track)   centry=centryL2Track;
  if (centry<centryEFCluster) centry=centryEFCluster;
  if (centry<centryEFTrack)   centry=centryEFTrack;
  if (centry<centryEFegamma)  centry=centryEFegamma;
  if (centry<centryOFFCluster)centry=centryOFFCluster;
  if (centry<centryOFFTrack)  centry=centryOFFTrack;
  if (centry<centryOFFegamma) centry=centryOFFegamma;
  
  Long64_t Gentry=GentryInfo;
  if (Gentry<GentryTrigger)   Gentry=GentryTrigger;
  if (Gentry<GentryL1)        Gentry=GentryL1;
  if (Gentry<GentryL2Cluster) Gentry=GentryL2Cluster;
  if (Gentry<GentryL2Electron)Gentry=GentryL2Electron;
  if (Gentry<GentryL2Photon)  Gentry=GentryL2Photon;
  if (Gentry<GentryL2Track)   Gentry=GentryL2Track;
  if (Gentry<GentryEFCluster) Gentry=GentryEFCluster;
  if (Gentry<GentryEFTrack)   Gentry=GentryEFTrack;
  if (Gentry<GentryEFegamma)  Gentry=GentryEFegamma;
  if (Gentry<GentryOFFCluster)Gentry=GentryOFFCluster;
  if (Gentry<GentryOFFTrack)  Gentry=GentryOFFTrack;
  if (Gentry<GentryOFFegamma) Gentry=GentryOFFegamma;

//   cout << "Gentry: " << Gentry << endl;

  return centry;
}

Int_t TrigEgammaNtuple_v2::GetEntries()
{
  Int_t entryInfo=-10;
  if (hasInfo) {
    if (!fChainInfo) {
      std::cout << "ERROR: event information enabled but Tree is empty" << std::endl;
      return -1;
    } else entryInfo=fChainInfo->GetEntries();
  }
  
  Int_t entryTruth=-10;
  if (hasTruth) {
    if (!fChainTruth) {
      std::cout << "ERROR: event information enabled but Tree is empty" << std::endl;
      return -1;
    } else entryTruth=fChainTruth->GetEntries();
  }

  Int_t entryTrigger=-10;
  if (hasTrigger) {
    if (!fChainTrigger) {
      std::cout << "ERROR: event information enabled but Tree is empty" << std::endl;
      return -1;
    } else entryTrigger=fChainTrigger->GetEntries();
  }

  Int_t entryL1=-10;
  if (hasL1) {
    if (!fChainL1) {
      std::cout << "ERROR: L1 cluster information enabled but Tree is empty" << std::endl;
      return -1;
    } else entryL1=fChainL1->GetEntries();
  }
  
  Int_t entryL2Cluster=-10;
  if (hasL2Cluster) {
    if (!fChainL2Cluster) {
      std::cout << "ERROR: TrigEMCluster information enabled but Tree is empty" << std::endl;
      return -1;
    } else entryL2Cluster=fChainL2Cluster->GetEntries();
  }

  Int_t entryL2Electron=-10;
  if (hasL2Electron) {
    if (!fChainL2Electron) {
      std::cout << "ERROR: TrigElectron information enabled but Tree is empty" << std::endl;
      return -1;
    } else entryL2Electron=fChainL2Electron->GetEntries();
  }

  Int_t entryL2Photon=-10;
  if (hasL2Photon) {
    if (!fChainL2Photon) {
      std::cout << "ERROR: TrigPhoton information enabled but Tree is empty" << std::endl;
      return -1;
    } else entryL2Photon=fChainL2Photon->GetEntries();
  }
  
  Int_t entryL2Track=-10;
  if (hasL2Track) {
    if (!fChainL2Track) {
      std::cout << "ERROR: TrigTrack information enabled but Tree is empty" << std::endl;
      return -1;
    } else entryL2Track=fChainL2Track->GetEntries();    
  }
 
  Int_t entryEFCluster=-10;
  if (hasEFCluster) {
    if (!fChainEFCluster) {
      std::cout << "ERROR: EFCaloCluster information enabled but Tree is empty" << std::endl;
      return -1;
    } else entryEFCluster=fChainEFCluster->GetEntries();
  }
  
  Int_t entryEFTrack=-10;
  if (hasEFTrack) {
    if (!fChainEFTrack) {
      std::cout << "ERROR: EFTrackParticle information enabled but Tree is empty" << std::endl;
      return -1;
    } else entryEFTrack=fChainEFTrack->GetEntries();    
  }

  Int_t entryEFegamma=-10;
  if (hasEFegamma) {
    if (!fChainEFegamma) {
      std::cout << "ERROR: EFegamma information enabled but Tree is empty" << std::endl;
      return -1;
    } else entryEFegamma=fChainEFegamma->GetEntries();
  }
  
  Int_t entryOFFCluster=-10;
  if (hasOFFCluster) {
    if (!fChainOFFCluster) {
      std::cout << "ERROR: OFFCaloCluster information enabled but Tree is empty" << std::endl;
      return -1;
    } else entryOFFCluster=fChainOFFCluster->GetEntries();
  }
  
  Int_t entryOFFTrack=-10;
  if (hasOFFTrack) {
    if (!fChainOFFTrack) {
      std::cout << "ERROR: OFFTrackParticle information enabled but Tree is empty" << std::endl;
      return -1;
    } else entryOFFTrack=fChainOFFTrack->GetEntries();    
  }

  Int_t entryOFFegamma=-10;
  if (hasOFFegamma) {
    if (!fChainOFFegamma) {
      std::cout << "ERROR: OFFegamma information enabled but Tree is empty" << std::endl;
      return -1;
    } else entryOFFegamma=fChainOFFegamma->GetEntries();
  }
  Int_t entry=-100;
  if (entryInfo!=entry && entryInfo!=-10) entry=entryInfo;
  if (entryTrigger!=entry && entryTrigger!=-10) entry=entryTrigger;
  if (entryL1!=entry && entryL1!=-10) entry=entryL1;
  if (entryL2Cluster!=entry && entryL2Cluster!=-10) entry=entryL2Cluster;
  if (entryL2Track!=entry && entryL2Track!=-10) entry=entryL2Track;
  if (entryL2Photon!=entry && entryL2Photon!=-10) entry=entryL2Photon;
  if (entryL2Electron!=entry && entryL2Electron!=-10) entry=entryL2Electron;
  if (entryEFCluster!=entry && entryEFCluster!=-10) entry=entryEFCluster;
  if (entryEFTrack!=entry && entryEFTrack!=-10) entry=entryEFTrack;
  if (entryEFegamma!=entry && entryEFegamma!=-10) entry=entryEFegamma;
  if (entryOFFCluster!=entry && entryOFFCluster!=-10) entry=entryOFFCluster;
  if (entryOFFTrack!=entry && entryOFFTrack!=-10) entry=entryOFFTrack;
  if (entryOFFegamma!=entry && entryOFFegamma!=-10) entry=entryOFFegamma;

  return entry;
}


void TrigEgammaNtuple_v2::Init()
{ 
  // Event Info Leaf
  Event_Trigger_lvl1_trig_info = 0;
  Event_Trigger_lvl2_trig_info = 0;
  Event_Trigger_evt_filter_info = 0;
  
  //Trigger Info Leaf
  Trigger_L1passed = 0;
  Trigger_L2passed = 0;
  Trigger_EFpassed = 0;
  Trigger_L1passed_PT = 0;
  Trigger_L2passed_PT = 0;
  Trigger_EFpassed_PT = 0;
  Trigger_L1prescale = 0;
  Trigger_L2prescale = 0;
  Trigger_EFprescale = 0;  
  Trigger_L1ChainName = 0;
  Trigger_L2ChainName = 0;
  Trigger_EFChainName = 0;
  

  //Truth Leaf
  truth_px = 0;
  truth_py = 0;
  truth_pz = 0;
  truth_e = 0;
  truth_phi = 0;
  truth_eta = 0;
  truth_pt = 0;
  truth_status = 0;
  truth_PDGId = 0;
  truth_MotherPDGId = 0;
  truth_barcode = 0;
  truth_charge = 0;
  truth_prod_vtx = 0;
  truth_end_vtx = 0;
    
  // L1Cluster Leaf
  L1ROI_eta = 0;
  L1ROI_phi = 0;
  L1ROI_Core = 0;
  L1ROI_EMet = 0;
  L1ROI_EMiso = 0;
  L1ROI_Hadiso = 0;
  L1ROI_Hadcore = 0;
  L1ROI_ROIword = 0;
  L1ROI_trigChain = 0;
  L1ROI_trigDec = 0;
 
  // TrigEmCluster Leaf
  TrigEMCluster_energy = 0;
  TrigEMCluster_coll = 0;
  TrigEMCluster_et = 0;
  TrigEMCluster_energyInSample = 0;
  TrigEMCluster_eta = 0;
  TrigEMCluster_phi = 0;
  TrigEMCluster_e237 = 0;
  TrigEMCluster_e277 = 0;
  TrigEMCluster_fracs1 = 0;
  TrigEMCluster_weta2 = 0;
  TrigEMCluster_ehad1 = 0;
  TrigEMCluster_Eta1 = 0;
  TrigEMCluster_emaxs1 = 0;
  TrigEMCluster_e2tsts1 = 0;
  TrigEMCluster_quality =0;
  TrigEMCluster_trigChain =0;
  TrigEMCluster_trigDec =0;

  // TrigElectron Leaf
  TrigElectron_roiId = 0;
  TrigElectron_roiWord = 0;
  TrigElectron_isValid = 0;
  TrigElectron_charge = 0;
  TrigElectron_trackAlgo = 0;
  TrigElectron_Zvtx = 0;
  TrigElectron_err_Zvtx = 0;
  TrigElectron_Pt_track = 0;
  TrigElectron_err_Pt = 0;
  TrigElectron_trkEtaAtCalo = 0;
  TrigElectron_err_Eta = 0;
  TrigElectron_trkPhiAtCalo = 0;
  TrigElectron_err_Phi = 0;
  TrigElectron_TrackIndex = 0;
  TrigElectron_EtOverPt = 0;
  TrigElectron_trkClusDeta = 0;
  TrigElectron_trkClusDphi = 0;
  TrigElectron_ClusIndex = 0;
  TrigElectron_caloEta = 0;
  TrigElectron_caloPhi = 0;
  TrigElectron_Rcore = 0;
  TrigElectron_Eratio = 0;
  TrigElectron_EThad = 0;
  TrigElectron_E = 0;
  TrigElectron_Pt = 0;
  TrigElectron_Phi = 0;
  TrigElectron_Eta = 0;
  TrigElectron_trigChain =0;
  TrigElectron_trigDec =0;
  
  // TrigPhoton Leaf
  TrigPhoton_roiID = 0;
  TrigPhoton_isValid = 0;
  TrigPhoton_Et = 0;
  TrigPhoton_HadEt = 0;
  TrigPhoton_energyRatio = 0;
  TrigPhoton_rCore = 0;
  TrigPhoton_dPhi = 0;
  TrigPhoton_dEta = 0;
  TrigPhoton_ClusIndex = 0;
  TrigPhoton_E = 0;
  TrigPhoton_Phi = 0;
  TrigPhoton_Eta = 0;
  TrigPhoton_trigChain =0;
  TrigPhoton_trigDec =0;

  // TrigInDetTrack Leaf
  TrigInDetTrack_AlgoId = 0;
  TrigInDetTrack_chi2 = 0;
  TrigInDetTrack_slice = 0;
  TrigInDetTrack_NStrawHits = 0;
  TrigInDetTrack_NStraw = 0;
  TrigInDetTrack_NStrawTime = 0;
  TrigInDetTrack_NTRHits = 0;
  TrigInDetTrack_NSiSpacePoints = 0;
  TrigInDetTrack_BL_hits = 0;
  TrigInDetTrack_Pixel_hits = 0;
  TrigInDetTrack_SCT_hits = 0;
  TrigInDetTrack_a0 = 0;
  TrigInDetTrack_z0 = 0;
  TrigInDetTrack_phi0 = 0;
  TrigInDetTrack_eta = 0;
  TrigInDetTrack_pT = 0;
  TrigInDetTrack_ea0 = 0;
  TrigInDetTrack_ez0 = 0;
  TrigInDetTrack_ephi0 = 0;
  TrigInDetTrack_eeta = 0;
  TrigInDetTrack_epT = 0;
  TrigInDetTrack_end_a0 = 0;
  TrigInDetTrack_end_z0 = 0;
  TrigInDetTrack_end_phi0 = 0;
  TrigInDetTrack_end_eta = 0;
  TrigInDetTrack_end_pT = 0;
  TrigInDetTrack_end_ea0 = 0;
  TrigInDetTrack_end_ez0 = 0;
  TrigInDetTrack_end_ephi0 = 0;
  TrigInDetTrack_end_eeta = 0;
  TrigInDetTrack_end_epT = 0;
  TrigInDetTrack_trigChain =0;
  TrigInDetTrack_trigDec =0;

  // EFCaloCluster Leaf
  EFCaloCluster_energy = 0;
  EFCaloCluster_eta = 0;
  EFCaloCluster_phi = 0;
  EFCaloCluster_m = 0;
  EFCaloCluster_pt = 0;
  EFCaloCluster_coll=0;
  EFCaloCluster_nSamples = 0;
  EFCaloCluster_EInSample = 0;
  EFCaloCluster_EtaInSample = 0;
  EFCaloCluster_PhiInSample = 0;
  EFCaloCluster_BasicEnergy = 0;
  EFCaloCluster_Time = 0;
  EFCaloCluster_ClusterSize = 0;
  EFCaloCluster_EtaSize = 0;
  EFCaloCluster_PhiSize = 0;
  EFCaloCluster_eta0 = 0;
  EFCaloCluster_phi0 = 0;
  EFCaloCluster_EMax = 0;
  EFCaloCluster_EtaMax = 0;
  EFCaloCluster_PhiMax = 0;
  EFCaloCluster_EBe = 0;
  EFCaloCluster_EtaBe = 0;
  EFCaloCluster_PhiBe = 0;
  EFCaloCluster_trigChain = 0;
  EFCaloCluster_trigDec = 0;
  
  //EFTrackparticle Leaf
  EFTrackParticle_slice = 0;
  EFTrackParticle_pt = 0;
  EFTrackParticle_phi = 0;
  EFTrackParticle_eta = 0;
  EFTrackParticle_charge = 0;
  EFTrackParticle_chi2 = 0;
  EFTrackParticle_BL_hits = 0;
  EFTrackParticle_Pixel_hits = 0;
  EFTrackParticle_SCT_hits = 0;
  EFTrackParticle_TRT_hits = 0;
  EFTrackParticle_TRT_out = 0;
  EFTrackParticle_TRT_tubeHits = 0;
  EFTrackParticle_TRT_highHits = 0;
  EFTrackParticle_TRT_highOut = 0;
  EFTrackParticle_eProb = 0;
  EFTrackParticle_a0 = 0;
  EFTrackParticle_z0 = 0;
  EFTrackParticle_phi0 = 0;
  EFTrackParticle_eOVERt = 0;
  EFTrackParticle_trigChain = 0;
  EFTrackParticle_trigDec = 0;
  
  // EFegamma Laef
  EFegamma_e = 0;
  EFegamma_et = 0;
  EFegamma_pt = 0;
  EFegamma_phi = 0;
  EFegamma_eta = 0;
  EFegamma_m = 0;
  EFegamma_PID = 0;
  EFegamma_author = 0;
  EFegamma_isem = 0;
  EFegamma_isemse = 0;
  EFegamma_TrackIndex = 0;
  EFegamma_ClusIndex = 0;
  EFegamma_charge = 0;
  EFegamma_etaBE2 = 0;
  EFegamma_Eclu = 0;
  EFegamma_e233 = 0;
  EFegamma_e237 = 0;
  EFegamma_e277 = 0;
  EFegamma_ethad = 0;
  EFegamma_ethad1 = 0;
  EFegamma_weta1 = 0;
  EFegamma_weta2 = 0;
  EFegamma_f1 = 0;
  EFegamma_e2tsts1 = 0;
  EFegamma_emaxs1 = 0;
  EFegamma_emins1 = 0;
  EFegamma_wtots1 = 0;
  EFegamma_fracs1 = 0;
  EFegamma_etcone20 = 0;
  EFegamma_dEta = 0;
  EFegamma_dPhi = 0;
  EFegamma_eOVERp = 0;
  EFegamma_nBL = 0;
  EFegamma_nPix = 0;
  EFegamma_nSCT = 0;
  EFegamma_nTRThigh = 0;
  EFegamma_nTRThighOut = 0;
  EFegamma_nTRT = 0;
  EFegamma_nTRTOut = 0;
  EFegamma_trkPt = 0;
  EFegamma_trkCosTh = 0;
  EFegamma_trkSinTh = 0;
  EFegamma_trkD0 = 0;
  EFegamma_isElectron = 0;
  EFegamma_isPhoton = 0;
  EFegamma_trigChain = 0;
  EFegamma_trigDec = 0;
  
  // OFFCaloCluster Leaf
  OFFCaloCluster_energy = 0;
  OFFCaloCluster_eta = 0;
  OFFCaloCluster_phi = 0;
  OFFCaloCluster_m = 0;
  OFFCaloCluster_pt = 0;
  OFFCaloCluster_coll=0;
  OFFCaloCluster_nSamples = 0;
  OFFCaloCluster_EInSample = 0;
  OFFCaloCluster_EtaInSample = 0;
  OFFCaloCluster_PhiInSample = 0;
  OFFCaloCluster_EInSampleRaw = 0;
  OFFCaloCluster_EtaInSampleRaw = 0;
  OFFCaloCluster_PhiInSampleRaw = 0;
  OFFCaloCluster_BasicEnergy = 0;
  OFFCaloCluster_Time = 0;
  OFFCaloCluster_ClusterSize = 0;
  OFFCaloCluster_EtaSize = 0;
  OFFCaloCluster_PhiSize = 0;
  OFFCaloCluster_nCell = 0;
  OFFCaloCluster_eta0 = 0;
  OFFCaloCluster_phi0 = 0;
  OFFCaloCluster_etaRaw = 0;
  OFFCaloCluster_phiRaw = 0;
  OFFCaloCluster_eRaw = 0;
  OFFCaloCluster_EMax = 0;
  OFFCaloCluster_EtaMax = 0;
  OFFCaloCluster_PhiMax = 0;
  OFFCaloCluster_EBe = 0;
  OFFCaloCluster_EtaBe = 0;
  OFFCaloCluster_PhiBe = 0;
  OFFCaloCluster_trigChain = 0;
  OFFCaloCluster_trigDec = 0;
  
  //OFFTrackparticle Leaf
  OFFTrackParticle_slice = 0;
  OFFTrackParticle_pt = 0;
  OFFTrackParticle_phi = 0;
  OFFTrackParticle_eta = 0;
  OFFTrackParticle_charge = 0;
  OFFTrackParticle_chi2 = 0;
  OFFTrackParticle_BL_hits = 0;
  OFFTrackParticle_Pixel_hits = 0;
  OFFTrackParticle_SCT_hits = 0;
  OFFTrackParticle_TRT_hits = 0;
  OFFTrackParticle_TRT_out = 0;
  OFFTrackParticle_TRT_tubeHits = 0;
  OFFTrackParticle_TRT_highHits = 0;
  OFFTrackParticle_TRT_highOut = 0;
  OFFTrackParticle_eProb = 0;
  OFFTrackParticle_a0 = 0;
  OFFTrackParticle_z0 = 0;
  OFFTrackParticle_phi0 = 0;
  OFFTrackParticle_eOVERt = 0;
  OFFTrackParticle_trigChain = 0;
  OFFTrackParticle_trigDec = 0;
  
  // OFFegamma Laef
  OFFegamma_e = 0;
  OFFegamma_et = 0;
  OFFegamma_pt = 0;
  OFFegamma_phi = 0;
  OFFegamma_eta = 0;
  OFFegamma_m = 0;
  OFFegamma_PID = 0;
  OFFegamma_author = 0;
  OFFegamma_isem = 0;
  OFFegamma_isemse = 0;
  OFFegamma_isLoose = 0;
  OFFegamma_isMedium= 0;
  OFFegamma_isTight = 0;
  OFFegamma_TrackIndex = 0;
  OFFegamma_ClusIndex = 0;
  OFFegamma_charge = 0;
  OFFegamma_etaBE2 = 0;
  OFFegamma_Eclu = 0;
  OFFegamma_e233 = 0;
  OFFegamma_e237 = 0;
  OFFegamma_e277 = 0;
  OFFegamma_ethad = 0;
  OFFegamma_ethad1 = 0;
  OFFegamma_weta1 = 0;
  OFFegamma_weta2 = 0;
  OFFegamma_f1 = 0;
  OFFegamma_e2tsts1 = 0;
  OFFegamma_emaxs1 = 0;
  OFFegamma_emins1 = 0;
  OFFegamma_wtots1 = 0;
  OFFegamma_fracs1 = 0;
  OFFegamma_etcone20 = 0;
  OFFegamma_dEta = 0;
  OFFegamma_dPhi = 0;
  OFFegamma_eOVERp = 0;
  OFFegamma_nBL = 0;
  OFFegamma_nPix = 0;
  OFFegamma_nSCT = 0;
  OFFegamma_nTRThigh = 0;
  OFFegamma_nTRThighOut = 0;
  OFFegamma_nTRT = 0;
  OFFegamma_nTRTOut = 0;
  OFFegamma_trkPt = 0;
  OFFegamma_trkCosTh = 0;
  OFFegamma_trkSinTh = 0;
  OFFegamma_trkD0 = 0;
  OFFegamma_MCtype = 0;
  OFFegamma_MCorig = 0;
  OFFegamma_MCorigMother = 0;
  OFFegamma_isElectron = 0;
  OFFegamma_isPhoton = 0;
  OFFegamma_trigChain = 0;
  OFFegamma_trigDec = 0;

  if (hasInfo) {
    fChainInfo->SetBranchAddress("Event_run_number", &Event_run_number, &b_Event_run_number);
    fChainInfo->SetBranchAddress("Event_evt_number", &Event_evt_number, &b_Event_evt_number);
    fChainInfo->SetBranchAddress("Event_time_stamp", &Event_time_stamp, &b_Event_time_stamp);
    fChainInfo->SetBranchAddress("Event_time_stamp_ns_offset", &Event_time_stamp_ns_offset, &b_Event_time_stamp_ns_off);
    fChainInfo->SetBranchAddress("Event_lumiBlock", &Event_lumiBlock, &b_Event_lumiBlock);
    fChainInfo->SetBranchAddress("Event_bc_id", &Event_bc_id, &b_Event_bc_id);
    fChainInfo->SetBranchAddress("Event_det_mask0", &Event_det_mask0, &b_Event_det_mask0);
    fChainInfo->SetBranchAddress("Event_det_mask1", &Event_det_mask1, &b_Event_det_mask1);
    fChainInfo->SetBranchAddress("Event_deltaT_Calo", &Event_deltaT_Calo, &b_Event_deltaT_Calo);
    fChainInfo->SetBranchAddress("Event_deltaT_MBTS", &Event_deltaT_MBTS, &b_Event_deltaT_MBTS);
    fChainInfo->SetBranchAddress("Event_passed_MBTS", &Event_passed_MBTS, &b_Event_passed_MBTS);  
    fChainInfo->SetBranchAddress("Event_Trigger_present", &Event_Trigger_present, &b_Event_Trigger_present);
    fChainInfo->SetBranchAddress("Event_Trigger_status_element", &Event_Trigger_status_element, &b_Event_Trigger_status_element);
    fChainInfo->SetBranchAddress("Event_Trigger_extended_lvl1_id", &Event_Trigger_extended_lvl1_id, &b_Event_Trigger_extended_lvl1_id);
    fChainInfo->SetBranchAddress("Event_Trigger_lvl1_trig_type", &Event_Trigger_lvl1_trig_type, &b_Event_Trigger_lvl1_trig_type);
    fChainInfo->SetBranchAddress("Event_Trigger_nlvl1_trig_info", &Event_Trigger_nlvl1_trig_info, &b_Event_Trigger_nlvl1_trig_info);
    fChainInfo->SetBranchAddress("Event_Trigger_lvl1_trig_info", &Event_Trigger_lvl1_trig_info, &b_Event_Trigger_lvl1_trig_info);
    fChainInfo->SetBranchAddress("Event_Trigger_nlvl2_trig_info", &Event_Trigger_nlvl2_trig_info, &b_Event_Trigger_nlvl2_trig_info);
    fChainInfo->SetBranchAddress("Event_Trigger_lvl2_trig_info", &Event_Trigger_lvl2_trig_info, &b_Event_Trigger_lvl2_trig_info);
    fChainInfo->SetBranchAddress("Event_Trigger_nevt_filter_info", &Event_Trigger_nevt_filter_info, &b_Event_Trigger_nevt_filter_info);
    fChainInfo->SetBranchAddress("Event_Trigger_evt_filter_info", &Event_Trigger_evt_filter_info, &b_Event_Trigger_evt_filter_info);
    fChainInfo->SetBranchAddress("MET_et", &MET_et, &b_MET_et);
    fChainInfo->SetBranchAddress("MET_phi", &MET_phi, &b_MET_phi);
  }

  if (hasTrigger) {
    fChainTrigger->SetBranchAddress("Trigger_L1passed", &Trigger_L1passed, &b_Trigger_L1passed);
    fChainTrigger->SetBranchAddress("Trigger_L2passed", &Trigger_L2passed, &b_Trigger_L2passed);
    fChainTrigger->SetBranchAddress("Trigger_EFpassed", &Trigger_EFpassed, &b_Trigger_EFpassed);
    fChainTrigger->SetBranchAddress("Trigger_L1passed_PT", &Trigger_L1passed_PT, &b_Trigger_L1passed_PT);
    fChainTrigger->SetBranchAddress("Trigger_L2passed_PT", &Trigger_L2passed_PT, &b_Trigger_L2passed_PT);
    fChainTrigger->SetBranchAddress("Trigger_EFpassed_PT", &Trigger_EFpassed_PT, &b_Trigger_EFpassed_PT);
    fChainTrigger->SetBranchAddress("Trigger_L1prescale", &Trigger_L1prescale, &b_Trigger_L1prescale);
    fChainTrigger->SetBranchAddress("Trigger_L2prescale", &Trigger_L2prescale, &b_Trigger_L2prescale);
    fChainTrigger->SetBranchAddress("Trigger_EFprescale", &Trigger_EFprescale, &b_Trigger_EFprescale);


    fChainMetadata->SetBranchAddress("Trigger_L1ChainName", &Trigger_L1ChainName, &b_Trigger_L1ChainName);
    fChainMetadata->SetBranchAddress("Trigger_L2ChainName", &Trigger_L2ChainName, &b_Trigger_L2ChainName);
    fChainMetadata->SetBranchAddress("Trigger_EFChainName", &Trigger_EFChainName, &b_Trigger_EFChainName);
  }

  if (hasTruth) {
    fChainTruth->SetBranchAddress("truth_npart", &truth_npart, &b_truth_npart);
    fChainTruth->SetBranchAddress("truth_px", &truth_px, &b_truth_px);
    fChainTruth->SetBranchAddress("truth_py", &truth_py, &b_truth_py);
    fChainTruth->SetBranchAddress("truth_pz", &truth_pz, &b_truth_pz);
    fChainTruth->SetBranchAddress("truth_e", &truth_e, &b_truth_e);
    fChainTruth->SetBranchAddress("truth_phi", &truth_phi, &b_truth_phi);
    fChainTruth->SetBranchAddress("truth_eta", &truth_eta, &b_truth_eta);
    fChainTruth->SetBranchAddress("truth_pt", &truth_pt, &b_truth_pt);
    fChainTruth->SetBranchAddress("truth_status", &truth_status, &b_truth_status);
    fChainTruth->SetBranchAddress("truth_PDGId", &truth_PDGId, &b_truth_PDGId);
    fChainTruth->SetBranchAddress("truth_MotherPDGId", &truth_MotherPDGId, &b_truth_MotherPDGId);
    fChainTruth->SetBranchAddress("truth_barcode", &truth_barcode, &b_truth_barcode);
    fChainTruth->SetBranchAddress("truth_charge", &truth_charge, &b_truth_charge);
    fChainTruth->SetBranchAddress("truth_prod_vtx", &truth_prod_vtx, &b_truth_prod_vtx);
    fChainTruth->SetBranchAddress("truth_end_vtx", &truth_end_vtx, &b_truth_end_vtx);
  }
  
  if (hasL1) {
    fChainL1->SetBranchAddress("L1ROI_nClus", &L1ROI_nClus, &b_L1ROI_nClus);
    fChainL1->SetBranchAddress("L1ROI_eta", &L1ROI_eta, &b_L1ROI_eta);
    fChainL1->SetBranchAddress("L1ROI_phi", &L1ROI_phi, &b_L1ROI_phi);
    fChainL1->SetBranchAddress("L1ROI_Core", &L1ROI_Core, &b_L1ROI_Core);
    fChainL1->SetBranchAddress("L1ROI_EMet", &L1ROI_EMet, &b_L1ROI_EMet);
    fChainL1->SetBranchAddress("L1ROI_EMiso", &L1ROI_EMiso, &b_L1ROI_EMiso);
    fChainL1->SetBranchAddress("L1ROI_Hadiso", &L1ROI_Hadiso, &b_L1ROI_Hadiso);
    fChainL1->SetBranchAddress("L1ROI_Hadcore", &L1ROI_Hadcore, &b_L1ROI_Hadcore);
    fChainL1->SetBranchAddress("L1ROI_ROIword", &L1ROI_ROIword, &b_L1ROI_ROIword);
    fChainL1->SetBranchAddress("L1ROI_trigChain", &L1ROI_trigChain, &b_L1ROI_trigChain);
    fChainL1->SetBranchAddress("L1ROI_trigDec", &L1ROI_trigDec, &b_L1ROI_trigDec);
  }
  
  if (hasL2Cluster) {
    fChainL2Cluster->SetBranchAddress("TrigEMCluster_nClus", &TrigEMCluster_nClus, &b_TrigEMCluster_nClus);
    fChainL2Cluster->SetBranchAddress("TrigEMCluster_energy", &TrigEMCluster_energy, &b_TrigEMCluster_energy);
    fChainL2Cluster->SetBranchAddress("TrigEMCluster_coll", &TrigEMCluster_coll, &b_TrigEMCluster_coll);
    fChainL2Cluster->SetBranchAddress("TrigEMCluster_et", &TrigEMCluster_et, &b_TrigEMCluster_et);
    fChainL2Cluster->SetBranchAddress("TrigEMCluster_energyInSample", &TrigEMCluster_energyInSample, &b_TrigEMCluster_energyInSample);
    fChainL2Cluster->SetBranchAddress("TrigEMCluster_eta", &TrigEMCluster_eta, &b_TrigEMCluster_eta);
    fChainL2Cluster->SetBranchAddress("TrigEMCluster_phi", &TrigEMCluster_phi, &b_TrigEMCluster_phi);
    fChainL2Cluster->SetBranchAddress("TrigEMCluster_e237", &TrigEMCluster_e237, &b_TrigEMCluster_e237);
    fChainL2Cluster->SetBranchAddress("TrigEMCluster_e277", &TrigEMCluster_e277, &b_TrigEMCluster_e277);
    fChainL2Cluster->SetBranchAddress("TrigEMCluster_fracs1", &TrigEMCluster_fracs1, &b_TrigEMCluster_fracs1);
    fChainL2Cluster->SetBranchAddress("TrigEMCluster_weta2", &TrigEMCluster_weta2, &b_TrigEMCluster_weta2);
    fChainL2Cluster->SetBranchAddress("TrigEMCluster_ehad1", &TrigEMCluster_ehad1, &b_TrigEMCluster_ehad1);
    fChainL2Cluster->SetBranchAddress("TrigEMCluster_Eta1", &TrigEMCluster_Eta1, &b_TrigEMCluster_Eta1);
    fChainL2Cluster->SetBranchAddress("TrigEMCluster_emaxs1", &TrigEMCluster_emaxs1, &b_TrigEMCluster_emaxs1);
    fChainL2Cluster->SetBranchAddress("TrigEMCluster_e2tsts1", &TrigEMCluster_e2tsts1, &b_TrigEMCluster_e2tsts1);
    fChainL2Cluster->SetBranchAddress("TrigEMCluster_quality", &TrigEMCluster_quality, &b_TrigEMCluster_quality);
    fChainL2Cluster->SetBranchAddress("TrigEMCluster_trigDec", &TrigEMCluster_trigDec, &b_TrigEMCluster_trigDec);
    fChainL2Cluster->SetBranchAddress("TrigEMCluster_trigChain", &TrigEMCluster_trigChain, &b_TrigEMCluster_trigChain);
  }

  if (hasL2Electron) {
    fChainL2Electron->SetBranchAddress("TrigElectron_nTrigElectron", &TrigElectron_nTrigElectron, &b_TrigElectron_nTrigElectron);
    fChainL2Electron->SetBranchAddress("TrigElectron_roiId", &TrigElectron_roiId, &b_TrigElectron_roiId);
    fChainL2Electron->SetBranchAddress("TrigElectron_roiWord", &TrigElectron_roiWord, &b_TrigElectron_roiWord);
    fChainL2Electron->SetBranchAddress("TrigElectron_isValid", &TrigElectron_isValid, &b_TrigElectron_isValid);
    fChainL2Electron->SetBranchAddress("TrigElectron_charge", &TrigElectron_charge, &b_TrigElectron_charge);
    fChainL2Electron->SetBranchAddress("TrigElectron_trackAlgo", &TrigElectron_trackAlgo, &b_TrigElectron_trackAlgo);
    fChainL2Electron->SetBranchAddress("TrigElectron_Zvtx", &TrigElectron_Zvtx, &b_TrigElectron_Zvtx);
    fChainL2Electron->SetBranchAddress("TrigElectron_err_Zvtx", &TrigElectron_err_Zvtx, &b_TrigElectron_err_Zvtx);
    fChainL2Electron->SetBranchAddress("TrigElectron_Pt_track", &TrigElectron_Pt_track, &b_TrigElectron_Pt_track);
    fChainL2Electron->SetBranchAddress("TrigElectron_err_Pt", &TrigElectron_err_Pt, &b_TrigElectron_err_Pt);
    fChainL2Electron->SetBranchAddress("TrigElectron_trkEtaAtCalo", &TrigElectron_trkEtaAtCalo, &b_TrigElectron_trkEtaAtCalo);
    fChainL2Electron->SetBranchAddress("TrigElectron_err_Eta", &TrigElectron_err_Eta, &b_TrigElectron_err_Eta);
    fChainL2Electron->SetBranchAddress("TrigElectron_trkPhiAtCalo", &TrigElectron_trkPhiAtCalo, &b_TrigElectron_trkPhiAtCalo);
    fChainL2Electron->SetBranchAddress("TrigElectron_err_Phi", &TrigElectron_err_Phi, &b_TrigElectron_err_Phi);
    fChainL2Electron->SetBranchAddress("TrigElectron_TrackIndex", &TrigElectron_TrackIndex, &b_TrigElectron_TrackIndex);
    fChainL2Electron->SetBranchAddress("TrigElectron_EtOverPt", &TrigElectron_EtOverPt, &b_TrigElectron_EtOverPt);
    fChainL2Electron->SetBranchAddress("TrigElectron_trkClusDeta", &TrigElectron_trkClusDeta, &b_TrigElectron_trkClusDeta);
    fChainL2Electron->SetBranchAddress("TrigElectron_trkClusDphi", &TrigElectron_trkClusDphi, &b_TrigElectron_trkClusDphi);
    fChainL2Electron->SetBranchAddress("TrigElectron_ClusIndex", &TrigElectron_ClusIndex, &b_TrigElectron_ClusIndex);
    fChainL2Electron->SetBranchAddress("TrigElectron_caloEta", &TrigElectron_caloEta, &b_TrigElectron_caloEta);
    fChainL2Electron->SetBranchAddress("TrigElectron_caloPhi", &TrigElectron_caloPhi, &b_TrigElectron_caloPhi);
    fChainL2Electron->SetBranchAddress("TrigElectron_Rcore", &TrigElectron_Rcore, &b_TrigElectron_Rcore);
    fChainL2Electron->SetBranchAddress("TrigElectron_Eratio", &TrigElectron_Eratio, &b_TrigElectron_Eratio);
    fChainL2Electron->SetBranchAddress("TrigElectron_EThad", &TrigElectron_EThad, &b_TrigElectron_EThad);
    fChainL2Electron->SetBranchAddress("TrigElectron_E", &TrigElectron_E, &b_TrigElectron_E);
    fChainL2Electron->SetBranchAddress("TrigElectron_Pt", &TrigElectron_Pt, &b_TrigElectron_Pt);
    fChainL2Electron->SetBranchAddress("TrigElectron_Phi", &TrigElectron_Phi, &b_TrigElectron_Phi);
    fChainL2Electron->SetBranchAddress("TrigElectron_Eta", &TrigElectron_Eta, &b_TrigElectron_Eta);
    fChainL2Electron->SetBranchAddress("TrigElectron_trigDec", &TrigElectron_trigDec, &b_TrigElectron_trigDec);
    fChainL2Electron->SetBranchAddress("TrigElectron_trigChain", &TrigElectron_trigChain, &b_TrigElectron_trigChain);
  }
  
  if (hasL2Photon) {
    fChainL2Photon->SetBranchAddress("TrigPhoton_nTrigPhoton", &TrigPhoton_nTrigPhoton, &b_TrigPhoton_nTrigPhoton);
    fChainL2Photon->SetBranchAddress("TrigPhoton_roiID", &TrigPhoton_roiID, &b_TrigPhoton_roiID);
    fChainL2Photon->SetBranchAddress("TrigPhoton_isValid", &TrigPhoton_isValid, &b_TrigPhoton_isValid);
    fChainL2Photon->SetBranchAddress("TrigPhoton_Et", &TrigPhoton_Et, &b_TrigPhoton_Et);
    fChainL2Photon->SetBranchAddress("TrigPhoton_HadEt", &TrigPhoton_HadEt, &b_TrigPhoton_HadEt);
    fChainL2Photon->SetBranchAddress("TrigPhoton_energyRatio", &TrigPhoton_energyRatio, &b_TrigPhoton_energyRatio);
    fChainL2Photon->SetBranchAddress("TrigPhoton_rCore", &TrigPhoton_rCore, &b_TrigPhoton_rCore);
    fChainL2Photon->SetBranchAddress("TrigPhoton_dPhi", &TrigPhoton_dPhi, &b_TrigPhoton_dPhi);
    fChainL2Photon->SetBranchAddress("TrigPhoton_dEta", &TrigPhoton_dEta, &b_TrigPhoton_dEta);
    fChainL2Photon->SetBranchAddress("TrigPhoton_ClusIndex", &TrigPhoton_ClusIndex, &b_TrigPhoton_ClusIndex);
    fChainL2Photon->SetBranchAddress("TrigPhoton_E", &TrigPhoton_E, &b_TrigPhoton_E);
    fChainL2Photon->SetBranchAddress("TrigPhoton_Phi", &TrigPhoton_Phi, &b_TrigPhoton_Phi);
    fChainL2Photon->SetBranchAddress("TrigPhoton_Eta", &TrigPhoton_Eta, &b_TrigPhoton_Eta);
    fChainL2Photon->SetBranchAddress("TrigPhoton_trigDec", &TrigPhoton_trigDec, &b_TrigPhoton_trigDec);
    fChainL2Photon->SetBranchAddress("TrigPhoton_trigChain", &TrigPhoton_trigChain, &b_TrigPhoton_trigChain);
  }
  
  if (hasL2Track) {
    fChainL2Track->SetBranchAddress("TrigInDetTrack_nTrack", &TrigInDetTrack_nTrack, &b_TrigInDetTrack_nTrack);
    fChainL2Track->SetBranchAddress("TrigInDetTrack_AlgoId", &TrigInDetTrack_AlgoId, &b_TrigInDetTrack_AlgoId);
    fChainL2Track->SetBranchAddress("TrigInDetTrack_chi2", &TrigInDetTrack_chi2, &b_TrigInDetTrack_chi2);
    fChainL2Track->SetBranchAddress("TrigInDetTrack_slice", &TrigInDetTrack_slice, &b_TrigInDetTrack_slice);
    fChainL2Track->SetBranchAddress("TrigInDetTrack_NStrawHits", &TrigInDetTrack_NStrawHits, &b_TrigInDetTrack_NStrawHits);
    fChainL2Track->SetBranchAddress("TrigInDetTrack_NStraw", &TrigInDetTrack_NStraw, &b_TrigInDetTrack_NStraw);
    fChainL2Track->SetBranchAddress("TrigInDetTrack_NStrawTime", &TrigInDetTrack_NStrawTime, &b_TrigInDetTrack_NStrawTime);
    fChainL2Track->SetBranchAddress("TrigInDetTrack_NTRHits", &TrigInDetTrack_NTRHits, &b_TrigInDetTrack_NTRHits);
    fChainL2Track->SetBranchAddress("TrigInDetTrack_NSiSpacePoints", &TrigInDetTrack_NSiSpacePoints, &b_TrigInDetTrack_NSiSpacePoints);
    fChainL2Track->SetBranchAddress("TrigInDetTrack_BL_hits", &TrigInDetTrack_BL_hits, &b_TrigInDetTrack_BL_hits);
    fChainL2Track->SetBranchAddress("TrigInDetTrack_Pixel_hits", &TrigInDetTrack_Pixel_hits, &b_TrigInDetTrack_Pixel_hits);
    fChainL2Track->SetBranchAddress("TrigInDetTrack_SCT_hits", &TrigInDetTrack_SCT_hits, &b_TrigInDetTrack_SCT_hits);  
    fChainL2Track->SetBranchAddress("TrigInDetTrack_a0", &TrigInDetTrack_a0, &b_TrigInDetTrack_a0);
    fChainL2Track->SetBranchAddress("TrigInDetTrack_z0", &TrigInDetTrack_z0, &b_TrigInDetTrack_z0);
    fChainL2Track->SetBranchAddress("TrigInDetTrack_phi0", &TrigInDetTrack_phi0, &b_TrigInDetTrack_phi0);
    fChainL2Track->SetBranchAddress("TrigInDetTrack_eta", &TrigInDetTrack_eta, &b_TrigInDetTrack_eta);
    fChainL2Track->SetBranchAddress("TrigInDetTrack_pT", &TrigInDetTrack_pT, &b_TrigInDetTrack_pT);
    fChainL2Track->SetBranchAddress("TrigInDetTrack_ea0", &TrigInDetTrack_ea0, &b_TrigInDetTrack_ea0);
    fChainL2Track->SetBranchAddress("TrigInDetTrack_ez0", &TrigInDetTrack_ez0, &b_TrigInDetTrack_ez0);
    fChainL2Track->SetBranchAddress("TrigInDetTrack_ephi0", &TrigInDetTrack_ephi0, &b_TrigInDetTrack_ephi0);
    fChainL2Track->SetBranchAddress("TrigInDetTrack_eeta", &TrigInDetTrack_eeta, &b_TrigInDetTrack_eeta);
    fChainL2Track->SetBranchAddress("TrigInDetTrack_epT", &TrigInDetTrack_epT, &b_TrigInDetTrack_epT);
    fChainL2Track->SetBranchAddress("TrigInDetTrack_end_a0", &TrigInDetTrack_end_a0, &b_TrigInDetTrack_end_a0);
    fChainL2Track->SetBranchAddress("TrigInDetTrack_end_z0", &TrigInDetTrack_end_z0, &b_TrigInDetTrack_end_z0);
    fChainL2Track->SetBranchAddress("TrigInDetTrack_end_phi0", &TrigInDetTrack_end_phi0, &b_TrigInDetTrack_end_phi0);
    fChainL2Track->SetBranchAddress("TrigInDetTrack_end_eta", &TrigInDetTrack_end_eta, &b_TrigInDetTrack_end_eta);
    fChainL2Track->SetBranchAddress("TrigInDetTrack_end_pT", &TrigInDetTrack_end_pT, &b_TrigInDetTrack_end_pT);
    fChainL2Track->SetBranchAddress("TrigInDetTrack_end_ea0", &TrigInDetTrack_end_ea0, &b_TrigInDetTrack_end_ea0);
    fChainL2Track->SetBranchAddress("TrigInDetTrack_end_ez0", &TrigInDetTrack_end_ez0, &b_TrigInDetTrack_end_ez0);
    fChainL2Track->SetBranchAddress("TrigInDetTrack_end_ephi0", &TrigInDetTrack_end_ephi0, &b_TrigInDetTrack_end_ephi0);
    fChainL2Track->SetBranchAddress("TrigInDetTrack_end_eeta", &TrigInDetTrack_end_eeta, &b_TrigInDetTrack_end_eeta);
    fChainL2Track->SetBranchAddress("TrigInDetTrack_end_epT", &TrigInDetTrack_end_epT, &b_TrigInDetTrack_end_epT);
    fChainL2Track->SetBranchAddress("TrigInDetTrack_trigDec", &TrigInDetTrack_trigDec, &b_TrigInDetTrack_trigDec);
    fChainL2Track->SetBranchAddress("TrigInDetTrack_trigChain", &TrigInDetTrack_trigChain, &b_TrigInDetTrack_trigChain);
  } 

  if (hasEFCluster) {
    fChainEFCluster->SetBranchAddress("EFCaloCluster_nClus", &EFCaloCluster_nClus, &b_EFCaloCluster_nClus);
    fChainEFCluster->SetBranchAddress("EFCaloCluster_energy", &EFCaloCluster_energy, &b_EFCaloCluster_energy);
    fChainEFCluster->SetBranchAddress("EFCaloCluster_eta", &EFCaloCluster_eta, &b_EFCaloCluster_eta);
    fChainEFCluster->SetBranchAddress("EFCaloCluster_phi", &EFCaloCluster_phi, &b_EFCaloCluster_phi);
    fChainEFCluster->SetBranchAddress("EFCaloCluster_m", &EFCaloCluster_m, &b_EFCaloCluster_m);
    fChainEFCluster->SetBranchAddress("EFCaloCluster_pt", &EFCaloCluster_pt, &b_EFCaloCluster_pt);
    fChainEFCluster->SetBranchAddress("EFCaloCluster_coll", &EFCaloCluster_coll, &b_EFCaloCluster_coll);
    fChainEFCluster->SetBranchAddress("EFCaloCluster_nSamples", &EFCaloCluster_nSamples, &b_EFCaloCluster_nSamples);
    fChainEFCluster->SetBranchAddress("EFCaloCluster_EInSample", &EFCaloCluster_EInSample, &b_EFCaloCluster_EInSample);
    fChainEFCluster->SetBranchAddress("EFCaloCluster_EtaInSample", &EFCaloCluster_EtaInSample, &b_EFCaloCluster_EtaInSample);
    fChainEFCluster->SetBranchAddress("EFCaloCluster_PhiInSample", &EFCaloCluster_PhiInSample, &b_EFCaloCluster_PhiInSample);
    fChainEFCluster->SetBranchAddress("EFCaloCluster_BasicEnergy", &EFCaloCluster_BasicEnergy, &b_EFCaloCluster_BasicEnergy);
    fChainEFCluster->SetBranchAddress("EFCaloCluster_Time", &EFCaloCluster_Time, &b_EFCaloCluster_Time);
    fChainEFCluster->SetBranchAddress("EFCaloCluster_ClusterSize", &EFCaloCluster_ClusterSize, &b_EFCaloCluster_ClusterSize);
    fChainEFCluster->SetBranchAddress("EFCaloCluster_EtaSize", &EFCaloCluster_EtaSize, &b_EFCaloCluster_EtaSize);
    fChainEFCluster->SetBranchAddress("EFCaloCluster_PhiSize", &EFCaloCluster_PhiSize, &b_EFCaloCluster_PhiSize);
    fChainEFCluster->SetBranchAddress("EFCaloCluster_eta0", &EFCaloCluster_eta0, &b_EFCaloCluster_eta0);
    fChainEFCluster->SetBranchAddress("EFCaloCluster_phi0", &EFCaloCluster_phi0, &b_EFCaloCluster_phi0);
    fChainEFCluster->SetBranchAddress("EFCaloCluster_EMax", &EFCaloCluster_EMax, &b_EFCaloCluster_EMax);
    fChainEFCluster->SetBranchAddress("EFCaloCluster_EtaMax", &EFCaloCluster_EtaMax, &b_EFCaloCluster_EtaMax);
    fChainEFCluster->SetBranchAddress("EFCaloCluster_PhiMax", &EFCaloCluster_PhiMax, &b_EFCaloCluster_PhiMax);
    fChainEFCluster->SetBranchAddress("EFCaloCluster_EBe", &EFCaloCluster_EBe, &b_EFCaloCluster_EBe);
    fChainEFCluster->SetBranchAddress("EFCaloCluster_EtaBe", &EFCaloCluster_EtaBe, &b_EFCaloCluster_EtaBe);
    fChainEFCluster->SetBranchAddress("EFCaloCluster_PhiBe", &EFCaloCluster_PhiBe, &b_EFCaloCluster_PhiBe);
    fChainEFCluster->SetBranchAddress("EFCaloCluster_trigChain", &EFCaloCluster_trigChain, &b_EFCaloCluster_trigChain);
    fChainEFCluster->SetBranchAddress("EFCaloCluster_trigDec", &EFCaloCluster_trigDec, &b_EFCaloCluster_trigDec);
  }

  if (hasEFTrack) {
    fChainEFTrack->SetBranchAddress("EFTrackParticle_nTrack", &EFTrackParticle_nTrack, &b_EFTrackParticle_nTrack);
    fChainEFTrack->SetBranchAddress("EFTrackParticle_slice", &EFTrackParticle_slice, &b_EFTrackParticle_slice);
    fChainEFTrack->SetBranchAddress("EFTrackParticle_pt", &EFTrackParticle_pt, &b_EFTrackParticle_pt);
    fChainEFTrack->SetBranchAddress("EFTrackParticle_phi", &EFTrackParticle_phi, &b_EFTrackParticle_phi);
    fChainEFTrack->SetBranchAddress("EFTrackParticle_eta", &EFTrackParticle_eta, &b_EFTrackParticle_eta);
    fChainEFTrack->SetBranchAddress("EFTrackParticle_charge", &EFTrackParticle_charge, &b_EFTrackParticle_charge);
    fChainEFTrack->SetBranchAddress("EFTrackParticle_chi2", &EFTrackParticle_chi2, &b_EFTrackParticle_chi2);
    fChainEFTrack->SetBranchAddress("EFTrackParticle_BL_hits", &EFTrackParticle_BL_hits, &b_EFTrackParticle_BL_hits);
    fChainEFTrack->SetBranchAddress("EFTrackParticle_Pixel_hits", &EFTrackParticle_Pixel_hits, &b_EFTrackParticle_Pixel_hits);
    fChainEFTrack->SetBranchAddress("EFTrackParticle_SCT_hits", &EFTrackParticle_SCT_hits, &b_EFTrackParticle_SCT_hits);
    fChainEFTrack->SetBranchAddress("EFTrackParticle_TRT_hits", &EFTrackParticle_TRT_hits, &b_EFTrackParticle_TRT_hits);
    fChainEFTrack->SetBranchAddress("EFTrackParticle_TRT_out", &EFTrackParticle_TRT_out, &b_EFTrackParticle_TRT_out);
    fChainEFTrack->SetBranchAddress("EFTrackParticle_TRT_tubeHits", &EFTrackParticle_TRT_tubeHits, &b_EFTrackParticle_TRT_tubeHits);
    fChainEFTrack->SetBranchAddress("EFTrackParticle_TRT_highHits", &EFTrackParticle_TRT_highHits, &b_EFTrackParticle_TRT_highHits);
    fChainEFTrack->SetBranchAddress("EFTrackParticle_TRT_highOut", &EFTrackParticle_TRT_highOut, &b_EFTrackParticle_TRT_highOut);
    fChainEFTrack->SetBranchAddress("EFTrackParticle_eProb", &EFTrackParticle_eProb, &b_EFTrackParticle_eProb);
    fChainEFTrack->SetBranchAddress("EFTrackParticle_a0", &EFTrackParticle_a0, &b_EFTrackParticle_a0);
    fChainEFTrack->SetBranchAddress("EFTrackParticle_z0", &EFTrackParticle_z0, &b_EFTrackParticle_z0);
    fChainEFTrack->SetBranchAddress("EFTrackParticle_phi0", &EFTrackParticle_phi0, &b_EFTrackParticle_phi0);
    fChainEFTrack->SetBranchAddress("EFTrackParticle_eOVERt", &EFTrackParticle_eOVERt, &b_EFTrackParticle_eOVERt);
    fChainEFTrack->SetBranchAddress("EFTrackParticle_trigChain", &EFTrackParticle_trigChain, &b_EFTrackParticle_trigChain);
    fChainEFTrack->SetBranchAddress("EFTrackParticle_trigDec", &EFTrackParticle_trigDec, &b_EFTrackParticle_trigDec);
  }

  if (hasEFegamma) {
    fChainEFegamma->SetBranchAddress("EFegamma_nEGamma", &EFegamma_nEGamma, &b_EFegamma_nEGamma);
    fChainEFegamma->SetBranchAddress("EFegamma_e", &EFegamma_e, &b_EFegamma_e);
    fChainEFegamma->SetBranchAddress("EFegamma_et", &EFegamma_et, &b_EFegamma_et);
    fChainEFegamma->SetBranchAddress("EFegamma_pt", &EFegamma_pt, &b_EFegamma_pt);
    fChainEFegamma->SetBranchAddress("EFegamma_phi", &EFegamma_phi, &b_EFegamma_phi);
    fChainEFegamma->SetBranchAddress("EFegamma_eta", &EFegamma_eta, &b_EFegamma_eta);
    fChainEFegamma->SetBranchAddress("EFegamma_m", &EFegamma_m, &b_EFegamma_m);
    fChainEFegamma->SetBranchAddress("EFegamma_PID", &EFegamma_PID, &b_EFegamma_PID);
    fChainEFegamma->SetBranchAddress("EFegamma_author", &EFegamma_author, &b_EFegamma_author);
    fChainEFegamma->SetBranchAddress("EFegamma_isem", &EFegamma_isem, &b_EFegamma_isem);
    fChainEFegamma->SetBranchAddress("EFegamma_isemse", &EFegamma_isemse, &b_EFegamma_isemse);
    fChainEFegamma->SetBranchAddress("EFegamma_TrackIndex", &EFegamma_TrackIndex, &b_EFegamma_TrackIndex);
    fChainEFegamma->SetBranchAddress("EFegamma_ClusIndex", &EFegamma_ClusIndex, &b_EFegamma_ClusIndex);
    fChainEFegamma->SetBranchAddress("EFegamma_charge", &EFegamma_charge, &b_EFegamma_charge);
    fChainEFegamma->SetBranchAddress("EFegamma_etaBE2", &EFegamma_etaBE2, &b_EFegamma_etaBE2);
    fChainEFegamma->SetBranchAddress("EFegamma_Eclu", &EFegamma_Eclu, &b_EFegamma_Eclu);
    fChainEFegamma->SetBranchAddress("EFegamma_e233", &EFegamma_e233, &b_EFegamma_e233);
    fChainEFegamma->SetBranchAddress("EFegamma_e237", &EFegamma_e237, &b_EFegamma_e237);
    fChainEFegamma->SetBranchAddress("EFegamma_e277", &EFegamma_e277, &b_EFegamma_e277);
    fChainEFegamma->SetBranchAddress("EFegamma_ethad", &EFegamma_ethad, &b_EFegamma_ethad);
    fChainEFegamma->SetBranchAddress("EFegamma_ethad1", &EFegamma_ethad1, &b_EFegamma_ethad1);
    fChainEFegamma->SetBranchAddress("EFegamma_weta1", &EFegamma_weta1, &b_EFegamma_weta1);
    fChainEFegamma->SetBranchAddress("EFegamma_weta2", &EFegamma_weta2, &b_EFegamma_weta2);
    fChainEFegamma->SetBranchAddress("EFegamma_f1", &EFegamma_f1, &b_EFegamma_f1);
    fChainEFegamma->SetBranchAddress("EFegamma_e2tsts1", &EFegamma_e2tsts1, &b_EFegamma_e2tsts1);
    fChainEFegamma->SetBranchAddress("EFegamma_emaxs1", &EFegamma_emaxs1, &b_EFegamma_emaxs1);
    fChainEFegamma->SetBranchAddress("EFegamma_emins1", &EFegamma_emins1, &b_EFegamma_emins1);
    fChainEFegamma->SetBranchAddress("EFegamma_wtots1", &EFegamma_wtots1, &b_EFegamma_wtots1);
    fChainEFegamma->SetBranchAddress("EFegamma_fracs1", &EFegamma_fracs1, &b_EFegamma_fracs1);
    fChainEFegamma->SetBranchAddress("EFegamma_etcone20", &EFegamma_etcone20, &b_EFegamma_etcone20);
    fChainEFegamma->SetBranchAddress("EFegamma_dEta", &EFegamma_dEta, &b_EFegamma_dEta);
    fChainEFegamma->SetBranchAddress("EFegamma_dPhi", &EFegamma_dPhi, &b_EFegamma_dPhi);
    fChainEFegamma->SetBranchAddress("EFegamma_eOVERp", &EFegamma_eOVERp, &b_EFegamma_eOVERp);
    fChainEFegamma->SetBranchAddress("EFegamma_nBL", &EFegamma_nBL, &b_EFegamma_nBL);
    fChainEFegamma->SetBranchAddress("EFegamma_nPix", &EFegamma_nPix, &b_EFegamma_nPix);
    fChainEFegamma->SetBranchAddress("EFegamma_nSCT", &EFegamma_nSCT, &b_EFegamma_nSCT);
    fChainEFegamma->SetBranchAddress("EFegamma_nTRThigh", &EFegamma_nTRThigh, &b_EFegamma_nTRThigh);
    fChainEFegamma->SetBranchAddress("EFegamma_nTRThighOut", &EFegamma_nTRThighOut, &b_EFegamma_nTRThighOut);
    fChainEFegamma->SetBranchAddress("EFegamma_nTRT", &EFegamma_nTRT, &b_EFegamma_nTRT);
    fChainEFegamma->SetBranchAddress("EFegamma_nTRTOut", &EFegamma_nTRTOut, &b_EFegamma_nTRTOut);
    fChainEFegamma->SetBranchAddress("EFegamma_trkPt", &EFegamma_trkPt, &b_EFegamma_trkPt);
    fChainEFegamma->SetBranchAddress("EFegamma_trkCosTh", &EFegamma_trkCosTh, &b_EFegamma_trkCosTh);
    fChainEFegamma->SetBranchAddress("EFegamma_trkSinTh", &EFegamma_trkSinTh, &b_EFegamma_trkSinTh);
    fChainEFegamma->SetBranchAddress("EFegamma_trkD0", &EFegamma_trkD0, &b_EFegamma_trkD0);
    fChainEFegamma->SetBranchAddress("EFegamma_isElectron", &EFegamma_isElectron, &b_EFegamma_isElectron);
    fChainEFegamma->SetBranchAddress("EFegamma_isPhoton", &EFegamma_isPhoton, &b_EFegamma_isPhoton);
    fChainEFegamma->SetBranchAddress("EFegamma_trigChain", &EFegamma_trigChain, &b_EFegamma_trigChain);
    fChainEFegamma->SetBranchAddress("EFegamma_trigDec", &EFegamma_trigDec, &b_EFegamma_trigDec);
  }
  
  if (hasOFFCluster) {
    fChainOFFCluster->SetBranchAddress("OFFCaloCluster_nClus", &OFFCaloCluster_nClus, &b_OFFCaloCluster_nClus);
    fChainOFFCluster->SetBranchAddress("OFFCaloCluster_energy", &OFFCaloCluster_energy, &b_OFFCaloCluster_energy);
    fChainOFFCluster->SetBranchAddress("OFFCaloCluster_eta", &OFFCaloCluster_eta, &b_OFFCaloCluster_eta);
    fChainOFFCluster->SetBranchAddress("OFFCaloCluster_phi", &OFFCaloCluster_phi, &b_OFFCaloCluster_phi);
    fChainOFFCluster->SetBranchAddress("OFFCaloCluster_m", &OFFCaloCluster_m, &b_OFFCaloCluster_m);
    fChainOFFCluster->SetBranchAddress("OFFCaloCluster_pt", &OFFCaloCluster_pt, &b_OFFCaloCluster_pt);
    fChainOFFCluster->SetBranchAddress("OFFCaloCluster_coll", &OFFCaloCluster_coll, &b_OFFCaloCluster_coll);
    fChainOFFCluster->SetBranchAddress("OFFCaloCluster_nSamples", &OFFCaloCluster_nSamples, &b_OFFCaloCluster_nSamples);
    fChainOFFCluster->SetBranchAddress("OFFCaloCluster_EInSample", &OFFCaloCluster_EInSample, &b_OFFCaloCluster_EInSample);
    fChainOFFCluster->SetBranchAddress("OFFCaloCluster_EtaInSample", &OFFCaloCluster_EtaInSample, &b_OFFCaloCluster_EtaInSample);
    fChainOFFCluster->SetBranchAddress("OFFCaloCluster_PhiInSample", &OFFCaloCluster_PhiInSample, &b_OFFCaloCluster_PhiInSample);
    fChainOFFCluster->SetBranchAddress("OFFCaloCluster_EInSampleRaw", &OFFCaloCluster_EInSampleRaw, &b_OFFCaloCluster_EInSampleRaw);
    fChainOFFCluster->SetBranchAddress("OFFCaloCluster_EtaInSampleRaw", &OFFCaloCluster_EtaInSampleRaw, &b_OFFCaloCluster_EtaInSampleRaw);
    fChainOFFCluster->SetBranchAddress("OFFCaloCluster_PhiInSampleRaw", &OFFCaloCluster_PhiInSampleRaw, &b_OFFCaloCluster_PhiInSampleRaw);
    fChainOFFCluster->SetBranchAddress("OFFCaloCluster_BasicEnergy", &OFFCaloCluster_BasicEnergy, &b_OFFCaloCluster_BasicEnergy);
    fChainOFFCluster->SetBranchAddress("OFFCaloCluster_Time", &OFFCaloCluster_Time, &b_OFFCaloCluster_Time);
    fChainOFFCluster->SetBranchAddress("OFFCaloCluster_ClusterSize", &OFFCaloCluster_ClusterSize, &b_OFFCaloCluster_ClusterSize);
    fChainOFFCluster->SetBranchAddress("OFFCaloCluster_EtaSize", &OFFCaloCluster_EtaSize, &b_OFFCaloCluster_EtaSize);
    fChainOFFCluster->SetBranchAddress("OFFCaloCluster_PhiSize", &OFFCaloCluster_PhiSize, &b_OFFCaloCluster_PhiSize);
    fChainOFFCluster->SetBranchAddress("OFFCaloCluster_nCell", &OFFCaloCluster_nCell, &b_OFFCaloCluster_nCell);
    fChainOFFCluster->SetBranchAddress("OFFCaloCluster_eta0", &OFFCaloCluster_eta0, &b_OFFCaloCluster_eta0);
    fChainOFFCluster->SetBranchAddress("OFFCaloCluster_phi0", &OFFCaloCluster_phi0, &b_OFFCaloCluster_phi0);
    fChainOFFCluster->SetBranchAddress("OFFCaloCluster_etaRaw", &OFFCaloCluster_etaRaw, &b_OFFCaloCluster_etaRaw);
    fChainOFFCluster->SetBranchAddress("OFFCaloCluster_phiRaw", &OFFCaloCluster_phiRaw, &b_OFFCaloCluster_phiRaw);
    fChainOFFCluster->SetBranchAddress("OFFCaloCluster_eRaw"  , &OFFCaloCluster_eRaw  , &b_OFFCaloCluster_eRaw);
    fChainOFFCluster->SetBranchAddress("OFFCaloCluster_EMax", &OFFCaloCluster_EMax, &b_OFFCaloCluster_EMax);
    fChainOFFCluster->SetBranchAddress("OFFCaloCluster_EtaMax", &OFFCaloCluster_EtaMax, &b_OFFCaloCluster_EtaMax);
    fChainOFFCluster->SetBranchAddress("OFFCaloCluster_PhiMax", &OFFCaloCluster_PhiMax, &b_OFFCaloCluster_PhiMax);
    fChainOFFCluster->SetBranchAddress("OFFCaloCluster_EBe", &OFFCaloCluster_EBe, &b_OFFCaloCluster_EBe);
    fChainOFFCluster->SetBranchAddress("OFFCaloCluster_EtaBe", &OFFCaloCluster_EtaBe, &b_OFFCaloCluster_EtaBe);
    fChainOFFCluster->SetBranchAddress("OFFCaloCluster_PhiBe", &OFFCaloCluster_PhiBe, &b_OFFCaloCluster_PhiBe);
    fChainOFFCluster->SetBranchAddress("OFFCaloCluster_trigChain", &OFFCaloCluster_trigChain, &b_OFFCaloCluster_trigChain);
    fChainOFFCluster->SetBranchAddress("OFFCaloCluster_trigDec", &OFFCaloCluster_trigDec, &b_OFFCaloCluster_trigDec);
  }

  if (hasOFFTrack) {
    fChainOFFTrack->SetBranchAddress("OFFTrackParticle_nTrack", &OFFTrackParticle_nTrack, &b_OFFTrackParticle_nTrack);
    fChainOFFTrack->SetBranchAddress("OFFTrackParticle_slice", &OFFTrackParticle_slice, &b_OFFTrackParticle_slice);
    fChainOFFTrack->SetBranchAddress("OFFTrackParticle_pt", &OFFTrackParticle_pt, &b_OFFTrackParticle_pt);
    fChainOFFTrack->SetBranchAddress("OFFTrackParticle_phi", &OFFTrackParticle_phi, &b_OFFTrackParticle_phi);
    fChainOFFTrack->SetBranchAddress("OFFTrackParticle_eta", &OFFTrackParticle_eta, &b_OFFTrackParticle_eta);
    fChainOFFTrack->SetBranchAddress("OFFTrackParticle_charge", &OFFTrackParticle_charge, &b_OFFTrackParticle_charge);
    fChainOFFTrack->SetBranchAddress("OFFTrackParticle_chi2", &OFFTrackParticle_chi2, &b_OFFTrackParticle_chi2);
    fChainOFFTrack->SetBranchAddress("OFFTrackParticle_BL_hits", &OFFTrackParticle_BL_hits, &b_OFFTrackParticle_BL_hits);
    fChainOFFTrack->SetBranchAddress("OFFTrackParticle_Pixel_hits", &OFFTrackParticle_Pixel_hits, &b_OFFTrackParticle_Pixel_hits);
    fChainOFFTrack->SetBranchAddress("OFFTrackParticle_SCT_hits", &OFFTrackParticle_SCT_hits, &b_OFFTrackParticle_SCT_hits);
    fChainOFFTrack->SetBranchAddress("OFFTrackParticle_TRT_hits", &OFFTrackParticle_TRT_hits, &b_OFFTrackParticle_TRT_hits);
    fChainOFFTrack->SetBranchAddress("OFFTrackParticle_TRT_out", &OFFTrackParticle_TRT_out, &b_OFFTrackParticle_TRT_out);
    fChainOFFTrack->SetBranchAddress("OFFTrackParticle_TRT_tubeHits", &OFFTrackParticle_TRT_tubeHits, &b_OFFTrackParticle_TRT_tubeHits);
    fChainOFFTrack->SetBranchAddress("OFFTrackParticle_TRT_highHits", &OFFTrackParticle_TRT_highHits, &b_OFFTrackParticle_TRT_highHits);
    fChainOFFTrack->SetBranchAddress("OFFTrackParticle_TRT_highOut", &OFFTrackParticle_TRT_highOut, &b_OFFTrackParticle_TRT_highOut);
    fChainOFFTrack->SetBranchAddress("OFFTrackParticle_eProb", &OFFTrackParticle_eProb, &b_OFFTrackParticle_eProb);
    fChainOFFTrack->SetBranchAddress("OFFTrackParticle_a0", &OFFTrackParticle_a0, &b_OFFTrackParticle_a0);
    fChainOFFTrack->SetBranchAddress("OFFTrackParticle_z0", &OFFTrackParticle_z0, &b_OFFTrackParticle_z0);
    fChainOFFTrack->SetBranchAddress("OFFTrackParticle_phi0", &OFFTrackParticle_phi0, &b_OFFTrackParticle_phi0);
    fChainOFFTrack->SetBranchAddress("OFFTrackParticle_eOVERt", &OFFTrackParticle_eOVERt, &b_OFFTrackParticle_eOVERt);
    fChainOFFTrack->SetBranchAddress("OFFTrackParticle_trigChain", &OFFTrackParticle_trigChain, &b_OFFTrackParticle_trigChain);
    fChainOFFTrack->SetBranchAddress("OFFTrackParticle_trigDec", &OFFTrackParticle_trigDec, &b_OFFTrackParticle_trigDec);
  }

  if (hasOFFegamma) {
    fChainOFFegamma->SetBranchAddress("OFFegamma_nEGamma", &OFFegamma_nEGamma, &b_OFFegamma_nEGamma);
    fChainOFFegamma->SetBranchAddress("OFFegamma_e", &OFFegamma_e, &b_OFFegamma_e);
    fChainOFFegamma->SetBranchAddress("OFFegamma_et", &OFFegamma_et, &b_OFFegamma_et);
    fChainOFFegamma->SetBranchAddress("OFFegamma_pt", &OFFegamma_pt, &b_OFFegamma_pt);
    fChainOFFegamma->SetBranchAddress("OFFegamma_phi", &OFFegamma_phi, &b_OFFegamma_phi);
    fChainOFFegamma->SetBranchAddress("OFFegamma_eta", &OFFegamma_eta, &b_OFFegamma_eta);
    fChainOFFegamma->SetBranchAddress("OFFegamma_m", &OFFegamma_m, &b_OFFegamma_m);
    fChainOFFegamma->SetBranchAddress("OFFegamma_PID", &OFFegamma_PID, &b_OFFegamma_PID);
    fChainOFFegamma->SetBranchAddress("OFFegamma_author", &OFFegamma_author, &b_OFFegamma_author);
    fChainOFFegamma->SetBranchAddress("OFFegamma_isem", &OFFegamma_isem, &b_OFFegamma_isem);
    fChainOFFegamma->SetBranchAddress("OFFegamma_isemse", &OFFegamma_isemse, &b_OFFegamma_isemse);
    fChainOFFegamma->SetBranchAddress("OFFegamma_isLoose" , &OFFegamma_isLoose , &b_OFFegamma_isLoose);
    fChainOFFegamma->SetBranchAddress("OFFegamma_isMedium", &OFFegamma_isMedium, &b_OFFegamma_isMedium);
    fChainOFFegamma->SetBranchAddress("OFFegamma_isTight" , &OFFegamma_isTight , &b_OFFegamma_isTight);
    fChainOFFegamma->SetBranchAddress("OFFegamma_TrackIndex", &OFFegamma_TrackIndex, &b_OFFegamma_TrackIndex);
    fChainOFFegamma->SetBranchAddress("OFFegamma_ClusIndex", &OFFegamma_ClusIndex, &b_OFFegamma_ClusIndex);
    fChainOFFegamma->SetBranchAddress("OFFegamma_etaBE2", &OFFegamma_etaBE2, &b_OFFegamma_etaBE2);
    fChainOFFegamma->SetBranchAddress("OFFegamma_charge", &OFFegamma_charge, &b_OFFegamma_charge);
    fChainOFFegamma->SetBranchAddress("OFFegamma_Eclu", &OFFegamma_Eclu, &b_OFFegamma_Eclu);
    fChainOFFegamma->SetBranchAddress("OFFegamma_e233", &OFFegamma_e233, &b_OFFegamma_e233);
    fChainOFFegamma->SetBranchAddress("OFFegamma_e237", &OFFegamma_e237, &b_OFFegamma_e237);
    fChainOFFegamma->SetBranchAddress("OFFegamma_e277", &OFFegamma_e277, &b_OFFegamma_e277);
    fChainOFFegamma->SetBranchAddress("OFFegamma_ethad", &OFFegamma_ethad, &b_OFFegamma_ethad);
    fChainOFFegamma->SetBranchAddress("OFFegamma_ethad1", &OFFegamma_ethad1, &b_OFFegamma_ethad1);
    fChainOFFegamma->SetBranchAddress("OFFegamma_weta1", &OFFegamma_weta1, &b_OFFegamma_weta1);
    fChainOFFegamma->SetBranchAddress("OFFegamma_weta2", &OFFegamma_weta2, &b_OFFegamma_weta2);
    fChainOFFegamma->SetBranchAddress("OFFegamma_f1", &OFFegamma_f1, &b_OFFegamma_f1);
    fChainOFFegamma->SetBranchAddress("OFFegamma_e2tsts1", &OFFegamma_e2tsts1, &b_OFFegamma_e2tsts1);
    fChainOFFegamma->SetBranchAddress("OFFegamma_emaxs1", &OFFegamma_emaxs1, &b_OFFegamma_emaxs1);
    fChainOFFegamma->SetBranchAddress("OFFegamma_emins1", &OFFegamma_emins1, &b_OFFegamma_emins1);
    fChainOFFegamma->SetBranchAddress("OFFegamma_wtots1", &OFFegamma_wtots1, &b_OFFegamma_wtots1);
    fChainOFFegamma->SetBranchAddress("OFFegamma_fracs1", &OFFegamma_fracs1, &b_OFFegamma_fracs1);
    fChainOFFegamma->SetBranchAddress("OFFegamma_etcone20", &OFFegamma_etcone20, &b_OFFegamma_etcone20);
    fChainOFFegamma->SetBranchAddress("OFFegamma_dEta", &OFFegamma_dEta, &b_OFFegamma_dEta);
    fChainOFFegamma->SetBranchAddress("OFFegamma_dPhi", &OFFegamma_dPhi, &b_OFFegamma_dPhi);
    fChainOFFegamma->SetBranchAddress("OFFegamma_eOVERp", &OFFegamma_eOVERp, &b_OFFegamma_eOVERp);
    fChainOFFegamma->SetBranchAddress("OFFegamma_nBL", &OFFegamma_nBL, &b_OFFegamma_nBL);
    fChainOFFegamma->SetBranchAddress("OFFegamma_nPix", &OFFegamma_nPix, &b_OFFegamma_nPix);
    fChainOFFegamma->SetBranchAddress("OFFegamma_nSCT", &OFFegamma_nSCT, &b_OFFegamma_nSCT);
    fChainOFFegamma->SetBranchAddress("OFFegamma_nTRThigh", &OFFegamma_nTRThigh, &b_OFFegamma_nTRThigh);
    fChainOFFegamma->SetBranchAddress("OFFegamma_nTRThighOut", &OFFegamma_nTRThighOut, &b_OFFegamma_nTRThighOut);
    fChainOFFegamma->SetBranchAddress("OFFegamma_nTRT", &OFFegamma_nTRT, &b_OFFegamma_nTRT);
    fChainOFFegamma->SetBranchAddress("OFFegamma_nTRTOut", &OFFegamma_nTRTOut, &b_OFFegamma_nTRTOut);
    fChainOFFegamma->SetBranchAddress("OFFegamma_trkPt", &OFFegamma_trkPt, &b_OFFegamma_trkPt);
    fChainOFFegamma->SetBranchAddress("OFFegamma_trkCosTh", &OFFegamma_trkCosTh, &b_OFFegamma_trkCosTh);
    fChainOFFegamma->SetBranchAddress("OFFegamma_trkSinTh", &OFFegamma_trkSinTh, &b_OFFegamma_trkSinTh);
    fChainOFFegamma->SetBranchAddress("OFFegamma_trkD0", &OFFegamma_trkD0, &b_OFFegamma_trkD0);
    fChainOFFegamma->SetBranchAddress("OFFegamma_MCtype", &OFFegamma_MCtype, &b_OFFegamma_MCtype);
    fChainOFFegamma->SetBranchAddress("OFFegamma_MCorig", &OFFegamma_MCorig, &b_OFFegamma_MCorig);
    fChainOFFegamma->SetBranchAddress("OFFegamma_MCorigMother", &OFFegamma_MCorigMother, &b_OFFegamma_MCorigMother);
    fChainOFFegamma->SetBranchAddress("OFFegamma_isElectron", &OFFegamma_isElectron, &b_OFFegamma_isElectron);
    fChainOFFegamma->SetBranchAddress("OFFegamma_isPhoton", &OFFegamma_isPhoton, &b_OFFegamma_isPhoton);
    fChainOFFegamma->SetBranchAddress("OFFegamma_trigChain", &OFFegamma_trigChain, &b_OFFegamma_trigChain);
    fChainOFFegamma->SetBranchAddress("OFFegamma_trigDec", &OFFegamma_trigDec, &b_OFFegamma_trigDec);
  }

}

void TrigEgammaNtuple_v2::FillTriggerMap(vector<vector<string> >* names,  vector<vector<int> >* dec,vector<map<string,bool> >& omap) {
  omap.clear();
  if (names!=0) {
    // std::cout << (*L1ROI_trigDec).size() << std::endl;
    for(unsigned int i=0;i<(*names).size();i++) {
      map<string,bool> tempMap;
      for (unsigned int j=0;j<(*names)[i].size();j++) {
	if ( (*dec)[i][j]==0) 
	  tempMap[(*names)[i][j]]=false;
	else 
	  tempMap[(*names)[i][j]]=true;
      }
      omap.push_back(tempMap); 
    }
  }
}

/// Tells you wheter the event passed a particular trigger: need to pass map of the selected trigger level ....
bool TrigEgammaNtuple_v2::EventPassedTrig(string trig) {
  //can be doen in a more clever way ....
  
  if ( trig.find("L1_")!=string::npos ) {
    if ( trig!=thisTriggerL1 ) {
      thisTriggerL1=trig;
      for ( unsigned int i=0;i<Trigger_L1ChainName->size();i++) {
	if ( thisTriggerL1==Trigger_L1ChainName->at(i) ) {
	  thisIndexL1=i;
	  break;
	}
      }
    } 
    return Trigger_L1passed->at(thisIndexL1);
  }
  if ( trig.find("L2_")!=string::npos ) {
    if ( trig!=thisTriggerL2 ) {
      thisTriggerL2=trig;
      for ( unsigned int i=0;i<Trigger_L2ChainName->size();i++) {
	if ( thisTriggerL2==Trigger_L2ChainName->at(i) ) {
	  thisIndexL2=i;
	  break;
	}
      }
    } 
    return Trigger_L2passed->at(thisIndexL2);
  }
  if ( trig.find("EF_")!=string::npos ) {
    if ( trig!=thisTriggerEF ) {
      thisTriggerEF=trig;
      for ( unsigned int i=0;i<Trigger_EFChainName->size();i++) {
	if ( thisTriggerEF==Trigger_EFChainName->at(i) ) {
	  thisIndexEF=i;
	  break;
	}
      }
    } 
    return Trigger_EFpassed->at(thisIndexEF);
  }
  return false;
}

/// Tells you wheter the event passed a particular trigger: need to pass map of the selected trigger level ....
bool TrigEgammaNtuple_v2::EventPassedTrig_PT(string trig) {
  //can be doen in a more clever way ....
  if ( trig.find("L1_")!=string::npos ) {
    if ( trig!=thisTriggerL1 ) {
      thisTriggerL1=trig;
      for ( unsigned int i=0;i<Trigger_L1ChainName->size();i++) {
	if ( thisTriggerL1==Trigger_L1ChainName->at(i) ) {
	  thisIndexL1=i;
	  break;
	}
      }
    } 
    return Trigger_L1passed_PT->at(thisIndexL1);
  }
  if ( trig.find("L2_")!=string::npos ) {
    if ( trig!=thisTriggerL2 ) {
      thisTriggerL2=trig;
      for ( unsigned int i=0;i<Trigger_L2ChainName->size();i++) {
	if ( thisTriggerL2==Trigger_L2ChainName->at(i) ) {
	  thisIndexL2=i;
	  break;
	}
      }
    } 
    return Trigger_L2passed_PT->at(thisIndexL2);
  }
  if ( trig.find("EF_")!=string::npos ) {
    if ( trig!=thisTriggerEF ) {
      thisTriggerEF=trig;
      for ( unsigned int i=0;i<Trigger_EFChainName->size();i++) {
	if ( thisTriggerEF==Trigger_EFChainName->at(i) ) {
	  thisIndexEF=i;
	  break;
	}
      }
    } 
    return Trigger_EFpassed_PT->at(thisIndexEF);
  }
  return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TrigEgammaNtuple_v2::GetPrescaled(string trig) {
  //can be doen in a more clever way ....
  if ( trig.find("L1_")!=string::npos ) {
    if ( trig!=thisTriggerL1 ) {
      thisTriggerL1=trig;
      for ( unsigned int i=0;i<Trigger_L1ChainName->size();i++) {
	if ( thisTriggerL1==Trigger_L1ChainName->at(i) ) {
	  thisIndexL1=i;
	  break;
	}
      }
    } 
    return Trigger_L1prescale->at(thisIndexL1);
  }

  if ( trig.find("L2_")!=string::npos ) {
    if ( trig!=thisTriggerL2 ) {
      thisTriggerL2=trig;
      for ( unsigned int i=0;i<Trigger_L2ChainName->size();i++) {
	if ( thisTriggerL2==Trigger_L2ChainName->at(i) ) {
	  thisIndexL2=i;
	  break;
	}
      }
    } 
    return Trigger_L2prescale->at(thisIndexL2);
  }
  
  if ( trig.find("EF_")!=string::npos ) {
    if ( trig!=thisTriggerEF ) {
      thisTriggerEF=trig;
      for ( unsigned int i=0;i<Trigger_EFChainName->size();i++) {
	if ( thisTriggerEF==Trigger_EFChainName->at(i) ) {
	  thisIndexEF=i;
	  break;
	}
      }
    } 
    return Trigger_EFprescale->at(thisIndexEF);
  }
  return -666;
}


/// Tells you wheter the object was analyzed in the particular trigger: need to pass the map for the object  
bool TrigEgammaNtuple_v2::ObjInTrigger(map<string,bool> list, std::string trig) {
  std::map<string,bool>::iterator it=list.find(trig);
  if (it!=list.end()) {
    return true;
  }
  return false;
}

/// Tells you wheter the object passd in the particular trigger: need to pass the map for the object  
bool TrigEgammaNtuple_v2::ObjPassedTrigger(map<string,bool> list, std::string trig) {
  std::map<string,bool>::iterator it=list.find(trig);
  if (it!=list.end()) {
    if (it->second) return true;
  }
  return false;
}


#endif 
