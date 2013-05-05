####### Compiler, tools and options
CXX           = g++-4.9
DEFINES       = -Wall -std=c++11
CFLAGS        = -O2 $(DEFINES)
CXXFLAGS        = -O2 $(DEFINES)
INCPATH       = -Iinclude 
LINK          = $(CXX)
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
OBJECTS       = arcsine.o bernoulli.o normal.o beta_binomial.o rademacher.o
TARGET        = arcsine bernoulli normal beta_binomial rademacher
#DOC           = main.tex
DOC           = vg.tex

first: all
####### Implicit rules

all: $(TARGET)

pdf:
	$(LATEX) -output-directory=$(DOC_DIR) $(DOC_DIR)/$(DOC)
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
normal.o : test/normal.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/normal.o test/normal.cc
normal: normal.o 
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/normal $(OBJECTS_DIR)/normal.o $(OBJCOMP) $(LIBS)
beta_binomial.o : test/beta_binomial.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/beta_binomial.o test/beta_binomial.cc
beta_binomial: beta_binomial.o 
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/beta_binomial $(OBJECTS_DIR)/beta_binomial.o $(OBJCOMP) $(LIBS)
rademacher.o : test/rademacher.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/rademacher.o test/rademacher.cc
rademacher: rademacher.o 
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/rademacher $(OBJECTS_DIR)/rademacher.o $(OBJCOMP) $(LIBS)

