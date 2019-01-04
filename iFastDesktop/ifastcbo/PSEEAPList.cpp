//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confIdential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2009 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : PSEEAPList.cpp
// ^AUTHOR : 
// ^DATE   : April, 2010
//
// ^CLASS    : PSEEAPList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"

#include <ifastdataimpl\dse_dstc0404_req.hpp>
#include <ifastdataimpl\dse_dstc0404_vw.hpp>

#include "pseeaplist.hpp"

namespace DSTC_REQUEST
{
    extern CLASS_IMPORT const DSTCRequest PSE_EAP_INQUIRY;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME	= I_( "PSEEAPList" );
}

//******************************************************************************
PSEEAPList::PSEEAPList( BFAbstractCBO &parent )
: MFCanBFCbo(parent)
{
	TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
	setObjectAsList ();
}

//******************************************************************************
PSEEAPList::~PSEEAPList(void)
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//********************************************************************************
SEVERITY PSEEAPList::init( const DString& transId,
                           const DString& dstrTrack,
                           const DString& dstrPageName)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

	DString mgmtCoIdOut;
	BFData requestData (ifds::DSTC0404_REQ);

	requestData.setElementValue (ifds::TransId, transId);
   requestData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
	requestData.setElementValue (ifds::Track, dstrTrack);
	requestData.setElementValue (ifds::Activity, dstrPageName);

	ReceiveData (DSTC_REQUEST::PSE_EAP_INQUIRY, requestData, ifds::DSTC0404_VW, DSTCRequestor (getSecurity(), true));

	return GETCURRENTHIGHESTSEVERITY ();
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/** $Log:   Y:/VCS/BF iFAST/ifastcbo/PSEEAPList.cpp-arc  $
// 
//    Rev 1.2   Jun 11 2010 06:29:36   kitticha
// PETP0165541 FN02 IN#2123752 - PSE Fix. Remove previous rev logic.
// 
//    Rev 1.1   Jun 04 2010 03:08:22   kitticha
// IN#2123752 - Additional logic and validation for PSE.
// 
//    Rev 1.0   Apr 21 2010 17:22:12   popescu
// Initial revision.
 **/
