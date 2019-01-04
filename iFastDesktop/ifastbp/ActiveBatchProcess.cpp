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
//    Copyright 2007 IFDS Canada
//
//******************************************************************************
//
// ^FILE   : ActiveBatchProcess.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 27/09/07
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : ActiveBatchProcess
//    This class checks if there are any active batches
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "ActiveBatchProcess.hpp"
#include "ifastcbo\activebatch.hpp"
#include <bfcbo\bfnotification.hpp>
#include <ifastdbrkr\dstchost.hpp>
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ACTIVE_BATCH;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< ActiveBatchProcess > processCreator( CMD_BPROC_ACTIVE_BATCH );

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "ActiveBatchProcess" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

ActiveBatchProcess::ActiveBatchProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

//******************************************************************************

ActiveBatchProcess::~ActiveBatchProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY ActiveBatchProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOINIT );
   
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************

E_COMMANDRETURN ActiveBatchProcess::doProcess()
{  
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
	  // if release mode and if there are active batches, don't allow user to 
	  // log off, before closing the active batches
	  boolean blDebugMode = false;
	  #ifdef _DEBUG
        blDebugMode = true;
      #endif

      if( !blDebugMode )
	  {
		ActiveBatch activeBatch (getBFSession()->getUserSession());

		if (activeBatch.init (getBFSession(), getDataGroupId()) <= WARNING)
		{
			DString dstrActiveBatches;
			activeBatch.getActiveBatchesList (dstrActiveBatches);
			if (  !dstrActiveBatches.strip().empty ())
			{
				setParameter ( I_("ActiveBatches"), dstrActiveBatches);
			}
		}
	  }

      rtn = CMD_OK;
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
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/ActiveBatchProcess.cpp-arc  $
// 
//    Rev 1.0   27 Sep 2007 14:40:12   kovacsro
// Initial revision.
 * 
 *
 */

