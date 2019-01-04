//******************************************************************************
//
// COPYRIGHT:
//
// The computer systems, procedures, data bases and
// programs created and maintained by International Financial Data Services,
// are proprietary in nature and as such are confIdential.
// Any unauthorized use or disclosure of such information
// may result in civil liabilities.
//
// Copyright 2010 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : RESPInfoUpdateValidation.cpp
// ^AUTHOR : 
// ^DATE   : Oct, 2010
//
// ^CLASS    : RESPInfoUpdateValidation
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "RESPInfoUpdateValidation.hpp"

#include <ifastdataimpl\dse_dstc0415_req.hpp>
#include <ifastdataimpl\dse_dstc0415_reqrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0415_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME               = I_( "RESPInfoUpdateValidation" );
   const I_CHAR * const NO                      = I_( "N" );
   const I_CHAR * const YES                     = I_( "Y" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFIntegerFieldId WarnCode;
}

namespace CND
{  // Conditions used
      //QESI3FN03 - DOB,SIN
   extern const long ERR_AMENDMENT_REQUIRED;
   extern const long WARN_AMENDMENT_MAY_BE_REQUIRED;
   extern const long ERR_ADJUSTMENT_REQUIRED;
   extern const long WARN_ADJUSTMENT_MAY_BE_REQUIRED;
   extern const long ERR_SIN_EFFECTIVE_DATE_IS_MANDATORY;
   extern const long WARN_SIN_EFFECTIVE_DATE_IS_MANDATORY;
   extern const long ERR_SIN_EFFECTIVE_DATE_CANNOT_BE_UNKNOWN;
   extern const long WARN_SIN_EFFECTIVE_DATE_CANNOT_BE_UNKNOWN;
   extern const long ERR_SIN_EFFECTIVE_DATE_CANNOT_BE_EARLIER_THAN_DOFB;
   extern const long WARN_SIN_EFFECTIVE_DATE_CANNOT_BE_EARLIER_THAN_DOFB;
   extern const long ERR_SIN_EFFECTIVE_DATE_CANNOT_BE_FUTURE_DATE;
   extern const long WARN_SIN_EFFECTIVE_DATE_CANNOT_BE_FUTURE_DATE;
   extern const long ERR_REQUIRED_NEW_GRANT_REQUEST_FOR_TAX_YEAR;
   extern const long WARN_MAY_NEED_TO_ADD_NEW_GRANT_REQUEST_FOR_TAX_YEAR;
   extern const long ERR_STATUS_MAY_NEED_TO_FLIP_OR_NEW_REQUEST_MAY_BE_REQUIRED_FOR_TAX_YEAR;
   extern const long WARN_STATUS_NEED_TO_FLIP_OR_NEW_REQUEST_REQUIRED_FOR_TAX_YEAR;
   extern const long ERR_ACCOUNT_MUST_BE_SIBLING_ONLY_FOR_SAGES;
   extern const long WARN_ACCOUNT_MUST_BE_SIBLING_ONLY_FOR_SAGES;
   extern const long ERR_ACCOUNT_MUST_BE_SIBLING_ONLY_FOR_BCTESG;
   extern const long WARN_ACCOUNT_MUST_BE_SIBLING_ONLY_FOR_BCTESG;
}

namespace IFASTERR
{
   //QESI3FN03
   extern CLASS_IMPORT I_CHAR * const AMENDMENT_MAY_BE_REQUIRED;
   extern CLASS_IMPORT I_CHAR * const ADJUSTMENT_MAY_BE_REQUIRED;
   extern CLASS_IMPORT I_CHAR * const SIN_EFFECTIVE_DATE_IS_MANDATORY;
   extern CLASS_IMPORT I_CHAR * const SIN_EFFECTIVE_DATE_CANNOT_BE_UNKNOWN;
   extern CLASS_IMPORT I_CHAR * const SIN_EFFECTIVE_DATE_CANNOT_BE_EARLIER_THAN_DOFB;
   extern CLASS_IMPORT I_CHAR * const SIN_EFFECTIVE_DATE_CANNOT_BE_FUTURE_DATE;
   extern CLASS_IMPORT I_CHAR * const SIN_EFFECTIVE_DATE_CANNOT_BE_FUTURE_DATE;
   extern CLASS_IMPORT I_CHAR * const MAY_NEED_TO_ADD_NEW_GRANT_REQUEST_FOR_TAX_YEAR;
   extern CLASS_IMPORT I_CHAR * const MAY_NEED_TO_FLIP_OR_NEW_REQUEST_MAY_BE_REQUIRED_FOR_TAX_YEAR;
   extern CLASS_IMPORT I_CHAR * const ACCOUNT_MUST_BE_SIBLING_ONLY_FOR_SAGES;
   extern CLASS_IMPORT I_CHAR * const ACCOUNT_MUST_BE_SIBLING_ONLY_FOR_BCTESG;
}

