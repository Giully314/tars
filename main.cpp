import std;
import tars.mp;

auto main() -> int {
    auto a = tars::unique_id();
    auto b = tars::unique_id();
    auto c = tars::unique_id();
    std::println("hello world {} {} {}", a, b, c);
    return 0;
}