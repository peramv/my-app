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
// ^FILE   : BFAwdSession.cpp
// ^AUTHOR : Michael McGarry
// ^DATE   : 26 Dec 97
//
// ----------------------------------------------------------
//
// ^CLASS    : BFAwdSession
//
// ^MEMBER VARIABLES :
//    ^^Session        *m_pSession       - Pointer to owning BFCPSession object
//    ^^BFAwdKey         *m_pCase          - Pointer to case
//    ^^BFAwdData        *m_pCaseData      - Pointer to case data
//    ^^BFAwdKey         *m_pProcessCase   - Pointer to Parent case of m_pAwdWork
//    ^^BFAwdData        *m_pAwdWork       - Pointer to Work Selected object
//    ^^awd_event_list  m_eventList      - event list
//    ^^ConfigManager  *m_sessionCfgMgr  - BFCPSession's Configuration Manager
//    ^^bool            m_masterSession  - True if oning BFCPSession is a master
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "win32/stdafx.h"

#include "bfawdsession.hpp"
#include <bfawdi\bfawddata.hpp>
#include <bfawdi\bfawdinterface.hpp>
#include "bfsessn.h"

#include <configmanager.hpp>
#include <configuration.hpp>
#include <configmacro.h>
#include <conditionmanager.hpp>
#include <stringfunctions.hpp>

// must be changed?
#include <base.h>
#include "bfcpsessiontags.h"
#include "bfsessioncommon.hpp"

#define AWDSESSION_MSG( mthd, msg ) \
        TRACE_CLASS_MSG( I_("BFAwdSession"), mthd, msg )

namespace SessionTags
{
   const I_CHAR *HOLD_NEW_BEGIN_TIME = I_("HOLD_NEW_BEGIN_TIME");
   const I_CHAR *CALL_START_TIME     = I_("STIM");
   const I_CHAR *CALL_END_TIME       = I_("ETIM");
   const I_CHAR *LINK_SOURCE         = I_("LinkSource");
   const I_CHAR *AWD_PTR             = I_("_AwdInterface_Ptr_");
}

using namespace SessionTags;

namespace
{
   const int MAX_COMMENT_LEN = 720;
   const int MSG_LEN         = 128;
   const int TAG_LEN         = 30;
}

BFAwdSession::BFAwdSession( BFCPSession *pSession,
                            ConfigManager *pManager,
                            bool master )
: m_pSession( pSession ),
m_pCase( NULL ),
m_pProcessCase( NULL ),
m_pAwdWork( NULL ),
m_sessionCfgMgr( pManager ),
m_masterSession( master ),
m_hasCaseForParent( false ),
m_processWorkUpdated( false ),
m_lastEventPropagated( false ),
m_callTimeSet( false ),
m_caseOnMultiple( false ),
m_caseOnMultipleP( false ),
m_workCount( 0 ),
m_pAwd( NULL ),
m_pCaseData( NULL ),
m_haveListener( false ),
m_pProcessSource( NULL ),
m_linkSource( false ),
m_eventRecorded( false )
{
   MAKEFRAMECONSTRUCTOR2( DISESSN_CONDITION, I_("BFAwdSession"),
                          I_("BFAwdSession( BFSession *, ConfigManager *, bool master )") )

   if( m_masterSession )
   {
      try
      {
         // If we are using Awd make sure the operator is logged on
         if( BFAwdInterface::isLoggedOn() )
         {
            m_pAwd = new BFAwdInterface;

            DString opid = m_pAwd->getOperatorID();

            m_pSession->setGlobalSessionData( AWD_ID, opid );
            m_pAwd->openAwdContainer();

            DString strSourcePtr = asString( (int)m_pAwd );
            m_pSession->setGlobalSessionData( AWD_PTR, strSourcePtr );
         }
         else
         {
            // AWD is to be used, and the operator is not logged on.
            ADDCONDITIONFROMFILE( DISESSN_AWD_NOT_LOGGED_ON );
         }
      }
      catch( ConditionException &ce )
      {
         SETCONDITIONFROMEXCEPTION( ce )
      }
      catch( ... )
      {
      }
   }
   else
   {
      DString strSourcePtr = m_pSession->getSessionData( AWD_PTR );
      m_pAwd = (BFAwdInterface *)strSourcePtr.asInteger();
      m_haveListener = m_pAwd->beginListenCreateObjects();
   }

   // Determine is we are to create a case when multiple work objects exist
   Configuration cfgAwdCase = m_sessionCfgMgr->retrieveConfig( AWD_CASE );
   DStringA strAwdCase = cfgAwdCase.getValueAsString( AWD_CASE );
   m_caseOnMultiple = ( ! strAwdCase.empty() && ( 'M' == strAwdCase[0] ) );
   // Also check the paper case
   cfgAwdCase = m_sessionCfgMgr->retrieveConfig( AWD_PCASE );
   strAwdCase = cfgAwdCase.getValueAsString( AWD_CASE );
   m_caseOnMultipleP |= ( ! strAwdCase.empty() && ( 'M' == strAwdCase[0] ) );

   DStringA strLink = GetConfigValueAsString( CONFIG, USE_AWD, LINK_SOURCE );
   m_linkSource = ( ! strLink.empty() && ( 'Y' == strLink[0] ) );

   // Default to phone
   m_pSession->setSessionData( ORIGINATION, ORIG_PHONE );

   PROMOTECONDITIONS();
}

BFAwdSession::~BFAwdSession()
{
   TRACE_DESTRUCTOR( I_("BFAwdSession") )

   if( m_pAwd )
   {
      // If we have a case, and we are not paper, and the call time is not set ...
      if( m_pCaseData && ! ( m_pAwdWork || m_callTimeSet ) )
      {
         DString startTime = m_pSession->getSessionData( CALL_START );
         DString endTime = m_pSession->getSessionData( CALL_END );

         if( ! ( startTime.empty() || endTime.empty() ) )
         {
            m_pCaseData->setLobData( CALL_START_TIME, startTime );
            m_pCaseData->setLobData( CALL_END_TIME, endTime );
            m_pAwd->updateAwdObject( *m_pCaseData );
         }
      }

      if( m_haveListener )
      {
         BFAwdKeyVector keyList = m_pAwd->endListenCreateObjects();

         BFAwdKeyVector::reverse_iterator iter;

         while( ! keyList.empty() )
         {
            iter = keyList.rbegin();

            BFAwdKey *pKey = *iter;

            try
            {
               m_pAwd->lockAwdObject( pKey, false );
            }
            catch( ConditionException &ce )
            {
               MAKEFRAMENOTRACE( DISESSN_CONDITION,
                                 I_("BFAwdSession::~BFAwdSession( bool )") );
               SETCONDITIONFROMEXCEPTION( ce )
            }

            delete pKey;

            keyList.pop_back();
         }
      }

      relateWorkToCase( true );
      deleteAwdList();

      if( m_masterSession )
      {
         m_pAwd->closeAwdContainer();
         delete m_pAwd;
      }
      else
      {
         m_pAwd->clearAwdContainer();
      }

      // START KC INFRA FIXES 15Apr2004
      // The objcets from which CSDs are launched should be deleted after
      // the clear/close container. - DT21858
      BFAwdDataVector::reverse_iterator csdIter;

      while ( ! m_csdList.empty() )
      {
         csdIter = m_csdList.rbegin();
         BFAwdData *pData = ( *csdIter ).pData;

         // The stopCSD should no longer be needed.  This line has been
         // commented out and not deleted just in case it needs to be
         // re-inserted. - DT21858
         //
         // m_pAwd->stopCSD( pData->getKey() );

         ::Sleep( 200 );

         delete pData;

         m_csdList.pop_back();
      }
      // END KC INFRA FIXES 15Apr2004
   }
}

