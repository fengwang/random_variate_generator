#include <vg.hpp>
#include "test.hpp"
#include <cmath>
#include <vector>
#include <cstddef>
int main()
{
    vg::variate_generator<double, vg::gaussian, vg::mt19937> vg_( 1.0, 2.0 );
    std::size_t n = 10000000;
    std::vector<double> x(n);
    std::generate( x.begin(), x.end(), vg_ );
    test( x.begin(), x.end(), "beta_binomial", 1.0, 4.0, 0.0 ); 
    return 0;
}
