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
// ^FILE   : HypoRedCurrencyList.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 10/28/2002
//
// ^CLASS    : HypoRedCurrencyList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "hyporedcurrency.hpp"
#include "hyporedcurrencylist.hpp"

namespace  
{
   const I_CHAR * const CLASSNAME            = I_( "HypoRedCurrencyList" );
}

namespace ifds
{
	extern CLASS_IMPORT const BFTextFieldId Currency;
	extern CLASS_IMPORT const BFTextFieldId FundCurrency;
   extern CLASS_IMPORT const BFDecimalFieldId GrossAmt;
   extern CLASS_IMPORT const BFDecimalFieldId NetAmt;
	extern CLASS_IMPORT const BFDecimalFieldId DSC;
   extern CLASS_IMPORT const BFDecimalFieldId Fee;
   extern CLASS_IMPORT const BFDecimalFieldId WithHoldTax;
   extern CLASS_IMPORT const BFDecimalFieldId FedClawback;
   extern CLASS_IMPORT const BFDecimalFieldId ProvClawback;
   extern CLASS_IMPORT const BFDecimalFieldId AdditionalProvClawback;
  

}

//****************************************************************************
HypoRedCurrencyList::HypoRedCurrencyList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   setObjectAsList( );
}

//****************************************************************************
HypoRedCurrencyList::~HypoRedCurrencyList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}   

//****************************************************************************

SEVERITY HypoRedCurrencyList::init( const BFDataGroupId& idDataGroup, const DString& dstrTrack /*= I_("N")*/,
                         const DString& dstrPageName /*= NULL_STRING*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************

void HypoRedCurrencyList::changeCurrencyTotal(const BFDataGroupId& idDataGroup, const BFData &data)
{
	DString strCurrency;
   HypoRedCurrency *pHypoRedCurrency = NULL;
	data.getElementValue(ifds::FundCurrency, strCurrency);
	BFObjIter iter(*this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
	if ( iter.positionByKey( strCurrency.strip().upperCase() ) )
	{
		pHypoRedCurrency = dynamic_cast<HypoRedCurrency *>(iter.getObject());
		assert(pHypoRedCurrency);
	}
	else//not in the list yet; add a new HypoRedCurrency
	{
		BFObjectKey objKey;
		m_strKeyForNewItem = strCurrency;
		pHypoRedCurrency = dynamic_cast<HypoRedCurrency *>(
			getNewListItem(objKey)); 
		m_strKeyForNewItem = NULL_STRING;
      pHypoRedCurrency->setField(ifds::Currency, strCurrency, BF::HOST, false);
	}
   if (pHypoRedCurrency)
		pHypoRedCurrency->updateTotal(idDataGroup, data);
}
//******************************************************************************

SEVERITY HypoRedCurrencyList::doCreateNewObject(BFCBO *& pBase, DString & strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

	HypoRedCurrency* pCurrency = new HypoRedCurrency( *this );
   pCurrency->init( idDataGroup );
   pBase = pCurrency;

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

void HypoRedCurrencyList::getStrKeyForNewItem( DString & strKey )
{
	assert(!m_strKeyForNewItem.strip().empty());
	strKey = m_strKeyForNewItem;
}

//******************************************************************************
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/HypoRedCurrencyList.cpp-arc  $
// 
//    Rev 1.4   Nov 14 2004 14:44:36   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.3   May 10 2004 13:45:10   AGUILAAM
// PET985_FN01-1: LSIF HypoCalc enhancement - added clawback fields
// 
//    Rev 1.2   Mar 21 2003 18:14:12   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.1   Nov 25 2002 09:39:40   KOVACSRO
// Added implementation.
// 
//    Rev 1.0   Oct 29 2002 10:50:52   KOVACSRO
// Initial Revision
// 
 
*/