bool BFAwdSession::isAwdDefined( const DString &event )
{
   bool awdDefined = false;

   Configuration eventCfg = m_sessionCfgMgr->retrieveConfig( event );

   // Make sure event is defined
   if( ! eventCfg.isEmpty() )
   {
      // Check for Awd work
      DString awdWork = eventCfg.getValueAsString( AWD_WORK );

      awdDefined = ! awdWork.empty();
   }

   return(awdDefined);
}

bool BFAwdSession::getAwdWork()
{
   TRACE_METHOD( I_("BFAwdSession"), I_("getAwdWork()") );

   BFAwdData *pWork = new BFAwdData;
   ASSERT_NEW( pWork, I_("BFAwdSession::getAwdWork()") );

   m_pAwd->getAwdWork( *pWork );

   return(setProcessWork( pWork, true ));
}

bool BFAwdSession::setProcessWork( BFAwdData *pWork, bool reset )
{
   TRACE_METHOD( I_("BFAwdSession"), I_("setProcessWork( BFAwdData * )") )
   m_processWorkUpdated = false;

   // If we already have one, delete it so we don't have a memory leak.
   if( m_pAwdWork )
   {
      // Unlock it first
      m_pAwd->lockAwdObject( m_pAwdWork->getKey(), false );
      delete m_pAwdWork;

      m_pAwdWork = NULL;
   }

   // If we already have a Process Case, delete it
   if( reset )
   {
      if( m_pProcessSource )
      {
         // Unlock it first
         m_pAwd->lockAwdObject( m_pProcessSource, false );
         delete m_pProcessSource;

         m_pProcessSource = NULL;
      }

      if( m_pProcessCase )
      {
         // Unlock it first
         m_pAwd->lockAwdObject( m_pProcessCase, false );
         delete m_pProcessCase;

         m_pProcessCase = NULL;
      }

      if( m_pCaseData )
      {
         // Unlock it first
         m_pAwd->lockAwdObject( m_pCase, false );
         delete m_pCaseData;

         m_pCaseData = NULL;
         m_pCase = NULL;
      }

      m_hasCaseForParent = false;
   }

   if( pWork == NULL )
   {
	   return false;
   }

   // Query the object's Key
   const BFAwdKey *pKey = pWork->getKey();

   // Make sure the key is valid
   if( pKey && pKey->isKey() )
   {
      // Remember the Work ( it will be deleted in ~BFAwdSession() )
      m_pAwdWork = pWork;
      m_workCount = 1;

      AWDSESSION_MSG( I_("setProcessWork()"), I_("Process Work has been set") );

      if( reset )
      {
         // See if this work has a parent that is a case
         BFAwdKey *pParent = NULL;
         m_hasCaseForParent = m_pAwd->hasCaseForParent( pKey, &pParent );

         if( m_hasCaseForParent )
         {
            m_pProcessCase = pParent;
            AWDSESSION_MSG( I_("setProcessWork()"),
                            I_("Found an existing Case for the Process Work") );
         }

         // See if this work has a child that is a source
         if( m_linkSource )
         {
            if( m_pAwd->hasSourceForChild( pKey, &m_pProcessSource ) )
            {
               AWDSESSION_MSG( I_("setProcessWork()"),
                               I_("Found an existing Image for the Process Work") );
            }
         }
      }
   }
   else
   {
      delete pWork;
   }

   bool isPaper = NULL != m_pAwdWork;

   if( isPaper )
   {
      // Let everyone know we are paper
      m_pSession->setSessionData( ORIGINATION, ORIG_PAPER );
   }

   return(isPaper);
}

void BFAwdSession::getCreateDefaults( const DString &event,
                                      DString &busarea,
                                      DString &worktype,
                                      DString &status,
                                      bool    process )
{
   TRACE_METHOD( I_("BFAwdSession"),
                 I_("getCreateDefaults( const DString &, DString &, ")
                 I_("DString & ,DString &, bool )") )


   Configuration eventCfg = m_sessionCfgMgr->retrieveConfig( event );

   // Make sure event is defined
   if( ! eventCfg.isEmpty() )
   {
      // Check for Awd work
      DString awdWork;

      // If we have a process work object get the "paper" work
      if( m_pAwdWork )
      {
         awdWork = eventCfg.getValueAsString( AWD_PWORK );
      }
      else
      {
         awdWork = eventCfg.getValueAsString( AWD_WORK );
      }

      if( ! awdWork.empty() )
      {
         Configuration workCfg = m_sessionCfgMgr->retrieveConfig( awdWork );

         if( ! workCfg.isEmpty() )
         {
            busarea = workCfg.getValueAsString( BUSINESS_AREA );
            worktype = workCfg.getValueAsString( WORK_TYPE );

            if( process )
            {
               status = workCfg.getValueAsString( PSTATUS );
            }
            else
            {
               status = workCfg.getValueAsString( ISTATUS );
            }
         }
      }
   }

#ifdef ENABLE_TRACING
   DString msg = I_("Default AWD parameters for ");
   msg += event;
   msg += I_(" are ");
   msg += busarea;
   msg += I_(", ");
   msg += worktype;
   msg += I_(", ");
   msg += status;
   AWDSESSION_MSG( I_("getCreateDefaults()"), msg.c_str() );
#endif
}

