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

TTS_CASE("Check merge behavior: large defaults, few options")
{
  using namespace std::literals;

  auto defaults = rbr::settings(coord_ = "Jane Doe"s, factor_ = 42.69f, is_modal_);
  auto opts     = rbr::settings(factor_ = 9567);

  auto merged = rbr::merge(opts, defaults);

  TTS_EQUAL(merged[factor_]   , 9567        );
  TTS_EQUAL(merged[coord_]    , "Jane Doe"s );
  TTS_EQUAL(merged[is_modal_] , true        );

  auto nopts     = rbr::settings(value_ = 9567);

  auto merged2 = rbr::merge(nopts, defaults);

  TTS_EQUAL(merged2[value_]    , 9567        );
  TTS_EQUAL(merged2[factor_]   , 42.69f      );
  TTS_EQUAL(merged2[coord_]    , "Jane Doe"s );
  TTS_EQUAL(merged2[is_modal_] , true        );
};

TTS_CASE("Check merge behavior: few defaults, large options")
{
  using namespace std::literals;

  auto opts     = rbr::settings(coord_ = "Jane Doe"s, factor_ = 42.69f, is_modal_);
  auto defaults = rbr::settings(factor_ = 9567);

  auto merged = rbr::merge(opts, defaults);

  TTS_EQUAL(merged[factor_]   , 42.69f      );
  TTS_EQUAL(merged[coord_]    , "Jane Doe"s );
  TTS_EQUAL(merged[is_modal_] , true        );

  auto nopts     = rbr::settings(coord_ = "Jane Doe"s, value_ = 13.37, is_modal_);

  auto merged2 = rbr::merge(nopts, defaults);

  TTS_EQUAL(merged2[factor_]   , 9567        );
  TTS_EQUAL(merged2[value_]    , 13.37       );
  TTS_EQUAL(merged2[coord_]    , "Jane Doe"s );
  TTS_EQUAL(merged2[is_modal_] , true        );
};
