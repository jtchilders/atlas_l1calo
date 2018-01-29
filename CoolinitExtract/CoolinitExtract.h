#ifndef COOLINITEXTRACT_H
#define COOLINITEXTRACT_H

#include <string>
#include <fstream>
#include <vector>
#include <iostream>

class CoolinitExtract{
public:
   CoolinitExtract(std::string inputFilename,std::string outputFilename);
   
private:
   std::string m_inputFilename;
   std::ifstream m_inputFile;
   
   std::string m_outputFilename;
   std::ofstream m_outputFile;
   
   std::string m_s_separator;
   std::string m_s_subseparator;
   
   std::vector<std::string> m_folder;
   std::vector<unsigned int> m_id;
   std::vector<std::string> m_attrName;
   std::vector<std::string> m_attrType;
   std::vector<unsigned int> m_attrValue;
   
   std::string m_s_attributeName;
   
};

#endif

