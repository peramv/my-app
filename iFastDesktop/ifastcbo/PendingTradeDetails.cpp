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
// ^FILE   : PendingTradeDetails.cpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 03/20/99
//
// ^CLASS    : PendingTradeDetails
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"

#include "acctsettlementinstrlist.hpp"
#include "dstcworksession.hpp"
#include "externalinstitutionlist.hpp"
#include "funddetail.hpp"
#include "funddetaillist.hpp"
#include "fundmasterlist.hpp"
#include "fundmgmtsettlementinstrlist.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"
#include "pendingtradedetails.hpp"
#include "pendingtradebankinstructionslist.hpp"
#include "segtradeentryvalidation.hpp"
#include "tradeacctalloc.hpp"
#include "tradeacctalloclist.hpp"
#include "tradefundalloclist.hpp"
#include "tradefromfundalloclist.hpp"
#include "tradesettlementlocationslist.hpp"
#include "transactionupdate.hpp"
#include "transfeelist.hpp"
#include "transfeecontext.hpp"

#include <ifastdataimpl\dse_currency_vw.hpp>
#include <ifastdataimpl\dse_dstc0053_vw.hpp>
#include <ifastdataimpl\dse_dstc0054_req.hpp>
#include <ifastdataimpl\dse_dstc0054_vw.hpp>
#include <ifastdataimpl\dse_dstc0181_req.hpp>

#include <ifastdataimpl\dse_dstc0149_vw.hpp> //P0186486_FN15_The Source of Funds


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest PENDING_TRADE_DETAILS;
   extern CLASS_IMPORT const DSTCRequest TRADE_DATE_LAG_VALIDATION;
}

namespace
{
   // Trace literals
   const I_CHAR * CLASSNAME                  = I_( "PendingTradeDetails" );
   const I_CHAR * const YES                  = I_( "Y" );
   const I_CHAR * const NO                   = I_( "N" );
   const I_CHAR * EFT                        = I_( "E" );
   const I_CHAR * DIRECT                     = I_( "D" );
   const I_CHAR * DIRECT_DEPOSIT             = I_ ("D1");
   const I_CHAR * IW                         = I_( "I" );
   const I_CHAR * WIRE                       = I_( "WIRE" );
   const I_CHAR * CHEQUE                     = I_( "CHQ" );
   const I_CHAR * const PAC                  = I_( "ED" );
   const I_CHAR * const DEPOSIT_TYPE_TWO     = I_( "2" );   
  
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

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId AmtTypeRedemption;
   extern CLASS_IMPORT const BFTextFieldId AmountTypeExchange;
   extern CLASS_IMPORT const BFTextFieldId TradeDateLag;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFTextFieldId AllocAmtType;
   extern CLASS_IMPORT const BFDataId DSTC0181_VW;
   extern CLASS_IMPORT const BFTextFieldId MarginEligible;
   extern CLASS_IMPORT const BFIntegerFieldId CommissionType;
   extern CLASS_IMPORT const BFTextFieldId AllowMultiFundTransfer;
   extern CLASS_IMPORT const BFTextFieldId FromFund;
   extern CLASS_IMPORT const BFTextFieldId FromClass;
   extern CLASS_IMPORT const BFTextFieldId AdminFeeAmtType;
   extern CLASS_IMPORT const BFTextFieldId IgnoreActiveBatch;
   extern CLASS_IMPORT const BFDateFieldId ModDate;
   extern CLASS_IMPORT const BFTextFieldId ModUser;
   extern CLASS_IMPORT const BFTextFieldId GRRepayReasonCommon;
   extern CLASS_IMPORT const BFTextFieldId GRRepayReasonQESI;
   extern CLASS_IMPORT const BFTextFieldId GRRepayReasonRDSP;
   extern CLASS_IMPORT const BFNumericFieldId ErrorCode;
   extern CLASS_IMPORT const BFTextFieldId ErrorDesc;
   extern CLASS_IMPORT const BFTextFieldId ErrorValue1;
   extern CLASS_IMPORT const BFTextFieldId ErrorValue2;
   extern CLASS_IMPORT const BFTextFieldId ErrorValue3;
   extern CLASS_IMPORT const BFTextFieldId ErrorValue4;
   extern CLASS_IMPORT const BFTextFieldId IsCancelModSEGTradeAllowed;
   extern CLASS_IMPORT const BFIntegerFieldId WarnCode;
   extern CLASS_IMPORT const BFTextFieldId GuaranteeCalcByRules;
   extern CLASS_IMPORT const BFTextFieldId SrcOfFund; //P0186486_FN15_The Source of Funds
   extern CLASS_IMPORT const BFTextFieldId SrcOfFunds_IA; 
   extern CLASS_IMPORT const BFTextFieldId CUSIP;
   extern CLASS_IMPORT const BFTextFieldId TDCC;
   extern CLASS_IMPORT const BFTextFieldId Valoren;
   extern CLASS_IMPORT const BFTextFieldId ToCUSIP;
   extern CLASS_IMPORT const BFTextFieldId ToTDCC;
   extern CLASS_IMPORT const BFTextFieldId ToValoren;
   extern CLASS_IMPORT const BFTextFieldId RolloverExchangeAmountType;
   extern CLASS_IMPORT const BFTextFieldId AdvisorFeeAppl;
   extern CLASS_IMPORT const BFTextFieldId TransTypeOverrideDescription;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const TRANSFER;
   extern CLASS_IMPORT I_CHAR * const REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const EXCHANGE;
   extern CLASS_IMPORT I_CHAR * const MGMT_FEE;
   extern CLASS_IMPORT I_CHAR * const ADMIN_FEE;
   extern CLASS_IMPORT I_CHAR * const ROLLOVER_EXCHANGE;
   extern CLASS_IMPORT I_CHAR * const ADVISOR_FEE;
   extern CLASS_IMPORT I_CHAR * const INTER_CLASS_SWITCH;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
//  Field DD Id,                       State Flags,      Group Flags 
   { ifds::AmountType,                 BFCBO::NONE,         0 },
   { ifds::AccountNum,                 BFCBO::NONE,         0 },
   { ifds::EffectiveDate,              BFCBO::NONE,         0 },

