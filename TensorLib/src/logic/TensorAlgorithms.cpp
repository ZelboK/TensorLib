//
// Created by 12893 on 2023-03-18.
//

#include "TensorAlgorithms.hpp"
#include "../domain/Tensor.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


/*
 * At some point, in this project, I wanted to attempt trying to factor out some of the logic
 * in templated code in a cpp file.
 * This can likely be refactored(and perhaps should for consistency reasons) in to the hpp
 *
 */
namespace TensorAlgos
{
	template<int N, typename T>
	Tensor<N, T> loadImage(const std::string& path)
	{
		int width, height, channels;
		unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		Tensor<N, T> tensor(data, width * height * channels);
		return tensor;
	}

	// Explicit instantiation
	template Tensor<1, unsigned char> loadImage<1, unsigned char>(const std::string& path);



}