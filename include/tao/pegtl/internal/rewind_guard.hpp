// Copyright (c) 2014-2023 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_REWIND_GUARD_HPP
#define TAO_PEGTL_INTERNAL_REWIND_GUARD_HPP

#include <type_traits>
#include <utility>

#include "../config.hpp"
#include "../rewind_mode.hpp"

namespace TAO_PEGTL_NAMESPACE::internal
{
   template< rewind_mode, typename ParseInput >
   class rewind_guard;

   template< typename ParseInput >
   class rewind_guard< rewind_mode::optional, ParseInput >
   {
   public:
      explicit rewind_guard( ParseInput* /*unused*/ ) noexcept
      {}

      rewind_guard( rewind_guard&& ) = delete;
      rewind_guard( const rewind_guard& ) = delete;

      ~rewind_guard() = default;

      void operator=( rewind_guard&& ) = delete;
      void operator=( const rewind_guard& ) = delete;

      [[nodiscard]] bool operator()( const bool result ) const noexcept
      {
         return result;
      }
   };

   template< typename ParseInput >
   class rewind_guard< rewind_mode::required, ParseInput >
   {
   public:
      using rewind_data = std::decay_t< decltype( std::declval< ParseInput >().rewind_save() ) >;

      explicit rewind_guard( ParseInput* in ) noexcept
         : m_input( in ),
           m_saved( in->rewind_save() )
      {}

      rewind_guard( rewind_guard&& ) = delete;
      rewind_guard( const rewind_guard& ) = delete;

      ~rewind_guard()
      {
         if( m_input != nullptr ) {
            m_input->rewind_restore( std::move( m_saved ) );
         }
      }

      void operator=( rewind_guard&& ) = delete;
      void operator=( const rewind_guard& ) = delete;

      [[nodiscard]] bool operator()( const bool result ) noexcept
      {
         if( result ) {
            m_input = nullptr;
            return true;
         }
         return false;
      }

      [[nodiscard]] const rewind_data& inputerator() const noexcept
      {
         return m_saved;
      }

   private:
      ParseInput* m_input;
      rewind_data m_saved;
   };

}  // namespace TAO_PEGTL_NAMESPACE::internal

#endif
