//#include "VectorVectorDict.h"
#include "TrigEgammaNtuple_v1.h"

#include <TROOT.h>
#include <TChain.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TFile.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <cfloat>

enum mainMode { READ_FILE, READ_LIST, HELP};
enum mainMode mode;

int nEvent=-1;
std::string fileListName;
std::string outPutFileName="HistoOut.root";
std::vector<std::string> files;

void getParams(int argc, char **argv) {
  int ip = 1;
  mode = HELP;
  while (ip < argc) {
    if (std::string(argv[ip]).substr(0,2) == "--") {
      if (std::string(argv[ip]) == "--help") {
	mode = HELP;
	break;
      } else if (std::string(argv[ip]) == "--Ev") {
	if (ip+1 < argc && std::string(argv[ip+1]).substr(0,2) != "--" ) {
	  nEvent = atoi(argv[ip+1]);
	  std::cout << "Selected Number of Events is: " << nEvent << std::endl;
	  ip++; 
	} else  {
	  mode = HELP;
	  std::cout << std::endl << "No number of Event inserted" << std::endl << std::endl;
	  break;
	}
        ip++; 
      } else if (std::string(argv[ip]) == "--list") {
	if (ip+1 < argc && std::string(argv[ip+1]).substr(0,2) != "--") {
	  fileListName = argv[ip+1];
	  ip += 2; 
	  mode = READ_LIST;
	} else {
	  mode = HELP;
	  std::cout << std::endl << "No fileList name inserted" << std::endl << std::endl;
	  break;
	}
      } else if (std::string(argv[ip]) == "--out") {
	if (ip+1 < argc && std::string(argv[ip+1]).substr(0,2) != "--") {
	  outPutFileName = argv[ip+1];
	  ip += 2; 
	} else {
	  mode = HELP;
	  std::cout << std::endl << "No outPutFileName name inserted" << std::endl << std::endl;
	  break;
	}
      } else if (std::string(argv[ip]) == "--file") {
	int loop=ip+1;
	int count=0;;
	while (loop < argc && std::string(argv[loop]).substr(0,2)!= "--" && std::string(argv[loop]).find(".root")!=std::string::npos) {
	  files.push_back(argv[loop]);
	  loop++;
	  ip++;
	  count++;
	} 
	if (count!=0) {
	  std::cout << count << " file(s) inserted" << std::endl;
	  ip++;
	  mode = READ_FILE;
	} else {
	  mode = HELP;
	  std::cout << std::endl << "No file inserted" << std::endl << std::endl;
	  break;
	}
      }
    } else {
      std::cout << std::endl << "COMMAND: '" << std::string(argv[ip]) << "' unknown!!!" << std::endl << std::endl;
      mode = HELP;
      break;
    }
  }
}

void help() {
  std::cout << "Usage: ./ReadNtuple.exe --list <listFileName>\n"
	    << "            // Read all the ntuple files specified in the file list\n\n" 
	    << "Usage: ./ReadNtuple.exe --file <file1> <file2> <file3>  .... \n"
	    << "            // Read all the ntuple files \n\n" 
	    << "     Optional switches:\n"
	    << "--Ev <nEvents>   Sets the max number of Events\n" << std::endl;
  exit(-1);
} 


int main(int argc, char **argv) {
  
  getParams(argc, argv);  
  TrigEgammaNtuple_v1* mainClas;
  
  if (mode == HELP) {
    help();
  } else if (mode == READ_LIST) {
    std::cout << "The fileList name is: " << fileListName << std::endl;
    std::cout << std::endl << "SORRY!: this funcion is not yet implemented" << std::endl << std::endl;
  } else if (mode == READ_FILE) {
    for (unsigned int i=0; i<files.size(); i++) {
      std::cout << std::endl << "Loading File: " << files[i] << std::endl;
      if (i==0) {
	TFile *f=new TFile(files[i].c_str()); 
	mainClas=new TrigEgammaNtuple_v1(f,outPutFileName);
      } else {
	TFile *f=new TFile(files[i].c_str()); 
	mainClas->addFile(f);
      }
    }

    mainClas->Init();
    mainClas->SetnEntries(nEvent);
    std::cout << " The Total Number of Event is " << mainClas->GetEntries() << " (" << nEvent << ") " << std::endl;
    mainClas->Loop();
  }
}
