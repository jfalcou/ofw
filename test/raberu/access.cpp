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

TTS_CASE("Check settings(...) operator[t] behavior")
{
  using namespace std::literals;

  auto values = rbr::settings(coord_ = "Jane Doe"s, 42.69f, is_modal_);

  TTS_EQUAL(values[rbr::keyword<float>] , 42.69f      );
  TTS_EQUAL(values[coord_]              , "Jane Doe"s );
  TTS_EQUAL(values[is_modal_]           , true        );
  TTS_EQUAL(values[is_transparent_]     , false       );
}

TTS_CASE("Check settings(...) operator[t] life-time handling")
{
  using namespace std::literals;

  auto  s = "Jane Doe"s;
  float f = 42.69f;

  auto values = rbr::settings(coord_ = s, f);

  TTS_EQUAL(&values[rbr::keyword<float>], &f);
  TTS_EQUAL(&values[coord_], &s);
}

TTS_CASE("Check settings(...) operator[t] constexpr behavior")
{
  constexpr auto values = rbr::settings(coord_ = 75ULL, is_transparent_, 42.69f);

  TTS_CONSTEXPR_EQUAL(values[rbr::keyword<float>] , 42.69f);
  TTS_CONSTEXPR_EQUAL(values[coord_]              , 75ULL );
  TTS_CONSTEXPR_EQUAL(values[is_transparent_]     , true  );
  TTS_CONSTEXPR_EQUAL(values[is_modal_]           , false );
}

TTS_CASE("Check settings(...) operator[t | v] behavior")
{
  using namespace std::literals;
  using namespace rbr::literals;

  auto values = rbr::settings(name_ = "Jane Doe"s, "default_init"_fl);

  TTS_EQUAL(values[rbr::keyword<char> | -99], -99);
  TTS_EQUAL(values[rbr::keyword<int> | -99], -99);
  TTS_EQUAL(values[rbr::keyword<float> | -99], -99);
  TTS_EQUAL(values[name_ | -99], "Jane Doe"s);
  TTS_EQUAL(values["default_init"_fl | -99], true);
  TTS_EQUAL(values["perform_copy"_fl | -99], -99);
}

TTS_CASE("Check settings(...) operator[t | v] life-time handling")
{
  using namespace std::literals;

  auto  s   = "Jane Doe"s;
  auto  alt = "Bob Ross"s;
  float f   = 42.69f;

  auto values = rbr::settings(coord_ = s, f);

  TTS_EQUAL(&values[rbr::keyword<float> | 13.37f], &f);
  TTS_EQUAL(&values[coord_ | "test"s], &s);
  TTS_EQUAL(&values[name_ | alt], &alt);
}

TTS_CASE("Check settings(...) operator[t | v] constexpr behavior")
{
  using namespace rbr::literals;

  constexpr auto values = rbr::settings("default_init"_fl, coord_ = 75ULL);

  TTS_CONSTEXPR_EQUAL(values[rbr::keyword<char> | -99], -99);
  TTS_CONSTEXPR_EQUAL(values[rbr::keyword<int> | -99], -99);
  TTS_CONSTEXPR_EQUAL(values[rbr::keyword<float> | -99], -99);
  TTS_CONSTEXPR_EQUAL(values[coord_ | -99], 75ULL);
  TTS_CONSTEXPR_EQUAL(values["default_init"_fl | -99], true);
  TTS_CONSTEXPR_EQUAL(values["perform_copy"_fl | -99], -99);

}

TTS_CASE("Check settings(...) operator[t | func()] behavior")
{
  auto values  = rbr::settings(value_ = 1337.42f, is_modal_);
  auto or_else = []<typename T>(rbr::keyword_type<T>) { return sizeof(T); };

  TTS_EQUAL(values[rbr::keyword<char>   | or_else], 1ULL    );
  TTS_EQUAL(values[rbr::keyword<double> | or_else], 8ULL    );
  TTS_EQUAL(values[value_               | or_else], 1337.42f);

  TTS_EQUAL(values[coord_               | [](auto) { return 42ULL;  }], 42ULL   );
  TTS_EQUAL(values[is_modal_            | [](auto) { return 42ULL;  }], true    );
  TTS_EQUAL(values[is_transparent_      | [](auto) { return "oops"; }], "oops"  );
}

TTS_CASE("Check settings(...) operator[t | func()] constexpr behavior")
{
  constexpr auto values  = rbr::settings(is_modal_,value_ = 1337.42f);
  auto           or_else = []<typename T>(rbr::keyword_type<T>) { return 42.69; };
  auto           flag_it = []<typename T>(rbr::flag_type<T>) { return 42.69; };

  TTS_CONSTEXPR_EQUAL(values[rbr::keyword<char>   | or_else], 42.69   );
  TTS_CONSTEXPR_EQUAL(values[rbr::keyword<double> | or_else], 42.69   );
  TTS_CONSTEXPR_EQUAL(values[value_               | or_else], 1337.42f);
  TTS_CONSTEXPR_EQUAL(values[custom_              | or_else], 42.69   );
  TTS_CONSTEXPR_EQUAL(values[is_modal_            | or_else], true    );
  TTS_CONSTEXPR_EQUAL(values[is_transparent_      | flag_it], 42.69   );
}
