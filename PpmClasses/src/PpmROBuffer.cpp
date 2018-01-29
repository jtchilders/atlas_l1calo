#include "PpmROBuffer.h"

PpmROBuffer::PpmROBuffer(const unsigned int time_slices): m_maxBufferLength(128),m_numTimeSlices(time_slices){
	
	// Counts the number of steps needed (1 step = number of time slices readout)
	// to read out entire ppm buffer of 128
	m_maxSteps = (unsigned int)(m_maxBufferLength/m_numTimeSlices) + 1;
	// we read it out twice
	//m_maxSteps *= 2;
	// set the number of member slots needed in the vector.
	m_maxMemSlots = m_maxSteps*m_numTimeSlices;
	
	// Initialize the vectors to the given length
	m_slotValue.resize(m_maxMemSlots);
	
	m_prof = new TProfile("profile","signal profile",m_maxMemSlots,0,m_maxMemSlots,0,1024);
	
	//cerr << "maxSteps: " << m_maxSteps << " maxMemSlots: " << m_maxMemSlots << endl;
}



