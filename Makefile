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
SOURCES       = example/uniform_test.cc
OBJECTS       = binomial_test.o 
TARGET        = binomial_test 

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

####### Detailed Build Rules
binomial_test: binomial_test.o 
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/binomial_test $(OBJECTS_DIR)/binomial_test.o $(OBJCOMP) $(LIBS)

