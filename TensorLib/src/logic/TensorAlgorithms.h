#ifndef TENSORLIB_TENSORALGORITHMS_H
#define TENSORLIB_TENSORALGORITHMS_H


#include "../domain/Tensor.h"
#include "../domain/DefaultTypes.h"
#include <functional>

namespace TensorAlgos {
	template<int N>
	void printImageTensor(TensorImpl<N, unsigned char> tensor);

	template <Number T>
	T computeSquaredDiff(T a, T b);

	template<Tensor TensorIt, Tensor TensorOut, Number T, binary_fn<T, T> Functor>
	T accumulate(TensorIt begin, TensorOut end, T initial, Functor fn);

	template<Tensor Tensor, Number T, typename Functor>
	T accumulate(Tensor tensor, T initial, Functor fn);

	template<Number T, typename Tensor>
	T computeMean(Tensor tensor);

	// lacks referential transparency. If more than one thread is using this on the same
	// tensor, then the tensor data will be added accordingly.
	template<typename Tensor>
	Tensor modifyTensorWithRandomInts(Tensor& tensor);

	template<Number T, Tensor Tensor>
	T computeVariance(Tensor tensor, T mean);

	template<Number T, Tensor Tensor>
	T computeStandardDeviation(Tensor tensor, T mean);


}

namespace TensorAlgos
{
	template<int N>
	void printImageTensor(TensorImpl<N, unsigned char> tensor)
	{
		for (auto& elem : tensor)
		{
			std::cout << (int)elem << ","; // horrible printing lol
		}
	}

	template <Number T>
	T computeSquaredDiff(T a, T b) {

	}

	template<Tensor TensorIt, Tensor TensorOut, Number T, binary_fn<T, T> Functor>
	T accumulate(TensorIt begin, TensorOut end, T initial, Functor fn)
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


	template<Tensor Tensor, Number T, typename Functor>
	T accumulate(Tensor tensor, T initial, Functor fn)
	{
		return accumulate(tensor.begin(), tensor.end(), initial, fn);
	}

	template<Number T, typename Tensor>
	T computeMean(Tensor tensor) {
		int sum = 0;
		size_t size = tensor.size();
		// this doesn't have good cache reusing maybe because we aren't using blocks?
		#pragma omp parallel for reduction(+:sum)
		for(int i = 0; i<size; i++) {
			sum += (int) tensor[i];
		}
		return (sum/size);
	}

	template <Number T, typename Tensor>
	T computeVariance(Tensor tensor, T mean) {
		T curMean = computeMean(tensor);
		return (curMean - mean)*2; // squared diff is this the fastest?
	}

	// lacks referential transparency. If more than one thread is using this on the same
	// tensor, then the tensor data will be added accordingly.
	template<typename Tensor>
	Tensor modifyTensorWithRandomInts(Tensor& tensor) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(1, 255);

		for(auto & elem : tensor) {
			elem = dis(gen);
		}
		return tensor;
	}
}

#endif //TENSORLIB_TENSORALGORITHMS_H
