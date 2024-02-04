// Copyright (c) 2023-2024 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_SRC_TEST_PEGTL_TEST_UTILITY_HPP
#define TAO_PEGTL_SRC_TEST_PEGTL_TEST_UTILITY_HPP

#include <cstddef>
#include <iostream>
#include <string>

#include <tao/pegtl/eols.hpp>
#include <tao/pegtl/inputs.hpp>

#include <tao/pegtl/count_position.hpp>
#include <tao/pegtl/pointer_position.hpp>
#include <tao/pegtl/text_position.hpp>

namespace TAO_PEGTL_NAMESPACE::test
{
   template< typename Data >
   [[nodiscard]] const Data* rewind_adapt( const Data* start, const count_position c ) noexcept
   {
      return start + c.count;
   }

   template< typename Data >
   [[nodiscard]] const Data* rewind_adapt( const Data* /*unused*/, const pointer_position< Data > p ) noexcept
   {
      return p.data;
   }

   template< typename T >
   [[nodiscard]] bool equal( const T& position, const std::size_t line, const std::size_t column, const std::size_t count ) noexcept
   {
      if( ( position.count == count ) && ( position.line == line ) && ( position.column == column ) ) {
         return true;
      }
      const text_position reference( count, line, column );
      std::cerr << "Not equal position " << position << " reference " << reference << std::endl;
      return false;
   }

   [[nodiscard]] std::string endless( const std::string& data, const std::size_t offset, const std::size_t count )
   {
      std::string t;

      while( t.size() < ( offset + count ) ) {
         t += data;
      }
      return t.substr( offset, count );
   }

}  // namespace TAO_PEGTL_NAMESPACE::test

#endif