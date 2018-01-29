#include "DacVsAdcPeakGraph.h"

#include "TCanvas.h"
#include "TROOT.h"

DacVsAdcPeakGraph::DacVsAdcPeakGraph(void){
   Initialize();
}


DacVsAdcPeakGraph::DacVsAdcPeakGraph(L1CaloChannelId id):
   m_coolId(id)
{
   Initialize();
}

void DacVsAdcPeakGraph::Initialize(void){
   m_graph = 0;
   m_s_graphBaseName = "dacVsAdcPeak";
   m_s_graphBaseTitle = "Calo DAC vs. FADC Peak";
   m_s_xAxisTitle = "Calo DAC Value";
   m_s_yAxisTitle = "FADC Peak Value";
   
   m_fit = 0;
   m_s_fitBaseName = "fit_dacVsAdc";
   m_tooFewPoints = false;
   m_noSatData = false;
   
   m_fitMaxRange = 0;
   m_analogueSaturation = m_saturationLevel;
   m_isAnalogueSaturation = false;
   
   m_isProcessed = false;
}


DacVsAdcPeakGraph::~DacVsAdcPeakGraph(void){
   if(m_graph != 0){
      delete m_graph;
      m_graph = 0;
   }
   
   if(m_fit != 0){
      delete m_fit;
      m_fit = 0;
   }
}

void DacVsAdcPeakGraph::Fill(const unsigned int dac,const float adcPeak,const unsigned int peakBin,const float meanPedestal,TH1* signal){
   m_v_dac.push_back(dac);
   m_v_adcPeak.push_back(adcPeak);
   m_v_meanPedestal.push_back(meanPedestal);
   signal->SetDirectory(0);
   m_v_signal.push_back(signal);
   m_v_peakBin.push_back(peakBin);
   
//    std::cout << " id: " << m_coolId.GetIdAsString() << " dac: " << dac << " adcPeak: " << adcPeak << " bin: " << peakBin << " ped: " << meanPedestal << " signal: " << signal << std::endl;
}

