//
// Created by 12893 on 2023-03-28.
//

#ifndef TENSORLIB_TENSORLIB_SRC_LOGIC_FUNCTIONALPROGALGOS_HPP_
#define TENSORLIB_TENSORLIB_SRC_LOGIC_FUNCTIONALPROGALGOS_HPP_

#include "../domain/DefaultTypes.h"

namespace FPAlgos {

	template <Tensor first, Tensor second>
	auto zip(first, second);
}

namespace FPAlgos {



	template <Number T, Tensor first, Tensor second, binary_op<T, T> functor>
	auto zip(first, second, functor) {
 
	}
}


#endif //TENSORLIB_TENSORLIB_SRC_LOGIC_FUNCTIONALPROGALGOS_HPP_
