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
// ^FILE   : MgmtDetailsProcess.cpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 16/04/99
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : MgmtDetailsProcess
//    This class manages the management company and profile selection.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "mgmtdetailsprocess.hpp"
#include "mgmtdetailsprocessincludes.h"
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_MGMTDETAILS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_MGMTDETAILS;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< MgmtDetailsProcess > processCreator( CMD_BPROC_MGMTDETAILS );

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME     = I_( "MgmtDetailsProcess" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern CLASS_IMPORT const long BP_ERR_INVALID_METHOD_CALL;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319MgmtDetailsProcess::MgmtDetailsProcess() : 
MgmtDetailsProcess::MgmtDetailsProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( NULL )

{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addFieldDetails( ifds::FundCode, BF::NullContainerId, SUBCLASS_PROCESS );
}

//******************************************************************************

MgmtDetailsProcess::~MgmtDetailsProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   _rpChildGI = NULL;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY MgmtDetailsProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;
   sevRtn = NO_CONDITION;

   getParameter( I_( "FundCodeValue" ), m_FundCode );

   return(sevRtn);
}

//******************************************************************************

void MgmtDetailsProcess::doGetField(
                                   const GenericInterface *rpGICaller,
                                   const BFContainerId& idContainer,
                                   const BFFieldId& idField,
                                   const BFDataGroupId& idDataGroup,
                                   DString &strValueOut,
                                   bool bFormatted
                                   ) const
{
   if( idField == ifds::FundCode )
   {
      strValueOut = m_FundCode;
   }
   else
   {
      assert( 0 );   
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETFIELD,
                      CND::BP_ERR_INVALID_METHOD_CALL );
   }
}

//******************************************************************************

bool MgmtDetailsProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_MGMTDETAILS );
}

//******************************************************************************

bool MgmtDetailsProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   bool bRtn = false;

   getParameter( I_( "FundCodeValue" ), m_FundCode );
   if( _rpChildGI && isValidModelessInterface( _rpChildGI ) )
   {
      bRtn = _rpChildGI->refresh( this, NULL );
      bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
   }
   return(bRtn);
}

//******************************************************************************

E_COMMANDRETURN MgmtDetailsProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      rtn = invokeCommand( this, CMD_GUI_MGMTDETAILS, getProcessType(),
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
/* $Log:   Y:/VCS/BF iFAST/ifastbp/MgmtDetailsProcess.cpp-arc  $
 * 
 *    Rev 1.8   Mar 21 2003 17:45:08   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.7   Oct 09 2002 23:53:30   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.6   Aug 29 2002 16:45:08   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.5   Aug 29 2002 12:54:34   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.4   22 May 2002 18:24:52   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.3   27 Mar 2002 19:55:30   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.2   15 Dec 2000 12:43:44   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.1   Aug 02 2000 15:32:02   BUZILA
 * "locale" changes
 * 
 *    Rev 1.0   Feb 15 2000 10:59:36   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.7   Dec 08 1999 16:28:04   HSUCHIN
 * changed doGetField and doSetField to include groupid
 * 
 *    Rev 1.6   Oct 29 1999 11:13:58   DT24433
 * removed doCancel/doOK
 * 
 *    Rev 1.5   Aug 30 1999 18:22:48   DT24433
 * changed dogetfield method parms
 * 
 *    Rev 1.4   Aug 17 1999 18:36:42   DT24433
 * removed static FieldDetails array
 * 
 *    Rev 1.3   Jul 20 1999 11:14:10   VASILEAD
 * New conditions update
 * 
 *    Rev 1.2   Jul 15 1999 16:39:26   BUZILA
 * Fixing Mgmt Detail
 * 
 *    Rev 1.1   Jul 08 1999 10:02:08   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */

