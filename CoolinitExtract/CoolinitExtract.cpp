
#include "CoolinitExtract.h"

#include <sstream>

CoolinitExtract::CoolinitExtract(std::string inputFilename,std::string outputFilename){
   
   // name of attribute interested in
   m_s_attributeName = "FullDelayData";
   
   m_inputFilename = inputFilename;
   
   std::cout << "Opening: " << m_inputFilename << std::endl;
   
   m_inputFile.open(m_inputFilename.c_str());
   
   m_s_separator = ",";
   m_s_subseparator = ":";
   
   while(!m_inputFile.eof()){
      
      char line[1000];
      
      m_inputFile.getline(line,1000);
      
      std::string sline = line;
//       std::cout << sline << std::endl;
      
      // extract folder name
      unsigned int columnNumber = sline.find(m_s_separator);
      unsigned int lastColumnNumber = 0;
      std::string substr = sline.substr(lastColumnNumber,columnNumber-lastColumnNumber);
      
      m_folder.push_back(substr);
      
      lastColumnNumber = columnNumber + 1;
      
      // extract cool ID
      columnNumber = sline.find(m_s_separator,lastColumnNumber);
      
      substr = sline.substr(lastColumnNumber,columnNumber-lastColumnNumber);
      
      std::stringstream ss;
      ss << substr;
      unsigned int id = 0;
      ss >> std::hex >> id >> std::dec;
      m_id.push_back(id);
      
      lastColumnNumber = columnNumber + 1;
      
//       std::cout << m_folder.back() << " " << std::hex << m_id.back() << std::dec << " ";
      
      // extract attributes
      bool endOfLine = false;
      while(!endOfLine){
         // get the column number of the next separator
         columnNumber = sline.find(m_s_separator,lastColumnNumber);
         if(columnNumber == std::string::npos){
            endOfLine = true;
         }
         
         // this substr now contains all the info for this attribute and
         // they need to be extracted
         substr = sline.substr(lastColumnNumber,columnNumber-lastColumnNumber);
         
//          std::cout << substr << " ";
         
         // Extract attribute name
         unsigned short int subColumnNumber = substr.find(m_s_subseparator);
         unsigned short int lastSubColumnNumber = 0;
         std::string subsubstr = substr.substr(lastSubColumnNumber,subColumnNumber-lastSubColumnNumber);
         std::string attrName = subsubstr;
         
         lastSubColumnNumber = subColumnNumber + 1;
         
         // Extract attribute type
         subColumnNumber = substr.find(m_s_subseparator,lastSubColumnNumber);
         subsubstr = substr.substr(lastSubColumnNumber,subColumnNumber-lastSubColumnNumber);
         std::string attrType = subsubstr;
         
         lastSubColumnNumber = subColumnNumber + 1;
         
         // Extract attribute value
         subsubstr = substr.substr(lastSubColumnNumber,substr.size()-lastSubColumnNumber);
         
         std::stringstream ss;
         ss << subsubstr;
         unsigned int attrValue = 0;
         ss >> std::dec >> attrValue;
         
         
         lastColumnNumber = columnNumber + 1;
         
         if(attrName.compare(m_s_attributeName) == 0){
            m_attrName.push_back(attrName);
            m_attrType.push_back(attrType);
            m_attrValue.push_back(attrValue);
         }
         
         
      }// end while(eol)
//       std::cout << std::endl;
//       std::cin.get();
      
   }// end while(eof)
   
   m_inputFile.close();
   
   
   m_outputFilename = outputFilename;
   
   std::cout << "Opening: " << m_outputFilename << std::endl;
   
   m_outputFile.open(m_outputFilename.c_str());
   
   for(unsigned int i=0;i<m_id.size();++i){
      if(m_id[i] == 0 && m_attrValue[i] == 0) continue;
      if(i>0) m_outputFile << std::endl;
      m_outputFile << std::hex << m_id[i] << std::dec << "\t" << m_attrValue[i];
      
   }
   
   m_outputFile.close();
   
   
}




