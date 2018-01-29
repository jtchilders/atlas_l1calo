#include "commandLineParser.h"


CommandLineTool::CommandLineTool(int inArgc,char** inArgv){
	argc = inArgc;
	argv = inArgv;
	
	fileList = false;
	skipJemEndCap = false;
	
	if(argc < 2){
		cerr << "CommandLineTool::CommandLineTool: Error, should be atleast 2 arguments, but only " << argc << " were given.\n";
		PrintUsage();
		return;
	}
	
	ParseCommandLine();
}

void CommandLineTool::ParseCommandLine(void){
	
	// Loop over arguments
	for(int i=1;i<argc;i++){
		string arg = argv[i];
		if(arg.find("-fl") != string::npos){
			fileList=true;
			continue;
		}
		else if(arg.find("-pd") != string::npos){
			skipJemEndCap=true;
			continue;
		}
		else if(i == (argc - 1)){
			filename = arg;
			continue;
			
		}
		else{
			cerr << "CommandLineTool::ParseCommandLine: Error, Unrecognized arguments.\n";
			PrintUsage();
			return;
		}
		
		
	}
	
}

void CommandLineTool::PrintUsage(void){
	cerr << "Usage: " << argv[0] << " [-fl] [-pd] <filename>\n";
	cerr << "      -fl is used if <filename> is a list of files\n";
	cerr << "             with the directory path in the first line\n";
	cerr << "             Otherwise <filename> is expected to be a\n";
	cerr << "             root file.\n";
	cerr << "      -pd is used to skip the End Cap region for JEM\n";
	cerr << "             plots due to unused PPM channels\n";
	cerr << "             needed for [p]layback and [d]ac scans\n";
	cerr << "             NOT USED FOR ALL EXECUTABLES.\n";
	cerr << "\n";
	
}
