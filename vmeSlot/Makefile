
GCC=g++

ROOTLIBS=$(shell root-config --libs)
ROOTINCS=$(shell root-config --cflags)

INCS = -I$(TDAQ_INST_PATH)/include -Iinc/ -Icxx
LIBS = -L$(TDAQ_INST_PATH)/i686-slc4-gcc34-dbg/lib -lvme_rcc -lrcc_error

COPT = -c $(INCS)
LOPT =  $(LIBS)

SRC = src/VMESlotClass.cpp

CXX = cxx/ReadTempsVolts.cxx cxx/test.cxx

INCL = inc/PprmDefs.h inc/VMESlotClass.h

OBJ = obj/VMESlotClass.o

MAIN=main
FIRMTOFLASH=fwToFlash
FIRMFLASHLOAD=fwLoadFromFlash
FIRMFILELOAD=fwLoadFromFile

target:$(MAIN) $(FIRMTOFLASH) $(FIRMFLASHLOAD) $(FIRMFILELOAD) library

$(MAIN): obj/main.o $(OBJ) Makefile
	$(GCC) $(LOPT) $(ROOTLIBS) obj/main.o $(OBJ) -o bin/$(MAIN)

obj/main.o:main.cpp $(CXX) Makefile
	$(GCC) $(COPT) $(ROOTINCS) main.cpp -o obj/main.o

# Firmware to flash writer

$(FIRMTOFLASH): $(OBJ) obj/$(FIRMTOFLASH).o Makefile
	$(GCC) $(LOPT) obj/$(FIRMTOFLASH).o $(OBJ) -o bin/$(FIRMTOFLASH)

obj/$(FIRMTOFLASH).o: $(OBJ) src/$(FIRMTOFLASH).c Makefile
	$(GCC) $(COPT) src/$(FIRMTOFLASH).c -o obj/$(FIRMTOFLASH).o

# Firmware loader from flash memory

$(FIRMFLASHLOAD): $(OBJ) obj/$(FIRMFLASHLOAD).o Makefile
	$(GCC) $(LOPT) obj/$(FIRMFLASHLOAD).o $(OBJ) -o bin/$(FIRMFLASHLOAD)

obj/$(FIRMFLASHLOAD).o: $(OBJ) src/$(FIRMFLASHLOAD).c Makefile
	$(GCC) $(COPT) src/$(FIRMFLASHLOAD).c -o obj/$(FIRMFLASHLOAD).o

# Firmware loader from file

$(FIRMFILELOAD): $(OBJ) obj/$(FIRMFILELOAD).o Makefile
	$(GCC) $(LOPT) obj/$(FIRMFILELOAD).o $(OBJ) -o bin/$(FIRMFILELOAD)

obj/$(FIRMFILELOAD).o: $(OBJ) src/$(FIRMFILELOAD).c Makefile
	$(GCC) $(COPT) src/$(FIRMFILELOAD).c -o obj/$(FIRMFILELOAD).o



obj/%.o: src/%.cpp inc/%.h
	$(GCC) $(COPT) $(SRC)
	@mv $*.o obj
	
library: $(OBJ)
	$(GCC) $(LOPTS) --shared -o lib/libVMESlot.so $(OBJ)
clean:
	rm -f test
	rm -f obj/*
	rm -f bin/*
	rm -f lib/*
	rm -f ./*~
	rm -f src/*~
	rm -f inc/*~
	
