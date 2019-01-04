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
// ^FILE   : RolloverExchange.cpp
// ^AUTHOR : Robbins Kuriakose   
// ^DATE   : Nov 2013
// ^CLASS    : Rollover Exchange - 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :Used for the rollover exchnage trade object creation
//	Remark:The rolllover exchanges doesnot support any allocations and FeeSetup
//         based for inital version.Enhnacement is needed to support these
//         functionalities.
//
//******************************************************************************
#include "stdafx.h"
#include "RolloverExchange.hpp"
#include "funddetail.hpp"
#include "fundmasterlist.hpp"
#include "fundtolist.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"
#include "accounttradeslist.hpp"
#include "FundLmtOverride.hpp"
#include "FundLmtOverrideList.hpp"
#include "pendingtradelist.hpp"
#include "transactionlist.hpp"

namespace
{
 const I_CHAR * const CLASSNAME = I_ ("RolloverExchange"); 
 const I_CHAR * YES				= I_("Y");
 const I_CHAR * DIRECT			= I_("N");
 const I_CHAR * GROSS			= I_("Y");
 const I_CHAR * UNITS			= I_("U");
 const I_CHAR * OMNIBUS			= I_("OM");
 const int FULL_LIST            = 0;
 const I_CHAR * RED_CODE_CASH	= I_("01");
 const I_CHAR * DEP_CODE_CASH	= I_("1");
}
namespace ifds
{
  extern CLASS_IMPORT const BFTextFieldId AcctType;
  extern CLASS_IMPORT const BFTextFieldId RolloverExchangeAmountType;
  extern CLASS_IMPORT const BFTextFieldId RolloverExchangeAppl;
  extern CLASS_IMPORT const BFTextFieldId RolloverExchangeToFundClass;
  extern CLASS_IMPORT const BFTextFieldId StopFlag;
  extern CLASS_IMPORT const BFTextFieldId FundToISIN;
  extern CLASS_IMPORT const BFTextFieldId FundToWKN;
  extern CLASS_IMPORT const BFTextFieldId ToFundNumber;
  extern CLASS_IMPORT const BFTextFieldId FromFundNumber;
  extern CLASS_IMPORT const BFTextFieldId rxFundCode;
  extern CLASS_IMPORT const BFTextFieldId rxClassCode;
  extern CLASS_IMPORT const BFDateFieldId TradeDate;
  extern CLASS_IMPORT const BFTextFieldId FromToFundClass;
}
namespace CND
{
	extern const long ERR_FUND_NOT_ELIGABLE_FOR_ROLLOVEREX;
	extern const long ERR_TRADE_EXITS_IN_ACCT;
	extern const long WARN_TRADE_EXITS_IN_ACCT;
	extern const long ERR_FULL_ROLLOVER_EXCHANGE_FOR_OMNIBUS_ACCT;
	extern const long WARN_FULL_ROLLOVER_EXCHANGE_FOR_OMNIBUS_ACCT;
	extern const long ERR_FUND_CLASS_EXCHANGEOUT_STOP_FLAG_ON;
    extern const long ERR_WARN_FUND_CLASS_EXCHANGEOUT_STOP_FLAG_ON;
	extern const long ERR_SAME_FROM_TO_FUND_CLASS_NOT_ALLOW;
}
namespace IFASTERR
{
    extern CLASS_IMPORT I_CHAR * const  TRADE_EXITS_IN_OMNIBUS_ACCT;
	extern CLASS_IMPORT I_CHAR * const  TRADE_EXITS_IN_ACCT;
	extern CLASS_IMPORT I_CHAR * const  FULL_ROLLOVER_EXCHANGE_FOR_OMNIBUS_ACCT;
}
namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const ROLLOVER_EXCHANGE;
   extern CLASS_IMPORT I_CHAR * const ROLLOVER_EXCHANGE_OUT;
   extern CLASS_IMPORT I_CHAR * const ROLLOVER_EXCHANGE_IN;
   extern CLASS_IMPORT I_CHAR * const EXCHANGE_OUT;
   extern CLASS_IMPORT I_CHAR * const EXCHANGE_IN;
}
namespace RULE_TYPE
{
   extern const I_CHAR * const SKIP_ACCT_STOP_FOR_ROLLOVER_EXCHANGE_IN;
   extern const I_CHAR * const SKIP_ACCT_STOP_FOR_ROLLOVER_EXCHANGE_OUT;
}
const BFFieldId m_RolloverExRestrictedFields[]=
{
	ifds::GrossOrNet,
	ifds::OrderType,
	ifds::AmtType,
	ifds::Amount,
	ifds::ToFund,
	ifds::ToClass,
	ifds::FundToISIN,
	ifds::FundToWKN,
	ifds::ToFundNumber,
	ifds::DepositType,
	ifds::RedCode,
};
int m_RolloverExRestrictedFields_size = 
   sizeof(m_RolloverExRestrictedFields) / sizeof(BFFieldId);
