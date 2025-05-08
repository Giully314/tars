include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0
)

FetchContent_MakeAvailable(googletest)

add_executable(
    test_mp
)
target_sources(test_mp PRIVATE test_mp.cpp)
target_link_libraries(test_mp PRIVATE GTest::gtest_main tars)

add_executable(
    test_symbol
)
target_sources(test_symbol PRIVATE test_symbol.cpp)
target_link_libraries(test_symbol PRIVATE GTest::gtest_main tars)
    
include(GoogleTest)
gtest_discover_tests(test_mp)
gtest_discover_tests(test_symbol)