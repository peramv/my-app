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
//    Copyright 2004 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : HypoExchange.cpp
// ^AUTHOR : Monica Vadeanu
// ^DATE   : April, 2004
//
// ^CLASS    : HypoExchange
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"

#include "hypoexchange.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "fundmasterlist.hpp"

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_( "HypoExchange" );
   const I_CHAR * const NO = I_( "N" );
   const I_CHAR * const AMOUNT                     = I_( "D" );            // amount type
   const I_CHAR * const UNITS                      = I_( "U" );            // amount type

   const I_CHAR * const SUPPRESS = I_( "X" );  
   const I_CHAR * const SUPPRESS_CHEQUE = I_( "99" );




}

namespace ifds
{
   //field ids used, not found in the above view   
	extern CLASS_IMPORT const BFNumericFieldId AccountNum;   
	extern CLASS_IMPORT const BFTextFieldId    TradesTransType;   
	extern CLASS_IMPORT const BFDateFieldId    EffectiveDate;
	extern CLASS_IMPORT const BFDateFieldId    CurrBusDate;
   


	extern CLASS_IMPORT const BFTextFieldId    FromFundNumber;   
	extern CLASS_IMPORT const BFTextFieldId    FromFund;   
	extern CLASS_IMPORT const BFTextFieldId    FromClass;   

	extern CLASS_IMPORT const BFTextFieldId    ToFund;   
	extern CLASS_IMPORT const BFTextFieldId    ToClass;   
	extern CLASS_IMPORT const BFTextFieldId    ToFundNumber;   
	
	
	//extern CLASS_IMPORT const BFTextFieldId FromFundName;   	
	extern CLASS_IMPORT const BFDecimalFieldId Amount;   
	extern CLASS_IMPORT const BFTextFieldId    AmtType;   
	//extern CLASS_IMPORT const BFTextFieldId ???;   

	// Used for EffectiveDate validation
	extern CLASS_IMPORT const BFTextFieldId AcctNumSet;   	
	extern CLASS_IMPORT const BFTextFieldId OrderType;  
	extern CLASS_IMPORT const BFTextFieldId SuppressCode; 	
	extern CLASS_IMPORT const BFTextFieldId FromFundClass; 
	extern CLASS_IMPORT const BFTextFieldId AmtTypeFundTradeType; 
	extern CLASS_IMPORT const BFTextFieldId AmountAmtType; 
	extern CLASS_IMPORT const BFTextFieldId PayType; 

	extern CLASS_IMPORT const BFTextFieldId TradesPayType; 

	extern CLASS_IMPORT const BFTextFieldId ToFundTradeType; 
	extern CLASS_IMPORT const BFTextFieldId ToFundClassAllowed; 
	extern CLASS_IMPORT const BFTextFieldId ToFundAmtType; 
	extern CLASS_IMPORT const BFTextFieldId FromFundClassAcctTo; 
	extern CLASS_IMPORT const BFTextFieldId FromToFundClass; 
	extern CLASS_IMPORT const BFTextFieldId ToFundClass; 

	extern CLASS_IMPORT const BFTextFieldId FromFundName; 
	extern CLASS_IMPORT const BFTextFieldId ToFundName; 
	extern CLASS_IMPORT const BFTextFieldId ElongName1; 


}



namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const EXCHANGE;
}


const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags 
   { ifds::FromFundName,         BFCBO::NONE,                 0 }, 
   { ifds::ToFundName,           BFCBO::NONE,                 0 }, 

   { ifds::TradesTransType,      BFCBO::NONE,                 0 }, 
   { ifds::PayType,              BFCBO::NONE,                 0 }, 
   { ifds::TradesPayType,         BFCBO::NONE,                 0 }, 
};


static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );


//******************************************************************************
HypoExchange::HypoExchange( BFAbstractCBO &parent ) 
: Exchange( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );

   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL );


}

//******************************************************************************
HypoExchange::~HypoExchange()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY HypoExchange::init( const DString &dstrAccountNum, 
												   const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION,
                          CLASSNAME,
                          I_( "init( const Dstring &, const BFDataGroupId & )" ) );

	setFieldNoValidate(ifds::TradesTransType,TRADETYPE::EXCHANGE,idDataGroup,false,true,false,true);
	setField(ifds::AccountNum,dstrAccountNum,idDataGroup,false);
	
	setFieldNoValidate(ifds::OrderType,NO,idDataGroup,false,true,false,true); // Order type default to direct	
	DString dstrEffective;
   getWorkSession().getMgmtCoOptions()->getField( ifds::CurrBusDate, dstrEffective, BF::HOST,false );
	setFieldNoValidate(ifds::EffectiveDate,dstrEffective,idDataGroup,false,true,false,true);
	doInitWithDefaultValues( idDataGroup );
	setFieldReadOnly( ifds::ToFund, idDataGroup, false );
	setFieldReadOnly( ifds::ToClass, idDataGroup, false );
	setFieldReadOnly( ifds::ToFundNumber, idDataGroup, false );
	setFieldReadOnly( ifds::TradesTransType,idDataGroup,true);

	setFieldRequired( ifds::ToFund, idDataGroup, true );
	setFieldRequired( ifds::ToClass, idDataGroup, true );

	setFieldRequired( ifds::FromFund, idDataGroup, true );
	setFieldRequired( ifds::FromClass, idDataGroup, true );
		
	setFieldNoValidate(ifds::AmtType,AMOUNT,idDataGroup,false,true,false,true); // dollar for amtType		
	setFieldNoValidate(ifds::PayType,SUPPRESS,idDataGroup,false,true,false,true); // Pay type default to direct	
	setFieldNoValidate(ifds::TradesPayType,SUPPRESS,idDataGroup,false,true,false,true); // Pay type default to direct	
	setFieldNoValidate(ifds::SuppressCode,SUPPRESS_CHEQUE,idDataGroup,false,true,false,true);	
	setObjectNew();
	
	SEVERITY sev = GETCURRENTHIGHESTSEVERITY();
	if( sev>= WARNING )
	{
	   CONDITIONVECTOR* _pCond;

      getFieldConditionVector(ifds::TradesTransType,idDataGroup,_pCond );
      if( _pCond == NULL )
		{
         _pCond = new CONDITIONVECTOR;
		}
      int count = CURRENTCONDITIONCOUNT( );
      Condition   *c = NULL;
      for( int i = 0; i < count; i++ )
      {
         c = new Condition( *GETCURRENTCONDITION( i ));
         _pCond->push_back( c );
      };
      setFieldConditionVector(ifds::TradesTransType, idDataGroup,_pCond );	
	}
   return sev;

}

