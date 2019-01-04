//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2000 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : ManualMgmtFeeRebate.cpp
// ^AUTHOR : Serban Popescu   
// ^DATE   : November, 2006
//
// ^CLASS    : ManualMgmtFeeRebate - 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "manualmgmtfeerebate.hpp"
#include "fundmasterlist.hpp"
#include "mgmtco.hpp"
#include "mfaccount.hpp"

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId ManualTradesTransType;
   extern CLASS_IMPORT const BFTextFieldId MgtFeeRbtElig;
   extern CLASS_IMPORT const BFTextFieldId MFRCorporateFund;
   extern CLASS_IMPORT const BFTextFieldId MFRPayment;
   extern CLASS_IMPORT const BFTextFieldId Slsrep;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const MANUAL_MGMT_FEE_REBATE;
}


namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME		= I_ ("ManualMgmtFeeRebate");
   const I_CHAR * const YES				= I_ ("Y");
   const I_CHAR * const CORPORATE_TAX	= I_ ("I");
   const I_CHAR * const CASH_FUND	    = I_ ("CASH");
   const I_CHAR * const MFR				= I_ ("MFR");
   const I_CHAR * const NA				= I_ ("59");
}

namespace CND
{
	extern const long ERR_MGMT_FEE_REBATE_NOT_ALLOWED;
	extern const long ERR_TOFUND_SAME_OR_CASH;
	extern const long ERR_INVALID_MF_PAYMENT;
	extern const long WARN_INVALID_MF_PAYMENT;
}

namespace IFASTERR
{
	extern CLASS_IMPORT I_CHAR * const INVALID_MF_PAYMENT;
}
//******************************************************************************
ManualMgmtFeeRebate::ManualMgmtFeeRebate (BFAbstractCBO &parent) : ManualDividend (parent)
{
   TRACE_CONSTRUCTOR ( CLASSNAME, 
                       NULL_STRING);
}


//******************************************************************************
ManualMgmtFeeRebate::~ManualMgmtFeeRebate ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}     

//******************************************************************************
SEVERITY ManualMgmtFeeRebate::doInit (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doInit"));
   setFieldSubstituteValues (ifds::TradesTransType, idDataGroup, ifds::ManualTradesTransType);
   setFieldNoValidate ( ifds::TradesTransType, 
                        TRADETYPE::MANUAL_MGMT_FEE_REBATE, 
                        idDataGroup, 
                        false);

   setFieldSubstituteValues (ifds::MFPayment, idDataGroup, ifds::MFRPayment);

//attributes grid,set this as default, just to show something on the screen
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY ManualMgmtFeeRebate::preInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("preInitWithDefaultValues"));
//base class call   
   ManualDividend::preInitWithDefaultValues (idDataGroup);
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
void ManualMgmtFeeRebate::doInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
	ManualDividend::doInitWithDefaultValues (idDataGroup);
}

