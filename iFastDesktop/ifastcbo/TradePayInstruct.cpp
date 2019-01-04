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
//    Copyright 2004 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : TradePayInstruct.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : August, 2006
//
// ^CLASS    : TradePayInstruct
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "tradepayinstruct.hpp"

#include "agent.hpp"
#include "branch.hpp"
#include "broker.hpp"
#include "dynamicsublistholder.hpp"
#include "mgmtco.hpp"
#include "trade.hpp"
#include "tradebankinstructions.hpp"
#include "tradebankinstructionslist.hpp"

namespace
{
   const I_CHAR * const CLASSNAME = I_("TradePayInstruct");
}

namespace ifds
{   
   extern CLASS_IMPORT const BFTextFieldId RecordType;
   extern CLASS_IMPORT const BFTextFieldId UseEntityAddress;
   extern CLASS_IMPORT const BFTextFieldId TradePayInstructPayType;
   extern CLASS_IMPORT const BFTextFieldId PayInstructConsolType;
   extern CLASS_IMPORT const BFDecimalFieldId AllocPercent;
   extern CLASS_IMPORT const BFTextFieldId ACHRedemption;
   extern CLASS_IMPORT const BFTextFieldId ACHDividend;
   extern CLASS_IMPORT const BFTextFieldId MultiCurrency;
	extern CLASS_IMPORT const BFTextFieldId Address1;
	extern CLASS_IMPORT const BFTextFieldId Address2;
	extern CLASS_IMPORT const BFTextFieldId Address3;
	extern CLASS_IMPORT const BFTextFieldId Address4;
	extern CLASS_IMPORT const BFTextFieldId Address5;
	extern CLASS_IMPORT const BFTextFieldId AddrLine1;
	extern CLASS_IMPORT const BFTextFieldId AddrLine2;
	extern CLASS_IMPORT const BFTextFieldId AddrLine3;
	extern CLASS_IMPORT const BFTextFieldId AddrLine4;
	extern CLASS_IMPORT const BFTextFieldId AddrLine5;
   extern CLASS_IMPORT const BFTextFieldId CountryCode;
   extern CLASS_IMPORT const BFTextFieldId AddrCntryCode;
   extern CLASS_IMPORT const BFTextFieldId PostalCode;
   extern CLASS_IMPORT const BFTextFieldId PayInstructConsolType;
   extern CLASS_IMPORT const BFTextFieldId PayToEntity;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
}

namespace CND
{  // Conditions used
   extern const long ERR_VALUE_BETWEEN_0_AND_100;
}

namespace CURRENCY_OPTION
{
	extern const I_CHAR * PAY_SETTLEMENT_CURRENCY;
}

namespace CONSOL_TYPE
{
   extern const I_CHAR * INDIVIDUAL_PAYMENT;
}

namespace PAY_TO
{
   extern I_CHAR * const BROKER;
   extern I_CHAR * const BRANCH;
   extern I_CHAR * const SALESREP;	
   extern I_CHAR * const CLIENT;
}

namespace PAYMENT_FOR
{
   extern const I_CHAR * TRAILER_FEE;
   extern const I_CHAR * COMMISSION;
	extern const I_CHAR * REDEMPTION;
	extern const I_CHAR * DISTRIBUTION;
}

namespace TransType
{
	extern const I_CHAR * const REDEMPTION;
	extern const I_CHAR * const EFT_DIVIDEND;
}
namespace PAYTYPE
{
   extern CLASS_IMPORT I_CHAR * const EFT;
   extern CLASS_IMPORT I_CHAR * const SUPPRESS;
   extern CLASS_IMPORT I_CHAR * const SYSTEM_CHEQUE;
} 

