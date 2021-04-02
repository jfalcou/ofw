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
#include <string>

TTS_CASE("Check tuple::cat behavior")
{
  short s = 55;
  TTS_EQUAL ( (kumi::tuple{     }.cat(kumi::tuple{1,2.})    ) , (kumi::tuple{1,2.})       );
  TTS_EQUAL ( (kumi::tuple{1    }.cat(kumi::tuple{2.,3.f,4})) , (kumi::tuple{1,2.,3.f,4}) );
  TTS_EQUAL ( (kumi::tuple{1,2. }.cat(kumi::tuple{3.f,4})   ) , (kumi::tuple{1,2.,3.f,4}) );
  TTS_EQUAL ( (kumi::tuple{1,2. }.cat( kumi::tuple{3.f,4}
                                     , kumi::tuple{s,6.7}
                                     )
              )                                               , (kumi::tuple{1,2.,3.f,4,s,6.7})
            );
}

TTS_CASE("Check cat(tuple) behavior")
{
  short s = 55;
  TTS_EQUAL ( cat(kumi::tuple{     }, kumi::tuple{1,2.})    ) , (kumi::tuple{1,2.})       );
  TTS_EQUAL ( cat(kumi::tuple{1    }, kumi::tuple{2.,3.f,4})) , (kumi::tuple{1,2.,3.f,4}) );
  TTS_EQUAL ( cat(kumi::tuple{1,2. }, kumi::tuple{3.f,4})   ) , (kumi::tuple{1,2.,3.f,4}) );
  TTS_EQUAL ( cat(kumi::tuple{1,2. }, kumi::tuple{3.f,4}, kumi::tuple{s,6.7}))
            , (kumi::tuple{1,2.,3.f,4,s,6.7})
            );
}

/*
  TTS_EQUAL( cat(t0,t1,t2)  , ref);
  TTS_EQUAL( (t0 | t1 | t2) , ref);

*/
