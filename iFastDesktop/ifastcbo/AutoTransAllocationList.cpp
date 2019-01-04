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
// ^FILE   : AutoTransAllocationList.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : March 27, 2000
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : AutoTransAllocationList
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************


#include "stdafx.h"
#include "autotransallocationlist.hpp"
#include "autoaccttransallocation.hpp"
#include "autotransallocation.hpp"
#include <ifastdataimpl\dse_dstc0006_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0007_req.hpp>
#include <ifastdataimpl\dse_dstc0007_vwrepeat_record.hpp>
#include "funddetaillist.hpp"
#include "mgmtco.hpp"
#include "splitcommissionlist.hpp"
#include "systematic.hpp"
#include "dstcworksession.hpp"

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_("AutoTransAllocationList");
}

namespace CND
{
   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
   extern const long ERR_IDENTICAL_FUND_ALLOCS;
   extern const long ERR_SUM_OF_PERCENTAGES_NOT_100;
   extern const long ERR_FUND_CURRENCY_DIFFERENT;

}

namespace ifds
{ 
   extern CLASS_IMPORT const BFTextFieldId FundClass;
   extern CLASS_IMPORT const BFTextFieldId Default;
   extern CLASS_IMPORT const BFTextFieldId Currency;
   extern CLASS_IMPORT const BFTextFieldId MultiCurrency;
   extern CLASS_IMPORT const BFTextFieldId FundClassTradeDate;
   extern CLASS_IMPORT const BFTextFieldId ToSoftCapCheck;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//		Field DD Id,				State Flags,					Group Flags
   {ifds::SettleCurrency, BFCBO::NONE, 0}
};

static const int NUM_FIELDS = sizeof(classFieldInfo) / sizeof(BFCBO::CLASS_FIELD_INFO);

//********************************************************************************
AutoTransAllocationList::AutoTransAllocationList(BFAbstractCBO &parent) : MFCanBFCbo(parent),
_pSystematic(NULL),
_pAtAcctTransAllocation(NULL),
_dstrMultiCurrency(NULL_STRING),
_bAddCopy(false),
_dstrAddCopyKey(NULL_STRING),
_strPacSwpId(NULL_STRING),
_strAccount(NULL_STRING),
_bHasAcct(false)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   registerMemberData(NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL);
   setObjectAsList(); 
   getWorkSession().getOption(ifds::MultiCurrency, _dstrMultiCurrency, BF::HOST, false);
}

//********************************************************************************
AutoTransAllocationList::~AutoTransAllocationList()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//*********************************************************************************
SEVERITY AutoTransAllocationList::init()
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));
   return(GETCURRENTHIGHESTSEVERITY());
}

//*******************************************************************
SEVERITY AutoTransAllocationList::init(AutoAcctTransAllocation* pAtAcctTrans,
   const BFDataGroupId& idDataGroup, const DString& strPacSwpId, const DString& strAccount, 
   const BFData &data, bool bHasAcct)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   setAtAcctTransAlloc(pAtAcctTrans);
   _strPacSwpId = strPacSwpId;
   _strAccount = strAccount;
   _bHasAcct = bHasAcct;
   createObjectForEachRepeat(data);
   clearUpdatedFlags(idDataGroup, true);
   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************