bool BFAwdSession::createAwdCase( const BFData &datum, bool updateExisting )
{
   MAKEFRAMEAUTOPROMOTE( DISESSN_CONDITION,
                         I_("BFAwdSession::createAwdCase( const BFData & )") )

   bool success = false;

   // Clear out any comment that may be lingering
   m_pSession->setSessionData( AWD_COMMENT, I_("") );

   // Grab the config object for an AWD case
   Configuration caseCfg;

   if( m_pAwdWork )
   {
      caseCfg = m_sessionCfgMgr->retrieveConfig( AWD_PCASE );
   }
   else
   {
      caseCfg = m_sessionCfgMgr->retrieveConfig( AWD_CASE );
   }

   DString makeCase = caseCfg.getValueAsString( AWD_CASE );

   bool create = false;

   if( ! makeCase.empty() )
   {
      DString createCase = m_pSession->getSessionData( CREATE_CASE );
      bool checkUpdate = true;

      switch( makeCase[0] )
      {
         case 'Y':
            create = ( NULL == m_pCaseData );
            break;

         case 'M':
            create = ( ( NULL == m_pCaseData ) && ( 1 < m_workCount ) );
            break;

         case 'I':
            create = ( createCase == makeCase );
            break;

         default:
            checkUpdate = false;
            create = false;
            break;
      }

      if( ( ! create ) && checkUpdate )
      {
         create = ( updateExisting && ( NULL != m_pCaseData ) );
      }
   }

   if( create )
   {
      // Set these for preProcess() to use
      caseCfg.set( PRIMARY, DString( AWD_CASE ) );
      caseCfg.set( TABLE, DString( CASE_TABLE ) );

      // Check to see if we found a parent case for our process work
      if( m_pProcessCase )
      {
         if( m_pCaseData )
         {
            m_pAwd->lockAwdObject( m_pCase, false );
            delete m_pCaseData;
         }

         // Let the case be the process case and reset the process case
         m_pCaseData = new BFAwdData;
         m_pAwd->retrieveData( m_pProcessCase, *m_pCaseData );
         m_pCase = m_pCaseData->getKey();

         delete m_pProcessCase;
         m_pProcessCase = NULL;
      }

      // Create a data pointer map to pass to preProcess
      BFDataPtrMap data;

      // The case collecter is now the primary object since the data
      // passed in is unreliable.
      data.insert( BFDataPtrMap::value_type( AWD_CASE, &m_caseCollector ) );
      data.insert( BFDataPtrMap::value_type( DEFAULT, &datum ) );

      // If we already have a case, update it.
      if( m_pCaseData )
      {
         // Only update if the flag "updateExisting" is true
         if( updateExisting )
         {
            // Copy the data over
            preProcess( caseCfg, data, *m_pCaseData, true );

            // If we are not paper and we have not set the call time
            if( ! ( m_pAwdWork || m_callTimeSet ) )
            {
               DString startTime = m_pSession->getSessionData( CALL_START );
               DString endTime = m_pSession->getSessionData( CALL_END );

               // If we have both a start and an end time
               if( ! ( startTime.empty() || endTime.empty()) )
               {
                  // Store them in this case
                  m_pCaseData->setLobData( CALL_START_TIME, startTime );
                  m_pCaseData->setLobData( CALL_END_TIME, endTime );
                  m_callTimeSet = true;
               }
            }

            AWDSESSION_MSG( I_("createAwdCase()"),
                            I_("About to update the AWD Case") );

            try
            {
               success = m_pAwd->updateAwdObject( *m_pCaseData );
            }
            catch( ConditionException &ce )
            {
               SETCONDITIONFROMEXCEPTION( ce )
               success = false;
            }

            // Let the clean-up know this is a case and not to add to the list
            if( success )
            {
               postProcess( *m_pCaseData );
            }
         }
      }
      else
      {
         DString busarea = caseCfg.getValueAsString( BUSINESS_AREA );
         DString worktype = caseCfg.getValueAsString( WORK_TYPE );
         DString status = caseCfg.getValueAsString( STATUS );

         // If we do not have all three
         if( busarea.empty() || worktype.empty() || status.empty() )
         {
            // Create a condition
            ADDCONDITIONFROMFILE( DISESSN_UNDEFINED_AWD_PARAMETER );
         }
         else
         {
            m_pCaseData = new BFAwdData( busarea, worktype, status );

            // Copy the data over
            preProcess( caseCfg, data, *m_pCaseData, true );

            AWDSESSION_MSG( I_("createAwdCase()"),
                            I_("About to create an AWD Case") );

            try
            {
               success = m_pAwd->createAwdCase( *m_pCaseData, true );
            }
            catch( ConditionException &ce )
            {
               SETCONDITIONFROMEXCEPTION( ce )
               success = false;
            }

            setEventRecorded( success );

            // Let the clean-up know this is a case and not to add to the list
            if( success )
            {
               m_pCase = m_pCaseData->getKey();
               postProcess( *m_pCaseData );
               relateWorkToCase( false );
            }
            else
            {
               delete m_pCaseData;
               m_pCaseData = NULL;
               m_pCase = NULL;
            }
         }
      }
   }

   // Reset create case
   m_pSession->setSessionData( CREATE_CASE, I_("") );

   return(success);
}

bool BFAwdSession::createAwdTransaction( const BFData &datum, BFAwdData &awdData )
{
   MAKEFRAMEAUTOPROMOTE( DISESSN_CONDITION,
                         I_("BFAwdSession::createAwdTransaction( const BFData & BFAwdData & )") )

   bool success = false;
   const BFAwdKey *pKey = awdData.getKey();

   // Make sure that the BFAwdData is not already an object in the database
   if( ( ! pKey ) || ( pKey && ! pKey->isKey() ) )
   {
      Configuration cfg;
      cfg.set( PRIMARY, DString( AWD_WORK ) );
      cfg.set( TABLE, DString( WORK_TABLE ) );

      // Create a data pointer map to pass to preProcess
      BFDataPtrMap data;
      data.insert( BFDataPtrMap::value_type( AWD_WORK, &datum ) );

      const DString &busarea = awdData.getUnit();
      const DString &worktype = awdData.getWrkt();
      const DString &status = awdData.getStat();

      if( busarea.empty() || worktype.empty() || status.empty() )
      {
         // Create a condition
         ADDCONDITIONFROMFILE( DISESSN_UNDEFINED_AWD_PARAMETER );
      }
      else
      {
         preProcess( cfg, data, awdData, false );

         AWDSESSION_MSG( I_("createAwdTransaction()"),
                         I_("About to create an AWD Transaction") );

         try
         {
            success = m_pAwd->createAwdTransaction( awdData, true );
         }
         catch( ConditionException &ce )
         {
            SETCONDITIONFROMEXCEPTION( ce )
            success = false;
         }

         if( success )
         {
            postProcess( awdData, true );
         }
      }
   }

   return(success);
}

bool BFAwdSession::updateTransactions( const BFData &datum )
{
   MAKEFRAMEAUTOPROMOTE( DISESSN_CONDITION,
                         I_("BFAwdSession::updateTransactions( const BFData & )") )

   bool success = true;

   BFAwdData awdData;
   Configuration cfg;
   cfg.set( PRIMARY, DString( AWD_WORK ) );
   cfg.set( TABLE, DString( WORK_TABLE ) );

   // Create a data pointer map to pass to preProcess
   BFDataPtrMap data;
   data.insert( BFDataPtrMap::value_type( AWD_WORK, &datum ) );

   preProcess( cfg, data, awdData, false );

   awd_event_iterator iter = m_eventList.begin();

   while( iter != m_eventList.end() )
   {
      BFAwdData update( awdData );
      BFAwdKey *pKey = ( *iter ).key->makeCopy();
      update.setKey( pKey );

      try
      {
         success &= m_pAwd->updateAwdObject( update );
      }
      catch( ConditionException &ce )
      {
         SETCONDITIONFROMEXCEPTION( ce )
      }

      ++iter;
   }

   return(success);
}

