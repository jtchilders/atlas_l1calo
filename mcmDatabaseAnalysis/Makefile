

include ../make_include

CHANMAPLIBPATH=$(CHANNELMAPPATH)/lib
CHANMAPINCPATH=$(CHANNELMAPPATH)/inc
CHANMAPOBJPATH=$(CHANNELMAPPATH)/obj
CHANMAPLIB=$(MAINLIBPATH)/libL1caloChannelMap.so

PIXELMAPLIBPATH=$(PIXELMAPPATH)/lib
PIXELMAPINC=$(PIXELMAPPATH)/inc
PIXELMAPLIB=$(MAINLIBPATH)/libPixelMap.so

PPMCLASSESLIB =$(MAINLIBPATH)/libPpmClasses.so
PPMCLASSESINC=$(PPMCLASSESPATH)/inc

INCOPTS= -I$(CHANMAPINCPATH) -I$(PIXELMAPINC) -I$(PPMCLASSESINC) -Iinc
LIBOPTS= -L$(MAINLIBPATH) -lL1CaloChannelMap -lPixelMap -lPpmClasses

COPTS = -c $(ROOTCOPTS) $(INCOPTS) -g3
LOPTS = $(ROOTLOPTS) $(LIBOPTS)

GCC=g++

SRCPATH=src
SRC=
CXX=
INCPATH=inc
INC=
OBJPATH=obj
OBJ= $(OBJPATH)/entry.o $(OBJPATH)/extractTxt.o

ALL_LIBS= $(CHANMAPLIB) $(PIXELMAPLIB) $(PPMCLASSESLIB)

EXEPATH=bin
EXE1=analyzeReplacements

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
$(CHANMAPLIB):
	make -C $(CHANNELMAPPATH)

$(CHANMAPPATH)/make.depend:
	make -C $(CHANMAPPATH)

$(PIXELMAPLIB):
	make -C $(PIXELMAPPATH)

$(PIXELMAPPATH)/make.depend:
	make -C $(PIXELMAPPATH)

$(PPMCLASSESLIB):
	make -C $(PPMCLASSESPATH)

$(PPMCLASSESPATH)/make.depend:
	make -C $(PPMCLASSESPATH)

depend:
	makedepend -- $(SRC) -- $(CXX) -- $(COPTS)

libs:
	make -C $(CHANNELMAPPATH)
	make -C $(PIXELMAPPATH)
	make -C $(PPMCLASSESPATH)
	
clean:
	@echo "   >>>>Clean"
	rm -f obj/*
	rm -f $(EXEPATH)/*
	rm -f ./*~
	rm -f src/*~
	rm -f inc/*~

cleanall:
	rm -f obj/*
	rm -f $(EXEPATH)/*
	rm -f ./*~
	rm -f src/*~
	rm -f inc/*~
	make -C $(TREECLASSPATH) clean
	make -C $(CHANNELMAPPATH) clean
	make -C $(ROOTDEFPATH) clean
	make -C $(PIXELMAPPATH) clean
	make -C $(PPMCLASSESPATH) clean


# DO NOT DELETE
