#include "EstAdcVsAdcGraph.h"

#include "TH1.h"
#include "TProfile.h"
#include "TCanvas.h"

EstAdcVsAdcGraph::EstAdcVsAdcGraph(void){
   Initialize();
}

EstAdcVsAdcGraph::EstAdcVsAdcGraph(L1CaloChannelId id):
   m_coolId(id)
{
   Initialize();
}

void EstAdcVsAdcGraph::Initialize(void){
   m_graph = 0;
   m_s_graphBaseName = "estAdcVsAdc";
   m_s_graphBaseTitle = "Estimated ADC Peak vs. ADC for unsaturated slice";
   m_s_xAxisTitle = "Estimated ADC Peak";
   m_s_yAxisTitle = "Unsaturated Time Slice";
   
   m_dacAxis = 0;
   
   m_fit = 0;
   m_s_fitBaseName = "fit_estAdcVsAdc";
   m_tooFewSatSlices = false;
   m_noSatSlices = false;
   
   m_meanPeakBin = 0;
   
   m_maxFitBound_estAdc = 0;
   m_numberFitPoints = 0;
   
   m_isTs2 = false;
   m_isProcessed = false;
   
   m_meanPedestal = 0.;
   
   m_threshold = 0;
}

EstAdcVsAdcGraph::~EstAdcVsAdcGraph(void){
   if(m_graph != 0){
      delete m_graph;
      m_graph = 0;
   }
   
   if(m_fit != 0){
      delete m_fit;
      m_fit = 0;
   }
   
   if(m_dacAxis != 0){
      delete m_dacAxis;
      m_dacAxis = 0;
   }
}

void EstAdcVsAdcGraph::Build(std::vector<unsigned short int>* estAdcPeak,std::vector<unsigned short int>* 
timeSlice,std::vector<unsigned short int>* dac){
   
   /// Check for consistencies
   if(estAdcPeak->size() == 0 && timeSlice->size() == 0 && dac->size() == 0){
      std::cerr << "[EstAdcVsAdcGraph::FillGraph] No vector entries for 0x" << m_coolId.GetIdAsString() << std::endl;
      return; 
   }
   else if(estAdcPeak->size() == 0){
      std::cerr << "[EstAdcVsAdcGraph::FillGraph] No estAdcPeak entries for 0x" << m_coolId.GetIdAsString() << std::endl;
      return;
   }
   else if(timeSlice->size() == 0){
      std::cerr << "[EstAdcVsAdcGraph::FillGraph] No timeSlice entries for 0x" << m_coolId.GetIdAsString() << std::endl;
      return;
   }
   else if(dac->size() == 0){
      std::cerr << "[EstAdcVsAdcGraph::FillGraph] No dac entries for 0x" << m_coolId.GetIdAsString() << std::endl;
      return;
   }
   
   /// ////////////////////////////////////////
   /// Fill Graph
   /// ////////////////////////////////////////
   
   // want sort vectors vectors so they are ordered
   // from smallest estAdcPeak to largest
   // this makes things easier
   //std::vector<unsigned short int> tempX;
   //std::vector<unsigned short int> tempY;
   //tempX = *estAdcPeak;
   //tempY = *timeSlice;
   //bool goodSort = VectSortByX<unsigned short int,unsigned short int>(tempX,tempY);
   //if(!goodSort){
   //   std::cerr << "[EstAdcVsAdcGraph::FillGraph] Sort Failed. EstAdcPeak size: " << estAdcPeak->size() << "\n";
   //   m_tooFewSatSlices = true;
   //   m_noSatSlices = true;
   //   return;
   //}
   
   FillGraph(*estAdcPeak,*timeSlice);
   
   // Create the DAC axis for showing the DAC values on the plot
   const unsigned int N = m_graph->GetN();
   double *X = m_graph->GetX();
   double *Y = m_graph->GetY();
   const double x1 = X[0];
   const double x2 = X[N-1];
   const double ymax = m_graph->GetYaxis()->GetXmax();
   const double x3 = dac->at(0);
   const double x4 = dac->at(dac->size()-1);
   const int ndiv =  4 + 16*100;
   
   m_dacAxis = new TGaxis(x1,ymax,x2,ymax,x3,x4,ndiv,"-B");
   
   //std::cout << " x1: " << x1 << " x2: " << x2 << " ymax: " << ymax << " x3: " << x3 << " x4: " << x4 << " ndiv: " << ndiv << std::endl;
      
   // if graph only has 1 point there is no use
   // in continuing
   if(m_graph->GetN() <= 1){
      std::cerr << "[EstAdcVsAdcGraph::FillGraph] Graph has too few entries: " << m_graph->GetN() << "\n";
      m_tooFewSatSlices = true;
      m_noSatSlices = true;
      return;
   }
   
   /// ///////////////////////////////////////
   /// Fit Graph
   /// ///////////////////////////////////////
   
   // need to get the boundary for the fit
   // should be located where the discontinuity occurs
   // in the time slice -1/-2 values
   m_maxFitBound_estAdc = 0;
   m_numberFitPoints = 0;
   for(int i=1;i<estAdcPeak->size();++i){
      if((*timeSlice)[i] < (*timeSlice)[i-1]){
         m_maxFitBound_estAdc = (*estAdcPeak)[i-1];
         m_numberFitPoints = i;
         break;
      }
   }
   
   // if no bound was found then fit all the points 
   if(m_maxFitBound_estAdc == 0){
      m_maxFitBound_estAdc = estAdcPeak->back();
      m_numberFitPoints = estAdcPeak->size();
   }
   
   // if the number of fit points is too small
   // then skip the fit
   if(m_numberFitPoints > 1){
      FitGraph();
      
      // calculate intercept with saturation point
      if(!m_isProcessed){ // for raw
         m_threshold = (unsigned short int)(m_fit->GetParameter(0) + m_fit->GetParameter(1)*m_analogueSaturationLevel);
      }
      else{ // for processed need to take zero pedestal into account
         m_threshold = (unsigned short int)(m_fit->GetParameter(0) + m_fit->GetParameter(1)*(m_analogueSaturationLevel-m_meanPedestal));
         m_threshold += (unsigned short int)m_meanPedestal;
      }
   
      // if the threshold is too close to pedestal and this is ts2
      // then just set threshold to zero so that ADC > satLow is always
      // true
      if(m_isTs2 &&  m_threshold < m_meanPedestal+5){
         m_threshold = 0;
      }
      
      // If threshold is greater than 1023 just set it to zero.
      if(m_threshold >= 1023)
         m_threshold = 0;
      
   }
   else{
      if(m_numberFitPoints == 0)
         m_noSatSlices = 0;
      
      m_tooFewSatSlices = true;
      return;
   }
   
   
}


