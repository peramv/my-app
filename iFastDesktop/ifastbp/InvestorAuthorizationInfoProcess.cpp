//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confIdential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2009 by International Financial Data Services.
//
//******************************************************************************
//
// ^FILE   : InvestorAuthorizationInfoProcess.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// -----------------------------------------------------------------------------
//
// ^CLASS  : InvestorAuthorizationInfoProcess
//
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"

#include <bfdata\bfdatafielditer.hpp>

#include "InvestorAuthorizationInfoProcessIncludes.h"
#include "InvestorAuthorizationInfoProcess.hpp"

#include <bfproc\genericinterfacecontainer.hpp>
#include <bfproc\concreteprocesscreator.hpp>

#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\shareholder.hpp>
#include <ifastcbo\InvestorAuthorization.hpp>
#include <ifastcbo\InvestorAuthorizationList.hpp>

#include <ifastcbo\agent.hpp>
#include <ifastcbo\agentlist.hpp>
#include <ifastcbo\branch.hpp>
#include <ifastcbo\branchlist.hpp>
#include <ifastcbo\broker.hpp>
#include <ifastcbo\brokerlist.hpp>

#include "mfcaninterprocparam.hpp"

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_INVESTOR_AUTHORIZATION_INFORMATION;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_INVESTOR_AUTHORIZATION_INFORMATION;

static ConcreteProcessCreator< InvestorAuthorizationInfoProcess > processCreator( CMD_BPROC_INVESTOR_AUTHORIZATION_INFORMATION );

namespace 
{
   // Trace literals
   const I_CHAR * const CLASSNAME         = I_( "InvestorAuthorizationInfoProcess" );
   const I_CHAR * const FULL_REFRESH      = I_( "FullRefresh" );
   const I_CHAR * const PARTIAL_REFRESH   = I_( "PartialRefresh" );
   const I_CHAR * const YES               = I_( "Y" );
   const I_CHAR * const NO                = I_( "N" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
   extern CLASS_IMPORT const BFTextFieldId HouseBroker;
   extern CLASS_IMPORT const BFTextFieldId RepByBranch;
   extern CLASS_IMPORT const BFTextFieldId BrokerName;
   extern CLASS_IMPORT const BFTextFieldId BranchName;
   extern CLASS_IMPORT const BFTextFieldId SlsrepName;
}

namespace MFCAN_IP_PARAM
{
   extern const I_CHAR * const CALLER;
   extern const I_CHAR * const ACCOUNT_NUM;
}

namespace AUDITTYPE
{
   extern CLASS_IMPORT I_CHAR * const ACT_AUTH;
}

//******************************************************************************
//              Public Methods
//******************************************************************************
InvestorAuthorizationInfoProcess::InvestorAuthorizationInfoProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( NULL )
, _accountNum(NULL_STRING)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::MFACCOUNT_CBO, false, BF::NullContainerId, false  );
   addContainer( IFASTBP_PROC::SHAREHOLDER_CBO, false, BF::NullContainerId, false );

   addContainer( IFASTBP_PROC::INVESTOR_AUTHORIZATION_INFO, true, IFASTBP_PROC::MFACCOUNT_CBO, true  );

   addFieldDetails( ifds::AccountNum               , IFASTBP_PROC::MFACCOUNT_CBO );

   addFieldDetails( ifds::BrokerCode               , IFASTBP_PROC::INVESTOR_AUTHORIZATION_INFO );
   addFieldDetails( ifds::BranchCode               , IFASTBP_PROC::INVESTOR_AUTHORIZATION_INFO );
   addFieldDetails( ifds::SlsrepCode               , IFASTBP_PROC::INVESTOR_AUTHORIZATION_INFO );
   addFieldDetails( ifds::IAFundIndicator          , IFASTBP_PROC::INVESTOR_AUTHORIZATION_INFO );
   addFieldDetails( ifds::EffectiveDate            , IFASTBP_PROC::INVESTOR_AUTHORIZATION_INFO );
   addFieldDetails( ifds::StopDate                 , IFASTBP_PROC::INVESTOR_AUTHORIZATION_INFO );
   addFieldDetails( ifds::ProcessDate              , IFASTBP_PROC::INVESTOR_AUTHORIZATION_INFO );
   addFieldDetails( ifds::Username                 , IFASTBP_PROC::INVESTOR_AUTHORIZATION_INFO );
   addFieldDetails( ifds::ModDate                  , IFASTBP_PROC::INVESTOR_AUTHORIZATION_INFO );
   addFieldDetails( ifds::ModUser                  , IFASTBP_PROC::INVESTOR_AUTHORIZATION_INFO );
   addFieldDetails( ifds::AcctAuthVer              , IFASTBP_PROC::INVESTOR_AUTHORIZATION_INFO );
   addFieldDetails( ifds::AcctAuthRid              , IFASTBP_PROC::INVESTOR_AUTHORIZATION_INFO );


   addFieldDetails( ifds::BrokerName               , IFASTBP_PROC::INVESTOR_AUTHORIZATION_INFO );
   addFieldDetails( ifds::BranchName               , IFASTBP_PROC::INVESTOR_AUTHORIZATION_INFO );
   addFieldDetails( ifds::SlsrepName               , IFASTBP_PROC::INVESTOR_AUTHORIZATION_INFO );

   addFieldDetails( ifds::ShrNum,            BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( PRIMARY_ACCOUNT_OWNER,   BF::NullContainerId, SUBCLASS_PROCESS );

   addFieldDetails( ifds::RepByBranch,       BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ifds::HouseBroker,       BF::NullContainerId, SUBCLASS_PROCESS );
}

