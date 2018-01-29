
#include "CombinedCanvas.h"

CombinedCanvas::CombinedCanvas(L1CaloChannelId id):
   m_id(id)
{
   m_nameBase = "canvas";
   m_titleBase = "Canvas";
   
   m_canvas = 0;
   
   m_colorCounter = 1;
}

CombinedCanvas::~CombinedCanvas(void){
   if(m_canvas != 0){
      delete m_canvas;
      m_canvas = 0;
   }
}

void CombinedCanvas::AddSignalShape(unsigned int runNumber,TH1* signalShape){
   
   m_runNumbers.push_back(runNumber);
   std::string drawOpts;
   if(m_canvas == 0){
      // Create new Canvas for this channel
      std::string name = m_nameBase + "_" + m_id.GetIdAsString();
      std::string title = m_titleBase + " " + m_id.GetIdAsString();
      
      m_canvas = new TCanvas(name.c_str(),title.c_str(),0,0,800,600);
      m_canvas->SetBatch(1);
      drawOpts = "";
   }
   else{
      drawOpts = "same";
   }
   
   
   // draw plot on canvas
   m_canvas->cd();
   signalShape->SetMinimum(-10);
   signalShape->SetMaximum(1035);
   signalShape->SetMarkerStyle(20);
   signalShape->SetMarkerColor(m_colorCounter);
   signalShape->DrawCopy(drawOpts.c_str());
   
   m_colorCounter++;
   if(m_colorCounter == 10) m_colorCounter = 29;
}
