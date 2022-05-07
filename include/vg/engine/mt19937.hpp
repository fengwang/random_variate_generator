#ifndef _MT19937_HPP_INCLUDED28903RUAFSLDKJASFDOIJ4890UAFOPSI1209AFLKJ34OIUFJKDS
#define _MT19937_HPP_INCLUDED28903RUAFSLDKJASFDOIJ4890UAFOPSI1209AFLKJ34OIUFJKDS

#include "./default_seed.hpp"

/*
#include <cstddef>
#include <cstdint>
#include <limits>
#include <mutex>
*/

namespace vg
{

    struct mt19937
    {
            typedef mt19937                 self_type;
            typedef long double             final_type;
            typedef std::uint_fast64_t      value_type;
            typedef value_type              seed_type;
            typedef std::size_t             size_type;

        private:
            value_type                      mt[312];
            value_type                      mag01[2];
            size_type                       mti;

        public:
            mt19937( const seed_type s = 0 ) noexcept
            {
                init( s );
            }

            void reset_seed( const seed_type s = 0 ) noexcept
            {
                if ( 0 == s ) return;
                init( s );
            }

        private:
            void init( const seed_type s ) noexcept
            {
                mt[0] = s ? s : default_seed()();
                mag01[0] = 0ULL;
                mag01[1] = 0xB5026F5AA96619E9ULL;

                for ( mti = 1; mti < 312; ++mti )
                {
                    mt[mti] =  6364136223846793005ULL * ( mt[mti-1] ^( mt[mti-1] >> 62 ) );
                    mt[mti] += mti;
                }
            }

        public:
            final_type operator()() noexcept
            {
                value_type x;

                if ( mti > 311 )
                {
                    for ( size_type i = 0; i < 156; ++i )
                    {
                        x = ( mt[i] & 0xFFFFFFFF80000000ULL ) | ( mt[i+1] & 0x7FFFFFFFULL );
                        mt[i] = mt[i+156] ^( x >> 1 ) ^ mag01[x&1];
                    }

                    for ( size_type i = 156; i < 311; ++i )
                    {
                        x = ( mt[i] & 0xFFFFFFFF80000000ULL ) | ( mt[i+1] & 0x7FFFFFFFULL );
                        mt[i] = mt[i-156] ^( x >> 1 ) ^ mag01[x&1];
                    }

                    x = ( mt[311] & 0xFFFFFFFF80000000ULL ) | ( mt[0] & 0x7FFFFFFFULL );
                    mt[311] = mt[155] ^( x >> 1 ) ^ mag01[x&1];
                    mti = 0;
                }

                x = mt[mti++];
                x ^= ( x >> 29 ) & 0x5555555555555555ULL;
                x ^= ( x << 17 ) & 0x71D67FFFEDA60000ULL;
                x ^= ( x << 37 ) & 0xFFF7EEE000000000ULL;
                x ^= ( x >> 43 );
                const final_type ans =  static_cast<final_type>( static_cast<final_type>( x ) )  /
                                        static_cast<final_type>( std::numeric_limits<value_type>::max() );
                return ans;
            }

        private://not to be implemented
            mt19937( const self_type& );
            mt19937& operator = ( const self_type& );
    };

}//namespace vg

#endif//_MT19937_HPP_INCLUDED28903RUAFSLDKJASFDOIJ4890UAFOPSI1209AFLKJ34OIUFJKDS

