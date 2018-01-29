#include "commandLineParser.h"

#include "tclap/CmdLine.h"

CLParse::CLParse(const int argc,char** const argv,std::string progDescr){
   
   m_errorDuringSetup = false;
   
   if(progDescr.empty())
      progDescr = "Default Program Description.";
   
   TCLAP::CmdLine* m_cmd;
   
   try{
      m_cmd = new TCLAP::CmdLine(progDescr.c_str(),' ',"0.1");
      
      // Defining the arguments that are allowed

      // Want to choose Tile OR LArg Only if neither are specified then both are performed
      TCLAP::SwitchArg doTileOnlyArg("t","tileOnly","Perform algorithm on Tile trigger towers.",false);
      m_cmd->add(doTileOnlyArg);
      TCLAP::SwitchArg doLArgOnlyArg("l","largOnly","Perform algorithm on LArg trigger towers.",false);
      m_cmd->add(doLArgOnlyArg);
      
      // Require input filename
      TCLAP::MultiArg<std::string> inputFilenameArg("n","inputFilename","Input ROOT filename with pulse shape profile plots. Should be entered in ascending order according to DAC value.",true,"string");
      m_cmd->add(inputFilenameArg);
      
      // Require input run number for each filename
      TCLAP::MultiArg<unsigned int> inputRunNumberArg("r","runNumber","run number for each ROOT filename. Should be entered in ascending order according to DAC value.",false,"string");
      m_cmd->add(inputRunNumberArg);
      
      // Tile DAC values
      TCLAP::MultiArg<unsigned int> inputDacValuesArg("d","inputDacValue","For each file passed there should be one charge injection DAC value for that run passed in the same order. I assume that they are entered in ascending order.(TILE ONLY)",false,"integer");
      m_cmd->add(inputDacValuesArg);
      
      // LArg DAC Values
      // FCAL
      TCLAP::MultiArg<unsigned int> inputFcalDacValuesArg("f","inputFcalDacValue","For each file passed there should be one charge injection DAC value for the FCAL for that run passed in the same order. I assume that they are entered in ascending order.(LARG ONLY)",false,"integer");
      m_cmd->add(inputFcalDacValuesArg);
      
      // Barrel
      TCLAP::MultiArg<unsigned int> inputBarrelDacValuesArg("b","inputBarrelDacValue","For each file passed there should be one charge injection DAC value for the EM Barrel for that run passed in the same order. I assume that they are entered in ascending order.(LARG ONLY)",false,"integer");
      m_cmd->add(inputBarrelDacValuesArg);
      
      // EMEC
      TCLAP::MultiArg<unsigned int> inputEmecDacValuesArg("e","inputEmecDacValue","For each file passed there should be one charge injection DAC value for the EM End Cap for that run passed in the same order. I assume that they are entered in ascending order.(LARG ONLY)",false,"integer");
      m_cmd->add(inputEmecDacValuesArg);
      
      // EMEC
      TCLAP::MultiArg<unsigned int> inputHecDacValuesArg("i","inputHecDacValue","For each file passed there should be one charge injection DAC value for the HAD End Cap for that run passed in the same order. I assume that they are entered in ascending order.(LARG ONLY)",false,"integer");
      m_cmd->add(inputHecDacValuesArg);
      
      m_cmd->parse(argc,argv);
      
      // Retreive all the values
      m_inputFilenames           = inputFilenameArg.getValue();
      m_inputRunNumbers          = inputRunNumberArg.getValue();
      m_inputTileDacValues       = inputDacValuesArg.getValue();
      m_inputLArgFcalDacValues   = inputFcalDacValuesArg.getValue();
      m_inputLArgBarrelDacValues = inputBarrelDacValuesArg.getValue();
      m_inputLArgEmecDacValues   = inputEmecDacValuesArg.getValue();
      m_inputLArgHecDacValues    = inputHecDacValuesArg.getValue();
      bool doTileOnly          = doTileOnlyArg.getValue();
      bool doLArgOnly          = doLArgOnlyArg.getValue();
      
      // Perform checks and make sure things are congruent
      
      // number of filenames should equal number of runs
      if(m_inputFilenames.size() != m_inputRunNumbers.size() && m_inputRunNumbers.size() != 0){
         std::cerr << "ERROR: number of filenames passed not equal to the number of run numbers passed. See usage for details: -h\n";
         m_errorDuringSetup = true;
         return;
      }  
      
      
      if(doTileOnly && doLArgOnly){
         std::cerr << "ERROR: cannot specify Tile Only AND LArg Only, if you want both, do not specify either. See usage for details: -h\n";
         m_errorDuringSetup = true;
         return;
      }
      else if(doTileOnly)
         m_doLArg = false;
      else if(doLArgOnly)
         m_doTile = false;
      
      
      if(m_doTile && (m_inputTileDacValues.size() != 0 && m_inputTileDacValues.size() != m_inputFilenames.size())){
         std::cerr << "ERROR: Number of root files does not correspond to the number of Tile DAC values passed on command line. Each root file should have a corresponding dac value specified with -d argument. See usage for details: -h\n";
         m_errorDuringSetup = true;
         return;
      }
      
      if(m_doLArg
         && (m_inputLArgFcalDacValues.size() != 0 && m_inputLArgBarrelDacValues.size() != 0 && m_inputLArgEmecDacValues.size() != 0 && m_inputLArgHecDacValues.size() != 0)
         && (m_inputLArgFcalDacValues.size()   != m_inputFilenames.size())
         && (m_inputLArgBarrelDacValues.size() != m_inputFilenames.size())
         && (m_inputLArgEmecDacValues.size()   != m_inputFilenames.size())
         && (m_inputLArgHecDacValues.size()    != m_inputFilenames.size())
         ){
         std::cerr << "ERROR: Number of root files does not correspond to the number of LArg DAC values passed on command line. Each root file should have a corresponding fcal/barrel/emec/hec dac value specified with -f,-b,-e,-i arguments. See usage for details: -h\n";
         m_errorDuringSetup = true;
         return;
      }
      
   }
   catch (TCLAP::ArgException &e){
      std::cerr << "command line parse error: " << e.error() << " for arg " << e.argId() << std::endl;
      m_errorDuringSetup = true;
      return;
   }
   
}


