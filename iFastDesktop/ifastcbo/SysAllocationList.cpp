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
// ^FILE   : SysAllocationList.cpp
// ^AUTHOR : Chin Hsu
// ^DATE   : Feburary 25, 1999
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : SysAllocationList
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************

#include "stdafx.h"
#include "amsfundalloclist.hpp"
#include "deffundalloclist.hpp"
#include <ifastdataimpl\dse_dstc0004_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0006_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0007_vw.hpp>
#include <ifastdataimpl\dse_dstc0007_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0058_vw.hpp>
#include "funddetaillist.hpp"
#include "FundDetail.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "shareholder.hpp"
#include "shralloctypelist.hpp"
#include "splitcommissionlist.hpp"
#include "sysallocation.hpp"
#include "sysallocationlist.hpp"
#include "systematic.hpp"
#include "amsmstrinfo.hpp"
#include "amsmstrlist.hpp"

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_("SysAllocationList");
   const I_CHAR * const YES = I_("Y");
   const I_CHAR * const NO=I_("N");
}

namespace CND
{
   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
   extern const long ERR_IDENTICAL_FUND_ALLOCS;
   extern const long ERR_SUM_OF_PERCENTAGES_NOT_100;
   extern const long ERR_FUND_CURRENCY_DIFFERENT;
   extern const long ERR_ONLY_CUSTOM_PAYOUT_FUNDS_ARE_ALLOWED_FOR_THE_PLAN;
   extern const long WARN_ONLY_CUSTOM_PAYOUT_FUNDS_ARE_ALLOWED_FOR_THE_PLAN;
}

namespace IFASTERR
{
    extern CLASS_IMPORT I_CHAR * const ONLY_CUSTOM_PAYOUT_FUNDS_ARE_ALLOWED_FOR_THE_PLAN;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId ReplaceAsDefault;
   extern CLASS_IMPORT const BFTextFieldId MultiCurrency;
   extern CLASS_IMPORT const BFTextFieldId BankAcctCurrency;
   extern CLASS_IMPORT const BFDecimalFieldId AllocPercentage;
   extern CLASS_IMPORT const BFTextFieldId PACSWPOverride;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFTextFieldId DefaultAlloc;
   extern CLASS_IMPORT const BFTextFieldId FundAlloc;
   extern CLASS_IMPORT const BFTextFieldId FundClass;
   extern CLASS_IMPORT const BFTextFieldId SoftCapCheck;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//		Field DD Id,				State Flags,					Group Flags
   {ifds::ReplaceAsDefault, BFCBO::NONE, 0}, 
   {ifds::SettleCurrency,   BFCBO::NONE, 0}
};

static const int NUM_FIELDS = sizeof(classFieldInfo) / sizeof(BFCBO::CLASS_FIELD_INFO);

//********************************************************************************
SysAllocationList::SysAllocationList(BFAbstractCBO &parent) : MFCanBFCbo(parent),
_dstrMultiCurrency(NULL_STRING),
_dstrAddCopy(NULL_STRING),
_bAddCopy(false),
_strPacSwpId(NULL_STRING)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);

   registerMemberData(NUM_FIELDS,(const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL);
   setObjectAsList();
   getWorkSession().getOption(ifds::MultiCurrency, _dstrMultiCurrency, BF::HOST, false);
}

//********************************************************************************
SysAllocationList::~SysAllocationList()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//*********************************************************************************
void SysAllocationList::GetAccountLevelInfo(DString& strVer, DString& strRid)
{
   strVer = _dstrAcctLvlVer;
   strRid = _dstrAcctLvlRid; 
}

