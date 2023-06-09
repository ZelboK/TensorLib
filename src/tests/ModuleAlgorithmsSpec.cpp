//
// Created by Danial javady on 2023-04-03.
//
#include <gtest/gtest.h>
#include "old_tensor_impl/Tensor.h"
#include "ModuleAlgorithms.hpp"
#include "Batch.h"

class ModuleTest : public ::testing::Test
{
 protected:
	std::vector<float> r = {
		23, 56, 192, 99, 12, 78, 164, 48,
		48, 211, 55, 67, 0, 255, 34, 120,
		128, 75, 24, 111, 204, 36, 59, 222,
		187, 54, 18, 69, 81, 157, 66, 39,
		37, 91, 123, 97, 172, 88, 42, 159,
		250, 11, 195, 6, 214, 49, 147, 63,
		87, 240, 112, 20, 131, 94, 26, 60,
		77, 83, 33, 107, 219, 71, 58, 46
	};

	std::vector<float> g = {
		97, 180, 52, 73, 27, 200, 32, 144,
		45, 210, 61, 37, 7, 254, 19, 121,
		127, 78, 25, 104, 201, 40, 62, 218,
		174, 57, 14, 67, 76, 155, 68, 35,
		29, 88, 114, 92, 167, 85, 47, 162,
		248, 4, 194, 10, 213, 43, 148, 65,
		79, 235, 105, 24, 129, 95, 31, 53,
		72, 81, 38, 100, 216, 70, 51, 41
	};

	std::vector<float> b = {
		71, 66, 156, 84, 39, 69, 80, 118,
		34, 190, 44, 109, 8, 253, 22, 115,
		126, 82, 17, 106, 198, 30, 50, 217,
		186, 42, 9, 64, 72, 150, 56, 28,
		21, 96, 120, 90, 165, 89, 55, 160,
		251, 1, 193, 5, 212, 38, 141, 54,
		74, 231, 113, 16, 130, 93, 15, 57,
		67, 79, 35, 110, 220, 77, 49, 40
	};

};

class ModuleAlgosTest : public ModuleTest
{
 protected:
	ModuleAlgosTest()
	= default;
};

TEST_F(ModuleTest, reduceMapBatch)
{
	Tensor<3, int> random(32);
	Tensor<3, int> random2(32);

	TensorAlgos::modifyTensorWithRandomInts(random);
	TensorAlgos::modifyTensorWithRandomInts(random2);
	std::vector<Tensor<3, int> > batch{ random, random2 };
	int actualMean = ModuleAlgorithms::computeMeanBatch<int, 3>(batch);

	int expectedMean = 0;
	int size = 0;
	for (auto& tensor : batch)
	{
		size += tensor.size();
		for (auto& elem : tensor)
		{
			expectedMean += elem;
		}
	}
	expectedMean /= size;
	double absolute_error = 1e-9;
	ASSERT_NEAR(expectedMean, actualMean, absolute_error);
}

TEST_F(ModuleTest, batchVariance)
{
	std::vector<std::vector<float>> batch{ r, g, b };
	std::vector<float> savedMeans;
	float mean = 0;
	for (auto& vecTensor : batch)
	{
		float curMean = 0;
		for (auto& elem : vecTensor)
		{
			curMean += elem;
		}
		savedMeans.push_back(curMean / vecTensor.size());
		mean += (curMean / vecTensor.size());
	}
	float batchMean = (mean / batch.size());
	float varianceAcc = 0;

	for (auto& curMean : savedMeans)
	{
		float curDiff = (batchMean - curMean);
		varianceAcc += (curDiff * curDiff);
	}
	float expectedBatchVariance = varianceAcc / savedMeans.size();
	Tensor<1, float> rChannel(r.begin(), r.end());
	Tensor<1, float> gChannel(g.begin(), g.end());
	Tensor<1, float> bChannel(b.begin(), b.end());
	std::vector<Tensor<1, float>> batchActual { rChannel, gChannel, bChannel };

	auto actualVariance = ModuleAlgorithms::computeVarianceBatch<float,
										   3,
										   Tensor<1, float>>(batchActual);

	ASSERT_EQ(expectedBatchVariance, actualVariance);
}

