//
// Created by 12893 on 2023-03-19.
//

#ifndef TENSORLIB_TENSORLIB_SRC_LOGIC_MODULEALGORITHMS_HPP_
#define TENSORLIB_TENSORLIB_SRC_LOGIC_MODULEALGORITHMS_HPP_
#include "TensorAlgorithms.h"
#include "../domain/Tensor.h"

namespace ModuleAlgorithms
{
	template<typename T, int rank, unary_fn<Tensor<rank, T>> Function>
	T reduceMapBatch(const std::vector<Tensor<rank, T>>& batch, Function fn);

	template<typename T, int rank, binary_fn<Tensor<rank, T>, T> Function>
	T reduceFoldBatch(const std::vector<Tensor<rank, T>>& batch, T initial, Function fn);

	template<int rank, Number T>
	T computeMeanBatch(const std::vector<Tensor<rank, T>>& batch);

	template<int rank, Number T>
	T computeVarianceBatch(const std::vector<Tensor<rank, T>>& batch);

// return Type?
	template<Number T, int rank>
	Tensor<rank, T> normalize(Tensor<rank, T> tensor,
		T batchMean,
		T batchVariance,
		T gamma,
		T beta);
}
// The behavior is non-deterministic if reduce is not associative or not commutative.
// The behavior is undefined if reduce, or transform modifies any element or invalidates any
// iterator in the input ranges, including their end iterators.
namespace ModuleAlgorithms
{

	template<typename T, int rank, unary_fn<Tensor<rank, T>> Function>
	T reduceMapBatch(const std::vector<Tensor<rank, T>>& batch, Function fn)
	{
		T sum = 0;
		for (auto& tensor : batch)
		{
			sum += fn(tensor);
		}
		return sum / batch.size();
	}

	template<typename T, int rank, binary_fn<Tensor<rank, T>, T> Function>
	T reduceFoldBatch(const std::vector<Tensor<rank, T>>& batch, T initial, Function fn)
	{
		for (auto& tensor : batch)
		{
			initial = fn(tensor, initial);
		}
		return initial / batch.size(); // why are we dividing here
	}

	template<int rank, Number T>
	T computeMeanBatch(const std::vector<Tensor<rank, T>>& batch)
	{
		return
			reduceMapBatch(batch, TensorAlgos::computeMean<T, Tensor<rank, T>>);
	}

	template<int rank, Number T>
	T computeVarianceBatch(const std::vector<Tensor<rank, T>>& batch)
	{

		return
			reduceFoldBatch(batch,
				0,
				TensorAlgos::computeVariance<T, Tensor<rank, T>>);
	}

	template<Number T, int rank>
	Tensor<rank, T> normalize(Tensor<rank, T> tensor,
		T batchMean,
		T batchVariance,
		T gamma,
		T beta)
	{
		tensor.map([&batchMean, &batchVariance, &gamma, &beta](T cur)
		{
		  T numerator = cur - batchMean;
		  T denom = sqrt(batchVariance + epsilon);
		  T normalized = numerator / denom;
		  return (gamma * normalized) + beta;
		});
		// how do we develop the concept of learnability for ?
		return tensor;
	}
}

#endif //TENSORLIB_TENSORLIB_SRC_LOGIC_MODULEALGORITHMS_HPP_
