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
// ^FILE   : DefAcctAllocList.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 27/03/02
//
// ^CLASS    : DefAcctAllocList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : Default account allocation list
//
//******************************************************************************
#include "stdafx.h"
#include "defacctalloc.hpp"
#include "defacctalloclist.hpp"
#include "deffundalloclist.hpp"
#include "shralloctype.hpp"
#include "shralloctypelist.hpp"

namespace
{
   const I_CHAR * const CLASSNAME  = I_( "DefAcctAllocList" );
   const I_CHAR * const ACCT_LEVEL = I_( "2" );
   const I_CHAR * const MANAGEMENT_FEE_CODE = I_( "MF" );
}

namespace CND
{
   extern const long ERR_IDENTICAL_ACCT_DEFAULT_ALLOCS;
   extern const long ERR_ACCT_ALLOC_LIST_MANAGEMENT_FEE;
}

namespace ifds
{
   extern CLASS_IMPORT const BFDecimalFieldId Level;
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFTextFieldId rxTransTypeJapanese;
   extern CLASS_IMPORT const BFTextFieldId rxTransType;
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;

}


//******************************************************************************
DefAcctAllocList::DefAcctAllocList( BFAbstractCBO &parent ) 
: AcctAllocList( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   setObjectAsList();

}

//******************************************************************************
DefAcctAllocList::~DefAcctAllocList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************

