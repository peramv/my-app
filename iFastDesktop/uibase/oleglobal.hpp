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
// ^FILE   : OleGlobal.hpp
// ^AUTHOR : Michael McGarry
// ^DATE   : 21 Apr 1998
//
// ^CLASS  : OleGlobal
// ^PARENT : none
//
// ^CLASS DESCRIPTION :
//
//
// ----------------------------------------------------------
//                PUBLIC MEMBER FUNCTIONS
// ----------------------------------------------------------
//
// ^METHOD      : getInstance
//
// ^DESCRIPTION : Retrieves the singleton
//
// ^PARAMETERS  : none
//
// ^RETURNS     : OleGlobal * - pointer to the singleton
//
// ^THROWS      : ConditionException
//
// ----------------------------------------------------------
//
// ^METHOD      : setSearchScreenReady
//
// ^DESCRIPTION : To be called by the search screen to let any OLE object
//                know that the search screen is ready for messages.
//
// ^PARAMETERS  :
//   ^^ CWnd *searchDialog - Pointer to the search screen
//
// ^RETURNS     : void -
//
// ^THROWS      : none
//
// ----------------------------------------------------------
//
// ^METHOD      : waitForSearchScreen
//
// ^DESCRIPTION : Used by any OLE object to wait for the search screen
//
// ^PARAMETERS  : none
//
// ^RETURNS     : void -
//
// ^THROWS      : none
//
// ----------------------------------------------------------
//
// ^METHOD      : postMessageToSearchScreen
//
// ^DESCRIPTION : Posts a message in the Search Screen's message queue
//
// ^PARAMETERS  :
//   ^^ UINT msg - User message
//   ^^ WPARAM wparam -
//   ^^ LPARAM lparam -
//
// ^RETURNS     : bool - true if successfull
//
// ^THROWS      : none
//
// ----------------------------------------------------------
//                PRIVATE MEMBER FUNCTIONS
// ----------------------------------------------------------
//
// ^METHOD      : OleGlobal
//
// ^DESCRIPTION : Constructor used by _instanceManager
//
// ^PARAMETERS  :
//   ^^ const string &id - Id of the singleton
//
// ^RETURNS     : none
//
// ^THROWS      : ConditionException if fail to allocate memory
//
// ----------------------------------------------------------
//
// ^METHOD      : ~OleGlobal
//
// ^DESCRIPTION : Destructore called by _instanceManager
//
// ^PARAMETERS  : none
//
// ^RETURNS     : none
//
// ^THROWS      : none
//
//******************************************************************************

#ifndef TINSTANCEMANAGER_HPP
   #include <TInstanceManager.hpp>
#endif

#ifndef INCLUDED_STRING
#define INCLUDED_STRING
#include <string>
#endif

class EventSemaphore;

#undef WIN32UIBASE_LINKAGE
#ifdef WIN32UIBASE_DLL
   #define WIN32UIBASE_LINKAGE CLASS_EXPORT
#else
   #define WIN32UIBASE_LINKAGE CLASS_IMPORT
#endif

class WIN32UIBASE_LINKAGE OleGlobal
{
public:
   static OleGlobal *getInstance();
   void setSearchScreenReady( CWnd *searchDialog );
   void waitForSearchScreen();
   bool postMessageToSearchScreen( UINT msg, WPARAM wparam, LPARAM lparam );
   bool sendMessageToSearchScreen( UINT msg, WPARAM wparam, LPARAM lparam );

   // Private methods
private:
   OleGlobal( const DString &id );
   virtual ~OleGlobal();

   // Private members
private:
   typedef TInstanceManager<DString, OleGlobal> InstanceManager;
   friend InstanceManager;

   static InstanceManager _instanceManager;

   EventSemaphore *_searchScreenReady;
   CWnd *_searchDialog;
   DString _id;
};



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/uibase/oleglobal.hpp-arc  $
 * 
 *    Rev 1.3   Oct 09 2002 17:42:52   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.2   19 Mar 2002 13:36:16   PURDYECH
 * Added #pragma once include guard
 * Removed compile time "including..." message.
 * 
 *    Rev 1.1   Feb 15 2000 18:58:58   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 11:01:00   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.1   Jul 08 1999 10:05:42   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
