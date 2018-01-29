////////////////////////////////////////////////////////////////
/// Tree Package: Holds branch value of a Tree                //
/// Developed by: Taylor Childers                             //
/// Feel free to email with questions                         //
////////////////////////////////////////////////////////////////
#ifndef BRANCH_H
#define BRANCH_H

#include <typeinfo>

#include "AbstractBranch.h"
#include "TypeTraits.h"

template <class T>
class Branch: public AbstractBranch{
public:
   Branch(void){Initialize();};
   ~Branch(void){};
   
   void CreateBranch(TTree* tree);
   void SetBranchAddress(TTree* tree);
   
   T* GetValue(void) const;
   void SetValue(T& value);
   
   void DeleteObject(void);
   
private:
   T m_data;
   T *m_class;
   
   void DetermineDataType(void);
   std::string GetNameWithDataType(const std::string& name) const;
   void Initialize(void);
};

// must determine data type for automated delete in deconstructor to work
template <class T>
inline void Branch<T>::DetermineDataType(void){
   
   DataType temp;
        if(typeid(UInt_t)      == typeid(T)) temp.dataType(DataType::UINT);
   else if(typeid(Int_t)       == typeid(T)) temp.dataType(DataType::INT);
   else if(typeid(Bool_t)      == typeid(T)) temp.dataType(DataType::BOOL);
   else if(typeid(Char_t)      == typeid(T)) temp.dataType(DataType::CHAR);
   else if(typeid(UChar_t)     == typeid(T)) temp.dataType(DataType::UCHAR);
   else if(typeid(UShort_t)    == typeid(T)) temp.dataType(DataType::USHORT);
   else if(typeid(Short_t)     == typeid(T)) temp.dataType(DataType::SHORT);
   else if(typeid(ULong_t)     == typeid(T)) temp.dataType(DataType::ULONG);
   else if(typeid(Long_t)      == typeid(T)) temp.dataType(DataType::LONG);
   else if(typeid(ULong64_t)   == typeid(T)) temp.dataType(DataType::ULONG64);
   else if(typeid(Long64_t)    == typeid(T)) temp.dataType(DataType::LONG64);
   else if(typeid(Float_t)     == typeid(T)) temp.dataType(DataType::FLOAT);
   else if(typeid(Float16_t)   == typeid(T)) temp.dataType(DataType::FLOAT16);
   else if(typeid(Double_t)    == typeid(T)) temp.dataType(DataType::DOUBLE);
   else if(typeid(Double32_t)  == typeid(T)) temp.dataType(DataType::DOUBLE32);
   else if(typeid(TH1C)        == typeid(T)) temp.dataType(DataType::RTH1C);
   else if(typeid(TH1S)        == typeid(T)) temp.dataType(DataType::RTH1S);
   else if(typeid(TH1I)        == typeid(T)) temp.dataType(DataType::RTH1I);
   else if(typeid(TH1F)        == typeid(T)) temp.dataType(DataType::RTH1F);
   else if(typeid(TH1D)        == typeid(T)) temp.dataType(DataType::RTH1D);
   else if(typeid(TH2C)        == typeid(T)) temp.dataType(DataType::RTH2C);
   else if(typeid(TH2S)        == typeid(T)) temp.dataType(DataType::RTH2S);
   else if(typeid(TH2I)        == typeid(T)) temp.dataType(DataType::RTH2I);
   else if(typeid(TH2F)        == typeid(T)) temp.dataType(DataType::RTH2F);
   else if(typeid(TH2D)        == typeid(T)) temp.dataType(DataType::RTH2D);
   else if(typeid(TProfile)    == typeid(T)) temp.dataType(DataType::RTPROFILE);
   else if(typeid(TProfile2D)  == typeid(T)) temp.dataType(DataType::RTPROFILE2D);
   else if(typeid(TF1)         == typeid(T)) temp.dataType(DataType::RTF1);
   // no dataType found
   else std::cerr << "[Branch::DetermineDataType] ERROR data type, " << typeid(T).name() << " not found, branch will not be initialized.\n";
   
   this->SetDataType(temp);
   
}

