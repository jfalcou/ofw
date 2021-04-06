//==================================================================================================
/**
  RABERU - Fancy Parameters Library
  Copyright : RABERU Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#define TTS_MAIN
#include <tts/tts.hpp>
#include <kumi.hpp>

TTS_CASE("Check for_each behavior")
{
  auto t = kumi::tuple{1,2.,3.4f,'5'};

  t.for_each( [](auto& m) { m++; });

  auto[i,d,f,c] = t;
  TTS_EQUAL(i, 2);
  TTS_EQUAL(d, 3.);
  TTS_EQUAL(f, 4.4f);
  TTS_EQUAL(c, '6');
}

TTS_CASE("Check for_each constexpr behavior")
{
  constexpr auto t = kumi::tuple{1,2.,3.4f,'5'}.for_each( [](auto& m) { m++; });

  TTS_CONSTEXPR_EQUAL(get<0>(t), 2);
  TTS_CONSTEXPR_EQUAL(get<1>(t), 3.);
  TTS_CONSTEXPR_EQUAL(get<2>(t), 4.4f);
  TTS_CONSTEXPR_EQUAL(get<3>(t), '6');
}

TTS_CASE("Check for_each behavior as continuation")
{
  auto t = kumi::tuple{1,2.,3.4f,'5'};

  t.for_each( [](auto& m) { m++; })
   .for_each( [](auto& m) { m *= 2; });

  auto[i,d,f,c] = t;
  TTS_EQUAL(i, 4);
  TTS_EQUAL(d, 6.);
  TTS_EQUAL(f, 8.8f);
  TTS_EQUAL(c, 'l');
}

TTS_CASE("Check for_each constexpr behavior as continuation")
{
  constexpr auto t = kumi::tuple{1,2.,3.4f,'5'}
                                .for_each( [](auto& m) { m++;    })
                                .for_each( [](auto& m) { m *= 2; });

  TTS_CONSTEXPR_EQUAL(get<0>(t), 4);
  TTS_CONSTEXPR_EQUAL(get<1>(t), 6.);
  TTS_CONSTEXPR_EQUAL(get<2>(t), 8.8f);
  TTS_CONSTEXPR_EQUAL(get<3>(t), 'l');
}
