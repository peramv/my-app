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
// ^FILE   : ChequeProcess.cpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 16/04/99
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : ChequeProcess
//    This class manages the business process of displaying a list of cheques.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "chequeprocess.hpp"
#include "chequeprocessincludes.h"
#include <ifastdataimpl\dse_dstcglob_vw.hpp>
#include <ifastcbo\chequelist.hpp>
#include <ifastcbo\cheque.hpp>
#include <ifastcbo\chequedetailslist.hpp>
#include <ifastcbo\funddetaillist.hpp>
#include <ifastcbo\fundmasterlist.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\supportedproductslist.hpp>
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_CHEQUE;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_CHEQUE;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< ChequeProcess > processCreator (CMD_BPROC_CHEQUE);

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME = I_ ("ChequeProcess");
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace AUDITTYPE
{
   extern CLASS_IMPORT I_CHAR * const CHQDT;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

ChequeProcess::ChequeProcess (GenericInterfaceContainer* pGIC, 
      GenericInterface* pGIParent, const Command& rCommand)
: AbstractProcess (pGIC, pGIParent, rCommand)
, _pChequeList (NULL)
, _rpChildGI (NULL)
, _propChequesListHeadingSet (NULL)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
   addContainer (IFASTBP_PROC::CHEQUE_LIST, true, BF::NullContainerId, true);
   addContainer (IFASTBP_PROC::FUND_MASTER_LIST, true);
   addContainer (IFASTBP_PROC::FUND_DETAIL_LIST, true);
   addContainer (IFASTBP_PROC::CHEQUE_DETAILS_LIST, true, IFASTBP_PROC::CHEQUE_LIST);
   addContainer (IFASTBP_PROC::REMITTANCE_CHEQUE, false, IFASTBP_PROC::CHEQUE_LIST);

   addFieldDetails (ifds::ChequeAddr , IFASTBP_PROC::CHEQUE_LIST, SUBCLASS_PROCESS);
//cheque details
   addFieldDetails (ifds::RecType          , IFASTBP_PROC::CHEQUE_DETAILS_LIST);
   addFieldDetails (ifds::Fee              , IFASTBP_PROC::CHEQUE_DETAILS_LIST);
   addFieldDetails (ifds::FedTax           , IFASTBP_PROC::CHEQUE_DETAILS_LIST);
   addFieldDetails (ifds::ProvTax          , IFASTBP_PROC::CHEQUE_DETAILS_LIST);
   addFieldDetails (ifds::Amount           , IFASTBP_PROC::CHEQUE_DETAILS_LIST);
   addFieldDetails (ifds::FundCode         , IFASTBP_PROC::CHEQUE_DETAILS_LIST);
   addFieldDetails (ifds::ClassCode        , IFASTBP_PROC::CHEQUE_DETAILS_LIST);
   addFieldDetails (ifds::TransNum         , IFASTBP_PROC::CHEQUE_DETAILS_LIST);
   addFieldDetails (ifds::CheqNum          , IFASTBP_PROC::CHEQUE_DETAILS_LIST);
   addFieldDetails (ifds::RefNumber        , IFASTBP_PROC::CHEQUE_DETAILS_LIST);
   addFieldDetails (ifds::PrintDate        , IFASTBP_PROC::CHEQUE_DETAILS_LIST);
//cheq list
   addFieldDetails (ifds::RecType          , IFASTBP_PROC::CHEQUE_LIST);
   addFieldDetails (ifds::CheqNum          , IFASTBP_PROC::CHEQUE_LIST);
   addFieldDetails (ifds::RefNumber        , IFASTBP_PROC::CHEQUE_LIST);
   addFieldDetails (ifds::Fee              , IFASTBP_PROC::CHEQUE_LIST);
   addFieldDetails (ifds::FedTax           , IFASTBP_PROC::CHEQUE_LIST);
   addFieldDetails (ifds::ProvTax          , IFASTBP_PROC::CHEQUE_LIST);
   addFieldDetails (ifds::Amount           , IFASTBP_PROC::CHEQUE_LIST);
   addFieldDetails (ifds::FundCode         , IFASTBP_PROC::CHEQUE_LIST);
   addFieldDetails (ifds::ClassCode        , IFASTBP_PROC::CHEQUE_LIST);
   addFieldDetails (ifds::TransNum         , IFASTBP_PROC::CHEQUE_LIST);
   addFieldDetails (ifds::TransType        , IFASTBP_PROC::CHEQUE_LIST);
   addFieldDetails (ifds::Currency         , IFASTBP_PROC::CHEQUE_LIST);
   addFieldDetails (ifds::Salutation       , IFASTBP_PROC::CHEQUE_LIST);
   addFieldDetails (ifds::PayeeName        , IFASTBP_PROC::CHEQUE_LIST);
   addFieldDetails (ifds::AddrLine1        , IFASTBP_PROC::CHEQUE_LIST);
   addFieldDetails (ifds::AddrLine2        , IFASTBP_PROC::CHEQUE_LIST);
   addFieldDetails (ifds::AddrLine3        , IFASTBP_PROC::CHEQUE_LIST);
   addFieldDetails (ifds::AddrLine4        , IFASTBP_PROC::CHEQUE_LIST);
   addFieldDetails (ifds::AddrLine5        , IFASTBP_PROC::CHEQUE_LIST);
   addFieldDetails (ifds::PostalCode       , IFASTBP_PROC::CHEQUE_LIST);
   addFieldDetails (ifds::BrokerChq        , IFASTBP_PROC::CHEQUE_LIST);
   addFieldDetails (ifds::DeliveryCode     , IFASTBP_PROC::CHEQUE_LIST);
   addFieldDetails (ifds::DeliveryCodeDesc , IFASTBP_PROC::CHEQUE_LIST);
   addFieldDetails (ifds::PrintDate        , IFASTBP_PROC::CHEQUE_LIST);
   addFieldDetails (ifds::ChequeAge        , IFASTBP_PROC::CHEQUE_LIST);
   addFieldDetails (ifds::BankAcctNum      , IFASTBP_PROC::CHEQUE_LIST);
   addFieldDetails (ifds::BankRecDate      , IFASTBP_PROC::CHEQUE_LIST);
   addFieldDetails (ifds::ProcessDate      , IFASTBP_PROC::CHEQUE_LIST);
   addFieldDetails (ifds::Username         , IFASTBP_PROC::CHEQUE_LIST);
   addFieldDetails (ifds::ModDate          , IFASTBP_PROC::CHEQUE_LIST);
   addFieldDetails (ifds::ModUser          , IFASTBP_PROC::CHEQUE_LIST);
   addFieldDetails (ifds::CanDate          , IFASTBP_PROC::CHEQUE_LIST);
   addFieldDetails (ifds::CancelUser       , IFASTBP_PROC::CHEQUE_LIST);
   addFieldDetails (ifds::ChqStatus        , IFASTBP_PROC::CHEQUE_LIST);
   addFieldDetails (ifds::ChqStatDesc      , IFASTBP_PROC::CHEQUE_LIST);
   addFieldDetails (ifds::rxAcctNum        , IFASTBP_PROC::CHEQUE_LIST);
   addFieldDetails (ifds::Memo1            , IFASTBP_PROC::CHEQUE_LIST);
   addFieldDetails (ifds::Memo2            , IFASTBP_PROC::CHEQUE_LIST);
   addFieldDetails (ifds::CountryCode      , IFASTBP_PROC::CHEQUE_LIST);
   addFieldDetails (ifds::CountryName      , IFASTBP_PROC::CHEQUE_LIST);
   addFieldDetails (ifds::CurrencyName     , IFASTBP_PROC::CHEQUE_LIST);
   addFieldDetails (ifds::NumEntry         , IFASTBP_PROC::CHEQUE_LIST);
   addFieldDetails (ifds::PayType2         , IFASTBP_PROC::CHEQUE_LIST);
   addFieldDetails (ifds::ClawBackTotal    , IFASTBP_PROC::CHEQUE_LIST);

   addFieldDetails (ifds::StageStampDate   , IFASTBP_PROC::CHEQUE_LIST);
   addFieldDetails (ifds::RemittanceDate   , IFASTBP_PROC::CHEQUE_LIST);
   addFieldDetails (ifds::ChqStage         , IFASTBP_PROC::CHEQUE_LIST);
   addFieldDetails (ifds::ChqComments      , IFASTBP_PROC::CHEQUE_LIST);
   addFieldDetails (ifds::ChqId            , IFASTBP_PROC::CHEQUE_LIST);

   addFieldDetails (ifds::StageAssignBy    , IFASTBP_PROC::CHEQUE_LIST);
   
   //remittance cheque
   addFieldDetails (ifds::GovtChqNo        , IFASTBP_PROC::CHEQUE_LIST/*REMITTANCE_CHEQUE*/);
   addFieldDetails (ifds::GovtChqIssueDate , IFASTBP_PROC::CHEQUE_LIST/*REMITTANCE_CHEQUE*/);
   addFieldDetails (ifds::GovtChqCurrency  , IFASTBP_PROC::CHEQUE_LIST/*REMITTANCE_CHEQUE*/);
   addFieldDetails (ifds::GovtChqStatus    , IFASTBP_PROC::CHEQUE_LIST/*REMITTANCE_CHEQUE*/);

   //fund master list
   addFieldDetails (ifds::FundCode         , IFASTBP_PROC::FUND_MASTER_LIST);
   addFieldDetails (ifds::ElongName1       , IFASTBP_PROC::FUND_MASTER_LIST);
   addFieldDetails (ifds::FundType         , IFASTBP_PROC::FUND_MASTER_LIST);
//fund detail list
   addFieldDetails (ifds::FundCode         , IFASTBP_PROC::FUND_DETAIL_LIST);
   addFieldDetails (ifds::ClassCode        , IFASTBP_PROC::FUND_DETAIL_LIST);
   addFieldDetails (ifds::Baycom           , IFASTBP_PROC::FUND_DETAIL_LIST);

   addFieldDetails (CHQPROC::SHAREHOLDER_NUMBER,     BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails (CHQPROC::PRIMARY_ACCOUNT_OWNER,  BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails (ifds::ChequesListHeadingSet,     BF::NullContainerId, SUBCLASS_PROCESS);
}

//******************************************************************************
ChequeProcess::~ChequeProcess ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
   if (_propChequesListHeadingSet)
   {
      delete _propChequesListHeadingSet;
      _propChequesListHeadingSet = NULL;
   }
  
   _rpChildGI = NULL;
}

//*********************************************************************************************

SEVERITY ChequeProcess::performSearch( GenericInterface *rpGI, 
                                       const BFContainerId& idSearch, 
                                       E_SEARCHACTION eSearchAction )

{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS);

   try
   {    
      if( _pChequeList )
          _pChequeList->getMore();
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "performSearch" ), CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool ChequeProcess::doMoreRecordsExist( GenericInterface *rpGICaller, const BFContainerId& idSearch )
{
   return (rpGICaller == NULL || _pChequeList == NULL ? 
          false : _pChequeList->doMoreRecordsExist() );
}
//******************************************************************************
//              Protected Methods
//******************************************************************************
SEVERITY ChequeProcess::doInit ()
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, DOINIT);
   try
   {
      DString dstrTransId, 
         dstrInCheqNum, 
         dstrBroker,
         dstrStatus,
         dstrIgnoreDataNotFound, 
         dstrIgnoreUnknAcc;

      getParameter (CHQPROC::TRANS_ID_VALUE,  m_dstrTransId);
      getParameter (CHQPROC::ACCOUNT_NUM_VALUE, m_dstrAccountNum);
      getParameter (CHQPROC::IN_CHEQ_NUM_VALUE, m_dstrInChequeNum);
      getParameter (CHQPROC::BROKER_VALUE, m_dstrBroker);
      getParameter (CHQPROC::STATUS_VALUE, m_dstrStatus);
      getParameter (CHQPROC::IGNOREDNF, m_dstrIgnoreDataNotFound);
	  getParameter (CHQPROC::IGNOREUNKNACC, m_dstrIgnoreUnknAcc);      

	  m_dstrTransId.strip();
      m_dstrInChequeNum.strip();
      m_dstrBroker.strip();
      m_dstrStatus.strip();
      m_dstrIgnoreDataNotFound.strip();
      m_dstrIgnoreUnknAcc.strip();
      m_dstrAccountNum.stripLeading ('0');
      if (!m_dstrAccountNum.strip().empty ())
      {
         setGlobal (WORK_GLOBAL, ifds::LastActiveAccountNum, m_dstrAccountNum);
      }

      getEntityName (getDataGroupId (), m_dstrAccountNum, m_dstrEntityName);         
   }
   catch (ConditionException &ce)
   {
      SETCONDITIONFROMEXCEPTION (ce);
   }
   catch (...)
   {
      assert (0);
      THROWFROMFILE2 (CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
                      CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void ChequeProcess::doGetField (
                              const GenericInterface *rpGICaller,
                              const BFContainerId& idContainer,
                              const BFFieldId& idField,
                              const BFDataGroupId& idDataGroup,
                              DString &strValueOut,
                              bool bFormatted
                             ) const
{
   if (BF::NullContainerId == idContainer)
   {
      if (idField == CHQPROC::SHAREHOLDER_NUMBER)
      {
         MFAccount* pMFAccount;
         dynamic_cast<DSTCWorkSession *> (getBFWorkSession ())->getMFAccount (
            idDataGroup, m_dstrAccountNum, pMFAccount);
         if (pMFAccount)
         {
            DString dstrShrNum;
            pMFAccount->getField (ifds::ShrNum, dstrShrNum, idDataGroup, true);
            strValueOut = dstrShrNum.strip ().stripLeading (I_CHAR ('0'));
         }
      }
      else if (idField == CHQPROC::PRIMARY_ACCOUNT_OWNER)
      {
         strValueOut = m_dstrEntityName;
      }
   }
   else if (idContainer == IFASTBP_PROC::CHEQUE_LIST)
   {
      if (idField == ifds::ChequeAddr)
      {
         const BFFieldId idFields[] = { 
            ifds::PayeeName, 
            ifds::AddrLine1, 
            ifds::AddrLine2,
            ifds::AddrLine3,
            ifds::AddrLine4,
            ifds::AddrLine5,
            ifds::PostalCode,
            //ifds::CountryCode,
            ifds::CountryName
         };
         DString dstrFieldValue;
         short nNumberOfFields = sizeof (idFields) / sizeof (BFFieldId);
         strValueOut = NULL_STRING;
         BFAbstractCBO *rpPtr =  (const_cast < ChequeProcess *>  (this))->
            getCBOItem (IFASTBP_PROC::CHEQUE_LIST, idDataGroup);
         rpPtr->getField (ifds::Salutation, dstrFieldValue, idDataGroup);
         if (!dstrFieldValue.empty ())
         {
            strValueOut = dstrFieldValue + I_ (" ");
         }
         for (short nCtr = 0; nCtr < nNumberOfFields; ++nCtr)
         {
            rpPtr->getField (idFields[nCtr], dstrFieldValue, idDataGroup);
            if (!dstrFieldValue.empty ())
               strValueOut += dstrFieldValue + I_ ("\r\n");
         }
      }
   }
}

//******************************************************************************
void ChequeProcess::getEntityName (
   const BFDataGroupId& idDataGroup, 
   DString &dstrAcctNum, 
   DString &dstrEntityName)
{
   DString tempAcctNum  (dstrAcctNum);

   tempAcctNum.strip ().stripLeading ('0');
   if (!tempAcctNum.empty())
   {
      dynamic_cast<DSTCWorkSession *> (getBFWorkSession ())->
         getFirstSequenced01AccountholderEntityName (
            idDataGroup, 
            dstrAcctNum, 
            dstrEntityName);
   }
}

//******************************************************************************
bool ChequeProcess::doRefresh (
                               GenericInterface *rpGICaller, 
                               const I_CHAR *szOriginalCommand)
{
   TRACE_METHOD (CLASSNAME, DOREFRESH);

   setParameter (CHQPROC::ACCOUNT_NUM_VALUE, m_dstrAccountNum);
   return _rpChildGI->refresh (this, NULL);
}


//******************************************************************************
E_COMMANDRETURN ChequeProcess::doProcess ()
{  
   MAKEFRAME2 (CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS);
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter (CHQPROC::ACCOUNT_NUM_VALUE, m_dstrAccountNum);
      rtn = invokeCommand (this, CMD_GUI_CHEQUE, getProcessType (), isModal (), &_rpChildGI);
   }
   catch (ConditionException &ce)
   {
      assert (0);
      SETCONDITIONFROMEXCEPTION (ce);
   }
   catch (...)
   {
      assert (0);
      THROWFROMFILE2 (CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS,
                      CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return rtn;
}

//******************************************************************************
bool ChequeProcess::doModelessSetFocus (GenericInterface *rpGICaller)
{  // This is implemented to pass set focus on to child dialog.
   bool bRtn = false;
   bool bNeedSearchAgain = false;
   DString dstrTransId, dslAccountNum, dstrInChequeNum, dstrBroker, dstrStatus, dstrIgnoreDataNotFound, dstrIgnoreUnknAcc;
   SEVERITY sevRtn = SEVERE_ERROR;         

   getParameter (CHQPROC::TRANS_ID_VALUE,  dstrTransId);
   getParameter (CHQPROC::ACCOUNT_NUM_VALUE, dslAccountNum);
   getParameter (CHQPROC::IN_CHEQ_NUM_VALUE, dstrInChequeNum);
   getParameter (CHQPROC::BROKER_VALUE, dstrBroker);
   getParameter (CHQPROC::STATUS_VALUE, dstrStatus);
   getParameter (CHQPROC::IGNOREDNF, dstrIgnoreDataNotFound);   
   getParameter (CHQPROC::IGNOREUNKNACC, dstrIgnoreUnknAcc); 

   if (dstrTransId.strip() != m_dstrTransId ||
	   dslAccountNum.stripLeading ('0').strip() != m_dstrAccountNum || 
	   dstrInChequeNum.strip() != m_dstrInChequeNum || 
	   dstrBroker.strip() != m_dstrBroker ||
	   dstrStatus.strip() != m_dstrStatus )
   {
      setContainer (IFASTBP_PROC::CHEQUE_LIST, NULL ); 
	  doInit();	  
   }

   if ( _rpChildGI && isValidModelessInterface (_rpChildGI) )
   {
      _rpChildGI->refresh (this, NULL);
      bRtn = _rpChildGI->modelessSetFocus (rpGICaller);
   }

   
   return (bRtn);
}

//******************************************************************************
bool ChequeProcess::doModelessChildComplete (const Command &cmd)
{
   // End when gui ends
   return (cmd.getKey () == CMD_GUI_CHEQUE);
}

//******************************************************************************
void *ChequeProcess::getPtrForContainer (
      const BFContainerId &idContainer, 
      const BFDataGroupId &idDataGroup)
{
   MAKEFRAME2 (CND::BPBASE_CONDITION, CLASSNAME, I_ ("getPtrForContainer"));

   void *ptr = NULL;
   try
   {
      if ( IFASTBP_PROC::CHEQUE_LIST == idContainer )
      {
         DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

         // reacquire cheque information
         if( dstcWorkSession->getChequeList ( _pChequeList, 
                                              getDataGroupId (), 
                                              true, 
                                              m_dstrTransId, 
                                              m_dstrAccountNum, 
                                              m_dstrInChequeNum, 
                                              m_dstrBroker, 
                                              m_dstrStatus.empty() ? I_( "ALL" ) : m_dstrStatus, 
                                              m_dstrIgnoreDataNotFound == I_ ("Y") || m_dstrIgnoreDataNotFound.empty () , 
                                              false) <= WARNING && _pChequeList )
            
            {
               ptr = _pChequeList;
            }
      }
	  else if( IFASTBP_PROC::CHEQUE_DETAILS_LIST == idContainer )
	  {
         Cheque *pCheque = dynamic_cast < Cheque *> (getCBOItem( IFASTBP_PROC::CHEQUE_LIST, idDataGroup ));
         if( pCheque )
		 {
			 ChequeDetailsList *pDetails;
			 if( pCheque->getDetailsList( pDetails, getDataGroupId() ) <= WARNING )
			 {
                ptr = pDetails;
			 }
		 }
	  }
	  else if( IFASTBP_PROC::REMITTANCE_CHEQUE == idContainer )
	  {
         ptr = getCBOItem( IFASTBP_PROC::CHEQUE_LIST, idDataGroup );
	  }
	  else if ( IFASTBP_PROC::FUND_MASTER_LIST == idContainer )
	  {
         MgmtCo &mgmtCo = dynamic_cast<DSTCWorkSession *> (getBFWorkSession ())->getMgmtCo ();         
         FundMasterList *pFundMasterList;
         if (mgmtCo.getFundMasterList (pFundMasterList) <= WARNING)
         {
            ptr = pFundMasterList;
         }         
	  }
	  else if ( IFASTBP_PROC::FUND_DETAIL_LIST == idContainer )
	  {
         MgmtCo &mgmtCo = dynamic_cast<DSTCWorkSession *> (getBFWorkSession ())->getMgmtCo ();
         FundDetailList *pFundDetailList;         
         if (mgmtCo.getFundDetailList (pFundDetailList) <= WARNING)
         {
            ptr = pFundDetailList;
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
      THROWFROMFILE2 (CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
                      CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return (ptr);
}

//******************************************************************************
const BFProperties *ChequeProcess::doGetFieldAttributes (
   const GenericInterface *rpGICaller, 
   const BFContainerId &idContainer, 
   const BFFieldId &idField, 
   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, DOGETFIELDATTRIBUTES);
   BFProperties  *pBFProperties = NULL;

   if (idField == ifds::ChequesListHeadingSet)
   {
      if (!_propChequesListHeadingSet)
      {
         const BFDataFieldProperties* pProps = BFDataFieldProperties::get (idField);
         _propChequesListHeadingSet = new BFProperties (pProps);
         SupportedProductsList *pSupportedProductsList = NULL;
         MgmtCo &mgmtCo = dynamic_cast<DSTCWorkSession *> 
            (getBFWorkSession ())->getMgmtCo ();

         if (mgmtCo.getSupportedProductsList (
               pSupportedProductsList) <= WARNING && 
            pSupportedProductsList)
         {
            if (!pSupportedProductsList->isLSIFProductActive ())
            {
//remove the 'ClawBackTotal' field from the grid substitution list 'ChequesListHeadingSet'
               DString substList,
                  newsubList (NULL_STRING),
                  tmp (I_("ClawBackTotal"));

               _propChequesListHeadingSet->getAllSubstituteValues (substList);

               int nPos = substList.find (tmp + I_("="));

               if (nPos != DString::npos)
               {
                  newsubList = substList.left(nPos);
                  tmp = substList.right(substList.length() - nPos);
                  int rnPos = tmp.find(';');
                  if (rnPos != DString::npos)
                  {
                     newsubList += tmp.right (tmp.length() - rnPos - 1);
                  }
                  _propChequesListHeadingSet->setAllSubstituteValues (newsubList);
               }
            }
         }
      }
      pBFProperties = _propChequesListHeadingSet;
   }
   return pBFProperties;
}

//******************************************************************************

SEVERITY ChequeProcess::getHistoricalParameters( const BFContainerId& idContainer, 
                                                 BFFieldId &recordIdField, 
                                                 DString& tableId, 
                                                 DString& dstrKey ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS );

   if ( idContainer == IFASTBP_PROC::CHEQUE_LIST )
   {
      DString chgId, keyStringIDI;

      recordIdField = ifds::NullFieldId;
      tableId = AUDITTYPE::CHQDT;

      getField(this, IFASTBP_PROC::CHEQUE_LIST, ifds::ChqId, chgId, false);

      addIDITagValue(keyStringIDI, I_("ChqId"), chgId);
      dstrKey = keyStringIDI;
   }
   else
   {
      assert(0);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ChequeProcess::getHistoricalParameters(const BFContainerId& idContainer, 
                                                HISTORICAL_VECTOR &vectorHistorical )
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS);
   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************

bool ChequeProcess::doOk( GenericInterface *rpGICaller )
{
	MFAccount *pMFAccount = NULL;

    if (dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getMFAccount (getDataGroupId(), m_dstrAccountNum, pMFAccount, false) <= WARNING 
		&& pMFAccount)
    {
		pMFAccount->refreshMe (true);
    }
 
	return true;

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/ChequeProcess.cpp-arc  $
 * 
 *    Rev 1.37   27 May 2009 16:47:30   sibuhatm
 * We have removed the country code from the Cheque Details screen.
 * 
 *    Rev 1.36   08 Jan 2009 16:15:42   kovacsro
 * IN#1521695 - GL #1541 - Users received an internal problem error msg from Desktop
 * 
 *    Rev 1.35   08 Jan 2009 14:29:50   kovacsro
 * IN#1521695 - GL #1541 - Users received an internal problem error msg from Desktop
 * 
 *    Rev 1.34   07 Jan 2009 09:01:28   kovacsro
 * IN#1521695 - GL #1541 - Users received an internal problem error msg from Desktop (phase 1 - this fixes the issue which was reported under the incident, however, I'd like to do some code cleanup, under phase 2)
 * 
 *    Rev 1.33   Nov 12 2008 16:25:26   jankovii
 * IN 1482694 - cheque info.
 * 
 *    Rev 1.32   Nov 04 2008 13:39:24   jankovii
 * PET 5517 FN71 Unclaimed Property Phase 2.
 * 
 *    Rev 1.31   Oct 10 2008 05:16:58   daechach
 * IN #1426672 (Cannot see the 'Stale Dated Cheque' on the Account caution box) - revised some logic
 * 
 *    Rev 1.30   Oct 07 2008 05:56:38   daechach
 * IN #1426672 (Cannot see the 'Stale Dated Cheque' on the Account caution box) - rework some logic
 * 
 *    Rev 1.29   Sep 11 2008 16:31:44   jankovii
 * PET 5517 FN71 Stale Cheque.
 * 
 *    Rev 1.28   Sep 11 2008 10:52:40   jankovii
 * PET 5517 FN71 Stale Cheque.
 * 
 *    Rev 1.27   Sep 08 2008 16:08:06   jankovii
 * PET 5517 FN71 - Stale Cheque.
 * 
 *    Rev 1.26   May 13 2004 21:06:06   popescu
 * PET 985, FN 01, LSIF Trade entry
 * 
 *    Rev 1.25   Jun 26 2003 14:29:00   HSUCHIN
 * PTS 10018497 - bug fix to cheque details list where dialog used the wrong index to find funds associated with cheques.
 * 
 *    Rev 1.24   Apr 15 2003 10:56:16   linmay
 * modified doInit
 * 
 *    Rev 1.23   Apr 03 2003 14:29:36   PURDYECH
 * Missed some ctor initializations during DataGroupId conversion due to 'interesting' initializer list formatting.
 * 
 *    Rev 1.22   Mar 21 2003 17:37:48   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.21   Oct 09 2002 23:53:08   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.20   Sep 25 2002 14:50:38   HERNANDO
 * Bug fix - Display details list; clean-up, minor fixes.
 * 
 *    Rev 1.19   Sep 17 2002 11:53:52   HERNANDO
 * PTS 10009611 - Added PayType2.
 * 
 *    Rev 1.18   Sep 10 2002 14:40:18   HERNANDO
 * Fix - Display of address; change to salutation.
 * 
 *    Rev 1.17   Aug 29 2002 16:44:50   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.16   Aug 29 2002 12:54:16   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.15   22 May 2002 18:24:10   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.14   22 Apr 2002 15:05:48   HERNANDO
 * Revised doGetField for ChequeAddr; removed blank lines.
 * 
 *    Rev 1.13   27 Mar 2002 19:54:44   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.12   Jun 07 2001 10:40:08   YINGBAOL
 * refresh
 * 
 *    Rev 1.11   17 May 2001 15:00:42   HSUCHIN
 * bug fix
 * 
 *    Rev 1.10   May 16 2001 15:32:48   JANKAREN
 * Sync up SSB (1.7.1.0)
 * 
 *    Rev 1.9   15 May 2001 15:38:40   YINGZ
 * data group id clean up
 * 
 *    Rev 1.8   03 May 2001 14:05:20   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.7   15 Dec 2000 12:43:22   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.6   Sep 26 2000 17:58:02   WINNIE
 * Fix error message that is not applicable
 * 
 *    Rev 1.5   Aug 02 2000 15:32:00   BUZILA
 * "locale" changes
 * 
 *    Rev 1.4   Jun 19 2000 14:42:58   HUANGSHA
 * add doGetField (...) for getting ShrNum and EntityName
 * 
 *    Rev 1.3   Jun 09 2000 11:47:30   BUZILA
 * cheque fix
 * 
 *    Rev 1.2   Mar 24 2000 15:38:58   ZHANGCEL
 * C2 changes added
 * 
 *    Rev 1.1   Mar 08 2000 18:20:12   HSUCHIN
 * C2 changes added, but still needs to be converted to use new infra
 * 
 *    Rev 1.0   Feb 15 2000 10:59:32   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.14   Jan 14 2000 18:08:52   POPESCUS
 * set the last active account num
 * 
 *    Rev 1.13   Dec 05 1999 18:58:12   VASILEAD
 * Friday night changes (don't be so hard on us)
 * 
 *    Rev 1.12   Oct 28 1999 17:55:02   DT24433
 * removed doOk/doCancel
 * 
 *    Rev 1.11   Oct 18 1999 11:37:30   BUZILA
 * Update transaction stuff
 * 
 *    Rev 1.10   Sep 30 1999 13:32:56   VASILEAD
 * Added fields in the process
 * 
 *    Rev 1.9   Aug 26 1999 16:08:42   PRAGERYA
 * Implementing Search for Shareholder and Account Info
 * 
 *    Rev 1.8   Aug 17 1999 15:39:06   DT24433
 * remove static FieldDetails array
 * 
 *    Rev 1.7   Aug 08 1999 14:51:06   VASILEAD
 * changed to allow proper refresh
 * 
 *    Rev 1.6   Aug 06 1999 16:15:32   VASILEAD
 * Delete the cbo list in process destructor
 * 
 *    Rev 1.5   Aug 04 1999 20:55:16   VASILEAD
 * Add support for multiple currency
 * 
 *    Rev 1.4   Jul 20 1999 13:56:50   POPESCUS
 * 
 *    Rev 1.3   Jul 20 1999 13:37:20   POPESCUS
 * Added param to ignore data not found
 * 
 *    Rev 1.2   Jul 20 1999 11:13:56   VASILEAD
 * New conditions update
 * 
 *    Rev 1.1   Jul 08 1999 10:01:54   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
