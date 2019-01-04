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
//    ^FILE   : OPCOnlineConfirmReprint.cpp
//    ^AUTHOR : Monica Porteanu
//    ^DATE   : May, 2005
//    Copyright 2005 by International Financial Data Services
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : OPCOnlineConfirmReprint
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"

#include "OPCOnlineConfirmReprint.hpp"

#include <dataimpl\dse_dstc0149_vw.hpp>                // System Configuration 
//#include <dataimpl\dse_dstc0345_req.hpp>               // OPC Confirm Reprint Inquiry
//#include <dataimpl\dse_dstc0345_vwrepeat_record.hpp>   // OPC Confirm Reprint Inquiry


// Constants
namespace 
{
   const I_CHAR * CLASSNAME = I_("OPCOnlineConfirmReprint");
}


/*
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
    //  Field DD Id,          State Flags,     Group Flags 
    {ifds::,         BFCBO::REQUIRED, 0 }, 	
};
*/

//static const int NUM_FIELDS = sizeof(classFieldInfo) / sizeof(BFCBO::CLASS_FIELD_INFO);
//******************************************************************************
OPCOnlineConfirmReprint::OPCOnlineConfirmReprint(BFAbstractCBO &parent) 
: OPCConfirmReprint(parent)
{
   TRACE_CONSTRUCTOR(CLASSNAME , NULL_STRING);

   /*
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL);     
   */
}

//******************************************************************************
OPCOnlineConfirmReprint::~OPCOnlineConfirmReprint()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
void OPCOnlineConfirmReprint::doInitWithDefaultValues( const BFDataGroupId &idDataGroup )
{   		
}

//******************************************************************************
void OPCOnlineConfirmReprint::doReset (const BFDataGroupId &idDataGroup)
{
   if( isNew() )
   {
      init( idDataGroup );
   }
}

//******************************************************************************
SEVERITY OPCOnlineConfirmReprint::doApplyRelatedChanges( const BFFieldId &idField, 
																		   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));

   
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY OPCOnlineConfirmReprint::doValidateField( const BFFieldId &idField, 
																   const DString &strValue, 
																   const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField") );
   	

   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/OPCOnlineConfirmReprint.cpp-arc  $
// 
//    Rev 1.0   May 06 2005 11:55:08   porteanm
// Initial revision.
// 


