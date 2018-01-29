

include ../make_include

TREELIBPATH=$(MAINLIBPATH)
TREEOBJPATH=$(TREECLASSPATH)/obj
TREELIB=$(MAINLIBPATH)/libTTreeMakeClass.so

CHANMAPLIBPATH=$(MAINLIBPATH)
CHANMAPINCPATH=$(CHANNELMAPPATH)/inc
CHANMAPOBJPATH=$(CHANNELMAPPATH)/obj
CHANMAPLIB=$(MAINLIBPATH)/libL1caloChannelMap.so

PIXELMAPLIBPATH=$(MAINLIBPATH)
PIXELMAPINCPATH=$(PIXELMAPPATH)/inc
PIXELMAPOBJPATH=$(PIXELMAPPATH)/obj
PIXELMAPLIB=$(MAINLIBPATH)/libPixelMap.so

PPMCLASSESLIBPATH=$(MAINLIBPATH)
PPMCLASSESINCPATH=$(PPMCLASSESPATH)/inc
PPMCLASSESOBJPATH=$(PPMCLASSESPATH)/obj
PPMCLASSESLIB=$(MAINLIBPATH)/libPpmClasses.so

CBNTLIB=$(MAINLIBPATH)/libCbntDict.so

INCOPTS= -I$(TREECLASSPATH) -I$(CHANMAPINCPATH) -I$(COMLINEPARSEINCPATH) \
         -I$(PPMCLASSESINCPATH) -Iinc -I$(PIXELMAPINCPATH)
LIBOPTS= -L$(MAINLIBPATH) -lCbntDict -lL1CaloChannelMap -lTTreeMakeClass \
         -lPpmClasses -lPixelMap

COPTS = -c $(ROOTCOPTS) $(INCOPTS) -g -fPIC -fno-inline
LOPTS = $(ROOTLOPTS) $(LIBOPTS) -lrt

GCC=g++

SRCPATH=src
INCPATH=inc
OBJPATH=obj

OBJ= $(OBJPATH)/ShapeMakerTree.o $(OBJPATH)/SatBcidTree.o \
	$(OBJPATH)/DacVsAdcPeakGraph.o $(OBJPATH)/ChanCalibErrorCode.o \
	$(OBJPATH)/AbstractErrorCode.o $(OBJPATH)/EstAdcVsAdcGraph.o \
	$(OBJPATH)/CombinedCanvas.o $(OBJPATH)/SatBcidTreeFiller.o \
	$(OBJPATH)/SignalShape.o $(OBJPATH)/SignalShapeCollection.o

ALL_LIBS= $(TREELIB) $(CHANMAPLIB) $(CBNTLIB) $(PPMCLASSESLIB)

EXEPATH=bin
#EXE1=fillEmptySatBcidSettings
EXE2=processSatBcidResults
EXE3=adcSliceCombinePlots
EXE4=analyzePhos4runSeries
EXE5=tempAnal
EXE=$(EXEPATH)/$(EXE2) $(EXEPATH)/$(EXE3) $(EXEPATH)/$(EXE4) $(EXEPATH)/$(EXE5)
OBJEXE=$(OBJPATH)/$(EXE2).o $(OBJPATH)/$(EXE3).o $(OBJPATH)/$(EXE4).o $(OBJPATH)/$(EXE5).o

target: $(OBJ) $(OBJEXE) $(EXE)

$(EXEPATH)/%: $(OBJPATH)/%.o $(OBJ) $(ALL_LIBS)
	@echo " "
	@echo "--------->>>>>> Linking" $*
	$(GCC) $(LOPTS) -o $(EXEPATH)/$* $(OBJ) $(OBJ2) $(OBJPATH)/$*.o
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
