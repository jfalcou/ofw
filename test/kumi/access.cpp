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

TTS_CASE("Check access to kumi::tuple via indexing")
{
  using namespace kumi::literal;

  kumi::tuple t1 = {1};
  kumi::tuple t2 = {1.f,2};
  kumi::tuple t3 = {1.,2.f,3};
  kumi::tuple t4 = {'1',2.,3.f,4};

  auto[t1_0] = t1;
  TTS_EQUAL( t1_0, t1[0_c]);

  t1[0_c] = 42;
  TTS_EQUAL( t1[0_c], 42);

  auto[t2_0, t2_1] = t2;
  TTS_EQUAL( t2_0, t2[0_c]);
  TTS_EQUAL( t2_1, t2[1_c]);
  t2[0_c] = 4.2f;
  t2[1_c] = 69;

  TTS_EQUAL( t2[0_c], 4.2f);
  TTS_EQUAL( t2[1_c], 69  );

  auto[t3_0, t3_1, t3_2] = t3;
  TTS_EQUAL( t3_0, t3[0_c]);
  TTS_EQUAL( t3_1, t3[1_c]);
  TTS_EQUAL( t3_2, t3[2_c]);

  t3[0_c] = 13.37;
  t3[1_c] = 4.2f;
  t3[2_c] = 40;

  TTS_EQUAL( t3[0_c], 13.37 );
  TTS_EQUAL( t3[1_c], 4.2f  );
  TTS_EQUAL( t3[2_c], 40    );

  auto[t4_0, t4_1, t4_2, t4_3] = t4;
  TTS_EQUAL( t4_0, t4[0_c]);
  TTS_EQUAL( t4_1, t4[1_c]);
  TTS_EQUAL( t4_2, t4[2_c]);
  TTS_EQUAL( t4_3, t4[3_c]);

  t4[0_c] = 'z';
  t4[1_c] = 6.9;
  t4[2_c] = 4.2f;
  t4[3_c] = 1337;

  TTS_EQUAL(t4[0_c], 'z'  );
  TTS_EQUAL(t4[1_c], 6.9  );
  TTS_EQUAL(t4[2_c], 4.2f );
  TTS_EQUAL(t4[3_c], 1337 );
}

TTS_CASE("Check constexpr access to kumi::tuple via indexing")
{
  using namespace kumi::literal;

  constexpr kumi::tuple t1 = {1};
  constexpr kumi::tuple t2 = {1.f,2};
  constexpr kumi::tuple t3 = {1.,2.f,3};
  constexpr kumi::tuple t4 = {'1',2.,3.f,4};

  TTS_CONSTEXPR_EQUAL( get<0>(t1) , t1[0_c] );

  TTS_CONSTEXPR_EQUAL( get<0>(t2) , t2[0_c]);
  TTS_CONSTEXPR_EQUAL( get<1>(t2) , t2[1_c]);

  TTS_CONSTEXPR_EQUAL( get<0>(t3) , t3[0_c] );
  TTS_CONSTEXPR_EQUAL( get<1>(t3) , t3[1_c] );
  TTS_CONSTEXPR_EQUAL( get<2>(t3) , t3[2_c] );

  TTS_CONSTEXPR_EQUAL( get<0>(t4) , t4[0_c] );
  TTS_CONSTEXPR_EQUAL( get<1>(t4) , t4[1_c] );
  TTS_CONSTEXPR_EQUAL( get<2>(t4) , t4[2_c] );
  TTS_CONSTEXPR_EQUAL( get<3>(t4) , t4[3_c] );
}
