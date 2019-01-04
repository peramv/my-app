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
//    Copyright 2002 by International Financial, Inc.
//
//*****************************************************************************
//
// ^FILE   : AccrualsSearchCrieria.cpp
// ^AUTHOR : 
// ^DATE   : Jan 09, 2002
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : AccrualsSearchCrieria
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include "accrualssearchcriteria.hpp"
#include "funddetail.hpp"
#include "funddetaillist.hpp"
#include "fundmasterlist.hpp"
#include "mfaccountholdinglist.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "fundlist.hpp"

namespace
{
   const I_CHAR * const CLASSNAME = I_( "AccrualsSearchCriteria" );
   const I_CHAR * const INTEREST_ACCURAL = I_( "InterestAccural" );
   const I_CHAR * const MF_ACCURAL = I_( "MFAccural" );
   const I_CHAR * const MF_REBATE_ACCURAL = I_( "MFRebateAccural" );
   const I_CHAR * const INTEREST_ACCRUAL_TYPE = I_( "01" );
   const I_CHAR * const MF_ACCRUAL_TYPE = I_( "02" );
   const I_CHAR * const MF_REBATE_ACCRUAL_TYPE = I_( "03" );
   const I_CHAR * const NO = I_( "N" );
   const I_CHAR * const YES = I_( "Y" );   
}

namespace CND
{
   extern const long ERR_ENTITY_TYPE_EMPTY;
   extern const long ERR_START_DATE_LATE_THAN_STOP_DATE;
   extern const long ERR_START_DATE_BEFORE_EFFECTIVE_DATE_OF_FUND;
   extern const long ERR_START_DATE_BEFORE_LAST_DIV_DATE;
   extern const long ERR_ACCRUALS_FUND_NOT_IN_HOLDINGS;
   extern const long ERR_INVALID_FUND_CLASS_CODES;
   extern const long ERR_INVALID_FUND_NUMBER;
   extern const long ERR_FUND_CLASS_MUST_BE_SPECIFIED;
   extern const long ERR_THIS_FUND_HAS_NO_MGT_FEE;
   extern const long ERR_THIS_FUND_HAS_NO_MGT_REBATE_FEE;
   extern const long ERR_START_DATE_MUST_BE_PRIOR_TO_LAST_PROCESSED_DATE;
	extern const long ERR_START_DATE_EARLEAR_THAN_LAST_DIVIDEND_DATE;
	extern const long ERR_START_DATE_DISTRIBUTION_DAY;
	extern const long WARN_ALL_FUND_ACCRUAL;
	extern const long	ERR_FUND_IS_NOT_ACCRUAL_TYPE;
	extern const long	ERR_END_DATE_EARLIER_THAN_ALL_FUND_DIV_DATE;
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFTextFieldId AccrualSummary;
   extern CLASS_IMPORT const BFTextFieldId AccrualType;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFDateFieldId EndDate;
   extern CLASS_IMPORT const BFTextFieldId FundClass;
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId rxClassCode;
   extern CLASS_IMPORT const BFTextFieldId rxFundCode;
   extern CLASS_IMPORT const BFTextFieldId FundNumber;
   extern CLASS_IMPORT const BFTextFieldId FundType;
   extern CLASS_IMPORT const BFTextFieldId InclUnsettled;
   extern CLASS_IMPORT const BFDateFieldId LastDivDate;
   extern CLASS_IMPORT const BFDateFieldId LastMFRebateDate;
   extern CLASS_IMPORT const BFDateFieldId LastMgmtFeeDate;
   extern CLASS_IMPORT const BFTextFieldId MgtFeeElig;
   extern CLASS_IMPORT const BFTextFieldId MgtFeeRbtElig;
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFDateFieldId StartDate;
   extern CLASS_IMPORT const BFDateFieldId ValueAsAt;
   extern CLASS_IMPORT const BFTextFieldId CompoundDate;
	extern CLASS_IMPORT const BFTextFieldId IntAccrualMthd;
	extern CLASS_IMPORT const BFDateFieldId LastIntAccDate;

}

//*****************************************************************************
// UT - stands for Unsettled Trades
// MF - Management Fee
// MF - Management Fee Rebate
//*****************************************************************************

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//   Field DD Id,           State Flags,              Group Flags
   { ifds::AccountNum,     BFCBO::NOT_ON_HOST,          0 }, 
   { ifds::AccrualSummary, BFCBO::NOT_ON_HOST,          0 }, 
   { ifds::AccrualType,    BFCBO::NOT_ON_HOST,          0 }, 
   { ifds::ClassCode,      BFCBO::NOT_ON_HOST,          0 }, 
   { ifds::EndDate,        BFCBO::NOT_ON_HOST,          0 }, 
   { ifds::FundClass,      BFCBO::IMMEDIATE_VALIDATION, 0 }, 
   { ifds::FundCode,       BFCBO::NOT_ON_HOST,          0 }, 
   { ifds::FundNumber,     BFCBO::IMMEDIATE_VALIDATION, 0 }, 
   { ifds::StartDate,      BFCBO::NOT_ON_HOST,          0 }, 
   { ifds::InclUnsettled,  BFCBO::NOT_ON_HOST,          0 }, 
   { ifds::CompoundDate,	 BFCBO::IMMEDIATE_VALIDATION, 0 }, 


};

//*****************************************************************************

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//*****************************************************************************
// Constructor
//*****************************************************************************

