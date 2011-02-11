####### Compiler, tools and options
CC            = gcc
#CC            = gcc-4.6
#CXX           = icpc
#CXX           = g++-4.6
CXX           = g++
DEFINES       = -Wall -std=c++0x
CFLAGS        = -O2 $(DEFINES)
CXXFLAGS        = -O2 $(DEFINES)
INCPATH       = -Iinclude 
#LINK          = icpc
LINK          = g++
#LINK          = g++-4.6
LFLAGS        = 
#LFLAGS        = -Wl,--as-needed -Wl,-O1
DEL_FILE      = rm -f
DEL_DIR       = rmdir
MOVE          = mv -f
MAKE_DIR      = mkdir

####### Output directory
OBJECTS_DIR   = ./obj
BIN_DIR       = ./bin

####### Files
OBJECTS       = binomial_test.o poisson_test.o laplace_test.o bernoulli_test.o t_test.o exponential_test.o \
                f_test.o gumbel_1_test.o gumbel_2_test.o negative_binomial_test.o lognormal_test.o logarithmic_test.o \
                exponential_power_test.o  gaussian_test.o hypergeometric_test.o levy_test.o beta_test.o \
                logistic_test.o pascal_test.o polya_test.o beta_binomial_test.o zipf_test.o gamma_test.o planck_test.o \
                yule_test.o generalized_hypergeometric_b3_test.o generalized_waring_test.o mizutani_test.o \
                waring_test.o digamma_test.o trigamma_test.o inverse_gaussian_test.o wald_test.o teichroew_test.o \
				pearson_vi_test.o
TARGET        = binomial_test poisson_test laplace_test bernoulli_test t_test exponential_test \
                f_test gumbel_1_test gumbel_2_test negative_binomial_test lognormal_test logarithmic_test \
                exponential_power_test gaussian_test hypergeometric_test levy_test beta_test \
                logistic_test pascal_test polya_test beta_binomial_test zipf_test gamma_test planck_test \
                yule_test.o generalized_hypergeometric_b3_test generalized_waring_test mizutani_test \
                waring_test digamma_test trigamma_test inverse_gaussian_test wald_test teichroew_test \
				pearson_vi_test

first: all
####### Implicit rules

all:  makedir $(TARGET)

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

exponential_power_test.o : example/exponential_power_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/exponential_power_test.o example/exponential_power_test.cc

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

gaussian_test.o : example/gaussian_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/gaussian_test.o example/gaussian_test.cc

hypergeometric_test.o : example/hypergeometric_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/hypergeometric_test.o example/hypergeometric_test.cc

levy_test.o : example/levy_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/levy_test.o example/levy_test.cc

beta_test.o : example/beta_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/beta_test.o example/beta_test.cc

logistic_test.o : example/logistic_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/logistic_test.o example/logistic_test.cc

pascal_test.o : example/pascal_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/pascal_test.o example/pascal_test.cc

polya_test.o : example/polya_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/polya_test.o example/polya_test.cc

beta_binomial_test.o : example/beta_binomial_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/beta_binomial_test.o example/beta_binomial_test.cc

zipf_test.o : example/zipf_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/zipf_test.o example/zipf_test.cc

gamma_test.o : example/gamma_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/gamma_test.o example/gamma_test.cc

planck_test.o : example/planck_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/planck_test.o example/planck_test.cc

yule_test.o : example/yule_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/yule_test.o example/yule_test.cc

generalized_hypergeometric_b3_test.o : example/generalized_hypergeometric_b3_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/generalized_hypergeometric_b3_test.o example/generalized_hypergeometric_b3_test.cc

generalized_waring_test.o : example/generalized_waring_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/generalized_waring_test.o example/generalized_waring_test.cc

mizutani_test.o : example/mizutani_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/mizutani_test.o example/mizutani_test.cc

waring_test.o : example/waring_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/waring_test.o example/waring_test.cc

digamma_test.o : example/digamma_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/digamma_test.o example/digamma_test.cc

trigamma_test.o : example/trigamma_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/trigamma_test.o example/trigamma_test.cc

inverse_gaussian_test.o : example/inverse_gaussian_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/inverse_gaussian_test.o example/inverse_gaussian_test.cc

