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
//    Copyright 2000 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : SplitCommission.cpp
// ^AUTHOR : Zijian Ying
// ^DATE   : February  26, 2001
//
// ^CLASS    : SplitCommission
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "agentlist.hpp"
#include "autotransallocation.hpp"
#include "branchlist.hpp"
#include "brokerlist.hpp"
#include <ifastdataimpl\dse_dstc0151_vw.hpp>
#include <ifastdataimpl\dse_dstc0158_vw.hpp>
#include "matchtransferdetails.hpp"
#include "mgmtco.hpp"
#include "splitcommission.hpp"
#include "splitcommissionlist.hpp"
#include "sysallocation.hpp"
#include "transactiondetails.hpp"
#include "trade.hpp"
#include "mfaccount.hpp"
#include "systematic.hpp"

namespace
{
   const I_CHAR * const CLASSNAME = I_ ("SplitCommission");
   const I_CHAR * const BROKER_CODE = I_ ("BROK");
   const I_CHAR * const BRANCH_CODE = I_ ("BRNH");
   const I_CHAR * const MGMT_CODE = I_ ("CNTX");
   const I_CHAR * const SLSREP_CODE = I_ ("SREP");
   const I_CHAR * const YES = I_ ("Y");
   const I_CHAR * const DATE_IDI_TAG = I_ ("DATE");
   const I_CHAR * const COMMISSION_TYPE_ZERO = I_ ("0");
   const I_CHAR * const COMMISSION_TYPE_ONE = I_ ("1");
   const I_CHAR * const COMMISSION_TYPE_TWO = I_ ("2");   
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId SlsrepName;
   extern CLASS_IMPORT const BFTextFieldId SlsrepAltName;
   extern CLASS_IMPORT const BFTextFieldId RepByBranch;
   extern CLASS_IMPORT const BFDecimalFieldId AllocAmount;
   extern CLASS_IMPORT const BFDecimalFieldId Amount;
   extern CLASS_IMPORT const BFTextFieldId SettleCurrency;
   extern CLASS_IMPORT const BFTextFieldId Default;
   extern CLASS_IMPORT const BFTextFieldId CompanyId;
   extern CLASS_IMPORT const BFDateFieldId StopDate;
   extern CLASS_IMPORT const BFIntegerFieldId CommissionType;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFDateFieldId TradeDate;
   extern CLASS_IMPORT const BFDecimalFieldId AllocPercentage;
   extern CLASS_IMPORT const BFTextFieldId RedemptionPayType;
   extern CLASS_IMPORT const BFDecimalFieldId Fee;
   extern CLASS_IMPORT const BFTextFieldId CompanyName;
}

namespace CND
{
   extern const long ERR_BROKER_EMPTY;
   extern const long ERR_BRANCH_EMPTY;
   extern const long ERR_SALES_REP_EMPTY;
   extern const long ERR_ENTITY_TYPE_EMPTY;
   extern const long ERR_BROKER_INVALID_AS_OF_DATE;
   extern const long ERR_BRANCH_INVALID_AS_OF_DATE;
   extern const long ERR_SLSREP_INVALID_AS_OF_DATE;
   extern const long ERR_COMM_RATE_LESS_THEN_ZERO;
   extern const long ERR_COMM_RATE_GREATER_THEN_100;   
   extern const long WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_SICAV;
   extern const long WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_OEIC;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//   Field DD Id,        State Flags,       Group Flags 
   {ifds::CommEntType,     BFCBO::REQUIRED,    0}, 
   {ifds::CommEntTypeDesc, BFCBO::NONE,        0}, 
   {ifds::CommEntCode,     BFCBO::NONE,        0}, 
   {ifds::CommPrcnt,       BFCBO::NONE,        0}, 
   {ifds::CommAmount,      BFCBO::NONE,        0}, 
   {ifds::Currency,        BFCBO::NONE,        0}, 
   {ifds::TradesPayType,   BFCBO::NONE,        0}, 
   {ifds::Fixed,           BFCBO::NONE,        0}, 
   {ifds::GrossOrNet,      BFCBO::NONE,        0}, 
   {ifds::BrokerCode,      BFCBO::NONE,        0}, 
   {ifds::BranchCode,      BFCBO::NONE,        0}, 
   {ifds::SlsrepCode,      BFCBO::NONE,        0}, 
   {ifds::CommEntName,     BFCBO::NONE,        0}, 
   {ifds::CommRate,        BFCBO::REQUIRED,    0}, 
   {ifds::BranchName,      BFCBO::NONE,        0}, 
   {ifds::BrokerName,      BFCBO::NONE,        0}, 
   {ifds::SlsrepName,      BFCBO::NONE,        0}, 
   {ifds::CommLevel,       BFCBO::NONE,        0}, 
   {ifds::SplitCommRid,    BFCBO::NONE,        0}, 
   {ifds::Default,         BFCBO::NOT_ON_HOST, 0}, 
   {ifds::RenunAmount,     BFCBO::NONE,        0}, 
   {ifds::SplitCommRid,     BFCBO::NONE,        0}, 


};

