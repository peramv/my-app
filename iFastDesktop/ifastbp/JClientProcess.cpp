//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : ClientProcess.cpp
// ^AUTHOR : 
// ^DATE   : 02/21/2003
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : ClientProcess
//    
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"

#include <ifastcbo\pendingtradelist.hpp>
#include <ifastcbo\tradesearchcriteria.hpp>
#include "JClientProcess.hpp"
#include "JClientProcessincludes.h"
#include <ifastcbo\transactionlist.hpp>
#include <ifastcbo\deductionlist.hpp>
#include <ifastcbo\TransactionDetails.hpp>

//#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\dstcworksession.hpp>



extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_CLIENT;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< ClientProcess > processCreator( CMD_BPROC_CLIENT );

namespace CND
{   // Conditions used
    extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
	extern const long BP_ERR_DATA_NOT_FOUND;
	extern const long BP_ERR_MORE_THAN_ONE_RECORD_FOUND;
	//extern CLASS_IMPORT const long BP_ERR_RECORD_VALUE_NOT_MATCH;
}

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME             = I_( "ClientProcess" );
   const I_CHAR * const PERFORMSEARCH  = I_( "performSearch" );   

   const I_CHAR * const YES            = I_( "Y" );
   const I_CHAR * const NO             = I_( "N" );

   const I_CHAR * const SENDREF           = I_( "SendRefNum" );

   const I_CHAR * const ALTACCOUNT		  = I_( "AltAccountNum" );
   const I_CHAR * const FUNDIDTYPE        = I_( "FundIdType" );
   const I_CHAR * const FUNDIDVALUE       = I_( "FundIdValue" );   
   const I_CHAR * const TRANSTYPE		  = I_( "TransType" );
   const I_CHAR * const TRADEDATE		  = I_( "TradeDate" );   
   const I_CHAR * const UNITS			  = I_( "Units" );

   const I_CHAR * const SETTLEDATE		  = I_( "SettleDate" );
   const I_CHAR * const AMOUNT			  = I_( "Amount" );
   const I_CHAR * const OFFERPRICE		  = I_( "OfferPrice" );
   const I_CHAR * const DISCOUNTRATE	  = I_( "DiscountRate" );
   const I_CHAR * const DISCOUNTAMT		  = I_( "DiscountAmt" );

   const I_CHAR * const DISCOUNT		  = I_( "88" );
   const I_CHAR * const REDEMPTION		  = I_( "PW" );

   const I_CHAR * const ACCOUNT			  = I_("AccountNum");
   const I_CHAR * const ALTACCOUNTSEARCH  = I_("AltAccount");
}

namespace ifds
{
   extern CLASS_IMPORT const BFDecimalFieldId FeePercent;
   extern CLASS_IMPORT const BFTextFieldId AltAccount;
   extern CLASS_IMPORT const BFTextFieldId SendRefNum;
   extern CLASS_IMPORT const BFTextFieldId FundIDType;
   extern CLASS_IMPORT const BFTextFieldId FundIDValue;
   extern CLASS_IMPORT const BFDecimalFieldId DeductAmt;
   extern CLASS_IMPORT const BFTextFieldId DeductCategory;
   extern CLASS_IMPORT const BFDecimalFieldId DiscountAmount;
   extern CLASS_IMPORT const BFDecimalFieldId AcqDiscountRate;
   extern CLASS_IMPORT const BFTextFieldId FrClearingMethod;
   extern CLASS_IMPORT const BFTextFieldId ToClearingMethod;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319ClientProcess::ClientProcess() : 
ClientProcess::ClientProcess (GenericInterfaceContainer* pGIC, 
   GenericInterface* pGIParent, const Command& rCommand)
: AbstractProcess( pGIC, pGIParent, rCommand)
, _rpChildGI( NULL ),
_pTransactionList(NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, "" );

   //add containers
   addContainer( IFASTBP_PROC::CRITERIA, 
      false, BF::NullContainerId, true, I_("Criteria") );
   
