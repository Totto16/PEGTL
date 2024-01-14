// Copyright (c) 2020-2024 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_VECTOR_STACK_GUARD_HPP
#define TAO_PEGTL_INTERNAL_VECTOR_STACK_GUARD_HPP

#include <utility>
#include <vector>

#include "../config.hpp"

namespace TAO_PEGTL_NAMESPACE::internal
{
   template< typename... Cs >
   class [[nodiscard]] vector_stack_guard
   {
   public:
      template< typename... Ts >
      vector_stack_guard( std::vector< Cs... >& vector, Ts&&... ts )
         : m_s( vector )
      {
         m_s.emplace_back( std::forward< Ts >( ts )... );
      }

      vector_stack_guard( vector_stack_guard&& ) = delete;
      vector_stack_guard( const vector_stack_guard& ) = delete;

      void operator=( vector_stack_guard&& ) = delete;
      void operator=( const vector_stack_guard& ) = delete;

      ~vector_stack_guard()
      {
         m_s.pop_back();
      }

   private:
      std::vector< Cs... >& m_s;
   };

   template< typename... Cs >
   vector_stack_guard( std::vector< Cs... >&, const typename std::vector< Cs... >::value_type& ) -> vector_stack_guard< Cs... >;

}  // namespace TAO_PEGTL_NAMESPACE::internal

#endif