static const int NUM_FIELDS = sizeof (classFieldInfo) / sizeof (BFCBO::CLASS_FIELD_INFO);


//****************************************************************************
bool SplitCommission::isTypeZERO (DSTCWorkSession &rpDSTCWorkSession)
{
   DString commissionType;

   rpDSTCWorkSession.getOption (ifds::CommissionType, 
      commissionType, BF::HOST, false);
   return commissionType == COMMISSION_TYPE_ZERO;
}

//****************************************************************************
bool SplitCommission::isTypeONE (DSTCWorkSession &rpDSTCWorkSession)
{
   DString commissionType;

   rpDSTCWorkSession.getOption (ifds::CommissionType, 
      commissionType, BF::HOST, false);
   return commissionType == COMMISSION_TYPE_ONE;
}

//****************************************************************************
bool SplitCommission::isTypeTWO (DSTCWorkSession &rpDSTCWorkSession)
{
   DString commissionType;

   rpDSTCWorkSession.getOption (ifds::CommissionType, 
      commissionType, BF::HOST, false);
   return commissionType == COMMISSION_TYPE_TWO;
}

//****************************************************************************
SplitCommission::SplitCommission (BFAbstractCBO &parent) :
   MFCanBFCbo (parent)
{
   TRACE_CONSTRUCTOR (CLASSNAME , NULL_STRING);
   registerMemberData (NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL); 
//   setFieldAllSubstituteValues (ifds::TradesPayType, BF::HOST, ifds::RedemptionPayType);
}

//****************************************************************************
SplitCommission::~SplitCommission (void)
{
   TRACE_DESTRUCTOR (CLASSNAME);
}     


//******************************************************************************
SEVERITY SplitCommission::init (const BFData &data)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("init"));

   attachDataObject (const_cast<BFData&> (data), false, true);

   
   DString dstrCommLevel;
   getField (ifds::CommLevel, dstrCommLevel, BF::HOST);   
   if (dstrCommLevel == I_("40"))
   {
      DString dstrCommEntName;
      getField (ifds::CommEntName, dstrCommEntName, BF::HOST);
      setFieldNoValidate (ifds::SlsrepName, dstrCommEntName, BF::HOST, false, true, false, false );
      clearUpdatedFlags (BF::HOST);
   }
   //calculate the either the CommRate or the 

   // System Level set.  If RepByBranch option is set to Yes then BranchCode field will be active.
   setFieldReadOnly (ifds::BranchCode, BF::HOST, !slsRepByBranch (BF::HOST));
   return (GETCURRENTHIGHESTSEVERITY ());
}

//******************************************************************************
SEVERITY SplitCommission::initNew (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("initNew"));

   setObjectNew ();
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
void SplitCommission::doInitWithDefaultValues (const BFDataGroupId& idDataGroup)
{
   DString dstrCurrency;
   assert (getParent() && getParent()->getParent());
   // Assuming all the parents of SplitCommission have a SettleCurrency Field.
   // Current parents are Trade, Pending Trade, Systematic, Transaction History
   // and Matching Transfers.
   getParent ()->getParent ()->getField (ifds::SettleCurrency, dstrCurrency, idDataGroup);
   
   DString payType;
   
   if (dynamic_cast <Trade*> (getParent ()->getParent ()))
   {
      getParent ()->getParent ()->getField (ifds::TradesPayType, payType, idDataGroup, false);
   }
   if (!payType.empty())
   {
      setFieldNoValidate (ifds::TradesPayType, payType, idDataGroup, false, true, true, false);
   }
   // Initialize the Currency to the Fund Currency   
   setFieldNoValidate (ifds::Currency, dstrCurrency, idDataGroup, false, true, true, false );      
   // System Level set.  If RepByBranch option is set to Yes then BranchCode field will be active.
   setFieldReadOnly (ifds::BranchCode, idDataGroup, !slsRepByBranch (BF::HOST));
   if (SplitCommission::isTypeONE (getWorkSession()))
   {
      setFieldNoValidate (ifds::CommRate, I_ ("0.0"), idDataGroup, false, false);// to force validation
   } 
   else if (SplitCommission::isTypeTWO (getWorkSession()))
   {
      setFieldNoValidate (ifds::CommPrcnt, I_ ("0.0"), idDataGroup, false, false);// to force validation
   }
}

//****************************************************************************
SEVERITY SplitCommission::doApplyRelatedChanges (const BFFieldId& idField, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("doApplyRelatedChanges"));

   if (idField == ifds::CommEntType)
   {
      DString dstr;
      getField (ifds::CommEntType, dstr, idDataGroup, true);
      setFieldNoValidate (ifds::CommEntTypeDesc, dstr, idDataGroup);
      getField (ifds::CommEntType, dstr, idDataGroup, false);
      if (dstr == MGMT_CODE)
      {
         DString dstrCompanyId, dstrtempCompanyId, dstrCompanyName;
         setFieldNoValidate (ifds::CommLevel, I_ ("10"), idDataGroup);

		 getMgmtCo ().getField (ifds::CompanyName, dstrCompanyName, BF::HOST); 
		 /*
         getMgmtCo ().getField (ifds::CompanyId, dstrCompanyId, BF::HOST);        
         const DSTCSecurity* pSecurity = const_cast<DSTCSecurity *> (dynamic_cast<const DSTCSecurity *> ( getSecurity ()));
         long lnumCompany = pSecurity->getNumberOfCompanies ();
         for (int i=0; i < lnumCompany; ++i)
         {
            pSecurity->getCompanyInfo (i, dstrtempCompanyId, dstrCompanyName);
            if (dstrtempCompanyId == dstrCompanyId)
            {
               break;
            }
         } 
		 */       
         setFieldNoValidate (ifds::CommEntName, dstrCompanyName, idDataGroup);
      }
      else if (dstr == BROKER_CODE)
      {
         setFieldNoValidate (ifds::CommLevel, I_ ("20"), idDataGroup);
         setValidFlag (ifds::BrokerCode, idDataGroup, false);   // to force validation
         setFieldNoValidate (ifds::CommEntName, NULL_STRING, idDataGroup);
      }
      else if (dstr == BRANCH_CODE)
      {
         setFieldNoValidate (ifds::CommLevel, I_ ("30"), idDataGroup);
         setValidFlag (ifds::BranchCode, idDataGroup, false);   // to force validation
         setFieldNoValidate (ifds::CommEntName, NULL_STRING, idDataGroup);
      }
      else if (dstr == SLSREP_CODE)
      {
         setFieldNoValidate (ifds::CommLevel, I_ ("40"), idDataGroup);
         setValidFlag (ifds::SlsrepCode, idDataGroup, false);   // to force validation
         setFieldNoValidate (ifds::CommEntName, NULL_STRING, idDataGroup);
      }
   }
   else if (idField == ifds::CommRate && SplitCommission::isTypeONE (getWorkSession()))
   {
      dynamic_cast <SplitCommissionList*> (getParent ())->calculateFieldsBasedOnCommissionType (idDataGroup);
      calculateTheCommissionAmount (idDataGroup);
   }
   else if (idField == ifds::CommPrcnt && SplitCommission::isTypeTWO (getWorkSession()))
   {
      dynamic_cast <SplitCommissionList*> (getParent ())->calculateFieldsBasedOnCommissionType (idDataGroup);
      calculateTheCommissionAmount (idDataGroup);
   }
   return (GETCURRENTHIGHESTSEVERITY ());
}

