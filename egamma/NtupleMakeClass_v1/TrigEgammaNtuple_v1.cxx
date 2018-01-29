#define TrigEgammaNtuple_v1_cxx
#include "TrigEgammaNtuple_v1.h"
#include "TH2.h"
#include "TH1.h"
#include <cmath>

//#include "GoodRunsLists/TGoodRunsListReader.h" // decomment to use GRL

double getDPhi(double phi1, double phi2) {
  double deltaPhi=fabs(phi1-phi2);
  if (deltaPhi>M_PI) deltaPhi=2*M_PI-deltaPhi;
  return deltaPhi;
}

void TrigEgammaNtuple_v1::DumpTrigger(std::string level, bool verbose=false) {
  std::cout << std::endl << "Trigger information for the event: " << Event_evt_number << std::endl;
  if ( level.find("L1")!=std::string::npos || level=="ALL") {
    std::cout << "** L1 chains: " << std::endl;
    std::map<string,bool>::iterator it;
    for (it=Trigger_L1passed->begin();it!=Trigger_L1passed->end();it++) {
      if (it->second)                std::cout << "   - " << it->first << " is PASSED" << std::endl;
      if (verbose && !(it->second) ) std::cout << "   - " << it->first << " is NOT passed" << std::endl;
    }
  }
  if ( level.find("L2")!=std::string::npos || level=="ALL") {
    std::cout << "** L2 chains: " << std::endl;
    std::map<string,bool>::iterator it;
    for (it=Trigger_L2passed->begin();it!=Trigger_L2passed->end();it++) {
      if (it->second)                std::cout << "   - " << it->first << " is PASSED" << std::endl;
      if (verbose && !(it->second) ) std::cout << "   - " << it->first << " is NOT passed" << std::endl;
    }
  }
  if ( level.find("EF")!=std::string::npos || level=="ALL") {
    std::cout << "** EF chains: " << std::endl;
    std::map<string,bool>::iterator it;
    for (it=Trigger_EFpassed->begin();it!=Trigger_EFpassed->end();it++) {
      if (it->second)                std::cout << "   - " << it->first << " is PASSED" << std::endl;
      if (verbose && !(it->second) ) std::cout << "   - " << it->first << " is NOT passed" << std::endl;
    }
  }
}

void TrigEgammaNtuple_v1::DumpL1(unsigned int i, bool verbose=false) {
  std::cout << std::endl << "Information on L1Cluster " << i << std::endl;
  std::cout << " Et: " << (*L1ROI_EMet)[i] << " | Eta: " << (*L1ROI_eta)[i] << " | Phi: " << (*L1ROI_phi)[i] << std::endl;
  if (verbose) {
    std::cout << "RoIWord: " << (*L1ROI_ROIword)[i] << std::endl;
    std::cout << "Core: " << (*L1ROI_Core)[i] << " | HadCore: " << (*L1ROI_Hadcore)[i] << " | EM_iso: " << (*L1ROI_EMiso)[i] << " | HadIso: " << (*L1ROI_Hadiso)[i] << std::endl;
  }
  map<string,bool>::iterator it;
  for(it=L1ROI_trigRes[i].begin();it!=L1ROI_trigRes[i].end();it++) {
    if ( it->second )              std::cout << " - Chain " << it->first << " PASSED " << std::endl;
    if (verbose && !(it->second) ) std::cout << " - Chain " << it->first << " NOT PASSED " << std::endl;
  } 
}

