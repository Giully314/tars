# TARS
TARS is a framework for manipulating symbols and formulas using C++ variables.

# How to build
cmake -B build -S . -GNinja --fresh -DCMAKE_TOOLCHAIN_FILE=cmake/homebrew.cmake (if on macos and want to use homebrew clang).
cmake --build build

# Resources
[Cppcon23 symbolic calculus](https://youtu.be/lPfA4SFojao?si=wd4-8vxe03peYqW6)  