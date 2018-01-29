#include <ScopeFile.h>
#include <FileList.h>
#include <Tree.h>

#include <TApplication.h>
#include <TGraph.h>
#include <TCanvas.h>
#include <TFile.h>

#include <iostream>


int main(int argc, char** argv){
   
   if(argc < 3){
      std::cout << "usage: <txt list of input files> <outputFilename>\n";
      std::cout << "   txt list = a text file with the full path to each\n";
      std::cout << "              scope file, one per line.\n";
      std::cout << "   outputFilename = name of root file\n";
      return 0;
   }
   
   
   FileList fileList(argv[1]);
   
   std::string filename = argv[2];
   
   Tree tree("scopeTraceTree","scopeTraceTree",filename);
   
   std::cout << "number of scope traces: " << fileList.size() << std::endl;
   
   for(unsigned int i=0;i<fileList.size();++i){
      std::cout << "scope trace number: " << i << std::endl;
      
      ScopeFile *trace = new ScopeFile(fileList[i],fileList[i],fileList[i]);
      
      tree.Fill(trace->getGraph(),trace->getProfile(),trace->getMaxVoltageInMilliVolts()/1000.);
      
      delete trace;
      trace = 0;
      
   }
   
   
   
   return 0;
   
   
}
