#include <vg.hpp>

#include <iostream>
#include <algorithm>
#include <iterator>
#include <numeric>

using namespace vg;
using namespace std;

int main()
{
    variate_generator<double, laplace> vg(11, 1.3);    

    copy( vg.begin(), vg.begin()+10000, ostream_iterator<int>(cout, "\n"));


    auto sum = accumulate( vg.begin(), vg.begin()+10000, 0.0 );

    cout << sum << endl;

    return 0;
}