void TrigEgammaNtuple_v1::DumpL2Cluster(unsigned int i, bool verbose=false) {
  std::cout << std::endl << "Information on TrigEMCluster " << i << " ( collection: " << (*TrigEMCluster_coll)[i] << " ) "<<  std::endl;
  std::cout << " Et: " << (*TrigEMCluster_et)[i] << " | Eta: " << (*TrigEMCluster_eta)[i] << " | Phi: " << (*TrigEMCluster_phi)[i] << std::endl;
  double EtHad=(*TrigEMCluster_ehad1)[i]/cosh(fabs((*TrigEMCluster_eta)[i]));
  double rEta=0;
  if ( (*TrigEMCluster_e277)[i]!= 0 ) rEta=(*TrigEMCluster_e237)[i]/(*TrigEMCluster_e277)[i];
  double eRatio=-1;
  if ( ((*TrigEMCluster_emaxs1)[i]+(*TrigEMCluster_e2tsts1)[i])!=0) 
    eRatio=((*TrigEMCluster_emaxs1)[i]-(*TrigEMCluster_e2tsts1)[i])/((*TrigEMCluster_emaxs1)[i]+(*TrigEMCluster_e2tsts1)[i]);
  std::cout << " HadEt: " << EtHad/(*TrigEMCluster_et)[i] << " | Reta: " << rEta << " | Eratio: " << eRatio << std::endl;
  if ( verbose ) {
    std::cout << "Energy= " << (*TrigEMCluster_energy)[i] << std::endl;
    std::cout << "E237= " << (*TrigEMCluster_e237)[i] << " , E277= " << (*TrigEMCluster_e277)[i] << " , fracs1= " << (*TrigEMCluster_fracs1)[i] << " , weta2= " << (*TrigEMCluster_weta2)[i] << std::endl;
    std::cout << "ehad1= " << (*TrigEMCluster_ehad1)[i] << " , Eta1= " << (*TrigEMCluster_Eta1)[i] << " , emaxs1= " << (*TrigEMCluster_emaxs1)[i] << " , e2tsts1= " << (*TrigEMCluster_e2tsts1)[i] << " , quality= "<< (*TrigEMCluster_quality)[i] << std::endl;
    for (unsigned int j=0;j<(*TrigEMCluster_energyInSample)[i].size();j++) {
      double val=(*TrigEMCluster_energyInSample)[i][j];
      if (val!=0) std::cout << "Energy in layer " << j << " is " << val << " MeV" << std::endl;
    }
  }
  map<string,bool>::iterator it;
  for(it=TrigEMCluster_trigRes[i].begin();it!=TrigEMCluster_trigRes[i].end();it++) {
    if ( it->second ) std::cout << " - Chain " << it->first << " PASSED " << std::endl;
    else              std::cout << " - Chain " << it->first << " NOT PASSED " << std::endl;
  }
}

void TrigEgammaNtuple_v1::DumpL2Photon(unsigned int i, bool verbose=false) {
  std::cout << std::endl << "Information on TrigPhoton " << i << std::endl;
  std::cout << " Et: "    << (*TrigPhoton_Et)[i] << " | Eta: " << (*TrigPhoton_Eta)[i] << " | Phi: " << (*TrigPhoton_Phi)[i] << std::endl;
  std::cout << " HadEt: " << (*TrigPhoton_HadEt)[i]/(*TrigPhoton_Et)[i] << " | Reta: " << (*TrigPhoton_rCore)[i] << " | Eratio: " << (*TrigPhoton_energyRatio)[i] << std::endl;
  std::cout << " linked to EMCluster " << (*TrigPhoton_ClusIndex)[i] << std::endl;
  if (verbose) {
    std::cout << "Energy= " << (*TrigPhoton_E)[i] << std::endl;
    std::cout << "RoIID= " << (*TrigPhoton_roiID)[i] << " , isValid= " << (*TrigPhoton_isValid)[i] << std::endl;
    std::cout << "HadEt= " << (*TrigPhoton_HadEt)[i] << std::endl;
    std::cout << "dEta= " << (*TrigPhoton_dEta)[i] << " , dPhi= " << (*TrigPhoton_dPhi)[i] << std::endl;
  }
  map<string,bool>::iterator it;
  for(it=TrigPhoton_trigRes[i].begin();it!=TrigPhoton_trigRes[i].end();it++) {
    if ( it->second ) std::cout << " - Chain " << it->first << " PASSED " << std::endl;
    else              std::cout << " - Chain " << it->first << " NOT PASSED " << std::endl;
  }
}

