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
OBJECTS       = binomial_test.o poisson_test.o laplace_test.o bernoulli_test.o t_test.o exponential_test.o \
                f_test.o gumbel_1_test.o gumbel_2_test.o negative_binomial_test.o lognormal_test.o logarithmic_test.o
TARGET        = binomial_test poisson_test laplace_test bernoulli_test t_test exponential_test \
                f_test gumbel_1_test gumbel_2_test negative_binomial_test lognormal_test logarithmic_test

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

t_test.o : example/t_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/t_test.o example/t_test.cc

exponential_test.o : example/exponential_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/exponential_test.o example/exponential_test.cc

f_test.o : example/f_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/f_test.o example/f_test.cc

gumbel_1_test.o : example/gumbel_1_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/gumbel_1_test.o example/gumbel_1_test.cc

gumbel_2_test.o : example/gumbel_2_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/gumbel_2_test.o example/gumbel_2_test.cc

negative_binomial_test.o : example/negative_binomial_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/negative_binomial_test.o example/negative_binomial_test.cc

lognormal_test.o : example/lognormal_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/lognormal_test.o example/lognormal_test.cc

logarithmic_test.o : example/logarithmic_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/logarithmic_test.o example/logarithmic_test.cc

####### Detailed Build Rules
binomial_test: binomial_test.o 
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/binomial_test $(OBJECTS_DIR)/binomial_test.o $(OBJCOMP) $(LIBS)

poisson_test: poisson_test.o 
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/poisson_test $(OBJECTS_DIR)/poisson_test.o $(OBJCOMP) $(LIBS)

laplace_test: laplace_test.o 
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/laplace_test $(OBJECTS_DIR)/laplace_test.o $(OBJCOMP) $(LIBS)

bernoulli_test: bernoulli_test.o 
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/bernoulli_test $(OBJECTS_DIR)/bernoulli_test.o $(OBJCOMP) $(LIBS)

t_test: t_test.o 
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/t_test $(OBJECTS_DIR)/t_test.o $(OBJCOMP) $(LIBS)

exponential_test: exponential_test.o 
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/exponential_test $(OBJECTS_DIR)/exponential_test.o $(OBJCOMP) $(LIBS)

f_test: f_test.o 
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/f_test $(OBJECTS_DIR)/f_test.o $(OBJCOMP) $(LIBS)

gumbel_1_test: gumbel_1_test.o 
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/gumbel_1_test $(OBJECTS_DIR)/gumbel_1_test.o $(OBJCOMP) $(LIBS)

gumbel_2_test: gumbel_2_test.o 
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/gumbel_2_test $(OBJECTS_DIR)/gumbel_2_test.o $(OBJCOMP) $(LIBS)

negative_binomial_test: negative_binomial_test.o 
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/negative_binomial_test $(OBJECTS_DIR)/negative_binomial_test.o $(OBJCOMP) $(LIBS)

lognormal_test: lognormal_test.o 
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/lognormal_test $(OBJECTS_DIR)/lognormal_test.o $(OBJCOMP) $(LIBS)

logarithmic_test: logarithmic_test.o 
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/logarithmic_test $(OBJECTS_DIR)/logarithmic_test.o $(OBJCOMP) $(LIBS)



