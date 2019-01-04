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
//    Copyright 2002 By International Financial
//
//
//******************************************************************************
//
// ^FILE   : RESPBeneficiaryAllocationList.cpp
// ^AUTHOR : 
// ^DATE   : Febrary, 2010
//
// ^CLASS    : RESPBeneficiaryAllocationList 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "respbeneficiaryallocationlist.hpp"
#include "respbeneficiaryallocation.hpp"
#include "accountentityxref.hpp"
#include "entity.hpp"
#include "RESPInfoUpdateValidationList.hpp"
#include "resptransactionsdetails.hpp"
#include "resptransactionslist.hpp"
#include "transactiondetails.hpp"
#include <ifastdataimpl\dse_dstc0402_req.hpp>
#include <ifastdataimpl\dse_dstc0402_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0402_vw.hpp>
#include <ifastdataimpl\dse_dstc0403_req.hpp>
#include <ifastdataimpl\dse_dstc0050_vwrepeat_record.hpp>

#include "mgmtco.hpp"


namespace DSTC_REQUEST
{
	extern CLASS_IMPORT const DSTCRequest RESP_BENEF_ALLOCATION_INQUIRY;
}

namespace  
{
   const I_CHAR * const CLASSNAME		= I_( "RESPBeneficiaryAllocationList");  
   const I_CHAR * const BENEF_NAME		= I_("BENNAME");
   const I_CHAR * const UNITS           = I_( "U" );
   const I_CHAR * const NEW             = I_( "New" );
   const I_CHAR * const PENDING         = I_( "Pend" );
   const I_CHAR * const PROCESSED       = I_( "Proc" );
   const I_CHAR * const NO              = I_( "N" );
   const I_CHAR * const HISTORY			= I_( "H" );
   const double dSmallValue             = .0000000001;
}

namespace ifds
{   
	extern CLASS_IMPORT const BFTextFieldId AmtType;
	extern CLASS_IMPORT const BFTextFieldId LastName;
	extern CLASS_IMPORT const BFTextFieldId FirstName;
	extern CLASS_IMPORT const BFTextFieldId Currency;
	extern CLASS_IMPORT const BFDecimalFieldId Amount;
	extern CLASS_IMPORT const BFIntegerFieldId WarnCode;
	extern CLASS_IMPORT const BFTextFieldId TaxType;
	extern CLASS_IMPORT const BFTextFieldId HRDCPending;
	extern CLASS_IMPORT const BFTextFieldId HRDCRespPending;
}

namespace CND
{ 	
	extern const long ERR_DUPLICATE_RECORD;	
	extern const long ERR_RESP_BENEF_ALLOCATIONS_MISSING;
	extern const long ERR_BENEFICIARY_NOT_EFFECTIVE;
	extern const long ERR_SUM_OF_PERCENTAGES_NOT_100;
	extern const long ERR_ALLOCAMOUNT_GREATER_THAN_TOTAL;
	extern const long ERR_ADJUSTMENT_REQUIRED;
	extern const long WARN_ADJUSTMENT_MAY_BE_REQUIRED;   
	extern const long ERR_SYS_TRIG_AMEND_AND_RECAL_QESI_NOTIONAL_BALANCE;
	extern const long WARN_SYS_TRIG_AMEND_AND_RECAL_QESI_NOTIONAL_BALANCE;
	extern const long ERR_TRANSACTION_AWAITING_HRSDC_RESPONSE_CANNOT_CHANGE_ALLOCATIONS;
	extern const long WARN_TRANSACTION_AWAITING_HRSDC_RESPONSE_CANNOT_CHANGE_ALLOCATIONS;
}
namespace IFASTERR
{
	extern CLASS_IMPORT I_CHAR * const AMENDMENT_MAY_BE_REQUIRED;
	extern CLASS_IMPORT I_CHAR * const ADJUSTMENT_MAY_BE_REQUIRED;
	extern CLASS_IMPORT I_CHAR * const SYS_TRIG_AMEND_AND_RECAL_QESI_NOTIONAL_BALANCE;
	extern CLASS_IMPORT I_CHAR * const TRANSACTION_AWAITING_HRSDC_RESPONSE_CANNOT_CHANGE_ALLOCATIONS;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
	{ ifds::EffectiveDate,  BFCBO::CALCULATED_FIELD, 0 }, 
	{ ifds::AmtType,        BFCBO::CALCULATED_FIELD, 0 }, 
	{ ifds::Amount,         BFCBO::CALCULATED_FIELD, 0 }, 
	{ ifds::Currency,       BFCBO::CALCULATED_FIELD, 0 }, 
	{ ifds::TransId,        BFCBO::CALCULATED_FIELD, 0 }, 
	{ ifds::AccountNum,	    BFCBO::CALCULATED_FIELD, 0 }, 
	{ ifds::CallType,	    BFCBO::CALCULATED_FIELD, 0 }, 
	{ ifds::TradeType,	    BFCBO::CALCULATED_FIELD, 0 },
	{ ifds::HRDCPending,	BFCBO::NONE, 0 },
	{ ifds::HRDCRespPending,BFCBO::NONE, 0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) 
                              / sizeof( BFCBO::CLASS_FIELD_INFO );

//*********************************************************************************
RESPBeneficiaryAllocationList::RESPBeneficiaryAllocationList (BFAbstractCBO &parent) : 
MFCanBFCbo (parent),
_bSetFieldsReadOnly (false)
{
	TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0, NULL/*(const CLASS_OBJECT_INFO *)&classObjectInfo*/ );
	setObjectAsList();
}

