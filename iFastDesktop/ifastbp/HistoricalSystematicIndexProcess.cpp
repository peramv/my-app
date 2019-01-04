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
// ^FILE   : HistoricalSystematicIndexProcess.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : HistoricalSystematicIndexProcess
//    This class manages the Historical Systematic Index information.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "historicalsystematicindexprocess.hpp"
#include <ifastcbo\historicalsystematicindexlist.hpp>
#include "historicalsystematicindexprocessincludes.h"
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_HISTORICAL_SYS_INDEX;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_HISTORICAL_SYS_INDEX;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< HistoricalSystematicIndexProcess > processCreator( CMD_BPROC_HISTORICAL_SYS_INDEX );

namespace HISTSYSINDEX
{
   const I_CHAR * const PARM_TRANSACTIONNUMBER = I_( "TRANSACTIONNUMBER" );
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME         = I_( "HistoricalSystematicIndexProcess" );
}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319HistoricalSystematicIndexProcess::HistoricalSystematicIndexProcess() : 
HistoricalSystematicIndexProcess::HistoricalSystematicIndexProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, m_pHistoricalSystematicIndexList( 0 ),
m_rpChildGI( 0 ),
m_dstrTransactionNumber( NULL_STRING )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::HISTORICAL_SYSTEMATIC_INDEX_LIST, true );

   addFieldDetails( ifds::ModDate, IFASTBP_PROC::HISTORICAL_SYSTEMATIC_INDEX_LIST );
   addFieldDetails( ifds::FieldLabel, IFASTBP_PROC::HISTORICAL_SYSTEMATIC_INDEX_LIST );
   addFieldDetails( ifds::OldValue, IFASTBP_PROC::HISTORICAL_SYSTEMATIC_INDEX_LIST );
   addFieldDetails( ifds::NewValue, IFASTBP_PROC::HISTORICAL_SYSTEMATIC_INDEX_LIST );
}

//******************************************************************************

HistoricalSystematicIndexProcess::~HistoricalSystematicIndexProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   delete m_pHistoricalSystematicIndexList;
   m_pHistoricalSystematicIndexList = NULL;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY HistoricalSystematicIndexProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      getParameter( HISTSYSINDEX::PARM_TRANSACTIONNUMBER, m_dstrTransactionNumber );
      m_dstrTransactionNumber.stripAll().stripLeading( I_CHAR( '0' ) );

      m_pHistoricalSystematicIndexList = new HistoricalSystematicIndexList( *getBFWorkSession() );
      sevRtn = m_pHistoricalSystematicIndexList->init( m_dstrTransactionNumber );
      if( WARNING >= sevRtn )
      {  //register list with base
         setContainer( IFASTBP_PROC::HISTORICAL_SYSTEMATIC_INDEX_LIST, m_pHistoricalSystematicIndexList );
      }
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

E_COMMANDRETURN HistoricalSystematicIndexProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      rtn = invokeCommand( this, CMD_GUI_HISTORICAL_SYS_INDEX,
                           getProcessType(), isModal(), &m_rpChildGI );
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

bool HistoricalSystematicIndexProcess::doModelessSetFocus(
                                                         GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );
   SEVERITY sevRtn = SEVERE_ERROR;
   bool bRtn = false;
   try
   {
      assert( m_rpChildGI && isValidModelessInterface( m_rpChildGI ) );

      DString dstrNewTransactionNumber;
      getParameter( HISTSYSINDEX::PARM_TRANSACTIONNUMBER, dstrNewTransactionNumber );
      if( dstrNewTransactionNumber != m_dstrTransactionNumber )
      {
         delete m_pHistoricalSystematicIndexList;
         m_dstrTransactionNumber = dstrNewTransactionNumber.stripAll().stripLeading( I_CHAR ('0') );
         m_pHistoricalSystematicIndexList = new HistoricalSystematicIndexList( *getBFWorkSession() );
         sevRtn = m_pHistoricalSystematicIndexList->init( m_dstrTransactionNumber );
         if( WARNING >= sevRtn )
         {  //register list with base
            setContainer( IFASTBP_PROC::HISTORICAL_SYSTEMATIC_INDEX_LIST, m_pHistoricalSystematicIndexList );
         }
         bRtn = m_rpChildGI->refresh( this, I_( "FullRefresh" ) );
      }
      else
      {
         if( !( bRtn = m_rpChildGI->refresh( this, I_( "PartialRefresh" ) ) ) )
         {
            return(bRtn);  // false
         }
      }

      bRtn = m_rpChildGI->modelessSetFocus( rpGICaller );
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
   return(bRtn);
}

//******************************************************************************

bool HistoricalSystematicIndexProcess::doModelessChildComplete(const Command &cmd)
{
   // End when GUI ends   
   return( cmd.getKey() == CMD_GUI_HISTORICAL_SYS_INDEX );
}

//******************************************************************************

bool HistoricalSystematicIndexProcess::doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch )
{
   return(rpGICaller == NULL || m_pHistoricalSystematicIndexList == NULL ? false : 
          m_pHistoricalSystematicIndexList->moreRecordsExist());
}

//******************************************************************************

SEVERITY HistoricalSystematicIndexProcess::performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, 
                                                          E_SEARCHACTION eSearchAction )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "doMore" ));
   SEVERITY severity = SEVERE_ERROR;

   try
   {
      if( m_pHistoricalSystematicIndexList != NULL && rpGI != NULL )
      {
         severity = m_pHistoricalSystematicIndexList->search(eSearchAction == SEARCH_START);
         if( WARNING >= severity )
         {  //register list with base
            setContainer( IFASTBP_PROC::HISTORICAL_SYSTEMATIC_INDEX_LIST, m_pHistoricalSystematicIndexList );
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
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/HistoricalSystematicIndexProcess.cpp-arc  $
// 
//    Rev 1.10   Mar 21 2003 17:41:20   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.9   Oct 09 2002 23:53:18   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.8   Aug 29 2002 16:44:58   SMITHDAV
// Condition split.
// 
//    Rev 1.7   Aug 29 2002 12:54:24   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.6   Jul 05 2002 08:57:34   PURDYECH
// Fixed include files
// Removed commented-out code.
// 
//    Rev 1.5   22 May 2002 18:24:18   PURDYECH
// BFData Implementation
// 
//    Rev 1.4   27 Mar 2002 19:54:56   PURDYECH
// Process/WindowFactory overhaul
// 
//    Rev 1.3   Jun 01 2001 15:18:02   HERNANDO
// Clean up.
// 
//    Rev 1.2   May 24 2001 17:53:44   HERNANDO
// Session management restructuring.
// 
//    Rev 1.1   May 11 2001 12:45:50   HERNANDO
// _
// 
//    Rev 1.0   May 10 2001 14:13:44   HERNANDO
// Initial revision.
 * 
 * 
 */
