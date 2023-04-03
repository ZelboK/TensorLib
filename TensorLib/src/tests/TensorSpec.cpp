//
// Created by Danial javady on 2023-03-12.
//
#include <gtest/gtest.h>
#include "../domain/Tensor.h"
#include "../logic/TensorAlgorithms.h"

class TensorTest : public ::testing::Test {
 protected:
	Tensor<1, float> test{32};
};

class TensorAlgosTest : public TensorTest {
 protected:
	TensorAlgosTest() {
		TensorAlgos::modifyTensorWithRandomInts(test);
	}
};

TEST_F(TensorTest, Constructor) {
}

TEST_F(TensorTest, TransformAndModify) {
	for(int i = 0; i < test.size(); i++) {
		test[i] = i;
	}

	test.map([](float cur) {
	  return cur * 5;
	});

	for(int i = 0; i < test.size(); i++) {
		ASSERT_TRUE(test[i] == i * 5);
	}
}

TEST_F(TensorTest, AssignmentOperator) {
	Tensor<1, float> copied = test;
	ASSERT_TRUE(test == copied);
}



TEST_F(TensorAlgosTest, ComputeMean) {
	auto expected = std::accumulate(test.begin(), test.end(), 0, [](int acc, int cur) {
	  return acc + cur;
	}) / 32;
	auto actual = TensorAlgos::computeMean<int>(test);
	ASSERT_EQ(actual, expected);
}

TEST_F(TensorAlgosTest, CopyConstructor) {
	Tensor<1, float> copied(test);
	ASSERT_TRUE(test == copied);
}