SEVERITY DefAcctAllocList::initExisting( const DString& dstrTrack ,
                                         const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initExisting" ) );

   setListFields(BF::HOST);

   const BFData* pView58 = NULL;
   ShrAllocTypeList* pParentShrAllocList = getShrAllocTypeList();
   pView58 = pParentShrAllocList->getView58();
   assert(pView58);

   int cRepeats = pView58->getRepeatCount();

   for( int i = 0; i < cRepeats; i++ )
   {
      const BFData &data = pView58->getRepeat( i );
      DString strLevel = data.getElementValue( ifds::Level );
      if( strLevel.strip() == ACCT_LEVEL )
      {
         DString dstrTransType, dstrEffectiveDate, strTemp;
         BFCBO* pShrAllocType = getTopLevelCBO();
         pShrAllocType->getField(ifds::TransType, dstrTransType, BF::HOST, false);
         strTemp = data.getElementValue( ifds::TransType );
			DString dstrPAccount,dstrCAccount;
         pShrAllocType->getField(ifds::AccountNum, dstrPAccount, BF::HOST, false);
			dstrPAccount.strip().stripLeading('0');			
			dstrCAccount = data.getElementValue( ifds::AccountNum );
			dstrCAccount.strip().stripLeading('0');
			
			DString dstrPEffective,dstrCEffective;
         pShrAllocType->getField(ifds::EffectiveDate, dstrPEffective, BF::HOST, false);
			dstrPEffective.strip();			
			dstrCEffective = data.getElementValue( ifds::EffectiveDate );
			dstrCEffective.strip();

         if( strTemp.strip() == dstrTransType.strip() && dstrCAccount == dstrPAccount )
         {
            pShrAllocType->getField(ifds::EffectiveDate, dstrEffectiveDate, BF::HOST, false);
            strTemp = data.getElementValue( ifds::EffectiveDate );
            if( strTemp.strip() == dstrEffectiveDate.strip() )
            {
               DString dstrKeyAlloc;
               getStrKey( dstrKeyAlloc, &data );
               assert(!dstrKeyAlloc.empty());
               DefAcctAlloc *pAllocation = new DefAcctAlloc( *this );
               setObject( pAllocation, dstrKeyAlloc, OBJ_ACTIVITY_NONE, BF::HOST );
               pAllocation->initExisting( data );
            }
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY DefAcctAllocList::addNewAllocation( const DString& strKey, 
                                             const BFDataGroupId& idDataGroup,
                                             bool bGetDefault, 
                                             bool bCopyParent,
                                             bool bAddChildren)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "addNewAllocation" ) );
   assert(!bGetDefault);//shouldn't be called with bGetDefault set to true; this is the default allocation
   assert(!bCopyParent);//it doesn't apply for default allocations to copy data from parent
   BFObjectKey objKey( strKey, idDataGroup );
   DString strKeyCopy(strKey);
   if( !strKeyCopy.strip().empty() )
      m_strKeyForNewItem = strKey;
   BFCBO * pNewObject = getNewListItem( objKey );
   m_strKeyForNewItem = NULL_STRING;

   if( bAddChildren )
   {
      DefAcctAlloc *pNewDefAcctAlloc = dynamic_cast<DefAcctAlloc*>(pNewObject);
      assert(pNewDefAcctAlloc);
      DefFundAllocList *pFundAllocList;
      pNewDefAcctAlloc->getFundAllocationList(pFundAllocList, idDataGroup, true, false);
      if( pFundAllocList )
         pFundAllocList->addNewAllocation(strKey, idDataGroup, bGetDefault, bCopyParent, bAddChildren);
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY DefAcctAllocList::addExistingAllocation( const DString& strKey, 
                                                  const BFDataGroupId& idDataGroup,
                                                  bool bAddChildren)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "addExistingAllocation" ) );
   assert(0);//doesn't make sens to call this method
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY DefAcctAllocList::initDefaultAllocationList(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initDefaultAllocationList" ) );
   assert(0);
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY DefAcctAllocList::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );
   if( AcctAllocList::doApplyRelatedChanges( idField, idDataGroup ) > WARNING )
      return(GETCURRENTHIGHESTSEVERITY());

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY DefAcctAllocList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   //check for empty list : if it is empty is OK as long parent is dummy
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   if( iter.end() || iter.isDummy() )
   {
      if (getTopLevelCBO()->getNonDummyFlag())
         return(GETCURRENTHIGHESTSEVERITY());
   }

   if( AcctAllocList::doValidateAll( idDataGroup, lValidateGroup )>WARNING )
      return(GETCURRENTHIGHESTSEVERITY());

   // Management Fee Check
   if( iter.getNumberOfItemsInList() > 1 )
   {
      DString dstrTransType;
      getField( ifds::TransType, dstrTransType, idDataGroup, false );
      if( dstrTransType == MANAGEMENT_FEE_CODE )
      {
         ADDCONDITIONFROMFILE( CND::ERR_ACCT_ALLOC_LIST_MANAGEMENT_FEE );
      }
   }

   //rule: backend wants us to send for ShrAllocType AccountNum = 0 if there are multiple account allocations
   //and the actual AccountNum if there is only one
   BFCBO* pParent = getParent();
   assert(pParent);
   DString strAccountNum = I_("0");
   iter.begin();
   if( iter.getNumberOfItemsInList() == 1 )
      iter.getObject()->getField(ifds::AccountNum, strAccountNum, idDataGroup, false);

   pParent->setField(ifds::AccountNum, strAccountNum, idDataGroup, false);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY DefAcctAllocList::doCreateNewObject( BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   DefAcctAlloc *pAllocation = new DefAcctAlloc( *this );
   pAllocation->initNew( idDataGroup );
   pBase = pAllocation;
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

ShrAllocTypeList* DefAcctAllocList::getShrAllocTypeList()
{
   ShrAllocTypeList* pParent = dynamic_cast<ShrAllocTypeList*>(getParent()->getParent());
   assert(pParent);
   return(pParent);
}

//******************************************************************************

SEVERITY DefAcctAllocList::loadSubstitutions( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "loadSubstitutions" ) );

   if( DSTCommonFunctions::getMarket() == MARKET_IDS::JAPAN )
      setFieldSubstituteValues( ifds::TransType, idDataGroup, ifds::rxTransTypeJapanese );
   else  // for Canada and any other market
      setFieldSubstituteValues( ifds::TransType, idDataGroup, ifds::rxTransType);

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DefAcctAllocList.cpp-arc  $
// 
//    Rev 1.11   Nov 14 2004 14:30:26   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.10   Feb 12 2004 15:54:12   YINGBAOL
// PTS 10021233: Multi allocation at account level is not been supported
// 
//    Rev 1.9   Apr 25 2003 14:26:48   HERNANDO
// Prudential Broker Level Fee - PET792.FN07.2 - modified doValidateAll.
// 
//    Rev 1.8   Mar 21 2003 18:02:46   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.7   Nov 28 2002 13:44:08   KOVACSRO
// Added dummy item logic in doValidateAll.
// 
//    Rev 1.6   Oct 09 2002 23:54:12   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.5   Aug 29 2002 12:55:16   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.4   Jul 31 2002 14:56:36   KOVACSRO
// new item key fix.
// 
//    Rev 1.3   22 May 2002 18:26:44   PURDYECH
// BFData Implementation
// 
//    Rev 1.2   10 May 2002 11:57:28   KOVACSRO
// Added addExistingAllocation()
// 
//    Rev 1.1   12 Apr 2002 16:54:50   KOVACSRO
// More implementation.
 * 
 * 
 */