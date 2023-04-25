//
// Created by Danial javady on 2023-04-02.
//
#include <gtest/gtest.h>

#include "../domain/Tensor.h"
#include <iostream>

class TensorImplTest : public ::testing::Test
{

};

class TensorImplTestSpec : public TensorImplTest
{
 protected:
	TensorImplTestSpec()
	{

	}
};


TEST(TensorImplTest, TensorIterator)
{
	const Tensor<1, float> test(32);
	const TensorIterator<1, float, true> iterator = test.begin();
	Tensor<1, float> test2(32);
	TensorIterator<1, float, false> iterator2 = test2.begin();
}

TEST(TensorImplTest, Tensor_Constructor_init_list)
{
	std::initializer_list<float> redInit = {
		23, 56, 192, 99, 12, 78, 164, 48,
		48, 211, 55, 67, 0, 255, 34, 120,
		128, 75, 24, 111, 204, 36, 59, 222,
		187, 54, 18, 69, 81, 157, 66, 39,
		37, 91, 123, 97, 172, 88, 42, 159,
		250, 11, 195, 6, 214, 49, 147, 63,
		87, 240, 112, 20, 131, 94, 26, 60,
		77, 83, 33, 107, 219, 71, 58, 46
	};
	Tensor<1, float> red = {
		redInit
	};

	std::initializer_list<float> blueInit = {
		71, 66, 156, 84, 39, 69, 80, 118,
		34, 190, 44, 109, 8, 253, 22, 115,
		126, 82, 17, 106, 198, 30, 50, 217,
		186, 42, 9, 64, 72, 150, 56, 28,
		21, 96, 120, 90, 165, 89, 55, 160,
		251, 1, 193, 5, 212, 38, 141, 54,
		74, 231, 113, 16, 130, 93, 15, 57,
		67, 79, 35, 110, 220, 77, 49, 40
	};
	Tensor<1, float> blue = { blueInit};


	std::initializer_list<float> greenInit = {
		97, 180, 52, 73, 27, 200, 32, 144,
		45, 210, 61, 37, 7, 254, 19, 121,
		127, 78, 25, 104, 201, 40, 62, 218,
		174, 57, 14, 67, 76, 155, 68, 35,
		29, 88, 114, 92, 167, 85, 47, 162,
		248, 4, 194, 10, 213, 43, 148, 65,
		79, 235, 105, 24, 129, 95, 31, 53,
		72, 81, 38, 100, 216, 70, 51, 41
	};
	Tensor<1, float> green = { greenInit };

	Tensor<3, float> rgb(red, green, blue);
	std::vector<float> rgbValues;

	EXPECT_EQ(red.size(), redInit.size());
	EXPECT_EQ(green.size(), greenInit.size());
	EXPECT_EQ(blue.size(), blueInit.size());
	EXPECT_EQ(red.size()+green.size()+blue.size(), rgb.size());

	EXPECT_TRUE(std::equal(red.begin(), red.end(), redInit.begin()));
	EXPECT_TRUE(std::equal(green.begin(), green.end(), greenInit.begin()));
	EXPECT_TRUE(std::equal(blue.begin(), blue.end(), blueInit.begin()));

	rgbValues.insert(rgbValues.end(), redInit.begin(), redInit.end());
	rgbValues.insert(rgbValues.end(), greenInit.begin(), greenInit.end());
	rgbValues.insert(rgbValues.end(), blueInit.begin(), blueInit.end());

	EXPECT_TRUE(std::equal(rgbValues.begin(), rgbValues.end(), rgb.begin()));

	for(int i = 0; i< rgbValues.size(); i++) {
		std::cout << rgbValues[i] << " vec,";
		std::cout << rgb[i] << " tensor,\n";
	}



}