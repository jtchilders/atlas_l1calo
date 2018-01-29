////////////////////////////////////////////////////////////////
/// Tree Package: virtual base class for Branch               //
/// Developed by: Taylor Childers                             //
/// Feel free to email with questions                         //
////////////////////////////////////////////////////////////////
#ifndef ABSTRACTBRANCH_H
#define ABSTRACTBRANCH_H

#include <iostream>

#include "DataType.h"
#include "TBranch.h"
#include "TTree.h"

class AbstractBranch{
public:
   AbstractBranch(void){Clear();};
   virtual ~AbstractBranch(void){};
   
   std::string GetName(void) const {return m_name;};
   void SetName(std::string& name){m_name = name;};
   
   TBranch* GetBranch(void) const {return m_branch;};
   void SetBranch(TBranch* branch){m_branch = branch;};
   
   TTree* GetTree(void) const {return m_tree;};
   void SetTree(TTree* tree){ m_tree = tree;};
   
   void Clear(void){m_name.clear();m_branch=0;m_tree=0;};
   
   DataType GetDataType(void){return m_dataType;};
   void SetDataType(DataType& type){m_dataType = type;};
private:
   std::string m_name;
   TBranch *m_branch;
   TTree *m_tree;
   DataType m_dataType;
   
    virtual void DetermineDataType(void) = 0;
};



#endif

