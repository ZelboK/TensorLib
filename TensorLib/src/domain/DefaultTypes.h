//
// Created by Danial javady on 2023-03-11.
//

#ifndef TENSORLIB_DEFAULTTYPES_H
#define TENSORLIB_DEFAULTTYPES_H

#include <type_traits>
#include <iostream>


template <typename T>
concept NumberType = std::is_arithmetic<T>::value;  // OK


#endif //TENSORLIB_DEFAULTTYPES_H
