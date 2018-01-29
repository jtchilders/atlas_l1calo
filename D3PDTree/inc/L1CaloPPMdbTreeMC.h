//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Sep 14 09:38:26 2010 by ROOT version 5.22/00d
// from TTree L1CaloPPMdbTree/L1CaloPPMdbTree
// found on file: L1CaloD3PD.root
//////////////////////////////////////////////////////////

#ifndef L1CaloPPMdbTreeMC_h
#define L1CaloPPMdbTreeMC_h

#include <vector>

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>


class L1CaloPPMdbTreeMC {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   std::vector<double>  *eta;
   std::vector<double>  *l1caloPhi;
   std::vector<double>  *atlasPhi;
   std::vector<unsigned int> *CoolId;
   std::vector<double>  *DacOffset;
   std::vector<double>  *DacSlope;
   std::vector<double>  *PedMean;
   std::vector<int>     *PedValue;
   std::vector<int>     *FullDelayData;
   std::vector<int>     *SatBcidThreshLow;
   std::vector<int>     *SatBcidThreshHigh;
   std::vector<int>     *SatBcidLevel;
   std::vector<int>     *BcidEnergyRangeLow;
   std::vector<int>     *BcidEnergyRangeHigh;
   std::vector<int>     *FirStartBit;
   std::vector<int>     *FirCoeff1;
   std::vector<int>     *FirCoeff2;
   std::vector<int>     *FirCoeff3;
   std::vector<int>     *FirCoeff4;
   std::vector<int>     *FirCoeff5;
   std::vector<int>     *LutStrategy;
   std::vector<int>     *LutOffset;
   std::vector<int>     *LutNoiseCut;
   std::vector<int>     *LutSlope;
   std::vector<int>     *NCaloCells;
   std::vector<std::vector<double> > *RxGain;
   std::vector<std::vector<int> > *RxStatus;

   // List of branches
   TBranch        *b_eta;   //!
   TBranch        *b_l1caloPhi;   //!
   TBranch        *b_atlasPhi;   //!
   TBranch        *b_CoolId;   //!
   TBranch        *b_DacOffset;   //!
   TBranch        *b_DacSlope;   //!
   TBranch        *b_PedMean;   //!
   TBranch        *b_PedValue;   //!
   TBranch        *b_FullDelayData;   //!
   TBranch        *b_SatBcidThreshLow;   //!
   TBranch        *b_SatBcidThreshHigh;   //!
   TBranch        *b_SatBcidLevel;   //!
   TBranch        *b_BcidEnergyRangeLow;   //!
   TBranch        *b_BcidEnergyRangeHigh;   //!
   TBranch        *b_FirStartBit;   //!
   TBranch        *b_FirCoeff1;   //!
   TBranch        *b_FirCoeff2;   //!
   TBranch        *b_FirCoeff3;   //!
   TBranch        *b_FirCoeff4;   //!
   TBranch        *b_FirCoeff5;   //!
   TBranch        *b_LutStrategy;   //!
   TBranch        *b_LutOffset;   //!
   TBranch        *b_LutNoiseCut;   //!
   TBranch        *b_LutSlope;   //!
   TBranch        *b_NCaloCells;   //!
   TBranch        *b_RxGain;   //!
   TBranch        *b_RxStatus;   //!

   L1CaloPPMdbTreeMC(TTree *tree=0);
   virtual ~L1CaloPPMdbTreeMC();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef L1CaloPPMdbTreeMC_cxx
L1CaloPPMdbTreeMC::L1CaloPPMdbTreeMC(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("L1CaloD3PD.root");
      if (!f) {
         f = new TFile("L1CaloD3PD.root");
      }
      tree = (TTree*)gDirectory->Get("L1CaloPPMdbTree");

   }
   Init(tree);
}

L1CaloPPMdbTreeMC::~L1CaloPPMdbTreeMC()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t L1CaloPPMdbTreeMC::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t L1CaloPPMdbTreeMC::LoadTree(Long64_t entry)
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

