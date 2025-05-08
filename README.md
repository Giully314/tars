# TARS
TARS is a framework for manipulating symbols and formulas using C++ variables.

# How to build
cmake -B build -S . -GNinja --fresh -DCMAKE_TOOLCHAIN_FILE=cmake/homebrew.cmake (if on macos and want to use homebrew clang).  
cmake --build build

# How to run tests
ctest --test-dir build

# Resources
[Cppcon23 symbolic calculus](https://youtu.be/lPfA4SFojao?si=wd4-8vxe03peYqW6)  

[Compile time counter C++11](https://b.atch.se/posts/constexpr-counter)  
[Compile time counter C++20](https://stackoverflow.com/a/74453799)  