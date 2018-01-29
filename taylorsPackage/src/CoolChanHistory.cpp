#include "taylorsPackage/CoolChanHistory.h"


CoolChanHistory::CoolChanHistory(void){
	Init();
}


CoolChanHistory::~CoolChanHistory(void){
	
	for(std::map<uint,coolAttributeCollection*>::iterator itr = m_attrCollection->begin();
		itr != m_attrCollection->end();itr++){
		
		delete itr->second;
		itr->second = 0;
	}
	
	delete m_attrCollection; m_attrCollection = 0;
	
	delete m_coolDb; m_coolDb = 0;
}

void CoolChanHistory::Init(void){
	
	m_attrCollection = new std::map<uint,coolAttributeCollection*>;
	
	m_dbOpen = false;
	m_folderOpen = false;
	
	// Used for omitting PPM disabled channels
	m_omitDisabled = false;
	m_disabledAttrStr = "ErrorCode";
	
	// Default values for L1Calo Database, but these can be changed
	m_databaseStr = "sqlite://;schema=/afs/cern.ch/atlas/project/tdaq/level1/calo/data/calib/calib.sqlite;dbname=L1CALO";
	m_folderStr = "/TRIGGER/L1Calo/Calibration/PprChanCalib";
	
	
	openDb();
	openFolder();
}

// taken from Martin's CoolL1Calo class
int CoolChanHistory::openDb(void){
	
	// read database values for given run
	const Bool_t readOnly = kTRUE;
	
	m_coolDb = new CoolAccess(m_databaseStr.c_str(), readOnly);
	if(m_coolDb->isOpen()){
		std::cerr << "[CoolChanHistory::openDb]: Database opened OK\n";
		m_dbOpen = true;
		return 0;
	}
	else{
		std::cerr << "[CoolChanHistory::openDb]: Error opening database.\n";
		return -1;
	}
	
	return -1;
}


// taken from Martin's CoolTools class
int CoolChanHistory::openFolder(void)
{
	cool::IDatabasePtr dbPtr = m_coolDb->getDb();
	
	try {
	if (dbPtr->existsFolder(m_folderStr.c_str())) {
		m_folderPtr = dbPtr->getFolder(m_folderStr.c_str());
		m_folderOpen = true;
	}
	}
	catch (cool::Exception& e) {
		std::cerr << "[CoolChanHistory::openFolder]: " << e.what() << std::endl;
		return -1;
	}
	catch (coral::Exception& e) {
		std::cerr << "[CoolChanHistory::openFolder]:" << e.what() << std::endl;
		return -1;
	}
	catch (...) {
		std::cerr << "[CoolChanHistory::openFolder]: Failed to open folder (UNKNOWN exception)\n";
		return -1;
	}
	
	if (!m_folderPtr) {
		std::cerr << "[CoolChanHistory::openFolder]: Failed to open folder " << m_folderStr << std::endl;
		return -1;
	}
	
	return 0;
}

void CoolChanHistory::setStartTime(uint yr,uint mon,uint day,uint hr,uint min,uint sec){
	
	TDatime startTime(yr,mon,day,hr,min,sec);
	
	m_start = startTime.Convert();
}

void CoolChanHistory::setEndTime(uint yr,uint mon,uint day,uint hr,uint min,uint sec){
	TDatime endTime(yr,mon,day,hr,min,sec);
	
	m_end = endTime.Convert();
}

void CoolChanHistory::setAttributeList(std::vector<std::string>& attrList){
	
	m_attrNames.clear();
	m_attrNames = attrList;
	
	m_attrMeanOfMeans.resize(m_attrNames.size(),0);
	m_attrSigmaOfMeans.resize(m_attrNames.size(),0);
	m_attrMeanOfSigmas.resize(m_attrNames.size(),0);
	m_attrSigmaOfSigmas.resize(m_attrNames.size(),0);
	
	for(uint i=0;i<m_attrNames.size();i++){
		char temp[100];
		sprintf(temp,"%s_history.root",m_attrNames[i].c_str());
		std::string tempStr = temp;
		m_rootFilenames.push_back(tempStr);
	}
	
}

// Searches the Attribute Collections and calculates overall mean for the given attribute
// This uses the sum/sum2 for each attribute so it really is an overall mean
// That is, this is not a mean of the mean values for each cool id
void CoolChanHistory::getAttrStatsA(std::string attrName,double& mean, double& sigma){
	
	std::map<uint,coolAttributeCollection*>::iterator attrItr = 
		m_attrCollection->begin();
	
	double sum=0,sum2=0;
	uint n=0;
	for(;attrItr != m_attrCollection->end();attrItr++){
		for(uint i=0;i<attrItr->second->GetNumberAttrInt();i++){
			std::string* tempName = attrItr->second->GetAttributeInt(i)->GetName();
			if(tempName->find(attrName) != std::string::npos){
				sum += attrItr->second->GetAttributeInt(i)->GetSum();
				sum2 += attrItr->second->GetAttributeInt(i)->GetSum2();
				n += attrItr->second->GetAttributeInt(i)->GetEntries();
			}
		}
		for(uint i=0;i<attrItr->second->GetNumberAttrUInt();i++){
			std::string* tempName = attrItr->second->GetAttributeUInt(i)->GetName();
			if(tempName->find(attrName) != std::string::npos){
				sum += attrItr->second->GetAttributeUInt(i)->GetSum();
				sum2 += attrItr->second->GetAttributeUInt(i)->GetSum2();
				n += attrItr->second->GetAttributeUInt(i)->GetEntries();
			}
		}
		for(uint i=0;i<attrItr->second->GetNumberAttrShort();i++){
			std::string* tempName = attrItr->second->GetAttributeShort(i)->GetName();
			if(tempName->find(attrName) != std::string::npos){
				sum += attrItr->second->GetAttributeShort(i)->GetSum();
				sum2 += attrItr->second->GetAttributeShort(i)->GetSum2();
				n += attrItr->second->GetAttributeShort(i)->GetEntries();
			}
		}
		for(uint i=0;i<attrItr->second->GetNumberAttrUShort();i++){
			std::string* tempName = attrItr->second->GetAttributeUShort(i)->GetName();
			if(tempName->find(attrName) != std::string::npos){
				sum += attrItr->second->GetAttributeUShort(i)->GetSum();
				sum2 += attrItr->second->GetAttributeUShort(i)->GetSum2();
				n += attrItr->second->GetAttributeUShort(i)->GetEntries();
			}
		}
		for(uint i=0;i<attrItr->second->GetNumberAttrUChar();i++){
			std::string* tempName = attrItr->second->GetAttributeUChar(i)->GetName();
			if(tempName->find(attrName) != std::string::npos){
				sum += attrItr->second->GetAttributeUChar(i)->GetSum();
				sum2 += attrItr->second->GetAttributeUChar(i)->GetSum2();
				n += attrItr->second->GetAttributeUChar(i)->GetEntries();
			}
		}
		for(uint i=0;i<attrItr->second->GetNumberAttrFloat();i++){
			std::string* tempName = attrItr->second->GetAttributeFloat(i)->GetName();
			if(tempName->find(attrName) != std::string::npos){
				sum += attrItr->second->GetAttributeFloat(i)->GetSum();
				sum2 += attrItr->second->GetAttributeFloat(i)->GetSum2();
				n += attrItr->second->GetAttributeFloat(i)->GetEntries();
			}
		}
		for(uint i=0;i<attrItr->second->GetNumberAttrDouble();i++){
			std::string* tempName = attrItr->second->GetAttributeDouble(i)->GetName();
			if(tempName->find(attrName) != std::string::npos){
				sum += attrItr->second->GetAttributeDouble(i)->GetSum();
				sum2 += attrItr->second->GetAttributeDouble(i)->GetSum2();
				n += attrItr->second->GetAttributeDouble(i)->GetEntries();
			}
		}
	}
	
	mean = sum/(double)n;
	sigma = sqrt((1.0/(double)n)*sum2-mean*mean);
	
}

