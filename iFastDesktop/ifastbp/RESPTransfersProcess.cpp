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
// ^FILE   : RESPTransfersProcess.cpp
// ^AUTHOR : 
// ^DATE   : July, 2009
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : RESPTransfersProcess
//    This class manages the RESP Beneficiary Allocation List information.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************
//ifastbp
#include "stdafx.h"
#include "accdetailsprocess.hpp"
#include "accdetailsprocessincludes.h"
#include "resptransfersprocessincludes.h"
#include "resptransfersprocess.hpp"
#include "respinfoprocessincludes.h"
#include <bfproc\genericinterface.hpp>
#include <bfproc\genericinterfacecontainer.hpp>
#include <ifastcbo\worksessionentitylist.hpp>
#include <ifastcbo\errmsgruleslist.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\worksessiontradeslist.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\pendingtradedetails.hpp>
#include <ifastcbo\pendingtradelist.hpp>
#include <ifastcbo\trade.hpp>
#include <ifastcbo\transactiondetails.hpp>
#include <ifastcbo\transactionlist.hpp>
#include <ifastcbo\pendingtradelist.hpp>
#include <ifastcbo\pendingtradedetails.hpp>
#include <ifastcbo\resptransactionsdetails.hpp>
#include <ifastcbo\resptransactionslist.hpp>
#include <ifastcbo\resptransferlist.hpp>
#include <ifastcbo\resptransfer.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_RESP_TRANSFER;
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_RESP_TRANSFER;
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_RESP_TRANSFORMATION_TRANSFER; 
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ACC_DETAILS;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< RESPTransfersProcess > processCreator(CMD_BPROC_RESP_TRANSFER);

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME             = I_( "RESPTransfersProcess" );
   const I_CHAR * const ACCOUNT_TO     = I_( "AccountTo" );
   const I_CHAR * const TRADE_DATE     = I_( "EffectiveDate" ); 
   const I_CHAR * const RED_CODE01     = I_( "01" );
   const I_CHAR * const DEP_CODE17     = I_( "17" );
   const I_CHAR * const TRANSFER_LIKE  = I_( "TR,AFTR" ); 
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId HistNonTrustYear;
   extern CLASS_IMPORT const BFTextFieldId TotTransfINDC;
   extern CLASS_IMPORT const BFDateFieldId TradeDate;
   extern CLASS_IMPORT const BFTextFieldId IsNotionalTaxYearApplicable;
   extern CLASS_IMPORT const BFTextFieldId IsTotTransfINDCApplicable;
   extern CLASS_IMPORT const BFTextFieldId IsInNonTrusteeTxfrPeriod;
   extern CLASS_IMPORT const BFTextFieldId BenefCurrTradeYearFound;
   extern CLASS_IMPORT const BFTextFieldId AnyBenefCurrTradeYear;
   extern CLASS_IMPORT const BFDecimalFieldId QESIPaid;
   extern CLASS_IMPORT const BFTextFieldId GrantAmountNA;
   extern CLASS_IMPORT const BFDecimalFieldId BCTESGGrant;
}

