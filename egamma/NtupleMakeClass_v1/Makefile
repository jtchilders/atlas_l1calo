
include ../../make_include

CC=g++

LIB=$(MAINLIBPATH)/libEgammaNtuple_v1.so

INCLUDES=Makefile

TARGET=ReadNtuple.exe

OBJECTS=ReadNtuple.o TrigEgammaNtuple_v1.o RootDictionary.o

INCFLAGS=-m32 -I$(shell root-config --incdir) -O
##INCFLAGS=-m32 -I$(shell root-config --incdir) -I$(TestArea)/DataQuality/GoodRunsLists/  -O
# decomment the line and follow the GRL tutorial for standalone usage

ROOTLIBS = $(shell root-config --libs)

LIBS=-m32 $(ROOTLIBS) -ldl 
##LIBS=-m32 -L$(TestArea)/DataQuality/GoodRunsLists/StandAlone/ $(ROOTLIBS) -ldl -lGoodRunsLists
# decomment the line and follow the GRL tutorial for standalone usage

INCLUDES=Makefile

target: $(TARGET) $(LIB)

$(TARGET): $(OBJECTS) $(INCLUDES)
	@echo "**"
	@echo "** Linking Executable"
	@echo "**"
	$(CC) $(OBJECTS) $(LIBS) -o $(TARGET)

clean:
	@rm -f *.o *~
	@rm -f $(TARGET) $(LIB)

veryclean: clean
	@rm -f RootDictionary.*

%.o: %.cxx $(INCLUDES)
	@echo "**"
	@echo "** Compiling C++ Source" 
	@echo "**"
	$(CC) -c $(INCFLAGS) $< 

RootDictionary.cxx: LinkDef.h
	@echo "**"
	@echo "** Creating Root dictionary"
	@echo "**"
	rootcint -f RootDictionary.cxx -c $<

# Hack to avoid need to re-run make file following code generation target.
RootDictionary.o: RootDictionary.cxx
	@echo "**"
	@echo "** Compiling C++ Source" 
	@echo "**"
	$(CC) -c $(INCFLAGS)  RootDictionary.cxx -o RootDictionary.o


#------------ Library --------------------
$(LIB): $(OBJ)
	@echo "**"
	@echo "** Linking Library"
	@echo "**"
	$(CC) -shared -o $(LIB) $(OBJECTS)
