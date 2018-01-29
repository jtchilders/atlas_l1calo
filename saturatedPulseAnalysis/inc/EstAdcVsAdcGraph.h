#ifndef ESTADCVSADCGRAPH_H
#define ESTADCVSADCGRAPH_H

#include <vector>
#include <string>

#include "TGraph.h"
#include "TF1.h"
#include "TAxis.h"
#include "TGaxis.h"

#include "L1CaloChannelId.h"
#include "MeanValue.h"

class EstAdcVsAdcGraph{
public:
   EstAdcVsAdcGraph(void);
   EstAdcVsAdcGraph(L1CaloChannelId id);
   ~EstAdcVsAdcGraph(void);
   
   void Build(std::vector<unsigned short int>* estAdcPeak,std::vector<unsigned short int>* timeSlice,std::vector<unsigned short int>* 
dac );
   
   void SetL1CaloChannelId(const L1CaloChannelId id){m_coolId = id;};
   L1CaloChannelId GetL1CaloChannelId(void) const {return m_coolId;};
   
   void SetBaseGraphTitle(std::string title){m_s_graphBaseTitle = title;};
   std::string GetBaseGraphTitle(void) const {return m_s_graphBaseTitle;};
   void SetBaseGraphName(std::string name){m_s_graphBaseName = name;};
   std::string GetBaseGraphName(void) const {return m_s_graphBaseName;};
   
   void SetGraphXaxisTitle(std::string title){m_s_xAxisTitle = title;};
   void SetGraphYaxisTitle(std::string title){m_s_yAxisTitle = title;};
   
   void SetBaseFitName(std::string name){m_s_fitBaseName = name;};
   std::string GetBaseFitName(void) const {return m_s_fitBaseName;};
   
   unsigned short int GetSaturationLevel(void) const {return m_saturationLevel;};
   
   void Draw(std::string opts) const {if(m_graph!=0)m_graph->Draw(opts.c_str());};
   
   TGraph* GetGraph(void) const {return m_graph;};
   
   void DrawAxis(std::string opts) const {if(m_dacAxis!=0)m_dacAxis->Draw(opts.c_str());};
   
   TGaxis* GetAxis(void) const {return m_dacAxis;};
   
   void DrawFit(std::string opts){if(m_fit!=0)m_fit->Draw(opts.c_str());};
   
   TF1* GetFit(void) const {return m_fit;};
   
   bool IsTooFewSatSlices(void) const {return m_tooFewSatSlices;};
   bool IsNoSatSlices(void) const {return m_noSatSlices;};
   unsigned short int GetNumberOfFitPoints(void) const {return m_numberFitPoints;}; 
   
   void IsTs2(bool ts2){m_isTs2 = ts2;};
   bool IsTs2(void) const {return m_isTs2;};
   void IsProcessed(bool processed){m_isProcessed = processed;};
   bool IsProcessed(void) const {return m_isProcessed;};
   
   void SetMeanPeakBin(const unsigned int peakBin){m_meanPeakBin=peakBin;};
   unsigned int GetMeanPeakBin(void) const {return m_meanPeakBin;};
   
   void SetMeanPedestal(const float pedestal){m_meanPedestal=pedestal;};
   float GetMeanPedestak(void) const {return m_meanPedestal;};
   
   unsigned short int GetThreshold(void) const {return m_threshold;};
   
   void SetAnalogueSaturationLevel(unsigned short int level){m_analogueSaturationLevel = level;};
   unsigned short int GetAnalogueSaturationLevel(void){return m_analogueSaturationLevel;};
   
private:
   TGraph *m_graph;
   std::string m_s_graphBaseName;
   std::string m_s_graphBaseTitle;
   std::string m_s_xAxisTitle;
   std::string m_s_yAxisTitle;
   
   TGaxis *m_dacAxis;
   
   TF1 *m_fit;
   std::string m_s_fitBaseName;
   bool m_tooFewSatSlices;
   bool m_noSatSlices;
   
   unsigned int m_meanPeakBin;
   
   float m_maxFitBound_estAdc;
   unsigned short int m_numberFitPoints;
   
   unsigned short int m_analogueSaturationLevel;
   
   bool m_isTs2; // false = t_{-1}; true = t_{-2}
   bool m_isProcessed; // false = raw; true = processed
   
   float m_meanPedestal;
   unsigned short int m_threshold;
   
   L1CaloChannelId m_coolId;
   
   
   template <class T> void Vect2array(const std::vector<T> x, float xprime[]){
      for(unsigned short int i=0;i<x.size();++i) xprime[i] = (float)x[i];
   }
   template <class T> void Array2vect(const unsigned int n,T x[],std::vector<T>& xprime){
      for(unsigned int i=0;i<n;++i) xprime.push_back(x[i]);
   }
   template <class A,class B> bool VectSortByX(std::vector<A>& x,std::vector<B>& y);
   
   void Initialize(void);
   std::string GetPlotName(const std::string base,const L1CaloChannelId coolId) const;
   std::string GetPlotTitle(const std::string base,const L1CaloChannelId coolId) const;
   
   void FillGraph(std::vector<unsigned short int>& estAdcPeak,std::vector<unsigned short int>& timeSlice);
   void FitGraph(void);
   
   static const unsigned short int m_saturationLevel = 1020;
   
};

template <class A,class B>
bool EstAdcVsAdcGraph::VectSortByX(std::vector<A>& x,std::vector<B>& y){
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

