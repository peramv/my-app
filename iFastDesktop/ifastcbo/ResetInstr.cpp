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
// ^FILE   : ResetInstr.cpp
// ^AUTHOR : 
// ^DATE   : Jan 15, 2003
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : ResetInstr
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************

#include "stdafx.h"
#include "mfaccount.hpp"
#include "mgmtcooptions.hpp"
#include "resetinstr.hpp"
#include "resetinstrlist.hpp"
#include "fundclassrules.hpp"
#include "protectedfundlist.hpp"
#include <ifastcbo\mfaccountholdinglist.hpp>
#include <ifastdataimpl\dse_dstc0124_req.hpp>
#include <ifastdataimpl\dse_dstc0124_vw.hpp>
#include <ifastdataimpl\dse_dstc0243_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0243_req.hpp>
#include <ifastdataimpl\dse_dstc0243_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME = I_( "ResetInstr" );
   const I_CHAR * const CLIENT_REQ_RESET = I_("01");
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FundClass;
   extern CLASS_IMPORT const BFTextFieldId FundNumber;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFTextFieldId rxFundCode;
   extern CLASS_IMPORT const BFTextFieldId rxClassCode;
   extern CLASS_IMPORT const BFTextFieldId ResetGroup;
   extern CLASS_IMPORT const BFNumericFieldId ResetsAllowed;
}

namespace CND
{
   extern const long ERR_ACCRUALS_FUND_NOT_IN_HOLDINGS;
   extern const long ERR_INVALID_ACCOUNT_NUMBER;
   extern const long ERR_RESET_DATE_LATER_CUR_DATE;
   extern const long ERR_FUND_CLASS_NOT_PROTECTED;   
   extern const long ERR_ACCOUNT_EMPTY;
   extern const long ERR_RESET_EXCEED_MAX;
   extern const long ERR_DUP_RESET_INSTR;
   extern const long ERR_RESET_ENTITY_EXCEED_AGE_LIMIT;
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ACTIVE_BATCH;
   extern CLASS_IMPORT const DSTCRequest RESET_INSTR_LIST;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
//  Field DD Id,					State Flags,	Group Flags 
   { ifds::AccountNum,          BFCBO::NONE, 0 },  
   { ifds::FundCode,            BFCBO::NONE, 0 },  
   { ifds::ClassCode,           BFCBO::NONE, 0 },  
   { ifds::ResetType,           BFCBO::NONE, 0 },  
   { ifds::ResetDate,           BFCBO::NONE, 0 },  
   { ifds::BatchName,           BFCBO::NONE, 0 },
   { ifds::BatchEffective,      BFCBO::NONE, 0 },
   { ifds::Trace,               BFCBO::NONE, 0 },  
   { ifds::CanResetId,          BFCBO::NONE, 0 },  
   { ifds::FundClass,           BFCBO::IMMEDIATE_VALIDATION, 0 },  
   { ifds::ResetGroup,          BFCBO::NONE, 0 },  
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//*****************************************************************************
// Constructor.  The Fund/Class code cross edits are d4efined here.
//*****************************************************************************

ResetInstr::ResetInstr( BFAbstractCBO &parent )
:  _pFundClassRules( NULL ),
	_pProtectedFundList ( NULL ),
   MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );   
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
   //addCrossEdit ( ifds::AccountNum, ifds::FundClass ); 
   addCrossEdit(ifds::FundClass, ifds::FundCode);
   addCrossEdit(ifds::FundClass, ifds::ClassCode);

   addCrossEdit ( ifds::ResetGroup, ifds::AccountNum ); 
   addCrossEdit ( ifds::ResetGroup, ifds::FundCode );
   addCrossEdit ( ifds::ResetGroup, ifds::ClassCode );
   addCrossEdit ( ifds::ResetGroup, ifds::ResetType );
   addCrossEdit ( ifds::ResetGroup, ifds::ResetDate );

   _pFundClassRules = new FundClassRules ( *this );
   _pFundClassRules->init ( );
}

//*****************************************************************************
// Destructor
//*****************************************************************************

ResetInstr::~ResetInstr()
{
   TRACE_DESTRUCTOR( CLASSNAME );   
   if ( _pFundClassRules  ) {
      delete _pFundClassRules;
      _pFundClassRules = NULL;
   }
}

