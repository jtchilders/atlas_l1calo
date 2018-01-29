

#include <string>

#include "extractTxt.h"

#include "L1CaloChannelMap.h"
#include "PixelMap.h"

#include "TCanvas.h"
#include "TH1I.h"
#include "TH2D.h"
#include "TApplication.h"
#include "TFile.h"
#include "TLegend.h"

#include "gStyleSetup.cxx"
	
int main(int argc,char** argv){
	
	if(argc != 2){
		std::cerr << "Usage: analyzeReplacements <filename>\n";
		return 0;
		
	}
	
	gStyleSetup();
	
	L1CaloChannelMap* map = new L1CaloChannelMap;
	map->SetCpmEnable(false);
	map->SetJemEnable(false);
	
	std::string filename = argv[1];
	
	ExtractTxt ext(filename);
	
	TH1I* th1OldCrate = new TH1I("th1OldCrate","Crate Number Distribution;Crate Number;number of bad MCMs replaced",8,0,8);
	TH1I* th1OldPpm = new TH1I("th1OldPpm","Ppm Number Distribution;Ppm Number;number of bad MCMs replaced",16,0,16);
	TH1I* th1OldMcm = new TH1I("th1OldMcm","Mcm Number Distribution;Mcm Number;number of bad MCMs replaced",16,0,16);
	TH1I* th1OldChan = new TH1I("th1OldChan","Channel Number Distribution;Channel Number;number of bad MCMs replaced",4,0,4);
	
	const int maxProbCode = 16;
	TH1I* th1ProblemCode = new TH1I("th1ProblemCode","MCM replacement reasons;;num of mcms",maxProbCode,0,maxProbCode);
	char problemCode[maxProbCode][100] = {"DAC","PED","PHOS4","LUT","MCM Kaputt","ASIC: BCMiss","ASIC: EvtMiss","ActuallyOK","RateMetering","CP Parity","JEM Parity","ASIC: Timeout","Temp Diode","Playback","At High Rate","Other"};
	
	for(int i=1;i<=maxProbCode;i++)
		th1ProblemCode->GetXaxis()->SetBinLabel(i,problemCode[i-1]);
	
	
	PixelMap<unsigned int>* pmHad = new PixelMap<unsigned int>(TrigTower);
	PixelMap<unsigned int>* pmEm  = new PixelMap<unsigned int>(TrigTower);
	
	
	const unsigned int numEtaBins = 66;
	float etaBins[numEtaBins+1];
	etaBins[0] = -49;
	etaBins[1] = -44;
	etaBins[2] = -40;
	etaBins[3] = -36;
	etaBins[4] = -32;
	etaBins[5] = -31;
	etaBins[6] = -29;
	etaBins[7] = -27;
	for(int i=-25,j=8;i<=25;i++,j++)
		etaBins[j] = i;
	etaBins[59] = 27;
	etaBins[60] = 29;
	etaBins[61] = 31;
	etaBins[62] = 32;
	etaBins[63] = 36;
	etaBins[64] = 40;
	etaBins[65] = 44;
	etaBins[66] = 49;
	
	TH1F* th1OldEta = new TH1F("th1OldEta","Eta distribution of replaced MCMs;#Eta;number of bad MCMs replaced",numEtaBins,etaBins);
	
	
	TH1I* th1OldPhi = new TH1I("th1OldPhi","Phi distribution of replaced MCMs;#Phi;number of bad MCMs replaced",64,0,64);
	
	
	std::vector<time_t> timeEntries;
	
	unsigned int problemCodeToBin[maxProbCode+2] = {0,1,2,3,99,99,4,5,6,7,8,9,10,11,12,13,14,15};
	
	for(unsigned int entry=0;entry<ext.GetNumberOfEntries();entry++){
		Entry* current = ext.GetEntry(entry);
		
		// don't want to count PPM exchanges at the moment
		if(current->GetSwappedItem().find("PPM") != std::string::npos) continue;
		
		th1OldCrate->Fill(current->GetOldCrate());
		th1OldPpm->Fill(current->GetOldPpm());
		th1OldMcm->Fill(current->GetOldMcm());
		
		for(unsigned int i=0;i<current->GetNumberOldChannels();i++){
			th1OldChan->Fill(current->GetOldChannel(i));
			
			map->SetPpmChannel(current->GetOldCrate(),
			                   current->GetOldPpm(),
			                   current->GetOldMcm(),
			                   current->GetOldChannel(i));
			
			
			if(map->GetEta() < 0)
				th1OldEta->Fill((map->GetEta()*10));
			else
				th1OldEta->Fill((map->GetEta()*10 - 1));
			
			th1OldPhi->Fill((int)(map->GetPhi()*(64/(2*PI)) + 0.0001));
			
			if(map->GetEmHad() == HAD){
				unsigned int oldValue = pmHad->GetTriggerTower(map->GetEta(),map->GetPhi());
				pmHad->SetTriggerTower(map->GetEta(),map->GetPhi(),oldValue + 1);
			}
			else if(map->GetEmHad() == EM){
				unsigned int oldValue = pmEm->GetTriggerTower(map->GetEta(),map->GetPhi());
				pmEm->SetTriggerTower(map->GetEta(),map->GetPhi(),oldValue + 1);
			}
			
		}
		
		for(unsigned int i=0;i<current->GetNumberOfProblems();i++)
			th1ProblemCode->Fill(problemCodeToBin[current->GetProblemCode(i)-1]);
		
		if(timeEntries.size() == 0)
			timeEntries.push_back(current->GetEntryTime());
		
		for(int i=0;i<timeEntries.size();i++){
			if(timeEntries[i] == current->GetEntryTime())
				break;
			else if(i == timeEntries.size() - 1){
				timeEntries.push_back(current->GetEntryTime());
				break;
			}
		}
		
	}
	
	TH1I* th1DacErrorVsTime = new TH1I("th1DacErrorVsTime","Number of MCM replaced due to errors;Time of Replacement;number of errors",timeEntries.size(),0,timeEntries.size());
	TH1I* th1PedErrorVsTime = new TH1I("th1PedErrorVsTime","Number of MCM replaced due to errors;Time of Replacement;number of errors",timeEntries.size(),0,timeEntries.size());
	TH1I* th1Phos4ErrorVsTime = new TH1I("th1Phos4ErrorVsTime","Number of MCM replaced due to errors;Time of Replacement;number of errors",timeEntries.size(),0,timeEntries.size());
	TH1I* th1LutErrorVsTime = new TH1I("th1LutErrorVsTime","Number of MCM replaced due to errors;Time of Replacement;number of errors",timeEntries.size(),0,timeEntries.size());
	TH1I* th1AsicErrorVsTime = new TH1I("th1AsicErrorVsTime","Number of MCM replaced due to errors;Time of Replacement;number of errors",timeEntries.size(),0,timeEntries.size());
	TH1I* th1McmErrorVsTime = new TH1I("th1McmErrorVsTime","Number of MCM replaced due to errors;Time of Replacement;number of errors",timeEntries.size(),0,timeEntries.size());
	TH1I* th1RmErrorVsTime = new TH1I("th1RmErrorVsTime","Number of MCM replaced due to errors;Time of Replacement;number of errors",timeEntries.size(),0,timeEntries.size());
	TH1I* th1LinkErrorVsTime = new TH1I("th1LinkErrorVsTime","Number of MCM replaced due to errors;Time of Replacement;number of errors",timeEntries.size(),0,timeEntries.size());
	
	TH1I* th1NumReplaced = new TH1I("th1NumReplaced","Number of MCM replaced due to errors;Time of Replacement;number of errors",timeEntries.size(),0,timeEntries.size());
	
	const int maxTimes = timeEntries.size();
	//char timeStrings[maxTimes][100];
	for(int i=timeEntries.size();i>0;i--){
		
		struct tm* tempTime = localtime(&timeEntries[i-1]);
		char timeString[100];
		strftime(timeString,100,"%Y-%m-%d",tempTime);
		
		
		unsigned int invertedBin = timeEntries.size() - i + 1;
		
		th1DacErrorVsTime->GetXaxis()->SetBinLabel(invertedBin,timeString);
		th1PedErrorVsTime->GetXaxis()->SetBinLabel(invertedBin,timeString);
		th1Phos4ErrorVsTime->GetXaxis()->SetBinLabel(invertedBin,timeString);
		th1LutErrorVsTime->GetXaxis()->SetBinLabel(invertedBin,timeString);
		th1AsicErrorVsTime->GetXaxis()->SetBinLabel(invertedBin,timeString);
		th1McmErrorVsTime->GetXaxis()->SetBinLabel(invertedBin,timeString);
		th1RmErrorVsTime->GetXaxis()->SetBinLabel(invertedBin,timeString);
		th1LinkErrorVsTime->GetXaxis()->SetBinLabel(invertedBin,timeString);
		
		th1NumReplaced->GetXaxis()->SetBinLabel(invertedBin,timeString);
	}
	
	for(unsigned int entry=0;entry<ext.GetNumberOfEntries();entry++){
		Entry* current = ext.GetEntry(entry);
		
		// don't want to count PPM exchanges at the moment
		if(current->GetSwappedItem().find("PPM") != std::string::npos) continue;
		
		int timeEntry;
		for(timeEntry=0;timeEntry<timeEntries.size();timeEntry++)
			if(timeEntries[timeEntry] == current->GetEntryTime())
				break;
		
		unsigned int invertedTimeEntry = timeEntries.size() - timeEntry - 1;
		th1NumReplaced->Fill(invertedTimeEntry);
		
		
		for(unsigned int codeEntry=0;codeEntry<current->GetNumberOfProblems();codeEntry++){
			
			switch(current->GetProblemCode(codeEntry)){
			case 1: // fails DAC scan
				th1DacErrorVsTime->Fill(invertedTimeEntry);
				break;
			case 2: // fails PED scan
				th1PedErrorVsTime->Fill(invertedTimeEntry);
				break;
			case 3: // fails PHOS4
				th1Phos4ErrorVsTime->Fill(invertedTimeEntry);
				break;
			case 4: // LUT bit errors
				th1LutErrorVsTime->Fill(invertedTimeEntry);
				break;
			case 7: // MCM Death
				th1McmErrorVsTime->Fill(invertedTimeEntry);
				break;
			case 8: // ASIC: BC Missmatch
				th1AsicErrorVsTime->Fill(invertedTimeEntry);
				break;
			case 9: // ASIC: Evt Missmatch
				th1AsicErrorVsTime->Fill(invertedTimeEntry);
				break;
			case 11: // No Rate Metering
				th1RmErrorVsTime->Fill(invertedTimeEntry);
				break;
			case 12: // CP Parity Link Error
				th1LinkErrorVsTime->Fill(invertedTimeEntry);
				break;
			case 13: // Jem Parity Link Error
				th1LinkErrorVsTime->Fill(invertedTimeEntry);
				break;
			
			case 14: // ASIC: Timeout
				th1AsicErrorVsTime->Fill(invertedTimeEntry);
				break;
			default:
				break;
			}
		}
		
	}
	
	
	
	TApplication app("app",&argc,argv);
	
	TCanvas* canvas = new TCanvas("canvas","canvas",0,0,800,600);
	canvas->SetBatch(true);
	canvas->Divide(2,2);
	
	canvas->cd(1);
	th1OldCrate->Draw();
	
	canvas->cd(2);
	th1OldPpm->Draw();
	
	canvas->cd(3);
	th1OldMcm->Draw();
	
	canvas->cd(4);
	th1OldChan->Draw();
	
	canvas->SaveAs("plots.ps(");
	
	canvas->Clear();
	canvas->Divide(1,2);
	
	canvas->cd(1);
	th1OldEta->Draw();
	
	canvas->cd(2);
	th1OldPhi->Draw();
	
	canvas->SaveAs("plots.ps");
	
	canvas->Clear();
	canvas->Divide(1,2);
	
	canvas->cd(1);
	
	TH2D* th2HadMap = new TH2D("th2HadMap","MCM Replacements by Channel in Hadronic Layer;#Eta;#Phi",L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
	
	pmHad->FillEtaPhiHistogram(th2HadMap);
	
	th2HadMap->Draw("colz");
	
	canvas->cd(2);
	
	TH2D* th2EmMap = new TH2D("th2EmMap","MCM Replacements by Channel in Electromagnetic Layer;#Eta;#Phi",L1CALO_ETA_TT,-4.9,4.9,L1CALO_PHI_TT,0,2*PI);
	
	pmEm->FillEtaPhiHistogram(th2EmMap);
	
	th2EmMap->Draw("colz");
	
	canvas->SaveAs("plots.ps");
	
	canvas->Clear();
	
	th1ProblemCode->Draw();
	
	canvas->SaveAs("plots.ps");
	
	canvas->Clear();
	
	th1NumReplaced->SetBarWidth(0.9);
	th1NumReplaced->SetBarOffset(0.05);
	th1NumReplaced->SetFillColor(50);
	th1NumReplaced->Draw("bar2");
	
	canvas->SaveAs("plots.ps");
	
	canvas->Clear();
	
	gStyle->SetOptStat(0);
	
	th1DacErrorVsTime->SetBarWidth(0.1);
	th1DacErrorVsTime->SetBarOffset(0.1);
	th1DacErrorVsTime->SetFillColor(40);
	th1DacErrorVsTime->SetMaximum(20);
	th1DacErrorVsTime->DrawCopy("bar1");
	
	th1PedErrorVsTime->SetBarWidth(0.1);
	th1PedErrorVsTime->SetBarOffset(0.2);
	th1PedErrorVsTime->SetFillColor(41);
	th1PedErrorVsTime->DrawCopy("bar1,same");
	
	th1Phos4ErrorVsTime->SetBarWidth(0.1);
	th1Phos4ErrorVsTime->SetBarOffset(0.3);
	th1Phos4ErrorVsTime->SetFillColor(42);
	th1Phos4ErrorVsTime->DrawCopy("bar1,same");
	
	th1LutErrorVsTime->SetBarWidth(0.1);
	th1LutErrorVsTime->SetBarOffset(0.4);
	th1LutErrorVsTime->SetFillColor(45);
	th1LutErrorVsTime->DrawCopy("bar1,same");
	
	th1McmErrorVsTime->SetBarWidth(0.1);
	th1McmErrorVsTime->SetBarOffset(0.5);
	th1McmErrorVsTime->SetFillColor(49);
	th1McmErrorVsTime->DrawCopy("bar1,same");
	
	th1AsicErrorVsTime->SetBarWidth(0.1);
	th1AsicErrorVsTime->SetBarOffset(0.6);
	th1AsicErrorVsTime->SetFillColor(50);
	th1AsicErrorVsTime->DrawCopy("bar1,same");
	
	th1RmErrorVsTime->SetBarWidth(0.1);
	th1RmErrorVsTime->SetBarOffset(0.7);
	th1RmErrorVsTime->SetFillColor(51);
	th1RmErrorVsTime->DrawCopy("bar1,same");
	
	th1LinkErrorVsTime->SetBarWidth(0.1);
	th1LinkErrorVsTime->SetBarOffset(0.8);
	th1LinkErrorVsTime->SetFillColor(30);
	th1LinkErrorVsTime->DrawCopy("bar1,same");
	
	TLegend* legend = new TLegend(0.35,0.55,0.66,0.85);
	legend->AddEntry(th1DacErrorVsTime,"Fails DAC","f");
	legend->AddEntry(th1PedErrorVsTime,"Fails PED","f");
	legend->AddEntry(th1Phos4ErrorVsTime,"Fails PHOS4","f");
	legend->AddEntry(th1LutErrorVsTime,"LUT bit error","f");
	legend->AddEntry(th1McmErrorVsTime,"MCM death","f");
	legend->AddEntry(th1AsicErrorVsTime,"ASIC reporting error","f");
	legend->AddEntry(th1RmErrorVsTime,"No Rate Metering","f");
	legend->AddEntry(th1LinkErrorVsTime,"CP/JEP Link Error","f");
	
	legend->Draw();
	
	canvas->SaveAs("plots.ps)");
	
	
	
	delete th1OldCrate;
	delete th1OldPpm;
	delete th1OldMcm;
	delete th1OldChan;
	delete th1OldEta;
	delete th1OldPhi;
	
	delete th1ProblemCode;
	
	delete pmHad;
	delete pmEm;
	
	delete canvas;
	
	delete map;
	
	return 0;
}
