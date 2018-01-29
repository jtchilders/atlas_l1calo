#include <ScopeFile.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include <TAxis.h>

ScopeFile::ScopeFile(std::string filename,std::string name,std::string title){
   
   m_maxVoltageInMilliVolts = 0;
   m_timeOfMaxVoltageInNanoSeconds = -9999;
   
   // open file
   std::ifstream *file = new std::ifstream(filename.c_str());
   
   //loop over each line and extract information
   char line[500];
   
   // skip first five lines
   file->getline(line,500); // 1
   file->getline(line,500); // 2
   file->getline(line,500); // 3
   file->getline(line,500); // 4
   file->getline(line,500); // 5
   
   std::vector<float> m_time;
   std::vector<float> m_voltage;
   
   double xMin = 99999.;
   double xMax = -99999.;
   
   // loop over remaining lines in file
   while(file->getline(line,500)){
      
#ifdef DEBUG
      std::cout << "line: " << line << " ";
#endif
      
      // copy line to stringstream
      std::stringstream sline(line);
      
      //if(sline.str().size() == 0) continue;
      
      float timeInSeconds = 0;
      float voltageInVolts = 0;
      
      // use getline function to extract first string before the comma
      char number[50];
      sline.getline(number,50,',');
      
#ifdef DEBUG
      std::cout << "number: " << number << " ";
#endif
      
      // convert line to integer
      std::stringstream stime(number);
      stime >> timeInSeconds;
      
      // use getline function to extract second string after the comma
      sline.getline(number,50);
      
#ifdef DEBUG
      std::cout << "number: " << number << " ";
#endif
      
      // convert line to integer
      std::stringstream svoltage(number);
      svoltage >> voltageInVolts;
      
      float timeInNs = timeInSeconds*1e9;
      float voltageInMilliVolts = voltageInVolts*1000.;
      
      m_time.push_back(timeInNs); 
      m_voltage.push_back(voltageInVolts);
      
#ifdef DEBUG
      std::cout << " time: " << timeInNs << " voltage: " << voltageInMilliVolts << std::endl;
#endif
      
      // looking for peak and peak location
      if(m_maxVoltageInMilliVolts < voltageInMilliVolts){
         m_maxVoltageInMilliVolts = voltageInMilliVolts;
         m_timeOfMaxVoltageInNanoSeconds = timeInNs;
      }
      
      // get x range
      if(xMin > timeInNs) xMin = timeInNs;
      if(xMax < timeInNs) xMax = timeInNs;
      
   }
   // done with the file
   file->close();
   delete file;
   file = 0;
   
   
   // want the peak at zero to normalize all the pulses.
   //for(unsigned int i=0;i<m_time.size();++i){
   //   m_time[i] -= m_timeOfMaxVoltageInNanoSeconds;
   //}
   
   
   m_graph = new TGraph(m_time.size(),&m_time[0],&m_voltage[0]);
   //m_graph->SetName(name.c_str());
   //m_graph->SetTitle(title.c_str());
   //m_graph->GetXaxis()->SetTitle("Time [ns]");
   //m_graph->GetYaxis()->SetTitle("Voltage [V #approx 100GeV]");
   //m_graph->GetXaxis()->SetLimits(-200,700);
   //m_graph->SetMaximum(3.2);
   //m_graph->SetMinimum(-1.0);
   
   
   // Fit around peak with a gaus
   m_gausFit = 0;
   if(m_timeOfMaxVoltageInNanoSeconds != -9999){
      m_gausFit = new TF1("gausFit","gaus", m_timeOfMaxVoltageInNanoSeconds-14, m_timeOfMaxVoltageInNanoSeconds+14);
      m_graph->Fit(m_gausFit,"rqn");
      m_maxVoltageInMilliVolts = m_gausFit->GetParameter(0)*1000;
      m_timeOfMaxVoltageInNanoSeconds = m_gausFit->GetParameter(1);
      m_gausFit->SetLineColor(kRed);
   }
   
   m_prof = new TProfile((name+"_profile").c_str(),"",900,-200.,700.);
   
   // want the peak at zero to normalize all the pulses.
   for(unsigned int i=0;i<m_time.size();++i){
      m_time[i] -= m_timeOfMaxVoltageInNanoSeconds;
      
      m_prof->Fill(m_time[i],m_voltage[i]);
   }
   
   
   m_prof->GetXaxis()->SetTitle("Time [ns]");
   m_prof->GetYaxis()->SetTitle("Voltage [1V #approx 100GeV]");
   m_prof->GetXaxis()->SetLimits(-200,700);
   m_prof->SetMaximum(3.2);
   m_prof->SetMinimum(-1.0);
   m_prof->SetMarkerStyle(20);
   m_prof->SetMarkerSize(0.6);
   
   
   delete m_graph;
   m_graph = 0;
   
   
   m_graph = new TGraph(m_time.size(),&m_time[0],&m_voltage[0]);
   m_graph->SetName(name.c_str());
   //m_graph->SetTitle(title.c_str());
   m_graph->GetXaxis()->SetTitle("Time [ns]");
   m_graph->GetYaxis()->SetTitle("Voltage [1V #approx 100GeV]");
   m_graph->GetXaxis()->SetLimits(-200,700);
   m_graph->SetMaximum(3.2);
   m_graph->SetMinimum(-1.0);
   m_graph->SetMarkerStyle(20);
   m_graph->SetMarkerSize(0.6);
   
   
   
   
}

ScopeFile::~ScopeFile(void){
   delete m_graph;
   m_graph = 0;
   
   if(m_gausFit != 0) delete m_gausFit;
   m_gausFit = 0;
   
   delete m_prof;
   m_prof = 0;
}



