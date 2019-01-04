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
// ^FILE   : TradeFundAllocList.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 08/04/02
//
// ^CLASS    : TradeFundAllocList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : Trade, PendingTradeDetails and TransactionDetails fund allocation list
//
//******************************************************************************

#include "stdafx.h"
#include "amsmstrlist.hpp"
#include "deffundalloclist.hpp"
#include "mfaccount.hpp"
#include "splitcommissionlist.hpp"
#include "trade.hpp"
#include "tradeacctalloclist.hpp"
#include "tradefundalloc.hpp"
#include "tradefundalloclist.hpp"
#include <ifastdataimpl\dse_dstc0058_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME = I_( "TradeFundAllocList" );
   const I_CHAR * const NO = I_( "N" );
   const I_CHAR * const YES = I_( "Y" );
   const I_CHAR * const UNITS = I_( "U" ); // amount type
   const I_CHAR * const RB_TYPE = I_( "RB" );
}

namespace CND
{
   extern const long ERR_ALLOCAMOUNT_GREATER_THAN_TOTAL;
	extern const long ERR_FULL_REDEMPTION_PERCENTAGE_MUST_BE_ZERO_FOR_EACH_FUND;
}

namespace ifds
{  
   extern CLASS_IMPORT const BFDecimalFieldId Amount;
   extern CLASS_IMPORT const BFTextFieldId SplitComm;
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFTextFieldId ReplaceAsDefault;
   extern CLASS_IMPORT const BFTextFieldId AllocAmtType;
   extern CLASS_IMPORT const BFTextFieldId MultiCurrency;
   extern CLASS_IMPORT const BFTextFieldId Default;
   extern CLASS_IMPORT const BFTextFieldId AMSCode;
   extern CLASS_IMPORT const BFTextFieldId DefaultAlloc;
   extern CLASS_IMPORT const BFTextFieldId FundAlloc;  
   extern CLASS_IMPORT const BFTextFieldId FundClass;
   extern CLASS_IMPORT const BFTextFieldId SoftCapCheck;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const PURCHASE;
   extern CLASS_IMPORT I_CHAR * const TRANSFER;
   extern CLASS_IMPORT I_CHAR * const REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const EXCHANGE;
   extern CLASS_IMPORT I_CHAR * const ALL_FUND_TRANSFER;
   extern CLASS_IMPORT I_CHAR * const MGMT_FEE;
	extern CLASS_IMPORT I_CHAR * const ONE_SIDE_TRADE;
	extern CLASS_IMPORT I_CHAR * const ADMIN_FEE;
    extern CLASS_IMPORT I_CHAR * const INTER_CLASS_SWITCH;
}

//******************************************************************************
TradeFundAllocList::TradeFundAllocList( BFAbstractCBO &parent ) 
: FundAllocList( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );   

   setObjectAsList();
}

//******************************************************************************
TradeFundAllocList::~TradeFundAllocList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}
//******************************************************************************

