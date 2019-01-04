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
// ^FILE   : AccInfoProcess.cpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 06/04/99
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : AccInfoProcess
//    This class manages the management company and profile selection.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "accinfoprocess.hpp"
#include <ifastcbo\accountentityxref.hpp>
#include <ifastcbo\accountentityxrefobject.hpp>
#include "accinfoprocessincludes.h"
#include "accdetailsprocessincludes.h"
#include "shareholderprocessincludes.h"
#include <ifastcbo\accshrnumcheck.hpp>
#include <ifastcbo\agentlist.hpp>

#include <bfsessn\bfawdsession.hpp>

#include <ifastcbo\branchlist.hpp>
#include <ifastcbo\brokerlist.hpp>
#include "confirmationprocessincludes.h"
#include <ifastdataimpl\dse_dstcglob_vw.hpp>
#include <ifastcbo\grouplist.hpp>
#include <ifastcbo\dstcommonfunction.hpp>
#include <bfproc\genericinterfacecontainer.hpp>
#include "entityprocessincludes.h"
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\mfaccountlist.hpp>
#include <ifastcbo\mgmtco.hpp>
#include "nasuprocessincludes.h"
#include <ifastcbo\shareholder.hpp>
#include <ifastcbo\taxtyperulelist.hpp>
#include "shareholderprocessincludes.h"
#include <bfproc\genericinterfacecontainer.hpp>
#include <ifastdataimpl\dse_dstc0091_vw.hpp>
#include <ifastdataimpl\dse_dstc0092_vw.hpp>
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_ACCINFO;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ENTITY;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_COA;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ADDRESSES;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ACCINFO;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< AccInfoProcess > processCreator( CMD_BPROC_ACCINFO );

namespace ACCINFOPROC
{
   // Trace literals
   const I_CHAR * const ACCOUNT_NUM = I_( "AccountNum" );
   const I_CHAR * const SHAREHOLDER_NUM = I_( "ShareholderNum" );
   const I_CHAR * const ENTITY_ID = I_( "EntityId" );
   const I_CHAR * const MODEL_ACCOUNT_NUM = I_( "ModelAccountNum" );
}

namespace ADDRLIT
{
   extern const I_CHAR * const ACCOUNT_NUM;
   extern const I_CHAR * const ADDRESS_CODE;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "AccInfoProcess" );
   const I_CHAR * const PERFORMSEARCH = I_( "performSearch" );
   const I_CHAR * const YES = I_( "Y" );
   const I_CHAR * const NO = I_( "N" );
   const DString EMPTY_STRING;
   const I_CHAR * const ACCOUNT_OWNER_ENTITY_TYPE           = I_( "01" );
   const I_CHAR * const NOMINEE_OWNER_ENTITY_TYPE           = I_( "21" );
   
   const I_CHAR * const SHAREHOLDER_GROUP_LEVEL = I_( "S" );
}

namespace CND
{
   extern CLASS_IMPORT const long ERR_MULTIPLE_ACCT_OWNER_NEEDED;
   extern CLASS_IMPORT const long INFO_SHAREHOLDER_HAS_MULTIPLE_ADDRESSES;
   extern CLASS_IMPORT const long ERR_NO_SLSREP_FOUND;
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern CLASS_IMPORT const long BP_ERR_INVALID_METHOD_CALL;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId AccountNumManual;
   extern CLASS_IMPORT const BFTextFieldId CreateRep;
   extern CLASS_IMPORT const BFTextFieldId ShouldAskForRep;
   extern CLASS_IMPORT const BFTextFieldId MarketMailChgSh;
   extern CLASS_IMPORT const BFTextFieldId ShouldAskForMail;
   extern CLASS_IMPORT const BFTextFieldId DataFound;
   extern CLASS_IMPORT const BFTextFieldId ShouldAskForSWPStop;
   extern CLASS_IMPORT const BFTextFieldId StopSWP;
   extern CLASS_IMPORT const BFTextFieldId Rebalance;
   extern CLASS_IMPORT const BFTextFieldId HouseBroker;
   extern CLASS_IMPORT const BFTextFieldId UpdatePACSWP;
   extern CLASS_IMPORT const BFTextFieldId TaxTypeScheduleApplicable;
   extern CLASS_IMPORT const BFTextFieldId ProdPortfolioUUID;
   extern CLASS_IMPORT const BFTextFieldId ProdPortfolioPlanUUID;
   extern CLASS_IMPORT const BFTextFieldId PortfolioPlanName;
   extern CLASS_IMPORT const BFTextFieldId DefaultPlan;
   extern CLASS_IMPORT const BFTextFieldId PortfolioName;
   extern CLASS_IMPORT const BFDateFieldId TaxableTrustDate;
   extern CLASS_IMPORT const BFDateFieldId ExemptPeriod;
}

extern CLASS_IMPORT BF_OBJ_TYPE OBJ_TYPE_MFACCOUNT;

