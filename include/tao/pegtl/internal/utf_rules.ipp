// Copyright (c) 2014-2024 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

// Some preprocessor games. Neither do I want to maintain six copies
// of the rules below, nor do I want to stick it all into a struct and
// template over the peek. What we need here are namespace templates.

#if !defined( TAO_PEGTL_UTF_NAME )
#error Missing name!
#endif

#if !defined( TAO_PEGTL_NAMESPACE )
#error Missing namespace!
#endif

#define TAO_PEGTL_UTF_IMPL( NaMe ) internal::peek_##NaMe
#define TAO_PEGTL_UTF_HELP( NaMe ) TAO_PEGTL_UTF_IMPL( NaMe )

#define TAO_PEGTL_UTF_PEEK TAO_PEGTL_UTF_HELP( TAO_PEGTL_UTF_NAME )

namespace TAO_PEGTL_NAMESPACE
{
   namespace TAO_PEGTL_UTF_NAME
   {
      // clang-format off
      struct cr : internal::one< TAO_PEGTL_UTF_PEEK, '\r' > {};
      struct lf : internal::one< TAO_PEGTL_UTF_PEEK, '\n' > {};
      struct crlf : internal::utf_string_t< TAO_PEGTL_UTF_PEEK, '\r', '\n' > {};
      struct cr_lf : internal::one< TAO_PEGTL_UTF_PEEK, '\r', '\n' > {};
      struct cr_crlf : internal::sor< crlf::rule_t, cr::rule_t > {};
      struct lf_crlf : internal::sor< lf::rule_t, crlf::rule_t > {};
      struct cr_lf_crlf : internal::sor< crlf::rule_t, cr_lf::rule_t > {};
      struct ls : internal::one< TAO_PEGTL_UTF_PEEK, char32_t( 0x2028 ) > {};
      struct nel : internal::one< TAO_PEGTL_UTF_PEEK, char32_t( 0x85 ) > {};
      struct ps : internal::one< TAO_PEGTL_UTF_PEEK, char32_t( 0x2029 ) > {};
      struct eol1 : internal::one< TAO_PEGTL_UTF_PEEK, char32_t( '\r' ), char32_t( '\n' ), char32_t( '\v' ), char32_t( '\f' ), char32_t( 0x85 ), char32_t( 0x2028 ), char32_t( 0x2029 ) > {};
      struct eolu : internal::sor< crlf::rule_t, eol1::rule_t > {};

      struct any : internal::any< TAO_PEGTL_UTF_PEEK > {};
      struct bom : internal::one< TAO_PEGTL_UTF_PEEK, 0xfeff > {};
      template< unsigned Count > struct many : internal::many< Count, TAO_PEGTL_UTF_PEEK > {};
      template< char32_t... Cs > struct not_one : internal::not_one< TAO_PEGTL_UTF_PEEK, Cs... > {};
      template< char32_t Lo, char32_t Hi > struct not_range : internal::not_range< TAO_PEGTL_UTF_PEEK, Lo, Hi > {};
      template< char32_t... Cs > struct one : internal::one< TAO_PEGTL_UTF_PEEK, Cs... > {};
      template< char32_t Lo, char32_t Hi > struct range : internal::range< TAO_PEGTL_UTF_PEEK, Lo, Hi > {};
      template< char32_t... Cs > struct ranges : internal::ranges< TAO_PEGTL_UTF_PEEK, Cs... > {};
      template< char32_t... Cs > struct string : internal::utf_string_t< TAO_PEGTL_UTF_PEEK, Cs... > {};
      // clang-format on

