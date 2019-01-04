#pragma once
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
// ^FILE   : RoadComMgr.hpp
// ^AUTHOR : Michael McGarry
// ^DATE   : 22 Jun 1998
//
// ^CLASS  : RoadComMgr
// ^PARENT : none
//
// ^CLASS DESCRIPTION :
//
//
// ----------------------------------------------------------
//                PUBLIC MEMBER FUNCTIONS
// ----------------------------------------------------------
//
// ^METHOD      : isThreadActive
//
// ^DESCRIPTION : Returns true if there is an active thread for this object.
//
// ^PARAMETERS  : none
//
// ^RETURNS     : BOOL -
//
// ^THROWS      : none
//
// ----------------------------------------------------------
//
// ^METHOD      : releaseAllDispatches
//
// ^DESCRIPTION : To be called by the ExistInstance method of the application
//
// ^PARAMETERS  : none
//
// ^RETURNS     : void -
//
// ^THROWS      : none
//
// ----------------------------------------------------------
//
// ^METHOD      : callEndOnAllActiveObjects
//
// ^DESCRIPTION : This will call the end method for all active objects
//
// ^PARAMETERS  : none
//
// ^RETURNS     : void -
//
// ^THROWS      : none
//
// ----------------------------------------------------------
//
// ^METHOD      : end
//
// ^DESCRIPTION : This method is a signal the the EndCall button was pressed.
//
// ^PARAMETERS  : none
//
// ^RETURNS     : void -
//
// ^THROWS      : none
//
// ----------------------------------------------------------
//               PROTECTED MEMBER FUNCTIONS
// ----------------------------------------------------------
//
// ^METHOD      : performTask
//
// ^DESCRIPTION : This method is called by the thread.  Before calling
//                RoadComMgr::spool, the member m_methodID should be set
//                to indicate what action sould be taken when performTask()
//                is called.
//
// ^PARAMETERS  :
//   ^^ COleDispatchDriver *pOleDispatch - Dispatch to the ole interface to
//                                         be used in performTask()
//
// ^RETURNS     : BOOL - true if successful
//
// ^THROWS      : none - All exceptions should be handled in this method
//
// ----------------------------------------------------------
//
// ^METHOD      : createDispatch
//
// ^DESCRIPTION : This method should create the dispatch to the ole interface
//                being managed.
//
// ^PARAMETERS  : none
//
// ^RETURNS     : COleDispatchDriver * -
//
// ^THROWS      : none
//
// ----------------------------------------------------------
//
// ^METHOD      : releaseDispatch
//
// ^DESCRIPTION : This method should release the dispatch.
//
// ^PARAMETERS  :
//   ^^ COleDispatchDriver *pOleDispatch -
//
// ^RETURNS     : void -
//
// ^THROWS      : none
//
// ----------------------------------------------------------
//
// ^METHOD      : RoadComMgr
//
// ^DESCRIPTION : Constructor
//
// ^PARAMETERS  : none
//
// ^RETURNS     : none
//
// ^THROWS      : ConditionException
//
// ----------------------------------------------------------
//
// ^METHOD      : ~RoadComMgr
//
// ^DESCRIPTION : Destructor
//
// ^PARAMETERS  : none
//
// ^RETURNS     : none
//
// ^THROWS      : none
//
// ----------------------------------------------------------
//
// ^METHOD      : spool
//
// ^DESCRIPTION : Method used by derived class to spool the thread. This method
//                creates new Data objects (one for the thread data and one
//                for the thread's parameters) using the copy constructor.
//                This method then calls the third spool method described below.
//
// ^PARAMETERS  :
//   ^^ RequestType m_request - whether to wait on the thread or error
//                              if a thread is already present
//   ^^ const Data &data - Data to be passed to the thread
//   ^^ const Data &params - Parameters to be passed to the thread.
//   ^^ int conditionID - Defaults to 0.  Condition code for the error
//
// ^RETURNS     : BOOL -
//
// ^THROWS      : < description of all possible thrown exceptions >
//
// ^EXAMPLE     : < if the use of this member is not obvious,
//                  give an example >
//
// ----------------------------------------------------------
//
// ^METHOD      : spool
//
// ^DESCRIPTION : Method used by derived class to spool the thread. This method
//                creates a new Data object using the copy constructor.  This
//                method then calls the other spool method described below.
//
// ^PARAMETERS  :
//   ^^ RequestType m_request - whether to wait on the thread or error
//                              if a thread is already present
//   ^^ const Data &data - Data to be passed to the thread
//   ^^ int conditionID - Defaults to 0.  Condition code for the error
//
// ^RETURNS     : BOOL -
//
// ^THROWS      : ConditionException
//
// ----------------------------------------------------------
//
// ^METHOD      : spool
//
// ^DESCRIPTION : Method used by derived class to spool the thread.
//
// ^PARAMETERS  :
//   ^^ RequestType m_request - whether to wait on the thread or error
//                              if a thread is already present
//   ^^ Data *pData - Defaults to NULL. Data pointer to pass to thread.
//                    NOTE: This Data pointer will be deleted by this
//                    base class.
//   ^^ Data *pParams - Defaults to NULL. Data pointer representing thread
//                      parameters.  NOTE: This Data pointer will be deleted by
//                      this base class.
//   ^^ int conditionID - Defaults to 0.  Condition code for the error
//
// ^RETURNS     : BOOL - TRUE if the thread successfully started.
//
// ^THROWS      : none
//
// ----------------------------------------------------------
//
// ^METHOD      : getThreadParams
//
// ^DESCRIPTION : to be used by the inherited class to retrieve the data object
//                representing the thread's parameters
//
// ^PARAMETERS  : none
//
// ^RETURNS     : Data * -
//
// ^THROWS      : none
//
// ----------------------------------------------------------
//
// ^METHOD      : getThreadData
//
// ^DESCRIPTION : to be used by the inherited class to retrieve the thread data
//
// ^PARAMETERS  : none
//
// ^RETURNS     : Data * -
//
// ^THROWS      : none
//
// ----------------------------------------------------------
//
// ^METHOD      : getMethodID
//
// ^DESCRIPTION : to be used by inherited class to identify method to perform
//
// ^PARAMETERS  : none
//
// ^RETURNS     : int -
//
// ^THROWS      : none
//
//******************************************************************************

