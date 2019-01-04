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
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : TradeSettleLocationsProcess.cpp
// ^AUTHOR : 
// ^DATE   : July, 2009
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : TradeSettleLocationsProcess
//    This class manages the Regulatory Document List information.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************
//ifastbp
#include "stdafx.h"
#include "TradeSettleLocationsProcessincludes.h"
#include "TradeSettleLocationsProcess.hpp"
#include <ifastcbo\worksessionentitylist.hpp>
#include <ifastcbo\errmsgruleslist.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\worksessiontradeslist.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\PendingTradeDetails.hpp>
#include <ifastcbo\PendingTradeList.hpp>
#include <ifastcbo\Trade.hpp>
#include <ifastcbo\TransactionDetails.hpp>
#include <ifastcbo\TransactionList.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_TRADE_SETTLEMENT_LOCATIONS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_TRADE_SETTLEMENT_LOCATIONS;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< TradeSettleLocationsProcess > processCreator(CMD_BPROC_TRADE_SETTLEMENT_LOCATIONS);

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME = I_( "TradeSettleLocationsProcess" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace
{
   const I_CHAR * const CALLER = I_("Caller");
   const I_CHAR * const ACCOUNT_NUM = I_("AccountNum");
   const I_CHAR * const TRADE_LIST_KEY = I_("ListKey");
   const I_CHAR * const TRANS_LIST_KEY = I_("TransListKey");
   const I_CHAR * const PENDPROCRECORD_TYPE   = I_( "PendProcRecordType" );
   const I_CHAR * const DECIMAL_DIGITS  	  = I_("DecimalDigits");
}

//******************************************************************************
//              Public Methods
//******************************************************************************
TradeSettleLocationsProcess::TradeSettleLocationsProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( NULL )
, m_Caller (NULL_STRING)
, m_TradeListKey (NULL_STRING)
, m_TransListKey (NULL_STRING)
, m_AccountNum (NULL_STRING)
, m_RecordType (NULL_STRING)
, m_DecimalDigits (NULL_STRING)
{
	TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

	addContainer ( IFASTBP_PROC::TRADE, false, BF::NullContainerId, false, I_("Trade"));
	addContainer ( IFASTBP_PROC::TRADE_MULTI_SETTLEMENT_LOC_LIST, true, BF::NullContainerId, true, I_("TradeSettleLocsList"));

	addFieldDetails( ifds::SettleLocCode,		IFASTBP_PROC::TRADE_MULTI_SETTLEMENT_LOC_LIST);
	addFieldDetails( ifds::TransClrSettlAmt,	IFASTBP_PROC::TRADE_MULTI_SETTLEMENT_LOC_LIST);
	addFieldDetails( ifds::ForAccount,			IFASTBP_PROC::TRADE_MULTI_SETTLEMENT_LOC_LIST);
	addFieldDetails( ifds::InFavourOf,			IFASTBP_PROC::TRADE_MULTI_SETTLEMENT_LOC_LIST);
	addFieldDetails( ifds::DeliveryTo,			IFASTBP_PROC::TRADE_MULTI_SETTLEMENT_LOC_LIST);
	addFieldDetails( ifds::TransClrSettlUUID,	IFASTBP_PROC::TRADE_MULTI_SETTLEMENT_LOC_LIST);
}

//******************************************************************************
TradeSettleLocationsProcess::~TradeSettleLocationsProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

//******************************************************************************
SEVERITY TradeSettleLocationsProcess::doInit()
{
	MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );

	getParameter (CALLER, m_Caller);
    getParameter (ACCOUNT_NUM, m_AccountNum);
    getParameter (TRADE_LIST_KEY, m_TradeListKey);
    getParameter (TRANS_LIST_KEY, m_TransListKey);
    getParameter (PENDPROCRECORD_TYPE, m_RecordType);
    getParameter (DECIMAL_DIGITS, m_DecimalDigits);

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool TradeSettleLocationsProcess::doModelessChildComplete( const Command &cmd )
{
	// End when GUI ends
	return( cmd.getKey() == CMD_GUI_TRADE_SETTLEMENT_LOCATIONS);
}

//******************************************************************************


//******************************************************************************
bool TradeSettleLocationsProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  
	// This is implemented to pass set focus on to child dialog.
	MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );
	bool bRtn = false;

	try
	{
		getParameter (CALLER, m_Caller);
		getParameter (ACCOUNT_NUM, m_AccountNum);
		getParameter (TRADE_LIST_KEY, m_TradeListKey);
		getParameter (TRANS_LIST_KEY, m_TransListKey);
		getParameter (PENDPROCRECORD_TYPE, m_RecordType);
        getParameter (DECIMAL_DIGITS, m_DecimalDigits);

		setContainer (IFASTBP_PROC::TRADE_MULTI_SETTLEMENT_LOC_LIST, NULL);

		if (isValidModelessInterface (_rpChildGI))
		{  // Only if child still exists
			bRtn = _rpChildGI->refresh (this, NULL);
		}
		if( isValidModelessInterface( _rpChildGI ) )
		{  // Only if child still exists
			bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
		}
	}
	catch( ConditionException &ce )
	{
		SETCONDITIONFROMEXCEPTION( ce );
	}
	catch( ... )
	{
		assert( 0 );
		THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS,
			CND::BP_ERR_UNKNOWN_EXCEPTION );
	}

	return(bRtn);
}

