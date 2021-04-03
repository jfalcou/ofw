//==================================================================================================
/**
  RABERU - Fancy Parameters Library
  Copyright : RABERU Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#define TTS_MAIN
#include <tts/tts.hpp>
#include <raberu.hpp>
#include "common.hpp"

TTS_CASE("Check settings(...).contains behavior")
{
  using namespace std::literals;

  rbr::settings values(custom_ = foo{}, name_ = "john"s, value_ = 3.f);

  TTS_EXPECT    ( values.contains(custom_)            );
  TTS_EXPECT    ( values.contains(name_)              );
  TTS_EXPECT    ( values.contains(value_)             );
  TTS_EXPECT_NOT( values.contains(rbr::keyword<char>) );
  TTS_EXPECT_NOT( values.contains(rbr::keyword<short>));
  TTS_EXPECT_NOT( values.contains(rbr::keyword<void*>));
}

TTS_CASE("Check settings(...).contains constexpr behavior")
{
  using namespace std::literals;
  using namespace rbr::literal;

  constexpr rbr::settings values("custom"_kw = foo{}, name_ = 88, value_ = 3.f);

  TTS_CONSTEXPR_EXPECT( values.contains("custom"_kw));
  TTS_CONSTEXPR_EXPECT( values.contains(name_)      );
  TTS_CONSTEXPR_EXPECT( values.contains(value_)     );

  TTS_CONSTEXPR_EXPECT_NOT( values.contains(rbr::keyword<char>) );
  TTS_CONSTEXPR_EXPECT_NOT( values.contains(rbr::keyword<short>));
  TTS_CONSTEXPR_EXPECT_NOT( values.contains(rbr::keyword<void*>));
}