   addContainer( IFASTBP_PROC::TRANSACTION_LIST, 
      true,  IFASTBP_PROC::CRITERIA, true, I_("TransactionList") );

//   addContainer( IFASTBP_PROC::DEDUCTION_LIST, true, IFASTBP_PROC::TRANSACTION_LIST, false, I_("DeductionList") );

   //CRITERIA fields
   addFieldDetails( ifds::SearchType,          IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::NetworkID,           IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::ExtTransNum,         IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::SendRefNum,          IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::FromDate,            IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::ToDate,              IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::AccountNum,          IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::ExternalIdType,      IFASTBP_PROC::CRITERIA );
   addFieldDetails( ifds::ExternalId,          IFASTBP_PROC::CRITERIA );

   //TRANSACTION_LIST fields
   addFieldDetails( ifds::AccountNum,          IFASTBP_PROC::TRANSACTION_LIST );
   addFieldDetails( ifds::rxFundCode,          IFASTBP_PROC::TRANSACTION_LIST );
   addFieldDetails( ifds::rxClassCode,         IFASTBP_PROC::TRANSACTION_LIST );
   addFieldDetails( ifds::TradeDate,           IFASTBP_PROC::TRANSACTION_LIST );
   addFieldDetails( ifds::TransType,           IFASTBP_PROC::TRANSACTION_LIST );
   addFieldDetails( ifds::TransNum,            IFASTBP_PROC::TRANSACTION_LIST );
   addFieldDetails( ifds::Units,               IFASTBP_PROC::TRANSACTION_LIST );
   addFieldDetails( ifds::GrossAmt,            IFASTBP_PROC::TRANSACTION_LIST );
   addFieldDetails( ifds::NetAmt,            IFASTBP_PROC::TRANSACTION_LIST );
   addFieldDetails( ifds::TransId,             IFASTBP_PROC::TRANSACTION_LIST );
   addFieldDetails( ifds::NetworkID,           IFASTBP_PROC::TRANSACTION_LIST );
   addFieldDetails( ifds::ExtTransNum,         IFASTBP_PROC::TRANSACTION_LIST );
   addFieldDetails( ifds::SendRefNum,          IFASTBP_PROC::TRANSACTION_LIST );
   addFieldDetails( ifds::SettleDate,          IFASTBP_PROC::TRANSACTION_LIST );
   addFieldDetails( ifds::Amount,			   IFASTBP_PROC::TRANSACTION_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::OfferPrice,			   IFASTBP_PROC::TRANSACTION_LIST );   
   addFieldDetails( ifds::FrClearingMethod,          IFASTBP_PROC::TRANSACTION_LIST );
   addFieldDetails( ifds::ToClearingMethod,          IFASTBP_PROC::TRANSACTION_LIST );
   
   addFieldDetails( ifds::AcqDiscountRate,         IFASTBP_PROC::TRANSACTION_LIST );
   addFieldDetails( ifds::DiscountAmount,              IFASTBP_PROC::TRANSACTION_LIST );

   addFieldDetails( ifds::ValidTradeCriteria,   BF::NullContainerId, SUBCLASS_PROCESS);
}

//******************************************************************************

