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
// ^FILE   : RoadEncorr.cpp
// ^AUTHOR : Darrin Donahue
// ^DATE   : 8-97
//
// ----------------------------------------------------------
//
// ^CLASS    : RoadEncorr
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for Encorr stuff
//
//
//******************************************************************************
#include "stdafx.h"

#include "roadencorr.h"
#include <bfsessn\bfcpsessiontags.h>
#include <bfawdi\bfawdinterface.hpp>
#include <stringfunctions.hpp>
#include <uibase\oleglobal.hpp>

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace AwdTags
{
   const I_CHAR *CRDA      = I_( "CRDA" );
   const I_CHAR *RECO      = I_( "RECO" );
   const I_CHAR *CRNO      = I_( "CRNO" );
   const I_CHAR *UNIT      = I_( "UNIT" );
}


/////////////////////////////////////////////////////////////////////////////
// RoadEncorr

IMPLEMENT_DYNCREATE(RoadEncorr, CCmdTarget)

RoadEncorr::RoadEncorr()
: m_processing( false )
{
   EnableAutomation();
}

RoadEncorr::~RoadEncorr()
{
}


void RoadEncorr::OnFinalRelease()
{
   // When the last reference for an automation object is released
   // OnFinalRelease is called.  The base class will automatically
   // deletes the object.  Add additional cleanup required for your
   // object before calling the base class.

   CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(RoadEncorr, CCmdTarget)
//{{AFX_MSG_MAP(RoadEncorr)
// NOTE - the ClassWizard will add and remove mapping macros here.
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(RoadEncorr, CCmdTarget)
//{{AFX_DISPATCH_MAP(RoadEncorr)
DISP_FUNCTION(RoadEncorr, "CreateTime", CreateTime, VT_BSTR, VTS_NONE)
DISP_FUNCTION(RoadEncorr, "RecordCode", RecordCode, VT_BSTR, VTS_NONE)
DISP_FUNCTION(RoadEncorr, "CreateNode", CreateNode, VT_BSTR, VTS_NONE)
DISP_FUNCTION(RoadEncorr, "DataIDI", DataIDI, VT_BSTR, VTS_NONE)
DISP_FUNCTION(RoadEncorr, "BusinessArea", BusinessArea, VT_BSTR, VTS_NONE)
DISP_FUNCTION(RoadEncorr, "Update", Update, VT_EMPTY, VTS_BSTR)
DISP_FUNCTION(RoadEncorr, "Complete", Complete, VT_EMPTY, VTS_BSTR)
DISP_FUNCTION(RoadEncorr, "Pass", Pass, VT_EMPTY, VTS_BSTR)
DISP_FUNCTION(RoadEncorr, "Fail", Fail, VT_EMPTY, VTS_BSTR)
DISP_FUNCTION(RoadEncorr, "Save", Save, VT_EMPTY, VTS_NONE)
DISP_FUNCTION(RoadEncorr, "Abort", Abort, VT_EMPTY, VTS_NONE)
DISP_FUNCTION(RoadEncorr, "Cancel", Cancel, VT_EMPTY, VTS_NONE)
//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IRoadEncorr to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the
//  dispinterface in the .ODL file.

// {7C0841B3-0CA1-11D1-BA74-0004ACB678B6}
static const IID IID_IRoadEncorr =
{ 0x7c0841b3, 0xca1, 0x11d1, { 0xba, 0x74, 0x0, 0x4, 0xac, 0xb6, 0x78, 0xb6}};

BEGIN_INTERFACE_MAP(RoadEncorr, CCmdTarget)
INTERFACE_PART(RoadEncorr, IID_IRoadEncorr, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RoadEncorr message handlers

BSTR RoadEncorr::CreateTime()
{
   return(m_createDateTime.AllocSysString());
}

BSTR RoadEncorr::RecordCode()
{
   return(m_recordCode.AllocSysString());
}

BSTR RoadEncorr::CreateNode()
{
   return(m_createNode.AllocSysString());
}

BSTR RoadEncorr::BusinessArea()
{
   return(m_businessArea.AllocSysString());
}

BSTR RoadEncorr::DataIDI()
{
   return(m_csIDI.AllocSysString());
}

void RoadEncorr::Update( LPCTSTR szIdi )
{
   m_processing = FALSE;
   return;
}

void RoadEncorr::Complete( LPCTSTR szIdi )
{
   // This method is called by EnCorr when the letter is supposed to go
   // to Quality
   m_processing = FALSE;
   updateAwd( szIdi, false );
   return;
}

void RoadEncorr::Pass( LPCTSTR szIdi )
{
   // This method is called by EnCorr when the letter has been printed
   // (and an AWD image was created)
   m_processing = FALSE;
   updateAwd( szIdi, true );
   return;
}

void RoadEncorr::Fail( LPCTSTR szIdi )
{
   m_processing = FALSE;
   return;
}

void RoadEncorr::Save()
{
   m_processing = FALSE;
   return;
}

void RoadEncorr::Abort()
{
   m_processing = FALSE;
   return;
}

void RoadEncorr::Cancel()
{
   m_processing = FALSE;
   return;
}

//*****************************************************************************
//          Public Methods
//*****************************************************************************

void RoadEncorr::end()
{
   delete this;
}

void RoadEncorr::setData( BFData *pRoadData )
{
   TRACE_METHOD( I_( "RoadEncorr" ), I_( "setData( BFData * )" ))

   DString strIDI;

   pRoadData->getAllValues( strIDI );
   m_csIDI = strIDI.c_str();
}

void RoadEncorr::setAwdData( const BFData *pData )
{
   // if we have the createdatetime, then we should have all four
   if( pData->exists( AwdTags::CRDA ) )
   {
      m_businessArea = pData->getElementValue( AwdTags::UNIT ).c_str();
      m_createDateTime = pData->getElementValue( AwdTags::CRDA ).c_str();
      m_recordCode = pData->getElementValue( AwdTags::RECO ).c_str();
      m_createNode = pData->getElementValue( AwdTags::CRNO ).c_str();
      m_completedStatus = pData->getElementValue( SessionTags::PSTATUS );
   }
}

//*****************************************************************************
//          Private Methods
//*****************************************************************************

void RoadEncorr::updateAwd( LPCTSTR szIdi, bool completed )
{
   if( ! m_createDateTime.IsEmpty() )
   {
      bool hasValue = false;
      int index = 0;
      int count = 0;
      int position = 0;

      DString tag;
      DString value;
      DString pair;

      DString strIdi( szIdi );
      DString crda = LPCTSTR( m_createDateTime );
      DString reco = LPCTSTR( m_recordCode );
      DString crno = LPCTSTR( m_createNode );

      BFAwdData awdData;
      BFAwdInterface awd;

      BFDataObjMap& dictionary = awd.getAwdFieldList();
      awdData.setKey( awd.newAwdKey( crda, reco, crno ) );

      while( ( position = strIdi.find( ';', index ) ) != DString::npos )
      {
         count = position - index;
         pair = strIdi.substr( index, count );
         index = position + 1;

         // Make sure there is an '='
         position = pair.find( '=' );

         if( DString::npos != position )
         {
            tag = pair.substr( 0, position );

            if( dictionary.end() != dictionary.find( tag ) )
            {
               value = pair.substr( position + 1 );
               strip( value );

               // Make sure the value is not empty
               if( ! value.empty() )
               {
                  awdData.setLobData( tag, value );
                  hasValue = true;
               }
            }
         }
      }

      if( completed )
      {
         awdData.setStat( m_completedStatus );
      }

      if( hasValue )
      {
         awd.updateAwdObject( awdData );
      }

      OleGlobal *pOleGlobal = OleGlobal::getInstance();
      pOleGlobal->postMessageToSearchScreen( UM_EXPANDCASE, 0L, 0L );
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   D:/scc/ifds/ifast/archives/ifastgui/RoadEncorr.cpp-arc  $
 * 
 *    Rev 1.3   Oct 09 2002 23:56:12   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.2   May 28 2002 12:19:52   PURDYECH
 * BFData Implementation - Phase II
 * 
 *    Rev 1.1   22 May 2002 19:16:24   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.0   Feb 15 2000 11:01:24   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.1   Jul 08 1999 10:05:52   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
