//
// Created by Danial javady on 2023-03-11.
//

#ifndef TENSORLIB_DEFAULTTYPES_H
#define TENSORLIB_DEFAULTTYPES_H

#include <type_traits>
#include <iostream>


template <typename T>
concept Number = std::is_arithmetic<T>::value;  // OK

static float epsilon = 0.000005;

template<typename T>
concept Container_V =
requires
{
	typename T::value_type;
} && Number<typename T::value_type>;

template<typename Op, typename Arg1, typename Arg2>
concept binary_fn = std::invocable<Op, Arg1, Arg2>;

template <typename Op, typename Arg>
concept unary_fn = std::invocable<Op, Arg>;

#endif //TENSORLIB_DEFAULTTYPES_H