      namespace eols
      {
         namespace scan
         {
            // clang-format off
            struct cr : TAO_PEGTL_UTF_NAME::cr { using eol_char_rule = TAO_PEGTL_UTF_NAME::cr; };
            struct lf : TAO_PEGTL_UTF_NAME::lf { using eol_char_rule = TAO_PEGTL_UTF_NAME::lf; };
            struct cr_crlf : TAO_PEGTL_UTF_NAME::cr_crlf { using eol_char_rule = TAO_PEGTL_UTF_NAME::cr; };
            struct lf_crlf : TAO_PEGTL_UTF_NAME::lf_crlf { using eol_char_rule = TAO_PEGTL_UTF_NAME::lf; };
            struct ls : TAO_PEGTL_UTF_NAME::ls { using eol_char_rule = TAO_PEGTL_UTF_NAME::ls; };
            struct nel : TAO_PEGTL_UTF_NAME::nel { using eol_char_rule = TAO_PEGTL_UTF_NAME::nel; };
            struct ps : TAO_PEGTL_UTF_NAME::ps { using eol_char_rule = TAO_PEGTL_UTF_NAME::ps; };
            // clang-format on
         }  // namespace scan

         namespace lazy
         {
            // clang-format off
            struct cr : TAO_PEGTL_UTF_NAME::cr { using eol_lazy_peek = TAO_PEGTL_UTF_PEEK; };
            struct lf : TAO_PEGTL_UTF_NAME::lf { using eol_lazy_peek = TAO_PEGTL_UTF_PEEK; };
            struct crlf : TAO_PEGTL_UTF_NAME::crlf { using eol_lazy_peek = TAO_PEGTL_UTF_PEEK; };
            struct cr_lf : TAO_PEGTL_UTF_NAME::cr_lf { using eol_lazy_peek = TAO_PEGTL_UTF_PEEK; };
            struct cr_crlf : TAO_PEGTL_UTF_NAME::cr_crlf { using eol_lazy_peek = TAO_PEGTL_UTF_PEEK; };
            struct lf_crlf : TAO_PEGTL_UTF_NAME::lf_crlf { using eol_lazy_peek = TAO_PEGTL_UTF_PEEK; };
            struct cr_lf_crlf : TAO_PEGTL_UTF_NAME::cr_lf_crlf { using eol_lazy_peek = TAO_PEGTL_UTF_PEEK; };
            struct ls : TAO_PEGTL_UTF_NAME::ls { using eol_lazy_peek = TAO_PEGTL_UTF_PEEK; };
            struct nel : TAO_PEGTL_UTF_NAME::nel { using eol_lazy_peek = TAO_PEGTL_UTF_PEEK; };
            struct ps : TAO_PEGTL_UTF_NAME::ps { using eol_lazy_peek = TAO_PEGTL_UTF_PEEK; };
            struct eolu : TAO_PEGTL_UTF_NAME::eolu { using eol_lazy_peek = TAO_PEGTL_UTF_PEEK; };
            // clang-format on
         }  // namespace rule

         namespace rule
         {
            // clang-format off
            struct cr : TAO_PEGTL_UTF_NAME::cr {};
            struct lf : TAO_PEGTL_UTF_NAME::lf {};
            struct crlf : TAO_PEGTL_UTF_NAME::crlf {};
            struct cr_lf : TAO_PEGTL_UTF_NAME::cr_lf {};
            struct cr_crlf : TAO_PEGTL_UTF_NAME::cr_crlf {};
            struct lf_crlf : TAO_PEGTL_UTF_NAME::lf_crlf {};
            struct cr_lf_crlf : TAO_PEGTL_UTF_NAME::cr_lf_crlf {};
            struct ls : TAO_PEGTL_UTF_NAME::ls {};
            struct nel : TAO_PEGTL_UTF_NAME::nel {};
            struct ps : TAO_PEGTL_UTF_NAME::ps {};
            struct eolu : TAO_PEGTL_UTF_NAME::eolu {};
            // clang-format on
         }  // namespace rule

      }  // namespace eols

   }  // namespace TAO_PEGTL_UTF_NAME

}  // namespace TAO_PEGTL_NAMESPACE

#undef TAO_PEGTL_UTF_NAME
#undef TAO_PEGTL_UTF_PEEK