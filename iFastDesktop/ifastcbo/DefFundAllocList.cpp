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
// ^FILE   : DefFundAllocList.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 27/03/02
//
// ^CLASS    : DefFundAllocList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : default fund allocation list
//
//******************************************************************************
#include "stdafx.h"
#include "defacctalloc.hpp"
#include "deffundalloc.hpp"
#include "deffundalloclist.hpp"
#include "shralloctype.hpp"
#include "shralloctypelist.hpp"
#include "mgmtcooptions.hpp"
#include "mgmtco.hpp"

namespace
{
   const I_CHAR * const CLASSNAME = I_( "DefFundAllocList" );
   const I_CHAR * const NO = I_( "N" );
   const I_CHAR * const FUND_LEVEL = I_( "3" );
   const I_CHAR * const FOREIGN_CONTENT_REBALANCING= I_( "XS" );
   const I_CHAR * const MANAGEMENT_FEE_CODE        = I_( "MF" );
   const I_CHAR * const YES                        = I_( "Y" );
	const I_CHAR * const REBALANCE						= I_("RB");
	const I_CHAR * const REPORT							= I_("RO");
}

namespace CND
{
   extern const long ERR_FUND_ALLOC_LIST_MANAGEMENT_FEE;

}

namespace ifds
{  
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFDecimalFieldId Level;
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFTextFieldId rxTransTypeJapanese;
   extern CLASS_IMPORT const BFTextFieldId rxTransType;
   extern CLASS_IMPORT const BFTextFieldId FundGroup;
   extern CLASS_IMPORT const BFTextFieldId CommonCurrency;

}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//		Field DD Id,				State Flags,					Group Flags
   { ifds::FundGroup, BFCBO::NONE, 0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) 
                              / sizeof( BFCBO::CLASS_FIELD_INFO );
//******************************************************************************
DefFundAllocList::DefFundAllocList( BFAbstractCBO &parent ) 
: FundAllocList( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   setObjectAsList();
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0, NULL );
}

//******************************************************************************
DefFundAllocList::~DefFundAllocList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}
//******************************************************************************

