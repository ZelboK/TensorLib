set(TESTS LinearTests.cpp)

add_executable(MLTestSuite
        ${TESTS})

enable_testing()
target_link_libraries(MLTestSuite
        TensorAlgorithms
        Catch2::Catch2
        Catch2::Catch2WithMain)

add_test(NAME MLAlgosTests COMMAND MLAlgosTests)
