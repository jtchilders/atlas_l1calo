
#include "extractTxt.h"

ExtractTxt::ExtractTxt(std::string filename){
	m_filename = filename;
	
	std::ifstream inFile(m_filename.c_str());
	if(!inFile){
		std::cerr << "Error opening file.\n";
		return;
	}
	
	while(!inFile.eof()){
		
		char cline[500];
		inFile.getline(cline,500);
		if(!(48 <= (int)cline[0] && (int)cline[0] <= 57)) continue;
		
		std::string sline = cline;
		
		Entry* temp = new Entry(sline);
		
		m_entries.push_back(temp);
	}
	
	
}

ExtractTxt::~ExtractTxt(void){
	for(int i=0;i<m_entries.size();i++){
		delete m_entries[i];
	}
	
}



