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

constexpr auto
named_interface(rbr::concepts::option auto const &...vs) noexcept
{
  rbr::settings s(vs...);
  return s["level"_kw] * s[value_];
}

template<rbr::concepts::option... Vs>
constexpr auto filtered_interface(Vs const &...vs) noexcept
requires( rbr::settings<Vs...>::contains_any("level"_kw, value_) )
{
  rbr::settings s(vs...);
  return s["level"_kw] * s[value_];
}

template<rbr::concepts::option... Vs>
constexpr auto restricted_interface(Vs const &...vs) noexcept
requires( rbr::settings<Vs...>::contains_only("level"_kw, value_) )
{
  rbr::settings s(vs...);
  return s["level"_kw] * s[value_];
}

TTS_CASE("Check settings(...) as function interface with named parameters")
{
  TTS_EQUAL(named_interface("level"_kw = 10, value_ = 3.4f), 34.f);
  TTS_EQUAL(named_interface(value_ = 3.4f, "level"_kw = 10), 34.f);
};

TTS_CASE("Check settings(...) as constexpr function interface with named parameters")
{
  TTS_CONSTEXPR_EQUAL(named_interface("level"_kw = 10, value_ = 3.4f), 34.f);
  TTS_CONSTEXPR_EQUAL(named_interface(value_ = 3.4f, "level"_kw = 10), 34.f);
};

TTS_CASE("Check settings(...) as function interface with filtered named parameters")
{
  TTS_EQUAL(filtered_interface("level"_kw = 10, value_ = 3.4f), 34.f);
  TTS_EQUAL(filtered_interface(value_ = 3.4f, "level"_kw = 10), 34.f);
  TTS_EQUAL(filtered_interface("level"_kw = 10, value_ = 3.4f, is_modal_), 34.f);
  TTS_EQUAL(filtered_interface("level"_kw = 10, is_modal_, value_ = 3.4f), 34.f);
};

TTS_CASE("Check settings(...) as constexpr function interface with filtered named parameters")
{
  TTS_CONSTEXPR_EQUAL(filtered_interface("level"_kw = 10, value_ = 3.4f), 34.f);
  TTS_CONSTEXPR_EQUAL(filtered_interface(value_ = 3.4f, "level"_kw = 10), 34.f);
  TTS_CONSTEXPR_EQUAL(filtered_interface("level"_kw = 10, value_ = 3.4f, is_modal_), 34.f);
  TTS_CONSTEXPR_EQUAL(filtered_interface("level"_kw = 10, is_modal_, value_ = 3.4f), 34.f);
};

TTS_CASE("Check settings(...) as function interface with restricted named parameters")
{
  TTS_EQUAL(restricted_interface("level"_kw = 10, value_ = 3.4f), 34.f);
  TTS_EQUAL(restricted_interface(value_ = 3.4f, "level"_kw = 10), 34.f);
};

TTS_CASE("Check settings(...) as constexpr function interface with restricted named parameters")
{
  TTS_CONSTEXPR_EQUAL(restricted_interface("level"_kw = 10, value_ = 3.4f), 34.f);
  TTS_CONSTEXPR_EQUAL(restricted_interface(value_ = 3.4f, "level"_kw = 10), 34.f);
};
