#include <iostream>
#include "domain/Tensor.h"
#include "TensorAlgorithms.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

template<typename TensorIn, typename TensorOut>
TensorOut initialize_imgs(TensorIn first, TensorIn last, TensorOut out)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_real_distribution<float>
		dist(0, 255); // Change to uniform_real_distribution since TensorImpl is using float type

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
auto graveyard()
{
	const std::string path = "shiki.jpg";
	int width, height, channels;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
	if (data == nullptr)
		std::cout << "OOI TO NA.";
	int totalSize = width * height * channels;
	auto tensor = TensorImpl<1, unsigned char>(data, totalSize);
	return tensor;
}



int main()
{
	auto tensor = graveyard();

	auto value = TensorAlgos::computeMean<unsigned char>(tensor);
	std::cout << value;
	return 0;
}

/*
 * //	const std::string path = "shiki.jpg";
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 100);

	std::vector<int> myVector(10030);
	std::generate(myVector.begin(), myVector.end(), [&](){ return dis(gen); });


std::vector<float> createVec() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 100);

	std::vector<float> myVector(2304923);
	std::generate(myVector.begin(), myVector.end(), [&](){ return dis(gen); });
	return myVector;
}
 */