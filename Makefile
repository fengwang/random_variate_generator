####### Compiler, tools and options
CXX 	      = g++
DEFINES       = -std=c++20 -O3 -DNDEBUG -Wall -Wextra
CFLAGS        = $(DEFINES)
CXXFLAGS      = $(DEFINES)
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
	-$(DEL_FILE) $(DOC_DIR)/*.aux $(DOC_DIR)/*.idx $(DOC_DIR)/*.log $(DOC_DIR)/*.out $(DOC_DIR)/*.toc
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
uniform.o : test/uniform.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/uniform.o test/uniform.cc
uniform: uniform.o
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/uniform $(OBJECTS_DIR)/uniform.o $(OBJCOMP) $(LIBS)
gaussian_test.o : test/gaussian_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/gaussian_test.o test/gaussian_test.cc
gaussian_test: gaussian_test.o
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/gaussian_test $(OBJECTS_DIR)/gaussian_test.o $(OBJCOMP) $(LIBS)

balding_nichols_test.o : test/balding_nichols_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/balding_nichols_test.o test/balding_nichols_test.cc
balding_nichols_test: balding_nichols_test.o
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/balding_nichols_test $(OBJECTS_DIR)/balding_nichols_test.o $(OBJCOMP) $(LIBS)

uniform_example.o : test/uniform_example.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/uniform_example.o test/uniform_example.cc
uniform_example: uniform_example.o
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/uniform_example $(OBJECTS_DIR)/uniform_example.o $(OBJCOMP) $(LIBS)

variate_generator_example.o : test/variate_generator_example.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/variate_generator_example.o test/variate_generator_example.cc
variate_generator_example: variate_generator_example.o
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/variate_generator_example $(OBJECTS_DIR)/variate_generator_example.o $(OBJCOMP) $(LIBS)

first_test.o : test/first_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/first_test.o test/first_test.cc
first_test: first_test.o
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/first_test $(OBJECTS_DIR)/first_test.o $(OBJCOMP) $(LIBS)

arcsine_example.o : test/arcsine_example.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/arcsine_example.o test/arcsine_example.cc
arcsine_example: arcsine_example.o
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/arcsine_example $(OBJECTS_DIR)/arcsine_example.o $(OBJCOMP) $(LIBS)

balding_nichols_example.o : test/balding_nichols_example.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/balding_nichols_example.o test/balding_nichols_example.cc
balding_nichols_example: balding_nichols_example.o
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/balding_nichols_example $(OBJECTS_DIR)/balding_nichols_example.o $(OBJCOMP) $(LIBS)

bernoulli_example.o : test/bernoulli_example.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/bernoulli_example.o test/bernoulli_example.cc
bernoulli_example: bernoulli_example.o
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/bernoulli_example $(OBJECTS_DIR)/bernoulli_example.o $(OBJCOMP) $(LIBS)

beta_example.o : test/beta_example.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/beta_example.o test/beta_example.cc
beta_example: beta_example.o
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/beta_example $(OBJECTS_DIR)/beta_example.o $(OBJCOMP) $(LIBS)

beta_binomial_example.o : test/beta_binomial_example.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/beta_binomial_example.o test/beta_binomial_example.cc
beta_binomial_example: beta_binomial_example.o
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/beta_binomial_example $(OBJECTS_DIR)/beta_binomial_example.o $(OBJCOMP) $(LIBS)

binomial_example.o : test/binomial_example.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/binomial_example.o test/binomial_example.cc
binomial_example: binomial_example.o
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/binomial_example $(OBJECTS_DIR)/binomial_example.o $(OBJCOMP) $(LIBS)

burr_example.o : test/burr_example.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/burr_example.o test/burr_example.cc
burr_example: burr_example.o
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/burr_example $(OBJECTS_DIR)/burr_example.o $(OBJCOMP) $(LIBS)

make_passwd.o : test/make_passwd.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/make_passwd.o test/make_passwd.cc
make_passwd: make_passwd.o
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/make_passwd $(OBJECTS_DIR)/make_passwd.o $(OBJCOMP) $(LIBS)

gaussian.o : test/gaussian.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/gaussian.o test/gaussian.cc
gaussian: gaussian.o
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/gaussian $(OBJECTS_DIR)/gaussian.o $(OBJCOMP) $(LIBS)

chi_square_example.o : test/chi_square_example.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/chi_square_example.o test/chi_square_example.cc
chi_square_example: chi_square_example.o
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/chi_square_example $(OBJECTS_DIR)/chi_square_example.o $(OBJCOMP) $(LIBS)

