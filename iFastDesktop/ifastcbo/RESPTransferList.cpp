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
// ^FILE   : RESPTransferList.cpp
// ^AUTHOR : Unknown
// ^DATE   : Febrary, 2010
//
// ^CLASS    : RESPTransferList 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "resptransferlist.hpp"
#include "resptransfer.hpp"
#include "accountentityxref.hpp"
#include <ifastcbo\errmsgruleslist.hpp>
#include "entity.hpp"
#include "dstcworksession.hpp"
#include "trade.hpp"
#include "RESPInfoUpdateValidationList.hpp"
#include "RespTransactionsDetails.hpp"
#include "resptransactionslist.hpp"
#include "TransactionDetails.hpp"

#include <ifastdataimpl\dse_dstc0407_req.hpp>
#include <ifastdataimpl\dse_dstc0406_req.hpp>
#include <ifastdataimpl\dse_dstc0406_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0406_vw.hpp>
#include <ifastdataimpl\dse_dstc0050_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0409_req.hpp>
#include <ifastdataimpl\dse_dstc0409_vw.hpp>

#include "mgmtco.hpp"


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest RESP_TRANSFER_INQUIRY;
   extern CLASS_IMPORT const DSTCRequest RESP_TRANSFER_BENE_INQUIRY;
}

namespace  
{
   const I_CHAR * const CLASSNAME      = I_( "RESPTransferList");  
   const I_CHAR * const BENEF_NAME     = I_("BENNAME");
   const I_CHAR * const UNITS          = I_( "U" );
   const I_CHAR * const NEW            = I_( "New" );
   const I_CHAR * const PENDING        = I_( "Pend" );
   const I_CHAR * const PROCESSED      = I_( "Proc" );
   const I_CHAR * const YES            = I_( "Y" );
   const I_CHAR * const NO             = I_( "N" );
   const I_CHAR * const RED_CODE64     = I_( "64" );
   const I_CHAR * const RED_CODE65     = I_( "65" );
   const I_CHAR * const DEP_CODE17     = I_( "17" );
   const I_CHAR * const PURCHASE       = I_( "ED" );
   const I_CHAR * const REDEMPTION     = I_( "PW" );
   const I_CHAR * const TRANSFER_LIKE  = I_( "TR,AFTR" );
   const I_CHAR * const PURCHASE_LIKE  = I_( "ED,TR,AFTR" );
   const I_CHAR * const TRANSFER_OUT   = I_( "TO" );
   const I_CHAR * const TRANSFER_IN	   = I_( "TI" );  
   const I_CHAR * const CLIENT         = I_( "03" );
   const I_CHAR * const EXT_PROVIDER   = I_( "12" );
   const I_CHAR * const DEFAULT_NEQ    = I_( "0" );  

   const double dSmallValue            = .0000000001;
}

namespace RECORD_LEVEL
{
   extern const CLASS_EXPORT I_CHAR * BENEFICIARY   = I_( "Benef" ); 
   extern const CLASS_EXPORT I_CHAR * ACCOUNT       = I_( "Acct" ); 
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId LastName;
   extern CLASS_IMPORT const BFTextFieldId FirstName;
   extern CLASS_IMPORT const BFDecimalFieldId Amount;
   extern CLASS_IMPORT const BFTextFieldId RESPTransStat;
   extern CLASS_IMPORT const BFTextFieldId TerminationAgeAfterDeff;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFTextFieldId CSSStopSINMatch;
   extern CLASS_IMPORT const BFIntegerFieldId WarnCode;
   extern CLASS_IMPORT const BFNumericFieldId HistNonTrustYear;
   extern CLASS_IMPORT const BFTextFieldId TotTransfINDC;
   extern CLASS_IMPORT const BFDateFieldId NonTrustStartDate;
   extern CLASS_IMPORT const BFDateFieldId NonTrustStopDate;
   extern CLASS_IMPORT const BFTextFieldId RESPQCResidentFound;
   extern CLASS_IMPORT const BFTextFieldId IsNotionalTaxYearApplicable;
   extern CLASS_IMPORT const BFTextFieldId IsTotTransfINDCApplicable;
   extern CLASS_IMPORT const BFTextFieldId IsNonTrustee;
   extern CLASS_IMPORT const BFTextFieldId IsInNonTrusteeTxfrPeriod;
   extern CLASS_IMPORT const BFTextFieldId BenefCurrTradeYearFound;
   extern CLASS_IMPORT const BFTextFieldId AnyBenefCurrTradeYear;
   extern CLASS_IMPORT const BFDecimalFieldId QESIPaid;
   extern CLASS_IMPORT const BFTextFieldId Cancelled;
   extern CLASS_IMPORT const BFTextFieldId Reversal;
}

namespace CND
{
   extern const long ERR_DUPLICATE_RECORD;	
   extern const long ERR_RESP_BENEF_ALLOCATIONS_MISSING;
   extern const long ERR_BENEFICIARY_NOT_EFFECTIVE;
   extern const long ERR_INVALID_INCEPTION_DATE;
   extern const long ERR_INVALID_TERMINATION_DATE;
   extern const long ERR_INVALID_RESP_PLAN;
   extern const long ERR_INVALID_RESP_CONTRACTIDS;
   extern const long ERR_RESP_LETTER_MISSING;
   extern const long ERR_RESP_INFOCOMPLETED_IS_MISSING;
   extern const long ERR_ONE_RESP_BENEF_ALLOWED;
   extern const long ERR_RESP_BENEF_IS_MISSING;
   extern const long WARN_RESP_TRANSFER_OUT;
   extern const long ERR_CLB_AMOUNT_CANNOT_BE_TRANSFERED;
   extern const long WARN_CLB_AMOUNT_CANNOT_BE_TRANSFERED;
   extern const long WARN_ACCOUNT_NOTINALS_ARE_ZERO;
   extern const long ERR_ADJUSTMENT_REQUIRED;
   extern const long WARN_ADJUSTMENT_MAY_BE_REQUIRED;
   extern const long ERR_SYS_TRIG_AMEND_AND_RECAL_QESI_NOTIONAL_BALANCE;
   extern const long WARN_SYS_TRIG_AMEND_AND_RECAL_QESI_NOTIONAL_BALANCE;
   extern const long ERR_MAY_NEED_TO_ADD_NEW_GRANT_REQUEST_FOR_TAX_YEAR; //1091
   extern const long WARN_MAY_NEED_TO_ADD_NEW_GRANT_REQUEST_FOR_TAX_YEAR;
   extern const long ERR_NON_TRUSTEE_UPDATE_HIST_INFO_REQ;
   extern const long WARN_NON_TRUSTEE_UPDATE_HIST_INFO_REQ;
   extern const long ERR_NON_ASSOCIATED_BENEF_IS_NOT_ALLOWED;//1124
   extern const long WARN_NON_ASSOCIATED_BENEF_IS_NOT_ALLOWED;
   extern const long ERR_BENEF_CURR_TAXYEAR_MANDATORY;
   extern const long ERR_DEL_HIST_TXFR_BENEF_RECORD;
   extern const long ERR_LTD_CONTRIB_MUST_EQUAL_SUM_OF_PRE98_CESGAC_CESGUC;
   extern const long WARN_LTD_CONTRIB_MUST_EQUAL_SUM_OF_PRE98_CESGAC_CESGUC;
   extern const long ERR_QESIPREFEB2007_NOT_EQUAL_LTD_MINUS_QESIAC_QESIUC_QESIYTD;
   extern const long WARN_QESIPREFEB2007_NOT_EQUAL_LTD_MINUS_QESIAC_QESIUC_QESIYTD;
   extern const long ERR_NOTIONAL_AMOUNTS_UPDATE_FOR_CANCELLED_OR_REVERSED_TRADE_NOT_ALLOWED;
   extern const long WARN_NOTIONAL_AMOUNTS_UPDATE_FOR_CANCELLED_OR_REVERSED_TRADE_NOT_ALLOWED;
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const CLB_AMOUNT_CANNOT_BE_TRANSFERED;
   extern CLASS_IMPORT I_CHAR * const ADJUSTMENT_MAY_BE_REQUIRED;
   extern CLASS_IMPORT I_CHAR * const SYS_TRIG_AMEND_AND_RECAL_QESI_NOTIONAL_BALANCE;
   extern CLASS_IMPORT I_CHAR * const MAY_NEED_TO_ADD_NEW_GRANT_REQUEST_FOR_TAX_YEAR;
   extern CLASS_IMPORT I_CHAR * const NON_TRUSTEE_UPDATE_HIST_INFO_REQ;
   extern CLASS_IMPORT I_CHAR * const NON_ASSOCIATED_BENEF_IS_NOT_ALLOWED;//1124
   extern CLASS_IMPORT I_CHAR * const LTD_CONTRIB_MUST_EQUAL_SUM_OF_PRE98_CESGAC_CESGUC;
   extern CLASS_IMPORT I_CHAR * const QESIPREFEB2007_NOT_EQUAL_LTD_MINUS_QESIAC_QESIUC_QESIYTD;
   extern CLASS_IMPORT I_CHAR * const NOTIONAL_AMOUNTS_UPDATE_FOR_CANCELLED_OR_REVERSED_TRADE_NOT_ALLOWED;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
   { ifds::EffectiveDate,     BFCBO::NONE,   0 }, 
   { ifds::Amount,            BFCBO::NONE,   0 }, 
   { ifds::TransId,           BFCBO::NONE,   0 }, 
   { ifds::AccountNum,        BFCBO::NONE,   0 }, 
   { ifds::AccountTo,         BFCBO::NONE,   0 }, 
   { ifds::CallType,          BFCBO::NONE,   0 }, 
   { ifds::TradeType,         BFCBO::NONE,   0 },
   { ifds::FromPlanNum,       BFCBO::NONE,   0 }, 
   { ifds::ToPlanNum,         BFCBO::NONE,   0 }, 
   { ifds::InceptionDate,     BFCBO::NONE,   0 }, 
   { ifds::NEQ1,              BFCBO::NONE,   0 }, 
   { ifds::NEQ2,              BFCBO::NONE,   0 }, 
   { ifds::FromContractId,    BFCBO::NONE,   0 }, 
   { ifds::AcctLvlOverride,   BFCBO::NONE,   0 }, 
   { ifds::ToContractId,      BFCBO::NONE,   0 }, 
   { ifds::TransType,         BFCBO::NONE,   0 }, 
   { ifds::DepositType,       BFCBO::NONE,   0 }, 
   { ifds::RedCode,           BFCBO::NONE,   0 }, 
   { ifds::TerminationDate,   BFCBO::NONE,   0 }, 
   { ifds::RESPLetter,        BFCBO::NONE,   0 }, 
   { ifds::RESPTransStat,     BFCBO::NONE,   0 }, 
 //  { ifds::IsNotionalTaxYearApplicable,   BFCBO::NONE,   0 }, 
 //  { ifds::IsTotTransfINDCApplicable,      BFCBO::NONE,   0 },
   { ifds::IsInNonTrusteeTxfrPeriod,      BFCBO::NONE,   0 }, 
   { ifds::AnyBenefCurrTradeYear,      BFCBO::NONE,   0 },  
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) 
                              / sizeof( BFCBO::CLASS_FIELD_INFO );

//*********************************************************************************
RESPTransferList::RESPTransferList (BFAbstractCBO &parent) : 
MFCanBFCbo (parent),
_bSetFieldsReadOnly (false),
_dstrPageName (NULL_STRING),
_dstrTrack (I_("N")),
_bOnlyUpdated(false),
_pRequestData(NULL),
_bNonTrusteeContrib(false) //IN2672499 - RESP Transfer Information error message
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0, NULL/*(const CLASS_OBJECT_INFO *)&classObjectInfo*/ );
   setObjectAsList();
}

//*********************************************************************************
RESPTransferList::~RESPTransferList()
{
   TRACE_DESTRUCTOR (CLASSNAME);
  
   if( _pRequestData )
   {
      delete _pRequestData;
      _pRequestData = NULL;
   }
}

