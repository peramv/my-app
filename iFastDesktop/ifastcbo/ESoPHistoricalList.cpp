//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1999 by DST Systems, Inc.
//
//*****************************************************************************
//
// ^FILE   : ESoPHistoricalList.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : September 19, 2001
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : ESoPHistoricalList
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include "esophistoricallist.hpp"
#include <ifastdataimpl\dse_dstc0178_req.hpp>
#include <ifastdataimpl\dse_dstc0178_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ESOP_HISTORICAL_ACCOUNT;
}

namespace
{
   const I_CHAR * const CLASSNAME = I_( "ESoPHistoricalList" );
}

ESoPHistoricalList::ESoPHistoricalList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}

ESoPHistoricalList::~ESoPHistoricalList()
{
   TRACE_DESTRUCTOR( CLASSNAME );

}
//*******************************************************************************************
SEVERITY ESoPHistoricalList::init( const DString& dstrTrack, const DString& dstrPageName )

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );   

   DString mgmtCoIdOut;
   BFData queryData(ifds::DSTC0178_REQ);
   DString accountNum;
   getParent()->getParent()->getField( ifds::AccountNum, accountNum, BF::HOST );//we know it can't be a new account
   queryData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   queryData.setElementValue( ifds::AccountNum, accountNum ); 
   queryData.setElementValue( ifds::Track, dstrTrack );
   queryData.setElementValue( ifds::Activity, dstrPageName );

   ReceiveData( DSTC_REQUEST::ESOP_HISTORICAL_ACCOUNT, queryData, ifds::DSTC0178_VW, DSTCRequestor( getSecurity() ) );


   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ESoPHistoricalList.cpp-arc  $
// 
//    Rev 1.6   Nov 14 2004 14:36:50   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.5   Mar 21 2003 18:08:36   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.4   Oct 09 2002 23:54:28   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.3   Aug 29 2002 12:55:46   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.2   22 May 2002 18:28:34   PURDYECH
// BFData Implementation
// 
//    Rev 1.1   02 Oct 2001 11:47:18   KOVACSRO
// Modified init.
// 
//    Rev 1.0   24 Sep 2001 12:23:18   KOVACSRO
// Initial revision.
 * 
 
*/