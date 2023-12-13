// Copyright (c) 2019-2023 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#include "test.hpp"
#include "test_inputs.hpp"

#include <tao/pegtl/ascii.hpp>
#include <tao/pegtl/change_action_and_states.hpp>
#include <tao/pegtl/parse.hpp>
#include <tao/pegtl/rules.hpp>

namespace TAO_PEGTL_NAMESPACE
{
   // clang-format off
   struct A : one< 'a' > {};
   struct B : one< 'b' > {};
   struct AB : seq< A, B > {};
   // clang-format on

   template< typename >
   struct my_action_1
   {};

   template< typename >
   struct my_action_2
   {};

   template<>
   struct my_action_1< A >
   {
      static void apply0( int& c )
      {
         TAO_PEGTL_TEST_ASSERT( c == 0 );
         c = 1;
      }
   };

   template<>
   struct my_action_1< B >
      : change_action_and_states< my_action_2, int >
   {
      // not called because my_action_2 is active
      static void apply0( int& /*v*/ )
      {
         TAO_PEGTL_TEST_UNREACHABLE;
      }

      template< typename ParseInput >
      static void success( const ParseInput& /*unused*/, int& v, int& c )
      {
         TAO_PEGTL_TEST_ASSERT( v == 2 );
         TAO_PEGTL_TEST_ASSERT( c == 1 );
         c = 3;
      }
   };

   template<>
   struct my_action_2< A >
   {
      static void apply0( int& /*c*/ )
      {
         TAO_PEGTL_TEST_UNREACHABLE;
      }
   };

   template<>
   struct my_action_2< B >
   {
      static void apply0( int& v )
      {
         TAO_PEGTL_TEST_ASSERT( v == 0 );
         v = 2;
      }
   };

   void unit_test()
   {
      {
         test::text_input< ascii::lf > in( "ab" );
         int c = 0;
         const auto result = parse< AB, my_action_1 >( in, c );
         TAO_PEGTL_TEST_ASSERT( result );
         TAO_PEGTL_TEST_ASSERT( c == 3 );
      }
      {
         test::text_input< ascii::lf > in( "a" );
         int c = 0;
         const auto result = parse< AB, my_action_1 >( in, c );
         TAO_PEGTL_TEST_ASSERT( !result );
         TAO_PEGTL_TEST_ASSERT( c == 1 );
      }
      {
         test::text_input< ascii::lf > in( "b" );
         int c = 0;
         const auto result = parse< AB, my_action_1 >( in, c );
         TAO_PEGTL_TEST_ASSERT( !result );
         TAO_PEGTL_TEST_ASSERT( c == 0 );
      }
      {
         test::text_input< ascii::lf > in( "ab" );
         int c = 5;
         const auto result = parse< disable< AB >, my_action_1 >( in, c );
         TAO_PEGTL_TEST_ASSERT( result );
         TAO_PEGTL_TEST_ASSERT( c == 5 );
      }
   }

}  // namespace TAO_PEGTL_NAMESPACE

#include "main.hpp"
