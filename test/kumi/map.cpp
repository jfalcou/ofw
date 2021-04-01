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

TTS_CASE("Check tuple::map behavior")
{
  TTS_WHEN("Given a tuple t")
  {
    auto t = kumi::tuple{1,2.,3.4f,'5'};

    TTS_AND_THEN(" - we call t.map(f)")
    {
      auto s = t.map( [](auto m) { return sizeof(m); } );

      auto[m0,m1,m2,m3] = s;
      TTS_EQUAL(m0, sizeof(int)   );
      TTS_EQUAL(m1, sizeof(double));
      TTS_EQUAL(m2, sizeof(float) );
      TTS_EQUAL(m3, sizeof(char)  );
    }

    TTS_AND_THEN(" - we call t.map(f,u)")
    {
      auto u = kumi::tuple{2,3,4,5};
      auto s = t.map( [](auto m, auto n) { return n * sizeof(m); }, u );

      auto[m0,m1,m2,m3] = s;
      TTS_EQUAL(m0, 2*sizeof(int)   );
      TTS_EQUAL(m1, 3*sizeof(double));
      TTS_EQUAL(m2, 4*sizeof(float) );
      TTS_EQUAL(m3, 5*sizeof(char)  );
    }
  }
}

TTS_CASE("Check tuple::map constexpr behavior")
{
  TTS_WHEN("Given a tuple t")
  {
    constexpr auto t = kumi::tuple{1,2.,3.4f,'5'};

    TTS_AND_THEN(" - we call t.map(f)")
    {
      constexpr auto s = t.map( [](auto m) { return sizeof(m); } );

      TTS_CONSTEXPR_EQUAL(get<0>(s), sizeof(int)   );
      TTS_CONSTEXPR_EQUAL(get<1>(s), sizeof(double));
      TTS_CONSTEXPR_EQUAL(get<2>(s), sizeof(float) );
      TTS_CONSTEXPR_EQUAL(get<3>(s), sizeof(char)  );
    }

    TTS_AND_THEN(" - we call t.map(f,u)")
    {
      constexpr auto u = kumi::tuple{2,3,4,5};
      constexpr auto s = t.map( [](auto m, auto n) { return n * sizeof(m); }, u );

      TTS_CONSTEXPR_EQUAL(get<0>(s), 2*sizeof(int)   );
      TTS_CONSTEXPR_EQUAL(get<1>(s), 3*sizeof(double));
      TTS_CONSTEXPR_EQUAL(get<2>(s), 4*sizeof(float) );
      TTS_CONSTEXPR_EQUAL(get<3>(s), 5*sizeof(char)  );
    }
  }
}

TTS_CASE("Check map(f, tuple) behavior")
{
  TTS_WHEN("Given a tuple t")
  {
    auto t = kumi::tuple{1,2.,3.4f,'5'};

    TTS_AND_THEN(" - we call map(f,t)")
    {
      auto s = map( [](auto m) { return sizeof(m); }, t );

      auto[m0,m1,m2,m3] = s;
      TTS_EQUAL(m0, sizeof(int)   );
      TTS_EQUAL(m1, sizeof(double));
      TTS_EQUAL(m2, sizeof(float) );
      TTS_EQUAL(m3, sizeof(char)  );
    }

    TTS_AND_THEN(" - we call map(f,t,u)")
    {
      auto u = kumi::tuple{2,3,4,5};
      auto s = map( [](auto m, auto n) { return n * sizeof(m); }, t, u );

      auto[m0,m1,m2,m3] = s;
      TTS_EQUAL(m0, 2*sizeof(int)   );
      TTS_EQUAL(m1, 3*sizeof(double));
      TTS_EQUAL(m2, 4*sizeof(float) );
      TTS_EQUAL(m3, 5*sizeof(char)  );
    }
  }
}

