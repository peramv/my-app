//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : RoadComMgr.cpp
// ^AUTHOR : Michael McGarry
// ^DATE   : 22 Jun 1998
//
// ----------------------------------------------------------
//
// ^CLASS    : RoadComMgr
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"

#ifndef ROADCOMMGR_HPP
   #include "RoadComMgr.hpp"
#endif
#ifndef OLEGLOBAL_HPP
   #include <uibase\OleGlobal.hpp>
#endif
#ifndef CONDITIONMESSAGEDIALOG_H
   #include <uibase\conditionmessagedialog.h>
#endif
#ifndef INCLUDED_ASSERT_H
#define INCLUDED_ASSERT_H
#include <assert.h>
#endif
#include "resource.h"


//******************************************************************************
//              Public Methods
//******************************************************************************

BOOL RoadComMgr::isThreadActive()
{
   CSingleLock singleLock( &m_csThreadPointer );
   singleLock.Lock();

   return( NULL != m_pThread ) || m_requestingThread;
}

void RoadComMgr::releaseAllDispatches()
{
   CSingleLock singleLock( &m_csList );
   singleLock.Lock();

   // Iterate through the list and call releaseDispatch, passing a NULL.
   RoadComList::iterator iter = m_list.begin();

   while( iter != m_list.end() )
   {
      ( *iter )->releaseDispatch();
      ++iter;
   }

   if( 0 < m_objectCount )
   {
      OleUninitialize();
      m_objectCount = 0;
   }

   m_releaseAllDispatches = TRUE;
}

void RoadComMgr::callEndOnAllActiveObjects()
{
   CSingleLock singleLock( &m_csList );
   singleLock.Lock();

   // Iterate through the list and call end()
   RoadComList::iterator iter = m_list.begin();

   while( iter != m_list.end() )
   {
      ( *iter )->end();
      ++iter;
   }
}


//******************************************************************************
//              Static member objects
//******************************************************************************

CCriticalSection RoadComMgr::m_csList;
RoadComMgr::RoadComList RoadComMgr::m_list;
BOOL RoadComMgr::m_releaseAllDispatches = FALSE;
int RoadComMgr::m_objectCount = 0;

//******************************************************************************
//              Protected Methods
//******************************************************************************

RoadComMgr::RoadComMgr()
: m_esThread( TRUE, TRUE )
{
   m_pThread = NULL;
   m_pThreadData = NULL;
   m_pThreadParams = NULL;
   m_requestingThread = 0L;

   CSingleLock singleLock( &m_csList );
   singleLock.Lock();

   // Initialize COM so we can instantiate external COM objects
   if( 1 == ++m_objectCount )
   {
      HRESULT hr = OleInitialize( NULL );

      if( FAILED( hr ) )
      {
         AfxMessageBox( TXT_FAILED_TO_INITIALIZE_COM );
         throw;
      }
   }

   // Add ourself to the list
   m_list.insert( this );
}

RoadComMgr::~RoadComMgr()
{
   if( ! m_releaseAllDispatches )
   {
      CSingleLock singleLock( &m_csList );
      singleLock.Lock();

      if( 0 == --m_objectCount )
      {
         OleUninitialize();
      }

      // Remove ourself from the list
      RoadComList::iterator iter = m_list.find( this );
      m_list.erase( iter );
   }
}

BOOL RoadComMgr::spool( RequestType m_request,
                        const BFData &data,
                        const BFData &params,
                        int conditionID,
                        int methodID )
{
   BFData *pData = new BFData( data );

   if( ! pData )
   {
      //THROWFROMFILE( I_( "RoadComMgr" ), I_( "RoadComMgr::spool()" ), RRGUI_ERROR_MALLOC );
      assert( 0 );
      throw;
   }

   BFData *pParams = new BFData( params );

   if( ! pParams )
   {
      //THROWFROMFILE( I_( "RoadComMgr" ), I_( "RoadComMgr::spool()" ), RRGUI_ERROR_MALLOC );
      assert( 0 );
      throw;
   }

   return(spool( m_request, pData, pParams, conditionID, methodID ));
}

