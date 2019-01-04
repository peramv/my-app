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
//    Copyright 2003 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : TransSettlementInstr.cpp
// ^AUTHOR : Monica Vadeanu
// ^DATE   : November 10, 2003
//
// ^CLASS    : TransSettlementInstr
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"

#include "ifastcbo\TransSettlementInstr.hpp"

#include "ifastcbo\dstcworksession.hpp"
#include "ifastcbo\mfaccount.hpp"
#include "ifastcbo\FundMgmtSettlementInstr.hpp"
#include "ifastcbo\FundMgmtSettlementInstrList.hpp"
#include "ifastcbo\SysLvlSettlementInstr.hpp"
#include "ifastcbo\SysLvlSettlementInstrList.hpp"
#include "ifastcbo\trade.hpp"
#include "ifastcbo\SettlementInstrList.hpp"
#include "ifastcbo\AcctSettlementInstrList.hpp"
#include "ifastcbo\AcctSettlementInstr.hpp"
#include "ifastcbo\FundDetail.hpp"

//#include <ifastdataimpl\dse_dstc_vw.hpp>

#include <ifastdataimpl\dse_dstc0269_vw.hpp>
#include <ifastdataimpl\dse_dstc0269_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0317_vw.hpp>
#include <ifastdataimpl\dse_dstc0317_vwrepeat_record.hpp>


namespace  
{
   const I_CHAR * const CLASSNAME = I_( "TransSettlementInstr" );  
   //Clearning method
   const I_CHAR * const DELIVERYvsPAYMENT          = I_ ("DVP");
   const I_CHAR * const DELIVERYafterPAYMENT       = I_ ("DAP");
   const I_CHAR * const PAYMENTafterDELIVERY       = I_ ("PAD");
   const I_CHAR * const FUNDSETTLE                 = I_ ("FDS");
   const I_CHAR * const FREEofPAYMENT              = I_ ("FOP");
   const I_CHAR * const REALIGNMENT                = I_ ("RLG");
   const I_CHAR * const VESTIMA                    = I_ ("VST");
}

namespace ifds
{	
	extern CLASS_IMPORT const BFTextFieldId FrSettlLocCode;
	extern CLASS_IMPORT const BFTextFieldId FrDeliveryTo;
	extern CLASS_IMPORT const BFTextFieldId FrSettlLocDescription;
	extern CLASS_IMPORT const BFTextFieldId FrInFavourOf;
	extern CLASS_IMPORT const BFTextFieldId FrForAccount;
	extern CLASS_IMPORT const BFTextFieldId FrClearingMethod;
	extern CLASS_IMPORT const BFTextFieldId FrSettlInstrCode;

	extern CLASS_IMPORT const BFTextFieldId ToSettlLocCode;
	extern CLASS_IMPORT const BFTextFieldId ToDeliveryTo;
	extern CLASS_IMPORT const BFTextFieldId ToSettlLocDescription;
	extern CLASS_IMPORT const BFTextFieldId ToInFavourOf;
	extern CLASS_IMPORT const BFTextFieldId ToForAccount;
	extern CLASS_IMPORT const BFTextFieldId ToClearingMethod;
	extern CLASS_IMPORT const BFTextFieldId ToSettlInstrCode;
    extern CLASS_IMPORT const BFTextFieldId AcctSettleInstrCode;
    extern CLASS_IMPORT const BFTextFieldId ClearingIdDefault;
    extern CLASS_IMPORT const BFTextFieldId SettleAccountNum;
    extern CLASS_IMPORT const BFTextFieldId InternalSettlementAccount;
}

namespace  CND
{
   extern const long ERR_CLEARING_METHOD_NOT_ALLOWED_FOR_NON_CLEARING_ACCOUNT;   
	extern const long ERR_CLEARING_METHOD_NOT_ALLOWED_FOR_TRANSACTION_TYPE;   
	extern const long ERR_CLEARING_METHOD_NOT_ALLOWED_FOR_NON_FUNDSETTLE_ACCOUNT;   
	extern const long ERR_CLEARING_METHOD_NOT_ALLOWED_FOR_NON_VESTIMA_ACCOUNT;   
	extern const long ERR_FROM_DELIVERY_TO_MUST_BE_SUPPLIED_FOR_CLEARING_ACCOUNT;   
	extern const long ERR_TO_DELIVERY_TO_MUST_BE_SUPPLIED_FOR_CLEARING_ACCOUNT;   
	extern const long ERR_TRADING_SETTLEMENT_LOCATION_HAS_NOT_BEEN_SETUP_FOR_CLEARING_ACCOUNT;
	extern const long ERR_SETTLEMENT_LOCATION_CODE_FOR_ACCOUNT_DOES_NOT_EXIST_AT_SYSTEM_LEVEL;	
	extern const long ERR_TRADING_SETTLEMENT_LOCATION_INVALID_CODE_FOR_CLEARING_ACCOUNT;
	extern const long WARN_TRADE_SETTLEMENT_INSTRUCTIONS_MISSING_ACCT_LEVEL_DEFAULT;
	extern const long ERR_FROM_CLEARING_METHOD_REALIGNMENT_ONLY_FOR_SAME_FROM_TO_FUND;
	extern const long ERR_FROM_CLEARING_METHOD_REALIGNMENT_ONLY_FOR_SAME_FROM_TO_CLASS;
	extern const long ERR_TO_CLEARING_METHOD_REALIGNMENT_ONLY_FOR_SAME_FROM_TO_FUND;
	extern const long ERR_TO_CLEARING_METHOD_REALIGNMENT_ONLY_FOR_SAME_FROM_TO_CLASS;
	extern const long ERR_CLEARING_METHOD_REALIGNMENT_APPLICABLE_TO_FROM_AND_TO_CLEARING_ACCOUNTS;
	extern const long ERR_FROM_CLEARING_METHOD_CCY_ONLY_FOR_SAME_SETTLE_CURR_FUND_CURR ;
	extern const long ERR_TO_CLEARING_METHOD_CCY_ONLY_FOR_SAME_SETTLE_CURR_FUND_CURR ;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const EXCHANGE;
   extern CLASS_IMPORT I_CHAR * const TRANSFER;
   extern CLASS_IMPORT I_CHAR * const ALL_FUND_TRANSFER;
   extern CLASS_IMPORT I_CHAR * const REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const PURCHASE;
   extern CLASS_IMPORT I_CHAR * const MGMT_FEE;
   extern CLASS_IMPORT I_CHAR * const EXCHANGE_OUT;
   extern CLASS_IMPORT I_CHAR * const ROLLOVER;
   extern CLASS_IMPORT I_CHAR * const REDEMPTION_LIKE;  
   extern CLASS_IMPORT I_CHAR * const PURCHASE_LIKE;
   extern CLASS_IMPORT I_CHAR * const ONE_SIDE_TRADE;
}


namespace SETL_LOC_FIELDS
{

    extern CLASS_EXPORT const  BFFieldId SttlInstrReadOnlyAlways[] = 
    {
         ifds::FrSettlementAccount,            
         ifds::FrInternalSettlementAccount,  
         ifds::ToSettlementAccount,            
         ifds::ToInternalSettlementAccount, 
    };
    extern CLASS_EXPORT const int numSttlInstrReadOnlyAlways = sizeof(SttlInstrReadOnlyAlways) / sizeof(BFFieldId);
    //FROM
    extern CLASS_EXPORT const  BFFieldId SttlInstrFrReadOnlyFields[] = 
    {
         ifds::FrIntermediaryBank,   
         ifds::FrReceivingBank,      
         ifds::FrBeneficiary,         
         ifds::FrSpecialInstructions, 
         ifds::FrCashMsgType, 
    } ;

    extern CLASS_EXPORT const int numSttlInstrFrReadOnlyFields = sizeof(SttlInstrFrReadOnlyFields) / sizeof(BFFieldId);

