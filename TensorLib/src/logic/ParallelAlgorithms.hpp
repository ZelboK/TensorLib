//
// Created by 12893 on 2023-03-30.
//

#include "../domain/Tensor.h"
#ifndef TENSORLIB_TENSORLIB_SRC_LOGIC_PARALLELALGORITHMS_HPP_
#define TENSORLIB_TENSORLIB_SRC_LOGIC_PARALLELALGORITHMS_HPP_

#endif //TENSORLIB_TENSORLIB_SRC_LOGIC_PARALLELALGORITHMS_HPP_

namespace ParAlgos {
	template<typename T, int rank, unary_fn<Tensor<rank, T>> Function>
	T reduceMapBatch(const std::vector<Tensor<rank, T>>& batch, Function fn);

	template<Number T, Container_V Tensor>
	T computeMean(const Tensor& tensor);
}

namespace ParAlgos {
	template<typename T, int rank, unary_fn<Tensor<rank, T>> Function>
	T reduceMapBatch(const std::vector<Tensor<rank, T>>& batch, Function fn) {
		int sum = 0;
		size_t size = batch.size();
		// this doesn't have good cache reusing maybe because we aren't using blocks?
		#pragma omp parallel for reduction(+:sum)
		for(auto & tensor : batch) {
			sum += computeMean<T, Tensor<rank, T>>(tensor);

		}
		return (sum/size);
	}
	template<Number T, Container_V Tensor>
	T computeMean(const Tensor& tensor) {
		int sum = 0;
		size_t size = tensor.size();
		// this doesn't have good cache reusing maybe because we aren't using blocks?
		#pragma omp parallel for reduction(+:sum)
		for(auto& elem : tensor) {
			sum += elem;
		}
		return (sum/size);
	}
}