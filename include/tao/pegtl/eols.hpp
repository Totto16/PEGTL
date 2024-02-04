// Copyright (c) 2014-2024 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_EOLS_HPP
#define TAO_PEGTL_EOLS_HPP

#include "config.hpp"

#include "internal/ascii_string.hpp"
#include "internal/one.hpp"
#include "internal/peek_ascii8.hpp"
#include "internal/peek_unicode.hpp"
#include "internal/sor.hpp"

namespace TAO_PEGTL_NAMESPACE::eols
{
   namespace impl
   {
      using cr = internal::one< internal::peek_ascii8, '\r' >;  // Carriage Return
      using lf = internal::one< internal::peek_ascii8, '\n' >;  // Line Feed

      using ls = internal::one< internal::peek_unicode, char32_t( 0x2028 ) >;  // Line Separator
      using nel = internal::one< internal::peek_unicode, char32_t( 0x85 ) >;  // Next Line
      using ps = internal::one< internal::peek_unicode, char32_t( 0x2029 ) >;  // Paragraph Separator

      using crlf = internal::ascii_string< internal::identity_endian, '\r', '\n' >;
      using lfcr = internal::ascii_string< internal::identity_endian, '\n', '\r' >;

      using cr_lf = internal::one< internal::peek_ascii8, '\r', '\n' >;

      using unicode1 = internal::one< internal::peek_unicode, char32_t( '\r' ), char32_t( '\n' ), char32_t( '\v' ), char32_t( '\f' ), char32_t( 0x85 ), char32_t( 0x2028 ), char32_t( 0x2029 ) >;

   }  // namespace impl

   namespace rule
   {
      // clang-format off
      struct cr : impl::cr {};
      struct lf : impl::lf {};

      struct ls : impl::ls {};
      struct nel : impl::nel {};
      struct ps : impl::ps {};

      struct crlf : impl::crlf {};
      struct lfcr : impl::lfcr {};

      struct cr_lf : impl::cr_lf {};

      struct cr_crlf : internal::sor< impl::crlf, impl::cr > {};
      struct lf_crlf : internal::sor< impl::lf, impl::crlf > {};

      struct cr_lf_crlf : internal::sor< impl::crlf, impl::cr_lf > {};

      struct unicode : internal::sor< impl::crlf, impl::unicode1 > {};
      // clang-format on
   }  // namespace rule

   namespace scan
   {
      // clang-format off
      struct cr : impl::cr { static constexpr char eol_char = '\r'; };
      struct lf : impl::lf { static constexpr char eol_char = '\n'; };

      struct cr_crlf : internal::sor< impl::crlf, impl::cr > { static constexpr char eol_char = '\r'; };
      struct lf_crlf : internal::sor< impl::lf, impl::crlf > { static constexpr char eol_char = '\n'; };
      // clang-format on
   }  // namespace scan

}  // namespace TAO_PEGTL_NAMESPACE::eols

#endif