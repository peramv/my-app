//******************************************************************************
//
// COPYRIGHT:
//
//    Th* comput;
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : ShareholderProcess.cpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 16/04/99
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : ShareholderProcess
//    This class manages the management company and profile selection.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include <ifastcbo\accshrnumcheck.hpp>

#include <bfsessn\bfawdsession.hpp>

//CP20021108#include <bfcbo\bfsessionmanager.hpp>
#include "confirmationprocessincludes.h"
#include <ifastdataimpl\dse_dstcglob_vw.hpp>
#include <bfproc\genericinterfacecontainer.hpp>
#include <ifastcbo\grouplist.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\mgmtco.hpp>
#include "nasuprocessincludes.h"
#include <ifastcbo\shareholder.hpp>
#include "shareholderprocess.hpp"
#include "shareholderprocessincludes.h"
#include <bfproc\genericinterfacecontainer.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_SHAREHOLDER;
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_ACCOUNT_DETAILS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_SHAREHOLDER;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< ShareholderProcess > processCreator( CMD_BPROC_SHAREHOLDER );

namespace 
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "ShareholderProcess" );
   const I_CHAR * const YES = I_( "Y" );
   const I_CHAR * const NO = I_( "N" );
}

namespace SHRPROC
{
   const I_CHAR * const SHAREHOLDER_NUM = I_( "ShareholderNum" );
   const I_CHAR * const ACCOUNT_NUM = I_( "AccountNum" );
   const I_CHAR * const GROUP_CODE = I_( "GroupCode" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern CLASS_IMPORT const long BP_ERR_INVALID_METHOD_CALL;
   extern const long ERR_NO_VALID_SHAREHOLDER_OR_ACCOUNT;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId ShrNumManual;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319ShareholderProcess::ShareholderProcess() : 
ShareholderProcess::ShareholderProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( NULL ),
m_bManualShr( false ),
m_bShrCreated( false ),
_pCondition(NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::SHAREHOLDER_CBO, false, BF::NullContainerId, true, I_("Shareholder") );
   addContainer( IFASTBP_PROC::GROUP_LIST, true );

   //for the shareholder
   addFieldDetails( ifds::Name1, IFASTBP_PROC::SHAREHOLDER_CBO );
   addFieldDetails( ifds::Name2, IFASTBP_PROC::SHAREHOLDER_CBO );
   addFieldDetails( ifds::FundRelnCode, IFASTBP_PROC::SHAREHOLDER_CBO );
   addFieldDetails( ifds::GroupCode, IFASTBP_PROC::SHAREHOLDER_CBO );
   addFieldDetails( ifds::GroupName1, IFASTBP_PROC::SHAREHOLDER_CBO );
   addFieldDetails( ifds::GroupName2, IFASTBP_PROC::SHAREHOLDER_CBO );
   addFieldDetails( ifds::ResProvCode, IFASTBP_PROC::SHAREHOLDER_CBO );
   addFieldDetails( ifds::TaxJurisCode, IFASTBP_PROC::SHAREHOLDER_CBO );
   addFieldDetails( ifds::Channel, IFASTBP_PROC::SHAREHOLDER_CBO );
   addFieldDetails( ifds::Confidential, IFASTBP_PROC::SHAREHOLDER_CBO );

   addFieldDetails( ifds::EffectiveDate, IFASTBP_PROC::SHAREHOLDER_CBO );
   addFieldDetails( ifds::ShrNum, BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ifds::AcctDesignation, IFASTBP_PROC::SHAREHOLDER_CBO );
   addFieldDetails( ifds::AcctDesignationDesc, IFASTBP_PROC::SHAREHOLDER_CBO );
   addFieldDetails( ifds::ConsolEFT, IFASTBP_PROC::SHAREHOLDER_CBO );

   addFieldDetails( ifds::GrpCodeLevel, BF::NullContainerId, SUBCLASS_PROCESS   );

   // for AdminDates
   addFieldDetails( ifds::ModUser, IFASTBP_PROC::SHAREHOLDER_CBO );
   addFieldDetails( ifds::ModDate, IFASTBP_PROC::SHAREHOLDER_CBO );
   addFieldDetails( ifds::ProcessDate, IFASTBP_PROC::SHAREHOLDER_CBO );
   addFieldDetails( ifds::Username, IFASTBP_PROC::SHAREHOLDER_CBO );

   addFieldDetails( SHRPROC::CREATING_SHAREHOLDER, BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( SHRPROC::SHAREHOLDER_NUM_FIELD, BF::NullContainerId, SUBCLASS_PROCESS );

   // for group list
   //addFieldDetails( DBR::rxGroupCode, SHRPROC::GROUP_LIST );
}

//******************************************************************************
ShareholderProcess::~ShareholderProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   _rpChildGI = NULL;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************
void ShareholderProcess::doGetField(
                                   const GenericInterface *rpGICaller,
                                   const BFContainerId& idContainer,
                                   const BFFieldId& idField,
                                   const BFDataGroupId& idDataGroup,
                                   DString &strValueOut,
                                   bool bFormatted
                                   ) const
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOGETFIELD );

   if( idField == ifds::ShrNum )
   {
      strValueOut = _shrNum;
      return;
   }
   else if( idField == ifds::GrpCodeLevel )
   {
      DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      dstcWorkSession->getOption( ifds::GrpCodeLevel, strValueOut, idDataGroup );
      strValueOut.strip().upperCase(); 
      return;
   }
   if( idField == SHRPROC::CREATING_SHAREHOLDER )
   {
      strValueOut = _dstrCreatingShareholder;
   }
   else if( idField == SHRPROC::SHAREHOLDER_NUM_FIELD )
   {
      strValueOut = _shrNum;
   }
   else
   {
      assert( 0 );   
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETFIELD, CND::BP_ERR_INVALID_METHOD_CALL );
   }
}

//******************************************************************************

SEVERITY ShareholderProcess::doSetField(
                                       const GenericInterface *rpGICaller,
                                       const BFContainerId& idContainer,
                                       const BFFieldId& idField,
                                       const BFDataGroupId& idDataGroup,
                                       const DString& strValue,
                                       bool bFormatted
                                       )
{  
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, CLASSNAME, I_("doSetField") );

   DString strValueCopy(strValue);  

   if( BF::NullContainerId == idContainer )
   {
      if( idField  ==  ifds::ShrNum )
      {
         if( m_bManualShr )
         {
            DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
            Shareholder* pShareholder = NULL;

            SEVERITY sevRtn = SEVERE_ERROR;
            if( _dstrCreatingShareholder == YES && _shrNum == NULL_STRING )
            {
               AccShrNumCheck acctShrNumCheck( *dstcWorkSession );
               DString dstrCalledByProc = (_dstrCreatingShareholder == YES)? I_("NASU"):NULL_STRING;

               //look for the list of account numbers for this shareholder
               
               if( acctShrNumCheck.init( strValue, dstrCalledByProc) > WARNING )
               {
                  if( _pCondition )
                     delete _pCondition;
                  _pCondition = new Condition( *GETCONDITION( 0 ));

                  return(GETCURRENTHIGHESTSEVERITY());
               }

               sevRtn = dstcWorkSession->getNewShareholder( getDataGroupId(), pShareholder, strValueCopy );
               if( sevRtn <= WARNING )
               {
                  pShareholder->getField( ifds::ShrNum, _shrNum, getDataGroupId() );
               }
               else
               {
                  sevRtn = dstcWorkSession->getShareholder( getDataGroupId(), _shrNum, pShareholder );
               }
               if( sevRtn <= WARNING )
               {
                  m_bShrCreated = true;
               }

            }
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//************************************************************************************
SEVERITY ShareholderProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      Shareholder* pShareholder = NULL;

      getParameter( NASULIT::CREATING_SHAREHOLDER, _dstrCreatingShareholder );
      getParameter( SHRPROC::SHAREHOLDER_NUM, _shrNum );

      if( _dstrCreatingShareholder != YES )
      {// search
         _shrNum.stripLeading();
         _shrNum.stripLeading( '0' );
         if( _shrNum == NULL_STRING ) //try and get the account number
         {
            DString accountNum;

            getParameter( SHRPROC::ACCOUNT_NUM, accountNum );
            accountNum.stripLeading();
            accountNum.stripLeading( '0' );
            if( accountNum == NULL_STRING )
            {
               //TODO add condition that we do not have a shareholder number and/or account num
               ADDCONDITIONFROMFILE( CND::ERR_NO_VALID_SHAREHOLDER_OR_ACCOUNT );
               return(GETCURRENTHIGHESTSEVERITY());//sever error
            }
            MFAccount *pMFAccount = NULL;
            sevRtn = dstcWorkSession->getMFAccount( getDataGroupId(), accountNum, pMFAccount, I_("N"), NULL_STRING, true, true );
            if( sevRtn <= WARNING )
            {
               pMFAccount->getField( ifds::ShrNum, _shrNum, BF::HOST );
            }

         }
         else
         {
            sevRtn = dstcWorkSession->getShareholder( getDataGroupId(), _shrNum, pShareholder, true );//force validation for ShrNum
         }
      }
      else
      {  // create new share holder

         DString shrNumCtrl;
         if( dstcWorkSession->getOption( ifds::ShrNumCtrl, shrNumCtrl, getDataGroupId() ) <= WARNING )
         {

            if( ( shrNumCtrl == I_( "M" ) || shrNumCtrl == I_( "m" ) ) )
            {// we force user to input shareholder number
               m_bManualShr = true;
               if( _shrNum == NULL_STRING )
                  m_bShrCreated = false;
               else
                  m_bShrCreated = true;

               if( !m_bShrCreated )
               {
                  return(GETCURRENTHIGHESTSEVERITY());
               }
               if( m_bShrCreated )
               {
                  sevRtn = dstcWorkSession->getShareholder( getDataGroupId(), _shrNum, pShareholder );
               }
            }

            else
            { // not manually create      
               if( _shrNum == NULL_STRING )
               {
                  sevRtn = dstcWorkSession->getNewShareholder( getDataGroupId(), pShareholder, _dstrNewShrNum );
                  if( sevRtn <= WARNING )
                  {
                     //retrieve the shareholder number from the newly created object
                     pShareholder->getField( ifds::ShrNum, _shrNum, getDataGroupId() );
                  }
               }
               else
               {
                  sevRtn = dstcWorkSession->getShareholder( getDataGroupId(), _shrNum, pShareholder );
               }

            }
         }// if option
      }// create new shareholder
   }
   catch( ConditionException& ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(sevRtn);
}

//******************************************************************************
bool ShareholderProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_SHAREHOLDER );
}

