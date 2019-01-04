//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2003 by International Financial, Inc.
//
//*****************************************************************************
//
// ^FILE   : ResetInstrCriteria.cpp
// ^AUTHOR : 
// ^DATE   : Jan 15, 2003
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : ResetInstrCriteria
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************

#include "stdafx.h"
#include "resetinstrcriteria.hpp"
#include "mfaccount.hpp"
#include "mgmtcooptions.hpp"
#include "resetinstrlist.hpp"

namespace
{
   const I_CHAR * const CLASSNAME = I_( "ResetInstrCriteria" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFDateFieldId ResetDate;
   extern CLASS_IMPORT const BFTextFieldId ResetInstrUsing;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
}

namespace CND
{
//Invalid Account Number 
   extern const long ERR_INVALID_ACCOUNT_NUMBER;
//Reset Date cannot be later than current business date.
   extern const long ERR_RESET_DATE_LATER_CUR_DATE;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
//  Field DD Id,					State Flags,	Group Flags 
   { ifds::ResetInstrUsing,	BFCBO::INIT_TO_DEFAULT, 0 },  
   { ifds::AccountNum,			BFCBO::NONE, 0 },  
   { ifds::ResetDate,        BFCBO::NONE, 0 },  
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );
//*****************************************************************************
// Constructor
//*****************************************************************************

ResetInstrCriteria::ResetInstrCriteria( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );   
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//*****************************************************************************
// Destructor
//*****************************************************************************

ResetInstrCriteria::~ResetInstrCriteria()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//*****************************************************************************
// This method will init the field ResetInstrUsing to AccountNum
// @param   const BFDataGroupId& idDataGroup - current data group id.
// @returns SEVERITY. "Invalid Account Number."
//*****************************************************************************
SEVERITY ResetInstrCriteria::init(  DString& dstrAccountNum, const BFDataGroupId& idDataGroup )
{    
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   initWithDefaultValues ( idDataGroup );
   DString dstrCurrBusDate;
   getWorkSession().getMgmtCoOptions()->getField( ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false );
   setFieldNoValidate ( ifds::ResetDate, dstrCurrBusDate, BF::HOST, true, true, true, false );   
   setFieldNoValidate ( ifds::AccountNum, dstrAccountNum, BF::HOST, true, true, true, false );      
   setFieldReadOnly ( ifds::ResetInstrUsing, idDataGroup, true );   
   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
// This method will check to see if the account number passed in is validate 
// or not by issuing a call to WorkSession::getMFAccount.
// @param   const DString& dstrAccountNum - Account Number to validate.
//          const BFDataGroupId& idDataGroup - current data group id.
// @returns SEVERITY. "Invalid Account Number."
//*****************************************************************************
SEVERITY ResetInstrCriteria::validateAccountNum( const DString& dstrAccountNum, const BFDataGroupId& idDataGroup )
{    
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAccountNum" ) );
   MFAccount* pMFAccount;
   SEVERITY sevRtn = getWorkSession().getMFAccount ( idDataGroup, dstrAccountNum, pMFAccount, I_("N"), NULL_STRING, false, true );
   if ( sevRtn > WARNING ) {
      ADDCONDITIONFROMFILE ( CND::ERR_INVALID_ACCOUNT_NUMBER );
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
// Validates the Trade Date passed in is before the current business date.
// @param   const DString& dstrTradeDate - Trade Date to check
//          const BFDataGroupId& idDataGroup - current data group id.
//*****************************************************************************
SEVERITY ResetInstrCriteria::validateTradeDate( const DString& dstrTradeDate, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateTradeDate" ) );

   DString dstrCurrBusDate, dstrResetDate;
   getWorkSession().getMgmtCoOptions()->getField( ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false );
   getField ( ifds::ResetDate, dstrResetDate, idDataGroup );
   if( DSTCommonFunctions::CompareDates( dstrCurrBusDate, dstrResetDate ) == DSTCommonFunctions::FIRST_EARLIER ) {
      ADDCONDITIONFROMFILE ( CND::ERR_RESET_DATE_LATER_CUR_DATE );
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
// doValidateFields will validate the AccountNum and TradeDate.  It will call
// the helper methods validateAccountNum and validateTradeDate to do the
// validation.
// @param   const BFFieldId& idField - current field id validated.
//          const DString& strValue - value associated to field id.
//          const BFDataGroupId& idDataGroup - current group id.
//*****************************************************************************
SEVERITY ResetInstrCriteria::doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateFields" ) );
   if ( idField == ifds::AccountNum ) {
      DString dstrResetInstrUsing;
      getField ( ifds::ResetInstrUsing, dstrResetInstrUsing, idDataGroup );
      const BFFieldId& fieldId = BFFieldId::getId ( dstrResetInstrUsing );
      if ( ifds::AccountNum == idField ) {
         validateAccountNum ( strValue, idDataGroup );
      } else {
         return NO_CONDITION;
      }
   } else if ( idField == ifds::ResetDate ) {
      DString dstrResetInstrUsing;
      getField ( ifds::ResetInstrUsing, dstrResetInstrUsing, idDataGroup );
      const BFFieldId& fieldId = BFFieldId::getId ( dstrResetInstrUsing );
      if ( ifds::ResetDate == idField ) {
         validateTradeDate ( strValue, idDataGroup );
      } else {
         return NO_CONDITION;
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ResetInstrCriteria.cpp-arc  $
// 
//    Rev 1.6   Nov 14 2004 14:52:14   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.5   Mar 21 2003 18:21:50   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.4   Feb 04 2003 11:46:44   HSUCHIN
// added new condition and removed ResetInstrList retrieval methods
// 
//    Rev 1.3   Jan 27 2003 07:42:32   HSUCHIN
// lock criteria to only show ResetDate
// 
//    Rev 1.2   Jan 26 2003 16:04:08   HSUCHIN
// changed the way reset instr list is init
// 
//    Rev 1.1   Jan 25 2003 17:36:30   HSUCHIN
// more enhancements
// 
//    Rev 1.0   Jan 24 2003 10:19:28   HSUCHIN
// Initial Revision
*/
