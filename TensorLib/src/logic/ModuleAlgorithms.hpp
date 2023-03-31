//
// Created by 12893 on 2023-03-19.
//

#ifndef TENSORLIB_TENSORLIB_SRC_LOGIC_MODULEALGORITHMS_HPP_
#define TENSORLIB_TENSORLIB_SRC_LOGIC_MODULEALGORITHMS_HPP_
#include "TensorAlgorithms.h"
#include "../domain/Tensor.h"


namespace ModuleAlgorithms
{
	template<typename T, int rank, unary_fn<TensorImpl<rank, T>> Function>
	T reduceMapBatch(std::vector<TensorImpl<rank, T>> batch, Function fn);

	template<typename T, int rank, binary_fn<T, T> Function>
	T reduceFoldBatch(std::vector<TensorImpl<rank, T>> batch, T initial, Function fn);

	template<int rank, Number T>
	T computeMeanBatch(std::vector<TensorImpl<rank, T>> batch);

	template<int rank, Number T>
	T computeVarianceBatch(std::vector<TensorImpl<rank, T>> batch);

	// return Type?
	template<Number T>
	void normalize(T batchMean, T batchVariance);

	template<Number T>
	void scaleAndShift(auto batch, auto learnA, auto learnB); // two learnable parameters
}
// The behavior is non-deterministic if reduce is not associative or not commutative.
// The behavior is undefined if reduce, or transform modifies any element or invalidates any
// iterator in the input ranges, including their end iterators.
namespace ModuleAlgorithms
{

	template<Number T, int rank, unary_fn<T> Function>
	T reduceMapBatch(std::vector<TensorImpl<rank, T>> batch, Function fn)
	{
		T sum = 0;
		for (auto& tensor : batch)
		{
			sum += fn(tensor);
		}
		return sum / batch.size();
	}

	template<typename T, int rank, typename Function>
	T reduceFoldBatch(std::vector<TensorImpl<rank, T>> batch, T initial, Function fn)
	{
		for (auto& tensor : batch)
		{
			initial += fn(tensor);
		}
		return initial / batch.size();
	}

	template<int rank, Number T>
	T computeMeanBatch(std::vector<TensorImpl<rank, T>> batch)
	{
		return
			reduceMapBatch(batch, TensorAlgos::computeMean<T>);
	}

	template<int rank, Number T>
	T computeVarianceBatch(std::vector<TensorImpl<rank, T>> batch)
	{
		return
			reduceFoldBatch(batch, 0, TensorAlgos::computeVariance<T>);
	}
}

#endif //TENSORLIB_TENSORLIB_SRC_LOGIC_MODULEALGORITHMS_HPP_