    extern CLASS_EXPORT const  STTL_INSTR_FIELD_MAPPING SttlInstrFrMapping[] = 
    {
       { ifds::FrIntermediaryBank,      ifds::IntermediaryBank  },  
       { ifds::FrReceivingBank,         ifds::ReceivingBank     },
       { ifds::FrBeneficiary,           ifds::Beneficiary       } ,       
       { ifds::FrSpecialInstructions,   ifds::SpecialInstructions}, 
       { ifds::FrCashMsgType,           ifds::CashMsgType       }, 
    } ;

    extern CLASS_EXPORT const int numSttlInstrFrMapping = sizeof(SttlInstrFrMapping) / sizeof(SttlInstrFieldMapping);

    //TO
    extern CLASS_EXPORT const  BFFieldId SttlInstrToReadOnlyFields[] = 
    { 
         ifds::ToIntermediaryBank,    
         ifds::ToReceivingBank,      
         ifds::ToBeneficiary,         
         ifds::ToSpecialInstructions,
         ifds::ToCashMsgType,   
    } ;

    extern CLASS_EXPORT const int numSttlInstrToReadOnlyFields = sizeof(SttlInstrToReadOnlyFields) / sizeof(BFFieldId);

    extern CLASS_EXPORT const  STTL_INSTR_FIELD_MAPPING SttlInstrToMapping[] = 
    {
       { ifds::ToIntermediaryBank,      ifds::IntermediaryBank  },  
       { ifds::ToReceivingBank,         ifds::ReceivingBank     },
       { ifds::ToBeneficiary,           ifds::Beneficiary       } ,       
       { ifds::ToSpecialInstructions,   ifds::SpecialInstructions}, 
       { ifds::ToCashMsgType,           ifds::CashMsgType       }, 
    } ;

    extern CLASS_EXPORT const int numSttlInstrToMapping = sizeof(SttlInstrToMapping) / sizeof(SttlInstrFieldMapping);
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
   //   Field DD Id,                                       State Flags, Group Flags    
	{ ifds::FrSettlLocCode,        BFCBO::NONE,                 0 }, 
   { ifds::FrDeliveryTo,          BFCBO::IMMEDIATE_VALIDATION, 0 }, 
	{ ifds::FrSettlLocDescription, BFCBO::NONE,                 0 }, 
	{ ifds::FrInFavourOf,          BFCBO::NONE,                 0 }, 
	{ ifds::FrForAccount,          BFCBO::NONE,                 0 }, 
	{ ifds::FrClearingMethod,      BFCBO::IMMEDIATE_VALIDATION, 0 }, 
	{ ifds::ToSettlLocCode,        BFCBO::NONE,                 0 }, 
   { ifds::ToDeliveryTo,          BFCBO::IMMEDIATE_VALIDATION, 0 }, 
	{ ifds::ToSettlLocDescription, BFCBO::NONE,                 0 }, 
	{ ifds::ToInFavourOf,          BFCBO::NONE,                 0 }, 
	{ ifds::ToForAccount,          BFCBO::NONE,                 0 }, 
	{ ifds::ToClearingMethod,      BFCBO::IMMEDIATE_VALIDATION, 0 },   
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
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );


//****************************************************************************
TransSettlementInstr::TransSettlementInstr( BFAbstractCBO &parent )
: MFCanBFCbo( parent ),
_pTrade( NULL ),
_blFrom( false )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );   		

	registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0, 
							  NULL );   	
}

//****************************************************************************
TransSettlementInstr::~TransSettlementInstr()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}   

