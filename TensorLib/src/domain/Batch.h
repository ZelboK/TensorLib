//
// Created by Danial javady on 2023-03-11.
//

#ifndef TENSORLIB_BATCH_H
#define TENSORLIB_BATCH_H

#include "Module.h"

template <Number T, typename A, int rank>
class Batch : Module<T> {
    int in_features;
	std::vector<A> batch;
public:
    Batch(int in_features, bool affine);

	std::vector<Tensor<rank, T>> forward();

};
// i think Batch::rank >= Tensor::rank. Figure that out later.
template <Number T, int rank>
Batch<T, Tensor<rank, T>, rank> forward() {
	// is the organization of this correct? how does the compiler know to use this
	// impl
}

#endif //TENSORLIB_BATCH_H
