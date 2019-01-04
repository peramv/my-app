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
//    Copyright 2006 by International Financial Data Services
//
//*****************************************************************************
//
//    ^FILE   : AgencyNegComm.cpp
//    ^AUTHOR : Monica Vadeanu
//    ^DATE   : November, 2004
//    Copyright 2004 by International Financial Data Services
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : AgencyNegComm
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"

#include "AgencyNegComm.hpp"

#include <ifastdataimpl\dse_dstc0370_req.hpp>
#include <ifastdataimpl\dse_dstc0370_vw.hpp>

// Constants
namespace 
{
   const I_CHAR * CLASSNAME = I_("AgencyNegComm");
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest AGENCY_NEGATIVE_COMMISSION;
}

//******************************************************************************
AgencyNegComm::AgencyNegComm(BFAbstractCBO &parent) 
: MFCanBFCbo(parent)
{
   TRACE_CONSTRUCTOR(CLASSNAME , NULL_STRING);   
}

//******************************************************************************
AgencyNegComm::~AgencyNegComm()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
SEVERITY AgencyNegComm::init( const DString &dstrPayInstructRID,							  
							  const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));
   
   _pRequestData = new BFData(ifds::DSTC0370_REQ);

   DString dstrMgmtCoIdOut;

   _pRequestData->setElementValue(ifds::PayInstructRID, dstrPayInstructRID );      
   _pRequestData->setElementValue(ifds::CompanyId,      getMgmtCoId( dstrMgmtCoIdOut ) );
   _pRequestData->setElementValue(ifds::Track,          I_( "N" ) );   

   ReceiveData( DSTC_REQUEST::AGENCY_NEGATIVE_COMMISSION, 
	            *_pRequestData, 
                ifds::DSTC0370_VW, 
				DSTCRequestor( getSecurity(), 
				false ) );   

   return GETCURRENTHIGHESTSEVERITY();            
}

//******************************************************************************
bool AgencyNegComm::hasNegativeCommission( const BFDataGroupId &idDataGroup )
{
    DString dstrHasNegativeCommission;
	getField( ifds::HasNegativeComm, dstrHasNegativeCommission, idDataGroup );	
	return ( dstrHasNegativeCommission.stripAll().upperCase() == I_( "Y" ) );
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/AgencyNegComm.cpp-arc  $
// 
//    Rev 1.1   Jun 07 2006 13:27:24   porteanm
// PET2132 FN03 - Edit check for Negative Commission.
// 
//    Rev 1.0   May 31 2006 17:52:42   porteanm
// Initial revision.
// 


