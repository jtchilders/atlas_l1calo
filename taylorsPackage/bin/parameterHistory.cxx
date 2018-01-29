

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <anaTools/CoolL1Calo.h>
#include <coolL1Calo/CoolChannelId.h>
#include <anaTools/CoolPpmChan.h>

#include "TCanvas.h"
#include "TH1I.h"
#include "TH1S.h"
#include "TH1C.h"
#include "TH1D.h"
#include "TTimeStamp.h"
#include "TApplication.h"
#include "TStyle.h"
#include "TF1.h"

#include "taylorsPackage/CoolChanHistory.h"
#include "infraL1Calo/L1CaloModuleType.h"

int main(int argc,char** argv){
	
	#include "src/gStyleSetup.cxx"
	
	
	gROOT->SetBatch(true);
	
	TApplication *app = new TApplication("app",&argc,argv);
	
	time_t currentLocalTimeInSeconds = time(NULL);
	struct tm* currentUTCTime = gmtime(&currentLocalTimeInSeconds);
	time_t currentUTCtimeInSenconds = mktime(currentUTCTime);
	
	//TTimeStamp *endTimeStamp = new TTimeStamp(currentUTCTImeInSenconds,0);
	
	struct tm startTime;
	startTime.tm_year = 108;  //yr since 1900
	startTime.tm_mon  = 6;   // months 0 - 11
	startTime.tm_mday = 1;    // day of month 1 - 31
	startTime.tm_wday = 1;    // day of week since sunday 0-6
	startTime.tm_hour = 1;
	startTime.tm_min  = 1;
	startTime.tm_sec  = 1;
	startTime.tm_isdst = 1;   // day light savings 0=winter 1=summer
	
	time_t startTimeInSeconds = mktime(&startTime);
	if(startTimeInSeconds == -1) std::cerr << "Error\n";
	
	std::cerr << "Since: " << ctime(&startTimeInSeconds);
	std::cerr << "Until: " << ctime(&currentUTCtimeInSenconds) << std::endl;
	
	CoolChannelId coolId(0,L1CaloModuleType::Ppm,0,0,0);
	
	std::string dacOffsetStr = "DacOffset";
	std::string dacSlopeStr = "DacSlope";
	std::vector<std::string> attrStrList;
	attrStrList.push_back(dacSlopeStr);
	attrStrList.push_back(dacOffsetStr);
	
	CoolChanHistory history;
	history.OmitDisabledPpmChannels(true);
	history.OmitUnusedPpmChannels(true);
	//history.SetModuleType(PPM);
	history.setAttributeList(attrStrList);
	history.setStartTime(startTimeInSeconds);
	history.setEndTime(currentUTCtimeInSenconds);
	
	
	//TCanvas temp("temp","temp",0,0,1800,600);
// 	for(uint crate=0;crate<8;crate++){
// 		coolId.setCrate(crate);
// 		for(uint ppm=0;ppm<16;ppm++){
// 			coolId.setModule(ppm);
// 			std::cerr << "Crate: " << crate << " PPM: " << ppm << std::endl;
// 			for(uint mcm=0;mcm<16;mcm++){
// 				coolId.setSubmodule(mcm);
// 				for(uint chan=0;chan<4;chan++){
// 					coolId.setChannel(chan);
// 					//std::cerr << "  Cool ID: 0x" << std::hex << coolId.getId() << std::dec << std::endl;
// 					history.fillAttrCollection(coolId.getId());
// 					
// 				} //for(chan)
// 			} //for(mcm)
// 			
// 		} //for(ppm)
// 	} //for(crate)
// 	
// 	history.fillSummaryPlots();
// 	
// 	std::vector<double> meanOfMeans,sigmaOfMeans,meanOfSigmas,sigmaOfSigmas;
// 	history.getAttrStatsB(meanOfMeans,sigmaOfMeans,meanOfSigmas,sigmaOfSigmas);
// 	
// 	for(uint i=0;i<attrStrList.size();i++){
// 		
// 		std::cerr << "Mean of means for " << attrStrList[i] << ": " << meanOfMeans[i] << " +/- " << sigmaOfMeans[i] << std::endl;
// 		std::cerr << "Mean of sigmas for " << attrStrList[i] << ": " << meanOfSigmas[i] << " +/- " << sigmaOfSigmas[i] << std::endl;
// 		
// 	}
// 	
// 	history.errorCheckHistograms();
	
	history.printToFile();
	
	
	exit(0);
	app->Run();
	
	return 0;
	
}