bool BFAwdSession::loadAwdCsd( BFAwdData &awdData )
{
   bool success = false;
   const BFAwdKey *pKey = awdData.getKey();

   if( pKey && pKey->isKey() )
   {
      BFAwdData *pData = new BFAwdData( awdData );

      success = m_pAwd->loadCSD( *pData );

      if( success )
      {
         BFAwdDataItem item = { false, pData};

         m_csdList.push_back( item );
      }
      else
      {
         delete pData;
      }
   }
   else
   {
      success = m_pAwd->loadCSD( awdData );
   }

   return(success);
}

unsigned long BFAwdSession::convertToAwdTags( const BFData &source, BFData &dest )
{
   TRACE_METHOD( I_("BFAwdSession"),
                 I_("convertToAwdTags( const BFData &, BFData & )") )

   BFData data;
   unsigned long converted = 0;
   DString conversion;
   Configuration table;
   getExportTable( table );

   // This will need to be changed when class BFData has an iterator
   int index = 0;
   int count = 0;
   int position = 0;

   DString idiString;
   DString pair;
   DString tag;
   DString value;

   // Create an IDI string
   source.getAllValues( idiString );

   // Traverse the IDI string passing CallTracker one tag=value pair
   // at a time.
   while( ( position = idiString.find( ';', index ) ) != DString::npos )
   {
      count = position - index;
      pair = idiString.substr( index, count );
      index = position + 1;

      // Make sure there is an '='
      position = pair.find( '=' );

      if( DString::npos != position )
      {
         tag = pair.substr( 0, position );
         value = pair.substr( position + 1 );
         strip( tag );
         strip( value );

         // Make sure the value is not empty
         if( ! value.empty() )
         {
            conversion = table.getValueAsString( tag );

            if( ! conversion.empty() )
            {
               ++converted;
            }
            else
            {
               conversion = tag;
            }

            data.setElementValue( conversion, value, true );
         }
      }
   }

   dest = data;

   return(converted);
}


//******************************************************************************
//              Private Methods
//******************************************************************************
void BFAwdSession::getExportTable( Configuration &exportTable )
{
   exportTable = m_sessionCfgMgr->retrieveConfig( EXPORT_TABLE );

   // If the table is empty, build it from the case and work tables
   if( exportTable.isEmpty() )
   {
      DString tag;
      ConfigValue value;

      Configuration caseTable = m_sessionCfgMgr->retrieveConfig( CASE_TABLE );
      Configuration workTable = m_sessionCfgMgr->retrieveConfig( WORK_TABLE );

      Configuration::iterator iter = caseTable.begin();

      while( iter != caseTable.end() )
      {
         value = ( *iter ).getValue();

         if( ! value.asString().empty() )
         {
            tag = ( *iter ).getKey();
            exportTable.set( tag, value );
         }

         ++iter;
      }

      iter = workTable.begin();

      while( iter != workTable.end() )
      {
         value = ( *iter ).getValue();

         if( ! value.asString().empty() )
         {
            tag = ( *iter ).getKey();
            exportTable.set( tag, value );
         }

         ++iter;
      }

      m_sessionCfgMgr->storeConfig( exportTable );
   }
}


