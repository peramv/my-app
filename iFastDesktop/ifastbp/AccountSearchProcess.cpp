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
// ^FILE   : AccountSearchProcess.cpp
// ^AUTHOR : Yongmei Feng
// ^DATE   : 01/11/1999
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : AccountSearchProcess
//    This class manages the management company and profile selection.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "accountsearchprocess.hpp"
#include <ifastcbo\accountsearchlist.hpp>
#include "accountsearchprocessincludes.h"
#include <ifastcbo\mfaccount.hpp>
#include "etrackheader.h"
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ACCOUNT_SEARCH;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< AccountSearchProcess > processCreator( CMD_BPROC_ACCOUNT_SEARCH );

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "AccountSearchProcess" );
   const I_CHAR * const OVERRIDEREPEATS = I_( "Overriderepeats" );

   const I_CHAR * const SRCHALTACCT = I_( "AltAccountNum" );
   const I_CHAR * const SRCHBROKER = I_( "BrokerCode" );
   const I_CHAR * const NEXTORPREVIOUS = I_( "NextOrPrevious" );
   const I_CHAR * const ONEACCTONLY = I_( "OneAcctOnly" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern const long BP_ERR_DATA_NOT_FOUND;
}


//******************************************************************************
//              Public Methods
//******************************************************************************

AccountSearchProcess::AccountSearchProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI(NULL)  
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::ACCOUNT_SEARCH_LIST, true, BF::NullContainerId, false, I_( "Account" ) );

   addFieldDetails( ifds::AccountNum, IFASTBP_PROC::ACCOUNT_SEARCH_LIST );
}

//******************************************************************************

AccountSearchProcess::~AccountSearchProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   if( _pAccountSearchList ) delete _pAccountSearchList;
   _pAccountSearchList = NULL;
   _rpChildGI = NULL;   
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY AccountSearchProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;
   DString NextOrPrevious;
   try
   {

      DString overrideRepeats;

      getParameter( SRCHALTACCT, _SrchAltAcct );
      getParameter( SRCHBROKER, _SrchBrokerCode );
      getParameter( ONEACCTONLY, _OneAcctOnly );

      if( _OneAcctOnly == NULL_STRING ) _OneAcctOnly = I_("N");

      DString dstrTrack,dstrActivity;
      getParameter( ETRACK::TRACK, dstrTrack );
      getParameter( ETRACK::ACTIVITY, dstrActivity );
      if( dstrTrack.strip() == NULL_STRING ) dstrTrack = I_("N");
      getParameter( NEXTORPREVIOUS, NextOrPrevious );
      if( NextOrPrevious == NULL_STRING ) NextOrPrevious = I_("Y");

      _pAccountSearchList = new AccountSearchList( *getBFWorkSession() );

      //get first 25 records
      sevRtn = _pAccountSearchList->init( _SrchAltAcct, _SrchBrokerCode,_OneAcctOnly, 
                                          dstrTrack,dstrActivity, overrideRepeats,NextOrPrevious );
      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::ACCOUNT_SEARCH_LIST, _pAccountSearchList );
      }
      else return(GETCURRENTHIGHESTSEVERITY());
      if( bfutil::isServerContext() )
      {
         BFObjIter bfIter( *_pAccountSearchList, getDataGroupId(), false, BFObjIter::ITERTYPE::NON_DELETED );
         if( bfIter.getNumberOfItemsInList() == 0 )
         {
            THROWFROMFILE2( CND::IFASTBP_CONDITION, CLASSNAME, DOINIT,CND::BP_ERR_DATA_NOT_FOUND );
         }
      }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
      throw;
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

bool AccountSearchProcess::doMoreRecordsExist( GenericInterface *rpGICaller,
                                               const BFContainerId& idContainer )
{
   return( _pAccountSearchList->doMoreRecordsExist() );
}

//******************************************************************************

bool AccountSearchProcess::doGetData( GenericInterface * ,
                                      BFData * ) const
{
   return(true);
}
//******************************************************************************

E_COMMANDRETURN AccountSearchProcess::doProcess()
{  
   E_COMMANDRETURN rtn = CMD_FAILURE;

   rtn = CMD_MODELESS_INPROCESS;

   return(rtn);
}

void AccountSearchProcess::setCurrentListItem( const GenericInterface *rpGICaller,
                                               const BFContainerId& idList,
                                               const DString& strListItemKey )
{
   AbstractProcess::setCurrentListItem( rpGICaller, idList, strListItemKey );
}

void AccountSearchProcess::doGetField( const GenericInterface *rpGICaller,
                                       const BFContainerId& idContainer,
                                       const BFFieldId& idField,
                                       const BFDataGroupId& idDataGroup, 
                                       DString &strValueOut,
                                       bool bFormatted ) const
{  
}
//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AccountSearchProcess.cpp-arc  $
// 
//    Rev 1.9   Apr 02 2003 12:19:18   PURDYECH
// Code cleanup
// 
//    Rev 1.8   Mar 21 2003 17:34:44   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.7   Oct 09 2002 23:52:58   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.6   Sep 04 2002 15:45:42   PURDYECH
// Condition, comment and formatting cleanup
// 
//    Rev 1.5   Aug 29 2002 16:42:32   SMITHDAV
// Condition split.
// 
//    Rev 1.4   Aug 29 2002 12:54:10   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.3   22 May 2002 18:23:46   PURDYECH
// BFData Implementation
// 
//    Rev 1.2   27 Mar 2002 19:54:28   PURDYECH
// Process/WindowFactory overhaul
// 
//    Rev 1.1   Feb 07 2002 16:52:22   FENGYONG
// Add no date found cnd
 * 
 */
