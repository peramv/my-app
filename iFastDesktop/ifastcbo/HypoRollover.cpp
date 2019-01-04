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
// ^FILE   : HypoRollover.cpp
// ^AUTHOR : Yingbao  Li
// ^DATE   : May, 2004
//
// ^CLASS    : HypoRollover
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"

#include "HypoRollover.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "fundmasterlist.hpp"

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_( "HypoRollover" );
   const I_CHAR * const NO = I_( "N" );
   const I_CHAR * const AMOUNT                     = I_( "D" );            // amount type
   const I_CHAR * const SUPPRESS = I_( "X" );
   const I_CHAR * const SUPPRESS_CHEQUE = I_( "99" );

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
	extern CLASS_IMPORT const BFTextFieldId    ToFund;   
	extern CLASS_IMPORT const BFTextFieldId    ToClass;   
	extern CLASS_IMPORT const BFTextFieldId    ToFundNumber;   
	
	//extern CLASS_IMPORT const BFTextFieldId FromFundName;   	
	extern CLASS_IMPORT const BFDecimalFieldId Amount;   
	extern CLASS_IMPORT const BFTextFieldId    AmtType;   
	//extern CLASS_IMPORT const BFTextFieldId ???;   
   	extern CLASS_IMPORT const BFDateFieldId    CurrBusDate;


	// Used for EffectiveDate validation
	extern CLASS_IMPORT const BFTextFieldId AcctNumSet;   	
	extern CLASS_IMPORT const BFTextFieldId OrderType;  
	extern CLASS_IMPORT const BFTextFieldId SuppressCode; //	
	extern CLASS_IMPORT const BFTextFieldId FromFundClass;// 
	extern CLASS_IMPORT const BFTextFieldId AmtTypeFundTradeType;// 
	extern CLASS_IMPORT const BFTextFieldId AmountAmtType; //
	extern CLASS_IMPORT const BFTextFieldId PayType; //
	extern CLASS_IMPORT const BFTextFieldId FromToFundClass; //
	extern CLASS_IMPORT const BFTextFieldId FundClass; //
	extern CLASS_IMPORT const BFTextFieldId FromFundName; 
	extern CLASS_IMPORT const BFTextFieldId ToFundName; 
	extern CLASS_IMPORT const BFTextFieldId ElongName1; 

   extern CLASS_IMPORT const BFTextFieldId SettleLocRealignFromToClassXEdit;
	extern CLASS_IMPORT const BFTextFieldId FundCodeRedCodeAmount;
}
namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const ROLLOVER;
}
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags 
   { ifds::FromFundName,         BFCBO::NONE,                 0 }, 
   { ifds::ToFundName,           BFCBO::NONE,                 0 }, 
   { ifds::PayType,              BFCBO::NONE,                 0 },    
};


static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );


//******************************************************************************
HypoRollover::HypoRollover( BFAbstractCBO &parent ) : Rollover (parent), Trade (parent)
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );

   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL );
}

