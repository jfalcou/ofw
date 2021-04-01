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

TTS_CASE("Check construction of kumi::tuple as an aggregate")
{
  kumi::tuple t0 = {};
  kumi::tuple t1 = {1};
  kumi::tuple t2 = {1.f,2};
  kumi::tuple t3 = {1.,2.f,3};
  kumi::tuple t4 = {'1',2.,3.f,4};

  TTS_CONSTEXPR_EXPECT( (kumi::sized_product_type<decltype(t0),0>) );
  TTS_EQUAL( t0.size(), 0ULL );

  auto[t1_0] = t1;
  TTS_CONSTEXPR_EXPECT( (kumi::sized_product_type<decltype(t1),1>) );
  TTS_EQUAL( t1.size(), 1ULL );
  TTS_EQUAL( t1_0, 1);

  auto[t2_0, t2_1] = t2;
  TTS_CONSTEXPR_EXPECT( (kumi::sized_product_type<decltype(t2),2>) );
  TTS_EQUAL( t2.size(), 2ULL );
  TTS_EQUAL( t2_0, 1.f);
  TTS_EQUAL( t2_1, 2  );

  auto[t3_0, t3_1, t3_2] = t3;
  TTS_CONSTEXPR_EXPECT( (kumi::sized_product_type<decltype(t3),3>) );
  TTS_EQUAL( t3.size(), 3ULL );
  TTS_EQUAL( t3_0, 1. );
  TTS_EQUAL( t3_1, 2.f);
  TTS_EQUAL( t3_2, 3  );

  auto[t4_0, t4_1, t4_2, t4_3] = t4;
  TTS_CONSTEXPR_EXPECT( (kumi::sized_product_type<decltype(t4),4>) );
  TTS_EQUAL( t4.size(), 4ULL );
  TTS_EQUAL( t4_0, '1');
  TTS_EQUAL( t4_1, 2. );
  TTS_EQUAL( t4_2, 3.f);
  TTS_EQUAL( t4_3, 4  );
}

TTS_CASE("Check construction of kumi::tuple as a constexpr aggregate")
{
  constexpr kumi::tuple t0 = {};
  constexpr kumi::tuple t1 = {1};
  constexpr kumi::tuple t2 = {1.f,2};
  constexpr kumi::tuple t3 = {1.,2.f,3};
  constexpr kumi::tuple t4 = {'1',2.,3.f,4};

  TTS_CONSTEXPR_EXPECT( (kumi::sized_product_type<decltype(t0),0>) );
  TTS_CONSTEXPR_EQUAL( t0.size(), 0ULL );

  TTS_CONSTEXPR_EXPECT( (kumi::sized_product_type<decltype(t1),1>) );
  TTS_CONSTEXPR_EQUAL( t1.size()  , 1ULL);
  TTS_CONSTEXPR_EQUAL( get<0>(t1) , 1   );

  TTS_CONSTEXPR_EXPECT( (kumi::sized_product_type<decltype(t2),2>) );
  TTS_CONSTEXPR_EQUAL( t2.size()  , 2ULL);
  TTS_CONSTEXPR_EQUAL( get<0>(t2) , 1.f );
  TTS_CONSTEXPR_EQUAL( get<1>(t2) , 2   );

  TTS_CONSTEXPR_EXPECT( (kumi::sized_product_type<decltype(t3),3>) );
  TTS_CONSTEXPR_EQUAL( t3.size()  , 3ULL);
  TTS_CONSTEXPR_EQUAL( get<0>(t3) , 1.  );
  TTS_CONSTEXPR_EQUAL( get<1>(t3) , 2.f );
  TTS_CONSTEXPR_EQUAL( get<2>(t3) , 3   );

  TTS_CONSTEXPR_EXPECT( (kumi::sized_product_type<decltype(t4),4>) );
  TTS_CONSTEXPR_EQUAL( t4.size()  , 4ULL);
  TTS_CONSTEXPR_EQUAL( get<0>(t4) , '1' );
  TTS_CONSTEXPR_EQUAL( get<1>(t4) , 2.  );
  TTS_CONSTEXPR_EQUAL( get<2>(t4) , 3.f );
  TTS_CONSTEXPR_EQUAL( get<3>(t4) , 4   );
}

