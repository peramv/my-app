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
// ^FILE   : BFLogSession.cpp
// ^AUTHOR : Michael McGarry
// ^DATE   : 2 Feb 1999
//
// ----------------------------------------------------------
//
// ^CLASS    : BFLogSession
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "win32/stdafx.h"

#include "bflogsession.hpp"
#include <configmanager.hpp>
#include <stringfunctions.hpp>
#include "odbclink.hpp"
#include "bfsessioncommon.hpp"
#include "bfcpsessiontags.h"

#define LOGSESSION_MSG( mthd, msg ) \
        TRACE_CLASS_MSG( I_("BFLogSession"), mthd, msg )

namespace
{
   const int MSG_LEN = 128;
   const int TAG_LEN = 30;
}

namespace SessionTags
{
   const I_CHAR *TABLE_LIST = I_("Log Table List");
   const I_CHAR *TABLE_1    = I_("LogTable_1");
   const I_CHAR *TABLE_2    = I_("LogTable_2");
   const I_CHAR *LOG_KEY    = I_("Log Key");
   const I_CHAR *ODBC_PTR   = I_("_ODBCLink_Ptr_");
   const I_CHAR *SOFT       = I_("SoftColumnCheck");
}

using namespace SessionTags;

//******************************************************************************
//              Public Methods
//******************************************************************************

BFLogSession::BFLogSession( BFCPSession *pSession,
                            ConfigManager *pManager,
                            bool master )
: m_pSession( pSession ),
m_pSessionCfgMgr( pManager ),
m_pSource( NULL ),
m_bMasterSession( master ),
m_bConnected( false ),
m_bEventRecorded( false ),
m_bSoftColumCheck( false )
{
   MAKEFRAMECONSTRUCTOR2( DISESSN_CONDITION, I_("BFLogSession"),
                          I_("BFLogSession( BFCPSession *, ConfigManager *, bool  )") )

   Configuration cfgLog = m_pSessionCfgMgr->retrieveConfig( EVENT_LOGGING );
   DString strSource = cfgLog.getValueAsString( LOG_SOURCE );

   if( !strSource.empty() )
   {
      if( m_bMasterSession )
      {
         try
         {
            DString strUser = cfgLog.getValueAsString( LOG_USER );
            DString strPassword = cfgLog.getValueAsString( LOG_PASSWORD );

            m_pSource = new ODBCLink();
            ASSERT_NEW( m_pSource, I_("BFLogSession::BFLogSession()") );

            m_pSource->connect( strSource, strUser, strPassword );

            // Store the pointer
            m_bConnected = true;
         }
         catch( ConditionException &ce )
         {
            LOGSESSION_MSG( I_("BFLogSession()"), ce.getMessage() );
            SETCONDITIONFROMEXCEPTION( ce )

            delete m_pSource;
            m_pSource = NULL;
            m_bConnected = false;
         }

         DString strSourcePtr = asString( (int)m_pSource );
         m_pSession->setGlobalSessionData( ODBC_PTR, strSourcePtr );
      }
      else
      {
         DString strSourcePtr = m_pSession->getSessionData( ODBC_PTR );
         m_pSource = (ODBCLink *)asInteger( strSourcePtr );
         m_bConnected = NULL != m_pSource;

         if( m_bConnected )
         {
            DString strKey;
            Configuration cfgKey = m_pSessionCfgMgr->retrieveConfig( LOG_KEY );
            Configuration::iterator cfgIter = cfgKey.begin();

            while( cfgIter != cfgKey.end() )
            {
               Configuration::ConfigPair &cfg = *cfgIter;
               strKey += m_pSession->getSessionData( cfg.getValueAsString() );
               ++cfgIter;
            }

            m_pSession->setSessionData( LOG_KEY, strKey );
            m_strKeyColumn = cfgLog.getValueAsString( LOG_KEY );
         }
      }

      if( m_bConnected )
      {
         m_strTable1 = cfgLog.getValueAsString( TABLE_1 );
         m_strTable2 = cfgLog.getValueAsString( TABLE_2 );

         DString strSoft = cfgLog.getValueAsString( SOFT );
         m_bSoftColumCheck = ( ! strSoft.empty() && ( 'Y' == strSoft[0] ) );
      }
   }

   PROMOTECONDITIONS();
}

BFLogSession::~BFLogSession()
{
   TRACE_DESTRUCTOR( I_("BFLogSession") )

   if( m_bMasterSession )
   {
      delete m_pSource;
   }
   else
   {
      if( m_bConnected )
      {
         BFData logData;
         DString strIdi;
         DString strTable = TABLE_1;

         translate( strTable, m_strTable1, NULL, &m_collector, logData );
         logData.getAllValues( strIdi );

         if( ! strIdi.empty() )
         {
            appendKey( strIdi );
            m_pSource->addRow( m_strTable1, strIdi, m_bSoftColumCheck );
         }
      }
   }
}

