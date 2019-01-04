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
// ^FILE   : ConfirmationProcess.cpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 16/04/99
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : ConfirmationProcess
//    This class manages the management company and profile selection.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include <ifastdataimpl\dse_dstcglob_vw.hpp>
#include "confirmationprocess.hpp"
#include "confirmationprocessincludes.h"

#include "accdetailsprocessincludes.h"
#include "accinfoprocessincludes.h"
#include "mfcaninterprocparam.hpp"
#include "nasuprocessincludes.h"
#include "transcancelprocessincludes.h"

#include <ifastcbo\broker.hpp>
#include <ifastcbo\confirmation.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\intermediary.hpp>
#include <ifastcbo\intermediarylist.hpp>
#include <ifastcbo\remarkslist.hpp>
#include <ifastcbo\shareholder.hpp>
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_CONFIRMATION;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< ConfirmationProcess > processCreator (CMD_BPROC_CONFIRMATION);
#include <ifastcbo\remarks.hpp>
//awd
#include <ifastawd\DSTCAWDSession.hpp>
#include <bfawdi\bfawdinterface.hpp>
#include <bfsessn\bfawdsession.hpp>

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "ConfirmationProcess" );
   const I_CHAR * const PERFORMSEARCH = I_( "performSearch" );
   const I_CHAR * const Y                       = I_( "Y" );
   const I_CHAR * const N                       = I_( "N" );
   const I_CHAR * const PARM_DATAGROUPID        = I_( "DataGroupID" );
   const I_CHAR * const TRADES_PROCESS          = I_( "TradesProcess" );
   const I_CHAR * const JTRADES_PROCESS         = I_( "JTradesProcess" );
   const I_CHAR * const TRADES_PROCESS_GENERAL  = I_( "GeneralTradesProcess" );
   const I_CHAR * const TRADE_PROCESS_WITHLOSS  = I_("ModifyPendingTradesWithLoss");
   const I_CHAR * const ACCOUNT_NUM             = I_( "AccountNum" );
}

namespace CONFPROC
{
   const DString REFRESH( I_( "Refresh" ) );
   const DString GETWORK( I_( "GetWork" ) );
   const DString END( I_( "End" ) );
   const DString NEWSEARCH( I_( "NewSearch" ) );
   const DString CHOICE( I_( "Choice" ) );
   const DString TRADE( I_( "Trade" ) );
   const DString BATCH( I_("Batch") );

}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;   
}

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319ConfirmationProcess::ConfirmationProcess() : 
ConfirmationProcess::ConfirmationProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, m_rpChildGI (NULL)
, m_pConfirmation (NULL)
, m_dstrAWDEvent(NULL_STRING)
, m_InvokedBrowserScreen( NULL_STRING )
, m_dstrHostAccountNum(NULL_STRING)
, m_dstrHostShareholderNum(NULL_STRING)
, m_dstrHostEntityId(NULL_STRING)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   addContainer( IFASTBP_PROC::CONFIRMATION, false, BF::NullContainerId, true );
   addContainer( IFASTBP_PROC::REMARKS_LIST, true, BF::NullContainerId, true );

// Remarks Details
   addFieldDetails( ifds::TransNote, IFASTBP_PROC::REMARKS_LIST );
   addFieldDetails( ifds::Remark1, IFASTBP_PROC::REMARKS_LIST );
   addFieldDetails( ifds::Remark2, IFASTBP_PROC::REMARKS_LIST );
   addFieldDetails( ifds::Remark3, IFASTBP_PROC::REMARKS_LIST );
   addFieldDetails( ifds::Remark4, IFASTBP_PROC::REMARKS_LIST );
   addFieldDetails( ifds::Remark5, IFASTBP_PROC::REMARKS_LIST );
   addFieldDetails( ifds::Remark6, IFASTBP_PROC::REMARKS_LIST );
   addFieldDetails( ifds::Remark7, IFASTBP_PROC::REMARKS_LIST );
   addFieldDetails( ifds::Remark8, IFASTBP_PROC::REMARKS_LIST );
   addFieldDetails( ifds::Remark9, IFASTBP_PROC::REMARKS_LIST );
   addFieldDetails( ifds::Remark10, IFASTBP_PROC::REMARKS_LIST );
   addFieldDetails( ifds::Active, IFASTBP_PROC::REMARKS_LIST );
   addFieldDetails( ifds::EffectiveDate, IFASTBP_PROC::REMARKS_LIST );
   addFieldDetails( ifds::ProcessDate, IFASTBP_PROC::REMARKS_LIST );
   addFieldDetails( ifds::Username, IFASTBP_PROC::REMARKS_LIST );
   addFieldDetails( ifds::ModDate, IFASTBP_PROC::REMARKS_LIST );
   addFieldDetails( ifds::ModUser, IFASTBP_PROC::REMARKS_LIST );
   addFieldDetails( ifds::RemarkType, IFASTBP_PROC::REMARKS_LIST );
   addFieldDetails( ifds::AccountNum, IFASTBP_PROC::REMARKS_LIST );

