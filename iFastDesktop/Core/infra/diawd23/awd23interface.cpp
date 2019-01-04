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
// ^FILE   : Awd23Interface.cpp
// ^AUTHOR : Michael McGarry
// ^DATE   : 31 Mar 97
//
// ----------------------------------------------------------
//
// ^CLASS    : Awd23Interface
//
// ^MEMBER VARIABLES :
//
//  ^^ static data_obj_map s_fieldList        - data dictionary
//  ^^ static bool         s_loggedOn         - if the operator is logged on
//  ^^ static HWND         s_hContainer       - handle to AWD conatiner
//
//  ^^ AWDApplication * m_pApp                - poiner to AWDApplication
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#define DIAWD23_DLL

#include "stdafx.h"
// This is really a fix for release builds concerning a the call to
// AwdApiInsertItemAndTakeOwnership()
#pragma optimize( "", off )

#include <fstream>
#include <io.h>

//******************************************************************************
//
// Inlcude this header before ANYTHING that uses the standard C++ library
//
//    This header includes all the SOM headers for AWD.
//
      #include "sominc.h"

//
//******************************************************************************

#ifndef EXCEPTIONHANDLER_HPP
   #include "exceptionhandler.hpp"
#endif
#ifndef AWD23INTERFACE_HPP
   #include "awd23interface.hpp"
#endif
#ifndef AWD23KEY_HPP
   #include "awd23key.hpp"
#endif
#ifndef AWD23SOURCE_HPP
   #include "awd23source.hpp"
#endif
#ifndef AWD23LOOKUPRESULT_HPP
   #include "awd23lookupresult.hpp"
#endif
#ifndef STRINGFUNCTIONS_HPP
   #include "stringfunctions.hpp"
#endif
#ifndef DATAELEMENT_HPP
   #include "dataelement.hpp"
#endif
#ifndef CONFIGMANAGER_HPP
   #include "configmanager.hpp"
#endif
#ifndef VMREQ_HPP
   #include "vmreq.hpp"
#endif
#ifndef AWDFIELD_VW_HPP
   #include <awdfield_vw.hpp>
#endif

#include <sstream>

// Awd NON-SOM includes
#ifndef AWDAPI_H
   #include "awdapi.h"
#endif
#ifndef STEALTH_H
   #include "stealth.h"
#endif
#ifndef AWDDEF_H
   #include "awddef.h"
#endif
#ifndef AWDCONT_H
   #include "awdcont.h"
#endif
#ifndef _AWDMSGID_H_
   #include "awdmsgid.h"
#endif

static const I_CHAR* s_szClass = I_("Awd23Interface");
static const I_CHAR* s_szFile = I_("awd23interface.cpp");

namespace Awd23Interface_cpp
{
   const int IDC_BTN_CLEAR            = 0x3210;

   const int MSG_LEN                  = 255;
   const int BUFF_LEN                 = 64;
   const int LOCKSTAT_LEN             = 8;
   const int SEQ_LEN                  = 3;
   const int DATA_NAME_LEN            = 4;
   const int DATA_VALUE_LEN           = 75;
   const int AMTT_LEN                 = 1;
   const int AMTV_LEN                 = 17;
   const int INDEX_01_LEN             = 10;
   const int INDEX_02_LEN             = 21;
   const int INDEX_03_LEN             = 25;
   const int INDEX_04_LEN             = 30;
   const int AWD_MIN_PSWD_LEN         = 5;
   const int TIMESTAMP_LENGTH         = 26;
   const int ACBL0076_MAX_REP         = 177;
   const int ACBL0076_REPEAT_SIZE     = 170;
   const int ACBL0076_DATAVALUE_SIZE  = 75;
   const int DEFAULT_TIMEOUT          = 90;
   const int MAX_COMMENT_LEN          = 721;


   const I_CHAR WRKT_BOTH         = 'B';
   const I_CHAR WRKT_CASE         = 'C';
   const I_CHAR WRKT_TRNS         = 'T';

   const I_CHAR chALPHA           = 'A';
   const I_CHAR chNUMTEXT         = '9';
   const I_CHAR chDATETIME        = 'S';
   const I_CHAR chDATE            = 'D';
   const I_CHAR chTIME            = 'T';
   const I_CHAR chCURRENCY        = 'C';
   const I_CHAR chNUMERIC         = 'N';
   const I_CHAR chUNKNOWN         = 'U';

   const DString strCONTAINER     = I_("AWD Container");

   const DString strAWDFIELD      = I_("AWDFIELD.VW");
   const DString strMANAGER       = I_("AwdInterface");
   const DString strOPTIONS       = I_("Options");

   const DStringA strPQMON        = "PQMON";

   // These are not const on purpose
   char *szPQMON_S                = "PQMON ";
   char *szEQUAL_TO               = "=";
   char *szLESS_THAN              = "<";
   char *szGREATER_THAN           = ">";
   char *szGREATER_THAN_OR_EQUAL  = ">=";
   char *szLESS_THAN_OR_EQUAL     = "<=";
   char *szNOT_EQUAL              = "<>";

   const char *szAPI_INSERT       = "AwdApiInsertItemAndTakeOwnership";

   const I_CHAR *ec               = I_("Awd23Interface");

   // Condition IDI tag names
   const DString AWD_EXCEPTION_MESSAGE = I_("AWD_EXCEPTION_MESSAGE");
   const DString AWD_ERROR_MESSAGE = I_("AWD_ERROR_MESSAGE");

   Environment * ev = NULL;
}

namespace AwdDataTags
{
   const DStringA strAMTT         = "AMTT";
   const DStringA strAMTV         = "AMTV";
   const DStringA strBATC         = "BATC";
   const DStringA strCRNO         = "CRNO";
   const DStringA strCRST         = "CRST";
   const DStringA strCRUS         = "CRUS";
   const DStringA strOWNE         = "OWNE";
   const DStringA strQUEU         = "QUEU";
   const DStringA strRECO         = "RECO";
   const DStringA strSTAT         = "STAT";
   const DStringA strSUSP         = "SUSP";
   const DStringA strVIFL         = "VIFL";
   const DStringA strWRKT         = "WRKT";
   const DStringA strOBJT         = "OBJT";
}

using namespace AwdDataTags;
using namespace Awd23Interface_cpp;

//******************************************************************************
//              Exported Functions
//******************************************************************************

//******************************************************************************
//
// ^FUNCTION    : fnObjectFactory
//
// ^DESCRIPTION : This function is used by processes that dynamically loads
//                this dll.  It will return an Awd23Interface object as
//                a pointer to its base class.
//
// ^PARAMETERS  : none
//
// ^RETURNS     : AwdBaseInterface * - pointer to an Awd23Interface object
//
// ^THROWS      : none - ( ConditionException may be thrown by caled methods )
//
// ^EXAMPLE     :
//
//  typedef AwdBaseInterface * ( far * OBJ_FACTORY )();
//
//  OBJ_FACTORY m_pObjectFactory;
//  HINSTANCE   m_hMod;
//
//  m_hMod = LoadLibrary( "DIAWD23" );
//  m_pObjectFactory = (OBJ_FACTORY)GetProcAddress( m_hMod, "fnObjectFactory" );
//
//  AwdBaseInterface * pInterface = m_pObjectFactory();
//
//******************************************************************************
extern "C" EXPORTWIN AwdBaseInterface * fnObjectFactory()
{
   AwdBaseInterface *pBase = new Awd23Interface;

   if ( ! pBase )
   {
      THROWFROMBASE( DIAWD23_CONDITION,
                     I_("fnObjectFactory()"),
                     BASE_ALLOC_FAIL );
   }

   return pBase;
}

//******************************************************************************
//
// ^PRIVATE METHOD      : fnIsLoggedOn
//
// ^DESCRIPTION : This function is used by processes that dynamically loads
//                this dll.  It calls the static method
//
//                Awd23Interface::isLoggedOn()
//
// ^PARAMETERS  : none
//
// ^RETURNS     : see Awd23Interface::isLoggedOn()
//
// ^THROWS      : see Awd23Interface::isLoggedOn()
//
// ^EXAMPLE     :
//
//    typedef bool ( far * IS_LOGGED_ON )();
//
//    IS_LOGGED_ON m_pIsLoggedOn;
//    HINSTANCE    m_hMod;
//
//    m_hMod = LoadLibrary( "DIAWD23" );
//    m_pIsLoggedOn = (IS_LOGGED_ON)GetProcAddress( m_hMod, "fnIsLoggedOn" );
//
//    bool loggedOn = m_pIsLoggedOn();
//
//******************************************************************************
extern "C" EXPORTWIN bool fnIsLoggedOn()
{
   bool b = Awd23Interface::isLoggedOn();
   return( b );
}

//******************************************************************************
//
// ^PRIVATE METHOD      : fnLogon
//
// ^DESCRIPTION : This function is used by processes that dynamically loads
//                this dll.  It calls the static method
//
//                Awd23Interface::logon( operatorID, password, newPassword )
//
// ^PARAMETERS  :
//   ^^ const string &operatorID  -
//   ^^ const string &password    -
//   ^^ const string &newPassword -
//
// ^RETURNS     : see Awd23Interface::logon()
//
// ^THROWS      : see Awd23Interface::logon()
//
// ^EXAMPLE     :
//
//    typedef long ( far * LOGON )( const string &operatorID,
//                                  const string &password,
//                                  const string &newPassword );
//
//    LOGON      m_pLogon;
//    HINSTANCE  m_hMod;
//
//    m_hMod = LoadLibrary( "DIAWD23" );
//    m_pLogon = (LOGON)GetProcAddress( _hMod, "fnLogon" );
//
//    long lRet = m_pLogon( "FLINSTONE", "YABADABADOO", "" );
//
//******************************************************************************
extern "C" EXPORTWIN long fnLogon( const DString &operatorID,
                                   const DString &password,
                                   const DString &newPassword )
{
   return Awd23Interface::logon( operatorID, password, newPassword );
}

//******************************************************************************
//
// ^PRIVATE METHOD      : fnLogoff
//
// ^DESCRIPTION : This function is used by processes that dynamically loads
//                this dll.  It calls the static method
//
//                Awd23Interface::fnLogoff()
//
// ^PARAMETERS  : none
//
// ^RETURNS     : see Awd23Interface::fnLogoff()
//
// ^THROWS      : see Awd23Interface::fnLogoff()
//
// ^EXAMPLE     :
//
//    typedef long ( far * LOGOFF )();
//
//    LOGOFF     m_pLogoff;
//    HINSTANCE  m_hMod;
//
//    m_hMod = LoadLibrary( "DIAWD23" );
//    m_pLogoff = (LOGOFF)GetProcAddress( _hMod, "fnLogoff" );
//
//    bool loggedOff = m_pLogoff();
//
//******************************************************************************
extern "C" EXPORTWIN long fnLogoff()
{
   return Awd23Interface::logoff();
}

//******************************************************************************
//              Public Methods
//******************************************************************************

Awd23Interface::Awd23Interface()
   : m_pApp( NULL ),
     m_pListener( NULL ),
     m_pTree( NULL ),
     m_lkupContainer( NULL )
{
   TRACE_CONSTRUCTOR( I_("Awd23Interface"), I_("Awd23Interface()") )

   try
   {
      // Get an AWDApplicatoin object
      m_pApp = new AWDApplication();

      ASSERT_NEW( m_pApp, ec, I_("Awd23Interface()") )
   }
   AWD_EXCEPTION_TO_CONDITION_EXCEPTION( ec, I_("Awd23Interface()") )

   if ( ! s_loggedOn )
   {
      s_loggedOn = isLoggedOn( m_pApp );
   }

   if ( ( NULL == s_pLists ) || s_pLists->m_fieldList.empty() )
   {
      populateFieldList( m_pApp );
   }
}

Awd23Interface::~Awd23Interface()
{
   TRACE_DESTRUCTOR( I_("Awd23Interface") )

   awd_obj_reverse_iterator iter;

   while ( ! m_objList.empty() )
   {
      iter = m_objList.rbegin();

      AWDBase *pObj = *iter;
      pObj->stopCsd( ev );
      delete pObj;

      m_objList.pop_back();
   }

   if ( m_lkupContainer && IsWindow( m_lkupContainer ) )
   {
      closeAwdContainer( m_lkupContainer );
   }

   if ( m_pListener )
   {
      m_pListener->stop( ev );
      Sleep( 100 );

      AwdKeyVector::reverse_iterator iter;

      while ( ! m_keyList.empty() )
      {
         iter = m_keyList.rbegin();

         Awd23Key *p23Key = static_cast<Awd23Key *>( *iter );
         delete p23Key;

         m_keyList.pop_back();
      }

      delete m_pListener;
      s_listenerActive = false;
   }

   delete m_pApp;
}

string_vector Awd23Interface::getBusinessAreaList()
{
   TRACE_METHOD( I_("Awd23Interface"), I_("getBusinessAreaList()") )

   string_vector list;

   // Make sure the operator is logged on to AWD
   if ( s_loggedOn )
   {
      ACBL0045       *pView   = NULL;
      ACBL0045Record *pRec    = NULL;
      unsigned long   repeats = 0;

      try
      {
         // Create a new ACBL0045
         pView = new ACBL0045();

         ASSERT_NEW( pView, ec, I_("getBusinessAreaList()") )

         // Make the view call
         pView->start( ev );
         repeats = pView->numRepeats( ev );

         // If we have 1 or more repeats, we have a list
         if ( repeats )
         {
            pRec = new ACBL0045Record();

            ASSERT_NEW( pRec, ec, I_("getBusinessAreaList()") )

            // Cycle throug the list and copy the values
            for ( unsigned long index = 0; index < repeats; ++index )
            {
               pView->getRecord( ev, pRec, index, AWDView_INDEX );
               DStringA businessArea = pRec->businessArea( ev );
               list.push_back( businessArea );
            }

            delete pRec;
         }

         delete pView;
      }
      AWD_EXCEPTION_TO_CONDITION_EXCEPTION( ec, I_("getBusinessAreaList()") )
   }

   return list;
}

string_vector Awd23Interface::getWorkTypeList( const DString & busarea )
{
   return getWorkTypeList( busarea, WRKT_BOTH );
}

string_vector Awd23Interface::getCaseWorkTypeList( const DString &busarea )
{
   return getWorkTypeList( busarea, WRKT_CASE );
}

string_vector Awd23Interface::getTransWorkTypeList( const DString &busarea )
{
   return getWorkTypeList( busarea, WRKT_TRNS );
}

string_vector Awd23Interface::getSourceTypeList( const DString &busarea )
{
   string_vector list;

   // Make sure the operator is logged on to AWD
   if ( s_loggedOn )
   {
      ACBL0048       *pView    = NULL;
      ACBL0048Record *pRec     = NULL;
      unsigned long   repeats  = 0;
      char           *pBusarea = NULL;
      DStringA        sourceType;

      // make a buffer to pass the business area
      pBusarea = new char[ busarea.length() + 1 ];

      ASSERT_NEW( pBusarea, ec, I_("getSourceTypeList()") )

      // Copy the business area
      strcpy( pBusarea, busarea.asA().c_str() );

      try
      {
         // Create a new ACBL0048
         pView = new ACBL0048( ev, pBusarea );

         ASSERT_NEW( pView, ec, I_("getSourceTypeList()") )

         // Make the view call
         pView->start( ev );
         repeats = pView->numRepeats( ev );

         // If we have 1 or more repeats, we have a list
         if ( repeats )
         {
            pRec = new ACBL0048Record();

            ASSERT_NEW( pRec, ec, I_("getSourceTypeList()") )

            for ( unsigned long index = 0; index < repeats; ++index )
            {
               // Cycle throug the list and copy the values
               pView->getRecord( ev, pRec, index, AWDView_INDEX );
               sourceType = pRec->sourceType( ev );

               list.push_back( sourceType );
            }

            delete pRec;
         }

         delete pView;
      }
      AWD_EXCEPTION_TO_CONDITION_EXCEPTION( ec, I_("getSourceTypeList()") )

      // Cleanup
      delete[] pBusarea;
   }

   return list;
}

string_vector Awd23Interface::getStatusList()
{
   TRACE_METHOD( I_("Awd23Interface"), I_("getStatusList()") )

   string_vector list;

   // Make sure the operator is logged on to AWD
   if ( s_loggedOn )
   {
      ACBL0044       *pView   = NULL;
      ACBL0044Record *pRec    = NULL;
      unsigned long   repeats = 0;

      try
      {
         // Create a new ACBL0044
         pView = new ACBL0044();

         ASSERT_NEW( pView, ec, I_("getStatusList()") )

         // Make the view call
         pView->start( ev );
         repeats = pView->numRepeats( ev );

         // If we have 1 or more repeats, we have a list
         if ( repeats )
         {
            pRec = new ACBL0044Record();

            ASSERT_NEW( pRec, ec, I_("getStatusList()") )

            for ( unsigned long index = 0; index < repeats; ++index )
            {
               // Cycle throug the list and copy the values
               pView->getRecord( ev, pRec, index, AWDView_INDEX );
               DStringA status = pRec->status( ev );
               list.push_back( status );
            }

            delete pRec;
         }

         delete pView;
      }
      AWD_EXCEPTION_TO_CONDITION_EXCEPTION( ec, I_("getStatusList()") )
   }

   return list;
}

string_vector Awd23Interface::getStatusList( const AwdKey *pKey )
{
   TRACE_METHOD( I_("Awd23Interface"), I_("getStatusList( const AwdKey * )") )

   string_vector list;

   // Make sure the operator is logged on to AWD and we have a valid key
   const Awd23Key *p23Key = confirmAndCast( pKey );

   if ( NULL != p23Key )
   {
      AWDOBJ objStruct = p23Key->getAwdObjStruct();

      ACBL0044       *pView   = NULL;
      ACBL0044Record *pRec    = NULL;
      unsigned long   repeats = 0;

      char szQueue[ QUEUE_LEN + 1 ];
      char szObjKey[ sizeof( AWDOBJKEY ) + 1 ];

      // Copy the parameters to the buffers for passing along
      memcpy( szQueue, &objStruct.awddata.awdwrkobj.queuecd, QUEUE_LEN );
      memcpy( szObjKey, &objStruct.awdobjkey, sizeof( AWDOBJKEY ) );

      // Zero terminate the buffers
      szQueue[ QUEUE_LEN ] = '\0';
      szObjKey[ sizeof( AWDOBJKEY ) ] = '\0';

      try
      {
         // Create a new ACBL0044
         pView = new ACBL0044();

         ASSERT_NEW( pView, ec, I_("getStatusList()") )

         // Pass the parameters
         pView->setQueue( ev, szQueue );
         pView->setObjectKey( ev, szObjKey );

         // Make the view call
         pView->start( ev );
         repeats = pView->numRepeats( ev );

         // If we have 1 or more repeats, we have a list
         if ( repeats )
         {
            pRec = new ACBL0044Record();

            ASSERT_NEW( pRec, ec, I_("getStatusList()") )

            for ( unsigned long index = 0; index < repeats; ++index )
            {
               // Cycle throug the list and copy the values
               pView->getRecord( ev, pRec, index, AWDView_INDEX );
               DStringA status = pRec->status( ev );
               char flag = pRec->defaultFlag( ev );

               if ( 'Y' != flag )
               {
                  // This is not the default, put it on the end.
                  list.push_back( status );
               }
               else
               {
                  // This is the default, put it on the front.
                  list.insert( list.begin(), status );
               }
            }

            delete pRec;
         }

         delete pView;
      }
      AWD_EXCEPTION_TO_CONDITION_EXCEPTION( ec, I_("getStatusList()") )
   }

   return list;
}

