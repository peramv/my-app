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
// ^FILE   : InterestSegmentProcess.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : InterestSegmentProcess
//    
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************
//ifastbp
#include "stdafx.h"
#include "InterestSegmentProcessIncludes.h"
#include "InterestSegmentProcess.hpp"
#include <ifastdataimpl\dse_dstcglob_vw.hpp>
#include <ifastcbo\InterestSegmentList.hpp>
#include <ifastcbo\worksessionentitylist.hpp>
#include <ifastcbo\errmsgruleslist.hpp>
#include <ifastcbo\mgmtco.hpp>
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_INTEREST_SEGMENT_LIST;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_INTEREST_SEGMENT_LIST;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< InterestSegmentProcess > processCreator( CMD_BPROC_INTEREST_SEGMENT_LIST);

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId INTEREST_SEGMENT_LIST;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME		= I_( "InterestSegmentProcess" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
	extern CLASS_IMPORT const BFTextFieldId InterestSegmentDetailsList;
}

//******************************************************************************
//              Public Methods
//******************************************************************************
InterestSegmentProcess::InterestSegmentProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( NULL )
, m_strAcctNum(NULL_STRING)
, m_strIntInvestID(NULL_STRING)
, m_pInterestSegmentList (NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );   

	addContainer (IFASTBP_PROC::INTEREST_SEGMENT_LIST, true, BF::NullContainerId, true);

	//Fields related to Interest Segment Dialog
	addFieldDetails (ifds::InvHisIntSegment					, IFASTBP_PROC::INTEREST_SEGMENT_LIST); //
	addFieldDetails (ifds::InvHisRate						, IFASTBP_PROC::INTEREST_SEGMENT_LIST); //
}

//******************************************************************************
InterestSegmentProcess::~InterestSegmentProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   _rpChildGI = NULL;
}

//******************************************************************************
bool InterestSegmentProcess::doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch )
{
   return m_pInterestSegmentList == NULL ? false : m_pInterestSegmentList->doMoreRecordsExist();
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

//******************************************************************************
SEVERITY InterestSegmentProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );

	try
	{
		getParameter (INTSEGMENT::ACCOUNT_NUM_VALUE, m_strAcctNum);
		getParameter (INTSEGMENT::INVEST_ID, m_strIntInvestID);
		
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
E_COMMANDRETURN InterestSegmentProcess::doProcess()
{
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
		setParameter (INTSEGMENT::ACCOUNT_NUM_VALUE, m_strAcctNum);
		setParameter (INTSEGMENT::INVEST_ID, m_strIntInvestID);

		rtn = invokeCommand( this, CMD_GUI_INTEREST_SEGMENT_LIST, getProcessType(), isModal(), &_rpChildGI);
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
bool InterestSegmentProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  
	// This is implemented to pass set focus on to child dialog.
	MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );
	bool bRtn = false;

	try
	{
		DString dstrAcctNum, dstrIntInvestID;
		getParameter (INTSEGMENT::ACCOUNT_NUM_VALUE, dstrAcctNum);
		getParameter (INTSEGMENT::INVEST_ID, dstrIntInvestID);

		if (dstrIntInvestID.strip() != m_strIntInvestID ||
			dstrAcctNum.stripLeading ('0').strip() != m_strAcctNum )
		{
			setContainer (IFASTBP_PROC::INTEREST_SEGMENT_LIST, NULL);
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
bool InterestSegmentProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_INTEREST_SEGMENT_LIST);
}

//******************************************************************************
void *InterestSegmentProcess::getPtrForContainer( const BFContainerId& idContainer, 
												  const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "getPtrForContainer" ) );
 
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   void *ptr = NULL;
   try
   {
		if (IFASTBP_PROC::INTEREST_SEGMENT_LIST == idContainer)
		{
			m_strAcctNum.strip();
			m_strIntInvestID.strip();

			//m_pInterestSegmentList = NULL;
			if( dstcWorkSession->getInterestSegmentList( m_pInterestSegmentList,
														 m_strAcctNum,
														 m_strIntInvestID,
														 idDataGroup) <= WARNING && m_pInterestSegmentList)
			{
				ptr = m_pInterestSegmentList;
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
/* $Log:   Y:/VCS/BF iFAST/ifastbp/InterestSegmentProcess.cpp-arc  $
// 
//    Rev 1.2   Feb 02 2012 20:42:54   wp040100
// P0186477 FN03 - IN # 2832278 - Interest segments display change.
// 
//    Rev 1.1   Dec 20 2011 14:45:52   wp040100
// P0186477/FN03 - Added substitution set for Interest Segment dialog. View 422.
// 
//    Rev 1.0   Dec 09 2011 19:35:34   wp040100
// Initial revision.
// 
//
//
//
//
 */
