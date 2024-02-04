// Copyright (c) 2023-2024 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_INTEGER_ADAPT_HPP
#define TAO_PEGTL_INTERNAL_INTEGER_ADAPT_HPP

#include <cstring>
#include <type_traits>

#include "../config.hpp"

#include "dependent_false.hpp"

namespace TAO_PEGTL_NAMESPACE::internal
{
   template< typename Type, typename Data >
   [[nodiscard]] Type integer_adapt( const Data* pointer ) noexcept
   {
      static_assert( std::is_integral_v< Type > || std::is_enum_v< Type > );
      static_assert( std::is_integral_v< Data > || std::is_enum_v< Data > );

      if constexpr( sizeof( Type ) == sizeof( Data ) ) {
         return static_cast< Type >( *pointer );
      }
      else if constexpr( sizeof( Data ) == 1 ) {
         Type result;
         std::memcpy( &result, pointer, sizeof( result ) );
         return result;
      }
      else {
         static_assert( dependent_false< Type, Data > );
      }
   }

}  // namespace TAO_PEGTL_NAMESPACE::internal

#endif