AccrualsSearchCriteria::AccrualsSearchCriteria( BFAbstractCBO &parent )
:  MFCanBFCbo( parent ),
_pMFAccountHoldingList ( NULL ),
_pFundDetailsList ( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );   
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );

   // Setup cross edits
   addCrossEdit(ifds::FundClass, ifds::FundCode);
   addCrossEdit(ifds::FundClass, ifds::ClassCode);
   addCrossEdit(ifds::CompoundDate, ifds::StartDate);
   addCrossEdit(ifds::CompoundDate, ifds::EndDate);

   // Store the Fund Details List locally for easy access.
   getMgmtCo().getFundDetailList( _pFundDetailsList );
}

//*****************************************************************************
// Destructor
//*****************************************************************************

AccrualsSearchCriteria::~AccrualsSearchCriteria()
{
   TRACE_DESTRUCTOR( CLASSNAME );

}

//*****************************************************************************
// Initializes search criteria cbo with default information.  Sets up a local
// pointer to Account Holdings for later verification.
// @param   DString dstrAccountNum - Account Number used to get Account Holdings
//          DString dstrAccrualType - Interest, MF, MFR are the 3 different types.
//          const BFDataGroupId& idDataGroup - current datagroup.
// @returns void.
//*****************************************************************************

void AccrualsSearchCriteria::init( DString dstrAccountNum, DString dstrAccrualType, const BFDataGroupId& idDataGroup )
{
   setField ( ifds::AccountNum, dstrAccountNum, idDataGroup );
   setField ( ifds::AccrualType, dstrAccrualType, idDataGroup );
   _dstrAccrualType = dstrAccrualType;
   DString dstrCurrBusDate;

   getWorkSession().getMgmtCoOptions()->getField( ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false );      
   setFieldNoValidate( ifds::StartDate, dstrCurrBusDate, idDataGroup, false, true, true, false );
   setFieldNoValidate( ifds::EndDate, dstrCurrBusDate, idDataGroup, false, true, false );
   setFieldNoValidate( ifds::InclUnsettled, NO, idDataGroup, false, true, false );
   setFieldNoValidate( ifds::AccrualSummary, NO, idDataGroup, false, true, false );      

   MFAccount *pMFAccount;
   getWorkSession().getMFAccount( idDataGroup, dstrAccountNum, pMFAccount );
   if( pMFAccount )
   {
      pMFAccount->getAccountHoldingList( _pMFAccountHoldingList, idDataGroup );
   } //else add condition
}

//*****************************************************************************
// Validates the field information. The following fields are validated.
// FundClass - Cross edit of FundCode, ClassCode
// StartDate
// FundNumber - Sets FundCode/Class Code when valid.
// @param   const BFFieldId& idField - field to be validated.
//          const DString& strValue - Value contained in field.
//          const BFDataGroupId& idDataGroup - datagroup to be validated.
// @returns SEVERITY.
//*****************************************************************************

