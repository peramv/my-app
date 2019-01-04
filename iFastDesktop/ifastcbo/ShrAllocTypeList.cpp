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
// ^FILE   : ShrAllocTypeList.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 25/03/02
//
// ^CLASS    : ShrAllocTypeList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : former shareholder level allocation
//
//******************************************************************************
#include "stdafx.h"
#include "defacctalloclist.hpp"
#include "defacctalloc.hpp"
#include "deffundalloclist.hpp"
#include "funddetail.hpp"
#include "funddetaillist.hpp"
#include "mfaccount.hpp"
#include "mfaccountlist.hpp"
#include "mgmtcooptions.hpp"
#include "shareholder.hpp"
#include "shralloctype.hpp"
#include "shralloctypelist.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0058_vw.hpp>
#include <ifastdataimpl\dse_dstc0058_req.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ALLOCATIONS;
}

namespace
{
   const I_CHAR * const CLASSNAME             = I_( "ShrAllocTypeList" );
   const I_CHAR * const SHR_LEVEL             = I_( "1" );
   const I_CHAR * const ED                    = I_( "ED" );
   const I_CHAR * const DD                    = I_( "DD" );
   const I_CHAR * const P                     = I_( "P" );
   const I_CHAR * const S                     = I_( "S" );
   const I_CHAR * const AW                    = I_( "AW" );
   const I_CHAR * const YES                   = I_( "Y" );
   const I_CHAR * const NO                    = I_( "N" );

}

namespace CND
{
   extern CLASS_IMPORT const long ERR_INVALID_SHAREHOLDER;
   extern const long ERR_IDENTICAL_SHR_DEFAULT_ALLOCS;
}

namespace ifds
{
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFTextFieldId AcctAlloc;
   extern CLASS_IMPORT const BFTextFieldId UpdatePACSWP;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,              State Flags,      Group Flags 
   {ifds::ShrNum,     BFCBO::NONE,             0}, 
   {ifds::UpdatePACSWP,     BFCBO::NONE,             0}, 
   
};

static const int NUM_FIELDS = sizeof (classFieldInfo) / sizeof (BFCBO::CLASS_FIELD_INFO);


//******************************************************************************
ShrAllocTypeList::ShrAllocTypeList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent ),
_pView58Data(NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );

   setObjectAsList();
}

//******************************************************************************
ShrAllocTypeList::~ShrAllocTypeList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
   if( _pView58Data )
      delete _pView58Data;
}

//******************************************************************************

