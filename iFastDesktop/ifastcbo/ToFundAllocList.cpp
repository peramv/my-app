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
//    Copyright 2003 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : ToFundAllocList.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : 22/May/03
//
// ^CLASS    : ToFundAllocList
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
#include "ToFundAlloc.hpp"
#include "ToFundAllocList.hpp"
#include "MFAccount.hpp"
#include "FundDetailList.hpp"
#include "FundDetail.hpp"
#include "FundToList.hpp"
#include "FundDetailList.hpp"
#include "FromFundAllocList.hpp"

#include "mgmtco.hpp"


#include <ifastdataimpl\dse_dstc0068_req.hpp>
#include <ifastdataimpl\dse_dstc0068_vw.hpp>
#include <ifastdataimpl\dse_dstc0067_vw.hpp>
#include <ifastdataimpl\dse_dstc0149_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME = I_( "ToFundAllocList" );
   const I_CHAR * const NO = I_( "N" );
   const I_CHAR * const YES = I_( "Y" );
   const I_CHAR * const EX_FER_IN_CODE             = I_( "XFIN" );   // trade trans type Exchange In 

}

namespace CND
{
   extern const long  ERR_RRIF_ALLOCATION_SETUP;
   extern const long  ERR_AT_FUNDCLASS_TRANSFER_NOT_ALLOWED;
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
   extern CLASS_IMPORT const BFTextFieldId FundClass;
   extern CLASS_IMPORT const BFTextFieldId ToSoftCapCheck;
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest RRIF_LIF_LRIF_ALLOC;
}


//******************************************************************************
ToFundAllocList::ToFundAllocList( BFAbstractCBO &parent ) 
: FundAllocList( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   setObjectAsList();
}

//******************************************************************************
ToFundAllocList::~ToFundAllocList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}
//******************************************************************************

