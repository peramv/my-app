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
//    Copyright 2005 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : TransCancel.cpp
// ^AUTHOR : 
// ^DATE   : July 21, 2004
//
// ^CLASS    : TransCancel 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "transcancel.hpp"

#include "dstcommonfunction.hpp"
#include "dilutionalloclist.hpp"
#include "dilutionalloc.hpp"
#include "BatchInfoList.hpp"
#include "RESPInfoUpdateValidationList.hpp"

#include "mgmtco.hpp"

#include <ifastdataimpl\dse_dstc0083_vw.hpp>
#include <ifastdataimpl\dse_dstc0127_req.hpp>
#include <ifastdataimpl\dse_dstc0127_vw.hpp>
#include <ifastdataimpl\dse_dstc0149_vw.hpp>
#include <ifastdataimpl\dse_dstc0337_req.hpp>
#include <ifastdataimpl\dse_dstc0337_vw.hpp>
#include "mfaccount.hpp"
#include "mgmtcooptions.hpp"
#include "FundLmtOverrideList.hpp"
#include "fundlmtoverride.hpp"
#include "transcancellist.hpp"
#include "translationtable.hpp"

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest TRANS_CANCEL;
   extern CLASS_IMPORT const DSTCRequest TRANS_NUM;
}

namespace  
{
   const I_CHAR * const CLASSNAME    = I_( "TransCancel");  

   // Statuses for individual trade cancellation
   const I_CHAR * const UNVERIFIED                       = I_("01");
   const I_CHAR * const VERIFIED                         = I_("02");
   const I_CHAR * const DELETED                          = I_("03");

   const I_CHAR * const YES                              = I_("Y");
   const I_CHAR * const NO                               = I_("N");

   const I_CHAR * const BULK_CANCELLATION                = I_( "BULKCAN" ); 
   const I_CHAR * const INDIVIDUAL_CANCELLATION          = I_( "INDVCAN" );
   const I_CHAR * const SUPPRESS_INDICATOR_DEFAULT_CODE  = I_("2");
   const int AUTO_BATCHING = 2;
  
   const I_CHAR * const RIGHT_TO_CANCEL					 = I_("82");
   const I_CHAR * const VERIFIED_AND_REFUNDCALCREQ		 = I_("15");
   const I_CHAR * OMNIBUS								 = I_("OM");
}

namespace RefundPayType
{
   const I_CHAR * const MANUAL       = I_("M"); 
   const I_CHAR * const REDIRECT_RA  = I_("RA");
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const VERIFY_CANCEL_INSTRUCTION;
   extern CLASS_IMPORT I_CHAR * const TRANCE_CANCELLATION;
   extern CLASS_IMPORT I_CHAR * const MCH_AND_SECUR_REC_FILE_INDICATOR;
}

namespace ifds
{   
   extern CLASS_IMPORT const BFTextFieldId ReadOnly;   
   // This is just for a Bulk Cancel record accessed via the Transaction History screen
   extern CLASS_IMPORT const BFTextFieldId XtraActive;    

   extern CLASS_IMPORT const BFTextFieldId MCHSRActive;
   extern CLASS_IMPORT const BFTextFieldId MCHIndCancel;
   extern CLASS_IMPORT const BFTextFieldId SRIndCancel;
   extern CLASS_IMPORT const BFTextFieldId ESGSettle;
   extern CLASS_IMPORT const BFTextFieldId IsSplitDilution;
   extern CLASS_IMPORT const BFTextFieldId RecptIssued;

   extern CLASS_IMPORT const BFTextFieldId CancelContribRcpt;
   extern CLASS_IMPORT const BFTextFieldId ExcldRcptPrint;
   extern CLASS_IMPORT const BFTextFieldId RetRcptToSender;
   extern CLASS_IMPORT const BFTextFieldId CancelGrant;
   extern CLASS_IMPORT const BFTextFieldId GrantExists;
   extern CLASS_IMPORT const BFTextFieldId TrfResubmit;
   extern CLASS_IMPORT const BFTextFieldId IsAGrantTrade;
   extern CLASS_IMPORT const BFIntegerFieldId WarnCode;
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFTextFieldId SettleBatch;   
   extern CLASS_IMPORT const BFTextFieldId RefundOption;
   extern CLASS_IMPORT const BFTextFieldId RefundOptionAvailable;
   extern CLASS_IMPORT const BFTextFieldId RefundPayType;
   extern CLASS_IMPORT const BFTextFieldId TaxType;
   extern CLASS_IMPORT const BFTextFieldId RefundRVCD;
   extern CLASS_IMPORT const BFTextFieldId StopFlag;
   extern CLASS_IMPORT const BFTextFieldId rxFundCode;
   extern CLASS_IMPORT const BFTextFieldId rxClassCode;
   extern CLASS_IMPORT const BFDecimalFieldId MinInitAmt;
   extern CLASS_IMPORT const BFTextFieldId UCITFlag;
   extern CLASS_IMPORT const BFTextFieldId XEditEventRecieptDateTime;
   extern CLASS_IMPORT const BFTextFieldId AutoDefaultCancelGrant;
}
namespace RVCDCODEALLOWEDFORREFUND
{
	const I_CHAR * const RIGHT_TO_CANCEL	  = I_("82");
	const I_CHAR * const RIGHT_TO_CANCEL_RULE = I_("49");
}

namespace CND
{
   //extern const long ERR_DATA_NOT_FOUND;
   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
   extern const long ERR_ACCOUNTABLE_CODE_REQUIRED;
   extern const long ERR_REVERSAL_CODE_REQUIRED;
   extern const long WARN_GRANT_ASSOC_WITH_TRADE;
   extern const long WARN_TRANFER_TANSACTION_RESUBMITTED;
   extern const long WARN_TRADE_IS_A_GRANT;
   extern const long ERR_GRANT_ASSOC_WITH_TRADE;
   extern const long ERR_TRANFER_TANSACTION_RESUBMITTED;
   extern const long ERR_TRADE_IS_A_GRANT;
   extern const long ERR_ADJUSTMENT_REQUIRED;
   extern const long WARN_ADJUSTMENT_MAY_BE_REQUIRED;
   extern const long ERR_TRADE_EXIST_FOR_TAX_YEAR;
   extern const long WARN_TRADE_EXIST_FOR_TAX_YEAR;
   extern const long ERR_SYS_TRIG_AMEND_AND_RECAL_QESI_NOTIONAL_BALANCE;
   extern const long WARN_SYS_TRIG_AMEND_AND_RECAL_QESI_NOTIONAL_BALANCE;
   extern const long ERR_CANCEL_BATCH_MUST_BE_PREFIXED_SP_DC;
   extern const long WARN_CANCEL_BATCH_MUST_BE_PREFIXED_SP_DC;  
   extern const long ERR_RIGHT_TO_CANCEL_NOTALLWD;
   extern const long  ERR_EVENT_RECIEPT_DATE_AND_TIME_EMPTY;
   extern const long  WARN_EVENT_RECIEPT_DATE_AND_TIME_EMPTY;
   extern const long  ERR_FUTURE_DATE;
   extern const long  ERR_REQ_FIELD_EMPTY; 
   extern const long  ERR_INVALID_TIME_FORMAT;
   extern const long ERR_TRADE_EXITS_IN_ACCT;
   extern const long WARN_TRADE_EXITS_IN_ACCT;
}
namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const ADJUSTMENT_MAY_BE_REQUIRED;
   extern CLASS_IMPORT I_CHAR * const TRADE_EXIST_FOR_TAX_YEAR;
   extern CLASS_IMPORT I_CHAR * const SYS_TRIG_AMEND_AND_RECAL_QESI_NOTIONAL_BALANCE;
   extern CLASS_IMPORT I_CHAR * const CANCEL_BATCH_MUST_BE_PREFIXED_SP_DC;
   extern CLASS_IMPORT I_CHAR * const EVENT_RECIEPT_DATE_AND_TIME_EMPTY;
   extern CLASS_IMPORT I_CHAR * const  TRADE_EXITS_IN_OMNIBUS_ACCT;
   extern CLASS_IMPORT I_CHAR * const  TRADE_EXITS_IN_ACCT;
}
namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const EXCHANGE_LIKE;
   extern CLASS_IMPORT I_CHAR * const REDEMPTION_LIKE;
   extern CLASS_IMPORT I_CHAR * const PURCHASE_LIKE;
   extern CLASS_IMPORT I_CHAR * const ROLLOVER_EXCHANGE_OUT;
   extern CLASS_IMPORT I_CHAR * const ROLLOVER_EXCHANGE_IN;
}
//-------------------------------------------------------------------
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
   //Field DD Id,                State Flags,                        Group Flags
   { ifds::TransNum,             BFCBO::NONE,                           0 },
   { ifds::Accountable,          BFCBO::NONE,                           0 },
   { ifds::RvCode,               BFCBO::NONE,                           0 },
   { ifds::OnStmt,               BFCBO::REQUIRED,                       0 },
   { ifds::ConfirmRequired,      BFCBO::REQUIRED,                       0 },
   { ifds::CancelCheque,         BFCBO::REQUIRED,                       0 },
   { ifds::TranStatus,           BFCBO::NONE,                           0 },
   { ifds::Remarks1,             BFCBO::NONE,                           0 },
   { ifds::Remarks2,             BFCBO::NONE,                           0 },
   { ifds::Remarks3,             BFCBO::NONE,                           0 },
   { ifds::ModPermission,        BFCBO::NONE,                           0 },
   { ifds::Version,              BFCBO::NONE,                           0 },
   { ifds::TransType,            BFCBO::NONE,                           0 },
   { ifds::TransId,              BFCBO::NONE,                           0 },
   { ifds::Batch,                BFCBO::REQUIRED  | BFCBO::APPEND_VALUE_TO_SUBST,0 },
   { ifds::Trace,                BFCBO::NONE,                           0 },
   { ifds::ReadOnly,             BFCBO::CALCULATED_FIELD,               0 },
   { ifds::CancellationType,     BFCBO::NONE,                           0 },
   { ifds::XtraActive,           BFCBO::NONE,                           0 },
   { ifds::MCHFileIndicator,     BFCBO::NONE,                           0 },
   { ifds::SecRecFileIndicator,  BFCBO::NONE,                           0 },
   { ifds::ESGSettle,            BFCBO::NONE,                           0 },
   { ifds::IsSplitDilution,      BFCBO::NONE,                           0 },

   { ifds::RecptIssued,          BFCBO::NONE,                           0 },
   { ifds::CancelContribRcpt,    BFCBO::REQUIRED,                       0 },
   { ifds::ExcldRcptPrint,       BFCBO::REQUIRED,                       0 },
   { ifds::RetRcptToSender,      BFCBO::REQUIRED,                       0 },
   { ifds::CancelGrant,          BFCBO::NONE,                           0 },
   { ifds::GrantExists,          BFCBO::NONE,                           0 },
   { ifds::TrfResubmit,          BFCBO::NONE,                           0 },
   { ifds::IsAGrantTrade,        BFCBO::NONE,                           0 },
   { ifds::SettleBatch,          BFCBO::NONE,                           0 },
   { ifds::RefundOption,         BFCBO::NONE,                           0 },
   { ifds::RefundPayType,        BFCBO::NONE,                           0 },
   { ifds::rxFundCode,           BFCBO::NONE,                           0 },
   { ifds::rxClassCode,          BFCBO::NONE,                           0 },
   { ifds::EventReceiptDate,               BFCBO::NONE,                 0}, 
   { ifds::EventReceiptTime,               BFCBO::NONE,                 0},
   { ifds::XEditEventRecieptDateTime,      BFCBO::IMMEDIATE_VALIDATION, 0},
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
//  Object Label,             State Flags,           Group Flags 
   {  I_(""),                 BFCBO::REQUIRED,         0}
};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );

//*********************************************************************************
TransCancel::TransCancel( BFAbstractCBO &parent ) : MFCanBFCbo( parent ),
pBatchInfoList (NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );   
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0, NULL );   
   addCrossEdit (ifds::XEditEventRecieptDateTime, ifds::EventReceiptDate); 
   addCrossEdit (ifds::XEditEventRecieptDateTime, ifds::EventReceiptTime);
}

//*********************************************************************************
TransCancel::~TransCancel()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//************************************************************************************
SEVERITY TransCancel::initNew ( const BFDataGroupId &idDataGroup,
                                const DString &transNum, /*, const DString &transId */ 
                                const DString &dstrTradeDate,
                                const DString &dstrSettleDate,
                                const DString &dstrTransType )
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("InitNew" ));

   _dstrTradeDate  = dstrTradeDate;
   _dstrSettleDate = dstrSettleDate;
   _dstrTransType  = dstrTransType;

   commonInit( idDataGroup, transNum );

   //Remove 'N/A' option from the list. It's applicable for Dilution only.
   BFProperties *pBFProperties;
   DString dstrRefundOptionSet;

   pBFProperties = getFieldProperties (ifds::RefundOption, idDataGroup);
   pBFProperties->getAllSubstituteValues (dstrRefundOptionSet);
   dstrRefundOptionSet = removeItemFromSubtList(dstrRefundOptionSet, I_("N/A"));   
   setFieldAllSubstituteValues(ifds::RefundOption, idDataGroup, dstrRefundOptionSet);
   
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************************
SEVERITY TransCancel::init( const BFData& data,
                            const DString &dstrTradeDate,
                            const DString &dstrSettleDate )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init(BFData&)" ) );  

   attachDataObject (const_cast<BFData&>(data), false);    

   _dstrTradeDate = dstrTradeDate;
   _dstrSettleDate = dstrSettleDate;

   // If this record is accessed from the Transaction History screen,
   // and the cancellation was done through the Bulk process, then all fields cannot be modified
   DString dstrCancellationType= data.getElementValue( ifds::CancellationType );   
   if ( BULK_CANCELLATION == dstrCancellationType.stripAll().upperCase() )
   {
      setReadOnlyFields( true, BF::HOST );
      setFieldReadOnly (ifds::TransNum,   BF::HOST, true );
      setFieldReadOnly (ifds::TranStatus, BF::HOST, true );

      setFieldNoValidate( ifds::XtraActive, I_( "Y" ), BF::HOST, false, false, true );

      ////////DilutionAllocList *pDilutionAllocList = NULL;
      ////////getDilutionAllocList( BF::HOST, pDilutionAllocList );   
   }
   else
   {
      DString transNum = data.getElementValue( ifds::TransNum );
      transNum.strip ();

      _dstrTransType = data.getElementValue( ifds::TransType );
      commonInit( BF::HOST,
                  transNum );
   }

   //Remove 'N/A' option from the list. It's applicable for Dilution only.
   BFProperties *pBFProperties;
   DString dstrRefundOptionSet;

   pBFProperties = getFieldProperties (ifds::RefundOption, BF::HOST);
   pBFProperties->getAllSubstituteValues (dstrRefundOptionSet);
   dstrRefundOptionSet = removeItemFromSubtList(dstrRefundOptionSet, I_("N/A"));   
   setFieldAllSubstituteValues(ifds::RefundOption, BF::HOST, dstrRefundOptionSet);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void TransCancel::setReadOnlyFields (bool readonly, const BFDataGroupId &idDataGroup)
{
   setFieldReadOnly (ifds::Accountable,     idDataGroup, readonly );
   setFieldReadOnly (ifds::RvCode,          idDataGroup, readonly );
   setFieldReadOnly (ifds::OnStmt,          idDataGroup, readonly );
   setFieldReadOnly (ifds::ConfirmRequired, idDataGroup, readonly );
   setFieldReadOnly (ifds::CancelCheque,    idDataGroup, readonly );
   setFieldReadOnly (ifds::Batch,           idDataGroup, readonly );
   setFieldReadOnly (ifds::Remarks1,        idDataGroup, readonly );
   setFieldReadOnly (ifds::Remarks2,        idDataGroup, readonly );
   setFieldReadOnly (ifds::Remarks3,        idDataGroup, readonly );
   setFieldReadOnly (ifds::ESGSettle,       idDataGroup, readonly );
}

