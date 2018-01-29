#include "ShapeMakerTree.h"

ShapeMakerTree::ShapeMakerTree(void)
{
   
   // Initialize variables
   Initialize();
   
   // If run is from after April 2010 need to use the new tree output
   m_useNewTree = true;
   
}

ShapeMakerTree::ShapeMakerTree(std::string filename):m_s_treeFilename(filename){
   
   // Initialize variables
   Initialize();
   
   // If run is from after April 2010 need to use the new tree output
   m_useNewTree = true;
   
}

ShapeMakerTree::~ShapeMakerTree(void){
   
   if(m_treeFile->IsOpen()){
      m_treeFile->Close();
      m_treeFile->Delete();
   }
   else if(m_treeFile != 0){
      m_treeFile->Delete();
   }
}

bool ShapeMakerTree::OpenFile(void){
   m_treeFile = new TFile(m_s_treeFilename.c_str(),"READ");
   
   // get the tree pointer if file was opened
   if(m_treeFile->IsOpen()){
      m_tree = (TTree*)m_treeFile->Get(m_s_treename.c_str());
      if(m_tree == 0){
         std::cerr << "[ShapeMakerTree::OpenFile] Failed to extract tree with name: " << m_s_treename << std::endl;
         return false;
      }
      else{
         // set the number of events to keep in memory
         m_tree->SetCircular(10);
         // set the number of events before the tree flushes the branch buffers to file.
         // this function is in the documentation, but for some reason doesn't exist in my root version
         //m_tree->SetAutoFlush(10);
      }
      
   }
   else{
      std::cerr << "[ShapeMakerTree::ShapeMakerTree] Failed to open file: " << m_s_treeFilename << std::endl;
      return false;
   }
   
   ClearTree();
   
   // set branch variable addresses
   SetBranchAddresses();
   
   return m_treeFile->IsOpen();
}

void ShapeMakerTree::CloseFile(void){
   //m_tree->ResetBranchAddresses();
   m_tree->Delete();
   m_tree = 0;
   
   m_treeFile->Close();
   m_treeFile->Delete();
   delete m_treeFile;
   m_treeFile = 0;
   
   ClearTree();
}

