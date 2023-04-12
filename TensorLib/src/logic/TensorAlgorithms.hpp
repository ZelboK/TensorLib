#ifndef TENSORLIB_TENSORALGORITHMS_H
#define TENSORLIB_TENSORALGORITHMS_H

#include "../domain/Tensor.h"
#include "../domain/DefaultTypes.h"
#include <functional>
#include "FunctionalProgrammingAlgos.hpp"
namespace TensorAlgos
{
	template<int N>
	void printImageTensor(const Tensor<N, unsigned char>& tensor);

	template<Number T, class TensorIt, class Functor>
	T accumulate(const TensorIt& begin, const TensorIt& end, T initial, Functor fn);

	template<Number T, class Tensor, typename Functor>
	T accumulate(const Tensor& tensor, T initial, Functor fn);

	template<Number T, class Tensor>
	T computeMean(const Tensor& tensor);

// lacks referential transparency. If more than one thread is using this on the same
// tensor, then the tensor data will be added accordingly.
	template<typename Tensor>
	Tensor modifyTensorWithRandomInts(Tensor& tensor);

	template<Number T, class Tensor>
	T computeVariance(const Tensor& tensor, T mean);

	template<Number T, class Tensor>
	T computeStandardDeviation(const Tensor& tensor, T mean);

	template<Number T, class Tensor>
	Tensor randTensor(int channels, int rows, int cols); // TODO this clearly does not take into account SHAPE.
}

namespace TensorAlgos
{
	template<int N>
	void printImageTensor(const Tensor<N, unsigned char>& tensor)
	{
		for (auto& elem : tensor)
		{
			std::cout << (int)elem << ","; // horrible printing lol
		}
	}

	template<Number T, class TensorIt, class Functor>
	requires(std::same_as<T, typename TensorIt::value_type> &&
	    std::constructible_from<T, typename TensorIt::value_type> &&
		std::invocable<Functor, T, T>)
	T accumulate(const TensorIt& begin, const TensorIt& end, T initial, Functor fn)
	{
		T acc = initial;
		int ctr = 0;
		while (begin != end)
		{
			T cur = begin[ctr++];
			acc = fn(acc, cur);
		}
		return acc;
	}

	template<Number T, class Tensor, typename Functor>
	requires(std::same_as<T, typename Tensor::value_type> &&
	    	std::invocable<Functor, T>)
	T accumulate(const Tensor& tensor, T initial, Functor fn)
	{
		return accumulate(tensor.begin(), tensor.end(), initial, fn);
	}


	template<Number T, class Tensor>
	requires(std::same_as<T, typename Tensor::value_type>)
	T computeMean(const Tensor& tensor)
	{
		int sum = 0;
		size_t size = tensor.size();
		// this doesn't have good cache reusing maybe because we aren't using blocks?
		#pragma omp parallel for reduction(+:sum)
		for (int i = 0; i < size; i++)
		{
			sum += (int)tensor[i];
		}
		return (sum / size);
	}

	template<Number T, class Tensor>
	requires(std::same_as<T, typename Tensor::value_type>)
	T computeVariance(const Tensor& tensor, T mean)
	{
		T curMean = computeMean<T, Tensor>(tensor);
		return (curMean - mean) * 2; // squared diff is this the fastest?
	}

// lacks referential transparency. If more than one thread is using this on the same
// tensor, then the tensor data will be added accordingly.
	template<typename Tensor>
	Tensor modifyTensorWithRandomInts(Tensor& tensor)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(1, 255);

		for (auto& elem : tensor)
		{
			elem = dis(gen);
		}
		return tensor;
	}

	template<Number T, class Tensor>
	requires (std::same_as<typename Tensor::value_type, T> &&
		std::constructible_from<Tensor, T>)
	Tensor randTensor(int channels, int rows, int cols)
	{
//		auto range = std::views::iota(0, channels) | std::views::transform([](int index)
//		{
//		  return FunctionalProgAlgos::randomColor();
//		});
//		Tensor result(range.begin(), range.end());
	}
}

#endif //TENSORLIB_TENSORALGORITHMS_H
