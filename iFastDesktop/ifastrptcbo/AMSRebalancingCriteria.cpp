//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 by International Financial, Inc.
//
//*****************************************************************************
//
// ^FILE   : AMSRebalancingCriteria.cpp
// ^AUTHOR : 
// ^DATE   : Nov 15, 2002
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : AMSRebalancingCriteria
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************

#include "stdafx.h"
#include "amsrebalancingcriteria.hpp"
#include <dataimpl\dse_dstc0223_req.hpp>
#include <dataimpl\dse_dstc0223_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME = I_( "AMSRebalancingCriteria" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId AMSCode;
   extern CLASS_IMPORT const BFTextFieldId Description;
   extern CLASS_IMPORT const BFTextFieldId Name;
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest AMS_ACCOUNT_CHECK;
}

//*****************************************************************************
// Constructor
//*****************************************************************************

AMSRebalancingCriteria::AMSRebalancingCriteria( BFAbstractCBO &parent )
:  ifastReportCriteria( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );      
}

//*****************************************************************************
// Destructor
//*****************************************************************************

AMSRebalancingCriteria::~AMSRebalancingCriteria()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//*****************************************************************************
// doValidateFields will validate the AccountNum and AMSCode.  It will call
// the helper methods validateAMSCode and validateAccountNum to do the
// validation.
// @param   const BFFieldId& idField - current field id validated.
//          const DString& strValue - value associated to field id.
//          long lDataGroupId - current group id.
//*****************************************************************************
SEVERITY AMSRebalancingCriteria::doValidateFields( const BFFieldId &idField, const DString& strValue, long  lDataGroupId )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateFields" ) );
   if ( idField == ifds::AccountNum ) {
      validateAccountNum ( strValue, lDataGroupId );
   } else if ( idField == ifds::AMSCode ) {
      validateAMSCode ( strValue, lDataGroupId );
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
// This method will blank out the Description field and validate the AMSCode
// entered for the AMS Code criteria type.   The validation is successful upon
// a successful creation of the AMSMstrList.  
// @param   const DString& dstrBrokerCode - broker code to check
//          long lDataGroupId - current data group id.
// @returns SEVERITY - Error from creation of AMSMstrList.
//*****************************************************************************
SEVERITY AMSRebalancingCriteria::validateAMSCode( const DString& strValue, long  lDataGroupId )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAMSCode" ) );

/*   AMSMstrList pAMSMstrList ( *this );
   SEVERITY sev = pAMSMstrList.init ( strValue, I_( "N" ), NULL_STRING );   
   setFieldNoValidate ( ifds::Description, NULL_STRING, lDataGroupId, true, true, true, false );*/
   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
// This method will make a view call 223 to validate the account number.  View
// 223 will return valid for AMS accounts only, error otherwise.  When the 
// view is successfull the Description field will be populated with the 
// shareholder name, NULL_STRING otherwise.
// @param   const DString& dstrBrokerCode - broker code to check
//          long lDataGroupId - current data group id.
// @returns SEVERITY - Error from view call.
//*****************************************************************************
SEVERITY AMSRebalancingCriteria::validateAccountNum( const DString& strValue, long  lDataGroupId )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAccountNum" ) );
   BFData requestData(ifds::DSTC0223_REQ);
   BFData response(ifds::DSTC0223_VW);

   DString mgmtCoIdOut;
   requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   requestData.setElementValue( ifds::AccountNum, strValue );
   requestData.setElementValue( ifds::Track, I_( "N" ) );
   requestData.setElementValue( ifds::Activity, NULL_STRING );

   SEVERITY sevRtn = BFDataBroker::getInstance( )->receive( DSTC_REQUEST::AMS_ACCOUNT_CHECK,
                                                            requestData, 
                                                            response, 
                                                            DSTCRequestor( getSecurity(), true ) );
   if ( sevRtn <= WARNING ) {
      BFData* repeat = new BFData( response.getRepeat( 0 ));
      DString dstrShrName = repeat->getElementValue ( ifds::Name );
      setFieldNoValidate ( ifds::Description, dstrShrName, lDataGroupId, true, true, true, false );       
   } else {
      setFieldNoValidate ( ifds::Description, NULL_STRING, lDataGroupId, true, true, true, false );
   }

   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastrptcbo/AMSRebalancingCriteria.cpp-arc  $
// 
//    Rev 1.0   Nov 19 2002 11:28:12   HSUCHIN
// Initial Revision
*/
