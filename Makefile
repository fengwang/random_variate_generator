####### Compiler, tools and options
CXX           = g++
DEFINES       = -Wall -std=c++11
CFLAGS        = -O2 $(DEFINES)
CXXFLAGS        = -O2 $(DEFINES)
INCPATH       = -Iinclude 
LINK          = g++
LATEX         = xelatex
LFLAGS        = 
DEL_FILE      = rm -f
DEL_DIR       = rmdir
MOVE          = mv -f
MAKE_DIR      = mkdir

####### Output directory
OBJECTS_DIR   = ./obj
BIN_DIR       = ./bin
DOC_DIR       = ./doc

####### Files
OBJECTS       = arcsine.o bernoulli.o
TARGET        = arcsine bernoulli
DOC           = main.tex

first: all
####### Implicit rules

all: $(TARGET)

pdf:
	$(LATEX) -output-directory=$(DOC_DIR) $(DOC_DIR)/$(DOC)

$(TARGET): 

makedir: 
	test -z $(OBJECTS_DIR) || $(MAKE_DIR) -p $(OBJECTS_DIR)
	test -z $(BIN_DIR) || $(MAKE_DIR) -p $(BIN_DIR)

clean: 
	-$(DEL_FILE) $(OBJECTS_DIR)/*.o
	-$(DEL_FILE) *~ core *.core

distclean: clean
	-$(DEL_FILE) $(BIN_DIR)/* 

####### Compile
arcsine.o : test/arcsine.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/arcsine.o test/arcsine.cc
arcsine: arcsine.o 
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/arcsine $(OBJECTS_DIR)/arcsine.o $(OBJCOMP) $(LIBS)
bernoulli.o : test/bernoulli.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/bernoulli.o test/bernoulli.cc
bernoulli: bernoulli.o 
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/bernoulli $(OBJECTS_DIR)/bernoulli.o $(OBJCOMP) $(LIBS)

