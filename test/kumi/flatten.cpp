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

TTS_CASE("Check tuple::flatten behavior")
{
  TTS_EQUAL((kumi::flatten(kumi::tuple {2., 1, short {55}})), (kumi::tuple {2., 1, short {55}}));
  TTS_EQUAL((kumi::flatten(kumi::tuple {3.25f, kumi::tuple {2., 1, short {55}}, 'z'})),
            (kumi::tuple {3.25f, 2., 1, short {55}, 'z'}));
  TTS_EQUAL((kumi::flatten(kumi::tuple {
                3.25f, kumi::tuple {2., kumi::tuple {2., 1, short {55}}, short {55}}, 'z'})),
            (kumi::tuple {3.25f, 2., kumi::tuple {2., 1, short {55}}, short {55}, 'z'}));
}

TTS_CASE("Check tuple::flatten constexpr behavior")
{
  constexpr auto t0 = kumi::tuple {2., 1, short {55}};
  constexpr auto t1 = kumi::tuple {3.25f, kumi::tuple {2., 1, short {55}}, 'z'};
  constexpr auto t2 =
      kumi::tuple {3.25f, kumi::tuple {2., kumi::tuple {2., 1, short {55}}, short {55}}, 'z'};

  TTS_CONSTEXPR_EQUAL(kumi::flatten(t0), (kumi::tuple {2., 1, short {55}}));
  TTS_CONSTEXPR_EQUAL(kumi::flatten(t1), (kumi::tuple {3.25f, 2., 1, short {55}, 'z'}));
  TTS_CONSTEXPR_EQUAL(kumi::flatten(t2),
                      (kumi::tuple {3.25f, 2., kumi::tuple {2., 1, short {55}}, short {55}, 'z'}));
}

TTS_CASE("Check tuple::flatten_all behavior")
{
  TTS_EQUAL((kumi::flatten_all(kumi::tuple {2., 1, short {55}})),
            (kumi::tuple {2., 1, short {55}}));
  TTS_EQUAL((kumi::flatten_all(kumi::tuple {3.25f, kumi::tuple {2., 1, short {55}}, 'z'})),
            (kumi::tuple {3.25f, 2., 1, short {55}, 'z'}));
  TTS_EQUAL((kumi::flatten_all(kumi::tuple {
                3.25f, kumi::tuple {2., kumi::tuple {2., 1, short {55}}, short {55}}, 'z'})),
            (kumi::tuple {3.25f, 2., 2., 1, short {55}, short {55}, 'z'}));
}

TTS_CASE("Check tuple::flatten_all constexpr behavior")
{
  constexpr auto t0 = kumi::tuple {2., 1, short {55}};
  constexpr auto t1 = kumi::tuple {3.25f, kumi::tuple {2., 1, short {55}}, 'z'};
  constexpr auto t2 = kumi::tuple {3.25f, t0, t1, 'z'};

  TTS_CONSTEXPR_EQUAL(kumi::flatten_all(t0), (kumi::tuple {2., 1, short {55}}));
  TTS_CONSTEXPR_EQUAL(kumi::flatten_all(t1), (kumi::tuple {3.25f, 2., 1, short {55}, 'z'}));
  TTS_CONSTEXPR_EQUAL(kumi::flatten_all(t2),
                      (kumi::tuple {3.25f, 2., 1, short {55}, 3.25f, 2., 1, short {55}, 'z', 'z'}));
}