SEVERITY AutoTransAllocationList::doCreateObject(const BFData& data, BFCBO *&pObjOut)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateObject"));

   DString dstrLevel = data.getElementValue(I_("Level"));
   DString dstrPACSWPId = data.getElementValue(I_("PACSWPId"));
   DString dstrAccount = data.getElementValue(ifds::AllocAccountNum);

   dstrLevel.strip();
   dstrPACSWPId.strip().stripLeading(I_CHAR('0'));
   dstrAccount.strip().stripLeading(I_CHAR('0'));                                                       
   if(dstrPACSWPId.compare(_strPacSwpId) == 0 && 
      dstrLevel == I_("3") && dstrAccount == _strAccount)
   {
      AutoTransAllocation *pAutoTransAllocation = new AutoTransAllocation(*this);

      pAutoTransAllocation->init(data);
      pAutoTransAllocation->setAutoAcctTransAllocation(getAtAcctTransAlloc());
      pAutoTransAllocation->setSystematicPtr(getSystematicPtr());
      if (_bHasAcct)
      {
         DString strAcct, strFundTo, strClassTo, strAmount, strSplitComm;
         
         getSystematicPtr()->getParameter(strAcct, strFundTo, strClassTo, strAmount);
         pAutoTransAllocation->setParameter(strAcct, strFundTo, strClassTo, strAmount);
         getSystematicPtr()->getField(ifds::SplitComm, strSplitComm, BF::HOST, false);
         pAutoTransAllocation->setField(ifds::SplitComm, strSplitComm, BF::HOST, false, false);
      }
      if(_dstrMultiCurrency == I_("N"))
      {
         DString dstrFundCode, dstrClassCode, dstrCurrency;

         dstrFundCode = data.getElementValue(I_("FundCode"));
         dstrClassCode = data.getElementValue(I_("ClassCode"));
         setCurrency(dstrFundCode, dstrClassCode, BF::HOST);
      }
      pObjOut = pAutoTransAllocation;
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************
SEVERITY AutoTransAllocationList::initNew(AutoAcctTransAllocation* pAtAcctTrans, 
   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("initNew"));

   setAtAcctTransAlloc(pAtAcctTrans);

   BFObjectKey objKey;

   getNewListItem(objKey);
   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************
SEVERITY AutoTransAllocationList::doCreateNewObject(BFCBO *& pBase,
   DString &strKey, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateNewObject"));

   if(_bAddCopy)
   {
      strKey = _dstrAddCopyKey;
   }
   
   AutoTransAllocation *pAtAllocation = new AutoTransAllocation(*this);

   pAtAllocation->init();
   pBase = pAtAllocation;
   pAtAllocation->setAutoAcctTransAllocation(getAtAcctTransAlloc());
   pAtAllocation->setSystematicPtr(getSystematicPtr());
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AutoTransAllocationList::doValidateAll(const BFDataGroupId& idDataGroup, long lValidateGroup) 
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll"));
   I_CHAR *stopstring;
   std::set< DString > setCharacteristic;
   double dMaxPercentage = 0, dTotalPercentage = 0;
   double dMaxAmount = 0, dTotalAmount = 0;
   DString dstrMaxPercentageKey, dstrMaxAmountKey;
   bool bInitializeCurrency = true;

   // 1. iterate through the list
   BFObjIter iter1(*this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
   if(iter1.end())
   {
      ADDCONDITIONFROMFILE(CND::ERR_SUM_OF_PERCENTAGES_NOT_100);
      return(GETCURRENTHIGHESTSEVERITY());
   }
   SplitCommissionList *pSplitCommissionList = NULL;
   AutoTransAllocation *pAutoTransAllocation = NULL;
   while(!iter1.end())
   {	  
      BFAbstractCBO* pBf = iter1.getObject();
      DString str(NULL_STRING);
      (dynamic_cast<AutoTransAllocation* >(pBf))->validateField(ifds::FundClass, str, idDataGroup);

	  if ( !iter1.isDummy() )
	  {
			// 1-1. Verify that all fund-class pairs are unique
			DString dstrFundCode;
			pBf->getField(ifds::FundCode, dstrFundCode, idDataGroup);
			dstrFundCode.strip();

			DString dstrClassCode;
			pBf->getField(ifds::ClassCode, dstrClassCode, idDataGroup);
			dstrClassCode.strip();

			DString dstr = dstrFundCode + dstrClassCode;

			if(!setCharacteristic.insert(dstr).second)
				ADDCONDITIONFROMFILE(CND::ERR_IDENTICAL_FUND_ALLOCS);

			// 1-2. calculate total percentage and maximal percentage
			DString dstrPercentage;
			pBf->getField(ifds::Percentage, dstrPercentage, 
							idDataGroup);
			dstrPercentage.strip().stripAll(I_CHAR(','));
			double dPercentage = wcstod(dstrPercentage.c_str(), &stopstring);
			if(dPercentage > dMaxPercentage)
			{
				dMaxPercentage = dPercentage;
				dstrMaxPercentageKey = iter1.getStringKey();
			}
			dTotalPercentage += dPercentage;

			// 1-3. calculate total amount and maximal amount
			DString dstrAmount;
			pBf->getField(ifds::AllocAmount, dstrAmount, 
							idDataGroup);
			dstrAmount.strip().stripAll(I_CHAR(','));
			double dAmount = wcstod(dstrAmount.c_str(), &stopstring);
			if(dAmount > dMaxAmount)
			{
				dMaxAmount = dAmount;
				dstrMaxAmountKey = iter1.getStringKey();
			}
			dTotalAmount += dAmount;
			DString dstrSplitComm;      
			pAutoTransAllocation = dynamic_cast <AutoTransAllocation*>(iter1.getObject());

			// validate fund currency to ensure all currency are the same for single currency system
			if(_dstrMultiCurrency == I_("N"))
			{
				if(bInitializeCurrency)
				{
					setFieldNoValidate(ifds::SettleCurrency, NULL_STRING, idDataGroup, false);
					bInitializeCurrency = false;
				}
				if(setCurrency(dstrFundCode,  dstrClassCode, idDataGroup) > WARNING)
					return(GETCURRENTHIGHESTSEVERITY());
			}

			// validate split commission
			pAutoTransAllocation->getField (ifds::SplitComm, dstrSplitComm, idDataGroup, false);
			pAutoTransAllocation->getSplitCommissionList (pSplitCommissionList, idDataGroup);
			if(dstrSplitComm == I_("Y") && pSplitCommissionList)
			{
				pSplitCommissionList->validateAll(idDataGroup, lValidateGroup);      
			}
	  }

      ++iter1;
   }

   // 2. retrieve the systematic amount
   DString dstrTotalAcctAmount;
   getAtAcctTransAlloc()->getField(ifds::AllocAmount, dstrTotalAcctAmount, idDataGroup);
   dstrTotalAcctAmount.strip().stripAll(I_CHAR(','));
   double dTotalAcctAmount = wcstod(dstrTotalAcctAmount.c_str(), &stopstring);

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
   double dAllocAmountDiff = dTotalAmount - dTotalAcctAmount;
   if(fabs(dPercentageDiff) < dPercentageThreshold)
   {
      if(fabs(dAllocAmountDiff) >= dAllocAmountThreshold)
      {
         dMaxAmount -= dAllocAmountDiff;
         char buffer[ 50 ];
         DString dstrMaxAmount = DStringA(_gcvt(dMaxAmount, 30, buffer));
         iter1.positionByKey(dstrMaxAmountKey);
         iter1.getObject()->setField(ifds::AllocAmount, dstrMaxAmount, 
                                      idDataGroup);
      }
   }
   else if(fabs(dAllocAmountDiff) < dAllocAmountThreshold)
   {
      dMaxPercentage -= dPercentageDiff;
      char buffer[ 50 ];
      DString dstrMaxPercentage = DStringA(_gcvt(dMaxPercentage, 30, 
                                                   buffer));
      iter1.positionByKey(dstrMaxPercentageKey);
      iter1.getObject()->setField(ifds::Percentage, dstrMaxPercentage, 
                                   idDataGroup);
   }
   else
      ADDCONDITIONFROMFILE(CND::ERR_SUM_OF_PERCENTAGES_NOT_100);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void AutoTransAllocationList::ModelOffer(AutoTransAllocationList *Model, const BFDataGroupId& idDataGroup)
{
   AutoTransAllocation * pAutoTransAllocation;
   BFObjectKey objKey;
   _bAddCopy = true;

   BFObjIter iterDest(*this, idDataGroup);

   for(BFObjIter Iter(*Model, idDataGroup); !Iter.end(); ++Iter)
   {
      objKey = Iter.getKey(); // we don't want to ruin old key, so make a copy
      objKey.setActivity(OBJ_ACTIVITY_ADDED);
      _dstrAddCopyKey = Iter.getStringKey();
      objKey.setDataGroupId(idDataGroup);

      if(iterDest.end())
      {
         pAutoTransAllocation = dynamic_cast< AutoTransAllocation * >(getNewListItem(objKey));
      }
      else
      {
         pAutoTransAllocation = dynamic_cast< AutoTransAllocation * >(iterDest.getObject());
         ++iterDest;
      }
      pAutoTransAllocation->setSystematicPtr(getSystematicPtr());
      pAutoTransAllocation->ModelOffer(dynamic_cast< AutoTransAllocation * >(Iter.getObject()), idDataGroup);
   }
   _bAddCopy = false;
}

//******************************************************************************
void AutoTransAllocationList::getTotal (const BFFieldId& idField, DString &dstrTotal, const BFDataGroupId& idDataGroup)
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
void AutoTransAllocationList::GetDefaultSplitComm (const BFDataGroupId& idDataGroup)
{
   BFObjIter iter(*this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);   
   while(!iter.end())
   {
      static_cast <AutoTransAllocation*>(iter.getObject())->GetDefaultSplitComm (idDataGroup);
      ++iter;
   }
}

//******************************************************************************
void AutoTransAllocationList::GetSplitCommFlag (const BFDataGroupId& idDataGroup, DString &dstrSplitComm)
{
   BFObjIter iter(*this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
   while(!iter.end())
   {
      static_cast <AutoTransAllocation*>(iter.getObject())->getField(ifds::SplitComm, dstrSplitComm, idDataGroup);
      if(dstrSplitComm == I_("Y"))
         return;
      ++iter;
   }
   dstrSplitComm = I_("N");
}

//******************************************************************************
int AutoTransAllocationList::getNbrOfAllocInList(const BFDataGroupId& idDataGroup)//NON_DELETED
{
   BFObjIter iter(*this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
   return(iter.getNumberOfItemsInList());
}

//******************************************************************************
SEVERITY AutoTransAllocationList::setCurrency(const DString& dstrFundCode, 
                                               const DString& dstrClassCode, 
                                               const BFDataGroupId& idDataGroup) 
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getCurrency"));

	DString dstrCurrency;
	FundDetailList *pFundDetailList = NULL;

	getMgmtCo().getFundDetailList(pFundDetailList);
	if(pFundDetailList)
	{
		pFundDetailList->getField(dstrFundCode, dstrClassCode, ifds::Currency, dstrCurrency, idDataGroup, false); 

		DString dstrPreviousCurrency;
		      
		getField(ifds::SettleCurrency, dstrPreviousCurrency, idDataGroup, false);
		if(dstrPreviousCurrency.strip().empty())
		{
			setField(ifds::SettleCurrency, dstrCurrency.strip(), idDataGroup, false);
		}
		else
		{
			if(dstrPreviousCurrency != dstrCurrency.strip())
			{
				ADDCONDITIONFROMFILE(CND::ERR_FUND_CURRENCY_DIFFERENT);
			}
		}
	}
  
   return(GETCURRENTHIGHESTSEVERITY());
}

//**********************************************************

bool AutoTransAllocationList::hasCappedFund ( const BFDataGroupId& idDataGroup )
{   
   Systematic *pSystematic = NULL;
   pSystematic = dynamic_cast< Systematic * >(getSystematicPtr());
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
void AutoTransAllocationList::setAllAllocsFndClsValidFlag(bool isValid, const BFDataGroupId& idDataGroup)
{
    BFObjIter iter(*this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

    while (!iter.end())
    {
        AutoTransAllocation *pAutoTransAllocation = dynamic_cast<AutoTransAllocation*>(iter.getObject());

        if (pAutoTransAllocation && !iter.isDummy())
        {
            pAutoTransAllocation->setFieldValid(ifds::ToSoftCapCheck, idDataGroup, isValid);
            pAutoTransAllocation->setFieldUpdated(ifds::ToSoftCapCheck, idDataGroup, true);
        }

        ++iter;
    }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AutoTransAllocationList.cpp-arc  $
 // 
 //    Rev 1.33   Sep 12 2006 16:16:32   porteanm
 // Incident 698369 - Issue error message "Fund Currency is different" only for non-dummy records (Problem 2).
 // 
 //    Rev 1.32   Jan 18 2005 17:21:54   hernando
 // PTS10037757 - Changed the pow calls.
 // 
 //    Rev 1.31   Nov 14 2004 14:27:46   purdyech
 // PET910 - .NET Conversion
 // 
 //    Rev 1.30   Sep 04 2003 17:13:50   HSUCHIN
 // PTS 10021181 - bug fix for capped fund rule and AT Allocations
 // Added method to check for capped funds in AT Allocations
 // 
 //    Rev 1.29   May 13 2003 17:07:06   popescu
 // Split commission re-work, part II
 // 
 //    Rev 1.28   May 13 2003 10:05:12   popescu
 // Split commission re-work
 // 
 //    Rev 1.27   May 06 2003 11:18:40   popescu
 // PTS 10016243, fix of the internal problem issue
 // 
 //    Rev 1.26   Mar 21 2003 17:59:44   PURDYECH
 // BFDataGroupId/BFContainerId changeover
 // 
 //    Rev 1.25   Oct 09 2002 23:54:02   PURDYECH
 // PVCS Database Conversion
 // 
 //    Rev 1.24   Aug 29 2002 12:55:04   SMITHDAV
 // ClientLocale and typed field changes.
 // 
 //    Rev 1.23   22 May 2002 18:26:26   PURDYECH
 // BFData Implementation
 // 
 //    Rev 1.22   Feb 25 2002 18:55:10   PURDYECH
 // Phase 1 of BFData Rollout - Base Component Compatibility
 // 
 //    Rev 1.21   09 Nov 2001 10:35:36   HSUCHIN
 // initialized splitcommission list to null
 // 
 //    Rev 1.20   Jun 26 2001 14:17:48   HERNANDO
 // Changed getCurrency() to setCurrency(); validate currency for single-currency system.
 // 
 //    Rev 1.19   Jun 26 2001 12:55:00   PURDYECH
 // Infrastructure Release 1.9 Integration.
 // 
 //    Rev 1.18   09 May 2001 14:17:40   HSUCHIN
 // Sync up with SSB
 // 
 //    Rev 1.17   02 May 2001 15:11:12   HSUCHIN
 // null pointer bug fix
 // 
 //    Rev 1.16   27 Apr 2001 14:39:52   HSUCHIN
 // validateall retrieves split comm list 
 // 
 //    Rev 1.15   Apr 26 2001 10:46:36   JANKAREN
 // Add getNbrOfAllocInList & getCurrency
 // 
 //    Rev 1.14   14 Apr 2001 10:40:10   HSUCHIN
 // doValidateAll also validates split commission
 // 
 //    Rev 1.13   03 Apr 2001 20:13:26   HSUCHIN
 // implemented default split commission
 // 
 //    Rev 1.12   01 Apr 2001 12:57:46   HSUCHIN
 // check in for winnie
 // 
 //    Rev 1.11   Mar 05 2001 16:16:10   YINGBAOL
 // validate fundclass transfer
 // 
 //    Rev 1.10   Dec 17 2000 20:22:36   OLTEANCR
 // changed to use a precompiled header
 // 
 //    Rev 1.9   Nov 16 2000 15:53:14   HUANGSHA
 // fixed in ModelOffer(..)
 // 
 //    Rev 1.8   Aug 24 2000 16:38:56   YINGBAOL
 // clean up file
 // 
 //    Rev 1.7   Jul 26 2000 16:26:34   YINGBAOL
 // change create new item logic
 // 
 //    Rev 1.6   Jun 30 2000 09:54:04   YINGBAOL
 // fix add copy and other bugs
 // 
 //    Rev 1.5   Jun 13 2000 18:20:30   DT24433
 // new Infra interfaces use ClientLocale
 // 
 //    Rev 1.4   May 01 2000 09:39:28   YINGBAOL
 // add validation
 // 
 //    Rev 1.3   Apr 17 2000 17:15:56   YINGZ
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