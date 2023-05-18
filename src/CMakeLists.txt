
set(HEADERS
        domain/Linear.h
        domain/Module.h
        domain/Batch.h
        domain/DefaultTypes.h
        domain/Convolution.h)

set(ALGORITHMS
        logic/TensorAlgorithms.hpp
        logic/TensorAlgorithms.cpp
        logic/FunctionalProgrammingAlgos.hpp
        logic/ModuleAlgorithms.hpp
        logic/ParallelAlgorithms.hpp )

add_library(TensorAlgorithms
        ${HEADERS}
        ${ALGORITHMS})

target_include_directories(TensorAlgorithms
        PUBLIC
        "${CMAKE_SOURCE_DIR}/include"
        "${CMAKE_SOURCE_DIR}/src/domain"
        "${CMAKE_SOURCE_DIR}/src/logic")

# REQUIRED FOR LINKER ERROR
target_compile_features(TensorAlgorithms PUBLIC cxx_std_20)
