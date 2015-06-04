#ifndef RGODGIABHAUJSROAIUONLWGKCBNMYJRDWATDIGDNRDEPJQUVDCESQINNINICYTWSHRFDHXFLQ
#define RGODGIABHAUJSROAIUONLWGKCBNMYJRDWATDIGDNRDEPJQUVDCESQINNINICYTWSHRFDHXFLQ

#include <vg/engine/default_seed.hpp>

#include <cstddef>
#include <cstdint>
#include <limits>
#include <mutex>

namespace vg
{

    //64, 44497, 21034
    struct lagged_fibonacci
    {
            typedef lagged_fibonacci        self_type;
            typedef long double             final_type;
            typedef std::uint_fast64_t      value_type;
            typedef value_type              seed_type;
            typedef std::size_t             size_type;

        private:
            value_type                      data[44497];
            size_type                       mti;
            mutable std::mutex              mtx;

        public:
            lagged_fibonacci( const seed_type s = 0 ) noexcept
            {
                std::lock_guard<std::mutex> l( mtx );

                init( s );
            }

            void reset_seed( const seed_type s = 0 ) noexcept
            {
                if ( 0 == s ) return;

                std::lock_guard<std::mutex> l( mtx );
                init( s );
            }

        private:
            void refill() noexcept
            {
                std::copy( data+21034, data+44497, data );
                
                for ( size_type index = 23463; index != 44497; ++index )
                    data[index] = data[index-2] + data[index-1];

                mti = 0;
            }


            void init( const seed_type s ) noexcept
            {
                mti = s ? s : default_seed{}();
                mti %= 21034;

                data[0] = 1;
                data[1] = 1;

                for ( size_type index = 2; index != 44497; ++index )
                    data[index] = data[index-2] + data[index-1];
            }

        public:
            final_type operator()() noexcept
            {
                std::lock_guard<std::mutex> l( mtx );

                if ( mti > 21034 ) refill();

                size_type const mtj = mti + 23463;

                value_type x = data[mti] + data[mtj];
                ++mti;

                const final_type ans =  static_cast<final_type>( static_cast<final_type>( x ) )  / static_cast<final_type>( std::numeric_limits<value_type>::max() );
                return ans;
            }

        private://not to be implemented
            lagged_fibonacci( const self_type& );
            lagged_fibonacci& operator = ( const self_type& );
    };

}//namespace vg

#endif//RGODGIABHAUJSROAIUONLWGKCBNMYJRDWATDIGDNRDEPJQUVDCESQINNINICYTWSHRFDHXFLQ

