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
// ^FILE   : ProgressiveIntRateProcess.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : ProgressiveIntRateProcess
//    
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************
//ifastbp
#include "stdafx.h"
#include "ProgressiveIntRateProcessIncludes.h"
#include "ProgressiveIntRateProcess.hpp"
#include <ifastdataimpl\dse_dstcglob_vw.hpp>
#include <ifastcbo\ProgressiveIntRateList.hpp>
#include <ifastcbo\worksessionentitylist.hpp>
#include <ifastcbo\errmsgruleslist.hpp>
#include <ifastcbo\mgmtco.hpp>
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_PROGRESSIVE_INTEREST_RATE_LIST;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_PROGRESSIVE_INTEREST_RATE_LIST;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< ProgressiveIntRateProcess > processCreator( CMD_BPROC_PROGRESSIVE_INTEREST_RATE_LIST);

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId INVESTMENT_HISTORY_LIST;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME		= I_( "ProgressiveIntRateProcess" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}


namespace IFASTERR
{
   //extern CLASS_IMPORT I_CHAR * const PROGRESSIVE_INT_LIST_DATA_REQUIRED;
}


namespace ifds
{
	extern CLASS_IMPORT const BFTextFieldId ProgressiveIntRateDetailsList;
}

//******************************************************************************
//              Public Methods
//******************************************************************************
ProgressiveIntRateProcess::ProgressiveIntRateProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( NULL )
, m_strAcctNum(NULL_STRING)
, m_strIntInvestID(NULL_STRING)
, m_pProgressiveIntRateList (NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );   

	addContainer (IFASTBP_PROC::PROGRESSIVE_INTEREST_RATE_LIST, true, BF::NullContainerId, true);

	//Fields related to Progressive Interest Rate Dialog
	addFieldDetails (ifds::ProgressiveInvTerm					, IFASTBP_PROC::PROGRESSIVE_INTEREST_RATE_LIST); //Int
	addFieldDetails (ifds::ProgressiveIntRate					, IFASTBP_PROC::PROGRESSIVE_INTEREST_RATE_LIST); //Decimal
}

//******************************************************************************
ProgressiveIntRateProcess::~ProgressiveIntRateProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   _rpChildGI = NULL;
}

//******************************************************************************
bool ProgressiveIntRateProcess::doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch )
{
   return m_pProgressiveIntRateList == NULL ? false : m_pProgressiveIntRateList->doMoreRecordsExist();
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

//******************************************************************************
SEVERITY ProgressiveIntRateProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );

	try
	{
		getParameter (PROGINTRATE::ACCOUNT_NUM_VALUE, m_strAcctNum);
		getParameter (PROGINTRATE::INVEST_ID, m_strIntInvestID);
		
		m_strAcctNum.strip();
		m_strIntInvestID.strip();
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
/*
bool ProgressiveIntRateProcess::doRefresh (
                               GenericInterface *rpGICaller, 
                               const I_CHAR *szOriginalCommand)
{
   TRACE_METHOD (CLASSNAME, DOREFRESH);

   setParameter (PROGINTRATE::ACCOUNT_NUM_VALUE, m_strAcctNum);
   return _rpChildGI->refresh (this, NULL);
}
*/

//******************************************************************************
E_COMMANDRETURN ProgressiveIntRateProcess::doProcess()
{
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
		setParameter (PROGINTRATE::ACCOUNT_NUM_VALUE, m_strAcctNum);
		setParameter (PROGINTRATE::INVEST_ID, m_strIntInvestID);

		rtn = invokeCommand( this, CMD_GUI_PROGRESSIVE_INTEREST_RATE_LIST, getProcessType(), isModal(), &_rpChildGI);
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
bool ProgressiveIntRateProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  
	// This is implemented to pass set focus on to child dialog.
	MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );
	bool bRtn = false;

	try
	{
		DString dstrAcctNum, dstrIntInvestID;
		getParameter (PROGINTRATE::ACCOUNT_NUM_VALUE, dstrAcctNum);
		getParameter (PROGINTRATE::INVEST_ID, dstrIntInvestID);

		if (dstrIntInvestID.strip() != m_strIntInvestID ||
			dstrAcctNum.stripLeading ('0').strip() != m_strAcctNum )
		{
			setContainer (IFASTBP_PROC::PROGRESSIVE_INTEREST_RATE_LIST, NULL);
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
bool ProgressiveIntRateProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_PROGRESSIVE_INTEREST_RATE_LIST);
}

//******************************************************************************
void *ProgressiveIntRateProcess::getPtrForContainer( const BFContainerId& idContainer, 
													 const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "getPtrForContainer" ) );
 
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   void *ptr = NULL;
   try
   {
		if (IFASTBP_PROC::PROGRESSIVE_INTEREST_RATE_LIST == idContainer)
		{
			m_strAcctNum.strip();
			m_strIntInvestID.strip();

			//m_pProgressiveIntRateList = NULL;
			if( dstcWorkSession->getProgressiveIntRateList( m_pProgressiveIntRateList,
															m_strAcctNum,
															m_strIntInvestID,
															idDataGroup) <= WARNING && m_pProgressiveIntRateList)
			{
				ptr = m_pProgressiveIntRateList;
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
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastbp/ProgressiveIntRateProcess.cpp-arc  $
// 
//    Rev 1.3   May 28 2012 00:35:16   wp040100
// Removed Comments
// 
//    Rev 1.2   Dec 01 2011 19:11:20   wp040100
// P0186477/FN03 - GIA - Investment History Changes
// 
//    Rev 1.1   Dec 01 2011 18:03:08   wp040100
// P0186477/FN03 - GIA - Investment History Changes
// 
//    Rev 1.0   Nov 27 2011 21:17:42   wp040100
// Initial revision.
//
//
//
 */
