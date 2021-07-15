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

TTS_CASE("Check rbr::keyword_parameters concept")
{
  using namespace rbr::literals;

  auto param = (coord_ = 9);

  TTS_EXPECT( rbr::keyword_parameter<decltype(param             )> );
  TTS_EXPECT( rbr::keyword_parameter<decltype("local"_kw = 6.34f)> );
  TTS_EXPECT_NOT( rbr::keyword_parameter<decltype("local"_kw)> );
  TTS_EXPECT_NOT( rbr::keyword_parameter<float**> );
};

TTS_CASE("Check rbr::exactly concept")
{
  using namespace rbr::literals;

  auto param = (coord_ = 9);

  TTS_EXPECT( (rbr::exactly<decltype(param)              , coord_    >) );
  TTS_EXPECT( (rbr::exactly<decltype("local"_kw = 6.34f) , "local"_kw>) );
  TTS_EXPECT_NOT( (rbr::exactly<decltype("local"_kw = 77), coord_    >) );
};
