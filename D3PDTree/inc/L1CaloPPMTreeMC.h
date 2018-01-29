//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Sep 14 09:38:38 2010 by ROOT version 5.22/00d
// from TTree L1CaloPPMTree/L1CaloPPMTree
// found on file: L1CaloD3PD.root
//////////////////////////////////////////////////////////

#ifndef L1CaloPPMTreeMC_h
#define L1CaloPPMTreeMC_h

#include <vector>

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class L1CaloPPMTreeMC {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   UInt_t          RunNumber;
   UInt_t          EventNumber;
   UInt_t          timestamp;
   UInt_t          timestamp_ns;
   UInt_t          lbn;
   UInt_t          bcid;
   UInt_t          detmask0;
   UInt_t          detmask1;
   std::vector<unsigned int> *emCoolId;
   std::vector<double>  *emTTCellsEnergy;
   std::vector<double>  *emTTCellsEt;
   std::vector<int>     *emPeak;
   std::vector<int>     *emADCPeak;
   std::vector<std::vector<int> > *emLUT;
   std::vector<std::vector<int> > *emADC;
   std::vector<int>     *emEnergy;
   std::vector<std::vector<int> > *emBCIDvec;
   std::vector<std::vector<int> > *emBCIDext;
   std::vector<int>     *emError;
   std::vector<int>     *emBCID;
   std::vector<int>     *emIsSaturated;
   std::vector<int>     *emBadCalo;
   std::vector<int>     *emDeadChannel;
   std::vector<double>  *emCaloQuality;
   std::vector<unsigned int> *hadCoolId;
   std::vector<double>  *hadTTCellsEnergy;
   std::vector<double>  *hadTTCellsEt;
   std::vector<double>  *hadTileCellsEnergy;
   std::vector<int>     *hadPeak;
   std::vector<int>     *hadADCPeak;
   std::vector<std::vector<int> > *hadLUT;
   std::vector<std::vector<int> > *hadADC;
   std::vector<int>     *hadEnergy;
   std::vector<std::vector<int> > *hadBCIDvec;
   std::vector<std::vector<int> > *hadBCIDext;
   std::vector<int>     *hadError;
   std::vector<int>     *hadBCID;
   std::vector<int>     *hadIsSaturated;
   std::vector<int>     *hadBadCalo;
   std::vector<int>     *hadDeadChannel;
   std::vector<double>  *hadCaloQuality;

   // List of branches
   TBranch        *b_RunNumber;   //!
   TBranch        *b_EventNumber;   //!
   TBranch        *b_timestamp;   //!
   TBranch        *b_timestamp_ns;   //!
   TBranch        *b_lbn;   //!
   TBranch        *b_bcid;   //!
   TBranch        *b_detmask0;   //!
   TBranch        *b_detmask1;   //!
   TBranch        *b_emCoolId;   //!
   TBranch        *b_emTTCellsEnergy;   //!
   TBranch        *b_emTTCellsEt;   //!
   TBranch        *b_emPeak;   //!
   TBranch        *b_emADCPeak;   //!
   TBranch        *b_emLUT;   //!
   TBranch        *b_emADC;   //!
   TBranch        *b_emEnergy;   //!
   TBranch        *b_emBCIDvec;   //!
   TBranch        *b_emBCIDext;   //!
   TBranch        *b_emError;   //!
   TBranch        *b_emBCID;   //!
   TBranch        *b_emIsSaturated;   //!
   TBranch        *b_emBadCalo;   //!
   TBranch        *b_emDeadChannel;   //!
   TBranch        *b_emCaloQuality;   //!
   TBranch        *b_hadCoolId;   //!
   TBranch        *b_hadTTCellsEnergy;   //!
   TBranch        *b_hadTTCellsEt;   //!
   TBranch        *b_hadTileCellsEnergy;   //!
   TBranch        *b_hadPeak;   //!
   TBranch        *b_hadADCPeak;   //!
   TBranch        *b_hadLUT;   //!
   TBranch        *b_hadADC;   //!
   TBranch        *b_hadEnergy;   //!
   TBranch        *b_hadBCIDvec;   //!
   TBranch        *b_hadBCIDext;   //!
   TBranch        *b_hadError;   //!
   TBranch        *b_hadBCID;   //!
   TBranch        *b_hadIsSaturated;   //!
   TBranch        *b_hadBadCalo;   //!
   TBranch        *b_hadDeadChannel;   //!
   TBranch        *b_hadCaloQuality;   //!

   L1CaloPPMTreeMC(TTree *tree=0);
   virtual ~L1CaloPPMTreeMC();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef L1CaloPPMTreeMC_cxx
L1CaloPPMTreeMC::L1CaloPPMTreeMC(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("L1CaloD3PD.root");
      if (!f) {
         f = new TFile("L1CaloD3PD.root");
      }
      tree = (TTree*)gDirectory->Get("L1CaloPPMTree");

   }
   Init(tree);
}

L1CaloPPMTreeMC::~L1CaloPPMTreeMC()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t L1CaloPPMTreeMC::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t L1CaloPPMTreeMC::LoadTree(Long64_t entry)
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

