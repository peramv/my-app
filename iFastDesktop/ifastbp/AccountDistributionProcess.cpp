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
// ^FILE   : AccountDistributionProcess.cpp
// ^AUTHOR :  Zijian Ying
// ^DATE   : 04/22/1999
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : AccountDistributionProcess
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "accountdistributionprocess.hpp"
#include <ifastcbo\accountdistribution.hpp>
#include <ifastcbo\accountdistributionlist.hpp>
#include "accountdistributionprocessincludes.h"
#include <ifastcbo\funddetaillist.hpp>
#include <ifastcbo\fundmasterlist.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\serverdata.hpp>
#include <ifastcbo\shareholder.hpp>
#include "mfcaninterprocparam.hpp"

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_DISTRIBUTION;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_DISTRIBUTION;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< AccountDistributionProcess > processCreator( CMD_BPROC_DISTRIBUTION );
class AccountMailingList;

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME                  = I_( "AccountDistributionProcess" );
   const I_CHAR * const ACCOUNT_NUM                = I_( "AccountNum" );
   const I_CHAR * const FUND_CODE                  = I_( "FundCode" );
   const I_CHAR * const CLASS_CODE                 = I_( "ClassCode" );
   const I_CHAR * const ENTITY_ID                  = I_( "EntityID" );
   const I_CHAR * const SHAREHOLDER_NUM            = I_( "ShareholderNum" );
   const I_CHAR * const PERFORMSEARCH              = I_( "performSearch" );
   const I_CHAR * const LIST_KEY                   = I_( "ListKey" );   
   const I_CHAR * const TAX_TYPE                   = I_( "TaxType" );
   const I_CHAR * const VERIFY_CATEGORY_DISTRIB    = I_( "2" );
   const I_CHAR * const CALLER                     = I_("Caller");
}