//******************************************************************************
RolloverExchange::RolloverExchange (BFAbstractCBO &parent) : Exchange (parent)
{
   TRACE_CONSTRUCTOR ( CLASSNAME, 
                       NULL_STRING );
}
 //******************************************************************************
RolloverExchange::~RolloverExchange ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}
//******************************************************************************
SEVERITY RolloverExchange::doInit (const BFData &data)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doInit"));
   Exchange::doInit (data);
   commonInit(BF::HOST);
   return GETCURRENTHIGHESTSEVERITY ();
}
//******************************************************************************
SEVERITY RolloverExchange::doInit (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doInit"));
   Exchange::doInit (idDataGroup);
   setFieldNoValidate (ifds::TradesTransType, TRADETYPE::ROLLOVER_EXCHANGE, idDataGroup, false, true, true);
   commonInit(idDataGroup);
   return GETCURRENTHIGHESTSEVERITY ();
}
//******************************************************************************
SEVERITY RolloverExchange::preInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("preInitWithDefaultValues"));
   Exchange::preInitWithDefaultValues (idDataGroup);
   return GETCURRENTHIGHESTSEVERITY ();
}
//******************************************************************************
void RolloverExchange::doInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
	Exchange::doInitWithDefaultValues(idDataGroup);
	commonInit(idDataGroup);
}
//******************************************************************************
void RolloverExchange::commonInit(const BFDataGroupId &idDataGroup)
{
   setDefaultOrderType(idDataGroup);
   setFieldNoValidate(ifds::GrossOrNet, GROSS, idDataGroup, false, false, true, true);
   for( int i = 0;i < m_RolloverExRestrictedFields_size; i++)
   {
    setFieldValid(m_RolloverExRestrictedFields[i], idDataGroup, true);
    setFieldReadOnly(m_RolloverExRestrictedFields[i], idDataGroup, true);
   }
   setFieldSubstituteValues (ifds::AmtType, idDataGroup, ifds::RolloverExchangeAmountType);
   if( isNew())//new trade
   {
	 setFieldNoValidate(ifds::AmtType,UNITS,idDataGroup, false, false, true, true);
	 setFieldNoValidate(ifds::Amount,I_("0.00"),idDataGroup, false, false, true, true); 
	 setDepositAndRedemptionCode(idDataGroup);
   }
   //rebook case also we neee do default like tarde entry for XR33 but with the exception
   if( isRebook())
   {
    setFieldNoValidate(ifds::Amount,I_("0.00"),idDataGroup, false, false, true, true);
   }
   //pending or rebook.New tarde entry is handled in doapplyrelated chnages
   //Fund ,class,account  might not be intialized for new trades.
   //handles the dynamic chnages in Account catagory as well
   if(!isNew()|| isRebook())
   {
	 DString dstrAccountNum;
	 getField (ifds::AccountNum, dstrAccountNum, idDataGroup);
	 DString dstrFromFund,dstrFromClass;
	 getField (ifds::FromFund,  dstrFromFund, idDataGroup);
	 getField (ifds::FromClass, dstrFromClass, idDataGroup);
	 setFieldReadOnly(ifds::Amount, idDataGroup, true);
	 if(isRebook())
		setFieldNoValidate(ifds::Amount,I_("0.00"),idDataGroup, false, false, true, true);
     if (!dstrFromFund.strip().upperCase().empty() && 
	     !dstrFromClass.strip().upperCase().empty())
	 {
	  FundDetail *pFundDetail = NULL;
	  getWorkSession().getFundDetail(dstrFromFund, dstrFromClass, idDataGroup, pFundDetail);
	  if(pFundDetail)
	  {
	   MFAccount *pMFAccount = NULL;
	   if(getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING &&
	      pMFAccount)
	   {
		 if(!pMFAccount->isAccountOmnibus(dstrAccountNum, idDataGroup))
	 	 {
	      DString  dstrRolloverExchangeAmountType;
		  pFundDetail->getField( ifds::RolloverExchangeAmountType,
			     				 dstrRolloverExchangeAmountType,
		    					 idDataGroup,false);
		  setFieldNoValidate(ifds::AmtType,dstrRolloverExchangeAmountType,
		      		        idDataGroup, false, false, true, true);
		  setFieldValid(ifds::AmtType, idDataGroup, true);
		  setFieldReadOnly(ifds::Amount, idDataGroup, true);
		 }
		 else
		 {
		  setFieldNoValidate(ifds::AmtType,UNITS,idDataGroup, false, false, true, true);
		  setFieldValid(ifds::AmtType, idDataGroup, true);
		  setFieldReadOnly(ifds::Amount, idDataGroup, false);
		 }		
	  }
     }//if fund detail
   }//if fundclass not empty
  } //if re-book/pending 
}
//******************************************************************************
 SEVERITY RolloverExchange::doValidateField ( const BFFieldId &idField, const DString &strValue, 
											  const BFDataGroupId &idDataGroup)
{
 MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                         CLASSNAME, 
                         I_("doValidateField"));
 if (Exchange::doValidateField (idField, strValue, idDataGroup) <= WARNING)
 {
	 if (ifds::Amount == idField )
	 {
	  DString dstrAmount,dstrAccountNum;
	  getField (ifds::AccountNum, dstrAccountNum, idDataGroup);
	  getField (ifds::Amount, dstrAmount, idDataGroup, false);
      double dec_amount = DSTCommonFunctions::convertToDouble (dstrAmount);
	  MFAccount *pMFAccount = NULL;
	  if(getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING &&
         pMFAccount)
	  {
	   if(dec_amount == 0 && pMFAccount->isAccountOmnibus(dstrAccountNum, idDataGroup))
	   {
	     getErrMsg ( IFASTERR::FULL_ROLLOVER_EXCHANGE_FOR_OMNIBUS_ACCT,
                     CND::ERR_FULL_ROLLOVER_EXCHANGE_FOR_OMNIBUS_ACCT,
		 			 CND::WARN_FULL_ROLLOVER_EXCHANGE_FOR_OMNIBUS_ACCT, 
                     idDataGroup);
	   }
	  }
	 }
	 else if (ifds::EffectiveDate == idField )
	 {
	  if( isBackdatedTrade(idDataGroup)&& 
		  accountHasTradeAfterTradeDate(idDataGroup))
	  {
	    DString dstrAccountNum;
	    getField (ifds::AccountNum, dstrAccountNum, idDataGroup);
		MFAccount *pMFAccount = NULL;
	    if(getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING &&
           pMFAccount)
	    {
		 if(pMFAccount->isAccountOmnibus(dstrAccountNum, idDataGroup))
		 {
		  getErrMsg ( IFASTERR::TRADE_EXITS_IN_OMNIBUS_ACCT,
                      CND::ERR_TRADE_EXITS_IN_ACCT,
		              CND::WARN_TRADE_EXITS_IN_ACCT, 
                      idDataGroup);
		 }
		 else
		 {
		 getErrMsg ( IFASTERR::TRADE_EXITS_IN_ACCT,
                     CND::ERR_TRADE_EXITS_IN_ACCT,
		             CND::WARN_TRADE_EXITS_IN_ACCT, 
                     idDataGroup);
		 }
		}
	  }
	 }
	 else if(ifds::ToFund == idField ||ifds::ToClass == idField)
	 {
	  DString dstrAccountNum, dstrFromFund, dstrFromClass, dstrToFund, dstrToClass;
	  getField (ifds::AccountNum, dstrAccountNum, idDataGroup);
	  getField (ifds::FromFund,  dstrFromFund, idDataGroup);
	  getField (ifds::FromClass, dstrFromClass, idDataGroup);
	  getField (ifds::ToFund,  dstrToFund, idDataGroup);
	  getField (ifds::ToClass, dstrToClass, idDataGroup);

	  MFAccount *pMFAccount = NULL;
	  if(getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING &&
	     pMFAccount)
	  {
	   if ( canAccountToTrade( pMFAccount, idDataGroup)<= WARNING &&
		    !dstrFromFund.empty() && !dstrFromClass.empty() &&
			!dstrToFund.empty() && !dstrToClass.empty())
	   {
	 	    validateFromToFundClass ( dstrFromFund, dstrFromClass,
                                      dstrToFund, dstrToClass, idDataGroup);
	   }
	  }
	 }
	 else if(ifds::FromFund == idField ||ifds::FromClass == idField )
	 {
	  DString dstrAccountNum;
	  getField (ifds::AccountNum, dstrAccountNum, idDataGroup);
	  MFAccount *pMFAccount = NULL;
	  if(getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING &&
	     pMFAccount)
	  {
	   canAccountTrade( pMFAccount, idDataGroup);
	  }
	 }
     else if (idField == ifds::FromToFundClass)
     {
	  DString  dstrFromFund, dstrFromClass, dstrToFund, dstrToClass;
	  getField (ifds::FromFund,  dstrFromFund, idDataGroup);
	  getField (ifds::FromClass, dstrFromClass, idDataGroup);
	  getField (ifds::ToFund,  dstrToFund, idDataGroup);
	  getField (ifds::ToClass, dstrToClass, idDataGroup);
	  if (!dstrFromFund.empty() && !dstrFromClass.empty() &&
		  !dstrToFund.empty() && !dstrToClass.empty())
	 	    validateFromToFundClass ( dstrFromFund, dstrFromClass,
                                      dstrToFund, dstrToClass, idDataGroup);
     }
  }
 return GETCURRENTHIGHESTSEVERITY ();
}
//******************************************************************************
SEVERITY RolloverExchange::doApplyRelatedChanges ( const BFFieldId &idField, 
                                 const BFDataGroupId &idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
							CLASSNAME, 
							I_("doApplyRelatedChanges"));
	if (Exchange::doApplyRelatedChanges (idField, idDataGroup) <= WARNING)
	{
	 if (ifds::AccountNum == idField )
	 {
	  DString dstrAccountNum;
	  bool bReadOnly = true;;
	  getField (ifds::AccountNum, dstrAccountNum, idDataGroup);
	  MFAccount *pMFAccount = NULL;
	  if(getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING &&
		 pMFAccount)
	  {
		if(pMFAccount->isAccountOmnibus(dstrAccountNum, idDataGroup))
		{      
		 setFieldNoValidate(ifds::AmtType,UNITS,idDataGroup, false, false, true, true);
		 setFieldValid(ifds::AmtType, idDataGroup, true);
		 setFieldNoValidate(ifds::Amount,I_("0.00"),idDataGroup, false, false, true, true);
		 bReadOnly = false;
		}
	  }
	  setFieldReadOnly(ifds::Amount, idDataGroup, bReadOnly );
	} 
   if(ifds::SettleDate  == idField || 
      ifds::TradeDate   == idField )
    {
     DString dstrAccountNum;
	 getField (ifds::AccountNum, dstrAccountNum, idDataGroup);
     if(!dstrAccountNum.stripAll().empty())
     {      
      MFAccount *pMFAccount = NULL;
	   if(getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING &&
	      pMFAccount)	
         {   
          setFieldReadOnly(ifds::Amount, idDataGroup, !pMFAccount->isAccountOmnibus(dstrAccountNum, idDataGroup)); 
         }
     }     
    }
	if (ifds::FromFund ==idField   ||
		ifds::FromClass == idField ||
		ifds::FromFundNumber == idField )
	{
	 DString dstrAccountNum;
	 getField (ifds::AccountNum, dstrAccountNum, idDataGroup);
	 DString dstrFromFund,dstrFromClass;
	 getField (ifds::FromFund,  dstrFromFund, idDataGroup);
	 getField (ifds::FromClass, dstrFromClass, idDataGroup);
	 if (!dstrFromFund.strip().upperCase().empty() && 
	     !dstrFromClass.strip().upperCase().empty())
	 {
	  FundDetail *pFundDetail = NULL;
	  getWorkSession().getFundDetail(dstrFromFund, dstrFromClass, idDataGroup, pFundDetail);
	  if(pFundDetail)
	  {
	   MFAccount *pMFAccount = NULL;
	   if(getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING &&
	      pMFAccount)
	   {
		 if(!pMFAccount->isAccountOmnibus(dstrAccountNum, idDataGroup))
	 	 {
	      DString  dstrRolloverExchangeAmountType;
		  pFundDetail->getField( ifds::RolloverExchangeAmountType,
			     				 dstrRolloverExchangeAmountType,
		    					 idDataGroup,false);
		  setFieldNoValidate(ifds::AmtType,dstrRolloverExchangeAmountType,
		      		        idDataGroup, false, false, true, true);
		  setFieldValid(ifds::AmtType, idDataGroup, true);
		  setFieldNoValidate(ifds::Amount,I_("0.00"),idDataGroup, false, false, true, true);
		  setFieldReadOnly(ifds::Amount, idDataGroup, true);
		 }
		 else
		 {
		  setFieldNoValidate(ifds::AmtType,UNITS,idDataGroup, false, false, true, true);
		  setFieldValid(ifds::AmtType, idDataGroup, true);
		  setFieldNoValidate(ifds::Amount,I_("0.00"),idDataGroup, false, false, true, true);
		  setFieldReadOnly(ifds::Amount, idDataGroup, false);
		 }
	   }
	   DString dstrRolloverExchangeToFundClass(NULL_STRING);
	   DString dstrToFund, dstrToClass;
	   DString::size_type pos = 0;
	   pFundDetail->getField(ifds::RolloverExchangeToFundClass,
	                         dstrRolloverExchangeToFundClass,
							 idDataGroup,false);
	   if( NULL_STRING != dstrRolloverExchangeToFundClass )
	   {
 		EXTRACT_VALUE(dstrRolloverExchangeToFundClass, dstrToFund );
		CHOP_STRING (dstrRolloverExchangeToFundClass);
		dstrToClass = dstrRolloverExchangeToFundClass;
	   }
	   setFieldNoValidate(ifds::ToFund, dstrToFund,   idDataGroup, false, false, true, true);
	   setFieldNoValidate(ifds::ToClass, dstrToClass, idDataGroup, false, false, true, true);
	 }
	setFieldSubstituteValues (ifds::AmtType, idDataGroup, ifds::RolloverExchangeAmountType);
    setFieldReadOnly (ifds::AmtType, idDataGroup, true);
	}
   }
   //As the ToFund ToClass is read only dont wait for Okay button click and raise an error if
   //To fund/class is not valid
   if ( ifds::ToFund ==  idField ||
	    ifds::ToClass == idField )
   {
	DString  dstrFromFund, dstrFromClass, dstrToFund, dstrToClass;
	getField (ifds::FromFund,  dstrFromFund, idDataGroup);
	getField (ifds::FromClass, dstrFromClass, idDataGroup);
	getField (ifds::ToFund,  dstrToFund, idDataGroup);
	getField (ifds::ToClass, dstrToClass, idDataGroup);
	if (!dstrFromFund.empty() && !dstrFromClass.empty() &&
		!dstrToFund.empty() && !dstrToClass.empty())
	 	validateFromToFundClass ( dstrFromFund, dstrFromClass,
                                    dstrToFund, dstrToClass, idDataGroup);
  }
  }
  return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY RolloverExchange::canAccountTrade ( MFAccount *pMFAccount, 
											const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("canAccountTrade"));
	//calls base class, 
   if (Trade::canAccountTrade (pMFAccount, idDataGroup) <= WARNING)
   {
     DString dstrAccountNum;
     pMFAccount->getField (ifds::AccountNum, dstrAccountNum, idDataGroup, false);
	 dstrAccountNum.strip().stripLeading('0');
     validateClosedCountry (dstrAccountNum, idDataGroup);
     //For a rollover exchnage trade if rule 39,38 is allowed for the fund 
     //allow trade even if Acct Level Transfer/Exchnage stop is on
     DString dstrFundCode, dstrClassCode;
	 getField(ifds::FromFund, dstrFundCode,idDataGroup);
	 getField(ifds::FromClass, dstrClassCode,idDataGroup);
	 if(!dstrFundCode.empty()&& !dstrClassCode.empty()&&
		!skipAccountLevelStopFlags(TRADETYPE::ROLLOVER_EXCHANGE_OUT, dstrFundCode, dstrClassCode,
	  							   dstrAccountNum, idDataGroup))
	 {
      DString tradeDate; 
      getField (ifds::EffectiveDate, tradeDate, idDataGroup);
      if (pMFAccount->canTrfExchOut (tradeDate, idDataGroup) <= WARNING)
         pMFAccount->exchEscrow (tradeDate, idDataGroup);
	 }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}
