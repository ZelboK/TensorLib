# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/12893/Desktop/TensorLib/TensorLib/cmake-build-debug/_deps/stb_image-src"
  "C:/Users/12893/Desktop/TensorLib/TensorLib/cmake-build-debug/_deps/stb_image-build"
  "C:/Users/12893/Desktop/TensorLib/TensorLib/cmake-build-debug/_deps/stb_image-subbuild/stb_image-populate-prefix"
  "C:/Users/12893/Desktop/TensorLib/TensorLib/cmake-build-debug/_deps/stb_image-subbuild/stb_image-populate-prefix/tmp"
  "C:/Users/12893/Desktop/TensorLib/TensorLib/cmake-build-debug/_deps/stb_image-subbuild/stb_image-populate-prefix/src/stb_image-populate-stamp"
  "C:/Users/12893/Desktop/TensorLib/TensorLib/cmake-build-debug/_deps/stb_image-subbuild/stb_image-populate-prefix/src"
  "C:/Users/12893/Desktop/TensorLib/TensorLib/cmake-build-debug/_deps/stb_image-subbuild/stb_image-populate-prefix/src/stb_image-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/12893/Desktop/TensorLib/TensorLib/cmake-build-debug/_deps/stb_image-subbuild/stb_image-populate-prefix/src/stb_image-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/12893/Desktop/TensorLib/TensorLib/cmake-build-debug/_deps/stb_image-subbuild/stb_image-populate-prefix/src/stb_image-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
