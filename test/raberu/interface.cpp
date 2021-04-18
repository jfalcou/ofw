//==================================================================================================
/**
  RABERU - Fancy Parameters Library
  Copyright : RABERU Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#define TTS_MAIN
#include "common.hpp"
#include <raberu.hpp>
#include <tts/tts.hpp>

template<typename... Vs>
constexpr auto
typed_interface(Vs const &...vs) noexcept
{
  rbr::settings s(vs...);
  return s[rbr::keyword<int>] * s[rbr::keyword<double>];
}

constexpr auto
named_interface(rbr::keyword_parameter auto const &...vs) noexcept
{
  rbr::settings s(vs...);
  return s[factor_] * s[ref_];
}

TTS_CASE("Check settings(...) as function interface with simple parameters")
{
  TTS_EQUAL(typed_interface(10, 3.41), 34.1);
  TTS_EQUAL(typed_interface(3.41, 10), 34.1);
}

TTS_CASE("Check settings(...) as function interface with named parameters")
{
  TTS_EQUAL(named_interface(factor_ = 10, ref_ = 3.41), 34.1);
  TTS_EQUAL(named_interface(ref_ = 3.41, factor_ = 10), 34.1);
}

TTS_CASE("Check settings(...) as constexpr function interface with simple parameters")
{
  TTS_CONSTEXPR_EQUAL(typed_interface(10, 3.41), 34.1);
  TTS_CONSTEXPR_EQUAL(typed_interface(3.41, 10), 34.1);
}

TTS_CASE("Check settings(...) as constexpr function interface with named parameters")
{
  TTS_CONSTEXPR_EQUAL(named_interface(factor_ = 10, ref_ = 3.41), 34.1);
  TTS_CONSTEXPR_EQUAL(named_interface(ref_ = 3.41, factor_ = 10), 34.1);
}
