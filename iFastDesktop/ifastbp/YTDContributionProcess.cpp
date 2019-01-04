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
// ^FILE   : YTDContributionProcess.cpp
// ^AUTHOR : 
// ^DATE   : 03/08/2001
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : YTDContributionProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include <ifastcbo\accountentityxref.hpp>
#include <ifastcbo\accountmailinglist.hpp>
#include <ifastcbo\accountMailingInfo.hpp>

#include <ifastcbo\address.hpp>
#include <ifastcbo\addresslist.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\rspcontribution.hpp>
#include <ifastcbo\rspcontributionlist.hpp>
#include "ytdcontributionprocess.hpp"
#include "ytdcontributionprocessincludes.h"
#include <ifastcbo\rspreceiptslist.hpp>
#include <ifastcbo\shareholder.hpp>
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_YTD_CONTRIBUTION;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_YTD_CONTRIBUTION;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< YTDContributionProcess > processCreator( CMD_BPROC_YTD_CONTRIBUTION );

namespace
{
   const I_CHAR * const CLASSNAME                     = I_( "YTDContributionProcess" );
   const I_CHAR * const ACCOUNT_OWNER_ENTITY_TYPE     = I_( "01" );
   const I_CHAR * const ACCOUNT_OWNER_SEQ_NUM         = I_( "1" );
   const I_CHAR * const PERFORMSEARCH                 = I_( "performSearch" );
   const I_CHAR * const SPOUSAL_ENTITY_TYPE           = I_( "06" );
   const I_CHAR * const SPOUSAL_ENTITY_SEQ_NUM        = I_( "1" );
   const I_CHAR * const TAX_ADDRESS_CODE              = I_( "12" );   
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION; 
}

namespace YTD
{
   const I_CHAR * const ACCOUNT_NUM                   = I_( "AccountNum" );
   const I_CHAR * const SHR_NUM                       = I_( "ShrNum" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId Name;
}

//******************************************************************************
// Constructor
//******************************************************************************

//CP20030319YTDContributionProcess::YTDContributionProcess() : 
YTDContributionProcess::YTDContributionProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, m_rpChildGI  ( 0 ),
_pRSPReceiptsList (NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::ACCOUNT, false );
   addContainer( IFASTBP_PROC::ACCOUNT_MAILING_LIST, false );