SEVERITY TradeFundAllocList::initExisting( const DString& dstrTrack,
                                           const DString& dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initExisting" ) );

   TradeAcctAllocList* pParentAllocList = dynamic_cast<TradeAcctAllocList*>(getParentList());
   const BFData* pView60Data = NULL;
   pView60Data = pParentAllocList->getView60();
   assert(pView60Data);

   setListFields(BF::HOST);

   DString strParentAccountNum;
   getField(ifds::AccountNum, strParentAccountNum, BF::HOST, false);
   strParentAccountNum.strip().stripLeading('0');


   int cRepeats = pView60Data->getRepeatCount();
   //this method shouldn't be called if view 60 came back empty
   assert( cRepeats );

   for( int i = 0; i < cRepeats; i++ )
   {
      const BFData &data = pView60Data->getRepeat( i );
      DString strAccountNum  = data.getElementValue( ifds::AccountNum );
      strAccountNum.strip().stripLeading('0');
      if( strAccountNum != strParentAccountNum )
         continue;

      TradeFundAlloc *pFundAlloc = new TradeFundAlloc( *this );
      DString dstrKey;
      getStrKey(dstrKey, &data);
      assert(!dstrKey.empty());
      setObject( pFundAlloc, dstrKey, OBJ_ACTIVITY_NONE, BF::HOST );
      pFundAlloc->initExisting( data );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY TradeFundAllocList::initNew( const BFDataGroupId& idDataGroup,
                                      bool bGetDefault,
                                      const DString& dstrTrack,
                                      const DString& dstrPageName)
{
  MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initNew" ) );

   FundAllocList::initNew(idDataGroup, bGetDefault, dstrTrack, dstrPageName);

   setFieldNoValidate(ifds::ReplaceAsDefault, NO, idDataGroup);

   if( bGetDefault )
   {
      TradeFundAlloc *pTradeFundAlloc = NULL;
      initDefaultAllocationList(pTradeFundAlloc, idDataGroup);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY TradeFundAllocList::addNewAllocation( const DString& strKey, 
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
   TradeFundAlloc * pNewTradeFundAlloc = dynamic_cast<TradeFundAlloc*>(getNewListItem( objKey ));
   m_strKeyForNewItem = NULL_STRING;
   assert(pNewTradeFundAlloc);
   if( bCopyParent )
      pNewTradeFundAlloc->copyDataFromParent(idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY TradeFundAllocList::addExistingAllocation( const DString& strKey, 
                                                    const BFDataGroupId& idDataGroup,
                                                    bool bAddChildren)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "addExistingAllocation" ) );

   BFObjectKey objKey( strKey, idDataGroup );
   TradeFundAlloc * pNewTradeFundAlloc;
   getKey( objKey, NULL, true );
   objKey.setActivity( OBJ_ACTIVITY_NONE );
   pNewTradeFundAlloc = new TradeFundAlloc( *this );
   setObject( objKey, pNewTradeFundAlloc );

   //what do we do with the key if not null??
   pNewTradeFundAlloc->initWithDefaultValues(idDataGroup);
   pNewTradeFundAlloc->copyDataFromParent(idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY TradeFundAllocList::doCreateNewObject( BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   TradeFundAlloc *pAllocation = new TradeFundAlloc( *this );
   pAllocation->initNew( idDataGroup );
   pBase = pAllocation;

   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
SEVERITY TradeFundAllocList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

	bool bSkip100PercentValidation = false;
	if( bfutil::isServerContext())
	{	
		//Cause desktop's dummy record, api not be able to add allocation without delete the dummy record.
		//So API have to check if record is dummy then skip the dummy 100 allocation.
		//API is replacing by new application, so here leave the function like before, the problem still there.
		//This is the final catch for bugs in parent allocation which become dummy for multiple fund trade when did not delete the dummy record.
		BFObjIter iterFundAllocList( *this, 
										idDataGroup, 
										false, 
										BFObjIter::ITERTYPE::NON_DELETED );
		iterFundAllocList.begin();			
		int iNoOfFunds = iterFundAllocList.getNumberOfItemsInList();
		if( iNoOfFunds > 1 ) getParent()->setNonDummyFlag();
		//bSkip100PercentValidation = true;
	}
	Trade *pTrade = pTrade = dynamic_cast< Trade * >( getTopLevelCBO() );
	DString dstrTransType;
	getField( ifds::TransType, dstrTransType, idDataGroup, false );

	// 100Percent Validation is skipped when Amount = 0 and Redemption code is listed in 
	// Generic Control.FullRedCode
	// In this case, the user specifies the funds to be fully redeemed. We need to have 0% percentage
	// indicated for each fund to be redeemed	
	if ( (TRADETYPE::REDEMPTION == dstrTransType ||
		   TRADETYPE::MGMT_FEE == dstrTransType ||
			TRADETYPE::ADMIN_FEE == dstrTransType ) && 
		   NULL != pTrade &&
	      pTrade->isFullRedemption( idDataGroup ) )
	{			
		BFObjIter iterTradeFundAllocationList( *this, 
															idDataGroup, 
															false, 
															BFObjIter::ITERTYPE::NON_DELETED );
		
		// If any AllocPercentage field has already been updated, it's been validated and in case
		// it has wrong value, an error has already been issued, don't throw another one here
		iterTradeFundAllocationList.begin();			
		int iNoOfFunds = iterTradeFundAllocationList.getNumberOfItemsInList();
		if ( iNoOfFunds > 1 )
		{
			bSkip100PercentValidation = true;
			bool blAllocPercentageNotZero = false;

			while( !iterTradeFundAllocationList.end() )
			{
				BFAbstractCBO *pTradeFundAlloc = iterTradeFundAllocationList.getObject();
				if( NULL != pTradeFundAlloc )
				{
					DString dstrAllocPercentage;
					pTradeFundAlloc->getField( ifds::AllocPercentage, dstrAllocPercentage, idDataGroup );                   								
					double dblAllocPercentage = DSTCommonFunctions::convertToDouble( dstrAllocPercentage );				
					if ( 0.00 != dblAllocPercentage )
					{
						blAllocPercentageNotZero = true;
						break;
					}
				}
				++iterTradeFundAllocationList;		
			}         		
			
			if ( blAllocPercentageNotZero )
			{
				ADDCONDITIONFROMFILE( CND::ERR_FULL_REDEMPTION_PERCENTAGE_MUST_BE_ZERO_FOR_EACH_FUND );				
			}      
		}
	}	

   if( FundAllocList::doValidateAll( idDataGroup, lValidateGroup, bSkip100PercentValidation )>WARNING )
      return(GETCURRENTHIGHESTSEVERITY());

   //for non multicurrency env., issue an error if not all the currencies are the same
   if( !isMultiCurrency() )
      validateMulticurrency(idDataGroup);

   DString strMultiCurrency;
   getWorkSession().getOption( ifds::MultiCurrency, strMultiCurrency, BF::HOST, false );
   if( strMultiCurrency == NO )
   {
      Trade *pTrade = NULL;
      pTrade = dynamic_cast< Trade * >( getTopLevelCBO() );
      if( pTrade )
      {
         DString dstrAllocCurrency;
         getAllocCurrency( dstrAllocCurrency, idDataGroup );
//TODO - set currency
//         if( !dstrAllocCurrency.strip().upperCase().empty() )
//            pTrade->getDefaultBank( idDataGroup, dstrAllocCurrency );

      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY TradeFundAllocList::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );
   if( FundAllocList::doApplyRelatedChanges( idField, idDataGroup ) > WARNING )
      return(GETCURRENTHIGHESTSEVERITY());

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

void TradeFundAllocList::getFormattedAmount(const BFDataGroupId& idDataGroup, DString &dstrValue)
{
   DString strTransType, strAmountType;

   getField(ifds::AllocAmtType, strAmountType, idDataGroup, false);
   getField(ifds::TransType, strTransType, idDataGroup, false);
   strTransType.strip();

   if( strAmountType.strip() != UNITS )
   {
      if (DSTCommonFunctions::codeInList (strTransType.strip(), TRADETYPE::ONE_SIDE_TRADE))
         formatAmtUsingCurrency(idDataGroup, dstrValue);
      else if (strTransType == TRADETYPE::EXCHANGE ||
               strTransType == TRADETYPE::INTER_CLASS_SWITCH ||
               strTransType == TRADETYPE::TRANSFER || 
               strTransType == TRADETYPE::ALL_FUND_TRANSFER)

         formatAmtUsingFromFund( idDataGroup, dstrValue );
   }
   else//units
   {
      formatAmtUsingFromFund( idDataGroup, dstrValue );
   }  
}
//******************************************************************************

SEVERITY TradeFundAllocList::getDefaultAllocList(AbstractAllocList*& pDefaultAllocationList, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getDefaultAllocList" ) );
   //rule : if AMSCode in the account 
   //a) has a valid value - get AMSType, DefaultAlloc and FundAlloc fields 
   //from the corresponding AMSMstr record
   //a1)if AMSType == RB
   //a11) if  DefaultAlloc == Y, get RB type shareholder default allocations
   //a12 else if FundAlloc == Y, get AMS allocations from MFAccount
   //a2,b) any other case - get default allocations for the specified trans type

   pDefaultAllocationList = NULL;
   DString strAccountNum, strAMSCode(NULL_STRING);
   getField(ifds::AccountNum, strAccountNum, idDataGroup, false);
   MFAccount* pMFAccount = NULL;
   if( getWorkSession().getMFAccount( idDataGroup, strAccountNum, pMFAccount) > WARNING || !pMFAccount)
      return(GETCURRENTHIGHESTSEVERITY());

   pMFAccount->getField(ifds::AMSCode, strAMSCode, idDataGroup, false);
   if (!strAMSCode.strip().empty())
   {
      DString strDefaultAlloc, strFundAlloc;
      AMSMstrList objAMSMstrList(*this);
      if (objAMSMstrList.init2(RB_TYPE, strAMSCode, true)>WARNING)
         return(GETCURRENTHIGHESTSEVERITY());

	  DString dstrEffectiveDate = NULL;
	  getWorkSession().getDateInHostFormat(dstrEffectiveDate, DSTCWorkSession::DATE_TYPE::CURRENT_BUSINESS_DAY, idDataGroup);   

      objAMSMstrList.getFieldByAMSCode(RB_TYPE,strAMSCode,dstrEffectiveDate, ifds::DefaultAlloc, 
         strDefaultAlloc, idDataGroup, false);
      if (strDefaultAlloc == YES)
      {
         getRebalDefAllocList(pDefaultAllocationList, idDataGroup);
         return(GETCURRENTHIGHESTSEVERITY());
      }
      else if (strDefaultAlloc == NO)
      {
         objAMSMstrList.getFieldByAMSCode(RB_TYPE,strAMSCode,dstrEffectiveDate, ifds::FundAlloc, 
            strFundAlloc, idDataGroup, false);
         if (strFundAlloc == YES)
         {
            getAMSDefAllocList(pDefaultAllocationList, idDataGroup);
            return(GETCURRENTHIGHESTSEVERITY());
         }
      }
   }

   getShrDefAllocList(pDefaultAllocationList, idDataGroup);   

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void TradeFundAllocList::getStrKey(DString &strKey, const BFData *data)
{
   TRACE_METHOD( CLASSNAME, I_( "getStrKey" ) );

   if( !data )
   {
      BFCBO::getStrKey( strKey, data );
   }
   else
   {
	  DString tmpkey = NULL_STRING;
      data->getElementValue( ifds::AccountNum, tmpkey );
	  strKey += tmpkey.strip();
	  strKey += I_(" ");
	  data->getElementValue( ifds::FundCode, tmpkey );
	  strKey += tmpkey.strip();
	  strKey += I_(" ");
	  data->getElementValue( ifds::ClassCode, tmpkey );
	  strKey += tmpkey.strip();
   }
}


//******************************************************************************
void TradeFundAllocList::setFullRedemption ( const BFDataGroupId& idDataGroup, bool isFullRedeem )
{
   TRACE_METHOD( CLASSNAME, I_( "setFullRedemption" ) );

   if ( isFullRedeem )
   {      
      BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
      while( !iter.end() )
      {
         TradeFundAlloc* pTradeFundAlloc = dynamic_cast<TradeFundAlloc*>(iter.getObject());         
			pTradeFundAlloc->setFieldReadOnly( ifds::AllocAmount, idDataGroup, true );

         ++iter; 
      }
   }
   else
   {
      BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
      while( !iter.end() )
      {
         TradeFundAlloc* pTradeFundAlloc = dynamic_cast<TradeFundAlloc*>(iter.getObject());
            
	  	   pTradeFundAlloc->setFieldReadOnly( ifds::AllocAmount, idDataGroup, false );
         ++iter; 
      }
   }

}
//******************************************************************************
void TradeFundAllocList::changeFieldsForRebook()
{
   BFObjIter iter( *this, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() )
   {
      TradeFundAlloc* pTradeFundAlloc = dynamic_cast<TradeFundAlloc*>( iter.getObject() );
      pTradeFundAlloc->changeFieldsForRebook();   
      ++iter;
   }
}

//******************************************************************************
void TradeFundAllocList::setAllAllocsFndClsValidFlag(bool isValid, const BFDataGroupId& idDataGroup)
{
    BFObjIter iter(*this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

    while (!iter.end())
    {
        TradeFundAlloc *pTradeFundAlloc = dynamic_cast<TradeFundAlloc*>(iter.getObject());

        if (pTradeFundAlloc && !iter.isDummy())
        {
            pTradeFundAlloc->setFieldValid(ifds::SoftCapCheck, idDataGroup, isValid);
            pTradeFundAlloc->setFieldUpdated(ifds::SoftCapCheck, idDataGroup, true);
        }

        ++iter;
    }
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TradeFundAllocList.cpp-arc  $
// 
//    Rev 1.28   Jan 16 2006 11:23:54   fengyong
// Incident 520481 - fix API allocation problem
// 
//    Rev 1.27   Jul 08 2005 09:33:30   Yingbaol
// PET1235,FN01:transaction cancellation rebook
// 
//    Rev 1.26   Feb 22 2005 11:36:24   winnie
// PTS 123456 Testing checkin with no change
// 
//    Rev 1.25   Dec 31 2004 13:38:50   popescu
// PTS 10037395, settlement currency should be set as required if for redemption the account closes or a full redemption is processed. Also, isFullNotCloseAcctRed method name to isFullRedemption
// 
//    Rev 1.24   Nov 14 2004 14:57:58   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.23   Nov 06 2004 00:43:18   popescu
// PET 1117/06, synch changes
// 
//    Rev 1.22   Sep 09 2004 10:05:44   ZHANGCEL
// Code clean up by grouping the transtype
// 
//    Rev 1.21   Oct 21 2003 13:44:10   VADEANUM
// PTS 10023082 
// 
//    Rev 1.20   Oct 14 2003 10:45:50   VADEANUM
// PTS 10021935 - Allocation screen Percent Total is 200 - if FullRedCode, then make sure percentage is 0 for each fund that is redeemed.
// 
//    Rev 1.19   Sep 26 2003 17:29:54   VADEANUM
// PTS 10021901 & 10021935 - WHTax - Allocations - Work in progress.
// 
//    Rev 1.18   Aug 25 2003 18:32:52   WINNIE
// Full Redemption code for not closing account : add new field FullRedem to indicate if a non close account redemption code is indicated. New method SetFullRedemption to invoke TradeFundAlloc to disable AllocPercentage and set to 100%; change doValidateAll to skip the total percentage validation if non close account full redemption code is indicated.
// 
//    Rev 1.17   Jul 23 2003 11:08:00   linmay
// sync with getamsmstrlist
// 
//    Rev 1.16   May 16 2003 17:18:50   popescu
// now the transaction details object asks trade fund alloc for its plit commission
// 
//    Rev 1.15   Apr 21 2003 09:48:48   YINGBAOL
// change getFieldByAMSCode sync.
// 
//    Rev 1.14   Mar 21 2003 18:27:14   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.13   Feb 18 2003 10:35:36   FENGYONG
// Add getStrKey
// 
//    Rev 1.12   Jan 16 2003 17:04:48   KOVACSRO
// Fix for previous implementation : if view 179 fails, just return.
// 
//    Rev 1.11   Jan 15 2003 17:36:18   KOVACSRO
// The rules for picking up default allocations have changed.
// 
//    Rev 1.10   Dec 31 2002 13:51:40   KOVACSRO
// added multicurrency check.
// 
//    Rev 1.9   Nov 29 2002 10:53:50   KOVACSRO
// Added support for different kind of default allocations.
// 
//    Rev 1.8   Oct 09 2002 23:55:10   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.7   Aug 29 2002 12:56:56   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.6   Aug 01 2002 11:35:38   KOVACSRO
// format amount fix
// 
//    Rev 1.5   Jul 31 2002 14:59:32   KOVACSRO
// Added getStrKeyForNewItem
// 
//    Rev 1.4   Jun 27 2002 17:21:42   KOVACSRO
// AllocAmtType versus AmountType.
// 
//    Rev 1.3   24 May 2002 15:50:08   KOVACSRO
// some fixes.
// 
//    Rev 1.2   22 May 2002 18:30:08   PURDYECH
// BFData Implementation
// 
//    Rev 1.1   08 May 2002 17:06:50   KOVACSRO
// More implementation.
// 
//    Rev 1.0   29 Apr 2002 16:57:50   KOVACSRO
// Initial revision.
 * 
 * 
 */