//******************************************************************************
SEVERITY RolloverExchange::canAccountToTrade ( MFAccount *pMFAccountTo, 
											   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("canAccountToTrade"));
   //calls base class, skip transfer logic,
   if (Trade::canAccountToTrade (pMFAccountTo, idDataGroup) <= WARNING)
   {
      //For a rollover exchnage trade if rule 39,38 is allowed for the fund 
      //allow trade even if Acct Level Transfer/Exchnage stop is on
      DString dstrFundCode, dstrClassCode, dstrToAccountNum;
      pMFAccountTo->getField (ifds::AccountNum, dstrToAccountNum, idDataGroup, false);
	  dstrToAccountNum.strip().stripLeading('0');
	  getField(ifds::ToFund, dstrFundCode,idDataGroup);
	  getField(ifds::ToClass, dstrClassCode,idDataGroup);
	  if(!dstrFundCode.empty()&& !dstrClassCode.empty()&&
		 !skipAccountLevelStopFlags(TRADETYPE::ROLLOVER_EXCHANGE_IN, dstrFundCode, dstrClassCode,
								    dstrToAccountNum, idDataGroup))
	  {
	   DString tradeDate;
       getField (ifds::EffectiveDate, tradeDate, idDataGroup);
       pMFAccountTo->canTrfExchIn (tradeDate, idDataGroup);
	  }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}
