#ifndef _VARIATE_GENERATOR_HPP_INCLUDED_IUH398UHFKJH29U8HSFIOUHE98UHDUHE98UH23UJ
#define _VARIATE_GENERATOR_HPP_INCLUDED_IUH398UHFKJH29U8HSFIOUHE98UHDUHE98UH23UJ

#include "distribution.hpp"
#include "engine.hpp"

#include <cstddef>
#include <iterator>

namespace feng
{

    template <
			  class Return_Type = long double,
			  template<class, class>
			  class Distribution = uniform,
			  class Engine = mitchell_moore
			 >
    struct variate_generator
    {
        typedef Distribution<Return_Type, Engine>       distribution_type;
        typedef typename distribution_type::seed_type   seed_type;
        typedef typename distribution_type::return_type return_type;
        typedef std::size_t                             size_type;
        typedef variate_generator                       self_type;

    private:
        distribution_type dt_;

        struct iterator; //implemented in file "variate_generator/variate_generator.tcc"
        iterator iterator_;

    public:

        explicit variate_generator() : dt_( 0 )
        {
            iterator_ = iterator( &dt_ );
        }

        template<typename T>
        explicit variate_generator( const T t ) : dt_( t )
        {
            iterator_ = iterator( &dt_ );
        }

        template<typename T1, typename T2>
        variate_generator( const T1 t1, const T2 t2 ) : dt_( t1, t2 )
        {
            iterator_ = iterator( &dt_ );
        }

        template<typename T1, typename T2, typename T3>
        variate_generator( const T1 t1, const T2 t2, const T3 t3 ) : dt_( t1, t2, t3 )
        {
            iterator_ = iterator( &dt_ );
        }

        ~variate_generator() {}

    public:
        return_type
        operator()()
        {
            return dt_();
        }

        operator return_type ()
        {
            return_type ans = operator();
            return ans;
        }

        iterator
        begin()
        {
            return iterator_;
        }

    private://not to be implemented
        variate_generator( const self_type& );
        self_type& operator=( const self_type& );
    };


}//namespace feng

#include "variate_generator/variate_generator.tcc"


#endif//_VARIATE_GENERATOR_HPP_INCLUDED_IUH398UHFKJH29U8HSFIOUHE98UHDUHE98UH23UJ