//-------------------------------------------------------------------
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags    
   { ifds::PayToEntity,	      BFCBO::NONE,	    0 },
   { ifds::AllocPercent,	   BFCBO::NONE,	    0 },
   { ifds::RecordType,		   BFCBO::NONE,	    0 },
   { ifds::PaymentFor,	      BFCBO::NONE,	    0 },
   { ifds::PayType,	         BFCBO::REQUIRED,   0 },
   { ifds::PayMethod,	      BFCBO::REQUIRED,	 0 },
   { ifds::ACHProcessor,	   BFCBO::REQUIRED,	 0 },
   { ifds::ConsolType,	      BFCBO::NONE,	    0 },
   { ifds::DirectTo,	         BFCBO::NONE,	    0 },
   { ifds::AccountNum,	      BFCBO::NONE,	    0 },
   { ifds::BankCharge,	      BFCBO::NONE,	    0 },
   { ifds::CurrencyOption,	   BFCBO::REQUIRED,	 0 },
   { ifds::Currency,	         BFCBO::NONE,	    0 },
   { ifds::EffectiveDate,	   BFCBO::REQUIRED,	 0 },
   { ifds::StopDate,	         BFCBO::NONE,	    0 },
   { ifds::UseEntityAddress,	BFCBO::REQUIRED,	 0 },
   { ifds::AddrLine1,         BFCBO::NONE,       0}, 
   { ifds::AddrLine2,         BFCBO::NONE,       0}, 
   { ifds::AddrLine3,         BFCBO::NONE,       0}, 
   { ifds::AddrLine4,         BFCBO::NONE,       0}, 
   { ifds::AddrLine5,         BFCBO::NONE,       0}, 
   { ifds::PostalCode,        BFCBO::NONE,       0}, 
   { ifds::CountryCode,       BFCBO::NONE,       0}, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************************
TradePayInstruct::TradePayInstruct( BFAbstractCBO &parent )
: MFCanBFCbo (parent),
_hostCurrenciesSet (NULL_STRING)

{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL );

   //save the currencies set....
   BFProperties *pProperties = getFieldProperties (ifds::Currency, BF::HOST);
   
   pProperties->getAllSubstituteValues (_hostCurrenciesSet);
}
//******************************************************************************************
TradePayInstruct::~TradePayInstruct()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}     

//************************************************************************************
SEVERITY TradePayInstruct::initNew ( const DString &payToEntity, 
                                     const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("initNew"));  	

   setFieldNoValidate (ifds::RecordType, I_("TradePayInstr"), idDataGroup, false);
   commonInit (payToEntity, idDataGroup);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************************
