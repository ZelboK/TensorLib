
# Create a library for TensorAlgorithms
add_library(TensorAlgorithms
        TensorAlgorithms.h
        TensorAlgorithms.cpp
        ModuleAlgorithms.hpp)

# Specify the include directories for the TensorAlgorithms library
target_include_directories(TensorAlgorithms
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        PRIVATE
        ${stb_image_SOURCE_DIR})

# Set the C++ standard to C++20 for the TensorAlgorithms library
target_compile_features(TensorAlgorithms PUBLIC cxx_std_20)
