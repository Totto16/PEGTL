// Copyright (c) 2016-2023 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_EOL_HPP
#define TAO_PEGTL_INTERNAL_EOL_HPP

#include "../apply_mode.hpp"
#include "../config.hpp"
#include "../rewind_mode.hpp"
#include "../type_list.hpp"

#include "enable_control.hpp"

namespace TAO_PEGTL_NAMESPACE::internal
{
   template< typename Eol >
   struct eol
   {
      using rule_t = eol;
      using subs_t = empty_list;  // TODO?

      template< apply_mode A,
                rewind_mode M,
                template< typename... >
                class Action,
                template< typename... >
                class Control,
                typename ParseInput,
                typename... States >
      [[nodiscard]] static bool match( ParseInput& in, States&&... st )
      {
         using eol_impl = typename Eol::rule_t;
         return Control< eol_impl >::template match< apply_mode::nothing, M, Action, Control >( in, st... );
      }
   };

   template<>
   struct eol< void >
   {
      using rule_t = eol;
      using subs_t = empty_list;

      template< apply_mode A,
                rewind_mode M,
                template< typename... >
                class Action,
                template< typename... >
                class Control,
                typename ParseInput,
                typename... States >
      [[nodiscard]] static bool match( ParseInput& in, States&&... st )
      {
         using eol_rule = typename ParseInput::eol_rule;
         using eol_impl = typename eol_rule::rule_t;
         return Control< eol_impl >::template match< apply_mode::nothing, M, Action, Control >( in, st... );
      }
   };

   template< typename Eol >
   inline constexpr bool enable_control< eol< Eol > > = false;

}  // namespace TAO_PEGTL_NAMESPACE::internal

#endif