SEVERITY TradePayInstruct::init ( const DString &payToEntity,
                                  const BFData& data,
                                  const BFDataGroupId& idDataGroup /*= BF::HOST*/,
                                  bool bSetFieldsReadOnly /*=false*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   attachDataObject (const_cast<BFData&>(data), false);
   setFieldNoValidate (ifds::RecordType, I_("TradePayInstr"), idDataGroup, false);
   commonInit (payToEntity, idDataGroup);
   if (bSetFieldsReadOnly)
   {
      for (int i = 0; i < NUM_FIELDS; i++)
      {
         BFCBO::CLASS_FIELD_INFO fieldInfo = classFieldInfo [i];     
         const BFFieldId &fieldId = fieldInfo.getFieldId();

         setFieldReadOnly (fieldId, idDataGroup, true);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void TradePayInstruct::doInitWithDefaultValues (const BFDataGroupId& idDataGroup)
{
//for the trade's transaction builder
   setFieldNoValidate (ifds::RecordType, I_("TradePayInstr"), idDataGroup, false);
   setFieldNoValidate ( ifds::ConsolType, CONSOL_TYPE::INDIVIDUAL_PAYMENT, idDataGroup, 
                        false, true, true, true);
   setFieldNoValidate ( ifds::DirectTo, I_("PE"), idDataGroup,  //pay entity
                        false, true, true, false);
   setFieldNoValidate ( ifds::AccountNum, NULL_STRING, idDataGroup,
                        false, true, true, false);
   DString bankChrgs;

   getWorkSession().getOption (ifds::BankChrgs, bankChrgs, BF::HOST, false);
   setFieldNoValidate (ifds::BankCharge, bankChrgs, idDataGroup, false, true, true, false);
   setFieldNoValidate ( ifds::CurrencyOption, CURRENCY_OPTION::PAY_SETTLEMENT_CURRENCY, idDataGroup, 
                        false, true, true, true);

   DString date,
      stopDate;

   getWorkSession().getOption (ifds::CurrBusDate, date, idDataGroup, false);
   setFieldNoValidate (ifds::EffectiveDate, date, idDataGroup, false, true, true);
   getWorkSession().getDateInHostFormat (stopDate, DSTCWorkSession::DATE_TYPE::DAY12319999, idDataGroup);
   setFieldNoValidate (ifds::StopDate, stopDate, idDataGroup, false, true, true );
   setFieldNoValidate ( ifds::UseEntityAddress, Y, idDataGroup, 
                        false, true, true, false);

}

//***********************************************************************************
SEVERITY TradePayInstruct::commonInit ( const DString &payToEntity, 
                                        const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("commonInit"));

   bool bDataNotFound = false;

   setFieldNoValidate (ifds::PayToEntity, payToEntity, idDataGroup, false);
   setFieldAllSubstituteValues (ifds::ConsolType, idDataGroup, ifds::PayInstructConsolType);
   setFieldAllSubstituteValues (ifds::PayType, idDataGroup, ifds::TradePayInstructPayType);
   setFieldReadOnly (ifds::PaymentFor, idDataGroup, true);
   setFieldReadOnly (ifds::ConsolType, idDataGroup, true);
   setFieldReadOnly (ifds::Currency, idDataGroup, true);
   setFieldReadOnly (ifds::DirectTo, idDataGroup, true);
	fillAddressInfo (idDataGroup, bDataNotFound);
	loadCurrencySet (idDataGroup);
	loadFileProcessorSet (idDataGroup);
// for now since only one record is available - set this to 100%
	setFieldNoValidate (ifds::AllocPercent, I_("100"), idDataGroup, false);
   return GETCURRENTHIGHESTSEVERITY();
}

//***********************************************************************************
SEVERITY TradePayInstruct::doValidateField( const BFFieldId &idField,
                                            const DString &strValue,
                                            const BFDataGroupId &idDataGroup)

{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField"));
	
   if (idField == ifds::AllocPercent)
   {
		validatePercent( idDataGroup );
   }
	return GETCURRENTHIGHESTSEVERITY();
}


//*****************************************************************************************
SEVERITY TradePayInstruct::doApplyRelatedChanges ( const BFFieldId &idField, 
                                                   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_( "doApplyRelatedChanges"));

   if (idField == ifds::PayMethod)
   {
//reset the file processor field
      setFieldNoValidate (ifds::ACHProcessor, NULL_STRING, idDataGroup, true, true, true);
//fillAdressInfo method will figure out whether
//it should go ahead and fill the info, or not
      fillAddressInfo (idDataGroup);
      loadFileProcessorSet (idDataGroup);
  }
   else if (idField == ifds::UseEntityAddress)
   {
      //set the address info if UseEntityAddress in Yes
      DString useEntityAddress;

      getField (ifds::UseEntityAddress, useEntityAddress, idDataGroup, false);
      fillAddressInfo (idDataGroup);
   }
   else if (idField == ifds::ACHProcessor)
   {
      loadCurrencySet (idDataGroup);
   }
   else if (idField == ifds::Currency)
   {
      loadFileProcessorSet (idDataGroup);
   }
   else if (idField == ifds::PayType)
   {
      DString payType;

      getField (ifds::PayType, payType, idDataGroup, false);
      if (payType == PAYTYPE::SUPPRESS  || payType == PAYTYPE::SYSTEM_CHEQUE)
      {
//clear the pay method field
         setFieldNoValidate ( ifds::PayMethod, payType == PAYTYPE::SYSTEM_CHEQUE ? I_("CHQ") : NULL_STRING, idDataGroup, 
                              false, true, true, false);
         setFieldNoValidate ( ifds::ACHProcessor, NULL_STRING, idDataGroup, 
                              false, true, true, false);
      }
//load the currency sub-set, if necessary
      loadCurrencySet (idDataGroup);
      loadFileProcessorSet (idDataGroup);
//payTypeRelatedChanges method will figure out whether
//it should go ahead and clear out all fields
      payTypeRelatedChanges (idDataGroup);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************
SEVERITY TradePayInstruct::validatePercent (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validatePercent"));

   DString dstrPercentage;
   
   getField (ifds::AllocPercent, dstrPercentage, idDataGroup, false);
   dstrPercentage.strip().stripAll(I_CHAR(','));

   I_CHAR *stopstring;
   double dPercent = wcstod (dstrPercentage.c_str(), &stopstring);

   if (dPercent > 100)
   {
      ADDCONDITIONFROMFILE (CND::ERR_VALUE_BETWEEN_0_AND_100);      
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool TradePayInstruct::isBankingAllowed (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("isBankingAllowed"));
   DString payMethod, 
      payType;

   getField (ifds::PayType, payType, idDataGroup, false);
   getField (ifds::PayMethod, payMethod, idDataGroup, false);
   return payType == PAYTYPE::EFT && (payMethod == I_("WIRE") || payMethod == I_("EFT"));
}

//******************************************************************************
bool TradePayInstruct::isSuppressAllowed (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("isSuppressAllowed"));
   DString payMethod, 
      payType;

   getField (ifds::PayType, payType, idDataGroup, false);
   getField (ifds::PayMethod, payMethod, idDataGroup, false);
   return payType == PAYTYPE::SUPPRESS && payMethod == NULL_STRING;
}

//******************************************************************************
bool TradePayInstruct::isAddressInfoAllowed (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("isAddressInfoAllowed"));
   DString payMethod, 
      payType;

   getField (ifds::PayType, payType, idDataGroup, false);
   getField (ifds::PayMethod, payMethod, idDataGroup, false);
   return (payType == PAYTYPE::EFT ||
           payType == PAYTYPE::SYSTEM_CHEQUE) && payMethod == I_("CHQ");
}


//******************************************************************************
SEVERITY TradePayInstruct::fillAddressInfo ( const BFDataGroupId &idDataGroup,
                                             bool bDataNotFound /*= false*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("fillAddressInfo"));
   assert (getParent () && getParent ()->getParent ());

   if (getParent () && getParent ()->getParent ())
   {
      Trade *pTrade = dynamic_cast <Trade*> (getParent ()->getParent ());
//      assert (pTrade);

      if (pTrade)
      {
         //the address info should be set only if banking is not allowed,
         //meaning, pay method is CHQ and pay type is EFT
        if (isAddressInfoAllowed (idDataGroup) && !bDataNotFound)
      //do not want to get the address of the broker/branch/sales rep if records do not exist on the back-end
         {
      //set the address info if UseEntityAddress in Yes
            DString useEntityAddress;

            getField (ifds::UseEntityAddress, useEntityAddress, idDataGroup, false);
            if (useEntityAddress == Y)
            {
               DString payToEntity, 
                  address1, 
                  address2, 
                  address3, 
                  address4, 
                  address5, 
                  postalCode, 
                  countryCode;
               bool bFoundFiller = false;
            
      //copy broker address if Pay to Entity is BROKER
               getField (ifds::PayToEntity, payToEntity, idDataGroup, false);
               if (payToEntity == PAY_TO::BROKER)
               {
                  Broker *pBroker (NULL);

                  if ( pTrade->getBroker (pBroker, idDataGroup) <= WARNING &&
                       pBroker)
                  {
                     pBroker->getField (ifds::AddrLine1, address1, idDataGroup, false);
                     pBroker->getField (ifds::AddrLine2, address2, idDataGroup, false);
                     pBroker->getField (ifds::AddrLine3, address3, idDataGroup, false);
                     pBroker->getField (ifds::AddrLine4, address4, idDataGroup, false);
                     pBroker->getField (ifds::AddrLine5, address5, idDataGroup, false);
                     pBroker->getField (ifds::AddrCntryCode, countryCode, idDataGroup, false);
                     pBroker->getField (ifds::PostalCode, postalCode, idDataGroup, false);
                     bFoundFiller = true;
                  }
               }
               //copy branch address if Pay to Entity is BRANCH
               else if (payToEntity == PAY_TO::BRANCH)
               {
                  Branch *pBranch (NULL);

                  if ( pTrade->getBranch (pBranch, idDataGroup) <= WARNING &&
                       pBranch)
                  {                  
                     pBranch->getField (ifds::AddrLine1, address1, idDataGroup, false);
                     pBranch->getField (ifds::AddrLine2, address2, idDataGroup, false);
                     pBranch->getField (ifds::AddrLine3, address3, idDataGroup, false);
                     pBranch->getField (ifds::AddrLine4, address4, idDataGroup, false);
                     pBranch->getField (ifds::AddrLine5, address5, idDataGroup, false);
                     pBranch->getField (ifds::AddrCntryCode, countryCode, idDataGroup, false);
                     pBranch->getField (ifds::PostalCode, postalCode, idDataGroup, false);
                     bFoundFiller = true;
                  }
               }
      //copy branch address if Pay to Entity is REP
               else if (payToEntity == PAY_TO::SALESREP)
               {
                  Agent *pAgent = NULL;

                  if ( pTrade->getAgent (pAgent, idDataGroup) <= WARNING &&
                       pAgent)
                  {
                     pAgent->getField(ifds::AddrLine1, address1, idDataGroup, false);
                     pAgent->getField(ifds::AddrLine2, address2, idDataGroup, false);
                     pAgent->getField(ifds::AddrLine3, address3, idDataGroup, false);
                     pAgent->getField(ifds::AddrLine4, address4, idDataGroup, false);
                     pAgent->getField(ifds::AddrLine5, address5, idDataGroup, false);
                     pAgent->getField(ifds::AddrCntryCode, countryCode, idDataGroup, false);
                     pAgent->getField(ifds::PostalCode, postalCode, idDataGroup, false);
                     bFoundFiller = true;
                  }
               }
               if (bFoundFiller)
               {
                  setFieldNoValidate ( ifds::AddrLine1, address1, idDataGroup, 
                                       false, true, true);
                  setFieldUpdated (ifds::AddrLine1, idDataGroup, false);
                  setFieldNoValidate ( ifds::AddrLine2, address2, idDataGroup, 
                                       false, true, true);
                  setFieldUpdated (ifds::AddrLine2, idDataGroup, false);
                  setFieldNoValidate ( ifds::AddrLine3, address3, idDataGroup, 
                                       false, true, true);
                  setFieldUpdated (ifds::AddrLine3, idDataGroup, false);
                  setFieldNoValidate ( ifds::AddrLine4, address4, idDataGroup, 
                                       false, true, true);
                  setFieldUpdated (ifds::AddrLine4, idDataGroup, false);
                  setFieldNoValidate ( ifds::AddrLine5, address5, idDataGroup, 
                                       false, true, true);
                  setFieldUpdated (ifds::AddrLine5, idDataGroup, false);
                  setFieldNoValidate ( ifds::CountryCode, countryCode, idDataGroup, 
                                       false, true, true);
                  setFieldUpdated ( ifds::CountryCode, idDataGroup, false);
                  setFieldNoValidate ( ifds::PostalCode, postalCode, idDataGroup, 
                                       false, true, true);
                  setFieldUpdated (ifds::PostalCode, idDataGroup, false);
               }
            }
         }
         addressInfoRelatedChanges (idDataGroup);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradePayInstruct::addressInfoRelatedChanges (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("addressInfoRelatedChanges"));

   if (isAddressInfoAllowed (idDataGroup))
   {
      DString useEntityAddress;

      getField (ifds::UseEntityAddress, useEntityAddress, idDataGroup, false);

      bool bUseEntityAddress = useEntityAddress == Y;

      setFieldReadOnly (ifds::AddrLine1, idDataGroup, bUseEntityAddress);
      setFieldReadOnly (ifds::AddrLine2, idDataGroup, bUseEntityAddress);
      setFieldReadOnly (ifds::AddrLine3, idDataGroup, bUseEntityAddress);
      setFieldReadOnly (ifds::AddrLine4, idDataGroup, bUseEntityAddress);
      setFieldReadOnly (ifds::AddrLine5, idDataGroup, bUseEntityAddress);
      setFieldReadOnly (ifds::CountryCode, idDataGroup, bUseEntityAddress);
      setFieldReadOnly (ifds::PostalCode, idDataGroup, bUseEntityAddress);
      setValidFlag (ifds::AddrLine1, idDataGroup, false);
      setFieldRequired (ifds::AddrLine1, idDataGroup, true);
      setValidFlag (ifds::CountryCode, idDataGroup, false);
      setFieldRequired (ifds::CountryCode, idDataGroup, true);
   }
   else
   {
      setFieldRequired (ifds::AddrLine1, idDataGroup, false);
      setFieldRequired (ifds::CountryCode, idDataGroup, false);
      //clear the address related fields
      /*setFieldNoValidate(ifds::UseEntityAddress, I_("N"), idDataGroup, 
         false, true, true, false);*/
      setFieldNoValidate ( ifds::AddrLine1, NULL_STRING, idDataGroup, 
                           false, true, true, false);
      setFieldNoValidate ( ifds::AddrLine2, NULL_STRING, idDataGroup, 
                           false, true, true, false);
      setFieldNoValidate ( ifds::AddrLine3, NULL_STRING, idDataGroup, 
                           false, true, true, false);
      setFieldNoValidate ( ifds::AddrLine4, NULL_STRING, idDataGroup, 
                           false, true, true, false);
      setFieldNoValidate ( ifds::AddrLine5, NULL_STRING, idDataGroup, 
                           false, true, true, false);
      setFieldNoValidate ( ifds::CountryCode, NULL_STRING, idDataGroup, 
                           false, true, true, false);
      setFieldNoValidate ( ifds::PostalCode, NULL_STRING, idDataGroup, 
                           false, true, true, false);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradePayInstruct::loadCurrencySet (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("loadCurrencySet"));

   DString multiCurrency, 
      dstrACHRedemption,
      dstrACHDividend;
      //substList;

   getWorkSession().getOption ( ifds::ACHRedemption, dstrACHRedemption, 
                                BF::HOST, false);
   getWorkSession ().getOption ( ifds::ACHDividend, dstrACHDividend, 
                                 BF::HOST, false);   
   getWorkSession().getOption ( ifds::MultiCurrency, multiCurrency, 
                                BF::HOST, false);
   /*if (multiCurrency.strip() == Y)
   {*/
      DString paymentFor, 
         transType;

      getField(ifds::PaymentFor, paymentFor, idDataGroup, false);
      if ( paymentFor == PAYMENT_FOR::REDEMPTION && 
           dstrACHRedemption == Y)
      {
         transType = TransType::REDEMPTION;
      }
      else if ( paymentFor == PAYMENT_FOR::DISTRIBUTION && 
                dstrACHDividend == Y)
      {
         transType = TransType::EFT_DIVIDEND;
      }

      DynamicSubListHolder* pDynamicSubListHolder = getMgmtCo().getDynamicSubListHolder();
	   assert (pDynamicSubListHolder);

      DString payMethod, 
         fileProcessor,
         substList;

      getField (ifds::PayMethod, payMethod, idDataGroup, false);
      payMethod.strip();
      getField (ifds::ACHProcessor, fileProcessor, idDataGroup, false);
      fileProcessor.strip();
      if (!fileProcessor.empty())
      {
		   substList = pDynamicSubListHolder->getCurrencySubList (transType, payMethod, fileProcessor);
      }
      else
      {
		   substList = pDynamicSubListHolder->getCurrencySubList (transType, payMethod);
      }
      if (substList.empty())
      {
         setFieldAllSubstituteValues (ifds::Currency, idDataGroup, _hostCurrenciesSet);
      }
      else
      {
		   setFieldAllSubstituteValues (ifds::Currency, idDataGroup, substList);
      }
//have to force validation, because substitute values have changed
		setValidFlag (ifds::Currency, idDataGroup, false);
      setFieldReadOnly (ifds::Currency, idDataGroup, true);
   //}
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradePayInstruct::loadFileProcessorSet (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("loadCurrencySet"));

   DString multiCurrency, 
      dstrACHRedemption,
      dstrACHDividend,
      substList,
      payType;

   getWorkSession().getOption ( ifds::ACHRedemption, dstrACHRedemption, 
                                BF::HOST, false);
   getWorkSession ().getOption ( ifds::ACHDividend, dstrACHDividend, 
                                 BF::HOST, false);   
   getWorkSession().getOption ( ifds::MultiCurrency, multiCurrency, 
                                BF::HOST, false);
   getField (ifds::PayType, payType, idDataGroup);
   if (/*multiCurrency.strip() == Y &&*/ payType == PAYTYPE::EFT)
   {
      DString paymentFor, 
         transType;

      getField (ifds::PaymentFor, paymentFor, idDataGroup, false);
      if ( paymentFor == PAYMENT_FOR::REDEMPTION && 
           dstrACHRedemption == Y)
      {
         transType = TransType::REDEMPTION;
      }
      else if ( paymentFor == PAYMENT_FOR::DISTRIBUTION && 
                dstrACHDividend == Y)
      {
         transType = TransType::EFT_DIVIDEND;
      }

      DynamicSubListHolder *pDynamicSubListHolder = getMgmtCo().getDynamicSubListHolder();
	   assert(pDynamicSubListHolder);

      DString payMethod, 
         currency;

      getField (ifds::PayMethod, payMethod, idDataGroup, false);
      payMethod.strip();
      getField (ifds::Currency, currency, idDataGroup, false);
      currency.strip();
      if (!payMethod.empty())
      {
         if (currency.empty())
         {
	         substList = pDynamicSubListHolder->getFileProcSubList (transType, payMethod);
         }
         else 
         {
	         substList = pDynamicSubListHolder->getFileProcSubList (transType, payMethod, currency);
         }
      }
   }
   setFieldAllSubstituteValues (ifds::ACHProcessor, idDataGroup, substList);

   bool bRequired = !substList.empty();

   setFieldRequired (ifds::ACHProcessor, idDataGroup, bRequired);
   setValidFlag (ifds::ACHProcessor, idDataGroup, !bRequired);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradePayInstruct::payTypeRelatedChanges ( const BFDataGroupId &idDataGroup,
                                                   bool bDataNotFound /*= false*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("payTypeRelatedChanges"));

   if (isSuppressAllowed (idDataGroup))
   {
      //clear the address info fields
      addressInfoRelatedChanges (idDataGroup);
      //set the address fields to read only
      setFieldReadOnly (ifds::AddrLine1, idDataGroup, true);
      setFieldReadOnly (ifds::AddrLine2, idDataGroup, true);
      setFieldReadOnly (ifds::AddrLine3, idDataGroup, true);
      setFieldReadOnly (ifds::AddrLine4, idDataGroup, true);
      setFieldReadOnly (ifds::AddrLine5, idDataGroup, true);
      setFieldReadOnly (ifds::CountryCode, idDataGroup, true);
      setFieldReadOnly (ifds::PostalCode, idDataGroup, true);
//pay method should be read only
      setFieldReadOnly (ifds::PayMethod, idDataGroup, true);
      setFieldReadOnly (ifds::ACHProcessor, idDataGroup, true);
      setFieldRequired (ifds::PayMethod, idDataGroup, false);
      setFieldRequired (ifds::ACHProcessor, idDataGroup, false);
   }
   else 
   {
      if (isBankingAllowed (idDataGroup))
      {
         assert (getParent () && getParent ()->getParent ());

         if (getParent () && getParent ()->getParent ())
         {
            Trade *pTrade = dynamic_cast <Trade*> (getParent ()->getParent ());
            assert (pTrade);

            if (pTrade)
            {
               TradeBankInstructionsList *pTradeBankInstructionsList = NULL;

               if (  pTrade->getBankInstructionsList ( pTradeBankInstructionsList, 
                                                      idDataGroup,
                                                      true,
                                                      this) <= WARNING &&
                     pTradeBankInstructionsList)
               {
                  BFObjIter iter (*pTradeBankInstructionsList, idDataGroup);

                  if (!iter.end())
                  {
                     TradeBankInstructions *pTradeBankInstructions = 
                           dynamic_cast <TradeBankInstructions*> (iter.getObject());

                     pTradeBankInstructions->copyToSpecificCBO (idDataGroup);
                  }         
               }
            }
         }
      }
//see whether the address fields can be restored
      fillAddressInfo (idDataGroup, bDataNotFound);
      //pay method should be editable
      setFieldReadOnly (ifds::PayMethod, idDataGroup, false);
      setFieldReadOnly (ifds::ACHProcessor, idDataGroup, false);
      setFieldRequired (ifds::PayMethod, idDataGroup, true);
      setFieldRequired (ifds::ACHProcessor, idDataGroup, true);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TradePayInstruct.cpp-arc  $
// 
//    Rev 1.10   Oct 20 2006 18:14:58   popescu
// Incident# 731541 reviewed the way related changes for  fields is working in paym instruct
// 
//    Rev 1.9   Oct 19 2006 15:35:08   popescu
// Incident# 722294 - users will be able to override the trade payment instructions with system cheque
// 
//    Rev 1.8   Sep 22 2006 00:46:56   popescu
// STP 2217/13
// 
//    Rev 1.7   Sep 21 2006 01:50:38   popescu
// STP PET 2217/13
// 
//    Rev 1.6   Sep 20 2006 13:01:22   porteanm
// STP Pet 2217/13
// 
//    Rev 1.5   Sep 18 2006 00:25:40   popescu
// STP Pet 2217/13
// 
//    Rev 1.4   Sep 15 2006 19:43:18   popescu
// STP 2217/13 - fixes
// 
//    Rev 1.3   Sep 13 2006 19:11:32   popescu
// STP 2192/FN 13
// 
//    Rev 1.2   Sep 10 2006 18:00:26   popescu
// STP 2192/12
// 
//    Rev 1.1   Sep 07 2006 21:38:24   popescu
// STP 2192/02
// 
//    Rev 1.0   Aug 29 2006 18:26:52   popescu
// Initial revision.
*/
