//
// Created by Danial javady on 2023-03-12.
//
#include <gtest/gtest.h>
#include "../domain/Tensor.h"
#include "../logic/TensorAlgorithms.hpp"

class TensorTest : public ::testing::Test
{
 protected:
	size_t size = 32;
	Tensor<1, float> test;

	TensorTest() : test(size)
	{
	}
};

class TensorAlgosTest : public TensorTest
{
 protected:
	TensorAlgosTest()
	{
		TensorAlgos::modifyTensorWithRandomInts(test);
	}
};

TEST_F(TensorTest, TransformAndModify)
{
	for (int i = 0; i < test.size(); i++)
	{
		test[i] = i;
	}

	test.map([](float cur)
	{
	  return cur * 5;
	});

	for (int i = 0; i < test.size(); i++)
	{
		ASSERT_TRUE(test[i] == i * 5);
	}
}

TEST_F(TensorTest, AssignmentOperator)
{
	Tensor<1, float> copied = test;
	ASSERT_TRUE(test == copied);
}

TEST_F(TensorAlgosTest, ComputeMean)
{
	auto expected = std::accumulate(test.begin(), test.end(), 0, [](int acc, int cur)
	{

	  return acc + cur;
	}) / 32;

	auto actual = TensorAlgos::computeMean<float>(test);
	ASSERT_EQ(actual, expected);
}

TEST_F(TensorAlgosTest, ComputeVariance)
{
	auto mean = std::accumulate(test.begin(), test.end(), 0, [](int acc, int cur)
	{
	  return acc + cur;
	}) / 32;
	Tensor<1, int> randTensor(32);
	TensorAlgos::modifyTensorWithRandomInts(randTensor);
	auto randTensorMean = std::accumulate(randTensor.begin(), randTensor.end(),
		0,
		[](int acc, int cur)
		{
		  return acc + cur;
		}) / 32;

	int actual = TensorAlgos::computeVariance(randTensor, mean);
	auto expected = (mean - randTensorMean)*(mean - randTensorMean);
	ASSERT_EQ(actual, expected);
}

TEST_F(TensorAlgosTest, CopyConstructor)
{
	Tensor<1, float> copied(test);
	ASSERT_TRUE(test == copied);
}

TEST_F(TensorAlgosTest, std_transform)
{
	Tensor<1, float> copied(test);
	std::transform(copied.begin(), copied.end(), copied.begin(), [](float cur)
	{
	  return cur;
	});

	ASSERT_TRUE(test == copied);
}