void ShapeMakerTree::Initialize(void){
   
   m_tree                          = 0;
   m_s_treename                    =       "phos4signalShapes";
   m_currentEntry                  = 0;
   m_treeFile                      = 0;
   
   m_useNewTree                    = false;
   
   m_tileRun                       = false;
   m_larRun                        = false;
   
   m_dacBarrel                     = 0;
   m_dacEmec                       = 0;
   m_dacFcal                       = 0;
   m_dacHec                        = 0;
   
   // tree branches
   m_t_coolId                      = 0;
   m_t_s_coolId                    =       "coolId";
   m_t_currentFullDelayData        = 0;
   m_t_s_currentFullDelayData      =       "currentFullDelayData";
   m_t_isEnabled                   = false;
   m_t_s_isEnabled                 =       "isEnabled";
   m_t_isValid                     = false;
   m_t_s_isValid                   =       "isValid";
   m_t_pedestalMean                = 0.0;
   m_t_s_pedestalMean              =       "pedestalMean";
   m_t_pedestalSigma               = 0.0;
   m_t_s_pedestalSigma             =       "pedestalSigma";
   m_t_rawSignalShape              = 0;
   m_t_s_rawSignalShape            =       "rawSignalShape";
   m_t_processedSignalShape        = 0;
   m_t_s_processedSignalShape      =       "processedSignalShape";
   m_t_risingSlopeMean             = 0.0;
   m_t_s_risingSlopeMean           =       "risingSlopeMean";
   m_t_risingSlopeSigma            = 0.0;
   m_t_s_risingSlopeSigma          =       "risingSlopeSigma";
   
   // old tree branches
   m_t_newFullDelayData            = 0;
   m_t_s_newFullDelayData          =       "newFullDelayData";
   
   m_t_rawPeakValue                = 0.0;
   m_t_s_rawPeakValue              =       "rawPeakValue";
   m_t_rawPeakBin                  = 0;
   m_t_s_rawPeakBin                =       "rawPeakBin";
   
   m_t_processedPeakValue          = 0.0;
   m_t_s_processedPeakValue        =       "processedPeakValue";
   m_t_processedPeakBin            = 0;
   m_t_s_processedPeakBin          =       "processedPeakBin";
   
   // new tree branches
   m_t_rawMaxFullDelayData         = 0;
   m_t_s_rawMaxFullDelayData       =       "rawMaxFullDelayData";
   m_t_rawFitFullDelayData         = 0;
   m_t_s_rawFitFullDelayData       =       "rawFitFullDelayData";
   m_t_rawMaxPeakValue             = 0.0;
   m_t_s_rawMaxPeakValue           =       "rawMaxPeakValue";
   m_t_rawMaxPeakBin               = 0;
   m_t_s_rawMaxPeakBin             =       "rawMaxPeakBin";
   m_t_rawFitPeakValue             = 0.0;
   m_t_s_rawFitPeakValue           =       "rawFitPeakValue";
   m_t_rawFitPeakBin               = 0;
   m_t_s_rawFitPeakBin             =       "rawFitPeakBin";
   m_t_rawFit                      = 0;
   m_t_s_rawFit                    =       "rawFit";
   m_t_rawFitPerformed             = false;
   m_t_s_rawFitPerformed           =       "rawFitPerformed";
   
   m_t_processedMaxFullDelayData   = 0;
   m_t_s_processedMaxFullDelayData =       "processedMaxFullDelayData";
   m_t_processedFitFullDelayData   = 0;
   m_t_s_processedFitFullDelayData =       "processedFitFullDelayData";
   m_t_processedMaxPeakValue       = 0.0;
   m_t_s_processedMaxPeakValue     =       "processedMaxPeakValue";
   m_t_processedMaxPeakBin         = 0;
   m_t_s_processedMaxPeakBin       =       "processedMaxPeakBin";
   m_t_processedFitPeakValue       = 0.0;
   m_t_s_processedFitPeakValue     =       "processedFitPeakValue";
   m_t_processedFitPeakBin         = 0;
   m_t_s_processedFitPeakBin       =       "processedFitPeakBin";
   m_t_processedFit                = 0;
   m_t_s_processedFit              =       "processedFit";
   m_t_processedFitPerformed       = false;
   m_t_s_processedFitPerformed     =       "processedFitPerformed";
   
   m_t_errorCode                   = 0;
   m_t_s_errorCode                 =       "errorCode";
   
   m_t_isProcessed                 = 0;
   m_t_s_isProcessed               =       "isProcessed";
}

void ShapeMakerTree::ClearTree(void){
   m_t_coolId                      = 0;
   m_t_currentFullDelayData        = 0;
   m_t_newFullDelayData            = 0;
   m_t_isEnabled                   = false;
   m_t_isValid                     = false;
   m_t_pedestalMean                = 0.0;
   m_t_pedestalSigma               = 0.0;
   m_t_rawSignalShape              = 0;
   m_t_rawPeakValue                = 0.0;
   m_t_rawPeakBin                  = 0;
   m_t_processedSignalShape        = 0;
   m_t_processedPeakValue          = 0.0;
   m_t_processedPeakBin            = 0;
   m_t_risingSlopeMean             = 0.0;
   m_t_risingSlopeSigma            = 0.0;
   m_t_rawMaxFullDelayData         = 0;
   m_t_rawFitFullDelayData         = 0;
   m_t_rawMaxPeakValue             = 0.0;
   m_t_rawMaxPeakBin               = 0;
   m_t_rawFitPeakValue             = 0.0;
   m_t_rawFitPeakBin               = 0;
   m_t_rawFit                      = 0;
   m_t_processedMaxFullDelayData   = 0;
   m_t_processedFitFullDelayData   = 0;
   m_t_processedMaxPeakValue       = 0.0;
   m_t_processedMaxPeakBin         = 0;
   m_t_processedFitPeakValue       = 0.0;
   m_t_processedFitPeakBin         = 0;
   m_t_processedFit                = 0;
   m_t_errorCode                   = 0;
   m_t_isProcessed                 = false;
}

