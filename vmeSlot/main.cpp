
#include <iostream>


//#include "ReadTempsVolts.cxx"
#include "test.cxx"

#include "TApplication.h"
#include "TROOT.h"

using namespace std;

int main(int argc, char** argv){
	
	gROOT->SetBatch(kTRUE);
	
	TApplication theApp("theApp",&argc,argv);
	
	
	//test();
	test();

	theApp.Run();
	
	
	return 0;
}