void L1CaloPPMTreeMC::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   emCoolId = 0;
   emTTCellsEnergy = 0;
   emTTCellsEt = 0;
   emPeak = 0;
   emADCPeak = 0;
   emLUT = 0;
   emADC = 0;
   emEnergy = 0;
   emBCIDvec = 0;
   emBCIDext = 0;
   emError = 0;
   emBCID = 0;
   emIsSaturated = 0;
   emBadCalo = 0;
   emDeadChannel = 0;
   emCaloQuality = 0;
   hadCoolId = 0;
   hadTTCellsEnergy = 0;
   hadTTCellsEt = 0;
   hadTileCellsEnergy = 0;
   hadPeak = 0;
   hadADCPeak = 0;
   hadLUT = 0;
   hadADC = 0;
   hadEnergy = 0;
   hadBCIDvec = 0;
   hadBCIDext = 0;
   hadError = 0;
   hadBCID = 0;
   hadIsSaturated = 0;
   hadBadCalo = 0;
   hadDeadChannel = 0;
   hadCaloQuality = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("RunNumber", &RunNumber, &b_RunNumber);
   fChain->SetBranchAddress("EventNumber", &EventNumber, &b_EventNumber);
//    fChain->SetBranchAddress("timestamp", &timestamp, &b_timestamp);
//    fChain->SetBranchAddress("timestamp_ns", &timestamp_ns, &b_timestamp_ns);
//    fChain->SetBranchAddress("lbn", &lbn, &b_lbn);
   fChain->SetBranchAddress("bcid", &bcid, &b_bcid);
//    fChain->SetBranchAddress("detmask0", &detmask0, &b_detmask0);
//    fChain->SetBranchAddress("detmask1", &detmask1, &b_detmask1);
   fChain->SetBranchAddress("emCoolId", &emCoolId, &b_emCoolId);
//    fChain->SetBranchAddress("emTTCellsEnergy", &emTTCellsEnergy, &b_emTTCellsEnergy);
//    fChain->SetBranchAddress("emTTCellsEt", &emTTCellsEt, &b_emTTCellsEt);
//    fChain->SetBranchAddress("emPeak", &emPeak, &b_emPeak);
   fChain->SetBranchAddress("emADCPeak", &emADCPeak, &b_emADCPeak);
//    fChain->SetBranchAddress("emLUT", &emLUT, &b_emLUT);
   fChain->SetBranchAddress("emADC", &emADC, &b_emADC);
//    fChain->SetBranchAddress("emEnergy", &emEnergy, &b_emEnergy);
//    fChain->SetBranchAddress("emBCIDvec", &emBCIDvec, &b_emBCIDvec);
//    fChain->SetBranchAddress("emBCIDext", &emBCIDext, &b_emBCIDext);
//    fChain->SetBranchAddress("emError", &emError, &b_emError);
   fChain->SetBranchAddress("emBCID", &emBCID, &b_emBCID);
//    fChain->SetBranchAddress("emIsSaturated", &emIsSaturated, &b_emIsSaturated);
//    fChain->SetBranchAddress("emBadCalo", &emBadCalo, &b_emBadCalo);
//    fChain->SetBranchAddress("emDeadChannel", &emDeadChannel, &b_emDeadChannel);
//    fChain->SetBranchAddress("emCaloQuality", &emCaloQuality, &b_emCaloQuality);
   fChain->SetBranchAddress("hadCoolId", &hadCoolId, &b_hadCoolId);
//    fChain->SetBranchAddress("hadTTCellsEnergy", &hadTTCellsEnergy, &b_hadTTCellsEnergy);
//    fChain->SetBranchAddress("hadTTCellsEt", &hadTTCellsEt, &b_hadTTCellsEt);
//    fChain->SetBranchAddress("hadTileCellsEnergy", &hadTileCellsEnergy, &b_hadTileCellsEnergy);
//    fChain->SetBranchAddress("hadPeak", &hadPeak, &b_hadPeak);
   fChain->SetBranchAddress("hadADCPeak", &hadADCPeak, &b_hadADCPeak);
//    fChain->SetBranchAddress("hadLUT", &hadLUT, &b_hadLUT);
   fChain->SetBranchAddress("hadADC", &hadADC, &b_hadADC);
//    fChain->SetBranchAddress("hadEnergy", &hadEnergy, &b_hadEnergy);
//    fChain->SetBranchAddress("hadBCIDvec", &hadBCIDvec, &b_hadBCIDvec);
//    fChain->SetBranchAddress("hadBCIDext", &hadBCIDext, &b_hadBCIDext);
//    fChain->SetBranchAddress("hadError", &hadError, &b_hadError);
   fChain->SetBranchAddress("hadBCID", &hadBCID, &b_hadBCID);
//    fChain->SetBranchAddress("hadIsSaturated", &hadIsSaturated, &b_hadIsSaturated);
//    fChain->SetBranchAddress("hadBadCalo", &hadBadCalo, &b_hadBadCalo);
//    fChain->SetBranchAddress("hadDeadChannel", &hadDeadChannel, &b_hadDeadChannel);
//    fChain->SetBranchAddress("hadCaloQuality", &hadCaloQuality, &b_hadCaloQuality);
   Notify();
}

Bool_t L1CaloPPMTreeMC::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void L1CaloPPMTreeMC::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t L1CaloPPMTreeMC::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef L1CaloPPMTreeMC_cxx