// This calculates the mean of the means of each cool id for the given attribute
// and the sigma of the means
// and the mean of the sigmas
// and the sigma of the sigmas
void CoolChanHistory::getAttrStatsB(std::vector<double>& meanOfMeans,
	std::vector<double>& sigmaOfMeans,std::vector<double>& meanOfSigmas,
	std::vector<double>& sigmaOfSigmas){
	
	std::vector<double> sumOfMeans,sum2ofMeans,sumOfSigmas,sum2ofSigmas;
	std::vector<uint> n;
	
	sumOfMeans.resize(m_attrNames.size(),0);
	sum2ofMeans.resize(m_attrNames.size(),0);
	sumOfSigmas.resize(m_attrNames.size(),0);
	sum2ofSigmas.resize(m_attrNames.size(),0);
	n.resize(m_attrNames.size(),0);
	
	
	for(uint attrEntry=0;attrEntry<m_attrNames.size();attrEntry++){
		
		TFile* rootFile = new TFile(m_rootFilenames[attrEntry].c_str(),"READ");
		::Info("CoolChanHistory::getAttrStatsB","Calculating mean/sigma using histograms in: %s",m_rootFilenames[attrEntry].c_str());
		
		// Get a list of keys that reference the histograms in this file
		TList* keyList = rootFile->GetListOfKeys();
		
		if(keyList->GetEntries() == 0){
			::Warning("CoolChanHistory::getAttrStatsB","%s has no histograms in it.",m_rootFilenames[attrEntry].c_str());
			break;
		}
		
		//std::cerr << "num of keys: " << keyList->GetEntries() << std::endl;
		// Loop over all the 1D histograms
		for(int key=0;key<keyList->GetEntries();key++){
			// grab the actual histogram pointer.
			TKey* histoKey = (TKey*)keyList->At(key);
			TH1* histo = (TH1*)histoKey->ReadObj();
			std::string histoName = histo->GetName();
			
			//std::cerr << histoName << std::endl;
			
			bool attrNameFound = false;
			// want to skip mean/sigma summary histograms
			if(histoName.find("mean") != std::string::npos){
				attrNameFound = false;
			}
			else if(histoName.find("sigma") != std::string::npos){
				attrNameFound = false;
			}
			else{
				attrNameFound = true;
			}
			
			
			if(!attrNameFound) continue;
			
			std::stringstream str(histoName);
			char divider = '_';
			std::string attrName,histoType;
			uint coolChanId=0;
			getline(str,attrName,divider);
			getline(str,histoType,divider);
			str >> std::hex >> coolChanId;
			
			if(m_omitUnusedPpms){
				
				CoolChannelId id(coolChanId);
				
				if( id.getCrate() == 2 || id.getCrate() == 3)
					if( id.getModule() == 0 || id.getModule() == 8)
						continue;
			}
			
			
			double sum=0,sum2=0;
			int tempN = 0;
			for(int bin=1;bin<=histo->GetNbinsX();bin++){
				// make sure bin is filled to count it.
				
				if(fabs(histo->GetBinContent(bin)) < 0.0001) continue;
				
				sum += histo->GetBinContent(bin);
				sum2 += histo->GetBinContent(bin)*histo->GetBinContent(bin);
				tempN++;
				
				//std::cerr << "   " << histo->GetBinContent(bin) << std::endl;
			}
			
			double mean=sum/(double)tempN;
			double sigma=sqrt( (1.0/(double)tempN)*sum2-mean*mean);
			
			sumOfMeans[attrEntry] += mean;
			sum2ofMeans[attrEntry] += mean*mean;
			sumOfSigmas[attrEntry] += sigma;
			sum2ofSigmas[attrEntry] += sigma*sigma;
			n[attrEntry]++;
			
		}
		
		rootFile->Close();
		rootFile->Delete();
		rootFile = 0;
	} // end for loop over attribute names
		
	
	
	
	meanOfMeans.clear();
	sigmaOfMeans.clear();
	meanOfSigmas.clear();
	sigmaOfSigmas.clear();
	
	for(uint i=0;i<m_attrNames.size();i++){
		meanOfMeans.push_back( sumOfMeans[i]/(double)n[i] );
		sigmaOfMeans.push_back(  sqrt((1.0/(double)n[i])*sum2ofMeans[i]-meanOfMeans[i]*meanOfMeans[i]) );
		
		meanOfSigmas.push_back( sumOfSigmas[i]/(double)n[i] );
		sigmaOfSigmas.push_back( sqrt((1.0/(double)n[i])*sum2ofSigmas[i]-meanOfSigmas[i]*meanOfSigmas[i]) );
		
		
		m_attrMeanOfMeans[i] = meanOfMeans[i];
		m_attrSigmaOfMeans[i] = sigmaOfMeans[i];
		m_attrMeanOfSigmas[i] = meanOfSigmas[i];
		m_attrSigmaOfSigmas[i] = sigmaOfSigmas[i];
		
		
	}
	
}

