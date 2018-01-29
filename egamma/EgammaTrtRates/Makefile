

# Used by Taylor and otherwise should be commented out
include ../../make_include

# IF not Taylor uncomment these
#EGAMMA_TREE=.
#MAINLIBPATH=.

GCC = g++

OBJDIR=obj
OBJ= $(OBJDIR)/RateHisto.o
INCDIR=inc
SRCDIR=src

EXEDIR=bin
EXE1=egammaTrtRates
EXE2=ntupleConsistencyCheck
EXE3=trtTrackTest

EXE= $(EXEDIR)/$(EXE1) $(EXEDIR)/$(EXE2) $(EXEDIR)/$(EXE3)

EXEOBJ= $(OBJDIR)/$(EXE1).o $(OBJDIR)/$(EXE2).o $(OBJDIR)/$(EXE3).o

COPTS = -c -I$(INCDIR) -I$(EGAMMA_TREE_V2) -I$(EGAMMA_TREE_V1) -I$(COMLINEPARSEINCPATH) -g3 -fPIC -O2 -Wall $(ROOTCOPTS)
LOPTS = -L$(MAINLIBPATH) -lEgammaNtuple_v2 -lEgammaNtuple_v1 $(ROOTLOPTS)

target: $(EXE) $(OBJ) $(EXEOBJ)

$(EXEDIR)/%: $(OBJDIR)/%.o $(OBJ) $(SRC) $(INC) Makefile
	@echo "--> Linking $*"
	$(GCC) $(LOPTS) -o $(EXEDIR)/$* $(OBJ) $(OBJDIR)/$*.o

$(OBJDIR)/%.o: $(SRCDIR)/%.cxx $(INC) Makefile
	@echo ">>> Compiling $*.cxx"
	$(GCC) $(COPTS) $(SRCDIR)/$*.cxx -o $(OBJDIR)/$*.o

#-------------- Classes ------------------
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(INCDIR)/%.h
	@echo ">>> Compiling $*.cpp"
	$(GCC) $(COPTS) $(SRCDIR)/$*.cpp -o $(OBJDIR)/$*.o

#------------ Clean ----------------------
clean:
	rm -f $(OBJDIR)/*
	rm -f $(EXE)
	rm -f ./*~
	rm -f $(SRCDIR)/*~
	rm -f $(INCDIR)/*~
	rm -f $(LIB)
