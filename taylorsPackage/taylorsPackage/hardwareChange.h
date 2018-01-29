#ifndef HARDWARECHANGE_H
#define HARDWARECHANGE_H

#include <ctime>

class HardwareChange{
public:
	HardwareChange(){};
	~HardwareChange(){};
	
	unsigned int GetCoolId(void){return m_coolId;};
	void SetCoolId(unsigned int id){m_coolId = id;};
	
	time_t GetChangeTime(void){return m_changeTime;};
	void SetChangeTime(time_t time){m_changeTime=time;};
	void SetChangeTime(unsigned int yr,unsigned int mon,unsigned int day,
	                   unsigned int hr,unsigned int min,unsigned int sec){
	     struct tm temp; temp.tm_sec=sec;temp.tm_min=min;temp.tm_hour=hr;
	     temp.tm_mday=day;temp.tm_mon=mon-1;temp.tm_year=yr-1900;
	     m_changeTime=mktime(&temp);};
	
private:
	unsigned int m_coolId;
	time_t       m_changeTime;
	
};





#endif


