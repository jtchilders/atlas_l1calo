
#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <map>
#include <vector>

#include "TApplication.h"
#include "TCanvas.h"
#include "TProfile.h"
#include "TH1I.h"
#include "TFile.h"
#include "TStyle.h"
#include "TList.h"
#include "TKey.h"
#include "TTree.h"
#include "TObjArray.h"

#include "commandLineParser.h"


typedef std::map<unsigned int,int> simpleMapType;
typedef std::map<unsigned int,int>::iterator Itr_simpMap;
typedef std::map<unsigned int,simpleMapType> complexMapType;
typedef std::map<unsigned int,simpleMapType>::iterator Itr_compMap;

unsigned int GetCoolId(const std::string histoName);

int main(int argc, char** argv){
   
   /// Parse command line
   //////////////////////////////////
   /////////////////////////////////////////////
   /////////////////////////////////////////////////
   CLParse cmdLineParser(argc,argv,"Take multiple root files filled with TProfiles from a group of PHOS4 runs taken together and merge into one file.");
   if(cmdLineParser.errorDuringSetup()){
      std::cerr << "ERROR: Failed to parse command line input.\n";
      return -1;
   }
   
   std::vector<std::string> inputFilenames = cmdLineParser.getFilenames();
   std::vector<unsigned int> inputRunNumbers = cmdLineParser.getRunNumbers();
   
   std::vector<unsigned int> inputTileDacValues = cmdLineParser.getTileDacValues();
   
   std::vector<unsigned int> inputLArgFcalDacValues = cmdLineParser.getLArgFcalDacValues();
   std::vector<unsigned int> inputLArgBarrelDacValues = cmdLineParser.getLArgBarrelDacValues();
   std::vector<unsigned int> inputLArgEmecDacValues = cmdLineParser.getLArgEmecDacValues();
   std::vector<unsigned int> inputLArgHecDacValues = cmdLineParser.getLArgHecDacValues();
   
   bool doTile=cmdLineParser.doTile();
   if(doTile) std::cout << "Doing Tile\n";
   bool doLArg=cmdLineParser.doLArg();
   if(doLArg) std::cout << "Doing LArg\n";
   ///////////////////////////////////////////
   //////////////////////////////////
   ////////////////////////////
   
   TApplication app("app",&argc,argv);
   
   /// Setup the gStyle environment
   #include "gStyleSetup.h"
   
   // Open each file as a root file
   // and get pointers to their tree
   std::vector<TFile*> inputFiles;
   std::vector<TTree*> inputTree;
   std::string inputTreeName = "phos4signals";
   for(unsigned int i=0;i<inputFilenames.size();i++){
      std::cout << "Opening file: " << inputFilenames[i] << std::endl;
      TFile* inputFile = new TFile(inputFilenames[i].c_str(),"READ");
      inputFiles.push_back(inputFile);
      
      inputFile->cd();
      inputTree.push_back((TTree*)gDirectory->Get(inputTreeName.c_str()));
   }
   
   // I want to enter all the entries in maps organized by Cool IDs
   // this will make things easier
   // This is a map that uses Cool ID as the key and then contains another
   // map which uses the tree number as a key and contains a corresponding 
   // tree entry number for the run/coolId combo.
   complexMapType masterMap;
   
   std::cerr << "Filling master map.\n";
   
   
   //input tree variables
   std::vector<unsigned int> inputCoolId;
   inputCoolId.resize(inputTree.size(),0);
   std::vector<bool> inputIsProcessed;
   inputIsProcessed.resize(inputTree.size(),0);
   std::vector<TProfile*> inputProcProf;
   inputProcProf.resize(inputTree.size(),0);
   std::vector<float> inputPeakValue;
   inputPeakValue.resize(inputTree.size(),0);
   std::vector<unsigned int> inputPeakBin;
   inputPeakBin.resize(inputTree.size(),0);
   std::vector<unsigned int> inputErrorBits;
   inputErrorBits.resize(inputTree.size(),0);
   
   // fill this map with the appropriate content
   // map[cooldId] -> tree entry number for that cool id
   for(unsigned int treeNum = 0;treeNum<inputTree.size();++treeNum){
      // assign branch addresses
      inputTree[treeNum]->SetBranchAddress("coolId",&inputCoolId[treeNum]);
      inputTree[treeNum]->SetBranchAddress("isProcessed",&inputIsProcessed[treeNum]);
      inputTree[treeNum]->SetBranchAddress("processedSignalProfile",&inputProcProf[treeNum]);
      inputTree[treeNum]->SetBranchAddress("procPeakValue",&inputPeakValue[treeNum]);
      inputTree[treeNum]->SetBranchAddress("procPeakBin",&inputPeakBin[treeNum]);
      inputTree[treeNum]->SetBranchAddress("procErrorBits",&inputErrorBits[treeNum]);
      
      // loop over the keys in this list
      for(unsigned int entry = 0;entry<inputTree[treeNum]->GetEntries();entry++){
         inputTree[treeNum]->GetEntry(entry);
         
         // add the pointer to the profile to the map
         masterMap[inputCoolId[treeNum]][treeNum] = entry;
         
      }
      
   }
   
   std::cerr << "Creating new output file.\n";
   
   // Setup output file
   
   std::string outputFilenameBase = "combinedPhos4Runs";
   std::string outputFilenamePostfix = "root";
   std::string outputFilename = outputFilenameBase + "." + outputFilenamePostfix;
   TFile* outputFile = new TFile(outputFilename.c_str(),"NEW");
   // this is just incase the filename already exists so then I want to create a new file
   // with a number at the end.
   unsigned int filenameCounter = 0;
   while(!outputFile->IsOpen()){
      delete outputFile; outputFile = 0;
      char temp[200];
      sprintf(temp,"%d",filenameCounter);
      outputFilename = outputFilenameBase + "-" + temp + "." + outputFilenamePostfix;
      outputFile = new TFile(outputFilename.c_str(),"NEW");
      filenameCounter++;
   }
   std::cout << "Writing to file: " << outputFilename << std::endl;
   
   std::cerr << "Creating output TTrees.\n";
   
   // create associated Trees for output
   TTree* outputTree = new TTree("tree","tree");
   // associated tree variables that will be filled into
   // each output tree
   unsigned int fillCoolId = 0;
   
   std::vector<bool>         fillIsProcessed;
   fillIsProcessed.resize(inputRunNumbers.size(),false);
   
   TObjArray                 fillProf(inputRunNumbers.size());
   
   std::vector<float>        fillPeakValue;
   fillPeakValue.resize(inputRunNumbers.size(),0);
   
   std::vector<unsigned int> fillPeakBin;
   fillPeakBin.resize(inputRunNumbers.size(),0);
   
   std::vector<unsigned int> fillErrorBits;
   fillErrorBits.resize(inputRunNumbers.size(),0);
   
   // set branch addresses for filling
   outputTree->Branch("isProcessed",&fillIsProcessed);
   outputTree->Branch("coolId",&fillCoolId,"coolId/i");
   outputTree->Branch("signalProfile",&fillProf);
   outputTree->Branch("peakValue",&fillPeakValue);
   outputTree->Branch("peakBin",&fillPeakBin);
   outputTree->Branch("errorBits",&fillErrorBits);
   
   std::cerr << "Looping over masterMap\n";
   
   // now that I have a usable list of all the tree entries
   // I can loop over them and add them to the output tree
   
   for(Itr_compMap topItr = masterMap.begin();topItr != masterMap.end();++topItr){
      
      // first zero the output Vectors
      fillIsProcessed.clear();
      fillIsProcessed.resize(inputRunNumbers.size(),false);
      fillProf.Clear();
      fillProf.Expand(inputRunNumbers.size());
      fillPeakValue.clear();
      fillPeakValue.resize(inputRunNumbers.size(),0);
      fillPeakBin.clear();
      fillPeakBin.resize(inputRunNumbers.size(),0);
      fillErrorBits.clear();
      fillErrorBits.resize(inputRunNumbers.size(),0);
      
      fillCoolId = topItr->first;
      
      // fill the vectors with their respective values
      for(Itr_simpMap itr = topItr->second.begin();itr != topItr->second.end();++itr){
         
         unsigned int treeEntry = itr->first;
         unsigned int entry = itr->second;
         inputTree[treeEntry]->GetEntry(entry);
         fillIsProcessed[treeEntry] = inputIsProcessed[treeEntry];
         fillPeakValue[treeEntry]   = inputPeakValue[treeEntry];
         fillPeakBin[treeEntry]     = inputPeakBin[treeEntry];
         fillErrorBits[treeEntry]   = inputErrorBits[treeEntry];
         
         
         fillProf.AddAt(inputProcProf[treeEntry],treeEntry);
         
         
      } // end for(itr)
      
      
      outputTree->Fill();
      outputTree->Write();
      
   } // end for(topItr)
   
   std::cerr << "Creatng RunInfo TTree.\n";
   
   std::string runInfoDirName = "runInfo";
   
   unsigned int runNumber;
   unsigned int tileDacValue;
   unsigned int largFcalDac;
   unsigned int largBarDac;
   unsigned int largEmecDac;
   unsigned int largHecDac;
   
   
   TTree* tempTree = new TTree(runInfoDirName.c_str(),"Run Information");
   
   tempTree->Branch("runNumber",   &runNumber,   "runNumber/i");
   tempTree->Branch("tileDacValue",&tileDacValue,"tileDacValue/i");
   tempTree->Branch("largFcalDac", &largFcalDac, "largFcalDac/i");
   tempTree->Branch("largBarDac",  &largBarDac,  "largBarDac/i");
   tempTree->Branch("largEmecDac", &largEmecDac, "largEmecDac/i");
   tempTree->Branch("largHecDac",  &largHecDac,  "largHecDac/i");
   
   for(unsigned int i=0;i<inputRunNumbers.size();++i){
      runNumber    = inputRunNumbers[i];
      
      if(doTile)
         tileDacValue = inputTileDacValues[i];
      else
         tileDacValue = 0;
      
      if(doLArg){
         largFcalDac  = inputLArgFcalDacValues[i];
         largBarDac   = inputLArgBarrelDacValues[i];
         largEmecDac  = inputLArgEmecDacValues[i];
         largHecDac   = inputLArgHecDacValues[i];
      }
      else{
         largFcalDac  = 0;
         largBarDac   = 0;
         largEmecDac  = 0;
         largHecDac   = 0;
      }
      
      std::cout << "       Run Number: " << runNumber << 
                      "\n        Tile DAC: " << tileDacValue << 
                      "\n        LArg Barrel DAC: " << largBarDac <<
                      "\n        LArg EMEC DAC: " << largEmecDac <<
                      "\n        LArg FCAL DAC: " << largFcalDac <<
                      "\n        LArg HEC DAC: " << largHecDac <<
                      "\n";
         
      
      tempTree->Fill();
      
   }
   
   std::cerr << "Writing TTrees to file.\n";
   
   tempTree->Write();
   delete tempTree;
   tempTree = 0;
   
   outputFile->cd();
   
   outputTree->Write();
   
   delete outputTree;
   outputTree = 0;
   
   
   std::cerr << "\nClosing file.\n";
   outputFile->Close();
   
   
   exit(0);
}

unsigned int GetCoolId(const std::string histoName){
   unsigned int coolIdLocation = histoName.find('_')+1;
   std::string strCoolId = histoName.substr(coolIdLocation,8);
   unsigned int coolID = 0;
   sscanf(strCoolId.c_str(),"%x",&coolID);
   
   return coolID;
} 

