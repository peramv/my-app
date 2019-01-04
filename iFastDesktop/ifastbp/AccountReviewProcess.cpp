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
// ^FILE   : AccountReviewProcess.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : AccountReviewProcess
//    This class manages the Account Review information.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "accountreviewprocess.hpp"
#include <ifastdataimpl\dse_dstcglob_vw.hpp>
#include <ifastcbo\mfaccount.hpp>
#include "mfcaninterprocparam.hpp"
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\mgmtcooptions.hpp>
#include <ifastcbo\accountreviewlist.hpp>
#include <ifastcbo\accountreview.hpp>
#include "accountreviewprocessincludes.h"
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_ACCOUNTREVIEW;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ACCOUNTREVIEW;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< AccountReviewProcess > processCreator( CMD_BPROC_ACCOUNTREVIEW );

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME = I_( "AccountReviewProcess" );
   const I_CHAR * const PERFORMSEARCH = I_( "performSearch" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace ACCOUNTREVIEWLITERALS
{
   const I_CHAR * const ACCOUNT_NUM        = I_( "AccountNum" );
   const I_CHAR * const SHAREHOLDER_NUMBER = I_( "ShrNum" );
   const I_CHAR * const NAME               = I_( "Name" );
}

//******************************************************************************
//              Public Methods
//******************************************************************************

AccountReviewProcess::AccountReviewProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, m_rpChildGI( NULL )
, m_pAccountReviewList(NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::ACCOUNTREVIEW_LIST, true, BF::NullContainerId, true );

   addFieldDetails( ifds::AcctReviewRId,    IFASTBP_PROC::ACCOUNTREVIEW_LIST );
   addFieldDetails( ifds::SchedReviewDate,  IFASTBP_PROC::ACCOUNTREVIEW_LIST );
   addFieldDetails( ifds::ActualReviewDate, IFASTBP_PROC::ACCOUNTREVIEW_LIST );
   addFieldDetails( ifds::Comments1,        IFASTBP_PROC::ACCOUNTREVIEW_LIST );
   addFieldDetails( ifds::Comments2,        IFASTBP_PROC::ACCOUNTREVIEW_LIST );
   addFieldDetails( ifds::Comments3,        IFASTBP_PROC::ACCOUNTREVIEW_LIST );
   addFieldDetails( ifds::Overriden,        IFASTBP_PROC::ACCOUNTREVIEW_LIST );
   addFieldDetails( ifds::ProcessDate,      IFASTBP_PROC::ACCOUNTREVIEW_LIST );
   addFieldDetails( ifds::Username,         IFASTBP_PROC::ACCOUNTREVIEW_LIST );
   addFieldDetails( ifds::ModDate,          IFASTBP_PROC::ACCOUNTREVIEW_LIST );
   addFieldDetails( ifds::ModUser,          IFASTBP_PROC::ACCOUNTREVIEW_LIST );

   addFieldDetails( ifds::AccountNum,       BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails( ifds::ShrNum,           BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails( ifds::CurrBusDate,      BF::NullContainerId, SUBCLASS_PROCESS);
}

//******************************************************************************

AccountReviewProcess::~AccountReviewProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   m_rpChildGI = NULL;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

void AccountReviewProcess::doGetField( const GenericInterface *rpGICaller,
                                       const BFContainerId& idContainer,
                                       const BFFieldId& idField,
                                       const BFDataGroupId& idDataGroup,
                                       DString &strValueOut,
                                       bool bFormatted ) const
{
   if( idField == ifds::CurrBusDate )
   {
      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      dstcWorkSession->getMgmtCoOptions()->getField(idField, strValueOut, getDataGroupId(), bFormatted );
   }
   else if( idField == ifds::AccountNum )
   {
      strValueOut = m_dstrAccountNumber;
   }
   else if( idField == ifds::ShrNum )
   {
      strValueOut = m_dstrShrNum;
   }
}

//******************************************************************************

SEVERITY AccountReviewProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOINIT );

   getParameter( ACCOUNTREVIEWLITERALS::ACCOUNT_NUM,        m_dstrAccountNumber );
   getParameter( ACCOUNTREVIEWLITERALS::SHAREHOLDER_NUMBER, m_dstrShrNum );

   SEVERITY sevRtn = NO_CONDITION;
   MFAccount* mfAccount;
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   if( dstcWorkSession->getMFAccount( getDataGroupId(), m_dstrAccountNumber, mfAccount ) <= WARNING )
   {
      if( mfAccount->getAccountReviewList( m_pAccountReviewList, getDataGroupId()) <= WARNING )
      {
         setContainer( IFASTBP_PROC::ACCOUNTREVIEW_LIST, m_pAccountReviewList );
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

bool AccountReviewProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_ACCOUNTREVIEW );
}

//******************************************************************************

bool AccountReviewProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );
   DString dstrNewAccountNumber;
   bool bRtn = false;

   try
   {
      assert( m_rpChildGI && isValidModelessInterface( m_rpChildGI ) );

      getParameter( ACCOUNTREVIEWLITERALS::ACCOUNT_NUM, dstrNewAccountNumber );
      if( dstrNewAccountNumber != m_dstrAccountNumber )
      {
         m_dstrAccountNumber = dstrNewAccountNumber;
         setContainer( IFASTBP_PROC::ACCOUNTREVIEW_LIST, NULL );
         if( isValidModelessInterface( m_rpChildGI ) )
         {  // Only if child still exists
            bRtn = m_rpChildGI->refresh( this, NULL );
         }
      }

      if( isValidModelessInterface( m_rpChildGI ) )
      {  // Only if child still exists
         bRtn = m_rpChildGI->modelessSetFocus( rpGICaller );
      }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(bRtn);
}

