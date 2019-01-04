//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by IFDS, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//******************************************************************************
//
// ^FILE   : AMSAcctLvlProcess.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : AMSAcctLvlProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "AMSAcctLvlprocess.hpp"
#include <ifastdataimpl\dse_dstcglob_vw.hpp>

#include "mfcaninterprocparam.hpp"
#include "AMSMstProcessIncludes.h"
#include "AMSAcctLvlProcessIncludes.h"
#include "confirmationprocessincludes.h"

#include <ifastcbo\acctalloc.hpp>
#include <ifastcbo\acctalloclist.hpp>
#include <ifastcbo\AMSAcctLvl.hpp>
#include <ifastcbo\AMSAcctLvllist.hpp>
#include <ifastcbo\AmsMstrList.hpp>
#include <ifastcbo\amsmstrinfo.hpp>
#include <ifastcbo\defacctalloclist.hpp>
#include <ifastcbo\defacctalloc.hpp>
#include <ifastcbo\deffundalloclist.hpp>
#include <ifastcbo\fundalloclist.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\mgmtcooptions.hpp>
#include <ifastcbo\shralloctypelist.hpp>
#include <ifastcbo\shralloctype.hpp>
#include <ifastcbo\shareholder.hpp>
#include <ifastcbo\AmsFundAllocList.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_AMSACCTLVL;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_AMSACCTLVL;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< AMSAcctLvlProcess > processCreator( CMD_BPROC_AMSACCTLVL );

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME                = I_( "AMSAcctLvlProcess" );
   const I_CHAR *CODE_AMSTYPE_REBALANCING = I_("RB");
   const I_CHAR *CODE_AMSTYPE_REPORT_ONLY = I_("RO");
   const I_CHAR * const CALLER            = I_( "Caller" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace IFASTBP_PROC
{
   const I_CHAR * const ACCOUNT_NUM = I_( "AccountNum" );
   const I_CHAR * const NAME        = I_( "Name" );
}

namespace AUDITTYPE
{
   extern CLASS_IMPORT I_CHAR * const ACTAMS;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId    ToFundNumber;
   extern CLASS_IMPORT const BFTextFieldId    FundCode;
   extern CLASS_IMPORT const BFTextFieldId    ClassCode;
   extern CLASS_IMPORT const BFTextFieldId    AMSType;
   extern CLASS_IMPORT const BFTextFieldId    DefaultAlloc;
   extern CLASS_IMPORT const BFTextFieldId    FundAlloc;
   extern CLASS_IMPORT const BFTextFieldId    EnglishName;
   extern CLASS_IMPORT const BFDecimalFieldId AllocPercentage;
   extern CLASS_IMPORT const BFTextFieldId    Rebalance;
//   extern CLASS_IMPORT const BFDecimalFieldId RebalPrcnt;
   extern CLASS_IMPORT const BFDecimalFieldId Percentage;
//   extern CLASS_IMPORT const BFTextFieldId    AMSCurrency;
   extern CLASS_IMPORT const BFTextFieldId    UpdatePACSWP;
   extern CLASS_IMPORT const BFTextFieldId    Currency;   
   extern CLASS_IMPORT const BFTextFieldId    AMSCodeBuffer;
   extern CLASS_IMPORT const BFTextFieldId    RebalDateFormat;
   extern CLASS_IMPORT const BFTextFieldId    AMSRebalPending;
   extern CLASS_IMPORT const BFDateFieldId    ActualRebalanceDate;
   extern CLASS_IMPORT const BFTextFieldId    AMSRebReqMode;
}

//******************************************************************************
//              Public Methods
//******************************************************************************
AMSAcctLvlProcess::AMSAcctLvlProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, m_rpChildGI( NULL ),
m_pAMSFundAllocList( NULL ),
m_pAMSDefFundAllocList( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::MFACCOUNT_CBO,          false, BF::NullContainerId,                    true,  I_("Account") );
   addContainer( IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, true,  IFASTBP_PROC::MFACCOUNT_CBO,            true,  I_("AMSAccountLevel") );
   addContainer( IFASTBP_PROC::USER_DEFINED_AMS,       true,  IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST,   true,  I_("UserDefinedAMS") );
   addContainer( IFASTBP_PROC::GLOBAL_DEFINED_AMS,     true,  BF::NullContainerId,                    true,  I_("GlobalDefinedAMS") );
   addContainer( IFASTBP_PROC::AMS_MASTER_LIST,        true,  BF::NullContainerId,                    false, I_("AMSMasterList") );

   // AMS Master Info
   addFieldDetails( ifds::DefaultAlloc,      IFASTBP_PROC::AMS_MASTER_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::FundAlloc,         IFASTBP_PROC::AMS_MASTER_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::EnglishName,       IFASTBP_PROC::AMS_MASTER_LIST, SUBCLASS_PROCESS );   
   addFieldDetails( ifds::AMSCode,           IFASTBP_PROC::AMS_MASTER_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::Currency,          IFASTBP_PROC::AMS_MASTER_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::Percentage,        IFASTBP_PROC::AMS_MASTER_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::EffectiveDate,     IFASTBP_PROC::AMS_MASTER_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::SchedSetupFreqID,  IFASTBP_PROC::AMS_MASTER_LIST, SUBCLASS_PROCESS );   

   // Account Details
   // Add AMS type field
   addFieldDetails( ifds::AMSCode,              IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST );
   addFieldDetails( ifds::AMSType,              IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST );   
   addFieldDetails( ifds::Deff,                 IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST );   
   addFieldDetails( ifds::StopDate,             IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST );   
   addFieldDetails( ifds::NextProcessDate,      IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST );   
   addFieldDetails( ifds::LastProcessDate,      IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST );   
   addFieldDetails( ifds::FreqOverride,         IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST );   
   addFieldDetails( ifds::SchedSetupFreqID,     IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, SUBCLASS_PROCESS );   
   addFieldDetails( ifds::AMSStat,              IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST );   
   addFieldDetails( ifds::ActivationDate,       IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST );   
   addFieldDetails( ifds::Rebalance,            IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST );   
   addFieldDetails( ifds::UpdatePACSWP,         IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST );
   addFieldDetails( ifds::AcctAMSRID,           IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST );
   addFieldDetails( ifds::ModUser,              IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST );
   addFieldDetails( ifds::ProcessDate,          IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST );
   addFieldDetails( ifds::ModDate,              IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST );
   addFieldDetails( ifds::Username,             IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST );
   addFieldDetails( ifds::ThresholdPrcnt,       IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST );
   addFieldDetails( ifds::Currency,             IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST );
   addFieldDetails( ifds::AMSCodeBuffer,        IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST );
   addFieldDetails( ifds::ActualRebalanceDate,  IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST );
   addFieldDetails( ifds::TargetMixOption,      IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST );
   addFieldDetails( ifds::AMSDeltaRequestUUID,  IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST );
   addFieldDetails( ifds::LastAMSModDate,       IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST );

   addFieldDetails( ifds::ShrNum,            IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::AccountNum,        IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( ifds::AcctStatus,        IFASTBP_PROC::MFACCOUNT_CBO );
   addFieldDetails( TOTAL_PERCENTAGE,        BF::NullContainerId, SUBCLASS_PROCESS );
   
   // User Defined AMS - Fund Details
   addFieldDetails( ifds::ToFundNumber,      IFASTBP_PROC::USER_DEFINED_AMS );
   addFieldDetails( ifds::FundCode,          IFASTBP_PROC::USER_DEFINED_AMS );
   addFieldDetails( ifds::ClassCode,         IFASTBP_PROC::USER_DEFINED_AMS );
   addFieldDetails( ifds::AllocPercentage,   IFASTBP_PROC::USER_DEFINED_AMS );

   // Global Defined AMS - Fund Details
   addFieldDetails( ifds::ToFundNumber,      IFASTBP_PROC::GLOBAL_DEFINED_AMS );
   addFieldDetails( ifds::FundCode,          IFASTBP_PROC::GLOBAL_DEFINED_AMS );
   addFieldDetails( ifds::ClassCode,         IFASTBP_PROC::GLOBAL_DEFINED_AMS );
   addFieldDetails( ifds::AllocPercentage,   IFASTBP_PROC::GLOBAL_DEFINED_AMS );

   // Options
   addFieldDetails( ifds::DispRBLSysThrshld,	BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ifds::CommonCurrency,    BF::NullContainerId, SUBCLASS_PROCESS );

   //IN2818924 - DSK_AMS Validation for CDIC
   addFieldDetails( IsFundLimitedByBankuptcy,        BF::NullContainerId, SUBCLASS_PROCESS );

   addFieldDetails(AMS_DELTA::IsAMSUpdate, BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails(AMS_DELTA::IsAMSFundUpdate, BF::NullContainerId, SUBCLASS_PROCESS);
}

//******************************************************************************
AMSAcctLvlProcess::~AMSAcctLvlProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   m_rpChildGI = NULL;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************
SEVERITY AMSAcctLvlProcess::doInit()
{
   getParameter(I_("AccountNum"), m_dstrAccountNumber );
   getParameter(CALLER, m_dstrCaller );
  			
   return( NO_CONDITION );
}

//******************************************************************************
E_COMMANDRETURN AMSAcctLvlProcess::doProcess()
{  
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter(CALLER, m_dstrCaller );

      rtn = invokeCommand( this, CMD_GUI_AMSACCTLVL, getProcessType(), isModal(), &m_rpChildGI );
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
bool AMSAcctLvlProcess::doOk( GenericInterface *rpGICaller )
{
   setParameter( CONFPROC::PARM_CALLED_FROM, I_("AMSAcctLvl") );

   MFAccount *pMFAccount  = dynamic_cast<MFAccount *>(getCBOItem(IFASTBP_PROC::MFACCOUNT_CBO, getDataGroupId()));
   if( pMFAccount ) {
      pMFAccount->refreshMe (true); //refresh mfaccount
   }

   //DefFundAllocList *pFundAllocList = 
   //   dynamic_cast<DefFundAllocList*>(getCBOList(IFASTBP_PROC::USER_DEFINED_AMS,getDataGroupId()));

   //if (pFundAllocList)
   //{
   //   if ( pFundAllocList->isUpdatedForDataGroup(getDataGroupId()))
   //   {
   //      AMSAcctLvl *pAMSAcctLvl = 
   //         dynamic_cast <AMSAcctLvl*> (getCBOItem ( IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, 
   //         getDataGroupId()));

   //      if (pAMSAcctLvl)
   //      {
   //         pAMSAcctLvl->setField(ifds::AMSRebReqMode, NULL_STRING,getDataGroupId(),false,false,true);
   //      }
   //   }
   //}

   return(true);
}

//******************************************************************************
void *AMSAcctLvlProcess::getPtrForContainer( const BFContainerId& idContainer, 
                                             const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, I_( "getPtrForContainer" ) );
   void *ptr = NULL;

   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   try
   {
      if( IFASTBP_PROC::MFACCOUNT_CBO == idContainer )
      {
         MFAccount *pMFAccount;
         if( dstcWorkSession->getMFAccount( idDataGroup, m_dstrAccountNumber, pMFAccount ) <= WARNING )
         {
            ptr = pMFAccount;
         }
      }
      else if ( IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST == idContainer  )
      {
         MFAccount *pMFAccount = dynamic_cast< MFAccount * >( getCBOItem(IFASTBP_PROC::MFACCOUNT_CBO, idDataGroup ) );
         if ( NULL != pMFAccount )
         {
            AMSAcctLvlList *pAMSAcctLvlList = NULL;
            if ( pMFAccount->getAMSAcctLvlList( idDataGroup, pAMSAcctLvlList ) &&
                 NULL != pAMSAcctLvlList )
            {
               ptr = pAMSAcctLvlList;
            }
         }
      }
      else if( IFASTBP_PROC::AMS_MASTER_LIST == idContainer )
      {
         MFAccount *pMFAccount = dynamic_cast< MFAccount * >( getCBOItem(IFASTBP_PROC::MFACCOUNT_CBO, idDataGroup ) );
         DString dstrCurDate;
         DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
         dstcWorkSession->getDateInHostFormat( dstrCurDate, DSTCWorkSession::CURRENT_BUSINESS_DAY, idDataGroup );
         AMSMstrList* pAMSMstrList = NULL;	
         pMFAccount->getAMSMstrList( pAMSMstrList, idDataGroup,dstrCurDate );					
         ptr= pAMSMstrList;
      }
      else if( IFASTBP_PROC::SHAREHOLDER_CBO == idContainer )
      {
         Shareholder *pShareholder = NULL;
         DString dstrShareholderNum;
         getField( this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::ShrNum, dstrShareholderNum );
         dstrShareholderNum.strip().stripLeading( I_CHAR( '0' ) );
         if( dstcWorkSession->getShareholder( idDataGroup, dstrShareholderNum, pShareholder ) <= WARNING )
         {
            ptr = pShareholder;
         }
      }
      else if (IFASTBP_PROC::USER_DEFINED_AMS == idContainer)
      {
         AMSAcctLvl *pAMSAcctLvl = 
            dynamic_cast <AMSAcctLvl*> (getCBOItem ( IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, 
                                                     idDataGroup));
         if (pAMSAcctLvl)
         {
            DefFundAllocList *pFundAllocList = NULL;

            if ( pAMSAcctLvl->getAMSAcctLvlAllocation ( pFundAllocList, idDataGroup) <= WARNING && 
                                                        pFundAllocList)
            {
               ptr = pFundAllocList;
               m_pAMSDefFundAllocList = pFundAllocList;
            }
         }
      }
      else if( IFASTBP_PROC::GLOBAL_DEFINED_AMS == idContainer )
      {
         AmsFundAllocList *pAMSFundAllocList = NULL;
         AmsMstrInfo *pAmsMstrInfo = NULL;
         DString	   dstrEffectiveDate;


         DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

         dstcWorkSession->getDateInHostFormat( dstrEffectiveDate, DSTCWorkSession::CURRENT_BUSINESS_DAY, idDataGroup );


         MFAccount* pMFAccount = dynamic_cast<MFAccount *>(getCBOItem(IFASTBP_PROC::MFACCOUNT_CBO, idDataGroup));
         if( pMFAccount )
         {	
//				pMFAccount->getField(ifds::AMSType,dstrAMSType,idDataGroup,false);
//				dstrAMSType.strip();
//			  if( dstrAMSType == CODE_AMSTYPE_REBALANCING ) 
//			  {
//				  pMFAccount->getField( ifds::AMSCode, dstrAMSCode,idDataGroup,false );
//			  }
//			  else if( dstrAMSType == CODE_AMSTYPE_REPORT_ONLY ) 
//			  {
//				  pMFAccount->getField( ifds::AMSROCode, dstrAMSCode,idDataGroup,false );
//			  }
            DString     dstrAMSType;
            getField( this, IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, ifds::AMSType, dstrAMSType, false );
            dstrAMSType.strip();

            DString     dstrAMSCode;
            getField( this, IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, ifds::AMSCode, dstrAMSCode, false );

            AMSMstrList* pAMSMstrList = NULL;	
            pMFAccount->getAMSMstrList( pAMSMstrList, idDataGroup,dstrEffectiveDate );
            pAMSMstrList->getAMSMstrInfo(dstrAMSType,dstrAMSCode,dstrEffectiveDate,pAmsMstrInfo,idDataGroup);
            if(pAmsMstrInfo )
            {	
               pAmsMstrInfo->getAMSFundAllocList( pAMSFundAllocList, idDataGroup );
               ptr = pAMSFundAllocList;
               m_pAMSFundAllocList = pAMSFundAllocList;
            }
         }	
      }
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "getPtrForContainer" ), CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(ptr);
}

//******************************************************************************
bool AMSAcctLvlProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_AMSACCTLVL );
}

