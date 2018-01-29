

# Used by Taylor and otherwise should be commented out
include ../make_include

# IF not Taylor uncomment these
#CHANNELMAPPATH=.
#MAINLIBPATH=lib


GCC = g++

SRCDIR=src
SRC = $(SRCDIR)/L1CaloPPMdbTree.cpp $(SRCDIR)/L1CaloPPMTree.cpp \
	$(SRCDIR)/L1CaloPPMdbRxGainBugFixTree.cpp $(SRCDIR)/L1CaloPPMdbTreeMC.cpp \
	$(SRCDIR)/L1CaloPPMTreeMC.cpp

INCDIR=inc
INC = $(INCDIR)/L1CaloPPMdbTree.h $(INCDIR)/L1CaloPPMTree.h \
	$(INCDIR)/L1CaloPPMdbRxGainBugFixTree.h $(INCDIR)/L1CaloPPMdbTreeMC.h \
	$(INCDIR)/L1CaloPPMTreeMC.h

OBJDIR=obj
OBJ = $(OBJDIR)/L1CaloPPMdbTree.o $(OBJDIR)/L1CaloPPMTree.o \
	$(OBJDIR)/L1CaloPPMdbRxGainBugFixTree.o $(OBJDIR)/L1CaloPPMdbTreeMC.o \
	$(OBJDIR)/L1CaloPPMTreeMC.o

EXEDIR=bin
#EXE1=
EXE=
#$(EXEDIR)/$(EXE1)

#EXEOBJ= $(OBJDIR)/$(EXE1).o

LIB = $(MAINLIBPATH)/libD3PDTree.so

COPTS = -c -I$(INCDIR) -g -fPIC -Wall -fno-inline $(ROOTCOPTS)
LOPTS = $(ROOTLOPTS)

target: $(EXE) library

library: $(LIB)


$(EXEDIR)/%: $(OBJDIR)/%.o $(OBJ) $(SRC) $(INC) Makefile
	$(GCC) $(LOPTS) -o $(EXEDIR)/$* $(OBJ) $(OBJDIR)/$*.o

$(OBJDIR)/%.o: $(SRCDIR)/%.cxx $(INC) Makefile
	$(GCC) $(COPTS) $(SRCDIR)/$*.cxx -o $(OBJDIR)/$*.o

#-------------- Classes ------------------
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(INCDIR)/%.h
	$(GCC) $(COPTS) $(SRCDIR)/$*.cpp -o $(OBJDIR)/$*.o

#------------ Library --------------------
$(LIB): $(OBJ)
	$(GCC) -shared -o $(LIB) $(OBJ)

#------------ Make Dependencies ----------

#------------ Clean ----------------------
clean:
	rm -f obj/*
	rm -f ChannelMapTest
	rm -f lib/*
	rm -f ./*~
	rm -f src/*~
	rm -f inc/*~
	rm -f $(LIB)