//******************************************************************************
void TransCancel::commonInit( const BFDataGroupId &idDataGroup,
                              const DString &transNum )
{
   DString substList;
   TranslationTable *pTranslationTable = NULL;
   getMgmtCo().getTranslationTable(I_("RV"), pTranslationTable);
   if(pTranslationTable)
   {
       pTranslationTable->getSubstitutionList(substList, true);
   }

// PET 1235, FN01 remove 08---Back dated; 10---settlement adjust ment
   substList = removeItemFromSubtList( substList, I_( "08" ) );   
   substList = removeItemFromSubtList( substList, I_( "10" ) );    
   setFieldAllSubstituteValues( ifds::RvCode, 
                                idDataGroup, 
                                substList );

   setFieldReadOnly( ifds::TransNum,   idDataGroup, true );
   setFieldReadOnly( ifds::TranStatus, idDataGroup, true );

   setFieldRequired( ifds::RvCode, idDataGroup, true );
   setFieldValid( ifds::RvCode, idDataGroup, false );

   DString dstrReadOnly( NO );	    
   bool bVerification = getWorkSession().hasReadPermission( UAF::VERIFY_CANCEL_INSTRUCTION );   

   setFieldNoValidate( ifds::CancelGrant,     NO,       idDataGroup, false, false, true );

   if( isNew () )
   {
      if( !isIndividualTransCancelAllowed() )
      {
         dstrReadOnly = YES;
         setReadOnlyFields (true, idDataGroup);
      }
      else 
      {
         setNewTransStatus( idDataGroup );

         setFieldNoValidate( ifds::OnStmt,          NO,       idDataGroup, false, false, true );
         setFieldNoValidate( ifds::ConfirmRequired, YES,      idDataGroup, false, false, true );
         setFieldNoValidate( ifds::CancelCheque,    YES,      idDataGroup, false, false, true );
         setFieldNoValidate( ifds::TransNum,        transNum, idDataGroup, false, false, true );
         setFieldNoValidate( ifds::ESGSettle,       I_("In"), idDataGroup, false, false, true );
      }
   }
   else	
   {
      DString dstrModPerm, dstrTranStatus;

      getField( ifds::ModPermission, dstrModPerm,    idDataGroup, false );
      getField( ifds::TranStatus,    dstrTranStatus, idDataGroup, false );

      if ( !isModifiableBasedOnStatus( idDataGroup ) ||
         ( dstrModPerm == I_("1") && !isIndividualTransCancelAllowed() ) ||
         ( dstrModPerm == I_("2") && !bVerification ) )
      {
         dstrReadOnly = YES;
         setReadOnlyFields (true, idDataGroup);
      }
   }

   setFieldNoValidate( ifds::ReadOnly, dstrReadOnly, idDataGroup, false, false, true );
   setFieldValid( ifds::Accountable, idDataGroup, false );
//init batch by call view 127
   if (isNew())
   {
      getBatchNum (idDataGroup);

      initBatchList (idDataGroup);
   }
   else
   {
      DString originalBatch, 
         batchList;

      getField (ifds::Batch, originalBatch, idDataGroup);
      batchList = originalBatch + I_("=") +  originalBatch + I_(";");
      setFieldAllSubstituteValues (ifds::Batch, idDataGroup, batchList);	
   }

   DilutionAllocList *pDilutionAllocList = NULL;
   getDilutionAllocList (idDataGroup, pDilutionAllocList);    

   if (pDilutionAllocList)
   {
      BFObjIter iter ( *pDilutionAllocList, 
                        idDataGroup, 
                        false, 
                        BFObjIter::ITERTYPE::NON_DELETED);

      iter.begin();
      while (!iter.end())
      {
         DilutionAlloc *pDilutionAlloc = dynamic_cast <DilutionAlloc *> (iter.getObject());

         if (pDilutionAlloc)
         {
            //only set the resp date to the trade date for the first record...
            pDilutionAlloc->setTradeDateToRespDate (_dstrTradeDate, idDataGroup);
            break;
         }
         ++iter;
      }
   }

   setTransNum( idDataGroup );

   DString dstrMCHSRActive;

   getWorkSession().getOption ( ifds::MCHSRActive, dstrMCHSRActive, BF::HOST, false);
   dstrMCHSRActive.stripAll().upperCase();

   if (dstrMCHSRActive == YES)
   {
      setSuppressIndicatorsSet(idDataGroup);

      if (isNew())
      {
         setSuppressIndicatorsPerm(idDataGroup);
         setDefaultSuppressIndicators(idDataGroup);
      }
      else
      {
         setSuppressIndicatorsReadOnlyFlags(idDataGroup);
      }
   }
   else
   {
      setSuppressIndicatorsInactive(idDataGroup, isNew());
   }
   setFieldValid(ifds::EventReceiptDate,idDataGroup,false);
   setFieldValid(ifds::EventReceiptTime,idDataGroup,false);
   bool bEventReceiptDateTimeAppl = bIsEventReceiptDateTimeAppl(idDataGroup); 
   if(isNew())
   {
   //A new setup should allow entry irresepctive of verification status
   setFieldNoValidate(ifds::EventReceiptDate,NULL_STRING,idDataGroup);
   setFieldNoValidate(ifds::EventReceiptTime,NULL_STRING,idDataGroup);
   setFieldReadOnly(ifds::EventReceiptDate,idDataGroup, !bEventReceiptDateTimeAppl);//no apply related changes
   setFieldReadOnly(ifds::EventReceiptTime,idDataGroup, !bEventReceiptDateTimeAppl); 
   }
   else
   {
   //mask the time returned by the view using ##:##:##
   DString dstrValue;
   getField (ifds::EventReceiptTime, dstrValue, BF::HOST, false);
   formatStringUsingMask(dstrValue, I_("##:##:##"));
   setFieldNoValidate(ifds::EventReceiptTime, dstrValue, BF::HOST, false, false, false);

   setFieldReadOnly(ifds::EventReceiptDate,idDataGroup, (!bEventReceiptDateTimeAppl));  //||
														  //(dstrVerifyStat == VERIFIED));
   setFieldReadOnly(ifds::EventReceiptTime,idDataGroup, (!bEventReceiptDateTimeAppl));//  ||
														  //(dstrVerifyStat == VERIFIED));
   }

   setField( ifds::TransType, _dstrTransType, idDataGroup );

   setFieldNoValidate( ifds::CancelContribRcpt, NO, idDataGroup, false, false, true );
   setFieldNoValidate( ifds::ExcldRcptPrint, NO, idDataGroup, false, false, true );
   setFieldNoValidate( ifds::RetRcptToSender, NO, idDataGroup, false, false, true );
   
   setFieldReadOnly( ifds::RefundOption, idDataGroup, true );
   setFieldReadOnly( ifds::RefundPayType, idDataGroup, true );
}

