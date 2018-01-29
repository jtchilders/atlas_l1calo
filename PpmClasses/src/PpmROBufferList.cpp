#include "PpmROBufferList.h"


PpmROBufferList::PpmROBufferList(const unsigned int numTimeSlices): m_numTimeSlices(numTimeSlices){
	
	m_chanToROB = new map<unsigned int,PpmROBuffer*>;
}



void PpmROBufferList::SetValue(const unsigned int
chanId,const unsigned int step,const unsigned int
slice,const unsigned int value){
	
	map<unsigned int,PpmROBuffer*>::iterator itr = m_chanToROB->find(chanId);
	
	if(itr == m_chanToROB->end()){ // didn't find channel ID so create a new one
		(*m_chanToROB)[chanId] = new PpmROBuffer(m_numTimeSlices);
		(*m_chanToROB)[chanId]->SetValue(step,slice,value);
		
	}
	else
		itr->second->SetValue(step,slice,value);
	
	
}

PpmROBuffer* PpmROBufferList::GetPpmROBuffer(const unsigned int chanId){
	
	map<unsigned int,PpmROBuffer*>::iterator itr = m_chanToROB->find(chanId);
	
	if(itr == m_chanToROB->end()){ // didn't find channel ID
		return (PpmROBuffer*)0;
	}
	else
		return itr->second;
	
	return (PpmROBuffer*)0;
}