// subclass process
   addFieldDetails (CONFPROC::CHOICE_FIELD, BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails (CONFPROC::CREATING_SHAREHOLDER, BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails (CONFPROC::REMARKS_AVAILABLE, BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails (CONFPROC::FROM_REMARKS, BF::NullContainerId, SUBCLASS_PROCESS); 
   addFieldDetails (CONFPROC::SHOW_UPDATE_ALL_CIF, BF::NullContainerId, SUBCLASS_PROCESS);
   
   addFieldDetails (CONFPROC::HostAccountNum, BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails (CONFPROC::HostShareholderNum, BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails (CONFPROC::HostEntityId, BF::NullContainerId, SUBCLASS_PROCESS);

// Confirmation Details
   addFieldDetails ( ifds::Using_AWD, 
                     IFASTBP_PROC::CONFIRMATION );
   addFieldDetails ( ifds::BusinessArea, 
                     IFASTBP_PROC::CONFIRMATION );
   addFieldDetails ( ifds::WorkType, 
                     IFASTBP_PROC::CONFIRMATION );
   addFieldDetails ( ifds::StatusDesc, 
                     IFASTBP_PROC::CONFIRMATION );
   addFieldDetails ( ifds::Batch, 
                     IFASTBP_PROC::CONFIRMATION );
   addFieldDetails ( ifds::Remarks, 
                     IFASTBP_PROC::CONFIRMATION );
   addFieldDetails ( ifds::AWDComment, 
                     IFASTBP_PROC::CONFIRMATION );
   addFieldDetails ( ifds::Option, 
                     IFASTBP_PROC::CONFIRMATION );
   addFieldDetails ( ifds::UpdAllNonFin, 
                     IFASTBP_PROC::CONFIRMATION );
   addFieldDetails ( ifds::AWDObjectId, 
                     IFASTBP_PROC::CONFIRMATION );
   addFieldDetails ( ifds::AWDCrda, 
                     IFASTBP_PROC::CONFIRMATION );
}

//******************************************************************************
ConfirmationProcess::~ConfirmationProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   m_rpChildGI = NULL;
   delete m_pConfirmation;
   m_pConfirmation = NULL;
}

//******************************************************************************
void ConfirmationProcess::doGetField( const GenericInterface *rpGICaller,
                                      const BFContainerId& idContainer,
                                      const BFFieldId& idField,
                                      const BFDataGroupId& idDataGroup,
                                      DString &dstrValueOut,
                                      bool bFormatted) const
{
   dstrValueOut = NULL_STRING;
   if (BF::NullContainerId == idContainer)
   {
      if (idField == CONFPROC::CHOICE_FIELD)
      {
         dstrValueOut = m_dstrChoiceField;
      }
      else if (idField == CONFPROC::CREATING_SHAREHOLDER)
      {
         dstrValueOut = m_dstrCreatingShareholder;
      }
      else if (idField == CONFPROC::REMARKS_AVAILABLE)
      {
         dstrValueOut = ( m_dstrDisableRemarks == N ) ? m_dstrRemarksAvailable : N;
      }
      else if (idField == CONFPROC::FROM_REMARKS)
      {
         dstrValueOut = m_dstrFromRemarks;
      }
      else if (idField == CONFPROC::SHOW_UPDATE_ALL_CIF)
      {
         dstrValueOut = I_("0");

         DString cssStopSINMatch;
         DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

         pDSTCWorkSession->getOption (ifds::CSSStopSINMatch, cssStopSINMatch, idDataGroup, false);
         if (cssStopSINMatch == Y)
         {
            DString accountNum;
            MFAccount *pMFAccount (NULL);

            getGlobal (WORK_GLOBAL, ifds::LastActiveAccountNum, accountNum);
            if ( pDSTCWorkSession->getMFAccount (idDataGroup, accountNum, pMFAccount) <= WARNING &&
                 pMFAccount)
            {
               DString shrNum;
               Shareholder *pShareholder (NULL);

               pMFAccount->getField (ifds::ShrNum, shrNum, idDataGroup);
               if ( pDSTCWorkSession->getShareholder (idDataGroup, shrNum, pShareholder) <= WARNING &&
                    pShareholder)
               {
//if designation is Nominee and Client look at the broker and check the NFUUpdate flag,
//otherwise look at the Intermediary
                  DString acctDesignation;
                  
                  pShareholder->getField (ifds::AcctDesignation, acctDesignation, idDataGroup, false);
                  
                  if (acctDesignation == I_("1") || acctDesignation == I_("2"))
                  {
                     Broker *pBroker (NULL);
                     DString brokerCode (NULL_STRING);
                     
                     pMFAccount->getField (ifds::BrokerCode, brokerCode, idDataGroup, false);

                     if ( !brokerCode.empty () &&
                          pMFAccount->getBroker (pBroker, brokerCode, idDataGroup) <= WARNING &&
                          pBroker)
                     {

                        pBroker->getField (ifds::NFUpdate, dstrValueOut, idDataGroup, false);
                     }
                  }
                  else if (acctDesignation == I_("3"))
                  {
                     DString interCode;
                     IntermediaryList *pIntermediaryList;

                     if (pDSTCWorkSession->getMgmtCo().getIntermediaryList(pIntermediaryList) <= WARNING &&
                         pIntermediaryList)
                     {
                        Intermediary *pIntermediary (NULL);
                        
                        pMFAccount->getField (ifds::InterCode, interCode, idDataGroup, false);
                        if (!interCode.empty () &&
                            pIntermediaryList->getIntermediary (idDataGroup, interCode, pIntermediary) &&
                            pIntermediary)
                        {
                           pIntermediary->getField (ifds::NFUpdate, dstrValueOut, idDataGroup, false);
                        }
                     }
                  }
               }
            }
         }
      } 
      else if (idField == CONFPROC::HostAccountNum)
      {
         dstrValueOut = m_dstrHostAccountNum;
      }
      else if (idField == CONFPROC::HostShareholderNum)
      {
         dstrValueOut = m_dstrHostShareholderNum;
      }
      else if (idField == CONFPROC::HostEntityId)
      {
         dstrValueOut = m_dstrHostEntityId;
      }
   }
}

//******************************************************************************
SEVERITY ConfirmationProcess::doSetField( const GenericInterface *rpGICaller,
                                          const BFContainerId& idContainer,
                                          const BFFieldId& idField,
                                          const BFDataGroupId& idDataGroup,
                                          const DString& dstrValue,
                                          bool bFormatted)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, DOSETFIELD);

   if (idField == CONFPROC::CHOICE_FIELD && BF::NullContainerId == idContainer)
   {
      m_dstrChoiceField = dstrValue;
   }   

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ConfirmationProcess::doInit ()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );

   m_dstrAWDEvent = getParent()->getCommand().getName();

	// Save data group to commit
   //getParameter( PARM_DATAGROUPID, dstr );
   getParameter( MFCAN_IP_PARAM::DISABLE_REMARKS, m_dstrDisableRemarks );
   getParameter( MFCAN_IP_PARAM::FROM_REMARKS, m_dstrFromRemarks );
   getParameter( NASULIT::PARM_CALLED_FROM, m_dstrCalledFrom );
   getParameter( NASULIT::CREATING_ACCOUNT, m_strNASUFlag );
   getParameter( TRANSCANCEL::DISPLAY_REBOOK, m_dstrDispRebook );
	getParameter( CONFPROC::BATCH, m_dstrBatchNum );
   getParameter( I_("InvokedBrowserName"), m_InvokedBrowserScreen );
   getParameter( CONFPROC::COMMIT_PARENT_DATA_GROUPS, m_CommitParentDataGroups);
   m_dstrDispRebook.strip().upperCase();
   getParameter( TRANSCANCEL::BULK_CANCEL, m_dstrBulkCancel );
   m_dstrBulkCancel.strip().upperCase(); 

   if (m_dstrDisableRemarks.empty())
   {
      m_dstrDisableRemarks = N;
   }
   m_dstrFromRemarks = m_dstrFromRemarks.empty() ? N : m_dstrFromRemarks;

   const BFDataGroupId& idParentDataGroup = getParent()->getDataGroupId(); // the data group that need commit
   m_dstrRemarksAvailable = Y;
   try
   {
      MFAccount *pMFAccount;
      Shareholder* pShareholder;
      DString dstrShrNum, 
         dstrAccountNum;

      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

      //try and get the global shareholder number
      getGlobal( WORK_GLOBAL, ifds::LastActiveShrNum, dstrShrNum );
      dstrShrNum.strip().stripLeading( '0' );
      if( dstrShrNum.empty() ) //no shareholder number, get the shareholder number from the account
      {
         //get the global account number for this worksessionid
         getGlobal( WORK_GLOBAL, ifds::LastActiveAccountNum, dstrAccountNum );
         dstrAccountNum.strip().stripLeading( '0' );
         if( dstrAccountNum.empty() ) //we cannot get the remarks list, should be disabled
         {
            m_dstrRemarksAvailable = N;
            return(GETCURRENTHIGHESTSEVERITY());
         }
         m_dstrAccountNum = dstrAccountNum;
         if( dstcWorkSession->getMFAccount( idParentDataGroup, dstrAccountNum, pMFAccount ) <= WARNING )
         {
            pMFAccount->getField( ifds::ShrNum, dstrShrNum, idParentDataGroup );
            if( !dstrShrNum.strip().stripLeading( '0' ).empty() )
               setGlobal( WORK_GLOBAL, ifds::LastActiveShrNum, dstrShrNum );
         }
      }
      //at this point we should have a shareholder number
      //get the shareholder from the repository
      m_dstrShrNum = dstrShrNum;

      if( !bfutil::isServerContext() && dstcWorkSession->getShareholder( idParentDataGroup, dstrShrNum, pShareholder ) <= WARNING )
      {
         RemarksList *pRemarksList = NULL;

         if( pShareholder->getRemarksList( pRemarksList, idParentDataGroup ) <= WARNING )
         {
            setContainer( IFASTBP_PROC::REMARKS_LIST, pRemarksList );
            getParameter( NASULIT::CREATING_SHAREHOLDER, m_dstrCreatingShareholder );
         }
      }
      else setContainer( IFASTBP_PROC::REMARKS_LIST, NULL );
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
bool ConfirmationProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_CONFIRMATION );
}

