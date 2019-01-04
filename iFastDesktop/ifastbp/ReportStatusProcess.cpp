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
// ^FILE   : ReportStatusProcess.cpp
// ^AUTHOR : 
// ^DATE   : Nov 28, 2002
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : ReportStatusProcess
//   
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "reportstatusprocess.hpp"
#include "reportstatusprocessincludes.h"
#include <ifastcbo\reportstatuscriteria.hpp>
#include <ifastcbo\reportstatus.hpp>
#include <ifastcbo\reportstatuslist.hpp>
#include <ifastcbo\reportparamlist.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\dstcusersession.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_REPORT_STATUS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_REPORT_STATUS;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< ReportStatusProcess > processCreator( CMD_BPROC_REPORT_STATUS );

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME               = I_( "ReportStatusProcess" );
   const I_CHAR * const PERFORMSEARCH           = I_( "performSearch" );   
}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************
// Constructor - Container and field details are initialized here.
//******************************************************************************

//CP20030319ReportStatusProcess::ReportStatusProcess() : 
ReportStatusProcess::ReportStatusProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::REPORT_STATUS_CRITERIA, false, BF::NullContainerId, true ); 
   addContainer( IFASTBP_PROC::REPORT_STATUS_LIST, true, BF::NullContainerId, false );
   addContainer( IFASTBP_PROC::REPORT_PARAM_LIST, true, IFASTBP_PROC::REPORT_STATUS_LIST, false );  

   addFieldDetails( ifds::CompanyId, IFASTBP_PROC::REPORT_STATUS_CRITERIA );   
   addFieldDetails( ifds::StartDate, IFASTBP_PROC::REPORT_STATUS_CRITERIA );

   addFieldDetails( ifds::SchedJobId, IFASTBP_PROC::REPORT_STATUS_LIST );
   addFieldDetails( ifds::ReportName, IFASTBP_PROC::REPORT_STATUS_LIST );
   addFieldDetails( ifds::StartDate, IFASTBP_PROC::REPORT_STATUS_LIST );
   addFieldDetails( ifds::EndDate, IFASTBP_PROC::REPORT_STATUS_LIST );
   addFieldDetails( ifds::StartTime, IFASTBP_PROC::REPORT_STATUS_LIST );
   addFieldDetails( ifds::FinalTime, IFASTBP_PROC::REPORT_STATUS_LIST );
   addFieldDetails( ifds::JobStatus, IFASTBP_PROC::REPORT_STATUS_LIST );   
   addFieldDetails( ifds::OutputFileName, IFASTBP_PROC::REPORT_STATUS_LIST );
   addFieldDetails( ifds::OutputFilePath, IFASTBP_PROC::REPORT_STATUS_LIST );   
   addFieldDetails( ifds::PrinterName, IFASTBP_PROC::REPORT_STATUS_LIST, SUBCLASS_PROCESS );   

   addFieldDetails( ifds::CriteriaType, IFASTBP_PROC::REPORT_PARAM_LIST );
   addFieldDetails( ifds::CriteriaValue, IFASTBP_PROC::REPORT_PARAM_LIST );   
   addFieldDetails( ifds::IncludeExclude, IFASTBP_PROC::REPORT_PARAM_LIST );
}

//******************************************************************************
// Destructor 
//******************************************************************************

ReportStatusProcess::~ReportStatusProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
// Function which get the container pointer on demand.
// @param   const BFContainerId& idContainer - Id to the container.
//          const BFDataGroupId& idDataGroup - group id.
// @returns void.
//******************************************************************************

void *ReportStatusProcess::getPtrForContainer(
                                             const BFContainerId& idContainer,
                                             const BFDataGroupId& idDataGroup
                                             )
{
   void *ptr = NULL;
   SEVERITY sevRtn = NO_CONDITION;
   try
   {
//CP20030319      switch( idContainer )
//CP20030319      {
      // RSP Contribution List
//CP20030319         case REPORT_STATUS::REPORT_STATUS_CRITERIA :
      if( IFASTBP_PROC::REPORT_STATUS_CRITERIA == idContainer )
      {
         {            
            ReportStatusCriteria* pReportStatusCriteria = NULL;
            DSTCUserSession &pDSTCUserSession = dynamic_cast<DSTCUserSession &>(getBFSession()->getUserSession());
            pDSTCUserSession.getReportStatusCriteria( pReportStatusCriteria, idDataGroup );
            if( pReportStatusCriteria )
               ptr = pReportStatusCriteria;
            else
            {
               pDSTCUserSession.createReportStatusCriteria( pReportStatusCriteria, idDataGroup );
               ptr = pReportStatusCriteria;
            }
         }
//CP20030319            break;
//CP20030319         case REPORT_STATUS::REPORT_STATUS_LIST :
      }
      else if( IFASTBP_PROC::REPORT_STATUS_LIST == idContainer )
      {
         {
            ReportStatusCriteria *pReportStatusCriteria = dynamic_cast< ReportStatusCriteria * >( getCBOItem( IFASTBP_PROC::REPORT_STATUS_CRITERIA, idDataGroup ) );
            if( pReportStatusCriteria )
            {
               if( pReportStatusCriteria->validateAll (idDataGroup ) < WARNING )
               {
                  ReportStatusList* pReportStatusList;
                  pReportStatusCriteria->getReportStatusList( pReportStatusList, idDataGroup );
                  if( !pReportStatusList )
                  {
                     pReportStatusCriteria->createReportStatusList( pReportStatusList, idDataGroup );
                  }
                  _pReportStatusList = pReportStatusList;
                  ptr = pReportStatusList;
               }
            }
         }   
//CP20030319            break;
//CP20030319         case REPORT_STATUS::REPORT_PARAM_LIST :
      }
      else if( IFASTBP_PROC::REPORT_PARAM_LIST == idContainer )
      {
         {
            ReportStatus *pReportStatus = dynamic_cast< ReportStatus * >( getCBOItem( IFASTBP_PROC::REPORT_STATUS_LIST, idDataGroup ) );
            if( pReportStatus )
            {
               ReportParamList* pReportParamList;
               pReportStatus->getReportParamList ( pReportParamList, idDataGroup );
               if( !pReportParamList )
                  pReportStatus->createReportParamList ( pReportParamList, idDataGroup );
               ptr = pReportParamList;
            }
         }
//CP20030319            break;
//CP20030319      }
      }
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( ... )
   {
      //Show we throw?
   }
   return(ptr);
}

//******************************************************************************
// @returns SEVERITY.
//******************************************************************************

SEVERITY ReportStatusProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
//      getParameter( REPORT_GROUP, _dstrReportGroup );     
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

bool ReportStatusProcess::doModelessChildComplete( const Command &cmd )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOMODELESSCHILDCOMPLETE );

   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_REPORT_STATUS );
}


