#pragma once

#include <commonport.h>
#include <set>
#include <vector>
#include <algorithm>

#include <bfutil/subscriber.hpp>

#include <boost/type_traits.hpp>
#include <boost/static_assert.hpp>

// Helper macros
#define SUBSCRIBER_R( r, x ) ( static_cast< bf::Publisher< x >& >( r ) )
#define SUBSCRIBER( p, x ) ( static_cast< bf::Publisher< x >* >( p ) )
#define MY_SUBSCRIBER( x ) SUBSCRIBER( this, x )
#define DEF_SUBSCRIBER_LIST( x ) typedef bf::SubscriberContainer< x >::SubscriberList x##ObsList

namespace bf
{
   class AbstractPublisher
   {
   public:
      virtual ~AbstractPublisher() {}
   };

   template< typename _S >
   class SubscriberContainer
   {
   private:
      // Will generate Compile Error C2027 if _S is not derived from AbstractSubscriber
      BOOST_STATIC_ASSERT( ( ::boost::is_convertible< typename _S*, AbstractSubscriber* >::value ) );
   public:
      virtual void attach( typename _S* pSubscriber )
      {
         std::set< typename _S* >::iterator it = observers_.find( pSubscriber );
         if( observers_.end() == it )
         {
            observers_.insert( pSubscriber );
         }
      }
      virtual void detach( typename _S* pSubscriber )
      {
         std::set< typename _S* >::iterator it = observers_.find( pSubscriber );
         if( observers_.end() != it ) 
         {
            observers_.erase( it );
         }
      }
      void finish( AbstractPublisher* pPublisher )
      {
         // instruct each observer that this subject is being destroyed
         std::set< typename _S* >::iterator it = observers_.begin();
         for( ; it != observers_.end(); it = observers_.begin() )
         {
            _S* pSubscriber = (*it);
            pSubscriber->finish( pPublisher );
            observers_.erase( it );
         }
      }

      typedef std::vector< _S* > SubscriberList;
      typedef typename std::vector< _S* >::iterator SubscriberListIter;
      typedef typename std::vector< _S* >::const_iterator SubscriberListConstIter;

      SubscriberList getList() const
      {
         SubscriberList v;
         v.reserve( observers_.size() );
         std::copy( observers_.begin(), observers_.end(), std::back_inserter( v ) );
         return( v );
      }
   private:
      std::set< typename _S* > observers_;
   };

   template< typename _S >
   class Publisher : public AbstractPublisher 
   {
   public:
      virtual ~Publisher()
      {
         finish();
      }

      void attach( typename _S* pSubscriber ) { c_.attach( pSubscriber ); }
      void detach( typename _S* pSubscriber ) { c_.detach( pSubscriber ); }

      typename bf::SubscriberContainer< _S >::SubscriberList getSubscriberList( ) const 
      {
         return( c_.getList() );
      }

      void finish() { c_.finish( this ); }

   protected:
      Publisher() {}

   private:
      SubscriberContainer< typename _S > c_;
   };
}
     


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfutil/publisher.hpp-arc  $
//
//   Rev 1.2   Oct 22 2004 09:00:56   PURDYECH
//PET910 - .NET Conversion Fixes
//
//   Rev 1.1   Apr 10 2003 10:51:14   PURDYECH
//Forgot to #include <vector> !!
//
//   Rev 1.0   Mar 14 2003 11:07:54   PURDYECH
//Initial Revision
//
