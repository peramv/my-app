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
// ^FILE   : RegPlanTransferAllocList.cpp
// ^AUTHOR : Mihai Buzila
// ^DATE   : November 4, 2016
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : RegPlanTransferAllocList
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************

#include "stdafx.h"
#include <ifastdataimpl\dse_dstc0473_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0473_vw.hpp>
#include <ifastdataimpl\dse_dstc0473_req.hpp>
#include "RegPlanTransferAlloc.hpp"
#include "RegPlanTransferAlloclist.hpp"

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_("RegPlanTransferAllocList");
   const I_CHAR * const YES = I_("Y");
   const I_CHAR * const NO=I_("N");
}

namespace CND
{
   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
   extern CLASS_IMPORT const long ERR_SUM_OF_PERCENTAGES_NOT_100;
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
   extern CLASS_IMPORT const BFDecimalFieldId Percentage;
   extern CLASS_IMPORT const BFDecimalFieldId Amount;
   extern CLASS_IMPORT const BFTextFieldId PACSWPOverride;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFTextFieldId DefaultAlloc;
   extern CLASS_IMPORT const BFTextFieldId FundAlloc;
   extern CLASS_IMPORT const BFTextFieldId FundClass;
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest REG_PLAN_TRANSF_INQUIRY;            
   extern CLASS_IMPORT const DSTCRequest REG_PLAN_TRANSF_ALLOC_INQUIRY;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
// Field DD Id,   State Flags,   Group Flags
   {ifds::ReplaceAsDefault, BFCBO::NONE, 0}, 
};

static const int NUM_FIELDS = sizeof(classFieldInfo) / sizeof(BFCBO::CLASS_FIELD_INFO);

static BigDecimal bd100 = BigDecimal("100.00");
static BigDecimal bd0 = BigDecimal("0.00");

//********************************************************************************
RegPlanTransferAllocList::RegPlanTransferAllocList(BFAbstractCBO &parent) : MFCanBFCbo(parent)
//   ,_strRegTransferMstrUUID(NULL_STRING)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   isPercent = true;
   registerMemberData(NUM_FIELDS,(const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL);
   setObjectAsList();
}

//********************************************************************************
RegPlanTransferAllocList::~RegPlanTransferAllocList()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}


//********************************************************************************
SEVERITY RegPlanTransferAllocList::init(const BFDataGroupId& idDataGroup, 
   const DString& strRegTransferMstrUUID, const DString& dstrTrack /*= I_("N")*/, const DString& dstrPageName /* = NULL_STRING */)
{
   MAKEFRAME2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   // get info for validation
   dstrRegTransferMstrUUID = strRegTransferMstrUUID;

   {
      // get systematic info
      BFData requestData(ifds::DSTC0473_REQ); 

      DString mgmtCoIdOut;
      requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
      requestData.setElementValue( ifds::RegTransferMstrUUID, dstrRegTransferMstrUUID);
      requestData.setElementValue( ifds::Track, dstrTrack );
      requestData.setElementValue( ifds::Activity, dstrPageName );

      BFData* responseData = new BFData(ifds::DSTC0473_VW);

      ReceiveData(DSTC_REQUEST::REG_PLAN_TRANSF_ALLOC_INQUIRY, requestData, *responseData, DSTCRequestor( getSecurity(), true ) );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY RegPlanTransferAllocList::doCreateObject(const BFData& data, BFCBO *&pObjOut)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateObject"));

   RegPlanTransferAlloc *pRegPlanTransferAlloc= new RegPlanTransferAlloc(*this);

   pRegPlanTransferAlloc->init(data);
   pObjOut = pRegPlanTransferAlloc;

   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************
SEVERITY RegPlanTransferAllocList::initNew(const BFDataGroupId& idDataGroup)
{
   MAKEFRAME2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("initNew"));

   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************
SEVERITY RegPlanTransferAllocList::doCreateNewObject(BFCBO *& pBase, DString &strKey, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateNewObject"));
   RegPlanTransferAlloc *pRegPlanTransferAlloc = new RegPlanTransferAlloc(*this);
   pRegPlanTransferAlloc->setPercentTypeAlloc(idDataGroup, isPercent);
   pRegPlanTransferAlloc->init();
   pBase = pRegPlanTransferAlloc;
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY RegPlanTransferAllocList::doValidateAll(const BFDataGroupId& idDataGroup, long lValidateGroup) 
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll"));
   BigDecimal bdTotalAmount;
   BigDecimal bdTotalPercentage;

   getTotalAllocAmountPercent(idDataGroup, bdTotalAmount, bdTotalPercentage);
   if(bdTotalPercentage != bd100)
   {
      ADDCONDITIONFROMFILE(CND::ERR_SUM_OF_PERCENTAGES_NOT_100);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
void RegPlanTransferAllocList::getTotalAllocAmountPercent(const BFDataGroupId& idDataGroup, double &dTotalAmount, double &dTotalPercentage)
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
         iter.getObject()->getField(ifds::Amount, dstrTemp, idDataGroup, false);
         dstrTemp.strip().stripAll(I_CHAR(','));
         dTotalAmount      += DSTCommonFunctions::convertToDouble(dstrTemp);
      }
      ++iter;
   }
}

//******************************************************************************
void RegPlanTransferAllocList::getTotalAllocAmountPercent(const BFDataGroupId& idDataGroup, BigDecimal &dTotalAmount, BigDecimal &dTotalPercentage)
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
         dTotalPercentage += dstrTemp;

         // Total Amount
         iter.getObject()->getField(ifds::Amount, dstrTemp, idDataGroup, false);
         dstrTemp.strip().stripAll(I_CHAR(','));
         dTotalAmount      += dstrTemp;
      }
      ++iter;
   }
}

