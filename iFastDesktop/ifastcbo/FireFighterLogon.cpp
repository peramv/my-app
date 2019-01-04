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
//    Copyright 2002 by International Financial.
//
//
//******************************************************************************
//
// ^FILE   : FireFighterLogon.cpp
// ^AUTHOR : May Lin
// ^DATE   : Feb. 2, 2003
//
// ^CLASS    : FireFighterLogon 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "FireFighterLogon.hpp"
#include <ifastdataimpl\dse_dstc0276_vw.hpp>
#include <ifastdataimpl\dse_dstc0276_req.hpp>

#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "dstcommonfunction.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest FIRE_FIGHTER_LOGON;
}

namespace  
{
   const I_CHAR * const CLASSNAME = I_( "FireFighterLogon" );  
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,     Group Flags 
   { ifds::UpdateStatus,            BFCBO::NONE,     0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//*********************************************************************************
FireFighterLogon::FireFighterLogon( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );

}


//*********************************************************************************
FireFighterLogon::~FireFighterLogon()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//*********************************************************************************
SEVERITY FireFighterLogon::init(
								const DString & dstCompanyId,
								const DString& dstrFFID,
								const DString& dstrPassword, 
								const DString& dstrPTSNum,
								const DString& dstrDesc1,
								const DString& dstrDesc2,
								const DString& dstrDesc3,
								const DString& dstrDesc4,
								const DString& dstrTrack,
								const DString& dstrPageName)

{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init(DString&, DString&, DString&, DString&..." ) );
	DString mgmtCoIdOut;
	BFData RequestData(ifds::DSTC0276_REQ );
	RequestData.setElementValue( ifds::Track, dstrTrack );
	RequestData.setElementValue( ifds::Activity, dstrPageName ); 
	RequestData.setElementValue( ifds::CompanyId, dstCompanyId ); 
	RequestData.setElementValue( ifds::FireFighterId, dstrFFID ); 
	RequestData.setElementValue( ifds::FireFighterPassword, dstrPassword ); 
	RequestData.setElementValue( ifds::PTSNumber, dstrPTSNum ); 
	RequestData.setElementValue( ifds::Description1, dstrDesc1 );
	RequestData.setElementValue( ifds::Description2, dstrDesc2 ); 
	RequestData.setElementValue( ifds::Description3, dstrDesc3 );
	RequestData.setElementValue( ifds::Description4, dstrDesc4 ); 


	BFData *responseData = new BFData(ifds::DSTC0276_VW);
	DSTCRequestor requestor(getSecurity(), true, false );

	ReceiveData(DSTC_REQUEST::FIRE_FIGHTER_LOGON, RequestData, *responseData, requestor);
	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FireFighterLogon.cpp-arc  $
// 
//    Rev 1.4   Jan 08 2010 11:57:44   yingz
// delay view 276 for inc#1936007
// 
//    Rev 1.3   Aug 31 2005 16:03:20   ZHANGCEL
// PET1235 - FN02 -- Add two fields Description3 and Description4
// 
//    Rev 1.2   Nov 14 2004 14:41:02   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.1   Dec 11 2003 11:43:48   linmay
// modified init( )
// 
//    Rev 1.0   Dec 09 2003 09:06:20   linmay
// Initial Revision
// 
 */