//****************************************************************************
SEVERITY TransSettlementInstr::init( bool blFrom, 					   
 										 BFAbstractCBO *pTrade, 
										 const DString &dstrAccountNum,
										 const DString &dstrTransType,
										 bool blUpdateableLocation,
										 const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
	
	_dstrAccountNum       = dstrAccountNum;
	_dstrTransType        = dstrTransType;	
	_blFrom               = blFrom;	

	_pTrade = pTrade;

	if ( blUpdateableLocation )
	{
		setObjectNew();
	}
	
	doInitWithDefaultValues( idDataGroup );
		
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void TransSettlementInstr::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doInitWithDefaultValues" ) );

	if ( NULL != _pTrade )
	{				
		DString dstrSettleLocCode, 
				dstrDeliveryTo, 
   				dstrSettleLocDescription, 
			  	dstrInFavourOf, 
				dstrForAccount, 
				dstrClearingMethod,
				dstrSettlInstrCode;

		if ( _blFrom )
		{									
			setSettlementLocationSubstList( idDataGroup, ifds::FrSettlLocCode );
			setSettlementCodeSubstList (idDataGroup, ifds::FrSettlInstrCode);

			_pTrade->getField( ifds::FrSettlLocCode,        dstrSettleLocCode,        idDataGroup );
			_pTrade->getField( ifds::FrDeliveryTo,          dstrDeliveryTo,           idDataGroup );
			_pTrade->getField( ifds::FrSettlLocDescription, dstrSettleLocDescription, idDataGroup );
			_pTrade->getField( ifds::FrInFavourOf,          dstrInFavourOf,           idDataGroup );
			_pTrade->getField( ifds::FrForAccount,          dstrForAccount,           idDataGroup );
			_pTrade->getField( ifds::FrClearingMethod,      dstrClearingMethod,       idDataGroup );
  			_pTrade->getField( ifds::FrSettlInstrCode,      dstrSettlInstrCode,idDataGroup );

			setFieldNoValidate( ifds::FrSettlLocCode,        dstrSettleLocCode,        idDataGroup, false );			
			setFieldNoValidate( ifds::FrDeliveryTo,          dstrDeliveryTo,           idDataGroup );
			setFieldNoValidate( ifds::FrSettlLocDescription, dstrSettleLocDescription, idDataGroup );
			setFieldNoValidate( ifds::FrInFavourOf,          dstrInFavourOf,           idDataGroup );
			setFieldNoValidate( ifds::FrForAccount,          dstrForAccount,           idDataGroup );
			setFieldNoValidate( ifds::FrClearingMethod,      dstrClearingMethod,       idDataGroup );	
			setFieldNoValidate( ifds::FrSettlInstrCode,		 dstrSettlInstrCode,       idDataGroup );
           
            for(int i= 0; i < SETL_LOC_FIELDS::numSttlInstrFrReadOnlyFields;	i++)
            {
               DString dstrValue;
               _pTrade->getField( SETL_LOC_FIELDS::SttlInstrFrReadOnlyFields[i], dstrValue, idDataGroup);
               setFieldNoValidate( SETL_LOC_FIELDS::SttlInstrFrReadOnlyFields[i], dstrValue, idDataGroup);
            }					
		}
		else
		{			
			setSettlementLocationSubstList( idDataGroup, ifds::ToSettlLocCode );	
			setSettlementCodeSubstList (idDataGroup, ifds::ToSettlInstrCode);

			_pTrade->getField( ifds::ToSettlLocCode,        dstrSettleLocCode,        idDataGroup );
			_pTrade->getField( ifds::ToDeliveryTo,          dstrDeliveryTo,           idDataGroup );
			_pTrade->getField( ifds::ToSettlLocDescription, dstrSettleLocDescription, idDataGroup );
			_pTrade->getField( ifds::ToInFavourOf,          dstrInFavourOf,           idDataGroup );
			_pTrade->getField( ifds::ToForAccount,          dstrForAccount,           idDataGroup );
			_pTrade->getField( ifds::ToClearingMethod,      dstrClearingMethod,       idDataGroup );
  			_pTrade->getField( ifds::ToSettlInstrCode,		dstrSettlInstrCode,		  idDataGroup );

			setFieldNoValidate( ifds::ToSettlLocCode,        dstrSettleLocCode,        idDataGroup );
			setFieldNoValidate( ifds::ToDeliveryTo,          dstrDeliveryTo,           idDataGroup );
			setFieldNoValidate( ifds::ToSettlLocDescription, dstrSettleLocDescription, idDataGroup );
			setFieldNoValidate( ifds::ToInFavourOf,          dstrInFavourOf,           idDataGroup );
			setFieldNoValidate( ifds::ToForAccount,          dstrForAccount,           idDataGroup );
			setFieldNoValidate( ifds::ToClearingMethod,      dstrClearingMethod,       idDataGroup );	
			setFieldNoValidate( ifds::ToSettlInstrCode,		 dstrSettlInstrCode,	   idDataGroup );
            
            for(int i= 0; i < SETL_LOC_FIELDS::numSttlInstrToReadOnlyFields;	i++)
            {
               DString dstrValue;
               _pTrade->getField( SETL_LOC_FIELDS::SttlInstrToReadOnlyFields[i], dstrValue, idDataGroup);
               setFieldNoValidate( SETL_LOC_FIELDS::SttlInstrToReadOnlyFields[i], dstrValue, idDataGroup);
            }				
		}
        for(int i= 0; i < SETL_LOC_FIELDS::numSttlInstrReadOnlyAlways;	i++)
        {
            DString dstrValue;  
            _pTrade->getField(  SETL_LOC_FIELDS::SttlInstrReadOnlyAlways[i], dstrValue, idDataGroup);
            setFieldNoValidate( SETL_LOC_FIELDS::SttlInstrReadOnlyAlways[i], dstrValue, idDataGroup); 
        }
	}

	if ( isNew() )
	{
		DString dstrDeliveryTo, dstrInFavourOf, dstrForAccount, dstrSettleInstrCode, dstrClearingMethod;

		getWorkSession().getOption (ifds::ClearingIdDefault, dstrClearingMethod, idDataGroup, false);

		if ( true == _blFrom )
		{
			DString dstrFrSettlLocCode;
			getField( ifds::FrSettlLocCode, dstrFrSettlLocCode, idDataGroup );			
			if ( dstrFrSettlLocCode.stripAll().empty() )	
				setDefaultSettlementLocation( ifds::FrSettlLocCode, idDataGroup );

			if (!dstrClearingMethod.empty())
				setFieldNoValidate (ifds::FrClearingMethod, dstrClearingMethod, idDataGroup, false);

			setFieldReadOnly( ifds::FrSettlLocCode,   idDataGroup, false );
			setFieldReadOnly( ifds::FrDeliveryTo,     idDataGroup, false );			
			setFieldReadOnly( ifds::FrInFavourOf,     idDataGroup, false );
			setFieldReadOnly( ifds::FrForAccount,     idDataGroup, false );
			setFieldReadOnly( ifds::FrClearingMethod, idDataGroup, false );

			setFieldRequired( ifds::FrSettlLocCode,   idDataGroup,true );
			setFieldRequired( ifds::FrClearingMethod, idDataGroup,true );
			setFieldRequired( ifds::FrDeliveryTo,     idDataGroup,true );
			setFieldRequired( ifds::FrSettlInstrCode, idDataGroup,true );
			
			setValidFlag ( ifds::FrSettlLocCode,   idDataGroup, false );
			setValidFlag ( ifds::FrClearingMethod, idDataGroup, false );
			setValidFlag ( ifds::FrDeliveryTo,     idDataGroup, false );
			
			setUpdatedFlag( ifds::FrSettlLocCode,   idDataGroup, true );
			setUpdatedFlag( ifds::FrClearingMethod, idDataGroup, true );				
			setUpdatedFlag( ifds::FrDeliveryTo,     idDataGroup, true );	
  			setUpdatedFlag( ifds::FrSettlInstrCode, idDataGroup, true );

            for(int i= 0; i < SETL_LOC_FIELDS::numSttlInstrFrReadOnlyFields;	i++)
            {
              setFieldReadOnly( SETL_LOC_FIELDS::SttlInstrFrReadOnlyFields[i], idDataGroup, false );
              setValidFlag ( SETL_LOC_FIELDS::SttlInstrFrReadOnlyFields[i],   idDataGroup, false );
              setUpdatedFlag( SETL_LOC_FIELDS::SttlInstrFrReadOnlyFields[i], idDataGroup, true );
            }	
		}
		else 
		{
			DString dstrToSettlLocCode;
			getField( ifds::ToSettlLocCode, dstrToSettlLocCode, idDataGroup );			
			if ( dstrToSettlLocCode.stripAll().empty() )	
				setDefaultSettlementLocation( ifds::ToSettlLocCode, idDataGroup );

			if (!dstrClearingMethod.empty())
				setFieldNoValidate (ifds::ToClearingMethod, dstrClearingMethod, idDataGroup, false);

			setFieldReadOnly( ifds::ToSettlLocCode,   idDataGroup, false );
			setFieldReadOnly( ifds::ToDeliveryTo,     idDataGroup, false );			
			setFieldReadOnly( ifds::ToInFavourOf,     idDataGroup, false );
			setFieldReadOnly( ifds::ToForAccount,     idDataGroup, false );
			setFieldReadOnly( ifds::ToClearingMethod, idDataGroup, false );

			setFieldRequired( ifds::ToSettlLocCode,   idDataGroup, true );
			setFieldRequired( ifds::ToDeliveryTo,     idDataGroup,  true );
			setFieldRequired( ifds::ToClearingMethod, idDataGroup,  true );
  			setFieldRequired( ifds::ToSettlInstrCode, idDataGroup,  true );

			setValidFlag ( ifds::ToSettlLocCode,   idDataGroup, false );
			setValidFlag ( ifds::ToDeliveryTo,     idDataGroup, false );
			setValidFlag ( ifds::ToClearingMethod, idDataGroup, false );
			
			setUpdatedFlag( ifds::ToSettlLocCode,   idDataGroup, true );					
			setUpdatedFlag( ifds::ToDeliveryTo,     idDataGroup, true );						
			setUpdatedFlag( ifds::ToClearingMethod, idDataGroup, true );	
  			setUpdatedFlag( ifds::ToSettlInstrCode, idDataGroup, true );	           
            
            for(int i= 0; i < SETL_LOC_FIELDS::numSttlInstrToReadOnlyFields;	i++)
            {
              setFieldReadOnly( SETL_LOC_FIELDS::SttlInstrToReadOnlyFields[i], idDataGroup, false );
              setValidFlag ( SETL_LOC_FIELDS::SttlInstrToReadOnlyFields[i],   idDataGroup, false );
              setUpdatedFlag( SETL_LOC_FIELDS::SttlInstrToReadOnlyFields[i], idDataGroup, true );
            }			
		}
	}
	else
	{
		if ( true == _blFrom )
		{		   
			setFieldReadOnly( ifds::FrSettlLocCode,   idDataGroup, true );
			setFieldReadOnly( ifds::FrDeliveryTo,     idDataGroup, true );			
			setFieldReadOnly( ifds::FrInFavourOf,     idDataGroup, true );
			setFieldReadOnly( ifds::FrForAccount,     idDataGroup, true );
			setFieldReadOnly( ifds::FrClearingMethod, idDataGroup, true );		
  			setFieldReadOnly( ifds::FrSettlInstrCode, idDataGroup, true );	
            for(int i= 0; i < SETL_LOC_FIELDS::numSttlInstrFrReadOnlyFields;	i++)
            {
               setFieldReadOnly( SETL_LOC_FIELDS::SttlInstrFrReadOnlyFields[i], idDataGroup, true );
            }            	
		}
		else 
		{
			setFieldReadOnly( ifds::ToSettlLocCode,   idDataGroup, true );
			setFieldReadOnly( ifds::ToDeliveryTo,     idDataGroup, true );			
			setFieldReadOnly( ifds::ToInFavourOf,     idDataGroup, true );
			setFieldReadOnly( ifds::ToForAccount,     idDataGroup, true );
			setFieldReadOnly( ifds::ToClearingMethod, idDataGroup, true );
  			setFieldReadOnly( ifds::ToSettlInstrCode, idDataGroup, true );	
            for(int i= 0; i < SETL_LOC_FIELDS::numSttlInstrToReadOnlyFields;	i++)
            {
               setFieldReadOnly( SETL_LOC_FIELDS::SttlInstrToReadOnlyFields[i], idDataGroup, true );
            }			
		}
	}
    for(int i= 0; i < SETL_LOC_FIELDS::numSttlInstrReadOnlyAlways;	i++)
    {
      setFieldReadOnly( SETL_LOC_FIELDS::SttlInstrReadOnlyAlways[i], idDataGroup, true );
      setValidFlag ( SETL_LOC_FIELDS::SttlInstrReadOnlyAlways[i],   idDataGroup, true );
      setFieldUpdated( SETL_LOC_FIELDS::SttlInstrReadOnlyAlways[i], idDataGroup, false );
    }
}

