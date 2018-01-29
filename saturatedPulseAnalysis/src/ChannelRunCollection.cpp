#include "ChannelRunCollection.h"


// given a canvas, this function will plot all the signals on it
void ChannelRunCollection::PlotSignalsToCanvas(TCanvas* canvas){
   
   canvas->cd();
   
   RunEntry_itr itr = m_runList.begin(),itrEnd = m_runList.end();
   
   bool firstRun = true;
   unsigned int colorCount = 1;
   for(;itr!=itrEnd;++itr){
      
   
      std::string opts = "same";
      if(firstRun){
         opts = "";
         firstRun = false;
      }
      
      // force this to run until I update algorithm code to run on new Athena Algs output
      if(itr->second->GetIsProcessed() || true){
         TProfile* prof = itr->second->GetProcessedSignalShape();
         std::cerr << prof << std::endl;
         prof->SetMarkerColor(colorCount);
         prof->Draw(opts.c_str());
         
      }
      else{
         itr->second->GetRawSignalShape()->SetMarkerColor(colorCount);
         itr->second->GetRawSignalShape()->Draw(opts.c_str());
      }
      
      colorCount++;
      if(colorCount == 10) colorCount += 17;
   }
   
}

void ChannelRunCollection::PlotDacVsAdcPeak(void){
   
   
   const unsigned int arrayLength = size();
   float xDac[arrayLength],yAdcPeak[arrayLength];
   
   unsigned int fitMax = 0;
   // loop over the runs in this collection
   RunEntry_itr itr = begin();
   for(unsigned int entry=0;itr!=end();++itr,++entry){
      
      xDac[entry] = itr->second->GetCaloDacValue();
      yAdcPeak[entry] = itr->second->GetProcessedPeakValue();
      
      if(itr->second->GetProcessedPeakValue() > (float)minPedestal && fitMax == 0){
         fitMax = itr->second->GetProcessedPeakBin() - 1;
      }
   }
   
   // Create graph
   m_dacVsAdcPeak = new TGraph(arrayLength,xDac,yAdcPeak);
   char graphName[200];
   sprintf(graphName,"dacVsAdcPeak_0x%08x",m_coolId);
   char graphTitle[200];
   sprintf(graphTitle,"Calo DAC Vs. L1Calo ADC Signal Peak for 0x08x;Calo DAC;L1Calo ADC Peak Value",m_coolId);
   
   m_dacVsAdcPeak->SetName(graphName);
   m_dacVsAdcPeak->SetTitle(graphTitle);
   m_dacVsAdcPeak->SetMarkerStyle(8);
   
   // fit the linear region
   char fitName[200];
   sprintf(fitName,"linearFit_0x%08x",m_coolId);
   m_linearFit = new TF1(fitName,"pol1",0,fitMax);
   
   m_dacVsAdcPeak->Fit(m_linearFit,"rq");
   
   // extract fit parameters
   for(unsigned int i=0; i < m_linearFit->GetNpar();++i){
      m_par.push_back(m_linearFit->GetParameter(i));
      m_parError.push_back(m_linearFit->GetParError(i));
   }
   
   // loop over run entries and calculate the Slice -1 and -2
   itr = begin();
   for(;itr!=end();++itr){
      itr->second->CalculateEffectivePeakValue(m_par,m_parError);
   }
   
}

void ChannelRunCollection::PlotAdcPeakVsSlice12(void){
   
   const unsigned int arrayLength = size();
   float xEffectiveAdcPeak[arrayLength],yAdcSlice1[arrayLength],yAdcSlice2[arrayLength];
   
   // loop over the run entries and  fill the arrays for the graphs
   RunEntry_itr itr = begin();
   for(unsigned int entry=0;itr!=end();++itr,++entry){
      xEffectiveAdcPeak[entry] = itr->second->GetEffectivePeakValue();
      yAdcSlice1[entry] = itr->second->GetProcessedSlice1();
      yAdcSlice2[entry] = itr->second->GetProcessedSlice2();
   }
   
   m_peakVsSlice1 = new TGraph(arrayLength,xEffectiveAdcPeak,yAdcSlice1);
   char graphName[200];
   sprintf(graphName,"peakVsSlice1_0x%08x",m_coolId);
   m_peakVsSlice1->SetName(graphName);
   char graphTitle[200];
   sprintf(graphTitle,"Effective ADC Peak Vs. Slice (-1) for 0x%08x;ADC Peak;ADC Slice (-1)",m_coolId);
   m_peakVsSlice1->SetTitle(graphTitle);
   m_peakVsSlice1->SetMarkerStyle(8);
   
   
   m_peakVsSlice2 = new TGraph(arrayLength,xEffectiveAdcPeak,yAdcSlice2);
   sprintf(graphName,"peakVsSlice2_0x%08x",m_coolId);
   m_peakVsSlice2->SetName(graphName);
   sprintf(graphTitle,"Effective ADC Peak Vs. Slice (-2) for 0x%08x;ADC Peak;ADC Slice (-2)",m_coolId);
   m_peakVsSlice2->SetTitle(graphTitle);
   m_peakVsSlice2->SetMarkerStyle(8);
   
}





