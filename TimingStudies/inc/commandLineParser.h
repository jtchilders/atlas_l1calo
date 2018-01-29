#ifndef COMMANDLINEPARSER_H
#define COMMANDLINEPARSER_H


#include <iostream>
#include <string>

using namespace std;

class CommandLineTool{
public:
	CommandLineTool(int,char**);
	
	void ParseCommandLine(void);
	
	bool IsFileList(void){return fileList;};
	bool SkipJemEndCap(void){return skipJemEndCap;};
	
	string GetFilename(void){return filename;};
	
private:
	// passed a fileList
	bool fileList;
	string filename;
	
	int argc;
	char **argv;
	
	void PrintUsage();
	
	// skip End Cap regions in JEM maps
	// this is here because of unused PPM channels
	// which are included in the sums
	bool skipJemEndCap;
};


#endif

