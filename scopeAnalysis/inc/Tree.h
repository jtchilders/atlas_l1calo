
#include <TFile.h>
#include <TTree.h>
#include <TGraph.h>
#include <TProfile.h>

#include <iostream>


class Tree{
public:
   Tree(std::string name,std::string title,std::string filename);
   ~Tree(void);
   
   void SetGraph(TGraph* graph){m_graph = graph;};
   void SetProfile(TProfile* prof){m_profile = prof;};
   void SetMaxVoltage(float& voltage){m_maxVoltage = voltage;};
   
   void Clear(void);
   
   void Fill(TGraph* graph, TProfile* prof,float voltage);
   void Fill(void);
   
private:
   TTree *m_tree;
   TFile *m_file;
   
   TGraph     *m_graph;
   TProfile   *m_profile;
   float       m_maxVoltage;
   float       m_maxADC;
   float       m_maxEt;
   
};