//******************************************************************************
// Functions which brings the Report dialog to focus and top of the window 
// stack.  It also notifies Report to refresh in case account information 
// has changed.
// @param   GenericInterface *rpGICaller - pointer to parent object.
// @return bool - true when successful, false otherwise.
//******************************************************************************

bool ReportStatusProcess::doModelessSetFocus( GenericInterface *rpGICaller )
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

E_COMMANDRETURN ReportStatusProcess::doProcess()
{  
   MAKEFRAME2( CND::IFASTBP_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      rtn = invokeCommand( this, CMD_GUI_REPORT_STATUS, getProcessType(),
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

SEVERITY ReportStatusProcess::performSearch( GenericInterface *rpGICaller, 
                                             const BFContainerId& idSearch, E_SEARCHACTION eSearchAction )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, PERFORMSEARCH );
   SEVERITY sevRtn = SEVERE_ERROR;
   if( idSearch == IFASTBP_PROC::REPORT_STATUS_LIST )
   {
      const BFDataGroupId& idDataGroup = getDataGroupId ();
      if( eSearchAction == SEARCH_START )
      {
         ReportStatusCriteria *pReportStatusCriteria = dynamic_cast< ReportStatusCriteria * >( getCBOItem( IFASTBP_PROC::REPORT_STATUS_CRITERIA, idDataGroup  ) );
         //ReportStatusList* pReportStatusList;
         sevRtn = pReportStatusCriteria->validateAll (idDataGroup  );
         if( sevRtn < WARNING )
         {
            pReportStatusCriteria->createReportStatusList( _pReportStatusList, idDataGroup  );
            setContainer ( IFASTBP_PROC::REPORT_STATUS_LIST, _pReportStatusList );
         }
         else
         {
            return(sevRtn);
         }
      }
      else if( eSearchAction == SEARCH_NEXT_BLOCK )
      {
         try
         {
            sevRtn = _pReportStatusList->getMore ();
         }
         catch( ConditionException &ce )
         {
            SETCONDITIONFROMEXCEPTION( ce );
         }
         catch( ... )
         {
            assert( 0 );
            THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, PERFORMSEARCH, CND::BP_ERR_UNKNOWN_EXCEPTION );
         }
      }
   }
   return(sevRtn); 
}

bool ReportStatusProcess::doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch )
{
   if( idSearch == IFASTBP_PROC::REPORT_STATUS_LIST )
   {
      return( _pReportStatusList == NULL ) ? false : _pReportStatusList->doMoreRecordsExist();
   }
   else
      return(false);
} 

SEVERITY ReportStatusProcess::doSetField( const GenericInterface *rpGICaller,
                                          const BFContainerId& idContainer,
                                          const BFFieldId& fieldID,
                                          const BFDataGroupId& idDataGroup,
                                          const DString& strValue,
                                          bool bFormatted )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOSETFIELD );

   if( idContainer == IFASTBP_PROC::REPORT_STATUS_LIST )
   {
      ReportStatus *pReportStatus = dynamic_cast< ReportStatus * >( getCBOItem( IFASTBP_PROC::REPORT_STATUS_LIST, idDataGroup ) );
      pReportStatus->printReport ( strValue, idDataGroup );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/ReportStatusProcess.cpp-arc  $
// 
//    Rev 1.3   Feb 21 2006 12:03:04   popescu
// Incindent# 544677 - correctly updates the Begin and End time of a work object.
// 
//    Rev 1.2   Mar 21 2003 17:46:42   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.1   Dec 08 2002 22:12:36   HSUCHIN
// added support for printer process and report view
// 
//    Rev 1.0   Nov 29 2002 13:51:54   HSUCHIN
// Initial Revision
 */
