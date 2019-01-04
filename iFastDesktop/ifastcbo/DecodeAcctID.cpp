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
// ^FILE   : DecodeAcctID.cpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 07/10/2005
//
// ^CLASS    : DecodeAcctID
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "DecodeAcctID.hpp"
#include <ifastdataimpl\dse_dstc0356_vw.hpp>
#include <ifastdataimpl\dse_dstc0356_req.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest DECODE_ACCTID;
}

namespace
{
   const I_CHAR * const CLASSNAME = I_( "DecodeAcctID" );
   const I_CHAR * const YES = I_( "Y" );
}


//****************************************************************************
DecodeAcctID::DecodeAcctID( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
}

//****************************************************************************
DecodeAcctID::~DecodeAcctID()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}     

//******************************************************************************
SEVERITY DecodeAcctID::init( const DString& dstrAccountID,
                          const DString& dstrTrack,
                          const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   BFData queryData(ifds::DSTC0356_REQ);

   DString mgmtCoIdOut;
   queryData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   queryData.setElementValue( ifds::Track, dstrTrack );
   queryData.setElementValue( ifds::Activity, dstrPageName );
   queryData.setElementValue( ifds::AccountID, dstrAccountID ); 

   ReceiveData( DSTC_REQUEST::DECODE_ACCTID, queryData, ifds::DSTC0356_VW, DSTCRequestor( getSecurity() ) );

   return(GETCURRENTHIGHESTSEVERITY());
}



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DecodeAcctID.cpp-arc  $
// 
//    Rev 1.0   Oct 24 2005 17:35:48   ZHANGCEL
// Initial revision.
//   
// 
*/
