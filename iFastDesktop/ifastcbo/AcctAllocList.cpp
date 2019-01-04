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
// ^FILE   : AcctAllocList.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 25/03/02
//
// ^CLASS    : AcctAllocList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : common interface for all the account allocation lists
//
//******************************************************************************
#include "stdafx.h"
#include "acctalloc.hpp"
#include "defacctalloclist.hpp"
#include "fundalloclist.hpp"
#include "mfaccount.hpp"
#include "shareholder.hpp"
#include "shralloctypelist.hpp"

namespace
{
   const I_CHAR * const CLASSNAME                = I_( "AcctAllocList" );
   const I_CHAR * const REDEMPTION_CODE          = I_( "PW" );     // trade trans type Redemption
   const I_CHAR * const WIRE                     = I_( "WIRE" );   //PayMethod Wire
   const I_CHAR * const AMS_REBALANCING          = I_( "RB" );   //TransType AMS Rebalancing
}

namespace CND
{
   extern const long ERR_IDENTICAL_ACCT_DEFAULT_ALLOCS;
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFTextFieldId AllocAmtType;
   extern CLASS_IMPORT const BFDecimalFieldId Amount;
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
   extern CLASS_IMPORT const BFTextFieldId FromFund;
   extern CLASS_IMPORT const BFTextFieldId FromClass;
   extern CLASS_IMPORT const BFTextFieldId SettleCurrency;
   extern CLASS_IMPORT const BFTextFieldId Currency;
   extern CLASS_IMPORT const BFTextFieldId PayMethod;
   extern CLASS_IMPORT const BFTextFieldId AmountType;

}

//******************************************************************************
AcctAllocList::AcctAllocList( BFAbstractCBO &parent ) 
: AbstractAllocList( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   setObjectAsList();
}

