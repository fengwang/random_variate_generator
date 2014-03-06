#include <vg.hpp>
#include <cmath>
#include <map>
#include <iostream>

int main()
{
    //generate double gaussian random numbers with argument (0,4), i.e. N(0,4)
    //using mt19937 as uniform random generator engine
    vg::variate_generator<double, vg::gaussian, vg::mt19937> vg_(0, 4);    
    std::map< int, int > sample;

    //generate 500 gaussian numbers and store it in a map
    for ( auto i = vg_.begin(); i != vg_.begin()+500; ++i )
        sample[std::round(*i)]++;

    //show the number generated
    for ( auto i = sample.begin(); i != sample.end(); ++i )
    {
        std::cout << (*i).first << "\t";
        for ( auto j = 0; j < (*i).second; ++j )
            std::cout << "*";
        std::cout << "\n";
    }

    return 0;
}

