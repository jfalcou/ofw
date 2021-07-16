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

TTS_CASE("Check settings(...) size")
{
  using namespace std::literals;
  using namespace rbr::literals;

  TTS_EQUAL(rbr::settings("custom"_kw = foo {}).size(), 1);
  TTS_EQUAL(rbr::settings("custom"_kw = foo {}, "border"_fl).size(), 2);
  TTS_EQUAL(rbr::settings("custom"_kw = foo {}, "name"_kw = "john"s, "border"_fl).size(), 3);

  std::cout << rbr::settings("custom"_kw = foo {}, unroll<8>, "border"_fl) << "\n";
};

TTS_CASE("Check settings(...) constexpr size - named parameters")
{
  using namespace std::literals;
  using namespace rbr::literals;

  TTS_CONSTEXPR_EQUAL(rbr::settings("custom"_kw = foo{}).size(), 1);
  TTS_CONSTEXPR_EQUAL(rbr::settings("custom"_kw = foo{}, "value"_kw = 3.f).size(), 2);
  TTS_CONSTEXPR_EQUAL(rbr::settings("custom"_kw = foo{}, "coord"_kw = point{}, "value"_kw = 3.f).size(), 3);
};
