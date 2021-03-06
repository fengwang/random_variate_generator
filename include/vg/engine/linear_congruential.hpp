#ifndef _LINEAR_CONGRUENTIAL_HPP_INCLUDED_3UHSFKJHNSAIFUNVCJMNZKJHDEIUHE3IUHSIKUJHEE8
#define _LINEAR_CONGRUENTIAL_HPP_INCLUDED_3UHSFKJHNSAIFUNVCJMNZKJHDEIUHE3IUHSIKUJHEE8

#include <vg/engine/default_seed.hpp>

#include <cstddef>
#include <cstdint>
#include <mutex>
#include <limits>

namespace vg
{
    struct linear_congruential
    {
            typedef linear_congruential     self_type;
            typedef long double             final_type;
            typedef std::uint_fast64_t      value_type;
            typedef value_type              seed_type;
            typedef std::size_t             size_type;

        private:
            static const value_type         a_ = 6364136223846793005ULL;
            static const value_type         c_ = 1442695040888963407ULL;
            value_type                      x_;
            mutable std::mutex              mtx;

        public:
            linear_congruential( const seed_type s = 0 ) noexcept
            {
                std::lock_guard<std::mutex> l( mtx );

                x_ = s ? s : default_seed()();
            }

            void reset_seed( const seed_type s = 0 ) noexcept
            {
                if ( s )
                {
                    std::lock_guard<std::mutex> l( mtx );
                    x_ = s;
                }
            }

            final_type operator()() noexcept
            {
                std::lock_guard<std::mutex> l( mtx );

                x_ *= a_;
                x_ += c_;
                const final_type ans = static_cast<final_type>( x_ ) / static_cast<final_type>( std::numeric_limits<value_type>::max() );
                return ans;
            } // end of operator()

        private://not to be implemented
            linear_congruential( const self_type& );
            linear_congruential& operator = ( const self_type& );
    };// end of struct linear_congruential
}//namespace vg

#endif//_LINEAR_CONGRUENTIAL_HPP_INCLUDED_3UHSFKJHNSAIFUNVCJMNZKJHDEIUHE3IUHSIKUJHEE8