//******************************************************************************
SEVERITY TransCancel::getDilutionAllocList ( const BFDataGroupId &idDataGroup, 
                                             DilutionAllocList *&pDilutionAllocList )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getDilutionAllocList"));

   pDilutionAllocList = NULL;
   if (isDilutionAllowed (idDataGroup))
   {
      pDilutionAllocList = 
         dynamic_cast<DilutionAllocList*> (getObject( I_("DilutionAllocList"), idDataGroup));
      
      if (!pDilutionAllocList)
      {
         DString transId, transNum;

         getField (ifds::TransId, transId, idDataGroup, false);
         getField (ifds::TransNum, transNum, idDataGroup, false);
         if (isNew())
         {
            pDilutionAllocList = new DilutionAllocList (*this);
            pDilutionAllocList->initNew ( idDataGroup, _dstrTradeDate, _dstrSettleDate );
         }
         else if (!transId.empty())
         {
            pDilutionAllocList = new DilutionAllocList (*this);
            pDilutionAllocList->init (transId, idDataGroup, _dstrTradeDate, _dstrSettleDate, transNum );
         }
         if (pDilutionAllocList)
         {
            pDilutionAllocList->setField(ifds::TransNum, transNum, BF::HOST,false, false, false);
            BFObjIter iter (*pDilutionAllocList, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);

            if (isNew ())
            {
               //new 100% dilution
               pDilutionAllocList->addNewAllocation (NULL_STRING, NULL_STRING, idDataGroup);
            }
            else
            {
               BFObjIter iter (*pDilutionAllocList, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);

               if (iter.getNumberOfItemsInList () == 0)
               {
                  DString accountable, 
                     backDatedReason;

                  getField (ifds::Accountable, accountable, idDataGroup, false);
                  getField (ifds::RvCode, backDatedReason, idDataGroup, false);
                  pDilutionAllocList->addNewAllocation (accountable, backDatedReason, idDataGroup);
               }
            }
            if (GETCURRENTHIGHESTSEVERITY() <= WARNING)
            {
               setObject( pDilutionAllocList, 
                          I_("DilutionAllocList"), 
                          OBJ_ACTIVITY_NONE, 
                          idDataGroup);
            }
            else
            {
               delete pDilutionAllocList;
               pDilutionAllocList = NULL;
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TransCancel::getBatchNum ( const BFDataGroupId &idDataGroup,
                                    const DString &track /*= I_("N")*/,
                                    const DString &pageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                        CLASSNAME, 
                        I_("getBatchNum"));

   BFData query127 (ifds::DSTC0127_REQ);
   BFData *response = new BFData (ifds::DSTC0127_VW);

   DString mgmtCoIdOut;
   query127.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   query127.setElementValue (ifds::Track, track);
   query127.setElementValue (ifds::Activity, pageName);
   query127.setElementValue (ifds::SupTransNo, YES);	  

   if (BFDataBroker::getInstance ()->
         receive ( DSTC_REQUEST::TRANS_NUM, 
                   query127, 
                   *response, 
                   DSTCRequestor (getSecurity ())) <= WARNING)
   {
      DString batch, 
         batchTrace;

      response->getElementValue (ifds::rxBatchName, batch);
      response->getElementValue (ifds::BatchTrace, batchTrace);   	
      batch.strip();
      batchTrace.strip();

      setFieldNoValidate (ifds::Batch, batch, idDataGroup, false);
      setFieldNoValidate (ifds::Trace, batchTrace, idDataGroup, false);
      setFieldReadOnly (ifds::Trace, idDataGroup, true);
   }

   if (response)
   {
      delete response;
      response = NULL;
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TransCancel::setField ( const BFFieldId& idField, 
                                 const DString& dstrValue,
                                 const BFDataGroupId& idDataGroup, 
                                 bool bFormatted, 
                                 bool bSideEffect, 
                                 bool bCheckCurrentValue)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setField" ) );      

   if (idField == ifds::TranStatus)
   {
      if (dstrValue == DELETED)
      {
         DilutionAllocList * pDilutionAllocList = NULL;

         getDilutionAllocList( idDataGroup, pDilutionAllocList );

         if ( NULL != pDilutionAllocList )
         {
            BFObjIter bfIter (*pDilutionAllocList, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED, false);
            bfIter.begin();
            while (!bfIter.end())
            {
               bfIter.deleteObject ();
            }
         }
         setFieldNoValidate (ifds::ReadOnly, YES, BF::HOST, false, false, true);
         setReadOnlyFields(true, idDataGroup);
      }
   }
   BFCBO::setField (idField, dstrValue, idDataGroup, bFormatted, bSideEffect);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TransCancel::doValidateField ( const BFFieldId &idField, 
                                        const DString &strValue, 
                                        const BFDataGroupId &idDataGroup) 
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("setField"));

   if (idField == ifds::Accountable)
   {
      DString accountableMandatory,
         splitAcCode,
         tranStatus;

      getWorkSession().getOption ( ifds::AccountableMandatory, 
                                   accountableMandatory, 
                                   BF::HOST, 
                                   false);
      getWorkSession().getOption ( ifds::SplitAcCode, 
                                   splitAcCode, 
                                   BF::HOST, 
                                   false);
      getField (ifds::TranStatus, tranStatus, idDataGroup, false);
      setFieldRequired ( ifds::Accountable, 
                         idDataGroup, 
                         accountableMandatory == Y &&
                         !hasAllocatedDilution (idDataGroup) && 
                         tranStatus != DELETED);
   }
   else if ( idField == ifds::RvCode )
   {
      DString tranStatus;
      getField (ifds::TranStatus, tranStatus, idDataGroup, false);

       setFieldRequired ( ifds::RvCode, 
                         idDataGroup, 
                         !hasAllocatedDilution (idDataGroup) && 
                         tranStatus != DELETED);
	  bIsRefundCalcReq(idDataGroup);
   }
   else if ( idField == ifds::Batch )
   {
      if (pBatchInfoList)
          pBatchInfoList->validateBatch (strValue, idDataGroup);
   }
   else if( idField == ifds::EventReceiptDate || idField == ifds::EventReceiptTime )
   {
    DString dstrEventReceiptDate,dstrEventReceiptTime,dstrTemp;
	bool bEventReceiptDateTimeAppl = bIsEventReceiptDateTimeAppl(idDataGroup); 
	getField(ifds::EventReceiptDate, dstrEventReceiptDate, idDataGroup, false);
	getField(ifds::EventReceiptTime, dstrEventReceiptTime, idDataGroup, false);
	dstrEventReceiptDate.stripAll();
    dstrEventReceiptTime.stripAll();
 	//invalidate the field so that crossedit will be called  after fields validation
	setFieldValid(ifds::EventReceiptDate, idDataGroup, false);
	setFieldValid(ifds::EventReceiptTime, idDataGroup, false );
	if ( !dstrEventReceiptDate.empty() && bEventReceiptDateTimeAppl )
	{ 
		DString dstrCurrentSysDate;
        getWorkSession().getDateInHostFormat(dstrCurrentSysDate, DSTCWorkSession::DATE_TYPE::CURRENT_SYSTEM_DAY, idDataGroup);  
		// Event reciept date cannot future dated 
		if (DSTCommonFunctions::CompareDates (dstrCurrentSysDate, dstrEventReceiptDate) == DSTCommonFunctions::FIRST_EARLIER)
		{
	    	addIDITagValue( dstrTemp, I_("FieldName"), I_("Event Receipt Date"));
			ADDCONDITIONFROMFILEIDI( CND::ERR_FUTURE_DATE, dstrTemp );
		}
	}
	if ( !dstrEventReceiptTime.empty() && bEventReceiptDateTimeAppl )
	{
		if(!DSTCommonFunctions::bValidateTime(dstrEventReceiptTime))
		{
			DString dstrTemp;
			addIDITagValue( dstrTemp, I_("FORMAT"), I_("HH:MM:SS"));
            ADDCONDITIONFROMFILEIDI(CND::ERR_INVALID_TIME_FORMAT,dstrTemp)
		}
	}
	if(GETCURRENTHIGHESTSEVERITY () <= WARNING )
	{
		setFieldValid(ifds::EventReceiptDate, idDataGroup, true);
		setFieldValid(ifds::EventReceiptTime, idDataGroup, true );
	}
   }
   else if (idField == ifds::XEditEventRecieptDateTime )
   {
     bool bEventReceiptDateTimeAppl = bIsEventReceiptDateTimeAppl(idDataGroup);
     if(bEventReceiptDateTimeAppl)
	 {
		DString dstrEventReceiptDate,dstrEventReceiptTime,dstrTemp;
		getField(ifds::EventReceiptDate, dstrEventReceiptDate, idDataGroup, false);
		getField(ifds::EventReceiptTime, dstrEventReceiptTime, idDataGroup, false);
		if ( dstrEventReceiptDate.stripAll().empty())
		{
			addIDITagValue( dstrTemp, I_("FieldName"), I_("Event Receipt Date"));
			ADDCONDITIONFROMFILEIDI( CND::ERR_REQ_FIELD_EMPTY, dstrTemp );
		}
		else if ( dstrEventReceiptTime.stripAll().empty() )
		{
			addIDITagValue( dstrTemp, I_("FieldName"), I_("Event Receipt Time"));
			ADDCONDITIONFROMFILEIDI( CND::ERR_REQ_FIELD_EMPTY, dstrTemp );
		}
	 }
   }     
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TransCancel::doApplyRelatedChanges ( const BFFieldId &idField, 
                                              const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doApplyRelatedChanges"));

   if ( idField == ifds::Accountable ||
        idField == ifds::RvCode)
   {
//refresh dilution
      DilutionAllocList *pDilutionList = NULL;
      pDilutionList = dynamic_cast <DilutionAllocList*> (getObject( I_( "DilutionAllocList" ), idDataGroup));
      
      if (pDilutionList)
      {
         BFObjIter iter (*pDilutionList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);	   
         if (iter.getNumberOfItemsInList() == 1)
         {
            DString strValue;

            getField (idField, strValue, idDataGroup, false);
            
            BFFieldId idField_ (idField);
            
            if (idField == ifds::RvCode)
            {
               idField_ = ifds::BackDatedReason;
            }
            iter.getObject()->setField (idField_, strValue, idDataGroup);
         }
      }
	  //Call in to enable disable the Refund paytype and Refund Option based on the Genr Cntrl
	  if( idField == ifds::RvCode )
	  {	  
		  SetRefundRVCDFields(idDataGroup); 		  
      }
   } // ifds::RvCode)

   else if (idField == ifds::CancelContribRcpt)
   {
      DString strValue;
      getField(idField,strValue,idDataGroup);
      if( strValue == NO )
      {
         setField(ifds::ExcldRcptPrint,NO,idDataGroup);
         setField(ifds::RetRcptToSender,NO,idDataGroup);
         
         setFieldReadOnly (ifds::ExcldRcptPrint, idDataGroup, true);
         setFieldReadOnly (ifds::RetRcptToSender, idDataGroup, true);
      } 
      else
      {
         setFieldReadOnly (ifds::ExcldRcptPrint, idDataGroup, false);
         setFieldReadOnly (ifds::RetRcptToSender, idDataGroup, false);
      }
   }
   else if (idField == ifds::ExcldRcptPrint)
   {
      DString strValue;
      getField(idField,strValue,idDataGroup);
      if( strValue == YES )
      {
         setField(ifds::RetRcptToSender,NO,idDataGroup);
         setFieldReadOnly (ifds::RetRcptToSender, idDataGroup, true);
      } 
      else
      {
         setFieldReadOnly (ifds::RetRcptToSender, idDataGroup, false);
      }
   }
   else if (idField == ifds::Batch)
   {
      setFieldUpdated (ifds::Batch, idDataGroup, true);
      setFieldValid (ifds::Batch, idDataGroup, false);
   }
   else if (idField == ifds::IsAGrantTrade)
   {
	   DString dstrIsAGrantTrade;
	   getField(ifds::IsAGrantTrade, dstrIsAGrantTrade, idDataGroup);
	   if (dstrIsAGrantTrade == I_("Y"))
		   setFieldNoValidate(ifds::CancelGrant, I_("Y"), idDataGroup, false);
   }
   else if (idField == ifds::GrantExists)
   {
        DString dstrAutoDefaultCancelGrant, dstrGrantExists;

        getField(ifds::GrantExists, dstrGrantExists, idDataGroup, false);
        getWorkSession().getOption(ifds::AutoDefaultCancelGrant, dstrAutoDefaultCancelGrant, BF::HOST, false);

        dstrGrantExists.upperCase().stripAll(); 
        dstrAutoDefaultCancelGrant.upperCase().stripAll();

        if (isNew() && dstrAutoDefaultCancelGrant == YES)
        {
            setFieldNoValidate(ifds::CancelGrant, dstrGrantExists == YES ? YES:NO, idDataGroup, false, false, true, true);
        }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool TransCancel::isDilutionAllowed (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("isDilutionAllowed"));

   DString splitAcCode, fundSERVClient, readOnly;
        
   getWorkSession().getOption (ifds::SplitAcCode, splitAcCode, BF::HOST, false);
   getWorkSession().getOption (ifds::FundSERVClient, fundSERVClient, BF::HOST, false);
   getField (ifds::ReadOnly, readOnly, idDataGroup, false);
   
   return (splitAcCode == Y || (splitAcCode == N && fundSERVClient == Y)) && readOnly != Y;
}

//******************************************************************************
bool TransCancel::hasAllocatedDilution (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("hasAllocatedDilution"));

   bool bHasAllocatedDilution = false;
   DilutionAllocList *pDilutionList = 
      dynamic_cast <DilutionAllocList*> (getObject (I_("DilutionAllocList" ), idDataGroup));

   if (pDilutionList)
   {
      BFObjIter iter (*pDilutionList, idDataGroup);
      bHasAllocatedDilution = iter.getNumberOfItemsInList() > 1;
   }

   return bHasAllocatedDilution;
}

//******************************************************************************
SEVERITY TransCancel::setNewTransStatus( const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_( "setTransStatus" ) );

   DString dstrVerifyCancel( NO );

   getWorkSession().getOption (ifds::VerCancTrd, dstrVerifyCancel, BF::HOST, false);
   if (dstrVerifyCancel == YES)
   {
      setFieldNoValidate (ifds::TranStatus, UNVERIFIED, idDataGroup, false, false, true);	
   }
   else
   {
      //Need to call a new function here which returns a bool if trans status to be set to
      //verifieddilutioncalc required.
	  if(bIsRefundCalcReq(idDataGroup))
	  {
	     setFieldNoValidate (ifds::TranStatus, VERIFIED_AND_REFUNDCALCREQ , idDataGroup, false, false, true);
	  }
      else
	  {
		  setFieldNoValidate (ifds::TranStatus, VERIFIED, idDataGroup, false, false, true);
	  }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TransCancel::setTransNum( const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_( "setTransNum" ) );	

   setFieldRequired (ifds::TransNum, idDataGroup, true );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool TransCancel::isModifiableBasedOnStatus( const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("isModifiableBasedOnStatus"));

   bool bModifiable = true;

   DString dstrTranStatus;
   getField( ifds::TranStatus,    dstrTranStatus, idDataGroup, false );
    
   if( VERIFIED == dstrTranStatus || VERIFIED_AND_REFUNDCALCREQ == dstrTranStatus )
   {
      bModifiable = false;
   }
   return bModifiable;
}

//******************************************************************************
bool TransCancel::isIndividualTransCancelAllowed()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isIndividualTransCancelAllowed" ) );	

   return getWorkSession().hasReadPermission( UAF::TRANCE_CANCELLATION );
}

//******************************************************************************
void TransCancel::setSuppressIndicatorsPerm(const BFDataGroupId &idDataGroup)
{
   if (getWorkSession ().hasUpdatePermission(UAF::MCH_AND_SECUR_REC_FILE_INDICATOR))
   {
      setFieldReadOnly( ifds::MCHFileIndicator,	idDataGroup, false );
      setFieldReadOnly( ifds::SecRecFileIndicator,	idDataGroup, false );
   }
   else
   {
      setFieldReadOnly( ifds::MCHFileIndicator,	idDataGroup, true );
      setFieldReadOnly( ifds::SecRecFileIndicator,	idDataGroup, true );
   }
}

//******************************************************************************
bool TransCancel::areSuppressIndicatorsModifiableBasedOnStatus( const BFDataGroupId &idDataGroup)
{
   return isModifiableBasedOnStatus(idDataGroup);
}

//******************************************************************************
SEVERITY TransCancel::setSuppressIndicatorsReadOnlyFlags(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_( "setSuppressIndicatorsReadOnlyFlags" ) );	

   DString dstrModPerm;

   bool bVerification = getWorkSession().hasReadPermission( UAF::VERIFY_CANCEL_INSTRUCTION ); 
   getField( ifds::ModPermission, dstrModPerm, idDataGroup, false );
   dstrModPerm.stripAll();

   if ((!areSuppressIndicatorsModifiableBasedOnStatus(idDataGroup)) || 
         (!getWorkSession ().hasUpdatePermission(UAF::MCH_AND_SECUR_REC_FILE_INDICATOR)) ||
         (dstrModPerm == I_("1") && !isIndividualTransCancelAllowed()) ||
         (dstrModPerm == I_("2") && !bVerification))
   {
      setFieldReadOnly( ifds::MCHFileIndicator,	idDataGroup, true );
      setFieldReadOnly( ifds::SecRecFileIndicator,	idDataGroup, true );
   }
   else
   {
      setFieldReadOnly( ifds::MCHFileIndicator,	idDataGroup, false );
      setFieldReadOnly( ifds::SecRecFileIndicator,	idDataGroup, false );
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TransCancel::setDefaultSuppressIndicators(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_( "setDefaultSuppressIndicators" ) );

   DString dstrMCHIndCancel, dstrSRIndCancel;

   getWorkSession().getOption ( ifds::MCHIndCancel, dstrMCHIndCancel, BF::HOST, false);
   getWorkSession().getOption ( ifds::SRIndCancel, dstrSRIndCancel, BF::HOST, false);

   setFieldNoValidate( ifds::MCHFileIndicator,		dstrMCHIndCancel,		idDataGroup, false, true, false, false);
   setFieldNoValidate( ifds::SecRecFileIndicator,	dstrSRIndCancel,	idDataGroup, false, true, false, false);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TransCancel::setSuppressIndicatorsSet(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_( "setSuppressIndicatorsSet" ) );	

   BFProperties *pBFProperties;
   DString dstrSuppressIndicatorSubst;

   pBFProperties = getFieldProperties (ifds::MCHFileIndicator, idDataGroup);
   pBFProperties->getAllSubstituteValues (dstrSuppressIndicatorSubst);
   dstrSuppressIndicatorSubst = removeItemFromSubtList( dstrSuppressIndicatorSubst, SUPPRESS_INDICATOR_DEFAULT_CODE );   
   setFieldAllSubstituteValues( ifds::MCHFileIndicator, 
                                idDataGroup, 
                                dstrSuppressIndicatorSubst );

   pBFProperties = getFieldProperties (ifds::SecRecFileIndicator, idDataGroup);
   pBFProperties->getAllSubstituteValues (dstrSuppressIndicatorSubst);
   dstrSuppressIndicatorSubst = removeItemFromSubtList( dstrSuppressIndicatorSubst, SUPPRESS_INDICATOR_DEFAULT_CODE );   
   setFieldAllSubstituteValues( ifds::SecRecFileIndicator, 
                                idDataGroup, 
                                dstrSuppressIndicatorSubst );

   return GETCURRENTHIGHESTSEVERITY();

}
//******************************************************************************
SEVERITY TransCancel::setSuppressIndicatorsInactive(const BFDataGroupId &idDataGroup, const bool isNew)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_( "setSuppressIndicatorsInactive" ) );	

   if (isNew)
   {
      setFieldNoValidate( ifds::MCHFileIndicator,		SUPPRESS_INDICATOR_DEFAULT_CODE,	idDataGroup, false, true, false, false);
      setFieldNoValidate( ifds::SecRecFileIndicator,	SUPPRESS_INDICATOR_DEFAULT_CODE,	idDataGroup, false, true, false, false);
   }

   setFieldReadOnly( ifds::MCHFileIndicator,	idDataGroup, true );
   setFieldReadOnly( ifds::SecRecFileIndicator,	idDataGroup, true );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TransCancel::initBatchList (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initBatchList" ) );	

   getWorkSession().getBatchList (pBatchInfoList, idDataGroup);
   DString firstBatch;

   if (pBatchInfoList)
   {
      DString batchList,
         originalBatch;

      getField (ifds::Batch, originalBatch, idDataGroup);
      pBatchInfoList->getSubstitionList(batchList, originalBatch, idDataGroup, firstBatch);
      setFieldAllSubstituteValues (ifds::Batch, idDataGroup, batchList);
   }

   DString autoBatch;

   getWorkSession().getOption( ifds::AutoBatch, autoBatch, idDataGroup, false );

   bool bReadOnly = autoBatch.asInteger () !=  AUTO_BATCHING ? true : false;

   if (bReadOnly && !firstBatch.empty ())
   {
      setFieldNoValidate (ifds::Batch, firstBatch, idDataGroup, false);
   }
   setFieldReadOnly (ifds::Batch, idDataGroup, bReadOnly);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TransCancel::doValidateAll ( const BFDataGroupId &idDataGroup, 
                                      long lValidateGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "doValidateAll" ) );
   DString strGrantExists,
      strTrfResubmit,
      strIsAGrantTrade,
      strBatch,
      strSettleBatch,
      strBatchPrefix,
      strSettleBatchPrefix;

   getField( ifds::GrantExists, strGrantExists, idDataGroup, false );
   getField( ifds::TrfResubmit, strTrfResubmit, idDataGroup, false );
   getField( ifds::IsAGrantTrade, strIsAGrantTrade, idDataGroup, false );
   getField( ifds::Batch, strBatch, idDataGroup, false );
   getField( ifds::SettleBatch, strSettleBatch, idDataGroup, false );

   if( strGrantExists.strip().upperCase() == I_("Y") )
   {
      ADDCONDITIONFROMFILE( CND::WARN_GRANT_ASSOC_WITH_TRADE );
   }

   if( strTrfResubmit.strip().upperCase() == I_("Y") )
   {
      ADDCONDITIONFROMFILE( CND::WARN_TRANFER_TANSACTION_RESUBMITTED );
   }

   if( strIsAGrantTrade.strip().upperCase() == I_("Y") )
   {
      ADDCONDITIONFROMFILE( CND::WARN_TRADE_IS_A_GRANT );
   }
   strBatchPrefix = strBatch.strip().upperCase().left(2);
   strSettleBatchPrefix = strSettleBatch.strip().upperCase().left(2);
   
   if(DSTCommonFunctions::codeInList( strSettleBatchPrefix, I_("SP,DC") ) &&
      strBatchPrefix != strSettleBatchPrefix)
   {
        getErrMsg (IFASTERR::CANCEL_BATCH_MUST_BE_PREFIXED_SP_DC,
                   CND::ERR_CANCEL_BATCH_MUST_BE_PREFIXED_SP_DC, 
                   CND::WARN_CANCEL_BATCH_MUST_BE_PREFIXED_SP_DC, 
                   idDataGroup);
   }
   
   validateRESPInfoUpdate(idDataGroup);
   DString dstrEventReceiptDate,dstrEventReceiptTime;
   getField(ifds::EventReceiptDate, dstrEventReceiptDate, idDataGroup, false);
   getField(ifds::EventReceiptTime, dstrEventReceiptTime, idDataGroup, false);
   if(dstrEventReceiptDate.stripAll().empty() && dstrEventReceiptTime.stripAll().empty()&&
	  GETCURRENTHIGHESTSEVERITY() <= WARNING ) //Display the warning first and assign the systime and date.
   {
    getErrMsg ( IFASTERR::EVENT_RECIEPT_DATE_AND_TIME_EMPTY,
				 CND::ERR_EVENT_RECIEPT_DATE_AND_TIME_EMPTY,
                 CND::WARN_EVENT_RECIEPT_DATE_AND_TIME_EMPTY,                     
                 idDataGroup); 
   }
   DString dstrTransType;
   getField(ifds::TransType, dstrTransType, idDataGroup, false);
   if((TRADETYPE::ROLLOVER_EXCHANGE_IN == dstrTransType || 
	   TRADETYPE::ROLLOVER_EXCHANGE_OUT ==  dstrTransType )&& 
	   accountHasTradeAfterTradeDate(idDataGroup))
   {
	DString dstrAccountNum;
	getParent()->getField(ifds::AccountNum, dstrAccountNum, idDataGroup, false);
	MFAccount *pMFAccount = NULL;
    if(getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING &&
       pMFAccount)
	{
	 if(pMFAccount->isAccountOmnibus(dstrAccountNum, idDataGroup))
	 {
	  getErrMsg ( IFASTERR::TRADE_EXITS_IN_OMNIBUS_ACCT,
				  CND::ERR_TRADE_EXITS_IN_ACCT,
				  CND::WARN_TRADE_EXITS_IN_ACCT, 
				  idDataGroup);
	 }
	 else
	 {
	  getErrMsg ( IFASTERR::TRADE_EXITS_IN_ACCT,
				 CND::ERR_TRADE_EXITS_IN_ACCT,
				 CND::WARN_TRADE_EXITS_IN_ACCT, 
				 idDataGroup);
	 }
	}
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*************************************************************************************************
SEVERITY TransCancel::validateRESPInfoUpdate ( const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateRESPInfoUpdate"));
   
   DString dstrTransType;
   getField(ifds::TransType, dstrTransType, idDataGroup, false);
   dstrTransType.strip().upperCase();
   
   if((!getWorkSession().isQESIClient()) || dstrTransType == I_("ID"))
      return GETCURRENTHIGHESTSEVERITY();
   
   DString dstrAccountNum, dstrTransId;
   
   getParent()->getField(ifds::AccountNum, dstrAccountNum, idDataGroup, false);
   getParent()->getField(ifds::TransId, dstrTransId, idDataGroup, false);
   
   RESPInfoUpdateValidationList *pRESPInfoUpdateValidationList = NULL;     

   pRESPInfoUpdateValidationList = new RESPInfoUpdateValidationList (*this);
   if ( pRESPInfoUpdateValidationList->init ( dstrAccountNum,
                                              dstrTransId,
                                              NULL_STRING,
                                              NO,
                                              I_("CANTRADE"),
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
         else if ( dstrWarnCode == IFASTERR::TRADE_EXIST_FOR_TAX_YEAR )
         {
            getErrMsg ( dstrWarnCode,
                        CND::ERR_TRADE_EXIST_FOR_TAX_YEAR, 
                        CND::WARN_TRADE_EXIST_FOR_TAX_YEAR, 
                        idDataGroup );
         }
         else if( dstrWarnCode == IFASTERR::SYS_TRIG_AMEND_AND_RECAL_QESI_NOTIONAL_BALANCE )
         {
            getErrMsg ( dstrWarnCode,
                        CND::ERR_SYS_TRIG_AMEND_AND_RECAL_QESI_NOTIONAL_BALANCE, 
                        CND::WARN_SYS_TRIG_AMEND_AND_RECAL_QESI_NOTIONAL_BALANCE, 
                        idDataGroup );
         }
         ++iter;
      }

   }

   delete pRESPInfoUpdateValidationList;
   pRESPInfoUpdateValidationList = NULL;

   return GETCURRENTHIGHESTSEVERITY (); 
}

/******************************************************************************
 Input: BFDataGroupId
 OutPut:none
 Return:Bool
 Functionality:Returns Dilution Claculation is required or not based on below condition
               1.FundClass Overide allows right to cancel.
               2.The selected RVCD is in the list of RVCD code returend by VW149
 ******************************************************************************/
bool TransCancel::bIsRefundCalcReq( const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
		CLASSNAME, 
		I_("bIsRefundCalcReq"));
	//if the transtype id ED...This is allowed for PAC only
	DString dstrTransType,dstrRvcd,dstrRVCDSet,dstrRuleSet,dstrRefundCalcRequired = I_("N");
	bool bRefundCalcReq = false;
	
	getField(ifds::TransType, dstrTransType, idDataGroup, false);
	dstrTransType.strip().upperCase();
	
	getField(ifds::RvCode, dstrRvcd, idDataGroup, false);
	getWorkSession().getOption (ifds::RefundRVCD, dstrRVCDSet, BF::HOST, false);
	
	if(!dstrRvcd.empty())
	{
		if( isCodeInList(dstrRvcd, dstrRVCDSet)&& (I_("ED") == dstrTransType) )//only for PAC and Purchase
		{
			FundLmtOverrideList	*pFundLmtOverrideList = NULL;
			if(getFundLmtOverrideList ( pFundLmtOverrideList,idDataGroup) <= WARNING && 
				pFundLmtOverrideList )
			{
				bRefundCalcReq = bIsRuleTypeEnabled4FundLimit(pFundLmtOverrideList,
															  RVCDCODEALLOWEDFORREFUND::RIGHT_TO_CANCEL_RULE,
															  idDataGroup);	
				if( !bRefundCalcReq )
				{
					ADDCONDITIONFROMFILE( CND::ERR_RIGHT_TO_CANCEL_NOTALLWD);
				}
			}
		}
		else if(RVCDCODEALLOWEDFORREFUND::RIGHT_TO_CANCEL == dstrRvcd && !bRefundCalcReq )
		{
			ADDCONDITIONFROMFILE( CND::ERR_RIGHT_TO_CANCEL_NOTALLWD);
		}
	}
	return bRefundCalcReq;
}
// ******************************************************************************
bool TransCancel::isRefundOptAndPayTypeAvailable( const BFDataGroupId &idDataGroup,DString &stopFlag,DString &defaultRefundOption)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
		CLASSNAME, 
		I_("isRefundOptAndPayTypeAvailable"));
	
	DString dstrTransType,dstrRvcd,dstrRVCDSet,dstrRuleSet;
	bool bRefundOptAndPayTypeAvailable = false;
	
	getField(ifds::TransType, dstrTransType, idDataGroup, false);
	dstrTransType.strip().upperCase();
	
	getField(ifds::RvCode, dstrRvcd, idDataGroup, false);
	getWorkSession().getOption (ifds::RefundRVCD, dstrRVCDSet, BF::HOST, false); 
	
	if(!dstrRvcd.empty())
	{
		if( isCodeInList(dstrRvcd, dstrRVCDSet)&& (I_("ED") == dstrTransType) )//only for PAC and Purchase
		{
			FundLmtOverrideList	*pFundLmtOverrideList = NULL;
			if(getFundLmtOverrideList ( pFundLmtOverrideList,idDataGroup) <= WARNING && pFundLmtOverrideList )
			{
				FundLmtOverride *pFundLmtOverride = NULL;
				
				DString dstrAccountNum;
				getParent()->getField(ifds::AccountNum, dstrAccountNum, idDataGroup, false);
				dstrAccountNum.strip();
				
				if(!dstrAccountNum.empty())
				{  
					if (	pFundLmtOverrideList != NULL &&  
							pFundLmtOverrideList->getFundLmtOverride ( getWorkSession(), 
																	   dstrAccountNum,
																	   RVCDCODEALLOWEDFORREFUND::RIGHT_TO_CANCEL_RULE,
																	   pFundLmtOverride,
																	   idDataGroup) <= WARNING )
                    {
						if( pFundLmtOverride )
						{
							bRefundOptAndPayTypeAvailable = true;
							
							pFundLmtOverride->getField (ifds::StopFlag, stopFlag, idDataGroup, false);
							stopFlag.strip().upperCase();
							
							pFundLmtOverride->getField (ifds::MinInitAmt, defaultRefundOption, idDataGroup, false);
							defaultRefundOption.strip();  		 
						}
					}
				}		
			}
		}
	}
	return bRefundOptAndPayTypeAvailable;
}

