
include ../make_include

GCC = g++

SRCDIR = $(PPMCLASSESPATH)/src
SRC = $(SRCDIR)/PpmROBuffer.cpp $(SRCDIR)/PpmSatBcidLogic.cpp $(SRCDIR)/PpmFadcSim.cpp

INCDIR = $(PPMCLASSESPATH)/inc
INC = $(INCDIR)/PpmROBuffer.h $(INCDIR)/PpmFadcSim.h $(INCDIR)/PpmSatBcidLogic.h

OBJDIR = $(PPMCLASSESPATH)/obj
OBJ = $(OBJDIR)/PpmROBuffer.o $(OBJDIR)/PpmSatBcidLogic.o $(OBJDIR)/PpmFadcSim.o \
	$(OBJDIR)/PpmROBufferList.o

LIB = $(MAINLIBPATH)/libPpmClasses.so

COPTS = -c -I$(INCDIR) -g3 $(ROOTCOPTS) -fPIC -O2
LOPTS = -o $(EXE) $(ROOTLOPTS)

target: $(LIB)


$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(INCDIR)/%.h
	$(GCC) $(COPTS) $(SRCDIR)/$*.cpp -o $(OBJDIR)/$*.o

#------------ Library --------------------
$(LIB): $(OBJ)
	$(GCC) -shared -o $(LIB) $(OBJDIR)/*.o

#------------ Make Dependencies ----------
depend:
	makedepend -- $(COPTS) -- $(SRC)

clean:
	rm -f obj/*
	rm -f $(EXE)
	rm -f $(LIB)


# DO NOT DELETE

/scratch/childers/hdSVN/Analysis/Workspace/childers/PpmClasses/src/PpmROBuffer.o: /scratch/childers/hdSVN/Analysis/Workspace/childers/PpmClasses/inc/PpmROBuffer.h
/scratch/childers/hdSVN/Analysis/Workspace/childers/PpmClasses/src/PpmSatBcidLogic.o: /scratch/childers/hdSVN/Analysis/Workspace/childers/PpmClasses/inc/PpmSatBcidLogic.h
/scratch/childers/hdSVN/Analysis/Workspace/childers/PpmClasses/src/PpmFadcSim.o: /scratch/childers/hdSVN/Analysis/Workspace/childers/PpmClasses/inc/PpmFadcSim.h
/scratch/childers/hdSVN/Analysis/Workspace/childers/PpmClasses/src/PpmFadcSim.o: /scratch/childers/hdSVN/Analysis/Workspace/childers/PpmClasses/inc/LandGaus.h
