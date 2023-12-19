// Copyright (c) 2021-2023 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#include "test.hpp"
#include "test_utility.hpp"

namespace TAO_PEGTL_NAMESPACE
{
   void test_01_lazy()
   {
      using input_1 = lazy_view_input< ascii::lf >;
      {
         input_1 in( "" );
         TAO_PEGTL_TEST_ASSERT( test::equal( in.current_position(), 0, 1, 1 ) );
         TAO_PEGTL_TEST_ASSERT( parse< eof >( in ) );
         TAO_PEGTL_TEST_ASSERT( in.empty() );
         TAO_PEGTL_TEST_ASSERT( test::equal( in.current_position(), 0, 1, 1 ) );
      } {
         input_1 in( " " );
         TAO_PEGTL_TEST_ASSERT( test::equal( in.current_position(), 0, 1, 1 ) );
         TAO_PEGTL_TEST_ASSERT( parse< blank >( in ) );
         TAO_PEGTL_TEST_ASSERT( in.empty() );
         TAO_PEGTL_TEST_ASSERT( test::equal( in.current_position(), 1, 1, 2 ) );
      } {
         input_1 in( "\n" );
         TAO_PEGTL_TEST_ASSERT( test::equal( in.current_position(), 0, 1, 1 ) );
         TAO_PEGTL_TEST_ASSERT( parse< eol >( in ) );
         TAO_PEGTL_TEST_ASSERT( in.empty() );
         TAO_PEGTL_TEST_ASSERT( test::equal( in.current_position(), 1, 2, 1 ) );
      }
      using input_2 = lazy_view_input< ascii::cr_lf_crlf >;
      {
         input_2 in( "" );
         TAO_PEGTL_TEST_ASSERT( test::equal( in.current_position(), 0, 1, 1 ) );
         TAO_PEGTL_TEST_ASSERT( parse< eof >( in ) );
         TAO_PEGTL_TEST_ASSERT( test::equal( in.current_position(), 0, 1, 1 ) );
      } {
         input_2 in( " " );
         TAO_PEGTL_TEST_ASSERT( test::equal( in.current_position(), 0, 1, 1 ) );
         TAO_PEGTL_TEST_ASSERT( parse< blank >( in ) );
         TAO_PEGTL_TEST_ASSERT( test::equal( in.current_position(), 1, 1, 2 ) );
      } {
         input_2 in( "\n" );
         TAO_PEGTL_TEST_ASSERT( test::equal( in.current_position(), 0, 1, 1 ) );
         TAO_PEGTL_TEST_ASSERT( parse< eol >( in ) );
         TAO_PEGTL_TEST_ASSERT( test::equal( in.current_position(), 1, 2, 1 ) );
      } {
         input_2 in( "\r" );
         TAO_PEGTL_TEST_ASSERT( test::equal( in.current_position(), 0, 1, 1 ) );
         TAO_PEGTL_TEST_ASSERT( parse< eol >( in ) );
         TAO_PEGTL_TEST_ASSERT( test::equal( in.current_position(), 1, 2, 1 ) );
      } {
         input_2 in( "\r\n" );
         TAO_PEGTL_TEST_ASSERT( test::equal( in.current_position(), 0, 1, 1 ) );
         TAO_PEGTL_TEST_ASSERT( parse< eol >( in ) );
         TAO_PEGTL_TEST_ASSERT( test::equal( in.current_position(), 2, 2, 1 ) );
      } {
         input_2 in( "\n\r" );
         TAO_PEGTL_TEST_ASSERT( test::equal( in.current_position(), 0, 1, 1 ) );
         TAO_PEGTL_TEST_ASSERT( parse< eol >( in ) );
         TAO_PEGTL_TEST_ASSERT( parse< eol >( in ) );
         TAO_PEGTL_TEST_ASSERT( test::equal( in.current_position(), 2, 3, 1 ) );
      } {
         input_2 in( " \n " );
         TAO_PEGTL_TEST_ASSERT( test::equal( in.current_position(), 0, 1, 1 ) );
         TAO_PEGTL_TEST_ASSERT( parse< blank >( in ) );
         TAO_PEGTL_TEST_ASSERT( parse< eol >( in ) );
         TAO_PEGTL_TEST_ASSERT( parse< blank >( in ) );
         TAO_PEGTL_TEST_ASSERT( test::equal( in.current_position(), 3, 2, 2 ) );
      }
      using input_3 = lazy_view_input< ascii::lf >;
      {
         input_3 in( " \n " );
         TAO_PEGTL_TEST_ASSERT( test::equal( in.current_position(), 0, 1, 1 ) );
         TAO_PEGTL_TEST_ASSERT( parse< blank >( in ) );
         TAO_PEGTL_TEST_ASSERT( parse< one< '\n' > >( in ) );
         TAO_PEGTL_TEST_ASSERT( parse< blank >( in ) );
         TAO_PEGTL_TEST_ASSERT( test::equal( in.current_position(), 3, 2, 2 ) );
      }
   }

   void unit_test()
   {
      test_01_lazy();
   }

}  // namespace TAO_PEGTL_NAMESPACE

#include "main.hpp"
