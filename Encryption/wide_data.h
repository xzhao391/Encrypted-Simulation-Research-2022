// Created by Shane on 4/9/2022.

#ifndef DYERS_NATIVE_WIDE_DATA_H
#define DYERS_NATIVE_WIDE_DATA_H

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>
//using wide_int_t = boost::multiprecision::checked_int1024_t;

#define INT_WIDTH 8192
using wide_int_t = boost::multiprecision::number<
        boost::multiprecision::cpp_int_backend<INT_WIDTH, INT_WIDTH,
        boost::multiprecision::signed_magnitude,
        boost::multiprecision::unchecked,void> >;

using wide_uint_t = boost::multiprecision::number<
        boost::multiprecision::cpp_int_backend<INT_WIDTH, INT_WIDTH,
        boost::multiprecision::unsigned_magnitude,
        boost::multiprecision::unchecked,void> >;

using wide_double_t = boost::multiprecision::cpp_bin_float_quad;

// Type aliases
using cipher_text = wide_int_t;
//using plain_text = wide_int_t;

#endif //DYERS_NATIVE_WIDE_DATA_H
