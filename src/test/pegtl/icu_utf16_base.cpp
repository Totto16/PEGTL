// Copyright (c) 2020-2024 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#include "test.hpp"
#include "verify_meta.hpp"
#include "verify_rule.hpp"

#include <tao/pegtl/icu/utf16.hpp>

namespace TAO_PEGTL_NAMESPACE
{
   void unit_test()
   {
      // verify_analyze< utf16::icu::alphabetic >( __LINE__, __FILE__, true, false );

      // verify_rule< utf16::icu::alphabetic >( __LINE__, __FILE__, "", result_type::local_failure, 0 );
      // verify_rule< utf16::icu::alphabetic >( __LINE__, __FILE__, std::string( "a", 2 ), result_type::success );  // LE
   }

}  // namespace TAO_PEGTL_NAMESPACE

#include "main.hpp"