void TrigEgammaNtuple_v1::DumpL2Track(unsigned int i, bool verbose=false) {
  std::cout << std::endl << "Information on TrigInDetTrack " << i << " from Collection: " << (*TrigInDetTrack_slice)[i] << std::endl;
  std::cout << " AlgoId= " << (*TrigInDetTrack_AlgoId)[i] << " | chi2= " << (*TrigInDetTrack_chi2)[i] << std::endl;
  std::cout << " Pt= " << (*TrigInDetTrack_pT)[i] << " | Eta= " << (*TrigInDetTrack_eta)[i] << " | Phi= " << (*TrigInDetTrack_phi0)[i] << std::endl;
  std::cout << " a0= " << (*TrigInDetTrack_a0)[i] << " | z0= " << (*TrigInDetTrack_z0)[i]<< std::endl;
  std::cout << " BL_Hits: " << (*TrigInDetTrack_BL_hits)[i] << " | Pixel_hits= " << (*TrigInDetTrack_Pixel_hits)[i] << " | SCT_hits= " << (*TrigInDetTrack_SCT_hits)[i] <<  " | NStrawHits= " << (*TrigInDetTrack_NStrawHits)[i] << " | NTRHits= " << (*TrigInDetTrack_NTRHits)[i] << std::endl;
  if (verbose) {
    std::cout << "NStrawHits= " << (*TrigInDetTrack_NStrawHits)[i] << " , NStraw= " << (*TrigInDetTrack_NStraw)[i] << " , NStrawTime= " << (*TrigInDetTrack_NStrawTime)[i] << std::endl;
    std::cout << " err_a0= " << (*TrigInDetTrack_ea0)[i] << " | err_z0= " << (*TrigInDetTrack_ez0)[i] << std::endl;
    std::cout << " err_phi0= " << (*TrigInDetTrack_ephi0)[i] << " | err_eta= " << (*TrigInDetTrack_eeta)[i] << " | err_pT= " << (*TrigInDetTrack_epT)[i] << std::endl;
  }  
  map<string,bool>::iterator it;
  for(it=TrigInDetTrack_trigRes[i].begin();it!=TrigInDetTrack_trigRes[i].end();it++) {
    if ( it->second ) std::cout << " - Chain " << it->first << " PASSED " << std::endl;
    else              std::cout << " - Chain " << it->first << " NOT PASSED " << std::endl;
  }
}

void TrigEgammaNtuple_v1::DumpL2Electron(unsigned int i, bool verbose=false) {
  std::cout << std::endl << "TrigElectron " << i << std::endl;
  double etaL2=(*TrigElectron_Eta)[i];
  double etL2=(*TrigElectron_E)[i]/cosh(fabs(etaL2));
  std::cout << " Et: " << etL2 << " | Eta: " << (*TrigElectron_Eta)[i] << " | Phi: " << (*TrigElectron_Phi)[i] << std::endl;
  std::cout << " Reta: " << (*TrigElectron_Rcore)[i] << " | Ethad: " << (*TrigElectron_EThad)[i]/etL2 << " | eratio: " << (*TrigElectron_Eratio)[i] << std::endl;
  std::cout << " trkPt: " << (*TrigElectron_Pt_track)[i] << " | algo: " << (*TrigElectron_trackAlgo)[i] << std::endl;
  std::cout << " link to EMCluster: " << (*TrigElectron_ClusIndex)[i] << " || link to Track: " << (*TrigElectron_TrackIndex)[i] << std::endl;
  if (verbose) {
    std::cout << "Energy= " << (*TrigElectron_E)[i] << " , Pt= " << (*TrigElectron_Pt)[i] << std::endl;
    std::cout << "RoIID= " << (*TrigElectron_roiId)[i] << " , RoIWord= " << (*TrigElectron_roiWord)[i] << " , isValid= " << (*TrigElectron_isValid)[i] << std::endl;
    std::cout << " charge= " << (*TrigElectron_charge)[i] << " , EtOverPt= " << (*TrigElectron_EtOverPt)[i] << std::endl;
    std::cout << "TrackZvtx= " << (*TrigElectron_Zvtx)[i] << " , TrackZvtx_err= " << (*TrigElectron_err_Zvtx)[i] << std::endl;
    std::cout << "TrackPt= " << (*TrigElectron_Pt_track)[i] << " , TrackPt_err= " << (*TrigElectron_err_Pt)[i] << std::endl;
    std::cout << "TrackEtaAtCalo= " << (*TrigElectron_trkEtaAtCalo)[i] << " , TrackEta_err= " << (*TrigElectron_err_Eta)[i] << std::endl;
    std::cout << "TrackPhiAtCalo= " << (*TrigElectron_trkPhiAtCalo)[i] << " , TrackPhi_err= " << (*TrigElectron_err_Phi)[i] << std::endl;
  }
  map<string,bool>::iterator it;
  for(it=TrigElectron_trigRes[i].begin();it!=TrigElectron_trigRes[i].end();it++) {
    if ( it->second ) std::cout << " - Chain " << it->first << " PASSED " << std::endl;
    else              std::cout << " - Chain " << it->first << " NOT PASSED " << std::endl;
  }
}