   addContainer( IFASTBP_PROC::RSP_CONTRIBUTION_LIST, true );
   // The RSP Receipts List Container is a child of the RSP Contribution List
   addContainer( IFASTBP_PROC::RSP_RECEIPTS_LIST, true, IFASTBP_PROC::RSP_CONTRIBUTION_LIST );
   addFieldDetails( ifds::ContribYear,  IFASTBP_PROC::RSP_CONTRIBUTION_LIST );
   addFieldDetails( ifds::First60days,  IFASTBP_PROC::RSP_CONTRIBUTION_LIST );
   addFieldDetails( ifds::Remaining,    IFASTBP_PROC::RSP_CONTRIBUTION_LIST );
   addFieldDetails( ifds::RcptNum,      IFASTBP_PROC::RSP_RECEIPTS_LIST );
   addFieldDetails( ifds::Issued,       IFASTBP_PROC::RSP_RECEIPTS_LIST );
   addFieldDetails( ifds::RcptStatus,   IFASTBP_PROC::RSP_RECEIPTS_LIST );
   addFieldDetails( ifds::IssueDate,    IFASTBP_PROC::RSP_RECEIPTS_LIST );
   addFieldDetails( ifds::RcptAmount,   IFASTBP_PROC::RSP_RECEIPTS_LIST );
   addFieldDetails( ifds::Duplicates,   IFASTBP_PROC::RSP_RECEIPTS_LIST );
   addFieldDetails( ifds::RecipientType,IFASTBP_PROC::RSP_RECEIPTS_LIST );
   addFieldDetails( ifds::PrevRcptNo,   IFASTBP_PROC::RSP_RECEIPTS_LIST );
   addFieldDetails( ifds::Name1,        IFASTBP_PROC::RSP_RECEIPTS_LIST );
   addFieldDetails( ifds::SIN,          IFASTBP_PROC::RSP_RECEIPTS_LIST );
   addFieldDetails( ifds::Address1,     IFASTBP_PROC::RSP_RECEIPTS_LIST );
   addFieldDetails( ifds::Address2,     IFASTBP_PROC::RSP_RECEIPTS_LIST );
   addFieldDetails( ifds::Address3,     IFASTBP_PROC::RSP_RECEIPTS_LIST );
   addFieldDetails( ifds::Address4,     IFASTBP_PROC::RSP_RECEIPTS_LIST );
   addFieldDetails( ifds::Address5,     IFASTBP_PROC::RSP_RECEIPTS_LIST );
   addFieldDetails( ifds::PostalCode,   IFASTBP_PROC::RSP_RECEIPTS_LIST );
   addFieldDetails( ifds::CName1,       IFASTBP_PROC::RSP_RECEIPTS_LIST );
   addFieldDetails( ifds::Csin,         IFASTBP_PROC::RSP_RECEIPTS_LIST );
   addFieldDetails( ifds::Caution,      IFASTBP_PROC::RSP_RECEIPTS_LIST );
   addFieldDetails( ifds::ModUser,      IFASTBP_PROC::RSP_RECEIPTS_LIST );
   addFieldDetails( ifds::ModDate,      IFASTBP_PROC::RSP_RECEIPTS_LIST );
   addFieldDetails( ifds::ProcessDate,  IFASTBP_PROC::RSP_RECEIPTS_LIST );
   addFieldDetails( ifds::Username,     IFASTBP_PROC::RSP_RECEIPTS_LIST );


   addFieldDetails( ifds::AccountNum,   IFASTBP_PROC::ACCOUNT );
   addFieldDetails( ifds::Slsrep,       IFASTBP_PROC::ACCOUNT );
   addFieldDetails( ifds::SlsrepName,   IFASTBP_PROC::ACCOUNT );
   addFieldDetails( ifds::AcctType,     IFASTBP_PROC::ACCOUNT );
   addFieldDetails( ifds::PlanType,     IFASTBP_PROC::ACCOUNT );

   addFieldDetails(ifds::ContributionMail,		      IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::ContributionFax,		         IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::ContributionCD,		         IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::ContributionEmail,		      IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::ContributionEpost,		      IFASTBP_PROC::ACCOUNT_MAILING_LIST); 




}

//******************************************************************************
// Destructor
//******************************************************************************

YTDContributionProcess::~YTDContributionProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   // Do not delete since this is taken care of by BFBase
   _pRSPReceiptsList = NULL;
}

//******************************************************************************
// Process Initialization.  Account and Shareholder number is required.
//******************************************************************************

SEVERITY YTDContributionProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = NO_CONDITION;

   getParameter( YTD::ACCOUNT_NUM, _dstrAccountNum );
   getParameter( YTD::SHR_NUM, _dstrShrNum );

   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   const BFDataGroupId& idDataGroup = getDataGroupId();

   Shareholder *pShareholder = NULL;
   _dstrShrNum.strip();
   _dstrAccountNum.strip().stripLeading('0' );
   if( _dstrShrNum != NULL_STRING )
   {
      if( dstcWorkSession->getShareholder( idDataGroup, _dstrShrNum, pShareholder ) <= WARNING )
      {
         AccountMailingList* pAccountMailingList = NULL;

         if( pShareholder->getAccountMailingList( pAccountMailingList, idDataGroup ) <= WARNING )
         {
            
           BFObjIter iter( *pAccountMailingList, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );
           while( !iter.end() )
           {
              DString dstrAccount;
              iter.getObject()->getField(ifds::AccountNum, dstrAccount, idDataGroup,false);
              dstrAccount.strip().stripLeading('0');
              if( dstrAccount == _dstrAccountNum )
              {
                 AccountMailingInfo* pAccountMailingInfo =  dynamic_cast<AccountMailingInfo*>( iter.getObject() );
                 if( pAccountMailingInfo )
                 {                 
                   setContainer (IFASTBP_PROC::ACCOUNT_MAILING_LIST, pAccountMailingInfo);
                   break;
                 }
                 else 
                 {
                    assert( 0 );                 
                 }
              }   
              ++iter;
           }
         }
      }
    }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
