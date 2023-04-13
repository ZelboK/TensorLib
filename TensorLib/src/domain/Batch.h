//
// Created by Danial javady on 2023-03-11.
//

#ifndef TENSORLIB_BATCH_H
#define TENSORLIB_BATCH_H

#include "Module.h"
#include "../logic/ModuleAlgorithms.hpp"

template<Number T, class Tensor, int rank>
class Batch : Module<T>
{
	int in_features;
	std::vector<Tensor> batch_;
 public:
	explicit Batch(std::vector<Tensor> batch) : batch_(batch) {

	}
	std::vector<Tensor> forward()
	{
		T mean = ModuleAlgorithms::computeMeanBatch<T, rank, Tensor>(batch_);
		//T variance = ModuleAlgorithms::computeVarianceBatch<T, rank>(batch_);

//		std::for_each(batch_.begin(),
//			batch_.end(),
//			[&mean, &variance](Tensor cur)
//			{
//			  ModuleAlgorithms::normalize(cur, mean, variance, 1.0, 0.0);
//			});
		return batch_;
	}

};

// i think Batch::rank >= Tensor::rank. Figure that out later.
//template<Number T, int rank>
//Batch<T, Tensor<rank, T>, rank> forward()
//{
//	// is the organization of this correct? how does the compiler know to use this
//	// impl
//}

#endif //TENSORLIB_BATCH_H
