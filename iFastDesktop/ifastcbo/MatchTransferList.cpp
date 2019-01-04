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
//    Copyright 2000 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : GuaranteeInfoList.cpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 01/18/2000
//
// ^CLASS    : GuaranteeInfoList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include <ifastdataimpl\dse_dstc0022_req.hpp>
#include <ifastdataimpl\dse_dstc0022_vw.hpp>
#include "matchtransferlist.hpp"
#include "matchtransferdetails.hpp"
#include "splitcommissionlist.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest TRANSACTION_DETAILS ;
}

namespace
{
   // Trace literals
   const I_CHAR * CLASSNAME = I_( "MatchTransferList" );
//   const I_CHAR * CASH = I_( "CASH" );
}

namespace CND
{
   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
}

// Constructors
//
// *********************************************************************************

MatchTransferList::MatchTransferList( BFAbstractCBO &parent ) : 
MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}


// *********************************************************************************

MatchTransferList::~MatchTransferList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );

}

//******************************************************************************
SEVERITY MatchTransferList::init( const DString& TransId,
                                  const DString& dstrTrack,
                                  const DString& dstrPageName   )

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );      

   BFData queryData(ifds::DSTC0022_REQ);
   BFData *response = new BFData(ifds::DSTC0022_VW);

   DString mgmtCoIdOut;
   queryData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   queryData.setElementValue( ifds::TransId, TransId );
   queryData.setElementValue( ifds::Track, dstrTrack );
   queryData.setElementValue( ifds::Activity, dstrPageName );

   DSTCRequestor requestor( getSecurity(), true, false );


   if( BFDataBroker::getInstance()->receive( DSTC_REQUEST::TRANSACTION_DETAILS, queryData, *response, requestor )  > WARNING )
   {
      delete response;
      response = NULL;
   }
   else
   {
      attachDataObject( *response, true, true );
      init2( *response );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}


//------------------------------------------------------------------------------------
SEVERITY MatchTransferList::init2(const BFData& recData ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init2" ) );

   MatchTransferDetails* _pMatchTransferDetails = new MatchTransferDetails( *this );
   _pMatchTransferDetails->init( recData);
   DString strKey;
   strKey = NULL_STRING;
   getStrKey( strKey );
   setObject( _pMatchTransferDetails, strKey, OBJ_ACTIVITY_NONE, BF::HOST );
   return(GETCURRENTHIGHESTSEVERITY());
}

//***************************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/MatchTransferList.cpp-arc  $
// 
//    Rev 1.5   Nov 14 2004 14:49:32   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.4   Mar 21 2003 18:18:14   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.3   Oct 09 2002 23:54:44   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.2   Aug 29 2002 12:56:08   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.1   22 May 2002 18:28:58   PURDYECH
// BFData Implementation
// 
//    Rev 1.0   Aug 16 2001 13:43:38   ZHANGCEL
// Initial revision.
 * 
 */