void DacVsAdcPeakGraph::Build(void){
   
   ///////////////////////////////////////////
   // First sort the vectors by DAC value
   // I want all vectors organized by smalled
   // to largest DAC value
   ///////////////////////////////////////////
   
   // first make a copy of the dac values
   std::vector<unsigned int> tempDac = m_v_dac;
   
   // organize adcPeak
   VectSortByX<unsigned int,float>(tempDac,m_v_adcPeak);
   
   // organize meanPedestal
   tempDac.clear();
   tempDac = m_v_dac;
   VectSortByX<unsigned int,float>(tempDac,m_v_meanPedestal);
   
   // organize signal
   tempDac.clear();
   tempDac = m_v_dac;
   VectSortByX<unsigned int,TH1*>(tempDac,m_v_signal);
   
   // organize peakBin
   // this time I use m_v_dac so that it is also organized
   tempDac.clear();
   tempDac = m_v_dac;
   VectSortByX<unsigned int,unsigned int>(m_v_dac,m_v_peakBin);
   
   /// fill unsaturated values into vectors
   for(unsigned int i=0;i<m_v_dac.size();++i){
      
      float peakValue = m_v_adcPeak[i];
      unsigned int dac = m_v_dac[i];
      unsigned int peakBin = m_v_peakBin[i];
      float pedestal = m_v_meanPedestal[i];
      
      // if the adc peak is zero, skip this entry
      if(fabs(peakValue) < 0.001) continue;
      
      float saturatedLevel = (float)m_analogueSaturation;
      // if this is a processed signal we must also substract
      // the pedestal to test for saturation
      if(m_isProcessed) saturatedLevel -= pedestal;
      
      // if peak value isn't saturated include in unsat variables
      // Use absolute value of the difference to make sure we are
      // well away from the saturatedLevel. This avoids rounding
      // affects which come with using floats.
      if(peakValue < saturatedLevel && (saturatedLevel-peakValue) > 1.0){
         m_unsat_adcPeak.push_back(peakValue);
         m_unsat_dac.push_back(dac);
         
         m_peakBin.AddEntry(peakBin);
         
      }
   } // end for(m_v_dac)
   
   // fill the graph with unsaturated bits
   FillGraph();
   
   // fit graph for dac to adc conversion
   FitGraph();
   
   /// fill saturated values into vectors
   std::vector<TH1*> sat_signal;
   std::vector<float> sat_pedMean;
   for(unsigned int i=0;i<m_v_dac.size();++i){
      float peakValue = m_v_adcPeak[i];
      unsigned int dac = m_v_dac[i];
      float pedestal = m_v_meanPedestal[i];
      
      // use analogue saturation level determined from Fit
      float saturatedLevel = (float)m_analogueSaturation;
      // if this is a processed signal, must substract pedestal
      // for comparing saturation level
      if(m_isProcessed) saturatedLevel -= pedestal;
      
      // if peak value is saturated, add to sat variables
      // Use absolute value to make sure we are not close to saturation
      // since I'm using float types.
      if(peakValue > saturatedLevel || fabs(peakValue - saturatedLevel) < 1.0){
         m_sat_dac.push_back(dac);
         sat_signal.push_back(m_v_signal[i]);
         sat_pedMean.push_back(pedestal);
         
      }
   }
   
   // make sure there is some saturated entries
   if(m_sat_dac.size() <= 0){
      m_noSatData = true;
      std::cout << "[DacVsAdcPeakGraph::Build] No saturated Data.\n";
   }
   
   /// extrapolate adcPeak for saturated DAC values
   // only if fit exists
   if(!m_tooFewPoints){
      for(unsigned short int i=0;i<m_sat_dac.size();++i){
         unsigned short int estimatedAdcPeak = (unsigned short int)(m_fit->GetParameter(0) + m_fit->GetParameter(1)*(float)m_sat_dac[i]);
         m_sat_adcPeak.push_back(estimatedAdcPeak);
         
//          std::cout << " sat dac: " << m_sat_dac[i] << " adcPeak: " << m_sat_adcPeak[i] << std::endl;
         
//          m_graph->SetPoint(m_graph->GetN(),(float)m_sat_dac[i],m_sat_adcPeak[i]);
      }
   }
   
   // Fill peak value and estimated peak over full sat/unsat ADC range
   // fill unsaturated peak values
   unsigned int numUnsatValues = m_v_dac.size()-m_sat_dac.size();
   for(unsigned int i=0;i<numUnsatValues;++i){
      m_v_ts1_estAdc.push_back((unsigned short int)m_v_adcPeak[i]);
      m_v_ts2_estAdc.push_back((unsigned short int)m_v_adcPeak[i]);
   }
   // fill saturated peak values
   for(unsigned int i=0;i<m_sat_adcPeak.size();++i){
      m_v_ts1_estAdc.push_back((unsigned short int)m_sat_adcPeak[i]);
      m_v_ts2_estAdc.push_back((unsigned short int)m_sat_adcPeak[i]);
   }
   
   /// calculate t_{s-1/2} for the measure meanPeakBin
   for(unsigned int i=0;i<m_v_dac.size();++i){
      unsigned int ts1 = (unsigned int)m_v_signal[i]->GetBinContent(m_peakBin.GetIntegerMean() - 25);
      unsigned int ts2 = (unsigned int)m_v_signal[i]->GetBinContent(m_peakBin.GetIntegerMean() - 50);
      if(m_isProcessed){
         if(ts1 >= m_saturationLevel - (unsigned int)m_v_meanPedestal[i]){
            ts1 = (unsigned int)m_v_signal[i]->GetBinContent(m_peakBin.GetIntegerMean() - 50);
            ts2 = (unsigned int)m_v_signal[i]->GetBinContent(m_peakBin.GetIntegerMean() - 75);
         }
      }
      else{
         if(ts1 >= m_saturationLevel){
            ts1 = (unsigned int)m_v_signal[i]->GetBinContent(m_peakBin.GetIntegerMean() - 50);
            ts2 = (unsigned int)m_v_signal[i]->GetBinContent(m_peakBin.GetIntegerMean() - 75);
         }
      }
      
      m_v_ts1.push_back(ts1);
      m_v_ts2.push_back(ts2);
   }
   
   
   /// Need to delete Cloned signal shape histograms
   for(unsigned int i=0;i<m_v_signal.size();++i){
      delete m_v_signal[i];
      m_v_signal[i] = 0;
   }
   m_v_signal.clear();
}


