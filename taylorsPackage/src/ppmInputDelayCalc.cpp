#include "taylorsPackage/ppmInputDelayCalc.h"

PpmInputDelayCalc::PpmInputDelayCalc(void): 
	m_FifoLength(16),m_MaxPhos4(25){
	
	m_inBcidNegEdge = 0; // pos Edge by default
	m_inDataNegEdge = 0; // pos Edge by default
	
	m_phos4delay = 0; // no delay by default
	
	m_fifoOffset = 0; // no offset by default
	m_syncDelayData = 0; // 1 BC delay by default
	m_syncDelayBcid = 0; // 1 BC delay by default
	
	m_delayIndex = 0; // overall delay offset in ns
	
}


void PpmInputDelayCalc::setDelayIndex(unsigned int index){
	
	m_delayIndex = index;
	
	m_syncDelayData = (unsigned int)((double)m_delayIndex/(double)m_MaxPhos4);
	m_syncDelayBcid = m_syncDelayBcid;
	
	m_phos4delay = (unsigned int)((((double)m_delayIndex/(double)m_MaxPhos4) - m_syncDelayData)*m_MaxPhos4);
	
	m_inBcidNegEdge = getNegEdge(m_phos4delay);
	m_inDataNegEdge = getNegEdge(m_phos4delay);
	
	
}

void PpmInputDelayCalc::setPhos4delay(unsigned int delay){
	
	m_phos4delay = delay;
	
	m_inBcidNegEdge = getNegEdge(m_phos4delay);
	m_inDataNegEdge = getNegEdge(m_phos4delay);
	
	if(m_inDataNegEdge == 0)
		m_fifoOffset = 0;
	if(m_inDataNegEdge == 1)
		m_fifoOffset = 1;
	
	// can't calculate delay index or other delays
	m_delayIndex = 0;
	m_syncDelayData = 0;
	m_syncDelayBcid = 0;
}

unsigned int PpmInputDelayCalc::getNegEdge(unsigned int phos4delay){
	
	if( phos4delay <= 9 ){
		return 1;
	}
	else if( 10 <= phos4delay && phos4delay <= 21){
		return 0;
	}
	else if( 21 <= phos4delay && phos4delay < m_MaxPhos4){
		return 1;
	}
	else{
		std::cerr << "[PpmInputDelayCalc::setNegEdge] Error: phos4 delay out of range, " << phos4delay << " is not within 0 to " << m_MaxPhos4 << ".\n";
		return 0;
	}
	
	return 0;
}