/******************************************************************************
 Input: BFDataGroupId
 OutPut:none
 Return:SEVERITY
 Functionality:Sets the RefundRVCD related fields enabled or disabled if the 
               reversal code selected is in the Genric Control List	and the default 
			   values based on Tax type for the fields.
 ******************************************************************************/
SEVERITY TransCancel::SetRefundRVCDFields(const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
		CLASSNAME, 
		I_("SetRefundRVCDFields"));
		
	DString stopFlag = I_(""),
			defaultRefundOption = I_(""), 
			dstrRefundOptionAvailable = I_("");
	
	bool bRefundOptAndPayTypeAvailable	= isRefundOptAndPayTypeAvailable(idDataGroup, stopFlag, defaultRefundOption);
	bool bRefundOptionEnabled			= bRefundOptAndPayTypeAvailable && (stopFlag == I_("Y"));
	
	int iPosition = defaultRefundOption.find(I_("."));
	defaultRefundOption = defaultRefundOption.substr(0,iPosition);
	if( !defaultRefundOption.empty() )
		defaultRefundOption = I_("0") + defaultRefundOption;
	
	setFieldNoValidate( ifds::RefundOption ,defaultRefundOption,idDataGroup);
	setFieldReadOnly (ifds::RefundOption,idDataGroup,!bRefundOptionEnabled);

	if( bRefundOptAndPayTypeAvailable )
	{
		DString dstrAccountNum;
		getParent()->getField(ifds::AccountNum, dstrAccountNum, idDataGroup, false);
		MFAccount *pMFAccount = NULL;
		
		if(  !dstrAccountNum.empty() && 
			getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING && 
			pMFAccount)
		{			
			if(pMFAccount->bIsTaxTypeRelatedtoRegAgent(idDataGroup))
			{
				setFieldNoValidate( ifds::RefundPayType,RefundPayType::REDIRECT_RA,idDataGroup, false);
			}
			else
			{
				setFieldNoValidate( ifds::RefundPayType,RefundPayType::MANUAL,idDataGroup, false);
			}
		}
	}
	else   
	{
		setFieldNoValidate( ifds::RefundPayType,NULL_STRING,idDataGroup, false);
	}
	setFieldReadOnly (ifds::RefundPayType,idDataGroup,!bRefundOptAndPayTypeAvailable);
	setNewTransStatus(idDataGroup);//call this because you need to change the status based on the rvcd selected
	
	return GETCURRENTHIGHESTSEVERITY (); 
}

