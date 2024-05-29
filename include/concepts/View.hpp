#ifndef KOKKOS_UTILS_CONCEPTS_VIEW_HPP
#define KOKKOS_UTILS_CONCEPTS_VIEW_HPP

#include "Kokkos_View.hpp"

namespace concepts
{

//! Concept to specify that a type is a @c Kokkos::View.
template <typename T>
concept View = Kokkos::is_view_v<T>;

} // namespace concepts

#endif // KOKKOS_UTILS_CONCEPTS_VIEW_HPP