#include <vg.hpp>
#include "test.hpp"
#include <cmath>
#include <vector>
#include <cstddef>
int main()
{
    vg::variate_generator<double, vg::beta_binomial, vg::mt19937> vg_( 100.0, 0.1, 0.2 );
    std::size_t n = 10000000;
    std::vector<double> x(n);
    std::generate( x.begin(), x.end(), vg_ );
    auto const& mean = []( double n, double a, double b ){ return n * a / ( a+b ); };
    auto const& variance = []( double n, double a, double b ) { return n * a * b * (a+b+n)/((a+b)*(a+b)*(a+b+1)); };
    auto const& skewness = []( double n, double a, double b ) { return ( a+b+n+n)*(b-a)/(a+b+2)*std::sqrt((1+a+b)/(n*a*b*(a+b))); };
    test( x.begin(), x.end(), "beta_binomial", mean(100, 0.1, 0.2), variance(100, 0.1, 0.2), skewness(100, 0.1, 0.2), -1.5 );
    return 0;
}
