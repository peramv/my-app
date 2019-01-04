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
// ^FILE   : AmsFundAlloc.cpp
// ^AUTHOR : Yingbao   Li
// ^DATE   : Nov. 07, 2002
//
// ^CLASS    : AmsFundAlloc
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : Ams fund allocation
//
//******************************************************************************
#include "stdafx.h"

#include "amsacctlvl.hpp"
#include "AmsFundAlloc.hpp"
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

#include <ifastdataimpl\dse_dstc0083_vw.hpp>
#include <ifastdataimpl\dse_dstc0218_req.hpp>
#include <ifastdataimpl\dse_dstc0218_vw.hpp>

#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_Err_account_ams_model_cannot_hold_global_model_funds.h>
#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_warn_account_ams_model_cannot_hold_global_model_funds.h>
#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_Err_only_child_fund_can_be_added_to_allocation.h>
#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_warn_only_child_fund_can_be_added_to_allocation.h>

namespace
{
   const I_CHAR * const CLASSNAME               = I_( "AmsFundAlloc" );
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
   extern const long	ERR_WARNING_FUND_FOREIGN_CURRENCY;
   extern const long ERR_AMS_FUND_CLASS_INVALID;
   extern const long ERR_AMS_TYPE_INVALID;
   extern const long	ERR_FUND_FOREIGN_CURRENCY;
   extern const long	ERR_FUND_INVALID_FOR_REGISTER_ACCOUNT;   
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
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
AmsFundAlloc::AmsFundAlloc( BFAbstractCBO &parent ) 
: FundAlloc( parent ),
m_bBankruptcyApplied(false) //IN2818924 - DSK_AMS Validation for CDIC
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

//******************************************************************************
AmsFundAlloc::~AmsFundAlloc( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}
//******************************************************************************

SEVERITY AmsFundAlloc::initNew( const BFDataGroupId& idDataGroup,
                                 const DString& dstrTrack ,
                                 const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initNew" ) );

   setObjectNew();
   checkUpdatePermission(BF::HOST );
   m_bBankruptcyApplied = false;

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY AmsFundAlloc::initExisting(const BFData &data)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initExisting" ) );

   attachDataObject( const_cast< BFData & >( data ), false, true ); 
   setFundNumber(BF::HOST);
	checkUpdatePermission(BF::HOST );
	//IN2818924 - DSK_AMS Validation for CDIC
	//AMSCODE 0001, disable editing base on BANKRUPTCY
	{
		DString dstrFundCode, 
			dstrClassCode;

		getField (ifds::FundCode, dstrFundCode, BF::HOST);
		getField (ifds::ClassCode, dstrClassCode, BF::HOST);
		dstrFundCode.strip().upperCase();
		dstrClassCode.strip().upperCase();

		m_bBankruptcyApplied = isFieldsDisabledBaseOnRuleType(dstrFundCode, dstrClassCode, BANKRUPTCY, BF::HOST);

	}//---
	
   setAllocFields(BF::HOST);
   setAmount(BF::HOST);
   clearUpdatedFlags( BF::HOST );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY AmsFundAlloc::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

   if( FundAlloc::doApplyRelatedChanges( idField, idDataGroup ) > WARNING )
      return(GETCURRENTHIGHESTSEVERITY());

   return(GETCURRENTHIGHESTSEVERITY());

}
//******************************************************************************

SEVERITY AmsFundAlloc::doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );
   if( FundAlloc::doValidateField( idField, strValue, idDataGroup ) > WARNING )
      return(GETCURRENTHIGHESTSEVERITY());

   if( idField == ifds::FundClass )
      validateFundClass ( idDataGroup );

   return(GETCURRENTHIGHESTSEVERITY());

}
//*****************************************************************************
void AmsFundAlloc::checkUpdatePermission(const BFDataGroupId& idDataGroup)
{
	bool bPermit = getWorkSession().hasUpdatePermission(UAF::AMS_GLOBAL );

	// PTS 10031833 - For AMS Global:
	// As long as the AMS code in question has not been added to an account, 
	// you should be able to make as many changes as you want to the AMS target mix.  
	// User should also be able to make corrections during the first day of setup.  
	// Once the AMS code in question has been added to an account (except during the first day correction period), you should not be able to modify the AMS target asset mix at the GLOBAL level.  If the asset mix changes, users will be required to place a STOP date on the GLOBAL mix and setup a COPY (with the same AMS code) and new start date (Stop date + 1) and then update the AMS mix accordingly.  
	// (One day correction privileges should still apply to this NEW setup.)
	// For AMS Account level: enabling/disabling the fields is done at dialog level
	DString dstrCurrentBusinessDate, dstrEffectiveDate;
	getWorkSession().getMgmtCoOptions()->getField( ifds::CurrBusDate, 
		                                            dstrCurrentBusinessDate, 
																  BF::HOST,
																  false );
	getParent()->getField( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup );
	if( DSTCommonFunctions::CompareDates( dstrEffectiveDate, dstrCurrentBusinessDate ) == DSTCommonFunctions::FIRST_EARLIER )
	{	 	
		DString dstrInUse;
		getParent()->getParent()->getField(ifds::AMSCodeInUse, dstrInUse, BF::HOST,false );
		if ( dstrInUse.strip().upperCase() == YES )
			bPermit = false;
	}
	
	setFieldReadOnly( ifds::FundCode,idDataGroup,        !bPermit );
	setFieldReadOnly( ifds::ClassCode,idDataGroup,       !bPermit );
	setFieldReadOnly( ifds::ToFundNumber,idDataGroup,    !bPermit );
	setFieldReadOnly( ifds::AllocPercentage,idDataGroup, !bPermit );
}

