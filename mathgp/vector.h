//                MathGP Library
//     Copyright (c) 2012 Borislav Stanimirov
//   
//  See the LICENSE.txt file, included in this 
//  distribution for details about the copyright
#pragma once

#include "ntuple.h"

namespace yamgp
{
namespace _internal
{

template <size_t _n, typename _type, typename _this_type>
class vectornt : public ntuple<_n, _type, _this_type>
{
public:
    static const size_type dimension = value_count;
};

#if defined(_OSTREAM_)
template <size_t _n, typename _type, typename _this_type>
::std::ostream& operator<<(::std::ostream& o, const vectornt<_n, _type, _this_type>& vec)
{
    typedef yamgp::_internal::vectornt<_n, _type, _this_type> vector;

    o << '(';
    for(typename vector::size_type i=0; i<vector::dimension; ++i)
    {
        if(i)
        {
            o << ", ";
        }

        o << vec.at(i);
    }
    o << ')';

    return o;
}
#endif


template <typename _type>
class wrap_ref
{
public:
    operator _type&()
    {
        return *ref;
    }

    operator const _type&() const
    {
        return *ref;
    }

    _type* ref;
};


template <size_t _n, typename _type, typename _this_type>
class swizzle_vectornt : public vectornt<_n, wrap_ref<_type>, _this_type>
{
public:
    
    operator _this_type() const
    {
        _this_type ret;

        YAMGP_EACH_OF(ret) = at(i);

        return ret;
    }

    // intentionally void
    // it breaks a=b=c, but gets rid of unwanted temporary objects
    void operator=(const vectornt<dimension, _type, _this_type>& b)
    {
        for(size_type i=0; i<value_count; ++i) 
            *at(i).ref = b.at(i);    
    }

private:
    ////////////////////////////////////////////////////////
    // unsafe operators to be hidden
};

template <typename _this_type, typename _type>
swizzle_vectornt<2, _type, _this_type> swizzle2(const _type& x, const _type& y)
{
    swizzle_vectornt<2, _type, _this_type> ret;

    ret.at(0).ref = &x;
    ret.at(1).ref = &y;

    return ret;
}

template <typename _this_type, typename _type>
swizzle_vectornt<3, _type, _this_type> swizzle3(const _type& x, const _type& y, const _type& z)
{
    swizzle_vectornt<3, _type, _this_type> ret;

    ret.at(0).ref = &x;
    ret.at(1).ref = &y;
    ret.at(2).ref = &z;

    return ret;
}

template <typename _this_type, typename _type>
swizzle_vectornt<4, _type, _this_type> swizzle3(const _type& x, const _type& y, const _type& z, const _type& w)
{
    swizzle_vectornt<4, _type, _this_type> ret;

    ret.at(0).ref = &x;
    ret.at(1).ref = &y;
    ret.at(2).ref = &z;
    ret.at(3).ref = &w;

    return ret;
}

}

template <typename _type>
class vector1t;

template <typename _type>
class vector2t;

template <typename _type>
class vector3t;

template <typename _type>
class vector4t;

template <typename _type>
class vectornt;

template <typename _type>
class vector1t : public _internal::vectornt<1, _type, vector1t<_type>>
{
public:
    ////////////////////////////////////////////////////////
    // named constructors

    static vector1t coord(value_type x)
    {
        vector1t ret;

        ret.x() = x;

        return ret;
    }

#include "vector1_swizzle_declare.inl"

};

template <typename _type>
class vector2t : public _internal::vectornt<2, _type, vector2t<_type>>
{
public:
    ////////////////////////////////////////////////////////
    // named constructors

    static vector2t coord(value_type x, value_type y)
    {
        vector2t ret;

        ret.x() = x;
        ret.y() = y;

        return ret;
    }

#include "vector1_swizzle_declare.inl"
#include "vector2_swizzle_declare.inl"

};

template <typename _type>
class vector3t : public _internal::vectornt<3, _type, vector3t<_type>>
{
public:
    ////////////////////////////////////////////////////////
    // named constructors

    static vector3t coord(value_type x, value_type y, value_type z)
    {
        vector3t ret;

        ret.x() = x;
        ret.y() = y;
        ret.z() = z;

        return ret;
    }

#include "vector1_swizzle_declare.inl"
#include "vector2_swizzle_declare.inl"
#include "vector3_swizzle_declare.inl"

};

#define YAMGP_SWIZZLE_VEC vector1t
#include "vector1_swizzle_define.inl"
#undef YAMGP_SWIZZLE_VEC

#define YAMGP_SWIZZLE_VEC vector2t
#include "vector1_swizzle_define.inl"
#include "vector2_swizzle_define.inl"
#undef YAMGP_SWIZZLE_VEC

#define YAMGP_SWIZZLE_VEC vector3t
#include "vector1_swizzle_define.inl"
#include "vector2_swizzle_define.inl"
#include "vector3_swizzle_define.inl"
#undef YAMGP_SWIZZLE_VEC

//#define YAMGP_SWIZZLE_VEC vector1t
//#include "vector1_swizzle_define.inl"

}