//******************************************************************************
//              Public Methods
//******************************************************************************
//CP20030319AccInfoProcess::AccInfoProcess() : 
AccInfoProcess::AccInfoProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( NULL ),
m_bManualAccNum(false),
_pCondition(NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   //add containers
   addContainer( IFASTBP_PROC::MFACCOUNT_CBO, false, BF::NullContainerId, true, I_("Account") );

   //for MFACCOUNT_CBO
   addFieldDetails( ifds::TaxType, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::AcctType, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::BrokerCode, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::BrokerName, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::BranchCode, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::BranchName, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::SocialCode, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::AMSCode, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::StopSWP, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::FirstEffective, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::Rebalance, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::StopAMSRebalancing, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::UpdatePACSWP, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::AccountClosingReason, IFASTBP_PROC::MFACCOUNT_CBO  );
   addFieldDetails( ifds::TaxTypeSchedule, IFASTBP_PROC::MFACCOUNT_CBO  );

   addFieldDetails( ifds::ProdPortfolioUUID, IFASTBP_PROC::MFACCOUNT_CBO  );
   addFieldDetails( ifds::ProdPortfolioPlanUUID, IFASTBP_PROC::MFACCOUNT_CBO  );

   //special handling
   addFieldDetails( ifds::Slsrep, IFASTBP_PROC::MFACCOUNT_CBO  );
   addFieldDetails( ifds::SlsrepName, IFASTBP_PROC::MFACCOUNT_CBO  );
   addFieldDetails( ifds::SlsrepAltName, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::AccountNum, BF::NullContainerId , SUBCLASS_PROCESS);
   addFieldDetails( ifds::AltAccount, IFASTBP_PROC::MFACCOUNT_CBO  );
   addFieldDetails( ifds::BeneficialOwner, IFASTBP_PROC::MFACCOUNT_CBO  );
   addFieldDetails( ifds::XrefNum, IFASTBP_PROC::MFACCOUNT_CBO  );
   addFieldDetails( ifds::RecipientType, IFASTBP_PROC::MFACCOUNT_CBO  );
   addFieldDetails( ifds::PensionJuris, IFASTBP_PROC::MFACCOUNT_CBO  );
   addFieldDetails( ifds::Currency, IFASTBP_PROC::MFACCOUNT_CBO  );
   addFieldDetails( ifds::MarketMail, IFASTBP_PROC::MFACCOUNT_CBO  );
   addFieldDetails( ifds::EffectiveDate, IFASTBP_PROC::MFACCOUNT_CBO  );
   addFieldDetails( ifds::DateOfReg, IFASTBP_PROC::MFACCOUNT_CBO  );
   addFieldDetails( ifds::AcctStatus, IFASTBP_PROC::MFACCOUNT_CBO  );
   addFieldDetails( ifds::InterCode, IFASTBP_PROC::MFACCOUNT_CBO  );
   addFieldDetails( ifds::InterAccount, IFASTBP_PROC::MFACCOUNT_CBO  );
   addFieldDetails( ifds::InTrustFor, IFASTBP_PROC::MFACCOUNT_CBO  );
   addFieldDetails( ifds::Escrow, IFASTBP_PROC::MFACCOUNT_CBO  );
   addFieldDetails( ifds::RegCompleted, IFASTBP_PROC::MFACCOUNT_CBO  );
   addFieldDetails( ifds::AcctDesignation, IFASTBP_PROC::MFACCOUNT_CBO  );
   addFieldDetails( ifds::ShrNum, IFASTBP_PROC::MFACCOUNT_CBO  );
   addFieldDetails( ifds::CreateRep, IFASTBP_PROC::MFACCOUNT_CBO  );
   addFieldDetails( ifds::MarketMailChgSh, IFASTBP_PROC::MFACCOUNT_CBO  );
   addFieldDetails( ifds::RRSPFee, IFASTBP_PROC::MFACCOUNT_CBO  );
   addFieldDetails( ifds::AcctPurpose, IFASTBP_PROC::MFACCOUNT_CBO  );
   addFieldDetails( ifds::AdditionalInfo, IFASTBP_PROC::MFACCOUNT_CBO  );
   addFieldDetails( ifds::BusinessNo, IFASTBP_PROC::MFACCOUNT_CBO  );
   addFieldDetails( ifds::PensionLegCode, IFASTBP_PROC::MFACCOUNT_CBO  );
   addFieldDetails( ifds::RegistrationInfo, IFASTBP_PROC::MFACCOUNT_CBO  );
   addFieldDetails( ifds::TaxTypeScheduleApplicable, IFASTBP_PROC::MFACCOUNT_CBO );

   //this is put here so the GUI can be notified that it should ask for rep
   addFieldDetails( ifds::ShouldAskForRep, IFASTBP_PROC::MFACCOUNT_CBO  );
   addFieldDetails( ifds::ShouldAskForMail, IFASTBP_PROC::MFACCOUNT_CBO  );
   addFieldDetails( ifds::ShouldAskForSWPStop, IFASTBP_PROC::MFACCOUNT_CBO  );


   //for AdminDates
   addFieldDetails( ifds::ModDate, IFASTBP_PROC::MFACCOUNT_CBO  );
   addFieldDetails( ifds::ModUser, IFASTBP_PROC::MFACCOUNT_CBO  );
   addFieldDetails( ifds::ProcessDate, IFASTBP_PROC::MFACCOUNT_CBO  );
   addFieldDetails( ifds::Username, IFASTBP_PROC::MFACCOUNT_CBO  );

   addFieldDetails( ifds::AcctGroup, IFASTBP_PROC::MFACCOUNT_CBO  );
   addFieldDetails( ifds::AcctGroupName, IFASTBP_PROC::MFACCOUNT_CBO  );
   addFieldDetails( ifds::GrpCodeLevel, IFASTBP_PROC::MFACCOUNT_CBO  );
   addFieldDetails( ifds::ClearingFirm, IFASTBP_PROC::MFACCOUNT_CBO  );
   addFieldDetails( ifds::UnclmRemitDate, IFASTBP_PROC::MFACCOUNT_CBO  );  
   addFieldDetails( ifds::ExemptPeriod, IFASTBP_PROC::MFACCOUNT_CBO  );
   addFieldDetails( ifds::TaxableTrustDate, IFASTBP_PROC::MFACCOUNT_CBO  );
   addFieldDetails( ifds::InvestorClassification, IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::AIFMDInvestorCategory, IFASTBP_PROC::MFACCOUNT_CBO  );
   addFieldDetails( ifds::AcctTaxModel, IFASTBP_PROC::MFACCOUNT_CBO  );

   //for SUBCLASS_PROCESS
   addFieldDetails( ACCINFOPROC::CREATING_ACCOUNT_FIELD,       BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ACCINFOPROC::ACCOUNT_NUMBER_FIELD,         BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ACCINFOPROC::GRP_CODE_LEVEL_FIELD,         BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ACCINFOPROC::ACCOUNT_INFO_CHANGED,         BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ACCINFOPROC::REP_BY_BRANCH_FIELD,          BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ACCINFOPROC::TITLE_FIELD,                  BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ifds::HouseBroker,                         BF::NullContainerId, SUBCLASS_PROCESS );
//   addFieldDetails( ACCINFOPROC::CREATING_SHAREHOLDER_FIELD,   BF::NullContainerId, SUBCLASS_PROCESS );
//   addFieldDetails( ACCINFOPROC::SHAREHOLDER_NUMBER_FIELD,     BF::NullContainerId, SUBCLASS_PROCESS );


}

