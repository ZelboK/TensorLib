cmake_minimum_required(VERSION 3.24)
project(TensorLib)

set(CMAKE_CXX_STANDARD 20)

add_executable(TensorLib
        src/main.cpp
        src/domain/tensor.h
        src/domain/Linear.h
        src/domain/Module.h
        src/domain/Batch.h
        src/domain/DefaultTypes.h)

include(FetchContent)
FetchContent_Declare(
        stb_image
        GIT_REPOSITORY https://github.com/nothings/stb.git
        GIT_TAG        master
)
FetchContent_MakeAvailable(stb_image)

target_include_directories(TensorLib PRIVATE ${stb_image_SOURCE_DIR} src/logic)

#add_library(Algos src/logic/TensorAlgorithms.h)
#target_include_directories(Algos PRIVATE ${stb_image_SOURCE_DIR})

# Link Algos library to TensorLib
# target_link_libraries(TensorLib PRIVATE Algos)
target_link_libraries(TensorLib PRIVATE TensorAlgorithms)

add_subdirectory(src/tests)
add_subdirectory(src/logic)