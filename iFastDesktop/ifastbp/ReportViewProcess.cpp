//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 by International Financial.
//
//******************************************************************************
//
// ^FILE   : ReportViewProcess.cpp
// ^AUTHOR : 
// ^DATE   : Dec 8, 2002
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : ReportViewProcess
//   
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "reportviewprocess.hpp"
#include "reportviewprocessincludes.h"

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_REPORT_VIEW;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_REPORT_VIEW;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< ReportViewProcess > processCreator( CMD_BPROC_REPORT_VIEW );

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME               = I_( "ReportViewProcess" );      
}



namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************
// Constructor - Container and field details are initialized here.
//******************************************************************************

//CP20030319ReportViewProcess::ReportViewProcess() : 
ReportViewProcess::ReportViewProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _dstrReportPath ( NULL_STRING ), 
_dstrReportName ( NULL_STRING ),
_dstrReportData ( NULL_STRING ),
_rpChildGI ( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING ); 
   addFieldDetails( ifds::Description, BF::NullContainerId, SUBCLASS_PROCESS );
}

//******************************************************************************
// Destructor 
//******************************************************************************

ReportViewProcess::~ReportViewProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );   
}

//******************************************************************************
// @returns SEVERITY.
//******************************************************************************

SEVERITY ReportViewProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      getParameter( REPORT_VIEW::REPORTPATH, _dstrReportPath );
      getParameter( REPORT_VIEW::REPORTNAME, _dstrReportName );
      getParameter( REPORT_VIEW::REPORTDATA, _dstrReportData );
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
// Function which tells the generic interface container that the modeless child
// has been destroyed.
// @param   const Command &cmd - cmd indicating the child is destroyed.
// @returns bool - true when successful.
//******************************************************************************

bool ReportViewProcess::doModelessChildComplete( const Command &cmd )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOMODELESSCHILDCOMPLETE );

   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_REPORT_VIEW );
}


//******************************************************************************
//******************************************************************************

bool ReportViewProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );

   bool bRtn = false;
   try
   {
      assert( _rpChildGI && isValidModelessInterface( _rpChildGI ) );

      if( isValidModelessInterface( _rpChildGI ) )
      {  // Only if child still exists
         bRtn = _rpChildGI->refresh( this, NULL );
         bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
      }
      return(bRtn);
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
   return(false);
}

//******************************************************************************
// This functions starts the Reports Dialog
// @returns E_COMMANDRETURN.
//******************************************************************************

E_COMMANDRETURN ReportViewProcess::doProcess()
{  
   MAKEFRAME2( CND::IFASTBP_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter( REPORT_VIEW::REPORTPATH, _dstrReportPath );
      setParameter( REPORT_VIEW::REPORTNAME, _dstrReportName );      
      rtn = invokeCommand( this, CMD_GUI_REPORT_VIEW, getProcessType(),
                           isModal(), &_rpChildGI );
   }
   catch( ConditionException &ce )
   {
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

SEVERITY ReportViewProcess::ok2( GenericInterface *rpGI )
{
   MAKEFRAME2( CND::IFASTBP_CONDITION, CLASSNAME, OK2 );
   return NO_CONDITION;
}

void ReportViewProcess::doGetField(
                                const GenericInterface *rpGICaller,
                                const BFContainerId& idContainer,
                                const BFFieldId& idField,
                                const BFDataGroupId& idDataGroup,
                                DString &strValueOut,
                                bool bFormatted
                                ) const
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOGETFIELD );   
   if ( BF::NullContainerId == idContainer ) {
      if ( idField == ifds::Description ) 
         strValueOut = _dstrReportData;
   }
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/ReportViewProcess.cpp-arc  $
// 
//    Rev 1.3   Mar 21 2003 17:46:50   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.2   Dec 10 2002 13:34:56   HSUCHIN
// added dogetfield
// 
//    Rev 1.1   Dec 10 2002 10:59:26   HSUCHIN
// added report data
// 
//    Rev 1.0   Dec 08 2002 22:10:50   HSUCHIN
// Initial Revision
 */
