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
  TTS_EQUAL ( (kumi::tuple{1,'5',"things"}
                    .apply( [](auto... m)
                            {
                              std::ostringstream s;
                              ((s << m << " "),...);
                              return s.str();
                            }
                          )
              )
            , "1 5 things "
            );
}

TTS_CASE("Check apply constexpr behavior")
{
  TTS_CONSTEXPR_EQUAL ( (kumi::tuple{1,2.3,4.5f,}.apply( [](auto... m) { return (m + ...); }))
                      , 7.8
                      );
}
