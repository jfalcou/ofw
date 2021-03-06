//==================================================================================================
/**
  RABERU - Fancy Parameters Library
  Copyright : RABERU Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#define TTS_MAIN
#include "common.hpp"
#include <raberu.hpp>
#include <tts/tts.hpp>

TTS_CASE("Check settings(...).contains behavior")
{
  using namespace std::literals;
  using namespace rbr::literals;

  rbr::settings values( custom_ = foo {}, "surname"_kw = "john"s, value_ = 3.f
                      , "aligned"_fl, is_transparent_
                      );

  TTS_EXPECT(values.contains(custom_)         );
  TTS_EXPECT(values.contains("surname"_kw)    );
  TTS_EXPECT(values.contains(value_)          );
  TTS_EXPECT(values.contains(is_transparent_) );
  TTS_EXPECT(values.contains("aligned"_fl) );

  TTS_EXPECT_NOT(values.contains(rbr::keyword<char>   ));
  TTS_EXPECT_NOT(values.contains(rbr::keyword<short>  ));
  TTS_EXPECT_NOT(values.contains(rbr::keyword<void *> ));
  TTS_EXPECT_NOT(values.contains(is_modal_            ));
  TTS_EXPECT_NOT(values.contains("compact"_fl         ));
};

TTS_CASE("Check settings(...).contains constexpr behavior")
{
  using namespace std::literals;
  using namespace rbr::literals;

  constexpr rbr::settings values("custom"_kw = foo {}, name_ = 88, value_ = 3.f, is_modal_);

  TTS_CONSTEXPR_EXPECT(values.contains("custom"_kw) );
  TTS_CONSTEXPR_EXPECT(values.contains(name_  )     );
  TTS_CONSTEXPR_EXPECT(values.contains(value_ )     );
  TTS_CONSTEXPR_EXPECT(values.contains(is_modal_)   );

  TTS_CONSTEXPR_EXPECT_NOT(values.contains(rbr::keyword<char> )   );
  TTS_CONSTEXPR_EXPECT_NOT(values.contains(rbr::keyword<short>)   );
  TTS_CONSTEXPR_EXPECT_NOT(values.contains(rbr::keyword<void *> ) );
  TTS_CONSTEXPR_EXPECT_NOT(values.contains(is_transparent_  )     );
};