//******************************************************************************
bool AMSAcctLvlProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doModelessSetFocus") );

   bool bRtn = false;
   try
   {
      assert( m_rpChildGI && isValidModelessInterface( m_rpChildGI ) );
      bRtn = m_rpChildGI->refresh( this, NULL );
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
AmsMstrInfo* AMSAcctLvlProcess::getMasterInfo( const BFDataGroupId& idDataGroup ) const
{
   AmsMstrInfo* pAMSMstrInfo = NULL;
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   AMSAcctLvlProcess *rpNonConstThis = const_cast < AMSAcctLvlProcess *>(this);

   MFAccount* pMFAccount = dynamic_cast<MFAccount *>(rpNonConstThis->getCBOItem(IFASTBP_PROC::MFACCOUNT_CBO, idDataGroup));
   if( pMFAccount )
   {	
      DString	   dstrEffectiveDate;
      dstcWorkSession->getDateInHostFormat( dstrEffectiveDate, DSTCWorkSession::CURRENT_BUSINESS_DAY, idDataGroup );

      AMSMstrList* pAMSMstrList = NULL;	
      pMFAccount->getAMSMstrList( pAMSMstrList, idDataGroup, dstrEffectiveDate );

      DString     dstrAMSType;
      rpNonConstThis->getField( rpNonConstThis, IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, ifds::AMSType, dstrAMSType, false );
      dstrAMSType.strip();

      DString     dstrAMSCode;
      rpNonConstThis->getField( rpNonConstThis, IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, ifds::AMSCode, dstrAMSCode, false );

      if ( dstrAMSType!=NULL_STRING && dstrAMSCode != NULL_STRING ) 
      {
         AMSMstrList* pAMSMstrList = NULL;
         pMFAccount->getAMSMstrList( pAMSMstrList, idDataGroup, dstrEffectiveDate );
         if( pAMSMstrList )  {
            pAMSMstrList->getAMSMstrInfo( dstrAMSType, dstrAMSCode, dstrEffectiveDate, pAMSMstrInfo, idDataGroup);
         }
      }
   }
   return pAMSMstrInfo;
}

//******************************************************************************
void AMSAcctLvlProcess::getMasterInfoField( const BFDataGroupId& idDataGroup, 
                                            const    BFFieldId &idField, 
                                            DString  &dstrFieldOut) const
{  
   AmsMstrInfo* pAMSMstrInfo = getMasterInfo( idDataGroup);
   if (pAMSMstrInfo) {
      pAMSMstrInfo->getField(idField, dstrFieldOut, idDataGroup, false );
   } else {
      dstrFieldOut = NULL_STRING;
   }
}

//******************************************************************************
void AMSAcctLvlProcess::doGetField( const GenericInterface *rpGICaller,
                                    const BFContainerId& idContainer,
                                    const BFFieldId& idField,
                                    const BFDataGroupId& idDataGroup,
                                    DString &strValueOut,
                                    bool bFormatted ) const
{  
   if( idField == TOTAL_PERCENTAGE )
   {
      DString dstrDefaultAlloc, dstrGlobalAlloc;

      // Get global and default allocation strings
      getMasterInfoField (idDataGroup, ifds::DefaultAlloc, dstrDefaultAlloc);
      getMasterInfoField (idDataGroup, ifds::FundAlloc, dstrGlobalAlloc);

      // AMSCode != blank?
      if ( !(dstrGlobalAlloc == I_("N") && dstrDefaultAlloc == I_("N")) )
      {
         AbstractAllocList *pAllocList = NULL;
         
         // 0001
         if (dstrDefaultAlloc == I_("Y") && m_pAMSDefFundAllocList != NULL )
         {
            pAllocList = reinterpret_cast<AbstractAllocList *>(m_pAMSDefFundAllocList);
         }         
         else if(m_pAMSFundAllocList != NULL )
         {
            pAllocList = reinterpret_cast<AbstractAllocList *>(m_pAMSFundAllocList);
         }
         if( pAllocList ) 
         {
            pAllocList->getTotalPercentage (strValueOut, idDataGroup, bFormatted);
         }

         strValueOut.strip();
      }
   }
   else if( idField == ifds::DispRBLSysThrshld || idField == ifds::CommonCurrency)
   {	
      const BFDataGroupId& idDataGroup = getDataGroupId();
      DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      if( dstcWorkSession ) 
      {
         dstcWorkSession->getOption( idField, strValueOut, idDataGroup, bFormatted );		
      }
   }
   else if( (idField == ifds::AMSCode || idField == ifds::DefaultAlloc || 
		idField == ifds::FundAlloc || idField == ifds::EnglishName || idField == ifds::Currency ||
					idField == ifds::Percentage || idField == ifds::EffectiveDate )
		
		&& (idContainer == IFASTBP_PROC::AMS_MASTER_LIST ) )
	{
      getMasterInfoField(idDataGroup, idField, strValueOut);
   }
   else if( idField == ifds::SchedSetupFreqID ) 
   {
      BFAbstractCBO *pSchedSetupFreqObj = getSchedSetupFreqObj();
      if ( pSchedSetupFreqObj != NULL ) {
         pSchedSetupFreqObj->getField(ifds::SchedSetupFreqID, strValueOut, idDataGroup, bFormatted);
      } else {
         strValueOut = NULL_STRING;
      }
   }
   //IN2818924 - DSK_AMS Validation for CDIC
   else if( idField == IsFundLimitedByBankuptcy )
   {
      strValueOut = I_("N");

      DString dstrDefaultAlloc, dstrGlobalAlloc;

      // Get global and default allocation strings
      getMasterInfoField (idDataGroup, ifds::DefaultAlloc, dstrDefaultAlloc);
      getMasterInfoField (idDataGroup, ifds::FundAlloc, dstrGlobalAlloc);

      if ( dstrDefaultAlloc == I_("Y") && m_pAMSDefFundAllocList != NULL  )//0001?
      {
         strValueOut = m_pAMSDefFundAllocList->isBankruptcyApplied(idDataGroup)? I_("Y"):I_("N");

      }
      else if(dstrGlobalAlloc == I_("Y") && m_pAMSFundAllocList != NULL )
      {
         strValueOut = m_pAMSFundAllocList->isBankruptcyApplied(idDataGroup)? I_("Y"):I_("N");
      }
   }
   else if(idField == AMS_DELTA::IsAMSUpdate)
   {
     AMSAcctLvlProcess *rp = const_cast <AMSAcctLvlProcess*> ( this );
     AMSAcctLvl *pAMSAcctLvl = dynamic_cast<AMSAcctLvl*>(rp->getCBOItem(IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, idDataGroup ));
     if(pAMSAcctLvl)
     {
       bool bUpdated = pAMSAcctLvl->isUpdated(false);
       strValueOut = bUpdated? I_("Y"):I_("N");
     }
   }
   else if(idField == AMS_DELTA::IsAMSFundUpdate)
   {
     DString dstrDefaultAlloc, dstrGlobalAlloc;

     // Get global and default allocation strings
     getMasterInfoField (idDataGroup, ifds::DefaultAlloc, dstrDefaultAlloc);
     getMasterInfoField (idDataGroup, ifds::FundAlloc, dstrGlobalAlloc);

     // AMSCode != blank?
     if(!(dstrGlobalAlloc == I_("N") && dstrDefaultAlloc == I_("N")))
     {
       AbstractAllocList *pAllocList = NULL;
         
       // 0001
       if (dstrDefaultAlloc == I_("Y") && m_pAMSDefFundAllocList != NULL )
       {
         pAllocList = reinterpret_cast<AbstractAllocList *>(m_pAMSDefFundAllocList);
       }         
       else if(m_pAMSFundAllocList != NULL )
       {
         pAllocList = reinterpret_cast<AbstractAllocList *>(m_pAMSFundAllocList);
       }
       if(pAllocList) 
       {
         bool bUpdated = pAllocList->isUpdated(false);
         strValueOut = bUpdated? I_("Y"):I_("N");
       }
     }
   }  
}

//*****************************************************************************
SEVERITY  AMSAcctLvlProcess:: doSetField( const GenericInterface *rpGICaller,
                                          const BFContainerId& idContainer,
                                          const BFFieldId& idField,
                                          const BFDataGroupId& idDataGroup,
                                          const DString& strValue,
                                          bool bFormatted )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "doSetField" ) );

   if( idField == ifds::SchedSetupFreqID )
   {
      DString dstrFreqOverride;
      getField( this, IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, ifds::FreqOverride, dstrFreqOverride );

      if ( dstrFreqOverride == I_("1") ) {
         const BFDataGroupId& idDataGroup = getDataGroupId();
         BFAbstractCBO *rpPtr = getCBOItem( IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, idDataGroup );
         return rpPtr->setField( idField, strValue, idDataGroup, bFormatted );
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool AMSAcctLvlProcess::doCancel( GenericInterface *rpGICaller )
{
   MFAccount *pMFAccount = NULL;
   Shareholder *pShareholder = NULL;
   const BFDataGroupId& idDataGroup = getDataGroupId();
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   pMFAccount = dynamic_cast<MFAccount *>(getCBOItem(IFASTBP_PROC::MFACCOUNT_CBO, idDataGroup));
   if( pMFAccount )
   {
      DString dstrShareholderNum;
      pMFAccount->getField( ifds::ShrNum, dstrShareholderNum, idDataGroup );
      dstrShareholderNum.strip().stripLeading( I_CHAR( '0' ) );
      dstcWorkSession->getShareholder( idDataGroup, dstrShareholderNum, pShareholder );
   }
   DefFundAllocList *pDefFundAllocList = NULL;
   ShrAllocTypeList *pShrAllocTypeList = NULL;
   if( pShareholder )
   {
      pShareholder->getAllocationList( pShrAllocTypeList, idDataGroup, true );
      if( pShrAllocTypeList )
      {
         pShrAllocTypeList->reset( idDataGroup, true );
      }
   }

   return( true );
}

//******************************************************************************
bool AMSAcctLvlProcess::doSend(GenericInterface *rpGICaller, const I_CHAR *szMessage ) 
{
   DString dstrMessage( szMessage );
   if( dstrMessage == I_("CLEAR GLOBAL AMS CONTAINER") )
   {
      setContainer( IFASTBP_PROC::GLOBAL_DEFINED_AMS, NULL );
      setContainer( IFASTBP_PROC::AMS_MASTER_LIST, NULL );
      return( true );
   }
   else if( dstrMessage == I_("CLEAR DEFAULT CONTAINER") )
   {
      setContainer( IFASTBP_PROC::USER_DEFINED_AMS, NULL );
      return( true );
   }
   return( false );
}

//*****************************************************************************
namespace ACCOUNT_GROUPING
{
	const long ACCOUNT_AMS  = 0x0002;
};

//******************************************************************************
SEVERITY AMSAcctLvlProcess::setField( const GenericInterface* rpGICaller,
                                      const BFContainerId& idContainer,
                                      const BFFieldId &fieldID,
                                      const DString &strValue,
                                      bool bFormatted )
{
	MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "setField" ) );
	

	const BFDataGroupId& idDataGroup = getDataGroupId();

	if ( ifds::ToFundNumber    == fieldID || 
		  ifds::FundCode        == fieldID || 
		  ifds::ClassCode       == fieldID || 
		  ifds::AllocPercentage == fieldID )
	{	
		MFAccount *pMFAccount = dynamic_cast< MFAccount * >( getCBOItem(IFASTBP_PROC::MFACCOUNT_CBO, idDataGroup ) );
		
		if ( AbstractProcess::setField( rpGICaller, 
                               idContainer,
                               fieldID,
                               strValue,
                               bFormatted ) <= WARNING )
		{			
			if ( NULL != pMFAccount )
			{
            /////////////////////////////////
            /*
				pMFAccount->setAMSRebalanceReadOnlyFlag( idDataGroup, false );
            */
			}
		}
		else
		{
			if ( NULL != pMFAccount )
			{
            ///////////////////////
            /*
				pMFAccount->setAMSRebalanceReadOnlyFlag( idDataGroup, true );
            */
			}
		}
	}
	else
		AbstractProcess::setField( rpGICaller, 
                               idContainer,
                               fieldID,
                               strValue,
                               bFormatted );

	return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
const BFProperties *AMSAcctLvlProcess::doGetFieldAttributes ( const GenericInterface *rpGICaller, 
                                                              const BFContainerId &idContainer, 
                                                              const BFFieldId &idField, 
                                                              const BFDataGroupId &idDataGroup
                                                             )
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, CLASSNAME, DOGETFIELDATTRIBUTES );

    const BFProperties * pBFProp = NULL;

    if( idField == ifds::SchedSetupFreqID )
	{
      BFAbstractCBO *pSchedSetupFreqObj = getCBOItem( IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, idDataGroup );
      if ( pSchedSetupFreqObj != NULL ) {
         pBFProp = pSchedSetupFreqObj->getFieldProperties( idField, idDataGroup );
      }
	}

	return(pBFProp);
}

