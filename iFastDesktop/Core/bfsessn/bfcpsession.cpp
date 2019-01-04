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
// ^FILE   : Session.cpp
// ^AUTHOR : Michael McGarry
// ^DATE   : 29 Apr 97
//
// ----------------------------------------------------------
//
// ^CLASS    : BFCPSession
//
// ^MEMBER VARIABLES :
//
//   ^^ BFCPSession        *m_parent        - pointer to parent session object
//   ^^ BFCPSession        *m_MasterSession - pointer to master session object
//   ^^ child_list      m_childList     - list of pointers to children
//   ^^ string          m_value         - value to return
//   ^^ Data            m_data          - session data
//   ^^ ConfigManager  *m_sessionCfgMgr - pointer to session's configuration
//   ^^ BFAwdSession     *m_pAwdSession   - pointer to BFAwdSession member object
//   ^^ bool            m_okToDelete    - indcates that a child is ok to delete
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "win32/stdafx.h"

#include "bfcpsession.hpp"
#include "bfawdsession.hpp"

#include <configmanager.hpp>
#include <configuration.hpp>
#include <configmacro.h>
#include <conditionmanager.hpp>

#include "bfsessn.h"

#include <base.h>
#include "bfcpsessiontags.h"
#include "bfsessioncommon.hpp"
#include "bflogsession.hpp"

#include <sstream>
#include <iomanip>
using std::setw;
using std::setfill;



#define SESSION_MSG( mthd, msg ) TRACE_CLASS_MSG( I_("BFCPSession"), mthd, msg )


namespace SessionTags
{
   const I_CHAR *PROFILE_NAME = I_("ProfileName");
}

using namespace SessionTags;

