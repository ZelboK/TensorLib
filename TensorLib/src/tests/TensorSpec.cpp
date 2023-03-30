//
// Created by Danial javady on 2023-03-12.
//
#include <gtest/gtest.h>
#include "../domain/Tensor.h"
#include "../logic/TensorAlgorithms.h"

TEST(constructor, Tensors) {
	TensorImpl<1, float> test(32);
	TensorAlgos::modifyTensorWithRandomInts(test);
}

TEST(constructor, TensorAlgos) {
	TensorImpl<1, float> test(32);
	TensorAlgos::modifyTensorWithRandomInts(test);

	auto expected = std::accumulate(test.begin(), test.end(), 0, [](int acc, int cur) {
		return acc+cur;
	}) / 32;
	auto actual = TensorAlgos::computeMean<int>(test);
	ASSERT_EQ(actual, expected);
}

