#include "Tree.h"

#include "TH1.h"

Tree::Tree(AccessMode accessMode,std::string treeName,std::string filename){
   Initialize();
   m_accessMode = accessMode;
   m_s_treeName = treeName;
   m_s_filename = filename;
   
   if(m_accessMode.IsReadMode()){ // Read Mode
      // read the tree from the file
      m_file = new TFile(m_s_filename.c_str(),"READ");
      if(!m_file->IsOpen()){
         std::cerr << "[Tree::Tree] Error opening file, " << m_s_filename.c_str() << " for reading.\n";
         return;
      }
      m_tree = (TTree*)m_file->Get(m_s_treeName.c_str());
   }
   else if(m_accessMode.IsWriteMode()){ // Write Mode
      // open a new file for the tree and create the tree
      m_file = new TFile(m_s_filename.c_str(),"RECREATE");
      if(!m_file->IsOpen()){
         std::cerr << "[Tree::Tree] Error opening file, " << m_s_filename.c_str() << " for writing.\n";
         return;
      }
      m_tree = new TTree(m_s_treeName.c_str(),m_s_treeName.c_str());
   }
}

Tree::~Tree(void){
   
   if(m_map_branches->size() > 0){
      std::map<std::string,AbstractBranch*>::iterator itr,end;
      itr = m_map_branches->begin();
      end = m_map_branches->end();
      
      for(;itr != end;++itr){
         AbstractBranch *abBr = itr->second;
         DataType temp = abBr->GetDataType();
         
         if(temp.IsULONG64()){
            Branch<ULong64_t>* branch = static_cast<Branch<ULong64_t>*>(abBr);
            delete branch;
            branch = 0;
         }
         else if(temp.IsLONG64()){
            Branch<Long64_t>* branch = static_cast<Branch<Long64_t>*>(abBr);
            delete branch;
            branch = 0;
         }
         else if(temp.IsULONG()){
            Branch<ULong_t>* branch = static_cast<Branch<ULong_t>*>(abBr);
            delete branch;
            branch = 0;
         }
         else if(temp.IsLONG()){
            Branch<Long_t>* branch = static_cast<Branch<Long_t>*>(abBr);
            delete branch;
            branch = 0;
         }
         else if(temp.IsUINT()){
            Branch<UInt_t>* branch = static_cast<Branch<UInt_t>*>(abBr);
            delete branch;
            branch = 0;
         }
         else if(temp.IsINT()){
            Branch<Int_t>* branch = static_cast<Branch<Int_t>*>(abBr);
            delete branch;
            branch = 0;
         }
         else if(temp.IsUSHORT()){
            Branch<UShort_t>* branch = static_cast<Branch<UShort_t>*>(abBr);
            delete branch;
            branch = 0;
         }
         else if(temp.IsSHORT()){
            Branch<Short_t>* branch = static_cast<Branch<Short_t>*>(abBr);
            delete branch;
            branch = 0;
         }
         else if(temp.IsUCHAR()){
            Branch<UChar_t>* branch = static_cast<Branch<UChar_t>*>(abBr);
            delete branch;
            branch = 0;
         }
         else if(temp.IsCHAR()){
            Branch<Char_t>* branch = static_cast<Branch<Char_t>*>(abBr);
            delete branch;
            branch = 0;
         }
         else if(temp.IsDOUBLE32()){
            Branch<Double32_t>* branch = static_cast<Branch<Double32_t>*>(abBr);
            delete branch;
            branch = 0;
         }
         else if(temp.IsDOUBLE()){
            Branch<Double_t>* branch = static_cast<Branch<Double_t>*>(abBr);
            delete branch;
            branch = 0;
         }
         else if(temp.IsFLOAT16()){
            Branch<Float16_t>* branch = static_cast<Branch<Float16_t>*>(abBr);
            delete branch;
            branch = 0;
         }
         else if(temp.IsFLOAT()){
            Branch<Float_t>* branch = static_cast<Branch<Float_t>*>(abBr);
            delete branch;
            branch = 0;
         }
         else if(temp.IsBOOL()){
            Branch<Bool_t>* branch = static_cast<Branch<Bool_t>*>(abBr);
            delete branch;
            branch = 0;
         }
         else if(temp.IsTH1C()){
            Branch<TH1C>* branch = static_cast<Branch<TH1C>*>(abBr);
            delete branch;
            branch = 0;
         }
         else if(temp.IsTH1S()){
            Branch<TH1S>* branch = static_cast<Branch<TH1S>*>(abBr);
            delete branch;
            branch = 0;
         }
         else if(temp.IsTH1I()){
            Branch<TH1I>* branch = static_cast<Branch<TH1I>*>(abBr);
            delete branch;
            branch = 0;
         }
         else if(temp.IsTH1F()){
            Branch<TH1F>* branch = static_cast<Branch<TH1F>*>(abBr);
            delete branch;
            branch = 0;
         }
         else if(temp.IsTH1D()){
            Branch<TH1D>* branch = static_cast<Branch<TH1D>*>(abBr);
            delete branch;
            branch = 0;
         }
         else if(temp.IsTH2C()){
            Branch<TH2C>* branch = static_cast<Branch<TH2C>*>(abBr);
            delete branch;
            branch = 0;
         }
         else if(temp.IsTH2S()){
            Branch<TH2S>* branch = static_cast<Branch<TH2S>*>(abBr);
            delete branch;
            branch = 0;
         }
         else if(temp.IsTH2I()){
            Branch<TH2I>* branch = static_cast<Branch<TH2I>*>(abBr);
            delete branch;
            branch = 0;
         }
         else if(temp.IsTH2F()){
            Branch<TH2F>* branch = static_cast<Branch<TH2F>*>(abBr);
            delete branch;
            branch = 0;
         }
         else if(temp.IsTH2D()){
            Branch<TH2D>* branch = static_cast<Branch<TH2D>*>(abBr);
            delete branch;
            branch = 0;
         }
         else if(temp.IsTPROFILE()){
            Branch<TProfile>* branch = static_cast<Branch<TProfile>*>(abBr);
            delete branch;
            branch = 0;
         }
         else if(temp.IsTPROFILE2D()){
            Branch<TProfile2D>* branch = static_cast<Branch<TProfile2D>*>(abBr);
            delete branch;
            branch = 0;
         }
         else if(temp.IsTF1()){
            Branch<TF1>* branch = static_cast<Branch<TF1>*>(abBr);
            delete branch;
            branch = 0;
         }
         else
            std::cerr << "[Tree::~Tree] ERROR branch, " << abBr->GetName() << ", data type not found. Not properly deleted.\n";
         
         
      } // end for(itr)
      
   } // end if(branches exist)
   
   
   // delete tree --- causes seg fault
//    if(m_tree != 0){
//       m_tree->Delete();
//       m_tree = 0;
//    }
   
   
   // delete/close file
   if(m_file != 0){
      if(m_file->IsOpen()){
         if(!m_endFillCalled && m_accessMode.IsWriteMode()) EndFill();
         else m_file->Close();
      }
      delete m_file;
      m_file = 0;
   }
   
   
   
}

void Tree::Initialize(void){
   m_map_branches = new std::map<std::string,AbstractBranch*>;
   m_accessMode.SetReadMode(); // default read mode
   m_tree = 0;
   m_s_treeName.clear();
   m_file = 0;
   m_s_filename.clear();
   m_endFillCalled = false;
   TH1::AddDirectory(0);
}

// User function to end tree fill
bool Tree::EndFill(void){
   
   if(m_accessMode.IsWriteMode()){
      m_file->cd();
      m_tree->Write();
      m_file->Close();
      m_endFillCalled = true;
   }
   else
      std::cerr << "[Tree::EndFill] In READ mode, no fill to end.\n";
   
   return false;
   
}

