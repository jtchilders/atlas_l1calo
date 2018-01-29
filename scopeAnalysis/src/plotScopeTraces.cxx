
#include <ScopeFile.h>
#include <FileList.h>

#include <TApplication.h>
#include <TGraph.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TTree.h>

#include <iostream>


int main(int argc, char** argv){
   
   if(argc < 3){
      std::cout << " usage: use one of these two ways:\n";
      std::cout << "    -f <filelist.txt> (where filelist.txt is a list of the scope files)\n";
      std::cout << "    -r <traces.root>  (where traces.root is the root file created by the makeTree programs)\n";
      return 0;
   }
   std::string argv1 = argv[1];
   std::string argv2 = argv[2];
   if(argv1.find("-f") != std::string::npos){
      std::cout << " text list of scope traces passed... looping over files.\n";
      FileList fileList(argv2.c_str());
      
      TApplication app("app",&argc,argv);
      
      TCanvas can("can","can",0,0,800,600);
      
      std::cout << "\n size: " << fileList.size() << std::endl;
      
      int plotCount = 0;
      for(unsigned int i=0;i<fileList.size();++i){
         std::cout << "plot: " << i << std::endl;
         
         ScopeFile *trace = new ScopeFile(fileList[i],fileList[i],fileList[i]);
         
         if(trace->getMaxVoltageInMilliVolts() > 20 && trace->getMaxVoltageInMilliVolts() < 9000.){
            if(plotCount == 0)
               trace->Draw("ap");
            else
               trace->Draw("p");
            
            trace->getGraph()->SetMarkerColor(plotCount % 10 + 1);
            //if(trace->getFit() != 0) trace->getFit()->Draw("same");
            
            can.Update();
            std::cout << " file: " << fileList[i] << std::endl;
            std::cout << " max: " << trace->getMaxVoltageInMilliVolts() << " time: " << trace->getTimeOfMaxVoltageInNanoSeconds() << std::endl;
            
            plotCount++;
            
            //TFile file("plot.root","RECREATE");
            //trace->getProfile()->Write();
            //file.Close();
            //return 0;
            
            
            std::cin.get();
         }
         else{
            delete trace;
            trace = 0;
         }
      }
      
      app.Run();
      
   }//end if(-f)
   else if(argv1.find("-r") != std::string::npos){
      std::cout << " ROOT file passed... looping over tree.\n";
      
      TFile file(argv2.c_str(),"READ");
      
      TTree* t = (TTree*)file.Get("scopeTraceTree");
      
      TApplication app("app",&argc,argv);
      
      TGraph* graph = 0;
      TProfile* prof = 0;
      
      t->SetBranchAddress("graph",&graph);
      t->SetBranchAddress("profile",&prof);
      
      TCanvas can("can","can",0,0,600,400);
      
      std::cout << "\n size: " << t->GetEntries() << std::endl;
      
      
      for(unsigned int entry=0;entry<t->GetEntries();++entry){
         std::cout << " plot: " << entry << std::endl;
         t->GetEntry(entry);
         
         if(entry == 0)
            prof->Draw();
         else
            prof->Draw("same");
         
         can.Update();
         
         std::cin.get();
         
      }
      
      file.Close();
      
      app.Run();
      
   }
   else{
      std::cout << " usage: use one of these two ways:\n";
      std::cout << "    -f <filelist.txt> (where filelist.txt is a list of the scope files)\n";
      std::cout << "    -r <traces.root>  (where traces.root is the root file created by the makeTree programs)\n";
      return 0;
   }
   
   
   
   
   return 0;
   
   
}


