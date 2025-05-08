// tars/tars_symbol.cppm
// PURPOSE: Define the basic components for manipulating symbols and formula.
//
// CLASSES:
//
// DESCRIPTION:
//  This component provides implementation of a Symbol and Formula class, used to shape a DSL for
//  manipulating mathematical formula directly in C++ (check USAGE below). The symbols are abstract
//  entities that could represent whatever object (numbers, tensors, functions). We can also apply
//  transformation for computing derivatives (backward pass) or other operators.
//
// USAGE:
//  Symbol a;
//  Symbol b;
//  Formula f = a + b * b
//  auto result = f(a = 1.3, b = 3.14);

export module tars.symbol;

import std;
import tars.mp;
import tars.type_traits;
import tars.algebraic_traits;

namespace tars {

/// @brief Class binder for symbol.
/// @tparam T Type of the value to be assigned to a symbol.
/// @tparam TSymbol Symbol.
export template<typename TSymbol, typename T>
struct SymbolBinder {
    using symbol_type = TSymbol;
    using value_type = std::remove_cvref_t<T>;
    using deduced_type = T;

    template<typename U>
        requires std::is_convertible_v<U&&, requalify_as_const_t<remove_rvalue_reference_t<T>>>
    constexpr SymbolBinder(TSymbol, U&& x) noexcept(
        std::is_nothrow_convertible_v<U&&, requalify_as_const_t<remove_rvalue_reference_t<T>>>)
        : value{std::forward<U>(x)} {}

    auto operator()() const noexcept -> const value_type& {
        return value;
    }

public:
    static constexpr TSymbol symbol{};

private:
    requalify_as_const_t<remove_rvalue_reference_t<T>> value;
};

template<typename TSymbol, typename T>
SymbolBinder(TSymbol, T&&) -> SymbolBinder<TSymbol, T&&>;

/// @brief Define the Symbol class, the atom of a formula.
/// This class defines the core type representing a symbol abstraction in a formula.
/// @tparam Trait Specify the algebraic trait of the symbol.
/// @tparam ID Should be ignored and not specified, it is used to define different unique types for
/// the Symbol.
export template<typename Trait = Uncostrained, auto ID = [] {}>
struct Symbol {
    // This variable is used as a unique id for comparison and ordering.
    static constexpr const void* address = std::addressof(ID);

    template<typename T>
        requires(Trait::template trait<std::remove_cvref_t<T>>::value)
    constexpr auto operator=(T&& value) -> SymbolBinder<Symbol, T&&> {
        return SymbolBinder{*this, std::forward<T>(value)};
    }
};

export template<typename Tlhs, auto Lhs, typename Trhs, auto Rhs>
constexpr auto operator<=>(Symbol<Tlhs, Lhs>, Symbol<Trhs, Rhs>) -> std::strong_ordering {
    return std::compare_three_way{}(Symbol<Tlhs, Lhs>::address, Symbol<Trhs, Rhs>::address);
}

} // namespace tars
