#include <iostream>
#include "domain/Tensor.h"
#include "TensorAlgorithms.h"

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"
#include "logic/ModuleAlgorithms.hpp"

template<typename TensorIn, typename TensorOut>
TensorOut initialize_imgs(TensorIn first, TensorIn last, TensorOut out)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_real_distribution<float>
		dist(0, 255); // Change to uniform_real_distribution since Tensor is using float type

	auto out_it = out.begin(); // Iterator for the output tensor
	while (first != last)
	{
		*out_it++ = dist(rng); // Assign random values to the output tensor
		++first;
	}
	std::cout << out[0] << "Hello there";
	return out;
}

// obviously this is trash code but im just experimenting
Tensor<1, unsigned char> graveyard()
{
	const std::string path = R"(shiki.jpg)";
	int width, height, channels;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
	if (data == nullptr)
		std::cout << "OOI TO NA.";
	int totalSize = width * height * channels;
	auto tensor = Tensor<1, unsigned char>(data, totalSize);
	return tensor;
}

template<typename Op, typename Arg>
concept A_B = std::invocable<Op, Arg>;

struct MyStruct
{
};

int stupid(int i)
{
	return i + 1;
}

template<A_B<int> Fn>
void iAccept(Fn fn, int i)
{
	fn(i);
}

int main()
{
	Tensor<1, unsigned char> tensor = graveyard();
	// std::vector<Tensor<1, unsigned char>> batch{tensor};

	Tensor<1, int> yo(32);
	yo.map([](int cur)
	{
	  return cur;
	});
//	ModuleAlgorithms::normalize<int>(yo, 0, 0);
	return 0;
}