//******************************************************************************
bool ConfirmationProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   return(false);
}

//******************************************************************************
bool ConfirmationProcess::doCancel( GenericInterface *rpGI )
{  
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOCANCEL );

   // cleanup the uncommited transactions
   dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->clearUncommitedTransactions();
   return(true);
}

//******************************************************************************
E_COMMANDRETURN ConfirmationProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
		m_pConfirmation = new Confirmation( *getBFWorkSession() );
      m_pConfirmation->init();

      const BFDataGroupId& idParentDataGroup = getParent()->getDataGroupId(); // the data group that need commit
      m_pConfirmation->setField ( ifds::Using_AWD, N, idParentDataGroup, false);
      m_pConfirmation->setField ( ifds::Remarks, Y, idParentDataGroup, false);
      m_pConfirmation->setField ( ifds::AWDComment, N, idParentDataGroup, false);
      m_pConfirmation->setField ( ifds::Option, 0, idParentDataGroup, false);
      m_pConfirmation->setField ( ifds::UpdAllNonFin, N, idParentDataGroup, false);
		if (m_dstrCalledFrom == TRADES_PROCESS_GENERAL || 
          m_dstrCalledFrom == TRADE_PROCESS_WITHLOSS)
		{
			m_pConfirmation->setField( ifds::Batch, m_dstrBatchNum, idParentDataGroup, false );
			m_pConfirmation->setFieldReadOnly( ifds::Batch, idParentDataGroup, true );
		}

      setContainer (IFASTBP_PROC::CONFIRMATION, m_pConfirmation);
      setParameter (CONFPROC::PARM_AWDEVENT, m_dstrAWDEvent);
      setParameter (CONFPROC::PARM_CALLED_FROM, m_dstrCalledFrom);
      setParameter (CONFPROC::CREATING_ACCOUNT, m_strNASUFlag);
      setParameter (TRANSCANCEL::DISPLAY_REBOOK, m_dstrDispRebook);
      setParameter (TRANSCANCEL::BULK_CANCEL, m_dstrBulkCancel);
      setParameter (CONFPROC::BATCH, m_dstrBatchNum );
      setParameter( CONFPROC::COMMIT_PARENT_DATA_GROUPS, m_CommitParentDataGroups);

      setParameter( I_("InvokedBrowserName"), m_InvokedBrowserScreen );

      if (!bfutil::isServerContext())
      {
         rtn = invokeCommand (this, CMD_GUI_CONFIRMATION, getProcessType(), isModal(), &m_rpChildGI);
      }
      else
      {
         setField (this, BF::NullContainerId, CONFPROC::CHOICE_FIELD, CONFPROC::END);
         if (ok (this))
         {
            rtn = CMD_OK;
         }
         else
         {
            PROMOTECONDITIONS();
         }
      }
   }
   catch (ConditionException &ce)
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
   return rtn;
}