//******************************************************************************

E_COMMANDRETURN AccountReviewProcess::doProcess()
{  
   MAKEFRAME2( CND::IFASTBP_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter( ACCOUNTREVIEWLITERALS::ACCOUNT_NUM,        m_dstrAccountNumber );
      setParameter( ACCOUNTREVIEWLITERALS::SHAREHOLDER_NUMBER, m_dstrShrNum );

      rtn = invokeCommand( this, CMD_GUI_ACCOUNTREVIEW, getProcessType(), isModal(), &m_rpChildGI );
   }
   catch( ConditionException &ce )
   {
      assert( 0 );
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(rtn);
}

//******************************************************************************

bool AccountReviewProcess::doOk( GenericInterface *rpGICaller )
{
   return(true);
}

//******************************************************************************
void *AccountReviewProcess::getPtrForContainer( const BFContainerId& idContainer,
                                                const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, I_( "getPtrForContainer" ) );
   void *ptr = NULL;
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   try
   {
      if( IFASTBP_PROC::ACCOUNTREVIEW_LIST == idContainer )
      {
         {
            MFAccount   *rpMFAccount;
            AccountReviewList *rpAccountReviewList;

            if( dstcWorkSession->getMFAccount( idDataGroup, m_dstrAccountNumber, rpMFAccount ) <= WARNING )
            {
               if( rpMFAccount->getAccountReviewList( rpAccountReviewList, idDataGroup ) <= WARNING )
               {
                  ptr = rpAccountReviewList;
               }
            }
         }
      }
      else
      {
      }
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(ptr);
}

//******************************************************************************
SEVERITY AccountReviewProcess::performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, E_SEARCHACTION eSearchAction )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, PERFORMSEARCH );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      if( m_pAccountReviewList != NULL )
      {
         sevRtn = m_pAccountReviewList->getMore();
      }
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
   return(sevRtn); 
}

//******************************************************************************

bool AccountReviewProcess::doMoreRecordsExist( GenericInterface *rpGICaller,  const BFContainerId& idSearch )
{
   return( rpGICaller == NULL || m_pAccountReviewList == NULL ) ? false : m_pAccountReviewList->doMoreRecordsExist();
}

//******************************************************************************

SEVERITY AccountReviewProcess::doValidateAll(BFAbstractCBO *rpWSD, const BFDataGroupId& idDataGroup)
{
   return(m_pAccountReviewList->validateAll( idDataGroup ));
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AccountReviewProcess.cpp-arc  $
// 
//    Rev 1.10   Mar 17 2005 14:12:20   aguilaam
// IN_234826: display shrnum, acctnum, entity owner name on acctreview screen
// 
//    Rev 1.9   Apr 02 2003 12:19:16   PURDYECH
// Code cleanup
// 
//    Rev 1.8   Mar 21 2003 17:34:36   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.7   Oct 09 2002 23:52:58   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.6   Aug 29 2002 16:42:32   SMITHDAV
// Condition split.
// 
//    Rev 1.5   Aug 29 2002 12:54:10   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.4   Jun 20 2002 19:22:34   HERNANDO
// Uncommented lines pertaining to getAccountReviewList call.  This code was initially commented out for the BFData Implementation.
// 
//    Rev 1.3   Jun 03 2002 16:55:16   HSUCHIN
// bug fix to doValidateAll to use BFAbstractCBO rather than BFCBO
// 
//    Rev 1.2   31 May 2002 13:48:26   HERNANDO
// Revised for Rel47.
// 
//    Rev 1.1   22 May 2002 18:23:46   PURDYECH
// BFData Implementation
// 
//    Rev 1.0   08 May 2002 18:11:16   HERNANDO
// Initial revision.
 * 
 */