string_vector Awd23Interface::getStatusList(const AwdKey *pKey, const DString &strBussArea, const DString &strWkType)
{
   TRACE_METHOD( I_("Awd23Interface"), I_("getStatusList( const AwdKey *, const DString &, const DString & )") )

   DString dstrBussArea( strBussArea );
   DString dstrWkType( strWkType );

   // Make sure the operator is logged on to AWD and we have a valid key
   const Awd23Key *p23Key = confirmAndCast( pKey );

   if( p23Key == NULL || dstrBussArea.strip() == NULL_STRING || dstrWkType.strip() == NULL_STRING )
   {
      return getStatusList();
   }

   string_vector list;

   // Make sure the operator is logged on to AWD
   if ( s_loggedOn && p23Key != NULL )
   {
     AWDOBJ objStruct = p23Key->getAwdObjStruct();
      ACBL0342       *pView   = NULL;
      ACBL0342Record *pRec    = NULL;
      unsigned long   repeats = 0;

     char szQueue[ QUEUE_LEN + 1 ];
      char szObjKey[ sizeof( AWDOBJKEY ) + 1 ];

     // Copy the parameters to the buffers for passing along
     memcpy( szQueue, &objStruct.awddata.awdwrkobj.queuecd, QUEUE_LEN );
      memcpy( szObjKey, &objStruct.awdobjkey, sizeof( AWDOBJKEY ) );

      // Zero terminate the buffers
      szQueue[ QUEUE_LEN ] = '\0';
      szObjKey[ sizeof( AWDOBJKEY ) ] = '\0';

      try
      {
         // Create a new ACBL0342
         pView = new ACBL0342();
         ASSERT_NEW( pView, ec, I_("getStatusList()") )

       //set the Queue
       pView->setQueue( ev, szQueue );

       //set the key
         pView->setAwdObjectKey( ev, szObjKey );

       //set the Business Area
       char *pBusarea = NULL;
         // make a buffer to pass the business area
         pBusarea = new char[ dstrBussArea.length() + 1 ];
         ASSERT_NEW( pBusarea, ec, I_("getStatusList()") )
         // Copy the business area
         strcpy( pBusarea, dstrBussArea.asA().c_str() );
       pView->setBusinessArea( ev, pBusarea );

       //set the Work Type
       char *pWkType = NULL;
         // make a buffer to pass the work type
         pWkType = new char[ dstrWkType.length() + 1 ];
         ASSERT_NEW( pWkType, ec, I_("getStatusList()") )
         // Copy the work type
         strcpy( pWkType, dstrWkType.asA().c_str() );
       pView->setWorkType( ev, pWkType );

         // Make the view call
         pView->start( ev );
         repeats = pView->numRepeats( ev );

         // If we have 1 or more repeats, we have a list
         if ( repeats )
         {
            pRec = new ACBL0342Record();

            ASSERT_NEW( pRec, ec, I_("getStatusList()") )

            for ( unsigned long index = 0; index < repeats; ++index )
            {
               // Cycle throug the list and copy the values
               pView->getRecord( ev, pRec, index, AWDView_INDEX );
               DStringA status = pRec->status( ev );
               list.push_back( status );
            }

            delete pRec;
         }

         delete pView;
      }
      AWD_EXCEPTION_TO_CONDITION_EXCEPTION( ec, I_("getStatusList()") )
   }

   return list;
}

//////////////////////////////////////////////////////////////////////
//  The user will be responsible for deleting the AwdKey objects
bool Awd23Interface::doubleClickContainerItem( const AwdKey *pKey )
{
   MAKEFRAMEAUTOPROMOTE( DIAWD23_CONDITION,
                         I_("Awd23Interface::doubleClickContainerItem()") )


   bool success = false;

   // Make sure the container is active
   if ( confirmContainer() )
   {
      // Make sure the operator is logged on to AWD and we have a valid key
      const Awd23Key *p23Key = confirmAndCast( pKey );

      if ( NULL != p23Key )
      {
         AWDOBJKEY key = p23Key->getKey();
         short awdRet = AwdApiDoubleClickContainerItem( s_hContainer, &key, NULL );
         success = NO_ERROR == awdRet;
      }
   }
   else
   {
      ADDCONDITIONFROMFILE( DIAWD23_CONTAINER_NOT_OPEN );
   }

   return success;
}

//////////////////////////////////////////////////////////////////////
//will return the currently selected item
AwdKey * Awd23Interface::getCurrentContainerSelection()
{
   MAKEFRAMEAUTOPROMOTE( DIAWD23_CONDITION,
                         I_("Awd23Interface::getCurrentContainerSelection()") )

   Awd23Key *pKey = NULL;

   // Proceede only if we have a container
   if ( confirmContainer() )
   {
      unsigned short index = 0;
      unsigned short count = 0;
      short awdRet;

      // Get the selected item
      awdRet = AwdApiQueryItem( s_hContainer,
                                NULL,
                                NULL,
                                0,
                                AWD_GETNUM_ALL,
                                &index,
                                0 );

      if ( awdRet > 0 )
      {
         count = awdRet;
         index  = 0;

         PAWDOBJ pObjects = new AWDOBJ[ count ];

         awdRet = AwdApiQueryItem( s_hContainer,
                                   NULL,
                                   pObjects,
                                   count,
                                   AWD_SELECTEDITEM,
                                   &index,
                                   0 );

         if ( awdRet > 0 )
         {
            // Create a new key and retrieve the AWD Object
            AWDOBJ & objStruct = pObjects[ index - 1 ];
            pKey = new Awd23Key( objStruct.awdobjkey );
         }
         delete[] pObjects;
      }
   }
   else
   {
      ADDCONDITIONFROMFILE( DIAWD23_CONTAINER_NOT_OPEN );
   }

   return pKey;
}

/////////////////////////////////////////////////////////////
string_vector Awd23Interface::getQueueList( const I_CHAR type )
{
   TRACE_METHOD( I_("Awd23Interface"), I_("getQueueList( const I_CHAR type )") )

   string_vector list;

   // Make sure the operator is logged on to AWD
   if ( s_loggedOn )
   {
      ACBL0043       *pView   = NULL;
      ACBL0043Record *pRec    = NULL;
      unsigned long   repeats = 0;

      try
      {
         // Create a new ACBL0043
         ACBL0043_ACTION action;

         switch ( type )
         {
            case 'B':
               action = ACBL0043_BOTH;
               break;

            case 'P':
               action = ACBL0043_PERSONAL;
               break;

            case 'Q':
               action = ACBL0043_WORK;
               break;
         }

         pView = new ACBL0043( ev, action );

         ASSERT_NEW( pView, ec, I_("getQueueList()") )

         // Make the view call
         pView->setContinuation( ev, FALSE );
         pView->start( ev );
         repeats = pView->numRepeats( ev );

         // If we have 1 or more repeats, we have a list
         if ( repeats )
         {
            pRec = new ACBL0043Record();

            ASSERT_NEW( pRec, ec, I_("getQueueList()") )

            for ( unsigned long index = 0; index < repeats; ++index )
            {
               // Cycle throug the list and copy the values
               pView->getRecord( ev, pRec, index, AWDView_INDEX );
               DStringA queue = pRec->queue( ev );
               list.push_back( queue );
            }

            delete pRec;
         }

         delete pView;
      }
      AWD_EXCEPTION_TO_CONDITION_EXCEPTION( ec, I_("getQueueList()") )
   }

   return list;
}

data_obj_map & Awd23Interface::getAwdFieldList()
{
   return s_pLists->m_fieldList;
}

bool Awd23Interface::lookupWork( const CriteriaVector &criteria )
{
   return lookup( criteria, FieldIterator_WORK );
}

ResultVector Awd23Interface::lookupWork( const CriteriaVector &criteria,
                                               bool &more,
                                         const unsigned long max )
{
   return lookup( criteria, FieldIterator_WORK, more, max );
}

bool Awd23Interface::lookupSource( const CriteriaVector &criteria )
{
   return lookup( criteria, FieldIterator_SOURCE );
}

ResultVector Awd23Interface::lookupSource( const CriteriaVector &criteria,
                                                 bool &more,
                                           const unsigned long max )
{
   return lookup( criteria, FieldIterator_SOURCE, more, max );
}


ResultVector Awd23Interface::lookupMore( bool &more )
{
   ResultVector workList;

   AWDTree *pTree = NULL;
   unsigned long count = 0;
   unsigned long last = 0;
   more = false;

   try
   {
      if ( m_pTree )
      {
         last = m_pTree->count( ev );
         AWDBase *pObj = m_pTree->more( ev );
         count = m_pTree->count( ev ) - last;
         more = m_pTree->isMore( ev ) != FALSE;

         buildList( workList, m_pTree, count, last );
      }

      if ( ! more )
      {
         delete m_pTree;
         m_pTree = NULL;
      }
   }
   AWD_EXCEPTION_TO_CONDITION_EXCEPTION( ec, I_("lookupMoreWork()") )

   return workList;
}

bool Awd23Interface::loadCSD( AwdData &awdData )
{
   MAKEFRAME( DIAWD23_CONDITION, I_("Awd23Interface::loadCSD()") )

   bool success = false;

   // make sure the operator is logged on
   if ( s_loggedOn )
   {
      const Awd23Key * p23Key = static_cast<const Awd23Key *>( awdData.getKey() );
      bool isKey = p23Key && p23Key->isKey();

      AWD_AWDLOBARRAYSTRCT lobArray;

      if ( ! isKey )
      {
         DString str1 = awdData.getLobValue( strAMTT );

         if ( str1.empty() )
         {
            awdData.setLobData( strAMTT, I_("U") );
         }

         str1 = awdData.getLobValue( strRECO );

         if ( str1.empty() )
         {
            awdData.setLobData( strRECO, I_("T") );
         }

         awdData.setLobData( strCRNO, I_("01") );
         awdData.setLobData( strOWNE, I_("01") );
         awdData.setLobData( strSUSP, I_("N") );
         awdData.setLobData( strVIFL, I_("N") );
      }

      // Create LOB array
      if ( fillLobArray( awdData, lobArray ) )
      {
         AWDObjectFactory *pFactory;
         AWDBase *pObj;
         HWND hwnd = 0L;

         try
         {
            if ( isKey )
            {
               pObj = p23Key->getAwdBaseObj();
            }
            else
            {
               pFactory = new AWDObjectFactory();
               ASSERT_NEW( pFactory, ec, I_("loadCSD()") )

               pObj = pFactory->makeFromArray( ev, &lobArray );
               delete pFactory;
            }

            if( pObj )
            {
               bool locked = true;

               if ( isKey )
               {
                  // Check the locked status
                  switch ( objectLockStatus( pObj ) )
                  {
                     case OBJ_NOT_LOCKED:
                        // Lock the object here
                        locked = ( AWDBase_SUCCESSFULLY_LOCKED == pObj->lock( ev ) );
                        break;

                     case OBJ_LOCKED_BY_USER:
                        // We already have it locked
                        locked = true;
                        break;

                     default:
                        locked = false;
                  }

                  if ( locked )
                  {
                     pObj->updateFromArray( ev, &lobArray );
                     pObj->update( ev );
                  }
               }

               // If this is an already existing object, make sure
               // that we have it locked.  If this a new object, then
               // for all practical purposes we have it locked
               if ( locked )
               {
                  if ( m_pApp->getServiceManager()->startService( ev, AWD_SERVICE_CSD, pObj ) )
                  {
                     // We have to appeal to the service manager to get the csd's
                     // handle.
                     AWDBaseService* pSrv = 0;
                     pSrv = m_pApp->getServiceManager()->findService( ev, AWD_SERVICE_CSD, pObj );

                     if( pSrv )
                     {
                        hwnd = (HWND)pSrv->getWindowHandle( ev );
                     }

                     if ( hwnd )
                     {
                        success = TRUE;
                     }
                  }  /* end of if then */
               }  /* end of if then */

               // Only add it to our list if it not a key
               if ( ! isKey )
               {
                  m_objList.push_back( pObj );
               }

            }  /* end of if then */
         }
         AWD_EXCEPTION_TO_CONDITION_EXCEPTION( ec, I_("loadCSD()") )

         delete[] lobArray.pAwdLobData;
      }

      if ( ! success )
      {
         // Failed to create the AWD object
         ADDCONDITIONFROMFILE( DIAWD23_CREATE_AWDOBJ_FAIL );
      }
   }

   return success;
}

bool Awd23Interface::stopCSD( const AwdKey *pKey )
{
   bool success = false;

   const Awd23Key *p23Key = confirmAndCast( pKey );

   if ( NULL != p23Key )
   {
      AWDBase *pObj = p23Key->getAwdBaseObj();

      try
      {
         success = pObj->stopCsd( ev );
      }
      AWD_EXCEPTION_TO_CONDITION_EXCEPTION( ec, I_("stopCSD()") )
   }

   return success;
}


bool Awd23Interface::showAwdContainer( bool bShow )
{
   MAKEFRAMEAUTOPROMOTE( DIAWD23_CONDITION,
                         I_("Awd23Interface::showAwdContainer()") );

   bool bSuccess = false;

   try
   {
      if ( confirmContainer() )
      {
         // show or hide the awd object container
         ::ShowWindow( s_hContainer, ( bShow ? SW_SHOW : SW_HIDE ) );

         CWnd * pContainer = CWnd::FromHandle( s_hContainer );

         if ( pContainer )
         {
            pContainer->ShowOwnedPopups( bShow );
         }
         bSuccess = true;
      }
   }
   AWD_EXCEPTION_TO_CONDITION_EXCEPTION( ec, I_("showAwdContainer()") )

   return bSuccess;
}

bool Awd23Interface::showAwdServiceWindow( const AwdKey *pKey,
                                           const DString &serviceName,
                                           bool show )
{
   MAKEFRAME( DIAWD23_CONDITION,
              I_("Awd23Interface::showAwdServiceWindow()") );

   bool success = false;

   // Make sure the operator is logged on to AWD and we have a valid key
   const Awd23Key *p23Key = confirmAndCast( pKey );

   if ( NULL != p23Key )
   {
      HWND hwnd = NULL;
      AWDBaseService* pSrv = 0;
      AWDBase *pObj = p23Key->getAwdBaseObj();

      char szService[64] = "";
      strncpy( szService, serviceName.asA().c_str(), 63 );

      pSrv = m_pApp->getServiceManager()->findService( ev,
                                                       szService,
                                                       pObj );

      if( pSrv )
      {
         hwnd = (HWND)pSrv->getWindowHandle( ev );

         if ( hwnd )
         {
            ::ShowWindow( hwnd, ( show ? SW_SHOW : SW_HIDE ) );
            success = true;

            //Just in case
            CWnd * pDecendants = CWnd::FromHandle( hwnd );

            if ( pDecendants )
            {
               pDecendants->SendMessageToDescendants(
                             WM_SHOWWINDOW,
                             (WPARAM)( show ? TRUE : FALSE ),
                             0 );
            }
         }
      }
   }

   return success;
}

bool Awd23Interface::hasActiveService( const AwdKey *pKey,
                                       const DString &serviceName )
{
   MAKEFRAME( DIAWD23_CONDITION, I_("Awd23Interface::hasActiveService()") );

   bool success = false;

   // Make sure the operator is logged on to AWD and we have a valid key
   const Awd23Key *p23Key = confirmAndCast( pKey );

   if ( NULL != p23Key )
   {
      AWDBase *pObj = p23Key->getAwdBaseObj();
      AWDBaseService* pSrv = 0;

      char szService[64] = "";
      strncpy( szService, serviceName.asA().c_str(), 63 );

      pSrv = m_pApp->getServiceManager()->findService( ev,
                                                       szService,
                                                       pObj );

      if ( NULL != pSrv )
      {
         success = true;
      }
   }

   return success;
}

//////////////////////////////////////////////////////////////////////
//  The user will be responsible for deleting the AwdKeyVector
//  Note We will NOT put the parent object into the Vector
bool Awd23Interface::getAllChildren( const AwdKey* pKey,
                                     AwdKeyVector &awdKeyVector )
{
   return getChildren( pKey, awdKeyVector, true );

}

//////////////////////////////////////////////////////////////////////
//  The user will be responsible for deleting the AwdKeyVector
//  Note We will NOT put the parent object into the Vector
bool Awd23Interface::getImmediateChildren( const AwdKey* pKey,
                                           AwdKeyVector &awdKeyVector )
{
   return getChildren( pKey, awdKeyVector, false );
}

bool Awd23Interface::openAwdContainer()
{
   MAKEFRAME( DIAWD23_CONDITION,
              I_("Awd23Interface::openAwdContainer()") )

   bool success = false;

   // Make sure the Operator is logged onto AWD
   if ( s_loggedOn )
   {
      if ( confirmContainer() && s_interfaceContainer )
      {
         ADDCONDITIONFROMFILE( DIAWD23_CONTAINER_ALREADY_OPEN );
      }
      else
      {
         s_hContainer = NULL;
         HWND hDeskTop = CWnd::GetDesktopWindow()->m_hWnd;
         s_hContainer = AwdApiOpenContainer( hDeskTop, AWD_CONT_GENERIC, 0 );

         if ( NULL != s_hContainer )
         {
            // We have a container!
            s_interfaceContainer = true;
            success = true;

            // Set the Container title text
            CWnd * pContainer = CWnd::FromHandle( s_hContainer );
            pContainer->SetWindowText( strCONTAINER.c_str() );

            determineTakeOwnership();
         }
         else
         {
            ADDCONDITIONFROMFILE( DIAWD23_CONTAINER_OPEN_FAIL );
         }
      }
   }

   return success;
}

