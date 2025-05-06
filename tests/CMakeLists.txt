include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0
)

FetcContent_MakeAvailable(googletest)

# include(GoogleTest)
# gtest_discover_tests(hello_test)