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
// ^FILE   : TransSettleLoc.cpp
// ^AUTHOR : Monica Vadeanu
// ^DATE   : November 10, 2003
//
// ^CLASS    : TransSettleLoc
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"

#include "ifastcbo\TransSettleLoc.hpp"

#include "ifastcbo\dstcworksession.hpp"
#include "ifastcbo\mfaccount.hpp"
#include "ifastcbo\SettleLocationAcctLvl.hpp"
#include "ifastcbo\SettleLocationAcctLvlList.hpp"
#include "ifastcbo\SettleLocationSysLvl.hpp"
#include "ifastcbo\SettleLocationSysLvlList.hpp"
#include "ifastcbo\trade.hpp"
//#include <dataimpl\dse_dstc_vw.hpp>

#include <dataimpl\dse_dstc0269_vw.hpp>

namespace  
{
   const I_CHAR * const CLASSNAME = I_( "TransSettleLoc" );  
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

	extern CLASS_IMPORT const BFTextFieldId ToSettlLocCode;
	extern CLASS_IMPORT const BFTextFieldId ToDeliveryTo;
	extern CLASS_IMPORT const BFTextFieldId ToSettlLocDescription;
	extern CLASS_IMPORT const BFTextFieldId ToInFavourOf;
	extern CLASS_IMPORT const BFTextFieldId ToForAccount;
   extern CLASS_IMPORT const BFTextFieldId ToClearingMethod;	   
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


const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
   //   Field DD Id,                                       State Flags, Group Flags    
	{ BFCBO::CLASS_FIELD_INFO( ifds::FrSettlLocCode,        BFCBO::NONE,                 0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::FrDeliveryTo,          BFCBO::IMMEDIATE_VALIDATION, 0 )}, 
	{ BFCBO::CLASS_FIELD_INFO( ifds::FrSettlLocDescription, BFCBO::NONE,                 0 )}, 
	{ BFCBO::CLASS_FIELD_INFO( ifds::FrInFavourOf,          BFCBO::NONE,                 0 )}, 
	{ BFCBO::CLASS_FIELD_INFO( ifds::FrForAccount,          BFCBO::NONE,                 0 )}, 
	{ BFCBO::CLASS_FIELD_INFO( ifds::FrClearingMethod,      BFCBO::IMMEDIATE_VALIDATION, 0 )}, 
	{ BFCBO::CLASS_FIELD_INFO( ifds::ToSettlLocCode,        BFCBO::NONE,                 0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::ToDeliveryTo,          BFCBO::IMMEDIATE_VALIDATION, 0 )}, 
	{ BFCBO::CLASS_FIELD_INFO( ifds::ToSettlLocDescription, BFCBO::NONE,                 0 )}, 
	{ BFCBO::CLASS_FIELD_INFO( ifds::ToInFavourOf,          BFCBO::NONE,                 0 )}, 
	{ BFCBO::CLASS_FIELD_INFO( ifds::ToForAccount,          BFCBO::NONE,                 0 )}, 
	{ BFCBO::CLASS_FIELD_INFO( ifds::ToClearingMethod,      BFCBO::IMMEDIATE_VALIDATION, 0 )},    
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );


//****************************************************************************
TransSettleLoc::TransSettleLoc( BFAbstractCBO &parent )
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
TransSettleLoc::~TransSettleLoc()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}   

