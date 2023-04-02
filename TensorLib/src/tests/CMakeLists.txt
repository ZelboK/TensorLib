include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
FetchContent_MakeAvailable(googletest)
add_executable(TensorLibTests LinearTests.cpp TensorSpec.cpp TensorIteratorSpec.cpp)

enable_testing()
target_link_libraries(TensorLibTests gtest_main)

add_test(NAME TensorLibTests COMMAND TensorLibTests) # TODO look up
