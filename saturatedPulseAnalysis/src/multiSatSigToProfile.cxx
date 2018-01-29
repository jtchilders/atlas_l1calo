
#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>

#include "TApplication.h"
#include "TCanvas.h"
#include "TProfile.h"
#include "TH1I.h"
#include "TFile.h"
#include "TStyle.h"
#include "TList.h"
#include "TKey.h"
#include "TGaxis.h"

#include <tclap/CmdLine.h>

int main(int argc, char** argv){
	
	/// Setup the gStyle environment
	#include "gStyleSetup.h"
	
	std::vector<std::string> inputFilenames;
   std::vector<unsigned int> inputDacValues;
	
	TCLAP::CmdLine* cmd;
	try{
		cmd = new TCLAP::CmdLine("This program will take many root file containing profile histograms of saturated phos4 pulse shapes and perform an analysis of the signals.",' ',"0.1");
		
		// Defining the arguments that are allowed
		
		// Require input filename
		TCLAP::MultiArg<std::string> inputFilenameArg("n","inputFilename","Input ROOT filename with pulse shape profile plots",true,"string");
		cmd->add(inputFilenameArg);
      
      TCLAP::MultiArg<unsigned int> inputDacValuesArg("d","inputDacValue","For each file passed there should be one charge injection DAC value for that run passed in the same order. I assume that they are entered in ascending order.(TILE ONLY)",false,"integer");
		cmd->add(inputDacValuesArg);
      
		cmd->parse(argc,argv);
		
		inputFilenames = inputFilenameArg.getValue();
		inputDacValues = inputDacValuesArg.getValue();
      
      if(inputDacValues.size() != 0 && inputDacValues.size() != inputFilenames.size()){
         std::cerr << "ERROR: Number of root files does not correspond to the number of DAC values passed on command line.\n";
         return -1;
      }
	}
	catch (TCLAP::ArgException &e){
		std::cerr << "command line parse error: " << e.error() << " for arg " << e.argId() << std::endl;
		return -1;
	}
	
	TApplication app("app",&argc,argv);
	
	// Open each file as a root file
	std::vector<TFile*> inputFiles;
	for(unsigned int i=0;i<inputFilenames.size();i++){
		TFile* inputFile = new TFile(inputFilenames[i].c_str(),"READ");
		inputFiles.push_back(inputFile);
	}
   TFile* outputFile = new TFile("multiSatSigToProfile.root","RECREATE");
   
	// Get the key lists from the files
	std::vector<TList*> keyLists;
	for(unsigned int i=0;i<inputFilenames.size();i++){
      inputFiles[i]->cd();
      inputFiles[i]->cd("PpmPhos4Analysis");
      gDirectory->cd("CleanSignalProfiles");
      
		TList* keyList = gDirectory->GetListOfKeys();
		if(keyList->GetEntries() == 0){
			std::cerr << inputFilenames[i] << " has no histograms in it.\n";
			return 0;
		}
		
		keyLists.push_back(keyList);
	}
	
   
   // Fill vector with Delta DAC values
   std::vector<unsigned int> deltaDac;
   for(unsigned int i=0;i+1<inputDacValues.size();i++){
      deltaDac.push_back(inputDacValues[i+1]-inputDacValues[i]);
   }
   
	
	TCanvas can("can","can",0,0,1200,600);
// 	can.Divide(2);
	
	/////////////////////////
	/// For the moment I am assuming that the key from each file
	/// is the same such that Key == 0 refers to the same cool ID
	/// in all files
	///////////////////////////
	
   // assuming pedestal of 40 for signal shape cut
   const double pedestal = 40;
   const unsigned int selectedChannel = 0x06120101;
   std::vector<Color_t> colors;
   colors.push_back(kBlack);
   colors.push_back(kRed);
   colors.push_back(kOrange);
   colors.push_back(kYellow);
   colors.push_back(kGreen);
   colors.push_back(kCyan);
   colors.push_back(kBlue);
   colors.push_back(kViolet);
   
	// Loop over the Profiles in this file
	for(int key=0;key<keyLists[0]->GetEntries();key++){
		
		if( !(key % (int(keyLists[0]->GetEntries()*0.01) + 1)))
			std::cerr << "\r Percent Done: " << int(((float)key/(float)keyLists[0]->GetEntries())*100) << "\t";
      
      
      // grab the actual histogram pointer.
      std::vector<TProfile*> profs;
      for(unsigned int i=0;i<inputFilenames.size();i++){
         TKey* histoKey = (TKey*)keyLists[i]->At(key);
         
         TProfile* prof = (TProfile*)histoKey->ReadObj();
         profs.push_back(prof);
      }
      
      // need to extract the cool ID
      std::string histoName = profs[0]->GetName();
      unsigned int coolIdLocation = histoName.find('_')+1;
      std::string strCoolId = histoName.substr(coolIdLocation,8);
      unsigned int coolID = 0;
      sscanf(strCoolId.c_str(),"%x",&coolID);
      
      // need to calculate the mean pedestal for all signals
      std::vector<double> meanPedestal,sigmaPedestal;
      for(unsigned int i=0;i<profs.size();++i)
      {
         double pedSum = 0,pedSum2 = 0;
         unsigned int pedN = 0;
         unsigned int pedStartBin = 1,pedEndBin = 26;
         for(unsigned int bin=pedStartBin;bin<pedEndBin;++bin){
            pedSum += profs[i]->GetBinContent(bin);
            pedSum2 += profs[i]->GetBinContent(bin)*profs[i]->GetBinContent(bin);
            pedN++;
            
         }
         double meanPed = (pedN == 0) ? 0 : pedSum/(double)pedN;
         double sigmaPed = (pedN == 0) ? 0 : sqrt((1.0/(double)pedN)*pedSum2 - meanPed*meanPed);
         
         meanPedestal.push_back(meanPed);
         sigmaPedestal.push_back(sigmaPed);
      }
      
      TH1F* normPulse;
      {
         // first I want to cut out all histograms that are no good
         // I've determined that cutting on the rising edge instantaneous
         // slope eliminates funny signal shapes.
         TProfile* testProf = profs[0];
         
         // find the peak location
         unsigned int peakBin = 0;
         double peakValue = 0;
         for(unsigned int bin=1;bin<testProf->GetNbinsX();bin++){
            if(peakValue < testProf->GetBinContent(bin)){
               peakBin = bin;
               peakValue = testProf->GetBinContent(bin);
            }
         }
         
         const double peakHeight = peakValue - meanPedestal[0];
         const double valueAt10 = peakHeight*0.10 + meanPedestal[0];
         const double valueAt90 = peakHeight*0.90 + meanPedestal[0];
         
         // calculate the mean instantaneous slope of the rising edge
         double sum=0,sum2=0;
         unsigned int n=0;
         for(unsigned int bin=1;bin<testProf->GetNbinsX();bin++){
            double y2 = testProf->GetBinContent(bin);
            double y1 = 0;
            if(bin > 1) y1 = testProf->GetBinContent(bin-1);
            
            double x2 = (double)bin;
            double x1 = double(bin-1);
            
            double dydx = (y2 - y1)/(x2 - x1);
            double intercept = y2 - dydx*x2;
            
            // only include the slope if it is within the 10% and 90% marks
            // AND only include slope values from rising edge
            if(valueAt10 <= y2 && y2 <= valueAt90 && bin < peakBin){
               sum += dydx;
               sum2 += dydx*dydx;
               n++;
            }
            
         }
         
         // calculate the mean/sigma of instantaneous slopes on rising edge
         double meanSlope = (n==0) ? 0 : sum/(double)n;
         double sigmaSlope = (n==0) ? 0 : sqrt((1.0/(double)n)*sum2-meanSlope*meanSlope);
         
         // make the cut on the sigma in the instantaneous slopes
         if(!(2.0 < sigmaSlope && sigmaSlope < 10.0)) continue;
         
         /// Now I will be calculating a normalized pulse shape using the lowest energy pulse
         normPulse = new TH1F("normPulse","normalized pulse shape",testProf->GetNbinsX(),0,testProf->GetNbinsX());
         
         // I will normalize to the peak of the pulse height
         double d_peakHeight = sqrt( testProf->GetBinError(peakBin)*testProf->GetBinError(peakBin) + sigmaPedestal[0]*sigmaPedestal[0] );
         for(unsigned int bin=1;bin<=testProf->GetNbinsX();++bin){
            
            double adc_adjusted = testProf->GetBinContent(bin) - meanPedestal[0];
            double d_adc_adjusted = sqrt( testProf->GetBinError(bin)*testProf->GetBinError(bin) + sigmaPedestal[0]*sigmaPedestal[0] );
            
            double ratio = adc_adjusted/peakHeight;
            
            double d_ratio_a = (1.0/peakHeight)*d_adc_adjusted;
            double d_ratio_b = (-adc_adjusted/(peakHeight*peakHeight))*d_peakHeight;
            double d_ratio = sqrt( d_ratio_a*d_ratio_a + d_ratio_b*d_ratio_b );
            
            if(ratio < 0) ratio = 0;
            normPulse->SetBinContent(bin,ratio);
            normPulse->SetBinError(bin,d_ratio);
            
         }
      }
      
      
      char tempName[100];
      sprintf(tempName,"deltaAdc_%08x",coolID);
		char tempTitle[100];
      sprintf(tempTitle,"Profile of mean ADC differences for cool ID: 0x%08x",coolID);
      TProfile tmpProf(tempName,tempName,profs[0]->GetNbinsX(),0,profs[0]->GetNbinsX());
		for(unsigned int bin=1;bin<=profs[0]->GetNbinsX();bin++){
			
			for(unsigned int i=0;i+1<inputFilenames.size();i++){
				if(profs[i+1]->GetBinContent(bin) != 0x3ff && profs[i]->GetBinContent(bin) != 0x3ff &&
               !(profs[i+1]->GetBinContent(bin) == 0 || profs[i]->GetBinContent(bin) == 0)){
					double dy = profs[i+1]->GetBinContent(bin) - profs[i]->GetBinContent(bin);
               
					double norm_dy = dy/deltaDac[i];
					
					tmpProf.Fill(bin-1,norm_dy);
					
				}
			}
		}
		
      
		outputFile->cd();
      tmpProf.Write();
      
      
      {
         // set which profile to use
         const unsigned int entry = 1;
         TProfile* prof = profs[entry];
         // now I can fit the normalized pulse to the next biggest pulse
         
         
         unsigned int lowBin = 127;
         unsigned int highBin = 145;
         
         double peakSum=0,peakSum2=0;
         unsigned int peakN=0;
         
         double chi2=0;
         for(unsigned int bin=1;bin<=tmpProf.GetNbinsX();++bin){
            if((lowBin <= bin && bin < highBin)){
               double adc_predicted = tmpProf.GetBinContent(bin)*inputDacValues[entry];
               double d_adc_predicted = tmpProf.GetBinError(bin)*inputDacValues[entry];
               
               double predictedPeakValue = adc_predicted/normPulse->GetBinContent(bin);
               std::cerr << predictedPeakValue << std::endl;
               
               double d_predictedPeakValue_a = (1.0/normPulse->GetBinError(bin))*d_adc_predicted;
               double d_predictedPeakValue_b = (-adc_predicted/ (normPulse->GetBinContent(bin)*normPulse->GetBinContent(bin)) ) * normPulse->GetBinError(bin);
               double d_predictedPeakValue = sqrt( d_predictedPeakValue_a*d_predictedPeakValue_a + d_predictedPeakValue_b*d_predictedPeakValue_b );
               
               peakSum += predictedPeakValue;
               peakSum2 += predictedPeakValue*predictedPeakValue;
               peakN++;
               
               chi2 += (adc_predicted - prof->GetBinContent(bin))*(adc_predicted - prof->GetBinContent(bin))/(d_adc_predicted*d_adc_predicted + prof->GetBinError(bin)*prof->GetBinError(bin));
               
//                std::cerr << prof->GetBinContent(bin) << " " << predictedADC << std::endl;
            }
         }
         
//          std::cerr << "  chi2/NDF: " << (chi2/(highBin-lowBin)) << std::endl;
         
         double meanPeak = (peakN == 0) ? 0 : peakSum/(double)peakN;
         double sigmaPeak = (peakN == 0) ? 0 : sqrt( (1.0/(double)peakN)*peakSum2 - meanPeak*meanPeak);
         
         std::cerr << "\n    peak: " << meanPeak << " +/- " << sigmaPeak << std::endl;
         
         TH1F predictedPulse("predictedPulse","predictedPulse",normPulse->GetNbinsX(),0,normPulse->GetNbinsX());
         for(unsigned int bin=1;bin<=normPulse->GetNbinsX();++bin){
            
            double adc_predicted = normPulse->GetBinContent(bin)*meanPeak + meanPedestal[entry];
            double d_adc_predicted_a = meanPeak*normPulse->GetBinError(bin);
            double d_adc_predicted_b = normPulse->GetBinContent(bin)*sigmaPeak;
            double d_adc_predicted = sqrt( d_adc_predicted_a*d_adc_predicted_a + d_adc_predicted_b*d_adc_predicted_b + sigmaPedestal[entry]*sigmaPedestal[entry] );
            
            predictedPulse.SetBinContent(bin,adc_predicted);
            predictedPulse.SetBinError(bin,d_adc_predicted);
         }
         
         can.cd();
         
         prof->Draw();
         
         predictedPulse.Draw("sameE");
        
         can.Update();
         std::cin.get();
         
         
      }
      
      
      can.cd();
      
      for(unsigned int i=profs.size(),j=0;i>0;i--,j++){
         profs[i-1]->SetMarkerColor(colors[j]);
         if(i == profs.size())
            profs[i-1]->Draw();
         else
            profs[i-1]->Draw("same");
      }
      
//       TH1F sigmas("sigmas","sigmas",tmpProf.GetNbinsX(),0,tmpProf.GetNbinsX());
//       for(unsigned int i=100;i<150;i++){
//          sigmas.SetBinContent(i,tmpProf.GetBinError(i));
//       }
      
      float rightmax = 1.5*tmpProf.GetMaximum();
      float scale = gPad->GetUymax()/rightmax;
      tmpProf.Scale(scale);
      tmpProf.Draw("same");
//       rightmax = 2.0*sigmas.GetMaximum();
//       scale = gPad->GetUymax()/rightmax;
//       sigmas.Scale(scale);
//       sigmas.Draw("same");
      
      
      TGaxis* axis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(),gPad->GetUxmax(),gPad->GetUymax(),0,rightmax,510,"+L");
      axis->SetLineColor(kRed);
      axis->SetLabelColor(kRed);
      axis->Draw();
      
      
      can.Update();
      std::cin.get();
      
	}
   
   std::cerr << "\nClosing file.\n";
	outputFile->Close();
   outputFile->Delete();
   
// 	app.Run();
	
}



