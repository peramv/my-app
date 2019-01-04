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
//    Copyright 1999 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : MgmtCoOptions2.cpp
// ^AUTHOR : 
// ^DATE   : 10/14/1999
//
// ^CLASS    : MgmtCoOptions2
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "mgmtcooptions2.hpp"
#include <ifastdataimpl\dse_dstc0149_vw.hpp>
#include <ifastdataimpl\dse_dstc0149_req.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest MGMT_CO_OPTIONS_NEXT;
}

namespace
{
   const I_CHAR * const CLASSNAME   = I_( "MgmtCoOptions2" );
   const I_CHAR * const YES         = I_( "Y" );
   const I_CHAR * const NO          = I_( "N" );
   const I_CHAR * const CANADA      = I_( "Canada");
   const I_CHAR * const JAPAN       = I_( "Japan" );
   const I_CHAR * const COMMA       = I_( "," );
}

//******************************************************************************
MgmtCoOptions2::MgmtCoOptions2( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   setVersionable( false );
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
}

//******************************************************************************
MgmtCoOptions2::~MgmtCoOptions2()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY MgmtCoOptions2::init( const DString& dstrTrack, const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   BFData queryData(ifds::DSTC0149_REQ);

   DString mgmtCoIdOut;
   queryData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   queryData.setElementValue( ifds::Track, dstrTrack );
   queryData.setElementValue( ifds::Activity, dstrPageName );

   AsyncReceiveData (DSTC_REQUEST::MGMT_CO_OPTIONS_NEXT, 
                     queryData, 
                     ifds::DSTC0149_VW, 
                     DSTCRequestor (getSecurity()));

   return GETCURRENTHIGHESTSEVERITY();

}

//******************************************************************************
SEVERITY MgmtCoOptions2::init( const DString& dstrMgmgCo, const DString& dstrTrack, const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   BFData queryData(ifds::DSTC0149_REQ);

   DString mgmtCoIdOut;
   queryData.setElementValue( ifds::CompanyId, dstrMgmgCo);
   queryData.setElementValue( ifds::Track, dstrTrack );
   queryData.setElementValue( ifds::Activity, dstrPageName );

   AsyncReceiveData (DSTC_REQUEST::MGMT_CO_OPTIONS_NEXT, 
                     queryData, 
                     ifds::DSTC0149_VW, 
                     DSTCRequestor (getSecurity()));

   return GETCURRENTHIGHESTSEVERITY();

}

//******************************************************************************
SEVERITY MgmtCoOptions2::initSynch( const DString& dstrMgmgCo, const DString& dstrTrack, const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   BFData queryData(ifds::DSTC0149_REQ);

   DString mgmtCoIdOut;
   queryData.setElementValue( ifds::CompanyId, dstrMgmgCo);
   queryData.setElementValue( ifds::Track, dstrTrack );
   queryData.setElementValue( ifds::Activity, dstrPageName );

   ReceiveData (DSTC_REQUEST::MGMT_CO_OPTIONS_NEXT, 
                     queryData, 
                     ifds::DSTC0149_VW, 
                     DSTCRequestor (getSecurity()));

   return GETCURRENTHIGHESTSEVERITY();

}

//******************************************************************************


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/MgmtCoOptions2.cpp-arc  $
// 
//    Rev 1.11   24 Jul 2008 12:01:08   popescu
// Incident - 1190617 - set all the data init calls to be asynch
// 
//    Rev 1.10   Dec 10 2004 14:53:24   hernando
// PET1117 - Recovered version feature.
// 
//    Rev 1.9   Nov 24 2004 10:18:44   yingbaol
// PET1117:temperary take out version features
// 
//    Rev 1.8   Nov 18 2004 13:28:22   YINGBAOL
// PET1117: Perfermance Tunning
// 
//    Rev 1.7   Nov 14 2004 14:50:16   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.6   Mar 21 2003 18:18:56   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.5   Oct 09 2002 23:54:46   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.4   Aug 29 2002 12:56:20   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.3   22 May 2002 18:29:34   PURDYECH
// BFData Implementation
// 
//    Rev 1.2   03 May 2001 14:06:52   SMITHDAV
// Session management restructuring.
// 
//    Rev 1.1   Mar 22 2001 14:17:10   FENGYONG
// change dstrequest name
// 
//    Rev 1.0   Mar 21 2001 12:18:42   FENGYONG
// Initial revision.
 * 
*/