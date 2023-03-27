//
// Created by Danial javady on 2023-03-11.
//

#ifndef TENSORLIB_MODULE_H
#define TENSORLIB_MODULE_H

#include "DefaultTypes.h"
#include "Tensor.h"

template<NumberType T>
class Module
{
 public:
	template<int rank>
	// are we sure this is what we want? Maybe this just takes
	// a Tensor base class
	TensorImpl<rank, T> forward(TensorImpl<rank, T> layer,
		TensorImpl<rank, T> data)
	{
		return layer * data;
	}
};

#endif //TENSORLIB_MODULE_H