// Loops over stored histograms and finds problem channels
// using the calculated mean/sigma values
void CoolChanHistory::errorCheckHistograms(void){
	
	for(uint attrEntry=0;attrEntry<m_attrNames.size();attrEntry++){
	
		TFile* rootFile = new TFile(m_rootFilenames[attrEntry].c_str(),"UPDATE");
		::Info("CoolChanHistory::reprocessHistograms","Calculating bad channels using histograms in: %s",m_rootFilenames[attrEntry].c_str());
		
		// Get a list of keys that reference the histograms in this file
		TList* keyList = rootFile->GetListOfKeys();
		
		if(keyList->GetEntries() == 0){
			::Warning("CoolChanHistory::reprocessHistograms","%s has no histograms in it.",m_rootFilenames[attrEntry].c_str());
			return;
		}
		
		// Loop over all the 1D histograms
		for(int key=0;key<keyList->GetEntries();key++){
			// grab the actual histogram pointer.
			TKey* histoKey = (TKey*)keyList->At(key);
			TH1* histo = (TH1*)histoKey->ReadObj();
			std::string histoName = histo->GetName();
			
			//std::cerr << histoName << std::endl;
			
			bool attrNameFound = false;
			
			// want to skip mean/sigma summary histograms
			if(histoName.find("mean") != std::string::npos){
				attrNameFound = false;
			}
			else if(histoName.find("sigma") != std::string::npos){
				attrNameFound = false;
			}
			else{
				attrNameFound = true;
			}
			
			
			if(!attrNameFound) continue;
			
			std::stringstream str(histoName);
			char divider = '_';
			std::string attrName,histoType;
			uint coolChanId=0;
			getline(str,attrName,divider);
			getline(str,histoType,divider);
			str >> std::hex >> coolChanId;
			
			if(m_omitUnusedPpms){
				
				CoolChannelId id(coolChanId);
				
				if( id.getCrate() == 2 || id.getCrate() == 3)
					if( id.getModule() == 0 || id.getModule() == 8)
						continue;
			}
			
			// Calculate the mean for this channel
			double sum=0,sum2=0;
			int n=0;
			for(int bin=1;bin<=histo->GetNbinsX();bin++){
				// bin is empty (is equal to zero)
				if(fabs(histo->GetBinContent(bin)) < 0.0001) continue;
				
				sum += histo->GetBinContent(bin);
				sum2 += histo->GetBinContent(bin)*histo->GetBinContent(bin);
				n++;
			}
			
			double mean=sum/(double)n;
			double sigma=sqrt( (1.0/(double)n)*sum2-mean*mean);
			
			
			if(fabs(mean-m_attrMeanOfMeans[attrEntry]) > m_attrSigmaOfMeans[attrEntry]*3.0){
				histo->SetFillColor(kGreen);
				
				//std::cerr << "mean > 3sigma : 0x" << std::hex << coolChanId << std::dec << "  mean: " << mean << " moms: " << m_attrMeanOfMeans[attrEntry] << " soms: " << m_attrSigmaOfMeans[attrEntry] << std::endl;
				
				if(fabs(sigma-m_attrMeanOfSigmas[attrEntry]) > m_attrSigmaOfSigmas[attrEntry]*3.0){
					histo->SetFillColor(kViolet);
					
					//std::cerr << "sigma > 3sigma : 0x" << std::hex << coolChanId << std::dec << "  sigma: " << sigma << " moss: " << m_attrMeanOfSigmas[attrEntry] << " soss: " << m_attrSigmaOfSigmas[attrEntry] << std::endl;
				}
				else if(fabs(sigma-m_attrMeanOfSigmas[attrEntry]) > m_attrSigmaOfSigmas[attrEntry]*2.0){
					histo->SetFillColor(kMagenta);
					
					//std::cerr << "sigma > 2sigma : 0x" << std::hex << coolChanId << std::dec << "  sigma: " << sigma << " moss: " << m_attrMeanOfSigmas[attrEntry] << " soss: " << m_attrSigmaOfSigmas[attrEntry] << std::endl;
				}
				
				histo->Write(histo->GetName(),TObject::kOverwrite);
				
			
			}
			
			
			if(fabs(sigma-m_attrMeanOfSigmas[attrEntry]) > m_attrSigmaOfSigmas[attrEntry]*3.0){
				histo->SetFillColor(kRed);
				histo->Write(histo->GetName(),TObject::kOverwrite);
				
				//std::cerr << "sigma > 3sigma : 0x" << std::hex << coolChanId << std::dec << "  sigma: " << sigma << " moss: " << m_attrMeanOfSigmas[attrEntry] << " soss: " << m_attrSigmaOfSigmas[attrEntry] << std::endl;
			}
			else if(fabs(sigma-m_attrMeanOfSigmas[attrEntry]) > m_attrSigmaOfSigmas[attrEntry]*2.0){
				histo->SetFillColor(kPink);
				histo->Write(histo->GetName(),TObject::kOverwrite);
				
				//std::cerr << "sigma > 2sigma : 0x" << std::hex << coolChanId << std::dec << "  sigma: " << sigma << " moss: " << m_attrMeanOfSigmas[attrEntry] << " soss: " << m_attrSigmaOfSigmas[attrEntry] << std::endl;
			}
			
		} //for(keyList)
		
		rootFile->Close();
		rootFile->Delete();
		rootFile = 0;
	} // loop of attribute names
}


