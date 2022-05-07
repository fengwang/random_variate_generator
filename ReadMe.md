# Non-Uniform Random Variate Generator

This is a non-uniform random variate generator, a single-file header-only library written in C++.


--------

+ [Start](#a-quick-start)
+ [Usage](#basic-usage)
+ [Examples](#examples)
    - [arcsin distribution](#arcsin-distribution)
    - [balding_nichols distribution](#balding_nichols-distribution)
    - [bernoulli distribution](#bernoulli-distribution)
    - [beta distribution](#beta-distribution)
    - [beta_binomial distribution](#beta_binomial-distribution)
    - [beta_pascal distribution](#beta_pascal-distribution)
    - [beta_pascal distribution](#beta_pascal-distribution)
    - [binomial distribution](#binomial-distribution)
    - [burr distribution](#burr-distribution)
    - [cauchy distribution](#cauchy-distribution)
    - [chi_square distribution](#chi_square-distribution)
    - [digamma distribution](#digamma-distribution)
    - [erlang distribution](#erlang-distribution)
    - [exponential distribution](#exponential-distribution)
    - [exponential_power distribution](#exponential_power-distribution)
    - [extreme_value distribution](#extreme_value-distribution)
    - [f distribution](#f-distribution)
    - [factorial distribution](#factorial-distribution)
    - [gamma distribution](#gamma-distribution)
    - [gaussian distribution](#gaussian-distribution)
    - [gaussian_tail distribution](#gaussian_tail-distribution)
    - [generalized_hypergeometric_b3 distribution](#generalized_hypergeometric_b3-distribution)
    - [generalized_waring distribution](#generalized_waring-distribution)
    - [geometric distribution](#geometric-distribution)
    - [grassia distribution](#grassia-distribution)
    - [gumbel_1 distribution](#gumbel_1-distribution)
    - [gumbel_2 distribution](#gumbel_2-distribution)
    - [hyperbolic_secant distribution](#hyperbolic_secant-distribution)
    - [hypergeometric distribution](#hypergeometric-distribution)
    - [inverse_gaussian distribution](#inverse_gaussian-distribution)
    - [inverse_polya_eggenberger distribution](#inverse_polya_eggenberger-distribution)
    - [lambda distribution](#lambda-distribution)
    - [laplace distribution](#laplace-distribution)
    - [levy distribution](#levy-distribution)
    - [logarithmic distribution](#logarithmic-distribution)
    - [logistic distribution](#logistic-distribution)
    - [lognormal distribution](#lognormal-distribution)
    - [mizutani distribution](#mizutani-distribution)
    - [negative_binomial distribution](#negative_binomial-distribution)
    - [negative_binomial_beta distribution](#negative_binomial_beta-distribution)
    - [normal distribution](#normal-distribution)
    - [pareto distribution](#pareto-distribution)
    - [pascal distribution](#pascal-distribution)
    - [pearson distribution](#pearson-distribution)
    - [planck distribution](#planck-distribution)
    - [poisson distribution](#poisson-distribution)
    - [polya distribution](#polya-distribution)
    - [polya_aeppli distribution](#polya_aeppli-distribution)
    - [rademacher distribution](#rademacher-distribution)
    - [rayleigh distribution](#rayleigh-distribution)
    - [rayleigh_tail distribution](#rayleigh_tail-distribution)
    - [singh_maddala distribution](#singh_maddala-distribution)
    - [t distribution](#t-distribution)
    - [teichroew distribution](#teichroew-distribution)
    - [triangular distribution](#triangular-distribution)
    - [trigamma distribution](#trigamma-distribution)
    - [uniform distribution](#uniform-distribution)
    - [von_mises distribution](#von_mises-distribution)
    - [wald distribution](#wald-distribution)
    - [waring distribution](#waring-distribution)
    - [weibull distribution](#weibull-distribution)
    - [yule distribution](#yule-distribution)
    - [zipf distribution](#zipf-distribution)
+ [License](#license)

--------


## A Quick Start

Quick start source code(1):

```cpp
    //test.cc
	#include <vg.hpp> // just copy this file  from include/vg.hpp
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
```

command to compile:

```bash
    $g++ -o ./gaussian_test ./test.cc -std=c++14 -O2 -Iinclude(PATH)
```

Output:

```bash
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
```


Quick start source code(2):

```cpp
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
```

compile:

```bash
    g++ -o make_passwd make_passwd.cc -std=c++14 -O2 -I(PATH)
```

Output:

    5Tq5kxmmnULP3qh1qa5pT9bOYzJ


## Basic usage

First create a generator
```cpp
vg::variate_generator<double, vg::exponential, vg::mt19937> gen{ 1.0 };
```
in which
- `double` is the data type we want to generate,
- `vg::exponentional` is the random distribution,
- `vg::mt19937` is the random number engine, and
- `1.0` is the parameter possed to the random distribution `vg::exponential`.

we use `gen` as a generator/functor

```cpp
for ( int i = 0; i < 10; ++i )
    std::cout << gen();
```



## Examples



### arcsin distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::arcsin, vg::mt19937> gen{  };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### balding_nichols distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::balding_nichols, vg::mt19937> gen{ 0.5, 0.5 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### bernoulli distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::bernoulli, vg::mt19937> gen{ 0.5 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### beta distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::beta, vg::mt19937> gen{ 1.0, 1.0 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### beta_binomial distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::beta_binomial, vg::mt19937> gen{ 10.0, 1.0, 1.0 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### beta_pascal distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::beta_pascal, vg::mt19937> gen{ 3.0, 3.0 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### beta_pascal distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::beta_pascal, vg::mt19937> gen{ 3.0, 3.0 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### binomial distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<unsigned long, vg::binomial, vg::mt19937> gen{ 1, 0.5 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### burr distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::burr, vg::mt19937> gen{ 1, 1.0, 1.0, 1.0 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### cauchy distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::cauchy, vg::mt19937> gen{ 1.0 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### chi_square distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::chi_square, vg::mt19937> gen{ 10 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### digamma distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::digamma, vg::mt19937> gen{ 3, 3 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### erlang distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::erlang, vg::mt19937> gen{ 1.0, 10.0 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### exponential distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::exponential, vg::mt19937> gen{ 1.0 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### exponential_power distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::exponential_power, vg::mt19937> gen{ 1.0, 1.0 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### extreme_value distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::extreme_value, vg::mt19937> gen{ 0.0, 1.0, 0.0 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### f distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::f, vg::mt19937> gen{ 2.0, 2.0 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### factorial distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::factorial, vg::mt19937> gen{ 3.0, 3.0 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### gamma distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::gamma, vg::mt19937> gen{ 1.0, 1.0 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### gaussian distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::gaussian, vg::mt19937> gen{ 0.0, 1.0 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### gaussian_tail distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::gaussian_tail, vg::mt19937> gen{ 0.0, 1.0 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### generalized_hypergeometric_b3 distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::generalized_hypergeometric_b3, vg::mt19937> gen{ 1.0, 1.0, 1.0 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### generalized_waring distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::generalized_waring, vg::mt19937> gen{ 1.0, 1.0, 1.0 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### geometric distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::geometric, vg::mt19937> gen{ 0.5 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### grassia distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::grassia, vg::mt19937> gen{ 1.0, 1.0 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### gumbel_1 distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::gumbel_1, vg::mt19937> gen{ 1.0, 1.0 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### gumbel_2 distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::gumbel_2, vg::mt19937> gen{ 1.0, 1.0 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### hyperbolic_secant distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::hyperbolic_secant, vg::mt19937> gen{  };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### hypergeometric distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<unsigned long, vg::hypergeometric, vg::mt19937> gen{ 1, 0, 1 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### inverse_gaussian distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::inverse_gaussian, vg::mt19937> gen{ 1.0, 1.0 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### inverse_polya_eggenberger distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::inverse_polya_eggenberger, vg::mt19937> gen{ 1.0, 1.0, 1.0 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### lambda distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::lambda, vg::mt19937> gen{ 1.0, 1.0, 1.0, 1.0 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### laplace distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::laplace, vg::mt19937> gen{ 1.0, 1.0 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### levy distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::levy, vg::mt19937> gen{ 1.0, 1.0 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### logarithmic distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::logarithmic, vg::mt19937> gen{ 0.5 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### logistic distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::logistic, vg::mt19937> gen{ 1.0, 1.0 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### lognormal distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::lognormal, vg::mt19937> gen{ 1.0, 1.0 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### mizutani distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::mizutani, vg::mt19937> gen{ 1.0 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### negative_binomial distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::negative_binomial, vg::mt19937> gen{ 1, 0.5 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### negative_binomial_beta distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::negative_binomial_beta, vg::mt19937> gen{ 1.0, 1.0, 1.0 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### normal distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::normal, vg::mt19937> gen{  };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### pareto distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::pareto, vg::mt19937> gen{ 1.0, 2.0 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### pascal distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::pascal, vg::mt19937> gen{ 1.0, 0.5 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### pearson distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::pearson, vg::mt19937> gen{ 1.0, 1.0, 1.0, 1.0, 1.0 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### planck distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::planck, vg::mt19937> gen{ 1.0, 1.0 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### poisson distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::poisson, vg::mt19937> gen{ 10.0 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### polya distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::polya, vg::mt19937> gen{ 1.0, 0.5 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### polya_aeppli distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::polya_aeppli, vg::mt19937> gen{ 1.0, 1.0, 1.0 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### rademacher distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::rademacher, vg::mt19937> gen{  };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### rayleigh distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::rayleigh, vg::mt19937> gen{ 1.0 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### rayleigh_tail distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::rayleigh_tail, vg::mt19937> gen{ 1.0 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### singh_maddala distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::singh_maddala, vg::mt19937> gen{ 1.0, 1.0, 1.0 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### t distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::t, vg::mt19937> gen{ 1.0 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### teichroew distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::teichroew, vg::mt19937> gen{ 1.0 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### triangular distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::triangular, vg::mt19937> gen{ 1.0 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### trigamma distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::trigamma, vg::mt19937> gen{ 3.0 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### uniform distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::uniform, vg::mt19937> gen{ 0.0, 1.0 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### von_mises distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::von_mises, vg::mt19937> gen{ 0.0, 1.0 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### wald distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::wald, vg::mt19937> gen{ 1.0, 1.0 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### waring distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::waring, vg::mt19937> gen{ 1.0, 1.0 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### weibull distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::weibull, vg::mt19937> gen{ 1.0, 1.0 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### yule distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::yule, vg::mt19937> gen{ 2.0 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```


### zipf distribution

```cpp
#include <vg.hpp>
#include <vector>
#include <iostream>

int main()
{
    unsigned long const n = 1000000;
    std::vector<double> x(n);
    vg::variate_generator<double, vg::zipf, vg::mt19937> gen{ 2.0 };
    for ( unsigned long idx = 0; idx < n; ++idx ) x[idx] = gen();

    std::cout << "Testing arcsin distribution: with " << n << " examples.\n" ;
    std::cout << "Mean:	" << vg::mean( x.begin(), x.end() ) << "\n";
    std::cout << "Variance:	" << vg::variance( x.begin(), x.end() ) << "\n";
    std::cout << "Skewness:	" << vg::skewness( x.begin(), x.end() ) << "\n";

    return 0;
}
```






## License

LGPL




