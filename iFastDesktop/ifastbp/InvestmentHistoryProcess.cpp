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
// ^FILE   : InvestmentHistoryProcess.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : InvestmentHistoryProcess
//    
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************
//ifastbp
#include "stdafx.h"
#include "investmenthistoryprocessincludes.h"
#include "investmenthistoryprocess.hpp"
#include <ifastdataimpl\dse_dstcglob_vw.hpp>
#include <ifastcbo\InvestmentHistory.hpp>
#include <ifastcbo\InvestmentHistoryList.hpp>
#include <ifastcbo\InvestmentHistoryDetails.hpp>
#include <ifastcbo\InvestmentHistoryDetailsList.hpp>
#include <ifastcbo\InvestmentHistoryInterest.hpp>
#include <ifastcbo\InvestmentHistoryInterestList.hpp>
#include <ifastcbo\worksessionentitylist.hpp>
#include <ifastcbo\errmsgruleslist.hpp>
#include <ifastcbo\mgmtco.hpp>
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_INVESTMENT_HISTORY_LIST;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_INVESTMENT_HISTORY_LIST;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< InvestmentHistoryProcess > processCreator( CMD_BPROC_INVESTMENT_HISTORY_LIST);

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME		= I_( "InvestmentHistoryProcess" );
   const I_CHAR * const PERFORMSEARCH	= I_( "performSearch" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}


namespace IFASTERR
{
   //extern CLASS_IMPORT I_CHAR * const INVESTMENT_LIST_DATA_REQUIRED;
}

namespace ifds
{
	extern CLASS_IMPORT const BFTextFieldId InvestmentHistoryDetailsList;
	extern CLASS_IMPORT const BFTextFieldId InvestmentHistoryDetailsTranList;
	extern CLASS_IMPORT const BFTextFieldId InvestmentHistoryFund;
	extern CLASS_IMPORT const BFTextFieldId InvestmentHistoryClass;
	extern CLASS_IMPORT const BFTextFieldId InvestmentHistoryNumber;
	extern CLASS_IMPORT const BFTextFieldId InvestmentHistorySearch;
	extern CLASS_IMPORT const BFTextFieldId InvestmentHistoryStatus;
	extern CLASS_IMPORT const BFTextFieldId FromFundNumber;
	extern CLASS_IMPORT const BFDecimalFieldId InvHisCalculatedMVA;
	extern CLASS_IMPORT const BFTextFieldId InvHisMVAReason;
}

