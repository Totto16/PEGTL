// Copyright (c) 2017-2024 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#if !defined( __cpp_exceptions )
#include <iostream>
int main()
{
   std::cerr << "Exception support required, example unavailable." << std::endl;
   return 1;
}
#else

#include <iomanip>

#include <tao/pegtl.hpp>
#include <tao/pegtl/analyze.hpp>

#include "proto3.hpp"

int main( int argc, char** argv )  // NOLINT(bugprone-exception-escape)
{
   using namespace TAO_PEGTL_NAMESPACE;

   if( analyze< proto3::proto >() != 0 ) {
      return 1;
   }

   for( int i = 1; i < argc; ++i ) {
      text_file_input< eols::scan::lf_crlf > in( argv[ i ] );
      try {
         parse< proto3::proto >( in );
      }
      catch( const parse_error< text_position >& e ) {
         const auto& p = e.position_object();
         std::cerr << e.what() << '\n'
                   << line_view_at( in, p ) << '\n'
                   << std::setw( int( p.column ) ) << '^' << '\n';
      }
   }
   return 0;
}

#endif
