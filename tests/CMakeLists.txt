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
# target_include_directories(test_mp PRIVATE ${TARS_SOURCE_DIR}/src)    
    
include(GoogleTest)
gtest_discover_tests(test_mp)