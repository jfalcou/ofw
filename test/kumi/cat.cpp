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

TTS_CASE("Check cat(tuple) behavior")
{
  short s = 55;
  TTS_EQUAL((cat(kumi::tuple {}, kumi::tuple {1, 2.})), (kumi::tuple {1, 2.}));
  TTS_EQUAL((cat(kumi::tuple {1}, kumi::tuple {2., 3.f, 4})), (kumi::tuple {1, 2., 3.f, 4}));
  TTS_EQUAL((cat(kumi::tuple {1, 2.}, kumi::tuple {3.f, 4})), (kumi::tuple {1, 2., 3.f, 4}));
  TTS_EQUAL((cat(kumi::tuple {1, 2.}, kumi::tuple {3.f, 4}, kumi::tuple {s, 6.7})),
            (kumi::tuple {1, 2., 3.f, 4, s, 6.7}));
}

TTS_CASE("Check cat(tuple) constexpr behavior")
{
  constexpr short s = 55;
  TTS_CONSTEXPR_EQUAL((cat(kumi::tuple {}, kumi::tuple {1, 2.})), (kumi::tuple {1, 2.}));
  TTS_CONSTEXPR_EQUAL((cat(kumi::tuple {1}, kumi::tuple {2., 3.f, 4})),
                      (kumi::tuple {1, 2., 3.f, 4}));
  TTS_CONSTEXPR_EQUAL((cat(kumi::tuple {1, 2.}, kumi::tuple {3.f, 4})),
                      (kumi::tuple {1, 2., 3.f, 4}));
  TTS_CONSTEXPR_EQUAL((cat(kumi::tuple {1, 2.}, kumi::tuple {3.f, 4}, kumi::tuple {s, 6.7})),
                      (kumi::tuple {1, 2., 3.f, 4, s, 6.7}));
}

TTS_CASE("Check t0 | ... | tn behavior")
{
  short s = 55;
  TTS_EQUAL((kumi::tuple {} | kumi::tuple {1, 2.}), (kumi::tuple {1, 2.}));
  TTS_EQUAL((kumi::tuple {1} | kumi::tuple {2., 3.f, 4}), (kumi::tuple {1, 2., 3.f, 4}));
  TTS_EQUAL((kumi::tuple {1, 2.} | kumi::tuple {3.f, 4}), (kumi::tuple {1, 2., 3.f, 4}));
  TTS_EQUAL((kumi::tuple {1, 2.} | kumi::tuple {3.f, 4} | kumi::tuple {s, 6.7}),
            (kumi::tuple {1, 2., 3.f, 4, s, 6.7}));
}

TTS_CASE("Check t0 | ... | tn constexpr behavior")
{
  constexpr short s = 55;
  TTS_CONSTEXPR_EQUAL((kumi::tuple {} | kumi::tuple {1, 2.}), (kumi::tuple {1, 2.}));
  TTS_CONSTEXPR_EQUAL((kumi::tuple {1} | kumi::tuple {2., 3.f, 4}), (kumi::tuple {1, 2., 3.f, 4}));
  TTS_CONSTEXPR_EQUAL((kumi::tuple {1, 2.} | kumi::tuple {3.f, 4}), (kumi::tuple {1, 2., 3.f, 4}));
  TTS_CONSTEXPR_EQUAL((kumi::tuple {1, 2.} | kumi::tuple {3.f, 4} | kumi::tuple {s, 6.7}),
                      (kumi::tuple {1, 2., 3.f, 4, s, 6.7}));
}
