#ifndef TENSORLIB_TENSORALGORITHMS_H
#define TENSORLIB_TENSORALGORITHMS_H

#include "../domain/Tensor.h"
#include "../domain/DefaultTypes.h"
#include "stb_image.h"

namespace TensorAlgos {
    template <int N, typename T>
    TensorImpl<N, T> loadImage(const std::string& path);

    template <int rankA, int rankB, NumberType T, int rankC>
    TensorImpl<rankC, T> dotProd(TensorImpl<rankA, T> left,
                                 TensorImpl<rankB, T> right);

	template <int N>
	void printImageTensor(TensorImpl<N, unsigned char> tensor);
}




#endif //TENSORLIB_TENSORALGORITHMS_H
