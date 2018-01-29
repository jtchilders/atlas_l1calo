#ifndef DACVSADCPEAKGRAPH_H
#define DACVSADCPEAKGRAPH_H

#include <vector>
#include <string>

#include "TGraph.h"
#include "TH1.h"
#include "TF1.h"
#include "TAxis.h"

#include "L1CaloChannelId.h"
#include "MeanValue.h"

class DacVsAdcPeakGraph{
public:
   DacVsAdcPeakGraph(void);
   DacVsAdcPeakGraph(L1CaloChannelId id);
   ~DacVsAdcPeakGraph(void);
   
   void Initialize(void);
   
   void Fill(const unsigned int dac,const float adcPeak,const unsigned int peakBin,const float meanPedestal,TH1* signal);
   
   void Build(void);
   
   void SetL1CaloChannelId(const L1CaloChannelId id){m_coolId = id;};
   L1CaloChannelId GetL1CaloChannelId(void){return m_coolId;};
   
   void SetBaseGraphTitle(std::string title){m_s_graphBaseTitle = title;};
   std::string GetBaseGraphTitle(void){return m_s_graphBaseTitle;};
   void SetBaseGraphName(std::string name){m_s_graphBaseName = name;};
   std::string GetBaseGraphName(void){return m_s_graphBaseName;};
   
   void SetBaseFitName(std::string name){m_s_fitBaseName = name;};
   std::string GetBaseFitName(void){return m_s_fitBaseName;};
   
   MeanValue* GetMeanSlope(void){return &m_meanSlope;};
   
   unsigned short int GetAnalogueSaturationLevel(void){return m_analogueSaturation;};
   unsigned short int GetSaturationLevel(void){return m_saturationLevel;};
   
   std::vector<unsigned short int>* GetUnsaturatedDac(void){return &m_unsat_dac;};
   std::vector<float>* GetUnsaturatedAdcPeak(void){return &m_unsat_adcPeak;};
   
   std::vector<unsigned short int>* GetSaturatedDac(void){return &m_sat_dac;};
   std::vector<float>* GetSaturatedAdcPeak(void){return &m_sat_adcPeak;};
   
   void Draw(std::string opts){if(m_graph!=0)m_graph->Draw(opts.c_str());};
   
   TGraph* GetGraph(void){return m_graph;};
   
   void DrawFit(std::string opts){if(m_fit!=0)m_fit->Draw(opts.c_str());};
   
   TF1* GetFit(void){return m_fit;};
   
   bool IsTooFewPoints(void){return m_tooFewPoints;};
   bool IsNoSaturatedData(void){return m_noSatData;};
   
   std::vector<unsigned short int>* GetTs1EstAdcPeak(void){return &m_v_ts1_estAdc;};
   std::vector<unsigned short int>* GetTs1(void){return &m_v_ts1;};
   std::vector<unsigned short int>* GetTs2EstAdcPeak(void){return &m_v_ts2_estAdc;};
   std::vector<unsigned short int>* GetTs2(void){return &m_v_ts2;};
   
   unsigned int GetSatEntries(void){return m_sat_dac.size();};
   unsigned int GetUnsatEntries(void){return m_unsat_dac.size();};
   
   void IsProcessed(bool processed){m_isProcessed = processed;};
   bool IsProcessed(void){return m_isProcessed;};
   
   MeanValue* GetMeanPeakBin(void){return &m_peakBin;};
   
   unsigned int GetEntries(void) const { m_v_dac.size();}; 
   
private:
   std::vector<TH1*> m_v_signal;
   std::vector<unsigned int> m_v_dac;
   std::vector<float> m_v_adcPeak;
   std::vector<float> m_v_meanPedestal;
   std::vector<unsigned int> m_v_peakBin;
   
   TGraph *m_graph;
   std::string m_s_graphBaseName;
   std::string m_s_graphBaseTitle;
   std::string m_s_xAxisTitle;
   std::string m_s_yAxisTitle;
   
   bool m_isProcessed; // false = raw; true = processed
   
   MeanValue m_meanSlope;
   unsigned short int m_fitMaxRange;
   unsigned short int m_analogueSaturation;
   bool m_isAnalogueSaturation;
   
   MeanValue m_peakBin;
   std::vector<unsigned short int> m_v_ts1;
   std::vector<unsigned short int> m_v_ts1_estAdc;
   std::vector<unsigned short int> m_v_ts2;
   std::vector<unsigned short int> m_v_ts2_estAdc;
   
   TF1 *m_fit;
   std::string m_s_fitBaseName;
   bool m_tooFewPoints;
   bool m_noSatData;
   
   std::vector<float> m_unsat_adcPeak;
   std::vector<unsigned short int> m_unsat_dac;
   
   std::vector<float> m_sat_adcPeak;
   std::vector<unsigned short int> m_sat_dac;
   
   L1CaloChannelId m_coolId;
   
   template <class T> void Vect2array(const std::vector<T> x, float xprime[]){
      for(unsigned short int i=0;i<x.size();++i) xprime[i] = (float)x[i];
   }
   template <class T> void Array2vect(const unsigned int n,T x[],std::vector<T>& xprime){
      for(unsigned int i=0;i<n;++i) xprime.push_back(x[i]);
   }
   
   template <class A,class B> bool VectSortByX(std::vector<A>& x,std::vector<B>& y);
   
   std::string GetPlotName(const std::string base,const L1CaloChannelId coolId) const;
   std::string GetPlotTitle(const std::string base,const L1CaloChannelId coolId) const;
   
   static const unsigned short int m_saturationLevel = 1020;
   
   bool FillGraph(void);
   bool FitGraph(void);
   
};

template <class A,class B>
bool DacVsAdcPeakGraph::VectSortByX(std::vector<A>& x,std::vector<B>& y){
   // sort the vectors by the x entry from lowest to highest
   
   if(x.size() != y.size()){
      std::cerr << "[DacVsAdcPeakGraph::VectSortByX] size of vectors differs: x:" << x.size() << " y: " << y.size() << ". Cannot continue for channel: " << std::hex << m_coolId.GetId() << std::dec << ".\n";
      return false;
   }
   
   bool orderChanged = true;
   while(orderChanged){
      
      orderChanged = false;
      for(int i=x.size()-1;i>0;--i){
         // if x is less than previous value swap entries
         if(x[i] < x[i-1]){
            A tempX=0;
            B tempY=0;
            tempX = x[i];
            tempY = y[i];
            x[i] = x[i-1];
            y[i] = y[i-1];
            x[i-1] = tempX;
            y[i-1] = tempY;
            orderChanged = true;
            
         }
      }
      
   } // end while(orderChanged)
   
   return true;
}


#endif

