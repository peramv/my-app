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
//    Copyright 2002 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : RRIFFundAllocList.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 22/07/02
//
// ^CLASS    : RRIFFundAllocList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : Trade, PendingTradeDetails and TransactionDetails fund allocation list
//
//******************************************************************************

#include "stdafx.h"
#include "deffundalloclist.hpp"
//#include "splitcommissionlist.hpp"
//#include "trade.hpp"
//#include "tradeacctalloclist.hpp"
#include "rriffundalloc.hpp"
#include "rriffundalloclist.hpp"
#include <ifastdataimpl\dse_dstc0068_req.hpp>
#include <ifastdataimpl\dse_dstc0068_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME = I_( "RRIFFundAllocList" );
   const I_CHAR * const NO = I_( "N" );
   const I_CHAR * const YES = I_( "Y" );
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
RRIFFundAllocList::RRIFFundAllocList( BFAbstractCBO &parent ) 
: FundAllocList( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   setObjectAsList();
}

//******************************************************************************
RRIFFundAllocList::~RRIFFundAllocList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}
//******************************************************************************

SEVERITY RRIFFundAllocList::initExisting( const DString& dstrTrack,
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

   ReceiveData(DSTC_REQUEST::RRIF_LIF_LRIF_ALLOC, *pRequestDataRRIF_Alloc, ifds::DSTC0068_VW, 
               DSTCRequestor( getSecurity(), false ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY RRIFFundAllocList::initNew( const BFDataGroupId& idDataGroup,
                                     bool bGetDefault,
                                     const DString& dstrTrack,
                                     const DString& dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initNew" ) );

   FundAllocList::initNew(idDataGroup, bGetDefault, dstrTrack, dstrPageName);

   setFieldNoValidate(ifds::ReplaceAsDefault, NO, idDataGroup);

   if( bGetDefault )
   {
      RRIFFundAlloc *pRRIFFundAlloc = NULL;
      initDefaultAllocationList(pRRIFFundAlloc, idDataGroup);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY RRIFFundAllocList::addNewAllocation( const DString& strKey, 
                                              const BFDataGroupId& idDataGroup,
                                              bool bGetDefault, 
                                              bool bCopyParent,
                                              bool bAddChildren)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "addNewAllocation" ) );

   BFObjectKey objKey( strKey, idDataGroup );
   DString strKeyCopy(strKey);
   if( !strKeyCopy.strip().empty() )
      m_strKeyForNewItem = strKey;
   RRIFFundAlloc * pNewRRIFFundAlloc = dynamic_cast<RRIFFundAlloc*>(getNewListItem( objKey ));
   m_strKeyForNewItem = NULL_STRING;

   assert(pNewRRIFFundAlloc);
   if( bCopyParent )
      pNewRRIFFundAlloc->copyDataFromParent(idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY RRIFFundAllocList::addExistingAllocation( const DString& strKey, 
                                                   const BFDataGroupId& idDataGroup,
                                                   bool bAddChildren)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "addExistingAllocation" ) );

   BFObjectKey objKey( strKey, idDataGroup );
   RRIFFundAlloc * pNewRRIFFundAlloc;
   getKey( objKey, NULL, true );
   objKey.setActivity( OBJ_ACTIVITY_NONE );
   pNewRRIFFundAlloc = new RRIFFundAlloc( *this );
   setObject( objKey, pNewRRIFFundAlloc );

   //what do we do with the key if not null??
   pNewRRIFFundAlloc->initWithDefaultValues(idDataGroup);
   pNewRRIFFundAlloc->copyDataFromParent(idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY RRIFFundAllocList::doCreateNewObject( BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   RRIFFundAlloc *pAllocation = new RRIFFundAlloc( *this );
   pAllocation->initNew( idDataGroup );
   pBase = pAllocation;
   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************

SEVERITY RRIFFundAllocList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup ) 
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
   getWorkSession().getOption( ifds::RRIFAllocations, dstrAllocMandatory, idDataGroup, false );
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

bool RRIFFundAllocList::isAllDummy(const BFDataGroupId& idDataGroup)
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

SEVERITY RRIFFundAllocList::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );
   if( FundAllocList::doApplyRelatedChanges( idField, idDataGroup ) > WARNING )
      return(GETCURRENTHIGHESTSEVERITY());

   return(GETCURRENTHIGHESTSEVERITY());
}

/******************************************************************************

void RRIFFundAllocList::getFormattedAmount(const BFDataGroupId& idDataGroup, DString &dstrValue)
{
  //no formatting for RRIF??!?
}*/
//******************************************************************************

SEVERITY RRIFFundAllocList::setListFields(const BFDataGroupId& idDataGroup)
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
   if( getWorkSession ().isLIFLike (dstrTaxType)) dstrTaxType = I_("LF");
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

SEVERITY RRIFFundAllocList::doCreateObject( const BFData &data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut = new RRIFFundAlloc ( *this );
   dynamic_cast< RRIFFundAlloc * >( pObjOut )->initExisting( data );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY RRIFFundAllocList::loadSubstitutions( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "loadSubstitutions" ) );

   if( DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA )
      setFieldSubstituteValues( ifds::TransType, idDataGroup, ifds::RRIFTransType);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RRIFFundAllocList.cpp-arc  $
// 
//    Rev 1.10   Nov 25 2008 11:27:58   jankovii
// PET 142196 FN01 Federal Restricted LIF and LIRA.
// 
//    Rev 1.9   Nov 14 2004 14:53:28   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.8   Mar 21 2003 18:22:56   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.7   Jan 12 2003 16:00:50   KOVACSRO
// If RRIFAllocation is 'N', doValidateAll will return if there are no items or only dummy items in the list.
// 
//    Rev 1.6   Dec 31 2002 13:51:20   KOVACSRO
// added multicurrency check.
// 
//    Rev 1.5   Dec 06 2002 09:32:20   YINGBAOL
// PRIF Enhancement
// 
//    Rev 1.4   Oct 09 2002 23:54:54   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.3   Aug 29 2002 12:56:34   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.2   Aug 19 2002 15:28:30   KOVACSRO
// 1. introduced RRIFTransType
// 2. getting currency from account
// 
//    Rev 1.1   Aug 13 2002 10:43:38   KOVACSRO
// when RRIFallocations  is Yes, user has to set up RRIFAllocation
// 
//    Rev 1.0   Aug 06 2002 10:50:22   KOVACSRO
// Initial revision.
 * 
 * 
 */