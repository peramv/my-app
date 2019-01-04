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
// ^FILE   : TradePayInstructList.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : August, 2006
//
// ^CLASS    : TradePayInstructList 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "tradepayinstructlist.hpp"

#include "mgmtco.hpp"
#include "tradepayinstruct.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest TRADE_PAY_INSTRUCT;
}

namespace  
{
   const I_CHAR * const CLASSNAME = I_( "TradePayInstructList");  
}

namespace CND
{
   extern const long ERR_SUM_OF_PERCENTAGES_NOT_100;
   extern const long ERR_BROKER_PAYMENT_INSTRUCTIONS_FOR_REDEMPTION_MISSING;
   extern const long WARN_BROKER_PAYMENT_INSTRUCTIONS_FOR_REDEMPTION_MISSING;
   extern const long ERR_BROKER_PAYMENT_INSTRUCTIONS_FOR_DISTRIBUTION_MISSING;
   extern const long WARN_BROKER_PAYMENT_INSTRUCTIONS_FOR_DISTRIBUTION_MISSING;
}

namespace ifds
{   
   extern CLASS_IMPORT const BFDecimalFieldId AllocPercent;
   extern CLASS_IMPORT const BFTextFieldId PayToEntity;
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const BROKER_PAYMENT_FOR_SETUP_NOT_IN_PAIR;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo [] = {
//  Field DD Id,            State Flags,             Group Flags    
   { ifds::PayToEntity,	   BFCBO::NONE,	 0 },
   { ifds::TransNum,	      BFCBO::NONE,	 0 },
   { ifds::Broker,	      BFCBO::NONE,	 0 },
   { ifds::Branch,	      BFCBO::NONE,	 0 },
   { ifds::Branch,	      BFCBO::NONE,	 0 },
   { ifds::SalesRepCode,	BFCBO::NONE,	 0 },
   { ifds::EffectiveDate,	BFCBO::NONE,	 0 },
   { ifds::PaymentFor,	   BFCBO::NONE,	 0 },
};

static const int NUM_FIELDS = sizeof (classFieldInfo) / sizeof (BFCBO::CLASS_FIELD_INFO);

namespace PAYMENT_FOR
{
	extern const I_CHAR * REDEMPTION;
	extern const I_CHAR * DISTRIBUTION;
}

//*********************************************************************************
TradePayInstructList::TradePayInstructList (BFAbstractCBO &parent) : MFCanBFCbo (parent),
_idDataGroup (BF::HOST),
_bSetFieldsReadOnly (false)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL );
   setObjectAsList();
}

