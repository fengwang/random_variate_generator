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