void L1CaloPPMdbTreeMC::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   eta = 0;
   l1caloPhi = 0;
   atlasPhi = 0;
   CoolId = 0;
   DacOffset = 0;
   DacSlope = 0;
   PedMean = 0;
   PedValue = 0;
   FullDelayData = 0;
   SatBcidThreshLow = 0;
   SatBcidThreshHigh = 0;
   SatBcidLevel = 0;
   BcidEnergyRangeLow = 0;
   BcidEnergyRangeHigh = 0;
   FirStartBit = 0;
   FirCoeff1 = 0;
   FirCoeff2 = 0;
   FirCoeff3 = 0;
   FirCoeff4 = 0;
   FirCoeff5 = 0;
   LutStrategy = 0;
   LutOffset = 0;
   LutNoiseCut = 0;
   LutSlope = 0;
   NCaloCells = 0;
   RxGain = 0;
   RxStatus = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

//    fChain->SetBranchAddress("eta", &eta, &b_eta);
//    fChain->SetBranchAddress("l1caloPhi", &l1caloPhi, &b_l1caloPhi);
//    fChain->SetBranchAddress("atlasPhi", &atlasPhi, &b_atlasPhi);
   fChain->SetBranchAddress("CoolId", &CoolId, &b_CoolId);
//    fChain->SetBranchAddress("DacOffset", &DacOffset, &b_DacOffset);
//    fChain->SetBranchAddress("DacSlope", &DacSlope, &b_DacSlope);
//    fChain->SetBranchAddress("PedMean", &PedMean, &b_PedMean);
//    fChain->SetBranchAddress("PedValue", &PedValue, &b_PedValue);
//    fChain->SetBranchAddress("FullDelayData", &FullDelayData, &b_FullDelayData);
   fChain->SetBranchAddress("SatBcidThreshLow", &SatBcidThreshLow, &b_SatBcidThreshLow);
   fChain->SetBranchAddress("SatBcidThreshHigh", &SatBcidThreshHigh, &b_SatBcidThreshHigh);
   fChain->SetBranchAddress("SatBcidLevel", &SatBcidLevel, &b_SatBcidLevel);
//    fChain->SetBranchAddress("BcidEnergyRangeLow", &BcidEnergyRangeLow, &b_BcidEnergyRangeLow);
//    fChain->SetBranchAddress("BcidEnergyRangeHigh", &BcidEnergyRangeHigh, &b_BcidEnergyRangeHigh);
   fChain->SetBranchAddress("FirStartBit", &FirStartBit, &b_FirStartBit);
   fChain->SetBranchAddress("FirCoeff1", &FirCoeff1, &b_FirCoeff1);
   fChain->SetBranchAddress("FirCoeff2", &FirCoeff2, &b_FirCoeff2);
   fChain->SetBranchAddress("FirCoeff3", &FirCoeff3, &b_FirCoeff3);
   fChain->SetBranchAddress("FirCoeff4", &FirCoeff4, &b_FirCoeff4);
   fChain->SetBranchAddress("FirCoeff5", &FirCoeff5, &b_FirCoeff5);
//    fChain->SetBranchAddress("LutStrategy", &LutStrategy, &b_LutStrategy);
//    fChain->SetBranchAddress("LutOffset", &LutOffset, &b_LutOffset);
//    fChain->SetBranchAddress("LutNoiseCut", &LutNoiseCut, &b_LutNoiseCut);
//    fChain->SetBranchAddress("LutSlope", &LutSlope, &b_LutSlope);
//    fChain->SetBranchAddress("NCaloCells", &NCaloCells, &b_NCaloCells);
//    fChain->SetBranchAddress("RxGain", &RxGain, &b_RxGain);
//    fChain->SetBranchAddress("RxStatus", &RxStatus, &b_RxStatus);
   Notify();
}

Bool_t L1CaloPPMdbTreeMC::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void L1CaloPPMdbTreeMC::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t L1CaloPPMdbTreeMC::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef L1CaloPPMdbTreeMC_cxx