ClientProcess::~ClientProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY ClientProcess::doInit()
{
    MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );

	DString _sendRefNum, _searchType, _altAccountNum, _FundIDType, _FundIDValue;
	DString _TransType, _FromDate, _Units;
	const BFDataGroupId &idDataGroup = getDataGroupId ();

	getParameter ( SENDREF, _sendRefNum);
    _sendRefNum.strip();

	DString _AccountNum;
	getParameter ( ACCOUNT, _AccountNum);
    _AccountNum.strip();
    
	getParameter ( ALTACCOUNT, _altAccountNum);
    _altAccountNum.strip();
	getParameter ( FUNDIDTYPE, _FundIDType);
    _FundIDType.strip();
	getParameter ( FUNDIDVALUE, _FundIDValue);
    _FundIDValue.strip();
	getParameter ( TRANSTYPE, _TransType);
    _TransType.strip();
	getParameter ( TRADEDATE, _FromDate);
    _FromDate.strip();
	getParameter ( UNITS, _Units);
    _Units.strip();

	if ( _sendRefNum != NULL_STRING ) 		_searchType = SENDREF;	
	else _searchType = ALTACCOUNTSEARCH;

	TradeSearchCriteria* pTradeSearchCriteria = NULL;
	DSTCWorkSession* dstcWorkSession = 
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

	if (dstcWorkSession->getTradeSearchCriteria (pTradeSearchCriteria) <= WARNING)
	{		
		pTradeSearchCriteria->setField(ifds::SearchType, _searchType, idDataGroup );

		pTradeSearchCriteria->setField(ifds::SendRefNum, _sendRefNum, idDataGroup );

		pTradeSearchCriteria->setField(ifds::AccountNum, _AccountNum, idDataGroup );

		pTradeSearchCriteria->setField(ifds::AltAccount, _altAccountNum, idDataGroup );		
		pTradeSearchCriteria->setField(ifds::FundIDType, _FundIDType, idDataGroup );		
		pTradeSearchCriteria->setField(ifds::FundIDValue, _FundIDValue, idDataGroup );
		pTradeSearchCriteria->setField(ifds::TransType, _TransType, idDataGroup );
		pTradeSearchCriteria->setField(ifds::FromDate, _FromDate, idDataGroup );
		pTradeSearchCriteria->setField(ifds::Units, _Units, idDataGroup );

		setContainer (IFASTBP_PROC::CRITERIA, pTradeSearchCriteria);
	}

	ValidateFieldsValues();
    return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

E_COMMANDRETURN ClientProcess::doProcess()
{  
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;
   try
   {
       rtn = CMD_MODELESS_INPROCESS;
   }
   catch( ConditionException &ce )
   {
      //assert( 0 );
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      //assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(rtn);
}

//******************************************************************************
void *ClientProcess::getPtrForContainer (const BFContainerId& idContainer, 
                                              const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, I_("getPtrForContainer") );

   void *ptr = NULL;
   DSTCWorkSession* dstcWorkSession = 
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   try
   {
      if( IFASTBP_PROC::TRANSACTION_LIST == idContainer )
      {
         TradeSearchCriteria* pTradeSearchCriteria = dynamic_cast<TradeSearchCriteria*>(
            getCBOItem (IFASTBP_PROC::CRITERIA, idDataGroup));

         _pTransactionList = NULL;
         if (pTradeSearchCriteria->getTransactionList (_pTransactionList, idDataGroup) <= WARNING)
         {
			BFObjIter iter ( *_pTransactionList, 
								getDataGroupId(), 
								false, 
								BFObjIter::ITERTYPE::NON_DELETED);

			while (!iter.end())
			{
				DString strKey = iter.getStringKey ();
				TransactionDetails *tmp =_pTransactionList->getItem( strKey, BF::HOST );
				++iter;
			}
            ptr = _pTransactionList;
         }
      }
/*	  if( IFASTBP_PROC::DEDUCTION_LIST == idContainer )
	  {
			TransactionDetails *tmp = 
				dynamic_cast<TransactionDetails*> (getCBOItem(IFASTBP_PROC::TRANSACTION_LIST, idDataGroup));
			if( tmp )
			{
				ptr = tmp->getDeductionList();
			}                               
	  }*/
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(ptr);
}
//******************************************************************************

SEVERITY ClientProcess::ok2( GenericInterface *rpGICaller )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("ok2") );
      
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void ClientProcess::doGetField(
                                   const GenericInterface *rpGICaller,
                                   const BFContainerId& idContainer,
                                   const BFFieldId& fieldID,
                                   const BFDataGroupId& idDataGroup,
                                   DString &strValueOut,
                                   bool bFormatted
                                   ) const
{
   if( fieldID == ifds::ValidTradeCriteria )
   {
      strValueOut = NO;
      TradeSearchCriteria* pSearchCrt = NULL;
      DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      if( dstcWorkSession->getTradeSearchCriteria(pSearchCrt)<=WARNING )
         if( pSearchCrt->isValidForInquiry(idDataGroup) )
            strValueOut = YES;
   }
   else
      assert(0);

}