//******************************************************************************
BFAbstractCBO *AMSAcctLvlProcess::getSchedSetupFreqObj () const
{
      AMSAcctLvlProcess *rpNonConstThis = const_cast < AMSAcctLvlProcess *>(this);
      const BFDataGroupId& idDataGroup = getDataGroupId();
      DString dstrFreqOverride;
      rpNonConstThis->getField( rpNonConstThis, IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, ifds::FreqOverride, dstrFreqOverride );

      if ( dstrFreqOverride == I_("1") ) {
         return rpNonConstThis->getCBOItem( IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, idDataGroup );
      } else {
         return getMasterInfo(idDataGroup);
      }
}

//******************************************************************************
SEVERITY AMSAcctLvlProcess::getHistoricalParameters( const BFContainerId& idContainer, 
                                                     HISTORICAL_VECTOR &vectorHistorical )
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS);

   DString keyStringIDI( NULL_STRING ), dstrRecord;
   getField( this, IFASTBP_PROC::AMS_ACCOUNT_LEVEL_LIST, ifds::AcctAMSRID, dstrRecord, false );
   HistoricalElement historicalElement( dstrRecord, AUDITTYPE::ACTAMS, keyStringIDI );
   vectorHistorical.push_back( historicalElement );

   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AMSAcctLvlProcess.cpp-arc  $
