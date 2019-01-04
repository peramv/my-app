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
// ^FILE   : HypoRedAcctHolding.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 10/28/2002
//
// ^CLASS    : HypoRedAcctHolding
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "certificatelist.hpp"
#include "hyporedacctholding.hpp"
#include "funddetail.hpp"
#include "funddetaillist.hpp"
#include "fundmaster.hpp"
#include "fundmasterlist.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"


#include <ifastdataimpl\dse_dstc0020_vwrepeat_record.hpp>

namespace  
{
   const I_CHAR * const CLASSNAME            = I_( "HypoRedAcctHolding" );
   const double dSmallValue                  = .0000000001;
   const I_CHAR * const AMOUNT               = I_( "D" );
   const I_CHAR * const UNITS                = I_( "U" );
   const I_CHAR * const MONEY_MARKET         = I_( "I" );
	const I_CHAR * const YES                  = I_( "Y" );
   const I_CHAR * const NO                   = I_( "N" );
}

namespace CND
{
   extern const long ERR_AMOUNT_MUST_BE_GREATER_THAN_ZERO;
   extern const long ERR_AMOUNT_GREATER_THAN_HOLDING;
   extern const long ERR_WARN_FULL_MONEY_MARKET;
   extern const long ERR_WARN_CERT_UNITS_EXISTS;
}

namespace ifds
{
   extern CLASS_IMPORT const BFDecimalFieldId Amount;
   extern CLASS_IMPORT const BFTextFieldId FundName;
   extern CLASS_IMPORT const BFTextFieldId ElongName1;
   extern CLASS_IMPORT const BFTextFieldId AmtType;
   extern CLASS_IMPORT const BFDecimalFieldId USDollar;
	extern CLASS_IMPORT const BFDecimalFieldId UnitsPrecision;
	extern CLASS_IMPORT const BFTextFieldId FundType;
	extern CLASS_IMPORT const BFTextFieldId Certificates;

	extern CLASS_IMPORT const BFTextFieldId MoneyMktFund;
}
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//										Field DD Id,             State Flags,       Group Flags 
   { ifds::Amount,        BFCBO::NONE,                 0 }, 
   { ifds::FundName,      BFCBO::NONE,                 0 }, 

};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );
//****************************************************************************
HypoRedAcctHolding::HypoRedAcctHolding( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
	registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL );
}

//****************************************************************************
HypoRedAcctHolding::~HypoRedAcctHolding()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}   

//****************************************************************************

