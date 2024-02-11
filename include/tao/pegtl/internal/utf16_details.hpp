// Copyright (c) 2024 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_UTF16_DETAILS_HPP
#define TAO_PEGTL_INTERNAL_UTF16_DETAILS_HPP

#include "../config.hpp"

#include "unicode_constants.hpp"

namespace TAO_PEGTL_NAMESPACE::internal
{
   [[nodiscard]] constexpr bool is_utf16_surrogate( const char32_t t ) noexcept
   {
      return ( minimum_surrogate <= t ) && ( t <= maximum_surrogate );
   }

   [[nodiscard]] constexpr bool is_utf16_high_surrogate( const char32_t t ) noexcept
   {
      return ( minimum_high_surrogate <= t ) && ( t <= maximum_high_surrogate );
   }

   [[nodiscard]] constexpr bool is_utf16_low_surrogate( const char32_t t ) noexcept
   {
      return ( minimum_low_surrogate <= t ) && ( t <= maximum_low_surrogate );
   }

   [[nodiscard]] constexpr bool utf16_needs_1_code_unit( const char32_t t ) noexcept
   {
      return t <= 0xffff;  // TODO: Exclude surrogates here?
   }

   [[nodiscard]] constexpr bool utf16_needs_2_code_units( const char32_t t ) noexcept
   {
      return ( 0x10000 <= t ) && ( t <= maximum_codepoint );
   }

   [[nodiscard]] constexpr char32_t utf16_surrogate_compose( const char16_t high, const char16_t low ) noexcept
   {
      return ( ( char32_t( high & 0x03ff ) << 10 ) | char32_t( low & 0x03ff ) ) + 0x10000;
   }

}  // namespace TAO_PEGTL_NAMESPACE::internal

#endif