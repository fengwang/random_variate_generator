# Non-Uniform Random Variate Generator

>
> 無種而有生
> 
> 生已而覆滅
> 
> ------ 聖入楞伽寶經名為諸佛所說心髓品

## A Very Short Introduction

This library 

+ is a C++ library
+ is a header-only library
+ contains 62 kinds of non-uniform random variate generator


## A Quick Start

source code:

    //test.cc
	#include <vg.hpp>
	#include <cmath>
	#include <map>
	#include <iostream>

	using namespace std;

	int main()
	{
    	// a gaussian variate generator with parameter 0(the mean) and 4(the variance)
    	vg::variate_generator<double, vg::gaussian, vg::mt19937> v(0, 4);

    	map<int, int> sample;

    	for ( unsigned long int i = 0; i != 500; ++i )
        	sample[static_cast<int>(round(v()))]++;

    	for ( auto i = sample.begin(); i != sample.end(); ++i )
    	{
        	cout << "\n" << (*i).first << "\t";
        	for ( auto j = 0; j < (*i).second; ++j ) cout << "*";
    	}
    	std::cout << "\n";

    	return 0;
	}

command to compile:

    $g++ -o ./gaussian_test ./test.cc -std=c++14 -O2 -Iinclude(PATH_TO_HEADER_FILES)

following output will be produced after execution:

    -16 *
    -13 ***
    -12 ***
    -11 ***
    -10 *
    -9  ********
    -8  *********
    -7  **************
    -6  ************
    -5  ******************
    -4  **************************
    -3  *********************************
    -2  ******************************************
    -1  ****************************************************
    0   **************************************************
    1   **************************************************
    2   **********************************************
    3   ******************************
    4   ************************
    5   *******************
    6   ****************
    7   **************
    8   ******
    9   ****
    10  **
    11  ******
    12  *****
    14  *
    15  *
    16  *


## Reference in Detail

#### variate_generator 

The class template

    vg::variate_generator 
    

is defined in  __'include/vg/variate_generator.hpp'__   

    template < class Return_Type = double, template<class, class> class Distribution = uniform, class Engine = mitchell_moore >
    struct variate_generator;

##### Template Parameters   

***

>__Return_Type__ 
>> the variate __type__ this generator will generate, default is _double_

***

>__Distribution__
>> the variate __kind__ this generator will generate, default is _uniform_; 

***

>__Engine__
>> the pseudo-random number generator engine generating _unsigned long long_ interger employed by the generator, default is _vg::mitchell\_moore_, can also be one of _vg::lagged\_fibonacci_, _vg::linear\_congruential_ and _vg::mt19937_.

***

##### Member Types
The following alias is a member type of class _variate\_generator_:

***
>__distribution\_type__
>> Distribution\<Return_Type, Engine\>

***

>__seed\_type__
>> typename distribution_type::seed_type

***

>__return\_type__
>> typename distribution_type::return_type

***

>__size\_type__
>> std::size_t

***

>__self\_type__
>> variate_generator

***

##### Member Functions

* [Constructor](#toc_8)  -- creating instance of a variate generator
* [operator ()](#toc_10) -- generate a new variate of the specified distribution

###### variate_generator:: __(constructor)__
    
    template< typename ... Args >
    explicit variate_generator( Args ... args ) noexcept; 
    
Constructs a __variate\_generator__ with the specified given argument(s).  All the argument(s) will be passed to the constructor of the __Distribution__ type, which is given in the [template parameters](#toc_5).

####### variate_generator example:

    #include <vg.hpp>
	#include <iostream>

	int main()
	{
    	unsigned long int N = 10;
    	vg::variate_generator<int> vg( 0, 10 );
    	std::cout << "Uniform in [0,10):\n";
    	for ( unsigned long int index = 0; index != N; ++index )
      	  	std::cout << vg() << "\t";
    	std::cout << "\n";

    	vg::variate_generator<unsigned int, vg::poisson> vg_possion( 3 );
    	std::cout << "possion(3):\n";
    	for ( unsigned long int index = 0; index != N; ++index )
        	std::cout << vg_possion() << "\t";
    	std::cout << "\n";
    	
    	vg::variate_generator<unsigned int, vg::hypergeometric, vg::mt19937> vg_hypergeometric( 3, 4, 5 );
    	std::cout << "hypergeometric(3, 4, 5):\n";
    	for ( unsigned long int index = 0; index != N; ++index )
        	std::cout << vg_hypergeometric() << "\t";
    	std::cout << "\n";

    	return 0;
	}

Output:

	Uniform in [0,10):
	8	3	7	2	1	3	5	4	3	7
	possion(3):
	1	4	1	3	4	3	0	2	3	4
	hypergeometric(3, 4, 5):
	2	2	3	2	3	1	2	3	3	2


###### variate_generator:: __operator()__

    return_type operator()() const noexcept;

Returns a new random variate following the __Distribution__ parameters associated to this generator.

Return Type:

> A new random number.
> 
> return_type is a member type, defined as an alias of the first class [template parameter](#toc_5) (__Return\_Type_).
> 

###### variate_generator operator() example:

see [variate_generator::constructor example](#toc_9) above.

### Distributions

There should be some indeces here. TODO:

#### Arcsine Distribution

Produces random variates that are following [arcsine distribution](http://en.wikipedia.org/wiki/Arcsine_distribution).

The template class

	template < typename Return_Type, typename Engine >
    struct arcsine;

is defined in 'include/vg/distribution/arcsine.hpp'.

##### arcsine Template Parameters

see [Template Parameters in variate_generator](#toc_5).

##### arcsine Member Types

see [Member Types in varaite_generator](#toc_6).

##### arcsine Member Functions

###### arcsine::constructor:

	explicit arcsine( const seed_type sd = 0 ) noexcept;

The constructor expects a _seed_ for the engine inside this distrubtion class.

	
###### arcsine::operator()
	
	return_type operator()() const noexcept
	
Generates a new random variate following the arcsine distribution.

Example:

	#include <vg.hpp>
	#include <iostream>

	int main()
	{
    	vg::variate_generator<double, vg::arcsine> v;

    	for ( unsigned long int i = 0; i != 10; ++i )
        	std::cout << v() << "\t";

    	std::cout << "\n";

    	return 0;
	} 	
	 
Output:

	0.0548315	0.92341	0.884892	0.441578	0.985113	0.460975	0.0877635	0.164131	0.999518	0.531236
		

####	Balding–Nichols Distirubtion

Produces random variates that are following [Balding–Nichols Distirubtion](http://en.wikipedia.org/wiki/Balding%E2%80%93Nichols_model).

The template class

    template < typename Return_Type, typename Engine >
    struct balding_nichols
    
is defined in 'include/vg/distribution/balding_nichols.hpp'.






