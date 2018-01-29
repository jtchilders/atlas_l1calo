////////////////////////////////////////////////////////////////
/// Tree Class                                                //
/// Developed by: Taylor Childers                             //
/// Feel free to email with questions                         //
////////////////////////////////////////////////////////////////
/// This package was developed to provide an easy to use      //
/// interface to the ROOT TTree.                              //
///                                                           //
/// It comes with some support classes:                       //
/// 1. AbstractBranch, a virtual base class                   //
///    This classs holds the common branch information, like  //
///    the name and type of data the branch holds.            //
/// 2. Branch, derived from AbstractBranch                    //
///    This is a template class designed to hold standard C   //
///    data types and ROOT classes derived from TObject,      //
///    namely things like TH1s, TH2s, TProfiles. For a list   //
///    see the enum DATA_TYPE in the DataType class.          //
/// 3. DataType, defines the allowed data types with which a  //
///    Branch can be defined.                                 //
/// 4. TypeTraits, compile-time class that gives some info    //
///    about the datatype that is passed to the template list //
///    For Example, TypeTraits<int>::isPlainType evaluates as //
///    true, whereas TypeTraits<TH1I>::isPlainType evalates   //
///    as false, however, TypeTraits<TH1I>::isClass is true.  //
/// 5. AccessMode, class that defines how you plan to use the //
///    Tree, in Read or Write mode. This is a class you will  //
///    actually need to instantiate to use the Tree class.    //
///                                                           //
/// The Tree class can be used in two ways:                   //
/// 1. Read Mode, used for reading a tree from a ROOT file    //
///    accessing it's branches.                               //
/// 2. Write Mode, used for creating a new tree, filling      //
///    new branches and writing the tree to a ROOT file.      //
///                                                           //
/// For a short example of how to use this class you should   //
/// have a look at TestTree.cxx in the src directory.         //
///                                                           //
/// There is one important note for memory management:        //
/// If you are in Read mode and looping over a branch that is //
/// a ROOT TObject, you should call the DeleteRootObject<>()  //
/// method at the end of your loop because for these types of //
/// branches ROOT reads the data from file and allocates the  //
/// memory dynamically but never deletes the object.          //
////////////////////////////////////////////////////////////////


#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <string>
#include <map>

#include "TTree.h"
#include "TFile.h"

#include "AbstractBranch.h"
#include "Branch.h"
#include "AccessMode.h"
#include "DataType.h"

class Tree{
public:
   Tree(AccessMode accessMode,std::string treeName,std::string filename);
   ~Tree(void);
   
   bool EndFill(void);
   
   template <typename T>
   bool AddBranch(std::string b_name);
   
   template <typename T>
   Branch<T>* GetBranch(std::string b_name) const;
   
   int Fill(void){
      if(m_accessMode.IsWriteMode())
         return m_tree->Fill();
      else
         std::cerr << "[Tree::Fill] In READ mode, cannot fill.\n";
      return 0;
   };
   Long64_t GetEntries(void) const {return m_tree->GetEntries();};
   
   int GetEntry(Long64_t entry = 0,int getall = 0){
      if(m_accessMode.IsReadMode())
         return m_tree->GetEntry(entry,getall);
      else
         std::cerr << "[Tree::GetEntry] In WRITE mode, cannot GetEntry.\n";
      return 0;
   };
   
   template <typename T>
   bool DeleteRootObject(std::string b_name);
   
   TTree* GetTree(void){return m_tree;};
   
   template <typename T>
         bool SetBranchValue(std::string b_name,T& b_value);
   template <typename T>
         T* GetBranchValue(std::string b_name);
   
private:
   TTree *m_tree;
   std::string m_s_treeName;
   
   TFile *m_file;
   std::string m_s_filename;
   
   std::map<std::string,AbstractBranch*> *m_map_branches;
   
   AccessMode m_accessMode;
   
   bool m_endFillCalled;
   
   void Initialize(void);
   
   template <typename T>
   bool AddBranchReadMode(std::string& b_name);
   template <typename T>
   bool AddBranchWriteMode(std::string& b_name);
   
   template <typename T>
   bool DataTypeOK(T& obj);
   
};


// User function, just determines which mode it is and calls the private
// functions below
template <typename T>
inline bool Tree::AddBranch(std::string b_name){
   
   if(m_accessMode.IsReadMode()) // Read Mode
      return AddBranchReadMode<T>(b_name);
   else if(m_accessMode.IsWriteMode()) // Write Mode
      return AddBranchWriteMode<T>(b_name);
   
   return false;
}

// used to add a new tree address for readout
template <typename T>
inline bool Tree::AddBranchReadMode(std::string& b_name){
   
   // Should be checking type
   Branch<T> *branch = new Branch<T>;
   branch->SetName(b_name);
   branch->SetBranchAddress(m_tree);
   (*m_map_branches)[b_name] = dynamic_cast<AbstractBranch*>(branch);
   
   return true;
   
}

template <typename T>
bool Tree::AddBranchWriteMode(std::string& b_name){
   
   // Should be checking type
   Branch<T> *branch = new Branch<T>;
   branch->SetName(b_name);
   branch->CreateBranch(m_tree);
   (*m_map_branches)[b_name] = dynamic_cast<AbstractBranch*>(branch);
   
   return true;
}


// Set a value in a branch
template <typename T>
inline bool Tree::SetBranchValue(std::string b_name,T& b_value){
   Branch<T>* branch = GetBranch<T>(b_name);
   if(branch == 0) return false;
   branch->SetValue(b_value);
   return true;
}

template <typename T>
inline T* Tree::GetBranchValue(std::string b_name){
   Branch<T>* branch = GetBranch<T>(b_name);
   if(branch == 0){
      return (T*)0;
   }
   
   return branch->GetValue();
}


template <typename T>
inline Branch<T>* Tree::GetBranch(std::string b_name) const {
   
   std::map<std::string,AbstractBranch*>::iterator itr,end;
   itr = m_map_branches->find(b_name);
   end = m_map_branches->end();
   if(itr == end){
      std::cerr << "[Tree::GetBranch] ERROR Branch, " << b_name << ", not found.\n";
      return (Branch<T>*)0;
   }
   
   Branch<T> *temp = static_cast<Branch<T>*>(itr->second);
   
   return temp;
}

template <typename T>
inline bool DataTypeOK(T& obj){
   
   if(!TypeTraits<T>::isPlainType && !TypeTraits<T>::isClass){
      std::cerr << "[Tree::DataTypeOK] ERROR, data type must be a plain data type (i.e. int,double,etc.) or class. No pointers.\n";
      return false;
   }
   
   
   
   
   
   return true;
}

template <typename T>
inline bool Tree::DeleteRootObject(std::string b_name){
   Branch<T>* branch = GetBranch<T>(b_name);
   if(branch == 0) return false;
   
   branch->DeleteObject();
   return true;
}

#endif