//******************************************************************************
//
// ^PRIVATE METHOD      : BFAwdSession::awdEvent
//
// ^DESCRIPTION : Process an AWD event
//
// ^PARAMETERS  :
//   ^^ const string &awdwork         - Work to be created
//   ^^ const Configuration &eventcfg - the event's configuration object
//   ^^ const data_ptr_map &data      - Collection of pointers to BFData objects
//
// ^RETURNS     : bool - True if an AWD work object was successfully created
//
// ^THROWS      : none
//
//******************************************************************************
bool BFAwdSession::awdEvent( const DString &awdWork,
                             const Configuration &eventCfg,
                             const BFDataPtrMap &data,
                             bool bLocked )
   //CP20040224 Added bLocked at urging of YingBao Li.  Non-standard change to DST code
{
   MAKEFRAMEAUTOPROMOTE( DISESSN_CONDITION,
                         I_( "BFAwdSession::awdEvent( const DString &, const " )
                         I_( "Configuration &, const BFDataPtrMap & )" ) )

   bool success = false;
   bool noWork = false;

   DString busarea;
   DString worktype;
   DString status;

   // Grab the begin time
   DString begin = m_pSession->getSessionData( BEGIN_TIME );

   // Determine if we are propagating
   DStringA propagate = m_pSession->getSessionData( AWD_PROPAGATE );
   bool propagating = ( ! propagate.empty() ) && ( 'Y' == propagate[0] );

   //
   // If a begin time has not been set, see if there is a new begin
   // time on hold.  A new begin time may be on hold if the last event
   // was a propagation event and this one is not.
   //
   if( begin.empty() && ( ! propagating ) && m_lastEventPropagated )
   {
      DString newBeginTime = m_pSession->getSessionData( HOLD_NEW_BEGIN_TIME );

      if( ! newBeginTime.empty() )
      {
         begin = newBeginTime;
         m_pSession->setSessionData( HOLD_NEW_BEGIN_TIME, I_("") );
      }
   }

   // Determine if we will create work or update work
   DString awdEvent = m_pSession->getSessionData( AWD_EVENT );

   if( awdEvent.empty() )
   {
      // Default to create work
      awdEvent = CREATE_WORK;
   }

   // See if we're not supposed to create work
   if( NO_WORK == awdEvent )
   {
      noWork = true;
      success = true;
   }
   else
   {
      // We're supposed to create work, get the values
      busarea = m_pSession->getSessionData( BUSINESS_AREA );
      worktype = m_pSession->getSessionData( WORK_TYPE );
      status = m_pSession->getSessionData( STATUS );

      // if any one of these is not in the session object
      if( busarea.empty() || worktype.empty() || status.empty() )
      {
         // See if this is a hllapi event
         DString hllapi = eventCfg.getValueAsString( HLLAPI );

         if( ! hllapi.empty() )
         {
            const BFData *pDatum;

            // Grab the data object indicated by hllapi
            BFDataPtrMap_Const_Iter iter = data.find( hllapi );

            // make sure we have the data object
            if( iter != data.end() )
            {
               // Grab the data object
               pDatum = ( *iter ).second;

               // Grab the business area
               if( pDatum->exists( BUSINESS_AREA ) )
               {
                  busarea = pDatum->getElementValue( BUSINESS_AREA );
               }

               // Grab the worktype
               if( pDatum->exists( WORK_TYPE ) )
               {
                  worktype = pDatum->getElementValue( WORK_TYPE );
               }

               // Grab the status
               if( pDatum->exists( STATUS ) )
               {
                  status =  pDatum->getElementValue( STATUS );
               }
            }
         }
         else
         {
            // This is not a HLLAPI event, lets try to use the defaults
            DString thisWork;

            // If we have a process work object we need the "paper" work
            if( m_pAwdWork )
            {
               thisWork = eventCfg.getValueAsString( AWD_PWORK );
            }
            else
            {
               thisWork = awdWork;
            }

            if( thisWork.empty() )
            {
               awdEvent = NO_WORK;
               noWork = true;
            }
            else
            {
               // Find the config for this awd work
               Configuration workCfg = m_sessionCfgMgr->retrieveConfig( thisWork );

               DString statusType = m_pSession->getSessionData( STATUS_TYPE );

               if( statusType.empty() )
               {
                  statusType = PSTATUS;
               }

               // Grab the busarea, worktype and status
               busarea = workCfg.getValueAsString( BUSINESS_AREA );
               worktype = workCfg.getValueAsString( WORK_TYPE );
               status = workCfg.getValueAsString( statusType );
            }
         }
      } // Need Business area, worktype and/or status
   }// Work will be created or updated

#ifdef ENABLE_TRACING
   DString msg = I_("AWD event is ");
   msg += awdEvent;
   AWDSESSION_MSG( I_("awdEvent()"), msg.c_str() );
#endif

   // If we're not doing "no work" - we're creating or updating work
   if( ! noWork )
   {
      if( busarea.empty() || worktype.empty() || status.empty() )
      {
         // Create a condition
         ADDCONDITIONFROMFILE( DISESSN_UNDEFINED_AWD_PARAMETER );
      }
      else
      {
         DString end = m_pSession->getSessionData( END_TIME );

         if( CREATE_WORK == awdEvent )
         {
            // Construct an BFAwdData object
            BFAwdData awdData( busarea, worktype, status );

            // Set the begin and end time
            if( ( ! begin.empty() ) && ( ! end.empty() ) )
            {
               awdData.setBeginTime( begin );
               awdData.setEndTime( end );
            }

            // Copy the data over
            preProcess( eventCfg, data, awdData );

            AWDSESSION_MSG( I_("awdEvent()"),
                            I_("About to create an AWD Transaction") );

            try
            {
               //CP20040224 Added bLocked at urging of YingBao Li.  Non-standard change to DST code
               success = m_pAwd->createAwdTransaction( awdData, bLocked );
            }
            catch( ConditionException &ce )
            {
               SETCONDITIONFROMEXCEPTION( ce )
               success = false;
            }

            // Clean up
            if( success )
            {
               // If we are to create a case on multiple, do not have
               // a case and have more than one work object, create the
               // case.
               bool bMultiple = ( ( m_caseOnMultiple && ! m_pAwdWork ) ||
                                  ( m_caseOnMultipleP && m_pAwdWork ) );

               if( bMultiple && ! m_pCase && ( 1 < ++m_workCount ) )
               {
                  BFData empty;
                  DString comment = m_pSession->getSessionData( AWD_COMMENT );
                  // Clear the comment
                  m_pSession->setSessionData( AWD_COMMENT, I_("") );
                  // Create the case
                  createAwdCase( empty );
                  // Restore the comment
                  m_pSession->setSessionData( AWD_COMMENT, comment );
               }

               postProcess( awdData, true );
               checkDisplayCsd( eventCfg, awdData );
            }
         }
         else if( UPDATE_WORK == awdEvent )
         {
            // Update work, first make sure we have work to update
            if( m_pAwdWork )
            {
               // Set the values enterd by the operator
               m_pAwdWork->setUnit( busarea );
               m_pAwdWork->setWrkt( worktype );
               m_pAwdWork->setStat( status );

               // Set the begin and end time
               if( ( ! begin.empty() ) && ( ! end.empty() ) )
               {
                  m_pAwdWork->setBeginTime( begin );
                  m_pAwdWork->setEndTime( end );
               }

               // Copy the data over
               preProcess( eventCfg, data, *m_pAwdWork );

               AWDSESSION_MSG( I_("awdEvent()"),
                               I_("About to update an AWD Transaction") );

               try
               {
                  success = m_pAwd->updateAwdObject( *m_pAwdWork );
               }
               catch( ConditionException &ce )
               {
                  SETCONDITIONFROMEXCEPTION( ce )
                  success = false;
               }

               setEventRecorded( success );
               m_processWorkUpdated = success;

               // Clean up
               if( success )
               {
                  postProcess( *m_pAwdWork );

                  // Wait until the destructor to link this work to a case
                  // If we create our own container, then this code will
                  // be un-commented.
                  //
                  // // If we have a case, and the work is not yet related
                  // if ( m_pCase && ( ! m_hasCaseForParent ) )
                  // {
                  //    // Relate the work to the case
                  //    m_pAwd->createRelationship( m_pCase,
                  //                               m_pAwdWork->getKey() );
                  //    m_hasCaseForParent = true;
                  // }
               }
            }
         }
      }
   }

   // If we are propagating don't clear out all the values
   if( propagating )
   {
      m_lastEventPropagated = true;

      if( ! noWork )
      {
         // We are propagating, make sure the next object is created
         m_pSession->setSessionData( AWD_EVENT, CREATE_WORK );
      }

      // Clear out the Propagate tag and the begin time
      m_pSession->setSessionData( AWD_PROPAGATE, I_("") );
      m_pSession->setSessionData( BEGIN_TIME, I_("") );

      // Hold the new begin time
      DString newBeginTime = m_pSession->getSessionData( NEW_BEGIN_TIME );

      if( ! newBeginTime.empty() )
      {
         m_pSession->setSessionData( HOLD_NEW_BEGIN_TIME, newBeginTime );
         m_pSession->setSessionData( NEW_BEGIN_TIME, I_("") );
      }
   }
   else
   {
      m_lastEventPropagated = false;

      // Clear these data items
      m_pSession->setSessionData( AWD_EVENT, I_("") );
      m_pSession->setSessionData( AWD_COMMENT, I_("") );
      m_pSession->setSessionData( BUSINESS_AREA, I_("") );
      m_pSession->setSessionData( WORK_TYPE, I_("") );
      m_pSession->setSessionData( STATUS, I_("") );
      m_pSession->setSessionData( STATUS_TYPE, I_("") );

      DString newBeginTime = m_pSession->getSessionData( NEW_BEGIN_TIME );

      // If we have a new begin time, set it, otherwise clear out the old
      // begin time
      if( ! newBeginTime.empty() )
      {
         m_pSession->setSessionData( BEGIN_TIME, newBeginTime );
         m_pSession->setSessionData( NEW_BEGIN_TIME, I_("") );
      }
      else
      {
         m_pSession->setSessionData( BEGIN_TIME, I_("") );
      }
   }

   return(success);
}