//******************************************************************************
SEVERITY SplitCommission::doValidateField (const BFFieldId& idField, const DString& strValue, 
   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("doValidateField"));
   SEVERITY sevRtn = NO_CONDITION;
   DString dstrCommEntType;
   getField (ifds::CommEntType, dstrCommEntType, idDataGroup);

   if (idField == ifds::BrokerCode)
   {
      if (dstrCommEntType != MGMT_CODE)
      {
         if (strValue == NULL_STRING)
         {
            ADDCONDITIONFROMFILE (CND::ERR_BROKER_EMPTY);
         }
         else
         {
            checkBroker (strValue, idDataGroup, true);                           
         }      
         if (dstrCommEntType == BROKER_CODE)
         {
            setFieldNoValidate (ifds::CommEntName, _brokerName, idDataGroup);
         }
         setFieldNoValidate (ifds::BrokerName, _brokerName, idDataGroup);
      }
   }
   else if (idField == ifds::BranchCode)
   {
      if ( (dstrCommEntType == SLSREP_CODE) || (dstrCommEntType == BRANCH_CODE))
      {
         DString brokerCode;
         if (strValue == NULL_STRING && slsRepByBranch (BF::HOST))
         {
            ADDCONDITIONFROMFILE (CND::ERR_BRANCH_EMPTY);
         }
         else
         {
            getField (ifds::BrokerCode, brokerCode, idDataGroup);
            if (validateField (ifds::BrokerCode, brokerCode, idDataGroup) <= WARNING)
            {
               checkBranches (strValue, idDataGroup, true);
            }
         }
         if (dstrCommEntType == BRANCH_CODE)
         {
            setFieldNoValidate (ifds::CommEntName, _branchName, idDataGroup);
         }
         setFieldNoValidate (ifds::BranchName, _branchName, idDataGroup);
      }
   }
   else if (idField == ifds::SlsrepCode)
   {
      if (dstrCommEntType == SLSREP_CODE)
      {
         DString branchCode, slsrepName;
         if (strValue == NULL_STRING)
         {
            ADDCONDITIONFROMFILE (CND::ERR_SALES_REP_EMPTY);
         }
         else
         {
            if (slsRepByBranch (idDataGroup))
            {
               getField (ifds::BranchCode, branchCode, idDataGroup);
               sevRtn = validateField (ifds::BranchCode, branchCode, idDataGroup);
            }
            else
            {
               sevRtn = NO_CONDITION;
            }
            if (sevRtn <= WARNING)
            {
               checkAgents (strValue, idDataGroup, true);
            }
         }
         setFieldNoValidate (ifds::SlsrepName, _agentName, idDataGroup);
         setFieldNoValidate (ifds::CommEntName, _agentName, idDataGroup);
      }
   }
   else if (idField == ifds::CommEntType)
   {
      if (strValue == NULL_STRING)
      {
         ADDCONDITIONFROMFILE (CND::ERR_ENTITY_TYPE_EMPTY);
      }
   }
   else if (idField == ifds::CommRate || 
      //comm percent is only for commssion type two
      (idField == ifds::CommPrcnt && SplitCommission::isTypeTWO (getWorkSession())))
   {
      double dblRate = DSTCommonFunctions::convertToDouble (strValue);

      if (dblRate < 0.0)
      {
         ADDCONDITIONFROMFILE (CND::ERR_COMM_RATE_LESS_THEN_ZERO);
      } 
      else if (idField == ifds::CommPrcnt && dblRate > 100.0)
      {
         ADDCONDITIONFROMFILE (CND::ERR_COMM_RATE_GREATER_THEN_100);
      }
   }
   return (GETCURRENTHIGHESTSEVERITY ());
}

