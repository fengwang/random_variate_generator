/*
vg -- random variate generator library 
Copyright (C) 2010-2012  Feng Wang (feng.wang@uni-ulm.de) 

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

    template < class Return_Type = double, template<class, class> class Distribution = uniform, class Engine = mitchell_moore >
    struct variate_generator
    {
        typedef Distribution<Return_Type, Engine>       distribution_type;
        typedef typename distribution_type::seed_type   seed_type;
        typedef typename distribution_type::return_type return_type;
        typedef std::size_t                             size_type;
        typedef variate_generator                       self_type;

        distribution_type   dt_;

        //explicit variate_generator() noexcept : dt_( 0 ) {}

        template< typename ... Args >
        explicit variate_generator( Args ... args ) noexcept : dt_( args... ) {}

        return_type operator()() const noexcept
        {
            return dt_();
        }
#if 0
        operator return_type () const noexcept
        {
            return dt_();
        }
#endif
#if 0 
        struct              iterator; 
        iterator            iterator_;

    public:

        explicit variate_generator() noexcept : dt_( 0 )
        {
            iterator_ = iterator( &dt_ );
        }

        template< typename ... Tn >
        explicit variate_generator( const Tn ... tn ) noexcept : dt_(tn...)
        {
            iterator_ = iterator(&dt_);
        }

        ~variate_generator() {}

        return_type operator()() const noexcept
        {
            return dt_();
        }

        operator return_type () const noexcept
        {
            return dt_();
        }

        iterator begin() const noexcept
        {
            return iterator_;
        }

        variate_generator( const self_type& ) = delete;
        self_type& operator=( const self_type& ) = delete;
        variate_generator( self_type&& ) = delete;
        self_type& operator=( self_type&& ) = delete;
#endif
    };

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

}//namespace vg

//#include <vg/variate_generator/variate_generator.tcc>

#endif//_VARIATE_GENERATOR_HPP_INCLUDED_IUH398UHFKJH29U8HSFIOUHE98UHDUHE98UH23UJ

