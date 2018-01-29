#ifndef PPMINPUTDELAYCALC_H
#define PPMINPUTDELAYCALC_H

#include <iostream>

class PpmInputDelayCalc{
public:
	PpmInputDelayCalc();
	~PpmInputDelayCalc(){};
	
	void setDelayIndex(unsigned int index);
	unsigned int getDelayIndex(void){return m_delayIndex;};
	
	void setPhos4delay(unsigned int delay);
	unsigned int getPhos4delay(void){return m_phos4delay;};
	
	unsigned int getInBcidNegEdge(void){return m_inBcidNegEdge;};
	unsigned int getInDataNegEdge(void){return m_inDataNegEdge;};
	
	unsigned int getFifoOffset(void){return m_fifoOffset;};
	unsigned int getSyncDelayBcid(void){return m_syncDelayBcid;};
	unsigned int getSyncDelayData(void){return m_syncDelayData;};
	
	
private:
	
	unsigned int		m_inBcidNegEdge;
	unsigned int		m_inDataNegEdge;
	
	unsigned int		m_phos4delay;
	
	unsigned int		m_fifoOffset;
	unsigned int		m_syncDelayData;
	unsigned int		m_syncDelayBcid;
	
	unsigned int		m_delayIndex; // number in ns between 0 & (m_FifoLength*m_MaxPhos4)
	
	const unsigned int	m_FifoLength;
	const unsigned int	m_MaxPhos4;
	
	unsigned int getNegEdge(unsigned int phos4delay);
};




#endif

