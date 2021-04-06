//==================================================================================================
/**
  KUMI - Compact Tuple Tools
  Copyright : OFW Contributors & Maintainers
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
  template<std::size_t N> struct index_t  { static constexpr auto value = N; };
  template<std::size_t N> inline constexpr index_t<N> const index = {};

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
    template<char ...c> constexpr auto operator"" _c() noexcept { return index<b10<c...>()>; }
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
    constexpr auto& get_leaf(leaf<I, T>& arg) noexcept { return arg.value;  }

    template <std::size_t I, typename T>
    constexpr auto&& get_leaf(leaf<I, T>&& arg) noexcept { return std::move(arg.value);  }

    template <std::size_t I, typename T>
    constexpr decltype(auto) get_leaf(leaf<I, T> const& arg) noexcept { return arg.value;  }

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
        return detail::foldable{x.func,x.func(y.value, x.value)};
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
    template<std::size_t I> requires(I<sizeof...(Ts))
    constexpr decltype(auto) operator[](index_t<I>) noexcept
    {
      return detail::get_leaf<I>(impl);
    }

    template<std::size_t I> requires(I<sizeof...(Ts))
    constexpr decltype(auto) operator[](index_t<I>) const noexcept
    {
      return detail::get_leaf<I>(impl);
    }

    //==============================================================================================
    // Algorithms
    //==============================================================================================

    //==============================================================================================
    //Appyl f to each element of tuple and returns a continuation
    //==============================================================================================
    template<typename Function> constexpr decltype(auto) for_each(Function f)
    {
      [&]<std::size_t... I>(std::index_sequence<I...>)
      {
        (f(detail::get_leaf<I>(impl)),...);
      }(std::make_index_sequence<sizeof...(Ts)>());

      return *this;
    }

    template<typename Function> constexpr decltype(auto) for_each(Function f) const
    {
      [&]<std::size_t... I>(std::index_sequence<I...>)
      {
        (f(detail::get_leaf<I>(impl)),...);
      }(std::make_index_sequence<sizeof...(Ts)>());

      return *this;
    }

    //==============================================================================================
    // Pass every elements of the tuple to f
    //==============================================================================================
    template<typename Function> constexpr decltype(auto) apply(Function f)
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>)
      {
        return f(detail::get_leaf<I>(impl)...);
      }(std::make_index_sequence<sizeof...(Ts)>());
    }

    template<typename Function> constexpr decltype(auto) apply(Function f) const
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>)
      {
        return f(detail::get_leaf<I>(impl)...);
      }(std::make_index_sequence<sizeof...(Ts)>());
    }

    //==============================================================================================
    // Construct the tuple made of the application of f to elements of each tuples
    //==============================================================================================
    template<typename Function, sized_product_type<sizeof...(Ts)>... Tuples>
    constexpr auto map(Function f, Tuples const&... others) const;

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
    [[nodiscard]] constexpr auto fold_left(Function f, Value init) const
    {
      return  [&]<std::size_t... I>(std::index_sequence<I...>)
              {
                return  (   detail::foldable{f,init}
                        <<  ...
                        <<  detail::foldable{f, detail::get_leaf<I>(impl) }
                        ).value;
              }(std::make_index_sequence<sizeof...(Ts)>());
    }

    //==============================================================================================
    // Concatenates tuples
    //==============================================================================================
    template<typename... Us>
    [[nodiscard]] constexpr auto cat(tuple<Us...> const& us) const
    {
      return [&]<std::size_t... TI, std::size_t... UI>( std::index_sequence<TI...>
                                                      , std::index_sequence<UI...>
                                                      )
      {
        return tuple<Ts...,Us...>{ get<TI>(*this)..., get<UI>(us)...};
      }( std::index_sequence_for<Ts...>{}, std::index_sequence_for<Us...>{});
    }

    template< product_type... Tuples> [[nodiscard]] constexpr auto cat(Tuples const&... ts ) const
    {
      auto const cc = [](auto const& a, auto const& b) { return a.cat(b); };
      return (detail::foldable{cc,*this} << ... << detail::foldable{cc,ts}).value;
    }

    //==============================================================================================
    // Extract a sub-rage of tuple element
    //==============================================================================================
    template<std::size_t I0, std::size_t I1>
    requires((I1-I0) <= sizeof...(Ts))
    [[nodiscard]] constexpr auto extract( index_t<I0> const&, index_t<I1> const&) const noexcept
    {
      return [&]<std::size_t... N>(std::index_sequence<N...>)
      {
        return tuple<std::tuple_element_t<N+I0,tuple>...>{ (*this)[index<N+I0>]... };
      }( std::make_index_sequence<I1-I0>() );
    }

    template<std::size_t I0, std::size_t I1>
    requires((I1-I0) <= sizeof...(Ts))
    [[nodiscard]] constexpr auto extract( index_t<I0> const&, index_t<I1> const&) noexcept
    {
      return [&]<std::size_t... N>(std::index_sequence<N...>)
      {
        return tuple<std::tuple_element_t<N+I0,tuple>...>{ (*this)[index<N+I0>]... };
      }( std::make_index_sequence<I1-I0>() );
    }

    template<std::size_t I0>
    requires(I0 <= sizeof...(Ts))
    [[nodiscard]] constexpr auto extract( index_t<I0> const&) const noexcept
    {
      return [&]<std::size_t... N>(std::index_sequence<N...>)
      {
        return tuple<std::tuple_element_t<N+I0,tuple>...>{ (*this)[index<N+I0>]... };
      }( std::make_index_sequence<sizeof...(Ts)-I0>() );
    }

    template<std::size_t I0>
    requires(I0 <= sizeof...(Ts))
    [[nodiscard]] constexpr auto extract( index_t<I0> const&) noexcept
    {
      return [&]<std::size_t... N>(std::index_sequence<N...>)
      {
        return tuple<std::tuple_element_t<N+I0,tuple>...>{ (*this)[index<N+I0>]... };
      }( std::make_index_sequence<sizeof...(Ts)-I0>() );
    }

    //==============================================================================================
    // Split a tuple into two tuples based on an index
    //==============================================================================================
    template<std::size_t I0>
    requires(I0 <= sizeof...(Ts))
    [[nodiscard]] constexpr auto split( index_t<I0> const&) const noexcept;

    template<std::size_t I0>
    requires(I0 <= sizeof...(Ts))
    [[nodiscard]] constexpr auto split( index_t<I0> const&)  noexcept;

    //==============================================================================================
    // Informations on tuple
    //==============================================================================================
    [[nodiscard]] static constexpr auto size() noexcept { return sizeof...(Ts); }

    //==============================================================================================
    // Assignment
    //==============================================================================================
    template<typename... Us>
    requires( detail::piecewise_assignable<tuple,tuple<Us...>> )
    constexpr tuple& operator=(tuple<Us...> const& other) &
    {
      [&]<std::size_t... I>(std::index_sequence<I...>)
      {
        ((detail::get_leaf<I>(impl) = detail::get_leaf<I>(other.impl)),...);
      }(std::make_index_sequence<sizeof...(Ts)>());

      return *this;
    }

    template<typename... Us>
    requires( detail::piecewise_assignable<tuple,tuple<Us...>> )
    constexpr tuple& operator=(tuple<Us...> && other) &
    {
      [&]<std::size_t... I>(std::index_sequence<I...>)
      {
        ((detail::get_leaf<I>(impl) = std::move(detail::get_leaf<I>(other.impl))),...);
      }(std::make_index_sequence<sizeof...(Ts)>());

      return *this;
    }

    //==============================================================================================
    // Comparison operators
    //==============================================================================================
    template<sized_product_type<sizeof...(Ts)> Other>
    friend constexpr bool operator==(tuple const& self, Other const& other) noexcept
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>)
      {
        return ((detail::get_leaf<I>(self.impl) == detail::get_leaf<I>(other.impl)) && ...);
      }(std::make_index_sequence<sizeof...(Ts)>());
    }

    template<sized_product_type<sizeof...(Ts)> Other>
    friend constexpr bool operator!=(tuple const& self, Other const& other) noexcept
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>)
      {
        return ((detail::get_leaf<I>(self.impl) != detail::get_leaf<I>(other.impl)) || ...);
      }(std::make_index_sequence<sizeof...(Ts)>());
    }

    //==============================================================================================
    // Stream interaction
    //==============================================================================================
    friend std::ostream& operator<<(std::ostream& os, tuple const& t) noexcept
    {
      os << "( ";
      t.for_each( [&os](auto const& e) { os << e << " "; });
      os << ")";

      return os;
    }
  };

  //================================================================================================
  // CTAD and other helpers
  //================================================================================================
  template <typename... Ts> tuple(Ts&&...) -> tuple<std::remove_cvref_t<Ts>...>;

  template <typename... Ts>
  [[nodiscard]] constexpr tuple<Ts&...> tie(Ts&... ts)
  {
    return {ts...};
  }

  template <typename... Ts>
  [[nodiscard]] constexpr tuple<Ts&&...> forward_as_tuple(Ts&&... ts)
  {
    return {std::forward<Ts>(ts)...};
  }

  template <typename... Ts>
  [[nodiscard]] constexpr tuple<std::unwrap_ref_decay_t<Ts>...>  make_tuple(Ts&&... ts)
  {
    return {std::forward<Ts>(ts)...};
  }

  //================================================================================================
  // Implementation depending on make_tuple/tie
  //================================================================================================
  template<typename... Ts>
  template<typename Function, sized_product_type<sizeof...(Ts)>... Tuples>
  constexpr auto tuple<Ts...>::map(Function f, Tuples const&... others) const
  {
    return [&]<std::size_t... I>(std::index_sequence<I...>)
    {
      auto call = [&]<std::size_t N>(index_t<N>, auto const&... args)
                  {
                    return f(detail::get_leaf<N>(args.impl)...);
                  };

      return  make_tuple( call( index<I>, *this, others...)...);
    }(std::make_index_sequence<sizeof...(Ts)>());
  }

  template<typename... Ts>
  template<std::size_t I0>
  requires(I0 <= sizeof...(Ts))
  [[nodiscard]] constexpr auto tuple<Ts...>::split( index_t<I0> const&) const noexcept
  {
    return kumi::make_tuple(extract(index<0>,index<I0>), extract(index<I0>) );
  }

  template<typename... Ts>
  template<std::size_t I0>
  requires(I0 <= sizeof...(Ts))
  [[nodiscard]] constexpr auto tuple<Ts...>::split( index_t<I0> const&)  noexcept
  {
    return kumi::make_tuple(extract(index<0>,index<I0>), extract(index<I0>) );
  }

  //================================================================================================
  // Access
  //================================================================================================
  template<std::size_t I, typename... Ts>
  requires( I<sizeof...(Ts) )
  [[nodiscard]] constexpr decltype(auto) get(tuple<Ts...>& arg) noexcept
  {
    return arg[index<I>];
  }

  template<std::size_t I, typename... Ts>
  requires(I<sizeof...(Ts))
  [[nodiscard]] constexpr decltype(auto) get(tuple<Ts...> const& arg) noexcept
  {
    return arg[index<I>];
  }

  //================================================================================================
  // Free functions interface
  //================================================================================================
  template<typename Function, product_type Tuple>
  constexpr decltype(auto) apply(Function f, Tuple t)
  {
    return t.apply(f);
  }

  template<typename Function, product_type Tuple>
  constexpr decltype(auto) for_each(Function f, Tuple t)
  {
    return t.for_each(f);
  }

  template<typename Function, product_type Arg0, sized_product_type<Arg0{}.size()>... Args>
  constexpr auto map(Function f, Arg0 arg0, Args const&... others)
  {
    return arg0.map(f, others...);
  }

  template<product_type Head, product_type... Tail>
  [[nodiscard]] constexpr auto cat(Head const& h, Tail const&... ts )
  {
    return h.cat(ts...);
  }

  template<product_type T1, product_type T2>
  [[nodiscard]] constexpr auto operator|(T1&& t1, T2&& t2)
  {
    return std::forward<T1>(t1).cat(std::forward<T2>(t2));
  }
}

//==================================================================================================
// Structured binding adaptation
//==================================================================================================
namespace std
{
  template<std::size_t I, typename Head, typename... Tail>
  struct  tuple_element<I, kumi::tuple<Head, Tail...>>
        : tuple_element<I-1,kumi::tuple<Tail...>>
  {};

  template<typename Head, typename... Tail>
  struct  tuple_element<0, kumi::tuple<Head, Tail...>>
  {
    using type = Head;
  };

  template<typename... Ts>
  struct tuple_size<kumi::tuple<Ts...>> : std::integral_constant<std::size_t,sizeof...(Ts)>
  {};
}