//******************************************************************************
SEVERITY ManualMgmtFeeRebate::doApplyRelatedChanges ( const BFFieldId &idField, 
                                                      const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doApplyRelatedChanges"));
	ManualDividend::doApplyRelatedChanges (idField, idDataGroup);

	if (idField == ifds::TradesTransType)
	{
		setFieldRequired (ifds::MFPayment, idDataGroup, true);
		setFieldValid (ifds::MFPayment, idDataGroup, false);
	}
	else if (idField == ifds::AccountNum)
	{
		DString accountNum;

		getField (ifds::AccountNum, accountNum, idDataGroup, false);

		if (!accountNum.empty ())
		{
			MFAccount *pMFAccount = NULL;
			
			if (getWorkSession ().getMFAccount (idDataGroup, accountNum, pMFAccount) <= WARNING && 
				pMFAccount)
			{
				DString brokerCode, branchCode,  slsrepCode;

			     pMFAccount->getField (ifds::BrokerCode, brokerCode, idDataGroup, false);
   				 pMFAccount->getField (ifds::BranchCode, branchCode, idDataGroup, false);
				 pMFAccount->getField (ifds::Slsrep, slsrepCode, idDataGroup, false);

				 setFieldNoValidate (ifds::Broker, brokerCode, idDataGroup, false, false, true, false); 
				 setFieldNoValidate (ifds::Branch, branchCode, idDataGroup, false, false, true, false); 
				 setFieldNoValidate (ifds::SlsrepCode, slsrepCode, idDataGroup, false, false, true, false); 
			}
		}
	}

	return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY ManualMgmtFeeRebate::doValidateField ( const BFFieldId &idField, 
                                                const DString &strValue, 
                                                const BFDataGroupId &idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField"));
	 
	if (ManualDividend::doValidateField (idField, strValue, idDataGroup) <= WARNING)
	{
		if (idField == ifds::MFPayment)
		{
			DString mfPayment;

			getField (ifds::MFPayment, mfPayment, idDataGroup, false);

			if (mfPayment == NA)
			{
				getErrMsg (IFASTERR::INVALID_MF_PAYMENT,
                           CND::ERR_INVALID_MF_PAYMENT, 
                           CND::WARN_INVALID_MF_PAYMENT, 
                           idDataGroup);
			}
		}
	}
 
	return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
bool ManualMgmtFeeRebate::isMgtFeeRbtElig ( const DString &fundCode, 
                                            const DString &classCode, 
                                            const BFDataGroupId &idDataGroup)
{
   DString mgtFeeRbtElig;
   
   getFundField (fundCode, classCode, ifds::MgtFeeRbtElig, mgtFeeRbtElig);
   return mgtFeeRbtElig == Y;
}

//****************************************************************************** 
SEVERITY ManualMgmtFeeRebate::validateFundClass ( const DString &fundCode, 
                                                  const DString &classCode, 
                                                  const DString &accountNum, 
                                                  const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateFundClass"));

   if (!fundCode.empty() && !classCode.empty())
   {
      if (isMgtFeeRbtElig (fundCode, classCode, idDataGroup))
      {
         ; //continue with other validation if necessary
      }
      else
      {
// management fee rebate is not allowed. 
         ADDCONDITIONFROMFILE (CND::ERR_MGMT_FEE_REBATE_NOT_ALLOWED);
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY ManualMgmtFeeRebate::validateToFundClass ( const DString &toFund, 
                                                    const DString &toClass, 
                                                    const DString &accountNum, 
                                                    const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateToFundClass"));

   validateMasterActAMS(idDataGroup);
   validateToFundClassAgainstFundEligible(toFund, toClass, idDataGroup);

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY ManualMgmtFeeRebate::validateFromToFundClass ( const DString &fromFund,
                                                        const DString &fromClass,
                                                        const DString &toFund,
                                                        const DString &toClass,
                                                        const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateFromToFundClass"));

    FundMasterList	*pFundMasterList;
	DString			taxType;
	DString			mfrCorporateFund;

    getWorkSession().getOption( ifds::MFRCorporateFund, mfrCorporateFund, idDataGroup, false );

	if (getMgmtCo ().getFundMasterList (pFundMasterList) <= WARNING && pFundMasterList != NULL)
		taxType = pFundMasterList->getTaxType (fromFund);

	// need to see for cash fund
	if  (mfrCorporateFund == YES && taxType == CORPORATE_TAX)
	{
		if (fromFund != toFund && fromClass != toClass)
		{
			ADDCONDITIONFROMFILE (CND::ERR_TOFUND_SAME_OR_CASH);
		}
	}

	return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY ManualMgmtFeeRebate::validateESGSettle ( const DString &strValue, 
                                                  const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateESGSettle"));

   return GETCURRENTHIGHESTSEVERITY ();
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ManualMgmtFeeRebate.cpp-arc  $
// 
//    Rev 1.1   Sep 16 2007 15:41:44   jankovii
// IN #990336 - User is unable to process manual/adhoc MFR trades.
// 
//    Rev 1.0   Sep 06 2007 17:24:20   popescu
// Initial revision.
// 
// 
*/
