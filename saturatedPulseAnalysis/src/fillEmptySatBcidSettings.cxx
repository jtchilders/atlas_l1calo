
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "tclap/CmdLine.h"

#include "SatBcidTree.h"
#include "SatBcidTreeFiller.h"

#include "TApplication.h"
#include "TStyle.h"
#include "TH1.h"

int main(int argc, char** argv){
   
   
   #include "gStyleSetup.h"
   
   TH1::AddDirectory(false);
   
   std::string inputFilename;
   try{
      // Define the command line object.
      TCLAP::CmdLine cmd("Fill SatBcidTree where values could not be determined", ' ', "0.1");
      
      TCLAP::ValueArg<std::string> inputFileList("f","file","ROOT file with SatBcidTree.",true,"","string");
      cmd.add(inputFileList);
      
      cmd.parse(argc,argv);
      
      inputFilename = inputFileList.getValue();
      
   } catch (TCLAP::ArgException &e)  // catch any exceptions
   { std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl; }
   
   
//    TApplication app("app",&argc,argv);
   
   /// Extract Tree from file
   SatBcidTree *tree = new SatBcidTree;
   tree->SetReadMode();
   tree->OpenFile(inputFilename);
   
   SatBcidTreeFiller *filler = new SatBcidTreeFiller(tree);
   filler->isLAr(true);
   filler->FillTree();
   
   return 0;
}


