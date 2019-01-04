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
//    Copyright 2002 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : AMSHypoAlloc.cpp
// ^AUTHOR : Thanisorn Sangkrajang
// ^DATE   : Jul. 26, 2017
//
// ^CLASS    : AMSHypoAlloc
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : AMS Hypothetical report proposed fund allocation.
//
//******************************************************************************
#include "stdafx.h"

#include "AMSHypoAlloc.hpp"
#include "amsmstrinfo.hpp"
#include "amsmstrlist.hpp"
#include "FundAlloc.hpp"
#include "funddetail.hpp"
#include "fundgrouptypelist.hpp"
#include "fundmasterlist.hpp"
#include "mfaccount.hpp"
#include "MgmtCoOptions.hpp"
#include "mgmtco.hpp"
#include "fundlmtoverride.hpp"//IN2818924 - DSK_AMS Validation for CDIC
#include "fundlmtoverridelist.hpp"

#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_Err_account_ams_model_cannot_hold_global_model_funds.h>
#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_warn_account_ams_model_cannot_hold_global_model_funds.h>
#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_Err_only_child_fund_can_be_added_to_allocation.h>
#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_warn_only_child_fund_can_be_added_to_allocation.h>

namespace
{
   const I_CHAR * const CLASSNAME               = I_( "AMSHypoAlloc" );
   const I_CHAR * const NO                      = I_( "N" );
   const I_CHAR * const YES                     = I_( "Y" );
   const double dSmallValue                     = .0000000001;
   const I_CHAR * const REBALANCE               = I_("RB");
   const I_CHAR * const REPORT_ONLY             = I_("RO");
   const I_CHAR * const FUND_OF_FUNDS           = I_("FOF");
   const I_CHAR * const DEFAULT_AMS_TYPE        = I_("ROFND");
   const I_CHAR * const DEFAULT_AMS_GROUP_CODE  = I_("VISCNT");

   //frank russel have diffrent default amstype from the other client
   const I_CHAR * const DEFAULT_AMS_TYPE_FRK          = I_("REPORT");
   const I_CHAR * const DEFAULT_AMS_GROUP_CODE_FRK    = I_("TARAST");
   const I_CHAR * const BANKRUPTCY                    = I_("43"); //IN2818924 - DSK_AMS Validation for CDIC
}

namespace CND
{  // Conditions used
   extern const long ERR_FUND_STOP_TRANSFER;
   extern const long ERR_WARNING_FUND_FOREIGN_CURRENCY;
   extern const long ERR_AMS_FUND_CLASS_INVALID;
   extern const long ERR_AMS_TYPE_INVALID;
   extern const long ERR_FUND_FOREIGN_CURRENCY;
   extern const long ERR_FUND_INVALID_FOR_REGISTER_ACCOUNT;   
   extern const long AMS_ERR_CANNOT_ADD_GIC;
   extern const long AMS_ERR_CANNOT_ADD_MPS;
   extern const long ERR_NON_AMS_FUND_INELIGIBLE_FOR_AMS_REBALANCING;
   extern const long ERR_FUND_CLASS_STOP_FLAG_ON; //IN2818924 - DSK_AMS Validation for CDIC
}
namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const AMS_GLOBAL;
}

namespace ifds
{  
   extern CLASS_IMPORT const BFTextFieldId      Currency;
   extern CLASS_IMPORT const BFTextFieldId      SysCurrency;
   extern CLASS_IMPORT const BFTextFieldId      FundClass;
   extern CLASS_IMPORT const BFTextFieldId      MultiCurrency;
   extern CLASS_IMPORT const BFTextFieldId      AMSType;
   extern CLASS_IMPORT const BFTextFieldId      AMSFund;
   extern CLASS_IMPORT const BFTextFieldId      AMSEligible;
   extern CLASS_IMPORT const BFTextFieldId      AMSCodeInUse;
   extern CLASS_IMPORT const BFTextFieldId      StopSysGenTrnfrIn;
   extern CLASS_IMPORT const BFTextFieldId      StopSysGenTrfrOut;
   extern CLASS_IMPORT const BFNumericFieldId   AccountNum; //IN2818924 - DSK_AMS Validation for CDIC
   extern CLASS_IMPORT const BFTextFieldId      StopFlag;

   extern CLASS_IMPORT const BFTextFieldId		FundCode;
   extern CLASS_IMPORT const BFTextFieldId		ClassCode;
   extern CLASS_IMPORT const BFTextFieldId		ToFundNumber;
   extern CLASS_IMPORT const BFDecimalFieldId 	AllocPercentage;
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const ACCOUNT_AMS_MODEL_CANNOT_HOLD_GLOBAL_MODEL_FUNDS;
   extern CLASS_IMPORT I_CHAR * const ONLY_CHILD_FUND_CAN_BE_ADDED_TO_ALLOCATION;
}


const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,                 State Flags,      Group Flags
   { ifds::FundCode,            BFCBO::NONE,        0 },          
   { ifds::ClassCode,           BFCBO::NONE,        0 },          
   { ifds::ToFundNumber,        BFCBO::NONE,        0 },          
   { ifds::AllocPercentage,     BFCBO::NONE,        0 },
   { ifds::AMSType,				BFCBO::NONE,		0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
AMSHypoAlloc::AMSHypoAlloc( BFAbstractCBO &parent ) 
: FundAlloc( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   /*registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );*/
}

//******************************************************************************
AMSHypoAlloc::~AMSHypoAlloc( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}
//******************************************************************************

SEVERITY AMSHypoAlloc::initNew( const BFDataGroupId& idDataGroup,
                                 const DString& dstrTrack ,
                                 const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initNew" ) );
  
   setObjectNew();
   setFieldNoValidate(ifds::AMSType, REBALANCE, idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY AMSHypoAlloc::initExisting(const BFData &data)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initExisting" ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY AMSHypoAlloc::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

   if( FundAlloc::doApplyRelatedChanges( idField, idDataGroup ) > WARNING )
      return(GETCURRENTHIGHESTSEVERITY());

   return(GETCURRENTHIGHESTSEVERITY());

}
//******************************************************************************

SEVERITY AMSHypoAlloc::doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );
   if( FundAlloc::doValidateField( idField, strValue, idDataGroup ) > WARNING )
      return(GETCURRENTHIGHESTSEVERITY());

   if( idField == ifds::FundClass )
      validateFundClass ( idDataGroup );

   return(GETCURRENTHIGHESTSEVERITY());

}

