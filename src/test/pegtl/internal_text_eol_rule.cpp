// Copyright (c) 2023 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#include <cstddef>
#include <string>

#include "test.hpp"
#include "test_utility.hpp"

#include <tao/pegtl/text_position.hpp>
#include <tao/pegtl/internal/text_eol_rule.hpp>

namespace TAO_PEGTL_NAMESPACE
{
   template< typename Eol, typename Rule >
   void rule_test( const std::string& str, const std::size_t line, const std::size_t column, const std::size_t count )
   {
      text_position pos;
      internal::text_eol_rule< Eol, Rule >( pos, str.data(), str.size() );
      TAO_PEGTL_TEST_ASSERT( test::equal( pos, line, column, count ) );
   }

   void unit_test()
   {
      rule_test< eols::rule::lf, eol >( " ", 1, 2, 1 );
      rule_test< eols::rule::lf, eol >( "\n", 1, 2, 1 );

      rule_test< eols::rule::lf, eolf >( " ", 1, 2, 1 );
      rule_test< eols::rule::lf, eolf >( "\n", 1, 2, 1 );

      rule_test< eols::rule::lf, ascii::any8 >( " ", 1, 2, 1 );
      rule_test< eols::rule::lf, ascii::any8 >( "\n", 1, 2, 1 );

      rule_test< eols::rule::lf, ascii::many8< 3 > >( "xyz", 1, 4, 3 );
      rule_test< eols::rule::lf, ascii::many8< 30 > >( "xyz", 1, 4, 3 );
      rule_test< eols::rule::lf, ascii::many8< 3 > >( "\n\n\n", 1, 4, 3 );

      rule_test< eols::rule::lf, eol_matched_tag >( " ", 2, 1, 1 );
   }

}  // namespace TAO_PEGTL_NAMESPACE

#include "main.hpp"
