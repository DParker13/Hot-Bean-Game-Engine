/**
 * @file type_traits.hpp
 * @author Daniel Parker (DParker13)
 * @brief Custom type traits for HotBeanEngine.
 * @version 0.1
 * @date 2025-10-20
 * 
 * @copyright Copyright (c) 2025
 */

#pragma once

/// @brief Checks if a type has a static GetName() function.
/// @tparam T The type to check.
template<typename T>
class has_static_get_name {
private:
    template<typename U>
    static auto test(int) -> decltype(U::StaticGetName(), std::true_type{});
    template<typename>
    static std::false_type test(...);
public:
    static constexpr bool value = decltype(test<T>(0))::value;
};