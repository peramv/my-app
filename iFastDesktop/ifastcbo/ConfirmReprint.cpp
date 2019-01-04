//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2005 by International Financial Data Services
//
//*****************************************************************************
//
//    ^FILE   : ConfirmReprint.cpp
//    ^AUTHOR : Monica Porteanu
//    ^DATE   : May, 2005
//    Copyright 2005 by International Financial Data Services
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : ConfirmReprint
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"

#include "ConfirmReprint.hpp"
#include "MFAccount.hpp"


// Constants
namespace 
{
   const I_CHAR * CLASSNAME = I_("ConfirmReprint");
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest CONFIRM_REPRINT_INQUIRY;
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;   
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
    //  Field DD Id,          State Flags, Group Flags 

	// Confirm Reprint fields
    {ifds::AccountNum,        BFCBO::NONE, 0 }, 			
};


static const int NUM_FIELDS = sizeof(classFieldInfo) / sizeof(BFCBO::CLASS_FIELD_INFO);
//******************************************************************************
ConfirmReprint::ConfirmReprint(BFAbstractCBO &parent) 
: MFCanBFCbo(parent)
, _pRequestData ( NULL )
, _pResponse ( NULL )
{
   TRACE_CONSTRUCTOR(CLASSNAME , NULL_STRING);

   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL);     

}

//******************************************************************************
ConfirmReprint::~ConfirmReprint()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
SEVERITY ConfirmReprint::init( const DString &dstrTransId, 
							   const DString &dstrAccountNum,
							   const BFDataGroupId &idDataGroup,
							   const DString& dstrTrack, 
				               const DString &dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));
      	  	
   setTransId( dstrTransId );
   setAccountNum( dstrAccountNum );

   _pRequestData = new BFData ( ifds::DSTC0345_REQ );
   _pResponse = new BFData (ifds::DSTC0345_VW);

   DString mgmtCoIdOut;

   _pRequestData->setElementValue (ifds::TransId,   _dstrTransId );   
   _pRequestData->setElementValue (ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   _pRequestData->setElementValue (ifds::Track,     dstrTrack );
   _pRequestData->setElementValue (ifds::Activity,  dstrPageName );    

   if ( BFDataBroker::getInstance ()->receive( DSTC_REQUEST::CONFIRM_REPRINT_INQUIRY, 
 											   *_pRequestData, 
											   *_pResponse, 
											   DSTCRequestor (getSecurity(), true, true ) ) <= WARNING &&
		NULL != _pResponse )
   {          
       attachDataObject( *_pResponse, true, false );	  	   

	   setExistingRecord( idDataGroup );	   
	   setRunMode( I_( "M" ) );
   }   
   else
   {
		delete _pResponse;
      _pResponse = NULL;   
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ConfirmReprint::initNew ( const DString &dstrTransId, 
								   const DString &dstrAccountNum,
								   const BFDataGroupId &idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("initNew"));

	setTransId( dstrTransId );
    setAccountNum( dstrAccountNum );
	setRunMode( I_( "A" ) );

	setNewRecord( idDataGroup );

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void ConfirmReprint::doInitWithDefaultValues( const BFDataGroupId &idDataGroup )
{   		
}

//******************************************************************************
void ConfirmReprint::reprintReset(const BFDataGroupId &idDataGroup)
{   
}

//******************************************************************************
void ConfirmReprint::doReset (const BFDataGroupId &idDataGroup)
{
	reprintReset( idDataGroup );
}

//******************************************************************************
SEVERITY ConfirmReprint::doApplyRelatedChanges( const BFFieldId &idField, 
	 										       const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));
   
   
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ConfirmReprint::doValidateField( const BFFieldId &idField, 
										  const DString &strValue, 
										  const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField") );
   	

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ConfirmReprint::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );   

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY ConfirmReprint::setExistingRecord( const BFDataGroupId &idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("setExistingRecord") );


	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ConfirmReprint::setNewRecord( const BFDataGroupId &idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("setExistingRecord") );


	return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/ConfirmReprint.cpp-arc  $
// 
//    Rev 1.2   May 31 2005 15:53:42   porteanm
// PET OPC Confirm Reprint - Commit and Reset.
// 
//    Rev 1.1   May 25 2005 15:00:20   porteanm
// PET OPC Confirm Reprint - Commit and Reset.
// 
//    Rev 1.0   May 24 2005 12:33:08   porteanm
// Initial revision.
// 