//******************************************************************************
//
// ^PRIVATE METHOD      : BFAwdSession::relateWorkToCase
//
// ^DESCRIPTION : If we have a case, releates all other AWD work object to
//                the case.
//
// ^PARAMETERS  :
//   ^^ bool relateProcessWork - if true relates the process selected work
//
// ^RETURNS     : void
//
// ^THROWS      : none
//
//******************************************************************************
void BFAwdSession::relateWorkToCase( bool relateProcessWork )
{
   TRACE_METHOD( I_("BFAwdSession"), I_("relateWorkToCase( bool )") )

   // Make sure we have a case
   if( m_pCase )
   {
      awd_event_iterator iter = m_eventList.begin();

      // Iterate over the list realting the AWD work objects to the case
      while( iter != m_eventList.end() )
      {
         BFAwdWorkEvent &event = *iter;

         if( ! event.related )
         {
            BFAwdKey *pWork = event.key;

            try
            {
               event.related = m_pAwd->createRelationship( m_pCase, pWork );
            }
            catch( ConditionException &ce )
            {
               MAKEFRAMENOTRACE( DISESSN_CONDITION,
                                 I_("BFAwdSession::relateWorkToCase( bool )") );
               SETCONDITIONFROMEXCEPTION( ce )
            }
         }

         ++iter;
      }

      if( relateProcessWork && m_pAwdWork && ( ! m_hasCaseForParent ) )
      {
         try
         {
            m_pAwd->createRelationship( m_pCase, m_pAwdWork->getKey() );
            m_hasCaseForParent = true;
         }
         catch( ConditionException &ce )
         {
            MAKEFRAMENOTRACE( DISESSN_CONDITION,
                              I_("BFAwdSession::relateWorkToCase( bool )") );
            SETCONDITIONFROMEXCEPTION( ce )
         }
      }
   }
}

//******************************************************************************
//
// ^PRIVATE METHOD      : BFAwdSession::deleteAwdList
//
// ^DESCRIPTION : Performs a memory cleanup and unlocks all AWD work objects
//                created during this session.
//
// ^PARAMETERS  : none
//
// ^RETURNS     : void
//
// ^THROWS      : none
//
//******************************************************************************
void BFAwdSession::deleteAwdList()
{
   awd_event_reverse_iterator iter;

   // Continue while we have entries in this object's list
   while( ! m_eventList.empty() )
   {
      iter = m_eventList.rbegin();

      // Unlock the AWD work object
      BFAwdKey *pKey = ( *iter ).key;

      try
      {
         m_pAwd->lockAwdObject( pKey, false );
      }
      catch( ConditionException &ce )
      {
         MAKEFRAMENOTRACE( DISESSN_CONDITION, I_("Session::deleteAwdList()") );
         SETCONDITIONFROMEXCEPTION( ce )
      }

      // Clean up memory here
      delete ( *iter ).itemList;
      delete pKey;

      m_eventList.pop_back();
   }

   // Cleanup
   if( m_pAwdWork )
   {
      const BFAwdKey *pKey = m_pAwdWork->getKey();

      try
      {
         if( ! m_processWorkUpdated )
         {
            // If the process work has not been updated add a history item
            Configuration cfg = m_sessionCfgMgr->retrieveConfig( NOT_PROCESSED );
            DString msg = cfg.getValueAsString( MESSAGE );

            if( ! msg.empty() )
            {
               m_pAwd->addComment( pKey, msg );
            }
         }

         m_pAwd->lockAwdObject( pKey, false );
      }
      catch( ConditionException &ce )
      {
         MAKEFRAMENOTRACE( DISESSN_CONDITION, I_("Session::deleteAwdList()") );
         SETCONDITIONFROMEXCEPTION( ce )
      }

      delete m_pAwdWork;
      m_pAwdWork = NULL;
   }

   if( m_pProcessCase )
   {
      try
      {
         m_pAwd->lockAwdObject( m_pProcessCase, false );
      }
      catch( ConditionException &ce )
      {
         MAKEFRAMENOTRACE( DISESSN_CONDITION, I_("Session::deleteAwdList()") );
         SETCONDITIONFROMEXCEPTION( ce )
      }

      delete m_pProcessCase;
   }

   if( m_pCaseData )
   {
      try
      {
         m_pAwd->lockAwdObject( m_pCase, false );
      }
      catch( ConditionException &ce )
      {
         MAKEFRAMENOTRACE( DISESSN_CONDITION, I_("Session::deleteAwdList()") );
         SETCONDITIONFROMEXCEPTION( ce )
      }

      delete m_pCaseData;
   }

   if( m_pProcessSource )
   {
      // Unlock it first
      try
      {
         m_pAwd->lockAwdObject( m_pProcessSource, false );
      }
      catch( ConditionException &ce )
      {
         MAKEFRAMENOTRACE( DISESSN_CONDITION, I_("Session::deleteAwdList()") );
         SETCONDITIONFROMEXCEPTION( ce )
      }

      delete m_pProcessSource;
   }

   // START KC INFRA FIXES 15Apr2004

   // The code block to delete the obects from which CSDs are launched has
   // been moved to a point after the container as been cleared. - DT21858
//CP20040415   BFAwdDataVector::reverse_iterator csdIter;
//CP20040415
//CP20040415   while( ! m_csdList.empty() )
//CP20040415   {
//CP20040415      csdIter = m_csdList.rbegin();
//CP20040415      BFAwdData *pData = ( *csdIter ).pData;
//CP20040415      delete pData;
//CP20040415
//CP20040415      m_csdList.pop_back();
//CP20040415   }
   // END KC INFRA FIXES 15Apr2004
}

