// Copyright (c) 2018-2024 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_UINT32_HPP
#define TAO_PEGTL_UINT32_HPP

#include "config.hpp"

#include "internal/peek_integer.hpp"
#include "internal/rules.hpp"

namespace TAO_PEGTL_NAMESPACE
{
   namespace uint32_be
   {
      // clang-format off
      struct any : internal::any< internal::peek_uint32_be > {};
      template< unsigned Count > struct many : internal::many< Count, internal::peek_uint32_be > {};

      template< std::uint32_t... Cs > struct not_one : internal::not_one< internal::peek_uint32_be, Cs... > {};
      template< std::uint32_t Lo, std::uint32_t Hi > struct not_range : internal::not_range< internal::peek_uint32_be, Lo, Hi > {};
      template< std::uint32_t... Cs > struct one : internal::one< internal::peek_uint32_be, Cs... > {};
      template< std::uint32_t Lo, std::uint32_t Hi > struct range : internal::range< internal::peek_uint32_be, Lo, Hi > {};
      template< std::uint32_t... Cs > struct ranges : internal::ranges< internal::peek_uint32_be, Cs... > {};
      template< std::uint32_t... Cs > struct string : internal::seq_one< internal::peek_uint32_be, Cs... > {};

      template< std::uint32_t M, std::uint32_t... Cs > struct mask_not_one : internal::not_one< internal::peek_mask_uint32_be< M >, Cs... > {};
      template< std::uint32_t M, std::uint32_t Lo, std::uint32_t Hi > struct mask_not_range : internal::not_range< internal::peek_mask_uint32_be< M >, Lo, Hi > {};
      template< std::uint32_t M, std::uint32_t... Cs > struct mask_one : internal::one< internal::peek_mask_uint32_be< M >, Cs... > {};
      template< std::uint32_t M, std::uint32_t Lo, std::uint32_t Hi > struct mask_range : internal::range< internal::peek_mask_uint32_be< M >, Lo, Hi > {};
      template< std::uint32_t M, std::uint32_t... Cs > struct mask_ranges : internal::ranges< internal::peek_mask_uint32_be< M >, Cs... > {};
      template< std::uint32_t M, std::uint32_t... Cs > struct mask_string : internal::seq_one< internal::peek_mask_uint32_be< M >, Cs... > {};
      // clang-format on

   }  // namespace uint32_be

   namespace uint32_le
   {
      // clang-format off
      struct any : internal::any< internal::peek_uint32_le > {};
      template< unsigned Count > struct many : internal::many< Count, internal::peek_uint32_le > {};

      template< std::uint32_t... Cs > struct not_one : internal::not_one< internal::peek_uint32_le, Cs... > {};
      template< std::uint32_t Lo, std::uint32_t Hi > struct not_range : internal::not_range< internal::peek_uint32_le, Lo, Hi > {};
      template< std::uint32_t... Cs > struct one : internal::one< internal::peek_uint32_le, Cs... > {};
      template< std::uint32_t Lo, std::uint32_t Hi > struct range : internal::range< internal::peek_uint32_le, Lo, Hi > {};
      template< std::uint32_t... Cs > struct ranges : internal::ranges< internal::peek_uint32_le, Cs... > {};
      template< std::uint32_t... Cs > struct string : internal::seq_one< internal::peek_uint32_le, Cs... > {};

      template< std::uint32_t M, std::uint32_t... Cs > struct mask_not_one : internal::not_one< internal::peek_mask_uint32_le< M >, Cs... > {};
      template< std::uint32_t M, std::uint32_t Lo, std::uint32_t Hi > struct mask_not_range : internal::not_range< internal::peek_mask_uint32_le< M >, Lo, Hi > {};
      template< std::uint32_t M, std::uint32_t... Cs > struct mask_one : internal::one< internal::peek_mask_uint32_le< M >, Cs... > {};
      template< std::uint32_t M, std::uint32_t Lo, std::uint32_t Hi > struct mask_range : internal::range< internal::peek_mask_uint32_le< M >, Lo, Hi > {};
      template< std::uint32_t M, std::uint32_t... Cs > struct mask_ranges : internal::ranges< internal::peek_mask_uint32_le< M >, Cs... > {};
      template< std::uint32_t M, std::uint32_t... Cs > struct mask_string : internal::seq_one< internal::peek_mask_uint32_le< M >, Cs... > {};
      // clang-format on

   }  // namespace uint32_le

}  // namespace TAO_PEGTL_NAMESPACE

#endif
