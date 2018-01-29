
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "tclap/CmdLine.h"

#include "ShapeMakerTree.h"
//#include "AnalyzeSaturatedBcid.h"

#include "SignalShapeCollection.h"

#include "TApplication.h"
#include "TStyle.h"
#include "TH1.h"
#include "TROOT.h"

int main(int argc, char** argv){
   
   
   #include "gStyleSetup.h"
   
   std::string inputFilename;
   try{
      // Define the command line object.
      TCLAP::CmdLine cmd("Analyze multiple unsaturated and saturated PHOS4 scans in order to predict the appropriate SatHigh/SatLow/SatLevel register values for each channel", ' ', "0.1");
      
      TCLAP::ValueArg<std::string> inputFileList("f","file","Text file with input root file on separate lines, each followed by the DAC values for that run separated by tabs.",true,"","string");
      cmd.add(inputFileList);
      
      cmd.parse(argc,argv);
      
      inputFilename = inputFileList.getValue();
      
   } catch (TCLAP::ArgException &e)  // catch any exceptions
   { std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl; }
   
   
   /// Extract data from file list
   /// file should contain on each row:
   /// </path/filename.root> <tab> <run number> <tab> <DAC value> <tab> <DAC value> , etc.
   ///
   std::vector<ShapeMakerTree*> trees;
   
   std::ifstream fin(inputFilename.c_str());
   if(!fin){
      std::cerr << "ERROR Opening file: " << inputFilename << std::endl;
      return 0;
   }
   
   bool tileRun=false;
   bool largRun=false;
   // extract TTrees from files
   while(!fin.eof()){
      
      char buffer[500];
      
      fin.getline(buffer,500);
      
      std::stringstream sline(buffer);
      
      std::string filename;
      unsigned int runNumber = 0;
      unsigned int dacValueBarrel = 0;
      unsigned int dacValueEMEC = 0;
      unsigned int dacValueFCAL = 0;
      unsigned int dacValueHEC = 0;
      
      sline >> filename >> runNumber >> dacValueBarrel >> dacValueEMEC >> dacValueFCAL >> dacValueHEC;
      
//       std::cout << filename << "\t" << runNumber << "\t" << dacValueBarrel << "\t" << dacValueEMEC << "\t" << dacValueFCAL << "\t" << dacValueHEC << std::endl;
      
      // check for empty line
      if(filename.empty() && runNumber == 0 
         && dacValueBarrel == 0 && dacValueEMEC == 0
         && dacValueFCAL == 0 && dacValueHEC == 0)
         continue;
      // otherwise make sure filename is specified
      else if(filename.empty()){
         std::cerr << "ERROR no filename specified.\n";
         return 0;
      }
      // make sure run number is specified
      else if(runNumber == 0){
         std::cerr << "ERROR no run number specified.\n";
         return 0;
      }
      // make sure at least the barrel DAC value is specified.
      else if(dacValueBarrel == 0){
         std::cerr << "ERROR no dac value specified.\n";
         return 0;
      }
      
      ShapeMakerTree* tree = new ShapeMakerTree(filename);
      tree->SetRunNumber(runNumber);
      
      // set dac values and determine if this is a tile or LArg run.
      if(dacValueEMEC == 0 && dacValueFCAL == 0 && dacValueHEC == 0){
         std::cerr << "INFO assuming Tile Run since only one dac value given for each run.\n";
         tree->SetDacBarrel(dacValueBarrel);
         
         tree->SetTileRun(true);
         tileRun = true;
      }
      else{
         std::cerr << "INFO assuming LArg Run since more than one dac value given:\n";
         std::cerr << "INFO DAC for BARREL: " << dacValueBarrel << " EMEC: " << dacValueEMEC << " FCAL: " << dacValueFCAL << " HEC: " << dacValueHEC << std::endl;
         tree->SetDacBarrel(dacValueBarrel);
         tree->SetDacEmec(dacValueEMEC);
         tree->SetDacFcal(dacValueFCAL);
         tree->SetDacHec(dacValueHEC);
         
         tree->SetLArRun(true);
         largRun = true;
      }
      
      trees.push_back(tree);
      
   }
   
   TDirectory::AddDirectory(false);
   TProfile::AddDirectory(false);
   TH1::AddDirectory(false);
   
//    TApplication app("app",&argc,argv);
   //gROOT->SetBatch(kTRUE);
   
   //AnalyzeSaturatedBcid* satBcid = new AnalyzeSaturatedBcid(&trees);
   
   //satBcid->PopulateGraphs();
   
   SignalShapeCollection::RUN_TYPE runType;
   if(tileRun && largRun){
      std::cerr << " main: ERROR, both tile and larg runs detected. Only one run type allowed.\n";
      return 0;
   }
   else if(tileRun && !largRun){
      runType = SignalShapeCollection::TILE_RUN;
   }
   else if(!tileRun && largRun){
      runType = SignalShapeCollection::LAR_RUN;
   }
   
   SignalShapeCollection coll(&trees,runType);
   
   
   
   return 0;
}