TEST_F(ModuleTest, batch_norm_2d)
{
	Tensor<1, float> red = {
		23, 56, 192, 99, 12, 78, 164, 48,
		48, 211, 55, 67, 0, 255, 34, 120,
		128, 75, 24, 111, 204, 36, 59, 222,
		187, 54, 18, 69, 81, 157, 66, 39,
		37, 91, 123, 97, 172, 88, 42, 159,
		250, 11, 195, 6, 214, 49, 147, 63,
		87, 240, 112, 20, 131, 94, 26, 60,
		77, 83, 33, 107, 219, 71, 58, 46
	};

	Tensor<1, float> blue = {
		71, 66, 156, 84, 39, 69, 80, 118,
		34, 190, 44, 109, 8, 253, 22, 115,
		126, 82, 17, 106, 198, 30, 50, 217,
		186, 42, 9, 64, 72, 150, 56, 28,
		21, 96, 120, 90, 165, 89, 55, 160,
		251, 1, 193, 5, 212, 38, 141, 54,
		74, 231, 113, 16, 130, 93, 15, 57,
		67, 79, 35, 110, 220, 77, 49, 40
	};

	Tensor<1, float> green = {
		97, 180, 52, 73, 27, 200, 32, 144,
		45, 210, 61, 37, 7, 254, 19, 121,
		127, 78, 25, 104, 201, 40, 62, 218,
		174, 57, 14, 67, 76, 155, 68, 35,
		29, 88, 114, 92, 167, 85, 47, 162,
		248, 4, 194, 10, 213, 43, 148, 65,
		79, 235, 105, 24, 129, 95, 31, 53,
		72, 81, 38, 100, 216, 70, 51, 41
	};

	Tensor<1, float> normalizedRed = {
		-1.0757, -0.5842, 1.4416, 0.0563, -1.2396, -0.2565, 1.0245, -0.7033,
		-0.7033, 1.7246, -0.5991, -0.4203, -1.4183, 2.3800, -0.9119, 0.3691,
		0.4883, -0.3012, -1.0608, 0.2351, 1.6203, -0.8821, -0.5395, 1.8885,
		1.3671, -0.6140, -1.1502, -0.3905, -0.2118, 0.9203, -0.4352, -0.8374,
		-0.8672, -0.0628, 0.4138, 0.0265, 1.1437, -0.1075, -0.7927, 0.9501,
		2.3055, -1.2545, 1.4863, -1.3290, 1.7693, -0.6884, 0.7713, -0.4799,
		-0.1224, 2.1566, 0.2500, -1.1204, 0.5330, -0.0182, -1.0310, -0.5246,
		-0.2714, -0.1820, -0.9268, 0.1755, 1.8438, -0.3607, -0.5544, -0.7331
	};

	Tensor<1, float> normalizedGreen = {
		0.0044, 1.2306, -0.6604, -0.3502, -1.0297, 1.5260, -0.9559, 0.6987,
		-0.7638, 1.6738, -0.5274, -0.8820, -1.3252, 2.3238, -1.1479, 0.3589,
		0.4476, -0.2763, -1.0593, 0.1078, 1.5408, -0.8377, -0.5127, 1.7919,
		1.1419, -0.5865, -1.2218, -0.4388, -0.3059, 0.8612, -0.4240, -0.9116,
		-1.0002, -0.1286, 0.2555, -0.0695, 1.0385, -0.1729, -0.7343, 0.9646,
		2.2351, -1.3695, 1.4374, -1.2809, 1.7181, -0.7934, 0.7578, -0.4684,
		-0.2615, 2.0431, 0.1226, -1.0741, 0.4771, -0.0252, -0.9706, -0.6456,
		-0.3649, -0.2320, -0.8672, 0.0487, 1.7624, -0.3945, -0.6752, -0.8229
	};

	Tensor<1, float> normalizedBlue = {
		-0.3607, -0.4352, 0.9054, -0.1671, -0.8374, -0.3905, -0.2267, 0.3393,
		-0.9119, 1.4118, -0.7629, 0.2053, -1.2992, 2.3502, -1.0906, 0.2947,
		0.4585, -0.1969, -1.1651, 0.1606, 1.5310, -0.9715, -0.6736, 1.8140,
		1.3522, -0.7927, -1.2843, -0.4650, -0.3459, 0.8160, -0.5842, -1.0013,
		-1.1055, 0.0116, 0.3691, -0.0777, 1.0394, -0.0926, -0.5991, 0.9649,
		2.3204, -1.4034, 1.4565, -1.3439, 1.7395, -0.8523, 0.6819, -0.6140,
		-0.3161, 2.0225, 0.2649, -1.1800, 0.5181, -0.0330, -1.1949, -0.5693,
		-0.4203, -0.2416, -0.8970, 0.2202, 1.8587, -0.2714, -0.6884, -0.8225
	};

	Tensor<3, float> rgb(red, green, blue);
	Tensor<3, float> rgb2(green, blue, red);
	Tensor<3, float> normalizedRgb(normalizedRed, normalizedGreen, normalizedBlue);
	Tensor<3, float> normalizedRgb2(normalizedGreen, normalizedBlue, normalizedRed);

	std::vector<Tensor<3, float>> batch;
	batch.emplace_back(rgb);
	batch.emplace_back(rgb2);
	Batch<float, Tensor<3, float>, 3> batchNormed(batch);

	std::cout << "\n";

	auto vec = batchNormed.forward();

	std::vector<Tensor<3, double>> expectedBatch;

	expectedBatch.emplace_back(normalizedRgb);
	expectedBatch.emplace_back(normalizedRgb2);
	Batch<double, Tensor<3, double>, 3> expected(expectedBatch);

	// assert both are equal in size ... or refactor later to use zip
	for (int i = 0; i < batch.size(); i++)
	{
		Tensor<3, double> curTensor = vec[i];
		Tensor<3, double> expectedTensor = expectedBatch[i];

		for (int j = 0; j < curTensor.size(); j++)
		{
			double cur = curTensor[j];
			double expected = expectedTensor[j];

			ASSERT_EQ(cur, expected);
		}
	}

}