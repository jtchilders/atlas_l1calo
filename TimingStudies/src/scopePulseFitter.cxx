
#include <iostream>


#include "scopePulse.h"

#include "L1CaloChannelMap.h"
#include "LandGaus.h"
#include "FermiFunction.h"
#include "PixelMap.h"
#include "LandGaus.h"

#include "commandLineParser.h"

#include "TH1D.h"
#include "TF1.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TProfile.h"
#include "TApplication.h"

using namespace std;

int main(int argc, char** argv){
	
	
	#include "gStyleSetup.cxx"
	
	
	TApplication *app = new TApplication("App",&argc,argv);
	
	//gROOT->SetBatch(kTRUE);
	
	CommandLineTool* opts = new CommandLineTool(app->Argc(),app->Argv());
	
	string filename = opts->GetFilename();
	
	ScopePulse* pulse = new ScopePulse(filename);
	pulse->FillPulse();
	
	cerr << "Entries: " << pulse->GetEntries() << endl;
	cerr << "Resolution: " << pulse->GetResolution() << endl;
	
	const uint numTimeSlices = 5;
	const uint numPhos4Steps = 25;
	
	const uint numEntries = pulse->GetEntries();
	
	TH1D* histoPulse = new TH1D("histoPulse","Pulse Shape", numEntries,0.,(pulse->GetEntries()*pulse->GetResolution()*1e9) );
	
	
	for(uint i=0;i<numEntries;i++){
		
		histoPulse->SetBinContent(i+1,pulse->GetVoltageValue(i));
		
	}
	
	
	TCanvas* canvas = new TCanvas("canvas","canvas",0,0,800,600);
	
	
	histoPulse->Draw();
	
	
	FermiFunc* fermiFunc = new FermiFunc;
	TF1* ffit = new TF1("ffit",fermiFunc,70,140,4);
	ffit->SetParameters(3.5,430.,10.,0.);
	ffit->SetLineColor(kBlue);
	
	
	TF1* fit = new TF1("fit","gaus + [3]",70,140);
	
	fit->SetParameters(3.5,110.,10.,0.);
	fit->FixParameter(3,0.4);
	
	histoPulse->Fit(fit,"rb");
	histoPulse->Fit(ffit,"r");
	fit->SetRange(0,1200);
	ffit->SetRange(0,1200);
	
	fit->Draw("same");
	ffit->Draw("same");
	
	
	app->Run();
	
	return 0;
}

