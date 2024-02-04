// Copyright (c) 2023-2024 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INTERNAL_INPUT_TRAITS_HPP
#define TAO_PEGTL_INTERNAL_INPUT_TRAITS_HPP

#include <string>

#include "../config.hpp"

#include "inputs.hpp"

namespace TAO_PEGTL_NAMESPACE::internal
{
   template< typename Input, typename = void >
   struct input_traits;

   // TODO: Find a better structure than a kitchen sink full of bools?

   template< typename Data >
   struct input_traits< view_input< Data > >
   {
      static constexpr bool is_argv = false;
      static constexpr bool is_copy = false;
      static constexpr bool is_file = false;
      static constexpr bool is_lazy = false;
      static constexpr bool is_mmap = false;
      static constexpr bool is_read = false;
      static constexpr bool is_text = false;
      static constexpr bool is_view = true;

      static constexpr bool has_fakes = false;
      static constexpr bool has_peeks = false;
      static constexpr bool has_lines = false;
      static constexpr bool has_start = false;
      static constexpr bool has_source = false;
      static constexpr bool has_offset = false;
   };

   template< typename Container >
   struct input_traits< copy_input< Container > >
   {
      static constexpr bool is_argv = false;
      static constexpr bool is_copy = true;
      static constexpr bool is_file = false;
      static constexpr bool is_lazy = false;
      static constexpr bool is_mmap = false;
      static constexpr bool is_read = false;
      static constexpr bool is_text = false;
      static constexpr bool is_view = false;

      static constexpr bool has_fakes = false;
      static constexpr bool has_peeks = false;
      static constexpr bool has_lines = false;
      static constexpr bool has_start = true;
      static constexpr bool has_source = false;
      static constexpr bool has_offset = false;
   };

   template<>
   struct input_traits< argv_input >
      : input_traits< view_input< char > >
   {
      static constexpr bool is_argv = true;
   };

   template<>
   struct input_traits< read_input >
      : input_traits< copy_input< std::string > >
   {
      static constexpr bool is_read = true;
   };

#if defined( TAO_PEGTL_MMAP_AVAILABLE )

   template< typename Data >
   struct input_traits< mmap_input< Data > >
   {
      static constexpr bool is_mmap = true;
   };

   template<>
   struct input_traits< file_input >
      : input_traits< mmap_input< char > >
   {
      static constexpr bool is_file = true;
   };

#else

   template<>
   struct input_traits< file_input >
      : input_traits< read_input >
   {
      static constexpr bool is_file = true;
   };

#endif

   template< typename Eol, typename Input >
   struct input_traits< lazy_input< Eol, Input > >
      : input_traits< Input >
   {
      static constexpr bool is_lazy = true;
      static constexpr bool has_lines = true;
   };

   template< typename Eol, typename Input >
   struct input_traits< text_input< Eol, Input > >
      : input_traits< Input >
   {
      static constexpr bool is_text = true;
      static constexpr bool has_lines = true;
   };

   template< typename Input >
   struct input_traits< input_with_fakes< Input > >
      : input_traits< Input >
   {
      static constexpr bool has_fakes = true;
   };

   template< typename Input >
   struct input_traits< input_with_peeks< Input > >
      : input_traits< Input >
   {
      static constexpr bool has_peeks = true;
   };

   template< typename Input >
   struct input_traits< input_with_funcs< Input > >
      : input_traits< input_with_fakes< input_with_peeks< Input > > >
   {};

   template< typename Eol, typename Input >
   struct input_traits< input_with_lines< Eol, Input > >
      : input_traits< Input >
   {
      static constexpr bool has_lines = true;
   };

   template< typename Input >
   struct input_traits< input_with_lines< void, Input > >
      : input_traits< Input >
   {};

   template< typename InputSource, typename ErrorSource, typename Input >
   struct input_traits< input_with_source< InputSource, ErrorSource, Input > >
      : input_traits< Input >
   {
      static constexpr bool has_source = true;
   };

   template< typename Input >
   struct input_traits< input_with_source< void, void, Input > >
      : input_traits< Input >
   {};

   template< typename Input >
   struct input_traits< input_with_start< Input > >
      : input_traits< Input >
   {
      static constexpr bool has_start = true;
   };

   template< typename Input >
   struct input_traits< input_with_offset< true, Input > >
      : input_traits< Input >
   {
      static constexpr bool has_offset = true;
   };

   template< typename Input >
   struct input_traits< input_with_offset< false, Input > >
      : input_traits< Input >
   {};

   template< typename Input >
   struct input_traits< input_double_path< Input > >
      : input_traits< Input >
   {};

   template<>
   struct input_traits< argv_input_with_source< std::string > >
      : input_traits< input_with_source< std::string, std::string, argv_input > >
   {};

   template<>
   struct input_traits< argv_input_with_source< void > >
      : input_traits< argv_input >
   {};

   template< typename Eol, typename InputSource, typename ErrorSource, typename Input >
   struct input_traits< text_input_with_source< Eol, InputSource, ErrorSource, Input > >
      : input_traits< Input >
   {
      static constexpr bool has_lines = true;
      static constexpr bool has_source = true;
   };

   template< typename Eol, typename Input >
   struct input_traits< text_input_with_source< Eol, void, void, Input > >
      : input_traits< Input >
   {
      static constexpr bool is_text = true;
      static constexpr bool has_lines = true;
   };

   template< typename Eol, typename Input >
   struct input_traits< base_combination< Eol, Input > >
      : input_traits< input_with_fakes< input_with_peeks< input_with_lines< Eol, Input > > > >
   {};

   template< typename Input >
   struct input_traits< path_combination< Input > >
      : input_traits< input_double_path< input_with_source< std::filesystem::path, std::filesystem::path, Input > > >
   {};

   template< typename Eol, typename Input >
   struct input_traits< text_combination< Eol, Input > >
      : input_traits< input_double_path< text_input_with_source< Eol, std::filesystem::path, std::filesystem::path, Input > > >
   {};

}  // namespace TAO_PEGTL_NAMESPACE::internal

#endif