//******************************************************************************
//              Public Methods
//******************************************************************************
InvestmentHistoryProcess::InvestmentHistoryProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( NULL )
, m_strAcctNum(NULL_STRING)
, m_pHistoryList (NULL)
, m_pSearchHistoryList (NULL)
, m_pDetailsList (NULL)
, m_pInterestList (NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );   

	addContainer (INVESTMENT_HISTORY_SEARCH, false, BF::NullContainerId, true);
	addContainer (IFASTBP_PROC::INVESTMENT_HISTORY_LIST, true, BF::NullContainerId, false);
	addContainer (IFASTBP_PROC::INVESTMENT_HISTORY_TRAN_LIST, true, IFASTBP_PROC::INVESTMENT_HISTORY_LIST, false);
	addContainer (IFASTBP_PROC::INVESTMENT_HISTORY_INT_LIST, true, IFASTBP_PROC::INVESTMENT_HISTORY_LIST, false);


	//Input params for the query
	addFieldDetails (ifds::FromFundNumber						, INVESTMENT_HISTORY_SEARCH); //Char
	addFieldDetails (ifds::InvestmentHistoryFund				, INVESTMENT_HISTORY_SEARCH); //Char
	addFieldDetails (ifds::InvestmentHistoryClass				, INVESTMENT_HISTORY_SEARCH); //Char
	addFieldDetails (ifds::InvestmentHistoryNumber				, INVESTMENT_HISTORY_SEARCH); //Char
	addFieldDetails (ifds::InvestmentHistorySearch				, INVESTMENT_HISTORY_SEARCH); //Char
	addFieldDetails (ifds::InvestmentHistoryStatus				, INVESTMENT_HISTORY_SEARCH); //Char

	//Fields related to Investment History List Grid I
    addFieldDetails( ifds::IntInvestUUID                        , IFASTBP_PROC::INVESTMENT_HISTORY_LIST);
	addFieldDetails (ifds::InvHisNumber							, IFASTBP_PROC::INVESTMENT_HISTORY_LIST); //Char
	addFieldDetails (ifds::Fund									, IFASTBP_PROC::INVESTMENT_HISTORY_LIST); //Char
	addFieldDetails (ifds::Class								, IFASTBP_PROC::INVESTMENT_HISTORY_LIST); //Char
	addFieldDetails (ifds::TransNum								, IFASTBP_PROC::INVESTMENT_HISTORY_LIST); //Char
	addFieldDetails (ifds::TransId								, IFASTBP_PROC::INVESTMENT_HISTORY_LIST); //Char
	addFieldDetails (ifds::InvHisStatus							, IFASTBP_PROC::INVESTMENT_HISTORY_LIST); //Char
	addFieldDetails (ifds::InvHisIntCalcMthd					, IFASTBP_PROC::INVESTMENT_HISTORY_LIST); //Char
	addFieldDetails (ifds::InvHisIntRateType					, IFASTBP_PROC::INVESTMENT_HISTORY_LIST); //Char
	addFieldDetails (ifds::InvHisTerm							, IFASTBP_PROC::INVESTMENT_HISTORY_LIST); //Int
	addFieldDetails (ifds::InvHisIntRate						, IFASTBP_PROC::INVESTMENT_HISTORY_LIST); //Decimal
	addFieldDetails (ifds::InvHisDepDate						, IFASTBP_PROC::INVESTMENT_HISTORY_LIST); //Date
	addFieldDetails (ifds::InvHisMatDate						, IFASTBP_PROC::INVESTMENT_HISTORY_LIST); //Date
	addFieldDetails (ifds::InvHisPrincipal						, IFASTBP_PROC::INVESTMENT_HISTORY_LIST); //Decimal
	addFieldDetails (ifds::InvHisIntFreq						, IFASTBP_PROC::INVESTMENT_HISTORY_LIST); //Char
	addFieldDetails (ifds::InvHisCurMktVal						, IFASTBP_PROC::INVESTMENT_HISTORY_LIST); //Decimal
	addFieldDetails (ifds::InvHisLastIntCrdDate					, IFASTBP_PROC::INVESTMENT_HISTORY_LIST); //Date
	addFieldDetails (ifds::InvHisAcurdToDate					, IFASTBP_PROC::INVESTMENT_HISTORY_LIST); //Date
	addFieldDetails (ifds::InvHisLotId							, IFASTBP_PROC::INVESTMENT_HISTORY_LIST); //Decimal
	addFieldDetails (ifds::InvHisInvestId						, IFASTBP_PROC::INVESTMENT_HISTORY_LIST); //Decimal
	addFieldDetails (ifds::IntRateType							, IFASTBP_PROC::INVESTMENT_HISTORY_LIST); //Char
	addFieldDetails (ifds::AddlAmt   							, IFASTBP_PROC::INVESTMENT_HISTORY_LIST); //Decimal
	
    //Fields related to Investment History List Grid II
	addFieldDetails (ifds::InvHisTransType						, IFASTBP_PROC::INVESTMENT_HISTORY_TRAN_LIST); //Char
	addFieldDetails (ifds::InvHisTradeDate						, IFASTBP_PROC::INVESTMENT_HISTORY_TRAN_LIST); //Date
	addFieldDetails (ifds::InvHisPrincipalGrossMoneyOut			, IFASTBP_PROC::INVESTMENT_HISTORY_TRAN_LIST); //Decimal
	addFieldDetails (ifds::InvHisMVA							, IFASTBP_PROC::INVESTMENT_HISTORY_TRAN_LIST); //Decimal
	addFieldDetails (ifds::InvHisCalculatedMVA						, IFASTBP_PROC::INVESTMENT_HISTORY_TRAN_LIST); //Decimal
	addFieldDetails (ifds::InvHisMVAReason							, IFASTBP_PROC::INVESTMENT_HISTORY_TRAN_LIST); //Decimal
	addFieldDetails (ifds::InvHisAdminFee						, IFASTBP_PROC::INVESTMENT_HISTORY_TRAN_LIST); //Char
	addFieldDetails (ifds::InvHisNetOfFees						, IFASTBP_PROC::INVESTMENT_HISTORY_TRAN_LIST); //Decimal

	//Fields related to Investment History List Grid III
	addFieldDetails (ifds::InvHisIntDate						, IFASTBP_PROC::INVESTMENT_HISTORY_INT_LIST); //Date
	addFieldDetails (ifds::InvHisIntAmt							, IFASTBP_PROC::INVESTMENT_HISTORY_INT_LIST); //Decimal
	addFieldDetails (ifds::InvestStatus1						, IFASTBP_PROC::INVESTMENT_HISTORY_INT_LIST); //Char
}

