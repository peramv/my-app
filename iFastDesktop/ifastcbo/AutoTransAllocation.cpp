//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1997 by DST Systems, Inc.
//
//*****************************************************************************
//
// ^FILE   : AutoTransAllocation.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : March 27, 2000
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : AutoTransAllocation
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************

#include "stdafx.h"
#include "autotransallocation.hpp"
#include "autotransallocationlist.hpp"
#include "autoaccttransallocation.hpp"
#include <ifastdataimpl\dse_dstc0004_vw.hpp>
#include <ifastdataimpl\dse_dstc0006_vw.hpp>
#include <ifastdataimpl\dse_dstc0007_vw.hpp>
#include <ifastdataimpl\dse_dstc0084_req.hpp>
#include <ifastdataimpl\dse_dstc0095_req.hpp>
#include <ifastdataimpl\dse_dstc0098_vwrepeat_record.hpp>
#include "dstcommonfunction.hpp"
#include "funddetaillist.hpp"
#include "funddetail.hpp"
#include "fundmaster.hpp"
#include "fundmasterlist.hpp"
#include "fundtolist.hpp"
#include "groupfundlist.hpp"
#include "grouplist.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"
#include "splitcommissionlist.hpp"
#include "splitcommission.hpp"
#include "systematic.hpp"
#include "dstcworksession.hpp"
#include "SeqFundValidation.hpp"

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_("AutoTransAllocation");
   const I_CHAR * const EX_FER_IN_CODE = I_("XFIN"); // trade trans type Exchange In 
   const I_CHAR * const SPLITCOM_LIST = I_("SplitCommissionList");
   const I_CHAR * const STRING_Y = I_("Y");
   const I_CHAR * const STRING_N = I_("N");
   const I_CHAR * const FROMFUND = I_( "FROMFUND" ); // PAC, SWP, saving plan use from fund
   const I_CHAR * const TOFUND = I_( "TOFUND" );   // AT Automatic transfer use to fund
   const I_CHAR * const FUND = I_( "FUND" );
   const I_CHAR * const CLASS = I_( "CLASS" );
   const I_CHAR * const YES = I_( "Y" );
}


namespace CND
{  // Conditions used
   extern const long ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE;
   extern const long ERR_INVALID_FUND_CLASS_CODES;
   extern const long ERR_BLANK_FUND;
   extern const long ERR_BLANK_CLASS;
   extern const long ERR_VALUE_BETWEEN_0_AND_100;
   extern const long ERR_VALUE_CANNOT_BE_ZERO;
   extern const long ERR_FUND_NOT_EFFECTIVE;
   extern const long ERR_INVALID_FUND_NUMBER;
   extern const long ERR_AT_FUNDCLASS_TRANSFER_NOT_ALLOWED;
   extern const long ERR_FUND_CURRENCY_DIFFERENT;
   extern const long ERR_FUND_CLASS_NOT_AVAILABLE_FOR_BROKER;
   extern const long ERR_FUND_CLASS_NOT_AVAILABLE_FOR_SALESREP;
   extern const long ERR_CAPPEDFUND_STATUSE;
   extern const long ERR_CAPPEDFUND_STATUSW;
   extern const long ERR_INVALID_FUND_CLASS_CODES;
   extern const long ERR_CLOSED_COUNTRY_RESIDENT_FOR_MONEY_IN;  
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId ToFundNumber;
   extern CLASS_IMPORT const BFTextFieldId FundClass;
   extern CLASS_IMPORT const BFTextFieldId SplitCommSWP;
   extern CLASS_IMPORT const BFTextFieldId SplitCommPAC;
   extern CLASS_IMPORT const BFTextFieldId SplitCommTrfln;
   extern CLASS_IMPORT const BFTextFieldId Default;
   extern CLASS_IMPORT const BFTextFieldId MultiCurrency;
   extern CLASS_IMPORT const BFTextFieldId Slsrep;
   extern CLASS_IMPORT const BFIntegerFieldId CommissionType;
	extern CLASS_IMPORT const BFTextFieldId FundClassTradeDate;
	extern CLASS_IMPORT const BFTextFieldId SegClient;
	extern CLASS_IMPORT const BFTextFieldId CotClient;
    extern CLASS_IMPORT const BFTextFieldId ToSoftCapCheck;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags 
   {ifds::RunMode, BFCBO::INIT_TO_DEFAULT,          0}, 
   {ifds::TransType, BFCBO::INIT_TO_DEFAULT,        0}, 
   {ifds::PACSWPId, BFCBO::INIT_TO_DEFAULT,         0}, 
   {ifds::FundCode, BFCBO::INIT_TO_DEFAULT,         0}, 
   {ifds::ClassCode, BFCBO::INIT_TO_DEFAULT,        0}, 
   {ifds::Percentage, BFCBO::INIT_TO_DEFAULT,       0}, 
   {ifds::AllocAmount, BFCBO::INIT_TO_DEFAULT,      0}, 
   {ifds::SettleCurrency, BFCBO::INIT_TO_DEFAULT,   0}, 
   {ifds::DistribDetlVer, BFCBO::INIT_TO_DEFAULT,   0}, 
   {ifds::DistribDetlRid, BFCBO::INIT_TO_DEFAULT,   0}, 
   {ifds::Level, BFCBO::INIT_TO_DEFAULT,            0}, 
   {ifds::AllocAccountNum, BFCBO::INIT_TO_DEFAULT,  0}, 
   {ifds::ToFundNumber, BFCBO::NONE,                0}, 
   {ifds::Default, BFCBO::NONE,                     0}, 
   {ifds::SplitComm, BFCBO::NONE,                   0}, 
   //cross-edit
   {ifds::FundClass,   BFCBO::IMMEDIATE_VALIDATION, 0}, 
	{ifds::FundClassTradeDate, BFCBO::NONE,              0}, 
    {ifds::ToSoftCapCheck, BFCBO::NONE,                  0}, 
};

static const int NUM_FIELDS = sizeof(classFieldInfo) / sizeof(BFCBO::CLASS_FIELD_INFO);

//******************************************************************************
AutoTransAllocation::AutoTransAllocation(BFAbstractCBO &parent) 
: MFCanBFCbo(parent), 
_bInitialSplitComm(false), 
_pSystematic(NULL),
_pAutoAcctTransAllocation(NULL)
{
   TRACE_CONSTRUCTOR(CLASSNAME , NULL_STRING);

   registerMemberData(NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL);
   addCrossEdit(ifds::FundClass, ifds::FundCode);
   addCrossEdit(ifds::FundClass, ifds::ClassCode);

	 //cross edit for Fund, Class, AccountNum and EffectiveDate
   addCrossEdit(ifds::FundClassTradeDate, ifds::FundCode);
   addCrossEdit(ifds::FundClassTradeDate, ifds::ClassCode);
   addCrossEdit(ifds::FundClassTradeDate, ifds::AccountNum);
   addCrossEdit(ifds::FundClassTradeDate, ifds::EffectiveDate);

   addCrossEdit(ifds::ToSoftCapCheck, ifds::FundCode);
   addCrossEdit(ifds::ToSoftCapCheck, ifds::ClassCode);
   addCrossEdit(ifds::ToSoftCapCheck, ifds::AccountNum);
   addCrossEdit(ifds::ToSoftCapCheck, ifds::EffectiveDate);
}

