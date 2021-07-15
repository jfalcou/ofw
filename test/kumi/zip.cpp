//==================================================================================================
/**
  KUMI - Compact Tuple Tools
  Copyright : KUMI Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#define TTS_MAIN
#include <array>
#include <kumi.hpp>
#include <tts/tts.hpp>
#include <vector>

TTS_CASE("Check tuple::zip behavior")
{
  using kumi::tuple;

  auto numbers = tuple {1, 2, 3, 4};
  auto letters = tuple {'a', 'b', 'c', 'd'};
  auto ratio   = tuple {1.f, 0.5f, 0.25, 0.01};

  TTS_EQUAL((kumi::zip(numbers, letters)),
            (tuple {tuple {1, 'a'}, tuple {2, 'b'}, tuple {3, 'c'}, tuple {4, 'd'}}));

  TTS_EQUAL(
      (kumi::zip(numbers, letters, ratio)),
      (tuple {
          tuple {1, 'a', 1.f}, tuple {2, 'b', 0.5f}, tuple {3, 'c', 0.25}, tuple {4, 'd', 0.01}}));
};

TTS_CASE("Check tuple::zip constexpr behavior")
{
  using kumi::tuple;

  constexpr auto numbers = tuple {1, 2, 3, 4};
  constexpr auto letters = tuple {'a', 'b', 'c', 'd'};
  constexpr auto ratio   = tuple {1.f, 0.5f, 0.25, 0.01};

  TTS_CONSTEXPR_EQUAL((kumi::zip(numbers, letters)),
                      (tuple {tuple {1, 'a'}, tuple {2, 'b'}, tuple {3, 'c'}, tuple {4, 'd'}}));

  TTS_CONSTEXPR_EQUAL(
      (kumi::zip(numbers, letters, ratio)),
      (tuple {
          tuple {1, 'a', 1.f}, tuple {2, 'b', 0.5f}, tuple {3, 'c', 0.25}, tuple {4, 'd', 0.01}}));
};