//*****************************************************************************
SEVERITY AmsFundAlloc::validateFundClass( const BFDataGroupId& idDataGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundClass" ) );

   DString dstrFundCode,dstrClassCode,dstrSysCurrency, dstrAMSType;
   getField( ifds::FundCode,dstrFundCode,idDataGroup,false );
   getField( ifds::ClassCode,dstrClassCode,idDataGroup,false );
   //validate FundClass based on AMSType
   (getParent()->getParent() ) -> getField(ifds::AMSType,dstrAMSType, idDataGroup, false);

   //Soft Capped
   MFAccount *pMFAccount = dynamic_cast<MFAccount*>(getParent()->getParent()->getParent()->getParent());

   if (pMFAccount)
   {
       DString dstrAccountNum, dstrEffectiveDate;
       pMFAccount->getField(ifds::AccountNum, dstrAccountNum, idDataGroup);
       getParent()->getField(ifds::EffectiveDate, dstrEffectiveDate, idDataGroup );

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
   else if ( dstrAMSType == REPORT_ONLY )
   {
      //This enhacement make frank russel doesn't work, May 15, 2003
      //To make frank russel work, winnie and shaobo agree the change for checking frank russel default type also.
      FundGroupTypeList *pFundGroupTypeList = NULL;
      bool fundclassexist = false;
      if(getMgmtCo().getFundGroupTypeList( pFundGroupTypeList, DEFAULT_AMS_TYPE ) <= WARNING )
      {
         if (pFundGroupTypeList)
         {
            if (pFundGroupTypeList->isFundClassExist(
               dstrFundCode.strip().upperCase(), dstrClassCode, DEFAULT_AMS_TYPE, DEFAULT_AMS_GROUP_CODE) )
            {
               fundclassexist = true;
            }
         }
      }
      if(!fundclassexist && getMgmtCo().getFundGroupTypeList( pFundGroupTypeList, DEFAULT_AMS_TYPE_FRK ) <= WARNING )
      {
         if (pFundGroupTypeList)
         {
            if ( pFundGroupTypeList->isFundClassExist(
               dstrFundCode.strip().upperCase(), dstrClassCode, DEFAULT_AMS_TYPE_FRK, DEFAULT_AMS_GROUP_CODE_FRK) )
            {
               fundclassexist = true;
            }
         }
      }
      if(!fundclassexist)
      {
         DString idiStr;
         addIDITagValue( idiStr, I_( "FUNDNAME" ),  dstrFundCode.strip() );
         addIDITagValue( idiStr, I_( "CLASSNAME" ), dstrClassCode.strip() );
         ADDCONDITIONFROMFILEIDI( CND::ERR_AMS_FUND_CLASS_INVALID, idiStr );
         return(GETCURRENTHIGHESTSEVERITY());
      }
   }
   else if ( dstrAMSType == FUND_OF_FUNDS )
   {
      // No edits!!!
   }
   else
   {
      DString idiStr;
      addIDITagValue( idiStr, I_( "AMSTYPE" ),  dstrAMSType.strip() );
      ADDCONDITIONFROMFILEIDI( CND::ERR_AMS_TYPE_INVALID, idiStr ); 
      return(GETCURRENTHIGHESTSEVERITY());
   }


    return(GETCURRENTHIGHESTSEVERITY());

}

//****************************************************************************
//IN2818924 - DSK_AMS Validation for CDIC
SEVERITY AmsFundAlloc::getFundLmtOverrideList ( FundLmtOverrideList *&pFundLmtOverrideList,
                                              const DString& transType,
                                              const DString& fundCode,
                                              const DString& classCode,
                                              const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getFundLmtOverrideList"));

   pFundLmtOverrideList = NULL;
   
   DString strKey;
   
   strKey = I_("FundLmtOverrideList");
   strKey += I_(";TransType=");
   strKey += transType;
   strKey += I_(";FundCode=");
   strKey += fundCode;   
   strKey += I_(";ClassCode=");
   strKey += classCode;   
   pFundLmtOverrideList = 
      dynamic_cast<FundLmtOverrideList *>(BFCBO::getObject(strKey, idDataGroup));

   if (!pFundLmtOverrideList )
   {
      pFundLmtOverrideList = new FundLmtOverrideList (*this);
      if (pFundLmtOverrideList->init (fundCode, classCode, transType) <= WARNING)
      {
         setObject (pFundLmtOverrideList, strKey, OBJ_ACTIVITY_NONE, idDataGroup); 
      }
      else
      {
         delete pFundLmtOverrideList;
         pFundLmtOverrideList = NULL;
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//IN2818924 - DSK_AMS Validation for CDIC
bool AmsFundAlloc::isFieldsDisabledBaseOnRuleType( const DString& fundCode,
											    const DString& classCode,
												const DString& ruleType, 
                                                const BFDataGroupId &idDataGroup)
{
   DString transType(I_("AMS")),
	   accountNum;

   MFAccount *pMFAccount = dynamic_cast<MFAccount*>(
                     getParent()->getParent()->getParent()->getParent());

   if(!pMFAccount) return false;

   pMFAccount->getField (ifds::AccountNum, accountNum, idDataGroup, false);

   accountNum.strip();

   bool bReadOnlyBaseOnRuleType = false;
 
   FundLmtOverrideList *pFundLmtOverrideList = NULL;

   if(!fundCode.empty() && !classCode.empty())
   {
	   getFundLmtOverrideList(pFundLmtOverrideList,
		   transType,
		   fundCode,
		   classCode,
		   idDataGroup);

	   FundLmtOverride *pFundLmtOverride = NULL;
	   if ( pFundLmtOverrideList != NULL &&
		   pFundLmtOverrideList->getFundLmtOverride ( getWorkSession(), 
		   accountNum, 
		   ruleType, 
		   pFundLmtOverride, 
		   idDataGroup) <= WARNING && 
		   pFundLmtOverride)
	   {
		   // disable fields
		   DString stopFlag;
		   pFundLmtOverride->getField (ifds::StopFlag, stopFlag, idDataGroup, false);
		   stopFlag.strip().upperCase();

		   bReadOnlyBaseOnRuleType = stopFlag == I_("Y");

	   }
   }

   return bReadOnlyBaseOnRuleType;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/amsFundAlloc.cpp-arc  $
// 
//    Rev 1.25   Jan 31 2012 07:36:42   panatcha
// IN2818924 - DSK_AMS Validation for CDIC
// 
//    Rev 1.24   Nov 07 2011 23:30:36   wichian
// IN#2575735 - To calculate each allocation amount in the initialization.
// 
//    Rev 1.23   Jul 18 2007 09:35:44   smithdav
// PET2360 FN02
// 
//    Rev 1.22   Dec 08 2004 17:21:58   aguilaam
// PET_910: clean-up for setfields
// 
//    Rev 1.21   Jul 16 2004 15:20:10   VADEANUM
// PTS 10031833 - Added 24hr grace period for AMS Global. 
// 
//    Rev 1.20   Jul 15 2004 16:34:52   VADEANUM
// PTS 10031833 - Enable Fund/Class if AMS Code has not been added to any account.
// 
//    Rev 1.19   Jun 25 2004 16:37:40   popescu
// PST 10031525, fund limitation override issues
// 
//    Rev 1.18   May 11 2004 15:49:04   popescu
// PET 985, FN 01, LSIF Trade Entry, added handy methods to fund master list, to check whether a fund is LSIF/Money Market, GIC
// 
//    Rev 1.17   Apr 16 2004 16:38:10   VADEANUM
// PET1005 FN11 - AMS Gaps for 56.1- added AMSEligible to view 56.
// 
//    Rev 1.16   Apr 12 2004 16:13:14   VADEANUM
// PET1005 FN11 - AMS Gaps.
// 
//    Rev 1.15   Oct 14 2003 17:10:46   HSUCHIN
// PTS 10022556 - bug fix to prevent GIC and MPS funds to be part of AMS.
// 
//    Rev 1.14   Jul 30 2003 14:13:50   linmay
// modified initExisting()..
// 
//    Rev 1.13   Jul 18 2003 11:23:24   linmay
// modified for CIBC AMS
// 
//    Rev 1.12   Jun 12 2003 11:44:40   FENGYONG
// if fail to get fundgrouplist, treat it the same as failed to find fundclass exist in it
// 
//    Rev 1.11   Jun 12 2003 10:38:30   FENGYONG
// fix
// 
//    Rev 1.10   Jun 11 2003 13:47:42   FENGYONG
// 10018204
// 
//    Rev 1.9   May 14 2003 12:02:28   FENGYONG
// 10017087 frank russell
// 
//    Rev 1.8   Apr 15 2003 10:43:20   linmay
// Sync up with 1.5.2.0
// 
//    Rev 1.7   Apr 10 2003 15:06:00   ZHANGCEL
// PTS 10015549: Added logic to check fund currency against System Currency only if MultiCurrency is 'no'
// 
//    Rev 1.6   Mar 21 2003 19:42:52   PURDYECH
// Sync 1.5.1.0 back to trunk
// 
//    Rev 1.5.1.0   Mar 21 2003 17:57:06   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.5   Jan 13 2003 14:22:02   WINNIE
// Edit check against SysTransferIn and SysTransferOut instead StopPurchase, StopRedemption and StopTransferIn
// 
//    Rev 1.4   Nov 29 2002 09:57:08   KOVACSRO
// added setAllocFields in initExisting.
// 
//    Rev 1.3   Nov 29 2002 08:58:28   KOVACSRO
// made it work globally, rather than just for AMS screens.
// 
//    Rev 1.2   Nov 22 2002 14:28:34   YINGBAOL
// add validateFundClass and change FundNumber to ToFundNumber
// 
//    Rev 1.1   Nov 19 2002 13:27:20   YINGBAOL
// check permission
// 
//    Rev 1.0   Nov 13 2002 09:59:34   YINGBAOL
// Initial Revision
// 
 * 
 * 
 */