bool Awd23Interface::locateAwdContainer( const AwdKey *pKey )
{
   MAKEFRAME( DIAWD23_CONDITION,
              I_("Awd23Interface::locateAwdContainer()") )

   bool success = false;

   // Make sure the operator is logged on to AWD and we have a valid key
   const Awd23Key *p23Key = confirmAndCast( pKey );

   if ( NULL != p23Key )
   {
      if ( confirmContainer() )
      {
         if ( s_interfaceContainer )
         {
            closeAwdContainer( s_hContainer );
            s_interfaceContainer = false;
         }

         s_hContainer = NULL;
      }

      AWDOBJ objStruct = p23Key->getAwdObjStruct();
      SHORT rc;

      s_hContainer = AwdApiLocateContainer( &objStruct, &rc, 0 );

      if ( s_hContainer )
      {
         // We have a container!
         success = true;
         determineTakeOwnership();
      }
      else
      {
         ADDCONDITIONFROMFILE( DIAWD23_CONTAINER_OPEN_FAIL );
      }
   }

   return success;
}

bool Awd23Interface::isLocked( const AwdKey *pKey )
{
   MAKEFRAMEAUTOPROMOTE( DIAWD23_CONDITION,
                         I_("Awd23Interface::isLocked( const AwdKey *)") )
   bool locked = false;
   const Awd23Key * p23Key = static_cast<const Awd23Key *>( pKey );

   if ( ( NULL != p23Key ) && p23Key->isKey() )
   {
      AWDBase *pObj = p23Key->getAwdBaseObj();
      locked = pObj->isLocked( ev ) != FALSE;
   }

   return locked;
}

bool Awd23Interface::insertItemInContainer( const AwdKey *pKey, bool lock )
{
   MAKEFRAMEAUTOPROMOTE( DIAWD23_CONDITION,
          I_("Awd23Interface::insertItemInContainer( const AwdKey *, bool )") )

   bool success = false;

   // Make sure the container is active
   if ( confirmContainer() )
   {
      // Make sure the operator is logged on to AWD and we have a valid key
      const Awd23Key *p23Key = confirmAndCast( pKey );

      if ( NULL != p23Key )
      {
         short awdRet = smartInsert( p23Key, NULL, lock, false );
         success = ( NO_ERROR == awdRet );
      }
   }
   else
   {
      ADDCONDITIONFROMFILE( DIAWD23_CONTAINER_NOT_OPEN );
   }

   return success;
}

bool Awd23Interface::insertItemInContainer( const AwdKey *pKey,
                                            const AwdKey *pParent,
                                            bool lock )
{
   MAKEFRAMEAUTOPROMOTE( DIAWD23_CONDITION,
      I_("Awd23Interface::insertItemInContainer( const AwdKey *, const AwdKey *, bool )") )

   bool success = false;

   const Awd23Key * p23Key = static_cast<const Awd23Key *>( pKey );
   const Awd23Key * p23ParentKey = static_cast<const Awd23Key *>( pParent );

   if ( confirmContainer() )
   {
      if ( ( NULL != p23Key ) && ( NULL !=p23ParentKey ) &&
           p23Key->isKey() && p23ParentKey->isKey() )
      {
         short awdRet = smartInsert( p23Key, p23ParentKey, lock, false );
         success = ( NO_ERROR == awdRet );
      }
   }
   else
   {
      ADDCONDITIONFROMFILE( DIAWD23_CONTAINER_NOT_OPEN );
   }

   return success;
}

bool Awd23Interface::isItemInContainer( const AwdKey *pKey )
{
   MAKEFRAMEAUTOPROMOTE( DIAWD23_CONDITION,
                    I_("Awd23Interface::isItemInContainer( const AwdKey * )") )

   bool inContainer = false;

   // Proceede only if we have a container
   if ( confirmContainer() )
   {
      // Make sure the operator is logged on to AWD and we have a valid key
      const Awd23Key *p23Key = confirmAndCast( pKey );

      if ( NULL != p23Key )
      {
         AWDOBJKEY awdKey = p23Key->getKey();
         unsigned short index = 0;
         short awdRet;

         // Get the selected item
         awdRet = AwdApiQueryItem( s_hContainer,
                                   &awdKey,
                                   NULL,
                                   0,
                                   AWD_GETNUM_ITEM,
                                   &index,
                                   0 );

         inContainer = ( awdRet > 0 );
      }
   }
   else
   {
      ADDCONDITIONFROMFILE( DIAWD23_CONTAINER_NOT_OPEN );
   }

   return inContainer;
}

bool Awd23Interface::selectItemInContainer( const AwdKey *pKey )
{
   MAKEFRAMEAUTOPROMOTE( DIAWD23_CONDITION,
                    I_("Awd23Interface::isItemInContainer( const AwdKey * )") )

   bool success = false;

   // Proceede only if we have a container
   if ( confirmContainer() )
   {
      // Make sure the operator is logged on to AWD and we have a valid key
      const Awd23Key *p23Key = confirmAndCast( pKey );

      if ( NULL != p23Key )
      {
         AWDOBJKEY awdKey = p23Key->getKey();
         short awdRet;

         // Selected the item
         awdRet = AwdApiSelectItem( s_hContainer,
                                    &awdKey,
                                    AWD_ITEM,
                                    0,
                                    NULL );

         success = ( NO_ERROR == awdRet );
      }
   }
   else
   {
      ADDCONDITIONFROMFILE( DIAWD23_CONTAINER_NOT_OPEN );
   }

   return success;
}

bool Awd23Interface::closeAwdContainer()
{
   MAKEFRAME( DIAWD23_CONDITION,
              I_("Awd23Interface::closeAwdContainer()") )

   bool success = false;

   // Make sure the Operator is logged on and the container is active
   if ( confirmContainer() )
   {
      // Make sure this is the interface container.
      if ( s_interfaceContainer )
      {
         closeAwdContainer( s_hContainer );
         s_interfaceContainer = false;
      }

      // Whether of not it was the interface container, clear out the variables.
      s_hContainer = NULL;
      success = true;
   }
   else
   {
      ADDCONDITIONFROMFILE( DIAWD23_CONTAINER_NOT_OPEN );
   }

#ifdef ENABLE_TRACING
   TRACE_CLASS_MSG( I_("Awd23Interface"),
                    I_("closeAwdContainer()"),
                    success ? I_("closeAwdContainer() - Success!") :
                              I_("closeAwdContainer() - Failed!") )
#endif

   return success;
}

bool Awd23Interface::clearAwdContainer()
{
   MAKEFRAME( DIAWD23_CONDITION,
              I_("Awd23Interface::clearAwdContainer()") )

   bool success = false;

   // Make sure the container is active and it is the interface container
   if ( confirmContainer() && s_interfaceContainer )
   {
      // Clear the container - by posting the message a user clicked the
      // clear button. - DMUM ( suggested by Mark Clobes )
      // Post changed to Send.  Reccommended by AWD Support for TRACCSW issue.
      // - DT21858
      ::SendMessage( s_hContainer,
                     WM_COMMAND,
                     MAKEWPARAM( IDC_BTN_CLEAR, BN_CLICKED ),
                     NULL );
   }
   else
   {
      ADDCONDITIONFROMFILE( DIAWD23_CONTAINER_NOT_OPEN );
   }

   return success;
}

bool Awd23Interface::expandContainerItemDown( const AwdKey *pKey )
{
   MAKEFRAME( DIAWD23_CONDITION,
              I_("Awd23Interface::expandContainerItemDown()") )

   bool success = false;

   // Make sure the container is active
   if ( confirmContainer() )
   {
      // Make sure the operator is logged on to AWD and we have a valid key
      const Awd23Key *p23Key = confirmAndCast( pKey );

      if ( NULL != p23Key )
      {
         AWDOBJKEY objKey = p23Key->getKey();
         success = AwdApiExpandContainerItem( s_hContainer, &objKey, AWD_CHILD, 0 ) != 0;
      }
   }
   else
   {
      ADDCONDITIONFROMFILE( DIAWD23_CONTAINER_NOT_OPEN );
   }

   return success;
}


bool Awd23Interface::createAwdTransaction( AwdData &awdData, bool lock )
{
   TRACE_METHOD( I_("Awd23Interface"), I_("createAwdTransaction( AwdData &, bool  )") )

   awdData.setLobData( strRECO, I_("T") );

   return createAwdWork( awdData, lock );
}

bool Awd23Interface::createAwdCase( AwdData &awdData, bool lock )
{
   TRACE_METHOD( I_("Awd23Interface"), I_("createAwdCase( AwdData &, bool  )") )

   awdData.setLobData( strRECO, I_("C") );

   return createAwdWork( awdData, lock );
}

bool Awd23Interface::createAwdSource( const AwdData &awdData,
                                      const AwdSource::ObjectFormat format,
                                      const DString &strFile,
                                      AwdSource **ppSource,
                                      bool lock )
{
   MAKEFRAME( DIAWD23_CONDITION, I_("Awd23Interface::createAwdSource()") );

   bool created = false;
   bool fileExists = verifyFile( strFile );

   if ( NULL != ppSource )
   {
      *ppSource = NULL;
   }

   // make sure the operator is logged on and passed an objectFormat and
   // passed a valid file
   if ( s_loggedOn && fileExists && ( AwdSource::NO_FORMAT != format ) )
   {
      AWD_AWDLOBARRAYSTRCT lobArray;
      Awd23Key *pKey = NULL;

      Awd23Source *p23Source = new Awd23Source;

      ASSERT_NEW( p23Source, ec, I_("createAwdSource()") )

      AwdData &sourceData = p23Source->exposeData();
      sourceData = awdData;
      p23Source->setFormat( format );

      sourceData.setLobData( strCRNO, I_("01") );
      sourceData.setLobData( strOWNE, I_("01") );
      sourceData.setLobData( strSTAT, I_("") );
      sourceData.setLobData( strWRKT, I_("") );

      try
      {
         sourceData.setLobData( strCRST, DStringA( m_pApp->getWorkStation()->workStationID( ev ) ) );
         sourceData.setLobData( strCRUS, DStringA( m_pApp->getUser()->id( ev ) ) );
      }
      AWD_EXCEPTION_TO_CONDITION_EXCEPTION( ec, I_("createAwdSource()") )

      // Create LOB array
      if ( fillLobArray( sourceData, lobArray ) )
      {
         try
         {
            CSingleLock singleLock( &s_csListener );
            singleLock.Lock();

            // Create an AWD object
            AWDSource *pSource;

            pSource = new AWDSource( ev, &lobArray );

            ASSERT_NEW( pSource, ec, I_("createAwdSource()") )

            char szFormat[2] = " ";
            char szFile[MAX_PATH];
            int len = strFile.size();

            memcpy( szFile, strFile.asA().c_str(), len );
            szFile[len] = '\0';
            szFormat[0] = format;

            pSource->setObjectFormat( ev, szFormat );
            pSource->setSourceFile( ev, szFile );

            if( lock )
            {
               pSource->create( ev, AWDBase_LOCKED, 0 );
            }
            else
            {
               pSource->create( ev, AWDBase_UNLOCKED, 0 );
            }

            created = pSource->retrieveSecondaryFields( ev ) != FALSE;

            if ( created )
            {
               pKey = new Awd23Key( pSource );
               ASSERT_NEW( pKey, ec, I_("createAwdSource()") )

               FieldList *pFieldList =  pSource->getFieldList( ev );

               if ( pFieldList )
               {
                  AWDBaseField *pAWDBaseField = (AWDBaseField * )pFieldList->somfFirst( ev );

                  while( pAWDBaseField )
                  {
                     int seq = pAWDBaseField->sequenceNumber( ev );

                     sourceData.setLobData( DStringA( pAWDBaseField->name( ev ) ),
                                            DStringA( pAWDBaseField->asString( ev ) ),
                                            ( seq > 0 ) ? seq : 1 );

                     pAWDBaseField = (AWDBaseField *)pFieldList->somfAfter( ev, pAWDBaseField );
                  }
               }

               AWDOBJKEY objKey = pKey->getKey();
               s_lastKey = objKey;

               smartInsert( pKey, NULL, false, true );
            }

            // The Awd23Key will make a copy of the object
            // so we still need to delete it here.
            delete pSource;
         }
         AWD_EXCEPTION_TO_CONDITION_EXCEPTION( ec, I_("createAwdSource()") )

         delete[] lobArray.pAwdLobData;
      }

      // When the awdData object is destroyed, it will delete pKey
      sourceData.setKey( pKey );
      created = pKey->isKey();

      // If the source was not created or ppSource was not passed in, then
      // delete p23Source
      if ( ! ( created && ppSource ) )
      {
         delete p23Source;
         p23Source = NULL;
      }

      if ( NULL != ppSource )
      {
         *ppSource = p23Source;
      }
   }

   if ( ! created  )
   {
      DString strMsg;

      if ( ! fileExists )
      {
         strMsg = AWD_ERROR_MESSAGE;
         strMsg += I_("=The file \"");
         strMsg += strFile;
         strMsg += I_("\" does not exist.");
      }
      else if ( AwdSource::NO_FORMAT != format )
      {
         strMsg = AWD_ERROR_MESSAGE;
         strMsg += I_("=Unkown image format.");
      }

      // Failed to create the AWD object
      ADDCONDITIONFROMFILEIDI( DIAWD23_CREATE_AWDSRC_FAIL, strMsg );
   }

   return created;
}

bool Awd23Interface::createRelationship( const AwdKey *pParent,
                                         const AwdKey *pChild )
{
   TRACE_METHOD( I_("Awd23Interface"),
                 I_("createRelationship( const AwdKey *, const AwdKey * )") )

   bool related = false;

   const Awd23Key * p23Parent = static_cast<const Awd23Key *>( pParent );
   const Awd23Key * p23Child = static_cast<const Awd23Key *>( pChild );

   // Make sure the Operator is logged on and both Keys are valid
   if ( s_loggedOn && ( NULL != pParent ) && ( NULL != pChild ) &&
        p23Parent->isKey() && p23Child->isKey() )
   {
      short awdRet;

      // Extract the AWDOBJKEYs  and create the relationship
      AWDOBJKEY parent = p23Parent->getKey();
      AWDOBJKEY child  = p23Child->getKey();

      awdRet = AwdApiCreateRelationship( s_hContainer, &parent, &child, 0 );

      related = ( awdRet == 0 );

      if ( ! related )
      {
         // The two AWD objects did not relate
         MAKEFRAMENOTRACE( DIAWD23_CONDITION,
                           I_("Awd23Interface::createRelationship()") )

         DString strCode = AWD_ERROR_MESSAGE + I_("=");
         strCode.appendInt( awdRet );

         ADDCONDITIONFROMFILEIDI( DIAWD23_RELATE_FAIL, strCode );
      }
   }

   return related;
}

bool Awd23Interface::lockAwdObject( const AwdKey *pKey, bool lock )
{
   MAKEFRAMEAUTOPROMOTE( DIAWD23_CONDITION,
                  I_("Awd23Interface::lockAwdObject( const AwdKey *, bool  )") )

   bool success = false;

   // Make sure the operator is logged on to AWD and we have a valid key
   const Awd23Key *p23Key = confirmAndCast( pKey );

   if ( NULL != p23Key )
   {
      // Get the Object
      AWDBase *pObj = p23Key->getAwdBaseObj();

      try
      {
         if ( lock )
         {
            LOCKRESULT lockResult = AWDBase_INSUFFICIENT_PRIVILEGE;

            if ( ! pObj->isLocked( ev ) )
            {
               lockResult = pObj->lock( ev );

               if ( AWDBase_SUCCESSFULLY_LOCKED == lockResult )
               {
                  addToLockList( p23Key );
               }
            }

            success = ( ( AWDBase_SUCCESSFULLY_LOCKED == lockResult ) ||
                        ( AWDBase_LOCKED_BY_CURRENT_USER == lockResult ) );
         }
         else
         {
            // Only unlock it if we found it in the list.
            if ( checkLockList( p23Key ) )
            {
               success = pObj->unlock( ev ) != FALSE;

               // Lets try again to unlock if it failed
               if ( ! success )
               {
                  success = pObj->unlockRegardless( ev ) != FALSE;
               }
            }
         }
      }
      AWD_EXCEPTION_TO_CONDITION_EXCEPTION( ec, I_("lockAwdObject()") )
   }

   return success;
}

bool Awd23Interface::hasCaseForParent( const AwdKey *pKey, AwdKey **ppParent )
{
   TRACE_METHOD( I_("Awd23Interface"), I_("hasCaseForParent( const AwdKey * )") )

   bool parentIsCase = false;

   // Make sure the operator is logged on to AWD and we have a valid key
   const Awd23Key *p23Key = confirmAndCast( pKey );

   if ( NULL != p23Key )
   {
      // Get the Object
      AWDBase *pObj = p23Key->getAwdBaseObj();

      try
      {
         AWDTree* pParents = new AWDTree;

         ASSERT_NEW( pParents, ec, I_("hasCaseForParent()") )

         pParents->getParents( ev, pObj );
         AWDTreeIterator *pTreeIter = new AWDTreeIterator( ev, pParents );

         ASSERT_NEW( pTreeIter, ec, I_("hasCaseForParent()") )

         AWDBase *pParent = pTreeIter->root( ev );

         while ( pParent )
         {
            if ( pParent->isCaseObject( ev ) )
            {
               if ( NULL != ppParent )
               {
                  *ppParent = new Awd23Key( pParent );

                  ASSERT_NEW( *ppParent, ec, I_("hasCaseForParent()") )
               }

               parentIsCase = true;
               break;
            }

            pParent = pTreeIter->next( ev );
         }

         delete pTreeIter;
         delete pParents;
      }
      AWD_EXCEPTION_TO_CONDITION_EXCEPTION( ec, I_("hasCaseForParent()") )
   }

   return parentIsCase;
}

bool Awd23Interface::hasSourceForChild( const AwdKey *pKey, AwdKey **ppChild )
{
   TRACE_METHOD( I_("Awd23Interface"), I_("hasImageForChild( const AwdKey * )") )

   bool childIsSource = false;

   // Make sure the operator is logged on to AWD and we have a valid key
   const Awd23Key *p23Key = confirmAndCast( pKey );

   if ( NULL != p23Key )
   {
      // Get the Object
      AWDBase *pObj = p23Key->getAwdBaseObj();

      try
      {
         AWDTree* pChildren = new AWDTree;

         ASSERT_NEW( pChildren, ec, I_("hasImageForChild()") )

         pChildren->getChildren( ev, pObj );
         AWDTreeIterator *pTreeIter = new AWDTreeIterator( ev, pChildren );

         ASSERT_NEW( pTreeIter, ec, I_("hasImageForChild()") )

         AWDBase *pChild = pTreeIter->root( ev );

         while ( pChild )
         {
            if ( pChild->isSourceObject( ev ) )
            {
               if ( NULL != ppChild )
               {
                  *ppChild = new Awd23Key( pChild );

                  ASSERT_NEW( *ppChild, ec, I_("hasImageForChild()") )
               }

               childIsSource = true;
               break;
            }

            pChild = pTreeIter->next( ev );
         }

         delete pTreeIter;
         delete pChildren;
      }
      AWD_EXCEPTION_TO_CONDITION_EXCEPTION( ec, I_("hasImageForChild()") )
   }

   return childIsSource;
}