namespace
{
   const I_CHAR *TIME_FORMAT = I_("yyyy-MM-dd-HH.mm.ss.");
   const int     MSG_LEN     = 128;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

BFCPSession::BFCPSession()
: m_parent( NULL ),
m_MasterSession( NULL ),
m_data(),
m_sessionCfgMgr( NULL ),
m_okToDelete( true ),
m_pAwdSession( NULL ),
m_pLogSession( NULL ),
m_eventRecorded( false ),
m_strBeginSusp( I_( "" ) ),
m_durationSusp( 0 )
{
   MAKEFRAMECONSTRUCTOR2( DISESSN_CONDITION, I_("BFCPSession"),
                          I_("BFCPSession()") )

   SESSION_MSG( I_("BFCPSession()"), I_("Master Session constuctor") );

   m_MasterSession = this;
   m_sessionCfgMgr = CONFIG_MGR( CONFIG );

   setSessionData( CALL_START, getTimeStamp() );

   checkForAwd();
   PROMOTECONDITIONS();

   checkForLog();
   PROMOTECONDITIONS();
}

BFCPSession::~BFCPSession()
{
   TRACE_DESTRUCTOR( I_("BFCPSession") )

   if( isMaster() )
   {
      SESSION_MSG( I_("~BFCPSession()"), I_("Master Session destuctor") );
   }
   else
   {
      SESSION_MSG( I_("~BFCPSession()"), I_("Subsession destuctor") );
   }

   // Delete any child session objects
   deleteChildren();

   // If not ok to delete (this is a child session being deleted by the app)
   if( ! m_okToDelete )
   {
      // Remove ourself from our parent's child list.
      m_okToDelete = m_parent->removeFromChildList( this );
   }

   // This child has not been removed from parent's list.
   if( ! m_okToDelete )
   {
      // Trace what happened
      MAKEFRAMENOTRACE( DISESSN_CONDITION, I_("BFCPSession::~BFCPSession()") );
      ADDCONDITIONFROMFILE( DISESSN_CHILD_NOT_REMOVED );
   }

   setSessionData( CALL_END, getTimeStamp() );

   if( m_pAwdSession )
   {
      delete m_pAwdSession;
   }

   if( m_pLogSession )
   {
      delete m_pLogSession;
   }
}

const DString BFCPSession::getTimeStamp()
{
   static long microSecondCount = 0;


   SYSTEMTIME lt;
   GetLocalTime( &lt );
   std::wstringstream wss;
   wss << setfill( I_('0') ) << setw(4);
   DString dstrTemp;
   dstrTemp.appendULong( lt.wYear ); wss << dstrTemp;
   wss << I_( "-" ) << setw(2);
   dstrTemp = NULL_STRING; dstrTemp.appendULong( lt.wMonth ); wss << dstrTemp;
   wss << I_( "-" ) << setw(2);
   dstrTemp = NULL_STRING; dstrTemp.appendULong( lt.wDay ); wss << dstrTemp;
   wss << I_( "-" ) << setw(2);
   dstrTemp = NULL_STRING; dstrTemp.appendULong( lt.wHour ); wss << dstrTemp;
   wss << I_( "." ) << setw(2);
   dstrTemp = NULL_STRING; dstrTemp.appendULong( lt.wMinute ); wss << dstrTemp;
   wss << I_( "." ) <<  setw(2);
   dstrTemp = NULL_STRING; dstrTemp.appendULong( lt.wSecond ); wss << dstrTemp;
   wss << I_( "." ) << setw( 6 );
   dstrTemp = NULL_STRING; dstrTemp.appendULong( 0 ); wss << dstrTemp;
   return( wss.str() );
}

unsigned long BFCPSession::calcDuration( const I_STRING& begin, const I_STRING& end )
{
   unsigned long seconds = 0;

   if ( ( 26 == begin.size() ) && ( 26 == end.size() ) )
   {
      // 01234567890123456789012345
      // YYYY-MM-DD-HH.MM.SS.NNNNNN

      // Seconds
      DString strBuff1 = begin.substr( 17, 2 );
      DString strBuff2 = end.substr( 17, 2 );

      unsigned long i1 = i_ttoi( strBuff1.c_str() );
      unsigned long i2 = i_ttoi( strBuff2.c_str() );

      // Minutes
      strBuff1 = begin.substr( 14, 2 );
      strBuff2 = end.substr( 14, 2 );

      i1 = i1 + ( 60 * i_ttoi( strBuff1.c_str() ) );
      i2 = i2 + ( 60 * i_ttoi( strBuff2.c_str() ) );

      // Hours
      strBuff1 = begin.substr( 11, 2 );
      strBuff2 = end.substr( 11, 2 );

      i1 = i1 + ( 3600 * i_ttoi( strBuff1.c_str() ) );
      i2 = i2 + ( 3600 * i_ttoi( strBuff2.c_str() ) );

      // Make sure same day
      strBuff1 = begin.substr( 8, 2 );
      strBuff2 = end.substr( 8, 2 );

      if ( strBuff1 != strBuff2 )
      {
         unsigned long i3 = i_ttoi( strBuff2.c_str() ) - i_ttoi( strBuff1.c_str() );
         i2 = i2 + ( 86400 * i3 );
      }
      seconds = i2 - i1;
   }

   return seconds;
}

void BFCPSession::setSessionData( const DString &key, const DString &value )
{
   m_data.setElementValue( key, value, true );
}

void BFCPSession::setGlobalSessionData( const DString &key, const DString &value )
{
   m_MasterSession->setSessionData( key, value );
}

void BFCPSession::populateData( BFData &data )
{
   // If we're not the master session, populate from our parent first
   if( ! isMaster() )
   {
      m_parent->populateData( data );
   }

   m_data.getSelectedValues( data );
}

DString BFCPSession::getSessionData( const DString &key )
{
   DString value;

   // Find the key
   if( m_data.exists( key ) )
   {
      // Found, return it.
      value = m_data.getElementValue( key );
   }
   else
   {
      // Not found
      if( isMaster() )
      {
         // Return empty string
         value = I_("");
      }
      else
      {
         // See if our parent has the data
         value = m_parent->getSessionData( key );
      }
   }

   return(value);
}

SEVERITY BFCPSession::setSessionEvent( const DString &event,
                                       const BFDataPtrMap& data,
                                       bool bLocked )
   //CP20040224 Added bLocked at urging of YingBao Li.  Non-standard change to DST code
{
   MAKEFRAMEAUTOPROMOTE( DISESSN_CONDITION,
                         I_("BFCPSession:setSessionEvent()") )

   DString strMsg = I_("BFCPSession event identifier is ");
   strMsg += event;
   SESSION_MSG( I_("setSessionEvent()"), strMsg.c_str() );

   if( m_sessionCfgMgr->isProfileGroup() )
   {
      setSessionData( PROFILE_NAME, m_sessionCfgMgr->getCurrentProfileName() );
   }

   setSessionData( EVENT_ID, event );
   setSessionData( EVENT_TIME, getTimeStamp() );

   DString awdwork;
   DString logitem;

   //
   //  Query the config object what to do with this event.
   //
   Configuration eventcfg = m_sessionCfgMgr->retrieveConfig( event );

   // Make sure event is defined
   if( ! eventcfg.isEmpty() )
   {
      // Check for BFAwd work
      awdwork = eventcfg.getValueAsString( AWD_WORK );
      // Check for log event
      logitem = eventcfg.getValueAsString( LOG_ITEM );
   }

   if( m_pAwdSession )
   {
      DString awdEvent = getSessionData( AWD_EVENT );

      if( ( ! awdwork.empty() ) || ( ! awdEvent.empty() ) )
      {
         // Do the AWD work
         //CP20040224 Added bLocked at urging of YingBao Li.  Non-standard change to DST code
         m_pAwdSession->awdEvent( awdwork, eventcfg, data, bLocked );
      }
   }

   if( m_pLogSession )
   {
      DString logEvent = getSessionData( LOG_EVENT );

      if( ( ! logitem.empty() ) || ( ! logEvent.empty() ) )
      {
         // Log the event
         m_pLogSession->logEvent( logitem, eventcfg, data );
      }
   }

   setSessionData( EVENT_ID, I_("") );

   return(GETCURRENTHIGHESTSEVERITY());
}

BFCPSession *BFCPSession::createSubSession()
{
   TRACE_METHOD( I_("BFCPSession"), I_("createSubSession()") )

   // Call private constructor
   BFCPSession *child = new BFCPSession( this );
   ASSERT_NEW( child, I_("BFCPSession::createSubSession()") );

   // Add to cild list
   m_childList.push_back( child );

   return(child);
}

bool BFCPSession::endSubSession( BFCPSession *child )
{
   TRACE_METHOD( I_("BFCPSession"), I_("endSubSession( Session * )") )

   bool erased = removeFromChildList( child );

   if( erased )
   {
      child->m_okToDelete = true;
      delete child;
   }

   return(erased);
}


bool BFCPSession::setBeginSuspend()
{
   bool success = false;

   if ( ! isMaster() && m_strBeginSusp.empty() )
   {
      m_strBeginSusp = getTimeStamp();
      success = true;
   }

   return success;
}

bool BFCPSession::setEndSuspend()
{
   bool success = false;

   if ( ! ( isMaster() || m_strBeginSusp.empty() ) )
   {
      DString strNow = getTimeStamp();
      m_durationSusp += calcDuration( m_strBeginSusp.getImp(), strNow.getImp() );

      m_strBeginSusp = I_("");
      success = true;
   }

   return success;
}

//******************************************************************************
//              Private Methods
//******************************************************************************

bool BFCPSession::s_usingAwd = false;
bool BFCPSession::s_usingLog = false;
bool BFCPSession::s_usingMessage = false;

//******************************************************************************
//
// ^PRIVATE METHOD      : BFCPSession::BFCPSession
//
// ^DESCRIPTION : Pirvate constructor used for creating child (sub) sessions
//
// ^PARAMETERS  :
//   ^^ BFCPSession *parent
//
// ^RETURNS     : none
//
// ^THROWS      : ConditionException
//
//******************************************************************************
BFCPSession::BFCPSession( BFCPSession *parent )
: m_parent( parent ),
m_MasterSession( m_parent->m_MasterSession ),
m_data(),
m_sessionCfgMgr( m_parent->m_sessionCfgMgr ),
m_okToDelete( false ),
m_pAwdSession( NULL ),
m_pLogSession( NULL ),
m_eventRecorded( false )
{
   TRACE_CONSTRUCTOR( I_("BFCPSession"), I_("BFCPSession( BFCPSession * )") )
   SESSION_MSG( I_("BFCPSession( BFCPSession * )"), I_("Subsession constuctor") );

   setSessionData( CALL_START, getTimeStamp() );

   if( s_usingAwd )
   {
      m_pAwdSession = new BFAwdSession( this, m_sessionCfgMgr, false );
   }

   if( s_usingLog )
   {
      m_pLogSession = new BFLogSession( this, m_sessionCfgMgr, false );
   }
}

//******************************************************************************
//
// ^PRIVATE METHOD      : BFCPSession::checkForAwd
//
// ^DESCRIPTION : This method checks to see if session will be working
//                with AWD.
//
// ^PARAMETERS  : none
//
// ^RETURNS     : void
//
// ^THROWS      : ConditionException
//
//******************************************************************************
void BFCPSession::checkForAwd()
{
   MAKEFRAMEAUTOPROMOTE2( DISESSN_CONDITION, I_("BFCPSession"),
                          I_("checkForAwd()") )

   //
   // Ask the configuration object if we are using AWD
   //
   Configuration awdCfg = m_sessionCfgMgr->retrieveConfig( USE_AWD );
   DStringA useAwd = awdCfg.getValueAsString( USE_AWD );

   if( ( ! useAwd.empty() ) && ( useAwd[0] == 'Y' ) )
   {
      SESSION_MSG( I_("checkForAwd()"), I_("AWD option turned on") );

      m_pAwdSession = new BFAwdSession( this, m_sessionCfgMgr, true );
      s_usingAwd = m_pAwdSession->hasAwdInterface();

      SESSION_MSG( I_("checkForLog()"), ( s_usingAwd ?
                                          I_("Successfully connected to AWD") :
                                          I_("Failed to connect to AWD") ) );

      if( ! s_usingAwd )
      {
         delete m_pAwdSession;
         m_pAwdSession = NULL;
      }
   }
   else
   {
      SESSION_MSG( I_("checkForAwd()"), I_("AWD option *not* turned on") );

      s_usingAwd = false;
   }
}

//******************************************************************************
//
// ^PRIVATE METHOD      : BFCPSession::checkForLog
//
// ^DESCRIPTION : This method checks to see if event logging is set.
//
// ^PARAMETERS  : none
//
// ^RETURNS     : void -
//
// ^THROWS      : < description of all possible thrown exceptions >
//
// ^EXAMPLE     : < if the use of this member is not obvious,
//                  give an example >
//
//******************************************************************************
void BFCPSession::checkForLog()
{
   MAKEFRAMEAUTOPROMOTE2( DISESSN_CONDITION, I_("BFCPSession"),
                          I_("checkForLog()") )

   //
   // Ask the configuration object if we are using Logging
   //
   Configuration awdCfg = m_sessionCfgMgr->retrieveConfig( EVENT_LOGGING );
   DStringA useLog = awdCfg.getValueAsString( EVENT_LOGGING );

   if( ( ! useLog.empty() ) && ( useLog[0] == 'Y' ) )
   {
      SESSION_MSG( I_("checkForLog()"), I_("Logging option turned on") );

      m_pLogSession = new BFLogSession( this, m_sessionCfgMgr, true );
      s_usingLog = m_pLogSession->connectedToDataSource();

      SESSION_MSG( I_("checkForLog()"), ( s_usingLog ?
                                          I_("Successfully connected to Data Source") :
                                          I_("Failed to connect to Data Source") ) );

      if( ! s_usingLog )
      {
         delete m_pLogSession;
         m_pLogSession = NULL;
      }
   }
   else
   {
      SESSION_MSG( I_("checkForLog()"), I_("Loging option *not* turned on") );
      s_usingLog = false;
   }
}

//******************************************************************************
//
// ^PRIVATE METHOD      : Session::checkForMessage
//
// ^DESCRIPTION : This method checks to see if event messaging is set.
//
// ^PARAMETERS  : none
//
// ^RETURNS     : void -
//
// ^THROWS      : < description of all possible thrown exceptions >
//
// ^EXAMPLE     : < if the use of this member is not obvious,
//                  give an example >
//
//******************************************************************************
void BFCPSession::checkForMessage()
{
   TRACE_METHOD( I_("BFCPSession"), I_("checkForMessage()") );
   SESSION_MSG( I_("checkForMessage()"), I_("Messaging option *not* turned on") );
   s_usingMessage = false;
}

//*****************************************************************************
//
// ^PRIVATE METHOD      : BFCPSession::deleteChildren
//
// ^DESCRIPTION : Deletes all this object's children
//
// ^PARAMETERS  : none
//
// ^RETURNS     : void -
//
// ^THROWS      : none
//
//******************************************************************************
void BFCPSession::deleteChildren()
{
   BFCPSession *pChild;

   // Continue whaile there are children to delete
   while( ! m_childList.empty() )
   {
      // Grab the last child in the vector, then call pop_back
      pChild = *( m_childList.rbegin() );
      m_childList.pop_back();

      pChild->m_okToDelete = true;
      delete pChild;
   }
}

//******************************************************************************
//
// ^PRIVATE METHOD      : BFCPSession::removeFromChildList
//
// ^DESCRIPTION : Removes a child form the m_childList
//
// ^PARAMETERS  :
//   ^^ BFCPSession *child
//
// ^RETURNS     : bool - true if removed
//
// ^THROWS      : none
//
//******************************************************************************
bool BFCPSession::removeFromChildList( BFCPSession *child )
{
   TRACE_METHOD( I_("BFCPSession"), I_("removeFromChildList( BFCPSession * )") )

   // Initialize in a failed state
   bool removed = false;

   child_iterator childIter = m_childList.begin();

   // Compare the child to each child in the list until found or until
   //  we hit the end of the list.
   do
   {
      if( child == *childIter )
      {
         // child has been found.
         m_childList.erase( childIter );
         removed = true;

         SESSION_MSG( I_("removeFromChildList( BFCPSession * )"),
                      I_("Child Session removed from child list") );
      }

   } while( ( ! removed ) && ( ++childIter != m_childList.end() ) );

   return(removed);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfsessn/bfcpsession.cpp-arc  $
//
//   Rev 1.6   Mar 24 2005 16:36:32   popescu
//Incident# 272049, AWD time stamp retrieval fix
//
//   Rev 1.5   Oct 22 2004 08:58:34   PURDYECH
//PET910 - .NET Conversion Fixes
//
//   Rev 1.4   Apr 20 2004 10:47:34   PURDYECH
//PTS10024114 - Integrate changes from KC to deal with Double Locking in AWD.
//
//   Rev 1.3   Feb 24 2004 09:04:18   PURDYECH
//Add bLocked flag.  Non-standard extension to DST code.
// 
//    Rev 1.2   Oct 09 2002 17:41:02   PURDYECH
// New PVCS Database
// 
//    Rev 1.1   Aug 29 2002 12:51:04   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.0   28 May 2002 12:11:12   SMITHDAV
// Initial revision.
// 
//    Rev 1.14   May 04 2000 16:23:54   DMUM
// Made Session Thread aware
//
//    Rev 1.13   Aug 30 1999 16:22:56   DMUM
// The constructor for Session no longer throws
//
//    Rev 1.11   Jun 11 1999 09:21:12   DMUM
// Bug Fix
//
//    Rev 1.10   May 18 1999 08:50:06   DMUM
//
//
//    Rev 1.9   Apr 16 1999 17:43:06   DMUM
// Changes for Unicode
//
//    Rev 1.8   Apr 09 1999 13:29:58   DMUM
// Sync up with 1.6.x
//
//    Rev 1.4.1.0   Mar 31 1999 13:16:54   DMUM
//
//
//    Rev 1.1.1.4   Feb 26 1999 08:50:16   DMUM
// Development for TA2000 NT 3.4
//
//    Rev 1.1.1.3   Feb 11 1999 07:23:50   DMUM
// Now initializes m_pLogSession
//
//    Rev 1.1.1.2   Feb 08 1999 15:09:20   DMUM
// Changes for TA2000 NT 3.4
//
//    Rev 1.1.1.1   Dec 30 1998 13:00:52   DMUM
// Changes in TRACING
//
//    Rev 1.1.1.0   Nov 05 1998 13:14:06   DMUM
// Fixes ticket #5486
//
//    Rev 1.1   Jul 30 1998 16:40:46   dmum
// Fixed potential bug
//
//    Rev 1.0   29 Jul 1998 20:33:18   DT14596
// DLMG New Archives for TA2000NTDT
//
//    Rev 1.18   Jul 16 1998 11:47:30   dmum
// More developement
//
//    Rev 1.17   Apr 28 1998 08:47:02   dmum
// Added better tracing messages
//
//    Rev 1.16   Mar 27 1998 11:25:40   dmum
// Replaced the string_map with a Data object
//
//    Rev 1.15   Jan 13 1998 08:30:28   dmum
// Modified setSessionEvent
//
//    Rev 1.14   Jan 07 1998 09:30:02   dmum
// Fixed uninitialized m_pAwdSessoin pointer in a SubSession
//
//    Rev 1.13   Dec 30 1997 12:39:26   dmum
// Moved AWD specific methods to the new class
// BFAwdSession
//
//    Rev 1.12   10 Nov 1997 14:59:16   dmum
// Added redundancy guards and export/import guards
//
//    Rev 1.11   26 Sep 1997 16:20:40   dmum
// Now gets tags from SessionTags.h
//
//    Rev 1.10   20 Sep 1997 12:03:04   dmum
// Fixed problem where an BFAwdInterface object should
// not be created if not using BFAwd flag is set. Tracker # 1163
//
//    Rev 1.9   10 Sep 1997 11:13:18   dmum
// setSessionEvent() now returns SEVERITY
//
//    Rev 1.8   07 Aug 1997 15:54:12   dmum
// Inlines should not reference class static variables
//
//    Rev 1.7   07 Aug 1997 12:19:34   dmum
// Removed getAwdInterface, added usingAwd.
// Session now creates an BFAwdInterface object when needed instead
// of having one that is used all the time.
//
//    Rev 1.6   24 Jul 1997 13:28:08   dmum
// Added newline char "\n" to TRACE_MSG
//
//    Rev 1.5   24 Jul 1997 10:59:28   dmum
// Added tracing
//
//    Rev 1.4   18 Jul 1997 10:41:50   dmum
// Added method isAwdDefined,
// Method setSessionEvent no longer returns anything.
// It will always create a Condition object.
//
//    Rev 1.3   07 Jul 1997 08:13:52   dmum
// Fixed problems found through extensive testing
//
//    Rev 1.2   27 Jun 1997 10:50:06   dmum
// method in BFAwdInterface renamed from createAwdWork to createAwdTransaction
//
//    Rev 1.1   20 Jun 1997 15:23:26   dmum
// Documentation / fixed some problem areas
//
//    Rev 1.0   13 Jun 1997 18:42:46   dmum
//
//
//


