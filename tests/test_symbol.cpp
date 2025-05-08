#include <gtest/gtest.h>

import std;
import tars.symbol;

using namespace tars;

TEST(TestSymbolBinder, Binder) {
    Symbol x;

    const int i = 3;
    SymbolBinder q{x = i};

    static_assert(std::same_as<decltype(q)::deduced_type, const int&>);

    int o = 3;
    SymbolBinder w{x = o};
    static_assert(std::same_as<decltype(w)::deduced_type, int&>);

    SymbolBinder e{x = 3};
    static_assert(std::same_as<decltype(e)::deduced_type, int&&>);
}