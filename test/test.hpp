#ifndef _TEST_HPP_INCLUDED_SFDPOIHJASHSAFD
#define _TEST_HPP_INCLUDED_SFDPOIHJASHSAFD

#include <iostream>
#include <string>
#include <iterator>
#include <vg/utility.hpp>

template<typename Input_Iterator>
void test( 
           Input_Iterator first, Input_Iterator last, 
           const std::string& name, 
           const typename std::iterator_traits<Input_Iterator>::value_type _mean,
           const typename std::iterator_traits<Input_Iterator>::value_type _variance,
           const typename std::iterator_traits<Input_Iterator>::value_type _skewness,
           const typename std::iterator_traits<Input_Iterator>::value_type _kurtosis
         )
{
    std::cout << "\nTesting ["<< name << "] engine with n = " << std::distance( first, last ) << "\n";
    std::cout << "|        |\tTheory\t|\tPseudo\t|\n";
    std::cout << "|  Mean  |\t"<<_mean<<"\t|\t" << vg::mean( first, last ) << "\t|\n";
    std::cout << "|Variance|\t"<<_variance<<"\t|\t" << vg::variance( first, last ) << "\t|\n";
    std::cout << "|Skewness|\t"<<_skewness<<"\t|\t" << vg::skewness( first, last ) << "\t|\n";
    //std::cout << "|Kurtosis|\t"<<_kurtosis<<"\t|\t" << vg::kurtosis( first, last ) << "\t|\n";
}

#endif//_TEST_HPP_INCLUDED_SFDPOIHJASHSAFD