//******************************************************************************************
RESPInfoUpdateValidation::RESPInfoUpdateValidation( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

//******************************************************************************************
RESPInfoUpdateValidation::~RESPInfoUpdateValidation()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************************
SEVERITY RESPInfoUpdateValidation::init(const BFData& data)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject( const_cast< BFData& >( data ), false, true );

   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY RESPInfoUpdateValidation::displayRESPError(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("displayRESPError"));

   DString dstrWarnCode;
   getField(ifds::WarnCode, dstrWarnCode, idDataGroup, false);

   if(dstrWarnCode == NULL_STRING)
      return (GETCURRENTHIGHESTSEVERITY());

   if (dstrWarnCode == IFASTERR::AMENDMENT_MAY_BE_REQUIRED)
   {
      getErrMsg(dstrWarnCode,
                CND::ERR_AMENDMENT_REQUIRED, 
                CND::WARN_AMENDMENT_MAY_BE_REQUIRED,
                idDataGroup);
   }
   else if (dstrWarnCode == IFASTERR::ADJUSTMENT_MAY_BE_REQUIRED)
   {
      getErrMsg(dstrWarnCode,
                CND::ERR_ADJUSTMENT_REQUIRED, 
                CND::WARN_ADJUSTMENT_MAY_BE_REQUIRED,
                idDataGroup);
   }
   else if(dstrWarnCode == IFASTERR::SIN_EFFECTIVE_DATE_IS_MANDATORY)
   {
      getErrMsg(dstrWarnCode,
                CND::ERR_SIN_EFFECTIVE_DATE_IS_MANDATORY, 
                CND::WARN_SIN_EFFECTIVE_DATE_IS_MANDATORY,
                idDataGroup);
   }
   else if(dstrWarnCode == IFASTERR::SIN_EFFECTIVE_DATE_CANNOT_BE_UNKNOWN)
   {
      getErrMsg(dstrWarnCode,
                CND::ERR_SIN_EFFECTIVE_DATE_CANNOT_BE_UNKNOWN, 
                CND::WARN_SIN_EFFECTIVE_DATE_CANNOT_BE_UNKNOWN,
                idDataGroup);
   }
   else if(dstrWarnCode == IFASTERR::SIN_EFFECTIVE_DATE_CANNOT_BE_EARLIER_THAN_DOFB)
   {
      getErrMsg(dstrWarnCode,
                CND::ERR_SIN_EFFECTIVE_DATE_CANNOT_BE_EARLIER_THAN_DOFB, 
                CND::WARN_SIN_EFFECTIVE_DATE_CANNOT_BE_EARLIER_THAN_DOFB,
                idDataGroup);
   }
   else if(dstrWarnCode == IFASTERR::SIN_EFFECTIVE_DATE_CANNOT_BE_FUTURE_DATE)
   {
      getErrMsg(dstrWarnCode,
                CND::ERR_SIN_EFFECTIVE_DATE_CANNOT_BE_FUTURE_DATE, 
                CND::WARN_SIN_EFFECTIVE_DATE_CANNOT_BE_FUTURE_DATE,
                idDataGroup);
   }
   else if(dstrWarnCode ==  IFASTERR::MAY_NEED_TO_ADD_NEW_GRANT_REQUEST_FOR_TAX_YEAR)
   {
      getErrMsg(dstrWarnCode,
                CND::ERR_REQUIRED_NEW_GRANT_REQUEST_FOR_TAX_YEAR,
                CND::WARN_MAY_NEED_TO_ADD_NEW_GRANT_REQUEST_FOR_TAX_YEAR,
                idDataGroup);
   }
   else if(dstrWarnCode ==  IFASTERR::MAY_NEED_TO_FLIP_OR_NEW_REQUEST_MAY_BE_REQUIRED_FOR_TAX_YEAR)
   {
      getErrMsg(dstrWarnCode,
                CND::ERR_STATUS_MAY_NEED_TO_FLIP_OR_NEW_REQUEST_MAY_BE_REQUIRED_FOR_TAX_YEAR,
                CND::WARN_STATUS_NEED_TO_FLIP_OR_NEW_REQUEST_REQUIRED_FOR_TAX_YEAR,
                idDataGroup);
   }
   else if(dstrWarnCode ==  IFASTERR::ACCOUNT_MUST_BE_SIBLING_ONLY_FOR_SAGES) // 1395 
   {
      getErrMsg(dstrWarnCode,
                CND::ERR_ACCOUNT_MUST_BE_SIBLING_ONLY_FOR_SAGES,
                CND::WARN_ACCOUNT_MUST_BE_SIBLING_ONLY_FOR_SAGES,
                idDataGroup);
   }
   else if(dstrWarnCode ==  IFASTERR::ACCOUNT_MUST_BE_SIBLING_ONLY_FOR_BCTESG) // 1710 
   {
      getErrMsg(dstrWarnCode,
                CND::ERR_ACCOUNT_MUST_BE_SIBLING_ONLY_FOR_BCTESG,
                CND::WARN_ACCOUNT_MUST_BE_SIBLING_ONLY_FOR_BCTESG,
                idDataGroup);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RESPInfoUpdateValidation.cpp-arc  $
// 
//    Rev 1.2   Feb 07 2011 18:59:10   dchatcha
// Incident 2409562 - Fix to return warning message for DOFB changes
// 
//    Rev 1.1   Nov 23 2010 08:57:30   kitticha
// PET165541_FN03_QESI_Phase3_Non_Finance - revise.
// 
//    Rev 1.0   Oct 29 2010 03:54:16   kitticha
// Initial revision.
// 
*/