//******************************************************************************
InvestmentHistoryProcess::~InvestmentHistoryProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   if (m_pSearchHistoryList)
   {
	   delete m_pSearchHistoryList;
	   m_pSearchHistoryList = NULL;
   }
   _rpChildGI = NULL;
}

//******************************************************************************
bool InvestmentHistoryProcess::doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch )
{
   if(idSearch == IFASTBP_PROC::INVESTMENT_HISTORY_LIST)
      return m_pHistoryList == NULL ? false : m_pHistoryList->doMoreRecordsExist();

   else if(idSearch == IFASTBP_PROC::INVESTMENT_HISTORY_TRAN_LIST)
      return m_pDetailsList == NULL? false: m_pDetailsList->doMoreRecordsExist();

   else if(idSearch == IFASTBP_PROC::INVESTMENT_HISTORY_INT_LIST)
      return m_pInterestList == NULL? false: m_pInterestList->doMoreRecordsExist();

   else
      return false;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

//******************************************************************************
SEVERITY InvestmentHistoryProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );

	try
	{
		getParameter (INVHISTORYPROC::ACCOUNT_NUM_VALUE, m_strAcctNum);
		getParameter (INVHISTORYPROC::TRANS_ID_VALUE, m_strTransId);
		getParameter (INVHISTORYPROC::INVEST_ID, m_strInvHisInvestId);

		m_strAcctNum.strip();
		m_strTransId.strip();
		m_strInvHisInvestId.strip();

		readSearchParameters ();
	}
	catch (ConditionException &ce)
	{
		SETCONDITIONFROMEXCEPTION (ce);
	}
	catch (...)
	{
		assert (0);
		THROWFROMFILE2 (CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION);
	}

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool InvestmentHistoryProcess::doRefresh (
                               GenericInterface *rpGICaller, 
                               const I_CHAR *szOriginalCommand)
{
   TRACE_METHOD (CLASSNAME, DOREFRESH);

   setParameter (INVHISTORYPROC::ACCOUNT_NUM_VALUE, m_strAcctNum);
   setParameter (INVHISTORYPROC::INVEST_ID, m_strInvHisInvestId);

   return _rpChildGI->refresh (this, NULL);
}

//******************************************************************************
E_COMMANDRETURN InvestmentHistoryProcess::doProcess()
{
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
		setParameter (INVHISTORYPROC::ACCOUNT_NUM_VALUE, m_strAcctNum);
		rtn = invokeCommand( this, CMD_GUI_INVESTMENT_HISTORY_LIST, getProcessType(), isModal(), &_rpChildGI);
   }
   catch( ConditionException &ce )
   {
      assert( 0 );
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(rtn);
}

