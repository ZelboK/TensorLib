cmake_minimum_required(VERSION 3.24)
project(TensorLib)

set(CMAKE_CXX_STANDARD 20)

add_executable(TensorLib
        src/main.cpp
        src/domain/tensor.h
        src/domain/Linear.h
        src/domain/Module.h
        src/domain/Batch.h
        src/domain/DefaultTypes.h
        src/domain/Convolution.h)

file(DOWNLOAD "https://raw.githubusercontent.com/nothings/stb/master/stb_image.h" "${CMAKE_CURRENT_SOURCE_DIR}/include/stb_image.h" SHOW_PROGRESS)

add_subdirectory(src/tests)
add_subdirectory(src/logic)

target_include_directories(TensorLib PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/include src/logic)
target_include_directories(TensorLib PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/include ${PROJECT_SOURCE_DIR}/src/logic)

target_link_libraries(TensorLib PRIVATE TensorAlgorithms)