#include <bfdata\bfdata.hpp>
#include <set>
#include <afxmt.h>

class RoadComMgr
{
public:
   BOOL isThreadActive();

   static void releaseAllDispatches();

   static void callEndOnAllActiveObjects();

   virtual void end() = 0;

   // Protected virtuals - THESE MUST BE IMPLEMENTED in the derived class
protected:
   virtual BOOL performTask( COleDispatchDriver *pOleDispatch ) = 0;

   virtual COleDispatchDriver *createDispatch() = 0;

   virtual void releaseDispatch( COleDispatchDriver *pOleDispatch = NULL ) = 0;

   // Structs and enums
protected:
   enum RequestType
   {
      ERROR_ON_PRIOR_THREAD,
      WAIT_ON_PRIOR_THREAD
   };

   // Constructor and destructor
protected:
//CP20030319   RoadComMgr();
   RoadComMgr();
   virtual ~RoadComMgr();

   // Protected methods
protected:
   BOOL spool( RequestType m_request,
               const BFData &data,
               const BFData &params,
               int conditionID = 0,
               int methodID = 0 );
   BOOL spool( RequestType m_request,
               const BFData &data,
               int conditionID = 0,
               int methodID = 0 );
   BOOL spool( RequestType m_request,
               BFData *pData = NULL,
               BFData *pParams = NULL,
               int conditionID = 0,
               int methodID = 0 );
   BFData *getThreadParams();
   BFData *getThreadData();
   int getMethodID();

   // Private Structs
private:
   typedef std::set< RoadComMgr*, std::less< RoadComMgr* > > RoadComList;

   // Private methods
private:
   static UINT threadProc( LPVOID pParam );
   void setThread( CWinThread *pThread );
   CWinThread *getThread();
   void setThreadData( BFData *pData, BFData *pParams, int methodID );
   void deleteThreadData();
   BOOL isReadyForNewThread();
   void endRequestForThread();


   // Private members
private:
   CCriticalSection m_csWaitingOnThread;
   CCriticalSection m_csThreadPointer;
   CCriticalSection m_csThreadData;
   CWinThread *m_pThread;
   BFData *m_pThreadParams;
   BFData *m_pThreadData;
   int m_methodID;
   CEvent m_esThread;
   unsigned long m_requestingThread;

   static CCriticalSection m_csList;
   static RoadComList m_list;
   static BOOL m_releaseAllDispatches;
   static int m_objectCount;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/RoadComMgr.hpp-arc  $
 * 
 *    Rev 1.4   Mar 21 2003 18:40:28   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.3   Oct 09 2002 23:56:12   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.2   22 May 2002 19:16:24   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.1   Feb 15 2000 18:59:42   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 11:01:24   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.1   Jul 08 1999 10:05:50   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */

