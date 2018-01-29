////////////////////////////////////////////////////////////////
/// Test of the Tree Package                                  //
/// Developed by: Taylor Childers                             //
/// Feel free to email with questions                         //
////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>

#include "Tree.h"
#include "AccessMode.h"
#include "TypeTraits.h"

#include "TH1I.h"
#include "TProfile.h"
#include "TCanvas.h"
#include "TApplication.h"

int main(int argc,char** argv){
   
   
   // I commented this out, but left it in to give you an example of how to use the TypeTraits class.
//    std::cout << " int plain type: " << TypeTraits<int>::isPlainType << std::endl;
//    std::cout << " int isConst: " << TypeTraits<int>::isConst << std::endl;
//    std::cout << " int isPointerType: " << TypeTraits<int>::isPointerType << std::endl;
//    std::cout << " int isReferenceType: " << TypeTraits<int>::isReferenceType << std::endl;
//    std::cout << " int isRvalueReferenceType: " << TypeTraits<int>::isRvalueReferenceType << std::endl;
//    std::cout << " int isClass: " << TypeTraits<int>::isClass << std::endl;
//    std::cout << std::endl;
//    
//    std::cout << " int* plain type: " << TypeTraits<int*>::isPlainType << std::endl;
//    std::cout << " int* isConst: " << TypeTraits<int*>::isConst << std::endl;
//    std::cout << " int* isPointerType: " << TypeTraits<int*>::isPointerType << std::endl;
//    std::cout << " int* isReferenceType: " << TypeTraits<int*>::isReferenceType << std::endl;
//    std::cout << " int* isRvalueReferenceType: " << TypeTraits<int*>::isRvalueReferenceType << std::endl;
//    std::cout << " int* isClass: " << TypeTraits<int*>::isClass << std::endl;
//    std::cout << std::endl;
//    
//    std::cout << " int const * plain type: " << TypeTraits<int const *>::isPlainType << std::endl;
//    std::cout << " int const * isConst: " << TypeTraits<int const *>::isConst << std::endl;
//    std::cout << " int const * isPointerType: " << TypeTraits<int const *>::isPointerType << std::endl;
//    std::cout << " int const * isReferenceType: " << TypeTraits<int const *>::isReferenceType << std::endl;
//    std::cout << " int const * isRvalueReferenceType: " << TypeTraits<int const *>::isRvalueReferenceType << std::endl;
//    std::cout << " int const * isClass: " << TypeTraits<int const *>::isClass << std::endl;
//    std::cout << std::endl;
//    
//    std::cout << " const int plain type: " << TypeTraits<const int>::isPlainType << std::endl;
//    std::cout << " const int isConst: " << TypeTraits<const int>::isConst << std::endl;
//    std::cout << " const int isPointerType: " << TypeTraits<const int>::isPointerType << std::endl;
//    std::cout << " const int isReferenceType: " << TypeTraits<const int>::isReferenceType << std::endl;
//    std::cout << " const int isRvalueReferenceType: " << TypeTraits<const int>::isRvalueReferenceType << std::endl;
//    std::cout << " const int isClass: " << TypeTraits<const int>::isClass << std::endl;
//    std::cout << std::endl;
//    
//    std::cout << " AccessMode plain type: " << TypeTraits<AccessMode>::isPlainType << std::endl;
//    std::cout << " AccessMode isConst: " << TypeTraits<AccessMode>::isConst << std::endl;
//    std::cout << " AccessMode isPointerType: " << TypeTraits<AccessMode>::isPointerType << std::endl;
//    std::cout << " AccessMode isReferenceType: " << TypeTraits<AccessMode>::isReferenceType << std::endl;
//    std::cout << " AccessMode isRvalueReferenceType: " << TypeTraits<AccessMode>::isRvalueReferenceType << std::endl;
//    std::cout << " AccessMode isClass: " << TypeTraits<AccessMode>::isClass << std::endl;
//    std::cout << std::endl;
//    
//    std::cout << " AccessMode* plain type: " << TypeTraits<AccessMode*>::isPlainType << std::endl;
//    std::cout << " AccessMode* isConst: " << TypeTraits<AccessMode*>::isConst << std::endl;
//    std::cout << " AccessMode* isPointerType: " << TypeTraits<AccessMode*>::isPointerType << std::endl;
//    std::cout << " AccessMode* isReferenceType: " << TypeTraits<AccessMode*>::isReferenceType << std::endl;
//    std::cout << " AccessMode* isRvalueReferenceType: " << TypeTraits<AccessMode*>::isRvalueReferenceType << std::endl;
//    std::cout << " AccessMode* isClass: " << TypeTraits<AccessMode*>::isClass << std::endl;
//    std::cout << std::endl;
   
   // WRITE MODE
   AccessMode mode(AccessMode::WRITE);
   // create a tree named "testTree" which will be saved to file "testTree.root"
   Tree *tree = new Tree(mode,"testTree","testTree.root");
   
   // create some branches for saving data
   tree->AddBranch<ULong64_t>("ulong64");
   tree->AddBranch<ULong_t>("ulong");
   tree->AddBranch<Long64_t>("long64");
   tree->AddBranch<Long_t>("long");
   tree->AddBranch<UInt_t>("uint");
   tree->AddBranch<Int_t>("int");
   tree->AddBranch<UShort_t>("ushort");
   tree->AddBranch<Short_t>("short");
   tree->AddBranch<UChar_t>("uchar");
   tree->AddBranch<Char_t>("char");
   tree->AddBranch<Double_t>("double");
   tree->AddBranch<Double32_t>("double32");
   tree->AddBranch<Float_t>("float");
   tree->AddBranch<Float16_t>("float16");
   tree->AddBranch<Bool_t>("bool");
   tree->AddBranch<TH1I>("TH1I");
   tree->AddBranch<TProfile>("TProfile");
   
   tree->AddBranch<std::vector<int> >("vectorInt");
   
   // make a loop to save a few entries in the tree.
   for(unsigned int i=0;i<10;++i){
      ULong64_t ulo64 = (ULong64_t)i;
      tree->SetBranchValue<ULong64_t>("ulong64",ulo64);
      ULong_t ulo = (ULong_t)i;
      tree->SetBranchValue<ULong_t>("ulong",ulo);
      Long64_t lo64 = (Long64_t)i;
      tree->SetBranchValue<Long64_t>("long64",lo64);
      Long_t lo = (Long_t)i;
      tree->SetBranchValue<Long_t>("long",lo);
      UInt_t uin = (UInt_t)i;
      tree->SetBranchValue<UInt_t>("uint",uin);
      Int_t in = (Int_t)i;
      tree->SetBranchValue<Int_t>("int",in);
      UShort_t ush = (UShort_t)i;
      tree->SetBranchValue<UShort_t>("ushort",ush);
      Short_t sh = (Short_t)i;
      tree->SetBranchValue<Short_t>("short",sh);
      UChar_t uch = (UChar_t)i;
      tree->SetBranchValue<UChar_t>("uchar",uch);
      Char_t ch = (Char_t)i;
      tree->SetBranchValue<Char_t>("char",ch);
      Double_t dou = (Double_t)i;
      tree->SetBranchValue<Double_t>("double",dou);
      Double32_t dou32 = (Double32_t)i;
      tree->SetBranchValue<Double32_t>("double32",dou32);
      Float_t flo = (Float_t)i;
      tree->SetBranchValue<Float_t>("float",flo);
      Float16_t flo16 = (Float16_t)i;
      tree->SetBranchValue<Float16_t>("float16",flo16);
      bool temp = i % 2;
      tree->SetBranchValue<bool>("bool",temp);
      
      // Fill some histograms
      TH1I *th1i = new TH1I("th1i","TH1I",10,0,10);
      th1i->Fill(i);
      tree->SetBranchValue<TH1I>("TH1I",*th1i);
      
      TProfile *tprofile = new TProfile("tprofile","TProfile",10,0,10);
      tprofile->Fill(i,i);tprofile->Fill(i,i+2);tprofile->Fill(i,i-1);
      tree->SetBranchValue<TProfile>("TProfile",*tprofile);
      
      std::vector<int> vint;
      vint.push_back(i);vint.push_back(i+1);
      tree->SetBranchValue<std::vector<int> >("vectorInt",vint);
      
      // fill the tree
      tree->Fill();
      
      // delete histograms
      delete th1i;
      th1i = 0;
      
      delete tprofile;
      tprofile = 0;
   }
   
   // end of fill so tree is written to file and file is closed.
   tree->EndFill();
   
   // delete tree for safe memory management
   delete tree;
   
   
   // READ MODE
   mode.SetReadMode();
   // create a tree named "testTree" which will be read from file "testTree.root"
   tree = new Tree(mode,"testTree","testTree.root");
   
   // add branches to the tree for holding the data that will be read.
   tree->AddBranch<ULong64_t>("ulong64");
   tree->AddBranch<ULong_t>("ulong");
   tree->AddBranch<Long64_t>("long64");
   tree->AddBranch<Long_t>("long");
   tree->AddBranch<UInt_t>("uint");
   tree->AddBranch<Int_t>("int");
   tree->AddBranch<UShort_t>("ushort");
   tree->AddBranch<Short_t>("short");
   tree->AddBranch<UChar_t>("uchar");
   tree->AddBranch<Char_t>("char");
   tree->AddBranch<Double_t>("double");
   tree->AddBranch<Double32_t>("double32");
   tree->AddBranch<Float_t>("float");
   tree->AddBranch<Float16_t>("float16");
   tree->AddBranch<Bool_t>("bool");
   tree->AddBranch<TH1I>("TH1I");
   tree->AddBranch<TProfile>("TProfile");
   tree->AddBranch<std::vector<int> >("vectorInt");
   
   // this branch does exist in tree, but wanted to test that tree doesn't crash.
   tree->AddBranch<int>("testNon_int"); 
   tree->AddBranch<TH1I>("testNon_class");
   
   // want to see the output from my histograms
   TApplication app("app",&argc,argv);
   TCanvas can("can","can",0,0,1200,600);
   can.Divide(2,1);
   
   // loop over the tree entries
   for(unsigned int i=0;i<tree->GetEntries();++i){
      // load entry i
      tree->GetEntry(i);
      
      // access standard data
      std::cout << "ulong64: " << std::hex << *tree->GetBranchValue<ULong64_t>("ulong64") << std::endl;
      std::cout << "ulong: "   << *tree->GetBranchValue<ULong_t>("ulong") << std::endl;
      std::cout << "long64: "  << *tree->GetBranchValue<Long64_t>("long64") << std::endl;
      std::cout << "long: "    << *tree->GetBranchValue<Long_t>("long") << std::endl;
      std::cout << "uint: "    << *tree->GetBranchValue<UInt_t>("uint") << std::endl;
      std::cout << "int: "     << *tree->GetBranchValue<Int_t>("int") << std::endl;
      std::cout << "ushort: "  << *tree->GetBranchValue<UShort_t>("ushort") << std::endl;
      std::cout << "short: "   << *tree->GetBranchValue<Short_t>("short") << std::endl;
      std::cout << "uchar: "   << (unsigned int)*tree->GetBranchValue<UChar_t>("uchar") << std::endl;
      std::cout << "char: "    << (int)*tree->GetBranchValue<Char_t>("char") << std::endl;
      std::cout << "double: "  << *tree->GetBranchValue<Double_t>("double") << std::endl;
      std::cout << "double32: "<< *tree->GetBranchValue<Double32_t>("double32") << std::endl;
      std::cout << "float: "   << *tree->GetBranchValue<Float_t>("float") << std::endl;
      std::cout << "float16: " << *tree->GetBranchValue<Float16_t>("float16") << std::endl;
      std::cout << "bool: "    << *tree->GetBranchValue<bool>("bool") << std::endl;
      
      // branch vector
      std::vector<int> *vint = tree->GetBranchValue<std::vector<int> >("vectorInt");
      for(unsigned int j=0;j<vint->size();++j){
         std::cout << "vint[" << j << "] = " << vint->at(j) << std::endl;
      }
      
      // branch that doesn't exist (testing for crash)
      std::cout << "testNon_int: "    << *tree->GetBranchValue<int>("testNon_int") << std::endl;
      std::cout << std::endl;
      
      // access and plot the histograms
      TH1I *th1i = tree->GetBranchValue<TH1I>("TH1I");
      if(th1i != 0){
         can.cd(1);
         th1i->Draw();
      }
      else{
         std::cout << "th1i not found\n";
      }
      
      TProfile *tprofile = tree->GetBranchValue<TProfile>("TProfile");
      if(tprofile != 0){
         can.cd(2);
         tprofile->Draw();
      }
      else{
         std::cout << "tprofile not found\n";
      }
      
      // try to access branch that doesn't exist (testing for crash)
      TH1I *testNon_class = tree->GetBranchValue<TH1I>("testNon_class");
      if(testNon_class != 0){
         can.cd(1);
         testNon_class->Draw();
      }
      else{
         std::cout << "testNon_int not found\n";
      }
      
      can.Update();
      std::cout << "press enter to continue...";
      std::cin.get();
      
      // delete TObjects after use so they don't take up memoery
      tree->DeleteRootObject<TH1I>("TH1I");
      tree->DeleteRootObject<TProfile>("TProfile");
      tree->DeleteRootObject<TH1I>("testNon_class"); // test for crash
   }
   
   // delete tree (deconstructor will close file ;) )
   delete tree;
   
   return 0;
}

