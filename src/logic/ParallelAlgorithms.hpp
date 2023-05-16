//
// Created by 12893 on 2023-03-30.
//

#include "old_tensor_impl/Tensor.h"
#include "DefaultTypes.h"
#ifndef TENSORLIB_TENSORLIB_SRC_LOGIC_PARALLELALGORITHMS_HPP_
#define TENSORLIB_TENSORLIB_SRC_LOGIC_PARALLELALGORITHMS_HPP_

#endif //TENSORLIB_TENSORLIB_SRC_LOGIC_PARALLELALGORITHMS_HPP_

namespace ParAlgos
{

	template<Number T, int rank, class Container, class Tensor, typename Function>
	T reduceMapBatch(const Container batch, Function fn);

	template<Number T, class Tensor>
	T computeMean(const Tensor& tensor);
}

namespace ParAlgos
{

	template<Number T, int rank, class Container, class Tensor, typename Function>
	requires (std::invocable<Function, Container, T> &&
		std::same_as<T, typename Container::value_type>)
	T reduceMapBatch(const Container batch, Function fn)
	{
		int sum = 0;
		size_t size = batch.size();
		// this doesn't have good cache reusing maybe because we aren't using blocks?
		#pragma omp parallel for reduction(+:sum)
		for (auto& tensor : batch)
		{
			sum += computeMean(tensor);

		}
		return (sum / size);
	}

	template<Number T, class Tensor>
	T computeMean(const Tensor& tensor)
	{
		int sum = 0;
		size_t size = tensor.size();
		// this doesn't have good cache reusing maybe because we aren't using blocks?
		#pragma omp parallel for reduction(+:sum)
		for (auto& elem : tensor)
		{
			sum += elem;
		}
		return (sum / size);
	}
}