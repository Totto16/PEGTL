// Copyright (c) 2023-2024 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#include "test.hpp"

#include <tao/pegtl/internal/has_eol_char_rule.hpp>

namespace TAO_PEGTL_NAMESPACE
{
   void unit_test()
   {
      static_assert( internal::has_eol_char_rule< eols::scan::lf > );
      static_assert( internal::has_eol_char_rule< eols::scan::cr_crlf > );
      static_assert( !internal::has_eol_char_rule< ascii::lf > );
      static_assert( !internal::has_eol_char_rule< utf8::crlf > );
   }

}  // namespace TAO_PEGTL_NAMESPACE

#include "main.hpp"
