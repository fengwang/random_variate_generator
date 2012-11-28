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
    struct vg
    {
        typedef Distribution<Return_Type, Engine>       distribution_type;
        typedef typename distribution_type::seed_type   seed_type;
        typedef typename distribution_type::return_type return_type;
        typedef std::size_t                             size_type;
        typedef vg                                      self_type;

    private:
        distribution_type   dt_;
        struct              iterator; 
        iterator            iterator_;

    public:

        explicit vg() : dt_( 0 )
        {
            iterator_ = iterator( &dt_ );
        }

        template<typename T>
        explicit vg( const T t ) : dt_( t )
        {
            iterator_ = iterator( &dt_ );
        }

        template<typename T1, typename T2>
        vg( const T1 t1, const T2 t2 ) : dt_( t1, t2 )
        {
            iterator_ = iterator( &dt_ );
        }

        template<typename T1, typename T2, typename T3>
        vg( const T1 t1, const T2 t2, const T3 t3 ) : dt_( t1, t2, t3 )
        {
            iterator_ = iterator( &dt_ );
        }

        template<typename T1, typename T2, typename T3, typename T4>
        vg( const T1 t1, const T2 t2, const T3 t3, const T4 t4 ) : dt_( t1, t2, t3, t4 )
        {
            iterator_ = iterator( &dt_ );
        }

        template<typename T1, typename T2, typename T3, typename T4, typename T5>
        vg( const T1 t1, const T2 t2, const T3 t3, const T4 t4, const T5 t5 ) : dt_( t1, t2, t3, t4, t5 )
        {
            iterator_ = iterator( &dt_ );
        }

        ~vg() {}

    public:
        return_type
        operator()() const
        {
            return dt_();
        }

        operator return_type () const
        {
            return dt_();
        }

        iterator
        begin() const
        {
            return iterator_;
        }

    public:
        vg( const self_type& ) = default;
        self_type& operator=( const self_type& ) = default;
        vg( self_type&& ) = default;
        self_type& operator=( self_type&& ) = default;
    };

}//namespace vg

#include <vg/variate_generator/variate_generator.tcc>

#endif//_VARIATE_GENERATOR_HPP_INCLUDED_IUH398UHFKJH29U8HSFIOUHE98UHDUHE98UH23UJ

