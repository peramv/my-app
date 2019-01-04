//********************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2010 By International Financial Data Services.
//
//
//********************************************************************************
//
// ^FILE   : EstateAllocation.cpp
// ^AUTHOR : 
// ^DATE   : 
//
//********************************************************************************
#include "stdafx.h"
#include "estateallocation.hpp"
#include "estateallocationlist.hpp"
#include "mfaccount.hpp"
#include "addresslist.hpp"
#include "address.hpp"
#include "shareholder.hpp"
#include "entity.hpp"
#include "addressentitylist.hpp"
#include "entityaddress.hpp"
#include "trade.hpp"

#include <ifastdataimpl\dse_dstc0441_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME				= I_( "EstateAllocation" );

   const I_CHAR * const SEARCHALL				= I_( "ALL" );	   //I_( "AL" ); //All
   const I_CHAR * const SEARCH_INV_NUM			= I_( "INVNUM" );  //I_( "IN" ); //Investment Number
   const I_CHAR * const SEARCH_INV_STATUS		= I_( "INVSTAT" ); //I_( "IS" ); //Investment Status

   const I_CHAR * const STATUS_ACTIVE			= I_( "ACTIVE" );
   const I_CHAR * const STATUS_MATURED			= I_( "MATURED" );
   const I_CHAR * const STATUS_CANCELLED		= I_( "CANCELLED" );
   const I_CHAR * const ADDR_LEVEL_SHAREHOLDER	= I_( "S" );
   const I_CHAR * const ADDR_LEVEL_ENTITY	   = I_( "E" );
   
   const I_CHAR * const AMOUNT_TYPE_AMOUNT   = I_( "D" );
   const I_CHAR * const AMOUNT_TYPE_PERCENT  = I_( "P" );
   const I_CHAR * const AMOUNT_TYPE_UNITS    = I_( "U" );
}
  
namespace CND
{  
   extern const long ERR_AMOUNT_EXCEEDS_PRINCIPAL;
   extern const long ERR_VALUE_BETWEEN_0_AND_100;
   extern const long ERR_ADDRESS_CODE_INVALID;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId Selected;
   extern CLASS_IMPORT const BFDecimalFieldId Amount;
   extern CLASS_IMPORT const BFTextFieldId RecordType;
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFTextFieldId GrossOrNet;
   extern CLASS_IMPORT const BFTextFieldId RedemOrder;
   extern CLASS_IMPORT const BFTextFieldId SuppressMVA;
   extern CLASS_IMPORT const BFTextFieldId SuppressAdmin;
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFDecimalFieldId TradeAmount;
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
   extern CLASS_IMPORT const BFTextFieldId AddrCode;
   extern CLASS_IMPORT const BFTextFieldId Address;
   extern CLASS_IMPORT const BFTextFieldId AmountType;
}