//******************************************************************************
AutoTransAllocation::~AutoTransAllocation(void)
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
SEVERITY AutoTransAllocation::init()
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AutoTransAllocation::init(const BFData &viewData)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   //attach the data object
   attachDataObject(const_cast<BFData&>(viewData), false, true);

   //set the fund number
   DString fundCode, classCode, fundNumber;

   fundCode = viewData.getElementValue(ifds::FundCode);
   classCode = viewData.getElementValue(ifds::ClassCode);
   getWorkSession().GetFundNumber(fundCode.strip().upperCase(), 
      classCode.strip().upperCase(), fundNumber);
   setFieldNoValidate(ifds::ToFundNumber, fundNumber, BF::HOST);
   _bInitialSplitComm = STRING_Y == viewData.getElementValue(ifds::SplitComm);
   // Init the Default field to No      
   setFieldNoValidate(ifds::Default, STRING_N, BF::HOST);
   if (SplitCommission::isTypeZERO(getWorkSession()))
   {
      setFieldNoValidate(ifds::SplitComm, STRING_N, BF::HOST);
   }
   clearUpdatedFlags(BF::HOST);
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void AutoTransAllocation::getField(const BFFieldId& idField, DString &dstrFieldValue, 
                                    const BFDataGroupId& idDataGroup, bool formattedReturn) const
{
   BFCBO::getField(idField, dstrFieldValue, idDataGroup, formattedReturn);
   if (idField == ifds::AllocAmount && formattedReturn)
   {
      BFCBO::getField(idField, dstrFieldValue, idDataGroup, false);
      getSystematicPtr()->getFormattedAmount(idDataGroup,dstrFieldValue);
   }
   else if (idField == ifds:: Percentage || idField == ifds::AllocAccountNum)
   {
      dstrFieldValue.stripLeading('+');
   } 
   else if (idField == ifds::SplitComm)
   {
      //funky...!
      AutoTransAllocationList *pAutoTransAllocationList = 
         dynamic_cast<AutoTransAllocationList*>(const_cast<BFCBO*>(getParent()));

      //this method will set the split comm flag to N if we have more then one 
      //elements in the parent allocation list, 
      //this is due to the fact that the back-end doesn't support split commissions
      //for allocated Auto Transfers (Serban P June, 2003)
      if (pAutoTransAllocationList && 
         pAutoTransAllocationList->getNbrOfAllocInList(idDataGroup) > 1)
      {
         dstrFieldValue = I_("N");
      }
   }
   else if (idField == ifds::AccountTo)
   {
      _pAutoAcctTransAllocation->getField(ifds::AllocAccountNum, dstrFieldValue, idDataGroup, false);
   }
}
//*****************************************************************************
void AutoTransAllocation::setParameter(DString& Acct, DString& FundCode, DString& ClassCode, DString& strAmount)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("setParameter"));

   setFieldNoValidate (ifds::ClassCode, NULL_STRING, BF::HOST, false, false, false, false);
   setFieldNoValidate (ifds::FundCode, NULL_STRING, BF::HOST, false, false, false, false);

   setFieldNoValidate (ifds::ClassCode, ClassCode, BF::HOST, false, false, true);
   setFieldNoValidate (ifds::FundCode, FundCode, BF::HOST, false, false, true);
   setFieldNoValidate (ifds::AllocAccountNum, Acct, BF::HOST, false, false, true);                                             
   setFieldNoValidate (ifds::AllocAmount, strAmount, BF::HOST, false, false, true);                                             
}