SEVERITY ShrAllocTypeList::initNew( const BFDataGroupId& idDataGroup,
                                    const DString& dstrTrack,
                                    const DString& dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initNew" ) );

   DString strShrNum;
   getParent()->getField(ifds::ShrNum, strShrNum, idDataGroup, false);
// setField(ifds::ShrNum, strShrNum, idDataGroup, false); no class really use this field. change to avoid the object getting dirty
   setFieldNoValidate ( ifds::UpdatePACSWP, NO, BF::HOST, true, true, true, false );
   

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
SEVERITY ShrAllocTypeList::initExisting( const DString& dstrTrack, const DString& dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initExisting" ) );

   BFData requestData(ifds::DSTC0058_REQ); 
   DString strShareholderNum, mgmtCoIdOut;

   getTopLevelCBO()->getField(ifds::ShrNum, strShareholderNum, BF::HOST, false);

   requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   requestData.setElementValue( ifds::ShrNum, strShareholderNum );
   requestData.setElementValue( ifds::Track, dstrTrack );
   requestData.setElementValue( ifds::Activity, dstrPageName );

   _pView58Data = new BFData(ifds::DSTC0058_VW);

   DSTCRequestor requestor( getSecurity() );
   requestor.filterHostCondition(CND::ERR_INVALID_SHAREHOLDER);//??

   if( BFDataBroker::getInstance()->receive( DSTC_REQUEST::ALLOCATIONS, requestData, *_pView58Data, requestor) > WARNING )
   {
      delete _pView58Data;
      _pView58Data = NULL;
      return(GETCURRENTHIGHESTSEVERITY());
   }

   int cRepeats = _pView58Data->getRepeatCount();
   if( 0 != cRepeats )
   {
      for( int i = 0; i < cRepeats; i++ )
      {
         const BFData &data = _pView58Data->getRepeat( i );
         DString strLevel = data.getElementValue( ifds::Level );
			DString strAccount = data.getElementValue( ifds::AccountNum );
			strAccount.strip().stripLeading('0');
         if( strLevel.strip() == SHR_LEVEL && strAccount != NULL_STRING )
         {
            DString dstrKeyAlloc;
            getStrKey( dstrKeyAlloc, &data );
            ShrAllocType *pAllocation = new ShrAllocType( *this );
            setObject( pAllocation, dstrKeyAlloc, OBJ_ACTIVITY_NONE, BF::HOST );
            pAllocation->initExisting( data );
         }
      }
	  setFieldNoValidate ( ifds::UpdatePACSWP, NO, BF::HOST, true, true, true, false );
   }
   else
      initNew(BF::HOST);

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
void ShrAllocTypeList::getStrKey( DString &strKey, const BFData *data  )
{
	DString dstrTransType,dstrAccount,dstrEffectiveDate;
	if(data)
	{
	   dstrTransType = data->getElementValue( I_( "TransType" ) );
		dstrTransType.strip().upperCase();
	   dstrAccount = data->getElementValue( I_( "AccountNum" ) );
		dstrAccount.strip().stripLeading('0' );
	   dstrEffectiveDate = data->getElementValue( I_( "EffectiveDate" ) );
		dstrEffectiveDate.strip();
		strKey = dstrTransType + dstrAccount + dstrEffectiveDate;
	}
	else 
	{
		BFCBO::getStrKey( strKey , NULL );	
	}
}
//******************************************************************************

SEVERITY ShrAllocTypeList::doCreateObject( const BFData &data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   assert( 0 );//should not be called for the current design for allocations

   throw;
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY ShrAllocTypeList::doCreateNewObject( BFCBO *& pBase, 
                                              DString & strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   ShrAllocType *pShrAllocType = new ShrAllocType( *this );

   pShrAllocType->initNew( idDataGroup );

   pBase = pShrAllocType;

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY ShrAllocTypeList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   std::set< DString > setCharacteristic;

   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() )
   {
      DString strTransType, strEffectiveDate,dstrAccount;
		BFCBO* pCbo = dynamic_cast<BFCBO* >(iter.getObject() );
      pCbo->getField(ifds::TransType, strTransType, idDataGroup, false);
      pCbo->getField(ifds::EffectiveDate, strEffectiveDate, idDataGroup, false);
      pCbo->getField(ifds::AccountNum, dstrAccount, idDataGroup, false);
		dstrAccount.strip().stripLeading('0');
      DString strNewEntry = strTransType.strip().upperCase() + dstrAccount + strEffectiveDate.strip();

      if( !setCharacteristic.insert( strNewEntry ).second )
      {
         ADDCONDITIONFROMFILE( CND::ERR_IDENTICAL_SHR_DEFAULT_ALLOCS );
         break;
      }
      ++iter; 
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY ShrAllocTypeList::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

   setUpdatedFlag(idField, idDataGroup, false);

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY ShrAllocTypeList::getLatestDefaultShrAlloc( const BFDataGroupId& idDataGroup, 
                                                     const DString& dstrTransTypeIn,
												                 const DString& strAccountNum,
                                                     ShrAllocType*& pAllocation,
                                                     const DString& effectiveDate)
{   
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getLatestDefaultShrAlloc" ) );

	pAllocation = NULL;

   DString asOfDate (effectiveDate), 
      strTransTypeIn (dstrTransTypeIn), 
      strAccNum (strAccountNum);

   strAccNum.strip().stripLeading('0');
   //as Winnie asked, we want to keep same code name for different transaction types  (ED)
   //and also keep different code names for the same transaction(P,ED for PAC; S,AW for SWP; ED,DD for Purchase)
   //please see AMS Trade and Systematic ESS for an explanation
   //so we have to do the "translation" here (and in other places whenever it will be necessary to make this work)

//for RB&RO we need to match the date ...not get the latest...
   strTransTypeIn.strip();
   if (strTransTypeIn == ED)
   {
      strTransTypeIn = DD;
   }
   else if (strTransTypeIn == P)
   {
      strTransTypeIn = ED;
   }
   else if (strTransTypeIn == S)
   {
      strTransTypeIn = AW;
   }

   if (asOfDate.empty())
   {
      getWorkSession().getMgmtCoOptions()->getField (ifds::CurrBusDate, asOfDate, idDataGroup, false);
   }

   //get the most recent effective date 
   //if strAccountNum is not empty, search for the latest effective date which contains the
   //specified account num
   DString dstrLatestEffecDate (NULL_STRING);
   BFAbstractCBO *pBFCBOLatest = NULL;
   BFObjIter iter (*this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
   while (!iter.end())
   {
      ShrAllocType *pBFCBO = dynamic_cast<ShrAllocType *>(iter.getObject());
      if (pBFCBO)
      {
         DString dstrLevel, 
            dstrTransType;

         pBFCBO->getField (ifds::TransType, dstrTransType, idDataGroup, false);
         dstrTransType.strip().upperCase();

         if (dstrTransType == strTransTypeIn)
         {
            DString dstrEffecDate;

            pBFCBO->getField (ifds::EffectiveDate, dstrEffecDate, idDataGroup, false);
               if( DSTCommonFunctions::CompareDates (dstrEffecDate, asOfDate) == DSTCommonFunctions::FIRST_EARLIER ||
                   DSTCommonFunctions::CompareDates (dstrEffecDate, asOfDate) == DSTCommonFunctions::EQUAL)
               {
                  if( dstrLatestEffecDate == NULL_STRING ||
                      DSTCommonFunctions::CompareDates (dstrLatestEffecDate, dstrEffecDate) == DSTCommonFunctions::FIRST_EARLIER )
                  {
						   //if strAccountNum has been specified, check if it has allocations for this account
						   if ( strAccNum.empty() || 
                          pBFCBO->hasDefaultAllocations (strAccNum, idDataGroup))
						   {
							   dstrLatestEffecDate = dstrEffecDate;
							   pBFCBOLatest = pBFCBO;
						   }
                  }
               }
         }
      }
      ++iter;
   }
   pAllocation = dynamic_cast<ShrAllocType*>(pBFCBOLatest);
   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************

SEVERITY ShrAllocTypeList::getDefaultAcctAllocList( const DString& dstrTransTypeIn, 
                                                    DefAcctAllocList*& pAcctAllocationList,
                                                    const BFDataGroupId& idDataGroup,
                                                    const DString& dstrAccountNum,
                                                    const DString& effectiveDate /*=NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getDefaultAcctAllocList" ) );

   pAcctAllocationList = NULL;
   DString dstrAccNum(dstrAccountNum);
   ShrAllocType* pAllocation = NULL;
   dstrAccNum.strip().stripLeading('0');

   if ( getLatestDefaultShrAlloc (idDataGroup, dstrTransTypeIn, dstrAccNum, pAllocation, effectiveDate) <= WARNING &&
        pAllocation)
   {
      //Get the Account Level Allocation List
      DefAcctAllocList *pAcctAllocList = NULL;
      pAllocation->getAccountAllocationList (pAcctAllocList, idDataGroup, true);
      if (pAcctAllocList)
         pAcctAllocationList = dynamic_cast<DefAcctAllocList*>(pAcctAllocList);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************

SEVERITY ShrAllocTypeList::getDefaultFundAllocList( const DString& dstrTransTypeIn, 
                                                    const DString& dstrAcctNumIn,
                                                    DefFundAllocList*& pFundAllocationList,
                                                    const BFDataGroupId& idDataGroup,
                                                    const DString& effectiveDate /*=NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getDefaultFundAllocList" ) );

   pFundAllocationList = NULL;
   DefAcctAllocList* pAcctAllocationList = NULL;
   DString strAccNum(dstrAcctNumIn);
   if (strAccNum.strip().stripLeading('0').empty())
      strAccNum = NULL_STRING;
   //if dstrAcctNumIn empty, get the very latest account allocation
   if ( getDefaultAcctAllocList( dstrTransTypeIn, pAcctAllocationList, idDataGroup, strAccNum, effectiveDate ) > WARNING || !pAcctAllocationList )
      return(GETCURRENTHIGHESTSEVERITY());

   DefAcctAlloc* pAcctAlloc = NULL;
   if( pAcctAllocationList->getAccountAllocation(dstrAcctNumIn, pAcctAlloc, idDataGroup)>WARNING || !pAcctAlloc )
      return(GETCURRENTHIGHESTSEVERITY());

   if( pAcctAlloc )
      pAcctAlloc->getFundAllocationList(pFundAllocationList, idDataGroup, true, false);

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY ShrAllocTypeList::addNewAllocation( const DString& strKey, 
                                             const BFDataGroupId& idDataGroup,
                                             bool bAddChildren /*= true*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "addNewAllocation" ) );

   BFObjectKey objKey( strKey, idDataGroup );
   DString strKeyCopy(strKey);
   if( !strKeyCopy.strip().empty() )
      m_strKeyForNewItem = strKey;
   BFCBO * pNewObject = getNewListItem( objKey );
   m_strKeyForNewItem = NULL_STRING;

   if( bAddChildren )
   {
      ShrAllocType *pNewShrAllocType = dynamic_cast<ShrAllocType*>(pNewObject);
      assert(pNewShrAllocType);
      DefAcctAllocList *pAcctAllocList;
      pNewShrAllocType->getAccountAllocationList(pAcctAllocList, idDataGroup); 
      pAcctAllocList->addNewAllocation(strKey, idDataGroup, false, false, bAddChildren);
   }
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
SEVERITY ShrAllocTypeList::getShrAllocType(const DString& strKey, 
                                           ShrAllocType *& pShrAllocType, 
                                           const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getShrAllocType" ) );

   pShrAllocType = NULL;

   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   if( iter.positionByKey( strKey ) )
      pShrAllocType = static_cast<ShrAllocType *>( iter.getObject());

   return(GETCURRENTHIGHESTSEVERITY());

}
//******************************************************************************

void ShrAllocTypeList::setAcctAllocFlags(const BFDataGroupId& idDataGroup)
{
   Shareholder* pParent = dynamic_cast<Shareholder*>(getParent());
   assert(pParent);
   MFAccountList *pMFAccountList;
   if( pParent->getMFAccountList(pMFAccountList, idDataGroup)>WARNING )
      return;
   BFObjIter iter(*pMFAccountList, idDataGroup);
   while( !iter.end() )
   {
      BFAbstractCBO* pMFAccount = iter.getObject();
      assert(pMFAccount);

      DString strAccNum;
      pMFAccount->getField(ifds::AccountNum, strAccNum, idDataGroup, false);
      if( !strAccNum.strip().stripLeading('0').empty() )
      {
         MFAccount *pMFAccount = NULL;
         if( getWorkSession().getMFAccount(idDataGroup, strAccNum, pMFAccount, 
                                           I_("N"), NULL_STRING, false)<=WARNING && pMFAccount ) //don't have to create here
         {
            bool bHasAlloc = hasDefaultAllocations(strAccNum, idDataGroup);
            if( bHasAlloc )
               pMFAccount->setField(ifds::AcctAlloc, YES, idDataGroup, false);
            else
               pMFAccount->setField(ifds::AcctAlloc, NO, idDataGroup, false);
         }
      }
      ++iter;
   }

}
//******************************************************************************

bool ShrAllocTypeList::hasDefaultAllocations(const DString& strAccNum, const BFDataGroupId& idDataGroup)
{
   DString strAccNumIn(strAccNum);
   if( strAccNumIn.strip().stripLeading('0').empty() )
      return(false);
   BFObjIter iter(*this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
   while( !iter.end() )
   {
      ShrAllocType *pShrAllocType = static_cast<ShrAllocType*>(iter.getObject());
      assert(pShrAllocType);
      DefAcctAllocList *pDefAcctAllocList = NULL;
      if( pShrAllocType->getAccountAllocationList(pDefAcctAllocList, idDataGroup)<=WARNING && pShrAllocType )
      {
         BFObjIter iter1(*pDefAcctAllocList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
         while( !iter1.end() )
         {
            BFAbstractCBO* pDefAcctAlloc = iter1.getObject();
            assert(pDefAcctAlloc);
            DString strAccountNum;
            pDefAcctAlloc->getField(ifds::AccountNum, strAccountNum, idDataGroup, false);
            if( strAccNumIn == strAccountNum.strip().stripLeading('0') )
               return(true);
            ++iter1;
         }
      }
      ++iter;
   }
   return(false);
}
//******************************************************************************

void ShrAllocTypeList::getStrKeyForNewItem( DString & strKey )
{
   if( !m_strKeyForNewItem.empty() )
      strKey = m_strKeyForNewItem;
   else
      BFCBO::getStrKeyForNewItem( strKey );
}

//******************************************************************************

SEVERITY ShrAllocTypeList::getShrAllocType(const DString& dstrAccountNum, 
                                           const DString& dstrAllocationType,
                                           ShrAllocType *& pShrAllocType, 
                                           const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getShrAllocType" ) );

   DString dstrTransType;
   pShrAllocType = NULL;
   DefAcctAllocList *pDefAcctAllocList = NULL;
   DefAcctAlloc *pDefAcctAlloc = NULL;

   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   while (!iter.end()) {
      pShrAllocType = static_cast<ShrAllocType *>( iter.getObject());
      pShrAllocType->getField(ifds::TransType, dstrTransType, idDataGroup, false);
      if( dstrTransType == dstrAllocationType ) {
         pShrAllocType->getAccountAllocationList(pDefAcctAllocList, idDataGroup, false);
         pDefAcctAllocList->getAccountAllocation( dstrAccountNum, pDefAcctAlloc, idDataGroup );
         if( !pDefAcctAlloc )
         {
            pShrAllocType = NULL;
            break;
         }
      }
      ++iter;
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY ShrAllocTypeList::removeShrAllocType(const DString& dstrAccountNum, 
                                           const DString& dstrAllocationType,
                                           const DString& dstrEffectiveDate,
                                           const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "removeShrAllocType" ) );

   DString dstrTransType, dstrDate;
   ShrAllocType *pShrAllocType = NULL;

   if( dstrEffectiveDate.empty() )
   {
      getLatestDefaultShrAlloc( idDataGroup, dstrAllocationType, dstrAccountNum, pShrAllocType, dstrEffectiveDate );
   }
   else 
   {
      BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
      while (!iter.end()) {
         bool bDeleteShrAllocType = false;
         pShrAllocType = static_cast<ShrAllocType *>( iter.getObject());
         pShrAllocType->getField(ifds::TransType, dstrTransType, idDataGroup, false);
         pShrAllocType->getField(ifds::EffectiveDate, dstrDate, idDataGroup, false);
         if( dstrTransType == dstrAllocationType && dstrDate == dstrEffectiveDate )
         {
            getShrAllocType( dstrAccountNum, dstrAllocationType, pShrAllocType, idDataGroup );
         }
         ++iter;
      }
   }
   if( pShrAllocType )
   {
      pShrAllocType->clearAllocations( idDataGroup );

      // Delete from ShrAllocTypeList;
      ShrAllocType *pShrAllocTypeTemp = NULL;
      BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
      while( !iter.end() )
      {
         pShrAllocTypeTemp = static_cast<ShrAllocType *>( iter.getObject() );
         if( pShrAllocType == pShrAllocTypeTemp )
         {
            iter.deleteObject();
            break;
         }
         else 
         {
            ++iter;
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY ShrAllocTypeList::addNewShrAllocType( const DString& dstrAllocType,
                                               const DString& dstrAccountNum,
                                               const BFDataGroupId& idDataGroup,
                                               const DString &effectiveDate /*=NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "addNewShrAllocType" ) );

   // Get Effective date from Account Number
   MFAccount *pMFAccount = NULL;
   DString dstrDate (effectiveDate);
   bool blAllowRBROEffectiveDateChange = false;

   if (dstrDate.empty())
   {
      getWorkSession().getDateInHostFormat ( dstrDate, 
                                             DSTCWorkSession::DATE_TYPE::CURRENT_BUSINESS_DAY, 
                                             idDataGroup);
   }
   else
   {
	   // used by Account level AMS, so allow Effectivedate change
	   blAllowRBROEffectiveDateChange = true;
   }

   ShrAllocType* pShrAllocType = NULL;
   DefAcctAllocList *pAcctAllocList = NULL;
   addNewAllocation(dstrAllocType, idDataGroup, false);
   getShrAllocType(dstrAllocType, pShrAllocType, idDataGroup);
   pShrAllocType->allowRBROEffectiveDateChange( blAllowRBROEffectiveDateChange );
   pShrAllocType->setField( ifds::TransType, dstrAllocType, idDataGroup, false );
   pShrAllocType->setField( ifds::EffectiveDate, dstrDate, idDataGroup, false );
   pShrAllocType->getAccountAllocationList(pAcctAllocList, idDataGroup);
   pAcctAllocList->addNewAllocation(dstrAccountNum, idDataGroup, false, false, true); // true

   DefAcctAlloc *pAcctAlloc = NULL;
   pAcctAlloc = dynamic_cast<DefAcctAlloc*>(pAcctAllocList->getObject(dstrAccountNum, idDataGroup));
   pAcctAlloc->setField(ifds::AccountNum, dstrAccountNum, idDataGroup, false);
   pAcctAlloc->setField(ifds::AllocPercentage, I_("100"), idDataGroup, false);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ShrAllocTypeList.cpp-arc  $
// 
//    Rev 1.22   Feb 12 2008 15:57:16   yingz
// fix 1101619 - When submit the modification of Acct level AMS code or AMS allocation, user has a choice to refresh the existing PAC with the same allocation. The refresh should be done with the effective AMS allcation
// 
//    Rev 1.21   Jan 15 2008 11:14:54   yingz
// fix incident 1101619 and 1094212
// 
//    Rev 1.20   19 Oct 2007 16:19:44   kovacsro
// IN#1038318 - added rej erros / hard edit to prevent users from entering future dated Stop dates on AMS and modifying Effective Date for RB/RO default allocations on Allocation screen
// 
//    Rev 1.19   14 Sep 2007 10:59:42   popescu
// Incident 1003183 (GAP2360/02) - fixed AMS allocations
// 
//    Rev 1.18   Jan 04 2005 16:00:02   Fengyong
// PET10037335 - view 98, field UpdatePACSWP initialize
// 
//    Rev 1.17   Dec 10 2004 13:19:28   Fengyong
// PET10034197 - PAC allocation not being changed after account level AMS set flag change pac/swp is yes.
// 
//    Rev 1.16   Nov 14 2004 14:55:32   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.15   Aug 27 2004 16:10:18   WINNIE
// error due to a bug fixed in core code. Class field info missing for update of field in the object.
// 
//    Rev 1.14   Feb 12 2004 15:56:38   YINGBAOL
// PTS 10021233: Multi allocation at account level is not been supported
// 
//    Rev 1.13   Mar 21 2003 18:24:50   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.12   Dec 05 2002 15:53:00   HERNANDO
// Changed removeShrAllocType.
// 
//    Rev 1.11   Dec 05 2002 13:09:16   KOVACSRO
// As Winnie asked, we'll keep double names for trans type (see AMS Trade & Systematic ESS, ver. 1.1) 
// 
//    Rev 1.10   Dec 04 2002 18:20:18   HERNANDO
// Changed getShrAllocType and removeShrAllocType.
// 
//    Rev 1.9   Nov 29 2002 10:25:18   KOVACSRO
// rxTransType changes
// 
//    Rev 1.8   Nov 28 2002 18:22:00   HERNANDO
// Added some functions.
// 
//    Rev 1.7   Nov 18 2002 13:34:52   KOVACSRO
// 1. Added getDefaultAcctAllocList which has an AccountNum parameter (so now it will pick-up the latest allocations that contain the specified account number)
// 2. Added AccountNum param, to the existing getLatestDefaultShrAlloc.
// 
//    Rev 1.6   Oct 09 2002 23:55:02   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.5   Aug 29 2002 12:56:40   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.4   Jul 31 2002 14:58:06   KOVACSRO
// Added getStrKeyForNewItem
// 
//    Rev 1.3   22 May 2002 18:29:52   PURDYECH
// BFData Implementation
// 
//    Rev 1.2   08 May 2002 16:56:30   KOVACSRO
// More implementation.
// 
//    Rev 1.1   29 Apr 2002 16:30:34   KOVACSRO
// DD versus ED (!)
// 
//    Rev 1.0   22 Apr 2002 13:00:06   KOVACSRO
// Initial revision.
 * 
 * 
 */