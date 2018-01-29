

#include "entry.h"

Entry::Entry(std::string line):
	m_inputLine(line)
{
	
	m_entryTime    = 0;
	m_oldCrate     = 0;
	m_oldPpm       = 0;
	m_oldMcm       = 0;
	m_oldPpmSerial = 0;
	m_oldMcmSerial = 0;
	m_newCrate     = 0;
	m_newPpm       = 0;
	m_newMcm       = 0;
	m_newPpmSerial = 0;
	m_newMcmSerial = 0;
	
	
	std::stringstream inputString(std::stringstream::in | std::stringstream::out);
	inputString << line;
	
	
	m_placeHolder = '*';
	int counter=0;
	while(!inputString.eof()){
		
		std::string temp;
		
		inputString >> temp;
		//std::cerr << "-> " << temp << std::endl;
		
		if(temp.find(m_placeHolder) != std::string::npos){
			counter++;
			continue;
		}
		
		// Extract the time
		switch(counter)
		{
		case 0:  // Time
		{
			std::string sday,smonth,syear;
			
			syear = temp.substr(0,4);
			smonth = temp.substr(5,2);
			sday = temp.substr(8,2);
			
			int day = atoi(sday.c_str()),month = atoi(smonth.c_str()),year = atoi(syear.c_str());
			
			time_t rawtime;
			time(&rawtime);
			struct tm tm_temp;
			tm_temp = *localtime(&rawtime);
			
			tm_temp.tm_sec = 0;
			tm_temp.tm_min = 0;
			tm_temp.tm_hour = 0;
			tm_temp.tm_mday = day;
			tm_temp.tm_mon = month-1;
			tm_temp.tm_year = year - 1900;
			
			m_entryTime = mktime(&tm_temp);
			
			break;
		}
		case 1:  // swapped item MCM/PPM
			m_swappedItem  = temp;
			break;
		case 2:
			m_oldCrate     = atoi(temp.c_str());
			break;
		case 3:
			m_oldPpm       = atoi(temp.c_str());
			break;
		case 4:
			m_oldMcm       = atoi(temp.c_str());
			break;
		case 5: // channel
		{
			for(int i=0;i<temp.size();i++){
				if(temp[i] == ',' || temp[i] == '\"') continue;
				
				m_oldChannel.push_back(atoi(&temp[i]));
			}
			//std::cerr << m_oldChannel.size() << std::endl;
			
			break;
		}
		case 6:
			m_oldPpmSerial = atoi(temp.c_str());
			break;
		case 7:
			m_oldMcmSerial = atoi(temp.c_str());
			break;
		case 8:
			m_newCrate     = atoi(temp.c_str());
			break;
		case 9:
			m_newPpm       = atoi(temp.c_str());
			break;
		case 10:
			m_newMcm       = atoi(temp.c_str());
			break;
		case 11: // channel
			for(int i=0;i<temp.size();i++){
				if(temp[i] == ',' || temp[i] == '\"') continue;
				
				m_newChannel.push_back(atoi(&temp[i]));
			}
			//std::cerr << m_newChannel.size() << std::endl;
			
			break;
		case 12:
			m_newPpmSerial = atoi(temp.c_str());
			break;
		case 13:
			m_newMcmSerial = atoi(temp.c_str());
			break;
		case 14: // problem code
		{
			int stringPosition=0,lastFind=0;
			
			// determine if there are quotes, which means multiple codes
			stringPosition = temp.find('\"');
			if(stringPosition == std::string::npos){
				m_problemList.push_back(atoi(temp.c_str()));
			}
			else{
				int nextComma = 0;
				for(int currentReadPosition=1;currentReadPosition<temp.size()-1;){
					nextComma = temp.find(',',currentReadPosition);
					if(nextComma == std::string::npos){
						std::string substring = temp.substr(currentReadPosition,temp.size() - 1 - currentReadPosition);
						m_problemList.push_back(atoi(substring.c_str()));
						break;
					}
					else{
						std::string substring = temp.substr(currentReadPosition,nextComma-currentReadPosition);
						m_problemList.push_back(atoi(substring.c_str()));
						currentReadPosition = nextComma+1;
					}
					
					
				}
				
			}
			
			break;
		}
		default:
			break;
		}
		
		counter++;
		
	}
	
	for(int i=0;i<m_oldChannel.size();i++){
		unsigned int coolId = ( (0xff & m_oldCrate) << 24) | ( 0x1 << 20) | ( (0xff & m_oldPpm)  << 16) | ( (0xff & m_oldMcm) << 8) | (0xff & m_oldChannel[i]);
		m_oldCoolId.push_back(coolId);
		
	}
	
	for(int i=0;i<m_newChannel.size();i++){
		unsigned int coolId = ( (0xff & m_newCrate) << 24) | ( 0x1 << 20) | ( (0xff & m_newPpm)  << 16) | ( (0xff & m_newMcm) << 8) | (0xff & m_newChannel[i]);
		m_newCoolId.push_back(coolId);
		
	}
	
}


void Entry::PrintEntry(void){
	std::cerr << "Date: " << ctime(&m_entryTime) << std::endl;
	std::cerr << "   Old Address: " << m_oldCrate << "-" << m_oldPpm << "-" << m_oldMcm << "-";
	if(m_oldChannel.size() > 1)
		std::cerr << "{" << m_oldChannel[0];
	else
		std::cerr << m_oldChannel[0];
	for(int i = 1;i< m_oldChannel.size(); i++)
		std::cerr << "," << m_oldChannel[i];
	if(m_oldChannel.size() > 1)
		std::cerr << "}\n";
	else
		std::cerr << std::endl;
	std::cerr << "   Old PPM Serial: " << m_oldPpmSerial << " Old MCM Serial: " << m_oldMcmSerial << std::endl;
	
	std::cerr << "   New Address: " << m_newCrate << "-" << m_newPpm << "-" << m_newMcm << std::endl;
	std::cerr << "   New PPM Serial: " << m_newPpmSerial << " New MCM Serial: " << m_newMcmSerial << std::endl;
	
	
}