//******************************************************************************
SEVERITY AutoTransAllocation::doValidateField(const BFFieldId& idField,
                                               const DString& strValue,
                                               const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField"));
   DString dstr(strValue);

   dstr.strip();
   if(!dstr.empty())
   {
      getSystematicPtr()->setObjectAsNew();
   }
   if(idField == ifds::FundCode)
      validateFundCode(strValue, idDataGroup);
   else if(idField == ifds::ClassCode)
      validateClassCode(strValue, idDataGroup);
   else if(idField == ifds::Percentage)
      validatePercentage(strValue, idDataGroup);
   else if(idField == ifds::ToFundNumber)
   {
      DString dstrFundCode,dstrClassCode;
      if (!getWorkSession().GetFundClassCode(strValue, dstrFundCode, dstrClassCode))
      {
         ADDCONDITIONFROMFILE(CND::ERR_INVALID_FUND_NUMBER);
      }
   }
   else if (idField == ifds::FundClass)
   {
      validateFundClass(idDataGroup);
   } else if ( idField == ifds::AllocAmount ) {
      DString dstrFundCode;
      getField ( ifds::FundCode, dstrFundCode, idDataGroup );
		dstrFundCode.strip().upperCase();
      if ( _pSystematic->isCappedFund ( dstrFundCode, idDataGroup ) ) {
         DString dstrOriAmount,dstrOriFund;
         getField ( ifds::AllocAmount,dstrOriAmount, BF::HOST );
			getField( ifds::FundCode, dstrOriFund,BF::HOST,false );
			dstrOriFund.strip().upperCase();
			if(dstrOriFund == dstrFundCode )
			{
				_pSystematic->ValidateCappedAmt ( dstrOriAmount, strValue, idDataGroup );
			}        
      }
   }
   else if (idField == ifds::FundClassTradeDate)
   {
       validateFundClassAccNumDate ( idDataGroup );
   }
   else if (idField == ifds::ToSoftCapCheck)
   {
       validateToFundClassSoftCapped(idDataGroup);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AutoTransAllocation::validateFundClassAccNumDate ( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundClassAccNumDate" ) );
	
   // if SegClient and CotClient do the SegFundValidation
	DString strSegClient, strCotClient;
   getWorkSession().getOption(ifds::SegClient, strSegClient, BF::HOST );
   getWorkSession().getOption(ifds::CotClient, strCotClient, BF::HOST );

	if( (strSegClient.strip() == STRING_Y && strCotClient.strip() == STRING_Y ))
   {
		
		DString dstrAcctNum, dstrFundCode, dstrClassCode, dstrEffectiveDate;
		
		_pSystematic->getField (ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false);
		//_pSystematic->getField (ifds::AccountTo, dstrAcctNum, idDataGroup, false);

		AutoAcctTransAllocation *pAutoAcctTransAllocation;
		pAutoAcctTransAllocation = static_cast <AutoAcctTransAllocation*> (getParent()->getParent());
      pAutoAcctTransAllocation->getField (ifds::AllocAccountNum, dstrAcctNum, idDataGroup, false);


		getField (ifds::FundCode, dstrFundCode, idDataGroup, false);
      getField (ifds::ClassCode, dstrClassCode, idDataGroup, false);


		SeqFundValidation *pSeqFundValidation = NULL;

		if( _pSystematic->getSeqFundValidation( pSeqFundValidation, idDataGroup, dstrFundCode, dstrClassCode, dstrAcctNum, dstrEffectiveDate ) 
			<= WARNING && pSeqFundValidation )
		{
			pSeqFundValidation->addSegFundValidationWarnings( idDataGroup );
		}

		 //_pSystematic->segFundValidation( idDataGroup, dstrFundCode, dstrClassCode, dstrAcctNum, dstrEffectiveDate ); 
		
   }
   
   DString dstrFromFundCode, dstrFromClassCode;
   _pSystematic->getField (ifds::FundCode, dstrFromFundCode, idDataGroup, false);
   _pSystematic->getField (ifds::ClassCode, dstrFromClassCode, idDataGroup, false);
   
   AutoTransAllocationList* pAutoTransAllocationList;
	_pAutoAcctTransAllocation->getAtAllocationList(pAutoTransAllocationList);
	
	BFObjIter iter(*pAutoTransAllocationList, idDataGroup);
	iter.begin();
	while ( !iter.end() )
	{
	   DString dstrIterFundToCode, dstrIterClassToCode;
	   
	   iter.getObject()->getField( ifds::FundCode, dstrIterFundToCode, idDataGroup, false );
	   iter.getObject()->getField( ifds::ClassCode, dstrIterClassToCode, idDataGroup, false );
	   	   
	   // if fundfrom/classfrom are NOT equal with fundto/classto, must have validation
	   if (!( dstrFromFundCode.strip().upperCase() == dstrIterFundToCode.strip().upperCase() &&
	          dstrFromClassCode.strip().upperCase() == dstrIterClassToCode.strip().upperCase() )
	      )
	   {
	      // get MFAccount
	      DString dstrAccountTo;
	      _pAutoAcctTransAllocation->getField(ifds::AllocAccountNum, dstrAccountTo, idDataGroup, false);
	      
	      MFAccount *pMFAccount = NULL;
                 
         if ( getWorkSession().getMFAccount ( idDataGroup, 
                                              dstrAccountTo, 
                                              pMFAccount) <= WARNING && pMFAccount)
         {
            DString dstrIsClosedCountryResident;
            pMFAccount->getField( ifds::IsClosedCountryResident, dstrIsClosedCountryResident, idDataGroup, false );  
         
            if ( dstrIsClosedCountryResident.strip().upperCase() == YES )
            {
               // Raise error message, No Customizing Service allowed for closed country resident.
               DString idiStr;
               addIDITagValue (idiStr, I_("TRADETYPE"), I_("Customizing Service"));    
               ADDCONDITIONFROMFILEIDI (CND::ERR_CLOSED_COUNTRY_RESIDENT_FOR_MONEY_IN , idiStr);
            } // end if closecountry == yes   
   
         } // end if getMFAccount()           
	   }
	
	   ++iter;
	}
 
      
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AutoTransAllocation::doValidateAll(const BFDataGroupId& idDataGroup, long lValidateGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("doValidateAll"));

   //To ensure the error message will be shown in the popup as well
   validateToFundClassSoftCapped(idDataGroup);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void AutoTransAllocation::validateFundCode(const DString& strValue,
   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("ValidateFundCode"));
   DString dstrFundCode(strValue);

   dstrFundCode.strip().upperCase();
   if(dstrFundCode == I_("CASH"))
      return;
   if(dstrFundCode.empty())
   {
      ADDCONDITIONFROMFILE(CND::ERR_BLANK_FUND);
      return;
   }

   FundMasterList *pFundMasterList;

   if (getMgmtCo().getFundMasterList(pFundMasterList) <= WARNING && pFundMasterList)
   {
      if (pFundMasterList->IsFundExist(dstrFundCode, idDataGroup) == false)
      {
         ADDCONDITIONFROMFILE(CND::ERR_INVALID_FUND_CLASS_CODES);
      }
      else
      {
         DString dstrEffectiveDate;
         getSystematicPtr()->getField(ifds::EffectiveDate, dstrEffectiveDate, idDataGroup);
         dstrEffectiveDate.strip();
         if (pFundMasterList->IsFundValidAtDate(dstrFundCode, dstrEffectiveDate, idDataGroup) == false)
         {
            DString msg(I_("FUNDNAME="));
            msg += dstrFundCode;
            ADDCONDITIONFROMFILEIDI(CND::ERR_FUND_NOT_EFFECTIVE, msg.c_str());
         }
         else
         {
            FundMaster *pFundMaster = NULL;
            if (pFundMasterList->getFundMaster (dstrFundCode, idDataGroup, pFundMaster))
            {
               if( pFundMaster && pFundMaster->isCappedFund ( dstrEffectiveDate, idDataGroup ) )              
			      {
                  long errorConID (CND::ERR_CAPPEDFUND_STATUSE);
                  long warningConID (CND::ERR_CAPPEDFUND_STATUSW);
                  DString dstrFund;
                  getField ( ifds::FundToCode, dstrFund, idDataGroup );
                  DString idiStr(NULL_STRING);
                  addIDITagValue( idiStr, I_( "FUND" ), dstrFund );
                  getSystematicPtr()->getErrMsg( I_("358"), errorConID, warningConID, idDataGroup, idiStr );
               }
            }
         }
      }
   }
}

//******************************************************************************
void AutoTransAllocation::validateClassCode(const DString& strValue,
   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("ValidateClassCode"));

   DString dstrClassCode(strValue);
   dstrClassCode.strip().upperCase();
   if(dstrClassCode.empty())
   {
      ADDCONDITIONFROMFILE(CND::ERR_BLANK_CLASS);
      return;
   }

   DString dstrFundCode;
   getField(ifds::FundCode, dstrFundCode, idDataGroup);
   dstrFundCode.strip().upperCase();
   if(dstrFundCode == I_("CASH"))
   {
      if(dstrClassCode != I_("A"))
         ADDCONDITIONFROMFILE(CND::ERR_INVALID_FUND_CLASS_CODES);
      return;
   }
   if(dstrFundCode.empty())
   {
      ADDCONDITIONFROMFILE(CND::ERR_INVALID_FUND_CLASS_CODES);
      return;
   }

   /* W.Shiu Feb 24,2003
   should get the AccounTo number. GetParent will get the AccountFrom rather than the AccounTo. 
   Check canTrade FundTo and ClassTo against the AccounTo    

   MFAccount *pMFAccount = dynamic_cast< MFAccount *>(
                                                     getSystematicPtr()->getParent()->getParent());
   */

   MFAccount *pMFAccount=NULL;
   DString dstrAccountTo;

   Systematic *pSystematic = getSystematicPtr();      

   if (pSystematic)
   {
      pSystematic->getField (ifds::AccountTo, dstrAccountTo, idDataGroup);
      
      SEVERITY sevRtn = getWorkSession().getMFAccount(idDataGroup, dstrAccountTo, pMFAccount);

      if (pMFAccount)
      {
         DString dstrTransType = EX_FER_IN_CODE;
         DString dstrEffectiveDate;

         pSystematic->getField(ifds::EffectiveDate, dstrEffectiveDate, idDataGroup);
         dstrEffectiveDate.strip();

         sevRtn = pMFAccount->canTradeFundClass(dstrFundCode, strValue, dstrTransType, dstrEffectiveDate, idDataGroup);
         if(sevRtn > WARNING)
         {
            setFieldNoValidate(ifds::ToFundNumber, NULL_STRING, idDataGroup, false);
            ADDCONDITIONFROMFILE(CND::ERR_INVALID_FUND_CLASS_CODES);
         }
      }
   }
}

//******************************************************************************
void AutoTransAllocation::validatePercentage(const DString& strValue,
                                              const BFDataGroupId& idDataGroup) const
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("ValidatePercentage"));

   DString dstrPercentage(strValue);
   dstrPercentage.strip();
   if(dstrPercentage.empty())
   {
      ADDCONDITIONFROMFILE(CND::ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE);
      return;
   }

   BigDecimal bdPercent = DSTCommonFunctions::convertToBigDecimal(dstrPercentage);
   BigDecimal bdHundred = DSTCommonFunctions::convertToBigDecimal(I_("100.0"));
   BigDecimal bdZero = DSTCommonFunctions::convertToBigDecimal(I_("0.0"));
  
   if (bdPercent == bdZero)
   {
      ADDCONDITIONFROMFILE (CND::ERR_VALUE_CANNOT_BE_ZERO);
   }
   else
   {
      if (bdPercent > bdHundred || bdPercent < bdZero)
      {
         ADDCONDITIONFROMFILE (CND::ERR_VALUE_BETWEEN_0_AND_100);
      }	
   }
}

//*******************************************************************************
// we are in the target item
void AutoTransAllocation::ModelOffer(AutoTransAllocation *Model, const BFDataGroupId& idDataGroup)
{
   BFData *tmp = new BFData(ifds::DSTC0007_VWRepeat_Record);

//CP	BFDataComponentProperties *dcpPtr  = NULL;

   BFDataFieldIter dIter(*tmp);
   DString str;
   for(;dIter; ++dIter)
   {
      BFDataField& idField = dIter();
//CP      dcpPtr = const_cast< BFDataComponentProperties * >(dIter().getProperties());
//CP      dcpPtr->getId(idField);
      Model->getField(idField.getId(), str, idDataGroup);
      setFieldNoValidate(idField.getId(), str, idDataGroup, false);
   };
   clearUpdatedFlags(idDataGroup);

   delete tmp;
}

