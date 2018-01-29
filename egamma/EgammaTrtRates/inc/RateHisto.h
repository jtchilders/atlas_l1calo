#ifndef RATEHISTO_H
#define RATEHISTO_H


#include <map>
#include <string>

#include "TH1F.h"

class RateHisto{
public:
   RateHisto(void);
   RateHisto(std::string name, std::string title);
   ~RateHisto(void);
   
   std::string GetName(void){return m_histoName;};
   void SetName(std::string name){m_histoName = name;m_histo->SetName(name.c_str());};
   
   std::string GetTitle(void){return m_histoTitle;};
   void SetTitle(std::string title){m_histoTitle = title;m_histo->SetTitle(title.c_str());};
   
   void IncrementLumiblock(unsigned short int lumiNumber){m_map_lbn_nhits[lumiNumber]++;};
   
   void SetSecondsPerLumiBlock(unsigned int value){m_secPerLumiBlock = value;}
   unsigned int GetSecondsPerLumiBlock(void){return m_secPerLumiBlock;};
   
   void SetPrescale(unsigned int lumiBmin,unsigned int lumiBmax,int prescale);
   
   TH1F* BuildHisto(void);
   
   TH1F* GetHisto(void){return m_histo;};
   TH1F* GetPrescaleCorrectedHisto(void){return m_prescaleCorrectedHisto;};
   
   void SetLineColor(int color){m_histo->SetLineColor(color);
      m_prescaleCorrectedHisto->SetLineColor(color);};
   
private:
   TH1F *m_histo;
   TH1F *m_prescaleCorrectedHisto;
   std::string m_histoName;
   std::string m_histoTitle;
   
   unsigned int m_secPerLumiBlock;
   
   std::map<unsigned short int,unsigned int> m_map_lbn_nhits;
   std::map<unsigned short int,int> m_map_lbn_prescale;
   
};




#endif
