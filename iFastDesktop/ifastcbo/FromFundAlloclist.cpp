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
//    Copyright 2003 by IFDS.
//
//
//******************************************************************************
//
// ^FILE   : FromFundAllocList.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : May 27,2003
//
// ^CLASS    : FromFundAllocList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#include "stdafx.h"
#include "deffundalloclist.hpp"
//#include "splitcommissionlist.hpp"
//#include "trade.hpp"
//#include "tradeacctalloclist.hpp"
#include "FromFundAlloc.hpp"
#include "FromFundAllocList.hpp"
#include "MFAccount.hpp"

#include <ifastdataimpl\dse_dstc0068_req.hpp>
#include <ifastdataimpl\dse_dstc0068_vw.hpp>
#include <ifastdataimpl\dse_dstc0149_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME = I_( "FromFundAllocList" );
   const I_CHAR * const NO = I_( "N" );
   const I_CHAR * const YES = I_( "Y" );
	const I_CHAR * const EX_FER_OUT_CODE            = I_( "XFOUT" );  // trade trans type Exchange Out

}

namespace CND
{
   extern const long  ERR_RRIF_ALLOCATION_SETUP;
}

namespace ifds
{  
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFTextFieldId ReplaceAsDefault;
   extern CLASS_IMPORT const BFTextFieldId AllocAmtType;
   extern CLASS_IMPORT const BFTextFieldId GoodBad;
   extern CLASS_IMPORT const BFDecimalFieldId Amount;
   extern CLASS_IMPORT const BFDateFieldId EffectiveFrom;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFDecimalFieldId RRIFAmount;
   extern CLASS_IMPORT const BFTextFieldId Currency;
   extern CLASS_IMPORT const BFTextFieldId TaxType;
   extern CLASS_IMPORT const BFTextFieldId RRIFAllocations;
   extern CLASS_IMPORT const BFTextFieldId RRIFTransType;

}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest RRIF_LIF_LRIF_ALLOC;
}


//******************************************************************************
FromFundAllocList::FromFundAllocList( BFAbstractCBO &parent ) 
: FundAllocList( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   setObjectAsList();
}

//******************************************************************************
FromFundAllocList::~FromFundAllocList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}
//******************************************************************************