//*******************************************************************************
SEVERITY AutoTransAllocation::doApplyRelatedChanges(const BFFieldId& idField, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));

   AutoAcctTransAllocation *pAutoAcctTransAllocation;

   pAutoAcctTransAllocation = static_cast <AutoAcctTransAllocation*> (getParent()->getParent());
   if(idField == ifds::FundCode)
   {
      DString dstrFundCode;
      getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
      dstrFundCode.strip().upperCase();
      if(dstrFundCode == I_("CASH"))
		{
         setFieldNoValidate(ifds::ClassCode, I_("A"), idDataGroup, false, false, true);
		}
		else
      {
         DString dstrClassCode;
         getField (ifds::ClassCode, dstrClassCode, idDataGroup, false);
         if((!dstrFundCode.empty()) && (!dstrClassCode.empty()))
			{
            setFundNumber (idField, idDataGroup);			
			}
			Systematic *pSystematic = dynamic_cast< Systematic * >(getParent()->getParent()->getParent()->getParent() );
			if( !dstrFundCode.empty() )
			{
				if( pSystematic->isCappedFund( dstrFundCode, idDataGroup ) )
				{
					setValidFlag( ifds::AllocAmount,idDataGroup,false );				
				}		
			}
		}
   }
   else if(idField == ifds::ClassCode)
   {
      DString dstrFundCode;
      getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
      dstrFundCode.strip().upperCase();
      if(dstrFundCode != I_("CASH") && !dstrFundCode.empty())
         setFundNumber(idField,idDataGroup);
   }
   else if(idField == ifds::ToFundNumber)
   {
      setFundClassCode(idField,idDataGroup);
   }
   else if(idField == ifds::Percentage)
   {
      DString dstrTotalAmount;
      
      pAutoAcctTransAllocation->getField(ifds::AllocAmount, dstrTotalAmount, idDataGroup, false);

      double dTotalAmount = DSTCommonFunctions::convertToDouble(dstrTotalAmount);
      if(dTotalAmount <= .00000000001)
         return(GETCURRENTHIGHESTSEVERITY());
      DString dstrPercentage;
      getField (ifds::Percentage, dstrPercentage, idDataGroup, false);
      double dPercentage = DSTCommonFunctions::convertToDouble(dstrPercentage);
      double dAmount = dTotalAmount * dPercentage / 100; 
      DString dstrAmount = DSTCommonFunctions::doubleToDString(ifds::AllocAmount,dAmount);
      dstrAmount.strip().stripAll(I_CHAR(','));
      getSystematicPtr()->getFormattedAmount(idDataGroup,dstrAmount);
		setFieldNoValidate(ifds::AllocAmount, dstrAmount, idDataGroup,true,true,true,false );

   }
   else if(idField == ifds::AllocAmount)
   {
      DString dstrTotalAmount;

      pAutoAcctTransAllocation->getField(ifds::AllocAmount, dstrTotalAmount,idDataGroup, false); 

      double dTotalAmount = DSTCommonFunctions::convertToDouble(dstrTotalAmount);
      if(dTotalAmount <= .00000000001)
         return(GETCURRENTHIGHESTSEVERITY());
      DString dstrAmount;
      getField (ifds::AllocAmount, dstrAmount, idDataGroup, false);
      double dAmount = DSTCommonFunctions::convertToDouble(dstrAmount);
      double dPercentage = dAmount / dTotalAmount * 100; 
      DString dstrPercentage  = DSTCommonFunctions::doubleToDString(ifds::Percentage,dPercentage);
		setFieldNoValidate(ifds::Percentage, dstrPercentage, idDataGroup,true,true,true,false );


  //    BFCBO::setField(ifds::Percentage, dstrPercentage, idDataGroup, false, true);
      //
      //we should look if this auto trans allocation has split commission list,
      //and if it has we should change the commission amounts and rates;
      //do not create the split commission list if it doesn't exist
      SplitCommissionList* pSplitCommissionList = NULL;

      if (getSplitCommissionList(pSplitCommissionList, idDataGroup) <= WARNING && 
            pSplitCommissionList)
      {
         //DString dstrAmount;
         //getField(idField, dstrAmount, idDataGroup);
         pSplitCommissionList->setField(ifds::Amount, dstrAmount, idDataGroup);
      }
   }

   if ((idField == ifds::FundCode || idField == ifds::ClassCode || idField == ifds::EffectiveDate || idField == ifds::AccountNum) &&
       isFieldUpdated(idField, idDataGroup))
   {
       revalidateField(ifds::ToSoftCapCheck, idDataGroup);
   }

   //If any fields are changed, fund/class must be revalidated against soft capped.
   AutoTransAllocationList *pAutoTransAllocationList = NULL;
   pAutoTransAllocationList = dynamic_cast<AutoTransAllocationList*>(getParent());

   if (pAutoTransAllocationList && isFieldUpdated(idField, idDataGroup))
       pAutoTransAllocationList->setAllAllocsFndClsValidFlag(false, idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
}

//*******************************************************************************
void AutoTransAllocation::setFundClassCode(const BFFieldId& idField,const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("setFundClassCode"))
   DString dstrFundNumber,dstrFundCode,dstrCalssCode;

   getField(ifds::ToFundNumber, dstrFundNumber, idDataGroup,false);

   if(dstrFundNumber.strip() != NULL_STRING)
   {
      if(getWorkSession().GetFundClassCode(dstrFundNumber,dstrFundCode, dstrCalssCode))
      {
         DString oldFundCode, oldClassCode;
         getField(ifds::FundCode, oldFundCode, idDataGroup, false);
         getField(ifds::ClassCode, oldClassCode, idDataGroup, false);
         if(oldFundCode.upperCase() != dstrFundCode.upperCase())
            setFieldNoValidate(ifds::FundCode, dstrFundCode, idDataGroup, false,true,true);
         if(oldClassCode.upperCase() != dstrCalssCode.upperCase())
            setFieldNoValidate(ifds::ClassCode, dstrCalssCode, idDataGroup, false,true,true);
         // set FundClass Invalid
         setCrossEditInvalid(ifds::FundCode, idDataGroup);
         setCrossEditInvalid(ifds::ClassCode, idDataGroup);
      }
   }
}

//*****************************************************************************
void AutoTransAllocation::setFundNumber(const BFFieldId& idField,const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("setFundNumber"))
   DString dstrFundNumber, dstrFundCode, dstrCalssCode, dstrTransType, dstrSplitComm;

   getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
   getField(ifds::ClassCode, dstrCalssCode, idDataGroup, false);
   dstrFundCode.strip().upperCase();
   dstrCalssCode.strip().upperCase();
   getWorkSession().GetFundNumber(dstrFundCode, dstrCalssCode, dstrFundNumber);
   DString oldFundNumber;

   getField(ifds::ToFundNumber, oldFundNumber, idDataGroup, false);
   if(oldFundNumber.strip() != dstrFundNumber)
      setFieldNoValidate(ifds::ToFundNumber, dstrFundNumber, idDataGroup, false,true,true);

   // Split Commission flag is set here because Fund Code and Class Code should exists before 
   // fund number can be retrieved
   if(splitCommActive (idDataGroup))
   {
      setFieldNoValidate(ifds::SplitComm, STRING_Y, idDataGroup, false,true,true);  
      GetDefaultSplitComm (idDataGroup);
   }
   else
   {
      setFieldNoValidate(ifds::SplitComm, STRING_N, idDataGroup, false,true,true);  
      setFieldNoValidate(ifds::Default, STRING_N, idDataGroup, false);   
   }
}

