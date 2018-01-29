#include "ChannelRunEntry.h"

ChannelRunEntry::ChannelRunEntry(const ChannelRunEntry &entry){
   ClearEntry();
   
   SetRunNumber(entry.GetRunNumber());
   
   SetFullDelayData(entry.GetFullDelayData());
   SetNewFullDelayData(entry.GetNewFullDelayData());
   
   SetPedestalMean(entry.GetPedestalMean());
   SetPedestalSigma(entry.GetPedestalSigma());
   
   SetRawSignalShape(entry.GetRawSignalShape());
   SetRawPeakBin(entry.GetRawPeakBin());
   SetRawPeakValue(entry.GetRawPeakValue());
   
   if(GetRawSignalShape() != 0 && GetRawPeakBin() != 0){
      ExtractRawSlice12();
   }
   
   SetProcessedSignalShape(entry.GetProcessedSignalShape());
   SetProcessedPeakBin(entry.GetProcessedPeakBin());
   SetProcessedPeakValue(entry.GetProcessedPeakValue());
   
   if(GetProcessedSignalShape() != 0 && GetProcessedPeakBin() != 0){
      ExtractProcessedSlice12();
   }
   
   SetRisingSlopeMean(entry.GetRisingSlopeMean());
   SetRisingSlopeSigma(entry.GetRisingSlopeSigma());
   
   SetIsProcessed(entry.GetIsProcessed());
   
   SetCaloDacValue(entry.GetCaloDacValue());
}

void ChannelRunEntry::ClearEntry(void){
   SetRunNumber(0);
   SetFullDelayData(0);
   SetNewFullDelayData(0);
   SetPedestalMean(0.0);
   SetPedestalSigma(0.0);
   m_rawSignalShape = 0;
   SetRawPeakBin(0);
   SetRawPeakValue(0.0);
   m_processedSignalShape = 0;
   SetProcessedPeakBin(0);
   SetProcessedPeakValue(0.0);
   SetRisingSlopeMean(0.0);
   SetRisingSlopeSigma(0.0);
   SetIsProcessed(false);
   SetCaloDacValue(0);
}

void ChannelRunEntry::SetRawSignalShape(TProfile* raw){
   if(raw != 0) {
      m_rawSignalShape = (TProfile*)raw->Clone();
      m_rawSignalShape->SetMarkerStyle(7);
      m_rawSignalShape->SetMaximum(1030);
      m_rawSignalShape->SetMinimum(0);
   }
   else 
      m_rawSignalShape == 0;
}

void ChannelRunEntry::SetProcessedSignalShape(TProfile* processed){
   
   if(processed != 0) {
      m_processedSignalShape = (TProfile*)processed->Clone();
      m_processedSignalShape->SetMarkerStyle(7);
      m_processedSignalShape->SetMaximum(1030);
      m_processedSignalShape->SetMinimum(0);
      
   }
   else 
      m_processedSignalShape == 0;
   
}

void ChannelRunEntry::CalculateEffectivePeakValue(std::vector<float> par, std::vector<float> parError){
   
   // expecting the results from a line
   if(par.size() != 2 && parError.size() != 2){
      std::cerr << "[ChannelRunEntry::CalculateEffectivePeakValue]: Error: Expecting results of a linear fit, so 2 parameters with errors.\n";
      return;
   }
   
   float slope = par[1];
   float dSlope = parError[1];
   float offset = par[0];
   float dOffset = parError[0];
   
   
   m_effectivePeakValue = slope*m_caloDacValue+offset;
   m_effectivePeakError = sqrt( dSlope*dSlope*m_caloDacValue*m_caloDacValue + dOffset*dOffset );
   
}

void ChannelRunEntry::ExtractRawSlice12(void){
   
   m_rawSlice1 = 0; m_rawSlice2 = 0;
   if(m_rawSignalShape->GetBinContent(m_rawPeakBin - m_nsStepsPerBc) < m_minPedestal){
      m_rawSlice1 = m_rawSignalShape->GetBinContent(m_rawPeakBin - m_nsStepsPerBc);
      m_rawSlice2 = m_rawSignalShape->GetBinContent(m_rawPeakBin - m_nsStepsPerBc*2);
   }
   else{
      m_rawSlice1 = m_rawSignalShape->GetBinContent(m_rawPeakBin - m_nsStepsPerBc*2);
      m_rawSlice2 = m_rawSignalShape->GetBinContent(m_rawPeakBin - m_nsStepsPerBc*3);
   }
   
}

void ChannelRunEntry::ExtractProcessedSlice12(void){
   
   m_processedSlice1 = 0; m_processedSlice2 = 0;
   if(m_processedSignalShape->GetBinContent(m_processedPeakBin - m_nsStepsPerBc) < m_minPedestal){
      m_processedSlice1 = m_processedSignalShape->GetBinContent(m_processedPeakBin - m_nsStepsPerBc);
      m_processedSlice2 = m_processedSignalShape->GetBinContent(m_processedPeakBin - m_nsStepsPerBc*2);
   }
   else{
      m_processedSlice1 = m_processedSignalShape->GetBinContent(m_processedPeakBin - m_nsStepsPerBc*2);
      m_processedSlice2 = m_processedSignalShape->GetBinContent(m_processedPeakBin - m_nsStepsPerBc*3);
   }
   
}

