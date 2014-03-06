#include <vg.hpp>
#include "test.hpp"
#include <vector>
#include <cstddef>
int main()
{
    vg::variate_generator<double, vg::bernoulli, vg::mt19937> vg_(0.5);    
    std::size_t n = 10000000;
    std::vector<double> x(n);
    std::generate( x.begin(), x.end(), vg_ );
    test( x.begin(), x.end(), "bernoulli", 0.5, 0.25, 0 ); 
    return 0;
}
