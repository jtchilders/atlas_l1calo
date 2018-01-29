

include ../make_include

TREELIBPATH=$(MAINLIBPATH)
TREEOBJPATH=$(TREECLASSPATH)/obj
TREELIB=$(MAINLIBPATH)/libTTreeMakeCLass.so

CHANMAPLIBPATH=$(MAINLIBPATH)
CHANMAPINCPATH=$(CHANNELMAPPATH)/inc
CHANMAPOBJPATH=$(CHANNELMAPPATH)/obj
CHANMAPLIB=$(MAINLIBPATH)/libL1caloChannelMap.so

PPMCLASSESLIBPATH=$(MAINLIBPATH)
PPMCLASSESINCPATH=$(PPMCLASSESPATH)/inc
PPMCLASSESOBJPATH=$(PPMCLASSESPATH)/obj
PPMCLASSESLIB=$(MAINLIBPATH)/libPpmClasses.so

CBNTLIB=$(MAINLIBPATH)/libCbntDict.so

INCOPTS= -I$(TREECLASSPATH) -I$(CHANMAPINCPATH) -I$(COMLINEPARSEINCPATH) \
         -I$(PPMCLASSESINCPATH) -Iinc
LIBOPTS= -L$(MAINLIBPATH) -lCbntDict -lL1CaloChannelMap -lTTreeMakeClass \
         -lPpmClasses

COPTS = -c $(ROOTCOPTS) $(INCOPTS) -g3
LOPTS = $(ROOTLOPTS) $(LIBOPTS)

GCC=g++

SRCPATH=src
INCPATH=inc
OBJPATH=obj

OBJ=

ALL_LIBS= $(TREELIB) $(CHANMAPLIB) $(CBNTLIB) $(PPMCLASSESLIB)

EXEPATH=bin
EXE1=simSatPulse
EXE=$(EXEPATH)/$(EXE1)
OBJEXE=$(OBJPATH)/$(EXE1).o

target: $(OBJ) $(OBJEXE) $(EXE)
# make.depend

$(EXEPATH)/%: $(OBJPATH)/%.o $(OBJ) $(ALL_LIBS)
	@echo " "
	@echo "--------->>>>>> Linking" $*
	$(GCC) $(LOPTS) -o $(EXEPATH)/$* $(OBJ) $(OBJPATH)/$*.o
	@echo "----->>> Done."

$(OBJPATH)/%.o: $(SRCPATH)/%.cxx $(INC)
	@echo " "
	@echo "--------->>>>>> Compiling" $*.o
	$(GCC) $(COPTS) $(SRCPATH)/$*.cxx -o $(OBJPATH)/$*.o
	@echo "----->>> Done."

# Build Generic Object Files
$(OBJPATH)/%.o: $(SRCPATH)/%.cpp $(INCPATH)/%.h
	@echo " "
	@echo "--------->>>>>> Compiling" $*.o
	$(GCC) $(COPTS) $(SRCPATH)/$*.cpp -o $(OBJPATH)/$*.o
	@echo "----->>> Done."

# Build necessary libraries if they don't exist
$(CBNTLIB):
	make -C $(TREECLASSPATH)
	make -C $(ROOTDEFPATH) clean
	make -C $(ROOTDEFPATH)

$(CHANMAPLIB):
	make -C $(CHANNELMAPPATH)

$(TREELIB):
	make -C $(TREECLASSPATH)

$(PPMCLASSESLIB):
	make -C $(PPMCLASSESPATH)

libs:
	make -C $(TREECLASSPATH)
	make -C $(CHANNELMAPPATH)
	make -C $(ROOTDEFPATH)
	make -C $(PIXELMAPPATH)
	make -C $(PPMCLASSESPATH)
	
clean:
	@echo "   >>>>Clean"
	rm -f $(OBJPATH)/*
	rm -f $(EXEPATH)/*
	rm -f ./*~
	rm -f $(SRCPATH)/*~
	rm -f $(INCPATH)/*~

cleanall:
	rm -f $(OBJPATH)/*
	rm -f $(EXEPATH)/*
	rm -f ./*~
	rm -f $(SRCPATH)/*~
	rm -f $(INCPATH)/*~
	make -C $(TREECLASSPATH) clean
	make -C $(CHANNELMAPPATH) clean
	make -C $(ROOTDEFPATH) clean
	make -C $(PPMCLASSESPATH) clean