//******************************************************************************
AccInfoProcess::~AccInfoProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   _rpChildGI = NULL;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************
SEVERITY AccInfoProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOINIT );

   try
   {
      MFAccount* pMFAccount = NULL;
      //if it is creating_account is Y then we should create a new one
      DSTCWorkSession* pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

      getParameter (NASULIT::CREATING_SHAREHOLDER, _creatingShareholder);
      getParameter (NASULIT::CREATING_ACCOUNT, _creatingAccount);
      getParameter (ACCINFOPROC::ACCOUNT_NUM, _accountNum);
      getParameter (ACCINFOPROC::SHAREHOLDER_NUM, _shareholderNum);
      getParameter (ACCINFOPROC::MODEL_ACCOUNT_NUM, _modelAccountNum);
      getParameter (NASULIT::CanCelAfterAccountInfo, _CancelAfterAccountInfo);
      getParameter (I_("FromScreen"), _fromScreen);

      _shareholderNum.strip();

      DString accNumCtrl;

      pDSTCWorkSession->getOption (ifds::AcctNumCtrl, accNumCtrl, getDataGroupId());
      accNumCtrl.strip().upperCase();
      if (accNumCtrl == I_("M"))
      {
         if (_creatingAccount == YES && 
               _CancelAfterAccountInfo != I_("Y"))
         {
            _accountNum = NULL_STRING;
            m_bManualAccNum = true;
            m_bAccCreated = false;
         }
      }
      else if (_creatingAccount == YES && 
            _accountNum.stripLeading('0') == NULL_STRING)
      { //create a new account object
         if (pDSTCWorkSession->getNewMFAccount (getDataGroupId(), _shareholderNum, pMFAccount) <= WARNING)
         {
            m_bAccCreated = true;
            //get the account number
            pMFAccount->getField (ifds::AccountNum, _accountNum, getDataGroupId());
            if (_creatingShareholder == NO) //get some of the data from the model account
            {
//clone this account from model
               pMFAccount->cloneFromModel (_modelAccountNum, getDataGroupId());
            }
         }
      }
      else if (_accountNum != NULL_STRING) //get an existing account object
      {
         if (pDSTCWorkSession->getMFAccount(getDataGroupId(), _accountNum, 
               pMFAccount, I_("N"), NULL, true, true) <= WARNING)//validate Account Num 
         {
            if (pMFAccount)
            {
               if (_creatingAccount == YES)
               {
                  pMFAccount->setAccountDesignation (getDataGroupId());
				  
				  DString grpCodeLevel;
				  
					pDSTCWorkSession->getOption( ifds::GrpCodeLevel, grpCodeLevel, getDataGroupId(), false );
					if( grpCodeLevel == SHAREHOLDER_GROUP_LEVEL ) 
					{
						DString acctGroupCode, acctGroupName;
						Shareholder *pShareholder;
						if(pDSTCWorkSession->getShareholder(getDataGroupId(), _shareholderNum, pShareholder) <=WARNING && 
							pShareholder)
						{
							pShareholder->getField( ifds::GroupCode, acctGroupCode, getDataGroupId(), false );
							pShareholder->getField( ifds::GroupName1, acctGroupName, getDataGroupId(), false);

							pMFAccount->setField( ifds::AcctGroup, acctGroupCode, getDataGroupId(), false, true );
							pMFAccount->setField( ifds::AcctGroupName, acctGroupName, getDataGroupId(), false, true );
						}
					}
               }
               else 
               {
                  DString dstrAcctDesignation;

                  pMFAccount->getField (ifds::ShrNum, _shareholderNum, getDataGroupId());
                  pMFAccount->getField (ifds::AcctDesignation, dstrAcctDesignation, getDataGroupId());
                  if (dstrAcctDesignation == I_("3")) // Intermediary
                  {
                     pMFAccount->loadIntermCodeSubstitutionList (getDataGroupId());
                  }
               }
            }
         }
      }
      if (GETCURRENTHIGHESTSEVERITY() <= WARNING && pMFAccount)
      {
         //register CBO with base
         setContainer (IFASTBP_PROC::MFACCOUNT_CBO, pMFAccount);
      }
   }
   catch (ConditionException &ce)
   {
      SETCONDITIONFROMEXCEPTION (ce);
   }
   catch ( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void AccInfoProcess::doGetField(
                               const GenericInterface *rpGICaller,
                               const BFContainerId& idContainer,
                               const BFFieldId& idField,
                               const BFDataGroupId& idDataGroup, 
                               DString &strValueOut,
                               bool bFormatted
                               ) const
{  
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOGETFIELD );
   DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   if( BF::NullContainerId == idContainer )
   {
      if( idField == ifds::AccountNum )
      {
         strValueOut = _accountNum;
         return;
      }

      if( idField == ACCINFOPROC::CREATING_ACCOUNT_FIELD )
      {
         strValueOut = _creatingAccount;
      }
      else if( idField == ACCINFOPROC::ACCOUNT_NUMBER_FIELD )
      {
         strValueOut = _accountNum;
      }
      else if( idField == ACCINFOPROC::GRP_CODE_LEVEL_FIELD )
      {
         dstcWorkSession->getOption( ifds::GrpCodeLevel, strValueOut, idDataGroup );
         strValueOut.strip().upperCase();
      }
      else if( idField == ACCINFOPROC::REP_BY_BRANCH_FIELD )
      {
         dstcWorkSession->getOption( ifds::RepByBranch, strValueOut, idDataGroup );
         strValueOut.strip().upperCase();
      }
      else if( idField == ACCINFOPROC::TITLE_FIELD )
      {
         strValueOut.empty();
        
         strValueOut = I_(": ");

         DString strShareholderNumber = _shareholderNum; 
         strShareholderNumber.strip().stripLeading('0');
         strValueOut += I_(" Shareholder: ") + strShareholderNumber;
			if( _creatingAccount == NO )
         {
            DString accNumCtrl;
            if( dstcWorkSession->getOption( ifds::AcctNumCtrl, accNumCtrl, idDataGroup ) <= WARNING )
            {
               if( accNumCtrl == I_( "M" ) || accNumCtrl == I_( "m" ) )
               {
                  if( _accountNum == NULL_STRING )
                     return;
               }

            }

            DString strAccountNumber = _accountNum; 
            strAccountNumber.strip().stripLeading('0');
            if( _creatingAccount == NO )
            {
               strValueOut += I_("; Account Nbr.: ") + strAccountNumber;
            }

            DString strEntityName;
            dstcWorkSession->getFirstSequenced01AccountholderEntityName( getDataGroupId(), 
                                                                         strAccountNumber, 
                                                                         strEntityName );
            strValueOut += I_("; ") + strEntityName;
         }
      }
      else if( idField == ACCINFOPROC::ACCOUNT_INFO_CHANGED )
      {
         MFAccount* pMFAccount;
         if( dstcWorkSession->getMFAccount( getDataGroupId(), _accountNum, pMFAccount ) <= WARNING )
         {
            if( pMFAccount->isUpdatedForDataGroup(idDataGroup, false ) )
            {
               strValueOut = YES;
            }
            else strValueOut = NO;
         }
      }
      else if ( idField == ifds::HouseBroker ) {
         MFAccount* pMFAccount;
         if( dstcWorkSession->getMFAccount( getDataGroupId(), _accountNum, pMFAccount ) <= WARNING ) {
            strValueOut = pMFAccount->isHouseBroker(getDataGroupId())?YES:NO;
         }
      }	  
      else
      {
         assert( 0 );   
         THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETFIELD, CND::BP_ERR_INVALID_METHOD_CALL );
      }
   }
}

//******************************************************************************

