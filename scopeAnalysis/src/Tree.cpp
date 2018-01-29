#include <Tree.h>

Tree::Tree(std::string name,std::string title,std::string filename){
   
   Clear();
   
   m_file = new TFile(filename.c_str(),"RECREATE");
   
   m_tree = new TTree(name.c_str(),title.c_str());
   
   m_tree->Branch("graph",&m_graph);
   m_tree->Branch("profile",&m_profile);
   m_tree->Branch("maxVoltage",&m_maxVoltage);
   m_tree->Branch("maxADC",&m_maxADC);
   m_tree->Branch("maxEt",&m_maxEt);
   
   
}

Tree::~Tree(void){
   
   m_tree->Write();
   m_file->Close();
   
   //delete m_tree;
   //m_tree = 0;
   
   delete m_file;
   m_file = 0;
   
   Clear();
   
}

void Tree::Clear(void){
   m_graph      = 0;
   m_profile    = 0;
   m_maxVoltage = 0.;
   m_maxADC     = 0.;
   m_maxEt      = 0.;
   
}

void Tree::Fill(TGraph* graph, TProfile* prof,float voltage){
   
   Clear();
   
   m_graph = graph;
   m_profile = prof;
   m_maxVoltage = voltage;
   m_maxADC = voltage/0.0025;
   m_maxEt  = voltage*100;
   
   Fill();
}

void Tree::Fill(void){
   m_tree->Fill();
}