//******************************************************************************
SEVERITY ClientProcess::doSetField(
                                       const GenericInterface *rpGICaller,
                                       const BFContainerId& idContainer,
                                       const BFFieldId& fieldID,
                                       const BFDataGroupId& idDataGroup,
                                       const DString& strValue,
                                       bool bFormatted
                                       )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doSetField") );

   if( fieldID == ifds::Amount )
   {
      TradeSearchCriteria* pSearchCrt = NULL;
      DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      if( dstcWorkSession->getTradeSearchCriteria(pSearchCrt)<=WARNING )
	  {
		_pTransactionList = NULL;
		if (pSearchCrt->getTransactionList (_pTransactionList, idDataGroup) <= WARNING)
		{
			DString _transType;
			BFObjIter bfIter( *_pTransactionList, getDataGroupId(), false, BFObjIter::ITERTYPE::NON_DELETED );
			( ( BFCBO* ) (bfIter.getObject()))->getField(ifds::TransType, _transType, idDataGroup);
			if( _transType == REDEMPTION )
			{
				( ( BFCBO* ) (bfIter.getObject()))->setField(ifds::NetAmt, strValue, idDataGroup);				
			}
			else 
			{
				( ( BFCBO* ) (bfIter.getObject()))->setField(ifds::GrossAmt, strValue, idDataGroup);
			}
		}
	  }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY ClientProcess::performSearch (
   GenericInterface *rpGICaller, 
   const BFContainerId& idSearch, 
   E_SEARCHACTION eSearchAction )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, PERFORMSEARCH );

   const BFDataGroupId& idDataGroup = getDataGroupId ();
   try
   {
      switch (eSearchAction)
      {
         case SEARCH_START:
            {
				if (idSearch == IFASTBP_PROC::TRANSACTION_LIST)
                  _pTransactionList = NULL;
               setContainer (idSearch, NULL);
            }
            break;
         case SEARCH_NEXT_BLOCK:
            {
			   if (idSearch == IFASTBP_PROC::TRANSACTION_LIST)
               {
                  if (_pTransactionList)
                     _pTransactionList->getMore();
               }
            }
            break;
         default:
            break;
      }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, PERFORMSEARCH, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool ClientProcess::doMoreRecordsExist( GenericInterface *rpGICaller,
                                             const BFContainerId& idSearch )
{
   if (!rpGICaller)
      return(false);

   if (IFASTBP_PROC::TRANSACTION_LIST == idSearch)
   {
      return _pTransactionList == NULL ? false : _pTransactionList->doMoreRecordsExist();
   }
   return false;
}

//******************************************************************************
SEVERITY ClientProcess::ValidateFieldsValues( )
{
	MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, SETCURRENTLISTITEM ); 
	const BFDataGroupId &idDataGroup = getDataGroupId ();

	TradeSearchCriteria* pTradeSearchCriteria = dynamic_cast<TradeSearchCriteria*>(
			getCBOItem (IFASTBP_PROC::CRITERIA, idDataGroup));

    _pTransactionList = NULL;
    if (pTradeSearchCriteria->getTransactionList (_pTransactionList, idDataGroup) <= WARNING)
	{
	   BFObjIter bfIter( *_pTransactionList, getDataGroupId(), false, BFObjIter::ITERTYPE::NON_DELETED );
	   int numOfItem = bfIter.getNumberOfItemsInList();
       if( numOfItem == 0 )
       {
           THROWFROMFILE2( CND::IFASTBP_CONDITION, CLASSNAME, DOINIT,CND::BP_ERR_DATA_NOT_FOUND );
       }
	   if( numOfItem > 1 )
	   {
		   THROWFROMFILE2( CND::IFASTBP_CONDITION, CLASSNAME, DOINIT,CND::BP_ERR_MORE_THAN_ONE_RECORD_FOUND );
	   }
/*
	   DString _transType, _tradeDate, _settleDate, _Units, _settleAmt, _offerPrice, _discountRate;
	   bfIter.begin();

	   ( ( BFCBO* ) (bfIter.getObject()))->getField(ifds::TransType, _transType, idDataGroup);
	   ( ( BFCBO* ) (bfIter.getObject()))->getField(ifds::TradeDate, _tradeDate, idDataGroup);
	   ( ( BFCBO* ) (bfIter.getObject()))->getField(ifds::SettleDate, _settleDate, idDataGroup);
	   ( ( BFCBO* ) (bfIter.getObject()))->getField(ifds::Units, _Units, idDataGroup);
	   ( ( BFCBO* ) (bfIter.getObject()))->getField(ifds::GrossAmt, _settleAmt, idDataGroup);
	   ( ( BFCBO* ) (bfIter.getObject()))->getField(ifds::OfferPrice, _offerPrice, idDataGroup);
	   ( ( BFCBO* ) (bfIter.getObject()))->getField(ifds::AcqDiscountRate, _discountRate, idDataGroup);	   
	   
	   if( _transType == REDEMPTION )
	   {
		   ( ( BFCBO* ) (bfIter.getObject()))->getField(ifds::NetAmt, _settleAmt, idDataGroup);
	   }

	   DString _ptransType, _ptradeDate, _psettleDate, _pUnits, _psettleAmt, _pofferPrice, _pdiscountRate;

	   getParameter ( TRANSTYPE, _ptransType);
       _ptransType.strip();
	   getParameter ( TRADEDATE, _ptradeDate);
       _ptradeDate.strip();
	   getParameter ( SETTLEDATE, _psettleDate);
       _psettleDate.strip();
	   getParameter ( UNITS, _pUnits);
       _pUnits.strip();
	   getParameter ( AMOUNT, _psettleAmt);
       _psettleAmt.strip();
	   getParameter ( OFFERPRICE, _pofferPrice);
       _pofferPrice.strip();
	   getParameter ( DISCOUNTRATE, _pdiscountRate);
       _pdiscountRate.strip();


	   //all decimal fields need use common function convert to same decimal places.
	   if( _transType != _ptransType || _tradeDate != _ptradeDate || _settleDate != _psettleDate ||
		   CompareDouble(ifds::Units, _Units, _pUnits ) ||
		   CompareDouble(ifds::GrossAmt, _settleAmt, _psettleAmt ) ||
		   CompareDouble(ifds::OfferPrice, _offerPrice, _pofferPrice ) ||
		   CompareDouble(ifds::DiscountRate, _discountRate, _pdiscountRate ) )
	   {
		   THROWFROMFILE2( CND::IFASTBP_CONDITION, CLASSNAME, DOINIT,CND::BP_ERR_RECORD_VALUE_NOT_MATCH );
	   }
*/
	}

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool ClientProcess::CompareDouble(const BFFieldId& fieldID, const DString string1, const DString string2 )
{
	double _dDouble1, _dDouble2;
	//DString _str1, _str2;

	_dDouble1 = DSTCommonFunctions::convertToDouble (string1);
	//_str1 = DSTCommonFunctions::doubleToDString (fieldID, _dDouble1);
	_dDouble2 = DSTCommonFunctions::convertToDouble (string2);
	//_str2 = DSTCommonFunctions::doubleToDString (fieldID, _dDouble2);

	//return (_str1 == _str2) ? true : false;
	return (_dDouble1 == _dDouble2) ? true : false;
}