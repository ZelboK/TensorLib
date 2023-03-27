#ifndef TENSORLIB_TENSORALGORITHMS_H
#define TENSORLIB_TENSORALGORITHMS_H

#include "../domain/Tensor.h"
#include "../domain/DefaultTypes.h"
#include "stb_image.h"
#include <functional>

namespace TensorAlgos {
	template<int N>
	void printImageTensor(TensorImpl<N, unsigned char> tensor);

	template<TensorIter TensorIt, TensorIter TensorOut, NumberType T, binary_op<T, T> Functor>
	T accumulate(TensorIt begin, TensorOut end, T initial, Functor fn);

	template<TensorIter Tensor, NumberType T, typename Functor>
	T accumulate(Tensor tensor, T initial, Functor fn);

	template<NumberType T, typename Tensor>
	T computeMean(Tensor tensor);
}

namespace TensorAlgos
{
	template<int N, typename T>
	TensorImpl<N, T> loadImage(const std::string& path);

	template<int rankA, int rankB, NumberType T, int rankC>
	TensorImpl<rankC, T> dotProd(TensorImpl<rankA, T> left,
		TensorImpl<rankB, T> right);

	template<int N>
	void printImageTensor(TensorImpl<N, unsigned char> tensor)
	{
		for (auto& elem : tensor)
		{
			std::cout << (int)elem << ","; // horrible printing lol
		}
	}


	template<TensorIter TensorIt, TensorIter TensorOut, NumberType T, binary_op<T, T> Functor>
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


	template<TensorIter Tensor, NumberType T, typename Functor>
	T accumulate(Tensor tensor, T initial, Functor fn)
	{
		return accumulate(tensor.begin(), tensor.end(), initial, fn);
	}

	template<NumberType T, typename Tensor>
	T computeMean(Tensor tensor) {
		int sum = 0;
		size_t size = tensor.size();
		// this doesn't have good cache reusing maybe because we aren't using blocks?
		std::cout << " testingdtb";
		#pragma omp parallel for reduction(+:sum)
		for(int i = 0; i<size; i++) {
			sum += (int) tensor[i];
		}
		return (sum/size);
	}
}

#endif //TENSORLIB_TENSORALGORITHMS_H
