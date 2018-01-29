
# if not Taylor, Comment out
include ../make_include

# if not Taylor, Uncomment
#PIXELMAPPATH=.
#MAINLIBPATH=lib
#ROOTCOPTS=$(shell root-config --cflags)
#ROOTLOPTS=$(shell root-config --libs)

GCC = g++

EXE = PixelMap

SRCDIR = $(PIXELMAPPATH)/src
SRC = $(SRCDIR)/PixelMap.cpp

INCDIR = $(PIXELMAPPATH)/inc
INC = $(INCDIR)/PixelMap.h

OBJDIR = $(PIXELMAPPATH)/obj
OBJ = $(OBJDIR)/PixelMap.o

LIB = $(MAINLIBPATH)/libPixelMap.so

COPTS = -c -I$(INCDIR) -g $(ROOTCOPTS) -fPIC -fno-inline
LOPTS = -o $(EXE) $(ROOTLOPTS)

target: $(EXE) library

library: $(LIB)


$(EXE): main.cpp $(OBJDIR)/main.o $(OBJ) $(SRC) $(INC) Makefile
	$(GCC) $(LOPTS) $(OBJ) $(OBJDIR)/main.o

$(OBJDIR)/main.o: main.cpp $(INC) Makefile
	$(GCC) $(COPTS) main.cpp -o $*.o

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(INCDIR)/%.h
	$(GCC) $(COPTS) $(SRCDIR)/$*.cpp -o $(OBJDIR)/$*.o

#------------ Library --------------------
$(LIB): $(OBJ)
	$(GCC) -shared -o $(LIB) $(OBJ)


clean:
	rm -f obj/*
	rm -f $(EXE)
	rm -f lib/*
	rm -f $(LIB)
	rm -f ./*~
	rm -f src/*~
	rm -f inc/*~
	rm -f make.depend
