#include <iostream>
#include "domain/Tensor.h"
#include "TensorAlgorithms.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <unistd.h>

struct MyStruct
{
};

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

TensorImpl<1, float> miniExperiment(TensorImpl<1, float> out)
{
	auto first = out.begin();
	auto finished = out.end();
	int ctr = 0;
	auto out_it = out.begin();
	while (first != finished)
	{
		*out_it++ = ctr++;
		++first;
	}
	return out;
}

void printContents(unsigned char* data, int size) {
	unsigned char* itr = data;
	for(int i = 0;i<25;i++) {
		std::cout << (int)*itr << ", ";
		itr++;
	}
	std::cout << "\n";
}

int main()
{
	const std::string path = "shiki.jpg";
	const std::string shiki_path = R"(C:\Users\12893\Desktop\TensorLib\TensorLib\src\shiki.jpg)";
	int width, height, channels;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
	if (data == nullptr)
		std::cout << "OOI TO NA.";
	int totalSize = width*height*channels;
	auto tensor = TensorImpl<1, unsigned char>(data, totalSize);

	auto test = tensor.begin();

	TensorAlgos::printImageTensor(tensor);



	return 0;
}