SEVERITY AccrualsSearchCriteria::doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

   if( idField == ifds::FundClass )
   {
      ValidateFundClass ( idDataGroup );
		validateFundTypeForInterest( idDataGroup );
   }
	else if( idField == ifds::StartDate )
	{
	   validateStartDateFundClass(idDataGroup );	
	}
   else if( idField == ifds::CompoundDate )
   {
      ValidateDateRange ( idDataGroup );
   }
   else if( idField == ifds::FundNumber )
   {
      if( strValue == NULL_STRING )
         return(GETCURRENTHIGHESTSEVERITY());
      DString dstrFundCode, dstrClassCode;
      if( getWorkSession().GetFundClassCode( strValue, dstrFundCode, dstrClassCode ) )
      {
         DString dstrOldFundCode, dstrOldClassCode;
         getField ( ifds::FundCode, dstrOldFundCode, idDataGroup );
         getField ( ifds::ClassCode, dstrOldClassCode, idDataGroup );
         if( dstrOldFundCode != dstrFundCode )
            setField ( ifds::FundCode, dstrFundCode, idDataGroup );
         if( dstrOldClassCode != dstrClassCode )
            setField ( ifds::ClassCode, dstrClassCode, idDataGroup );
      }
      else
      {
         //Invalid Fund Number
         ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_NUMBER );
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************
// Functions which checks to see the current Fund/Class code is in the Account
// holdings.  NULL_STRING for Fund/Class codes is accepted and considered as all
// funds.
// @param   const BFDataGroupId& idDataGroup - current data group.
// @retursn SEVERITY.
//*****************************************************************************

SEVERITY AccrualsSearchCriteria::ValidateFundClass(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateFundClass" ) );

   DString dstrFundCode, dstrClassCode, dstrAccrualSummary;
   getField ( ifds::FundCode, dstrFundCode, idDataGroup );
   getField ( ifds::ClassCode, dstrClassCode, idDataGroup );
   getField ( ifds::AccrualSummary, dstrAccrualSummary, idDataGroup );

   if( dstrFundCode == NULL_STRING && dstrClassCode == NULL_STRING && dstrAccrualSummary == NO )
   {
      /*DString dstrCurrBusDate;
      getWorkSession().getMgmtCoOptions()->getField( DBR::CurrBusDate, dstrCurrBusDate, idDataGroup, false );
      setField ( DBR::EndDate, dstrCurrBusDate, idDataGroup );
      setEarliestAllFundDates( idDataGroup );*/
      ADDCONDITIONFROMFILE( CND::ERR_FUND_CLASS_MUST_BE_SPECIFIED );               
      return(GETCURRENTHIGHESTSEVERITY());
   }
   else if( dstrAccrualSummary == YES )
   {
      return(NO_CONDITION);
   }
   else
   {
    
		_dstrFundCode = dstrFundCode;
		_dstrClassCode = dstrClassCode;
		
		if( isFundinHoldings ( dstrFundCode, dstrClassCode, idDataGroup ) <= WARNING )
      {
         //Now that the fund is valid and in holdings we will set the fund number field if this is a CDN/LUX market.      
         BFObjIter iterFundDetailsList ( *_pFundDetailsList, idDataGroup, false, BFObjIter::ITERTYPE::ALL );   
         DString dstrKey, dstrMarket ;
         _pFundDetailsList->getStrKey ( dstrKey, dstrFundCode, dstrClassCode );
         dstrMarket = DSTCommonFunctions::getMarket();
         if( !iterFundDetailsList.positionByKey ( dstrKey ) )
         {
            // we could not find the fund in the fundetails list.
            ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_CLASS_CODES );
         }
         else
         {
            bool _bCanLuxMarket = ( dstrMarket == MARKET_IDS::CANADA || dstrMarket == MARKET_IDS::LUXEMBOURG );
            if( _bCanLuxMarket )
            {
               DString dstrFundNumber;
               getWorkSession().GetFundNumber( dstrFundCode, dstrClassCode, dstrFundNumber );
               // since fund/class is correct, do not fire doapply on set of fundnubmer.
               setFieldNoValidate ( ifds::FundNumber, dstrFundNumber, idDataGroup, false, true, true, false );
            }
				if( _dstrAccrualType == INTEREST_ACCRUAL_TYPE )
				{
				
				}


            if( _dstrAccrualType == MF_ACCRUAL_TYPE )
            {
               DString dstrMgtFeeElig;
               iterFundDetailsList.getObject()->getField ( ifds::MgtFeeElig, dstrMgtFeeElig, idDataGroup );
               if( dstrMgtFeeElig != YES )
               {
                  ADDCONDITIONFROMFILE ( CND::ERR_THIS_FUND_HAS_NO_MGT_FEE );
                  return(GETCURRENTHIGHESTSEVERITY());
               }
            }
            else if( _dstrAccrualType == MF_REBATE_ACCRUAL_TYPE )
            {
               DString dstrMgtFeeRbtElig;
               iterFundDetailsList.getObject()->getField ( ifds::MgtFeeRbtElig, dstrMgtFeeRbtElig, idDataGroup );
               if( dstrMgtFeeRbtElig != YES )
               {
                  ADDCONDITIONFROMFILE ( CND::ERR_THIS_FUND_HAS_NO_MGT_REBATE_FEE );
                  return(GETCURRENTHIGHESTSEVERITY());
               }
            }
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************
// Function which iterates through the fund holding comparing with the
// Fund/Class passed in.
// @param   const DString& dstrFundCode - Fund Code.
//          const DString& dstrClassCode - Class Code.
//          const BFDataGroupId& idDataGroup - current data group.
// @returns SEVERITY.
//*****************************************************************************

SEVERITY AccrualsSearchCriteria::isFundinHoldings( const DString& dstrSrchFundCode, const DString& dstrSrchClassCode, const BFDataGroupId& idDataGroup )
{  
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isFundinHoldings" ) );

   DString dstrFundCode, dstrClassCode;
   DString dstrSearchFundCode( dstrSrchFundCode ), dstrSearchClassCode( dstrSrchClassCode );
   BFObjIter iterMFAccountHoldings (*_pMFAccountHoldingList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED); 

   // Iterate through MFAccountHoldingList and see if fund class passed is in list
   while( !iterMFAccountHoldings.end() )
   {
      iterMFAccountHoldings.getObject()->getField ( ifds::rxFundCode,  dstrFundCode, idDataGroup );
      iterMFAccountHoldings.getObject()->getField ( ifds::rxClassCode, dstrClassCode, idDataGroup );

      // If match found, return NO_CONDITION
      if( (dstrFundCode.strip().upperCase() == dstrSearchFundCode.strip().upperCase()) 
           && (dstrClassCode.strip().upperCase() == dstrSearchClassCode.strip().upperCase()) ) 
      {
         return(NO_CONDITION);
      }
      ++iterMFAccountHoldings;
   }

   ADDCONDITIONFROMFILE( CND::ERR_ACCRUALS_FUND_NOT_IN_HOLDINGS );

   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************
// Sets the start date to the last divident date and stores additional fund 
// information for later validatation eg. Start date must be before fund 
// effective date.
// @param   const DString& dstrFundCode - Fund Code.
//          const DString& dstrClassCode - Class Code.
//          long lDataGroupid - current data group.
// @returns SEVERITY.
//*****************************************************************************

SEVERITY AccrualsSearchCriteria::setDefaultStartDate( const DString& dstrFundCode, const DString& dstrClassCode, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setDefaultStartDate" ) );

   if( ( dstrFundCode == NULL_STRING ) || ( dstrClassCode == NULL_STRING ) )
      return(GETCURRENTHIGHESTSEVERITY());
   DString dstrKey;
   _pFundDetailsList->getStrKey ( dstrKey, dstrFundCode, dstrClassCode );
   BFObjIter iterFundDetailsList ( *_pFundDetailsList, idDataGroup, false, BFObjIter::ITERTYPE::ALL );   
   if( !iterFundDetailsList.positionByKey ( dstrKey ) )
   {
      // we could not find the fund in the fundetails list.
      ADDCONDITIONFROMFILE( CND::ERR_INVALID_FUND_CLASS_CODES );
   }
   else
   {
      DString dstrFundNumber, dstrAccrualType;
      if( _dstrAccrualType == INTEREST_ACCRUAL_TYPE )
      {        
			FundMasterList *pFundMasterList; 
			if( getMgmtCo().getFundMasterList( pFundMasterList ) <= WARNING &&
				 NULL != pFundMasterList )
			{
				DString dstrKey;
				pFundMasterList->buildKey(dstrFundCode,dstrKey );
				BFObjIter iter(*pFundMasterList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
				if(iter.positionByKey ( dstrKey ) )
				{
					DString dstrIntAccrualMethod;
					iter.getObject()->getField( ifds::IntAccrualMthd, dstrIntAccrualMethod, idDataGroup, false );
					if ( I_( "0" ) == dstrIntAccrualMethod.stripAll() )
					{
						iterFundDetailsList.getObject()->getField ( ifds::LastDivDate, _dstrDefaultStartDate, idDataGroup );
						iterFundDetailsList.getObject()->getField ( ifds::LastDivDate, _dstrDefaultStartDateFormatted, idDataGroup, true );
					}
					else if ( I_( "1" ) == dstrIntAccrualMethod.stripAll() )
					{
						iterFundDetailsList.getObject()->getField ( ifds::LastIntAccDate, _dstrDefaultStartDate, idDataGroup );
						iterFundDetailsList.getObject()->getField ( ifds::LastIntAccDate, _dstrDefaultStartDateFormatted, idDataGroup, true );
					}
				}
			}
      }
      else if( _dstrAccrualType == MF_ACCRUAL_TYPE )
      {
         iterFundDetailsList.getObject()->getField ( ifds::LastMgmtFeeDate, _dstrDefaultStartDate, idDataGroup );
         iterFundDetailsList.getObject()->getField ( ifds::LastMgmtFeeDate, _dstrDefaultStartDateFormatted, idDataGroup, true );
      }
      else if( _dstrAccrualType == MF_REBATE_ACCRUAL_TYPE )
      {
         iterFundDetailsList.getObject()->getField ( ifds::LastMFRebateDate, _dstrDefaultStartDate, idDataGroup );
         iterFundDetailsList.getObject()->getField ( ifds::LastMFRebateDate, _dstrDefaultStartDateFormatted, idDataGroup, true );
      }
      iterFundDetailsList.getObject()->getField ( ifds::EffectiveDate, _dstrEarliestStartDate, idDataGroup );
      iterFundDetailsList.getObject()->getField ( ifds::EffectiveDate, _dstrEarliestStartDateFormatted, idDataGroup, true );
      if( _dstrDefaultStartDate == NULL_STRING )
      {
         setFieldNoValidate ( ifds::StartDate, _dstrEarliestStartDate, idDataGroup, false, true, true, false );
      }
      else
      {
         DSTCommonFunctions::addDays ( _dstrDefaultStartDate, _dstrDefaultStartDate, 1 );
         setFieldNoValidate ( ifds::StartDate, _dstrDefaultStartDate, idDataGroup, false, true, true, false );
         getField ( ifds::StartDate, _dstrDefaultStartDateFormatted, idDataGroup, true );
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************
// Validates the Date range.  Start date must be before end date. Start date
// must be later than Fund Effective date. Start date must be later than
// fund's last divident date.
// @param   const BFDataGroupId& idDataGroup - current data group.
// @returns SEVERITY.
//*****************************************************************************

SEVERITY AccrualsSearchCriteria::ValidateDateRange(const BFDataGroupId& idDataGroup)
{
   MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateDateRange" ) );
   DString dstrStartDate, dstrEndDate, dstrTemp, dstrAccrualSummary;
   getField ( ifds::StartDate, dstrStartDate, idDataGroup );
   getField ( ifds::EndDate, dstrEndDate, idDataGroup );
   getField ( ifds::AccrualSummary, dstrAccrualSummary, idDataGroup );
   if( ( _dstrEarliestStartDate != NULL_STRING ) && ( DSTCommonFunctions::CompareDates( dstrStartDate, _dstrEarliestStartDate )
                                                      == DSTCommonFunctions::FIRST_EARLIER ) && ( dstrAccrualSummary == NO ) )
   {
      // add condition, start date earlier than fund effective date.
      DString error = I_( "" );      
      dstrTemp = _dstrEarliestStartDateFormatted;

      //DSTCommonFunctions::formatToolTipDate( ifds::EffectiveDate, dstrTemp );
      addIDITagValue( error, I_("DATE"), dstrTemp );
      ADDCONDITIONFROMFILEIDI( CND::ERR_START_DATE_BEFORE_EFFECTIVE_DATE_OF_FUND, error );
   }
   else if( dstrAccrualSummary == NO &&
		      DSTCommonFunctions::CompareDates( dstrEndDate, dstrStartDate ) == DSTCommonFunctions::FIRST_EARLIER )
   {
      ADDCONDITIONFROMFILE( CND::ERR_START_DATE_LATE_THAN_STOP_DATE );
   }
	else if ( dstrAccrualSummary == YES )
	{
		bool bLastDivDateEarlierThanEndDate = false;				
		
		FundMasterList *pFundMasterList; 
		if( getMgmtCo().getFundMasterList( pFundMasterList ) <= WARNING &&
			 NULL != pFundMasterList && 
			 NULL != _pFundDetailsList )
		{
			BFObjIter iterFundMasterList(  *pFundMasterList,   idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
			BFObjIter iterFundDetailsList( *_pFundDetailsList, idDataGroup, false, BFObjIter::ITERTYPE::ALL );   			

			// Iterate through MFAccountHoldingList and check LastDivDate against End Date
			BFObjIter iterMFAccountHoldings (*_pMFAccountHoldingList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED); 			
			while( !iterMFAccountHoldings.end() )
			{
				DString dstrFundCode,dstrClassCode, dstrLastDivDate;
				iterMFAccountHoldings.getObject()->getField ( ifds::rxFundCode,  dstrFundCode,  idDataGroup );
				iterMFAccountHoldings.getObject()->getField ( ifds::rxClassCode, dstrClassCode, idDataGroup );
								
				DString dstrFundDetlKey;				         
				_pFundDetailsList->getStrKey ( dstrFundDetlKey, dstrFundCode, dstrClassCode );    
				iterFundDetailsList.begin();
				if( iterFundDetailsList.positionByKey ( dstrFundDetlKey ) )
				{															
					DString dstrFundMstrKey;
					pFundMasterList->buildKey( dstrFundCode, dstrFundMstrKey );
					
					iterFundMasterList.begin();
					if( iterFundMasterList.positionByKey ( dstrFundMstrKey ) )
					{
						if ( _dstrAccrualType == INTEREST_ACCRUAL_TYPE )
						{						
							DString dstrIntAccrualMethod;
							iterFundMasterList.getObject()->getField( ifds::IntAccrualMthd, dstrIntAccrualMethod, idDataGroup, false );
							if ( I_( "0" ) == dstrIntAccrualMethod.stripAll() )
							{
								iterFundDetailsList.getObject()->getField ( ifds::LastDivDate, dstrLastDivDate, idDataGroup );					
							}
							else if ( I_( "1" ) == dstrIntAccrualMethod.stripAll() )
							{
								iterFundDetailsList.getObject()->getField ( ifds::LastIntAccDate, dstrLastDivDate, idDataGroup );						
							}
						}
						else if( _dstrAccrualType == MF_ACCRUAL_TYPE )
						{
							iterFundDetailsList.getObject()->getField ( ifds::LastMgmtFeeDate, dstrLastDivDate, idDataGroup );							
						}
						else if( _dstrAccrualType == MF_REBATE_ACCRUAL_TYPE )
						{
							iterFundDetailsList.getObject()->getField ( ifds::LastMFRebateDate, dstrLastDivDate, idDataGroup );							
						}
					}
				}
																			
				if ( DSTCommonFunctions::CompareDates( dstrLastDivDate, dstrEndDate ) == DSTCommonFunctions::FIRST_EARLIER )
				{
					bLastDivDateEarlierThanEndDate = true;
					break;
				}
			
				++iterMFAccountHoldings;
			}
		}

		if ( false == bLastDivDateEarlierThanEndDate )
		{
			// No account fund has last dividend date earlier than end date.
			ADDCONDITIONFROMFILE( CND::ERR_END_DATE_EARLIER_THAN_ALL_FUND_DIV_DATE );
		}
	}
/*   else if( ( _dstrAccrualType == MF_ACCRUAL_TYPE ) || 
            ( _dstrAccrualType == MF_REBATE_ACCRUAL_TYPE ) )
   {
      if( DSTCommonFunctions::CompareDates( _dstrDefaultStartDate, dstrStartDate ) == DSTCommonFunctions::FIRST_EARLIER )
      {
         DString error = I_( "" );      
         dstrTemp = _dstrDefaultStartDateFormatted;
         //DSTCommonFunctions::formatToolTipDate( ifds::EffectiveDate, dstrTemp );
         addIDITagValue( error, I_("DATE"), dstrTemp );
         ADDCONDITIONFROMFILEIDI( CND::ERR_START_DATE_MUST_BE_PRIOR_TO_LAST_PROCESSED_DATE, error );
      }
   }*/
   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************
// This function will iterate through account holdings and Fund Details list
// seeking the earliest IntAccrLastDivDate (Last Divident Date) and Effective 
// date (Fund Effective Date).  These dates will then be stored to the private
// member variables _dstrIntAccrLastDivDate and _dstrEarliestStartDate.  This is
// used for All Fund mode for MF/MFR since Interest Accruals do not require
// start date for All Fund mode.
//
// @param   const BFDataGroupId& idDataGroup - current data group.
// @returns void
//*****************************************************************************
/*
void AccrualsSearchCriteria::setEarliestAllFundDates ( const BFDataGroupId& idDataGroup )
{
   DString dstrFundCode, dstrClassCode, dstrKey, dstrLastDefaultStartDate, dstrEffectiveDate;
   BFObjIter iterMFAccountHoldings (*_pMFAccountHoldingList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
   while ( !iterMFAccountHoldings.end() ) {
      iterMFAccountHoldings.getObject()->getField ( DBR::FundCode, dstrFundCode, idDataGroup );
      iterMFAccountHoldings.getObject()->getField ( DBR::ClassCode, dstrClassCode, idDataGroup );
      BFObjIter iterFundDetailsList ( *_pFundDetailsList, idDataGroup, false, BFObjIter::ITERTYPE::ALL );      
      _pFundDetailsList->getStrKey ( dstrKey, dstrFundCode, dstrClassCode );
      if ( iterFundDetailsList.positionByKey ( dstrKey ) ) {         
         if ( _dstrAccrualType == INTEREST_ACCRUAL_TYPE ) {
            iterFundDetailsList.getObject()->getField ( DBR::LastDivDate, dstrLastDefaultStartDate, idDataGroup );
         } else if ( _dstrAccrualType == MF_ACCRUAL_TYPE ) {
            //iterFundDetailsList.getObject()->getField ( DBR::LastMFDate, dstrLastDefaultStartDate, idDataGroup );
         } else if ( _dstrAccrualType == MF_REBATE_ACCRUAL_TYPE ) {
            //iterFundDetailsList.getObject()->getField ( DBR::LastMFRDate, dstrLastDefaultStartDate, idDataGroup );
         }
//         iterFundDetailsList.getObject()->getField ( DBR::LastDivDate, dstrLastDivDate, idDataGroup );
         iterFundDetailsList.getObject()->getField ( DBR::EffectiveDate, dstrEffectiveDate, idDataGroup );
         if ( DSTCommonFunctions::CompareDates( dstrEffectiveDate, _dstrEarliestStartDate )
            == DSTCommonFunctions::DATE_ORDER::FIRST_EARLIER ) {
            _dstrEarliestStartDate = dstrEffectiveDate;
         }
         if ( DSTCommonFunctions::CompareDates( dstrLastDefaultStartDate, _dstrDefaultStartDate )
            == DSTCommonFunctions::DATE_ORDER::FIRST_EARLIER ) {
            _dstrDefaultStartDate = dstrLastDefaultStartDate;
            DSTCommonFunctions::addDays ( dstrLastDivDate, _dstrDefaultStartDate, 1 );
         }         
      }
      ++iterMFAccountHoldings;
   }
   if ( _dstrDefaultStartDate != NULL_STRING )
      setFieldNoValidate ( DBR::StartDate, _dstrDefaultStartDate, idDataGroup, false, true, true, NULL, false );
   else 
      setFieldNoValidate ( DBR::StartDate, _dstrEarliestStartDate, idDataGroup, false, true, true, NULL, false );
}
*/
//******************************************************************************
// Override the doPreValidationAll to mark the FundClass Field dirty so that
// doValidateField will always execute.
//
// @param   const BFDataGroupId& idDataGroup - current data group.
//******************************************************************************
SEVERITY AccrualsSearchCriteria::doPreValidateAll( const BFDataGroupId& idDataGroup )
{
   setValidFlag ( ifds::FundClass, idDataGroup, false );
   DString dstrFundCode, dstrClassCode;
   getField ( ifds::FundCode, dstrFundCode, idDataGroup );
   getField ( ifds::ClassCode, dstrClassCode, idDataGroup );
   if( ( dstrFundCode != NULL_STRING ) && ( dstrClassCode != NULL_STRING ) )
      setValidFlag ( ifds::StartDate, idDataGroup, false );
   return(NO_CONDITION);
}

//*****************************************************************************

SEVERITY AccrualsSearchCriteria::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );
   if( idField == ifds::FundClass )
   {
      DString dstrFundCode, dstrClassCode;
      getField ( ifds::FundCode, dstrFundCode, idDataGroup );
      getField ( ifds::ClassCode, dstrClassCode, idDataGroup );
      setDefaultStartDate ( dstrFundCode, dstrClassCode, idDataGroup );
   }
   else if( idField == ifds::AccrualSummary )
   {
      DString dstrFundCode, dstrClassCode,dstrSummary,dstrFundNum;
		getField(ifds::AccrualSummary,dstrSummary,idDataGroup,false );
		dstrSummary.strip().upperCase();
		if(dstrSummary ==  NO )
		{
			setFieldNoValidate(ifds::FundCode,_dstrFundCode,idDataGroup );
			setFieldNoValidate(ifds::ClassCode,_dstrClassCode,idDataGroup );

         DString dstrFundNumber;
         getWorkSession().GetFundNumber( dstrFundCode, dstrClassCode, dstrFundNumber );
         // since fund/class is correct, do not fire doapply on set of fundnubmer.
         setFieldNoValidate ( ifds::FundNumber, dstrFundNumber, idDataGroup, false, true, true, false );

		}
		
      getField ( ifds::FundCode, dstrFundCode, idDataGroup );
      getField ( ifds::ClassCode, dstrClassCode, idDataGroup );
		setValidFlag ( ifds::StartDate, idDataGroup, false );

      if( ( dstrFundCode == NULL_STRING ) && ( dstrClassCode == NULL_STRING ) )
      {
         setValidFlag ( ifds::FundCode, idDataGroup, false );
         setValidFlag ( ifds::ClassCode, idDataGroup, false );
         setValidFlag ( ifds::ClassCode, idDataGroup, false );
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//*******************************************************************************
// for interest accrual, The fund type must be 

SEVERITY AccrualsSearchCriteria::validateFundTypeForInterest(  const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundTypeForInterest" ) );
   if( _dstrAccrualType == INTEREST_ACCRUAL_TYPE )
	{
	
		DString dstrFundCode,dstrClassCode;
		getField(ifds::FundCode,dstrFundCode,idDataGroup,false );
		getField(ifds::ClassCode,dstrClassCode,idDataGroup,false );
		dstrFundCode.strip();
		dstrClassCode.strip();
		if( dstrClassCode == NULL_STRING ||  dstrFundCode == NULL_STRING )
		{
			return NO_CONDITION;
		}


		FundMasterList *pFundMasterList; 
		SEVERITY sevRtn = getMgmtCo().getFundMasterList( pFundMasterList );

		if( pFundMasterList && sevRtn <= WARNING )
		{
			DString dstrKey;
			pFundMasterList->buildKey(dstrFundCode,dstrKey );
			BFObjIter iter(*pFundMasterList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
			if(iter.positionByKey ( dstrKey ) )
			{
				DString dstrFundType;
				iter.getObject()->getField(ifds::FundType,dstrFundType,idDataGroup,false);
				dstrFundType.strip().upperCase();
				if(dstrFundType != I_("I") )
				{
				ADDCONDITIONFROMFILE( CND::ERR_FUND_IS_NOT_ACCRUAL_TYPE );
						//issue error "Fund must be Interest Accrual Type." 			
				
				}			
			}
		}	
	}
   return(GETCURRENTHIGHESTSEVERITY());
}
//*********************************************************************************
SEVERITY AccrualsSearchCriteria::validateStartDateFundClass( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "checkStartDateAgainstValueAsAt" ) );
   if( _dstrAccrualType == INTEREST_ACCRUAL_TYPE )
	{
		DString dstrFund,dstrClass,dstrFromDate,dstrToDate,dstrPrevDatePressed,dstrNextDatePressed;
		getField ( ifds::FundCode, dstrFund, idDataGroup );
		getField ( ifds::ClassCode, dstrClass, idDataGroup );
		getField ( ifds::StartDate, dstrFromDate, idDataGroup,false );
		dstrFund.strip().upperCase();
		dstrClass.strip().upperCase();
		if( dstrFund == NULL_STRING && dstrClass == NULL_STRING )
		{  // All FundMode
			// add warning condition here.
		  
			ADDCONDITIONFROMFILE( CND::WARN_ALL_FUND_ACCRUAL );
			
			// to display warning field at enddate control
			SEVERITY sevRtn = GETCURRENTHIGHESTSEVERITY( );
			if( sevRtn >= WARNING )
			{
				CONDITIONVECTOR* _pCond;
				
				getFieldConditionVector(ifds::EndDate,idDataGroup,_pCond );
				if( _pCond == NULL )
					_pCond = new CONDITIONVECTOR;
				int count = CURRENTCONDITIONCOUNT( );
				Condition   *c = NULL;
				for( int i = 0; i < count; i++ )
				{
					c = new Condition( *GETCURRENTCONDITION( i ));
					_pCond->push_back( c );
				};
				setFieldConditionVector(ifds::EndDate, idDataGroup,_pCond );
				notifyObservers( ifds::EndDate, idDataGroup, FIELD_NOTIFICATIONS, E_EVENT_VALUE_CHANGE, I_( "" ) );
			}



			return sevRtn;
		}
		dstrToDate = dstrFromDate;
		dstrPrevDatePressed = I_( "Y" );
		dstrNextDatePressed = I_( "N" );		
		DString dstrKey;
		_pFundDetailsList->getStrKey ( dstrKey, dstrFund, dstrClass );
		BFObjIter iterFundDetailsList ( *_pFundDetailsList, idDataGroup, false, BFObjIter::ITERTYPE::ALL );   
		if( !iterFundDetailsList.positionByKey ( dstrKey ) )
		{
			 return GETCURRENTHIGHESTSEVERITY();
		}
		DString dstrLastDivDate,dstrEffectiveDate,dstrOrgDivDate;

		//iterFundDetailsList.getObject()->getField( ifds::LastDivDate,dstrLastDivDate,idDataGroup,false );
		FundMasterList *pFundMasterList; 
		if( getMgmtCo().getFundMasterList( pFundMasterList ) <= WARNING &&
			 NULL != pFundMasterList )
		{
			DString dstrKey;
			pFundMasterList->buildKey(dstrFund,dstrKey );
			BFObjIter iter(*pFundMasterList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
			if(iter.positionByKey ( dstrKey ) )
			{
				DString dstrIntAccrualMethod;
				iter.getObject()->getField( ifds::IntAccrualMthd, dstrIntAccrualMethod, idDataGroup, false );
				if ( I_( "0" ) == dstrIntAccrualMethod.stripAll() )
				{
					iterFundDetailsList.getObject()->getField ( ifds::LastDivDate, dstrLastDivDate, idDataGroup );						
				}
				else if ( I_( "1" ) == dstrIntAccrualMethod.stripAll() )
				{
					iterFundDetailsList.getObject()->getField ( ifds::LastIntAccDate, dstrLastDivDate, idDataGroup );						
				}
			}
		}

		iterFundDetailsList.getObject()->getField( ifds::EffectiveDate,dstrEffectiveDate,idDataGroup,false );
		dstrOrgDivDate = dstrLastDivDate;	
		
		DSTCommonFunctions::addDays ( dstrLastDivDate, dstrLastDivDate, 1 );// last dividend day + 1;
		
		if(  DSTCommonFunctions::CompareDates( dstrFromDate, dstrLastDivDate ) == 
			DSTCommonFunctions::EQUAL )
		{
			return NO_CONDITION;
		}
		else if(	DSTCommonFunctions::CompareDates( dstrFromDate, dstrLastDivDate ) == 
			DSTCommonFunctions::SECOND_EARLIER )
		{
			// issue error: start date can not be earlier than last dividend date + 1
				
			   DSTCommonFunctions::FormatDate(dstrOrgDivDate); // format lastDivDate;
				DString strTemp;
				addIDITagValue( strTemp, I_("DATE"), dstrOrgDivDate );
				ADDCONDITIONFROMFILEIDI( CND::ERR_START_DATE_EARLEAR_THAN_LAST_DIVIDEND_DATE,strTemp );				


		}
		else // start date now earlier than LastDividend date. 
		{
		
			FundList* pFundList =  new FundList( *this );
			if( pFundList->init( dstrFund, dstrClass, dstrFromDate,
											dstrToDate, dstrPrevDatePressed, dstrNextDatePressed ) <= WARNING )
			{		
				BFAbstractCBO* pcbo = NULL;
				BFObjIter iter( *pFundList, idDataGroup,true,BFObjIter::ITERTYPE::NON_DELETED );
				while( !iter.end() )
				{
					DString dstrTransType;
					iter.getObject()->getField(ifds::TransType,dstrTransType,idDataGroup,false );
					dstrTransType.strip().upperCase();
					//ID: income distribution; CD: Capital distribution
					if( dstrTransType == I_("ID" ) || dstrTransType == I_("CD") )
					{
						pcbo = iter.getObject();
						break;
					
					}			
					++iter;	
				}
				if( pcbo )
				{
					DString dstrValueDate;
					pcbo->getField(ifds::ValueAsAt,dstrValueDate,idDataGroup,false );
					DString dstrOrgDate(dstrValueDate);
					DSTCommonFunctions::addDays ( dstrValueDate, dstrValueDate, 1 );// last dividend day + 1;
					if( DSTCommonFunctions::CompareDates( dstrFromDate, dstrValueDate ) != 
							DSTCommonFunctions::EQUAL )
					{
								
						DSTCommonFunctions::FormatDate(dstrOrgDate); // format lastDivDate;
						DString strTemp;
						addIDITagValue( strTemp, I_("DATE"), dstrOrgDate );
						ADDCONDITIONFROMFILEIDI( CND::ERR_START_DATE_DISTRIBUTION_DAY,strTemp );									
					}			
				
				}
/*
				else { // there is no dividend pay out
						 if( DSTCommonFunctions::CompareDates( dstrFromDate, dstrEffectiveDate ) != 
							DSTCommonFunctions::EQUAL )
						 {
							// add condition here.
							
						 }				
				}
*/
			}
		}
	}
   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AccrualsSearchCriteria.cpp-arc  $
// 
//    Rev 1.26   Nov 14 2004 14:24:56   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.25   Oct 27 2004 17:00:34   VADEANUM
// PTS 10034817 - End date error for All Funds mode.
// 
//    Rev 1.24   Apr 22 2004 17:00:20   VADEANUM
// PTS 10025621 - Default Start Datevalidation for Interest Accruals
// 
//    Rev 1.23   Feb 24 2004 09:00:04   VADEANUM
// PTS 10025621 - Default Start Deat for Interest Accruals
// 
//    Rev 1.22   Feb 20 2004 09:40:38   HERNANDO
// PTS10027074 - Modified the comparison in isFundInHoldings.
// 
//    Rev 1.21   Sep 08 2003 09:08:08   YINGBAOL
// add business rules for SSII
// 
//    Rev 1.20   Mar 21 2003 17:55:30   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.19   Jan 14 2003 14:56:36   ZHANGCEL
// Sunc up to R49 1.17 -- PTS ticket 10010316 : Bug fix for the wrong error message
// 
//    Rev 1.18   Dec 19 2002 13:33:20   sanchez
// Modified  IsFundInHOldings(). Support for Whirlwind.  Iterate through the MFAccountHoldingList  to see of the fund class and code passed are in the list.  Don't search for fund by  using fund class as key.
// 
//    Rev 1.17   Nov 19 2002 10:16:02   HSUCHIN
// changed fundnumber from decimal to text
// 
//    Rev 1.16   Oct 09 2002 23:53:56   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.15   Aug 29 2002 12:54:56   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.14   Jul 17 2002 13:44:10   HSUCHIN
// bug fix - DSTCommonFunction::formatToolTipDate is no longer use since getMask fails. 
// 
//    Rev 1.13   Jun 27 2002 13:28:14   YINGBAOL
// small tuning
// 
//    Rev 1.12   22 May 2002 18:26:16   PURDYECH
// BFData Implementation
// 
//    Rev 1.11   04 Apr 2002 17:04:00   HSUCHIN
// bug fix for cross edit firing off when switching between accrual details/totals
// 
//    Rev 1.10   04 Apr 2002 15:05:08   HSUCHIN
// fixed a condition message ERR_START_DATE_MUST_BE_PRIOR_TO_LAST_PROCESSED_DATE
// 
//    Rev 1.9   04 Apr 2002 13:49:42   HSUCHIN
// changed the bus logic to the way start date was calculated.
// 
//    Rev 1.8   03 Apr 2002 12:34:02   HSUCHIN
// bug fix for start date resetting.
// 
//    Rev 1.7   28 Mar 2002 15:33:06   HSUCHIN
// business rule bug fix for start date and date range validation
// 
//    Rev 1.6   12 Mar 2002 15:43:48   HSUCHIN
// added doprevalidateall
// 
//    Rev 1.5   12 Mar 2002 10:26:08   HSUCHIN
// check in for new base objects. 
// 
//    Rev 1.4   07 Mar 2002 16:36:24   HSUCHIN
// bug fix to remove warning for empty fund number
// 
//    Rev 1.3   06 Mar 2002 17:15:24   HSUCHIN
// duplicate validation bug fix
// 
//    Rev 1.2   27 Feb 2002 16:08:08   HSUCHIN
// added new function to setEarliestAllFundDates
// 
//    Rev 1.1   26 Feb 2002 16:53:48   HSUCHIN
// bug fix for undefined earlieststartdate and lastdividentdate
// 
//    Rev 1.0   21 Feb 2002 16:07:00   HSUCHIN
// Initial revision.
*/
