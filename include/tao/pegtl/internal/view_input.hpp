// Copyright (c) 2014-2024 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_VIEW_INPUT_HPP
#define TAO_PEGTL_INTERNAL_VIEW_INPUT_HPP

#include <array>
#include <cstddef>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

#include "../config.hpp"
#include "../pointer_position.hpp"

#include "rewind_guard.hpp"

namespace TAO_PEGTL_NAMESPACE::internal
{
   template< typename Data >
   class view_input
   {
   public:
      using data_t = Data;
      using error_position_t = pointer_position< data_t >;
      using offset_position_t = void;
      using rewind_position_t = pointer_position< data_t >;

      view_input( const data_t* in_begin, const data_t* in_end ) noexcept
         : m_current( in_begin ),
           m_end( in_end )
      {}

      view_input( const data_t* in_begin, const std::size_t in_size ) noexcept
         : view_input( in_begin, in_begin + in_size )
      {}

      view_input( std::string&& ) = delete;
      view_input( const std::string&& ) = delete;

      explicit view_input( std::string& data ) noexcept
         : view_input( const_cast< const std::string& >( data ) )
      {
         static_assert( std::is_same_v< data_t, char > );  // TODO: Or reinterpret_cast for sizeof( data_t ) == 1 instead?
      }

      explicit view_input( const std::string& data ) noexcept
         : view_input( data.data(), data.size() )
      {
         static_assert( std::is_same_v< data_t, char > );  // TODO: Or reinterpret_cast for sizeof( data_t ) == 1 instead?
      }

      explicit view_input( const std::string_view data ) noexcept
         : view_input( data.data(), data.size() )
      {
         static_assert( std::is_same_v< data_t, char > );  // TODO: Or reinterpret_cast for sizeof( data_t ) == 1 instead?
      }

      view_input( std::vector< data_t >&& ) = delete;
      view_input( const std::vector< data_t >&& ) = delete;

      explicit view_input( std::vector< data_t >& data ) noexcept
         : view_input( const_cast< const std::vector< data_t >& >( data ) )
      {}

      explicit view_input( const std::vector< data_t >& data ) noexcept
         : view_input( data.data(), data.size() )
      {}

      template< std::size_t N >
      explicit view_input( const char ( &in_literal )[ N ] ) noexcept
         : view_input( in_literal, N - 1 )
      {
         static_assert( std::is_same_v< data_t, char > );  // TODO: Or reinterpret_cast for sizeof( data_t ) == 1 instead?
      }

      template< std::size_t Size >
      explicit view_input( const std::array< data_t, Size >& in_array ) noexcept
         : view_input( in_array.data(), in_array.size() )
      {}

      [[nodiscard]] bool empty() const noexcept
      {
         return size() == 0;
      }

      [[nodiscard]] std::size_t size() const noexcept
      {
         return m_end - m_current;
      }

      [[nodiscard]] const data_t* current( const std::size_t offset = 0 ) const noexcept
      {
         return m_current + offset;
      }

      // [[nodiscard]] const data_t* previous( const error_position_t saved ) const noexcept

      [[nodiscard]] const data_t* previous( const rewind_position_t saved ) const noexcept
      {
         return saved.data;
      }

      [[nodiscard]] const data_t* end() const noexcept
      {
         return m_end;
      }

      template< typename Rule >
      void consume( const std::size_t count ) noexcept
      {
         m_current += count;
      }

      template< rewind_mode M >
      [[nodiscard]] auto make_rewind_guard() noexcept
      {
         return rewind_guard< M, view_input >( this );
      }

      [[nodiscard]] auto rewind_position() const noexcept
      {
         return rewind_position_t( m_current );
      }

      void rewind_to_position( const rewind_position_t saved ) noexcept
      {
         m_current = saved.data;
      }

      [[nodiscard]] auto current_position() const noexcept
      {
         return error_position_t( m_current );
      }

      [[nodiscard]] auto previous_position( const rewind_position_t saved ) const noexcept
      {
         return saved;  // error_position_t
      }

      void private_set_current( const data_t* in_current ) noexcept
      {
         m_current = in_current;
      }

      void private_set_end( const data_t* in_end ) noexcept
      {
         m_end = in_end;
      }

   protected:
      const data_t* m_current;
      const data_t* m_end;
   };

}  // namespace TAO_PEGTL_NAMESPACE::internal

#endif