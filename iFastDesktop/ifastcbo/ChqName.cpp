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
// ^FILE   : ChqName.cpp
// ^AUTHOR : 
// ^DATE   : 30/06/2004
//
// ^CLASS    : ChqName
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "chqname.hpp"
#include <ifastdataimpl\dse_dstc0297_vw.hpp>
#include <ifastdataimpl\dse_dstc0297_req.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest CHQNAMEINQUIRY;
}

namespace
{
   const I_CHAR * const CLASSNAME = I_( "ChqName" );
   const I_CHAR * const YES = I_( "Y" );
}


//****************************************************************************
ChqName::ChqName( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
}

//****************************************************************************
ChqName::~ChqName()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}     

//******************************************************************************
SEVERITY ChqName::init( const DString& dstrAccountNum,
                          const DString& dstrTrack,
                          const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   BFData queryData(ifds::DSTC0297_REQ);

   DString mgmtCoIdOut;
   queryData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   queryData.setElementValue( ifds::Track, dstrTrack );
   queryData.setElementValue( ifds::Activity, dstrPageName );
   queryData.setElementValue( ifds::AccountNum, dstrAccountNum ); 

   ReceiveData( DSTC_REQUEST::CHQNAMEINQUIRY, queryData, ifds::DSTC0297_VW, DSTCRequestor( getSecurity() ) );

   return(GETCURRENTHIGHESTSEVERITY());
}



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ChqName.cpp-arc  $
// 
//    Rev 1.2   Nov 14 2004 14:29:38   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.1   Jul 02 2004 14:45:36   AGUILAAM
// PTS 10030921 - assign name1 and name2 from new view 297 on settlement cheque
// 
//    Rev 1.0   Jul 02 2004 12:05:44   AGUILAAM
// Initial Revision
// 
*/
