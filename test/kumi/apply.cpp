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
#include <sstream>

TTS_CASE("Check apply behavior")
{
  TTS_EQUAL ( ( kumi::apply ( [](auto... m)
                              {
                                std::ostringstream s;
                                ((s << m << " "),...);
                                return s.str();
                              }
                            , kumi::tuple{1,'5',"things"}
                            )
              )
            , "1 5 things "
            );
}

TTS_CASE("Check apply constexpr behavior")
{
  constexpr auto t = []()
  {
    auto it = kumi::tuple{1,2.,3.f};
    return kumi::apply( [](auto... m) { return (m + ...); }, it);
  }();

  std::cout << t << "\n";
  TTS_CONSTEXPR_EQUAL(t, 6.);
}
