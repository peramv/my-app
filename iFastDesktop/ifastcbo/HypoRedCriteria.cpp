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
//    Copyright 2000 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : HypoRedCriteria.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 10/28/2002
//
// ^CLASS    : HypoRedCriteria
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"


#include "hyporedcriteria.hpp"
#include "hyporedacctholdingslist.hpp"
#include "hyporedcurrencylist.hpp"
#include "hyporedsummarylist.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "taxtyperule.hpp"
#include "supportedproductslist.hpp"

#include <ifastdataimpl\dse_dstc0217_vw.hpp>
#include <ifastdataimpl\dse_dstc0217_req.hpp>

namespace  
{
   const I_CHAR * const CLASSNAME            = I_( "HypoRedCriteria" );
   const I_CHAR * const YES                  = I_( "Y" );
   const I_CHAR * const NO                   = I_( "N" );
   const I_CHAR * const RED_SUMMARY_LIST     = I_( "RedSummaryList" );
   const I_CHAR * const RED_CURRENCY_LIST    = I_( "RedCurrencyList" );
   const I_CHAR * const RED_HOLDINGS_LIST    = I_( "RedHoldingsList" );
   const I_CHAR * const AMOUNT               = I_( "D" );
   const I_CHAR * const UNITS                = I_( "U" );
   const I_CHAR * const CASH_PAYMENT         = I_( "01" );
   const I_CHAR * const BLANK_SUBSTITUTION   = I_( " = ;"); // substitution with only one element with tag = value = " " 
   const I_CHAR * const NET                  = I_( "N" );
   const I_CHAR * const GROSS                = I_( "Y" );
   const I_CHAR * const INVALID_DATE         = I_( "12319999" );

}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId GrossAmtType;
   extern CLASS_IMPORT const BFTextFieldId TRExclRedCodes;
   extern CLASS_IMPORT const BFTextFieldId FullRedCode;
   extern CLASS_IMPORT const BFTextFieldId FullRedGross;
	extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
	extern CLASS_IMPORT const BFTextFieldId RedCodeList;
	extern CLASS_IMPORT const BFDecimalFieldId OverridePrcntFree;
	extern CLASS_IMPORT const BFDateFieldId FirstSettleDate;
   extern CLASS_IMPORT const BFTextFieldId isLSIF;
}

namespace  CND
{
   extern const long ERR_GROSS_FULL_REDEMPTION;
   extern const long ERR_UNIT_NOT_FOR_NET_REDEMPTIONS;
   extern const long ERR_CLOSE_ACCT_MUST_BE_FULL_RED;
   extern const long ERR_NO_HOLDINGS_FOR_DATE;
   extern const long ERR_FIELD_REQUIRED_PLS_ENTER;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//   Field DD Id,             State Flags,       Group Flags 
   { ifds::TradeDate,         BFCBO::NONE,                 0 }, 
   { ifds::FullRed,           BFCBO::NONE,                 0 }, 
   { ifds::RedCode,           BFCBO::NONE,                 0 }, 
   { ifds::GrossOrNet,        BFCBO::NONE,                 0 }, 
   { ifds::AmtType,           BFCBO::NONE,                 0 }, 
   { ifds::AcctLvlDSC,        BFCBO::NONE,                 0 }, 
	//cross edits
	{ ifds::GrossAmtType,      BFCBO::IMMEDIATE_VALIDATION, 0 }, 
   { ifds::FullRedCode,       BFCBO::IMMEDIATE_VALIDATION, 0 }, 
   { ifds::FullRedGross,      BFCBO::IMMEDIATE_VALIDATION, 0 }, 
   { ifds::isLSIF,            BFCBO::NONE,                 0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
   //  Object Label,                  State Flags,      Group Flags 
   { I_( "RedSummaryList" ),          BFCBO::NONE,      0},
   { I_( "RedCurrencyList" ),         BFCBO::NONE,      0},
   { I_( "RedHoldingsList" ),         BFCBO::NONE,      0},
   
};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );

//****************************************************************************
HypoRedCriteria::HypoRedCriteria( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       NUM_OBJECTS, 
							  (const CLASS_OBJECT_INFO *)&classObjectInfo );

   addCrossEdit(ifds::GrossAmtType, ifds::GrossOrNet);
   addCrossEdit(ifds::GrossAmtType, ifds::AmtType); 

	addCrossEdit(ifds::FullRedCode, ifds::FullRed);
   addCrossEdit(ifds::FullRedCode, ifds::RedCode); 

	addCrossEdit(ifds::FullRedGross, ifds::FullRed);
   addCrossEdit(ifds::FullRedGross, ifds::GrossOrNet); 
}

