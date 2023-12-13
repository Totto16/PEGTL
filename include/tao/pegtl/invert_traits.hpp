// Copyright (c) 2023 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INVERT_TRAITS_HPP
#define TAO_PEGTL_INVERT_TRAITS_HPP

#include "config.hpp"
#include "forward.hpp"

#include "internal/any.hpp"
#include "internal/enum_invert_bool.hpp"
#include "internal/failure.hpp"
#include "internal/one.hpp"
#include "internal/range.hpp"
#include "internal/result_on_found.hpp"

namespace TAO_PEGTL_NAMESPACE
{
   template<>
   struct invert_traits< internal::failure >
   {
      // Unfortunately at this point we don't know what Peek was and have to skip this corner case for the time being.
   };

   template< typename Peek >
   struct invert_traits< internal::any< Peek > >
   {
      using rule_t = internal::failure;
   };

   template< internal::result_on_found R, typename Peek, typename Peek::data_t... Cs >
   struct invert_traits< internal::one< R, Peek, Cs... > >
   {
      using rule_t = internal::one< internal::enum_invert_bool( R ), Peek, Cs... >;
   };

   template< internal::result_on_found R, typename Peek, typename Peek::data_t Lo, typename Peek::data_t Hi >
   struct invert_traits< internal::range< R, Peek, Lo, Hi > >
   {
      using rule_t = internal::range< internal::enum_invert_bool( R ), Peek, Lo, Hi >;
   };

}  // namespace TAO_PEGTL_NAMESPACE

#endif
