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
//    Copyright 1999 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : TransactionDetails.cpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 03/20/99
//
// ^CLASS    : TransactionDetails
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"

#include "acctsettlementinstrlist.hpp"
#include "bankinstructions.hpp"
#include "broker.hpp"
#include "datevalidation.hpp"
#include "deductionlist.hpp"
#include "distributionbankinstructionslist.hpp"
#include "distributorbankinstructionslist.hpp"
#include "distributorrepository.hpp"
#include "dstcommonfunction.hpp"
#include "externalinstitutionlist.hpp"
#include "fundmasterlist.hpp"
#include "fundmgmtsettlementinstrlist.hpp"
#include "intermediarylist.hpp"
#include "intermediary.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"
#include "segtradeentryvalidation.hpp"
#include "splitcommissionlist.hpp"
#include "tradeacctalloclist.hpp"
#include "tradefromfundalloclist.hpp"
#include "tradepayinstructlist.hpp"
#include "tradepayinstruct.hpp"
#include "tradesettlementlocationslist.hpp"
#include "transactiondetails.hpp"
#include "transactiondetailsbankinstructionslist.hpp"
#include "transactionlinklist.hpp"
#include "transactionupdate.hpp"
#include "estateallocationlist.hpp"
#include "funddetaillist.hpp" 
#include "fundlmtoverridelist.hpp"
#include "FundDetail.hpp"

#include <ifastdataimpl\dse_dstc0017_vw.hpp>
#include <ifastdataimpl\dse_dstc0022_req.hpp>
#include <ifastdataimpl\dse_dstc0022_vw.hpp>
#include <ifastdataimpl\dse_dstc0436_vw.hpp>
#include <ifastdataimpl\dse_dstc0149_vw.hpp> //P0186486_FN15_The Source of Funds

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest TRANSACTION_DETAILS;
}

namespace DATE_VALIDATION
{
   extern const I_CHAR * const DEFAULT_VALUE_DATE;
}

namespace RVCDCODEALLOWEDFORREFUND
{
	const I_CHAR * const RIGHT_TO_CANCEL	  = I_("82");
	const I_CHAR * const RIGHT_TO_CANCEL_RULE = I_("49");
}

namespace
{
   // Trace literals
   const I_CHAR * CLASSNAME               = I_( "TransactionDetails" );
   const I_CHAR * CASH                    = I_( "CASH" );
   const I_CHAR * YES                     = I_( "Y" );
   const I_CHAR * NO                      = I_( "N" );
   const I_CHAR * EFT                     = I_( "E" );
   const I_CHAR * DIRECT                  = I_( "D" );
   const I_CHAR * DIRECT_DEPOSIT          = I_( "D1" );
   const I_CHAR * IW                      = I_( "I" );
   const I_CHAR * WIRE                    = I_( "WIRE" );
   const I_CHAR * CHEQUE                  = I_( "CHQ" );
   const I_CHAR * SUPPRESS                = I_( "X" );

   const I_CHAR * VERIFIED                = I_( "02" );
   const I_CHAR * SRC_OF_FUND_MATUR_PW    = I_( "AR" );   
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const VERIFY_CANCEL_INSTRUCTION;
   extern CLASS_IMPORT I_CHAR * const TRANCE_CANCELLATION;
}

namespace PAYMENT_FOR
{
   extern const I_CHAR * REDEMPTION;
}

namespace AcctUseCode
{
   extern const I_CHAR * const EFT_REDEMPTION;
   extern const I_CHAR * const DEFAULT;
}

namespace PAY_TO
{
   extern I_CHAR * const BROKER;
   extern I_CHAR * const BRANCH;
   extern I_CHAR * const SALESREP;
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFNumericFieldId AccountTo;
   extern CLASS_IMPORT const BFTextFieldId FromCurrency;
   extern CLASS_IMPORT const BFTextFieldId ToCurrency;
   extern CLASS_IMPORT const BFTextFieldId AmountType;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFTextFieldId AllocAmtType;
   extern CLASS_IMPORT const BFTextFieldId Cancellation;
   extern CLASS_IMPORT const BFTextFieldId VerCancTrd;
   extern CLASS_IMPORT const BFTextFieldId AcctDesignation;
   extern CLASS_IMPORT const BFTextFieldId SWPSettleESGElig;
   extern CLASS_IMPORT const BFTextFieldId InterCode;
   extern CLASS_IMPORT const BFTextFieldId PayToEntity;
   extern CLASS_IMPORT const BFTextFieldId BrokerCode;
   extern CLASS_IMPORT const BFTextFieldId BranchCode;
   extern CLASS_IMPORT const BFTextFieldId Slsrep;
   extern CLASS_IMPORT const BFTextFieldId AcctUseCode;
   extern CLASS_IMPORT const BFTextFieldId BankAcctCurrency;
   extern CLASS_IMPORT const BFTextFieldId IsCancelModSEGTradeAllowed;
   extern CLASS_IMPORT const BFTextFieldId GuaranteeCalcByRules;
   extern CLASS_IMPORT const BFTextFieldId SrcOfFund; //P0186486_FN15_The Source of Funds
   extern CLASS_IMPORT const BFTextFieldId SrcOfFunds_IA; 
   extern CLASS_IMPORT const BFTextFieldId CUSIP;
   extern CLASS_IMPORT const BFTextFieldId TDCC;
   extern CLASS_IMPORT const BFTextFieldId Valoren;
   extern CLASS_IMPORT const BFTextFieldId ToCUSIP;
   extern CLASS_IMPORT const BFTextFieldId ToTDCC;
   extern CLASS_IMPORT const BFTextFieldId ToValoren;
   extern CLASS_IMPORT const BFTextFieldId TradeRestriction;
   extern CLASS_IMPORT const BFTextFieldId TradeRestrictionReason;
   extern CLASS_IMPORT const BFTextFieldId IsEPATrade;
   extern CLASS_IMPORT const BFTextFieldId SourceOfTrade;
   extern CLASS_IMPORT const BFTextFieldId ChannelOfTrade;
   extern CLASS_IMPORT const BFTextFieldId Platform;
   extern CLASS_IMPORT const BFTextFieldId AdvisorFeeAppl;
   extern CLASS_IMPORT const BFTextFieldId TransTypeOverrideDescription;
   extern CLASS_IMPORT const BFTextFieldId Deconversion;
   extern CLASS_IMPORT const BFDateFieldId RDSPPaymtDate;
}

namespace CND
{  // Conditions used
   extern const long ERR_RECORD_VALUE_NOT_MATCH;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const REDEMPTION_LIKE;
   extern CLASS_IMPORT I_CHAR * const ADVISOR_FEE;
}

