#include <vg.hpp>
#include "test.hpp"
#include <vector>
#include <cstddef>

int main()
{
    vg::variate_generator<double, vg::uniform, vg::mt19937> vg_(-1, 1);

    std::size_t const n = 10000000;
    std::vector<double> x(n);

    std::generate( x.begin(), x.end(), vg_ );

    test( x.begin(), x.end(), "uniform", 0, 4.0/12, 0.0); 

    return 0;
}
