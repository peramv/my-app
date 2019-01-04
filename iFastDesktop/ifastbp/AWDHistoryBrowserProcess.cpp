//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2013 by International Financial, Inc.
//
//******************************************************************************

#include "stdafx.h"
#include "awdhistorybrowserprocess.hpp"
#include "awdhistorybrowserprocessincludes.h"

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_AWDHISTORY_BROWSER;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_AWDHISTORY_BROWSER;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< AWDHistoryBrowserProcess > processCreator( CMD_BPROC_AWDHISTORY_BROWSER );

namespace
{
	// Trace literals
	const I_CHAR * const CLASSNAME = I_( "AWDHistoryBrowserProcess" );
}

namespace CND
{
	extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

AWDHistoryBrowserProcess::AWDHistoryBrowserProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI(NULL)
, _accountNum(NULL_STRING)
, _extTransNum(NULL_STRING)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

AWDHistoryBrowserProcess::~AWDHistoryBrowserProcess(void)
{
	TRACE_DESTRUCTOR( CLASSNAME );

   _rpChildGI = NULL;
}

//******************************************************************************

SEVERITY AWDHistoryBrowserProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOINIT );
   getParameter( MFCAN_IP_PARAM::ACCOUNT_NUM, _accountNum );
   getParameter( MFCAN_IP_PARAM::TRANS_NUM, _extTransNum );
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

E_COMMANDRETURN AWDHistoryBrowserProcess::doProcess()
{  
   MAKEFRAME2( CND::IFASTBP_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
	  setParameter( MFCAN_IP_PARAM::ACCOUNT_NUM, _accountNum );
	  setParameter( MFCAN_IP_PARAM::TRANS_NUM, _extTransNum );
      rtn = invokeCommand( this, CMD_GUI_AWDHISTORY_BROWSER, getProcessType(), isModal(), &_rpChildGI );
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