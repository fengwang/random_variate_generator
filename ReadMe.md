# Non-Uniform Random Variate Generator

This is a non-uniform random variate generator library, in c++20, single-file and header-only.



## A Quick Start

Quick start source code(1):

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

    $g++ -o ./gaussian_test ./test.cc -std=c++14 -O2 -Iinclude(PATH)

Output:

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


Quick start source code(2):

    //make_passwd.cc
    #include <vg.hpp>
	#include <iostream>
	#include <vector>
	#include <iterator>
	#include <algorithm>

	int main()
	{
    	char chars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    	//char chars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890`~!@#$%^&*()_+\\|[]{}'\";:/?>.<,";
    	vg::variate_generator<unsigned long> v{ 0UL, sizeof(chars)/sizeof(char) };
    	unsigned long const password_length = std::max( v(), 10UL );
    	std::vector<char> password( password_length );
    	std::generate( password.begin(), password.end(), [&](){ return chars[v()]; } );
    	std::copy( password.begin(), password.end(), std::ostream_iterator<char>( std::cout, "" ) );
    	std::cout << "\n";

    	return 0;
	}

compile:

    g++ -o make_passwd make_passwd.cc -std=c++14 -O2 -I(PATH)

Output:

    5Tq5kxmmnULP3qh1qa5pT9bOYzJ

##Reference

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
The following alias defined as member types of class _variate\_generator_:

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

