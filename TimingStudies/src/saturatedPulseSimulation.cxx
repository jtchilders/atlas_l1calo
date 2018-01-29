

#include <iostream>


#include "saturatedAnalysis.h"


using namespace std;

int main(int argc, char** argv){
	
	SaturatedAnalysis* ana = new SaturatedAnalysis(5);
	
	ana->SetBatch(false);
	//ana->FindRegSatLowHigh(argc,argv);
	//ana->CalculateBcDetectionEfficiency(argc,argv);
	//ana->TestEfficiencyStability(argc,argv);
	
	//ana->SetLowestRegSatLow(96);
	//ana->FindBestRegSatHigh(argc,argv);
	
	ana->fadcPlotter(argc,argv);
	
	delete ana;ana = 0;
	
}