BOOL RoadComMgr::spool( RequestType m_request,
                        const BFData &data,
                        int conditionID,
                        int methodID )
{
   BFData *pData = new BFData( data );

   if( ! pData )
   {
      //THROWFROMFILE( RRGUI, "RoadComMgr::spool()", RRGUI_ERROR_MALLOC );
      assert( 0 );
      throw;
   }

   return(spool( m_request, pData, NULL, conditionID, methodID ));
}

BOOL RoadComMgr::spool( RequestType m_request,
                        BFData *pData,
                        BFData *pParams,
                        int conditionID,
                        int methodID )
{
   BOOL started = FALSE;

   if( ! isReadyForNewThread() )
   {
      switch( m_request )
      {
         case ERROR_ON_PRIOR_THREAD:
            if( conditionID )
            {
               MAKEFRAMENOTRACE( I_ ( "RoadCommMgr" ), I_( "RoadCommMgr::spool" ));
               //            DISPLAYCONDITIONFROMFILE( conditionID, I_( "" ), I_( "" ), I_( "" ), I_( "" ) );
            }
            endRequestForThread();
            return(started);

         case WAIT_ON_PRIOR_THREAD:
            {
               // Make other threads wait in turn
               CSingleLock singleLock( &m_csWaitingOnThread );
               singleLock.Lock();
               {
                  // Wait for worker thread to end
                  CSingleLock waitForThread( &m_esThread );
                  waitForThread.Lock();
               }

               // Signal others to wait for worker thread
               m_esThread.ResetEvent();
            }
            break;
      }
   }

   // Execution should not reach this point while there is still an active
   // thread.
   setThreadData( pData, pParams, methodID );
   setThread( AfxBeginThread( RoadComMgr::threadProc, (LPVOID)this ) );
   started = isThreadActive();

   if( ! started )
   {
      deleteThreadData();
   }

   endRequestForThread();
   return(started);
}

BFData * RoadComMgr::getThreadParams()
{
   CSingleLock singleLock( &m_csThreadData );
   singleLock.Lock();

   return(m_pThreadParams);
}

BFData * RoadComMgr::getThreadData()
{
   CSingleLock singleLock( &m_csThreadData );
   singleLock.Lock();

   return(m_pThreadData);
}

int RoadComMgr::getMethodID()
{
   CSingleLock singleLock( &m_csThreadData );
   singleLock.Lock();

   return(m_methodID);
}

//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//
// ^PRIVATE METHOD      : RoadComMgr::threadProc
//
// ^DESCRIPTION : static method used to run the thread
//
// ^PARAMETERS  :
//   ^^ LPVOID pParam - pointer to a RoadComMgr object
//
// ^RETURNS     : UINT -
//
// ^THROWS      : none
//
//******************************************************************************
UINT RoadComMgr::threadProc( LPVOID pParam )
{
   RoadComMgr *pMgr = (RoadComMgr *) pParam;

   AfxOleInit();

   COleDispatchDriver *pOle = pMgr->createDispatch();

   // Only call performTask if we have an Ole Dispatch
   if( pOle )
   {
      pMgr->performTask( pOle );
      pMgr->releaseDispatch( pOle );
   }

   pMgr->deleteThreadData();
   pMgr->setThread( NULL );

   return(FALSE);
}

//******************************************************************************
//
// ^PRIVATE METHOD      : RoadComMgr::setThread
//
// ^DESCRIPTION : used to set the current thread ID.  If the parameter is NULL
//                then the thread event semaphore is reset.
//
// ^PARAMETERS  :
//   ^^ CWinThread *pThread -
//
// ^RETURNS     : void -
//
// ^THROWS      : none
//
//******************************************************************************
void RoadComMgr::setThread( CWinThread *pThread )
{
   CSingleLock singleLock( &m_csThreadPointer );
   singleLock.Lock();

   // If a null is passed in, then we no longer have a thread (or care about it)
   if( NULL == pThread )
   {
      m_esThread.SetEvent();
   }

   m_pThread = pThread;
}

