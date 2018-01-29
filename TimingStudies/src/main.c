
#include <iostream>

#include "TApplication.h"
#include "TROOT.h"

//#include "basicAnalysis.cxx"
 #include "simplePpmPlots.cxx"
//#include "robRun.cxx"
//#include "EnergyAnalysis.cxx"


using namespace std;

int main(int argc,char **argv){
	
	
	TApplication *app = new TApplication("app",&argc,argv);
	
	SimplePpmPlots(app->Argc(),app->Argv());
	
	app->Run();
	
	return 0;
}