bool AccInfoProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_ACCINFO );
}

//******************************************************************************
bool AccInfoProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );

   SEVERITY severity = SEVERE_ERROR;
   bool bRtn = false;

   try
   {
      assert( _rpChildGI && isValidModelessInterface( _rpChildGI ) );

      //just get the new param, and then force a refresh
      getParameter( ACCINFOPROC::ACCOUNT_NUM, _accountNum );
      //reset the container
      setContainer( IFASTBP_PROC::MFACCOUNT_CBO, NULL );
      if( !( bRtn = _rpChildGI->refresh( this, NULL ) ) )
         return(bRtn);// false
      bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
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
E_COMMANDRETURN AccInfoProcess::doProcess()
{  
   MAKEFRAME2( CND::IFASTBP_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      if( !isXMLAPIContext() )
      {
			setParameter( ACCINFOPROC::SHAREHOLDER_NUM, _shareholderNum );
         if( m_bManualAccNum )
            setParameter( I_("ManualAccount"), YES );
         else
            setParameter( I_("ManualAccount"), NO );
         if( m_bAccCreated )
            setParameter( I_("AccountCreated"), YES );
         else
            setParameter( I_("AccountCreated"), NO );
         setParameter( I_("FromScreen"), _fromScreen );

         rtn = invokeCommand( this, CMD_GUI_ACCINFO, getProcessType(), isModal(), &_rpChildGI );
      }
      else
      {
         setParameter( SHRPROC::ACCOUNT_NUM, _accountNum );
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
void *AccInfoProcess::getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup )
{
   MAKEFRAME2( CND::IFASTBP_CONDITION, CLASSNAME, I_( "getPtrForContainer" ) );

   void *ptr = NULL;

   try
   {
      if (IFASTBP_PROC::MFACCOUNT_CBO == idContainer)
      {
         MFAccount *pMFAccount = NULL;

         if (dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getMFAccount (
               getDataGroupId(), 
               _accountNum, 
               pMFAccount) <= WARNING)
         {
            ptr = pMFAccount;
         }
      }
   }
   catch (ConditionException &)
   {
      throw;
   }
   catch (...)
   {
      assert (0);
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return ptr;
}

//******************************************************************************
bool AccInfoProcess::doCancel( GenericInterface * rpGICaller )
{
   bool bRet = false;
   DString accNumCtrl;
   DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   dstcWorkSession->getOption( ifds::AcctNumCtrl, accNumCtrl, getDataGroupId()  );       
   accNumCtrl.upperCase();

   if( _creatingAccount == YES && _creatingShareholder == NO ||
       _creatingAccount == YES && accNumCtrl == I_( "M" ) ) // we should also remove the object if Manually create acount
   {
      if( !m_bAccCreated )
      {
         bRet = true;
      }
      else
      {
         DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
         MFAccount* pMFAccount = NULL;

         //we do this rollback here, because we want to remove the new account (the cloned one),
         //that has been created; since this account was created with the group id,
         //of the process we will rollback it with that group id;
         if( dstcWorkSession->getMFAccount( getDataGroupId(), _accountNum, pMFAccount ) <= WARNING )
         {
            if( pMFAccount->rollbackClone( getDataGroupId() ) <= WARNING )
            {
               //but we have to remove the account by hand from the repository, a
               //global rollback will not do
               //the new account has been added with the group id of this process
               BFObjIter bfIter( *dstcWorkSession, getDataGroupId() );

               if( bfIter.begin( OBJ_TYPE_MFACCOUNT, OBJ_ACTIVITY_ADDED, _accountNum ) )
               {
                  if( !bfIter.end() )
                  {
                     //remove the instance of the object
                     bfIter.removeObjectFromMap( true );
                     bRet = true;
                  }
               }
            }
         }
      }

   }
   // clear temp account num
   else if( _creatingAccount == YES )
   {
      setGlobal( WORK_GLOBAL, ifds::LastActiveAccountNum, I_("0") );
      bRet = true;
   }
   if( _creatingShareholder == YES )
   {
      if( accNumCtrl == I_( "M" ) )
      {

         setGlobal( WORK_GLOBAL, ifds::LastActiveAccountNum, NULL_STRING );
         setParameter(ACCINFOPROC::ACCOUNT_NUM, NULL_STRING);     

      }
      if( _CancelAfterAccountInfo == YES )
		{
			setParameter(ACCINFOPROC::ACCOUNT_NUM, _accountNum);
		}
      else
		{
			setParameter(ACCINFOPROC::ACCOUNT_NUM, NULL_STRING);
		}

      bRet = true;
   }
   else
   {
      bRet = true;
   }
   return(bRet);
}

//******************************************************************************
SEVERITY AccInfoProcess::ok2( GenericInterface *rpGICaller )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTBP_CONDITION, CLASSNAME, OK2 );

   try
   {
      AccountEntityXref* pAccountEntityXref = NULL;
      const BFDataGroupId& idDataGroup = getDataGroupId();
      bool bSuccessFlag = false;
      bool bNeedRefresh = false;
      MFAccount* pMFAccount;
      SEVERITY sevRtn = NO_CONDITION;

      DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

      if( dstcWorkSession->getAccountEntityXref( idDataGroup, pAccountEntityXref ) <= WARNING && 
          dstcWorkSession->getMFAccount( idDataGroup, _accountNum, pMFAccount ) <= WARNING )
      {
         //although it doesn't seem right to check here if is new,
         //and to check the repository if it is updated,
         //we'll put this in, hoping in a future bfbase fix
         if( pMFAccount->isNew() || dstcWorkSession->isUpdatedForDataGroup( idDataGroup ) )
         {
            bool bWarningContinue = getIgnoreWarningsOnOk2(); //true;
            sevRtn = pMFAccount->validateAll( idDataGroup, ACCOUNT_GROUPING::ACCOUNT_INFO );
            if( sevRtn == WARNING && !bfutil::isServerContext() )
            {
               bWarningContinue = rpGICaller->send( rpGICaller, I_( "WarningConfirm" ));
            }

            if( bWarningContinue && sevRtn <= WARNING )
            {
               bSuccessFlag = true;
               //if we are in NASU, then see if the user changed the account num
               if( _creatingAccount == YES )
               {
                  DString accountNumManual, newAccountNum;

                  pMFAccount->getField( ifds::AccountNumManual, accountNumManual, idDataGroup );
                  //get the new account number
                  pMFAccount->getField( ifds::AccountNum, newAccountNum, idDataGroup );
                  setGlobal( WORK_GLOBAL, ifds::LastActiveAccountNum, _accountNum );
                  /*if( accountNumManual == YES )
                  {
                     //the new account has been added with the group id of this process
                     BFObjIter bfIter( *dstcWorkSession, getDataGroupId() );

                     if( bfIter.begin( OBJ_TYPE_MFACCOUNT, OBJ_ACTIVITY_ADDED, _accountNum ) )
                     {
                        if( !bfIter.end() )
                        {
                           //do not remove the instance of the object
                           bfIter.removeObjectFromMap( false );
                           //add the same instance of the object with a new key
                           dstcWorkSession->addObject( getDataGroupId(), 
                                                       OBJ_TYPE_MFACCOUNT, 
                                                       newAccountNum, 
                                                       pMFAccount, 
                                                       OBJ_ACTIVITY_ADDED );

                           //refresh other things, hopefully we don't miss anything
                           _accountNum = newAccountNum;
                           setParameter( ACCINFOPROC::ACCOUNT_NUM, _accountNum );
                        }
                        else
                        {
                           assert( 0 ); //that means the account is not in the repository
                           throw;
                        }
                     }
                  }*/
               }//creatingaccount
            }
            else if( sevRtn > WARNING )//validate all
            {
               //if only one condition and either in maintenance,
               //or new account flux
               CONDITIONVECTOR conditionVector;
               int count = 0;

               pMFAccount->getAllErrors( idDataGroup, conditionVector );
               for( CONDITIONVECTOR::iterator it = conditionVector.begin();
                  it != conditionVector.end(); ++it, ++count )
               {
                  if( _creatingShareholder == NO )
                  {
                     Condition* pCondition = *it;

                     if( pCondition->getCode() == CND::ERR_MULTIPLE_ACCT_OWNER_NEEDED )
                     {
                        //launch the entity process, so the user can add a new account holder
                        setParameter( NASULIT::CREATING_ACCOUNT, _creatingAccount );
                        setParameter( NASULIT::CREATING_SHAREHOLDER, _creatingShareholder );
                        //we should send this over to the address screen since we are not commited, yet
                        setParameter( ENTPROC::ACCOUNT_NUM, _accountNum );
                        if( invokeProcessFromChild( rpGICaller, CMD_BPROC_ENTITY, PROC_SUPPORT ) == CMD_OK )
                        {
                           //clear the condition on this frame
                           CLEARCURRENTCONDITION( count );
                        }
                     }
                     //check this informational condition
                     //call the address process only if the current highest severity on the frame is 
                     //informational
                     else if( pCondition->getCode() == CND::INFO_SHAREHOLDER_HAS_MULTIPLE_ADDRESSES &&
                              GETCURRENTHIGHESTSEVERITY() == INFORMATIONAL )
                     {
                        setParameter( ADDRLIT::ACCOUNT_NUM, _accountNum );
                        //01 address code suppose to be the default,
                        //here we have to walk the list of address mailing info,
                        //and get the mailing info for this account and assign the 
                        //corresponding address code, or something like this
                        setParameter( ADDRLIT::ADDRESS_CODE, I_( "01" ) );
                        if( invokeProcessFromChild( rpGICaller, CMD_BPROC_ADDRESSES, PROC_SUPPORT ) == CMD_OK )
                        {
                           //clear the condition on this frame
                           CLEARCURRENTCONDITION( count );
                        }
                     }
                  }
               }
            }
				/*
				if ( _LaunchCOA == I_("LaunchCOA"));
				{
					 if( invokeProcessFromChild( rpGICaller, CMD_BPROC_COA, PROC_SUPPORT ) == CMD_OK )
               {
                  //clear the condition on this frame
                  //CLEARCURRENTCONDITION( );
               }
				}*/

            //if we cleared all conditions the success flag should be set to true
            if( CONDITIONCOUNT() <= 0  && GETCURRENTHIGHESTSEVERITY() <= WARNING && bWarningContinue )
            {
               bSuccessFlag = true;
            }//we didn't clear conditions for the API.
			else if(bfutil::isServerContext() && 
				      ( (GETCURRENTHIGHESTSEVERITY() < WARNING ) || 
				        (GETCURRENTHIGHESTSEVERITY() == WARNING && bWarningContinue) )
				)
			{
				bSuccessFlag = true;
			}


            if( bSuccessFlag && ( ( bfutil::isServerContext() && isModal() ) ||
                                  ( !bfutil::isServerContext() && isModal() &&  getParent() && getParent()->isModal() ) ) )
            {
               //commit the changes for the account and repository
               if( dstcWorkSession->commitDataGroup( idDataGroup ) <= WARNING )
               {
                  // Refresh other processes
                  bNeedRefresh = true;
               }
               else
               {  // Commit failed
                  bSuccessFlag = false;
                  PROMOTECONDITIONS();
               }
            }
         }//is updated for data group
         else
         {  // Nothing happened - make sure and remove any dummy entries added
            pMFAccount->deleteNonUpdatedAddedElements( idDataGroup );
            bSuccessFlag = true;
         }
         if( bSuccessFlag )
         {
            //probably this should be done in the CBO, but now base
            //doesn't have support for commiting properties!
            //lock the account number, once is validated and commited
            //pMFAccount->setFieldReadOnly( ifds::AccountNum, getParent()->getDataGroupId(), true );

            // after finished an updating data we assume that all of data 
            // are in sych with back-end hence we would use BF::HOST as data group
            pMFAccount->setFieldReadOnly( ifds::AccountNum, BF::HOST, true );

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
               if( pMFAccount->isUpdated( true ) /*||
                   ( rpAwdSession && rpAwdSession->getProcessWork() )*/ )
               {
//CP20030319                  DString str = asString( idDataGroup );
//CP20030319                  setParameter( I_( "DataGroupID" ), str );
                  setGlobal( WORK_GLOBAL, ifds::LastActiveAccountNum, _accountNum );
                  setGlobal( WORK_GLOBAL, ifds::LastActiveShrNum, _shareholderNum );
                  if( CMD_OK != invokeCommand( this, CMD_BPROC_CONFIRMATION,
                                               PROC_NO_TYPE, true, NULL ) )
                  {
                     DString strOut;

                     bSuccessFlag = false;
                     PROMOTECONDITIONS();
                     getParameter( I_( "TrxnsError" ), strOut );
                     if( strOut == YES )
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
      }//get the account and the Xref object
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

//******************************************************************************

SEVERITY AccInfoProcess::doSetField(
                                   const GenericInterface *rpGICaller,
                                   const BFContainerId& idContainer,
                                   const BFFieldId& idField,
                                   const BFDataGroupId& idDataGroup,
                                   const DString& strValue,
                                   bool bFormatted
                                   )
{  
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTBP_CONDITION, CLASSNAME, I_("doSetField") );

   DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   // If we try to set a field this should be overridden
   if (BF::NullContainerId == idContainer)
   {
      if (idField == ifds::AccountNum)
      {
         if (m_bManualAccNum)
         {
            MFAccount *pMFAccount = NULL;
            SEVERITY sevRtn = SEVERE_ERROR;
            if (_creatingAccount == YES  && 
                  _accountNum == NULL_STRING)
            { //create a new account object
               AccShrNumCheck acctShrNumCheck (*dstcWorkSession);
               DString dstrCalledByProc = (_creatingAccount == YES)? I_("NASU"):NULL_STRING;
							
					if (acctShrNumCheck.initCheck (NULL_STRING, strValue, dstrCalledByProc) > WARNING)
					{
						if (_pCondition)
                  {
							delete _pCondition;
                  }
						_pCondition = new Condition( *GETCONDITION( 0 ));
						return GETCURRENTHIGHESTSEVERITY();
					}		
               sevRtn = dstcWorkSession->getNewMFAccount (getDataGroupId(), _shareholderNum, pMFAccount, strValue);
               if (sevRtn <= WARNING)
               {
                  //get the account number
                  pMFAccount->getField (ifds::AccountNum, _accountNum, getDataGroupId());

                  if (_creatingShareholder == NO) //get some of the data from the model account
                  {
                     //clone this account from model
                     pMFAccount->cloneFromModel( _modelAccountNum, getDataGroupId() );
                  }
               }
            }
            else
            {
               //get an existing account object
               sevRtn = dstcWorkSession->getMFAccount( getDataGroupId(), _accountNum, pMFAccount );
               if( _creatingAccount == YES && pMFAccount )
               {
                  pMFAccount->setAccountDesignation( getDataGroupId() );
               }
               else if( pMFAccount )
               {
                  pMFAccount->getField( ifds::ShrNum, _shareholderNum, getDataGroupId() );
                  DString dstrAcctDesignation;
                  pMFAccount->getField( ifds::AcctDesignation, dstrAcctDesignation, getDataGroupId() );
                  if( dstrAcctDesignation == I_("3") ) // Intermediary
                  {
                     pMFAccount->loadIntermCodeSubstitutionList( getDataGroupId() );
                  }
               }
            }
            if (sevRtn <= WARNING)
            {
               //register CBO with base
               m_bAccCreated = true;
            }
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AccInfoProcess::doGetErrors( const GenericInterface *rpGICaller, const BFContainerId& idContainer,
                                      const BFFieldId& idField, const BFDataGroupId& idDataGroup, CONDITIONVECTOR &conditions ) const
{

   SEVERITY sevRtn = NO_CONDITION;

   if( idField == ifds::AccountNum )
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
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AccInfoProcess.cpp-arc  $
 * 
 *    Rev 1.85   Jul 12 2012 10:42:28   dchatcha
 * P0191601 FN03 - Manual T3/RL 16/NR4 Slip for Taxable Trusts.
 * 
 *    Rev 1.84   Mar 23 2012 07:46:08   wutipong
 * IN2672446 - Shareholder group issue on account in SSG
 * 
 *    Rev 1.83   Feb 17 2012 10:04:26   popescu
 * refresh portfolio - temporary backed the code out.
 * 
 *    Rev 1.82   Feb 08 2012 20:30:18   dchatcha
 * IN# 2837678 - REL12.2-PET0186484- New INA Contract Information screen issues as on 6 Feb 2012
 * 
 *    Rev 1.81   Feb 07 2012 18:07:22   dchatcha
 * IN# 2837678 - REL12.2-PET0186484- New INA Contract Information screen issues as on 6 Feb 2012
 * 
 *    Rev 1.80   Oct 07 2011 00:50:54   kitticha
 * PETP0183105 FN02 - Unclaimed Property Alberta.
 * 
 *    Rev 1.79   Oct 03 2011 14:39:42   dchatcha
 * P0186477 FN01 - GIA Enhancements, remove reference to 'ProdPortfolioCode' and 'PordPortfolioPlanCode'
 * 
 *    Rev 1.78   Sep 06 2011 14:14:24   dchatcha
 * P0186477 FN01 - GIA Enhancements
 * 
 *    Rev 1.77   Aug 04 2011 11:41:10   dchatcha
 * P0186477 FN01 - GIA Enhancements
 * 
 *    Rev 1.76   Jan 27 2010 17:58:16   wutipong
 * IN1877040 -- More fix to remove hard-coding.
 * 
 *    Rev 1.75   15 Apr 2008 11:40:26   kovacsro
 * PET2255-FN47 - Ontario New LIF
 * 
 *    Rev 1.74   Jul 27 2007 16:19:28   kovacsro
 * PET 2372 FN02 FDP-AIM KYC - added AccountClosingReason
 * 
 *    Rev 1.73   Jan 26 2006 12:04:18   popescu
 * Disable the COA button on the AccInfo screen if this is invoked from the  COA dialog
 * 
 *    Rev 1.72   Jul 06 2005 10:54:08   ZHANGCEL
 * PET1141 - FN05 -- NSCC Broker enhancement
 * 
 *    Rev 1.71   Sep 13 2004 11:36:26   popescu
 * PTS 10033771 - Overwriting AccountNum for new Account when Control Keys File.Account Generate is on.
 * 
 *    Rev 1.70   Sep 09 2004 14:43:30   VADEANUM
 * PTS 10033771 - Overwriting AccountNum for new Account when Control Keys File.Account Generate is on.
 * 
 *    Rev 1.69   Aug 25 2004 17:01:26   HERNANDO
 * PTS 10033324 - Ignore reference to the AWD Work Object in determining whether to launch the Confirmation Dialog.
 * 
 *    Rev 1.68   Aug 11 2004 11:59:48   AGUILAAM
 * PET1117_FN02:  Account Static enhancement for SSBG - added new acct categories, and contact person, registrationinfo fields
 * 
 *    Rev 1.67   Apr 05 2004 17:35:52   FENGYONG
 * PET944FN01, release 56.1 NSCC Broker
 * 
 *    Rev 1.66   Nov 10 2003 11:48:58   ZHANGCEL
 * PTS 10023790: TITLE_FIELD should be set up regardless the status of _creatingShareholder
 * 
 *    Rev 1.65   Oct 27 2003 16:37:32   ZHANGCEL
 * PTS ticket 10023250: fix crash when manually create an account number
 * 
 *    Rev 1.64   Sep 12 2003 13:55:04   FENGYONG
 * fix for API frankrussel
 * 
 *    Rev 1.63   Sep 03 2003 15:16:28   FENGYONG
 * API Account information update enhancement
 * 
 *    Rev 1.62   Aug 19 2003 09:08:52   HSUCHIN
 * added HouseBroker field to field details
 * 
 *    Rev 1.61   Aug 01 2003 14:11:40   FENGYONG
 * Add Rebalance for API
 * 
 *    Rev 1.60   Jul 30 2003 11:26:52   FENGYONG
 * CIBC enhancement PET809_FN46
 * 
 *    Rev 1.59   Jul 17 2003 10:40:02   FENGYONG
 * Add fields
 * 
 *    Rev 1.58   Jul 10 2003 22:19:00   popescu
 * check in for payment instruct, used mfcan_ip_param for some interporcess param passing
 * 
 *    Rev 1.57   Apr 28 2003 10:57:24   YINGBAOL
 * In Nasu flow, AccountNum is passed back shareholder process only after account information screen
 * 
 *    Rev 1.56   Apr 02 2003 16:38:28   linmay
 * clean for sec
 * 
 *    Rev 1.55   Mar 21 2003 17:33:50   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.54   Nov 18 2002 10:55:26   PURDYECH
 * BFObjectKey changes.
 * 
 *    Rev 1.53   Oct 09 2002 23:52:56   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.52   Aug 29 2002 16:42:30   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.51   Aug 29 2002 12:54:06   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.50   Jul 26 2002 15:28:14   YINGBAOL
 * fix PTS10009161
 * 
 *    Rev 1.49   Jul 18 2002 14:18:38   FENGYONG
 * Use  MyGroupId get new mfaccount instead of ParentGroupId
 * 
 *    Rev 1.48   Jul 05 2002 17:08:24   HSUCHIN
 * bug fix for serverContext checks and AbstractProcess changes
 * 
 *    Rev 1.47   Jul 03 2002 16:02:30   PURDYECH
 * Initialization problem in doInit()
 * 
 *    Rev 1.46   Jul 03 2002 15:53:26   SMITHDAV
 * Fix commit logic for server context.
 * 
 *    Rev 1.45   Jun 26 2002 19:23:26   ZHANGCEL
 * Fixed the bug which causes crashing in the doInit()
 * 
 *    Rev 1.44   08 Jun 2002 15:25:32   HERNANDO
 * Added Account Opening Date (field FirstEffective).
 * 
 *    Rev 1.43   May 28 2002 12:18:04   PURDYECH
 * BFData Implementation - Phase II
 * 
 *    Rev 1.42   22 May 2002 22:22:52   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.41   17 Apr 2002 16:58:30   KOVACSRO
 * Added StopSWP.
 * 
 *    Rev 1.40   27 Mar 2002 19:54:26   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.39   14 Feb 2002 17:10:42   WINNIE
 * PTS 10007077 : Fix internal error due to cancellation at account information screen
 * 
 *    Rev 1.38   08 Feb 2002 16:49:16   KOVACSRO
 * Force validation for the AccountNum
 * 
 *    Rev 1.37   Dec 31 2001 15:30:26   YINGBAOL
 * remove newly created mfaccount object if it is canceled  
 * and Manual created.
 * 
 *    Rev 1.36   Dec 31 2001 14:35:54   YINGBAOL
 * use lastactiveAccount Number to solve cancel problems
 * 
 *    Rev 1.35   Dec 20 2001 10:46:24   YINGBAOL
 * fix populate account number
 * 
 *    Rev 1.34   Dec 18 2001 16:24:32   YINGBAOL
 * fix groupcode issue
 * 
 *    Rev 1.33   Nov 28 2001 12:18:38   JANKAREN
 * Added AMSCode
 * 
 *    Rev 1.32   Nov 09 2001 16:08:18   YINGBAOL
 * fix NASU problem
 * 
 *    Rev 1.31   Oct 16 2001 11:22:40   ZHANGCEL
 * Added SetGlobal parameter of LastActiveShrNum in order to fix the bug that causes AccountInfo modification fail.
 * 
 *    Rev 1.30   19 Jun 2001 10:42:58   KOVACSRO
 * create the new account with the NASU (parent) datagroupId.
 * 
 *    Rev 1.29   Jun 13 2001 09:58:06   OLTEANCR
 * fixed sync up bug, cancel button
 * 
 *    Rev 1.28   15 May 2001 15:37:40   YINGZ
 * data group id clean up
 * 
 *    Rev 1.27   11 May 2001 16:33:32   YINGZ
 * code sync up
 * 
 *    Rev 1.26   03 May 2001 14:05:12   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.25   Mar 20 2001 13:15:12   YINGZ
 * clear lastacctnum when user cancel
 * 
 *    Rev 1.24   18 Mar 2001 14:27:26   JANKAREN
 * Add Social Code
 * 
 *    Rev 1.23   Feb 21 2001 11:33:50   YINGZ
 * make api nasu work
 * 
 *    Rev 1.22   Feb 12 2001 15:50:08   YINGZ
 * add apinasu
 * 
 *    Rev 1.21   Jan 18 2001 09:35:48   KOVACSRO
 * More fixes for Cancel for new shareholder .
 * 
 *    Rev 1.20   Jan 17 2001 17:26:56   KOVACSRO
 * Modified doCancel().
 * 
 *    Rev 1.19   Dec 28 2000 16:55:56   KOVACSRO
 * Bug fixed for Cancel.
 * 
 *    Rev 1.18   15 Dec 2000 12:43:16   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.17   Nov 29 2000 17:19:56   WINNIE
 * pop up warning box for validateAll
 * 
 *    Rev 1.16   Oct 04 2000 11:45:12   HERNANDO
 * Check for session before attempting getAwdSession
 * 
 *    Rev 1.15   Oct 03 2000 18:29:42   WINNIE
 * move get shareholdernum to the right spot
 * 
 *    Rev 1.14   Sep 26 2000 19:13:52   WINNIE
 * Load substitution list for intermediary
 * 
 *    Rev 1.13   Sep 25 2000 16:58:46   WINNIE
 * change clonefromaccount method to void
 * 
 *    Rev 1.12   Sep 23 2000 15:37:40   DINACORN
 * Implemented code for the Title of Acct.Info Screen
 * 
 *    Rev 1.11   Sep 01 2000 14:39:22   YINGBAOL
 * implement lauching entity screen logic
 * 
 *    Rev 1.10   Aug 30 2000 10:10:06   YINGBAOL
 * add accountdesignation
 * 
 *    Rev 1.9   Aug 23 2000 11:54:34   DINACORN
 * Added code in doGetField, case: GRP_CODE_LEVEL_FIELD
 * 
 *    Rev 1.8   Aug 16 2000 10:39:04   DINACORN
 * Added addFieldDetails() for Group
 * 
 *    Rev 1.7   Aug 02 2000 15:31:54   BUZILA
 * "locale" changes
 * 
 *    Rev 1.6   Apr 04 2000 15:15:06   DT24433
 * changed to use getGIContainer
 * 
 *    Rev 1.5   Mar 31 2000 14:29:26   HSUCHIN
 * minor change
 * 
 *    Rev 1.4   Mar 30 2000 12:07:08   HSUCHIN
 * M2 sync up
 * 
 *    Rev 1.3   Mar 29 2000 14:38:12   YINGZ
 * code sync
 * 
 *    Rev 1.2   Mar 13 2000 16:43:22   HSUCHIN
 * C2 sync up
 * 
 *    Rev 1.1   Feb 15 2000 18:57:08   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:30   SMITHDAV
 * Initial revision.
// 
//    Rev 1.52   Feb 07 2000 18:18:54   POPESCUS
// returned SEVERE_ERROR in ok2 instead of GETCURRENTHIGHESTSEVERITY if succes flag is false
// 
//    Rev 1.51   Jan 27 2000 10:22:50   POPESCUS
// took out the info for the address, for now
// 
//    Rev 1.50   Jan 26 2000 21:32:52   POPESCUS
// ?
// 
//    Rev 1.49   Jan 26 2000 19:44:52   POPESCUS
// fixes for th release
// 
//    Rev 1.48   Jan 25 2000 17:14:22   POPESCUS
// fixes for validation of a new account
// 
//    Rev 1.47   Jan 23 2000 18:46:02   POPESCUS
// changes related to refresh and the creation of a new rep on the fly
// 
//    Rev 1.46   Jan 21 2000 11:11:36   POPESCUS
// the user can change the account number and the shareholder number
// 
//    Rev 1.45   Jan 17 2000 14:00:14   POPESCUS
// support for refresh and misc
// 
//    Rev 1.44   Jan 16 2000 18:01:08   POPESCUS
// fixed the ok2 logic
// 
//    Rev 1.43   Jan 14 2000 18:08:50   POPESCUS
// set the last active account num
// 
//    Rev 1.42   Jan 14 2000 09:34:34   POPESCUS
// set the last active account number in ok2
// 
//    Rev 1.41   Jan 14 2000 09:10:58   POPESCUS
// fixed some validation issues and cloning of a new account
// 
//    Rev 1.40   Jan 12 2000 11:59:34   POPESCUS
// cloning an account
// 
//    Rev 1.39   Jan 12 2000 08:57:28   POPESCUS
// changes related to cloning an account and fixing some validation, adding subst sets
// 
//    Rev 1.38   Jan 11 2000 08:41:34   POPESCUS
// fixes and validation
// 
//    Rev 1.37   Jan 09 2000 19:11:12   POPESCUS
// bug fixes?
// 
//    Rev 1.36   Jan 07 2000 15:54:18   POPESCUS
// just checking in...
// 
//    Rev 1.35   Jan 06 2000 09:57:56   POPESCUS
// cleanup code and remove some unused methods
// 
//    Rev 1.34   Dec 24 1999 15:18:06   VASILEAD
// Fixed transactions
// 
//    Rev 1.33   Dec 24 1999 10:29:38   VASILEAD
// Fixed NASU flow
// 
//    Rev 1.32   Dec 23 1999 11:29:04   POPESCUS
// NASU process and the new confirmation model
// 
//    Rev 1.31   Dec 21 1999 14:23:56   POPESCUS
// fixed a name of a param
// 
//    Rev 1.30   Dec 21 1999 14:14:34   POPESCUS
// cleanup the code, validations and misc
// 
//    Rev 1.29   Dec 20 1999 16:14:20   POPESCUS
// Code review, validations removed commented code, misc
// 
//    Rev 1.28   Dec 15 1999 12:07:56   ZHANGCEL
// Add a new substitution list AcctTypeX
// 
//    Rev 1.27   Dec 14 1999 09:46:18   ZHANGCEL
// Improvement
// 
//    Rev 1.26   Dec 03 1999 18:20:58   ZHANGCEL
// Improvement 
// 
//    Rev 1.24   Dec 01 1999 11:23:32   ZHANGCEL
// Modify for default Broker Branch and SalesRep 
// 
//    Rev 1.23   Nov 30 1999 18:24:46   POPESCUS
// changes related to the NASU flow
// 
//    Rev 1.22   Nov 30 1999 14:16:58   POPESCUS
// Fix required for NASU flow
// 
//    Rev 1.21   Nov 30 1999 13:57:54   ZHANGCEL
// New AccountInfo implementation
// 
//    Rev 1.19   Nov 27 1999 19:22:16   ZHANGCEL
// Add new function for View requirst
// 
//    Rev 1.18   Nov 25 1999 14:08:48   POPESCUS
// get the account number for mfcommonbm and cleanup
// 
//    Rev 1.17   Nov 25 1999 10:09:52   ZHANGCEL
// add two files for Broker_list
// 
//    Rev 1.16   Nov 24 1999 10:06:04   POPESCUS
// again NASU
// 
//    Rev 1.15   Nov 23 1999 18:05:36   POPESCUS
// NASU flow
// 
//    Rev 1.14   Nov 15 1999 11:57:08   PRAGERYA
// Further additions for Incr2
// 
//    Rev 1.13   Nov 01 1999 15:17:00   DT24433
// removed doOk/doCancel
// 
//    Rev 1.12   Oct 29 1999 11:30:10   BUZILA
// changing WorkSessionDetails into a BFBase descendant
// 
//    Rev 1.11   Sep 23 1999 13:03:04   YINGZ
// make it wokr for c1
// 
//    Rev 1.10   Sep 01 1999 12:36:56   DT24433
// changed doGetField/doSetField parms
// 
//    Rev 1.9   Sep 01 1999 12:04:56   PRAGERYA
// Enhancing implementation for Incr 2
// 
//    Rev 1.8   Aug 26 1999 16:08:40   PRAGERYA
// Implementing Search for Shareholder and Account Info
// 
//    Rev 1.7   Aug 20 1999 08:27:40   DT24433
// removed static FieldDetails array
// 
//    Rev 1.6   Aug 19 1999 12:35:36   PRAGERYA
// Enhancing ShareholderInfo and AccountInfo implementations
// 
//    Rev 1.5   Aug 18 1999 15:32:56   PRAGERYA
// Bug fixes
// 
//    Rev 1.4   Aug 11 1999 12:34:28   PRAGERYA
// Enhancing implementation
// 
//    Rev 1.3   Aug 08 1999 19:32:00   PRAGERYA
// All in!
// 
//    Rev 1.2   Aug 04 1999 09:35:16   PRAGERYA
// Implementing process
// 
//    Rev 1.1   Jul 27 1999 16:01:38   BUZILA
// Increment M2
// 
//    Rev 1.0   Jul 22 1999 17:23:32   BUZILA
// Initial revision.
*/ 

//******************************************************************************