//********************************************************************************
void AutoTransAllocation::validateFundClass(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("ValidateFundClass"));

   DString FundCode, FundToCode, ClassCode, ClassToCode, AccountNum, dstrAccountTo, dstrAccountFrom;
   //getsystematic CBO, so we can get from fundcode and classcode 
   Systematic *pSystematic = getSystematicPtr();  
   MFAccount *pMFAccountFrom = NULL;

   pSystematic->getField(ifds::FundCode,FundCode,idDataGroup,false);
   FundCode.strip().upperCase();
   pSystematic->getField(ifds::ClassCode,ClassCode,idDataGroup,false);
   ClassCode.strip().upperCase();

   // current FundCode and Class Code is transfer to

   getField(ifds::FundCode,FundToCode,idDataGroup,false);
   FundToCode.strip().upperCase();
   getField(ifds::ClassCode,ClassToCode,idDataGroup,false);
   ClassToCode.strip().upperCase();

   if(FundCode.empty() || ClassCode.empty() || ClassToCode.empty() || FundToCode.empty())
      return;

	FundToList fundToList( *this );
	bool bAllowTransfer = fundToList.isTransferAllowed(FundCode,
					ClassCode,FundToCode,ClassToCode );
	if( !bAllowTransfer )	
	{
		DString idiStr;
		addIDITagValue(idiStr, I_("FIELD1"), FundCode);
		addIDITagValue(idiStr, I_("FIELD2"), ClassCode);
		addIDITagValue(idiStr, I_("FIELD3"), FundToCode);
		addIDITagValue(idiStr, I_("FIELD4"), ClassToCode);
		ADDCONDITIONFROMFILEIDI(CND::ERR_AT_FUNDCLASS_TRANSFER_NOT_ALLOWED,idiStr);             
		return;
	}

      DString dstrEffectiveDate, dstrTransType;
      pSystematic->getField(ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false);
      dstrEffectiveDate.strip();

      //DString dstrTransTypeParam;

      //dstrTransTypeParam = EX_FER_IN_CODE;

      /* W.Shiu Oct 13,2002
         should get the AccounTo number. GetParent will get the AccountFrom rather than the AccounTo. 
         Check canTrade FundTo and ClassTo against the AccounTo    
      MFAccount *pMFAccount = dynamic_cast< MFAccount *>(getSystematicPtr()->getParent()->getParent());
      pMFAccount->canTradeFundClass (FundToCode, ClassToCode, EX_FER_IN_CODE, dstrEffectiveDate, idDataGroup);*/

      // W.Shiu Oct 13, 2002 : Use this logic instead 
      MFAccount *mfAccount=NULL;
      //pSystematic->getField(ifds::AccountTo, dstrAccountTo, idDataGroup)
      _pAutoAcctTransAllocation->getField(ifds::AllocAccountNum, dstrAccountTo, idDataGroup, false);;

	   SEVERITY sevRtn = getWorkSession().getMFAccount(idDataGroup, dstrAccountTo, mfAccount);
      
      if (mfAccount)
      {
         sevRtn = mfAccount->canTradeFundClass (FundToCode, ClassToCode, EX_FER_IN_CODE, dstrEffectiveDate, idDataGroup);
      }
      
      // W.Shiu Jan 12, 2003 - Stop Flag check missing
      if (pSystematic && sevRtn <= WARNING) 
      {
         sevRtn= pSystematic->stopFlagCheck(FundToCode, ClassToCode, I_("ATI"), idDataGroup);
      }

      // broker fund logic for ticket 10009829 : check broker fund validation against the ToFund/ToClass using the broker of AccountTO as per E&P's request
      if (pSystematic)
      {   
         bool bBrokerFundOk (false), bSlsrepFundOk (false);
         bBrokerFundOk = pSystematic->validBrokerFund (TOFUND, FundToCode, ClassToCode, idDataGroup);
         bSlsrepFundOk = pSystematic->validSalesrepFund (TOFUND, FundToCode, ClassToCode, idDataGroup);

         if (!bBrokerFundOk ) // failed in edit check for fund/class code against the broker
         {
            ADDCONDITIONFROMFILE(CND::ERR_FUND_CLASS_NOT_AVAILABLE_FOR_BROKER);
         }
         if (!bSlsrepFundOk)
         {
            DString idiStr;
            addIDITagValue(idiStr, FUND, FundToCode);
            addIDITagValue(idiStr, CLASS, ClassToCode);

            ADDCONDITIONFROMFILEIDI(CND::ERR_FUND_CLASS_NOT_AVAILABLE_FOR_SALESREP, idiStr);
         }
      }

      validateToFundClassSoftCapped(idDataGroup);

//   validateAllocCurrency(FundToCode, ClassToCode, idDataGroup);

}