namespace TRADETYPE
{
   extern CLASS_EXPORT I_CHAR * const EXCHANGE;
   extern CLASS_IMPORT I_CHAR * const REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const TRANSFER;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
	// Field DD Id,                          State Flags, Group Flags 
   { ifds::BenefEntityID,                   BFCBO::NONE,		0},
   { ifds::BenefAddrCode,                   BFCBO::NONE,		0},
   { ifds::BenefAddrLevel,                  BFCBO::NONE,		0},
   { ifds::BenefPrcnt,                      BFCBO::NONE,		0},
   { ifds::BenefAmount,                     BFCBO::NONE,		0},
   { ifds::BenefUnits,                      BFCBO::NONE,		0},
   { ifds::BenefName,                       BFCBO::NONE,		0},
   { ifds::Address,                         BFCBO::READ_ONLY,		0},
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
EstateAllocation::EstateAllocation( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//******************************************************************************
EstateAllocation::~EstateAllocation()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}  

//******************************************************************************
SEVERITY EstateAllocation::init (const BFData &data)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );	

   attachDataObject (const_cast<BFData&>(data), false); 
   
   updateAddress(BF::HOST);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY EstateAllocation::doApplyRelatedChanges ( const BFFieldId &idField, 
                                          const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));

   if(ifds::BenefPrcnt == idField)
   {
      recalculateForPercentChange(idDataGroup);
   } 
   else if(ifds::BenefAmount == idField)
   {
      recalculateForAmountChange(idDataGroup);
   }
   else if(ifds::BenefUnits == idField)
   {
      recalculateForUnitsChange(idDataGroup);
   }
   else if(ifds::BenefAddrCode == idField || 
           ifds::BenefAddrLevel == idField )
   {
      updateAddress(idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

SEVERITY EstateAllocation::updateAddress(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("updateAddress"));
   DString dstrBenefAddrLevel;
   getField(ifds::BenefAddrLevel, dstrBenefAddrLevel, idDataGroup, false);
   dstrBenefAddrLevel.stripAll();
   
   DString dstrBenefAddrCode;
   getField(ifds::BenefAddrCode, dstrBenefAddrCode, idDataGroup, false);
   dstrBenefAddrCode.stripAll();

   bool found = false;

   if(dstrBenefAddrLevel == ADDR_LEVEL_SHAREHOLDER)
   {
      DString dstrAccountNum;
      getParent()->getField(ifds::AccountNum, dstrAccountNum, idDataGroup, false);
      MFAccount *pMFAccount = NULL;
      getWorkSession().getMFAccount ( idDataGroup, dstrAccountNum, pMFAccount); 

      if(pMFAccount)
      {
         DString dstrShrNum;
         pMFAccount->getField( ifds::ShrNum, dstrShrNum, idDataGroup, false);
         Shareholder* pShareholder = NULL;
         getWorkSession().getShareholder(idDataGroup, dstrShrNum, pShareholder);
         AddressList* _pAddressList = NULL;
         if(pShareholder->getAddressList(_pAddressList, idDataGroup, true, true ) <= WARNING)
         {
            BFObjIter iterShrAddr(*_pAddressList, idDataGroup);

            while (!iterShrAddr.end())
            {
               Address *pAddress =  dynamic_cast <Address*> (iterShrAddr.getObject());

               if (pAddress)
               {
                  DString dstrAddrCode;
                  pAddress->getField(ifds::AddrCode, dstrAddrCode, idDataGroup, false);
                  if(dstrAddrCode.stripAll() == dstrBenefAddrCode)
                  {
                     DString dstrAddress;
                     pAddress->getFormattedAddress(dstrAddress, idDataGroup);
                     setField(ifds::Address, dstrAddress, idDataGroup, false, true, false);
                     break;
                  }
               }
               ++iterShrAddr;
            }
         }
      }
   }
   else if(dstrBenefAddrLevel == ADDR_LEVEL_ENTITY)
   {
      
      DString dstrEntityId;
      getField(ifds::BenefEntityID, dstrEntityId, idDataGroup, false);
      Entity* pEntity = NULL;
      getWorkSession().getEntity(idDataGroup, dstrEntityId, pEntity);
      AddressEntityList* pAddressEntityList = NULL;
      if(pEntity->getAddressEntityList(pAddressEntityList, idDataGroup, true) <= WARNING)
      {
         BFObjIter iterEntAddr(*pAddressEntityList, idDataGroup);
         while (!iterEntAddr.end())
         {
            EntityAddress *pEntityAddress =  dynamic_cast <EntityAddress*> (iterEntAddr.getObject());

            if (pEntityAddress)
            {
               DString dstrAddrCode;
               pEntityAddress->getField(ifds::AddrCode, dstrAddrCode, idDataGroup, false);
               if(dstrAddrCode.stripAll() == dstrBenefAddrCode)
               {
                  DString dstrAddress;
                  pEntityAddress->getFormattedAddress(dstrAddress, idDataGroup);
                  setField(ifds::Address, dstrAddress, idDataGroup, false, true, false);
                  break;
               }
            }
            ++iterEntAddr;
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
};

//******************************************************************************
SEVERITY EstateAllocation::setBenefAddrCodeSubst(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("setBenefAddrCodeSubst"));
   
   DString substSet;
   DString dstrBenefAddrLevel;
   DString dstrAccountNum;

   getField(ifds::BenefAddrLevel, dstrBenefAddrLevel, idDataGroup, false);
   getParent()->getField(ifds::AccountNum, dstrAccountNum, idDataGroup, false);
 
   MFAccount *pMFAccount = NULL;
   getWorkSession().getMFAccount ( idDataGroup, dstrAccountNum, pMFAccount); 
   
   if(dstrBenefAddrLevel == ADDR_LEVEL_SHAREHOLDER)
   {
      DString dstrShrNum;
      getField( ifds::ShrNum, dstrShrNum, idDataGroup, false);
      Shareholder* pShareholder = NULL;
      getWorkSession().getShareholder(idDataGroup, dstrShrNum, pShareholder);
      AddressList* _pAddressList = NULL;
      if(pShareholder->getAddressList(_pAddressList, idDataGroup, true, true ) <= WARNING)
      {
         BFObjIter iterShrAddr(*_pAddressList, idDataGroup);

         while (!iterShrAddr.end())
         {
            Address *pAddress =  dynamic_cast <Address*> (iterShrAddr.getObject());

            if (pAddress)
            {
               DString dstrAddrCode;
               pAddress->getField(ifds::AddrCode, dstrAddrCode, idDataGroup, false);
               DString dstrAddrCode1;
               pAddress->getField(ifds::AddrCode, dstrAddrCode1, idDataGroup, true);
               substSet+= dstrAddrCode;
               substSet+= I_("=");
               substSet+= dstrAddrCode1;
               substSet += I_(";");

            }
            ++iterShrAddr;
         }

      }
      setFieldAllSubstituteValues(ifds::BenefAddrCode, idDataGroup, substSet);
   }
   else
   {
      DString dstrEntityId;
      getField(ifds::BenefEntityID, dstrEntityId, idDataGroup, false);
      Entity* pEntity = NULL;
      getWorkSession().getEntity(idDataGroup, dstrEntityId, pEntity);
      AddressEntityList* pAddressEntityList = NULL;
      if(pEntity->getAddressEntityList(pAddressEntityList, idDataGroup, true) <= WARNING)
      {
         BFObjIter iterEntAddr(*pAddressEntityList, idDataGroup);
         while (!iterEntAddr.end())
         {
            EntityAddress *pEntityAddress =  dynamic_cast <EntityAddress*> (iterEntAddr.getObject());

            if (pEntityAddress)
            {
               DString dstrAddrCode;
               pEntityAddress->getField(ifds::AddrCode, dstrAddrCode, idDataGroup, false);
               DString dstrAddrCode1;
               pEntityAddress->getField(ifds::AddrCode, dstrAddrCode1, idDataGroup, true);
               substSet+= dstrAddrCode;
               substSet+= I_("=");
               substSet+= dstrAddrCode1;
               substSet += I_(";");

            }
            ++iterEntAddr;
         }
      }
      setFieldAllSubstituteValues(ifds::BenefAddrCode, idDataGroup, substSet);

   }

   AccountEntityXref* pAccountEntityXref = NULL;
   getWorkSession().getAccountEntityXref(idDataGroup, pAccountEntityXref) ;
   
   DString dstrEntityId;
   getField(ifds::BenefEntityID, dstrEntityId, idDataGroup, false);
      


   return GETCURRENTHIGHESTSEVERITY();
}


SEVERITY EstateAllocation::doValidateField( const BFFieldId &fieldId,
                                    const DString& strValue,
                                    const BFDataGroupId& idDataGroup )
{ 
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );
   if(fieldId  == ifds::BenefAddrCode)
   {
      validateAddressCode(strValue, idDataGroup);
   }
   else if(fieldId == ifds::BenefAddrLevel)
   {
      validateAddressLevel(strValue, idDataGroup);
      DString dstrBenefAddrCode;    
      getField(ifds::BenefAddrCode, dstrBenefAddrCode, idDataGroup, false);
      
      validateAddressCode(dstrBenefAddrCode, idDataGroup);
   }
   else if(fieldId == ifds::BenefPrcnt)
   {
      BigDecimal bdPrcnt (strValue);
      BigDecimal bd100Percent (I_("100"));
      if(bdPrcnt < BIGDEC_ZERO || bdPrcnt > bd100Percent)
      {
         ADDCONDITIONFROMFILE(CND::ERR_VALUE_BETWEEN_0_AND_100);
      }

   }
   return(GETCURRENTHIGHESTSEVERITY());
}

SEVERITY EstateAllocation::recalculateAmount(const DString& dstrAmount, const DString& dstrAmountType, 
                                             const DString& dstrFundNAV, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("recalculateAmount"));

   DString dstrBenefPrcnt;
   getField(ifds::BenefPrcnt, dstrBenefPrcnt, idDataGroup);
	BigDecimal bdBenefPrcnt = DSTCommonFunctions::convertToBigDecimal(dstrBenefPrcnt);
	BigDecimal bdAmount     = DSTCommonFunctions::convertToBigDecimal(dstrAmount);
   BigDecimal bdHundred    = DSTCommonFunctions::convertToBigDecimal(I_("100.0"));
   BigDecimal bdFundNAV    = DSTCommonFunctions::convertToBigDecimal(dstrFundNAV);

   BigDecimal bdBenefAmount;
   BigDecimal bdBenefUnits;
   if(AMOUNT_TYPE_AMOUNT == dstrAmountType)
   {
      bdBenefAmount = bdBenefPrcnt *  bdAmount / bdHundred;
      bdBenefUnits  = bdBenefAmount / bdFundNAV;
   }
   else if(AMOUNT_TYPE_UNITS == dstrAmountType)
   {
      bdBenefUnits  = bdBenefPrcnt * bdAmount / bdHundred;
      bdBenefAmount = bdBenefUnits * bdFundNAV;
   }
   else if(AMOUNT_TYPE_PERCENT == dstrAmountType)
   {
      DString dstrTotalAmount;
      EstateAllocationList * pEstateAllocationList = (EstateAllocationList*)getParent();
      pEstateAllocationList->getField(ifds::Amount, dstrTotalAmount, idDataGroup);
      BigDecimal bdTotalAmount(dstrTotalAmount);

      bdBenefAmount = bdBenefPrcnt *  bdTotalAmount / bdHundred;
      bdBenefUnits  = bdBenefAmount / bdFundNAV;
   }
   
   setFieldNoValidate(ifds::BenefAmount, bdBenefAmount.asDString(), idDataGroup, false, true, true, false);
   setFieldNoValidate(ifds::BenefUnits,  bdBenefUnits.asDString(),  idDataGroup, false, true, true, false);

   return GETCURRENTHIGHESTSEVERITY ();
};

SEVERITY EstateAllocation::recalculateForPercentChange(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("recalculateForPercentChange"));

   EstateAllocationList * pEstateAllocationList = (EstateAllocationList*)getParent();
   DString dstrFundNAV;
   pEstateAllocationList->getField(ifds::FundNAV, dstrFundNAV, idDataGroup, false);
   BigDecimal bdFundNAV(dstrFundNAV);

   Trade* pTrade = (Trade*)(pEstateAllocationList->getParent());

   DString dstrAmount;
   pEstateAllocationList->getField(ifds::Amount, dstrAmount, idDataGroup, false);

   DString dstrAmountType;
   pEstateAllocationList->getField(ifds::AmountType, dstrAmountType, idDataGroup);
   
   BigDecimal bdTotalAmount(dstrAmount);
   DString dstrBenefPrcnt;
   getField(ifds::BenefPrcnt, dstrBenefPrcnt, idDataGroup);
   BigDecimal bdBenefPrcnt(dstrBenefPrcnt);
   BigDecimal bd100(100);
   
   BigDecimal bdBenefAmount = bdTotalAmount * bdBenefPrcnt / bd100;
   setFieldNoValidate(ifds::BenefAmount, bdBenefAmount.asDString(), idDataGroup, false, true, true, false);

   BigDecimal bdUnits = bdBenefAmount / bdFundNAV;
   setFieldNoValidate(ifds::BenefUnits, bdUnits.asDString(), idDataGroup, false, true, true, false);

   return GETCURRENTHIGHESTSEVERITY ();
};

