// Copyright (c) 2023 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_TEXT_EOL_SCAN_HPP
#define TAO_PEGTL_INTERNAL_TEXT_EOL_SCAN_HPP

#include "../config.hpp"

#include "text_scan_traits.hpp"

namespace TAO_PEGTL_NAMESPACE::internal
{
   template< typename Eol, typename Rule, typename Position, typename Data >
   void text_eol_scan( Position& pos, const Data* data, const std::size_t count )
   {
      text_scan_traits< Eol, Rule >::scan( pos, data, count );
   }

}  // namespace TAO_PEGTL_NAMESPACE::internal

#endif