//////////////////////////////////////////////////////////////////////
//  Does the passed parent object have any children
bool Awd23Interface::hasChildren( const AwdKey *pKey )
{
   MAKEFRAMEAUTOPROMOTE( DIAWD23_CONDITION,
                         I_("Awd23Interface::hasChildren()") )

   bool bHasChildren = false;

   // Make sure the operator is logged on to AWD and we have a valid key
   const Awd23Key *p23Key = confirmAndCast( pKey );

   if ( NULL != p23Key )
   {
      // Get the Object
      AWDBase *pObj = p23Key->getAwdBaseObj();

      try
      {
         AWDTree* pChildren = new AWDTree;

         ASSERT_NEW( pChildren, ec, I_("hasChildren()") )

         bHasChildren = pChildren->getChildren( ev, pObj ) != FALSE;

         delete pChildren;

      }
      AWD_EXCEPTION_TO_CONDITION_EXCEPTION( ec, I_("hasChildren()") )
   }

   return bHasChildren;
}

bool Awd23Interface::addComment( const AwdKey *pKey, const DString &comment )
{
   TRACE_METHOD( I_("Awd23Interface"), I_("addComment( const AwdKey *, const DString & )") )

   bool lockedForUpdate = false;
   bool success = false;
   bool locked = false;

   // Make sure the operator is logged on to AWD and we have a valid key
   const Awd23Key *p23Key = confirmAndCast( pKey );

   if ( NULL != p23Key )
   {
      // Get the Object Struct
      AWDBase *pObj = p23Key->getAwdBaseObj();

      try
      {
         // Check the Locked status
         switch ( objectLockStatus( pObj ) )
         {
            case OBJ_NOT_LOCKED:
               // We will lock it here
               locked = ( AWDBase_SUCCESSFULLY_LOCKED == pObj->lock( ev ) );
               lockedForUpdate = true;
               break;

            case OBJ_LOCKED_BY_USER:
               // We already have it locked
               locked = true;
               break;

            default:
               locked = false;
         }

         // Proceded only if we have it locked
         if ( locked )
         {
            // Copy the comment to the buffer
            char szComment[MAX_COMMENT_LEN];
            strcpy( szComment, comment.asA().c_str() );

            // Add the comments
            success = pObj->addComments( ev, szComment, AWDBase_COMMENT_STRING ) != FALSE;
         }

         // If we locked it here, then unlock the AWD object
         if ( locked && lockedForUpdate )
         {
            pObj->unlock( ev );
         }

         if ( ! success )
         {
            MAKEFRAMENOTRACE( DIAWD23_CONDITION,
                              I_("Awd23Interface::addComment()") )
            ADDCONDITIONFROMFILE( DIAWD23_COMMENT_FAIL );
         }
      }
      AWD_EXCEPTION_TO_CONDITION_EXCEPTION( ec, I_("addComment()") )
   }

   return success;
}

bool Awd23Interface::beginListenCreateObjects()
{
   bool success = false;

   // Make sure we don't have a listener already
   if ( ! ( m_pListener || s_listenerActive ) )
   {
      try
      {
         m_pListener = new AWDListener( ev,
                                        (void *)Awd23Interface::listenerCallbackProc,
                                        (void *)this,
                                        (boolean)true );
      }
      AWD_EXCEPTION_TO_CONDITION_EXCEPTION( ec, I_("beginListenCreateObjects()") )

      ASSERT_NEW( m_pListener, ec, I_("beginListenCreateObjects()") )

      s_listenerActive = true;
      success = true;
   }

   return success;
}

AwdKeyVector Awd23Interface::endListenCreateObjects()
{
   AwdKeyVector keyList;

   if ( m_pListener )
   {
      m_pListener->stop( ev );
      Sleep( 100 );

      // Copy the list, then clean up.
      // The caller is now responsible for deleting all the AwdKeys.
      keyList = m_keyList;

      if ( ! m_keyList.empty() )
      {
         m_keyList.erase( m_keyList.begin(), m_keyList.end() );
      }

      delete m_pListener;
      m_pListener = NULL;
      s_listenerActive = false;
   }

   return keyList;
}

AwdKey * Awd23Interface::newAwdKey( const DString &createDateTime,
                                    const DString &recordCode,
                                    const DString &createNode )
{
   TRACE_METHOD( I_("Awd23Interface"),
                 I_("newAwdKey( const DString &, const DString &, const DString & )") )

   Awd23Key *pKey = NULL;

   // Make sure the values passed in make a valid key
   if ( ( Awd23Key::CRDATTIM_LEN == createDateTime.length() )
        && ( Awd23Key::RECORDCD_LEN == recordCode.length() )
        && ( Awd23Key::CRNODE_LEN == createNode.length() ) )
   {
      AWDOBJKEY objKey;

      // Copy the parameters
      memcpy( &objKey.crdattim, createDateTime.asA().c_str(), Awd23Key::CRDATTIM_LEN );
      memcpy( &objKey.recordcd, recordCode.asA().c_str(), Awd23Key::RECORDCD_LEN );
      memcpy( &objKey.crnode, createNode.asA().c_str(), Awd23Key::CRNODE_LEN );

      pKey = new Awd23Key( objKey );
   }
   else
   {
      pKey = new Awd23Key;
   }

   ASSERT_NEW( pKey, ec, I_("newAwdKey()") )

   return pKey;
}

bool Awd23Interface::retrieveData( const AwdKey *pKey, AwdData &awdData )
{
   TRACE_METHOD( I_("Awd23Interface"), I_("retrieveData( const AwdKey *, AwdData & )") )

   return retrieveData( pKey, awdData, true );
}


////////////////////////////////////////////////////////////////////////////
//  Do the same as the retrieve data, but dont get secondary fields
//  It would result in a view call (and we don't want that)
bool Awd23Interface::retrieveDataLite( const AwdKey *pKey, AwdData &awdData )
{
   TRACE_METHOD( I_("Awd23Interface"),
                 I_("retrieveDataLite( const AwdKey *, AwdData & )") )

   return retrieveData( pKey, awdData, false );

}

bool Awd23Interface::retrieveSource( const AwdKey *pKey, AwdSource **ppSource )
{
   TRACE_METHOD( I_("Awd23Interface"),
                 I_("retrieveSource( const AwdKey *, AwdSource ** )") )

   bool success = false;

   if ( NULL != ppSource )
   {
      *ppSource = NULL;
   }

   // Make sure the operator is logged on to AWD and we have a valid key
   const Awd23Key *p23Key = confirmAndCast( pKey );

   if ( NULL != p23Key )
   {
      try
      {
         Awd23Source *p23Source = NULL;
         Awd23Key *pSourceKey = new Awd23Key( p23Key );

         AWDBase *pObj = pSourceKey->getAwdBaseObj();

         if ( pObj->isSourceObject( ev ) )
         {
            AWDSource *pSource = static_cast<AWDSource *>( pObj );
            p23Source = new Awd23Source;

            ASSERT_NEW( p23Source, ec, I_("retrieveSource()") )

            AwdData &sourceData = p23Source->exposeData();
            sourceData.setKey( pSourceKey );

            // Retrieve the object
            pObj->retrieveSecondaryFields( ev );
            FieldList *pFieldList = pObj->getFieldList( ev );

            if ( pFieldList )
            {
               AWDBaseField *pAWDBaseField = (AWDBaseField * )pFieldList->somfFirst( ev );

               while( pAWDBaseField )
               {
                  int seq = pAWDBaseField->sequenceNumber( ev );

                  sourceData.setLobData( DStringA( pAWDBaseField->name( ev ) ),
                                         DStringA( pAWDBaseField->asString( ev ) ),
                                         ( seq > 0 ) ? seq : 1 );

                  pAWDBaseField = (AWDBaseField *)pFieldList->somfAfter( ev, pAWDBaseField );
               }
            }

            p23Source->establishFormat();
            success = true;
         }
         else
         {
            delete pSourceKey;
         }

         if ( NULL != ppSource )
         {
            *ppSource = p23Source;
         }
      }
      AWD_EXCEPTION_TO_CONDITION_EXCEPTION( ec, I_("retrieveData()") )
   }

   return success;
}

bool Awd23Interface::startService( const AwdKey *pKey,
                                   const DString &strServiceName )
{
   MAKEFRAMEAUTOPROMOTE( DIAWD23_CONDITION,
                       I_("Awd23Interface::startService( AwdData &, string )") )

   bool success = false;

   const Awd23Key *p23Key = static_cast<const Awd23Key *>( pKey );

   if ( ( NULL != p23Key ) && p23Key->isKey() )
   {
      try
      {
         AWDBase *pObj = p23Key->getAwdBaseObj();
         bool locked = false;

         // Check the locked status
         switch ( objectLockStatus( pObj ) )
         {
            case OBJ_NOT_LOCKED:
               // Lock the object here
               locked = ( AWDBase_SUCCESSFULLY_LOCKED == pObj->lock( ev ) );
               break;

            case OBJ_LOCKED_BY_USER:
               // We already have it locked
               locked = true;
               break;

            default:
               locked = false;
         }

         if ( locked )
         {
            char szService[64] = "";
            strncpy( szService, strServiceName.asA().c_str(), 63 );
            success =  m_pApp->getServiceManager()->startService( ev, szService, pObj ) != FALSE;
         }
      }
      AWD_EXCEPTION_TO_CONDITION_EXCEPTION( ec, I_("startService()") )
   }

   return success;
}

bool Awd23Interface::stopService( const AwdKey *pKey,
                                  const DString &strServiceName )
{
   MAKEFRAMEAUTOPROMOTE( DIAWD23_CONDITION,
                       I_("Awd23Interface::stopService( AwdData &, string )") )

   bool success = false;

   const Awd23Key *p23Key = static_cast<const Awd23Key *>( pKey );

   if ( ( NULL != p23Key ) && p23Key->isKey() )
   {
      try
      {
         AWDBase *pObj = p23Key->getAwdBaseObj();

         char szService[64] = "";
         strncpy( szService, strServiceName.asA().c_str(), 63 );
         success =  m_pApp->getServiceManager()->stopService( ev, szService, pObj ) != FALSE;

         if ( ! success )
         {
            AWDBaseService* pSrv = 0;
            pSrv = m_pApp->getServiceManager()->findService( ev, szService, pObj );

            //ok some services don't stop this way, so lets try the other
            if( pSrv )
            {
               pSrv->stop( ev );
               success = true;
            }
         }
      }
      AWD_EXCEPTION_TO_CONDITION_EXCEPTION( ec, I_("stopService()") )
   }

   return success;
}

bool Awd23Interface::updateAwdObject( AwdData &awdData )
{
   MAKEFRAMEAUTOPROMOTE( DIAWD23_CONDITION,
                         I_("Awd23Interface::updateAwdObject( AwdData & )") )
   bool updated = false;
   bool locked = false;
   bool lockedForUpdate = false;

   // Make sure the operator is logged on to AWD and we have a valid key
   const Awd23Key *p23Key = confirmAndCast( awdData.getKey() );

   if ( NULL != p23Key )
   {
      AWD_AWDLOBARRAYSTRCT lobArray;
      awdData.setLobData( strQUEU, I_("") );

      try
      {
         AWDBase *pObj = p23Key->getAwdBaseObj();

         DString beginTime = awdData.getBeginTime();
         DString endTime = awdData.getEndTime();

         if ( ( ! beginTime.empty() ) && ( ! endTime.empty() ) )
         {
            char szBegin[ AwdData::DATETIME_LEN + 1 ];
            char szEnd[ AwdData::DATETIME_LEN + 1 ];

            strncpy( szBegin, beginTime.asA().c_str(), AwdData::DATETIME_LEN );
            strncpy( szEnd, endTime.asA().c_str(), AwdData::DATETIME_LEN );

            szBegin[ AwdData::DATETIME_LEN ] = '\0';
            szEnd[ AwdData::DATETIME_LEN ] = '\0';

            // must be 0 or AWDOBJ uses it instead
            pObj->setElapsedTime( ev, 0 );
            //CCYY-MM-DD-HH.MM.SS.FFFFFF
            pObj->setBeginTimeFromTimestamp( ev, szBegin );
            pObj->setEndTimeFromTimestamp( ev, szEnd );
         }

         // Check the locked status
         switch ( objectLockStatus( pObj ) )
         {
            case OBJ_NOT_LOCKED:
               // Lock the object here
               locked = ( AWDBase_SUCCESSFULLY_LOCKED == pObj->lock( ev ) );
               lockedForUpdate = true;
               break;

            case OBJ_LOCKED_BY_USER:
               // We already have it locked
               locked = true;
               break;

            default:
               locked = false;
         }

         // If we have the object locked Create LOB array
         if ( locked && fillLobArray( awdData, lobArray ) )
         {
            // Update object
            pObj->updateFromArray( ev, &lobArray );
            updated = pObj->update( ev ) != FALSE;

            if ( updated )
            {
               // Retrieve the object
               pObj->retrieveSecondaryFields( ev );
               FieldList *pFieldList = pObj->getFieldList( ev );

               if ( pFieldList )
               {
                  AWDBaseField *pAWDBaseField = (AWDBaseField * )pFieldList->somfFirst( ev );

                  while( pAWDBaseField )
                  {
                     int seq = pAWDBaseField->sequenceNumber( ev );

                     awdData.setLobData( DStringA( pAWDBaseField->name( ev ) ),
                                         DStringA( pAWDBaseField->asString( ev ) ),
                                         ( seq > 0 ) ? seq : 1 );

                     pAWDBaseField = (AWDBaseField *)pFieldList->somfAfter( ev, pAWDBaseField );
                  }
               }
            }
            else
            {
               ADDCONDITIONFROMFILE( DIAWD23_UPDATE_AWDOBJ_FAIL );
            }

            // Clean up
            delete[] lobArray.pAwdLobData;
         }

         // If we locked the object here, unlock it.
         if ( locked && lockedForUpdate )
         {
            pObj->unlock( ev );
         }
      }
      AWD_EXCEPTION_TO_CONDITION_EXCEPTION( ec, I_("updateAwdObject()") )
   }

   return updated;
}

bool Awd23Interface::getAwdWork( AwdData &awdData )
{
   MAKEFRAMEAUTOPROMOTE( DIAWD23_CONDITION,
                         I_("Awd23Interface::getAwdWork( AwdData & )") )

   bool success = false;

   // Make sure the Operator is logged onto AWD
   if ( s_loggedOn )
   {
      // Proceede only if we have a container
      if ( confirmContainer() )
      {
         unsigned short index = 0;
         unsigned short count = 0;
         short awdRet;

         // Tell the container to get the work for us
         ::SendMessage( s_hContainer, UM_AWD_CONT_GETWORK, 0, 0 );

         // Get the selected item
         awdRet = AwdApiQueryItem( s_hContainer,
                                   NULL,
                                   NULL,
                                   0,
                                   AWD_GETNUM_ALL,
                                   &index,
                                   0 );

         if ( awdRet > 0 )
         {
            count = awdRet;
            index  = 0;

            PAWDOBJ pObjects = new AWDOBJ[ count ];

            awdRet = AwdApiQueryItem( s_hContainer,
                                      NULL,
                                      pObjects,
                                      count,
                                      AWD_SELECTEDITEM,
                                      &index,
                                      0 );

            if ( awdRet > 0 )
            {
               // Create a new key and retrieve the AWD Object
               AWDOBJ & objStruct = pObjects[ index - 1 ];
               Awd23Key * pKey = new Awd23Key( objStruct.awdobjkey );
               success = retrieveData( pKey, awdData );
               delete pKey;
            }
            else
            {
               // Something is wrong
            }

            delete[] pObjects;
         }
         else
         {
            // Something is wrong
         }
      }
      else
      {
         ADDCONDITIONFROMFILE( DIAWD23_CONTAINER_NOT_OPEN );
      }
   }

   // If we were not sucecssfull, the AwdData object should still have a key
   if ( ! success )
   {
      Awd23Key * pKey = new Awd23Key;
      awdData.setKey( pKey );
   }

   return success;
}

//////////////////////////////////////////////////////////////////////
//  The user will be responsible for deleting the AwdKey objects
bool Awd23Interface::getAwdWorkObjects( AwdKeyVector &awdKeyVector )
{
   MAKEFRAMEAUTOPROMOTE( DIAWD23_CONDITION,
                      I_("Awd23Interface::getAWDWorkObjects( &awdKeyVector )") )

   bool bWeFoundObjects = false;

   // Make sure the Operator is logged onto AWD
   // and they have a container up
   // and the vector is initially clear
   if ( ! ( confirmContainer() && awdKeyVector.empty() ) )
   {
      return bWeFoundObjects;
   }

   unsigned short index = 0;
   unsigned short count = 0;
   short awdRet;

   // Are there any items in the container
   awdRet = AwdApiQueryItem( s_hContainer,
                             NULL,
                             NULL,
                             0,
                             AWD_GETNUM_ALL,
                             &index,
                             0 );

   if ( 0 >= awdRet )
   {
      // If there are no objects in the container lets get out
      return bWeFoundObjects;
   }

   // This will get the item at the top of the container
   PAWDOBJ pParentObject = new AWDOBJ;
   index  = 0;

   awdRet = AwdApiQueryItem( s_hContainer,
                             NULL,
                             pParentObject,
                             1,
                             AWD_ITEM,
                             &index,
                             0 );

   if ( ( 0 < awdRet ) &&
        ( ( 'T' == pParentObject->awdobjkey.recordcd ) ||
          ( 'C' == pParentObject->awdobjkey.recordcd ) ) )
   {
      count = AwdApiQueryItem( s_hContainer,
                               &pParentObject->awdobjkey,
                               NULL,
                               0,
                               AWD_GETNUM_SIBLINGS,
                               &index,
                               0 );

      // SIBLING SEARCH LOGIC FIRST
      // siblings search will return all siblings
      // including ourselves (the parent object)
      if ( 0 < count )
      {
         // we do have siblings
         index = 0;
         PAWDOBJ pObjects = new AWDOBJ[ count ];

         awdRet = AwdApiQueryItem( s_hContainer,
                                   &pParentObject->awdobjkey,
                                   pObjects,
                                   count,
                                   AWD_ALLSIBLINGS,
                                   &index,
                                   0 );

         if ( 0 < awdRet )
         {
            // we got the siblings
            for ( int i = 0; i < count; i++ )
            {
               AWDOBJ &objStruct = pObjects[ i ];

               // Filter out source objects and store work obj's
               if ( ( 'T' == objStruct.awdobjkey.recordcd ) ||
                    ( 'C' == objStruct.awdobjkey.recordcd ) )
               {
                  Awd23Key *pKey = new Awd23Key( objStruct.awdobjkey );
                  awdKeyVector.push_back( pKey );
                  bWeFoundObjects = true;
               }

               if ( 'C' == objStruct.awdobjkey.recordcd )
               {
                  // lets see if the case has children ???
                  unsigned short childCount = 0;
                  index = 0;

                  childCount = AwdApiQueryItem( s_hContainer,
                                                &objStruct.awdobjkey,
                                                NULL,
                                                0,
                                                AWD_GETNUM_CHILDREN,
                                                &index,
                                                0 );

                  if ( 0 < childCount )
                  {
                     index = 0;
                     PAWDOBJ pChildObjects = new AWDOBJ[ childCount ];

                     awdRet = AwdApiQueryItem( s_hContainer,
                                               &objStruct.awdobjkey,
                                               pChildObjects,
                                               childCount,
                                               AWD_ALLCHILDREN,
                                               &index,
                                               0 );
                     if ( 0 < awdRet )
                     {
                        for ( int iCnt = 0; iCnt < childCount; ++iCnt )
                        {
                           AWDOBJ & objKid = pChildObjects[ iCnt ];

                           // Filter out source objects
                           if ( 'T' == objKid.awdobjkey.recordcd )
                           {
                              Awd23Key *pKey = new Awd23Key( objKid.awdobjkey );
                              awdKeyVector.push_back( pKey );
                           }
                        }
                     }

                     delete[] pChildObjects;
                  }
               }
            }
         }

         delete[] pObjects;
      }
   }

   delete pParentObject;
   return bWeFoundObjects;
}