//******************************************************************************
//
// ^PRIVATE METHOD      : BFAwdSession::preProcess
//
// ^DESCRIPTION : This method will copy the data from the BFData objects to
//                the BFAwdData object while at the same time translating the
//                tags from RoadRunner tags to AWD dataname tags.  This
//                translation is identified in Session.ini and is set up
//                through the admin utility
//
// ^PARAMETERS  :
//   ^^ const Configuration &eventCfg - Event Configuration object
//   ^^ const data_ptr_map  &data - Collection of BFData objects
//   ^^ BFAwdData             &awdData - BFAwdData object
//   ^^ bool                 isCase - true if preprocessing a case
//
// ^RETURNS     : void
//
// ^THROWS      : none
//
//******************************************************************************
void BFAwdSession::preProcess( const Configuration &eventCfg,
                               const BFDataPtrMap  &data,
                               BFAwdData       &awdData,
                               bool           isCase )
{
   TRACE_METHOD( I_( "BFAwdSession "),
                 I_( "preProcess( const Configuration &, const BFDataPtrMap " )
                 I_( "&, BFAwdData & )" ) )

   DString ttag;                 // Tag from translation table
   DString tag;                  // Tag used by RoadRunner
   DString dataName;             // Awd BFData Name
   const BFData *pDefault = NULL;  // Default data opbject to search in
   bool notAlterate;             // Flag to show the label is not an alternate

#ifdef ENABLE_TRACING
   DString msg;                   // Used for trace messages
#endif

   // Grab the name of the transaltion table to use.
   DString table = eventCfg.getValueAsString( TABLE );

   if( table.empty() )
   {
      table = WORK_TABLE;
   }

#ifdef ENABLE_TRACING
   msg = I_("AWD Translation table = ");
   msg += table;
   AWDSESSION_MSG( I_("preProcess()"), msg.c_str() );
#endif

   BFDataPtrMap_Const_Iter iter = data.find( DEFAULT );

   if( iter != data.end() )
   {
      pDefault = ( *iter ).second;
   }

   // Get the translation table
   Configuration xtable = m_sessionCfgMgr->retrieveConfig( table );

   // Iterate through the translation table
   Configuration::iterator xiter = xtable.begin();

   while( xiter != xtable.end() )
   {
      // Identify our tag for the value
      ttag = ( *xiter ).getKey();
      tag = ttag;
      // Identify the clients tag (dataname) for the value
      dataName = ( *xiter ).getValueAsString();

      // If the client's tag is defined, look for the value
      if( ( ! dataName.empty() ) && ( ! tag.empty() ) )
      {
         const BFData *pDatum;
         DString label;
         DString labelName;

         //Check the tag for an overriding 'label' - only if not a case
         if( ! isCase && ( tag[0] == '(' ) )
         {
            DString::size_type position = tag.find( I_(")") );

            // if there is no closing parenths, ignore this tag
            if( position == DString::npos )
            {
               tag = I_("");
               labelName = I_("");
            }
            else
            {
               // Extract the labelName
               labelName = tag.substr( 1, position - 1 );
               // Leave only the tag
               tag.erase( 0, position + 1 );
            }

            notAlterate = false;
         }
         else
         {
            // No overriding label, use the primary
            labelName = PRIMARY;
            notAlterate = true;
         }

         // Translate the labelName into a label
         label = eventCfg.getValueAsString( labelName );

         // If we don't have a label and were're not using an alternate label,
         // use the label of the first data object
         if( label.empty() && notAlterate )
         {
            iter = data.begin();
            label = ( *iter ).first;
         }

         // Initialize our value
         DString value = I_("");

         // If we have a label, find the BFData object to search in.
         if( ! label.empty() )
         {
            iter = data.find( label );

            // if we have the BFData object
            if( iter != data.end() )
            {
               pDatum = ( *iter ).second;

               // If the tag exists, get the value
               if( pDatum->exists( tag ) )
               {
                  value = pDatum->getElementValue( tag );
                  strip( value );
               }
            }
         }

         // If the value has not been found, check session data.
         if( value.empty() && notAlterate )
         {
            value = m_pSession->getSessionData( tag );
            strip( value );
         }

         // If the value still has not been found, check the default
         if( value.empty() && pDefault && notAlterate )
         {
            // If the tag exists, get the value
            if( pDefault->exists( tag ) )
            {
               value = pDefault->getElementValue( tag );
               strip( value );
            }
         }

         // If we have a value,
         if( ! value.empty() )
         {
            // Store it with the dataname as an LOB item.
            awdData.setLobData( dataName, value );
            // Also store it in the case collector
            if( ! isCase )
            {
               m_caseCollector.setElementValue( ttag, value, true );
            }

#ifdef ENABLE_TRACING
            // Trace the translation
            msg = I_("AWD data set for ");
            msg += padRight( tag, TAG_LEN );
            msg += I_(": ");
            msg += dataName;
            msg += I_(" = ");
            msg += value;
            AWDSESSION_MSG( I_("preProcess()"), msg.c_str() );
#endif
         }
      }

      ++xiter;
   }
}

//******************************************************************************
//
// ^PRIVATE METHOD      : BFAwdSession::postProcess
//
// ^DESCRIPTION : Does cleanup work and adds a comment to the AWD Work object
//                represented by the BFAwdData object
//
// ^PARAMETERS  :
//   ^^ BFAwdData        &awdData - represents the AWD Work object
//   ^^ bool            isCase - indicates whether this is an AWD Case
//
// ^RETURNS     : void
//
// ^THROWS      : ConditionException
//
//******************************************************************************
void BFAwdSession::postProcess( BFAwdData       &awdData,
                                bool           addToList )
{
   MAKEFRAMEAUTOPROMOTE( DISESSN_CONDITION, I_("BFAwdSession::postProcess()") )

   const BFAwdKey *pKey = awdData.getKey();

   // If we have a valid key, add to the event log, and set condition
   if( pKey->isKey() )
   {
      // Add comment if we have one
      DString comment = m_pSession->getSessionData( AWD_COMMENT );

      if( ! comment.empty() )
      {
         try
         {
            AWDSESSION_MSG( I_("postProcess()"), I_("About to add an AWD Comment") );

            int size = comment.size();

            while( size > MAX_COMMENT_LEN )
            {
               DString partial = comment.substr( 0, MAX_COMMENT_LEN );
               comment.erase( 0, MAX_COMMENT_LEN );
               m_pAwd->addComment( pKey, partial );
               size = comment.size();
            }

            m_pAwd->addComment( pKey, comment );

         }
         catch( ConditionException & ce )
         {
            SETCONDITIONFROMEXCEPTION( ce )
         }
      }

      if( addToList )
      {
         // Get the configuration for the event log
         Configuration logCfg = m_sessionCfgMgr->retrieveConfig( EVENT_LOG );
         // Create the map of values to include in the event log.
         string_map *pMap = new string_map;
         ASSERT_NEW( pMap, I_("BFAwdSession::postProcess()") );

         Configuration::iterator logIter = logCfg.begin();

         // Add to the log those items specified in the event log configuration
         while( logIter != logCfg.end() )
         {
            DString value = awdData.getLobValue( ( *logIter ).getKey() );
            DString name = ( *logIter ).getValueAsString();

            if( ( ! value.empty() ) && ( ! name.empty() ) )
            {
               pMap->insert( string_map_type( name, value ) );
            }

            ++logIter;
         }

         if( ! comment.empty() )
         {
            // If the comment is defined in logcfg, add it to the map
            DString logname = logCfg.getValueAsString( AWD_COMMENT );

            if( ! logname.empty() )
            {
               pMap->insert( string_map_type( logname, comment ) );
            }
         }

         BFAwdKey *pCopy  = pKey->makeCopy();

         // Put the event together and add it to the event log
         BFAwdWorkEvent event;

         event.key = pCopy;
         event.itemList = pMap;
         event.related = false;

         // If we have a case, relate the work to it
         if( m_pCase )
         {
            // Relate the work to the case
            m_pAwd->createRelationship( m_pCase, pCopy );
            event.related = true;
         }

         if( m_pProcessSource )
         {
            m_pAwd->createRelationship( pCopy, m_pProcessSource );
         }

         // pKey and pMap will be deleted when this BFAwdSession
         // object is destroyed.
         m_eventList.push_back( event );
      }

      DString strBusarea = awdData.getUnit();
      DString strWorktype = awdData.getWrkt();
      DString strStatus = awdData.getStat();
      DString strQueue = awdData.getLobValue( QUEU );

      // Set condition indicating success
      DString idiMsg = WORK_OBJECT_DETAILS;
      idiMsg += I_("=BA::");
      idiMsg += strBusarea;
      idiMsg += I_("  WT::");
      idiMsg += strWorktype;
      idiMsg += I_("  ST::");
      idiMsg += strStatus;
      idiMsg += I_("  QU::");
      idiMsg += strQueue;

      ADDCONDITIONFROMFILEIDI( DISESSN_AWD_WORK_CREATED, idiMsg );

#ifdef ENABLE_TRACING
      DString msg = I_("An AWD Work object has been created: \"");
      msg += strBusarea;
      msg += I_("\"     \"");
      msg += strWorktype;
      msg += I_("\"    \"");
      msg += strStatus;
      msg += I_("\"     \"");
      msg += strQueue;
      msg += I_("\"");

      AWDSESSION_MSG( I_("postProcess()"), msg );
#endif

   }

   AWDSESSION_MSG( I_("postProcess()"), I_("AWD Create/Update complete") );
}