void TrigEgammaNtuple_v1::DumpCluster(unsigned int i, bool off=false, bool verbose=false) {
  if ( off ) {
    std::cout << std::endl << "Information on OFFCluster " << i << " ( collection: " << (*OFFCaloCluster_coll)[i] << " ) "<<  std::endl;
    std::cout << " Et= " << (*OFFCaloCluster_pt)[i] << " | Eta= " << (*OFFCaloCluster_eta)[i] << " | Phi= " << (*OFFCaloCluster_phi)[i] << std::endl;
    std::cout << " nCell: " << (*OFFCaloCluster_nCell)[i] << " | Eraw: " << (*OFFCaloCluster_eRaw)[i] << " | EtaRaw: " << (*OFFCaloCluster_etaRaw)[i] << " | PhiRaw: " << (*OFFCaloCluster_etaRaw)[i] << std::endl;
    std::cout << " vector ERaw size is:: " << ((*OFFCaloCluster_EInSampleRaw)[i]).size() << std::endl;
    for (unsigned int j=0;j<((*OFFCaloCluster_EInSampleRaw)[i]).size() ;j++) {
      std::cout << "sample: " << j << " - with energy " << (*OFFCaloCluster_EInSampleRaw)[i][j] << std::endl; 
    }     
    //  std::cout << " vector EtaRawIs: " << (*OFFCaloCluster_EtaInSampleRaw)[i] << std::endl;
    //  std::cout << " vector PhiRawIs: " << (*OFFCaloCluster_PhiInSampleRaw)[i] << std::endl;
  } else {
    std::cout << std::endl << "Information on EFCluster " << i << " ( collection: " << (*EFCaloCluster_coll)[i] << " ) "<<  std::endl;
    std::cout << " Et= " << (*EFCaloCluster_pt)[i] << " | Eta= " << (*EFCaloCluster_eta)[i] << " | Phi= " << (*EFCaloCluster_phi)[i] << std::endl;
    map<string,bool>::iterator it;
    for(it=EFCaloCluster_trigRes[i].begin();it!=EFCaloCluster_trigRes[i].end();it++) {
      if ( it->second ) std::cout << " - Chain " << it->first << " PASSED " << std::endl;
      else              std::cout << " - Chain " << it->first << " NOT PASSED " << std::endl;
    }
  }
}

