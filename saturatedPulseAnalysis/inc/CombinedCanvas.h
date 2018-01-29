#ifndef COMBINEDCANVAS_H
#define COMBINEDCANVAS_H

#include <string>

#include "TCanvas.h"
#include "TH1.h"

#include "L1CaloChannelId.h"

class CombinedCanvas{
public:
   CombinedCanvas(L1CaloChannelId id);
   ~CombinedCanvas(void);
   
   void SetNameBase(std::string name){m_nameBase = name;};
   void SetTitleBase(std::string title){m_titleBase = title;};
   
   void AddSignalShape(unsigned int runNumber,TH1* signalShape);
   
   TCanvas* GetCanvas(void){return m_canvas;};
   
   std::vector<unsigned short int>* GetRunNumbers(void){return &m_runNumbers;};
   
private:
   L1CaloChannelId m_id;
   
   TCanvas *m_canvas;
   
   std::string m_nameBase;
   std::string m_titleBase;
   
   std::vector<unsigned short int> m_runNumbers;
   unsigned short int m_colorCounter;
   
};


#endif