void ShapeMakerTree::DeleteEntry(void){
   if(m_t_rawSignalShape != 0){
      delete m_t_rawSignalShape;
      m_t_rawSignalShape = 0;
   }
   
   if(m_t_processedSignalShape != 0){
      delete m_t_processedSignalShape;
      m_t_processedSignalShape = 0;
   }
   
   if(m_t_rawFit != 0){
      delete m_t_rawFit;
      m_t_rawFit = 0;
   }
   
   if(m_t_processedFit != 0){
      delete m_t_processedFit;
      m_t_processedFit = 0;
   }
   
}


void ShapeMakerTree::SetBranchAddresses(void){
   
   m_tree->SetBranchAddress(m_t_s_coolId.c_str(),                &m_t_coolId);
   m_tree->SetBranchAddress(m_t_s_currentFullDelayData.c_str(),  &m_t_currentFullDelayData);
   m_tree->SetBranchAddress(m_t_s_isEnabled.c_str(),             &m_t_isEnabled);
   m_tree->SetBranchAddress(m_t_s_isValid.c_str(),               &m_t_isValid);
   m_tree->SetBranchAddress(m_t_s_pedestalMean.c_str(),          &m_t_pedestalMean);
   m_tree->SetBranchAddress(m_t_s_pedestalSigma.c_str(),         &m_t_pedestalSigma);
   m_tree->SetBranchAddress(m_t_s_rawSignalShape.c_str(),        &m_t_rawSignalShape);
   m_tree->SetBranchAddress(m_t_s_processedSignalShape.c_str(),  &m_t_processedSignalShape);
   m_tree->SetBranchAddress(m_t_s_risingSlopeMean.c_str(),       &m_t_risingSlopeMean);
   m_tree->SetBranchAddress(m_t_s_risingSlopeSigma.c_str(),      &m_t_risingSlopeSigma);
   
   if(m_useNewTree){
      m_tree->SetBranchAddress(m_t_s_rawMaxFullDelayData.c_str(),   &m_t_rawMaxFullDelayData);
      m_tree->SetBranchAddress(m_t_s_rawFitFullDelayData.c_str(),   &m_t_rawFitFullDelayData);
      m_tree->SetBranchAddress(m_t_s_rawMaxPeakValue.c_str(),       &m_t_rawMaxPeakValue);
      m_tree->SetBranchAddress(m_t_s_rawMaxPeakBin.c_str(),         &m_t_rawMaxPeakBin);
      m_tree->SetBranchAddress(m_t_s_rawFitPeakValue.c_str(),       &m_t_rawFitPeakValue);
      m_tree->SetBranchAddress(m_t_s_rawFitPeakBin.c_str(),         &m_t_rawFitPeakBin);
      m_tree->SetBranchAddress(m_t_s_rawFit.c_str(),                &m_t_rawFit);
      
      m_tree->SetBranchAddress(m_t_s_processedMaxFullDelayData.c_str(),&m_t_processedMaxFullDelayData);
      m_tree->SetBranchAddress(m_t_s_processedFitFullDelayData.c_str(),&m_t_processedFitFullDelayData);
      m_tree->SetBranchAddress(m_t_s_processedMaxPeakValue.c_str(),    &m_t_processedMaxPeakValue);
      m_tree->SetBranchAddress(m_t_s_processedMaxPeakBin.c_str(),      &m_t_processedMaxPeakBin);
      m_tree->SetBranchAddress(m_t_s_processedFitPeakValue.c_str(),    &m_t_processedFitPeakValue);
      m_tree->SetBranchAddress(m_t_s_processedFitPeakBin.c_str(),      &m_t_processedFitPeakBin);
      m_tree->SetBranchAddress(m_t_s_processedFit.c_str(),             &m_t_processedFit);
      
      m_tree->SetBranchAddress(m_t_s_errorCode.c_str(),                &m_t_errorCode);
      
      m_tree->SetBranchAddress(m_t_s_isProcessed.c_str(),              &m_t_isProcessed);
   }
   else{
      m_tree->SetBranchAddress(m_t_s_newFullDelayData.c_str(),      &m_t_newFullDelayData);
      m_tree->SetBranchAddress(m_t_s_rawPeakValue.c_str(),          &m_t_rawPeakValue);
      m_tree->SetBranchAddress(m_t_s_rawPeakBin.c_str(),            &m_t_rawPeakBin);
      m_tree->SetBranchAddress(m_t_s_processedPeakValue.c_str(),    &m_t_processedPeakValue);
      m_tree->SetBranchAddress(m_t_s_processedPeakBin.c_str(),      &m_t_processedPeakBin);
   }
}