//******************************************************************************
SEVERITY AutoTransAllocation::validateToFundClassSoftCapped(const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateToFundClassSoftCapped"));

    DString FundCode, FundToCode, ClassCode, ClassToCode, AccountNum, dstrAccountTo, dstrAccountFrom;

    Systematic *pSystematic = NULL; 
    MFAccount *pMFAccountFrom = NULL;
    DString dstrEffectiveDate, dstrTransType;

    pSystematic = getSystematicPtr(); 
    _pAutoAcctTransAllocation->getField(ifds::AllocAccountNum, dstrAccountTo, idDataGroup, false);;

    getField(ifds::FundCode,FundToCode,idDataGroup,false);
    FundToCode.strip().upperCase();
    getField(ifds::ClassCode,ClassToCode,idDataGroup,false);
    ClassToCode.strip().upperCase();

    if (pSystematic)
    {   
        pSystematic->getField(ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false);
        pSystematic->getField(ifds::FundCode,FundCode,idDataGroup,false);
        FundCode.strip().upperCase();
        pSystematic->getField(ifds::ClassCode,ClassCode,idDataGroup,false);
        ClassCode.strip().upperCase();

        pSystematic->getField(ifds::TransType, dstrTransType, idDataGroup);
        pMFAccountFrom = dynamic_cast<MFAccount*>(pSystematic->getParent()->getParent());  

        if (pMFAccountFrom)
            pMFAccountFrom->getField(ifds::AccountNum, dstrAccountFrom, idDataGroup, false);

        bool isTransfer = !dstrAccountFrom.empty() && !dstrAccountTo.empty() && 
            !FundCode.empty() && !ClassCode.empty() &&
            !FundToCode.empty() && !ClassToCode.empty() &&
            dstrAccountFrom != dstrAccountTo &&
            FundCode == FundToCode &&
            ClassCode == ClassToCode;

        if (dstrTransType == I_("AT") && !isTransfer) // Validate soft capped if AT and Twitch/Exchange.
        {
            getWorkSession().fundClassSoftCappedCheck(dstrAccountTo, FundToCode, ClassToCode, I_("ED"), dstrEffectiveDate, idDataGroup);
        }
    }

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AutoTransAllocation::getSplitCommissionList(SplitCommissionList *&rpSplitCommissionList,
   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getSplitCommissionList"));

   rpSplitCommissionList = dynamic_cast<SplitCommissionList*> (BFCBO::getObject(SPLITCOM_LIST, idDataGroup));
   //If the Commission Type is 0, then there is no split commission
   if (SplitCommission::isTypeZERO(getWorkSession()))
   {
      // The delete is necessary to prevent the transaction builder from calling hasTransactionUpdate() check 
      if (rpSplitCommissionList)
      {
         delete rpSplitCommissionList;
      }
      rpSplitCommissionList = NULL;
   }
   else
   {
      SEVERITY severity = NO_CONDITION;
         //always fetch the split list if it was suppose to be there in the beginning
      if (!rpSplitCommissionList && _bInitialSplitComm)
      {
         severity = fetchSplitCommisionListUsingSystematicParent(rpSplitCommissionList, idDataGroup);
      }
      if (severity <= WARNING) //if okay, process further
      {
         DString dstrSplitComm, dstrDefault;

         getField(ifds::SplitComm, dstrSplitComm, idDataGroup, false);
         getField(ifds::Default, dstrDefault, idDataGroup);
         if (dstrSplitComm != STRING_Y) //split comm flag set to No
         {
            if (_bInitialSplitComm)
            {
               //if the fund had split commission but changed to a fund with no split commission, 
               //we need to send the deleted split commission in the transaction builder
               rpSplitCommissionList->deleteSplitCommList(idDataGroup);
            }
         }
         else //the split comm flag is set to Yes
         {
            if (!rpSplitCommissionList)
            {
               if (dstrDefault == STRING_N) //there is no default split commission list
               {
                  fetchSplitCommisionListUsingSystematicParent(rpSplitCommissionList, idDataGroup);
               }
               else if (dstrDefault == STRING_Y && !rpSplitCommissionList) //call the default split commission view, 158
               {
                  DString AccountNum, AccountTo, Fund, FundTo, Class, ClassTo;
                  DString PUD, FlatPrcnt, InPayType, IAmount, InTransType, EffectiveDate;
                  DString InGrossNet, BrokerCode, BranchCode, SlsRepCode, SettleCurrency;
                  MFAccount *pMFAccount = dynamic_cast< MFAccount *>(_pSystematic->getParent()->getParent());
      
                  AutoAcctTransAllocation *pAutoAcctTransAllocation;

                  pAutoAcctTransAllocation = static_cast <AutoAcctTransAllocation*> (getParent()->getParent());
                  pAutoAcctTransAllocation->getField (ifds::AllocAccountNum, AccountTo, idDataGroup, false);
                  pMFAccount->getField (ifds::AccountNum, AccountNum, idDataGroup, false);
                  pMFAccount->getField (ifds::BrokerCode, BrokerCode, idDataGroup, false);
                  pMFAccount->getField (ifds::BranchCode, BranchCode, idDataGroup, false);
                  pMFAccount->getField (ifds::Slsrep, SlsRepCode, idDataGroup, false);
                  _pSystematic->getField (ifds::AmountType, PUD, idDataGroup, false);
                  _pSystematic->getField (ifds::FlatPercent, FlatPrcnt, idDataGroup, false);
                  _pSystematic->getField (ifds::PayType, InPayType, idDataGroup, false);
                  _pSystematic->getField (ifds::TransType, InTransType, idDataGroup, false);
                  _pSystematic->getField (ifds::EffectiveDate, EffectiveDate, idDataGroup, false);
                  _pSystematic->getField (ifds::GrossOrNet, InGrossNet, idDataGroup, false);
                  _pSystematic->getField (ifds::SettleCurrency, SettleCurrency, idDataGroup, false);                                                                       
                  _pSystematic->getField (ifds::FundCode, Fund, idDataGroup, false);
                  _pSystematic->getField (ifds::ClassCode, Class, idDataGroup, false);
                  getField(ifds::AllocAmount, IAmount, idDataGroup, false);
                  getField(ifds::FundCode, FundTo, idDataGroup, false);
                  getField(ifds::ClassCode, ClassTo, idDataGroup, false);
                  rpSplitCommissionList = new SplitCommissionList(*this);
                  //call the default split commission view
                  if (rpSplitCommissionList->init (AccountNum, AccountTo, Fund, 
                           FundTo, Class, ClassTo, PUD, FlatPrcnt, InPayType, IAmount, InTransType, 
                           EffectiveDate, InGrossNet, BrokerCode, BranchCode, SlsRepCode, 
                           SettleCurrency, NULL_STRING, //record type
                           I_("0.0"),  // exchange rate for autoallocation should be 0.0
                           NULL_STRING,NULL_STRING,NULL_STRING,
                           idDataGroup) <= WARNING)
                  {
                     //set the split list object
                     setObject(rpSplitCommissionList, SPLITCOM_LIST, OBJ_ACTIVITY_NONE, idDataGroup);
                     //clear the default flag
                     setFieldNoValidate(ifds::Default, STRING_N, idDataGroup, false);
                     if (!rpSplitCommissionList->hasSplits())
                     {
                        setField (ifds::SplitComm, STRING_N, idDataGroup, false);
                     }
                  }
                  else
                  {
                     delete rpSplitCommissionList;
                     rpSplitCommissionList = NULL;
                  }
               }
            }
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AutoTransAllocation::fetchSplitCommisionListUsingSystematicParent(
   SplitCommissionList *&rpSplitCommissionList, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("initSplitCommisionList"));

   DString dstrTransNum, dstrTransSeq, dstrAccountNum, dstrTransType, dstrFund, 
      dstrClass, dstrBrokerCode, dstrBranchCode, dstrSalesRepCode, dstrEffectiveDate;

   // If the split has never been downloaded.
   if(!rpSplitCommissionList && _pSystematic)
   {
      _pSystematic->getField(ifds::TransNum, dstrTransNum, idDataGroup, true);
      _pSystematic->getField(ifds::TransType, dstrTransType, idDataGroup, true);
      //_pSystematic->getField(ifds::AccountNum, dstrAccountNum, idDataGroup, true);
      AutoAcctTransAllocation *pAutoAcctTransAllocation;

      pAutoAcctTransAllocation = static_cast <AutoAcctTransAllocation*> (getParent()->getParent());
      pAutoAcctTransAllocation->getField (ifds::AllocAccountNum, dstrAccountNum, idDataGroup, false);
      getField(ifds::FundCode, dstrFund, idDataGroup, true);
      getField(ifds::ClassCode, dstrClass, idDataGroup, true);
      _pSystematic->getField(ifds::BrokerCode, dstrBrokerCode, idDataGroup, true);
      _pSystematic->getField(ifds::BranchCode, dstrBranchCode, idDataGroup, true);
      _pSystematic->getField(ifds::SalesRepCode, dstrSalesRepCode, idDataGroup, true);
      _pSystematic->getField(ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, true);
      getField(ifds::TransSeq, dstrTransSeq, idDataGroup, true);
      rpSplitCommissionList = new SplitCommissionList(*this);
      //calls view 151
      if (rpSplitCommissionList->init(dstrTransNum, dstrTransSeq, dstrTransType, dstrAccountNum,
         dstrFund, dstrClass, dstrBrokerCode, dstrBranchCode, dstrSalesRepCode, dstrEffectiveDate,NULL_STRING) <= WARNING)
      {
         setObject(rpSplitCommissionList, SPLITCOM_LIST, OBJ_ACTIVITY_NONE, idDataGroup); 
      }
      else
      {
         delete rpSplitCommissionList;
         rpSplitCommissionList = NULL;
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void AutoTransAllocation::GetDefaultSplitComm(const BFDataGroupId& idDataGroup)
{   
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("GetDefaultSplitComm"));

   setFieldNoValidate(ifds::Default, I_("Y"), idDataGroup, false);   
}



//******************************************************************************
SEVERITY AutoTransAllocation::validateAllocCurrency(DString dstrFundCode, DString dstrClassCode, const BFDataGroupId& idDataGroup) 
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateAllocCurrency"));

   DString dstrmultiCurrency;
   getWorkSession().getOption(ifds::MultiCurrency, dstrmultiCurrency,
                               idDataGroup, false);

   if(dstrmultiCurrency == STRING_N)
   {
      int nNbrOfItemsInList = 0;
      AutoTransAllocationList *pParent = dynamic_cast<AutoTransAllocationList *>(getParent());
      if(pParent)
         nNbrOfItemsInList = pParent->getNbrOfAllocInList(idDataGroup);

      FundDetail *pFundDetail = NULL;

      if(getWorkSession().getFundDetail(dstrFundCode, dstrClassCode, idDataGroup, pFundDetail))
      {
         DString dstrCurrency, dstrSettleCurrency;
         pFundDetail->getField(ifds::Currency, dstrCurrency, idDataGroup, false);

         if(nNbrOfItemsInList == 1)
         {
            pParent->setField(ifds::SettleCurrency, dstrCurrency, idDataGroup, false);
         }
         else
         {
            pParent->getField(ifds::SettleCurrency, dstrSettleCurrency, idDataGroup, false);

            if(dstrSettleCurrency.strip() != dstrCurrency.strip())
            {
               ADDCONDITIONFROMFILE(CND::ERR_FUND_CURRENCY_DIFFERENT);
            }
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());

}

//******************************************************************************
bool AutoTransAllocation::splitCommActive (const BFDataGroupId& idDataGroup)
{
   bool bSplitCommActive = false;

   if(!SplitCommission::isTypeZERO(getWorkSession()))
   {
      FundDetail *pFundDetail = NULL;
      DString dstrfundCode, dstrclassCode;
    
      getField(ifds::FundCode, dstrfundCode, idDataGroup);
      getField(ifds::ClassCode, dstrclassCode, idDataGroup);

      dstrfundCode.strip().upperCase();
      dstrclassCode.strip().upperCase();

      if((!dstrfundCode.empty() && !dstrclassCode.empty())
          && getWorkSession().getFundDetail(dstrfundCode, dstrclassCode, idDataGroup, pFundDetail))
      {
         DString dstrTransType; 
         _pSystematic->getField(ifds::TransType, dstrTransType, idDataGroup, false);
         
         if ( dstrTransType == I_("AT") )
         {
            DString dstrAccountFrom, dstrAccountTo;

            MFAccount *pMFAccount = dynamic_cast< MFAccount *>(_pSystematic->getParent()->getParent()) ;
            _pSystematic->getField(ifds::AccountTo, dstrAccountTo, idDataGroup, false);      
            pMFAccount->getField (ifds::AccountNum, dstrAccountFrom, idDataGroup, false);
         
            if (dstrAccountTo != dstrAccountFrom)
               dstrTransType = I_("TR");
            else
               dstrTransType = I_("XR");
            
         }

         bSplitCommActive = pFundDetail->splitCommActive(getWorkSession(), dstrTransType, idDataGroup) ;      
      }
   }
   return bSplitCommActive;
}

//******************************************************************************
// when fields value changed in parent,
// The related fields in this CBO should be changed accordingly.
// Validation should only happen in parent CBO.

void AutoTransAllocation::parentFieldChangeNotify(const BFFieldId& fieldId,
				const BFDataGroupId& idDataGroup, 
				DString& dstrValue,
				bool bFormat)
{
   setFieldNoValidate(fieldId, dstrValue, idDataGroup,bFormat,true,true,true );
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AutoTransAllocation.cpp-arc  $
 // 
 //    Rev 1.89   Jul 26 2012 10:52:14   wp040027
 // P0198518 - RDR Functionality
 // 
 //    Rev 1.88   Jan 11 2012 15:26:46   dchatcha
 // IN# 2796443 - Validation rule for Allocated Auto Transfer
 // 
 //    Rev 1.87   Nov 27 2011 19:40:02   popescu
 // INA Commission Work
 // 
 //    Rev 1.86   Oct 25 2011 03:09:28   wichian
 // IN#2578362 - Prevent zero fund allocation percentage and replace existing validation logic with bigdecimal class.
 // 
 //    Rev 1.85   Jun 09 2009 05:40:34   kitticha
 // PET157837 FN02 - Country Schedule Daily Non Resident Schedule A
 // 
 //    Rev 1.84   Apr 29 2008 15:05:56   jankovii
 // IN 1179969 - Error messages on allocated SMART.
 // 
 //    Rev 1.83   Sep 30 2005 14:33:08   ZHANGCEL
 // PET1244 - FN01 -- uncomment the logic of involing SegFundValidation.
 // 
 //    Rev 1.82   Sep 29 2005 15:06:40   ZHANGCEL
 // PET1244 - FN01 -- Move the logic of invoking SegFundValidation to Systematic.cpp
 // 
 //    Rev 1.81   Sep 28 2005 16:19:00   ZHANGCEL
 // PET1244 - FN01 - Seg Fund Evolution enhancement
 // 
 //    Rev 1.80   May 18 2005 09:03:00   yingbaol
 // PET1203,FN01 Commission-Class A enhancement
 // 
 //    Rev 1.79   Mar 30 2005 14:37:28   popescu
 // Incident# 275373, added an extra parameter to view 151 (TransId), split commission trans history/pending trades inquiry
 // 
 //    Rev 1.78   Mar 16 2005 14:25:54   aguilaam
 // IN 265068 - auto-transfers should be properly defined as either a transfer or exchange in order to set the split commission transtype properly: transfer within same account is an 'exchange' and transfer to a different account is a 'transfer'.
 // 
 //    Rev 1.77   Jan 18 2005 16:36:46   popescu
 // PTS 10037757, should apply 'related changes' so the split commissions get initialized
 // 
 //    Rev 1.76   Nov 18 2004 13:27:56   YINGBAOL
 // PET1117: Perfermance Tunning
 // 
 //    Rev 1.75   Nov 14 2004 14:27:44   purdyech
 // PET910 - .NET Conversion
 // 
 //    Rev 1.74   Mar 05 2004 16:27:18   HERNANDO
 // PTS10026849 - Changed code for clarity.
 // 
 //    Rev 1.73   Feb 25 2004 13:14:22   YINGBAOL
 // PTS10022298: solve rounding of percentage and amount
 // 
 //    Rev 1.72   Feb 10 2004 15:59:40   YINGBAOL
 // 10021181:Validate Amount for Cap fund
 // 
 //    Rev 1.71   Feb 06 2004 16:39:16   YINGBAOL
 // PTS10026412 part 2: Add parentFieldChangeNotify method.
 // 
 //    Rev 1.70   Dec 12 2003 13:25:28   AGUILAAM
 // PTS 10024124, split comm, re-work
 // 
 //    Rev 1.69   Dec 08 2003 15:28:14   popescu
 // PTS 10023645, split commission re-work
 // 
 //    Rev 1.68   Sep 04 2003 17:08:12   HSUCHIN
 // PTS 10021181 - bug fix for capped fund rule and AT Allocations
 // 
 //    Rev 1.67   Jun 18 2003 19:00:24   popescu
 // Partial fix for 10018618
 // 
 //    Rev 1.66   Jun 11 2003 13:18:16   popescu
 // Removed unecessary GEtSplitCommissionList from the AutAccTransAllocationList level
 // 
 //    Rev 1.65   Jun 05 2003 11:20:14   popescu
 // Set SplitComm field to 'N' if AutoTransfer is allocated, PTS10017784
 // 
 //    Rev 1.64   Jun 02 2003 16:20:24   FENGYONG
 // pts10017664, 
 // 
 //    Rev 1.63   May 13 2003 19:36:14   popescu
 // PTS 10016228 & 10016241
 // 
 //    Rev 1.62   May 13 2003 17:07:02   popescu
 // Split commission re-work, part II
 // 
 //    Rev 1.61   May 13 2003 10:05:08   popescu
 // Split commission re-work
 // 
 //    Rev 1.60   May 06 2003 13:54:44   popescu
 // Fixed call to 158 for default split commission, the fund and fundto fields were sent empty
 // 
 //    Rev 1.59   Apr 29 2003 17:12:14   popescu
 // PTS 10016204
 // 
 //    Rev 1.58   Apr 14 2003 16:27:28   popescu
 // PTS 10011081- split commision amount is being calculated by the view side
 // 
 //    Rev 1.57   Apr 04 2003 15:59:02   popescu
 // split commsion work for Systematic
 // 
 //    Rev 1.56   Mar 21 2003 17:59:38   PURDYECH
 // BFDataGroupId/BFContainerId changeover
 // 
 //    Rev 1.55   Feb 25 2003 13:40:32   WINNIE
 // 10013810 : Validation should be done against the accountto rather than the account from
 // 
 //    Rev 1.54   Jan 12 2003 15:27:52   WINNIE
 // Stop flag edit check missing, invoke the one in Systematic; Modification for Broker fund validation due to new parameters required; Add logic for validation of fund against salesrep, new required for release pre-51
 // 
 //    Rev 1.53   Jan 08 2003 17:57:52   WINNIE
 // Sync up release 49.1 (1.49 and 1.50) :   broker fund logic for ticket 10009829 : edit check against accountto broker code; same logic added to AutoTransAllocation;  Also corrected logic that check if Fund/Class are valid for the Account. It should check against the AccountTo instead of AccountNum
 // 
 //    Rev 1.52   Jan 03 2003 10:39:32   HERNANDO
 // Undid changes.
 // 
 //    Rev 1.51   Jan 02 2003 18:49:08   HERNANDO
 // Check flag to determine Distribution Funds Validation.
 // 
 //    Rev 1.50   Nov 29 2002 10:21:42   KOVACSRO
 // rxTransType changes
 // 
 //    Rev 1.49   Oct 09 2002 23:54:02   PURDYECH
 // PVCS Database Conversion
 // 
 //    Rev 1.48   Sep 09 2002 13:39:28   HERNANDO
 // PTS 10009499 - Sync w/rel 47 of Stop purchase and capped fund logic.
 // 
 //    Rev 1.47   Aug 29 2002 12:55:04   SMITHDAV
 // ClientLocale and typed field changes.
 // 
 //    Rev 1.46   Jun 10 2002 16:28:06   ZHANGCEL
 // Minor changes
 // 
 //    Rev 1.45   Jun 10 2002 11:31:28   ZHANGCEL
 // PTS 10008472: bug fix regarding percentage
 // 
 //    Rev 1.44   Jun 06 2002 15:30:24   ZHANGCEL
 // Syn up to the 1.42.1.0: Bug fix for 10008340 -- fix format problem for units.
 // 
 //    Rev 1.43   22 May 2002 18:26:26   PURDYECH
 // BFData Implementation
 // 
 //    Rev 1.42   13 Feb 2002 14:09:02   KOVACSRO
 // ClearUpdatedFlags and setFiledNoValidate in modelOffer (otherwise 'Allocation percentage not 100' error message is issued for a copied item).
 // 
 //    Rev 1.41   09 Nov 2001 09:16:48   HSUCHIN
 // bug fix for the transaction builder
 // 
 //    Rev 1.40   05 Nov 2001 11:44:28   HSUCHIN
 // bug fix for getSplitCommissionList.   CommissionType check is insert, if 0 - no Split Commission will be returned.   bug fix to scenario where a fund with split is modified to a fund with no split.
 // 
 //    Rev 1.39   26 Sep 2001 17:01:22   HSUCHIN
 // changed SplitComm check to Commission Type check
 // 
 //    Rev 1.38   26 Sep 2001 13:58:52   HSUCHIN
 // added function to retrieve systematic effective date and bus rule to active/deactive split commission
 // 
 //    Rev 1.37   Sep 12 2001 11:24:24   YINGBAOL
 // force to do validation if Fund or Class has been changed
 // 
 //    Rev 1.36   Aug 15 2001 19:09:30   YINGBAOL
 // fix bug
 // 
 //    Rev 1.35   Jul 29 2001 14:52:26   YINGBAOL
 // modify condition ---version sync. up
 // 
 //    Rev 1.34   Jun 26 2001 14:33:12   HERNANDO
 // Removed call to validateAllocCurrencyvalidateAllocCurrency.
 // 
 //    Rev 1.33   Jun 26 2001 12:55:00   PURDYECH
 // Infrastructure Release 1.9 Integration.
 // 
 //    Rev 1.32   17 May 2001 10:43:30   HSUCHIN
 // added dstcworksession point to splitcommactive function call
 // 
 //    Rev 1.31   09 May 2001 14:17:40   HSUCHIN
 // Sync up with SSB
 // 
 //    Rev 1.30   02 May 2001 13:02:20   HSUCHIN
 // added severity check after init
 // 
 //    Rev 1.29   May 02 2001 09:10:58   JANKAREN
 // Modify to use getFundDetail method
 // 
 //    Rev 1.28   01 May 2001 10:12:22   HSUCHIN
 // changed ifds::Default to be initialized with setFieldNoValidate rather than setElement Value
 // 
 //    Rev 1.27   28 Apr 2001 16:16:56   HSUCHIN
 // bug fix when deleting split commission
 // 
 //    Rev 1.26   28 Apr 2001 15:18:56   HSUCHIN
 // ensure that split comm exists before getting default
 // 
 //    Rev 1.25   27 Apr 2001 14:40:58   HSUCHIN
 // removed recalculateCommAmount, changed the way split comm flag is retrieved and changed getSplitCommList to detect original split comm
 // 
 //    Rev 1.24   Apr 26 2001 10:44:00   JANKAREN
 // add validateAllocCurrency
 // 
 //    Rev 1.23   Apr 25 2001 14:19:56   WINNIE
 // fix calling of FundToList
 // 
 //    Rev 1.22   25 Apr 2001 10:01:32   HSUCHIN
 // bug fix for Default SplitCommission
 // 
 //    Rev 1.21   17 Apr 2001 10:32:52   HSUCHIN
 // minor bug fix for when Default flag is not set for split commission
 // 
 //    Rev 1.20   14 Apr 2001 10:38:58   HSUCHIN
 // removed code from setField and move them to doapplyrelated changes.  Changed default split commission implementation
 // 
 //    Rev 1.19   03 Apr 2001 20:12:54   HSUCHIN
 // implemented default split commission
 // 
 //    Rev 1.18   01 Apr 2001 12:57:42   HSUCHIN
 // check in for winnie
 // 
 //    Rev 1.17   Mar 05 2001 16:16:08   YINGBAOL
 // validate fundclass transfer
 // 
 //    Rev 1.16   Dec 17 2000 20:22:36   OLTEANCR
 // changed to use a precompiled header
 // 
 //    Rev 1.15   Sep 22 2000 16:42:26   HUANGSHA
 // fixed the problem in setting amount field
 // 
 //    Rev 1.14   Sep 01 2000 14:33:28   ZHANGCEL
 // Added code for Fund Number stuffs
 // 
 //    Rev 1.13   Aug 29 2000 11:22:10   ZHANGCEL
 // Fixed Fund Number issue
 // 
 //    Rev 1.12   Aug 24 2000 16:38:56   YINGBAOL
 // clean up file
 // 
 //    Rev 1.11   Aug 04 2000 13:56:38   YINGBAOL
 // change validation
 // 
 //    Rev 1.10   Jul 26 2000 16:26:32   YINGBAOL
 // change create new item logic
 // 
 //    Rev 1.9   Jun 30 2000 09:54:04   YINGBAOL
 // fix add copy and other bugs
 // 
 //    Rev 1.8   Jun 19 2000 11:32:38   YINGBAOL
 // change format
 // 
 //    Rev 1.7   Jun 13 2000 18:06:22   DT24433
 // new Infra interfaces use ClientLocale
 // 
 //    Rev 1.6   May 04 2000 16:56:14   WINNIE
 // change CURRENCY_HPP to CURRENCYCLASS_HPP
 // 
 //    Rev 1.5   May 01 2000 14:16:38   YINGBAOL
 // small fix
 // 
 //    Rev 1.4   May 01 2000 09:39:26   YINGBAOL
 // add validation
 // 
 //    Rev 1.3   Apr 17 2000 17:15:54   YINGZ
 // add AddCopy function for systematic
 // 
 //    Rev 1.2   Apr 17 2000 11:22:54   YINGBAOL
 // fix M3 crash
 // 
 //    Rev 1.1   Mar 31 2000 16:22:06   YINGBAOL
 // check in sync.
 // 
 //    Rev 1.0   Mar 27 2000 13:29:14   YINGBAOL
 // Initial revision.
// 
*/

