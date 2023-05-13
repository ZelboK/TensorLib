//
// Created by 12893 on 2023-03-19.
//

#ifndef TENSORLIB_TENSORLIB_SRC_LOGIC_MODULEALGORITHMS_HPP_
#define TENSORLIB_TENSORLIB_SRC_LOGIC_MODULEALGORITHMS_HPP_
#include <execution>
#include "TensorAlgorithms.hpp"
#include "Tensor.h"
#include "DefaultTypes.h"
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

	template<Number T, int rank, typename Tensor>
	requires (std::same_as<T, typename Tensor::value_type> && Tensor::rank == rank)
	Tensor batchNorm(const Tensor& tensor, T batchMean, T batchVariance, T gamma, T beta);

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
			std::transform_reduce(batch.begin(), batch.end(), T(0), std::plus<T>(), fn);

	}
	// what did i make this for again...?
	template<Number T, class Tensor, class Function>
	T reduceFoldBatch(const std::vector<Tensor>& batch, Function fn)
	{
		return std::accumulate(batch.begin(), batch.end(), T(0),
			[&fn](T acc, const Tensor& cur)
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
		T batchMean = computeMeanBatch<T, rank, Tensor>(batch);
		std::vector<T> means(batch.size());

		std::transform(batch.begin(),
			batch.end(),
			means.begin(),
			[](Tensor cur)
			{
			  T mean = TensorAlgos::computeMean<T, Tensor>(cur);
			  return mean;
			});

		return std::accumulate(
			means.begin(), means.end(), T(0),
			[&batchMean](T acc, T curMean)
			{
			  T diff = batchMean - curMean;
			  return acc + (diff * diff);
			}
		) / batch.size();

	}

	template<Number T, int rank, typename Tensor>
	requires (std::same_as<T, typename Tensor::value_type> && Tensor::rank == rank)
	Tensor batchNorm(const Tensor& tensor, T batchMean, T batchVariance, T gamma, T beta)
	{
		T epsilon = std::numeric_limits<T>::epsilon() * 1e2;
		Tensor result = tensor;

		std::transform(tensor.begin(), tensor.end(), result.begin(), [&](T cur)
		{
		  T numerator = cur - batchMean;
		  T denom = std::sqrt(batchVariance + epsilon);

		  T normalized = numerator / denom;

		  return (gamma * normalized) + beta;
		});

		return result;
	}
}

#endif //TENSORLIB_TENSORLIB_SRC_LOGIC_MODULEALGORITHMS_HPP_
