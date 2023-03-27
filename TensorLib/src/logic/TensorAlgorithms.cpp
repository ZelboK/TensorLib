//
// Created by 12893 on 2023-03-18.
//

#include "stb_image.h"
#include "TensorAlgorithms.h"
#include "../domain/Tensor.h"
#define STB_IMAGE_IMPLEMENTATION

namespace TensorAlgos
{
	template<int N, typename T>
	TensorImpl<N, T> loadImage(const std::string& path)
	{
		int width, height, channels;
		unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		TensorImpl<N, T> tensor(data, width * height * channels);
		return tensor;
	}

	// Explicit instantiation
	template TensorImpl<1, unsigned char> loadImage<1, unsigned char>(const std::string& path);



}