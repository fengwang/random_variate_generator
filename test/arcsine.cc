#include <vg.hpp>
#include "test.hpp"
#include <vector>
#include <cstddef>

int main()
{
    vg::variate_generator<double, vg::arcsine, vg::mt19937> vg_;    

    std::size_t n = 10000000;
    std::vector<double> x(n);

    std::generate( x.begin(), x.end(), vg_ );

    test( x.begin(), x.end(), "arcsine", 0.5, 0.125, 0); 

    return 0;
}