//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//
// ^PRIVATE METHOD      : BFLogSession::logEvent
//
// ^DESCRIPTION :
//
// ^PARAMETERS  :
//   ^^ const DString   &strLogItem -
//   ^^ const Configuration &cfgEvent -
//   ^^ const data_ptr_map  &data -
//
// ^RETURNS     : bool -
//
// ^THROWS      : < description of all possible thrown exceptions >
//
// ^EXAMPLE     : < if the use of this member is not obvious,
//                  give an example >
//
//******************************************************************************
bool BFLogSession::logEvent( const DString   &strLogItem,
                             const Configuration &cfgEvent,
                             const BFDataPtrMap& data )
{
   MAKEFRAMEAUTOPROMOTE( DISESSN_CONDITION,
                         I_( "BFLogSession::logEvent( const DString &, const " )
                         I_( "Configuration &, const data_ptr_map  & )" ) )

   bool success = false;

   if( m_bConnected )
   {
      // Make sure this is a log event
      bool bLogEvent = ! strLogItem.empty() && 'Y' == strLogItem[0];

      // See if this a paper event
      if( BFCPSession::usingAwd() )
      {
         DString strPaper = m_pSession->getSessionData( ORIGINATION );

         if( ORIG_PAPER == strPaper )
         {
            DString strPaperItem = cfgEvent.getValueAsString( LOG_PITEM );
            bLogEvent = ! strPaperItem.empty() && 'Y' == strPaperItem[0];
         }
      }

      if( ! bLogEvent )
      {
         // Check the override
         DString strLogEvent = m_pSession->getSessionData( LOG_EVENT );
         bLogEvent = ! strLogEvent.empty() && 'Y' == strLogEvent[0];
      }

      if( bLogEvent && ! data.empty() )
      {
         const BFData *pDefault = NULL;  // Default data opbject to search in
         const BFData *pPrimary = NULL;  // Primary data opbject to search in

         // Get the primary data
         DString strPrimary = cfgEvent.getValueAsString( PRIMARY );

         if( strPrimary.empty() )
         {
            strPrimary = cfgEvent.getName();
         }

         BFDataPtrMap_Const_Iter iter = data.find( strPrimary );

         if( iter != data.end() )
         {
            pPrimary = ( *iter ).second;
         }

         // Get the default data
         iter = data.find( DEFAULT );

         if( iter != data.end() )
         {
            pDefault = ( *iter ).second;
         }

         if( NULL == pPrimary && NULL == pDefault )
         {
            iter = data.begin();
            pDefault = ( *iter ).second;
         }

         if( pPrimary )
         {
            m_collector.setValues( *pPrimary, true );
         }
         else
         {
            m_collector.setValues( *pDefault, true );
         }

         BFData logData;
         DString strIdi;
         DString strTable = TABLE_2;

         translate( strTable, m_strTable2, pPrimary, pDefault, logData );
         logData.getAllValues( strIdi );

         if( ! strIdi.empty() )
         {
            appendKey( strIdi );
            m_pSource->addRow( m_strTable2, strIdi, m_bSoftColumCheck );

            success = WARNING > GETHIGHESTSEVERITY();
            setEventRecorded( success );
         }
      }
   }

   return(success);
}

