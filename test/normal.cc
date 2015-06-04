#include <vg.hpp>

#include "test.hpp"

#include <vector>
#include <cstddef>

int main()
{
    //vg::variate_generator<double, vg::normal, vg::mt19937> vg_(13);    
    vg::variate_generator<double, vg::normal, vg::mt19937> vg_;    
    //vg::variate_generator<double, vg::normal, vg::lagged_fibonacci> vg_;    

    std::size_t n = 10000000;
    std::vector<double> x(n);

    std::generate( x.begin(), x.end(), vg_ );

    test( x.begin(), x.end(), "normal", 0, 1, 0); 

    return 0;
}

