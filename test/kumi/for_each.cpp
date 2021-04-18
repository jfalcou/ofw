//==================================================================================================
/**
  RABERU - Fancy Parameters Library
  Copyright : RABERU Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#define TTS_MAIN
#include <kumi.hpp>
#include <tts/tts.hpp>

TTS_CASE("Check for_each behavior")
{
  auto t = kumi::tuple {1, 2., 3.4f, '5'};
  kumi::for_each([](auto &m) { m++; }, t);

  auto [i, d, f, c] = t;
  TTS_EQUAL(i, 2);
  TTS_EQUAL(d, 3.);
  TTS_EQUAL(f, 4.4f);
  TTS_EQUAL(c, '6');
}

TTS_CASE("Check for_each constexpr behavior")
{
  constexpr auto t = []() {
    auto it = kumi::tuple {1, 2., 3.4f, '5'};
    kumi::for_each([](auto &m) { m++; }, it);
    return it;
  }();

  TTS_CONSTEXPR_EQUAL(get<0>(t), 2);
  TTS_CONSTEXPR_EQUAL(get<1>(t), 3.);
  TTS_CONSTEXPR_EQUAL(get<2>(t), 4.4f);
  TTS_CONSTEXPR_EQUAL(get<3>(t), '6');
}

TTS_CASE("Check for_each_index behavior")
{
  auto t = kumi::tuple {1, 2., 3.4f, '5'};
  kumi::for_each_index(
      [](auto i, auto &m) {
        if constexpr( i % 2 == 0 )
          m++;
        else
          m--;
      },
      t);

  auto [i, d, f, c] = t;
  TTS_EQUAL(i, 2);
  TTS_EQUAL(d, 1.);
  TTS_EQUAL(f, 4.4f);
  TTS_EQUAL(c, '4');
}

TTS_CASE("Check for_each_index constexpr behavior")
{
  constexpr auto t = []() {
    auto it = kumi::tuple {1, 2., 3.4f, '5'};
    kumi::for_each_index(
        [](auto i, auto &m) {
          if constexpr( i % 2 == 0 )
            m++;
          else
            m--;
        },
        it);
    return it;
  }();

  TTS_CONSTEXPR_EQUAL(get<0>(t), 2);
  TTS_CONSTEXPR_EQUAL(get<1>(t), 1.);
  TTS_CONSTEXPR_EQUAL(get<2>(t), 4.4f);
  TTS_CONSTEXPR_EQUAL(get<3>(t), '4');
}
