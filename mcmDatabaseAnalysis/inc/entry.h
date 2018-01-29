
#include <string>
#include <sstream>
#include <vector>
#include <ctime>
#include <iostream>
#include <cstdio>


class Entry{
public:
	Entry(std::string line);
	~Entry(void){};
	
	std::vector<unsigned int>* GetOldCoolId(void){return &m_oldCoolId;};
	std::vector<unsigned int>* GetNewCoolId(void){return &m_newCoolId;};
	
	time_t GetEntryTime(void){return m_entryTime;};
	
	unsigned int GetOldCrate(void){return m_oldCrate;};
	unsigned int GetOldPpm(void){return m_oldPpm;};
	unsigned int GetOldMcm(void){return m_oldMcm;};
	unsigned int GetNumberOldChannels(void){return m_oldChannel.size();};
	unsigned int GetOldChannel(unsigned int entry){return m_oldChannel[entry];};
	
	unsigned int GetNewCrate(void){return m_newCrate;};
	unsigned int GetNewPpm(void){return m_newPpm;};
	unsigned int GetNewMcm(void){return m_newMcm;};
	unsigned int GetNumberNewChannels(void){return m_newChannel.size();};
	unsigned int GetNewChannel(unsigned int entry){return m_newChannel[entry];};
	
	void PrintEntry(void);
	
	unsigned int GetNumberOfProblems(void){return m_problemList.size();};
	unsigned int GetProblemCode(unsigned int entry){return m_problemList[entry];};
	
	std::string GetSwappedItem(void){return m_swappedItem;};
	
private:
	std::string m_inputLine;
	
	char m_placeHolder;
	
	time_t m_entryTime;
	
	std::string m_swappedItem;
	
	unsigned int m_oldCrate;
	unsigned int m_oldPpm;
	unsigned int m_oldMcm;
	std::vector<unsigned int> m_oldChannel;
	std::vector<unsigned int> m_oldCoolId;
	
	unsigned int m_oldPpmSerial;
	unsigned int m_oldMcmSerial;
	
	unsigned int m_newCrate;
	unsigned int m_newPpm;
	unsigned int m_newMcm;
	std::vector<unsigned int> m_newChannel;
	std::vector<unsigned int> m_newCoolId;
	
	unsigned int m_newPpmSerial;
	unsigned int m_newMcmSerial;
	
	
	std::vector<unsigned int> m_problemList;
	
};
