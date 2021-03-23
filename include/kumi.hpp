//==================================================================================================
/**
  KUMI - Compact Tuple Tools
  Copyright : RABERU Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <utility>
#include <ostream>

namespace kumi
{
  //================================================================================================
  // Constant integers
  //================================================================================================
  template<std::size_t N> struct index  { static constexpr auto value = N; };

  //================================================================================================
  // UDL for constant indexing like 42_c
  //================================================================================================
  namespace literal
  {
    template<char... c> constexpr auto b10()
    {
      auto value = 0ULL;
      ((value = value*10 + (c - '0')),...);
      return value;
    }
    template<char ...c> constexpr auto operator"" _c() noexcept { return index<b10<c...>()>{}; }
  }

  //================================================================================================
  // Implementation detail
  //================================================================================================
  namespace detail
  {
    //==============================================================================================
    // Helper concepts
    //==============================================================================================
    template<typename From, typename To> struct is_piecewise_assignable;

    template<template<class...> class Box, typename... From, typename... To>
    struct is_piecewise_assignable<Box<From...>,Box<To...>>
    {
      static constexpr bool value = ( ... && std::convertible_to<From,To>);
    };

    template<typename From, typename To>
    concept piecewise_assignable = detail::is_piecewise_assignable<From,To>::value;

    //==============================================================================================
    // Tuple leaf binder tricks
    //==============================================================================================
    template <std::size_t I, typename T> struct leaf { T value; };

    template <std::size_t I, typename T>
    constexpr auto leaf_type(leaf<I, T> const& arg) -> T;

    template <std::size_t I, typename T>
    constexpr auto& get_leaf(leaf<I, T>& arg) noexcept { return arg.value;  }

    template <std::size_t I, typename T>
    constexpr auto&& get_leaf(leaf<I, T>&& arg) noexcept { return std::move(arg.value);  }

    template <std::size_t I, typename T>
    constexpr auto const& get_leaf(leaf<I, T> const& arg) noexcept { return arg.value;  }

    template <std::size_t I, typename T>
    constexpr auto& get_leaf(leaf<I, T&> const& arg) noexcept { return arg.value;  }

    template <typename ISeq, typename... Ts> struct binder;

    template <auto... Is, typename... Ts>
    struct binder<std::index_sequence<Is...>, Ts...> : leaf<Is, Ts>... {};

    //==============================================================================================
    // Fold helpers
    //==============================================================================================
    template<typename F, typename T>
    struct foldable
    {
      F func;
      T value;

      template<typename W>
      friend constexpr decltype(auto) operator>>(foldable&& x, foldable<F, W>&& y)
      {
        return detail::foldable{x.func,x.func(x.value, y.value)};
      }

      template<typename W>
      friend constexpr decltype(auto) operator<<(foldable&& x, foldable<F, W>&& y)
      {
        return detail::foldable{x.func,x.func(x.value, y.value)};
      }
    };

    template<class F, class T> foldable(const F&, T&&) -> foldable<F, T>;
  }

  //==============================================================================================
  // Concept
  //==============================================================================================
  template<typename T>
  concept product_type = std::remove_cvref_t<T>::is_product_type;

  template<typename T, std::size_t N>
  concept sized_product_type = product_type<T> && (T::size() == N);

  //================================================================================================
  // Main tuple class
  //================================================================================================
  template <typename... Ts> struct tuple
  {
    static constexpr bool is_product_type = true;
    detail::binder<std::make_index_sequence<sizeof...(Ts)>, Ts...> impl;

    //==============================================================================================
    // Access
    //==============================================================================================
    template<std::size_t I>
    constexpr decltype(auto) operator[](index<I>) noexcept requires(I<sizeof...(Ts))
    {
      return detail::get_leaf<I>(impl);
    }

    template<std::size_t I>
    constexpr decltype(auto) operator[](index<I>) const noexcept requires(I<sizeof...(Ts))
    {
      return detail::get_leaf<I>(impl);
    }

    //==============================================================================================
    // Algorithms
    //==============================================================================================
    // Apply f to every elements of the tuple and return a continuation
    template<typename Function> constexpr tuple& apply(Function f)
    {
      [&]<std::size_t... I>(std::index_sequence<I...>)
      {
        (f(detail::get_leaf<I>(impl)),...);
      }(std::make_index_sequence<sizeof...(Ts)>());

      return *this;
    }

    template<typename Function> constexpr tuple const& apply(Function f) const
    {
      [&]<std::size_t... I>(std::index_sequence<I...>)
      {
        (f(detail::get_leaf<I>(impl)),...);
      }(std::make_index_sequence<sizeof...(Ts)>());

      return *this;
    }

    // Construct the tuple made of the application of f to elements of each tuples
    template<typename Function, sized_product_type<sizeof...(Ts)>... Tuples>
    [[nodiscard]] constexpr auto map(Function f, Tuples const&... others) const;

    template<typename Function, typename Value>
    constexpr auto fold_right(Function f, Value init) const
    {
      return  [&]<std::size_t... I>(std::index_sequence<I...>)
              {
                return  (   detail::foldable{f, detail::get_leaf<I>(impl) }
                        >>  ...
                        >>  detail::foldable{f,init}
                        ).value;
              }(std::make_index_sequence<sizeof...(Ts)>());
    }

    template<typename Function, typename Value>
    constexpr auto fold_left(Function f, Value init) const
    {
      return  [&]<std::size_t... I>(std::index_sequence<I...>)
              {
                return  (   detail::foldable{f,init}
                        <<  ...
                        <<  detail::foldable{f, detail::get_leaf<I>(impl) }
                        ).value;
              }(std::make_index_sequence<sizeof...(Ts)>());
    }

    template<typename... Us>
    [[nodiscard]] auto cat(tuple<Us...> const& us) const
    {
      return [&]<std::size_t... TI, std::size_t... UI>( std::index_sequence<TI...>
                                                      , std::index_sequence<UI...>
                                                      )
      {
        return tuple<Ts...,Us...>{ get<TI>(*this)..., get<UI>(us)...};
      }( std::index_sequence_for<Ts...>{}, std::index_sequence_for<Us...>{});
    }

    template< product_type... Tuples> [[nodiscard]] constexpr auto cat(Tuples const&... ts )
    {
      auto const cc = [](auto const& a, auto const& b) { return a.cat(b); };
      return (detail::foldable{cc,*this} >> ... >> detail::foldable{cc,ts}).value;
    }

    template<std::size_t I0, std::size_t I1>
    constexpr auto extract( index<I0> const&, index<I1> const&) const noexcept requires((I1-I0) <= sizeof...(Ts))
    {
      return [&]<std::size_t... N>(std::index_sequence<N...>)
      {
        return tuple<std::tuple_element_t<N+I0,tuple>...>{ (*this)[index<N+I0>{}]... };
      }( std::make_index_sequence<I1-I0>() );
    }

    template<std::size_t I0, std::size_t I1>
    constexpr auto extract( index<I0> const&, index<I1> const&) noexcept requires((I1-I0) <= sizeof...(Ts))
    {
      return [&]<std::size_t... N>(std::index_sequence<N...>)
      {
        return tuple<std::tuple_element_t<N+I0,tuple>...>{ (*this)[index<N+I0>{}]... };
      }( std::make_index_sequence<I1-I0>() );
    }

    template<std::size_t I0>
    constexpr auto extract( index<I0> const&) const noexcept requires(I0 <= sizeof...(Ts))
    {
      return [&]<std::size_t... N>(std::index_sequence<N...>)
      {
        return tuple<std::tuple_element_t<N+I0,tuple>...>{ (*this)[index<N+I0>{}]... };
      }( std::make_index_sequence<sizeof...(Ts)-I0>() );
    }

    template<std::size_t I0>
    constexpr auto extract( index<I0> const&) noexcept requires(I0 <= sizeof...(Ts))
    {
      return [&]<std::size_t... N>(std::index_sequence<N...>)
      {
        return tuple<std::tuple_element_t<N+I0,tuple>...>{ (*this)[index<N+I0>{}]... };
      }( std::make_index_sequence<sizeof...(Ts)-I0>() );
    }

    template<std::size_t I0>
    constexpr auto split( index<I0> const&) const noexcept requires(I0 <= sizeof...(Ts));

    template<std::size_t I0>
    constexpr auto split( index<I0> const&)  noexcept requires(I0 <= sizeof...(Ts));

    //==============================================================================================
    // Informations on tuple
    //==============================================================================================
    static constexpr auto size() noexcept { return sizeof...(Ts); }

    //==============================================================================================
    // Assignment
    //==============================================================================================
    template<typename... Us>
    tuple& operator=(tuple<Us...> const& other) &
    requires( detail::piecewise_assignable<tuple,tuple<Us...>> )
    {
      [&]<std::size_t... I>(std::index_sequence<I...>)
      {
        ((detail::get_leaf<I>(impl) = detail::get_leaf<I>(other.impl)),...);
      }(std::make_index_sequence<sizeof...(Ts)>());

      return *this;
    }

    template<typename... Us>
    tuple& operator=(tuple<Us...> && other) &
    requires( detail::piecewise_assignable<tuple,tuple<Us...>> )
    {
      [&]<std::size_t... I>(std::index_sequence<I...>)
      {
        ((detail::get_leaf<I>(impl) = std::move(detail::get_leaf<I>(other.impl))),...);
      }(std::make_index_sequence<sizeof...(Ts)>());

      return *this;
    }

    //==============================================================================================
    // Stream interaction
    //==============================================================================================
    friend std::ostream& operator<<(std::ostream& os, tuple const& t) noexcept
    {
      os << "( ";
      t.apply( [&os](auto const& e) { os << e << " "; });
      os << ")";

      return os;
    }
  };

  //================================================================================================
  // CTAD and other helpers
  //================================================================================================
  template <typename... Ts> tuple(Ts&&...) -> tuple<std::remove_cvref_t<Ts>...>;

  template <typename... Ts>
  [[nodiscard]] constexpr tuple<Ts&...> tie(Ts&... ts)          { return {ts...};                   }

  template <typename... Ts>
  [[nodiscard]] constexpr tuple<Ts...>  make_tuple(Ts&&... ts)  { return {std::forward<Ts>(ts)...}; }

  //================================================================================================
  // Implementation depending on make_tuple/tie
  //================================================================================================
  template<typename... Ts>
  template<typename Function, sized_product_type<sizeof...(Ts)>... Tuples>
  [[nodiscard]] constexpr auto tuple<Ts...>::map(Function f, Tuples const&... others) const
  {
    return [&]<std::size_t... I>(std::index_sequence<I...>)
    {
      auto call = [&]<std::size_t N>(index<N>, auto const&... args)
                  {
                    return f(detail::get_leaf<N>(args.impl)...);
                  };

      return  make_tuple( call( index<I>{}, *this, others...)...);
    }(std::make_index_sequence<sizeof...(Ts)>());
  }

    template<typename... Ts>
    template<std::size_t I0>
    constexpr auto tuple<Ts...>::split( index<I0> const&) const noexcept requires(I0 <= sizeof...(Ts))
    {
      return kumi::make_tuple(extract(index<0>{},index<I0>{}), extract(index<I0>{}) );
    }

    template<typename... Ts>
    template<std::size_t I0>
    constexpr auto tuple<Ts...>::split( index<I0> const&)  noexcept requires(I0 <= sizeof...(Ts))
    {
      return kumi::make_tuple(extract(index<0>{},index<I0>{}), extract(index<I0>{}) );
    }

  //==============================================================================================
  // Access
  //==============================================================================================
  template<std::size_t I, typename... Ts>
  constexpr decltype(auto) get(tuple<Ts...>& arg) noexcept requires( I<sizeof...(Ts) )
  {
    return arg[index<I>{}];
  }

  template<std::size_t I, typename... Ts>
  constexpr decltype(auto) get(tuple<Ts...> const& arg)  noexcept requires(I<sizeof...(Ts))
  {
    return arg[index<I>{}];
  }
}

//==================================================================================================
// Structured binding adaptation
//==================================================================================================
namespace std
{
  template<std::size_t I, typename... Ts>
  struct tuple_element<I, kumi::tuple<Ts...>>
  {
    using type = decltype(std::declval<kumi::tuple<Ts...> const&>()[kumi::index<I>{}]);
  };

  template<typename... Ts>
  struct tuple_size<kumi::tuple<Ts...>> : std::integral_constant<std::size_t,sizeof...(Ts)>
  {};
}
