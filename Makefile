####### Compiler, tools and options
CC            = gcc
CXX           = g++
DEFINES       = -Wall -g -std=c++0x
CFLAGS        = -O2 $(DEFINES)
CXXFLAGS        = -O2 $(DEFINES)
INCPATH       = -Iinclude 
LINK          = g++
LFLAGS        = -Wl,--as-needed -Wl,-O1
DEL_FILE      = rm -f
DEL_DIR       = rmdir
MOVE          = mv -f

####### Output directory
OBJECTS_DIR   = ./obj
BIN_DIR       = ./bin

####### Files
OBJECTS       = binomial_test.o poisson_test.o laplace_test.o bernoulli.o
TARGET        = binomial_test poisson_test laplace_test bernoulli 

first: all
####### Implicit rules

all:  $(TARGET)

$(TARGET):  $(OBJECTS)  

clean: 
	-$(DEL_FILE) $(OBJECTS_DIR)/*.o
	-$(DEL_FILE) *~ core *.core

distclean: clean
	-$(DEL_FILE) $(BIN_DIR)/* 

####### Compile
binomial_test.o : example/binomial_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/binomial_test.o example/binomial_test.cc

poisson_test.o : example/poisson_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/poisson_test.o example/poisson_test.cc

laplace_test.o : example/laplace_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/laplace_test.o example/laplace_test.cc

bernoulli_test.o : example/bernoulli_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/bernoulli_test.o example/bernoulli_test.cc

####### Detailed Build Rules
binomial_test: binomial_test.o 
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/binomial_test $(OBJECTS_DIR)/binomial_test.o $(OBJCOMP) $(LIBS)

poisson_test: poisson_test.o 
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/poisson_test $(OBJECTS_DIR)/poisson_test.o $(OBJCOMP) $(LIBS)

laplace_test: laplace_test.o 
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/laplace_test $(OBJECTS_DIR)/laplace_test.o $(OBJCOMP) $(LIBS)

bernoulli_test: bernoulli_test.o 
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/bernoulli_test $(OBJECTS_DIR)/bernoulli_test.o $(OBJCOMP) $(LIBS)