// Fills the CoolAttribute objects for all the m_attrNames that have been set
// and the cool id given passed
int CoolChanHistory::fillAttrCollection(uint coolId){
	
	if(!m_dbOpen){
		::Warning("CoolChanHistory::fillAttrCollection","Error: No Database open.");
		return -1;
	}
	if(!m_folderOpen){
		::Warning("CoolChanHistory::fillAttrCollection","Error: No Folder open.");
		return -1;
	}
	
	cool::IObjectIteratorPtr objIter;
	uint numOfEntries;
	cool::ChannelSelection chanSel = cool::ChannelSelection(coolId);
	try {
		objIter = m_folderPtr->browseObjects(getValidityKey(m_start), getValidityKey(m_end), chanSel);
		numOfEntries = m_folderPtr->countObjects(getValidityKey(m_start), getValidityKey(m_end), chanSel);
	}
	catch (cool::Exception& e) {
		::Warning("CoolChanHistory::fillAttrCollection"," failed to read PprChanCalib folder");
	}
	
	
	while (objIter->goToNext()){
		const cool::IObject& o = objIter->currentRef();
		
		
		// Check for disabled channels
		bool disabled = false;
		if(m_omitDisabled){
			unsigned int errorCode = o.payloadValue<unsigned int>(m_disabledAttrStr);
			if(errorCode & 0xf){
				//std::cerr << "disabled: " << std::hex << coolId << std::dec << std::endl;
				disabled = true;
			}
		}
		
		for(uint attr=0;attr<m_attrNames.size();attr++){
			
			const cool::StorageType::TypeId typeId = o.payload()[m_attrNames[attr]].storageType().id();
			
			// Get This entries validity keys and convert them to system time values
			time_t since_t = getTime_t(o.since());
			time_t until_t = getTime_t(o.until());
			
			if(o.until() == cool::ValidityKeyMax){
				time_t a = time(NULL);
				until_t = mktime(gmtime(&a));
			}
			
			switch (typeId){
			case cool::StorageType::Int32:
			{
				
				int value = o.payloadValue<int>(m_attrNames[attr]);
				
				std::map<uint,coolAttributeCollection*>::iterator itr = m_attrCollection->find(coolId);
				
				if(itr == m_attrCollection->end()){
					coolAttributeCollection* temp = new coolAttributeCollection;
					
					(*m_attrCollection)[coolId] = temp;
					itr = m_attrCollection->find(coolId);
					if(itr == m_attrCollection->end()){
						::Warning("CoolChanHistory::fillAttrCollection(Int32)"," Failed to create map entry");
					}
					else{
						itr->second->CreateNewAttribute(m_attrNames[attr],typeId,coolId);
					}
				}
				
				if(itr->second->AddAttrValue(m_attrNames[attr],value,since_t,until_t,disabled) == -1){
					itr->second->CreateNewAttribute(m_attrNames[attr],typeId,coolId);
					itr->second->AddAttrValue(m_attrNames[attr],value,since_t,until_t,disabled);
				}
				
				break;
			}
			case cool::StorageType::Int16:
			{
				short int value = o.payloadValue<short int>(m_attrNames[attr]);
				
				std::map<uint,coolAttributeCollection*>::iterator itr = m_attrCollection->find(coolId);
				
				if(itr == m_attrCollection->end()){
					coolAttributeCollection* temp = new coolAttributeCollection;
					
					(*m_attrCollection)[coolId] = temp;
					itr = m_attrCollection->find(coolId);
					if(itr == m_attrCollection->end()){
						::Warning("CoolChanHistory::fillAttrCollection(Int16)"," Failed to create map entry");
					}
					else{
						itr->second->CreateNewAttribute(m_attrNames[attr],typeId,coolId);
					}
				}
				
				if(itr->second->AddAttrValue(m_attrNames[attr],value,since_t,until_t,disabled) == -1){
					itr->second->CreateNewAttribute(m_attrNames[attr],typeId,coolId);
					itr->second->AddAttrValue(m_attrNames[attr],value,since_t,until_t,disabled);
				}
				
				break;
			}
			case cool::StorageType::UInt32:
			{
				unsigned int value = o.payloadValue<unsigned int>(m_attrNames[attr]);
				
				std::map<uint,coolAttributeCollection*>::iterator itr = m_attrCollection->find(coolId);
				
				if(itr == m_attrCollection->end()){
					coolAttributeCollection* temp = new coolAttributeCollection;
					
					(*m_attrCollection)[coolId] = temp;
					itr = m_attrCollection->find(coolId);
					if(itr == m_attrCollection->end()){
						::Warning("CoolChanHistory::fillAttrCollection(UInt32)"," Failed to create map entry");
					}
					else{
						itr->second->CreateNewAttribute(m_attrNames[attr],typeId,coolId);
					}
				}
				
				if(itr->second->AddAttrValue(m_attrNames[attr],value,since_t,until_t,disabled) == -1){
					itr->second->CreateNewAttribute(m_attrNames[attr],typeId,coolId);
					itr->second->AddAttrValue(m_attrNames[attr],value,since_t,until_t,disabled);
				}
				
				break;
			}
			case cool::StorageType::UInt16:
			{
				unsigned short value = o.payloadValue<unsigned short>(m_attrNames[attr]);
				
				std::map<uint,coolAttributeCollection*>::iterator itr = m_attrCollection->find(coolId);
				
				if(itr == m_attrCollection->end()){
					coolAttributeCollection* temp = new coolAttributeCollection;
					
					(*m_attrCollection)[coolId] = temp;
					itr = m_attrCollection->find(coolId);
					if(itr == m_attrCollection->end()){
						::Warning("CoolChanHistory::fillAttrCollection(UInt16)"," Failed to create map entry");
					}
					else{
						itr->second->CreateNewAttribute(m_attrNames[attr],typeId,coolId);
					}
				}
				
				if(itr->second->AddAttrValue(m_attrNames[attr],value,since_t,until_t,disabled) == -1){
					itr->second->CreateNewAttribute(m_attrNames[attr],typeId,coolId);
					itr->second->AddAttrValue(m_attrNames[attr],value,since_t,until_t,disabled);
				}
				
				break;
			}
			case cool::StorageType::UChar:
			{
				unsigned char value = o.payloadValue<unsigned char>(m_attrNames[attr]);
				
				std::map<uint,coolAttributeCollection*>::iterator itr = m_attrCollection->find(coolId);
				
				if(itr == m_attrCollection->end()){
					coolAttributeCollection* temp = new coolAttributeCollection;
					
					(*m_attrCollection)[coolId] = temp;
					itr = m_attrCollection->find(coolId);
					if(itr == m_attrCollection->end()){
						::Warning("CoolChanHistory::fillAttrCollection(UChar)"," Failed to create map entry");
					}
					else{
						itr->second->CreateNewAttribute(m_attrNames[attr],typeId,coolId);
					}
				}
				
				if(itr->second->AddAttrValue(m_attrNames[attr],value,since_t,until_t,disabled) == -1){
					itr->second->CreateNewAttribute(m_attrNames[attr],typeId,coolId);
					itr->second->AddAttrValue(m_attrNames[attr],value,since_t,until_t,disabled);
				}
				
				break;
			}
			case cool::StorageType::Float:
			{
				float value = o.payloadValue<float>(m_attrNames[attr]);
				
				std::map<uint,coolAttributeCollection*>::iterator itr = m_attrCollection->find(coolId);
				
				if(itr == m_attrCollection->end()){
					coolAttributeCollection* temp = new coolAttributeCollection;
					
					(*m_attrCollection)[coolId] = temp;
					itr = m_attrCollection->find(coolId);
					if(itr == m_attrCollection->end()){
						::Warning("CoolChanHistory::fillAttrCollection(Float)"," Failed to create map entry");
					}
					else{
						itr->second->CreateNewAttribute(m_attrNames[attr],typeId,coolId);
					}
				}
				
				if(itr->second->AddAttrValue(m_attrNames[attr],value,since_t,until_t,disabled) == -1){
					itr->second->CreateNewAttribute(m_attrNames[attr],typeId,coolId);
					itr->second->AddAttrValue(m_attrNames[attr],value,since_t,until_t,disabled);
				}
				
				break;
			}
			case cool::StorageType::Double:
			{
				double value = o.payloadValue<double>(m_attrNames[attr]);
				
				std::map<uint,coolAttributeCollection*>::iterator itr = m_attrCollection->find(coolId);
				
				if(itr == m_attrCollection->end()){
					coolAttributeCollection* temp = new coolAttributeCollection;
					
					(*m_attrCollection)[coolId] = temp;
					itr = m_attrCollection->find(coolId);
					if(itr == m_attrCollection->end()){
						::Warning("CoolChanHistory::fillAttrCollection(Double)"," Failed to create map entry");
					}
					else{
						itr->second->CreateNewAttribute(m_attrNames[attr],typeId,coolId);
					}
				}
				
				if(itr->second->AddAttrValue(m_attrNames[attr],value,since_t,until_t,disabled) == -1){
					itr->second->CreateNewAttribute(m_attrNames[attr],typeId,coolId);
					itr->second->AddAttrValue(m_attrNames[attr],value,since_t,until_t,disabled);
				}
				
				break;
			}
			default:
				::Warning("CoolChanHistory::fillAttrCollection"," Error finding case");
				return 0;
				break;
			}
			
		} // for(attr)
		
	} // while(iter)
	objIter->close();
	
	// Write the 1D histograms to a file
	// Fill Histograms for these attributes
	for(uint entry=0;entry<m_attrNames.size();entry++){
		TFile rootFile(m_rootFilenames[entry].c_str(),"UPDATE");
		
		TH1* temphisto = (*m_attrCollection)[coolId]->GetAttrHistogram(m_attrNames[entry]);
		std::string histoName = temphisto->GetName();
		temphisto->Write(histoName.c_str(),TObject::kOverwrite);
		
		rootFile.Close();
	}
	
	return 0;
}

