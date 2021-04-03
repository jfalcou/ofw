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
#include <array>
#include <vector>

TTS_CASE("Check tuple::fold_left behavior")
{
  auto t = kumi::tuple{2.,1,short{55},'z'};

  std::vector<int> output;

  auto accumulated  = t.fold_left ( [](auto acc, auto m)
                                    {
                                      acc.push_back(sizeof(m));
                                      return acc;
                                    }
                                  , output
                                  );

  TTS_EQUAL( accumulated, (std::vector<int>{8,4,2,1}));
}

TTS_CASE("Check tuple::fold_left constexpr behavior")
{
  constexpr auto t = kumi::tuple{2.,1,short{55},'z'};

  constexpr auto accumulated  = t.fold_left( []<std::size_t N>( std::array<int,N> acc, auto m)
                                              {
                                                if constexpr(N==0)
                                                {
                                                  std::array<int,1> res{sizeof(m)};
                                                  return res;
                                                }
                                                else
                                                {
                                                  std::array<int,N+1> res;
                                                  for(std::size_t i=0;i<N;++i) res[i] = acc[i];
                                                  res[N] = sizeof(m);
                                                  return res;
                                                }
                                              }
                                            , std::array<int,0>{} );

  TTS_CONSTEXPR_EQUAL( accumulated, (std::array<int,4>{8,4,2,1}));
}

TTS_CASE("Check tuple::fold_right behavior")
{
  auto t = kumi::tuple{2.,1,short{55},'z'};

  std::vector<int> output;

  auto accumulated  = t.fold_right ( [](auto acc, auto m)
                                    {
                                      acc.push_back(sizeof(m));
                                      return acc;
                                    }
                                  , output
                                  );

  TTS_EQUAL( accumulated, (std::vector<int>{1,2,4,8}));
}

TTS_CASE("Check tuple::fold_right constexpr behavior")
{
  constexpr auto t = kumi::tuple{2.,1,short{55},'z'};

  constexpr auto accumulated  = t.fold_right( []<std::size_t N>( std::array<int,N> acc, auto m)
                                              {
                                                if constexpr(N==0)
                                                {
                                                  std::array<int,1> res{sizeof(m)};
                                                  return res;
                                                }
                                                else
                                                {
                                                  std::array<int,N+1> res;
                                                  for(std::size_t i=0;i<N;++i) res[i] = acc[i];
                                                  res[N] = sizeof(m);
                                                  return res;
                                                }
                                              }
                                            , std::array<int,0>{} );

  TTS_CONSTEXPR_EQUAL( accumulated, (std::array<int,4>{1,2,4,8}));
}