DString Awd23Interface::getQueue( const AwdKey *pKey )
{
   TRACE_METHOD( I_("Awd23Interface"), I_("getQueue( const AwdKey * )") )

   DString queue( I_("__NO_Q__") );

   // Make sure the operator is logged on to AWD and we have a valid key
   const Awd23Key *p23Key = confirmAndCast( pKey );

   if ( NULL != p23Key )
   {
      // Get the Object Struct
      AWDOBJ objStruct = p23Key->getAwdObjStruct();
      queue = DStringA( objStruct.awddata.awdwrkobj.queuecd, QUEUE_LEN );
   }

   return queue;
}

bool Awd23Interface::setQueue( const AwdKey *pKey, const DString &queue )
{
   TRACE_METHOD( I_("Awd23Interface"), I_("setQueue( const AwdKey *, const DString & )") )

   bool success = false;

   // Make sure the operator is logged on to AWD and we have a valid key
   const Awd23Key *p23Key = confirmAndCast( pKey );

   if ( NULL != p23Key )
   {
      char szQueue[5];
      strcpy( szQueue, queue.asA().c_str() );

      AWDBase *pObj = p23Key->getAwdBaseObj();
      pObj->setFieldFromString( ev, "QUEU", 1, szQueue );

      success = pObj->update( ev ) != FALSE;
   }

   return success;
}

DString Awd23Interface::getOperatorID()
{
   TRACE_METHOD( I_("Awd23Interface"), I_("getOperatorID()") )

   DString opId( I_("_NO_ID_") );

   // Make sure the operator is logged on
   if ( s_loggedOn )
   {
      try
      {
         // Get the ID
         opId = m_pApp->getUser()->id( ev );
      }
      AWD_EXCEPTION_TO_CONDITION_EXCEPTION( ec, I_("getOperatorID()") )
   }

   return opId;
}

unsigned long Awd23Interface::getCountry()
{
   TRACE_METHOD( I_("Awd23Interface"), I_("getCountry()") )

   unsigned long country;

   // Make sure the operator is logged on
   if ( s_loggedOn )
   {
      try
      {
         // Get the ID
         country = m_pApp->getUser()->country( ev );
      }
      AWD_EXCEPTION_TO_CONDITION_EXCEPTION( ec, I_("getCountry()") )
   }

   return country;
}

DString Awd23Interface::getWorkstationID()
{
   TRACE_METHOD( I_("Awd23Interface"), I_("getWorkstationID()") )

   DString wsId( I_("_NO_ID_") );

   // Make sure the operator is logged on
   if ( s_loggedOn )
   {
      try
      {
         // Get the ID
         wsId = m_pApp->getWorkStation()->workStationID( ev );
      }
      AWD_EXCEPTION_TO_CONDITION_EXCEPTION( ec, I_("getWorkstationID()") )
   }

   return wsId;
}

DString Awd23Interface::getServerDateTime()
{
   TRACE_METHOD( I_("Awd23Interface"), I_("getServerDateTime()") )

   DString timeDateStamp = I_("");

   // Make sure the operator is logged on
   if ( s_loggedOn )
   {
      try
      {
         // Get the time date
         char  serverDT[27] = "";
         m_pApp->getWorkStation()->serverDateTime( ev, serverDT );
         timeDateStamp = DStringA( serverDT );
      }
      AWD_EXCEPTION_TO_CONDITION_EXCEPTION( ec, I_("getServerDateTime()") )
   }

   return timeDateStamp;
}

string_vector Awd23Interface::getSuspendCodeList()
{
   MAKEFRAMEAUTOPROMOTE( DIAWD23_CONDITION,
                         I_("Awd23Interface::getSuspendCodeList()") );

   string_vector list;

   // Build view request string
   DStringA sRequest( "VIEW" );
   sRequest += "ACBL0076";             //Viewname
   sRequest += "XXXXXXXX";             //Userid (will use blank values)
   sRequest += "000";                  //systemID
   sRequest += "001";                  //Country code
   sRequest += "GETLISTALL          "; //Process Code length 20
   sRequest += "N";                    //Continue from last view call code
   sRequest += "SUSC";                 //Dataname SUSC for suspend codes
   sRequest.upperCase();

   try
   {
      // Make a real view call
      VMRequest vmRequest( DEFAULT_TIMEOUT );

      do
      {
         //If the send is crap, drop out of loop
         if ( ! vmRequest.send( "ACBL0076", sRequest.c_str() ) )
         {
            break;
         }

         //If we got a condition codde from the view call, drop out of loop
         if ( vmRequest.getTA2000SpecificData() > NO_CONDITION )
         {
            break;
         }

         unsigned short viewRC = vmRequest.getViewReturnCode();
         if ( viewRC >= 900 && viewRC < 1000 )
         {
            break;
         }

         // Extract view buffer from VMRequest
         unsigned long ulNumRepeats = vmRequest.getNumRepeatRec();
         unsigned long ulBuffSize = vmRequest.getVarLenBufSize();

         // Ok, we received no repeats so lets leave
         if ( ulNumRepeats == 0 )
         {
            break;
         }

         unsigned char * pRptBuff = new unsigned char[ ulBuffSize + 1 ];
         memset( pRptBuff, 0, ulBuffSize + 1 );

         if ( ! vmRequest.getVarData( pRptBuff, ulBuffSize ) )
         {
            break;
         }

         // Spin through the repeat records and load them into the string_vector
         for( unsigned long cnt = 0; cnt < ulNumRepeats; cnt++ )
         {
            // pointer to the current variable length record
            const char * pVerRec =
               (const char *)&pRptBuff[ACBL0076_REPEAT_SIZE * cnt];

            DString strStatCd( A_STRING( pVerRec, ACBL0076_DATAVALUE_SIZE ) );
            strStatCd.strip();

            if ( ! strStatCd.empty() )
            {
               list.push_back( strStatCd );   // Add the value to the list
            }
         }

         delete [] pRptBuff;

         // If we don't return the max number of repeats, then we
         // don't need to call the view again, and we can exit
         if( ulNumRepeats < ACBL0076_MAX_REP )
         {
            break;
         }

      }
      while ( false );

   }
   AWD_EXCEPTION_TO_CONDITION_EXCEPTION( ec, I_("getSuspendCodeList()") )

   return list;
}



bool Awd23Interface::suspendWorkObject( const AwdKey *pKey,
                                        const DString &activateDateTime,
                                        const DString &suspendCode )
{
   TRACE_METHOD( I_("Awd23Interface"), I_("suspendWorkObject()") );

   bool suspended = false;

   // Make sure the operator is logged on to AWD and we have a valid key
   const Awd23Key *p23Key = confirmAndCast( pKey );

   if ( ( NULL != p23Key ) && ( TIMESTAMP_LENGTH == activateDateTime.length() ) )
   {
      AWDBase *pBase = p23Key->getAwdBaseObj();
      AWDSuspendAid* pAid = NULL;

      // I will only suspend a case or work object
      if ( pBase->isTransactionObject( ev ) || pBase->isCaseObject( ev ) )
      {
         AWDWork *pAwdWork = static_cast<AWDWork *>( pBase );

         try
         {
            pAid = new AWDSuspendAid( ev, pAwdWork );

            //  Did we get a suspend aid object?
            if ( pAid )
            {
               //if the activation date/time and the
               //suspend code are set correctly
               if ( pAid->setActivateDateTime( ev,
                       const_cast<char *>( activateDateTime.asA().c_str() ) ) &&
                    ( suspendCode.empty() ||  //there is no code
                      pAid->setSuspendCode( ev,
                           const_cast<char *>( suspendCode.asA().c_str() ) ) ) )

               {
                  //if we are resuspending
                  if (  pAwdWork->isSuspended( ev ) )
                  {
                     if ( pAid->update( ev ) )
                     {
                        suspended = true;// We suspended correctly
                     }
                  }
                  else if ( pAid->suspend( ev ) )
                  {
                     suspended = true;// We suspended correctly
                  }
               }
               delete pAid;
            }
         }
         AWD_EXCEPTION_TO_CONDITION_EXCEPTION( ec, I_("suspendWorkObject()") )
      }
   }

   return suspended;
}

bool Awd23Interface::unSuspendWorkObject(const AwdKey *pKey )
{
   TRACE_METHOD( I_("Awd23Interface"), I_("unSuspendWorkObject()") );

   bool unSuspended = false;

   const Awd23Key *p23Key = confirmAndCast( pKey );

   if ( NULL != p23Key )
   {
      AWDBase *pBase = p23Key->getAwdBaseObj();
      AWDSuspendAid *pAid = NULL;

      //The only objects I unsuspend are work and case objects!
      if ( pBase->isTransactionObject( ev ) || pBase->isCaseObject( ev ) )
      {
         AWDWork *pAwdWork = static_cast<AWDWork *>( pBase );

         try
         {
            pAid = new AWDSuspendAid( ev, pAwdWork );

            //  Did we get a suspend aid object?
            if ( pAid )
            {
               //if we are suspended
               if ( pAwdWork->isSuspended( ev ) )
               {
                  if ( pAid->unsuspend( ev ) )
                  {
                     //We unSuspended
                     unSuspended = true;
                  }
               }

               delete pAid;
            }
         }
         AWD_EXCEPTION_TO_CONDITION_EXCEPTION( ec, I_("unSuspendWorkObject()") )
      }
   }

   return unSuspended;
}


bool Awd23Interface::isLoggedOn()
{
   MAKEFRAME( DIAWD23_CONDITION, I_("Awd23Interface::isLoggedOn()") )

   AWDApplication* pApp = NULL;

   try
   {
      pApp = new AWDApplication();

      ASSERT_NEW( pApp, ec, I_("isLoggedOn()") )

      s_loggedOn = isLoggedOn( pApp );

      delete pApp;

   }
   AWD_EXCEPTION_TO_CONDITION_EXCEPTION( ec, I_("isLoggedOn()") )

   return s_loggedOn;
}

bool Awd23Interface::isLoggedOn( AWDApplication *pApp )
{
   MAKEFRAME( DIAWD23_CONDITION,
              I_("Awd23Interface::isLoggedOn( AWDApplication * )") )

   bool loggedOn = FALSE;

   try
   {
      loggedOn = pApp->getUser()->isLoggedOn( ev ) != FALSE;
   }
   AWD_EXCEPTION_TO_CONDITION_EXCEPTION( ec, I_("isLoggedOn( AWDApplication * )") )

   return loggedOn;
}

long Awd23Interface::logon( const DString &operatorID,
                            const DString &password,
                            const DString &newPassword )
{
   MAKEFRAME( DIAWD23_CONDITION, I_("Awd23Interface::logon()") )

   AWDApplication* pApp = NULL;
   long awdRc;

   if ( ( ! newPassword.empty() ) && ( AWD_MIN_PSWD_LEN > newPassword.size() ) )
   {
      THROWFROMFILE( DIAWDI_CONDITION,
                     I_( "Awd23Interface::logon()" ),
                     DIAWDI_LOGON_INVALID_NEW_PASSWORD );
   }

   try
   {
      pApp = new AWDApplication();
      ASSERT_NEW( pApp, ec, I_("logon()") )
   }
   AWD_EXCEPTION_TO_CONDITION_EXCEPTION( ec, I_("logon()") )

   try
   {
      char szID[BUFF_LEN];
      char szPW[BUFF_LEN];
      char szNP[BUFF_LEN];

      strcpy( szID, operatorID.asA().c_str() );
      strcpy( szPW, password.asA().c_str() );
      strcpy( szNP, newPassword.asA().c_str() );

      _strupr( szID );
      _strupr( szPW );
      _strupr( szNP );

      pApp->getUser()->logon( ev, szID, szPW, szNP );
      awdRc = DIAWDI_LOGON_NO_ERROR;
      s_loggedOn = true;

   }
   catch( AWDException *pExc )
   {
      //
      // Map the return code into a condition object.
      //
      switch ( pExc->returnCode( ev ) )
      {
         case AWD_LOGON_PSWD_EXPIRED:       //SYS0105
            awdRc = DIAWDI_LOGON_PASSWORD_EXPIRED;
            break;

         case AWD_NEWPSWD_SAMEAS_OLD: //SYS0108
            awdRc = DIAWDI_LOGON_NEW_PASSWORD_SAMEAS_OLD;
            break;

         case AWD_LOGON_INVALID_OPID:       //SYS0100
            awdRc = DIAWDI_LOGON_INVALID_OPID;
            break;

         case AWD_LOGON_USER_DISABLED:      //SYS0113
            awdRc = DIAWDI_LOGON_USER_DISABLED ;
            break;

         case AWD_LOGON_INVALID_PSWD:       //SYS0101
            awdRc = DIAWDI_LOGON_INVALID_PASSWORD;
            break;

         default:            // All other errors
            awdRc = DIAWDI_LOGON_OTHER_ERROR;
      }

      s_loggedOn = false;
      delete pApp;

      DStringA msg = AWD_ERROR_MESSAGE;
      msg += "=";
      msg += pExc->message( ev );

      THROWFROMFILEIDI( DIAWDI_CONDITION,
                        I_("Awd23Interface::logon()"),
                        awdRc,
                        msg );
   }
   catch ( ConditionException &ce )
   {
      s_loggedOn = false;
      delete pApp;
      throw ce;
   }
   catch ( ... )
   {
      s_loggedOn = false;
      delete pApp;

      THROWFROMFILE( DIAWD23_CONDITION,
                     I_("Awd23Interface::logon()"),
                     DIAWD23_UNKNOWN_AWD_EXCEPTION );
   }

   try
   {
      // If logon was successfull, get the data dictionary
      if ( s_loggedOn )
      {
         pApp->getUser()->retrieveServiceDotDat( ev );

         CAWDLogon awdOperator( FALSE );
         awdOperator.DestroyMainFolderBeforeCreate();
         awdOperator.CreateMainFolder();
         awdOperator.RefreshMainFolder();

         populateFieldList( pApp );
      }
   }
   catch ( AWDException *pExc )
   {
      delete pApp;

      ConvertAwdExceptionToConditionException( pExc,
                                               ec,
                                               I_("logon()"),
                                               __FILE__,
                                               __LINE__ );
   }
   catch ( ConditionException &ce )
   {
      delete pApp;
      throw ce;
   }
   catch ( ... )
   {
      delete pApp;

      THROWFROMFILE( DIAWD23_CONDITION,
                     I_("logon()"),
                     DIAWD23_UNKNOWN_AWD_EXCEPTION );
   }

   DString strOpt = GetConfigValueAsString( strMANAGER, strOPTIONS, strPQMON );

   // If the option to monitor the personal queue is set, the start it.
   if ( ! strOpt.empty() && ( 'Y' == strOpt[0] ) )
   {
      ACBL0030Record *pRec = new ACBL0030Record;
      ACBL0030 *pView = new ACBL0030;

      try
      {
         DStringA strBuff;
         unsigned long index, count;

         pView->setSecurityPlatform( NULL, PLATFORM_WINDOWS );
         pView->setRefreshFlag( NULL, FALSE );
         pView->setContinuation( NULL,  FALSE );
         pView->setSecurityType( NULL, SECURITY_RESOURCE );
         pView->setSecurityValue( NULL, szPQMON_S );

         pView->start( ev );

         count = pView->numRepeats( ev );

         for ( index = 0; index < count; ++index )
         {
             pView->getRecord( ev, pRec, index, AWDView_INDEX );

             strBuff = pRec->resource( ev );
             stripTrailing( strBuff );

             if ( strPQMON == strBuff )
             {
                 if ( pRec->accesstype( ev ) != ACCESS_EXCLUDE )
                 {
                    strBuff = pApp->getWorkStation()->binPath( ev );
                    strBuff += "\\pqmon.exe";

                    DString strFile( strBuff );
                    DString strParams( A_STRING( pRec->parameters( ev ) ) );

                    ShellExecute( NULL,
                                  NULL,
                                  strFile.c_str(),
                                  strParams.c_str(),
                                  NULL,
                                  SW_SHOWNORMAL );
                 }

                 break;
             }
         }

      }
      catch ( AWDException *pExc )
      {
         delete pApp;
         delete pRec;
         delete pView;

         ConvertAwdExceptionToConditionException( pExc,
                                                  ec,
                                                  I_("logon()"),
                                                  __FILE__,
                                                  __LINE__ );
      }
      catch ( ConditionException &ce )
      {
         delete pApp;
         delete pRec;
         delete pView;
         throw ce;
      }
      catch ( ... )
      {
         delete pApp;
         delete pRec;
         delete pView;

         THROWFROMFILE( DIAWD23_CONDITION,
                        I_("logon()"),
                        DIAWD23_UNKNOWN_AWD_EXCEPTION );
      }

      delete pRec;
      delete pView;
   }

   delete pApp;

   return awdRc;
}

long Awd23Interface::logoff()
{
   MAKEFRAME( DIAWD23_CONDITION, I_("Awd23Interface::logoff()") )

   long loggedOff;

   if ( confirmContainer() )
   {
      if ( s_interfaceContainer )
      {
         closeAwdContainer( s_hContainer );
         s_interfaceContainer = false;
      }

      s_hContainer = NULL;
   }

   try
   {
      AWDLogoff awdOperator( FALSE );

      loggedOff = awdOperator.logoff();
   }
   AWD_EXCEPTION_TO_CONDITION_EXCEPTION( ec, I_("logoff()") )

   s_loggedOn = ! loggedOff;

   return loggedOff ? 0 : 1;
}

void Awd23Interface::deregister( void *pObj )
{
   const Awd23Statics *pList = (Awd23Statics *)pObj;

   if ( pList == s_pLists )
   {
      delete s_pLists;
      s_pLists = NULL;
   }
}

