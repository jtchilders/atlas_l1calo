#ifndef _SCOPEFILE_H_
#define _SCOPEFILE_H_

#include <string>

#include <TGraph.h>
#include <TF1.h>
#include <TProfile.h>

class ScopeFile{
public:
   ScopeFile(std::string filename,std::string name,std::string title);
   ~ScopeFile(void);
   
   TGraph* getGraph(void) const {return m_graph;};
   
   TF1* getFit(void) const {return m_gausFit;};
   
   TProfile* getProfile(void) const {return m_prof;};
   
   void Draw(char* options){m_graph->Draw(options);};
   
   float getMaxVoltageInMilliVolts(void) const {return m_maxVoltageInMilliVolts;};
   float getTimeOfMaxVoltageInNanoSeconds(void) const {return m_timeOfMaxVoltageInNanoSeconds;};
   
private:
   TGraph *m_graph;
   TF1 *m_gausFit;
   TProfile *m_prof;
   
   float m_maxVoltageInMilliVolts;
   float m_timeOfMaxVoltageInNanoSeconds;
   
};

#endif
