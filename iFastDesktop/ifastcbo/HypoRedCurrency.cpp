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
// ^FILE   : HypoRedCurrency.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 10/28/2002
//
// ^CLASS    : HypoRedCurrency
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "hyporedcurrency.hpp"

namespace  
{
   const I_CHAR * const CLASSNAME            = I_( "HypoRedCurrency" );

}


namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId Currency;
   extern CLASS_IMPORT const BFDecimalFieldId Amount;
   extern CLASS_IMPORT const BFDecimalFieldId GrossAmt;
   extern CLASS_IMPORT const BFDecimalFieldId NetAmt;
   extern CLASS_IMPORT const BFDecimalFieldId DSC;
   extern CLASS_IMPORT const BFDecimalFieldId Fee;   
   extern CLASS_IMPORT const BFTextFieldId ErrorDesc;
   extern CLASS_IMPORT const BFDecimalFieldId FedClawback;
   extern CLASS_IMPORT const BFDecimalFieldId ProvClawback;
   extern CLASS_IMPORT const BFDecimalFieldId AdditionalProvClawback;   
   extern CLASS_IMPORT const BFDecimalFieldId FedTax;
   extern CLASS_IMPORT const BFDecimalFieldId ProvTax;
   extern CLASS_IMPORT const BFDecimalFieldId TotCBAmount;  
  
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//                            Field DD Id,                  State Flags,             Group Flags 
   { ifds::Currency,               BFCBO::NONE,                 0 }, 
   { ifds::GrossAmt,               BFCBO::NONE,                 0 }, 
   { ifds::NetAmt,                 BFCBO::NONE,                 0 }, 
   { ifds::DSC,                    BFCBO::NONE,                 0 }, 
   { ifds::Fee,                    BFCBO::NONE,                 0 },    
   { ifds::FedClawback,            BFCBO::NONE,                 0 },
   { ifds::ProvClawback,           BFCBO::NONE,                 0 },
   { ifds::AdditionalProvClawback, BFCBO::NONE,                 0 },   
   { ifds::FedTax,                 BFCBO::NONE,                 0 },
   { ifds::ProvTax,                BFCBO::NONE,                 0 }, 
   { ifds::TotCBAmount,			   BFCBO::NONE,                 0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );
//****************************************************************************
HypoRedCurrency::HypoRedCurrency( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
	registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL );
}

//****************************************************************************
HypoRedCurrency::~HypoRedCurrency()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}   

//****************************************************************************

SEVERITY HypoRedCurrency::init( const BFDataGroupId& idDataGroup, const DString& dstrTrack /*= I_("N")*/,
                         const DString& dstrPageName /*= NULL_STRING*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
	
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

void HypoRedCurrency::getField( const BFFieldId& idField,
                         DString& strFieldValue,
                         const BFDataGroupId& idDataGroup,
                         bool formattedReturn ) const
{
	if (idField == ifds::NetAmt)
	{
		DString strGrossAmt, strDSC, strFee, /*strWithHoldTax,*/ strProvCB, strFedCB, strAddlProvCB;
		DString strFedTax,strProvTax,strTotCBAmount;
		getField(ifds::GrossAmt, strGrossAmt, idDataGroup, false);
		getField(ifds::DSC, strDSC, idDataGroup, false);
		getField(ifds::Fee, strFee, idDataGroup, false);
		getField(ifds::FedTax,  strFedTax, idDataGroup, false);
		getField(ifds::ProvTax, strProvTax, idDataGroup, false);
		getField(ifds::ProvClawback, strProvCB, idDataGroup, false);
		getField(ifds::FedClawback, strFedCB, idDataGroup, false);
		getField(ifds::AdditionalProvClawback, strAddlProvCB, idDataGroup, false);
		getField(ifds::TotCBAmount, strTotCBAmount, idDataGroup, false);

		double dGrossAmt(0), dDSC(0), dFee(0), dNetAmt(0), dFedCB(0), dProvCB(0), dAddlProvCB(0);		
		double dFedTax(0),dProvTax(0),dTotCBAmount(0);

		if (!strGrossAmt.strip().empty())
			dGrossAmt = DSTCommonFunctions::convertToDouble(strGrossAmt);
		if (!strDSC.strip().empty())
			dDSC = DSTCommonFunctions::convertToDouble(strDSC);	
		if (!strFee.strip().empty())
			dFee = DSTCommonFunctions::convertToDouble(strFee);	
		if (!strFedTax.strip().empty())
			dFedTax = DSTCommonFunctions::convertToDouble(strFedTax);
		if (!strProvTax.strip().empty())
			dProvTax = DSTCommonFunctions::convertToDouble(strProvTax);
		if (!strProvCB.strip().empty())
			dProvCB = DSTCommonFunctions::convertToDouble(strProvCB);	
		if (!strFedCB.strip().empty())
			dFedCB = DSTCommonFunctions::convertToDouble(strFedCB);	
		if (!strAddlProvCB.strip().empty())
			dAddlProvCB = DSTCommonFunctions::convertToDouble(strAddlProvCB);
		if (!strTotCBAmount.strip().empty())
			dTotCBAmount = DSTCommonFunctions::convertToDouble(strTotCBAmount);

		dNetAmt = dGrossAmt - dDSC - dFee /*- dWithHoldTax*/-dFedTax - dProvTax - dProvCB - dFedCB - dAddlProvCB;
		strFieldValue = DSTCommonFunctions::doubleToDString(ifds::Amount, dNetAmt);
		unformatField( ifds::Amount, strFieldValue, idDataGroup );
	}
	else
		BFCBO::getField( idField, strFieldValue, idDataGroup, formattedReturn );

   if( idField == ifds::GrossAmt 
      || idField == ifds::NetAmt 
	  || idField == ifds::DSC || idField == ifds::Fee 
	  || idField == ifds::FedTax
	  || idField == ifds::ProvTax
      || idField == ifds::FedClawback
      || idField == ifds::ProvClawback
      || idField == ifds::AdditionalProvClawback 
	  || idField == ifds::TotCBAmount 
		&& formattedReturn )
   {
      DString strCurrency;
      getField( ifds::Currency, strCurrency, idDataGroup, false );
      strCurrency.strip();

      if (idField != ifds::NetAmt)
         BFCBO::getField( idField, strFieldValue, idDataGroup, false );
      CurrencyClass::FormatValue( strCurrency, strFieldValue, strFieldValue );
   }
}
//******************************************************************************

