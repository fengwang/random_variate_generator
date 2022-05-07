/*
vg -- random variate generator library
Copyright (C) 2010-2022  Feng Wang wang_feng@live.com

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef _VARIATE_GENERATOR_HPP_INCLUDED_IUH398UHFKJH29U8HSFIOUHE98UHDUHE98UH23UJ
#define _VARIATE_GENERATOR_HPP_INCLUDED_IUH398UHFKJH29U8HSFIOUHE98UHDUHE98UH23UJ

#include <vg/distribution.hpp>
#include <vg/engine.hpp>

#include <cstddef>
#include <iterator>

namespace vg
{

    ///
    /// @brief Create a random variate generator.
    ///
    /// @tparam Return_Type Data type the random variate that will be generated.
    /// @tparam Distribution The distribution that our random variate generate will generate. List of the distributions goes to vg/distribution.hpp.
    /// @tparam Engine Uniform random variate generator method. Can be one of lagged_fibonacci, linear_congruential, mitchell_moore or mt19937
    ///
    /// Example usage:
    /// \code{.cpp}
    /// vg::variate_generator vg<float, exponentional>{ 1.0 };
    /// for ( int i = 0; i < 100; ++i )
    /// {
    ///     float const x = vg();
    ///     std::cout << x << "\n";
    /// }
    /// \endcode
    ///
    template < class Return_Type = double, template<class, class> class Distribution = uniform, class Engine = mitchell_moore >
    struct variate_generator
    {
        typedef Distribution<Return_Type, Engine>       distribution_type;
        typedef typename distribution_type::seed_type   seed_type;
        typedef typename distribution_type::return_type return_type;
        typedef std::size_t                             size_type;
        typedef variate_generator                       self_type;

        distribution_type   dt_;

        template< typename ... Args >
        explicit variate_generator( Args&& ... args ) noexcept : dt_{ std::forward<Args>(args)... } {}

        return_type operator()() const noexcept
        {
            return dt_();
        }
    }; // struct variate_generator

#if 0
    template < class Return_Type, template<class, class> class Distribution, class Engine, typename... Args >
    variate_generator<Return_Type, Distribution, Engine>
    make_variate_generator( Args ... args ) noexcept
    {
        return variate_generator<Return_Type, Distribution, Engine>{ args... };
    }

    template < class Return_Type, template<class, class> class Distribution,  typename... Args >
    variate_generator<Return_Type, Distribution, mitchell_moore>
    make_variate_generator( Args ... args ) noexcept
    {
        return variate_generator<Return_Type, Distribution, mitchell_moore>{ args... };
    }

    template < class Return_Type, typename... Args >
    variate_generator<Return_Type, uniform, mitchell_moore>
    make_variate_generator( Args ... args ) noexcept
    {
        return variate_generator<Return_Type, uniform, mitchell_moore>{ args... };
    }

    template < typename... Args >
    variate_generator<double, uniform, mitchell_moore>
    make_variate_generator( Args ... args ) noexcept
    {
        return variate_generator<double, uniform, mitchell_moore>{ args... };
    }
#endif

}//namespace vg

#endif//_VARIATE_GENERATOR_HPP_INCLUDED_IUH398UHFKJH29U8HSFIOUHE98UHDUHE98UH23UJ

