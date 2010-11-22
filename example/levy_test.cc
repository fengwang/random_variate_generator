#include <vg.hpp>

#include <iostream>
#include <algorithm>
#include <iterator>
#include <numeric>

using namespace vg;
using namespace std;

int main()
{
    variate_generator<double, vg::levy, vg::mt19937> vg(1.5, 1.5);    

    copy( vg.begin(), vg.begin()+1000, ostream_iterator<double>(cout, "\n"));

    auto sum = accumulate( vg.begin(), vg.begin()+1000, 0.0 );

    cout << sum << endl;

    return 0;
}