namespace SETL_LOC_FIELDS
{
  //From
   extern CLASS_IMPORT const  BFFieldId SttlInstrFrReadOnlyFields[];
   extern CLASS_IMPORT const int numSttlInstrFrReadOnlyFields;
   //To
   extern CLASS_IMPORT const  BFFieldId SttlInstrToReadOnlyFields[];
   extern CLASS_IMPORT const int numSttlInstrToReadOnlyFields;
   //Always read only
   extern CLASS_IMPORT const  BFFieldId SttlInstrReadOnlyAlways[];
   extern CLASS_EXPORT const int numSttlInstrReadOnlyAlways;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{  
   { ifds::FrSettlLocCode,             BFCBO::NONE,               0},
   { ifds::FrClearingMethod,           BFCBO::NONE,               0},
   { ifds::FrSettlInstrCode,           BFCBO::NONE,               0},
   { ifds::FrDeliveryTo,               BFCBO::NONE,               0},
   { ifds::FrInFavourOf,               BFCBO::NONE,               0},
   { ifds::FrForAccount,               BFCBO::NONE,               0},
   { ifds::FrCSDLocation,			   BFCBO::NONE,               0},
   { ifds::FrCSDAcctNum,			   BFCBO::NONE,               0},

   { ifds::ToSettlLocCode,             BFCBO::NONE,               0},
   { ifds::ToClearingMethod,           BFCBO::NONE,               0},
   { ifds::ToSettlInstrCode,           BFCBO::NONE,               0},
   { ifds::ToDeliveryTo,               BFCBO::NONE,               0},
   { ifds::ToInFavourOf,               BFCBO::NONE,               0},
   { ifds::ToForAccount,               BFCBO::NONE,               0},
   { ifds::ToCSDLocation,			   BFCBO::NONE,               0},
   { ifds::ToCSDAcctNum,			   BFCBO::NONE,               0},

   { ifds::TransType,                  BFCBO::NONE,               0},
   { ifds::Units,                      BFCBO::NONE,               0},
   { ifds::TradeDate,                  BFCBO::NONE,               0},
   { ifds::SettleDate,                 BFCBO::NONE,               0},
   { ifds::GrossAmt,                   BFCBO::NONE,               0},
   { ifds::NetAmt,                     BFCBO::NONE,               0},
   { ifds::AcqDiscountRate,            BFCBO::NONE,               0},
   { ifds::DiscountAmount,             BFCBO::NONE,               0},
   { ifds::OfferPrice,                 BFCBO::NONE,               0},
   { ifds::Cancellation,               BFCBO::CALCULATED_FIELD,   0},
   { ifds::IsCancelModSEGTradeAllowed, BFCBO::NOT_ON_HOST,        0},
   { ifds::SrcOfFund,                  BFCBO::NONE,         0 }, //P0186486_FN15_The Source of Funds
   { ifds::SrcOfFunds_IA,              BFCBO::NONE,         0 }, //P0186486_FN15_The Source of Funds
   { ifds::TradeRestriction,           BFCBO::NONE,         0 },
   { ifds::TradeRestrictionReason,     BFCBO::NONE,         0 },
   { ifds::IsEPATrade,                 BFCBO::NONE,         0 },
   { ifds::FrSettlementAccount,        BFCBO::NONE,              0 },
   { ifds::FrInternalSettlementAccount, BFCBO::NONE,             0 },
   { ifds::FrIntermediaryBank,         BFCBO::NONE,              0 },
   { ifds::FrCashMsgType,              BFCBO::NONE,              0 }, 
   { ifds::FrReceivingBank,            BFCBO::NONE,              0 },
   { ifds::FrBeneficiary,              BFCBO::NONE,              0 }, 
   { ifds::FrSpecialInstructions,      BFCBO::NONE,              0 },
   { ifds::ToSettlementAccount,        BFCBO::NONE,              0 },
   { ifds::ToInternalSettlementAccount, BFCBO::NONE,             0 },
   { ifds::ToIntermediaryBank,         BFCBO::NONE,              0 },
   { ifds::ToCashMsgType,              BFCBO::NONE,              0 }, 
   { ifds::ToReceivingBank,            BFCBO::NONE,              0 },
   { ifds::ToBeneficiary,              BFCBO::NONE,              0 }, 
   { ifds::ToSpecialInstructions,      BFCBO::NONE,              0 }, 
   { ifds::BidPrice,                   BFCBO::NONE,              0 },
   { ifds::ExternalInstitution,        BFCBO::NONE,              0 },
   { ifds::Deconversion,			   BFCBO::NONE,              0 },
   { ifds::RDSPPaymtDate,			   BFCBO::NONE,              0 }
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
   //  Object Label,                                  State Flags,      Group Flags 
   { I_("AccountAllocationList"),                   BFCBO::NONE,     0},
   { I_("FromFundAllocationList"),                  BFCBO::NONE,     0},
   { I_("TransactionDetails_BankInstructionsList"), BFCBO::NONE,     0},
};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );

//******************************************************************************
TransactionDetails::TransactionDetails( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent ),
_TransId( DString( NULL_STRING) ), 
pDeductionList_ (NULL ),
_AlreadyGotDetails( false )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );

   registerMemberData (NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       NUM_OBJECTS, (const CLASS_OBJECT_INFO *)&classObjectInfo);
}

//******************************************************************************
TransactionDetails::~TransactionDetails()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   if( pDeductionList_ != NULL )
   {
      delete pDeductionList_;
      pDeductionList_ = NULL;
   }
}

