// Copyright (c) 2023 Dr. Colin Hirsch and Daniel Frey
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

#ifndef TAO_PEGTL_CONTRIB_NESTED_EXCEPTIONS_HH
#define TAO_PEGTL_CONTRIB_NESTED_EXCEPTIONS_HH

#include <exception>
#include <vector>

#include "../config.hpp"
#include "../parse_error.hpp"
#include "../position.hpp"

// Various utility functions and classes to handle nested exceptions given that parse_nested() now uses them.
// At this point it's not clear how many, and which, of these will become part of the PEGTL. Experimental.

namespace TAO_PEGTL_NAMESPACE::nested
{
   namespace internal
   {
      template< typename... >
      struct rethrower;

      template<>
      struct rethrower<>
      {
         template< typename Processor, typename Caught, typename Visitor >
         static void rethrow( const Caught& caught, Visitor&& /*unused*/, const std::size_t /*unused*/ )
         {
            std::rethrow_if_nested( caught );
         }

         template< typename Processor, typename Visitor >
         static void rethrow( const std::exception_ptr& caught, Visitor&& /*unused*/, const std::size_t /*unused*/ )
         {
            std::rethrow_exception( caught );
         }
      };

      template< typename Exception, typename... Exceptions >
      struct rethrower< Exception, Exceptions... >
      {
         template< typename Processor, typename Caught, typename Visitor >
         static void rethrow( const Caught& caught, Visitor&& visitor, const std::size_t level )
         {
            try {
               rethrower< Exceptions... >::template rethrow< Processor >( caught, visitor, level );
            }
            catch( const Exception& exception ) {
               Processor::process( exception, visitor, level );
            }
         }
      };

      template< typename Rethrower >
      struct processor
      {
         template< typename Exception, typename Visitor >
         static void process( const Exception& exception, Visitor&& visitor, const std::size_t level )
         {
            Rethrower::template rethrow< processor >( exception, visitor, level + 1 );
            visitor( exception, level );
         }
      };

      template< typename... Exceptions >
      struct inspector
      {
         using Rethrower = rethrower< Exceptions... >;
         using Processor = processor< Rethrower >;

         template< typename Visitor >
         static void inspect( const std::exception_ptr& ptr, Visitor&& visitor )
         {
            Rethrower::template rethrow< Processor >( ptr, visitor, 0 );
         }
      };

   }  // namespace internal

   // Exceptions in an inheritance hierarchy MUST be listed from general to specific,
   // e.g. inspect< std::exception, std::runtime_error >, otherwise the more specific
   // exceptions will be caught by the handler for the more general case.

   template< typename... Exceptions, typename Visitor >
   void inspect( Visitor&& visitor )
   {
      internal::inspector< Exceptions... >::inspect( std::current_exception(), visitor );
   }

   template< typename... Exceptions, typename Visitor >
   void inspect( const std::exception_ptr& ptr, Visitor&& visitor )
   {
      internal::inspector< Exceptions... >::inspect( ptr, visitor );
   }

   [[nodiscard]] inline std::vector< parse_error< position > > flatten( const std::exception_ptr& ptr = std::current_exception() )
   {
      std::vector< parse_error< position > > result;
      inspect< parse_error< position > >( ptr, [ &result ]( const parse_error< position >& e, const std::size_t /*unused*/ ) {
         result.emplace_back( e );
      } );
      return result;
   }

}  // namespace TAO_PEGTL_NAMESPACE::nested

#endif
