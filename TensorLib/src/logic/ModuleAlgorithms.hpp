//
// Created by 12893 on 2023-03-19.
//

#ifndef TENSORLIB_TENSORLIB_SRC_LOGIC_MODULEALGORITHMS_HPP_
#define TENSORLIB_TENSORLIB_SRC_LOGIC_MODULEALGORITHMS_HPP_
#include "TensorAlgorithms.hpp"
#include "../domain/Tensor.h"
#include "../domain/DefaultTypes.h"
namespace ModuleAlgorithms
{
	template<Number T, class Tensor, class Function>
	requires (std::same_as<T, typename Tensor::value_type> &&
		std::invocable<Function, T> &&
		requires { typename Tensor::rank; })
	T reduceMapBatch(const std::vector<Tensor>& batch, Function fn);

	template<Number T, class Tensor, class Function>
	requires (std::same_as<T, typename Tensor::value_type> &&
		std::invocable<Function, T, const Tensor&> &&
		requires { typename Tensor::rank; })
	T reduceFoldBatch(const std::vector<Tensor>& batch, Function fn);

	template<Number T, int rank, class Tensor>
	T computeMeanBatch(const std::vector<Tensor>& batch);

	template<Number T, int rank, class Tensor>
	T computeVarianceBatch(const std::vector<Tensor>& batch);

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
	template<Number T, class Tensor, class Function>
	T reduceMapBatch(const std::vector<Tensor>& batch, Function fn)
	{
		return
			std::transform_reduce(batch.begin(), batch.end(), 0, std::plus<T>(), fn);

	}

	template<Number T, class Tensor, class Function>
	T reduceFoldBatch(const std::vector<Tensor>& batch, Function fn)
	{
		return std::accumulate(batch.begin(), batch.end(), T(0),
			[&](T acc, const Tensor& cur)
			{
			  return fn(acc, cur);
			});
	}

	template<Number T, int rank, class Tensor>
	T computeMeanBatch(const std::vector<Tensor>& batch)
	{
		return
			reduceMapBatch<T, Tensor>(batch,
				[](const Tensor& cur)
				{
				  return TensorAlgos::computeMean<T>(cur);
				}
			) / batch.size();
	}

	template<Number T, int rank, class Tensor>
	T computeVarianceBatch(const std::vector<Tensor>& batch)
	{

		return
			reduceFoldBatch<T, Tensor>(batch,
				[](T acc, const Tensor cur)
				{
				  return TensorAlgos::computeVariance<T>(cur, acc);
				}
			) / batch.size();
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
	template<Number T, int rank, class Tensor>
	requires (std::same_as<T, typename Tensor::value_type> &&
		Tensor::rank == rank && // idk if we want this constraint.
		Tensor::iterator) // This constraint may not be good
	// what if T is anint, and value_type is a float?
	Tensor batchNorm(Tensor tensor,
		const T batchMean,
		const T batchVariance,
		const T gamma,
		const T beta)
	{
		std::transform(tensor.begin(), tensor.end(), [&batchMean, &batchVariance, &gamma, &beta](T cur)
		{
		  T numerator = cur - batchMean;
		  T denom = sqrt(batchVariance + epsilon);
		  T normalized = numerator / denom;
		  return (gamma * normalized) + beta;
		});

	}
}

#endif //TENSORLIB_TENSORLIB_SRC_LOGIC_MODULEALGORITHMS_HPP_
