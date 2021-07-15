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

TTS_CASE("Check settings(...) size - simple parameters")
{
  TTS_EQUAL(rbr::settings().size(), 0);
  TTS_EQUAL(rbr::settings(1).size(), 1);
  TTS_EQUAL(rbr::settings(2, 1.f).size(), 2);
  TTS_EQUAL(rbr::settings("3", 2, 1.f).size(), 3);
};

TTS_CASE("Check settings(...) size - named parameters")
{
  using namespace std::literals;
  using namespace rbr::literals;

  TTS_EQUAL(rbr::settings(custom_ = foo {}).size(), 1);
  TTS_EQUAL(rbr::settings(custom_ = foo {}, value_ = 3.f).size(), 2);
  TTS_EQUAL(rbr::settings(custom_ = foo {}, name_ = "john"s, value_ = 3.f).size(), 3);

  TTS_EQUAL(rbr::settings("custom"_kw = foo {}).size(), 1);
  TTS_EQUAL(rbr::settings("custom"_kw = foo {}, "value"_kw = 3.f).size(), 2);
  TTS_EQUAL(rbr::settings("custom"_kw = foo {}, "name"_kw = "john"s, "value"_kw = 3.f).size(), 3);
};

TTS_CASE("Check settings(...) constexpr size - simple parameters")
{
  TTS_CONSTEXPR_EQUAL(rbr::settings().size(), 0);
  TTS_CONSTEXPR_EQUAL(rbr::settings(1).size(), 1);
  TTS_CONSTEXPR_EQUAL(rbr::settings(2, 1.f).size(), 2);
  TTS_CONSTEXPR_EQUAL(rbr::settings("3", 2, 1.f).size(), 3);
};

TTS_CASE("Check settings(...) constexpr size - named parameters")
{
  using namespace std::literals;
  using namespace rbr::literals;

  TTS_CONSTEXPR_EQUAL(rbr::settings(custom_ = foo {}).size(), 1);
  TTS_CONSTEXPR_EQUAL(rbr::settings(custom_ = foo {}, value_ = 3.f).size(), 2);
  TTS_CONSTEXPR_EQUAL(rbr::settings(custom_ = foo {}, coord_ = point {}, value_ = 3.f).size(), 3);

  TTS_CONSTEXPR_EQUAL(rbr::settings("custom"_kw = foo {}).size(), 1);
  TTS_CONSTEXPR_EQUAL(rbr::settings("custom"_kw = foo {}, "value"_kw = 3.f).size(), 2);
  TTS_CONSTEXPR_EQUAL(
      rbr::settings("custom"_kw = foo {}, "coord"_kw = point {}, "value"_kw = 3.f).size(), 3);
};