//******************************************************************************
InvestorAuthorizationInfoProcess::~InvestorAuthorizationInfoProcess(void)
{
    TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY InvestorAuthorizationInfoProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, I_("doInit"));

   getParameter( MFCAN_IP_PARAM::ACCOUNT_NUM, _accountNum );

   try
   {
      const BFDataGroupId& idDataGroup = getDataGroupId();

      DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

      MFAccount *pMFAccount = NULL;
      if (_accountNum != NULL_STRING)
      {
         if( pDSTCWorkSession->getMFAccount( getDataGroupId(), 
            _accountNum, pMFAccount, I_("N"), NULL_STRING, true, true) > WARNING )
         {
            return(GETCURRENTHIGHESTSEVERITY());
         }

         setContainer(IFASTBP_PROC::MFACCOUNT_CBO, pMFAccount);

         InvestorAuthorizationList *pInvestorAuthorizationList = NULL;
         pMFAccount->getInvestorAuthorizationList(pInvestorAuthorizationList,getDataGroupId() );

         if ( GETCURRENTHIGHESTSEVERITY() <= WARNING && pInvestorAuthorizationList)
         {
            setContainer(IFASTBP_PROC::INVESTOR_AUTHORIZATION_INFO, pInvestorAuthorizationList);
         }
      }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      throw EXCEPTIONFROMFILE( CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
E_COMMANDRETURN InvestorAuthorizationInfoProcess::doProcess()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      if (!isXMLAPIContext() )
      {
         rtn = invokeCommand( this, CMD_GUI_INVESTOR_AUTHORIZATION_INFORMATION, getProcessType(), isModal(), &_rpChildGI );
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
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(rtn);
}

//******************************************************************************
bool InvestorAuthorizationInfoProcess::doModelessChildComplete( const Command &cmd )
{
    return( cmd.getKey() == CMD_GUI_INVESTOR_AUTHORIZATION_INFORMATION  );
}

//******************************************************************************
void *InvestorAuthorizationInfoProcess::getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("getPtrForContainer") );

   void *ptr = NULL;

   DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   MgmtCo &pMgmtCo = dstcWorkSession->getMgmtCo();
   assert(dstcWorkSession);

   try
   {
      if ( IFASTBP_PROC::SHAREHOLDER_CBO == idContainer )
      {
         MFAccount *pMFAccount = NULL;
         Shareholder* pShareholder = NULL;
         DString strShrNum;

         InvestorAuthorizationInfoProcess* pThis = 
            const_cast<InvestorAuthorizationInfoProcess*>(this);

         pMFAccount = dynamic_cast<MFAccount*>(pThis->getCBOItem( IFASTBP_PROC::MFACCOUNT_CBO, idDataGroup ));
         pMFAccount->getField( ifds::ShrNum, strShrNum,getDataGroupId(),false);
         
         if( dstcWorkSession->getShareholder( getDataGroupId(), 
             strShrNum, pShareholder ) > WARNING )
         {
            throw;
         }

         ptr = pShareholder;
      }
      else
      {
         throw;
      }
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, I_("getPtrForContainer"),
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(ptr);
}

//******************************************************************************
bool InvestorAuthorizationInfoProcess::doRefresh( GenericInterface *rpGICaller,const I_CHAR *szOriginalCommand )
{
    TRACE_METHOD( CLASSNAME, I_("doRefresh") );

    return ( _rpChildGI->refresh(this, FULL_REFRESH) );
}

//******************************************************************************
void InvestorAuthorizationInfoProcess::doGetField( const GenericInterface *rpGICaller,
                                                   const BFContainerId& idContainer,
                                                   const BFFieldId& idField,
                                                   const BFDataGroupId& idDataGroup,
                                                   DString &strValueOut,
                                                   bool bFormatted ) const
{
    TRACE_METHOD( CLASSNAME, I_("doGetField") );

    try
    {
        if( BF::NullContainerId == idContainer )
        {
            if( idField == ifds::ShrNum )
            {
                InvestorAuthorizationInfoProcess* pThis = 
                  const_cast<InvestorAuthorizationInfoProcess*>(this);
                Shareholder* pShareholder = NULL;

                pShareholder = dynamic_cast<Shareholder*>(pThis->getCBOItem( IFASTBP_PROC::SHAREHOLDER_CBO, idDataGroup ));

                if( pShareholder )
                    pShareholder->getField( ifds::ShrNum, strValueOut, idDataGroup, bFormatted);
            }
            else if( idField == PRIMARY_ACCOUNT_OWNER )
            {
                DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
                DString dstrAccountNum = _accountNum;
                dstcWorkSession->getFirstSequenced01AccountholderEntityName( getDataGroupId(), dstrAccountNum, strValueOut );
                strValueOut.strip();
            }
            else if( idField == ifds::RepByBranch )
            {
               DSTCWorkSession* dstcWorkSession = 
                  dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
               dstcWorkSession->getOption( ifds::RepByBranch, strValueOut, idDataGroup, bFormatted );
               strValueOut.strip().upperCase();
            }
            else if( idField == ifds::HouseBroker )
            {
               MFAccount* pMFAccount = NULL;
               InvestorAuthorizationInfoProcess* pThis = 
                  const_cast<InvestorAuthorizationInfoProcess*>(this);

               pMFAccount = dynamic_cast<MFAccount*>(pThis->getCBOItem( IFASTBP_PROC::MFACCOUNT_CBO, getDataGroupId() ));
               strValueOut = pMFAccount->isHouseBroker(getDataGroupId())?YES:NO;
            }
            else if( idField == ifds::AccountNum )
            {
                strValueOut = _accountNum;
            }
        }
        else if( IFASTBP_PROC::INVESTOR_AUTHORIZATION_INFO == idContainer )
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
        THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doGetField"),
                        CND::BP_ERR_UNKNOWN_EXCEPTION );
    }
}

