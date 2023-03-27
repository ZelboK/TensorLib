include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
FetchContent_MakeAvailable(googletest)
add_executable(LinearTests LinearTests.cpp)

enable_testing()
target_link_libraries(LinearTests gtest_main)

add_test(NAME LinearTests COMMAND LinearTests) # TODO look up
