//
// Created by Danial javady on 2023-03-11.
//

#ifndef TENSORLIB_LINEAR_H
#define TENSORLIB_LINEAR_H

#include "DefaultTypes.h"
#include "Module.h"

template<Number T>
class Linear : public Module<T> {
    int in_channels;
    int out_channels;
    T bias; // TODO implement
public:
    Tensor<1, T> layer; // The rank here doesn't make sense!?
    Linear(int in, int out) : in_channels(in),
                              out_channels(out) {
        layer = Tensor<1, T>(in);
    }

};

#endif //TENSORLIB_LINEAR_H
