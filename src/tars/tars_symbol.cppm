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

namespace tars {

/// @brief Define the Symbol class, the atom of a formula.
/// This class defines the core type representing a symbol abstraction in a formula.
/// @tparam Should be ignored and not specified, it is used to define different unique types for the
/// Symbol.
export template<auto = [] {}>
struct Symbol {};

} // namespace tars
