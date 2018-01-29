
#include <iostream>
#include <fstream>
#include <fstream>
#include <vector>
#include <cmath>
#include <map>

#include "cbntClass.h"

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
	
	CommandLineTool* opts = new CommandLineTool(argc,argv);
	
	TApplication *app = new TApplication("App",&argc,argv);
	
	gROOT->SetBatch(kTRUE);
	
	
	cbntClass *t;
	string filename = opts->GetFilename();
	
	if(!opts->IsFileList()){
		cerr << "Creating cbntClass with " << filename.c_str() << endl;
		t = new cbntClass(filename);
	}
	else if(opts->IsFileList()){
		t = new cbntClass(filename,opts->IsFileList());
		
	}
	
	const int totalEvts = t->fChain->GetEntries();
	
	cerr << "Total Events: " << totalEvts << endl;
	
	
	map<uint,TProfile*>* mProf = new map<uint,TProfile*>;
	
	unsigned int globalNumTimeSlices = 0;
	unsigned int globalNumPhos4Steps = 0;
	const unsigned int numNanosecPerTimeSlice = 25;
	const unsigned int numSteps = 27;
	
	// Keep track of which channels pass saturation
	map<unsigned int,bool>* satChannelOutToFile = new map<unsigned int,bool>;
	
	//Want a TH1 for each bin in each TProfile so I can see the distribution of the Entries at each step
	map<unsigned int,vector<TH1I*>* >* binHistoPerProfile = new map<unsigned int,vector<TH1I*>* >;
	unsigned int chanSelect = 0x00140602;
	
	for(int i=0;i<totalEvts;i++){
		
		//if( i%10 ) continue;
		
		t->GetEntry(i);
		
		if( !(i % (int(totalEvts*0.01) + 1)))
			cerr << "\r Percent Done: " << int(((float)i/(float)totalEvts)*100) << "\t";
		
		if( i == 0){
			const int numTimeSlices = t->L1CaloPPM_hadADC->at(0).size();
			globalNumTimeSlices = numTimeSlices;
			const int numPhos4Steps = numTimeSlices*numNanosecPerTimeSlice;
			globalNumPhos4Steps = numPhos4Steps;
		}
		
		// Loop of trigger towers
		for(int tt=0;tt<t->L1CaloPPM_ntt;tt++){
			
			uint stepNumber = t->L1CaloRODHeader_stepNumber->at(0) % 25;
			
			// Fill the Hadronic channels if they are filled
			if(t->L1CaloPPM_hadIsFilled->at(tt)){
				const unsigned int numTimeSlices = t->L1CaloPPM_hadADC->at(tt).size();
				const unsigned int numPhos4Steps = numTimeSlices*numNanosecPerTimeSlice;
				
				
				uint chanID = t->L1CaloPPM_hadChannelId->at(tt);
				
				// want to see which channels are saturated
				map<unsigned int,bool>::iterator satItr = satChannelOutToFile->find(chanID);
				// if no entry is found, create one
				if(satItr == satChannelOutToFile->end()){
					(*satChannelOutToFile)[chanID] = false;
					satItr = satChannelOutToFile->find(chanID);
				}
				
				// get iterator to the appropriate profile plot
				// if one doesn't exist create it
				map<uint,TProfile*>::iterator itr = mProf->find(chanID);
				if(itr == mProf->end()){
					char name[100];
					sprintf(name,"prof_%08x",t->L1CaloPPM_hadChannelId->at(tt));
					char title[100];
					sprintf(title,"Profile of PHOS4 Steps in %08x",t->L1CaloPPM_hadChannelId->at(tt));
					(*mProf)[chanID] = new TProfile(name,title,numPhos4Steps,0,numPhos4Steps,0,1024);
					itr =  mProf->find(chanID);
				}
				map<unsigned int, vector<TH1I*>* >::iterator itrTH1;
				if(chanID == chanSelect){
					// get iterator to the appropriate vector of TH1 histos
					// for each bin in this profile
					// If it isn't found create a new one
					itrTH1 = binHistoPerProfile->find(chanID);
					if(itrTH1 == binHistoPerProfile->end()){
						vector<TH1I*>* temp = new vector<TH1I*>;
						temp->resize(numPhos4Steps,(TH1I*)0);
						(*binHistoPerProfile)[chanID] = temp;
						itrTH1 = binHistoPerProfile->find(chanID);
					}
				}
				
				for(int slice=0;slice<t->L1CaloPPM_hadADC->at(tt).size();slice++){
					uint ADC = t->L1CaloPPM_hadADC->at(tt)[slice];
					
					unsigned int binNumber = 0;
					binNumber = slice*25+stepNumber;
					
					itr->second->Fill(binNumber,ADC);
					
					// if this channel has a saturated slice I want to know
					if(ADC == 0x3ff)
						satItr->second = true;
					
					// fill in TH1 histo for this binNumber
					// if histo hasn't been created yet, create it
					if(chanID == chanSelect){
						//cerr << "slice: " << slice << " bin: " << binNumber << " stepNumber: " << stepNumber << endl;
						if(binNumber >= numPhos4Steps){
							cerr << "Error here: bin: " << binNumber << " numPhos4Steps: " << numPhos4Steps << "\n";
						}
						else{
							if((*itrTH1->second)[binNumber] == (TH1I*)0){
								char tempName[100];
								sprintf(tempName,"prof_%08x_%03i",chanID,binNumber);
								char tempTitle[100];
								sprintf(tempName,"Bin %03i of Profile plot for channel %08x",binNumber,chanID);
								
								(*itrTH1->second)[binNumber] = new TH1I(tempName,tempTitle,1024,0,1024);
							}
							(*itrTH1->second)[binNumber]->Fill(ADC);
						}
					}
				}
			}
			
			// Fill the Electromagnetic channels if they are filled
			if(t->L1CaloPPM_emIsFilled->at(tt)){
				const unsigned int numTimeSlices = t->L1CaloPPM_emADC->at(tt).size();
				const unsigned int numPhos4Steps = numTimeSlices*numNanosecPerTimeSlice;
				
				
				uint chanID = t->L1CaloPPM_emChannelId->at(tt);
				
				// want to see which channels are saturated
				map<unsigned int,bool>::iterator satItr = satChannelOutToFile->find(chanID);
				// if no entry is found, create one
				if(satItr == satChannelOutToFile->end()){
					(*satChannelOutToFile)[chanID] = false;
					satItr = satChannelOutToFile->find(chanID);
				}
				
				map<uint,TProfile*>::iterator itr = mProf->find(chanID);
				if(itr == mProf->end()){
					char name[100];
					sprintf(name,"prof_%08x",t->L1CaloPPM_emChannelId->at(tt));
					char title[100];
					sprintf(title,"Profile of PHOS4 Steps in %08x",t->L1CaloPPM_emChannelId->at(tt));
					(*mProf)[chanID] = new TProfile(name,title,numPhos4Steps,0,numPhos4Steps,0,1024);
					itr =  mProf->find(chanID);
				}
				
				map<unsigned int, vector<TH1I*>* >::iterator itrTH1;
				if(chanID == chanSelect){
					// get iterator to the appropriate vector of TH1 histos
					// for each bin in this profile
					// If it isn't found create a new one
					itrTH1 = binHistoPerProfile->find(chanID);
					if(itrTH1 == binHistoPerProfile->end()){
						vector<TH1I*>* temp = new vector<TH1I*>;
						temp->resize(numPhos4Steps,(TH1I*)0);
						(*binHistoPerProfile)[chanID] = temp;
						itrTH1 = binHistoPerProfile->find(chanID);
					}
				}
				
				for(int slice=0;slice<t->L1CaloPPM_emADC->at(tt).size();slice++){
					uint ADC = t->L1CaloPPM_emADC->at(tt)[slice];
					
					unsigned int binNumber = 0;
					binNumber = slice*25+stepNumber;
					
					itr->second->Fill(binNumber,ADC);
					
					// if this channel has a saturated slice I want to know
					if(ADC == 0x3ff)
						satItr->second = true;
					
					// fill in TH1 histo for this binNumber
					// if histo hasn't been created yet, create it
					if(chanID == chanSelect){
						
						//cerr << "slice: " << slice << " bin: " << binNumber << " stepNumber: " << stepNumber << endl;
						
						if(binNumber >= numPhos4Steps){
							cerr << "EM Error here: bin: " << binNumber << " numPhos4Steps: " << numPhos4Steps << "\n";
						}
						else{
							if((*itrTH1->second)[binNumber] == (TH1I*)0){
								char tempName[100];
								sprintf(tempName,"prof_%08x_%03i",chanID,binNumber);
								char tempTitle[100];
								sprintf(tempName,"Bin %03i of Profile plot for channel %08x",binNumber,chanID);
								
								(*itrTH1->second)[binNumber] = new TH1I(tempName,tempTitle,1024,0,1024);
							}
							(*itrTH1->second)[binNumber]->Fill(ADC);
						}
					}
				}
			}
			
			
		}
		
	}// end for(entries)
	
	map<uint,uint> robValue;
	uint slotAve=0;
	uint slotCounter=0;
	
