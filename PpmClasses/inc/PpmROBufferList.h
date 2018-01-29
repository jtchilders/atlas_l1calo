#ifndef __PPMROBUFFERLIST_H__
#define __PPMROBUFFERLIST_H__


#include <iostream>
#include <map>

#include "PpmROBuffer.h"

using namespace std;

class PpmROBufferList{
public:
	PpmROBufferList(const unsigned int numTimeSlices);
	~PpmROBufferList(void){delete m_chanToROB;m_chanToROB=0;};
	
	void SetValue(const unsigned int chanId,const unsigned
int step,const unsigned int slice,const unsigned int value);
	
	PpmROBuffer* GetPpmROBuffer(const unsigned int chanId);
	
private:
	map<unsigned int,PpmROBuffer*>* m_chanToROB; // < Channel COOL ID , Readout Buffer obj >
	
	const unsigned int m_numTimeSlices;
	
};



#endif


