#include <vg.hpp>

#include <iostream>
#include <algorithm>
#include <iterator>
#include <numeric>

using namespace vg;
using namespace std;

int main()
{
    variate_generator<double, exponential> vg(10.0);    

    copy( vg.begin(), vg.begin()+100, ostream_iterator<double>(cout, "\n"));

    auto sum = accumulate( vg.begin(), vg.begin()+100, 0.0 );

    cout << sum << endl;

    return 0;
}

