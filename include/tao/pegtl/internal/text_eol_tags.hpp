// Copyright (c) 2021-2023 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_TEXT_EOL_TAGS_HPP
#define TAO_PEGTL_INTERNAL_TEXT_EOL_TAGS_HPP

#include "../config.hpp"

namespace TAO_PEGTL_NAMESPACE::internal
{
   struct eol_exclude_tag
   {};

   struct eol_matched_tag
   {};

   struct eol_unknown_tag
   {};

}  // namespace TAO_PEGTL_NAMESPACE::internal

#endif