/******************************************************************************
 Input: FundLimitOverideList ,BFDataGroupId
 OutPut:FundLimitOverideList
 Return:SEVERITY
 Functionality:Output the fundlimitoveridelist
 ******************************************************************************/
SEVERITY TransCancel::getFundLmtOverrideList ( FundLmtOverrideList *&pFundLmtOverrideList, 
											  const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
		CLASSNAME, 
		I_("getFundLmtOverrideList"));
	pFundLmtOverrideList = NULL;

	DString transType,
		overrideExists,
		fundCode,
		classCode,dstrFundNumber;
	
	
	getField( ifds::rxFundCode, fundCode, idDataGroup, false );
	getField( ifds::rxClassCode, classCode, idDataGroup, false );

	if(!fundCode.empty() && !classCode.empty())
	{
		getField (ifds::TransType, transType, idDataGroup);
		//check cbobase to see if we've already built it
		//if not built, create and store with base
		DString strKey = I_("FundLmtOverrideList");
		strKey += I_(";FundCode=") + fundCode + I_(";ClassCode=") + classCode; 
		pFundLmtOverrideList = 
			dynamic_cast<FundLmtOverrideList *>(BFCBO::getObject(strKey, idDataGroup));

		if (!pFundLmtOverrideList )
		{
			pFundLmtOverrideList = new FundLmtOverrideList (*this);
			if (pFundLmtOverrideList->init (fundCode, classCode, transType) <= WARNING)
			{
				setObject (pFundLmtOverrideList, strKey, OBJ_ACTIVITY_NONE, idDataGroup);          
			}
			else
			{
				delete pFundLmtOverrideList;
				pFundLmtOverrideList = NULL;
			}
		}  
	}
	return GETCURRENTHIGHESTSEVERITY();
}
/******************************************************************************
 Input: FundLimitOverideList,const RuleType,BFDataGroupId
 OutPut:None
 Return:bool
 Functionality:Output the fundlimitoveridelist has got the Ruletype Stop flag enabled
 ******************************************************************************/