//*********************************************************************************
RESPBeneficiaryAllocationList::~RESPBeneficiaryAllocationList()
{
	TRACE_DESTRUCTOR (CLASSNAME);
}

//*********************************************************************************

//*********************************************************************************
SEVERITY RESPBeneficiaryAllocationList::init ( const DString &accountNum,
                                               const DString &transId,                                              
											              const DString& tradeType, /*=I_("Pend")*/
                                               bool bSetFieldsReadOnly, /*=false*/
                                               const DString &dstrTrack, /*=I_("N")*/
                                               const DString &dstrPageName /*=NULL_STRING*/)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

	_bSetFieldsReadOnly = bSetFieldsReadOnly;
   setFieldNoValidate (ifds::CallType, I_("U"), BF::HOST, false);
   setFieldNoValidate (ifds::TransId, transId, BF::HOST, false);
   setFieldNoValidate (ifds::AccountNum, accountNum, BF::HOST, false);
   setFieldNoValidate (ifds::TradeType, tradeType, BF::HOST, false);

	DString mgmtCoIdOut;	
	BFData requestData (ifds::DSTC0402_REQ);
		
	requestData.setElementValue (ifds::TransId, transId);
	requestData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
	requestData.setElementValue (ifds::Track, dstrTrack);
	requestData.setElementValue (ifds::Activity, dstrPageName);
	
	ReceiveData (DSTC_REQUEST::RESP_BENEF_ALLOCATION_INQUIRY, requestData, ifds::DSTC0402_VW, DSTCRequestor (getSecurity(), false, false));
	   
	return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************
SEVERITY RESPBeneficiaryAllocationList::initNew (const DString &accountNum,
                                                 const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("initNew"));
	setFieldNoValidate (ifds::AccountNum, accountNum, idDataGroup, false);
	setFieldNoValidate (ifds::CallType, I_("U"), idDataGroup, false);
	setFieldNoValidate (ifds::TradeType, NEW, idDataGroup, false);
	return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************
SEVERITY RESPBeneficiaryAllocationList::doCreateObject (const BFData& data, BFCBO *&pObjOut)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ));
	   
	pObjOut =  new RESPBeneficiaryAllocation( *this );
	((RESPBeneficiaryAllocation* )pObjOut )->init (data, _bSetFieldsReadOnly);
	   
	return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************