TTS_CASE("Check map(f, tuple) constexpr behavior")
{
  TTS_WHEN("Given a tuple t")
  {
    constexpr auto t = kumi::tuple{1,2.,3.4f,'5'};

    TTS_AND_THEN(" - we call t.map(f)")
    {
      constexpr auto s = map( [](auto m) { return sizeof(m); }, t );

      TTS_CONSTEXPR_EQUAL(get<0>(s), sizeof(int)   );
      TTS_CONSTEXPR_EQUAL(get<1>(s), sizeof(double));
      TTS_CONSTEXPR_EQUAL(get<2>(s), sizeof(float) );
      TTS_CONSTEXPR_EQUAL(get<3>(s), sizeof(char)  );
    }

    TTS_AND_THEN(" - we call t.map(f,u)")
    {
      constexpr auto u = kumi::tuple{2,3,4,5};
      constexpr auto s = map( [](auto m, auto n) { return n * sizeof(m); }, t, u );

      TTS_CONSTEXPR_EQUAL(get<0>(s), 2*sizeof(int)   );
      TTS_CONSTEXPR_EQUAL(get<1>(s), 3*sizeof(double));
      TTS_CONSTEXPR_EQUAL(get<2>(s), 4*sizeof(float) );
      TTS_CONSTEXPR_EQUAL(get<3>(s), 5*sizeof(char)  );
    }
  }
}


TTS_CASE("Check tuple::map continuation behavior")
{
  TTS_WHEN("Given a tuple t")
  {
    auto t = kumi::tuple{1,2.,short(34),'5'};

    TTS_AND_THEN(" - we call t.map(f).map(g)")
    {
      auto s = t.map( [](auto m) { return sizeof(m); } )
                .map( [](auto m) { return 1./m; } );

      auto[m0,m1,m2,m3] = s;
      TTS_EQUAL(m0, 1./4);
      TTS_EQUAL(m1, 1./8);
      TTS_EQUAL(m2, 1./2);
      TTS_EQUAL(m3, 1.  );
    }

    TTS_AND_THEN(" - we call t.map(f).map(g,u)")
    {
      auto u = kumi::tuple{2.,3.,4.,5.};
      auto s = t.map( [](auto m)          { return sizeof(m); }     )
                .map( [](auto m, auto v)  { return v/m;       }, u  );

      auto[m0,m1,m2,m3] = s;
      TTS_EQUAL(m0, 2./4);
      TTS_EQUAL(m1, 3./8);
      TTS_EQUAL(m2, 4./2);
      TTS_EQUAL(m3, 5.  );
    }
  }
}

TTS_CASE("Check tuple::map constexpr continuation behavior")
{
  TTS_WHEN("Given a tuple t")
  {
    constexpr auto t = kumi::tuple{1,2.,short(34),'5'};

    TTS_AND_THEN(" - we call t.map(f).map(g)")
    {
      constexpr auto s = t.map( [](auto m) { return sizeof(m); } )
                          .map( [](auto m) { return 1./m; } );

      TTS_CONSTEXPR_EQUAL(get<0>(s), 1./4);
      TTS_CONSTEXPR_EQUAL(get<1>(s), 1./8);
      TTS_CONSTEXPR_EQUAL(get<2>(s), 1./2);
      TTS_CONSTEXPR_EQUAL(get<3>(s), 1.  );
    }


    TTS_AND_THEN(" - we call t.map(f).map(g,u)")
    {
      constexpr auto u = kumi::tuple{2.,3.,4.,5.};
      constexpr auto s = t.map( [](auto m)          { return sizeof(m); }     )
                .map( [](auto m, auto v)  { return v/m;       }, u  );

      TTS_CONSTEXPR_EQUAL(get<0>(s), 2./4);
      TTS_CONSTEXPR_EQUAL(get<1>(s), 3./8);
      TTS_CONSTEXPR_EQUAL(get<2>(s), 4./2);
      TTS_CONSTEXPR_EQUAL(get<3>(s), 5.  );
    }
  }
}