SEVERITY EstateAllocation::recalculateForAmountChange(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("recalculateForAmountChange"));

   EstateAllocationList * pEstateAllocationList = (EstateAllocationList*)getParent();

   DString dstrTotalBenefAmount;
   pEstateAllocationList->getField(ifds::Amount, dstrTotalBenefAmount, idDataGroup);
   BigDecimal bdTotalBenefAmount(dstrTotalBenefAmount);

   DString dstrAmountType;
   pEstateAllocationList->getField(ifds::AmountType, dstrAmountType, idDataGroup);
   DString dstrFundNAV;
   pEstateAllocationList->getField(ifds::FundNAV, dstrFundNAV, idDataGroup);
   BigDecimal bdFundNAV(dstrFundNAV);

   BigDecimal bdHundred(100);
   
   DString dstrBenefAmount;
   getField(ifds::BenefAmount, dstrBenefAmount, idDataGroup);
   BigDecimal bdBenefAmount(dstrBenefAmount);

   BigDecimal bdUnits = bdBenefAmount / bdFundNAV;
   setFieldNoValidate(ifds::BenefUnits, bdUnits.asDString(), idDataGroup, false, true, true, false);

   BigDecimal bdPercent = bdBenefAmount * bdHundred / bdTotalBenefAmount;
   setFieldNoValidate(ifds::BenefPrcnt, bdPercent.asDString(), idDataGroup, false, true, true, false);

   return GETCURRENTHIGHESTSEVERITY ();
};

