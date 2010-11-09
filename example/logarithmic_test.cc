#include <vg.hpp>

#include <iostream>
#include <algorithm>
#include <iterator>
#include <numeric>

using namespace vg;
using namespace std;

int main()
{
    variate_generator<double, logarithmic> vg(0.33);    

    copy( vg.begin(), vg.begin()+1000, ostream_iterator<double>(cout, "\n"));


    auto sum = accumulate( vg.begin(), vg.begin()+1000, 0.0 );

    cout << sum << endl;

    return 0;
}

