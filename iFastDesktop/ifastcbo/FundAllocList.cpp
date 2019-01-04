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
// ^FILE   : FundAllocList.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 25/03/02
//
// ^CLASS    : FundAllocList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : common interface for all the fund allocation lists
//
//******************************************************************************
#include "stdafx.h"

#include "AmsFundAllocList.hpp"
#include "deffundalloclist.hpp"
#include "fundalloc.hpp"
#include "fundalloclist.hpp"
#include "funddetail.hpp"
#include "mfaccount.hpp"
#include "shareholder.hpp"
#include "shralloctypelist.hpp"
#include "splitcommissionlist.hpp"

namespace
{
   const I_CHAR * const CLASSNAME         = I_( "FundAllocList" );
   const I_CHAR * const NO                = I_( "N" );
   const I_CHAR * const YES               = I_( "Y" );
   const I_CHAR * const AMS_REBALANCING   = I_( "RB" );   //TransType AMS Rebalancing

}

namespace CND
{
   extern const long ERR_IDENTICAL_FUND_ALLOCS;
   extern const long ERR_FUND_CURRENCY_DIFFERENT;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FundCode;
   extern CLASS_IMPORT const BFTextFieldId ClassCode;
   extern CLASS_IMPORT const BFTextFieldId Currency;

   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFTextFieldId AllocAmtType;
   extern CLASS_IMPORT const BFDecimalFieldId Amount;
   extern CLASS_IMPORT const BFTextFieldId SplitComm;
   extern CLASS_IMPORT const BFDecimalFieldId AllocAmount;
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
   extern CLASS_IMPORT const BFTextFieldId Default;
   extern CLASS_IMPORT const BFTextFieldId ReplaceAsDefault;
   extern CLASS_IMPORT const BFTextFieldId FromFund;
   extern CLASS_IMPORT const BFTextFieldId FromClass;
   extern CLASS_IMPORT const BFTextFieldId SettleCurrency;
   extern CLASS_IMPORT const BFTextFieldId AmountType;

}
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//		Field DD Id,				State Flags,					Group Flags
   { ifds::ReplaceAsDefault, BFCBO::NONE, 0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) 
                              / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
FundAllocList::FundAllocList( BFAbstractCBO &parent ) 
: AbstractAllocList( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   setObjectAsList();
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0, NULL );
}

