#ifndef COOLATTRIBUTESINGLET_H
#define COOLATTRIBUTESINGLET_H

#include <ctime>


template <class dataType = uint>
class coolAttributeSinglet{
public:
	coolAttributeSinglet(){};
	coolAttributeSinglet(dataType a,time_t start, time_t end)
		{m_attr = a;m_startIOV=start;m_endIOV=end;};
	~coolAttributeSinglet(){};
	
	dataType GetValue(void){return m_attr;};
	void SetValue(dataType attr){m_attr = attr;};
	
	time_t GetStartIOV(void){return m_startIOV;};
	void SetStartIOV(time_t time){m_startIOV = time;};
	
	time_t GetEndIOV(void){return m_endIOV;};
	void SetEndIOV(time_t time){m_endIOV = time;};
	
	bool IsDisabled(void){return m_disabled;};
	void SetDisabled(bool setting){m_disabled = setting;};
private:
	
	dataType m_attr;
	time_t   m_startIOV;
	time_t   m_endIOV;
	bool     m_disabled;
	
};


#endif