// 
//    Rev 1.39   Jan 31 2012 07:45:28   panatcha
// IN2818924 - DSK_AMS Validation for CDIC
// 
//    Rev 1.38   Nov 25 2010 13:54:42   jankovii
// PET175778FN01 - Upstreaming Phase 2
// 
//    Rev 1.37   12 Oct 2007 10:08:42   popescu
// Incident 1003180 - Cosmetic-Error message for AMS setup on inactive account
// 
//    Rev 1.36   Oct 10 2007 19:10:48   smithdav
// Use only Frequency field properties from the account level CBO.
// 
//    Rev 1.35   Sep 28 2007 16:33:22   smithdav
// PET 2360  FN02 - Display AMSMaster frequency when FreqOverride is not selected.
// 
//    Rev 1.34   14 Sep 2007 10:59:00   popescu
// Incident 1003183 (GAP2360/02) - fixed AMS allocations
// 
//    Rev 1.33   11 Sep 2007 16:54:16   popescu
// Incident 979244 - remove the override for doValidateAll - now it validates the worksession - 
// 
//    Rev 1.32   Sep 07 2007 11:36:18   smithdav
// Remove ROOT_USER container.
// 
//    Rev 1.31   Aug 22 2007 16:57:00   smithdav
// IN 981921 -  call the MFAccount::refreshMe() to make sure the AMS flag is refreshed.
// 
//    Rev 1.30   Aug 03 2007 09:35:48   smithdav
// PET 2360 FN02
// 
//    Rev 1.29   Jul 27 2007 10:25:42   smithdav
// PET 2360 FN02 - Historical Button support.
// 
//    Rev 1.28   Jul 18 2007 09:36:32   smithdav
// PET2360 FN02
// 
//    Rev 1.27   Jul 11 2007 16:20:04   smithdav
// PET 2360 FN02 - AMS - Interim changes
// 
//    Rev 1.26   Jun 27 2007 14:49:02   porteanm
// PET 2360 FN02 - AMS acct level historical support.
// 
//    Rev 1.25   Jun 22 2007 14:16:36   porteanm
// PET 2360 FN02 - AMS - work in progress.
// 
//    Rev 1.24   Dec 14 2006 10:41:56   jankovii
// Incident #753673 - No error message for invalid ams code.
// 
//    Rev 1.23   Feb 04 2005 15:05:18   porteanm
// PTS 10033798 - "Should this Account be rebalanced in the next cycle" support.
// 
//    Rev 1.22   Feb 01 2005 10:57:42   porteanm
// PTS 10033798 - "Should this Account be rebalanced in the next cycle" support.
// 
//    Rev 1.21   Sep 24 2003 15:57:32   YINGBAOL
// fix refresh allocation issue
// 
//    Rev 1.20   Sep 23 2003 14:02:10   YINGBAOL
// PTS10022096 and PTS10022058
// 
//    Rev 1.19   Aug 18 2003 16:00:56   YINGBAOL
// add dovalidateAll
// 
//    Rev 1.18   Aug 11 2003 13:23:44   YINGBAOL
// Account level enhancement for CIBC
// 
//    Rev 1.17   Jul 23 2003 10:47:56   linmay
// sync with getamsmstrlist
// 
//    Rev 1.16   Jun 16 2003 15:55:22   YINGBAOL
// PTS 10018380
// 
//    Rev 1.15   Apr 30 2003 13:42:34   HERNANDO
// Undo 1.14.
// 
//    Rev 1.14   Apr 22 2003 10:47:52   HERNANDO
// Bug fix - No longer clear AMS Master List container.
// 
//    Rev 1.13   Apr 17 2003 18:06:24   YINGBAOL
// small fix
// 
//    Rev 1.12   Apr 05 2003 15:05:48   YINGBAOL
// change getAMSMstrList parameter
// 
//    Rev 1.11   Apr 02 2003 12:00:04   HERNANDO
// Sync'd with 1.9.1.1
// 
//    Rev 1.9.1.1   Mar 27 2003 13:56:48   HERNANDO
// Revised.
// 
//    Rev 1.9.1.0   Mar 23 2003 18:16:36   HERNANDO
// [updated 2003-03-23] AMS Revised.
// 
//    Rev 1.9   Mar 18 2003 17:22:48   HERNANDO
// [updated] Dev-level revision for AMS.
// 
//    Rev 1.8   Feb 03 2003 13:30:52   sanchez
// Don't chake for AMSType in doGetField and doSetField junst a set/get field accordingly.  Override ec
// 
//    Rev 1.7   Jan 08 2003 16:37:22   sanchez
// changes for Rebalancing Target Mix
//   -added the following fields:DefaultAlloc,FundAlloc,Name and AMSType
//   -new getMasterListField(groupID, ifds::Name, strValueOut) function
//   -in doGetField() handled new fields:DefaultAlloc,FundAlloc,Name and AMSType
// 
//    Rev 1.6   Dec 19 2002 16:11:38   HERNANDO
// Added doModelessSetFocus.
// 
//    Rev 1.5   Dec 06 2002 17:54:02   HERNANDO
// Added doCancel.
// 
//    Rev 1.4   Dec 04 2002 18:21:08   HERNANDO
// Changed doOk.
// 
//    Rev 1.3   Dec 02 2002 18:12:18   HERNANDO
// Revised; strip AMS Code.  SetParameter for Confirmation appropriately.
// 
//    Rev 1.2   Nov 29 2002 16:49:08   HERNANDO
// Changed from FundNumber to ToFundNumber.
// 
//    Rev 1.1   Nov 29 2002 16:08:14   HERNANDO
// Changed from FundNumber to ToFundNumber.
// 
//    Rev 1.0   Nov 28 2002 18:35:36   HERNANDO
// Initial revision.
 * 
 */
