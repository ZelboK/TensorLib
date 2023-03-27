//
// Created by Danial javady on 2023-03-11.
//

#ifndef TENSORLIB_DEFAULTTYPES_H
#define TENSORLIB_DEFAULTTYPES_H

#include <type_traits>
#include <iostream>


template <typename T>
concept NumberType = std::is_arithmetic<T>::value;  // OK


template<typename T>
concept TensorIter =
requires
{
	typename T::value_type;
} && NumberType<typename T::value_type>;

template<typename Op, typename Arg1, typename Arg2>
concept binary_op = std::invocable<Op, Arg1, Arg2>;

#endif //TENSORLIB_DEFAULTTYPES_H