//*********************************************************************************
TradePayInstructList::~TradePayInstructList()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//*********************************************************************************
SEVERITY TradePayInstructList::init ( const DString &payToEntity,
                                      const DString &broker,
                                      const DString &branch,
                                      const DString &salesRepCode,
                                      const DString &effectiveDate,
                                      const DString &paymentFor,
                                      const BFDataGroupId& idDataGroup,
                                      const DString &dstrTrack, /*=I_("N")*/
                                      const DString &dstrPageName /*=NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   _idDataGroup = idDataGroup;
   setFieldNoValidate (ifds::Broker, broker, idDataGroup, false);
   setFieldNoValidate (ifds::Branch, branch, idDataGroup, false);
   setFieldNoValidate (ifds::SalesRepCode, salesRepCode, idDataGroup, false);
   setFieldNoValidate (ifds::EffectiveDate, effectiveDate, idDataGroup, false);
   setFieldNoValidate (ifds::PaymentFor, paymentFor, idDataGroup, false);
   setFieldNoValidate (ifds::PayToEntity, payToEntity, idDataGroup, false);
   
   DString mgmtCoIdOut;	
	BFData requestData (ifds::DSTC0374_REQ);
	
   requestData.setElementValue (ifds::Broker, broker);
   requestData.setElementValue (ifds::Branch, branch);
   requestData.setElementValue (ifds::SalesRepCode, salesRepCode);
   requestData.setElementValue (ifds::EffectiveDate, effectiveDate);
   requestData.setElementValue (ifds::PaymentFor, paymentFor);
   requestData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
	requestData.setElementValue (ifds::Track, dstrTrack);
	requestData.setElementValue (ifds::Activity, dstrPageName);
	ReceiveData ( DSTC_REQUEST::TRADE_PAY_INSTRUCT, 
                 requestData, 
                 ifds::DSTC0374_VW, 
                 DSTCRequestor (getSecurity(), false, false));

   return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************
SEVERITY TradePayInstructList::init ( const DString &payToEntity,
                                      const DString &transNum,
                                      const BFDataGroupId &idDataGroup,
                                      bool bSetFieldsReadOnly, /*=false*/
                                      const DString &dstrTrack, /*=I_("N")*/
                                      const DString &dstrPageName /*=NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   _idDataGroup = idDataGroup;
   _bSetFieldsReadOnly = bSetFieldsReadOnly;
   setFieldNoValidate (ifds::TransNum, transNum, idDataGroup, false);
   setFieldNoValidate (ifds::PayToEntity, payToEntity, idDataGroup, false);
   
   DString mgmtCoIdOut;	
	BFData requestData (ifds::DSTC0374_REQ);
	
   requestData.setElementValue (ifds::TransNum, transNum);
   requestData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
	requestData.setElementValue (ifds::Track, dstrTrack);
	requestData.setElementValue (ifds::Activity, dstrPageName);
	ReceiveData ( DSTC_REQUEST::TRADE_PAY_INSTRUCT, 
                 requestData, 
                 ifds::DSTC0374_VW, 
                 DSTCRequestor (getSecurity(), false, false));
   
   return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************
SEVERITY TradePayInstructList::initNew ( const DString &payToEntity,
                                         const DString &transNum, 
                                         const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("initNew"));

   _idDataGroup = idDataGroup;
   setFieldNoValidate (ifds::PayToEntity, payToEntity, idDataGroup, false);
   setFieldNoValidate (ifds::TransNum, transNum, idDataGroup, false);
	return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************
SEVERITY TradePayInstructList::doCreateObject (const BFData& data, BFCBO *&pObjOut)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "doCreateObject" ));
   DString payToEntity;

   getField (ifds::PayToEntity, payToEntity, _idDataGroup);
   pObjOut =  new TradePayInstruct( *this );
   ((TradePayInstruct* )pObjOut )->init (payToEntity, data, _idDataGroup, _bSetFieldsReadOnly);
   return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************
SEVERITY TradePayInstructList::doCreateNewObject ( BFCBO *&pBase, 
                                                   DString &strKey, 
                                                   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("doCreateNewObject"));
   DString payToEntity;

   getField (ifds::PayToEntity, payToEntity, idDataGroup);

   TradePayInstruct* pTradePayInstruct = new TradePayInstruct (*this);

   pTradePayInstruct->initNew (payToEntity, idDataGroup);

   pBase = pTradePayInstruct;
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradePayInstructList::addNewAllocation( const DString &paymentFor, 
                                                 const DString &payType,
											                const DString &payMethod,
                                                 const DString &currency,
                                                 const DString &achProcessor,
                                                 const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("addNewAllocation"));

   DString payToEntity;

   getField (ifds::PayToEntity, payToEntity, idDataGroup);
   assert (!payToEntity.empty());

   TradePayInstruct *pTradePayInstruct = NULL;
   BFObjectKey objKey (NULL_STRING, idDataGroup);
   pTradePayInstruct = dynamic_cast <TradePayInstruct *> (getNewListItem (objKey));

   if (!paymentFor.empty())
   {
      pTradePayInstruct->setField (ifds::PaymentFor, paymentFor, idDataGroup);
   }   	
   if (!payType.empty())
   {
      pTradePayInstruct->setField (ifds::PayType, payType, idDataGroup);
   }
   if (!payMethod.empty())
   {
      pTradePayInstruct->setField (ifds::PayMethod, payMethod, idDataGroup);
   }
   if (!currency.empty())
   {
      pTradePayInstruct->setField (ifds::Currency, currency, idDataGroup);
   }
   if (!achProcessor.empty())
   {
      pTradePayInstruct->setField (ifds::ACHProcessor, achProcessor, idDataGroup);
   }
	pTradePayInstruct->setField (ifds::AllocPercent, I_("100"), idDataGroup);
   pTradePayInstruct->setFieldUpdated (ifds::AllocPercent, idDataGroup, false);
   return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************
SEVERITY TradePayInstructList::doValidateAll (const BFDataGroupId &idDataGroup, 
                                              long lValidateGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll"));

   BFObjIter iter (*this, idDataGroup);
   double dTotalPercentage = 0;
   
   iter.begin();
   while (!iter.end())
   {
      TradePayInstruct *pTradePayInstruct = dynamic_cast <TradePayInstruct*> (iter.getObject());

		if (pTradePayInstruct)
      {
         DString dstrPercent;
		   pTradePayInstruct->getField (ifds::AllocPercent, dstrPercent, idDataGroup, false);
		   dstrPercent.strip().stripAll(I_CHAR(','));

		   I_CHAR *sPercentage;
		   double dPercentage = wcstod (dstrPercent.c_str(), &sPercentage); 
         dTotalPercentage += dPercentage;
         ++iter;
      }
   }
   
   if (GETCURRENTHIGHESTSEVERITY() <= WARNING)
   {
      if (fabs (dTotalPercentage) != 100)
		{
// Allocation percentages must sum up to 100%.
         ADDCONDITIONFROMFILE (CND::ERR_SUM_OF_PERCENTAGES_NOT_100);
		}
   }     
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradePayInstructList::otherBrokerPaymentForExist (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doValidateAll"));


   BFObjIter iter ( *this, 
						  idDataGroup, 
						  false, 
						  BFObjIter::ITERTYPE::NON_DELETED);

   if (!iter.end() && iter.getNumberOfItemsInList () == 1)
   {
      DString paymentFor,
         othPaymentForExist;

      getField (ifds::OthPaymentForExist, othPaymentForExist, idDataGroup, false);
      iter.getObject ()-> getField (ifds::PaymentFor, paymentFor, idDataGroup, false);
      othPaymentForExist.strip ().upperCase();
      if (paymentFor == PAYMENT_FOR::DISTRIBUTION && othPaymentForExist == I_("N"))
      {
         getErrMsg ( IFASTERR::BROKER_PAYMENT_FOR_SETUP_NOT_IN_PAIR, 
                     CND::ERR_BROKER_PAYMENT_INSTRUCTIONS_FOR_REDEMPTION_MISSING, 
                     CND::WARN_BROKER_PAYMENT_INSTRUCTIONS_FOR_REDEMPTION_MISSING, 
                     idDataGroup); 
      }
      else if (paymentFor == PAYMENT_FOR::REDEMPTION && othPaymentForExist == I_("N"))
      {
         getErrMsg ( IFASTERR::BROKER_PAYMENT_FOR_SETUP_NOT_IN_PAIR, 
                     CND::ERR_BROKER_PAYMENT_INSTRUCTIONS_FOR_DISTRIBUTION_MISSING, 
                     CND::WARN_BROKER_PAYMENT_INSTRUCTIONS_FOR_DISTRIBUTION_MISSING, 
                     idDataGroup); 
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TradePayInstructList.cpp-arc  $
// 
//    Rev 1.7   Oct 03 2006 22:26:00   popescu
// Incident #722094 - raise warn msgs if payment instr missing for either pw or id
// 
//    Rev 1.6   Sep 22 2006 00:47:00   popescu
// STP 2217/13
// 
//    Rev 1.5   Sep 21 2006 01:50:42   popescu
// STP PET 2217/13
// 
//    Rev 1.4   Sep 15 2006 19:43:22   popescu
// STP 2217/13 - fixes
// 
//    Rev 1.3   Sep 13 2006 19:11:34   popescu
// STP 2192/FN 13
// 
//    Rev 1.2   Sep 10 2006 18:00:38   popescu
// STP 2192/12
// 
//    Rev 1.1   Sep 07 2006 21:38:38   popescu
// STP 2192/02
// 
//    Rev 1.0   Aug 29 2006 18:27:02   popescu
// Initial revision.
*/
