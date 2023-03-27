//
// Created by 12893 on 2023-03-19.
//

#ifndef TENSORLIB_TENSORLIB_SRC_LOGIC_MODULEALGORITHMS_HPP_
#define TENSORLIB_TENSORLIB_SRC_LOGIC_MODULEALGORITHMS_HPP_
#include "TensorAlgorithms.h"
#include "../domain/Tensor.h"
#include "opmapi.h"

namespace ModuleAlgos {

	template <int rank, NumberType T>
	T computeMeanBatch(std::vector<TensorImpl<rank, T>> batch);
}
// The behavior is non-deterministic if reduce is not associative or not commutative.
// The behavior is undefined if reduce, or transform modifies any element or invalidates any
// iterator in the input ranges, including their end iterators.
namespace ModuleAlgorithms {

	template <int rank, NumberType T>
	T computeMeanBatch(std::vector<TensorImpl<rank, T>> batch) {

	}

}

#endif //TENSORLIB_TENSORLIB_SRC_LOGIC_MODULEALGORITHMS_HPP_