SEVERITY EstateAllocation::recalculateForUnitsChange(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("recalculateForUnitsChange"));

   DString dstrBenefUnits;    
   getField(ifds::BenefUnits, dstrBenefUnits, idDataGroup, false);
   
   EstateAllocationList * pEstateAllocationList = (EstateAllocationList*)getParent();

   DString dstrFundNAV;
   pEstateAllocationList->getField(ifds::FundNAV, dstrFundNAV, idDataGroup);

   BigDecimal bdFundNAV(dstrFundNAV);
   BigDecimal bdUnits(dstrBenefUnits);
   BigDecimal bdAmount = bdUnits * bdFundNAV;
   BigDecimal bd100(100);

   DString dstrTotalBenefAmount;
   pEstateAllocationList->getField(ifds::Amount, dstrTotalBenefAmount, idDataGroup);
   BigDecimal bdTotalBenefAmount(dstrTotalBenefAmount);


   BigDecimal bdPrcnt =  bdAmount * bd100 / bdTotalBenefAmount;
   setFieldNoValidate(ifds::BenefAmount, bdAmount.asDString(), idDataGroup, false, true, true, false);
   setFieldNoValidate(ifds::BenefPrcnt, bdPrcnt.asDString(), idDataGroup, false, true, true, false);


   return GETCURRENTHIGHESTSEVERITY ();
};