//******************************************************************************
void SplitCommission::getField ( const BFFieldId &idField, 
                                 DString &fieldValue, 
                                 const BFDataGroupId &idDataGroup, 
                                 bool formattedReturn) const
{
   if (idField == ifds::CommAmount && formattedReturn)
   {
      BFCBO::getField (idField, fieldValue, idDataGroup, false);
      CurrencyClass::getFormattedValue (getWorkSession (), fieldValue);
   }
   else
   {
      BFCBO::getField (idField, fieldValue, idDataGroup, formattedReturn);
   }
}

//******************************************************************************
SEVERITY SplitCommission::checkBroker (const DString& brokerCode, const BFDataGroupId& idDataGroup,
                                       bool condition_returned)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("checkBroker"));

   BrokerList brokerList (*this);

   //checks for the validity of the broker code. by making a view call, and raising a condition
   //we do not want to make the view call when the broker code is NULL, because the view will
   //return us all the brokers
   if (brokerCode != NULL_STRING && 
       // 'L' for the request type will do a search for broker by code
       brokerList.init (brokerCode, NULL_STRING, I_ ("L")) <= WARNING)
   {
      BFObjIter bfIter (brokerList, idDataGroup);
      DString brokerName;

      bfIter.begin ();
      if (!bfIter.end ())
      {
         DString dstrStopDate;
         bfIter.getObject ()->getField (ifds::StopDate, dstrStopDate, idDataGroup, false);         
         if (checkDateStatus (dstrStopDate, CND::ERR_BROKER_INVALID_AS_OF_DATE, idDataGroup) <= WARNING)
            bfIter.getObject ()->getField (ifds::BrokerName, _brokerName, idDataGroup);
      }
   }
   else
   {
      _brokerName = NULL_STRING;
   }

   if (condition_returned == true)
      return (GETCURRENTHIGHESTSEVERITY ());
   else
      return (NO_CONDITION);

}

//******************************************************************************
SEVERITY SplitCommission::checkBranches (const DString& branchCode, 
   const BFDataGroupId& idDataGroup, bool condition_returned)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("checkBranches"));

   BranchList branchList (*this);
   DString brokerCode;

   getField (ifds::BrokerCode, brokerCode, idDataGroup);
   //checks for the validity of the branch code. by making a view call, and raising a condition
   //we do not want to make the view call when the branch code is NULL, because the view will
   //return us all the branches for this broker
   if (branchCode != NULL_STRING && 
       branchList.init (brokerCode, branchCode) <= WARNING)
   {
      BFObjIter bfIter (branchList, idDataGroup);
      DString branchName;

      bfIter.begin ();
      if (!bfIter.end ())
      {
         DString dstrStopDate;
         bfIter.getObject ()->getField (ifds::StopDate, dstrStopDate, idDataGroup, false);         
         if (checkDateStatus (dstrStopDate, CND::ERR_BRANCH_INVALID_AS_OF_DATE, idDataGroup) <= WARNING)
            bfIter.getObject ()->getField (ifds::BranchName, _branchName, idDataGroup);
      }
   }
   else
   {
      _branchName = NULL_STRING;
   }

   if (condition_returned == true)
      return (GETCURRENTHIGHESTSEVERITY ());
   else
      return (NO_CONDITION);
}

