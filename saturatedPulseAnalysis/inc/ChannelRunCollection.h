#ifndef CHANNELRUNCOLLECTION_H
#define CHANNELRUNCOLLECTION_H

#include <map>
#include <vector>
#include <string>

#include "ChannelRunEntry.h"

#include "TCanvas.h"
#include "TGraph.h"
#include "TF1.h"

class ChannelRunCollection{
public:
   ChannelRunCollection(void){};
   ChannelRunCollection(unsigned int id){SetCoolId(id);};
   
   void push_back(ChannelRunEntry* const entry){m_runList[entry->GetRunNumber()] = entry;};
   
   typedef std::map<unsigned int,ChannelRunEntry*>::iterator RunEntry_itr;
   RunEntry_itr begin(void){return m_runList.begin();};
   RunEntry_itr end(void){return m_runList.end();};
   unsigned int size(void){return m_runList.size();};
   
   void SetCoolId(unsigned int id){m_coolId = id;};
   unsigned int GetCoolId(void){return m_coolId;};
   
   void PlotSignalsToCanvas(TCanvas* canvas);
   
   void PlotDacVsAdcPeak(void);
   
   void PlotAdcPeakVsSlice12(void);
   
private:
   std::map <unsigned int,ChannelRunEntry*> m_runList;
   
   unsigned int m_coolId;
   
   
   TGraph* m_dacVsAdcPeak;
   TF1*    m_linearFit;
   std::vector<float> m_par;
   std::vector<float> m_parError;
   
   TGraph* m_peakVsSlice1;
   TGraph* m_peakVsSlice2;
   
   const static unsigned int minPedestal = CRE_MIN_PEDESTAL;
   const static unsigned int maxPedestal = CRE_MAX_PEDESTAL;
   
};

#endif