bool TransCancel::bIsRuleTypeEnabled4FundLimit(FundLmtOverrideList *pFundLmtOverrideList,
												   const DString ruleType,
												   const BFDataGroupId &idDataGroup)
{
	bool bRuleTypeEnabled = false;

	DString dstrAccountNum;
	FundLmtOverride *pFundLmtOverride = NULL;
	getParent()->getField(ifds::AccountNum, dstrAccountNum, idDataGroup, false);
	dstrAccountNum.strip();
	if(!dstrAccountNum.empty())
	{  
		if ( pFundLmtOverrideList != NULL &&  pFundLmtOverrideList->getFundLmtOverride ( getWorkSession(), 
			dstrAccountNum,ruleType,pFundLmtOverride,idDataGroup) <= WARNING )
		{
			if( pFundLmtOverride )
			{
				bRuleTypeEnabled = true;
			}
		}
	}
	return bRuleTypeEnabled; 
}
/******************************************************************************
 Input: idDataGroup
 OutPut:None
 Return:bool
 Functionality:returns true if EventReceiptDate & EventReciptTime is Applicable. 
 ******************************************************************************/
bool TransCancel::bIsEventReceiptDateTimeAppl(const BFDataGroupId &idDataGroup)
{
   DString dstrTransType,dstrUCITSEnv;
   bool bEventReceiptDateTimeAppl   = false;
   getWorkSession().getOption(ifds::UCITFlag, dstrUCITSEnv, idDataGroup, false );
   dstrTransType = _dstrTransType  ;
   //getField(ifds::TransType, dstrTransType, idDataGroup, false);
   dstrTransType.strip().upperCase();
   bEventReceiptDateTimeAppl =  (( dstrUCITSEnv == YES) &&
					            ( DSTCommonFunctions::codeInList (dstrTransType, TRADETYPE::PURCHASE_LIKE)   || 
                                  DSTCommonFunctions::codeInList (dstrTransType, TRADETYPE::REDEMPTION_LIKE) || 
								  DSTCommonFunctions::codeInList (dstrTransType, TRADETYPE::EXCHANGE_LIKE)   ));
   return   bEventReceiptDateTimeAppl;
}
/******************************************************************************
 Input: BFDataGroupId
 OutPut:None
 Return:bool
 Functionality:Return true if the account has subsequent trades after the trade 
			   date including pending and processed
 ******************************************************************************/
