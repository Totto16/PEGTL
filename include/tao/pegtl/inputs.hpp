// Copyright (c) 2021-2023 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_INPUTS_HPP
#define TAO_PEGTL_INPUTS_HPP

#include <string>

#include "config.hpp"
#include "eol.hpp"

#include "internal/inputs.hpp"

namespace TAO_PEGTL_NAMESPACE
{
   using argv_input = internal::input_with_fakes< internal::input_with_peeks< internal::input_with_start< internal::input_with_lines< ascii::lf, internal::argv_input > > > >;
   using argv_input_with_source = internal::input_with_fakes< internal::input_with_peeks< internal::input_with_start< internal::input_with_lines< ascii::lf, internal::argv_input_with_source > > > >;

   template< typename Container >
   using copy_input = internal::input_with_fakes< internal::input_with_peeks< internal::copy_input< Container > > >;
   template< typename Container, typename Source = std::string >
   using copy_input_with_source = internal::input_with_fakes< internal::input_with_peeks< internal::input_with_source< Source, internal::copy_input< Container > > > >;

   template< typename Eol, typename Container = std::string >
   using lazy_copy_input = internal::input_with_fakes< internal::input_with_peeks< internal::lazy_input< Eol, internal::copy_input< Container > > > >;
   template< typename Eol, typename Container = std::string, typename Source = std::string >
   using lazy_copy_input_with_source = internal::input_with_fakes< internal::input_with_peeks< internal::input_with_source< Source, internal::lazy_input< Eol, internal::copy_input< Container > > > > >;

   template< typename Eol, typename Container = std::string >
   using text_copy_input = internal::input_with_fakes< internal::input_with_peeks< internal::text_input< Eol, internal::copy_input< Container > > > >;
   template< typename Eol, typename Container = std::string, typename Source = std::string >
   using text_copy_input_with_source = internal::input_with_fakes< internal::input_with_peeks< internal::text_input_with_source< Eol, Source, internal::copy_input< Container > > > >;

   template< typename Data >
   using view_input = internal::input_with_fakes< internal::input_with_peeks< internal::input_with_start< internal::view_input< Data > > > >;
   template< typename Data, typename Source = std::string >
   using view_input_with_source = internal::input_with_fakes< internal::input_with_peeks< internal::input_with_source< Source, internal::input_with_start< internal::view_input< Data > > > > >;

   template< typename Eol, typename Data = char >
   using lazy_view_input = internal::input_with_fakes< internal::input_with_peeks< internal::lazy_input< Eol, internal::input_with_start< internal::view_input< Data > > > > >;
   template< typename Eol, typename Data = char, typename Source = std::string >
   using lazy_view_input_with_source = internal::input_with_fakes< internal::input_with_peeks< internal::input_with_source< Source, internal::lazy_input< Eol, internal::input_with_start< internal::view_input< Data > > > > > >;

   template< typename Eol, typename Data = char >
   using text_view_input = internal::input_with_fakes< internal::input_with_peeks< internal::text_input< Eol, internal::input_with_start< internal::view_input< Data > > > > >;
   template< typename Eol, typename Data = char, typename Source = std::string >
   using text_view_input_with_source = internal::input_with_fakes< internal::input_with_peeks< internal::text_input_with_source< Eol, Source, internal::input_with_start< internal::view_input< Data > > > > >;

   using file_input = internal::input_with_fakes< internal::input_with_peeks< internal::file_input > >;
   using file_input_with_source = internal::input_with_fakes< internal::input_with_peeks< internal::input_double_path< internal::input_with_source< std::filesystem::path, internal::file_input > > > >;

   template< typename Eol >
   using lazy_file_input = internal::input_with_fakes< internal::input_with_peeks< internal::lazy_input< Eol, internal::file_input > > >;
   template< typename Eol >
   using lazy_file_input_with_source = internal::input_with_fakes< internal::input_with_peeks< internal::input_double_path< internal::input_with_source< std::filesystem::path, internal::lazy_input< Eol, internal::file_input > > > > >;

   template< typename Eol >
   using text_file_input = internal::input_with_fakes< internal::input_with_peeks< internal::text_input< Eol, internal::file_input > > >;
   template< typename Eol >
   using text_file_input_with_source = internal::input_with_fakes< internal::input_with_peeks< internal::input_double_path< internal::text_input_with_source< Eol, std::filesystem::path, internal::file_input > > > >;

   using read_input = internal::input_with_fakes< internal::input_with_peeks< internal::read_input > >;
   using read_input_with_source = internal::input_with_fakes< internal::input_with_peeks< internal::input_double_path< internal::input_with_source< std::filesystem::path, internal::read_input > > > >;

   template< typename Eol >
   using lazy_read_input = internal::input_with_fakes< internal::input_with_peeks< internal::lazy_input< Eol, internal::read_input > > >;
   template< typename Eol >
   using lazy_read_input_with_source = internal::input_with_fakes< internal::input_with_peeks< internal::input_double_path< internal::input_with_source< std::filesystem::path, internal::lazy_input< Eol, internal::read_input > > > > >;

   template< typename Eol >
   using text_read_input = internal::input_with_fakes< internal::input_with_peeks< internal::text_input< Eol, internal::read_input > > >;
   template< typename Eol >
   using text_read_input_with_source = internal::input_with_fakes< internal::input_with_peeks< internal::input_double_path< internal::text_input_with_source< Eol, std::filesystem::path, internal::read_input > > > >;

#if defined( TAO_PEGTL_MMAP_AVAILABLE )
   using mmap_input = internal::input_with_fakes< internal::input_with_peeks< internal::mmap_input< char > > >;
   using mmap_input_with_source = internal::input_with_fakes< internal::input_with_peeks< internal::input_double_path< internal::input_with_source< std::filesystem::path, internal::mmap_input< char > > > > >;

   template< typename Eol >
   using lazy_mmap_input = internal::input_with_fakes< internal::input_with_peeks< internal::lazy_input< Eol, internal::mmap_input< char > > > >;
   template< typename Eol >
   using lazy_mmap_input_with_source = internal::input_with_fakes< internal::input_with_peeks< internal::input_double_path< internal::input_with_source< std::filesystem::path, internal::lazy_input< Eol, internal::mmap_input< char > > > > > >;

   template< typename Eol >
   using text_mmap_input = internal::input_with_fakes< internal::input_with_peeks< internal::text_input< Eol, internal::mmap_input< char > > > >;
   template< typename Eol >
   using text_mmap_input_with_source = internal::input_with_fakes< internal::input_with_peeks< internal::input_double_path< internal::text_input_with_source< Eol, std::filesystem::path, internal::mmap_input< char > > > > >;
#endif

}  // namespace TAO_PEGTL_NAMESPACE

#endif
