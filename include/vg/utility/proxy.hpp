#ifndef _PROXY_HPP_INCLUDED_SDOIFJ438OUAFSLSF988923PFUISLFKJEOIJFLKJDOIJFALIJEIJ
#define _PROXY_HPP_INCLUDED_SDOIFJ438OUAFSLSF988923PFUISLFKJEOIJFLKJDOIJFALIJEIJ

#include <cstddef>

namespace vg 
{

//template<typename T>
//struct proxy : T
//{};

template< typename T, std::size_t Level = 0 >
struct proxy;

template< typename T, std::size_t Level >
struct proxy : proxy< T, Level - 1 >
{};

template< typename T >
struct proxy<T, 0> : T
{};


}//namespace vg

#endif//_PROXY_HPP_INCLUDED_SDOIFJ438OUAFSLSF988923PFUISLFKJEOIJFLKJDOIJFALIJEIJ

