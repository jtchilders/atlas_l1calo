
# Used by Taylor and otherwise should be commented out
include ../make_include

# IF not Taylor uncomment these
#MAINLIBPATH=lib
#ROOTCOPTS=$(shell root-config --cflags)
#ROOTLOPTS=$(shell root-config --libs)

GCC = g++

SRCDIR=src
SRC = $(SRCDIR)/Tree.cpp

INCDIR=inc
INC=$(INCDIR)/Tree.h $(INCDIR)/Branch.h $(INCDIR)/AbstractBranch.h \
	$(INCDIR)/DataType.h $(INCDIR)/TypeTraits.h

OBJDIR=obj
OBJ=$(OBJDIR)/Tree.o

EXEDIR=bin
EXE1=TestTree
EXE=$(EXEDIR)/$(EXE1)
EXEOBJ=$(OBJDIR)/$(EXE1).o

LIB = $(MAINLIBPATH)/libTree.so

COPTS = -c -I$(INCDIR) -g3 -fPIC -O2 -Wall $(ROOTCOPTS)
LOPTS = $(ROOTLOPTS)

target: $(EXE) $(EXEOBJ) $(OBJ) library

library: $(LIB)


$(EXEDIR)/%: $(OBJDIR)/%.o $(OBJ) $(SRC) $(INC) Makefile
	$(GCC) $(LOPTS) -o $(EXEDIR)/$* $(OBJ) $(OBJDIR)/$*.o

$(OBJDIR)/%.o: $(SRCDIR)/%.cxx $(INC) Makefile
	$(GCC) $(COPTS) $(SRCDIR)/$*.cxx -o $(OBJDIR)/$*.o

#-------------- Classes ------------------
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(INCDIR)/%.h Makefile
	$(GCC) $(COPTS) $(SRCDIR)/$*.cpp -o $(OBJDIR)/$*.o

#------------ Library --------------------
$(LIB): $(OBJ)
	$(GCC) -shared -o $(LIB) $(OBJ)

#------------ Make Dependencies ----------
$(INCDIR)/AbstractBranch.h : $(INCDIR)/DataType.h
$(INCDIR)/Branch.h : $(INCDIR)/DataType.h $(INCDIR)/AbstractBranch.h \
	$(INCDIR)/TypeTraits.h
$(SRCDIR)/TestTree.cxx: $(INCDIR)/Tree.h $(INCDIR)/AccessMode.h \
	$(INCDIR)/TypeTraits.h
$(SRCDIR)/Tree.cpp : $(INCDIR)/Tree.h
$(INCDIR)/Tree.h: $(INCDIR)/DataType.h $(INCDIR)/Branch.h \
	$(INCDIR)/AbstractBranch.h $(INCDIR)/AccessMode.h \
	Makefile


#------------ Clean ----------------------
clean:
	rm -f obj/*
	rm -f $(EXE)
	rm -f lib/*
	rm -f ./*~
	rm -f src/*~
	rm -f inc/*~
	rm -f $(LIB)
