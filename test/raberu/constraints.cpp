//==================================================================================================
/**
  RABERU - Fancy Parameters Library
  Copyright : RABERU Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#define TTS_MAIN
#include <raberu.hpp>
#include <tts/tts.hpp>
#include <type_traits>

struct real_type
{
  template<typename T> struct check : std::is_floating_point<T> {};
};

struct small_type
{
  template<typename T> struct check : std::bool_constant<(sizeof(T) < 4)> {};
};

inline constexpr auto angle   = rbr::keyword<struct angle   , real_type >;
inline constexpr auto pattern = rbr::keyword<struct pattern , small_type>;

TTS_CASE("Check constrainted keyword::operator= behavior")
{
  rbr::settings s( angle = 3., pattern = 'z');

  TTS_EQUAL( s[angle]   , 3.  );
  TTS_EQUAL( s[pattern] , 'z' );
}