void TrigEgammaNtuple_v1::DumpEgamma(unsigned int i, bool off=false, bool verbose=false) {
  if (off) {
    std::cout << std::endl << "Information on OFFLINEegamma " << i << " | type: " << (*OFFegamma_MCtype)[i] << " | orig: " << (*OFFegamma_MCorig)[i] << " | origMother: " << (*OFFegamma_MCorigMother)[i] << std::endl;
    std::cout << " isElectron= " << (*OFFegamma_isElectron)[i] << " | isPhoton= " << (*OFFegamma_isPhoton)[i] << " | author: " << (*OFFegamma_author)[i] << std::endl;
    std::cout << " isLoose= " << (*OFFegamma_isLoose)[i] << " | isMedium= " << (*OFFegamma_isMedium)[i] << " | isTight: " << (*OFFegamma_isTight)[i] << std::endl;
    
    std::cout << " Et= " << (*OFFegamma_et)[i] << " | Eta: " << (*OFFegamma_eta)[i] << " | Phi: " <<  (*OFFegamma_phi)[i] <<  std::endl;
    if ( (*OFFegamma_ClusIndex)[i]!=-1) std::cout << " Cluster Et: " << (*OFFCaloCluster_energy)[(*OFFegamma_ClusIndex)[i]]/cosh(fabs((*OFFegamma_etaBE2)[i])) << " | Eta: " << (*OFFegamma_etaBE2)[i] << std::endl;
    double eta=(*OFFegamma_etaBE2)[i];
    double et=-1;
    if ( (*OFFegamma_ClusIndex)[i]!=-1) et=(*OFFCaloCluster_energy)[(*OFFegamma_ClusIndex)[i]]/cosh(fabs((*OFFegamma_etaBE2)[i]));
    double rHad=-1;
    if ( fabs(eta)>0.8 && fabs(eta)<1.37 ) rHad=(*OFFegamma_ethad)[i]/et;
    else rHad=(*OFFegamma_ethad1)[i]/et;
    std::cout << " rEta: " << (*OFFegamma_e237)[i]/(*OFFegamma_e277)[i] << " | rHad: " << rHad << " | eratio: " << ( (*OFFegamma_emaxs1)[i]-(*OFFegamma_e2tsts1)[i] )/( (*OFFegamma_emaxs1)[i]+(*OFFegamma_e2tsts1)[i]) << " | F1: " << (*OFFegamma_f1)[i] << std::endl;
    std::cout << " trkPt: " << (*OFFegamma_trkPt)[i] << " | isEm= " << std::hex << (*OFFegamma_isem)[i] << std::dec <<std::endl;
    std::cout << " charge: " << (*OFFegamma_charge)[i] << " | dEta: " << (*OFFegamma_dEta)[i] << " | dPhi: " << (*OFFegamma_dPhi)[i] << std::endl;
    std::cout << " linked to CaloCluster " << (*OFFegamma_ClusIndex)[i] << std::endl;
    std::cout << " linked to Track " << (*OFFegamma_TrackIndex)[i] << std::endl;
  } else {
    std::cout << std::endl << "Information on EFegamma " << i << std::endl;
    std::cout << " isElectron= " << (*EFegamma_isElectron)[i] << " | isPhoton= " << (*EFegamma_isPhoton)[i] << " | author: " << (*EFegamma_author)[i] << std::endl;
    std::cout << " Et= " << (*EFegamma_et)[i] << " | Eta: " << (*EFegamma_eta)[i] << " | Phi: " <<  (*EFegamma_phi)[i] <<  std::endl;
    if ( (*EFegamma_ClusIndex)[i]!=-1) std::cout << " Cluster Et: " << (*EFCaloCluster_energy)[(*EFegamma_ClusIndex)[i]]/cosh(fabs((*EFegamma_etaBE2)[i])) << " | Eta: " << (*EFegamma_etaBE2)[i] << std::endl;
    double eta=(*EFegamma_etaBE2)[i];
    double et=(*EFCaloCluster_energy)[(*EFegamma_ClusIndex)[i]]/cosh(fabs((*EFegamma_etaBE2)[i]));
    double rHad=-1;
    if ( fabs(eta)>0.8 && fabs(eta)<1.37 ) rHad=(*EFegamma_ethad)[i]/et;
    else rHad=(*EFegamma_ethad1)[i]/et;
    std::cout << " rEta: " << (*EFegamma_e237)[i]/(*EFegamma_e277)[i] << " | rHad: " << rHad << " | eratio: " << ( (*EFegamma_emaxs1)[i]-(*EFegamma_e2tsts1)[i] )/( (*EFegamma_emaxs1)[i]+(*EFegamma_e2tsts1)[i]) << " | F1: " << (*EFegamma_f1)[i] << std::endl;
    std::cout << " trkPt: " << (*EFegamma_trkPt)[i] << " | isEm= " << std::hex << (*EFegamma_isem)[i] << std::dec <<std::endl;
    std::cout << " charge: " << (*EFegamma_charge)[i] << " dEta: " << (*EFegamma_dEta)[i] << " | dPhi: " << (*EFegamma_dPhi)[i] << std::endl;
    std::cout << " linked to CaloCluster " << (*EFegamma_ClusIndex)[i] << std::endl;
    std::cout << " linked to Track " << (*EFegamma_TrackIndex)[i] << std::endl;
    map<string,bool>::iterator it;
    for(it=EFegamma_trigRes[i].begin();it!=EFegamma_trigRes[i].end();it++) {
      if ( it->second )  std::cout << " - Chain " << it->first << " PASSED " << std::endl;
      else               std::cout << " - Chain " << it->first << " NOT PASSED " << std::endl;
    }
  }
}

///// END of DUMPING methods
////////////////////////////////////////////////////////////////////////////////////////////////


void TrigEgammaNtuple_v1::Loop() {
  if (!CheckTrees()) {
    std::cout << "All the Trees are empty" << std::endl;
    exit(-1);
  }
  Init();
  Long64_t nentries = GetEntries();
  if (nentries>nEntry && nEntry>0) nentries=nEntry;

  std::cout << "The number of Event for the loop is: " <<  nentries << std::endl;

  Long64_t nbytes = 0;
  
  //used to automatically dump histogram into a file
  std::vector<TH1F*>     th1dVect;
  std::vector<TH2F*>     th2dVect;
  // define histogram:                          TH1F* myhist=new TH1F(.............)
  // and put it into the corresponding vector:  th1dVect.push_back(myhist);

  int nEvent=0;

  /* //decomment to use GRL BUT first have a look at Makefile
  Root::TGoodRunsList m_grl;
  Root::TGoodRunsListReader reader = Root::TGoodRunsListReader();
  reader.SetXMLFile("myGRL.xml");
  reader.Interpret();
  m_grl = reader.GetMergedGoodRunsList();
  m_grl.Summary();
  */
  
  
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    if ( jentry%1000==0) std::cout << std::endl << "Event " << jentry << std::endl;
    
    /* //decomment to use GRL
       bool isGoodLumi = m_grl.HasRunLumiBlock(Event_run_number,Event_lumiBlock);
       if (!isGoodLumi) continue;    
    */
    nEvent++;
    std::cout << std::endl;
    std::cout << "CaloTiming: " << Event_deltaT_Calo << " | MBTS timing: " << Event_deltaT_MBTS << " | L1_MBTS: " << Event_passed_MBTS << std::endl;
  
    for (unsigned int i=0;i<OFFegamma_nEGamma;i++) {
      if ( (*OFFegamma_author)[i]==8 || (*OFFegamma_author)[i]==2 ) continue;
      DumpEgamma(i,true);
    }
    continue;

    for (unsigned int i=0;i<truth_npart;i++) {
      std::cout << "Truth particle : " << i << " | status: " << (*truth_status)[i] << " | Pt: " << (*truth_pt)[i] << " | PDG id: " << (*truth_PDGId)[i] << " | mother PDGId: " << (*truth_MotherPDGId)[i] << std::endl;  
    }
      
    // for (unsigned int i=0;i<TrigInDetTrack_nTrack;i++)  DumpL2Track(i);
      
    //    for (unsigned int i=0;i<EFegamma_nEGamma;i++)   DumpEgamma(i);
  
    //    for (unsigned int i=0;i<OFFegamma_nEGamma;i++)  DumpEgamma(i,true);
  
    
    continue;
    //    DumpTrigger();
    std::cout << std::endl;
    std::cout << "Event INFORMATION: " << std::endl;
    std::cout << " -> " << L1ROI_nClus << " L1 cluster " << std::endl;
    std::cout << " -> " << TrigEMCluster_nClus << " EMCluster, " << TrigElectron_nTrigElectron << " TrigElectron, " << TrigPhoton_nTrigPhoton << " TrigPhoton and " << TrigInDetTrack_nTrack << " TrigInDetTrack" << std::endl; 
    std::cout << " -> " << EFCaloCluster_nClus << " EFCaloCluster, " <<  EFTrackParticle_nTrack << " EFTrackParticle, " <<  EFegamma_nEGamma << " EFegamma" << std::endl; 
    std::cout << " -> " << OFFCaloCluster_nClus << " OFFCaloCluster, " <<  OFFTrackParticle_nTrack << " OFFTrackParticle, " <<  OFFegamma_nEGamma << " OFFegamma" << std::endl; 
    
    /*
      if ( L1ROI_nClus!=0           ) DumpL1(0);
      if ( TrigEMCluster_nClus!=0   ) DumpL2Cluster(0);
      if ( TrigInDetTrack_nTrack!=0 ) DumpL2Track(0);
      if ( TrigPhoton_nTrigPhoton!=0) DumpL2Photon(0);
      if ( TrigElectron_nTrigElectron!=0) DumpL2Electron(0);
      if ( EFCaloCluster_nClus!=0) DumpCluster(0);
      if ( EFegamma_nEGamma!=0 )   DumpEgamma(0);
      if ( OFFCaloCluster_nClus!=0)DumpCluster(0,true);
      if ( OFFegamma_nEGamma!=0)   DumpEgamma(0,true);
    */
    
    for (unsigned int i=0;i<L1ROI_nClus;i++)         DumpL1(i);
    
    for (unsigned int i=0;i<TrigEMCluster_nClus;i++) DumpL2Cluster(i,true);
    
    for (unsigned int i=0;i<TrigInDetTrack_nTrack;i++)  DumpL2Track(i);
    
    for (unsigned int i=0;i<TrigPhoton_nTrigPhoton;i++) DumpL2Photon(i);
    
    for (unsigned int i=0;i<TrigElectron_nTrigElectron;i++) DumpL2Electron(i);
    
    for (unsigned int i=0;i<EFCaloCluster_nClus;i++) DumpCluster(i);

    for (unsigned int i=0;i<EFegamma_nEGamma;i++)     DumpEgamma(i);
    
    for (unsigned int i=0;i<OFFCaloCluster_nClus;i++) DumpCluster(i,true);
    
    for (unsigned int i=0;i<OFFegamma_nEGamma;i++) DumpEgamma(i,true);
    
    //    if ( L1ROI_nClus!=0 || TrigEMCluster_nClus!=0 || EFCaloCluster_nClus!=0 || OFFegamma_nEGamma!=0 ) {   
  }
  
  std::cout << std::endl << std::endl;
  std::cout << "Events: " << nEvent << std::endl;
  std::cout << std::endl;
  
  if ( th2dVect.size()!=0 || th1dVect.size()!=0 ) {
    TFile *occOutputFile;
    std::string OutPutFile=m_outPutFile;
    occOutputFile = new TFile(OutPutFile.c_str(), "RECREATE");
    if (occOutputFile->IsZombie()) {
      std::cout << " Unable to open File or File already exitst: " << OutPutFile.c_str() << std::endl;
      exit(-1);
    }
    TDirectory* direc = occOutputFile->mkdir("result");
    gDirectory->cd("result");
    
    for(int i=0; i<th2dVect.size();i++) {
      direc->WriteTObject(th2dVect[i],(th2dVect[i])->GetName());
    }
    
    for(int i=0; i<th1dVect.size();i++) {
      direc->WriteTObject(th1dVect[i],(th1dVect[i])->GetName());
    }
  }
}