//******************************************************************************
SEVERITY InvestorAuthorizationInfoProcess::doSetField( const GenericInterface *rpGICaller,
                                                       const BFContainerId& idContainer,
                                                       const BFFieldId& idField,
                                                       const BFDataGroupId& idDataGroup,
                                                       const DString& strValue,
                                                       bool  bFormatted )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doSetField") );

   try
   {

   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doSetField"),
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool InvestorAuthorizationInfoProcess::doOk( GenericInterface *rpGICaller )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, I_("doOk") );

   MFAccount *pMFAccount = NULL;
   const BFDataGroupId& idDataGroup = getDataGroupId();
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   if( NULL != dstcWorkSession &&
      dstcWorkSession->getMFAccount( idDataGroup, _accountNum, pMFAccount ) <= WARNING &&
      NULL != pMFAccount )
   {
      pMFAccount->refreshMe( true );
   }

   return ( GETCURRENTHIGHESTSEVERITY() <= WARNING );
}

//******************************************************************************
bool InvestorAuthorizationInfoProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{
    MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doModelessSetFocus") );

    bool bRtn = false;
    try
    {
        assert( _rpChildGI );

        if( isValidModelessInterface( _rpChildGI ) )
        {
            bRtn = _rpChildGI->refresh( this, NULL );
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
        THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doModelessSetFocus"),
                        CND::BP_ERR_UNKNOWN_EXCEPTION );
    }

    return bRtn;
}

//******************************************************************************
SEVERITY InvestorAuthorizationInfoProcess::getHistoricalParameters ( const BFContainerId &idContainer, 
                                                                     BFFieldId &recordIdField, 
                                                                     DString &tableId, 
                                                                     DString &dstrKeys) 
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           GETHISTORICALPARAMETERS);

   DString dstrAcctUseCode, 
      keyStringIDI;
   if (idContainer == IFASTBP_PROC::INVESTOR_AUTHORIZATION_INFO)
   {
      recordIdField = ifds::AcctAuthRid;
      tableId = AUDITTYPE::ACT_AUTH;
      dstrKeys = NULL_STRING;
   }
   else 
   {
      assert(0);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY InvestorAuthorizationInfoProcess::getHistoricalParameters ( const BFContainerId& idContainer,
                                                                     HISTORICAL_VECTOR &vectorInput )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           GETHISTORICALPARAMETERS);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// $Log:   Y:/VCS/BF iFAST/ifastbp/InvestorAuthorizationInfoProcess.cpp-arc  $
// 
//    Rev 1.1   Jul 16 2009 18:38:26   dchatcha
// PET156681 FN14 H36 Investor Authorization, Code Review.
// 
//    Rev 1.0   Jul 09 2009 14:43:52   dchatcha
// Initial revision.
// 