//******************************************************************************
//
// ^PRIVATE METHOD      : BFLogSession::translate
//
// ^DESCRIPTION :
//
// ^PARAMETERS  :
//   ^^ const DString &strTable -
//   ^^ const DString &strTableName -
//   ^^ const BFData *pPrimary -
//   ^^ const BFData *pDefault -
//   ^^ BFData &logData -
//
// ^RETURNS     : void -
//
// ^THROWS      : < description of all possible thrown exceptions >
//
// ^EXAMPLE     : < if the use of this member is not obvious,
//                  give an example >
//
//******************************************************************************
void BFLogSession::translate( const DString &strTable,
                              const DString &strTableName,
                              const BFData *pPrimary,
                              const BFData *pDefault,
                              BFData &logData )
{
   TRACE_METHOD( I_( "BFLogSession" ),
                 I_( "translate( const DString &, const DString &, const " )
                 I_( "Data *, const BFData *, BFData & )" ) )

   DString tag;              // Tag used by application
   DString column;           // Column in clients BFData Source

#ifdef ENABLE_TRACING
   DString msg;              // Used for trace messages
#endif

   // Get the translation table
   Configuration xtable = m_pSessionCfgMgr->retrieveConfig( strTable );

   // Iterate through the translation table
   Configuration::iterator xiter = xtable.begin();

   while( xiter != xtable.end() )
   {
      // Identify our tag for the value
      tag = ( *xiter ).getKey();
      // Identify the clients tag (dataname) for the value
      column = ( *xiter ).getValueAsString();

      // If the client's tag is defined, look for the value
      if( ! ( column.empty() || tag.empty() ) )
      {
         // Initialize our value
         DString value = I_("");

         if( pPrimary && pPrimary->exists( tag ) )
         {
            value = pPrimary->getElementValue( tag );
            strip( value );
         }

         if( value.empty() && pDefault && pDefault->exists( tag ) )
         {
            value = pDefault->getElementValue( tag );
            strip( value );
         }

         // If the value has not been found, check session data.
         if( value.empty() )
         {
            value = m_pSession->getSessionData( tag );
            strip( value );
         }

         // If we have a value,
         if( ! value.empty() )
         {
            // Store the tag-converted data
            logData.setElementValue( column, value, true );

#ifdef ENABLE_TRACING
            // Trace the translation
            msg = I_("LOG data set for ");
            msg += padRight( tag, TAG_LEN );
            msg += I_(": ");
            msg += strTableName;
            msg += I_(".");
            msg += column;
            msg += I_(" = ");
            msg += value;
            LOGSESSION_MSG( I_("translate()"), msg.c_str() );
#endif
         }
      }

      ++xiter;
   }
}

//******************************************************************************
//
// ^PRIVATE METHOD      : BFLogSession::appendKey
//
// ^DESCRIPTION :
//
// ^PARAMETERS  :
//   ^^ DString &strIdi -
//
// ^RETURNS     : void -
//
// ^THROWS      : < description of all possible thrown exceptions >
//
// ^EXAMPLE     : < if the use of this member is not obvious,
//                  give an example >
//
//******************************************************************************
void BFLogSession::appendKey( DString &strIdi )
{
   TRACE_METHOD( I_("BFLogSession"), I_("appendKey( DString & )") )
   DString strKey = m_pSession->getSessionData( LOG_KEY );

   // If the key column is identified and we have a key value
   // append it to the idi string
   if( ! ( m_strKeyColumn.empty() && strKey.empty() ) )
   {
      strIdi += m_strKeyColumn;
      strIdi += I_("=");
      strIdi += strKey;
      strIdi += I_(";");

#ifdef ENABLE_TRACING
      // Trace the translation
      DString msg;
      msg = I_("LOG data Event Link : ");
      msg += m_strKeyColumn;
      msg += I_(" = ");
      msg += strKey;
      LOGSESSION_MSG( I_("appendKey()"), msg.c_str() );
#endif
   }
}

void BFLogSession::setEventRecorded( bool recorded )
{
   m_bEventRecorded |= recorded;
   m_pSession->setEventRecorded( recorded );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfsessn/bflogsession.cpp-arc  $
//
//   Rev 1.2   Oct 22 2004 08:58:38   PURDYECH
//PET910 - .NET Conversion Fixes
// 
//    Rev 1.1   Oct 09 2002 17:41:02   PURDYECH
// New PVCS Database
// 
//    Rev 1.0   28 May 2002 12:11:12   SMITHDAV
// Initial revision.
// 
//    Rev 1.11   Jun 12 2000 06:45:48   dtwk
// Fix UNICODE build
// 
//    Rev 1.10   Jun 09 2000 12:19:16   DMUM
// Sync up with 1.7
//
//    Rev 1.9   13 Jan 2000 16:28:38   dt20842
// Added back in ODBC support
//
//    Rev 1.8   Aug 30 1999 16:22:54   DMUM
// The constructor for BFCPSession no longer throws
//
//    Rev 1.6   Jul 14 1999 10:08:50   DMUM
// Cleanup on temporary removal of ODBC dependancy
//
//    Rev 1.5   Jul 13 1999 16:23:38   dtwk
//
//
//    Rev 1.4   Jun 09 1999 16:21:22   DMUM
// Now supports soft column check to work with an
// ODBC Source that is a text file.
//
//    Rev 1.3   May 18 1999 08:50:02   DMUM
//
//
//    Rev 1.2   Apr 16 1999 17:43:02   DMUM
// Changes for Unicode
//
//    Rev 1.1   Apr 09 1999 13:29:56   DMUM
// Sync up with 1.6.x
//
//    Rev 1.0.2.0   Mar 31 1999 13:16:52   DMUM
//
//
//    Rev 1.0.1.0   Feb 26 1999 08:50:12   DMUM
// Development for TA2000 NT 3.4
//
//    Rev 1.0   Feb 08 1999 14:47:50   DMUM
//
//
//

