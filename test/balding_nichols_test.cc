#include <vg.hpp>
#include "test.hpp"
#include <vector>
#include <cstddef>

int main()
{
    double p = 0.5;
    double f = 0.5;
    double mean = p;
    double variance = f*p*(1.0-p);
    double skew = 2.0 * f * ( 1.0 - p - p ) / ( ( 1.0 + f ) * std::sqrt( f * ( 1.0-p) * p) );
    auto vg_ = vg::make_variate_generator<double, vg::balding_nichols>( p, f );

    std::size_t n = 10000000;
    std::vector<double> x(n);

    std::generate( x.begin(), x.end(), vg_ );

    test( x.begin(), x.end(), "balding_nichols", mean, variance, skew); 

    return 0;
}