//******************************************************************************
bool ConfirmationProcess::doRefresh( GenericInterface *rpGICaller, const I_CHAR *szOriginalCommand )
{
   TRACE_METHOD( CLASSNAME, DOREFRESH );

   return(true);
}

//******************************************************************************
bool ConfirmationProcess::doOk (GenericInterface *rpGICaller)
{
   bool bRet = true; //no matter what return true
   //refresh the remarks COA flag on the shareholder
   const BFDataGroupId& idDataGroup = getDataGroupId();
   Shareholder *pShareholder;

   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   // when there is no remarks, we should not call getShareholder which cause problems!
   if( m_dstrRemarksAvailable == Y && 
       dstcWorkSession->getShareholder (idDataGroup, m_dstrShrNum, pShareholder) <= WARNING)
   {

      if (getNumberOfItemsInList (rpGICaller, IFASTBP_PROC::REMARKS_LIST))
      {
         DString key = getFirstListItemKey (rpGICaller, IFASTBP_PROC::REMARKS_LIST);

         if( !key.empty() )
         {
            pShareholder->setField (ifds::Remarks, Y, idDataGroup, false);
         }
      }
   }

   DSTCAWDSession *pDSTCAWDSession = dynamic_cast<DSTCAWDSession* > (getSession());
   if (pDSTCAWDSession && pDSTCAWDSession->isAWDWorking())
   {
      pDSTCAWDSession->retrieveObjectId ();
      
      DString awdObjectId,
         awdCrda;
      BFAwdInterface *pAwdInterface (NULL);

      // Get AWD Object ID
      pDSTCAWDSession->getAwdField (I_("ObjectID"), awdObjectId);
      //get crda      
      const BFAwdData *pAwdWork = pDSTCAWDSession->getAwdSession ()->getProcessWork();
      if (pAwdWork)
      {
         awdCrda = pAwdWork->getLobValue (I_("CRDA"));
      }
      if (m_pConfirmation && !awdObjectId.empty()) //store it
      {
         m_pConfirmation->setField (ifds::AWDObjectId, awdObjectId, idDataGroup, false);
         m_pConfirmation->setField (ifds::AWDCrda, awdCrda, idDataGroup, false);
      }
   }

   return bRet;
}

