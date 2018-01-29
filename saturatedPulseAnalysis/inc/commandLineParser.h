#ifndef COMMANDLINEPARSER_H
#define COMMANDLINEPARSER_H

#include <iostream>
#include <vector>

class CLParse{
public:
   CLParse(const int argc,char** const argv,std::string progDescr = "");
   
   std::vector<std::string> getFilenames(){return m_inputFilenames;};
   std::vector<unsigned int> getRunNumbers(){return m_inputRunNumbers;};
   
   std::vector<unsigned int> getTileDacValues(){return m_inputTileDacValues;};
   
   std::vector<unsigned int> getLArgFcalDacValues(){return m_inputLArgFcalDacValues;};
   std::vector<unsigned int> getLArgBarrelDacValues(){return m_inputLArgBarrelDacValues;};
   std::vector<unsigned int> getLArgEmecDacValues(){return m_inputLArgEmecDacValues;};
   std::vector<unsigned int> getLArgHecDacValues(){return m_inputLArgHecDacValues;};
   
   bool doTile(void){return m_doTile;};
   bool doLArg(void){return m_doLArg;};
   
   bool errorDuringSetup(void){return m_errorDuringSetup;};
   
private:
   
   
   std::vector<std::string>  m_inputFilenames;
   std::vector<unsigned int> m_inputRunNumbers;
   
   std::vector<unsigned int> m_inputTileDacValues;
   
   std::vector<unsigned int> m_inputLArgFcalDacValues;
   std::vector<unsigned int> m_inputLArgBarrelDacValues;
   std::vector<unsigned int> m_inputLArgEmecDacValues;
   std::vector<unsigned int> m_inputLArgHecDacValues;
   
   
   bool m_doTile;
   bool m_doLArg;
   
   bool m_errorDuringSetup;
   
   
};


#endif

