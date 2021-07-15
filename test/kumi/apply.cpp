//==================================================================================================
/**
  KUMI - Compact Tuple Tools
  Copyright : KUMI Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#define TTS_MAIN
#include <kumi.hpp>
#include <sstream>
#include <tts/tts.hpp>

TTS_CASE("Check apply behavior")
{
  TTS_EQUAL((kumi::apply(
                [](auto... m) {
                  std::ostringstream s;
                  ((s << m << " "), ...);
                  return s.str();
                },
                kumi::tuple {1, '5', "things"})),
            "1 5 things ");

  kumi::tuple some_tuple {1, '5', "things"};

  TTS_EQUAL((some_tuple([](auto... m) {
              std::ostringstream s;
              ((s << m << " "), ...);
              return s.str();
            })),
            "1 5 things ");
};

TTS_CASE("Check apply constexpr behavior")
{
  constexpr auto t1 = []() {
    auto it = kumi::tuple {1, 2., 3.f};
    return kumi::apply([](auto... m) { return (m + ...); }, it);
  }();

  constexpr auto t2 = []() {
    auto it = kumi::tuple {1, 2., 3.f};
    return it([](auto... m) { return (m + ...); });
  }();

  TTS_CONSTEXPR_EQUAL(t1, 6.);
  TTS_CONSTEXPR_EQUAL(t2, 6.);
};
