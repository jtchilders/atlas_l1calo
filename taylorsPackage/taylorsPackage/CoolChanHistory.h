#ifndef COOLHISTORY_H
#define COOLHISTORY_H


#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>
#include <map>
#include <cmath>
#include <fstream>

#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TROOT.h>
#include <TSystem.h>
#include <TError.h>
#endif

#include "TH1.h"
#include "TH1I.h"
#include "TH1S.h"
#include "TH1C.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TDatime.h"
#include "TTimeStamp.h"
#include "TStyle.h"
#include "TFile.h"
#include "TList.h"
#include "TKey.h"
#include "TList.h"
#include "TObject.h"
#include "TCanvas.h"

#include "coolL1Calo/CoolChannelId.h"
#include "coolL1Calo/CoolAccess.h"
#include "infraL1Calo/L1CaloModuleType.h"
#include "ppmMonitoring/PixelMap.h"
#include "channelMappings/L1CaloChannelMap.h"
#include "taylorsPackage/coolAttributeCollection.h"

#include "CoolKernel/IFolder.h"
#include "CoolKernel/IObject.h"
#include "CoolKernel/IObjectIterator.h"
#include "CoolKernel/ValidityKey.h"
#include "CoolKernel/ChannelSelection.h"
#include "CoolKernel/ChannelId.h"
#include "CoolKernel/StorageType.h"
#include "CoralBase/Exception.h"



class CoolChanHistory{
public:
	CoolChanHistory();
	~CoolChanHistory();
	
	void Init(void);
	
	void setAttributeList(std::vector<std::string>& attrList);
	std::vector<std::string>* getAttributeList(void){return &m_attrNames;};
	
	void setFolderName(std::string folderName){m_folderStr=folderName;};
	std::string* getFolderName(void){return &m_folderStr;};
	
	void setStartTime(time_t start){m_start = start;};
	void setStartTime(uint yr,uint mon,uint day,uint hr,uint min,uint sec);
	time_t getStartTime(void){return m_start;};
	
	void setEndTime(time_t end){m_end = end;};
	void setEndTime(uint yr,uint mon,uint day,uint hr,uint min,uint sec);
	time_t getEndTime(void){return m_end;};
	
	int openDb(void);
	int openFolder(void);
	
	int fillAttrCollection(uint coolId); // fills attribute history for given coolId
	
	void getAttrStatsA(std::string attrName,double& mean,double& sigma);
	void getAttrStatsB(std::vector<double>& meanOfMeans,
	std::vector<double>& sigmaOfMeans,std::vector<double>& meanOfSigmas,
	std::vector<double>& sigmaOfSigmas);
	
	void errorCheckHistograms(void);
	
	void OmitDisabledPpmChannels(bool setting){m_omitDisabled = setting;};
	void OmitUnusedPpmChannels(bool setting){m_omitUnusedPpms = setting;};
	
	void fillSummaryPlots(void);
	
	void printToFile(void);
	
private:
	
	
	CoolAccess* 			m_coolDb;
	std::string			m_databaseStr;
	bool				m_dbOpen;
	
	cool::IFolderPtr 		m_folderPtr;
	std::string			m_folderStr;
	bool				m_folderOpen;
	
	time_t				m_start;
	time_t				m_end;
	
	std::vector<std::string>	m_attrNames;
	std::vector<double>		m_attrMeanOfMeans;
	std::vector<double>		m_attrSigmaOfMeans;
	std::vector<double>		m_attrMeanOfSigmas;
	std::vector<double>		m_attrSigmaOfSigmas;
	
	std::vector<std::string>	m_rootFilenames;
	
	bool				m_omitDisabled;
	bool				m_omitUnusedPpms;
	std::string			m_disabledAttrStr;
	
	std::map<uint,coolAttributeCollection*>*	m_attrCollection;
	
	void push_back(const uint coolId,coolAttributeCollection* attrCollection)
		{(*m_attrCollection)[coolId] = attrCollection;};
	
	cool::ValidityKey getValidityKey(time_t time)
		{return cool::ValidityKey(((ULong64_t)time)*(ULong64_t)1000000000 );};
	time_t getTime_t(cool::ValidityKey key){return (time_t)(key/1000000000);};
	
};



#endif