//******************************************************************************
SEVERITY SplitCommission::checkAgents (const DString& slsrepCode, 
   const BFDataGroupId& idDataGroup, bool condition_returned)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("checkAgents"));

   AgentList agentList (*this);
   DString brokerCode, branchCode;

   getField (ifds::BrokerCode, brokerCode, idDataGroup);
   getField (ifds::BranchCode, branchCode, idDataGroup);
   //checks for the validity of the agent code. by making a view call, and raising a condition
   //we do not want to make the view call when the slslrep code is NULL, because the view will
   //return us all the agents for this broker and branch
   if (slsrepCode != NULL_STRING && 
       agentList.init (brokerCode, branchCode, slsrepCode) <= WARNING)
   {
      BFObjIter bfIter (agentList, idDataGroup);
      DString slsrepName;
      DString slsrepAltName;

      bfIter.begin ();
      if (!bfIter.end ())
      {
         DString dstrStopDate;
         bfIter.getObject ()->getField (ifds::StopDate, dstrStopDate, idDataGroup, false);         
         if (checkDateStatus (dstrStopDate, CND::ERR_SLSREP_INVALID_AS_OF_DATE, idDataGroup) <= WARNING)
         {
            bfIter.getObject ()->getField (ifds::SlsrepName, _agentName, idDataGroup);                        
            bfIter.getObject ()->getField (ifds::BranchName, _branchName, idDataGroup);
         }
      }
   }
   else
   {
      _agentName = NULL_STRING;
      if (!slsRepByBranch (idDataGroup))
      {
         _branchName = NULL_STRING;
      }
   }

   if (condition_returned == true)
      return (GETCURRENTHIGHESTSEVERITY ());
   else
      return (NO_CONDITION);
}

//******************************************************************************
bool SplitCommission::slsRepByBranch (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("slsRepByBranc"));

   if (_salesRepByBranch == NULL_STRING)
   {
      getWorkSession ().getOption (ifds::RepByBranch, _salesRepByBranch, idDataGroup);
   }
   return (_salesRepByBranch == YES);
}

//******************************************************************************
SEVERITY SplitCommission::checkDateStatus (const DString& dstrStopDate, long lcondition, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("checkStatus"));
   DString dstrEffectiveDate;
   BFCBO* pBFCBO = getParent ()->getParent ();


   pBFCBO->getField (ifds::EffectiveDate, dstrEffectiveDate, idDataGroup);

   SysAllocation* pSysAllocation = dynamic_cast <SysAllocation*> (pBFCBO);
   if (pSysAllocation)
   {
      pSysAllocation->getField (ifds::EffectiveDate, dstrEffectiveDate, idDataGroup);
   }

   AutoTransAllocation* pAutoTransAllocation = dynamic_cast <AutoTransAllocation*> (pBFCBO);
   if (pAutoTransAllocation)
   {
      pAutoTransAllocation->getField (ifds::EffectiveDate, dstrEffectiveDate, idDataGroup);
   }

   MatchTransferDetails* pMatchTransferDetails = dynamic_cast<MatchTransferDetails*> (pBFCBO);
   if (pMatchTransferDetails)
   {
      pMatchTransferDetails->getField (ifds::TradeDate, dstrEffectiveDate, idDataGroup);
   }

   if (DSTCommonFunctions::CompareDates (dstrStopDate, dstrEffectiveDate) == DSTCommonFunctions::FIRST_EARLIER)
   {
      DString error = I_ ("");      
      addIDITagValue (error, DATE_IDI_TAG, dstrStopDate);
      ADDCONDITIONFROMFILEIDI (lcondition, error);
   }
   return (GETCURRENTHIGHESTSEVERITY ());
}

