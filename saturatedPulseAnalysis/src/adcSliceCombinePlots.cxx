#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "L1CaloChannelMap.h"

#include "TFile.h"
#include "TProfile.h"
#include "TH2I.h"
#include "TKey.h"
#include "TList.h"
#include "TDirectory.h"

unsigned int GetCoolId(string name);

int main(int argc,char** argv){
   
   TH1::AddDirectory(false);
   
   string inFilename;
   if(argc != 2 || argv[1] == "-h" || argv[1] == "--help"){
      cout << " usage: adcSliceCombinePlots <input filename>\n";
      return 0;
   }
   else inFilename = argv[1];
   
   TFile inFile(inFilename.c_str(),"READ");
   if(!inFile.IsOpen()){
      cout << "Could not open file: " << inFilename << endl;
      cout << " usage: adcSliceCombinePlots <input filename>\n";
      return 0;
   }
   
   string baseDirectory = "ExampleDirectory";
   string peakDirectory = baseDirectory + "/peak";
   string peakM1directory = baseDirectory + "/peakMinusOne";
   string peakM2directory = baseDirectory + "/peakMinusTwo";
   string peakM3directory = baseDirectory + "/peakMinusThree";
   
   // Want a few types of histograms
   // 1. grouped into partition by partition
   // 2. grouped by eta slice
   // 3. grouped by PPM module
   
   L1CaloChannelMap* l1map = new L1CaloChannelMap;
   l1map->SetCpmEnable(false);
   l1map->SetJemEnable(false);
   l1map->SetTcppEnable(false);
   
   const unsigned int xbins = 250;
   const unsigned int xmax  = 500;
   const unsigned int xmin  =   0;
    
   const unsigned int ybins =  206;
   const unsigned int ymax  = 1030;
   const unsigned int ymin  =    0;
   
   
   map<unsigned int,TH2I*> map_div_peak;
   map<unsigned int,TH2I*> map_em_eta_peak;
   map<unsigned int,TH2I*> map_had_eta_peak;
   map<unsigned int,TH2I*> map_ppm_peak;
   
   for(unsigned short int crate=0;crate<8;++crate){
   for(unsigned short int module=0;module<16;++module){
   for(unsigned short int submodule=0;submodule<16;++submodule){
   for(unsigned short int channel=0;channel<4;++channel){
      l1map->SetPpmChannel(crate,module,submodule,channel);
      if(!l1map->IsPpmChannelUsed()) continue;
      CaloDivision div = l1map->GetDetectorRegion();
      
      // first see if division plot exists
      map<unsigned int,TH2I*>::iterator itr = map_div_peak.find((int)div.GetDivision());
      if(itr == map_div_peak.end()){
         string name = "peak_";
         name += div.GetString();
         string title = "ADC Peak Slice vs. Calo Energy for ";
         title += div.GetString();
         title += ";Calo Energy (GeV);ADC Peak Slice";
         TH2I *temp = new TH2I(name.c_str(),title.c_str(),xbins,xmin,xmax,ybins,ymin,ymax);
         map_div_peak[(int)div.GetDivision()] = temp;
      }
      
      // second see if eta slice plot exists
      unsigned int eta = l1map->GetIntegerEta();
      if(l1map->GetLayer() == CaloLayer::EM){
         itr = map_em_eta_peak.find(eta);
         if(itr == map_em_eta_peak.end()){
            string name = "peak_em_eta_";
            char ceta[10];
            sprintf(ceta,"%03i",eta-49);
            name += ceta;
            string title = "ADC Peak Slice vs. Calo Energy for EM Eta Slice ";
            title += ceta;
            title += ";Calo Energy (GeV);ADC Peak Slice";
            TH2I *temp = new TH2I(name.c_str(),title.c_str(),xbins,xmin,xmax,ybins,ymin,ymax);
            map_em_eta_peak[eta] = temp;
         }
      }
      else if(l1map->GetLayer() == CaloLayer::HAD){
         itr = map_had_eta_peak.find(eta);
         if(itr == map_had_eta_peak.end()){
            string name = "peak_had_eta_";
            char ceta[10];
            sprintf(ceta,"%03i",eta-49);
            name += ceta;
            string title = "ADC Peak Slice vs. Calo Energy for HAD Eta Slice ";
            title += ceta;
            title += ";Calo Energy (GeV);ADC Peak Slice";
            TH2I *temp = new TH2I(name.c_str(),title.c_str(),xbins,xmin,xmax,ybins,ymin,ymax);
            map_had_eta_peak[eta] = temp;
         }
      }
      
      // third see if the ppm plot exists
      unsigned int ppm = module + 16*crate;
      itr = map_ppm_peak.find(ppm);
      if(itr == map_ppm_peak.end()){
         string name = "peak_ppm_";
         char cppm[5];
         sprintf(cppm,"%03i",ppm);
         name += cppm;
         string title = "ADC Peak Slice vs. Calo Energy for PPM ";
         title += cppm;
         title += ";Calo Energy (GeV);ADC Peak Slice";
         TH2I *temp = new TH2I(name.c_str(),title.c_str(),xbins,xmin,xmax,ybins,ymin,ymax);
         map_ppm_peak[ppm] = temp;
         
      }
      
   }
   }
   }
   }
   
   
   // first loop over the peak directory
   inFile.cd(peakDirectory.c_str());
   TList *list = gDirectory->GetListOfKeys();
   
   for(int entry=0;entry<list->GetEntries();++entry){
      TKey *key = (TKey*)list->At(entry);
      TProfile *prof = (TProfile*)key->ReadObj();
      
      // get channel Id from name
      L1CaloChannelId id(GetCoolId(prof->GetName()));
      
      // set channel map
      l1map->SetPpmChannelID(id);
      CaloDivision div = l1map->GetDetectorRegion();
      unsigned int ppmNum = l1map->GetPpmCrate()->at(0)*16 + l1map->GetPpmModule()->at(0);
      
      
      // get iterator to partition depedent plots
      map<unsigned int,TH2I*>::iterator itrDiv = map_div_peak.find((int)div.GetDivision());
      bool fillDiv=false;
      if(itrDiv == map_div_peak.end()){
         cout << " ERROR: Could not find map_div_peak[" << div.GetString() << "] for channel 0x" << id.GetIdAsString() << endl;
      }
      else fillDiv=true;
      
      // get iterator to em eta slice depedent plots
      map<unsigned int,TH2I*>::iterator itrEta;
      bool fillEta=false;
      if(l1map->GetLayer() == CaloLayer::EM){
         itrEta = map_em_eta_peak.find(l1map->GetIntegerEta());
         if(itrEta == map_em_eta_peak.end()){
            cout << " ERROR: Could not find map_em_eta_peak[" << div.GetString() << "] for channel 0x" << id.GetIdAsString() << endl;
         }
         else fillEta=true;
      }
      else if(l1map->GetLayer() == CaloLayer::HAD){
         itrEta = map_had_eta_peak.find(l1map->GetIntegerEta());
         if(itrEta == map_had_eta_peak.end()){
            cout << " ERROR: Could not find map_had_peak[" << div.GetString() << "] for channel 0x" << id.GetIdAsString() << endl;
         }
         else fillEta=true;
      }
      
      // get iterator to ppm depedent plots
      map<unsigned int,TH2I*>::iterator itrPpm = map_ppm_peak.find(ppmNum);
      bool fillPpm=false;
      if(itrPpm == map_ppm_peak.end()){
         cout << " ERROR: Could not find map_ppm_peak[" << div.GetString() << "] for channel 0x" << id.GetIdAsString() << endl;
      }
      else fillPpm=true;
      
      // now fill histograms
      for(unsigned int bin=1;bin<prof->GetNbinsX();++bin){
         
         // if there is no mean ADC for this bin skip it.
         if(prof->GetBinEntries(bin) <= 0) continue;
         
         float caloEnergyGeV = bin-1;
         float meanAdc = prof->GetBinContent(bin);
         if(fillDiv){
            itrDiv->second->Fill(caloEnergyGeV,meanAdc);
         }
         if(fillEta){
            itrEta->second->Fill(caloEnergyGeV,meanAdc);
         }
         if(fillPpm){
            itrPpm->second->Fill(caloEnergyGeV,meanAdc);
         }
      }
      
      
      delete prof;
      prof = 0;
   }
   
   // close input file
   inFile.Close();
   
   // now loop over each map and write to disk
   
   
   string outFilename = "adcSliceCombinePlots.root";
   TFile outFile(outFilename.c_str(),"RECREATE");
   outFile.mkdir("peak");
   outFile.cd("peak");
   gDirectory->mkdir("caloDivision");
   gDirectory->mkdir("em_eta");
   gDirectory->mkdir("had_eta");
   gDirectory->mkdir("ppm");
   
   gDirectory->cd("caloDivision");
   map<unsigned int,TH2I*>::iterator itr = map_div_peak.begin();
   for(;itr != map_div_peak.end();++itr){
      TH2I *hist = itr->second;
      hist->Write();
   }
   
   outFile.cd("peak");
   gDirectory->cd("em_eta");
   itr = map_em_eta_peak.begin();
   for(;itr != map_em_eta_peak.end();++itr){
      TH2I *hist = itr->second;
      hist->Write();
   }
   
   outFile.cd("peak");
   gDirectory->cd("had_eta");
   itr = map_had_eta_peak.begin();
   for(;itr != map_had_eta_peak.end();++itr){
      TH2I *hist = itr->second;
      hist->Write();
   }
   
   outFile.cd("peak");
   gDirectory->cd("ppm");
   itr = map_ppm_peak.begin();
   for(;itr != map_ppm_peak.end();++itr){
      TH2I *hist = itr->second;
      hist->Write();
   }
   
   outFile.Close();
   
   return 0;
}


unsigned int GetCoolId(string name){
   size_t start = name.find("_0");
   if(start !=string::npos)
      start = start + 1; // skip '_'
   int length = 8;
   string sid = name.substr(start,length);
   
   stringstream ssid(sid);
   unsigned int id = 0;
   ssid >> hex >> id >> dec;
   
   return id;
}