unsigned int ShapeMakerTree::FindEntry(const L1CaloChannelId findCoolId){
   
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
      for(unsigned int entry=m_currentEntry-1;entry>=0;--entry){
         m_tree->GetEntry(entry);
         
         if(m_t_coolId == findCoolId.GetId()){
            m_currentEntry = entry;
            return m_currentEntry;
         }
         
      }
   }
   else if(m_t_coolId > findCoolId.GetId()){
      
      for(unsigned int entry=m_currentEntry-1;entry>=0;--entry){
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

void ShapeMakerTree::Print(void) const{
   
   std::cout << "Cool Id 0x" << std::hex << m_t_coolId << std::dec << std::endl;
   std::cout << "isEnabled: " << (int)m_t_isEnabled << " isValid: " << (int)m_t_isValid << std::endl;
   std::cout << "ped mean: " << m_t_pedestalMean << " sigma: " << m_t_pedestalSigma << std::endl;
   std::cout << "rising slope mean: " << m_t_risingSlopeMean << " sigma: " << m_t_risingSlopeSigma << std::endl;
   std::cout << "currentFullDelayData: " << m_t_currentFullDelayData << std::endl;
   m_t_rawSignalShape->Print();
   m_t_processedSignalShape->Print();
   if(m_useNewTree){
      std::cout << std::endl;
      std::cout << "rawMaxFullDelayData: " << m_t_rawMaxFullDelayData << " rawFitFullDelayData: " << m_t_rawFitFullDelayData << std::endl;
      std::cout << "rawMaxPeakValue: " << m_t_rawMaxPeakValue << " rawMaxPeakBin: " << m_t_rawMaxPeakValue << std::endl;
      std::cout << "rawFitPeakValue: " << m_t_rawMaxPeakValue << " rawFitPeakBin: " << m_t_rawMaxPeakValue << std::endl;
      m_t_rawFit->Print();
      
      std::cout << "processedMaxFullDelayData: " << m_t_processedMaxFullDelayData << " processedFitFullDelayData: " << m_t_processedFitFullDelayData << std::endl;
      std::cout << "processedMaxPeakValue: " << m_t_processedMaxPeakValue << " processedMaxPeakBin: " << m_t_processedMaxPeakValue << std::endl;
      std::cout << "processedFitPeakValue: " << m_t_processedMaxPeakValue << " processedFitPeakBin: " << m_t_processedMaxPeakValue << std::endl;
      m_t_processedFit->Print();
      
      std::cout << "errorCode: " << m_t_errorCode << std::endl;
      std::cout << "isProcessed: " << (int)m_t_isProcessed << std::endl;
   }
   else{
      std::cout << " newFullDelayData: " << m_t_newFullDelayData << std::endl;
      
      std::cout << "rawPeakValue: " << m_t_rawPeakValue << " rawPeakBin: " << m_t_rawPeakValue << std::endl;
      std::cout << "processedPeakValue: " << m_t_processedPeakValue << " processedPeakBin: " << m_t_processedPeakValue << std::endl;
   }
   std::cout << std::endl;
}

unsigned int ShapeMakerTree::GetDacForRegion(const CaloDivision& region) const{
   if(region.IsLArFCAL1C() || region.IsLArFCAL1A()
      || region.IsLArFCAL23A() || region.IsLArFCAL23C()){
      
      return m_dacFcal;
   }
   else if(region.IsLArEMECC() || region.IsLArEMECA()
           || region.IsLArOverlapC() || region.IsLArOverlapA()){
      
      return m_dacEmec;
   }
   else if(region.IsLArEMBC() || region.IsLArEMBA()
           || region.IsTileEBC() || region.IsTileEBA()
           || region.IsTileLBC() || region.IsTileLBA()){
      
      return m_dacBarrel;
   }
   else if(region.IsLArHECC() || region.IsLArHECA()){
      
      return m_dacHec;
   }
   else{
      std::cerr << "[ShapeMakerTree::GetDacForId] ERROR region, " << region.GetString() << ", not found.\n";
   }
   
   return 0;
   
}