//****************************************************************************
SEVERITY TransSettleLoc::init( bool blFrom, 					   
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
void TransSettleLoc::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doInitWithDefaultValues" ) );

	if ( NULL != _pTrade )
	{				
		DString dstrSettleLocCode, 
			     dstrDeliveryTo, 
   			  dstrSettleLocDescription, 
			  	  dstrInFavourOf, 
				  dstrForAccount, 
				  dstrClearingMethod;

		if ( _blFrom )
		{									
			setSettlementLocationSubstList( idDataGroup, ifds::FrSettlLocCode );

			_pTrade->getField( ifds::FrSettlLocCode,        dstrSettleLocCode,        idDataGroup );
			_pTrade->getField( ifds::FrDeliveryTo,          dstrDeliveryTo,           idDataGroup );
			_pTrade->getField( ifds::FrSettlLocDescription, dstrSettleLocDescription, idDataGroup );
			_pTrade->getField( ifds::FrInFavourOf,          dstrInFavourOf,           idDataGroup );
			_pTrade->getField( ifds::FrForAccount,          dstrForAccount,           idDataGroup );
			_pTrade->getField( ifds::FrClearingMethod,      dstrClearingMethod,       idDataGroup );

			setFieldNoValidate( ifds::FrSettlLocCode,        dstrSettleLocCode,        idDataGroup, false );			
			setFieldNoValidate( ifds::FrDeliveryTo,          dstrDeliveryTo,           idDataGroup );
			setFieldNoValidate( ifds::FrSettlLocDescription, dstrSettleLocDescription, idDataGroup );
			setFieldNoValidate( ifds::FrInFavourOf,          dstrInFavourOf,           idDataGroup );
			setFieldNoValidate( ifds::FrForAccount,          dstrForAccount,           idDataGroup );
			setFieldNoValidate( ifds::FrClearingMethod,      dstrClearingMethod,       idDataGroup );				
		}
		else
		{			
			setSettlementLocationSubstList( idDataGroup, ifds::ToSettlLocCode );	

			_pTrade->getField( ifds::ToSettlLocCode,        dstrSettleLocCode,        idDataGroup );
			_pTrade->getField( ifds::ToDeliveryTo,          dstrDeliveryTo,           idDataGroup );
			_pTrade->getField( ifds::ToSettlLocDescription, dstrSettleLocDescription, idDataGroup );
			_pTrade->getField( ifds::ToInFavourOf,          dstrInFavourOf,           idDataGroup );
			_pTrade->getField( ifds::ToForAccount,          dstrForAccount,           idDataGroup );
			_pTrade->getField( ifds::ToClearingMethod,      dstrClearingMethod,       idDataGroup );

			setFieldNoValidate( ifds::ToSettlLocCode,        dstrSettleLocCode,        idDataGroup, false );
			setFieldNoValidate( ifds::ToDeliveryTo,          dstrDeliveryTo,           idDataGroup );
			setFieldNoValidate( ifds::ToSettlLocDescription, dstrSettleLocDescription, idDataGroup );
			setFieldNoValidate( ifds::ToInFavourOf,          dstrInFavourOf,           idDataGroup );
			setFieldNoValidate( ifds::ToForAccount,          dstrForAccount,           idDataGroup );
			setFieldNoValidate( ifds::ToClearingMethod,      dstrClearingMethod,       idDataGroup );					
		}
	}

	if ( isNew() )
	{
		if ( true == _blFrom )
		{
			DString dstrFrSettlLocCode;
			getField( ifds::FrSettlLocCode, dstrFrSettlLocCode, idDataGroup );			
			if ( dstrFrSettlLocCode.stripAll().empty() )	
				setDefaultSettlementLocation( ifds::FrSettlLocCode, idDataGroup );

			setFieldReadOnly( ifds::FrSettlLocCode,   idDataGroup, false );
			setFieldReadOnly( ifds::FrDeliveryTo,     idDataGroup, false );			
			setFieldReadOnly( ifds::FrInFavourOf,     idDataGroup, false );
			setFieldReadOnly( ifds::FrForAccount,     idDataGroup, false );
			setFieldReadOnly( ifds::FrClearingMethod, idDataGroup, false );

			setFieldRequired( ifds::FrSettlLocCode,   idDataGroup,true );
			setFieldRequired( ifds::FrClearingMethod, idDataGroup,true );
			setFieldRequired( ifds::FrDeliveryTo,     idDataGroup,true );
			
			setValidFlag ( ifds::FrSettlLocCode,   idDataGroup, false );
			setValidFlag ( ifds::FrClearingMethod, idDataGroup, false );
			setValidFlag ( ifds::FrDeliveryTo,     idDataGroup, false );
			
			setUpdatedFlag( ifds::FrSettlLocCode,   idDataGroup, true );
			setUpdatedFlag( ifds::FrClearingMethod, idDataGroup, true );				
		   setUpdatedFlag( ifds::FrDeliveryTo,     idDataGroup, true );											
		}
		else 
		{
			DString dstrToSettlLocCode;
			getField( ifds::ToSettlLocCode, dstrToSettlLocCode, idDataGroup );			
			if ( dstrToSettlLocCode.stripAll().empty() )	
				setDefaultSettlementLocation( ifds::ToSettlLocCode, idDataGroup );

			setFieldReadOnly( ifds::ToSettlLocCode,   idDataGroup, false );
			setFieldReadOnly( ifds::ToDeliveryTo,     idDataGroup, false );			
			setFieldReadOnly( ifds::ToInFavourOf,     idDataGroup, false );
			setFieldReadOnly( ifds::ToForAccount,     idDataGroup, false );
			setFieldReadOnly( ifds::ToClearingMethod, idDataGroup, false );

			setFieldRequired( ifds::ToSettlLocCode,   idDataGroup, true );
			setFieldRequired( ifds::ToDeliveryTo,     idDataGroup,  true );
			setFieldRequired( ifds::ToClearingMethod, idDataGroup,  true );

			setValidFlag ( ifds::ToSettlLocCode,   idDataGroup, false );
			setValidFlag ( ifds::ToDeliveryTo,     idDataGroup, false );
			setValidFlag ( ifds::ToClearingMethod, idDataGroup, false );
			
			setUpdatedFlag( ifds::ToSettlLocCode,   idDataGroup, true );					
			setUpdatedFlag( ifds::ToDeliveryTo,     idDataGroup, true );						
			setUpdatedFlag( ifds::ToClearingMethod, idDataGroup, true );			
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
		}
		else 
		{
			setFieldReadOnly( ifds::ToSettlLocCode,   idDataGroup, true );
			setFieldReadOnly( ifds::ToDeliveryTo,     idDataGroup, true );			
			setFieldReadOnly( ifds::ToInFavourOf,     idDataGroup, true );
			setFieldReadOnly( ifds::ToForAccount,     idDataGroup, true );
			setFieldReadOnly( ifds::ToClearingMethod, idDataGroup, true );
		}
	}
}