//********************************************************************************
SEVERITY SysAllocationList::init(const BFDataGroupId& idDataGroup, 
   const DString& strPacSwpId, const BFData &data)
{
   MAKEFRAME2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   initNew(idDataGroup);
   _strPacSwpId = strPacSwpId;
   createObjectForEachRepeat(data);
   clearUpdatedFlags(idDataGroup, true);
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY SysAllocationList::doCreateObject(const BFData& data, BFCBO *&pObjOut)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateObject"));

   DString dstrLevel = data.getElementValue(I_("Level"));
   DString dstrPACSWPId = data.getElementValue(I_("PACSWPId"));

   dstrLevel.strip();
   dstrPACSWPId.strip().stripLeading(I_CHAR('0'));  
   if (dstrPACSWPId.compare(_strPacSwpId) == 0 && dstrLevel == I_("2"))
   {
      _dstrAcctLvlVer = data.getElementValue(I_("DistribDetlVer"));
      _dstrAcctLvlRid = data.getElementValue(I_("DistribDetlRid"));
   }
   else if (dstrPACSWPId.compare(_strPacSwpId) == 0 && dstrLevel == I_("3"))
   {
      SysAllocation *pSysAllocation= new SysAllocation(*this);

      pSysAllocation->init(data);
      if(_dstrMultiCurrency == I_("N"))
      {
         DString dstrFundCode, dstrClassCode;
      
         dstrFundCode = data.getElementValue(I_("FundCode"));
         dstrClassCode = data.getElementValue(I_("ClassCode"));
         setCurrency(dstrFundCode, dstrClassCode, BF::HOST);
      }
      pObjOut = pSysAllocation;
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************
SEVERITY SysAllocationList::initNew(const BFDataGroupId& idDataGroup)
{
   MAKEFRAME2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("initNew"));

   setFieldNoValidate(ifds::ReplaceAsDefault, I_("N"), idDataGroup);
   setFieldNoValidate(ifds::SettleCurrency, NULL_STRING, idDataGroup, false);
   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************
SEVERITY SysAllocationList::doCreateNewObject(BFCBO *& pBase, DString &strKey, 
   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateNewObject"));
   if (_bAddCopy)
   {
      strKey = _dstrAddCopy;
   }
   SysAllocation *pSysAllocation = new SysAllocation(*this);
   pSysAllocation->init();
   pBase = pSysAllocation;
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY SysAllocationList::doValidateAll(const BFDataGroupId& idDataGroup, long lValidateGroup) 
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll"));

   //Only validate for the PAC and SWP
   DString dstrTransType;
   getParent()->getField(ifds::TransType, dstrTransType, idDataGroup, false);
   dstrTransType.strip().upperCase();
   if(dstrTransType != I_("P") && dstrTransType != I_("S"))
      return(GETCURRENTHIGHESTSEVERITY());

   I_CHAR *stopstring;
   std::set< DString > setCharacteristic;
   double dMaxPercentage = 0, dTotalPercentage = 0;
   double dMaxAmount = 0, dTotalAmount = 0;
   DString dstrMaxPercentageKey, dstrMaxAmountKey;
   bool bInitializeCurrency = true;

   // 1. iterate through the list
   BFObjIter iter1(*this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
   if(iter1.isDummy() || !isUpdatedForDataGroup(idDataGroup)) 
      //NOTE: dummy record is never  created coz of AMS a/c
      return(GETCURRENTHIGHESTSEVERITY());


   if(iter1.end())
   {  
      ADDCONDITIONFROMFILE(CND::ERR_SUM_OF_PERCENTAGES_NOT_100);
      return(GETCURRENTHIGHESTSEVERITY());
   }
   SplitCommissionList *pSplitCommissionList = NULL;
   SysAllocation *pSysAllocation;
   DString dstrFundCode, dstrClassCode, dstrSplitComm, dstr, dstrAmount, dstrPercentage;
   double dPercentage = 0, dAmount = 0;
   while(!iter1.end())
   {
      // 1-1. Verify that all fund-class pairs are unique		
      iter1.getObject()->getField(ifds::FundCode, dstrFundCode,  idDataGroup);
      dstrFundCode.strip();

      iter1.getObject()->getField(ifds::ClassCode, dstrClassCode, 
                                   idDataGroup);
      dstrClassCode.strip();

      dstr = dstrFundCode + dstrClassCode;

      if(!setCharacteristic.insert(dstr).second)
         ADDCONDITIONFROMFILE(CND::ERR_IDENTICAL_FUND_ALLOCS);

      // 1-2. calculate total percentage and maximal percentage

      iter1.getObject()->getField(ifds::Percentage, dstrPercentage, 
                                   idDataGroup);
      dstrPercentage.strip().stripAll(I_CHAR(','));
      dPercentage = wcstod(dstrPercentage.c_str(), &stopstring);
      if(dPercentage > dMaxPercentage)
      {
         dMaxPercentage = dPercentage;
         dstrMaxPercentageKey = iter1.getStringKey();
      }
      dTotalPercentage += dPercentage;

      // 1-3. calculate total amount and maximal amount

      iter1.getObject()->getField(ifds::AllocAmount, dstrAmount, 
                                   idDataGroup);
      dstrAmount.strip().stripAll(I_CHAR(','));
      dAmount = wcstod(dstrAmount.c_str(), &stopstring);
      if(dAmount > dMaxAmount)
      {
         dMaxAmount = dAmount;
         dstrMaxAmountKey = iter1.getStringKey();
      }
      dTotalAmount += dAmount;
      pSysAllocation = dynamic_cast <SysAllocation*>(iter1.getObject());

      // validate fund currency to ensure all currency are the same for single currency system
      /*if(_dstrMultiCurrency.empty())
         getWorkSession().getOption(ifds::MultiCurrency, _dstrMultiCurrency, idDataGroup, false);*/

      if(_dstrMultiCurrency == I_("N"))
      {
         if(bInitializeCurrency)
         {
            setFieldNoValidate(ifds::SettleCurrency, NULL_STRING, idDataGroup, false);
            bInitializeCurrency = false;
         }
         if(setCurrency (dstrFundCode,  dstrClassCode, idDataGroup) > WARNING)
            return(GETCURRENTHIGHESTSEVERITY());
      }

      // validate split commission
      pSysAllocation->getField (ifds::SplitComm, dstrSplitComm, idDataGroup, false);
      pSysAllocation->getSplitCommissionList (pSplitCommissionList, idDataGroup);
      if(dstrSplitComm == I_("Y") && pSplitCommissionList)
      {
         pSplitCommissionList->validateAll(idDataGroup, lValidateGroup);
         //set the split comm field on the systematic parent
         getParent()->setField(ifds::SplitComm, I_("Y"), idDataGroup, false, true, false);
      }
      ++iter1;
   }

   // 2. retrieve the systematic amount
   DString dstrTotalSysAmount;
   getParent()->getField(ifds::Amount, dstrTotalSysAmount, idDataGroup);
   dstrTotalSysAmount.strip().stripAll(I_CHAR(','));
   double dTotalSysAmount = wcstod(dstrTotalSysAmount.c_str(), &stopstring);

   // 3. calculate the percentage accuracy
   DString dstrPercentageMask = DSTCommonFunctions::getRawMask(ifds::Percentage);
   dstrPercentageMask.strip();
   int iPercentageNumDigitsAfterDecimalPoint = dstrPercentageMask.length() 
                                               - dstrPercentageMask.find(I_(".")) - 1;
   double dPercentageThreshold = pow(10.0, 
                                      -iPercentageNumDigitsAfterDecimalPoint);

   // 4. calculate the amount accuracy
   DString dstrAllocAmountMask = DSTCommonFunctions::getRawMask(ifds::AllocAmount);
   dstrAllocAmountMask.strip();
   int iAllocAmountNumDigitsAfterDecimalPoint = dstrAllocAmountMask.length() 
                                                - dstrAllocAmountMask.find(I_(".")) - 1;
   double dAllocAmountThreshold = pow(10.0, 
                                       -iAllocAmountNumDigitsAfterDecimalPoint);

   // 5. Eliminate rounding differences, or signal an error if the differences
   //    are larger than expected from the rounding effects.
   double dPercentageDiff = dTotalPercentage - 100;
   double dAllocAmountDiff = dTotalAmount - dTotalSysAmount;
   if(fabs(dPercentageDiff) <= dPercentageThreshold)
   {
      //assert(fabs(dAllocAmountDiff) < dAllocAmountThreshold * 10);
      if(fabs(dAllocAmountDiff) >= dAllocAmountThreshold)
      {
         dMaxAmount -= dAllocAmountDiff;
         //char buffer[ 50 ];
         //DString dstrMaxAmount = DStringA(_gcvt(dMaxAmount, 30, buffer));
         DString dstrMaxAmount = DSTCommonFunctions::doubleToDString(ifds::AllocAmount, dMaxAmount);

         iter1.positionByKey( dstrMaxAmountKey);
         iter1.getObject()->setField(ifds::AllocAmount, dstrMaxAmount, 
                                      idDataGroup);
      }
   }
   else if(fabs(dAllocAmountDiff) <= dAllocAmountThreshold)
   {
      //assert(fabs(dPercentageDiff) < dPercentageThreshold * 10);
      dMaxPercentage -= dPercentageDiff;
//		char buffer[ 50 ];
//		DString dstrMaxPercentage = DStringA(_gcvt(dMaxPercentage, 30, 
//																							buffer));

      DString dstrMaxPercentage = DSTCommonFunctions::doubleToDString(ifds::Percentage, dMaxPercentage);

      iter1.positionByKey( dstrMaxPercentageKey);
      iter1.getObject()->setField(ifds::Percentage, dstrMaxPercentage, 
                                   idDataGroup);
   }
   else
      ADDCONDITIONFROMFILE(CND::ERR_SUM_OF_PERCENTAGES_NOT_100);

   if(_dstrMultiCurrency == I_("N"))
   {
      Systematic *pSystematic = NULL;
      pSystematic = dynamic_cast< Systematic * >(getParent());
      if(pSystematic)
      {
         DString dstrSettleCurrency;
         getField (ifds::SettleCurrency, dstrSettleCurrency, idDataGroup, false); 
         pSystematic->setField (ifds::BankAcctCurrency, dstrSettleCurrency, idDataGroup);
      }
   }

   //Validate SWP custom payout plan
   if (dstrTransType == I_("S"))
   {
       BFObjIter iterSys(*this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
       bool foundNonCustomPayout(false), foundCustomPayout(false);

       while (!iterSys.end() && !(foundNonCustomPayout && foundCustomPayout))
       {
           DString dstrFund, dstrClass;
           iterSys.getObject()->getField(ifds::FundCode, dstrFund, idDataGroup);
           iterSys.getObject()->getField(ifds::ClassCode, dstrClass, idDataGroup);

           if (!dstrFund.empty() && !dstrClass.empty())
           {
               FundDetail *pFundDetail = NULL;
               bool isCustomPayout = getWorkSession().getFundDetail(dstrFund, dstrClass, idDataGroup, pFundDetail) && 
                                     pFundDetail &&
                                     pFundDetail->isCustomPayoutFund(idDataGroup);

               foundCustomPayout = foundCustomPayout || isCustomPayout;
               foundNonCustomPayout = foundNonCustomPayout || !isCustomPayout;
           }

           ++iterSys;
       }

       if (foundNonCustomPayout && foundCustomPayout)
       {
           getErrMsg(IFASTERR::ONLY_CUSTOM_PAYOUT_FUNDS_ARE_ALLOWED_FOR_THE_PLAN, 
                     CND::ERR_ONLY_CUSTOM_PAYOUT_FUNDS_ARE_ALLOWED_FOR_THE_PLAN, 
                     CND::WARN_ONLY_CUSTOM_PAYOUT_FUNDS_ARE_ALLOWED_FOR_THE_PLAN,
                     idDataGroup);
       }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void SysAllocationList::ModelOffer(SysAllocationList *Model, const BFDataGroupId& idDataGroup)
{
   SysAllocation * pSysAllocation;
   BFObjectKey objKey;
   _bAddCopy = true;

   BFObjIter iterDest(*this, idDataGroup);

   for(BFObjIter Iter(*Model, idDataGroup); !Iter.end(); ++Iter)
   {
      //	objKey = Iter.getKey(); // we don't want to ruin old key, so make a copy
      _dstrAddCopy = Iter.getStringKey();
      // objKey.getActivity() = OBJ_ADDED;
      //  objKey.getDataGroupId() = idDataGroup;
      if(iterDest.end())
      {
         pSysAllocation = static_cast< SysAllocation * >(getNewListItem(objKey));
         pSysAllocation->ModelOffer(static_cast< SysAllocation * >(Iter.getObject()), idDataGroup);
      }
      else
      {
         pSysAllocation = static_cast< SysAllocation * >(iterDest.getObject());
         pSysAllocation->ModelOffer(static_cast< SysAllocation * >(Iter.getObject()), idDataGroup);
         ++iterDest;
      }
   }
   _bAddCopy = false;
}

//********************************************************************************

SEVERITY SysAllocationList::initWithDefaultAllocations(const BFDataGroupId& idDataGroup, 
                                                        const DString& dstrTransTypeIn, const DString& dstrAcctNumIn, 
                                                        const DString& dstrCurrency, const DString& dstrAmount,
                                                        const DString& dstrEffectiveDate, bool bDummyAllocations )
{
   MAKEFRAME2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("initWithDefault"));

   setFieldNoValidate(ifds::ReplaceAsDefault, I_("N"), idDataGroup);
   setFieldNoValidate(ifds::SettleCurrency,NULL_STRING, idDataGroup, false);

   /*if(_dstrMultiCurrency.empty())
   {
      getWorkSession().getOption(ifds::MultiCurrency, _dstrMultiCurrency, idDataGroup, false);
   }*/

   if(dstrTransTypeIn == NULL_STRING || dstrAcctNumIn == NULL_STRING)
      return(GETCURRENTHIGHESTSEVERITY());

   SEVERITY sevRtn = SEVERE_ERROR;


   MFAccount* pMFAccount = NULL;
   sevRtn = getWorkSession().getMFAccount(idDataGroup, dstrAcctNumIn, pMFAccount);
   if(sevRtn > WARNING || pMFAccount == NULL)
      return(sevRtn);

   MFCanBFCbo *pAllocationList = NULL;
   //rule : if AMSCode in the account is
   //a) empty - get default allocations for the specified trans type
   //b) 0001 - use the Ams rebalancing default allocations
   //c) any other value - use the ams allocation list from MFAccount


/* Old logic removied
   DString strAccountNum, strAMSCode(NULL_STRING);
   pMFAccount->getField(ifds::AMSCode, strAMSCode, idDataGroup, false);
   if (strAMSCode.strip().empty())
      getShrDefAllocList(pAllocationList, idDataGroup, dstrTransTypeIn, dstrAcctNumIn);
   else if (strAMSCode == I_("0001"))
      getRebalDefAllocList(pAllocationList, idDataGroup, dstrAcctNumIn);
   else
      getAMSDefAllocList(pAllocationList, idDataGroup, dstrAcctNumIn, dstrEffectiveDate);
*/
   if ( pMFAccount->isAMSAccount ( idDataGroup ) ) {
      DString dstrAMSCode;
      pMFAccount->getField(ifds::AMSCode, dstrAMSCode, idDataGroup, false);
      if (!dstrAMSCode.strip().empty()) {
         DString dstrDefaultAlloc, dstrFundAlloc;
         AMSMstrList* pAMSMstrList;
         pMFAccount->getAMSMstrList ( pAMSMstrList, idDataGroup, dstrEffectiveDate );
         if ( pAMSMstrList ) {
            AmsMstrInfo* pAMSMstrInfo;
            pAMSMstrList->getAMSMstrInfo ( I_("RB"), dstrAMSCode, dstrEffectiveDate, pAMSMstrInfo, idDataGroup );
            if ( pAMSMstrInfo ) {
               pAMSMstrInfo->getField(ifds::DefaultAlloc, dstrDefaultAlloc, idDataGroup, false);
               if ( dstrDefaultAlloc == YES ) {
                  getRebalDefAllocList(pAllocationList, idDataGroup, dstrAcctNumIn);                  
               } else if ( dstrDefaultAlloc == NO ) {
                  pAMSMstrInfo->getField(ifds::FundAlloc, dstrFundAlloc, idDataGroup, false);
                  if (dstrFundAlloc == YES) {
                     getAMSDefAllocList(pAllocationList, idDataGroup, dstrAcctNumIn, dstrEffectiveDate);                     
                  }
               }
            }
         }       
      }
   } else {
      // Get Default allocations from shareholder.
      getShrDefAllocList(pAllocationList, idDataGroup, dstrTransTypeIn, dstrAcctNumIn);
   }

   if (!pAllocationList)
      return(GETCURRENTHIGHESTSEVERITY());

   /**
     *   Fill in the Allocation List with the Default Allocation List
     */
   BFObjIter iter(*pAllocationList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
   if(iter.getNumberOfItemsInList() <= 0)
      return(GETCURRENTHIGHESTSEVERITY());

   DString dstrKey;
   while(!iter.end())
   {
      BFAbstractCBO *pBFCBO = iter.getObject();
      if(pBFCBO)
      {
         DString dstrLevel, dstrAccountNum, dstrTransType, dstrEffecDate;
         //pBFCBO->getField(ifds::Level, dstrLevel, idDataGroup, false);
         pBFCBO->getField(ifds::AccountNum, dstrAccountNum, idDataGroup, true);
         if (dstrAccountNum.strip().empty())
            dstrAccountNum = dstrAcctNumIn;
         pBFCBO->getField(ifds::TransType, dstrTransType, idDataGroup, false);
         if (dstrTransType.strip().upperCase().empty() || pMFAccount->isAMSAccount ( idDataGroup ))
            dstrTransType = dstrTransTypeIn;
         pBFCBO->getField(ifds::EffectiveDate, dstrEffecDate, idDataGroup, false);

         //if(convertToULong(dstrLevel) == 3)       //Actually no need to check
         //{
            SysAllocation *pSysAllocation = new SysAllocation(*this);
            BFData *pDataAlloc = new BFData(ifds::DSTC0007_VWRepeat_Record);

            DString dstrValue;

            pDataAlloc->setElementValue(ifds::DistribDetlRid, I_("0"));
            pDataAlloc->setElementValue(ifds::TransType, dstrTransType);
            pDataAlloc->setElementValue(ifds::PACSWPId, I_("0"));
            pDataAlloc->setElementValue(ifds::Level, I_("3"));
            pDataAlloc->setElementValue(ifds::AllocAccountNum, dstrAccountNum);
            pDataAlloc->setElementValue(ifds::SettleCurrency, dstrCurrency);
            pBFCBO->getField(ifds::FundCode, dstrValue, idDataGroup, false);
            pDataAlloc->setElementValue(ifds::FundCode, dstrValue);

            pBFCBO->getField(ifds::ClassCode, dstrValue, idDataGroup, false);
            pDataAlloc->setElementValue(ifds::ClassCode, dstrValue);

            pBFCBO->getField(ifds::AllocPercentage, dstrValue, idDataGroup, false);
            pDataAlloc->setElementValue(ifds::Percentage, dstrValue, false, false);
            if ( dstrAmount == I_("0") ) {
               pDataAlloc->setElementValue(ifds::AllocAmount, I_("0"));
            } else {
               double dPercent = DSTCommonFunctions::convertToDouble ( dstrValue );
               double dAmount = DSTCommonFunctions::convertToDouble ( dstrAmount );
               double dTotal = dAmount * dPercent / 100;
               DString dstr = DSTCommonFunctions::doubleToDString ( ifds::AllocAmount, dTotal );
               pDataAlloc->setElementValue(ifds::AllocAmount, dstr);
            }

            //create a new object
            getStrKey(dstrKey, pDataAlloc);
            pSysAllocation->init(*pDataAlloc);
            setObject(pSysAllocation, dstrKey, bDummyAllocations?OBJ_ACTIVITY_NONE:OBJ_ACTIVITY_ADDED, idDataGroup);
            pSysAllocation->GetDefaultSplitComm (idDataGroup);
         //}
      }
      ++iter;
   }

   /*
   // for ams account, when ams allocation is used as default allocation, its transtype needs
   // to be set to PAC or SWP. otherwise, view 236 will fail when doing validation for fundclass
   if ( pMFAccount->isAMSAccount ( idDataGroup ) ) {
	   BFObjIter iter(*this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
	   while( !iter.end() )
	   {
		   SysAllocation *pSysAlloc = dynamic_cast<SysAllocation* >(iter.getObject() );
		   if( pSysAlloc )
		   {
			   pSysAlloc->setField( ifds::TransType, dstrTransTypeIn, idDataGroup, false ); 
		   }
		   ++iter;
	   }
   }
   */

   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
void SysAllocationList::getTotalAllocAmountPercent(const BFDataGroupId& idDataGroup, double &dTotalAmount, double &dTotalPercentage)
{
   DString dstrTemp;
   dTotalAmount      = 0;
   dTotalPercentage  = 0;
   BFObjIter iter(*this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
   while(!iter.end())
   {
      if(iter.getObject())
      {
         // Total Percentage
         iter.getObject()->getField(ifds::Percentage, dstrTemp, idDataGroup, false); 
         dstrTemp.strip().stripAll(I_CHAR(','));
         dTotalPercentage  += DSTCommonFunctions::convertToDouble(dstrTemp);

         // Total Amount
         iter.getObject()->getField(ifds::AllocAmount, dstrTemp, idDataGroup, false);
         dstrTemp.strip().stripAll(I_CHAR(','));
         dTotalAmount      += DSTCommonFunctions::convertToDouble(dstrTemp);
      }
      ++iter;
   }
}

//******************************************************************************
void SysAllocationList::getTotal (const BFFieldId& idField, DString &dstrTotal, const BFDataGroupId& idDataGroup)
{
   BFObjIter iter(*this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
   DString dstr;
   double dtotal = 0;
   while(!iter.end())
   {
      iter.getObject()->getField (idField, dstr, idDataGroup);
      dtotal += DSTCommonFunctions::convertToDouble (dstr);
      ++iter;
   }
   dstrTotal = DSTCommonFunctions::doubleToDString (idField, dtotal);
}

//******************************************************************************
void SysAllocationList::GetDefaultSplitComm (const BFDataGroupId& idDataGroup)
{
   BFObjIter iter(*this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);   
   while(!iter.end())
   {
      static_cast <SysAllocation*>(iter.getObject())->GetDefaultSplitComm (idDataGroup);
      ++iter;
   }
}

//******************************************************************************
void SysAllocationList::GetSplitCommFlag (const BFDataGroupId& idDataGroup, DString &dstrSplitComm)
{
   BFObjIter iter(*this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
   while(!iter.end())
   {
      static_cast <SysAllocation*>(iter.getObject())->getField(ifds::SplitComm, dstrSplitComm, idDataGroup);
      if(dstrSplitComm == I_("Y"))
         return;
      ++iter;
   }
   dstrSplitComm = I_("N");
}

//******************************************************************************

void SysAllocationList::GetSplitCommList (const BFDataGroupId& idDataGroup) {
   SplitCommissionList *pSplitCommissionList = NULL;
   SysAllocation *pSysAllocation;
   DString dstrSplitComm;
   BFObjIter iter(*this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);   
   while(!iter.end())
   {
      pSysAllocation = static_cast <SysAllocation*>(iter.getObject());
      pSysAllocation->getField (ifds::SplitComm, dstrSplitComm, idDataGroup, false);
      if(dstrSplitComm == I_("Y"))
         pSysAllocation->getSplitCommissionList (pSplitCommissionList, idDataGroup);
      ++iter;
   }
}

//******************************************************************************

int SysAllocationList::getNbrOfAllocInList(const BFDataGroupId& idDataGroup)//NON_DELETED
{
   BFObjIter iter(*this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
   return(iter.getNumberOfItemsInList());
}

//******************************************************************************
SEVERITY SysAllocationList::setCurrency(const DString dstrFundCode, 
   const DString dstrClassCode, const BFDataGroupId& idDataGroup) 
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("setCurrency"));

   DString dstrCurrency;
   FundDetailList *pFundDetailList = NULL;

   getMgmtCo().getFundDetailList(pFundDetailList);
   if(pFundDetailList)
   {
      pFundDetailList->getField(dstrFundCode, dstrClassCode, ifds::Currency, 
         dstrCurrency, idDataGroup, false);
      if(!dstrCurrency.strip().upperCase().empty())
      {
         DString previousCurrency;

         getField(ifds::SettleCurrency, previousCurrency, idDataGroup, false);
         if (previousCurrency.strip().empty())
         {
            setFieldNoValidate(ifds::SettleCurrency, dstrCurrency, idDataGroup, false);
         }
         else if (previousCurrency != dstrCurrency)
         {
            ADDCONDITIONFROMFILE(CND::ERR_FUND_CURRENCY_DIFFERENT);
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}
//**********************************************************
SEVERITY SysAllocationList::doApplyRelatedChanges(const BFFieldId& idField, 
   const BFDataGroupId& idDataGroup)
{
   if(idField == ifds::SettleCurrency)
   {
      setUpdatedFlag(ifds::SettleCurrency, idDataGroup, false);
   }
   return(NO_CONDITION);
}

//**********************************************************
SEVERITY SysAllocationList::getShrDefAllocList(MFCanBFCbo* &pDefaultAllocationList, const BFDataGroupId& idDataGroup, 
                                               const DString& dstrTransTypeIn, const DString& dstrAcctNumIn)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getShrDefAllocList"));

   pDefaultAllocationList = NULL;

   DString dstrShrNum;
   MFAccount* pMFAccount = NULL;
   if (getWorkSession().getMFAccount(idDataGroup, dstrAcctNumIn, pMFAccount) > WARNING || !pMFAccount)
      return(GETCURRENTHIGHESTSEVERITY());

   pMFAccount->getField(ifds::ShrNum, dstrShrNum, idDataGroup, true);
   Shareholder* pShareholder = NULL;
   if (getWorkSession().getShareholder(idDataGroup, dstrShrNum.strip(), pShareholder) > WARNING || !pShareholder)
      return(GETCURRENTHIGHESTSEVERITY());

   //Get the Shareholder Level Allocation
   ShrAllocTypeList* pShrAllocationList = NULL;
   if (pShareholder->getAllocationList(pShrAllocationList, idDataGroup) > WARNING || !pShrAllocationList)
      return(GETCURRENTHIGHESTSEVERITY());

   //get the Fund Level default allocation list
   DefFundAllocList *pAllocationList = NULL;
   if (pShrAllocationList->getDefaultFundAllocList(dstrTransTypeIn, dstrAcctNumIn, pAllocationList, 
      idDataGroup) <= WARNING)
      pDefaultAllocationList = pAllocationList;

   return(GETCURRENTHIGHESTSEVERITY());
}
//**********************************************************

SEVERITY SysAllocationList::getRebalDefAllocList(MFCanBFCbo* &pDefaultAllocationList, const BFDataGroupId& idDataGroup, 
                                                 const DString& strAccountNum)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getRebalDefAllocList"));

   pDefaultAllocationList = NULL;

   DString dstrShrNum;
   MFAccount* pMFAccount = NULL;
   if (getWorkSession().getMFAccount(idDataGroup, strAccountNum, pMFAccount) > WARNING || !pMFAccount)
      return(GETCURRENTHIGHESTSEVERITY());

   pMFAccount->getField(ifds::ShrNum, dstrShrNum, idDataGroup, true);
   Shareholder* pShareholder = NULL;
   if (getWorkSession().getShareholder(idDataGroup, dstrShrNum.strip(), pShareholder) > WARNING || !pShareholder)
      return(GETCURRENTHIGHESTSEVERITY());

   //Get the Shareholder Level Allocation
   ShrAllocTypeList* pShrAllocationList = NULL;
   if (pShareholder->getAllocationList(pShrAllocationList, idDataGroup) > WARNING || !pShrAllocationList)
      return(GETCURRENTHIGHESTSEVERITY());

   DefFundAllocList* pDefFundAllocList = NULL;
   if (pShrAllocationList->getDefaultFundAllocList(I_("RB"), strAccountNum, pDefFundAllocList, 
      idDataGroup) <= WARNING)
      pDefaultAllocationList = pDefFundAllocList;

   return(GETCURRENTHIGHESTSEVERITY());
}
//**********************************************************

SEVERITY SysAllocationList::getAMSDefAllocList(MFCanBFCbo* &pDefaultAllocationList, const BFDataGroupId& idDataGroup, 
                                                 const DString& strAccountNum, const DString& dstrEffectiveDate )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getAMSDefAllocList"));
   DString dstrDate = dstrEffectiveDate;
   pDefaultAllocationList = NULL;

   MFAccount* pMFAccount = NULL;
   if (getWorkSession().getMFAccount(idDataGroup, strAccountNum, pMFAccount) > WARNING || !pMFAccount)
      return(GETCURRENTHIGHESTSEVERITY());
   AMSMstrList* pAMSMstrList = NULL;

   DString dstrPACSWPOverride;
   getWorkSession().getOption( ifds::PACSWPOverride, dstrPACSWPOverride, idDataGroup, false); 
   //If it PAC/SWP Override is Yes, then we will use the current business date except for future date.
   if ( dstrPACSWPOverride == YES ) {
      DString dstrCurrBusDate;
      getWorkSession().getOption(ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false);
      if ( DSTCommonFunctions::CompareDates ( dstrEffectiveDate, dstrCurrBusDate ) 
         == DSTCommonFunctions::FIRST_EARLIER || dstrDate == NULL_STRING) {
         dstrDate = dstrCurrBusDate;
      }
   }
   DString dstrAMSCode;
   pMFAccount->getField ( ifds::AMSCode, dstrAMSCode, idDataGroup );
/*
   pMFAccount->getAMSMstrList ( pAMSMstrList, idDataGroup, dstrDate );
   if ( pAMSMstrList ) {
      AmsMstrInfo* pAMSMstrInfo = NULL;
      pAMSMstrList->getAMSMstrInfo ( I_("RB"), dstrAMSCode, dstrDate, pAMSMstrInfo, idDataGroup );
      AmsFundAllocList* pAmsFundAllocList = NULL;
      pAMSMstrInfo->getAMSFundAllocList( pAmsFundAllocList, idDataGroup );
      pDefaultAllocationList = dynamic_cast<MFCanBFCbo*>(pAmsFundAllocList);
   }
  */ 

   AmsFundAllocList *pAmsFundAllocList = NULL;
   if (pMFAccount->getAMSFundAllocList( I_("RB"), dstrEffectiveDate, pAmsFundAllocList, idDataGroup) <= WARNING)
      pDefaultAllocationList = dynamic_cast<MFCanBFCbo*>(pAmsFundAllocList);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void SysAllocationList::setAllAllocsFndClsValidFlag(bool isValid, const BFDataGroupId& idDataGroup)
{
    BFObjIter iter(*this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

    while (!iter.end())
    {
        SysAllocation *pSysAllocation = dynamic_cast<SysAllocation*>(iter.getObject());

        if (pSysAllocation && !iter.isDummy())
        {
            pSysAllocation->setFieldValid(ifds::SoftCapCheck, idDataGroup, isValid);
            pSysAllocation->setFieldUpdated(ifds::SoftCapCheck, idDataGroup, true);
        }

        ++iter;
    }
}

//**********************************************************

bool SysAllocationList::hasCappedFund ( const BFDataGroupId& idDataGroup )
{   
   Systematic *pSystematic = NULL;
   pSystematic = dynamic_cast< Systematic * >(getParent());
   DString dstrFundCode;
   BFObjIter iter(*this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);   
   while(!iter.end()) {
      iter.getObject()->getField (ifds::FundCode, dstrFundCode, idDataGroup );            
      if ( pSystematic && pSystematic->isCappedFund ( dstrFundCode, idDataGroup ) )
         return true; 
      ++iter;
   }
   return false;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/SysAllocationList.cpp-arc  $
 * 
 *    Rev 1.44   Jul 06 2012 17:00:12   if991250
 * IN2640544  - do not validate sysallocation for dummy systematics
 * 
 *    Rev 1.43   Sep 05 2011 10:17:04   panatcha
 * IN2640544  - Unexpected error message when deleting a SWP
 * 
 *    Rev 1.42   Feb 22 2008 13:18:44   yingz
 * incident 1186526, 835643 and 846177, allcation error
 * 
 *    Rev 1.41   Dec 10 2004 17:35:26   hernando
 * PET910 - Changed pow call.
 * 
 *    Rev 1.40   Dec 10 2004 13:19:30   Fengyong
 * PET10034197 - PAC allocation not being changed after account level AMS set flag change pac/swp is yes.
 * 
 *    Rev 1.39   Nov 14 2004 14:56:18   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.38   Sep 04 2003 17:26:16   HSUCHIN
 * PTS 10021181 - bug fix for capped fund rule for normal Allocations
 * Added method hasCappedFund to check allocations for capped fund.
 * 
 *    Rev 1.37   Aug 25 2003 15:42:36   HSUCHIN
 * fixed bug with systematic updating for AMS accounts when nothing has changed.
 * 
 *    Rev 1.36   Aug 22 2003 13:05:32   HSUCHIN
 * bug fix for account level ams.  It is no longer looking at code 0001 for acct level ams.
 * 
 *    Rev 1.35   Aug 15 2003 15:29:54   HSUCHIN
 * AMS Restriction enhancement to default allocation.  Change the way the AMS Fund list is retrieved.
 * 
 *    Rev 1.34   Jun 11 2003 15:47:44   popescu
 * fixed crash when adding  new PAC with default allocation
 * 
 *    Rev 1.33   May 13 2003 20:05:20   popescu
 * FIxed pts 10016214, enable the split commission button in the split commission dialog if there is split commiision for the funds in allocation, after the allocation has been set
 * 
 *    Rev 1.32   May 06 2003 11:19:02   popescu
 * PTS 10016243, fix of the internal problem issue
 * 
 *    Rev 1.31   Mar 21 2003 18:25:26   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.30   Dec 03 2002 14:24:04   KOVACSRO
 * Added AMS allocations
 * 
 *    Rev 1.29   Oct 09 2002 23:55:04   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.28   Aug 29 2002 12:56:42   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.27   Jul 15 2002 14:47:26   YINGBAOL
 * PTS 10008987
 * 
 *    Rev 1.26   Jun 04 2002 17:32:28   ZHANGCEL
 * PTS 10008333: bug fix for the persentage and AllocAmount calculate problem -- added a new function: getTotalAllocAmountPercent() and made some code changes
 * 
 *    Rev 1.25   22 May 2002 18:29:54   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.24   22 Apr 2002 10:05:38   KOVACSRO
 * Rel.47 : new design for Allocations.
 * 
 *    Rev 1.23   Feb 25 2002 18:55:52   PURDYECH
 * Phase 1 of BFData Rollout - Base Component Compatibility
 * 
 *    Rev 1.22   09 Nov 2001 10:13:42   HSUCHIN
 * bug fix for getSplitCommissionList
 * 
 *    Rev 1.21   Aug 21 2001 14:05:04   YINGBAOL
 * change for account level trasactiob builder
 * 
 *    Rev 1.20   Aug 15 2001 19:09:32   YINGBAOL
 * fix bug
 * 
 *    Rev 1.19   Aug 15 2001 10:09:44   YINGBAOL
 * fix validation for dummy records.
 * 
 *    Rev 1.18   03 Aug 2001 13:39:58   WINNIE
 * bug fix for currecy for non-multicurrency company
 * 
 *    Rev 1.17   Jul 29 2001 14:57:10   YINGBAOL
 * fix multicurrency
 * 
 *    Rev 1.16   Jun 25 2001 15:00:32   HERNANDO
 * Added iInitialization of  _dstrMultiCurrency.
 * 
 *    Rev 1.15   Jun 22 2001 16:59:10   HERNANDO
 * doValidateAll verifies that the Fund Currency for all is the same for single currency clients.
 * 
 *    Rev 1.14   15 Jun 2001 14:25:10   KOVACSRO
 * Some changes for multi currency check.
 * 
 *    Rev 1.13   11 May 2001 09:23:58   HSUCHIN
 * Sync up with SSB (1.11.2.3)
 * 
 *    Rev 1.11.2.3   02 May 2001 15:11:42   HSUCHIN
 * null pointer bug fix
 * 
 *    Rev 1.11.2.2   Apr 26 2001 12:58:34   JANKAREN
 * Add getNbrOfAllocInList & getCurrency
 * 
 *    Rev 1.11.2.1   25 Apr 2001 13:39:06   HSUCHIN
 * Validate all now checks SplitComm flag before retriving SplitComm List
 * 
 *    Rev 1.11.2.0   14 Apr 2001 10:33:22   HSUCHIN
 * Added function to retrive the SplitCommissionList.  doValidateall now also validates the SplitCommissionList
 * 
 *    Rev 1.11   03 Apr 2001 20:16:54   HSUCHIN
 * implemented default splitcommissions
 * 
 *    Rev 1.10   01 Apr 2001 12:50:32   HSUCHIN
 * added default split commission and code cleanup
 * 
 *    Rev 1.9   Mar 21 2001 13:29:26   HSUCHIN
 * added function to calculate totals for the list
 * 
 *    Rev 1.8   Dec 17 2000 20:24:30   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.7   Nov 16 2000 15:53:42   HUANGSHA
 * fixed in ModelOffer(..)
 * 
 *    Rev 1.6   Oct 11 2000 09:53:42   HUANGSHA
 * added initWithDefaultAllocation() function
 * 
 *    Rev 1.5   Jul 04 2000 10:00:20   YINGBAOL
 * fix add copy crash
 * 
 *    Rev 1.4   Jun 13 2000 18:23:26   DT24433
 * new Infra interfaces use ClientLocale
 * 
 *    Rev 1.3   May 19 2000 17:10:22   HUANGSHA
 * Removed the Market Condition for AT
 * 
 *    Rev 1.2   Apr 18 2000 13:33:18   YINGZ
 * addcopy
 * 
 *    Rev 1.1   Apr 17 2000 17:15:56   YINGZ
 * add AddCopy function for systematic
 * 
 *    Rev 1.0   Feb 15 2000 11:00:06   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.15   Feb 03 2000 10:51:06   BUZILA
 * INIT_TO_DEFAULT flag took out
 * 
 *    Rev 1.14   Feb 01 2000 14:36:28   BUZILA
 * added lValidateGroup parameter to doValidateAll method
 * 
 *    Rev 1.13   Jan 28 2000 14:43:12   PRAGERYA
 * For Shaobo
 * 
 *    Rev 1.12   Jan 26 2000 19:41:54   PRAGERYA
 * For release
 * 
 *    Rev 1.11   Jan 24 2000 18:11:26   PRAGERYA
 * Fixes
 * 
 *    Rev 1.10   Dec 24 1999 17:10:16   PRAGERYA
 * For internal release
 * 
 *    Rev 1.9   Dec 22 1999 11:21:54   PRAGERYA
 * For Jerry
 * 
 *    Rev 1.8   Dec 12 1999 16:25:56   POPESCUS
 * Xchgdata issue; create and delete the object in the CBO
// 
*/