bool DacVsAdcPeakGraph::FillGraph(void){
   
   // order vectors from smallest to largest x-value
   std::vector<unsigned short int> tempX;
   std::vector<float> tempY;
   tempX = m_unsat_dac;
   tempY = m_unsat_adcPeak;
//    bool goodSort = VectSortByX<unsigned short int,float>(tempX,tempY);
//    if(!goodSort){
//       std::cerr << "[DacVsAdcPeakGraph::FillGraph] Sort Failed.\n";
//       return false;
//    }
   
   // convert vectors to arrays for stupid TGraph
   const unsigned short int max = tempX.size();
   float dac[max],adcPeak[max];
   Vect2array<unsigned short int>(tempX,dac);
   Vect2array<float>(tempY,adcPeak);
   
   m_graph = new TGraph(max,dac,adcPeak);
   m_graph->SetName((GetPlotName(m_s_graphBaseName,m_coolId)).c_str());
   m_graph->SetTitle((GetPlotTitle(m_s_graphBaseTitle,m_coolId)).c_str());
   m_graph->GetXaxis()->SetTitle(m_s_xAxisTitle.c_str());
   m_graph->GetYaxis()->SetTitle(m_s_yAxisTitle.c_str());
   m_graph->SetMarkerStyle(20);
   m_graph->SetMarkerColor(kBlue);
   m_graph->SetMaximum(1030);
   m_graph->SetMinimum(0);
   
   return true;
}

bool DacVsAdcPeakGraph::FitGraph(void){
   
   // if the graph only has one entry we cannot fit it.
   const unsigned int N = m_graph->GetN();
   if(N <= 1){
      m_tooFewPoints = true;
      return false;
   }
   
   double *x = m_graph->GetX();
   double *y = m_graph->GetY();
   
   // Fit graph with line to extrapolate what the ADC value would be for saturated DACs
   m_fit = new TF1((GetPlotName(m_s_fitBaseName,m_coolId)).c_str(),"pol1",x[0],x[N-1]);
   m_fit->SetLineColor(kRed);
   m_graph->Fit(m_fit,"qunobr");
   
   float chisq = m_fit->GetNDF() == 0 ? 0 : (m_fit->GetChisquare()/m_fit->GetNDF());
   
   
   
//    TCanvas can("can","can",0,0,800,600);
//    
//    m_graph->Draw("ap");
//    m_fit->Draw("same");
//    can.Update();
//    std::cout << " chisq: " << chisq << std::endl;
//    std::cin.get();
   
   // if there are more than just 2 points
   // try fitting one less point at the top of the x-range
   // if the chisquare improves significantly set the
   // analogue saturation level and interate again until
   // the chi square doesn't change too much.
   if(N > 2){
      
      // keep copy of last fit so it can be used if
      // chi square doesn't change with new fit.
      TF1 *lastFit = m_fit;
      float lastChisq = chisq;
      for(unsigned int i=N-1;i>2;--i){
         
         // allow for duplicate dac values
         if(x[i-1] == x[i]) continue;
         
         TF1 *tempFit = new TF1("tempFit","pol1",x[0],x[i-1]);
         
         m_graph->Fit(tempFit,"qunobr");
         
         chisq = tempFit->GetNDF() == 0 ? 0 : (tempFit->GetChisquare()/tempFit->GetNDF());
         double dChisq = fabs(chisq-lastChisq);
         
         // require chisq to be below a certain value
         // and that it doesn't change too much from the
         // last fit
         bool chisqCuts = (chisq < 250.0 && dChisq < 150.0);
         
         
//          m_graph->Draw("ap");
//          tempFit->Draw("same");
//          can.Update();
//          std::cout << " chisq: " << chisq << " dChisq: " << dChisq << std::endl;
//          std::cin.get();
         
         
         
         if( !chisqCuts ){
            // if things are still changing delete last fit, keep current fit
            // and repeat loop.
            delete lastFit;
            lastFit = tempFit;
            lastChisq = chisq;
            m_fit = tempFit;
            
            // set the analogue saturation
            m_isAnalogueSaturation = true;
            m_analogueSaturation = (unsigned short int)y[i-1];
            
//             std::cout << " things changed\n";
         }
         // if things did not change alot
         // then we keep the last fit and exit the loop
         else{
            m_fit = lastFit;
            delete tempFit;
            tempFit = 0;
            
//             std::cout << " no change.\n";
            
            break;
         }
      }// end for(i)
      
   }// end if(N>2)
   
   // add pedestal if signal as analogue saturation and is processed
   if(m_isProcessed && m_isAnalogueSaturation){
      m_analogueSaturation += (unsigned int)m_v_meanPedestal[0];
      // analogue saturation cannot be larger than saturationLevel(1023)
      if(m_analogueSaturation > m_saturationLevel)
         m_analogueSaturation = m_saturationLevel;
   }
   
   return true;
}


std::string DacVsAdcPeakGraph::GetPlotName(const std::string base,const L1CaloChannelId coolId) const{
   std::string output = base;
   output += "_";
   output += coolId.GetIdAsString();
   return output;
}

std::string DacVsAdcPeakGraph::GetPlotTitle(const std::string base,const L1CaloChannelId coolId) const{
   std::string output = base;
   output += " 0x";
   output += coolId.GetIdAsString();
   return output;
}

