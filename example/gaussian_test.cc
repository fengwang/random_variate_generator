#include <vg.hpp>

#include <cmath>
#include <map>
#include <iostream>

using namespace vg;
using namespace std;

int main()
{
    variate_generator<double, gaussian, vg::mt19937> vg(0, 4);    
    map< int, int > sample;

    for ( auto i = vg.begin(); i != vg.begin()+500; ++i )
        sample[round(*i)]++;

    for ( auto i = sample.begin(); i != sample.end(); ++i )
    {
        cout << "\n" << (*i).first << "\t";
        for ( auto j = 0; j < (*i).second; ++j )
            cout << "*";
    }

    return 0;
}