void HypoRedCurrency::updateTotal(const BFDataGroupId& idDataGroup, const BFData &data)
{
   //this code is here to fix a view problem : if the record is bad, view still returns values for
   //amounts different from zero
   DString strError;
   data.getElementValue(ifds::ErrorDesc, strError);
   if (!strError.strip().empty())//bad record
      return;

	DString strCurrGrossAmt, strCurrDSC, strCurrFee, /*strCurrWithHoldTax*,*/
		    strNewGrossAmt, strNewDSC, strNewFee, /*strNewWithHoldTax,*/
            strCurrProvClawback, strCurrFedClawback, strCurrAddlProvClawback,			
			strCurrFedTax,strCurrProvTax,strNewFedTax,strNewProvTax,			
            strNewProvClawback, strNewFedClawback, strNewAddlProvClawback, strCurrTotCBAmount, strNewTotCBAmount;
      
	getField(ifds::GrossAmt, strCurrGrossAmt, idDataGroup, false);
	getField(ifds::DSC, strCurrDSC, idDataGroup, false);
	getField(ifds::Fee, strCurrFee, idDataGroup, false);	
	getField(ifds::FedTax, strCurrFedTax, idDataGroup, false);
	getField(ifds::ProvTax, strCurrProvTax, idDataGroup, false);
    getField(ifds::FedClawback, strCurrFedClawback, idDataGroup, false);
    getField(ifds::ProvClawback, strCurrProvClawback, idDataGroup, false);
    getField(ifds::AdditionalProvClawback, strCurrAddlProvClawback, idDataGroup, false);
	getField(ifds::TotCBAmount, strCurrTotCBAmount, idDataGroup, false);

	double dCurrGrossAmt(0), dCurrDSC(0), dCurrFee(0), 
		   dNewGrossAmt(0), dNewDSC(0), dNewFee(0), 
		   dCurrFedTax(0), dCurrProvTax(0),
		   dNewFedTax(0),dNewProvTax(0),
           dCurrFedClawback (0), dCurrProvClawback (0), dCurrAddlProvClawback (0),
           dNewFedClawback (0), dNewProvClawback (0), dNewAddlProvClawback (0), dCurrTotCBAmount (0), dNewTotCBAmount (0);

	if (!strCurrGrossAmt.strip().empty())
		dCurrGrossAmt = DSTCommonFunctions::convertToDouble(strCurrGrossAmt);
	if (!strCurrDSC.strip().empty())
		dCurrDSC = DSTCommonFunctions::convertToDouble(strCurrDSC);	
	if (!strCurrFee.strip().empty())
		dCurrFee = DSTCommonFunctions::convertToDouble(strCurrFee);	
	if (!strCurrFedTax.strip().empty())
		dCurrFedTax = DSTCommonFunctions::convertToDouble(strCurrFedTax);
	if (!strCurrProvTax.strip().empty())
		dCurrProvTax = DSTCommonFunctions::convertToDouble(strCurrProvTax);
    if (!strCurrFedClawback.strip().empty())
		dCurrFedClawback = DSTCommonFunctions::convertToDouble(strCurrFedClawback);
    if (!strCurrProvClawback.strip().empty())
		dCurrProvClawback = DSTCommonFunctions::convertToDouble(strCurrProvClawback);
    if (!strCurrAddlProvClawback.strip().empty())
		dCurrAddlProvClawback = DSTCommonFunctions::convertToDouble(strCurrAddlProvClawback);
	if (!strCurrTotCBAmount.strip().empty())
		dCurrTotCBAmount = DSTCommonFunctions::convertToDouble(strCurrTotCBAmount);
	
	data.getElementValue(ifds::Amount, strNewGrossAmt);
	data.getElementValue(ifds::DSC, strNewDSC);
	data.getElementValue(ifds::Fee, strNewFee);
	data.getElementValue(ifds::FedTax, strNewFedTax);
	data.getElementValue(ifds::ProvTax, strNewProvTax);
    data.getElementValue(ifds::FedClawback, strNewFedClawback);
    data.getElementValue(ifds::ProvClawback, strNewProvClawback);
    data.getElementValue(ifds::AdditionalProvClawback, strNewAddlProvClawback);
	data.getElementValue(ifds::TotCBAmount, strNewTotCBAmount);
   
	if (!strNewGrossAmt.strip().empty())
		dNewGrossAmt = DSTCommonFunctions::convertToDouble(strNewGrossAmt);
	if (!strNewDSC.strip().empty())
		dNewDSC = DSTCommonFunctions::convertToDouble(strNewDSC);	
	if (!strNewFee.strip().empty())
		dNewFee = DSTCommonFunctions::convertToDouble(strNewFee);	
	if (!strNewFedTax.strip().empty())
		dNewFedTax = DSTCommonFunctions::convertToDouble(strNewFedTax);
	if (!strNewProvTax.strip().empty())
		dNewProvTax = DSTCommonFunctions::convertToDouble(strNewProvTax);
    if (!strNewFedClawback.strip().empty())
		dNewFedClawback = DSTCommonFunctions::convertToDouble(strNewFedClawback);
    if (!strNewProvClawback.strip().empty())
		dNewProvClawback = DSTCommonFunctions::convertToDouble(strNewProvClawback);
    if (!strNewAddlProvClawback.strip().empty())
		dNewAddlProvClawback = DSTCommonFunctions::convertToDouble(strNewAddlProvClawback);
	if (!strNewTotCBAmount.strip().empty())
		dNewTotCBAmount = DSTCommonFunctions::convertToDouble(strNewTotCBAmount);

	dNewGrossAmt         += dCurrGrossAmt;
	dNewDSC              += dCurrDSC;
	dNewFee              += dCurrFee;
	dNewFedTax           += dCurrFedTax;
	dNewProvTax          += dCurrProvTax;
    dNewFedClawback      += dCurrFedClawback;
    dNewProvClawback     += dCurrProvClawback;
    dNewAddlProvClawback += dCurrAddlProvClawback;
	dNewTotCBAmount		 += dCurrTotCBAmount;

	strNewGrossAmt = DSTCommonFunctions::doubleToDString(ifds::Amount, dNewGrossAmt);
	strNewDSC = DSTCommonFunctions::doubleToDString(ifds::Amount, dNewDSC);
	strNewFee = DSTCommonFunctions::doubleToDString(ifds::Amount, dNewFee);
	strNewFedTax = DSTCommonFunctions::doubleToDString(ifds::Amount, dNewFedTax);
	strNewProvTax = DSTCommonFunctions::doubleToDString(ifds::Amount, dNewProvTax);
    strNewFedClawback = DSTCommonFunctions::doubleToDString(ifds::Amount, dNewFedClawback);
    strNewProvClawback = DSTCommonFunctions::doubleToDString(ifds::Amount, dNewProvClawback);
    strNewAddlProvClawback = DSTCommonFunctions::doubleToDString(ifds::Amount, dNewAddlProvClawback);
	strNewTotCBAmount = DSTCommonFunctions::doubleToDString(ifds::Amount, dNewTotCBAmount);

	setField(ifds::GrossAmt, strNewGrossAmt, idDataGroup, true);
	setField(ifds::DSC, strNewDSC, idDataGroup, true);
	setField(ifds::Fee, strNewFee, idDataGroup, true);
	setField(ifds::FedTax, strNewFedTax, idDataGroup, true);
	setField(ifds::ProvTax, strNewProvTax, idDataGroup, true);
    setField(ifds::FedClawback, strNewFedClawback, idDataGroup, true);
    setField(ifds::ProvClawback, strNewProvClawback, idDataGroup, true);
    setField(ifds::AdditionalProvClawback, strNewAddlProvClawback, idDataGroup, true);
	setField(ifds::TotCBAmount, strNewTotCBAmount, idDataGroup, true);
}

//******************************************************************************
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/HypoRedCurrency.cpp-arc  $
// 
//    Rev 1.7   Jun 14 2007 11:28:34   porteanm
// PET 2363 FN?? - GAP 5  - Cleanup.
// 
//    Rev 1.6   Jun 14 2007 10:52:32   porteanm
// PET 2363 FN?? - GAP 5  - for BKK.
// 
//    Rev 1.5   Nov 14 2004 14:44:34   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.4   Jul 21 2004 12:34:20   AGUILAAM
// PTS 10031847 - clawback values should be deducted from grossamount to come up with the netamount. 
// 
//    Rev 1.3   May 10 2004 13:45:06   AGUILAAM
// PET985_FN01-1: LSIF HypoCalc enhancement - added clawback fields
// 
//    Rev 1.2   Mar 21 2003 18:14:06   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.1   Nov 25 2002 09:39:02   KOVACSRO
// Added implementation.
// 
//    Rev 1.0   Oct 29 2002 10:50:52   KOVACSRO
// Initial Revision
// 
 
*/