//******************************************************************************
void SplitCommission::calculateTheCommissionAmount (const BFDataGroupId& idDataGroup)
{
   if (idDataGroup != BF::HOST) //comm amounts are already calculated by the back-end
   {
      DString dstrCommRate, dstrAmount, dstrCommAmount;
      double dblCommRate, dblAmount, dblCommAmount;

      getField (ifds::CommRate, dstrCommRate, idDataGroup);
      //get the total amount
      getParent ()->getField (ifds::Amount, dstrAmount, idDataGroup);
      dblCommRate = DSTCommonFunctions::convertToDouble (dstrCommRate);
      dblAmount = DSTCommonFunctions::convertToDouble (dstrAmount);
      dblCommAmount = dblCommRate * dblAmount / 100;
      dstrCommAmount = DSTCommonFunctions::doubleToDString (ifds::CommAmount, dblCommAmount);
      setFieldNoValidate (ifds::CommAmount, dstrCommAmount, idDataGroup);
   }
}
//*****************************************************************************
void SplitCommission::changeFieldsForRebook()
{
   setFieldNoValidate( ifds::SplitCommRid, NULL_STRING, BF::HOST, false,true,false,false ); // no related changes
   clearUpdatedFlags( BF::HOST ); // the object should not be dirty 
}

//************************************************************************************
SEVERITY SplitCommission::doValidateAll(const BFDataGroupId &idDataGroup, long lValidateGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll"));
	DString dstrAccountNum;

	if(isUpdatedForDataGroup (idDataGroup) && !isNew())
	{
		Systematic *pSystematic =dynamic_cast< Systematic * >(getParent()->getParent());
		if(pSystematic)
			pSystematic->getField(ifds::AccountNum, dstrAccountNum, idDataGroup, true);
		dstrAccountNum.strip ().stripLeading ('0');
		MFAccount *pMFAccount = NULL;
		if (getWorkSession().getMFAccount (idDataGroup, dstrAccountNum,
			pMFAccount) <= WARNING && pMFAccount)
		{	
			bool bDisplyWarnSICAV ,bDisplyWarnOEIC;
			pMFAccount->displayEnvXrefWarningOnUpdate(idDataGroup, bDisplyWarnSICAV, bDisplyWarnOEIC);
			if(bDisplyWarnSICAV)
				ADDCONDITIONFROMFILE (CND::WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_SICAV);
			if(bDisplyWarnOEIC)
				ADDCONDITIONFROMFILE (CND::WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_OEIC);
		}  
	}

	return GETCURRENTHIGHESTSEVERITY();	
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/SplitCommission.cpp-arc  $
// 
//    Rev 1.39   Jul 15 2005 09:20:34   Yingbaol
// PET1235,FN01: Add Record ID ro field info
// 
//    Rev 1.38   Jul 08 2005 09:31:48   Yingbaol
// PET1235,FN01:transaction cancellation rebook
// 
//    Rev 1.37   Jun 30 2005 12:39:06   popescu
// Incident # 338532 - fixed nbr of decimals on the split commission screen for amounts and percentages  - amount fields are formatted to 2 decimals, percentages to 4
// 
//    Rev 1.36   Feb 21 2005 15:18:42   Fengyong
// User needs to log on first
// 
//    Rev 1.35   Feb 17 2005 17:05:04   aguilaam
// incident # 239846 - pass and display RenunAmount (checked in for Serban)
// 
//    Rev 1.34   Dec 02 2004 18:23:02   popescu
// PET 1117/06/56, trades processing/fees processing
// 
//    Rev 1.33   Nov 14 2004 14:56:06   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.32   Dec 08 2003 15:28:20   popescu
// PTS 10023645, split commission re-work
// 
//    Rev 1.31   Nov 12 2003 16:01:32   popescu
// PTS 10023876 , desktop was erroneous preventing the user to modify the comm rate to be equal to zero
// 
//    Rev 1.30   May 13 2003 19:36:24   popescu
// PTS 10016228 & 10016241
// 
//    Rev 1.29   May 13 2003 10:06:04   popescu
// Split commission re-work
// 
//    Rev 1.28   May 06 2003 15:29:30   popescu
// PTS 10016245; restrict the validation on CommPrcnt only for commssion type two environments
// 
//    Rev 1.27   Apr 29 2003 17:08:00   popescu
// PTS 10016204
// 
//    Rev 1.26   Apr 25 2003 16:33:06   popescu
// PTS Work:10016245,
// 
//    Rev 1.25   Apr 04 2003 10:18:40   popescu
// split commsion work
// 
//    Rev 1.24   Mar 21 2003 18:25:04   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.23   Oct 29 2002 11:36:16   HSUCHIN
// sync up with release 49 - 1.22
// 
//    Rev 1.22   Oct 09 2002 23:55:02   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.21   Aug 29 2002 12:56:42   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.20   22 May 2002 18:29:52   PURDYECH
// BFData Implementation
// 
//    Rev 1.19   08 May 2002 16:57:06   KOVACSRO
// getting the stop date unformatted.
// 
//    Rev 1.18   29 Apr 2002 16:31:24   KOVACSRO
// Removed FundAllocation references.
// 
//    Rev 1.17   21 Mar 2002 11:10:26   HSUCHIN
// duplicate namespace definition fix
// 
//    Rev 1.16   08 Mar 2002 09:45:52   HSUCHIN
// bug fix - validation error when sales rep by branch is true, branch cannot be blank.
// 
//    Rev 1.15   13 Feb 2002 11:25:50   HSUCHIN
// bug fix for split commission, added a new field splitcommrid.
// 
//    Rev 1.14   16 Nov 2001 16:35:10   HSUCHIN
// bug fix in doapplyrelatedchanges for different commission types
// 
//    Rev 1.13   07 Nov 2001 15:42:34   HSUCHIN
// code clean up and support for commission type 2
// 
//    Rev 1.12   26 Sep 2001 11:47:24   HSUCHIN
// added function check status to check broker/branch/slsrep status (active/inactive) 
// 
//    Rev 1.11   20 Sep 2001 12:06:36   HSUCHIN
// fixed sales rep name not showing up properly on inquiry of split commission
// 
//    Rev 1.10   13 Sep 2001 17:51:16   HSUCHIN
// added logic to set the rate/percent when either fields are changed.  This is to support percent display.
// 
//    Rev 1.9   03 Jul 2001 12:28:36   HSUCHIN
// Sync up with 1.6.2.4 and bug fix
// 
//    Rev 1.8   09 May 2001 10:26:56   HSUCHIN
// Sync Up to SSB
// 
//    Rev 1.6.2.3   02 May 2001 14:04:26   HSUCHIN
// cosmetic fix
// 
//    Rev 1.6.2.2   02 May 2001 12:54:30   HSUCHIN
// bug fix for commlevel
// 
//    Rev 1.6.2.1   02 May 2001 11:54:28   HSUCHIN
// removed commAmount calc and added logic for commLevel
// 
//    Rev 1.6.2.0   14 Apr 2001 16:00:32   HSUCHIN
// improve validation rule and auto transfer fix
// 
//    Rev 1.6   Mar 22 2001 14:13:24   HSUCHIN
// added transaction allocations hook up
// 
//    Rev 1.5   Mar 19 2001 15:03:58   HSUCHIN
// additional processing and validation
// 
//    Rev 1.4   Mar 18 2001 11:52:06   HSUCHIN
// additioanl features and support
// 
//    Rev 1.3   Mar 13 2001 09:21:38   HSUCHIN
// checked in for Zijian
// 
//    Rev 1.2   Mar 08 2001 15:32:46   YINGZ
// make it work
// 
//    Rev 1.1   Feb 27 2001 15:49:26   YINGZ
// for robert
 * 
 */