// if the details have not been get, it will go to get them
//******************************************************************************
SEVERITY TransactionDetails::getDetails( DString& TransId,
                                         const DString& dstrTrack,
                                         const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getDetails") );
   SEVERITY sevRtn = SEVERE_ERROR;

   if( !_AlreadyGotDetails )
   {
      _AlreadyGotDetails = true;

      BFData queryData(ifds::DSTC0022_REQ);
      BFData *response = new BFData(ifds::DSTC0022_VW);

      DString mgmtCoIdOut;
      queryData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
      queryData.setElementValue( ifds::TransId, TransId );
      queryData.setElementValue( ifds::Track, dstrTrack );
      queryData.setElementValue( ifds::Activity, dstrPageName );

      if( BFDataBroker::getInstance()->receive( DSTC_REQUEST::TRANSACTION_DETAILS, 
                                                queryData, 
                                                *response, 
                                                DSTCRequestor( getSecurity(), true, true) ) <= WARNING )
      {
         attachDataObject( *response, true, false );

         DString currency;
         getCurrency( BF::HOST, currency );

         pDeductionList_ = new DeductionList( *this );
         pDeductionList_->init( *response, currency );

         clearingRelatedChanges();
         initIsCancelModSEGTradeAllowed(BF::HOST);
         setSourceOfFundSubstList(BF::HOST); //P0186486_FN15_The Source of Funds
      }
      else
      {
         delete response;
         response = NULL;
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
SEVERITY TransactionDetails::getEstateAllocationList ( EstateAllocationList *&pEstateAllocationList, 
                                            const BFDataGroupId &idDataGroup, bool bReadOnly, bool bCreate) /*= true*/
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getEstateAllocationList"));

   DString dstrAccountNum;
   DString dstrTransId; 
   DString dstrAmount;
   DString dstrAmountType;
   DString dstrFund;
   DString dstrClass;
   DString dstrTradeDate;

   getField (ifds::AccountNum,   dstrAccountNum, idDataGroup, false);
   getField (ifds::TransId,      dstrTransId,    idDataGroup, false);
   getField (ifds::GrossAmt,     dstrAmount,     idDataGroup, false);
   dstrAmountType = I_("D");
   getField (ifds::TfrFund,      dstrFund,       idDataGroup, false);
   getField (ifds::TfrClass,     dstrClass,      idDataGroup, false);
   getField (ifds::TradeDate,    dstrTradeDate,  idDataGroup, false);


   DString strKey = I_ ("EstateAlloc");

   pEstateAllocationList = dynamic_cast<EstateAllocationList*>( getObject ( strKey, idDataGroup));
   if (!pEstateAllocationList && bCreate)
   {
      SEVERITY severity = NO_CONDITION;

      pEstateAllocationList = new EstateAllocationList(*this);

      severity = pEstateAllocationList->init(dstrAccountNum, dstrTransId, dstrAmount, dstrAmountType,
                  dstrFund, dstrClass, dstrTradeDate, idDataGroup, bReadOnly);

      if (severity <= WARNING)
      {
         setObject ( pEstateAllocationList, strKey, OBJ_ACTIVITY_NONE, idDataGroup);
      }
      else
      {
         delete pEstateAllocationList;
         pEstateAllocationList = NULL;
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}


//******************************************************************************
SEVERITY TransactionDetails::clearingRelatedChanges( )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "clearingRelatedChanges") );

   DString dstrAccountNum;
   getField( ifds::AccountNum, dstrAccountNum, BF::HOST );
   
   DString dstrFrSettlLocCode, dstrFrSettlInstrCode;
   getField (ifds::FrSettlLocCode,   dstrFrSettlLocCode,   BF::HOST );
   getField( ifds::FrSettlInstrCode, dstrFrSettlInstrCode, BF::HOST );

   if ( !dstrFrSettlLocCode.empty() )
   {
      setSettlementLocationSubstList( ifds::FrSettlLocCode, dstrAccountNum, BF::HOST );

      setFieldReadOnly( ifds::FrSettlLocCode,   BF::HOST, true );
      setFieldReadOnly( ifds::FrClearingMethod, BF::HOST, true );
      setFieldReadOnly( ifds::FrSettlInstrCode, BF::HOST, true );
      setFieldReadOnly( ifds::FrDeliveryTo,     BF::HOST, true );
      setFieldReadOnly( ifds::FrInFavourOf,     BF::HOST, true );
      setFieldReadOnly( ifds::FrForAccount,     BF::HOST, true );
	  setFieldReadOnly( ifds::FrCSDLocation,    BF::HOST, true );
	  setFieldReadOnly( ifds::FrCSDAcctNum,     BF::HOST, true );
      for(int i= 0; i < SETL_LOC_FIELDS::numSttlInstrFrReadOnlyFields;	i++)
      {
        setFieldReadOnly( SETL_LOC_FIELDS::SttlInstrFrReadOnlyFields[i],  BF::HOST, true );
      }	
      for(int i= 0; i < SETL_LOC_FIELDS::numSttlInstrReadOnlyAlways;	i++)
      {
        setFieldReadOnly( SETL_LOC_FIELDS::SttlInstrReadOnlyAlways[i], BF::HOST, true );
      }
   }
   if ( !dstrFrSettlInstrCode.empty() )
   {
      setSettlementCodeSubstList( ifds::FrSettlInstrCode,   dstrAccountNum, BF::HOST );
   }

   DString dstrToSettlLocCode, dstrToSettlInstrCode;
   getField (ifds::ToSettlLocCode,   dstrToSettlLocCode,   BF::HOST );
   getField( ifds::ToSettlInstrCode, dstrToSettlInstrCode, BF::HOST );
   if ( !dstrToSettlLocCode.empty() )
   {
      setSettlementLocationSubstList( ifds::ToSettlLocCode, dstrAccountNum, BF::HOST );

      setFieldReadOnly( ifds::ToSettlLocCode,   BF::HOST, true );
      setFieldReadOnly( ifds::ToClearingMethod, BF::HOST, true );
      setFieldReadOnly( ifds::ToSettlInstrCode, BF::HOST, true );
      setFieldReadOnly( ifds::ToDeliveryTo,     BF::HOST, true );
      setFieldReadOnly( ifds::ToInFavourOf,     BF::HOST, true );
      setFieldReadOnly( ifds::ToForAccount,     BF::HOST, true );  
	  setFieldReadOnly( ifds::ToCSDLocation,     BF::HOST, true );
	  setFieldReadOnly( ifds::ToCSDAcctNum,     BF::HOST, true );
      for(int i= 0; i < SETL_LOC_FIELDS::numSttlInstrToReadOnlyFields;	i++)
      {
        setFieldReadOnly( SETL_LOC_FIELDS::SttlInstrToReadOnlyFields[i],  BF::HOST, true );
      }	  
      for(int i= 0; i < SETL_LOC_FIELDS::numSttlInstrReadOnlyAlways;	i++)
      {
        setFieldReadOnly( SETL_LOC_FIELDS::SttlInstrReadOnlyAlways[i], BF::HOST, true );
      }       
   }
   if ( !dstrToSettlInstrCode.empty() )
   {
      setSettlementCodeSubstList( ifds::ToSettlInstrCode,   dstrAccountNum, BF::HOST );
   }


   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY TransactionDetails::setSettlementLocationSubstList ( const BFFieldId &idFieldCode,
                                                              const DString &dstrAccountNum,
                                                              const BFDataGroupId &idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_( "setSettlementLocationSubstList" ) );
	
	bool blSuccess = true;
	DString dstrSettlementLocations;

	MFAccount *pMFAccount = NULL;
   if ( getWorkSession().getMFAccount ( idDataGroup, dstrAccountNum, pMFAccount ) <= WARNING &&
		  NULL != pMFAccount )
	{
		FundMgmtSettlementInstrList *pSettlementLocationAcctList = NULL;
		if ( pMFAccount->getFundMgmtSettlementInstrList( pSettlementLocationAcctList, 
			                                              idDataGroup, 
																		 true ) <= WARNING &&
			  NULL != pSettlementLocationAcctList )
		{
         pSettlementLocationAcctList->getSettlementLocationSubstList (dstrSettlementLocations, idDataGroup);

         if ( !dstrSettlementLocations.empty() )
            setFieldAllSubstituteValues( idFieldCode, idDataGroup, dstrSettlementLocations );
      }
	}

   //if ( blSuccess )
   //{
	//	setFieldAllSubstituteValues( idFieldCode, idDataGroup, dstrSettlementLocations );
   //}
	//else
   //{
	//	ADDCONDITIONFROMFILE( CND::ERR_TRADING_SETTLEMENT_LOCATION_INVALID_CODE_FOR_CLEARING_ACCOUNT );
   //}

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TransactionDetails::setSettlementCodeSubstList ( const BFFieldId& idFieldCode,
                                                          const DString &dstrAccountNum,
                                                          const BFDataGroupId& idDataGroup )
	                                                         
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "setSettlementCodeSubstList" ) );
	
	DString dstrSettleInstrSubstList;
	MFAccount *pMFAccount = NULL;

	if ( getWorkSession().getMFAccount ( idDataGroup, dstrAccountNum, pMFAccount ) <= WARNING && 
        NULL != pMFAccount )
	{
		AcctSettlementInstrList *pAcctSettlementInstrList = NULL;
		if ( pMFAccount->getSettlementInstrList(	pAcctSettlementInstrList, 
													         idDataGroup, 
													         true ) <= WARNING &&
			  NULL != pAcctSettlementInstrList )
		{
         pAcctSettlementInstrList->getSettlementCodeSubstList (dstrSettleInstrSubstList, idDataGroup);

         if ( !dstrSettleInstrSubstList.empty() )
            setFieldAllSubstituteValues( idFieldCode, idDataGroup, dstrSettleInstrSubstList );
      }
   }

   //setFieldAllSubstituteValues( idFieldCode, idDataGroup, dstrSettleInstrSubstList );
	
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TransactionDetails::init( BFData &data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init") );

   attachDataObject( data, false, true );

   DString dstrTransType;
   getField(ifds::TransType, dstrTransType, BF::HOST, false);

   if (dstrTransType == TRADETYPE::ADVISOR_FEE)
   {
       DString dstrAdvisorFeeAppl;
       getWorkSession().getOption(ifds::AdvisorFeeAppl, dstrAdvisorFeeAppl, BF::HOST, false);

       // If function control named "DLRFEE" is active, 
       // change the description of "AFDF" from Dealer Service Fee to Advisor Fee.
       if (dstrAdvisorFeeAppl.stripAll().upperCase() == YES)
       {
           BFProperties *pProperties = getFieldProperties(ifds::TransType, BF::HOST);
           DString dstrTransTypeSubList, tmpSubList, newDescription;
           int nPos;

           pProperties->getAllSubstituteValues(dstrTransTypeSubList);
           tmpSubList = dstrTransTypeSubList;
           nPos = tmpSubList.find(I_("AFDF="));
           newDescription = I_("AFDF=") + DSTCommonFunctions::getDescription(I_("AFDF"), ifds::TransTypeOverrideDescription) + I_(";");

           if (nPos != -1)
           {
               dstrTransTypeSubList = tmpSubList.left(nPos) + newDescription;
               tmpSubList = tmpSubList.right(tmpSubList.length() - nPos);

               int rnPos = tmpSubList.find(';');

               if (rnPos != -1)
               {
                   dstrTransTypeSubList = dstrTransTypeSubList + tmpSubList.right(tmpSubList.length() - rnPos - 1);
               }

               setFieldAllSubstituteValues(ifds::TransType,  BF::HOST,  dstrTransTypeSubList);
           }
       }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void TransactionDetails::getField( const BFFieldId& idField, DString& strFieldValue, 
                                   const BFDataGroupId& idDataGroup, bool formattedReturn ) const
{
   BFCBO::getField( idField, strFieldValue, idDataGroup, formattedReturn );

   if( (  idField == ifds::GrossAmt    ||
          idField == ifds::NetAmt      ||
          idField == ifds::Commission  ||
          idField == ifds::HoldBackAmt ||
          idField == ifds::OverrideAmt ||
          idField == ifds::DeductAmt )
          // || idField == ifds::SetGrossAmt 
          // || idField == ifds::SetNetAmt)  
          &&  formattedReturn )
   {
      DString currency;
      getCurrency( idDataGroup, currency);

      BFCBO::getField( idField, strFieldValue, idDataGroup, false );
      CurrencyClass::FormatValue( currency, strFieldValue, strFieldValue );
   }
   if( idField == ifds::Cancellation )
   {
      if ( IsCancellationEnable( idDataGroup ) ) strFieldValue = YES;
      else strFieldValue = NO;
   }
   if( ifds::TDCC == idField || ifds::Valoren == idField || ifds::CUSIP == idField )
   {
      DString dstrFundCode,dstrClassCode;
      FundDetailList * pFundDetailList = NULL;
      getField( ifds::rxFundCode,dstrFundCode, idDataGroup, true );
      dstrFundCode.strip();
      getField( ifds::rxClassCode,dstrClassCode, idDataGroup, true );
      dstrClassCode.strip();
      if( const_cast<MgmtCo &> (getMgmtCo()).getFundDetailList(pFundDetailList) <= WARNING &&
         pFundDetailList)
         pFundDetailList->getField(dstrFundCode, dstrClassCode, idField, strFieldValue,
         idDataGroup, false);
   }
   if( ifds::ToTDCC == idField || ifds::ToValoren == idField || ifds::ToCUSIP == idField )
   {
      DString dstrToFundCode,dstrToClassCode;
      FundDetailList * pFundDetailList = NULL;
      getField( ifds::TfrFund,  dstrToFundCode, idDataGroup, true );
      dstrToFundCode.strip();
      getField( ifds::TfrClass, dstrToClassCode, idDataGroup, true );
      dstrToClassCode.strip();
      //Fund class details have got only Valoren,TDCC and CUSIP fields in cbo 
      BFFieldId bfTempFieldId;
      if ( ifds::ToTDCC == idField )bfTempFieldId = ifds::TDCC ;
      else if( ifds::ToValoren == idField )bfTempFieldId = ifds::Valoren;
      else if( ifds::ToCUSIP   == idField )bfTempFieldId = ifds::CUSIP;

      if( const_cast<MgmtCo &> (getMgmtCo()).getFundDetailList(pFundDetailList) <= WARNING &&
         pFundDetailList)
         pFundDetailList->getField(dstrToFundCode, dstrToClassCode, bfTempFieldId, strFieldValue,
         idDataGroup, false);
   }
}

//******************************************************************************
void TransactionDetails::getCurrency(const BFDataGroupId& idDataGroup, DString &currency) const
{
   DString fundCode, classCode;
   getField( ifds::rxFundCode, fundCode, idDataGroup, true );
   fundCode.stripAll().upperCase();
   if( fundCode==CASH )
      BFCBO::getField( ifds::SettleCurrency, currency, idDataGroup, false );
   else
   {
      getField( ifds::rxClassCode, classCode, idDataGroup, true );
      CurrencyClass::getFundCurrency( getWorkSession(), fundCode, classCode, currency );
   }
   currency.strip();
}

//******************************************************************************
bool TransactionDetails::isSWPSettleESGElig( const BFDataGroupId &idDataGroup)
{
   DString dstrFromFund, dstrSWPSettleESGElig, dstrTransType,
      dstrPayType, dstrBroker;

   getField (ifds::PayType2, dstrPayType, idDataGroup, false);
   getField (ifds::TfrFund, dstrFromFund, idDataGroup, false);
	getField (ifds::BrokerCode, dstrBroker, idDataGroup, false);
	getField( ifds::TransType, dstrTransType, idDataGroup );
	getWorkSession().getOption ( ifds::SWPSettleESGElig, dstrSWPSettleESGElig, BF::HOST, false);

	if ( ( allowESGSettleForNominee( dstrBroker, idDataGroup )  || 
			 allowESGSettleForIntermediary( idDataGroup ) ) &&
			 dstrPayType == I_("S") &&
			 dstrFromFund != NULL_STRING &&
			 dstrTransType == I_("AW") &&
			 dstrSWPSettleESGElig == I_("Y") )
	{   
		return true;
	}
	else
	{
		return false;
	}
}

//******************************************************************************
bool TransactionDetails::allowESGSettleForNominee ( const DString& dstrBroker, const BFDataGroupId &idDataGroup)
{

	DString dstrAllowed = I_("N");
	
	DString dstrAccountNum;
   getField( ifds::AccountNum, dstrAccountNum, BF::HOST );
	MFAccount *pMFAccount = NULL;  
   if ( getWorkSession().getMFAccount ( idDataGroup, dstrAccountNum, pMFAccount,NO,NULL_STRING,false )
		                   <= WARNING  && pMFAccount ) 
   {
      DString dstrAcctDesignation;
      pMFAccount->getField (ifds::AcctDesignation, dstrAcctDesignation, idDataGroup, false);
		{
			if ( dstrAcctDesignation == I_("2") )
			{
				Broker *pBroker = NULL;
				if ( pMFAccount->getBroker (pBroker, dstrBroker, idDataGroup) <= WARNING && pBroker )
				{
					pBroker->getField ( ifds::SWPSettleESGElig, dstrAllowed, idDataGroup, false);
				}
			}
		}
	}

	return ( dstrAllowed == I_("Y")); 
}

//******************************************************************************
bool TransactionDetails::allowESGSettleForIntermediary ( const BFDataGroupId &idDataGroup)
{
	DString dstrAllowed = I_("N");
	
	DString dstrAccountNum;
   getField( ifds::AccountNum, dstrAccountNum, BF::HOST );

	MFAccount *pMFAccount = NULL;   
   if ( getWorkSession().getMFAccount ( idDataGroup, dstrAccountNum, pMFAccount,NO,NULL_STRING,false )
		                   <= WARNING  && pMFAccount ) 
	{
		DString dstrAcctDesignation;
      pMFAccount->getField (ifds::AcctDesignation, dstrAcctDesignation, idDataGroup, false);
		{
			if ( dstrAcctDesignation == I_("3") )
			{
				DString dstrInterCode;
				pMFAccount->getField (ifds::InterCode, dstrInterCode, idDataGroup, false);

				IntermediaryList *pIntermediaryList = NULL;
				if ( getMgmtCo ().getIntermediaryList (pIntermediaryList) <= WARNING && pIntermediaryList )
				{
					Intermediary* pIntermediary = NULL;
					if ( pIntermediaryList->getIntermediary( idDataGroup, dstrInterCode, pIntermediary ) && pIntermediary)
					{
						pIntermediary->getField ( ifds::SWPSettleESGElig, dstrAllowed, idDataGroup, false);
					}
				}
			}
		}
	}

	return ( dstrAllowed == I_("Y")); 
}

//******************************************************************************
bool TransactionDetails::isBankingAllowed  (const BFDataGroupId &idDataGroup)
{
   DString dstrPayMethod, 
      dstrPayType;

   getField (ifds::PayType2, dstrPayType, idDataGroup, false);
   getField (ifds::PayMethod, dstrPayMethod, idDataGroup, false);
   dstrPayType.strip().upperCase();
   
   if ( dstrPayType == SUPPRESS )
   {
      return isPayEntityBankAvailable(idDataGroup);
   }
   else
   {
      return ( ( dstrPayType == EFT || dstrPayType == DIRECT || dstrPayType == DIRECT_DEPOSIT ) && dstrPayMethod != CHEQUE) || dstrPayType == IW;
   }
}

//******************************************************************************
SEVERITY TransactionDetails::getAccountAllocationList(TradeAcctAllocList*& pAccountAllocationList, 
   const BFDataGroupId& idDataGroup, DString& AccountNum)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getAccountAllocationList" ) );

   pAccountAllocationList = dynamic_cast<TradeAcctAllocList * >(
      getObject( I_("AccountAllocationList"), BF::HOST ));

   if( !pAccountAllocationList )
   {

      pAccountAllocationList = new TradeAcctAllocList( *this );

      DString str, strAllocExists, strSplitCommExists;
      pAccountAllocationList->setField(ifds::AccountNum, AccountNum.strip().stripLeading('0'), BF::HOST, false);
      getField(ifds::TransType, str, BF::HOST, false);
      pAccountAllocationList->setField(ifds::TransType, str, BF::HOST, false);
      getField(ifds::AmountType, str, BF::HOST, false);
      pAccountAllocationList->setField(ifds::AllocAmtType, str, BF::HOST, false);
      getField(ifds::TradeDate, str, BF::HOST, false);
      pAccountAllocationList->setField(ifds::EffectiveDate, str, BF::HOST, false);

      setObject( pAccountAllocationList, I_( "AccountAllocationList" ), OBJ_ACTIVITY_NONE, BF::HOST ); 

      getField(ifds::Allocation, strAllocExists, BF::HOST, false);
      getField(ifds::SplitComm, strSplitCommExists, BF::HOST, false);
      if( strAllocExists.strip() == YES )
         pAccountAllocationList->initExisting();
      else if( strSplitCommExists.strip() == YES )//have to add a 100% alloc
         if( pAccountAllocationList->initNew(BF::HOST, false) <= WARNING )//don't pick up the default allocations here
            pAccountAllocationList->addNewAllocation(AccountNum, BF::HOST, false, true);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY TransactionDetails::getFromFundAllocationList(
   TradeFromFundAllocList *&pTradeFromFundAllocList, 
   const BFDataGroupId &idDataGroup, bool bCreate /*= true*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getFromFundAllocationList"));

   pTradeFromFundAllocList = 
      dynamic_cast<TradeFromFundAllocList*>(getObject(I_("FromFundAllocationList"), 
      idDataGroup));
   if (!pTradeFromFundAllocList && bCreate)
   {
      DString accountNum;

      getField(ifds::AccountNum, accountNum, idDataGroup);
      pTradeFromFundAllocList = new TradeFromFundAllocList(*this);
      if (pTradeFromFundAllocList->initExisting() <= WARNING)
      {
         setObject (pTradeFromFundAllocList, I_("FromFundAllocationList"), 
            OBJ_ACTIVITY_NONE, idDataGroup);
      }
      else
      {
         delete pTradeFromFundAllocList;
         pTradeFromFundAllocList = NULL;
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TransactionDetails::getBankInstructionsList(
   TransactionDetailsBankInstructionsList *&pTransactionDetailsBankInstructionsList, 
   const BFDataGroupId& idDataGroup, 
   bool bCreate /*= true*/,
   bool bCheckBankAllow /*= true*/ )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getBankInstructionsList"));

   //the bank instructions list can be created here depend on check bank allow flag
   bool bBankingAllowed = false;

   if ( bCheckBankAllow )
   {
      bBankingAllowed = isBankingAllowed (idDataGroup);
   }
   else
   {
      bBankingAllowed = true;
   }

   if ( bBankingAllowed )
   {
      BFObjectKey objKey(I_("TransactionDetails_BankInstructionsList"), idDataGroup, 
         OBJ_ACTIVITY_NONE, OBJ_TYPE_NONE);

      pTransactionDetailsBankInstructionsList = NULL;
      pTransactionDetailsBankInstructionsList = 
         dynamic_cast<TransactionDetailsBankInstructionsList *>(findObject(objKey));
      if (!pTransactionDetailsBankInstructionsList && bCreate)
      {
         pTransactionDetailsBankInstructionsList = 
            new TransactionDetailsBankInstructionsList(*this);
         if (pTransactionDetailsBankInstructionsList)
         {
            DString accountNum;

            getField(ifds::AccountNum, accountNum, idDataGroup);
            if (pTransactionDetailsBankInstructionsList->init(
               accountNum, idDataGroup) <= WARNING)
            {
               setObject (objKey, pTransactionDetailsBankInstructionsList);
            }
            else
            {
               delete pTransactionDetailsBankInstructionsList;
               pTransactionDetailsBankInstructionsList = NULL;
            }
         }
      }
   } 
   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
SEVERITY TransactionDetails::doValidateField ( const BFFieldId &idField, 
                                  const DString &strValue, 
                                  const BFDataGroupId &idDataGroup
                                ) 
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doValidateField")
                         );

   DString orgValue;
   getField( idField, orgValue, BF::HOST );

   if(idField == ifds::Units || idField == ifds::GrossAmt || 
      idField == ifds::NetAmt || idField == ifds::AcqDiscountRate || 
      idField == ifds::DiscountAmount || idField == ifds::OfferPrice || ifds::BidPrice == idField )
   {
      if( DSTCommonFunctions::convertToDouble (orgValue) != 
          DSTCommonFunctions::convertToDouble (strValue) )
      {
         ADDCONDITIONFROMFILE (CND::ERR_RECORD_VALUE_NOT_MATCH);
      }
   }
   else if ( idField == ifds::SettleDate )
   {
      ValidateSettleDate( BF::HOST, strValue );
   }
   else if( orgValue != strValue )
   {
      ADDCONDITIONFROMFILE (CND::ERR_RECORD_VALUE_NOT_MATCH);
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
bool TransactionDetails::IsCancellationEnable ( const BFDataGroupId &idDataGroup ) const
{
   bool enableTxnCancel = false, bFnTransCancel = false, bFnVerification = false;	
   DString dstrTranStatus, VerifyCancelCtr;
   DString dstrCanceled, dstrReversal;

   getField( ifds::TranStatus, dstrTranStatus, BF::HOST, false );
   getField( ifds::Cancelled, dstrCanceled, BF::HOST, false );
   getField( ifds::Reversal, dstrReversal, BF::HOST, false );

   bFnTransCancel = getWorkSession().hasReadPermission( UAF::TRANCE_CANCELLATION  );
   bFnVerification = getWorkSession().hasReadPermission( UAF::VERIFY_CANCEL_INSTRUCTION  );
   getWorkSession().getOption (ifds::VerCancTrd, VerifyCancelCtr, BF::HOST, false);

   bool bVerifyMod = VerifyCancelCtr == YES && bFnVerification && dstrTranStatus != VERIFIED;
   bool bCancelMod = dstrTranStatus != VERIFIED && bFnTransCancel;

   if( dstrReversal == NO && dstrCanceled == NO && ( bVerifyMod || bCancelMod ) )
      enableTxnCancel = true;

   return enableTxnCancel;
}
//******************************************************************************
SEVERITY TransactionDetails::getTransactionLinkList(
   TransactionLinkList *&pTransactionLinkList, 
   const BFDataGroupId& idDataGroup, bool bCreate /*= true*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getTransactionLinkList"));

   pTransactionLinkList = 
      dynamic_cast<TransactionLinkList*>(getObject(I_("TransactionLinkList"), 
      idDataGroup));
   if (!pTransactionLinkList && bCreate)
   {
      DString transNum;

      getField(ifds::TransNum, transNum, idDataGroup);
      pTransactionLinkList = new TransactionLinkList(*this);
      if (pTransactionLinkList->init(transNum) <= WARNING)
      {
         setObject (pTransactionLinkList, I_("TransactionLinkList"), 
            OBJ_ACTIVITY_NONE, idDataGroup);
      }
      else
      {
         delete pTransactionLinkList;
         pTransactionLinkList = NULL;
      }
    } 
   return GETCURRENTHIGHESTSEVERITY();
}


//***********************************************************************************
SEVERITY TransactionDetails::getDateValidation ( DateValidation *&pDateValidation, 
                                         const DString &validationType,
                                         const DString &tradeDate, 
                                         const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getDateValidation"));
   DString fundCode, 
      classCode, 
      payType, 
      transType, 
      broker, 
      brokerTo,
      orderType, 
      settleCurrency,
      dealDate, 
      dealTime, 
      toFund, 
      toClass, 
      amount, 
      amtType;

    DString AccountNum, toAccountNum;
    DString settleDate, depositDate, valueDate,settleInDate;
    DString fromCurrency, toCurrency;

    getField (ifds::rxFundCode, fundCode, idDataGroup);
    getField (ifds::rxClassCode, classCode, idDataGroup);
    getField (ifds::OrderType, orderType, idDataGroup);

    getField (ifds::AccountNum, AccountNum, idDataGroup);
    getField (ifds::AccountTo, toAccountNum, idDataGroup);
    getField (ifds::FromCurrency, fromCurrency, idDataGroup);
    getField (ifds::ToCurrency, toCurrency, idDataGroup);
    
    fundCode.strip ().upperCase ();
    classCode.strip ().upperCase ();
    orderType.strip ().upperCase ();

    fromCurrency.strip ().upperCase ();
    toCurrency.strip ().upperCase ();


//call 135 always, even if fund and class are empty, for allocations...
//   if (!fundCode.empty() && !classCode.empty())
   {
      DString strKey;

      DateValidation::buildKey( validationType,
                                tradeDate,
                                settleDate,
                                depositDate,
                                valueDate,
                                transType,
                                payType,
                                broker,
                                fundCode,
                                classCode,
                                toFund,
                                toClass,
                                orderType,
                                dealDate,
                                dealTime,
                                settleCurrency,
                                amount,
                                amtType,
                                strKey,
                                AccountNum,
                                toAccountNum,
                                fromCurrency,
                                toCurrency,
                                I_(""),
                                I_(""),
                                I_("")
                              );
      pDateValidation = 
         dynamic_cast<DateValidation *> (getObject (strKey, idDataGroup));
       if (!pDateValidation)
      {	
         pDateValidation = new DateValidation (*this);
         if (pDateValidation->init( validationType,
                                    tradeDate,
                                    settleDate,
                                    depositDate,
                                    valueDate,
                                    transType,
                                    payType,
                                    broker,
                                    fundCode,
                                    classCode,
                                    toFund,
                                    toClass,
                                    orderType,
                                    dealDate,
                                    dealTime,
                                    settleCurrency,
                                    amount,
                                    amtType,
                                    settleInDate,
                                    brokerTo,
                                    AccountNum,
                                    toAccountNum,
                                    fromCurrency,
                                    toCurrency,
                                    I_(""),
                                    I_(""),
                                    I_("")) <= WARNING)

         {
            setObject (pDateValidation, strKey, OBJ_ACTIVITY_NONE, idDataGroup);
         }
         else
         {
            delete pDateValidation;
            pDateValidation = NULL;
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY (); 
}

//**********************************************************************************************
SEVERITY TransactionDetails::ValidateSettleDate (const BFDataGroupId &idDataGroup, const DString inputSettleDate )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("isBackdatedTrade"));
   DateValidation *pDateValidation = NULL;
   DString tradeDate, settleDate, rxsettleDate;

   getField (ifds::TradeDate, tradeDate, idDataGroup, false);
   getField (ifds::SettleDate, settleDate, idDataGroup, false);

   if( inputSettleDate == NULL_STRING )
   {
      if ( getDateValidation ( pDateValidation, 
                               DATE_VALIDATION::DEFAULT_VALUE_DATE,
                               tradeDate, 
                               idDataGroup) <= WARNING &&
         pDateValidation)
      {
         pDateValidation->getField (ifds::SettleDate, rxsettleDate, idDataGroup, false);
      }
   }
   else 
   {
      rxsettleDate = inputSettleDate;
   }

   if( DSTCommonFunctions::CompareDates (rxsettleDate, settleDate) != DSTCommonFunctions::EQUAL )
   {
      ADDCONDITIONFROMFILE (CND::ERR_RECORD_VALUE_NOT_MATCH);
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//**********************************************************************************************
SEVERITY TransactionDetails::getTransactionUpdate (TransactionUpdate *&pTransactionUpdate,
                                                   const DString &recordType,
                                                   const DString &caller,
                                                   const DString &dstrEnableTradeAuthorization,
                                                   const BFDataGroupId &idDataGroup,
                                                   bool bInquireDataBase)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getTransactionUpdate"));

   DString dstrKey = NULL_STRING;

   DString transNum;
   DString transId;
   DString settleBatch;
   DString authorization = NULL_STRING;
   DString settleUser;
   DString paymentInfo;
   DString tradeRestriction;
   DString tradeRestrictionReason;
   DString dstrSourceOfFundsChecked;
   

   getField (ifds::TransNum, transNum, idDataGroup, false);
   getField (ifds::TransId, transId, idDataGroup, false);
   getField (ifds::StcPendTrdAuthorization, authorization, idDataGroup, false);
   getField (ifds::SettleBatch, settleBatch, idDataGroup, false);
   getField (ifds::SettleUser, settleUser, idDataGroup, false);
   getField (ifds::PaymentInfo, paymentInfo, idDataGroup, false); 
   getField (ifds::TradeRestriction, tradeRestriction, idDataGroup, false); 
   getField (ifds::TradeRestrictionReason, tradeRestrictionReason, idDataGroup, false); 
   getField (ifds::SourceofFundsChecked, dstrSourceOfFundsChecked, idDataGroup, false); 


   if (!caller.empty ())
   {
      if (caller != I_("TradeAuthorization"))
      {
         authorization = I_("");
      }
      else if (caller != I_("Batch"))
      {
         settleBatch = I_("");
      }
      else if (caller != I_("Payment")) 
      {
         paymentInfo = I_("");
      }
      else if (caller != I_("SourceofFundsChecked")) 
      {
         dstrSourceOfFundsChecked = I_("");
      }
   }

   dstrKey = I_("TransNum=") + transNum + I_(";");
   dstrKey += I_("TransId=") + transId;

   pTransactionUpdate = dynamic_cast <TransactionUpdate*>(getObject (dstrKey, idDataGroup));

   if (bInquireDataBase)
   {
      if (!pTransactionUpdate) 
      {
         pTransactionUpdate = new TransactionUpdate (*this);

         if (pTransactionUpdate->init (recordType, transNum, transId, authorization, settleBatch, settleUser, caller,paymentInfo, dstrEnableTradeAuthorization, idDataGroup,
                                       tradeRestriction, tradeRestrictionReason, dstrSourceOfFundsChecked ) <= WARNING)
         
         {
            setObject (pTransactionUpdate, dstrKey, OBJ_ACTIVITY_NONE, idDataGroup); 
         }
         else
         {
            delete pTransactionUpdate;
            pTransactionUpdate = NULL;
         }
      }
      else
      {
         pTransactionUpdate->init (recordType, transNum, transId, authorization, settleBatch, settleUser, caller,paymentInfo, dstrEnableTradeAuthorization, idDataGroup, 
                                   tradeRestriction, tradeRestrictionReason, dstrSourceOfFundsChecked );
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TransactionDetails::getSettlementLocsList (TradeSettlementLocationsList *&pTradeSettlementLocationsList, 
                                                    const BFDataGroupId &idDataGroup, 
                                                    bool bCreate)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getSettlementLocsList"));

   pTradeSettlementLocationsList = NULL;
   SEVERITY severity = NO_CONDITION;
   bool bSetObject = false;
   DString dstrTransNum;

   getField(ifds::TransNum, dstrTransNum, idDataGroup);

   DString strKey = I_("TransNum=") + dstrTransNum;


   pTradeSettlementLocationsList = dynamic_cast <TradeSettlementLocationsList*> (getObject (strKey, idDataGroup));

   if (!pTradeSettlementLocationsList && bCreate)
   {
      bSetObject = true;
      pTradeSettlementLocationsList = new TradeSettlementLocationsList (*this);

      severity = pTradeSettlementLocationsList->init (dstrTransNum, idDataGroup, true);
   }

   if (severity <= WARNING && pTradeSettlementLocationsList)
   {
      BFObjIter iter ( *pTradeSettlementLocationsList, 
                        idDataGroup, 
                        false, 
                        BFObjIter::ITERTYPE::NON_DELETED);

      if (severity <= WARNING)
      {
         if (bSetObject)
         {
            setObject (pTradeSettlementLocationsList, strKey, OBJ_ACTIVITY_NONE, idDataGroup); 
         }
      }
      else
      {
         delete pTradeSettlementLocationsList;
         pTradeSettlementLocationsList = NULL;
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
bool TransactionDetails::isPayEntityBankAvailable( const BFDataGroupId &idDataGroup )
{
   bool bResult = false;
   TradePayInstructList *pTradePayInstructList = NULL;
   BankInstructions *pBankInstructions = NULL;

   if ( getPayInstructList (pTradePayInstructList, idDataGroup) <= WARNING &&
        pTradePayInstructList)
   {
      DString strPayToEntity;
      BFObjIter bfIter (*pTradePayInstructList, 
                        idDataGroup, 
                        false, 
                        BFObjIter::ITERTYPE::NON_DELETED);
      if ( !bfIter.end() )
      {
         TradePayInstruct* pTradePayInstruct = 
            dynamic_cast<TradePayInstruct*>(bfIter.getObject());

         if (pTradePayInstruct && pTradePayInstruct->isBankingAllowed(idDataGroup) )
         {
            pTradePayInstruct->getField( ifds::PayToEntity, strPayToEntity, idDataGroup, false );
            strPayToEntity.strip().upperCase();
         }
      }

      if ( !strPayToEntity.empty() )
      {
         getEntityBankInstruction( pBankInstructions, strPayToEntity, idDataGroup );

         if ( pBankInstructions )
         {
            bResult = true;
         }
      }
   }

   return bResult;
}

//******************************************************************************
SEVERITY TransactionDetails::getPayInstructList ( TradePayInstructList *&pTradePayInstructList, 
                                                  const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getPayInstructList"));
   SEVERITY severity = NO_CONDITION;
   DString paymentFor (PAYMENT_FOR::REDEMPTION),
           payToEntity,
           broker,
           branch,
           slsrep,
           tradeDate,
           dstrAccountNum;

   getField( ifds::AccountNum, dstrAccountNum, idDataGroup );
   getField( ifds::TradeDate, tradeDate, idDataGroup );

   MFAccount *pMFAccount = NULL;
   if ( getWorkSession().getMFAccount ( idDataGroup, dstrAccountNum, pMFAccount ) <= WARNING &&
        NULL != pMFAccount )
   {
      if ( pMFAccount->getPayToEntityForRedemption (payToEntity, idDataGroup) <= WARNING &&
           !payToEntity.empty ())
      {
         if (payToEntity == PAY_TO::BROKER)
         {
            pMFAccount->getField (ifds::BrokerCode, broker, idDataGroup);
         }
         else if (payToEntity == PAY_TO::BRANCH)
         {
            pMFAccount->getField (ifds::BrokerCode, broker, idDataGroup);
            pMFAccount->getField (ifds::BranchCode, branch, idDataGroup);
         }
         else if (payToEntity == PAY_TO::SALESREP)
         {
            pMFAccount->getField (ifds::BrokerCode, broker, idDataGroup);
            pMFAccount->getField (ifds::BranchCode, branch, idDataGroup);
            pMFAccount->getField (ifds::Slsrep, slsrep, idDataGroup);
         }
      }

      if (!payToEntity.empty ())
      {
         pTradePayInstructList = new TradePayInstructList (*this);
         if ( (payToEntity == PAY_TO::BROKER   && !broker.empty()) ||
              (payToEntity == PAY_TO::BRANCH   && !broker.empty() && !branch.empty()) ||
              (payToEntity == PAY_TO::SALESREP && !broker.empty() && !branch.empty() && !slsrep.empty()))
         {
            pTradePayInstructList->init ( payToEntity,
                                          broker, 
                                          branch,
                                          slsrep,
                                          tradeDate,
                                          paymentFor,
                                          idDataGroup);
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TransactionDetails::getEntityBankInstruction(BankInstructions *&pBankInstructions,
                                                      const DString& payToEntity,
                                                      const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "getEntityBankInstruction" ) );

   DString tradeDate, strBroker, strBranch, strSlsRep,
           strAccountNum;

   getField( ifds::AccountNum, strAccountNum, idDataGroup );
   getField( ifds::TradeDate, tradeDate, idDataGroup );

   MFAccount *pMFAccount = NULL;
   if ( getWorkSession().getMFAccount ( idDataGroup, strAccountNum, pMFAccount ) <= WARNING &&
        NULL != pMFAccount )
   {
      if (payToEntity == PAY_TO::BROKER)
      {
         pMFAccount->getField (ifds::BrokerCode, strBroker, idDataGroup);
      }
      else if (payToEntity == PAY_TO::BRANCH)
      {
         pMFAccount->getField (ifds::BrokerCode, strBroker, idDataGroup);
         pMFAccount->getField (ifds::BranchCode, strBranch, idDataGroup);
      }
      else if (payToEntity == PAY_TO::SALESREP)
      {
         pMFAccount->getField (ifds::BrokerCode, strBroker, idDataGroup);
         pMFAccount->getField (ifds::BranchCode, strBranch, idDataGroup);
         pMFAccount->getField (ifds::Slsrep, strSlsRep, idDataGroup);
      }
   }

   DistributorRepository *pDistributorRepository = NULL;

   if ( getWorkSession ().getDistributorRepository (pDistributorRepository) <= WARNING &&
         pDistributorRepository)
   {
      DistributorBankInstructionsList *pDistributorBankInstructionsList = NULL;

      if ( pDistributorRepository->
               getDistributorBankInstructionsList ( strBroker, 
                                                    strBranch, 
                                                    strSlsRep,
                                                    pDistributorBankInstructionsList, 
                                                    idDataGroup) <= WARNING &&
            pDistributorBankInstructionsList)
      {
         BFObjIter iterPayEntityBank ( *pDistributorBankInstructionsList, 
                                       idDataGroup, 
                                       0, 
                                       BFObjIter::ITERTYPE::NON_DELETED);
         while (!iterPayEntityBank.end())
         {
            DString bankAcctCurrency,
                    bankAcctUseCode,
                    bankEffectiveDate,
                    bankStopDate;

            DString strValidBankUseCode;
            strValidBankUseCode += AcctUseCode::DEFAULT;          // '00'
            strValidBankUseCode += I_(",");
            strValidBankUseCode += AcctUseCode::EFT_REDEMPTION;   // '07'

            iterPayEntityBank.getObject()->getField (ifds::BankAcctCurrency, bankAcctCurrency, idDataGroup, false);
            iterPayEntityBank.getObject()->getField (ifds::AcctUseCode, bankAcctUseCode, idDataGroup, false);
            iterPayEntityBank.getObject()->getField (ifds::EffectiveDate, bankEffectiveDate, idDataGroup, false);
            iterPayEntityBank.getObject()->getField (ifds::StopDate, bankStopDate, idDataGroup, false);
            bool bValid = DSTCommonFunctions::codeInList (bankAcctUseCode, strValidBankUseCode);
            if ( DSTCommonFunctions::IsDateBetween (bankEffectiveDate, bankStopDate, tradeDate) && bValid )
            {
               pBankInstructions 
                  = dynamic_cast <BankInstructions*> (iterPayEntityBank.getObject());
               break;
            }
            ++iterPayEntityBank;
         }
      }
   }

   if ( !pBankInstructions )
   {
      getEntityBankInstructionFromTrxnBank( pBankInstructions, idDataGroup );
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TransactionDetails::getEntityBankInstructionFromTrxnBank(BankInstructions *&pBankInstructions,
                                                                  const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "getEntityBankInstructionFromTrxnBank" ) );

   TransactionDetailsBankInstructionsList *pTransactionDetailsBankInstructionsList = NULL; 

   // bypass checking for bank allowance for first time
   getBankInstructionsList( pTransactionDetailsBankInstructionsList,
                            idDataGroup, true, false );

   if ( pTransactionDetailsBankInstructionsList )
   {
      BFObjIter iterTrnxBank ( *pTransactionDetailsBankInstructionsList, 
                                idDataGroup, 
                                0, 
                                BFObjIter::ITERTYPE::NON_DELETED);

      if (!iterTrnxBank.end())
      {
         pBankInstructions = 
            dynamic_cast<BankInstructions *>(iterTrnxBank.getObject());
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TransactionDetails::getPayToEntity (DString &payToEntity, const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "getPayToEntity" ) );

   TradePayInstructList *pTradePayInstructList = NULL;
   BankInstructions *pBankInstructions = NULL;
   payToEntity = NULL_STRING;

   if ( getPayInstructList (pTradePayInstructList, idDataGroup) <= WARNING &&
        pTradePayInstructList)
   {
      DString strPayToEntity;
      BFObjIter bfIter (*pTradePayInstructList, 
                        idDataGroup, 
                        false, 
                        BFObjIter::ITERTYPE::NON_DELETED);
      if ( !bfIter.end() )
      {
         TradePayInstruct* pTradePayInstruct = 
            dynamic_cast<TradePayInstruct*>(bfIter.getObject());

         if (pTradePayInstruct && pTradePayInstruct->isBankingAllowed(idDataGroup) )
         {
            pTradePayInstruct->getField( ifds::PayToEntity, strPayToEntity, idDataGroup, false );
            strPayToEntity.strip().upperCase();
         }
      }

      if ( !strPayToEntity.empty() )
      {
         getEntityBankInstruction( pBankInstructions, strPayToEntity, idDataGroup );

         if ( pBankInstructions )
         {
            payToEntity = strPayToEntity;
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TransactionDetails::initIsCancelModSEGTradeAllowed(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "initIsCancelModSEGTradeAllowed" ) );

   DString strGuaranteeCalcByRules;
   getWorkSession().getOption( ifds::GuaranteeCalcByRules, strGuaranteeCalcByRules, idDataGroup, false );
   strGuaranteeCalcByRules.strip().upperCase();

   DString accountNum,
      fundCode,
      classCode,
      tradeDate,
      transType,
      transId,
      srcOfFund;

   getField (ifds::AccountNum, accountNum, idDataGroup, false);
   getField (ifds::rxFundCode, fundCode, idDataGroup, false);
   getField (ifds::rxClassCode, classCode, idDataGroup, false);
   getField (ifds::TradeDate, tradeDate, idDataGroup, false);
   getField (ifds::TransType, transType, idDataGroup, false);
   getField (ifds::TransId, transId, idDataGroup,false);
   getField (ifds::SrcOfFund, srcOfFund, idDataGroup,false);

   transType.strip().upperCase();
   srcOfFund.strip().upperCase();

   bool bAllowCancel = true;
   if( isSEGFund (fundCode) && strGuaranteeCalcByRules == I_("Y"))
   {
      if( !( DSTCommonFunctions::codeInList ( transType, TRADETYPE::REDEMPTION_LIKE )&& 
             srcOfFund == SRC_OF_FUND_MATUR_PW) )
      {
         SEGTradeEntryValidation validationObj(*this);

         if( validationObj.init(accountNum,
                              fundCode,
                              classCode,
                              NULL_STRING, // account to
                              NULL_STRING, // fund to
                              NULL_STRING, // class to
                              tradeDate,
                              I_("TxnCancel"),
                              transType,
                              transId) <= WARNING )
         {
            DString strErrorCode;
            validationObj.getField(ifds::WarnCode, strErrorCode, idDataGroup, false);
            strErrorCode.strip().upperCase();

            switch( strErrorCode.asInteger())
            {
               case 491:
               case 1217:
               case 1218:
               case 1219:
               case 1220:
               case 1311:
                  bAllowCancel = false;
                  break;
               default:
                  bAllowCancel = true;
                  break;
            }
         }
         else
         {
            bAllowCancel = true;
         }
      }
      else
      {
         bAllowCancel = false;
      }
   }
   else
   {
      bAllowCancel = true;
   }

   if(bAllowCancel)
   {
      setFieldNoValidate(ifds::IsCancelModSEGTradeAllowed, I_("Y"), idDataGroup, false, true);
   }
   else
   {
      setFieldNoValidate(ifds::IsCancelModSEGTradeAllowed, I_("N"), idDataGroup, false, true);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
bool TransactionDetails::isSEGFund ( const DString& fundCode)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isSEGFund" ) );
   bool bIsSEGFund = false;
   FundMasterList *pFundMasterList = NULL;

   if ( !fundCode.empty() && 
         getMgmtCo().getFundMasterList (pFundMasterList) && 
         NULL != pFundMasterList )
   {
      if (pFundMasterList->isSEGFund(fundCode))
      {
         bIsSEGFund = true;
      }
   }

   return bIsSEGFund;
}

//******************************************************************************
SEVERITY TransactionDetails::setSourceOfFundSubstList(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setSourceOfFundSubstList" ) );    

   //P0186486_FN15_The Source of Funds
   DString sourceOfFundApp;

   getWorkSession().getOption(ifds::SourceOfFundApp, sourceOfFundApp, idDataGroup, false);

   sourceOfFundApp.strip().upperCase();

   if(sourceOfFundApp == I_("Y"))
   {
      DString newList;
      BFProperties *pBFProperties = getFieldProperties (ifds::SrcOfFunds_IA, idDataGroup); 
      assert (pBFProperties);
      if (pBFProperties)
      {
         pBFProperties->getAllSubstituteValues (newList);
         setFieldAllSubstituteValues (ifds::SrcOfFund, idDataGroup, newList);
         pBFProperties->setSubstituteValues(NULL);
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
SEVERITY TransactionDetails::getFundLmtOverrideList ( FundLmtOverrideList *&pFundLmtOverrideList, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getFundLmtOverrideList"));
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
      pFundLmtOverrideList = dynamic_cast<FundLmtOverrideList *>(BFCBO::getObject(strKey, idDataGroup));

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
bool TransactionDetails::bIsRightToCancelRuleEnabled(const BFDataGroupId &idDataGroup)
{
   bool bRuleTypeEnabled = false;
   
   const DString ruleType = RVCDCODEALLOWEDFORREFUND::RIGHT_TO_CANCEL_RULE;

   FundLmtOverrideList	*pFundLmtOverrideList = NULL;
   if(getFundLmtOverrideList ( pFundLmtOverrideList,idDataGroup) <= WARNING && pFundLmtOverrideList )
   {
      FundLmtOverride *pFundLmtOverride = NULL;
      if ( pFundLmtOverrideList != NULL &&  pFundLmtOverrideList->getFundLevelFundLmtOverride ( getWorkSession(), ruleType,pFundLmtOverride,idDataGroup) <= WARNING )
      {
         if( pFundLmtOverride )
         {
            bRuleTypeEnabled = true;
         }
      }
   }
   return bRuleTypeEnabled; 
}

//********************************************************************************
bool TransactionDetails::amountInventoryAppl(const BFDataGroupId &idDataGroup)
{
    FundDetail *pFundDetail = NULL;
    DString fundCode, classCode;

    getField(ifds::rxFundCode, fundCode, idDataGroup);
    getField(ifds::rxClassCode, classCode, idDataGroup);

    if (getWorkSession().getFundDetail(fundCode, classCode, BF::HOST, pFundDetail) && pFundDetail)
    {
        return pFundDetail->amountInventoryAppl(BF::HOST);
    }

    return false;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TransactionDetails.cpp-arc  $
 * 
 *    Rev 1.60   May 04 2012 11:38:14   panatcha
 * P0186486_FN15_The Source of Funds
 * 
 *    Rev 1.59   Mar 22 2012 15:32:48   dchatcha
 * P0186484 FN 05 - SEG Trade Processing, transfer validations during fund\class changed.
 * 
 *    Rev 1.58   Mar 19 2012 17:26:10   dchatcha
 * P0186484 FN 05 - SEG Trade Processing, include error code 491 to diable cancel button.
 * 
 *    Rev 1.57   Mar 12 2012 21:14:32   dchatcha
 * P0186484 FN 05 - SEG Trade Processing, there seem to be call failing then field value is not correct.
 * 
 *    Rev 1.56   Mar 09 2012 20:46:06   dchatcha
 * P0186484 FN05 - SEG Trade Processing.
 * 
 *    Rev 1.55   Mar 09 2012 16:40:00   dchatcha
 * P0186484 FN05 - SEG Trade Processing.
 * 
 *    Rev 1.54   Mar 05 2012 12:15:44   dchatcha
 * P0186484 FN05 - SEG Trade Processing.
 * 
 *    Rev 1.53   Dec 08 2011 21:51:28   wp040032
 * P0183989 - Money Market Non Receipt
 * 
 *    Rev 1.52   Jul 05 2010 02:14:20   dchatcha
 * IN# 1984105 - Settlement from Broker trade will bring out shareholder default bank.
 * 
 *    Rev 1.51   Jan 20 2010 08:58:42   dchatcha
 * IN# 1976746 - Pay Instruction button enabled with Pay type X and error displayed.
 * 
 *    Rev 1.50   Aug 11 2009 15:13:56   jankovii
 * PET0164824 FN01 - Eiger iShares Orders and ETF Fields
 * 
 *    Rev 1.49   Jul 16 2009 19:18:20   dchatcha
 * PET156681 FN14 H36 Investor Authorization, Integration issues.
 * 
 *    Rev 1.48   May 22 2009 16:04:30   jankovii
 * PET 159770 FN05 Auto Batching.
 * 
 *    Rev 1.47   May 22 2009 13:46:02   jankovii
 * PET 159770 FN05 Auto Batching.
 * 
 *    Rev 1.46   May 22 2009 10:36:32   jankovii
 * PET 159770 FN05 Auto Batching.
 * 
 *    Rev 1.45   May 22 2009 10:31:16   jankovii
 * PET 159770 FN05 Auto Batching.
 * 
 *    Rev 1.44   Mar 11 2008 20:16:54   daechach
 * PET2385FN02&07 - Account Level Settlement Periods and Currency Holiday - Check in for Build.
 * 
 *    Rev 1.43   Mar 21 2007 13:26:36   jankovii
 * PET 2292 FN01 - Switch Settlement.
 * 
 *    Rev 1.42   Oct 16 2006 17:08:34   AGUILAAM
 * IN 730965 - settledgross and settled net will be displayed as-is, not formatted in fund currency
 * 
 *    Rev 1.41   Mar 02 2006 17:33:02   ZHANGCEL
 * PET1334 - FN01 -- ESG Settlement enhancement
 * 
 *    Rev 1.40   Aug 04 2005 17:50:24   Fengyong
 * Incident 366368 - Add SettleDate validation
 * 
 *    Rev 1.39   Jul 08 2005 09:33:48   Yingbaol
 * PET1235,FN01:transaction cancellation rebook
 * 
 *    Rev 1.38   Jun 15 2005 18:33:28   popescu
 * Incident # 333141- correctly displayed the split commission amount value for processed transactions
 * 
 *    Rev 1.37   Apr 01 2005 13:38:02   Fengyong
 * PET1190 FN05 - check canceled and reversal two fields for transaction history screen cancel button
 * 
 *    Rev 1.36   Mar 28 2005 16:05:48   yingbaol
 * incident 23776: fix discard window pops up even though there is nothing updated
 * 
 *    Rev 1.35   Mar 08 2005 14:11:08   Fengyong
 * PET1190 FN04 - Uncomment out enhance code after DD sync up.
 * 
 *    Rev 1.34   Mar 04 2005 17:02:28   Fengyong
 * PET1190 FN04 - TranCancel tempary check in for other coder
 * 
 *    Rev 1.33   Feb 03 2005 17:55:22   Fengyong
 * PET1117 FN66 - Trade Reconcile API - decimal fields comparation 
 * 
 *    Rev 1.32   Feb 03 2005 13:38:38   Fengyong
 * PET1117 FN66 - Trade reconcile API
 * 
 *    Rev 1.31   Dec 14 2004 10:46:10   vadeanum
 * PET1117 FN21 - Settlement Instr setup.
 * 
 *    Rev 1.30   Nov 14 2004 14:58:12   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.29   Oct 28 2003 10:44:04   FENGYONG
 * add direct trading as a parameter to the is bank allowed function
 * 
 *    Rev 1.28   Oct 19 2003 18:35:40   popescu
 * CIBC PET 809, FN 13
 * 
 *    Rev 1.27   Oct 19 2003 16:44:56   popescu
 * CIBC, PET809, FN 13 banking work
 * 
 *    Rev 1.26   Sep 01 2003 21:32:44   popescu
 * PET 809, FN 02 CIBC Multi Fund Transfer
 * 
 *    Rev 1.25   May 16 2003 17:16:56   popescu
 * TransactionDetails doesn't own split commission; it goes thru TradeFundAllocation
 * 
 *    Rev 1.24   May 15 2003 15:03:54   popescu
 * fixes for a crash in PendingTrades, split comm
 * 
 *    Rev 1.23   Apr 29 2003 17:14:56   popescu
 * PTS 10016204
 * 
 *    Rev 1.22   Apr 14 2003 16:27:42   popescu
 * PTS 10011081- split commision amount is being calculated by the view side
 * 
 *    Rev 1.21   Mar 21 2003 18:27:40   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.20   Oct 09 2002 23:55:12   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.19   Aug 29 2002 12:56:56   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.18   Jun 27 2002 17:21:56   KOVACSRO
 * AllocAmtType versus AmountType.
 * 
 *    Rev 1.17   22 May 2002 18:30:10   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.16   08 May 2002 17:07:32   KOVACSRO
 * new allocation design fixes.
 * 
 *    Rev 1.15   01 May 2002 10:25:20   KOVACSRO
 * Don't call view 60 if there are no allocations.
 * 
 *    Rev 1.14   30 Apr 2002 16:33:12   KOVACSRO
 * new trade allocations
 * 
 *    Rev 1.13   11 May 2001 10:54:00   HSUCHIN
 * Sync up with SSB (1.11.2.2)
 * 
 *    Rev 1.12   03 May 2001 14:07:14   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.11   Mar 26 2001 10:30:54   YINGZ
 * change AccountAllocationList::initPTAlloc to AccountAllocationList::initAllocList
 * 
 *    Rev 1.10   Mar 18 2001 12:32:00   HSUCHIN
 * added accountallocation hook up
 * 
 *    Rev 1.9   Mar 15 2001 09:43:10   HSUCHIN
 * removed worksession id from getSplitCommission list
 * 
 *    Rev 1.8   Mar 15 2001 09:41:10   HSUCHIN
 * added split commission to the class object to ensure proper initialization
 * 
 *    Rev 1.7   Mar 09 2001 13:10:14   HSUCHIN
 * code cleanup and split commision hook up
 * 
 *    Rev 1.6   Mar 08 2001 15:25:58   HSUCHIN
 * check in for Ulli
 * 
 *    Rev 1.5   Feb 19 2001 14:08:16   DINACORN
 * Add Revision Control Entries
 *
 */