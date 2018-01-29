
#include "entry.h"
#include <string>
#include <vector>
#include <fstream>


class ExtractTxt{
public:
	ExtractTxt(std::string filename);
	~ExtractTxt(void);
	
	unsigned int GetNumberOfEntries(void){return m_entries.size();};
	Entry* GetEntry(unsigned int entryNumber){return m_entries[entryNumber];};
	
private:
	std::vector<Entry*> m_entries;
	std::string m_filename;
	
	
};


