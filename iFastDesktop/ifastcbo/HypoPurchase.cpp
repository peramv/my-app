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
// ^FILE   : HypoPurchase.cpp
// ^AUTHOR : Monica Vadeanu
// ^DATE   : April, 2004
//
// ^CLASS    : HypoPurchase
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"

#include "hypopurchase.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "fundmasterlist.hpp"


namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_( "HypoPurchase" );
   const I_CHAR * const NO        = I_( "N" );
   const I_CHAR * const AMOUNT    = I_( "D" );            // amount type
   const I_CHAR * const UNITS     = I_( "U" );            // amount type


}

namespace ifds
{
   //field ids used, not found in the above view   
	extern CLASS_IMPORT const BFNumericFieldId AccountNum;   
	extern CLASS_IMPORT const BFTextFieldId    TradesTransType;   
	extern CLASS_IMPORT const BFDateFieldId    EffectiveDate;   
	extern CLASS_IMPORT const BFTextFieldId    FromFundNumber;   
	extern CLASS_IMPORT const BFTextFieldId    FromFund;   
	extern CLASS_IMPORT const BFTextFieldId    FromClass;   
	//extern CLASS_IMPORT const BFTextFieldId FromFundName;   	
	extern CLASS_IMPORT const BFDecimalFieldId Amount;   
	extern CLASS_IMPORT const BFTextFieldId    AmtType;   	
	extern CLASS_IMPORT const BFDateFieldId    CurrBusDate;
	extern CLASS_IMPORT const BFTextFieldId    ToFundNumber;   

	// Used for EffectiveDate validation
	extern CLASS_IMPORT const BFTextFieldId AcctNumSet;   	
	extern CLASS_IMPORT const BFTextFieldId OrderType; 
	extern CLASS_IMPORT const BFTextFieldId SuppressCode; 	
	extern CLASS_IMPORT const BFTextFieldId FromFundClass; 
	extern CLASS_IMPORT const BFTextFieldId AmtTypeFundTradeType; 
	extern CLASS_IMPORT const BFTextFieldId AmountAmtType; 
	extern CLASS_IMPORT const BFTextFieldId FromFundName; 
	extern CLASS_IMPORT const BFTextFieldId ToFundName; 
	extern CLASS_IMPORT const BFTextFieldId ElongName1; 	
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const PURCHASE;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags 
   { ifds::FromFundName,         BFCBO::NONE,                 0 }, 
   { ifds::ToFundName,           BFCBO::NONE,                 0 }, 
};


static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );


//******************************************************************************
HypoPurchase::HypoPurchase( BFAbstractCBO &parent ) : Purchase (parent), Trade (parent)
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL );
	
}

//******************************************************************************
HypoPurchase::~HypoPurchase()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY HypoPurchase::init( const DString &dstrAccountNum, 
												   const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION,
                          CLASSNAME,
                          I_( "init( const Dstring &, const BFDataGroupId & )" ) );
	
	setObjectNew();
	setFieldNoValidate(ifds::OrderType,NO,idDataGroup,false,true,false,true); // Order type default to direct	
	DString dstrEffective;
    getWorkSession().getMgmtCoOptions()->getField( ifds::CurrBusDate, dstrEffective, BF::HOST,false );
	setFieldNoValidate(ifds::EffectiveDate,dstrEffective,idDataGroup,false,true,false,true);	
   	setFieldNoValidate(ifds::TradesTransType,TRADETYPE::PURCHASE,idDataGroup,false,true,false,true);
	setField(ifds::AccountNum,dstrAccountNum,idDataGroup,false);
	setFieldReadOnly(ifds::TradesTransType,idDataGroup,true);
	setFieldNoValidate(ifds::AmtType,AMOUNT,idDataGroup,false,true,false,true);		
	setFieldNoValidate(ifds::SuppressCode,I_("99"),idDataGroup,false,true,false,true);	
	doInitWithDefaultValues( idDataGroup );
	setFieldRequired( ifds::FromFund, idDataGroup, true );
	setFieldRequired( ifds::FromClass, idDataGroup, true );

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
SEVERITY HypoPurchase::doValidateField( const BFFieldId &idField, 
										 		              const DString& strValue, 
												              const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );
   
	if ( 
		  idField == ifds::EffectiveDate ||
		  idField == ifds::FromFundNumber ||   
		  idField == ifds::FromFund ||  
		  idField == ifds::FromClass ||  
		  idField == ifds::Amount ||
		  idField == ifds::FromFundClass ||
		  idField == ifds::AmtTypeFundTradeType  ||
		  idField == ifds::AmountAmtType ||
		  idField == ifds::AmtType		  	

		  )
	{
		Purchase::doValidateField( idField, strValue, idDataGroup );
	}

	return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************
SEVERITY HypoPurchase::doApplyRelatedChanges( const BFFieldId& idField, 
															const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

	if( idField == ifds::FromFund )
	{

      FundMasterList *pFundMasterList;
      DString fundCode,fundName(NULL_STRING);
      getField (ifds::FromFund, fundCode, idDataGroup, false);
      if (!fundCode.empty() && 
         getMgmtCo().getFundMasterList (pFundMasterList) && 
         pFundMasterList)
      {	
			pFundMasterList->getFundName (fundCode, fundName);
		}
		setFieldNoValidate(ifds::FromFundName,fundName,idDataGroup,false,true,true,true);

	}

	Purchase::doApplyRelatedChanges(idField,idDataGroup);

	if ( idField == ifds::TradesTransType )
	{
		setFieldReadOnly( ifds::ToFundNumber, idDataGroup, true );
		setFieldReadOnly( ifds::ToFund,       idDataGroup, true );
		setFieldReadOnly( ifds::ToClass,      idDataGroup, true );			
	}

	return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/HypoPurchase.cpp-arc  $
// 
//    Rev 1.12   May 03 2005 12:25:22   porteanm
// Incident 298673 - Disable ToFund related controls.
// 
//    Rev 1.11   May 02 2005 16:05:36   porteanm
// Incident 298673 - OrderType initialization.
// 
//    Rev 1.10   Feb 15 2005 16:59:50   porteanm
// Incident 241862 - Removed fields no longer used in Trade.
// 
//    Rev 1.9   Dec 14 2004 15:01:42   popescu
// some of the cross-edits have been renamed
// 
//    Rev 1.8   Nov 17 2004 15:20:50   popescu
// PET 1117/56, removed 'getField' method at the fund master list level, 
// 
//    Rev 1.7   Nov 14 2004 14:44:24   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.6   Nov 06 2004 00:41:08   popescu
// PET 1117/06, synch changes
// 
//    Rev 1.5   May 27 2004 14:33:20   YINGBAOL
// PET 985: FundClass are required fields
// 
//    Rev 1.4   May 26 2004 18:20:20   YINGBAOL
// PET985: validate amount type
// 
//    Rev 1.3   May 26 2004 09:50:34   YINGBAOL
// PET985:promot error when init
// 
//    Rev 1.2   May 25 2004 10:04:56   YINGBAOL
// PET985:implement FundName
// 
//    Rev 1.1   May 19 2004 17:39:08   YINGBAOL
// PET985: make hypo work
// 
//    Rev 1.0   Apr 26 2004 13:44:04   VADEANUM
// Initial revision.
//
