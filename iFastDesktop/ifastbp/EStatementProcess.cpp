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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : EStatementProcess.cpp
// ^AUTHOR : Shaobo Huang
// ^DATE   : July, 2002
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : EStatementProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "EStatementProcess.hpp"
#include "EStatementProcessIncludes.h"
#include <ifastdbrkr\dstchost.hpp>
#include <ifastcbo\mgmtco.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_ESTATEMENT;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ESTATEMENT;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< EStatementProcess > processCreator( CMD_BPROC_ESTATEMENT );

namespace
{
   const I_CHAR * const CLASSNAME     = I_( "EStatementProcess" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern CLASS_IMPORT const long BP_ERR_INVALID_METHOD_CALL;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId CompanyId;
}
//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319EStatementProcess::EStatementProcess() : 
EStatementProcess::EStatementProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( NULL )

{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addFieldDetails( ESTATEMENT::ACCOUNT_NUM,    BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ESTATEMENT::RTS_SESSION_ID, BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ESTATEMENT::USER_ID,        BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ESTATEMENT::LANGUAGE_ID,    BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ESTATEMENT::LOCALE_ID,      BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ESTATEMENT::MANAGEMENT_CO_ID,  BF::NullContainerId, SUBCLASS_PROCESS );
}

//******************************************************************************

EStatementProcess::~EStatementProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   _rpChildGI = NULL;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY EStatementProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;
   sevRtn = NO_CONDITION;

   getParameter( I_("ACCOUNT_NUM_PARAM"), m_accountNum );

   return(sevRtn);
}

//******************************************************************************

void EStatementProcess::doGetField(
                                  const GenericInterface *rpGICaller,
                                  const BFContainerId& idContainer,
                                  const BFFieldId& idField,
                                  const BFDataGroupId& idDataGroup,
                                  DString &strValueOut,
                                  bool bFormatted
                                  ) const
{
   DSTCWorkSession* dstWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   DSTCUserSession& dstUserSession = dynamic_cast<DSTCUserSession &>(dstWorkSession->getUserSession());

   if( idField == ESTATEMENT::ACCOUNT_NUM )
   {
      strValueOut = m_accountNum;
   }
   else if( idField == ESTATEMENT::RTS_SESSION_ID )
   {
      strValueOut = dstUserSession.getSessionId(DSTCHost::getPrimaryHost());
   }
   else if( idField == ESTATEMENT::USER_ID )
   {
      strValueOut = dstUserSession.getUserId(DSTCHost::getPrimaryHost());
   }
   else if( idField == ESTATEMENT::LANGUAGE_ID )
   {
      strValueOut = dstUserSession.getLanguage();
   }
   else if( idField == ESTATEMENT::LOCALE_ID )
   {
      strValueOut = getClientLocale().getLocale();
   }
   else if( idField == ESTATEMENT::MANAGEMENT_CO_ID )
   {
      dstWorkSession->getMgmtCo().getField( ifds::CompanyId,strValueOut,idDataGroup );
   }
   else
   {
      assert( 0 );   
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETFIELD,
                      CND::BP_ERR_INVALID_METHOD_CALL );
   }
}

//******************************************************************************

bool EStatementProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_ESTATEMENT );
}

//******************************************************************************

bool EStatementProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   bool bRtn = false;

   getParameter( I_("ACCOUNT_NUM_PARAM"), m_accountNum );

   if( _rpChildGI && isValidModelessInterface( _rpChildGI ) )
   {
      bRtn = _rpChildGI->refresh( this, NULL );
      bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
   }
   return(bRtn);
}

//******************************************************************************

E_COMMANDRETURN EStatementProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      rtn = invokeCommand( this, CMD_GUI_ESTATEMENT, getProcessType(),
                           isModal(), &_rpChildGI );
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
/* $Log:   Y:/VCS/BF iFAST/ifastbp/EStatementProcess.cpp-arc  $
// 
//    Rev 1.4   Mar 21 2003 17:39:26   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.3   Oct 09 2002 23:53:12   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.2   Aug 29 2002 16:44:54   SMITHDAV
// Condition split.
// 
//    Rev 1.1   Aug 29 2002 12:54:20   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.0   31 Jul 2002 09:32:08   HUANGSHA
// Initial revision.
 * 
 */