//******************************************************************************
//              Public Methods
//******************************************************************************
RESPTransfersProcess::RESPTransfersProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( NULL )
, m_Caller (NULL_STRING)
, m_TradeListKey (NULL_STRING)
, m_RESPTransListKey (NULL_STRING)
, m_AccountNum (NULL_STRING)
, m_DecimalDigits (NULL_STRING)
, m_HistoryPending (NULL_STRING)
, m_TransType (NULL_STRING)
, m_DepositType (NULL_STRING)
, m_RedCode (NULL_STRING)
, m_AccountTo(NULL_STRING) 
, _pRESPTransferList( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer ( IFASTBP_PROC::TRADE, false, BF::NullContainerId, false, I_("Trade"));
   addContainer ( IFASTBP_PROC::TRANSACTION, false, BF::NullContainerId, false, I_("Transaction"));
   addContainer ( IFASTBP_PROC::PENDING_TRANSACTION, false, BF::NullContainerId, false, I_("PendingTransaction"));
   addContainer ( IFASTBP_PROC::RESP_TRANSACTION, false);
   addContainer ( IFASTBP_PROC::RESP_TRANSFER_LIST, true, BF::NullContainerId, true, I_("RESPTransferList"));

//fields at list level	
   addFieldDetails( ifds::FromPlanNum,		   IFASTBP_PROC::RESP_TRANSFER_LIST, SUBCLASS_PROCESS);
   addFieldDetails( ifds::FromContractId,	   IFASTBP_PROC::RESP_TRANSFER_LIST, SUBCLASS_PROCESS);
   addFieldDetails( ifds::ToPlanNum,		   IFASTBP_PROC::RESP_TRANSFER_LIST, SUBCLASS_PROCESS);
   addFieldDetails( ifds::ToContractId,	   IFASTBP_PROC::RESP_TRANSFER_LIST, SUBCLASS_PROCESS);
   addFieldDetails( ifds::InceptionDate,	   IFASTBP_PROC::RESP_TRANSFER_LIST, SUBCLASS_PROCESS);
   addFieldDetails( ifds::TerminationDate,	IFASTBP_PROC::RESP_TRANSFER_LIST, SUBCLASS_PROCESS);
   addFieldDetails( ifds::NEQ1,			      IFASTBP_PROC::RESP_TRANSFER_LIST, SUBCLASS_PROCESS);
   addFieldDetails( ifds::NEQ2,			      IFASTBP_PROC::RESP_TRANSFER_LIST, SUBCLASS_PROCESS);
   addFieldDetails( ifds::RESPLetter,		   IFASTBP_PROC::RESP_TRANSFER_LIST, SUBCLASS_PROCESS);
   addFieldDetails( ifds::RESPTransStat,	   IFASTBP_PROC::RESP_TRANSFER_LIST, SUBCLASS_PROCESS);

   addFieldDetails( ifds::RecordLevel,			IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::YTDContr,			   IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::TDContr,				IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::GrantAmount,			IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::AdditionalGrant,	IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::CLBAmount,			IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::PGrantAmount,		IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::TDRedContrib,		IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::TDRedEarning,		IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::RedCESG,				IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::RedCLB,				IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::RedPGrant,			IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::UCAmt,					IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::ACAmt,					IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::Pre98ContribAmt,	IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::Pre98RedContribAmt,IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::RESPBenefIDFrom,	IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::RESPTrfAllocEntityTypeFrom, IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::RESPTrfEntityTypeSeqFrom,   IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::RESPBenefIDTo,				   IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::RESPTrfAllocEntityTypeTo,   IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::RESPTrfEntityTypeSeqTo,     IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::RESPAllocPrcnt,				   IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::Tainted,						   IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::TaintEndDate,				   IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::GrantRequest,				   IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::BenefDofB,					   IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::TaxJuris,					      IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::Relation,					      IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::BenefEffectiveDate,         IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::TransferPercent,            IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::AcctLvlOverride,            IFASTBP_PROC::RESP_TRANSFER_LIST, SUBCLASS_PROCESS);
   addFieldDetails( ifds::EligibleTransfer,           IFASTBP_PROC::RESP_TRANSFER_LIST);
   //P0185010.FN02.R01.02 - CESG Grant paid for view 407 406 115
   addFieldDetails( ifds::CESGPaid,                   IFASTBP_PROC::RESP_TRANSFER_LIST);
   
//qesi fields
   addFieldDetails( ifds::QESIUCAmount,         IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::QESIACAmount,         IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::QESIYTDContribution,  IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::QESIBasicGrant,       IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::QESIIncreaseAmt,      IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::Pre98QESIContrib,     IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::Pre2007QESIContrib,   IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::QESIPaid           ,  IFASTBP_PROC::RESP_TRANSFER_LIST);

   addFieldDetails( ifds::RESPExtTrDetlUUID,    IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::RESPExtTrDetlVer,     IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::RESPContrDetlUUID,    IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::RESPContrDetlVer,     IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::IsResidualCESG,       IFASTBP_PROC::RESP_TRANSFER_LIST);

   addFieldDetails (IsAcctLevelOverrideApplicable, IFASTBP_PROC::RESP_TRANSFER_LIST, SUBCLASS_PROCESS);
   addFieldDetails (ReadBeneDefaults, IFASTBP_PROC::RESP_TRANSFER_LIST, SUBCLASS_PROCESS);
   addFieldDetails (IsInternalTransfer, IFASTBP_PROC::RESP_TRANSFER_LIST, SUBCLASS_PROCESS);
   addFieldDetails (IsAnyRESPBenefQCResident, IFASTBP_PROC::RESP_TRANSFER_LIST, SUBCLASS_PROCESS);

   addFieldDetails (ifds::HistNonTrustYear, IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::TotTransfINDC,	   IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::TradeDate,    IFASTBP_PROC::RESP_TRANSFER_LIST, SUBCLASS_PROCESS);

   addFieldDetails( ifds::IsNotionalTaxYearApplicable,   IFASTBP_PROC::RESP_TRANSFER_LIST );
   addFieldDetails( ifds::IsTotTransfINDCApplicable,   IFASTBP_PROC::RESP_TRANSFER_LIST );
   addFieldDetails( ifds::IsInNonTrusteeTxfrPeriod,   IFASTBP_PROC::RESP_TRANSFER_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::BenefCurrTradeYearFound,	   IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::AnyBenefCurrTradeYear,    IFASTBP_PROC::RESP_TRANSFER_LIST, SUBCLASS_PROCESS);

   // SAGES
   addFieldDetails( ifds::SAGESGrant,		IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::SAGESUCAmount,	IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::SAGESACAmount,	IFASTBP_PROC::RESP_TRANSFER_LIST);

   addFieldDetails( ifds::GrantAmountNA,  IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::BCTESGGrant,  IFASTBP_PROC::RESP_TRANSFER_LIST);

   addFieldDetails( ifds::UCRedAmt,					IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::ACRedAmt,					IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::SAGESRedUCAmt,			IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::SAGESRedACAmt,			IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::QESIRedUCAmt,				IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::QESIRedACAmt,				IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::QESIRedYTDContrib,		IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::Pre2007QESIRedContrib,	IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::RedAdditionalGrant,		IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::RedSAGES,					IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::QESIRedBasic,				IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::QESIRedIncrease,			IFASTBP_PROC::RESP_TRANSFER_LIST);
   addFieldDetails( ifds::RedBCTESG,				IFASTBP_PROC::RESP_TRANSFER_LIST);

//read the caller in ctor to determine the commit parent
   getParameter (CALLER, m_Caller);
}