// Dialog creation.
//******************************************************************************

E_COMMANDRETURN YTDContributionProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      rtn = invokeCommand( this, CMD_GUI_YTD_CONTRIBUTION, getProcessType(), isModal(), &m_rpChildGI );
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

bool YTDContributionProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );

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

bool YTDContributionProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_YTD_CONTRIBUTION );
}

//******************************************************************************
// Sets up the container if it hasn't been setup yet.
// @param   const BFContainerId& idContainer - The requested Container.
// @param   const BFDataGroupId& idDataGroup - The group the container belongs to.
//******************************************************************************

void *YTDContributionProcess::getPtrForContainer(
                                                const BFContainerId& idContainer,
                                                const BFDataGroupId& idDataGroup
                                                )
{
   void *ptr = NULL;
   SEVERITY sevRtn = NO_CONDITION;
   DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   MFAccount      * pMFAccount      = NULL;
   Entity *pEntity = NULL;

   try
   {
//CP20030319      switch( idContainer )
//CP20030319      {
      // RSP Contribution List
//CP20030319         case YTD::RSP_CONTRIBUTION_LIST :
      if( IFASTBP_PROC::RSP_CONTRIBUTION_LIST == idContainer )
      {
         {
            // Get MFAccount CBO
            if( dstcWorkSession->getMFAccount( idDataGroup, _dstrAccountNum, pMFAccount) <= WARNING && pMFAccount )
            {
               RSPContributionList *pRSPContributionList;
					sevRtn = pMFAccount->getRSPContributionList( pRSPContributionList, idDataGroup);
               // Retrieve RSP Contribution List.
               if(  sevRtn <= WARNING && pRSPContributionList )
               {
                  ptr = pRSPContributionList;                  
               }
					//else
						//throw ( sevRtn );
            }
         }
//CP20030319            break;
         // RSP Receipts List
//CP20030319         case YTD::RSP_RECEIPTS_LIST :
      }
      else if( IFASTBP_PROC::RSP_RECEIPTS_LIST == idContainer )
      {
         {
            // Retrieve the current RSP Contribution CBO
            RSPContribution *pRSPContribution = dynamic_cast< RSPContribution * >( getCBOItem( IFASTBP_PROC::RSP_CONTRIBUTION_LIST, idDataGroup ) );
            if( pRSPContribution )
            {
               // Retrieve the RSP Receipts List based on the current RSP Contribution CBO
               if( pRSPContribution->getRSPReceiptsList ( idDataGroup, _pRSPReceiptsList ) <= WARNING && _pRSPReceiptsList )
               {
                  ptr = _pRSPReceiptsList;
               }
            }
         }
//CP20030319            break;

         // Account CBO
//CP20030319         case YTD::ACCOUNT :
      }
      else if( IFASTBP_PROC::ACCOUNT == idContainer )
      {
         {
            // Get the Account CBO
            if( dstcWorkSession->getMFAccount( idDataGroup, _dstrAccountNum, pMFAccount) <= WARNING && pMFAccount )
            {
               ptr = pMFAccount;
            }
         }
//CP20030319            break;

//CP20030319         default :
      }
      else
      {
         assert(0);
//CP20030319      }
      }
   }
   catch( ConditionException & )
   {
		throw;
   }
   catch( ... )
   {
     //assert( 0 );
     THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
                     CND::BP_ERR_UNKNOWN_EXCEPTION ); //Show we throw?
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

void YTDContributionProcess::doGetField(
                                       const GenericInterface *rpGICaller,
                                       const BFContainerId& idContainer,
                                       const BFFieldId& idField,
                                       const BFDataGroupId& idDataGroup,
                                       DString &strValueOut,
                                       bool bFormatted
                                       ) const
{
	/*if( IFASTBP_PROC::RSP_CONTRIBUTION_LIST == idContainer )
   {
		if( idField  ==  ifds::EffectiveDate2 )
         {
            BFAbstractCBO *rpPtr = ( const_cast < EntityProcess *> ( this ) )->getCBOItem( IFASTBP_PROC::ENTITY_LIST, idDataGroup );
            if( rpPtr )
            {
               rpPtr->getField(ifds::EffectiveDate,strValueOut,idDataGroup,bFormatted);
            }
         }*/
}

//******************************************************************************
// Retrieve more records for RSP Receipts if more records exists.
// @param   GenericInnterface *rpGI - Pointer to the Dialog
// @param   const BFContainerId& idSearch - Not used.
// @param   E_SEARCHACTION eSearchAction - Not used.
//******************************************************************************

SEVERITY YTDContributionProcess::performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, E_SEARCHACTION eSearchAction )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, PERFORMSEARCH );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      // Ensure that the RSPRecipt List exists and there are more Records.
      if( _pRSPReceiptsList != NULL && _pRSPReceiptsList->doMoreRecordsExist() )
      {
         sevRtn = _pRSPReceiptsList->getMore();
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
// Check RSP Receipts for more records
// @param   GenericInterface *rpGI Caller - Pointer to the Dialog.
// @param   const BFContainerId& idSearch - Not used.
//******************************************************************************

bool YTDContributionProcess::doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch )
{
   return( rpGICaller == NULL || _pRSPReceiptsList == NULL ) ? false : _pRSPReceiptsList->doMoreRecordsExist();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/YTDContributionProcess.cpp-arc  $
// 
//    Rev 1.15   22 Jul 2008 13:49:56   kovacsro
// PET5517FN60 - Added Admin/Dates fields
// 
//    Rev 1.14   22 Jul 2008 11:12:54   kovacsro
// PET5517FN60C - Changed AmtMismatch into Caution, as per Winnie's suggestion
// 
//    Rev 1.13   17 Jul 2008 14:20:44   kovacsro
// PET5517 FN60C Cancellation of Contribution Receipts - Rebooking
// 
//    Rev 1.12   Dec 02 2004 11:37:58   yingbaol
// PET1137,FN01: Add Epost functionality
// 
//    Rev 1.11   Jul 22 2003 18:26:50   ZHANGCEL
// PTS 10019752 : not throw exception
// 
//    Rev 1.10   Jul 21 2003 16:32:48   ZHANGCEL
// PTS 10019752: Throw the exception of  getRSPContributionList
// 
//    Rev 1.9   Mar 21 2003 17:50:20   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.8   Oct 09 2002 23:53:44   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.7   Aug 29 2002 16:45:22   SMITHDAV
// Condition split.
// 
//    Rev 1.6   Aug 29 2002 12:54:48   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.5   22 May 2002 18:25:24   PURDYECH
// BFData Implementation
// 
//    Rev 1.4   27 Mar 2002 19:56:26   PURDYECH
// Process/WindowFactory overhaul
// 
//    Rev 1.3   Nov 20 2001 16:19:52   ZHANGCEL
// Many changes for getting Address from  view174
// 
//    Rev 1.2   20 Aug 2001 12:05:42   HSUCHIN
// cleanup and added comments
// 
//    Rev 1.1   18 Aug 2001 09:28:34   HSUCHIN
// implemented moreAvailiable and other enhancements
// 
//    Rev 1.0   05 Aug 2001 15:31:20   HSUCHIN
// Initial revision.
 */