//******************************************************************************
void ConfirmationProcess::refreshGlobals()
{
   //The call to DSTCHostDataManager is somehow, against the rule of supporting multiple back-ends.
   //Until we are sure that this will be the case we will keep the call here. However, is less
   //likely possible that different back-ends will have the same way to confirm the changes. 
   //It will be probably necessary to move the host substitution values from DSTCHostDataManager,
   //to another level, a more abstract one.(SP)
   DString dstrShrNum, dstrAccountNum, dstrEntityId;
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   //try and get the global shareholder number
   getGlobal( WORK_GLOBAL, ifds::LastActiveShrNum, dstrShrNum );
   //try and get the global account number
   getGlobal( WORK_GLOBAL, ifds::LastActiveAccountNum, dstrAccountNum );
   getGlobal( WORK_GLOBAL, ifds::LastActiveEntityId, dstrEntityId );
   dstrShrNum.strip().stripLeading( '0' );
   dstrAccountNum.strip().stripLeading( '0' );
   dstrEntityId.strip().stripLeading( '0' );
   if( !dstrShrNum.empty() )
   {
      DString dstrHostShrNum;

      dstcWorkSession->getHostShareholderNum( dstrShrNum, dstrHostShrNum );
      dstrHostShrNum.strip().stripLeading( '0' );
      if( !dstrHostShrNum.empty() )
      {
         //yes, there is a refreshed value for us
         //set it as the global value 
         setGlobal( WORK_GLOBAL, ifds::LastActiveShrNum, dstrHostShrNum );
         m_dstrHostShareholderNum = dstrHostShrNum;
      }
   }
   if( !dstrAccountNum.empty() )
   {
      DString dstrHostAccountNum;

      dstcWorkSession->getHostAccountNum( dstrAccountNum, dstrHostAccountNum );
      dstrHostAccountNum.strip().stripLeading( '0' );
      if( !dstrHostAccountNum.empty() )
      {
         //yes, there is a refreshed value for us
         //set it as the global value
         setGlobal( WORK_GLOBAL, ifds::LastActiveAccountNum, dstrHostAccountNum );
         m_dstrHostAccountNum = dstrHostAccountNum;
      }
   }
   if( !dstrEntityId.empty() )
   {
      DString dstrHostEntityId;

      dstcWorkSession->getHostEntityId( dstrEntityId, dstrHostEntityId );
      dstrHostEntityId.strip().stripLeading( '0' );
      if( !dstrHostEntityId.empty() )
      {
         //yes, there is a refreshed value for us
         //set it as the global value
         setGlobal( WORK_GLOBAL, ifds::LastActiveEntityId, dstrHostEntityId );
         m_dstrHostEntityId = dstrHostEntityId;
      }
   }
}