template <class T>
inline void Branch<T>::Initialize(void){
   if(!(TypeTraits<T>::isPlainType || TypeTraits<T>::isClass) ){
      std::cerr << "[Branch::Initialize] WARNING: Expecting plain data type or class, no pointers should be passed to template parameter.\n";
   }
   
   m_class = (T*)0;
   
   DetermineDataType();
}

template <class T>
inline T* Branch<T>::GetValue(void) const{
   if(TypeTraits<T>::isPlainType){
      return (T*)&m_data;
   }
   else if(TypeTraits<T>::isClass){
      return m_class;
   }
   else{
      std::cout << "[Branch::GetValue] WARNING: TypeTraits not determined.\n";
   }
   
   return (T*)0;
}

template <class T>
inline void Branch<T>::SetValue(T& value){
   if(TypeTraits<T>::isPlainType){
      m_data = value;
   }
   else if(TypeTraits<T>::isClass){
      m_class = &value;
   }
   else{
      std::cout << "[Branch::SetValue] WARNING: No value set.\n";
   }
}

template <class T>
inline void Branch<T>::CreateBranch(TTree* tree){
   this->SetTree(tree);
   TBranch *temp = 0;
   
   if(TypeTraits<T>::isPlainType){
      temp = tree->Branch(this->GetName().c_str(),&m_data,GetNameWithDataType(this->GetName()).c_str());
   }
   else if(TypeTraits<T>::isClass){
      temp = tree->Branch(this->GetName().c_str(),&m_class);
   }
   
   else{
      std::cout << "[Branch::CreateBranch] WARNING: No branch created.\n";
   }
   this->SetBranch(temp);
}

template <class T>
inline void Branch<T>::SetBranchAddress(TTree* tree){
   this->SetTree(tree);
   if(TypeTraits<T>::isPlainType)
      tree->SetBranchAddress(this->GetName().c_str(),&m_data);
   else if(TypeTraits<T>::isClass)
      tree->SetBranchAddress(this->GetName().c_str(),&m_class);
   else
      std::cout << "[Branch::SetBranchAddress] WARNING: No branch addressed.\n";
}

template <class T>
inline std::string Branch<T>::GetNameWithDataType(const std::string& name) const{
   
   if(!TypeTraits<T>::isPlainType){
      std::cerr << "[Branch::GetNameWithDataType] ERROR Invalid data type for this branch.\n";
      return name;
   }
   
   std::string temp = name;
        if(typeid(ULong64_t)   == typeid(T)) temp += "/l";
   else if(typeid(Long64_t)    == typeid(T)) temp += "/L";
   else if(typeid(ULong_t)     == typeid(T)) temp += "/i";
   else if(typeid(Long_t)      == typeid(T)) temp += "/I";
   else if(typeid(UInt_t)      == typeid(T)) temp += "/i";
   else if(typeid(Int_t)       == typeid(T)) temp += "/I";
   else if(typeid(UShort_t)    == typeid(T)) temp += "/s";
   else if(typeid(Short_t)     == typeid(T)) temp += "/S";
   else if(typeid(UChar_t)     == typeid(T)) temp += "/b";
   else if(typeid(Char_t)      == typeid(T)) temp += "/B";
   else if(typeid(Double_t)    == typeid(T)) temp += "/D";
   else if(typeid(Double32_t)  == typeid(T)) temp += "/D";
   else if(typeid(Float_t)     == typeid(T)) temp += "/F";
   else if(typeid(Float16_t)   == typeid(T)) temp += "/F";
   else if(typeid(Bool_t)      == typeid(T)) temp += "/O";
   
   return temp;
}

template <class T>
inline void Branch<T>::DeleteObject(void){
   if(!TypeTraits<T>::isClass){
      std::cerr << "[Branch::DeleteObject] Object is not class and will not be deleted. Only ROOT classes need to be deleted. Should be called at the end of a fill to free up memory.\n";
      return;
   }
   else{
      delete m_class;
      m_class = (T*)0;
   }
}

#endif 