//******************************************************************************
SEVERITY HypoExchange::doValidateField( const BFFieldId &idField, 
										 		              const DString& strValue, 
												              const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );
   
	if ( 
		  idField == ifds::EffectiveDate ||
		  idField == ifds::FromFundNumber ||   
		  idField == ifds::FromFund ||  
		  idField == ifds::FromClass || 
		  
		  idField == ifds::ToFundNumber ||   
		  idField == ifds::ToFund ||  
		  idField == ifds::ToClass || 

		  idField == ifds::Amount  ||
		  idField == ifds::FromFundClass ||
		  idField == ifds::AmtTypeFundTradeType ||
		  idField == ifds::AmountAmtType ||
		  idField == ifds::ToFundClass ||
		  idField == ifds::ToFundClassAllowed ||
		  idField == ifds::ToFundAmtType ||
		  idField == ifds::FromToFundClass	||
        idField == ifds::FromFundClassAcctTo ||
		  idField == ifds::AmtType		  

		  )
	{
		Exchange::doValidateField( idField, strValue, idDataGroup );
	}

	return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************
SEVERITY HypoExchange::doApplyRelatedChanges( const BFFieldId& idField, 
															const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

	if( idField == ifds::FromFund || idField == ifds::ToFund  )
	{
		BFFieldId fundCode,fundName;
		if( idField == ifds::FromFund )
		{
			fundCode = ifds::FromFund;
			fundName = ifds::FromFundName;
		}
		else if (idField == ifds::ToFund )
		{
			fundCode = ifds::ToFund;
			fundName = ifds::ToFundName;
		}

      FundMasterList *pFundMasterList;
      DString strFundCode,strFundName(NULL_STRING);
      getField (fundCode, strFundCode, idDataGroup, false);
      if (!strFundCode.empty() && 
         getMgmtCo().getFundMasterList (pFundMasterList) && 
         pFundMasterList)
      {
		   pFundMasterList->getFundName (strFundCode, strFundName);
		}
		setFieldNoValidate(fundName,strFundName,idDataGroup,false,true,true,true);
	}

	Exchange::doApplyRelatedChanges(idField,idDataGroup);

	if ( idField == ifds::TradesTransType )
	{
		setFieldReadOnly( ifds::ToFundNumber, idDataGroup, false );
		setFieldReadOnly( ifds::ToFund,       idDataGroup, false );
		setFieldReadOnly( ifds::ToClass,      idDataGroup, false );			
	}

	return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/HypoExchange.cpp-arc  $
// 
//    Rev 1.13   May 03 2005 12:24:16   porteanm
// Incident 298673 - Enable ToFund related controls.
// 
//    Rev 1.12   May 02 2005 16:03:26   porteanm
// Incident 298673 - OrderType initialization.
// 
//    Rev 1.11   Feb 15 2005 17:00:58   porteanm
// Incident 241862 - Removed fields no longer used in Trade and set TradesPayType with same value as PayType.
// 
//    Rev 1.10   Dec 14 2004 18:37:50   popescu
// Restored a cross-edit
// 
//    Rev 1.9   Dec 14 2004 15:01:40   popescu
// some of the cross-edits have been renamed
// 
//    Rev 1.8   Nov 17 2004 15:20:46   popescu
// PET 1117/56, removed 'getField' method at the fund master list level, 
// 
//    Rev 1.7   Nov 14 2004 14:44:22   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.6   May 27 2004 14:33:32   YINGBAOL
// PET 985: FundClass are required fields
// 
//    Rev 1.5   May 26 2004 18:20:10   YINGBAOL
// PET985: validate amount type
// 
//    Rev 1.4   May 26 2004 09:50:22   YINGBAOL
// PET985:promot error when init
// 
//    Rev 1.3   May 25 2004 10:03:26   YINGBAOL
// implement Fund name
// 
//    Rev 1.2   May 19 2004 17:38:52   YINGBAOL
// PET985: make hypo work
// 
//    Rev 1.1   May 10 2004 20:27:52   popescu
// PET 985, FN 01, LSIF Trade Entry
// 
//    Rev 1.0   Apr 26 2004 13:52:18   VADEANUM
// Initial revision.
//