//******************************************************************************
SEVERITY ConfirmationProcess::ok2 (GenericInterface *rpGICaller)
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, OK2 );
   bool bSuccessFlag = false;

   const BFDataGroupId& idDataGroup = getDataGroupId();

   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   if (doOk (rpGICaller ))
   {
      if (dstcWorkSession->isUpdatedForDataGroup (idDataGroup))
      {
         if (dstcWorkSession->validateAll (idDataGroup) <= WARNING)
         {
            bSuccessFlag = true;
            dstcWorkSession->commitDataGroup (idDataGroup);
         }
      }
      else
      {  // Nothing happened - make sure and remove any dummy entries added
         dstcWorkSession->deleteNonUpdatedAddedElements (idDataGroup);
         bSuccessFlag = true;
      }
   }
   if (bSuccessFlag)
   {
      const BFDataGroupId& idCommitDataGroup = getParent()->getDataGroupId(); // the data group that need commit
      if (BF::HOST != idCommitDataGroup)
      {
         dstcWorkSession->commitDataGroup (idCommitDataGroup);
         const BFDataGroupId& parentIdDataGroup = dstcWorkSession->getParentDataGroup(idCommitDataGroup);
         if(m_CommitParentDataGroups == I_("1") || m_CommitParentDataGroups == I_("2"))
         {
            if(parentIdDataGroup != BF::HOST)
            {  
               const BFDataGroupId& parentParentIdDataGroup = dstcWorkSession->getParentDataGroup(parentIdDataGroup);
               dstcWorkSession->commitDataGroup(parentIdDataGroup);
               if(m_CommitParentDataGroups == I_("2") && parentParentIdDataGroup != BF::HOST)
               {
                  dstcWorkSession->commitDataGroup(parentParentIdDataGroup);
               }
            }
         }
      }

      //in any case we should build transactions and try to commit them
      dstcWorkSession->buildTransactions ();
	  BFData *pCommitParams = new BFData (ifds::DSTCCONF_VW);
      m_pConfirmation->getData (*pCommitParams, idDataGroup);
      dstcWorkSession->setCommitParams (*pCommitParams);
      dstcWorkSession->commit ();
	  delete pCommitParams;
      
	  dstcWorkSession->popCommitConditions (MYFRAME());
      if (GETCURRENTHIGHESTSEVERITY() > WARNING)
      {  // tell the world we have transaction errors
         setParameter (NASULIT::TRXNS_ERROR, Y);
         rpGICaller->send (this, I_("TrxnsError"));
         return GETCURRENTHIGHESTSEVERITY();
      }
      else
      {       
         setParameter (NASULIT::TRXNS_ERROR, N);
         if (GETCURRENTHIGHESTSEVERITY() == WARNING)
         {
            setParameter (I_( "TrxnsWarnings" ), Y);
         }       

		// fix incident 2935967 where SMRT should be set up N after success of processing smartform
		// so that when QC check the work object, smartform won't be loaded again 
		 DSTCAWDSession *pDSTCAWDSession = dynamic_cast<DSTCAWDSession* > (getSession());
		 if (pDSTCAWDSession && pDSTCAWDSession->isAWDWorking()){
			BFAwdData *pAwdWork = const_cast<BFAwdData* >(pDSTCAWDSession->getAwdSession ()->getProcessWork());
			if (pAwdWork && pAwdWork->getLobValue (I_("SMRT")) == Y)
			{
				pAwdWork->setLobData (I_("SMRT"), N);
			}
		 }
      }
      if (m_dstrChoiceField == CONFPROC::REFRESH)
      {
         if( GETCURRENTHIGHESTSEVERITY() == WARNING || 
			    CURRENTCONDITIONCOUNT() == 0 ) //refresh only if we do not have errors after transactions
         {
            refreshGlobals();
         }
      }
      else if (m_dstrChoiceField == CONFPROC::END)
      {
         refreshGlobals();
      }
      else if (m_dstrChoiceField == CONFPROC::GETWORK)
      {
         refreshGlobals();
      }
      else if (m_dstrChoiceField == CONFPROC::NEWSEARCH)
      {
         refreshGlobals();
      }
      else if (m_dstrChoiceField == CONFPROC::TRADE)
      {
         refreshGlobals();
      }
      else
      {
         assert( 0 );
         throw;
      }
      setParameter (CONFPROC::CHOICE, m_dstrChoiceField);

      ProcessObserver* procObserver = getProcessObserver();
      if (procObserver) {
         procObserver->notifyOk(rpGICaller, this);
      }
      
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/ConfirmationProcess.cpp-arc  $
 * 
 *    Rev 1.62   Aug 10 2012 12:18:36   popescu
 * IN#3051211 - P0179630 FN01 - FATCA - Acct Ownership Allocation option is not refreshed
 * 
 *    Rev 1.61   Jun 07 2012 15:51:16   yingz
 * fix 2935967
 * 
 *    Rev 1.60   Jun 06 2012 14:41:10   yingz
 * fix incident 2935967 where SMRT should be set up N after success of processing smartform so that when QC check the work object, smartform won't be loaded again
 * 
 *    Rev 1.59   Jan 14 2011 16:45:36   dchatcha
 * PET0165541 FN03 - QESI Phase3, refresh account detail screen after there is update from Govt Amendment screen.
 * 
 *    Rev 1.58   27 May 2009 10:22:54   popescu
 * Autobatch - passed the name of the batch to reebok functionality
 * 
 *    Rev 1.57   07 Apr 2008 09:38:24   kovacsro
 * IN#1166229 - refresh ObjectId & CRDA
 * 
 *    Rev 1.56   12 Nov 2007 23:44:00   popescu
 * PET 5653/01 - Internal Audit project
 * 
 *    Rev 1.55   02 Nov 2007 17:01:32   popescu
 * Internal Audit Project passed in AWDObjectId to views that have the field
 * 
 *    Rev 1.54   01 Aug 2007 09:45:32   popescu
 * GAP 6 - CIF - also added UpdateAllCIF for vew 85
 * 
 *    Rev 1.53   17 Jul 2007 15:18:42   popescu
 * GAP 6 CIF - AIM
 * 
 *    Rev 1.52   Sep 25 2006 13:59:20   porteanm
 * Incident 693185 - Warn support for view 161.
 * 
 *    Rev 1.51   May 08 2006 11:42:40   popescu
 * Incident# 613483 - the standard  'Confirmation' window will pop-up for entering AWD Comments - enhancement
 * 
 *    Rev 1.50   Jan 23 2006 14:00:30   zhengcon
 * Incident #521273 -- Auto Clone - Integration  - Add new LOB (Batch) field to confirmation
 * 
 *    Rev 1.49   Nov 24 2005 16:20:34   porteanm
 * PET1286 FN01 - Bulk Cancellation.
 * 
 *    Rev 1.48   Aug 19 2005 13:18:26   yingbaol
 * Incident 379395: account number error in AWD 
 * 
 *    Rev 1.47   Jul 15 2005 09:26:30   Yingbaol
 * PET1235,FN01: pass parameters 
 * 
 *    Rev 1.46   Jun 20 2005 18:41:38   porteanm
 * PET1024 FN40 - Guarantee Adjustments.
 * 
 *    Rev 1.45   Jun 20 2005 06:24:36   popescu
 * PET1024 FN40 - Guarantee Adjustments - displayed the Warning Conditions Message Box.
 * 
 *    Rev 1.44   Jun 16 2005 10:57:36   porteanm
 * PET1024 FN40 - Guarantee Adjustments.
 * 
 *    Rev 1.43   Apr 12 2005 10:28:22   porteanm
 * PET1190 FN14 - Wire order redemption against unsettled units.
 * 
 *    Rev 1.42   Nov 17 2004 15:03:06   PURDYECH
 * PET910 - .NET Conversion:  Fixed compiler warning messages.
 * 
 *    Rev 1.41   May 27 2004 17:18:24   HERNANDO
 * PET1017 FN01- Remarks-Confirmation change.   Allow Confirmation to view the Added Remark and allow copying it to the AWD object.
 * 
 *    Rev 1.40   Oct 03 2003 09:55:38   VADEANUM
 * PTS 10022545 - Record created when no Remark entered on the Remarks dialog - removed refAccount setting on this layer
 * PTS 10022399 - Wrong Account # assigned to Remark - replaced RefAccount with AccountNum in order to have the fieldid picked up in DSTCWorkSession::commit() after including the field in the transaction key.
 * 
 *    Rev 1.39   Sep 11 2003 10:30:18   HSUCHIN
 * bug fix to setting the refAccount to remarks during confirmation.
 * 
 *    Rev 1.38   Jul 30 2003 11:26:58   FENGYONG
 * CIBC enhancement PET809_FN46
 * 
 *    Rev 1.37   Mar 21 2003 17:38:10   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.36   Mar 11 2003 13:49:44   PURDYECH
 * Fixes to help the DataGroupId source code converters work more smoothly.
 * 
 *    Rev 1.35   Mar 09 2003 15:55:30   PURDYECH
 * Small fixes around DataGroupIds and ContainerIds.
 * 
 *    Rev 1.34   Mar 07 2003 11:55:46   PURDYECH
 * Cleanup obsolete code.
 * 
 *    Rev 1.33   Oct 09 2002 23:53:08   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.32   Aug 29 2002 16:44:50   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.31   Aug 29 2002 12:54:16   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.30   Aug 12 2002 14:33:42   KOVACSRO
 * PTS 10009105: in case we used LastActiveAccountNum, we should set the last Shr Num.
 * 
 *    Rev 1.29   Jul 12 2002 15:20:44   FENGYONG
 * Add entityId to refreshglobals
 * 
 *    Rev 1.28   22 May 2002 18:24:10   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.27   19 Apr 2002 15:53:04   HERNANDO
 * Took out dstcWorkSession->refreshData() call to prevent Trades from disappearing before updating the AWD work object.
 * 
 *    Rev 1.26   27 Mar 2002 19:54:46   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.25   Mar 15 2002 14:20:30   HERNANDO
 * Removed (Commented-out) Batch Number.
 * 
 *    Rev 1.24   Jan 25 2002 13:13:30   FENGYONG
 * promopt condition
 * 
 *    Rev 1.23   18 Oct 2001 17:04:06   KOVACSRO
 * Don't get RemarksList for server context.
 * 
 *    Rev 1.22   18 Oct 2001 14:56:30   KOVACSRO
 * Don't get RemarksList when not necessary.
 * 
 *    Rev 1.21   12 Jun 2001 16:57:34   YINGZ
 * we do not need datagroupid parm when commit
 * 
 *    Rev 1.20   15 May 2001 15:38:40   YINGZ
 * data group id clean up
 * 
 *    Rev 1.19   03 May 2001 14:05:22   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.18   Apr 06 2001 17:15:40   YINGZ
 * make group id work
 * 
 *    Rev 1.17   Feb 21 2001 11:33:54   YINGZ
 * make api nasu work
 * 
 *    Rev 1.16   Jan 24 2001 13:03:08   KOVACSRO
 * Code cleanup.
 * 
 *    Rev 1.15   Jan 17 2001 10:29:20   KOVACSRO
 * Delete PendingTradesList whenever new trade(s) is confirmed.
 * 
 *    Rev 1.14   Jan 04 2001 09:40:06   ZHANGCEL
 * Added getParameter and setParameter for CreateAccount
 * 
 *    Rev 1.13   15 Dec 2000 12:43:24   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.12   Dec 01 2000 11:06:36   VASILEAD
 * Fixed sending worksessionid instead usersessionid to the Confirmation init
 * 
 *    Rev 1.11   Nov 27 2000 11:41:40   VASILEAD
 * check if it is server context for pushing the conditions on the Host frame
 * 
 *    Rev 1.10   Nov 27 2000 11:38:54   VASILEAD
 * Push the conditions on the HostTransactionContainer so we can pick them up in our services
 * 
 *    Rev 1.9   Nov 07 2000 13:22:46   YINGBAOL
 * fix bug for client locale
 * 
 *    Rev 1.8   Oct 11 2000 15:28:02   KOVACSRO
 * Added parameter 'CalledFrom'.
 * 
 *    Rev 1.7   Sep 20 2000 17:39:56   HERNANDO
 * AWD Event implementation.
 * 
 *    Rev 1.6   Aug 25 2000 10:41:08   YINGBAOL
 * popup Trade screen after confirmation
 * 
 *    Rev 1.5   Aug 10 2000 09:05:06   DT24433
 * changed to call clearUncommittedTransactions via WorkSessionDetails
 * 
 *    Rev 1.4   Aug 02 2000 15:32:00   BUZILA
 * "locale" changes
 * 
 *    Rev 1.3   Apr 28 2000 18:20:04   BUZILA
 * M3
 * 
 *    Rev 1.2   Apr 04 2000 15:23:20   DT24433
 * removed unused headers
 * 
 *    Rev 1.1   Mar 27 2000 16:09:20   YINGZ
 * code sync
 * 
 *    Rev 1.0   Feb 15 2000 10:59:32   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.42   Jan 31 2000 13:48:14   POPESCUS
 * took out clearing the update flags
 * 
 *    Rev 1.41   Jan 28 2000 09:43:36   POPESCUS
 * ?
 * 
 *    Rev 1.40   Jan 27 2000 17:35:10   POPESCUS
 * fixed some memory leaks
 * 
 *    Rev 1.39   Jan 26 2000 19:37:50   DT24433
 * changed to set TRXNS_ERROR parm and send TrxnsError message to calling dialog (handled by basemaindlg)
 * 
 *    Rev 1.38   Jan 26 2000 19:43:02   VASILEAD
 * Fixes
 * 
 *    Rev 1.37   Jan 24 2000 18:10:22   POPESCUS
 * took out some comments
 * 
 *    Rev 1.36   Jan 23 2000 21:12:28   POPESCUS
 * Refresh fix
 * 
 *    Rev 1.35   Jan 23 2000 18:27:50   POPESCUS
 * disable remarks when no global account num and shareholder num exist
 * 
 *    Rev 1.34   Jan 23 2000 16:58:34   POPESCUS
 * fixed the bug that freezes the app after errors in trxns and updated remarks in confirmation
 * 
 *    Rev 1.33   Jan 21 2000 15:46:54   POPESCUS
 * set the choice field as param
 * 
 *    Rev 1.32   Jan 21 2000 14:34:46   HSUCHIN
 * modified to get account number and shareholder number from global params
 * 
 *    Rev 1.31   Jan 19 2000 10:12:08   BUZILA
 * refresh stuf
 * 
 *    Rev 1.30   Jan 18 2000 16:47:48   HSUCHIN
 * storing account num and shareholder num for dialog usage.
 * 
 *    Rev 1.29   Jan 18 2000 11:29:46   POPESCUS
 * fixed some of the settings of the global values (account & shareholder)
 * 
 *    Rev 1.28   Jan 16 2000 16:58:06   POPESCUS
 * prepared for refresh and cleaned up the code
 * 
 *    Rev 1.27   Jan 15 2000 14:19:44   BUZILA
 * fix DG problem
 * 
 *    Rev 1.26   Jan 14 2000 18:08:52   POPESCUS
 * set the last active account num
 * 
 *    Rev 1.25   Jan 14 2000 17:03:24   BUZILA
 * refresh stuff
 * 
 *    Rev 1.24   Jan 14 2000 10:18:24   POPESCUS
 * fix the last active shareholder number
 * 
 *    Rev 1.23   Jan 14 2000 09:35:04   POPESCUS
 * get the either the last active account number or the last active shareholder number
 * 
 *    Rev 1.22   Jan 09 2000 19:11:14   POPESCUS
 * bug fixes?
 * 
 *    Rev 1.21   09 Jan 2000 17:43:34   HSUCHIN
 * default date for remarks added
 * 
 *    Rev 1.20   Jan 08 2000 15:49:20   BUZILA
 * confirmation commits its remarks
 * 
 *    Rev 1.19   Jan 08 2000 14:32:56   POPESCUS
 * added the datagroupid when quering for children lists
 * 
 *    Rev 1.18   Jan 07 2000 17:08:26   BUZILA
 * clearing out the updated flag in CBO's
 * 
 *    Rev 1.17   07 Jan 2000 10:49:50   HSUCHIN
 * for mihai
 * 
 *    Rev 1.16   Dec 24 1999 10:29:40   VASILEAD
 * Fixed NASU flow
 * 
 *    Rev 1.15   Dec 23 1999 16:47:04   BUZILA
 * avoiding transactions
 * 
 *    Rev 1.14   23 Dec 1999 15:51:04   HSUCHIN
 * commits transaction now.
 * 
 *    Rev 1.13   Dec 22 1999 10:50:16   WINNIE
 * add build transaction and commit (currently commented out)
 * 
 *    Rev 1.12   Dec 17 1999 17:53:44   DT24433
 * get DataGroupID parm
 * 
 *    Rev 1.11   Dec 17 1999 15:06:24   DT24433
 * added ok2
 * 
 *    Rev 1.10   Dec 08 1999 16:27:44   HSUCHIN
 * changed doGetField and doSetField to include groupid
 * 
 *    Rev 1.9   Nov 22 1999 15:24:30   HSUCHIN
 * redesigned and OG usage.
 * 
 *    Rev 1.8   Oct 28 1999 18:19:24   DT24433
 * removed doOk/doCancel
 * 
 *    Rev 1.7   Oct 28 1999 09:29:52   YINGZ
 * for a clean Get from PVCS!
 * 
 *    Rev 1.6   Aug 31 1999 10:33:52   DT24433
 * changed dogetfield/dosetfield parms
 * 
 *    Rev 1.5   Aug 17 1999 16:47:36   DT24433
 * removed static FieldDetails array
 * 
 *    Rev 1.4   Jul 27 1999 16:01:48   BUZILA
 * Increment M2
 * 
 *    Rev 1.3   Jul 26 1999 10:37:40   BUZILA
 * changed doGetField
 * 
 *    Rev 1.2   Jul 20 1999 11:14:00   VASILEAD
 * New conditions update
 * 
 *    Rev 1.1   Jul 08 1999 10:01:58   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
