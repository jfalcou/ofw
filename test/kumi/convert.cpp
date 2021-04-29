//==================================================================================================
/**
  RABERU - Fancy Parameters Library
  Copyright : RABERU Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#define TTS_MAIN
#include <array>
#include <kumi.hpp>
#include <tts/tts.hpp>
#include <string>

TTS_CASE("Check tuple to tuple conversion")
{
  kumi::tuple in{short{49},62.5f};

  TTS_EQUAL ( (kumi::tuple<int ,double>(in)), (kumi::tuple{49 ,62.5}) );
  TTS_EQUAL ( (kumi::tuple<char,int>(in))   , (kumi::tuple{'1',62})   );

  TTS_EQUAL ( kumi::tuple<std::string>(kumi::tuple{"some text"})
            , kumi::tuple{std::string("some text")}
            );
}

TTS_CASE("Check tuple to tuple constexpr conversion")
{
  constexpr kumi::tuple in{short{49},62.5f};

  TTS_CONSTEXPR_EQUAL ( (kumi::tuple<int ,double>(in)), (kumi::tuple{49 ,62.5}) );
  TTS_CONSTEXPR_EQUAL ( (kumi::tuple<char,int>(in))   , (kumi::tuple{'1',62})   );
}

struct my_struct
{
  std::size_t n;
  double      data;
  constexpr auto operator<=>(my_struct const&) const = default;
};

TTS_CASE("Check tuple to constructible type conversion")
{
  kumi::tuple in{std::size_t{9}, 13.37};

  TTS_EQUAL ( my_struct(in), (my_struct{9,13.37}) );
}

TTS_CASE("Check tuple to constructible type constexpr conversion")
{
  constexpr kumi::tuple in{std::size_t{9}, 13.37};

  TTS_CONSTEXPR_EQUAL ( my_struct(in), (my_struct{9,13.37}) );
}
