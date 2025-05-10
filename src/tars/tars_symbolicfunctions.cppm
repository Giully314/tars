// tars/tars_symbolicfunctions.cppm
// PURPOSE:
//
// CLASSES:
//
// DESCRIPTION:
//
// USAGE:
//

export module tars.symbolic_functions;

import std;

import tars.symbol;

export namespace tars {

struct SinSymbol {
    template <typename Arg>
    constexpr auto operator()(Arg&& arg) {
        return std::sin(std::forward<Arg>(arg));
    }
};

// Function builder to use 'sin' in a formula context.
template <symbolic Arg>
constexpr auto sin(Arg) noexcept -> SymbolicExpression<SinSymbol, Arg> {
    return {};
}

} // namespace tars