//******************************************************************************
FundAllocList::~FundAllocList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY FundAllocList::initNew( const BFDataGroupId& idDataGroup,
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

SEVERITY FundAllocList::clearAllocations( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "clearAllocations" ) );

   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   iter.begin();
   while( !iter.end() )
   {
      FundAlloc *pFundAlloc = NULL;
      pFundAlloc = dynamic_cast<FundAlloc*>(iter.getObject());
      if( pFundAlloc )
      {
         SplitCommissionList *pSplitCommissionList = NULL;
         pFundAlloc->getSplitCommissionList ( pSplitCommissionList, idDataGroup );
         if( pSplitCommissionList )
            pSplitCommissionList->deleteSplitCommList(idDataGroup);
      }
      iter.deleteObject();
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY FundAllocList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup,
                                      bool bSkip100PercentValidation /*default to false*/) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   if ( !bSkip100PercentValidation )
      AbstractAllocList::doValidateAll( idDataGroup, lValidateGroup );

   //no identical allocations allowed
   std::set< DString > setCharacteristic;
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() )
   {
      DString strAllocFundCode, strAllocClassCode;
      iter.getObject()->getField(ifds::FundCode, strAllocFundCode, idDataGroup, false);
      iter.getObject()->getField(ifds::ClassCode, strAllocClassCode, idDataGroup, false);
      DString strNewEntry = strAllocFundCode.strip().upperCase() + strAllocClassCode.strip().upperCase();

      if( !setCharacteristic.insert( strNewEntry ).second )
      {
         ADDCONDITIONFROMFILE( CND::ERR_IDENTICAL_FUND_ALLOCS );
         break;
      }
      ++iter; 
   }
   
   iter.begin();

   bool bhasAllocations = iter.getNumberOfItemsInList () > 1; //1 means 100% allocation, logic from Trade

   while( !iter.end() )
   {
      FundAlloc* pFundAlloc = dynamic_cast <FundAlloc*>(iter.getObject());
      assert(pFundAlloc);
      // validate split commission
      DString dstrSplitComm;
      pFundAlloc->getField ( ifds::SplitComm, dstrSplitComm, idDataGroup, false );
      if( dstrSplitComm == YES )
      {
         SplitCommissionList *pSplitCommissionList;
         pFundAlloc->getSplitCommissionList ( pSplitCommissionList, idDataGroup, false );
         if( pSplitCommissionList )
            pSplitCommissionList->validateAll( idDataGroup, lValidateGroup );
      }
	
	  if(bhasAllocations)
	  {
          pFundAlloc->validateParentFundClass(idDataGroup);
	  }

      ++iter;
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY FundAllocList::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );
   if( AbstractAllocList::doApplyRelatedChanges( idField, idDataGroup ) > WARNING )
      return(GETCURRENTHIGHESTSEVERITY());

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY FundAllocList::validateMulticurrency(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateMulticurrency" ) );

   DString strPreviousCurrency(NULL_STRING);;

   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() )
   {
      DString strAllocFundCode, strAllocClassCode, dstrCurrency;
      iter.getObject()->getField(ifds::FundCode, strAllocFundCode, idDataGroup, false);
      iter.getObject()->getField(ifds::ClassCode, strAllocClassCode, idDataGroup, false);

      FundDetail *pFundDetail = NULL;

      if( getFundDetail( strAllocFundCode.strip().upperCase(), strAllocClassCode.strip().upperCase(), 
                         pFundDetail)<=WARNING && pFundDetail )
         pFundDetail->getField( ifds::Currency, dstrCurrency, idDataGroup, false );

      if( !dstrCurrency.strip().upperCase().empty() )
      {
         if( strPreviousCurrency.empty() )
            strPreviousCurrency = dstrCurrency;
         else if( strPreviousCurrency != dstrCurrency )
         {
            ADDCONDITIONFROMFILE( CND::ERR_FUND_CURRENCY_DIFFERENT );
            break;
         }
      }
      ++iter; 
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY FundAllocList::setListFields(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setListFields" ) );

   AbstractAllocList::setListFields(idDataGroup);

   BFCBO *pParent = NULL;
   pParent = getParent();
   assert(pParent);
   DString str;

   setFieldFromCBO(pParent, ifds::AccountNum, ifds::AccountNum, idDataGroup, str);
   setFieldFromCBO(pParent, ifds::TransType, ifds::TransType, idDataGroup, str);
   setFieldFromCBO(pParent, ifds::EffectiveDate, ifds::EffectiveDate, idDataGroup, str);
   if( getParentAllocation() )//this is not the first level allocation
   {
      setFieldFromCBO(pParent, ifds::AllocAmount, ifds::Amount, idDataGroup, str);//use AllocAmount field
      pParent = getParentList();
      setFieldFromCBO(pParent, ifds::FromFund, ifds::FromFund, idDataGroup, str);
      setFieldFromCBO(pParent, ifds::FromClass, ifds::FromClass, idDataGroup, str);
      setFieldFromCBO(pParent, ifds::Currency, ifds::Currency, idDataGroup, str);//use Currency field
      setFieldFromCBO(pParent, ifds::AllocAmtType, ifds::AllocAmtType, idDataGroup, str);
   }
   else//else this is the first level allocation
   {
      setFieldFromCBO(pParent, ifds::Amount, ifds::Amount, idDataGroup, str);//use Amount field
      setFieldFromCBO(pParent, ifds::FromFund, ifds::FromFund, idDataGroup, str);
      setFieldFromCBO(pParent, ifds::FromClass, ifds::FromClass, idDataGroup, str);
      setFieldFromCBO(pParent, ifds::SettleCurrency, ifds::Currency, idDataGroup, str);//use SettleCurrency field
      setFieldFromCBO(pParent, ifds::AmountType, ifds::AllocAmtType, idDataGroup, str);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY FundAllocList::createSplitCommLists ( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "createSplitCommLists" ) );

   SplitCommissionList *pSplitCommissionList = NULL;
   FundAlloc *pFundAllocation;
   DString dstrSplitComm;
   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
   while( !iter.end() )
   {
      pFundAllocation = static_cast <FundAlloc*>(iter.getObject());
      pFundAllocation->getField ( ifds::SplitComm, dstrSplitComm, idDataGroup, false );
      if( dstrSplitComm == YES )
         pFundAllocation->getSplitCommissionList( pSplitCommissionList, idDataGroup );
      ++iter;
   }
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

void FundAllocList::setDefaultSplitCommFlags( const BFDataGroupId& idDataGroup )
{
   SplitCommissionList *pSplitCommissionList = NULL;
   FundAlloc *pFundAllocation;
   DString dstrSplitComm;
   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
   while( !iter.end() )
   {
      pFundAllocation = static_cast <FundAlloc*>(iter.getObject());
      pFundAllocation->setField ( ifds::Default, YES, idDataGroup, false );
      ++iter;
   }
}

//******************************************************************************

SEVERITY FundAllocList::getDefaultAllocList(AbstractAllocList*& pDefaultAllocationList, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getDefaultFundAllocList"));

   pDefaultAllocationList = NULL;
   getShrDefAllocList(pDefaultAllocationList, idDataGroup);
   
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

void FundAllocList::getAllocCurrency( DString& dstrFundAllocCurrency, const BFDataGroupId& idDataGroup)
{
   DString strPreviousCurrency(NULL_STRING);
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() )
   {
      DString strAllocFundCode, strAllocClassCode, dstrCurrency;
      iter.getObject()->getField(ifds::FundCode, strAllocFundCode, idDataGroup, false);
      iter.getObject()->getField(ifds::ClassCode, strAllocClassCode, idDataGroup, false);

      FundDetail *pFundDetail = NULL;

      if( getFundDetail( strAllocFundCode.strip().upperCase(), strAllocClassCode.strip().upperCase(), pFundDetail)<=WARNING && pFundDetail )
         pFundDetail->getField( ifds::Currency, dstrCurrency, idDataGroup, false );

      if( !dstrCurrency.strip().upperCase().empty() )
      {
         if( strPreviousCurrency.empty() )
            strPreviousCurrency = dstrCurrency;
         else if( strPreviousCurrency != dstrCurrency )
         {
            dstrFundAllocCurrency = NULL_STRING;
            return;
         }
      }
      ++iter; 
   }
   dstrFundAllocCurrency = strPreviousCurrency;
}
//******************************************************************************

SEVERITY FundAllocList::hasInternationalWireAlloc(const DString& strSettleCurrency, const DString& strCountryCode,
                                                  bool &bIsInternationalWire, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("hasInternationalWireAlloc"));

   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() )
   {
      FundAlloc *pFundAlloc = NULL;
      pFundAlloc = dynamic_cast<FundAlloc*>(iter.getObject());
      if( pFundAlloc )
      {
         pFundAlloc->isInternationalWire(strSettleCurrency, strCountryCode, bIsInternationalWire, idDataGroup);
         if( bIsInternationalWire )
            break;
      }
      ++iter;
   }
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY FundAllocList::getShrDefAllocList(AbstractAllocList* &pDefaultAllocationList, const BFDataGroupId& idDataGroup)
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
   DefFundAllocList* pDefFundAllocList = NULL;
   if (pShrAllocTypeList->getDefaultFundAllocList(strTransType.strip().upperCase(), strAccountNum, 
      pDefFundAllocList, idDataGroup) <= WARNING)
      pDefaultAllocationList = pDefFundAllocList;

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY FundAllocList::getRebalDefAllocList(AbstractAllocList* &pDefaultAllocationList, const BFDataGroupId& idDataGroup)
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


   DefFundAllocList* pDefFundAllocList = NULL;
   if (pShrAllocTypeList->getDefaultFundAllocList(strTransType, strAccountNum, pDefFundAllocList, 
      idDataGroup) <= WARNING)
      pDefaultAllocationList = pDefFundAllocList;

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY FundAllocList::getAMSDefAllocList(AbstractAllocList* &pDefaultAllocationList, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getAMSDefAllocList" ) );

   pDefaultAllocationList = NULL;

   DString strAccountNum;
   getField(ifds::AccountNum, strAccountNum, idDataGroup, false);
   MFAccount* pMFAccount = NULL;
   if( getWorkSession().getMFAccount( idDataGroup, strAccountNum, pMFAccount) > WARNING || !pMFAccount)
      return(GETCURRENTHIGHESTSEVERITY());

   AmsFundAllocList *pAmsFundAllocList = NULL;
   DString dstrEffectiveDate;
   getField ( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup );   
   if (pMFAccount->getAMSFundAllocList( I_("RB"), dstrEffectiveDate, pAmsFundAllocList, idDataGroup) <= WARNING)
      pDefaultAllocationList = pAmsFundAllocList;

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

bool FundAllocList::isMarginEligible(const BFDataGroupId& idDataGroup)
{
   //rule: if there is at least one non margin eligible allocation, the list is not eligible
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() )
   {
      FundAlloc *pFundAlloc = NULL;
      pFundAlloc = dynamic_cast<FundAlloc*>(iter.getObject());
      assert(pFundAlloc);
      if (!pFundAlloc->isMarginEligible(idDataGroup))
         return false;
      ++iter;
   }
   //consider an empty list as being margin eligible
   return true;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundAllocList.cpp-arc  $
// 
//    Rev 1.19   Nov 14 2004 14:41:20   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.18   Aug 25 2003 18:19:52   WINNIE
// Full Redemption Code enhancement : Add new input parameter to indicate skipping the validation in AbstractAllocList which perform the total percentage validation 
// 
//    Rev 1.17   Aug 21 2003 17:21:46   HSUCHIN
// change getAMSFundAllocList calling method
// 
//    Rev 1.16   Aug 15 2003 15:25:42   HSUCHIN
// change getAMSDefAllocList to pass RB as AMS Type
// 
//    Rev 1.15   Mar 21 2003 18:10:30   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.14   Feb 12 2003 16:45:10   KOVACSRO
// Added isMarginEligible()
// 
//    Rev 1.13   Dec 31 2002 13:50:18   KOVACSRO
// removed multicurrency check since it does not apply for all the allocations anymore.
// 
//    Rev 1.12   Dec 02 2002 15:14:30   KOVACSRO
// very minor changes.
// 
//    Rev 1.11   Nov 29 2002 10:46:56   KOVACSRO
// Added support for different kind of default allocations.
// 
//    Rev 1.10   Nov 18 2002 13:40:04   KOVACSRO
// Checking for NULL pointer.
// 
//    Rev 1.9   Oct 09 2002 23:54:30   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.8   Aug 29 2002 12:55:52   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.7   Jun 27 2002 17:19:50   KOVACSRO
// AllocAmtType versus AmountType.
// 
//    Rev 1.6   Jun 20 2002 13:38:00   KOVACSRO
// multicurrency
// 
//    Rev 1.5   Jun 07 2002 17:45:50   KOVACSRO
// International Wire modifications.
// 
//    Rev 1.4   22 May 2002 18:28:42   PURDYECH
// BFData Implementation
// 
//    Rev 1.3   08 May 2002 16:53:26   KOVACSRO
// More implementation.
// 
//    Rev 1.2   29 Apr 2002 16:24:36   KOVACSRO
// Added a few more methods.
// 
//    Rev 1.1   12 Apr 2002 16:58:16   KOVACSRO
// More implementation.
 * 
 * 
 */