void EstAdcVsAdcGraph::FillGraph(std::vector<unsigned short int>& estAdcPeak,std::vector<unsigned short int>& timeSlice){
   
   const unsigned short int max = estAdcPeak.size();
   float x[max],y[max];
   Vect2array<unsigned short int>(estAdcPeak,x);
   Vect2array<unsigned short int>(timeSlice,y);
   
   
   m_graph = new TGraph(max,x,y);
   m_graph->SetName((GetPlotName(m_s_graphBaseName,m_coolId)).c_str());
   m_graph->SetTitle((GetPlotTitle(m_s_graphBaseTitle,m_coolId)).c_str());
   m_graph->GetXaxis()->SetTitle(m_s_xAxisTitle.c_str());
   m_graph->GetYaxis()->SetTitle(m_s_yAxisTitle.c_str());
   m_graph->SetMarkerStyle(20);
   m_graph->SetMarkerColor(kBlue);
   
}

void EstAdcVsAdcGraph::FitGraph(void){
   
   const unsigned int N = m_graph->GetN();
   double *x = m_graph->GetX();
   double *y = m_graph->GetY();
   
   // Fit graph with line to extrapolate what the ADC value would be for saturated DACs
   m_fit = new TF1((GetPlotName(m_s_fitBaseName,m_coolId)).c_str(),"pol1",x[0],x[N-1]);
   m_fit->SetLineColor(kRed);
   
   m_graph->Fit(m_fit,"qurnob");
   
   float chisq = m_fit->GetNDF() == 0 ? 0 : (m_fit->GetChisquare()/m_fit->GetNDF());
   
   TF1 *lastFit = m_fit;
   float lastChisq = chisq;
   for(unsigned int i=N-1;i>=2;--i){
      // allow for duplicate dac values
      if(x[i-1] == x[i]) continue;
      
      TF1 *tempFit = new TF1("tempFit","pol1",x[0],x[i-1]);
      
      m_graph->Fit(tempFit,"qunobr");
      
      chisq = tempFit->GetNDF() == 0 ? 0 : (tempFit->GetChisquare()/tempFit->GetNDF());
      double dChisq = fabs(chisq-lastChisq);
      
      bool chisqCuts = (chisq < 100.0 && dChisq < 100.0);
      
//       if(m_coolId.GetId() == 0x051e0e01 && m_isTs2)
//       std::cout << " chisq: " << chisq << " dChisq: " << dChisq << std::endl;
      
      if( !chisqCuts){
         // if things are still changing delete last fit, keep current fit
         // and repeat loop.
         delete lastFit;
         lastFit = tempFit;
         lastChisq = chisq;
         m_fit = tempFit;
         //std::cout << " still changing\n";
      }
      // if things did not change alot
      // then we keep the last fit and exit the loop
      else{
         m_fit = lastFit;
         delete tempFit;
         tempFit = 0;
         //std::cout << " keeping last fit.\n\n";
         break;
      }
   }// end for(i)
   
}


std::string EstAdcVsAdcGraph::GetPlotName(const std::string base,const L1CaloChannelId coolId) const{
   std::string output = base;
   output += "_";
   output += coolId.GetIdAsString();
   return output;
}

std::string EstAdcVsAdcGraph::GetPlotTitle(const std::string base,const L1CaloChannelId coolId) const{
   std::string output = base;
   output += " 0x";
   output += coolId.GetIdAsString();
   return output;
}