//******************************************************************************
//              Private Methods
//******************************************************************************

// static variables
// data_obj_map Awd23Interface::s_fieldList;
// Awd23Interface::group_map Awd23Interface::s_groupList;

Awd23Interface::Awd23Statics * Awd23Interface::s_pLists = NULL;

bool Awd23Interface::s_loggedOn = false;
bool Awd23Interface::s_interfaceContainer = false;
bool Awd23Interface::s_listenerActive = false;
HWND Awd23Interface::s_hContainer = NULL;

HMODULE Awd23Interface::s_hAwdApi = NULL;
Awd23Interface::API_INSERT Awd23Interface::s_pAwdApiInsertItemAndTakeOwnership = NULL;

CCriticalSection Awd23Interface::s_csListener;
AWDOBJKEY Awd23Interface::s_lastKey;

//******************************************************************************
//
// ^PRIVATE METHOD      : Awd23Interface::retrieveData
//
// ^DESCRIPTION : Private method for retrieveData, and retrieveDataLite code
//                reuse.
//
// ^PARAMETERS  :
//
// ^RETURNS     : bool
//
// ^THROWS      : none
//
//******************************************************************************
bool Awd23Interface::retrieveData( const AwdKey* pKey,
                                    AwdData &awdData,
                                    bool bGetSecondaryFields )
{
   TRACE_METHOD( I_("Awd23Interface"),
                 I_("retrieveData( const AwdKey *, AwdData &, bool )") )

   bool success = false;

   // Make sure the operator is logged on to AWD and we have a valid key
   const Awd23Key *p23Key = confirmAndCast( pKey );

   if ( NULL != p23Key )
   {
      Awd23Key *pDataKey = new Awd23Key( p23Key );
      awdData.setKey( pDataKey );

      try
      {
         AWDBase *pObj = pDataKey->getAwdBaseObj();

         // Retrieve the object
         if ( bGetSecondaryFields )
         {
            pObj->retrieveSecondaryFields( ev );
         }

         FieldList *pFieldList = pObj->getFieldList( ev );

         if ( pFieldList )
         {
            AWDBaseField *pAWDBaseField = (AWDBaseField *)pFieldList->somfFirst( ev );

            while( pAWDBaseField )
            {
               int seq = pAWDBaseField->sequenceNumber( ev );

               awdData.setLobData( DStringA( pAWDBaseField->name( ev ) ),
                                   DStringA( pAWDBaseField->asString( ev ) ),
                                   ( seq > 0 ) ? seq : 1 );

               pAWDBaseField = (AWDBaseField *)pFieldList->somfAfter( ev, pAWDBaseField );
            }
         }
      }
      AWD_EXCEPTION_TO_CONDITION_EXCEPTION( ec, I_("retrieveData()") )

      success = true;
   }

   return success;
}

bool Awd23Interface::getChildren( const AwdKey* pKey,
                                  AwdKeyVector &awdKeyVector,
                                  bool grandchildren )
{
   MAKEFRAMEAUTOPROMOTE( DIAWD23_CONDITION,
                         I_("Awd23Interface::getAllChildren()") )

   // Make sure the operator is logged on to AWD and we have a valid key
   const Awd23Key *pParentKey = confirmAndCast( pKey );

   if ( NULL != pParentKey )
   {
      AWDTree* pTree = new AWDTree;
      pTree->getChildren( ev, pParentKey->getAwdBaseObj() );

      AWDTreeIterator *pTreeIter = new AWDTreeIterator( ev, pTree );
      AWDBase *pObj = pTreeIter->root( ev );

      while ( NULL != pObj )
      {
         Awd23Key *pKey = new Awd23Key( pObj );
         awdKeyVector.push_back( pKey );

         //Expand all non source objects if grandchildren have been requested.
         if ( grandchildren && !pObj->isSourceObject( ev ) )
         {
            AWDTree* pBranch = new AWDTree;
            pBranch->getChildren( ev, pObj );
            AWDTreeIterator *pIter = new AWDTreeIterator( ev,
                                                       pBranch );
            AWDBase *pChild = pIter->root( ev );

            while ( pChild )
            {
              Awd23Key *pCKey = new Awd23Key( pChild );
              awdKeyVector.push_back( pCKey );
              pChild = pIter->next( ev );
            }

            delete pIter;
            delete pBranch;
         }

         pObj = pTreeIter->next( ev );
      }

      delete pTreeIter;
      delete pTree;
   }

   return true;
}



//******************************************************************************
//
// ^PRIVATE METHOD      : Awd23Interface::smartInsert
//
// ^DESCRIPTION : Calls the AwdApiInsertItem function.
//
// ^PARAMETERS  :
//
// ^RETURNS     : SHORT
//
// ^THROWS      : none
//
//******************************************************************************
SHORT Awd23Interface::smartInsert( const Awd23Key *pKey,
                                   const Awd23Key *pParent,
                                   bool lock,
                                   bool add )
{
   AFX_MANAGE_STATE( AfxGetStaticModuleState() );

   PAWDOBJKEY pParentKey = NULL;
   SHORT awdRet;

   if ( NULL != pParent )
   {
      pParentKey = (PAWDOBJKEY) &( pParent->getKey() );
   }

   if ( NULL != s_pAwdApiInsertItemAndTakeOwnership )
   {

      AWDOBJ obj = pKey->getAwdObjStruct();

      awdRet = s_pAwdApiInsertItemAndTakeOwnership( s_hContainer,
                                                    pParentKey,
                                                    &obj,
                                                    true,
                                                    lock,
                                                    0L );

      checkLockList( pKey );
   }
   else
   {
      AWDOBJKEY key = pKey->getKey();

      awdRet = AwdApiInsertItemKey( s_hContainer,
                                    pParentKey,
                                    &key,
                                    true,
                                    lock,
                                    0L );

      if ( add )
      {
         addToLockList( pKey );
      }
   }

   return awdRet;
}

//******************************************************************************
//
// ^PRIVATE METHOD      : Awd23Interface::buildList
//
// ^DESCRIPTION :
//
// ^PARAMETERS  :
//   ^^ AWDTree *pTree -
//   ^^ unsigned long limit -
//
// ^RETURNS     : void -
//
// ^THROWS      : ConditionException
//
//******************************************************************************
void Awd23Interface::buildList( ResultVector &resultList,
                                AWDTree *pTree,
                                unsigned long count,
                                unsigned long last )
{
   if ( pTree && count )
   {
      try
      {
         AWDOBJ objStruct;
         AWD_PAWDOBJECTSTRCT pAwdObj = (AWD_PAWDOBJECTSTRCT)&objStruct;
         unsigned long index;

         AWDTreeIterator *pTreeIter = new AWDTreeIterator( ev, pTree );
         AWDBase *pWork = pTreeIter->root( ev );

         if ( last )
         {
            for ( index = 0; index < last; ++index )
            {
               pWork = pTreeIter->next( ev );
            }
         }

         for ( index = 0; index < count; ++index )
         {
            pWork->getStructure( ev, pAwdObj );

            Awd23LookupResult work( objStruct );
            resultList.push_back( work );

            // get the next one
            pWork = pTreeIter->next( ev );
         }

         delete pTreeIter;
      }
      AWD_EXCEPTION_TO_CONDITION_EXCEPTION( ec, I_("buildList()") )
   }
}

//******************************************************************************
//
// ^PRIVATE METHOD      : Awd23Interface::lookup
//
// ^DESCRIPTION :
//
// ^PARAMETERS  :
//   ^^ const CriteriaVector &criteria -
//   ^^ unsigned long lookupType -
//
// ^RETURNS     : bool -
//
// ^THROWS      : ConditionException
//
//******************************************************************************
bool Awd23Interface::lookup( const CriteriaVector &criteria,
                             unsigned long lookupType )
{
   bool more;   // This is only used to satify parameter requirements

   if ( m_lkupContainer && IsWindow( m_lkupContainer ) )
   {
      closeAwdContainer( m_lkupContainer );
   }

   m_lkupContainer = NULL;
   AWDTree *pTree = doLookup( criteria, lookupType, more );

   try
   {
      if ( pTree )
      {
         m_lkupContainer = AWDLoadContainer( LOOKUP, pTree, NULL );

         if ( m_lkupContainer )
         {
            ShowWindow( m_lkupContainer, SW_SHOWNORMAL );
         }
      }
   }
   AWD_EXCEPTION_TO_CONDITION_EXCEPTION( ec, I_("lookup()") )

   return NULL != m_lkupContainer;
}

//******************************************************************************
//
// ^PRIVATE METHOD      : Awd23Interface::lookup
//
// ^DESCRIPTION :
//
// ^PARAMETERS  :
//   ^^ const CriteriaVector &criteria -
//   ^^ unsigned long lookupType -
//   ^^ bool &more -
//   ^^ const unsigned long max -
//
// ^RETURNS     : ResultVector -
//
// ^THROWS      : ConditionException
//
//******************************************************************************
ResultVector Awd23Interface::lookup( const CriteriaVector &criteria,
                                           unsigned long lookupType,
                                           bool &more,
                                     const unsigned long max )
{
   ResultVector resultList;
   unsigned long limit;
   unsigned long count;
   more = false;

   try
   {
      if ( m_pTree )
      {
         delete m_pTree;
         m_pTree = NULL;
      }

      AWDTree *pTree = doLookup( criteria, lookupType, more );

      if ( pTree )
      {
         count = pTree->count( ev );

         while ( more && ( count < max ) )
         {
            pTree->more( ev );
            more = pTree->isMore( ev ) != FALSE;
            count = pTree->count( ev );
         }

         limit = ( max  && ( count > max ) ? max : count );

         buildList( resultList, pTree, limit );

         // If a max value was passed in, then there is no need to worry
         // if there are any more.
         more &= ! max;

         if ( more )
         {
            m_pTree = pTree;
         }
         else
         {
            delete pTree;
         }
      }
   }
   AWD_EXCEPTION_TO_CONDITION_EXCEPTION( ec, I_("lookup()") )

   return resultList;
}

//******************************************************************************
//
// ^PRIVATE METHOD      : Awd23Interface::doLookup
//
// ^DESCRIPTION :
//
// ^PARAMETERS  :
//   ^^ const CriteriaVector &criteria -
//   ^^ unsigned long lookupType -
//   ^^ bool &more -
//
// ^RETURNS     : AWDTree * -
//
// ^THROWS      : ConditionException
//
//******************************************************************************
AWDTree *Awd23Interface::doLookup( const CriteriaVector &criteria,
                                   unsigned long lookupType,
                                   bool &more )
{
   LookupServiceAid *pLookupAid = NULL;
   LookupCriteria *pCriteria = NULL;
   OrderBy *pOrder = NULL;
   AWDData *pData = NULL;
   AWDTree *pTree = NULL;
   AWDTreeIterator *pIter = NULL;
   SOMList* pCriteriaList = NULL;
   SOMList* pOrderByList = NULL;
   AWDDictionary* pDictionary = NULL;

   ACBL0049_FIELD_TYPE fldType;

   char szField[DATA_NAME_LEN+1];
   char szValue[DATA_VALUE_LEN+1];
   char *pszComp = NULL;

   DString field, value;

   int criteriaCount = criteria.size();
   bool useSQL = true;
   bool hasOrderBy = false;
   more = false;

   if ( criteriaCount )
   {
      try
      {
         pLookupAid = new LookupServiceAid;
         pLookupAid->setLookupType( ev, lookupType );

         pCriteriaList = pLookupAid->criteriaList( ev );
         pOrderByList = pLookupAid->orderByList( ev );
         pDictionary = pLookupAid->getDictionary( ev );

         CriteriaVector::const_iterator iter = criteria.begin();

         int count = 0;

         while ( iter != criteria.end() )
         {
            const AwdLookupCriteria &item = *iter;
            field = item.getField();
            data_obj_map_iterator dataIter = s_pLists->m_fieldList.find( field );

            if ( item.isValid() && ( dataIter != s_pLists->m_fieldList.end() ) )
            {
               strcpy( szField, field.asA().c_str() );
               pData = pDictionary->get( ev, szField );
               fldType = pData->fldType( ev );

               // If this an order by item and it is an AWD type
               if ( item.isOrderBy() )
               {
                  // This if is nested so that if the item is an OrderBy
                  // but does not meet the criteria of being an AWD field,
                  // we wont accidentally execute the else statement below.
                  if ( ACBL0049_TYPE_AWD == fldType )
                  {
                     pOrder = new OrderBy( ev, pData );
                     ASSERT_NEW( pOrder, ec, I_("doLookup()") )

                     pOrderByList->somfAddLast( ev, pOrder );

                     if ( AwdLookupCriteria::DESCENDING == item.getOrder() )
                     {
                        pLookupAid->setOrder( ev, LookupServiceAid_DESCENDING );
                     }
                     else
                     {
                        pLookupAid->setOrder( ev, LookupServiceAid_ASCENDING );
                     }

                     hasOrderBy = true;
                  }
               }
               else
               {
                  value = item.getValue();
                  strcpy( szValue, value.asA().c_str() );

                  pszComp = getComparison( item.getComparison() );

                  pCriteria = new LookupCriteria( ev, pData, pszComp, szValue );
                  ASSERT_NEW( pCriteria, ec, I_("doLookup()") )

                  pCriteriaList->somfAddLast( ev, pCriteria );

                  if ( useSQL && ( ! pData->isIndexed( ev ) ) )
                  {
                     // Borrowed code.  If the field is not indexed and it is
                     // either an LOB or GROUPED field, then we cannot use SQL
                     useSQL = ( ACBL0049_TYPE_LOB != fldType )
                              && ( ACBL0049_TYPE_GROUP != fldType );
                  }

                  ++count;
               }
            }

            ++iter;
         }

         if ( count )
         {
            pLookupAid->setLookupMethod( ev, useSQL || hasOrderBy );
            pTree = pLookupAid->processLookup( ev );
            more = pLookupAid->isMore( ev ) != FALSE;
            pTree->setLookupAid( ev, pLookupAid );
         }
         else
         {
            delete pLookupAid;
         }
      }
      catch ( AWDException *pExc )
      {
         delete pLookupAid;

         ConvertAwdExceptionToConditionException( pExc,
                                                  ec,
                                                  I_("doLookup()"),
                                                  __FILE__,
                                                  __LINE__ );
      }
      catch ( ConditionException &ce )
      {
         delete pLookupAid;
         throw ce;
      }
      catch ( ... )
      {
         delete pLookupAid;

         THROWFROMFILE( DIAWD23_CONDITION,
                        I_( "Awd23Interface::doLookup()" ),
                        DIAWD23_UNKNOWN_AWD_EXCEPTION );
      }
   }

   return pTree;
}


//******************************************************************************
//
// ^PRIVATE METHOD      : Awd23Interface::getComparison
//
// ^DESCRIPTION :
//
// ^PARAMETERS  :
//   ^^ AwdLookupCriteria::Comparison comp -
//
// ^RETURNS     : const char * -
//
// ^THROWS      : < description of all possible thrown exceptions >
//
// ^EXAMPLE     : < if the use of this member is not obvious,
//                  give an example >
//
//******************************************************************************
char *Awd23Interface::getComparison( AwdLookupCriteria::Comparison comp )
{
   char * pCompare = NULL;

   switch ( comp )
   {
      case AwdLookupCriteria::EQUAL_TO:
         pCompare = szEQUAL_TO;
         break;

      case AwdLookupCriteria::LESS_THAN:
         pCompare = szLESS_THAN;
         break;

      case AwdLookupCriteria::GREATER_THAN:
         pCompare = szGREATER_THAN;
         break;

      case AwdLookupCriteria::GREATER_THAN_OR_EQUAL:
         pCompare = szGREATER_THAN_OR_EQUAL;
         break;

      case AwdLookupCriteria::LESS_THAN_OR_EQUAL:
         pCompare = szLESS_THAN_OR_EQUAL;
         break;

      case AwdLookupCriteria::NOT_EQUAL:
         pCompare = szNOT_EQUAL;
         break;

      default:
         pCompare = " ";
   }

   return pCompare;
}

//******************************************************************************
//
// ^PRIVATE METHOD      : Awd23Interface::getWorkTypeList
//
// ^DESCRIPTION : This will return the worktype list base on a filter
//
// ^PARAMETERS  :
//   ^^ const string & busarea -
//   ^^ const char type -
//
// ^RETURNS     : string_vector -
//
// ^THROWS      : ConditionException
//
//******************************************************************************
string_vector Awd23Interface::getWorkTypeList( const DString & busarea,
                                               const char type )
{
   string_vector list;

   // Make sure the operator is logged on to AWD
   if ( s_loggedOn )
   {
      ACBL0046       *pView    = NULL;
      ACBL0046Record *pRec     = NULL;
      unsigned long   repeats  = 0;
      char           *pBusarea = NULL;
      DString          workType;
      char            workTypeCode;

      // make a buffer to pass the business area
      pBusarea = new char[ busarea.length() + 1 ];

      ASSERT_NEW( pBusarea, ec, I_("getWorkTypeList()") )

      // Copy the business area
      strcpy( pBusarea, busarea.asA().c_str() );

      try
      {
         // Create a new ACBL0046
         pView = new ACBL0046( ev, pBusarea );

         ASSERT_NEW( pView, ec, I_("getWorkTypeList()") )

         // Make the view call
         pView->start( ev );
         repeats = pView->numRepeats( ev );

         // If we have 1 or more repeats, we have a list
         if ( repeats )
         {
            pRec = new ACBL0046Record();

            ASSERT_NEW( pRec, ec, I_("getWorkTypeList()") )

            for ( unsigned long index = 0; index < repeats; ++index )
            {
               // Cycle throug the list and copy the values
               pView->getRecord( ev, pRec, index, AWDView_INDEX );
               workType = pRec->workType( ev );
               workTypeCode = pRec->workTypeCode( ev );

               if ( ( WRKT_BOTH == type ) || ( workTypeCode == type ) )
               {
                  list.push_back( workType );
               }
            }

            delete pRec;
         }

         delete pView;
      }
      AWD_EXCEPTION_TO_CONDITION_EXCEPTION( ec, I_("getWorkTypeList()") )

      // Cleanup
      delete[] pBusarea;
   }

   return list;
}

