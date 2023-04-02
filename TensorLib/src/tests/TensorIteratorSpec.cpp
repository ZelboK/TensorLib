//
// Created by Danial javady on 2023-04-02.
//
#include <gtest/gtest.h>
#include "../domain/Linear.h"

TEST(doesNotEqual, TensorIterator)
{
	const Tensor<1, float> test(32);
	const TensorIterator<1, float, true> iterator = test.begin();
	Tensor<1, float> test2(32);
	TensorIterator<1, float, false> iterator2 = test2.begin();


}