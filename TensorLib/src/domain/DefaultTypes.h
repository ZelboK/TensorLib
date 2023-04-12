//
// Created by Danial javady on 2023-03-11.
//

#ifndef TENSORLIB_DEFAULTTYPES_H
#define TENSORLIB_DEFAULTTYPES_H

#include <type_traits>
#include <iostream>


template <typename T>
concept Number = std::is_arithmetic<T>::value;  // This concept can be further refined
// to be more strict with types

static float epsilon = 0.000005;

template<typename Op, typename Arg1, typename Arg2>
concept binary_fn = std::invocable<Op, Arg1, Arg2>;

template <typename Op, typename Arg>
concept unary_fn = std::invocable<Op, Arg>;

#endif //TENSORLIB_DEFAULTTYPES_H