//******************************************************************************
//
// ^PRIVATE METHOD      : RoadComMgr::getThread
//
// ^DESCRIPTION : used to get the current thread ID
//
// ^PARAMETERS  : none
//
// ^RETURNS     : CWinThread * -
//
// ^THROWS      : none
//
//******************************************************************************
CWinThread * RoadComMgr::getThread()
{
   CSingleLock singleLock( &m_csThreadPointer );
   singleLock.Lock();

   return(m_pThread);
}

//******************************************************************************
//
// ^PRIVATE METHOD      : RoadComMgr::setThreadData
//
// ^DESCRIPTION : used to set the data and parameters for the thread
//
// ^PARAMETERS  :
//   ^^ BFData *pData -
//   ^^ BFData *pParams -
//   ^^ int methodId -
//
// ^RETURNS     : void -
//
// ^THROWS      : none
//
//******************************************************************************
void RoadComMgr::setThreadData( BFData *pData, BFData *pParams, int methodID )
{
   CSingleLock singleLock( &m_csThreadData );
   singleLock.Lock();

   if( m_pThreadData )
   {
      delete m_pThreadData;
   }

   if( m_pThreadParams )
   {
      delete m_pThreadParams;
   }

   m_pThreadData = pData;
   m_pThreadParams = pParams;
   m_methodID = methodID;
}

//******************************************************************************
//
// ^PRIVATE METHOD      : RoadComMgr::deleteThreadData
//
// ^DESCRIPTION : used to release the memory of the thread data
//
// ^PARAMETERS  : none
//
// ^RETURNS     : void -
//
// ^THROWS      : none
//
//******************************************************************************
void RoadComMgr::deleteThreadData()
{
   CSingleLock singleLock( &m_csThreadData );
   singleLock.Lock();

   if( m_pThreadData )
   {
      delete m_pThreadData;
      m_pThreadData = NULL;
   }

   if( m_pThreadParams )
   {
      delete m_pThreadParams;
      m_pThreadParams = NULL;
   }
}

//******************************************************************************
//
// ^PRIVATE METHOD      : RoadComMgr::isReadyForNewThread
//
// ^DESCRIPTION : Returns a false if the thread is active.  If the thread is
//                not active, sets m_waitingOnThread to true, sets the
//                thread event semaphore and returns true.
//
// ^PARAMETERS  : none
//
// ^RETURNS     : BOOL -
//
// ^THROWS      :
//
//******************************************************************************
BOOL RoadComMgr::isReadyForNewThread()
{
   CSingleLock singleLock( &m_csThreadPointer );
   singleLock.Lock();

   // See if there is an active thread (or request)
   BOOL isReady = ! isThreadActive();

   // Register our request
   ++m_requestingThread;

   // If we are ready, make others wait for the work thread to end
   if( isReady )
   {
      m_esThread.ResetEvent();
   }

   return(isReady);
}

//******************************************************************************
//
// ^PRIVATE METHOD      : RoadComMgr::endRequestForThread
//
// ^DESCRIPTION : Decrements the count of threads requesting the worker thread
//
// ^PARAMETERS  : none
//
// ^RETURNS     : void -
//
// ^THROWS      : none
//
//******************************************************************************
void RoadComMgr::endRequestForThread()
{
   CSingleLock singleLock( &m_csThreadPointer );
   singleLock.Lock();

   --m_requestingThread;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/RoadComMgr.cpp-arc  $
 * 
 *    Rev 1.3   Feb 26 2003 13:27:56   linmay
 * clean up message
 * 
 *    Rev 1.2   Oct 09 2002 23:56:12   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.1   22 May 2002 19:16:24   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.0   Feb 15 2000 11:01:24   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.1   Jul 08 1999 10:05:50   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