bool TransCancel::accountHasTradeAfterTradeDate(const BFDataGroupId &idDataGroup)
{
 MFAccount *pMFAccount = NULL;
 bool bTradeExists = false;
 bool bFound = false;
 DString dstrAccountNum;
 TransCancellist *pTransCancellist = dynamic_cast <TransCancellist*> (getParent());
 getParent()->getField(ifds::AccountNum, dstrAccountNum, idDataGroup, false);  
 if(getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING &&
    pMFAccount && pTransCancellist)
 {
  if(getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING &&
	 pMFAccount)
   {
	 if( pMFAccount->accountHasTradeAfterDate( pTransCancellist->getFund(), 
											   pTransCancellist->getClass(),
											   pTransCancellist->getTradeDate(), 
											   idDataGroup))
	     bTradeExists = true;
    }
 }
 return bTradeExists;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TransCancel.cpp-arc  $
// 
//    Rev 1.46   May 29 2012 13:46:58   wp040027
// IN 2956475 – Enabling RefundPayType for Rule type 49
// 
//    Rev 1.45   May 18 2012 10:18:44   wp040027
// IN2959343 CPF-FKR-Redemption Trade
// 
//    Rev 1.44   May 07 2012 14:28:00   wp040027
// PETP0187485-CPF-Trade Cancellation
// 
//    Rev 1.43   Apr 13 2012 12:52:32   popescu
// Incident 2900100 - fixed bulk/cancelation issues related to the batch field being mandatory
// 
//    Rev 1.42   Sep 06 2011 16:19:36   wutipong
// IN2426017 - RESP_Rebooked CESG Transaction Details -- Default CancelGrant to Yes when the transaction is Grant
// 
//    Rev 1.41   Apr 05 2011 06:50:44   kitticha
// PETP0181067_FN00_IN2460780_Empire Autobatch Development on Cancelled SP and DC trades.
// 
//    Rev 1.40   Jan 06 2011 02:44:18   dchatcha
// IN#2381736 - P0165541FN12 - Missing Warning message upon trade cancellation.
// 
//    Rev 1.39   Oct 29 2010 05:39:06   kitticha
// PET0165541 FN03 - QESI Phase3.
// 
//    Rev 1.38   Jun 01 2010 23:34:22   dchatcha
// IN#2128812 - PETP0165541 FN 01 - Cancellation of processed transaction for RESP Accounts.
// 
//    Rev 1.37   Apr 15 2010 00:00:48   popescu
// PET165541_FN01_QESI - RESP Gap_Dsk_Trading
// 
//    Rev 1.36   Nov 05 2009 05:31:18   dchatcha
// IN# 1897496 - RESP Date not defaulted to Trade date when original trade is cancelled.
// 
//    Rev 1.35   Sep 15 2009 17:47:12   popescu
// Incident 1835113 - error canceling a trade in SSBG second fix.
// 
//    Rev 1.34   Sep 14 2009 19:28:04   popescu
// Incident 1835113 - error canceling a trade in SSBG
// 
//    Rev 1.33   May 26 2009 14:18:46   jankovii
// PET 159770 FN05 Auto Batching.
// 
//    Rev 1.32   May 14 2009 13:39:28   jankovii
// PET 159770 FN05 Auto Batching.
// 
//    Rev 1.31   Jan 16 2008 17:55:42   wongsakw
// Incident 1142459 - Invalid Cancel Receipt
// 
//    Rev 1.30   Dec 11 2007 15:54:52   wongsakw
// PET2360 FN60 -- Automatically Canel Contribution Reciept
// 
//    Rev 1.29   Nov 02 2007 11:29:06   jankovii
// IN #1057653 - trade cancellation using split dilution.
// 
//    Rev 1.28   12 Oct 2007 13:47:18   kovacsro
// IN#1037783 - RvCode not required when there's a dilution allocation in place
// 
//    Rev 1.27   Nov 14 2006 16:50:40   porteanm
// Incident 676881 - Pass TransType to 338 (TransCancel).
// 
//    Rev 1.26   Mar 10 2006 13:51:18   porteanm
// Incident 563764 - TradeDate/SettleDate validation support for a cancelled transaction.
// 
//    Rev 1.25   Mar 06 2006 16:21:18   ZHANGCEL
// PET1334 - FN01 -- Code clean up
// 
//    Rev 1.24   Mar 02 2006 17:34:02   ZHANGCEL
// PET1334 - FN01 -- ESG Settlement enhancement
// 
//    Rev 1.23   Jan 12 2006 15:57:18   zhengcon
// PET1295_FN01: Trade Suppress Indicator for MCH and SR Files -- Trade Cancellation: Individual and rebook 
// 
//    Rev 1.22   Nov 26 2005 17:32:36   porteanm
// PET1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.21   Nov 23 2005 17:14:16   porteanm
// PET1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.20   Nov 12 2005 13:44:48   porteanm
// PET 1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.19   Nov 12 2005 11:54:12   porteanm
// PET 1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.18   Nov 11 2005 17:16:50   porteanm
// PET 1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.17   Nov 09 2005 19:51:40   porteanm
// PET 1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.16   Nov 08 2005 19:17:34   porteanm
// PET 1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.15   Nov 06 2005 13:57:20   porteanm
// PET 1286 FN01 - Bulk Cancellation - work in progress.
// 
//    Rev 1.14   Sep 01 2005 16:53:50   popescu
// Incident# 388632 - trans cancel screen code overhaul
// 
//    Rev 1.13   Sep 01 2005 14:02:16   popescu
// Incident# 388632 - trans cancel screen code overhaul
// 
//    Rev 1.12   Aug 10 2005 17:17:06   Fengyong
// Incident 370336 - make error message consistent
// 
//    Rev 1.11   Aug 04 2005 10:21:42   Fengyong
// Incident 349214 - do not allow set percent for one dilution record.
// 
//    Rev 1.10   Jul 29 2005 11:57:50   Fengyong
// Incident 331149 - TransCancel and dilution have different sub list for revcode and backdatereason
// 
//    Rev 1.9   Jul 20 2005 13:59:30   winnie
// Sync up fixes for incident 325606 in rel 63. Reversal code should always be mandatory as it was in version 1.6. Only copy Reversal code to Backdated reason in dilution if it is not a split dilution cancellation (i.e. accountable is not blank). Dilution is applicable if ifds::SplitAcCode is Y. Ensure Accountable is not missing if control ifds::AccountableMandatory is active
// 
//    Rev 1.8   Jul 08 2005 09:34:04   Yingbaol
// PET1235,FN01:transaction cancellation rebook
// 
//    Rev 1.7   Jun 15 2005 14:45:12   ZHANGCEL
// Incident #322193 - Add logic to set  BackDatedReason into RvCode  fields
// 
//    Rev 1.6   Apr 28 2005 16:27:48   Fengyong
// #Incident 299957 - accountable code mandatory when there is no dilution.
// 
//    Rev 1.5   Apr 20 2005 17:11:20   Fengyong
// #incident 293411 - can not enter 0 percent dilution allocation
// 
//    Rev 1.4   Apr 15 2005 16:34:38   Fengyong
// Incident #290591 - Avoid unexpecting error message.
// 
//    Rev 1.3   Apr 01 2005 13:42:00   Fengyong
// PET1190 FN05 - add condition accountable required
// 
//    Rev 1.2   Mar 16 2005 18:35:20   Fengyong
// PET1190FN05 - after restrore button clicked, do not allow modify
// 
//    Rev 1.1   Mar 16 2005 16:45:04   Fengyong
// PET1190 FN05 - remove getstrKey function
*/
