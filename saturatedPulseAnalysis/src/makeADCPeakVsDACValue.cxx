
#include <iostream>
#include <string>
#include <sstream>
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
#include "TGaxis.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TH2D.h"
#include "TTree.h"

#include "commandLineParser.h"

#include "L1CaloChannelMap.h"
#include "PixelMap.h"

#include "ChannelRunCollection.h"

// this struct will hold the run info ttree values
typedef struct RunInfoContainerStruct{
   std::vector<unsigned int> tRunNumber; // holds the run number
   std::vector<unsigned int> tTileDac; // tile dac value
   std::vector<unsigned int> tLArgEmecDac; // larg dac value in EMEC
   std::vector<unsigned int> tLArgHecDac; // larg dac value in HEC
   std::vector<unsigned int> tLArgBarrelDac; // larg dac value in Barrel
   std::vector<unsigned int> tLArgFcalDac; // larg dac value in FCAL
   
}runInfoObj;

int main(int argc, char** argv){
   
   /// Parse command line
   //////////////////////////////////
   /////////////////////////////////////////////
   /////////////////////////////////////////////////
   CLParse cmdLineParser(argc,argv,"Take multiple merged ROOT files output from _combindRunFiles_ program and perform analysis on all pulse shapes. Ouput are plots of ADC vs DAC and Peak ADC vs ADC in sat-1 bin.");
   if(cmdLineParser.errorDuringSetup()){
      std::cerr << "ERROR: Failed to parse command line input.\n";
      return -1;
   }
   
   std::vector<std::string> inputFilenames = cmdLineParser.getFilenames();
   
   bool doTile=cmdLineParser.doTile();
   if(doTile) std::cout << "Doing Tile\n";
   bool doLArg=cmdLineParser.doLArg();
   if(doLArg) std::cout << "Doing LArg\n";
   ///////////////////////////////////////////
   //////////////////////////////////
   ////////////////////////////
   
   /// Setup the gStyle environment
   #include "gStyleSetup.h"
   
   gStyle->SetOptStat(0);
   gDirectory->AddDirectory(false);
   TH1::AddDirectory(false);
   
   // Need channel map for Detector Regions.
   L1CaloChannelMap* l1map = new L1CaloChannelMap;
   l1map->SetCpmEnable(false);
   l1map->SetJemEnable(false);
   
   // RunInfo TTree name
   std::string runInfoTreeName    = "runInfo";
   // TTree branch names
   std::string bRunNumberName     = "runNumber";
   std::string bTileDacName       = "tileDacValue";
   std::string bLArgFcalDacName   = "largFcalDac";
   std::string bLArgBarrelDacName = "largBarDac";
   std::string bLArgEmecDacName   = "largEmecDac";
   std::string bLArgHecDacName    = "largHecDac";
   
   // data tree
   std::string dataTreeName       = "tree";
   
   // other branch names
   std::string bCoolIdName        = "coolId";
   std::string bIsProcessedName   = "isProcessed";
   std::string bSignalProfileName = "signalProfile";
   std::string bPeakValueName     = "peakValue";
   std::string bPeakBinName       = "peakBin";
   std::string bErrorBitsName     = "errorBits";
   
   // These are used for determining if a pulse is saturated
   // because these have had their Pedestal corrected to 0.
   const float saturatedMin = 980.0;
   const float saturatedMax = 1000.0;
   
   
   
   // setup output file name
   std::cerr << "Opening output file.\n";
   
   std::string outputFilenameBase = "dacVsAdcPeak";
   std::string outputFilename = outputFilenameBase + ".root";
   
   TFile* outputFile = new TFile(outputFilename.c_str(),"NEW");
   unsigned int outputFileCounter = 0;
   while(!outputFile->IsOpen()){
      
      // delete file I just created
      delete outputFile;
      outputFile = 0;
      
      char fileNumber[20];
      sprintf(fileNumber,"%02d",outputFileCounter++);
      outputFilename = outputFilenameBase + "-" + fileNumber + ".root";
      outputFile = new TFile(outputFilename.c_str(),"NEW");
   }
   std::cerr << "output file name: " << outputFilename << std::endl;
   
   // create directory structure in output file
   std::string combinedCanvasDirName = "combinedCanvas";
   outputFile->mkdir(combinedCanvasDirName.c_str());
   std::string dacVsAdcPeakDirName = "dacVsAdcPeak";
   outputFile->mkdir(dacVsAdcPeakDirName.c_str());
   std::string fitFunctionDirName = "fitFunction";
   outputFile->mkdir(fitFunctionDirName.c_str());
   std::string adcPeakVsAdcSlice1DirName = "adcPeakVsAdcSlice1";
   outputFile->mkdir(adcPeakVsAdcSlice1DirName.c_str());
   std::string adcPeakVsAdcSlice2DirName = "adcPeakVsAdcSlice2";
   outputFile->mkdir(adcPeakVsAdcSlice2DirName.c_str());
   std::string summaryPlotDirName = "summaryPlots";
   outputFile->mkdir(summaryPlotDirName.c_str());
   outputFile->cd(summaryPlotDirName.c_str());
   std::string etaDependentAdcPeakVsSlice = "etaDependentAdcPeakVsSlice";
   gDirectory->mkdir(etaDependentAdcPeakVsSlice.c_str());
   outputFile->cd();
   
   outputFile->Close();
   delete outputFile;
   outputFile = 0;
  
   
   std::cerr << "Opening Input Files for first loop...\n";
   
   // used to calculate the mean peakBin
   std::map<unsigned int,unsigned int> sumPeakBin,sum2PeakBin,nPeakBin;
   
   // Open each file as a root file and extract the Run Info TTree
   // this provides information about what runs are contained in the file
   // Then fill the data from each data tree into the chanDataMap
   for(unsigned int fileNum=0;fileNum<inputFilenames.size();++fileNum){
      
      std::cout << "..." << inputFilenames[fileNum] << ".\n";
      
      TFile* inputFile = new TFile(inputFilenames[fileNum].c_str(),"READ");
      if(!inputFile->IsOpen()){
         std::cout << "Failed to open input file: " << inputFilenames[fileNum] << std::endl;
      }
      
      runInfoObj* tempRunInfo = new runInfoObj;
      
      std::cout << "   Extracting run information.\n";
      
      TTree* runInfoTree = (TTree*)inputFile->Get(runInfoTreeName.c_str());
      if(runInfoTree == 0){
         std::cerr << "    Error getting tree from file. No tree found with name: " << runInfoTreeName << std::endl;
         return -1;
      }
      
      unsigned int tempRunNumber   = 0;
      unsigned int tempTileDac     = 0;
      unsigned int tempLArgEmecDac = 0;
      unsigned int tempLArgFcalDac = 0;
      unsigned int tempLArgBarDac  = 0;
      unsigned int tempLArgHecDac  = 0;
      
      runInfoTree->SetBranchAddress(bRunNumberName.c_str(),&tempRunNumber);
      runInfoTree->SetBranchAddress(bTileDacName.c_str(),&tempTileDac);
      runInfoTree->SetBranchAddress(bLArgEmecDacName.c_str(),&tempLArgEmecDac);
      runInfoTree->SetBranchAddress(bLArgFcalDacName.c_str(),&tempLArgFcalDac);
      runInfoTree->SetBranchAddress(bLArgBarrelDacName.c_str(),&tempLArgBarDac);
      runInfoTree->SetBranchAddress(bLArgHecDacName.c_str(),&tempLArgHecDac);
      
      for(unsigned int treeEntry=0;treeEntry < runInfoTree->GetEntries();++treeEntry){
         runInfoTree->GetEntry(treeEntry);
         
         std::cout << "       Run Number: " << tempRunNumber << 
                      "\n        Tile DAC: " << tempTileDac << 
                      "\n        LArg Barrel DAC: " << tempLArgBarDac <<
                      "\n        LArg EMEC DAC: " << tempLArgEmecDac <<
                      "\n        LArg FCAL DAC: " << tempLArgFcalDac <<
                      "\n        LArg HEC DAC: " << tempLArgHecDac <<
                      "\n";
         
         tempRunInfo->tRunNumber.push_back(tempRunNumber);
         tempRunInfo->tTileDac.push_back(tempTileDac);
         tempRunInfo->tLArgEmecDac.push_back(tempLArgEmecDac);
         tempRunInfo->tLArgFcalDac.push_back(tempLArgFcalDac);
         tempRunInfo->tLArgBarrelDac.push_back(tempLArgBarDac);
         tempRunInfo->tLArgHecDac.push_back(tempLArgHecDac);
         
         
      } // end for(treeEntry)
      
      // now I loop over the data tree to get the map of cool ids to tree entry number
      
      std::cout << "   Filling dacVsAdc and combinedCanvases.\n";
      
      TTree* dataTree = (TTree*)inputFile->Get(dataTreeName.c_str());
      
      unsigned int tempCoolId                  = 0;
      std::vector<bool>* tempIsProcessed       = 0;
      TObjArray* tempSignalProfile             = 0;
      std::vector<float>* tempPeakValue        = 0;
      std::vector<unsigned int>* tempPeakBin   = 0;
      std::vector<unsigned int>* tempErrorBits = 0;
      
      dataTree->SetBranchAddress(bCoolIdName.c_str(),&tempCoolId);
//       dataTree->SetBranchAddress(bIsProcessedName.c_str(),&tempIsProcessed);
      dataTree->SetBranchAddress(bSignalProfileName.c_str(),&tempSignalProfile);
      dataTree->SetBranchAddress(bPeakValueName.c_str(),&tempPeakValue);
      dataTree->SetBranchAddress(bPeakBinName.c_str(),&tempPeakBin);
//       dataTree->SetBranchAddress(bErrorBitsName.c_str(),&tempErrorBits);
      
      unsigned int lastStartEntryA=0,lastStartEntryB=0;
      for(unsigned int treeEntry=0;treeEntry<dataTree->GetEntries();++treeEntry){
         
         dataTree->GetEntry(treeEntry);
         
         std::cout << "CoolId: 0x" << std::hex << tempCoolId << std::dec << "\n";
         
         // get an iterator to the sums for the calculation of the mean peak bin
         std::map<unsigned int,unsigned int>::iterator itrSum,itrSum2,itrN;
         itrSum = sumPeakBin.find(tempCoolId);
         itrSum2 = sum2PeakBin.find(tempCoolId);
         itrN = nPeakBin.find(tempCoolId);
         if(itrSum == sumPeakBin.end()){
            sumPeakBin[tempCoolId] = 0;
            sum2PeakBin[tempCoolId] = 0;
            nPeakBin[tempCoolId] = 0;
            itrSum = sumPeakBin.find(tempCoolId);
            itrSum2 = sum2PeakBin.find(tempCoolId);
            itrN = nPeakBin.find(tempCoolId);
         }
         
         
         
         // open output file for read/write
         if(outputFile == 0){
            outputFile = new TFile(outputFilename.c_str(),"UPDATE");
            if(!outputFile->IsOpen()){
               std::cerr << "ERROR: Failed to re-open " << outputFilename << std::endl;
               continue;
            }
         }
         
         // fill the detector region for this channel
         l1map->SetPpmChannelID(tempCoolId);
         const enum  CaloDivisionEnum region = l1map->GetDetectorRegion();
         
         // load combined canvas for this cool id
         outputFile->cd(combinedCanvasDirName.c_str());
         
         TList* listOfKeysA = gDirectory->GetListOfKeys();
         TCanvas* combinedCanvas = 0;
         // After the first loop the canvases will already exist
         if(fileNum > 0){
            for(unsigned int listEntry=lastStartEntryA;listEntry<listOfKeysA->GetEntries();++listEntry){
               TKey* key = (TKey*)listOfKeysA->At(listEntry);
               
               std::string name = key->GetName();
               
               
               unsigned int position = name.find('_') + 1;
               std::string strCoolId = "0x";
               strCoolId += name.substr(position,8);
               std::stringstream ssCoolId;
               ssCoolId << strCoolId;
               unsigned int keyCoolId = 0;
               ssCoolId >> std::hex >> keyCoolId;
               
               if(keyCoolId == tempCoolId){
                  combinedCanvas = (TCanvas*)key->ReadObj();
                  lastStartEntryA = listEntry;
                  break;
               }
               
            }
         }
         
         if(combinedCanvas == 0){
            char canvasName[200],canvasTitle[200];
            sprintf(canvasName,"combinedCanvas_%08x",tempCoolId);
            sprintf(canvasTitle,"Combined Pulse Shapes for 0x%08x",tempCoolId);
            combinedCanvas = new TCanvas(canvasName,canvasTitle,0,0,1000,800);
         }
         unsigned int colorCount = combinedCanvas->GetListOfPrimitives()->GetEntries() + 1;
         if(colorCount >= 10) colorCount += 10;
         
         // load dac vs adc plot from output file
         outputFile->cd(dacVsAdcPeakDirName.c_str());
         TList* listOfKeysB = gDirectory->GetListOfKeys();
         TGraph* dacVsAdc = 0;
         if(fileNum > 0){
            for(unsigned int listEntry=lastStartEntryB;listEntry<listOfKeysB->GetEntries();++listEntry){
               TKey* key = (TKey*)listOfKeysB->At(listEntry);
               
               std::string name = key->GetName();
               
               unsigned int position = name.find('_') + 1;
               std::string strCoolId = "0x";
               strCoolId += name.substr(position,8);
               std::stringstream ssCoolId;
               ssCoolId << strCoolId;
               unsigned int keyCoolId = 0;
               ssCoolId >> std::hex >> keyCoolId;
               
               if(keyCoolId == tempCoolId){
                  dacVsAdc = (TGraph*)key->ReadObj();
                  lastStartEntryB = listEntry;
                  break;
               }
               
            } // end for(listEntries)
         } // end if(fileNum)
         
         if(dacVsAdc == 0){
            char graphName[200],graphTitle[200];
            sprintf(graphName,"dacVsAdc_%08x",tempCoolId);
            sprintf(graphTitle,"Calo DAC vs L1Calo ADC Peak Value for 0x%08x;Calo DAC;L1Calo ADC Value",tempCoolId);
            dacVsAdc = new TGraph();
            dacVsAdc->SetName(graphName);
            dacVsAdc->SetTitle(graphTitle);
         }
         
         // loop over the vectors,
         // each entry is for a different run
         for(unsigned int i=0;i<tempSignalProfile->GetEntries();++i){
            
            // collection sums in order to calculate the mean peak bin
            // which is used in the next second loop
            if(tempPeakValue->at(i) < saturatedMin){
               itrSum->second += tempPeakBin->at(i);
               itrSum2->second += tempPeakBin->at(i)*tempPeakBin->at(i);
               itrN->second++;
            }
            
            TProfile* prof = (TProfile*)tempSignalProfile->At(i);
            
            std::string drawOpts = "same";
            if(i==0 && fileNum == 0)
               drawOpts = "";
            
            combinedCanvas->cd();
            
            prof->SetMarkerStyle(7);
            prof->SetMarkerColor(colorCount++);
            if(colorCount == 10) colorCount += 10;
            prof->SetMaximum(1030);
            prof->Draw(drawOpts.c_str());
            
            // extract the appropriate DAC value for this channel
            unsigned int caloDAC = 0;
            if(region == LArFCAL1C || region == LArFCAL1A || region == LArFCAL23C || region == LArFCAL23A){
               caloDAC = tempRunInfo->tLArgFcalDac[i];
            }
            else if(region == LArEMECC || region == LArEMECA){
               caloDAC = tempRunInfo->tLArgEmecDac[i];
            }
            else if(region == LArEMBC || region == LArEMBA){
               caloDAC = tempRunInfo->tLArgBarrelDac[i];
            }
            else if(region == LArHECC || region == LArHECA){
               caloDAC = tempRunInfo->tLArgHecDac[i];
            }
            else if(region == LArOverlapC || region == LArOverlapA){
               caloDAC = 0;
            }
            else if(region == TileLBC || region == TileLBA || region == TileEBC || region == TileEBA){
               caloDAC = tempRunInfo->tTileDac[i];
            }
            else{
               caloDAC = 0;
            }
            
            // fill dacVsAdc graph with DAC value and true ADC value
            unsigned int pointNumber = dacVsAdc->GetN();
            dacVsAdc->SetPoint(pointNumber,(double)caloDAC,tempPeakValue->at(i));
            
         } // end for(vectors)
         
         // Write combined canvases to file
         outputFile->cd(combinedCanvasDirName.c_str());
         combinedCanvas->Write(combinedCanvas->GetName(),TObject::kOverwrite);
         
         delete combinedCanvas;
         combinedCanvas = 0;
         
         // write dac Vs adc graph to file
         outputFile->cd(dacVsAdcPeakDirName.c_str());
         dacVsAdc->Write(dacVsAdc->GetName(),TObject::kOverwrite);
         
         delete dacVsAdc;
         dacVsAdc = 0;
         
         // close the output file
         if(outputFile != 0){
            outputFile->Close();
            delete outputFile;
            outputFile = 0;
         }
         
         tempSignalProfile->Delete();
         tempSignalProfile = 0;
         delete tempPeakBin;
         tempPeakBin = 0;
         delete tempPeakValue;
         tempPeakValue = 0;
      } // end for(dataTree)
      
      delete tempRunInfo;
      tempRunInfo = 0;
      
      inputFile->Close();
      delete inputFile;
      inputFile = 0;
      
   } // end for(fileNum)
   
   // calculate mean Peak bin location for following loop
   std::map<unsigned int,float> meanPeakBin,sigmaPeakBin;
   std::map<unsigned int,unsigned int>::iterator itrSum = sumPeakBin.begin();
   std::map<unsigned int,unsigned int>::iterator itrSum2 = sum2PeakBin.begin();
   std::map<unsigned int,unsigned int>::iterator itrN = nPeakBin.begin();
   for(;itrSum != sumPeakBin.end();++itrSum,++itrSum2,++itrN){
      meanPeakBin[itrSum->first] = itrN->second == 0 ? 0 : (float)itrSum->second/(float)itrN->second;
      sigmaPeakBin[itrSum->first] = itrN->second == 0 ? 0 : sqrt( (1.0/(float)itrN->second)*itrSum2->second - meanPeakBin[itrSum->first]*meanPeakBin[itrSum->first]);
      
   }
   
   // I must run over the files again to produce the 
   // ADC effective peak vs the Slice -1/-2
   // and do the linear fits
   std::cout << "Second Loop...\n";
   
   // some summary plots for the adcPeakVsSlice1/2 graphs
   std::vector<TGraph*> adcPeakVsSlice1ByPartition,adcPeakVsSlice2ByPartition;
   for(unsigned int partition=0;partition<Invalid;++partition){
      
      std::string partitionName;
      switch(partition){
      case LArFCAL1C:
         partitionName = "LArFCAL1C";
         break;
      case LArEMECC:
         partitionName = "LArEMECC";
         break;
      case LArOverlapC:
         partitionName = "LArOverlapC";
         break;
      case LArEMBC:
         partitionName = "LArEMBC";
         break;
      case LArEMBA:
         partitionName = "LArEMBA";
         break;
      case LArOverlapA:
         partitionName = "LArOverlapA";
         break;
      case LArEMECA:
         partitionName = "LArEMECA";
         break;
      case LArFCAL1A:
         partitionName = "LArFCAL1A";
         break;
      case LArFCAL23C:
         partitionName = "LArFCAL23C";
         break;
      case LArHECC:
         partitionName = "LArHECC";
         break;
      case TileEBC:
         partitionName = "TileEBC";
         break;
      case TileLBC:
         partitionName = "TileLBC";
         break;
      case TileLBA:
         partitionName = "TileLBA";
         break;
      case TileEBA:
         partitionName = "TileEBA";
         break;
      case LArHECA:
         partitionName = "LArHECA";
         break;
      case LArFCAL23A:
         partitionName = "LArFCAL23A";
         break;
      case Invalid:
         partitionName = "Invalid";
         break;
      default:
         partitionName = "Invalid";
         break;
      }
      
      std::string graphName = "adcPeakVsSlice1_" + partitionName;
      std::string graphTitle = "ADC Effective Peak Vs. 1st Slice prior to saturation for: " + partitionName;
      graphTitle += ";ADC Effective Peak;Slice saturation -1";
      
      TGraph* graph1 = new TGraph;
      graph1->SetName(graphName.c_str());
      graph1->SetTitle(graphTitle.c_str());
      adcPeakVsSlice1ByPartition.push_back(graph1);
      
      graphName = "adcPeakVsSlice2_" + partitionName;
      graphTitle = "ADC Effective Peak Vs. 2nd Slice prior to saturation for: " + partitionName;
      graphTitle += ";ADC Effective Peak;Slice saturation -2";
      TGraph* graph2 = new TGraph;
      graph2->SetName(graphName.c_str());
      graph2->SetTitle(graphTitle.c_str());
      adcPeakVsSlice2ByPartition.push_back(graph2);
      
   }
   
   // Also want graphs by eta slice
   std::map<unsigned int,TGraph*> emAdcPeakVsSlice1ByEtaSlice,hadAdcPeakVsSlice1ByEtaSlice;
   std::map<unsigned int,TGraph*> emAdcPeakVsSlice2ByEtaSlice,hadAdcPeakVsSlice2ByEtaSlice;
   
   
   // want to see which channels aren't saturating
   PixelMap<float>* pmHadSaturation = new PixelMap<float>(TrigTower);
   PixelMap<float>* pmEmSaturation = new PixelMap<float>(TrigTower);
   
   // Open each file as a root file and extract the Run Info TTree
   // this provides information about what runs are contained in the file
   // Then fill the data from each data tree into the chanDataMap
   for(unsigned int fileNum=0;fileNum<inputFilenames.size();++fileNum){
      
      std::cout << "..." << inputFilenames[fileNum] << ".\n";
      
      TFile* inputFile = new TFile(inputFilenames[fileNum].c_str(),"READ");
      if(!inputFile->IsOpen()){
         std::cout << "Failed to open input file: " << inputFilenames[fileNum] << std::endl;
      }
      
      runInfoObj* tempRunInfo = new runInfoObj;
      
      std::cout << "   Extracting run information.\n";
      
      TTree* runInfoTree = (TTree*)inputFile->Get(runInfoTreeName.c_str());
      if(runInfoTree == 0){
         std::cerr << "    Error getting tree from file. No tree found with name: " << runInfoTreeName << std::endl;
         return -1;
      }
      
      unsigned int tempRunNumber   = 0;
      unsigned int tempTileDac     = 0;
      unsigned int tempLArgEmecDac = 0;
      unsigned int tempLArgFcalDac = 0;
      unsigned int tempLArgBarDac  = 0;
      unsigned int tempLArgHecDac  = 0;
      
      runInfoTree->SetBranchAddress(bRunNumberName.c_str(),&tempRunNumber);
      runInfoTree->SetBranchAddress(bTileDacName.c_str(),&tempTileDac);
      runInfoTree->SetBranchAddress(bLArgEmecDacName.c_str(),&tempLArgEmecDac);
      runInfoTree->SetBranchAddress(bLArgFcalDacName.c_str(),&tempLArgFcalDac);
      runInfoTree->SetBranchAddress(bLArgBarrelDacName.c_str(),&tempLArgBarDac);
      runInfoTree->SetBranchAddress(bLArgHecDacName.c_str(),&tempLArgHecDac);
      
      for(unsigned int treeEntry=0;treeEntry < runInfoTree->GetEntries();++treeEntry){
         runInfoTree->GetEntry(treeEntry);
         
         std::cout << "       Run Number: " << tempRunNumber << 
                      "\n        Tile DAC: " << tempTileDac << 
                      "\n        LArg Barrel DAC: " << tempLArgBarDac <<
                      "\n        LArg EMEC DAC: " << tempLArgEmecDac <<
                      "\n        LArg FCAL DAC: " << tempLArgFcalDac <<
                      "\n        LArg HEC DAC: " << tempLArgHecDac <<
                      "\n";
         
         tempRunInfo->tRunNumber.push_back(tempRunNumber);
         tempRunInfo->tTileDac.push_back(tempTileDac);
         tempRunInfo->tLArgEmecDac.push_back(tempLArgEmecDac);
         tempRunInfo->tLArgFcalDac.push_back(tempLArgFcalDac);
         tempRunInfo->tLArgBarrelDac.push_back(tempLArgBarDac);
         tempRunInfo->tLArgHecDac.push_back(tempLArgHecDac);
         
         
      } // end for(treeEntry)
      
      // now I loop over the data tree to get the map of cool ids to tree entry number
      
      std::cout << "   Filling adcPeakVsSlice1/2 and linearFits.\n";
      
      TTree* dataTree = (TTree*)inputFile->Get(dataTreeName.c_str());
      
      unsigned int tempCoolId                  = 0;
      std::vector<bool>* tempIsProcessed       = 0;
      TObjArray* tempSignalProfile             = 0;
      std::vector<float>* tempPeakValue        = 0;
      std::vector<unsigned int>* tempPeakBin   = 0;
      std::vector<unsigned int>* tempErrorBits = 0;
      
      dataTree->SetBranchAddress(bCoolIdName.c_str(),&tempCoolId);
//       dataTree->SetBranchAddress(bIsProcessedName.c_str(),&tempIsProcessed);
      dataTree->SetBranchAddress(bSignalProfileName.c_str(),&tempSignalProfile);
      dataTree->SetBranchAddress(bPeakValueName.c_str(),&tempPeakValue);
      dataTree->SetBranchAddress(bPeakBinName.c_str(),&tempPeakBin);
//       dataTree->SetBranchAddress(bErrorBitsName.c_str(),&tempErrorBits);
      
      unsigned int lastStartEntryA = 0,lastStartEntryB = 0,lastStartEntryC = 0;
      for(unsigned int treeEntry=0;treeEntry<dataTree->GetEntries();++treeEntry){
         
         dataTree->GetEntry(treeEntry);
         
         std::cout << "CoolId: 0x" << std::hex << tempCoolId << std::dec << "\n";
         
         // open the output file for read/write
         if(outputFile == 0){
            outputFile = new TFile(outputFilename.c_str(),"UPDATE");
            if(!outputFile->IsOpen()){
               std::cerr << "ERROR: Failed to re-open " << outputFilename << std::endl;
               continue;
            }
         }
         
         // fill the detector region for this channel
         l1map->SetPpmChannelID(tempCoolId);
         const enum  CaloDivisionEnum region = l1map->GetDetectorRegion();
         
         // load dac vs adc plot from output file
         outputFile->cd(dacVsAdcPeakDirName.c_str());
         TList* listOfKeys = gDirectory->GetListOfKeys();
         TGraph* dacVsAdc = 0;
         for(unsigned int listEntry=lastStartEntryA;listEntry<listOfKeys->GetEntries();++listEntry){
            TKey* key = (TKey*)listOfKeys->At(listEntry);
            
            std::string name = key->GetName();
            
            unsigned int position = name.find('_') + 1;
            std::string strCoolId = "0x";
            strCoolId += name.substr(position,8);
            std::stringstream ssCoolId;
            ssCoolId << strCoolId;
            unsigned int keyCoolId = 0;
            ssCoolId >> std::hex >> keyCoolId;
            
//             std::cout << name << " >> " << std::hex << "0x" << keyCoolId << "   0x" << tempCoolId << std::dec << "   " << strCoolId << std::endl;
            
            if(keyCoolId == tempCoolId){
               dacVsAdc = (TGraph*)key->ReadObj();
               lastStartEntryA = listEntry;
               break;
            }
         }
         
         if(dacVsAdc == 0){
            std::cerr << "Error locating dacVsAdc plot for 0x" << std::hex << tempCoolId << std::dec << std::endl;
         }
         
         // loop over data points in dac Vs Adc plot to get
         // the range of the linear points
         unsigned int linearFitMax = 0;
         for(unsigned int i=0;i<dacVsAdc->GetN();++i){
            double x=0,y=0;
            dacVsAdc->GetPoint(i,x,y);
            if( y > saturatedMin && linearFitMax == 0){
               linearFitMax = (unsigned int)x - 1;
               break; 
            }
         }
         
         // Perform linear fit of the dac Vs Adc plots
         char linearFitName[200];
         sprintf(linearFitName,"linearFit_%08x",tempCoolId);
         TF1* linearFit = new TF1(linearFitName,"pol1",0,linearFitMax);
         dacVsAdc->Fit(linearFit,"rq");
         
         outputFile->cd(fitFunctionDirName.c_str());
         linearFit->Write();
         
         // load adc peak vs slice 1/2 plots from output file
         outputFile->cd(adcPeakVsAdcSlice1DirName.c_str());
         listOfKeys = gDirectory->GetListOfKeys();
         TGraph* adcPeakVsSlice1 = 0;
         for(unsigned int listEntry=lastStartEntryB;listEntry<listOfKeys->GetEntries();++listEntry){
            TKey* key = (TKey*)listOfKeys->At(listEntry);
            
            std::string name = key->GetName();
            
            
            unsigned int position = name.find('_') + 1;
            std::string strCoolId = "0x";
            strCoolId += name.substr(position,8);
            std::stringstream ssCoolId;
            ssCoolId << strCoolId;
            unsigned int keyCoolId = 0;
            ssCoolId >> std::hex >> keyCoolId;
            
            if(keyCoolId == tempCoolId){
               adcPeakVsSlice1 = (TGraph*)key->ReadObj();
               lastStartEntryB = listEntry;
               break;
            }
            
         }
         
         bool deleteAdcPeakVsSlice1 = false;
         if(adcPeakVsSlice1 == 0){
            deleteAdcPeakVsSlice1 = true;
            adcPeakVsSlice1 = new TGraph;
            char graphName[200],graphTitle[200];
            sprintf(graphName,"adcPeakVsSlice1_%08x",tempCoolId);
            adcPeakVsSlice1->SetName(graphName);
            sprintf(graphTitle,"Effective ADC peak vs. 1st slice prior to saturation for 0x%08x;Effective Peak;Slice t_{-1}",tempCoolId);
            adcPeakVsSlice1->SetTitle(graphTitle);
         }
         
         // load adc peak vs slice 1/2 plots from output file
         outputFile->cd(adcPeakVsAdcSlice2DirName.c_str());
         listOfKeys = gDirectory->GetListOfKeys();
         TGraph* adcPeakVsSlice2 = 0;
         for(unsigned int listEntry=lastStartEntryC;listEntry<listOfKeys->GetEntries();++listEntry){
            TKey* key = (TKey*)listOfKeys->At(listEntry);
            
            std::string name = key->GetName();
            
            
            unsigned int position = name.find('_') + 1;
            std::string strCoolId = "0x";
            strCoolId += name.substr(position,8);
            std::stringstream ssCoolId;
            ssCoolId << strCoolId;
            unsigned int keyCoolId = 0;
            ssCoolId >> std::hex >> keyCoolId;
            
            if(keyCoolId == tempCoolId){
               adcPeakVsSlice2 = (TGraph*)key->ReadObj();
               lastStartEntryC = listEntry;
               break;
            }
         }
         
         bool deleteAdcPeakVsSlice2 = false;
         if(adcPeakVsSlice2 == 0){
            deleteAdcPeakVsSlice2 = true;
            adcPeakVsSlice2 = new TGraph;
            char graphName[200],graphTitle[200];
            sprintf(graphName,"adcPeakVsSlice2_%08x",tempCoolId);
            adcPeakVsSlice2->SetName(graphName);
            sprintf(graphTitle,"Effective ADC peak vs. 2nd slice prior to saturation for 0x%08x;Effective Peak;Slice t_{-2}",tempCoolId);
            adcPeakVsSlice2->SetTitle(graphTitle);
         }
         
         // load the summary plots
         
         std::map<unsigned int,TGraph*>::iterator adcVsSlice1Itr,adcVsSlice2Itr;
         
         if(l1map->GetEmHad() == EM){
            std::map<unsigned int,TGraph*>::iterator emAdcVsSlice1Itr = emAdcPeakVsSlice1ByEtaSlice.find(l1map->GetIntegerEta());
            if(emAdcVsSlice1Itr == emAdcPeakVsSlice1ByEtaSlice.end()){
               TGraph* temp = new TGraph;
               char graphName[200];
               sprintf(graphName,"em_adcPeakVsSlice1_eta_%02i",l1map->GetIntegerEta()-49);
               char graphTitle[200];
               sprintf(graphTitle,"ADC Effective Peak Vs 1st slice prior to saturation for EM layer and Eta slice %f;ADC Effective Peak;Slice t_{-1}",l1map->GetEta());
               temp->SetName(graphName);
               temp->SetTitle(graphTitle);
               emAdcPeakVsSlice1ByEtaSlice[l1map->GetIntegerEta()] = temp;
               emAdcVsSlice1Itr = emAdcPeakVsSlice1ByEtaSlice.find(l1map->GetIntegerEta());
            }
            adcVsSlice1Itr = emAdcVsSlice1Itr;
            
            std::map<unsigned int,TGraph*>::iterator emAdcVsSlice2Itr = emAdcPeakVsSlice2ByEtaSlice.find(l1map->GetIntegerEta());
            if(emAdcVsSlice2Itr == emAdcPeakVsSlice2ByEtaSlice.end()){
               TGraph* temp = new TGraph;
               char graphName[200];
               sprintf(graphName,"em_adcPeakVsSlice2_eta_%02i",l1map->GetIntegerEta()-49);
               char graphTitle[200];
               sprintf(graphTitle,"ADC Effective Peak Vs 2nd slice prior to saturation for EM layer and Eta slice %f;ADC Effective Peak;Slice t_{-2}",l1map->GetEta());
               temp->SetName(graphName);
               temp->SetTitle(graphTitle);
               emAdcPeakVsSlice2ByEtaSlice[l1map->GetIntegerEta()] = temp;
               emAdcVsSlice2Itr = emAdcPeakVsSlice2ByEtaSlice.find(l1map->GetIntegerEta());
            }
            adcVsSlice2Itr = emAdcVsSlice2Itr;
         }
         else if(l1map->GetEmHad() == HAD){
            std::map<unsigned int,TGraph*>::iterator hadAdcVsSlice1Itr = hadAdcPeakVsSlice1ByEtaSlice.find(l1map->GetIntegerEta());
            if(hadAdcVsSlice1Itr == hadAdcPeakVsSlice1ByEtaSlice.end()){
               TGraph* temp = new TGraph;
               char graphName[200];
               sprintf(graphName,"had_adcPeakVsSlice1_eta_%02i",l1map->GetIntegerEta()-49);
               char graphTitle[200];
               sprintf(graphTitle,"ADC Effective Peak Vs 1st slice prior to saturation for HAD layer and Eta slice %f;ADC Effective Peak;Slice t_{-1}",l1map->GetEta());
               temp->SetName(graphName);
               temp->SetTitle(graphTitle);
               hadAdcPeakVsSlice1ByEtaSlice[l1map->GetIntegerEta()] = temp;
               hadAdcVsSlice1Itr = hadAdcPeakVsSlice1ByEtaSlice.find(l1map->GetIntegerEta());
            }
            adcVsSlice1Itr = hadAdcVsSlice1Itr;
            
            std::map<unsigned int,TGraph*>::iterator hadAdcVsSlice2Itr = hadAdcPeakVsSlice2ByEtaSlice.find(l1map->GetIntegerEta());
            if(hadAdcVsSlice2Itr == hadAdcPeakVsSlice2ByEtaSlice.end()){
               TGraph* temp = new TGraph;
               char graphName[200];
               sprintf(graphName,"had_adcPeakVsSlice2_eta_%02i",l1map->GetIntegerEta()-49);
               char graphTitle[200];
               sprintf(graphTitle,"ADC Effective Peak Vs 2nd slice prior to saturation for HAD layer and Eta slice %f;ADC Effective Peak;Slice t_{-2}",l1map->GetEta());
               temp->SetName(graphName);
               temp->SetTitle(graphTitle);
               hadAdcPeakVsSlice2ByEtaSlice[l1map->GetIntegerEta()] = temp;
               hadAdcVsSlice2Itr = hadAdcPeakVsSlice2ByEtaSlice.find(l1map->GetIntegerEta());
            }
            adcVsSlice2Itr = hadAdcVsSlice2Itr;
         }
         
         // loop over the vectors,
         // each entry is for a different run
         for(unsigned int i=0;i<tempSignalProfile->GetEntries();++i){
            
            TProfile* prof = (TProfile*)tempSignalProfile->At(i);
            
            // extract the appropriate DAC value for this channel
            unsigned int caloDAC = 0;
            if(region == LArFCAL1C || region == LArFCAL1A || region == LArFCAL23C || region == LArFCAL23A){
               caloDAC = tempRunInfo->tLArgFcalDac[i];
            }
            else if(region == LArEMECC || region == LArEMECA){
               caloDAC = tempRunInfo->tLArgEmecDac[i];
            }
            else if(region == LArEMBC || region == LArEMBA){
               caloDAC = tempRunInfo->tLArgBarrelDac[i];
            }
            else if(region == LArHECC || region == LArHECA){
               caloDAC = tempRunInfo->tLArgHecDac[i];
            }
            else if(region == LArOverlapC || region == LArOverlapA){
               caloDAC = 0;
            }
            else if(region == TileLBC || region == TileLBA || region == TileEBC || region == TileEBA){
               caloDAC = tempRunInfo->tTileDac[i];
            }
            else{
               caloDAC = 0;
            }
            
            
            int peakBin = (int)meanPeakBin[tempCoolId];
//             std::cout << " >>> 0x" << std::hex << tempCoolId << std::dec << " " << tempPeakValue->at(i) << " " << peakBin;
            // fill adcPeakVsSlice1 with the effective adc peak vs. the slice prior to saturation
            if(tempPeakValue->at(i) > saturatedMin){
               // calculate slice1/2
               float slice1 = 0,slice2 = 0;
               if(prof->GetBinContent(peakBin - 25) > saturatedMin){
                  slice1 = prof->GetBinContent(peakBin - 50);
                  slice2 = prof->GetBinContent(peakBin - 75);
               }
               else{
                  slice1 = prof->GetBinContent(peakBin - 25);
                  slice2 = prof->GetBinContent(peakBin - 50);
               }
               
               // calculate the effective peak
               float effPeak = linearFit->GetParameter(1)*caloDAC + linearFit->GetParameter(0);
               
               unsigned int pointNumber = adcPeakVsSlice1->GetN();
               adcPeakVsSlice1->SetPoint(pointNumber,effPeak,slice1);
               
               adcPeakVsSlice1ByPartition[region]->SetPoint(adcPeakVsSlice1ByPartition[region]->GetN(),effPeak,slice1);
               
               adcVsSlice1Itr->second->SetPoint(adcVsSlice1Itr->second->GetN(),effPeak,slice1);
               
               pointNumber = adcPeakVsSlice2->GetN();
               adcPeakVsSlice2->SetPoint(pointNumber,effPeak,slice2);
               
               adcPeakVsSlice2ByPartition[region]->SetPoint(adcPeakVsSlice2ByPartition[region]->GetN(),effPeak,slice2);
               
               adcVsSlice2Itr->second->SetPoint(adcVsSlice2Itr->second->GetN(),effPeak,slice2);
               
               // check to see if this is the largest peak Value for this eta/phi
               if(region == LArFCAL1C || region == LArFCAL1A){
                  if(tempPeakValue->at(i) > pmEmSaturation->GetTriggerTower(l1map->GetEta(),l1map->GetPhi(),FCAL1)){
                     pmEmSaturation->SetTriggerTower(l1map->GetEta(),l1map->GetPhi(),tempPeakValue->at(i),FCAL1);
                  }
               }
               else if(region == LArFCAL23C || region == LArFCAL23A){
                  // FCAL2
                  if(l1map->GetPpmChan()->at(0) == 0 || l1map->GetPpmChan()->at(0) == 3){
                     if(tempPeakValue->at(i) > pmHadSaturation->GetTriggerTower(l1map->GetEta(),l1map->GetPhi(),FCAL2)){
                        pmHadSaturation->SetTriggerTower(l1map->GetEta(),l1map->GetPhi(),tempPeakValue->at(i),FCAL2);
                     }
                  }
                  // FCAL3
                  else if(l1map->GetPpmChan()->at(0) == 1 || l1map->GetPpmChan()->at(0) == 2){
                     if(tempPeakValue->at(i) > pmHadSaturation->GetTriggerTower(l1map->GetEta(),l1map->GetPhi(),FCAL3)){
                        pmHadSaturation->SetTriggerTower(l1map->GetEta(),l1map->GetPhi(),tempPeakValue->at(i),FCAL3);
                     }
                  }
                  
               }
               else{
                  // EM layer
                  if(region == LArEMECC || region == LArEMECA || region == LArOverlapC || region == LArOverlapA
                     || region == LArEMBC || region == LArEMBA){
                     
                     if(tempPeakValue->at(i) > pmEmSaturation->GetTriggerTower(l1map->GetEta(),l1map->GetPhi())){
                        pmEmSaturation->SetTriggerTower(l1map->GetEta(),l1map->GetPhi(),tempPeakValue->at(i));
                     }
                  }
                  
                  // HAD layer
                  if(region == LArHECC || region == LArHECA
                     || region == TileEBC || region == TileEBA || region == TileLBC || region == TileLBA){
                     
                     if(tempPeakValue->at(i) > pmHadSaturation->GetTriggerTower(l1map->GetEta(),l1map->GetPhi())){
                        pmHadSaturation->SetTriggerTower(l1map->GetEta(),l1map->GetPhi(),tempPeakValue->at(i));
                     }
                  }
               }
               
            }// end if(saturated)
            
//             std::cout << std::endl;
         } // end for(vectors)
         
         // delete linearFit
         delete linearFit;
         linearFit = 0;
         
         outputFile->cd(adcPeakVsAdcSlice1DirName.c_str());
         adcPeakVsSlice1->Write(adcPeakVsSlice1->GetName(),TObject::kOverwrite);
         delete adcPeakVsSlice1;
         adcPeakVsSlice1 = 0;
         
         outputFile->cd(adcPeakVsAdcSlice2DirName.c_str());
         adcPeakVsSlice2->Write(adcPeakVsSlice2->GetName(),TObject::kOverwrite);
         delete adcPeakVsSlice2;
         adcPeakVsSlice2 = 0;
         
         delete dacVsAdc;
         dacVsAdc = 0;
         
         if(outputFile != 0){
            outputFile->Close();
            delete outputFile;
            outputFile = 0;
         }
         
         tempSignalProfile->Delete();
         tempSignalProfile = 0;
         delete tempPeakBin;
         tempPeakBin = 0;
         delete tempPeakValue;
         tempPeakValue = 0;
         
      } // end for(dataTree)
      
      delete tempRunInfo;
      tempRunInfo = 0;
      
      inputFile->Close();
      delete inputFile;
      inputFile = 0;
      
   } // end for(fileNum)
   
   outputFile = new TFile(outputFilename.c_str(),"UPDATE");
   
   outputFile->cd(summaryPlotDirName.c_str());
   
   for(unsigned int partition=0;partition < Invalid;++partition){
      
      adcPeakVsSlice1ByPartition[partition]->Write(adcPeakVsSlice1ByPartition[partition]->GetName(),TObject::kOverwrite);
      delete adcPeakVsSlice1ByPartition[partition];
      adcPeakVsSlice1ByPartition[partition] = 0;
      
      
      adcPeakVsSlice2ByPartition[partition]->Write(adcPeakVsSlice2ByPartition[partition]->GetName(),TObject::kOverwrite);
      delete adcPeakVsSlice2ByPartition[partition];
      adcPeakVsSlice2ByPartition[partition] = 0;
      
   }
   
   TH2D* hadSaturation = new TH2D("hadSaturation","HAD Max Signal Peak;#eta;#phi",L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
   pmHadSaturation->FillEtaPhiHistogram(hadSaturation);
   
   hadSaturation->Write();
   
   delete hadSaturation;
   hadSaturation = 0;
   
   delete pmHadSaturation;
   pmHadSaturation = 0;
   
   TH2D* emSaturation = new TH2D("emSaturation","EM Max Signal Peak;#eta;#phi",L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
   pmEmSaturation->FillEtaPhiHistogram(emSaturation);
   
   emSaturation->Write();
   
   delete emSaturation;
   emSaturation = 0;
   
   delete pmEmSaturation;
   pmEmSaturation = 0;
   
   // write adcPeakVsSlice1/2ByEtaSlice graphs to file
   outputFile->cd(std::string(summaryPlotDirName + '/' + etaDependentAdcPeakVsSlice).c_str());
   
   std::map<unsigned int,TGraph*>::iterator itr = emAdcPeakVsSlice1ByEtaSlice.begin();
   for(;itr != emAdcPeakVsSlice1ByEtaSlice.end();++itr){
      itr->second->Write();
      delete itr->second;
      itr->second = 0;
   }
   emAdcPeakVsSlice1ByEtaSlice.clear();
   
   itr = hadAdcPeakVsSlice1ByEtaSlice.begin();
   for(;itr != hadAdcPeakVsSlice1ByEtaSlice.end();++itr){
      itr->second->Write();
      delete itr->second;
      itr->second = 0;
   }
   hadAdcPeakVsSlice1ByEtaSlice.clear();
   
   itr = emAdcPeakVsSlice2ByEtaSlice.begin();
   for(;itr != emAdcPeakVsSlice2ByEtaSlice.end();++itr){
      itr->second->Write();
      delete itr->second;
      itr->second = 0;
   }
   emAdcPeakVsSlice2ByEtaSlice.clear();
   
   itr = hadAdcPeakVsSlice2ByEtaSlice.begin();
   for(;itr != hadAdcPeakVsSlice2ByEtaSlice.end();++itr){
      itr->second->Write();
      delete itr->second;
      itr->second = 0;
   }
   hadAdcPeakVsSlice2ByEtaSlice.clear();
   
   if(outputFile != 0){
      outputFile->Close();
      delete outputFile;
      outputFile = 0;
   }
   
   std::cout << "Output Filename: " << outputFilename << std::endl;
   
   return 0;
}