* [Constructor](#variate_generator-constructor)  -- creating instance of a variate generator
* [operator ()](#-variate_generator-example) -- generate a new variate of the specified distribution

###### variate_generator:: __(constructor)__

    template< typename ... Args >
    explicit variate_generator( Args ... args ) noexcept;

Constructs a __variate\_generator__ with the specified given argument(s).  All the argument(s) will be passed to the constructor of the [__Distribution__ type](#distributions), which is specified in the [template parameters](#template-parameters).

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
> return_type is a member type, defined as an alias of the first class [template parameter](#template-parameters) (__Return\_Type_).
>

###### variate_generator operator() example:

see [variate_generator::constructor example](#-variate_generator-example) above.

### Distributions

There should be some indeces here. TODO:

#### Arcsine Distribution

Produces random variates that are following [arcsine distribution](http://en.wikipedia.org/wiki/Arcsine_distribution).

The template class

	template < typename Return_Type, typename Engine >
    struct arcsine;

is defined in ['include/vg/distribution/arcsine.hpp'](./include/vg/distribution/arcsine.hpp).

##### arcsine Template Parameters

see [Template Parameters in variate_generator](#template-parameters).

##### arcsine Member Types

see [Member Types in varaite_generator](#member-types).

##### arcsine Member Functions

###### arcsine::constructor:

	explicit arcsine( const seed_type sd = 0 ) noexcept;

The constructor expects a parameter _sd_ for the engine inside this distrubtion class, and if this parameter is not given, a default _sd_ will be used.


###### arcsine::operator()

	return_type operator()() const noexcept

Generates a new random variate following the __Arcsine__ distribution.

##### arcsine Example:

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
    struct balding_nichols;

is defined in ['include/vg/distribution/balding_nichols.hpp'](./include/vg/distribution/balding_nichols.hpp).

##### Balding–Nichols Template Parameters

see [Template Parameters in variate_generator](#template-parameters).

##### Balding–Nichols Member Types

see [Member Types in varaite_generator](#member-types).

##### Balding–Nichols Member Functions

###### Balding-Nichols constructor

    explicit balding_nichols( const final_type f = final_type(0.5), const final_type p = final_type(0.5), const seed_type sd = 0 ) noexcept;

The constructor expects three paremeters. The first two real parameters f and p, are subject to 0 < f < 1 and 0 < p < 1, and the third paremeter, _sd_, is for the engine employed by the distrubtion, and if _sd_ is not provided, a default one will be used.

###### Balding-Nichols operator()

	return_type operator()() const noexcept;

Generates a new random variate that follows Balding Nichols distribution.

##### Balding-Nichols Example

    #include <vg.hpp>
    #include <iostream>

    int main()
    {
    	vg::variate_generator<double, vg::balding_nichols> v{ 0.2, 0.7 };

    	for ( unsigned long int i = 0; i != 10; ++i )
        	std::cout << v() << "\t";

    	std::cout << "\n";

    	return 0;
    }

Output:

    0.947175	0.232065	0.783228	0.942613	0.404222	0.789025	0.916455	0.941101	0.533812	0.822633

####	Bernoulli Distirubtion

Produces random variates that are following [Bernoulli Distirubtion](http://en.wikipedia.org/wiki/Bernoulli_distribution).

The template class

    template < typename Return_Type, typename Engine >
    struct bernoulli;

is defined in ['include/vg/distribution/bernoulli.hpp'](./include/vg/distribution/bernoulli.hpp).

##### Bernoulli Template Parameters

see [Template Parameters in variate_generator](#template-parameters).

##### Bernoulli Member Types

see [Member Types in varaite_generator](#member-types).

##### Bernoulli Member Functions

###### Bernoulli constructor

    explicit bernoulli( final_type p = final_type( 0.5 ), const seed_type s = seed_type( 0 ) ) noexcept;

The constructor expects two paremeters. The first p is subject to 0 < p < 1, and the last paremeter, _s_, is for the engine employed by the distrubtion, and if _s_ is not provided, a default one will be used.

###### Bernoulli operator()

	return_type operator()() const noexcept;

Generates a new random variate that follows __Bernoulli__ distribution.

##### Bernoulli Example

    #include <vg.hpp>
	#include <iostream>

	int main()
	{
    	vg::variate_generator<int, vg::bernoulli> v{ 0.34 };

    	for ( unsigned long int i = 0; i != 10; ++i )
        	std::cout << v() << "\t";

    	std::cout << "\n";

    	return 0;
	}

Output:

    0	0	1	0	0	1	1	1	0	1



####Beta Distirubtion

Produces random variates that are following [Beta Distirubtion](http://en.wikipedia.org/wiki/Beta_distribution).

The template class

    template < typename Return_Type, typename Engine >
    struct beta;

is defined in ['include/vg/distribution/beta.hpp'](./include/vg/distribution/beta.hpp).

##### Beta Template Parameters

see [Template Parameters in variate_generator](#template-parameters).

##### Beta Member Types

see [Member Types in varaite_generator](#member-types).

##### Beta Member Functions

###### Beta constructor

    explicit beta( const value_type a = value_type( 1 ), const value_type b = value_type( 1 ), const seed_type sd = 0 ) noexcept;

The constructor expects three paremeters. The first two are positive shape parameters, and the last paremeter, _sd_, is for the engine employed by the distrubtion, and if _sd_ is not provided, a default one will be used.

###### Beta operator()

	return_type operator()() const noexcept;

Generates a new random variate that follows __Beta__ distribution.

##### Beta Example

    #include <vg.hpp>
	#include <iostream>

	int main()
	{
    	vg::variate_generator<double, vg::beta, vg::mt19937> v{ 0.1, 0.2, 19876238763287ULL };

    	for ( unsigned long int i = 0; i != 10; ++i )
        	std::cout << v() << "\t";

    	std::cout << "\n";

    	return 0;
	}

Output:

    0.141858	1.60925e-06	9.89096e-05	7.39141e-05	0.00105271	6.55803e-09	0.724791	0.0842294	0.0221139	0.436397

####Beta Binomial Distirubtion

Produces random variates that are following [Beta Binomial Distirubtion](http://en.wikipedia.org/wiki/Beta-binomial_distribution).

The template class

    template < typename Return_Type, typename Engine >
    struct beta_binomial;

is defined in ['include/vg/distribution/beta_binomial.hpp'](./include/vg/distribution/beta_binomial.hpp).

##### Beta Binomial Template Parameters

see [Template Parameters in variate_generator](#template-parameters).

##### Beta Binomial Member Types

see [Member Types in varaite_generator](#member-types).

##### Beta Binomial Member Functions

###### Beta Binomial constructor

    explicit beta_binomial( const value_type n = value_type( 10 ),
                            const final_type a = final_type(1),
                            const final_type b = final_type(1),
                            const seed_type sd = 0 ) noexcept;

The constructor expects 4 paremeters. The first parameter, _n_, is an interger representing Bernoulli trials, while _a_ and _b_ are two positive shape parameters, and the last paremeter, _sd_, is for the engine employed by the distrubtion, and if _sd_ is not provided, a default one will be used.

###### Beta Binomial operator()

	return_type operator()() const noexcept;

Generates a new random variate that follows __Beta Binomial__ distribution.

##### Beta Binomial Example

    #include <vg.hpp>
	#include <iostream>

	int main()
	{
    	vg::variate_generator<int, vg::beta_binomial, vg::linear_congruential> v{ 10, 0.4, 0.5, 98187638263287932ULL };

    	for ( unsigned long int i = 0; i != 10; ++i )
        	std::cout << v() << "\t";

    	std::cout << "\n";

    	return 0;
	}

Output:

   1	6	0	1	0	0	0	1	0	3

####Binomial Distirubtion

Produces random variates that are following [Binomial Distirubtion](http://en.wikipedia.org/wiki/Binomial_distribution).

The template class

    template < typename Return_Type, typename Engine >
    struct binomial;

is defined in ['include/vg/distribution/binomial.hpp'](./include/vg/distribution/binomial.hpp).

##### Binomial Template Parameters

see [Template Parameters in variate_generator](#template-parameters).

##### Binomial Member Types

see [Member Types in varaite_generator](#member-types).

##### Binomial Member Functions

###### Binomial constructor

    explicit binomial( size_type n = size_type( 1 ),
                       final_type p = final_type( 0.5 ),
                       const seed_type sd = seed_type( 0 ) ) noexcept;

The constructor expects 3 paremeters. The first parameter, _n_, is an interger representing number of trials, while _p_ is a positive parameter of the success probability of the trial, and the last paremeter, _sd_, is for the engine employed by the distrubtion, and if _sd_ is not provided, a default one will be used.

###### Binomial operator()

	return_type operator()() const noexcept;

Generates a new random variate that follows Binomial distribution.

##### Binomial Example

   	#include <vg.hpp>
	#include <iostream>

	int main()
	{
    	vg::variate_generator<int, vg::binomial> v{ 10, 0.4 };

    	for ( unsigned long int i = 0; i != 10; ++i )
        	std::cout << v() << "\t";

    	std::cout << "\n";

    	return 0;
	}


Output:

   3	4	3	3	3	6	4	5	4	5

####Burr Distirubtion

Produces random variates that are following [Burr Distirubtion
Family](http://dx.doi.org/10.1214%2Faoms%2F1177731607).

The template class

    template < typename Return_Type, typename Engine >
    struct burr;

is defined in ['include/vg/distribution/burr.hpp'](./include/vg/distribution/burr.hpp).

##### Burr Template Parameters

see [Template Parameters in variate_generator](#template-parameters).

##### Burr Member Types

see [Member Types in varaite_generator](#member-types).

##### Burr Member Functions

###### Burr constructor

    explicit burr( const size_type  n = size_type(1),
                   const final_type c = final_type(1),
                   const final_type k = final_type(1),
                   const final_type r = final_type(1),
                   const seed_type sd = 0 ) noexcept;

The constructor expects 5 paremeters. The first parameter, _n_, is an interger representing index of the distribution in Burr family, which is subject to 0 < n < 13, while _c_, _k_ and _r_ are positive real numbers, and the last paremeter, _sd_, is for the engine employed by the distrubtion, and if _sd_ is not provided, a default one will be used.

###### Burr operator()

	return_type operator()() const noexcept;

Generates a new random variate that follows __Burr__ distribution.

##### Burr Example

   	#include <vg.hpp>
	#include <iostream>

	int main()
	{
    	for ( unsigned long int index = 1; index != 13; ++index )
    	{
        	vg::variate_generator<double, vg::burr> v{ index, 1.0, 2.0, 3.0 };

        	std::cout << "Burr--[" << index << "]:\n";
        	for ( unsigned long int i = 0; i != 10; ++i )
            	std::cout << v() << "\t";

        	std::cout << "\n";
    	}

    	return 0;
	}


Output:

   	Burr--[1]:
	0.691701	0.503969	0.775365	0.616878	0.910301	0.259373	0.340916	0.0500518	0.293938	0.555238
	Burr--[2]:
	1.05542	2.71497	-0.218548	-0.0761166	1.17026	1.78444	0.884203	1.30093	0.631601	1.54087
	Burr--[3]:
	1.64714	2.00575	1.65232	0.591113	1.67746	2.43094	1.13836	2.05393	1.5601	2.298
	Burr--[4]:
	0.928387	0.684173	0.857723	0.601024	0.630111	0.956288	0.776311	0.991735	0.571119	0.595129
	Burr--[5]:
	1.3221	0.957629	0.889189	0.543457	1.11291	1.23837	1.17445	0.887858	1.13989	0.448486
	Burr--[6]:
	1.33317	1.61416	0.587275	1.88367	1.85513	1.26575	2.03609	1.54311	1.2578	-0.0170988
	Burr--[7]:
	1.25635	0.459867	1.49758	-0.127729	0.960515	-0.0670914	0.794886	2.48393	0.868511	1.0654
	Burr--[8]:
	-0.715498	-0.0967954	3.51838	0.233612	0.0809866	2.07674	0.828366	1.38016	0.396843	-0.630856
	Burr--[9]:
	-0.421246	-0.766305	-1.65146	-1.37102	-0.257663	-1.15828	-1.11598	-0.930168	-0.9182	-1.67391
	Burr--[10]:
	1.05374	1.24458	1.11537	1.22802	0.920393	1.60435	1.11702	0.712841	2.09835	1.50033
	Burr--[11]:
	0.000104468	0.000104468	0.000104468	0.000104468	0.000104468	0.000104468	0.000104468	0.000104468	0.000104468	0.000104468
	Burr--[12]:
	2.42904	0.217242	0.0023998	0.13086	0.939905	0.197871	0.00245561	0.282117	2.11047	1.83234

####Chi Square Distirubtion

Produces random variates that are following [Chi Square Distirubtion](http://en.wikipedia.org/wiki/Chi-squared_distribution).

The template class

    template < typename Return_Type, typename Engine >
    struct chi_square;

is defined in ['include/vg/distribution/chi_squre.hpp'](./include/vg/distribution/chi_square.hpp).

##### Chi Square Template Parameters

see [Template Parameters in variate_generator](#template-parameters).

##### Chi Square Member Types

see [Member Types in varaite_generator](#member-types).

##### Chi Square Member Functions

###### Chi Square constructor

    explicit chi_square( const size_type k = 10, const seed_type sd = 0 ) noexcept;

The constructor expects 2 paremeters. The first parameter, _k_, is a positive interger representing the degrees of freedom, and the last paremeter, _sd_, is for the engine employed by the distrubtion, and if _sd_ is not provided, a default one will be used.

###### Chi Square operator()

	return_type operator()() const noexcept;

Generates a new random variate that follows __Chi Square__ distribution.

##### Chi Square Example

    #include <vg.hpp>
	#include <iostream>

	int main()
	{
    	vg::variate_generator<double, vg::chi_square> v{ 10 };

    	for ( unsigned long int i = 0; i != 10; ++i )
        	std::cout << v() << "\t";

    	std::cout << "\n";

    	return 0;
	}


Output:

   	25.0486	12.4258	22.4472	14.5258	17.4818	13.0089	8.77502	13.2517	7.47055	11.0505

