## A short Introduction
vg is a pseudo-random variate generator library, aiming to generate a large amount of random numbers, with a luxury kinds of built-in distributions(currently 62), aiding applications in gambling, statistical sampling, computer simulation, cryptography, completely randomized design, and other areas where producing an unpredictable result is desirable. In the wake of C++ generic template meta-programming, it is written in c++, compatible with STL.

## Quick Start
For a very quick start, here is an example(can be found in file "example/gaussian_test.cc"):

    #include <vg.hpp>
    #include <cmath>
    #include <map>
    #include <iostream>

    using namespace std;

    int main()
    {
        // a gaussian variate generator with parameter 0(the mean) and 4(the variance),
        // the variate type is double,
        // default pseudo-number generator engine is mt19937,
        // the seed for the engine is 0, which is the third argument, but is simply ignored here, or we
        // would have to write variate_generator<double, gaussian, vg::mt19937> v(0, 4, 0);
        vg::variate_generator<double, vg::gaussian, vg::mt19937> v(0, 4);    

        map< int, int > sample;

        for ( auto i = v.begin(); i != v.begin()+500; ++i )
            sample[round(*i)]++;

        for ( auto i = sample.begin(); i != sample.end(); ++i )
        {
            cout << "\n" << (*i).first << "\t";
            for ( auto j = 0; j < (*i).second; ++j ) cout << "*";
        }

        return 0;
    }

command to compile:

    $g++ -o bin/gaussian_test example/gaussian_test.cc -std=c++11 -O2 -Iinclude

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

Please check out doc/vg.pdf for more information.

