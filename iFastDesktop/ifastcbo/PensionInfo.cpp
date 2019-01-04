//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 by DST Systems, Inc.
//
//*****************************************************************************
//
// ^FILE   : PensionInfo.cpp
// ^AUTHOR : 
// ^DATE   : May 15, 2002
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : PensionInfo
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************

#include "stdafx.h"
#include <ifastdataimpl\dse_dstc0202_req.hpp>
#include <ifastdataimpl\dse_dstc0202_vw.hpp>
#include "dstcworksession.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "pensioninfo.hpp"
#include "taxtyperule.hpp"
#include "taxtyperulelist.hpp"

//******************************************************************************

namespace CND
{
   extern const long ERR_PENSION_SEX_PRCNT_NOT_ADD_TO_100;
   extern const long ERR_PENSION_TAX_RULE_NOT_SETUP;
   extern const long WARN_PENSION_AGE_LESS_THAN_REQUIRED;
   extern const long ERR_PENSION_UNISEX_PERCENT_MUST_EQ_100;
   extern const long ERR_PENSION_INVALID_PERCENT;   
   extern const long ERR_PENSION_DISTINCTSEX_PERCENT_MUST_EQ_100;
}

namespace ifds
{
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFIntegerFieldId MinAge;
   extern CLASS_IMPORT const BFDecimalFieldId AccountBalance;
   extern CLASS_IMPORT const BFTextFieldId SexDistinct;
   extern CLASS_IMPORT const BFTextFieldId TaxTypeRules;
   extern CLASS_IMPORT const BFTextFieldId Unisex;
   extern CLASS_IMPORT const BFTextFieldId TaxType;
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest PENSION_INFO;   
}