//******************************************************************************
void TransSettlementInstr::doReset ( const BFDataGroupId& idDataGroup )
{
	if ( NULL != _pTrade && isNew() )
	{				
		DString	dstrSettleLocCode, 
			    dstrDeliveryTo, 
   				dstrSettleLocDescription, 
			  	dstrInFavourOf, 
				dstrForAccount, 
				dstrClearingMethod,
				dstrSettleInstrCode;

		if ( _blFrom )
		{						
			_pTrade->getFieldBeforeImage( ifds::FrSettlLocCode,        dstrSettleLocCode );
			_pTrade->getFieldBeforeImage( ifds::FrDeliveryTo,          dstrDeliveryTo  );
			_pTrade->getFieldBeforeImage( ifds::FrSettlLocDescription, dstrSettleLocDescription );
			_pTrade->getFieldBeforeImage( ifds::FrInFavourOf,          dstrInFavourOf  );
			_pTrade->getFieldBeforeImage( ifds::FrForAccount,          dstrForAccount  );
			_pTrade->getFieldBeforeImage( ifds::FrClearingMethod,      dstrClearingMethod );
  			_pTrade->getFieldBeforeImage( ifds::FrSettlInstrCode,	   dstrSettleInstrCode );
			
			_pTrade->setField( ifds::FrSettlLocCode,        dstrSettleLocCode,        idDataGroup );
			_pTrade->setField( ifds::FrDeliveryTo,          dstrDeliveryTo,           idDataGroup );
			_pTrade->setField( ifds::FrSettlLocDescription, dstrSettleLocDescription, idDataGroup );
			_pTrade->setField( ifds::FrInFavourOf,          dstrInFavourOf,           idDataGroup );
			_pTrade->setField( ifds::FrForAccount,          dstrForAccount,           idDataGroup );
			_pTrade->setField( ifds::FrClearingMethod,      dstrClearingMethod,       idDataGroup );	
			_pTrade->setField( ifds::FrSettlInstrCode,		dstrSettleInstrCode,      idDataGroup );

            for(int i= 0; i < SETL_LOC_FIELDS::numSttlInstrFrReadOnlyFields;	i++)
            {
               DString dstrFieldValueBeforeImage;
               _pTrade->getFieldBeforeImage( SETL_LOC_FIELDS::SttlInstrFrReadOnlyFields[i], dstrFieldValueBeforeImage);
               _pTrade->setField( SETL_LOC_FIELDS::SttlInstrFrReadOnlyFields[i], dstrFieldValueBeforeImage, idDataGroup);
            }	
                        	
		}
		else
		{	
			_pTrade->getFieldBeforeImage( ifds::ToSettlLocCode,        dstrSettleLocCode );
			_pTrade->getFieldBeforeImage( ifds::ToDeliveryTo,          dstrDeliveryTo  );
			_pTrade->getFieldBeforeImage( ifds::ToSettlLocDescription, dstrSettleLocDescription );
			_pTrade->getFieldBeforeImage( ifds::ToInFavourOf,          dstrInFavourOf  );
			_pTrade->getFieldBeforeImage( ifds::ToForAccount,          dstrForAccount  );
			_pTrade->getFieldBeforeImage( ifds::ToClearingMethod,      dstrClearingMethod );
			_pTrade->getFieldBeforeImage( ifds::ToSettlInstrCode,	   dstrSettleInstrCode );

			_pTrade->setField( ifds::ToSettlLocCode,        dstrSettleLocCode,        idDataGroup );
			_pTrade->setField( ifds::ToDeliveryTo,          dstrDeliveryTo,           idDataGroup );
			_pTrade->setField( ifds::ToSettlLocDescription, dstrSettleLocDescription, idDataGroup );
			_pTrade->setField( ifds::ToInFavourOf,          dstrInFavourOf,           idDataGroup );
			_pTrade->setField( ifds::ToForAccount,          dstrForAccount,           idDataGroup );
			_pTrade->setField( ifds::ToClearingMethod,      dstrClearingMethod,       idDataGroup );
			_pTrade->setField( ifds::ToSettlInstrCode,		dstrSettleInstrCode,      idDataGroup );

             for(int i= 0; i < SETL_LOC_FIELDS::numSttlInstrToReadOnlyFields;	i++)
            {
               DString dstrFieldValueBeforeImage;
               _pTrade->getFieldBeforeImage( SETL_LOC_FIELDS::SttlInstrToReadOnlyFields[i], dstrFieldValueBeforeImage);
               _pTrade->setField( SETL_LOC_FIELDS::SttlInstrToReadOnlyFields[i], dstrFieldValueBeforeImage, idDataGroup);
            }					
		}
        for(int i= 0; i < SETL_LOC_FIELDS::numSttlInstrReadOnlyAlways;	i++)
        {
            DString dstrValue;  
            _pTrade->getFieldBeforeImage(  SETL_LOC_FIELDS::SttlInstrReadOnlyAlways[i], dstrValue );
            _pTrade->setField( SETL_LOC_FIELDS::SttlInstrReadOnlyAlways[i], dstrValue, idDataGroup);
            setFieldReadOnly( SETL_LOC_FIELDS::SttlInstrReadOnlyAlways[i], idDataGroup, true); 
            setFieldUpdated( SETL_LOC_FIELDS::SttlInstrReadOnlyAlways[i], idDataGroup, false );
        }
	}	
}

