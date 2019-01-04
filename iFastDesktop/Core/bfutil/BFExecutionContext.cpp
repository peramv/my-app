#include "stdafx.h"

#include "BFExecutionContext.hpp"
#include "bfguard.hpp"

namespace bfutil
{
   bool s_bServerContext_ = false;
   bool s_bRetry_ = true;

   /**
    * This method returns the server context.  If true, no GUI commands should
    * be invoked.
    * 
    * @return true = running on server.
    */
   bool isServerContext()
   {
      return( s_bServerContext_ );
   }
   /**
    * This method sets the flag to indicate if running in server context.
    *  (no GUI)
    * 
    * @param bServerContext
    *               set to true if running in server context.
    */
   void setServerContext( bool bServerContext )
   {
      s_bServerContext_ = bServerContext;
   }

   bool isRetry()
   {
      return( s_bRetry_ );
   }

   void setRetry( bool bRetry )
   {
      s_bRetry_ = bRetry;
   }
};

/*==========================================================================
 *---------------------------- ContextMap class ----------------------------
 *==========================================================================*/
   
class ContextMap : public std::map< unsigned long, BFExecutionContext* >
{
protected:
   ContextMap() {}

public:
   ~ContextMap() {}

   BFCritSec& getCS() { return cs_; }

   static ContextMap& getInstance()
   {
      static ContextMap instance;
      return( instance );
   }

private:
   BFCritSec cs_;
};

typedef ContextMap::iterator BFEXECUTIONCONTEXT_ITER;

static __declspec( thread ) BFExecutionContext* t_pContext_ = NULL;

/*==========================================================================
 *------------------------------ Class Methods -----------------------------
 *==========================================================================*/

BFExecutionContext* BFExecutionContext::create()
{

   BFExecutionContext* pBFExecutionContext = NULL;
   ContextMap& rMap = ContextMap::getInstance();
   BFEXECUTIONCONTEXT_ITER it;
   {
      BFGuard g( ContextMap::getInstance().getCS() );
      it = rMap.find( GetCurrentThreadId() );
   }

   if( it != rMap.end() )
   {
      pBFExecutionContext = (*it).second;
      pBFExecutionContext->reset();
   }
   else
   {
      pBFExecutionContext = new BFExecutionContext();
      BFGuard g( ContextMap::getInstance().getCS() );
      rMap[ GetCurrentThreadId() ] = pBFExecutionContext;
   }

   return(pBFExecutionContext);
}

BFExecutionContext* BFExecutionContext::get()
{
   // if the thread has a context object then return it. 
   if( NULL != t_pContext_ )
   {
      return( t_pContext_ );
   }

   // create a new context object
   t_pContext_ = create();
   return( t_pContext_ );
}

void BFExecutionContext::attach( BFExecutionContext* pBFExecutionContext )
{
   if( NULL != t_pContext_ )
   {
      detach();
   }
   ContextMap& rMap = ContextMap::getInstance();
   // attach the specified BFExecutionContext object to the current thread
   BFGuard g( ContextMap::getInstance().getCS() );
   rMap[ GetCurrentThreadId() ] = pBFExecutionContext;
   t_pContext_ = pBFExecutionContext;

   // walk all of the BFExecutionContextImpl objects and notify them that we attached
   BFEXECUTIONCONTEXTIMPL_ITER it = t_pContext_->_mapImpl.begin();
   BFEXECUTIONCONTEXTIMPL_ITER itEnd = t_pContext_->_mapImpl.end();
   for( ; it != itEnd; ++it )
   {
      BFExecutionContextImpl* pImpl = (*it).second;
      pImpl->notifyAttach();
   }
}

BFExecutionContext* BFExecutionContext::attach( unsigned long idMasterThread )
{
   if( NULL != t_pContext_ )
   {
      detach();
   }

   // attach the BFExecutionContext object which belongs to the specified thread 
   // to the current thread
   ContextMap& rMap = ContextMap::getInstance();
   BFGuard g( ContextMap::getInstance().getCS() );
   t_pContext_ = NULL;

   BFEXECUTIONCONTEXT_ITER it = rMap.find( idMasterThread );
   if( it != rMap.end() )
   {
      attach( (*it).second );
   }
   return( t_pContext_ );
}

void BFExecutionContext::detach()
{
   // detach the BFExecutionContext object from the current thread.
   int cOccurences = 0;
   BFExecutionContext* pBFExecutionContext = NULL;

   {
      ContextMap& rMap = ContextMap::getInstance();
      BFGuard g( ContextMap::getInstance().getCS() );

      BFEXECUTIONCONTEXT_ITER it = rMap.find( ::GetCurrentThreadId() );
      if( it != rMap.end() )
      {
         pBFExecutionContext = (*it).second;

         if( NULL != pBFExecutionContext )
         {
            // is this the last occurrence in the map?
            BFEXECUTIONCONTEXT_ITER itMap;

            for( itMap = rMap.begin(); itMap != rMap.end(); ++itMap )
            {
               if( (*itMap).second == pBFExecutionContext )
               {
                  ++cOccurences;
               }
            }
         }
         rMap.erase( it );
      }
   }

   if( cOccurences == 1 )
   {
      delete pBFExecutionContext;
   }
}

/*==========================================================================
 *---------------------------- Instance Methods ----------------------------
 *==========================================================================*/

BFExecutionContext::BFExecutionContext()
{
}

BFExecutionContext::~BFExecutionContext()
{
   reset();

   // find all instances of this BFExecutionContext object in the map 
   // and remove them from the map
   {
      ContextMap& rMap = ContextMap::getInstance();
      BFGuard g( ContextMap::getInstance().getCS() );

      BFEXECUTIONCONTEXT_ITER it;
      for( it = rMap.begin(); it != rMap.end(); ++it )
      {
         if( (*it).second == this )
         {
            it = rMap.erase( it );
         }
      }
   }
}

void BFExecutionContext::reset()
{
   // delete all BFExecutionContextImpl objects from the map
   BFEXECUTIONCONTEXTIMPL_ITER it = _mapImpl.begin();
   for( ; it != _mapImpl.end(); ++it )
   {
      delete (*it).second;
   }
   _mapImpl.erase( _mapImpl.begin(), _mapImpl.end() );
}


bool BFExecutionContext::addObject( const DString &dstrKey, BFExecutionContextImpl* pImpl )
{
   BFGuard g( _cs );

   BFEXECUTIONCONTEXTIMPL_ITER it = _mapImpl.find( dstrKey );
   if( it != _mapImpl.end() )
   {
      // there is already such an object!  Throw an exception 
      return( false );
   }

   _mapImpl[ dstrKey ] = pImpl;
   return( true );
}

BFExecutionContextImpl* BFExecutionContext::getObject( const DString &dstrKey ) const
{
   BFGuard g( _cs );

   BFEXECUTIONCONTEXTIMPL_CITER it = _mapImpl.find( dstrKey );
   if( it != _mapImpl.end() )
   {
      return( (*it).second );
   }

   return( NULL );
}

bool BFExecutionContext::removeObject( const DString &dstrKey )
{
   BFGuard g( _cs );

   BFEXECUTIONCONTEXTIMPL_ITER it = _mapImpl.find( dstrKey );
   if( it != _mapImpl.end() )
   {
      _mapImpl.erase( it );
      return( true );
   }

   return( false );
}
/*==========================================================================
 *--------------------- BFExecutionContextImpl methods ---------------------
 *==========================================================================*/
BFExecutionContextImpl::BFExecutionContextImpl()
{}

BFExecutionContextImpl::~BFExecutionContextImpl()
{}