//******************************************************************************
SEVERITY RolloverExchange::validateFundClass ( const DString &dstrFundCode, 
											   const DString &dstrClassCode, 
                                               const DString &dstrAccountNum, 
                                               const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
							CLASSNAME, 
							I_("validateFundClass"));
	//overide the exchnage functinality in case of Rollover exchnages
	FundDetail *pFundDetail = NULL;
	DString dstrFund(dstrFundCode);
	DString dstrClass(dstrClassCode);
	if (!dstrFund.stripAll().upperCase().empty() && 
		!dstrClass.stripAll().upperCase().empty())
	{
		getWorkSession().getFundDetail( dstrFund, dstrClass, idDataGroup, pFundDetail );
		if(pFundDetail)
		{
			DString dstrRolloverExchangeAppl;
			pFundDetail->getField(ifds::RolloverExchangeAppl, dstrRolloverExchangeAppl, idDataGroup,
								false);
			if( YES != dstrRolloverExchangeAppl.stripAll())
			{
			  DString idiStr;
			  addIDITagValue( idiStr, I_("FUND"),dstrFund );
			  addIDITagValue( idiStr, I_("CLASS"),dstrClass );
     		  ADDCONDITIONFROMFILEIDI (CND::ERR_FUND_NOT_ELIGABLE_FOR_ROLLOVEREX, idiStr);
			}
			if(!skipAccountLevelStopFlags(TRADETYPE::ROLLOVER_EXCHANGE_OUT, dstrFundCode, dstrClassCode,
										  dstrAccountNum, idDataGroup))
			{
			  DString dstrBroker, dstrBranch, dstrAgent, dstrAccounttNum; 
			  getField (ifds::Broker, dstrBroker, idDataGroup);
			  getField (ifds::Branch, dstrBranch, idDataGroup);
			  getField (ifds::SlsrepCode, dstrAgent, idDataGroup);
			  canFundTrade ( dstrBroker, dstrBranch, dstrAgent,
						  TRADETYPE::EXCHANGE_OUT,
						  dstrAccountNum, dstrFundCode,
						  dstrClassCode,
						  CND::ERR_FUND_CLASS_EXCHANGEOUT_STOP_FLAG_ON,
						  CND::ERR_WARN_FUND_CLASS_EXCHANGEOUT_STOP_FLAG_ON,
						  idDataGroup);
			}
	   }
	}
	return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY RolloverExchange::validateToFundClass ( const DString &dstrFundCode, 
                                         const DString &dstrClassCode, 
                                         const DString &dstrToAccountNum, 
                                         const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateToFundClass"));
    //For a rollover exchnage trade if rule 39,38 is allowed for the fund 
    //allow trade even if Acct Level Transfer/Exchnage stop is on
	MFAccount *pMFAccountTo = NULL;
	if(!dstrFundCode.empty()&& !dstrClassCode.empty()&&
	   !skipAccountLevelStopFlags(TRADETYPE::ROLLOVER_EXCHANGE_IN, dstrFundCode, dstrClassCode,
								  dstrToAccountNum, idDataGroup))
	{
	 
	 DString tradeDate;
     getField (ifds::EffectiveDate, tradeDate, idDataGroup);
	 if(getWorkSession().getMFAccount (idDataGroup, dstrToAccountNum, pMFAccountTo) <= WARNING &&
		pMFAccountTo )
	 {
       pMFAccountTo->canTrfExchIn (tradeDate, idDataGroup);
	 }
	}
    return GETCURRENTHIGHESTSEVERITY ();
}
//******************************************************************************
SEVERITY RolloverExchange::validateAmountAmtType (const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateAmountAmtType"));
	//Rollovwer exchanges are always gross and hard set..No validation required
	return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY RolloverExchange::validateOrderType ( const DString &orderType,const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
							CLASSNAME, 
							I_("validateOrderType"));
		//Rollovwer exchanges are always Direct and hard set..No validation required
	return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY RolloverExchange::setDefaultOrderType (const BFDataGroupId &idDataGroup)
{   
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
							CLASSNAME, 
							I_("setDefaultOrderType"));
	setFieldNoValidate( ifds::OrderType, DIRECT, idDataGroup, false, 
						false, true, true);
	setFieldValid(ifds::OrderType, idDataGroup, true);
	return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY RolloverExchange::validateFromToFundClass ( const DString &fromFund, const DString &fromClass,
													 const DString &toFund, const DString &toClass,
													 const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateFromToFundClass"));
   // do not allow if exchange to same fund and same class
   if (toFund == fromFund && toClass == fromClass)
   {
      ADDCONDITIONFROMFILE (CND::ERR_SAME_FROM_TO_FUND_CLASS_NOT_ALLOW);
   }

   //look for to skip allowable transfer validation
   //else continue with exisiting validation 
   if(!bskipAllowableTransferValidation(idDataGroup))
   {
	 Exchange::validateFromToFundClass ( fromFund, fromClass,
                                         toFund, toClass,
                                         idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY(); 
}
/******************************************************************************
 Input: BFDataGroupId
 OutPut:None
 Return:bool
 Functionality:Return true if the account has subsequent trades after the trade 
			   date including pending and processed
 ******************************************************************************/
bool RolloverExchange::accountHasTradeAfterTradeDate(const BFDataGroupId &idDataGroup)
{
	MFAccount *pMFAccount = NULL;
	bool bTradeExists = false;
	DString dstrFromFund, dstrFromClass, dstrTradeDate,dstrAccountNum,
		    dstrTradedFromFund, dstrTradedFromClass, dstrTradedDate;
	getField (ifds::FromFund,  dstrFromFund, idDataGroup);
	getField (ifds::FromClass, dstrFromClass, idDataGroup);
	getField (ifds::EffectiveDate, dstrTradeDate, idDataGroup);
	getField (ifds::AccountNum, dstrAccountNum, idDataGroup);
	if(getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING &&
	   pMFAccount)
	{
	 if( pMFAccount->accountHasTradeAfterDate( dstrFromFund, dstrFromClass, dstrTradeDate, idDataGroup))
	     bTradeExists = true;
	}
  return bTradeExists;
}
/******************************************************************************
 Input: Fund,Class,TransType,dataGroup
 OutPut:
 Return:bool
 Functionality:Return true if skipAccountLevelStopFlags Rules set for Exchnage IN/OUT 
 ******************************************************************************/
bool RolloverExchange::skipAccountLevelStopFlags(const DString& dstrTransType,
												 const DString& dstrFundCode,
												 const DString& dstrClassCode,
												 const DString& dstrAccountNum,
												 const BFDataGroupId &idDataGroup)
{
  bool bStopFlag (false);
  bool bErrorSeverity (true);
  if(!dstrFundCode.empty()&& !dstrClassCode.empty())
  {
    readStopFlag ( dstrTransType, dstrFundCode, dstrClassCode, dstrAccountNum, bStopFlag, 
                  bErrorSeverity, idDataGroup);
  }
  return !bStopFlag; //dstrStopFlag = NO means skip account level stops;
}
/******************************************************************************
 Input: dataGroup
 OutPut:
 Return:bool
 Functionality:Set the Redemption code and deposit code to CASH if avilable in the environment 
			   Else will substitue with Blank value
 ******************************************************************************/
void RolloverExchange::setDepositAndRedemptionCode(const BFDataGroupId &idDataGroup)
{
   DString dstrRedCodeList, dstrDepCodeList;
   BFProperties *pDepProperties = getFieldProperties (ifds::DepositType, idDataGroup);
   BFProperties *pRedProperties = getFieldProperties (ifds::RedCode, idDataGroup);
   pDepProperties->getAllSubstituteValues (dstrDepCodeList);
   pRedProperties->getAllSubstituteValues (dstrRedCodeList);
   I_CHAR *temp = const_cast<I_CHAR*> (dstrDepCodeList.c_str ());
   bool bfound  = false;
   do {  
	   DString dstrCode,dstrDescr;
       temp = parseIdiString (temp, dstrCode, dstrDescr);         
       if (isCodeInList (DEP_CODE_CASH, dstrCode))
       {
         setFieldNoValidate(ifds::DepositType, DEP_CODE_CASH, idDataGroup, false, false, true, true);//CASH  
         bfound = true;
	   }
      }while ( !bfound && temp && temp != NULL_STRING && *temp);
   if(!bfound)
     setFieldNoValidate(ifds::DepositType, NULL_STRING, idDataGroup, false, false, true, true);
   bfound  = false;    
   temp = const_cast<I_CHAR*> (dstrRedCodeList.c_str ());
   do {  
	   DString dstrCode,dstrDescr;
       temp = parseIdiString (temp, dstrCode, dstrDescr);         
       if (isCodeInList (RED_CODE_CASH, dstrCode))
       {
         setFieldNoValidate(ifds::RedCode, RED_CODE_CASH, idDataGroup, false, false, true, true);//CASH  
         bfound = true;
	   }       	   
      }while ( !bfound && temp && temp != NULL_STRING && *temp);
   if(!bfound)
     setFieldNoValidate(ifds::RedCode, NULL_STRING, idDataGroup, false, false, true, true);
   setFieldValid(ifds::DepositType, idDataGroup, true);
   setFieldValid(ifds::RedCode, idDataGroup, true);  
}
/******************************************************************************
 Input: dataGroup
 OutPut:
 Return:bool
 Functionality:Set the Amount Type to read only
 ******************************************************************************/
SEVERITY RolloverExchange::amtTypeExtraRelatedChanges (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("amtTypeRelatedChanges"));

   if(!isNew()|| isRebook())
   {
	 DString dstrAccountNum;
	 getField (ifds::AccountNum, dstrAccountNum, idDataGroup);
	 if(isRebook())
		setFieldNoValidate(ifds::Amount,I_("0.00"),idDataGroup, false, false, true, true);
     MFAccount *pMFAccount = NULL;
	 if(getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING &&
	    pMFAccount)
	   {
		 if(!pMFAccount->isAccountOmnibus(dstrAccountNum, idDataGroup))
			 setFieldReadOnly(ifds::Amount, idDataGroup, true);
		 else
			 setFieldReadOnly(ifds::Amount, idDataGroup, false);
	  }
    }
   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/Trade.hpp-arc  $
*/