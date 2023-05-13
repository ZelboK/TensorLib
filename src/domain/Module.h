//
// Created by Danial javady on 2023-03-11.
//

#ifndef TENSORLIB_MODULE_H
#define TENSORLIB_MODULE_H

#include "DefaultTypes.h"
#include "Tensor.h"

template<Number T>
class Module
{
 public:
	template<int rank>
	// are we sure this is what we want? Maybe this just takes
	// a Tensor base class
	Tensor<rank, T> forward(Tensor<rank, T> layer,
		Tensor<rank, T> data)
	{
		return layer * data;
	}
};

#endif //TENSORLIB_MODULE_H
