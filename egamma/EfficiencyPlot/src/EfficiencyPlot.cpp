#include "EfficiencyPlot.h"

EfficiencyPlot::EfficiencyPlot(const std::string name,const std::string title,const unsigned int nbinsx,const float xlow,const float xup):
   m_s_name(name),
   m_s_title(title)
{
   
   std::string denom_name = m_s_name + "_denom";
   m_denominator = new TH1D(denom_name.c_str(),m_s_title.c_str(),nbinsx,xlow,xup);
   
   std::string numer_name = m_s_name + "_numer";
   m_numerator = new TH1D(numer_name.c_str(),m_s_title.c_str(),nbinsx,xlow,xup);
   
}

TH1D* EfficiencyPlot::GetResult(void){
   
   
}

