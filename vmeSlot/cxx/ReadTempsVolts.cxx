
#include "VME_memRegisters.h"
#include "VMESlotClass.h"

#include "TH2F.h"
#include "TCanvas.h"
#include "TStyle.h"

void ReadTempsVolts(void){
	
	
	
	double temp[16];
	double volts[7];
	
	TH2F *histoTemps = new TH2F("histoTemps","PPM Temperatures;Slot;MCM",16,5,21,16,0,16);
	
	
	int slot = 10;	
	
	VMESlot *vme = new VMESlot(slot);	
	
	cerr << "Reading Temperatures...";
	vme->ReadTempsAndVoltages(temp,volts);
	cerr << "done.\n";

	for(int j=0;j<16;j++)
		histoTemps->Fill(10,15-j,temp[j]);
	
	
	TCanvas *c1 = new TCanvas("c1","Temps",0,0,600,400);
	
	
	gStyle->SetPalette(1);
	histoTemps->Draw("colz");
	
	c1->SaveAs("Temps.ps");
	//cerr << "String: " << output << endl;

	exit(0);
}