//******************************************************************************
void RegPlanTransferAllocList::getTotal (const BFFieldId& idField, DString &dstrTotal, const BFDataGroupId& idDataGroup)
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

int RegPlanTransferAllocList::getNbrOfAllocInList(const BFDataGroupId& idDataGroup)//NON_DELETED
{
   BFObjIter iter(*this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
   return(iter.getNumberOfItemsInList());
}


//**********************************************************
SEVERITY RegPlanTransferAllocList::doApplyRelatedChanges(const BFFieldId& idField, 
   const BFDataGroupId& idDataGroup)
{
   return(NO_CONDITION);
}

//**********************************************************
void RegPlanTransferAllocList::setPercentTypeAlloc(const BFDataGroupId& idDataGroup, boolean isPercent)
{
   this->isPercent = isPercent;
   BFObjIter iter(*this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
   while(!iter.end())
   {
      RegPlanTransferAlloc* alloc = dynamic_cast<RegPlanTransferAlloc*>(iter.getObject());
      if(alloc != NULL)
      {
         alloc->setPercentTypeAlloc(idDataGroup, isPercent);
      }
      ++iter;
   }
}

void RegPlanTransferAllocList::ModelOffer(RegPlanTransferAllocList *Model, const BFDataGroupId& idDataGroup)
{
   RegPlanTransferAlloc * pRegPlanTransferAlloc;
   BFObjectKey objKey;

   BFObjIter iterDest(*this, idDataGroup);

   for(BFObjIter Iter(*Model, idDataGroup); !Iter.end(); ++Iter)
   {
      if(iterDest.end())
      {
         pRegPlanTransferAlloc = static_cast< RegPlanTransferAlloc* >(getNewListItem(objKey));
         pRegPlanTransferAlloc->ModelOffer(static_cast<RegPlanTransferAlloc* >(Iter.getObject()), idDataGroup);
      }
      else
      {
         pRegPlanTransferAlloc = static_cast<RegPlanTransferAlloc* >(iterDest.getObject());
         pRegPlanTransferAlloc->ModelOffer(static_cast<RegPlanTransferAlloc* >(Iter.getObject()), idDataGroup);
         ++iterDest;
      }
   }
}

void RegPlanTransferAllocList::updateTotalAmount(const BFDataGroupId& idDataGroup, BigDecimal totalAmount)
{
   RegPlanTransferAlloc * pRegPlanTransferAlloc;
   BFObjectKey objKey;


   for(BFObjIter Iter(*this, idDataGroup); !Iter.end(); ++Iter)
   {
      pRegPlanTransferAlloc = static_cast<RegPlanTransferAlloc* >(Iter.getObject());
      DString amt;
      pRegPlanTransferAlloc->getField(this->isPercent ? ifds::Percentage : ifds::Amount, amt, idDataGroup, false);
      
      BigDecimal amtDec(amt);
      if(this->isPercent)
      {
         BigDecimal prcDec(amt);
         BigDecimal amtDec = prcDec*totalAmount/100;
         DString dstrAmount = amtDec.asDString();
         pRegPlanTransferAlloc->setField(ifds::Amount, dstrAmount, idDataGroup, false, true);
      }
      else
      {
         BigDecimal amtDec(amt);
         if(totalAmount != bd0 )
         {
            BigDecimal  prcDec = amtDec*100/totalAmount;
            DString dstrPercentage = prcDec.asDString();
            pRegPlanTransferAlloc->setField(ifds::Percentage, dstrPercentage, idDataGroup, false, true);
         }
      }
   }
}