SEVERITY HypoRedAcctHolding::init( const BFData& data, const DString& dstrTrack /*= I_("N")*/,
                         const DString& dstrPageName /*= NULL_STRING*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

	//attach the data object
   attachDataObject( const_cast<BFData&>(data), false );

	//set fund name
   setFundName(BF::HOST);

   clearUpdatedFlags( BF::HOST );

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

void HypoRedAcctHolding::getField( const BFFieldId& idField,
                         DString& strFieldValue,
                         const BFDataGroupId& idDataGroup,
                         bool formattedReturn ) const
{
   BFCBO::getField( idField, strFieldValue, idDataGroup, formattedReturn );
   if( idField == ifds::Amount && formattedReturn )
   {
      BFCBO::getField( idField, strFieldValue, idDataGroup, false );
      DString strAmtType;
      getParent()->getParent()->getField(ifds::AmtType, strAmtType, idDataGroup, false);
      if (strAmtType.strip().upperCase() == AMOUNT)
         (const_cast<HypoRedAcctHolding*>(this))->formatAmount( strFieldValue, idDataGroup);
      else if (strAmtType == UNITS)
		   (const_cast<HypoRedAcctHolding*>(this))->formatUnits(strFieldValue, idDataGroup);      
   }
   else if (idField == ifds::SettledValue && formattedReturn)
   {
      BFCBO::getField( idField, strFieldValue, idDataGroup, false );
      (const_cast<HypoRedAcctHolding*>(this))->formatAmount( strFieldValue, idDataGroup);
   }
   else if (idField == ifds::SettledUnits && formattedReturn)
		(const_cast<HypoRedAcctHolding*>(this))->formatUnits(strFieldValue, idDataGroup);      
}
//******************************************************************************

void HypoRedAcctHolding::setFundName(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setFundName" ) )

   FundMasterList *pFundMasterList = NULL;
   DString fundName;

   getWorkSession().getMgmtCo().getFundMasterList(pFundMasterList);
   if (pFundMasterList)
   {
      DString fundCode;

      getField (ifds::rxFundCode, fundCode, idDataGroup, false);
      if (!fundCode.strip().empty())
      {
	      FundMaster *pFundMaster = NULL;

	      if (pFundMasterList->getFundMaster (fundCode, idDataGroup, pFundMaster) &&
		        NULL != pFundMaster)
         {
            pFundMaster->getField (ifds::ElongName1, fundName, idDataGroup, true);
         }
      }
   }
   setFieldNoValidate (ifds::FundName, fundName, idDataGroup, true, true, true);
}

//******************************************************************************

SEVERITY HypoRedAcctHolding::doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

   if( idField == ifds::Amount )
      validateAmount(strValue, idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY HypoRedAcctHolding::validateAmount(const DString& strValue, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAmount" ) );

	DString strTemp(strValue);
	strTemp.strip();
	
	//rule: zero is a valid amount
	double dAmount = DSTCommonFunctions::convertToDouble(strTemp);
	if (fabs(dAmount) < dSmallValue)
		return(GETCURRENTHIGHESTSEVERITY());

	//rule: amount must be greater than zero
	if (dAmount < 0.0)
	{
		ADDCONDITIONFROMFILE(CND::ERR_AMOUNT_MUST_BE_GREATER_THAN_ZERO);
		return(GETCURRENTHIGHESTSEVERITY());
	}

	//rule: amount should be less or equal to the available holding
	DString strAmtType, strTotal;
	getParent()->getParent()->getField(ifds::AmtType, strAmtType, idDataGroup, false);
	if (strAmtType.strip() == AMOUNT)
		getField(ifds::SettledValue, strTotal, idDataGroup, false);
	else if (strAmtType.strip() == UNITS)
		getField(ifds::SettledUnits, strTotal, idDataGroup, false);
	else assert(0);

	double dTotal = DSTCommonFunctions::convertToDouble(strTotal);
	if ( dAmount - dTotal > dSmallValue)
	{
		ADDCONDITIONFROMFILE(CND::ERR_AMOUNT_GREATER_THAN_HOLDING);
		return(GETCURRENTHIGHESTSEVERITY());
	}

	//rule: if all units or dollar amounts are redeemed from a money market fund,
	//display warning
	if (isMoneyMarketFund())
	{
		if ( fabs(dAmount - dTotal) < dSmallValue)
		{
			ADDCONDITIONFROMFILE(CND::ERR_WARN_FULL_MONEY_MARKET);
		}
	}

	//rule: if certificate units exist issue warning
	validateCertificate(idDataGroup);

	//rule: check for escrow units
	validateEscrow(idDataGroup);


   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

void HypoRedAcctHolding::formatUnits(DString& strValue, const BFDataGroupId& idDataGroup)
{
	DString dstrAmountType, dstrCurrency;
   int iUnitsPrecision = 0;

   FundDetail *pFundDetail = NULL;
	FundDetailList *pFundDetailList = NULL;
   DString dstrUnitsPrecision, dstrFundCode, dstrClassCode;
	getField(ifds::rxFundCode, dstrFundCode, idDataGroup, false);
	getField(ifds::rxClassCode, dstrClassCode, idDataGroup, false);
	getMgmtCo().getFundDetailList( pFundDetailList );
	assert(pFundDetailList);
   if (pFundDetailList->getFundDetail( dstrFundCode.strip().upperCase(), 
		dstrClassCode.strip().upperCase(), idDataGroup, pFundDetail ) )
   {
		pFundDetail->getField( ifds::UnitsPrecision, dstrUnitsPrecision, BF::HOST, false  );
      iUnitsPrecision = dstrUnitsPrecision.asInteger(); 
      const BFFieldId& idField = ifds::USDollar;
      DSTCommonFunctions::formattedField( idField, iUnitsPrecision, strValue ); 
   }
}
//******************************************************************************

void HypoRedAcctHolding::formatAmount(DString& strValue, const BFDataGroupId& idDataGroup)
{
   DString strCurrency;
   getField( ifds::FundCurrency, strCurrency, idDataGroup, false );
   CurrencyClass::FormatValue( strCurrency.strip(), strValue, strValue ); 
}

//******************************************************************************

bool HypoRedAcctHolding::isMoneyMarketFund()
{
	bool blIsMoneyMarketFund = false;
	
	FundMasterList *pFundMasterList;
   if (getMgmtCo().getFundMasterList( pFundMasterList )<=WARNING && 
		pFundMasterList)
	{
		DString strFundCode, strClassCode;
		FundMaster *pFundMaster = NULL;
		getField(ifds::rxFundCode, strFundCode, BF::HOST, false);
		if( pFundMasterList->getFundMaster (strFundCode, BF::HOST, pFundMaster) &&
			pFundMaster)
		{
			DString dstrIsFundMM;
			pFundMaster->getField(ifds::MoneyMktFund, dstrIsFundMM, BF::HOST, false);			
			if ( dstrIsFundMM.strip().upperCase() == I_( "Y" ) )
				blIsMoneyMarketFund = true;
		}
	}
	
	return blIsMoneyMarketFund;
}
//******************************************************************************
SEVERITY HypoRedAcctHolding::validateCertificate(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateCertificate" ) );

   CertificateList *pCertificateList = NULL;
	MFAccount *pMFAccount = dynamic_cast<MFAccount*>(getParent()->getParent()->getParent());
	assert(pMFAccount);

   DString dstrCertExists (NO);
   pMFAccount->getField( ifds::Certificates, dstrCertExists, idDataGroup, false );
   if( dstrCertExists.strip().upperCase() == YES )
   {
      if (pMFAccount->getCertificateList ( pCertificateList, idDataGroup )
      <= WARNING && pCertificateList )
      {
			DString dstrFundCode, dstrClassCode;
		   double dIssueUnits = 0;

			getField(ifds::rxFundCode, dstrFundCode, idDataGroup, false);
			getField(ifds::rxClassCode, dstrClassCode, idDataGroup, false);

         if( pCertificateList->certIssueUnitsExist ( dstrFundCode, dstrClassCode, dIssueUnits, idDataGroup ) )
         {
            DString idiStr;
            DString dstrIssueUnits = DSTCommonFunctions::doubleToDString( ifds::SettledUnits, dIssueUnits );
			DSTCommonFunctions::DisplayFormat( dstrIssueUnits, ifds::SettledUnits );
            addIDITagValue(idiStr, I_( "ISSUEUNITS"), dstrIssueUnits);
            ADDCONDITIONFROMFILEIDI(CND::ERR_WARN_CERT_UNITS_EXISTS, idiStr);
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY HypoRedAcctHolding::validateEscrow(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateEscrow" ) );

	MFAccount *pMFAccount = dynamic_cast<MFAccount*>(getParent()->getParent()->getParent());
	assert(pMFAccount);

	DString dstrFundCode, dstrClassCode, strTradeDate;
	getField(ifds::rxFundCode, dstrFundCode, idDataGroup, false);
	getField(ifds::rxClassCode, dstrClassCode, idDataGroup, false);
	getField(ifds::AsAtDate, strTradeDate, idDataGroup, false);

	pMFAccount->lockedInFundClass( dstrFundCode.strip(), dstrClassCode.strip(), strTradeDate, idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/HypoRedAcctHolding.cpp-arc  $
// 
//    Rev 1.8   Jul 11 2005 17:23:48   Fengyong
// PET1250FN02 - European numeric enahncement - conditions
// decimal format 
// 
//    Rev 1.7   Nov 14 2004 14:44:26   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.6   May 11 2004 15:49:28   popescu
// PET 985, FN 01, LSIF Trade Entry, added handy methods to fund master list, to check whether a fund is LSIF/Money Market, GIC
// 
//    Rev 1.5   May 26 2003 17:04:52   VADEANUM
// Replaced criteria for deciding if a Fund Money Market.
// 
//    Rev 1.4   Apr 04 2003 15:53:52   VADEANUM
// Sync-ed up for isMoneyMarketFund() return value fix.
// 
//    Rev 1.3   Mar 21 2003 18:13:52   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.2   Feb 25 2003 14:40:28   PURDYECH
// Remove CLASS_IMPORT from Condition declaration as it causes a Linker warning.
// 
//    Rev 1.1   Nov 25 2002 09:36:22   KOVACSRO
// Added implementation.
// 
//    Rev 1.0   Oct 29 2002 10:50:48   KOVACSRO
// Initial Revision
// 
 
*/


