// Copyright (c) 2023-2024 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#include "test.hpp"

#include <tao/pegtl/internal/input_traits.hpp>

namespace TAO_PEGTL_NAMESPACE
{
   void unit_test()
   {
      static_assert( internal::input_traits< base_input< eols::scan::lf > >::is_lazy == false );
      static_assert( internal::input_traits< base_input< eols::scan::lf > >::is_text == false );
   }

}  // namespace TAO_PEGTL_NAMESPACE

#include "main.hpp"