TTS_CASE("Check construction of kumi::tuple via make_tuple")
{
  kumi::tuple t0 = kumi::make_tuple();
  kumi::tuple t1 = kumi::make_tuple(1);
  kumi::tuple t2 = kumi::make_tuple(1.f,2);
  kumi::tuple t3 = kumi::make_tuple(1.,2.f,3);
  kumi::tuple t4 = kumi::make_tuple('1',2.,3.f,4) ;

  TTS_CONSTEXPR_EXPECT( (kumi::sized_product_type<decltype(t0),0>) );
  TTS_EQUAL( t0.size(), 0ULL );

  auto[t1_0] = t1;
  TTS_CONSTEXPR_EXPECT( (kumi::sized_product_type<decltype(t1),1>) );
  TTS_EQUAL( t1.size(), 1ULL );
  TTS_EQUAL( t1_0, 1);

  auto[t2_0, t2_1] = t2;
  TTS_CONSTEXPR_EXPECT( (kumi::sized_product_type<decltype(t2),2>) );
  TTS_EQUAL( t2.size(), 2ULL );
  TTS_EQUAL( t2_0, 1.f);
  TTS_EQUAL( t2_1, 2  );

  auto[t3_0, t3_1, t3_2] = t3;
  TTS_CONSTEXPR_EXPECT( (kumi::sized_product_type<decltype(t3),3>) );
  TTS_EQUAL( t3.size(), 3ULL );
  TTS_EQUAL( t3_0, 1. );
  TTS_EQUAL( t3_1, 2.f);
  TTS_EQUAL( t3_2, 3  );

  auto[t4_0, t4_1, t4_2, t4_3] = t4;
  TTS_CONSTEXPR_EXPECT( (kumi::sized_product_type<decltype(t4),4>) );
  TTS_EQUAL( t4.size(), 4ULL );
  TTS_EQUAL( t4_0, '1');
  TTS_EQUAL( t4_1, 2. );
  TTS_EQUAL( t4_2, 3.f);
  TTS_EQUAL( t4_3, 4  );
}

TTS_CASE("Check construction of kumi::tuple via constexpr make_tuple")
{
  constexpr kumi::tuple t0 = kumi::make_tuple();
  constexpr kumi::tuple t1 = kumi::make_tuple(1);
  constexpr kumi::tuple t2 = kumi::make_tuple(1.f,2);
  constexpr kumi::tuple t3 = kumi::make_tuple(1.,2.f,3);
  constexpr kumi::tuple t4 = kumi::make_tuple('1',2.,3.f,4) ;

  TTS_CONSTEXPR_EXPECT( (kumi::sized_product_type<decltype(t0),0>) );
  TTS_CONSTEXPR_EQUAL( t0.size(), 0ULL );

  TTS_CONSTEXPR_EXPECT( (kumi::sized_product_type<decltype(t1),1>) );
  TTS_CONSTEXPR_EQUAL( t1.size()  , 1ULL);
  TTS_CONSTEXPR_EQUAL( get<0>(t1) , 1   );

  TTS_CONSTEXPR_EXPECT( (kumi::sized_product_type<decltype(t2),2>) );
  TTS_CONSTEXPR_EQUAL( t2.size()  , 2ULL);
  TTS_CONSTEXPR_EQUAL( get<0>(t2) , 1.f );
  TTS_CONSTEXPR_EQUAL( get<1>(t2) , 2   );

  TTS_CONSTEXPR_EXPECT( (kumi::sized_product_type<decltype(t3),3>) );
  TTS_CONSTEXPR_EQUAL( t3.size()  , 3ULL);
  TTS_CONSTEXPR_EQUAL( get<0>(t3) , 1.  );
  TTS_CONSTEXPR_EQUAL( get<1>(t3) , 2.f );
  TTS_CONSTEXPR_EQUAL( get<2>(t3) , 3   );

  TTS_CONSTEXPR_EXPECT( (kumi::sized_product_type<decltype(t4),4>) );
  TTS_CONSTEXPR_EQUAL( t4.size()  , 4ULL);
  TTS_CONSTEXPR_EQUAL( get<0>(t4) , '1' );
  TTS_CONSTEXPR_EQUAL( get<1>(t4) , 2.  );
  TTS_CONSTEXPR_EQUAL( get<2>(t4) , 3.f );
  TTS_CONSTEXPR_EQUAL( get<3>(t4) , 4   );
}

TTS_CASE("Check construction of kumi::tuple via tie")
{
  auto i = 1;
  auto f = 2.f;
  auto d = 3.;
  auto c = '4';

  kumi::tuple t1 = kumi::tie(i);
  kumi::tuple t2 = kumi::tie(i,f);
  kumi::tuple t3 = kumi::tie(i,f,d);
  kumi::tuple t4 = kumi::tie(i,f,d,c) ;

  auto& [t1_0] = t1;
  TTS_CONSTEXPR_EXPECT( (kumi::sized_product_type<decltype(t1),1>) );
  TTS_EQUAL( t1.size(), 1ULL );
  TTS_EQUAL( &t1_0, &i);

  auto&[t2_0, t2_1] = t2;
  TTS_CONSTEXPR_EXPECT( (kumi::sized_product_type<decltype(t2),2>) );
  TTS_EQUAL( t2.size(), 2ULL );
  TTS_EQUAL( &t2_0, &i);
  TTS_EQUAL( &t2_1, &f );

  auto&[t3_0, t3_1, t3_2] = t3;
  TTS_CONSTEXPR_EXPECT( (kumi::sized_product_type<decltype(t3),3>) );
  TTS_EQUAL( t3.size(), 3ULL );
  TTS_EQUAL( &t3_0, &i);
  TTS_EQUAL( &t3_1, &f);
  TTS_EQUAL( &t3_2, &d);

  auto&[t4_0, t4_1, t4_2, t4_3] = t4;
  TTS_CONSTEXPR_EXPECT( (kumi::sized_product_type<decltype(t4),4>) );
  TTS_EQUAL( t4.size(), 4ULL );
  TTS_EQUAL( &t4_0, &i);
  TTS_EQUAL( &t4_1, &f);
  TTS_EQUAL( &t4_2, &d);
  TTS_EQUAL( &t4_3, &c);
}