//******************************************************************************
//
// ^PRIVATE METHOD      : Awd23Interface::createAwdWork
//
// ^DESCRIPTION : Creates an AWD work (transaction or case) object
//
// ^PARAMETERS  :
//   ^^ AwdData &awdData - LOB items
//   ^^ bool lock        - true to lock, fals to not lock
//   ^^ int type         - transaction or case
//
// ^RETURNS     : bool -
//
// ^THROWS      : ConditionException - memory allocation errors
//
//******************************************************************************
bool Awd23Interface::createAwdWork( AwdData &awdData, bool lock )
{
   MAKEFRAME( DIAWD23_CONDITION, I_("Awd23Interface::createAwdWork()") )

   bool created = false;

   // make sure the operator is logged on
   if ( s_loggedOn )
   {
      AWD_AWDLOBARRAYSTRCT lobArray;
      Awd23Key *pKey = NULL;

      DString amtt = awdData.getLobValue( strAMTT );

      if ( amtt.empty() )
      {
         awdData.setLobData( strAMTT, I_("U") );
      }

      awdData.setLobData( strCRNO, I_("01") );
      awdData.setLobData( strOWNE, I_("01") );
      awdData.setLobData( strSUSP, I_("N") );
      awdData.setLobData( strVIFL, I_("N") );
      awdData.setLobData( strOBJT, I_("") );

      // Create LOB array
      if ( fillLobArray( awdData, lobArray ) )
      {
         try
         {
            CSingleLock singleLock( &s_csListener );
            singleLock.Lock();

            // Create an AWD object
            AWDWork *pWork;

            // See if we are a Transaction - if not we are a Case
            DString strReco = awdData.getLobValue( strRECO );

            if ( I_("T") == strReco )
            {
               pWork = new AWDTransaction( ev, &lobArray );
            }
            else
            {
               pWork = new AWDCase( ev, &lobArray );
            }

            ASSERT_NEW( pWork, ec, I_("createAwdWork()") )

            DString beginTime = awdData.getBeginTime();
            DString endTime = awdData.getEndTime();

            if ( ( ! beginTime.empty() ) && ( ! endTime.empty() ) )
            {
               char szBegin[ AwdData::DATETIME_LEN + 1 ];
               char szEnd[ AwdData::DATETIME_LEN + 1 ];

               strncpy( szBegin, beginTime.asA().c_str(), AwdData::DATETIME_LEN );
               strncpy( szEnd, endTime.asA().c_str(), AwdData::DATETIME_LEN );

               szBegin[ AwdData::DATETIME_LEN ] = '\0';
               szEnd[ AwdData::DATETIME_LEN ] = '\0';

               // must be 0 or AWDOBJ uses it instead
               pWork->setElapsedTime( ev, 0 );
               //CCYY-MM-DD-HH.MM.SS.FFFFFF
               pWork->setBeginTimeFromTimestamp( ev, szBegin );
               pWork->setEndTimeFromTimestamp( ev, szEnd );
            }

            if( lock )
            {
               pWork->create( ev, AWDBase_LOCKED, 0 );
            }
            else
            {
               pWork->create( ev, AWDBase_UNLOCKED, 0 );
            }

            created = pWork->retrieveSecondaryFields( ev ) != FALSE;

            if ( created )
            {
               pKey = new Awd23Key( pWork );
               ASSERT_NEW( pKey, ec, I_("createAwdWork()") )

               FieldList *pFieldList =  pWork->getFieldList( ev );

               if ( pFieldList )
               {
                  AWDBaseField *pAWDBaseField = (AWDBaseField * )pFieldList->somfFirst( ev );

                  while( pAWDBaseField )
                  {
                     int seq = pAWDBaseField->sequenceNumber( ev );

                     awdData.setLobData( DStringA( pAWDBaseField->name( ev ) ),
                                         DStringA( pAWDBaseField->asString( ev ) ),
                                         ( seq > 0 ) ? seq : 1 );

                     pAWDBaseField = (AWDBaseField *)pFieldList->somfAfter( ev, pAWDBaseField );
                  }
               }

               AWDOBJKEY objKey = pKey->getKey();
               s_lastKey = objKey;

               smartInsert( pKey, NULL, false, true );
            }

            // The Awd23Key will make a copy of the object
            // so we still need to delete it here.
            delete pWork;
         }
         AWD_EXCEPTION_TO_CONDITION_EXCEPTION( ec, I_("createAwdWork()") )

         delete[] lobArray.pAwdLobData;
      }

      if ( ! created )
      {
         // Failed to create the AWD object
         ADDCONDITIONFROMFILE( DIAWD23_CREATE_AWDOBJ_FAIL );

         pKey = new Awd23Key();
         ASSERT_NEW( pKey, ec, I_("createAwdWork()") )
      }

      // When the awdData object is destroyed, it will delete pKey
      awdData.setKey( pKey );
      created = pKey->isKey();
   }

   return created;
}

//******************************************************************************
//
// ^PRIVATE METHOD      : Awd23Interface::fillLobArray
//
// ^DESCRIPTION : Populates the lob array with the lob data objects in the
//                AwdData object.
//
//                * This method allocates memory, with a new, for the member
//                  lobArray.pAwdLobData.  The calling method should delete
//                  this memory when it is done.
//
// ^PARAMETERS  :
//   ^^ AwdData &awdData      -  source
//   ^^ AWDLOBARRAY &lobArray -  destination
//
// ^RETURNS     : bool -
//
// ^THROWS      : ConditionException
//
//******************************************************************************
bool Awd23Interface::fillLobArray( AwdData &awdData,
                                   AWD_AWDLOBARRAYSTRCT &lobArray )
{
   TRACE_METHOD( I_("Awd23Interface"), I_("fillLobArray( AwdData &, AWDLOBARRAY & )") )

   unsigned short count = awdData.lobCount();  // count of items to insert
   lobArray.pAwdLobData = NULL;
   lobArray.usCount     = 0;

   bool success = false;

   if ( count )
   {
      int iSeq;            // the sequence number in integer form

      // Make sure we are ASCII
      DStringA name;       // the value's DataName
      DStringA value;      // the value
      DStringA seq;        // the sequence number in DString form

      data_obj_map_iterator awdFieldIter; // Iterator for the field list

      AWD_PAWDLOBDATASTRCT pAwdLobData = new AWD_AWDLOBDATASTRCT[ count ];

      ASSERT_NEW( pAwdLobData, ec, I_("fillLobArray()") )

      unsigned short index = 0;    // count of items inserted into the array

      AwdData::LobIterator iter( awdData.begin() );
      AwdData::LobIterator end( awdData.end() );

      while ( ( iter != end ) && ( index < count ) )
      {
         // Grab the value
         name  = ( *iter ).getName();
         value = ( *iter ).getValue();
         seq   = ( *iter ).getSeqNoAsString();
         iSeq  = ( *iter ).getSeqNo();

         if ( ! value.empty() )
         {
            // See if the Data Name is defined
            awdFieldIter = s_pLists->m_fieldList.find( name );

            // Found! This is LOB data, insert it into the LOB array
            if ( awdFieldIter != s_pLists->m_fieldList.end() )
            {
               const Data *pAwdField = &( ( *awdFieldIter ).second );

               DString fldType = pAwdField->getElementValue( DBR::Fld_Type );

               // Treat Groups differently
               if ( ACBL0049_TYPE_GROUP == asInteger( fldType ) )
               {
                  // Put the group together
                  group_map_iterator listIter = s_pLists->m_groupList.find( name );

                  if ( listIter != s_pLists->m_groupList.end() )
                  {
                     group_seq *pGroup = &( ( *listIter ).second );
                     group_seq_iterator groupIter = pGroup->begin();

                     DStringA newValue( "" );
                     bool allOk = true;

                     while ( groupIter != pGroup->end() )
                     {
                        // Grab the data name
                        DStringA dataName = ( *groupIter ).second;

                        // Find the dataname in the data dictionary
                        data_obj_map_iterator dataIter = s_pLists->m_fieldList.find( dataName );

                        // If we did not find the dataname, exit this loop
                        if ( dataIter == s_pLists->m_fieldList.end() )
                        {
                           allOk = false;
                           break;
                        }

                        const Data *pGroupField = &( ( *dataIter ).second );
                        DStringA dataValue = awdData.getLobValue( dataName );

                        // Format the data value
                        formatLobItem( awdData, pGroupField, dataName, dataValue );

                        // append the data value
                        newValue += dataValue;

                        // Let's go on to the next data item in the group
                        ++groupIter;

                     } // end while

                     if ( allOk )
                     {
                        // Set and store
                        value = newValue;
                        awdData.setLobData( name, value, iSeq );
                     }
                  } // end if
               }
               else
               {
                  // Not a group - just format the value
                  formatLobItem( awdData, pAwdField, name, value, iSeq );
               }

               // Put the value in the LOB array
               memset( &pAwdLobData[index], ' ', sizeof( AWDLOBDATA ) );
               memcpy( pAwdLobData[index].seqnbr, seq.c_str(), seq.length() );
               memcpy( pAwdLobData[index].dataname, name.c_str(), name.length() );
               memcpy( pAwdLobData[index].datavalue, value.c_str(), value.length() );
               pAwdLobData[index].datalength = value.length();

   #ifdef ENABLE_TRACING
               DStringA valueLen;
               valueLen.appendInt( value.length() );
               valueLen.padRight( 2, '0' );

               DStringA msg = "AWD Data - ";
               msg += seq;
               msg += ' ';
               msg += name;
               msg += " = [";
               msg += valueLen;
               msg += "] ";
               msg += value;

               TRACE_CLASS_MSG( I_("Awd23Interface"),
                                I_("fillLobArray( AwdData &, AWDLOBARRAY & )"),
                                msg)
   #endif

               ++index;
            } // end - is LOB data
         }

         ++iter;
      } // end - while loop

      // We are successfull if we put at least one item into the array
      success = ( index > 0 );

      lobArray.usCount = index;

      if ( success )
      {
         lobArray.pAwdLobData = pAwdLobData;
      }
      else
      {
         delete[] pAwdLobData;
      }
   }

   return success;
}

//******************************************************************************
//
// ^PRIVATE METHOD      : formatLobITem
//
// ^DESCRIPTION : formats an LOB item accoring to the data dictionary
//
// ^PARAMETERS  :
//   ^^ AwdData &awdData -
//   ^^ const Data *pAwdField -
//   ^^ const string &name -
//   ^^ string &value -
//
// ^RETURNS     : Awd23Interface::void -
//
// ^THROWS      : none
//
//******************************************************************************
void Awd23Interface::formatLobItem( AwdData &awdData,
                                    const Data *pAwdField,
                                    const DStringA &name,
                                          DStringA &value,
                                    const int iSeq )
{
   unsigned long vlen;          // the DString length of the value
   unsigned long vdec;          // the decimal location of the value
   unsigned long length;        // the length defined for the DataName
   unsigned long decimal;       // the decimal defined for the DataName
   DString strTemp;

   char chFldFormat = chUNKNOWN;
   DStringA strFldFormat = pAwdField->getElementValue( DBR::Fld_Format );
   length = pAwdField->getElementValue( DBR::Fld_Length, strTemp ).convertToULong();
   decimal = pAwdField->getElementValue( DBR::Fld_Decimal, strTemp ).convertToULong();

   if ( !strFldFormat.empty() )
   {
      chFldFormat = strFldFormat[0];
   }

   // Check to see if the data is Numeric
   if ( chNUMERIC == chFldFormat )
   {
      if ( isDecimal( value ) )
      {
         // Format the amount for AWD
         value.stripLeading( ' ' );
         value.stripLeading( '+' );
         value.stripLeading( '-' );

         vlen = value.length();
         vdec = value.find( "." );

         if ( vdec == DString::npos )
         {
            value += DStringA( decimal, '0' );
         }
         else
         {
            value.erase( vdec, 1 );
            --vlen;

            if ( ( vlen - vdec ) < decimal )
            {
               value += DStringA( decimal - ( vlen - vdec ), '0' );
            }
            else if ( ( vlen - vdec ) > decimal )
            {
               value.erase( vdec + decimal );
            }
         }

         vlen = value.length();

         if ( vlen < length )
         {
            value.padLeft(length, '0');
//            value.getImp().insert( value.getImp().begin(), length - vlen, '0' );
         }
         else if ( vlen > length )
         {
            value.getImp().erase( length + 1 );
         }
      }
      else
      {
         value = DString( length, '0' );
      }

      // Save the modified value back in the AwdData object
      awdData.setLobData( name, value, iSeq );
   } // end Numeric data

   vlen = value.length();

   // Make sure the data is not too long
   if ( vlen > length )
   {
      // Strip off the extra bit.  Since a string is zero based,
      // this works.
      value.erase( length );
      // Save the modified value back in the AwdData object
      awdData.setLobData( name, value, iSeq );
   }
   else if ( vlen < length )
   {
      enum FillType
      {
         NoFill,
         PreFill,
         PostFill
      };

      FillType ft;
      char chFill;

      switch ( chFldFormat )
      {
         case chNUMTEXT:
            ft = PreFill;
            chFill = '0';
            break;

         case chALPHA:
            ft = PostFill;
            chFill = ' ';
            break;

         default:
            ft = NoFill;
            break;
      }

      if ( PreFill == ft )
      {
         value.padLeft(length, chFill);
//         value.getImp().insert( value.getImp().begin(), length - vlen, chFill );
      }
      else if ( PostFill == ft )
      {
         value.getImp().append( length - vlen, chFill );
      }
   }
}

//******************************************************************************
//
// ^PRIVATE METHOD      : Awd23Interface::objectLockStatus
//
// ^DESCRIPTION : Returns the object's locked status
//
// ^PARAMETERS  :
//   ^^ PAWDOBJ pAwdobj -
//
// ^RETURNS     : ObjectLockType -
//
// ^THROWS      : none
//
//******************************************************************************
Awd23Interface::ObjectLockType Awd23Interface::objectLockStatus( AWDBase *pObj )
{
   TRACE_METHOD( I_("Awd23Interface"), I_("objectLockStatus( AWDBase *pAwdobj )") )

   ObjectLockType locked;

   if ( pObj->isLocked( ev ) )
   {
      AWDString *pAwdStr = new AWDString;

      ASSERT_NEW( pAwdStr, ec, I_("objectLockStatus()") )

      DStringA lockedBy = pObj->lockedBy( ev, pAwdStr );
      DString opid = getOperatorID();

      delete pAwdStr;

      // Clean them up
      strip( lockedBy );
      strip( opid );

      if ( ! lockedBy.compare( opid.asA() ) )
      {
         locked = OBJ_LOCKED_BY_USER;
      }
      else
      {
         // char szBuff[255];
         locked = OBJ_LOCKED_BY_OTHER;

         MAKEFRAMENOTRACE( DIAWD23_CONDITION,
                           I_("Awd23Interface::objectLockStatus()") )

         DStringA idiString = AWD_ERROR_MESSAGE;
         idiString += '=';
         idiString += lockedBy;

         ADDCONDITIONFROMFILEIDI( DIAWD23_OBJECT_LOCKED, idiString );
      }
   }
   else
   {
      locked = OBJ_NOT_LOCKED;
   }

   return locked;
}

//******************************************************************************
//
// ^PRIVATE METHOD      : Awd23Interface::populateFiledList
//
// ^DESCRIPTION : This method will populate s_pLists->m_fieldList
//
// ^PARAMETERS  : none
//
// ^RETURNS     : void
//
// ^THROWS      : ConditionExeception if an AWDException is caught.
//
//******************************************************************************
void Awd23Interface::populateFieldList( AWDApplication * pApp )
{
   TRACE_METHOD( I_("Awd23Interface"), I_("populateFieldList()") )

   // Make sure we're logged on
   if ( s_loggedOn && ( NULL != pApp ) )
   {
      if ( NULL == s_pLists )
      {
         s_pLists = new Awd23Statics;
      }

      data_obj_map &fieldList = s_pLists->m_fieldList;
      group_map &groupList = s_pLists->m_groupList;

      DString value;
      DString dataName;

      Data dbAwdField( DBR::AWDFIELD_VW );

      // If the field list is not empty, empty it.
      if ( ! fieldList.empty() )
      {
         fieldList.erase( fieldList.begin(), fieldList.end() );
      }

      // If the group list is not empty, empty it.
      if ( ! groupList.empty() )
      {
         groupList.erase( groupList.begin(), groupList.end() );
      }

      try
      {
         AWDDictionary *pDict = pApp->getDictionary();
         AWDData       *pRec  = (AWDData *)pDict->somfFirst(NULL);

         while ( pRec )
         {
            // Get the data name
            dataName = pRec->name( ev );
            dbAwdField.setElementValue( DBR::Fld_Data_Name, dataName );

            // Get the format
            switch ( pRec->format( ev ) )
            {
               case ACBL0049_FORMAT_ALPHA:
                  value = chALPHA;
                  break;
               case ACBL0049_FORMAT_NUMTEXT:
                  value = chNUMTEXT;
                  break;
               case ACBL0049_FORMAT_DATETIME:
                  value = chDATETIME;
                  break;
               case ACBL0049_FORMAT_DATE:
                  value = chDATE;
                  break;
               case ACBL0049_FORMAT_TIME:
                  value = chTIME;
                  break;
               case ACBL0049_FORMAT_CURRENCY:
                  value = chCURRENCY;
                  break;
               case ACBL0049_FORMAT_NUMERIC:
                  value = chNUMERIC;
                  break;
               default:  // Should never happen
                  value = " ";
            }

            dbAwdField.setElementValue( DBR::Fld_Format, value );

            // Get the length
         std::ostringstream length;
         length << pRec->length(NULL) << std::ends;
            value = length.str();
            dbAwdField.setElementValue( DBR::Fld_Length, value );

            // Get the decimal portion
            std::ostringstream decimal;
         decimal << pRec->decimals(NULL) << std::ends;
            value = decimal.str();
            dbAwdField.setElementValue( DBR::Fld_Decimal, value );

            // Get the mask
            value =  pRec->mask(NULL);
            dbAwdField.setElementValue( DBR::Fld_Mask, value );

            // Get the field type
            std::ostringstream fldType;
         fldType << pRec->fldType(NULL) << std::ends;
            value = fldType.str();
            dbAwdField.setElementValue( DBR::Fld_Type, value );

            // Get the medium name
            value = pRec->mediumName(NULL);
            dbAwdField.setElementValue( DBR::Fld_Medium_Name, value );

            // Group management
            if ( pRec->isPartofGroup( ev ) )
            {
               DString groupName = DStringA( pRec->groupName( ev ) );
               unsigned short seq = pRec->groupSequence( ev );
               DString strSeq = asString( seq );

               group_map_iterator listIter = groupList.find( groupName );

               if ( listIter == groupList.end() )
               {
                  group_seq group;

                  group.insert( group_seq_type( seq, dataName ) );

                  groupList.insert( group_map_type( groupName, group ) );
               }
               else
               {
                  group_seq *pGroup = &( ( *listIter ).second );

                  group_seq_iterator groupIter = pGroup->find( seq );

                  if ( groupIter == pGroup->end() )
                  {
                     pGroup->insert( group_seq_type( seq, dataName ) );
                  }
                  else
                  {
                     ( *groupIter ).second = dataName;
                  }
               }

               dbAwdField.setElementValue( DBR::Fld_Group_Name, groupName );
               dbAwdField.setElementValue( DBR::Fld_Group_Sequence, strSeq );
            }
            else
            {
               dbAwdField.setElementValue( DBR::Fld_Group_Name, I_("    ") );
               dbAwdField.setElementValue( DBR::Fld_Group_Sequence, I_("0") );
            }

            // Check for Indexed field
            if ( pRec->isIndexed( ev ) )
            {
               unsigned short index = pRec->indexNumber( ev );
               DString strIndex = asString( index );
               dbAwdField.setElementValue( DBR::Fld_Index_Number, strIndex );
            }
            else
            {
               dbAwdField.setElementValue( DBR::Fld_Index_Number, I_("0") );
            }

            // Insert into the map, using the data name as the key
            fieldList.insert( data_obj_type( dataName, dbAwdField ) );

            pRec = (AWDData *)pDict->somfAfter( ev, pRec );
         }
      }
      AWD_EXCEPTION_TO_CONDITION_EXCEPTION( ec, I_("populateFieldList()") )
   }
}

