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

TTS_CASE("Check map(f, tuple) behavior")
{
  TTS_WHEN("Given a tuple t")
  {
    auto t = kumi::tuple {1, 2., 3.4f, '5'};

    TTS_AND_THEN(" - we call map(f,t)")
    {
      auto s = map([](auto m) { return sizeof(m); }, t);

      auto [s0, s1, s2, s3] = s;
      auto m0 = s0;
      auto m1 = s1;
      auto m2 = s2;
      auto m3 = s3;
      TTS_EQUAL(m0, sizeof(int));
      TTS_EQUAL(m1, sizeof(double));
      TTS_EQUAL(m2, sizeof(float));
      TTS_EQUAL(m3, sizeof(char));
    }

    TTS_AND_THEN(" - we call map(f,t,u)")
    {
      auto u = kumi::tuple {2, 3, 4, 5};
      auto s = map([](auto m, auto n) { return n * sizeof(m); }, t, u);

      auto [s0, s1, s2, s3] = s;
      auto m0 = s0;
      auto m1 = s1;
      auto m2 = s2;
      auto m3 = s3;
      TTS_EQUAL(m0, 2 * sizeof(int));
      TTS_EQUAL(m1, 3 * sizeof(double));
      TTS_EQUAL(m2, 4 * sizeof(float));
      TTS_EQUAL(m3, 5 * sizeof(char));
    }
  }
};

TTS_CASE("Check map(f, tuple) constexpr behavior")
{
  TTS_WHEN("Given a tuple t")
  {
    constexpr auto t = kumi::tuple {1, 2., 3.4f, '5'};

    TTS_AND_THEN(" - we call t.map(f)")
    {
      constexpr auto s = map([](auto m) { return sizeof(m); }, t);

      TTS_CONSTEXPR_EQUAL(get<0>(s), sizeof(int));
      TTS_CONSTEXPR_EQUAL(get<1>(s), sizeof(double));
      TTS_CONSTEXPR_EQUAL(get<2>(s), sizeof(float));
      TTS_CONSTEXPR_EQUAL(get<3>(s), sizeof(char));
    }

    TTS_AND_THEN(" - we call t.map(f,u)")
    {
      constexpr auto u = kumi::tuple {2, 3, 4, 5};
      constexpr auto s = map([](auto m, auto n) { return n * sizeof(m); }, t, u);

      TTS_CONSTEXPR_EQUAL(get<0>(s), 2 * sizeof(int));
      TTS_CONSTEXPR_EQUAL(get<1>(s), 3 * sizeof(double));
      TTS_CONSTEXPR_EQUAL(get<2>(s), 4 * sizeof(float));
      TTS_CONSTEXPR_EQUAL(get<3>(s), 5 * sizeof(char));
    }
  }
};