//*****************************************************************************
// This method will attach the BFData object passed in to to BFCBO data map.
// It will also set all the fields to readonly when the Complete Date in data
// is set, otherwise only the account number will be set to readonly.
// @param   const BFData& data - reference to data to insert into BFCBO data map.
//          bool bBaseDelete - boolean to indicate who cleans up the data.
// @returns SEVERITY - SEVERITY from BFCBO::attachDataObject.
//*****************************************************************************
SEVERITY ResetInstr::init( const BFData& data, bool bBaseDelete )
{  
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   attachDataObject( const_cast<BFData&>(data), bBaseDelete, true );
   DString dstrCompleteDate;
   dstrCompleteDate = data.getElementValue( ifds::CompleteDate );
   if ( !dstrCompleteDate.empty() )
      setAllFieldsReadOnly ( BF::HOST );
   else
      setFieldReadOnly ( ifds::AccountNum, BF::HOST, true );
   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
SEVERITY ResetInstr::init( const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
	getBatchInfo( idDataGroup );
	return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
// This method will check to see if the account number passed in is validate 
// or not by issuing a call to WorkSession::getMFAccount.
// @param   const DString& dstrAccountNum - Account Number to validate.
//          const BFDataGroupId& idDataGroup - current data group id.
// @returns SEVERITY. "Invalid Account Number."
//*****************************************************************************
SEVERITY ResetInstr::validateAccountNum( const DString& dstrAccountNum, const BFDataGroupId& idDataGroup )
{    
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAccountNum" ) );
   MFAccount* pMFAccount;
   SEVERITY sevRtn = getWorkSession().getMFAccount ( idDataGroup, dstrAccountNum, pMFAccount, I_("N"), NULL_STRING, true, true );
   if ( sevRtn > WARNING ) {
      ADDCONDITIONFROMFILE ( CND::ERR_INVALID_ACCOUNT_NUMBER );
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
// Validates the Effective Date passed in is before the current business date.  If 
// the instruction code is not 02 (Death Reset), the Effective Date cannot not be 
// changed.
// @param   const DString& dstrEffectiveDate - Effective Date to check
//          const BFDataGroupId& idDataGroup - current data group id.
//*****************************************************************************
SEVERITY ResetInstr::validateEffectiveDate( const DString& dstrEffectiveDate, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateTradeDate" ) );

   DString dstrCurrBusDate, dstrResetDate;
   getWorkSession().getMgmtCoOptions()->getField( ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false );
   getField ( ifds::ResetDate, dstrResetDate, idDataGroup );
   if( DSTCommonFunctions::CompareDates( dstrCurrBusDate, dstrResetDate ) == DSTCommonFunctions::FIRST_EARLIER ) {
      //Reset Date cannot be later than current business date.
      ADDCONDITIONFROMFILE ( CND::ERR_RESET_DATE_LATER_CUR_DATE );
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
// @param   const BFFieldId& idField - current field id validated.
//          const DString& strValue - value associated to field id.
//          const BFDataGroupId& idDataGroup - current group id.
//*****************************************************************************
SEVERITY ResetInstr::doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateFields" ) );
   if ( idField == ifds::AccountNum ) 
   {
      validateAccountNum ( strValue, idDataGroup );
      setValidFlag ( ifds::FundCode, idDataGroup, false );
      setValidFlag ( ifds::ClassCode, idDataGroup, false );
   } 
   else if ( idField == ifds::ResetDate ) 
   {
      validateEffectiveDate ( strValue, idDataGroup );
   } else if ( idField == ifds::FundCode ) 
   {     
      _pFundClassRules->validateFundCode ( idDataGroup );
     // validateFundClass ( idDataGroup );
   } 
   else if ( idField == ifds::ClassCode ) 
   {
      _pFundClassRules->validateClassCode ( idDataGroup );      
     // validateFundClass ( idDataGroup );
   } else if ( idField == ifds::FundClass )
   {
      validateFundClass ( idDataGroup );
   } else if ( idField == ifds::ResetGroup ) 
   {
      isResetAllowed ( idDataGroup );
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
// Makes a view call to get the Batch information.
// @param   const BFDataGroupId& idDataGroup - current group id.

SEVERITY ResetInstr::getBatchInfo( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getBatchInfo" ) );
   DString mgmtCoIdOut;
   BFData request(ifds::DSTC0124_REQ);
   BFData *response = new BFData(ifds::DSTC0124_VW);
   const DSTCSecurity* pSecurity =  dynamic_cast<const DSTCSecurity *>(getSecurity());
   request.setElementValue( ifds::Track, I_("N") );
   request.setElementValue( ifds::Activity, NULL_STRING );   
   request.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );  
   if( BFDataBroker::getInstance()->receive( DSTC_REQUEST::ACTIVE_BATCH, request, *response, DSTCRequestor(getSecurity()) ) <= WARNING )
   {
      DString dstr;
      response->getElementValue( ifds::rxBatchName, dstr );
      setField( ifds::BatchName, dstr.strip(), idDataGroup, false, true );      
      response->getElementValue( ifds::EffectiveDate, dstr );
      setField( ifds::BatchEffective, dstr.strip(), idDataGroup, false, true );      
      response->getElementValue( ifds::BatchTrace, dstr );
      setField( ifds::Trace, dstr.strip(), idDataGroup, false, true );      
      delete response;
   }
   else
      setField(ifds::BatchName, NULL_STRING, idDataGroup, false, true );

   return(GETCURRENTHIGHESTSEVERITY());  

}

//*****************************************************************************
//*****************************************************************************
void ResetInstr::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
//   getBatchInfo( idDataGroup );
   DString dstrCurrBusDate;
   getWorkSession().getMgmtCoOptions()->getField( ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false );
   setFieldNoValidate ( ifds::ResetDate, dstrCurrBusDate, idDataGroup, false );
   DString dstrAccountNum;
   ResetInstrList* pResetInstrList = dynamic_cast <ResetInstrList*> (getParent());
   dstrAccountNum = pResetInstrList->getAccountNum ();
   if ( dstrAccountNum != I_("0") ) {
      setFieldNoValidate ( ifds::AccountNum, dstrAccountNum, idDataGroup );
      setFieldReadOnly ( ifds::AccountNum, idDataGroup, true );
   }     
}

//*****************************************************************************
//*****************************************************************************
SEVERITY ResetInstr::validateFundClass( const BFDataGroupId& idDataGroup )
{

   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundClass" ) );

   DString dstrFundCode, dstrClassCode;
   getField ( ifds::FundCode, dstrFundCode, idDataGroup );
   getField ( ifds::ClassCode, dstrClassCode, idDataGroup );
   if ( ( dstrFundCode == NULL_STRING ) || ( dstrClassCode == NULL_STRING ) ) {
      return NO_CONDITION;
   }
   isFundClassInProtectedList ( idDataGroup );
   isFundClassInHoldings ( idDataGroup );
   return(GETCURRENTHIGHESTSEVERITY());
}
//*****************************************************************************
//*****************************************************************************
SEVERITY ResetInstr::isFundClassInProtectedList( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isFundClassInProtectedList" ) );
      
   getWorkSession().getProtectedFundList( _pProtectedFundList );
   DString dstrFundCode,dstrClassCode;
   getField ( ifds::FundCode, dstrFundCode, idDataGroup );
   getField ( ifds::ClassCode, dstrClassCode, idDataGroup );
   dstrFundCode.strip().upperCase();
   dstrClassCode.strip().upperCase();
/*
   if ( _pProtectedFundList ) {
      BFObjIter iter( *_pProtectedFundList, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );      
      while (!iter.end() ) {
         iter.getObject()->getField( ifds::FundCode, dstrFundCode, idDataGroup );
         dstrFundCode.strip();
         iter.getObject()->getField( ifds::ClassCode, dstrClassCode, idDataGroup );
         dstrClassCode.strip();
         if (( dstrFundCode == dstrCurFundCode ) && ( dstrClassCode == dstrCurClassCode )) 
            return NO_CONDITION;         
         ++iter;
      }
   }
*/
   if ( !_pProtectedFundList->isProtectedFund ( dstrFundCode, dstrClassCode, idDataGroup ) ){
      //Selected Fund/Class is not protected.
      ADDCONDITIONFROMFILE ( CND::ERR_FUND_CLASS_NOT_PROTECTED );
   }

   return(GETCURRENTHIGHESTSEVERITY());  
}

//*****************************************************************************
//*****************************************************************************
SEVERITY ResetInstr::isFundClassInHoldings( const BFDataGroupId& idDataGroup )
{   
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isFundClassInHoldings" ) );
   DString dstrAccountNum;
   MFAccount* pMFAccount;
   MFAccountHoldingList* pAccountHoldingList;
   getField ( ifds::AccountNum, dstrAccountNum, idDataGroup );
   if ( dstrAccountNum == I_("0") ) {
      ADDCONDITIONFROMFILE ( CND::ERR_ACCOUNT_EMPTY );
   } else {
      getWorkSession().getMFAccount ( idDataGroup, dstrAccountNum, pMFAccount, I_("N"), NULL_STRING/*, false, true */);
      pMFAccount->getAccountHoldingList( pAccountHoldingList, idDataGroup );
      DString dstrFundCode,dstrClassCode;
      getField ( ifds::FundCode, dstrFundCode, idDataGroup );
      getField ( ifds::ClassCode, dstrClassCode, idDataGroup );
      dstrFundCode.upperCase();
      dstrClassCode.upperCase();
      /*
      if ( pAccountHoldingList ) {
         BFObjIter iter( *pAccountHoldingList, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );      
         while ( !iter.end() ) {
            iter.getObject()->getField( ifds::rxFundCode, dstrFundCode, idDataGroup );
            dstrFundCode.strip();
            iter.getObject()->getField( ifds::rxClassCode, dstrClassCode, idDataGroup );
            dstrClassCode.strip();
            if (( dstrFundCode == dstrCurFundCode ) && ( dstrClassCode == dstrCurClassCode )) 
               return NO_CONDITION;         
            ++iter;
         }
      }*/
      if ( !pAccountHoldingList->isFundInHoldings ( dstrFundCode, dstrClassCode, idDataGroup ) ){
         //Selected fund is not in Account Holdings.
         ADDCONDITIONFROMFILE ( CND::ERR_ACCRUALS_FUND_NOT_IN_HOLDINGS );
      }
   }   
   return(GETCURRENTHIGHESTSEVERITY());  
}

//*****************************************************************************
//*****************************************************************************

void ResetInstr::Reversal( ResetInstr* pResetInstr, const BFDataGroupId& idDataGroup)
{
   BFData *tmp = new BFData(ifds::DSTC0243_VWRepeat_Record);
   BFDataFieldIter dIter( *tmp );

   DString dstr;
//   setObjectAsNew(pResetInstr->isNewObject());

   for( ;dIter; ++dIter )
   {
      const BFFieldId& idField = dIter().getId();
      pResetInstr->getField( idField, dstr, idDataGroup, false );
      //Skip CompleteDate, BatchName, BatchEffective and Trace

      if (( idField == ifds::CompleteDate ) || (idField == ifds::BatchName ) ||
         ( idField == ifds::BatchEffective) || (idField == ifds::Trace ) || ( idField == ifds::ResetDate ) )
         continue;


      if( idField == ifds::ResetID ) {
         setField(ifds::CanResetId, dstr, idDataGroup, false);      
      } else if ( idField != ifds::CanResetId ) {
         setField(idField, dstr, idDataGroup, false);               
      }      
   };

   getWorkSession().getMgmtCoOptions()->getField( ifds::CurrBusDate, dstr, idDataGroup, false );
   setFieldNoValidate ( ifds::ResetDate, dstr, idDataGroup, false );
   delete tmp;

   setAllFieldsReadOnly ( idDataGroup );
}

//*****************************************************************************
//*****************************************************************************
void ResetInstr::setAllFieldsReadOnly( const BFDataGroupId& idDataGroup )
{
   const CLASS_FIELD_INFO* pClassFieldInfo = (const CLASS_FIELD_INFO *)&classFieldInfo;
   for( int i = 0; i < NUM_FIELDS; i++, pClassFieldInfo++ )
   {
      setFieldReadOnly ( pClassFieldInfo->m_fieldId, idDataGroup, true );
   }      
}

//*****************************************************************************
//*****************************************************************************
SEVERITY ResetInstr::isResetAllowed ( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isResetAllowed" ) );
   DString dstrFundCode, dstrClassCode, dstrAccountNum, dstrMaxResets;
   DString dstrFundCode2, dstrClassCode2, dstrAccountNum2;
   getField ( ifds::FundCode, dstrFundCode, idDataGroup );
   getField ( ifds::ClassCode, dstrClassCode, idDataGroup );
   getField ( ifds::AccountNum, dstrAccountNum, idDataGroup );

   MFAccount *pMFAccount;
   getWorkSession().getMFAccount ( idDataGroup, dstrAccountNum, pMFAccount, I_("N"), NULL_STRING/*, false, true */);
   if ( pMFAccount ) {
      int OwnerAge = pMFAccount->getAgeofOwnerSeq01( idDataGroup );
      if ( OwnerAge > 79 ) {
         ADDCONDITIONFROMFILE ( CND::ERR_RESET_ENTITY_EXCEED_AGE_LIMIT );
         return GETCURRENTHIGHESTSEVERITY();
      }
   }

   dstrFundCode.strip().upperCase();
   dstrClassCode.strip().upperCase();
   // Lets get the maximum number of resets for this fund.
   if ( !_pProtectedFundList )
      getWorkSession().getProtectedFundList( _pProtectedFundList );

   if ( _pProtectedFundList ) {
      BFObjIter iter( *_pProtectedFundList, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );      
      while (!iter.end() ) {
         iter.getObject()->getField( ifds::FundCode, dstrFundCode2, idDataGroup );
         dstrFundCode2.strip().upperCase();
         iter.getObject()->getField( ifds::ClassCode, dstrClassCode2, idDataGroup );
         dstrClassCode2.strip().upperCase();
         
         if (( dstrFundCode == dstrFundCode2 ) && ( dstrClassCode == dstrClassCode2 ))
         {
            iter.getObject()->getField (ifds::ResetsAllowed, dstrMaxResets, idDataGroup );
            //we should not continue the loop when we found the record
            break;
         }
         ++iter;
      }
   }
   DString resetDate;   
   getField ( ifds::ResetDate, resetDate, idDataGroup,false );
   ResetInstrList* pResetInstrList = dynamic_cast <ResetInstrList*> (getParent());
   int numResets = pResetInstrList->getNumOfReset ( dstrFundCode, dstrClassCode, 
      dstrAccountNum,resetDate, idDataGroup );
   // If the number of reset is greater than the max allow already, we will return
   // and error condition.
   if ( numResets > dstrMaxResets.asInteger() ) {
      // The number of resets exceed the maximum allowed.
      ADDCONDITIONFROMFILE ( CND::ERR_RESET_EXCEED_MAX );
      return GETCURRENTHIGHESTSEVERITY();
   }
 

   //
   // do one thing at a time 
   // duplicate reset will be check in doValidateAll at leat level.
   //


   // We will make a view call here to ask the back end for all the reset instructions
   // for this fund.

   //yb2005/04/05  DString  mgmtCoIdOut, dstrEffectiveDate;   
   //yb2005/04/05  getField ( ifds::ResetDate, dstrEffectiveDate, idDataGroup );
   //yb2005/04/05  BFData   requestData(ifds::DSTC0243_REQ);
   //yb2005/04/05  BFData*  responseData = new BFData(ifds::DSTC0243_VW);
   
   //yb2005/04/05  requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   //yb2005/04/05  requestData.setElementValue( ifds::AccountNum, dstrAccountNum );
   //yb2005/04/05  requestData.setElementValue( ifds::FundCode, dstrFundCode );
   //yb2005/04/05  requestData.setElementValue( ifds::ClassCode, dstrClassCode );
   //yb2005/04/05  requestData.setElementValue( ifds::AsofDate, dstrEffectiveDate );
   //yb2005/04/05  requestData.setElementValue( ifds::Track, I_("N") );
   //yb2005/04/05  requestData.setElementValue( ifds::Activity, NULL_STRING );
   //yb2005/04/05  BFDataBroker::getInstance()->receive( DSTC_REQUEST::RESET_INSTR_LIST, 
   //yb2005/04/05                                        requestData, *responseData, DSTCRequestor(getSecurity(), true) );

/*   if( BFDataBroker::getInstance()->receive( DSTC_REQUEST::RESET_INSTR_LIST, 
      requestData, *responseData, DSTCRequestor(getSecurity(), true) ) <= WARNING ) {
      
      numResets += responseData->getRepeatCount();
   }

   if ( numResets > dstrMaxResets.asInteger() ) {
      ADDCONDITIONFROMFILE ( CND::ERR_RESET_EXCEED_MAX );
      return GETCURRENTHIGHESTSEVERITY();
   }
   */
   //yb2005/04/05  numResets = 0;
   //yb2005/04/05  DString dstrResetDate, dstrResetType, dstrResetDate2, dstrResetType2;
   //yb2005/04/05  getField ( ifds::ResetDate, dstrResetDate, idDataGroup );
   //yb2005/04/05  getField ( ifds::ResetType, dstrResetType, idDataGroup );
   // We will assume that the list will on contain resets for the same fund/class.
   //yb2005/04/05  for( unsigned long i = 0; i < responseData->getRepeatCount(); ++i )
   //yb2005/04/05  {
   //yb2005/04/05     const BFData& repeatData = responseData->getRepeat(i);      
   //yb2005/04/05     dstrResetDate2 = repeatData.getElementValue( ifds::ResetDate );
   //yb2005/04/05     dstrResetType2 = repeatData.getElementValue ( ifds::ResetType );   
   //yb2005/04/05     dstrResetType.strip();
   //yb2005/04/05     dstrResetType2.strip();
   //yb2005/04/05     if (( dstrResetDate == dstrResetDate2 ) /*&& ( dstrResetType == dstrResetType2 )*/ ) {
         //Duplicate Reset Instruction.
   //yb2005/04/05        ADDCONDITIONFROMFILE ( CND::ERR_DUP_RESET_INSTR );
   //yb2005/04/05        return GETCURRENTHIGHESTSEVERITY();
   //yb2005/04/05     }
      // We'll count only the client issued resets.  Ingoring the Expiry and Death Claim.
   //yb2005/04/05     if ( dstrResetType2 == CLIENT_REQ_RESET ) {
   //yb2005/04/05        ++numResets;
   //yb2005/04/05     }
   //yb2005/04/05   }   

   //yb2005/04/05  if ( numResets > dstrMaxResets.asInteger() ) {
   //yb2005/04/05     ADDCONDITIONFROMFILE ( CND::ERR_RESET_EXCEED_MAX );
   //yb2005/04/05     return GETCURRENTHIGHESTSEVERITY();
   //yb2005/04/05  }


   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ResetInstr.cpp-arc  $
// 
//    Rev 1.17   Aug 02 2005 16:38:46   AGUILAAM
// IN 329838 : call getBatchInfo within (new) init procedure only; 'no active batch' error from getBatchInfo when called from  doInitWithDefaultValues was causing Desktop to crash.
// 
//    Rev 1.16   Jun 29 2005 14:16:44   AGUILAAM
// IN 329838 - reverted back to ver 1.14. 
// 
//    Rev 1.15   Jun 10 2005 17:28:20   AGUILAAM
// IN 329838 - do not allow reset if numreset >= maxreset
// 
//    Rev 1.14   Apr 05 2005 15:52:10   yingbaol
// Incident 243363: fix 2 issues, 1) wrong duplicate check; 2) wrong max reset instruction check.
// 
//    Rev 1.13   Nov 17 2004 15:02:18   PURDYECH
// PET910 - .NET Conversion:  Fixed compiler warning messages
// 
//    Rev 1.12   Nov 14 2004 14:52:12   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.11   Jul 29 2003 10:31:30   HERNANDO
// PTS 10016740 - Removed reset type from duplicate check.  Also, fixed bug regarding setting fields to Read Only if completed transaction.
// 
//    Rev 1.10   Jul 17 2003 14:04:02   ZHANGCEL
// PTS 10019763 : Fix crash when user submits Reset Instruction
// 
//    Rev 1.9   Jun 26 2003 15:37:38   HSUCHIN
// PTS 10016854 - Reversals not working properly during TP.   CanResetId was not set properly.
// 
//    Rev 1.8   May 13 2003 08:39:12   sanchez
// sync. up with v.1.6.1.0 PTS# 10016787
// 
//    Rev 1.7   Mar 21 2003 18:21:46   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.6   Feb 06 2003 15:05:00   HSUCHIN
// added method isResetAllowed to check if the current cbo is allowed to be reset
// 
//    Rev 1.5   Jan 29 2003 16:24:52   HSUCHIN
// added some comments
// 
//    Rev 1.4   Jan 29 2003 12:15:56   HSUCHIN
// add bus rule to mark all field readonly when the reset instr has been completed
// 
//    Rev 1.3   Jan 27 2003 07:41:16   HSUCHIN
// added support for reversal
// 
//    Rev 1.2   Jan 26 2003 16:03:42   HSUCHIN
// bug fix and added support
// 
//    Rev 1.1   Jan 25 2003 17:36:20   HSUCHIN
// more enhancements
// 
//    Rev 1.0   Jan 24 2003 10:19:18   HSUCHIN
// Initial Revision
*/