//*********************************************************************************
SEVERITY RESPTransferList::initNew ( const DString &accountNum,
                                     const DString &accountNumTo,
                                     const DString &transType,
                                     const DString &tradeDate,
                                     const DString &depositType,
                                     const DString &redCode, 
                                     const DString &amount,
                                     const BFDataGroupId &idDataGroup,
                                     bool bSetFieldsReadOnly,    /*=false*/
                                     const DString &dstrTrack,   /*=I_("N")*/
                                     const DString &dstrPageName /*=NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   _bSetFieldsReadOnly = bSetFieldsReadOnly;
   _dstrPageName = dstrPageName;
   _dstrTrack = dstrTrack;

   setFieldNoValidate (ifds::CallType, I_("U"), idDataGroup, false);
   setFieldNoValidate (ifds::TradeType, NEW, idDataGroup, false);

   setFieldNoValidate (ifds::AccountNum, accountNum, idDataGroup, false);
   setFieldNoValidate (ifds::AccountTo, accountNumTo, idDataGroup, false);
   setFieldNoValidate (ifds::TransType, transType, idDataGroup, false);
   setFieldNoValidate (ifds::EffectiveDate, tradeDate, idDataGroup, false);
   setFieldNoValidate (ifds::DepositType, depositType, idDataGroup, false);
   setFieldNoValidate (ifds::RedCode, redCode, idDataGroup, false);
   setFieldNoValidate (ifds::Amount, amount, idDataGroup, false);

//deal with account level notionals...
   readDefaultNotionals (NULL_STRING, NULL_STRING, NULL_STRING, 0, idDataGroup);

   setInNonTrusteeTxfrPeriod(idDataGroup);
   //ToDo: Only Processed trade invoke this method
   setAnyBenefCurrTradeYear(idDataGroup);
   _bNonTrusteeContrib = isNonTrusteeContrib(idDataGroup); //IN2672499 - RESP Transfer Information error message


   return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************
SEVERITY RESPTransferList::init ( const DString &accountNum,
                                  const DString &accountNumTo,
                                  const DString &transId,
                                  const DString &transType,
                                  const DString &tradeDate,
                                  const DString &depositType,
                                  const DString &redCode, 
                                  const DString &amount,
                                  const DString &tradeType,   /*=I_("Pend")*/
                                  bool bSetFieldsReadOnly,    /*=false*/
                                  const DString &dstrTrack,   /*=I_("N")*/
                                  const DString &dstrPageName /*=NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   _bSetFieldsReadOnly = bSetFieldsReadOnly;

   setFieldNoValidate (ifds::CallType, I_("U"), BF::HOST, false);
   setFieldNoValidate (ifds::TradeType, tradeType, BF::HOST, false);

   setFieldNoValidate (ifds::AccountNum, accountNum, BF::HOST, false);
   setFieldNoValidate (ifds::AccountTo, accountNumTo, BF::HOST, false);
   setFieldNoValidate (ifds::TransId, transId, BF::HOST, false);
   setFieldNoValidate (ifds::TransType, transType, BF::HOST, false);
   setFieldNoValidate (ifds::EffectiveDate, tradeDate, BF::HOST, false);
   setFieldNoValidate (ifds::DepositType, depositType, BF::HOST, false);
   setFieldNoValidate (ifds::RedCode, redCode, BF::HOST, false);
   setFieldNoValidate (ifds::Amount, amount, BF::HOST, false);

   DString mgmtCoIdOut;
   _pRequestData = new BFData(ifds::DSTC0406_REQ);
   _pRequestData->setElementValue (ifds::TradeType, tradeType);
   _pRequestData->setElementValue (ifds::TransId, transId);
   _pRequestData->setElementValue (ifds::AccountNum, accountNum);
   _pRequestData->setElementValue (ifds::AccountTo, accountNumTo);
   _pRequestData->setElementValue (ifds::TransType, transType);
   _pRequestData->setElementValue (ifds::EffectiveDate, tradeDate);
   _pRequestData->setElementValue (ifds::DepositType, depositType);
   _pRequestData->setElementValue (ifds::RedCode, redCode);

   _pRequestData->setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   _pRequestData->setElementValue (ifds::Track, dstrTrack);
   _pRequestData->setElementValue (ifds::Activity, dstrPageName);

   ReceiveData ( DSTC_REQUEST::RESP_TRANSFER_INQUIRY, 
                 *_pRequestData, 
                 ifds::DSTC0406_VW, 
                 DSTCRequestor (getSecurity(), false, false));

   commonInit (BF::HOST);
   //internal used field
   setInNonTrusteeTxfrPeriod(BF::HOST);
   _bNonTrusteeContrib = isNonTrusteeContrib(BF::HOST); //IN2672499 - RESP Transfer Information error message

   return GETCURRENTHIGHESTSEVERITY ();
}

//********************************************************************************
SEVERITY RESPTransferList::doCreateObject (const BFData& data, BFCBO *&pObjOut)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ));

   pObjOut =  new RESPTransfer( *this );

   ((RESPTransfer* )pObjOut )->init (data, BF::HOST, _bSetFieldsReadOnly);

   return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************
SEVERITY RESPTransferList::doCreateNewObject ( BFCBO *&pBase, 
                                               DString &strKey, 
                                               const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateNewObject"));

   RESPTransfer* pRESPTransfer = new RESPTransfer (*this);

   if(!_bOnlyUpdated)
   {
      pRESPTransfer->initNew (idDataGroup, _bSetFieldsReadOnly);
   }

   pBase = pRESPTransfer;

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY RESPTransferList::setFieldsReadOnly (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("setFieldsReadOnly"));

   setFieldReadOnly (ifds::FromPlanNum, idDataGroup, true);
   setFieldReadOnly (ifds::ToPlanNum, idDataGroup, true);
   setFieldReadOnly (ifds::InceptionDate, idDataGroup, true);
   setFieldReadOnly (ifds::NEQ1, idDataGroup, true);
   setFieldReadOnly (ifds::FromContractId, idDataGroup, true);
   setFieldReadOnly (ifds::ToContractId, idDataGroup, true);
   setFieldReadOnly (ifds::TerminationDate, idDataGroup, true);
   setFieldReadOnly (ifds::RESPLetter, idDataGroup, true);
   setFieldReadOnly (ifds::RESPTransStat, idDataGroup, true);
   setFieldReadOnly (ifds::AcctLvlOverride, idDataGroup, true);

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY RESPTransferList::readDefaultNotionals ( const DString &benefIdFrom_,
                                                  const DString &benefIdTo_,
                                                  const DString &benefIdSeqTo_,
                                                  const DString &transferPercent_,
                                                  const BFDataGroupId &idDataGroup,
                                                  bool bAcctTransferPercent,
                                                  bool bTransferPercentUpdate)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("readDefaultNotionals"));

   DString benefId (benefIdFrom_),
      transferPercent (transferPercent_),
      recordLevel;
   bool moreRecordsAvailable;

   benefId.stripLeading ('0');  

   if (!benefId.empty() || bAcctTransferPercent) //beneficiary level notionals... & account level tranfer %
   {
      if (bAcctTransferPercent)
         recordLevel = RECORD_LEVEL::ACCOUNT;
      else
         recordLevel = RECORD_LEVEL::BENEFICIARY;

      BFData requestData (ifds::DSTC0409_REQ),
         *receivedData = new BFData (ifds::DSTC0409_VW);

      populateRequestData (requestData, idDataGroup);
      requestData.setElementValue (ifds::RESPBenefId, benefId);
		  requestData.setElementValue (ifds::TransferPercent, transferPercent);
      requestData.setElementValue (ifds::RecordLevel, recordLevel);
      if (BFDataBroker::getInstance( )->receive( DSTC_REQUEST::RESP_TRANSFER_BENE_INQUIRY,
                                                 requestData, 
                                                 *receivedData, 
                                                 DSTCRequestor (getSecurity(), false, false), 
                                                 &moreRecordsAvailable) <= WARNING)
      {
         RESPTransfer* pRESPTransfer = new RESPTransfer (*this);

         pRESPTransfer->init (*receivedData, idDataGroup, _bSetFieldsReadOnly, true);
         DString strKey (NULL_STRING);
         BF_OBJ_ACTIVITY objActivity (OBJ_ACTIVITY_ADDED);

         getStrKey (strKey, receivedData);
//get the parent..
         Trade *pTrade = dynamic_cast <Trade*> (getParent());

         /*if (pTrade && !pTrade->isNew ())
		 {
			objActivity = OBJ_ACTIVITY_NONE;
         }*/
         setObject (pRESPTransfer, strKey,  objActivity, idDataGroup);
         pRESPTransfer->clearUpdatedFlags (idDataGroup);
		 pRESPTransfer->setNonDummyFlag ();

         if (bTransferPercentUpdate)
         {
            pRESPTransfer->setFieldUpdated (ifds::TransferPercent, idDataGroup, true);
         }

         if (!benefIdTo_.empty () && isInternalTransfer (idDataGroup))
         {
            pRESPTransfer->setField(ifds::RESPBenefIDTo, benefIdTo_, idDataGroup);
            pRESPTransfer->setField(ifds::RESPTrfEntityTypeSeqTo, benefIdSeqTo_, idDataGroup);
         }
      }
      else
      {
         delete receivedData;
         receivedData = NULL;
      }
   }
   else //account level notionals
   {
      BFData requestData (ifds::DSTC0406_REQ),
         *receivedData = new BFData (ifds::DSTC0406_VW);

      populateRequestData (requestData, idDataGroup);
      if (BFDataBroker::getInstance( )->receive( DSTC_REQUEST::RESP_TRANSFER_INQUIRY,
                                                 requestData, 
                                                 *receivedData, 
                                                 DSTCRequestor (getSecurity(), false, false), 
                                                 &moreRecordsAvailable) <= WARNING)
      {
         attachDataObject (*receivedData, true, false);
         int repeats = receivedData->getRepeatCount ();

         for (int i = 0; i < repeats; i++)
         {
            RESPTransfer* pRESPTransfer = new RESPTransfer (*this);

            pRESPTransfer->init (receivedData->getRepeat (i), idDataGroup, _bSetFieldsReadOnly);

            DString dstrKey (NULL_STRING);

            getStrKey (dstrKey, &receivedData->getRepeat (i));
            setObject (pRESPTransfer, dstrKey, OBJ_ACTIVITY_ADDED, idDataGroup);
            pRESPTransfer->clearUpdatedFlags (idDataGroup);
            pRESPTransfer->setNonDummyFlag();
            pRESPTransfer->setField (ifds::RecordLevel, RECORD_LEVEL::ACCOUNT, idDataGroup);
         }

         commonInit (idDataGroup);
      }
      else
      {
         delete receivedData;
         receivedData = NULL;
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY RESPTransferList::restoreNotionals ( const DString &benefIdFrom_,
                                              const DString &benefIdTo_,
                                              const DString &benefIdSeqTo_,
                                              const DString &transferPercent_,
                                              const BFDataGroupId &idDataGroup,
                                              bool bAcctLevel,                                              										 
											  DString &strKey)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("restoreNotionals"));

   DString benefId (benefIdFrom_),
		   transferPercent (transferPercent_),
		   recordLevel;
   bool moreRecordsAvailable;

   benefId.stripLeading ('0');  

   bool bNotionalsRestored = false;

   if (!benefId.empty() || bAcctLevel) // account/beneficiary level notionals
   {
	   BFData requestData (ifds::DSTC0406_REQ),
		   *receivedData = new BFData (ifds::DSTC0406_VW);

	   populateRequestData (requestData, idDataGroup);
	   if (BFDataBroker::getInstance( )->receive( DSTC_REQUEST::RESP_TRANSFER_INQUIRY,
		   requestData, 
		   *receivedData, 
		   DSTCRequestor (getSecurity(), false, false), 
		   &moreRecordsAvailable) <= WARNING)
	   {
		   attachDataObject (*receivedData, true, false);
		   int repeats = receivedData->getRepeatCount ();

		   for (int i = 0; i < repeats; i++)
		   {			
			   RESPTransfer* pRESPTransfer = new RESPTransfer (*this);

			   const BFData& repeatData = receivedData->getRepeat(i);
			   DString dstrBenefId = repeatData.getElementValue(I_("RESPBenefIDFrom"));
			   dstrBenefId.stripLeading ('0');			

			   if (benefId == dstrBenefId)
			   {
				   pRESPTransfer->init (receivedData->getRepeat (i), idDataGroup, _bSetFieldsReadOnly);

				   getStrKey (strKey, &receivedData->getRepeat (i));
				   setObject (pRESPTransfer, strKey, OBJ_ACTIVITY_ADDED, idDataGroup);
				   pRESPTransfer->clearUpdatedFlags (idDataGroup);
				   pRESPTransfer->setNonDummyFlag();
				   bNotionalsRestored = true;
			   }
		   }
	   }
	   else
	   {
		   delete receivedData;
		   receivedData = NULL;
	   }
   }

   if (!benefId.empty() && !bNotionalsRestored) // beneficiary level notionals
   {
	   BFData requestData (ifds::DSTC0409_REQ),
		   *receivedData = new BFData (ifds::DSTC0409_VW);

	   populateRequestData (requestData, idDataGroup);
	   requestData.setElementValue (ifds::RESPBenefId, benefId);
	   requestData.setElementValue (ifds::TransferPercent, transferPercent);
	   requestData.setElementValue (ifds::RecordLevel, RECORD_LEVEL::BENEFICIARY);

	   if (BFDataBroker::getInstance( )->receive( DSTC_REQUEST::RESP_TRANSFER_BENE_INQUIRY,
		   requestData, 
		   *receivedData, 
		   DSTCRequestor (getSecurity(), false, false), 
		   &moreRecordsAvailable) <= WARNING)
	   {	
		   RESPTransfer* pRESPTransfer = new RESPTransfer (*this);

		   pRESPTransfer->init (*receivedData, idDataGroup, _bSetFieldsReadOnly);

		   getStrKey (strKey, receivedData);
		   setObject (pRESPTransfer, strKey, OBJ_ACTIVITY_ADDED, idDataGroup);
		   pRESPTransfer->clearUpdatedFlags (idDataGroup);
		   pRESPTransfer->setNonDummyFlag();			 

		   if (!benefIdTo_.empty () && isInternalTransfer (idDataGroup))
		   {
			   pRESPTransfer->setField(ifds::RESPBenefIDTo, benefIdTo_, idDataGroup);
			   pRESPTransfer->setField(ifds::RESPTrfEntityTypeSeqTo, benefIdSeqTo_, idDataGroup);
		   }
	   }
	   else
	   {
		   delete receivedData;
		   receivedData = NULL;
	   }
   }	  

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY RESPTransferList::populateRequestData ( BFData &requestData,
                                                 const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "populateRequestData" ) );
   DString tradeType,
      accountNum,
      accountNumTo,
      transType,
      transId,
      tradeDate,
      depositType,
      redCode,
      amount;

   getField (ifds::TradeType, tradeType, idDataGroup, false);
   getField (ifds::TransId, transId, idDataGroup, false);
   getField (ifds::AccountNum, accountNum, idDataGroup, false);
   getField (ifds::AccountTo, accountNumTo, idDataGroup, false);
   getField (ifds::TransType, transType, idDataGroup, false);
   getField (ifds::EffectiveDate, tradeDate, idDataGroup, false);
   getField (ifds::DepositType, depositType, idDataGroup, false);
   getField (ifds::RedCode, redCode, idDataGroup, false);
   getField (ifds::Amount, amount, idDataGroup, false);

   DString mgmtCoIdOut;

   requestData.setElementValue (ifds::TradeType, tradeType);
   requestData.setElementValue (ifds::TransId, transId);
   requestData.setElementValue (ifds::AccountNum, accountNum);
   requestData.setElementValue (ifds::AccountTo, accountNumTo);
   requestData.setElementValue (ifds::TransType, transType);
   requestData.setElementValue (ifds::EffectiveDate, tradeDate);
   requestData.setElementValue (ifds::DepositType, depositType);
   requestData.setElementValue (ifds::RedCode, redCode);

   requestData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   requestData.setElementValue (ifds::Track, _dstrTrack);
   requestData.setElementValue (ifds::Activity, _dstrPageName);

   return GETCURRENTHIGHESTSEVERITY ();
}


