#ifndef _DEFAULT_SEED_HPP_INCLUDED_SDFOIUJ4OIUASF8U3OIAUF983ILAUFSO8U34LIUFSDLIJ
#define _DEFAULT_SEED_HPP_INCLUDED_SDFOIUJ4OIUASF8U3OIAUF983ILAUFSO8U34LIUFSDLIJ

/*
#include <cstddef>
#include <cstdint>
#include <ctime>
*/

namespace vg
{

    struct default_seed
    {
        typedef std::uint_fast64_t              seed_type;

        seed_type operator()() const noexcept
        {
            const seed_type  s = time(0);
            int * i = new int;
            seed_type  ans = s + ( reinterpret_cast<seed_type>(i) | (reinterpret_cast<seed_type>(i) << 32) );
            ans = ( ans & 0x5555555555555555ULL ) <<  1 | ( ans & 0xAAAAAAAAAAAAAAAAULL ) >>  1;
            ans = ( ans & 0x3333333333333333ULL ) <<  2 | ( ans & 0xCCCCCCCCCCCCCCCCULL ) >>  2;
            ans = ( ans & 0x0F0F0F0F0F0F0F0FULL ) <<  4 | ( ans & 0xF0F0F0F0F0F0F0F0ULL ) >>  4;
            ans = ( ans & 0x00FF00FF00FF00FFULL ) <<  8 | ( ans & 0xFF00FF00FF00FF00ULL ) >>  8;
            ans = ( ans & 0x0000FFFF0000FFFFULL ) << 16 | ( ans & 0xFFFF0000FFFF0000ULL ) >> 16;
            ans = ( ans & 0x00000000FFFFFFFFULL ) << 32 | ( ans & 0xFFFFFFFF00000000ULL ) >> 32;
            ans |= s;
            delete i;
            return ans;
        }// end of operator ()

    }; // end of struct default_seed

}// end of namespace vg

#endif//_DEFAULT_SEED_HPP_INCLUDED_SDFOIUJ4OIUASF8U3OIAUF983ILAUFSO8U34LIUFSDLIJ

