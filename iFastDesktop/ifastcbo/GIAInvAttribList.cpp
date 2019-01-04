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
//    Copyright 2011 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : GIAInvAttrib.cpp
// ^AUTHOR : Panatchakorn Pokawinkoon
// ^DATE   : Oct 26, 2000
//
// ^CLASS    : GIAInvAttrib
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "giainvattriblist.hpp"


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest GIA_ATTRIBS_INQUIRY;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "GIAInvAttribList" );
}


//****************************************************************************
GIAInvAttribList::GIAInvAttribList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   setObjectAsList();
}

//****************************************************************************
GIAInvAttribList::~GIAInvAttribList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//********************************************************************************
SEVERITY GIAInvAttribList::init( const DString &fundCode,
                                 const DString &classCode,
                                 const DString &tradeDate,
                                 const DString &dstrTrack,
                                 const DString &dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   DString mgmtCoIdOut;	
	BFData requestData (ifds::DSTC0420_REQ);
	
	requestData.setElementValue (ifds::FundCode, fundCode);
	requestData.setElementValue (ifds::ClassCode, classCode);
	requestData.setElementValue (ifds::TradeDate, tradeDate);
	requestData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
	requestData.setElementValue (ifds::Track, dstrTrack);
	requestData.setElementValue (ifds::Activity, dstrPageName);
	
	ReceiveData (DSTC_REQUEST::GIA_ATTRIBS_INQUIRY, requestData, ifds::DSTC0420_VW, DSTCRequestor (getSecurity(), true));

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/** $Log:   Y:/VCS/BF iFAST/ifastcbo/GIAInvAttribList.cpp-arc  $
// 
//    Rev 1.2   Nov 30 2011 00:16:52   dchatcha
// P0186477/FN03 - GIA - Purchase
// 
//    Rev 1.1   Nov 27 2011 19:40:30   popescu
// INA Commission Work
// 
// Initial revision.
 **/