// 	FermiFunc* fermiFitFunc = new FermiFunc;
// 	TF1* fermiFit = new TF1("fermiFit",fermiFitFunc,0,128,4);
// 	fermiFit->SetParameters(600,25,10,40);
// 	fermiFit->FixParameter(3,40);
// 	fermiFit->SetLineColor(kBlue);
// 	
	
	LandGaussFunc* fitFunc = new LandGaussFunc;
	TF1* fit = new TF1("fit",fitFunc,0,globalNumPhos4Steps,5);
	fit->SetParameter(0,50);
	fit->SetParameter(1,500);
	fit->SetParameter(2,20);
	fit->SetParameter(3,20);
	fit->FixParameter(4,40);
	
	
	vector<double> empty;
	empty.resize(4,0);
	
	map<uint,vector<double> > sumList;
	map<uint,vector<double> > sum2List;
	
	map<uint,double> sumChi;
	map<uint,double> sum2Chi;
	
	map<uint,uint> nList;
	
	TCanvas *canvas;
	
	TFile* rootFile = new TFile("pulseFitter.root","RECREATE");
	
	// Filename for postscript output
	string psfilename = "pulseFitter.ps";
	
	// File used to output the channel IDs which saturated
	string satChanFilename = "saturatedChannels.txt";
	ofstream satOutFile(satChanFilename.c_str());
	if(!satOutFile)
		cerr << "Error opening file: " << satChanFilename << endl;
	
	// ROOT File for TH1I histograms of bins of Profiles
	TFile* rootFileTh1 = new TFile("pulseFitterTh1.root","RECREATE");
	
	for(int crate=0;crate<8;crate++){
		cerr << "Crate: " << crate << endl;
		for(int mod=0;mod<16;mod++){
			cerr << "Ppm: " << mod << endl;
			
			canvas = new TCanvas("canvas","canvas",0,0,1200,900);
			canvas->SetBatch(kTRUE);
			canvas->Divide(8,8);
			
			
			for(int submod=0;submod<16;submod++){
				for(int chan=0;chan<4;chan++){
					
					
					
					uint maxValue=0;
					uint maxSlot=0;
					
					uint chanID = ((crate & 0xff) << 24) | ((0x1) << 20) | ((mod & 0xf) << 16) | ((submod & 0xff) << 8) | (chan & 0xff);
					
					// Output which channels had saturated ADCs
					map<unsigned int,bool>::iterator satItr = satChannelOutToFile->find(chanID);
					// if no entry is found, create one
					if(satItr == satChannelOutToFile->end()){
						;// do nothing
					}
					else{
						if(satItr->second)
							satOutFile << "Channel ID: 0x " << hex << satItr->first << dec << endl;
					}
					
					// Want to output my TH1I histograms to a root file
					if(chanID == chanSelect){
						map<unsigned int,vector<TH1I*>* >::iterator itrTH1 = binHistoPerProfile->find(chanID);
						if(itrTH1 == binHistoPerProfile->end()){
							;//do nothing
						}
						else{
							rootFileTh1->cd();
							for(unsigned int step=0; step<globalNumPhos4Steps;step++){
								itrTH1->second->at(step)->Write();
							}
							rootFile->cd();
						}
					}
					
					
					//cerr << "ChanID: " << chanID << endl;
					//cerr << "Crate: " << crate << " ppm: " << mod << " mcm: " << submod << " chan: " << chan << endl;
					
					map<uint,TProfile*>::iterator itr = mProf->find(chanID);
					if(itr == mProf->end()) continue;
					
					// Write the profile to the file
					rootFile->cd();
					itr->second->Write();
					
					
					fit->SetParameter(0,itr->second->GetMean(1));
					fit->SetParameter(1,700);
					fit->SetParameter(2,23);
					fit->SetParameter(3,15);
					
					itr->second->Fit(fit,"rbq");
					
					const double mean = fit->GetParameter(0);
					const double amp  = fit->GetParameter(1);
					const double sigma_g = fit->GetParameter(2);
					const double sigma_l = fit->GetParameter(3);
					
					
					// Draw to canvas
					canvas->cd(submod*4 + chan + 1);
					
					itr->second->Draw();
					
					
					if(amp > 300  && amp < 1000000 
						&& sigma_g > 0 && sigma_l > 0){
						
						//fermiFit->SetRange(0,fit->GetParameter(0)+2);
						
						//itr->second->Fit(fermiFit,"rb");
						
						//fermiFit->SetRange(0,125);
						
						uint index = 0;
						for(uint i=1;i<20;i++)
							if( (100*i) < amp && amp < ((100*i) + 100) ){
								index = (100*i);
								break;
							}
						
						
						//cerr << fit->GetParameter(1) << " " << index << endl;
						
						
						map<uint,vector<double> >::iterator sumItr = sumList.find(index);
						if(sumItr == sumList.end()){
							sumList[index] = empty;
							sumItr = sumList.find(index);
						}
						
						sumItr->second[0] += mean;
						sumItr->second[1] += amp;
						sumItr->second[2] += sigma_g;
						sumItr->second[3] += sigma_l;
						
						
						
						map<uint,vector<double> >::iterator sum2Itr = sum2List.find(index);
						if(sum2Itr == sum2List.end()){
							sum2List[index] = empty;
							sum2Itr = sum2List.find(index);
						}
						
						sum2Itr->second[0] += mean*mean;
						sum2Itr->second[1] += amp*amp;
						sum2Itr->second[2] += sigma_g*sigma_g;
						sum2Itr->second[3] += sigma_l*sigma_l;
						
						
						
						
						map<uint,double>::iterator sumChiItr = sumChi.find(index);
						if(sumChiItr == sumChi.end()){
							sumChi[index] = 0;
							sumChiItr = sumChi.find(index);
						}
						
						sumChiItr->second += fit->GetChisquare();
						
						
						map<uint,double>::iterator sum2ChiItr = sum2Chi.find(index);
						if(sum2ChiItr == sum2Chi.end()){
							sum2Chi[index] = 0;
							sum2ChiItr = sum2Chi.find(index);
						}
						
						sum2ChiItr->second += fit->GetChisquare()*fit->GetChisquare();
						
						
						map<uint,uint>::iterator nItr = nList.find(index);
						if(nItr == nList.end()){
							nList[index] = 0;
							nItr = nList.find(index);
						}
						
						nItr->second++;
						//cerr << "n: " << nItr->second << endl;
						
//  						cerr << "Reduced Chi2: " << (double)(fit->GetChisquare() /fit->GetNDF()) << endl;
//  						canvas->Update();
 						
//  						cin.get();
					}
					
					
					
				}
				
			}
			
			canvas->Update();
			if(crate == 0 && mod == 0){
				string temp = psfilename + "(";
				canvas->SaveAs(temp.c_str());
			}
			else if(crate == 7 && mod == 15){
				string temp = psfilename + ")";
				canvas->SaveAs(temp.c_str());
			}
			else
				canvas->SaveAs(psfilename.c_str());
			
			delete canvas;
			canvas = 0;
			
		}
		
	}
	
	rootFile->Close();
	delete rootFile;
	
	rootFileTh1->Close();
	delete rootFileTh1;
	
	delete binHistoPerProfile;
	
	satOutFile.close();
	delete satChannelOutToFile;
	
	string outFilename = "fitPars.txt";
	ofstream outFile(outFilename.c_str());
	if(!outFile)
		cerr << "Error opening file: " << outFilename << endl;
	
	map<uint,vector<double> >::iterator sumItr = sumList.begin();
	map<uint,vector<double> >::iterator sum2Itr = sum2List.begin();
	map<uint,double>::iterator sumChiItr = sumChi.begin();
	map<uint,double>::iterator sum2ChiItr = sum2Chi.begin();
	map<uint,uint>::iterator nItr = nList.begin();
	while(nItr != nList.end()){
		
		cerr << "Index: " << nItr->first << "   Entries: " << nItr->second << endl;
		outFile << "Index: " << nItr->first << "   Entries: " << nItr->second << endl;
		
		for(int i=0;i<sumItr->second.size();i++){
			double mean = sumItr->second[i]/(double)nItr->second;
			double sigma = sqrt( (1.0/(double)nItr->second)*sum2Itr->second[i] - mean*mean);
			
			cerr << "   Parameter: " << i << " Mean: " << mean << " Sigma: " << sigma << endl;
			outFile << "   Parameter: " << i << " Mean: " << mean << " Sigma: " << sigma << endl;
			
			
		}
		
		double meanChi = sumChiItr->second/(double)nItr->second;
		double sigmaChi = sqrt( (1.0/(double)nItr->second)*sum2ChiItr->second - meanChi*meanChi);
		
		cerr << "   Chi^2:   Mean: " << meanChi << " Sigma: " << sigmaChi << endl;
		outFile << "   Chi^2:  Mean: " << meanChi << " Sigma: " << sigmaChi << endl;
		
		
		nItr++;sumItr++;sum2Itr++;sumChiItr++;sum2ChiItr++;
	}
	outFile.close();
	
	//app->Run();
	exit(0);
	
	return 0;
}