SEVERITY FromFundAllocList::initExisting( const DString& dstrTrack,
                                          const DString& dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initExisting" ) );

   setListFields(BF::HOST);

   BFData* pRequestDataRRIF_Alloc =  new BFData( ifds::DSTC0068_REQ);

   DString mgmtCoIdOut, strAccountNum, dstrRIFId;
   getField(ifds::AccountNum, strAccountNum, BF::HOST, false);
   pRequestDataRRIF_Alloc->setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   pRequestDataRRIF_Alloc->setElementValue( ifds::AccountNum, strAccountNum);
   pRequestDataRRIF_Alloc->setElementValue( ifds::NextKey,NULL_STRING );
   pRequestDataRRIF_Alloc->setElementValue( ifds::Track, dstrTrack );
   pRequestDataRRIF_Alloc->setElementValue( ifds::Activity, dstrPageName );
   BFCBO* pParent = getTopLevelCBO();
   pParent->getField(ifds::RIFId, dstrRIFId, BF::HOST, false);
   pRequestDataRRIF_Alloc->setElementValue( ifds::RIFId, dstrRIFId, false, false );
	
	DString dstrAllocType,dstrTaxType;
   BFCBO *pMFAccount = pParent->getParent()->getParent();
   pMFAccount->getField(ifds::TaxType, dstrTaxType, BF::HOST, false);
   if( getWorkSession().isLIFLike (dstrTaxType)) dstrAllocType = I_("LF");
   else if( dstrTaxType == I_("L") ) dstrAllocType = I_("LR");
   else if( dstrTaxType == I_("2") || dstrTaxType == I_("R") ) dstrAllocType = I_("RF");


   pRequestDataRRIF_Alloc->setElementValue( ifds::AllocType, dstrAllocType, false, false );


   ReceiveData(DSTC_REQUEST::RRIF_LIF_LRIF_ALLOC, *pRequestDataRRIF_Alloc, ifds::DSTC0068_VW, 
               DSTCRequestor( getSecurity(), false ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY FromFundAllocList::initNew( const BFDataGroupId& idDataGroup,
                                     bool bGetDefault,
                                     const DString& dstrTrack,
                                     const DString& dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initNew" ) );

   FundAllocList::initNew(idDataGroup, bGetDefault, dstrTrack, dstrPageName);

   setFieldNoValidate(ifds::ReplaceAsDefault, NO, idDataGroup);

   if( bGetDefault )
   {
      FromFundAlloc *pFromFundAlloc = NULL;
      initDefaultAllocationList(pFromFundAlloc, idDataGroup);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY FromFundAllocList::doCreateNewObject( BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   FromFundAlloc *pAllocation = new FromFundAlloc( *this );
   pAllocation->initNew( idDataGroup );
   pBase = pAllocation;
   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************

SEVERITY FromFundAllocList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   //don't validate allocations for a bad RRIF_Info
   DString dstrStatus;
   getParent()->getField(ifds::GoodBad,dstrStatus,idDataGroup,false);
   if( dstrStatus.strip() != YES )
      return(NO_SEVERITY);

   //if RRIFAllocations == 'N' and there are no allocations in the list, 
   //or there are only dummy items, just return
   DString dstrAllocMandatory;
   getWorkSession().getOption( ifds::RRIFFromAlloc, dstrAllocMandatory, idDataGroup, false );
   if( dstrAllocMandatory.strip().upperCase()==NO )
   {
      if (isAllDummy(idDataGroup))
         return(GETCURRENTHIGHESTSEVERITY());
   }

   if( FundAllocList::doValidateAll( idDataGroup, lValidateGroup )>WARNING )
      return(GETCURRENTHIGHESTSEVERITY());

   //for non multicurrency env., issue an error if not all the currencies are the same
   if( !isMultiCurrency() )
      validateMulticurrency(idDataGroup);

   if( dstrAllocMandatory.strip().upperCase()==YES )
   {
      BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
      int  iNum = iter.getNumberOfItemsInList();
      if( !iNum || isAllDummy(idDataGroup))
      {
         ADDCONDITIONFROMFILE( CND::ERR_RRIF_ALLOCATION_SETUP );
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

bool FromFundAllocList::isAllDummy(const BFDataGroupId& idDataGroup)
{
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
  
   bool bAllDummy = true;
   while( !iter.end() )
   {
      if( !iter.isDummy() )
      {
         bAllDummy=false;
         break;
      }
      ++iter;
   }

   return bAllDummy;
}

//******************************************************************************

SEVERITY FromFundAllocList::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );
   if( FundAllocList::doApplyRelatedChanges( idField, idDataGroup ) > WARNING )
      return(GETCURRENTHIGHESTSEVERITY());

   return(GETCURRENTHIGHESTSEVERITY());
}

/******************************************************************************

void FromFundAllocList::getFormattedAmount(const BFDataGroupId& idDataGroup, DString &dstrValue)
{
  //no formatting for RRIF??!?
}*/
//******************************************************************************

SEVERITY FromFundAllocList::setListFields(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setListFields" ) );

   loadSubstitutions(idDataGroup);

   BFCBO *pParent = NULL;
   pParent = getTopLevelCBO();
   assert(pParent);
   DString str, dstrTaxType;

   BFCBO *pMFAccount = pParent->getParent()->getParent();
   assert(pMFAccount);
   setFieldFromCBO(pMFAccount, ifds::AccountNum, ifds::AccountNum, idDataGroup, str);
   setFieldFromCBO(pMFAccount, ifds::Currency, ifds::Currency, idDataGroup, str);
   pMFAccount->getField(ifds::TaxType, dstrTaxType, idDataGroup, false);
   if( getWorkSession().isLIFLike (dstrTaxType)) dstrTaxType = I_("LF");
   else if( dstrTaxType == I_("L") ) dstrTaxType = I_("LR");
   else if( dstrTaxType == I_("2") || dstrTaxType == I_("R") ) dstrTaxType = I_("RF");
   setFieldNoValidate(ifds::TransType, dstrTaxType, idDataGroup, false);

   setFieldFromCBO(pParent, ifds::EffectiveFrom, ifds::EffectiveDate, idDataGroup, str);
   setFieldFromCBO(pParent, ifds::RRIFAmount, ifds::Amount, idDataGroup, str);
   //setFieldFromCBO(pParent, ifds::AmtType, ifds::AllocAmtType, idDataGroup, str);
   setField(ifds::AllocAmtType, I_("D"), idDataGroup, false);
   //setFieldFromCBO(pParent, ifds::FromFund, ifds::FromFund, idDataGroup, str);
   //setFieldFromCBO(pParent, ifds::FromClass, ifds::FromClass, idDataGroup, str);


   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY FromFundAllocList::doCreateObject( const BFData &data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut = new FromFundAlloc ( *this );
   dynamic_cast< FromFundAlloc * >( pObjOut )->initExisting( data );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY FromFundAllocList::loadSubstitutions( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "loadSubstitutions" ) );

   if( DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA )
      setFieldSubstituteValues( ifds::TransType, idDataGroup, ifds::RRIFTransType);

   return(GETCURRENTHIGHESTSEVERITY());
}
/*******************************************************************************
SEVERITY FromFundAllocList::isTransferAllowed( const BFDataGroupId& idDataGroup )
{



}
*/

SEVERITY FromFundAllocList::validateTransOut( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFromFundToFund" ) );
	DString dstrEffectiveDate;
	getParent()->getField(ifds::EffectiveFrom,dstrEffectiveDate,idDataGroup,false);
	MFAccount* pMFAccount = dynamic_cast<MFAccount* >( getParent()->getParent()->getParent() );
	if(pMFAccount )
	{
		DString dstrFundCode,dstrClassCode;
		BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
		while( !iter.end() )
		{
			iter.getObject()->getField(ifds::FundCode,dstrFundCode,idDataGroup,false);		 
			iter.getObject()->getField(ifds::ClassCode,dstrClassCode,idDataGroup,false);	
			SEVERITY sev = pMFAccount->canTradeFundClass ( dstrFundCode,dstrClassCode,EX_FER_OUT_CODE,
														dstrEffectiveDate,idDataGroup );
         if(sev>WARNING )
			{
				break;
			}		
		++iter;
		}		
	}	
   return(GETCURRENTHIGHESTSEVERITY());
}








//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FromFundAlloclist.cpp-arc  $
// 
//    Rev 1.3   Nov 25 2008 11:19:38   jankovii
// PET 142196 FN01 Federal Restricted LIF and LIRA.
// 
//    Rev 1.2   Nov 14 2004 14:41:14   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.1   Jun 13 2003 15:54:42   YINGBAOL
// implement validateTransout
// 
//    Rev 1.0   Jun 09 2003 11:03:10   YINGBAOL
// Initial revision.
// 

 * 
 * 
 */