namespace
{
   const I_CHAR * const CLASSNAME               = I_( "PensionInfo" );
   const I_CHAR * const HUNDRED                 = I_( "100" );
   const I_CHAR * const NO                      = I_( "N" );
   const I_CHAR * const YES                     = I_( "Y" );
   const I_CHAR * const ZERO                    = I_( "0" );   
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//   Field DD Id,              State Flags,             Group Flags 
   { ifds::EffectiveDate,  BFCBO::REQUIRED, 0 }, 
   { ifds::MinWithAge,     BFCBO::NONE, 0 }, 
   { ifds::PenSourceLine1, BFCBO::NONE, 0 }, 
   { ifds::PenSourceLine2, BFCBO::NONE, 0 }, 
   { ifds::PenSourceLine3, BFCBO::NONE, 0 }, 
   { ifds::UniSexPer,      BFCBO::NONE, 0 }, 
   { ifds::SexDistinctPer, BFCBO::NONE, 0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
// Constructor
// @param   BFBase - pointer to the parent BFBase
//******************************************************************************

PensionInfo::PensionInfo( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent ),
_pMFAccount ( dynamic_cast <MFAccount*> (getParent()) )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//******************************************************************************
// Destructor
//******************************************************************************

PensionInfo::~PensionInfo()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//*****************************************************************************
// Initializes Pension Info cbo.
// @param   DString dstrTrack - Account Number used to get Account Holdings
//          DString dstrPageName - Interest, MF, MFR are the 3 different types.
//          const BFDataGroupId& idDataGroup - current datagroup.
// @returns void.
//*****************************************************************************

SEVERITY PensionInfo::init( const BFDataGroupId& idDataGroup, const DString& dstrTrack, const DString& dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );     

   SEVERITY sev = NO_CONDITION;
   BFData requestData( ifds::DSTC0202_REQ );   
   DString dstrAccountNum, dstrMgmtCoId, dstrJurisdiction;   
   _pMFAccount->getField ( ifds::AccountNum, dstrAccountNum, idDataGroup );
   _pMFAccount->getField ( ifds::PensionJuris, dstrJurisdiction, idDataGroup );         
   requestData.setElementValue( ifds::AccountNum,  dstrAccountNum  );
   requestData.setElementValue( ifds::CompanyId, getMgmtCoId( dstrMgmtCoId ) );
   requestData.setElementValue( ifds::Track, dstrTrack );
   requestData.setElementValue( ifds::Activity, dstrPageName );
   const DSTCSecurity* security = dynamic_cast<const DSTCSecurity *> ( getSecurity() );
   ReceiveData (DSTC_REQUEST::PENSION_INFO, requestData, ifds::DSTC0202_VW, DSTCRequestor( security, false ) );
   refreshJurisdiction ( idDataGroup );

   /*
   DString dstrUnisex, dstrSexDistinct;   

// We ask MFAccount for the tax rules. From the TaxTypeRule CBO retried from MFAccount we can get a list of
// of Tax Limits for each jurisdiction.  Based on the jurisdiction defined in MFAccount (the current account)
// we can get the limits/default for the particular juridiction from TaxTypeRule CBO.

   TaxTypeRule *pTaxTypeRule;
   _pMFAccount->getTaxTypeRule( pTaxTypeRule, idDataGroup );   
   dstrSexDistinct = pTaxTypeRule->getJurisLimitField ( ifds::SexDistinct, dstrJurisdiction, idDataGroup );
   dstrUnisex = pTaxTypeRule->getJurisLimitField ( ifds::Unisex, dstrJurisdiction, idDataGroup );   

   // If either one of the two flags is set to No, we don't need user input anymore.
   // The data will be auto corrected.

   if (( dstrUnisex == NO ) || ( dstrSexDistinct == NO ) ) {
      setFieldReadOnly ( ifds::UniSexPer, idDataGroup, dstrUnisex == NO );
      setFieldReadOnly ( ifds::SexDistinctPer, idDataGroup, dstrSexDistinct == NO );
   } else {
      setFieldReadOnly ( ifds::UniSexPer, idDataGroup, dstrUnisex == NO );
      setFieldReadOnly ( ifds::SexDistinctPer, idDataGroup, dstrSexDistinct == NO );
//   }

   // If Unisex is NO then set the UniSexPer to 0 and SexDistinctPer to 100.
   // If SexDistinct is NO then set the UniSexPer to 100 and SexDistinctPer to 0.

   if (( dstrUnisex == NO ) && (dstrSexDistinct == YES )) {
      setFieldNoValidate ( ifds::UniSexPer, ZERO, idDataGroup, true, true, true );
      setFieldNoValidate ( ifds::SexDistinctPer, HUNDRED, idDataGroup, true, true, true );      
   } else if (( dstrUnisex == YES ) && ( dstrSexDistinct == NO )) {
      setFieldNoValidate ( ifds::UniSexPer, HUNDRED, idDataGroup, true, true, true );
      setFieldNoValidate ( ifds::SexDistinctPer, ZERO, idDataGroup, true, true, true );
   }
*/   
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
// Field validation
//    MinWithAge - must less than MinAge from MF Account.
//    UniSexPer - must be in between 0 and 100.
//    SexDistinctPer - must be in between 0 and 100.
// @param   const BFFieldId& idField - field id.
//          DString& strValue - value of the field
//          const BFDataGroupId& idDataGroup - data group id.
//******************************************************************************

SEVERITY PensionInfo::doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );
   if( idField == ifds::MinWithAge )
   {
      /*DString dstrMinAge;
      long lMinAge, lMinWithAge;
      _pTaxTypeRule->getField ( ifds::MinAge, dstrMinAge, idDataGroup );
      lMinAge = DSTCommonFunctions::convertToDouble ( dstrMinAge );
      lMinWithAge = DSTCommonFunctions::convertToDouble ( strValue );
      if ( lMinWithAge < lMinAge )
         // msg - Minimum withdrawal age is less than required for the Tax Type and Pension Jurisdiction.
         ADDCONDITIONFROMFILE( CND::WARN_PENSION_AGE_LESS_THAN_REQUIRED );
         */

      // Let TaxTypeRule do the min age validation.
      DString dstrJurisdiction;
      TaxTypeRule *pTaxTypeRule;
      _pMFAccount->getTaxTypeRule( pTaxTypeRule, idDataGroup );   
      _pMFAccount->getField ( ifds::PensionJuris, dstrJurisdiction, idDataGroup );
      if( pTaxTypeRule && !pTaxTypeRule->isValidMinimumAgeForWithdrawl( strValue, dstrJurisdiction, idDataGroup ) )
         ADDCONDITIONFROMFILE( CND::WARN_PENSION_AGE_LESS_THAN_REQUIRED );
   }
   else if( idField == ifds::UniSexPer )
   {
      BFProperties * pBFProperties = NULL;
      pBFProperties = getFieldProperties( idField, idDataGroup );      
      if( pBFProperties && !pBFProperties->isReadOnly() )
      {
         long lUniSexPer;
         DString dstrSexDistinct, dstrJurisdiction;
         TaxTypeRule *pTaxTypeRule;
         _pMFAccount->getTaxTypeRule( pTaxTypeRule, idDataGroup );   
         _pMFAccount->getField ( ifds::PensionJuris, dstrJurisdiction, idDataGroup );
         lUniSexPer = static_cast<long>(DSTCommonFunctions::convertToDouble ( strValue ));
		 if( pTaxTypeRule )
		 {
			dstrSexDistinct = pTaxTypeRule->getJurisLimitField ( ifds::SexDistinct, dstrJurisdiction, idDataGroup );
		 }
         if( ( dstrSexDistinct == NO ) && ( lUniSexPer != 100 ) )
         {
            // msg - Unisex Percent must be 100%. Tax Jurisdiction never allowed Sex Distinct.
            ADDCONDITIONFROMFILE ( CND::ERR_PENSION_UNISEX_PERCENT_MUST_EQ_100 );
         }
         else if( ( lUniSexPer < 0 ) || ( lUniSexPer > 100 ) )
         {
            // msg - Invalid Percentage.
            ADDCONDITIONFROMFILE ( CND::ERR_PENSION_INVALID_PERCENT );
         }
      }
   }
   else if( idField == ifds::SexDistinctPer )
   {
      BFProperties * pBFProperties = NULL;
      pBFProperties = getFieldProperties( idField, idDataGroup );      
      if( pBFProperties && !pBFProperties->isReadOnly() )
      {
         long lSexDistinctPer;
         DString dstrUnisex, dstrJurisdiction;
         lSexDistinctPer = static_cast<long>(DSTCommonFunctions::convertToDouble ( strValue ));
         TaxTypeRule *pTaxTypeRule;
         _pMFAccount->getTaxTypeRule( pTaxTypeRule, idDataGroup );   
         _pMFAccount->getField ( ifds::PensionJuris, dstrJurisdiction, idDataGroup );
		 if( pTaxTypeRule )
		 {
			dstrUnisex = pTaxTypeRule->getJurisLimitField ( ifds::Unisex, dstrJurisdiction, idDataGroup );
		 }
         if( ( dstrUnisex == NO ) && ( lSexDistinctPer != 100 ) )
         {
            // msg - Sex Distinct Percent must be 100%. Tax Jurisdiction never allowed Unisex.
            ADDCONDITIONFROMFILE ( CND::ERR_PENSION_DISTINCTSEX_PERCENT_MUST_EQ_100 );
         }
         else if( ( lSexDistinctPer < 0 ) || ( lSexDistinctPer > 100 ) )
         {
            // msg - Invalid Percentage.
            ADDCONDITIONFROMFILE ( CND::ERR_PENSION_INVALID_PERCENT );
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
// Do apply related changes
//    UniSexPer - will recalculated the MktValueSexDistinct based on the new
//                UniSexPer value.
// @param   const BFFieldId& idField - field id.
//          const BFDataGroupId& idDataGroup - data group id.
// @returns SEVERITY.
//******************************************************************************

SEVERITY PensionInfo::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
// Initializes new pension information with default values.
// @param   const BFDataGroupId& idDataGroup - data group id.
// returns  void.
//******************************************************************************

void PensionInfo::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
   DString dstrMinWithAge, dstrUnisex, dstrSexDistinct, dstrCurrBusDate, dstrJurisdiction;
   TaxTypeRule *pTaxTypeRule;
   _pMFAccount->getTaxTypeRule( pTaxTypeRule, idDataGroup );   
   _pMFAccount->getField ( ifds::PensionJuris, dstrJurisdiction, idDataGroup );
   if( pTaxTypeRule )
   {
		dstrSexDistinct = pTaxTypeRule->getJurisLimitField ( ifds::SexDistinct, dstrJurisdiction, idDataGroup );
		dstrUnisex = pTaxTypeRule->getJurisLimitField ( ifds::Unisex, dstrJurisdiction, idDataGroup );
		dstrMinWithAge = pTaxTypeRule->getJurisLimitField ( ifds::MinWithAge, dstrJurisdiction, idDataGroup );
   }

   getWorkSession().getMgmtCoOptions()->getField( ifds::CurrBusDate, dstrCurrBusDate, BF::HOST, false );

   setFieldNoValidate ( ifds::MinWithAge, dstrMinWithAge, idDataGroup );
   setFieldNoValidate ( ifds::EffectiveDate, dstrCurrBusDate, idDataGroup, false );

   if( dstrUnisex == YES )
   {
      setFieldNoValidate ( ifds::UniSexPer, HUNDRED, idDataGroup, true, true, true );
      setFieldNoValidate ( ifds::SexDistinctPer, ZERO, idDataGroup, true, true, true );
   }
   else
   {
      setFieldNoValidate ( ifds::UniSexPer, ZERO, idDataGroup, true, true, true );
      setFieldNoValidate ( ifds::SexDistinctPer, HUNDRED, idDataGroup, true, true, true );
      setFieldReadOnly ( ifds::UniSexPer, idDataGroup, true );
   }

   if( dstrSexDistinct == NO )
      setFieldReadOnly ( ifds::SexDistinctPer, idDataGroup, true );
}

//******************************************************************************
// validates all of Pension information
//    UniSexPer + SexDistinctPer must equal 100%
// @param   const BFDataGroupId& idDataGroup - data group id.
//          long lValidateGroup - validation group id.
// @returns SEVERITY.
//******************************************************************************

SEVERITY PensionInfo::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   DString dstrUniSexPer, dstrSexDistinctPer, dstrPensionJuris;
   double dUniSexPer, dSexDistinctPer;
   TaxTypeRule *pTaxTypeRule;
   // Get the Pension Jurisdiction and check to see if Tax Rules have been defined.
   // msg - Tax Type rules have not yet been set up.
   _pMFAccount->getField ( ifds::PensionJuris, dstrPensionJuris, idDataGroup );
   _pMFAccount->getTaxTypeRule( pTaxTypeRule, idDataGroup );
   if( pTaxTypeRule && !pTaxTypeRule->isValidPensionJurisdiction( dstrPensionJuris, idDataGroup ) )
   {
      ADDCONDITIONFROMFILE ( CND::ERR_PENSION_TAX_RULE_NOT_SETUP );
      return(GETCURRENTHIGHESTSEVERITY());
   }

   // Sum of UniSexPer and SexDistinctPer must add up to 100.
   // msg - Unisex/Sex Distinct Percents must add up to 100.
   getField ( ifds::UniSexPer, dstrUniSexPer, idDataGroup );
   getField ( ifds::SexDistinctPer, dstrSexDistinctPer, idDataGroup );
   dUniSexPer = DSTCommonFunctions::convertToDouble ( dstrUniSexPer );
   dSexDistinctPer = DSTCommonFunctions::convertToDouble ( dstrSexDistinctPer );
   if( dUniSexPer + dSexDistinctPer != 100 )
      ADDCONDITIONFROMFILE ( CND::ERR_PENSION_SEX_PRCNT_NOT_ADD_TO_100 );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
// Calculates the Sex Distinct Portion of Current Market Value for the Pension.
//    SettleValue (Account Holdings) * SexDistinctPer / 100.
// @param   const BFDataGroupId& idDataGroup - data group id.
// @returns DString - Portion of Current Market Value formatted to 2 decimals.
//******************************************************************************

DString PensionInfo::getSexDistinctCurrentMarketValue ( const BFDataGroupId& idDataGroup )
{
   DString dstrSettledValue, dstrSexDistinctPer;
   double dSettledValue, dCurrentMarketValue, dSexDistinctPer;      
   _pMFAccount->getField (ifds::AccountBalance, dstrSettledValue, idDataGroup );
   getField ( ifds::SexDistinctPer, dstrSexDistinctPer, idDataGroup );
   dSettledValue = DSTCommonFunctions::convertToDouble ( dstrSettledValue );
   dSexDistinctPer = DSTCommonFunctions::convertToDouble ( dstrSexDistinctPer );   
   dCurrentMarketValue = dSettledValue * dSexDistinctPer / 100;
   return(DSTCommonFunctions::doubleToDString ( ifds::AccountBalance, dCurrentMarketValue ));
}

//******************************************************************************
// Initializes new Pension Information.
// @param const BFDataGroupId& idDataGroup - data group id.
// @returns void.
//******************************************************************************

void PensionInfo::initNew ( const BFDataGroupId& idDataGroup ) 
{
   setObjectNew();
   doInitWithDefaultValues ( idDataGroup );   
}

//******************************************************************************
// This method will change the SexDistinct and UniSexPer accordingly to the 
// Jurisdiction set in MFAccount.
// @param const BFDataGroupId& idDataGroup - data group id.
// @returns void.
//******************************************************************************

void PensionInfo::refreshJurisdiction ( const BFDataGroupId& idDataGroup ) 
{

   DString dstrSexDistinct, dstrUnisex, dstrMinWithAge, dstrJurisdiction;

// We ask MFAccount for the tax rules. From the TaxTypeRule CBO retried from MFAccount we can get a list of
// of Tax Limits for each jurisdiction.  Based on the jurisdiction defined in MFAccount (the current account)
// we can get the limits/default for the particular juridiction from TaxTypeRule CBO.

   TaxTypeRule *pTaxTypeRule;
   _pMFAccount->getTaxTypeRule( pTaxTypeRule, idDataGroup );   
   _pMFAccount->getField ( ifds::PensionJuris, dstrJurisdiction, idDataGroup );
   if( pTaxTypeRule )
   {
		dstrSexDistinct = pTaxTypeRule->getJurisLimitField ( ifds::SexDistinct, dstrJurisdiction, idDataGroup );
		dstrUnisex = pTaxTypeRule->getJurisLimitField ( ifds::Unisex, dstrJurisdiction, idDataGroup );   
		dstrMinWithAge = pTaxTypeRule->getJurisLimitField ( ifds::MinWithAge, dstrJurisdiction, idDataGroup );
   }

   // If either one of the two flags is set to No, we don't need user input anymore.
   // The data will be auto corrected.

   setFieldReadOnly ( ifds::UniSexPer, idDataGroup, dstrUnisex == NO );
   setFieldReadOnly ( ifds::SexDistinctPer, idDataGroup, dstrSexDistinct == NO );

   // If Unisex is NO then set the UniSexPer to 0 and SexDistinctPer to 100.
   // If SexDistinct is NO then set the UniSexPer to 100 and SexDistinctPer to 0.

   if( ( dstrUnisex == NO ) && (dstrSexDistinct == YES ) )
   {
      setFieldNoValidate ( ifds::UniSexPer, ZERO, idDataGroup, true, true, true );
      setFieldNoValidate ( ifds::SexDistinctPer, HUNDRED, idDataGroup, true, true, true );      
   }
   else if( ( dstrUnisex == YES ) && ( dstrSexDistinct == NO ) )
   {
      setFieldNoValidate ( ifds::UniSexPer, HUNDRED, idDataGroup, true, true, true );
      setFieldNoValidate ( ifds::SexDistinctPer, ZERO, idDataGroup, true, true, true );
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/PensionInfo.cpp-arc  $
// 
//    Rev 1.10   Jun 16 2011 12:01:14   wutipong
// IN#2530747 - Major Alert on view #203. Make Effective Date become required.
// 
//    Rev 1.9   15 Apr 2008 12:09:48   kovacsro
// PET2255 FN47 - New Ontario LIF
// 
//    Rev 1.8   Nov 14 2004 14:51:06   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.7   Mar 21 2003 18:20:08   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.6   Oct 09 2002 23:54:50   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.5   Aug 29 2002 12:56:24   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.4   Aug 09 2002 16:13:42   HSUCHIN
// added refreshJurisdiction method
// 
//    Rev 1.3   Jul 09 2002 10:24:20   HSUCHIN
// bug fix for Nasu where SexDistinct and Unisex is not defined on the account level yet.  It is now using TaxJurisLimitList for these defaults.
// 
//    Rev 1.2   Jul 02 2002 13:58:50   HSUCHIN
// bug fix for SexDistinct/Unisex flags set to NO on init.  Auto corrected SexDistinctPer/UnisexPer values based on initial value of flags.
// 
//    Rev 1.1   Jun 02 2002 18:17:36   HSUCHIN
// changed getSexDistinctCurrentMarketValue to use Account Balance from MF Account
// 
//    Rev 1.0   May 30 2002 16:44:22   HSUCHIN
// Initial revision.
*/