//******************************************************************************
bool ShareholderProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );

   SEVERITY sevRtn = SEVERE_ERROR;
   bool bRtn = false;

   try
   {
      assert( _rpChildGI && isValidModelessInterface( _rpChildGI ) );
      DString accountNum;
      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

      getParameter( SHRPROC::SHAREHOLDER_NUM, _shrNum );
      _shrNum.stripLeading();
      _shrNum.stripLeading( '0' );
      if( _shrNum == NULL_STRING ) //try and get the account number
      {
         DString accountNum;

         getParameter( SHRPROC::ACCOUNT_NUM, accountNum );
         accountNum.stripLeading();
         accountNum.stripLeading( '0' );
         if( accountNum == NULL_STRING )
         {
            ADDCONDITIONFROMFILE( CND::ERR_NO_VALID_SHAREHOLDER_OR_ACCOUNT );
            return(bRtn); //false
         }
         MFAccount* pMFAccount = NULL;
         sevRtn = dstcWorkSession->getMFAccount( getDataGroupId(), accountNum, pMFAccount );
         if( sevRtn <= WARNING )
         {
            pMFAccount->getField( ifds::ShrNum, _shrNum, BF::HOST );
         }
      }
      else
      {
         sevRtn = NO_CONDITION;//everything went ok, so far
      }
      //here we have a shareholder number
      //reset the container
      if( sevRtn <= WARNING )
      {
         setContainer( IFASTBP_PROC::SHAREHOLDER_CBO, NULL );
         if( !( bRtn = _rpChildGI->refresh( this, NULL ) ) )
            return(bRtn);// false
         bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
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
E_COMMANDRETURN ShareholderProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      if( !isXMLAPIContext() )
      {
         if( m_bManualShr )
            setParameter( I_("ManualShr"), YES );
         else
            setParameter( I_("ManualShr"), NO );
         if( m_bShrCreated )
            setParameter( I_("ShrCreated"), YES );
         else
            setParameter( I_("ShrCreated"), NO );
         _shrNum.strip().stripLeading('0');
         rtn = invokeCommand( this, CMD_GUI_SHAREHOLDER, getProcessType(), isModal(), &_rpChildGI );
      }
      else
      {
         setParameter( SHRPROC::SHAREHOLDER_NUM, _shrNum );
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
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(rtn);
}

//**********************************************************************
void *ShareholderProcess::getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup )
{
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, I_( "getPtrForContainer" ) );

   void *ptr = NULL;

   try
   {
      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
//CP20030319      switch( idContainer )
//CP20030319      {
//CP20030319         case SHRPROC::SHAREHOLDER_CBO:
      if( IFASTBP_PROC::SHAREHOLDER_CBO == idContainer )
      {
         {
            Shareholder *pShareholder = NULL;

            if( dstcWorkSession->getShareholder( getDataGroupId(), _shrNum, pShareholder ) <= WARNING )
            {
               ptr = pShareholder;
            }
//CP20030319               break;
         }

//CP20030319         case SHRPROC::GROUP_LIST:
      }
      else if( IFASTBP_PROC::GROUP_LIST == idContainer )
      {
         {
            Shareholder *pShareholder = dynamic_cast<Shareholder *>(getCBOItem(IFASTBP_PROC::SHAREHOLDER_CBO, idDataGroup));
            if( pShareholder )
            {
               GroupList* pGroupList = NULL;

               if( dstcWorkSession->getMgmtCo().getGroupList( pGroupList ) <= WARNING )
               {
                  ptr = pGroupList;
               }
            }

//CP20030319               break;
         }

//CP20030319         default:
      }
      else
      {
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
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(ptr);
}

//******************************************************************************
SEVERITY ShareholderProcess::ok2( GenericInterface *rpGICaller )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTBP_CONDITION, CLASSNAME, OK2 );

   try
   {
      const BFDataGroupId& idDataGroup = getDataGroupId();
      bool bSuccessFlag = false;
      bool bNeedRefresh = false;
      Shareholder* pShareholder;
      SEVERITY sevRtn = SEVERE_ERROR; 
	  bool	bWarningContinue = getIgnoreWarningsOnOk2();
      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

      if( _shrNum == NULL_STRING )
      {
         sevRtn =  dstcWorkSession->getShareholder( getDataGroupId(), _dstrNewShrNum, pShareholder );
      }
      //the shareholder has been added with the groupid of this process
//      if( pMFCBM->getShareholder( getWorkSessionID(), getDataGroupId(), 
//            _shrNum, pShareholder ) <= WARNING )
      else
      {
         sevRtn =  dstcWorkSession->getShareholder( getDataGroupId(), _shrNum, pShareholder );
      }

      if( sevRtn <= WARNING )
      {
         //although it doesn't seem right to check here if is new,
         //and to check the repository if it is updated,
         //we'll put this in, hoping in a future bfbase fix
         if( pShareholder->isNew() || dstcWorkSession->isUpdatedForDataGroup( idDataGroup ) )
         {
		 	sevRtn = pShareholder->validateAll( idDataGroup, SHAREHOLDER_GROUPING::SHAREHOLDER_INFO );
			if( sevRtn == WARNING && !bfutil::isServerContext())
            {
               bWarningContinue = rpGICaller->send( rpGICaller, I_( "WarningConfirm" ));
            }
            if(  bWarningContinue && sevRtn <= WARNING ) 
            {
               bSuccessFlag = true;
               DString strAccountNum = NULL_STRING;
               getGlobal( WORK_GLOBAL, ifds::LastActiveAccountNum, strAccountNum );

               MFAccount *pMFAccount = NULL;
               
               if(dstcWorkSession->getMFAccount (idDataGroup, 
                                                 strAccountNum, 
                                                 pMFAccount) &&
                                   pMFAccount)               
               {
                  // PET157837 FN02 Country Schedule
                  // Refresh MFAccount for check the closedcountry flag when user was updated.                  
                  pMFAccount->refreshMe (true); //refresh mfaccount   
               }
               
               //if we are in NASU, then see if the user changed the shareholder num
               if( _dstrCreatingShareholder == YES )
               {
                  //if the ShrNumManual field is set to Y we should remove the entry 
                  //of the shareholder from the repository and add a new one, and also set the params 
                  //of the flow if we are in the flow
                  /*DString shrNumManual, newShareholderNum;

                  pShareholder->getField( DBR::ShrNumManual, shrNumManual, idDataGroup );
                  //get the new shareholder number
                  pShareholder->getField( DBR::ShrNum, newShareholderNum, idDataGroup );
                  if( shrNumManual == YES )
                  {
                     //the new shareholder has been added with the group id of this process
                     BFObjIter bfIter( *dstcWorkSession, getDataGroupId() );
         
                     if( bfIter.begin( OBJ_TYPE_SHAREHOLDER, OBJ_ACTIVITY_ADDED, _shrNum ) )
                     {
                        if( !bfIter.end() )
                        {
                           //do not remove the instance of the object
                           bfIter.removeObjectFromMap( false );
                           //add the same instance of the object with a new key
                           dstcWorkSession->addObject( getDataGroupId(), 
                                                       OBJ_TYPE_SHAREHOLDER, 
                                                       newShareholderNum, 
                                                       pShareholder, 
                                                       OBJ_ACTIVITY_ADDED );
                           //refresh other things, hopefully we don't miss anything
                           _shrNum = newShareholderNum;
                           setParameter( SHRPROC::SHAREHOLDER_NUM, _shrNum );
                        }
                        else
                        {
                           assert( 0 ); //that means the shareholder is not in the repository
                           throw;
                        }
                     }
                  }*/
               }
               if( ( bfutil::isServerContext() && isModal() ) ||
                   ( !bfutil::isServerContext() && isModal() &&  getParent() && getParent()->isModal() ) )
               {
                  //commit the repository so we can commit the account, as well
                  if( dstcWorkSession->commitDataGroup( idDataGroup ) <= WARNING )
                  {  // Refresh other processes
                     bNeedRefresh = true;
                  }
                  else
                  {  // Commit failed
                     bSuccessFlag = false;
                     PROMOTECONDITIONS();
                  }
               }
            }//validate all
         }
         else
         {  // Nothing happened - make sure and remove any dummy entries added
            pShareholder->deleteNonUpdatedAddedElements( idDataGroup );
            bSuccessFlag = true;
         }
         if( bSuccessFlag )
         {
            //probably this should be done in the CBO, but now base
            //doesn't have support for commiting properties!
            //lock the shareholder number, once is validated and commited
            pShareholder->setFieldReadOnly( ifds::ShrNum, getDataGroupId(), true );

            ProcessObserver* procObserver = getProcessObserver();
            if (procObserver) {
               procObserver->notifyOk(rpGICaller, this);
            }

            if( ( bfutil::isServerContext() && !isModal() ) || 
                ( !bfutil::isServerContext() && (!isModal() || !getParent() || !getParent()->isModal() ) ) )
            {  // Possibly need confirmation if we are modeless, no parent, or our 
               // parent is modeless
               BFAwdSession *rpAwdSession = NULL;
               if( getSession() != NULL )
               {
                  rpAwdSession = getSession()->getAwdSession();
               }
               if( pShareholder->isUpdated( true ) /*||
                   ( rpAwdSession && rpAwdSession->getProcessWork() )*/ )
               {
//CP20030309                  DString str = asString( idDataGroup );
//CP20030309                  setParameter( I_( "DataGroupID" ), str );
//                  setGlobal( WORK_GLOBAL, DBR::LastActiveShrNum, _shrNum );

                  if( CMD_OK != invokeCommand( this, CMD_BPROC_CONFIRMATION,
                                               PROC_NO_TYPE, true, NULL ) )
                  {
                     DString strOut;

                     bSuccessFlag = false;
                     PROMOTECONDITIONS();
                     getParameter( I_( "TrxnsError" ), strOut );
                     if( strOut == I_( "Y" ) )
                     {  // Need to halt further activities in BaseMainDlg
                        rpGICaller->send( this, I_( "TrxnsError" ) );
                     }
                  }
                  else
                  {  // Force refresh for now - but not needed for all cases
                     bNeedRefresh = true;
                  }
               }
            }
            if( bNeedRefresh )
            {
               getGIContainer()->refresh( this );
            }
         }
      }
      if( bSuccessFlag )
      {
         return(NO_CONDITION);
      }
      return(SEVERE_ERROR);
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
   return(GETCURRENTHIGHESTSEVERITY());
}
//***************************************************************************
SEVERITY ShareholderProcess::fireCrossEdit(
                                          const GenericInterface *rpGICaller,
                                          const BFContainerId& idContainer,
                                          const BFFieldId& idCrossEdit,
                                          long lValidateGroup 
                                          )
{
   return(AbstractProcess::fireCrossEdit(
                                        rpGICaller,
                                        idContainer,
                                        idCrossEdit,
                                        isXMLAPIContext()? SHAREHOLDER_GROUPING::SHAREHOLDER_INFO : 0
                                        ));
}

//******************************************************************************
SEVERITY ShareholderProcess::doGetErrors( const GenericInterface *rpGICaller, const BFContainerId& idContainer,
                                          const BFFieldId& idField, const BFDataGroupId& idDataGroup, CONDITIONVECTOR &conditions ) const
{

   SEVERITY sevRtn = NO_CONDITION;

   if( idField == ifds::ShrNum )
   {
      if( _pCondition )
         conditions.push_back( _pCondition );
   }
   else
   {
      sevRtn = AbstractProcess::doGetErrors( rpGICaller, idContainer, idField, idDataGroup, conditions );
   };
   return(sevRtn);

}

//******************************************************************************

SEVERITY ShareholderProcess::getHistoricalParameters( 
   const BFContainerId& idContainer, 
   HISTORICAL_VECTOR &vectorHistorical )
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/ShareholderProcess.cpp-arc  $
 * 
 *    Rev 1.44   Feb 17 2012 10:04:10   popescu
 * refresh portfolio - temporary backed the code out.
 * 
 *    Rev 1.43   Feb 08 2012 20:42:22   dchatcha
 * IN# 2837678 - REL12.2-PET0186484- New INA Contract Information screen issues as on 6 Feb 2012
 * 
 *    Rev 1.42   Feb 07 2012 18:10:22   dchatcha
 * IN# 2837678 - REL12.2-PET0186484- New INA Contract Information screen issues as on 6 Feb 2012
 * 
 *    Rev 1.41   Jan 27 2010 17:56:10   wutipong
 * IN1877040 -- More fix to remove hard-coding.
 * 
 *    Rev 1.40   Jun 09 2009 05:47:18   kitticha
 * PET157837 FN02 - Country Schedule Daily Non Resident Schedule A
 * 
 *    Rev 1.39   Aug 25 2004 16:51:56   HERNANDO
 * PTS 10033324 - Ignore reference to the AWD Work Object in determining whether to launch the Confirmation Dialog.
 * 
 *    Rev 1.38   Mar 10 2004 10:23:42   HERNANDO
 * PET965 FN11 - Added getHistoricalParameters.
 * 
 *    Rev 1.37   Aug 21 2003 09:26:34   linmay
 * added field Confidential and Channel
 * 
 *    Rev 1.36   May 22 2003 14:11:44   popescu
 * Replaced name 'BankInstr' with 'BankInstructions'; 
 * simplified child lists getters for the Shareholder object
 * 
 *    Rev 1.35   Apr 03 2003 13:45:22   linmay
 * clean up for sec
 * 
 *    Rev 1.34   Mar 21 2003 17:48:06   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.33   Mar 09 2003 15:56:40   PURDYECH
 * Small fixes around DataGroupIds and ContainerIds.
 * 
 *    Rev 1.32   Nov 18 2002 10:55:28   PURDYECH
 * BFObjectKey changes.
 * 
 *    Rev 1.31   Oct 09 2002 23:53:36   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.30   Sep 04 2002 15:45:48   PURDYECH
 * Condition, comment and formatting cleanup
 * 
 *    Rev 1.29   Aug 29 2002 16:45:16   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.28   Aug 29 2002 12:54:40   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.27   Jul 05 2002 17:08:22   HSUCHIN
 * bug fix for serverContext checks and AbstractProcess changes
 * 
 *    Rev 1.26   Jul 03 2002 15:53:28   SMITHDAV
 * Fix commit logic for server context.
 * 
 *    Rev 1.25   May 28 2002 12:18:04   PURDYECH
 * BFData Implementation - Phase II
 * 
 *    Rev 1.24   22 May 2002 18:25:04   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.23   27 Mar 2002 19:55:40   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.22   08 Feb 2002 16:50:12   KOVACSRO
 * Force validation for Shareholder number
 * 
 *    Rev 1.21   Nov 14 2001 15:35:34   YINGBAOL
 * code Clean up
 * 
 *    Rev 1.20   Nov 07 2001 16:45:16   YINGBAOL
 * do not check if it is create shareholder or not when getting GroupList
 * 
 *    Rev 1.19   Nov 05 2001 17:15:02   YINGBAOL
 * GroupLevel is obtained from option instead of shareholder
 * 
 *    Rev 1.18   Aug 31 2001 12:38:18   YINGBAOL
 * strip leading 0 for shareholder
 * 
 *    Rev 1.17   Aug 30 2001 17:13:02   YINGBAOL
 * change logic for search and create shareholder
 * 
 *    Rev 1.16   15 May 2001 15:38:54   YINGZ
 * data group id clean up
 * 
 *    Rev 1.15   11 May 2001 16:33:36   YINGZ
 * code sync up
 * 
 *    Rev 1.14   03 May 2001 14:05:44   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.13   Feb 28 2001 15:42:02   YINGZ
 * override fireCrossEdit to support validategroup
 * 
 *    Rev 1.12   Feb 21 2001 11:33:56   YINGZ
 * make api nasu work
 * 
 *    Rev 1.11   Feb 12 2001 15:50:14   YINGZ
 * add apinasu
 * 
 *    Rev 1.10   15 Dec 2000 12:43:52   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.9   Nov 02 2000 14:11:32   VASILEAD
 * Added workSeesionId parameter for Mgmtco based CBOs
 * 
 *    Rev 1.8   Oct 06 2000 13:44:02   HERNANDO
 * Preventive measure; ensure session exists before getAwdSession
 * 
 *    Rev 1.7   Sep 22 2000 11:51:00   ZHANGCEL
 * Fixed the bug for manually entering a new shareholder number
 * 
 *    Rev 1.6   Aug 16 2000 10:39:30   DINACORN
 * Added addFieldDetails()for Group
 * 
 *    Rev 1.5   Aug 02 2000 15:32:04   BUZILA
 * "locale" changes
 * 
 *    Rev 1.4   Apr 04 2000 17:54:06   DT24433
 * changed to use getGIContainer
 * 
 *    Rev 1.3   Mar 31 2000 14:29:26   HSUCHIN
 * minor change
 * 
 *    Rev 1.2   Mar 30 2000 11:32:08   HSUCHIN
 * M2 Sync up
 * 
 *    Rev 1.1   Mar 08 2000 09:58:06   HSUCHIN
 * added Canadian stuff
 * 
 *    Rev 1.0   Feb 15 2000 10:59:38   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.45   Feb 07 2000 18:18:54   POPESCUS
 * returned SEVERE_ERROR in ok2 instead of GETCURRENTHIGHESTSEVERITY if succes flag is false
 * 
 *    Rev 1.44   Jan 26 2000 19:44:54   POPESCUS
 * fixes for th release
 * 
 *    Rev 1.43   Jan 25 2000 17:14:24   POPESCUS
 * fixes for validation of a new account
 * 
 *    Rev 1.42   Jan 23 2000 18:46:50   POPESCUS
 * changes related to refresh and creating a sales rep on the fly
 * 
 *    Rev 1.41   Jan 21 2000 11:11:36   POPESCUS
 * the user can change the account number and the shareholder number
 * 
 *    Rev 1.40   Jan 19 2000 15:31:52   POPESCUS
 * fixes in Shareholder
 * 
 *    Rev 1.39   Jan 17 2000 14:00:28   POPESCUS
 * support for refresh and misc
 * 
 *    Rev 1.38   Jan 14 2000 18:08:54   POPESCUS
 * set the last active account num
 * 
 *    Rev 1.37   Jan 12 2000 08:58:20   POPESCUS
 * changes related to cloning an account and fixing some validation, adding subst sets
 * 
 *    Rev 1.36   Dec 29 1999 12:23:34   DT24433
 * removed substitute lists
 * 
 *    Rev 1.35   Dec 21 1999 14:14:40   POPESCUS
 * cleanup the code, validations and misc
 * 
 *    Rev 1.34   Dec 09 1999 18:47:36   DT24433
 * removed Ok2 & doRefresh to allow base processing
 * 
 *    Rev 1.33   Dec 02 1999 11:16:00   POPESCUS
 * fixed crash in searc
 * 
 *    Rev 1.32   Nov 29 1999 11:26:40   POPESCUS
 * Fixes in NASU flow
 * 
 *    Rev 1.31   Nov 28 1999 14:39:20   POPESCUS
 * ?
 * 
 *    Rev 1.30   Nov 25 1999 17:09:00   POPESCUS
 * 
 *    Rev 1.29   Nov 23 1999 18:05:40   POPESCUS
 * NASU flow
 * 
 *    Rev 1.28   Nov 15 1999 10:41:26   ZHANGCEL
 * change rxShrNum to ShrNum
 * 
 *    Rev 1.27   Nov 10 1999 12:52:32   ZHANGCEL
 * modify
 * 
 *    Rev 1.25   Nov 08 1999 15:24:04   ZHANGCEL
 * add mechanism for ShrNumCtrl and DefaultGrp
 * 
 *    Rev 1.24   Nov 02 1999 16:49:04   DT24433
 * removed doOk/doCancel
 * 
 *    Rev 1.23   Nov 01 1999 13:16:48   ZHANGCEL
 * add a new cbo field
 * 
 *    Rev 1.22   Oct 29 1999 11:30:16   BUZILA
 * changing WorkSessionDetails into a BFBase descendant
 * 
 *    Rev 1.21   Oct 29 1999 09:51:48   ZHANGCEL
 * add a field in shareholder cbo
 * 
 *    Rev 1.20   Oct 27 1999 10:15:38   ZHANGCEL
 * add new process for GroupList
 * 
 *    Rev 1.19   Oct 06 1999 17:16:08   PRAGERYA
 * Obsolete field removed
 * 
 *    Rev 1.18   Sep 24 1999 10:09:38   PRAGERYA
 * "Milestone" check in
 * 
 *    Rev 1.17   Sep 20 1999 10:19:48   BUZILA
 * changet get field to return void
 * 
 *    Rev 1.16   Sep 01 1999 16:05:48   BUZILA
 * added addFieldDetails for :AcctDesignation
 * 
 *    Rev 1.15   Sep 01 1999 12:36:56   DT24433
 * changed doGetField/doSetField parms
 * 
 *    Rev 1.14   Sep 01 1999 12:05:10   PRAGERYA
 * Enhancing implementation for Incr 2
 * 
 *    Rev 1.13   Aug 26 1999 16:08:50   PRAGERYA
 * Implementing Search for Shareholder and Account Info
 * 
 *    Rev 1.12   Aug 20 1999 09:06:32   DT24433
 * removed static FieldDetails array
 * 
 *    Rev 1.11   Aug 18 1999 15:57:24   PRAGERYA
 * Bug fixes
 * 
 *    Rev 1.10   Aug 08 1999 19:32:04   PRAGERYA
 * All in!
 * 
 *    Rev 1.9   Aug 04 1999 09:36:10   PRAGERYA
 * Implementing process
 * 
 *    Rev 1.8   Jul 30 1999 17:24:06   PRAGERYA
 * Coded to the level of Incr1
 * 
 *    Rev 1.7   Jul 27 1999 14:07:26   BUZILA
 * fix
 * 
 *    Rev 1.6   Jul 23 1999 15:46:00   YINGZ
 * 
 *    Rev 1.5   Jul 23 1999 15:34:38   SMITHDAV
 * m21
 * 
 *    Rev 1.2   Jul 20 1999 11:14:14   VASILEAD
 * New conditions update
 * 
 *    Rev 1.1   Jul 08 1999 10:02:12   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