//******************************************************************************
bool InvestmentHistoryProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  
	// This is implemented to pass set focus on to child dialog.
	MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );
	bool bRtn = false;

	try
	{
		DString dstrAcctNum, dstrTransId;

		getParameter (INVHISTORYPROC::ACCOUNT_NUM_VALUE, dstrAcctNum);
		getParameter (INVHISTORYPROC::TRANS_ID_VALUE, dstrTransId);
		
		if (dstrTransId.strip() != m_strTransId ||
			dstrAcctNum.stripLeading ('0').strip() != m_strAcctNum )
		{
			setContainer (IFASTBP_PROC::INVESTMENT_HISTORY_LIST, NULL);
			doInit();
		}

		if(_rpChildGI)
		{
			if (isValidModelessInterface (_rpChildGI))
			{  // Only if child still exists
				bRtn = _rpChildGI->refresh (this, NULL);
			}
			if( isValidModelessInterface( _rpChildGI ) )
			{  // Only if child still exists
				bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
			}
		}
	}
	catch( ConditionException &ce )
	{
		SETCONDITIONFROMEXCEPTION( ce );
	}
	catch( ... )
	{
		assert( 0 );
		THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS, CND::BP_ERR_UNKNOWN_EXCEPTION);
	}

   return(bRtn);
}

//******************************************************************************
bool InvestmentHistoryProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_INVESTMENT_HISTORY_LIST);
}

