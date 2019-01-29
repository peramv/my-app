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
//    Copyright 2002 By International Financial
//
//
//******************************************************************************
//
// ^FILE   : DilutionAllocList.cpp
// ^AUTHOR : 
// ^DATE   : Feb 21, 2005
//
// ^CLASS    : DilutionAllocList 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "dilutionalloclist.hpp"

#include "dstcommonfunction.hpp"
#include "mgmtco.hpp"
#include "dilutionalloc.hpp"
#include "trade.hpp"
#include "Broker.hpp"
#include "BrokerList.hpp"
#include "Intermediary.hpp"
#include "IntermediaryList.hpp"
#include "MFAccount.hpp"
#include "TransactionList.hpp"
#include "TransactionDetails.hpp"
#include "TradeSearchCriteria.hpp"
#include "DilutionValidation.hpp"
#include <ifastdataimpl\dse_dstc0339_req.hpp>
#include <ifastdataimpl\dse_dstc0339_vw.hpp>


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest DILUTION_LIST;
}

namespace  
{
   const I_CHAR * const CLASSNAME      = I_( "DilutionAllocList" );  
   const I_CHAR * const YES            = I_( "Y" );
   const I_CHAR * const NO             = I_( "N" );
   const I_CHAR * const BOTH           = I_( "0" );
   const I_CHAR * const USE_PERCENT    = I_( "1" );
   const I_CHAR * const USE_DATE       = I_( "2" );
   const I_CHAR * const FSRV           = I_( "FSRV" );
   const I_CHAR * const SETTLE_NETWORK_ELIGIBLE = I_( "ED,PW,AW,ID" );
}
namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const BROKER_DIFFERENT_THAN_ACCOUNT_BROKER;
   extern CLASS_IMPORT I_CHAR * const DILUTION_LINK_ID_AUTO_GENERATE;
   extern CLASS_IMPORT I_CHAR * const ONLY_ONE_REC_WITH_100_PERCENT_ALLOWED;
}
namespace CND
{
   extern const long ERR_DUPLICATE_RECORD;
   extern const long ERR_DILUTION_ALLOC_AT_LEAST_ONE_RECORD_REQUIRED;
   extern const long ERR_DILUTION_ALLOC_SAME_RESP_DATE;
   extern const long ERR_SUM_OF_PERCENTAGES_NOT_0;
   extern const long ERR_SUM_OF_PERCENTAGES_NOT_100;
   extern const long ERR_MISSING_ACCOUNTABLE_PARTY_FOR_TRADEDATE;
   extern const long ERR_BROKER_DIFFERENT_THAN_ACCOUNT_BROKER;
   extern const long WARN_BROKER_DIFFERENT_THAN_ACCOUNT_BROKER;
   extern const long ERR_DILUTION_LINK_ID_AUTO_GENERATE;
   extern const long WARN_DILUTION_LINK_ID_AUTO_GENERATE;
   extern const long ERR_ONLY_ONE_REC_WITH_100_PERCENT_ALLOWED;
   extern const long WARN_ONLY_ONE_REC_WITH_100_PERCENT_ALLOWED;
}

namespace ifds
{   
   extern CLASS_IMPORT const BFTextFieldId ReadOnly; 
   extern CLASS_IMPORT const BFTextFieldId SplitAcCode;
   extern CLASS_IMPORT const BFTextFieldId SplitPreferenceOption;
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFTextFieldId IsNetworkSettleEligible;
   extern CLASS_IMPORT const BFTextFieldId IsDilutionNSMEligible;
   extern CLASS_IMPORT const BFTextFieldId CPFRefundApplicable;
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFTextFieldId rxFundCode;
   extern CLASS_IMPORT const BFTextFieldId rxClassCode;
   extern CLASS_IMPORT const BFTextFieldId BrokCompliantNW;
   extern CLASS_IMPORT const BFTextFieldId BrokCssStatus;
   extern CLASS_IMPORT const BFTextFieldId InterCode;
   extern CLASS_IMPORT const BFTextFieldId IntrCssStatus;
   extern CLASS_IMPORT const BFTextFieldId AcctDesignation;
   extern CLASS_IMPORT const BFTextFieldId Cancelled;
   extern CLASS_IMPORT const BFTextFieldId Reversal;
   extern CLASS_IMPORT const BFTextFieldId Settled;
   extern CLASS_IMPORT const BFTextFieldId Allocation;
   extern CLASS_IMPORT const BFTextFieldId SearchType;
   extern CLASS_IMPORT const BFTextFieldId DilutionLinkNum;
   extern CLASS_IMPORT const BFTextFieldId FundSERVClient;
   extern CLASS_IMPORT const BFTextFieldId ShowExSysDilPymtNSM;
   extern CLASS_IMPORT const BFTextFieldId MatchingKey;
}

//-------------------------------------------------------------------
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags    
   { ifds::ReadOnly,	   BFCBO::CALCULATED_FIELD,	0 },  
   
   { ifds::RefundAmount,         BFCBO::NONE,            0 },
   { ifds::DilutionAmount,       BFCBO::NONE,            0 },
   { ifds::RefundFXRate,         BFCBO::NONE,            0 },
   { ifds::RefundCurrency,       BFCBO::NONE,            0 },
   { ifds::RefundOption,         BFCBO::NONE,            0 },
   { ifds::RefundPayType,        BFCBO::NONE,            0 },
   { ifds::DilutionAvail,        BFCBO::NONE,            0 },
   { ifds::TransNum,			 BFCBO::NONE,            0 },
   { ifds::SettleNetwork,        BFCBO::NONE,            0 },
   { ifds::IsNetworkSettleEligible,	   BFCBO::CALCULATED_FIELD,	0 },
   { ifds::DilutionLinkNum,		 BFCBO::IMMEDIATE_VALIDATION,   0 },
   { ifds::MatchingKey,          BFCBO::IMMEDIATE_VALIDATION,   0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//*********************************************************************************
DilutionAllocList::DilutionAllocList (BFAbstractCBO &parent) : MFCanBFCbo (parent)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL );

   setObjectAsList();
}