//******************************************************************************
SEVERITY RESPTransferList::checkDuplicate ( const RESPTransfer *pRESPTransferToCheck,
                                            const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "checkDuplicate" ) );

   DString dstrEntityIdToCheck;
   DString dstrHistNonTrustYearToCheck(NULL_STRING);
   DString dstrRESPBenefIDToCheck(NULL_STRING);

   pRESPTransferToCheck->getField (ifds::RESPBenefIDFrom, dstrEntityIdToCheck, idDataGroup);
   pRESPTransferToCheck->getField (ifds::HistNonTrustYear, dstrHistNonTrustYearToCheck, idDataGroup);
   pRESPTransferToCheck->getField (ifds::RESPBenefIDTo, dstrRESPBenefIDToCheck, idDataGroup);
   if(dstrRESPBenefIDToCheck.empty())
   {
      dstrRESPBenefIDToCheck = I_("0");
   }
   bool bIsNonTrustee = isNonTrustee(idDataGroup);

   bool bHasDuplicate = false;

   //check first whether in the list (in memory) we have a duplicate
   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
   iter.begin();

   while (!iter.end())
   {
      RESPTransfer *pRESPTransfer = dynamic_cast<RESPTransfer*>(iter.getObject());
      // Don't check against itself
      if ( pRESPTransfer != pRESPTransferToCheck )
      {
         DString dstrCurrentEntityId;

         pRESPTransfer->getField( ifds::RESPBenefIDFrom, dstrCurrentEntityId, idDataGroup );

         if (dstrCurrentEntityId == dstrEntityIdToCheck )
         {
            if(bIsNonTrustee)
            {
               DString dstrHistNonTrustYear(NULL_STRING);
               DString dstrRESPBenefIDTo(NULL_STRING);

               pRESPTransfer->getField (ifds::HistNonTrustYear, dstrHistNonTrustYear, idDataGroup);
               pRESPTransfer->getField (ifds::RESPBenefIDTo, dstrRESPBenefIDTo, idDataGroup);
               if(dstrRESPBenefIDTo.empty())
               {
                  dstrRESPBenefIDTo = I_("0");
               }

               if((dstrHistNonTrustYear == dstrHistNonTrustYearToCheck) &&
                  (dstrRESPBenefIDTo == dstrRESPBenefIDToCheck))
               {
                  bHasDuplicate = true;
                  break;
               }
            }
            else
            {
               bHasDuplicate = true;
               break;
            }
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

//*****************************************************************************************
SEVERITY RESPTransferList::doAcctLevelOverrideChanges (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doAcctLevelOverrideChanges")); 

   RESPTransfer *pRESPTransfer = NULL;
   DString  dstrAccountLevelOverride;

   getField (ifds::AcctLvlOverride, dstrAccountLevelOverride, idDataGroup, false);

   bool bReadOnly = /*dstrAccountLevelOverride == YES ? false :*/ true;

   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
   iter.begin();

   bool bIsRespTransformation = getWorkSession().isRESPTransformationClient ();
   while (!iter.end())
   {
      pRESPTransfer = dynamic_cast<RESPTransfer*>(iter.getObject());

      if (pRESPTransfer)
      {
         DString dstrRecordLevel;

         pRESPTransfer->getField (ifds::RecordLevel, dstrRecordLevel, idDataGroup, false);

		 if (bIsRespTransformation)
		 {
			 if (dstrRecordLevel == RECORD_LEVEL::ACCOUNT)
			 {	 
				 pRESPTransfer->setGrantsReadOnly (bReadOnly, idDataGroup);				  
			 }
			 else
			 {
				 pRESPTransfer->setFederalFieldsReadOnly (idDataGroup);
			 }
		 }
		 else 
		 {
			 if (dstrRecordLevel == RECORD_LEVEL::ACCOUNT)
			 {
				 pRESPTransfer->setGrantsReadOnly (bReadOnly, idDataGroup);
				 break;
			 }
		 }
      }

      ++iter;
   }

   /*if (pRESPTransfer)
   {
      pRESPTransfer->setGrantsReadOnly (bReadOnly, idDataGroup);
   }*/

   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY RESPTransferList::doApplyRelatedChanges ( const BFFieldId& idField, 
                                                   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));

   if (idField == ifds::InceptionDate)
   {
      doInceptionDateChanges (idDataGroup);
   }	
   else if (idField == ifds::AcctLvlOverride)
   {
      doAcctLevelOverrideChanges (idDataGroup);
   }
   else if(idField == ifds::NEQ1)
   {
      doNEQ1RelatedChanges(idDataGroup);
   }
   else if(idField == ifds::RESPTransStat)
   {  
      doRESPTransStatRelatedChanges(idDataGroup);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RESPTransferList::doInceptionDateChanges (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doInceptionDateChanges"));

   DString dstrTerminationAge;
   DString dstrInceptionDate;
   DString dstrTerminationDate;
   DString dstrTrerminationYear;
   bool	bFromClient = false;
   bool	bToClient = false;

   getWorkSession ().getOption (ifds::TerminationAgeAfterDeff, dstrTerminationAge, idDataGroup, false);

   getField (ifds::InceptionDate, dstrInceptionDate, idDataGroup, false);
   getField (ifds::TerminationDate, dstrTerminationDate, idDataGroup, false);

   if (dstrTerminationDate.empty () || dstrTerminationDate == NULL_STRING)
   {
      getWorkSession().getDateInHostFormat (dstrTerminationDate, DSTCWorkSession::DATE_TYPE::DAY12319999, idDataGroup);
   }

   I_CHAR *sAmount;
   double dTerminationAge = wcstod (dstrTerminationAge.c_str(), &sAmount); 

   int year = getYear (dstrInceptionDate);
   int iTerminationYear = year + (int) dTerminationAge;
   int year_pos = DSTCommonFunctions::getYearPosition();

   convertIntToString (iTerminationYear, dstrTrerminationYear);
   dstrTerminationDate.replace( year_pos, 4, dstrTrerminationYear);

   setFieldNoValidate (ifds::TerminationDate, dstrTerminationDate, idDataGroup, false, true, true, true);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void RESPTransferList::initNEQs (const DString &depositType, 
                                 const DString &redCode,
                                 const BFDataGroupId &idDataGroup)
{
   DString fromNEQ;
   DString toNEQ;
   DString dstrNEQId;
   bool	bFromClient = false;
   bool	bToClient = false;
   bool    bInternalTransfer = false;
   DString tradeType;

   getField (ifds::TradeType, tradeType, idDataGroup, false);

   getWorkSession().getNEQId (dstrNEQId, CLIENT, idDataGroup);

   if (depositType == DEP_CODE17 && !(redCode == RED_CODE64 || redCode == RED_CODE65))
   {
      getWorkSession().getNEQList (fromNEQ, EXT_PROVIDER, idDataGroup);
      getWorkSession().getNEQList (toNEQ, CLIENT, idDataGroup);
      bToClient = true;
   }
   else if (depositType == DEP_CODE17 && (redCode == RED_CODE64 || redCode == RED_CODE65))
   {
      getWorkSession().getNEQList (fromNEQ, CLIENT, idDataGroup);
      toNEQ = fromNEQ;
      bFromClient = true;
      bToClient = true;
      bInternalTransfer = true;
   }
   else if (depositType != DEP_CODE17 && (redCode == RED_CODE64 || redCode == RED_CODE65))
   {
      getWorkSession().getNEQList (fromNEQ, CLIENT, idDataGroup);
      getWorkSession().getNEQList (toNEQ, EXT_PROVIDER, idDataGroup);
      bFromClient = true;
   }

   setFieldAllSubstituteValues (ifds::NEQ1, idDataGroup, fromNEQ ); 
   setFieldAllSubstituteValues (ifds::NEQ2, idDataGroup, toNEQ ); 

   if (bFromClient)
   {
      setFieldNoValidate (ifds::NEQ1, dstrNEQId, idDataGroup, false);

      if (tradeType == NEW && !bInternalTransfer)
      {
         setFieldNoValidate (ifds::NEQ2, DEFAULT_NEQ, idDataGroup, false);
      }
   }

   if (bToClient)
   {
      if (tradeType == NEW && !bInternalTransfer)
      {
         setFieldNoValidate (ifds::NEQ1, DEFAULT_NEQ, idDataGroup, false);
      }

      setFieldNoValidate (ifds::NEQ2, dstrNEQId, idDataGroup, false);
   }
}

//******************************************************************************
void RESPTransferList::initDates ( const DString &depositType, 
                                   const DString &redCode,
                                   const BFDataGroupId &idDataGroup)
{
   bool bReadOnly = false;
   bool bRespToResp = (depositType == DEP_CODE17 && (redCode == RED_CODE64 || redCode == RED_CODE65)) ? true : false;

   DString dstrTradeType;
   DString dstrUpdateComplete;

   getField (ifds::TradeType, dstrTradeType, idDataGroup, false);
   getField (ifds::RESPTransStat, dstrUpdateComplete, idDataGroup, false);

   if (dstrTradeType == PROCESSED && dstrUpdateComplete == YES)
   {
      bReadOnly = true;
   }
   else
   {
      if (depositType == DEP_CODE17 && !bRespToResp)
      {
         bReadOnly = false;
      }
      else 
      {
         bReadOnly = true;
      }
   }

   setFieldReadOnly (ifds::InceptionDate, idDataGroup, bReadOnly);
   setFieldReadOnly (ifds::TerminationDate, idDataGroup, bReadOnly);

}

//******************************************************************************
bool RESPTransferList::initTransferPercent (const BFDataGroupId &idDataGroup)
{
   bool bReadOnly =  false;
   DString tradeType;
   DString redCode;
   DString depositType;

   getField (ifds::TradeType, tradeType, idDataGroup, false);
   getField (ifds::RedCode, redCode, idDataGroup, false);
   getField (ifds::DepositType, depositType, idDataGroup, false);

   if (tradeType == PROCESSED)
   {
      bReadOnly =  true;
   }
   else
   {
	   bReadOnly = (redCode == RED_CODE64 || redCode == RED_CODE65) ? false : true;
   }

   return bReadOnly;
}

//******************************************************************************
bool RESPTransferList::isAcctLevelOverrideApplicable (const BFDataGroupId &idDataGroup)
{
   bool bApplicable = false;
   DString tradeType;
   DString depositType;
   DString redCode;
   DString transType;

   getField (ifds::TradeType, tradeType, idDataGroup, false);
   getField (ifds::DepositType, depositType, idDataGroup, false);	
   getField (ifds::RedCode, redCode, idDataGroup, false);
   getField (ifds::TransType, transType, idDataGroup, false);

   bool bPurchase = transType == PURCHASE && depositType == DEP_CODE17 ? true : false;
   bool bTransfer = DSTCommonFunctions::codeInList (transType, TRANSFER_LIKE) && depositType == DEP_CODE17 ? true : false;
   bool bNonRespToResp = depositType == DEP_CODE17 && !(redCode == RED_CODE64 || redCode == RED_CODE65) ? true : false;

   if (bPurchase || (bNonRespToResp && bTransfer))
   {
	   bApplicable = true;
   }   

   return bApplicable;
}

//******************************************************************************
bool RESPTransferList::isManualOverrideApplicable (const BFDataGroupId &idDataGroup)
{
	bool bApplicable = false;
	DString tradeType, depositType, redCode, transType;	

	getField (ifds::TradeType, tradeType, idDataGroup, false);
	getField (ifds::DepositType, depositType, idDataGroup, false);	
	getField (ifds::RedCode, redCode, idDataGroup, false);
	getField (ifds::TransType, transType, idDataGroup, false);	

	if (tradeType != PROCESSED && (transType == REDEMPTION || DSTCommonFunctions::codeInList (transType, TRANSFER_LIKE)) && (redCode == RED_CODE64 || redCode == RED_CODE65))
	{		
		bApplicable = true; // external or internal transfer out
	}

	return bApplicable;
}

//******************************************************************************
void RESPTransferList::initLetterAndStatus (const DString &tradeType, 
                                            const DString &depositType,
                                            const DString &redCode,
                                            const DString &transType,
                                            const BFDataGroupId &idDataGroup)
{
   DString dstrUpdateComplete;

   getField (ifds::RESPTransStat, dstrUpdateComplete, idDataGroup, false);

   // init RESP Letter
   if (tradeType == PROCESSED)
   {
      setFieldReadOnly (ifds::RESPLetter, idDataGroup, true);
   }
   else
   {
      if ((redCode == RED_CODE64 || redCode == RED_CODE65))
      {
         if (tradeType == NEW)
         {
            setFieldNoValidate (ifds::RESPLetter, I_(""), idDataGroup, false);
         }
      }
      else
      {
         setFieldReadOnly (ifds::RESPLetter, idDataGroup, true);
      }
   }

   // Information completed: 
   bool bNonRespToResp = (depositType == DEP_CODE17 && !(redCode == RED_CODE64 || redCode == RED_CODE65)) ? true : false;

   if (tradeType == PROCESSED && dstrUpdateComplete == YES)
   {
      setFieldReadOnly (ifds::RESPTransStat, idDataGroup, true);
   }
   else
   {
      if (transType == PURCHASE || bNonRespToResp)
      {
         if (tradeType == NEW)
         {
            setFieldNoValidate (ifds::RESPTransStat, I_(""), idDataGroup, false);
         }
      }
      else
      {
         setFieldNoValidate (ifds::RESPTransStat, YES, idDataGroup, false);
         setFieldReadOnly (ifds::RESPTransStat, idDataGroup, true);
      }
   }
}

//******************************************************************************
bool RESPTransferList::isNonRespToResp (const BFDataGroupId &idDataGroup)
{
   bool bNonRespToResp = false;

   DString depositType;
   DString redCode;
   DString transType;

   getField (ifds::DepositType, depositType, idDataGroup, false);	
   getField (ifds::RedCode, redCode, idDataGroup, false);
   getField (ifds::TransType, transType, idDataGroup, false);

   transType.stripAll ();
   depositType.stripAll ();
   redCode.stripAll ();

   if (!DSTCommonFunctions::codeInList (transType, TRANSFER_LIKE))
      return bNonRespToResp;

   bNonRespToResp = (depositType == DEP_CODE17 && !(redCode == RED_CODE64 || redCode == RED_CODE65)) ? true : false;

   return bNonRespToResp;
}

//******************************************************************************
void RESPTransferList::initFromPlanInfo (const DString &depositType, 
                                         const DString &redCode,
                                         const DString &transType,
                                         const BFDataGroupId &idDataGroup)
{
   bool bNonRespToResp = (depositType == DEP_CODE17 && !(redCode == RED_CODE64 || redCode == RED_CODE65)) ? true : false;
   bool bReadOnly = false;

   if (transType == PURCHASE || bNonRespToResp)
   {
      bReadOnly = false;
   }
   else
   {
      bReadOnly = true;
   }

   setFieldReadOnly (ifds::FromPlanNum, idDataGroup, bReadOnly);
   setFieldReadOnly (ifds::FromContractId, idDataGroup, bReadOnly);

}

//***********************************************************************************
void RESPTransferList::initToPlanInfo (const DString &depositType, 
                                       const DString &redCode,
                                       const DString &transType,
                                       const BFDataGroupId &idDataGroup)
{
   bool bNonRespToResp = (depositType == DEP_CODE17 && !(redCode == RED_CODE64 || redCode == RED_CODE65)) ? true : false;
   bool bRespToResp = (depositType == DEP_CODE17 && (redCode == RED_CODE64 || redCode == RED_CODE65)) ? true : false;

   bool bReadOnly = false;

   if (transType == PURCHASE || bNonRespToResp ||
      (transType == TRANSFER_OUT && bRespToResp))
   {
      bReadOnly = true;
   }
   else 
   {
      bReadOnly = false;
   }

   setFieldReadOnly (ifds::ToPlanNum, idDataGroup, bReadOnly);
   setFieldReadOnly (ifds::ToContractId, idDataGroup, bReadOnly);
}

//***********************************************************************************
SEVERITY RESPTransferList::commonInit (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("commonInit"));

   DString tradeType;
   DString depositType;
   DString redCode;
   DString transType;

   getField (ifds::TradeType, tradeType, idDataGroup, false);
   getField (ifds::DepositType, depositType, idDataGroup, false);
   getField (ifds::RedCode, redCode, idDataGroup, false);
   getField (ifds::TransType, transType, idDataGroup, false);

   initLetterAndStatus (tradeType, depositType, redCode, transType, idDataGroup);
   initNEQs (depositType, redCode, idDataGroup);
   initDates (depositType, redCode, idDataGroup);

   initFromPlanInfo (depositType, redCode, transType, idDataGroup);
   initToPlanInfo (depositType, redCode, transType, idDataGroup);

   if (_bSetFieldsReadOnly)
      setFieldsReadOnly (idDataGroup);

   /*if (tradeType == PENDING || tradeType == PROCESSED)
      setAccountCLBGrant (idDataGroup);*/

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RESPTransferList::validateFromToBeneficiary (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFromToBeneficiary" ) );   	

   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );

   RESPTransfer *pRESPTransfer;

   while (!iter.end())
   {
      pRESPTransfer = dynamic_cast<RESPTransfer*>(iter.getObject());

      if (pRESPTransfer)
      {
         pRESPTransfer->validateFromToBeneficiary (idDataGroup);
      }
      ++iter;
   }

   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY RESPTransferList::validateInceptionDate (const DString &dstrInceptionDate, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateInceptionDate" ) );   	

   DString dstrCurrentBusDate;
   DString dstrTradeType;
   DString dstrUpdateComplete;

   getField (ifds::TradeType, dstrTradeType, idDataGroup, false);
   getField (ifds::RESPTransStat, dstrUpdateComplete, idDataGroup, false);

   if (dstrTradeType == PROCESSED && dstrUpdateComplete == YES)
      return GETCURRENTHIGHESTSEVERITY();

   getWorkSession().getOption( ifds::CurrBusDate, dstrCurrentBusDate, idDataGroup, false );

   if ( DSTCommonFunctions::CompareDates (dstrInceptionDate, dstrCurrentBusDate) == DSTCommonFunctions::SECOND_EARLIER )
   {
      ADDCONDITIONFROMFILE (CND::ERR_INVALID_INCEPTION_DATE);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RESPTransferList::validateTerminationDate (const DString &dstrTerminationDate, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateTerminationDate" ) );   	

   DString dstrInceptionDate;
   DString dstrTerminationAge;

   DString dstrTradeType;
   DString dstrUpdateComplete;

   getField (ifds::TradeType, dstrTradeType, idDataGroup, false);
   getField (ifds::RESPTransStat, dstrUpdateComplete, idDataGroup, false);

   if (dstrTradeType == PROCESSED && dstrUpdateComplete == YES)
      return GETCURRENTHIGHESTSEVERITY();

   getWorkSession ().getOption (ifds::TerminationAgeAfterDeff, dstrTerminationAge, idDataGroup, false);

   I_CHAR *sAmount;
   double dTerminationAge = wcstod (dstrTerminationAge.c_str(), &sAmount); 

   getField (ifds::InceptionDate, dstrInceptionDate, idDataGroup);

   if (getYear (dstrTerminationDate) - getYear (dstrInceptionDate) != dTerminationAge)
   {
      ADDCONDITIONFROMFILE(CND::ERR_INVALID_TERMINATION_DATE);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RESPTransferList::validateBeneficiaryEffectiveDate (const DString &dstrTradeDate, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateBeneficiaryEffectiveDate" ) );

   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
   iter.begin();

   while (!iter.end())
   {
      RESPTransfer *pRESPTransfer = dynamic_cast<RESPTransfer*>(iter.getObject());

      DString dstrEffectiveDate;

      pRESPTransfer->getField( ifds::BenefEffectiveDate, dstrEffectiveDate, idDataGroup );

      if (DSTCommonFunctions::CompareDates (dstrTradeDate, dstrEffectiveDate) == DSTCommonFunctions::FIRST_EARLIER)
      {
         DString idiStr = I_("");
         DString dstrBenName;

         pRESPTransfer->getField( ifds::RESPBenefIDFrom, dstrBenName, idDataGroup, true );
         addIDITagValue (idiStr, BENEF_NAME, dstrBenName );

         ADDCONDITIONFROMFILEIDI (CND::ERR_BENEFICIARY_NOT_EFFECTIVE, idiStr);
         break;
      }
      ++iter;
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RESPTransferList::getBeneficiaryMasterList (DString &beneficiaryList, 
                                                     const DString &accountNum,
                                                     const BFDataGroupId &idDataGroup,
                                                     bool bFromAccount)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMasterList" ) );   	

   if (bFromAccount && !m_FromBeneficiaryList.empty ())
   {
      beneficiaryList = m_FromBeneficiaryList;
      return GETCURRENTHIGHESTSEVERITY();
   }
   else if (!bFromAccount && !m_ToBeneficiaryList.empty ())
   {
      beneficiaryList = m_ToBeneficiaryList;
      return GETCURRENTHIGHESTSEVERITY();
   }

   DString dstrBenefList;

   AccountEntityXref *pAccountEntityXref = NULL;
   if (getWorkSession().getAccountEntityXref (idDataGroup, pAccountEntityXref) <= WARNING && pAccountEntityXref)
   {

      ENTITIES_VECTOR respBeneficiaryEntities;

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

            dstrBenefList += dstrEntityId + I_("=") + dstrFirstName + I_(" ") + dstrLastName+ I_(";");
         }
      }
   }

   beneficiaryList = dstrBenefList;

   if (bFromAccount)
      m_FromBeneficiaryList = beneficiaryList; 
   else
      m_ToBeneficiaryList = beneficiaryList; 

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool RESPTransferList::isInternalTransfer (const BFDataGroupId &idDataGroup)
{
   DString depositType;
   DString redCode;

   getField (ifds::DepositType, depositType, idDataGroup, false);
   getField (ifds::RedCode, redCode, idDataGroup, false);

   bool bRespToResp = (depositType == DEP_CODE17 && (redCode == RED_CODE64 || redCode == RED_CODE65)) ? true : false;

   return bRespToResp;
}

//******************************************************************************
bool RESPTransferList::isPurchaseLikeTransfer (const BFDataGroupId &idDataGroup)
{
   DString depositType;
   DString redCode;

   getField (ifds::DepositType, depositType, idDataGroup, false);
   getField (ifds::RedCode, redCode, idDataGroup, false);

   bool bPurchaseLike = (depositType == DEP_CODE17 && !(redCode == RED_CODE64 || redCode == RED_CODE65)) ? true : false;

   return bPurchaseLike;
}

//******************************************************************************
SEVERITY RESPTransferList::getRESPEntityInfo ( const DString dstrEntityId, 
                                              const BFDataGroupId &idDataGroup, 
                                              const DString& dstrAccountNum,
                                              DString& dstrEffectiveDate)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getRESPEntityInfo" ) );

   AccountEntityXref *pAccountEntityXref = NULL;

   if (getWorkSession().getAccountEntityXref (idDataGroup, pAccountEntityXref) <= WARNING && pAccountEntityXref)
   {

      DString dstrBenefDofBirth;
      DString dstrHRDCRelateCode;
      DString dstrTaxJuris;
      DString dstrRESPAllocPrcnt;

      pAccountEntityXref->GetRESPEntityInfo (dstrAccountNum, idDataGroup, dstrEntityId,
                                             dstrRESPAllocPrcnt, dstrBenefDofBirth, dstrHRDCRelateCode,
                                             dstrTaxJuris, dstrEffectiveDate);	
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RESPTransferList::getRESPEntityInfo(const DString dstrEntityId, 
                                             const BFDataGroupId &idDataGroup, 
                                             const DString& dstrAccountNum,
                                             DString& dstrEffectiveDate,
                                             DString& dstrRESPAllocPrcnt,
                                             DString& dstrTaxJuris,
                                             DString& dstrHRDCRelateCode,
                                             DString& dstrBenefDofBirth)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getRESPEntityInfo" ) );

   AccountEntityXref *pAccountEntityXref = NULL;

   if (getWorkSession().getAccountEntityXref (idDataGroup, pAccountEntityXref) <= WARNING && pAccountEntityXref)
   {

      pAccountEntityXref->GetRESPEntityInfo (dstrAccountNum, idDataGroup, dstrEntityId,
                                             dstrRESPAllocPrcnt, dstrBenefDofBirth, dstrHRDCRelateCode,
                                             dstrTaxJuris, dstrEffectiveDate);	
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RESPTransferList::getEntitySeqNumber (const DString dstrEntityId, 
                                               const DString dstrAccountNum,
                                               const BFDataGroupId &idDataGroup, 
                                               DString& dstrSeqNumber)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getEntitySeqNumber" ) );

   AccountEntityXref *pAccountEntityXref = NULL;

   if (getWorkSession().getAccountEntityXref (idDataGroup, pAccountEntityXref) <= WARNING && pAccountEntityXref)
   { 
      pAccountEntityXref->GetEntitySeqNumber (idDataGroup, dstrAccountNum, dstrEntityId, dstrSeqNumber);	
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RESPTransferList::validateNumberOfBeneficiaries (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateNumberOfBeneficiaries" ) );   	

   DString depositType;
   DString redCode;
   DString transType;

   getField (ifds::DepositType, depositType, idDataGroup, false);
   getField (ifds::RedCode, redCode, idDataGroup, false);
   getField (ifds::TransType, transType, idDataGroup, false);

   bool bRespToResp = (depositType == DEP_CODE17 && (redCode == RED_CODE64 || redCode == RED_CODE65)) ? true : false;

   if (bRespToResp && DSTCommonFunctions::codeInList (transType, TRANSFER_LIKE))
   {
      BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );

      int nItems = iter.getNumberOfItemsInList();

      if (nItems == 1) // has account only
      {
         ADDCONDITIONFROMFILE (CND::ERR_RESP_BENEF_IS_MISSING);
      }
      else if (nItems > 2) // must have account + one beneficiary only
      {

         DString strIsInNonTrusteeTxfrPeriod(NULL_STRING);

         getField( ifds::IsInNonTrusteeTxfrPeriod ,strIsInNonTrusteeTxfrPeriod,idDataGroup,false );
         strIsInNonTrusteeTxfrPeriod.stripAll();
         bool bIsInNonTrusteeTxfrPeriod = strIsInNonTrusteeTxfrPeriod == YES? true:false;

         bool bIsNonTrusteeTxfr = (isNonTrustee(idDataGroup) && bIsInNonTrusteeTxfrPeriod);

         if ( !bIsNonTrusteeTxfr )
         {
            ADDCONDITIONFROMFILE (CND::ERR_ONE_RESP_BENEF_ALLOWED);
         }
      }
   }

   // if trans type is purchase like, has deposit code 17, and red code is not 64 or 65 
   // beneficiary should be mandatory.
   if (!bRespToResp && DSTCommonFunctions::codeInList (transType, PURCHASE_LIKE) && 
      depositType == I_("17"))
   {
      BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );

      int nItems = iter.getNumberOfItemsInList();

      if (nItems == 1) // has account only
      {
         ADDCONDITIONFROMFILE (CND::ERR_RESP_BENEF_IS_MISSING);
      }
   }

   DString dstrManualOverride;
   bool bIsRespTransformation = getWorkSession().isRESPTransformationClient ();

   getField (ifds::AcctLvlOverride, dstrManualOverride, idDataGroup, false);

   if (bIsRespTransformation && isManualOverrideApplicable(idDataGroup) && dstrManualOverride == YES)
   {
	   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );

	   int nItems = iter.getNumberOfItemsInList();

	   if (nItems == 1) // has account only
	   {
		   ADDCONDITIONFROMFILE (CND::ERR_RESP_BENEF_IS_MISSING);
	   }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//***********************************************************************************
SEVERITY RESPTransferList::doValidateField( const BFFieldId &idField,
                                            const DString &strValue,
                                            const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField"));

   if (idField == ifds::InceptionDate)
   {
      validateInceptionDate (strValue, idDataGroup);
   }
   else if (idField == ifds::TerminationDate)
   {
      validateTerminationDate (strValue, idDataGroup);
   }
   else if(idField == ifds::NEQ1)
   {
       DString dstrNEQ1;
      
      getField (ifds::NEQ1, dstrNEQ1, idDataGroup);
      if(dstrNEQ1 != I_("0"))
      {
         if(isAnyHistricalTxfr(idDataGroup))
         {
            ADDCONDITIONFROMFILE (CND::ERR_DEL_HIST_TXFR_BENEF_RECORD);  
            return GETCURRENTHIGHESTSEVERITY(); 
         }
      }
   }
   
   return GETCURRENTHIGHESTSEVERITY();
}  
//*****************************************************************************************
SEVERITY RESPTransferList::validateQESITotTxfr (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateQESITotTxfr"));
   
   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );

   RESPTransfer *pRESPTransfer;

   while (!iter.end())
   {
      pRESPTransfer = dynamic_cast<RESPTransfer*>(iter.getObject());

      if (pRESPTransfer)
      {
         pRESPTransfer->validateQESITotTxfr (idDataGroup);
      }
      ++iter;
   }
   
   return GETCURRENTHIGHESTSEVERITY();
}                                         
//***********************************************************************************
SEVERITY RESPTransferList::doRESPTransStatRelatedChanges(const BFDataGroupId& idDataGroup)
{ // for non-trustee, when change RESPTransStat, check all BENF record if QESITotTxfr BLNK
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doRESPTransStatRelatedChanges"));

   //ToDo: -- make new internal field for identify non-trusteetxfr
   DString strIsNonTrustee;
   getWorkSession ().getOption (ifds::IsNonTrustee, strIsNonTrustee, idDataGroup, false); //HistTxfr in GC
   bool bHistTxfr = strIsNonTrustee == YES;

   bool bIsNonTrustee = isNonTrustee(idDataGroup);

   bool bTradeYearApplicable = isInHistoricalRESPPeriod(idDataGroup);

   BFObjIter iter1( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );

   while( !iter1.end() )
   {
      RESPTransfer *pRESPTransfer = dynamic_cast<RESPTransfer *>(iter1.getObject());

      if( pRESPTransfer )
      {
         DString strRecordLevel;

         pRESPTransfer->getField (ifds::RecordLevel, strRecordLevel, idDataGroup, false);

         if(strRecordLevel == RECORD_LEVEL::BENEFICIARY)
         {
            pRESPTransfer->setFieldValid(ifds::TotTransfINDC, idDataGroup, false);

         }

      }
      ++iter1;
   }


   return GETCURRENTHIGHESTSEVERITY();
}
//***********************************************************************************
SEVERITY RESPTransferList::doNEQ1RelatedChanges(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doNEQ1RelatedChanges"));

   DString strIsNonTrustee(NULL_STRING);
   DString NEQ1(NULL_STRING);
   DString dstrRecordLevel(NULL_STRING);
   DString dstrTradeType(NULL_STRING);


   getWorkSession ().getOption (ifds::IsNonTrustee, strIsNonTrustee, idDataGroup, false);
   bool bIsNonTrusteeFunctionApplicable = strIsNonTrustee ==I_("Y")? true:false; 

   bool bIsInNonTrusteeTxfrPeriod = isInHistoricalRESPPeriod(idDataGroup);


   getField (ifds::NEQ1, NEQ1, idDataGroup, false);
   bool bIsNonTrustee = NEQ1 == I_("0")? true:false;



   RESPTransfer *pRESPTransfer = NULL;


   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
   iter.begin();

   while (!iter.end())
   {
      RESPTransfer *pRESPTransfer = dynamic_cast<RESPTransfer*>(iter.getObject());

      if( pRESPTransfer )
      {/*
       //For New trade, NEQ1 sent from Vew406 is BLANK
       //this fix Trade Entry ACCT LVL vew406 sends BLANK for new trade
       pRESPTransfer->getField (ifds::RecordLevel, dstrRecordLevel, idDataGroup, false);

       if(dstrRecordLevel == RECORD_LEVEL::ACCOUNT)
       {

       getField (ifds::TradeType, dstrTradeType, idDataGroup, false);
       if(dstrTradeType == NEW &&
       bIsInNonTrusteeTxfrPeriod &&
       bIsNonTrusteeFunctionApplicable &&
       (NEQ1 == I_("")))
       {
       bIsNonTrustee = true;

       }
       }
       */
         if( bIsNonTrustee &&  
            bIsInNonTrusteeTxfrPeriod && 
            bIsNonTrusteeFunctionApplicable )
         {
            pRESPTransfer->setFieldNoValidate( ifds::IsTotTransfINDCApplicable,I_("Y"),idDataGroup, false );
            //setFieldValid (ifds::TotTransfINDC, idDataGroup, false);
         }
         else
         {
            pRESPTransfer->setFieldNoValidate( ifds::IsTotTransfINDCApplicable,I_("N"), idDataGroup, false );
            //setFieldValid (ifds::TotTransfINDC, idDataGroup, true); 
         }

         pRESPTransfer->setFieldValid( ifds::IsTotTransfINDCApplicable, idDataGroup, true);
         pRESPTransfer->setFieldUpdated( ifds::IsTotTransfINDCApplicable, idDataGroup,false );
      }

      ++iter;
   }



   


   return GETCURRENTHIGHESTSEVERITY();
}

//***********************************************************************************
SEVERITY RESPTransferList::validateLeterAndStatus (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateLeterAndStatus" ) );   	

   DString dstrLetterReq;
   DString dstrTransStatus;

   getField (ifds::RESPLetter, dstrLetterReq, idDataGroup, false);
   getField (ifds::RESPTransStat, dstrTransStatus, idDataGroup, false);

   dstrLetterReq.stripAll ();
   dstrTransStatus.stripAll ();

   if (dstrLetterReq.empty ())
   {
      ADDCONDITIONFROMFILE (CND::ERR_RESP_LETTER_MISSING);
   }

   if (dstrTransStatus.empty ())
   {
      ADDCONDITIONFROMFILE (CND::ERR_RESP_INFOCOMPLETED_IS_MISSING);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//***********************************************************************************
SEVERITY RESPTransferList::validateAccountNotinalData (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAccountNotinalData" ) );   	

   if (isPurchaseLikeTransfer (idDataGroup))
   {
      RESPTransfer *pRESPAcctLevelTransfer;
      BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );

      while (!iter.end())
      {
         pRESPAcctLevelTransfer = dynamic_cast<RESPTransfer*>(iter.getObject());

         if (pRESPAcctLevelTransfer)
         {
            DString dstrRecordLevel;

            pRESPAcctLevelTransfer->getField (ifds::RecordLevel, dstrRecordLevel, idDataGroup);

            if (dstrRecordLevel == RECORD_LEVEL::ACCOUNT)
               break;
         }
         ++iter;
      }

      if (pRESPAcctLevelTransfer)
      {
         std::vector<BFFieldId> fields;

         // federal:
         fields.push_back (ifds::YTDContr);
         fields.push_back (ifds::TDContr);
         fields.push_back (ifds::GrantAmount);
         fields.push_back (ifds::AdditionalGrant);
         fields.push_back (ifds::CLBAmount);
         fields.push_back (ifds::PGrantAmount);
         fields.push_back (ifds::TDRedContrib);
         fields.push_back (ifds::TDRedEarning);
         fields.push_back (ifds::RedCESG);
         fields.push_back (ifds::RedCLB);
         fields.push_back (ifds::RedPGrant);
         fields.push_back (ifds::UCAmt);
         fields.push_back (ifds::ACAmt);
         fields.push_back (ifds::Pre98ContribAmt);
         fields.push_back (ifds::Pre98RedContribAmt);
         fields.push_back (ifds::CESGPaid);//P0185010.FN02.R01.02 - CESG Grant paid

         // qesi:
         /*	fields.push_back (ifds::QESIUCAmount);
         fields.push_back (ifds::QESIACAmount);
         fields.push_back (ifds::QESIYTDContribution);
         fields.push_back (ifds::QESIBasicGrant);
         fields.push_back (ifds::QESIIncreaseAmt);
         fields.push_back (ifds::Pre98QESIContrib);
         fields.push_back (ifds::Pre2007QESIContrib);*/

         std::vector<BFFieldId>::iterator iter = fields.begin();

         bool bFound = false;

         for ( ; iter != fields.end(); ++iter ) 
         {
            BFFieldId idField = *iter;
            DString dstrValue = NULL_STRING;

            pRESPAcctLevelTransfer->getField (idField, dstrValue, idDataGroup);

            dstrValue.stripAll ('0');
            dstrValue.stripAll ('.');

            if (!dstrValue.empty ())
            {
               bFound = true;
               break;
            }
         }

         if (!bFound)
            ADDCONDITIONFROMFILE (CND::WARN_ACCOUNT_NOTINALS_ARE_ZERO);
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//***********************************************************************************
SEVERITY RESPTransferList::validatePlansAndContracts (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validatePlansAndContracts" ) );

   DString dstrFromPlan;
   DString dstrToPlan;
   DString dstrFromContractId;
   DString dstrToContractId;

   getField (ifds::FromPlanNum, dstrFromPlan, idDataGroup, false);
   getField (ifds::ToPlanNum, dstrToPlan, idDataGroup, false);
   getField (ifds::FromContractId, dstrFromContractId, idDataGroup, false);
   getField (ifds::ToContractId, dstrToContractId, idDataGroup, false);

   dstrFromPlan.stripAll ();
   dstrToPlan.stripAll ();
   dstrFromContractId.stripAll ();
   dstrToContractId.stripAll ();

   if (dstrFromPlan.empty () || dstrToPlan.empty ())
   {
      ADDCONDITIONFROMFILE (CND::ERR_INVALID_RESP_PLAN);
   }

   if (dstrFromContractId.empty () || dstrToContractId.empty ())
   {
      ADDCONDITIONFROMFILE (CND::ERR_INVALID_RESP_CONTRACTIDS);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************
SEVERITY RESPTransferList::doValidateAll (const BFDataGroupId &idDataGroup, 
                                          long lValidateGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll"));

   displayRespToRespWarning (idDataGroup);

   validateAccountCLBGrant (idDataGroup);

   validateNumberOfBeneficiaries (idDataGroup);

   validateFromToBeneficiary (idDataGroup);
   
   validateContribYear(idDataGroup);

   DString dstrInceptionDate;

   getField (ifds::InceptionDate, dstrInceptionDate, idDataGroup, false);
   validateInceptionDate (dstrInceptionDate, idDataGroup);

   DString dstrTerminationDate;
   getField (ifds::TerminationDate, dstrTerminationDate, idDataGroup, false);
   validateTerminationDate (dstrTerminationDate, idDataGroup);

   validatePlansAndContracts (idDataGroup);

   validateLeterAndStatus (idDataGroup);
   
//   validateQESITotTxfr(idDataGroup);

   validateAccountNotinalData (idDataGroup);
   
   validateRESPInfoUpdate(idDataGroup);

   validateAccountLTDAmt (idDataGroup);

   validateAccountQESIPreFeb2007Amt (idDataGroup);

   validateTransferUpdate (idDataGroup);

   checkDuplicate (idDataGroup);    

   validateBeneficiaries (idDataGroup);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RESPTransferList::totalGrants (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "totalGrants" ) );   	

   DString dstrAcctLvlOverride;

   getField (ifds::AcctLvlOverride, dstrAcctLvlOverride, idDataGroup, false);

   bool bIsRespTransformation = getWorkSession().isRESPTransformationClient ();

   if (!bIsRespTransformation && dstrAcctLvlOverride == YES)
      return GETCURRENTHIGHESTSEVERITY();

   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );

   int nItems = iter.getNumberOfItemsInList();

   if (nItems == 0)
      return GETCURRENTHIGHESTSEVERITY();

   RESPTransfer *pRESPAcctLevelTransfer;

   while (!iter.end())
   {
      pRESPAcctLevelTransfer = dynamic_cast<RESPTransfer*>(iter.getObject());

      if (pRESPAcctLevelTransfer)
      {
         DString dstrRecordLevel;

         pRESPAcctLevelTransfer->getField (ifds::RecordLevel, dstrRecordLevel, idDataGroup);

         if (dstrRecordLevel == RECORD_LEVEL::ACCOUNT)
            break;
      }
      ++iter;
   }

   std::vector<BFFieldId> fields;

   // federal:
   fields.push_back (ifds::YTDContr);				// deprecated in RESP Transformation
   fields.push_back (ifds::TDRedEarning);			// deprecated in RESP Transformation 
   fields.push_back (ifds::TDContr);				// Life to Date Contribution
   fields.push_back (ifds::TDRedContrib);
   fields.push_back (ifds::Pre98ContribAmt);		// Pre-1998 Contribution
   fields.push_back (ifds::Pre98RedContribAmt);
   fields.push_back (ifds::UCAmt);					// CESG Unassisted
   fields.push_back (ifds::UCRedAmt);
   fields.push_back (ifds::ACAmt);					// CESG Assisted
   fields.push_back (ifds::ACRedAmt);
   fields.push_back (ifds::GrantAmount);			// CESG	
   fields.push_back (ifds::RedCESG);
   fields.push_back (ifds::AdditionalGrant);		// Additional CESG
   fields.push_back (ifds::RedAdditionalGrant);
   fields.push_back (ifds::CLBAmount);				// CLB
   fields.push_back (ifds::RedCLB);
   fields.push_back (ifds::PGrantAmount);			// ACES
   fields.push_back (ifds::RedPGrant);              
   fields.push_back (ifds::CESGPaid);				// CESG By Other Institution
   
   // qesi:
   fields.push_back (ifds::QESIUCAmount);			// QESI Unassisted
   fields.push_back (ifds::QESIRedUCAmt); 
   fields.push_back (ifds::QESIACAmount);			// QESI Assisted  	
   fields.push_back (ifds::QESIRedACAmt);
   fields.push_back (ifds::QESIYTDContribution);	// QESI YTD  
   fields.push_back (ifds::QESIRedYTDContrib);
   fields.push_back (ifds::QESIBasicGrant);			// QESI Basic
   fields.push_back (ifds::QESIRedBasic);
   fields.push_back (ifds::QESIIncreaseAmt);		// QESI Increase
   fields.push_back (ifds::QESIRedIncrease);    
   fields.push_back (ifds::Pre2007QESIContrib);		// QESI Pre-Feb 21, 2007
   fields.push_back (ifds::Pre2007QESIRedContrib);
   fields.push_back (ifds::QESIPaid);				// QESI By Other Institution
   fields.push_back (ifds::Pre98QESIContrib);		// deprecated in RESP Transformation
     
   // sages:
   fields.push_back (ifds::SAGESGrant);				// SAGES
   fields.push_back (ifds::RedSAGES);
   fields.push_back (ifds::SAGESUCAmount);			// SAGES Unassisted
   fields.push_back (ifds::SAGESRedUCAmt);
   fields.push_back (ifds::SAGESACAmount);   		// SAGES Assisted	
   fields.push_back (ifds::SAGESRedACAmt);
   
   //bctesg:
   fields.push_back (ifds::BCTESGGrant);
   fields.push_back (ifds::RedBCTESG);  
   						
   if (pRESPAcctLevelTransfer)
   {
      std::vector<BFFieldId>::iterator iter = fields.begin();

      for ( ; iter != fields.end(); ++iter ) 
      {
         BFFieldId idField = *iter;
         DString dstrGrantTotal = NULL_STRING;

         grantTotal (idField, idDataGroup, dstrGrantTotal);
         pRESPAcctLevelTransfer->setField (idField, dstrGrantTotal, idDataGroup);
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RESPTransferList::grantTotal (const BFFieldId &idField,
                                       const BFDataGroupId &idDataGroup,
                                       DString &dstrGrantTotal)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "grantTotal" ) );

   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
   iter.begin();
   double dGrantTotal = 0;

   while (!iter.end())
   {
      RESPTransfer *pRESPTransfer = dynamic_cast<RESPTransfer*>(iter.getObject());

      if (pRESPTransfer)
      {
         DString dstrGrant;
         DString dstrRecordType;

         pRESPTransfer->getField (idField, dstrGrant, idDataGroup);
         pRESPTransfer->getField (ifds::RecordLevel, dstrRecordType, idDataGroup);

         if (dstrRecordType == RECORD_LEVEL::ACCOUNT)
         {
            ++iter;
            continue;
         }

         I_CHAR *sGrant;
         double dGrant = wcstod (dstrGrant.c_str(), &sGrant); 
         //Sum only current trade year
         DString strCurrTradeYear(NULL_STRING),
            strHistNonTrustYear (NULL_STRING);
             
         getTradeYear (strCurrTradeYear, idDataGroup);
         pRESPTransfer->getField (ifds::HistNonTrustYear, strHistNonTrustYear, idDataGroup);
         strCurrTradeYear.stripAll();
         strHistNonTrustYear.stripAll();
         if (strCurrTradeYear != strHistNonTrustYear && idField == ifds::QESIYTDContribution)
         {
            ;//do not sum up the YTD contriutions
         }
         else
         {
            dGrantTotal += dGrant;
         }                                                      
      }
      ++iter;
   }

   dstrGrantTotal = DSTCommonFunctions::doubleToDString (idField, dGrantTotal);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RESPTransferList::displayRespToRespWarning (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "displayRespToRespWarning" ) );

   DString depositType;
   DString redCode;

   getField (ifds::DepositType, depositType, idDataGroup, false);
   getField (ifds::RedCode, redCode, idDataGroup, false);

   bool bRespToResp = (depositType == DEP_CODE17 && (redCode == RED_CODE64 || redCode == RED_CODE65)) ? true : false;

   if (bRespToResp)
      ADDCONDITIONFROMFILE (CND::WARN_RESP_TRANSFER_OUT);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RESPTransferList::setAccountCLBGrant (const BFDataGroupId &idDataGroup, bool bSetValue)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setAccountCLBGrant" ) );

   DString depositType;
   DString redCode;

   getField (ifds::DepositType, depositType, idDataGroup, false);
   getField (ifds::RedCode, redCode, idDataGroup, false);

   bool bRespToResp = (depositType == DEP_CODE17 && (redCode == RED_CODE64 || redCode == RED_CODE65)) ? true : false;

   if (!bRespToResp)
      return GETCURRENTHIGHESTSEVERITY();

   ErrMsgRulesList* pErrMsgRulesList = NULL;
   DString dstrCSSStopSINMatch;

   getWorkSession ().getMgmtCo().getErrMsgRulesList( pErrMsgRulesList );
   getWorkSession ().getOption (ifds::CSSStopSINMatch, dstrCSSStopSINMatch, idDataGroup, false);

   if (pErrMsgRulesList)
   {
      DString strErrValue;
      pErrMsgRulesList->getEWIValue (IFASTERR::CLB_AMOUNT_CANNOT_BE_TRANSFERED, idDataGroup, strErrValue );

      strErrValue.strip().upperCase();

      if (strErrValue == I_("E") && dstrCSSStopSINMatch == I_("Y"))
      {
         RESPTransfer *pAcctRESPTransfer = NULL;
         RESPTransfer *pBenefRESPTransfer = NULL;

         BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
         iter.begin();

         while (!iter.end())
         {
            RESPTransfer *pRESPTransfer = dynamic_cast<RESPTransfer*>(iter.getObject());

            if (pRESPTransfer)
            {
               DString dstrRecordLevel;
               pRESPTransfer->getField (ifds::RecordLevel, dstrRecordLevel, idDataGroup);

               if (dstrRecordLevel == RECORD_LEVEL::ACCOUNT)
                  pAcctRESPTransfer = pRESPTransfer;
               else
                  pBenefRESPTransfer = pRESPTransfer;
            }
            ++iter;
         }

		 if (pBenefRESPTransfer && pAcctRESPTransfer)
		 {
			 bool bSameSIN = false;

			 DString dstrBeneficiaryFrom, dstrBeneficiaryTo;

			 pBenefRESPTransfer->getField (ifds::RESPBenefIDFrom, dstrBeneficiaryFrom, idDataGroup);
			 pBenefRESPTransfer->getField (ifds::RESPBenefIDTo, dstrBeneficiaryTo, idDataGroup);
			 dstrBeneficiaryFrom.stripLeading ('0');
			 dstrBeneficiaryTo.stripLeading ('0');

			 if (!(dstrBeneficiaryFrom.empty() || dstrBeneficiaryTo.empty()))
			 {									
				 pBenefRESPTransfer->isSameSIN (idDataGroup, bSameSIN);

				 if (!bSameSIN && bSetValue)
				 {
					 pAcctRESPTransfer->setFieldNoValidate (ifds::CLBAmount, I_("0"), idDataGroup);
				 }

				 DString dstrAcctCLBAmount;

				 pAcctRESPTransfer->getField (ifds::CLBAmount, dstrAcctCLBAmount, idDataGroup, false);

				 dstrAcctCLBAmount.stripLeading ('0');

				 if (dstrAcctCLBAmount.empty ())
					 pAcctRESPTransfer->setFieldReadOnly (ifds::CLBAmount, idDataGroup, !bSameSIN);
			 }
		 }
	  }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RESPTransferList::setAccountCLBAmounts (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setAccountCLBAmounts" ));

	BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
	iter.begin();

	while (!iter.end())
	{
		RESPTransfer *pRESPTransfer = dynamic_cast<RESPTransfer*>(iter.getObject());

		if (pRESPTransfer)
		{
			DString dstrRecordLevel;
			pRESPTransfer->getField (ifds::RecordLevel, dstrRecordLevel, idDataGroup);

			if (dstrRecordLevel == RECORD_LEVEL::ACCOUNT)
			{
				pRESPTransfer->setFieldNoValidate (ifds::CLBAmount, I_("0"), idDataGroup);
				pRESPTransfer->setFieldNoValidate (ifds::RedCLB, I_("0"), idDataGroup);			
				break;	
			}
		}
		++iter;
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RESPTransferList::validateAccountCLBGrant (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAccountCLBGrant" ) );

   DString depositType, redCode, transType;

   getField (ifds::DepositType, depositType, idDataGroup, false);
   getField (ifds::RedCode, redCode, idDataGroup, false);   

   bool bRespToResp = (depositType == DEP_CODE17 && (redCode == RED_CODE64 || redCode == RED_CODE65)) ? true : false;

   if (!bRespToResp)
      return GETCURRENTHIGHESTSEVERITY();


   RESPTransfer *pAcctRESPTransfer = NULL;
   RESPTransfer *pBenefRESPTransfer = NULL;

   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
   iter.begin();

   while (!iter.end())
   {
      RESPTransfer *pRESPTransfer = dynamic_cast<RESPTransfer*>(iter.getObject());

      if (pRESPTransfer)
      {
         DString dstrRecordLevel;
         pRESPTransfer->getField (ifds::RecordLevel, dstrRecordLevel, idDataGroup);

         if (dstrRecordLevel == RECORD_LEVEL::ACCOUNT)
            pAcctRESPTransfer = pRESPTransfer;
         else
            pBenefRESPTransfer = pRESPTransfer;
      }
      ++iter;
   }

   if (pBenefRESPTransfer && pAcctRESPTransfer)
   {
      bool bSameSIN = false;
      DString dstrAcctCLBAmount;

      pBenefRESPTransfer->isSameSIN (idDataGroup, bSameSIN);

      pAcctRESPTransfer->getField (ifds::CLBAmount, dstrAcctCLBAmount, idDataGroup, false);
      dstrAcctCLBAmount.stripLeading ('0');

      if (!bSameSIN && !dstrAcctCLBAmount.empty ())
      {
         getErrMsg (IFASTERR::CLB_AMOUNT_CANNOT_BE_TRANSFERED, 
                    CND::ERR_CLB_AMOUNT_CANNOT_BE_TRANSFERED, 
                    CND::WARN_CLB_AMOUNT_CANNOT_BE_TRANSFERED, 
                    idDataGroup);

      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
inline int RESPTransferList::getYear (const DString &strDate)
{
   int year = 0;
   DString strTemp (strDate);
   BFDate date (strDate, BFDate::DF_DDATE_DEPRECATED);   
   
   if (!strTemp.strip ().empty ())
   {
      year = date.getYear ();
   }
   return year;
}

//***********************************************************************************
bool RESPTransferList::isRESPRelatedFieldsUpdated (const BFDataGroupId &idDataGroup)
{
   // check fields updated at Account Level
   if( isFieldUpdated (ifds::NEQ1, idDataGroup) ||
       isFieldUpdated (ifds::NEQ2, idDataGroup) ||
       isFieldUpdated (ifds::FromContractId, idDataGroup) ||
       isFieldUpdated (ifds::ToContractId, idDataGroup) ||
       isFieldUpdated (ifds::FromPlanNum, idDataGroup) ||
       isFieldUpdated (ifds::ToPlanNum, idDataGroup) )
   {
      return true;
   }       

   return false;
}

//*************************************************************************************************
SEVERITY RESPTransferList::validateRESPInfoUpdate ( const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateRESPInfoUpdate"));
   
   RESPTransferList *pRESPTransferList = dynamic_cast<RESPTransferList*>( this );

   if (pRESPTransferList)
   {
      DString dstrTradeType;
      pRESPTransferList->getField(ifds::TradeType, dstrTradeType, idDataGroup, false);
      dstrTradeType.strip();
      
      if(dstrTradeType == PROCESSED)
      {
         DString dstrAccountNum, dstrTransId, dstrBenefIdList, dstrTmpBenefId;
         pRESPTransferList->getField(ifds::AccountNum, dstrAccountNum, idDataGroup, false);
         pRESPTransferList->getField(ifds::TransId, dstrTransId, idDataGroup, false);
         
         bool bFirstBenef = true;
         bool bViewCall = false;
         if(isRESPRelatedFieldsUpdated(idDataGroup))
         {
            // account fields updated, send benef = 0;
            dstrBenefIdList = I_("0");
            bFirstBenef = false;
            bViewCall = true;
         }
         // check benef level fields updated
         // get benef allocation
         RESPTransfer *pRESPTransfer = NULL;
         BFObjIter iter( *pRESPTransferList, 
                         idDataGroup, 
                         true, 
                         BFObjIter::ITERTYPE::NON_DELETED );

         iter.begin();
         bool bFirst = true;
         while(!iter.end())
         {
            pRESPTransfer = dynamic_cast <RESPTransfer*> (iter.getObject());
            DString dstrRecordLevel;
            pRESPTransfer->getField (ifds::RecordLevel, dstrRecordLevel, idDataGroup);
            
            if( pRESPTransfer->isUpdatedForDataGroup (idDataGroup, false) &&
               (!pRESPTransfer->isNew()) &&
                pRESPTransfer->isRESPRelatedFieldsUpdated(idDataGroup) &&
                dstrRecordLevel == RECORD_LEVEL::BENEFICIARY)
            {
               pRESPTransfer->getField(ifds::RESPBenefIDFrom, dstrTmpBenefId, idDataGroup, false); 
               
               if(!bFirstBenef)
               {
                  dstrBenefIdList += I_(",") + dstrTmpBenefId.stripLeading('0');   
               }
               else
               {
                  // first benef in list
                  dstrBenefIdList = dstrTmpBenefId.stripLeading('0'); 
                  bFirstBenef = false;  
                  bViewCall = true;
               }
            }
            ++iter;
         }

         if(bViewCall)
         {
            RESPInfoUpdateValidationList *pRESPInfoUpdateValidationList = NULL;     

            pRESPInfoUpdateValidationList = new RESPInfoUpdateValidationList (*this);
            if ( pRESPInfoUpdateValidationList->init ( dstrAccountNum,
                                                       dstrTransId,
                                                       NULL_STRING,
                                                       NO,
                                                       I_("RESPTFR"),
                                                       dstrBenefIdList,
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
                     getErrMsg ( dstrWarnCode,
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
      }
   }
   return GETCURRENTHIGHESTSEVERITY (); 
}

//******************************************************************************
inline void RESPTransferList::getTradeYear (DString &dstrTradeYear, 
                                         const BFDataGroupId &idDataGroup)
{
   DString dstrTradeDate;

   getField (ifds::EffectiveDate, dstrTradeDate, idDataGroup);

   int year_pos = DSTCommonFunctions::getYearPosition();
   dstrTradeYear.assign(dstrTradeDate,year_pos,4);
}

//************************************************************************************
bool RESPTransferList::isNonTrustee(const BFDataGroupId &idDataGroup)
{
   bool ret=false;

   DString dstrNEQ1(NULL_STRING);

   getField(ifds::NEQ1, dstrNEQ1, idDataGroup, false);
   dstrNEQ1.stripAll().upperCase();

   if(dstrNEQ1 == I_( "0" ))
   {
      ret = true;
   }

   return ret;
}

//************************************************************************************
bool RESPTransferList::isAnyRESPBenefQCResident(const BFDataGroupId &idDataGroup)
{
   bool ret(false);
   DString dstrRESPQCResidentFound(NULL_STRING);
   DString dstrAccountNum(NULL_STRING);

   getField (ifds::AccountNum, dstrAccountNum, idDataGroup, false);

   MFAccount *pMFAccount (NULL);


   if (getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING && pMFAccount)
   {
      pMFAccount->getField( ifds::RESPQCResidentFound, dstrRESPQCResidentFound, idDataGroup, false);
   }


   dstrRESPQCResidentFound.stripAll().upperCase();
   if(dstrRESPQCResidentFound == I_("Y"))
      ret = true;

   return ret;
}

//******************************************************************************
SEVERITY RESPTransferList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if( doMoreRecordsExist() )
   {
      const DSTCSecurity* security = dynamic_cast<const DSTCSecurity *> ( getSecurity() );

      ReceiveData( DSTC_REQUEST::RESP_TRANSFER_INQUIRY, 
                   *_pRequestData, 
                   ifds::DSTC0406_VW, 
                   DSTCRequestor(getSecurity(), false));
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool RESPTransferList::isListOfNonTrusteeTrfx ( const BFDataGroupId &idDataGroup )
{
   RESPTransferList *pRESPTransferList = dynamic_cast<RESPTransferList*>( this );

   bool bResult = false;
   if (pRESPTransferList)
   {
      BFObjIter iter( *pRESPTransferList, 
                      idDataGroup, 
                      true, 
                      BFObjIter::ITERTYPE::NON_DELETED );

      iter.begin();
      while(!iter.end())
      {
         RESPTransfer* pRESPTransfer = dynamic_cast <RESPTransfer*> (iter.getObject());
         DString dstrRecordLevel;
         pRESPTransfer->getField (ifds::RecordLevel, dstrRecordLevel, idDataGroup);

         if ( dstrRecordLevel == RECORD_LEVEL::ACCOUNT )
         {
            DString dstrNEQ1(NULL_STRING);
            getField(ifds::NEQ1, dstrNEQ1, idDataGroup, false);
            dstrNEQ1.stripAll().upperCase();

            if(dstrNEQ1 == I_( "0" ) || dstrNEQ1.empty())
            {
               bResult = true;
            }
            break;
         }
         ++iter;
      }
   }

   return bResult;
}

//******************************************************************************
SEVERITY RESPTransferList::getUpdatedRecord(RESPTransferList *&pList, const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getUpdatedRecord" ) );

   DString strKey = I_("RESPTransferList_Updated"); 
   pList = dynamic_cast< RESPTransferList* >(getObject (strKey, idDataGroup));

   if( pList )
   {
      setObject (NULL, strKey, OBJ_ACTIVITY_NONE, idDataGroup);
      pList = NULL;
   }

   pList = new RESPTransferList((BFAbstractCBO&)(*this));

   DString strEffectiveDate,
      strAmount,
      strTransId,
      strAccountNum,
      strAccountTo,
      strCallType,
      strTradeType,
      strFromPlanNum,
      strToPlanNum,
      strInceptionDate,
      strNEQ1,
      strNEQ2,
      strFromContractId,
      strAcctLvlOverride,
      strToContractId,
      strTransType,
      strDepositType,
      strRedCode,
      strTerminationDate,
      strRESPLetter,
      strRESPTransStat;

   getField( ifds::EffectiveDate,     strEffectiveDate, idDataGroup, false);
   getField( ifds::Amount,            strAmount, idDataGroup, false);
   getField( ifds::TransId,           strTransId, idDataGroup, false);
   getField( ifds::AccountNum,        strAccountNum, idDataGroup, false);
   getField( ifds::AccountTo,         strAccountTo, idDataGroup, false);
   getField( ifds::CallType,          strCallType, idDataGroup, false);
   getField( ifds::TradeType,         strTradeType, idDataGroup, false);
   getField( ifds::FromPlanNum,       strFromPlanNum, idDataGroup, false);
   getField( ifds::ToPlanNum,         strToPlanNum, idDataGroup, false);
   getField( ifds::InceptionDate,     strInceptionDate, idDataGroup, false);
   getField( ifds::NEQ1,              strNEQ1, idDataGroup, false);
   getField( ifds::NEQ2,              strNEQ2, idDataGroup, false);
   getField( ifds::FromContractId,    strFromContractId, idDataGroup, false);
   getField( ifds::AcctLvlOverride,   strAcctLvlOverride, idDataGroup, false);
   getField( ifds::ToContractId,      strToContractId, idDataGroup, false);
   getField( ifds::TransType,         strTransType, idDataGroup, false);
   getField( ifds::DepositType,       strDepositType, idDataGroup, false);
   getField( ifds::RedCode,           strRedCode, idDataGroup, false);
   getField( ifds::TerminationDate,   strTerminationDate, idDataGroup, false);
   getField( ifds::RESPLetter,        strRESPLetter, idDataGroup, false);
   getField( ifds::RESPTransStat,     strRESPTransStat, idDataGroup, false);

   pList->setFieldNoValidate( ifds::EffectiveDate,     strEffectiveDate, idDataGroup, false);
   pList->setFieldNoValidate( ifds::Amount,            strAmount, idDataGroup, false);
   pList->setFieldNoValidate( ifds::TransId,           strTransId, idDataGroup, false);
   pList->setFieldNoValidate( ifds::AccountNum,        strAccountNum, idDataGroup, false);
   pList->setFieldNoValidate( ifds::AccountTo,         strAccountTo, idDataGroup, false);
   pList->setFieldNoValidate( ifds::CallType,          strCallType, idDataGroup, false);
   pList->setFieldNoValidate( ifds::TradeType,         strTradeType, idDataGroup, false);
   pList->setFieldNoValidate( ifds::FromPlanNum,       strFromPlanNum, idDataGroup, false);
   pList->setFieldNoValidate( ifds::ToPlanNum,         strToPlanNum, idDataGroup, false);
   pList->setFieldNoValidate( ifds::InceptionDate,     strInceptionDate, idDataGroup, false);
   pList->setFieldNoValidate( ifds::NEQ1,              strNEQ1, idDataGroup, false);
   pList->setFieldNoValidate( ifds::NEQ2,              strNEQ2, idDataGroup, false);
   pList->setFieldNoValidate( ifds::FromContractId,    strFromContractId, idDataGroup, false);
   pList->setFieldNoValidate( ifds::AcctLvlOverride,   strAcctLvlOverride, idDataGroup, false);
   pList->setFieldNoValidate( ifds::ToContractId,      strToContractId, idDataGroup, false);
   pList->setFieldNoValidate( ifds::TransType,         strTransType, idDataGroup, false);
   pList->setFieldNoValidate( ifds::DepositType,       strDepositType, idDataGroup, false);
   pList->setFieldNoValidate( ifds::RedCode,           strRedCode, idDataGroup, false);
   pList->setFieldNoValidate( ifds::TerminationDate,   strTerminationDate, idDataGroup, false);
   pList->setFieldNoValidate( ifds::RESPLetter,        strRESPLetter, idDataGroup, false);
   pList->setFieldNoValidate( ifds::RESPTransStat,     strRESPTransStat, idDataGroup, false);

   buildDataObject(pList,idDataGroup);

   setObject (pList, strKey, OBJ_ACTIVITY_NONE, idDataGroup);

   pList->setFieldNoValidate( ifds::CallType,          strCallType, idDataGroup, false);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void RESPTransferList::setOnlyUpdatedFlag(bool bOnlyUpdated)
{
   _bOnlyUpdated = bOnlyUpdated;
}

//******************************************************************************
SEVERITY RESPTransferList::buildDataObject(RESPTransferList *pList, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("buildDataObject"));

   BFObjIter iter( *this, 
                   idDataGroup, 
                   true, 
                   BFObjIter::ITERTYPE::NON_DELETED );

   RESPTransfer* pRESPTransfer;

   iter.begin();

   unsigned int iCurrentCounter = 0;
   while(!iter.end())
   {
      pRESPTransfer = dynamic_cast <RESPTransfer*> (iter.getObject());
      DString dstrRecordLevel;
      pRESPTransfer->getField (ifds::RecordLevel, dstrRecordLevel, idDataGroup);

      BF_OBJ_ACTIVITY lObjActivity = iter.getKey().getActivity();

      bool bAddRecord = false;
      if (dstrRecordLevel == RECORD_LEVEL::ACCOUNT)
      {
         bAddRecord = true;
      }
      else if( dstrRecordLevel == RECORD_LEVEL::BENEFICIARY && 
               ( pRESPTransfer->isUpdatedForDataGroup(idDataGroup)  || 
                 lObjActivity == OBJ_ACTIVITY_ADDED || 
                 lObjActivity == OBJ_ACTIVITY_DELETED ) )
      {
         // only modified one or deleted
         bAddRecord = true;
      }

      if ( bAddRecord )
      {
         BFData bfData(ifds::DSTC0406_VWRepeat_Record);
         pRESPTransfer->getData(bfData, idDataGroup);

         BFObjectKey objKey;

         DString dstrKey = DString::asString( ++iCurrentCounter ).padLeft( 10, '0' );

         BFCBO * pObj;
         pList->setOnlyUpdatedFlag(true);
         pList->doCreateNewObject( pObj, dstrKey, idDataGroup );
         objKey.setStringKey( dstrKey );

         if( lObjActivity != OBJ_ACTIVITY_ADDED && lObjActivity != OBJ_ACTIVITY_DELETED )
         {
            objKey.setActivity(OBJ_ACTIVITY_NONE);
         }
         else
         {
            objKey.setActivity(lObjActivity);
         }

         //for proc trade
         dynamic_cast<RESPTransfer*>(pObj)->initClone( const_cast<BFData&>(bfData),idDataGroup); 
         //pObj->setData(bfData,idDataGroup);
         pList->setObject( objKey, pObj );
         //proc trade, send update data
         {
            DString strQESIYTDContribution;
            pObj->getField( ifds::QESIYTDContribution, strQESIYTDContribution, idDataGroup, false );
         }

         // when  we need to check in, we may need to remove this line of code
         pList->clearConditionBeforeSubmission(MYFRAME(),
            CND::ERR_BENEFICIARY_NOT_EFFECTIVE );
      }
      ++iter;
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void RESPTransferList::clearConditionBeforeSubmission (Frame *pFrame, int conditionCode)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("clearCondition"));

   int count = pFrame->getCount();
   for (int i = 0; i < count; i++)
   {
      Condition *c = pFrame->getCondition(i);
      int condCode = c->getCode();

      if(condCode == conditionCode)
      {
         pFrame->clearCondition(i);
         break;
      }
   }
}

//******************************************************************************
SEVERITY RESPTransferList::isTotTransfINDCApplicable(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("isTotTransfINDCApplicable"));

   DString dstrTradeYear(NULL_STRING);
   getTradeYear(dstrTradeYear,idDataGroup);

   bool bTradeYearApplicable = dstrTradeYear == I_("2011")? true: false;
   bool bIsNonTrustee = isNonTrustee(idDataGroup);


   if(bIsNonTrustee && bTradeYearApplicable)
   {
      setFieldNoValidate (ifds::IsTotTransfINDCApplicable, I_("Y"), idDataGroup, false);
   }
   else
   {
      setFieldNoValidate (ifds::IsTotTransfINDCApplicable, I_("N"), idDataGroup, false);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool RESPTransferList::isInHistoricalRESPPeriod(const DString& strYear,const BFDataGroupId& idDataGroup)
{
   DString strStartHistYear;
   DString strStopHistYear;

   bool bResult = false;
   int year_pos = DSTCommonFunctions::getYearPosition();
   getWorkSession ().getOption (ifds::NonTrustStartDate, strStartHistYear, idDataGroup, false);
   getWorkSession ().getOption (ifds::NonTrustStopDate, strStopHistYear, idDataGroup, false);

   if( !strStopHistYear.empty() && !strStartHistYear.empty())
   {
      DString strTemp;
      strTemp.assign(strStartHistYear,year_pos,4);
      strStartHistYear = strTemp;
      strTemp.assign(strStopHistYear,year_pos,4);
      strStopHistYear = strTemp;

      unsigned long iYear = strYear.convertToULong();
      unsigned long iStartYear = strStartHistYear.convertToULong();
      unsigned long iStopYear = strStopHistYear.convertToULong();

      if ( iYear >= iStartYear && iYear <= iStopYear )
      {
         bResult = true;
      }
   }

   return bResult;
}

//******************************************************************************
SEVERITY RESPTransferList::setInNonTrusteeTxfrPeriod(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("setInNonTrusteeTxfrPeriod"));

   bool bIsInHistoricalRESPPeriod = isInHistoricalRESPPeriod(idDataGroup);

   if(bIsInHistoricalRESPPeriod)
   {
      setFieldNoValidate (ifds::IsInNonTrusteeTxfrPeriod, I_("Y"), idDataGroup, false);
   }
   else
   {
      setFieldNoValidate (ifds::IsInNonTrusteeTxfrPeriod, I_("N"), idDataGroup, false);
   }

   setFieldValid( ifds::IsInNonTrusteeTxfrPeriod, idDataGroup, true);
   setFieldUpdated( ifds::IsInNonTrusteeTxfrPeriod, idDataGroup,false );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RESPTransferList::doTransfINDCApplicable(bool bApplicable,const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doTransfINDCApplicable"));

   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
   iter.begin();

   while (!iter.end())
   {
      RESPTransfer* pRESPTransfer = dynamic_cast<RESPTransfer*>(iter.getObject());

      if (pRESPTransfer)
      {
         pRESPTransfer->setField( ifds::IsTotTransfINDCApplicable,
                                  bApplicable ? I_("Y") : I_("N"), 
                                 idDataGroup, false );
      }

      ++iter;
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool RESPTransferList::isInHistoricalRESPPeriod(const BFDataGroupId& idDataGroup)
{
   bool bIsInHistoricalRESPPeriod(false);
   DString strTradeDate(NULL_STRING),
      strStartHistDate,
      strStopHistDate;

   getField( ifds::EffectiveDate, strTradeDate, idDataGroup, false );
   getWorkSession ().getOption (ifds::NonTrustStartDate, strStartHistDate, idDataGroup, false);
   getWorkSession ().getOption (ifds::NonTrustStopDate, strStopHistDate, idDataGroup, false);
   
   return DSTCommonFunctions::IsDateBetween(strStartHistDate,strStopHistDate,strTradeDate);
}

//****************************************************************************** 
SEVERITY RESPTransferList::checkDuplicate ( const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "checkDuplicate" ) );
   
   BFObjIter iter1( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );

   while( !iter1.end() )
   {
      RESPTransfer *pRESPTransfer = dynamic_cast<RESPTransfer *>(iter1.getObject());

      if( pRESPTransfer )
      {
         checkDuplicate ( pRESPTransfer, idDataGroup );
      }
      ++iter1;
   }
   
   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************  
SEVERITY RESPTransferList::checkExistingBenf ( const RESPTransfer *pRESPTransferToCheck,
                                            const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "checkExistingBenf" ) );

   DString dstrEntityIdToCheck;
   bool bIsExistingBenf(false);

   pRESPTransferToCheck->getField (ifds::RESPBenefIDFrom, dstrEntityIdToCheck, idDataGroup);

   if(!dstrEntityIdToCheck.empty())
   {

      //check first whether in the list (in memory) we have a duplicate
      BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
      iter.begin();

      while (!iter.end())
      {
         RESPTransfer *pRESPTransfer = dynamic_cast<RESPTransfer*>(iter.getObject());
         // Don't check against itself
         if ( pRESPTransfer != pRESPTransferToCheck )
         {
            DString dstrCurrentEntityId;

            pRESPTransfer->getField( ifds::RESPBenefIDFrom, dstrCurrentEntityId, idDataGroup );
            //ToDo!!!: re-order EntityID
            if (dstrCurrentEntityId == dstrEntityIdToCheck )
            {
               bIsExistingBenf = true;
               break;
            }
         }

         ++iter;
      }

      if ( !bIsExistingBenf )
      {//Error msg: 1124, Not allow to add new BENEF for processed trade
         getErrMsg(IFASTERR::NON_ASSOCIATED_BENEF_IS_NOT_ALLOWED,
                   CND::ERR_NON_ASSOCIATED_BENEF_IS_NOT_ALLOWED, 
                   CND::WARN_NON_ASSOCIATED_BENEF_IS_NOT_ALLOWED,
                   idDataGroup); 
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************  
bool RESPTransferList::checkBenefExists ( const RESPTransfer *pRESPTransferToCheck,
                                          const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "checkBenefExists" ) );

   DString dstrEntityIdToCheck;
   bool bExist(false);

   pRESPTransferToCheck->getField (ifds::RESPBenefIDFrom, dstrEntityIdToCheck, idDataGroup);
   if(dstrEntityIdToCheck.empty())
   {//skip if BENEF have not been selected
      bExist = true;
   }
   else
   {
      //check first whether in the list (in memory) we have a duplicate
      BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
      iter.begin();

      while (!iter.end())
      {
         RESPTransfer *pRESPTransfer = dynamic_cast<RESPTransfer*>(iter.getObject());
         // Don't check against itself
         if ( pRESPTransfer != pRESPTransferToCheck )
         {
            DString dstrCurrentEntityId;

            pRESPTransfer->getField( ifds::RESPBenefIDFrom, dstrCurrentEntityId, idDataGroup );

            if (dstrCurrentEntityId == dstrEntityIdToCheck )
            {
               bExist = true;
               break;
            }

         }

         ++iter;

      }
   }

   return bExist;
}

//******************************************************************************
SEVERITY RESPTransferList::validateContribYear (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateContribYear" ) );

   if(!_bNonTrusteeContrib)//IN2672499 - RESP Transfer Information error message
      return GETCURRENTHIGHESTSEVERITY();

   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );

   RESPTransfer *pRESPTransfer;

   bool bHaveCurrTradeYear(false);
   DString strCurrTradeYear(NULL_STRING);
   
   getTradeYear(strCurrTradeYear, idDataGroup);
   strCurrTradeYear.stripAll();
   
   while (!iter.end())
   {
      pRESPTransfer = dynamic_cast<RESPTransfer*>(iter.getObject());

      if (pRESPTransfer)
      {
         DString strHistNonTrustYear(NULL_STRING);
         DString strRecordLevel(NULL_STRING);

         pRESPTransfer->getField (ifds::RecordLevel, strRecordLevel, idDataGroup, false);
         strRecordLevel.stripAll();
         pRESPTransfer->getField (ifds::HistNonTrustYear, strHistNonTrustYear, idDataGroup);
         strHistNonTrustYear.stripAll();

         if (strRecordLevel == RECORD_LEVEL::BENEFICIARY)
         {
            if(strCurrTradeYear == strHistNonTrustYear)
            {
               bHaveCurrTradeYear = true;
               break;
            }
         }
      }
      ++iter;
   }

   if(!bHaveCurrTradeYear)
   { // TODO: ERR_MSG: 1125, Must contain a trade of current year
      ADDCONDITIONFROMFILE (CND::ERR_BENEF_CURR_TAXYEAR_MANDATORY); 
   }

   return GETCURRENTHIGHESTSEVERITY();
}
//************************************************************************************
SEVERITY RESPTransferList::doDefaultWithBenefCurrTradeYear( const  RESPTransfer *pRESPTransferToCheck,
                                                            DString &strEligibleTransfer,
                                                            DString &strTotTransfINDC,
                                                            const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doDefaultWithBenefCurrTradeYear" ) ); 

   DString dstrEntityIdToCheck(NULL_STRING);
   DString dstrCurrTradeYear; 
   bool  bIsAnyBenefCurrTradeYearExist(false);

   getTradeYear(dstrCurrTradeYear, idDataGroup);

   pRESPTransferToCheck->getField (ifds::RESPBenefIDFrom, dstrEntityIdToCheck, idDataGroup);

   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
   iter.begin();

   while( !iter.end() )
   {
      RESPTransfer *pRESPTransfer = dynamic_cast<RESPTransfer *>(iter.getObject());

      if ( pRESPTransfer != pRESPTransferToCheck )
      {
         DString dstrCurrentEntityId;

         pRESPTransfer->getField( ifds::RESPBenefIDFrom, dstrCurrentEntityId, idDataGroup );

         if (dstrCurrentEntityId == dstrEntityIdToCheck )
         {
            DString dstrHistNonTrustYear(NULL_STRING);

            pRESPTransfer->getField (ifds::HistNonTrustYear, dstrHistNonTrustYear, idDataGroup);

            if(dstrHistNonTrustYear == dstrCurrTradeYear) 
            {
               pRESPTransfer->getField (ifds::EligibleTransfer, strEligibleTransfer, idDataGroup);
               pRESPTransfer->getField (ifds::TotTransfINDC, strTotTransfINDC, idDataGroup);

               break;
            }

         }
      }
      ++iter;
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool RESPTransferList::isAnyHistricalTxfr(const BFDataGroupId &idDataGroup)
{
   bool ret(false);

   BFObjIter iter1( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );

   while( !iter1.end() )
   {
      RESPTransfer *pRESPTransfer = dynamic_cast<RESPTransfer *>(iter1.getObject());

      if( pRESPTransfer )
      {
         if(checkContribution(pRESPTransfer,idDataGroup, false))
         {
            ret = true;
            break;
         }
      }

      ++iter1;
   }

   return ret;
}
//******************************************************************************
bool RESPTransferList::isAnyBenefCurrTradeYear(const BFDataGroupId &idDataGroup)
{
bool ret(false);
DString dstrCurrTradeYear; 

getTradeYear(dstrCurrTradeYear, idDataGroup);

BFObjIter iter1( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );

   while( !iter1.end() )
   {
      RESPTransfer *pRESPTransfer = dynamic_cast<RESPTransfer *>(iter1.getObject());

      if( pRESPTransfer )
      {
         DString histNonTrustYear(NULL_STRING);
         DString recordLevel(NULL_STRING);
         
         pRESPTransfer->getField (ifds::RecordLevel, recordLevel, idDataGroup, false);
         
         pRESPTransfer->getField( ifds::HistNonTrustYear, histNonTrustYear, idDataGroup );

         if(recordLevel == RECORD_LEVEL::BENEFICIARY)
         {

            if(dstrCurrTradeYear == histNonTrustYear)
            {
               DString eligibleTransfer(NULL_STRING);
               DString totTransfINDC(NULL_STRING);

               pRESPTransfer->getField( ifds::EligibleTransfer, eligibleTransfer, idDataGroup );
               pRESPTransfer->getField( ifds::TotTransfINDC, totTransfINDC, idDataGroup );

               if(eligibleTransfer == YES &&
                  totTransfINDC == I_("1"))
               {
                  ret = true;
                  break;
               }
            }
         }

      }
      ++iter1;
   }


return ret;
}
//******************************************************************************
bool RESPTransferList::setAnyBenefCurrTradeYear(const BFDataGroupId &idDataGroup)
{
   //Only for processed trade
   bool ret(false);
   DString strTradeType;
   DString strValueOut ;

   getField( ifds::TradeType, strTradeType, idDataGroup, false);

   if (strTradeType == PROCESSED )
   {
      ret = isAnyBenefCurrTradeYear(idDataGroup);
      strValueOut = ret? YES : NO;
   }
   else if (strTradeType == NEW)
   {
      strValueOut = YES;
   }
   else
   {
      strValueOut = NO;
   }

   setFieldNoValidate (ifds::AnyBenefCurrTradeYear, strValueOut, idDataGroup, false);
   setFieldValid( ifds::AnyBenefCurrTradeYear, idDataGroup, true);

   return ret;
}

//******************************************************************************
bool RESPTransferList::checkContribution ( const RESPTransfer *pRESPTransferToCheck,
                                          const BFDataGroupId &idDataGroup,
                                          bool bCheckCurrYearTrade /*false*/)
{
   //default check if historical trade year exists

   bool bCurrYearTrade(false);
   bool bHistYearTrade(false);
   bool ret(false);
   DString dstrEntityIdToCheck;
   DString dstrEffectiveDate;
   
   getField( ifds::EffectiveDate,     dstrEffectiveDate, idDataGroup, false);
   
   int nCurrentYear = DSTCommonFunctions::getYearFromUnFormattedDate(dstrEffectiveDate);


   pRESPTransferToCheck->getField (ifds::RESPBenefIDFrom, dstrEntityIdToCheck, idDataGroup);

   //check first whether in the list (in memory) we have a duplicate
   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
   iter.begin();

   while (!iter.end())
   {
      RESPTransfer *pRESPTransfer = dynamic_cast<RESPTransfer*>(iter.getObject());
      // Don't check against itself
      if ( pRESPTransfer != pRESPTransferToCheck )
      {
         DString dstrRecordLevel;
         pRESPTransfer->getField (ifds::RecordLevel, dstrRecordLevel, idDataGroup, false);

         if( dstrRecordLevel == RECORD_LEVEL::BENEFICIARY)
         {
            DString dstrCurrentEntityId;

            pRESPTransfer->getField( ifds::RESPBenefIDFrom, dstrCurrentEntityId, idDataGroup );

            if (dstrCurrentEntityId == dstrEntityIdToCheck )
            {
               DString dstrHistNonTrustYear(NULL_STRING);

               pRESPTransfer->getField (ifds::HistNonTrustYear, dstrHistNonTrustYear, idDataGroup);
               //int nTradeYear = DSTCommonFunctions::convertToDouble(dstrHistNonTrustYear);
               int nTradeYear = dstrHistNonTrustYear.asInteger();

               if(bCheckCurrYearTrade)
               {
                  if(nCurrentYear == nTradeYear)
                  {
                     bCurrYearTrade = true;
                     break;
                  }

               }
               else //check historical trade
               {
                  if(nCurrentYear > nTradeYear)
                  {
                     bHistYearTrade = true;
                     break;
                  }
               }
            }
         }
      }

      ++iter;
   }

   return ret = bCheckCurrYearTrade? bCurrYearTrade : bHistYearTrade;
}

//******************************************************************************
//IN2672499 - RESP Transfer Information error message
bool RESPTransferList:: isNonTrusteeContrib(const BFDataGroupId &idDataGroup)
{
   DString strIsNonTrustee;
   bool bNonTrusteeHistTxfr(false);

   bool bIsNonTrustee = isNonTrustee(idDataGroup);
   getWorkSession ().getOption (ifds::IsNonTrustee, strIsNonTrustee, idDataGroup, false); //HistTxfr in GC
   bool bHistTxfr = strIsNonTrustee == YES;
   bool bTradeYearApplicable = isInHistoricalRESPPeriod(idDataGroup);

   if(bIsNonTrustee && bHistTxfr && bTradeYearApplicable) 
   {
      bNonTrusteeHistTxfr = true;
   }

   return bNonTrusteeHistTxfr;
}

//******************************************************************************
bool RESPTransferList::isExternalTransferOut (const BFDataGroupId &idDataGroup)
{
	DString transType, redCode, depositType;

	getField (ifds::TransType, transType, idDataGroup, false);
	getField (ifds::RedCode, redCode, idDataGroup, false);
	getField (ifds::DepositType, depositType, idDataGroup, false);
	
	bool bExternalTransferOut = transType == REDEMPTION && (redCode == RED_CODE64 || redCode == RED_CODE65) ? true : false;
	bool bInternalTransferOut = transType == TRANSFER_OUT && (redCode == RED_CODE64 || redCode == RED_CODE65) ? true : false;
	bool bInKindTransferIn = transType == TRANSFER_IN && depositType == I_("17") && redCode == I_("01") ? true : false;

	return bExternalTransferOut || bInternalTransferOut || bInKindTransferIn;
}

//******************************************************************************
SEVERITY RESPTransferList::validateAccountLTDAmt (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAccountLTDAmt" ) );
     
   DString transType, depositType, redCode;
   getField (ifds::TransType, transType, idDataGroup, false);
   getField (ifds::DepositType, depositType, idDataGroup, false);
   getField (ifds::RedCode, redCode, idDataGroup);

   bool bIsRespTransformation = getWorkSession().isRESPTransformationClient ();

   if ( !(bIsRespTransformation /*&& ((transType == I_("ED") && depositType == I_("17")) || 
									(DSTCommonFunctions::codeInList(transType, I_("TR,TI")) && depositType == I_("17") && redCode == I_("01")))*/))
	   return GETCURRENTHIGHESTSEVERITY();

   BigDecimal bdZero = DSTCommonFunctions::convertToBigDecimal(I_("0.0"));
   BigDecimal bdPurLTDAmt(0), bdRedLTDAmt(0), bdPurPre98Amt(0), bdRedPre98Amt(0), bdCESGACAmt(0), bdCESGUCAmt(0), bdCESGACRedAmt(0), bdCESGUCRedAmt(0), bdLTDdiffAmt(0);
   DString dstPurLTDAmt, dstrRedLTDAmt, dstPurPre98Amt, dstrRedPre98Amt, dstrCESGACAmt, dstrCESGACRedAmt, dstrCESGUCAmt, dstrCESGUCRedAmt;

   RESPTransfer *pRESPTransfer = NULL;

   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
   iter.begin();

   while (!iter.end())
   {
      pRESPTransfer = dynamic_cast<RESPTransfer*>(iter.getObject());

      if (pRESPTransfer)
      {
         DString dstrRecordLevel;

         pRESPTransfer->getField (ifds::RecordLevel, dstrRecordLevel, idDataGroup, false);

		 if (dstrRecordLevel == RECORD_LEVEL::BENEFICIARY)
		 {
			 // Life to Date Contribution
			 pRESPTransfer->getField(ifds::TDContr, dstPurLTDAmt, idDataGroup, false);
			 pRESPTransfer->getField(ifds::TDRedContrib, dstrRedLTDAmt, idDataGroup, false);	
			 bdPurLTDAmt = bdPurLTDAmt + DSTCommonFunctions::convertToBigDecimal(dstPurLTDAmt.stripAll());
			 bdRedLTDAmt = bdRedLTDAmt + DSTCommonFunctions::convertToBigDecimal(dstrRedLTDAmt.stripAll());

			 // Pre-1998 Contribution	
			 pRESPTransfer->getField(ifds::Pre98ContribAmt, dstPurPre98Amt, idDataGroup, false);
			 pRESPTransfer->getField(ifds::Pre98RedContribAmt, dstrRedPre98Amt, idDataGroup, false);
			 bdPurPre98Amt = bdPurPre98Amt + DSTCommonFunctions::convertToBigDecimal(dstPurPre98Amt.stripAll());
			 bdRedPre98Amt = bdRedPre98Amt + DSTCommonFunctions::convertToBigDecimal(dstrRedPre98Amt.stripAll());	

			 // CESG Assisted, CESG Unassisted	
			 pRESPTransfer->getField(ifds::ACAmt, dstrCESGACAmt, idDataGroup, false);
			 pRESPTransfer->getField(ifds::ACRedAmt, dstrCESGACRedAmt, idDataGroup, false);
			 pRESPTransfer->getField(ifds::UCAmt, dstrCESGUCAmt, idDataGroup, false);
			 pRESPTransfer->getField(ifds::UCRedAmt, dstrCESGUCRedAmt, idDataGroup, false);
			 bdCESGACAmt = bdCESGACAmt + DSTCommonFunctions::convertToBigDecimal(dstrCESGACAmt.stripAll());
			 bdCESGACRedAmt = bdCESGACRedAmt + DSTCommonFunctions::convertToBigDecimal(dstrCESGACRedAmt.stripAll());
			 bdCESGUCAmt = bdCESGUCAmt + DSTCommonFunctions::convertToBigDecimal(dstrCESGUCAmt.stripAll());
			 bdCESGUCRedAmt = bdCESGUCRedAmt + DSTCommonFunctions::convertToBigDecimal(dstrCESGUCRedAmt.stripAll());

			 bdLTDdiffAmt = bdPurLTDAmt + bdRedLTDAmt - (bdPurPre98Amt + bdRedPre98Amt + bdCESGACAmt + bdCESGACRedAmt + bdCESGUCAmt + bdCESGUCRedAmt);
		 }
      }

      ++iter;
   }

   // ‘Net of LTD’ = ‘Net of Pre-1998’ + ‘Net of CESG AC' + ‘Net of CESG UC'.
   if ( pRESPTransfer && (bdLTDdiffAmt != bdZero) ) 
   {	
	   // 1786 - LTD Contribution must be equal to the total of Pre-1998 + CESG Assisted + CESG Unassisted amounts
	   getErrMsg( IFASTERR::LTD_CONTRIB_MUST_EQUAL_SUM_OF_PRE98_CESGAC_CESGUC, 	  
				  CND::ERR_LTD_CONTRIB_MUST_EQUAL_SUM_OF_PRE98_CESGAC_CESGUC, 		  
				  CND::WARN_LTD_CONTRIB_MUST_EQUAL_SUM_OF_PRE98_CESGAC_CESGUC, 	
				  idDataGroup); 
   }
   
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RESPTransferList::validateAccountQESIPreFeb2007Amt (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAccountQESIPreFeb2007Amt" ) );
     
   DString transType, depositType, redCode;
   getField (ifds::TransType, transType, idDataGroup, false);
   getField (ifds::DepositType, depositType, idDataGroup, false);
   getField (ifds::RedCode, redCode, idDataGroup);

   bool bIsRespTransformation = getWorkSession().isRESPTransformationClient();
   bool bIsQESIClient = getWorkSession().isQESIClient();	
   bool bIsAnyRESPBenefQCResident = isAnyRESPBenefQCResident(idDataGroup);

   if ( !(bIsRespTransformation && bIsQESIClient && bIsAnyRESPBenefQCResident 
							  /*&& ((transType == I_("ED") && depositType == I_("17")) || (DSTCommonFunctions::codeInList(transType, I_("TR,TI")) && depositType == I_("17") && redCode == I_("01")))*/))
	   return GETCURRENTHIGHESTSEVERITY();

   BigDecimal bdZero = DSTCommonFunctions::convertToBigDecimal(I_("0.0"));
   BigDecimal bdPurLTDAmt(0), bdRedLTDAmt(0), bdQESIACAmt(0), bdQESIRedACAmt(0), bdQESIUCAmt(0), bdQESIRedUCAmt(0), bdQESIYTDAmt(0), bdQESIRedYTDAmt(0), bdPre2007QESIContribAmt(0), bdDiffAmt(0);
   DString dstPurLTDAmt, dstrRedLTDAmt, dstrQESIACAmt, dstrQESIRedACAmt, dstrQESIUCAmt, dstrQESIRedUCAmt, dstrQESIYTDAmt, dstrQESIRedYTDAmt, dstrPre2007QESIContribAmt;

   RESPTransfer *pRESPTransfer = NULL;

   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
   iter.begin();

   while (!iter.end())
   {
      pRESPTransfer = dynamic_cast<RESPTransfer*>(iter.getObject());

      if (pRESPTransfer)
      {
         DString dstrRecordLevel;

         pRESPTransfer->getField (ifds::RecordLevel, dstrRecordLevel, idDataGroup, false);

		 if (dstrRecordLevel == RECORD_LEVEL::BENEFICIARY)
		 {			
			 // Life to Date Contribution
			 pRESPTransfer->getField(ifds::TDContr, dstPurLTDAmt, idDataGroup, false);
			 pRESPTransfer->getField(ifds::TDRedContrib, dstrRedLTDAmt, idDataGroup, false);	
			 bdPurLTDAmt = bdPurLTDAmt + DSTCommonFunctions::convertToBigDecimal(dstPurLTDAmt.stripAll());
			 bdRedLTDAmt = bdRedLTDAmt + DSTCommonFunctions::convertToBigDecimal(dstrRedLTDAmt.stripAll());

			 // QESI AC, QESI UC, QESI YTD. 
			 pRESPTransfer->getField(ifds::QESIACAmount, dstrQESIACAmt, idDataGroup, false);
			 pRESPTransfer->getField(ifds::QESIRedACAmt, dstrQESIRedACAmt, idDataGroup, false);
			 pRESPTransfer->getField(ifds::QESIUCAmount, dstrQESIUCAmt, idDataGroup, false);
			 pRESPTransfer->getField(ifds::QESIRedUCAmt, dstrQESIRedUCAmt, idDataGroup, false);
			 pRESPTransfer->getField(ifds::QESIYTDContribution, dstrQESIYTDAmt, idDataGroup, false);
			 pRESPTransfer->getField(ifds::QESIRedYTDContrib, dstrQESIRedYTDAmt, idDataGroup, false);
			 bdQESIACAmt = bdQESIACAmt + DSTCommonFunctions::convertToBigDecimal(dstrQESIACAmt.stripAll());
			 bdQESIRedACAmt = bdQESIRedACAmt + DSTCommonFunctions::convertToBigDecimal(dstrQESIRedACAmt.stripAll());
			 bdQESIUCAmt = bdQESIUCAmt + DSTCommonFunctions::convertToBigDecimal(dstrQESIUCAmt.stripAll());
			 bdQESIRedUCAmt = bdQESIRedUCAmt + DSTCommonFunctions::convertToBigDecimal(dstrQESIRedUCAmt.stripAll());
			 bdQESIYTDAmt = bdQESIYTDAmt + DSTCommonFunctions::convertToBigDecimal(dstrQESIYTDAmt.stripAll());
			 bdQESIRedYTDAmt = bdQESIRedYTDAmt + DSTCommonFunctions::convertToBigDecimal(dstrQESIRedYTDAmt.stripAll());

			 // QESI Pre-Feb 21, 2007
			 pRESPTransfer->getField(ifds::Pre2007QESIContrib, dstrPre2007QESIContribAmt, idDataGroup, false);	
			 bdPre2007QESIContribAmt = bdPre2007QESIContribAmt + DSTCommonFunctions::convertToBigDecimal(dstrPre2007QESIContribAmt.stripAll());	

			 // QESI Pre Feb 2007 = 'Net of LTD' - 'Net of QESI AC' - 'Net of QESI UC' - 'Net of QESI YTD'	
			 bdDiffAmt = bdPurLTDAmt + bdRedLTDAmt - bdQESIACAmt - bdQESIRedACAmt - bdQESIUCAmt - bdQESIRedUCAmt - bdQESIYTDAmt - bdQESIRedYTDAmt - bdPre2007QESIContribAmt;	
		 }
      }

      ++iter;
   }	

   if ( pRESPTransfer && (bdDiffAmt != bdZero) ) 
   {	
	   // 1790 - The QESI Pre Feb 2007 is not equal to LTD - QESI AC - QESI UC - QESI YTD
	   getErrMsg( IFASTERR::QESIPREFEB2007_NOT_EQUAL_LTD_MINUS_QESIAC_QESIUC_QESIYTD, 	  
				  CND::ERR_QESIPREFEB2007_NOT_EQUAL_LTD_MINUS_QESIAC_QESIUC_QESIYTD, 		  
				  CND::WARN_QESIPREFEB2007_NOT_EQUAL_LTD_MINUS_QESIAC_QESIUC_QESIYTD, 	
				  idDataGroup); 
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RESPTransferList::validateTransferUpdate ( const BFDataGroupId &idDataGroup ) 
{  
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateTransferUpdate"));

	DString dstrAccountNum, dstrTransId, dstrEffectiveDate, dstrCanceled, dstrReversal;
	MFAccount *pMFAccount = NULL;

	getField (ifds::AccountNum, dstrAccountNum, idDataGroup, false);
	dstrAccountNum.strip ().stripLeading ('0');

	getField (ifds::TransId, dstrTransId, idDataGroup);	
	getField (ifds::EffectiveDate, dstrEffectiveDate, idDataGroup);

	if (getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING && pMFAccount && !(dstrTransId.stripAll().empty()))
	{	 
		RESPTransactionsList *pRESPTransactionsList (NULL);

		if (pMFAccount->getRESPTransactionsList (pRESPTransactionsList, 
												 I_("H"), 			// HistoryPending
												 dstrTransId,		// ReqTransid
												 NULL, 				// RESPBenefId
												 I_("ALL"),			// BeneName
												 dstrEffectiveDate, // FromDate
												 dstrEffectiveDate, // ToDate
												 I_("ALL"),	 		// TransType
												 I_("A"),			// TfrStat
												 I_("A"),			// RepHRDC
												 idDataGroup) <= WARNING && pRESPTransactionsList)
		{						
			BFObjIter iter( *pRESPTransactionsList, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
			iter.begin();

			while (!iter.end())
			{			
				RESPTransactionsDetails *pRESPTransactionsDetails = dynamic_cast<RESPTransactionsDetails*>(iter.getObject());

				TransactionDetails *pTransactionDetails (NULL);

				if (pRESPTransactionsDetails->getTransactionDetails (pTransactionDetails, idDataGroup) <= WARNING && pTransactionDetails)
				{							
					pTransactionDetails->getField( ifds::Cancelled, dstrCanceled, idDataGroup, false );
					pTransactionDetails->getField( ifds::Reversal, dstrReversal, idDataGroup, false );

					if( dstrReversal == YES || dstrCanceled == YES )
					{						
						// 1966 - Update of transfer notional values for a cancelled and/or reversed trade is not allowed.
						getErrMsg( IFASTERR::NOTIONAL_AMOUNTS_UPDATE_FOR_CANCELLED_OR_REVERSED_TRADE_NOT_ALLOWED, 
								   CND::ERR_NOTIONAL_AMOUNTS_UPDATE_FOR_CANCELLED_OR_REVERSED_TRADE_NOT_ALLOWED, 
								   CND::WARN_NOTIONAL_AMOUNTS_UPDATE_FOR_CANCELLED_OR_REVERSED_TRADE_NOT_ALLOWED, 
								   idDataGroup); 

						break;
					}
				}				

				++iter;
			}			
		}		
	}
		
	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RESPTransferList::validateBeneficiaries (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateBeneficiaries" ) );

   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
   iter.begin();

   while (!iter.end())
   {
      RESPTransfer *pRESPTransfer = dynamic_cast<RESPTransfer*>(iter.getObject());

	  if (!(pRESPTransfer->isUpdatedForDataGroup ( idDataGroup, false )))
		  pRESPTransfer->validateBeneficiary(idDataGroup);
      
      ++iter;
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log::   Y:/VCS/BF iFAST/ifastcbo/RESPTransferList.cpp-arc  $
// 
//    Rev 1.37   Oct 17 2011 14:59:40   popescu
// 2646349 - subsequent fix on account level notional
// 
//    Rev 1.36   Oct 06 2011 10:35:14   panatcha
// P0185010FN01 - Beneficiary Allocations, EAP, LLP Withdrawals
// 
//    Rev 1.35   Oct 05 2011 00:58:50   panatcha
// IN2672499 - RESP Transfer Information error message
// 
//    Rev 1.34   Sep 22 2011 23:30:04   popescu
// Incident 2646349 - adjust the account level record buckets with the notional for historical bene
// 
//    Rev 1.33   Jul 29 2011 07:42:00   panatcha
// fix IN5285248 and IN2591262
// 
//    Rev 1.32   Jul 25 2011 07:15:02   panatcha
// P0184541_FN01_InvescoQESItrans incidents
// 
//    Rev 1.31   Jul 14 2011 08:13:20   panatcha
// DRAFT - IN2584478, IN5285248, IN2591262 
// 
//    Rev 1.30   Jul 11 2011 05:23:08   dchatcha
// IN# 2587585 - P0184541FN01- Error when accessing RESP TRFR notl in trading screen
// 
//    Rev 1.29   Jun 28 2011 10:32:34   panatcha
// P0184541_FN01_InvescoQESItrans
// 
//    Rev 1.28   Dec 02 2010 15:25:46   jankovii
// IN 2293445 - beneficiary must be mandatory for all  RESP transfers
// 
//    Rev 1.27   Oct 29 2010 05:34:52   kitticha
// PET0165541 FN03 - QESI Phase3.
// 
//    Rev 1.26   Sep 03 2010 05:34:18   dchatcha
// IN# 2231991 - No warning message when changing the Transfer%
// 
//    Rev 1.25   Aug 13 2010 12:09:38   jankovii
// Sync up: IN 2200243 - Invesco Trimark Parent Cycle CY1287 {27 JULY 2010}
// 
//    Rev 1.24   Jul 21 2010 23:28:06   dchatcha
// PET0165541 FN09 QESI RESP phase2B - SOC04 - Eligible Transfer on RESP Transfer screen, code review, remove no longer required (more)pieces.
// 
//    Rev 1.23   Jul 21 2010 22:44:08   dchatcha
// PET0165541 FN09 QESI RESP phase2B - SOC04 - Eligible Transfer on RESP Transfer screen, code review, remove no longer required pieces.
// 
//    Rev 1.22   Jul 21 2010 01:32:42   dchatcha
// PET0165541 FN09 QESI RESP phase2B - SOC04 - Eligible Transfer on RESP Transfer screen, code review, logic will be more simpler.
// 
//    Rev 1.21   Jun 29 2010 03:01:10   dchatcha
// PET0165541 FN09 QESI RESP phase2B - SOC04 - Eligible Transfer on RESP Transfer screen, code review.
// 
//    Rev 1.20   Jun 24 2010 07:48:16   dchatcha
// PET0165541 FN09 QESI RESP phase2B - SOC04 - Eligible Transfer on RESP Transfer screen.
// 
