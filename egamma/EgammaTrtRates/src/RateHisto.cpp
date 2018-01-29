#include "RateHisto.h"


RateHisto::RateHisto(void){
   m_histoName = "rateHisto";
   m_histoTitle = "Rate Histogram";
   m_histo = 0;
   m_prescaleCorrectedHisto = 0;
   m_secPerLumiBlock = 120; // default for most physics runs as of Aug 3 2010.
}

RateHisto::RateHisto(std::string name, std::string title){
   m_histoName = name;
   m_histoTitle = title;
   m_histo = 0;
   m_prescaleCorrectedHisto = 0;
   m_secPerLumiBlock = 120; // default for most physics runs as of Aug 3 2010.
}

RateHisto::~RateHisto(void){
   if(m_histo!=0){
      delete m_histo;
      m_histo = 0;
   }
   
   if(m_prescaleCorrectedHisto!=0){
      delete m_prescaleCorrectedHisto;
      m_prescaleCorrectedHisto = 0;
   }
}

void RateHisto::SetPrescale(unsigned int lumiBmin,unsigned int lumiBmax,int prescale){
   for(unsigned int i=lumiBmin;i<=lumiBmax;++i)
      m_map_lbn_prescale[i] = prescale;
}

TH1F* RateHisto::BuildHisto(void){
   
   std::map<unsigned short int,int>::iterator itrPrescale;
   std::map<unsigned short int,unsigned int>::iterator itr = m_map_lbn_nhits.begin();
   unsigned short int lbn_min=0xffff,lbn_max = 0;
   for(;itr!=m_map_lbn_nhits.end();++itr){
      unsigned short int lumiNum = itr->first;
      if(lumiNum < lbn_min){
         lbn_min = lumiNum;
      }
      if(lumiNum > lbn_max){
         lbn_max = lumiNum;
      }
      
      // make sure there is a prescale for every lumiblock
      itrPrescale = m_map_lbn_prescale.find(lumiNum);
      // if no prescale is found for this lumi block, enter a value of 1
      if(itrPrescale == m_map_lbn_prescale.end()){
         m_map_lbn_prescale[lumiNum] = 1;
      }
   }
   
   // create normal histogram
   m_histo = new TH1F(m_histoName.c_str(),m_histoTitle.c_str(),lbn_max-lbn_min,lbn_min,lbn_max);
   // create corrected histogram
   std::string prescaleName = m_histoName + "_prescaleCorrected";
   std::string prescaleTitle = m_histoTitle + " with Prescale Correction";
   m_prescaleCorrectedHisto = new TH1F(prescaleName.c_str(),prescaleTitle.c_str(),lbn_max-lbn_min,lbn_min,lbn_max);
   
   
   itr = m_map_lbn_nhits.begin();
   for(;itr!=m_map_lbn_nhits.end();++itr){
      unsigned short int lumiNum = itr->first;
      float rateInHz = (float)itr->second/(float)m_secPerLumiBlock;
      m_histo->Fill(lumiNum,rateInHz);
      
      itrPrescale = m_map_lbn_prescale.find(lumiNum);
      float correctedRateInHz = 0;
      if(itrPrescale->second > 0) // prescale < 0 means disabled
         correctedRateInHz = rateInHz*itrPrescale->second;
      m_prescaleCorrectedHisto->Fill(lumiNum,correctedRateInHz);
   }
   
   return m_histo;
}

