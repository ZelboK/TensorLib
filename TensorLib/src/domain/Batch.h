//
// Created by Danial javady on 2023-03-11.
//

#ifndef TENSORLIB_BATCH_H
#define TENSORLIB_BATCH_H

#include "Module.h"

template <typename T>
class Batch : Module<T> {
    int in_features;
public:
    Batch(int in_features, bool affine);
};

#endif //TENSORLIB_BATCH_H