SEVERITY RESPBeneficiaryAllocationList::doCreateNewObject (BFCBO *&pBase, DString &strKey, const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateNewObject"));
	  
	RESPBeneficiaryAllocation* pRESPBeneficiaryAllocation = new RESPBeneficiaryAllocation (*this);

	// need to check this in: ivanka
	pRESPBeneficiaryAllocation->initNew (idDataGroup, _bSetFieldsReadOnly);

	pBase = pRESPBeneficiaryAllocation;
	
	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RESPBeneficiaryAllocationList::add100PercentBeneAlloc (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("add100PercentBeneAlloc"));
	DString beneficiaryList;

   AccountEntityXref *pAccountEntityXref (NULL);
   
   if ( getWorkSession().getAccountEntityXref ( idDataGroup, 
                                                pAccountEntityXref) <= WARNING && 
        pAccountEntityXref)
   {
      if (getBeneficiaryMasterList (beneficiaryList, idDataGroup) <= WARNING)
      {
         I_CHAR *temp = const_cast<I_CHAR*> (beneficiaryList.c_str ());
         DString entityId,
            beneName;
         
         do
         {
            temp = parseIdiString (temp, entityId, beneName);
            Entity *pEntity (NULL);

            if  (getWorkSession().getEntity (idDataGroup, entityId, pEntity) <= WARNING && 
                 pEntity)
            {
	            DString strKey;
               
               AccountEntityXref::buildPartialKeyForEntityId (strKey, entityId);
               BFObjIter iterEntity (*pAccountEntityXref, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED);

               if (iterEntity.begin (OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, strKey))
               {
                  DString respAllocPrcnt;

                  iterEntity.getObject () ->getField (ifds::BenPercentage, respAllocPrcnt, idDataGroup, false);
                  double dRespAllocPrcnt = DSTCommonFunctions::convertToDouble (respAllocPrcnt);
                  if (dRespAllocPrcnt > 0)
                  {
                     BFObjectKey objKey (entityId, idDataGroup);
                     BFCBO *pNewItem = getNewListItem (objKey);

                     if (pNewItem)
                     {
                        pNewItem ->setField (ifds::RESPBenefId, entityId, idDataGroup, false);
                        pNewItem ->setField (ifds::RESPAllocPrcnt, respAllocPrcnt, idDataGroup, false);
                     }
                  }
               }
            }
         } while (temp && temp != NULL_STRING && *temp);      
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RESPBeneficiaryAllocationList::checkDuplicate (const RESPBeneficiaryAllocation *pRESPBeneficiaryAllocationToCheck, const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "checkDuplicate" ) );   	
	
	DString dstrEntityIdToCheck;
	
	pRESPBeneficiaryAllocationToCheck->getField( ifds::RESPBenefId, dstrEntityIdToCheck, idDataGroup );

	bool bHasDuplicate = false;
	
	//check first whether in the list (in memory) we have a duplicate
	BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
	iter.begin();

	while (!iter.end())
	{
		RESPBeneficiaryAllocation *pRESPBeneficiaryAllocation = dynamic_cast<RESPBeneficiaryAllocation*>(iter.getObject());
		// Don't check against itself
		if ( pRESPBeneficiaryAllocation != pRESPBeneficiaryAllocationToCheck )
		{
			DString dstrCurrentEntityId;

			pRESPBeneficiaryAllocation->getField( ifds::RESPBenefId, dstrCurrentEntityId, idDataGroup );
			
			if (dstrCurrentEntityId  == dstrEntityIdToCheck )
			{
				bHasDuplicate = true;
				break;
			}
		}
		++iter;
	}

	if ( bHasDuplicate )
	{
		ADDCONDITIONFROMFILE(CND::ERR_DUPLICATE_RECORD);
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RESPBeneficiaryAllocationList::doApplyRelatedChanges (const BFFieldId& idField, 
                                                               const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));

   if (idField == ifds::Amount)
   {
      setAmount (idDataGroup);
   }
   
   setFieldUpdated (idField, idDataGroup, false);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RESPBeneficiaryAllocationList::setAmount (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("setAmount"));
      
   RESPBeneficiaryAllocation *pRESPBeneAlloc = NULL;
   bool bUpdated = false;

   BFObjIter iterAlloc( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   iterAlloc.begin();
   while(!iterAlloc.end())
   {
      pRESPBeneAlloc = dynamic_cast <RESPBeneficiaryAllocation*> (iterAlloc.getObject());
      
      if(pRESPBeneAlloc->isUpdatedForDataGroup (idDataGroup, false))
      {
         bUpdated = true;
         break;
      }
      ++iterAlloc;
   } 

   if (!bUpdated)
	   return(GETCURRENTHIGHESTSEVERITY());
   
   DString strTotalAmount;
   
   getField (ifds::Amount, strTotalAmount, idDataGroup, false);
   
   double dTotalAmount (atof (strTotalAmount.strip().asA().c_str())),
      dTotalPercentage (0),
      dTotalAllocAmount(0);

   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   int iAllocCnt = 0;
   int iAllocNum = iter.getNumberOfItemsInList();
   
   while (!iter.end())
   {
      ++iAllocCnt;

      DString strAllocPercent, 
         dstrAllocAmount;
      
      RESPBeneficiaryAllocation* pRESPBeneficiaryAllocation = 
            dynamic_cast<RESPBeneficiaryAllocation*>(iter.getObject());
      
      assert (pRESPBeneficiaryAllocation);
      
      pRESPBeneficiaryAllocation->getField (ifds::RESPAllocPrcnt, strAllocPercent, idDataGroup, false);
      double dAllocPercent = DSTCommonFunctions::convertToDouble(strAllocPercent);
      dTotalPercentage += dAllocPercent;
      double dAllocAmount(0);
      if (iAllocCnt < iAllocNum)//if not the last allocation
         dAllocAmount = dAllocPercent * dTotalAmount / 100.0;//alloc amount is calculated as a percentage of the total amount
      else
         dAllocAmount = dTotalAmount - dTotalAllocAmount;//because of the roundings

      dstrAllocAmount = DSTCommonFunctions::doubleToDString (ifds::RESPAllocAmt, dAllocAmount);
      getFormattedAmount (idDataGroup, dstrAllocAmount);
      //don't want to touch the percentage field here
      pRESPBeneficiaryAllocation->m_bSettingAmountField = true;
      pRESPBeneficiaryAllocation->setField(ifds::RESPAllocAmt, dstrAllocAmount, idDataGroup, true, true);
      pRESPBeneficiaryAllocation->m_bSettingAmountField = false;
      dAllocAmount = DSTCommonFunctions::convertToDouble (dstrAllocAmount);
      dTotalAllocAmount += dAllocAmount;

      ++iter; 
   }
   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
SEVERITY RESPBeneficiaryAllocationList::validateBeneficiaryEffectiveDate (const DString &dstrTradeDate, const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateBeneficiaryEffectiveDate" ) );   	
	
	BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
	iter.begin();

	while (!iter.end())
	{
		RESPBeneficiaryAllocation *pRESPBeneficiaryAllocation = dynamic_cast<RESPBeneficiaryAllocation*>(iter.getObject());
		
		DString dstrEffectiveDate;

		pRESPBeneficiaryAllocation->getField( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup );
		
		if (DSTCommonFunctions::CompareDates (dstrTradeDate, dstrEffectiveDate) == DSTCommonFunctions::FIRST_EARLIER)
		{
			DString idiStr = I_("");
			DString dstrBenName;

			pRESPBeneficiaryAllocation->getField( ifds::RESPBenefId, dstrBenName, idDataGroup, true );
			addIDITagValue (idiStr, BENEF_NAME, dstrBenName );

         ADDCONDITIONFROMFILEIDI (CND::ERR_BENEFICIARY_NOT_EFFECTIVE, idiStr);
			break;
		}
		++iter;
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RESPBeneficiaryAllocationList::validateTotalAmount (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateTotalAmount" ) );   	
	
   double dTotalPercent = 0, 
      dTotalAmt = 0, 
      cnt = 0;
   DString strTotAmount, 
      strTotPercent, 
      strParentAmount;
		
   getTotalPercentage (strTotPercent, idDataGroup, false);

	dTotalPercent = DSTCommonFunctions::convertToDouble(strTotPercent);
	if (fabs (dTotalPercent - 100) > dSmallValue)
   {
		ADDCONDITIONFROMFILE (CND::ERR_SUM_OF_PERCENTAGES_NOT_100);
   }

   if (GETCURRENTHIGHESTSEVERITY () <= WARNING)
   {
      getTotalAmount (strTotAmount, idDataGroup, false);
      dTotalAmt = DSTCommonFunctions::convertToDouble (strTotAmount);
      getField (ifds::Amount, strParentAmount, idDataGroup, false);
      
      if (!strParentAmount.strip().empty())
      {
         double dParentAmount = DSTCommonFunctions::convertToDouble (strParentAmount);
         if( dTotalAmt - dParentAmount > dSmallValue )
            ADDCONDITIONFROMFILE (CND::ERR_ALLOCAMOUNT_GREATER_THAN_TOTAL);
      }
   }

	return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY RESPBeneficiaryAllocationList::getBeneficiaryMasterList (DString &beneficiaryList, const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMasterList" ) );   	
	   
	if (!m_MasterBeneficiaryList.empty ())
	{
		beneficiaryList = m_MasterBeneficiaryList;
		return GETCURRENTHIGHESTSEVERITY();
	}

   AccountEntityXref *pAccountEntityXref = NULL;
	if (getWorkSession().getAccountEntityXref (idDataGroup, pAccountEntityXref) <= WARNING && pAccountEntityXref)
   {

      ENTITIES_VECTOR respBeneficiaryEntities;
      DString accountNum;

      getField (ifds::AccountNum, accountNum, idDataGroup, false);
      pAccountEntityXref->getRESPBeneficiaryEntities (respBeneficiaryEntities, accountNum, idDataGroup);

      for (ENTITIES_VECTOR::size_type i = 0; i < respBeneficiaryEntities.size(); ++i)
      {
         DString dstrEntityId, 
            dstrFirstName, 
            dstrLastName, 
            dstrActive;

         dstrEntityId = respBeneficiaryEntities [i];
         Entity *pEntity = NULL;

         if  (getWorkSession().getEntity (idDataGroup, dstrEntityId, pEntity) <= WARNING && pEntity)
         {
	         pEntity->getField( ifds::LastName, dstrLastName, idDataGroup, false );
	         pEntity->getField( ifds::FirstName, dstrFirstName, idDataGroup, false );

	         dstrEntityId.stripLeading().stripTrailing();
	         dstrLastName.stripLeading().stripTrailing();
	         dstrFirstName.stripLeading().stripTrailing();
	         dstrActive.stripAll().upperCase();

            m_MasterBeneficiaryList += dstrEntityId + I_("=") + dstrFirstName + I_(" ") + dstrLastName + I_(";");
         }
      }
   }
   beneficiaryList = m_MasterBeneficiaryList;
	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RESPBeneficiaryAllocationList::getRESPEntityInfo ( const DString dstrEntityId, 
													                     const BFDataGroupId &idDataGroup, 
							                                       DString& dstrRESPAllocPrcnt,
							                                       DString& dstrBenefDofBirth,
							                                       DString& dstrHRDCRelateCode,
							                                       DString& dstrTaxJuris,
							                                       DString& dstrEffectiveDate)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getRESPEntityInfo" ) );   	
	   
	AccountEntityXref *pAccountEntityXref = NULL;
	
	if (getWorkSession().getAccountEntityXref (idDataGroup, pAccountEntityXref) <= WARNING && pAccountEntityXref)
    {
      DString accountNum;

      getField (ifds::AccountNum, accountNum, idDataGroup, false);
      pAccountEntityXref->GetRESPEntityInfo (accountNum, idDataGroup, dstrEntityId,
										               dstrRESPAllocPrcnt, dstrBenefDofBirth, dstrHRDCRelateCode,
											            dstrTaxJuris, dstrEffectiveDate);	
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RESPBeneficiaryAllocationList::getEntitySeqNumber (const DString dstrEntityId, 
													                     const BFDataGroupId &idDataGroup, 
							                                       DString& dstrSeqNumber)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getEntitySeqNumber" ) );   	
	   
	AccountEntityXref *pAccountEntityXref = NULL;
	
	if (getWorkSession().getAccountEntityXref (idDataGroup, pAccountEntityXref) <= WARNING && pAccountEntityXref)
   {
      DString accountNum;

      getField (ifds::AccountNum, accountNum, idDataGroup, false);
      pAccountEntityXref->GetEntitySeqNumber (idDataGroup, accountNum, dstrEntityId, dstrSeqNumber);	
	}

	return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY RESPBeneficiaryAllocationList::validateNumberOfRESPAllocations (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getRESPEntity" ) );   	
	   
	BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );

	if (iter.getNumberOfItemsInList() == 0)
	{
		ADDCONDITIONFROMFILE (CND::ERR_RESP_BENEF_ALLOCATIONS_MISSING);
	}
	
	return GETCURRENTHIGHESTSEVERITY();
}
//*********************************************************************************
SEVERITY RESPBeneficiaryAllocationList::doValidateAll (const BFDataGroupId &idDataGroup, 
                                                      long lValidateGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll"));
	  
	validateNumberOfRESPAllocations (idDataGroup);

	validateTotalAmount (idDataGroup);
	
	validateRESPInfoUpdate (idDataGroup);

	validateHRDCPending (idDataGroup);
	
	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void RESPBeneficiaryAllocationList::getFormattedAmount (const BFDataGroupId &idDataGroup, 
                                                        DString &dstrValue)
{
   DString strCurrency, 
      strAmountType;

   getField (ifds::AmtType, strAmountType, idDataGroup, false);

   if( strAmountType.strip() != UNITS )
      formatAmtUsingCurrency( idDataGroup, dstrValue );
}

//******************************************************************************
void RESPBeneficiaryAllocationList::formatAmtUsingCurrency (const BFDataGroupId& idDataGroup, 
                                                            DString &dstrValue)
{
   DString strCurrency, strAmountType;

   getField (ifds::Currency, strCurrency, idDataGroup, false); 
   getField (ifds::AmtType, strAmountType, idDataGroup, false);

   CurrencyClass::getFormattedValue( getWorkSession(), dstrValue, strCurrency, strAmountType);
}

//******************************************************************************
void RESPBeneficiaryAllocationList::getTotalAmount (DString &strTotalAmount, 
                                                    const BFDataGroupId& idDataGroup, 
                                                    bool bFormatted)
{
   getTotalValue (ifds::RESPAllocAmt, strTotalAmount, idDataGroup);
   if (bFormatted)
   {
      getFormattedAmount (idDataGroup, strTotalAmount);
   }
}

//******************************************************************************
void RESPBeneficiaryAllocationList::getTotalPercentage (DString &strTotalPercentage, 
                                                        const BFDataGroupId &idDataGroup, 
                                                        bool bFormatted)
{
   getTotalValue (ifds::RESPAllocPrcnt, strTotalPercentage, idDataGroup);
}

//******************************************************************************
void RESPBeneficiaryAllocationList::getOtherAllocTotalAmount(DString &strTotalAmount, 
                                                             const BFDataGroupId& idDataGroup, 
                                                             bool bFormatted, 
                                                             RESPBeneficiaryAllocation *pRESPBeneficiaryAllocation)
{
   getTotalValue (ifds::RESPAllocAmt, strTotalAmount, idDataGroup, pRESPBeneficiaryAllocation);
   if (bFormatted)
   {
      getFormattedAmount (idDataGroup, strTotalAmount);
   }
}

//******************************************************************************
void RESPBeneficiaryAllocationList::getOtherAllocTotalPercentage (DString &strTotalPercentage, 
                                                                  const BFDataGroupId& idDataGroup, 
                                                                  bool bFormatted , 
                                                                  RESPBeneficiaryAllocation *pRESPBeneficiaryAllocation )
{
   getTotalValue (ifds::RESPAllocPrcnt, strTotalPercentage, idDataGroup, pRESPBeneficiaryAllocation);
}

//******************************************************************************
void RESPBeneficiaryAllocationList::getTotalValue ( const BFFieldId& fieldId, 
                                                    DString &strTotalValue, 
                                                    const BFDataGroupId& idDataGroup,
                                                    RESPBeneficiaryAllocation *pRESPBeneficiaryAllocation /*=NULL*/)
{
   assert (fieldId == ifds::RESPAllocAmt || fieldId == ifds::RESPAllocPrcnt);
   
   double dTotalValue = 0;
   BFObjIter iter (*this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
   
   while (!iter.end())
   {
      DString strAllocValue;
      if (iter.getObject() != pRESPBeneficiaryAllocation)
      {
         iter.getObject()->getField (fieldId, strAllocValue, idDataGroup, false);
         double dAllocValue = DSTCommonFunctions::convertToDouble (strAllocValue.strip());

         dTotalValue += dAllocValue;
      }
      ++iter; 
   }
   strTotalValue = DSTCommonFunctions::doubleToDString (fieldId, dTotalValue);   
}
//**********************************************************************************************
SEVERITY RESPBeneficiaryAllocationList::validateRESPInfoUpdate ( const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateRESPInfoUpdate"));
   
   // check for the updated datagroup
   RESPBeneficiaryAllocation *pRESPBeneficiaryAllocation = NULL;
   bool bViewCall = false;
   BFObjIter iter( *this, 
                   idDataGroup, 
                   true, 
                   BFObjIter::ITERTYPE::NON_DELETED );  
                   
   iter.begin();
   while(!iter.end())
   {
      pRESPBeneficiaryAllocation = dynamic_cast <RESPBeneficiaryAllocation*> (iter.getObject());
      
      if(pRESPBeneficiaryAllocation->isUpdatedForDataGroup (idDataGroup, false))
      {
         bViewCall = true;
         break;
      }
      ++iter;
   }                        
   
   DString dstrTradeType, dstrAccountNum, dstrTransId;
   getField(ifds::TradeType, dstrTradeType, idDataGroup, false);
   getField(ifds::AccountNum, dstrAccountNum, idDataGroup, false);
   getField(ifds::TransId, dstrTransId, idDataGroup, false);
   dstrTradeType.strip();
   dstrAccountNum.stripLeading('0');
   dstrTransId.strip();
         
   if(dstrTradeType == PROCESSED && bViewCall)
   {
      RESPInfoUpdateValidationList *pRESPInfoUpdateValidationList = NULL;     

      pRESPInfoUpdateValidationList = new RESPInfoUpdateValidationList (*this);
      
      if ( pRESPInfoUpdateValidationList->init ( dstrAccountNum,
                                                 dstrTransId,
                                                 NULL_STRING,
                                                 NO,
                                                 I_("BENEALLOC"),
                                                 I_("0"),
                                                 idDataGroup ) <= WARNING)
      {

         // do iterate through list of result...
         BFObjIter iter( *pRESPInfoUpdateValidationList, 
                         idDataGroup, 
                         true, 
                         BFObjIter::ITERTYPE::NON_DELETED );

         iter.begin();  

         while (!iter.end())
         {
            DString  dstrWarnCode;

            iter.getObject()->getField( ifds::WarnCode, 
                                        dstrWarnCode, 
                                        idDataGroup);

            dstrWarnCode.strip();           

            if ( dstrWarnCode == IFASTERR::ADJUSTMENT_MAY_BE_REQUIRED )
            {
               getErrMsg ( dstrWarnCode,
                           CND::ERR_ADJUSTMENT_REQUIRED, 
                           CND::WARN_ADJUSTMENT_MAY_BE_REQUIRED, 
                           idDataGroup );
            }
            else if( dstrWarnCode == IFASTERR::SYS_TRIG_AMEND_AND_RECAL_QESI_NOTIONAL_BALANCE )
            {
               getErrMsg (dstrWarnCode,
                          CND::ERR_SYS_TRIG_AMEND_AND_RECAL_QESI_NOTIONAL_BALANCE, 
                          CND::WARN_SYS_TRIG_AMEND_AND_RECAL_QESI_NOTIONAL_BALANCE, 
                          idDataGroup);
            }
            ++iter;
         }

      }

      delete pRESPInfoUpdateValidationList;
      pRESPInfoUpdateValidationList = NULL;
   }


   return GETCURRENTHIGHESTSEVERITY (); 
}
//******************************************************************************
//P0185010.FN03.R03.00 - RESP Beneficiary Re-Allocations
void RESPBeneficiaryAllocationList::getOtherBenefsField(const BFFieldId& fieldId,
																 DString &dstrValueOut, 
																 const BFDataGroupId &idDataGroup,
																 const RESPBeneficiaryAllocation *pRESPBeneficiaryAllocation /*NULL*/) 
{			
	BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );

	while (!iter.end())
	{
		if ( iter.getObject() != pRESPBeneficiaryAllocation) 		
		{
			iter.getObject()->getField (fieldId, dstrValueOut, idDataGroup, false);
			
			break;
		}
		
		++iter;
	}

}

//******************************************************************************
SEVERITY RESPBeneficiaryAllocationList::validateHRDCPending ( const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
							CLASSNAME, 
							I_("validateHRDCPending"));
	
	MFAccount *pMFAccount = NULL;
	DString dstrAccountNum, dstrTaxType, transId;

	getField (ifds::AccountNum, dstrAccountNum, idDataGroup, false);
	dstrAccountNum.strip ().stripLeading ('0');
	if (getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING && pMFAccount)
	{	 
		pMFAccount->getField (ifds::TaxType, dstrTaxType, idDataGroup);
		dstrTaxType.strip ().upperCase ();

		if ( dstrTaxType == I_("M")) // Family RESP
		{
			RESPTransactionsList *pRESPTransactionsList (NULL);
			if (pMFAccount->getRESPTransactionsList (pRESPTransactionsList, HISTORY, idDataGroup) <= WARNING && pRESPTransactionsList)
			{
				getField (ifds::TransId, transId, idDataGroup, false);

				bool bIsHRDCRespPending = false;
				DString dstrHRDCRespPending;

				BFObjIter iter( *pRESPTransactionsList, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
				iter.begin();

				while (!iter.end())
				{
					RESPTransactionsDetails *pRESPTransactionsDetails = dynamic_cast<RESPTransactionsDetails*>(iter.getObject());

					DString dstrReqTransid;
					pRESPTransactionsDetails->getField (ifds::TransId, dstrReqTransid, idDataGroup, false);

					if (dstrReqTransid == transId)
					{
						TransactionDetails *pTransactionDetails (NULL);

						if (pRESPTransactionsDetails->getTransactionDetails  (pTransactionDetails, idDataGroup) <= WARNING && pTransactionDetails)
						{
							pTransactionDetails->getField( ifds::HRDCRespPending, dstrHRDCRespPending, idDataGroup );
							dstrHRDCRespPending.strip().upperCase();
							if (dstrHRDCRespPending == I_("Y"))
							{
								bIsHRDCRespPending = true;
							}							
						}

						break;
					}

					++iter;
				}

				if (bIsHRDCRespPending)
				{
					BFObjIter iterAlloc( *this, idDataGroup, 0, BFObjIter::ITERTYPE::ALL );
					iterAlloc.begin();

					while (!iterAlloc.end())
					{
						RESPBeneficiaryAllocation *pRESPBeneficiaryAllocation = dynamic_cast<RESPBeneficiaryAllocation*>(iterAlloc.getObject());

						DString dstrHRDCReported;
						pRESPBeneficiaryAllocation->getField( ifds::HRDCReported, dstrHRDCReported, idDataGroup );
						dstrHRDCReported.strip().upperCase();

						if (dstrHRDCReported == I_("Y"))
						{
							getErrMsg (IFASTERR::TRANSACTION_AWAITING_HRSDC_RESPONSE_CANNOT_CHANGE_ALLOCATIONS, 
									   CND::ERR_TRANSACTION_AWAITING_HRSDC_RESPONSE_CANNOT_CHANGE_ALLOCATIONS, 
									   CND::WARN_TRANSACTION_AWAITING_HRSDC_RESPONSE_CANNOT_CHANGE_ALLOCATIONS, 
									   idDataGroup);
							break;
						}

						++iterAlloc;
					}
				}
			}
		}
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log::   Y:/VCS/BF iFAST/ifastcbo/RESPBeneficiaryAllocationList.cpp-arc  $
// 
//    Rev 1.13   Oct 13 2011 04:14:52   panatcha
// P0185010.FN03.R03.00 - RESP Beneficiary Re-Allocations
// 
//    Rev 1.12   Dec 10 2010 14:41:10   popescu
// Synch-up
// 
//    Rev 1.11   Nov 05 2010 16:11:08   popescu
// Incident 2202486 - RESP bene allocation screen defaults
// 
// 
//    Rev 1.10   Oct 29 2010 05:28:48   kitticha
// PET0165541 FN03 - QESI Phase3.
// 

