//==================================================================================================
/**
  RABERU - Fancy Parameters Library
  Copyright : OFW Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <type_traits>
#include <utility>

#define RBR_FWD(...) static_cast<decltype(__VA_ARGS__) &&>(__VA_ARGS__)

namespace rbr
{
  // Lightweight container of value
  template<typename T, typename V> struct type_or_
  {
    V value;
  };

  template<typename... KWs> struct either_
  {
  };

  // Basic checker for keyword constraints
  struct any_type
  {
    template<typename T> struct check : std::true_type {};
  };

  // Turn any type into a RegularType info carrier
  template<typename T, typename C = any_type> struct keyword_type
  {
    using type                                  = keyword_type<T,C>;
    template<typename V>
    requires( C::template check<V>::value )
    constexpr auto operator=(V &&v) const noexcept;

    template<typename V> constexpr auto operator|(V &&value) const noexcept
    {
      return type_or_<type, V> {RBR_FWD(value)};
    }

    template<typename U, typename K> constexpr auto operator|(keyword_type<U,K>) const noexcept
    {
      return either_<keyword_type<T,C>, keyword_type<U,K>> {};
    }

    template<typename... Kws>
    friend constexpr auto operator|(either_<Kws...>, keyword_type) noexcept
    {
      return either_<Kws..., keyword_type<T,C>> {};
    }

    template<typename... Kws>
    friend constexpr auto operator|(keyword_type, either_<Kws...>) noexcept
    {
      return either_<keyword_type<T,C>, Kws...> {};
    }
  };

  // Keyword_type generator
  template<typename T, typename C = any_type>
  inline constexpr const keyword_type<T,C> keyword = {};

  // Flag-like keyword parameter
  template<typename T> struct flag_type
  {
    static constexpr bool is_parameter_type     = true;
    using key_type                              = flag_type<T>;
    using type                                  = flag_type<T>;

    template<typename V> constexpr auto operator|(V &&value) const noexcept
    {
      return type_or_<type, V> {RBR_FWD(value)};
    }

    template<typename U> constexpr auto operator|(flag_type<U>) const noexcept
    {
      return either_<flag_type<T>, flag_type<U>> {};
    }

    template<typename... Kws>
    friend constexpr auto operator|(either_<Kws...>, flag_type) noexcept
    {
      return either_<Kws..., flag_type<T>> {};
    }

    template<typename... Kws>
    friend constexpr auto operator|(flag_type, either_<Kws...>) noexcept
    {
      return either_<flag_type<T>, Kws...> {};
    }

    constexpr std::true_type operator()(flag_type<T> const&) noexcept { return {}; }
  };

  // Flag_type generator
  template<typename T> inline constexpr const flag_type<T> flag = {};

  // Keyword/Flag-type user defined literals
  namespace literals
  {
    template<char... Char> struct id_
    {
    };

    template<typename T, T... Chars> constexpr auto operator""_kw() noexcept
    {
      return rbr::keyword<id_<Chars...>>;
    }

    template<typename T, T... Chars> constexpr auto operator""_fl() noexcept
    {
      return rbr::flag<id_<Chars...>>;
    }
  }

  namespace detail
  {
    // Turn a Type+Value pair into a Callable
    template<typename Key, typename Callable> struct linked_value : Callable
    {
      static constexpr bool is_parameter_type = true;
      using key_type                          = Key;

      constexpr linked_value(Key, Callable f) noexcept : Callable(f) {}
      using Callable::operator();
    };
  }

  // keyword parameter concept
  template<typename T> concept keyword_parameter = std::remove_cvref_t<T>::is_parameter_type;

  // Type notifying that we can't find a given key
  struct unknown_key
  {
    template<typename... T> unknown_key(T &&...) {}
  };

  namespace detail
  {
    // Build the type->value lambda capture
    template<typename Key, typename T> constexpr auto link(T &&v) noexcept
    {
      if constexpr( keyword_parameter<std::decay_t<T>> )
      {
        return RBR_FWD(v);
      }
      else if constexpr( std::is_lvalue_reference_v<T> )
      {
        return linked_value(
            Key {}, [&v](Key const &) constexpr->decltype(auto) { return v; });
      }
      else
      {
        return linked_value(
            Key {}, [w = std::move(v)](Key const &) constexpr->T const & { return w; });
      }
    }

    // Check if the key we used is correct
    template<typename T> inline constexpr bool is_unknown_v              = false;
    template<> inline constexpr bool           is_unknown_v<unknown_key> = true;

    // Aggregate lambdas and give them a operator(Key)-like interface
    template<typename... Ts> struct aggregator : Ts...
    {
      constexpr aggregator(Ts &&...t) noexcept : Ts(RBR_FWD(t))... {}
      using Ts::operator()...;

      template<typename K, typename C>
      constexpr auto operator()(keyword_type<K,C> const &) const noexcept
      {
        // If not found before, return the unknown_key value
        return unknown_key {};
      }

      template<typename K> constexpr auto operator()(flag_type<K> const &) const noexcept
      {
        // If not found before, return the unknown_key value
        return unknown_key {};
      }
    };
  }

  // Build a key-value from an option object
  template<typename T, typename C>
  template<typename V>
  requires( C::template check<V>::value )
  constexpr auto keyword_type<T,C>::operator=(V &&v) const noexcept
  {
    return detail::link<keyword_type<T,C>>(RBR_FWD(v));
  }

  // Extract tag from an Option
  template<typename O> struct tag
  {
    using type = keyword_type<O>;
  };

  template<typename O, typename C> struct tag<keyword_type<O,C>>
  {
    using type = keyword_type<O,C>;
  };

  template<typename O> struct tag<flag_type<O>>
  {
    using type = flag_type<O>;
  };

  template<typename K, typename C> struct tag<detail::linked_value<K, C>>
  {
    using type = K;
  };

  template<typename O> using tag_t = typename tag<O>::type;

  template<typename...> struct keys
  {
  };
  template<typename...> struct links
  {
  };

  // settings is an unordered set of values accessible via their types
  template<typename Keys, typename Links> struct settings;

  template<typename... Ks, typename... Ts> struct settings<keys<Ks...>, links<Ts...>>
  {
    using keys_type  = keys<Ks...>;
    using links_type = links<Ks...>;
    using parent     = detail::aggregator<Ts...>;

    template<typename... Vs>
    constexpr settings(Vs &&...v) : content_(detail::link<Ks>(RBR_FWD(v))...)
    {
    }

    static constexpr std::ptrdiff_t size() noexcept { return sizeof...(Ts); }

    // Named options interface
    template<typename T, typename C>
    static constexpr auto contains(keyword_type<T,C> const &) noexcept
    {
      using found = decltype(std::declval<parent>()(tag_t<T> {}));
      return std::bool_constant<!detail::is_unknown_v<found>>{};
    }

    template<typename T> static constexpr auto contains(flag_type<T> const &) noexcept
    {
      using found = decltype(std::declval<parent>()(flag_type<T> {}));
      return std::bool_constant<!detail::is_unknown_v<found>>{};
    }

    template<typename T, typename C>
    constexpr decltype(auto) operator[](keyword_type<T,C> const &tgt) const noexcept
    {
      return content_(tgt);
    }

    template<typename T>
    constexpr auto operator[](flag_type<T> const &tgt) const noexcept
    {
      return contains(tgt);
    }

    template<typename T, typename V>
    constexpr decltype(auto) operator[](type_or_<T, V> const &tgt) const
    {
            if constexpr( contains(T{}) )             return (*this)[T{}];
      else  if constexpr( std::is_invocable_v<V, T> ) return tgt.value(T{});
      else                                            return tgt.value;
    }

    // Pattern matcher
    template<typename... KW> static inline constexpr bool validate(either_<KW...> const &) noexcept
    {
      auto is_ok = []<typename K>(K) { return (std::same_as<K, KW> || ... || false); };
      return (is_ok(Ks {}) && ... && true);
    }

    template<typename K, typename C>
    static inline constexpr bool validate(keyword_type<K,C> const &) noexcept
    {
      return (std::same_as<Ks, keyword_type<K>> && ... && true);
    }

    template<typename K> static inline constexpr bool validate(flag_type<K> const &) noexcept
    {
      return (std::same_as<Ks, flag_type<K>> && ... && true);
    }

    parent content_;
  };

  template<typename... Vs>
  settings(Vs &&...v)
      -> settings<keys<tag_t<std::decay_t<Vs>>...>,
                  links<decltype(detail::link<tag_t<std::decay_t<Vs>>>(RBR_FWD(v)))...>>;

  // Pattern matcher entry point
  template<typename... Args> struct match
  {
    template<typename Pattern> static inline constexpr bool with(Pattern p)
    {
      return decltype(rbr::settings {std::declval<Args>()...})::validate(p);
    }
  };

  // keyword parameter exact match concept
  template<typename Param, auto Keyword> concept exactly = rbr::match<Param>::with(Keyword);

  // Traits to fetch type of an option from the type of a Settings
  template<typename Settings, auto Keyword, typename Default = unknown_key>
  struct get_type
  {
    using base = std::remove_cvref_t<decltype( std::declval<Settings>()[Keyword])>;
    using type = std::conditional_t< std::same_as<base,unknown_key>, Default, base>;
  };

  template<typename Settings, auto Keyword>
  struct get_type<Settings,Keyword>
  {
    using type = std::remove_cvref_t<decltype( std::declval<Settings>()[Keyword])>;
  };

  template<typename Settings, auto Keyword, typename Default = unknown_key>
  using get_type_t = typename get_type<Settings,Keyword,Default>::type;
}

#undef RBR_FWD