//******************************************************************************
//
// ^PRIVATE METHOD      : Awd23Interface::verifyFile
//
// ^DESCRIPTION : This method will verify that a file exists.
//
// ^PARAMETERS  :
//   ^^ const DString strFile - File to check
//
// ^RETURNS     : bool - True if exists
//
// ^THROWS      : none
//
//******************************************************************************
bool Awd23Interface::verifyFile( const DString &strFile )
{
   return -1 != _access( strFile.asA().c_str(), 0x00 );
}

/**
 * This method will determine whether or not to use the
 * AwdApiInsertItemAndTakeOwnership function.  If API is to be used, the static
 * funtion pointer will be set, otherwise it will remain NULL.
 */
void Awd23Interface::determineTakeOwnership()
{
   // The first time this method is called s_hAwdApi will be NULL.
   // This check should be done only once, therefore even if the
   // call to GetModuleHandle fails, s_hAwdApi will be non-NULL after
   // the code segment below.
   if ( NULL == s_hAwdApi )
   {
      s_hAwdApi = GetModuleHandle( I_("AWDAPI.DLL") );

      if ( NULL != s_hAwdApi )
      {
         // Now that we have the module handle for the AWDAPI.DLL
         // we will check to see if AWD's code fix for the container
         // is present.  If AWD's fix to the container is not present,
         // then AwdApiInsertItemAndTakeOwnership should *NOT* be
         // called.
         //
         // The method of determination will be to check the time-date
         // stamp on the file AWDCONT.DLL.  If the date is 6/1/2001
         // or greater, there is a 99% chance that the AWD fix has
         // been installed.  The last major release of AWD client
         // without the fix is AWD 2.3.4 and the AWDCONT.DLL has a
         // date of March 2001.  Any future release of AWD client
         // should have the fix.

         do
         {
            WIN32_FIND_DATA findData;
            FILETIME *pFileTime = &(findData.ftLastWriteTime);
            SYSTEMTIME systemTime;
            TCHAR szFileName[ MAX_PATH ];
            LPTSTR lpFilePart;

            // First find the full file name for ADWCONT.DLL
            // by searhcing the PATH.
            DWORD dwLen = SearchPath( NULL,
                                      I_("AWDCONT.DLL"),
                                      NULL,
                                      MAX_PATH,
                                      szFileName,
                                      &lpFilePart );

            // If the length is zero, then the file has not been
            // found.
            if ( 0 == dwLen )
            {
               break;
            }

            // Second, FindFirstFile will return the information
            // that we are looking for.
            HANDLE hSearch = FindFirstFile( szFileName, &findData );

            // If an invalid handle is returned, then the file
            // was not found.
            if ( INVALID_HANDLE_VALUE == hSearch )
            {
               break;
            }

            FindClose( hSearch );

            // Third extract the info we need to check
            if ( ! FileTimeToSystemTime( pFileTime, &systemTime ) )
            {
               break;
            }

            // Make sure the date is appropriate
            if ( 2000 > systemTime.wYear ||
                 ( 2000 == systemTime.wYear &&
                   6 > systemTime.wMonth ) ) {
               break;
            }

            // We have passed all tests in determining that the date
            // of the file AWDCONT.DLL is June 1, 2001 or greater.
            // Therefore, the AWD fix to this DLL should be present
            // and we can safely use the take ownwership API.
            s_pAwdApiInsertItemAndTakeOwnership =
              (API_INSERT)GetProcAddress( s_hAwdApi, szAPI_INSERT );
         }
         while ( false );
      }
      else
      {
         s_hAwdApi = (HMODULE)TRUE;
      }
   }
}

//******************************************************************************
//
// ^PRIVATE METHOD      : Awd23Interface::listenerCallbackProc
//
// ^DESCRIPTION :
//
// ^PARAMETERS  :
//   ^^ AWDEvent* eventObj -
//   ^^ void* pParam -
//
// ^RETURNS     : void -
//
// ^THROWS      : < description of all possible thrown exceptions >
//
// ^EXAMPLE     : < if the use of this member is not obvious,
//                  give an example >
//
//******************************************************************************
void Awd23Interface::listenerCallbackProc( AWDEvent* eventObj, void* pParam )
{
   Awd23Interface *pAwd = static_cast<Awd23Interface *>( pParam );

   unsigned long messageId = eventObj->messageId( ev );
   unsigned long created   = AWD_OBJECT_CREATED;

   if ( created == messageId )
   {
      CSingleLock singleLock( &s_csListener );
      singleLock.Lock();

      AWDOBJKEY key;

      unsigned long hObject = eventObj->getAwdObjectRepositoryHandle( ev );

      AWDObjectFactory* pObjFact = new AWDObjectFactory();
      AWDCommon *pCommon = pObjFact->makeFromHandle( ev, hObject );
      delete pObjFact;

      AWDBase *pObj = static_cast<AWDBase *>( pCommon );
      pObj->getKeyStrct( ev, (AWD_PAWDOBJECTKEYSTRCT)&key );

      // Make sure this is not one we just created.
      if ( 0 != memcmp( &s_lastKey, &key, sizeof( AWDOBJKEY ) ) )
      {
         if ( ! pObj->isLocked( ev ) )
         {
            pObj->lock( ev );

            Awd23Key *p23Key = new Awd23Key( pObj );
            pAwd->m_keyList.push_back( p23Key );
            addToLockList( p23Key );
         }
      }

      delete pCommon;
   }
}

bool Awd23Interface::findInLockList( const Awd23Key *pKey,
                                     string_vector_a &list,
                                     string_vector_a_iterator &iter,
                                     DStringA &strKey )
{
   bool found = false;

   strKey = DStringA( (char *)( &( pKey->getKey() ) ), sizeof( AWDOBJKEY ) );
   string_vector_a_iterator end = list.end();
   iter = list.begin();

   while ( ! ( found || iter == end ) )
   {
      const DStringA &strCompare = *iter;

      found = strCompare == strKey;

      if ( ! found )
      {
         ++iter;
      }
   }

   return found;
}

void Awd23Interface::addToLockList( const Awd23Key *pKey )
{
   if ( NULL != s_pAwdApiInsertItemAndTakeOwnership )
   {
      string_vector_a &list = s_pLists->m_lockList;
      string_vector_a_iterator iter = list.begin();
      DStringA strKey;

      if ( ! findInLockList( pKey, list, iter, strKey ) )
      {
         list.push_back( strKey );
      }
   }
}

bool Awd23Interface::checkLockList( const Awd23Key *pKey )
{
   bool found = true;

   if ( NULL != s_pAwdApiInsertItemAndTakeOwnership )
   {
      string_vector_a &list = s_pLists->m_lockList;
      string_vector_a_iterator iter = list.begin();
      DStringA strKey;

      found = findInLockList( pKey, list, iter, strKey );

      if ( found )
      {
         list.erase( iter );
      }
   }

   return found;
}

#pragma optimize( "", on )

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// Name:
//    %PM%
//    %PID%
//
// Description:
//    %PD%
//
// Design Parts:
//    %PIRP%
//
// Last Changed:
//    %PO%  -  %PRT%
//
// Changes:
//    %PLA%
//
//
// $Log:   Y:/VCS/iFastAWD/diawd23/awd23interface.cpp-arc  $
// 
//    Rev 1.4   Nov 02 2011 04:42:20   purdyech
// Registry cleanup
//
//    Rev 1.3   18 Apr 2008 14:40:16   kovacsro
// IN#1250989 - also setting the object key for getStatusList(const AwdKey *pKey, const DString &strBussArea, const DString &strWkType)
//
//    Rev 1.2   30 Jan 2008 14:16:46   kovacsro
// IN#1118094 - added an overloaded getStatusList method
//
//    Rev 1.1   28 Jan 2008 15:16:16   kovacsro
// IN#1103220 - entry# 3 - changed the maximum comment length
//
//    Rev 1.0   28 Jan 2008 13:16:22   kovacsro
// Initial revision.
//
//    Rev 1.34   Apr 30 2002 16:51:52   DT21858
// Fixed problem with ACBL0043 view call.
//
//    Rev 1.33   Nov 28 2001 11:07:42   dt21858
// Fix - Timing issue problem with closing AWD CSDs and
// clearing the AWD container.
//
//    Rev 1.32   Nov 23 2001 10:16:46   dt21858
// Made fix to enhancement regarding the AWD Data Dictionary
//
//    Rev 1.31   Nov 16 2001 07:55:40   dt21858
// Corrected include statement of a generated header file.
//
//    Rev 1.30   Nov 15 2001 15:50:50   dt21858
// Now tracks Index fields in the AWD Data Dictionary (AwdFields)
//
//    Rev 1.29   Oct 16 2001 15:03:04   dt21858
// Added stopCSD()
// Added selectItemInContainer()
//
//    Rev 1.28   Aug 23 2001 16:52:52   DT21858
// - Added overloaded method for insertItemInContainer().
// - Code Cleanup
//
//    Rev 1.27   Aug 13 2001 13:56:48   DT21858
// Added getImmediateChildren()
//
//    Rev 1.26   Aug 06 2001 15:07:08   DT21858
// - Sync up eith 1.7.2.10 branch (comments included below)
// - Added getWorkstationID(), getCountry() and implemented getQueueList()
//
//    Rev 1.9.2.15   Aug 01 2001 16:52:22   DT21858
// Additional fix for unlocking AWD work
//
//    Rev 1.9.2.14   Jul 10 2001 08:03:00   DT21858
// Check in changes for Craig:
//    added getAllChildren()
//    removed getAllAwdContainerObjects()
//
//    Rev 1.9.2.13   Jun 25 2001 17:35:26   DT21858
// Checkin fix to getAllAwdContainerObjects() by Craig
//
//    Rev 1.9.2.12   Jun 18 2001 11:41:00   DT21858
// check in bug fix to getAllAwdContainerObjects()
// for Craig B.
//
//    Rev 1.9.2.11   Jun 15 2001 08:28:54   DT21858
// Checked in methods added by Craig:
//    showAwdContainer()
//    showAwdServiceWindow()
//    hasActiveService()
//    getAllAwdContainerObjects()
// also removed:
//    isSuspended()
//
//    Rev 1.9.2.9   May 23 2001 11:08:52   DT21858
// Fixed isLocked()
// Optimized isSuspended()
// Fixed/Enhanced lockAwdObject()
//
//    Rev 1.25   Jun 04 2001 15:00:00   DT21858
// Sync-up with Infra 1.7
//
//    Rev 1.9.1.17   May 22 2001 12:48:04   DT21858
// Sync up with 17210 branch
//
//    Rev 1.9.2.8   May 21 2001 15:55:48   DT21858
// Changes for TA Desktop
//    - added isSuspended()
//
//    Rev 1.9.2.7   May 10 2001 09:35:28   DT21858
// added module state management
//
//    Rev 1.9.2.5   May 09 2001 17:19:14   DT21858
// Fix for release builds
//
//    Rev 1.9.2.3   May 09 2001 09:41:32   DT21858
// Added two methods:
// doubleClickContainerItem()
// getCurrentContainerSelection()
//
//    Rev 1.9.2.2   May 08 2001 12:05:40   DT21858
// Sync up with Fixes for TA Desktop 3.6
//
//    Rev 1.9.2.1   May 07 2001 13:42:20   DT21858
// Fix to prevent multiple unlocks by giving the AWD container
// ownership of work objects.
//
//    Rev 1.9.2.0   May 04 2001 16:11:24   DT21858
// Branch Check in
//
//    Rev 1.9.1.16   Apr 23 2001 10:46:06   dt21858
// Enhancements for TA Desktop
// Made by Craig Belser
// Checked in by Michael McGarry
//
//    Rev 1.9.1.15   Mar 08 2001 14:29:00   DT21858
// Additional enhancements to support AWD Suspend operationsAdditional
// enhancements to support AWD Suspend operations
//
//    Rev 1.9.1.14   Feb 06 2001 16:11:02   dt21858
// Sync up with 1.9 fixes
//
//    Rev 1.9.1.13   Feb 06 2001 15:15:56   dt21858
// Added getAwdWorkObjects()
//
//    Rev 1.9.1.12   Feb 06 2001 09:04:50   dt21858
// Added code to start the Personal Queue Monitor in
// support of TaLogon.
//
//    Rev 1.9.1.11   Jan 29 2001 12:22:24   dt21858
// Added getServerDateTime()
//
//    Rev 1.9.1.10   Jan 12 2001 13:09:24   dt21858
// Fixed syntax error due to capitolization
//
//    Rev 1.9.1.9   Jan 10 2001 13:38:08   dt21858
// Enhancement - Added suspend and unsuspend methods
//
//    Rev 1.9.1.8   Sep 11 2000 15:08:16   DT21858
// Work-around for closing container in W2K
//
//    Rev 1.9.1.7   Jun 09 2000 12:36:22   DMUM
// Removed calls to AwdApiQueryContainerMode().
// This is redundant error checking and does not
// work on Windows 2000.
//    Rev 1.24   Mar 23 2001 10:27:14   dt24433
// Removed use of getDataElement and substituted appropriate alternative code.
//
//    Rev 1.23   Feb 07 2001 09:14:28   dt21858
// Sync up with 1.7
//
//    Rev 1.22   Sep 11 2000 15:29:52   DT21858
// Sync up with 1.7 changes
//
//    Rev 1.21   Mar 24 2000 12:32:38   DMUM
// Dropped SingletonBase and now uses SingletonRegister
//
//    Rev 1.9.1.5   Mar 23 2000 09:33:42   DMUM
// Now uses SingletonRegister
//
//    Rev 1.20   Sep 30 1999 09:23:04   DMUM
// Started using SingletonBase
//
//    Rev 1.19   Aug 26 1999 14:34:00   DMUM
// Now has been unicode tested
//
//    Rev 1.18   Aug 26 1999 12:55:34   DMUM
// Sync up with 1.7 & 1.6
// Now supports Sources and the starting and stoping of
// a service.
//
//    Rev 1.16   Jun 10 1999 15:56:16   DMUM
// Bux Fix
//
//    Rev 1.15   May 18 1999 08:49:50   DMUM
// Sync up with 1.6.X
//
//    Rev 1.14   May 14 1999 13:02:38   DMUM
//
//
//    Rev 1.13   Apr 16 1999 17:38:18   DMUM
// Changes for Unicode compiles
//
//    Rev 1.12   Apr 09 1999 13:50:32   DMUM
// Sync up with 1.6.x
//
//    Rev 1.9.1.0   Mar 31 1999 13:20:48   DMUM
// Sync up with Infra 1.6.x
//
//    Rev 1.1.1.8   Mar 24 1999 12:42:44   DMUM
// The AWD container is now cleared by posting the
// message that a user clicked on the 'Clear' button.
// Fixes TT 7151
//
//    Rev 1.1.1.7   Feb 19 1999 07:48:48   DMUM
// Added lookupSource()
//
//    Rev 1.1.1.6   Feb 08 1999 15:18:50   DMUM
// Changes for TA2000 NT 3.4
//
//    Rev 1.1.1.5   Jan 20 1999 16:41:50   DMUM
// Development for TA2000 NT rel 3.4
//
//    Rev 1.1.1.4   Dec 30 1998 16:12:46   DMUM
// Fixes - for Kemper & for 3.4
//
//    Rev 1.1.1.3   Dec 11 1998 10:12:38   DMUM
// Added loadCSD()
//
//    Rev 1.1.1.2   Nov 03 1998 14:57:58   DMUM
// Fixes Tracker ticket # 5299 for TA2000 NT rel 3.2 and 3.3
//
//    Rev 1.1.1.1   Oct 01 1998 11:51:22   DMUM
//
//
//    Rev 1.5   Oct 01 1998 11:35:42   DMUM
// Added expandContainerItemDown()
//
//    Rev 1.4   Sep 21 1998 08:51:30   DMUM
// Added function.
//
//    Rev 1.3   Sep 11 1998 11:58:50   DMUM
// Added getCaseWorkTypeList and
// getTransWorkTypeList
//
//    Rev 1.2   Aug 27 1998 18:14:56   DMUM
// Made change on the recommendation of David Cloud
//
//    Rev 1.1   Aug 21 1998 11:37:20   DMUM
// Added trace message
//
//    Rev 1.0   29 Jul 1998 20:28:04   DT14596
// DLMG New Archives for TA2000NTDT
//
//    Rev 1.13   Jul 23 1998 07:35:30   dmum
// Clean up
//
//    Rev 1.12   May 13 1998 14:19:34   dmum
// Made changes affecting LOB Groups.
// Fixes tickets 2850 through 2857
//
//    Rev 1.11   Mar 17 1998 14:20:58   dmum
// Fixed problem with onlucking AWD objects
//
//    Rev 1.10   Mar 16 1998 15:45:50   dmum
// Added isItemInContainer method
//
//    Rev 1.9   Feb 23 1998 13:09:44   dmum
// Forgot to delete a line no longer needed
//
//    Rev 1.8   Feb 23 1998 11:09:36   dmum
// Uses more SOM interface and less AWD APIs
//
//    Rev 1.7   Jan 29 1998 16:46:58   dmum
// Now grabs LOB items from Indexed and Grouped LOB items
//
//    Rev 1.6   Jan 19 1998 13:45:38   dmum
// Added methods: insertItemInContainer & hasCaseForParent
//
//    Rev 1.5   Dec 30 1997 12:25:36   dmum
// Added methods
//
//    Rev 1.4   Dec 16 1997 11:21:12   dmum
// No longer interfaces with AWD32.EXE
//
// Now uses AWD 2.3.0b directly through SOM and APIs
//
//    Rev 1.3   10 Nov 1997 15:20:04   dmum
// Added redundancy guards and export/import guards
//
//    Rev 1.2   01 Oct 1997 13:11:04   dmum
// Accomodated changes in the OLE server.
//
//    Rev 1.1   20 Sep 1997 11:53:52   dmum
// Added exported functions
//
//    Rev 1.0   03 Sep 1997 14:21:20   dmum
//
//