//****************************************************************************
HypoRedCriteria::~HypoRedCriteria()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}   

//****************************************************************************

SEVERITY HypoRedCriteria::init( const BFDataGroupId& idDataGroup, const DString& dstrTrack /*= I_("N")*/,
                         const DString& dstrPageName /*= NULL_STRING*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

	doInitWithDefaultValues( idDataGroup );
	setObjectNew();

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

void HypoRedCriteria::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{

	//rules for default values:
	//1. TradeDate is next cycle date (or current business date) - updateable
	//2. Full redemption is No - updateable
	//3. Redemption code is 01-Cash Payment - updateable
	//4. Gross/Net is Gross - updateable
	//5. Amount type is Amount - updateable
	//6. Account level DSC Fee is No - updateable only for clients for which
	//account level DSC is allowed

	//set Redemption code substitution set
	loadRedCodeSubstList(idDataGroup);

	//TradeDate is next cycle date - is that current business date?
	DString dstrCurrBusDate;
	MgmtCoOptions *pMgmtCoOptions = NULL;
	getMgmtCo().getMgmtCoOptions( pMgmtCoOptions );
   if( pMgmtCoOptions )
      pMgmtCoOptions->getField( ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false );
	if(!dstrCurrBusDate.strip().empty())
		setFieldNoValidate(ifds::TradeDate, dstrCurrBusDate, idDataGroup, false, false, false, false);

	setFieldNoValidate(ifds::FullRed, NO, idDataGroup, false, true, false, false);
	setFieldNoValidate(ifds::RedCode, CASH_PAYMENT, idDataGroup, false, true, false, false);
	setFieldNoValidate(ifds::GrossOrNet, GROSS, idDataGroup, false, true, false, false);
	setFieldNoValidate(ifds::AmtType, AMOUNT, idDataGroup, false, true, false, false);
	setFieldNoValidate(ifds::AcctLvlDSC, NO, idDataGroup, false, true, false, false);

	//rule: if account level DSC Fee is not allowed, set AcctLvlDSC to read-only
	if (!isAcctLvlDSCAllowed())
		setFieldReadOnly(ifds::AcctLvlDSC, idDataGroup, true);


   SupportedProductsList *pSupportedProductsList = NULL;

   if( getMgmtCo().getSupportedProductsList (pSupportedProductsList) <= WARNING && pSupportedProductsList )
   {
      if ( pSupportedProductsList ->isLSIFProductActive() )
	   {
         setFieldNoValidate(ifds::isLSIF, YES, idDataGroup, false, true, false, false);
	   }
      else
      {  
         setFieldNoValidate(ifds::isLSIF, NO, idDataGroup, false, true, false, false);
      }

   }


}
//****************************************************************************

SEVERITY HypoRedCriteria::getHypoRedSummaryList( HypoRedSummaryList *&pRedSummaryList, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getRedSummaryList" ) );
   //check cbobase to see if we've already built it
   //otherwise, create and store with base
   pRedSummaryList = dynamic_cast<HypoRedSummaryList*>(BFCBO::getObject( RED_SUMMARY_LIST, idDataGroup ) );

   if( !pRedSummaryList || pRedSummaryList->needsRefresh(idDataGroup) )
   {
      pRedSummaryList = new HypoRedSummaryList( *this );
		if( pRedSummaryList->init(idDataGroup) <= WARNING )
         setObject( pRedSummaryList, RED_SUMMARY_LIST, OBJ_ACTIVITY_NONE, idDataGroup );
      else
      {
         delete pRedSummaryList;
         pRedSummaryList = NULL;
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************

SEVERITY HypoRedCriteria::getHypoRedAcctHoldingsList( HypoRedAcctHoldingsList *&pHypoRedAcctHoldingsList, 
                                   const BFDataGroupId& idDataGroup, bool bCreate /*= true*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getHypoRedAcctHoldingsList" ) );
	//check cbobase to see if we've already built it
   //if not already created or if it needs to be refreshed, create and store with base
   pHypoRedAcctHoldingsList = dynamic_cast<HypoRedAcctHoldingsList*>(BFCBO::getObject( RED_HOLDINGS_LIST, idDataGroup ) );

   if( bCreate && (!pHypoRedAcctHoldingsList || pHypoRedAcctHoldingsList->needsRefresh(idDataGroup)))
   {
      pHypoRedAcctHoldingsList = new HypoRedAcctHoldingsList( *this );
      if (pHypoRedAcctHoldingsList->init(idDataGroup) <= WARNING)
         setObject( pHypoRedAcctHoldingsList, RED_HOLDINGS_LIST, OBJ_ACTIVITY_NONE, idDataGroup );
      else
      {
         delete pHypoRedAcctHoldingsList;
         pHypoRedAcctHoldingsList = NULL;
      }
   }
   
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY HypoRedCriteria::getCurrencyList( HypoRedCurrencyList *&pHypoRedCurrencyList, 
														const BFDataGroupId& idDataGroup, bool bNewList /*= false*/)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getCurrencyList" ) );

	//check cbobase to see if we've already built it
   //otherwise, create and store with base
   pHypoRedCurrencyList = dynamic_cast<HypoRedCurrencyList*>(BFCBO::getObject( RED_CURRENCY_LIST, idDataGroup ) );

   if( !pHypoRedCurrencyList || bNewList)//if not created or we want to refresh
   {
      pHypoRedCurrencyList = new HypoRedCurrencyList( *this );
      if (pHypoRedCurrencyList->init(idDataGroup) <= WARNING)
         setObject( pHypoRedCurrencyList, RED_CURRENCY_LIST, OBJ_ACTIVITY_NONE, idDataGroup );
      else
      {
         delete pHypoRedCurrencyList;
         pHypoRedCurrencyList = NULL;
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

////////////////////////////////VALIDATIONS////////////////////////////////////

//******************************************************************************

SEVERITY HypoRedCriteria::doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

   if( idField == ifds::TradeDate )
      validateTradeDate(strValue, idDataGroup);
	else if ( idField == ifds::FullRedGross )
		validateGrossFullRedemption(idDataGroup);
	else if ( idField == ifds::GrossAmtType )
		validateGrossAmtType(idDataGroup);
	else if ( idField == ifds::FullRedCode )
		validateFullRedCode(idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY HypoRedCriteria::validateTradeDate(const DString& strValue, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateTradeDate" ) );

	//rule: should be a valid value
	DString strTemp(strValue);
	if (strTemp.strip().empty() || strTemp == INVALID_DATE)
	{
		ADDCONDITIONFROMFILE( CND::ERR_FIELD_REQUIRED_PLS_ENTER );
		return(GETCURRENTHIGHESTSEVERITY());  
	}

	//rule: Trade date must be greater or equal to the first settled trade date in the account
	DString strFirstSettledDate;
	getParent()->getField(ifds::FirstSettleDate, strFirstSettledDate, idDataGroup, false);
	if (DSTCommonFunctions::CompareDates(strValue, strFirstSettledDate) 
		== DSTCommonFunctions::FIRST_EARLIER)
	{
		ADDCONDITIONFROMFILE( CND::ERR_NO_HOLDINGS_FOR_DATE );
	}

   return(GETCURRENTHIGHESTSEVERITY());  
}

//******************************************************************************

SEVERITY HypoRedCriteria::validateGrossFullRedemption( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateGrossFullRedemption" ) );

	//rule: Full redemptions must be gross
	DString strFullRed, strGrossOrNet;
	getField(ifds::FullRed, strFullRed, idDataGroup, false);
	getField(ifds::GrossOrNet, strGrossOrNet, idDataGroup, false);
	if (strFullRed.strip() == YES && strGrossOrNet.strip() == NET)
	{
		ADDCONDITIONFROMFILE( CND::ERR_GROSS_FULL_REDEMPTION );
	}

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY HypoRedCriteria::validateGrossAmtType( const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateGrossAmtType" ) );

	//rule: Unit amount type is not permitted for net redemptions
	DString strAmtType, strGrossOrNet;
	getField(ifds::AmtType, strAmtType, idDataGroup, false);
	getField(ifds::GrossOrNet, strGrossOrNet, idDataGroup, false);
	if (strAmtType.strip() == UNITS && strGrossOrNet.strip() == NET)
	{
		ADDCONDITIONFROMFILE( CND::ERR_UNIT_NOT_FOR_NET_REDEMPTIONS );
	}

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY HypoRedCriteria::validateFullRedCode( const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFullRedCode" ) );

	//rule: Full redemption field should be Yes whenever using a redemption code
	//which is listed under the CloseAcctCode generic control
	DString strFullRed, 
      strRedCode,
      trexclRCList;
	
   getField(ifds::RedCode, strRedCode, idDataGroup, false);
   getWorkSession().getOption ( ifds::TRExclRedCodes, 
                                trexclRCList, 
                                idDataGroup,
                                false
                              );
  if (DSTCommonFunctions::codeInList (strRedCode, trexclRCList))
  {
	   getField(ifds::FullRed, strFullRed, idDataGroup, false);
	   if (strFullRed.strip() == NO)
	   {
		   ADDCONDITIONFROMFILE( CND::ERR_CLOSE_ACCT_MUST_BE_FULL_RED );
	   }
  }
  return GETCURRENTHIGHESTSEVERITY();

}
////////////////////////////////END VALIDATIONS////////////////////////////////
//******************************************************************************
////////////////////////////////RELATED CHANGES////////////////////////////////

//******************************************************************************

SEVERITY HypoRedCriteria::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

	if ( idField == ifds::FullRedCode )
		fullRedCodeChanges(idDataGroup);
	else if ( idField == ifds::FullRed )
		fullRedChanges(idDataGroup);
	else if ( idField == ifds::RedCode )
		redCodeChanges(idDataGroup);

   if ( idField == ifds::FullRedCode  ||
        idField == ifds::GrossAmtType ||
        idField == ifds::FullRedGross )
   {
      setUpdatedFlag(idField, idDataGroup, false);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
SEVERITY HypoRedCriteria::fullRedCodeChanges(const BFDataGroupId& idDataGroup)
{
   MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

	//rules:
	//0. The following rules only apply for clients with Account Level DSC fees
	//1. For Full redemption and close account RedCode, set AcctLvlDSC to Yes and readonly
	//2. For Full redemption and NOT close account RedCode, set AcctLvlDSC to No and readonly
	//3. For NOT Full redemption and close account RedCode, set AcctLvlDSC to No and updateable
	//4. For NOT Full redemption and NOT close account RedCode, set AcctLvlDSC to No, and updateable

	if (!isAcctLvlDSCAllowed())
		return(GETCURRENTHIGHESTSEVERITY());

	DString strFullRed, 
      strRedCode,
      trexclRCList;

   getField(ifds::FullRed, strFullRed, idDataGroup, false);
	getField(ifds::RedCode, strRedCode, idDataGroup, false);
   getWorkSession().getOption ( ifds::TRExclRedCodes, 
                                trexclRCList, 
                                idDataGroup,
                                false
                              );
	bool bFullRed = strFullRed.strip() == YES;
   bool bCloseAcct = DSTCommonFunctions::codeInList (strRedCode, trexclRCList);

	if (bFullRed)
	{
		if (bCloseAcct) setField(ifds::AcctLvlDSC, YES, idDataGroup, false);
		else setField(ifds::AcctLvlDSC, NO, idDataGroup, false);

		setFieldReadOnly(ifds::AcctLvlDSC, idDataGroup, true);
	}
	else
	{
		setField(ifds::AcctLvlDSC, NO, idDataGroup, false);
		setFieldReadOnly(ifds::AcctLvlDSC, idDataGroup, false);
	}

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY HypoRedCriteria::fullRedChanges(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "fullRedChanges" ) );

	//rules: according to ESS, when Full redemption is set to Yes, 
	//have to set GrossOrNet to No (actually it should be set to Yes)
	//and set Amount type to Units
	/*it has been decided to be removed
	DString strFullRed;
	getField(ifds::FullRed, strFullRed, idDataGroup, false);
	if (strFullRed.strip() == YES)
	{
		setField(ifds::GrossOrNet, GROSS, idDataGroup, false);
		setFieldReadOnly(ifds::GrossOrNet, idDataGroup, true);

		setField(ifds::AmtType, UNITS, idDataGroup, false);
		setFieldReadOnly(ifds::AmtType, idDataGroup, true);
	}
	else
	{
		setFieldReadOnly(ifds::GrossOrNet, idDataGroup, false);
		setFieldReadOnly(ifds::AmtType, idDataGroup, false);
	}*/

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY HypoRedCriteria::redCodeChanges(const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "redCodeChanges" ) );

	//rules: according to ESS, when a close account redemption is indicated, 
	//have to set Full redemption to Yes
	//and set Amount type to Units

	/*it has been decided to be removed
	DString strRedCode;
	getField(ifds::RedCode, strRedCode, idDataGroup, false);

	bool bCloseAcct = getWorkSession().getMgmtCoOptions()->closeAcctRedCode( 
		strRedCode.strip(), idDataGroup );

	if (bCloseAcct)
	{
		setField(ifds::FullRed, YES, idDataGroup, false);
		setFieldReadOnly(ifds::FullRed, idDataGroup, true);
	}
	else
		setFieldReadOnly(ifds::FullRed, idDataGroup, false);
	*/
   return(GETCURRENTHIGHESTSEVERITY());
}

////////////////////////////////END RELATED CHANGES////////////////////////////////
//******************************************************************************
SEVERITY HypoRedCriteria::loadRedCodeSubstList( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "loadDepRedCodeSubstList" ) );

   DString strCodesList;
   bool bLoadedSubstList(false);
   bool bStripLeadingZeros(false);
   bool bAddCodeToDescription(true);

   MFAccount *pMFAccount=NULL;
	pMFAccount = dynamic_cast<MFAccount*>(getParent());
   if( !pMFAccount)
		return(GETCURRENTHIGHESTSEVERITY());

   TaxTypeRule* pTaxTypeRule = NULL;
   if( pMFAccount->getTaxTypeRule ( pTaxTypeRule, idDataGroup ) <= WARNING && pTaxTypeRule)
   {
      pTaxTypeRule->getField( ifds::RedCodeList, strCodesList, idDataGroup );
      if( strCodesList.strip().empty() )
      {
         assert(0);  //codes list is empty or different field
         bLoadedSubstList = false;
      }
      else
      {
         bLoadedSubstList = loadSubstitutionList(  ifds::RedCode,
                                                   idDataGroup, 
                                                   strCodesList, 
                                                   bStripLeadingZeros, 
                                                   bAddCodeToDescription );
      }

      if( !bLoadedSubstList )
      {
         setFieldAllSubstituteValues( ifds::RedCode, idDataGroup, BLANK_SUBSTITUTION );
         setFieldNoValidate( ifds::RedCode, NULL_STRING, idDataGroup, false );
      }

   }//if( pTaxTypeRule != NULL ...

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

bool HypoRedCriteria::isValidForInquiry(const BFDataGroupId& idDataGroup)
{
   SEVERITY sev = NO_SEVERITY, sevMax = NO_SEVERITY;

	//fields
	sev = getErrorState(ifds::TradeDate, idDataGroup);
	if (sev > sevMax) sevMax = sev;

	sev = getErrorState(ifds::FullRed, idDataGroup);
	if (sev > sevMax) sevMax = sev;

	sev = getErrorState(ifds::RedCode, idDataGroup);
	if (sev > sevMax) sevMax = sev;

	sev = getErrorState(ifds::GrossOrNet, idDataGroup);
	if (sev > sevMax) sevMax = sev;

	sev = getErrorState(ifds::AmtType, idDataGroup);
	if (sev > sevMax) sevMax = sev;

	//cross edits 
	sev = getErrorState(ifds::FullRedGross, idDataGroup);
	if (sev > sevMax) sevMax = sev;

	sev = getErrorState(ifds::FullRedCode, idDataGroup);
	if (sev > sevMax) sevMax = sev;

	sev = getErrorState(ifds::GrossAmtType, idDataGroup);
	if (sev > sevMax) sevMax = sev;

	return (sevMax <= WARNING);
}
//******************************************************************************

bool HypoRedCriteria::isAcctLvlDSCAllowed()
{
	//rule : if OverridePrcntFree generic control is Type 1, AcctLvlDSC is allowed, otherwise no
	DString strOverridePercentFree;
   getWorkSession().getOption( ifds::OverridePrcntFree, strOverridePercentFree, BF::HOST, false);
	if (strOverridePercentFree.strip() == I_("1"))
		return true;

	return false;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/HypoRedCriteria.cpp-arc  $
// 
//    Rev 1.6   Nov 27 2004 19:44:48   popescu
// PET 1117/56, removed two validation methods from MgmtCoOptions. Either we have all of them here or none. Moved the methods to the CBO's that require 'em.
// 
//    Rev 1.5   Nov 14 2004 14:44:32   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.4   May 10 2004 13:44:54   AGUILAAM
// PET985_FN01-1: LSIF HypoCalc enhancement - added clawback fields
// 
//    Rev 1.3   Mar 21 2003 18:14:02   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.2   Feb 25 2003 14:40:32   PURDYECH
// Remove CLASS_IMPORT from Condition declaration as it causes a Linker warning.
// 
//    Rev 1.1   Nov 25 2002 09:38:20   KOVACSRO
// Added implementation.
// 
//    Rev 1.0   Oct 29 2002 10:50:50   KOVACSRO
// Initial Revision
// 
 
*/


