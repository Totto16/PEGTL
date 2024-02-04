// Copyright (c) 2018-2024 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INT8_HPP
#define TAO_PEGTL_INT8_HPP

#include "config.hpp"

#include "internal/peek_direct.hpp"
#include "internal/rules.hpp"

namespace TAO_PEGTL_NAMESPACE::int8
{
   // clang-format off
   struct any : internal::any< internal::peek_int8 > {};
   template< unsigned Count > struct many : internal::many< Count, internal::peek_int8 > {};

   template< std::int8_t... Cs > struct not_one : internal::not_one< internal::peek_int8, Cs... > {};
   template< std::int8_t Lo, std::int8_t Hi > struct not_range : internal::not_range< internal::peek_int8, Lo, Hi > {};
   template< std::int8_t... Cs > struct one : internal::one< internal::peek_int8, Cs... > {};
   template< std::int8_t Lo, std::int8_t Hi > struct range : internal::range< internal::peek_int8, Lo, Hi > {};
   template< std::int8_t... Cs > struct ranges : internal::ranges< internal::peek_int8, Cs... > {};
   template< std::int8_t... Cs > struct string : internal::seq_one< internal::peek_int8, Cs... > {};
   // clang-format on

}  // namespace TAO_PEGTL_NAMESPACE::int8

#endif