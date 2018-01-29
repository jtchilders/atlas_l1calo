
#--------------------------------------------------------------------------------

include ../make_include

PIXELMAPINCPATH = $(PIXELMAPPATH)/inc
CHANNELMAPINCPATH = $(CHANNELMAPPATH)/inc


LIB = 		$(MAINLIBPATH)/libCbntDict.so

OBJ = 		$(ROOTDEFPATH)/CbntDict.o
		
H = 		$(TREECLASSPATH)/cbntClass.h \
      $(PIXELMAPINCPATH)/PixelMap.h \
		$(ROOTDEFPATH)/LinkDef.h
		


target: $(DIC) $(LIB)

#------------------------------------------------------------------------------

DIC =		$(ROOTDEFPATH)/CbntDict.C
DICH =		$(ROOTDEFPATH)/CbntDict.h

$(DIC):		$(H)
		make clean
		rootcint $(DIC) -c -I$(CHANNELMAPINCPATH) $(H)
		echo $(ROOTCOPTS)

$(OBJ): $(DIC) $(DICH)
	g++ -c $(DIC) $(ROOTCOPTS) -I$(CHANNELMAPINCPATH) -fPIC -O2

$(LIB): $(OBJ)
	g++ -shared -o $(LIB) $(OBJ)

clean:
	rm -f $(DIC) 
	rm -f $(DICH) 
	rm -f $(LIB) 
	rm -f $(OBJ)
	rm -f ./*~


