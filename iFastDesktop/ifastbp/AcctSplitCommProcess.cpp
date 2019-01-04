//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Canada, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2001 by DST Canada, Inc.
//
//******************************************************************************
//
// ^FILE   : AcctSplitCommProcess.cpp
// ^AUTHOR : 
// ^DATE   : Aug 23, 2001
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : AcctSplitCommProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include <ifastcbo\acctsplitcomm.hpp>
#include <ifastcbo\acctsplitcommlist.hpp>
#include <ifastcbo\acctsplitcommreplist.hpp>
#include <ifastcbo\acctsplitcommrep.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\remarkslist.hpp>
#include <ifastcbo\shareholder.hpp>

#include "acctsplitcommprocess.hpp"
#include "acctsplitcommprocessincludes.h"
#include "nasuprocessincludes.h"

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_ACCT_SPLITCOMM;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ACCT_SPLITCOMM;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< AcctSplitCommProcess > processCreator( CMD_BPROC_ACCT_SPLITCOMM );

namespace
{
   const I_CHAR * const CLASSNAME                     = I_( "AcctSplitCommProcess" );
   const I_CHAR * const YES = I_( "Y" );
   const I_CHAR * const NO = I_( "N" );
}

namespace ACCTSPLIT
{
   const I_CHAR * const ACCOUNT_NUM                   = I_( "AccountNum" );
   const I_CHAR * const SHR_NUM                       = I_( "ShrNum" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
}

//******************************************************************************
// Constructor
//******************************************************************************

AcctSplitCommProcess::AcctSplitCommProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _dstrAccountNum(NULL_STRING)
, _dstrCreatingAcct(NULL_STRING)
, _dstrCreatingShr(NULL_STRING)
, m_rpChildGI( 0 )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   addContainer( IFASTBP_PROC::ACCT_SPLITCOMM_DATE_LIST, true, BF::NullContainerId,                    true, I_("AccountSplitCommDate"));
   addContainer( IFASTBP_PROC::ACCT_SPLITCOMM_REP_LIST,  true, IFASTBP_PROC::ACCT_SPLITCOMM_DATE_LIST, true, I_("AccountSplitComm"));
   addSubstituteList ( ifds::CommEntType );
   addSubstituteList ( ifds::TradesPayType );
   addSubstituteList ( ifds::GrossOrNet );

   addFieldDetails( ifds::Active,                  IFASTBP_PROC::ACCT_SPLITCOMM_DATE_LIST );   
   addFieldDetails( ifds::EffectiveDate,           IFASTBP_PROC::ACCT_SPLITCOMM_DATE_LIST );
   addFieldDetails( ifds::StopDate,                IFASTBP_PROC::ACCT_SPLITCOMM_DATE_LIST );
   addFieldDetails( ACCTSPLIT::TOTAL_RENUNCIATION, IFASTBP_PROC::ACCT_SPLITCOMM_DATE_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ACCTSPLIT::NEWITEM,            IFASTBP_PROC::ACCT_SPLITCOMM_DATE_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::CommLevel,               IFASTBP_PROC::ACCT_SPLITCOMM_REP_LIST );
   addFieldDetails( ifds::CommEntType,             IFASTBP_PROC::ACCT_SPLITCOMM_REP_LIST );
   addFieldDetails( ifds::GrossOrNet,              IFASTBP_PROC::ACCT_SPLITCOMM_REP_LIST );
   addFieldDetails( ifds::TradesPayType,           IFASTBP_PROC::ACCT_SPLITCOMM_REP_LIST );
   addFieldDetails( ifds::CommPrcnt,               IFASTBP_PROC::ACCT_SPLITCOMM_REP_LIST );
   addFieldDetails( ifds::EffectiveDate,           IFASTBP_PROC::ACCT_SPLITCOMM_REP_LIST );
   addFieldDetails( ifds::StopDate,                IFASTBP_PROC::ACCT_SPLITCOMM_REP_LIST );
   addFieldDetails( ifds::AgencyCode,              IFASTBP_PROC::ACCT_SPLITCOMM_REP_LIST );
   addFieldDetails( ifds::BranchCode,              IFASTBP_PROC::ACCT_SPLITCOMM_REP_LIST );
   addFieldDetails( ifds::AgentCode,               IFASTBP_PROC::ACCT_SPLITCOMM_REP_LIST );
   addFieldDetails( ifds::EntityName,              IFASTBP_PROC::ACCT_SPLITCOMM_REP_LIST );
   addFieldDetails( ifds::CommLevelDesc,           IFASTBP_PROC::ACCT_SPLITCOMM_REP_LIST );   
   addFieldDetails( ifds::BrokerName,              IFASTBP_PROC::ACCT_SPLITCOMM_REP_LIST );   
   addFieldDetails( ifds::BranchName,              IFASTBP_PROC::ACCT_SPLITCOMM_REP_LIST );   
   addFieldDetails( ifds::SlsrepName,              IFASTBP_PROC::ACCT_SPLITCOMM_REP_LIST );   
}