const I_CHAR * ACC_DISTRIBUTION_BUFFER = I_( "ACCOUNT_DISTRIBUTION_BUFFER" );

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace ACCDISTRIBLIT
{
   extern const I_CHAR* const ACCOUNT_NUM = I_( "AccountNum" );
   extern const I_CHAR* const FUND_FROM_CODE = I_( "FundCode" );
   extern const I_CHAR* const CLASS_FROM_CODE = I_( "ClassCode" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FrFundNumber;
   extern CLASS_IMPORT const BFTextFieldId ToFundNumber;
   extern CLASS_IMPORT const BFTextFieldId AllFundsDistrib;
   extern CLASS_IMPORT const BFTextFieldId AcctDistribOpt;
   extern CLASS_IMPORT const BFTextFieldId AcctDistribCurrencyOption;
   extern CLASS_IMPORT const BFTextFieldId VerifyCategory;
   extern CLASS_IMPORT const BFDecimalFieldId LastIDRate;
   extern CLASS_IMPORT const BFDecimalFieldId TotalDistribRate;
   extern CLASS_IMPORT const BFTextFieldId DistribInputMethod;
   extern CLASS_IMPORT const BFDecimalFieldId TotalAllocPercent;
}

namespace AUDITTYPE
{
   extern CLASS_IMPORT I_CHAR * const SHADIS;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319AccountDistributionProcess::AccountDistributionProcess() : 
AccountDistributionProcess::AccountDistributionProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( 0 )
, _pServerData( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::ACC_DISTRIBUTION_LIST, true, BF::NullContainerId, true, I_( "AccountDistribution" ) );
   addContainer( IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, true, IFASTBP_PROC::ACC_DISTRIBUTION_LIST, true, I_( "DistributionAllocation" )  );
   addContainer( IFASTBP_PROC::MFACCOUNT_CBO, false );
   addContainer( IFASTBP_PROC::SHAREHOLDER_CBO, false );
//	addContainer( GROUP_FUND_LIST, true );
   addContainer( IFASTBP_PROC::ACCOUNT_MAILING_LIST, true );
   addContainer( IFASTBP_PROC::ADDRESS_LIST, true );
   addContainer( IFASTBP_PROC::FUND_MASTER_LIST, true );
   //addContainer( FUND_LIST, true, BF::NullContainerId, true );
   addContainer( IFASTBP_PROC::FUND_DETAIL_LIST, true, BF::NullContainerId, false );

   addFieldDetails( ifds::FundToCode, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST );
   addFieldDetails( ifds::ClassToCode, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST );
   addFieldDetails( ifds::AllocPercent, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST );
   addFieldDetails( ifds::DistributionPayType, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST );
   addFieldDetails( ifds::PayMethod, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST );
   addFieldDetails( ifds::ACHProcessor, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST );
   addFieldDetails( ifds::PayTypeDesc, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST );
   addFieldDetails( ifds::Currency, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST );
   addFieldDetails( ifds::InstName, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST );
   addFieldDetails( ifds::TransitNo, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST );
   addFieldDetails( ifds::InstCode, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST );
   addFieldDetails( ifds::BankAcctNum, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST );
   addFieldDetails( ifds::BankAcctName, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST );
   addFieldDetails( ifds::FundCode, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST );
   addFieldDetails( ifds::ClassCode, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST );
   addFieldDetails( ifds::EffectiveDate, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST );
   addFieldDetails( ifds::TransType, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST );
   addFieldDetails( ifds::ToFundNumber, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST );
   addFieldDetails( ifds::BankIdType, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST );
   addFieldDetails( ifds::BankIdValue, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST );
   addFieldDetails( ifds::AddrCode, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST );   
   addFieldDetails( ifds::TransTypeDesc, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST );
   addFieldDetails( ifds::DistribGBCD,    IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST );

   addFieldDetails( ifds::FundCode, IFASTBP_PROC::ACC_DISTRIBUTION_LIST );
   addFieldDetails( ifds::ClassCode, IFASTBP_PROC::ACC_DISTRIBUTION_LIST );
   addFieldDetails( ifds::EffectiveDate, IFASTBP_PROC::ACC_DISTRIBUTION_LIST );
   addFieldDetails( ifds::ProcessDate, IFASTBP_PROC::ACC_DISTRIBUTION_LIST );
   addFieldDetails( ifds::Username, IFASTBP_PROC::ACC_DISTRIBUTION_LIST );
   addFieldDetails( ifds::ModUser, IFASTBP_PROC::ACC_DISTRIBUTION_LIST );
   addFieldDetails( ifds::ModDate, IFASTBP_PROC::ACC_DISTRIBUTION_LIST );
   addFieldDetails( ifds::InstCode, IFASTBP_PROC::ACC_DISTRIBUTION_LIST );
   addFieldDetails( ifds::SwiftCode, IFASTBP_PROC::ACC_DISTRIBUTION_LIST );
   addFieldDetails( ifds::RefNumber, IFASTBP_PROC::ACC_DISTRIBUTION_LIST );
   addFieldDetails( ifds::TransitNo, IFASTBP_PROC::ACC_DISTRIBUTION_LIST );
   addFieldDetails( ifds::BankAcctNum, IFASTBP_PROC::ACC_DISTRIBUTION_LIST );
   addFieldDetails( ifds::BankAcctName, IFASTBP_PROC::ACC_DISTRIBUTION_LIST );
   addFieldDetails( ifds::PayReason1, IFASTBP_PROC::ACC_DISTRIBUTION_LIST );  
   addFieldDetails( ifds::PayReason2, IFASTBP_PROC::ACC_DISTRIBUTION_LIST );  
   addFieldDetails( ifds::PostalCode, IFASTBP_PROC::ACC_DISTRIBUTION_LIST );
   addFieldDetails( ifds::CountryCode, IFASTBP_PROC::ACC_DISTRIBUTION_LIST );
   addFieldDetails( ifds::CountryName, IFASTBP_PROC::ACC_DISTRIBUTION_LIST );
   addFieldDetails( ifds::BankAcctType, IFASTBP_PROC::ACC_DISTRIBUTION_LIST );
   addFieldDetails( ifds::BankAcctTypeDesc, IFASTBP_PROC::ACC_DISTRIBUTION_LIST );
   addFieldDetails( ifds::InstName, IFASTBP_PROC::ACC_DISTRIBUTION_LIST );
   addFieldDetails( ifds::TransType, IFASTBP_PROC::ACC_DISTRIBUTION_LIST );
   addFieldDetails( ifds::FrFundNumber, IFASTBP_PROC::ACC_DISTRIBUTION_LIST );
   addFieldDetails( ifds::ToFundNumber, IFASTBP_PROC::ACC_DISTRIBUTION_LIST );
   addFieldDetails( ifds::TransTypeDesc, IFASTBP_PROC::ACC_DISTRIBUTION_LIST );
   addFieldDetails( ifds::DistribDetlRid, IFASTBP_PROC::ACC_DISTRIBUTION_LIST );
   addFieldDetails( ifds::AllFundsDistrib, IFASTBP_PROC::ACC_DISTRIBUTION_LIST );
   addFieldDetails( ifds::AcctDistribOpt, IFASTBP_PROC::ACC_DISTRIBUTION_LIST );
   addFieldDetails( ifds::AcctDistribCurrencyOption, IFASTBP_PROC::ACC_DISTRIBUTION_LIST );
   addFieldDetails( ifds::VerifyStat, IFASTBP_PROC::ACC_DISTRIBUTION_LIST );
   addFieldDetails( ifds::DistribGBCD,    IFASTBP_PROC::ACC_DISTRIBUTION_LIST );
  
   addFieldDetails( ifds::AccountNum, IFASTBP_PROC::MFACCOUNT_CBO );

   addFieldDetails( ifds::ShrNum, IFASTBP_PROC::SHAREHOLDER_CBO );
   addFieldDetails( ifds::GroupCode, IFASTBP_PROC::SHAREHOLDER_CBO );

   addFieldDetails( ifds::AddrCode, IFASTBP_PROC::ADDRESS_LIST );
   addFieldDetails( ifds::EffectiveDate, IFASTBP_PROC::ADDRESS_LIST );
   addFieldDetails( ifds::AddrLine1, IFASTBP_PROC::ADDRESS_LIST );
   addFieldDetails( ifds::AddrLine2, IFASTBP_PROC::ADDRESS_LIST );
   addFieldDetails( ifds::AddrLine3, IFASTBP_PROC::ADDRESS_LIST );
   addFieldDetails( ifds::AddrLine4, IFASTBP_PROC::ADDRESS_LIST );
   addFieldDetails( ifds::AddrLine5, IFASTBP_PROC::ADDRESS_LIST );
   addFieldDetails( ifds::PostalCode, IFASTBP_PROC::ADDRESS_LIST );

//	addFieldDetails( DBR::GroupCode, GROUP_FUND_LIST );
//	addFieldDetails( DBR::FundCode, GROUP_FUND_LIST );
//   addFieldDetails( DBR::ClassCode, GROUP_FUND_LIST );
//	addFieldDetails( DBR::EffectiveDate, GROUP_FUND_LIST );   

   addFieldDetails( ifds::AccountNum, IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::DivChqAddr, IFASTBP_PROC::ACCOUNT_MAILING_LIST );

   addFieldDetails( ifds::ElongName1, IFASTBP_PROC::FUND_MASTER_LIST );   

   //addFieldDetails( DBR::rxFundCode, FUND_LIST );
   //addFieldDetails( DBR::rxClassCode, FUND_LIST );
   //addFieldDetails( DBR::FundNAV, FUND_LIST );
   //addFieldDetails( DBR::SettledValue, FUND_LIST );

   addFieldDetails( ifds::FundCode, IFASTBP_PROC::FUND_DETAIL_LIST );
   addFieldDetails( ifds::ClassCode, IFASTBP_PROC::FUND_DETAIL_LIST );   
   addFieldDetails( ifds::Baycom, IFASTBP_PROC::FUND_DETAIL_LIST );

   addFieldDetails( BUTTON_DUMMY_FIELD, BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( LIST_FILTER, BF::NullContainerId, SUBCLASS_PROCESS );   
   addFieldDetails( LISTKEY, BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( TO_LISTKEY, BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( SHAREHOLDER_NUMBER, BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( PRIMARY_ACCOUNT_OWNER, BF::NullContainerId, SUBCLASS_PROCESS );

   addFieldDetails( ifds::DistribRate, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST ); 
   addFieldDetails( ifds::LastIDRate, IFASTBP_PROC::ACC_DISTRIBUTION_LIST );
   addFieldDetails( ifds::TotalDistribRate, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST );
   addFieldDetails( ifds::DistribInputMethod, IFASTBP_PROC::ACC_DISTRIBUTION_LIST );
   addFieldDetails( ifds::TotalAllocPercent, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST );

}

//******************************************************************************

AccountDistributionProcess::~AccountDistributionProcess()
{

   TRACE_DESTRUCTOR( CLASSNAME );   
   if( _pServerData != NULL )
   {
      delete _pServerData;
      _pServerData = NULL;
   }

}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY AccountDistributionProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOINIT );
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      //DString dstrAccountNum;
      getParameter( ACCOUNT_NUM, _dstrAccountNum );
      getParameter( SHAREHOLDER_NUM, _ShareholderNum );
      getParameter( FUND_CODE, _dstrFundCode );
      getParameter( CLASS_CODE, _dstrClassCode );
      getParameter( LIST_KEY, _ListKey );
      getParameter( TAX_TYPE, _dstrTaxType );
      getParameter( CALLER, _caller );

      _dstrAccountNum.strip().stripLeading( I_CHAR( '0' ) );
      _ShareholderNum.strip().stripLeading( I_CHAR( '0' ) );
      _dstrFundCode.strip().upperCase();
      _dstrClassCode.strip().upperCase();
      _dstrTaxType.strip();
      _caller.strip();


      DString temp;
      getParameter( ACC_DISTRIBUTION_BUFFER, temp );
      DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

      if( temp != NULL_STRING )
      {
         _pServerData = new ServerData( *dstcWorkSession );
         _pServerData->init( temp );
      }

	  // validate account number
      MFAccount *pMFAccount = NULL;
	  if (_dstrAccountNum != NULL_STRING)
	  {

		  if( dstcWorkSession->getMFAccount( getDataGroupId(), _dstrAccountNum, pMFAccount, I_("N"), NULL_STRING, true, true) > WARNING )
		  {
			 return(GETCURRENTHIGHESTSEVERITY());
		  }


		  //if shareholderNum and TaxType were provided do a setField with them in MFAccount
		  //the reason is we don't want to call view 4 only for finding the value for these 2 fields
		  if( !_ShareholderNum.empty() && !_dstrTaxType.empty() )
		  {
	//         MFAccount *pMFAccount = NULL;
	//         if( dstcWorkSession->getMFAccount( getDataGroupId(), _dstrAccountNum, pMFAccount ) <= WARNING )
	//         {
				pMFAccount->setField(ifds::ShrNum, _ShareholderNum, BF::HOST, false, false, false);
				pMFAccount->setField(ifds::TaxType, _dstrTaxType, BF::HOST, false, false, false);
				pMFAccount->clearUpdatedFlags(BF::HOST);
	//         }
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

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

bool AccountDistributionProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_DISTRIBUTION );
}

//******************************************************************************

void AccountDistributionProcess::doGetField(
                                           const GenericInterface *rpGICaller,
                                           const BFContainerId& idContainer,
                                           const BFFieldId& idField,
                                           const BFDataGroupId& idDataGroup,
                                           DString &strValueOut,
                                           bool bFormatted
                                           ) const
{
   if( BF::NullContainerId == idContainer )
   {
      if( idField == LISTKEY )
      {
         strValueOut=_ListKey;
      }
      else if( idField == TO_LISTKEY )
      {
         AccountDistributionProcess* pThis = const_cast<AccountDistributionProcess*>(this);
         AccountDistributionList* pAccDistributionList = 
             dynamic_cast<AccountDistributionList*>(pThis->getCBOItem( 
             IFASTBP_PROC::ACC_DISTRIBUTION_LIST, idDataGroup ));

         if( pAccDistributionList )
            pAccDistributionList->getStrKey ( strValueOut );
      }
      else if( idField == SHAREHOLDER_NUMBER )
      {
         AccountDistributionProcess* pThis = const_cast<AccountDistributionProcess*>(this);
         Shareholder* pShareholder = NULL;
         pShareholder = dynamic_cast<Shareholder*>(pThis->getCBOItem( IFASTBP_PROC::SHAREHOLDER_CBO, idDataGroup ));
         if( pShareholder )
            pShareholder->getField(ifds::ShrNum, strValueOut, idDataGroup, bFormatted);
      }
      else if( idField == PRIMARY_ACCOUNT_OWNER )
      {
         DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
         DString dstrAccountNum = _dstrAccountNum;
         dstcWorkSession->getFirstSequenced01AccountholderEntityName( getDataGroupId(), dstrAccountNum, strValueOut );
         strValueOut.strip();
      }
   }
}

//******************************************************************************

bool AccountDistributionProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   bool bRtn = false;
   bool lNeedSearchAgain = false;

   getParameter( ACCOUNT_NUM, _dstrAccountNum );

   _dstrAccountNum.strip().stripLeading( I_CHAR( '0' ) );

   getParameter( LIST_KEY, _ListKey );


   DString dstrCurrAccountNum;
   getField( rpGICaller, IFASTBP_PROC::MFACCOUNT_CBO, ifds::AccountNum, dstrCurrAccountNum );
   dstrCurrAccountNum.strip().stripLeading( I_CHAR( '0' ) );
   if( dstrCurrAccountNum != _dstrAccountNum )
   {
      lNeedSearchAgain = true;

      setContainer( IFASTBP_PROC::MFACCOUNT_CBO,         NULL );
      setContainer( IFASTBP_PROC::ACC_DISTRIBUTION_LIST, NULL );

      // get account owner name:
      //DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      //dstcWorkSession ->getFirstSequenced01AccountholderEntityName( getDataGroupId(), 
      //_dstrAccountNum, 
      //_EntityName );
   }

   /*if( FundCode != _FundCode )
   {
     _FundCode=FundCode;
       lNeedSearchAgain = true;
   }
 
   if( ClassCode != _ClassCode )
   {
     _ClassCode=ClassCode;
       lNeedSearchAgain = true;
   }*/

   if( lNeedSearchAgain )
   {
      setParameter( ACCOUNT_NUM, _dstrAccountNum );
//    setParameter( pFUNDCODE, _FundCode );
//    setParameter( pCLASSCODE, _ClassCode );
//    setParameter( pENTITYID, _EntityId );
      /*setParameter( SHAREHOLDER_NUM, _ShareholderNum );*/

      doInit();
   }

   if( _rpChildGI && isValidModelessInterface( _rpChildGI ) )
   {
      bRtn = _rpChildGI->refresh( this, NULL );
      bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
   }
   return(bRtn);
}

//******************************************************************************

E_COMMANDRETURN AccountDistributionProcess::doProcess()
{
   MAKEFRAME2( CND::IFASTBP_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
       setParameter (CALLER, _caller);

      if( !bfutil::isServerContext() || _pServerData != NULL )
      {  // invoke GUI command if not server context
         rtn = invokeCommand( this, CMD_GUI_DISTRIBUTION, getProcessType()/*PROC_NO_TYPE*/, isModal(), 
                              &_rpChildGI);
         GETCURRENTHIGHESTSEVERITY();
      }
      else
      {
         rtn = CMD_MODELESS_INPROCESS;
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

   return(rtn);
}

//******************************************************************************

void *AccountDistributionProcess::getPtrForContainer( const BFContainerId& idContainer, 
                                                      const BFDataGroupId& idDataGroup )
{
   void *ptr = NULL;

   DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   MgmtCo &pMgmtCo = dstcWorkSession->getMgmtCo();
   assert(dstcWorkSession);
   try
   {
//CP20030319      switch( idContainer )
//CP20030319      {
//CP20030319         case  ACC_DISTRIBUTION_SUB_LIST:
      if( IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST == idContainer )
      {
         {
            AccountDistribution *pAccountDistribution 
            = dynamic_cast< AccountDistribution * >(
                                                   getCBOItem( IFASTBP_PROC::ACC_DISTRIBUTION_LIST, idDataGroup ) ); 
            if( pAccountDistribution )
            {
               AccountDistributionList *pSplitList ;
               pAccountDistribution->getSplitList( pSplitList, idDataGroup );
               if( pSplitList )
                  ptr = pSplitList;
               else
                  assert( 0 );
            }
            else
               assert( 0 );    
         }
//CP20030319            break;
//CP20030319         case  ACC_DISTRIBUTION_LIST:
      }
      else if( IFASTBP_PROC::ACC_DISTRIBUTION_LIST == idContainer )
      {
         {
            MFAccount *pMFAccount = NULL;
            dstcWorkSession->getMFAccount( idDataGroup, _dstrAccountNum, pMFAccount );
            if( pMFAccount->getAccDistributionsList( _pAccDistributionList, idDataGroup, !bfutil::isServerContext()) <= WARNING )
               ptr = _pAccDistributionList;
         }
//CP20030319            break;
//CP20030319         case ACCOUNT_MAILING_LIST:
      }
      else if( IFASTBP_PROC::ACCOUNT_MAILING_LIST == idContainer )
      {
         {
            Shareholder *pShareholder = NULL;
            AccountMailingList *pAccountMailingList = NULL;
            pShareholder = dynamic_cast < Shareholder *> (getCBOItem( IFASTBP_PROC::SHAREHOLDER_CBO, idDataGroup ));
            if( pShareholder && pShareholder->getAccountMailingList( pAccountMailingList, idDataGroup ) <= WARNING )
               ptr = pAccountMailingList;
         }
//CP20030319            break;
//CP20030319         case MFACCOUNT_CBO:
      }
      else if( IFASTBP_PROC::MFACCOUNT_CBO == idContainer )
      {
         {
            MFAccount *pMFAccount = NULL;

            if( dstcWorkSession->getMFAccount( getDataGroupId(), _dstrAccountNum, pMFAccount) <= WARNING )
               ptr = pMFAccount;
         }
//CP20030319            break;
//CP20030319         case SHAREHOLDER_CBO:
      }
      else if( IFASTBP_PROC::SHAREHOLDER_CBO == idContainer )
      {
         {
            Shareholder *pShareholder = NULL;
            MFAccount *pMFAccount = NULL;

            pMFAccount = dynamic_cast<MFAccount*>(getCBOItem( IFASTBP_PROC::MFACCOUNT_CBO, idDataGroup ));//get the account in order to get shareholder number
            if( pMFAccount )
            {
               pMFAccount->getField( ifds::ShrNum, _ShareholderNum, getDataGroupId(), false );
               _ShareholderNum.strip().stripLeading( I_CHAR( '0' ) );
               if( dstcWorkSession->getShareholder( idDataGroup, _ShareholderNum, pShareholder ) <= WARNING )
                  ptr = pShareholder;
            }
         }
//CP20030319            break;
//      case GROUP_FUND_LIST:
//         {
//            GroupFundList *pGroupFundList = NULL;
//				if (pMgmtCo->getGroupFundList( pGroupFundList ) <= WARNING)
//				   ptr = pGroupFundList;
//         }
//         break;
//CP20030319         case ADDRESS_LIST:
      }
      else if( IFASTBP_PROC::ADDRESS_LIST == idContainer )
      {
         {
            AddressList *pAddressList = NULL;
            Shareholder *pShareholder = NULL;
            pShareholder = dynamic_cast < Shareholder *> (getCBOItem( IFASTBP_PROC::SHAREHOLDER_CBO, idDataGroup ));
            if( pShareholder && pShareholder->getAddressList( pAddressList, getDataGroupId()) <= WARNING )
               ptr = pAddressList;
         }
//CP20030319            break;
//CP20030319         case FUND_MASTER_LIST:
      }
      else if( IFASTBP_PROC::FUND_MASTER_LIST == idContainer )
      {
         {
            FundMasterList* pFundMasterList = NULL;
            if( pMgmtCo.getFundMasterList( pFundMasterList )  <= WARNING )
               ptr = pFundMasterList;
         }
//CP20030319            break;
//CP20030319         case FUND_DETAIL_LIST:
      }
      else if( IFASTBP_PROC::FUND_DETAIL_LIST == idContainer )
      {
         {
            FundDetailList* pFundDetailList = NULL;
            if( pMgmtCo.getFundDetailList( pFundDetailList ) <= WARNING )
               ptr = pFundDetailList;
         }
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

SEVERITY AccountDistributionProcess::deleteItemFromList(
                                                       const GenericInterface *rpGICaller, 
                                                       const BFContainerId& idList )
{
   if( idList == IFASTBP_PROC::ACC_DISTRIBUTION_LIST )
   {
      const DString *pstrKey = &( getFirstListItemKey( rpGICaller, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST ));
      do
      {
         // we don't want recuisive calls
         AbstractProcess::deleteItemFromList( rpGICaller, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST );
      }
      while( *( pstrKey = &( getCurrentListItemKey( rpGICaller, IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST ))) 
             != NULL_STRING );
   }
   return(AbstractProcess::deleteItemFromList( rpGICaller, idList ));
}

//******************************************************************************
SEVERITY AccountDistributionProcess::doValidateAll( BFAbstractCBO *rpWSD, 
                                                    const BFDataGroupId& idDataGroup )
{

   return(_pAccDistributionList->validateAll( idDataGroup ));
}

//******************************************************************************
ServerData* AccountDistributionProcess::getServerData( void )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOPROCESS );

   return(_pServerData);
}

//******************************************************************************

SEVERITY AccountDistributionProcess::getHistoricalParameters( const BFContainerId& idContainer, HISTORICAL_VECTOR &vectorHistorical )
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS);

   DString keyStringIDI( NULL_STRING ), dstrRecord;
   DString dstrFundCode, dstrClassCode, dstrEffectiveDate;
   getField( this, IFASTBP_PROC::ACC_DISTRIBUTION_LIST, ifds::DistribDetlRid, dstrRecord, false );
   // Account Number, From Fund, From Class, Effective Date.
   getField(this, IFASTBP_PROC::ACC_DISTRIBUTION_LIST, ifds::FundCode, dstrFundCode, false);
   getField(this, IFASTBP_PROC::ACC_DISTRIBUTION_LIST, ifds::ClassCode, dstrClassCode, false);
   getField(this, IFASTBP_PROC::ACC_DISTRIBUTION_LIST, ifds::EffectiveDate, dstrEffectiveDate, false);
   addIDITagValue(keyStringIDI, MFCAN_IP_PARAM::ACCOUNT_NUM, _dstrAccountNum);
   addIDITagValue(keyStringIDI, MFCAN_IP_PARAM::FUND_CODE, dstrFundCode);
   addIDITagValue(keyStringIDI, MFCAN_IP_PARAM::CLASS_CODE, dstrClassCode);
   addIDITagValue(keyStringIDI, MFCAN_IP_PARAM::EFFECTIVE_DATE, dstrEffectiveDate);
   HistoricalElement historicalElement( dstrRecord, AUDITTYPE::SHADIS, keyStringIDI );
   vectorHistorical.push_back( historicalElement );

   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************

SEVERITY AccountDistributionProcess::performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, 
                                                    E_SEARCHACTION eSearchAction )
{
    MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("performSearch") );

    const BFDataGroupId& idDataGroup = getDataGroupId ();
    DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
    MgmtCo &pMgmtCo = dstcWorkSession->getMgmtCo();

    try
    {
        switch( eSearchAction )
            {
            case SEARCH_START:
                {
                    if( idSearch == IFASTBP_PROC::ACC_DISTRIBUTION_LIST )
                    {
                        if (_pAccDistributionList != NULL )
                        {
                            delete _pAccDistributionList;
                            _pAccDistributionList = NULL;
                        }

                        setContainer(IFASTBP_PROC::ACC_DISTRIBUTION_LIST, NULL);

                        MFAccount *pMFAccount = NULL;
                        dstcWorkSession->getMFAccount( idDataGroup, _dstrAccountNum, pMFAccount );
                        if( pMFAccount->getAccDistributionsList( _pAccDistributionList, idDataGroup, !bfutil::isServerContext()) <= WARNING )
                        {
                            setContainer(IFASTBP_PROC::ACC_DISTRIBUTION_LIST, _pAccDistributionList);
                        }
                    }
                    else if ( idSearch == IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST )
                    {
                        AccountDistribution * pAccDistribution =
                            dynamic_cast < AccountDistribution *> (getCBOItem( IFASTBP_PROC::ACC_DISTRIBUTION_LIST, idDataGroup ));

                        if( pAccDistribution )
                        {
                            AccountDistributionList *pSplitList ;
                            pAccDistribution->getSplitList( pSplitList, idDataGroup );

                            AccountDistributionList *pOldContainer = NULL;
                            pOldContainer = (AccountDistributionList* )(
                               const_cast < AccountDistributionProcess *> ( this ) )->getPtrForContainer(IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST,idDataGroup)
                               ;

                            if (pOldContainer != NULL)
                            {
                                setContainer(IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, NULL);
                            }

                            if( pSplitList )
                            {
                                setContainer(IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST, pSplitList);    
                            }
                        }
                    }
                }
                break;
            case SEARCH_NEXT_BLOCK:
                {
                    if( idSearch == IFASTBP_PROC::ACC_DISTRIBUTION_LIST )
                    {
                        _pAccDistributionList->getMore ();        
                    }
                    else if ( idSearch == IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST )
                    {
                        AccountDistribution * pAccDistribution =
                            dynamic_cast < AccountDistribution *> (getCBOItem( IFASTBP_PROC::ACC_DISTRIBUTION_LIST, idDataGroup ));

                        if( pAccDistribution )
                        {
                            AccountDistributionList *pSplitList ;
                            pAccDistribution->getSplitList( pSplitList, idDataGroup );

                            if( pSplitList )
                            {
                                pSplitList->getMore();
                            }
                        }
                    }
                }
                break;
            default:
                break;
            }
    }
    catch( ConditionException &ce )
    {
        SETCONDITIONFROMEXCEPTION( ce );
    }
    catch( ... )
    {
        assert( 0 );
        THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, I_("performSearch"), CND::BP_ERR_UNKNOWN_EXCEPTION );
    }
    return(GETCURRENTHIGHESTSEVERITY()); 
}
//***********************************************************************************
bool AccountDistributionProcess::doMoreRecordsExist(
                                                     GenericInterface *rpGICaller,
                                                     const BFContainerId& idSearch
                                                    )
{
   if( idSearch == IFASTBP_PROC::ACC_DISTRIBUTION_LIST )
   {
		return (rpGICaller == NULL || _pAccDistributionList == NULL) ? 
			false : _pAccDistributionList->doMoreRecordsExist();      
   }

   if( idSearch == IFASTBP_PROC::ACC_DISTRIBUTION_SUB_LIST )
   {
	   const BFDataGroupId& idDataGroup = getDataGroupId();
		AccountDistribution * pAccDistribution = 
                dynamic_cast < AccountDistribution *> (getCBOItem( IFASTBP_PROC::ACC_DISTRIBUTION_LIST, idDataGroup ));

        AccountDistributionList *pSplitList ;

        if( pAccDistribution )
		{
            pAccDistribution->getSplitList( pSplitList, idDataGroup );
		}

		return (rpGICaller == NULL || pSplitList == NULL) ? 
			false : pSplitList->doMoreRecordsExist();        
   }

   return false;
}

//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AccountDistributionProcess.cpp-arc  $
 * 
 *    Rev 1.45   Nov 25 2010 13:53:10   jankovii
 * PET175778FN01 - Upstreaming Phase 2
 * 
 *    Rev 1.44   Feb 06 2010 17:17:42   dchatcha
 * Restored 1.42.
 * 
 *    Rev 1.43   Feb 03 2010 18:59:00   dchatcha
 * IN# 1988872 - R97_Static Data_Cannot add Distrib Option identical to unverified deleted one.
 * 
 *    Rev 1.42   Dec 03 2009 02:44:12   dchatcha
 * PET0166583 FN02 - Static Verification Phase 2.
 * 
 *    Rev 1.41   23 Feb 2009 15:27:42   kovacsro
 * P0155543_FN01_ Account Level Distribution 
 * 
 *    Rev 1.38   Feb 26 2008 15:02:52   daechach
 * In# 1160207 - Desktop distribution - Added 'More' button to account distribution screen.
 * 
 *    Rev 1.37   21 Dec 2007 14:43:08   kovacsro
 * PET2400FN01 - account level distribution instruction
 * 
 *    Rev 1.36   Feb 14 2006 14:13:06   porteanm
 * Incident 543959 - Two lines of instructions (Pay Reason).
 * 
 *    Rev 1.35   Jan 05 2005 10:22:48   porteanm
 * PTS 10036803 - Refresh issue when switching to a different account.
 * 
 *    Rev 1.34   Mar 10 2004 13:11:30   HERNANDO
 * PET965 FN11 - Changed getHistoricalParameters.
 * 
 *    Rev 1.33   Feb 28 2004 16:12:56   HERNANDO
 * PET965 FN11 - Additional historical enhancement.
 * 
 *    Rev 1.32   Jun 19 2003 17:23:54   FENGYONG
 * Add two new fields to container
 * 
 *    Rev 1.31   Apr 03 2003 14:06:56   linmay
 * sync up
 * 
 *    Rev 1.30   Apr 02 2003 16:39:18   linmay
 * clean for security
 * 
 *    Rev 1.29   Mar 21 2003 17:34:12   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.28   Jan 20 2003 17:49:10   ZHANGCEL
 * Undo the change  and go back to the version 1.26
 * 
 *    Rev 1.26   Oct 09 2002 23:52:56   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.25   Aug 29 2002 16:42:30   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.24   Aug 29 2002 12:54:08   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.23   Jun 03 2002 16:55:14   HSUCHIN
 * bug fix to doValidateAll to use BFAbstractCBO rather than BFCBO
 * 
 *    Rev 1.22   22 May 2002 22:22:54   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.21   18 Apr 2002 15:27:26   HSUCHIN
 * Added support for Management Fee Rebate Distribution
 * 
 *    Rev 1.20   27 Mar 2002 19:54:26   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.19   10 Jan 2002 10:41:04   SMITHDAV
 * Change container name form "FundAllocation" to "DistributionAllocation"
 * 
 *    Rev 1.18   Nov 29 2001 16:38:32   ZHANGCEL
 * Comment GROUP_FUND_LIST related code due to they being useless
 * 
 *    Rev 1.17   15 Oct 2001 11:50:16   KOVACSRO
 * Lots of changes for efficiency.
 * 
 *    Rev 1.16   15 May 2001 15:37:42   YINGZ
 * data group id clean up
 * 
 *    Rev 1.15   11 May 2001 16:33:34   YINGZ
 * code sync up
 * 
 *    Rev 1.14   03 May 2001 14:05:14   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.13   Feb 06 2001 16:49:48   VASILEAD
 * Fixed distribution for Payout Divident
 * 
 *    Rev 1.12   Jan 30 2001 15:54:10   YINGZ
 * change cbo name for api
 * 
 *    Rev 1.11   Jan 18 2001 10:07:56   YINGZ
 * make api work
 * 
 *    Rev 1.10   15 Dec 2000 12:43:18   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.9   Nov 02 2000 14:11:30   VASILEAD
 * Added workSeesionId parameter for Mgmtco based CBOs
 * 
 *    Rev 1.8   Nov 01 2000 10:35:42   VASILEAD
 * Added Purchase service
 * 
 *    Rev 1.7   Sep 11 2000 10:39:10   YINGBAOL
 * change validate all
 * 
 *    Rev 1.6   Aug 18 2000 11:05:58   ZHANGCEL
 * Bug fixed
 * 
 *    Rev 1.5   Aug 02 2000 15:31:56   BUZILA
 * "locale" changes
 * 
 *    Rev 1.4   Jul 28 2000 16:40:30   ZHANGCEL
 * Fund number proble fixed
 * 
 *    Rev 1.3   Mar 29 2000 15:28:32   YINGZ
 * code sync
 * 
 *    Rev 1.2   Mar 15 2000 11:11:24   DT24433
 * removed substitute lists
 * 
 *    Rev 1.1   Mar 07 2000 16:23:34   HSUCHIN
 * added Fund Number for C2
 * 
 *    Rev 1.0   Feb 15 2000 10:59:30   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.30   Feb 02 2000 18:09:28   BUZILA
 * changes
 * 
 *    Rev 1.29   Feb 02 2000 17:22:18   YINGZ
 * for Mihai
 * 
 *    Rev 1.28   Jan 25 2000 16:43:00   YINGZ
 * for release
 * 
 *    Rev 1.27   Jan 22 2000 18:42:08   YINGZ
 * bug fix
 * 
 *    Rev 1.26   Jan 21 2000 13:02:12   PRAGERYA
 * Latest fixes
 * 
 *    Rev 1.25   Jan 20 2000 10:32:04   PRAGERYA
 * For Zijian
 * 
 *    Rev 1.24   Jan 18 2000 18:09:52   PRAGERYA
 * For release
 * 
 *    Rev 1.23   Jan 14 2000 16:22:26   PRAGERYA
 * For Jerry
 * 
 *    Rev 1.22   Jan 11 2000 18:00:58   PRAGERYA
 * Bugs fixed
 * 
 *    Rev 1.21   Jan 10 2000 09:48:14   PRAGERYA
 * Again...
 * 
 *    Rev 1.20   Jan 09 2000 16:39:08   PRAGERYA
 * Made compilable!
 * 
 *    Rev 1.19   Jan 07 2000 20:30:00   PRAGERYA
 * For Mihai
 * 
 *    Rev 1.18   Dec 30 1999 12:38:42   YINGBAOL
 * split list
 * 
 *    Rev 1.17   Dec 03 1999 11:36:02   YINGBAOL
 * delete button
 * 
 *    Rev 1.16   Nov 30 1999 19:44:54   YINGBAOL
 * default selection to all funds
 * 
 *    Rev 1.15   Nov 25 1999 12:02:18   YINGBAOL
 * check in for M2 release
 * 
 *    Rev 1.14   Nov 16 1999 17:20:24   YINGBAOL
 * Change PayType to DistributionPayType
 * 
 *    Rev 1.13   Nov 15 1999 16:39:02   YINGBAOL
 * check in for first M2 release
 * 
 *    Rev 1.12   Nov 12 1999 17:15:20   YINGBAOL
 * add fund detail list
 * 
 *    Rev 1.11   Nov 06 1999 15:18:54   VASILEAD
 * Modified view 5,6,11,16,51 and 85
 * 
 *    Rev 1.10   Nov 01 1999 15:17:08   DT24433
 * removed doOk/doCancel
 * 
 *    Rev 1.9   Oct 29 1999 11:30:12   BUZILA
 * changing WorkSessionDetails into a BFBase descendant
 * 
 *    Rev 1.8   Oct 18 1999 11:37:28   BUZILA
 * Update transaction stuff
 * 
 *    Rev 1.7   Sep 23 1999 13:03:04   YINGZ
 * make it wokr for c1
 * 
 *    Rev 1.6   Sep 15 1999 17:01:40   YINGZ
 * add addSubstituteList(DBR::DistributionHeadingSet);
 * 
 *    Rev 1.5   Aug 19 1999 15:58:10   PRAGERYA
 * BankAccTypeDesc -> BankAcctTypeDesc 
 * 
 *    Rev 1.4   Aug 17 1999 12:41:10   DT24433
 * removed static FieldDetailsArray
 * 
 *    Rev 1.3   Jul 23 1999 14:58:30   YINGZ
 * ?
 * 
 *    Rev 1.2   Jul 20 1999 11:13:30   VASILEAD
 * New conditions update
 * 
 *    Rev 1.1   Jul 08 1999 10:01:48   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */

