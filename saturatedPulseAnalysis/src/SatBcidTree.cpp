#include "SatBcidTree.h"

SatBcidTree::SatBcidTree(void){
   // Initialize variables
   Initialize();
}

SatBcidTree::~SatBcidTree(void){
   
   if(m_treeFile->IsOpen()){
      m_treeFile->Close();
      m_treeFile->Delete();
   }
   else if(m_treeFile != 0){
      m_treeFile->Delete();
   }
}

void SatBcidTree::CloseFile(void){
   if(m_treeFile->IsOpen()){
      m_treeFile->Close();
      m_treeFile->Delete();
   }
   else if(m_treeFile != 0){
      m_treeFile->Delete();
   }
}


bool SatBcidTree::OpenFile(void)
{
   // open file
   if(m_readMode){
      m_treeFile = new TFile(m_s_treeFilename.c_str(),"READ");
      
      m_tree = (TTree*)gDirectory->Get(m_s_treename.c_str());
      SetBranchAddresses();
   }
   else if(m_createMode){ // create mode
      m_treeFile = new TFile(m_s_treeFilename.c_str(),"RECREATE");
      
      m_tree = new TTree(m_s_treename.c_str(),m_s_treename.c_str());
      CrateBranches();
   }
   else if(m_updateMode){ // update mode
      m_treeFile = new TFile(m_s_treeFilename.c_str(),"UPDATE");
      
      m_tree = (TTree*)gDirectory->Get(m_s_treename.c_str());
      SetBranchAddresses();
   }
   
   if(!m_treeFile->IsOpen()){
      return false;
   }
   
   return true;
   
}

bool SatBcidTree::OpenFile(std::string filename){
   m_s_treeFilename = filename;
   return OpenFile();
}

bool SatBcidTree::OpenFile(TFile* file){
   
   m_treeFile = file;
   m_s_treeFilename = m_treeFile->GetName();
   
   if(!m_treeFile->IsOpen()){
      return false;
   }
   
   m_treeFile->cd();
   
   // open file
   if(m_readMode){
      m_tree = (TTree*)gDirectory->Get(m_s_treename.c_str());
      if(m_tree == 0){
         std::cout << "[SatBcidTree::OpenFile] tree, " << m_s_treename << ", could not be found in file, " << m_s_treeFilename << ".\n";
         return false;
      }
      SetBranchAddresses();
   }
   else if(m_createMode){ // write mode
      m_tree = new TTree(m_s_treename.c_str(),m_s_treename.c_str());
      CrateBranches();
   }
   else if(m_updateMode){ // write mode
      m_tree = (TTree*)gDirectory->Get(m_s_treename.c_str());
      if(m_tree == 0){
         std::cout << "[SatBcidTree::OpenFile] tree, " << m_s_treename << ", could not be found in file, " << m_s_treeFilename << ".\n";
         return false;
      }
      SetBranchAddresses();
   }
   
   return true;
   
}

void SatBcidTree::Write(void){
   if(m_updateMode)
      m_tree->Write(m_s_treename.c_str(),TObject::kOverwrite);
   else if(m_createMode)
      m_tree->Write();
   else
      std::cerr << "[SatBcidTree::Write] ERROR must be in Update or Create mode to use Write function.\n";
}

void SatBcidTree::Initialize(void){
   
   
   m_s_treename = "satBcidTree";
   m_s_treeFilename = "satBcidTreeOutput.root";
   
   // Initialize TTree variables.
   m_t_coolId                      = 0;
   m_t_s_coolId                    =       "coolId";
   
   m_t_satHigh                     = 0;
   m_t_s_satHigh                   =       "satHigh";
   m_t_satLow                      = 0;
   m_t_s_satLow                    =       "satLow";
   m_t_satLevel                    = 0;
   m_t_s_satLevel                  =       "satLevel";
   
   m_t_raw_dacVsAdc                = 0;
   m_t_s_raw_dacVsAdc              =       "raw_dacVsAdc";
   m_t_raw_dacVsAdcFit             = 0;
   m_t_s_raw_dacVsAdcFit           =       "raw_dacVsAdcFit";
   m_t_raw_peakVsTs1               = 0;
   m_t_s_raw_peakVsTs1             =       "raw_peakVsTs1";
   m_t_raw_ts1LinearFit            = 0;
   m_t_s_raw_ts1LinearFit          =       "raw_ts1LinearFit";
   m_t_raw_satHigh                 = 0;
   m_t_s_raw_satHigh               =       "raw_satHigh";
   m_t_raw_peakVsTs2               = 0;
   m_t_s_raw_peakVsTs2             =       "raw_peakVsTs2";
   m_t_raw_ts2LinearFit            = 0;
   m_t_s_raw_ts2LinearFit          =       "raw_ts2LinearFit";
   m_t_raw_satLow                  = 0;
   m_t_s_raw_satLow                =       "raw_satLow";
   m_t_raw_satLevel                = 0;
   m_t_s_raw_satLevel              =       "raw_satLevel";
   
   m_t_processed_dacVsAdc          = 0;
   m_t_s_processed_dacVsAdc        =       "processed_dacVsAdc";
   m_t_processed_dacVsAdcFit       = 0;
   m_t_s_processed_dacVsAdcFit     =       "processed_dacVsAdcFit";
   m_t_processed_peakVsTs1         = 0;
   m_t_s_processed_peakVsTs1       =       "processed_peakVsTs1";
   m_t_processed_ts1LinearFit      = 0;
   m_t_s_processed_ts1LinearFit    =       "processed_ts1LinearFit";
   m_t_processed_satHigh           = 0;
   m_t_s_processed_satHigh         =       "processed_satHigh";
   m_t_processed_peakVsTs2         = 0;
   m_t_s_processed_peakVsTs2       =       "processed_peakVsTs2";
   m_t_processed_ts2LinearFit      = 0;
   m_t_s_processed_ts2LinearFit    =       "processed_ts2LinearFit";
   m_t_processed_satLow            = 0;
   m_t_s_processed_satLow          =       "processed_satLow";
   m_t_processed_satLevel          = 0;
   m_t_s_processed_satLevel        =       "processed_satLevel";
   
   m_t_isEnabled                   = false;
   m_t_s_isEnabled                 =       "isEnabled";
   m_t_isValid                     = false;
   m_t_s_isValid                   =       "isValid";
   m_t_isProcessed                 = false;
   m_t_s_isProcessed               =       "isProcessed";
   
   m_t_pedestalMean                = 0.0;
   m_t_s_pedestalMean              =       "pedestalMean";
   m_t_pedestalSigma               = 0.0;
   m_t_s_pedestalSigma             =       "pedestalSigma";
   
   m_t_raw_dacVsAdcSlopeMean       = 0.0;
   m_t_s_raw_dacVsAdcSlopeMean     =       "raw_dacVsAdcSlopeMean";
   m_t_raw_dacVsAdcSlopeSigma      = 0.0;
   m_t_s_raw_dacVsAdcSlopeSigma    =       "raw_dacVsAdcSlopeSigma";
   
   m_t_processed_dacVsAdcSlopeMean    = 0.0;
   m_t_s_processed_dacVsAdcSlopeMean  =       "processed_dacVsAdcSlopeMean";
   m_t_processed_dacVsAdcSlopeSigma   = 0.0;
   m_t_s_processed_dacVsAdcSlopeSigma =       "processed_dacVsAdcSlopeSigma";
   
   m_t_raw_peakBin                 = 0;
   m_t_s_raw_peakBin               =       "raw_peakBin";
   m_t_processed_peakBin           = 0;
   m_t_s_processed_peakBin         =       "processed_peakBin";
   
   m_t_errorCode                   = 0;
   m_t_s_errorCode                 =       "errorCode";
   
   m_t_phos4errorCode              = 0;
   m_t_s_phos4errorCode            =       "phos4errorCode";
   
}

void SatBcidTree::ClearTree(void){
   m_t_coolId                      = 0;
   
   m_t_satHigh                     = 0;
   m_t_satLow                      = 0;
   m_t_satLevel                    = 0;
   
   m_t_raw_dacVsAdc                = 0;
   m_t_raw_dacVsAdcFit             = 0;
   m_t_raw_peakVsTs1               = 0;
   m_t_raw_ts1LinearFit            = 0;
   m_t_raw_satHigh                 = 0;
   m_t_raw_peakVsTs2               = 0;
   m_t_raw_ts2LinearFit            = 0;
   m_t_raw_satLow                  = 0;
   m_t_raw_satLevel                = 0;
   
   m_t_processed_dacVsAdc          = 0;
   m_t_processed_dacVsAdcFit       = 0;
   m_t_processed_peakVsTs1         = 0;
   m_t_processed_ts1LinearFit      = 0;
   m_t_processed_satHigh           = 0;
   m_t_processed_peakVsTs2         = 0;
   m_t_processed_ts2LinearFit      = 0;
   m_t_processed_satLow            = 0;
   m_t_processed_satLevel          = 0;
   
   m_t_isEnabled                   = false;
   m_t_isValid                     = false;
   m_t_isProcessed                 = false;
   
   m_t_pedestalMean                = 0.0;
   m_t_pedestalSigma               = 0.0;
   
   m_t_raw_dacVsAdcSlopeMean       = 0.0;
   m_t_raw_dacVsAdcSlopeSigma      = 0.0;
   
   m_t_processed_dacVsAdcSlopeMean = 0.0;
   m_t_processed_dacVsAdcSlopeSigma= 0.0;
   
   m_t_raw_peakBin                 = 0;
   m_t_processed_peakBin           = 0;
   
   m_t_errorCode                   = 0;
   m_t_phos4errorCode              = 0;
}

void SatBcidTree::DeleteEntry(void){
   if(m_t_raw_dacVsAdc != 0){
      delete m_t_raw_dacVsAdc;
      m_t_raw_dacVsAdc = 0;
   }
   
   if(m_t_raw_dacVsAdcFit != 0){
      delete m_t_raw_dacVsAdcFit;
      m_t_raw_dacVsAdcFit = 0;
   }
   
   if(m_t_raw_peakVsTs1 != 0){
      delete m_t_raw_peakVsTs1;
      m_t_raw_peakVsTs1 = 0;
   }
   
   if(m_t_raw_ts1LinearFit != 0){
      delete m_t_raw_ts1LinearFit;
      m_t_raw_ts1LinearFit = 0;
   }
   
   if(m_t_raw_peakVsTs2 != 0){
      delete m_t_raw_peakVsTs2;
      m_t_raw_peakVsTs2 = 0;
   }
   
   if(m_t_raw_ts2LinearFit != 0){
      delete m_t_raw_ts2LinearFit;
      m_t_raw_ts2LinearFit = 0;
   }
   
   
   if(m_t_processed_dacVsAdc != 0){
      delete m_t_processed_dacVsAdc;
      m_t_processed_dacVsAdc = 0;
   }
   
   if(m_t_processed_dacVsAdcFit != 0){
      delete m_t_processed_dacVsAdcFit;
      m_t_processed_dacVsAdcFit = 0;
   }
   
   if(m_t_processed_peakVsTs1 != 0){
      delete m_t_processed_peakVsTs1;
      m_t_processed_peakVsTs1 = 0;
   }
   
   if(m_t_processed_ts1LinearFit != 0){
      delete m_t_processed_ts1LinearFit;
      m_t_processed_ts1LinearFit = 0;
   }
   
   if(m_t_processed_peakVsTs2 != 0){
      delete m_t_processed_peakVsTs2;
      m_t_processed_peakVsTs2 = 0;
   }
   
   if(m_t_processed_ts2LinearFit != 0){
      delete m_t_processed_ts2LinearFit;
      m_t_processed_ts2LinearFit = 0;
   }
   
}


void SatBcidTree::CrateBranches(void){
   
   // Initialize TTree variables.
   m_tree->Branch(m_t_s_coolId.c_str(), &m_t_coolId);
   
   m_tree->Branch(m_t_s_errorCode.c_str(), &m_t_errorCode);
   m_tree->Branch(m_t_s_phos4errorCode.c_str(), &m_t_phos4errorCode);
   
   m_tree->Branch(m_t_s_satHigh.c_str(), &m_t_satHigh);
   m_tree->Branch(m_t_s_satLow.c_str(), &m_t_satLow);
   m_tree->Branch(m_t_s_satLevel.c_str(), &m_t_satLevel);
   
   m_tree->Branch(m_t_s_raw_dacVsAdc.c_str(),      &m_t_raw_dacVsAdc);
   m_tree->Branch(m_t_s_raw_dacVsAdcFit.c_str(),   &m_t_raw_dacVsAdcFit);
   m_tree->Branch(m_t_s_raw_peakVsTs1.c_str(),     &m_t_raw_peakVsTs1);
   m_tree->Branch(m_t_s_raw_ts1LinearFit.c_str(),  &m_t_raw_ts1LinearFit);
   m_tree->Branch(m_t_s_raw_satHigh.c_str(),       &m_t_raw_satHigh);
   m_tree->Branch(m_t_s_raw_peakVsTs2.c_str(),     &m_t_raw_peakVsTs2);
   m_tree->Branch(m_t_s_raw_ts2LinearFit.c_str(),  &m_t_raw_ts2LinearFit);
   m_tree->Branch(m_t_s_raw_satLow.c_str(),        &m_t_raw_satLow);
   m_tree->Branch(m_t_s_raw_satLevel.c_str(),      &m_t_raw_satLevel);
   
   m_tree->Branch(m_t_s_processed_dacVsAdc.c_str(),      &m_t_processed_dacVsAdc);
   m_tree->Branch(m_t_s_processed_dacVsAdcFit.c_str(),   &m_t_processed_dacVsAdcFit);
   m_tree->Branch(m_t_s_processed_peakVsTs1.c_str(),     &m_t_processed_peakVsTs1);
   m_tree->Branch(m_t_s_processed_ts1LinearFit.c_str(),  &m_t_processed_ts1LinearFit);
   m_tree->Branch(m_t_s_processed_satHigh.c_str(),       &m_t_processed_satHigh);
   m_tree->Branch(m_t_s_processed_peakVsTs2.c_str(),     &m_t_processed_peakVsTs2);
   m_tree->Branch(m_t_s_processed_ts2LinearFit.c_str(),  &m_t_processed_ts2LinearFit);
   m_tree->Branch(m_t_s_processed_satLow.c_str(),        &m_t_processed_satLow);
   m_tree->Branch(m_t_s_processed_satLevel.c_str(),      &m_t_processed_satLevel);
   
   m_tree->Branch(m_t_s_isEnabled.c_str(),    &m_t_isEnabled);
   m_tree->Branch(m_t_s_isValid.c_str(),      &m_t_isValid);
   m_tree->Branch(m_t_s_isProcessed.c_str(),  &m_t_isProcessed);
   
   m_tree->Branch(m_t_s_pedestalMean.c_str(), &m_t_pedestalMean);
   m_tree->Branch(m_t_s_pedestalSigma.c_str(),&m_t_pedestalSigma);
   
   m_tree->Branch(m_t_s_raw_dacVsAdcSlopeMean.c_str(), &m_t_raw_dacVsAdcSlopeMean);
   m_tree->Branch(m_t_s_raw_dacVsAdcSlopeSigma.c_str(),&m_t_raw_dacVsAdcSlopeSigma);
   
   m_tree->Branch(m_t_s_processed_dacVsAdcSlopeMean.c_str(), &m_t_processed_dacVsAdcSlopeMean);
   m_tree->Branch(m_t_s_processed_dacVsAdcSlopeSigma.c_str(),&m_t_processed_dacVsAdcSlopeSigma);
   
   m_tree->Branch(m_t_s_raw_peakBin.c_str(),       &m_t_raw_peakBin);
   m_tree->Branch(m_t_s_processed_peakBin.c_str(), &m_t_processed_peakBin);
 
}

void SatBcidTree::SetBranchAddresses(void){
   
   // Initialize TTree variables.
   m_tree->SetBranchAddress(m_t_s_coolId.c_str(),            &m_t_coolId);
   
   m_tree->SetBranchAddress(m_t_s_errorCode.c_str(),         &m_t_errorCode);
   m_tree->SetBranchAddress(m_t_s_phos4errorCode.c_str(),    &m_t_phos4errorCode);
   
   m_tree->SetBranchAddress(m_t_s_satHigh.c_str(),           &m_t_satHigh);
   m_tree->SetBranchAddress(m_t_s_satLow.c_str(),            &m_t_satLow);
   m_tree->SetBranchAddress(m_t_s_satLevel.c_str(),          &m_t_satLevel);
   
   m_tree->SetBranchAddress(m_t_s_raw_dacVsAdc.c_str(),      &m_t_raw_dacVsAdc);
   m_tree->SetBranchAddress(m_t_s_raw_dacVsAdcFit.c_str(),   &m_t_raw_dacVsAdcFit);
   m_tree->SetBranchAddress(m_t_s_raw_peakVsTs1.c_str(),     &m_t_raw_peakVsTs1);
   m_tree->SetBranchAddress(m_t_s_raw_ts1LinearFit.c_str(),  &m_t_raw_ts1LinearFit);
   m_tree->SetBranchAddress(m_t_s_raw_satHigh.c_str(),       &m_t_raw_satHigh);
   m_tree->SetBranchAddress(m_t_s_raw_peakVsTs2.c_str(),     &m_t_raw_peakVsTs2);
   m_tree->SetBranchAddress(m_t_s_raw_ts2LinearFit.c_str(),  &m_t_raw_ts2LinearFit);
   m_tree->SetBranchAddress(m_t_s_raw_satLow.c_str(),        &m_t_raw_satLow);
   m_tree->SetBranchAddress(m_t_s_raw_satLevel.c_str(),      &m_t_raw_satLevel);
   
   m_tree->SetBranchAddress(m_t_s_processed_dacVsAdc.c_str(),      &m_t_processed_dacVsAdc);
   m_tree->SetBranchAddress(m_t_s_processed_dacVsAdcFit.c_str(),   &m_t_processed_dacVsAdcFit);
   m_tree->SetBranchAddress(m_t_s_processed_peakVsTs1.c_str(),     &m_t_processed_peakVsTs1);
   m_tree->SetBranchAddress(m_t_s_processed_ts1LinearFit.c_str(),  &m_t_processed_ts1LinearFit);
   m_tree->SetBranchAddress(m_t_s_processed_satHigh.c_str(),       &m_t_processed_satHigh);
   m_tree->SetBranchAddress(m_t_s_processed_peakVsTs2.c_str(),     &m_t_processed_peakVsTs2);
   m_tree->SetBranchAddress(m_t_s_processed_ts2LinearFit.c_str(),  &m_t_processed_ts2LinearFit);
   m_tree->SetBranchAddress(m_t_s_processed_satLow.c_str(),        &m_t_processed_satLow);
   m_tree->SetBranchAddress(m_t_s_processed_satLevel.c_str(),      &m_t_processed_satLevel);
   
   m_tree->SetBranchAddress(m_t_s_isEnabled.c_str(),    &m_t_isEnabled);
   m_tree->SetBranchAddress(m_t_s_isValid.c_str(),      &m_t_isValid);
   m_tree->SetBranchAddress(m_t_s_isProcessed.c_str(),  &m_t_isProcessed);
   
   m_tree->SetBranchAddress(m_t_s_pedestalMean.c_str(), &m_t_pedestalMean);
   m_tree->SetBranchAddress(m_t_s_pedestalSigma.c_str(),&m_t_pedestalSigma);
   
   m_tree->SetBranchAddress(m_t_s_raw_dacVsAdcSlopeMean.c_str(), &m_t_raw_dacVsAdcSlopeMean);
   m_tree->SetBranchAddress(m_t_s_raw_dacVsAdcSlopeSigma.c_str(),&m_t_raw_dacVsAdcSlopeSigma);
   
   m_tree->SetBranchAddress(m_t_s_processed_dacVsAdcSlopeMean.c_str(), &m_t_processed_dacVsAdcSlopeMean);
   m_tree->SetBranchAddress(m_t_s_processed_dacVsAdcSlopeSigma.c_str(),&m_t_processed_dacVsAdcSlopeSigma);
   
   m_tree->SetBranchAddress(m_t_s_raw_peakBin.c_str(),       &m_t_raw_peakBin);
   m_tree->SetBranchAddress(m_t_s_processed_peakBin.c_str(), &m_t_processed_peakBin);
 
}

unsigned int SatBcidTree::FindEntry(const L1CaloChannelId findCoolId){
   
   ClearTree();
   
   m_tree->GetEntry(m_currentEntry);
   
   if(m_t_coolId < findCoolId.GetId()){
      
      for(unsigned int entry=m_currentEntry+1;entry<m_tree->GetEntries();++entry){
         m_tree->GetEntry(entry);
         if(m_t_coolId == findCoolId.GetId()){
            m_currentEntry = entry;
            return m_currentEntry;
         }
         
      }
      // if the entry was not found than check the other entries
      for(unsigned int entry=m_currentEntry-1;entry<m_tree->GetEntries();--entry){
         m_tree->GetEntry(entry);
         if(m_t_coolId == findCoolId.GetId()){
            m_currentEntry = entry;
            return m_currentEntry;
         }
         
      }
   }
   else if(m_t_coolId > findCoolId.GetId()){
      
      for(unsigned int entry=m_currentEntry-1;entry<m_tree->GetEntries();--entry){
         m_tree->GetEntry(entry);
         
         if(m_t_coolId == findCoolId.GetId()){
            m_currentEntry = entry;
            return m_currentEntry;
         }
         
      }
      
      for(unsigned int entry=m_currentEntry+1;entry<m_tree->GetEntries();++entry){
         m_tree->GetEntry(entry);
         
         if(m_t_coolId == findCoolId.GetId()){
            m_currentEntry = entry;
            return m_currentEntry;
         }
         
      }
      
   }
   else if(m_t_coolId == findCoolId.GetId()){
      return m_currentEntry;
   }
   
   
   return 0;
}