void CoolChanHistory::fillSummaryPlots(void){
	
	
	// These will hold pixelMaps for the attributes
	// They will be eta/phi profiles for each attribute
	// entry X corresponds to entry X in the m_attrNames
	std::vector<PixelMap<double>*>* pmEm = new std::vector<PixelMap<double>*>;
	std::vector<PixelMap<double>*>* pmHad = new std::vector<PixelMap<double>*>;
	
	// need some vectors to hold pointers to the TH1 plots
	// they are created inside the loop and need to be held
	// until they are stored in the second loop
	
	
	
	// Need a channel map for eta/phi to coolId converstion
	L1CaloChannelMap* map = new L1CaloChannelMap;
	map->SetJemEnable(false);
	map->SetCpmEnable(false);
	
	for(uint attrEntry=0;attrEntry<m_attrNames.size();attrEntry++){
		
		//////////////////////////////////////////////
		/// Setup TH1 plots for 1D summary plots
		char meanName[50],sigmaName[50];
		sprintf(meanName,"%s_mean_1D",m_attrNames[attrEntry].c_str());
		sprintf(sigmaName,"%s_sigma_1D",m_attrNames[attrEntry].c_str());
		
		char meanTitle[100],sigmaTitle[100];
		sprintf(meanTitle,"Mean %s for all channels;mean %s;entries",m_attrNames[attrEntry].c_str(),m_attrNames[attrEntry].c_str());
		sprintf(sigmaTitle,"Sigma %s for all channels;sigma %s;entries",m_attrNames[attrEntry].c_str(),m_attrNames[attrEntry].c_str());
		
		TH1D* meanAttrHisto;
		TH1D* sigmaAttrHisto;
		 
		if(m_attrNames[attrEntry].find("DacOffset") != std::string::npos){
			meanAttrHisto = new TH1D(meanName,meanTitle,200,-300,-200);
			sigmaAttrHisto = new TH1D(sigmaName,sigmaTitle,250,0,5);
		}
		else if(m_attrNames[attrEntry].find("DacSlope") != std::string::npos){
			meanAttrHisto = new TH1D(meanName,meanTitle,200,1.7,2.3);
			sigmaAttrHisto = new TH1D(sigmaName,sigmaTitle,250,0,0.06);
		}
		else{
			meanAttrHisto = new TH1D(meanName,meanTitle,500,0,500);
			sigmaAttrHisto = new TH1D(sigmaName,sigmaTitle,500,0,5);
		}
		///////////////////////////////////////////////////
		
		// open root file that contains histograms (READ ONLY)
		TFile* rootFile = new TFile(m_rootFilenames[attrEntry].c_str());
		::Info("CoolChanHistory::fillSummaryPlots","Filling Summary Plots with file: %s",m_rootFilenames[attrEntry].c_str());
		// Get a list of keys that reference the histograms in this file
		TList* keyList = rootFile->GetListOfKeys();
		
		if(keyList->GetEntries() == 0){
			::Warning("CoolChanHistory::fillSummaryPlots","%s has no histograms in it.",m_rootFilenames[attrEntry].c_str());
			return;
		}
		
		
		
		PixelMap<double>* pmTempA = new PixelMap<double>(TrigTower);
		pmTempA->SetProfileMode(true);
		pmEm->push_back(pmTempA);
		
		PixelMap<double>* pmTempB = new PixelMap<double>(TrigTower);
		pmTempB->SetProfileMode(true);
		pmHad->push_back(pmTempB);
		
		
		// Loop over all the 1D histograms
		for(int i=0;i<keyList->GetEntries();i++){
			// grab the actual histogram pointer.
			TKey* histoKey = (TKey*)keyList->At(i);
			TH1* histo = (TH1*)histoKey->ReadObj();
			std::string histoName = histo->GetName();
			
			// make sure this is the 1D histo and not the summary plots
			bool attrNameFound = false;
			
			if(histoName.find("mean") != std::string::npos){
				attrNameFound = false;
			}
			else if(histoName.find("sigma") != std::string::npos){
				attrNameFound = false;
			}
			else{
				attrNameFound = true;
			}
			
			
			if(!attrNameFound) continue;
			
			// extract cool Id
			std::stringstream str(histoName);
			char divider = '_';
			std::string attrName,histoType;
			uint coolChanId=0;
			getline(str,attrName,divider);
			getline(str,histoType,divider);
			str >> std::hex >> coolChanId;
			
			// setup channel map
			map->SetPpmChannelID(coolChanId);
			
// 			std::cerr << "   " << histo->GetName() << "\n";
// 			std::cerr << "   " << map->GetPpmCrate()->at(0) << " " << map->GetPpmNum()->at(0) << " " << map->GetPpmMcm()->at(0) << " " << map->GetPpmChan()->at(0) << "\t" << std::hex << coolChanId << std::dec << "\n";
			
			// If this is an EM channel fill the appropriate pixelMap
			if(map->GetEmHad() == EM){
				double sum=0,sum2=0,n=0;
				for(int bin=1;bin<=histo->GetNbinsX();bin++){
// 					std::cerr << "     " << map->GetEta() << "/" << map->GetPhi() << "  " << histo->GetBinContent(bin) <<  "    " << map->GetPpmFcalLayer()->at(0) << "\n";
					// make sure this bin is not equal to zero
					if( !(fabs(histo->GetBinContent(bin)) < 0.0001)){
						
						(*pmEm)[attrEntry]->SetTriggerTower(
							map->GetEta(),map->GetPhi(),
							histo->GetBinContent(bin),
							map->GetPpmFcalLayer()->at(0) );
						
						// add to sums for mean/sigma calc
						sum += histo->GetBinContent(bin);
						sum2 += histo->GetBinContent(bin)*histo->GetBinContent(bin);
						n++;
					}
				}
				
				if(n > 0){
					double mean = sum/n;
					double sigma = sqrt((1.0/n)*sum2-mean*mean);
					meanAttrHisto->Fill(mean);
					sigmaAttrHisto->Fill(sigma);
				}
				
// 				std::cerr << "    mean: " << (*pmEm)[attrEntry]->GetTriggerTowerMean(map->GetEta(),map->GetPhi(),map->GetPpmFcalLayer()->at(0)) << "  sigma: " << (*pmEm)[attrEntry]->GetTriggerTowerSigma(map->GetEta(),map->GetPhi(),map->GetPpmFcalLayer()->at(0)) << std::endl;
			
			}
			else if(map->GetEmHad() == HAD){
				double sum=0,sum2=0,n=0;
				for(int bin=1;bin<histo->GetNbinsX();bin++){
// 					std::cerr << "     " << map->GetEta() << "/" << map->GetPhi() << "  " << histo->GetBinContent(bin) <<  "    " << map->GetPpmFcalLayer()->at(0) << "\n";
					// make sure this bin is not equal to zero
					if( !(fabs(histo->GetBinContent(bin)) < 0.0001)){
						(*pmHad)[attrEntry]->SetTriggerTower(
							map->GetEta(),map->GetPhi(),
							histo->GetBinContent(bin),
							map->GetPpmFcalLayer()->at(0) );
						
						// add to sums for mean/sigma calc
						sum += histo->GetBinContent(bin);
						sum2 += histo->GetBinContent(bin)*histo->GetBinContent(bin);
						n++;
					}
				}
				
				if(n > 0){
					double mean = sum/n;
					double sigma = sqrt((1.0/n)*sum2-mean*mean);
					meanAttrHisto->Fill(mean);
					sigmaAttrHisto->Fill(sigma);
				}
				
// 				std::cerr << "    mean: " << (*pmHad)[attrEntry]->GetTriggerTowerMean(map->GetEta(),map->GetPhi(),map->GetPpmFcalLayer()->at(0)) << "  sigma: " << (*pmHad)[attrEntry]->GetTriggerTowerSigma(map->GetEta(),map->GetPhi(),map->GetPpmFcalLayer()->at(0)) << std::endl;
			
			}
			
			
			
		}
		
		rootFile->Close();
		rootFile->Delete();
		rootFile = 0;
		
		// Now fill the 2D maps and save them to file
		
		// open root file for writing now
		rootFile = new TFile(m_rootFilenames[attrEntry].c_str(),"UPDATE");
		
		std::string emNameMean  = "em_" + m_attrNames[attrEntry] + "_mean";
		std::string emTitleMean = "Mean " + m_attrNames[attrEntry] + " for EM Layer";
		TH2D* histoEmMean = new TH2D(emNameMean.c_str(), emTitleMean.c_str(), L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
		
		std::string emNameSigma  = "em_" + m_attrNames[attrEntry] + "_sigma";
		std::string emTitleSigma = "Sigma " + m_attrNames[attrEntry] + " for EM Layer";
		TH2D* histoEmSigma = new TH2D(emNameSigma.c_str(), emTitleSigma.c_str(), L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
		
		TH2D* emHistos[2] = {histoEmMean,histoEmSigma};
		pmEm->at(attrEntry)->FillEtaPhiHistogram(emHistos);
		
		histoEmMean->Write(emNameMean.c_str(),TObject::kOverwrite);
		histoEmSigma->Write(emNameSigma.c_str(),TObject::kOverwrite);
		
		
		std::string hadNameMean  = "had_" + m_attrNames[attrEntry] + "_mean";
		std::string hadTitleMean = "Mean " + m_attrNames[attrEntry] + " for HAD Layer";
		TH2D* histoHadMean = new TH2D(hadNameMean.c_str(), hadTitleMean.c_str(), L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
		
		std::string hadNameSigma  = "had_" + m_attrNames[attrEntry] + "_sigma";
		std::string hadTitleSigma = "Sigma " + m_attrNames[attrEntry] + " for HAD Layer";
		TH2D* histoHadSigma = new TH2D(hadNameSigma.c_str(), hadTitleSigma.c_str(), L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
		
		TH2D* hadHistos[2] = {histoHadMean,histoHadSigma};
		pmHad->at(attrEntry)->FillEtaPhiHistogram(hadHistos);
		
		histoHadMean->Write(hadNameMean.c_str(),TObject::kOverwrite);
		histoHadSigma->Write(hadNameSigma.c_str(),TObject::kOverwrite);
		
		meanAttrHisto->Write(meanName,TObject::kOverwrite);
		sigmaAttrHisto->Write(sigmaName,TObject::kOverwrite);
		
		rootFile->Close();
		rootFile->Delete();
		rootFile = 0;
		
	}
	
	::Info("CoolChanHistory::fillSummaryPlots"," Completed summary plots");
	
}

void CoolChanHistory::printToFile(void){
	
	const int numOfPpmCrates = 8;
	const int numOfPpmPerCrate = 16;
	//const int numOfMcmPerPpm = 16;
	const int numOfChannelsPerMcm = 4;
	const int numOfPpmsTotal = numOfPpmCrates*numOfPpmPerCrate;
	
	for(uint attrEntry=0;attrEntry<m_attrNames.size();attrEntry++){
		
		// used to keep track of critical, fatal, and summary plots
		std::vector<int> keysForCriticalHistograms;
		std::vector<int> keysForFatalHistograms;
		
		std::vector<int> keysForSummaryHistograms;
		
		TFile* rootFile = new TFile(m_rootFilenames[attrEntry].c_str(),"UPDATE");
		::Info("CoolChanHistory::printToFile","Writing histograms in %s to file.",m_rootFilenames[attrEntry].c_str());
		
		// Get a list of keys that reference the histograms in this file
		TList* keyList = rootFile->GetListOfKeys();
		
		if(keyList->GetEntries() == 0){
			::Warning("CoolChanHistory::printToFile","%s has no histograms in it.",m_rootFilenames[attrEntry].c_str());
			return;
		}
		
		// I also want to write the bad Channels to text file so I can read them later
		std::string fatalFilename = "fatalCoolIds_";
		fatalFilename += m_attrNames[attrEntry];
		fatalFilename += ".dat";
		bool fatalFileNotOpen = false;
		std::ofstream* outFatalFile = new std::ofstream(fatalFilename.c_str());
		if(!outFatalFile->is_open()){
			::Warning("CoolChanHistory::printToFile","Error opening file %s for writing.",fatalFilename.c_str());
			fatalFileNotOpen = true;
		}
		std::string criticalFilename = "criticalCoolIds_";
		criticalFilename += m_attrNames[attrEntry];
		criticalFilename += ".dat";
		bool criticalFileNotOpen = false;
		std::ofstream* outCriticalFile = new std::ofstream(criticalFilename.c_str());
		if(!outCriticalFile->is_open()){
			::Warning("CoolChanHistory::printToFile","Error opening file %s for writing.",criticalFilename.c_str());
			criticalFileNotOpen = true;
		}
		
		::Info("CoolChanHistory::printToFile","Setting up Canvases for %s",m_attrNames[attrEntry].c_str());
		// setup canvas for each ppm
		TCanvas* canvas[numOfPpmsTotal];
		for(int crate=0;crate<numOfPpmCrates;crate++) 
		for(int ppm=0;ppm<numOfPpmPerCrate;ppm++){
			char name[100];
			sprintf(name,"canvas_crate%i_ppm%02i",crate,ppm);
			char title[100];
			sprintf(title,"Crate %i PPM %02i",crate,ppm);
			const int canvasIndex = crate*numOfPpmPerCrate + ppm;
			canvas[canvasIndex] = new TCanvas(name,title,0,0,1000,800);
			canvas[canvasIndex]->SetBatch(true);
			canvas[canvasIndex]->Divide(8,8);
		}
		
		::Info("CoolChanHistory::printToFile","Drawing Histograms to Canvases.");
		// Loop over cool Ids to place histograms
		for(int key=0;key<keyList->GetEntries();key++){
			// grab the actual histogram pointer.
			TKey* histoKey = (TKey*)keyList->At(key);
			TH1* histo = (TH1*)histoKey->ReadObj();
			std::string histoName = histo->GetName();
			
			//std::cerr << histoName << std::endl;
			
			bool isSummaryPlot = true;
			// want to skip mean/sigma summary histograms
			if(histoName.find("mean") != std::string::npos){
				isSummaryPlot = true;
				keysForSummaryHistograms.push_back(key);
				
			}
			else if(histoName.find("sigma") != std::string::npos){
				isSummaryPlot = true;
				keysForSummaryHistograms.push_back(key);
			}
			else{
				isSummaryPlot = false;
				
			}
			
			
			if(isSummaryPlot) continue;
			
			std::stringstream str(histoName);
			char divider = '_';
			std::string attrName,histoType;
			uint coolChanId=0;
			getline(str,attrName,divider);
			getline(str,histoType,divider);
			str >> std::hex >> coolChanId;
			
			CoolChannelId id(coolChanId);
			const int crate = id.getCrate();
			const int ppm = id.getModule();
			const int mcm = id.getSubmodule();
			const int chan = id.getChannel();
			
			const int canvasIndex = crate*numOfPpmPerCrate+ppm;
			const int padIndex = (mcm*numOfChannelsPerMcm+chan)+1;
			canvas[canvasIndex]->cd(padIndex);
			if(m_attrNames[attrEntry].find("DacOffset") != std::string::npos){
				histo->SetMaximum(-200);
				histo->SetMinimum(-300);
			}
			else if(m_attrNames[attrEntry].find("DacSlope") != std::string::npos){
				histo->SetMaximum(2.2);
				histo->SetMinimum(1.8);
			}
			
			gStyle->SetHatchesLineWidth(1);
			histo->SetLineColor(kBlack);
			// (mean-meanOfmeans) > 3 sigmaOfMean
			if(histo->GetFillColor() == kGreen){ 
				keysForFatalHistograms.push_back(key);
				histo->SetFillColor(kRed);
				histo->DrawCopy();
				histo->SetFillColor(kBlack);
				histo->SetFillStyle(3959); // vertical lines
				histo->DrawCopy("same");
				histo->SetFillColor(kGreen);
				
				*outFatalFile << coolChanId << "\t" << crate << "\t" << ppm << "\t" << mcm << "\t" << chan << "\n";
			}
			// (mean-meanOfmeans) > 3 sigmaOfMean && (sigma-meanOfSigmas) > 3 sigmaOfsigmas
			else if(histo->GetFillColor() == kViolet){ 
				keysForFatalHistograms.push_back(key);
				histo->SetFillColor(kRed);
				histo->DrawCopy();
				histo->SetFillColor(kBlack);
				histo->SetFillStyle(3909); // vertical & horizontal lines
				histo->DrawCopy("same");
				histo->SetFillColor(kViolet);
				
				*outFatalFile << coolChanId << "\t" << crate << "\t" << ppm << "\t" << mcm << "\t" << chan << "\n";
			}
			// (mean-meanOfmeans) > 3 sigmaOfMean && (sigma-meanOfSigmas) > 2 sigmaOfsigmas
			else if(histo->GetFillColor() == kMagenta){ 
				keysForFatalHistograms.push_back(key);
				histo->SetFillColor(kRed);
				histo->SetLineColor(kYellow);
				histo->DrawCopy();
				histo->SetFillColor(kBlack);
				histo->SetLineColor(kBlack);
				histo->SetFillStyle(3909); // vertical & horizontal lines
				histo->DrawCopy("same");
				histo->SetFillColor(kMagenta);
				
				*outFatalFile << coolChanId << "\t" << crate << "\t" << ppm << "\t" << mcm << "\t" << chan << "\n";
			}
			// ((sigma-meanOfSigmas) > 3 sigmaOfsigmas
			else if(histo->GetFillColor() == kRed){ 
				keysForFatalHistograms.push_back(key);
				histo->SetFillColor(kRed);
				histo->DrawCopy();
				histo->SetFillColor(kBlack);
				histo->SetFillStyle(3950); // horizontal lines
				histo->DrawCopy("same");
				histo->SetFillColor(kRed);
				
				*outFatalFile << coolChanId << "\t" << crate << "\t" << ppm << "\t" << mcm << "\t" << chan << "\n";
			}
			// ((sigma-meanOfSigmas) > 2 sigmaOfsigmas
			else if(histo->GetFillColor() == kPink){ 
				keysForCriticalHistograms.push_back(key);
				histo->SetFillColor(kYellow);
				histo->DrawCopy();
				histo->SetFillColor(kBlack);
				histo->SetFillStyle(3950); // horizontal lines
				histo->DrawCopy("same");
				histo->SetFillColor(kPink);
				
				*outCriticalFile << coolChanId << "\t" << crate << "\t" << ppm << "\t" << mcm << "\t" << chan << "\n";
			}
			else{
				histo->DrawCopy();
			}
			
			//canvas[canvasIndex]->Update();
			//canvas[canvasIndex]->SaveAs("canvas.ps");
			
		}
		
		
		
		outCriticalFile->close();
		delete outCriticalFile;
		
		outFatalFile->close();
		delete outFatalFile;
		
		
		// now fill Critical/Fatal canvases
		::Info("CoolChanHistory::printToFile","Filling canvases for critical and fatal histograms.");
		const int numOfPlotsPerCanvas = 64;
		const int numOfPlotsPerRow = 8;
		
		// Set up canvases for critical plots
		const unsigned int numOfCriticalCanvases = (int) ((double)keysForCriticalHistograms.size() / (double)numOfPlotsPerCanvas) + 1;
		std::vector<TCanvas*> criticalCanvas;
		for(unsigned int i=0;i<numOfCriticalCanvases;i++){
			std::string name = "criticalCanvas_";
			name += i;
			TCanvas* temp = new TCanvas(name.c_str(),"critical plots",0,0,1000,800);
			temp->SetBatch(true);
			temp->Divide(numOfPlotsPerRow,numOfPlotsPerCanvas/numOfPlotsPerRow);
			criticalCanvas.push_back(temp);
		}
		// Now populate canvases
		for(unsigned int entry=0;entry<keysForCriticalHistograms.size();entry++){
			
			TKey* histoKey = (TKey*)keyList->At(keysForCriticalHistograms[entry]);
			TH1* histo = (TH1*)histoKey->ReadObj();
			
			const int canvasIndex = (int)((double)entry/(double)numOfPlotsPerCanvas);
			
			const int padIndex = (entry+1) - canvasIndex*numOfPlotsPerCanvas;
			criticalCanvas[canvasIndex]->cd(padIndex);
			
			gStyle->SetHatchesLineWidth(1);
			histo->SetLineColor(kBlack);
			
			if(m_attrNames[attrEntry].find("DacOffset") != std::string::npos){
				histo->SetMaximum(-200);
				histo->SetMinimum(-300);
			}
			else if(m_attrNames[attrEntry].find("DacSlope") != std::string::npos){
				histo->SetMaximum(2.2);
				histo->SetMinimum(1.8);
			}
			
			// ((sigma-meanOfSigmas) > 2 sigmaOfsigmas
			if(histo->GetFillColor() == kPink){ 
				histo->SetFillColor(kYellow);
				histo->DrawCopy();
				histo->SetFillColor(kBlack);
				histo->SetFillStyle(3950); // horizontal lines
				histo->DrawCopy("same");
				histo->SetFillColor(kPink);
			}
		}
		
		// Set up canvases for fatal plots
		const unsigned int numOfFatalCanvases = (int) ((double)keysForFatalHistograms.size() / (double)numOfPlotsPerCanvas) + 1;
		std::vector<TCanvas*> fatalCanvas;
		for(unsigned int i=0;i<numOfFatalCanvases;i++){
			std::string name = "fatalCanvas_";
			name += i;
			TCanvas* temp = new TCanvas(name.c_str(),"fatal plots",0,0,1000,800);
			temp->SetBatch(true);
			temp->Divide(numOfPlotsPerRow,numOfPlotsPerCanvas/numOfPlotsPerRow);
			fatalCanvas.push_back(temp);
		}
		
		// Now populate canvases
		for(unsigned int entry=0;entry<keysForFatalHistograms.size();entry++){
			
			TKey* histoKey = (TKey*)keyList->At(keysForFatalHistograms[entry]);
			TH1* histo = (TH1*)histoKey->ReadObj();
			
			const int canvasIndex = (int)((double)entry/(double)numOfPlotsPerCanvas);
			
			const int padIndex = (entry+1) - canvasIndex*numOfPlotsPerCanvas;
			fatalCanvas[canvasIndex]->cd(padIndex);
			
			
			gStyle->SetHatchesLineWidth(1);
			histo->SetLineColor(kBlack);
			
			if(m_attrNames[attrEntry].find("DacOffset") != std::string::npos){
				histo->SetMaximum(-200);
				histo->SetMinimum(-300);
			}
			else if(m_attrNames[attrEntry].find("DacSlope") != std::string::npos){
				histo->SetMaximum(2.2);
				histo->SetMinimum(1.8);
			}
			
			// (mean-meanOfmeans) > 3 sigmaOfMean
			if(histo->GetFillColor() == kGreen){ 
				histo->SetFillColor(kRed);
				histo->DrawCopy();
				histo->SetFillColor(kBlack);
				histo->SetFillStyle(3959); // vertical lines
				histo->DrawCopy("same");
				histo->SetFillColor(kGreen);
			}
			// (mean-meanOfmeans) > 3 sigmaOfMean && (sigma-meanOfSigmas) > 3 sigmaOfsigmas
			else if(histo->GetFillColor() == kViolet){ 
				histo->SetFillColor(kRed);
				histo->DrawCopy();
				histo->SetFillColor(kBlack);
				histo->SetFillStyle(3909); // vertical & horizontal lines
				histo->DrawCopy("same");
				histo->SetFillColor(kViolet);
			}
			// (mean-meanOfmeans) > 3 sigmaOfMean && (sigma-meanOfSigmas) > 2 sigmaOfsigmas
			else if(histo->GetFillColor() == kMagenta){ 
				histo->SetFillColor(kRed);
				histo->SetLineColor(kYellow);
				histo->DrawCopy();
				histo->SetFillColor(kBlack);
				histo->SetLineColor(kBlack);
				histo->SetFillStyle(3909); // vertical & horizontal lines
				histo->DrawCopy("same");
				histo->SetFillColor(kMagenta);
			}
			// ((sigma-meanOfSigmas) > 3 sigmaOfsigmas
			else if(histo->GetFillColor() == kRed){ 
				histo->SetFillColor(kRed);
				histo->DrawCopy();
				histo->SetFillColor(kBlack);
				histo->SetFillStyle(3950); // horizontal lines
				histo->DrawCopy("same");
				histo->SetFillColor(kRed);
			}
		}
		
		
		::Info("CoolChanHistory::printToFile","Saving canvases to file.");
		std::string baseFilename = m_attrNames[attrEntry] + ".ps";
		for(int crate=0;crate<numOfPpmCrates;crate++) 
		for(int ppm=0;ppm<numOfPpmPerCrate;ppm++){
			char name[100];
			sprintf(name,"canvas_crate%i_ppm%02i",crate,ppm);
			char title[100];
			sprintf(title,"Crate %i PPM %02i",crate,ppm);
			
			const int canvasIndex = crate*numOfPpmPerCrate + ppm;
			
			canvas[canvasIndex]->Update();
			
			if(canvasIndex == 0){
				std::string filename = baseFilename + "(";
				canvas[canvasIndex]->SaveAs(filename.c_str());
			}
			else if (canvasIndex == numOfPpmsTotal-1 && 
				keysForFatalHistograms.size() == 0 &&
				keysForCriticalHistograms.size() == 0 &&
				keysForSummaryHistograms.size() == 0){
				std::string filename = baseFilename + ")";
				canvas[canvasIndex]->SaveAs(filename.c_str());
			}
			else
				canvas[canvasIndex]->SaveAs(baseFilename.c_str());
			
			delete canvas[canvasIndex];
			canvas[canvasIndex] = 0;
		}
		
		// save critical canvases to file
		for(uint critical=0;critical<numOfCriticalCanvases;critical++){
			
			criticalCanvas[critical]->Update();
			
			if(critical == (numOfCriticalCanvases - 1) &&
				keysForFatalHistograms.size() == 0 &&
				keysForSummaryHistograms.size() == 0){
				std::string filename = baseFilename + ")";
				criticalCanvas[critical]->SaveAs(filename.c_str());
			}
			else
				criticalCanvas[critical]->SaveAs(baseFilename.c_str());
			
			delete criticalCanvas[critical];
			criticalCanvas[critical] = 0;
		}
		criticalCanvas.clear();
		
		// save critical canvases to file
		for(uint fatal=0;fatal<numOfFatalCanvases;fatal++){
			
			fatalCanvas[fatal]->Update();
			
			if(fatal == (numOfFatalCanvases - 1) &&
				keysForSummaryHistograms.size() == 0){
				std::string filename = baseFilename + ")";
				fatalCanvas[fatal]->SaveAs(filename.c_str());
			}
			else
				fatalCanvas[fatal]->SaveAs(baseFilename.c_str());
			
			delete fatalCanvas[fatal];
			fatalCanvas[fatal] = 0;
		}
		fatalCanvas.clear();
		
		
		// Draw Summary Plots
		const unsigned int numOfSummaryHistogramsPerPage = 4;
		const unsigned int widthOfSummaryHistogramsPage = 2;
		TCanvas* summaryCanvas = new TCanvas("summaryCanvas","summaryCanvas",0,0,800,600);
		summaryCanvas->SetBatch(true);
		summaryCanvas->Divide(widthOfSummaryHistogramsPage,numOfSummaryHistogramsPerPage/widthOfSummaryHistogramsPage);
		
		if(keysForSummaryHistograms.size() > numOfSummaryHistogramsPerPage){
			const unsigned int numOfCanvas = keysForSummaryHistograms.size()/numOfSummaryHistogramsPerPage + 1;
			::Info("CoolChanHistory::printToFile","numOfSummaryHistograms: %i",numOfCanvas);
			for(unsigned int canvasNum=0;canvasNum<numOfCanvas;canvasNum++){
				unsigned int startKey = canvasNum*numOfSummaryHistogramsPerPage;
				for(unsigned int keyNum = startKey; 
				(keyNum - startKey) < numOfSummaryHistogramsPerPage 
				;keyNum++)
				{
					if(keyNum > keysForSummaryHistograms.size())
						summaryCanvas->cd( (keyNum-canvasNum*numOfSummaryHistogramsPerPage)+1)->Clear();
					else
						summaryCanvas->cd( (keyNum-canvasNum*numOfSummaryHistogramsPerPage)+1);
					
					TKey* histoKey = (TKey*)keyList->At(keysForSummaryHistograms[keyNum]);
					TH1* histo = (TH1*)histoKey->ReadObj();
					
					std::string histoName = histo->GetName();
					if(histoName.find("1D") != std::string::npos){
						histo->DrawCopy();
					}
					else{
						histo->SetContour(64);
						if(histoName.find("sigma") != std::string::npos){
							if(histoName.find("DacSlope") != std::string::npos){
								histo->SetMaximum(0.04);
							}
							else if(histoName.find("DacOffset") != std::string::npos){
								histo->SetMaximum(4);
							}
						}
						
						histo->DrawCopy("colz");
					}
				}
				if(canvasNum == (numOfCanvas - 1)){
					std::string filename = baseFilename + ")";
					summaryCanvas->SaveAs(filename.c_str());
				}
				else
					summaryCanvas->SaveAs(baseFilename.c_str());
			}
			
		}
		else{
			for(unsigned int i = 0;i<keysForSummaryHistograms.size();i++){
				summaryCanvas->cd(i+1);
				TKey* histoKey = (TKey*)keyList->At(keysForSummaryHistograms[i]);
				TH1* histo = (TH1*)histoKey->ReadObj();
				
				std::string histoName = histo->GetName();
				if(histoName.find("1D") != std::string::npos){
					histo->DrawCopy();
				}
				else{
					histo->SetContour(64);
					if(histoName.find("sigma") != std::string::npos){
						if(histoName.find("DacSlope") != std::string::npos){
							histo->SetMaximum(0.04);
						}
						else if(histoName.find("DacOffset") != std::string::npos){
							histo->SetMaximum(4);
						}
					}
					
					histo->DrawCopy("colz");
				}
			}
			std::string filename = baseFilename + ")";
			summaryCanvas->SaveAs(filename.c_str());
		}
		keysForSummaryHistograms.clear();
		
		
		rootFile->Close();
		rootFile->Delete();
		rootFile = 0;
		
		::Info("CoolChanHistory::printToFile","Number of Critical Channels: %i" ,keysForCriticalHistograms.size());
		::Info("CoolChanHistory::printToFile","Number of Fatal Channels: %i" ,keysForFatalHistograms.size());
		
		
	} // end loop over attribute names
}