//******************************************************************************
void *InvestmentHistoryProcess::getPtrForContainer( const BFContainerId& idContainer, 
													const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "getPtrForContainer" ) );
 
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   void *ptr = NULL;
   try
   {
		if (IFASTBP_PROC::INVESTMENT_HISTORY_LIST == idContainer)
		{
			//m_pHistoryList = NULL;
			
			readSearchParameters();
			if( dstcWorkSession->getInvestmentHistoryList (	m_pHistoryList,
															m_strAcctNum,
															m_strTransId,
															m_strFund,
															m_strClass,
															m_strInvestmentNo,
															m_strStatus,
															m_strSearchBy,
															idDataGroup) <= WARNING && m_pHistoryList)
			{
				ptr = m_pHistoryList;
			}
		}
		else if (IFASTBP_PROC::INVESTMENT_HISTORY_TRAN_LIST == idContainer )
		{
			InvestmentHistory *pInvestmentHistory = dynamic_cast <InvestmentHistory*>(
				getCBOItem (IFASTBP_PROC::INVESTMENT_HISTORY_LIST, idDataGroup));

			if (pInvestmentHistory)
			{
				m_pDetailsList = NULL;
				if( pInvestmentHistory->getInvestmentDetails (m_pDetailsList, getDataGroupId()) <= WARNING)
				{
					ptr = m_pDetailsList;
				}
			}
		}
		else if (IFASTBP_PROC::INVESTMENT_HISTORY_INT_LIST == idContainer )
		{
			InvestmentHistory *pInvestmentHistory = dynamic_cast <InvestmentHistory*>(
				getCBOItem (IFASTBP_PROC::INVESTMENT_HISTORY_LIST, idDataGroup));

			if (pInvestmentHistory)
			{
				m_pInterestList = NULL;
				if( pInvestmentHistory->getInvestmentInterestList (m_pInterestList, getDataGroupId()) <= WARNING )
				{
					ptr = m_pInterestList;
				}
			}
		}
		else if (INVESTMENT_HISTORY_SEARCH == idContainer)
		{
			if (!m_pSearchHistoryList)
			{
				m_pSearchHistoryList = new InvestmentHistoryList (*dstcWorkSession);
				m_pSearchHistoryList->init (idDataGroup);
			}
			if (m_pSearchHistoryList)
			{
				ptr = m_pSearchHistoryList;
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
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(ptr);
}

//******************************************************************************
SEVERITY InvestmentHistoryProcess::performSearch (GenericInterface *rpGICaller, 
												  const BFContainerId& idSearch, 
												  E_SEARCHACTION eSearchAction)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, PERFORMSEARCH );
	
	const BFDataGroupId& idDataGroup = getDataGroupId ();
	
	try
	{
		switch (eSearchAction)
		{
			case SEARCH_START:
			{
				readSearchParameters ();
				setContainer (IFASTBP_PROC::INVESTMENT_HISTORY_LIST, NULL);
				setContainer (IFASTBP_PROC::INVESTMENT_HISTORY_TRAN_LIST, NULL);
				setContainer (IFASTBP_PROC::INVESTMENT_HISTORY_INT_LIST, NULL);
			}
			break;
			case SEARCH_NEXT_BLOCK:
			{
				if (idSearch == IFASTBP_PROC::INVESTMENT_HISTORY_LIST)
				{
					if (m_pHistoryList)
					{
						m_pHistoryList->getMore();
					}
				}
            else if (idSearch == IFASTBP_PROC::INVESTMENT_HISTORY_TRAN_LIST)
				{
               if (m_pDetailsList)
					{
						m_pDetailsList->getMore();
					}
				}
            else if (idSearch == IFASTBP_PROC::INVESTMENT_HISTORY_INT_LIST)
				{
               if (m_pInterestList)
					{
						m_pInterestList->getMore();
					}
				}
			}
			break;

			default:
				break;

		}//end of switch (eSearchAction)
	}//end of try
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
SEVERITY InvestmentHistoryProcess::doSetField ( const GenericInterface *rpGICaller, 
                                              const BFContainerId &idContainer, 
                                              const BFFieldId &idField,
                                              const BFDataGroupId &idDataGroup, 
                                              const DString &strValue, 
                                              bool bFormatted) 
{  
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION,  CLASSNAME, I_("doSetField"));

   if ( idContainer == BF::NullContainerId )
   {
    
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY InvestmentHistoryProcess::doValidateAll (BFAbstractCBO *rpWSD, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, DOVALIDATEALL);

   if(m_pHistoryList)
   {
	  m_pHistoryList->validateAll (idDataGroup);
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
void  InvestmentHistoryProcess::readSearchParameters ()
{
	getParameter (INVHISTORYPROC::FUND, m_strFund);
	getParameter (INVHISTORYPROC::CLASS, m_strClass);
	getParameter (INVHISTORYPROC::INV_NUM, m_strInvestmentNo);
	getParameter (INVHISTORYPROC::INV_STATUS, m_strStatus);
	getParameter (INVHISTORYPROC::SEARCHBY, m_strSearchBy);

	m_strFund.strip();
	m_strClass.strip();
	m_strInvestmentNo.strip();
	m_strStatus.strip();
	m_strSearchBy.strip();
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/InvestmentHistoryProcess.cpp-arc  $
// 
//    Rev 1.14   Aug 10 2012 17:06:06   wutipong
// IN3038316 R12.5 P0186477 FN03 - Add Additional Cloumns to Investment Details
// 
//    Rev 1.13   Jul 06 2012 05:18:52   kitticha
// IN2932057 - Display the additional amount for investment history.
// 
//    Rev 1.12   May 28 2012 00:35:00   wp040100
// Removed Comments
// 
//    Rev 1.11   May 14 2012 18:27:44   wp040100
// IN 2886441 - Included BayCom/Fund Number 
// 1. Cash Sweep Screen.
// 2. Maturity Interest Instructions Screen.
// 3. GI investment Histroy Screen.
// 
//    Rev 1.10   Apr 18 2012 15:31:52   wp040100
// IN # 2891939 - Added "Forced Indicator" column in Grid 1 and "Status" in Grid 3.
// 
//    Rev 1.9   Feb 03 2012 10:39:50   jankovii
// IN 2813743 - P0186477FN03- Can't Access Maturity Instructions thru Investment Hist
// 
//    Rev 1.8   Jan 13 2012 10:47:00   wp040100
// P0186477/FN03 - GIA - Investment History Changes - Bug fixes.
// 
//    Rev 1.7   Dec 09 2011 20:03:40   wp040100
// P0186477/FN03 - GIA - Investment History Changes
// 
//    Rev 1.6   Dec 01 2011 20:39:14   wp040100
// P0186477/FN03 - GIA - Investment History Changes
// 
//    Rev 1.5   Dec 01 2011 18:03:52   wp040100
// P0186477/FN03 - GIA - Investment History Changes
// 
//    Rev 1.4   Nov 25 2011 17:39:54   wp040100
// P0186477/FN03 - GIA - Investment History Changes
 * 
 * 
// 
*/