   { ifds::FrSettlLocCode,             BFCBO::NONE,         0 },
   { ifds::FrClearingMethod,           BFCBO::NONE,         0 },
   { ifds::FrSettlInstrCode,           BFCBO::NONE,         0 },
   { ifds::FrDeliveryTo,               BFCBO::NONE,         0 },
   { ifds::FrInFavourOf,               BFCBO::NONE,         0 },
   { ifds::FrForAccount,               BFCBO::NONE,         0 },
   { ifds::FrCSDLocation,               BFCBO::NONE,         0 },
   { ifds::FrCSDAcctNum,               BFCBO::NONE,         0 },

   { ifds::ToSettlLocCode,             BFCBO::NONE,         0 },
   { ifds::ToClearingMethod,           BFCBO::NONE,         0 },
   { ifds::ToSettlInstrCode,           BFCBO::NONE,         0 },
   { ifds::ToDeliveryTo,               BFCBO::NONE,         0 },
   { ifds::ToInFavourOf,               BFCBO::NONE,         0 },
   { ifds::ToForAccount,               BFCBO::NONE,         0 },
   { ifds::TransType,                  BFCBO::NONE,         0 },
   { ifds::ModDate,                    BFCBO::NONE,         0 },
   { ifds::ModUser,                    BFCBO::NONE,         0 },
   { ifds::GRRepayReason,              BFCBO::NONE,         0 },
   { ifds::IsCancelModSEGTradeAllowed, BFCBO::NOT_ON_HOST,  0 },
   { ifds::SrcOfFund,                  BFCBO::NONE,         0 }, //P0186486_FN15_The Source of Funds
   { ifds::SrcOfFunds_IA,              BFCBO::NONE,         0 }, //P0186486_FN15_The Source of Funds
   { ifds::ToCSDLocation,               BFCBO::NONE,         0 },
   { ifds::ToCSDAcctNum,               BFCBO::NONE,         0 },
   
   //{ ifds::GrossNetMethod,           BFCBO::NONE,         0 },
   { ifds::FrSettlementAccount,            BFCBO::NONE,        0 },
   { ifds::FrInternalSettlementAccount,    BFCBO::NONE,        0 },
   { ifds::FrIntermediaryBank,    BFCBO::NONE,                 0 },
   { ifds::FrCashMsgType,         BFCBO::NONE,                 0 }, 
   { ifds::FrReceivingBank,       BFCBO::NONE,                 0 },
   { ifds::FrBeneficiary,         BFCBO::NONE,                 0 }, 
   { ifds::FrSpecialInstructions, BFCBO::NONE,                 0 },
   { ifds::ToSettlementAccount,   BFCBO::NONE,                 0 },
   { ifds::ToInternalSettlementAccount, BFCBO::NONE,           0 },
   { ifds::ToIntermediaryBank,    BFCBO::NONE,                 0 },
   { ifds::ToCashMsgType,         BFCBO::NONE,                 0 }, 
   { ifds::ToReceivingBank,       BFCBO::NONE,                 0 },
   { ifds::ToBeneficiary,         BFCBO::NONE,                 0 }, 
   { ifds::ToSpecialInstructions, BFCBO::NONE,                 0 },
   { ifds::ExternalInstitution,   BFCBO::NONE,                 0 },
 
   
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
   //  Object Label,                  State Flags,      Group Flags 
   { I_( "AccountAllocationList" ),   BFCBO::NONE,          0},
   { I_( "FromFundAllocationList" ),  BFCBO::NONE,          0},
};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );

//******************************************************************************
PendingTradeDetails::PendingTradeDetails( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent ),
_AlreadyGotDetails (false),
m_strAccountNum(NULL_STRING),
_pTransFeeContext (NULL)
{
   TRACE_CONSTRUCTOR(CLASSNAME , NULL_STRING);

   registerMemberData (NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       NUM_OBJECTS, (const CLASS_OBJECT_INFO *)&classObjectInfo);
}

//******************************************************************************
PendingTradeDetails::~PendingTradeDetails()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   if (_pTransFeeContext)
   {
      delete _pTransFeeContext;
      _pTransFeeContext = NULL;
   }
}

//******************************************************************************
SEVERITY PendingTradeDetails::getDetails( DString &AccountNum, 
                                          DString& FundCode, 
                                          DString& ClassCode,
                                          DString& TransType, 
                                          DString& TransNum, 
                                          DString& TradeDate,
                                          const DString& dstrTrack,
                                          const DString& dstrPageName,
                                          const DString& ignoreActiveBatch,
                                          const DString& rebook
                                         )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getDetails") );

   if( !_AlreadyGotDetails )
   {
      m_strAccountNum = AccountNum;
      _AlreadyGotDetails = true;

      BFData queryData(ifds::DSTC0054_REQ);

      DString mgmtCoIdOut;
      queryData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
      queryData.setElementValue( ifds::AccountNum,AccountNum );
      queryData.setElementValue( ifds::FundCode,FundCode );
      queryData.setElementValue( ifds::ClassCode,ClassCode );
      queryData.setElementValue( ifds::TransType,TransType );
      queryData.setElementValue( ifds::TransNum,TransNum );
      queryData.setElementValue( ifds::TradeDate,TradeDate, false, true );
      queryData.setElementValue( ifds::Track, dstrTrack );
      queryData.setElementValue( ifds::Activity, dstrPageName );
      queryData.setElementValue( ifds::IgnoreActiveBatch, ignoreActiveBatch );
      queryData.setElementValue( ifds::Rebook, rebook );

      setFieldNoValidate(ifds::AccountNum, AccountNum, BF::HOST, 
         false, false, false);
/*      setFieldNoValidate(ifds::TransType, TransType, BF::HOST, 
         false, false, false);
      setFieldNoValidate(ifds::TransNum, TransNum, BF::HOST, 
         false, false, false);*/
      setFieldNoValidate(ifds::EffectiveDate, TradeDate, BF::HOST, 
         false, false, false);
      if (ReceiveData(DSTC_REQUEST::PENDING_TRADE_DETAILS, queryData, 
         ifds::DSTC0054_VW, DSTCRequestor( getSecurity(), false, true )) <= WARNING)
      {
         clearingRelatedChanges();
         setGRRepayReasonSubstList(BF::HOST);
         initIsCancelModSEGTradeAllowed(BF::HOST);
         setSourceOfFundSubstList(BF::HOST);//P0186486_FN15_The Source of Funds
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY PendingTradeDetails::clearingRelatedChanges( )
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
	  setFieldReadOnly( ifds::FrCSDLocation,     BF::HOST, true );
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
SEVERITY PendingTradeDetails::setSettlementLocationSubstList ( const BFFieldId &idFieldCode,
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
    //    setFieldAllSubstituteValues( idFieldCode, idDataGroup, dstrSettlementLocations );
    //}
    //else
    //{
    //    ADDCONDITIONFROMFILE( CND::ERR_TRADING_SETTLEMENT_LOCATION_INVALID_CODE_FOR_CLEARING_ACCOUNT );
    //}

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY PendingTradeDetails::setSettlementCodeSubstList ( const BFFieldId& idFieldCode,
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
      if ( pMFAccount->getSettlementInstrList( pAcctSettlementInstrList, 
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
void PendingTradeDetails::init( BFData &data )
{
   attachDataObject( data, false, true);
   DString transType,amountType;
   BFCBO::getField(ifds::TransType,transType,BF::HOST,false);
   transType.strip();
   if( transType == TRADETYPE::REDEMPTION )
   {
      setFieldSubstituteValues( ifds::AmountType, BF::HOST, ifds::AmtTypeRedemption );
   }
   else if( transType == TRADETYPE::MGMT_FEE || transType == TRADETYPE::ADMIN_FEE )
   {
      setFieldSubstituteValues( ifds::AmountType, BF::HOST, ifds::AdminFeeAmtType );
   }
   else if( transType == TRADETYPE::EXCHANGE || 
            transType == TRADETYPE::INTER_CLASS_SWITCH || 
            transType == TRADETYPE::TRANSFER )
   {
      setFieldSubstituteValues( ifds::AmountType, BF::HOST, ifds::AmountTypeExchange );
   }
   else if ( transType == TRADETYPE::ROLLOVER_EXCHANGE )
   {
	  setFieldSubstituteValues (ifds::AmountType, BF::HOST, ifds::RolloverExchangeAmountType);
   }
   else if (transType == TRADETYPE::ADVISOR_FEE)
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
}
//******************************************************************************
void PendingTradeDetails::getField( const BFFieldId& idField, 
                                    DString& strFieldValue, 
                                    const BFDataGroupId& idDataGroup, 
                                    bool formattedReturn ) const
{
   BFCBO::getField( idField, strFieldValue, idDataGroup, formattedReturn );

   DString amttype = NULL_STRING;
   if( idField == ifds::Amount )
      BFCBO::getField( ifds::AmountType, amttype, idDataGroup, false );

   DString dstrFlatPercent = NULL_STRING;
   if( idField == ifds::Fee )
      BFCBO::getField( ifds::FlatPercent, dstrFlatPercent, idDataGroup, false );

   DString dstrExchInFlatPercent = NULL_STRING;
   if( idField == ifds::ExchInFee )
      BFCBO::getField( ifds::ExchInFlatPercent, dstrExchInFlatPercent, idDataGroup, false );

   if( ((idField == ifds::Amount && amttype != I_("U")   ) ||
      idField == ifds::AdminFeeAmt ||
      idField == ifds::OverrideAmt ||
      idField == ifds::Fee && dstrFlatPercent.upperCase() == I_( "Y" ) ||
      idField == ifds::ExchInFee && dstrExchInFlatPercent.upperCase() == I_( "Y" )) &&
      formattedReturn )
   {
      DString currency;
      BFCBO::getField( ifds::SettleCurrency, currency, idDataGroup, false );
      currency.strip();

      BFCBO::getField( idField, strFieldValue, idDataGroup, false );
      CurrencyClass::FormatValue( currency, strFieldValue, strFieldValue );
   }
   else if( idField == ifds::AmountType )
   {
      if( formattedReturn )
      {
         BFProperties* pBFP   =  const_cast< PendingTradeDetails * >( this )->getFieldProperties(idField,idDataGroup);
         pBFP->formatValue(  idField, strFieldValue,true );   
      }
   }
   if( ifds::TDCC  == idField ||ifds::Valoren == idField || ifds::CUSIP == idField )
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
	getField( ifds::FundTo, dstrToFundCode, idDataGroup, true );
	dstrToFundCode.strip();
	getField( ifds::ClassToCode, dstrToClassCode, idDataGroup, true );
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
SEVERITY PendingTradeDetails::getAccountAllocationList (TradeAcctAllocList *&pAccountAllocationList, 
   const BFDataGroupId& idDataGroup, DString &AccountNum)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getAccountAllocationList" ) );

   pAccountAllocationList = dynamic_cast<TradeAcctAllocList*> 
      (getObject (I_("AccountAllocationList"), idDataGroup));
   if (!pAccountAllocationList)
   {
      pAccountAllocationList = new TradeAcctAllocList (*this);

      DString str, 
         tradeType, 
         strAllocExists, 
         strSplitCommExists;

      getField (ifds::TransType, tradeType, idDataGroup, false);
      pAccountAllocationList->setField(ifds::TransType, tradeType, BF::HOST, false);
      getField (ifds::AmountType, str, idDataGroup, false);
      pAccountAllocationList->setField (ifds::AllocAmtType, str, BF::HOST, false);
      getField (ifds::TradeDate, str, idDataGroup, false);
      pAccountAllocationList->setField(ifds::EffectiveDate, str, BF::HOST, false);
      setObject (pAccountAllocationList, I_( "AccountAllocationList" ), OBJ_ACTIVITY_NONE, BF::HOST);
      getField (ifds::Allocation, strAllocExists, BF::HOST, false);
      getField (ifds::SplitComm, strSplitCommExists, BF::HOST, false);

      if (strAllocExists.strip() == YES)
      {
         pAccountAllocationList->setField (ifds::AccountNum, AccountNum, BF::HOST, false);
         pAccountAllocationList->initExisting();
      }
      else if (strSplitCommExists.strip() == YES)//have to add a 100% alloc
      {
         if( pAccountAllocationList->initNew (BF::HOST, false) <= WARNING ) //don't pick up the default allocations here
         {
            if (tradeType != TRADETYPE::TRANSFER)
            {
               pAccountAllocationList->addExistingAllocation (AccountNum, BF::HOST);
            }
            else 
            {
               DString AccountTo;

               getField (ifds::AccountTo, AccountTo, idDataGroup, false);
               pAccountAllocationList->addExistingAllocation (AccountTo, BF::HOST);
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool PendingTradeDetails::isValidDateLag( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isValidDateLag") );

   DString dstrTradeDateLag;
   getWorkSession().getOption2( ifds::TradeDateLag, dstrTradeDateLag, idDataGroup, false );

   if( dstrTradeDateLag == YES )
   {
      BFData requestData( ifds::DSTC0181_REQ );
      BFData receivedData( ifds::DSTC0181_VW );

      DString mgmtCoIdOut, dstrTransNum;
      getField( ifds::TransNum, dstrTransNum, idDataGroup );

      requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
      requestData.setElementValue( ifds::TransNum, dstrTransNum );
      requestData.setElementValue( ifds::Track, I_("N") );
      requestData.setElementValue( ifds::Activity, NULL_STRING );

      SEVERITY sev = BFDataBroker::getInstance( )->receive( DSTC_REQUEST::TRADE_DATE_LAG_VALIDATION, requestData, 
                                                            receivedData, DSTCRequestor( getSecurity(), true, true ) );

      if( sev > WARNING )
         return(false);
   }
   return(true);
}

//******************************************************************************
bool PendingTradeDetails::isMarginEligible(const BFDataGroupId& idDataGroup)
{
   DString strFund, strClass, strAllocExists(NO);
   getField(ifds::Allocation, strAllocExists, BF::HOST, false);
   getField(ifds::rxFundCode, strFund, BF::HOST, false);
   getField(ifds::rxClassCode, strClass, BF::HOST, false);

   if ( (strFund.strip().empty() && strClass.strip().empty()) ||
      strAllocExists.strip() == YES)
   {
      TradeAcctAllocList* pAccountAllocationList = NULL;
      if (getAccountAllocationList( pAccountAllocationList, BF::HOST, m_strAccountNum)
         <= WARNING && pAccountAllocationList)
      {
         TradeAcctAlloc* pAccountAllocation = NULL;
         if (pAccountAllocationList->getAccountAllocation(m_strAccountNum, pAccountAllocation, BF::HOST)
            <= WARNING && pAccountAllocation)
         {
            TradeFundAllocList* pFundAllocList = NULL;
            if (pAccountAllocation->getFundAllocationList(pFundAllocList, BF::HOST, true, false)
               <=WARNING && pFundAllocList)
            return (pFundAllocList->isMarginEligible(idDataGroup));
         }
      }
   }
   else//non allocated
   {
      FundDetail* pFundDetail = NULL;
      FundDetailList * pFundDetailList = NULL;

      getMgmtCo().getFundDetailList(  pFundDetailList );

      if( pFundDetailList )
         if (pFundDetailList->getFundDetail( strFund, strClass, BF::HOST, pFundDetail))
            if (pFundDetail)
            {
               DString dstrMarginEligible;
               pFundDetail->getField(ifds::MarginEligible, dstrMarginEligible, BF::HOST, false);
               return (dstrMarginEligible.strip() == YES);
            }
   }
   return false;
}

//******************************************************************************
bool PendingTradeDetails::isBankingAllowed  (const BFDataGroupId &idDataGroup)
{
   DString dstrPayMethod, 
      dstrPayType;

   getField (ifds::PayType2, dstrPayType, idDataGroup, false);
   getField (ifds::PayMethod, dstrPayMethod, idDataGroup, false);

   return ( ( dstrPayType == EFT || dstrPayType == DIRECT || dstrPayType == DIRECT_DEPOSIT) && dstrPayMethod != CHEQUE) || dstrPayType == IW;
}

//******************************************************************************
SEVERITY PendingTradeDetails::getFromFundAllocationList( TradeFromFundAllocList *&pTradeFromFundAllocList, 
                                                         const BFDataGroupId &idDataGroup, 
                                                         bool bCreate /*= true*/)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getFromFundAllocationList"));

   pTradeFromFundAllocList = NULL;

   DString tradeType;

   getField (ifds::TransType, tradeType, idDataGroup, false);
   if (tradeType == TRADETYPE::TRANSFER || 
       tradeType == TRADETYPE::EXCHANGE ||
       tradeType == TRADETYPE::INTER_CLASS_SWITCH)
   {
      //if multi transfer is allowed then create this list
      DString commissionType, 
         allowMultiFundTransfer = I_("Y"); //hardcode, for now 

      getWorkSession().getOption( ifds::CommissionType, 
                                  commissionType, 
                                  BF::HOST, 
                                  false);
      getWorkSession().getOption ( ifds::AllowMultiFundTransfer, 
                                   allowMultiFundTransfer, 
                                   BF::HOST, 
                                   false);
      if ( commissionType == I_("0") && 
           allowMultiFundTransfer == I_("Y"))
      {
         pTradeFromFundAllocList = 
            dynamic_cast<TradeFromFundAllocList*>(getObject(I_("FromFundAllocationList"), 
            idDataGroup));
         if (!pTradeFromFundAllocList && bCreate)
         {
            pTradeFromFundAllocList = new TradeFromFundAllocList(*this);
            pTradeFromFundAllocList->setField(ifds::AccountNum, m_strAccountNum, 
               BF::HOST, false);
            if (pTradeFromFundAllocList->initExisting() <= WARNING)
            {
               setObject (pTradeFromFundAllocList, I_("FromFundAllocationList"), 
                  OBJ_ACTIVITY_NONE, idDataGroup);
               //set the from fund and class on the account allocation object,
               TradeAcctAllocList *pAccountAllocationList = NULL;

               if (getAccountAllocationList (pAccountAllocationList, 
                  idDataGroup, m_strAccountNum) <= WARNING && pAccountAllocationList)
               {
                  BFObjIter iter( *pTradeFromFundAllocList, idDataGroup, false, 
                     BFObjIter::ITERTYPE::NON_DELETED);

                  if (!iter.end())
                  {
                     DString fromFund, fromClass;

                     iter.getObject()->getField (ifds::FundCode, fromFund, idDataGroup, false);
                     iter.getObject()->getField (ifds::ClassCode, fromClass, idDataGroup, false);

                     if (fromFund.strip() != NULL_STRING && 
                           fromClass.strip() != NULL_STRING)
                     {
                        pAccountAllocationList->setField (ifds::FromFund, 
                           fromFund, idDataGroup, false);
                        pAccountAllocationList->setField (ifds::FromClass, 
                           fromClass, idDataGroup, false);
                     }
                  }
               }
            }
            else
            {
               delete pTradeFromFundAllocList;
               pTradeFromFundAllocList = NULL;
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY PendingTradeDetails::getBankInstructionsList( PendingTradeBankInstructionsList *&pPendingTradeBankInstructionsList, 
                                                       const BFDataGroupId& idDataGroup, 
                                                       bool bCreate /*= true*/)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getBankInstructionsList"));

   //the bank instructions list can be created only if the 
   //payment method is EFT
   if (isBankingAllowed (idDataGroup))
   {
      BFObjectKey objKey( I_("PendingTrade_BankInstructionsList"), 
                          idDataGroup, 
                          OBJ_ACTIVITY_NONE, 
                          OBJ_TYPE_NONE);

      pPendingTradeBankInstructionsList = NULL;
      pPendingTradeBankInstructionsList = 
         dynamic_cast <PendingTradeBankInstructionsList*> (findObject(objKey));
      if (!pPendingTradeBankInstructionsList && bCreate)
      {
         pPendingTradeBankInstructionsList = new PendingTradeBankInstructionsList(*this);
         if (pPendingTradeBankInstructionsList)
         {
            if (pPendingTradeBankInstructionsList->init ( m_strAccountNum, 
                                                          idDataGroup) <= WARNING)
            {
               setObject (objKey, pPendingTradeBankInstructionsList);
            }
            else
            {
               delete pPendingTradeBankInstructionsList;
               pPendingTradeBankInstructionsList = NULL;
            }
         }
      }
   } 
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY PendingTradeDetails::getTransFeeList ( TransFeeList *&pTransFeeList, 
                                                const BFDataGroupId &idDataGroup,
                                                bool bCreate /*=true*/)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getTransFeeList"));
   DString strKey = I_("TransFeeList");

   pTransFeeList = dynamic_cast <TransFeeList *> (getObject (strKey, idDataGroup));
   if (bCreate && pTransFeeList)
   {
      BFObjIter iter (*pTransFeeList, idDataGroup);

      if (iter.positionByKey (strKey))
      {
         //blow the list
         iter.removeObjectFromMap (true);
      }
      pTransFeeList = NULL;
   }
   if (!pTransFeeList && bCreate)
   {
      DString transNum,
              accountNum;

      getField (ifds::TransNum, transNum, idDataGroup, false);
      getField (ifds::AccountNum, accountNum, idDataGroup, false);
      accountNum.stripLeading ('0').strip();
      if (!accountNum.empty())
      {
         if (getTransFeeContext (_pTransFeeContext, idDataGroup) <= WARNING)
         {
            pTransFeeList = new TransFeeList (*this);
            pTransFeeList->setContext (*_pTransFeeContext);
            if (pTransFeeList->init (transNum, accountNum, BF::HOST) <= WARNING)
            {
               setObject ( pTransFeeList, 
                           strKey, 
                           OBJ_ACTIVITY_NONE, 
                           idDataGroup);
            }
            else
            {
               delete pTransFeeList;
               pTransFeeList = NULL;
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY PendingTradeDetails::getTransFeeContext ( TransFeeContext *&pTransFeeContext, 
                                                   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getTransFeeContext"));
   if (_pTransFeeContext) //this is a very volatile object, no need to hold on to it
   {
      delete _pTransFeeContext;
      _pTransFeeContext = NULL;
   }
   if (!_pTransFeeContext)
   {
      _pTransFeeContext = new TransFeeContext (*this);
      if (_pTransFeeContext->initPendingTradeContext (this, idDataGroup) <= WARNING)
      {
         pTransFeeContext = _pTransFeeContext;
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY PendingTradeDetails::setConditions ( CONDITIONVECTOR *pCondVect, 
                                              const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("setConditions"));
   if (pCondVect)
   {
      CONDITIONVECTOR* _pCond;
      getFieldConditionVector(ifds::TransType,idDataGroup,_pCond );
      if( _pCond == NULL ) 
      {
         _pCond = new CONDITIONVECTOR;
         setFieldConditionVector (ifds::TransType, idDataGroup, _pCond);
      }

      CONDITIONVECTOR::iterator iter = pCondVect->begin( );
      for( ; iter != pCondVect->end( ); ++iter )
      {
         const Condition* pCondition = (*iter);
         if( pCondition )
         {
            Condition * c = new Condition( *pCondition );
            _pCond->push_back( c );
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool PendingTradeDetails::PendingPACExist( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("PendingPACExist"));

   DString dstrTransType,dstrStatus, dstrDeposit;
   DString FundCode,ClassCode,TransType,TransNum,TradeDate, AccountNum;

   getField( ifds::rxFundCode,FundCode, idDataGroup, true );
   FundCode.strip();
   getField( ifds::rxClassCode,ClassCode, idDataGroup, true );
   ClassCode.strip();
   TransType = NULL_STRING;   //back end don't need transtype here
   getField( ifds::PendingRid,TransNum, idDataGroup, true );
   TransNum.stripLeading( '0' );
   getField( ifds::rxAcctNum,AccountNum, idDataGroup, true );
   AccountNum.strip();
   getField( ifds::TradeDate,TradeDate, idDataGroup, true );
   TradeDate.strip('/');
   getDetails( AccountNum, 
               FundCode, 
               ClassCode, 
               TransType, 
               TransNum, 
               TradeDate );

   getField( ifds::TransType, dstrTransType, idDataGroup, false);
   dstrTransType.strip().upperCase();
   getField( ifds::GoodBad, dstrStatus, idDataGroup, false);
   dstrStatus.strip().upperCase();
   getField(ifds::DepositType,dstrDeposit,idDataGroup,false );
   dstrDeposit.strip();

   bool bRet = dstrStatus == YES && dstrTransType == PAC && dstrDeposit == DEPOSIT_TYPE_TWO;
   return bRet;
}

//**********************************************************************************************
SEVERITY PendingTradeDetails::getTransactionUpdate (TransactionUpdate *&pTransactionUpdate,
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
   DString settleBatch = NULL_STRING;
   DString authorization;
   DString settleUser = NULL_STRING;
   DString paymentInfo = NULL_STRING;
   DString dstrSourceOfFundsChecked;

   getField (ifds::TransNum, transNum, idDataGroup, false);
   getField (ifds::TransId, transId, idDataGroup, false);
   getField (ifds::StcPendTrdAuthorization, authorization, idDataGroup, false);
   getField (ifds::SourceofFundsChecked, dstrSourceOfFundsChecked, idDataGroup, false);

   dstrKey = I_("TransNum=") + transNum + I_(";");
   dstrKey += I_("TransId=") + transId;

   if (!caller.empty ())
   {
     if (caller != I_("SourceofFundsChecked")) 
      {
         dstrSourceOfFundsChecked = I_("");
      }
   }
   pTransactionUpdate = dynamic_cast <TransactionUpdate*>(getObject (dstrKey, idDataGroup));

   if (bInquireDataBase)
   {
		if (!pTransactionUpdate) 
		{
			pTransactionUpdate = new TransactionUpdate (*this);
        
			if (pTransactionUpdate->init (recordType, transNum, transId, authorization, settleBatch, settleUser, caller,paymentInfo, dstrEnableTradeAuthorization, idDataGroup,
                                          NULL_STRING, NULL_STRING, dstrSourceOfFundsChecked) <= WARNING)
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
                                      NULL_STRING, NULL_STRING, dstrSourceOfFundsChecked);
		}
	}

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY PendingTradeDetails::getSettlementLocsList (TradeSettlementLocationsList *&pTradeSettlementLocationsList, 
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
SEVERITY PendingTradeDetails::setGRRepayReasonSubstList(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("setGRRepayReason"));
   DString dstrRedCode,
      dstrGRRepayReason;

   getField (ifds::RedCode, dstrRedCode, idDataGroup, false);
   dstrRedCode.strip().upperCase();

   if (DSTCommonFunctions::codeInList (dstrRedCode, I_("78,IR"))) // QESI Grant return (78), QESI Increase special tax(IR)
   {
      setFieldSubstituteValues (ifds::GRRepayReason, idDataGroup, ifds::GRRepayReasonQESI);
   }
   else if (DSTCommonFunctions::codeInList (dstrRedCode, I_("75,76,83,AG,AR,GR,SR")))
   {
      setFieldSubstituteValues (ifds::GRRepayReason, idDataGroup, ifds::GRRepayReasonCommon);
   }
   else if (DSTCommonFunctions::codeInList (dstrRedCode, I_("BP,DP,GP,LP,TW")))
   {
	  setFieldSubstituteValues (ifds::GRRepayReason, idDataGroup, ifds::GRRepayReasonRDSP);
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY PendingTradeDetails::initIsCancelModSEGTradeAllowed(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "initIsCancelModSEGTradeAllowed" ) );

   DString accountNum,
      fundCode,
      classCode,
      tradeDate,
      transType,
      transId,
      redCode,
      depositType;

   getField (ifds::rxAcctNum, accountNum, idDataGroup, false);
   getField (ifds::rxFundCode, fundCode, idDataGroup, false);
   getField (ifds::rxClassCode, classCode, idDataGroup, false);
   getField (ifds::TradeDate, tradeDate, idDataGroup, false);
   getField (ifds::TransType, transType, idDataGroup, false);
   getField (ifds::TransId, transId, idDataGroup,false);
   getField (ifds::RedCode, redCode, idDataGroup,false);
   getField (ifds::DepositType, depositType, idDataGroup,false);
   transType.strip().upperCase();
   redCode.strip().upperCase();
   depositType.strip().upperCase();

   if( isSEGFund (fundCode.strip()))
   {
      DString strGuaranteeCalcByRules;
      getWorkSession().getOption( ifds::GuaranteeCalcByRules, strGuaranteeCalcByRules, idDataGroup, false );
      strGuaranteeCalcByRules.strip().upperCase();

      if( ((transType == I_("AF")&& redCode == I_("GF"))||
           (transType == I_("ED")&& depositType == I_("62"))) && 
          (strGuaranteeCalcByRules == I_("Y")))
      {
         setFieldNoValidate(ifds::IsCancelModSEGTradeAllowed, I_("N"), idDataGroup, false, true);
      }
      else
      {
         setFieldNoValidate(ifds::IsCancelModSEGTradeAllowed, I_("Y"), idDataGroup, false, true);
      }
   }
   else
   {
      setFieldNoValidate(ifds::IsCancelModSEGTradeAllowed, I_("Y"), idDataGroup, false, true);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
bool PendingTradeDetails::isSEGFund ( const DString& fundCode)
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
SEVERITY PendingTradeDetails::setSourceOfFundSubstList(const BFDataGroupId &idDataGroup)
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

//********************************************************************************
bool PendingTradeDetails::amountInventoryAppl(const BFDataGroupId &idDataGroup)
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
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/PendingTradeDetails.cpp-arc  $
 * 
 *    Rev 1.66   May 04 2012 11:44:42   panatcha
 * P0186486_FN15_The Source of Funds
 * 
 *    Rev 1.65   Mar 09 2012 20:47:40   dchatcha
 * P0186484 FN05 - SEG Trade Processing.
 * 
 *    Rev 1.64   Mar 05 2012 12:08:20   dchatcha
 * P0186484 FN05 - SEG Trade Processing.
 * 
 *    Rev 1.63   Dec 08 2011 21:46:28   wp040032
 * P0183989 - Money Market Non Receipt
 * 
 *    Rev 1.62   Apr 30 2010 01:18:12   dchatcha
 * PET0165541 FN01 QESI RESP Trading, display new fields of view 54.
 * 
 *    Rev 1.61   Aug 11 2009 15:12:50   jankovii
 * PET0164824 FN01 - Eiger iShares Orders and ETF Fields
 * 
 *    Rev 1.60   Jul 16 2009 19:16:46   dchatcha
 * PET156681 FN14 H36 Investor Authorization, Integration issues.
 * 
 *    Rev 1.59   May 22 2009 16:03:36   jankovii
 * PET 159770 FN05 Auto Batching.
 * 
 *    Rev 1.58   Aug 29 2008 09:56:00   daechach
 * in#1355618 - recode fix for 1259584 Gross\net
 * 
 *    Rev 1.57   Aug 06 2008 17:43:30   daechach
 * in#1355618 - recode fix for 1259584 Gross\net.
 * 
 *    Rev 1.56   Apr 25 2008 08:03:32   daechach
 * in#1259584-R84 - Gross / Net display issue in desktop for pending trades
 * 
 *    Rev 1.55   Dec 20 2007 16:31:54   wongsakw
 * PET2315 FN28 -- Audit an Tracking on Pending Trades -- Add ModDate and ModUser field to PendingTrade
 * 
 *    Rev 1.54   Jul 08 2005 09:31:16   Yingbaol
 * PET1235,FN01:transaction cancellation rebook
 * 
 *    Rev 1.53   Jun 14 2005 15:41:12   Fengyong
 * #Incident 328435 - Add IgnoreActiveBatch field to 54 request
 * 
 *    Rev 1.52   Apr 01 2005 14:30:28   Fengyong
 * PET1190/04, trade date aggregated order update
 * 
 *    Rev 1.51   Mar 23 2005 13:25:50   Fengyong
 * PET1190 / 04, trade date aggregated order update
 * 
 *    Rev 1.50   Mar 10 2005 09:47:04   popescu
 * PET 1190/04, trade date aggregated order update
 * 
 *    Rev 1.49   Jan 20 2005 11:03:28   popescu
 * PTS 10038127, fixed internal error when user clicks on the 'Fees' button in trans  history screen
 * 
 *    Rev 1.48   Dec 14 2004 09:59:42   popescu
 * PET 1117/06, refresh trans fee list in pending mode
 * 
 *    Rev 1.47   Dec 13 2004 16:47:20   vadeanum
 * PET1117 FN21 - Settlement Instr setup.
 * 
 *    Rev 1.46   Dec 11 2004 11:47:28   popescu
 * PET 1117/56 more fixes, pending trade mods
 * 
 *    Rev 1.45   Dec 07 2004 21:20:22   popescu
 * PET 1117/06, pending trades/fees fixes, add-ons
 * 
 *    Rev 1.44   Nov 14 2004 14:51:02   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.43   Sep 08 2004 18:12:28   ZHANGCEL
 * PET1094-FN8 -- AdminFee related changes
 * 
 *    Rev 1.42   Feb 23 2004 16:05:42   popescu
 * PTS 10023292, multi fund transfer issue display confusion units vs amount; set the from fund and class to the 'to' side of the transaction in order to format the amount values based on the from side of it.
 * 
 *    Rev 1.41   Nov 24 2003 09:42:02   linmay
 * modified PendingPACExist() for PTS #10024070
 * 
 *    Rev 1.40   Nov 20 2003 09:13:50   linmay
 * added PendingPACExist( ) for PTS #10024070
 * 
 *    Rev 1.39   Nov 04 2003 11:53:34   popescu
 * Synch-up PTS 100020344, R53
 * 
 *    Rev 1.38   Oct 28 2003 10:40:34   FENGYONG
 * add direct trading as an condition for showing banking information
 * 
 *    Rev 1.37   Oct 19 2003 18:35:36   popescu
 * CIBC PET 809, FN 13
 * 
 *    Rev 1.36   Oct 19 2003 16:44:42   popescu
 * CIBC, PET809, FN 13 banking work
 * 
 *    Rev 1.35   Sep 05 2003 15:03:10   popescu
 * fix issue in inquiring allocations transnum, wrongly set
 * 
 *    Rev 1.34   Sep 01 2003 21:32:34   popescu
 * PET 809, FN 02 CIBC Multi Fund Transfer
 * 
 *    Rev 1.33   May 16 2003 10:27:32   popescu
 * changed the transaction code to refer to to the TRADETYPE namespace
 * 
 *    Rev 1.32   Mar 21 2003 18:19:58   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.31   Feb 12 2003 16:38:34   KOVACSRO
 * Added isMarginEligible
 * 
 *    Rev 1.30   Oct 09 2002 23:54:48   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.29   Aug 29 2002 12:56:22   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.28   Jun 27 2002 17:20:06   KOVACSRO
 * AllocAmtType versus AmountType.
 * 
 *    Rev 1.27   24 May 2002 15:47:54   KOVACSRO
 * addExistingAlloc versus addNewAlloc
 * 
 *    Rev 1.26   22 May 2002 18:29:36   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.25   08 May 2002 16:54:06   KOVACSRO
 * new allocation design modifications.
 * 
 *    Rev 1.24   01 May 2002 10:23:52   KOVACSRO
 * Don't call view 60 if there are no allocations there.
 * 
 *    Rev 1.23   29 Apr 2002 16:27:22   KOVACSRO
 * New trade allocations.
 * 
 *    Rev 1.22   14 Dec 2001 16:58:12   KOVACSRO
 * bug fixed
 * 
 *    Rev 1.21   Dec 14 2001 10:39:14   JANKAREN
 * fix warning
 * 
 *    Rev 1.20   Dec 13 2001 11:17:42   JANKAREN
 * Added isValidDateLag()
 * 
 *    Rev 1.19   Jun 16 2001 14:25:54   ZHANGCEL
 * Added code to support ExchInFee and ExchInFlatPercent 
 * 
 *    Rev 1.18   31 May 2001 10:06:54   HSUCHIN
 * bug fix
 * 
 *    Rev 1.17   May 29 2001 11:00:18   YINGBAOL
 * sync up version 1.13.2.2
 * 
 *    Rev 1.16   11 May 2001 08:26:38   HSUCHIN
 * Sync up with SSB (1.13.2.1)
 * 
 *    Rev 1.15   May 08 2001 16:00:04   FENGYONG
 * 4 decimal for unit and amount still base on currency
 * 
 *    Rev 1.14   03 May 2001 14:06:54   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.13   Mar 26 2001 10:30:52   YINGZ
 * change AccountAllocationList::initPTAlloc to AccountAllocationList::initAllocList
 * 
 *    Rev 1.12   Mar 18 2001 18:37:10   HSUCHIN
 * bug fix
 * 
 *    Rev 1.11   Mar 15 2001 18:03:00   YINGZ
 * make account/fund allocation work
 * 
 *    Rev 1.10   Mar 12 2001 12:58:50   VASILEAD
 * Modified for FUNDcom release
 * 
 *    Rev 1.9   Feb 19 2001 12:31:02   DINACORN
 * Add Revision Control Entries
 * 
 */