wald_test.o : example/wald_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/wald_test.o example/wald_test.cc

teichroew_test.o : example/teichroew_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/teichroew_test.o example/teichroew_test.cc

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

exponential_power_test: exponential_power_test.o 
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/exponential_power_test $(OBJECTS_DIR)/exponential_power_test.o $(OBJCOMP) $(LIBS)

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

gaussian_test: gaussian_test.o 
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/gaussian_test $(OBJECTS_DIR)/gaussian_test.o $(OBJCOMP) $(LIBS)

hypergeometric_test: hypergeometric_test.o 
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/hypergeometric_test $(OBJECTS_DIR)/hypergeometric_test.o $(OBJCOMP) $(LIBS)

levy_test: levy_test.o 
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/levy_test $(OBJECTS_DIR)/levy_test.o $(OBJCOMP) $(LIBS)

beta_test: beta_test.o 
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/beta_test $(OBJECTS_DIR)/beta_test.o $(OBJCOMP) $(LIBS)

logistic_test: logistic_test.o 
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/logistic_test $(OBJECTS_DIR)/logistic_test.o $(OBJCOMP) $(LIBS)

pascal_test: pascal_test.o 
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/pascal_test $(OBJECTS_DIR)/pascal_test.o $(OBJCOMP) $(LIBS)

polya_test: polya_test.o 
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/polya_test $(OBJECTS_DIR)/polya_test.o $(OBJCOMP) $(LIBS)

beta_binomial_test: beta_binomial_test.o 
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/beta_binomial_test $(OBJECTS_DIR)/beta_binomial_test.o $(OBJCOMP) $(LIBS)

zipf_test: zipf_test.o 
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/zipf_test $(OBJECTS_DIR)/zipf_test.o $(OBJCOMP) $(LIBS)

gamma_test: gamma_test.o 
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/gamma_test $(OBJECTS_DIR)/gamma_test.o $(OBJCOMP) $(LIBS)

planck_test: planck_test.o 
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/planck_test $(OBJECTS_DIR)/planck_test.o $(OBJCOMP) $(LIBS)

yule_test: yule_test.o 
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/yule_test $(OBJECTS_DIR)/yule_test.o $(OBJCOMP) $(LIBS)

generalized_hypergeometric_b3_test: generalized_hypergeometric_b3_test.o 
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/generalized_hypergeometric_b3_test $(OBJECTS_DIR)/generalized_hypergeometric_b3_test.o $(OBJCOMP) $(LIBS)

generalized_waring_test: generalized_waring_test.o 
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/generalized_waring_test $(OBJECTS_DIR)/generalized_waring_test.o $(OBJCOMP) $(LIBS)

mizutani_test: mizutani_test.o 
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/mizutani_test $(OBJECTS_DIR)/mizutani_test.o $(OBJCOMP) $(LIBS)

waring_test: waring_test.o 
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/waring_test $(OBJECTS_DIR)/waring_test.o $(OBJCOMP) $(LIBS)

digamma_test: digamma_test.o 
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/digamma_test $(OBJECTS_DIR)/digamma_test.o $(OBJCOMP) $(LIBS)

trigamma_test: trigamma_test.o 
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/trigamma_test $(OBJECTS_DIR)/trigamma_test.o $(OBJCOMP) $(LIBS)

inverse_gaussian_test: inverse_gaussian_test.o 
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/inverse_gaussian_test $(OBJECTS_DIR)/inverse_gaussian_test.o $(OBJCOMP) $(LIBS)

wald_test: wald_test.o 
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/wald_test $(OBJECTS_DIR)/wald_test.o $(OBJCOMP) $(LIBS)

teichroew_test: teichroew_test.o 
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/teichroew_test $(OBJECTS_DIR)/teichroew_test.o $(OBJCOMP) $(LIBS)

pearson_vi_test.o : example/pearson_vi_test.cc
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/pearson_vi_test.o example/pearson_vi_test.cc

pearson_vi_test: pearson_vi_test.o 
	$(LINK) $(LFLAGS) -o $(BIN_DIR)/pearson_vi_test $(OBJECTS_DIR)/pearson_vi_test.o $(OBJCOMP) $(LIBS)