//*****************************************************************************
SEVERITY AMSHypoAlloc::validateFundClass( const BFDataGroupId& idDataGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundClass" ) );

   DString dstrFundCode,dstrClassCode,dstrSysCurrency, dstrAMSType;
   getField( ifds::FundCode,dstrFundCode,idDataGroup,false );
   getField( ifds::ClassCode,dstrClassCode,idDataGroup,false );
   //validate FundClass based on AMSType
   getParent()->getField(ifds::AMSType,dstrAMSType, idDataGroup, false);

   //Soft Capped
   MFAccount *pMFAccount = dynamic_cast<MFAccount*>(getParent()->getParent()->getParent()->getParent());

   if (pMFAccount)
   {
       DString dstrAccountNum, dstrEffectiveDate;
       pMFAccount->getField(ifds::AccountNum, dstrAccountNum, idDataGroup);
       /*getParent()->getField(ifds::EffectiveDate, dstrEffectiveDate, idDataGroup );*/

       getWorkSession().fundClassSoftCappedCheck(dstrAccountNum, dstrFundCode, dstrClassCode, I_("DD"), dstrEffectiveDate, idDataGroup);
   }

   if (dstrAMSType == REBALANCE)
   {
      FundDetail *pFundDetail;
      getFundDetail( dstrFundCode, dstrClassCode, pFundDetail );
      if(pFundDetail )
      {
         DString stopSysGenTrnfrIn, 
            stopSysGenTrfrOut;

         pFundDetail->getField (ifds::StopSysGenTrnfrIn, stopSysGenTrnfrIn, idDataGroup, false);
         stopSysGenTrnfrIn.strip().upperCase();
         pFundDetail->getField (ifds::StopSysGenTrfrOut, stopSysGenTrfrOut, idDataGroup, false);
         stopSysGenTrfrOut.strip().upperCase();

         bool bAddErr = stopSysGenTrnfrIn == I_("Y") || 
            stopSysGenTrfrOut == I_("Y");

         DString dstrCurrency, multiCurrency; 
         pFundDetail->getField(ifds::Currency,dstrCurrency,	idDataGroup,false );
         dstrCurrency.strip().upperCase();
         getWorkSession().getMgmtCoOptions()->getField( ifds::SysCurrency, dstrSysCurrency, idDataGroup ,false );
         dstrSysCurrency.strip().upperCase();

         getWorkSession().getMgmtCoOptions()->getField( ifds::MultiCurrency, multiCurrency, idDataGroup, false );
         multiCurrency.strip().upperCase();			
         bool bAddWarn = dstrCurrency != dstrSysCurrency;

         if( bAddErr ) {
            ADDCONDITIONFROMFILE( CND::ERR_FUND_STOP_TRANSFER );    
         } else if( bAddWarn ) {
            ADDCONDITIONFROMFILE( CND::ERR_WARNING_FUND_FOREIGN_CURRENCY ); 	
         }
         FundMasterList *pFundMasterList; 
         SEVERITY sevRtn = getMgmtCo().getFundMasterList( pFundMasterList );
         if ( pFundMasterList && pFundMasterList->isGICFund( dstrFundCode) ) 
         {
             ADDCONDITIONFROMFILE( CND::AMS_ERR_CANNOT_ADD_GIC )
         } else if ( pFundMasterList && pFundMasterList->isMPSFund ( dstrFundCode) ) 
         {
             ADDCONDITIONFROMFILE( CND::AMS_ERR_CANNOT_ADD_MPS )
         }

         DString dstrAMSFund;
         pFundDetail->getField( ifds::AMSEligible, dstrAMSFund, idDataGroup );
         if ( I_( "N" ) == dstrAMSFund.strip().upperCase() )
         {
             // Fund ineligible for AMS rebalancing.
             ADDCONDITIONFROMFILE( CND::ERR_NON_AMS_FUND_INELIGIBLE_FOR_AMS_REBALANCING );  
         }

         if(getWorkSession().isMasterActWithOneChild(idDataGroup))
         {
             if (dynamic_cast<AmsMstrInfo*>(getParent()->getParent()) && !pFundDetail->isAMSChildFund(idDataGroup))
             {
                 CND::CIFast_IFast_ifastcbo_warn_only_child_fund_can_be_added_to_allocation warnCond;
                 CND::CIFast_IFast_ifastcbo_err_only_child_fund_can_be_added_to_allocation errCond;

                 getErrMsg (IFASTERR::ONLY_CHILD_FUND_CAN_BE_ADDED_TO_ALLOCATION,
                            errCond,
                            warnCond,
                            idDataGroup);
             }
         }
      }
   }
    return(GETCURRENTHIGHESTSEVERITY());

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/amsFundAlloc.cpp-arc  $
//
//    Rev 1.0   Nov 13 2002 09:59:34   YINGBAOL
// Initial Revision
// 
 */