//******************************************************************************
E_COMMANDRETURN TradeSettleLocationsProcess::doProcess()
{
	MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
	E_COMMANDRETURN rtn = CMD_FAILURE;

	setParameter (CALLER, m_Caller);
    setParameter (DECIMAL_DIGITS, m_DecimalDigits);

	try
	{
		rtn = invokeCommand( this, CMD_GUI_TRADE_SETTLEMENT_LOCATIONS, getProcessType(), isModal(),
			&_rpChildGI );
	}
	catch( ConditionException &ce )
	{
		assert( 0 );
		SETCONDITIONFROMEXCEPTION( ce );
	}
	catch( ... )
	{
		assert( 0 );
		THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS,
			CND::BP_ERR_UNKNOWN_EXCEPTION );
	}

	return(rtn);
}

//******************************************************************************
void *TradeSettleLocationsProcess::getPtrForContainer( const BFContainerId& idContainer,
                                                  const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "getPtrForContainer" ) );

	void *ptr = NULL;
	DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

	try
	{
		if (IFASTBP_PROC::TRADE == idContainer)
		{
			WorksessionTradesList *pTradesList = NULL;

			if( dstcWorkSession->getTradesList(pTradesList, idDataGroup) <= WARNING
				&& pTradesList)
			{
				BFObjIter iter( *pTradesList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
			
				iter.positionByKey (m_TradeListKey);

				if( !iter.end())            
				{
					ptr = dynamic_cast <Trade*>(iter.getObject());
				}										
			}
		}
		else if (IFASTBP_PROC::TRADE_MULTI_SETTLEMENT_LOC_LIST == idContainer)
		{
			if (m_Caller == I_("TradeEntry"))
			{
				Trade *pTrade = dynamic_cast <Trade*> (getCBOItem ( IFASTBP_PROC::TRADE, idDataGroup));
				
				if (pTrade)
				{
					TradeSettlementLocationsList *pTradeSettlementLocationsList = NULL;

					if ( pTrade->getSettlementLocsList  (pTradeSettlementLocationsList, idDataGroup) <= WARNING &&
						pTradeSettlementLocationsList)
					{
						ptr = pTradeSettlementLocationsList;
					}
				}
			}
			else if (m_Caller == I_("TransactionHistoryDlg") && m_RecordType == I_("Pend"))
			{
				MFAccount *pMFAccount = NULL;
				
				if (dstcWorkSession->getMFAccount(idDataGroup, m_AccountNum, pMFAccount ) <= WARNING &&
				    NULL != pMFAccount)
				{
					PendingTradeList *pPendingTradeList = NULL;
					
					if (pMFAccount->getPendingTradesList( pPendingTradeList, idDataGroup ) <= WARNING &&
                        NULL != pPendingTradeList )
					{							
						BFObjIter iterPendingTradesList (*pPendingTradeList,idDataGroup, 
														 false, BFObjIter::ITERTYPE::NON_DELETED );

						iterPendingTradesList.begin();
						
						if (iterPendingTradesList.positionByKey (m_TransListKey))
						{																												
							PendingTradeDetails *pPendingTradeDetails =  dynamic_cast <PendingTradeDetails*>(iterPendingTradesList.getObject());								
   							pPendingTradeList->getItem(m_TransListKey, idDataGroup);								
							
							if (pPendingTradeDetails != NULL )
							{
								TradeSettlementLocationsList *pTradeSettlementLocationsList = NULL;

								if (pPendingTradeDetails->getSettlementLocsList  (pTradeSettlementLocationsList, idDataGroup) <= WARNING &&
									pTradeSettlementLocationsList)
								{
									ptr = pTradeSettlementLocationsList;
								}
							}
						}
					}
				}
			}
			else if (m_Caller == I_("TransactionHistoryDlg") && m_RecordType == I_("Proc"))
			{
				MFAccount *pMFAccount = NULL;

				if (dstcWorkSession->getMFAccount (idDataGroup, m_AccountNum, pMFAccount ) <= WARNING &&
				    NULL != pMFAccount )
				{
					TransactionList *pTransactionHistoryList = NULL;						
					pMFAccount->getLastActiveTransactionHistoryList (pTransactionHistoryList, idDataGroup );
					
					if (pTransactionHistoryList != NULL)
					{
						TransactionDetails *pTransactionHistoryDetails = NULL; 
						pTransactionHistoryDetails = pTransactionHistoryList->getItem(m_TransListKey, idDataGroup );
					
						if (pTransactionHistoryDetails != NULL)
						{
							TradeSettlementLocationsList *pTradeSettlementLocationsList = NULL;

							if (pTransactionHistoryDetails->getSettlementLocsList  (pTradeSettlementLocationsList, idDataGroup) <= WARNING &&
								pTradeSettlementLocationsList)
							{
								ptr = pTradeSettlementLocationsList;
							}	
						}
					}
				}		
			}
		}
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
bool TradeSettleLocationsProcess::doOk (GenericInterface *rpGICaller)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, I_( "doOk" ) );

	return GETCURRENTHIGHESTSEVERITY () <= WARNING;
}

/* $Log::
 */