//******************************************************************************
RESPTransfersProcess::~RESPTransfersProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   _pRESPTransferList = NULL; 
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

//******************************************************************************
SEVERITY RESPTransfersProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );

   getParameter (ACCOUNT_NUM, m_AccountNum);
   getParameter (TRADE_LIST_KEY, m_TradeListKey);
   getParameter (RESP_TRANS_LIST_KEY, m_RESPTransListKey);
   getParameter (DECIMAL_DIGITS, m_DecimalDigits);
   getParameter (HISTORY_PENDING_FIELD, m_HistoryPending);
   getParameter (TRANS_TYPE, m_TransType);
   getParameter (DEPOSIT_TYPE, m_DepositType);
   getParameter (RED_CODE, m_RedCode);
   getParameter (ACCOUNT_TO, m_AccountTo);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool RESPTransfersProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_RESP_TRANSFER);
}

//******************************************************************************
bool RESPTransfersProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{
   // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );

   bool bRtn = false;

   try
   {
      getParameter (CALLER, m_Caller);
      getParameter (ACCOUNT_NUM, m_AccountNum);
      getParameter (TRADE_LIST_KEY, m_TradeListKey);
      getParameter (RESP_TRANS_LIST_KEY, m_RESPTransListKey);
      getParameter (DECIMAL_DIGITS, m_DecimalDigits);
      getParameter (HISTORY_PENDING_FIELD, m_HistoryPending);
      getParameter (TRANS_TYPE, m_TransType);
      getParameter (DEPOSIT_TYPE, m_DepositType);
      getParameter (RED_CODE, m_RedCode);
	  getParameter (ACCOUNT_TO, m_AccountTo); 

      setContainer (IFASTBP_PROC::RESP_TRANSFER_LIST, NULL);

      if (isValidModelessInterface (_rpChildGI))
      {  // Only if child still exists
         bRtn = _rpChildGI->refresh (this, NULL);
      }
      if( isValidModelessInterface( _rpChildGI ) )
      {  // Only if child still exists
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
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(bRtn);
}

//******************************************************************************
void RESPTransfersProcess::doGetField ( const GenericInterface *rpGICaller,
                                        const BFContainerId &idContainer,
                                        const BFFieldId &idField,
                                        const BFDataGroupId &idDataGroup, 
                                        DString &strValueOut,
                                        bool bFormatted) const
{
   if (idContainer == IFASTBP_PROC::RESP_TRANSFER_LIST && 
         ( idField == ifds::FromPlanNum ||
           idField == ifds::FromContractId || 
           idField == ifds::ToPlanNum || 
           idField == ifds::ToContractId || 
           idField == ifds::InceptionDate || 
           idField == ifds::TerminationDate || 
           idField == ifds::NEQ1 || idField == ifds::NEQ2 ||
           idField == ifds::RESPLetter || 
           idField == ifds::RESPTransStat ||
           idField == ifds::AcctLvlOverride ||
           idField == IsAcctLevelOverrideApplicable ||
           idField == IsInternalTransfer || 
           idField == ifds::TradeDate ||
           idField == ifds::IsInNonTrusteeTxfrPeriod ||
           idField == ifds::AnyBenefCurrTradeYear))
   {

      RESPTransferList *pRESPTransferList = 
         dynamic_cast <RESPTransferList *> (const_cast<RESPTransfersProcess*> (this)->getCBOList (IFASTBP_PROC::RESP_TRANSFER_LIST, idDataGroup));

      if (pRESPTransferList)
      {
         if (idField == IsAcctLevelOverrideApplicable)
         {
			DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
			bool bIsRespTransformation = pDSTCWorkSession->isRESPTransformationClient (getDataGroupId());

			if (bIsRespTransformation)
				strValueOut = pRESPTransferList->isManualOverrideApplicable  (idDataGroup) ? I_("Y") : I_("N");
			else
				strValueOut = pRESPTransferList->isAcctLevelOverrideApplicable  (idDataGroup) ? I_("Y") : I_("N");
         }
         else if (idField == IsInternalTransfer)
         {
            strValueOut = pRESPTransferList->isInternalTransfer  (idDataGroup) ? I_("Y") : I_("N");
         }
         else if (idField == ifds::TradeDate)
         {
            pRESPTransferList->getField (ifds::EffectiveDate, strValueOut, idDataGroup, bFormatted);
         }
         else if (idField == ifds::IsInNonTrusteeTxfrPeriod)
         {
            strValueOut = 
               pRESPTransferList->isInHistoricalRESPPeriod(idDataGroup)? I_("Y") : I_("N");
         }
         else if(idField == ifds::AnyBenefCurrTradeYear)
         {           
            strValueOut = pRESPTransferList->setAnyBenefCurrTradeYear(idDataGroup)? I_("Y") : I_("N");
         }
         else
         {
            pRESPTransferList->getField (idField, strValueOut, idDataGroup, bFormatted);
         }
      }
   }
   else if (idContainer == IFASTBP_PROC::RESP_TRANSFER_LIST && 
            idField == IsAnyRESPBenefQCResident)
   {
      MFAccount *pMFAccount (NULL);
      DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      DString dstrAccount(NULL_STRING);

      bool bTransfer = DSTCommonFunctions::codeInList (m_TransType, TRANSFER_LIKE); 

      if(bTransfer && (m_DepositType == DEP_CODE17) && (m_RedCode==RED_CODE01)) 
      {
         dstrAccount = m_AccountTo;
      }
      else
      {
         dstrAccount = m_AccountNum;
      }

      if (pDSTCWorkSession ->getMFAccount (idDataGroup, dstrAccount, pMFAccount) <= WARNING &&
         pMFAccount)
      {
         pMFAccount->getField( ifds::RESPQCResidentFound, strValueOut, idDataGroup, false);
      }
   }
}

//******************************************************************************
SEVERITY RESPTransfersProcess::doSetField ( const GenericInterface *rpGICaller, 
                                            const BFContainerId &idContainer, 
                                            const BFFieldId &idField,
                                            const BFDataGroupId &idDataGroup, 
                                            const DString &strValue, 
                                            bool bFormatted) 
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, CLASSNAME, I_("doSetField"));

   if (idContainer == IFASTBP_PROC::RESP_TRANSFER_LIST)
   {
      RESPTransferList *pRESPTransferList = 
         dynamic_cast <RESPTransferList *> (getCBOList (IFASTBP_PROC::RESP_TRANSFER_LIST, idDataGroup));

      if (pRESPTransferList)
      {
         if ( idField == ifds::FromPlanNum ||
              idField == ifds::FromContractId || 
              idField == ifds::ToPlanNum || 
              idField == ifds::ToContractId || 
              idField == ifds::InceptionDate || 
              idField == ifds::TerminationDate || 
              idField == ifds::NEQ1 || 
              idField == ifds::NEQ2 ||
              idField == ifds::RESPLetter || 
              idField == ifds::RESPTransStat ||
              idField == ifds::AcctLvlOverride)
         {
            pRESPTransferList->setField (idField, strValue, idDataGroup, bFormatted, false);
         }
         else if (idField == ReadBeneDefaults && (strValue == I_("BEN") || strValue == I_("TP")))
         {
            DString respTransferKey = getCurrentListItemKey (this, IFASTBP_PROC::RESP_TRANSFER_LIST);
            
            if (!respTransferKey.empty())
            {
               DString respTransferNewKey,
                  benefIdFrom,
                  benefIdTo,
                  benefIdSeqTo,
                  recordLevel,
                  transferPercent;
               
               RESPTransfer *pRESPTransfer = 
                  dynamic_cast <RESPTransfer *> (getCBOItem (IFASTBP_PROC::RESP_TRANSFER_LIST, idDataGroup));

               getField (this, IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::TransferPercent, transferPercent, false);
               getField (this, IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::RESPBenefIDFrom, benefIdFrom, false);
               getField (this, IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::RESPBenefIDTo, benefIdTo, false);
               getField (this, IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::RESPTrfEntityTypeSeqTo, benefIdSeqTo, false);
               getField (this, IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::RecordLevel, recordLevel, false);
               benefIdFrom.stripLeading ('0');
               benefIdTo.stripLeading ('0');

               if ( pRESPTransfer )
               {
                  BFObjIter iter (*pRESPTransferList, idDataGroup);

                  bool bTransferPercentUpdate = strValue == I_("TP");

                  iter.positionByKey (respTransferKey);
                  if (!iter.end ())
                  {
                     iter.removeObjectFromMap (true);
                  }

                  setContainer (IFASTBP_PROC::RESP_TRANSFER_LIST, NULL);
                  //pass in the bene id to read the defaults for it from view 409
                  bool bAcctTransferPercent = recordLevel == RECORD_LEVEL::ACCOUNT && strValue == I_("TP") ? true : false;

                  if ( pRESPTransferList->readDefaultNotionals (benefIdFrom, 
                                                                benefIdTo, 
                                                                benefIdSeqTo,
                                                                transferPercent, 
                                                                idDataGroup, 
                                                                bAcctTransferPercent,
                                                                bTransferPercentUpdate  ) <= WARNING)
                  {
                     setParameter (I_("ListKey"), respTransferNewKey); 
                     if (_rpChildGI && isValidModelessInterface (_rpChildGI))
                     {
                        _rpChildGI->send (this, I_("RefreshBeneList"));
                     }
                     else //use the caller if the dlg is launched 'modal', _rpChildGI not valid or null
                     {
                        assert (rpGICaller);
                        if (rpGICaller)
                        {
                           const_cast <GenericInterface*>(rpGICaller)->send (this, I_("RefreshBeneList"));
                        }
                     }
                  }
               }
            }
         }
		 else if (idField == ReadBeneDefaults && strValue == I_("RESTORE_NOTIONALS"))
		 {			 			 
			 //restore account and beneficiary level notionals
			 BFObjIter iter (*pRESPTransferList, idDataGroup);			 
			 int iNum = iter.getNumberOfItemsInList();

			 while (iNum > 0)
			 {      				 				 				 
				 DString respTransferKey = getFirstListItemKey (this, IFASTBP_PROC::RESP_TRANSFER_LIST);

				 if (!respTransferKey.empty())
				 {
					 DString benefIdFrom,
							 benefIdTo,
							 benefIdSeqTo,
							 recordLevel,
							 transferPercent,
							 respTransferNewKey;

					 RESPTransfer *pRESPTransfer = 
						 dynamic_cast <RESPTransfer *> (getCBOItem (IFASTBP_PROC::RESP_TRANSFER_LIST, idDataGroup, &respTransferKey));

					 getField (this, IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::TransferPercent, transferPercent, false);
					 getField (this, IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::RESPBenefIDFrom, benefIdFrom, false);
					 getField (this, IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::RESPBenefIDTo, benefIdTo, false);
					 getField (this, IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::RESPTrfEntityTypeSeqTo, benefIdSeqTo, false);
					 getField (this, IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::RecordLevel, recordLevel, false);
					 benefIdFrom.stripLeading ('0');
					 benefIdTo.stripLeading ('0');

					 if ( pRESPTransfer )
					 {								 
						 iter.removeObjectFromMap (true);					
					
						 setContainer (IFASTBP_PROC::RESP_TRANSFER_LIST, NULL);
						 //pass in the bene id to read the defaults for it from view 409
						 bool bAcctLevel = recordLevel == RECORD_LEVEL::ACCOUNT ? true : false;

						 //read the defaults from view 406 (account) & 409 (beneficiary)						
						 if ( pRESPTransferList->restoreNotionals (benefIdFrom, 
																	benefIdTo, 
																	benefIdSeqTo,
																	transferPercent, 
																	idDataGroup, 
																	bAcctLevel,																
																	respTransferNewKey) <= WARNING)
						 {	
							 setParameter (I_("ListKey"), respTransferNewKey); 
						 }							 
					 }
				 }				
				 iNum--;
			 }						

			 if (_rpChildGI && isValidModelessInterface (_rpChildGI))
			 {
				 _rpChildGI->send (this, I_("RestoreNotionals"));
			 }
			 else //use the caller if the dlg is launched 'modal', _rpChildGI not valid or null
			 {
				 assert (rpGICaller);
				 if (rpGICaller)
				 {
					 const_cast <GenericInterface*>(rpGICaller)->send (this, I_("RestoreNotionals"));
				 }
			 }			
		 }
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
const BFProperties *RESPTransfersProcess::doGetFieldAttributes ( const GenericInterface *rpGICaller, 
                                                                 const BFContainerId &idContainer, 
                                                                 const BFFieldId &idField, 
                                                                 const BFDataGroupId &idDataGroup)
{
   const BFProperties *pBFProperties = NULL;

   if (idContainer == IFASTBP_PROC::RESP_TRANSFER_LIST)
   {
      RESPTransferList *pRESPTransferList = 
         dynamic_cast <RESPTransferList *> (getCBOList (IFASTBP_PROC::RESP_TRANSFER_LIST, idDataGroup));
      if (pRESPTransferList)
      {
         //if( idField == ifds::IsNotionalTaxYearApplicable ||
         //    idField == ifds::IsTotTransfINDCApplicable )
         //{
         //   DString respTransferKey = getCurrentListItemKey (this, IFASTBP_PROC::RESP_TRANSFER_LIST);

         //   if (!respTransferKey.empty())
         //   {
         //      RESPTransfer *pRESPTransfer = 
         //         dynamic_cast <RESPTransfer *> (getCBOItem (IFASTBP_PROC::RESP_TRANSFER_LIST, idDataGroup));

         //      pBFProperties = 
         //         pRESPTransfer->getFieldProperties (idField, idDataGroup);

         //   }
         //}
         //else
         //{
         //   pBFProperties = 
         //      pRESPTransferList->getFieldProperties (idField, idDataGroup);
         //}
         
         pBFProperties = 
            pRESPTransferList->getFieldProperties (idField, idDataGroup);
      }
   }

   return pBFProperties;
}

//******************************************************************************
SEVERITY RESPTransfersProcess::doGetErrors ( const GenericInterface *rpGICaller,
                                             const BFContainerId &idContainer,
                                             const BFFieldId &idField,
                                             const BFDataGroupId &idDataGroup,
                                             CONDITIONVECTOR &conditions) const
{  
   SEVERITY sevRtn = NO_CONDITION;

   if (idContainer == IFASTBP_PROC::RESP_TRANSFER_LIST)
   {
      RESPTransferList *pRESPTransferList = 
         dynamic_cast <RESPTransferList *> (const_cast<RESPTransfersProcess*> (this)->getCBOList (IFASTBP_PROC::RESP_TRANSFER_LIST, idDataGroup));

      if (pRESPTransferList)
      {
         if ( idField == ifds::FromPlanNum ||
              idField == ifds::FromContractId || 
              idField == ifds::ToPlanNum || 
              idField == ifds::ToContractId || 
              idField == ifds::InceptionDate || 
              idField == ifds::TerminationDate || 
              idField == ifds::NEQ1 || 
              idField == ifds::NEQ2 ||
              idField == ifds::RESPLetter || 
              idField == ifds::RESPTransStat)
         {
            sevRtn = pRESPTransferList->getErrors ( idField, 
                                                    idDataGroup, 
                                                    conditions);
         }
      }
   }

   return sevRtn;   
}

//******************************************************************************
bool RESPTransfersProcess::doRegisterObserver ( const GenericInterface *rpGICaller,
                                                const BFContainerId &idContainer,
                                                const BFFieldId &idField,
                                                const BFDataGroupId &idDataGroup,
                                                BFObserver &rpObserver) 
{
   bool bRegistered = false;

   if (idContainer == IFASTBP_PROC::RESP_TRANSFER_LIST)
   {
      if ( idField == ifds::FromPlanNum ||
           idField == ifds::FromContractId || 
           idField == ifds::ToPlanNum || 
           idField == ifds::ToContractId || 
           idField == ifds::InceptionDate || 
           idField == ifds::TerminationDate || 
           idField == ifds::NEQ1 || 
           idField == ifds::NEQ2 ||
           idField == ifds::RESPLetter || 
           idField == ifds::RESPTransStat ||
           idField == ifds::AcctLvlOverride)
      {
         RESPTransferList *pRESPTransferList = 
            dynamic_cast <RESPTransferList *> (getCBOList (IFASTBP_PROC::RESP_TRANSFER_LIST, idDataGroup));
         if (pRESPTransferList)
         {
            bRegistered = pRESPTransferList->registerObserver ( idField, 
                                                                idDataGroup, 
                                                                &rpObserver, 
                                                                FIELD_NOTIFICATIONS, 
                                                                E_EVENT_ALL);
         }
      }
   }
   return bRegistered;
}

//******************************************************************************
E_COMMANDRETURN RESPTransfersProcess::doProcess()
{
	MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
	E_COMMANDRETURN rtn = CMD_FAILURE;

	setParameter (ACCOUNT_NUM, m_AccountNum);
	setParameter (CALLER, m_Caller);
	setParameter (DECIMAL_DIGITS, m_DecimalDigits);
	setParameter (HISTORY_PENDING_FIELD, m_HistoryPending);
	setParameter (TRANS_TYPE, m_TransType);
	setParameter (DEPOSIT_TYPE, m_DepositType);
	setParameter (RED_CODE, m_RedCode);
	setParameter (ACCOUNT_TO, m_AccountTo);

	DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
	bool bIsRespTransformation = pDSTCWorkSession->isRESPTransformationClient (getDataGroupId());

	try
	{
		if (bIsRespTransformation)
			rtn = invokeCommand( this, CMD_GUI_RESP_TRANSFORMATION_TRANSFER, getProcessType(), isModal(), &_rpChildGI );
		else
			rtn = invokeCommand( this, CMD_GUI_RESP_TRANSFER, getProcessType(), isModal(), &_rpChildGI );		
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
void *RESPTransfersProcess::getPtrForContainer( const BFContainerId& idContainer,
                                                const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "getPtrForContainer" ) );

   void *ptr = NULL;
   DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   try
   {
      if (IFASTBP_PROC::TRADE == idContainer)
      {
         if (m_Caller == I_("TradeEntry"))
         {
            WorksessionTradesList *pTradesList (NULL);

            if( pDSTCWorkSession->getTradesList (pTradesList, idDataGroup) <= WARNING && 
               pTradesList)
            {
               BFObjIter iter (*pTradesList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

               iter.positionByKey (m_TradeListKey);
               if (!iter.end())
               {
                  ptr = dynamic_cast <Trade*>(iter.getObject());
               }
            }
         }
      }
      else if (IFASTBP_PROC::TRANSACTION == idContainer)
      {
         if (m_Caller == I_("RESPTransactionsDlg") && m_HistoryPending == RESPINFONAMES::HISTORY)
         {
            RESPTransactionsDetails *pRESPTransactionsDetails = 
               dynamic_cast <RESPTransactionsDetails*> (getCBOItem (IFASTBP_PROC::RESP_TRANSACTION, idDataGroup));

            if (pRESPTransactionsDetails)
            {
               TransactionDetails *pTransactionDetails = NULL;

               if ( pRESPTransactionsDetails->getTransactionDetails (pTransactionDetails, idDataGroup) &&
                  pTransactionDetails)
               {
                  ptr = pTransactionDetails;
               }
            }
         }
      }
      else if (IFASTBP_PROC::PENDING_TRANSACTION == idContainer)
      {
         if (m_Caller == I_("RESPTransactionsDlg") && m_HistoryPending == RESPINFONAMES::PENDING)
         {
            RESPTransactionsDetails *pRESPTransactionsDetails = 
               dynamic_cast <RESPTransactionsDetails*> (getCBOItem (IFASTBP_PROC::RESP_TRANSACTION, idDataGroup));

            if (pRESPTransactionsDetails)
            {
               PendingTradeDetails *pPendingTradeDetails = NULL;

               if ( pRESPTransactionsDetails->getPendingTransactionDetails (pPendingTradeDetails, idDataGroup) &&
                  pPendingTradeDetails)
               {
                  ptr = pPendingTradeDetails;
               }
            }
         }
      }
      else if (IFASTBP_PROC::RESP_TRANSACTION == idContainer)
      {
         MFAccount *pMFAccount (NULL);

         if ( pDSTCWorkSession ->getMFAccount (idDataGroup, m_AccountNum, pMFAccount) <= WARNING &&
            pMFAccount)
         {
            RESPTransactionsList *pRESPTransactionsList (NULL);

            if (pMFAccount->getRESPTransactionsList (pRESPTransactionsList, m_HistoryPending, getDataGroupId ()) <= WARNING &&
               pRESPTransactionsList)
            {
               BFObjIter iter ( *pRESPTransactionsList,idDataGroup, 
                  false, BFObjIter::ITERTYPE::NON_DELETED);

               iter.positionByKey (m_RESPTransListKey);

               if (!iter.end ())
               {
                  ptr = dynamic_cast <RESPTransactionsDetails *>(iter.getObject());
               }
            }
         }
      }
      else if (IFASTBP_PROC::RESP_TRANSFER_LIST == idContainer)
      {
         if (m_Caller == I_("TradeEntry"))
         {
            Trade *pTrade = dynamic_cast <Trade*> (getCBOItem (IFASTBP_PROC::TRADE, idDataGroup));

            if (pTrade)
            {
               RESPTransferList *pRESPTransferList = NULL;

               if (pTrade->getRESPTransferList  (pRESPTransferList, idDataGroup) <= WARNING &&
                  pRESPTransferList)
               {
                  ptr = pRESPTransferList;
               }
            }
         }
         else if (m_Caller == I_("RESPTransactionsDlg"))
         {
            RESPTransactionsDetails *pRESPTransactionsDetails = 
               dynamic_cast <RESPTransactionsDetails*> (getCBOItem (IFASTBP_PROC::RESP_TRANSACTION, idDataGroup));

            if (pRESPTransactionsDetails != NULL)
            {
               RESPTransferList *pRESPTransferList = NULL;

               DString tradeType = m_HistoryPending == RESPINFONAMES::HISTORY ? I_("Proc") : I_("Pend");
               if ( pRESPTransactionsDetails->getRESPTransferList  (pRESPTransferList, idDataGroup, tradeType) <= WARNING &&
                  pRESPTransferList)
               {
                  ptr = pRESPTransferList;
               }
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
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
         CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(ptr);
}

//******************************************************************************
SEVERITY RESPTransfersProcess::doValidateAll ( BFAbstractCBO *rpWSD, 
                                               const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTBP_CONDITION, CLASSNAME, DOVALIDATEALL);

   RESPTransferList *pRESPTransferList = 
      dynamic_cast <RESPTransferList *> (getCBOList (IFASTBP_PROC::RESP_TRANSFER_LIST, idDataGroup));

   if (pRESPTransferList)
   {
      pRESPTransferList->validateAll (idDataGroup);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool RESPTransfersProcess::doOk (GenericInterface *rpGICaller)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, I_( "doOk" ) );

   return GETCURRENTHIGHESTSEVERITY () <= WARNING;
}

//******************************************************************************
void RESPTransfersProcess::doPostOk ( GenericInterface *rpGICaller, 
                                      bool bSuccessFlag)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, I_("doPostOk"));
   const BFDataGroupId& idDataGroup = getDataGroupId();

   if (bSuccessFlag)
   {
      if (m_Caller == I_("TradeEntry"))
      {
         RESPTransferList *pRESPTransferList = 
            dynamic_cast <RESPTransferList *> (getCBOList (IFASTBP_PROC::RESP_TRANSFER_LIST, idDataGroup));

         if (pRESPTransferList)
         {
            Trade *pTrade = dynamic_cast <Trade*> (getCBOItem (IFASTBP_PROC::TRADE, idDataGroup));

            if (pTrade)
            {
               struct fields_mapping
               {
                  BFFieldId _transferlist;
                  BFFieldId _trade;
               } 
               a_fields_mapping [] = 
               {
                  {ifds::FromPlanNum,        ifds::FromPlanNum       },
                  {ifds::FromContractId,     ifds::FromContractId    },
                  {ifds::ToPlanNum,          ifds::ToPlanNum         },
                  {ifds::ToContractId,       ifds::ToContractId      },
                  {ifds::InceptionDate,      ifds::InceptionDate     },
                  {ifds::TerminationDate,    ifds::TerminationDate   },
                  {ifds::NEQ1,               ifds::NEQ1              },
                  {ifds::NEQ2,               ifds::NEQ2              },
                  {ifds::RESPTransStat,      ifds::RESPTransStat     },
                  {ifds::RESPLetter,         ifds::RESPLetter        },
                  {ifds::AcctLvlOverride,    ifds::AcctLvlOverride   },
               };

               int num_fields = sizeof (a_fields_mapping) / sizeof (fields_mapping);

               for (int i = 0; i < num_fields; i++)
               {
                  DString str;

                  pRESPTransferList->getField (a_fields_mapping [i]._transferlist, str, idDataGroup, false);
                  pTrade->setField (a_fields_mapping [i]._trade, str, idDataGroup.getParent(), false);
               }
            }
         }
      }
   }
}

//******************************************************************************
bool RESPTransfersProcess::setCommitDataGroupAsHost()
{
   return m_Caller == I_("RESPTransactionsDlg");
}

//*****************************************************************************
SEVERITY RESPTransfersProcess::performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, 
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
            if( idSearch == IFASTBP_PROC::RESP_TRANSFER_LIST )
            {
               RESPTransfersProcess *pThis = 
                  const_cast<RESPTransfersProcess*>(this);

               RESPTransferList *pRESPTransferList = 
                  dynamic_cast<RESPTransferList*>(pThis->getCBOList (IFASTBP_PROC::RESP_TRANSFER_LIST, idDataGroup));

               if( _pRESPTransferList && pRESPTransferList != NULL )
               {
                  _pRESPTransferList = NULL;
                  _pRESPTransferList = pRESPTransferList;
               }
            }
         }
         break;
      case SEARCH_NEXT_BLOCK:
         {
            if( idSearch == IFASTBP_PROC::RESP_TRANSFER_LIST )
            {
               if( _pRESPTransferList )
               {
                  _pRESPTransferList->getMore ();
               }
               else
               {
                  RESPTransfersProcess *pThis = 
                     const_cast<RESPTransfersProcess*>(this);

                  RESPTransferList *pRESPTransferList = 
                     dynamic_cast<RESPTransferList*>(pThis->getCBOList (IFASTBP_PROC::RESP_TRANSFER_LIST, idDataGroup));

                  _pRESPTransferList = pRESPTransferList;
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
bool RESPTransfersProcess::doMoreRecordsExist( GenericInterface *rpGICaller,
                                               const BFContainerId& idSearch )
{
   bool bReturn = false;
   if( idSearch == IFASTBP_PROC::RESP_TRANSFER_LIST )
   {
      if(rpGICaller != NULL)
      {
         if( _pRESPTransferList == NULL )
         {
            const BFDataGroupId& idDataGroup = getDataGroupId ();

            RESPTransfersProcess *pThis = 
               const_cast<RESPTransfersProcess*>(this);

            RESPTransferList *pRESPTransferList = 
               dynamic_cast<RESPTransferList*>(pThis->getCBOList (IFASTBP_PROC::RESP_TRANSFER_LIST, idDataGroup));

            _pRESPTransferList = pRESPTransferList;
         }

         bReturn = _pRESPTransferList->doMoreRecordsExist();
      }
   }

   return bReturn;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log::   Y:/VCS/BF iFAST/ifastbp/RESPTransfersProcess.cpp-arc  $
// 
//    Rev 1.25   Oct 06 2011 10:26:04   panatcha
// P0185010FN01 - Beneficiary Allocations, EAP, LLP Withdrawals
// 
//    Rev 1.24   Aug 22 2011 09:03:54   jankovii
// IN 2632850 - P0184541FN01- AFT in DSK does not work
// 
//    Rev 1.23   Jul 29 2011 07:38:22   panatcha
// fix IN5285248 and IN2591262
// 
//    Rev 1.22   Jul 25 2011 06:58:22   panatcha
// P0184541_FN01_InvescoQESItrans incidents
// 
//    Rev 1.21   Jun 28 2011 09:55:48   panatcha
// P0184541_FN01_InvescoQESItrans
// 
//    Rev 1.20   Nov 10 2010 04:03:58   dchatcha
// PET0165541 FN03 - QESI Phase3 - Removed not necessary pieces of code.
// 
//    Rev 1.19   Oct 29 2010 06:29:28   kitticha
// PET0165541 FN03 - QESI Phase3.
// 
//    Rev 1.18   Sep 22 2010 06:21:04   dchatcha
// Synch up: IN# 2231991 - No warning message when changing the Transfer%
// 
//    Rev 1.17   Sep 15 2010 13:51:44   jankovii
// PET165541 FN03 SOC14 & SOC6
// 
//    Rev 1.16   Sep 09 2010 14:04:38   jankovii
// IN 2222676 - QESI notional tab on Transfer screen.
// 
//    Rev 1.13.1.0   Aug 13 2010 12:11:42   jankovii
// Sync up: IN 2200243 - Invesco Trimark Parent Cycle CY1287 {27 JULY 2010}.
// 
//    Rev 1.13   Jul 21 2010 01:43:58   dchatcha
// PET0165541 FN09 QESI RESP phase2B - SOC04 - Eligible Transfer on RESP Transfer screen, code review, logic will be more simpler.
// 
//    Rev 1.12   Jun 29 2010 03:03:14   dchatcha
// PET0165541 FN09 QESI RESP phase2B - SOC04 - Eligible Transfer on RESP Transfer screen, code review.
// 
//    Rev 1.11   Jun 24 2010 07:31:44   dchatcha
// PET0165541 FN09 QESI RESP phase2B - SOC04 - Eligible Transfer on RESP Transfer screen.
// 