SEVERITY ToFundAllocList::initExisting( const DString& dstrTrack,
                                          const DString& dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initExisting" ) );

   setListFields(BF::HOST);

   BFData* pRequestDataRRIF_Alloc =  new BFData( ifds::DSTC0068_REQ);

   DString mgmtCoIdOut, strAccountNum, dstrRIFId;
   getParent()->getField(ifds::AccountTo, strAccountNum, BF::HOST, false);
   pRequestDataRRIF_Alloc->setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   pRequestDataRRIF_Alloc->setElementValue( ifds::AccountNum, strAccountNum);
   pRequestDataRRIF_Alloc->setElementValue( ifds::NextKey,NULL_STRING );
   pRequestDataRRIF_Alloc->setElementValue( ifds::Track, dstrTrack );
   pRequestDataRRIF_Alloc->setElementValue( ifds::Activity, dstrPageName );
   BFCBO* pParent = getTopLevelCBO();
   pParent->getField(ifds::RIFId, dstrRIFId, BF::HOST, false);
   pRequestDataRRIF_Alloc->setElementValue( ifds::RIFId, dstrRIFId, false, false );
   pRequestDataRRIF_Alloc->setElementValue( ifds::AllocType, I_("RT"), false, false );

   ReceiveData(DSTC_REQUEST::RRIF_LIF_LRIF_ALLOC, *pRequestDataRRIF_Alloc, ifds::DSTC0068_VW, 
               DSTCRequestor( getSecurity(), false ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY ToFundAllocList::initNew( const BFDataGroupId& idDataGroup,
                                     bool bGetDefault,
                                     const DString& dstrTrack,
                                     const DString& dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initNew" ) );

   FundAllocList::initNew(idDataGroup, bGetDefault, dstrTrack, dstrPageName);

   setFieldNoValidate(ifds::ReplaceAsDefault, NO, idDataGroup);

   if( bGetDefault )
   {
      ToFundAlloc *pToFundAlloc = NULL;
      initDefaultAllocationList(pToFundAlloc, idDataGroup);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void ToFundAllocList::setAllAllocsFndClsValidFlag(bool isValid, const BFDataGroupId& idDataGroup)
{
    BFObjIter iter(*this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

    while (!iter.end())
    {
        ToFundAlloc *pToFundAlloc = dynamic_cast<ToFundAlloc*>(iter.getObject());

        if (pToFundAlloc && !iter.isDummy())
        {
            pToFundAlloc->setFieldValid(ifds::ToSoftCapCheck, idDataGroup, isValid);
            pToFundAlloc->setFieldUpdated(ifds::ToSoftCapCheck, idDataGroup, true);
        }
        
        ++iter;
    }
}

/******************************************************************************

SEVERITY ToFundAllocList::addNewAllocation( const DString& strKey, 
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
   ToFundAlloc * pToFundAlloc = dynamic_cast<ToFundAlloc*>(getNewListItem( objKey ));
   m_strKeyForNewItem = NULL_STRING;

   assert(pToFundAlloc);
   if( bCopyParent )
      pToFundAlloc->copyDataFromParent(idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY ToFundAllocList::addExistingAllocation( const DString& strKey, 
                                                   const BFDataGroupId& idDataGroup,
                                                   bool bAddChildren)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "addExistingAllocation" ) );

   BFObjectKey objKey( strKey, idDataGroup );
   ToFundAlloc * pNewToFundAlloc;
   getKey( objKey, NULL, true );
   objKey.setActivity( OBJ_ACTIVITY_NONE );
   pNewToFundAlloc = new ToFundAlloc( *this );
   setObject( objKey, pNewToFundAlloc );

   //what do we do with the key if not null??
   pNewToFundAlloc->initWithDefaultValues(idDataGroup);
   pNewToFundAlloc->copyDataFromParent(idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
}
*/
//******************************************************************************

SEVERITY ToFundAllocList::doCreateNewObject( BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   ToFundAlloc *pAllocation = new ToFundAlloc( *this );
   pAllocation->initNew( idDataGroup );
   pBase = pAllocation;
   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************

SEVERITY ToFundAllocList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup ) 
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
   getWorkSession().getOption( ifds::RRIFToAlloc, dstrAllocMandatory, idDataGroup, false );
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

	validateFundTransfer( idDataGroup );
   validateFundClassTransferAllowed( idDataGroup );

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

bool ToFundAllocList::isAllDummy(const BFDataGroupId& idDataGroup)
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

SEVERITY ToFundAllocList::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );
   if( FundAllocList::doApplyRelatedChanges( idField, idDataGroup ) > WARNING )
      return(GETCURRENTHIGHESTSEVERITY());

   return(GETCURRENTHIGHESTSEVERITY());
}

/******************************************************************************

void ToFundAllocList::getFormattedAmount(const BFDataGroupId& idDataGroup, DString &dstrValue)
{
  //no formatting for RRIF??!?
}*/
//******************************************************************************

SEVERITY ToFundAllocList::setListFields(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setListFields" ) );

   loadSubstitutions(idDataGroup);

   BFCBO *pParent = NULL;
   pParent = getTopLevelCBO();
   assert(pParent);
   DString str, dstrTaxType;

   BFCBO *pMFAccount = pParent->getParent()->getParent();
   assert(pMFAccount);
   setFieldFromCBO(pMFAccount, ifds::Currency, ifds::Currency, idDataGroup, str);
	dstrTaxType = I_("RT");
   setFieldNoValidate(ifds::TransType, dstrTaxType, idDataGroup, false);

   setFieldFromCBO(pParent, ifds::EffectiveFrom, ifds::EffectiveDate, idDataGroup, str);
   setFieldFromCBO(pParent, ifds::RRIFAmount, ifds::Amount, idDataGroup, str);
   setField(ifds::AllocAmtType, I_("D"), idDataGroup, false);
   setFieldFromCBO(pMFAccount, ifds::AccountNum, ifds::AccountNum, idDataGroup, str);
   //setFieldFromCBO(pParent, ifds::FromClass, ifds::FromClass, idDataGroup, str);
	
	
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY ToFundAllocList::doCreateObject( const BFData &data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut = new ToFundAlloc ( *this );
   dynamic_cast< ToFundAlloc * >( pObjOut )->initExisting( data );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY ToFundAllocList::loadSubstitutions( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "loadSubstitutions" ) );

   if( DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA )
      setFieldSubstituteValues( ifds::TransType, idDataGroup, ifds::RRIFTransType);

   return(GETCURRENTHIGHESTSEVERITY());
}
//*****************************************************************************
SEVERITY ToFundAllocList::validateFundTransfer( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFromFundToFund" ) );
	DString dstrToAccount,dstrEffectiveDate;
	getParent()->getField(ifds::AccountTo,dstrToAccount,idDataGroup,false);
	getParent()->getField(ifds::EffectiveFrom,dstrEffectiveDate,idDataGroup,false);

	dstrToAccount.strip();
	MFAccount* pMFAccount;
	getWorkSession().getMFAccount( idDataGroup, dstrToAccount,pMFAccount );
	if(pMFAccount )
	{
		DString dstrFundCode,dstrClassCode;
		BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
		while( !iter.end() )
		{
			iter.getObject()->getField(ifds::FundCode,dstrFundCode,idDataGroup,false);		 
			iter.getObject()->getField(ifds::ClassCode,dstrClassCode,idDataGroup,false);	
			SEVERITY sev = pMFAccount->canTradeFundClass ( dstrFundCode,dstrClassCode,EX_FER_IN_CODE,
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

//*******************************************************************************
SEVERITY ToFundAllocList::validateFundClassTransferAllowed(const BFDataGroupId& idDataGroup)
{ 
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateFundClassTransferAllowed"));
   //rules check if transfer is allowed
   DString FundCode,FundToCode,ClassCode,ClassToCode,AccountNum,dstrAccountTo;
	GetFromToFundAllocListInterFace* pInfo = dynamic_cast<GetFromToFundAllocListInterFace*>(getParent() ); //for general purpose RRIF_Info object should not appeared here	
	if(pInfo )
	{	
	   FundDetailList *pFundDetailList = NULL;
		getMgmtCo().getFundDetailList(pFundDetailList);
		if(pFundDetailList)
		{
			FromFundAllocList* pFromFundAllocList = NULL;
			pInfo->getFromFundAllocList(pFromFundAllocList,idDataGroup,false);
			if(pFromFundAllocList)
			{
			 BFObjIter iterFrom( *pFromFundAllocList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
			 while( !iterFrom.end() && !iterFrom.isDummy() )
			 {
				 iterFrom.getObject()->getField(ifds::FundCode,FundCode,idDataGroup,false);
				 iterFrom.getObject()->getField(ifds::ClassCode,ClassCode,idDataGroup,false);
				 FundCode.strip().upperCase();
				 ClassCode.strip().upperCase();
				 if( FundCode.empty() || ClassCode.empty() ) 
				 {		 
					 ++iterFrom;
					continue;
				 }	 
				 BFObjIter iterTo( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
				 while( !iterTo.end() )
				 {
					 iterTo.getObject()->getField(ifds::FundCode,FundToCode,idDataGroup,false);
					 iterTo.getObject()->getField(ifds::ClassCode,ClassToCode,idDataGroup,false);
					 FundToCode.strip().upperCase();
					 ClassToCode.strip().upperCase();
					 if( FundToCode.empty() || ClassToCode.empty() ){
						 ++iterTo;						 
						 continue;
					 }		 
					 FundToList  fundToList(*this);
					 if( fundToList.isTransferAllowed(  FundCode, ClassCode, FundToCode, ClassToCode ) == false )
						{
							DString idiStr;
							addIDITagValue( idiStr, I_("FIELD1"), FundCode );
							addIDITagValue( idiStr, I_("FIELD2"), ClassCode );
							addIDITagValue( idiStr, I_("FIELD3"), FundToCode );
							addIDITagValue( idiStr, I_("FIELD4"), ClassToCode );
							ADDCONDITIONFROMFILEIDI( CND::ERR_AT_FUNDCLASS_TRANSFER_NOT_ALLOWED,idiStr );          														
						}						
					 ++iterTo;
				 }	//while iterTo.
				 ++iterFrom;
			 }//while from
			}//if FromFundAlloc
		}//FundDetailList
	} 
	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ToFundAllocList.cpp-arc  $
// 
//    Rev 1.8   Nov 18 2004 13:28:34   YINGBAOL
// PET1117: Perfermance Tunning
// 
//    Rev 1.7   Nov 14 2004 14:57:16   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.6   Oct 03 2003 12:37:52   YINGBAOL
// PTS10020438  use AccountTo as account number.
// 
//    Rev 1.5   Aug 27 2003 13:46:56   YINGBAOL
// PTS10020950 take care dummy record ToFundAlloclist
// 
//    Rev 1.4   Jul 21 2003 16:21:08   YINGBAOL
// fix Dummy record issue
// 
//    Rev 1.3   Jun 26 2003 15:34:46   YINGBAOL
// fix error in validateFundClassTransferAllowed
// 
//    Rev 1.2   Jun 24 2003 09:43:40   YINGBAOL
// implement FundClass Transfer allowed
// 
//    Rev 1.1   Jun 13 2003 16:01:46   YINGBAOL
// add validateFundTransfer
// 
//    Rev 1.0   Jun 09 2003 11:05:02   YINGBAOL
// Initial revision.


 * 
 * 
 */