
# Create a library for TensorAlgorithms
add_library(TensorAlgorithms
        TensorAlgorithms.hpp
        TensorAlgorithms.cpp
        FunctionalProgrammingAlgos.hpp
        ModuleAlgorithms.hpp
        ParallelAlgorithms.hpp)

target_include_directories(TensorAlgorithms
        PUBLIC
        "${CMAKE_SOURCE_DIR}/include"
        "${CMAKE_SOURCE_DIR}/src/domain")

# REQUIRED FOR LINKER ERROR
target_compile_features(TensorAlgorithms PUBLIC cxx_std_20)