void BFAwdSession::checkDisplayCsd( const Configuration &config,
                                    BFAwdData &awdData )
{
   const BFAwdKey *pKey = awdData.getKey();

   // Make sure we have a valid key
   if( pKey->isKey() )
   {
      DStringA display = config.getValueAsString( DISPLAY_CSD );

      if( ! display.empty() && 'Y' == display[0] )
      {
         loadAwdCsd( awdData );
      }
   }
}

void BFAwdSession::setEventRecorded( bool recorded )
{
   m_eventRecorded |= recorded;
   m_pSession->setEventRecorded( recorded );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/core/bfsessn/bfawdsession.cpp-arc  $
//
//   Rev 1.6   01 Feb 2008 09:00:40   kovacsro
//IN#1103220 - increased the length of the comment to 720
//
//   Rev 1.5   Oct 22 2004 08:58:32   PURDYECH
//PET910 - .NET Conversion Fixes
//
//   Rev 1.4   Apr 20 2004 10:47:24   PURDYECH
//PTS10024114 - Integrate changes from KC to deal with Double Locking in AWD.
//
//   Rev 1.3   Feb 24 2004 09:04:06   PURDYECH
//Add bLocked flag.  Non-standard extension to DST code.
// 
//    Rev 1.2   Oct 09 2002 17:41:00   PURDYECH
// New PVCS Database
// 
//    Rev 1.1   Aug 29 2002 12:51:04   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.0   28 May 2002 12:11:12   SMITHDAV
// Initial revision.
// 
//    Rev 1.15   Aug 30 1999 16:22:50   DMUM
// The constructor for BFCPSession no longer throws
//
//    Rev 1.13   May 18 1999 08:49:58   DMUM
//
//
//    Rev 1.12   Apr 22 1999 15:51:30   DMUM
// condition message changes
//
//    Rev 1.11   Apr 16 1999 17:49:24   DMUM
// Now works for Unicode builds
//
//    Rev 1.10   Apr 09 1999 13:29:52   DMUM
// Sync up with 1.6.x
//
//    Rev 1.8.1.0   Mar 31 1999 13:16:50   DMUM
//
//
//    Rev 1.3.1.6   Feb 26 1999 08:50:08   DMUM
// Development for TA2000 NT 3.4
//
//    Rev 1.3.1.5   Feb 08 1999 15:09:18   DMUM
// Changes for TA2000 NT 3.4
//
//    Rev 1.3.1.4   Jan 20 1999 16:39:38   DMUM
// Development for TA2000 NT rel 3.4
//
//    Rev 1.3.1.3   Dec 30 1998 13:02:06   DMUM
// Fixes ticket 6053 and has enhancement for Kemper
// (which are also required for 3.4)
//
//    Rev 1.3.1.2   Oct 14 1998 10:22:28   DMUM
// Now when case creates, links to all existing work
//
//    Rev 1.3.1.1   Oct 13 1998 12:39:38   DMUM
// Added create case on multiple work objects
//
//    Rev 1.3.1.0   Sep 29 1998 14:37:20   DTWK
//
//
//    Rev 1.5   Sep 21 1998 08:50:14   DMUM
// Added Try-Catch block
//
//    Rev 1.4   Aug 27 1998 09:57:04   DMUM
// Added macros around tracing statements
//
//    Rev 1.3   Aug 14 1998 13:51:22   DMUM
// Tuning
//
//    Rev 1.2   Aug 13 1998 12:04:50   DMUM
// Tunning
//
//    Rev 1.1   Aug 03 1998 13:22:14   dmum
// Fixed problem with updaing the case if the ID Caller option
// is set
//
//    Rev 1.0   29 Jul 1998 20:33:08   DT14596
// DLMG New Archives for TA2000NTDT
//
//    Rev 1.22   Jul 23 1998 15:25:56   dmum
// Fixed the method getExportTable
//
//    Rev 1.21   Jul 23 1998 10:28:38   dmum
// Added method convertToAwdTags()
//
//    Rev 1.20   Jul 16 1998 11:48:16   dmum
// More developement
//
//    Rev 1.19   Jul 07 1998 06:24:46   dmum
// Condensed four methods into two
//
//    Rev 1.18   Jul 06 1998 15:47:06   dmum
// added new createAwdCase method override
//
//    Rev 1.17   Jun 30 1998 15:20:48   dmum
// Changed the primary data object for passing data to a case
//
//    Rev 1.16   May 26 1998 08:16:10   dmum
// Now resets  m_processWorkUpdated in setProcessWork()
//
//    Rev 1.15   May 22 1998 14:00:02   dmum
// Fixes ticket #2864.  Also fixes issue of sending data to a Case.
//
//    Rev 1.14   May 01 1998 11:37:52   DTWK
// Sync with changes for 1.12.1.0 - bad data in .ini file causes trap
//
//    Rev 1.13   Apr 28 1998 08:45:46   dmum
// Added better tracing and fixed potential problem with
// propagation and begin time
//
//    Rev 1.12   Apr 20 1998 08:13:04   dmum
// Fixed problem when propagating and not creating AWD work
//
//    Rev 1.11   Apr 15 1998 14:34:22   dmum
// Fixed problem with updating work Tracker Ticket #2166
//
//    Rev 1.10   Apr 13 1998 16:43:14   dmum
// Fixed some minor problems with passing data to AWD
//
//    Rev 1.9   Mar 27 1998 11:19:56   dmum
// Now adds a comment if process work is not updated
// Now checks a "default" data object if a value has not been found
//
//    Rev 1.8   Mar 17 1998 11:04:26   dmum
// Added new begin time logic
//
//    Rev 1.7   Mar 16 1998 15:39:38   dmum
// Fixed problems
// Tracker 2034, 2035, 2036
//
//    Rev 1.6   Feb 23 1998 11:11:28   dmum
// Fixed Bug
//
//    Rev 1.5   Feb 03 1998 15:01:26   dmum
// Fixed Bug where checking for propagate flag
//
//    Rev 1.4   Jan 30 1998 13:59:40   dmum
// - Supports propagation
// - Subsequent calls to createCase update the case
// - Fixed bug that would occur if the process work were
//   updated more than once
//
//    Rev 1.3   Jan 20 1998 07:59:38   dmum
// createAwdCase now updates the m_pProcessCase
//
//    Rev 1.2   Jan 19 1998 15:46:50   dmum
// Added logic to use a Work Selected item's parent case
// if one already exists.
//
//    Rev 1.1   Jan 13 1998 08:29:54   dmum
// Modified createAwdCase and awdEvent methods
//
//    Rev 1.0   Dec 30 1997 12:40:04   dmum
//

