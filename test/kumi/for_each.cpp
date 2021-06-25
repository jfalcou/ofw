//==================================================================================================
/**
  KUMI - Compact Tuple Tools
  Copyright : KUMI Contributors & Maintainers
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

  kumi::for_each([](auto &m, auto n) { m *= n; }, t, t);

  auto [i2, d2, f2, c2] = t;
  TTS_EQUAL(i2, 4);
  TTS_EQUAL(d2, 9.);
  TTS_EQUAL(f2, 19.36f);
  TTS_EQUAL(c2, 'd');
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

  constexpr auto t2 = []() {
    auto it = kumi::tuple {1, 2., 3.4f, '6'};
    kumi::for_each([](auto &m, auto n) { m *= n; }, it, it);
    return it;
  }();

  TTS_CONSTEXPR_EQUAL(get<0>(t2), 1);
  TTS_CONSTEXPR_EQUAL(get<1>(t2), 4.);
  TTS_CONSTEXPR_EQUAL(get<2>(t2), 11.56f);
  TTS_CONSTEXPR_EQUAL(get<3>(t2), 'd');
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

  kumi::for_each_index(
      [](auto i, auto &m, auto n) {
        if constexpr( i % 2 == 0 )
          m *= n;
        else
          m += n;
      },
      t, t);

  auto [i2, d2, f2, c2] = t;
  TTS_EQUAL(i2, 4);
  TTS_EQUAL(d2, 2.);
  TTS_EQUAL(f2, 19.36f);
  TTS_EQUAL(c2, 'h');
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

  constexpr auto t2 = []() {
    auto it = kumi::tuple {1, 2., 3.4f, '5'};
    kumi::for_each_index(
        [](auto i, auto &m, auto n) {
          if constexpr( i % 2 == 0 )
            m *= n;
          else
            m +=n;
        },
        it, it);
    return it;
  }();

  TTS_CONSTEXPR_EQUAL(get<0>(t2), 1);
  TTS_CONSTEXPR_EQUAL(get<1>(t2), 4.);
  TTS_CONSTEXPR_EQUAL(get<2>(t2), 11.56f);
  TTS_CONSTEXPR_EQUAL(get<3>(t2), 'j');
}
