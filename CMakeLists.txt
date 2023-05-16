cmake_minimum_required(VERSION 3.18.4)
project(TensorLib)

set(CMAKE_CXX_STANDARD 20)

add_executable(TensorLib
        src/main.cpp
        src/domain/Linear.h
        src/domain/Module.h
        src/domain/Batch.h
        src/domain/DefaultTypes.h
        src/domain/Convolution.h)

find_package(Catch2 CONFIG REQUIRED)
file(DOWNLOAD "https://raw.githubusercontent.com/nothings/stb/master/stb_image.h" "include/stb_image.h" SHOW_PROGRESS)

add_subdirectory(src/tests)
add_subdirectory(src/logic)

target_include_directories(TensorLib PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/include src/logic)

target_link_libraries(TensorLib PRIVATE TensorAlgorithms OldTensorLib)