//******************************************************************************
// Destructor
//******************************************************************************

AcctSplitCommProcess::~AcctSplitCommProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
// Process Initialization.  Account and Shareholder number is required.
//******************************************************************************

SEVERITY AcctSplitCommProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = NO_CONDITION;

   getParameter( ACCTSPLIT::ACCOUNT_NUM, _dstrAccountNum );   
   getParameter( NASULIT::CREATING_ACCOUNT, _dstrCreatingAcct );
   getParameter( NASULIT::CREATING_SHAREHOLDER, _dstrCreatingShr );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
// Dialog creation.
//******************************************************************************

E_COMMANDRETURN AcctSplitCommProcess::doProcess()
{  
   MAKEFRAME2( CND::IFASTBP_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      if( !isXMLAPIContext() )
      {
         DString dstrShrNum;
         MFAccount *pMFAccount;
         const BFDataGroupId& idDataGroup = getDataGroupId();
         setParameter ( ACCTSPLIT::ACCOUNT_NUM, _dstrAccountNum );
         DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
         if( dstcWorkSession->getMFAccount( idDataGroup, _dstrAccountNum, pMFAccount) <= WARNING && pMFAccount )
         {
            pMFAccount->getField ( ifds::ShrNum, dstrShrNum, idDataGroup );
         }
         dstrShrNum.stripLeading (I_CHAR('0'));
         setParameter ( ACCTSPLIT::SHR_NUM, dstrShrNum );
         setParameter( NASULIT::CREATING_ACCOUNT, _dstrCreatingAcct );
         setParameter( NASULIT::CREATING_SHAREHOLDER, _dstrCreatingShr );
         rtn = invokeCommand( this, CMD_GUI_ACCT_SPLITCOMM, getProcessType(), isModal(), &m_rpChildGI );
      }
      else
      {
         rtn = CMD_MODELESS_INPROCESS;
      }
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
// Refreshes the modeless Dialog.
// @param   GenericInterface *rpGICaller - Pointer to the Dialog.
//******************************************************************************

bool AcctSplitCommProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );

   bool bRtn = false;
   try
   {
      assert( m_rpChildGI && isValidModelessInterface( m_rpChildGI ) );

      if( isValidModelessInterface( m_rpChildGI ) )
      {  // Only if child still exists
         bRtn = m_rpChildGI->refresh( this, NULL );
         bRtn = m_rpChildGI->modelessSetFocus( rpGICaller );
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
// Notifies the parent YTD Dialog is completed
//******************************************************************************

bool AcctSplitCommProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_ACCT_SPLITCOMM );
}

//******************************************************************************
// Sets up the container if it hasn't been setup yet.
// @param   const BFContainerId& idContainer - The requested Container.
// @param   const BFDataGroupId& idDataGroup - The group the container belongs to.
//******************************************************************************

void *AcctSplitCommProcess::getPtrForContainer(
                                              const BFContainerId& idContainer,
                                              const BFDataGroupId& idDataGroup
                                              )
{
   void *ptr = NULL;
   SEVERITY sevRtn = NO_CONDITION;

   DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   MFAccount      * pMFAccount      = NULL;

   try
   {
      // RSP Contribution List
      if( IFASTBP_PROC::ACCT_SPLITCOMM_DATE_LIST == idContainer )
      {
         {
            // Get MFAccount CBO
            if( dstcWorkSession->getMFAccount( idDataGroup, _dstrAccountNum, pMFAccount) <= WARNING && pMFAccount )
            {
               AcctSplitCommList *pAcctSplitCommList;
               // Retrieve Account Level Split Commission Date List.
               if( pMFAccount->getAcctSplitCommList( pAcctSplitCommList, idDataGroup) <= WARNING && pAcctSplitCommList )
               {
                  ptr = pAcctSplitCommList;                  
               }
            }
         }
         // RSP Receipts List
      }
      else if( IFASTBP_PROC::ACCT_SPLITCOMM_REP_LIST == idContainer )
      {
         {
            // Retrieve the current Split Commission Date CBO
            AcctSplitComm *pAcctSplitComm = dynamic_cast< AcctSplitComm * >( getCBOItem( IFASTBP_PROC::ACCT_SPLITCOMM_DATE_LIST, idDataGroup ) );
            if( pAcctSplitComm )
            {
               AcctSplitCommRepList *pAccctSplitCommRepList;
               // Retrieve the Split Commission REP List based on the current Split Commission Date CBO
               if( pAcctSplitComm->getAcctSplitCommRepList ( pAccctSplitCommRepList, idDataGroup ) <= WARNING && pAccctSplitCommRepList )
               {
                  ptr = pAccctSplitCommRepList;
               }
            }
         }

      }
      else
      {
         assert(0);
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
// Override for getField.  Name is override for special formatting based on the
// market.
// @param   const GenericInterface *rpGICaller - Pointer to the Dialog
// @param   const BFContainerId& idContainer - Container where the Field can be found.
// @param   const BFFieldId& idField - The Field to override.
// @param   const BFDataGroupId& idDataGroup - The group the Field belongs to.
// @param   DString &strValueOut - The value returned.
// @param   bool bFormatted - True for DataDictionary formatting.
//******************************************************************************

void AcctSplitCommProcess::doGetField( const GenericInterface *rpGICaller,
                                       const BFContainerId& idContainer,
                                       const BFFieldId& idField,
                                       const BFDataGroupId& idDataGroup,
                                       DString &strValueOut,
                                       bool bFormatted ) const
{
   if( idContainer == IFASTBP_PROC::ACCT_SPLITCOMM_DATE_LIST )
   {
      if( idField == ACCTSPLIT::NEWITEM )
      {
         AcctSplitComm *pAcctSplitComm = dynamic_cast < AcctSplitComm * >( const_cast <AcctSplitCommProcess*> (this)->getCBOItem( IFASTBP_PROC::ACCT_SPLITCOMM_DATE_LIST, idDataGroup ) );
         if( pAcctSplitComm->isNew() )
            strValueOut = YES;
         else
            strValueOut = NO;
      }
      else if( idField == ACCTSPLIT::TOTAL_RENUNCIATION )
      {
         AcctSplitComm *pAcctSplitComm = dynamic_cast < AcctSplitComm * >( const_cast <AcctSplitCommProcess*> (this)->getCBOItem( IFASTBP_PROC::ACCT_SPLITCOMM_DATE_LIST, idDataGroup ) );
         AcctSplitCommRepList *pAcctSplitCommRepList;
         if( pAcctSplitComm->getAcctSplitCommRepList ( pAcctSplitCommRepList, idDataGroup ) <= WARNING && pAcctSplitCommRepList )
         {
            strValueOut = pAcctSplitCommRepList->getTotalRenunciation( idDataGroup );
         }
      }
   }
}

bool AcctSplitCommProcess::doOk( GenericInterface* rpGICaller )
{
   const BFDataGroupId& idDataGroup = getDataGroupId();
   MFAccount* pMFAccount      = NULL;
   DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   if(dstcWorkSession && dstcWorkSession->getMFAccount( idDataGroup, _dstrAccountNum, pMFAccount) <= WARNING && pMFAccount )
   {
      pMFAccount->refreshMe (true);
   }

   return(true);
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AcctSplitCommProcess.cpp-arc  $
// 
//    Rev 1.15   Jul 20 2012 14:26:10   dchatcha
// IN# 2994672 - Block Service Unit Transfers, simplified logic that let account cbo update b\b\s
// 
//    Rev 1.14   May 21 2012 14:12:34   dchatcha
// P0186479 FN10 -Gap 14G - Block Service Unit Transfers, revise code.
// 
//    Rev 1.13   May 18 2012 15:27:08   dchatcha
// P0186479 FN10 -Gap 14G - Block Service Unit Transfers, revise code.
// 
//    Rev 1.12   May 14 2012 15:53:20   dchatcha
// P0186479 FN10 -Gap 14G - Block Service Unit Transfers.
// 
//    Rev 1.11   Apr 02 2003 12:19:28   PURDYECH
// Code cleanup
// 
//    Rev 1.10   Mar 21 2003 17:35:06   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.9   Oct 09 2002 23:53:00   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.8   Aug 29 2002 16:42:32   SMITHDAV
// Condition split.
// 
//    Rev 1.7   Aug 29 2002 12:54:10   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.6   Jul 10 2002 16:42:54   FENGYONG
// Add names for api
// 
//    Rev 1.5   22 May 2002 18:23:48   PURDYECH
// BFData Implementation
// 
//    Rev 1.4   27 Mar 2002 19:54:30   PURDYECH
// Process/WindowFactory overhaul
// 
//    Rev 1.3   23 Nov 2001 11:02:50   HSUCHIN
// passing NASU params to dialog
// 
//    Rev 1.2   25 Sep 2001 12:16:34   HSUCHIN
// fix to pass shareholder number to dialog so that the title bar can be set up properly
// 
//    Rev 1.1   29 Aug 2001 16:12:26   HSUCHIN
// added enhancements and missing implementations
// 
//    Rev 1.0   23 Aug 2001 14:50:42   HSUCHIN
// Initial revision.
 */

