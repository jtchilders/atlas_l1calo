

include ../make_include

INCOPTS= -Iinc
LIBOPTS=

COPTS = -c $(ROOTCOPTS) $(INCOPTS) -g -fPIC -fno-inline
LOPTS = $(ROOTLOPTS) $(LIBOPTS) -lrt

GCC=g++

SRCPATH=src
INCPATH=inc
OBJPATH=obj

OBJ= $(OBJPATH)/ScopeFile.o $(OBJPATH)/FileList.o $(OBJPATH)/Tree.o
INC= $(INCPATH)/ScopeFile.h $(INCPATH)/FileList.h $(INCPATH)/Tree.h
SRC= $(SRCPATH)/ScopeFile.cpp $(SRCPATH)/FileList.cpp $(SRCPATH)/Tree.cpp

EXEPATH=bin
EXE1=plotScopeTraces
EXE2=makeTree
EXE=$(EXEPATH)/$(EXE1) $(EXEPATH)/$(EXE2)
EXEOBJ=$(OBJPATH)/$(EXE1).o $(OBJPATH)/$(EXE2).o

target:  $(EXE) $(OBJ) #(EXEOBJ) $(INC) $(SRC)

$(EXEPATH)/%: $(OBJPATH)/%.o $(OBJ)
	@echo " "
	@echo "--------->>>>>> Linking" $*
	$(GCC) $(LOPTS) -o $(EXEPATH)/$* $(OBJPATH)/$*.o $(OBJ)
	@echo "----->>> Done."

$(OBJPATH)/%.o: $(SRCPATH)/%.cxx
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
	
clean:
	@echo "   >>>>Clean"
	rm -f $(OBJPATH)/*
	rm -f $(EXEPATH)/*
	rm -f ./*~
	rm -f $(SRCPATH)/*~
	rm -f $(INCPATH)/*~

