include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
FetchContent_MakeAvailable(googletest)
set(TESTS LinearTests.cpp
        TensorAlgosSpec.cpp
        TensorIteratorSpec.cpp
        ModuleAlgorithmsSpec.cpp)

add_executable(TensorLibTests
        ${TESTS})

enable_testing()
target_link_libraries(TensorLibTests
        TensorAlgorithms
        gtest_main)
target_include_directories(TensorLibTests PRIVATE
        "${CMAKE_SOURCE_DIR}/src/domain"
        "${CMAKE_SOURCE_DIR}/src/logic")

add_test(NAME TensorLibTests COMMAND TensorLibTests)
