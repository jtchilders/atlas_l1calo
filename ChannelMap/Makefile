

# Used by Taylor and otherwise should be commented out
#include ../make_include

# IF not Taylor uncomment these
CHANNELMAPPATH=.
MAINLIBPATH=lib


GCC = g++

SRCDIR=$(CHANNELMAPPATH)/src
SRC = $(SRCDIR)/JemChannelMap.cpp $(SRCDIR)/PpmChannelMap.cpp \
		$(SRCDIR)/CpmChannelMap.cpp $(SRCDIR)/L1CaloChannelMap.cpp \
		$(SRCDIR)/EtaPhiId.cpp $(SRCDIR)/L1CaloChannelId.cpp \
		$(SRCDIR)/CPMRoI.cpp $(SRCDIR)/TcppChannelMap.cpp

INCDIR = $(CHANNELMAPPATH)/inc
INC = $(INCDIR)/JemChannelMap.h $(INCDIR)/PpmChannelMap.h \
		$(INCDIR)/CpmChannelMap.h $(INCDIR)/L1CaloChannelMap.h \
		$(INCDIR)/EtaPhiId.h $(INCDIR)/L1CaloChannelId.h \
		$(INCDIR)/CaloLayer.h $(INCDIR)/FcalLayer.h \
		$(INCDIR)/CPMRoI.h $(INCDIR)/CaloDivision.h \
		$(INCDIR)/TcppChannelMap.h $(INCDIR)/TileDrawerId.h

OBJDIR = $(CHANNELMAPPATH)/obj
OBJ = $(OBJDIR)/JemChannelMap.o $(OBJDIR)/PpmChannelMap.o \
		$(OBJDIR)/CpmChannelMap.o $(OBJDIR)/L1CaloChannelMap.o \
		$(OBJDIR)/EtaPhiId.o $(OBJDIR)/L1CaloChannelId.o \
		$(OBJDIR)/CPMRoI.o $(OBJDIR)/TcppChannelMap.o

EXEDIR=bin
EXE1=ChannelMapTest
EXE1OBJ=$(OBJDIR)/main.o
EXE2=CaloLayerTest
EXE3=FcalLayerTest
EXE4=EtaPhiIdTest
EXE= $(EXEDIR)/$(EXE1) $(EXEDIR)/$(EXE2) $(EXEDIR)/$(EXE3) $(EXEDIR)/$(EXE4)

EXEOBJ= $(OBJDIR)/$(EXE1).o $(OBJDIR)/$(EXE2).o $(OBJDIR)/$(EXE3).o \
	$(OBJDIR)/(EXE4).o

LIB = $(MAINLIBPATH)/libL1CaloChannelMap.so

COPTS = -c -I$(INCDIR) -g -fPIC -Wall -fno-inline
LOPTS =

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
