//==================================================================================================
/**
  Random tools
  Copyright : OFW Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <type_traits>

#define static_warning(Condition, Message)                                                          \
static_assert ([] () {                                                                              \
  struct warn                                                                                       \
  {                                                                                                 \
    [[deprecated ("\n*** WARNING ***\n" Message "\n*** WARNING ***\n")]]                            \
    constexpr bool f ( ::std::false_type) { return true; }                                          \
    constexpr bool f ( ::std::true_type)  { return true; }                                          \
  };                                                                                                \
  return warn{}.f(std::bool_constant<(Condition)>{});                                               \
}())                                                                                                \
/**/