//******************************************************************************
HypoRollover::~HypoRollover()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY HypoRollover::init( const DString &dstrAccountNum, 
												   const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION,
                          CLASSNAME,
                          I_( "init( const Dstring &, const BFDataGroupId & )" ) );
	
	setObjectNew();
   	setFieldNoValidate(ifds::TradesTransType,TRADETYPE::ROLLOVER,idDataGroup,false,true,false,true);
	setFieldReadOnly(ifds::TradesTransType,idDataGroup,true);
	setField(ifds::AccountNum,dstrAccountNum,idDataGroup,false);
	
	setFieldNoValidate(ifds::OrderType,NO,idDataGroup,false,true,false,true); // Order type default to direct	
	DString dstrEffective;
   getWorkSession().getMgmtCoOptions()->getField( ifds::CurrBusDate, dstrEffective, BF::HOST,false );
	setFieldNoValidate(ifds::EffectiveDate,dstrEffective,idDataGroup,false,true,false,true);
	doInitWithDefaultValues( idDataGroup );
	setFieldReadOnly( ifds::ToFund, idDataGroup, false );
	setFieldReadOnly( ifds::ToClass, idDataGroup, false );
	setFieldReadOnly( ifds::ToFundNumber, idDataGroup, false );
	setFieldReadOnly( ifds::AmtType, idDataGroup, false ); 
	setFieldRequired( ifds::ToFund, idDataGroup, true );
	setFieldRequired( ifds::ToClass, idDataGroup, true );
	setFieldRequired( ifds::FromFund, idDataGroup, true );
	setFieldRequired( ifds::FromClass, idDataGroup, true );
	setFieldNoValidate(ifds::AmtType,AMOUNT,idDataGroup,false,true,false,true); // dollar for amtType		
	setFieldNoValidate(ifds::PayType,SUPPRESS,idDataGroup,false,true,false,true); // Pay type default to direct	
	setFieldNoValidate(ifds::SuppressCode,SUPPRESS_CHEQUE,idDataGroup,false,true,false,true);	
   setFieldSubstituteValues (ifds::AmtType, idDataGroup, ifds::AmtType);


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
SEVERITY HypoRollover::doValidateField( const BFFieldId &idField, 
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
         idField == ifds::Amount ||
         idField == ifds::FromFundClass ||
         idField == ifds::AmtTypeFundTradeType ||
         idField == ifds::AmountAmtType ||
         idField == ifds::FromToFundClass ||
         idField == ifds::FundClass ||
			idField == ifds::FundCodeRedCodeAmount
		  )
	{
		Rollover::doValidateField( idField, strValue, idDataGroup );
	}

	return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************
SEVERITY HypoRollover::doApplyRelatedChanges( const BFFieldId& idField, 
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

	Rollover::doApplyRelatedChanges(idField,idDataGroup);

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
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/HypoRollover.cpp-arc  $
// 
//    Rev 1.17   May 03 2005 12:26:58   porteanm
// Incident 298673 - Enable ToFund related controls.
// 
//    Rev 1.16   May 02 2005 16:09:04   porteanm
// Incident 298673 - OrderType initialization.
// 
//    Rev 1.15   Feb 15 2005 16:52:12   porteanm
// Incident 241862 - Removed fields no longer used in Trade.
// 
//    Rev 1.14   Dec 14 2004 15:01:46   popescu
// some of the cross-edits have been renamed
// 
//    Rev 1.13   Nov 30 2004 16:51:36   popescu
// PET 1117/56, removed one cross-edit, it's being renamed
// 
//    Rev 1.12   Nov 17 2004 15:20:54   popescu
// PET 1117/56, removed 'getField' method at the fund master list level, 
// 
//    Rev 1.11   Nov 14 2004 14:44:52   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.10   Nov 07 2004 16:10:40   popescu
// PET 1117/56, minor compilation/link errors
// 
//    Rev 1.9   Nov 07 2004 09:57:04   YINGBAOL
// Add version control
 * 
 *    Rev 1.8   Nov 6 2004 12:41:12   popsecu
 *    PET 1117/06, synch changes
 *
 *    Rev 1.7   Nov 2 2004 12:26:30   VEDEANUM
 *    PTS 10035000 - Added validation for FundCodeRedCodeAmount.
 *
 *    Rev 1.6   Nov 2 2004 12:26:30   HERNANDO
 *     PTS10035002 - Added ifds::SettleLocRealignFromToClassXEdit to doValidateField.
 *
 *    Rev 1.5   Jun 2 2004 12:26:30   YINGBAOL
 *     PTS10030671:change Amount type
 *
 *    Rev 1.4   May 27 2004 12:26:30   YINGBAOL
 *     PTS10030671:change Amount type
 *
 *    Rev 1.3   May 26 22004 12:26:30   YINGBAOL
 *     PET 985: FundClass are required fields
 *
 *    Rev 1.2   May 25 22004 12:26:30   YINGBAOL
 *     PET985:implement FundName
 *
 *    Rev 1.1   May 19 22004 12:26:30   YINGBAOL
 *     PET985: make hypo work

 *
 *    Rev 1.0   May 19 22004 12:26:30   YINGBAOL
 *     PET985: Initial revision.

  */