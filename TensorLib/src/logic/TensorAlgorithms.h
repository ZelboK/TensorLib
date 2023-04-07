#ifndef TENSORLIB_TENSORALGORITHMS_H
#define TENSORLIB_TENSORALGORITHMS_H

#include "../domain/Tensor.h"
#include "../domain/DefaultTypes.h"
#include <functional>

namespace TensorAlgos
{
	template<int N>
	void printImageTensor(const Tensor<N, unsigned char>& tensor);

	template<Container_V TensorIt, Container_V TensorOut, Number T, binary_fn<T, T> Functor>
	T accumulate(const TensorIt& begin, const TensorOut& end, T initial, Functor fn);

	template<Container_V Tensor, Number T, typename Functor>
	T accumulate(const Tensor& tensor, T initial, Functor fn);

	template<Number T, Container_V Tensor>
	T computeMean(const Tensor& tensor);

// lacks referential transparency. If more than one thread is using this on the same
// tensor, then the tensor data will be added accordingly.
	template<typename Tensor>
	Tensor modifyTensorWithRandomInts(Tensor& tensor);

	template<Number T, Container_V Tensor>
	T computeVariance(const Tensor& tensor, T mean);

	template<Number T, Container_V Tensor>
	T computeStandardDeviation(const Tensor& tensor, T mean);

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

	template<Container_V TensorIt, Container_V TensorOut, Number T, binary_fn<T, T> Functor>
	T accumulate(const TensorIt& begin, const TensorOut& end, T initial, Functor fn)
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

	template<Container_V Tensor, Number T, typename Functor>
	T accumulate(const Tensor& tensor, T initial, Functor fn)
	{
		return accumulate(tensor.begin(), tensor.end(), initial, fn);
	}

	template<int rank, Number T>
	T computeMeans(Tensor<rank, T> tensor);

	template<Number T, Container_V Tensor>
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

	template<Number T, Container_V Tensor>
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
}

#endif //TENSORLIB_TENSORALGORITHMS_H
