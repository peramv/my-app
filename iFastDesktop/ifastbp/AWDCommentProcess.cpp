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
//******************************************************************************
//
// ^FILE   : AWDCommentProcess.cpp
// ^AUTHOR : Monica Vadeanu
// ^DATE   : April 2004
//
// ----------------------------------------------------------
//
// ^CLASS    : AWDCommentProcess.cpp
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for a list selection dialog

//******************************************************************************

#include "stdafx.h"
#include "AWDCommentProcess.hpp"
#include "AWDCommentProcessincludes.h"
#include <dataimpl\dse_dstcglob_vw.hpp>
#include "mfcaninterprocparam.hpp"
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_AWD_COMMENT;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_AWD_COMMENT;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< AWDCommentProcess > processCreator( CMD_BPROC_AWD_COMMENT );

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "AWDCommentProcess" );
}

namespace CONFPROC
{
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************
AWDCommentProcess::AWDCommentProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, m_rpChildGI( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   // AWD Details   	
	addFieldDetails( ifds::BusinessArea, BF::NullContainerId );
   addFieldDetails( ifds::WorkType,     BF::NullContainerId );
   addFieldDetails( ifds::StatusDesc,   BF::NullContainerId );

	addFieldDetails( ifds::Remark1,  BF::NullContainerId );
   addFieldDetails( ifds::Remark2,  BF::NullContainerId );
   addFieldDetails( ifds::Remark3,  BF::NullContainerId );
   addFieldDetails( ifds::Remark4,  BF::NullContainerId );
   addFieldDetails( ifds::Remark5,  BF::NullContainerId );   
}

//******************************************************************************
AWDCommentProcess::~AWDCommentProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   m_rpChildGI = NULL;
}

//******************************************************************************
SEVERITY AWDCommentProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool AWDCommentProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_AWD_COMMENT );
}

//******************************************************************************
bool AWDCommentProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{
   return(false);
}

//******************************************************************************
bool AWDCommentProcess::doCancel( GenericInterface *rpGI )
{  
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOCANCEL );
   return(true);
}

//******************************************************************************
E_COMMANDRETURN AWDCommentProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      rtn = invokeCommand( this, CMD_GUI_AWD_COMMENT, getProcessType(), isModal(), &m_rpChildGI );
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
bool AWDCommentProcess::doRefresh( GenericInterface *rpGICaller, const I_CHAR *szOriginalCommand )
{
   TRACE_METHOD( CLASSNAME, DOREFRESH );
   return(true);
}

//******************************************************************************
bool AWDCommentProcess::doOk( GenericInterface *rpGICaller )
{
   bool bRet = true; //no matter what return true
   return(bRet);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AWDCommentProcess.cpp-arc  $
// 
//    Rev 1.1   May 10 2004 12:18:34   VADEANUM
// PET1017 - AWD Comments - Limit Comment to 250 characters.
// 
//    Rev 1.0   May 06 2004 16:30:50   VADEANUM
// Initial revision.
 */