SEVERITY EstateAllocation::validateAddressCode(const DString& strValue, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAddressCode" ) );

   DString dstrBenefAddrLevel;
   getField(ifds::BenefAddrLevel, dstrBenefAddrLevel, idDataGroup, false);
   dstrBenefAddrLevel.stripAll();
   DString dstrBenefAddrCode = strValue;
   dstrBenefAddrCode.stripAll();
   bool found = false;

   if(dstrBenefAddrLevel == ADDR_LEVEL_SHAREHOLDER)
   {
      DString dstrAccountNum;
      getParent()->getField(ifds::AccountNum, dstrAccountNum, idDataGroup, false);
      MFAccount *pMFAccount = NULL;
      getWorkSession().getMFAccount ( idDataGroup, dstrAccountNum, pMFAccount); 

      if(pMFAccount)
      {
         DString dstrShrNum;
         pMFAccount->getField( ifds::ShrNum, dstrShrNum, idDataGroup, false);
         Shareholder* pShareholder = NULL;
         getWorkSession().getShareholder(idDataGroup, dstrShrNum, pShareholder);
         AddressList* _pAddressList = NULL;
         if(pShareholder->getAddressList(_pAddressList, idDataGroup, true, true ) <= WARNING)
         {
            BFObjIter iterShrAddr(*_pAddressList, idDataGroup);

            while (!iterShrAddr.end())
            {
               Address *pAddress =  dynamic_cast <Address*> (iterShrAddr.getObject());

               if (pAddress)
               {
                  DString dstrAddrCode;
                  pAddress->getField(ifds::AddrCode, dstrAddrCode, idDataGroup, false);
                  if(dstrAddrCode.stripAll() == dstrBenefAddrCode)
                  {
                     found = true;
                     break;
                  }
               }
               ++iterShrAddr;
            }
         }
      }
   }
   else if(dstrBenefAddrLevel == ADDR_LEVEL_ENTITY)
   {
      
      DString dstrEntityId;
      getField(ifds::BenefEntityID, dstrEntityId, idDataGroup, false);
      Entity* pEntity = NULL;
      getWorkSession().getEntity(idDataGroup, dstrEntityId, pEntity);
      AddressEntityList* pAddressEntityList = NULL;
      if(pEntity->getAddressEntityList(pAddressEntityList, idDataGroup, true) <= WARNING)
      {
         BFObjIter iterEntAddr(*pAddressEntityList, idDataGroup);
         while (!iterEntAddr.end())
         {
            EntityAddress *pEntityAddress =  dynamic_cast <EntityAddress*> (iterEntAddr.getObject());

            if (pEntityAddress)
            {
               DString dstrAddrCode;
               pEntityAddress->getField(ifds::AddrCode, dstrAddrCode, idDataGroup, false);
               if(dstrAddrCode.stripAll() == dstrBenefAddrCode)
               {
                  found = true;
                  break;
               }
            }
            ++iterEntAddr;
         }
      }

   }
   if(!found)
   {
      ADDCONDITIONFROMFILE( CND::ERR_ADDRESS_CODE_INVALID);
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

SEVERITY EstateAllocation::validateAddressLevel(const DString& strValue, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAddressLevel" ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

   
   //******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/EstateAllocation.cpp-arc  $
// 
//    Rev 1.2   10 Aug 2012 13:05:38   if991250
// Estate Allocation
// 
//    Rev 1.1   29 Jul 2012 23:18:42   if991250
// Estate Allocation Address controls
// 
//    Rev 1.0   25 Jul 2012 15:25:58   if991250
// Initial revision.
// 
// 
*/
