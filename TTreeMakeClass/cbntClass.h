//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Nov 12 16:53:46 2008 by ROOT version 5.18/00a
// from TTree CollectionTree/CollectionTree
// found on file: /dataDisk/RunNumber/0093945/oneCBNT.root
//////////////////////////////////////////////////////////

#ifndef cbntClass_h
#define cbntClass_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#define L1CALO_ONLY
//#define PPM_ONLY

using namespace std;

class cbntClass {
public :
   TChain          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           RunNumber;
   Int_t           EventNumber;
#ifndef L1CALO_ONLY
   Char_t          StreamESD_ref;
#endif
   Char_t          Token[93];
   Int_t           Run;
   Int_t           Event;
   Int_t           Time;
   Int_t           LumiBlock;
   Int_t           BCID;
   Int_t           LVL1ID;
   Double_t        Weight;
   Int_t           IEvent;
   Int_t           StatusElement;
   Int_t           LVL1TriggerType;
   vector<long>    *LVL1TriggerInfo;
   vector<long>    *LVL2TriggerInfo;
   vector<long>    *EventFilterInfo;
   vector<string>  *StreamTagName;
   vector<string>  *StreamTagType;

#ifndef L1CALO_ONLY
   Int_t           pixel_nhits;
   vector<int>     *pixel_bec;
   vector<int>     *pixel_layer;
   vector<int>     *pixel_eta;
   vector<int>     *pixel_phi;
   vector<int>     *pixel_row;
   vector<int>     *pixel_col;
   vector<int>     *pixel_tot;
   vector<int>     *pixel_BCID;
   vector<int>     *pixel_LVL1;
   Int_t           sct_rdo_nhits;
   vector<int>     *sct_rdo_strips;
   vector<int>     *sct_rdo_tbin;
   vector<int>     *sct_rdo_rdoId;
   vector<int>     *sct_rdo_bec;
   vector<int>     *sct_rdo_layer;
   vector<int>     *sct_rdo_eta;
   vector<int>     *sct_rdo_phi;
   vector<int>     *sct_rdo_side;
   vector<int>     *sct_rdo_FirstSecondHitError;
   Int_t           tdc_ntdcs;
   vector<int>     *tdc_channel;
   vector<float>   *tdc_phase;
   Int_t           sct_bsErr_nErrs;
   vector<int>     *sct_bsErr_type;
   vector<int>     *sct_bsErr_eta;
   vector<int>     *sct_bsErr_phi;
   vector<int>     *sct_bsErr_layer;
   vector<int>     *sct_bsErr_side;
   vector<int>     *sct_bsErr_bec;
   Int_t           sct_clus_nclusters;
   vector<float>   *sct_clus_x;
   vector<float>   *sct_clus_y;
   vector<float>   *sct_clus_z;
   vector<int>     *sct_clus_groupsize;
   vector<int>     *sct_clus_bec;
   vector<int>     *sct_clus_layer;
   vector<int>     *sct_clus_eta;
   vector<int>     *sct_clus_phi;
   vector<int>     *sct_clus_side;
   Int_t           pixel_clus_nclusters;
   vector<float>   *pixel_clus_LocX;
   vector<float>   *pixel_clus_LocY;
   vector<float>   *pixel_clus_z;
   vector<int>     *pixel_clus_groupsize;
   vector<int>     *pixel_clus_bec;
   vector<int>     *pixel_clus_layer;
   vector<int>     *pixel_clus_phi;
   vector<float>   *pixel_clus_clx;
   vector<float>   *pixel_clus_cly;
   vector<float>   *pixel_clus_clz;
   vector<vector<int> > *pixel_clus_row;
   vector<vector<int> > *pixel_clus_col;
   Int_t           sct_sp_nspacepoints;
   vector<float>   *sct_sp_x;
   vector<float>   *sct_sp_y;
   vector<float>   *sct_sp_z;
   vector<int>     *sct_sp_barrelendcap;
   vector<int>     *sct_sp_layer;
   vector<int>     *sct_sp_phi;
   vector<int>     *sct_sp_eta;
   Int_t           pixel_sp_nspacepoints;
   vector<float>   *pixel_sp_x;
   vector<float>   *pixel_sp_y;
   vector<float>   *pixel_sp_z;
   vector<int>     *pixel_sp_barrelendcap;
   vector<int>     *pixel_sp_layer;
   vector<int>     *pixel_sp_phi;
   vector<int>     *pixel_sp_eta;
   Int_t           trk_nTracks;
   vector<int>     *trk_nPixelHits;
   vector<int>     *trk_nSctHits;
   vector<int>     *trk_nTrtHits;
   vector<vector<float> > *trk_PixResPhi;
   vector<vector<float> > *trk_PixResEta;
   vector<vector<float> > *trk_PixPullPhi;
   vector<vector<float> > *trk_PixPullEta;
   vector<vector<float> > *trk_PixErrTrkPhi;
   vector<vector<float> > *trk_PixErrTrkEta;
   vector<vector<float> > *trk_PixErrHitPhi;
   vector<vector<float> > *trk_PixErrHitEta;
   vector<vector<int> > *trk_Pix_bec;
   vector<vector<int> > *trk_Pix_layer;
   vector<vector<int> > *trk_Pix_eta;
   vector<vector<int> > *trk_Pix_phi;
   vector<vector<int> > *trk_Pix_clusWidthRow;
   vector<vector<int> > *trk_Pix_clusWidthCol;
   vector<vector<float> > *trk_Pix_LocX;
   vector<vector<float> > *trk_Pix_LocY;
   vector<vector<float> > *trk_SctRes;
   vector<vector<float> > *trk_SctPull;
   vector<vector<float> > *trk_SctErrTrk;
   vector<vector<float> > *trk_SctErrHit;
   vector<vector<int> > *trk_Sct_bec;
   vector<vector<int> > *trk_Sct_layer;
   vector<vector<int> > *trk_Sct_eta;
   vector<vector<int> > *trk_Sct_phi;
   vector<vector<int> > *trk_Sct_side;
   vector<vector<int> > *trk_Sct_rdoId;
   vector<vector<int> > *trk_Sct_clusGroupsize;
   vector<vector<float> > *trk_Sct_clusx;
   vector<vector<float> > *trk_Sct_clusy;
   vector<vector<float> > *trk_Sct_clusz;
   vector<vector<float> > *trk_TrtRes;
   vector<vector<float> > *trk_TrtPull;
   vector<vector<float> > *trk_TrtErrTrk;
   vector<vector<float> > *trk_TrtErrHit;
   vector<vector<float> > *trk_Trt_R;
   vector<vector<float> > *trk_Trt_Rtrack;
   vector<vector<float> > *trk_Trt_t;
   vector<vector<float> > *trk_Trt_x;
   vector<vector<float> > *trk_Trt_y;
   vector<vector<int> > *trk_Trt_HL;
   vector<vector<int> > *trk_Trt_strawlayer;
   vector<vector<int> > *trk_Trt_bec;
   vector<vector<int> > *trk_Trt_layer;
   vector<vector<int> > *trk_Trt_straw;
   vector<vector<int> > *trk_Trt_phisector;
   vector<float>   *trk_Rec_d0;
   vector<float>   *trk_Rec_z0;
   vector<float>   *trk_Rec_phi0;
   vector<float>   *trk_Rec_theta0;
   vector<float>   *trk_Rec_qoverp;
   vector<float>   *trk_Rec_chi2;
   vector<int>     *trk_Rec_ndof;
   vector<float>   *trk_Rec_eta;
   vector<float>   *trk_Rec_error_d0;
   vector<float>   *trk_Rec_error_z0;
   vector<float>   *trk_Rec_error_phi0;
   vector<float>   *trk_Rec_error_theta0;
   vector<float>   *trk_Rec_error_qoverp;
   vector<float>   *trk_Rec_chi2prob;
   vector<int>     *trk_Rec_author;
   Int_t           Nh_Calo;
   Float_t         Eh_Calo;
   Int_t           Nh_EM;
   Float_t         Eh_EM;
   Int_t           Nh_HAD;
   Float_t         Eh_HAD;
   Int_t           Nh_PresB;
   vector<float>   *Eh_PresB;
   Int_t           Nh_EMB;
   vector<float>   *Eh_EMB;
   Int_t           Nh_EMEC;
   vector<float>   *Eh_EMEC;
   Int_t           Nh_Tile;
   vector<float>   *Eh_Tile;
   Int_t           Nh_TileGap;
   vector<float>   *Eh_TileGap;
   Int_t           Nh_HEC;
   vector<float>   *Eh_HEC;
   Int_t           Nh_FCal;
   vector<float>   *Eh_FCal;
   Int_t           Nh_PresE;
   vector<float>   *Eh_PresE;
   Int_t           Nh_Scint;
   vector<float>   *Eh_Scint;
   Int_t           nhitLAr;
   Float_t         ecellLAr;
   Int_t           NCellsLAr;
   vector<float>   *ECellsLAr;
   vector<float>   *EtaCellsLAr;
   vector<float>   *PhiCellsLAr;
   vector<float>   *QCellsLAr;
   vector<long>    *GainCellsLAr;
   vector<long>    *DetCellsLAr;
   vector<float>   *TimeCellsLAr;
   vector<long>    *BadCellsLAr;
   vector<unsigned long> *IdCellsLAr;
   Int_t           LArDigit_icell;
   vector<long>    *LArDigit_layer;
   vector<long>    *LArDigit_ieta;
   vector<long>    *LArDigit_calo;
   vector<long>    *LArDigit_iphi;
   vector<long>    *LArDigit_barrel_ec;
   vector<long>    *LArDigit_pos_neg;
   vector<long>    *LArDigit_FT;
   vector<long>    *LArDigit_slot;
   vector<long>    *LArDigit_channel;
   vector<long>    *LArDigit_gain;
   Int_t           LArDigit_NSamples;
   vector<vector<long> > *LArDigit_Samples;
   vector<unsigned long> *LArDigit_offlineId;
   Float_t         TileCellETot;
   Float_t         TileMBTSETot;
   Float_t         TileMBTSETotA;
   Float_t         TileMBTSETotC;
   Int_t           TileCellN;
   vector<float>   *TileCellE;
   vector<float>   *TileCellTime;
   vector<float>   *TileCellEta;
   vector<float>   *TileCellPhi;
   vector<long>    *TileMBTSCounter;
   vector<float>   *TileMBTSE;
   vector<float>   *TileMBTSTime;
   vector<float>   *TileMBTSQuality;
   vector<float>   *TileMBTSEta;
   vector<float>   *TileMBTSPhi;
   vector<float>   *TileCellX;
   vector<float>   *TileCellY;
   vector<float>   *TileCellZ;
   vector<float>   *TileMBTSX;
   vector<float>   *TileMBTSY;
   vector<float>   *TileMBTSZ;
   vector<float>   *TileCellEdiff;
   vector<float>   *TileCellTimediff;
   vector<long>    *TileCellGain1;
   vector<long>    *TileCellGain2;
   vector<long>    *TileCellModule;
   vector<long>    *TileCellPartition;
   vector<long>    *TileCellTower;
   vector<long>    *TileCellSample;
   vector<long>    *TileCellChan1;
   vector<long>    *TileCellChan2;
   vector<long>    *TileCellPMT1;
   vector<long>    *TileCellPMT2;
   vector<unsigned int> *TileCellStatus1;
   vector<unsigned int> *TileCellStatus2;
   vector<long>    *TileMBTSModule;
   vector<long>    *TileMBTSGain;
   vector<unsigned int> *TileMBTSStatus;
   Float_t         cl_ecluster;
   Int_t           cl_nctotal;
   Int_t           cl_nc;
   vector<float>   *cl_et;
   vector<float>   *cl_e;
   vector<float>   *cl_eemb0;
   vector<float>   *cl_eemb1;
   vector<float>   *cl_eemb2;
   vector<float>   *cl_eemb3;
   vector<long>    *cl_nemb0;
   vector<long>    *cl_nemb1;
   vector<long>    *cl_nemb2;
   vector<long>    *cl_nemb3;
   vector<float>   *cl_phi2;
   vector<float>   *cl_eta0;
   vector<float>   *cl_eta1;
   vector<float>   *cl_eta2;
   vector<float>   *cl_eta3;
   vector<float>   *cl_eeme0;
   vector<float>   *cl_eeme1;
   vector<float>   *cl_eeme2;
   vector<float>   *cl_eeme3;
   vector<long>    *cl_neme0;
   vector<long>    *cl_neme1;
   vector<long>    *cl_neme2;
   vector<long>    *cl_neme3;
   vector<float>   *cl_etileg1;
   vector<float>   *cl_etileg2;
   vector<float>   *cl_etileg3;
   vector<long>    *cl_ntileg1;
   vector<long>    *cl_ntileg2;
   vector<long>    *cl_ntileg3;
   vector<float>   *cl_eta;
   vector<float>   *cl_phi;
   vector<long>    *cl_reco_stat;
   vector<float>   *cl_m1_eta;
   vector<float>   *cl_m1_phi;
   vector<float>   *cl_m2_r;
   vector<float>   *cl_m2_lambda;
   vector<float>   *cl_delta_phi;
   vector<float>   *cl_delta_theta;
   vector<float>   *cl_delta_alpha;
   vector<float>   *cl_center_x;
   vector<float>   *cl_center_y;
   vector<float>   *cl_center_z;
   vector<float>   *cl_center_lambda;
   vector<float>   *cl_lateral;
   vector<float>   *cl_longitudinal;
   vector<float>   *cl_eng_frac_em;
   vector<float>   *cl_eng_frac_max;
   vector<float>   *cl_eng_frac_core;
   vector<float>   *cl_m1_dens;
   vector<float>   *cl_m2_dens;
   vector<float>   *cl_isol;
   vector<long>    *cl_ntotcells;
   Float_t         cl_ecluster_topo;
   Int_t           cl_nctotal_topo;
   Int_t           cl_nc_topo;
   vector<float>   *cl_et_topo;
   vector<float>   *cl_e_topo;
   vector<float>   *cl_eemb0_topo;
   vector<float>   *cl_eemb1_topo;
   vector<float>   *cl_eemb2_topo;
   vector<float>   *cl_eemb3_topo;
   vector<long>    *cl_nemb0_topo;
   vector<long>    *cl_nemb1_topo;
   vector<long>    *cl_nemb2_topo;
   vector<long>    *cl_nemb3_topo;
   vector<float>   *cl_phi2_topo;
   vector<float>   *cl_eta0_topo;
   vector<float>   *cl_eta1_topo;
   vector<float>   *cl_eta2_topo;
   vector<float>   *cl_eta3_topo;
   vector<float>   *cl_eeme0_topo;
   vector<float>   *cl_eeme1_topo;
   vector<float>   *cl_eeme2_topo;
   vector<float>   *cl_eeme3_topo;
   vector<long>    *cl_neme0_topo;
   vector<long>    *cl_neme1_topo;
   vector<long>    *cl_neme2_topo;
   vector<long>    *cl_neme3_topo;
   vector<float>   *cl_etileg1_topo;
   vector<float>   *cl_etileg2_topo;
   vector<float>   *cl_etileg3_topo;
   vector<long>    *cl_ntileg1_topo;
   vector<long>    *cl_ntileg2_topo;
   vector<long>    *cl_ntileg3_topo;
   vector<float>   *cl_eta_topo;
   vector<float>   *cl_phi_topo;
   vector<long>    *cl_reco_stat_topo;
   vector<float>   *cl_m1_eta_topo;
   vector<float>   *cl_m1_phi_topo;
   vector<float>   *cl_m2_r_topo;
   vector<float>   *cl_m2_lambda_topo;
   vector<float>   *cl_delta_phi_topo;
   vector<float>   *cl_delta_theta_topo;
   vector<float>   *cl_delta_alpha_topo;
   vector<float>   *cl_center_x_topo;
   vector<float>   *cl_center_y_topo;
   vector<float>   *cl_center_z_topo;
   vector<float>   *cl_center_lambda_topo;
   vector<float>   *cl_lateral_topo;
   vector<float>   *cl_longitudinal_topo;
   vector<float>   *cl_eng_frac_em_topo;
   vector<float>   *cl_eng_frac_max_topo;
   vector<float>   *cl_eng_frac_core_topo;
   vector<float>   *cl_m1_dens_topo;
   vector<float>   *cl_m2_dens_topo;
   vector<float>   *cl_isol_topo;
   vector<float>   *cl_ehec0_topo;
   vector<float>   *cl_ehec1_topo;
   vector<float>   *cl_ehec2_topo;
   vector<float>   *cl_ehec3_topo;
   vector<long>    *cl_nhec0_topo;
   vector<long>    *cl_nhec1_topo;
   vector<long>    *cl_nhec2_topo;
   vector<long>    *cl_nhec3_topo;
   vector<float>   *cl_etileb0_topo;
   vector<float>   *cl_etileb1_topo;
   vector<float>   *cl_etileb2_topo;
   vector<long>    *cl_ntileb0_topo;
   vector<long>    *cl_ntileb1_topo;
   vector<long>    *cl_ntileb2_topo;
   vector<float>   *cl_etilee0_topo;
   vector<float>   *cl_etilee1_topo;
   vector<float>   *cl_etilee2_topo;
   vector<float>   *cl_efcal0_topo;
   vector<float>   *cl_efcal1_topo;
   vector<float>   *cl_efcal2_topo;
   vector<long>    *cl_ntilee0_topo;
   vector<long>    *cl_ntilee1_topo;
   vector<long>    *cl_ntilee2_topo;
   vector<long>    *cl_nfcal0_topo;
   vector<long>    *cl_nfcal1_topo;
   vector<long>    *cl_nfcal2_topo;
   vector<long>    *cl_ntotcells_topo;
   Float_t         cl_ecluster_topoEM430;
   Int_t           cl_nctotal_topoEM430;
   Int_t           cl_nc_topoEM430;
   vector<float>   *cl_et_topoEM430;
   vector<float>   *cl_e_topoEM430;
   vector<float>   *cl_eemb0_topoEM430;
   vector<float>   *cl_eemb1_topoEM430;
   vector<float>   *cl_eemb2_topoEM430;
   vector<float>   *cl_eemb3_topoEM430;
   vector<long>    *cl_nemb0_topoEM430;
   vector<long>    *cl_nemb1_topoEM430;
   vector<long>    *cl_nemb2_topoEM430;
   vector<long>    *cl_nemb3_topoEM430;
   vector<float>   *cl_phi2_topoEM430;
   vector<float>   *cl_eta0_topoEM430;
   vector<float>   *cl_eta1_topoEM430;
   vector<float>   *cl_eta2_topoEM430;
   vector<float>   *cl_eta3_topoEM430;
   vector<float>   *cl_eeme0_topoEM430;
   vector<float>   *cl_eeme1_topoEM430;
   vector<float>   *cl_eeme2_topoEM430;
   vector<float>   *cl_eeme3_topoEM430;
   vector<long>    *cl_neme0_topoEM430;
   vector<long>    *cl_neme1_topoEM430;
   vector<long>    *cl_neme2_topoEM430;
   vector<long>    *cl_neme3_topoEM430;
   vector<float>   *cl_etileg1_topoEM430;
   vector<float>   *cl_etileg2_topoEM430;
   vector<float>   *cl_etileg3_topoEM430;
   vector<long>    *cl_ntileg1_topoEM430;
   vector<long>    *cl_ntileg2_topoEM430;
   vector<long>    *cl_ntileg3_topoEM430;
   vector<float>   *cl_eta_topoEM430;
   vector<float>   *cl_phi_topoEM430;
   vector<long>    *cl_reco_stat_topoEM430;
   vector<float>   *cl_m1_eta_topoEM430;
   vector<float>   *cl_m1_phi_topoEM430;
   vector<float>   *cl_m2_r_topoEM430;
   vector<float>   *cl_m2_lambda_topoEM430;
   vector<float>   *cl_delta_phi_topoEM430;
   vector<float>   *cl_delta_theta_topoEM430;
   vector<float>   *cl_delta_alpha_topoEM430;
   vector<float>   *cl_center_x_topoEM430;
   vector<float>   *cl_center_y_topoEM430;
   vector<float>   *cl_center_z_topoEM430;
   vector<float>   *cl_center_lambda_topoEM430;
   vector<float>   *cl_lateral_topoEM430;
   vector<float>   *cl_longitudinal_topoEM430;
   vector<float>   *cl_eng_frac_em_topoEM430;
   vector<float>   *cl_eng_frac_max_topoEM430;
   vector<float>   *cl_eng_frac_core_topoEM430;
   vector<float>   *cl_m1_dens_topoEM430;
   vector<float>   *cl_m2_dens_topoEM430;
   vector<float>   *cl_isol_topoEM430;
   vector<long>    *cl_ntotcells_topoEM430;
   Int_t           NTileMuonTag;
   vector<float>   *EtaTileMuonTag;
   vector<float>   *PhiTileMuonTag;
   vector<vector<float> > *EnergyVecTileMuonTag;
   vector<float>   *LabelTileMuonTag;
   Double_t        TileCosmicsHT_x;
   Double_t        TileCosmicsHT_y;
   Double_t        TileCosmicsHT_z;
   Double_t        TileCosmicsHT_phi;
   Double_t        TileCosmicsHT_theta;
   Double_t        TileCosmicsHT_time;
   Double_t        TileCosmicsHT_fitQuality;
   Int_t           TileCosmicsHT_fitNcells;
   Double_t        TileCosmicsHT_path;
   Double_t        TileCosmicsHT_energy;
   vector<double>  *TileCosmicsHT_pathTop;
   vector<double>  *TileCosmicsHT_pathBottom;
   vector<double>  *TileCosmicsHT_energyTop;
   vector<double>  *TileCosmicsHT_energyBottom;
   Int_t           TileCosmicsHT_trackNcells;
   vector<double>  *TileCosmicsHT_cellE;
   vector<double>  *TileCosmicsHT_cellT;
   vector<double>  *TileCosmicsHT_cellEta;
   vector<double>  *TileCosmicsHT_cellPhi;
   vector<double>  *TileCosmicsHT_cellSample;
   vector<double>  *TileCosmicsHT_cellEdiff;
   vector<double>  *TileCosmicsHT_cellTdiff;
   Int_t           NTileMuonRODTag;
   vector<float>   *EtaTileMuonRODTag;
   vector<float>   *PhiTileMuonRODTag;
   vector<vector<float> > *EnergyVecTileMuonRODTag;
   vector<unsigned int> *LabelTileMuonRODTag;
   Int_t           mdt_nprdcoll;
   Int_t           mdt_nprd;
   vector<int>     *mdt_tdc;
   vector<int>     *mdt_adc;
   vector<int>     *mdt_station;
   vector<int>     *mdt_eta;
   vector<int>     *mdt_phi;
   vector<int>     *mdt_multi;
   vector<int>     *mdt_layer;
   vector<int>     *mdt_wire;
   vector<int>     *mdt_nmaxtubes;
   vector<float>   *mdt_globPosX;
   vector<float>   *mdt_globPosY;
   vector<float>   *mdt_globPosZ;
   Int_t           mdt_ncsm;
   Int_t           mdt_namt;
   vector<int>     *mdt_subid;
   vector<int>     *mdt_rodid;
   vector<int>     *mdt_csmid;
   vector<int>     *mdt_tdcid;
   vector<int>     *mdt_chanid;
   vector<int>     *mdt_fine;
   vector<int>     *mdt_coarse;
   vector<int>     *mdt_width;
   Int_t           rpc_prd_ncoll;
   Int_t           rpc_nprd;
   vector<long>    *rpc_prd_station;
   vector<long>    *rpc_prd_eta;
   vector<long>    *rpc_prd_phi;
   vector<long>    *rpc_prd_doublr;
   vector<long>    *rpc_prd_doublz;
   vector<long>    *rpc_prd_doublphi;
   vector<long>    *rpc_prd_gasgap;
   vector<long>    *rpc_prd_measphi;
   vector<long>    *rpc_prd_strip;
   vector<float>   *rpc_prd_time;
   vector<float>   *rpc_prd_stripx;
   vector<float>   *rpc_prd_stripy;
   vector<float>   *rpc_prd_stripz;
   vector<float>   *rpc_prd_triggerInfo;
   vector<float>   *rpc_prd_ambigFlag;
   Int_t           rpc_nclus;
   vector<long>    *rpc_clus_station;
   vector<long>    *rpc_clus_eta;
   vector<long>    *rpc_clus_phi;
   vector<long>    *rpc_clus_doublr;
   vector<long>    *rpc_clus_doublz;
   vector<long>    *rpc_clus_doublphi;
   vector<long>    *rpc_clus_gasgap;
   vector<long>    *rpc_clus_measphi;
   vector<long>    *rpc_clus_size;
   vector<float>   *rpc_clus_time;
   vector<float>   *rpc_clus_posx;
   vector<float>   *rpc_clus_posy;
   vector<float>   *rpc_clus_posz;
   Int_t           rpc_npads;
   vector<int>     *rpc_pad_id;
   vector<int>     *rpc_pad_bcid;
   vector<int>     *rpc_pad_lvl1id;
   vector<int>     *rpc_pad_sectorid;
   vector<int>     *rpc_pad_status;
   vector<int>     *rpc_pad_error;
   Int_t           rpc_ncmas;
   Int_t           rpc_fchan;
   vector<int>     *rpc_sector;
   vector<int>     *rpc_padId;
   vector<int>     *rpc_status;
   vector<int>     *rpc_ercode;
   vector<int>     *rpc_cmaId;
   vector<int>     *rpc_fel1Id;
   vector<int>     *rpc_febcId;
   vector<int>     *rpc_crc;
   vector<int>     *rpc_bcId;
   vector<int>     *rpc_ticks;
   vector<int>     *rpc_ijk;
   vector<int>     *rpc_cmachan;
   vector<int>     *rpc_overlap;
   vector<int>     *rpc_threshold;
   Int_t           rpc_SL_nSectors;
   vector<int>     *rpc_SL_sectorId;
   vector<int>     *rpc_SL_bcid;
   vector<int>     *rpc_SL_lvl1id;
   Int_t           rpc_SLnTriggerHits;
   vector<int>     *rpc_SLhit_sector;
   vector<int>     *rpc_SLhit_rowinBcid;
   vector<int>     *rpc_SLhit_triggerBcid;
   vector<int>     *rpc_SLhit_padId;
   vector<int>     *rpc_SLhit_ptId;
   vector<int>     *rpc_SLhit_roi;
   vector<int>     *rpc_SLhit_outerPlane;
   vector<int>     *rpc_SLhit_overlapPhi;
   vector<int>     *rpc_SLhit_overlapEta;
   vector<int>     *tgc_bcTag;
   vector<int>     *tgc_cointrackletbcTag;
   vector<int>     *tgc_coinhighptbcTag;
   vector<int>     *tgc_coinslbcTag;
   vector<int>     *tgc_cointype;
   vector<int>     *tgc_cointype_Prev;
   vector<int>     *tgc_cointype_Next;
   Int_t           tgc_nprdcoll;
   Int_t           tgc_nprd;
   vector<int>     *tgc_station;
   vector<int>     *tgc_eta;
   vector<int>     *tgc_phi;
   vector<int>     *tgc_gasGap;
   vector<int>     *tgc_isStrip;
   vector<int>     *tgc_channel;
   vector<float>   *tgc_globPosX;
   vector<float>   *tgc_globPosY;
   vector<float>   *tgc_globPosZ;
   vector<float>   *tgc_shortWidth;
   vector<float>   *tgc_longWidth;
   vector<float>   *tgc_length;
   Int_t           tgc_ncoincoll;
   Int_t           tgc_ncointracklet;
   vector<float>   *tgc_cointrackletdelta;
   vector<float>   *tgc_cointrackletposx_in;
   vector<float>   *tgc_cointrackletposy_in;
   vector<float>   *tgc_cointrackletposz_in;
   vector<float>   *tgc_cointrackletposx_out;
   vector<float>   *tgc_cointrackletposy_out;
   vector<float>   *tgc_cointrackletposz_out;
   vector<int>     *tgc_cointrackletstrip;
   vector<int>     *tgc_cointrackletforward;
   vector<float>   *tgc_cointrackletwidthout;
   vector<float>   *tgc_cointrackletwidthin;
   vector<int>     *tgc_cointrackletstationeta;
   vector<int>     *tgc_cointrackletstationphi;
   vector<int>     *tgc_cointrackletsector;
   vector<int>     *tgc_cointracklettrackletid;
   Int_t           tgc_ncoinhighpt;
   vector<float>   *tgc_coinhighptdelta;
   vector<float>   *tgc_coinhighptposx_in;
   vector<float>   *tgc_coinhighptposy_in;
   vector<float>   *tgc_coinhighptposz_in;
   vector<float>   *tgc_coinhighptposx_out;
   vector<float>   *tgc_coinhighptposy_out;
   vector<float>   *tgc_coinhighptposz_out;
   vector<int>     *tgc_coinhighptstrip;
   vector<int>     *tgc_coinhighptforward;
   vector<float>   *tgc_coinhighptwidthout;
   vector<float>   *tgc_coinhighptwidthin;
   vector<int>     *tgc_coinhighptstationeta;
   vector<int>     *tgc_coinhighptstationphi;
   vector<int>     *tgc_coinhighptsector;
   vector<int>     *tgc_coinhighpttrackletid;
   Int_t           tgc_ncoinsl;
   vector<float>   *tgc_coinslptthresh;
   vector<float>   *tgc_coinslposx_out;
   vector<float>   *tgc_coinslposy_out;
   vector<float>   *tgc_coinslposz_out;
   vector<float>   *tgc_coinslroi;
   vector<float>   *tgc_coinslforward;
   vector<float>   *tgc_coinslwidthr;
   vector<float>   *tgc_coinslwidthphi;
   vector<int>     *tgc_coinslstationeta;
   vector<int>     *tgc_coinslstationphi;
   vector<int>     *tgc_coinslsector;
   vector<int>     *tgc_coinsltrackletid;
   vector<int>     *tgc_coinsltrackletidstrip;
   Int_t           tgc_nprdcoll_Prev;
   Int_t           tgc_nprd_Prev;
   vector<int>     *tgc_station_Prev;
   vector<int>     *tgc_eta_Prev;
   vector<int>     *tgc_phi_Prev;
   vector<int>     *tgc_gasGap_Prev;
   vector<int>     *tgc_isStrip_Prev;
   vector<int>     *tgc_channel_Prev;
   vector<float>   *tgc_globPosX_Prev;
   vector<float>   *tgc_globPosY_Prev;
   vector<float>   *tgc_globPosZ_Prev;
   vector<float>   *tgc_shortWidth_Prev;
   vector<float>   *tgc_longWidth_Prev;
   vector<float>   *tgc_length_Prev;
   Int_t           tgc_ncoincoll_Prev;
   Int_t           tgc_ncointracklet_Prev;
   vector<float>   *tgc_cointrackletdelta_Prev;
   vector<float>   *tgc_cointrackletposx_in_Prev;
   vector<float>   *tgc_cointrackletposy_in_Prev;
   vector<float>   *tgc_cointrackletposz_in_Prev;
   vector<float>   *tgc_cointrackletposx_out_Prev;
   vector<float>   *tgc_cointrackletposy_out_Prev;
   vector<float>   *tgc_cointrackletposz_out_Prev;
   vector<int>     *tgc_cointrackletstrip_Prev;
   vector<int>     *tgc_cointrackletforward_Prev;
   vector<float>   *tgc_cointrackletwidthout_Prev;
   vector<float>   *tgc_cointrackletwidthin_Prev;
   vector<int>     *tgc_cointrackletstationeta_Prev;
   vector<int>     *tgc_cointrackletstationphi_Prev;
   vector<int>     *tgc_cointrackletsector_Prev;
   vector<int>     *tgc_cointracklettrackletid_Prev;
   Int_t           tgc_ncoinhighpt_Prev;
   vector<float>   *tgc_coinhighptdelta_Prev;
   vector<float>   *tgc_coinhighptposx_in_Prev;
   vector<float>   *tgc_coinhighptposy_in_Prev;
   vector<float>   *tgc_coinhighptposz_in_Prev;
   vector<float>   *tgc_coinhighptposx_out_Prev;
   vector<float>   *tgc_coinhighptposy_out_Prev;
   vector<float>   *tgc_coinhighptposz_out_Prev;
   vector<int>     *tgc_coinhighptstrip_Prev;
   vector<int>     *tgc_coinhighptforward_Prev;
   vector<float>   *tgc_coinhighptwidthout_Prev;
   vector<float>   *tgc_coinhighptwidthin_Prev;
   vector<int>     *tgc_coinhighptstationeta_Prev;
   vector<int>     *tgc_coinhighptstationphi_Prev;
   vector<int>     *tgc_coinhighptsector_Prev;
   vector<int>     *tgc_coinhighpttrackletid_Prev;
   Int_t           tgc_ncoinsl_Prev;
   vector<float>   *tgc_coinslptthresh_Prev;
   vector<float>   *tgc_coinslposx_out_Prev;
   vector<float>   *tgc_coinslposy_out_Prev;
   vector<float>   *tgc_coinslposz_out_Prev;
   vector<float>   *tgc_coinslroi_Prev;
   vector<float>   *tgc_coinslforward_Prev;
   vector<float>   *tgc_coinslwidthr_Prev;
   vector<float>   *tgc_coinslwidthphi_Prev;
   vector<int>     *tgc_coinslstationeta_Prev;
   vector<int>     *tgc_coinslstationphi_Prev;
   vector<int>     *tgc_coinslsector_Prev;
   vector<int>     *tgc_coinsltrackletid_Prev;
   vector<int>     *tgc_coinsltrackletidstrip_Prev;
   Int_t           tgc_nprdcoll_Next;
   Int_t           tgc_nprd_Next;
   vector<int>     *tgc_station_Next;
   vector<int>     *tgc_eta_Next;
   vector<int>     *tgc_phi_Next;
   vector<int>     *tgc_gasGap_Next;
   vector<int>     *tgc_isStrip_Next;
   vector<int>     *tgc_channel_Next;
   vector<float>   *tgc_globPosX_Next;
   vector<float>   *tgc_globPosY_Next;
   vector<float>   *tgc_globPosZ_Next;
   vector<float>   *tgc_shortWidth_Next;
   vector<float>   *tgc_longWidth_Next;
   vector<float>   *tgc_length_Next;
   Int_t           tgc_ncoincoll_Next;
   Int_t           tgc_ncointracklet_Next;
   vector<float>   *tgc_cointrackletdelta_Next;
   vector<float>   *tgc_cointrackletposx_in_Next;
   vector<float>   *tgc_cointrackletposy_in_Next;
   vector<float>   *tgc_cointrackletposz_in_Next;
   vector<float>   *tgc_cointrackletposx_out_Next;
   vector<float>   *tgc_cointrackletposy_out_Next;
   vector<float>   *tgc_cointrackletposz_out_Next;
   vector<int>     *tgc_cointrackletstrip_Next;
   vector<int>     *tgc_cointrackletforward_Next;
   vector<float>   *tgc_cointrackletwidthout_Next;
   vector<float>   *tgc_cointrackletwidthin_Next;
   vector<int>     *tgc_cointrackletstationeta_Next;
   vector<int>     *tgc_cointrackletstationphi_Next;
   vector<int>     *tgc_cointrackletsector_Next;
   vector<int>     *tgc_cointracklettrackletid_Next;
   Int_t           tgc_ncoinhighpt_Next;
   vector<float>   *tgc_coinhighptdelta_Next;
   vector<float>   *tgc_coinhighptposx_in_Next;
   vector<float>   *tgc_coinhighptposy_in_Next;
   vector<float>   *tgc_coinhighptposz_in_Next;
   vector<float>   *tgc_coinhighptposx_out_Next;
   vector<float>   *tgc_coinhighptposy_out_Next;
   vector<float>   *tgc_coinhighptposz_out_Next;
   vector<int>     *tgc_coinhighptstrip_Next;
   vector<int>     *tgc_coinhighptforward_Next;
   vector<float>   *tgc_coinhighptwidthout_Next;
   vector<float>   *tgc_coinhighptwidthin_Next;
   vector<int>     *tgc_coinhighptstationeta_Next;
   vector<int>     *tgc_coinhighptstationphi_Next;
   vector<int>     *tgc_coinhighptsector_Next;
   vector<int>     *tgc_coinhighpttrackletid_Next;
   Int_t           tgc_ncoinsl_Next;
   vector<float>   *tgc_coinslptthresh_Next;
   vector<float>   *tgc_coinslposx_out_Next;
   vector<float>   *tgc_coinslposy_out_Next;
   vector<float>   *tgc_coinslposz_out_Next;
   vector<float>   *tgc_coinslroi_Next;
   vector<float>   *tgc_coinslforward_Next;
   vector<float>   *tgc_coinslwidthr_Next;
   vector<float>   *tgc_coinslwidthphi_Next;
   vector<int>     *tgc_coinslstationeta_Next;
   vector<int>     *tgc_coinslstationphi_Next;
   vector<int>     *tgc_coinslsector_Next;
   vector<int>     *tgc_coinsltrackletid_Next;
   vector<int>     *tgc_coinsltrackletidstrip_Next;
   UInt_t          IS_Nsgins;
   vector<float>   *IS_Xpt;
   vector<float>   *IS_Ypt;
   vector<float>   *IS_Zpt;
   vector<float>   *IS_Xvec;
   vector<float>   *IS_Yvec;
   vector<float>   *IS_Zvec;
   vector<float>   *IS_QualityFactor;
   vector<long>    *IS_NbreOfMultiLayer;
   vector<long>    *IS_TrackSharing;
   vector<long>    *IS_StationName;
   vector<long>    *IS_Ndigits;
   vector<long>    *IS_HitPosition;
   UInt_t          IS_MaxHits;
   vector<float>   *IS_Rdigi;
   vector<float>   *IS_Rtrack;
   vector<float>   *IS_Xdca;
   vector<float>   *IS_Ydca;
   vector<float>   *IS_Zdca;
   vector<float>   *IS_Sdca;
   vector<float>   *IS_Reso;
   vector<long>    *IS_JTYP;
   vector<long>    *IS_JFF;
   vector<long>    *IS_JZZ;
   vector<long>    *IS_JOB;
   vector<long>    *IS_JSPLI;
   vector<long>    *IS_JSL;
   vector<long>    *IS_JTUBE;
   vector<long>    *IS_JSZ;
   vector<long>    *IS_JSTRI;
   vector<float>   *IS_DriftTime;
   vector<long>    *IS_ChamberTech;
   vector<long>    *IS_StationNber;
   vector<long>    *IS_StationEta;
   vector<long>    *IS_StationPhi;
   vector<long>    *IS_Multilayer;
   vector<long>    *IS_TubeLayer;
   vector<long>    *IS_Tube;
   vector<long>    *IS_DoubletR;
   vector<long>    *IS_DoubletZ;
   vector<long>    *IS_DoubletPhi;
   vector<long>    *IS_GasGap;
   vector<long>    *IS_MeasuresPhi;
   vector<long>    *IS_Strip;
   vector<long>    *IS_IsStrip;
   vector<long>    *IS_Channel;
   vector<long>    *IS_ChamberLayer;
   vector<long>    *IS_WireLayer;
   vector<float>   *IS_RpcTime;
   UInt_t          MB_NTrk;
   UInt_t          VT_NTrk;
   vector<long>    *VT_Va;
   vector<float>   *VT_A0;
   vector<float>   *VT_Z;
   vector<float>   *VT_Phi;
   vector<float>   *VT_CotTh;
   vector<float>   *VT_PTInv;
   vector<float>   *VT_Cov11;
   vector<float>   *VT_Cov21;
   vector<float>   *VT_Cov22;
   vector<float>   *VT_Cov31;
   vector<float>   *VT_Cov32;
   vector<float>   *VT_Cov33;
   vector<float>   *VT_Cov41;
   vector<float>   *VT_Cov42;
   vector<float>   *VT_Cov43;
   vector<float>   *VT_Cov44;
   vector<float>   *VT_Cov51;
   vector<float>   *VT_Cov52;
   vector<float>   *VT_Cov53;
   vector<float>   *VT_Cov54;
   vector<float>   *VT_Cov55;
   vector<float>   *VT_Xpt;
   vector<float>   *VT_Ypt;
   vector<float>   *VT_Zpt;
   vector<float>   *VT_Xvec;
   vector<float>   *VT_Yvec;
   vector<float>   *VT_Zvec;
   vector<float>   *VT_Mom;
   vector<long>    *VT_digits;
   vector<long>    *VT_HitPosition;
   UInt_t          VT_TrHi_hits;
   vector<float>   *VT_TrHi_Rdigi;
   vector<float>   *VT_TrHi_Rtrack;
   vector<float>   *VT_TrHi_Xdca;
   vector<float>   *VT_TrHi_Ydca;
   vector<float>   *VT_TrHi_Zdca;
   vector<float>   *VT_TrHi_Sdca;
   vector<float>   *VT_TrHi_Reso;
   vector<float>   *VT_TrHi_RZSsim;
   vector<float>   *VT_TrHi_EZSfit;
   vector<long>    *VT_TrHi_JTYP;
   vector<long>    *VT_TrHi_JFF;
   vector<long>    *VT_TrHi_JZZ;
   vector<long>    *VT_TrHi_JOB;
   vector<long>    *VT_TrHi_JSPLI;
   vector<long>    *VT_TrHi_JSL;
   vector<long>    *VT_TrHi_JTUBE;
   vector<long>    *VT_TrHi_JSZ;
   vector<long>    *VT_TrHi_JSTRI;
   vector<float>   *VT_TrHi_DriftTime;
   vector<long>    *VT_TrHi_ChamberTech;
   vector<long>    *VT_TrHi_StationNber;
   vector<long>    *VT_TrHi_StationEta;
   vector<long>    *VT_TrHi_StationPhi;
   vector<long>    *VT_TrHi_Multilayer;
   vector<long>    *VT_TrHi_TubeLayer;
   vector<long>    *VT_TrHi_Tube;
   vector<long>    *VT_TrHi_DoubletR;
   vector<long>    *VT_TrHi_DoubletZ;
   vector<long>    *VT_TrHi_DoubletPhi;
   vector<long>    *VT_TrHi_GasGap;
   vector<long>    *VT_TrHi_MeasuresPhi;
   vector<long>    *VT_TrHi_Strip;
   vector<long>    *VT_TrHi_IsStrip;
   vector<long>    *VT_TrHi_Channel;
   vector<long>    *VT_TrHi_ChamberLayer;
   vector<long>    *VT_TrHi_WireLayer;
   vector<float>   *VT_TrHi_RpcTime;
   UInt_t          KE_NTrk;
   vector<long>    *KE_Va;
   vector<float>   *KE_Thept;
   vector<float>   *KE_Phipt;
   vector<float>   *KE_Thevc;
   vector<float>   *KE_Phivc;
   vector<float>   *KE_PInv;
   vector<float>   *KE_Cov11;
   vector<float>   *KE_Cov21;
   vector<float>   *KE_Cov22;
   vector<float>   *KE_Cov31;
   vector<float>   *KE_Cov32;
   vector<float>   *KE_Cov33;
   vector<float>   *KE_Cov41;
   vector<float>   *KE_Cov42;
   vector<float>   *KE_Cov43;
   vector<float>   *KE_Cov44;
   vector<float>   *KE_Cov51;
   vector<float>   *KE_Cov52;
   vector<float>   *KE_Cov53;
   vector<float>   *KE_Cov54;
   vector<float>   *KE_Cov55;
   vector<float>   *KE_Xpt;
   vector<float>   *KE_Ypt;
   vector<float>   *KE_Zpt;
   vector<float>   *KE_Xvec;
   vector<float>   *KE_Yvec;
   vector<float>   *KE_Zvec;
   vector<float>   *KE_Mom;
   vector<float>   *KE_ZCyl;
   vector<float>   *KE_RCyl;
   UInt_t          MS_NTrk;
   vector<long>    *MS_Va;
   vector<float>   *MS_Thept;
   vector<float>   *MS_Phipt;
   vector<float>   *MS_Thevc;
   vector<float>   *MS_Phivc;
   vector<float>   *MS_PInv;
   vector<float>   *MS_Cov11;
   vector<float>   *MS_Cov21;
   vector<float>   *MS_Cov22;
   vector<float>   *MS_Cov31;
   vector<float>   *MS_Cov32;
   vector<float>   *MS_Cov33;
   vector<float>   *MS_Cov41;
   vector<float>   *MS_Cov42;
   vector<float>   *MS_Cov43;
   vector<float>   *MS_Cov44;
   vector<float>   *MS_Cov51;
   vector<float>   *MS_Cov52;
   vector<float>   *MS_Cov53;
   vector<float>   *MS_Cov54;
   vector<float>   *MS_Cov55;
   vector<float>   *MS_Xpt;
   vector<float>   *MS_Ypt;
   vector<float>   *MS_Zpt;
   vector<float>   *MS_Xvec;
   vector<float>   *MS_Yvec;
   vector<float>   *MS_Zvec;
   vector<float>   *MS_Mom;
   vector<float>   *MS_ZCyl;
   vector<float>   *MS_RCyl;
   vector<float>   *MS_Chican;
   vector<float>   *MS_Chifit;
   vector<float>   *MS_Chiver;
   vector<float>   *MS_Chistat;
   vector<long>    *MS_Ndof;
   Int_t           Moore_nmuon;
   vector<int>     *Moore_phih;
   vector<int>     *Moore_etah;
   vector<int>     *Moore_mdth;
   vector<int>     *Moore_cscetah;
   vector<int>     *Moore_cscphih;
   vector<int>     *Moore_rpcetah;
   vector<int>     *Moore_rpcphih;
   vector<int>     *Moore_tgcetah;
   vector<int>     *Moore_tgcphih;
   vector<int>     *Moore_stati;
   vector<int>     *Moore_statr;
   vector<float>   *Moore_xvtxr;
   vector<float>   *Moore_yvtxr;
   vector<float>   *Moore_zvtxr;
   vector<float>   *Moore_a0r;
   vector<float>   *Moore_z0r;
   vector<float>   *Moore_phir;
   vector<float>   *Moore_thetar;
   vector<float>   *Moore_qpir;
   vector<float>   *Moore_etar;
   vector<float>   *Moore_chi2;
   vector<float>   *Moore_chi2pr;
   vector<float>   *Moore_origx;
   vector<float>   *Moore_origy;
   vector<float>   *Moore_origz;
   vector<float>   *Moore_covr11;
   vector<float>   *Moore_covr12;
   vector<float>   *Moore_covr22;
   vector<float>   *Moore_covr13;
   vector<float>   *Moore_covr23;
   vector<float>   *Moore_covr33;
   vector<float>   *Moore_covr14;
   vector<float>   *Moore_covr24;
   vector<float>   *Moore_covr34;
   vector<float>   *Moore_covr44;
   vector<float>   *Moore_covr15;
   vector<float>   *Moore_covr25;
   vector<float>   *Moore_covr35;
   vector<float>   *Moore_covr45;
   vector<float>   *Moore_covr55;
   Int_t           MooreSegments_nseg;
   vector<int>     *MooreSegments_ml;
   vector<int>     *MooreSegments_nhml1;
   vector<int>     *MooreSegments_nhml2;
   vector<int>     *MooreSegments_nmlyr;
   vector<int>     *MooreSegments_nhit;
   vector<int>     *MooreSegments_nhcsc;
   vector<int>     *MooreSegments_nhmdt;
   vector<int>     *MooreSegments_nhrpc;
   vector<int>     *MooreSegments_nhtgc;
   vector<int>     *MooreSegments_n_tottubes_seg;
   vector<int>     *MooreSegments_n_hittubes_seg;
   vector<int>     *MooreSegments_hittype;
   vector<int>     *MooreSegments_prdadc;
   vector<int>     *MooreSegments_prdtdc;
   vector<float>   *MooreSegments_z;
   vector<float>   *MooreSegments_rho;
   vector<float>   *MooreSegments_phi;
   vector<float>   *MooreSegments_theta;
   vector<float>   *MooreSegments_cotth;
   vector<float>   *MooreSegments_dtheta;
   vector<float>   *MooreSegments_chi2;
   vector<int>     *MooreSegments_ndof;
   vector<float>   *MooreSegments_rInt;
   vector<float>   *MooreSegments_LocR;
   vector<float>   *MooreSegments_driftTime;
   UInt_t          jetNumCone4H1TowerJets;
   vector<double>  *jetEtaCone4H1TowerJets;
   vector<double>  *jetPhiCone4H1TowerJets;
   vector<double>  *jetECone4H1TowerJets;
   vector<double>  *jetEtCone4H1TowerJets;
   vector<double>  *jetMCone4H1TowerJets;
   vector<double>  *jetPxCone4H1TowerJets;
   vector<double>  *jetPyCone4H1TowerJets;
   vector<double>  *jetPzCone4H1TowerJets;
   vector<long>    *jetSizeCone4H1TowerJets;
   vector<double>  *jetEmfCone4H1TowerJets;
   UInt_t          CaloMu_ntrack;
   vector<int>     *CaloMu_trkPdgid;
   vector<int>     *CaloMu_trkMother;
   vector<double>  *CaloMu_trkEta;
   vector<double>  *CaloMu_trkPhi;
   vector<double>  *CaloMu_trkPt;
   vector<double>  *CaloMu_trkD0;
   vector<double>  *CaloMu_trkIP;
   vector<int>     *CaloMu_trkBLayerHits;
   vector<int>     *CaloMu_trkPixelHits;
   vector<int>     *CaloMu_trkSCTHits;
   vector<int>     *CaloMu_trkTRTHits;
   UInt_t          CaloMu_nmuon;
   vector<int>     *CaloMu_pdgid;
   vector<int>     *CaloMu_mother;
   vector<int>     *CaloMu_tag;
   vector<double>  *CaloMu_lhr;
   vector<vector<double> > *CaloMu_etCone;
   vector<vector<double> > *CaloMu_ptCone;
   vector<double>  *CaloMu_eta;
   vector<double>  *CaloMu_phi;
   vector<double>  *CaloMu_pt;
   vector<double>  *CaloMu_qoverp;
   vector<double>  *CaloMu_IP;
   vector<double>  *CaloMu_d0;
   vector<int>     *CaloMu_bLayerHits;
   vector<int>     *CaloMu_pixelHits;
   vector<int>     *CaloMu_SCTHits;
   vector<int>     *CaloMu_TRTHits;
   vector<vector<int> > *CaloMu_sample;
   vector<vector<double> > *CaloMu_energy;
   vector<vector<double> > *CaloMu_energyLoss;
   UInt_t          CaloMu2_ntrack;
   vector<int>     *CaloMu2_trkPdgid;
   vector<int>     *CaloMu2_trkMother;
   vector<double>  *CaloMu2_trkEta;
   vector<double>  *CaloMu2_trkPhi;
   vector<double>  *CaloMu2_trkPt;
   vector<double>  *CaloMu2_trkD0;
   vector<double>  *CaloMu2_trkIP;
   vector<int>     *CaloMu2_trkBLayerHits;
   vector<int>     *CaloMu2_trkPixelHits;
   vector<int>     *CaloMu2_trkSCTHits;
   vector<int>     *CaloMu2_trkTRTHits;
   UInt_t          CaloMu2_nmuon;
   vector<int>     *CaloMu2_pdgid;
   vector<int>     *CaloMu2_mother;
   vector<int>     *CaloMu2_tag;
   vector<double>  *CaloMu2_lhr;
   vector<vector<double> > *CaloMu2_etCone;
   vector<vector<double> > *CaloMu2_ptCone;
   vector<double>  *CaloMu2_eta;
   vector<double>  *CaloMu2_phi;
   vector<double>  *CaloMu2_pt;
   vector<double>  *CaloMu2_qoverp;
   vector<double>  *CaloMu2_IP;
   vector<double>  *CaloMu2_d0;
   vector<int>     *CaloMu2_bLayerHits;
   vector<int>     *CaloMu2_pixelHits;
   vector<int>     *CaloMu2_SCTHits;
   vector<int>     *CaloMu2_TRTHits;
   vector<vector<int> > *CaloMu2_sample;
   vector<vector<double> > *CaloMu2_energy;
   vector<vector<double> > *CaloMu2_energyLoss;
   Int_t           trk_nTracksComb;
   vector<int>     *trk_nPixelHitsComb;
   vector<int>     *trk_nSctHitsComb;
   vector<int>     *trk_nTrtHitsComb;
   vector<vector<float> > *trk_PixResPhiComb;
   vector<vector<float> > *trk_PixResEtaComb;
   vector<vector<float> > *trk_PixPullPhiComb;
   vector<vector<float> > *trk_PixPullEtaComb;
   vector<vector<float> > *trk_PixErrTrkPhiComb;
   vector<vector<float> > *trk_PixErrTrkEtaComb;
   vector<vector<float> > *trk_PixErrHitPhiComb;
   vector<vector<float> > *trk_PixErrHitEtaComb;
   vector<vector<int> > *trk_Pix_becComb;
   vector<vector<int> > *trk_Pix_layerComb;
   vector<vector<int> > *trk_Pix_etaComb;
   vector<vector<int> > *trk_Pix_phiComb;
   vector<vector<int> > *trk_Pix_clusWidthRowComb;
   vector<vector<int> > *trk_Pix_clusWidthColComb;
   vector<vector<float> > *trk_Pix_LocXComb;
   vector<vector<float> > *trk_Pix_LocYComb;
   vector<vector<float> > *trk_SctResComb;
   vector<vector<float> > *trk_SctPullComb;
   vector<vector<float> > *trk_SctErrTrkComb;
   vector<vector<float> > *trk_SctErrHitComb;
   vector<vector<int> > *trk_Sct_becComb;
   vector<vector<int> > *trk_Sct_layerComb;
   vector<vector<int> > *trk_Sct_etaComb;
   vector<vector<int> > *trk_Sct_phiComb;
   vector<vector<int> > *trk_Sct_sideComb;
   vector<vector<int> > *trk_Sct_rdoIdComb;
   vector<vector<int> > *trk_Sct_clusGroupsizeComb;
   vector<vector<float> > *trk_Sct_clusxComb;
   vector<vector<float> > *trk_Sct_clusyComb;
   vector<vector<float> > *trk_Sct_cluszComb;
   vector<vector<float> > *trk_TrtResComb;
   vector<vector<float> > *trk_TrtPullComb;
   vector<vector<float> > *trk_TrtErrTrkComb;
   vector<vector<float> > *trk_TrtErrHitComb;
   vector<vector<float> > *trk_Trt_RComb;
   vector<vector<float> > *trk_Trt_RtrackComb;
   vector<vector<float> > *trk_Trt_tComb;
   vector<vector<float> > *trk_Trt_xComb;
   vector<vector<float> > *trk_Trt_yComb;
   vector<vector<int> > *trk_Trt_HLComb;
   vector<vector<int> > *trk_Trt_strawlayerComb;
   vector<vector<int> > *trk_Trt_becComb;
   vector<vector<int> > *trk_Trt_layerComb;
   vector<vector<int> > *trk_Trt_strawComb;
   vector<vector<int> > *trk_Trt_phisectorComb;
   vector<float>   *trk_Rec_d0Comb;
   vector<float>   *trk_Rec_z0Comb;
   vector<float>   *trk_Rec_phi0Comb;
   vector<float>   *trk_Rec_theta0Comb;
   vector<float>   *trk_Rec_qoverpComb;
   vector<float>   *trk_Rec_chi2Comb;
   vector<int>     *trk_Rec_ndofComb;
   vector<float>   *trk_Rec_etaComb;
   vector<float>   *trk_Rec_error_d0Comb;
   vector<float>   *trk_Rec_error_z0Comb;
   vector<float>   *trk_Rec_error_phi0Comb;
   vector<float>   *trk_Rec_error_theta0Comb;
   vector<float>   *trk_Rec_error_qoverpComb;
   vector<float>   *trk_Rec_chi2probComb;
   vector<int>     *trk_Rec_authorComb;
   Int_t           trk_nTracksMuon;
   vector<int>     *trk_nPixelHitsMuon;
   vector<int>     *trk_nSctHitsMuon;
   vector<int>     *trk_nTrtHitsMuon;
   vector<float>   *trk_Rec_d0Muon;
   vector<float>   *trk_Rec_z0Muon;
   vector<float>   *trk_Rec_phi0Muon;
   vector<float>   *trk_Rec_theta0Muon;
   vector<float>   *trk_Rec_qoverpMuon;
   vector<float>   *trk_Rec_chi2Muon;
   vector<int>     *trk_Rec_ndofMuon;
   vector<float>   *trk_Rec_etaMuon;
   vector<float>   *trk_Rec_error_d0Muon;
   vector<float>   *trk_Rec_error_z0Muon;
   vector<float>   *trk_Rec_error_phi0Muon;
   vector<float>   *trk_Rec_error_theta0Muon;
   vector<float>   *trk_Rec_error_qoverpMuon;
   vector<float>   *trk_Rec_chi2probMuon;
   vector<int>     *trk_Rec_authorMuon;
   UInt_t          MuTagIMO_nmuon;
   UInt_t          MuTagIMO_nTagSegs;
   vector<int>     *MuTagIMO_trk_isTagged;
   vector<int>     *MuTagIMO_trk_matchesBarCode;
   vector<int>     *MuTagIMO_trk_matchesPdg;
   vector<int>     *MuTagIMO_trk_nrPixelHits;
   vector<int>     *MuTagIMO_trk_nrSctHits;
   vector<float>   *MuTagIMO_trk_A0;
   vector<float>   *MuTagIMO_trk_Z0;
   vector<float>   *MuTagIMO_trk_phi;
   vector<float>   *MuTagIMO_trk_theta;
   vector<float>   *MuTagIMO_trk_qOverP;
   vector<float>   *MuTagIMO_trk_chi2;
   vector<float>   *MuTagIMO_trk_ndof;
   vector<float>   *MuTagIMO_trk_Author;
   vector<float>   *MuTagIMO_trk_cov11;
   vector<float>   *MuTagIMO_trk_cov12;
   vector<float>   *MuTagIMO_trk_cov13;
   vector<float>   *MuTagIMO_trk_cov14;
   vector<float>   *MuTagIMO_trk_cov15;
   vector<float>   *MuTagIMO_trk_cov22;
   vector<float>   *MuTagIMO_trk_cov23;
   vector<float>   *MuTagIMO_trk_cov24;
   vector<float>   *MuTagIMO_trk_cov25;
   vector<float>   *MuTagIMO_trk_cov33;
   vector<float>   *MuTagIMO_trk_cov34;
   vector<float>   *MuTagIMO_trk_cov35;
   vector<float>   *MuTagIMO_trk_cov44;
   vector<float>   *MuTagIMO_trk_cov45;
   vector<float>   *MuTagIMO_trk_cov55;
   vector<int>     *MuTagIMO_exTrk_trackIndex;
   vector<float>   *MuTagIMO_exTrk_A0;
   vector<float>   *MuTagIMO_exTrk_Z0;
   vector<float>   *MuTagIMO_exTrk_phi;
   vector<float>   *MuTagIMO_exTrk_theta;
   vector<float>   *MuTagIMO_exTrk_qOverP;
   vector<float>   *MuTagIMO_exTrk_cov11;
   vector<float>   *MuTagIMO_exTrk_cov12;
   vector<float>   *MuTagIMO_exTrk_cov13;
   vector<float>   *MuTagIMO_exTrk_cov14;
   vector<float>   *MuTagIMO_exTrk_cov15;
   vector<float>   *MuTagIMO_exTrk_cov22;
   vector<float>   *MuTagIMO_exTrk_cov23;
   vector<float>   *MuTagIMO_exTrk_cov24;
   vector<float>   *MuTagIMO_exTrk_cov25;
   vector<float>   *MuTagIMO_exTrk_cov33;
   vector<float>   *MuTagIMO_exTrk_cov34;
   vector<float>   *MuTagIMO_exTrk_cov35;
   vector<float>   *MuTagIMO_exTrk_cov44;
   vector<float>   *MuTagIMO_exTrk_cov45;
   vector<float>   *MuTagIMO_exTrk_cov55;
   vector<float>   *MuTagIMO_exTrk_Eloss;
   vector<float>   *MuTagIMO_exTrk_gPosX;
   vector<float>   *MuTagIMO_exTrk_gPosY;
   vector<float>   *MuTagIMO_exTrk_gPosZ;
   vector<float>   *MuTagIMO_exTrk_gDirX;
   vector<float>   *MuTagIMO_exTrk_gDirY;
   vector<float>   *MuTagIMO_exTrk_gDirZ;
   vector<float>   *MuTagIMO_exTrk_locX;
   vector<float>   *MuTagIMO_exTrk_locY;
   vector<float>   *MuTagIMO_exTrk_angleXZ;
   vector<float>   *MuTagIMO_exTrk_angleYZ;
   vector<float>   *MuTagIMO_exTrk_locX_error;
   vector<float>   *MuTagIMO_exTrk_locY_error;
   vector<float>   *MuTagIMO_exTrk_angleXZ_error;
   vector<float>   *MuTagIMO_exTrk_angleYZ_error;
   vector<int>     *MuTagIMO_seg_isTagSeg;
   vector<int>     *MuTagIMO_seg_matchesBarCode;
   vector<int>     *MuTagIMO_seg_matchesPdg;
   vector<int>     *MuTagIMO_seg_exTrkIndex;
   vector<int>     *MuTagIMO_seg_trackIndex;
   vector<int>     *MuTagIMO_seg_stationLevel;
   vector<int>     *MuTagIMO_seg_isEndCap;
   vector<int>     *MuTagIMO_seg_isLarge;
   vector<int>     *MuTagIMO_seg_nrHoles;
   vector<int>     *MuTagIMO_seg_nrMLs;
   vector<int>     *MuTagIMO_seg_nrMdtHits;
   vector<int>     *MuTagIMO_seg_nrRpcHits;
   vector<int>     *MuTagIMO_seg_nrTgcHits;
   vector<int>     *MuTagIMO_seg_nrCscHits;
   vector<float>   *MuTagIMO_seg_phi;
   vector<float>   *MuTagIMO_seg_theta;
   vector<float>   *MuTagIMO_seg_chi2;
   vector<float>   *MuTagIMO_seg_cov11;
   vector<float>   *MuTagIMO_seg_cov12;
   vector<float>   *MuTagIMO_seg_cov13;
   vector<float>   *MuTagIMO_seg_cov14;
   vector<float>   *MuTagIMO_seg_cov15;
   vector<float>   *MuTagIMO_seg_cov22;
   vector<float>   *MuTagIMO_seg_cov23;
   vector<float>   *MuTagIMO_seg_cov24;
   vector<float>   *MuTagIMO_seg_cov25;
   vector<float>   *MuTagIMO_seg_cov33;
   vector<float>   *MuTagIMO_seg_cov34;
   vector<float>   *MuTagIMO_seg_cov35;
   vector<float>   *MuTagIMO_seg_cov44;
   vector<float>   *MuTagIMO_seg_cov45;
   vector<float>   *MuTagIMO_seg_cov55;
   vector<float>   *MuTagIMO_seg_gPosX;
   vector<float>   *MuTagIMO_seg_gPosY;
   vector<float>   *MuTagIMO_seg_gPosZ;
   vector<float>   *MuTagIMO_seg_gDirX;
   vector<float>   *MuTagIMO_seg_gDirY;
   vector<float>   *MuTagIMO_seg_gDirZ;
   vector<float>   *MuTagIMO_seg_locX;
   vector<float>   *MuTagIMO_seg_locY;
   vector<float>   *MuTagIMO_seg_angleXZ;
   vector<float>   *MuTagIMO_seg_angleYZ;
   vector<float>   *MuTagIMO_seg_locX_error;
   vector<float>   *MuTagIMO_seg_locY_error;
   vector<float>   *MuTagIMO_seg_angleXZ_error;
   vector<float>   *MuTagIMO_seg_angleYZ_error;
   vector<int>     *MuTagIMO_match_trackIndex;
   vector<float>   *MuTagIMO_match_locX;
   vector<float>   *MuTagIMO_match_locY;
   vector<float>   *MuTagIMO_match_angleXZ;
   vector<float>   *MuTagIMO_match_angleYZ;
   Float_t         MET_ExMiss0;
   Float_t         MET_EyMiss0;
   Float_t         MET_EtSum0;
   Float_t         MET_ExMiss;
   Float_t         MET_EyMiss;
   Float_t         MET_EtSum;
   Float_t         MET_ExMissTopo;
   Float_t         MET_EyMissTopo;
   Float_t         MET_EtSumTopo;
   Float_t         MET_ExMissCorr;
   Float_t         MET_EyMissCorr;
   Float_t         MET_EtSumCorr;
   Float_t         MET_ExMissLocHadTopo;
   Float_t         MET_EyMissLocHadTopo;
   Float_t         MET_EtSumLocHadTopo;
   Float_t         MET_ExMissCorrTopo;
   Float_t         MET_EyMissCorrTopo;
   Float_t         MET_EtSumCorrTopo;
   Float_t         MET_ExMissMu;
   Float_t         MET_EyMissMu;
   Float_t         MET_EtSumMu;
   Float_t         MET_ExMissMuBoyTrack;
   Float_t         MET_EyMissMuBoyTrack;
   Float_t         MET_EtSumMuBoyTrack;
   Float_t         MET_ExMissMuBoySpectro;
   Float_t         MET_EyMissMuBoySpectro;
   Float_t         MET_EtSumMuBoySpectro;
   Float_t         MET_ExMissMuBoy;
   Float_t         MET_EyMissMuBoy;
   Float_t         MET_EtSumMuBoy;
   Float_t         MET_ExMissFinal;
   Float_t         MET_EyMissFinal;
   Float_t         MET_EtSumFinal;
   Float_t         MET_ExMissRefFinal;
   Float_t         MET_EyMissRefFinal;
   Float_t         MET_EtSumRefFinal;
   Float_t         MET_ExMissCryo;
   Float_t         MET_EyMissCryo;
   Float_t         MET_EtSumCryo;
   Float_t         MET_ExMissCryoCone;
   Float_t         MET_EyMissCryoCone;
   Float_t         MET_EtSumCryoCone;
   Float_t         MET_ExMissDMCryo;
   Float_t         MET_EyMissDMCryo;
   Float_t         MET_EtSumDMCryo;
   Float_t         MET_ExMissDMCrack1;
   Float_t         MET_EyMissDMCrack1;
   Float_t         MET_EtSumDMCrack1;
   Float_t         MET_ExMissDMCrack2;
   Float_t         MET_EyMissDMCrack2;
   Float_t         MET_EtSumDMCrack2;
   Float_t         MET_ExMissDMAll;
   Float_t         MET_EyMissDMAll;
   Float_t         MET_EtSumDMAll;
   Float_t         MET_ExMissLocHadTopoObj;
   Float_t         MET_EyMissLocHadTopoObj;
   Float_t         MET_EtSumLocHadTopoObj;
   Float_t         MET_ExMissTopoObj;
   Float_t         MET_EyMissTopoObj;
   Float_t         MET_EtSumTopoObj;
   Float_t         MET_ExMissRefEle;
   Float_t         MET_EyMissRefEle;
   Float_t         MET_EtSumRefEle;
   Float_t         MET_ExMissRefGamma;
   Float_t         MET_EyMissRefGamma;
   Float_t         MET_EtSumRefGamma;
   Float_t         MET_ExMissRefMuo;
   Float_t         MET_EyMissRefMuo;
   Float_t         MET_EtSumRefMuo;
   Float_t         MET_ExMissRefMuoTrack;
   Float_t         MET_EyMissRefMuoTrack;
   Float_t         MET_EtSumRefMuoTrack;
   Float_t         MET_ExMissRefTau;
   Float_t         MET_EyMissRefTau;
   Float_t         MET_EtSumRefTau;
   Float_t         MET_ExMissRefJet;
   Float_t         MET_EyMissRefJet;
   Float_t         MET_EtSumRefJet;
   Float_t         MET_ExMissCellOut;
   Float_t         MET_EyMissCellOut;
   Float_t         MET_EtSumCellOut;
   Float_t         MET_ExFCALCorrTopo;
   Float_t         MET_EyFCALCorrTopo;
   Float_t         MET_EtSumFCALCorrTopo;
   Float_t         MET_ExFCALlocHadTopo;
   Float_t         MET_EyFCALlocHadTopo;
   Float_t         MET_EtSumFCALlocHadTopo;
   Float_t         MET_ExPEMB;
   Float_t         MET_EyPEMB;
   Float_t         MET_EtSumPEMB;
   Int_t           MET_nCellPEMB;
   Float_t         MET_ExEMB;
   Float_t         MET_EyEMB;
   Float_t         MET_EtSumEMB;
   Int_t           MET_nCellEMB;
   Float_t         MET_ExPEMEC;
   Float_t         MET_EyPEMEC;
   Float_t         MET_EtSumPEMEC;
   Int_t           MET_nCellPEMEC;
   Float_t         MET_ExEMEC;
   Float_t         MET_EyEMEC;
   Float_t         MET_EtSumEMEC;
   Int_t           MET_nCellEMEC;
   Float_t         MET_ExTILE;
   Float_t         MET_EyTILE;
   Float_t         MET_EtSumTILE;
   Int_t           MET_nCellTILE;
   Float_t         MET_ExHEC;
   Float_t         MET_EyHEC;
   Float_t         MET_EtSumHEC;
   Int_t           MET_nCellHEC;
   Float_t         MET_ExFCAL;
   Float_t         MET_EyFCAL;
   Float_t         MET_EtSumFCAL;
   Int_t           MET_nCellFCAL;
   Float_t         MET_ExBARReg;
   Float_t         MET_EyBARReg;
   Float_t         MET_EtSumBARReg;
   Float_t         MET_ExECReg;
   Float_t         MET_EyECReg;
   Float_t         MET_EtSumECReg;
   Float_t         MET_ExFCALReg;
   Float_t         MET_EyFCALReg;
   Float_t         MET_EtSumFCALReg;
   Int_t           L1Em_nRoI;
   vector<long>    *L1Em_RoIWord;
   vector<float>   *L1Em_Core;
   vector<float>   *L1Em_EmClus;
   vector<float>   *L1Em_TauClus;
   vector<float>   *L1Em_EmIsol;
   vector<float>   *L1Em_HdIsol;
   vector<float>   *L1Em_HdCore;
   vector<long>    *L1Em_EmTauThresh;
   vector<float>   *L1Em_eta;
   vector<float>   *L1Em_phi;
   Int_t           L1Jet_nRoI;
   vector<long>    *L1Jet_JetRoIWord;
   vector<float>   *L1Jet_ET4x4;
   vector<float>   *L1Jet_ET6x6;
   vector<float>   *L1Jet_ET8x8;
   vector<long>    *L1Jet_Thresh;
   vector<float>   *L1Jet_eta;
   vector<float>   *L1Jet_phi;
   Long64_t        L1ET_EtMissHits;
   Long64_t        L1ET_EtSumHits;
   Float_t         L1ET_Ex;
   Float_t         L1ET_Ey;
   Float_t         L1ET_EtMiss;
   Float_t         L1ET_EtSum;
   UInt_t          nCTP_ROI;
   vector<unsigned long> *CTP_ROI;
   UInt_t          nMuCTPI_ROI;
   vector<unsigned long> *muCTPI_ROI;
   UInt_t          nEMTau_ROI;
   vector<unsigned long> *EMTau_ROI;
   UInt_t          nJetEnergy_ROI;
   vector<unsigned long> *JetEnergy_ROI;
   UInt_t          muctpi_nCandidates;
   UInt_t          muctpi_windowSizeBC;
   vector<unsigned long> *muctpi_bcid;
   vector<unsigned long> *muctpi_PtMultiplicity;
   vector<unsigned long> *muctpi_cand_sectorOverflow;
   vector<unsigned long> *muctpi_cand_RoiOverflow;
   vector<unsigned long> *muctpi_cand_RoiNumber;
   vector<unsigned long> *muctpi_cand_overlapBits;
   vector<unsigned long> *muctpi_cand_sectorID;
   vector<unsigned long> *muctpi_cand_sectorLocation;
   vector<unsigned long> *muctpi_cand_hemisphere;
   vector<unsigned long> *muctpi_cand_Pt;
   vector<unsigned long> *muctpi_cand_bcid;
   vector<unsigned long> *muctpi_cand_isHighestPt;
   vector<unsigned long> *muctpi_cand_sentRoI;
   UInt_t          muctpi_roi_GBCID;
   UInt_t          muctpi_roi_N_ROI;
   vector<unsigned long> *muctpi_roi_SUM;
   vector<unsigned long> *muctpi_roi_BCID;
   vector<unsigned long> *muctpi_roi_First;
   vector<unsigned long> *muctpi_roi_Acc;
   vector<unsigned long> *muctpi_roi_O_ROI;
   vector<unsigned long> *muctpi_roi_O_STR;
   vector<unsigned long> *muctpi_roi_pT;
   vector<float>   *muctpi_roi_eta;
   vector<float>   *muctpi_roi_phi;
   UInt_t          muctpi_rodheader_sourceId;
   UInt_t          muctpi_rodheader_runNumber;
   UInt_t          muctpi_rodheader_lvl1Id;
   UInt_t          muctpi_rodheader_bcid;
   UInt_t          muctpi_rodheader_lvl1TriggerType;
   UInt_t          muctpi_rodheader_detectorEventType;
   UInt_t          muctpi_rodheader_nDataWords;
   vector<unsigned long> *muctpi_rodheader_statusWords;
   UInt_t          nCandidates;
   vector<double>  *etaCand;
   vector<double>  *phiCand;
   UInt_t          nItems;
   vector<string>  *itemName;
   vector<bool>    *itemTBP;
   vector<bool>    *itemTAP;
   vector<bool>    *itemTAV;
   UInt_t          nThresholds;
   vector<string>  *thresholdName;
   vector<unsigned long> *thresholdMulti;
   UInt_t          ctp_numberBC;
   Float_t         ctp_L1A_BC;
   UInt_t          ctp_timeSec;
   UInt_t          ctp_timeNanoSec;
   UInt_t          ctp_nPITs;
   UInt_t          ctp_firedItemsBeforePrescale;
   vector<long>    *ctp_bcid;
   vector<long>    *ctp_randomTrig;
   vector<long>    *ctp_prescaledClock;
   vector<long>    *ctp_bcIndexPIT;
   vector<long>    *ctp_pit;
   vector<long>    *ctp_bcIndexTriggerItems;
   vector<long>    *ctp_tbp;
   vector<long>    *ctp_tap;
   vector<long>    *ctp_tav;
   UInt_t          ctp_rodheader_sourceId;
   UInt_t          ctp_rodheader_runNumber;
   UInt_t          ctp_rodheader_lvl1Id;
   UInt_t          ctp_rodheader_bcid;
   UInt_t          ctp_rodheader_lvl1TriggerType;
   UInt_t          ctp_rodheader_detectorEventType;
   UInt_t          ctp_rodheader_nDataWords;
   vector<long>    *ctp_rodheader_statusWords;
#endif

   Int_t           L1CaloPPM_ntt;
   vector<double>  *L1CaloPPM_eta;
   vector<double>  *L1CaloPPM_phi;
   vector<unsigned int> *L1CaloPPM_emCrate;
   vector<unsigned int> *L1CaloPPM_emModule;
   vector<unsigned int> *L1CaloPPM_emSubmodule;
   vector<unsigned int> *L1CaloPPM_emChannel;
   vector<unsigned int> *L1CaloPPM_hadCrate;
   vector<unsigned int> *L1CaloPPM_hadModule;
   vector<unsigned int> *L1CaloPPM_hadSubmodule;
   vector<unsigned int> *L1CaloPPM_hadChannel;
   vector<unsigned int> *L1CaloPPM_emChannelId;
   vector<unsigned int> *L1CaloPPM_hadChannelId;
   vector<double>  *L1CaloPPM_emTTCellsEnergy;
   vector<double>  *L1CaloPPM_hadTTCellsEnergy;
   vector<vector<double> > *L1CaloPPM_emCaloWaves;
   vector<vector<double> > *L1CaloPPM_hadCaloWaves;
   vector<int>     *L1CaloPPM_emPeak;
   vector<int>     *L1CaloPPM_emADCPeak;
   vector<int>     *L1CaloPPM_hadPeak;
   vector<int>     *L1CaloPPM_hadADCPeak;
   vector<vector<int> > *L1CaloPPM_emLUT;
   vector<vector<int> > *L1CaloPPM_hadLUT;
   vector<vector<int> > *L1CaloPPM_emADC;
   vector<vector<int> > *L1CaloPPM_hadADC;
   vector<int>     *L1CaloPPM_emEnergy;
   vector<int>     *L1CaloPPM_hadEnergy;
   vector<vector<int> > *L1CaloPPM_emBCIDvec;
   vector<vector<int> > *L1CaloPPM_emBCIDext;
   vector<vector<int> > *L1CaloPPM_hadBCIDvec;
   vector<vector<int> > *L1CaloPPM_hadBCIDext;
   vector<int>     *L1CaloPPM_emError;
   vector<int>     *L1CaloPPM_hadError;
   vector<int>     *L1CaloPPM_emBCID;
   vector<int>     *L1CaloPPM_hadBCID;
   vector<int>     *L1CaloPPM_emIsSaturated;
   vector<int>     *L1CaloPPM_hadIsSaturated;
   vector<int>     *L1CaloPPM_emIsFilled;
   vector<int>     *L1CaloPPM_hadIsFilled;

#ifndef PPM_ONLY
   Int_t           L1CaloCPM_RoI_n;
   vector<int>     *L1CaloCPM_RoI_crate;
   vector<int>     *L1CaloCPM_RoI_cpm;
   vector<int>     *L1CaloCPM_RoI_chip;
   vector<int>     *L1CaloCPM_RoI_location;
   vector<int>     *L1CaloCPM_RoI_hits;
   vector<double>  *L1CaloCPM_RoI_eta;
   vector<double>  *L1CaloCPM_RoI_phi;
   vector<int>     *L1CaloCPM_RoI_core;
   vector<int>     *L1CaloCPM_RoI_emClus;
   vector<int>     *L1CaloCPM_RoI_tauClus;
   vector<int>     *L1CaloCPM_RoI_emIsol;
   vector<int>     *L1CaloCPM_RoI_hadIsol;
   vector<int>     *L1CaloCPM_RoI_hadVeto;
   vector<bool>    *L1CaloCPM_RoI_isEtMax;
   vector<int>     *L1CaloCPM_RoI_simHits;
   vector<int>     *L1CaloCPM_RoI_error;
   Int_t           L1CaloCPM_SimRoI_n;
   vector<double>  *L1CaloCPM_SimRoI_eta;
   vector<double>  *L1CaloCPM_SimRoI_phi;
   vector<int>     *L1CaloCPM_SimRoI_core;
   vector<int>     *L1CaloCPM_SimRoI_emClus;
   vector<int>     *L1CaloCPM_SimRoI_tauClus;
   vector<int>     *L1CaloCPM_SimRoI_emIsol;
   vector<int>     *L1CaloCPM_SimRoI_hadIsol;
   vector<int>     *L1CaloCPM_SimRoI_hadVeto;
   vector<bool>    *L1CaloCPM_SimRoI_isEtMax;
   vector<unsigned int> *L1CaloCPM_SimRoI_hits;
   vector<unsigned int> *L1CaloCPM_SimRoI_roiWord;
   Int_t           L1CaloCPM_Hits_n;
   vector<int>     *L1CaloCPM_Hits_crate;
   vector<int>     *L1CaloCPM_Hits_module;
   vector<int>     *L1CaloCPM_Hits_peak;
   vector<unsigned int> *L1CaloCPM_Hits_hitWord0;
   vector<unsigned int> *L1CaloCPM_Hits_hitWord1;
   vector<vector<unsigned int> > *L1CaloCPM_Hits_hitsVec0;
   vector<vector<unsigned int> > *L1CaloCPM_Hits_hitsVec1;
   Int_t           L1CaloCPM_Towers_n;
   vector<double>  *L1CaloCPM_Towers_eta;
   vector<double>  *L1CaloCPM_Towers_phi;
   vector<int>     *L1CaloCPM_Towers_peak;
   vector<int>     *L1CaloCPM_Towers_emEnergy;
   vector<int>     *L1CaloCPM_Towers_hadEnergy;
   vector<vector<int> > *L1CaloCPM_Towers_emEnergyVec;
   vector<vector<int> > *L1CaloCPM_Towers_hadEnergyVec;
   vector<int>     *L1CaloCPM_Towers_emError;
   vector<int>     *L1CaloCPM_Towers_hadError;
   vector<vector<int> > *L1CaloCPM_Towers_emErrorVec;
   vector<vector<int> > *L1CaloCPM_Towers_hadErrorVec;
   Int_t           L1CaloCPM_CMM_n;
   vector<int>     *L1CaloCPM_CMM_crate;
   vector<int>     *L1CaloCPM_CMM_dataID;
   vector<unsigned int> *L1CaloCPM_CMM_hitWord0;
   vector<unsigned int> *L1CaloCPM_CMM_hitWord1;
   vector<int>     *L1CaloCPM_CMM_error0;
   vector<int>     *L1CaloCPM_CMM_error1;
   vector<int>     *L1CaloCPM_CMM_peak;
   vector<vector<unsigned int> > *L1CaloCPM_CMM_hitsVec0;
   vector<vector<unsigned int> > *L1CaloCPM_CMM_hitsVec1;
   vector<vector<int> > *L1CaloCPM_CMM_errorVec0;
   vector<vector<int> > *L1CaloCPM_CMM_errorVec1;
   Int_t           L1CaloJEM_JetEl_n;
   vector<double>  *L1CaloJEM_JetEl_eta;
   vector<double>  *L1CaloJEM_JetEl_phi;
   vector<int>     *L1CaloJEM_JetEl_emEnergy;
   vector<int>     *L1CaloJEM_JetEl_hadEnergy;
   vector<int>     *L1CaloJEM_JetEl_energy;
   vector<int>     *L1CaloJEM_JetEl_isSaturated;
   vector<int>     *L1CaloJEM_JetEl_isEmSaturated;
   vector<int>     *L1CaloJEM_JetEl_isHadSaturated;
   vector<int>     *L1CaloJEM_JetEl_emError;
   vector<int>     *L1CaloJEM_JetEl_hadError;
   vector<int>     *L1CaloJEM_JetEl_linkError;
   vector<int>     *L1CaloJEM_JetEl_peak;
   vector<vector<int> > *L1CaloJEM_JetEl_emEnergyVec;
   vector<vector<int> > *L1CaloJEM_JetEl_hadEnergyVec;
   vector<vector<int> > *L1CaloJEM_JetEl_emErrorVec;
   vector<vector<int> > *L1CaloJEM_JetEl_hadErrorVec;
   vector<vector<int> > *L1CaloJEM_JetEl_linkErrorVec;
   Int_t           L1CaloJEM_Hits_n;
   vector<int>     *L1CaloJEM_Hits_crate;
   vector<int>     *L1CaloJEM_Hits_module;
   vector<unsigned int> *L1CaloJEM_Hits_jetHits;
   vector<vector<unsigned int> > *L1CaloJEM_Hits_jetHitsVec;
   vector<int>     *L1CaloJEM_Hits_peak;
   vector<int>     *L1CaloJEM_Hits_forward;
   Int_t           L1CaloJEM_EtSums_n;
   vector<int>     *L1CaloJEM_EtSums_crate;
   vector<int>     *L1CaloJEM_EtSums_module;
   vector<unsigned int> *L1CaloJEM_EtSums_et;
   vector<unsigned int> *L1CaloJEM_EtSums_ex;
   vector<unsigned int> *L1CaloJEM_EtSums_ey;
   vector<vector<unsigned int> > *L1CaloJEM_EtSums_etVec;
   vector<vector<unsigned int> > *L1CaloJEM_EtSums_exVec;
   vector<vector<unsigned int> > *L1CaloJEM_EtSums_eyVec;
   vector<int>     *L1CaloJEM_EtSums_peak;
   vector<int>     *L1CaloJEM_EtSums_forward;
   Int_t           L1CaloJEM_CMMJetHits_n;
   vector<int>     *L1CaloJEM_CMMJetHits_crate;
   vector<int>     *L1CaloJEM_CMMJetHits_dataID;
   vector<unsigned int> *L1CaloJEM_CMMJetHits_hits;
   vector<int>     *L1CaloJEM_CMMJetHits_error;
   vector<vector<unsigned int> > *L1CaloJEM_CMMJetHits_hitsVec;
   vector<vector<int> > *L1CaloJEM_CMMJetHits_errorVec;
   vector<int>     *L1CaloJEM_CMMJetHits_peak;
   Int_t           L1CaloJEM_CMMEtSums_n;
   vector<int>     *L1CaloJEM_CMMEtSums_crate;
   vector<int>     *L1CaloJEM_CMMEtSums_dataID;
   vector<unsigned int> *L1CaloJEM_CMMEtSums_et;
   vector<unsigned int> *L1CaloJEM_CMMEtSums_ex;
   vector<unsigned int> *L1CaloJEM_CMMEtSums_ey;
   vector<int>     *L1CaloJEM_CMMEtSums_etError;
   vector<int>     *L1CaloJEM_CMMEtSums_exError;
   vector<int>     *L1CaloJEM_CMMEtSums_eyError;
   vector<vector<unsigned int> > *L1CaloJEM_CMMEtSums_etVec;
   vector<vector<unsigned int> > *L1CaloJEM_CMMEtSums_exVec;
   vector<vector<unsigned int> > *L1CaloJEM_CMMEtSums_eyVec;
   vector<vector<int> > *L1CaloJEM_CMMEtSums_etErrorVec;
   vector<vector<int> > *L1CaloJEM_CMMEtSums_exErrorVec;
   vector<vector<int> > *L1CaloJEM_CMMEtSums_eyErrorVec;
   vector<int>     *L1CaloJEM_CMMEtSums_peak;
   Int_t           L1CaloJEM_RoI_n;
   vector<int>     *L1CaloJEM_RoI_crate;
   vector<int>     *L1CaloJEM_RoI_jem;
   vector<int>     *L1CaloJEM_RoI_frame;
   vector<int>     *L1CaloJEM_RoI_location;
   vector<double>  *L1CaloJEM_RoI_eta;
   vector<double>  *L1CaloJEM_RoI_phi;
   vector<int>     *L1CaloJEM_RoI_forward;
   vector<int>     *L1CaloJEM_RoI_hits;
   vector<int>     *L1CaloJEM_RoI_error;
   Int_t           L1CaloJEM_CMMRoI_jetEtHits;
   Int_t           L1CaloJEM_CMMRoI_sumEtHits;
   Int_t           L1CaloJEM_CMMRoI_missingEtHits;
   Int_t           L1CaloJEM_CMMRoI_ex;
   Int_t           L1CaloJEM_CMMRoI_ey;
   Int_t           L1CaloJEM_CMMRoI_et;
   Int_t           L1CaloJEM_CMMRoI_jetEtError;
   Int_t           L1CaloJEM_CMMRoI_sumEtError;
   Int_t           L1CaloJEM_CMMRoI_missingEtError;
   Int_t           L1CaloJEM_CMMRoI_exError;
   Int_t           L1CaloJEM_CMMRoI_eyError;
   Int_t           L1CaloJEM_CMMRoI_etError;
   Int_t           L1CaloJEM_CMMRoI_jetEtRoiWord;
   UInt_t          L1CaloJEM_CMMRoI_energyEtRoiWord0;
   UInt_t          L1CaloJEM_CMMRoI_energyEtRoiWord1;
   UInt_t          L1CaloJEM_CMMRoI_energyEtRoiWord2;
   Int_t           L1CaloRODHeader_nHeaders;
   vector<int>     *L1CaloRODHeader_version;
   vector<int>     *L1CaloRODHeader_majorVersion;
   vector<int>     *L1CaloRODHeader_minorVersion;
   vector<int>     *L1CaloRODHeader_sourceID;
   vector<int>     *L1CaloRODHeader_subDetectorID;
   vector<int>     *L1CaloRODHeader_moduleID;
   vector<int>     *L1CaloRODHeader_crate;
   vector<int>     *L1CaloRODHeader_sLink;
   vector<int>     *L1CaloRODHeader_dataType;
   vector<int>     *L1CaloRODHeader_run;
   vector<int>     *L1CaloRODHeader_runType;
   vector<int>     *L1CaloRODHeader_runNumber;
   vector<int>     *L1CaloRODHeader_extendedL1ID;
   vector<int>     *L1CaloRODHeader_ecrID;
   vector<int>     *L1CaloRODHeader_l1ID;
   vector<int>     *L1CaloRODHeader_bunchCrossing;
   vector<int>     *L1CaloRODHeader_l1TriggerType;
   vector<int>     *L1CaloRODHeader_detEventType;
   vector<int>     *L1CaloRODHeader_orbitCount;
   vector<int>     *L1CaloRODHeader_stepNumber;
   vector<int>     *L1CaloRODHeader_stepType;
   vector<bool>    *L1CaloRODHeader_bcnMismatch;
   vector<bool>    *L1CaloRODHeader_gLinkTimeout;
   vector<bool>    *L1CaloRODHeader_dataTransportError;
   vector<bool>    *L1CaloRODHeader_rodFifoOverflow;
   vector<bool>    *L1CaloRODHeader_lvdsLinkError;
   vector<bool>    *L1CaloRODHeader_cmmParityError;
   vector<bool>    *L1CaloRODHeader_gLinkError;
   vector<bool>    *L1CaloRODHeader_limitedRoISet;
   vector<bool>    *L1CaloRODHeader_triggerTypeTimeout;
#endif

#ifndef L1CALO_ONLY
   Float_t         MemRSS;
   Float_t         MemVSize;
   Float_t         TimeTotal;
   Float_t         TimeSum;
   Float_t         TimeEventCounter;
   Float_t         TimeInDetPixelRawDataProvider;
   Float_t         TimeInDetSCTRawDataProvider;
   Float_t         TimeInDetTRTRawDataProvider;
   Float_t         TimeMuonMdtRawDataProvider;
   Float_t         TimeMuonRpcRawDataProvider;
   Float_t         TimeMuonTgcRawDataProvider;
   Float_t         TimeTrigConfDataIOVChanger;
   Float_t         TimeRoIBResultToAOD;
   Float_t         TimeTrigBSExtraction;
   Float_t         TimeTrigDecMaker;
   Float_t         TimeMainMonManager;
   Float_t         TimeInDetPixelClusterization;
   Float_t         TimeInDetSCT_Clusterization;
   Float_t         TimeInDetSiTrackerSpacePointFinder;
   Float_t         TimeSiCTBTracking;
   Float_t         TimePixel_CTBTracking;
   Float_t         TimeSCT_CTBTracking;
   Float_t         TimeInDetTRT_RIO_Maker;
   Float_t         TimeTRT_CTBTrackingPhase;
   Float_t         TimeTRTSegmentsFinder_ECphase;
   Float_t         TimeInDetCosmicsEventPhase;
   Float_t         TimeInDetTRT_RIO_MakerCosmics;
   Float_t         TimeInDetCTBTracking;
   Float_t         TimeTRT_CTBTracking;
   Float_t         TimeTRTSegmentsFinderBC;
   Float_t         TimeTRTSegmentsFinder_EC;
   Float_t         TimeTRT_SegmentsToTrack_Endcap;
   Float_t         TimeIdTrackCopyAmbiSolver_0;
   Float_t         TimeIdTrackCopyAmbiSolver_1;
   Float_t         TimeIdTrackCopyAmbiSolver_2;
   Float_t         TimeIdTrackCopyAmbiSolver_3;
   Float_t         TimeIdTrackCopyAmbiSolver_4;
   Float_t         TimeIdTrackCopyAmbiSolver_final;
   Float_t         TimeInDetTrackCollectionMerger;
   Float_t         TimeInDetCopyAlg;
   Float_t         TimeInDetParticleCreation;
   Float_t         TimeTileRChMaker;
   Float_t         TimeLArRawChannelBuilder;
   Float_t         TimeLArDigitThinner;
   Float_t         TimeTileDigitsFilter;
   Float_t         TimeCaloCellMaker;
   Float_t         TimeEmTowerBldr;
   Float_t         TimeLArClusterMaker;
   Float_t         TimeLAr7_11NocorrClusterMaker;
   Float_t         TimeCaloTopoCluster;
   Float_t         TimeCaloCell2TopoClusterMapper;
   Float_t         TimeCaloClusterTopoEM430Getter;
   Float_t         TimeEMCell2TopoCluster430;
   Float_t         TimeTileLookForMuAlg;
   Float_t         TimeTileMuonFitter;
   Float_t         TimeMdtRdoToMdtPrepData;
   Float_t         TimeRpcRdoToRpcPrepData;
   Float_t         TimeTgcRdoToTgcPrepData;
   Float_t         TimeRpcClusterBuilderPRD;
   Float_t         TimeMboyDigiEmptyLoop;
   Float_t         TimeMboyRec;
   Float_t         TimeMooSegmentMaker;
   Float_t         TimeMuonCombiTrackBuilder;
   Float_t         TimeMuidMooreTPCreator;
   Float_t         TimeInitializeMuonClusters;
   Float_t         TimeCaloTrkMuIdAlg;
   Float_t         TimeCaloTrkMuIdAlg2;
   Float_t         TimeMuTagMasterIMO;
   Float_t         TimeCombMuonRefit;
   Float_t         TimeMergeMuonCollections;
   Float_t         TimeMakeAODMuons;
   Float_t         TimeFinalizeMuonClusters;
   Float_t         TimeCmbTowerBldr;
   Float_t         TimeTowerJetInput;
   Float_t         TimeCone4H1TowerJets;
   Float_t         TimeMETAlg;
   Float_t         TimeInDetGlobalManager;
   Float_t         TimePixelMonManager;
   Float_t         TimeSCTMonManager;
   Float_t         TimeTRTMonManager;
   Float_t         TimeIDAlignMonManager;
   Float_t         TimeGlobalMonManager;
   Float_t         TimeJetElementMaker;
   Float_t         TimeCPMTowerMaker;
   Float_t         TimeEmTauTrigger;
   Float_t         TimeEnergyTrigger;
   Float_t         TimeJetTrigger;
   Float_t         TimeROD;
   Float_t         TimeJEPCMMMaker;
   Float_t         TimeCPCMMMaker;
   Float_t         TimeL1CaloMonManager;
   Float_t         TimeTriggerTowerMaker;
   Float_t         TimeL1MonManager;
   Float_t         TimeCTMonManager;
   Float_t         TimeHLTMonManager;
   Float_t         TimeTileTowerBldr;
   Float_t         TimeTileTopoCluster;
   Float_t         TimeTileCell2TopoClusterMapper;
   Float_t         TimeManagedAthenaTileMon;
   Float_t         TimeLArMonManager;
   Float_t         TimeJetMonManager;
   Float_t         TimeJetTagMonManager;
   Float_t         TimeMuonRawMonManager;
   Float_t         TimeCBNT_AthenaAware;
   Float_t         TimeCreateLumiBlockCollectionFromFile;
   Float_t         TimeStreamESD;
   Float_t         TimeStreamESD_FH;
   Float_t         TimeStream2Filter;
   Float_t         TimeComTagWriter;
   Float_t         TimeStreamTAGCOM;
   Float_t         TimeAANTupleStream;
#endif

   // List of branches
   TBranch        *b_RunNumber;   //!
   TBranch        *b_EventNumber;   //!
#ifndef L1CALO_ONLY
   TBranch        *b_StreamESD_ref;   //!
#endif
   TBranch        *b_Token;   //!
   TBranch        *b_Run;   //!
   TBranch        *b_Event;   //!
   TBranch        *b_Time;   //!
   TBranch        *b_LumiBlock;   //!
   TBranch        *b_BCID;   //!
   TBranch        *b_LVL1ID;   //!
   TBranch        *b_Weight;   //!
   TBranch        *b_IEvent;   //!
   TBranch        *b_StatusElement;   //!
   TBranch        *b_LVL1TriggerType;   //!
   TBranch        *b_LVL1TriggerInfo;   //!
   TBranch        *b_LVL2TriggerInfo;   //!
   TBranch        *b_EventFilterInfo;   //!
   TBranch        *b_StreamTagName;   //!
   TBranch        *b_StreamTagType;   //!

#ifndef L1CALO_ONLY
   TBranch        *b_pixel_nhits;   //!
   TBranch        *b_pixel_bec;   //!
   TBranch        *b_pixel_layer;   //!
   TBranch        *b_pixel_eta;   //!
   TBranch        *b_pixel_phi;   //!
   TBranch        *b_pixel_row;   //!
   TBranch        *b_pixel_col;   //!
   TBranch        *b_pixel_tot;   //!
   TBranch        *b_pixel_BCID;   //!
   TBranch        *b_pixel_LVL1;   //!
   TBranch        *b_sct_rdo_nhits;   //!
   TBranch        *b_sct_rdo_strips;   //!
   TBranch        *b_sct_rdo_tbin;   //!
   TBranch        *b_sct_rdo_rdoId;   //!
   TBranch        *b_sct_rdo_bec;   //!
   TBranch        *b_sct_rdo_layer;   //!
   TBranch        *b_sct_rdo_eta;   //!
   TBranch        *b_sct_rdo_phi;   //!
   TBranch        *b_sct_rdo_side;   //!
   TBranch        *b_sct_rdo_FirstSecondHitError;   //!
   TBranch        *b_tdc_ntdcs;   //!
   TBranch        *b_tdc_channel;   //!
   TBranch        *b_tdc_phase;   //!
   TBranch        *b_sct_bsErr_nErrs;   //!
   TBranch        *b_sct_bsErr_type;   //!
   TBranch        *b_sct_bsErr_eta;   //!
   TBranch        *b_sct_bsErr_phi;   //!
   TBranch        *b_sct_bsErr_layer;   //!
   TBranch        *b_sct_bsErr_side;   //!
   TBranch        *b_sct_bsErr_bec;   //!
   TBranch        *b_sct_clus_nclusters;   //!
   TBranch        *b_sct_clus_x;   //!
   TBranch        *b_sct_clus_y;   //!
   TBranch        *b_sct_clus_z;   //!
   TBranch        *b_sct_clus_groupsize;   //!
   TBranch        *b_sct_clus_bec;   //!
   TBranch        *b_sct_clus_layer;   //!
   TBranch        *b_sct_clus_eta;   //!
   TBranch        *b_sct_clus_phi;   //!
   TBranch        *b_sct_clus_side;   //!
   TBranch        *b_pixel_clus_nclusters;   //!
   TBranch        *b_pixel_clus_LocX;   //!
   TBranch        *b_pixel_clus_LocY;   //!
   TBranch        *b_pixel_clus_z;   //!
   TBranch        *b_pixel_clus_groupsize;   //!
   TBranch        *b_pixel_clus_bec;   //!
   TBranch        *b_pixel_clus_layer;   //!
   TBranch        *b_pixel_clus_phi;   //!
   TBranch        *b_pixel_clus_clx;   //!
   TBranch        *b_pixel_clus_cly;   //!
   TBranch        *b_pixel_clus_clz;   //!
   TBranch        *b_pixel_clus_row;   //!
   TBranch        *b_pixel_clus_col;   //!
   TBranch        *b_sct_sp_nspacepoints;   //!
   TBranch        *b_sct_sp_x;   //!
   TBranch        *b_sct_sp_y;   //!
   TBranch        *b_sct_sp_z;   //!
   TBranch        *b_sct_sp_barrelendcap;   //!
   TBranch        *b_sct_sp_layer;   //!
   TBranch        *b_sct_sp_phi;   //!
   TBranch        *b_sct_sp_eta;   //!
   TBranch        *b_pixel_sp_nspacepoints;   //!
   TBranch        *b_pixel_sp_x;   //!
   TBranch        *b_pixel_sp_y;   //!
   TBranch        *b_pixel_sp_z;   //!
   TBranch        *b_pixel_sp_barrelendcap;   //!
   TBranch        *b_pixel_sp_layer;   //!
   TBranch        *b_pixel_sp_phi;   //!
   TBranch        *b_pixel_sp_eta;   //!
   TBranch        *b_trk_nTracks;   //!
   TBranch        *b_trk_nPixelHits;   //!
   TBranch        *b_trk_nSctHits;   //!
   TBranch        *b_trk_nTrtHits;   //!
   TBranch        *b_trk_PixResPhi;   //!
   TBranch        *b_trk_PixResEta;   //!
   TBranch        *b_trk_PixPullPhi;   //!
   TBranch        *b_trk_PixPullEta;   //!
   TBranch        *b_trk_PixErrTrkPhi;   //!
   TBranch        *b_trk_PixErrTrkEta;   //!
   TBranch        *b_trk_PixErrHitPhi;   //!
   TBranch        *b_trk_PixErrHitEta;   //!
   TBranch        *b_trk_Pix_bec;   //!
   TBranch        *b_trk_Pix_layer;   //!
   TBranch        *b_trk_Pix_eta;   //!
   TBranch        *b_trk_Pix_phi;   //!
   TBranch        *b_trk_Pix_clusWidthRow;   //!
   TBranch        *b_trk_Pix_clusWidthCol;   //!
   TBranch        *b_trk_Pix_LocX;   //!
   TBranch        *b_trk_Pix_LocY;   //!
   TBranch        *b_trk_SctRes;   //!
   TBranch        *b_trk_SctPull;   //!
   TBranch        *b_trk_SctErrTrk;   //!
   TBranch        *b_trk_SctErrHit;   //!
   TBranch        *b_trk_Sct_bec;   //!
   TBranch        *b_trk_Sct_layer;   //!
   TBranch        *b_trk_Sct_eta;   //!
   TBranch        *b_trk_Sct_phi;   //!
   TBranch        *b_trk_Sct_side;   //!
   TBranch        *b_trk_Sct_rdoId;   //!
   TBranch        *b_trk_Sct_clusGroupsize;   //!
   TBranch        *b_trk_Sct_clusx;   //!
   TBranch        *b_trk_Sct_clusy;   //!
   TBranch        *b_trk_Sct_clusz;   //!
   TBranch        *b_trk_TrtRes;   //!
   TBranch        *b_trk_TrtPull;   //!
   TBranch        *b_trk_TrtErrTrk;   //!
   TBranch        *b_trk_TrtErrHit;   //!
   TBranch        *b_trk_Trt_R;   //!
   TBranch        *b_trk_Trt_Rtrack;   //!
   TBranch        *b_trk_Trt_t;   //!
   TBranch        *b_trk_Trt_x;   //!
   TBranch        *b_trk_Trt_y;   //!
   TBranch        *b_trk_Trt_HL;   //!
   TBranch        *b_trk_Trt_strawlayer;   //!
   TBranch        *b_trk_Trt_bec;   //!
   TBranch        *b_trk_Trt_layer;   //!
   TBranch        *b_trk_Trt_straw;   //!
   TBranch        *b_trk_Trt_phisector;   //!
   TBranch        *b_trk_Rec_d0;   //!
   TBranch        *b_trk_Rec_z0;   //!
   TBranch        *b_trk_Rec_phi0;   //!
   TBranch        *b_trk_Rec_theta0;   //!
   TBranch        *b_trk_Rec_qoverp;   //!
   TBranch        *b_trk_Rec_chi2;   //!
   TBranch        *b_trk_Rec_ndof;   //!
   TBranch        *b_trk_Rec_eta;   //!
   TBranch        *b_trk_Rec_error_d0;   //!
   TBranch        *b_trk_Rec_error_z0;   //!
   TBranch        *b_trk_Rec_error_phi0;   //!
   TBranch        *b_trk_Rec_error_theta0;   //!
   TBranch        *b_trk_Rec_error_qoverp;   //!
   TBranch        *b_trk_Rec_chi2prob;   //!
   TBranch        *b_trk_Rec_author;   //!
   TBranch        *b_Nh_Calo;   //!
   TBranch        *b_Eh_Calo;   //!
   TBranch        *b_Nh_EM;   //!
   TBranch        *b_Eh_EM;   //!
   TBranch        *b_Nh_HAD;   //!
   TBranch        *b_Eh_HAD;   //!
   TBranch        *b_Nh_PresB;   //!
   TBranch        *b_Eh_PresB;   //!
   TBranch        *b_Nh_EMB;   //!
   TBranch        *b_Eh_EMB;   //!
   TBranch        *b_Nh_EMEC;   //!
   TBranch        *b_Eh_EMEC;   //!
   TBranch        *b_Nh_Tile;   //!
   TBranch        *b_Eh_Tile;   //!
   TBranch        *b_Nh_TileGap;   //!
   TBranch        *b_Eh_TileGap;   //!
   TBranch        *b_Nh_HEC;   //!
   TBranch        *b_Eh_HEC;   //!
   TBranch        *b_Nh_FCal;   //!
   TBranch        *b_Eh_FCal;   //!
   TBranch        *b_Nh_PresE;   //!
   TBranch        *b_Eh_PresE;   //!
   TBranch        *b_Nh_Scint;   //!
   TBranch        *b_Eh_Scint;   //!
   TBranch        *b_nhitLAr;   //!
   TBranch        *b_ecellLAr;   //!
   TBranch        *b_NCellsLAr;   //!
   TBranch        *b_ECellsLAr;   //!
   TBranch        *b_EtaCellsLAr;   //!
   TBranch        *b_PhiCellsLAr;   //!
   TBranch        *b_QCellsLAr;   //!
   TBranch        *b_GainCellsLAr;   //!
   TBranch        *b_DetCellsLAr;   //!
   TBranch        *b_TimeCellsLAr;   //!
   TBranch        *b_BadCellsLAr;   //!
   TBranch        *b_IdCellsLAr;   //!
   TBranch        *b_icell;   //!
   TBranch        *b_LArDigit_layer;   //!
   TBranch        *b_LArDigit_ieta;   //!
   TBranch        *b_LArDigit_calo;   //!
   TBranch        *b_LArDigit_iphi;   //!
   TBranch        *b_LArDigit_barrel_ec;   //!
   TBranch        *b_LArDigit_pos_neg;   //!
   TBranch        *b_LArDigit_FT;   //!
   TBranch        *b_LArDigit_slot;   //!
   TBranch        *b_LArDigit_channel;   //!
   TBranch        *b_LArDigit_gain;   //!
   TBranch        *b_NSamples;   //!
   TBranch        *b_LArDigit_Samples;   //!
   TBranch        *b_LArDigit_offlineId;   //!
   TBranch        *b_TileCellEtot;   //!
   TBranch        *b_TileMBTSETot;   //!
   TBranch        *b_TileMBTSETotA;   //!
   TBranch        *b_TileMBTSETotC;   //!
   TBranch        *b_TileCellN;   //!
   TBranch        *b_TileCellE;   //!
   TBranch        *b_TileCellTime;   //!
   TBranch        *b_TileCellEta;   //!
   TBranch        *b_TileCellPhi;   //!
   TBranch        *b_TileMBTSCounter;   //!
   TBranch        *b_TileMBTSE;   //!
   TBranch        *b_TileMBTSTime;   //!
   TBranch        *b_TileMBTSQuality;   //!
   TBranch        *b_TileMBTSEta;   //!
   TBranch        *b_TileMBTSPhi;   //!
   TBranch        *b_TileCellX;   //!
   TBranch        *b_TileCellY;   //!
   TBranch        *b_TileCellZ;   //!
   TBranch        *b_TileMBTSX;   //!
   TBranch        *b_TileMBTSY;   //!
   TBranch        *b_TileMBTSZ;   //!
   TBranch        *b_TileCellEdiff;   //!
   TBranch        *b_TileCellTimediff;   //!
   TBranch        *b_TileCellGain1;   //!
   TBranch        *b_TileCellGain2;   //!
   TBranch        *b_TileCellModule;   //!
   TBranch        *b_TileCellPartition;   //!
   TBranch        *b_TileCellTower;   //!
   TBranch        *b_TileCellSample;   //!
   TBranch        *b_TileCellChan1;   //!
   TBranch        *b_TileCellChan2;   //!
   TBranch        *b_TileCellPMT1;   //!
   TBranch        *b_TileCellPMT2;   //!
   TBranch        *b_TileCellStatus1;   //!
   TBranch        *b_TileCellStatus2;   //!
   TBranch        *b_TileMBTSModule;   //!
   TBranch        *b_TileMBTSGain;   //!
   TBranch        *b_TileMBTSStatus;   //!
   TBranch        *b_cl_ecluster;   //!
   TBranch        *b_cl_nctotal;   //!
   TBranch        *b_cl_nc;   //!
   TBranch        *b_cl_et;   //!
   TBranch        *b_cl_e;   //!
   TBranch        *b_cl_eemb0;   //!
   TBranch        *b_cl_eemb1;   //!
   TBranch        *b_cl_eemb2;   //!
   TBranch        *b_cl_eemb3;   //!
   TBranch        *b_cl_nemb0;   //!
   TBranch        *b_cl_nemb1;   //!
   TBranch        *b_cl_nemb2;   //!
   TBranch        *b_cl_nemb3;   //!
   TBranch        *b_cl_phi2;   //!
   TBranch        *b_cl_eta0;   //!
   TBranch        *b_cl_eta1;   //!
   TBranch        *b_cl_eta2;   //!
   TBranch        *b_cl_eta3;   //!
   TBranch        *b_cl_eeme0;   //!
   TBranch        *b_cl_eeme1;   //!
   TBranch        *b_cl_eeme2;   //!
   TBranch        *b_cl_eeme3;   //!
   TBranch        *b_cl_neme0;   //!
   TBranch        *b_cl_neme1;   //!
   TBranch        *b_cl_neme2;   //!
   TBranch        *b_cl_neme3;   //!
   TBranch        *b_cl_etileg1;   //!
   TBranch        *b_cl_etileg2;   //!
   TBranch        *b_cl_etileg3;   //!
   TBranch        *b_cl_ntileg1;   //!
   TBranch        *b_cl_ntileg2;   //!
   TBranch        *b_cl_ntileg3;   //!
   TBranch        *b_cl_eta;   //!
   TBranch        *b_cl_phi;   //!
   TBranch        *b_cl_reco_stat;   //!
   TBranch        *b_cl_m1_eta;   //!
   TBranch        *b_cl_m1_phi;   //!
   TBranch        *b_cl_m2_r;   //!
   TBranch        *b_cl_m2_lambda;   //!
   TBranch        *b_cl_delta_phi;   //!
   TBranch        *b_cl_delta_theta;   //!
   TBranch        *b_cl_delta_alpha;   //!
   TBranch        *b_cl_center_x;   //!
   TBranch        *b_cl_center_y;   //!
   TBranch        *b_cl_center_z;   //!
   TBranch        *b_cl_center_lambda;   //!
   TBranch        *b_cl_lateral;   //!
   TBranch        *b_cl_longitudinal;   //!
   TBranch        *b_cl_eng_frac_em;   //!
   TBranch        *b_cl_eng_frac_max;   //!
   TBranch        *b_cl_eng_frac_core;   //!
   TBranch        *b_cl_m1_dens;   //!
   TBranch        *b_cl_m2_dens;   //!
   TBranch        *b_cl_isol;   //!
   TBranch        *b_cl_ntotcells;   //!
   TBranch        *b_cl_ecluster_topo;   //!
   TBranch        *b_cl_nctotal_topo;   //!
   TBranch        *b_cl_nc_topo;   //!
   TBranch        *b_cl_et_topo;   //!
   TBranch        *b_cl_e_topo;   //!
   TBranch        *b_cl_eemb0_topo;   //!
   TBranch        *b_cl_eemb1_topo;   //!
   TBranch        *b_cl_eemb2_topo;   //!
   TBranch        *b_cl_eemb3_topo;   //!
   TBranch        *b_cl_nemb0_topo;   //!
   TBranch        *b_cl_nemb1_topo;   //!
   TBranch        *b_cl_nemb2_topo;   //!
   TBranch        *b_cl_nemb3_topo;   //!
   TBranch        *b_cl_phi2_topo;   //!
   TBranch        *b_cl_eta0_topo;   //!
   TBranch        *b_cl_eta1_topo;   //!
   TBranch        *b_cl_eta2_topo;   //!
   TBranch        *b_cl_eta3_topo;   //!
   TBranch        *b_cl_eeme0_topo;   //!
   TBranch        *b_cl_eeme1_topo;   //!
   TBranch        *b_cl_eeme2_topo;   //!
   TBranch        *b_cl_eeme3_topo;   //!
   TBranch        *b_cl_neme0_topo;   //!
   TBranch        *b_cl_neme1_topo;   //!
   TBranch        *b_cl_neme2_topo;   //!
   TBranch        *b_cl_neme3_topo;   //!
   TBranch        *b_cl_etileg1_topo;   //!
   TBranch        *b_cl_etileg2_topo;   //!
   TBranch        *b_cl_etileg3_topo;   //!
   TBranch        *b_cl_ntileg1_topo;   //!
   TBranch        *b_cl_ntileg2_topo;   //!
   TBranch        *b_cl_ntileg3_topo;   //!
   TBranch        *b_cl_eta_topo;   //!
   TBranch        *b_cl_phi_topo;   //!
   TBranch        *b_cl_reco_stat_topo;   //!
   TBranch        *b_cl_m1_eta_topo;   //!
   TBranch        *b_cl_m1_phi_topo;   //!
   TBranch        *b_cl_m2_r_topo;   //!
   TBranch        *b_cl_m2_lambda_topo;   //!
   TBranch        *b_cl_delta_phi_topo;   //!
   TBranch        *b_cl_delta_theta_topo;   //!
   TBranch        *b_cl_delta_alpha_topo;   //!
   TBranch        *b_cl_center_x_topo;   //!
   TBranch        *b_cl_center_y_topo;   //!
   TBranch        *b_cl_center_z_topo;   //!
   TBranch        *b_cl_center_lambda_topo;   //!
   TBranch        *b_cl_lateral_topo;   //!
   TBranch        *b_cl_longitudinal_topo;   //!
   TBranch        *b_cl_eng_frac_em_topo;   //!
   TBranch        *b_cl_eng_frac_max_topo;   //!
   TBranch        *b_cl_eng_frac_core_topo;   //!
   TBranch        *b_cl_m1_dens_topo;   //!
   TBranch        *b_cl_m2_dens_topo;   //!
   TBranch        *b_cl_isol_topo;   //!
   TBranch        *b_cl_ehec0_topo;   //!
   TBranch        *b_cl_ehec1_topo;   //!
   TBranch        *b_cl_ehec2_topo;   //!
   TBranch        *b_cl_ehec3_topo;   //!
   TBranch        *b_cl_nhec0_topo;   //!
   TBranch        *b_cl_nhec1_topo;   //!
   TBranch        *b_cl_nhec2_topo;   //!
   TBranch        *b_cl_nhec3_topo;   //!
   TBranch        *b_cl_etileb0_topo;   //!
   TBranch        *b_cl_etileb1_topo;   //!
   TBranch        *b_cl_etileb2_topo;   //!
   TBranch        *b_cl_ntileb0_topo;   //!
   TBranch        *b_cl_ntileb1_topo;   //!
   TBranch        *b_cl_ntileb2_topo;   //!
   TBranch        *b_cl_etilee0_topo;   //!
   TBranch        *b_cl_etilee1_topo;   //!
   TBranch        *b_cl_etilee2_topo;   //!
   TBranch        *b_cl_efcal0_topo;   //!
   TBranch        *b_cl_efcal1_topo;   //!
   TBranch        *b_cl_efcal2_topo;   //!
   TBranch        *b_cl_ntilee0_topo;   //!
   TBranch        *b_cl_ntilee1_topo;   //!
   TBranch        *b_cl_ntilee2_topo;   //!
   TBranch        *b_cl_nfcal0_topo;   //!
   TBranch        *b_cl_nfcal1_topo;   //!
   TBranch        *b_cl_nfcal2_topo;   //!
   TBranch        *b_cl_ntotcells_topo;   //!
   TBranch        *b_cl_ecluster_topoEM430;   //!
   TBranch        *b_cl_nctotal_topoEM430;   //!
   TBranch        *b_cl_nc_topoEM430;   //!
   TBranch        *b_cl_et_topoEM430;   //!
   TBranch        *b_cl_e_topoEM430;   //!
   TBranch        *b_cl_eemb0_topoEM430;   //!
   TBranch        *b_cl_eemb1_topoEM430;   //!
   TBranch        *b_cl_eemb2_topoEM430;   //!
   TBranch        *b_cl_eemb3_topoEM430;   //!
   TBranch        *b_cl_nemb0_topoEM430;   //!
   TBranch        *b_cl_nemb1_topoEM430;   //!
   TBranch        *b_cl_nemb2_topoEM430;   //!
   TBranch        *b_cl_nemb3_topoEM430;   //!
   TBranch        *b_cl_phi2_topoEM430;   //!
   TBranch        *b_cl_eta0_topoEM430;   //!
   TBranch        *b_cl_eta1_topoEM430;   //!
   TBranch        *b_cl_eta2_topoEM430;   //!
   TBranch        *b_cl_eta3_topoEM430;   //!
   TBranch        *b_cl_eeme0_topoEM430;   //!
   TBranch        *b_cl_eeme1_topoEM430;   //!
   TBranch        *b_cl_eeme2_topoEM430;   //!
   TBranch        *b_cl_eeme3_topoEM430;   //!
   TBranch        *b_cl_neme0_topoEM430;   //!
   TBranch        *b_cl_neme1_topoEM430;   //!
   TBranch        *b_cl_neme2_topoEM430;   //!
   TBranch        *b_cl_neme3_topoEM430;   //!
   TBranch        *b_cl_etileg1_topoEM430;   //!
   TBranch        *b_cl_etileg2_topoEM430;   //!
   TBranch        *b_cl_etileg3_topoEM430;   //!
   TBranch        *b_cl_ntileg1_topoEM430;   //!
   TBranch        *b_cl_ntileg2_topoEM430;   //!
   TBranch        *b_cl_ntileg3_topoEM430;   //!
   TBranch        *b_cl_eta_topoEM430;   //!
   TBranch        *b_cl_phi_topoEM430;   //!
   TBranch        *b_cl_reco_stat_topoEM430;   //!
   TBranch        *b_cl_m1_eta_topoEM430;   //!
   TBranch        *b_cl_m1_phi_topoEM430;   //!
   TBranch        *b_cl_m2_r_topoEM430;   //!
   TBranch        *b_cl_m2_lambda_topoEM430;   //!
   TBranch        *b_cl_delta_phi_topoEM430;   //!
   TBranch        *b_cl_delta_theta_topoEM430;   //!
   TBranch        *b_cl_delta_alpha_topoEM430;   //!
   TBranch        *b_cl_center_x_topoEM430;   //!
   TBranch        *b_cl_center_y_topoEM430;   //!
   TBranch        *b_cl_center_z_topoEM430;   //!
   TBranch        *b_cl_center_lambda_topoEM430;   //!
   TBranch        *b_cl_lateral_topoEM430;   //!
   TBranch        *b_cl_longitudinal_topoEM430;   //!
   TBranch        *b_cl_eng_frac_em_topoEM430;   //!
   TBranch        *b_cl_eng_frac_max_topoEM430;   //!
   TBranch        *b_cl_eng_frac_core_topoEM430;   //!
   TBranch        *b_cl_m1_dens_topoEM430;   //!
   TBranch        *b_cl_m2_dens_topoEM430;   //!
   TBranch        *b_cl_isol_topoEM430;   //!
   TBranch        *b_cl_ntotcells_topoEM430;   //!
   TBranch        *b_NTileMuonTag;   //!
   TBranch        *b_EtaTileMuonTag;   //!
   TBranch        *b_PhiTileMuonTag;   //!
   TBranch        *b_EnergyVecTileMuonTag;   //!
   TBranch        *b_LabelTileMuonTag;   //!
   TBranch        *b_TileCosmicsHT_x;   //!
   TBranch        *b_TileCosmicsHT_y;   //!
   TBranch        *b_TileCosmicsHT_z;   //!
   TBranch        *b_TileCosmicsHT_phi;   //!
   TBranch        *b_TileCosmicsHT_theta;   //!
   TBranch        *b_TileCosmicsHT_time;   //!
   TBranch        *b_TileCosmicsHT_fitQuality;   //!
   TBranch        *b_TileCosmicsHT_fitCells;   //!
   TBranch        *b_TileCosmicsHT_path;   //!
   TBranch        *b_TileCosmicsHT_energy;   //!
   TBranch        *b_TileCosmicsHT_pathTop;   //!
   TBranch        *b_TileCosmicsHT_pathBottom;   //!
   TBranch        *b_TileCosmicsHT_energyTop;   //!
   TBranch        *b_TileCosmicsHT_energyBottom;   //!
   TBranch        *b_TileCosmicsHT_trackCellN;   //!
   TBranch        *b_TileCosmicsHT_cellE;   //!
   TBranch        *b_TileCosmicsHT_cellT;   //!
   TBranch        *b_TileCosmicsHT_cellEta;   //!
   TBranch        *b_TileCosmicsHT_cellPhi;   //!
   TBranch        *b_TileCosmicsHT_cellSample;   //!
   TBranch        *b_TileCosmicsHT_cellEdiff;   //!
   TBranch        *b_TileCosmicsHT_cellTdiff;   //!
   TBranch        *b_NTileMuonRODTag;   //!
   TBranch        *b_EtaTileMuonRODTag;   //!
   TBranch        *b_PhiTileMuonRODTag;   //!
   TBranch        *b_EnergyVecTileMuonRODTag;   //!
   TBranch        *b_LabelTileMuonRODTag;   //!
   TBranch        *b_m_nMdtColl;   //!
   TBranch        *b_m_nMdtPrd;   //!
   TBranch        *b_mdt_tdc;   //!
   TBranch        *b_mdt_adc;   //!
   TBranch        *b_mdt_station;   //!
   TBranch        *b_mdt_eta;   //!
   TBranch        *b_mdt_phi;   //!
   TBranch        *b_mdt_multi;   //!
   TBranch        *b_mdt_layer;   //!
   TBranch        *b_mdt_wire;   //!
   TBranch        *b_mdt_nmaxtubes;   //!
   TBranch        *b_mdt_globPosX;   //!
   TBranch        *b_mdt_globPosY;   //!
   TBranch        *b_mdt_globPosZ;   //!
   TBranch        *b_m_nCsm;   //!
   TBranch        *b_m_nAmt;   //!
   TBranch        *b_mdt_subid;   //!
   TBranch        *b_mdt_rodid;   //!
   TBranch        *b_mdt_csmid;   //!
   TBranch        *b_mdt_tdcid;   //!
   TBranch        *b_mdt_chanid;   //!
   TBranch        *b_mdt_fine;   //!
   TBranch        *b_mdt_coarse;   //!
   TBranch        *b_mdt_width;   //!
   TBranch        *b_m_nRpcColl;   //!
   TBranch        *b_m_nRpcPrd;   //!
   TBranch        *b_rpc_prd_station;   //!
   TBranch        *b_rpc_prd_eta;   //!
   TBranch        *b_rpc_prd_phi;   //!
   TBranch        *b_rpc_prd_doublr;   //!
   TBranch        *b_rpc_prd_doublz;   //!
   TBranch        *b_rpc_prd_doublphi;   //!
   TBranch        *b_rpc_prd_gasgap;   //!
   TBranch        *b_rpc_prd_measphi;   //!
   TBranch        *b_rpc_prd_strip;   //!
   TBranch        *b_rpc_prd_time;   //!
   TBranch        *b_rpc_prd_stripx;   //!
   TBranch        *b_rpc_prd_stripy;   //!
   TBranch        *b_rpc_prd_stripz;   //!
   TBranch        *b_rpc_prd_triggerInfo;   //!
   TBranch        *b_rpc_prd_ambigFlag;   //!
   TBranch        *b_m_nClus;   //!
   TBranch        *b_rpc_clus_station;   //!
   TBranch        *b_rpc_clus_eta;   //!
   TBranch        *b_rpc_clus_phi;   //!
   TBranch        *b_rpc_clus_doublr;   //!
   TBranch        *b_rpc_clus_doublz;   //!
   TBranch        *b_rpc_clus_doublphi;   //!
   TBranch        *b_rpc_clus_gasgap;   //!
   TBranch        *b_rpc_clus_measphi;   //!
   TBranch        *b_rpc_clus_size;   //!
   TBranch        *b_rpc_clus_time;   //!
   TBranch        *b_rpc_clus_posx;   //!
   TBranch        *b_rpc_clus_posy;   //!
   TBranch        *b_rpc_clus_posz;   //!
   TBranch        *b_m_nPads;   //!
   TBranch        *b_rpc_pad_id;   //!
   TBranch        *b_rpc_pad_bcid;   //!
   TBranch        *b_rpc_pad_lvl1id;   //!
   TBranch        *b_rpc_pad_sectorid;   //!
   TBranch        *b_rpc_pad_status;   //!
   TBranch        *b_rpc_pad_error;   //!
   TBranch        *b_m_nCMA;   //!
   TBranch        *b_m_nFiredChannels;   //!
   TBranch        *b_rpc_sector;   //!
   TBranch        *b_rpc_padId;   //!
   TBranch        *b_rpc_status;   //!
   TBranch        *b_rpc_ercode;   //!
   TBranch        *b_rpc_cmaId;   //!
   TBranch        *b_rpc_fel1Id;   //!
   TBranch        *b_rpc_febcId;   //!
   TBranch        *b_rpc_crc;   //!
   TBranch        *b_rpc_bcId;   //!
   TBranch        *b_rpc_ticks;   //!
   TBranch        *b_rpc_ijk;   //!
   TBranch        *b_rpc_cmachan;   //!
   TBranch        *b_rpc_overlap;   //!
   TBranch        *b_rpc_threshold;   //!
   TBranch        *b_m_SL_nSectors;   //!
   TBranch        *b_rpc_SL_sectorId;   //!
   TBranch        *b_rpc_SL_bcid;   //!
   TBranch        *b_rpc_SL_lvl1id;   //!
   TBranch        *b_m_SL_nTriggerHits;   //!
   TBranch        *b_rpc_SLhit_sector;   //!
   TBranch        *b_rpc_SLhit_rowinBcid;   //!
   TBranch        *b_rpc_SLhit_triggerBcid;   //!
   TBranch        *b_rpc_SLhit_padId;   //!
   TBranch        *b_rpc_SLhit_ptId;   //!
   TBranch        *b_rpc_SLhit_roi;   //!
   TBranch        *b_rpc_SLhit_outerPlane;   //!
   TBranch        *b_rpc_SLhit_overlapPhi;   //!
   TBranch        *b_rpc_SLhit_overlapEta;   //!
   TBranch        *b_tgc_bcTag;   //!
   TBranch        *b_tgc_cointrackletbcTag;   //!
   TBranch        *b_tgc_coinhighptbcTag;   //!
   TBranch        *b_tgc_coinslbcTag;   //!
   TBranch        *b_tgc_cointype;   //!
   TBranch        *b_tgc_cointype_Prev;   //!
   TBranch        *b_tgc_cointype_Next;   //!
   TBranch        *b_m_nTgcColl;   //!
   TBranch        *b_m_nTgcPrd;   //!
   TBranch        *b_tgc_station;   //!
   TBranch        *b_tgc_eta;   //!
   TBranch        *b_tgc_phi;   //!
   TBranch        *b_tgc_gasGap;   //!
   TBranch        *b_tgc_isStrip;   //!
   TBranch        *b_tgc_channel;   //!
   TBranch        *b_tgc_globPosX;   //!
   TBranch        *b_tgc_globPosY;   //!
   TBranch        *b_tgc_globPosZ;   //!
   TBranch        *b_tgc_shortWidth;   //!
   TBranch        *b_tgc_longWidth;   //!
   TBranch        *b_tgc_length;   //!
   TBranch        *b_m_nTgcCoinColl;   //!
   TBranch        *b_m_nTgcCoinTracklet;   //!
   TBranch        *b_tgc_cointrackletdelta;   //!
   TBranch        *b_tgc_cointrackletposx_in;   //!
   TBranch        *b_tgc_cointrackletposy_in;   //!
   TBranch        *b_tgc_cointrackletposz_in;   //!
   TBranch        *b_tgc_cointrackletposx_out;   //!
   TBranch        *b_tgc_cointrackletposy_out;   //!
   TBranch        *b_tgc_cointrackletposz_out;   //!
   TBranch        *b_tgc_cointrackletstrip;   //!
   TBranch        *b_tgc_cointrackletforward;   //!
   TBranch        *b_tgc_cointrackletwidthout;   //!
   TBranch        *b_tgc_cointrackletwidthin;   //!
   TBranch        *b_tgc_cointrackletstationeta;   //!
   TBranch        *b_tgc_cointrackletstationphi;   //!
   TBranch        *b_tgc_cointrackletsector;   //!
   TBranch        *b_tgc_cointracklettrackletid;   //!
   TBranch        *b_m_nTgcCoinHighPt;   //!
   TBranch        *b_tgc_coinhighptdelta;   //!
   TBranch        *b_tgc_coinhighptposx_in;   //!
   TBranch        *b_tgc_coinhighptposy_in;   //!
   TBranch        *b_tgc_coinhighptposz_in;   //!
   TBranch        *b_tgc_coinhighptposx_out;   //!
   TBranch        *b_tgc_coinhighptposy_out;   //!
   TBranch        *b_tgc_coinhighptposz_out;   //!
   TBranch        *b_tgc_coinhighptstrip;   //!
   TBranch        *b_tgc_coinhighptforward;   //!
   TBranch        *b_tgc_coinhighptwidthout;   //!
   TBranch        *b_tgc_coinhighptwidthin;   //!
   TBranch        *b_tgc_coinhighptstationeta;   //!
   TBranch        *b_tgc_coinhighptstationphi;   //!
   TBranch        *b_tgc_coinhighptsector;   //!
   TBranch        *b_tgc_coinhighpttrackletid;   //!
   TBranch        *b_m_nTgcCoinSl;   //!
   TBranch        *b_tgc_coinslptthresh;   //!
   TBranch        *b_tgc_coinslposx_out;   //!
   TBranch        *b_tgc_coinslposy_out;   //!
   TBranch        *b_tgc_coinslposz_out;   //!
   TBranch        *b_tgc_coinslroi;   //!
   TBranch        *b_tgc_coinslforward;   //!
   TBranch        *b_tgc_coinslwidthr;   //!
   TBranch        *b_tgc_coinslwidthphi;   //!
   TBranch        *b_tgc_coinslstationeta;   //!
   TBranch        *b_tgc_coinslstationphi;   //!
   TBranch        *b_tgc_coinslsector;   //!
   TBranch        *b_tgc_coinsltrackletid;   //!
   TBranch        *b_tgc_coinsltrackletidstrip;   //!
   TBranch        *b_m_nTgcColl_Prev;   //!
   TBranch        *b_m_nTgcPrd_Prev;   //!
   TBranch        *b_tgc_station_Prev;   //!
   TBranch        *b_tgc_eta_Prev;   //!
   TBranch        *b_tgc_phi_Prev;   //!
   TBranch        *b_tgc_gasGap_Prev;   //!
   TBranch        *b_tgc_isStrip_Prev;   //!
   TBranch        *b_tgc_channel_Prev;   //!
   TBranch        *b_tgc_globPosX_Prev;   //!
   TBranch        *b_tgc_globPosY_Prev;   //!
   TBranch        *b_tgc_globPosZ_Prev;   //!
   TBranch        *b_tgc_shortWidth_Prev;   //!
   TBranch        *b_tgc_longWidth_Prev;   //!
   TBranch        *b_tgc_length_Prev;   //!
   TBranch        *b_m_nTgcCoinColl_Prev;   //!
   TBranch        *b_m_nTgcCoinTracklet_Prev;   //!
   TBranch        *b_tgc_cointrackletdelta_Prev;   //!
   TBranch        *b_tgc_cointrackletposx_in_Prev;   //!
   TBranch        *b_tgc_cointrackletposy_in_Prev;   //!
   TBranch        *b_tgc_cointrackletposz_in_Prev;   //!
   TBranch        *b_tgc_cointrackletposx_out_Prev;   //!
   TBranch        *b_tgc_cointrackletposy_out_Prev;   //!
   TBranch        *b_tgc_cointrackletposz_out_Prev;   //!
   TBranch        *b_tgc_cointrackletstrip_Prev;   //!
   TBranch        *b_tgc_cointrackletforward_Prev;   //!
   TBranch        *b_tgc_cointrackletwidthout_Prev;   //!
   TBranch        *b_tgc_cointrackletwidthin_Prev;   //!
   TBranch        *b_tgc_cointrackletstationeta_Prev;   //!
   TBranch        *b_tgc_cointrackletstationphi_Prev;   //!
   TBranch        *b_tgc_cointrackletsector_Prev;   //!
   TBranch        *b_tgc_cointracklettrackletid_Prev;   //!
   TBranch        *b_m_nTgcCoinHighPt_Prev;   //!
   TBranch        *b_tgc_coinhighptdelta_Prev;   //!
   TBranch        *b_tgc_coinhighptposx_in_Prev;   //!
   TBranch        *b_tgc_coinhighptposy_in_Prev;   //!
   TBranch        *b_tgc_coinhighptposz_in_Prev;   //!
   TBranch        *b_tgc_coinhighptposx_out_Prev;   //!
   TBranch        *b_tgc_coinhighptposy_out_Prev;   //!
   TBranch        *b_tgc_coinhighptposz_out_Prev;   //!
   TBranch        *b_tgc_coinhighptstrip_Prev;   //!
   TBranch        *b_tgc_coinhighptforward_Prev;   //!
   TBranch        *b_tgc_coinhighptwidthout_Prev;   //!
   TBranch        *b_tgc_coinhighptwidthin_Prev;   //!
   TBranch        *b_tgc_coinhighptstationeta_Prev;   //!
   TBranch        *b_tgc_coinhighptstationphi_Prev;   //!
   TBranch        *b_tgc_coinhighptsector_Prev;   //!
   TBranch        *b_tgc_coinhighpttrackletid_Prev;   //!
   TBranch        *b_m_nTgcCoinSl_Prev;   //!
   TBranch        *b_tgc_coinslptthresh_Prev;   //!
   TBranch        *b_tgc_coinslposx_out_Prev;   //!
   TBranch        *b_tgc_coinslposy_out_Prev;   //!
   TBranch        *b_tgc_coinslposz_out_Prev;   //!
   TBranch        *b_tgc_coinslroi_Prev;   //!
   TBranch        *b_tgc_coinslforward_Prev;   //!
   TBranch        *b_tgc_coinslwidthr_Prev;   //!
   TBranch        *b_tgc_coinslwidthphi_Prev;   //!
   TBranch        *b_tgc_coinslstationeta_Prev;   //!
   TBranch        *b_tgc_coinslstationphi_Prev;   //!
   TBranch        *b_tgc_coinslsector_Prev;   //!
   TBranch        *b_tgc_coinsltrackletid_Prev;   //!
   TBranch        *b_tgc_coinsltrackletidstrip_Prev;   //!
   TBranch        *b_m_nTgcColl_Next;   //!
   TBranch        *b_m_nTgcPrd_Next;   //!
   TBranch        *b_tgc_station_Next;   //!
   TBranch        *b_tgc_eta_Next;   //!
   TBranch        *b_tgc_phi_Next;   //!
   TBranch        *b_tgc_gasGap_Next;   //!
   TBranch        *b_tgc_isStrip_Next;   //!
   TBranch        *b_tgc_channel_Next;   //!
   TBranch        *b_tgc_globPosX_Next;   //!
   TBranch        *b_tgc_globPosY_Next;   //!
   TBranch        *b_tgc_globPosZ_Next;   //!
   TBranch        *b_tgc_shortWidth_Next;   //!
   TBranch        *b_tgc_longWidth_Next;   //!
   TBranch        *b_tgc_length_Next;   //!
   TBranch        *b_m_nTgcCoinColl_Next;   //!
   TBranch        *b_m_nTgcCoinTracklet_Next;   //!
   TBranch        *b_tgc_cointrackletdelta_Next;   //!
   TBranch        *b_tgc_cointrackletposx_in_Next;   //!
   TBranch        *b_tgc_cointrackletposy_in_Next;   //!
   TBranch        *b_tgc_cointrackletposz_in_Next;   //!
   TBranch        *b_tgc_cointrackletposx_out_Next;   //!
   TBranch        *b_tgc_cointrackletposy_out_Next;   //!
   TBranch        *b_tgc_cointrackletposz_out_Next;   //!
   TBranch        *b_tgc_cointrackletstrip_Next;   //!
   TBranch        *b_tgc_cointrackletforward_Next;   //!
   TBranch        *b_tgc_cointrackletwidthout_Next;   //!
   TBranch        *b_tgc_cointrackletwidthin_Next;   //!
   TBranch        *b_tgc_cointrackletstationeta_Next;   //!
   TBranch        *b_tgc_cointrackletstationphi_Next;   //!
   TBranch        *b_tgc_cointrackletsector_Next;   //!
   TBranch        *b_tgc_cointracklettrackletid_Next;   //!
   TBranch        *b_m_nTgcCoinHighPt_Next;   //!
   TBranch        *b_tgc_coinhighptdelta_Next;   //!
   TBranch        *b_tgc_coinhighptposx_in_Next;   //!
   TBranch        *b_tgc_coinhighptposy_in_Next;   //!
   TBranch        *b_tgc_coinhighptposz_in_Next;   //!
   TBranch        *b_tgc_coinhighptposx_out_Next;   //!
   TBranch        *b_tgc_coinhighptposy_out_Next;   //!
   TBranch        *b_tgc_coinhighptposz_out_Next;   //!
   TBranch        *b_tgc_coinhighptstrip_Next;   //!
   TBranch        *b_tgc_coinhighptforward_Next;   //!
   TBranch        *b_tgc_coinhighptwidthout_Next;   //!
   TBranch        *b_tgc_coinhighptwidthin_Next;   //!
   TBranch        *b_tgc_coinhighptstationeta_Next;   //!
   TBranch        *b_tgc_coinhighptstationphi_Next;   //!
   TBranch        *b_tgc_coinhighptsector_Next;   //!
   TBranch        *b_tgc_coinhighpttrackletid_Next;   //!
   TBranch        *b_m_nTgcCoinSl_Next;   //!
   TBranch        *b_tgc_coinslptthresh_Next;   //!
   TBranch        *b_tgc_coinslposx_out_Next;   //!
   TBranch        *b_tgc_coinslposy_out_Next;   //!
   TBranch        *b_tgc_coinslposz_out_Next;   //!
   TBranch        *b_tgc_coinslroi_Next;   //!
   TBranch        *b_tgc_coinslforward_Next;   //!
   TBranch        *b_tgc_coinslwidthr_Next;   //!
   TBranch        *b_tgc_coinslwidthphi_Next;   //!
   TBranch        *b_tgc_coinslstationeta_Next;   //!
   TBranch        *b_tgc_coinslstationphi_Next;   //!
   TBranch        *b_tgc_coinslsector_Next;   //!
   TBranch        *b_tgc_coinsltrackletid_Next;   //!
   TBranch        *b_tgc_coinsltrackletidstrip_Next;   //!
   TBranch        *b_IS_Nsgins;   //!
   TBranch        *b_IS_Xpt;   //!
   TBranch        *b_IS_Ypt;   //!
   TBranch        *b_IS_Zpt;   //!
   TBranch        *b_IS_Xvec;   //!
   TBranch        *b_IS_Yvec;   //!
   TBranch        *b_IS_Zvec;   //!
   TBranch        *b_IS_QualityFactor;   //!
   TBranch        *b_IS_NbreOfMultiLayer;   //!
   TBranch        *b_IS_TrackSharing;   //!
   TBranch        *b_IS_StationName;   //!
   TBranch        *b_IS_Ndigits;   //!
   TBranch        *b_IS_HitPosition;   //!
   TBranch        *b_IS_MaxHits;   //!
   TBranch        *b_IS_Rdigi;   //!
   TBranch        *b_IS_Rtrack;   //!
   TBranch        *b_IS_Xdca;   //!
   TBranch        *b_IS_Ydca;   //!
   TBranch        *b_IS_Zdca;   //!
   TBranch        *b_IS_Sdca;   //!
   TBranch        *b_IS_Reso;   //!
   TBranch        *b_IS_JTYP;   //!
   TBranch        *b_IS_JFF;   //!
   TBranch        *b_IS_JZZ;   //!
   TBranch        *b_IS_JOB;   //!
   TBranch        *b_IS_JSPLI;   //!
   TBranch        *b_IS_JSL;   //!
   TBranch        *b_IS_JTUBE;   //!
   TBranch        *b_IS_JSZ;   //!
   TBranch        *b_IS_JSTRI;   //!
   TBranch        *b_IS_DriftTime;   //!
   TBranch        *b_IS_ChamberTech;   //!
   TBranch        *b_IS_StationNber;   //!
   TBranch        *b_IS_StationEta;   //!
   TBranch        *b_IS_StationPhi;   //!
   TBranch        *b_IS_Multilayer;   //!
   TBranch        *b_IS_TubeLayer;   //!
   TBranch        *b_IS_Tube;   //!
   TBranch        *b_IS_DoubletR;   //!
   TBranch        *b_IS_DoubletZ;   //!
   TBranch        *b_IS_DoubletPhi;   //!
   TBranch        *b_IS_GasGap;   //!
   TBranch        *b_IS_MeasuresPhi;   //!
   TBranch        *b_IS_Strip;   //!
   TBranch        *b_IS_IsStrip;   //!
   TBranch        *b_IS_Channel;   //!
   TBranch        *b_IS_ChamberLayer;   //!
   TBranch        *b_IS_WireLayer;   //!
   TBranch        *b_IS_RpcTime;   //!
   TBranch        *b_MB_NTrk;   //!
   TBranch        *b_VT_NTrk;   //!
   TBranch        *b_VT_Va;   //!
   TBranch        *b_VT_A0;   //!
   TBranch        *b_VT_Z;   //!
   TBranch        *b_VT_Phi;   //!
   TBranch        *b_VT_CotTh;   //!
   TBranch        *b_VT_PTInv;   //!
   TBranch        *b_VT_Cov11;   //!
   TBranch        *b_VT_Cov21;   //!
   TBranch        *b_VT_Cov22;   //!
   TBranch        *b_VT_Cov31;   //!
   TBranch        *b_VT_Cov32;   //!
   TBranch        *b_VT_Cov33;   //!
   TBranch        *b_VT_Cov41;   //!
   TBranch        *b_VT_Cov42;   //!
   TBranch        *b_VT_Cov43;   //!
   TBranch        *b_VT_Cov44;   //!
   TBranch        *b_VT_Cov51;   //!
   TBranch        *b_VT_Cov52;   //!
   TBranch        *b_VT_Cov53;   //!
   TBranch        *b_VT_Cov54;   //!
   TBranch        *b_VT_Cov55;   //!
   TBranch        *b_VT_Xpt;   //!
   TBranch        *b_VT_Ypt;   //!
   TBranch        *b_VT_Zpt;   //!
   TBranch        *b_VT_Xvec;   //!
   TBranch        *b_VT_Yvec;   //!
   TBranch        *b_VT_Zvec;   //!
   TBranch        *b_VT_Mom;   //!
   TBranch        *b_VT_digits;   //!
   TBranch        *b_VT_HitPosition;   //!
   TBranch        *b_VT_TrHi_hits;   //!
   TBranch        *b_VT_TrHi_Rdigi;   //!
   TBranch        *b_VT_TrHi_Rtrack;   //!
   TBranch        *b_VT_TrHi_Xdca;   //!
   TBranch        *b_VT_TrHi_Ydca;   //!
   TBranch        *b_VT_TrHi_Zdca;   //!
   TBranch        *b_VT_TrHi_Sdca;   //!
   TBranch        *b_VT_TrHi_Reso;   //!
   TBranch        *b_VT_TrHi_RZSsim;   //!
   TBranch        *b_VT_TrHi_EZSfit;   //!
   TBranch        *b_VT_TrHi_JTYP;   //!
   TBranch        *b_VT_TrHi_JFF;   //!
   TBranch        *b_VT_TrHi_JZZ;   //!
   TBranch        *b_VT_TrHi_JOB;   //!
   TBranch        *b_VT_TrHi_JSPLI;   //!
   TBranch        *b_VT_TrHi_JSL;   //!
   TBranch        *b_VT_TrHi_JTUBE;   //!
   TBranch        *b_VT_TrHi_JSZ;   //!
   TBranch        *b_VT_TrHi_JSTRI;   //!
   TBranch        *b_VT_TrHi_DriftTime;   //!
   TBranch        *b_VT_TrHi_ChamberTech;   //!
   TBranch        *b_VT_TrHi_StationNber;   //!
   TBranch        *b_VT_TrHi_StationEta;   //!
   TBranch        *b_VT_TrHi_StationPhi;   //!
   TBranch        *b_VT_TrHi_Multilayer;   //!
   TBranch        *b_VT_TrHi_TubeLayer;   //!
   TBranch        *b_VT_TrHi_Tube;   //!
   TBranch        *b_VT_TrHi_DoubletR;   //!
   TBranch        *b_VT_TrHi_DoubletZ;   //!
   TBranch        *b_VT_TrHi_DoubletPhi;   //!
   TBranch        *b_VT_TrHi_GasGap;   //!
   TBranch        *b_VT_TrHi_MeasuresPhi;   //!
   TBranch        *b_VT_TrHi_Strip;   //!
   TBranch        *b_VT_TrHi_IsStrip;   //!
   TBranch        *b_VT_TrHi_Channel;   //!
   TBranch        *b_VT_TrHi_ChamberLayer;   //!
   TBranch        *b_VT_TrHi_WireLayer;   //!
   TBranch        *b_VT_TrHi_RpcTime;   //!
   TBranch        *b_KE_NTrk;   //!
   TBranch        *b_KE_Va;   //!
   TBranch        *b_KE_Thept;   //!
   TBranch        *b_KE_Phipt;   //!
   TBranch        *b_KE_Thevc;   //!
   TBranch        *b_KE_Phivc;   //!
   TBranch        *b_KE_PInv;   //!
   TBranch        *b_KE_Cov11;   //!
   TBranch        *b_KE_Cov21;   //!
   TBranch        *b_KE_Cov22;   //!
   TBranch        *b_KE_Cov31;   //!
   TBranch        *b_KE_Cov32;   //!
   TBranch        *b_KE_Cov33;   //!
   TBranch        *b_KE_Cov41;   //!
   TBranch        *b_KE_Cov42;   //!
   TBranch        *b_KE_Cov43;   //!
   TBranch        *b_KE_Cov44;   //!
   TBranch        *b_KE_Cov51;   //!
   TBranch        *b_KE_Cov52;   //!
   TBranch        *b_KE_Cov53;   //!
   TBranch        *b_KE_Cov54;   //!
   TBranch        *b_KE_Cov55;   //!
   TBranch        *b_KE_Xpt;   //!
   TBranch        *b_KE_Ypt;   //!
   TBranch        *b_KE_Zpt;   //!
   TBranch        *b_KE_Xvec;   //!
   TBranch        *b_KE_Yvec;   //!
   TBranch        *b_KE_Zvec;   //!
   TBranch        *b_KE_Mom;   //!
   TBranch        *b_KE_ZCyl;   //!
   TBranch        *b_KE_RCyl;   //!
   TBranch        *b_MS_NTrk;   //!
   TBranch        *b_MS_Va;   //!
   TBranch        *b_MS_Thept;   //!
   TBranch        *b_MS_Phipt;   //!
   TBranch        *b_MS_Thevc;   //!
   TBranch        *b_MS_Phivc;   //!
   TBranch        *b_MS_PInv;   //!
   TBranch        *b_MS_Cov11;   //!
   TBranch        *b_MS_Cov21;   //!
   TBranch        *b_MS_Cov22;   //!
   TBranch        *b_MS_Cov31;   //!
   TBranch        *b_MS_Cov32;   //!
   TBranch        *b_MS_Cov33;   //!
   TBranch        *b_MS_Cov41;   //!
   TBranch        *b_MS_Cov42;   //!
   TBranch        *b_MS_Cov43;   //!
   TBranch        *b_MS_Cov44;   //!
   TBranch        *b_MS_Cov51;   //!
   TBranch        *b_MS_Cov52;   //!
   TBranch        *b_MS_Cov53;   //!
   TBranch        *b_MS_Cov54;   //!
   TBranch        *b_MS_Cov55;   //!
   TBranch        *b_MS_Xpt;   //!
   TBranch        *b_MS_Ypt;   //!
   TBranch        *b_MS_Zpt;   //!
   TBranch        *b_MS_Xvec;   //!
   TBranch        *b_MS_Yvec;   //!
   TBranch        *b_MS_Zvec;   //!
   TBranch        *b_MS_Mom;   //!
   TBranch        *b_MS_ZCyl;   //!
   TBranch        *b_MS_RCyl;   //!
   TBranch        *b_MS_Chican;   //!
   TBranch        *b_MS_Chifit;   //!
   TBranch        *b_MS_Chiver;   //!
   TBranch        *b_MS_Chistat;   //!
   TBranch        *b_MS_Ndof;   //!
   TBranch        *b_Moore_nmuon;   //!
   TBranch        *b_Moore_phih;   //!
   TBranch        *b_Moore_etah;   //!
   TBranch        *b_Moore_mdth;   //!
   TBranch        *b_Moore_cscetah;   //!
   TBranch        *b_Moore_cscphih;   //!
   TBranch        *b_Moore_rpcetah;   //!
   TBranch        *b_Moore_rpcphih;   //!
   TBranch        *b_Moore_tgcetah;   //!
   TBranch        *b_Moore_tgcphih;   //!
   TBranch        *b_Moore_stati;   //!
   TBranch        *b_Moore_statr;   //!
   TBranch        *b_Moore_xvtxr;   //!
   TBranch        *b_Moore_yvtxr;   //!
   TBranch        *b_Moore_zvtxr;   //!
   TBranch        *b_Moore_a0r;   //!
   TBranch        *b_Moore_z0r;   //!
   TBranch        *b_Moore_phir;   //!
   TBranch        *b_Moore_thetar;   //!
   TBranch        *b_Moore_qpir;   //!
   TBranch        *b_Moore_etar;   //!
   TBranch        *b_Moore_chi2;   //!
   TBranch        *b_Moore_chi2pr;   //!
   TBranch        *b_Moore_origx;   //!
   TBranch        *b_Moore_origy;   //!
   TBranch        *b_Moore_origz;   //!
   TBranch        *b_Moore_covr11;   //!
   TBranch        *b_Moore_covr12;   //!
   TBranch        *b_Moore_covr22;   //!
   TBranch        *b_Moore_covr13;   //!
   TBranch        *b_Moore_covr23;   //!
   TBranch        *b_Moore_covr33;   //!
   TBranch        *b_Moore_covr14;   //!
   TBranch        *b_Moore_covr24;   //!
   TBranch        *b_Moore_covr34;   //!
   TBranch        *b_Moore_covr44;   //!
   TBranch        *b_Moore_covr15;   //!
   TBranch        *b_Moore_covr25;   //!
   TBranch        *b_Moore_covr35;   //!
   TBranch        *b_Moore_covr45;   //!
   TBranch        *b_Moore_covr55;   //!
   TBranch        *b_MooreSegments_nseg;   //!
   TBranch        *b_MooreSegments_ml;   //!
   TBranch        *b_MooreSegments_nhml1;   //!
   TBranch        *b_MooreSegments_nhml2;   //!
   TBranch        *b_MooreSegments_nmlyr;   //!
   TBranch        *b_MooreSegments_nhit;   //!
   TBranch        *b_MooreSegments_nhcsc;   //!
   TBranch        *b_MooreSegments_nhmdt;   //!
   TBranch        *b_MooreSegments_nhrpc;   //!
   TBranch        *b_MooreSegments_nhtgc;   //!
   TBranch        *b_MooreSegments_n_tottubes_seg;   //!
   TBranch        *b_MooreSegments_n_hittubes_seg;   //!
   TBranch        *b_MooreSegments_hittype;   //!
   TBranch        *b_MooreSegments_prdadc;   //!
   TBranch        *b_MooreSegments_prdtdc;   //!
   TBranch        *b_MooreSegments_z;   //!
   TBranch        *b_MooreSegments_rho;   //!
   TBranch        *b_MooreSegments_phi;   //!
   TBranch        *b_MooreSegments_theta;   //!
   TBranch        *b_MooreSegments_cotth;   //!
   TBranch        *b_MooreSegments_dtheta;   //!
   TBranch        *b_MooreSegments_chi2;   //!
   TBranch        *b_MooreSegments_ndof;   //!
   TBranch        *b_MooreSegments_rInt;   //!
   TBranch        *b_MooreSegments_LocR;   //!
   TBranch        *b_MooreSegments_driftTime;   //!
   TBranch        *b_Cone4H1TowerJetsjetNum;   //!
   TBranch        *b_jetEtaCone4H1TowerJets;   //!
   TBranch        *b_jetPhiCone4H1TowerJets;   //!
   TBranch        *b_jetECone4H1TowerJets;   //!
   TBranch        *b_jetEtCone4H1TowerJets;   //!
   TBranch        *b_jetMCone4H1TowerJets;   //!
   TBranch        *b_jetPxCone4H1TowerJets;   //!
   TBranch        *b_jetPyCone4H1TowerJets;   //!
   TBranch        *b_jetPzCone4H1TowerJets;   //!
   TBranch        *b_jetSizeCone4H1TowerJets;   //!
   TBranch        *b_jetEmfCone4H1TowerJets;   //!
   TBranch        *b_CaloMu_ntrack;   //!
   TBranch        *b_CaloMu_trkPdgid;   //!
   TBranch        *b_CaloMu_trkMother;   //!
   TBranch        *b_CaloMu_trkEta;   //!
   TBranch        *b_CaloMu_trkPhi;   //!
   TBranch        *b_CaloMu_trkPt;   //!
   TBranch        *b_CaloMu_trkD0;   //!
   TBranch        *b_CaloMu_trkIP;   //!
   TBranch        *b_CaloMu_trkBLayerHits;   //!
   TBranch        *b_CaloMu_trkPixelHits;   //!
   TBranch        *b_CaloMu_trkSCTHits;   //!
   TBranch        *b_CaloMu_trkTRTHits;   //!
   TBranch        *b_CaloMu_nmuon;   //!
   TBranch        *b_CaloMu_pdgid;   //!
   TBranch        *b_CaloMu_mother;   //!
   TBranch        *b_CaloMu_tag;   //!
   TBranch        *b_CaloMu_lhr;   //!
   TBranch        *b_CaloMu_etCone;   //!
   TBranch        *b_CaloMu_ptCone;   //!
   TBranch        *b_CaloMu_eta;   //!
   TBranch        *b_CaloMu_phi;   //!
   TBranch        *b_CaloMu_pt;   //!
   TBranch        *b_CaloMu_qoverp;   //!
   TBranch        *b_CaloMu_IP;   //!
   TBranch        *b_CaloMu_d0;   //!
   TBranch        *b_CaloMu_bLayerHits;   //!
   TBranch        *b_CaloMu_pixelHits;   //!
   TBranch        *b_CaloMu_SCTHits;   //!
   TBranch        *b_CaloMu_TRTHits;   //!
   TBranch        *b_CaloMu_sample;   //!
   TBranch        *b_CaloMu_energy;   //!
   TBranch        *b_CaloMu_energyLoss;   //!
   TBranch        *b_CaloMu2_ntrack;   //!
   TBranch        *b_CaloMu2_trkPdgid;   //!
   TBranch        *b_CaloMu2_trkMother;   //!
   TBranch        *b_CaloMu2_trkEta;   //!
   TBranch        *b_CaloMu2_trkPhi;   //!
   TBranch        *b_CaloMu2_trkPt;   //!
   TBranch        *b_CaloMu2_trkD0;   //!
   TBranch        *b_CaloMu2_trkIP;   //!
   TBranch        *b_CaloMu2_trkBLayerHits;   //!
   TBranch        *b_CaloMu2_trkPixelHits;   //!
   TBranch        *b_CaloMu2_trkSCTHits;   //!
   TBranch        *b_CaloMu2_trkTRTHits;   //!
   TBranch        *b_CaloMu2_nmuon;   //!
   TBranch        *b_CaloMu2_pdgid;   //!
   TBranch        *b_CaloMu2_mother;   //!
   TBranch        *b_CaloMu2_tag;   //!
   TBranch        *b_CaloMu2_lhr;   //!
   TBranch        *b_CaloMu2_etCone;   //!
   TBranch        *b_CaloMu2_ptCone;   //!
   TBranch        *b_CaloMu2_eta;   //!
   TBranch        *b_CaloMu2_phi;   //!
   TBranch        *b_CaloMu2_pt;   //!
   TBranch        *b_CaloMu2_qoverp;   //!
   TBranch        *b_CaloMu2_IP;   //!
   TBranch        *b_CaloMu2_d0;   //!
   TBranch        *b_CaloMu2_bLayerHits;   //!
   TBranch        *b_CaloMu2_pixelHits;   //!
   TBranch        *b_CaloMu2_SCTHits;   //!
   TBranch        *b_CaloMu2_TRTHits;   //!
   TBranch        *b_CaloMu2_sample;   //!
   TBranch        *b_CaloMu2_energy;   //!
   TBranch        *b_CaloMu2_energyLoss;   //!
   TBranch        *b_trk_nTracksComb;   //!
   TBranch        *b_trk_nPixelHitsComb;   //!
   TBranch        *b_trk_nSctHitsComb;   //!
   TBranch        *b_trk_nTrtHitsComb;   //!
   TBranch        *b_trk_PixResPhiComb;   //!
   TBranch        *b_trk_PixResEtaComb;   //!
   TBranch        *b_trk_PixPullPhiComb;   //!
   TBranch        *b_trk_PixPullEtaComb;   //!
   TBranch        *b_trk_PixErrTrkPhiComb;   //!
   TBranch        *b_trk_PixErrTrkEtaComb;   //!
   TBranch        *b_trk_PixErrHitPhiComb;   //!
   TBranch        *b_trk_PixErrHitEtaComb;   //!
   TBranch        *b_trk_Pix_becComb;   //!
   TBranch        *b_trk_Pix_layerComb;   //!
   TBranch        *b_trk_Pix_etaComb;   //!
   TBranch        *b_trk_Pix_phiComb;   //!
   TBranch        *b_trk_Pix_clusWidthRowComb;   //!
   TBranch        *b_trk_Pix_clusWidthColComb;   //!
   TBranch        *b_trk_Pix_LocXComb;   //!
   TBranch        *b_trk_Pix_LocYComb;   //!
   TBranch        *b_trk_SctResComb;   //!
   TBranch        *b_trk_SctPullComb;   //!
   TBranch        *b_trk_SctErrTrkComb;   //!
   TBranch        *b_trk_SctErrHitComb;   //!
   TBranch        *b_trk_Sct_becComb;   //!
   TBranch        *b_trk_Sct_layerComb;   //!
   TBranch        *b_trk_Sct_etaComb;   //!
   TBranch        *b_trk_Sct_phiComb;   //!
   TBranch        *b_trk_Sct_sideComb;   //!
   TBranch        *b_trk_Sct_rdoIdComb;   //!
   TBranch        *b_trk_Sct_clusGroupsizeComb;   //!
   TBranch        *b_trk_Sct_clusxComb;   //!
   TBranch        *b_trk_Sct_clusyComb;   //!
   TBranch        *b_trk_Sct_cluszComb;   //!
   TBranch        *b_trk_TrtResComb;   //!
   TBranch        *b_trk_TrtPullComb;   //!
   TBranch        *b_trk_TrtErrTrkComb;   //!
   TBranch        *b_trk_TrtErrHitComb;   //!
   TBranch        *b_trk_Trt_RComb;   //!
   TBranch        *b_trk_Trt_RtrackComb;   //!
   TBranch        *b_trk_Trt_tComb;   //!
   TBranch        *b_trk_Trt_xComb;   //!
   TBranch        *b_trk_Trt_yComb;   //!
   TBranch        *b_trk_Trt_HLComb;   //!
   TBranch        *b_trk_Trt_strawlayerComb;   //!
   TBranch        *b_trk_Trt_becComb;   //!
   TBranch        *b_trk_Trt_layerComb;   //!
   TBranch        *b_trk_Trt_strawComb;   //!
   TBranch        *b_trk_Trt_phisectorComb;   //!
   TBranch        *b_trk_Rec_d0Comb;   //!
   TBranch        *b_trk_Rec_z0Comb;   //!
   TBranch        *b_trk_Rec_phi0Comb;   //!
   TBranch        *b_trk_Rec_theta0Comb;   //!
   TBranch        *b_trk_Rec_qoverpComb;   //!
   TBranch        *b_trk_Rec_chi2Comb;   //!
   TBranch        *b_trk_Rec_ndofComb;   //!
   TBranch        *b_trk_Rec_etaComb;   //!
   TBranch        *b_trk_Rec_error_d0Comb;   //!
   TBranch        *b_trk_Rec_error_z0Comb;   //!
   TBranch        *b_trk_Rec_error_phi0Comb;   //!
   TBranch        *b_trk_Rec_error_theta0Comb;   //!
   TBranch        *b_trk_Rec_error_qoverpComb;   //!
   TBranch        *b_trk_Rec_chi2probComb;   //!
   TBranch        *b_trk_Rec_authorComb;   //!
   TBranch        *b_trk_nTracksMuon;   //!
   TBranch        *b_trk_nPixelHitsMuon;   //!
   TBranch        *b_trk_nSctHitsMuon;   //!
   TBranch        *b_trk_nTrtHitsMuon;   //!
   TBranch        *b_trk_Rec_d0Muon;   //!
   TBranch        *b_trk_Rec_z0Muon;   //!
   TBranch        *b_trk_Rec_phi0Muon;   //!
   TBranch        *b_trk_Rec_theta0Muon;   //!
   TBranch        *b_trk_Rec_qoverpMuon;   //!
   TBranch        *b_trk_Rec_chi2Muon;   //!
   TBranch        *b_trk_Rec_ndofMuon;   //!
   TBranch        *b_trk_Rec_etaMuon;   //!
   TBranch        *b_trk_Rec_error_d0Muon;   //!
   TBranch        *b_trk_Rec_error_z0Muon;   //!
   TBranch        *b_trk_Rec_error_phi0Muon;   //!
   TBranch        *b_trk_Rec_error_theta0Muon;   //!
   TBranch        *b_trk_Rec_error_qoverpMuon;   //!
   TBranch        *b_trk_Rec_chi2probMuon;   //!
   TBranch        *b_trk_Rec_authorMuon;   //!
   TBranch        *b_MuTagIMO__nmuon;   //!
   TBranch        *b_MuTagIMO__nTagSegs;   //!
   TBranch        *b_MuTagIMO_trk_isTagged;   //!
   TBranch        *b_MuTagIMO_trk_matchesBarCode;   //!
   TBranch        *b_MuTagIMO_trk_matchesPdg;   //!
   TBranch        *b_MuTagIMO_trk_nrPixelHits;   //!
   TBranch        *b_MuTagIMO_trk_nrSctHits;   //!
   TBranch        *b_MuTagIMO_trk_A0;   //!
   TBranch        *b_MuTagIMO_trk_Z0;   //!
   TBranch        *b_MuTagIMO_trk_phi;   //!
   TBranch        *b_MuTagIMO_trk_theta;   //!
   TBranch        *b_MuTagIMO_trk_qOverP;   //!
   TBranch        *b_MuTagIMO_trk_chi2;   //!
   TBranch        *b_MuTagIMO_trk_ndof;   //!
   TBranch        *b_MuTagIMO_trk_Author;   //!
   TBranch        *b_MuTagIMO_trk_cov11;   //!
   TBranch        *b_MuTagIMO_trk_cov12;   //!
   TBranch        *b_MuTagIMO_trk_cov13;   //!
   TBranch        *b_MuTagIMO_trk_cov14;   //!
   TBranch        *b_MuTagIMO_trk_cov15;   //!
   TBranch        *b_MuTagIMO_trk_cov22;   //!
   TBranch        *b_MuTagIMO_trk_cov23;   //!
   TBranch        *b_MuTagIMO_trk_cov24;   //!
   TBranch        *b_MuTagIMO_trk_cov25;   //!
   TBranch        *b_MuTagIMO_trk_cov33;   //!
   TBranch        *b_MuTagIMO_trk_cov34;   //!
   TBranch        *b_MuTagIMO_trk_cov35;   //!
   TBranch        *b_MuTagIMO_trk_cov44;   //!
   TBranch        *b_MuTagIMO_trk_cov45;   //!
   TBranch        *b_MuTagIMO_trk_cov55;   //!
   TBranch        *b_MuTagIMO_exTrk_trackIndex;   //!
   TBranch        *b_MuTagIMO_exTrk_A0;   //!
   TBranch        *b_MuTagIMO_exTrk_Z0;   //!
   TBranch        *b_MuTagIMO_exTrk_phi;   //!
   TBranch        *b_MuTagIMO_exTrk_theta;   //!
   TBranch        *b_MuTagIMO_exTrk_qOverP;   //!
   TBranch        *b_MuTagIMO_exTrk_cov11;   //!
   TBranch        *b_MuTagIMO_exTrk_cov12;   //!
   TBranch        *b_MuTagIMO_exTrk_cov13;   //!
   TBranch        *b_MuTagIMO_exTrk_cov14;   //!
   TBranch        *b_MuTagIMO_exTrk_cov15;   //!
   TBranch        *b_MuTagIMO_exTrk_cov22;   //!
   TBranch        *b_MuTagIMO_exTrk_cov23;   //!
   TBranch        *b_MuTagIMO_exTrk_cov24;   //!
   TBranch        *b_MuTagIMO_exTrk_cov25;   //!
   TBranch        *b_MuTagIMO_exTrk_cov33;   //!
   TBranch        *b_MuTagIMO_exTrk_cov34;   //!
   TBranch        *b_MuTagIMO_exTrk_cov35;   //!
   TBranch        *b_MuTagIMO_exTrk_cov44;   //!
   TBranch        *b_MuTagIMO_exTrk_cov45;   //!
   TBranch        *b_MuTagIMO_exTrk_cov55;   //!
   TBranch        *b_MuTagIMO_exTrk_Eloss;   //!
   TBranch        *b_MuTagIMO_exTrk_gPosX;   //!
   TBranch        *b_MuTagIMO_exTrk_gPosY;   //!
   TBranch        *b_MuTagIMO_exTrk_gPosZ;   //!
   TBranch        *b_MuTagIMO_exTrk_gDirX;   //!
   TBranch        *b_MuTagIMO_exTrk_gDirY;   //!
   TBranch        *b_MuTagIMO_exTrk_gDirZ;   //!
   TBranch        *b_MuTagIMO_exTrk_locX;   //!
   TBranch        *b_MuTagIMO_exTrk_locY;   //!
   TBranch        *b_MuTagIMO_exTrk_angleXZ;   //!
   TBranch        *b_MuTagIMO_exTrk_angleYZ;   //!
   TBranch        *b_MuTagIMO_exTrk_locX_error;   //!
   TBranch        *b_MuTagIMO_exTrk_locY_error;   //!
   TBranch        *b_MuTagIMO_exTrk_angleXZ_error;   //!
   TBranch        *b_MuTagIMO_exTrk_angleYZ_error;   //!
   TBranch        *b_MuTagIMO_seg_isTagSeg;   //!
   TBranch        *b_MuTagIMO_seg_matchesBarCode;   //!
   TBranch        *b_MuTagIMO_seg_matchesPdg;   //!
   TBranch        *b_MuTagIMO_seg_exTrkIndex;   //!
   TBranch        *b_MuTagIMO_seg_trackIndex;   //!
   TBranch        *b_MuTagIMO_seg_stationLevel;   //!
   TBranch        *b_MuTagIMO_seg_isEndCap;   //!
   TBranch        *b_MuTagIMO_seg_isLarge;   //!
   TBranch        *b_MuTagIMO_seg_nrHoles;   //!
   TBranch        *b_MuTagIMO_seg_nrMLs;   //!
   TBranch        *b_MuTagIMO_seg_nrMdtHits;   //!
   TBranch        *b_MuTagIMO_seg_nrRpcHits;   //!
   TBranch        *b_MuTagIMO_seg_nrTgcHits;   //!
   TBranch        *b_MuTagIMO_seg_nrCscHits;   //!
   TBranch        *b_MuTagIMO_seg_phi;   //!
   TBranch        *b_MuTagIMO_seg_theta;   //!
   TBranch        *b_MuTagIMO_seg_chi2;   //!
   TBranch        *b_MuTagIMO_seg_cov11;   //!
   TBranch        *b_MuTagIMO_seg_cov12;   //!
   TBranch        *b_MuTagIMO_seg_cov13;   //!
   TBranch        *b_MuTagIMO_seg_cov14;   //!
   TBranch        *b_MuTagIMO_seg_cov15;   //!
   TBranch        *b_MuTagIMO_seg_cov22;   //!
   TBranch        *b_MuTagIMO_seg_cov23;   //!
   TBranch        *b_MuTagIMO_seg_cov24;   //!
   TBranch        *b_MuTagIMO_seg_cov25;   //!
   TBranch        *b_MuTagIMO_seg_cov33;   //!
   TBranch        *b_MuTagIMO_seg_cov34;   //!
   TBranch        *b_MuTagIMO_seg_cov35;   //!
   TBranch        *b_MuTagIMO_seg_cov44;   //!
   TBranch        *b_MuTagIMO_seg_cov45;   //!
   TBranch        *b_MuTagIMO_seg_cov55;   //!
   TBranch        *b_MuTagIMO_seg_gPosX;   //!
   TBranch        *b_MuTagIMO_seg_gPosY;   //!
   TBranch        *b_MuTagIMO_seg_gPosZ;   //!
   TBranch        *b_MuTagIMO_seg_gDirX;   //!
   TBranch        *b_MuTagIMO_seg_gDirY;   //!
   TBranch        *b_MuTagIMO_seg_gDirZ;   //!
   TBranch        *b_MuTagIMO_seg_locX;   //!
   TBranch        *b_MuTagIMO_seg_locY;   //!
   TBranch        *b_MuTagIMO_seg_angleXZ;   //!
   TBranch        *b_MuTagIMO_seg_angleYZ;   //!
   TBranch        *b_MuTagIMO_seg_locX_error;   //!
   TBranch        *b_MuTagIMO_seg_locY_error;   //!
   TBranch        *b_MuTagIMO_seg_angleXZ_error;   //!
   TBranch        *b_MuTagIMO_seg_angleYZ_error;   //!
   TBranch        *b_MuTagIMO_match_trackIndex;   //!
   TBranch        *b_MuTagIMO_match_locX;   //!
   TBranch        *b_MuTagIMO_match_locY;   //!
   TBranch        *b_MuTagIMO_match_angleXZ;   //!
   TBranch        *b_MuTagIMO_match_angleYZ;   //!
   TBranch        *b_MET_ExMiss0;   //!
   TBranch        *b_MET_EyMiss0;   //!
   TBranch        *b_MET_EtSum0;   //!
   TBranch        *b_MET_ExMiss;   //!
   TBranch        *b_MET_EyMiss;   //!
   TBranch        *b_MET_EtSum;   //!
   TBranch        *b_MET_ExMissTopo;   //!
   TBranch        *b_MET_EyMissTopo;   //!
   TBranch        *b_MET_EtSumTopo;   //!
   TBranch        *b_MET_ExMissCorr;   //!
   TBranch        *b_MET_EyMissCorr;   //!
   TBranch        *b_MET_EtSumCorr;   //!
   TBranch        *b_MET_ExMissLocHadTopo;   //!
   TBranch        *b_MET_EyMissLocHadTopo;   //!
   TBranch        *b_MET_EtSumLocHadTopo;   //!
   TBranch        *b_MET_ExMissCorrTopo;   //!
   TBranch        *b_MET_EyMissCorrTopo;   //!
   TBranch        *b_MET_EtSumCorrTopo;   //!
   TBranch        *b_MET_ExMissMu;   //!
   TBranch        *b_MET_EyMissMu;   //!
   TBranch        *b_MET_EtSumMu;   //!
   TBranch        *b_MET_ExMissMuBoyTrack;   //!
   TBranch        *b_MET_EyMissMuBoyTrack;   //!
   TBranch        *b_MET_EtSumMuBoyTrack;   //!
   TBranch        *b_MET_ExMissMuBoySpectro;   //!
   TBranch        *b_MET_EyMissMuBoySpectro;   //!
   TBranch        *b_MET_EtSumMuBoySpectro;   //!
   TBranch        *b_MET_ExMissMuBoy;   //!
   TBranch        *b_MET_EyMissMuBoy;   //!
   TBranch        *b_MET_EtSumMuBoy;   //!
   TBranch        *b_MET_ExMissFinal;   //!
   TBranch        *b_MET_EyMissFinal;   //!
   TBranch        *b_MET_EtSumFinal;   //!
   TBranch        *b_MET_ExMissRefFinal;   //!
   TBranch        *b_MET_EyMissRefFinal;   //!
   TBranch        *b_MET_EtSumRefFinal;   //!
   TBranch        *b_MET_ExMissCryo;   //!
   TBranch        *b_MET_EyMissCryo;   //!
   TBranch        *b_MET_EtSumCryo;   //!
   TBranch        *b_MET_ExMissCryoCone;   //!
   TBranch        *b_MET_EyMissCryoCone;   //!
   TBranch        *b_MET_EtSumCryoCone;   //!
   TBranch        *b_MET_ExMissDMCryo;   //!
   TBranch        *b_MET_EyMissDMCryo;   //!
   TBranch        *b_MET_EtSumDMCryo;   //!
   TBranch        *b_MET_ExMissDMCrack1;   //!
   TBranch        *b_MET_EyMissDMCrack1;   //!
   TBranch        *b_MET_EtSumDMCrack1;   //!
   TBranch        *b_MET_ExMissDMCrack2;   //!
   TBranch        *b_MET_EyMissDMCrack2;   //!
   TBranch        *b_MET_EtSumDMCrack2;   //!
   TBranch        *b_MET_ExMissDMAll;   //!
   TBranch        *b_MET_EyMissDMAll;   //!
   TBranch        *b_MET_EtSumDMAll;   //!
   TBranch        *b_MET_ExMissLocHadTopoObj;   //!
   TBranch        *b_MET_EyMissLocHadTopoObj;   //!
   TBranch        *b_MET_EtSumLocHadTopoObj;   //!
   TBranch        *b_MET_ExMissTopoObj;   //!
   TBranch        *b_MET_EyMissTopoObj;   //!
   TBranch        *b_MET_EtSumTopoObj;   //!
   TBranch        *b_MET_ExMissRefEle;   //!
   TBranch        *b_MET_EyMissRefEle;   //!
   TBranch        *b_MET_EtSumRefEle;   //!
   TBranch        *b_MET_ExMissRefGamma;   //!
   TBranch        *b_MET_EyMissRefGamma;   //!
   TBranch        *b_MET_EtSumRefGamma;   //!
   TBranch        *b_MET_ExMissRefMuo;   //!
   TBranch        *b_MET_EyMissRefMuo;   //!
   TBranch        *b_MET_EtSumRefMuo;   //!
   TBranch        *b_MET_ExMissRefMuoTrack;   //!
   TBranch        *b_MET_EyMissRefMuoTrack;   //!
   TBranch        *b_MET_EtSumRefMuoTrack;   //!
   TBranch        *b_MET_ExMissRefTau;   //!
   TBranch        *b_MET_EyMissRefTau;   //!
   TBranch        *b_MET_EtSumRefTau;   //!
   TBranch        *b_MET_ExMissRefJet;   //!
   TBranch        *b_MET_EyMissRefJet;   //!
   TBranch        *b_MET_EtSumRefJet;   //!
   TBranch        *b_MET_ExMissCellOut;   //!
   TBranch        *b_MET_EyMissCellOut;   //!
   TBranch        *b_MET_EtSumCellOut;   //!
   TBranch        *b_MET_ExFCALCorrTopo;   //!
   TBranch        *b_MET_EyFCALCorrTopo;   //!
   TBranch        *b_MET_EtSumFCALCorrTopo;   //!
   TBranch        *b_MET_ExFCALlocHadTopo;   //!
   TBranch        *b_MET_EyFCALlocHadTopo;   //!
   TBranch        *b_MET_EtSumFCALlocHadTopo;   //!
   TBranch        *b_MET_ExPEMB;   //!
   TBranch        *b_MET_EyPEMB;   //!
   TBranch        *b_MET_EtSumPEMB;   //!
   TBranch        *b_MET_nCellPEMB;   //!
   TBranch        *b_MET_ExEMB;   //!
   TBranch        *b_MET_EyEMB;   //!
   TBranch        *b_MET_EtSumEMB;   //!
   TBranch        *b_MET_nCellEMB;   //!
   TBranch        *b_MET_ExPEMEC;   //!
   TBranch        *b_MET_EyPEMEC;   //!
   TBranch        *b_MET_EtSumPEMEC;   //!
   TBranch        *b_MET_nCellPEMEC;   //!
   TBranch        *b_MET_ExEMEC;   //!
   TBranch        *b_MET_EyEMEC;   //!
   TBranch        *b_MET_EtSumEMEC;   //!
   TBranch        *b_MET_nCellEMEC;   //!
   TBranch        *b_MET_ExTILE;   //!
   TBranch        *b_MET_EyTILE;   //!
   TBranch        *b_MET_EtSumTILE;   //!
   TBranch        *b_MET_nCellTILE;   //!
   TBranch        *b_MET_ExHEC;   //!
   TBranch        *b_MET_EyHEC;   //!
   TBranch        *b_MET_EtSumHEC;   //!
   TBranch        *b_MET_nCellHEC;   //!
   TBranch        *b_MET_ExFCAL;   //!
   TBranch        *b_MET_EyFCAL;   //!
   TBranch        *b_MET_EtSumFCAL;   //!
   TBranch        *b_MET_nCellFCAL;   //!
   TBranch        *b_MET_ExBARReg;   //!
   TBranch        *b_MET_EyBARReg;   //!
   TBranch        *b_MET_EtSumBARReg;   //!
   TBranch        *b_MET_ExECReg;   //!
   TBranch        *b_MET_EyECReg;   //!
   TBranch        *b_MET_EtSumECReg;   //!
   TBranch        *b_MET_ExFCALReg;   //!
   TBranch        *b_MET_EyFCALReg;   //!
   TBranch        *b_MET_EtSumFCALReg;   //!
   TBranch        *b_L1Em_nRoI;   //!
   TBranch        *b_L1Em_RoIWord;   //!
   TBranch        *b_L1Em_Core;   //!
   TBranch        *b_L1Em_EmClus;   //!
   TBranch        *b_L1Em_TauClus;   //!
   TBranch        *b_L1Em_EmIsol;   //!
   TBranch        *b_L1Em_HdIsol;   //!
   TBranch        *b_L1Em_HdCore;   //!
   TBranch        *b_L1Em_EmTauThresh;   //!
   TBranch        *b_L1Em_eta;   //!
   TBranch        *b_L1Em_phi;   //!
   TBranch        *b_L1Jet_nRoI;   //!
   TBranch        *b_L1Jet_JetRoIWord;   //!
   TBranch        *b_L1Jet_ET4x4;   //!
   TBranch        *b_L1Jet_ET6x6;   //!
   TBranch        *b_L1Jet_ET8x8;   //!
   TBranch        *b_L1Jet_Thresh;   //!
   TBranch        *b_L1Jet_eta;   //!
   TBranch        *b_L1Jet_phi;   //!
   TBranch        *b_L1ET_EtMissHits;   //!
   TBranch        *b_L1ET_EtSumHits;   //!
   TBranch        *b_L1ET_Ex;   //!
   TBranch        *b_L1ET_Ey;   //!
   TBranch        *b_L1ET_EtMiss;   //!
   TBranch        *b_L1ET_EtSum;   //!
   TBranch        *b_nCTP_ROI;   //!
   TBranch        *b_CTP_ROI;   //!
   TBranch        *b_nMuCTPI_ROI;   //!
   TBranch        *b_muCTPI_ROI;   //!
   TBranch        *b_nEMTau_ROI;   //!
   TBranch        *b_EMTau_ROI;   //!
   TBranch        *b_nJetEnergy_ROI;   //!
   TBranch        *b_JetEnergy_ROI;   //!
   TBranch        *b_muctpi_nCandidates;   //!
   TBranch        *b_muctpi_windowSizeBC;   //!
   TBranch        *b_muctpi_bcid;   //!
   TBranch        *b_muctpi_PtMultiplicity;   //!
   TBranch        *b_muctpi_cand_sectorOverflow;   //!
   TBranch        *b_muctpi_cand_RoiOverflow;   //!
   TBranch        *b_muctpi_cand_RoiNumber;   //!
   TBranch        *b_muctpi_cand_overlapBits;   //!
   TBranch        *b_muctpi_cand_sectorID;   //!
   TBranch        *b_muctpi_cand_sectorLocation;   //!
   TBranch        *b_muctpi_cand_hemisphere;   //!
   TBranch        *b_muctpi_cand_Pt;   //!
   TBranch        *b_muctpi_cand_bcid;   //!
   TBranch        *b_muctpi_cand_isHighestPt;   //!
   TBranch        *b_muctpi_cand_sentRoI;   //!
   TBranch        *b_muctpi_roi_GBCID;   //!
   TBranch        *b_muctpi_roi_N_ROI;   //!
   TBranch        *b_muctpi_roi_SUM;   //!
   TBranch        *b_muctpi_roi_BCID;   //!
   TBranch        *b_muctpi_roi_First;   //!
   TBranch        *b_muctpi_roi_Acc;   //!
   TBranch        *b_muctpi_roi_O_ROI;   //!
   TBranch        *b_muctpi_roi_O_STR;   //!
   TBranch        *b_muctpi_roi_pT;   //!
   TBranch        *b_muctpi_roi_eta;   //!
   TBranch        *b_muctpi_roi_phi;   //!
   TBranch        *b_muctpi_rodheader_sourceId;   //!
   TBranch        *b_muctpi_rodheader_runNumber;   //!
   TBranch        *b_muctpi_rodheader_lvl1Id;   //!
   TBranch        *b_muctpi_rodheader_bcid;   //!
   TBranch        *b_muctpi_rodheader_lvl1TriggerType;   //!
   TBranch        *b_muctpi_rodheader_detectorEventType;   //!
   TBranch        *b_muctpi_rodheader_nDataWords;   //!
   TBranch        *b_muctpi_rodheader_statusWords;   //!
   TBranch        *b_nCandidates;   //!
   TBranch        *b_etaCand;   //!
   TBranch        *b_phiCand;   //!
   TBranch        *b_nItems;   //!
   TBranch        *b_itemName;   //!
   TBranch        *b_itemTBP;   //!
   TBranch        *b_itemTAP;   //!
   TBranch        *b_itemTAV;   //!
   TBranch        *b_nThresholds;   //!
   TBranch        *b_thresholdName;   //!
   TBranch        *b_thresholdMulti;   //!
   TBranch        *b_ctp_numberBC;   //!
   TBranch        *b_ctp_L1A_BC;   //!
   TBranch        *b_ctp_timeSec;   //!
   TBranch        *b_ctp_timeNanoSec;   //!
   TBranch        *b_ctp_nPITs;   //!
   TBranch        *b_ctp_firedItemsBeforePrescale;   //!
   TBranch        *b_ctp_bcid;   //!
   TBranch        *b_ctp_randomTrig;   //!
   TBranch        *b_ctp_prescaledClock;   //!
   TBranch        *b_ctp_bcIndexPIT;   //!
   TBranch        *b_ctp_pit;   //!
   TBranch        *b_ctp_bcIndexTriggerItems;   //!
   TBranch        *b_ctp_tbp;   //!
   TBranch        *b_ctp_tap;   //!
   TBranch        *b_ctp_tav;   //!
   TBranch        *b_ctp_rodheader_sourceId;   //!
   TBranch        *b_ctp_rodheader_runNumber;   //!
   TBranch        *b_ctp_rodheader_lvl1Id;   //!
   TBranch        *b_ctp_rodheader_bcid;   //!
   TBranch        *b_ctp_rodheader_lvl1TriggerType;   //!
   TBranch        *b_ctp_rodheader_detectorEventType;   //!
   TBranch        *b_ctp_rodheader_nDataWords;   //!
   TBranch        *b_ctp_rodheader_statusWords;   //!
#endif

   TBranch        *b_L1CaloPPM_ntt;   //!
   TBranch        *b_L1CaloPPM_eta;   //!
   TBranch        *b_L1CaloPPM_phi;   //!
   TBranch        *b_L1CaloPPM_emCrate;   //!
   TBranch        *b_L1CaloPPM_emModule;   //!
   TBranch        *b_L1CaloPPM_emSubmodule;   //!
   TBranch        *b_L1CaloPPM_emChannel;   //!
   TBranch        *b_L1CaloPPM_hadCrate;   //!
   TBranch        *b_L1CaloPPM_hadModule;   //!
   TBranch        *b_L1CaloPPM_hadSubmodule;   //!
   TBranch        *b_L1CaloPPM_hadChannel;   //!
   TBranch        *b_L1CaloPPM_emChannelId;   //!
   TBranch        *b_L1CaloPPM_hadChannelId;   //!
   TBranch        *b_L1CaloPPM_emTTCellsEnergy;   //!
   TBranch        *b_L1CaloPPM_hadTTCellsEnergy;   //!
   TBranch        *b_L1CaloPPM_emCaloWaves;   //!
   TBranch        *b_L1CaloPPM_hadCaloWaves;   //!
   TBranch        *b_L1CaloPPM_emPeak;   //!
   TBranch        *b_L1CaloPPM_emADCPeak;   //!
   TBranch        *b_L1CaloPPM_hadPeak;   //!
   TBranch        *b_L1CaloPPM_hadADCPeak;   //!
   TBranch        *b_L1CaloPPM_emLUT;   //!
   TBranch        *b_L1CaloPPM_hadLUT;   //!
   TBranch        *b_L1CaloPPM_emADC;   //!
   TBranch        *b_L1CaloPPM_hadADC;   //!
   TBranch        *b_L1CaloPPM_emEnergy;   //!
   TBranch        *b_L1CaloPPM_hadEnergy;   //!
   TBranch        *b_L1CaloPPM_emBCIDvec;   //!
   TBranch        *b_L1CaloPPM_emBCIDext;   //!
   TBranch        *b_L1CaloPPM_hadBCIDvec;   //!
   TBranch        *b_L1CaloPPM_hadBCIDext;   //!
   TBranch        *b_L1CaloPPM_emError;   //!
   TBranch        *b_L1CaloPPM_hadError;   //!
   TBranch        *b_L1CaloPPM_emBCID;   //!
   TBranch        *b_L1CaloPPM_hadBCID;   //!
   TBranch        *b_L1CaloPPM_emIsSaturated;   //!
   TBranch        *b_L1CaloPPM_hadIsSaturated;   //!
   TBranch        *b_L1CaloPPM_emIsFilled;   //!
   TBranch        *b_L1CaloPPM_hadIsFilled;   //!

#ifndef PPM_ONLY
   TBranch        *b_L1CaloCPM_RoI_n;   //!
   TBranch        *b_L1CaloCPM_RoI_crate;   //!
   TBranch        *b_L1CaloCPM_RoI_cpm;   //!
   TBranch        *b_L1CaloCPM_RoI_chip;   //!
   TBranch        *b_L1CaloCPM_RoI_location;   //!
   TBranch        *b_L1CaloCPM_RoI_hits;   //!
   TBranch        *b_L1CaloCPM_RoI_eta;   //!
   TBranch        *b_L1CaloCPM_RoI_phi;   //!
   TBranch        *b_L1CaloCPM_RoI_core;   //!
   TBranch        *b_L1CaloCPM_RoI_emClus;   //!
   TBranch        *b_L1CaloCPM_RoI_tauClus;   //!
   TBranch        *b_L1CaloCPM_RoI_emIsol;   //!
   TBranch        *b_L1CaloCPM_RoI_hadIsol;   //!
   TBranch        *b_L1CaloCPM_RoI_hadVeto;   //!
   TBranch        *b_L1CaloCPM_RoI_isEtMax;   //!
   TBranch        *b_L1CaloCPM_RoI_simHits;   //!
   TBranch        *b_L1CaloCPM_RoI_error;   //!
   TBranch        *b_L1CaloCPM_SimRoI_n;   //!
   TBranch        *b_L1CaloCPM_SimRoI_eta;   //!
   TBranch        *b_L1CaloCPM_SimRoI_phi;   //!
   TBranch        *b_L1CaloCPM_SimRoI_core;   //!
   TBranch        *b_L1CaloCPM_SimRoI_emClus;   //!
   TBranch        *b_L1CaloCPM_SimRoI_tauClus;   //!
   TBranch        *b_L1CaloCPM_SimRoI_emIsol;   //!
   TBranch        *b_L1CaloCPM_SimRoI_hadIsol;   //!
   TBranch        *b_L1CaloCPM_SimRoI_hadVeto;   //!
   TBranch        *b_L1CaloCPM_SimRoI_isEtMax;   //!
   TBranch        *b_L1CaloCPM_SimRoI_hits;   //!
   TBranch        *b_L1CaloCPM_SimRoI_roiWord;   //!
   TBranch        *b_L1CaloCPM_Hits_n;   //!
   TBranch        *b_L1CaloCPM_Hits_crate;   //!
   TBranch        *b_L1CaloCPM_Hits_module;   //!
   TBranch        *b_L1CaloCPM_Hits_peak;   //!
   TBranch        *b_L1CaloCPM_Hits_hitWord0;   //!
   TBranch        *b_L1CaloCPM_Hits_hitWord1;   //!
   TBranch        *b_L1CaloCPM_Hits_hitsVec0;   //!
   TBranch        *b_L1CaloCPM_Hits_hitsVec1;   //!
   TBranch        *b_L1CaloCPM_Towers_n;   //!
   TBranch        *b_L1CaloCPM_Towers_eta;   //!
   TBranch        *b_L1CaloCPM_Towers_phi;   //!
   TBranch        *b_L1CaloCPM_Towers_peak;   //!
   TBranch        *b_L1CaloCPM_Towers_emEnergy;   //!
   TBranch        *b_L1CaloCPM_Towers_hadEnergy;   //!
   TBranch        *b_L1CaloCPM_Towers_emEnergyVec;   //!
   TBranch        *b_L1CaloCPM_Towers_hadEnergyVec;   //!
   TBranch        *b_L1CaloCPM_Towers_emError;   //!
   TBranch        *b_L1CaloCPM_Towers_hadError;   //!
   TBranch        *b_L1CaloCPM_Towers_emErrorVec;   //!
   TBranch        *b_L1CaloCPM_Towers_hadErrorVec;   //!
   TBranch        *b_L1CaloCPM_CMM_n;   //!
   TBranch        *b_L1CaloCPM_CMM_crate;   //!
   TBranch        *b_L1CaloCPM_CMM_dataID;   //!
   TBranch        *b_L1CaloCPM_CMM_hitWord0;   //!
   TBranch        *b_L1CaloCPM_CMM_hitWord1;   //!
   TBranch        *b_L1CaloCPM_CMM_error0;   //!
   TBranch        *b_L1CaloCPM_CMM_error1;   //!
   TBranch        *b_L1CaloCPM_CMM_peak;   //!
   TBranch        *b_L1CaloCPM_CMM_hitsVec0;   //!
   TBranch        *b_L1CaloCPM_CMM_hitsVec1;   //!
   TBranch        *b_L1CaloCPM_CMM_errorVec0;   //!
   TBranch        *b_L1CaloCPM_CMM_errorVec1;   //!
   TBranch        *b_L1CaloJEM_JetE_n;   //!
   TBranch        *b_L1CaloJEM_JetEl_eta;   //!
   TBranch        *b_L1CaloJEM_JetEl_phi;   //!
   TBranch        *b_L1CaloJEM_JetEl_emEnergy;   //!
   TBranch        *b_L1CaloJEM_JetEl_hadEnergy;   //!
   TBranch        *b_L1CaloJEM_JetEl_energy;   //!
   TBranch        *b_L1CaloJEM_JetEl_isSaturated;   //!
   TBranch        *b_L1CaloJEM_JetEl_isEmSaturated;   //!
   TBranch        *b_L1CaloJEM_JetEl_isHadSaturated;   //!
   TBranch        *b_L1CaloJEM_JetEl_emError;   //!
   TBranch        *b_L1CaloJEM_JetEl_hadError;   //!
   TBranch        *b_L1CaloJEM_JetEl_linkError;   //!
   TBranch        *b_L1CaloJEM_JetEl_peak;   //!
   TBranch        *b_L1CaloJEM_JetEl_emEnergyVec;   //!
   TBranch        *b_L1CaloJEM_JetEl_hadEnergyVec;   //!
   TBranch        *b_L1CaloJEM_JetEl_emErrorVec;   //!
   TBranch        *b_L1CaloJEM_JetEl_hadErrorVec;   //!
   TBranch        *b_L1CaloJEM_JetEl_linkErrorVec;   //!
   TBranch        *b_L1CaloJEM_Hits_n;   //!
   TBranch        *b_L1CaloJEM_Hits_crate;   //!
   TBranch        *b_L1CaloJEM_Hits_module;   //!
   TBranch        *b_L1CaloJEM_Hits_jetHits;   //!
   TBranch        *b_L1CaloJEM_Hits_jetHitsVec;   //!
   TBranch        *b_L1CaloJEM_Hits_peak;   //!
   TBranch        *b_L1CaloJEM_Hits_forward;   //!
   TBranch        *b_L1CaloJEM_EtSums_n;   //!
   TBranch        *b_L1CaloJEM_EtSums_crate;   //!
   TBranch        *b_L1CaloJEM_EtSums_module;   //!
   TBranch        *b_L1CaloJEM_EtSums_et;   //!
   TBranch        *b_L1CaloJEM_EtSums_ex;   //!
   TBranch        *b_L1CaloJEM_EtSums_ey;   //!
   TBranch        *b_L1CaloJEM_EtSums_etVec;   //!
   TBranch        *b_L1CaloJEM_EtSums_exVec;   //!
   TBranch        *b_L1CaloJEM_EtSums_eyVec;   //!
   TBranch        *b_L1CaloJEM_EtSums_peak;   //!
   TBranch        *b_L1CaloJEM_EtSums_forward;   //!
   TBranch        *b_L1CaloJEM_CMMJetHits_n;   //!
   TBranch        *b_L1CaloJEM_CMMJetHits_crate;   //!
   TBranch        *b_L1CaloJEM_CMMJetHits_dataID;   //!
   TBranch        *b_L1CaloJEM_CMMJetHits_hits;   //!
   TBranch        *b_L1CaloJEM_CMMJetHits_error;   //!
   TBranch        *b_L1CaloJEM_CMMJetHits_hitsVec;   //!
   TBranch        *b_L1CaloJEM_CMMJetHits_errorVec;   //!
   TBranch        *b_L1CaloJEM_CMMJetHits_peak;   //!
   TBranch        *b_L1CaloJEM_CMMEtSums_n;   //!
   TBranch        *b_L1CaloJEM_CMMEtSums_crate;   //!
   TBranch        *b_L1CaloJEM_CMMEtSums_dataID;   //!
   TBranch        *b_L1CaloJEM_CMMEtSums_et;   //!
   TBranch        *b_L1CaloJEM_CMMEtSums_ex;   //!
   TBranch        *b_L1CaloJEM_CMMEtSums_ey;   //!
   TBranch        *b_L1CaloJEM_CMMEtSums_etError;   //!
   TBranch        *b_L1CaloJEM_CMMEtSums_exError;   //!
   TBranch        *b_L1CaloJEM_CMMEtSums_eyError;   //!
   TBranch        *b_L1CaloJEM_CMMEtSums_etVec;   //!
   TBranch        *b_L1CaloJEM_CMMEtSums_exVec;   //!
   TBranch        *b_L1CaloJEM_CMMEtSums_eyVec;   //!
   TBranch        *b_L1CaloJEM_CMMEtSums_etErrorVec;   //!
   TBranch        *b_L1CaloJEM_CMMEtSums_exErrorVec;   //!
   TBranch        *b_L1CaloJEM_CMMEtSums_eyErrorVec;   //!
   TBranch        *b_L1CaloJEM_CMMEtSums_peak;   //!
   TBranch        *b_L1CaloJEM_RoI_n;   //!
   TBranch        *b_L1CaloJEM_RoI_crate;   //!
   TBranch        *b_L1CaloJEM_RoI_jem;   //!
   TBranch        *b_L1CaloJEM_RoI_frame;   //!
   TBranch        *b_L1CaloJEM_RoI_location;   //!
   TBranch        *b_L1CaloJEM_RoI_eta;   //!
   TBranch        *b_L1CaloJEM_RoI_phi;   //!
   TBranch        *b_L1CaloJEM_RoI_forward;   //!
   TBranch        *b_L1CaloJEM_RoI_hits;   //!
   TBranch        *b_L1CaloJEM_RoI_error;   //!
   TBranch        *b_L1CaloJEM_CMMRoI_jetEtHits;   //!
   TBranch        *b_L1CaloJEM_CMMRoI_sumEtHits;   //!
   TBranch        *b_L1CaloJEM_CMMRoI_missingEtHits;   //!
   TBranch        *b_L1CaloJEM_CMMRoI_ex;   //!
   TBranch        *b_L1CaloJEM_CMMRoI_ey;   //!
   TBranch        *b_L1CaloJEM_CMMRoI_et;   //!
   TBranch        *b_L1CaloJEM_CMMRoI_jetEtError;   //!
   TBranch        *b_L1CaloJEM_CMMRoI_sumEtError;   //!
   TBranch        *b_L1CaloJEM_CMMRoI_missingEtError;   //!
   TBranch        *b_L1CaloJEM_CMMRoI_exError;   //!
   TBranch        *b_L1CaloJEM_CMMRoI_eyError;   //!
   TBranch        *b_L1CaloJEM_CMMRoI_etError;   //!
   TBranch        *b_L1CaloJEM_CMMRoI_jetEtRoiWord;   //!
   TBranch        *b_L1CaloJEM_CMMRoI_energyEtRoiWord0;   //!
   TBranch        *b_L1CaloJEM_CMMRoI_energyEtRoiWord1;   //!
   TBranch        *b_L1CaloJEM_CMMRoI_energyEtRoiWord2;   //!
   TBranch        *b_L1CaloRODHeader_nHeaders;   //!
   TBranch        *b_L1CaloRODHeader_version;   //!
   TBranch        *b_L1CaloRODHeader_majorVersion;   //!
   TBranch        *b_L1CaloRODHeader_minorVersion;   //!
   TBranch        *b_L1CaloRODHeader_sourceID;   //!
   TBranch        *b_L1CaloRODHeader_subDetectorID;   //!
   TBranch        *b_L1CaloRODHeader_moduleID;   //!
   TBranch        *b_L1CaloRODHeader_crate;   //!
   TBranch        *b_L1CaloRODHeader_sLink;   //!
   TBranch        *b_L1CaloRODHeader_dataType;   //!
   TBranch        *b_L1CaloRODHeader_run;   //!
   TBranch        *b_L1CaloRODHeader_runType;   //!
   TBranch        *b_L1CaloRODHeader_runNumber;   //!
   TBranch        *b_L1CaloRODHeader_extendedL1ID;   //!
   TBranch        *b_L1CaloRODHeader_ecrID;   //!
   TBranch        *b_L1CaloRODHeader_l1ID;   //!
   TBranch        *b_L1CaloRODHeader_bunchCrossing;   //!
   TBranch        *b_L1CaloRODHeader_l1TriggerType;   //!
   TBranch        *b_L1CaloRODHeader_detEventType;   //!
   TBranch        *b_L1CaloRODHeader_orbitCount;   //!
   TBranch        *b_L1CaloRODHeader_stepNumber;   //!
   TBranch        *b_L1CaloRODHeader_stepType;   //!
   TBranch        *b_L1CaloRODHeader_bcnMismatch;   //!
   TBranch        *b_L1CaloRODHeader_gLinkTimeout;   //!
   TBranch        *b_L1CaloRODHeader_dataTransportError;   //!
   TBranch        *b_L1CaloRODHeader_rodFifoOverflow;   //!
   TBranch        *b_L1CaloRODHeader_lvdsLinkError;   //!
   TBranch        *b_L1CaloRODHeader_cmmParityError;   //!
   TBranch        *b_L1CaloRODHeader_gLinkError;   //!
   TBranch        *b_L1CaloRODHeader_limitedRoISet;   //!
   TBranch        *b_L1CaloRODHeader_triggerTypeTimeout;   //!
#endif

#ifndef L1CALO_ONLY
   TBranch        *b_MemRSS;   //!
   TBranch        *b_MemVSize;   //!
   TBranch        *b_TimeTotal;   //!
   TBranch        *b_TimeSum;   //!
   TBranch        *b_TimeEventCounter;   //!
   TBranch        *b_TimeInDetPixelRawDataProvider;   //!
   TBranch        *b_TimeInDetSCTRawDataProvider;   //!
   TBranch        *b_TimeInDetTRTRawDataProvider;   //!
   TBranch        *b_TimeMuonMdtRawDataProvider;   //!
   TBranch        *b_TimeMuonRpcRawDataProvider;   //!
   TBranch        *b_TimeMuonTgcRawDataProvider;   //!
   TBranch        *b_TimeTrigConfDataIOVChanger;   //!
   TBranch        *b_TimeRoIBResultToAOD;   //!
   TBranch        *b_TimeTrigBSExtraction;   //!
   TBranch        *b_TimeTrigDecMaker;   //!
   TBranch        *b_TimeMainMonManager;   //!
   TBranch        *b_TimeInDetPixelClusterization;   //!
   TBranch        *b_TimeInDetSCT_Clusterization;   //!
   TBranch        *b_TimeInDetSiTrackerSpacePointFinder;   //!
   TBranch        *b_TimeSiCTBTracking;   //!
   TBranch        *b_TimePixel_CTBTracking;   //!
   TBranch        *b_TimeSCT_CTBTracking;   //!
   TBranch        *b_TimeInDetTRT_RIO_Maker;   //!
   TBranch        *b_TimeTRT_CTBTrackingPhase;   //!
   TBranch        *b_TimeTRTSegmentsFinder_ECphase;   //!
   TBranch        *b_TimeInDetCosmicsEventPhase;   //!
   TBranch        *b_TimeInDetTRT_RIO_MakerCosmics;   //!
   TBranch        *b_TimeInDetCTBTracking;   //!
   TBranch        *b_TimeTRT_CTBTracking;   //!
   TBranch        *b_TimeTRTSegmentsFinderBC;   //!
   TBranch        *b_TimeTRTSegmentsFinder_EC;   //!
   TBranch        *b_TimeTRT_SegmentsToTrack_Endcap;   //!
   TBranch        *b_TimeIdTrackCopyAmbiSolver_0;   //!
   TBranch        *b_TimeIdTrackCopyAmbiSolver_1;   //!
   TBranch        *b_TimeIdTrackCopyAmbiSolver_2;   //!
   TBranch        *b_TimeIdTrackCopyAmbiSolver_3;   //!
   TBranch        *b_TimeIdTrackCopyAmbiSolver_4;   //!
   TBranch        *b_TimeIdTrackCopyAmbiSolver_final;   //!
   TBranch        *b_TimeInDetTrackCollectionMerger;   //!
   TBranch        *b_TimeInDetCopyAlg;   //!
   TBranch        *b_TimeInDetParticleCreation;   //!
   TBranch        *b_TimeTileRChMaker;   //!
   TBranch        *b_TimeLArRawChannelBuilder;   //!
   TBranch        *b_TimeLArDigitThinner;   //!
   TBranch        *b_TimeTileDigitsFilter;   //!
   TBranch        *b_TimeCaloCellMaker;   //!
   TBranch        *b_TimeEmTowerBldr;   //!
   TBranch        *b_TimeLArClusterMaker;   //!
   TBranch        *b_TimeLAr7_11NocorrClusterMaker;   //!
   TBranch        *b_TimeCaloTopoCluster;   //!
   TBranch        *b_TimeCaloCell2TopoClusterMapper;   //!
   TBranch        *b_TimeCaloClusterTopoEM430Getter;   //!
   TBranch        *b_TimeEMCell2TopoCluster430;   //!
   TBranch        *b_TimeTileLookForMuAlg;   //!
   TBranch        *b_TimeTileMuonFitter;   //!
   TBranch        *b_TimeMdtRdoToMdtPrepData;   //!
   TBranch        *b_TimeRpcRdoToRpcPrepData;   //!
   TBranch        *b_TimeTgcRdoToTgcPrepData;   //!
   TBranch        *b_TimeRpcClusterBuilderPRD;   //!
   TBranch        *b_TimeMboyDigiEmptyLoop;   //!
   TBranch        *b_TimeMboyRec;   //!
   TBranch        *b_TimeMooSegmentMaker;   //!
   TBranch        *b_TimeMuonCombiTrackBuilder;   //!
   TBranch        *b_TimeMuidMooreTPCreator;   //!
   TBranch        *b_TimeInitializeMuonClusters;   //!
   TBranch        *b_TimeCaloTrkMuIdAlg;   //!
   TBranch        *b_TimeCaloTrkMuIdAlg2;   //!
   TBranch        *b_TimeMuTagMasterIMO;   //!
   TBranch        *b_TimeCombMuonRefit;   //!
   TBranch        *b_TimeMergeMuonCollections;   //!
   TBranch        *b_TimeMakeAODMuons;   //!
   TBranch        *b_TimeFinalizeMuonClusters;   //!
   TBranch        *b_TimeCmbTowerBldr;   //!
   TBranch        *b_TimeTowerJetInput;   //!
   TBranch        *b_TimeCone4H1TowerJets;   //!
   TBranch        *b_TimeMETAlg;   //!
   TBranch        *b_TimeInDetGlobalManager;   //!
   TBranch        *b_TimePixelMonManager;   //!
   TBranch        *b_TimeSCTMonManager;   //!
   TBranch        *b_TimeTRTMonManager;   //!
   TBranch        *b_TimeIDAlignMonManager;   //!
   TBranch        *b_TimeGlobalMonManager;   //!
   TBranch        *b_TimeJetElementMaker;   //!
   TBranch        *b_TimeCPMTowerMaker;   //!
   TBranch        *b_TimeEmTauTrigger;   //!
   TBranch        *b_TimeEnergyTrigger;   //!
   TBranch        *b_TimeJetTrigger;   //!
   TBranch        *b_TimeROD;   //!
   TBranch        *b_TimeJEPCMMMaker;   //!
   TBranch        *b_TimeCPCMMMaker;   //!
   TBranch        *b_TimeL1CaloMonManager;   //!
   TBranch        *b_TimeTriggerTowerMaker;   //!
   TBranch        *b_TimeL1MonManager;   //!
   TBranch        *b_TimeCTMonManager;   //!
   TBranch        *b_TimeHLTMonManager;   //!
   TBranch        *b_TimeTileTowerBldr;   //!
   TBranch        *b_TimeTileTopoCluster;   //!
   TBranch        *b_TimeTileCell2TopoClusterMapper;   //!
   TBranch        *b_TimeManagedAthenaTileMon;   //!
   TBranch        *b_TimeLArMonManager;   //!
   TBranch        *b_TimeJetMonManager;   //!
   TBranch        *b_TimeJetTagMonManager;   //!
   TBranch        *b_TimeMuonRawMonManager;   //!
   TBranch        *b_TimeCBNT_AthenaAware;   //!
   TBranch        *b_TimeCreateLumiBlockCollectionFromFile;   //!
   TBranch        *b_TimeStreamESD;   //!
   TBranch        *b_TimeStreamESD_FH;   //!
   TBranch        *b_TimeStream2Filter;   //!
   TBranch        *b_TimeComTagWriter;   //!
   TBranch        *b_TimeStreamTAGCOM;   //!
   TBranch        *b_TimeAANTupleStream;   //!
#endif
   
   cbntClass(string filename,bool isFileList=false);
   virtual ~cbntClass();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(void);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef cbntClass_cxx
cbntClass::cbntClass(string filename,bool isFileList)
{
	
	fChain = new TChain("CollectionTree","CollectionTree");
	
	if(isFileList){
		cerr << "Passed File list, loading files...";
		ifstream *fin = new ifstream(filename.c_str());
		
		char line[500];
		
		fin->getline(line,500);
		string directory=line;
		while(!fin->eof()){
			fin->getline(line,500);
			if(!strcmp(line,"\0")) break;
			
			string temp = directory + "/" + line;
			
			fChain->Add(temp.c_str());
		}
		
		delete fin; fin = 0;
		
		cerr << "done.\n";
	}
	else{
		cerr << "Adding file to Chain...";
		fChain->Add(filename.c_str());
		cerr << "done.\n";
	}
	
	Init();
	
}

cbntClass::~cbntClass()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t cbntClass::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t cbntClass::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (!fChain->InheritsFrom(TChain::Class()))  return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void cbntClass::Init(void)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   LVL1TriggerInfo = 0;
   LVL2TriggerInfo = 0;
   EventFilterInfo = 0;
   StreamTagName = 0;
   StreamTagType = 0;
   
#ifndef L1CALO_ONLY
   pixel_bec = 0;
   pixel_layer = 0;
   pixel_eta = 0;
   pixel_phi = 0;
   pixel_row = 0;
   pixel_col = 0;
   pixel_tot = 0;
   pixel_BCID = 0;
   pixel_LVL1 = 0;
   sct_rdo_strips = 0;
   sct_rdo_tbin = 0;
   sct_rdo_rdoId = 0;
   sct_rdo_bec = 0;
   sct_rdo_layer = 0;
   sct_rdo_eta = 0;
   sct_rdo_phi = 0;
   sct_rdo_side = 0;
   sct_rdo_FirstSecondHitError = 0;
   tdc_channel = 0;
   tdc_phase = 0;
   sct_bsErr_type = 0;
   sct_bsErr_eta = 0;
   sct_bsErr_phi = 0;
   sct_bsErr_layer = 0;
   sct_bsErr_side = 0;
   sct_bsErr_bec = 0;
   sct_clus_x = 0;
   sct_clus_y = 0;
   sct_clus_z = 0;
   sct_clus_groupsize = 0;
   sct_clus_bec = 0;
   sct_clus_layer = 0;
   sct_clus_eta = 0;
   sct_clus_phi = 0;
   sct_clus_side = 0;
   pixel_clus_LocX = 0;
   pixel_clus_LocY = 0;
   pixel_clus_z = 0;
   pixel_clus_groupsize = 0;
   pixel_clus_bec = 0;
   pixel_clus_layer = 0;
   pixel_clus_phi = 0;
   pixel_clus_clx = 0;
   pixel_clus_cly = 0;
   pixel_clus_clz = 0;
   pixel_clus_row = 0;
   pixel_clus_col = 0;
   sct_sp_x = 0;
   sct_sp_y = 0;
   sct_sp_z = 0;
   sct_sp_barrelendcap = 0;
   sct_sp_layer = 0;
   sct_sp_phi = 0;
   sct_sp_eta = 0;
   pixel_sp_x = 0;
   pixel_sp_y = 0;
   pixel_sp_z = 0;
   pixel_sp_barrelendcap = 0;
   pixel_sp_layer = 0;
   pixel_sp_phi = 0;
   pixel_sp_eta = 0;
   trk_nPixelHits = 0;
   trk_nSctHits = 0;
   trk_nTrtHits = 0;
   trk_PixResPhi = 0;
   trk_PixResEta = 0;
   trk_PixPullPhi = 0;
   trk_PixPullEta = 0;
   trk_PixErrTrkPhi = 0;
   trk_PixErrTrkEta = 0;
   trk_PixErrHitPhi = 0;
   trk_PixErrHitEta = 0;
   trk_Pix_bec = 0;
   trk_Pix_layer = 0;
   trk_Pix_eta = 0;
   trk_Pix_phi = 0;
   trk_Pix_clusWidthRow = 0;
   trk_Pix_clusWidthCol = 0;
   trk_Pix_LocX = 0;
   trk_Pix_LocY = 0;
   trk_SctRes = 0;
   trk_SctPull = 0;
   trk_SctErrTrk = 0;
   trk_SctErrHit = 0;
   trk_Sct_bec = 0;
   trk_Sct_layer = 0;
   trk_Sct_eta = 0;
   trk_Sct_phi = 0;
   trk_Sct_side = 0;
   trk_Sct_rdoId = 0;
   trk_Sct_clusGroupsize = 0;
   trk_Sct_clusx = 0;
   trk_Sct_clusy = 0;
   trk_Sct_clusz = 0;
   trk_TrtRes = 0;
   trk_TrtPull = 0;
   trk_TrtErrTrk = 0;
   trk_TrtErrHit = 0;
   trk_Trt_R = 0;
   trk_Trt_Rtrack = 0;
   trk_Trt_t = 0;
   trk_Trt_x = 0;
   trk_Trt_y = 0;
   trk_Trt_HL = 0;
   trk_Trt_strawlayer = 0;
   trk_Trt_bec = 0;
   trk_Trt_layer = 0;
   trk_Trt_straw = 0;
   trk_Trt_phisector = 0;
   trk_Rec_d0 = 0;
   trk_Rec_z0 = 0;
   trk_Rec_phi0 = 0;
   trk_Rec_theta0 = 0;
   trk_Rec_qoverp = 0;
   trk_Rec_chi2 = 0;
   trk_Rec_ndof = 0;
   trk_Rec_eta = 0;
   trk_Rec_error_d0 = 0;
   trk_Rec_error_z0 = 0;
   trk_Rec_error_phi0 = 0;
   trk_Rec_error_theta0 = 0;
   trk_Rec_error_qoverp = 0;
   trk_Rec_chi2prob = 0;
   trk_Rec_author = 0;
   Eh_PresB = 0;
   Eh_EMB = 0;
   Eh_EMEC = 0;
   Eh_Tile = 0;
   Eh_TileGap = 0;
   Eh_HEC = 0;
   Eh_FCal = 0;
   Eh_PresE = 0;
   Eh_Scint = 0;
   ECellsLAr = 0;
   EtaCellsLAr = 0;
   PhiCellsLAr = 0;
   QCellsLAr = 0;
   GainCellsLAr = 0;
   DetCellsLAr = 0;
   TimeCellsLAr = 0;
   BadCellsLAr = 0;
   IdCellsLAr = 0;
   LArDigit_layer = 0;
   LArDigit_ieta = 0;
   LArDigit_calo = 0;
   LArDigit_iphi = 0;
   LArDigit_barrel_ec = 0;
   LArDigit_pos_neg = 0;
   LArDigit_FT = 0;
   LArDigit_slot = 0;
   LArDigit_channel = 0;
   LArDigit_gain = 0;
   LArDigit_Samples = 0;
   LArDigit_offlineId = 0;
   TileCellE = 0;
   TileCellTime = 0;
   TileCellEta = 0;
   TileCellPhi = 0;
   TileMBTSCounter = 0;
   TileMBTSE = 0;
   TileMBTSTime = 0;
   TileMBTSQuality = 0;
   TileMBTSEta = 0;
   TileMBTSPhi = 0;
   TileCellX = 0;
   TileCellY = 0;
   TileCellZ = 0;
   TileMBTSX = 0;
   TileMBTSY = 0;
   TileMBTSZ = 0;
   TileCellEdiff = 0;
   TileCellTimediff = 0;
   TileCellGain1 = 0;
   TileCellGain2 = 0;
   TileCellModule = 0;
   TileCellPartition = 0;
   TileCellTower = 0;
   TileCellSample = 0;
   TileCellChan1 = 0;
   TileCellChan2 = 0;
   TileCellPMT1 = 0;
   TileCellPMT2 = 0;
   TileCellStatus1 = 0;
   TileCellStatus2 = 0;
   TileMBTSModule = 0;
   TileMBTSGain = 0;
   TileMBTSStatus = 0;
   cl_et = 0;
   cl_e = 0;
   cl_eemb0 = 0;
   cl_eemb1 = 0;
   cl_eemb2 = 0;
   cl_eemb3 = 0;
   cl_nemb0 = 0;
   cl_nemb1 = 0;
   cl_nemb2 = 0;
   cl_nemb3 = 0;
   cl_phi2 = 0;
   cl_eta0 = 0;
   cl_eta1 = 0;
   cl_eta2 = 0;
   cl_eta3 = 0;
   cl_eeme0 = 0;
   cl_eeme1 = 0;
   cl_eeme2 = 0;
   cl_eeme3 = 0;
   cl_neme0 = 0;
   cl_neme1 = 0;
   cl_neme2 = 0;
   cl_neme3 = 0;
   cl_etileg1 = 0;
   cl_etileg2 = 0;
   cl_etileg3 = 0;
   cl_ntileg1 = 0;
   cl_ntileg2 = 0;
   cl_ntileg3 = 0;
   cl_eta = 0;
   cl_phi = 0;
   cl_reco_stat = 0;
   cl_m1_eta = 0;
   cl_m1_phi = 0;
   cl_m2_r = 0;
   cl_m2_lambda = 0;
   cl_delta_phi = 0;
   cl_delta_theta = 0;
   cl_delta_alpha = 0;
   cl_center_x = 0;
   cl_center_y = 0;
   cl_center_z = 0;
   cl_center_lambda = 0;
   cl_lateral = 0;
   cl_longitudinal = 0;
   cl_eng_frac_em = 0;
   cl_eng_frac_max = 0;
   cl_eng_frac_core = 0;
   cl_m1_dens = 0;
   cl_m2_dens = 0;
   cl_isol = 0;
   cl_ntotcells = 0;
   cl_et_topo = 0;
   cl_e_topo = 0;
   cl_eemb0_topo = 0;
   cl_eemb1_topo = 0;
   cl_eemb2_topo = 0;
   cl_eemb3_topo = 0;
   cl_nemb0_topo = 0;
   cl_nemb1_topo = 0;
   cl_nemb2_topo = 0;
   cl_nemb3_topo = 0;
   cl_phi2_topo = 0;
   cl_eta0_topo = 0;
   cl_eta1_topo = 0;
   cl_eta2_topo = 0;
   cl_eta3_topo = 0;
   cl_eeme0_topo = 0;
   cl_eeme1_topo = 0;
   cl_eeme2_topo = 0;
   cl_eeme3_topo = 0;
   cl_neme0_topo = 0;
   cl_neme1_topo = 0;
   cl_neme2_topo = 0;
   cl_neme3_topo = 0;
   cl_etileg1_topo = 0;
   cl_etileg2_topo = 0;
   cl_etileg3_topo = 0;
   cl_ntileg1_topo = 0;
   cl_ntileg2_topo = 0;
   cl_ntileg3_topo = 0;
   cl_eta_topo = 0;
   cl_phi_topo = 0;
   cl_reco_stat_topo = 0;
   cl_m1_eta_topo = 0;
   cl_m1_phi_topo = 0;
   cl_m2_r_topo = 0;
   cl_m2_lambda_topo = 0;
   cl_delta_phi_topo = 0;
   cl_delta_theta_topo = 0;
   cl_delta_alpha_topo = 0;
   cl_center_x_topo = 0;
   cl_center_y_topo = 0;
   cl_center_z_topo = 0;
   cl_center_lambda_topo = 0;
   cl_lateral_topo = 0;
   cl_longitudinal_topo = 0;
   cl_eng_frac_em_topo = 0;
   cl_eng_frac_max_topo = 0;
   cl_eng_frac_core_topo = 0;
   cl_m1_dens_topo = 0;
   cl_m2_dens_topo = 0;
   cl_isol_topo = 0;
   cl_ehec0_topo = 0;
   cl_ehec1_topo = 0;
   cl_ehec2_topo = 0;
   cl_ehec3_topo = 0;
   cl_nhec0_topo = 0;
   cl_nhec1_topo = 0;
   cl_nhec2_topo = 0;
   cl_nhec3_topo = 0;
   cl_etileb0_topo = 0;
   cl_etileb1_topo = 0;
   cl_etileb2_topo = 0;
   cl_ntileb0_topo = 0;
   cl_ntileb1_topo = 0;
   cl_ntileb2_topo = 0;
   cl_etilee0_topo = 0;
   cl_etilee1_topo = 0;
   cl_etilee2_topo = 0;
   cl_efcal0_topo = 0;
   cl_efcal1_topo = 0;
   cl_efcal2_topo = 0;
   cl_ntilee0_topo = 0;
   cl_ntilee1_topo = 0;
   cl_ntilee2_topo = 0;
   cl_nfcal0_topo = 0;
   cl_nfcal1_topo = 0;
   cl_nfcal2_topo = 0;
   cl_ntotcells_topo = 0;
   cl_et_topoEM430 = 0;
   cl_e_topoEM430 = 0;
   cl_eemb0_topoEM430 = 0;
   cl_eemb1_topoEM430 = 0;
   cl_eemb2_topoEM430 = 0;
   cl_eemb3_topoEM430 = 0;
   cl_nemb0_topoEM430 = 0;
   cl_nemb1_topoEM430 = 0;
   cl_nemb2_topoEM430 = 0;
   cl_nemb3_topoEM430 = 0;
   cl_phi2_topoEM430 = 0;
   cl_eta0_topoEM430 = 0;
   cl_eta1_topoEM430 = 0;
   cl_eta2_topoEM430 = 0;
   cl_eta3_topoEM430 = 0;
   cl_eeme0_topoEM430 = 0;
   cl_eeme1_topoEM430 = 0;
   cl_eeme2_topoEM430 = 0;
   cl_eeme3_topoEM430 = 0;
   cl_neme0_topoEM430 = 0;
   cl_neme1_topoEM430 = 0;
   cl_neme2_topoEM430 = 0;
   cl_neme3_topoEM430 = 0;
   cl_etileg1_topoEM430 = 0;
   cl_etileg2_topoEM430 = 0;
   cl_etileg3_topoEM430 = 0;
   cl_ntileg1_topoEM430 = 0;
   cl_ntileg2_topoEM430 = 0;
   cl_ntileg3_topoEM430 = 0;
   cl_eta_topoEM430 = 0;
   cl_phi_topoEM430 = 0;
   cl_reco_stat_topoEM430 = 0;
   cl_m1_eta_topoEM430 = 0;
   cl_m1_phi_topoEM430 = 0;
   cl_m2_r_topoEM430 = 0;
   cl_m2_lambda_topoEM430 = 0;
   cl_delta_phi_topoEM430 = 0;
   cl_delta_theta_topoEM430 = 0;
   cl_delta_alpha_topoEM430 = 0;
   cl_center_x_topoEM430 = 0;
   cl_center_y_topoEM430 = 0;
   cl_center_z_topoEM430 = 0;
   cl_center_lambda_topoEM430 = 0;
   cl_lateral_topoEM430 = 0;
   cl_longitudinal_topoEM430 = 0;
   cl_eng_frac_em_topoEM430 = 0;
   cl_eng_frac_max_topoEM430 = 0;
   cl_eng_frac_core_topoEM430 = 0;
   cl_m1_dens_topoEM430 = 0;
   cl_m2_dens_topoEM430 = 0;
   cl_isol_topoEM430 = 0;
   cl_ntotcells_topoEM430 = 0;
   EtaTileMuonTag = 0;
   PhiTileMuonTag = 0;
   EnergyVecTileMuonTag = 0;
   LabelTileMuonTag = 0;
   TileCosmicsHT_pathTop = 0;
   TileCosmicsHT_pathBottom = 0;
   TileCosmicsHT_energyTop = 0;
   TileCosmicsHT_energyBottom = 0;
   TileCosmicsHT_cellE = 0;
   TileCosmicsHT_cellT = 0;
   TileCosmicsHT_cellEta = 0;
   TileCosmicsHT_cellPhi = 0;
   TileCosmicsHT_cellSample = 0;
   TileCosmicsHT_cellEdiff = 0;
   TileCosmicsHT_cellTdiff = 0;
   EtaTileMuonRODTag = 0;
   PhiTileMuonRODTag = 0;
   EnergyVecTileMuonRODTag = 0;
   LabelTileMuonRODTag = 0;
   mdt_tdc = 0;
   mdt_adc = 0;
   mdt_station = 0;
   mdt_eta = 0;
   mdt_phi = 0;
   mdt_multi = 0;
   mdt_layer = 0;
   mdt_wire = 0;
   mdt_nmaxtubes = 0;
   mdt_globPosX = 0;
   mdt_globPosY = 0;
   mdt_globPosZ = 0;
   mdt_subid = 0;
   mdt_rodid = 0;
   mdt_csmid = 0;
   mdt_tdcid = 0;
   mdt_chanid = 0;
   mdt_fine = 0;
   mdt_coarse = 0;
   mdt_width = 0;
   rpc_prd_station = 0;
   rpc_prd_eta = 0;
   rpc_prd_phi = 0;
   rpc_prd_doublr = 0;
   rpc_prd_doublz = 0;
   rpc_prd_doublphi = 0;
   rpc_prd_gasgap = 0;
   rpc_prd_measphi = 0;
   rpc_prd_strip = 0;
   rpc_prd_time = 0;
   rpc_prd_stripx = 0;
   rpc_prd_stripy = 0;
   rpc_prd_stripz = 0;
   rpc_prd_triggerInfo = 0;
   rpc_prd_ambigFlag = 0;
   rpc_clus_station = 0;
   rpc_clus_eta = 0;
   rpc_clus_phi = 0;
   rpc_clus_doublr = 0;
   rpc_clus_doublz = 0;
   rpc_clus_doublphi = 0;
   rpc_clus_gasgap = 0;
   rpc_clus_measphi = 0;
   rpc_clus_size = 0;
   rpc_clus_time = 0;
   rpc_clus_posx = 0;
   rpc_clus_posy = 0;
   rpc_clus_posz = 0;
   rpc_pad_id = 0;
   rpc_pad_bcid = 0;
   rpc_pad_lvl1id = 0;
   rpc_pad_sectorid = 0;
   rpc_pad_status = 0;
   rpc_pad_error = 0;
   rpc_sector = 0;
   rpc_padId = 0;
   rpc_status = 0;
   rpc_ercode = 0;
   rpc_cmaId = 0;
   rpc_fel1Id = 0;
   rpc_febcId = 0;
   rpc_crc = 0;
   rpc_bcId = 0;
   rpc_ticks = 0;
   rpc_ijk = 0;
   rpc_cmachan = 0;
   rpc_overlap = 0;
   rpc_threshold = 0;
   rpc_SL_sectorId = 0;
   rpc_SL_bcid = 0;
   rpc_SL_lvl1id = 0;
   rpc_SLhit_sector = 0;
   rpc_SLhit_rowinBcid = 0;
   rpc_SLhit_triggerBcid = 0;
   rpc_SLhit_padId = 0;
   rpc_SLhit_ptId = 0;
   rpc_SLhit_roi = 0;
   rpc_SLhit_outerPlane = 0;
   rpc_SLhit_overlapPhi = 0;
   rpc_SLhit_overlapEta = 0;
   tgc_bcTag = 0;
   tgc_cointrackletbcTag = 0;
   tgc_coinhighptbcTag = 0;
   tgc_coinslbcTag = 0;
   tgc_cointype = 0;
   tgc_cointype_Prev = 0;
   tgc_cointype_Next = 0;
   tgc_station = 0;
   tgc_eta = 0;
   tgc_phi = 0;
   tgc_gasGap = 0;
   tgc_isStrip = 0;
   tgc_channel = 0;
   tgc_globPosX = 0;
   tgc_globPosY = 0;
   tgc_globPosZ = 0;
   tgc_shortWidth = 0;
   tgc_longWidth = 0;
   tgc_length = 0;
   tgc_cointrackletdelta = 0;
   tgc_cointrackletposx_in = 0;
   tgc_cointrackletposy_in = 0;
   tgc_cointrackletposz_in = 0;
   tgc_cointrackletposx_out = 0;
   tgc_cointrackletposy_out = 0;
   tgc_cointrackletposz_out = 0;
   tgc_cointrackletstrip = 0;
   tgc_cointrackletforward = 0;
   tgc_cointrackletwidthout = 0;
   tgc_cointrackletwidthin = 0;
   tgc_cointrackletstationeta = 0;
   tgc_cointrackletstationphi = 0;
   tgc_cointrackletsector = 0;
   tgc_cointracklettrackletid = 0;
   tgc_coinhighptdelta = 0;
   tgc_coinhighptposx_in = 0;
   tgc_coinhighptposy_in = 0;
   tgc_coinhighptposz_in = 0;
   tgc_coinhighptposx_out = 0;
   tgc_coinhighptposy_out = 0;
   tgc_coinhighptposz_out = 0;
   tgc_coinhighptstrip = 0;
   tgc_coinhighptforward = 0;
   tgc_coinhighptwidthout = 0;
   tgc_coinhighptwidthin = 0;
   tgc_coinhighptstationeta = 0;
   tgc_coinhighptstationphi = 0;
   tgc_coinhighptsector = 0;
   tgc_coinhighpttrackletid = 0;
   tgc_coinslptthresh = 0;
   tgc_coinslposx_out = 0;
   tgc_coinslposy_out = 0;
   tgc_coinslposz_out = 0;
   tgc_coinslroi = 0;
   tgc_coinslforward = 0;
   tgc_coinslwidthr = 0;
   tgc_coinslwidthphi = 0;
   tgc_coinslstationeta = 0;
   tgc_coinslstationphi = 0;
   tgc_coinslsector = 0;
   tgc_coinsltrackletid = 0;
   tgc_coinsltrackletidstrip = 0;
   tgc_station_Prev = 0;
   tgc_eta_Prev = 0;
   tgc_phi_Prev = 0;
   tgc_gasGap_Prev = 0;
   tgc_isStrip_Prev = 0;
   tgc_channel_Prev = 0;
   tgc_globPosX_Prev = 0;
   tgc_globPosY_Prev = 0;
   tgc_globPosZ_Prev = 0;
   tgc_shortWidth_Prev = 0;
   tgc_longWidth_Prev = 0;
   tgc_length_Prev = 0;
   tgc_cointrackletdelta_Prev = 0;
   tgc_cointrackletposx_in_Prev = 0;
   tgc_cointrackletposy_in_Prev = 0;
   tgc_cointrackletposz_in_Prev = 0;
   tgc_cointrackletposx_out_Prev = 0;
   tgc_cointrackletposy_out_Prev = 0;
   tgc_cointrackletposz_out_Prev = 0;
   tgc_cointrackletstrip_Prev = 0;
   tgc_cointrackletforward_Prev = 0;
   tgc_cointrackletwidthout_Prev = 0;
   tgc_cointrackletwidthin_Prev = 0;
   tgc_cointrackletstationeta_Prev = 0;
   tgc_cointrackletstationphi_Prev = 0;
   tgc_cointrackletsector_Prev = 0;
   tgc_cointracklettrackletid_Prev = 0;
   tgc_coinhighptdelta_Prev = 0;
   tgc_coinhighptposx_in_Prev = 0;
   tgc_coinhighptposy_in_Prev = 0;
   tgc_coinhighptposz_in_Prev = 0;
   tgc_coinhighptposx_out_Prev = 0;
   tgc_coinhighptposy_out_Prev = 0;
   tgc_coinhighptposz_out_Prev = 0;
   tgc_coinhighptstrip_Prev = 0;
   tgc_coinhighptforward_Prev = 0;
   tgc_coinhighptwidthout_Prev = 0;
   tgc_coinhighptwidthin_Prev = 0;
   tgc_coinhighptstationeta_Prev = 0;
   tgc_coinhighptstationphi_Prev = 0;
   tgc_coinhighptsector_Prev = 0;
   tgc_coinhighpttrackletid_Prev = 0;
   tgc_coinslptthresh_Prev = 0;
   tgc_coinslposx_out_Prev = 0;
   tgc_coinslposy_out_Prev = 0;
   tgc_coinslposz_out_Prev = 0;
   tgc_coinslroi_Prev = 0;
   tgc_coinslforward_Prev = 0;
   tgc_coinslwidthr_Prev = 0;
   tgc_coinslwidthphi_Prev = 0;
   tgc_coinslstationeta_Prev = 0;
   tgc_coinslstationphi_Prev = 0;
   tgc_coinslsector_Prev = 0;
   tgc_coinsltrackletid_Prev = 0;
   tgc_coinsltrackletidstrip_Prev = 0;
   tgc_station_Next = 0;
   tgc_eta_Next = 0;
   tgc_phi_Next = 0;
   tgc_gasGap_Next = 0;
   tgc_isStrip_Next = 0;
   tgc_channel_Next = 0;
   tgc_globPosX_Next = 0;
   tgc_globPosY_Next = 0;
   tgc_globPosZ_Next = 0;
   tgc_shortWidth_Next = 0;
   tgc_longWidth_Next = 0;
   tgc_length_Next = 0;
   tgc_cointrackletdelta_Next = 0;
   tgc_cointrackletposx_in_Next = 0;
   tgc_cointrackletposy_in_Next = 0;
   tgc_cointrackletposz_in_Next = 0;
   tgc_cointrackletposx_out_Next = 0;
   tgc_cointrackletposy_out_Next = 0;
   tgc_cointrackletposz_out_Next = 0;
   tgc_cointrackletstrip_Next = 0;
   tgc_cointrackletforward_Next = 0;
   tgc_cointrackletwidthout_Next = 0;
   tgc_cointrackletwidthin_Next = 0;
   tgc_cointrackletstationeta_Next = 0;
   tgc_cointrackletstationphi_Next = 0;
   tgc_cointrackletsector_Next = 0;
   tgc_cointracklettrackletid_Next = 0;
   tgc_coinhighptdelta_Next = 0;
   tgc_coinhighptposx_in_Next = 0;
   tgc_coinhighptposy_in_Next = 0;
   tgc_coinhighptposz_in_Next = 0;
   tgc_coinhighptposx_out_Next = 0;
   tgc_coinhighptposy_out_Next = 0;
   tgc_coinhighptposz_out_Next = 0;
   tgc_coinhighptstrip_Next = 0;
   tgc_coinhighptforward_Next = 0;
   tgc_coinhighptwidthout_Next = 0;
   tgc_coinhighptwidthin_Next = 0;
   tgc_coinhighptstationeta_Next = 0;
   tgc_coinhighptstationphi_Next = 0;
   tgc_coinhighptsector_Next = 0;
   tgc_coinhighpttrackletid_Next = 0;
   tgc_coinslptthresh_Next = 0;
   tgc_coinslposx_out_Next = 0;
   tgc_coinslposy_out_Next = 0;
   tgc_coinslposz_out_Next = 0;
   tgc_coinslroi_Next = 0;
   tgc_coinslforward_Next = 0;
   tgc_coinslwidthr_Next = 0;
   tgc_coinslwidthphi_Next = 0;
   tgc_coinslstationeta_Next = 0;
   tgc_coinslstationphi_Next = 0;
   tgc_coinslsector_Next = 0;
   tgc_coinsltrackletid_Next = 0;
   tgc_coinsltrackletidstrip_Next = 0;
   IS_Xpt = 0;
   IS_Ypt = 0;
   IS_Zpt = 0;
   IS_Xvec = 0;
   IS_Yvec = 0;
   IS_Zvec = 0;
   IS_QualityFactor = 0;
   IS_NbreOfMultiLayer = 0;
   IS_TrackSharing = 0;
   IS_StationName = 0;
   IS_Ndigits = 0;
   IS_HitPosition = 0;
   IS_Rdigi = 0;
   IS_Rtrack = 0;
   IS_Xdca = 0;
   IS_Ydca = 0;
   IS_Zdca = 0;
   IS_Sdca = 0;
   IS_Reso = 0;
   IS_JTYP = 0;
   IS_JFF = 0;
   IS_JZZ = 0;
   IS_JOB = 0;
   IS_JSPLI = 0;
   IS_JSL = 0;
   IS_JTUBE = 0;
   IS_JSZ = 0;
   IS_JSTRI = 0;
   IS_DriftTime = 0;
   IS_ChamberTech = 0;
   IS_StationNber = 0;
   IS_StationEta = 0;
   IS_StationPhi = 0;
   IS_Multilayer = 0;
   IS_TubeLayer = 0;
   IS_Tube = 0;
   IS_DoubletR = 0;
   IS_DoubletZ = 0;
   IS_DoubletPhi = 0;
   IS_GasGap = 0;
   IS_MeasuresPhi = 0;
   IS_Strip = 0;
   IS_IsStrip = 0;
   IS_Channel = 0;
   IS_ChamberLayer = 0;
   IS_WireLayer = 0;
   IS_RpcTime = 0;
   VT_Va = 0;
   VT_A0 = 0;
   VT_Z = 0;
   VT_Phi = 0;
   VT_CotTh = 0;
   VT_PTInv = 0;
   VT_Cov11 = 0;
   VT_Cov21 = 0;
   VT_Cov22 = 0;
   VT_Cov31 = 0;
   VT_Cov32 = 0;
   VT_Cov33 = 0;
   VT_Cov41 = 0;
   VT_Cov42 = 0;
   VT_Cov43 = 0;
   VT_Cov44 = 0;
   VT_Cov51 = 0;
   VT_Cov52 = 0;
   VT_Cov53 = 0;
   VT_Cov54 = 0;
   VT_Cov55 = 0;
   VT_Xpt = 0;
   VT_Ypt = 0;
   VT_Zpt = 0;
   VT_Xvec = 0;
   VT_Yvec = 0;
   VT_Zvec = 0;
   VT_Mom = 0;
   VT_digits = 0;
   VT_HitPosition = 0;
   VT_TrHi_Rdigi = 0;
   VT_TrHi_Rtrack = 0;
   VT_TrHi_Xdca = 0;
   VT_TrHi_Ydca = 0;
   VT_TrHi_Zdca = 0;
   VT_TrHi_Sdca = 0;
   VT_TrHi_Reso = 0;
   VT_TrHi_RZSsim = 0;
   VT_TrHi_EZSfit = 0;
   VT_TrHi_JTYP = 0;
   VT_TrHi_JFF = 0;
   VT_TrHi_JZZ = 0;
   VT_TrHi_JOB = 0;
   VT_TrHi_JSPLI = 0;
   VT_TrHi_JSL = 0;
   VT_TrHi_JTUBE = 0;
   VT_TrHi_JSZ = 0;
   VT_TrHi_JSTRI = 0;
   VT_TrHi_DriftTime = 0;
   VT_TrHi_ChamberTech = 0;
   VT_TrHi_StationNber = 0;
   VT_TrHi_StationEta = 0;
   VT_TrHi_StationPhi = 0;
   VT_TrHi_Multilayer = 0;
   VT_TrHi_TubeLayer = 0;
   VT_TrHi_Tube = 0;
   VT_TrHi_DoubletR = 0;
   VT_TrHi_DoubletZ = 0;
   VT_TrHi_DoubletPhi = 0;
   VT_TrHi_GasGap = 0;
   VT_TrHi_MeasuresPhi = 0;
   VT_TrHi_Strip = 0;
   VT_TrHi_IsStrip = 0;
   VT_TrHi_Channel = 0;
   VT_TrHi_ChamberLayer = 0;
   VT_TrHi_WireLayer = 0;
   VT_TrHi_RpcTime = 0;
   KE_Va = 0;
   KE_Thept = 0;
   KE_Phipt = 0;
   KE_Thevc = 0;
   KE_Phivc = 0;
   KE_PInv = 0;
   KE_Cov11 = 0;
   KE_Cov21 = 0;
   KE_Cov22 = 0;
   KE_Cov31 = 0;
   KE_Cov32 = 0;
   KE_Cov33 = 0;
   KE_Cov41 = 0;
   KE_Cov42 = 0;
   KE_Cov43 = 0;
   KE_Cov44 = 0;
   KE_Cov51 = 0;
   KE_Cov52 = 0;
   KE_Cov53 = 0;
   KE_Cov54 = 0;
   KE_Cov55 = 0;
   KE_Xpt = 0;
   KE_Ypt = 0;
   KE_Zpt = 0;
   KE_Xvec = 0;
   KE_Yvec = 0;
   KE_Zvec = 0;
   KE_Mom = 0;
   KE_ZCyl = 0;
   KE_RCyl = 0;
   MS_Va = 0;
   MS_Thept = 0;
   MS_Phipt = 0;
   MS_Thevc = 0;
   MS_Phivc = 0;
   MS_PInv = 0;
   MS_Cov11 = 0;
   MS_Cov21 = 0;
   MS_Cov22 = 0;
   MS_Cov31 = 0;
   MS_Cov32 = 0;
   MS_Cov33 = 0;
   MS_Cov41 = 0;
   MS_Cov42 = 0;
   MS_Cov43 = 0;
   MS_Cov44 = 0;
   MS_Cov51 = 0;
   MS_Cov52 = 0;
   MS_Cov53 = 0;
   MS_Cov54 = 0;
   MS_Cov55 = 0;
   MS_Xpt = 0;
   MS_Ypt = 0;
   MS_Zpt = 0;
   MS_Xvec = 0;
   MS_Yvec = 0;
   MS_Zvec = 0;
   MS_Mom = 0;
   MS_ZCyl = 0;
   MS_RCyl = 0;
   MS_Chican = 0;
   MS_Chifit = 0;
   MS_Chiver = 0;
   MS_Chistat = 0;
   MS_Ndof = 0;
   Moore_phih = 0;
   Moore_etah = 0;
   Moore_mdth = 0;
   Moore_cscetah = 0;
   Moore_cscphih = 0;
   Moore_rpcetah = 0;
   Moore_rpcphih = 0;
   Moore_tgcetah = 0;
   Moore_tgcphih = 0;
   Moore_stati = 0;
   Moore_statr = 0;
   Moore_xvtxr = 0;
   Moore_yvtxr = 0;
   Moore_zvtxr = 0;
   Moore_a0r = 0;
   Moore_z0r = 0;
   Moore_phir = 0;
   Moore_thetar = 0;
   Moore_qpir = 0;
   Moore_etar = 0;
   Moore_chi2 = 0;
   Moore_chi2pr = 0;
   Moore_origx = 0;
   Moore_origy = 0;
   Moore_origz = 0;
   Moore_covr11 = 0;
   Moore_covr12 = 0;
   Moore_covr22 = 0;
   Moore_covr13 = 0;
   Moore_covr23 = 0;
   Moore_covr33 = 0;
   Moore_covr14 = 0;
   Moore_covr24 = 0;
   Moore_covr34 = 0;
   Moore_covr44 = 0;
   Moore_covr15 = 0;
   Moore_covr25 = 0;
   Moore_covr35 = 0;
   Moore_covr45 = 0;
   Moore_covr55 = 0;
   MooreSegments_ml = 0;
   MooreSegments_nhml1 = 0;
   MooreSegments_nhml2 = 0;
   MooreSegments_nmlyr = 0;
   MooreSegments_nhit = 0;
   MooreSegments_nhcsc = 0;
   MooreSegments_nhmdt = 0;
   MooreSegments_nhrpc = 0;
   MooreSegments_nhtgc = 0;
   MooreSegments_n_tottubes_seg = 0;
   MooreSegments_n_hittubes_seg = 0;
   MooreSegments_hittype = 0;
   MooreSegments_prdadc = 0;
   MooreSegments_prdtdc = 0;
   MooreSegments_z = 0;
   MooreSegments_rho = 0;
   MooreSegments_phi = 0;
   MooreSegments_theta = 0;
   MooreSegments_cotth = 0;
   MooreSegments_dtheta = 0;
   MooreSegments_chi2 = 0;
   MooreSegments_ndof = 0;
   MooreSegments_rInt = 0;
   MooreSegments_LocR = 0;
   MooreSegments_driftTime = 0;
   jetEtaCone4H1TowerJets = 0;
   jetPhiCone4H1TowerJets = 0;
   jetECone4H1TowerJets = 0;
   jetEtCone4H1TowerJets = 0;
   jetMCone4H1TowerJets = 0;
   jetPxCone4H1TowerJets = 0;
   jetPyCone4H1TowerJets = 0;
   jetPzCone4H1TowerJets = 0;
   jetSizeCone4H1TowerJets = 0;
   jetEmfCone4H1TowerJets = 0;
   CaloMu_trkPdgid = 0;
   CaloMu_trkMother = 0;
   CaloMu_trkEta = 0;
   CaloMu_trkPhi = 0;
   CaloMu_trkPt = 0;
   CaloMu_trkD0 = 0;
   CaloMu_trkIP = 0;
   CaloMu_trkBLayerHits = 0;
   CaloMu_trkPixelHits = 0;
   CaloMu_trkSCTHits = 0;
   CaloMu_trkTRTHits = 0;
   CaloMu_pdgid = 0;
   CaloMu_mother = 0;
   CaloMu_tag = 0;
   CaloMu_lhr = 0;
   CaloMu_etCone = 0;
   CaloMu_ptCone = 0;
   CaloMu_eta = 0;
   CaloMu_phi = 0;
   CaloMu_pt = 0;
   CaloMu_qoverp = 0;
   CaloMu_IP = 0;
   CaloMu_d0 = 0;
   CaloMu_bLayerHits = 0;
   CaloMu_pixelHits = 0;
   CaloMu_SCTHits = 0;
   CaloMu_TRTHits = 0;
   CaloMu_sample = 0;
   CaloMu_energy = 0;
   CaloMu_energyLoss = 0;
   CaloMu2_trkPdgid = 0;
   CaloMu2_trkMother = 0;
   CaloMu2_trkEta = 0;
   CaloMu2_trkPhi = 0;
   CaloMu2_trkPt = 0;
   CaloMu2_trkD0 = 0;
   CaloMu2_trkIP = 0;
   CaloMu2_trkBLayerHits = 0;
   CaloMu2_trkPixelHits = 0;
   CaloMu2_trkSCTHits = 0;
   CaloMu2_trkTRTHits = 0;
   CaloMu2_pdgid = 0;
   CaloMu2_mother = 0;
   CaloMu2_tag = 0;
   CaloMu2_lhr = 0;
   CaloMu2_etCone = 0;
   CaloMu2_ptCone = 0;
   CaloMu2_eta = 0;
   CaloMu2_phi = 0;
   CaloMu2_pt = 0;
   CaloMu2_qoverp = 0;
   CaloMu2_IP = 0;
   CaloMu2_d0 = 0;
   CaloMu2_bLayerHits = 0;
   CaloMu2_pixelHits = 0;
   CaloMu2_SCTHits = 0;
   CaloMu2_TRTHits = 0;
   CaloMu2_sample = 0;
   CaloMu2_energy = 0;
   CaloMu2_energyLoss = 0;
   trk_nPixelHitsComb = 0;
   trk_nSctHitsComb = 0;
   trk_nTrtHitsComb = 0;
   trk_PixResPhiComb = 0;
   trk_PixResEtaComb = 0;
   trk_PixPullPhiComb = 0;
   trk_PixPullEtaComb = 0;
   trk_PixErrTrkPhiComb = 0;
   trk_PixErrTrkEtaComb = 0;
   trk_PixErrHitPhiComb = 0;
   trk_PixErrHitEtaComb = 0;
   trk_Pix_becComb = 0;
   trk_Pix_layerComb = 0;
   trk_Pix_etaComb = 0;
   trk_Pix_phiComb = 0;
   trk_Pix_clusWidthRowComb = 0;
   trk_Pix_clusWidthColComb = 0;
   trk_Pix_LocXComb = 0;
   trk_Pix_LocYComb = 0;
   trk_SctResComb = 0;
   trk_SctPullComb = 0;
   trk_SctErrTrkComb = 0;
   trk_SctErrHitComb = 0;
   trk_Sct_becComb = 0;
   trk_Sct_layerComb = 0;
   trk_Sct_etaComb = 0;
   trk_Sct_phiComb = 0;
   trk_Sct_sideComb = 0;
   trk_Sct_rdoIdComb = 0;
   trk_Sct_clusGroupsizeComb = 0;
   trk_Sct_clusxComb = 0;
   trk_Sct_clusyComb = 0;
   trk_Sct_cluszComb = 0;
   trk_TrtResComb = 0;
   trk_TrtPullComb = 0;
   trk_TrtErrTrkComb = 0;
   trk_TrtErrHitComb = 0;
   trk_Trt_RComb = 0;
   trk_Trt_RtrackComb = 0;
   trk_Trt_tComb = 0;
   trk_Trt_xComb = 0;
   trk_Trt_yComb = 0;
   trk_Trt_HLComb = 0;
   trk_Trt_strawlayerComb = 0;
   trk_Trt_becComb = 0;
   trk_Trt_layerComb = 0;
   trk_Trt_strawComb = 0;
   trk_Trt_phisectorComb = 0;
   trk_Rec_d0Comb = 0;
   trk_Rec_z0Comb = 0;
   trk_Rec_phi0Comb = 0;
   trk_Rec_theta0Comb = 0;
   trk_Rec_qoverpComb = 0;
   trk_Rec_chi2Comb = 0;
   trk_Rec_ndofComb = 0;
   trk_Rec_etaComb = 0;
   trk_Rec_error_d0Comb = 0;
   trk_Rec_error_z0Comb = 0;
   trk_Rec_error_phi0Comb = 0;
   trk_Rec_error_theta0Comb = 0;
   trk_Rec_error_qoverpComb = 0;
   trk_Rec_chi2probComb = 0;
   trk_Rec_authorComb = 0;
   trk_nPixelHitsMuon = 0;
   trk_nSctHitsMuon = 0;
   trk_nTrtHitsMuon = 0;
   trk_Rec_d0Muon = 0;
   trk_Rec_z0Muon = 0;
   trk_Rec_phi0Muon = 0;
   trk_Rec_theta0Muon = 0;
   trk_Rec_qoverpMuon = 0;
   trk_Rec_chi2Muon = 0;
   trk_Rec_ndofMuon = 0;
   trk_Rec_etaMuon = 0;
   trk_Rec_error_d0Muon = 0;
   trk_Rec_error_z0Muon = 0;
   trk_Rec_error_phi0Muon = 0;
   trk_Rec_error_theta0Muon = 0;
   trk_Rec_error_qoverpMuon = 0;
   trk_Rec_chi2probMuon = 0;
   trk_Rec_authorMuon = 0;
   MuTagIMO_trk_isTagged = 0;
   MuTagIMO_trk_matchesBarCode = 0;
   MuTagIMO_trk_matchesPdg = 0;
   MuTagIMO_trk_nrPixelHits = 0;
   MuTagIMO_trk_nrSctHits = 0;
   MuTagIMO_trk_A0 = 0;
   MuTagIMO_trk_Z0 = 0;
   MuTagIMO_trk_phi = 0;
   MuTagIMO_trk_theta = 0;
   MuTagIMO_trk_qOverP = 0;
   MuTagIMO_trk_chi2 = 0;
   MuTagIMO_trk_ndof = 0;
   MuTagIMO_trk_Author = 0;
   MuTagIMO_trk_cov11 = 0;
   MuTagIMO_trk_cov12 = 0;
   MuTagIMO_trk_cov13 = 0;
   MuTagIMO_trk_cov14 = 0;
   MuTagIMO_trk_cov15 = 0;
   MuTagIMO_trk_cov22 = 0;
   MuTagIMO_trk_cov23 = 0;
   MuTagIMO_trk_cov24 = 0;
   MuTagIMO_trk_cov25 = 0;
   MuTagIMO_trk_cov33 = 0;
   MuTagIMO_trk_cov34 = 0;
   MuTagIMO_trk_cov35 = 0;
   MuTagIMO_trk_cov44 = 0;
   MuTagIMO_trk_cov45 = 0;
   MuTagIMO_trk_cov55 = 0;
   MuTagIMO_exTrk_trackIndex = 0;
   MuTagIMO_exTrk_A0 = 0;
   MuTagIMO_exTrk_Z0 = 0;
   MuTagIMO_exTrk_phi = 0;
   MuTagIMO_exTrk_theta = 0;
   MuTagIMO_exTrk_qOverP = 0;
   MuTagIMO_exTrk_cov11 = 0;
   MuTagIMO_exTrk_cov12 = 0;
   MuTagIMO_exTrk_cov13 = 0;
   MuTagIMO_exTrk_cov14 = 0;
   MuTagIMO_exTrk_cov15 = 0;
   MuTagIMO_exTrk_cov22 = 0;
   MuTagIMO_exTrk_cov23 = 0;
   MuTagIMO_exTrk_cov24 = 0;
   MuTagIMO_exTrk_cov25 = 0;
   MuTagIMO_exTrk_cov33 = 0;
   MuTagIMO_exTrk_cov34 = 0;
   MuTagIMO_exTrk_cov35 = 0;
   MuTagIMO_exTrk_cov44 = 0;
   MuTagIMO_exTrk_cov45 = 0;
   MuTagIMO_exTrk_cov55 = 0;
   MuTagIMO_exTrk_Eloss = 0;
   MuTagIMO_exTrk_gPosX = 0;
   MuTagIMO_exTrk_gPosY = 0;
   MuTagIMO_exTrk_gPosZ = 0;
   MuTagIMO_exTrk_gDirX = 0;
   MuTagIMO_exTrk_gDirY = 0;
   MuTagIMO_exTrk_gDirZ = 0;
   MuTagIMO_exTrk_locX = 0;
   MuTagIMO_exTrk_locY = 0;
   MuTagIMO_exTrk_angleXZ = 0;
   MuTagIMO_exTrk_angleYZ = 0;
   MuTagIMO_exTrk_locX_error = 0;
   MuTagIMO_exTrk_locY_error = 0;
   MuTagIMO_exTrk_angleXZ_error = 0;
   MuTagIMO_exTrk_angleYZ_error = 0;
   MuTagIMO_seg_isTagSeg = 0;
   MuTagIMO_seg_matchesBarCode = 0;
   MuTagIMO_seg_matchesPdg = 0;
   MuTagIMO_seg_exTrkIndex = 0;
   MuTagIMO_seg_trackIndex = 0;
   MuTagIMO_seg_stationLevel = 0;
   MuTagIMO_seg_isEndCap = 0;
   MuTagIMO_seg_isLarge = 0;
   MuTagIMO_seg_nrHoles = 0;
   MuTagIMO_seg_nrMLs = 0;
   MuTagIMO_seg_nrMdtHits = 0;
   MuTagIMO_seg_nrRpcHits = 0;
   MuTagIMO_seg_nrTgcHits = 0;
   MuTagIMO_seg_nrCscHits = 0;
   MuTagIMO_seg_phi = 0;
   MuTagIMO_seg_theta = 0;
   MuTagIMO_seg_chi2 = 0;
   MuTagIMO_seg_cov11 = 0;
   MuTagIMO_seg_cov12 = 0;
   MuTagIMO_seg_cov13 = 0;
   MuTagIMO_seg_cov14 = 0;
   MuTagIMO_seg_cov15 = 0;
   MuTagIMO_seg_cov22 = 0;
   MuTagIMO_seg_cov23 = 0;
   MuTagIMO_seg_cov24 = 0;
   MuTagIMO_seg_cov25 = 0;
   MuTagIMO_seg_cov33 = 0;
   MuTagIMO_seg_cov34 = 0;
   MuTagIMO_seg_cov35 = 0;
   MuTagIMO_seg_cov44 = 0;
   MuTagIMO_seg_cov45 = 0;
   MuTagIMO_seg_cov55 = 0;
   MuTagIMO_seg_gPosX = 0;
   MuTagIMO_seg_gPosY = 0;
   MuTagIMO_seg_gPosZ = 0;
   MuTagIMO_seg_gDirX = 0;
   MuTagIMO_seg_gDirY = 0;
   MuTagIMO_seg_gDirZ = 0;
   MuTagIMO_seg_locX = 0;
   MuTagIMO_seg_locY = 0;
   MuTagIMO_seg_angleXZ = 0;
   MuTagIMO_seg_angleYZ = 0;
   MuTagIMO_seg_locX_error = 0;
   MuTagIMO_seg_locY_error = 0;
   MuTagIMO_seg_angleXZ_error = 0;
   MuTagIMO_seg_angleYZ_error = 0;
   MuTagIMO_match_trackIndex = 0;
   MuTagIMO_match_locX = 0;
   MuTagIMO_match_locY = 0;
   MuTagIMO_match_angleXZ = 0;
   MuTagIMO_match_angleYZ = 0;
   L1Em_RoIWord = 0;
   L1Em_Core = 0;
   L1Em_EmClus = 0;
   L1Em_TauClus = 0;
   L1Em_EmIsol = 0;
   L1Em_HdIsol = 0;
   L1Em_HdCore = 0;
   L1Em_EmTauThresh = 0;
   L1Em_eta = 0;
   L1Em_phi = 0;
   L1Jet_JetRoIWord = 0;
   L1Jet_ET4x4 = 0;
   L1Jet_ET6x6 = 0;
   L1Jet_ET8x8 = 0;
   L1Jet_Thresh = 0;
   L1Jet_eta = 0;
   L1Jet_phi = 0;
   CTP_ROI = 0;
   muCTPI_ROI = 0;
   EMTau_ROI = 0;
   JetEnergy_ROI = 0;
   muctpi_bcid = 0;
   muctpi_PtMultiplicity = 0;
   muctpi_cand_sectorOverflow = 0;
   muctpi_cand_RoiOverflow = 0;
   muctpi_cand_RoiNumber = 0;
   muctpi_cand_overlapBits = 0;
   muctpi_cand_sectorID = 0;
   muctpi_cand_sectorLocation = 0;
   muctpi_cand_hemisphere = 0;
   muctpi_cand_Pt = 0;
   muctpi_cand_bcid = 0;
   muctpi_cand_isHighestPt = 0;
   muctpi_cand_sentRoI = 0;
   muctpi_roi_SUM = 0;
   muctpi_roi_BCID = 0;
   muctpi_roi_First = 0;
   muctpi_roi_Acc = 0;
   muctpi_roi_O_ROI = 0;
   muctpi_roi_O_STR = 0;
   muctpi_roi_pT = 0;
   muctpi_roi_eta = 0;
   muctpi_roi_phi = 0;
   muctpi_rodheader_statusWords = 0;
   etaCand = 0;
   phiCand = 0;
   itemName = 0;
   itemTBP = 0;
   itemTAP = 0;
   itemTAV = 0;
   thresholdName = 0;
   thresholdMulti = 0;
   ctp_bcid = 0;
   ctp_randomTrig = 0;
   ctp_prescaledClock = 0;
   ctp_bcIndexPIT = 0;
   ctp_pit = 0;
   ctp_bcIndexTriggerItems = 0;
   ctp_tbp = 0;
   ctp_tap = 0;
   ctp_tav = 0;
   ctp_rodheader_statusWords = 0;
#endif

   L1CaloPPM_eta = 0;
   L1CaloPPM_phi = 0;
   L1CaloPPM_emCrate = 0;
   L1CaloPPM_emModule = 0;
   L1CaloPPM_emSubmodule = 0;
   L1CaloPPM_emChannel = 0;
   L1CaloPPM_hadCrate = 0;
   L1CaloPPM_hadModule = 0;
   L1CaloPPM_hadSubmodule = 0;
   L1CaloPPM_hadChannel = 0;
   L1CaloPPM_emChannelId = 0;
   L1CaloPPM_hadChannelId = 0;
   L1CaloPPM_emTTCellsEnergy = 0;
   L1CaloPPM_hadTTCellsEnergy = 0;
   L1CaloPPM_emCaloWaves = 0;
   L1CaloPPM_hadCaloWaves = 0;
   L1CaloPPM_emPeak = 0;
   L1CaloPPM_emADCPeak = 0;
   L1CaloPPM_hadPeak = 0;
   L1CaloPPM_hadADCPeak = 0;
   L1CaloPPM_emLUT = 0;
   L1CaloPPM_hadLUT = 0;
   L1CaloPPM_emADC = 0;
   L1CaloPPM_hadADC = 0;
   L1CaloPPM_emEnergy = 0;
   L1CaloPPM_hadEnergy = 0;
   L1CaloPPM_emBCIDvec = 0;
   L1CaloPPM_emBCIDext = 0;
   L1CaloPPM_hadBCIDvec = 0;
   L1CaloPPM_hadBCIDext = 0;
   L1CaloPPM_emError = 0;
   L1CaloPPM_hadError = 0;
   L1CaloPPM_emBCID = 0;
   L1CaloPPM_hadBCID = 0;
   L1CaloPPM_emIsSaturated = 0;
   L1CaloPPM_hadIsSaturated = 0;
   L1CaloPPM_emIsFilled = 0;
   L1CaloPPM_hadIsFilled = 0;

#ifndef PPM_ONLY
   L1CaloCPM_RoI_crate = 0;
   L1CaloCPM_RoI_cpm = 0;
   L1CaloCPM_RoI_chip = 0;
   L1CaloCPM_RoI_location = 0;
   L1CaloCPM_RoI_hits = 0;
   L1CaloCPM_RoI_eta = 0;
   L1CaloCPM_RoI_phi = 0;
   L1CaloCPM_RoI_core = 0;
   L1CaloCPM_RoI_emClus = 0;
   L1CaloCPM_RoI_tauClus = 0;
   L1CaloCPM_RoI_emIsol = 0;
   L1CaloCPM_RoI_hadIsol = 0;
   L1CaloCPM_RoI_hadVeto = 0;
   L1CaloCPM_RoI_isEtMax = 0;
   L1CaloCPM_RoI_simHits = 0;
   L1CaloCPM_RoI_error = 0;
   L1CaloCPM_SimRoI_eta = 0;
   L1CaloCPM_SimRoI_phi = 0;
   L1CaloCPM_SimRoI_core = 0;
   L1CaloCPM_SimRoI_emClus = 0;
   L1CaloCPM_SimRoI_tauClus = 0;
   L1CaloCPM_SimRoI_emIsol = 0;
   L1CaloCPM_SimRoI_hadIsol = 0;
   L1CaloCPM_SimRoI_hadVeto = 0;
   L1CaloCPM_SimRoI_isEtMax = 0;
   L1CaloCPM_SimRoI_hits = 0;
   L1CaloCPM_SimRoI_roiWord = 0;
   L1CaloCPM_Hits_crate = 0;
   L1CaloCPM_Hits_module = 0;
   L1CaloCPM_Hits_peak = 0;
   L1CaloCPM_Hits_hitWord0 = 0;
   L1CaloCPM_Hits_hitWord1 = 0;
   L1CaloCPM_Hits_hitsVec0 = 0;
   L1CaloCPM_Hits_hitsVec1 = 0;
   L1CaloCPM_Towers_eta = 0;
   L1CaloCPM_Towers_phi = 0;
   L1CaloCPM_Towers_peak = 0;
   L1CaloCPM_Towers_emEnergy = 0;
   L1CaloCPM_Towers_hadEnergy = 0;
   L1CaloCPM_Towers_emEnergyVec = 0;
   L1CaloCPM_Towers_hadEnergyVec = 0;
   L1CaloCPM_Towers_emError = 0;
   L1CaloCPM_Towers_hadError = 0;
   L1CaloCPM_Towers_emErrorVec = 0;
   L1CaloCPM_Towers_hadErrorVec = 0;
   L1CaloCPM_CMM_crate = 0;
   L1CaloCPM_CMM_dataID = 0;
   L1CaloCPM_CMM_hitWord0 = 0;
   L1CaloCPM_CMM_hitWord1 = 0;
   L1CaloCPM_CMM_error0 = 0;
   L1CaloCPM_CMM_error1 = 0;
   L1CaloCPM_CMM_peak = 0;
   L1CaloCPM_CMM_hitsVec0 = 0;
   L1CaloCPM_CMM_hitsVec1 = 0;
   L1CaloCPM_CMM_errorVec0 = 0;
   L1CaloCPM_CMM_errorVec1 = 0;
   L1CaloJEM_JetEl_eta = 0;
   L1CaloJEM_JetEl_phi = 0;
   L1CaloJEM_JetEl_emEnergy = 0;
   L1CaloJEM_JetEl_hadEnergy = 0;
   L1CaloJEM_JetEl_energy = 0;
   L1CaloJEM_JetEl_isSaturated = 0;
   L1CaloJEM_JetEl_isEmSaturated = 0;
   L1CaloJEM_JetEl_isHadSaturated = 0;
   L1CaloJEM_JetEl_emError = 0;
   L1CaloJEM_JetEl_hadError = 0;
   L1CaloJEM_JetEl_linkError = 0;
   L1CaloJEM_JetEl_peak = 0;
   L1CaloJEM_JetEl_emEnergyVec = 0;
   L1CaloJEM_JetEl_hadEnergyVec = 0;
   L1CaloJEM_JetEl_emErrorVec = 0;
   L1CaloJEM_JetEl_hadErrorVec = 0;
   L1CaloJEM_JetEl_linkErrorVec = 0;
   L1CaloJEM_Hits_crate = 0;
   L1CaloJEM_Hits_module = 0;
   L1CaloJEM_Hits_jetHits = 0;
   L1CaloJEM_Hits_jetHitsVec = 0;
   L1CaloJEM_Hits_peak = 0;
   L1CaloJEM_Hits_forward = 0;
   L1CaloJEM_EtSums_crate = 0;
   L1CaloJEM_EtSums_module = 0;
   L1CaloJEM_EtSums_et = 0;
   L1CaloJEM_EtSums_ex = 0;
   L1CaloJEM_EtSums_ey = 0;
   L1CaloJEM_EtSums_etVec = 0;
   L1CaloJEM_EtSums_exVec = 0;
   L1CaloJEM_EtSums_eyVec = 0;
   L1CaloJEM_EtSums_peak = 0;
   L1CaloJEM_EtSums_forward = 0;
   L1CaloJEM_CMMJetHits_crate = 0;
   L1CaloJEM_CMMJetHits_dataID = 0;
   L1CaloJEM_CMMJetHits_hits = 0;
   L1CaloJEM_CMMJetHits_error = 0;
   L1CaloJEM_CMMJetHits_hitsVec = 0;
   L1CaloJEM_CMMJetHits_errorVec = 0;
   L1CaloJEM_CMMJetHits_peak = 0;
   L1CaloJEM_CMMEtSums_crate = 0;
   L1CaloJEM_CMMEtSums_dataID = 0;
   L1CaloJEM_CMMEtSums_et = 0;
   L1CaloJEM_CMMEtSums_ex = 0;
   L1CaloJEM_CMMEtSums_ey = 0;
   L1CaloJEM_CMMEtSums_etError = 0;
   L1CaloJEM_CMMEtSums_exError = 0;
   L1CaloJEM_CMMEtSums_eyError = 0;
   L1CaloJEM_CMMEtSums_etVec = 0;
   L1CaloJEM_CMMEtSums_exVec = 0;
   L1CaloJEM_CMMEtSums_eyVec = 0;
   L1CaloJEM_CMMEtSums_etErrorVec = 0;
   L1CaloJEM_CMMEtSums_exErrorVec = 0;
   L1CaloJEM_CMMEtSums_eyErrorVec = 0;
   L1CaloJEM_CMMEtSums_peak = 0;
   L1CaloJEM_RoI_crate = 0;
   L1CaloJEM_RoI_jem = 0;
   L1CaloJEM_RoI_frame = 0;
   L1CaloJEM_RoI_location = 0;
   L1CaloJEM_RoI_eta = 0;
   L1CaloJEM_RoI_phi = 0;
   L1CaloJEM_RoI_forward = 0;
   L1CaloJEM_RoI_hits = 0;
   L1CaloJEM_RoI_error = 0;
   L1CaloRODHeader_version = 0;
   L1CaloRODHeader_majorVersion = 0;
   L1CaloRODHeader_minorVersion = 0;
   L1CaloRODHeader_sourceID = 0;
   L1CaloRODHeader_subDetectorID = 0;
   L1CaloRODHeader_moduleID = 0;
   L1CaloRODHeader_crate = 0;
   L1CaloRODHeader_sLink = 0;
   L1CaloRODHeader_dataType = 0;
   L1CaloRODHeader_run = 0;
   L1CaloRODHeader_runType = 0;
   L1CaloRODHeader_runNumber = 0;
   L1CaloRODHeader_extendedL1ID = 0;
   L1CaloRODHeader_ecrID = 0;
   L1CaloRODHeader_l1ID = 0;
   L1CaloRODHeader_bunchCrossing = 0;
   L1CaloRODHeader_l1TriggerType = 0;
   L1CaloRODHeader_detEventType = 0;
   L1CaloRODHeader_orbitCount = 0;
   L1CaloRODHeader_stepNumber = 0;
   L1CaloRODHeader_stepType = 0;
   L1CaloRODHeader_bcnMismatch = 0;
   L1CaloRODHeader_gLinkTimeout = 0;
   L1CaloRODHeader_dataTransportError = 0;
   L1CaloRODHeader_rodFifoOverflow = 0;
   L1CaloRODHeader_lvdsLinkError = 0;
   L1CaloRODHeader_cmmParityError = 0;
   L1CaloRODHeader_gLinkError = 0;
   L1CaloRODHeader_limitedRoISet = 0;
   L1CaloRODHeader_triggerTypeTimeout = 0;
#endif

   // Set branch addresses and branch pointers
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("RunNumber", &RunNumber, &b_RunNumber);
   fChain->SetBranchAddress("EventNumber", &EventNumber, &b_EventNumber);
#ifndef L1CALO_ONLY
   fChain->SetBranchAddress("StreamESD_ref", &StreamESD_ref, &b_StreamESD_ref);
#endif
   fChain->SetBranchAddress("Token", Token, &b_Token);
   fChain->SetBranchAddress("Run", &Run, &b_Run);
   fChain->SetBranchAddress("Event", &Event, &b_Event);
   fChain->SetBranchAddress("Time", &Time, &b_Time);
   fChain->SetBranchAddress("LumiBlock", &LumiBlock, &b_LumiBlock);
   fChain->SetBranchAddress("BCID", &BCID, &b_BCID);
   fChain->SetBranchAddress("LVL1ID", &LVL1ID, &b_LVL1ID);
   fChain->SetBranchAddress("Weight", &Weight, &b_Weight);
   fChain->SetBranchAddress("IEvent", &IEvent, &b_IEvent);
   fChain->SetBranchAddress("StatusElement", &StatusElement, &b_StatusElement);
   fChain->SetBranchAddress("LVL1TriggerType", &LVL1TriggerType, &b_LVL1TriggerType);
   fChain->SetBranchAddress("LVL1TriggerInfo", &LVL1TriggerInfo, &b_LVL1TriggerInfo);
   fChain->SetBranchAddress("LVL2TriggerInfo", &LVL2TriggerInfo, &b_LVL2TriggerInfo);
   fChain->SetBranchAddress("EventFilterInfo", &EventFilterInfo, &b_EventFilterInfo);
   fChain->SetBranchAddress("StreamTagName", &StreamTagName, &b_StreamTagName);
   fChain->SetBranchAddress("StreamTagType", &StreamTagType, &b_StreamTagType);
   
#ifndef L1CALO_ONLY
   fChain->SetBranchAddress("pixel_nhits", &pixel_nhits, &b_pixel_nhits);
   fChain->SetBranchAddress("pixel_bec", &pixel_bec, &b_pixel_bec);
   fChain->SetBranchAddress("pixel_layer", &pixel_layer, &b_pixel_layer);
   fChain->SetBranchAddress("pixel_eta", &pixel_eta, &b_pixel_eta);
   fChain->SetBranchAddress("pixel_phi", &pixel_phi, &b_pixel_phi);
   fChain->SetBranchAddress("pixel_row", &pixel_row, &b_pixel_row);
   fChain->SetBranchAddress("pixel_col", &pixel_col, &b_pixel_col);
   fChain->SetBranchAddress("pixel_tot", &pixel_tot, &b_pixel_tot);
   fChain->SetBranchAddress("pixel_BCID", &pixel_BCID, &b_pixel_BCID);
   fChain->SetBranchAddress("pixel_LVL1", &pixel_LVL1, &b_pixel_LVL1);
   fChain->SetBranchAddress("sct_rdo_nhits", &sct_rdo_nhits, &b_sct_rdo_nhits);
   fChain->SetBranchAddress("sct_rdo_strips", &sct_rdo_strips, &b_sct_rdo_strips);
   fChain->SetBranchAddress("sct_rdo_tbin", &sct_rdo_tbin, &b_sct_rdo_tbin);
   fChain->SetBranchAddress("sct_rdo_rdoId", &sct_rdo_rdoId, &b_sct_rdo_rdoId);
   fChain->SetBranchAddress("sct_rdo_bec", &sct_rdo_bec, &b_sct_rdo_bec);
   fChain->SetBranchAddress("sct_rdo_layer", &sct_rdo_layer, &b_sct_rdo_layer);
   fChain->SetBranchAddress("sct_rdo_eta", &sct_rdo_eta, &b_sct_rdo_eta);
   fChain->SetBranchAddress("sct_rdo_phi", &sct_rdo_phi, &b_sct_rdo_phi);
   fChain->SetBranchAddress("sct_rdo_side", &sct_rdo_side, &b_sct_rdo_side);
   fChain->SetBranchAddress("sct_rdo_FirstSecondHitError", &sct_rdo_FirstSecondHitError, &b_sct_rdo_FirstSecondHitError);
   fChain->SetBranchAddress("tdc_ntdcs", &tdc_ntdcs, &b_tdc_ntdcs);
   fChain->SetBranchAddress("tdc_channel", &tdc_channel, &b_tdc_channel);
   fChain->SetBranchAddress("tdc_phase", &tdc_phase, &b_tdc_phase);
   fChain->SetBranchAddress("sct_bsErr_nErrs", &sct_bsErr_nErrs, &b_sct_bsErr_nErrs);
   fChain->SetBranchAddress("sct_bsErr_type", &sct_bsErr_type, &b_sct_bsErr_type);
   fChain->SetBranchAddress("sct_bsErr_eta", &sct_bsErr_eta, &b_sct_bsErr_eta);
   fChain->SetBranchAddress("sct_bsErr_phi", &sct_bsErr_phi, &b_sct_bsErr_phi);
   fChain->SetBranchAddress("sct_bsErr_layer", &sct_bsErr_layer, &b_sct_bsErr_layer);
   fChain->SetBranchAddress("sct_bsErr_side", &sct_bsErr_side, &b_sct_bsErr_side);
   fChain->SetBranchAddress("sct_bsErr_bec", &sct_bsErr_bec, &b_sct_bsErr_bec);
   fChain->SetBranchAddress("sct_clus_nclusters", &sct_clus_nclusters, &b_sct_clus_nclusters);
   fChain->SetBranchAddress("sct_clus_x", &sct_clus_x, &b_sct_clus_x);
   fChain->SetBranchAddress("sct_clus_y", &sct_clus_y, &b_sct_clus_y);
   fChain->SetBranchAddress("sct_clus_z", &sct_clus_z, &b_sct_clus_z);
   fChain->SetBranchAddress("sct_clus_groupsize", &sct_clus_groupsize, &b_sct_clus_groupsize);
   fChain->SetBranchAddress("sct_clus_bec", &sct_clus_bec, &b_sct_clus_bec);
   fChain->SetBranchAddress("sct_clus_layer", &sct_clus_layer, &b_sct_clus_layer);
   fChain->SetBranchAddress("sct_clus_eta", &sct_clus_eta, &b_sct_clus_eta);
   fChain->SetBranchAddress("sct_clus_phi", &sct_clus_phi, &b_sct_clus_phi);
   fChain->SetBranchAddress("sct_clus_side", &sct_clus_side, &b_sct_clus_side);
   fChain->SetBranchAddress("pixel_clus_nclusters", &pixel_clus_nclusters, &b_pixel_clus_nclusters);
   fChain->SetBranchAddress("pixel_clus_LocX", &pixel_clus_LocX, &b_pixel_clus_LocX);
   fChain->SetBranchAddress("pixel_clus_LocY", &pixel_clus_LocY, &b_pixel_clus_LocY);
   fChain->SetBranchAddress("pixel_clus_z", &pixel_clus_z, &b_pixel_clus_z);
   fChain->SetBranchAddress("pixel_clus_groupsize", &pixel_clus_groupsize, &b_pixel_clus_groupsize);
   fChain->SetBranchAddress("pixel_clus_bec", &pixel_clus_bec, &b_pixel_clus_bec);
   fChain->SetBranchAddress("pixel_clus_layer", &pixel_clus_layer, &b_pixel_clus_layer);
   fChain->SetBranchAddress("pixel_clus_phi", &pixel_clus_phi, &b_pixel_clus_phi);
   fChain->SetBranchAddress("pixel_clus_clx", &pixel_clus_clx, &b_pixel_clus_clx);
   fChain->SetBranchAddress("pixel_clus_cly", &pixel_clus_cly, &b_pixel_clus_cly);
   fChain->SetBranchAddress("pixel_clus_clz", &pixel_clus_clz, &b_pixel_clus_clz);
   fChain->SetBranchAddress("pixel_clus_row", &pixel_clus_row, &b_pixel_clus_row);
   fChain->SetBranchAddress("pixel_clus_col", &pixel_clus_col, &b_pixel_clus_col);
   fChain->SetBranchAddress("sct_sp_nspacepoints", &sct_sp_nspacepoints, &b_sct_sp_nspacepoints);
   fChain->SetBranchAddress("sct_sp_x", &sct_sp_x, &b_sct_sp_x);
   fChain->SetBranchAddress("sct_sp_y", &sct_sp_y, &b_sct_sp_y);
   fChain->SetBranchAddress("sct_sp_z", &sct_sp_z, &b_sct_sp_z);
   fChain->SetBranchAddress("sct_sp_barrelendcap", &sct_sp_barrelendcap, &b_sct_sp_barrelendcap);
   fChain->SetBranchAddress("sct_sp_layer", &sct_sp_layer, &b_sct_sp_layer);
   fChain->SetBranchAddress("sct_sp_phi", &sct_sp_phi, &b_sct_sp_phi);
   fChain->SetBranchAddress("sct_sp_eta", &sct_sp_eta, &b_sct_sp_eta);
   fChain->SetBranchAddress("pixel_sp_nspacepoints", &pixel_sp_nspacepoints, &b_pixel_sp_nspacepoints);
   fChain->SetBranchAddress("pixel_sp_x", &pixel_sp_x, &b_pixel_sp_x);
   fChain->SetBranchAddress("pixel_sp_y", &pixel_sp_y, &b_pixel_sp_y);
   fChain->SetBranchAddress("pixel_sp_z", &pixel_sp_z, &b_pixel_sp_z);
   fChain->SetBranchAddress("pixel_sp_barrelendcap", &pixel_sp_barrelendcap, &b_pixel_sp_barrelendcap);
   fChain->SetBranchAddress("pixel_sp_layer", &pixel_sp_layer, &b_pixel_sp_layer);
   fChain->SetBranchAddress("pixel_sp_phi", &pixel_sp_phi, &b_pixel_sp_phi);
   fChain->SetBranchAddress("pixel_sp_eta", &pixel_sp_eta, &b_pixel_sp_eta);
   fChain->SetBranchAddress("trk_nTracks", &trk_nTracks, &b_trk_nTracks);
   fChain->SetBranchAddress("trk_nPixelHits", &trk_nPixelHits, &b_trk_nPixelHits);
   fChain->SetBranchAddress("trk_nSctHits", &trk_nSctHits, &b_trk_nSctHits);
   fChain->SetBranchAddress("trk_nTrtHits", &trk_nTrtHits, &b_trk_nTrtHits);
   fChain->SetBranchAddress("trk_PixResPhi", &trk_PixResPhi, &b_trk_PixResPhi);
   fChain->SetBranchAddress("trk_PixResEta", &trk_PixResEta, &b_trk_PixResEta);
   fChain->SetBranchAddress("trk_PixPullPhi", &trk_PixPullPhi, &b_trk_PixPullPhi);
   fChain->SetBranchAddress("trk_PixPullEta", &trk_PixPullEta, &b_trk_PixPullEta);
   fChain->SetBranchAddress("trk_PixErrTrkPhi", &trk_PixErrTrkPhi, &b_trk_PixErrTrkPhi);
   fChain->SetBranchAddress("trk_PixErrTrkEta", &trk_PixErrTrkEta, &b_trk_PixErrTrkEta);
   fChain->SetBranchAddress("trk_PixErrHitPhi", &trk_PixErrHitPhi, &b_trk_PixErrHitPhi);
   fChain->SetBranchAddress("trk_PixErrHitEta", &trk_PixErrHitEta, &b_trk_PixErrHitEta);
   fChain->SetBranchAddress("trk_Pix_bec", &trk_Pix_bec, &b_trk_Pix_bec);
   fChain->SetBranchAddress("trk_Pix_layer", &trk_Pix_layer, &b_trk_Pix_layer);
   fChain->SetBranchAddress("trk_Pix_eta", &trk_Pix_eta, &b_trk_Pix_eta);
   fChain->SetBranchAddress("trk_Pix_phi", &trk_Pix_phi, &b_trk_Pix_phi);
   fChain->SetBranchAddress("trk_Pix_clusWidthRow", &trk_Pix_clusWidthRow, &b_trk_Pix_clusWidthRow);
   fChain->SetBranchAddress("trk_Pix_clusWidthCol", &trk_Pix_clusWidthCol, &b_trk_Pix_clusWidthCol);
   fChain->SetBranchAddress("trk_Pix_LocX", &trk_Pix_LocX, &b_trk_Pix_LocX);
   fChain->SetBranchAddress("trk_Pix_LocY", &trk_Pix_LocY, &b_trk_Pix_LocY);
   fChain->SetBranchAddress("trk_SctRes", &trk_SctRes, &b_trk_SctRes);
   fChain->SetBranchAddress("trk_SctPull", &trk_SctPull, &b_trk_SctPull);
   fChain->SetBranchAddress("trk_SctErrTrk", &trk_SctErrTrk, &b_trk_SctErrTrk);
   fChain->SetBranchAddress("trk_SctErrHit", &trk_SctErrHit, &b_trk_SctErrHit);
   fChain->SetBranchAddress("trk_Sct_bec", &trk_Sct_bec, &b_trk_Sct_bec);
   fChain->SetBranchAddress("trk_Sct_layer", &trk_Sct_layer, &b_trk_Sct_layer);
   fChain->SetBranchAddress("trk_Sct_eta", &trk_Sct_eta, &b_trk_Sct_eta);
   fChain->SetBranchAddress("trk_Sct_phi", &trk_Sct_phi, &b_trk_Sct_phi);
   fChain->SetBranchAddress("trk_Sct_side", &trk_Sct_side, &b_trk_Sct_side);
   fChain->SetBranchAddress("trk_Sct_rdoId", &trk_Sct_rdoId, &b_trk_Sct_rdoId);
   fChain->SetBranchAddress("trk_Sct_clusGroupsize", &trk_Sct_clusGroupsize, &b_trk_Sct_clusGroupsize);
   fChain->SetBranchAddress("trk_Sct_clusx", &trk_Sct_clusx, &b_trk_Sct_clusx);
   fChain->SetBranchAddress("trk_Sct_clusy", &trk_Sct_clusy, &b_trk_Sct_clusy);
   fChain->SetBranchAddress("trk_Sct_clusz", &trk_Sct_clusz, &b_trk_Sct_clusz);
   fChain->SetBranchAddress("trk_TrtRes", &trk_TrtRes, &b_trk_TrtRes);
   fChain->SetBranchAddress("trk_TrtPull", &trk_TrtPull, &b_trk_TrtPull);
   fChain->SetBranchAddress("trk_TrtErrTrk", &trk_TrtErrTrk, &b_trk_TrtErrTrk);
   fChain->SetBranchAddress("trk_TrtErrHit", &trk_TrtErrHit, &b_trk_TrtErrHit);
   fChain->SetBranchAddress("trk_Trt_R", &trk_Trt_R, &b_trk_Trt_R);
   fChain->SetBranchAddress("trk_Trt_Rtrack", &trk_Trt_Rtrack, &b_trk_Trt_Rtrack);
   fChain->SetBranchAddress("trk_Trt_t", &trk_Trt_t, &b_trk_Trt_t);
   fChain->SetBranchAddress("trk_Trt_x", &trk_Trt_x, &b_trk_Trt_x);
   fChain->SetBranchAddress("trk_Trt_y", &trk_Trt_y, &b_trk_Trt_y);
   fChain->SetBranchAddress("trk_Trt_HL", &trk_Trt_HL, &b_trk_Trt_HL);
   fChain->SetBranchAddress("trk_Trt_strawlayer", &trk_Trt_strawlayer, &b_trk_Trt_strawlayer);
   fChain->SetBranchAddress("trk_Trt_bec", &trk_Trt_bec, &b_trk_Trt_bec);
   fChain->SetBranchAddress("trk_Trt_layer", &trk_Trt_layer, &b_trk_Trt_layer);
   fChain->SetBranchAddress("trk_Trt_straw", &trk_Trt_straw, &b_trk_Trt_straw);
   fChain->SetBranchAddress("trk_Trt_phisector", &trk_Trt_phisector, &b_trk_Trt_phisector);
   fChain->SetBranchAddress("trk_Rec_d0", &trk_Rec_d0, &b_trk_Rec_d0);
   fChain->SetBranchAddress("trk_Rec_z0", &trk_Rec_z0, &b_trk_Rec_z0);
   fChain->SetBranchAddress("trk_Rec_phi0", &trk_Rec_phi0, &b_trk_Rec_phi0);
   fChain->SetBranchAddress("trk_Rec_theta0", &trk_Rec_theta0, &b_trk_Rec_theta0);
   fChain->SetBranchAddress("trk_Rec_qoverp", &trk_Rec_qoverp, &b_trk_Rec_qoverp);
   fChain->SetBranchAddress("trk_Rec_chi2", &trk_Rec_chi2, &b_trk_Rec_chi2);
   fChain->SetBranchAddress("trk_Rec_ndof", &trk_Rec_ndof, &b_trk_Rec_ndof);
   fChain->SetBranchAddress("trk_Rec_eta", &trk_Rec_eta, &b_trk_Rec_eta);
   fChain->SetBranchAddress("trk_Rec_error_d0", &trk_Rec_error_d0, &b_trk_Rec_error_d0);
   fChain->SetBranchAddress("trk_Rec_error_z0", &trk_Rec_error_z0, &b_trk_Rec_error_z0);
   fChain->SetBranchAddress("trk_Rec_error_phi0", &trk_Rec_error_phi0, &b_trk_Rec_error_phi0);
   fChain->SetBranchAddress("trk_Rec_error_theta0", &trk_Rec_error_theta0, &b_trk_Rec_error_theta0);
   fChain->SetBranchAddress("trk_Rec_error_qoverp", &trk_Rec_error_qoverp, &b_trk_Rec_error_qoverp);
   fChain->SetBranchAddress("trk_Rec_chi2prob", &trk_Rec_chi2prob, &b_trk_Rec_chi2prob);
   fChain->SetBranchAddress("trk_Rec_author", &trk_Rec_author, &b_trk_Rec_author);
   fChain->SetBranchAddress("Nh_Calo", &Nh_Calo, &b_Nh_Calo);
   fChain->SetBranchAddress("Eh_Calo", &Eh_Calo, &b_Eh_Calo);
   fChain->SetBranchAddress("Nh_EM", &Nh_EM, &b_Nh_EM);
   fChain->SetBranchAddress("Eh_EM", &Eh_EM, &b_Eh_EM);
   fChain->SetBranchAddress("Nh_HAD", &Nh_HAD, &b_Nh_HAD);
   fChain->SetBranchAddress("Eh_HAD", &Eh_HAD, &b_Eh_HAD);
   fChain->SetBranchAddress("Nh_PresB", &Nh_PresB, &b_Nh_PresB);
   fChain->SetBranchAddress("Eh_PresB", &Eh_PresB, &b_Eh_PresB);
   fChain->SetBranchAddress("Nh_EMB", &Nh_EMB, &b_Nh_EMB);
   fChain->SetBranchAddress("Eh_EMB", &Eh_EMB, &b_Eh_EMB);
   fChain->SetBranchAddress("Nh_EMEC", &Nh_EMEC, &b_Nh_EMEC);
   fChain->SetBranchAddress("Eh_EMEC", &Eh_EMEC, &b_Eh_EMEC);
   fChain->SetBranchAddress("Nh_Tile", &Nh_Tile, &b_Nh_Tile);
   fChain->SetBranchAddress("Eh_Tile", &Eh_Tile, &b_Eh_Tile);
   fChain->SetBranchAddress("Nh_TileGap", &Nh_TileGap, &b_Nh_TileGap);
   fChain->SetBranchAddress("Eh_TileGap", &Eh_TileGap, &b_Eh_TileGap);
   fChain->SetBranchAddress("Nh_HEC", &Nh_HEC, &b_Nh_HEC);
   fChain->SetBranchAddress("Eh_HEC", &Eh_HEC, &b_Eh_HEC);
   fChain->SetBranchAddress("Nh_FCal", &Nh_FCal, &b_Nh_FCal);
   fChain->SetBranchAddress("Eh_FCal", &Eh_FCal, &b_Eh_FCal);
   fChain->SetBranchAddress("Nh_PresE", &Nh_PresE, &b_Nh_PresE);
   fChain->SetBranchAddress("Eh_PresE", &Eh_PresE, &b_Eh_PresE);
   fChain->SetBranchAddress("Nh_Scint", &Nh_Scint, &b_Nh_Scint);
   fChain->SetBranchAddress("Eh_Scint", &Eh_Scint, &b_Eh_Scint);
   fChain->SetBranchAddress("nhitLAr", &nhitLAr, &b_nhitLAr);
   fChain->SetBranchAddress("ecellLAr", &ecellLAr, &b_ecellLAr);
   fChain->SetBranchAddress("NCellsLAr", &NCellsLAr, &b_NCellsLAr);
   fChain->SetBranchAddress("ECellsLAr", &ECellsLAr, &b_ECellsLAr);
   fChain->SetBranchAddress("EtaCellsLAr", &EtaCellsLAr, &b_EtaCellsLAr);
   fChain->SetBranchAddress("PhiCellsLAr", &PhiCellsLAr, &b_PhiCellsLAr);
   fChain->SetBranchAddress("QCellsLAr", &QCellsLAr, &b_QCellsLAr);
   fChain->SetBranchAddress("GainCellsLAr", &GainCellsLAr, &b_GainCellsLAr);
   fChain->SetBranchAddress("DetCellsLAr", &DetCellsLAr, &b_DetCellsLAr);
   fChain->SetBranchAddress("TimeCellsLAr", &TimeCellsLAr, &b_TimeCellsLAr);
   fChain->SetBranchAddress("BadCellsLAr", &BadCellsLAr, &b_BadCellsLAr);
   fChain->SetBranchAddress("IdCellsLAr", &IdCellsLAr, &b_IdCellsLAr);
   fChain->SetBranchAddress("LArDigit_icell", &LArDigit_icell, &b_icell);
   fChain->SetBranchAddress("LArDigit_layer", &LArDigit_layer, &b_LArDigit_layer);
   fChain->SetBranchAddress("LArDigit_ieta", &LArDigit_ieta, &b_LArDigit_ieta);
   fChain->SetBranchAddress("LArDigit_calo", &LArDigit_calo, &b_LArDigit_calo);
   fChain->SetBranchAddress("LArDigit_iphi", &LArDigit_iphi, &b_LArDigit_iphi);
   fChain->SetBranchAddress("LArDigit_barrel_ec", &LArDigit_barrel_ec, &b_LArDigit_barrel_ec);
   fChain->SetBranchAddress("LArDigit_pos_neg", &LArDigit_pos_neg, &b_LArDigit_pos_neg);
   fChain->SetBranchAddress("LArDigit_FT", &LArDigit_FT, &b_LArDigit_FT);
   fChain->SetBranchAddress("LArDigit_slot", &LArDigit_slot, &b_LArDigit_slot);
   fChain->SetBranchAddress("LArDigit_channel", &LArDigit_channel, &b_LArDigit_channel);
   fChain->SetBranchAddress("LArDigit_gain", &LArDigit_gain, &b_LArDigit_gain);
   fChain->SetBranchAddress("LArDigit_NSamples", &LArDigit_NSamples, &b_NSamples);
   fChain->SetBranchAddress("LArDigit_Samples", &LArDigit_Samples, &b_LArDigit_Samples);
   fChain->SetBranchAddress("LArDigit_offlineId", &LArDigit_offlineId, &b_LArDigit_offlineId);
   fChain->SetBranchAddress("TileCellETot", &TileCellETot, &b_TileCellEtot);
   fChain->SetBranchAddress("TileMBTSETot", &TileMBTSETot, &b_TileMBTSETot);
   fChain->SetBranchAddress("TileMBTSETotA", &TileMBTSETotA, &b_TileMBTSETotA);
   fChain->SetBranchAddress("TileMBTSETotC", &TileMBTSETotC, &b_TileMBTSETotC);
   fChain->SetBranchAddress("TileCellN", &TileCellN, &b_TileCellN);
   fChain->SetBranchAddress("TileCellE", &TileCellE, &b_TileCellE);
   fChain->SetBranchAddress("TileCellTime", &TileCellTime, &b_TileCellTime);
   fChain->SetBranchAddress("TileCellEta", &TileCellEta, &b_TileCellEta);
   fChain->SetBranchAddress("TileCellPhi", &TileCellPhi, &b_TileCellPhi);
   fChain->SetBranchAddress("TileMBTSCounter", &TileMBTSCounter, &b_TileMBTSCounter);
   fChain->SetBranchAddress("TileMBTSE", &TileMBTSE, &b_TileMBTSE);
   fChain->SetBranchAddress("TileMBTSTime", &TileMBTSTime, &b_TileMBTSTime);
   fChain->SetBranchAddress("TileMBTSQuality", &TileMBTSQuality, &b_TileMBTSQuality);
   fChain->SetBranchAddress("TileMBTSEta", &TileMBTSEta, &b_TileMBTSEta);
   fChain->SetBranchAddress("TileMBTSPhi", &TileMBTSPhi, &b_TileMBTSPhi);
   fChain->SetBranchAddress("TileCellX", &TileCellX, &b_TileCellX);
   fChain->SetBranchAddress("TileCellY", &TileCellY, &b_TileCellY);
   fChain->SetBranchAddress("TileCellZ", &TileCellZ, &b_TileCellZ);
   fChain->SetBranchAddress("TileMBTSX", &TileMBTSX, &b_TileMBTSX);
   fChain->SetBranchAddress("TileMBTSY", &TileMBTSY, &b_TileMBTSY);
   fChain->SetBranchAddress("TileMBTSZ", &TileMBTSZ, &b_TileMBTSZ);
   fChain->SetBranchAddress("TileCellEdiff", &TileCellEdiff, &b_TileCellEdiff);
   fChain->SetBranchAddress("TileCellTimediff", &TileCellTimediff, &b_TileCellTimediff);
   fChain->SetBranchAddress("TileCellGain1", &TileCellGain1, &b_TileCellGain1);
   fChain->SetBranchAddress("TileCellGain2", &TileCellGain2, &b_TileCellGain2);
   fChain->SetBranchAddress("TileCellModule", &TileCellModule, &b_TileCellModule);
   fChain->SetBranchAddress("TileCellPartition", &TileCellPartition, &b_TileCellPartition);
   fChain->SetBranchAddress("TileCellTower", &TileCellTower, &b_TileCellTower);
   fChain->SetBranchAddress("TileCellSample", &TileCellSample, &b_TileCellSample);
   fChain->SetBranchAddress("TileCellChan1", &TileCellChan1, &b_TileCellChan1);
   fChain->SetBranchAddress("TileCellChan2", &TileCellChan2, &b_TileCellChan2);
   fChain->SetBranchAddress("TileCellPMT1", &TileCellPMT1, &b_TileCellPMT1);
   fChain->SetBranchAddress("TileCellPMT2", &TileCellPMT2, &b_TileCellPMT2);
   fChain->SetBranchAddress("TileCellStatus1", &TileCellStatus1, &b_TileCellStatus1);
   fChain->SetBranchAddress("TileCellStatus2", &TileCellStatus2, &b_TileCellStatus2);
   fChain->SetBranchAddress("TileMBTSModule", &TileMBTSModule, &b_TileMBTSModule);
   fChain->SetBranchAddress("TileMBTSGain", &TileMBTSGain, &b_TileMBTSGain);
   fChain->SetBranchAddress("TileMBTSStatus", &TileMBTSStatus, &b_TileMBTSStatus);
   fChain->SetBranchAddress("cl_ecluster", &cl_ecluster, &b_cl_ecluster);
   fChain->SetBranchAddress("cl_nctotal", &cl_nctotal, &b_cl_nctotal);
   fChain->SetBranchAddress("cl_nc", &cl_nc, &b_cl_nc);
   fChain->SetBranchAddress("cl_et", &cl_et, &b_cl_et);
   fChain->SetBranchAddress("cl_e", &cl_e, &b_cl_e);
   fChain->SetBranchAddress("cl_eemb0", &cl_eemb0, &b_cl_eemb0);
   fChain->SetBranchAddress("cl_eemb1", &cl_eemb1, &b_cl_eemb1);
   fChain->SetBranchAddress("cl_eemb2", &cl_eemb2, &b_cl_eemb2);
   fChain->SetBranchAddress("cl_eemb3", &cl_eemb3, &b_cl_eemb3);
   fChain->SetBranchAddress("cl_nemb0", &cl_nemb0, &b_cl_nemb0);
   fChain->SetBranchAddress("cl_nemb1", &cl_nemb1, &b_cl_nemb1);
   fChain->SetBranchAddress("cl_nemb2", &cl_nemb2, &b_cl_nemb2);
   fChain->SetBranchAddress("cl_nemb3", &cl_nemb3, &b_cl_nemb3);
   fChain->SetBranchAddress("cl_phi2", &cl_phi2, &b_cl_phi2);
   fChain->SetBranchAddress("cl_eta0", &cl_eta0, &b_cl_eta0);
   fChain->SetBranchAddress("cl_eta1", &cl_eta1, &b_cl_eta1);
   fChain->SetBranchAddress("cl_eta2", &cl_eta2, &b_cl_eta2);
   fChain->SetBranchAddress("cl_eta3", &cl_eta3, &b_cl_eta3);
   fChain->SetBranchAddress("cl_eeme0", &cl_eeme0, &b_cl_eeme0);
   fChain->SetBranchAddress("cl_eeme1", &cl_eeme1, &b_cl_eeme1);
   fChain->SetBranchAddress("cl_eeme2", &cl_eeme2, &b_cl_eeme2);
   fChain->SetBranchAddress("cl_eeme3", &cl_eeme3, &b_cl_eeme3);
   fChain->SetBranchAddress("cl_neme0", &cl_neme0, &b_cl_neme0);
   fChain->SetBranchAddress("cl_neme1", &cl_neme1, &b_cl_neme1);
   fChain->SetBranchAddress("cl_neme2", &cl_neme2, &b_cl_neme2);
   fChain->SetBranchAddress("cl_neme3", &cl_neme3, &b_cl_neme3);
   fChain->SetBranchAddress("cl_etileg1", &cl_etileg1, &b_cl_etileg1);
   fChain->SetBranchAddress("cl_etileg2", &cl_etileg2, &b_cl_etileg2);
   fChain->SetBranchAddress("cl_etileg3", &cl_etileg3, &b_cl_etileg3);
   fChain->SetBranchAddress("cl_ntileg1", &cl_ntileg1, &b_cl_ntileg1);
   fChain->SetBranchAddress("cl_ntileg2", &cl_ntileg2, &b_cl_ntileg2);
   fChain->SetBranchAddress("cl_ntileg3", &cl_ntileg3, &b_cl_ntileg3);
   fChain->SetBranchAddress("cl_eta", &cl_eta, &b_cl_eta);
   fChain->SetBranchAddress("cl_phi", &cl_phi, &b_cl_phi);
   fChain->SetBranchAddress("cl_reco_stat", &cl_reco_stat, &b_cl_reco_stat);
   fChain->SetBranchAddress("cl_m1_eta", &cl_m1_eta, &b_cl_m1_eta);
   fChain->SetBranchAddress("cl_m1_phi", &cl_m1_phi, &b_cl_m1_phi);
   fChain->SetBranchAddress("cl_m2_r", &cl_m2_r, &b_cl_m2_r);
   fChain->SetBranchAddress("cl_m2_lambda", &cl_m2_lambda, &b_cl_m2_lambda);
   fChain->SetBranchAddress("cl_delta_phi", &cl_delta_phi, &b_cl_delta_phi);
   fChain->SetBranchAddress("cl_delta_theta", &cl_delta_theta, &b_cl_delta_theta);
   fChain->SetBranchAddress("cl_delta_alpha", &cl_delta_alpha, &b_cl_delta_alpha);
   fChain->SetBranchAddress("cl_center_x", &cl_center_x, &b_cl_center_x);
   fChain->SetBranchAddress("cl_center_y", &cl_center_y, &b_cl_center_y);
   fChain->SetBranchAddress("cl_center_z", &cl_center_z, &b_cl_center_z);
   fChain->SetBranchAddress("cl_center_lambda", &cl_center_lambda, &b_cl_center_lambda);
   fChain->SetBranchAddress("cl_lateral", &cl_lateral, &b_cl_lateral);
   fChain->SetBranchAddress("cl_longitudinal", &cl_longitudinal, &b_cl_longitudinal);
   fChain->SetBranchAddress("cl_eng_frac_em", &cl_eng_frac_em, &b_cl_eng_frac_em);
   fChain->SetBranchAddress("cl_eng_frac_max", &cl_eng_frac_max, &b_cl_eng_frac_max);
   fChain->SetBranchAddress("cl_eng_frac_core", &cl_eng_frac_core, &b_cl_eng_frac_core);
   fChain->SetBranchAddress("cl_m1_dens", &cl_m1_dens, &b_cl_m1_dens);
   fChain->SetBranchAddress("cl_m2_dens", &cl_m2_dens, &b_cl_m2_dens);
   fChain->SetBranchAddress("cl_isol", &cl_isol, &b_cl_isol);
   fChain->SetBranchAddress("cl_ntotcells", &cl_ntotcells, &b_cl_ntotcells);
   fChain->SetBranchAddress("cl_ecluster_topo", &cl_ecluster_topo, &b_cl_ecluster_topo);
   fChain->SetBranchAddress("cl_nctotal_topo", &cl_nctotal_topo, &b_cl_nctotal_topo);
   fChain->SetBranchAddress("cl_nc_topo", &cl_nc_topo, &b_cl_nc_topo);
   fChain->SetBranchAddress("cl_et_topo", &cl_et_topo, &b_cl_et_topo);
   fChain->SetBranchAddress("cl_e_topo", &cl_e_topo, &b_cl_e_topo);
   fChain->SetBranchAddress("cl_eemb0_topo", &cl_eemb0_topo, &b_cl_eemb0_topo);
   fChain->SetBranchAddress("cl_eemb1_topo", &cl_eemb1_topo, &b_cl_eemb1_topo);
   fChain->SetBranchAddress("cl_eemb2_topo", &cl_eemb2_topo, &b_cl_eemb2_topo);
   fChain->SetBranchAddress("cl_eemb3_topo", &cl_eemb3_topo, &b_cl_eemb3_topo);
   fChain->SetBranchAddress("cl_nemb0_topo", &cl_nemb0_topo, &b_cl_nemb0_topo);
   fChain->SetBranchAddress("cl_nemb1_topo", &cl_nemb1_topo, &b_cl_nemb1_topo);
   fChain->SetBranchAddress("cl_nemb2_topo", &cl_nemb2_topo, &b_cl_nemb2_topo);
   fChain->SetBranchAddress("cl_nemb3_topo", &cl_nemb3_topo, &b_cl_nemb3_topo);
   fChain->SetBranchAddress("cl_phi2_topo", &cl_phi2_topo, &b_cl_phi2_topo);
   fChain->SetBranchAddress("cl_eta0_topo", &cl_eta0_topo, &b_cl_eta0_topo);
   fChain->SetBranchAddress("cl_eta1_topo", &cl_eta1_topo, &b_cl_eta1_topo);
   fChain->SetBranchAddress("cl_eta2_topo", &cl_eta2_topo, &b_cl_eta2_topo);
   fChain->SetBranchAddress("cl_eta3_topo", &cl_eta3_topo, &b_cl_eta3_topo);
   fChain->SetBranchAddress("cl_eeme0_topo", &cl_eeme0_topo, &b_cl_eeme0_topo);
   fChain->SetBranchAddress("cl_eeme1_topo", &cl_eeme1_topo, &b_cl_eeme1_topo);
   fChain->SetBranchAddress("cl_eeme2_topo", &cl_eeme2_topo, &b_cl_eeme2_topo);
   fChain->SetBranchAddress("cl_eeme3_topo", &cl_eeme3_topo, &b_cl_eeme3_topo);
   fChain->SetBranchAddress("cl_neme0_topo", &cl_neme0_topo, &b_cl_neme0_topo);
   fChain->SetBranchAddress("cl_neme1_topo", &cl_neme1_topo, &b_cl_neme1_topo);
   fChain->SetBranchAddress("cl_neme2_topo", &cl_neme2_topo, &b_cl_neme2_topo);
   fChain->SetBranchAddress("cl_neme3_topo", &cl_neme3_topo, &b_cl_neme3_topo);
   fChain->SetBranchAddress("cl_etileg1_topo", &cl_etileg1_topo, &b_cl_etileg1_topo);
   fChain->SetBranchAddress("cl_etileg2_topo", &cl_etileg2_topo, &b_cl_etileg2_topo);
   fChain->SetBranchAddress("cl_etileg3_topo", &cl_etileg3_topo, &b_cl_etileg3_topo);
   fChain->SetBranchAddress("cl_ntileg1_topo", &cl_ntileg1_topo, &b_cl_ntileg1_topo);
   fChain->SetBranchAddress("cl_ntileg2_topo", &cl_ntileg2_topo, &b_cl_ntileg2_topo);
   fChain->SetBranchAddress("cl_ntileg3_topo", &cl_ntileg3_topo, &b_cl_ntileg3_topo);
   fChain->SetBranchAddress("cl_eta_topo", &cl_eta_topo, &b_cl_eta_topo);
   fChain->SetBranchAddress("cl_phi_topo", &cl_phi_topo, &b_cl_phi_topo);
   fChain->SetBranchAddress("cl_reco_stat_topo", &cl_reco_stat_topo, &b_cl_reco_stat_topo);
   fChain->SetBranchAddress("cl_m1_eta_topo", &cl_m1_eta_topo, &b_cl_m1_eta_topo);
   fChain->SetBranchAddress("cl_m1_phi_topo", &cl_m1_phi_topo, &b_cl_m1_phi_topo);
   fChain->SetBranchAddress("cl_m2_r_topo", &cl_m2_r_topo, &b_cl_m2_r_topo);
   fChain->SetBranchAddress("cl_m2_lambda_topo", &cl_m2_lambda_topo, &b_cl_m2_lambda_topo);
   fChain->SetBranchAddress("cl_delta_phi_topo", &cl_delta_phi_topo, &b_cl_delta_phi_topo);
   fChain->SetBranchAddress("cl_delta_theta_topo", &cl_delta_theta_topo, &b_cl_delta_theta_topo);
   fChain->SetBranchAddress("cl_delta_alpha_topo", &cl_delta_alpha_topo, &b_cl_delta_alpha_topo);
   fChain->SetBranchAddress("cl_center_x_topo", &cl_center_x_topo, &b_cl_center_x_topo);
   fChain->SetBranchAddress("cl_center_y_topo", &cl_center_y_topo, &b_cl_center_y_topo);
   fChain->SetBranchAddress("cl_center_z_topo", &cl_center_z_topo, &b_cl_center_z_topo);
   fChain->SetBranchAddress("cl_center_lambda_topo", &cl_center_lambda_topo, &b_cl_center_lambda_topo);
   fChain->SetBranchAddress("cl_lateral_topo", &cl_lateral_topo, &b_cl_lateral_topo);
   fChain->SetBranchAddress("cl_longitudinal_topo", &cl_longitudinal_topo, &b_cl_longitudinal_topo);
   fChain->SetBranchAddress("cl_eng_frac_em_topo", &cl_eng_frac_em_topo, &b_cl_eng_frac_em_topo);
   fChain->SetBranchAddress("cl_eng_frac_max_topo", &cl_eng_frac_max_topo, &b_cl_eng_frac_max_topo);
   fChain->SetBranchAddress("cl_eng_frac_core_topo", &cl_eng_frac_core_topo, &b_cl_eng_frac_core_topo);
   fChain->SetBranchAddress("cl_m1_dens_topo", &cl_m1_dens_topo, &b_cl_m1_dens_topo);
   fChain->SetBranchAddress("cl_m2_dens_topo", &cl_m2_dens_topo, &b_cl_m2_dens_topo);
   fChain->SetBranchAddress("cl_isol_topo", &cl_isol_topo, &b_cl_isol_topo);
   fChain->SetBranchAddress("cl_ehec0_topo", &cl_ehec0_topo, &b_cl_ehec0_topo);
   fChain->SetBranchAddress("cl_ehec1_topo", &cl_ehec1_topo, &b_cl_ehec1_topo);
   fChain->SetBranchAddress("cl_ehec2_topo", &cl_ehec2_topo, &b_cl_ehec2_topo);
   fChain->SetBranchAddress("cl_ehec3_topo", &cl_ehec3_topo, &b_cl_ehec3_topo);
   fChain->SetBranchAddress("cl_nhec0_topo", &cl_nhec0_topo, &b_cl_nhec0_topo);
   fChain->SetBranchAddress("cl_nhec1_topo", &cl_nhec1_topo, &b_cl_nhec1_topo);
   fChain->SetBranchAddress("cl_nhec2_topo", &cl_nhec2_topo, &b_cl_nhec2_topo);
   fChain->SetBranchAddress("cl_nhec3_topo", &cl_nhec3_topo, &b_cl_nhec3_topo);
   fChain->SetBranchAddress("cl_etileb0_topo", &cl_etileb0_topo, &b_cl_etileb0_topo);
   fChain->SetBranchAddress("cl_etileb1_topo", &cl_etileb1_topo, &b_cl_etileb1_topo);
   fChain->SetBranchAddress("cl_etileb2_topo", &cl_etileb2_topo, &b_cl_etileb2_topo);
   fChain->SetBranchAddress("cl_ntileb0_topo", &cl_ntileb0_topo, &b_cl_ntileb0_topo);
   fChain->SetBranchAddress("cl_ntileb1_topo", &cl_ntileb1_topo, &b_cl_ntileb1_topo);
   fChain->SetBranchAddress("cl_ntileb2_topo", &cl_ntileb2_topo, &b_cl_ntileb2_topo);
   fChain->SetBranchAddress("cl_etilee0_topo", &cl_etilee0_topo, &b_cl_etilee0_topo);
   fChain->SetBranchAddress("cl_etilee1_topo", &cl_etilee1_topo, &b_cl_etilee1_topo);
   fChain->SetBranchAddress("cl_etilee2_topo", &cl_etilee2_topo, &b_cl_etilee2_topo);
   fChain->SetBranchAddress("cl_efcal0_topo", &cl_efcal0_topo, &b_cl_efcal0_topo);
   fChain->SetBranchAddress("cl_efcal1_topo", &cl_efcal1_topo, &b_cl_efcal1_topo);
   fChain->SetBranchAddress("cl_efcal2_topo", &cl_efcal2_topo, &b_cl_efcal2_topo);
   fChain->SetBranchAddress("cl_ntilee0_topo", &cl_ntilee0_topo, &b_cl_ntilee0_topo);
   fChain->SetBranchAddress("cl_ntilee1_topo", &cl_ntilee1_topo, &b_cl_ntilee1_topo);
   fChain->SetBranchAddress("cl_ntilee2_topo", &cl_ntilee2_topo, &b_cl_ntilee2_topo);
   fChain->SetBranchAddress("cl_nfcal0_topo", &cl_nfcal0_topo, &b_cl_nfcal0_topo);
   fChain->SetBranchAddress("cl_nfcal1_topo", &cl_nfcal1_topo, &b_cl_nfcal1_topo);
   fChain->SetBranchAddress("cl_nfcal2_topo", &cl_nfcal2_topo, &b_cl_nfcal2_topo);
   fChain->SetBranchAddress("cl_ntotcells_topo", &cl_ntotcells_topo, &b_cl_ntotcells_topo);
   fChain->SetBranchAddress("cl_ecluster_topoEM430", &cl_ecluster_topoEM430, &b_cl_ecluster_topoEM430);
   fChain->SetBranchAddress("cl_nctotal_topoEM430", &cl_nctotal_topoEM430, &b_cl_nctotal_topoEM430);
   fChain->SetBranchAddress("cl_nc_topoEM430", &cl_nc_topoEM430, &b_cl_nc_topoEM430);
   fChain->SetBranchAddress("cl_et_topoEM430", &cl_et_topoEM430, &b_cl_et_topoEM430);
   fChain->SetBranchAddress("cl_e_topoEM430", &cl_e_topoEM430, &b_cl_e_topoEM430);
   fChain->SetBranchAddress("cl_eemb0_topoEM430", &cl_eemb0_topoEM430, &b_cl_eemb0_topoEM430);
   fChain->SetBranchAddress("cl_eemb1_topoEM430", &cl_eemb1_topoEM430, &b_cl_eemb1_topoEM430);
   fChain->SetBranchAddress("cl_eemb2_topoEM430", &cl_eemb2_topoEM430, &b_cl_eemb2_topoEM430);
   fChain->SetBranchAddress("cl_eemb3_topoEM430", &cl_eemb3_topoEM430, &b_cl_eemb3_topoEM430);
   fChain->SetBranchAddress("cl_nemb0_topoEM430", &cl_nemb0_topoEM430, &b_cl_nemb0_topoEM430);
   fChain->SetBranchAddress("cl_nemb1_topoEM430", &cl_nemb1_topoEM430, &b_cl_nemb1_topoEM430);
   fChain->SetBranchAddress("cl_nemb2_topoEM430", &cl_nemb2_topoEM430, &b_cl_nemb2_topoEM430);
   fChain->SetBranchAddress("cl_nemb3_topoEM430", &cl_nemb3_topoEM430, &b_cl_nemb3_topoEM430);
   fChain->SetBranchAddress("cl_phi2_topoEM430", &cl_phi2_topoEM430, &b_cl_phi2_topoEM430);
   fChain->SetBranchAddress("cl_eta0_topoEM430", &cl_eta0_topoEM430, &b_cl_eta0_topoEM430);
   fChain->SetBranchAddress("cl_eta1_topoEM430", &cl_eta1_topoEM430, &b_cl_eta1_topoEM430);
   fChain->SetBranchAddress("cl_eta2_topoEM430", &cl_eta2_topoEM430, &b_cl_eta2_topoEM430);
   fChain->SetBranchAddress("cl_eta3_topoEM430", &cl_eta3_topoEM430, &b_cl_eta3_topoEM430);
   fChain->SetBranchAddress("cl_eeme0_topoEM430", &cl_eeme0_topoEM430, &b_cl_eeme0_topoEM430);
   fChain->SetBranchAddress("cl_eeme1_topoEM430", &cl_eeme1_topoEM430, &b_cl_eeme1_topoEM430);
   fChain->SetBranchAddress("cl_eeme2_topoEM430", &cl_eeme2_topoEM430, &b_cl_eeme2_topoEM430);
   fChain->SetBranchAddress("cl_eeme3_topoEM430", &cl_eeme3_topoEM430, &b_cl_eeme3_topoEM430);
   fChain->SetBranchAddress("cl_neme0_topoEM430", &cl_neme0_topoEM430, &b_cl_neme0_topoEM430);
   fChain->SetBranchAddress("cl_neme1_topoEM430", &cl_neme1_topoEM430, &b_cl_neme1_topoEM430);
   fChain->SetBranchAddress("cl_neme2_topoEM430", &cl_neme2_topoEM430, &b_cl_neme2_topoEM430);
   fChain->SetBranchAddress("cl_neme3_topoEM430", &cl_neme3_topoEM430, &b_cl_neme3_topoEM430);
   fChain->SetBranchAddress("cl_etileg1_topoEM430", &cl_etileg1_topoEM430, &b_cl_etileg1_topoEM430);
   fChain->SetBranchAddress("cl_etileg2_topoEM430", &cl_etileg2_topoEM430, &b_cl_etileg2_topoEM430);
   fChain->SetBranchAddress("cl_etileg3_topoEM430", &cl_etileg3_topoEM430, &b_cl_etileg3_topoEM430);
   fChain->SetBranchAddress("cl_ntileg1_topoEM430", &cl_ntileg1_topoEM430, &b_cl_ntileg1_topoEM430);
   fChain->SetBranchAddress("cl_ntileg2_topoEM430", &cl_ntileg2_topoEM430, &b_cl_ntileg2_topoEM430);
   fChain->SetBranchAddress("cl_ntileg3_topoEM430", &cl_ntileg3_topoEM430, &b_cl_ntileg3_topoEM430);
   fChain->SetBranchAddress("cl_eta_topoEM430", &cl_eta_topoEM430, &b_cl_eta_topoEM430);
   fChain->SetBranchAddress("cl_phi_topoEM430", &cl_phi_topoEM430, &b_cl_phi_topoEM430);
   fChain->SetBranchAddress("cl_reco_stat_topoEM430", &cl_reco_stat_topoEM430, &b_cl_reco_stat_topoEM430);
   fChain->SetBranchAddress("cl_m1_eta_topoEM430", &cl_m1_eta_topoEM430, &b_cl_m1_eta_topoEM430);
   fChain->SetBranchAddress("cl_m1_phi_topoEM430", &cl_m1_phi_topoEM430, &b_cl_m1_phi_topoEM430);
   fChain->SetBranchAddress("cl_m2_r_topoEM430", &cl_m2_r_topoEM430, &b_cl_m2_r_topoEM430);
   fChain->SetBranchAddress("cl_m2_lambda_topoEM430", &cl_m2_lambda_topoEM430, &b_cl_m2_lambda_topoEM430);
   fChain->SetBranchAddress("cl_delta_phi_topoEM430", &cl_delta_phi_topoEM430, &b_cl_delta_phi_topoEM430);
   fChain->SetBranchAddress("cl_delta_theta_topoEM430", &cl_delta_theta_topoEM430, &b_cl_delta_theta_topoEM430);
   fChain->SetBranchAddress("cl_delta_alpha_topoEM430", &cl_delta_alpha_topoEM430, &b_cl_delta_alpha_topoEM430);
   fChain->SetBranchAddress("cl_center_x_topoEM430", &cl_center_x_topoEM430, &b_cl_center_x_topoEM430);
   fChain->SetBranchAddress("cl_center_y_topoEM430", &cl_center_y_topoEM430, &b_cl_center_y_topoEM430);
   fChain->SetBranchAddress("cl_center_z_topoEM430", &cl_center_z_topoEM430, &b_cl_center_z_topoEM430);
   fChain->SetBranchAddress("cl_center_lambda_topoEM430", &cl_center_lambda_topoEM430, &b_cl_center_lambda_topoEM430);
   fChain->SetBranchAddress("cl_lateral_topoEM430", &cl_lateral_topoEM430, &b_cl_lateral_topoEM430);
   fChain->SetBranchAddress("cl_longitudinal_topoEM430", &cl_longitudinal_topoEM430, &b_cl_longitudinal_topoEM430);
   fChain->SetBranchAddress("cl_eng_frac_em_topoEM430", &cl_eng_frac_em_topoEM430, &b_cl_eng_frac_em_topoEM430);
   fChain->SetBranchAddress("cl_eng_frac_max_topoEM430", &cl_eng_frac_max_topoEM430, &b_cl_eng_frac_max_topoEM430);
   fChain->SetBranchAddress("cl_eng_frac_core_topoEM430", &cl_eng_frac_core_topoEM430, &b_cl_eng_frac_core_topoEM430);
   fChain->SetBranchAddress("cl_m1_dens_topoEM430", &cl_m1_dens_topoEM430, &b_cl_m1_dens_topoEM430);
   fChain->SetBranchAddress("cl_m2_dens_topoEM430", &cl_m2_dens_topoEM430, &b_cl_m2_dens_topoEM430);
   fChain->SetBranchAddress("cl_isol_topoEM430", &cl_isol_topoEM430, &b_cl_isol_topoEM430);
   fChain->SetBranchAddress("cl_ntotcells_topoEM430", &cl_ntotcells_topoEM430, &b_cl_ntotcells_topoEM430);
   fChain->SetBranchAddress("NTileMuonTag", &NTileMuonTag, &b_NTileMuonTag);
   fChain->SetBranchAddress("EtaTileMuonTag", &EtaTileMuonTag, &b_EtaTileMuonTag);
   fChain->SetBranchAddress("PhiTileMuonTag", &PhiTileMuonTag, &b_PhiTileMuonTag);
   fChain->SetBranchAddress("EnergyVecTileMuonTag", &EnergyVecTileMuonTag, &b_EnergyVecTileMuonTag);
   fChain->SetBranchAddress("LabelTileMuonTag", &LabelTileMuonTag, &b_LabelTileMuonTag);
   fChain->SetBranchAddress("TileCosmicsHT_x", &TileCosmicsHT_x, &b_TileCosmicsHT_x);
   fChain->SetBranchAddress("TileCosmicsHT_y", &TileCosmicsHT_y, &b_TileCosmicsHT_y);
   fChain->SetBranchAddress("TileCosmicsHT_z", &TileCosmicsHT_z, &b_TileCosmicsHT_z);
   fChain->SetBranchAddress("TileCosmicsHT_phi", &TileCosmicsHT_phi, &b_TileCosmicsHT_phi);
   fChain->SetBranchAddress("TileCosmicsHT_theta", &TileCosmicsHT_theta, &b_TileCosmicsHT_theta);
   fChain->SetBranchAddress("TileCosmicsHT_time", &TileCosmicsHT_time, &b_TileCosmicsHT_time);
   fChain->SetBranchAddress("TileCosmicsHT_fitQuality", &TileCosmicsHT_fitQuality, &b_TileCosmicsHT_fitQuality);
   fChain->SetBranchAddress("TileCosmicsHT_fitNcells", &TileCosmicsHT_fitNcells, &b_TileCosmicsHT_fitCells);
   fChain->SetBranchAddress("TileCosmicsHT_path", &TileCosmicsHT_path, &b_TileCosmicsHT_path);
   fChain->SetBranchAddress("TileCosmicsHT_energy", &TileCosmicsHT_energy, &b_TileCosmicsHT_energy);
   fChain->SetBranchAddress("TileCosmicsHT_pathTop", &TileCosmicsHT_pathTop, &b_TileCosmicsHT_pathTop);
   fChain->SetBranchAddress("TileCosmicsHT_pathBottom", &TileCosmicsHT_pathBottom, &b_TileCosmicsHT_pathBottom);
   fChain->SetBranchAddress("TileCosmicsHT_energyTop", &TileCosmicsHT_energyTop, &b_TileCosmicsHT_energyTop);
   fChain->SetBranchAddress("TileCosmicsHT_energyBottom", &TileCosmicsHT_energyBottom, &b_TileCosmicsHT_energyBottom);
   fChain->SetBranchAddress("TileCosmicsHT_trackNcells", &TileCosmicsHT_trackNcells, &b_TileCosmicsHT_trackCellN);
   fChain->SetBranchAddress("TileCosmicsHT_cellE", &TileCosmicsHT_cellE, &b_TileCosmicsHT_cellE);
   fChain->SetBranchAddress("TileCosmicsHT_cellT", &TileCosmicsHT_cellT, &b_TileCosmicsHT_cellT);
   fChain->SetBranchAddress("TileCosmicsHT_cellEta", &TileCosmicsHT_cellEta, &b_TileCosmicsHT_cellEta);
   fChain->SetBranchAddress("TileCosmicsHT_cellPhi", &TileCosmicsHT_cellPhi, &b_TileCosmicsHT_cellPhi);
   fChain->SetBranchAddress("TileCosmicsHT_cellSample", &TileCosmicsHT_cellSample, &b_TileCosmicsHT_cellSample);
   fChain->SetBranchAddress("TileCosmicsHT_cellEdiff", &TileCosmicsHT_cellEdiff, &b_TileCosmicsHT_cellEdiff);
   fChain->SetBranchAddress("TileCosmicsHT_cellTdiff", &TileCosmicsHT_cellTdiff, &b_TileCosmicsHT_cellTdiff);
   fChain->SetBranchAddress("NTileMuonRODTag", &NTileMuonRODTag, &b_NTileMuonRODTag);
   fChain->SetBranchAddress("EtaTileMuonRODTag", &EtaTileMuonRODTag, &b_EtaTileMuonRODTag);
   fChain->SetBranchAddress("PhiTileMuonRODTag", &PhiTileMuonRODTag, &b_PhiTileMuonRODTag);
   fChain->SetBranchAddress("EnergyVecTileMuonRODTag", &EnergyVecTileMuonRODTag, &b_EnergyVecTileMuonRODTag);
   fChain->SetBranchAddress("LabelTileMuonRODTag", &LabelTileMuonRODTag, &b_LabelTileMuonRODTag);
   fChain->SetBranchAddress("mdt_nprdcoll", &mdt_nprdcoll, &b_m_nMdtColl);
   fChain->SetBranchAddress("mdt_nprd", &mdt_nprd, &b_m_nMdtPrd);
   fChain->SetBranchAddress("mdt_tdc", &mdt_tdc, &b_mdt_tdc);
   fChain->SetBranchAddress("mdt_adc", &mdt_adc, &b_mdt_adc);
   fChain->SetBranchAddress("mdt_station", &mdt_station, &b_mdt_station);
   fChain->SetBranchAddress("mdt_eta", &mdt_eta, &b_mdt_eta);
   fChain->SetBranchAddress("mdt_phi", &mdt_phi, &b_mdt_phi);
   fChain->SetBranchAddress("mdt_multi", &mdt_multi, &b_mdt_multi);
   fChain->SetBranchAddress("mdt_layer", &mdt_layer, &b_mdt_layer);
   fChain->SetBranchAddress("mdt_wire", &mdt_wire, &b_mdt_wire);
   fChain->SetBranchAddress("mdt_nmaxtubes", &mdt_nmaxtubes, &b_mdt_nmaxtubes);
   fChain->SetBranchAddress("mdt_globPosX", &mdt_globPosX, &b_mdt_globPosX);
   fChain->SetBranchAddress("mdt_globPosY", &mdt_globPosY, &b_mdt_globPosY);
   fChain->SetBranchAddress("mdt_globPosZ", &mdt_globPosZ, &b_mdt_globPosZ);
   fChain->SetBranchAddress("mdt_ncsm", &mdt_ncsm, &b_m_nCsm);
   fChain->SetBranchAddress("mdt_namt", &mdt_namt, &b_m_nAmt);
   fChain->SetBranchAddress("mdt_subid", &mdt_subid, &b_mdt_subid);
   fChain->SetBranchAddress("mdt_rodid", &mdt_rodid, &b_mdt_rodid);
   fChain->SetBranchAddress("mdt_csmid", &mdt_csmid, &b_mdt_csmid);
   fChain->SetBranchAddress("mdt_tdcid", &mdt_tdcid, &b_mdt_tdcid);
   fChain->SetBranchAddress("mdt_chanid", &mdt_chanid, &b_mdt_chanid);
   fChain->SetBranchAddress("mdt_fine", &mdt_fine, &b_mdt_fine);
   fChain->SetBranchAddress("mdt_coarse", &mdt_coarse, &b_mdt_coarse);
   fChain->SetBranchAddress("mdt_width", &mdt_width, &b_mdt_width);
   fChain->SetBranchAddress("rpc_prd_ncoll", &rpc_prd_ncoll, &b_m_nRpcColl);
   fChain->SetBranchAddress("rpc_nprd", &rpc_nprd, &b_m_nRpcPrd);
   fChain->SetBranchAddress("rpc_prd_station", &rpc_prd_station, &b_rpc_prd_station);
   fChain->SetBranchAddress("rpc_prd_eta", &rpc_prd_eta, &b_rpc_prd_eta);
   fChain->SetBranchAddress("rpc_prd_phi", &rpc_prd_phi, &b_rpc_prd_phi);
   fChain->SetBranchAddress("rpc_prd_doublr", &rpc_prd_doublr, &b_rpc_prd_doublr);
   fChain->SetBranchAddress("rpc_prd_doublz", &rpc_prd_doublz, &b_rpc_prd_doublz);
   fChain->SetBranchAddress("rpc_prd_doublphi", &rpc_prd_doublphi, &b_rpc_prd_doublphi);
   fChain->SetBranchAddress("rpc_prd_gasgap", &rpc_prd_gasgap, &b_rpc_prd_gasgap);
   fChain->SetBranchAddress("rpc_prd_measphi", &rpc_prd_measphi, &b_rpc_prd_measphi);
   fChain->SetBranchAddress("rpc_prd_strip", &rpc_prd_strip, &b_rpc_prd_strip);
   fChain->SetBranchAddress("rpc_prd_time", &rpc_prd_time, &b_rpc_prd_time);
   fChain->SetBranchAddress("rpc_prd_stripx", &rpc_prd_stripx, &b_rpc_prd_stripx);
   fChain->SetBranchAddress("rpc_prd_stripy", &rpc_prd_stripy, &b_rpc_prd_stripy);
   fChain->SetBranchAddress("rpc_prd_stripz", &rpc_prd_stripz, &b_rpc_prd_stripz);
   fChain->SetBranchAddress("rpc_prd_triggerInfo", &rpc_prd_triggerInfo, &b_rpc_prd_triggerInfo);
   fChain->SetBranchAddress("rpc_prd_ambigFlag", &rpc_prd_ambigFlag, &b_rpc_prd_ambigFlag);
   fChain->SetBranchAddress("rpc_nclus", &rpc_nclus, &b_m_nClus);
   fChain->SetBranchAddress("rpc_clus_station", &rpc_clus_station, &b_rpc_clus_station);
   fChain->SetBranchAddress("rpc_clus_eta", &rpc_clus_eta, &b_rpc_clus_eta);
   fChain->SetBranchAddress("rpc_clus_phi", &rpc_clus_phi, &b_rpc_clus_phi);
   fChain->SetBranchAddress("rpc_clus_doublr", &rpc_clus_doublr, &b_rpc_clus_doublr);
   fChain->SetBranchAddress("rpc_clus_doublz", &rpc_clus_doublz, &b_rpc_clus_doublz);
   fChain->SetBranchAddress("rpc_clus_doublphi", &rpc_clus_doublphi, &b_rpc_clus_doublphi);
   fChain->SetBranchAddress("rpc_clus_gasgap", &rpc_clus_gasgap, &b_rpc_clus_gasgap);
   fChain->SetBranchAddress("rpc_clus_measphi", &rpc_clus_measphi, &b_rpc_clus_measphi);
   fChain->SetBranchAddress("rpc_clus_size", &rpc_clus_size, &b_rpc_clus_size);
   fChain->SetBranchAddress("rpc_clus_time", &rpc_clus_time, &b_rpc_clus_time);
   fChain->SetBranchAddress("rpc_clus_posx", &rpc_clus_posx, &b_rpc_clus_posx);
   fChain->SetBranchAddress("rpc_clus_posy", &rpc_clus_posy, &b_rpc_clus_posy);
   fChain->SetBranchAddress("rpc_clus_posz", &rpc_clus_posz, &b_rpc_clus_posz);
   fChain->SetBranchAddress("rpc_npads", &rpc_npads, &b_m_nPads);
   fChain->SetBranchAddress("rpc_pad_id", &rpc_pad_id, &b_rpc_pad_id);
   fChain->SetBranchAddress("rpc_pad_bcid", &rpc_pad_bcid, &b_rpc_pad_bcid);
   fChain->SetBranchAddress("rpc_pad_lvl1id", &rpc_pad_lvl1id, &b_rpc_pad_lvl1id);
   fChain->SetBranchAddress("rpc_pad_sectorid", &rpc_pad_sectorid, &b_rpc_pad_sectorid);
   fChain->SetBranchAddress("rpc_pad_status", &rpc_pad_status, &b_rpc_pad_status);
   fChain->SetBranchAddress("rpc_pad_error", &rpc_pad_error, &b_rpc_pad_error);
   fChain->SetBranchAddress("rpc_ncmas", &rpc_ncmas, &b_m_nCMA);
   fChain->SetBranchAddress("rpc_fchan", &rpc_fchan, &b_m_nFiredChannels);
   fChain->SetBranchAddress("rpc_sector", &rpc_sector, &b_rpc_sector);
   fChain->SetBranchAddress("rpc_padId", &rpc_padId, &b_rpc_padId);
   fChain->SetBranchAddress("rpc_status", &rpc_status, &b_rpc_status);
   fChain->SetBranchAddress("rpc_ercode", &rpc_ercode, &b_rpc_ercode);
   fChain->SetBranchAddress("rpc_cmaId", &rpc_cmaId, &b_rpc_cmaId);
   fChain->SetBranchAddress("rpc_fel1Id", &rpc_fel1Id, &b_rpc_fel1Id);
   fChain->SetBranchAddress("rpc_febcId", &rpc_febcId, &b_rpc_febcId);
   fChain->SetBranchAddress("rpc_crc", &rpc_crc, &b_rpc_crc);
   fChain->SetBranchAddress("rpc_bcId", &rpc_bcId, &b_rpc_bcId);
   fChain->SetBranchAddress("rpc_ticks", &rpc_ticks, &b_rpc_ticks);
   fChain->SetBranchAddress("rpc_ijk", &rpc_ijk, &b_rpc_ijk);
   fChain->SetBranchAddress("rpc_cmachan", &rpc_cmachan, &b_rpc_cmachan);
   fChain->SetBranchAddress("rpc_overlap", &rpc_overlap, &b_rpc_overlap);
   fChain->SetBranchAddress("rpc_threshold", &rpc_threshold, &b_rpc_threshold);
   fChain->SetBranchAddress("rpc_SL_nSectors", &rpc_SL_nSectors, &b_m_SL_nSectors);
   fChain->SetBranchAddress("rpc_SL_sectorId", &rpc_SL_sectorId, &b_rpc_SL_sectorId);
   fChain->SetBranchAddress("rpc_SL_bcid", &rpc_SL_bcid, &b_rpc_SL_bcid);
   fChain->SetBranchAddress("rpc_SL_lvl1id", &rpc_SL_lvl1id, &b_rpc_SL_lvl1id);
   fChain->SetBranchAddress("rpc_SLnTriggerHits", &rpc_SLnTriggerHits, &b_m_SL_nTriggerHits);
   fChain->SetBranchAddress("rpc_SLhit_sector", &rpc_SLhit_sector, &b_rpc_SLhit_sector);
   fChain->SetBranchAddress("rpc_SLhit_rowinBcid", &rpc_SLhit_rowinBcid, &b_rpc_SLhit_rowinBcid);
   fChain->SetBranchAddress("rpc_SLhit_triggerBcid", &rpc_SLhit_triggerBcid, &b_rpc_SLhit_triggerBcid);
   fChain->SetBranchAddress("rpc_SLhit_padId", &rpc_SLhit_padId, &b_rpc_SLhit_padId);
   fChain->SetBranchAddress("rpc_SLhit_ptId", &rpc_SLhit_ptId, &b_rpc_SLhit_ptId);
   fChain->SetBranchAddress("rpc_SLhit_roi", &rpc_SLhit_roi, &b_rpc_SLhit_roi);
   fChain->SetBranchAddress("rpc_SLhit_outerPlane", &rpc_SLhit_outerPlane, &b_rpc_SLhit_outerPlane);
   fChain->SetBranchAddress("rpc_SLhit_overlapPhi", &rpc_SLhit_overlapPhi, &b_rpc_SLhit_overlapPhi);
   fChain->SetBranchAddress("rpc_SLhit_overlapEta", &rpc_SLhit_overlapEta, &b_rpc_SLhit_overlapEta);
   fChain->SetBranchAddress("tgc_bcTag", &tgc_bcTag, &b_tgc_bcTag);
   fChain->SetBranchAddress("tgc_cointrackletbcTag", &tgc_cointrackletbcTag, &b_tgc_cointrackletbcTag);
   fChain->SetBranchAddress("tgc_coinhighptbcTag", &tgc_coinhighptbcTag, &b_tgc_coinhighptbcTag);
   fChain->SetBranchAddress("tgc_coinslbcTag", &tgc_coinslbcTag, &b_tgc_coinslbcTag);
   fChain->SetBranchAddress("tgc_cointype", &tgc_cointype, &b_tgc_cointype);
   fChain->SetBranchAddress("tgc_cointype_Prev", &tgc_cointype_Prev, &b_tgc_cointype_Prev);
   fChain->SetBranchAddress("tgc_cointype_Next", &tgc_cointype_Next, &b_tgc_cointype_Next);
   fChain->SetBranchAddress("tgc_nprdcoll", &tgc_nprdcoll, &b_m_nTgcColl);
   fChain->SetBranchAddress("tgc_nprd", &tgc_nprd, &b_m_nTgcPrd);
   fChain->SetBranchAddress("tgc_station", &tgc_station, &b_tgc_station);
   fChain->SetBranchAddress("tgc_eta", &tgc_eta, &b_tgc_eta);
   fChain->SetBranchAddress("tgc_phi", &tgc_phi, &b_tgc_phi);
   fChain->SetBranchAddress("tgc_gasGap", &tgc_gasGap, &b_tgc_gasGap);
   fChain->SetBranchAddress("tgc_isStrip", &tgc_isStrip, &b_tgc_isStrip);
   fChain->SetBranchAddress("tgc_channel", &tgc_channel, &b_tgc_channel);
   fChain->SetBranchAddress("tgc_globPosX", &tgc_globPosX, &b_tgc_globPosX);
   fChain->SetBranchAddress("tgc_globPosY", &tgc_globPosY, &b_tgc_globPosY);
   fChain->SetBranchAddress("tgc_globPosZ", &tgc_globPosZ, &b_tgc_globPosZ);
   fChain->SetBranchAddress("tgc_shortWidth", &tgc_shortWidth, &b_tgc_shortWidth);
   fChain->SetBranchAddress("tgc_longWidth", &tgc_longWidth, &b_tgc_longWidth);
   fChain->SetBranchAddress("tgc_length", &tgc_length, &b_tgc_length);
   fChain->SetBranchAddress("tgc_ncoincoll", &tgc_ncoincoll, &b_m_nTgcCoinColl);
   fChain->SetBranchAddress("tgc_ncointracklet", &tgc_ncointracklet, &b_m_nTgcCoinTracklet);
   fChain->SetBranchAddress("tgc_cointrackletdelta", &tgc_cointrackletdelta, &b_tgc_cointrackletdelta);
   fChain->SetBranchAddress("tgc_cointrackletposx_in", &tgc_cointrackletposx_in, &b_tgc_cointrackletposx_in);
   fChain->SetBranchAddress("tgc_cointrackletposy_in", &tgc_cointrackletposy_in, &b_tgc_cointrackletposy_in);
   fChain->SetBranchAddress("tgc_cointrackletposz_in", &tgc_cointrackletposz_in, &b_tgc_cointrackletposz_in);
   fChain->SetBranchAddress("tgc_cointrackletposx_out", &tgc_cointrackletposx_out, &b_tgc_cointrackletposx_out);
   fChain->SetBranchAddress("tgc_cointrackletposy_out", &tgc_cointrackletposy_out, &b_tgc_cointrackletposy_out);
   fChain->SetBranchAddress("tgc_cointrackletposz_out", &tgc_cointrackletposz_out, &b_tgc_cointrackletposz_out);
   fChain->SetBranchAddress("tgc_cointrackletstrip", &tgc_cointrackletstrip, &b_tgc_cointrackletstrip);
   fChain->SetBranchAddress("tgc_cointrackletforward", &tgc_cointrackletforward, &b_tgc_cointrackletforward);
   fChain->SetBranchAddress("tgc_cointrackletwidthout", &tgc_cointrackletwidthout, &b_tgc_cointrackletwidthout);
   fChain->SetBranchAddress("tgc_cointrackletwidthin", &tgc_cointrackletwidthin, &b_tgc_cointrackletwidthin);
   fChain->SetBranchAddress("tgc_cointrackletstationeta", &tgc_cointrackletstationeta, &b_tgc_cointrackletstationeta);
   fChain->SetBranchAddress("tgc_cointrackletstationphi", &tgc_cointrackletstationphi, &b_tgc_cointrackletstationphi);
   fChain->SetBranchAddress("tgc_cointrackletsector", &tgc_cointrackletsector, &b_tgc_cointrackletsector);
   fChain->SetBranchAddress("tgc_cointracklettrackletid", &tgc_cointracklettrackletid, &b_tgc_cointracklettrackletid);
   fChain->SetBranchAddress("tgc_ncoinhighpt", &tgc_ncoinhighpt, &b_m_nTgcCoinHighPt);
   fChain->SetBranchAddress("tgc_coinhighptdelta", &tgc_coinhighptdelta, &b_tgc_coinhighptdelta);
   fChain->SetBranchAddress("tgc_coinhighptposx_in", &tgc_coinhighptposx_in, &b_tgc_coinhighptposx_in);
   fChain->SetBranchAddress("tgc_coinhighptposy_in", &tgc_coinhighptposy_in, &b_tgc_coinhighptposy_in);
   fChain->SetBranchAddress("tgc_coinhighptposz_in", &tgc_coinhighptposz_in, &b_tgc_coinhighptposz_in);
   fChain->SetBranchAddress("tgc_coinhighptposx_out", &tgc_coinhighptposx_out, &b_tgc_coinhighptposx_out);
   fChain->SetBranchAddress("tgc_coinhighptposy_out", &tgc_coinhighptposy_out, &b_tgc_coinhighptposy_out);
   fChain->SetBranchAddress("tgc_coinhighptposz_out", &tgc_coinhighptposz_out, &b_tgc_coinhighptposz_out);
   fChain->SetBranchAddress("tgc_coinhighptstrip", &tgc_coinhighptstrip, &b_tgc_coinhighptstrip);
   fChain->SetBranchAddress("tgc_coinhighptforward", &tgc_coinhighptforward, &b_tgc_coinhighptforward);
   fChain->SetBranchAddress("tgc_coinhighptwidthout", &tgc_coinhighptwidthout, &b_tgc_coinhighptwidthout);
   fChain->SetBranchAddress("tgc_coinhighptwidthin", &tgc_coinhighptwidthin, &b_tgc_coinhighptwidthin);
   fChain->SetBranchAddress("tgc_coinhighptstationeta", &tgc_coinhighptstationeta, &b_tgc_coinhighptstationeta);
   fChain->SetBranchAddress("tgc_coinhighptstationphi", &tgc_coinhighptstationphi, &b_tgc_coinhighptstationphi);
   fChain->SetBranchAddress("tgc_coinhighptsector", &tgc_coinhighptsector, &b_tgc_coinhighptsector);
   fChain->SetBranchAddress("tgc_coinhighpttrackletid", &tgc_coinhighpttrackletid, &b_tgc_coinhighpttrackletid);
   fChain->SetBranchAddress("tgc_ncoinsl", &tgc_ncoinsl, &b_m_nTgcCoinSl);
   fChain->SetBranchAddress("tgc_coinslptthresh", &tgc_coinslptthresh, &b_tgc_coinslptthresh);
   fChain->SetBranchAddress("tgc_coinslposx_out", &tgc_coinslposx_out, &b_tgc_coinslposx_out);
   fChain->SetBranchAddress("tgc_coinslposy_out", &tgc_coinslposy_out, &b_tgc_coinslposy_out);
   fChain->SetBranchAddress("tgc_coinslposz_out", &tgc_coinslposz_out, &b_tgc_coinslposz_out);
   fChain->SetBranchAddress("tgc_coinslroi", &tgc_coinslroi, &b_tgc_coinslroi);
   fChain->SetBranchAddress("tgc_coinslforward", &tgc_coinslforward, &b_tgc_coinslforward);
   fChain->SetBranchAddress("tgc_coinslwidthr", &tgc_coinslwidthr, &b_tgc_coinslwidthr);
   fChain->SetBranchAddress("tgc_coinslwidthphi", &tgc_coinslwidthphi, &b_tgc_coinslwidthphi);
   fChain->SetBranchAddress("tgc_coinslstationeta", &tgc_coinslstationeta, &b_tgc_coinslstationeta);
   fChain->SetBranchAddress("tgc_coinslstationphi", &tgc_coinslstationphi, &b_tgc_coinslstationphi);
   fChain->SetBranchAddress("tgc_coinslsector", &tgc_coinslsector, &b_tgc_coinslsector);
   fChain->SetBranchAddress("tgc_coinsltrackletid", &tgc_coinsltrackletid, &b_tgc_coinsltrackletid);
   fChain->SetBranchAddress("tgc_coinsltrackletidstrip", &tgc_coinsltrackletidstrip, &b_tgc_coinsltrackletidstrip);
   fChain->SetBranchAddress("tgc_nprdcoll_Prev", &tgc_nprdcoll_Prev, &b_m_nTgcColl_Prev);
   fChain->SetBranchAddress("tgc_nprd_Prev", &tgc_nprd_Prev, &b_m_nTgcPrd_Prev);
   fChain->SetBranchAddress("tgc_station_Prev", &tgc_station_Prev, &b_tgc_station_Prev);
   fChain->SetBranchAddress("tgc_eta_Prev", &tgc_eta_Prev, &b_tgc_eta_Prev);
   fChain->SetBranchAddress("tgc_phi_Prev", &tgc_phi_Prev, &b_tgc_phi_Prev);
   fChain->SetBranchAddress("tgc_gasGap_Prev", &tgc_gasGap_Prev, &b_tgc_gasGap_Prev);
   fChain->SetBranchAddress("tgc_isStrip_Prev", &tgc_isStrip_Prev, &b_tgc_isStrip_Prev);
   fChain->SetBranchAddress("tgc_channel_Prev", &tgc_channel_Prev, &b_tgc_channel_Prev);
   fChain->SetBranchAddress("tgc_globPosX_Prev", &tgc_globPosX_Prev, &b_tgc_globPosX_Prev);
   fChain->SetBranchAddress("tgc_globPosY_Prev", &tgc_globPosY_Prev, &b_tgc_globPosY_Prev);
   fChain->SetBranchAddress("tgc_globPosZ_Prev", &tgc_globPosZ_Prev, &b_tgc_globPosZ_Prev);
   fChain->SetBranchAddress("tgc_shortWidth_Prev", &tgc_shortWidth_Prev, &b_tgc_shortWidth_Prev);
   fChain->SetBranchAddress("tgc_longWidth_Prev", &tgc_longWidth_Prev, &b_tgc_longWidth_Prev);
   fChain->SetBranchAddress("tgc_length_Prev", &tgc_length_Prev, &b_tgc_length_Prev);
   fChain->SetBranchAddress("tgc_ncoincoll_Prev", &tgc_ncoincoll_Prev, &b_m_nTgcCoinColl_Prev);
   fChain->SetBranchAddress("tgc_ncointracklet_Prev", &tgc_ncointracklet_Prev, &b_m_nTgcCoinTracklet_Prev);
   fChain->SetBranchAddress("tgc_cointrackletdelta_Prev", &tgc_cointrackletdelta_Prev, &b_tgc_cointrackletdelta_Prev);
   fChain->SetBranchAddress("tgc_cointrackletposx_in_Prev", &tgc_cointrackletposx_in_Prev, &b_tgc_cointrackletposx_in_Prev);
   fChain->SetBranchAddress("tgc_cointrackletposy_in_Prev", &tgc_cointrackletposy_in_Prev, &b_tgc_cointrackletposy_in_Prev);
   fChain->SetBranchAddress("tgc_cointrackletposz_in_Prev", &tgc_cointrackletposz_in_Prev, &b_tgc_cointrackletposz_in_Prev);
   fChain->SetBranchAddress("tgc_cointrackletposx_out_Prev", &tgc_cointrackletposx_out_Prev, &b_tgc_cointrackletposx_out_Prev);
   fChain->SetBranchAddress("tgc_cointrackletposy_out_Prev", &tgc_cointrackletposy_out_Prev, &b_tgc_cointrackletposy_out_Prev);
   fChain->SetBranchAddress("tgc_cointrackletposz_out_Prev", &tgc_cointrackletposz_out_Prev, &b_tgc_cointrackletposz_out_Prev);
   fChain->SetBranchAddress("tgc_cointrackletstrip_Prev", &tgc_cointrackletstrip_Prev, &b_tgc_cointrackletstrip_Prev);
   fChain->SetBranchAddress("tgc_cointrackletforward_Prev", &tgc_cointrackletforward_Prev, &b_tgc_cointrackletforward_Prev);
   fChain->SetBranchAddress("tgc_cointrackletwidthout_Prev", &tgc_cointrackletwidthout_Prev, &b_tgc_cointrackletwidthout_Prev);
   fChain->SetBranchAddress("tgc_cointrackletwidthin_Prev", &tgc_cointrackletwidthin_Prev, &b_tgc_cointrackletwidthin_Prev);
   fChain->SetBranchAddress("tgc_cointrackletstationeta_Prev", &tgc_cointrackletstationeta_Prev, &b_tgc_cointrackletstationeta_Prev);
   fChain->SetBranchAddress("tgc_cointrackletstationphi_Prev", &tgc_cointrackletstationphi_Prev, &b_tgc_cointrackletstationphi_Prev);
   fChain->SetBranchAddress("tgc_cointrackletsector_Prev", &tgc_cointrackletsector_Prev, &b_tgc_cointrackletsector_Prev);
   fChain->SetBranchAddress("tgc_cointracklettrackletid_Prev", &tgc_cointracklettrackletid_Prev, &b_tgc_cointracklettrackletid_Prev);
   fChain->SetBranchAddress("tgc_ncoinhighpt_Prev", &tgc_ncoinhighpt_Prev, &b_m_nTgcCoinHighPt_Prev);
   fChain->SetBranchAddress("tgc_coinhighptdelta_Prev", &tgc_coinhighptdelta_Prev, &b_tgc_coinhighptdelta_Prev);
   fChain->SetBranchAddress("tgc_coinhighptposx_in_Prev", &tgc_coinhighptposx_in_Prev, &b_tgc_coinhighptposx_in_Prev);
   fChain->SetBranchAddress("tgc_coinhighptposy_in_Prev", &tgc_coinhighptposy_in_Prev, &b_tgc_coinhighptposy_in_Prev);
   fChain->SetBranchAddress("tgc_coinhighptposz_in_Prev", &tgc_coinhighptposz_in_Prev, &b_tgc_coinhighptposz_in_Prev);
   fChain->SetBranchAddress("tgc_coinhighptposx_out_Prev", &tgc_coinhighptposx_out_Prev, &b_tgc_coinhighptposx_out_Prev);
   fChain->SetBranchAddress("tgc_coinhighptposy_out_Prev", &tgc_coinhighptposy_out_Prev, &b_tgc_coinhighptposy_out_Prev);
   fChain->SetBranchAddress("tgc_coinhighptposz_out_Prev", &tgc_coinhighptposz_out_Prev, &b_tgc_coinhighptposz_out_Prev);
   fChain->SetBranchAddress("tgc_coinhighptstrip_Prev", &tgc_coinhighptstrip_Prev, &b_tgc_coinhighptstrip_Prev);
   fChain->SetBranchAddress("tgc_coinhighptforward_Prev", &tgc_coinhighptforward_Prev, &b_tgc_coinhighptforward_Prev);
   fChain->SetBranchAddress("tgc_coinhighptwidthout_Prev", &tgc_coinhighptwidthout_Prev, &b_tgc_coinhighptwidthout_Prev);
   fChain->SetBranchAddress("tgc_coinhighptwidthin_Prev", &tgc_coinhighptwidthin_Prev, &b_tgc_coinhighptwidthin_Prev);
   fChain->SetBranchAddress("tgc_coinhighptstationeta_Prev", &tgc_coinhighptstationeta_Prev, &b_tgc_coinhighptstationeta_Prev);
   fChain->SetBranchAddress("tgc_coinhighptstationphi_Prev", &tgc_coinhighptstationphi_Prev, &b_tgc_coinhighptstationphi_Prev);
   fChain->SetBranchAddress("tgc_coinhighptsector_Prev", &tgc_coinhighptsector_Prev, &b_tgc_coinhighptsector_Prev);
   fChain->SetBranchAddress("tgc_coinhighpttrackletid_Prev", &tgc_coinhighpttrackletid_Prev, &b_tgc_coinhighpttrackletid_Prev);
   fChain->SetBranchAddress("tgc_ncoinsl_Prev", &tgc_ncoinsl_Prev, &b_m_nTgcCoinSl_Prev);
   fChain->SetBranchAddress("tgc_coinslptthresh_Prev", &tgc_coinslptthresh_Prev, &b_tgc_coinslptthresh_Prev);
   fChain->SetBranchAddress("tgc_coinslposx_out_Prev", &tgc_coinslposx_out_Prev, &b_tgc_coinslposx_out_Prev);
   fChain->SetBranchAddress("tgc_coinslposy_out_Prev", &tgc_coinslposy_out_Prev, &b_tgc_coinslposy_out_Prev);
   fChain->SetBranchAddress("tgc_coinslposz_out_Prev", &tgc_coinslposz_out_Prev, &b_tgc_coinslposz_out_Prev);
   fChain->SetBranchAddress("tgc_coinslroi_Prev", &tgc_coinslroi_Prev, &b_tgc_coinslroi_Prev);
   fChain->SetBranchAddress("tgc_coinslforward_Prev", &tgc_coinslforward_Prev, &b_tgc_coinslforward_Prev);
   fChain->SetBranchAddress("tgc_coinslwidthr_Prev", &tgc_coinslwidthr_Prev, &b_tgc_coinslwidthr_Prev);
   fChain->SetBranchAddress("tgc_coinslwidthphi_Prev", &tgc_coinslwidthphi_Prev, &b_tgc_coinslwidthphi_Prev);
   fChain->SetBranchAddress("tgc_coinslstationeta_Prev", &tgc_coinslstationeta_Prev, &b_tgc_coinslstationeta_Prev);
   fChain->SetBranchAddress("tgc_coinslstationphi_Prev", &tgc_coinslstationphi_Prev, &b_tgc_coinslstationphi_Prev);
   fChain->SetBranchAddress("tgc_coinslsector_Prev", &tgc_coinslsector_Prev, &b_tgc_coinslsector_Prev);
   fChain->SetBranchAddress("tgc_coinsltrackletid_Prev", &tgc_coinsltrackletid_Prev, &b_tgc_coinsltrackletid_Prev);
   fChain->SetBranchAddress("tgc_coinsltrackletidstrip_Prev", &tgc_coinsltrackletidstrip_Prev, &b_tgc_coinsltrackletidstrip_Prev);
   fChain->SetBranchAddress("tgc_nprdcoll_Next", &tgc_nprdcoll_Next, &b_m_nTgcColl_Next);
   fChain->SetBranchAddress("tgc_nprd_Next", &tgc_nprd_Next, &b_m_nTgcPrd_Next);
   fChain->SetBranchAddress("tgc_station_Next", &tgc_station_Next, &b_tgc_station_Next);
   fChain->SetBranchAddress("tgc_eta_Next", &tgc_eta_Next, &b_tgc_eta_Next);
   fChain->SetBranchAddress("tgc_phi_Next", &tgc_phi_Next, &b_tgc_phi_Next);
   fChain->SetBranchAddress("tgc_gasGap_Next", &tgc_gasGap_Next, &b_tgc_gasGap_Next);
   fChain->SetBranchAddress("tgc_isStrip_Next", &tgc_isStrip_Next, &b_tgc_isStrip_Next);
   fChain->SetBranchAddress("tgc_channel_Next", &tgc_channel_Next, &b_tgc_channel_Next);
   fChain->SetBranchAddress("tgc_globPosX_Next", &tgc_globPosX_Next, &b_tgc_globPosX_Next);
   fChain->SetBranchAddress("tgc_globPosY_Next", &tgc_globPosY_Next, &b_tgc_globPosY_Next);
   fChain->SetBranchAddress("tgc_globPosZ_Next", &tgc_globPosZ_Next, &b_tgc_globPosZ_Next);
   fChain->SetBranchAddress("tgc_shortWidth_Next", &tgc_shortWidth_Next, &b_tgc_shortWidth_Next);
   fChain->SetBranchAddress("tgc_longWidth_Next", &tgc_longWidth_Next, &b_tgc_longWidth_Next);
   fChain->SetBranchAddress("tgc_length_Next", &tgc_length_Next, &b_tgc_length_Next);
   fChain->SetBranchAddress("tgc_ncoincoll_Next", &tgc_ncoincoll_Next, &b_m_nTgcCoinColl_Next);
   fChain->SetBranchAddress("tgc_ncointracklet_Next", &tgc_ncointracklet_Next, &b_m_nTgcCoinTracklet_Next);
   fChain->SetBranchAddress("tgc_cointrackletdelta_Next", &tgc_cointrackletdelta_Next, &b_tgc_cointrackletdelta_Next);
   fChain->SetBranchAddress("tgc_cointrackletposx_in_Next", &tgc_cointrackletposx_in_Next, &b_tgc_cointrackletposx_in_Next);
   fChain->SetBranchAddress("tgc_cointrackletposy_in_Next", &tgc_cointrackletposy_in_Next, &b_tgc_cointrackletposy_in_Next);
   fChain->SetBranchAddress("tgc_cointrackletposz_in_Next", &tgc_cointrackletposz_in_Next, &b_tgc_cointrackletposz_in_Next);
   fChain->SetBranchAddress("tgc_cointrackletposx_out_Next", &tgc_cointrackletposx_out_Next, &b_tgc_cointrackletposx_out_Next);
   fChain->SetBranchAddress("tgc_cointrackletposy_out_Next", &tgc_cointrackletposy_out_Next, &b_tgc_cointrackletposy_out_Next);
   fChain->SetBranchAddress("tgc_cointrackletposz_out_Next", &tgc_cointrackletposz_out_Next, &b_tgc_cointrackletposz_out_Next);
   fChain->SetBranchAddress("tgc_cointrackletstrip_Next", &tgc_cointrackletstrip_Next, &b_tgc_cointrackletstrip_Next);
   fChain->SetBranchAddress("tgc_cointrackletforward_Next", &tgc_cointrackletforward_Next, &b_tgc_cointrackletforward_Next);
   fChain->SetBranchAddress("tgc_cointrackletwidthout_Next", &tgc_cointrackletwidthout_Next, &b_tgc_cointrackletwidthout_Next);
   fChain->SetBranchAddress("tgc_cointrackletwidthin_Next", &tgc_cointrackletwidthin_Next, &b_tgc_cointrackletwidthin_Next);
   fChain->SetBranchAddress("tgc_cointrackletstationeta_Next", &tgc_cointrackletstationeta_Next, &b_tgc_cointrackletstationeta_Next);
   fChain->SetBranchAddress("tgc_cointrackletstationphi_Next", &tgc_cointrackletstationphi_Next, &b_tgc_cointrackletstationphi_Next);
   fChain->SetBranchAddress("tgc_cointrackletsector_Next", &tgc_cointrackletsector_Next, &b_tgc_cointrackletsector_Next);
   fChain->SetBranchAddress("tgc_cointracklettrackletid_Next", &tgc_cointracklettrackletid_Next, &b_tgc_cointracklettrackletid_Next);
   fChain->SetBranchAddress("tgc_ncoinhighpt_Next", &tgc_ncoinhighpt_Next, &b_m_nTgcCoinHighPt_Next);
   fChain->SetBranchAddress("tgc_coinhighptdelta_Next", &tgc_coinhighptdelta_Next, &b_tgc_coinhighptdelta_Next);
   fChain->SetBranchAddress("tgc_coinhighptposx_in_Next", &tgc_coinhighptposx_in_Next, &b_tgc_coinhighptposx_in_Next);
   fChain->SetBranchAddress("tgc_coinhighptposy_in_Next", &tgc_coinhighptposy_in_Next, &b_tgc_coinhighptposy_in_Next);
   fChain->SetBranchAddress("tgc_coinhighptposz_in_Next", &tgc_coinhighptposz_in_Next, &b_tgc_coinhighptposz_in_Next);
   fChain->SetBranchAddress("tgc_coinhighptposx_out_Next", &tgc_coinhighptposx_out_Next, &b_tgc_coinhighptposx_out_Next);
   fChain->SetBranchAddress("tgc_coinhighptposy_out_Next", &tgc_coinhighptposy_out_Next, &b_tgc_coinhighptposy_out_Next);
   fChain->SetBranchAddress("tgc_coinhighptposz_out_Next", &tgc_coinhighptposz_out_Next, &b_tgc_coinhighptposz_out_Next);
   fChain->SetBranchAddress("tgc_coinhighptstrip_Next", &tgc_coinhighptstrip_Next, &b_tgc_coinhighptstrip_Next);
   fChain->SetBranchAddress("tgc_coinhighptforward_Next", &tgc_coinhighptforward_Next, &b_tgc_coinhighptforward_Next);
   fChain->SetBranchAddress("tgc_coinhighptwidthout_Next", &tgc_coinhighptwidthout_Next, &b_tgc_coinhighptwidthout_Next);
   fChain->SetBranchAddress("tgc_coinhighptwidthin_Next", &tgc_coinhighptwidthin_Next, &b_tgc_coinhighptwidthin_Next);
   fChain->SetBranchAddress("tgc_coinhighptstationeta_Next", &tgc_coinhighptstationeta_Next, &b_tgc_coinhighptstationeta_Next);
   fChain->SetBranchAddress("tgc_coinhighptstationphi_Next", &tgc_coinhighptstationphi_Next, &b_tgc_coinhighptstationphi_Next);
   fChain->SetBranchAddress("tgc_coinhighptsector_Next", &tgc_coinhighptsector_Next, &b_tgc_coinhighptsector_Next);
   fChain->SetBranchAddress("tgc_coinhighpttrackletid_Next", &tgc_coinhighpttrackletid_Next, &b_tgc_coinhighpttrackletid_Next);
   fChain->SetBranchAddress("tgc_ncoinsl_Next", &tgc_ncoinsl_Next, &b_m_nTgcCoinSl_Next);
   fChain->SetBranchAddress("tgc_coinslptthresh_Next", &tgc_coinslptthresh_Next, &b_tgc_coinslptthresh_Next);
   fChain->SetBranchAddress("tgc_coinslposx_out_Next", &tgc_coinslposx_out_Next, &b_tgc_coinslposx_out_Next);
   fChain->SetBranchAddress("tgc_coinslposy_out_Next", &tgc_coinslposy_out_Next, &b_tgc_coinslposy_out_Next);
   fChain->SetBranchAddress("tgc_coinslposz_out_Next", &tgc_coinslposz_out_Next, &b_tgc_coinslposz_out_Next);
   fChain->SetBranchAddress("tgc_coinslroi_Next", &tgc_coinslroi_Next, &b_tgc_coinslroi_Next);
   fChain->SetBranchAddress("tgc_coinslforward_Next", &tgc_coinslforward_Next, &b_tgc_coinslforward_Next);
   fChain->SetBranchAddress("tgc_coinslwidthr_Next", &tgc_coinslwidthr_Next, &b_tgc_coinslwidthr_Next);
   fChain->SetBranchAddress("tgc_coinslwidthphi_Next", &tgc_coinslwidthphi_Next, &b_tgc_coinslwidthphi_Next);
   fChain->SetBranchAddress("tgc_coinslstationeta_Next", &tgc_coinslstationeta_Next, &b_tgc_coinslstationeta_Next);
   fChain->SetBranchAddress("tgc_coinslstationphi_Next", &tgc_coinslstationphi_Next, &b_tgc_coinslstationphi_Next);
   fChain->SetBranchAddress("tgc_coinslsector_Next", &tgc_coinslsector_Next, &b_tgc_coinslsector_Next);
   fChain->SetBranchAddress("tgc_coinsltrackletid_Next", &tgc_coinsltrackletid_Next, &b_tgc_coinsltrackletid_Next);
   fChain->SetBranchAddress("tgc_coinsltrackletidstrip_Next", &tgc_coinsltrackletidstrip_Next, &b_tgc_coinsltrackletidstrip_Next);
   fChain->SetBranchAddress("IS_Nsgins", &IS_Nsgins, &b_IS_Nsgins);
   fChain->SetBranchAddress("IS_Xpt", &IS_Xpt, &b_IS_Xpt);
   fChain->SetBranchAddress("IS_Ypt", &IS_Ypt, &b_IS_Ypt);
   fChain->SetBranchAddress("IS_Zpt", &IS_Zpt, &b_IS_Zpt);
   fChain->SetBranchAddress("IS_Xvec", &IS_Xvec, &b_IS_Xvec);
   fChain->SetBranchAddress("IS_Yvec", &IS_Yvec, &b_IS_Yvec);
   fChain->SetBranchAddress("IS_Zvec", &IS_Zvec, &b_IS_Zvec);
   fChain->SetBranchAddress("IS_QualityFactor", &IS_QualityFactor, &b_IS_QualityFactor);
   fChain->SetBranchAddress("IS_NbreOfMultiLayer", &IS_NbreOfMultiLayer, &b_IS_NbreOfMultiLayer);
   fChain->SetBranchAddress("IS_TrackSharing", &IS_TrackSharing, &b_IS_TrackSharing);
   fChain->SetBranchAddress("IS_StationName", &IS_StationName, &b_IS_StationName);
   fChain->SetBranchAddress("IS_Ndigits", &IS_Ndigits, &b_IS_Ndigits);
   fChain->SetBranchAddress("IS_HitPosition", &IS_HitPosition, &b_IS_HitPosition);
   fChain->SetBranchAddress("IS_MaxHits", &IS_MaxHits, &b_IS_MaxHits);
   fChain->SetBranchAddress("IS_Rdigi", &IS_Rdigi, &b_IS_Rdigi);
   fChain->SetBranchAddress("IS_Rtrack", &IS_Rtrack, &b_IS_Rtrack);
   fChain->SetBranchAddress("IS_Xdca", &IS_Xdca, &b_IS_Xdca);
   fChain->SetBranchAddress("IS_Ydca", &IS_Ydca, &b_IS_Ydca);
   fChain->SetBranchAddress("IS_Zdca", &IS_Zdca, &b_IS_Zdca);
   fChain->SetBranchAddress("IS_Sdca", &IS_Sdca, &b_IS_Sdca);
   fChain->SetBranchAddress("IS_Reso", &IS_Reso, &b_IS_Reso);
   fChain->SetBranchAddress("IS_JTYP", &IS_JTYP, &b_IS_JTYP);
   fChain->SetBranchAddress("IS_JFF", &IS_JFF, &b_IS_JFF);
   fChain->SetBranchAddress("IS_JZZ", &IS_JZZ, &b_IS_JZZ);
   fChain->SetBranchAddress("IS_JOB", &IS_JOB, &b_IS_JOB);
   fChain->SetBranchAddress("IS_JSPLI", &IS_JSPLI, &b_IS_JSPLI);
   fChain->SetBranchAddress("IS_JSL", &IS_JSL, &b_IS_JSL);
   fChain->SetBranchAddress("IS_JTUBE", &IS_JTUBE, &b_IS_JTUBE);
   fChain->SetBranchAddress("IS_JSZ", &IS_JSZ, &b_IS_JSZ);
   fChain->SetBranchAddress("IS_JSTRI", &IS_JSTRI, &b_IS_JSTRI);
   fChain->SetBranchAddress("IS_DriftTime", &IS_DriftTime, &b_IS_DriftTime);
   fChain->SetBranchAddress("IS_ChamberTech", &IS_ChamberTech, &b_IS_ChamberTech);
   fChain->SetBranchAddress("IS_StationNber", &IS_StationNber, &b_IS_StationNber);
   fChain->SetBranchAddress("IS_StationEta", &IS_StationEta, &b_IS_StationEta);
   fChain->SetBranchAddress("IS_StationPhi", &IS_StationPhi, &b_IS_StationPhi);
   fChain->SetBranchAddress("IS_Multilayer", &IS_Multilayer, &b_IS_Multilayer);
   fChain->SetBranchAddress("IS_TubeLayer", &IS_TubeLayer, &b_IS_TubeLayer);
   fChain->SetBranchAddress("IS_Tube", &IS_Tube, &b_IS_Tube);
   fChain->SetBranchAddress("IS_DoubletR", &IS_DoubletR, &b_IS_DoubletR);
   fChain->SetBranchAddress("IS_DoubletZ", &IS_DoubletZ, &b_IS_DoubletZ);
   fChain->SetBranchAddress("IS_DoubletPhi", &IS_DoubletPhi, &b_IS_DoubletPhi);
   fChain->SetBranchAddress("IS_GasGap", &IS_GasGap, &b_IS_GasGap);
   fChain->SetBranchAddress("IS_MeasuresPhi", &IS_MeasuresPhi, &b_IS_MeasuresPhi);
   fChain->SetBranchAddress("IS_Strip", &IS_Strip, &b_IS_Strip);
   fChain->SetBranchAddress("IS_IsStrip", &IS_IsStrip, &b_IS_IsStrip);
   fChain->SetBranchAddress("IS_Channel", &IS_Channel, &b_IS_Channel);
   fChain->SetBranchAddress("IS_ChamberLayer", &IS_ChamberLayer, &b_IS_ChamberLayer);
   fChain->SetBranchAddress("IS_WireLayer", &IS_WireLayer, &b_IS_WireLayer);
   fChain->SetBranchAddress("IS_RpcTime", &IS_RpcTime, &b_IS_RpcTime);
   fChain->SetBranchAddress("MB_NTrk", &MB_NTrk, &b_MB_NTrk);
   fChain->SetBranchAddress("VT_NTrk", &VT_NTrk, &b_VT_NTrk);
   fChain->SetBranchAddress("VT_Va", &VT_Va, &b_VT_Va);
   fChain->SetBranchAddress("VT_A0", &VT_A0, &b_VT_A0);
   fChain->SetBranchAddress("VT_Z", &VT_Z, &b_VT_Z);
   fChain->SetBranchAddress("VT_Phi", &VT_Phi, &b_VT_Phi);
   fChain->SetBranchAddress("VT_CotTh", &VT_CotTh, &b_VT_CotTh);
   fChain->SetBranchAddress("VT_PTInv", &VT_PTInv, &b_VT_PTInv);
   fChain->SetBranchAddress("VT_Cov11", &VT_Cov11, &b_VT_Cov11);
   fChain->SetBranchAddress("VT_Cov21", &VT_Cov21, &b_VT_Cov21);
   fChain->SetBranchAddress("VT_Cov22", &VT_Cov22, &b_VT_Cov22);
   fChain->SetBranchAddress("VT_Cov31", &VT_Cov31, &b_VT_Cov31);
   fChain->SetBranchAddress("VT_Cov32", &VT_Cov32, &b_VT_Cov32);
   fChain->SetBranchAddress("VT_Cov33", &VT_Cov33, &b_VT_Cov33);
   fChain->SetBranchAddress("VT_Cov41", &VT_Cov41, &b_VT_Cov41);
   fChain->SetBranchAddress("VT_Cov42", &VT_Cov42, &b_VT_Cov42);
   fChain->SetBranchAddress("VT_Cov43", &VT_Cov43, &b_VT_Cov43);
   fChain->SetBranchAddress("VT_Cov44", &VT_Cov44, &b_VT_Cov44);
   fChain->SetBranchAddress("VT_Cov51", &VT_Cov51, &b_VT_Cov51);
   fChain->SetBranchAddress("VT_Cov52", &VT_Cov52, &b_VT_Cov52);
   fChain->SetBranchAddress("VT_Cov53", &VT_Cov53, &b_VT_Cov53);
   fChain->SetBranchAddress("VT_Cov54", &VT_Cov54, &b_VT_Cov54);
   fChain->SetBranchAddress("VT_Cov55", &VT_Cov55, &b_VT_Cov55);
   fChain->SetBranchAddress("VT_Xpt", &VT_Xpt, &b_VT_Xpt);
   fChain->SetBranchAddress("VT_Ypt", &VT_Ypt, &b_VT_Ypt);
   fChain->SetBranchAddress("VT_Zpt", &VT_Zpt, &b_VT_Zpt);
   fChain->SetBranchAddress("VT_Xvec", &VT_Xvec, &b_VT_Xvec);
   fChain->SetBranchAddress("VT_Yvec", &VT_Yvec, &b_VT_Yvec);
   fChain->SetBranchAddress("VT_Zvec", &VT_Zvec, &b_VT_Zvec);
   fChain->SetBranchAddress("VT_Mom", &VT_Mom, &b_VT_Mom);
   fChain->SetBranchAddress("VT_digits", &VT_digits, &b_VT_digits);
   fChain->SetBranchAddress("VT_HitPosition", &VT_HitPosition, &b_VT_HitPosition);
   fChain->SetBranchAddress("VT_TrHi_hits", &VT_TrHi_hits, &b_VT_TrHi_hits);
   fChain->SetBranchAddress("VT_TrHi_Rdigi", &VT_TrHi_Rdigi, &b_VT_TrHi_Rdigi);
   fChain->SetBranchAddress("VT_TrHi_Rtrack", &VT_TrHi_Rtrack, &b_VT_TrHi_Rtrack);
   fChain->SetBranchAddress("VT_TrHi_Xdca", &VT_TrHi_Xdca, &b_VT_TrHi_Xdca);
   fChain->SetBranchAddress("VT_TrHi_Ydca", &VT_TrHi_Ydca, &b_VT_TrHi_Ydca);
   fChain->SetBranchAddress("VT_TrHi_Zdca", &VT_TrHi_Zdca, &b_VT_TrHi_Zdca);
   fChain->SetBranchAddress("VT_TrHi_Sdca", &VT_TrHi_Sdca, &b_VT_TrHi_Sdca);
   fChain->SetBranchAddress("VT_TrHi_Reso", &VT_TrHi_Reso, &b_VT_TrHi_Reso);
   fChain->SetBranchAddress("VT_TrHi_RZSsim", &VT_TrHi_RZSsim, &b_VT_TrHi_RZSsim);
   fChain->SetBranchAddress("VT_TrHi_EZSfit", &VT_TrHi_EZSfit, &b_VT_TrHi_EZSfit);
   fChain->SetBranchAddress("VT_TrHi_JTYP", &VT_TrHi_JTYP, &b_VT_TrHi_JTYP);
   fChain->SetBranchAddress("VT_TrHi_JFF", &VT_TrHi_JFF, &b_VT_TrHi_JFF);
   fChain->SetBranchAddress("VT_TrHi_JZZ", &VT_TrHi_JZZ, &b_VT_TrHi_JZZ);
   fChain->SetBranchAddress("VT_TrHi_JOB", &VT_TrHi_JOB, &b_VT_TrHi_JOB);
   fChain->SetBranchAddress("VT_TrHi_JSPLI", &VT_TrHi_JSPLI, &b_VT_TrHi_JSPLI);
   fChain->SetBranchAddress("VT_TrHi_JSL", &VT_TrHi_JSL, &b_VT_TrHi_JSL);
   fChain->SetBranchAddress("VT_TrHi_JTUBE", &VT_TrHi_JTUBE, &b_VT_TrHi_JTUBE);
   fChain->SetBranchAddress("VT_TrHi_JSZ", &VT_TrHi_JSZ, &b_VT_TrHi_JSZ);
   fChain->SetBranchAddress("VT_TrHi_JSTRI", &VT_TrHi_JSTRI, &b_VT_TrHi_JSTRI);
   fChain->SetBranchAddress("VT_TrHi_DriftTime", &VT_TrHi_DriftTime, &b_VT_TrHi_DriftTime);
   fChain->SetBranchAddress("VT_TrHi_ChamberTech", &VT_TrHi_ChamberTech, &b_VT_TrHi_ChamberTech);
   fChain->SetBranchAddress("VT_TrHi_StationNber", &VT_TrHi_StationNber, &b_VT_TrHi_StationNber);
   fChain->SetBranchAddress("VT_TrHi_StationEta", &VT_TrHi_StationEta, &b_VT_TrHi_StationEta);
   fChain->SetBranchAddress("VT_TrHi_StationPhi", &VT_TrHi_StationPhi, &b_VT_TrHi_StationPhi);
   fChain->SetBranchAddress("VT_TrHi_Multilayer", &VT_TrHi_Multilayer, &b_VT_TrHi_Multilayer);
   fChain->SetBranchAddress("VT_TrHi_TubeLayer", &VT_TrHi_TubeLayer, &b_VT_TrHi_TubeLayer);
   fChain->SetBranchAddress("VT_TrHi_Tube", &VT_TrHi_Tube, &b_VT_TrHi_Tube);
   fChain->SetBranchAddress("VT_TrHi_DoubletR", &VT_TrHi_DoubletR, &b_VT_TrHi_DoubletR);
   fChain->SetBranchAddress("VT_TrHi_DoubletZ", &VT_TrHi_DoubletZ, &b_VT_TrHi_DoubletZ);
   fChain->SetBranchAddress("VT_TrHi_DoubletPhi", &VT_TrHi_DoubletPhi, &b_VT_TrHi_DoubletPhi);
   fChain->SetBranchAddress("VT_TrHi_GasGap", &VT_TrHi_GasGap, &b_VT_TrHi_GasGap);
   fChain->SetBranchAddress("VT_TrHi_MeasuresPhi", &VT_TrHi_MeasuresPhi, &b_VT_TrHi_MeasuresPhi);
   fChain->SetBranchAddress("VT_TrHi_Strip", &VT_TrHi_Strip, &b_VT_TrHi_Strip);
   fChain->SetBranchAddress("VT_TrHi_IsStrip", &VT_TrHi_IsStrip, &b_VT_TrHi_IsStrip);
   fChain->SetBranchAddress("VT_TrHi_Channel", &VT_TrHi_Channel, &b_VT_TrHi_Channel);
   fChain->SetBranchAddress("VT_TrHi_ChamberLayer", &VT_TrHi_ChamberLayer, &b_VT_TrHi_ChamberLayer);
   fChain->SetBranchAddress("VT_TrHi_WireLayer", &VT_TrHi_WireLayer, &b_VT_TrHi_WireLayer);
   fChain->SetBranchAddress("VT_TrHi_RpcTime", &VT_TrHi_RpcTime, &b_VT_TrHi_RpcTime);
   fChain->SetBranchAddress("KE_NTrk", &KE_NTrk, &b_KE_NTrk);
   fChain->SetBranchAddress("KE_Va", &KE_Va, &b_KE_Va);
   fChain->SetBranchAddress("KE_Thept", &KE_Thept, &b_KE_Thept);
   fChain->SetBranchAddress("KE_Phipt", &KE_Phipt, &b_KE_Phipt);
   fChain->SetBranchAddress("KE_Thevc", &KE_Thevc, &b_KE_Thevc);
   fChain->SetBranchAddress("KE_Phivc", &KE_Phivc, &b_KE_Phivc);
   fChain->SetBranchAddress("KE_PInv", &KE_PInv, &b_KE_PInv);
   fChain->SetBranchAddress("KE_Cov11", &KE_Cov11, &b_KE_Cov11);
   fChain->SetBranchAddress("KE_Cov21", &KE_Cov21, &b_KE_Cov21);
   fChain->SetBranchAddress("KE_Cov22", &KE_Cov22, &b_KE_Cov22);
   fChain->SetBranchAddress("KE_Cov31", &KE_Cov31, &b_KE_Cov31);
   fChain->SetBranchAddress("KE_Cov32", &KE_Cov32, &b_KE_Cov32);
   fChain->SetBranchAddress("KE_Cov33", &KE_Cov33, &b_KE_Cov33);
   fChain->SetBranchAddress("KE_Cov41", &KE_Cov41, &b_KE_Cov41);
   fChain->SetBranchAddress("KE_Cov42", &KE_Cov42, &b_KE_Cov42);
   fChain->SetBranchAddress("KE_Cov43", &KE_Cov43, &b_KE_Cov43);
   fChain->SetBranchAddress("KE_Cov44", &KE_Cov44, &b_KE_Cov44);
   fChain->SetBranchAddress("KE_Cov51", &KE_Cov51, &b_KE_Cov51);
   fChain->SetBranchAddress("KE_Cov52", &KE_Cov52, &b_KE_Cov52);
   fChain->SetBranchAddress("KE_Cov53", &KE_Cov53, &b_KE_Cov53);
   fChain->SetBranchAddress("KE_Cov54", &KE_Cov54, &b_KE_Cov54);
   fChain->SetBranchAddress("KE_Cov55", &KE_Cov55, &b_KE_Cov55);
   fChain->SetBranchAddress("KE_Xpt", &KE_Xpt, &b_KE_Xpt);
   fChain->SetBranchAddress("KE_Ypt", &KE_Ypt, &b_KE_Ypt);
   fChain->SetBranchAddress("KE_Zpt", &KE_Zpt, &b_KE_Zpt);
   fChain->SetBranchAddress("KE_Xvec", &KE_Xvec, &b_KE_Xvec);
   fChain->SetBranchAddress("KE_Yvec", &KE_Yvec, &b_KE_Yvec);
   fChain->SetBranchAddress("KE_Zvec", &KE_Zvec, &b_KE_Zvec);
   fChain->SetBranchAddress("KE_Mom", &KE_Mom, &b_KE_Mom);
   fChain->SetBranchAddress("KE_ZCyl", &KE_ZCyl, &b_KE_ZCyl);
   fChain->SetBranchAddress("KE_RCyl", &KE_RCyl, &b_KE_RCyl);
   fChain->SetBranchAddress("MS_NTrk", &MS_NTrk, &b_MS_NTrk);
   fChain->SetBranchAddress("MS_Va", &MS_Va, &b_MS_Va);
   fChain->SetBranchAddress("MS_Thept", &MS_Thept, &b_MS_Thept);
   fChain->SetBranchAddress("MS_Phipt", &MS_Phipt, &b_MS_Phipt);
   fChain->SetBranchAddress("MS_Thevc", &MS_Thevc, &b_MS_Thevc);
   fChain->SetBranchAddress("MS_Phivc", &MS_Phivc, &b_MS_Phivc);
   fChain->SetBranchAddress("MS_PInv", &MS_PInv, &b_MS_PInv);
   fChain->SetBranchAddress("MS_Cov11", &MS_Cov11, &b_MS_Cov11);
   fChain->SetBranchAddress("MS_Cov21", &MS_Cov21, &b_MS_Cov21);
   fChain->SetBranchAddress("MS_Cov22", &MS_Cov22, &b_MS_Cov22);
   fChain->SetBranchAddress("MS_Cov31", &MS_Cov31, &b_MS_Cov31);
   fChain->SetBranchAddress("MS_Cov32", &MS_Cov32, &b_MS_Cov32);
   fChain->SetBranchAddress("MS_Cov33", &MS_Cov33, &b_MS_Cov33);
   fChain->SetBranchAddress("MS_Cov41", &MS_Cov41, &b_MS_Cov41);
   fChain->SetBranchAddress("MS_Cov42", &MS_Cov42, &b_MS_Cov42);
   fChain->SetBranchAddress("MS_Cov43", &MS_Cov43, &b_MS_Cov43);
   fChain->SetBranchAddress("MS_Cov44", &MS_Cov44, &b_MS_Cov44);
   fChain->SetBranchAddress("MS_Cov51", &MS_Cov51, &b_MS_Cov51);
   fChain->SetBranchAddress("MS_Cov52", &MS_Cov52, &b_MS_Cov52);
   fChain->SetBranchAddress("MS_Cov53", &MS_Cov53, &b_MS_Cov53);
   fChain->SetBranchAddress("MS_Cov54", &MS_Cov54, &b_MS_Cov54);
   fChain->SetBranchAddress("MS_Cov55", &MS_Cov55, &b_MS_Cov55);
   fChain->SetBranchAddress("MS_Xpt", &MS_Xpt, &b_MS_Xpt);
   fChain->SetBranchAddress("MS_Ypt", &MS_Ypt, &b_MS_Ypt);
   fChain->SetBranchAddress("MS_Zpt", &MS_Zpt, &b_MS_Zpt);
   fChain->SetBranchAddress("MS_Xvec", &MS_Xvec, &b_MS_Xvec);
   fChain->SetBranchAddress("MS_Yvec", &MS_Yvec, &b_MS_Yvec);
   fChain->SetBranchAddress("MS_Zvec", &MS_Zvec, &b_MS_Zvec);
   fChain->SetBranchAddress("MS_Mom", &MS_Mom, &b_MS_Mom);
   fChain->SetBranchAddress("MS_ZCyl", &MS_ZCyl, &b_MS_ZCyl);
   fChain->SetBranchAddress("MS_RCyl", &MS_RCyl, &b_MS_RCyl);
   fChain->SetBranchAddress("MS_Chican", &MS_Chican, &b_MS_Chican);
   fChain->SetBranchAddress("MS_Chifit", &MS_Chifit, &b_MS_Chifit);
   fChain->SetBranchAddress("MS_Chiver", &MS_Chiver, &b_MS_Chiver);
   fChain->SetBranchAddress("MS_Chistat", &MS_Chistat, &b_MS_Chistat);
   fChain->SetBranchAddress("MS_Ndof", &MS_Ndof, &b_MS_Ndof);
   fChain->SetBranchAddress("Moore_nmuon", &Moore_nmuon, &b_Moore_nmuon);
   fChain->SetBranchAddress("Moore_phih", &Moore_phih, &b_Moore_phih);
   fChain->SetBranchAddress("Moore_etah", &Moore_etah, &b_Moore_etah);
   fChain->SetBranchAddress("Moore_mdth", &Moore_mdth, &b_Moore_mdth);
   fChain->SetBranchAddress("Moore_cscetah", &Moore_cscetah, &b_Moore_cscetah);
   fChain->SetBranchAddress("Moore_cscphih", &Moore_cscphih, &b_Moore_cscphih);
   fChain->SetBranchAddress("Moore_rpcetah", &Moore_rpcetah, &b_Moore_rpcetah);
   fChain->SetBranchAddress("Moore_rpcphih", &Moore_rpcphih, &b_Moore_rpcphih);
   fChain->SetBranchAddress("Moore_tgcetah", &Moore_tgcetah, &b_Moore_tgcetah);
   fChain->SetBranchAddress("Moore_tgcphih", &Moore_tgcphih, &b_Moore_tgcphih);
   fChain->SetBranchAddress("Moore_stati", &Moore_stati, &b_Moore_stati);
   fChain->SetBranchAddress("Moore_statr", &Moore_statr, &b_Moore_statr);
   fChain->SetBranchAddress("Moore_xvtxr", &Moore_xvtxr, &b_Moore_xvtxr);
   fChain->SetBranchAddress("Moore_yvtxr", &Moore_yvtxr, &b_Moore_yvtxr);
   fChain->SetBranchAddress("Moore_zvtxr", &Moore_zvtxr, &b_Moore_zvtxr);
   fChain->SetBranchAddress("Moore_a0r", &Moore_a0r, &b_Moore_a0r);
   fChain->SetBranchAddress("Moore_z0r", &Moore_z0r, &b_Moore_z0r);
   fChain->SetBranchAddress("Moore_phir", &Moore_phir, &b_Moore_phir);
   fChain->SetBranchAddress("Moore_thetar", &Moore_thetar, &b_Moore_thetar);
   fChain->SetBranchAddress("Moore_qpir", &Moore_qpir, &b_Moore_qpir);
   fChain->SetBranchAddress("Moore_etar", &Moore_etar, &b_Moore_etar);
   fChain->SetBranchAddress("Moore_chi2", &Moore_chi2, &b_Moore_chi2);
   fChain->SetBranchAddress("Moore_chi2pr", &Moore_chi2pr, &b_Moore_chi2pr);
   fChain->SetBranchAddress("Moore_origx", &Moore_origx, &b_Moore_origx);
   fChain->SetBranchAddress("Moore_origy", &Moore_origy, &b_Moore_origy);
   fChain->SetBranchAddress("Moore_origz", &Moore_origz, &b_Moore_origz);
   fChain->SetBranchAddress("Moore_covr11", &Moore_covr11, &b_Moore_covr11);
   fChain->SetBranchAddress("Moore_covr12", &Moore_covr12, &b_Moore_covr12);
   fChain->SetBranchAddress("Moore_covr22", &Moore_covr22, &b_Moore_covr22);
   fChain->SetBranchAddress("Moore_covr13", &Moore_covr13, &b_Moore_covr13);
   fChain->SetBranchAddress("Moore_covr23", &Moore_covr23, &b_Moore_covr23);
   fChain->SetBranchAddress("Moore_covr33", &Moore_covr33, &b_Moore_covr33);
   fChain->SetBranchAddress("Moore_covr14", &Moore_covr14, &b_Moore_covr14);
   fChain->SetBranchAddress("Moore_covr24", &Moore_covr24, &b_Moore_covr24);
   fChain->SetBranchAddress("Moore_covr34", &Moore_covr34, &b_Moore_covr34);
   fChain->SetBranchAddress("Moore_covr44", &Moore_covr44, &b_Moore_covr44);
   fChain->SetBranchAddress("Moore_covr15", &Moore_covr15, &b_Moore_covr15);
   fChain->SetBranchAddress("Moore_covr25", &Moore_covr25, &b_Moore_covr25);
   fChain->SetBranchAddress("Moore_covr35", &Moore_covr35, &b_Moore_covr35);
   fChain->SetBranchAddress("Moore_covr45", &Moore_covr45, &b_Moore_covr45);
   fChain->SetBranchAddress("Moore_covr55", &Moore_covr55, &b_Moore_covr55);
   fChain->SetBranchAddress("MooreSegments_nseg", &MooreSegments_nseg, &b_MooreSegments_nseg);
   fChain->SetBranchAddress("MooreSegments_ml", &MooreSegments_ml, &b_MooreSegments_ml);
   fChain->SetBranchAddress("MooreSegments_nhml1", &MooreSegments_nhml1, &b_MooreSegments_nhml1);
   fChain->SetBranchAddress("MooreSegments_nhml2", &MooreSegments_nhml2, &b_MooreSegments_nhml2);
   fChain->SetBranchAddress("MooreSegments_nmlyr", &MooreSegments_nmlyr, &b_MooreSegments_nmlyr);
   fChain->SetBranchAddress("MooreSegments_nhit", &MooreSegments_nhit, &b_MooreSegments_nhit);
   fChain->SetBranchAddress("MooreSegments_nhcsc", &MooreSegments_nhcsc, &b_MooreSegments_nhcsc);
   fChain->SetBranchAddress("MooreSegments_nhmdt", &MooreSegments_nhmdt, &b_MooreSegments_nhmdt);
   fChain->SetBranchAddress("MooreSegments_nhrpc", &MooreSegments_nhrpc, &b_MooreSegments_nhrpc);
   fChain->SetBranchAddress("MooreSegments_nhtgc", &MooreSegments_nhtgc, &b_MooreSegments_nhtgc);
   fChain->SetBranchAddress("MooreSegments_n_tottubes_seg", &MooreSegments_n_tottubes_seg, &b_MooreSegments_n_tottubes_seg);
   fChain->SetBranchAddress("MooreSegments_n_hittubes_seg", &MooreSegments_n_hittubes_seg, &b_MooreSegments_n_hittubes_seg);
   fChain->SetBranchAddress("MooreSegments_hittype", &MooreSegments_hittype, &b_MooreSegments_hittype);
   fChain->SetBranchAddress("MooreSegments_prdadc", &MooreSegments_prdadc, &b_MooreSegments_prdadc);
   fChain->SetBranchAddress("MooreSegments_prdtdc", &MooreSegments_prdtdc, &b_MooreSegments_prdtdc);
   fChain->SetBranchAddress("MooreSegments_z", &MooreSegments_z, &b_MooreSegments_z);
   fChain->SetBranchAddress("MooreSegments_rho", &MooreSegments_rho, &b_MooreSegments_rho);
   fChain->SetBranchAddress("MooreSegments_phi", &MooreSegments_phi, &b_MooreSegments_phi);
   fChain->SetBranchAddress("MooreSegments_theta", &MooreSegments_theta, &b_MooreSegments_theta);
   fChain->SetBranchAddress("MooreSegments_cotth", &MooreSegments_cotth, &b_MooreSegments_cotth);
   fChain->SetBranchAddress("MooreSegments_dtheta", &MooreSegments_dtheta, &b_MooreSegments_dtheta);
   fChain->SetBranchAddress("MooreSegments_chi2", &MooreSegments_chi2, &b_MooreSegments_chi2);
   fChain->SetBranchAddress("MooreSegments_ndof", &MooreSegments_ndof, &b_MooreSegments_ndof);
   fChain->SetBranchAddress("MooreSegments_rInt", &MooreSegments_rInt, &b_MooreSegments_rInt);
   fChain->SetBranchAddress("MooreSegments_LocR", &MooreSegments_LocR, &b_MooreSegments_LocR);
   fChain->SetBranchAddress("MooreSegments_driftTime", &MooreSegments_driftTime, &b_MooreSegments_driftTime);
   fChain->SetBranchAddress("jetNumCone4H1TowerJets", &jetNumCone4H1TowerJets, &b_Cone4H1TowerJetsjetNum);
   fChain->SetBranchAddress("jetEtaCone4H1TowerJets", &jetEtaCone4H1TowerJets, &b_jetEtaCone4H1TowerJets);
   fChain->SetBranchAddress("jetPhiCone4H1TowerJets", &jetPhiCone4H1TowerJets, &b_jetPhiCone4H1TowerJets);
   fChain->SetBranchAddress("jetECone4H1TowerJets", &jetECone4H1TowerJets, &b_jetECone4H1TowerJets);
   fChain->SetBranchAddress("jetEtCone4H1TowerJets", &jetEtCone4H1TowerJets, &b_jetEtCone4H1TowerJets);
   fChain->SetBranchAddress("jetMCone4H1TowerJets", &jetMCone4H1TowerJets, &b_jetMCone4H1TowerJets);
   fChain->SetBranchAddress("jetPxCone4H1TowerJets", &jetPxCone4H1TowerJets, &b_jetPxCone4H1TowerJets);
   fChain->SetBranchAddress("jetPyCone4H1TowerJets", &jetPyCone4H1TowerJets, &b_jetPyCone4H1TowerJets);
   fChain->SetBranchAddress("jetPzCone4H1TowerJets", &jetPzCone4H1TowerJets, &b_jetPzCone4H1TowerJets);
   fChain->SetBranchAddress("jetSizeCone4H1TowerJets", &jetSizeCone4H1TowerJets, &b_jetSizeCone4H1TowerJets);
   fChain->SetBranchAddress("jetEmfCone4H1TowerJets", &jetEmfCone4H1TowerJets, &b_jetEmfCone4H1TowerJets);
   fChain->SetBranchAddress("CaloMu_ntrack", &CaloMu_ntrack, &b_CaloMu_ntrack);
   fChain->SetBranchAddress("CaloMu_trkPdgid", &CaloMu_trkPdgid, &b_CaloMu_trkPdgid);
   fChain->SetBranchAddress("CaloMu_trkMother", &CaloMu_trkMother, &b_CaloMu_trkMother);
   fChain->SetBranchAddress("CaloMu_trkEta", &CaloMu_trkEta, &b_CaloMu_trkEta);
   fChain->SetBranchAddress("CaloMu_trkPhi", &CaloMu_trkPhi, &b_CaloMu_trkPhi);
   fChain->SetBranchAddress("CaloMu_trkPt", &CaloMu_trkPt, &b_CaloMu_trkPt);
   fChain->SetBranchAddress("CaloMu_trkD0", &CaloMu_trkD0, &b_CaloMu_trkD0);
   fChain->SetBranchAddress("CaloMu_trkIP", &CaloMu_trkIP, &b_CaloMu_trkIP);
   fChain->SetBranchAddress("CaloMu_trkBLayerHits", &CaloMu_trkBLayerHits, &b_CaloMu_trkBLayerHits);
   fChain->SetBranchAddress("CaloMu_trkPixelHits", &CaloMu_trkPixelHits, &b_CaloMu_trkPixelHits);
   fChain->SetBranchAddress("CaloMu_trkSCTHits", &CaloMu_trkSCTHits, &b_CaloMu_trkSCTHits);
   fChain->SetBranchAddress("CaloMu_trkTRTHits", &CaloMu_trkTRTHits, &b_CaloMu_trkTRTHits);
   fChain->SetBranchAddress("CaloMu_nmuon", &CaloMu_nmuon, &b_CaloMu_nmuon);
   fChain->SetBranchAddress("CaloMu_pdgid", &CaloMu_pdgid, &b_CaloMu_pdgid);
   fChain->SetBranchAddress("CaloMu_mother", &CaloMu_mother, &b_CaloMu_mother);
   fChain->SetBranchAddress("CaloMu_tag", &CaloMu_tag, &b_CaloMu_tag);
   fChain->SetBranchAddress("CaloMu_lhr", &CaloMu_lhr, &b_CaloMu_lhr);
   fChain->SetBranchAddress("CaloMu_etCone", &CaloMu_etCone, &b_CaloMu_etCone);
   fChain->SetBranchAddress("CaloMu_ptCone", &CaloMu_ptCone, &b_CaloMu_ptCone);
   fChain->SetBranchAddress("CaloMu_eta", &CaloMu_eta, &b_CaloMu_eta);
   fChain->SetBranchAddress("CaloMu_phi", &CaloMu_phi, &b_CaloMu_phi);
   fChain->SetBranchAddress("CaloMu_pt", &CaloMu_pt, &b_CaloMu_pt);
   fChain->SetBranchAddress("CaloMu_qoverp", &CaloMu_qoverp, &b_CaloMu_qoverp);
   fChain->SetBranchAddress("CaloMu_IP", &CaloMu_IP, &b_CaloMu_IP);
   fChain->SetBranchAddress("CaloMu_d0", &CaloMu_d0, &b_CaloMu_d0);
   fChain->SetBranchAddress("CaloMu_bLayerHits", &CaloMu_bLayerHits, &b_CaloMu_bLayerHits);
   fChain->SetBranchAddress("CaloMu_pixelHits", &CaloMu_pixelHits, &b_CaloMu_pixelHits);
   fChain->SetBranchAddress("CaloMu_SCTHits", &CaloMu_SCTHits, &b_CaloMu_SCTHits);
   fChain->SetBranchAddress("CaloMu_TRTHits", &CaloMu_TRTHits, &b_CaloMu_TRTHits);
   fChain->SetBranchAddress("CaloMu_sample", &CaloMu_sample, &b_CaloMu_sample);
   fChain->SetBranchAddress("CaloMu_energy", &CaloMu_energy, &b_CaloMu_energy);
   fChain->SetBranchAddress("CaloMu_energyLoss", &CaloMu_energyLoss, &b_CaloMu_energyLoss);
   fChain->SetBranchAddress("CaloMu2_ntrack", &CaloMu2_ntrack, &b_CaloMu2_ntrack);
   fChain->SetBranchAddress("CaloMu2_trkPdgid", &CaloMu2_trkPdgid, &b_CaloMu2_trkPdgid);
   fChain->SetBranchAddress("CaloMu2_trkMother", &CaloMu2_trkMother, &b_CaloMu2_trkMother);
   fChain->SetBranchAddress("CaloMu2_trkEta", &CaloMu2_trkEta, &b_CaloMu2_trkEta);
   fChain->SetBranchAddress("CaloMu2_trkPhi", &CaloMu2_trkPhi, &b_CaloMu2_trkPhi);
   fChain->SetBranchAddress("CaloMu2_trkPt", &CaloMu2_trkPt, &b_CaloMu2_trkPt);
   fChain->SetBranchAddress("CaloMu2_trkD0", &CaloMu2_trkD0, &b_CaloMu2_trkD0);
   fChain->SetBranchAddress("CaloMu2_trkIP", &CaloMu2_trkIP, &b_CaloMu2_trkIP);
   fChain->SetBranchAddress("CaloMu2_trkBLayerHits", &CaloMu2_trkBLayerHits, &b_CaloMu2_trkBLayerHits);
   fChain->SetBranchAddress("CaloMu2_trkPixelHits", &CaloMu2_trkPixelHits, &b_CaloMu2_trkPixelHits);
   fChain->SetBranchAddress("CaloMu2_trkSCTHits", &CaloMu2_trkSCTHits, &b_CaloMu2_trkSCTHits);
   fChain->SetBranchAddress("CaloMu2_trkTRTHits", &CaloMu2_trkTRTHits, &b_CaloMu2_trkTRTHits);
   fChain->SetBranchAddress("CaloMu2_nmuon", &CaloMu2_nmuon, &b_CaloMu2_nmuon);
   fChain->SetBranchAddress("CaloMu2_pdgid", &CaloMu2_pdgid, &b_CaloMu2_pdgid);
   fChain->SetBranchAddress("CaloMu2_mother", &CaloMu2_mother, &b_CaloMu2_mother);
   fChain->SetBranchAddress("CaloMu2_tag", &CaloMu2_tag, &b_CaloMu2_tag);
   fChain->SetBranchAddress("CaloMu2_lhr", &CaloMu2_lhr, &b_CaloMu2_lhr);
   fChain->SetBranchAddress("CaloMu2_etCone", &CaloMu2_etCone, &b_CaloMu2_etCone);
   fChain->SetBranchAddress("CaloMu2_ptCone", &CaloMu2_ptCone, &b_CaloMu2_ptCone);
   fChain->SetBranchAddress("CaloMu2_eta", &CaloMu2_eta, &b_CaloMu2_eta);
   fChain->SetBranchAddress("CaloMu2_phi", &CaloMu2_phi, &b_CaloMu2_phi);
   fChain->SetBranchAddress("CaloMu2_pt", &CaloMu2_pt, &b_CaloMu2_pt);
   fChain->SetBranchAddress("CaloMu2_qoverp", &CaloMu2_qoverp, &b_CaloMu2_qoverp);
   fChain->SetBranchAddress("CaloMu2_IP", &CaloMu2_IP, &b_CaloMu2_IP);
   fChain->SetBranchAddress("CaloMu2_d0", &CaloMu2_d0, &b_CaloMu2_d0);
   fChain->SetBranchAddress("CaloMu2_bLayerHits", &CaloMu2_bLayerHits, &b_CaloMu2_bLayerHits);
   fChain->SetBranchAddress("CaloMu2_pixelHits", &CaloMu2_pixelHits, &b_CaloMu2_pixelHits);
   fChain->SetBranchAddress("CaloMu2_SCTHits", &CaloMu2_SCTHits, &b_CaloMu2_SCTHits);
   fChain->SetBranchAddress("CaloMu2_TRTHits", &CaloMu2_TRTHits, &b_CaloMu2_TRTHits);
   fChain->SetBranchAddress("CaloMu2_sample", &CaloMu2_sample, &b_CaloMu2_sample);
   fChain->SetBranchAddress("CaloMu2_energy", &CaloMu2_energy, &b_CaloMu2_energy);
   fChain->SetBranchAddress("CaloMu2_energyLoss", &CaloMu2_energyLoss, &b_CaloMu2_energyLoss);
   fChain->SetBranchAddress("trk_nTracksComb", &trk_nTracksComb, &b_trk_nTracksComb);
   fChain->SetBranchAddress("trk_nPixelHitsComb", &trk_nPixelHitsComb, &b_trk_nPixelHitsComb);
   fChain->SetBranchAddress("trk_nSctHitsComb", &trk_nSctHitsComb, &b_trk_nSctHitsComb);
   fChain->SetBranchAddress("trk_nTrtHitsComb", &trk_nTrtHitsComb, &b_trk_nTrtHitsComb);
   fChain->SetBranchAddress("trk_PixResPhiComb", &trk_PixResPhiComb, &b_trk_PixResPhiComb);
   fChain->SetBranchAddress("trk_PixResEtaComb", &trk_PixResEtaComb, &b_trk_PixResEtaComb);
   fChain->SetBranchAddress("trk_PixPullPhiComb", &trk_PixPullPhiComb, &b_trk_PixPullPhiComb);
   fChain->SetBranchAddress("trk_PixPullEtaComb", &trk_PixPullEtaComb, &b_trk_PixPullEtaComb);
   fChain->SetBranchAddress("trk_PixErrTrkPhiComb", &trk_PixErrTrkPhiComb, &b_trk_PixErrTrkPhiComb);
   fChain->SetBranchAddress("trk_PixErrTrkEtaComb", &trk_PixErrTrkEtaComb, &b_trk_PixErrTrkEtaComb);
   fChain->SetBranchAddress("trk_PixErrHitPhiComb", &trk_PixErrHitPhiComb, &b_trk_PixErrHitPhiComb);
   fChain->SetBranchAddress("trk_PixErrHitEtaComb", &trk_PixErrHitEtaComb, &b_trk_PixErrHitEtaComb);
   fChain->SetBranchAddress("trk_Pix_becComb", &trk_Pix_becComb, &b_trk_Pix_becComb);
   fChain->SetBranchAddress("trk_Pix_layerComb", &trk_Pix_layerComb, &b_trk_Pix_layerComb);
   fChain->SetBranchAddress("trk_Pix_etaComb", &trk_Pix_etaComb, &b_trk_Pix_etaComb);
   fChain->SetBranchAddress("trk_Pix_phiComb", &trk_Pix_phiComb, &b_trk_Pix_phiComb);
   fChain->SetBranchAddress("trk_Pix_clusWidthRowComb", &trk_Pix_clusWidthRowComb, &b_trk_Pix_clusWidthRowComb);
   fChain->SetBranchAddress("trk_Pix_clusWidthColComb", &trk_Pix_clusWidthColComb, &b_trk_Pix_clusWidthColComb);
   fChain->SetBranchAddress("trk_Pix_LocXComb", &trk_Pix_LocXComb, &b_trk_Pix_LocXComb);
   fChain->SetBranchAddress("trk_Pix_LocYComb", &trk_Pix_LocYComb, &b_trk_Pix_LocYComb);
   fChain->SetBranchAddress("trk_SctResComb", &trk_SctResComb, &b_trk_SctResComb);
   fChain->SetBranchAddress("trk_SctPullComb", &trk_SctPullComb, &b_trk_SctPullComb);
   fChain->SetBranchAddress("trk_SctErrTrkComb", &trk_SctErrTrkComb, &b_trk_SctErrTrkComb);
   fChain->SetBranchAddress("trk_SctErrHitComb", &trk_SctErrHitComb, &b_trk_SctErrHitComb);
   fChain->SetBranchAddress("trk_Sct_becComb", &trk_Sct_becComb, &b_trk_Sct_becComb);
   fChain->SetBranchAddress("trk_Sct_layerComb", &trk_Sct_layerComb, &b_trk_Sct_layerComb);
   fChain->SetBranchAddress("trk_Sct_etaComb", &trk_Sct_etaComb, &b_trk_Sct_etaComb);
   fChain->SetBranchAddress("trk_Sct_phiComb", &trk_Sct_phiComb, &b_trk_Sct_phiComb);
   fChain->SetBranchAddress("trk_Sct_sideComb", &trk_Sct_sideComb, &b_trk_Sct_sideComb);
   fChain->SetBranchAddress("trk_Sct_rdoIdComb", &trk_Sct_rdoIdComb, &b_trk_Sct_rdoIdComb);
   fChain->SetBranchAddress("trk_Sct_clusGroupsizeComb", &trk_Sct_clusGroupsizeComb, &b_trk_Sct_clusGroupsizeComb);
   fChain->SetBranchAddress("trk_Sct_clusxComb", &trk_Sct_clusxComb, &b_trk_Sct_clusxComb);
   fChain->SetBranchAddress("trk_Sct_clusyComb", &trk_Sct_clusyComb, &b_trk_Sct_clusyComb);
   fChain->SetBranchAddress("trk_Sct_cluszComb", &trk_Sct_cluszComb, &b_trk_Sct_cluszComb);
   fChain->SetBranchAddress("trk_TrtResComb", &trk_TrtResComb, &b_trk_TrtResComb);
   fChain->SetBranchAddress("trk_TrtPullComb", &trk_TrtPullComb, &b_trk_TrtPullComb);
   fChain->SetBranchAddress("trk_TrtErrTrkComb", &trk_TrtErrTrkComb, &b_trk_TrtErrTrkComb);
   fChain->SetBranchAddress("trk_TrtErrHitComb", &trk_TrtErrHitComb, &b_trk_TrtErrHitComb);
   fChain->SetBranchAddress("trk_Trt_RComb", &trk_Trt_RComb, &b_trk_Trt_RComb);
   fChain->SetBranchAddress("trk_Trt_RtrackComb", &trk_Trt_RtrackComb, &b_trk_Trt_RtrackComb);
   fChain->SetBranchAddress("trk_Trt_tComb", &trk_Trt_tComb, &b_trk_Trt_tComb);
   fChain->SetBranchAddress("trk_Trt_xComb", &trk_Trt_xComb, &b_trk_Trt_xComb);
   fChain->SetBranchAddress("trk_Trt_yComb", &trk_Trt_yComb, &b_trk_Trt_yComb);
   fChain->SetBranchAddress("trk_Trt_HLComb", &trk_Trt_HLComb, &b_trk_Trt_HLComb);
   fChain->SetBranchAddress("trk_Trt_strawlayerComb", &trk_Trt_strawlayerComb, &b_trk_Trt_strawlayerComb);
   fChain->SetBranchAddress("trk_Trt_becComb", &trk_Trt_becComb, &b_trk_Trt_becComb);
   fChain->SetBranchAddress("trk_Trt_layerComb", &trk_Trt_layerComb, &b_trk_Trt_layerComb);
   fChain->SetBranchAddress("trk_Trt_strawComb", &trk_Trt_strawComb, &b_trk_Trt_strawComb);
   fChain->SetBranchAddress("trk_Trt_phisectorComb", &trk_Trt_phisectorComb, &b_trk_Trt_phisectorComb);
   fChain->SetBranchAddress("trk_Rec_d0Comb", &trk_Rec_d0Comb, &b_trk_Rec_d0Comb);
   fChain->SetBranchAddress("trk_Rec_z0Comb", &trk_Rec_z0Comb, &b_trk_Rec_z0Comb);
   fChain->SetBranchAddress("trk_Rec_phi0Comb", &trk_Rec_phi0Comb, &b_trk_Rec_phi0Comb);
   fChain->SetBranchAddress("trk_Rec_theta0Comb", &trk_Rec_theta0Comb, &b_trk_Rec_theta0Comb);
   fChain->SetBranchAddress("trk_Rec_qoverpComb", &trk_Rec_qoverpComb, &b_trk_Rec_qoverpComb);
   fChain->SetBranchAddress("trk_Rec_chi2Comb", &trk_Rec_chi2Comb, &b_trk_Rec_chi2Comb);
   fChain->SetBranchAddress("trk_Rec_ndofComb", &trk_Rec_ndofComb, &b_trk_Rec_ndofComb);
   fChain->SetBranchAddress("trk_Rec_etaComb", &trk_Rec_etaComb, &b_trk_Rec_etaComb);
   fChain->SetBranchAddress("trk_Rec_error_d0Comb", &trk_Rec_error_d0Comb, &b_trk_Rec_error_d0Comb);
   fChain->SetBranchAddress("trk_Rec_error_z0Comb", &trk_Rec_error_z0Comb, &b_trk_Rec_error_z0Comb);
   fChain->SetBranchAddress("trk_Rec_error_phi0Comb", &trk_Rec_error_phi0Comb, &b_trk_Rec_error_phi0Comb);
   fChain->SetBranchAddress("trk_Rec_error_theta0Comb", &trk_Rec_error_theta0Comb, &b_trk_Rec_error_theta0Comb);
   fChain->SetBranchAddress("trk_Rec_error_qoverpComb", &trk_Rec_error_qoverpComb, &b_trk_Rec_error_qoverpComb);
   fChain->SetBranchAddress("trk_Rec_chi2probComb", &trk_Rec_chi2probComb, &b_trk_Rec_chi2probComb);
   fChain->SetBranchAddress("trk_Rec_authorComb", &trk_Rec_authorComb, &b_trk_Rec_authorComb);
   fChain->SetBranchAddress("trk_nTracksMuon", &trk_nTracksMuon, &b_trk_nTracksMuon);
   fChain->SetBranchAddress("trk_nPixelHitsMuon", &trk_nPixelHitsMuon, &b_trk_nPixelHitsMuon);
   fChain->SetBranchAddress("trk_nSctHitsMuon", &trk_nSctHitsMuon, &b_trk_nSctHitsMuon);
   fChain->SetBranchAddress("trk_nTrtHitsMuon", &trk_nTrtHitsMuon, &b_trk_nTrtHitsMuon);
   fChain->SetBranchAddress("trk_Rec_d0Muon", &trk_Rec_d0Muon, &b_trk_Rec_d0Muon);
   fChain->SetBranchAddress("trk_Rec_z0Muon", &trk_Rec_z0Muon, &b_trk_Rec_z0Muon);
   fChain->SetBranchAddress("trk_Rec_phi0Muon", &trk_Rec_phi0Muon, &b_trk_Rec_phi0Muon);
   fChain->SetBranchAddress("trk_Rec_theta0Muon", &trk_Rec_theta0Muon, &b_trk_Rec_theta0Muon);
   fChain->SetBranchAddress("trk_Rec_qoverpMuon", &trk_Rec_qoverpMuon, &b_trk_Rec_qoverpMuon);
   fChain->SetBranchAddress("trk_Rec_chi2Muon", &trk_Rec_chi2Muon, &b_trk_Rec_chi2Muon);
   fChain->SetBranchAddress("trk_Rec_ndofMuon", &trk_Rec_ndofMuon, &b_trk_Rec_ndofMuon);
   fChain->SetBranchAddress("trk_Rec_etaMuon", &trk_Rec_etaMuon, &b_trk_Rec_etaMuon);
   fChain->SetBranchAddress("trk_Rec_error_d0Muon", &trk_Rec_error_d0Muon, &b_trk_Rec_error_d0Muon);
   fChain->SetBranchAddress("trk_Rec_error_z0Muon", &trk_Rec_error_z0Muon, &b_trk_Rec_error_z0Muon);
   fChain->SetBranchAddress("trk_Rec_error_phi0Muon", &trk_Rec_error_phi0Muon, &b_trk_Rec_error_phi0Muon);
   fChain->SetBranchAddress("trk_Rec_error_theta0Muon", &trk_Rec_error_theta0Muon, &b_trk_Rec_error_theta0Muon);
   fChain->SetBranchAddress("trk_Rec_error_qoverpMuon", &trk_Rec_error_qoverpMuon, &b_trk_Rec_error_qoverpMuon);
   fChain->SetBranchAddress("trk_Rec_chi2probMuon", &trk_Rec_chi2probMuon, &b_trk_Rec_chi2probMuon);
   fChain->SetBranchAddress("trk_Rec_authorMuon", &trk_Rec_authorMuon, &b_trk_Rec_authorMuon);
   fChain->SetBranchAddress("MuTagIMO_nmuon", &MuTagIMO_nmuon, &b_MuTagIMO__nmuon);
   fChain->SetBranchAddress("MuTagIMO_nTagSegs", &MuTagIMO_nTagSegs, &b_MuTagIMO__nTagSegs);
   fChain->SetBranchAddress("MuTagIMO_trk_isTagged", &MuTagIMO_trk_isTagged, &b_MuTagIMO_trk_isTagged);
   fChain->SetBranchAddress("MuTagIMO_trk_matchesBarCode", &MuTagIMO_trk_matchesBarCode, &b_MuTagIMO_trk_matchesBarCode);
   fChain->SetBranchAddress("MuTagIMO_trk_matchesPdg", &MuTagIMO_trk_matchesPdg, &b_MuTagIMO_trk_matchesPdg);
   fChain->SetBranchAddress("MuTagIMO_trk_nrPixelHits", &MuTagIMO_trk_nrPixelHits, &b_MuTagIMO_trk_nrPixelHits);
   fChain->SetBranchAddress("MuTagIMO_trk_nrSctHits", &MuTagIMO_trk_nrSctHits, &b_MuTagIMO_trk_nrSctHits);
   fChain->SetBranchAddress("MuTagIMO_trk_A0", &MuTagIMO_trk_A0, &b_MuTagIMO_trk_A0);
   fChain->SetBranchAddress("MuTagIMO_trk_Z0", &MuTagIMO_trk_Z0, &b_MuTagIMO_trk_Z0);
   fChain->SetBranchAddress("MuTagIMO_trk_phi", &MuTagIMO_trk_phi, &b_MuTagIMO_trk_phi);
   fChain->SetBranchAddress("MuTagIMO_trk_theta", &MuTagIMO_trk_theta, &b_MuTagIMO_trk_theta);
   fChain->SetBranchAddress("MuTagIMO_trk_qOverP", &MuTagIMO_trk_qOverP, &b_MuTagIMO_trk_qOverP);
   fChain->SetBranchAddress("MuTagIMO_trk_chi2", &MuTagIMO_trk_chi2, &b_MuTagIMO_trk_chi2);
   fChain->SetBranchAddress("MuTagIMO_trk_ndof", &MuTagIMO_trk_ndof, &b_MuTagIMO_trk_ndof);
   fChain->SetBranchAddress("MuTagIMO_trk_Author", &MuTagIMO_trk_Author, &b_MuTagIMO_trk_Author);
   fChain->SetBranchAddress("MuTagIMO_trk_cov11", &MuTagIMO_trk_cov11, &b_MuTagIMO_trk_cov11);
   fChain->SetBranchAddress("MuTagIMO_trk_cov12", &MuTagIMO_trk_cov12, &b_MuTagIMO_trk_cov12);
   fChain->SetBranchAddress("MuTagIMO_trk_cov13", &MuTagIMO_trk_cov13, &b_MuTagIMO_trk_cov13);
   fChain->SetBranchAddress("MuTagIMO_trk_cov14", &MuTagIMO_trk_cov14, &b_MuTagIMO_trk_cov14);
   fChain->SetBranchAddress("MuTagIMO_trk_cov15", &MuTagIMO_trk_cov15, &b_MuTagIMO_trk_cov15);
   fChain->SetBranchAddress("MuTagIMO_trk_cov22", &MuTagIMO_trk_cov22, &b_MuTagIMO_trk_cov22);
   fChain->SetBranchAddress("MuTagIMO_trk_cov23", &MuTagIMO_trk_cov23, &b_MuTagIMO_trk_cov23);
   fChain->SetBranchAddress("MuTagIMO_trk_cov24", &MuTagIMO_trk_cov24, &b_MuTagIMO_trk_cov24);
   fChain->SetBranchAddress("MuTagIMO_trk_cov25", &MuTagIMO_trk_cov25, &b_MuTagIMO_trk_cov25);
   fChain->SetBranchAddress("MuTagIMO_trk_cov33", &MuTagIMO_trk_cov33, &b_MuTagIMO_trk_cov33);
   fChain->SetBranchAddress("MuTagIMO_trk_cov34", &MuTagIMO_trk_cov34, &b_MuTagIMO_trk_cov34);
   fChain->SetBranchAddress("MuTagIMO_trk_cov35", &MuTagIMO_trk_cov35, &b_MuTagIMO_trk_cov35);
   fChain->SetBranchAddress("MuTagIMO_trk_cov44", &MuTagIMO_trk_cov44, &b_MuTagIMO_trk_cov44);
   fChain->SetBranchAddress("MuTagIMO_trk_cov45", &MuTagIMO_trk_cov45, &b_MuTagIMO_trk_cov45);
   fChain->SetBranchAddress("MuTagIMO_trk_cov55", &MuTagIMO_trk_cov55, &b_MuTagIMO_trk_cov55);
   fChain->SetBranchAddress("MuTagIMO_exTrk_trackIndex", &MuTagIMO_exTrk_trackIndex, &b_MuTagIMO_exTrk_trackIndex);
   fChain->SetBranchAddress("MuTagIMO_exTrk_A0", &MuTagIMO_exTrk_A0, &b_MuTagIMO_exTrk_A0);
   fChain->SetBranchAddress("MuTagIMO_exTrk_Z0", &MuTagIMO_exTrk_Z0, &b_MuTagIMO_exTrk_Z0);
   fChain->SetBranchAddress("MuTagIMO_exTrk_phi", &MuTagIMO_exTrk_phi, &b_MuTagIMO_exTrk_phi);
   fChain->SetBranchAddress("MuTagIMO_exTrk_theta", &MuTagIMO_exTrk_theta, &b_MuTagIMO_exTrk_theta);
   fChain->SetBranchAddress("MuTagIMO_exTrk_qOverP", &MuTagIMO_exTrk_qOverP, &b_MuTagIMO_exTrk_qOverP);
   fChain->SetBranchAddress("MuTagIMO_exTrk_cov11", &MuTagIMO_exTrk_cov11, &b_MuTagIMO_exTrk_cov11);
   fChain->SetBranchAddress("MuTagIMO_exTrk_cov12", &MuTagIMO_exTrk_cov12, &b_MuTagIMO_exTrk_cov12);
   fChain->SetBranchAddress("MuTagIMO_exTrk_cov13", &MuTagIMO_exTrk_cov13, &b_MuTagIMO_exTrk_cov13);
   fChain->SetBranchAddress("MuTagIMO_exTrk_cov14", &MuTagIMO_exTrk_cov14, &b_MuTagIMO_exTrk_cov14);
   fChain->SetBranchAddress("MuTagIMO_exTrk_cov15", &MuTagIMO_exTrk_cov15, &b_MuTagIMO_exTrk_cov15);
   fChain->SetBranchAddress("MuTagIMO_exTrk_cov22", &MuTagIMO_exTrk_cov22, &b_MuTagIMO_exTrk_cov22);
   fChain->SetBranchAddress("MuTagIMO_exTrk_cov23", &MuTagIMO_exTrk_cov23, &b_MuTagIMO_exTrk_cov23);
   fChain->SetBranchAddress("MuTagIMO_exTrk_cov24", &MuTagIMO_exTrk_cov24, &b_MuTagIMO_exTrk_cov24);
   fChain->SetBranchAddress("MuTagIMO_exTrk_cov25", &MuTagIMO_exTrk_cov25, &b_MuTagIMO_exTrk_cov25);
   fChain->SetBranchAddress("MuTagIMO_exTrk_cov33", &MuTagIMO_exTrk_cov33, &b_MuTagIMO_exTrk_cov33);
   fChain->SetBranchAddress("MuTagIMO_exTrk_cov34", &MuTagIMO_exTrk_cov34, &b_MuTagIMO_exTrk_cov34);
   fChain->SetBranchAddress("MuTagIMO_exTrk_cov35", &MuTagIMO_exTrk_cov35, &b_MuTagIMO_exTrk_cov35);
   fChain->SetBranchAddress("MuTagIMO_exTrk_cov44", &MuTagIMO_exTrk_cov44, &b_MuTagIMO_exTrk_cov44);
   fChain->SetBranchAddress("MuTagIMO_exTrk_cov45", &MuTagIMO_exTrk_cov45, &b_MuTagIMO_exTrk_cov45);
   fChain->SetBranchAddress("MuTagIMO_exTrk_cov55", &MuTagIMO_exTrk_cov55, &b_MuTagIMO_exTrk_cov55);
   fChain->SetBranchAddress("MuTagIMO_exTrk_Eloss", &MuTagIMO_exTrk_Eloss, &b_MuTagIMO_exTrk_Eloss);
   fChain->SetBranchAddress("MuTagIMO_exTrk_gPosX", &MuTagIMO_exTrk_gPosX, &b_MuTagIMO_exTrk_gPosX);
   fChain->SetBranchAddress("MuTagIMO_exTrk_gPosY", &MuTagIMO_exTrk_gPosY, &b_MuTagIMO_exTrk_gPosY);
   fChain->SetBranchAddress("MuTagIMO_exTrk_gPosZ", &MuTagIMO_exTrk_gPosZ, &b_MuTagIMO_exTrk_gPosZ);
   fChain->SetBranchAddress("MuTagIMO_exTrk_gDirX", &MuTagIMO_exTrk_gDirX, &b_MuTagIMO_exTrk_gDirX);
   fChain->SetBranchAddress("MuTagIMO_exTrk_gDirY", &MuTagIMO_exTrk_gDirY, &b_MuTagIMO_exTrk_gDirY);
   fChain->SetBranchAddress("MuTagIMO_exTrk_gDirZ", &MuTagIMO_exTrk_gDirZ, &b_MuTagIMO_exTrk_gDirZ);
   fChain->SetBranchAddress("MuTagIMO_exTrk_locX", &MuTagIMO_exTrk_locX, &b_MuTagIMO_exTrk_locX);
   fChain->SetBranchAddress("MuTagIMO_exTrk_locY", &MuTagIMO_exTrk_locY, &b_MuTagIMO_exTrk_locY);
   fChain->SetBranchAddress("MuTagIMO_exTrk_angleXZ", &MuTagIMO_exTrk_angleXZ, &b_MuTagIMO_exTrk_angleXZ);
   fChain->SetBranchAddress("MuTagIMO_exTrk_angleYZ", &MuTagIMO_exTrk_angleYZ, &b_MuTagIMO_exTrk_angleYZ);
   fChain->SetBranchAddress("MuTagIMO_exTrk_locX_error", &MuTagIMO_exTrk_locX_error, &b_MuTagIMO_exTrk_locX_error);
   fChain->SetBranchAddress("MuTagIMO_exTrk_locY_error", &MuTagIMO_exTrk_locY_error, &b_MuTagIMO_exTrk_locY_error);
   fChain->SetBranchAddress("MuTagIMO_exTrk_angleXZ_error", &MuTagIMO_exTrk_angleXZ_error, &b_MuTagIMO_exTrk_angleXZ_error);
   fChain->SetBranchAddress("MuTagIMO_exTrk_angleYZ_error", &MuTagIMO_exTrk_angleYZ_error, &b_MuTagIMO_exTrk_angleYZ_error);
   fChain->SetBranchAddress("MuTagIMO_seg_isTagSeg", &MuTagIMO_seg_isTagSeg, &b_MuTagIMO_seg_isTagSeg);
   fChain->SetBranchAddress("MuTagIMO_seg_matchesBarCode", &MuTagIMO_seg_matchesBarCode, &b_MuTagIMO_seg_matchesBarCode);
   fChain->SetBranchAddress("MuTagIMO_seg_matchesPdg", &MuTagIMO_seg_matchesPdg, &b_MuTagIMO_seg_matchesPdg);
   fChain->SetBranchAddress("MuTagIMO_seg_exTrkIndex", &MuTagIMO_seg_exTrkIndex, &b_MuTagIMO_seg_exTrkIndex);
   fChain->SetBranchAddress("MuTagIMO_seg_trackIndex", &MuTagIMO_seg_trackIndex, &b_MuTagIMO_seg_trackIndex);
   fChain->SetBranchAddress("MuTagIMO_seg_stationLevel", &MuTagIMO_seg_stationLevel, &b_MuTagIMO_seg_stationLevel);
   fChain->SetBranchAddress("MuTagIMO_seg_isEndCap", &MuTagIMO_seg_isEndCap, &b_MuTagIMO_seg_isEndCap);
   fChain->SetBranchAddress("MuTagIMO_seg_isLarge", &MuTagIMO_seg_isLarge, &b_MuTagIMO_seg_isLarge);
   fChain->SetBranchAddress("MuTagIMO_seg_nrHoles", &MuTagIMO_seg_nrHoles, &b_MuTagIMO_seg_nrHoles);
   fChain->SetBranchAddress("MuTagIMO_seg_nrMLs", &MuTagIMO_seg_nrMLs, &b_MuTagIMO_seg_nrMLs);
   fChain->SetBranchAddress("MuTagIMO_seg_nrMdtHits", &MuTagIMO_seg_nrMdtHits, &b_MuTagIMO_seg_nrMdtHits);
   fChain->SetBranchAddress("MuTagIMO_seg_nrRpcHits", &MuTagIMO_seg_nrRpcHits, &b_MuTagIMO_seg_nrRpcHits);
   fChain->SetBranchAddress("MuTagIMO_seg_nrTgcHits", &MuTagIMO_seg_nrTgcHits, &b_MuTagIMO_seg_nrTgcHits);
   fChain->SetBranchAddress("MuTagIMO_seg_nrCscHits", &MuTagIMO_seg_nrCscHits, &b_MuTagIMO_seg_nrCscHits);
   fChain->SetBranchAddress("MuTagIMO_seg_phi", &MuTagIMO_seg_phi, &b_MuTagIMO_seg_phi);
   fChain->SetBranchAddress("MuTagIMO_seg_theta", &MuTagIMO_seg_theta, &b_MuTagIMO_seg_theta);
   fChain->SetBranchAddress("MuTagIMO_seg_chi2", &MuTagIMO_seg_chi2, &b_MuTagIMO_seg_chi2);
   fChain->SetBranchAddress("MuTagIMO_seg_cov11", &MuTagIMO_seg_cov11, &b_MuTagIMO_seg_cov11);
   fChain->SetBranchAddress("MuTagIMO_seg_cov12", &MuTagIMO_seg_cov12, &b_MuTagIMO_seg_cov12);
   fChain->SetBranchAddress("MuTagIMO_seg_cov13", &MuTagIMO_seg_cov13, &b_MuTagIMO_seg_cov13);
   fChain->SetBranchAddress("MuTagIMO_seg_cov14", &MuTagIMO_seg_cov14, &b_MuTagIMO_seg_cov14);
   fChain->SetBranchAddress("MuTagIMO_seg_cov15", &MuTagIMO_seg_cov15, &b_MuTagIMO_seg_cov15);
   fChain->SetBranchAddress("MuTagIMO_seg_cov22", &MuTagIMO_seg_cov22, &b_MuTagIMO_seg_cov22);
   fChain->SetBranchAddress("MuTagIMO_seg_cov23", &MuTagIMO_seg_cov23, &b_MuTagIMO_seg_cov23);
   fChain->SetBranchAddress("MuTagIMO_seg_cov24", &MuTagIMO_seg_cov24, &b_MuTagIMO_seg_cov24);
   fChain->SetBranchAddress("MuTagIMO_seg_cov25", &MuTagIMO_seg_cov25, &b_MuTagIMO_seg_cov25);
   fChain->SetBranchAddress("MuTagIMO_seg_cov33", &MuTagIMO_seg_cov33, &b_MuTagIMO_seg_cov33);
   fChain->SetBranchAddress("MuTagIMO_seg_cov34", &MuTagIMO_seg_cov34, &b_MuTagIMO_seg_cov34);
   fChain->SetBranchAddress("MuTagIMO_seg_cov35", &MuTagIMO_seg_cov35, &b_MuTagIMO_seg_cov35);
   fChain->SetBranchAddress("MuTagIMO_seg_cov44", &MuTagIMO_seg_cov44, &b_MuTagIMO_seg_cov44);
   fChain->SetBranchAddress("MuTagIMO_seg_cov45", &MuTagIMO_seg_cov45, &b_MuTagIMO_seg_cov45);
   fChain->SetBranchAddress("MuTagIMO_seg_cov55", &MuTagIMO_seg_cov55, &b_MuTagIMO_seg_cov55);
   fChain->SetBranchAddress("MuTagIMO_seg_gPosX", &MuTagIMO_seg_gPosX, &b_MuTagIMO_seg_gPosX);
   fChain->SetBranchAddress("MuTagIMO_seg_gPosY", &MuTagIMO_seg_gPosY, &b_MuTagIMO_seg_gPosY);
   fChain->SetBranchAddress("MuTagIMO_seg_gPosZ", &MuTagIMO_seg_gPosZ, &b_MuTagIMO_seg_gPosZ);
   fChain->SetBranchAddress("MuTagIMO_seg_gDirX", &MuTagIMO_seg_gDirX, &b_MuTagIMO_seg_gDirX);
   fChain->SetBranchAddress("MuTagIMO_seg_gDirY", &MuTagIMO_seg_gDirY, &b_MuTagIMO_seg_gDirY);
   fChain->SetBranchAddress("MuTagIMO_seg_gDirZ", &MuTagIMO_seg_gDirZ, &b_MuTagIMO_seg_gDirZ);
   fChain->SetBranchAddress("MuTagIMO_seg_locX", &MuTagIMO_seg_locX, &b_MuTagIMO_seg_locX);
   fChain->SetBranchAddress("MuTagIMO_seg_locY", &MuTagIMO_seg_locY, &b_MuTagIMO_seg_locY);
   fChain->SetBranchAddress("MuTagIMO_seg_angleXZ", &MuTagIMO_seg_angleXZ, &b_MuTagIMO_seg_angleXZ);
   fChain->SetBranchAddress("MuTagIMO_seg_angleYZ", &MuTagIMO_seg_angleYZ, &b_MuTagIMO_seg_angleYZ);
   fChain->SetBranchAddress("MuTagIMO_seg_locX_error", &MuTagIMO_seg_locX_error, &b_MuTagIMO_seg_locX_error);
   fChain->SetBranchAddress("MuTagIMO_seg_locY_error", &MuTagIMO_seg_locY_error, &b_MuTagIMO_seg_locY_error);
   fChain->SetBranchAddress("MuTagIMO_seg_angleXZ_error", &MuTagIMO_seg_angleXZ_error, &b_MuTagIMO_seg_angleXZ_error);
   fChain->SetBranchAddress("MuTagIMO_seg_angleYZ_error", &MuTagIMO_seg_angleYZ_error, &b_MuTagIMO_seg_angleYZ_error);
   fChain->SetBranchAddress("MuTagIMO_match_trackIndex", &MuTagIMO_match_trackIndex, &b_MuTagIMO_match_trackIndex);
   fChain->SetBranchAddress("MuTagIMO_match_locX", &MuTagIMO_match_locX, &b_MuTagIMO_match_locX);
   fChain->SetBranchAddress("MuTagIMO_match_locY", &MuTagIMO_match_locY, &b_MuTagIMO_match_locY);
   fChain->SetBranchAddress("MuTagIMO_match_angleXZ", &MuTagIMO_match_angleXZ, &b_MuTagIMO_match_angleXZ);
   fChain->SetBranchAddress("MuTagIMO_match_angleYZ", &MuTagIMO_match_angleYZ, &b_MuTagIMO_match_angleYZ);
   fChain->SetBranchAddress("MET_ExMiss0", &MET_ExMiss0, &b_MET_ExMiss0);
   fChain->SetBranchAddress("MET_EyMiss0", &MET_EyMiss0, &b_MET_EyMiss0);
   fChain->SetBranchAddress("MET_EtSum0", &MET_EtSum0, &b_MET_EtSum0);
   fChain->SetBranchAddress("MET_ExMiss", &MET_ExMiss, &b_MET_ExMiss);
   fChain->SetBranchAddress("MET_EyMiss", &MET_EyMiss, &b_MET_EyMiss);
   fChain->SetBranchAddress("MET_EtSum", &MET_EtSum, &b_MET_EtSum);
   fChain->SetBranchAddress("MET_ExMissTopo", &MET_ExMissTopo, &b_MET_ExMissTopo);
   fChain->SetBranchAddress("MET_EyMissTopo", &MET_EyMissTopo, &b_MET_EyMissTopo);
   fChain->SetBranchAddress("MET_EtSumTopo", &MET_EtSumTopo, &b_MET_EtSumTopo);
   fChain->SetBranchAddress("MET_ExMissCorr", &MET_ExMissCorr, &b_MET_ExMissCorr);
   fChain->SetBranchAddress("MET_EyMissCorr", &MET_EyMissCorr, &b_MET_EyMissCorr);
   fChain->SetBranchAddress("MET_EtSumCorr", &MET_EtSumCorr, &b_MET_EtSumCorr);
   fChain->SetBranchAddress("MET_ExMissLocHadTopo", &MET_ExMissLocHadTopo, &b_MET_ExMissLocHadTopo);
   fChain->SetBranchAddress("MET_EyMissLocHadTopo", &MET_EyMissLocHadTopo, &b_MET_EyMissLocHadTopo);
   fChain->SetBranchAddress("MET_EtSumLocHadTopo", &MET_EtSumLocHadTopo, &b_MET_EtSumLocHadTopo);
   fChain->SetBranchAddress("MET_ExMissCorrTopo", &MET_ExMissCorrTopo, &b_MET_ExMissCorrTopo);
   fChain->SetBranchAddress("MET_EyMissCorrTopo", &MET_EyMissCorrTopo, &b_MET_EyMissCorrTopo);
   fChain->SetBranchAddress("MET_EtSumCorrTopo", &MET_EtSumCorrTopo, &b_MET_EtSumCorrTopo);
   fChain->SetBranchAddress("MET_ExMissMu", &MET_ExMissMu, &b_MET_ExMissMu);
   fChain->SetBranchAddress("MET_EyMissMu", &MET_EyMissMu, &b_MET_EyMissMu);
   fChain->SetBranchAddress("MET_EtSumMu", &MET_EtSumMu, &b_MET_EtSumMu);
   fChain->SetBranchAddress("MET_ExMissMuBoyTrack", &MET_ExMissMuBoyTrack, &b_MET_ExMissMuBoyTrack);
   fChain->SetBranchAddress("MET_EyMissMuBoyTrack", &MET_EyMissMuBoyTrack, &b_MET_EyMissMuBoyTrack);
   fChain->SetBranchAddress("MET_EtSumMuBoyTrack", &MET_EtSumMuBoyTrack, &b_MET_EtSumMuBoyTrack);
   fChain->SetBranchAddress("MET_ExMissMuBoySpectro", &MET_ExMissMuBoySpectro, &b_MET_ExMissMuBoySpectro);
   fChain->SetBranchAddress("MET_EyMissMuBoySpectro", &MET_EyMissMuBoySpectro, &b_MET_EyMissMuBoySpectro);
   fChain->SetBranchAddress("MET_EtSumMuBoySpectro", &MET_EtSumMuBoySpectro, &b_MET_EtSumMuBoySpectro);
   fChain->SetBranchAddress("MET_ExMissMuBoy", &MET_ExMissMuBoy, &b_MET_ExMissMuBoy);
   fChain->SetBranchAddress("MET_EyMissMuBoy", &MET_EyMissMuBoy, &b_MET_EyMissMuBoy);
   fChain->SetBranchAddress("MET_EtSumMuBoy", &MET_EtSumMuBoy, &b_MET_EtSumMuBoy);
   fChain->SetBranchAddress("MET_ExMissFinal", &MET_ExMissFinal, &b_MET_ExMissFinal);
   fChain->SetBranchAddress("MET_EyMissFinal", &MET_EyMissFinal, &b_MET_EyMissFinal);
   fChain->SetBranchAddress("MET_EtSumFinal", &MET_EtSumFinal, &b_MET_EtSumFinal);
   fChain->SetBranchAddress("MET_ExMissRefFinal", &MET_ExMissRefFinal, &b_MET_ExMissRefFinal);
   fChain->SetBranchAddress("MET_EyMissRefFinal", &MET_EyMissRefFinal, &b_MET_EyMissRefFinal);
   fChain->SetBranchAddress("MET_EtSumRefFinal", &MET_EtSumRefFinal, &b_MET_EtSumRefFinal);
   fChain->SetBranchAddress("MET_ExMissCryo", &MET_ExMissCryo, &b_MET_ExMissCryo);
   fChain->SetBranchAddress("MET_EyMissCryo", &MET_EyMissCryo, &b_MET_EyMissCryo);
   fChain->SetBranchAddress("MET_EtSumCryo", &MET_EtSumCryo, &b_MET_EtSumCryo);
   fChain->SetBranchAddress("MET_ExMissCryoCone", &MET_ExMissCryoCone, &b_MET_ExMissCryoCone);
   fChain->SetBranchAddress("MET_EyMissCryoCone", &MET_EyMissCryoCone, &b_MET_EyMissCryoCone);
   fChain->SetBranchAddress("MET_EtSumCryoCone", &MET_EtSumCryoCone, &b_MET_EtSumCryoCone);
   fChain->SetBranchAddress("MET_ExMissDMCryo", &MET_ExMissDMCryo, &b_MET_ExMissDMCryo);
   fChain->SetBranchAddress("MET_EyMissDMCryo", &MET_EyMissDMCryo, &b_MET_EyMissDMCryo);
   fChain->SetBranchAddress("MET_EtSumDMCryo", &MET_EtSumDMCryo, &b_MET_EtSumDMCryo);
   fChain->SetBranchAddress("MET_ExMissDMCrack1", &MET_ExMissDMCrack1, &b_MET_ExMissDMCrack1);
   fChain->SetBranchAddress("MET_EyMissDMCrack1", &MET_EyMissDMCrack1, &b_MET_EyMissDMCrack1);
   fChain->SetBranchAddress("MET_EtSumDMCrack1", &MET_EtSumDMCrack1, &b_MET_EtSumDMCrack1);
   fChain->SetBranchAddress("MET_ExMissDMCrack2", &MET_ExMissDMCrack2, &b_MET_ExMissDMCrack2);
   fChain->SetBranchAddress("MET_EyMissDMCrack2", &MET_EyMissDMCrack2, &b_MET_EyMissDMCrack2);
   fChain->SetBranchAddress("MET_EtSumDMCrack2", &MET_EtSumDMCrack2, &b_MET_EtSumDMCrack2);
   fChain->SetBranchAddress("MET_ExMissDMAll", &MET_ExMissDMAll, &b_MET_ExMissDMAll);
   fChain->SetBranchAddress("MET_EyMissDMAll", &MET_EyMissDMAll, &b_MET_EyMissDMAll);
   fChain->SetBranchAddress("MET_EtSumDMAll", &MET_EtSumDMAll, &b_MET_EtSumDMAll);
   fChain->SetBranchAddress("MET_ExMissLocHadTopoObj", &MET_ExMissLocHadTopoObj, &b_MET_ExMissLocHadTopoObj);
   fChain->SetBranchAddress("MET_EyMissLocHadTopoObj", &MET_EyMissLocHadTopoObj, &b_MET_EyMissLocHadTopoObj);
   fChain->SetBranchAddress("MET_EtSumLocHadTopoObj", &MET_EtSumLocHadTopoObj, &b_MET_EtSumLocHadTopoObj);
   fChain->SetBranchAddress("MET_ExMissTopoObj", &MET_ExMissTopoObj, &b_MET_ExMissTopoObj);
   fChain->SetBranchAddress("MET_EyMissTopoObj", &MET_EyMissTopoObj, &b_MET_EyMissTopoObj);
   fChain->SetBranchAddress("MET_EtSumTopoObj", &MET_EtSumTopoObj, &b_MET_EtSumTopoObj);
   fChain->SetBranchAddress("MET_ExMissRefEle", &MET_ExMissRefEle, &b_MET_ExMissRefEle);
   fChain->SetBranchAddress("MET_EyMissRefEle", &MET_EyMissRefEle, &b_MET_EyMissRefEle);
   fChain->SetBranchAddress("MET_EtSumRefEle", &MET_EtSumRefEle, &b_MET_EtSumRefEle);
   fChain->SetBranchAddress("MET_ExMissRefGamma", &MET_ExMissRefGamma, &b_MET_ExMissRefGamma);
   fChain->SetBranchAddress("MET_EyMissRefGamma", &MET_EyMissRefGamma, &b_MET_EyMissRefGamma);
   fChain->SetBranchAddress("MET_EtSumRefGamma", &MET_EtSumRefGamma, &b_MET_EtSumRefGamma);
   fChain->SetBranchAddress("MET_ExMissRefMuo", &MET_ExMissRefMuo, &b_MET_ExMissRefMuo);
   fChain->SetBranchAddress("MET_EyMissRefMuo", &MET_EyMissRefMuo, &b_MET_EyMissRefMuo);
   fChain->SetBranchAddress("MET_EtSumRefMuo", &MET_EtSumRefMuo, &b_MET_EtSumRefMuo);
   fChain->SetBranchAddress("MET_ExMissRefMuoTrack", &MET_ExMissRefMuoTrack, &b_MET_ExMissRefMuoTrack);
   fChain->SetBranchAddress("MET_EyMissRefMuoTrack", &MET_EyMissRefMuoTrack, &b_MET_EyMissRefMuoTrack);
   fChain->SetBranchAddress("MET_EtSumRefMuoTrack", &MET_EtSumRefMuoTrack, &b_MET_EtSumRefMuoTrack);
   fChain->SetBranchAddress("MET_ExMissRefTau", &MET_ExMissRefTau, &b_MET_ExMissRefTau);
   fChain->SetBranchAddress("MET_EyMissRefTau", &MET_EyMissRefTau, &b_MET_EyMissRefTau);
   fChain->SetBranchAddress("MET_EtSumRefTau", &MET_EtSumRefTau, &b_MET_EtSumRefTau);
   fChain->SetBranchAddress("MET_ExMissRefJet", &MET_ExMissRefJet, &b_MET_ExMissRefJet);
   fChain->SetBranchAddress("MET_EyMissRefJet", &MET_EyMissRefJet, &b_MET_EyMissRefJet);
   fChain->SetBranchAddress("MET_EtSumRefJet", &MET_EtSumRefJet, &b_MET_EtSumRefJet);
   fChain->SetBranchAddress("MET_ExMissCellOut", &MET_ExMissCellOut, &b_MET_ExMissCellOut);
   fChain->SetBranchAddress("MET_EyMissCellOut", &MET_EyMissCellOut, &b_MET_EyMissCellOut);
   fChain->SetBranchAddress("MET_EtSumCellOut", &MET_EtSumCellOut, &b_MET_EtSumCellOut);
   fChain->SetBranchAddress("MET_ExFCALCorrTopo", &MET_ExFCALCorrTopo, &b_MET_ExFCALCorrTopo);
   fChain->SetBranchAddress("MET_EyFCALCorrTopo", &MET_EyFCALCorrTopo, &b_MET_EyFCALCorrTopo);
   fChain->SetBranchAddress("MET_EtSumFCALCorrTopo", &MET_EtSumFCALCorrTopo, &b_MET_EtSumFCALCorrTopo);
   fChain->SetBranchAddress("MET_ExFCALlocHadTopo", &MET_ExFCALlocHadTopo, &b_MET_ExFCALlocHadTopo);
   fChain->SetBranchAddress("MET_EyFCALlocHadTopo", &MET_EyFCALlocHadTopo, &b_MET_EyFCALlocHadTopo);
   fChain->SetBranchAddress("MET_EtSumFCALlocHadTopo", &MET_EtSumFCALlocHadTopo, &b_MET_EtSumFCALlocHadTopo);
   fChain->SetBranchAddress("MET_ExPEMB", &MET_ExPEMB, &b_MET_ExPEMB);
   fChain->SetBranchAddress("MET_EyPEMB", &MET_EyPEMB, &b_MET_EyPEMB);
   fChain->SetBranchAddress("MET_EtSumPEMB", &MET_EtSumPEMB, &b_MET_EtSumPEMB);
   fChain->SetBranchAddress("MET_nCellPEMB", &MET_nCellPEMB, &b_MET_nCellPEMB);
   fChain->SetBranchAddress("MET_ExEMB", &MET_ExEMB, &b_MET_ExEMB);
   fChain->SetBranchAddress("MET_EyEMB", &MET_EyEMB, &b_MET_EyEMB);
   fChain->SetBranchAddress("MET_EtSumEMB", &MET_EtSumEMB, &b_MET_EtSumEMB);
   fChain->SetBranchAddress("MET_nCellEMB", &MET_nCellEMB, &b_MET_nCellEMB);
   fChain->SetBranchAddress("MET_ExPEMEC", &MET_ExPEMEC, &b_MET_ExPEMEC);
   fChain->SetBranchAddress("MET_EyPEMEC", &MET_EyPEMEC, &b_MET_EyPEMEC);
   fChain->SetBranchAddress("MET_EtSumPEMEC", &MET_EtSumPEMEC, &b_MET_EtSumPEMEC);
   fChain->SetBranchAddress("MET_nCellPEMEC", &MET_nCellPEMEC, &b_MET_nCellPEMEC);
   fChain->SetBranchAddress("MET_ExEMEC", &MET_ExEMEC, &b_MET_ExEMEC);
   fChain->SetBranchAddress("MET_EyEMEC", &MET_EyEMEC, &b_MET_EyEMEC);
   fChain->SetBranchAddress("MET_EtSumEMEC", &MET_EtSumEMEC, &b_MET_EtSumEMEC);
   fChain->SetBranchAddress("MET_nCellEMEC", &MET_nCellEMEC, &b_MET_nCellEMEC);
   fChain->SetBranchAddress("MET_ExTILE", &MET_ExTILE, &b_MET_ExTILE);
   fChain->SetBranchAddress("MET_EyTILE", &MET_EyTILE, &b_MET_EyTILE);
   fChain->SetBranchAddress("MET_EtSumTILE", &MET_EtSumTILE, &b_MET_EtSumTILE);
   fChain->SetBranchAddress("MET_nCellTILE", &MET_nCellTILE, &b_MET_nCellTILE);
   fChain->SetBranchAddress("MET_ExHEC", &MET_ExHEC, &b_MET_ExHEC);
   fChain->SetBranchAddress("MET_EyHEC", &MET_EyHEC, &b_MET_EyHEC);
   fChain->SetBranchAddress("MET_EtSumHEC", &MET_EtSumHEC, &b_MET_EtSumHEC);
   fChain->SetBranchAddress("MET_nCellHEC", &MET_nCellHEC, &b_MET_nCellHEC);
   fChain->SetBranchAddress("MET_ExFCAL", &MET_ExFCAL, &b_MET_ExFCAL);
   fChain->SetBranchAddress("MET_EyFCAL", &MET_EyFCAL, &b_MET_EyFCAL);
   fChain->SetBranchAddress("MET_EtSumFCAL", &MET_EtSumFCAL, &b_MET_EtSumFCAL);
   fChain->SetBranchAddress("MET_nCellFCAL", &MET_nCellFCAL, &b_MET_nCellFCAL);
   fChain->SetBranchAddress("MET_ExBARReg", &MET_ExBARReg, &b_MET_ExBARReg);
   fChain->SetBranchAddress("MET_EyBARReg", &MET_EyBARReg, &b_MET_EyBARReg);
   fChain->SetBranchAddress("MET_EtSumBARReg", &MET_EtSumBARReg, &b_MET_EtSumBARReg);
   fChain->SetBranchAddress("MET_ExECReg", &MET_ExECReg, &b_MET_ExECReg);
   fChain->SetBranchAddress("MET_EyECReg", &MET_EyECReg, &b_MET_EyECReg);
   fChain->SetBranchAddress("MET_EtSumECReg", &MET_EtSumECReg, &b_MET_EtSumECReg);
   fChain->SetBranchAddress("MET_ExFCALReg", &MET_ExFCALReg, &b_MET_ExFCALReg);
   fChain->SetBranchAddress("MET_EyFCALReg", &MET_EyFCALReg, &b_MET_EyFCALReg);
   fChain->SetBranchAddress("MET_EtSumFCALReg", &MET_EtSumFCALReg, &b_MET_EtSumFCALReg);
   fChain->SetBranchAddress("L1Em_nRoI", &L1Em_nRoI, &b_L1Em_nRoI);
   fChain->SetBranchAddress("L1Em_RoIWord", &L1Em_RoIWord, &b_L1Em_RoIWord);
   fChain->SetBranchAddress("L1Em_Core", &L1Em_Core, &b_L1Em_Core);
   fChain->SetBranchAddress("L1Em_EmClus", &L1Em_EmClus, &b_L1Em_EmClus);
   fChain->SetBranchAddress("L1Em_TauClus", &L1Em_TauClus, &b_L1Em_TauClus);
   fChain->SetBranchAddress("L1Em_EmIsol", &L1Em_EmIsol, &b_L1Em_EmIsol);
   fChain->SetBranchAddress("L1Em_HdIsol", &L1Em_HdIsol, &b_L1Em_HdIsol);
   fChain->SetBranchAddress("L1Em_HdCore", &L1Em_HdCore, &b_L1Em_HdCore);
   fChain->SetBranchAddress("L1Em_EmTauThresh", &L1Em_EmTauThresh, &b_L1Em_EmTauThresh);
   fChain->SetBranchAddress("L1Em_eta", &L1Em_eta, &b_L1Em_eta);
   fChain->SetBranchAddress("L1Em_phi", &L1Em_phi, &b_L1Em_phi);
   fChain->SetBranchAddress("L1Jet_nRoI", &L1Jet_nRoI, &b_L1Jet_nRoI);
   fChain->SetBranchAddress("L1Jet_JetRoIWord", &L1Jet_JetRoIWord, &b_L1Jet_JetRoIWord);
   fChain->SetBranchAddress("L1Jet_ET4x4", &L1Jet_ET4x4, &b_L1Jet_ET4x4);
   fChain->SetBranchAddress("L1Jet_ET6x6", &L1Jet_ET6x6, &b_L1Jet_ET6x6);
   fChain->SetBranchAddress("L1Jet_ET8x8", &L1Jet_ET8x8, &b_L1Jet_ET8x8);
   fChain->SetBranchAddress("L1Jet_Thresh", &L1Jet_Thresh, &b_L1Jet_Thresh);
   fChain->SetBranchAddress("L1Jet_eta", &L1Jet_eta, &b_L1Jet_eta);
   fChain->SetBranchAddress("L1Jet_phi", &L1Jet_phi, &b_L1Jet_phi);
   fChain->SetBranchAddress("L1ET_EtMissHits", &L1ET_EtMissHits, &b_L1ET_EtMissHits);
   fChain->SetBranchAddress("L1ET_EtSumHits", &L1ET_EtSumHits, &b_L1ET_EtSumHits);
   fChain->SetBranchAddress("L1ET_Ex", &L1ET_Ex, &b_L1ET_Ex);
   fChain->SetBranchAddress("L1ET_Ey", &L1ET_Ey, &b_L1ET_Ey);
   fChain->SetBranchAddress("L1ET_EtMiss", &L1ET_EtMiss, &b_L1ET_EtMiss);
   fChain->SetBranchAddress("L1ET_EtSum", &L1ET_EtSum, &b_L1ET_EtSum);
   fChain->SetBranchAddress("nCTP_ROI", &nCTP_ROI, &b_nCTP_ROI);
   fChain->SetBranchAddress("CTP_ROI", &CTP_ROI, &b_CTP_ROI);
   fChain->SetBranchAddress("nMuCTPI_ROI", &nMuCTPI_ROI, &b_nMuCTPI_ROI);
   fChain->SetBranchAddress("muCTPI_ROI", &muCTPI_ROI, &b_muCTPI_ROI);
   fChain->SetBranchAddress("nEMTau_ROI", &nEMTau_ROI, &b_nEMTau_ROI);
   fChain->SetBranchAddress("EMTau_ROI", &EMTau_ROI, &b_EMTau_ROI);
   fChain->SetBranchAddress("nJetEnergy_ROI", &nJetEnergy_ROI, &b_nJetEnergy_ROI);
   fChain->SetBranchAddress("JetEnergy_ROI", &JetEnergy_ROI, &b_JetEnergy_ROI);
   fChain->SetBranchAddress("muctpi_nCandidates", &muctpi_nCandidates, &b_muctpi_nCandidates);
   fChain->SetBranchAddress("muctpi_windowSizeBC", &muctpi_windowSizeBC, &b_muctpi_windowSizeBC);
   fChain->SetBranchAddress("muctpi_bcid", &muctpi_bcid, &b_muctpi_bcid);
   fChain->SetBranchAddress("muctpi_PtMultiplicity", &muctpi_PtMultiplicity, &b_muctpi_PtMultiplicity);
   fChain->SetBranchAddress("muctpi_cand_sectorOverflow", &muctpi_cand_sectorOverflow, &b_muctpi_cand_sectorOverflow);
   fChain->SetBranchAddress("muctpi_cand_RoiOverflow", &muctpi_cand_RoiOverflow, &b_muctpi_cand_RoiOverflow);
   fChain->SetBranchAddress("muctpi_cand_RoiNumber", &muctpi_cand_RoiNumber, &b_muctpi_cand_RoiNumber);
   fChain->SetBranchAddress("muctpi_cand_overlapBits", &muctpi_cand_overlapBits, &b_muctpi_cand_overlapBits);
   fChain->SetBranchAddress("muctpi_cand_sectorID", &muctpi_cand_sectorID, &b_muctpi_cand_sectorID);
   fChain->SetBranchAddress("muctpi_cand_sectorLocation", &muctpi_cand_sectorLocation, &b_muctpi_cand_sectorLocation);
   fChain->SetBranchAddress("muctpi_cand_hemisphere", &muctpi_cand_hemisphere, &b_muctpi_cand_hemisphere);
   fChain->SetBranchAddress("muctpi_cand_Pt", &muctpi_cand_Pt, &b_muctpi_cand_Pt);
   fChain->SetBranchAddress("muctpi_cand_bcid", &muctpi_cand_bcid, &b_muctpi_cand_bcid);
   fChain->SetBranchAddress("muctpi_cand_isHighestPt", &muctpi_cand_isHighestPt, &b_muctpi_cand_isHighestPt);
   fChain->SetBranchAddress("muctpi_cand_sentRoI", &muctpi_cand_sentRoI, &b_muctpi_cand_sentRoI);
   fChain->SetBranchAddress("muctpi_roi_GBCID", &muctpi_roi_GBCID, &b_muctpi_roi_GBCID);
   fChain->SetBranchAddress("muctpi_roi_N_ROI", &muctpi_roi_N_ROI, &b_muctpi_roi_N_ROI);
   fChain->SetBranchAddress("muctpi_roi_SUM", &muctpi_roi_SUM, &b_muctpi_roi_SUM);
   fChain->SetBranchAddress("muctpi_roi_BCID", &muctpi_roi_BCID, &b_muctpi_roi_BCID);
   fChain->SetBranchAddress("muctpi_roi_First", &muctpi_roi_First, &b_muctpi_roi_First);
   fChain->SetBranchAddress("muctpi_roi_Acc", &muctpi_roi_Acc, &b_muctpi_roi_Acc);
   fChain->SetBranchAddress("muctpi_roi_O_ROI", &muctpi_roi_O_ROI, &b_muctpi_roi_O_ROI);
   fChain->SetBranchAddress("muctpi_roi_O_STR", &muctpi_roi_O_STR, &b_muctpi_roi_O_STR);
   fChain->SetBranchAddress("muctpi_roi_pT", &muctpi_roi_pT, &b_muctpi_roi_pT);
   fChain->SetBranchAddress("muctpi_roi_eta", &muctpi_roi_eta, &b_muctpi_roi_eta);
   fChain->SetBranchAddress("muctpi_roi_phi", &muctpi_roi_phi, &b_muctpi_roi_phi);
   fChain->SetBranchAddress("muctpi_rodheader_sourceId", &muctpi_rodheader_sourceId, &b_muctpi_rodheader_sourceId);
   fChain->SetBranchAddress("muctpi_rodheader_runNumber", &muctpi_rodheader_runNumber, &b_muctpi_rodheader_runNumber);
   fChain->SetBranchAddress("muctpi_rodheader_lvl1Id", &muctpi_rodheader_lvl1Id, &b_muctpi_rodheader_lvl1Id);
   fChain->SetBranchAddress("muctpi_rodheader_bcid", &muctpi_rodheader_bcid, &b_muctpi_rodheader_bcid);
   fChain->SetBranchAddress("muctpi_rodheader_lvl1TriggerType", &muctpi_rodheader_lvl1TriggerType, &b_muctpi_rodheader_lvl1TriggerType);
   fChain->SetBranchAddress("muctpi_rodheader_detectorEventType", &muctpi_rodheader_detectorEventType, &b_muctpi_rodheader_detectorEventType);
   fChain->SetBranchAddress("muctpi_rodheader_nDataWords", &muctpi_rodheader_nDataWords, &b_muctpi_rodheader_nDataWords);
   fChain->SetBranchAddress("muctpi_rodheader_statusWords", &muctpi_rodheader_statusWords, &b_muctpi_rodheader_statusWords);
   fChain->SetBranchAddress("nCandidates", &nCandidates, &b_nCandidates);
   fChain->SetBranchAddress("etaCand", &etaCand, &b_etaCand);
   fChain->SetBranchAddress("phiCand", &phiCand, &b_phiCand);
   fChain->SetBranchAddress("nItems", &nItems, &b_nItems);
   fChain->SetBranchAddress("itemName", &itemName, &b_itemName);
   fChain->SetBranchAddress("itemTBP", &itemTBP, &b_itemTBP);
   fChain->SetBranchAddress("itemTAP", &itemTAP, &b_itemTAP);
   fChain->SetBranchAddress("itemTAV", &itemTAV, &b_itemTAV);
   fChain->SetBranchAddress("nThresholds", &nThresholds, &b_nThresholds);
   fChain->SetBranchAddress("thresholdName", &thresholdName, &b_thresholdName);
   fChain->SetBranchAddress("thresholdMulti", &thresholdMulti, &b_thresholdMulti);
   fChain->SetBranchAddress("ctp_numberBC", &ctp_numberBC, &b_ctp_numberBC);
   fChain->SetBranchAddress("ctp_L1A_BC", &ctp_L1A_BC, &b_ctp_L1A_BC);
   fChain->SetBranchAddress("ctp_timeSec", &ctp_timeSec, &b_ctp_timeSec);
   fChain->SetBranchAddress("ctp_timeNanoSec", &ctp_timeNanoSec, &b_ctp_timeNanoSec);
   fChain->SetBranchAddress("ctp_nPITs", &ctp_nPITs, &b_ctp_nPITs);
   fChain->SetBranchAddress("ctp_firedItemsBeforePrescale", &ctp_firedItemsBeforePrescale, &b_ctp_firedItemsBeforePrescale);
   fChain->SetBranchAddress("ctp_bcid", &ctp_bcid, &b_ctp_bcid);
   fChain->SetBranchAddress("ctp_randomTrig", &ctp_randomTrig, &b_ctp_randomTrig);
   fChain->SetBranchAddress("ctp_prescaledClock", &ctp_prescaledClock, &b_ctp_prescaledClock);
   fChain->SetBranchAddress("ctp_bcIndexPIT", &ctp_bcIndexPIT, &b_ctp_bcIndexPIT);
   fChain->SetBranchAddress("ctp_pit", &ctp_pit, &b_ctp_pit);
   fChain->SetBranchAddress("ctp_bcIndexTriggerItems", &ctp_bcIndexTriggerItems, &b_ctp_bcIndexTriggerItems);
   fChain->SetBranchAddress("ctp_tbp", &ctp_tbp, &b_ctp_tbp);
   fChain->SetBranchAddress("ctp_tap", &ctp_tap, &b_ctp_tap);
   fChain->SetBranchAddress("ctp_tav", &ctp_tav, &b_ctp_tav);
   fChain->SetBranchAddress("ctp_rodheader_sourceId", &ctp_rodheader_sourceId, &b_ctp_rodheader_sourceId);
   fChain->SetBranchAddress("ctp_rodheader_runNumber", &ctp_rodheader_runNumber, &b_ctp_rodheader_runNumber);
   fChain->SetBranchAddress("ctp_rodheader_lvl1Id", &ctp_rodheader_lvl1Id, &b_ctp_rodheader_lvl1Id);
   fChain->SetBranchAddress("ctp_rodheader_bcid", &ctp_rodheader_bcid, &b_ctp_rodheader_bcid);
   fChain->SetBranchAddress("ctp_rodheader_lvl1TriggerType", &ctp_rodheader_lvl1TriggerType, &b_ctp_rodheader_lvl1TriggerType);
   fChain->SetBranchAddress("ctp_rodheader_detectorEventType", &ctp_rodheader_detectorEventType, &b_ctp_rodheader_detectorEventType);
   fChain->SetBranchAddress("ctp_rodheader_nDataWords", &ctp_rodheader_nDataWords, &b_ctp_rodheader_nDataWords);
   fChain->SetBranchAddress("ctp_rodheader_statusWords", &ctp_rodheader_statusWords, &b_ctp_rodheader_statusWords);
#endif

   fChain->SetBranchAddress("L1CaloPPM_ntt", &L1CaloPPM_ntt, &b_L1CaloPPM_ntt);
   fChain->SetBranchAddress("L1CaloPPM_eta", &L1CaloPPM_eta, &b_L1CaloPPM_eta);
   fChain->SetBranchAddress("L1CaloPPM_phi", &L1CaloPPM_phi, &b_L1CaloPPM_phi);
   fChain->SetBranchAddress("L1CaloPPM_emCrate", &L1CaloPPM_emCrate, &b_L1CaloPPM_emCrate);
   fChain->SetBranchAddress("L1CaloPPM_emModule", &L1CaloPPM_emModule, &b_L1CaloPPM_emModule);
   fChain->SetBranchAddress("L1CaloPPM_emSubmodule", &L1CaloPPM_emSubmodule, &b_L1CaloPPM_emSubmodule);
   fChain->SetBranchAddress("L1CaloPPM_emChannel", &L1CaloPPM_emChannel, &b_L1CaloPPM_emChannel);
   fChain->SetBranchAddress("L1CaloPPM_hadCrate", &L1CaloPPM_hadCrate, &b_L1CaloPPM_hadCrate);
   fChain->SetBranchAddress("L1CaloPPM_hadModule", &L1CaloPPM_hadModule, &b_L1CaloPPM_hadModule);
   fChain->SetBranchAddress("L1CaloPPM_hadSubmodule", &L1CaloPPM_hadSubmodule, &b_L1CaloPPM_hadSubmodule);
   fChain->SetBranchAddress("L1CaloPPM_hadChannel", &L1CaloPPM_hadChannel, &b_L1CaloPPM_hadChannel);
   fChain->SetBranchAddress("L1CaloPPM_emChannelId", &L1CaloPPM_emChannelId, &b_L1CaloPPM_emChannelId);
   fChain->SetBranchAddress("L1CaloPPM_hadChannelId", &L1CaloPPM_hadChannelId, &b_L1CaloPPM_hadChannelId);
   fChain->SetBranchAddress("L1CaloPPM_emTTCellsEnergy", &L1CaloPPM_emTTCellsEnergy, &b_L1CaloPPM_emTTCellsEnergy);
   fChain->SetBranchAddress("L1CaloPPM_hadTTCellsEnergy", &L1CaloPPM_hadTTCellsEnergy, &b_L1CaloPPM_hadTTCellsEnergy);
   fChain->SetBranchAddress("L1CaloPPM_emCaloWaves", &L1CaloPPM_emCaloWaves, &b_L1CaloPPM_emCaloWaves);
   fChain->SetBranchAddress("L1CaloPPM_hadCaloWaves", &L1CaloPPM_hadCaloWaves, &b_L1CaloPPM_hadCaloWaves);
   fChain->SetBranchAddress("L1CaloPPM_emPeak", &L1CaloPPM_emPeak, &b_L1CaloPPM_emPeak);
   fChain->SetBranchAddress("L1CaloPPM_emADCPeak", &L1CaloPPM_emADCPeak, &b_L1CaloPPM_emADCPeak);
   fChain->SetBranchAddress("L1CaloPPM_hadPeak", &L1CaloPPM_hadPeak, &b_L1CaloPPM_hadPeak);
   fChain->SetBranchAddress("L1CaloPPM_hadADCPeak", &L1CaloPPM_hadADCPeak, &b_L1CaloPPM_hadADCPeak);
   fChain->SetBranchAddress("L1CaloPPM_emLUT", &L1CaloPPM_emLUT, &b_L1CaloPPM_emLUT);
   fChain->SetBranchAddress("L1CaloPPM_hadLUT", &L1CaloPPM_hadLUT, &b_L1CaloPPM_hadLUT);
   fChain->SetBranchAddress("L1CaloPPM_emADC", &L1CaloPPM_emADC, &b_L1CaloPPM_emADC);
   fChain->SetBranchAddress("L1CaloPPM_hadADC", &L1CaloPPM_hadADC, &b_L1CaloPPM_hadADC);
   fChain->SetBranchAddress("L1CaloPPM_emEnergy", &L1CaloPPM_emEnergy, &b_L1CaloPPM_emEnergy);
   fChain->SetBranchAddress("L1CaloPPM_hadEnergy", &L1CaloPPM_hadEnergy, &b_L1CaloPPM_hadEnergy);
   fChain->SetBranchAddress("L1CaloPPM_emBCIDvec", &L1CaloPPM_emBCIDvec, &b_L1CaloPPM_emBCIDvec);
   fChain->SetBranchAddress("L1CaloPPM_emBCIDext", &L1CaloPPM_emBCIDext, &b_L1CaloPPM_emBCIDext);
   fChain->SetBranchAddress("L1CaloPPM_hadBCIDvec", &L1CaloPPM_hadBCIDvec, &b_L1CaloPPM_hadBCIDvec);
   fChain->SetBranchAddress("L1CaloPPM_hadBCIDext", &L1CaloPPM_hadBCIDext, &b_L1CaloPPM_hadBCIDext);
   fChain->SetBranchAddress("L1CaloPPM_emError", &L1CaloPPM_emError, &b_L1CaloPPM_emError);
   fChain->SetBranchAddress("L1CaloPPM_hadError", &L1CaloPPM_hadError, &b_L1CaloPPM_hadError);
   fChain->SetBranchAddress("L1CaloPPM_emBCID", &L1CaloPPM_emBCID, &b_L1CaloPPM_emBCID);
   fChain->SetBranchAddress("L1CaloPPM_hadBCID", &L1CaloPPM_hadBCID, &b_L1CaloPPM_hadBCID);
   fChain->SetBranchAddress("L1CaloPPM_emIsSaturated", &L1CaloPPM_emIsSaturated, &b_L1CaloPPM_emIsSaturated);
   fChain->SetBranchAddress("L1CaloPPM_hadIsSaturated", &L1CaloPPM_hadIsSaturated, &b_L1CaloPPM_hadIsSaturated);
   fChain->SetBranchAddress("L1CaloPPM_emIsFilled", &L1CaloPPM_emIsFilled, &b_L1CaloPPM_emIsFilled);
   fChain->SetBranchAddress("L1CaloPPM_hadIsFilled", &L1CaloPPM_hadIsFilled, &b_L1CaloPPM_hadIsFilled);

#ifndef PPM_ONLY
   fChain->SetBranchAddress("L1CaloCPM_RoI_n", &L1CaloCPM_RoI_n, &b_L1CaloCPM_RoI_n);
   fChain->SetBranchAddress("L1CaloCPM_RoI_crate", &L1CaloCPM_RoI_crate, &b_L1CaloCPM_RoI_crate);
   fChain->SetBranchAddress("L1CaloCPM_RoI_cpm", &L1CaloCPM_RoI_cpm, &b_L1CaloCPM_RoI_cpm);
   fChain->SetBranchAddress("L1CaloCPM_RoI_chip", &L1CaloCPM_RoI_chip, &b_L1CaloCPM_RoI_chip);
   fChain->SetBranchAddress("L1CaloCPM_RoI_location", &L1CaloCPM_RoI_location, &b_L1CaloCPM_RoI_location);
   fChain->SetBranchAddress("L1CaloCPM_RoI_hits", &L1CaloCPM_RoI_hits, &b_L1CaloCPM_RoI_hits);
   fChain->SetBranchAddress("L1CaloCPM_RoI_eta", &L1CaloCPM_RoI_eta, &b_L1CaloCPM_RoI_eta);
   fChain->SetBranchAddress("L1CaloCPM_RoI_phi", &L1CaloCPM_RoI_phi, &b_L1CaloCPM_RoI_phi);
   fChain->SetBranchAddress("L1CaloCPM_RoI_core", &L1CaloCPM_RoI_core, &b_L1CaloCPM_RoI_core);
   fChain->SetBranchAddress("L1CaloCPM_RoI_emClus", &L1CaloCPM_RoI_emClus, &b_L1CaloCPM_RoI_emClus);
   fChain->SetBranchAddress("L1CaloCPM_RoI_tauClus", &L1CaloCPM_RoI_tauClus, &b_L1CaloCPM_RoI_tauClus);
   fChain->SetBranchAddress("L1CaloCPM_RoI_emIsol", &L1CaloCPM_RoI_emIsol, &b_L1CaloCPM_RoI_emIsol);
   fChain->SetBranchAddress("L1CaloCPM_RoI_hadIsol", &L1CaloCPM_RoI_hadIsol, &b_L1CaloCPM_RoI_hadIsol);
   fChain->SetBranchAddress("L1CaloCPM_RoI_hadVeto", &L1CaloCPM_RoI_hadVeto, &b_L1CaloCPM_RoI_hadVeto);
   fChain->SetBranchAddress("L1CaloCPM_RoI_isEtMax", &L1CaloCPM_RoI_isEtMax, &b_L1CaloCPM_RoI_isEtMax);
   fChain->SetBranchAddress("L1CaloCPM_RoI_simHits", &L1CaloCPM_RoI_simHits, &b_L1CaloCPM_RoI_simHits);
   fChain->SetBranchAddress("L1CaloCPM_RoI_error", &L1CaloCPM_RoI_error, &b_L1CaloCPM_RoI_error);
   fChain->SetBranchAddress("L1CaloCPM_SimRoI_n", &L1CaloCPM_SimRoI_n, &b_L1CaloCPM_SimRoI_n);
   fChain->SetBranchAddress("L1CaloCPM_SimRoI_eta", &L1CaloCPM_SimRoI_eta, &b_L1CaloCPM_SimRoI_eta);
   fChain->SetBranchAddress("L1CaloCPM_SimRoI_phi", &L1CaloCPM_SimRoI_phi, &b_L1CaloCPM_SimRoI_phi);
   fChain->SetBranchAddress("L1CaloCPM_SimRoI_core", &L1CaloCPM_SimRoI_core, &b_L1CaloCPM_SimRoI_core);
   fChain->SetBranchAddress("L1CaloCPM_SimRoI_emClus", &L1CaloCPM_SimRoI_emClus, &b_L1CaloCPM_SimRoI_emClus);
   fChain->SetBranchAddress("L1CaloCPM_SimRoI_tauClus", &L1CaloCPM_SimRoI_tauClus, &b_L1CaloCPM_SimRoI_tauClus);
   fChain->SetBranchAddress("L1CaloCPM_SimRoI_emIsol", &L1CaloCPM_SimRoI_emIsol, &b_L1CaloCPM_SimRoI_emIsol);
   fChain->SetBranchAddress("L1CaloCPM_SimRoI_hadIsol", &L1CaloCPM_SimRoI_hadIsol, &b_L1CaloCPM_SimRoI_hadIsol);
   fChain->SetBranchAddress("L1CaloCPM_SimRoI_hadVeto", &L1CaloCPM_SimRoI_hadVeto, &b_L1CaloCPM_SimRoI_hadVeto);
   fChain->SetBranchAddress("L1CaloCPM_SimRoI_isEtMax", &L1CaloCPM_SimRoI_isEtMax, &b_L1CaloCPM_SimRoI_isEtMax);
   fChain->SetBranchAddress("L1CaloCPM_SimRoI_hits", &L1CaloCPM_SimRoI_hits, &b_L1CaloCPM_SimRoI_hits);
   fChain->SetBranchAddress("L1CaloCPM_SimRoI_roiWord", &L1CaloCPM_SimRoI_roiWord, &b_L1CaloCPM_SimRoI_roiWord);
   fChain->SetBranchAddress("L1CaloCPM_Hits_n", &L1CaloCPM_Hits_n, &b_L1CaloCPM_Hits_n);
   fChain->SetBranchAddress("L1CaloCPM_Hits_crate", &L1CaloCPM_Hits_crate, &b_L1CaloCPM_Hits_crate);
   fChain->SetBranchAddress("L1CaloCPM_Hits_module", &L1CaloCPM_Hits_module, &b_L1CaloCPM_Hits_module);
   fChain->SetBranchAddress("L1CaloCPM_Hits_peak", &L1CaloCPM_Hits_peak, &b_L1CaloCPM_Hits_peak);
   fChain->SetBranchAddress("L1CaloCPM_Hits_hitWord0", &L1CaloCPM_Hits_hitWord0, &b_L1CaloCPM_Hits_hitWord0);
   fChain->SetBranchAddress("L1CaloCPM_Hits_hitWord1", &L1CaloCPM_Hits_hitWord1, &b_L1CaloCPM_Hits_hitWord1);
   fChain->SetBranchAddress("L1CaloCPM_Hits_hitsVec0", &L1CaloCPM_Hits_hitsVec0, &b_L1CaloCPM_Hits_hitsVec0);
   fChain->SetBranchAddress("L1CaloCPM_Hits_hitsVec1", &L1CaloCPM_Hits_hitsVec1, &b_L1CaloCPM_Hits_hitsVec1);
   fChain->SetBranchAddress("L1CaloCPM_Towers_n", &L1CaloCPM_Towers_n, &b_L1CaloCPM_Towers_n);
   fChain->SetBranchAddress("L1CaloCPM_Towers_eta", &L1CaloCPM_Towers_eta, &b_L1CaloCPM_Towers_eta);
   fChain->SetBranchAddress("L1CaloCPM_Towers_phi", &L1CaloCPM_Towers_phi, &b_L1CaloCPM_Towers_phi);
   fChain->SetBranchAddress("L1CaloCPM_Towers_peak", &L1CaloCPM_Towers_peak, &b_L1CaloCPM_Towers_peak);
   fChain->SetBranchAddress("L1CaloCPM_Towers_emEnergy", &L1CaloCPM_Towers_emEnergy, &b_L1CaloCPM_Towers_emEnergy);
   fChain->SetBranchAddress("L1CaloCPM_Towers_hadEnergy", &L1CaloCPM_Towers_hadEnergy, &b_L1CaloCPM_Towers_hadEnergy);
   fChain->SetBranchAddress("L1CaloCPM_Towers_emEnergyVec", &L1CaloCPM_Towers_emEnergyVec, &b_L1CaloCPM_Towers_emEnergyVec);
   fChain->SetBranchAddress("L1CaloCPM_Towers_hadEnergyVec", &L1CaloCPM_Towers_hadEnergyVec, &b_L1CaloCPM_Towers_hadEnergyVec);
   fChain->SetBranchAddress("L1CaloCPM_Towers_emError", &L1CaloCPM_Towers_emError, &b_L1CaloCPM_Towers_emError);
   fChain->SetBranchAddress("L1CaloCPM_Towers_hadError", &L1CaloCPM_Towers_hadError, &b_L1CaloCPM_Towers_hadError);
   fChain->SetBranchAddress("L1CaloCPM_Towers_emErrorVec", &L1CaloCPM_Towers_emErrorVec, &b_L1CaloCPM_Towers_emErrorVec);
   fChain->SetBranchAddress("L1CaloCPM_Towers_hadErrorVec", &L1CaloCPM_Towers_hadErrorVec, &b_L1CaloCPM_Towers_hadErrorVec);
   fChain->SetBranchAddress("L1CaloCPM_CMM_n", &L1CaloCPM_CMM_n, &b_L1CaloCPM_CMM_n);
   fChain->SetBranchAddress("L1CaloCPM_CMM_crate", &L1CaloCPM_CMM_crate, &b_L1CaloCPM_CMM_crate);
   fChain->SetBranchAddress("L1CaloCPM_CMM_dataID", &L1CaloCPM_CMM_dataID, &b_L1CaloCPM_CMM_dataID);
   fChain->SetBranchAddress("L1CaloCPM_CMM_hitWord0", &L1CaloCPM_CMM_hitWord0, &b_L1CaloCPM_CMM_hitWord0);
   fChain->SetBranchAddress("L1CaloCPM_CMM_hitWord1", &L1CaloCPM_CMM_hitWord1, &b_L1CaloCPM_CMM_hitWord1);
   fChain->SetBranchAddress("L1CaloCPM_CMM_error0", &L1CaloCPM_CMM_error0, &b_L1CaloCPM_CMM_error0);
   fChain->SetBranchAddress("L1CaloCPM_CMM_error1", &L1CaloCPM_CMM_error1, &b_L1CaloCPM_CMM_error1);
   fChain->SetBranchAddress("L1CaloCPM_CMM_peak", &L1CaloCPM_CMM_peak, &b_L1CaloCPM_CMM_peak);
   fChain->SetBranchAddress("L1CaloCPM_CMM_hitsVec0", &L1CaloCPM_CMM_hitsVec0, &b_L1CaloCPM_CMM_hitsVec0);
   fChain->SetBranchAddress("L1CaloCPM_CMM_hitsVec1", &L1CaloCPM_CMM_hitsVec1, &b_L1CaloCPM_CMM_hitsVec1);
   fChain->SetBranchAddress("L1CaloCPM_CMM_errorVec0", &L1CaloCPM_CMM_errorVec0, &b_L1CaloCPM_CMM_errorVec0);
   fChain->SetBranchAddress("L1CaloCPM_CMM_errorVec1", &L1CaloCPM_CMM_errorVec1, &b_L1CaloCPM_CMM_errorVec1);
   fChain->SetBranchAddress("L1CaloJEM_JetEl_n", &L1CaloJEM_JetEl_n, &b_L1CaloJEM_JetE_n);
   fChain->SetBranchAddress("L1CaloJEM_JetEl_eta", &L1CaloJEM_JetEl_eta, &b_L1CaloJEM_JetEl_eta);
   fChain->SetBranchAddress("L1CaloJEM_JetEl_phi", &L1CaloJEM_JetEl_phi, &b_L1CaloJEM_JetEl_phi);
   fChain->SetBranchAddress("L1CaloJEM_JetEl_emEnergy", &L1CaloJEM_JetEl_emEnergy, &b_L1CaloJEM_JetEl_emEnergy);
   fChain->SetBranchAddress("L1CaloJEM_JetEl_hadEnergy", &L1CaloJEM_JetEl_hadEnergy, &b_L1CaloJEM_JetEl_hadEnergy);
   fChain->SetBranchAddress("L1CaloJEM_JetEl_energy", &L1CaloJEM_JetEl_energy, &b_L1CaloJEM_JetEl_energy);
   fChain->SetBranchAddress("L1CaloJEM_JetEl_isSaturated", &L1CaloJEM_JetEl_isSaturated, &b_L1CaloJEM_JetEl_isSaturated);
   fChain->SetBranchAddress("L1CaloJEM_JetEl_isEmSaturated", &L1CaloJEM_JetEl_isEmSaturated, &b_L1CaloJEM_JetEl_isEmSaturated);
   fChain->SetBranchAddress("L1CaloJEM_JetEl_isHadSaturated", &L1CaloJEM_JetEl_isHadSaturated, &b_L1CaloJEM_JetEl_isHadSaturated);
   fChain->SetBranchAddress("L1CaloJEM_JetEl_emError", &L1CaloJEM_JetEl_emError, &b_L1CaloJEM_JetEl_emError);
   fChain->SetBranchAddress("L1CaloJEM_JetEl_hadError", &L1CaloJEM_JetEl_hadError, &b_L1CaloJEM_JetEl_hadError);
   fChain->SetBranchAddress("L1CaloJEM_JetEl_linkError", &L1CaloJEM_JetEl_linkError, &b_L1CaloJEM_JetEl_linkError);
   fChain->SetBranchAddress("L1CaloJEM_JetEl_peak", &L1CaloJEM_JetEl_peak, &b_L1CaloJEM_JetEl_peak);
   fChain->SetBranchAddress("L1CaloJEM_JetEl_emEnergyVec", &L1CaloJEM_JetEl_emEnergyVec, &b_L1CaloJEM_JetEl_emEnergyVec);
   fChain->SetBranchAddress("L1CaloJEM_JetEl_hadEnergyVec", &L1CaloJEM_JetEl_hadEnergyVec, &b_L1CaloJEM_JetEl_hadEnergyVec);
   fChain->SetBranchAddress("L1CaloJEM_JetEl_emErrorVec", &L1CaloJEM_JetEl_emErrorVec, &b_L1CaloJEM_JetEl_emErrorVec);
   fChain->SetBranchAddress("L1CaloJEM_JetEl_hadErrorVec", &L1CaloJEM_JetEl_hadErrorVec, &b_L1CaloJEM_JetEl_hadErrorVec);
   fChain->SetBranchAddress("L1CaloJEM_JetEl_linkErrorVec", &L1CaloJEM_JetEl_linkErrorVec, &b_L1CaloJEM_JetEl_linkErrorVec);
   fChain->SetBranchAddress("L1CaloJEM_Hits_n", &L1CaloJEM_Hits_n, &b_L1CaloJEM_Hits_n);
   fChain->SetBranchAddress("L1CaloJEM_Hits_crate", &L1CaloJEM_Hits_crate, &b_L1CaloJEM_Hits_crate);
   fChain->SetBranchAddress("L1CaloJEM_Hits_module", &L1CaloJEM_Hits_module, &b_L1CaloJEM_Hits_module);
   fChain->SetBranchAddress("L1CaloJEM_Hits_jetHits", &L1CaloJEM_Hits_jetHits, &b_L1CaloJEM_Hits_jetHits);
   fChain->SetBranchAddress("L1CaloJEM_Hits_jetHitsVec", &L1CaloJEM_Hits_jetHitsVec, &b_L1CaloJEM_Hits_jetHitsVec);
   fChain->SetBranchAddress("L1CaloJEM_Hits_peak", &L1CaloJEM_Hits_peak, &b_L1CaloJEM_Hits_peak);
   fChain->SetBranchAddress("L1CaloJEM_Hits_forward", &L1CaloJEM_Hits_forward, &b_L1CaloJEM_Hits_forward);
   fChain->SetBranchAddress("L1CaloJEM_EtSums_n", &L1CaloJEM_EtSums_n, &b_L1CaloJEM_EtSums_n);
   fChain->SetBranchAddress("L1CaloJEM_EtSums_crate", &L1CaloJEM_EtSums_crate, &b_L1CaloJEM_EtSums_crate);
   fChain->SetBranchAddress("L1CaloJEM_EtSums_module", &L1CaloJEM_EtSums_module, &b_L1CaloJEM_EtSums_module);
   fChain->SetBranchAddress("L1CaloJEM_EtSums_et", &L1CaloJEM_EtSums_et, &b_L1CaloJEM_EtSums_et);
   fChain->SetBranchAddress("L1CaloJEM_EtSums_ex", &L1CaloJEM_EtSums_ex, &b_L1CaloJEM_EtSums_ex);
   fChain->SetBranchAddress("L1CaloJEM_EtSums_ey", &L1CaloJEM_EtSums_ey, &b_L1CaloJEM_EtSums_ey);
   fChain->SetBranchAddress("L1CaloJEM_EtSums_etVec", &L1CaloJEM_EtSums_etVec, &b_L1CaloJEM_EtSums_etVec);
   fChain->SetBranchAddress("L1CaloJEM_EtSums_exVec", &L1CaloJEM_EtSums_exVec, &b_L1CaloJEM_EtSums_exVec);
   fChain->SetBranchAddress("L1CaloJEM_EtSums_eyVec", &L1CaloJEM_EtSums_eyVec, &b_L1CaloJEM_EtSums_eyVec);
   fChain->SetBranchAddress("L1CaloJEM_EtSums_peak", &L1CaloJEM_EtSums_peak, &b_L1CaloJEM_EtSums_peak);
   fChain->SetBranchAddress("L1CaloJEM_EtSums_forward", &L1CaloJEM_EtSums_forward, &b_L1CaloJEM_EtSums_forward);
   fChain->SetBranchAddress("L1CaloJEM_CMMJetHits_n", &L1CaloJEM_CMMJetHits_n, &b_L1CaloJEM_CMMJetHits_n);
   fChain->SetBranchAddress("L1CaloJEM_CMMJetHits_crate", &L1CaloJEM_CMMJetHits_crate, &b_L1CaloJEM_CMMJetHits_crate);
   fChain->SetBranchAddress("L1CaloJEM_CMMJetHits_dataID", &L1CaloJEM_CMMJetHits_dataID, &b_L1CaloJEM_CMMJetHits_dataID);
   fChain->SetBranchAddress("L1CaloJEM_CMMJetHits_hits", &L1CaloJEM_CMMJetHits_hits, &b_L1CaloJEM_CMMJetHits_hits);
   fChain->SetBranchAddress("L1CaloJEM_CMMJetHits_error", &L1CaloJEM_CMMJetHits_error, &b_L1CaloJEM_CMMJetHits_error);
   fChain->SetBranchAddress("L1CaloJEM_CMMJetHits_hitsVec", &L1CaloJEM_CMMJetHits_hitsVec, &b_L1CaloJEM_CMMJetHits_hitsVec);
   fChain->SetBranchAddress("L1CaloJEM_CMMJetHits_errorVec", &L1CaloJEM_CMMJetHits_errorVec, &b_L1CaloJEM_CMMJetHits_errorVec);
   fChain->SetBranchAddress("L1CaloJEM_CMMJetHits_peak", &L1CaloJEM_CMMJetHits_peak, &b_L1CaloJEM_CMMJetHits_peak);
   fChain->SetBranchAddress("L1CaloJEM_CMMEtSums_n", &L1CaloJEM_CMMEtSums_n, &b_L1CaloJEM_CMMEtSums_n);
   fChain->SetBranchAddress("L1CaloJEM_CMMEtSums_crate", &L1CaloJEM_CMMEtSums_crate, &b_L1CaloJEM_CMMEtSums_crate);
   fChain->SetBranchAddress("L1CaloJEM_CMMEtSums_dataID", &L1CaloJEM_CMMEtSums_dataID, &b_L1CaloJEM_CMMEtSums_dataID);
   fChain->SetBranchAddress("L1CaloJEM_CMMEtSums_et", &L1CaloJEM_CMMEtSums_et, &b_L1CaloJEM_CMMEtSums_et);
   fChain->SetBranchAddress("L1CaloJEM_CMMEtSums_ex", &L1CaloJEM_CMMEtSums_ex, &b_L1CaloJEM_CMMEtSums_ex);
   fChain->SetBranchAddress("L1CaloJEM_CMMEtSums_ey", &L1CaloJEM_CMMEtSums_ey, &b_L1CaloJEM_CMMEtSums_ey);
   fChain->SetBranchAddress("L1CaloJEM_CMMEtSums_etError", &L1CaloJEM_CMMEtSums_etError, &b_L1CaloJEM_CMMEtSums_etError);
   fChain->SetBranchAddress("L1CaloJEM_CMMEtSums_exError", &L1CaloJEM_CMMEtSums_exError, &b_L1CaloJEM_CMMEtSums_exError);
   fChain->SetBranchAddress("L1CaloJEM_CMMEtSums_eyError", &L1CaloJEM_CMMEtSums_eyError, &b_L1CaloJEM_CMMEtSums_eyError);
   fChain->SetBranchAddress("L1CaloJEM_CMMEtSums_etVec", &L1CaloJEM_CMMEtSums_etVec, &b_L1CaloJEM_CMMEtSums_etVec);
   fChain->SetBranchAddress("L1CaloJEM_CMMEtSums_exVec", &L1CaloJEM_CMMEtSums_exVec, &b_L1CaloJEM_CMMEtSums_exVec);
   fChain->SetBranchAddress("L1CaloJEM_CMMEtSums_eyVec", &L1CaloJEM_CMMEtSums_eyVec, &b_L1CaloJEM_CMMEtSums_eyVec);
   fChain->SetBranchAddress("L1CaloJEM_CMMEtSums_etErrorVec", &L1CaloJEM_CMMEtSums_etErrorVec, &b_L1CaloJEM_CMMEtSums_etErrorVec);
   fChain->SetBranchAddress("L1CaloJEM_CMMEtSums_exErrorVec", &L1CaloJEM_CMMEtSums_exErrorVec, &b_L1CaloJEM_CMMEtSums_exErrorVec);
   fChain->SetBranchAddress("L1CaloJEM_CMMEtSums_eyErrorVec", &L1CaloJEM_CMMEtSums_eyErrorVec, &b_L1CaloJEM_CMMEtSums_eyErrorVec);
   fChain->SetBranchAddress("L1CaloJEM_CMMEtSums_peak", &L1CaloJEM_CMMEtSums_peak, &b_L1CaloJEM_CMMEtSums_peak);
   fChain->SetBranchAddress("L1CaloJEM_RoI_n", &L1CaloJEM_RoI_n, &b_L1CaloJEM_RoI_n);
   fChain->SetBranchAddress("L1CaloJEM_RoI_crate", &L1CaloJEM_RoI_crate, &b_L1CaloJEM_RoI_crate);
   fChain->SetBranchAddress("L1CaloJEM_RoI_jem", &L1CaloJEM_RoI_jem, &b_L1CaloJEM_RoI_jem);
   fChain->SetBranchAddress("L1CaloJEM_RoI_frame", &L1CaloJEM_RoI_frame, &b_L1CaloJEM_RoI_frame);
   fChain->SetBranchAddress("L1CaloJEM_RoI_location", &L1CaloJEM_RoI_location, &b_L1CaloJEM_RoI_location);
   fChain->SetBranchAddress("L1CaloJEM_RoI_eta", &L1CaloJEM_RoI_eta, &b_L1CaloJEM_RoI_eta);
   fChain->SetBranchAddress("L1CaloJEM_RoI_phi", &L1CaloJEM_RoI_phi, &b_L1CaloJEM_RoI_phi);
   fChain->SetBranchAddress("L1CaloJEM_RoI_forward", &L1CaloJEM_RoI_forward, &b_L1CaloJEM_RoI_forward);
   fChain->SetBranchAddress("L1CaloJEM_RoI_hits", &L1CaloJEM_RoI_hits, &b_L1CaloJEM_RoI_hits);
   fChain->SetBranchAddress("L1CaloJEM_RoI_error", &L1CaloJEM_RoI_error, &b_L1CaloJEM_RoI_error);
   fChain->SetBranchAddress("L1CaloJEM_CMMRoI_jetEtHits", &L1CaloJEM_CMMRoI_jetEtHits, &b_L1CaloJEM_CMMRoI_jetEtHits);
   fChain->SetBranchAddress("L1CaloJEM_CMMRoI_sumEtHits", &L1CaloJEM_CMMRoI_sumEtHits, &b_L1CaloJEM_CMMRoI_sumEtHits);
   fChain->SetBranchAddress("L1CaloJEM_CMMRoI_missingEtHits", &L1CaloJEM_CMMRoI_missingEtHits, &b_L1CaloJEM_CMMRoI_missingEtHits);
   fChain->SetBranchAddress("L1CaloJEM_CMMRoI_ex", &L1CaloJEM_CMMRoI_ex, &b_L1CaloJEM_CMMRoI_ex);
   fChain->SetBranchAddress("L1CaloJEM_CMMRoI_ey", &L1CaloJEM_CMMRoI_ey, &b_L1CaloJEM_CMMRoI_ey);
   fChain->SetBranchAddress("L1CaloJEM_CMMRoI_et", &L1CaloJEM_CMMRoI_et, &b_L1CaloJEM_CMMRoI_et);
   fChain->SetBranchAddress("L1CaloJEM_CMMRoI_jetEtError", &L1CaloJEM_CMMRoI_jetEtError, &b_L1CaloJEM_CMMRoI_jetEtError);
   fChain->SetBranchAddress("L1CaloJEM_CMMRoI_sumEtError", &L1CaloJEM_CMMRoI_sumEtError, &b_L1CaloJEM_CMMRoI_sumEtError);
   fChain->SetBranchAddress("L1CaloJEM_CMMRoI_missingEtError", &L1CaloJEM_CMMRoI_missingEtError, &b_L1CaloJEM_CMMRoI_missingEtError);
   fChain->SetBranchAddress("L1CaloJEM_CMMRoI_exError", &L1CaloJEM_CMMRoI_exError, &b_L1CaloJEM_CMMRoI_exError);
   fChain->SetBranchAddress("L1CaloJEM_CMMRoI_eyError", &L1CaloJEM_CMMRoI_eyError, &b_L1CaloJEM_CMMRoI_eyError);
   fChain->SetBranchAddress("L1CaloJEM_CMMRoI_etError", &L1CaloJEM_CMMRoI_etError, &b_L1CaloJEM_CMMRoI_etError);
   fChain->SetBranchAddress("L1CaloJEM_CMMRoI_jetEtRoiWord", &L1CaloJEM_CMMRoI_jetEtRoiWord, &b_L1CaloJEM_CMMRoI_jetEtRoiWord);
   fChain->SetBranchAddress("L1CaloJEM_CMMRoI_energyEtRoiWord0", &L1CaloJEM_CMMRoI_energyEtRoiWord0, &b_L1CaloJEM_CMMRoI_energyEtRoiWord0);
   fChain->SetBranchAddress("L1CaloJEM_CMMRoI_energyEtRoiWord1", &L1CaloJEM_CMMRoI_energyEtRoiWord1, &b_L1CaloJEM_CMMRoI_energyEtRoiWord1);
   fChain->SetBranchAddress("L1CaloJEM_CMMRoI_energyEtRoiWord2", &L1CaloJEM_CMMRoI_energyEtRoiWord2, &b_L1CaloJEM_CMMRoI_energyEtRoiWord2);
   fChain->SetBranchAddress("L1CaloRODHeader_nHeaders", &L1CaloRODHeader_nHeaders, &b_L1CaloRODHeader_nHeaders);
   fChain->SetBranchAddress("L1CaloRODHeader_version", &L1CaloRODHeader_version, &b_L1CaloRODHeader_version);
   fChain->SetBranchAddress("L1CaloRODHeader_majorVersion", &L1CaloRODHeader_majorVersion, &b_L1CaloRODHeader_majorVersion);
   fChain->SetBranchAddress("L1CaloRODHeader_minorVersion", &L1CaloRODHeader_minorVersion, &b_L1CaloRODHeader_minorVersion);
   fChain->SetBranchAddress("L1CaloRODHeader_sourceID", &L1CaloRODHeader_sourceID, &b_L1CaloRODHeader_sourceID);
   fChain->SetBranchAddress("L1CaloRODHeader_subDetectorID", &L1CaloRODHeader_subDetectorID, &b_L1CaloRODHeader_subDetectorID);
   fChain->SetBranchAddress("L1CaloRODHeader_moduleID", &L1CaloRODHeader_moduleID, &b_L1CaloRODHeader_moduleID);
   fChain->SetBranchAddress("L1CaloRODHeader_crate", &L1CaloRODHeader_crate, &b_L1CaloRODHeader_crate);
   fChain->SetBranchAddress("L1CaloRODHeader_sLink", &L1CaloRODHeader_sLink, &b_L1CaloRODHeader_sLink);
   fChain->SetBranchAddress("L1CaloRODHeader_dataType", &L1CaloRODHeader_dataType, &b_L1CaloRODHeader_dataType);
   fChain->SetBranchAddress("L1CaloRODHeader_run", &L1CaloRODHeader_run, &b_L1CaloRODHeader_run);
   fChain->SetBranchAddress("L1CaloRODHeader_runType", &L1CaloRODHeader_runType, &b_L1CaloRODHeader_runType);
   fChain->SetBranchAddress("L1CaloRODHeader_runNumber", &L1CaloRODHeader_runNumber, &b_L1CaloRODHeader_runNumber);
   fChain->SetBranchAddress("L1CaloRODHeader_extendedL1ID", &L1CaloRODHeader_extendedL1ID, &b_L1CaloRODHeader_extendedL1ID);
   fChain->SetBranchAddress("L1CaloRODHeader_ecrID", &L1CaloRODHeader_ecrID, &b_L1CaloRODHeader_ecrID);
   fChain->SetBranchAddress("L1CaloRODHeader_l1ID", &L1CaloRODHeader_l1ID, &b_L1CaloRODHeader_l1ID);
   fChain->SetBranchAddress("L1CaloRODHeader_bunchCrossing", &L1CaloRODHeader_bunchCrossing, &b_L1CaloRODHeader_bunchCrossing);
   fChain->SetBranchAddress("L1CaloRODHeader_l1TriggerType", &L1CaloRODHeader_l1TriggerType, &b_L1CaloRODHeader_l1TriggerType);
   fChain->SetBranchAddress("L1CaloRODHeader_detEventType", &L1CaloRODHeader_detEventType, &b_L1CaloRODHeader_detEventType);
   fChain->SetBranchAddress("L1CaloRODHeader_orbitCount", &L1CaloRODHeader_orbitCount, &b_L1CaloRODHeader_orbitCount);
   fChain->SetBranchAddress("L1CaloRODHeader_stepNumber", &L1CaloRODHeader_stepNumber, &b_L1CaloRODHeader_stepNumber);
   fChain->SetBranchAddress("L1CaloRODHeader_stepType", &L1CaloRODHeader_stepType, &b_L1CaloRODHeader_stepType);
   fChain->SetBranchAddress("L1CaloRODHeader_bcnMismatch", &L1CaloRODHeader_bcnMismatch, &b_L1CaloRODHeader_bcnMismatch);
   fChain->SetBranchAddress("L1CaloRODHeader_gLinkTimeout", &L1CaloRODHeader_gLinkTimeout, &b_L1CaloRODHeader_gLinkTimeout);
   fChain->SetBranchAddress("L1CaloRODHeader_dataTransportError", &L1CaloRODHeader_dataTransportError, &b_L1CaloRODHeader_dataTransportError);
   fChain->SetBranchAddress("L1CaloRODHeader_rodFifoOverflow", &L1CaloRODHeader_rodFifoOverflow, &b_L1CaloRODHeader_rodFifoOverflow);
   fChain->SetBranchAddress("L1CaloRODHeader_lvdsLinkError", &L1CaloRODHeader_lvdsLinkError, &b_L1CaloRODHeader_lvdsLinkError);
   fChain->SetBranchAddress("L1CaloRODHeader_cmmParityError", &L1CaloRODHeader_cmmParityError, &b_L1CaloRODHeader_cmmParityError);
   fChain->SetBranchAddress("L1CaloRODHeader_gLinkError", &L1CaloRODHeader_gLinkError, &b_L1CaloRODHeader_gLinkError);
   fChain->SetBranchAddress("L1CaloRODHeader_limitedRoISet", &L1CaloRODHeader_limitedRoISet, &b_L1CaloRODHeader_limitedRoISet);
   fChain->SetBranchAddress("L1CaloRODHeader_triggerTypeTimeout", &L1CaloRODHeader_triggerTypeTimeout, &b_L1CaloRODHeader_triggerTypeTimeout);
#endif

#ifndef L1CALO_ONLY
   fChain->SetBranchAddress("MemRSS", &MemRSS, &b_MemRSS);
   fChain->SetBranchAddress("MemVSize", &MemVSize, &b_MemVSize);
   fChain->SetBranchAddress("TimeTotal", &TimeTotal, &b_TimeTotal);
   fChain->SetBranchAddress("TimeSum", &TimeSum, &b_TimeSum);
   fChain->SetBranchAddress("TimeEventCounter", &TimeEventCounter, &b_TimeEventCounter);
   fChain->SetBranchAddress("TimeInDetPixelRawDataProvider", &TimeInDetPixelRawDataProvider, &b_TimeInDetPixelRawDataProvider);
   fChain->SetBranchAddress("TimeInDetSCTRawDataProvider", &TimeInDetSCTRawDataProvider, &b_TimeInDetSCTRawDataProvider);
   fChain->SetBranchAddress("TimeInDetTRTRawDataProvider", &TimeInDetTRTRawDataProvider, &b_TimeInDetTRTRawDataProvider);
   fChain->SetBranchAddress("TimeMuonMdtRawDataProvider", &TimeMuonMdtRawDataProvider, &b_TimeMuonMdtRawDataProvider);
   fChain->SetBranchAddress("TimeMuonRpcRawDataProvider", &TimeMuonRpcRawDataProvider, &b_TimeMuonRpcRawDataProvider);
   fChain->SetBranchAddress("TimeMuonTgcRawDataProvider", &TimeMuonTgcRawDataProvider, &b_TimeMuonTgcRawDataProvider);
   fChain->SetBranchAddress("TimeTrigConfDataIOVChanger", &TimeTrigConfDataIOVChanger, &b_TimeTrigConfDataIOVChanger);
   fChain->SetBranchAddress("TimeRoIBResultToAOD", &TimeRoIBResultToAOD, &b_TimeRoIBResultToAOD);
   fChain->SetBranchAddress("TimeTrigBSExtraction", &TimeTrigBSExtraction, &b_TimeTrigBSExtraction);
   fChain->SetBranchAddress("TimeTrigDecMaker", &TimeTrigDecMaker, &b_TimeTrigDecMaker);
   fChain->SetBranchAddress("TimeMainMonManager", &TimeMainMonManager, &b_TimeMainMonManager);
   fChain->SetBranchAddress("TimeInDetPixelClusterization", &TimeInDetPixelClusterization, &b_TimeInDetPixelClusterization);
   fChain->SetBranchAddress("TimeInDetSCT_Clusterization", &TimeInDetSCT_Clusterization, &b_TimeInDetSCT_Clusterization);
   fChain->SetBranchAddress("TimeInDetSiTrackerSpacePointFinder", &TimeInDetSiTrackerSpacePointFinder, &b_TimeInDetSiTrackerSpacePointFinder);
   fChain->SetBranchAddress("TimeSiCTBTracking", &TimeSiCTBTracking, &b_TimeSiCTBTracking);
   fChain->SetBranchAddress("TimePixel_CTBTracking", &TimePixel_CTBTracking, &b_TimePixel_CTBTracking);
   fChain->SetBranchAddress("TimeSCT_CTBTracking", &TimeSCT_CTBTracking, &b_TimeSCT_CTBTracking);
   fChain->SetBranchAddress("TimeInDetTRT_RIO_Maker", &TimeInDetTRT_RIO_Maker, &b_TimeInDetTRT_RIO_Maker);
   fChain->SetBranchAddress("TimeTRT_CTBTrackingPhase", &TimeTRT_CTBTrackingPhase, &b_TimeTRT_CTBTrackingPhase);
   fChain->SetBranchAddress("TimeTRTSegmentsFinder_ECphase", &TimeTRTSegmentsFinder_ECphase, &b_TimeTRTSegmentsFinder_ECphase);
   fChain->SetBranchAddress("TimeInDetCosmicsEventPhase", &TimeInDetCosmicsEventPhase, &b_TimeInDetCosmicsEventPhase);
   fChain->SetBranchAddress("TimeInDetTRT_RIO_MakerCosmics", &TimeInDetTRT_RIO_MakerCosmics, &b_TimeInDetTRT_RIO_MakerCosmics);
   fChain->SetBranchAddress("TimeInDetCTBTracking", &TimeInDetCTBTracking, &b_TimeInDetCTBTracking);
   fChain->SetBranchAddress("TimeTRT_CTBTracking", &TimeTRT_CTBTracking, &b_TimeTRT_CTBTracking);
   fChain->SetBranchAddress("TimeTRTSegmentsFinderBC", &TimeTRTSegmentsFinderBC, &b_TimeTRTSegmentsFinderBC);
   fChain->SetBranchAddress("TimeTRTSegmentsFinder_EC", &TimeTRTSegmentsFinder_EC, &b_TimeTRTSegmentsFinder_EC);
   fChain->SetBranchAddress("TimeTRT_SegmentsToTrack_Endcap", &TimeTRT_SegmentsToTrack_Endcap, &b_TimeTRT_SegmentsToTrack_Endcap);
   fChain->SetBranchAddress("TimeIdTrackCopyAmbiSolver_0", &TimeIdTrackCopyAmbiSolver_0, &b_TimeIdTrackCopyAmbiSolver_0);
   fChain->SetBranchAddress("TimeIdTrackCopyAmbiSolver_1", &TimeIdTrackCopyAmbiSolver_1, &b_TimeIdTrackCopyAmbiSolver_1);
   fChain->SetBranchAddress("TimeIdTrackCopyAmbiSolver_2", &TimeIdTrackCopyAmbiSolver_2, &b_TimeIdTrackCopyAmbiSolver_2);
   fChain->SetBranchAddress("TimeIdTrackCopyAmbiSolver_3", &TimeIdTrackCopyAmbiSolver_3, &b_TimeIdTrackCopyAmbiSolver_3);
   fChain->SetBranchAddress("TimeIdTrackCopyAmbiSolver_4", &TimeIdTrackCopyAmbiSolver_4, &b_TimeIdTrackCopyAmbiSolver_4);
   fChain->SetBranchAddress("TimeIdTrackCopyAmbiSolver_final", &TimeIdTrackCopyAmbiSolver_final, &b_TimeIdTrackCopyAmbiSolver_final);
   fChain->SetBranchAddress("TimeInDetTrackCollectionMerger", &TimeInDetTrackCollectionMerger, &b_TimeInDetTrackCollectionMerger);
   fChain->SetBranchAddress("TimeInDetCopyAlg", &TimeInDetCopyAlg, &b_TimeInDetCopyAlg);
   fChain->SetBranchAddress("TimeInDetParticleCreation", &TimeInDetParticleCreation, &b_TimeInDetParticleCreation);
   fChain->SetBranchAddress("TimeTileRChMaker", &TimeTileRChMaker, &b_TimeTileRChMaker);
   fChain->SetBranchAddress("TimeLArRawChannelBuilder", &TimeLArRawChannelBuilder, &b_TimeLArRawChannelBuilder);
   fChain->SetBranchAddress("TimeLArDigitThinner", &TimeLArDigitThinner, &b_TimeLArDigitThinner);
   fChain->SetBranchAddress("TimeTileDigitsFilter", &TimeTileDigitsFilter, &b_TimeTileDigitsFilter);
   fChain->SetBranchAddress("TimeCaloCellMaker", &TimeCaloCellMaker, &b_TimeCaloCellMaker);
   fChain->SetBranchAddress("TimeEmTowerBldr", &TimeEmTowerBldr, &b_TimeEmTowerBldr);
   fChain->SetBranchAddress("TimeLArClusterMaker", &TimeLArClusterMaker, &b_TimeLArClusterMaker);
   fChain->SetBranchAddress("TimeLAr7_11NocorrClusterMaker", &TimeLAr7_11NocorrClusterMaker, &b_TimeLAr7_11NocorrClusterMaker);
   fChain->SetBranchAddress("TimeCaloTopoCluster", &TimeCaloTopoCluster, &b_TimeCaloTopoCluster);
   fChain->SetBranchAddress("TimeCaloCell2TopoClusterMapper", &TimeCaloCell2TopoClusterMapper, &b_TimeCaloCell2TopoClusterMapper);
   fChain->SetBranchAddress("TimeCaloClusterTopoEM430Getter", &TimeCaloClusterTopoEM430Getter, &b_TimeCaloClusterTopoEM430Getter);
   fChain->SetBranchAddress("TimeEMCell2TopoCluster430", &TimeEMCell2TopoCluster430, &b_TimeEMCell2TopoCluster430);
   fChain->SetBranchAddress("TimeTileLookForMuAlg", &TimeTileLookForMuAlg, &b_TimeTileLookForMuAlg);
   fChain->SetBranchAddress("TimeTileMuonFitter", &TimeTileMuonFitter, &b_TimeTileMuonFitter);
   fChain->SetBranchAddress("TimeMdtRdoToMdtPrepData", &TimeMdtRdoToMdtPrepData, &b_TimeMdtRdoToMdtPrepData);
   fChain->SetBranchAddress("TimeRpcRdoToRpcPrepData", &TimeRpcRdoToRpcPrepData, &b_TimeRpcRdoToRpcPrepData);
   fChain->SetBranchAddress("TimeTgcRdoToTgcPrepData", &TimeTgcRdoToTgcPrepData, &b_TimeTgcRdoToTgcPrepData);
   fChain->SetBranchAddress("TimeRpcClusterBuilderPRD", &TimeRpcClusterBuilderPRD, &b_TimeRpcClusterBuilderPRD);
   fChain->SetBranchAddress("TimeMboyDigiEmptyLoop", &TimeMboyDigiEmptyLoop, &b_TimeMboyDigiEmptyLoop);
   fChain->SetBranchAddress("TimeMboyRec", &TimeMboyRec, &b_TimeMboyRec);
   fChain->SetBranchAddress("TimeMooSegmentMaker", &TimeMooSegmentMaker, &b_TimeMooSegmentMaker);
   fChain->SetBranchAddress("TimeMuonCombiTrackBuilder", &TimeMuonCombiTrackBuilder, &b_TimeMuonCombiTrackBuilder);
   fChain->SetBranchAddress("TimeMuidMooreTPCreator", &TimeMuidMooreTPCreator, &b_TimeMuidMooreTPCreator);
   fChain->SetBranchAddress("TimeInitializeMuonClusters", &TimeInitializeMuonClusters, &b_TimeInitializeMuonClusters);
   fChain->SetBranchAddress("TimeCaloTrkMuIdAlg", &TimeCaloTrkMuIdAlg, &b_TimeCaloTrkMuIdAlg);
   fChain->SetBranchAddress("TimeCaloTrkMuIdAlg2", &TimeCaloTrkMuIdAlg2, &b_TimeCaloTrkMuIdAlg2);
   fChain->SetBranchAddress("TimeMuTagMasterIMO", &TimeMuTagMasterIMO, &b_TimeMuTagMasterIMO);
   fChain->SetBranchAddress("TimeCombMuonRefit", &TimeCombMuonRefit, &b_TimeCombMuonRefit);
   fChain->SetBranchAddress("TimeMergeMuonCollections", &TimeMergeMuonCollections, &b_TimeMergeMuonCollections);
   fChain->SetBranchAddress("TimeMakeAODMuons", &TimeMakeAODMuons, &b_TimeMakeAODMuons);
   fChain->SetBranchAddress("TimeFinalizeMuonClusters", &TimeFinalizeMuonClusters, &b_TimeFinalizeMuonClusters);
   fChain->SetBranchAddress("TimeCmbTowerBldr", &TimeCmbTowerBldr, &b_TimeCmbTowerBldr);
   fChain->SetBranchAddress("TimeTowerJetInput", &TimeTowerJetInput, &b_TimeTowerJetInput);
   fChain->SetBranchAddress("TimeCone4H1TowerJets", &TimeCone4H1TowerJets, &b_TimeCone4H1TowerJets);
   fChain->SetBranchAddress("TimeMETAlg", &TimeMETAlg, &b_TimeMETAlg);
   fChain->SetBranchAddress("TimeInDetGlobalManager", &TimeInDetGlobalManager, &b_TimeInDetGlobalManager);
   fChain->SetBranchAddress("TimePixelMonManager", &TimePixelMonManager, &b_TimePixelMonManager);
   fChain->SetBranchAddress("TimeSCTMonManager", &TimeSCTMonManager, &b_TimeSCTMonManager);
   fChain->SetBranchAddress("TimeTRTMonManager", &TimeTRTMonManager, &b_TimeTRTMonManager);
   fChain->SetBranchAddress("TimeIDAlignMonManager", &TimeIDAlignMonManager, &b_TimeIDAlignMonManager);
   fChain->SetBranchAddress("TimeGlobalMonManager", &TimeGlobalMonManager, &b_TimeGlobalMonManager);
   fChain->SetBranchAddress("TimeJetElementMaker", &TimeJetElementMaker, &b_TimeJetElementMaker);
   fChain->SetBranchAddress("TimeCPMTowerMaker", &TimeCPMTowerMaker, &b_TimeCPMTowerMaker);
   fChain->SetBranchAddress("TimeEmTauTrigger", &TimeEmTauTrigger, &b_TimeEmTauTrigger);
   fChain->SetBranchAddress("TimeEnergyTrigger", &TimeEnergyTrigger, &b_TimeEnergyTrigger);
   fChain->SetBranchAddress("TimeJetTrigger", &TimeJetTrigger, &b_TimeJetTrigger);
   fChain->SetBranchAddress("TimeROD", &TimeROD, &b_TimeROD);
   fChain->SetBranchAddress("TimeJEPCMMMaker", &TimeJEPCMMMaker, &b_TimeJEPCMMMaker);
   fChain->SetBranchAddress("TimeCPCMMMaker", &TimeCPCMMMaker, &b_TimeCPCMMMaker);
   fChain->SetBranchAddress("TimeL1CaloMonManager", &TimeL1CaloMonManager, &b_TimeL1CaloMonManager);
   fChain->SetBranchAddress("TimeTriggerTowerMaker", &TimeTriggerTowerMaker, &b_TimeTriggerTowerMaker);
   fChain->SetBranchAddress("TimeL1MonManager", &TimeL1MonManager, &b_TimeL1MonManager);
   fChain->SetBranchAddress("TimeCTMonManager", &TimeCTMonManager, &b_TimeCTMonManager);
   fChain->SetBranchAddress("TimeHLTMonManager", &TimeHLTMonManager, &b_TimeHLTMonManager);
   fChain->SetBranchAddress("TimeTileTowerBldr", &TimeTileTowerBldr, &b_TimeTileTowerBldr);
   fChain->SetBranchAddress("TimeTileTopoCluster", &TimeTileTopoCluster, &b_TimeTileTopoCluster);
   fChain->SetBranchAddress("TimeTileCell2TopoClusterMapper", &TimeTileCell2TopoClusterMapper, &b_TimeTileCell2TopoClusterMapper);
   fChain->SetBranchAddress("TimeManagedAthenaTileMon", &TimeManagedAthenaTileMon, &b_TimeManagedAthenaTileMon);
   fChain->SetBranchAddress("TimeLArMonManager", &TimeLArMonManager, &b_TimeLArMonManager);
   fChain->SetBranchAddress("TimeJetMonManager", &TimeJetMonManager, &b_TimeJetMonManager);
   fChain->SetBranchAddress("TimeJetTagMonManager", &TimeJetTagMonManager, &b_TimeJetTagMonManager);
   fChain->SetBranchAddress("TimeMuonRawMonManager", &TimeMuonRawMonManager, &b_TimeMuonRawMonManager);
   fChain->SetBranchAddress("TimeCBNT_AthenaAware", &TimeCBNT_AthenaAware, &b_TimeCBNT_AthenaAware);
   fChain->SetBranchAddress("TimeCreateLumiBlockCollectionFromFile", &TimeCreateLumiBlockCollectionFromFile, &b_TimeCreateLumiBlockCollectionFromFile);
   fChain->SetBranchAddress("TimeStreamESD", &TimeStreamESD, &b_TimeStreamESD);
   fChain->SetBranchAddress("TimeStreamESD_FH", &TimeStreamESD_FH, &b_TimeStreamESD_FH);
   fChain->SetBranchAddress("TimeStream2Filter", &TimeStream2Filter, &b_TimeStream2Filter);
   fChain->SetBranchAddress("TimeComTagWriter", &TimeComTagWriter, &b_TimeComTagWriter);
   fChain->SetBranchAddress("TimeStreamTAGCOM", &TimeStreamTAGCOM, &b_TimeStreamTAGCOM);
   fChain->SetBranchAddress("TimeAANTupleStream", &TimeAANTupleStream, &b_TimeAANTupleStream);
#endif

   Notify();
}

Bool_t cbntClass::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void cbntClass::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t cbntClass::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef cbntClass_cxx
