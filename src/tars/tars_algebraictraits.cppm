// tars/tars_algebraictraits.cppm
// PURPOSE: Define type traits for algebraic concepts.
//
// DESCRIPTION:
//  This component defines algebraic traits to customize symbols based on their mathematical
//  properties. For example we could have a symbol that represent a matrix which implies non
//  commutativity and so some optimization are not available.
//

export module tars.algebraic_traits;

import std;

export namespace tars {
struct Uncostrained {
    template<typename T>
    struct trait: std::true_type {};
};

struct Real {
    template<typename T>
    struct trait: std::is_floating_point<T> {};
};

} // namespace tars