//******************************************************************************
void TransSettleLoc::doReset ( const BFDataGroupId& idDataGroup )
{
	if ( NULL != _pTrade && isNew() )
	{				
		DString dstrSettleLocCode, 
			     dstrDeliveryTo, 
   			  dstrSettleLocDescription, 
			  	  dstrInFavourOf, 
				  dstrForAccount, 
				  dstrClearingMethod;

		if ( _blFrom )
		{						
			_pTrade->getFieldBeforeImage( ifds::FrSettlLocCode,        dstrSettleLocCode );
			_pTrade->getFieldBeforeImage( ifds::FrDeliveryTo,          dstrDeliveryTo  );
			_pTrade->getFieldBeforeImage( ifds::FrSettlLocDescription, dstrSettleLocDescription );
			_pTrade->getFieldBeforeImage( ifds::FrInFavourOf,          dstrInFavourOf  );
			_pTrade->getFieldBeforeImage( ifds::FrForAccount,          dstrForAccount  );
			_pTrade->getFieldBeforeImage( ifds::FrClearingMethod,      dstrClearingMethod );
			
			_pTrade->setField( ifds::FrSettlLocCode,        dstrSettleLocCode,        idDataGroup );
			_pTrade->setField( ifds::FrDeliveryTo,          dstrDeliveryTo,           idDataGroup );
			_pTrade->setField( ifds::FrSettlLocDescription, dstrSettleLocDescription, idDataGroup );
			_pTrade->setField( ifds::FrInFavourOf,          dstrInFavourOf,           idDataGroup );
			_pTrade->setField( ifds::FrForAccount,          dstrForAccount,           idDataGroup );
			_pTrade->setField( ifds::FrClearingMethod,      dstrClearingMethod,       idDataGroup );					
		}
		else
		{	
			_pTrade->getFieldBeforeImage( ifds::ToSettlLocCode,       dstrSettleLocCode );
			_pTrade->getFieldBeforeImage( ifds::ToDeliveryTo,          dstrDeliveryTo  );
			_pTrade->getFieldBeforeImage( ifds::ToSettlLocDescription, dstrSettleLocDescription );
			_pTrade->getFieldBeforeImage( ifds::ToInFavourOf,          dstrInFavourOf  );
			_pTrade->getFieldBeforeImage( ifds::ToForAccount,          dstrForAccount  );
			_pTrade->getFieldBeforeImage( ifds::ToClearingMethod,      dstrClearingMethod );

			_pTrade->setField( ifds::ToSettlLocCode,        dstrSettleLocCode,        idDataGroup );
			_pTrade->setField( ifds::ToDeliveryTo,          dstrDeliveryTo,           idDataGroup );
			_pTrade->setField( ifds::ToSettlLocDescription, dstrSettleLocDescription, idDataGroup );
			_pTrade->setField( ifds::ToInFavourOf,          dstrInFavourOf,           idDataGroup );
			_pTrade->setField( ifds::ToForAccount,          dstrForAccount,           idDataGroup );
			_pTrade->setField( ifds::ToClearingMethod,      dstrClearingMethod,       idDataGroup );				
		}
	}	
}

