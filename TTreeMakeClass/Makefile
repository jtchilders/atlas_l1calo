
include ../make_include

LIB=$(MAINLIBPATH)/libTTreeMakeClass.so

GCC=g++

SRC=cbntClass.C
OBJ=cbntClass.o

target: $(LIB)

#------- L1CaloTree Class -----------

$(OBJ): cbntClass.h $(SRC)
	@echo " "
	@echo " ----->>>>> Creating" $(OBJ)
	$(GCC) -c $(SRC) $(ROOTCOPTS) -fPIC

#------- L1CaloTree Library ---------

$(LIB) : $(OBJ)
	@echo " "
	@echo " ----->>>>> Creating" $(LIB)
	$(GCC) -shared -o $(LIB) $(OBJ)

clean:
	rm -f $(LIB)
	rm -f ./*~
	rm -f ./*.o

