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
// ^FILE   : HistoricalShareholderProcess.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : HistoricalShareholderProcess
//    This class manages the Historical information.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "HistoricalShareholderProcess.hpp"
#include <ifastcbo\historicalshareholderlist.hpp>
#include "HistoricalShareholderProcessincludes.h"
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_HISTORICAL_SHAREHOLDER;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_HISTORICAL_SHAREHOLDER;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< HistoricalShareholderProcess > processCreator( CMD_BPROC_HISTORICAL_SHAREHOLDER );

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "HistoricalShareholderProcess" );
   const I_CHAR * const NAME = I_( "Name" );
   const I_CHAR * const SHAREHOLDER_NUMBER = I_("ShareholderNumber");
}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

HistoricalShareholderProcess::HistoricalShareholderProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, m_pHistoricalShareholderList( 0 ),
m_rpChildGI( 0 )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::HISTORICAL_LIST, true );

   addFieldDetails( ifds::ModDate, IFASTBP_PROC::HISTORICAL_LIST );
   addFieldDetails( ifds::FieldLabel, IFASTBP_PROC::HISTORICAL_LIST );
   addFieldDetails( ifds::PreviousDisp, IFASTBP_PROC::HISTORICAL_LIST );
   addFieldDetails( ifds::ModUser, IFASTBP_PROC::HISTORICAL_LIST );
}

//******************************************************************************

HistoricalShareholderProcess::~HistoricalShareholderProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   delete m_pHistoricalShareholderList;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

void HistoricalShareholderProcess::doGetField(
                                         const GenericInterface *rpGICaller,
                                         const BFContainerId& idContainer,
                                         const BFFieldId& idField,
                                         const BFDataGroupId& idDataGroup,
                                         DString &strValueOut,
                                         bool bFormatted
                                         ) const
{
}

//******************************************************************************

SEVERITY HistoricalShareholderProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      DString dstrShareholderNumber, dstrName;
      getParameter( SHAREHOLDER_NUMBER, dstrShareholderNumber );
      dstrShareholderNumber = dstrShareholderNumber.stripAll();
      getParameter( NAME, m_dstrName );
      m_pHistoricalShareholderList = new HistoricalShareholderList( *getBFWorkSession() );
      sevRtn = m_pHistoricalShareholderList->init( dstrShareholderNumber );
      if( WARNING >= sevRtn )
      {  
         setContainer( IFASTBP_PROC::HISTORICAL_LIST, m_pHistoricalShareholderList );
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

E_COMMANDRETURN HistoricalShareholderProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   setParameter( NAME, m_dstrName );
   setParameter( SHAREHOLDER_NUMBER, m_dstrShareholderNumber );

   try
   {
      rtn = invokeCommand( this, CMD_GUI_HISTORICAL_SHAREHOLDER, 
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

bool HistoricalShareholderProcess::doModelessSetFocus(
                                                 GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );
   SEVERITY sevRtn = SEVERE_ERROR;
   bool bRtn = false;
   try
   {
      assert( m_rpChildGI && isValidModelessInterface( m_rpChildGI ) );

      DString dstrNewShareholderNumber;
      DString dstrShareholderNumber;
      DString dstrName;
      getParameter( SHAREHOLDER_NUMBER, dstrNewShareholderNumber );
      setParameter( SHAREHOLDER_NUMBER, dstrNewShareholderNumber );
      getParameter( NAME, dstrName );
      setParameter( NAME, dstrName );
      if( dstrNewShareholderNumber != m_dstrShareholderNumber )
      {
         delete m_pHistoricalShareholderList;
         m_dstrShareholderNumber = dstrNewShareholderNumber.stripAll();
         m_pHistoricalShareholderList = new HistoricalShareholderList( *getBFWorkSession() );
         sevRtn = m_pHistoricalShareholderList->init( m_dstrShareholderNumber );
         if( WARNING >= sevRtn )
         {
            setContainer( IFASTBP_PROC::HISTORICAL_LIST, m_pHistoricalShareholderList );
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

bool HistoricalShareholderProcess::doModelessChildComplete(const Command &cmd)
{
   // End when GUI ends   
   return( cmd.getKey() == CMD_GUI_HISTORICAL_SHAREHOLDER );
}

//******************************************************************************

bool HistoricalShareholderProcess::doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch )
{
   return( rpGICaller == NULL || m_pHistoricalShareholderList == NULL ? false : 
           m_pHistoricalShareholderList->moreRecordsExist() );
}

//******************************************************************************

SEVERITY HistoricalShareholderProcess::performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, 
                                                  E_SEARCHACTION eSearchAction )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "doMore" ));
   DString NextKey;
   SEVERITY severity = SEVERE_ERROR;

   try
   {
      if( m_pHistoricalShareholderList != NULL && rpGI != NULL )
      {
         severity = m_pHistoricalShareholderList->search( eSearchAction == SEARCH_START );
         if( WARNING >= severity )
         {
            setContainer( IFASTBP_PROC::HISTORICAL_LIST, m_pHistoricalShareholderList );
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
//*******************************************************************************

bool HistoricalShareholderProcess::doRefresh(
                                            GenericInterface *rpGICaller,
                                            const I_CHAR *szOriginalCommand
                                            )
{
   setParameter( NAME, m_dstrName );
   setParameter( SHAREHOLDER_NUMBER, m_dstrShareholderNumber );
   return( m_rpChildGI->refresh( this, I_( "FullRefresh" ) ) );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/HistoricalShareholderProcess.cpp-arc  $
// 
//    Rev 1.0   Feb 06 2004 14:52:24   HERNANDO
// Initial revision.
 */