//******************************************************************************
SEVERITY TransSettlementInstr::doApplyRelatedChanges( const BFFieldId &fieldId,
													  const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

	if ( ifds::FrSettlLocCode == fieldId && isNew() )
	{
		setSettleLocationDescription( ifds::FrSettlLocCode, idDataGroup, ifds::FrSettlLocDescription );		
	}
	else if ( ifds::ToSettlLocCode == fieldId && isNew() )
	{
		setSettleLocationDescription( ifds::ToSettlLocCode, idDataGroup, ifds::ToSettlLocDescription );
	}

   if (ifds::FrSettlInstrCode == fieldId)
   {

      DString dstrDeliveryTo, dstrInFavourOf, dstrForAccount, dstrClearingMethod, dstrSettleInstrCode;
      
      getField(ifds::FrSettlInstrCode, dstrSettleInstrCode, idDataGroup);

  		AcctSettlementInstr *pAcctSettlementInstr = NULL;

      if ( setAcctSettlementInstr( pAcctSettlementInstr, dstrSettleInstrCode, idDataGroup ) >= WARNING
            && pAcctSettlementInstr != NULL) 
      {
  		   pAcctSettlementInstr->getField( ifds::DeliveryTo, dstrDeliveryTo, idDataGroup );
		   pAcctSettlementInstr->getField( ifds::InFavourOf, dstrInFavourOf, idDataGroup );
		   pAcctSettlementInstr->getField( ifds::ForAccount, dstrForAccount, idDataGroup );
  			_pTrade->setField( ifds::FrDeliveryTo, dstrDeliveryTo, idDataGroup );
			_pTrade->setField( ifds::FrInFavourOf,          dstrInFavourOf,           idDataGroup );
			_pTrade->setField( ifds::FrForAccount,          dstrForAccount,           idDataGroup );
           //defualt from the account level
           for(int i= 0; i < SETL_LOC_FIELDS::numSttlInstrFrMapping;	i++)
            {
               DString dstrValue;
               pAcctSettlementInstr->getField( SETL_LOC_FIELDS::SttlInstrFrMapping[i].MappedFieldId, dstrValue, idDataGroup );
               _pTrade->setField( SETL_LOC_FIELDS::SttlInstrFrMapping[i].OrgFieldId, dstrValue, idDataGroup );
            }	
           setAccountNumbersFromSystemLevel(idDataGroup);

         if (dstrSettleInstrCode != I_("N/A")  )
         {
			   setFieldReadOnly( ifds::FrDeliveryTo, idDataGroup, true );			
			   setFieldReadOnly( ifds::FrInFavourOf, idDataGroup, true );
			   setFieldReadOnly( ifds::FrForAccount, idDataGroup, true );
               for(int i= 0; i < SETL_LOC_FIELDS::numSttlInstrFrReadOnlyFields;	i++)
               {
                setFieldReadOnly( SETL_LOC_FIELDS::SttlInstrFrReadOnlyFields[i], idDataGroup, true );
               }	
         }
         else
         {
			   setFieldReadOnly( ifds::FrDeliveryTo, idDataGroup, false );			
			   setFieldReadOnly( ifds::FrInFavourOf, idDataGroup, false );
			   setFieldReadOnly( ifds::FrForAccount, idDataGroup, false );
               for(int i= 0; i < SETL_LOC_FIELDS::numSttlInstrFrReadOnlyFields;	i++)
               {
                setFieldReadOnly( SETL_LOC_FIELDS::SttlInstrFrReadOnlyFields[i], idDataGroup, false );
               }
         }
  		setFieldRequired( ifds::FrDeliveryTo, idDataGroup,true );
	    setFieldRequired( ifds::FrInFavourOf, idDataGroup,true );
		setFieldRequired( ifds::FrForAccount, idDataGroup,true );
      }
   }

   else if (ifds::ToSettlInstrCode == fieldId)
   {

      DString dstrDeliveryTo, dstrInFavourOf, dstrForAccount, dstrClearingMethod, dstrSettleInstrCode;
      
      getField(ifds::ToSettlInstrCode, dstrSettleInstrCode, idDataGroup);

  		AcctSettlementInstr *pAcctSettlementInstr = NULL;

      if ( setAcctSettlementInstr( pAcctSettlementInstr, dstrSettleInstrCode, idDataGroup ) >= WARNING
            && pAcctSettlementInstr != NULL) 
      {
  		   pAcctSettlementInstr->getField( ifds::DeliveryTo, dstrDeliveryTo, idDataGroup );
		   pAcctSettlementInstr->getField( ifds::InFavourOf, dstrInFavourOf, idDataGroup );
		   pAcctSettlementInstr->getField( ifds::ForAccount, dstrForAccount, idDataGroup );

			_pTrade->setField( ifds::ToDeliveryTo, dstrDeliveryTo, idDataGroup );
			_pTrade->setField( ifds::ToInFavourOf,          dstrInFavourOf,           idDataGroup );
			_pTrade->setField( ifds::ToForAccount,          dstrForAccount,           idDataGroup );

           //defualt from the account level
           for(int i= 0; i < SETL_LOC_FIELDS::numSttlInstrToMapping;	i++)
            {
               DString dstrValue;
               pAcctSettlementInstr->getField( SETL_LOC_FIELDS::SttlInstrToMapping[i].MappedFieldId, dstrValue, idDataGroup );
               _pTrade->setField( SETL_LOC_FIELDS::SttlInstrToMapping[i].OrgFieldId, dstrValue, idDataGroup );
            }	
           setAccountNumbersFromSystemLevel(idDataGroup);
         if (dstrSettleInstrCode != I_("N/A")  )
         {
			   setFieldReadOnly( ifds::ToDeliveryTo, idDataGroup, true );			
			   setFieldReadOnly( ifds::ToInFavourOf, idDataGroup, true );
			   setFieldReadOnly( ifds::ToForAccount, idDataGroup, true );
         }
         else
         {
			   setFieldReadOnly( ifds::ToDeliveryTo, idDataGroup, false );			
			   setFieldReadOnly( ifds::ToInFavourOf, idDataGroup, false );
			   setFieldReadOnly( ifds::ToForAccount, idDataGroup, false );
         }
       //should be to fields..seems like an unexplored bug..why it is From here
  			setFieldRequired( ifds::FrDeliveryTo, idDataGroup,true );
			setFieldRequired( ifds::FrInFavourOf, idDataGroup,true );
			setFieldRequired( ifds::FrForAccount, idDataGroup,true );
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY TransSettlementInstr::doValidateField( const BFFieldId& idField, 
													   const DString& strValue, 
														const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

   if( ifds::FrClearingMethod == idField ||
		 ifds::ToClearingMethod == idField )
	{
      validateClearingMethod( strValue, idField, idDataGroup );
	}
	else if ( ifds::FrDeliveryTo == idField )
	{		
		DString dstrLocalDeliveryTo( strValue );
		if ( 0 == dstrLocalDeliveryTo.stripAll().length() )
			ADDCONDITIONFROMFILE( CND::ERR_FROM_DELIVERY_TO_MUST_BE_SUPPLIED_FOR_CLEARING_ACCOUNT );
	}
	else if ( ifds::ToDeliveryTo == idField )
	{		
		DString dstrLocalDeliveryTo( strValue );
		if ( 0 == dstrLocalDeliveryTo.stripAll().length() )
			ADDCONDITIONFROMFILE( CND::ERR_TO_DELIVERY_TO_MUST_BE_SUPPLIED_FOR_CLEARING_ACCOUNT );
	}	
	
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY TransSettlementInstr::validateClearingMethod( const DString &dstrClearingMethod,
																 const BFFieldId& idField,
		                                           const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateClearingMethod" ) );	

	MFAccount *pMFAccount = NULL;
   if (  getWorkSession().getMFAccount ( idDataGroup, _dstrAccountNum, pMFAccount ) <= WARNING &&
		  NULL != pMFAccount )
	{
		DString dstrClearingId;
		pMFAccount->getField( ifds::ClearingID, dstrClearingId, idDataGroup );
		dstrClearingId.stripAll();
	
		// DAP, DVP, PAD available for Purchase and Redemption in a 'Clearing' Account
      if (DELIVERYvsPAYMENT == dstrClearingMethod ||
			 DELIVERYafterPAYMENT== dstrClearingMethod ||
			 PAYMENTafterDELIVERY == dstrClearingMethod)
		{
  			if ( DSTCommonFunctions::codeInList (_dstrTransType, TRADETYPE::PURCHASE_LIKE) ||
              DSTCommonFunctions::codeInList (_dstrTransType, TRADETYPE::REDEMPTION_LIKE))  
			{
            if ( I_("C") != dstrClearingId)
            {
               ADDCONDITIONFROMFILE (CND::ERR_CLEARING_METHOD_NOT_ALLOWED_FOR_NON_CLEARING_ACCOUNT);
            }
			}
   		else // if not purchase nor redemption, these clearing method are not applicable
         {
				ADDCONDITIONFROMFILE (CND::ERR_CLEARING_METHOD_NOT_ALLOWED_FOR_TRANSACTION_TYPE);
			}

		}
		// FOP available for PW, ED, TR, AFTR, EX in a Clearing Account
		else if ( FREEofPAYMENT == dstrClearingMethod && I_ ("C") != dstrClearingId) 
		{			
			ADDCONDITIONFROMFILE( CND::ERR_CLEARING_METHOD_NOT_ALLOWED_FOR_NON_CLEARING_ACCOUNT );		
		}
		// RLG available for Transfers in a 'Clearing' Acount
		else if ( REALIGNMENT == dstrClearingMethod)
		{
			if ( I_( "TR" ) == _dstrTransType || I_( "AFTR" ) == _dstrTransType )		 
			{
				if (  I_( "C" ) != dstrClearingId  ) 
            {
               ADDCONDITIONFROMFILE( CND::ERR_CLEARING_METHOD_NOT_ALLOWED_FOR_NON_CLEARING_ACCOUNT );
            }
   			else 
            {
				   ADDCONDITIONFROMFILE( CND::ERR_CLEARING_METHOD_NOT_ALLOWED_FOR_TRANSACTION_TYPE );
			   }
         }
			if ( ( I_( "TR" ) == _dstrTransType || I_( "AFTR" ) == _dstrTransType ) && 
				  I_( "C" ) == dstrClearingId  &&
				  _pTrade != NULL ) 
			{
				// Check if both accounts are "Clearing"
				BFFieldId fieldIdAccount;
				if ( _blFrom )
				{
					fieldIdAccount = ifds::AccountTo;					
				}
				else
				{
					fieldIdAccount = ifds::AccountNum;
				}

				DString dstrAccount;
				_pTrade->getField( fieldIdAccount, dstrAccount, idDataGroup );
				MFAccount *pMFAccount = NULL;
				if (  getWorkSession().getMFAccount ( idDataGroup, dstrAccount, pMFAccount ) <= WARNING &&
						NULL != pMFAccount )
				{
					DString dstrAcctClearingId;
					pMFAccount->getField( ifds::ClearingID, dstrAcctClearingId, idDataGroup );
					if ( I_( "C" ) != dstrAcctClearingId.stripAll() )
					{
						// Realignment Method is applicable when both From and To Account are Clearing Accounts
						ADDCONDITIONFROMFILE( CND::ERR_CLEARING_METHOD_REALIGNMENT_APPLICABLE_TO_FROM_AND_TO_CLEARING_ACCOUNTS );	
					}
				}																
				
				DString dstrFromFund, dstrFromClass, dstrToFund, dstrToClass;
				_pTrade->getField( ifds::FromFund,  dstrFromFund,  idDataGroup );
				_pTrade->getField( ifds::FromClass, dstrFromClass, idDataGroup );
				_pTrade->getField( ifds::ToFund,    dstrToFund,    idDataGroup );
				_pTrade->getField( ifds::ToClass,   dstrToClass,   idDataGroup );

				if ( dstrFromFund.stripAll() != dstrToFund.stripAll() )
				{
					if ( _blFrom )
					{
						// Realignment Method for From side of Settlement Instruction allowed only for same From and To Fund.
						ADDCONDITIONFROMFILE( CND::ERR_FROM_CLEARING_METHOD_REALIGNMENT_ONLY_FOR_SAME_FROM_TO_FUND );
					}
					else
					{
						// Realignment Method for To side of Settlement Instruction allowed only for same From and To Fund.
						ADDCONDITIONFROMFILE( CND::ERR_TO_CLEARING_METHOD_REALIGNMENT_ONLY_FOR_SAME_FROM_TO_FUND );
					}
				}

				if ( dstrFromClass.stripAll() != dstrToClass.stripAll() )
				{
					if ( _blFrom )
					{
						// Realignment Method for From side of Settlement Instruction allowed only for same From and To Class.
						ADDCONDITIONFROMFILE( CND::ERR_FROM_CLEARING_METHOD_REALIGNMENT_ONLY_FOR_SAME_FROM_TO_CLASS );
					}
					else
					{
						// Realignment Method for To side of Settlement Instruction allowed only for same From and To Class.
						ADDCONDITIONFROMFILE( CND::ERR_TO_CLEARING_METHOD_REALIGNMENT_ONLY_FOR_SAME_FROM_TO_CLASS );
					}
				}
			}
		}
		//FDS available for PW, ED, TR, AFTR, EX in a Fund Settle Account
		else if ( FUNDSETTLE == dstrClearingMethod && I_ ("F") != dstrClearingId )
		{
			ADDCONDITIONFROMFILE( CND::ERR_CLEARING_METHOD_NOT_ALLOWED_FOR_NON_FUNDSETTLE_ACCOUNT );			
		}
		// VST available for PW, ED, TR, AFTR, EX in a Vestima Account
		else if ( VESTIMA == dstrClearingMethod && I_ ("V") != dstrClearingId )
		{		
			ADDCONDITIONFROMFILE( CND::ERR_CLEARING_METHOD_NOT_ALLOWED_FOR_NON_VESTIMA_ACCOUNT );		
		}
		else if ( dstrClearingMethod == I_("CCY") )
		{

  			DString dstrFundCode, dstrClassCode, dstrSettleCurrency, dstrFundCurrency;

			_pTrade->getField( ifds::FromFund,  dstrFundCode,  idDataGroup );
			_pTrade->getField( ifds::FromClass, dstrClassCode, idDataGroup );
			_pTrade->getField( ifds::FromClass, dstrSettleCurrency, idDataGroup );


			FundDetail *pFundDetail = NULL;

			if ( getWorkSession ().getFundDetail ( dstrFundCode, 
													dstrClassCode, 
													idDataGroup, 
													pFundDetail )
				&& pFundDetail)
			{
				pFundDetail->getField (ifds::Currency, dstrFundCurrency, idDataGroup, false);
			}

			if ( dstrSettleCurrency != dstrFundCurrency )
			{
     			ADDCONDITIONFROMFILE( CND::ERR_FROM_CLEARING_METHOD_CCY_ONLY_FOR_SAME_SETTLE_CURR_FUND_CURR );		
   				ADDCONDITIONFROMFILE( CND::ERR_TO_CLEARING_METHOD_CCY_ONLY_FOR_SAME_SETTLE_CURR_FUND_CURR );		

			}
		}
	}

	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY TransSettlementInstr::setSettlementLocationSubstList( const BFDataGroupId& idDataGroup,
																		   const BFFieldId& idFieldCode )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setSettlementLocationSubstList" ) );
	
	bool blSuccess = true;
	DString dstrSettlementLocations;

	MFAccount *pMFAccount = NULL;
   if (  getWorkSession().getMFAccount ( idDataGroup, _dstrAccountNum, pMFAccount ) <= WARNING &&
		  NULL != pMFAccount )
	{
		FundMgmtSettlementInstrList *pSettlementLocationAcctList = NULL;
		if ( pMFAccount->getFundMgmtSettlementInstrList( pSettlementLocationAcctList, 
			                                                 idDataGroup, 
																			 true ) <= WARNING &&
			  NULL != pSettlementLocationAcctList )
		{
			BFObjIter settlementLocationAcctListIter( *pSettlementLocationAcctList, 
				                                       idDataGroup, 
																	true, 
																	BFObjIter::ITERTYPE::NON_DELETED );
         
         settlementLocationAcctListIter.begin();  
			
			SysLvlSettlementInstrList *pSysLvlSettlementInstrList = NULL;
			if ( getWorkSession().getSettlementLocationSysLvlList( pSysLvlSettlementInstrList, 
					                                                 idDataGroup, 
																					 true ) <= WARNING &&
				  NULL != pSysLvlSettlementInstrList )
			{				
				while( !settlementLocationAcctListIter.end() )
				{
					FundMgmtSettlementInstr *pFundMgmtSettlementInstr = dynamic_cast<FundMgmtSettlementInstr*>( settlementLocationAcctListIter.getObject() );
					DString dstrSettleLocationCode;
					pFundMgmtSettlementInstr->getField( ifds::SettleLocationCode, dstrSettleLocationCode, idDataGroup );

					SysLvlSettlementInstr *pSysLvlSettlementInstr = NULL;
					if ( pSysLvlSettlementInstrList->getSysLvlSettlementInstr( dstrSettleLocationCode, 
	  				 			  										                  pSysLvlSettlementInstr, 
																		                  idDataGroup ) <= WARNING &&
						  NULL != pSysLvlSettlementInstr )
					{
						DString dstrSettleLocationDesc;
						pSysLvlSettlementInstr->getField( ifds::SettleLocationDesc, dstrSettleLocationDesc, idDataGroup );
									
						dstrSettlementLocations += dstrSettleLocationCode + I_("=") + dstrSettleLocationDesc + I_(";");				
						dstrSettleLocationCode = I_( "" );
					}		
					else
					{
						blSuccess = false;
						break;
					}

					++settlementLocationAcctListIter;         
				}	
			}
		}
		else			
			ADDCONDITIONFROMFILE( CND::ERR_TRADING_SETTLEMENT_LOCATION_HAS_NOT_BEEN_SETUP_FOR_CLEARING_ACCOUNT );
	}
	
   if ( blSuccess )
		setFieldAllSubstituteValues( idFieldCode, idDataGroup, dstrSettlementLocations );
	else
		ADDCONDITIONFROMFILE( CND::ERR_TRADING_SETTLEMENT_LOCATION_INVALID_CODE_FOR_CLEARING_ACCOUNT );		

	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY TransSettlementInstr::setDefaultSettlementLocation( const BFFieldId& idFieldCode,
								             						       const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setDefaultSettlementLocation" ) );

	bool blHasDefault = false;

	MFAccount *pMFAccount = NULL;
   if (  getWorkSession().getMFAccount ( idDataGroup, _dstrAccountNum, pMFAccount ) <= WARNING &&
		  NULL != pMFAccount )
	{
		FundMgmtSettlementInstrList *pSettlementLocationAcctList = NULL;
		if ( pMFAccount->getFundMgmtSettlementInstrList( pSettlementLocationAcctList, 
			                                                 idDataGroup, 
																			 true ) <= WARNING &&
			  NULL != pSettlementLocationAcctList )
		{
			BFObjIter settlementLocationAcctListIter( *pSettlementLocationAcctList, 
				                                       idDataGroup, 
																	true, 
																	BFObjIter::ITERTYPE::NON_DELETED );
         
         settlementLocationAcctListIter.begin();  						
			while( !settlementLocationAcctListIter.end() )
			{
				FundMgmtSettlementInstr *pFundMgmtSettlementInstr = dynamic_cast<FundMgmtSettlementInstr*>( settlementLocationAcctListIter.getObject() );
				if ( NULL != pFundMgmtSettlementInstr )
				{
					DString dstrDefault;
					pFundMgmtSettlementInstr->getField( ifds::Default, dstrDefault, idDataGroup ) ;
					if ( I_( "Y" ) == dstrDefault )
					{
						DString dstrSettleLocationCode;
						pFundMgmtSettlementInstr->getField( ifds::SettleLocationCode, dstrSettleLocationCode, idDataGroup );
						// Current method is called only for New Trade, so we'll set 
						// lFormatted = true, lSideEffect = true, bCheckCurrentValue = false
						setField( idFieldCode, dstrSettleLocationCode, idDataGroup, true, true, false );	
						blHasDefault = true;
						break;
					}
				}
				++settlementLocationAcctListIter;         
			}		
		}
	}

	if ( false == blHasDefault )
		ADDCONDITIONFROMFILE( CND::WARN_TRADE_SETTLEMENT_INSTRUCTIONS_MISSING_ACCT_LEVEL_DEFAULT );

	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY TransSettlementInstr::setSettleLocationDescription( const BFFieldId& idFieldCode, 
																		 const BFDataGroupId& idDataGroup,
																		 const BFFieldId& idFieldDescription )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setSettleLocationDescription" ) );

	bool blSettleLocDescExists = false;

	DString dstrSettleLocCode;
	getField( idFieldCode, dstrSettleLocCode, idDataGroup );
	SysLvlSettlementInstrList *pSysLvlSettlementInstrList = NULL;
	if ( getWorkSession().getSettlementLocationSysLvlList( pSysLvlSettlementInstrList, 
		                                                    idDataGroup, 
																			 true ) <= WARNING &&
        NULL != pSysLvlSettlementInstrList )
	{
		SysLvlSettlementInstr *pSysLvlSettlementInstr = NULL;
		if ( pSysLvlSettlementInstrList->getSysLvlSettlementInstr( dstrSettleLocCode, 
	  				 			  										         pSysLvlSettlementInstr, 
																		         idDataGroup ) <= WARNING &&
			  NULL != pSysLvlSettlementInstr )
		{
			DString dstrSettleLocDescription;
			pSysLvlSettlementInstr->getField( ifds::SettleLocationDesc, dstrSettleLocDescription, idDataGroup );

			setField( idFieldDescription, dstrSettleLocDescription, idDataGroup );
			blSettleLocDescExists = true;
		}
	}	

	if ( false == blSettleLocDescExists )
	{
		ADDCONDITIONFROMFILE( CND::ERR_SETTLEMENT_LOCATION_CODE_FOR_ACCOUNT_DOES_NOT_EXIST_AT_SYSTEM_LEVEL );		
	}

	return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
SEVERITY TransSettlementInstr::setSettlementCodeSubstList(	const BFDataGroupId& idDataGroup,
                                                            const BFFieldId& idFieldCode)
	                                                         
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setSettlementCodeSubstList" ) );
	
	DString dstrSettleInstrSubstList;
	SettlementInstrList*  pSettlementInstrList = NULL;

	if ( pSettlementInstrList->getSettlementCodeSubstList( dstrSettleInstrSubstList, idDataGroup ) <= WARNING &&
        !dstrSettleInstrSubstList.strip().empty() )
	{
		dstrSettleInstrSubstList.upperCase ();

		setFieldAllSubstituteValues (ifds::FrSettlInstrCode, idDataGroup, dstrSettleInstrSubstList);
		setFieldAllSubstituteValues (ifds::FrSettlInstrCode, idDataGroup, dstrSettleInstrSubstList);
	}

	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY TransSettlementInstr::setDefaultAcctSettlementInstr(const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setDefaultAcctSettlementLocation" ) );
	
	bool blHasDefault = false;

	MFAccount *pMFAccount = NULL;

	if (  getWorkSession().getMFAccount ( idDataGroup, _dstrAccountNum, pMFAccount ) <= WARNING 
		&& NULL != pMFAccount )
	{
		AcctSettlementInstrList *pAcctSettlementInstrList = NULL;
		if ( pMFAccount->getSettlementInstrList(	pAcctSettlementInstrList, 
													idDataGroup, 
													true ) <= WARNING &&
			  NULL != pAcctSettlementInstrList )
		{
			BFObjIter acctSettlementInstrListIter( *pAcctSettlementInstrList, 
				                                       idDataGroup, 
																	true, 
																	BFObjIter::ITERTYPE::NON_DELETED );
         
         acctSettlementInstrListIter.begin();  
         
	      while( !acctSettlementInstrListIter.end() )
	      {
  		      DString dstrDefaultSettleInstrCode;
		      acctSettlementInstrListIter.getObject()->getField( ifds::DefaultSettlementInstr, dstrDefaultSettleInstrCode, idDataGroup );


				if ( I_( "Y" ) == dstrDefaultSettleInstrCode )
				{
  					DString dstrSettleInstrCode, dstrDeliveryTo, dstrInFavourOf, dstrForAccount;

               if ( true == _blFrom )
               {
                       //ourious how this is working as there is no field FrSettlInstrCode in the AcctSettlementInstrList..
                       //wouldn't it be blank always 
					   pAcctSettlementInstrList->getField( ifds::FrSettlInstrCode, dstrSettleInstrCode, idDataGroup );
					   pAcctSettlementInstrList->getField( ifds::FrDeliveryTo, dstrDeliveryTo, idDataGroup );
					   pAcctSettlementInstrList->getField( ifds::FrInFavourOf, dstrInFavourOf, idDataGroup );
					   pAcctSettlementInstrList->getField( ifds::FrForAccount, dstrForAccount, idDataGroup );

                  setField( ifds::FrSettlInstrCode, dstrSettleInstrCode, idDataGroup, true, true, false );
                  setField( ifds::FrDeliveryTo, dstrDeliveryTo, idDataGroup, true, true, false );
                  setField( ifds::FrInFavourOf, dstrInFavourOf, idDataGroup, true, true, false );
                  setField( ifds::FrForAccount, dstrForAccount, idDataGroup, true, true, false );
               
                  //defualt from the account level
                  for(int i= 0; i < SETL_LOC_FIELDS::numSttlInstrFrMapping;	i++)
                  {
                    DString dstrValue;
                    pAcctSettlementInstrList->getField( SETL_LOC_FIELDS::SttlInstrFrMapping[i].MappedFieldId, dstrValue, idDataGroup );
                    _pTrade->setField( SETL_LOC_FIELDS::SttlInstrFrMapping[i].OrgFieldId, dstrValue, idDataGroup );
                  }	
                  setAccountNumbersFromSystemLevel(idDataGroup);
              
               }
               else
               {
                      //curious why the same fields for the from and to sides !
					   pAcctSettlementInstrList->getField( ifds::FrSettlInstrCode, dstrSettleInstrCode, idDataGroup );
					   pAcctSettlementInstrList->getField( ifds::FrDeliveryTo, dstrDeliveryTo, idDataGroup );
					   pAcctSettlementInstrList->getField( ifds::FrInFavourOf, dstrInFavourOf, idDataGroup );
					   pAcctSettlementInstrList->getField( ifds::FrForAccount, dstrForAccount, idDataGroup );

                  setField( ifds::FrSettlInstrCode, dstrSettleInstrCode, idDataGroup, true, true, false );
                  setField( ifds::FrDeliveryTo, dstrDeliveryTo, idDataGroup, true, true, false );
                  setField( ifds::FrInFavourOf, dstrInFavourOf, idDataGroup, true, true, false );
                  setField( ifds::FrForAccount, dstrForAccount, idDataGroup, true, true, false );

                  //defualt from the account level
                  for(int i= 0; i < SETL_LOC_FIELDS::numSttlInstrToMapping;	i++)
                  {
                    DString dstrValue;
                    pAcctSettlementInstrList->getField( SETL_LOC_FIELDS::SttlInstrToMapping[i].MappedFieldId, dstrValue, idDataGroup );
                    _pTrade->setField( SETL_LOC_FIELDS::SttlInstrToMapping[i].OrgFieldId, dstrValue, idDataGroup );
                  }	
                  setAccountNumbersFromSystemLevel(idDataGroup);
               }

               blHasDefault = true;
					break;
				}		
		      
		      ++acctSettlementInstrListIter;         
	      }
      }
   } 

	if ( false == blHasDefault )
		ADDCONDITIONFROMFILE( CND::WARN_TRADE_SETTLEMENT_INSTRUCTIONS_MISSING_ACCT_LEVEL_DEFAULT );

	return(GETCURRENTHIGHESTSEVERITY());

}

//******************************************************************************
SEVERITY TransSettlementInstr::setAcctSettlementInstr( AcctSettlementInstr *&pAcctSettlementInstr,
                                                       const DString &dstrSettlInstrCode, 
                                                       const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setAcctSettlementInstr" ) );

   MFAccount *pMFAccount = NULL;

   if (  getWorkSession().getMFAccount ( idDataGroup, _dstrAccountNum, pMFAccount ) <= WARNING &&
		  NULL != pMFAccount )
	{
		AcctSettlementInstrList *pAcctSettlementInstrList = NULL;

		if ( pMFAccount->getSettlementInstrList( pAcctSettlementInstrList, 
			                                                 idDataGroup, 
																			 true ) <= WARNING &&
			  NULL != pAcctSettlementInstrList )
		{
		   pAcctSettlementInstrList->getAcctSettlementInstr(  dstrSettlInstrCode,																			 
											                           idDataGroup,
												                        pAcctSettlementInstr ) ;
      }
   } 


	return(GETCURRENTHIGHESTSEVERITY());

}

//*****************************************************************************
SEVERITY TransSettlementInstr::setAccountNumbersFromSystemLevel(  const BFDataGroupId& idDataGroup )
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setAccountNumbersFromSystemLevel" ) );
    // get the Settlement Accoutn and iNternal settl account form the system level setup and assign it to tarde
    //these fields update flags should not be set true as they are not send to data base
    SysLvlSettlementInstrList *pSysLvlSettlementInstrList = NULL;
    if ( getWorkSession().getSettlementLocationSysLvlList( pSysLvlSettlementInstrList, idDataGroup, true ) <= WARNING &&
    NULL != pSysLvlSettlementInstrList )
    {
       SysLvlSettlementInstr *pSysLvlSettlementInstr = NULL;
       DString dstrSettleLocCode;
       if(_blFrom)
              _pTrade->getField( ifds::FrSettlLocCode,        dstrSettleLocCode,        idDataGroup );
       else
              _pTrade->getField( ifds::ToSettlLocCode,        dstrSettleLocCode,        idDataGroup );

	   if ( pSysLvlSettlementInstrList->getSysLvlSettlementInstr( dstrSettleLocCode, pSysLvlSettlementInstr, 
																  idDataGroup ) <= WARNING &&	 NULL != pSysLvlSettlementInstr)
       {
            DString dstrSettleAccountNum, dstrIntSettleAccountNum;
            pSysLvlSettlementInstr-> getField( ifds::SettleAccountNum, dstrSettleAccountNum, idDataGroup );
            pSysLvlSettlementInstr-> getField( ifds::InternalSettlementAccount, dstrIntSettleAccountNum, idDataGroup );
            if(_blFrom)
            {
                setFieldNoValidate( ifds::FrSettlementAccount, dstrSettleAccountNum, idDataGroup); 
                setFieldNoValidate( ifds::FrInternalSettlementAccount, dstrIntSettleAccountNum, idDataGroup); 
                setFieldUpdated(ifds::FrSettlementAccount, idDataGroup, false);
                setFieldUpdated(ifds::FrInternalSettlementAccount, idDataGroup, false);
            }
            else
            {
                setFieldNoValidate( ifds::ToSettlementAccount, dstrSettleAccountNum, idDataGroup); 
                setFieldNoValidate( ifds::ToInternalSettlementAccount, dstrIntSettleAccountNum, idDataGroup); 
                setFieldUpdated(ifds::ToSettlementAccount, idDataGroup, false);
                setFieldUpdated(ifds::ToInternalSettlementAccount, idDataGroup, false);
            }
       }
    }
    return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/TransSettlementInstr.cpp-arc  $
// 
//    Rev 1.1   Nov 19 2004 17:33:20   aguilaam
// PET117_FN21: settlement instructions enhancement (temporary check-in for build)
// 
//    Rev 1.0.1.0   Nov 14 2004 14:59:00   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.0   Oct 14 2004 12:23:02   VADEANUM
// Initial revision.
// 
//    Rev 1.7   Oct 13 2004 13:54:16   VADEANUM
// PET 1117 FN21 - Replaced SettleLoc with SettlementInstr.
// 
//    Rev 1.6   Sep 02 2004 15:04:06   WINNIE
// PET 1094 FN08 New transtype 'AF' using isPurchaseLike and isRedemptonLike and code clean up
// 
//    Rev 1.5   Feb 03 2004 09:19:52   VADEANUM
// PTS 10026456 - Limitation to "Realignment" Clearing Method as per Wendy's email - supporting validation.
// 
//    Rev 1.4   Jan 23 2004 16:17:02   VADEANUM
// PTS 10026456 - Limitation to "Realignment" Clearing Method as per Wendy's email - supporting validation.
// 
//    Rev 1.3   Dec 09 2003 10:57:50   VADEANUM
// PET859 FN1 - Settlement Location at Trade Level support.
// 
//    Rev 1.2   Dec 08 2003 12:38:56   VADEANUM
// PET859 FN1 - Settlement Location at Trade Level support - implemented additional requirements.
// 
//    Rev 1.1   Nov 27 2003 13:22:10   VADEANUM
// PET859 FN1 - Settlement Location at Trade Level support.
// 
//    Rev 1.0   Nov 10 2003 16:06:50   VADEANUM
// Initial revision.
//