//*********************************************************************************
DilutionAllocList::~DilutionAllocList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//*********************************************************************************
SEVERITY DilutionAllocList::init ( const DString &transId,
                                   const BFDataGroupId &idDataGroup, 
                                   const DString &dstrTradeDate,
                                   const DString &dstrSettleDate,
                                   const DString &dstrTransNum,
                                   const DString &dstrTrack, /*=I_("N")*/
                                   const DString &dstrPageName /*=NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   _dstrTransHistTradeDate  = dstrTradeDate;
   _dstrTransHistSettleDate = dstrSettleDate;
   _dstrTransId             = transId;
// receive data from back end

   DString mgmtCoIdOut;	
   BFData requestData339 (ifds::DSTC0339_REQ);
   requestData339.setElementValue (ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   requestData339.setElementValue (ifds::Track, dstrTrack );
   requestData339.setElementValue (ifds::Activity, dstrPageName );
   requestData339.setElementValue (ifds::NextKey, NULL_STRING);
   requestData339.setElementValue (ifds::TransId, transId);
   ReceiveData ( DSTC_REQUEST::DILUTION_LIST, 
                 requestData339, 
                 ifds::DSTC0339_VW, 
                 DSTCRequestor (getSecurity(), false, false));


   setFieldReadOnly ( ifds::RefundAmount,	idDataGroup,	true);
   setFieldReadOnly ( ifds::DilutionAmount,	idDataGroup,	true);
   setFieldReadOnly ( ifds::RefundFXRate,	idDataGroup,	true);
   setFieldReadOnly ( ifds::RefundCurrency, idDataGroup,	true);
   setFieldReadOnly ( ifds::RefundOption,	idDataGroup,	true);
   setFieldReadOnly ( ifds::RefundPayType,	idDataGroup,	true);  

   initCPFRefundRelatedFields(idDataGroup);

   setFieldValid( ifds::RefundOption, idDataGroup, true);

   setFieldNoValidate(ifds::TransNum, dstrTransNum, idDataGroup, false,true, false, false);
   DString dstrIsSettleNetworkEligible;
   refreshIsSettleNetworkEligible(dstrIsSettleNetworkEligible, idDataGroup);
   setFieldNoValidate(ifds::IsNetworkSettleEligible, dstrIsSettleNetworkEligible, idDataGroup, false, true, false, false);
   settleNetworkRelateChanges(BF::HOST);
   
   return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************
SEVERITY DilutionAllocList::initNew ( const BFDataGroupId &idDataGroup, 
                                      const DString &dstrTradeDate,
                                      const DString &dstrSettleDate,
                                      const DString &dstrTrack, /*=I_("N")*/
                                      const DString &dstrPageName /*=NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   _dstrTransHistTradeDate  = dstrTradeDate;
   _dstrTransHistSettleDate = dstrSettleDate;

   initCPFRefundRelatedFields(idDataGroup);
   refreshNSMEligibility(ifds::SettleNetwork, idDataGroup);

   //Remove 'N/A' item from the list. 
   //The 'N/A' is assigned by view program when no transaction found (for existing record).
   BFProperties *pBFProperties;
   DString dstrRefundOptionSet;

   pBFProperties = getFieldProperties (ifds::RefundOption, idDataGroup);
   pBFProperties->getAllSubstituteValues (dstrRefundOptionSet);
   dstrRefundOptionSet = removeItemFromSubtList(dstrRefundOptionSet, I_("N/A"));   
   setFieldAllSubstituteValues(ifds::RefundOption, idDataGroup, dstrRefundOptionSet);

   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************
SEVERITY DilutionAllocList::doCreateObject (const BFData& data, BFCBO *&pObjOut)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "doCreateObject" ));

   pObjOut =  new DilutionAlloc( *this );
   ((DilutionAlloc* )pObjOut )->init(data);
   return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************
SEVERITY DilutionAllocList::doCreateNewObject ( BFCBO *&pBase, 
                                                DString &strKey, 
                                                const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("doCreateNewObject"));
   DilutionAlloc* pDilutionAlloc = new DilutionAlloc (*this);
   pDilutionAlloc->initNew (idDataGroup);
   pBase = pDilutionAlloc;
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DilutionAllocList::doApplyRelatedChanges ( const BFFieldId &idField, 
                                                    const BFDataGroupId& idDataGroup)
{
   MAKEFRAME2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));

   if (idField == ifds::ReadOnly)
   {
      setValidFlag (ifds::ReadOnly, idDataGroup, true);
   }
   /*else if (idField == ifds::TransNum)
   {
	   refreshNSMEligibility(ifds::IsDilutionNSMEligible, idDataGroup);
	   refreshNSMEligibility(ifds::IsNetworkSettleEligible, idDataGroup);
      
      DString dstrSettleNetwork;
      getFieldBeforeImage(ifds::SettleNetwork, dstrSettleNetwork);
      setFieldNoValidate(ifds::SettleNetwork, dstrSettleNetwork.stripAll(), idDataGroup, false, true, false, false);

   }*/
   else if(idField == ifds::IsNetworkSettleEligible) 
   {
		setFieldNoValidate(ifds::SettleNetwork, I_(""), idDataGroup, false);
   }
   else if(idField == ifds::SettleNetwork)
   {
     settleNetworkRelateChanges(idDataGroup); 
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY DilutionAllocList::setField( const BFFieldId& idField, 
                                      const DString& dstrValue,
                                      const BFDataGroupId& idDataGroup, 
                                      bool bFormatted, 
                                      bool bSideEffect,
                                      bool bCheckCurrentValue)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("setField"));
   BFCBO::setField( idField, dstrValue, idDataGroup, bFormatted, bSideEffect );

   if (idField == ifds::ReadOnly)
   {
      BFObjIter iter ( *this, 
                       idDataGroup);
      iter.begin();
      while (!iter.end ())
      {
         DilutionAlloc *pDilutionAlloc_ = dynamic_cast <DilutionAlloc*> (iter.getObject ());

         if (pDilutionAlloc_)
         {
            pDilutionAlloc_->setFieldsReadOnly (BF::HOST, dstrValue == YES);
         }
         ++iter;
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************
SEVERITY DilutionAllocList::doValidateField(const BFFieldId &idField,
                                            const DString &strValue,
                                            const BFDataGroupId &idDataGroup)
{
  MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField"));

  DString strMarket = DSTCommonFunctions::getMarket();

  if(idField == ifds::DilutionLinkNum || (strMarket == MARKET_IDS::CANADA && idField == ifds::MatchingKey))
  {
    DString dstrAccountNum, dstrFundCode, dstrClassCode;
    
    Trade* pTrade = dynamic_cast<Trade*>(getParent());
    if(pTrade != NULL) 
    {
      pTrade->getField(ifds::AccountNum, dstrAccountNum, idDataGroup, false);
      pTrade->getField(ifds::FromFund, dstrFundCode, idDataGroup, false);
      pTrade->getField(ifds::FromClass, dstrClassCode, idDataGroup, false);	   
    }
    else
    {
      TransactionList *pTransactionList = getTransactionList(idDataGroup);
      if(pTransactionList != NULL)
      {
        TransactionDetails *pTransactionDetails = NULL;
        if(_dstrTransId.stripAll().empty())
        {
          DString transId;
          for(BFObjIter iter(*pTransactionList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
              !iter.end();
              ++iter)
          {
            DString transType;
            auto details = dynamic_cast<TransactionDetails*>(iter.getObject());
            if(details == NULL) continue;
            
            details->getField(ifds::TransType, transType, idDataGroup);
            if(transType == I_("ID")) continue;
            
            pTransactionDetails = details;
            pTransactionDetails->getField(ifds::TransId, transId, idDataGroup);
            pTransactionDetails->getDetails(transId);
          }
        }
        else
        {
          for(BFObjIter iter(*pTransactionList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
              !iter.end();
              ++iter)
          {
            DString iterTransId;
            iter.getObject()->getField(ifds::TransId, iterTransId, idDataGroup);
            if(iterTransId == _dstrTransId) 
            {
              pTransactionDetails = dynamic_cast<TransactionDetails*>(iter.getObject());
              break;
            }
          }
          if(pTransactionDetails != NULL) pTransactionDetails->getDetails(_dstrTransId);
        }
        
        pTransactionDetails->getField(ifds::AccountNum, dstrAccountNum, idDataGroup, false);
        pTransactionDetails->getField(ifds::rxFundCode, dstrFundCode, idDataGroup, false);
        pTransactionDetails->getField(ifds::rxClassCode, dstrClassCode, idDataGroup, false);
      }
    }
    
    DString dstrSettleNetwork, dstrDilutionLinkNum, dstrDilutionNSM, dstrMatchingKey(NULL_STRING);
    getField(ifds::SettleNetwork, dstrSettleNetwork, idDataGroup, false);
    getField(ifds::DilutionLinkNum, dstrDilutionLinkNum, idDataGroup, false);
  
    if (strMarket == MARKET_IDS::CANADA)
		getField(ifds::MatchingKey, dstrMatchingKey, idDataGroup, false);

    for(BFObjIter iter(*this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
        !iter.end();
        ++iter)
    {
      DilutionAlloc *pDilutionAlloc = dynamic_cast<DilutionAlloc*>(iter.getObject());
      pDilutionAlloc->getField(ifds::DilutionNSM, dstrDilutionNSM, idDataGroup, false);
      if(dstrDilutionNSM != I_("01"))
        break;
    }
    if(dstrSettleNetwork == FSRV || dstrDilutionNSM == I_("02"))
    {
      if(!dstrDilutionLinkNum.empty())
      {
        DilutionValidation *pDilutionValidation = new DilutionValidation(*this);
		SEVERITY iDilutionValidation;

		if (strMarket == MARKET_IDS::CANADA && idField == ifds::MatchingKey && !dstrMatchingKey.empty())
			iDilutionValidation = pDilutionValidation->init(dstrAccountNum, dstrFundCode, dstrClassCode, dstrDilutionLinkNum, dstrMatchingKey);
		else 
			iDilutionValidation = pDilutionValidation->init(dstrAccountNum, dstrFundCode, dstrClassCode, dstrDilutionLinkNum) ;

        if(iDilutionValidation > WARNING)
        {
          delete pDilutionValidation;
          pDilutionValidation = NULL;
        }
        if(pDilutionValidation)
        {
          pDilutionValidation->addConditions(dstrDilutionNSM);
        }
      }
    }
  }
  return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************
SEVERITY DilutionAllocList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   BFObjIter iter1(*this, idDataGroup, 0,BFObjIter::ITERTYPE::NON_DELETED);
   BFObjIter iter2(*this, idDataGroup, 0,BFObjIter::ITERTYPE::NON_DELETED);

   DString dstrSplitMethod;
   getDilutionSplitMethod( dstrSplitMethod, idDataGroup );
   dstrSplitMethod.stripAll();	

   double dTotalPercentage = 0;

   //at least one dilution record need when dilution system feature is turned on.
   DString dstrDilution, dstrFundSERVClient;
   getWorkSession().getOption (ifds::SplitAcCode, dstrDilution, BF::HOST, false);
   getWorkSession().getOption (ifds::FundSERVClient, dstrFundSERVClient, BF::HOST, false);

   iter1.begin();
   if( dstrDilution == YES || (dstrDilution == NO && dstrFundSERVClient == YES) )
   {
      while (!iter1.end())
      {
         if (!iter1.isDummy())
            break;
         ++iter1;
      }

      BFObjIter iterDeleted (*this, idDataGroup, 0);
      if( iter1.end() && iterDeleted.end() /*no deletes*/)
      {
         // At least one Dilution Allocation must be setup.
         ADDCONDITIONFROMFILE( CND::ERR_DILUTION_ALLOC_AT_LEAST_ONE_RECORD_REQUIRED );
         return GETCURRENTHIGHESTSEVERITY();
      }
   }

   /* If SplitAcCode = No, the record can have only one. */
   int numOfItem = iter1.getNumberOfItemsInList();
   if(numOfItem > 1 && (dstrDilution == NO && dstrFundSERVClient == YES))
   {
     getErrMsg(IFASTERR::ONLY_ONE_REC_WITH_100_PERCENT_ALLOWED,
               CND::ERR_ONLY_ONE_REC_WITH_100_PERCENT_ALLOWED,
               CND::WARN_ONLY_ONE_REC_WITH_100_PERCENT_ALLOWED,
               idDataGroup );
   }

   bool bTradeRespDate = false;
   iter1.begin();
   while (!iter1.end())
   {
      DilutionAlloc *pDilutionAlloc1 = dynamic_cast<DilutionAlloc*>(iter1.getObject());

	  if(pDilutionAlloc1)
	  {
		  DString dstrAccountable, dstrRespDate;   
		  pDilutionAlloc1->getField( ifds::Accountable, dstrAccountable, idDataGroup, false );
		  pDilutionAlloc1->getField( ifds::RespDate,    dstrRespDate,    idDataGroup, false );

		  if (DSTCommonFunctions::CompareDates (dstrRespDate, _dstrTransHistTradeDate) == DSTCommonFunctions::EQUAL)
			 bTradeRespDate = true;

		  iter2.begin();
		  while (!iter2.end() )
		  {
			 DilutionAlloc *pDilutionAlloc2 = dynamic_cast<DilutionAlloc*>(iter2.getObject());
			 if (pDilutionAlloc2 && (pDilutionAlloc1 != pDilutionAlloc2))
			 {
				DString accountable_, respDate_;
				pDilutionAlloc2->getField(ifds::Accountable, accountable_, idDataGroup, false);
				pDilutionAlloc2->getField(ifds::RespDate,    respDate_,    idDataGroup, false );

				accountable_.stripAll();
				// Duplicate check based on Accountable code
				if ( accountable_ == dstrAccountable )
				{
				   ADDCONDITIONFROMFILE (CND::ERR_DUPLICATE_RECORD);
				   break;
				}

				// Resp Date check
				else if ( I_( "D" ) == dstrSplitMethod &&
				   DSTCommonFunctions::CompareDates( dstrRespDate, respDate_ ) == DSTCommonFunctions::EQUAL )
				{
				   // Same Responsability Date cannot be assigned to more than one accountable party.						      								
				   ADDCONDITIONFROMFILE( CND::ERR_DILUTION_ALLOC_SAME_RESP_DATE );
				   break;
				}
			 }

			 ++iter2;
		  }

		  DString dstrPercent;
		  pDilutionAlloc1->getField (ifds::AllocPercent, dstrPercent, idDataGroup, false);
		  dstrPercent.strip().stripAll(I_CHAR(','));

		  I_CHAR *stopstring;
		  double dPercentage = wcstod(dstrPercent.c_str(), &stopstring); 
		  dTotalPercentage += dPercentage;
	  }
	  ++iter1;
   }

   if ( GETCURRENTHIGHESTSEVERITY() <= WARNING )
   {
      DString dstrSplitmethod;
      if ( getDilutionSplitMethod( dstrSplitMethod,idDataGroup ) <= WARNING )
      {
         if ( I_( "D" ) == dstrSplitMethod)
         {
            if (fabs(dTotalPercentage) != 0)
            {
               // Allocation percentages must sum up to 0%.
               ADDCONDITIONFROMFILE( CND::ERR_SUM_OF_PERCENTAGES_NOT_0 );
            }
            else if ( checkRespDate(idDataGroup) && ( bTradeRespDate == false ) )
            {
               ADDCONDITIONFROMFILE( CND::ERR_MISSING_ACCOUNTABLE_PARTY_FOR_TRADEDATE );
            }
         }
         else if ( I_( "P" ) == dstrSplitMethod && fabs(dTotalPercentage) != 100 )
         {
            // Allocation percentages must sum up to 100%.
            ADDCONDITIONFROMFILE( CND::ERR_SUM_OF_PERCENTAGES_NOT_100 );
         }
      }
   }

   if(TransactionList* pTransactionList = getTransactionList(idDataGroup))
   {
      DString accBroker, transBroker;
      DString dstrAccountNum;

      BFObjIter iter(*pTransactionList, idDataGroup, false, BFObjIter::NON_DELETED);
      if(!iter.end())
      {
         iter.getObject()->getField(ifds::BrokerCode, transBroker, idDataGroup);
         iter.getObject()->getField(ifds::AccountNum, dstrAccountNum, idDataGroup);
      }
      MFAccount *pAccount = NULL;
      if(!dstrAccountNum.strip().empty() && 
         getWorkSession().getMFAccount(idDataGroup, dstrAccountNum, pAccount) <=WARNING &&
         pAccount)
      {
         pAccount->getField(ifds::BrokerCode, accBroker, idDataGroup);
      }

      if(!accBroker.strip().empty() &&
         !transBroker.strip().empty() &&
         accBroker != transBroker)
	   {
		   getErrMsg(IFASTERR::BROKER_DIFFERENT_THAN_ACCOUNT_BROKER,
				   CND::ERR_BROKER_DIFFERENT_THAN_ACCOUNT_BROKER,
				   CND::WARN_BROKER_DIFFERENT_THAN_ACCOUNT_BROKER,
				   idDataGroup );
	   }
   }
   
   DString dstrAccountNum, dstrFundCode, dstrClassCode;
    
   Trade* pTrade = dynamic_cast<Trade*>(getParent());
   if(pTrade != NULL) 
   {
     pTrade->getField(ifds::AccountNum, dstrAccountNum, idDataGroup, false);
     pTrade->getField(ifds::FromFund, dstrFundCode, idDataGroup, false);
     pTrade->getField(ifds::FromClass, dstrClassCode, idDataGroup, false);	   
   }
   else
   {
     TransactionList *pTransactionList = getTransactionList(idDataGroup);
     if(pTransactionList != NULL)
     {
       TransactionDetails *pTransactionDetails = NULL;
       if(_dstrTransId.stripAll().empty())
       {
         DString transId;
         for(BFObjIter iter(*pTransactionList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
             !iter.end();
             ++iter)
         {
           DString transType;
           auto details = dynamic_cast<TransactionDetails*>(iter.getObject());
           if(details == NULL) continue;
            
           details->getField(ifds::TransType, transType, idDataGroup);
           if(transType == I_("ID")) continue;
            
           pTransactionDetails = details;
           pTransactionDetails->getField(ifds::TransId, transId, idDataGroup);
           pTransactionDetails->getDetails(transId);
         }
       }
       else
       {
         for(BFObjIter iter(*pTransactionList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
             !iter.end();
             ++iter)
         {
           DString iterTransId;
           iter.getObject()->getField(ifds::TransId, iterTransId, idDataGroup);
           if(iterTransId == _dstrTransId) 
           {
             pTransactionDetails = dynamic_cast<TransactionDetails*>(iter.getObject());
             break;
           }
         }
         if(pTransactionDetails != NULL) pTransactionDetails->getDetails(_dstrTransId);
       }
        
       pTransactionDetails->getField(ifds::AccountNum, dstrAccountNum, idDataGroup, false);
       pTransactionDetails->getField(ifds::rxFundCode, dstrFundCode, idDataGroup, false);
       pTransactionDetails->getField(ifds::rxClassCode, dstrClassCode, idDataGroup, false);
     }
   }
    
   DString dstrSettleNetwork, dstrDilutionLinkNum, dstrDilutionNSM;
   getField(ifds::SettleNetwork, dstrSettleNetwork, idDataGroup, false);
   getField(ifds::DilutionLinkNum, dstrDilutionLinkNum, idDataGroup, false);
    
   for(BFObjIter iter(*this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
       !iter.end();
       ++iter)
   {
     DilutionAlloc *pDilutionAlloc = dynamic_cast<DilutionAlloc*>(iter.getObject());
     pDilutionAlloc->getField(ifds::DilutionNSM, dstrDilutionNSM, idDataGroup, false);
     if(dstrDilutionNSM != I_("01"))
       break;
   }
   /* Validate if DilutionLinkNum is empty, then shows warning message. */
   if(dstrSettleNetwork == FSRV || dstrDilutionNSM == I_("02"))
   {
     if(dstrDilutionLinkNum.empty())
     {
       getErrMsg(IFASTERR::DILUTION_LINK_ID_AUTO_GENERATE,
                 CND::ERR_DILUTION_LINK_ID_AUTO_GENERATE,
                 CND::WARN_DILUTION_LINK_ID_AUTO_GENERATE,
                 idDataGroup);
     }
   }
   /* Validate if DilutionLinkNum is related to existing FSRV LinkNum, then shows warning message. */
   if(dstrSettleNetwork == FSRV && dstrDilutionNSM == I_("03"))
   {
     if(!dstrDilutionLinkNum.empty())
     {
        DilutionValidation *pDilutionValidation = new DilutionValidation(*this);
        if(pDilutionValidation->init(dstrAccountNum, dstrFundCode, dstrClassCode, dstrDilutionLinkNum) > WARNING)
        {
          delete pDilutionValidation;
          pDilutionValidation = NULL;
        }
        if(pDilutionValidation)
        {
          pDilutionValidation->addConditions(dstrDilutionNSM);
        }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DilutionAllocList::addNewAllocation( const DString& accountable, 
                                              const DString& backDatedReason, 
                                              const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("addNewAllocation"));

   DilutionAlloc *pDilutionAlloc = NULL;
   BFObjectKey objKey (accountable, idDataGroup);
   pDilutionAlloc = dynamic_cast <DilutionAlloc *> (getNewListItem (objKey));

   if (!accountable.empty())
   {
      pDilutionAlloc->setField (ifds::Accountable, accountable, idDataGroup );
   }
   if (!backDatedReason.empty())
   {
      pDilutionAlloc->setField (ifds::BackDatedReason, backDatedReason, idDataGroup );
   }
   DString strSplitPreferenceOption;
   getWorkSession().getOption ( ifds::SplitPreferenceOption, 
                                strSplitPreferenceOption, 
                                BF::HOST, 
                                false );
   strSplitPreferenceOption.strip().upperCase();

   if ( strSplitPreferenceOption == USE_DATE )
   {
      pDilutionAlloc->setField( ifds::AllocPercent, I_("0"), idDataGroup, false );
   }
   else // PERCENT & BOTH
   {
      pDilutionAlloc->setField( ifds::AllocPercent, I_("100"), idDataGroup, false );
   }

   pDilutionAlloc->setFieldUpdated (ifds::AllocPercent, idDataGroup, false);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DilutionAllocList::cloneForReebokWithNewTransId (const DString& transId, DilutionAllocList* pDilutionAllocList, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("cloneForReebok"));

   if (pDilutionAllocList != NULL)
   {
      DString dstrOriginalSettleNetwork, dstrOriginalDilutionLinkNum;
      pDilutionAllocList->getField(ifds::SettleNetwork, dstrOriginalSettleNetwork, idDataGroup);
      setFieldNoValidate(ifds::SettleNetwork, dstrOriginalSettleNetwork, idDataGroup, false, false, true, false);
	  pDilutionAllocList->getField(ifds::DilutionLinkNum, dstrOriginalDilutionLinkNum, idDataGroup);
      setFieldNoValidate(ifds::DilutionLinkNum, dstrOriginalDilutionLinkNum, idDataGroup, false, false, true, false);

      BFObjIter iter( *pDilutionAllocList, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
      iter.begin();

      while (!iter.end())
      {
         BFData rpBFData0339Repeat (ifds::DSTC0339_VWRepeat_Record);

         dynamic_cast<BFCBO*>(iter.getObject())->getData (rpBFData0339Repeat, idDataGroup);

         //create the cloned object

         DString accountable;

         rpBFData0339Repeat.getElementValue (ifds::Accountable, accountable);
         accountable.strip().upperCase();
         //set or clear elements for the cloned repeat.
         rpBFData0339Repeat.setElementValue (ifds::TransId, transId);
         //clear fields
         rpBFData0339Repeat.setElementValue (ifds::DilVersion, NULL_STRING);
         rpBFData0339Repeat.setElementValue (ifds::SplitAccCodeRID, NULL_STRING);
         rpBFData0339Repeat.setElementValue (ifds::ProcessDate, NULL_STRING);
         rpBFData0339Repeat.setElementValue (ifds::Username, NULL_STRING);
         rpBFData0339Repeat.setElementValue (ifds::ModDate, NULL_STRING);
         rpBFData0339Repeat.setElementValue (ifds::ModUser, NULL_STRING);

         DilutionAlloc *pDilutionAlloc (NULL);

         BFObjectKey objKey (accountable, idDataGroup);
         pDilutionAlloc = dynamic_cast <DilutionAlloc *> (getNewListItem (objKey));

         pDilutionAlloc->initNew (rpBFData0339Repeat, idDataGroup);

         ++iter;
      }
   }

   DString dstrIsSettleNetworkEligible;
   refreshIsSettleNetworkEligible(dstrIsSettleNetworkEligible, idDataGroup);
   setFieldNoValidate(ifds::IsNetworkSettleEligible, dstrIsSettleNetworkEligible, idDataGroup, false, true, false, false);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DilutionAllocList::getDilutionSplitMethod( DString &dstrSplitMethod,
                                                    const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getDilutionSplitMethod"));

   DString strSplitPrefOpt;
   getWorkSession().getOption ( ifds::SplitPreferenceOption, strSplitPrefOpt, BF::HOST, false );
   strSplitPrefOpt.strip().upperCase();

   if ( strSplitPrefOpt == USE_PERCENT )
   {
      dstrSplitMethod = I_( "P" );      // Percentage
   }
   else if ( strSplitPrefOpt == USE_DATE )
   {
      dstrSplitMethod = I_( "D" );      // Date
   }
   else // both
   {
      // if generic control allow to use both of date or percentage
      // choice it from either date or percentage by using existing logic
      BFObjIter iter( *this, idDataGroup, 0,BFObjIter::ITERTYPE::NON_DELETED );

      iter.begin();
      if ( !iter.isDummy() )
      {
         while (!iter.end())
         {
            DilutionAlloc *pDilutionAlloc1 = dynamic_cast<DilutionAlloc*>( iter.getObject() );
            if ( NULL != pDilutionAlloc1 )
            {
               DString dstrPercent, dstrRespDate;
               pDilutionAlloc1->getField (ifds::AllocPercent, dstrPercent,  idDataGroup, false);
               pDilutionAlloc1->getField( ifds::RespDate,     dstrRespDate, idDataGroup );
               dstrRespDate.stripAll();
               double dPercent = DSTCommonFunctions::convertToDouble( dstrPercent );

               // If first record, then decide split method
               // If Responsability Date was modified for the first record, 
               // then the Method is by Date, else is by Percentage
               if ( dstrRespDate != I_("12319999") && dstrRespDate != NULL_STRING )
                  dstrSplitMethod = I_( "D" );      // Date
               else if ( 0 != dPercent )
                  dstrSplitMethod = I_( "P" );      // Percentage

               break;
            }
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool DilutionAllocList::checkRespDate( const BFDataGroupId& idDataGroup )
{
   DString strSplitPrefOpt;
   getWorkSession().getOption ( ifds::SplitPreferenceOption, strSplitPrefOpt, BF::HOST, false );
   strSplitPrefOpt.strip().upperCase();

   BFObjIter iter(*this, idDataGroup, 0,BFObjIter::ITERTYPE::NON_DELETED);
   iter.begin();

   bool bResult = true;
   if( (iter.getNumberOfItemsInList() == 0 || (iter.getNumberOfItemsInList() == 1 && iter.isDummy())) && strSplitPrefOpt == USE_DATE )
   {
      bResult = false;
   }

   return bResult;
}

//******************************************************************************
SEVERITY DilutionAllocList::refreshNSMEligibility(const BFFieldId& idField, const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE(CLASSNAME, I_("refreshNSMEligibility"));

	if(idField == ifds::IsNetworkSettleEligible)
	{
		DString dstrIsNetworkSettleEligible, oldIsNetworkSettleEligible;
		getField(ifds::IsNetworkSettleEligible,  oldIsNetworkSettleEligible, idDataGroup);
		refreshIsSettleNetworkEligible(dstrIsNetworkSettleEligible, idDataGroup);

		if(dstrIsNetworkSettleEligible != oldIsNetworkSettleEligible)
		{
			setFieldNoValidate(ifds::IsNetworkSettleEligible, dstrIsNetworkSettleEligible, idDataGroup, false);
		}
	}
	else
	{
		for(BFObjIter iter(*this, idDataGroup, 0,BFObjIter::ITERTYPE::NON_DELETED);
			!iter.end(); 
			++iter)
		{
			dynamic_cast<DilutionAlloc*>(iter.getObject())->refreshNSMEligibility(idField, idDataGroup);
		}
	}
	return GETHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DilutionAllocList::initCPFRefundRelatedFields(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("initCPFRefundRelatedFields"));

   DString dstrCPFRefundApplicable;
   getWorkSession().getOption (ifds::CPFRefundApplicable, dstrCPFRefundApplicable, BF::HOST, false);
   dstrCPFRefundApplicable.strip().upperCase();

   if(dstrCPFRefundApplicable == I_("N"))
   {
      setFieldRequired ( ifds::RefundAmount,	idDataGroup,	false);
      setFieldValid ( ifds::RefundAmount,	idDataGroup,	true);
      setFieldRequired ( ifds::DilutionAmount,	idDataGroup,	false);
      setFieldValid ( ifds::DilutionAmount,	idDataGroup,	true);
      setFieldRequired ( ifds::RefundFXRate,	idDataGroup,	false);
      setFieldValid ( ifds::RefundFXRate,	idDataGroup,	true);
      setFieldRequired ( ifds::RefundCurrency, idDataGroup,	false);
      setFieldValid ( ifds::RefundCurrency,	idDataGroup,	true);
      setFieldRequired ( ifds::RefundOption,	idDataGroup,	false);
      setFieldValid ( ifds::RefundOption,	idDataGroup,	true);
      setFieldRequired ( ifds::RefundPayType,	idDataGroup,	false);
      setFieldValid ( ifds::RefundPayType,	idDataGroup,	true);
      setFieldRequired ( ifds::DilutionAvail,idDataGroup,	false);
      setFieldValid ( ifds::DilutionAvail,	idDataGroup,	true);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
TransactionList* DilutionAllocList::getTransactionList(const BFDataGroupId& idDataGroup)
{
	if(dynamic_cast<Trade*>(getParent()) != NULL) return NULL;

	DString transNum;
	getField(ifds::TransNum, transNum, idDataGroup, false);
	TransactionList *pTransactionList;
	getWorkSession().getTransactionList(pTransactionList, transNum, idDataGroup);

	return pTransactionList;
}

//******************************************************************************
SEVERITY DilutionAllocList::refreshIsSettleNetworkEligible (DString& eligibility, 
	                                const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE(CLASSNAME, I_("IsSettleNetworkEligible"));

	eligibility = N;
	
	DString dstrSettleSource, dstrBrokerCode, dstrTransType, dstrOrderType, dstrAccountNum;
	Trade* pTrade = dynamic_cast<Trade*>(getParent());
	if(pTrade != NULL) 
	{
		if(pTrade->hasAllocations(idDataGroup)) return GETCURRENTHIGHESTSEVERITY();
	
		pTrade->getField(ifds::SettleSource, dstrSettleSource, idDataGroup, false);
		pTrade->getField(ifds::Broker, dstrBrokerCode, idDataGroup, false);
		pTrade->getField(ifds::AccountNum, dstrAccountNum, idDataGroup, false);
		pTrade->getField(ifds::TradesTransType, dstrTransType, idDataGroup, false);
		pTrade->getField(ifds::OrderType, dstrOrderType, idDataGroup, false);
	}
	else 
	{
		TransactionList *pTransactionList = getTransactionList(idDataGroup);
		if(pTransactionList == NULL) return GETCURRENTHIGHESTSEVERITY();
		while(pTransactionList->doMoreRecordsExist()) pTransactionList->getMore();

		TransactionDetails *pTransactionDetails = NULL;
		if(_dstrTransId.stripAll().empty())
		 {
			DString transId;
			
			for(BFObjIter iter(*pTransactionList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
				!iter.end();
				++iter)
			{
				DString transType;
				auto details = dynamic_cast<TransactionDetails*>(iter.getObject());
				if(details == NULL) continue;

				details->getField(ifds::TransType, transType, idDataGroup);
				if(transType == I_("ID")) continue;

				pTransactionDetails = details;
			
				pTransactionDetails->getField(ifds::TransId, _dstrTransId, idDataGroup);
				pTransactionDetails->getDetails(_dstrTransId);
			}
		}
		else 
		{
			for(BFObjIter iter(*pTransactionList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
				!iter.end();
				++iter)
			{
	            DString iterTransId;
		        iter.getObject()->getField(ifds::TransId, iterTransId, idDataGroup);

			    if(iterTransId == _dstrTransId) 
				{
					pTransactionDetails = dynamic_cast<TransactionDetails*>(iter.getObject());
					break;
				}
			}
			if(pTransactionDetails != NULL) pTransactionDetails->getDetails(_dstrTransId);
		}
		if(pTransactionDetails == NULL) return GETCURRENTHIGHESTSEVERITY();

		DString dstrReversal, dstrSettled;
		pTransactionDetails->getField(ifds::Reversal, dstrReversal, idDataGroup);

		if(dstrReversal == I_("Y")) 
		{
			TransactionDetails* pCancelledTransDetails = NULL;
			DString transType;
			pTransactionDetails->getField(ifds::TransType, transType, idDataGroup, false);
			for(BFObjIter iter(*pTransactionList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
				!iter.end();
				++iter)
			{
				DString iterCancelled, iterTransType, iterTransId;
				iter.getObject()->getField(ifds::Cancelled, iterCancelled, idDataGroup);
				iter.getObject()->getField(ifds::TransType, iterTransType, idDataGroup);
				iter.getObject()->getField(ifds::TransId, iterTransId, idDataGroup);

				if(iterCancelled == I_("Y") && transType == iterTransType && iterTransId != _dstrTransId) 
				{
					pCancelledTransDetails = dynamic_cast<TransactionDetails*>(iter.getObject());
					break;
				}
			}
			if(pCancelledTransDetails == NULL) return GETCURRENTHIGHESTSEVERITY();

			DString cancelledTransId/*, dstrSettled*/;
			pCancelledTransDetails->getField(ifds::TransId, cancelledTransId, idDataGroup);
			pCancelledTransDetails->getDetails(cancelledTransId);

			pTransactionDetails = pCancelledTransDetails;
		}
		DString dstrAllocation;
		pTransactionDetails->getField(ifds::Allocation, dstrAllocation, idDataGroup);
		if(dstrAllocation == I_("Y")) return GETCURRENTHIGHESTSEVERITY();

		pTransactionDetails->getField(ifds::TransType, dstrTransType, idDataGroup);
		pTransactionDetails->getField(ifds::SettleSource, dstrSettleSource, idDataGroup, false);
		pTransactionDetails->getField(ifds::BrokerCode, dstrBrokerCode, idDataGroup, false);
		pTransactionDetails->getField(ifds::AccountNum, dstrAccountNum, idDataGroup, false);
		pTransactionDetails->getField(ifds::OrderType, dstrOrderType, idDataGroup, false);
		pTransactionDetails->getField(ifds::Settled, dstrSettled, idDataGroup, false);

		DString dstrFund;
		pTransactionDetails->getField(ifds::rxFundCode, dstrFund, idDataGroup);
		if ( dstrFund.stripAll().empty() || 
         (dstrSettled.stripAll().upperCase() != YES && _dstrTransId.empty()))  //<-- Unsettle and new.
          return GETCURRENTHIGHESTSEVERITY();
	}
		
	if(!DSTCommonFunctions::codeInList(dstrTransType, SETTLE_NETWORK_ELIGIBLE))
	{
		return GETCURRENTHIGHESTSEVERITY();
	}

	if (pTrade != NULL && dstrOrderType != Y ) return GETCURRENTHIGHESTSEVERITY();

	if(dstrSettleSource == I_("D"))
	{
		Broker *pBroker = NULL;
		BrokerList *pBrokerList = NULL;
		getWorkSession().getBrokerList(pBrokerList, idDataGroup);

		if (pBrokerList == NULL ||
			pBrokerList->getBroker(dstrBrokerCode, pBroker) > WARNING || 
			pBroker == NULL)
		{
			return GETCURRENTHIGHESTSEVERITY();
		}

		DString dstrBrokCompliantNW, dstrBrokCssStatus;
		pBroker->getField(ifds::BrokCompliantNW, dstrBrokCompliantNW, idDataGroup, false);
		pBroker->getField(ifds::BrokCssStatus, dstrBrokCssStatus, idDataGroup, false);

		if(dstrBrokCompliantNW != I_("F") || dstrBrokCssStatus !=I_("S"))
		{
			return GETCURRENTHIGHESTSEVERITY();
		}
	}
	else if(dstrSettleSource == I_("I"))
	{	
		MFAccount *pMFAccount;
		if( getWorkSession().getMFAccount(idDataGroup, dstrAccountNum, pMFAccount) > WARNING ||
			pMFAccount == NULL)
		{
			return GETCURRENTHIGHESTSEVERITY();
		}

		DString dstrInterCode;
		pMFAccount->getField(ifds::InterCode, dstrInterCode, idDataGroup, false);
		if( dstrInterCode.stripAll().empty()) return GETCURRENTHIGHESTSEVERITY();

		Intermediary *pIntermediary;
		IntermediaryList *pIntermediaryList;
		if(	getWorkSession().getMgmtCo().getIntermediaryList(pIntermediaryList) > WARNING || 
			pIntermediaryList == NULL)
		{
			return GETCURRENTHIGHESTSEVERITY();
		}

		if( !pIntermediaryList->getIntermediary(idDataGroup, dstrInterCode, pIntermediary) ||
			pIntermediary == NULL)
		{
			return GETCURRENTHIGHESTSEVERITY();
		}

		DString dstrIntrCssStatus;
		pIntermediary->getField(ifds::IntrCssStatus, dstrIntrCssStatus, idDataGroup, false);

		if(dstrIntrCssStatus !=I_("S")) return GETCURRENTHIGHESTSEVERITY();
	}
	else
	{
			if(pTrade != NULL) return GETCURRENTHIGHESTSEVERITY();
	}

	eligibility = Y;

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DilutionAllocList::settleNetworkRelateChanges(const BFDataGroupId& idDataGroup)
{
  MAKEFRAMEAUTOPROMOTE(CLASSNAME, I_("settleNetworkRelateChanges"));
  /*
    When settle network != FSRV or dilutionNSM != yes, iFastLinkID is cleared
    When settle network = FSRV and NSMEligible = yes, DilutionNSM = 02 and disabled
    Otherwise, DilutionNSM is enabled.
  */
  DString dstrSettleNetwork;
  getField(ifds::SettleNetwork, dstrSettleNetwork, idDataGroup, false);

  DString eligible, dstrDilutionNSM, dstrShowExSysDilPymtNSM;
  getWorkSession().getOption(ifds::ShowExSysDilPymtNSM, dstrShowExSysDilPymtNSM, idDataGroup, false);
  for(BFObjIter iter(*this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
      !iter.end(); 
      ++iter)
  {
    DilutionAlloc *pDilutionAlloc = dynamic_cast<DilutionAlloc*>(iter.getObject());
    pDilutionAlloc->refreshNSMEligibility(ifds::SettleNetwork, idDataGroup);
    pDilutionAlloc->getField(ifds::IsDilutionNSMEligible, eligible, idDataGroup, false);
    pDilutionAlloc->getField(ifds::DilutionNSM, dstrDilutionNSM, idDataGroup, false);

    if(dstrSettleNetwork != FSRV)
    {
      pDilutionAlloc->setFieldReadOnly(ifds::DilutionNSM, idDataGroup, false);
      if(dstrDilutionNSM != I_("02"))
        setFieldNoValidate(ifds::DilutionLinkNum, NULL_STRING, idDataGroup, false, true, true);
    }
    else
    {
      setValidFlag(ifds::DilutionLinkNum, idDataGroup, false);
      
      if(eligible == I_("Y") && idDataGroup != BF::HOST)
        pDilutionAlloc->setField(ifds::DilutionNSM, I_("02"), idDataGroup, false, false, true);
      
    }
  }
  return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DilutionAllocList.cpp-arc  $
// 
//    Rev 1.19   May 11 2012 15:21:00   wp040027
// PETP0187485-CPF-Dilution
// 
//    Rev 1.18   Aug 03 2009 18:53:28   dchatcha
// PET 157825 - FN 13 - Dilution Allocation Enhancements.
// 
//    Rev 1.17   Nov 19 2007 11:14:32   jankovii
// IN #1074083 - Error message when cancelling trade using date range split.
// 
//    Rev 1.16   Nov 16 2007 13:08:02   jankovii
// IN #1074083 - Error message when cancelling trade using date range split.
// 
//    Rev 1.15   Jun 05 2006 11:38:24   popescu
// Incident# 593551 - validation should be triggered in no deletes are part of the list
// 
//    Rev 1.14   Dec 18 2005 15:11:46   porteanm
// Incident 421704 - gap - TranshistDilutionAlloc update support.
// 
//    Rev 1.13   Dec 16 2005 20:44:20   porteanm
// Incident 421704 - gap - TranshistDilutionAlloc update support.
// 
//    Rev 1.12   Dec 02 2005 09:11:10   popescu
// Incident# 468413 - do not set the backdated reason if empty, when adding new 100 percent dilution record.
// 
//    Rev 1.11   Sep 01 2005 14:01:36   popescu
// Incident# 388632 - trans cancel screen code overhaul
// 
//    Rev 1.10   Jul 20 2005 13:56:42   winnie
// Sync up for 325606 : Use SplitCode control for dilution instead of AccountableMandatory
// 
//    Rev 1.9   Jul 12 2005 16:08:02   AGUILAAM
// PET 1235: additional, dilution.
// 
//    Rev 1.8   Jul 07 2005 12:17:56   AGUILAAM
// PET1235 : dilution, part of Rebook/Cancellation
// 
//    Rev 1.7   Jun 15 2005 14:42:48   ZHANGCEL
// Incident #322193 - Add logic to set RvCode into BackDatedReason fields
// 
//    Rev 1.6   Mar 16 2005 15:33:32   Fengyong
// PET1190 FN05 - change view 337 to repeatable
// 
//    Rev 1.5   Mar 09 2005 11:29:26   Fengyong
// PET1190 FN04 - decimal places fix
// 
//    Rev 1.4   Mar 08 2005 15:52:56   Fengyong
// PET1190 FN04 - view need submit at least one dilution record when dilution feature is on.
// 
//    Rev 1.3   Mar 08 2005 13:35:46   Fengyong
// PET1190 FN04 - Uncommon enhance code after DD sync up
// 
//    Rev 1.2   Mar 07 2005 13:57:10   Fengyong
// PET1190FN04 - accountableCode validation
// 
//    Rev 1.1   Mar 04 2005 16:59:22   Fengyong
// PET1190 FN04 - TranCancel tempary check in for other coder
*/