//******************************************************************************
AcctAllocList::~AcctAllocList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}
//******************************************************************************
SEVERITY AcctAllocList::initNew( const BFDataGroupId& idDataGroup,
                                 bool bGetDefault,
                                 const DString& dstrTrack,
                                 const DString& dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initNew" ) );

   setObjectNew();
   setListFields(idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY AcctAllocList::clearAllocations( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "clearAllocations" ) );

   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   iter.begin();
   while( !iter.end() )
   {
      AcctAlloc *pAcctAlloc = NULL;
      pAcctAlloc = dynamic_cast<AcctAlloc*>(iter.getObject());
      if( pAcctAlloc )
      {
         FundAllocList* pFundAllocList = NULL;
         pAcctAlloc->getFundAllocationList(pFundAllocList, idDataGroup, false, false);
         if( pFundAllocList )
            pFundAllocList->clearAllocations(idDataGroup);
      }
      iter.deleteObject();
   }
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY AcctAllocList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   AbstractAllocList::doValidateAll(idDataGroup, lValidateGroup);


   std::set< DString > setCharacteristic;

   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() )
   {
      DString strAllocAccountNum;
      iter.getObject()->getField(ifds::AccountNum, strAllocAccountNum, idDataGroup, false);

      if( !strAllocAccountNum.strip().stripLeading('0').empty() )
      {
         if( !setCharacteristic.insert( strAllocAccountNum ).second )
         {
            ADDCONDITIONFROMFILE( CND::ERR_IDENTICAL_ACCT_DEFAULT_ALLOCS );
            break;
         }
      }
      ++iter; 
   }

   iter.begin();
   AcctAlloc *pAccountAllocation;
   FundAllocList *pFundAllocationList;
   while( !iter.end() )
   {
      pAccountAllocation = dynamic_cast<AcctAlloc *>(iter.getObject());
      if( pAccountAllocation )
      {
         pAccountAllocation->getFundAllocationList ( pFundAllocationList, idDataGroup, false, false );
         if( pFundAllocationList )
         {
            pFundAllocationList->validateAll( idDataGroup, lValidateGroup );
         }
      }
      ++iter;
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY AcctAllocList::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );
   if( AbstractAllocList::doApplyRelatedChanges( idField, idDataGroup ) > WARNING )
      return(GETCURRENTHIGHESTSEVERITY());

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY AcctAllocList::setListFields(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setListFields" ) );

   AbstractAllocList::setListFields(idDataGroup);

   BFCBO *pParent = NULL;
   pParent = getParent();
   assert(pParent);
   DString str;

   setFieldFromCBO(pParent, ifds::TransType, ifds::TransType, idDataGroup, str);
   setFieldFromCBO(pParent, ifds::EffectiveDate, ifds::EffectiveDate, idDataGroup, str);
   setFieldFromCBO(pParent, ifds::Amount, ifds::Amount, idDataGroup, str);
   setFieldFromCBO(pParent, ifds::AmountType, ifds::AllocAmtType, idDataGroup, str);
   setFieldFromCBO(pParent, ifds::FromFund, ifds::FromFund, idDataGroup, str);
   setFieldFromCBO(pParent, ifds::FromClass, ifds::FromClass, idDataGroup, str);
   setFieldFromCBO(pParent, ifds::SettleCurrency, ifds::Currency, idDataGroup, str);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY AcctAllocList::getDefaultAllocList(AbstractAllocList*& pDefaultAllocationList, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getDefaultFundAllocList"));

   pDefaultAllocationList = NULL;
   getShrDefAllocList(pDefaultAllocationList, idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY AcctAllocList::hasInternationalWireAlloc(const DString& strSettleCurrency, const DString& strCountryCode,
                                                  bool &bIsInternationalWire, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("hasInternationalWireAlloc"));

   DString strTransType, strPayMethod;
   getField(ifds::TransType, strTransType, idDataGroup, false);
   getTopLevelCBO()->getField(ifds::PayMethod, strPayMethod, idDataGroup, false);
   if( !isMultiCurrency() || strTransType != REDEMPTION_CODE || strPayMethod != WIRE )
      return(GETCURRENTHIGHESTSEVERITY());

   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() )
   {
      AcctAlloc *pAcctAlloc = NULL;
      pAcctAlloc = dynamic_cast<AcctAlloc*>(iter.getObject());
      if( pAcctAlloc )
      {
         pAcctAlloc->hasInternationalWireFundAlloc(strSettleCurrency, strCountryCode, bIsInternationalWire, idDataGroup);
         if( bIsInternationalWire )
            break;
      }
      ++iter;
   }
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY AcctAllocList::getShrDefAllocList(AbstractAllocList* &pDefaultAllocationList, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getShrDefAllocList" ) );

   pDefaultAllocationList = NULL;

   DString strAccountNum, strTransType;
   getField(ifds::AccountNum, strAccountNum, idDataGroup, false);
   MFAccount* pMFAccount = NULL;
   if( getWorkSession().getMFAccount( idDataGroup, strAccountNum, pMFAccount) > WARNING || !pMFAccount)
      return(GETCURRENTHIGHESTSEVERITY());

   DString dstrShrNum;
   pMFAccount->getField( ifds::ShrNum, dstrShrNum, idDataGroup, true);
   Shareholder* pShareholder = NULL;
   if( getWorkSession().getShareholder( idDataGroup, dstrShrNum, pShareholder) > WARNING || !pShareholder)
      return(GETCURRENTHIGHESTSEVERITY());

   ShrAllocTypeList* pShrAllocTypeList = NULL;
   if( pShareholder->getAllocationList(pShrAllocTypeList, idDataGroup) > WARNING || !pShrAllocTypeList )
      return(GETCURRENTHIGHESTSEVERITY());

   getField(ifds::TransType, strTransType, idDataGroup, false);

   DefAcctAllocList* pDefAcctAllocList = NULL;
   pShrAllocTypeList->getDefaultAcctAllocList(strTransType, pDefAcctAllocList, idDataGroup, strAccountNum);
   pDefaultAllocationList = pDefAcctAllocList;

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY AcctAllocList::getRebalDefAllocList(AbstractAllocList* &pDefaultAllocationList, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getRebalDefAllocList" ) );

   pDefaultAllocationList = NULL;

   DString strAccountNum, strTransType(AMS_REBALANCING);
   getField(ifds::AccountNum, strAccountNum, idDataGroup, false);
   MFAccount* pMFAccount = NULL;
   if( getWorkSession().getMFAccount( idDataGroup, strAccountNum, pMFAccount) > WARNING || !pMFAccount)
      return(GETCURRENTHIGHESTSEVERITY());

   DString dstrShrNum;
   pMFAccount->getField( ifds::ShrNum, dstrShrNum, idDataGroup, true);
   Shareholder* pShareholder = NULL;
   if( getWorkSession().getShareholder( idDataGroup, dstrShrNum, pShareholder) > WARNING || !pShareholder)
      return(GETCURRENTHIGHESTSEVERITY());

   ShrAllocTypeList* pShrAllocTypeList = NULL;
   if( pShareholder->getAllocationList(pShrAllocTypeList, idDataGroup) > WARNING || !pShrAllocTypeList )
      return(GETCURRENTHIGHESTSEVERITY());


   DefAcctAllocList* pDefAcctAllocList = NULL;
   pShrAllocTypeList->getDefaultAcctAllocList(strTransType, pDefAcctAllocList, idDataGroup, strAccountNum);
   pDefaultAllocationList = pDefAcctAllocList;

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY AcctAllocList::getAMSDefAllocList(AbstractAllocList* &pAllocListForDefault, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getAMSDefAllocList" ) );
   pAllocListForDefault = NULL;
   DString strAccountNum;
   getField(ifds::AccountNum, strAccountNum, idDataGroup, false);
   MFAccount* pMFAccount = NULL;
   if( getWorkSession().getMFAccount( idDataGroup, strAccountNum, pMFAccount) > WARNING || !pMFAccount)
      return(GETCURRENTHIGHESTSEVERITY());

   pMFAccount->getAMSAcctAllocList(pAllocListForDefault, idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctAllocList.cpp-arc  $
// 
//    Rev 1.14   Nov 01 2004 15:20:24   YINGBAOL
// PTS10045342: Fix Round up issue for amount
// 
//    Rev 1.13   Mar 21 2003 17:55:44   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.12   Nov 29 2002 10:45:04   KOVACSRO
// added suport for AMS rebalancing and AMS account level allocation.
// 
//    Rev 1.11   Nov 26 2002 10:44:58   HERNANDO
// Changed function call as a result of changing ShrAllocTypeList::getDefaultAcctAllocList parameters.
// 
//    Rev 1.10   Nov 18 2002 13:44:04   KOVACSRO
// getDefaultAllocList will get now the latest one that contains the account specified by AccountNum field (day 1 bug fixed)
// 
//    Rev 1.9   Oct 09 2002 23:53:56   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.8   Aug 29 2002 12:54:56   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.7   Jun 27 2002 17:19:12   KOVACSRO
// AllocAmtType versus AmountType.
// 
//    Rev 1.6   Jun 20 2002 13:36:08   KOVACSRO
// International wire modifications.
// 
//    Rev 1.5   Jun 07 2002 17:41:50   KOVACSRO
// International Wire modifications.
// 
//    Rev 1.4   22 May 2002 18:26:18   PURDYECH
// BFData Implementation
// 
//    Rev 1.3   08 May 2002 16:51:36   KOVACSRO
// More implementation.
// 
//    Rev 1.2   29 Apr 2002 16:21:26   KOVACSRO
// Added getDefaultAllocList()
// 
//    Rev 1.1   12 Apr 2002 16:52:24   KOVACSRO
// More implementation.
 * 
 * 
 */