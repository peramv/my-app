////******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2000 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : RESPInfo.cpp
// ^AUTHOR : Dan Petolescu
// ^DATE   : January 12, 2000
//
// ^CLASS    : RESPInfo
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "respinfo.hpp"
#include "respinfobeneficiary.hpp"
#include <ifastdataimpl\dse_dstc0066_vw.hpp>
#include <ifastdataimpl\dse_dstc0066_req.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest RESPINFO;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "RESPInfo" );
}

namespace TRID
{
   extern const I_CHAR* RESPINFO;
}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
}

//****************************************************************************
RESPInfo::RESPInfo( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList();
}

//****************************************************************************
RESPInfo::~RESPInfo()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//****************************************************************************
SEVERITY RESPInfo::initNew( DString& accountNum )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initNew( int, DString )" ) );

   _accountNum = accountNum;

   return(GETCURRENTHIGHESTSEVERITY( ));
}

//****************************************************************************
SEVERITY RESPInfo::init( DString& accountNum,
                         const DString& dstrTrack,
                         const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init( int, DString )" ) );

   _accountNum = accountNum;

   BFData queryData(ifds::DSTC0066_REQ);

   DString mgmtCoIdOut;
   queryData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   queryData.setElementValue( ifds::AccountNum, _accountNum ); 
   queryData.setElementValue( ifds::Track, dstrTrack );
   queryData.setElementValue( ifds::Activity, dstrPageName );

   ReceiveData( DSTC_REQUEST::RESPINFO, queryData, ifds::DSTC0066_VW, DSTCRequestor( getSecurity() ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY RESPInfo::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );
   pObjOut = new RESPInfoBeneficiary( *this );
   ( ( RESPInfoBeneficiary* ) ( pObjOut ) )->init( const_cast<BFData&>(data) );

   return(GETCURRENTHIGHESTSEVERITY());
}

/******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RESPInfo.cpp-arc  $
 * 
 *    Rev 1.9   Nov 14 2004 14:52:20   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.8   Mar 21 2003 18:22:00   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.7   Oct 09 2002 23:54:52   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.6   Aug 29 2002 12:56:28   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.5   22 May 2002 18:29:42   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.4   03 May 2001 14:07:00   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.3   Jan 18 2001 16:05:44   YINGBAOL
 * add eTracker
 * 
 *    Rev 1.2   Dec 17 2000 20:24:18   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.1   Mar 22 2000 09:02:46   PETOLESC
 * Added Tax Rates and RESP dialogs.
// 
//    Rev 1.1   Feb 16 2000 10:18:00   PETOLESC
// This is the file formerly called InfoGlobalList.
 *
 * 
 *
 */