SEVERITY DefFundAllocList::initExisting(const DString& dstrTrack,
                                        const DString& dstrPageName)
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
      if( strLevel.strip() == FUND_LEVEL )
      {
         DString dstrTransType, dstrEffectiveDate, strTemp;
         BFCBO* pShrAllocType = getTopLevelCBO();//ShrAllocType
         pShrAllocType->getField(ifds::TransType, dstrTransType, BF::HOST, false);
         strTemp = data.getElementValue( ifds::TransType );
         if( strTemp.strip() == dstrTransType.strip() )
         {
            pShrAllocType->getField(ifds::EffectiveDate, dstrEffectiveDate, BF::HOST, false);
            strTemp = data.getElementValue( ifds::EffectiveDate );
            if( strTemp.strip() == dstrEffectiveDate.strip() )
            {
               DefAcctAlloc* pDefAlloc = dynamic_cast<DefAcctAlloc*>(getParentAllocation());
               assert(pDefAlloc);
               DString dstrAccountNum;
               pDefAlloc->getField(ifds::AccountNum, dstrAccountNum, BF::HOST, false);
               strTemp = data.getElementValue( ifds::AccountNum );
               if( strTemp.strip() == dstrAccountNum.strip() )
               {
                  DString dstrKeyAlloc;
                  getStrKey( dstrKeyAlloc, &data );
                  assert(!dstrKeyAlloc.empty());
                  DefFundAlloc *pAllocation = new DefFundAlloc( *this );
                  setObject( pAllocation, dstrKeyAlloc, OBJ_ACTIVITY_NONE, BF::HOST );
                  pAllocation->initExisting( data );
               }
            }
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY DefFundAllocList::addNewAllocation( const DString& strKey, 
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
   getNewListItem( objKey );
   m_strKeyForNewItem = NULL_STRING;

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY  DefFundAllocList::addExistingAllocation( const DString& strKey, 
                                                   const BFDataGroupId& idDataGroup,
                                                   bool bAddChildren)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "addExistingAllocation" ) );
   assert(0);//doesn't make sens to call this method
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY DefFundAllocList::doCreateNewObject( BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   DefFundAlloc *pAllocation = new DefFundAlloc( *this );
   pAllocation->initNew( idDataGroup );
   pBase = pAllocation;
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY DefFundAllocList::initDefaultAllocationList(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initDefaultAllocationList" ) );

   assert(0);//this is the default allocation list

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY DefFundAllocList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   //check for empty list : if it is empty is OK as long parents are dummy
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   if( iter.end() || iter.isDummy() )
   {
      if (getParentAllocation()->getNonDummyFlag() && getTopLevelCBO()->getNonDummyFlag())
         return(GETCURRENTHIGHESTSEVERITY());
   }

   FundAllocList::doValidateAll( idDataGroup, lValidateGroup );
   DString dstrTransType;
   getField( ifds::TransType, dstrTransType, idDataGroup, false );
	dstrTransType.strip().upperCase();

   // Management Fee Check
   if( iter.getNumberOfItemsInList() > 1 )
   {
      if( dstrTransType == MANAGEMENT_FEE_CODE )
      {
         ADDCONDITIONFROMFILE( CND::ERR_FUND_ALLOC_LIST_MANAGEMENT_FEE );
      }
   }
   DString dstrCommonCurrency;
   getWorkSession().getMgmtCoOptions()->getField( ifds::CommonCurrency, dstrCommonCurrency, idDataGroup ,false );	
	dstrCommonCurrency.strip().upperCase();
	bool bNoCheck = dstrCommonCurrency == YES && dstrTransType == REBALANCE || dstrTransType == REPORT;
		
		//for non multicurrency env., issue an error if not all the currencies are the same
   if( !isMultiCurrency() && !bNoCheck  )  // for Rebalance, check multi currency is not nessary
      validateMulticurrency(idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY DefFundAllocList::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );
   if( FundAllocList::doApplyRelatedChanges( idField, idDataGroup ) > WARNING )
      return(GETCURRENTHIGHESTSEVERITY());

   if( idField == ifds::FundGroup )
   {
      BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
      while( !iter.end() )
      {
         DString strValue;
         getField(idField, strValue, idDataGroup, false);
         iter.getObject()->setField(idField, strValue, idDataGroup, false);
         ++iter; 
      }
   }

   

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

ShrAllocTypeList* DefFundAllocList::getShrAllocTypeList()
{
   BFCBO* pShrAllocType;
   ShrAllocTypeList* pShrAllocTypeList;
   pShrAllocType = getTopLevelCBO();
   pShrAllocTypeList = dynamic_cast<ShrAllocTypeList*>(pShrAllocType->getParent());
   assert(pShrAllocTypeList);
   return(pShrAllocTypeList);
}

//******************************************************************************

SEVERITY DefFundAllocList::loadSubstitutions( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "loadSubstitutions" ) );

   if( DSTCommonFunctions::getMarket() == MARKET_IDS::JAPAN )
      setFieldSubstituteValues( ifds::TransType, idDataGroup, ifds::rxTransTypeJapanese );
   else  // for Canada and any other market
      setFieldSubstituteValues( ifds::TransType, idDataGroup, ifds::rxTransType);

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY DefFundAllocList::setListFields(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setListFields" ) );

   FundAllocList::setListFields(idDataGroup);
   BFCBO *pParent = NULL;
   pParent = getParent();
   assert(pParent);
   DString str;
   setFieldFromCBO(pParent, ifds::FundGroup, ifds::FundGroup, idDataGroup, str);

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
bool DefFundAllocList::isBankruptcyApplied(const BFDataGroupId& idDataGroup)
{
	bool ret(false);

   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
   iter.begin();

   while( !iter.end() )
   {
	   DefFundAlloc *pDefFundAlloc = dynamic_cast<DefFundAlloc *>(iter.getObject());

	   if(pDefFundAlloc->getBankruptcyAppliedFlag())
	   {
		   ret = true; 
		   break;
	   }

	   ++iter;
   }
   return ret;
}  

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DefFundAllocList.cpp-arc  $
// 
//    Rev 1.16   Jan 31 2012 07:18:44   panatcha
// IN2818924 - DSK_AMS Validation for CDIC
// 
//    Rev 1.15   Nov 14 2004 14:30:34   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.14   Jun 06 2003 13:44:34   YINGBAOL
// PVCS does not check in the latest code
// 
//    Rev 1.13   Jun 06 2003 11:08:02   YINGBAOL
// PTS10017424 implemet logic if AMSType "RO", allow multicurrency fund set up 
// 
//    Rev 1.12   Jun 06 2003 10:37:54   YINGBAOL
// PTS 10017861
// 
//    Rev 1.11   Apr 30 2003 12:11:52   HERNANDO
// Prudential Broker Level Fee - PET792.FN07.2 - modified doValidateAll.
// 
//    Rev 1.10   Mar 21 2003 18:03:00   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.9   Jan 12 2003 18:39:14   KOVACSRO
// Added FundGroup field for FC rebalancing
// 
//    Rev 1.8   Dec 31 2002 13:49:20   KOVACSRO
// added multicurrency check.
// 
//    Rev 1.7   Nov 28 2002 13:44:50   KOVACSRO
// Added dummy item logic in doValidateAll.
// 
//    Rev 1.6   Oct 09 2002 23:54:12   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.5   Aug 29 2002 12:55:16   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.4   Jul 31 2002 14:57:20   KOVACSRO
// new item key fix.
// 
//    Rev 1.3   22 May 2002 18:26:46   PURDYECH
// BFData Implementation
// 
//    Rev 1.2   10 May 2002 11:58:16   KOVACSRO
// Added addExistingAllocation()
// 
//    Rev 1.1   12 Apr 2002 16:57:00   KOVACSRO
// More implementation.
 * 
 * 
 */