//******************************************************************************
SEVERITY TransSettleLoc::doApplyRelatedChanges( const BFFieldId &fieldId,
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

	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY TransSettleLoc::doValidateField( const BFFieldId& idField, 
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
SEVERITY TransSettleLoc::validateClearingMethod( const DString &dstrClearingMethod,
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
	}

	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY TransSettleLoc::setSettlementLocationSubstList( const BFDataGroupId& idDataGroup,
																		   const BFFieldId& idFieldCode )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setSettlementLocationSubstList" ) );
	
	bool blSuccess = true;
	DString dstrSettlementLocations;

	MFAccount *pMFAccount = NULL;
   if (  getWorkSession().getMFAccount ( idDataGroup, _dstrAccountNum, pMFAccount ) <= WARNING &&
		  NULL != pMFAccount )
	{
		SettleLocationAcctLvlList *pSettlementLocationAcctList = NULL;
		if ( pMFAccount->getSettlementLocationAcctLvlList( pSettlementLocationAcctList, 
			                                                idDataGroup, 
																			true ) <= WARNING &&
			  NULL != pSettlementLocationAcctList )
		{
			BFObjIter settlementLocationAcctListIter( *pSettlementLocationAcctList, 
				                                       idDataGroup, 
																	true, 
																	BFObjIter::ITERTYPE::NON_DELETED );
         
         settlementLocationAcctListIter.begin();  
			
			SettleLocationSysLvlList *pSettleLocationSysLvlList = NULL;
			if ( getWorkSession().getSettlementLocationSysLvlList( pSettleLocationSysLvlList, 
					                                                 idDataGroup, 
																					 true ) <= WARNING &&
				  NULL != pSettleLocationSysLvlList )
			{				
				while( !settlementLocationAcctListIter.end() )
				{
					SettleLocationAcctLvl *pSettleLocationAcctLvl = dynamic_cast<SettleLocationAcctLvl*>( settlementLocationAcctListIter.getObject() );
					DString dstrSettleLocationCode;
					pSettleLocationAcctLvl->getField( ifds::SettleLocationCode, dstrSettleLocationCode, idDataGroup );

					SettleLocationSysLvl *pSettleLocationSysLvl = NULL;
					if ( pSettleLocationSysLvlList->getSettleLocationSysLvl( dstrSettleLocationCode, 
	  				 			  										                  pSettleLocationSysLvl, 
																		                  idDataGroup ) <= WARNING &&
						  NULL != pSettleLocationSysLvl )
					{
						DString dstrSettleLocationDesc;
						pSettleLocationSysLvl->getField( ifds::SettleLocationDesc, dstrSettleLocationDesc, idDataGroup );
									
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
SEVERITY TransSettleLoc::setSettleLocationDescription( const BFFieldId& idFieldCode, 
																		 const BFDataGroupId& idDataGroup,
																		 const BFFieldId& idFieldDescription )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setSettleLocationDescription" ) );

	bool blSettleLocDescExists = false;

	DString dstrSettleLocCode;
	getField( idFieldCode, dstrSettleLocCode, idDataGroup );
	SettleLocationSysLvlList *pSettleLocationSysLvlList = NULL;
	if ( getWorkSession().getSettlementLocationSysLvlList( pSettleLocationSysLvlList, 
		                                                    idDataGroup, 
																			 true ) <= WARNING &&
        NULL != pSettleLocationSysLvlList )
	{
		SettleLocationSysLvl *pSettleLocationSysLvl = NULL;
		if ( pSettleLocationSysLvlList->getSettleLocationSysLvl( dstrSettleLocCode, 
	  				 			  										         pSettleLocationSysLvl, 
																		         idDataGroup ) <= WARNING &&
			  NULL != pSettleLocationSysLvl )
		{
			DString dstrSettleLocDescription;
			pSettleLocationSysLvl->getField( ifds::SettleLocationDesc, dstrSettleLocDescription, idDataGroup );

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
SEVERITY TransSettleLoc::setDefaultSettlementLocation( const BFFieldId& idFieldCode, 
								             						 const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setDefaultSettlementLocation" ) );

	bool blHasDefault = false;

	MFAccount *pMFAccount = NULL;
   if (  getWorkSession().getMFAccount ( idDataGroup, _dstrAccountNum, pMFAccount ) <= WARNING &&
		  NULL != pMFAccount )
	{
		SettleLocationAcctLvlList *pSettlementLocationAcctList = NULL;
		if ( pMFAccount->getSettlementLocationAcctLvlList( pSettlementLocationAcctList, 
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
				SettleLocationAcctLvl *pSettleLocationAcctLvl = dynamic_cast<SettleLocationAcctLvl*>( settlementLocationAcctListIter.getObject() );
				if ( NULL != pSettleLocationAcctLvl )
				{
					DString dstrDefault;
					pSettleLocationAcctLvl->getField( ifds::Default, dstrDefault, idDataGroup ) ;
					if ( I_( "Y" ) == dstrDefault )
					{
						DString dstrSettleLocationCode;
						pSettleLocationAcctLvl->getField( ifds::SettleLocationCode, dstrSettleLocationCode, idDataGroup );
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

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/TransSettleLoc.cpp-arc  $
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
