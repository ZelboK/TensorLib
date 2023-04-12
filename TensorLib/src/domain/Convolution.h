//
// Created by 12893 on 2023-04-09.
//

#ifndef TENSORLIB_TENSORLIB_SRC_DOMAIN_CONVOLUTION_H_
#define TENSORLIB_TENSORLIB_SRC_DOMAIN_CONVOLUTION_H_
#include <vector>
#include "DefaultTypes.h"
#include <ranges>
template<Number T, int rank, class Container>
requires(
	std::same_as<typename Container::value_type, T>
) // no accountability for references
struct Convolution
{
	std::vector<Container> weights;

	Convolution(int inputChannels, int outputChannels, int kernelSize) {
		std::views::iota(0, inputChannels) | std::views::transform([](int i) {

		});
	}
};
#endif //TENSORLIB_TENSORLIB_SRC_DOMAIN_CONVOLUTION_H_
