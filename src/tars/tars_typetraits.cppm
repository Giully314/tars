// tars/tars_typetraits.cppm
// PURPOSE: Define custom type traits.
//
// DESCRIPTION:
//

export module tars.type_traits;

import std;

export namespace tars {
template <typename T>
struct remove_lvalue_reference: std::type_identity<T> {};

template <typename T>
    requires std::is_lvalue_reference_v<T>
struct remove_lvalue_reference<T>: std::type_identity<std::remove_reference_t<T>> {};

template <typename T>
using remove_lvalue_reference_t = remove_lvalue_reference<T>::type;

template <typename T>
struct remove_rvalue_reference: std::type_identity<T> {};

template <typename T>
    requires std::is_rvalue_reference_v<T>
struct remove_rvalue_reference<T>: std::type_identity<std::remove_reference_t<T>> {};

template <typename T>
using remove_rvalue_reference_t = remove_rvalue_reference<T>::type;

template <typename T>
struct requalify_as_const
    : std::conditional<std::is_lvalue_reference_v<T>,
                       std::add_lvalue_reference_t<std::add_const_t<std::remove_reference_t<T>>>,
                       std::conditional_t<std::is_rvalue_reference_v<T>,
                                          std::add_rvalue_reference_t<
                                              std::add_const_t<std::remove_reference_t<T>>>,
                                          std::add_const_t<T>>> {};

template <typename T>
using requalify_as_const_t = requalify_as_const<T>::type;

template <typename T>
struct requalify_as_volatile
    : std::conditional<std::is_lvalue_reference_v<T>,
                       std::add_lvalue_reference_t<std::add_volatile_t<std::remove_reference_t<T>>>,
                       std::conditional_t<std::is_rvalue_reference_v<T>,
                                          std::add_rvalue_reference_t<
                                              std::add_volatile_t<std::remove_reference_t<T>>>,
                                          std::add_volatile_t<T>>> {};

template <typename T>
using requalify_as_volatile_t = requalify_as_volatile<T>::type;

template <typename T>
struct requalify_as_cv
    : std::conditional<
          std::is_lvalue_reference_v<T>,
          std::add_lvalue_reference_t<std::add_cv_t<std::remove_reference_t<T>>>,
          std::conditional_t<std::is_rvalue_reference_v<T>,
                             std::add_rvalue_reference_t<std::add_cv_t<std::remove_reference_t<T>>>,
                             std::add_cv_t<T>>> {};

template <typename T>
using requalify_as_cv_t = requalify_as_cv<T>::type;

} // namespace tars
