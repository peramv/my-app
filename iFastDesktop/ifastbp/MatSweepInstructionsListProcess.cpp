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
// ^FILE   : MatSweepInstructionsListProcess.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : MatSweepInstructionsListProcess
//    This class manages the Maturity and Sweep Instructions List information.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************
//ifastbp
#include "stdafx.h"
#include "matsweepinstructionslistprocessincludes.h"
#include "matsweepinstructionslistprocess.hpp"
#include "MFCANInterProcParam.hpp"

#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\trade.hpp>
#include <ifastcbo\MatSweepInstrList.hpp>
#include <ifastcbo\MatSweepInstr.hpp>
#include <ifastcbo\MatSweepInstrDetails.hpp>
#include <ifastcbo\shareholder.hpp>
#include <ifastcbo\address.hpp>
#include <ifastcbo\addresslist.hpp>
#include <ifastcbo\MatSweepInstrDetailsList.hpp>
#include <ifastcbo\worksessiontradeslist.hpp>
#include <ifastcbo\worksessionentitylist.hpp>
#include <ifastcbo\errmsgruleslist.hpp>
#include <ifastcbo\mgmtco.hpp>

#include <ifastdataimpl\dse_dstcglob_vw.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_MATSWP_INSTRUCTIONS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_MATSWP_INSTRUCTIONS;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< MatSweepInstructionsListProcess > processCreator( CMD_BPROC_MATSWP_INSTRUCTIONS);

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME = I_( "MatSweepInstructionsListProcess" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}


//******************************************************************************
//              Public Methods
//******************************************************************************
MatSweepInstructionsListProcess::MatSweepInstructionsListProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand ), 
_rpChildGI( NULL ),
m_strAcctNum (NULL_STRING),
m_strCaller (NULL_STRING),
m_strInstrType (NULL_STRING),
m_strFund (NULL_STRING),
m_strClass (NULL_STRING),
m_strTransNumber (NULL_STRING),
m_strTransId (NULL_STRING),
m_strIntInvestId (NULL_STRING),
m_TradeListKey (NULL_STRING),
m_Reset(NULL_STRING)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   getParent()->getParameter (CALLER, m_strCaller);

   addContainer (IFASTBP_PROC::MFACCOUNT, false, BF::NullContainerId, false, I_("MFAccount"));
   addContainer (IFASTBP_PROC::TRADE, false, BF::NullContainerId, false, I_("Trade"));

   if (m_strCaller == COA || m_strCaller == INV_HISTORY)
   {
      addContainer (IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST, true, IFASTBP_PROC::MFACCOUNT, true, I_("MatSweepInstructionsList"));
   }
   else if (m_strCaller == TRADE)
   {
      addContainer (IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST,	true, IFASTBP_PROC::TRADE, true, I_("MatSweepInstructionsList"));
   }
   addContainer( IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST, true, IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST, true, I_("MatSweepInstructionDetailList"));

   addContainer ( SHAREHOLDER_ADDRESS, false,  IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST, false, I_("ShareholderAddress"));

   //shareholder address
   addFieldDetails (ifds::MatInstrAddrCode,  IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails (ifds::Name,        SHAREHOLDER_ADDRESS, SUBCLASS_PROCESS);
   addFieldDetails (ifds::AddrLine1,   SHAREHOLDER_ADDRESS, SUBCLASS_PROCESS);
   addFieldDetails (ifds::AddrLine2,   SHAREHOLDER_ADDRESS, SUBCLASS_PROCESS);
   addFieldDetails (ifds::AddrLine3,   SHAREHOLDER_ADDRESS, SUBCLASS_PROCESS);
   addFieldDetails (ifds::AddrLine4,   SHAREHOLDER_ADDRESS, SUBCLASS_PROCESS);
   addFieldDetails (ifds::AddrLine5,   SHAREHOLDER_ADDRESS, SUBCLASS_PROCESS);
   addFieldDetails (ifds::PostalCode,  SHAREHOLDER_ADDRESS, SUBCLASS_PROCESS);
   addFieldDetails (ifds::CountryCode, SHAREHOLDER_ADDRESS, SUBCLASS_PROCESS);

   // instructions list
   addFieldDetails( ifds::MatSwpInstructionType,   IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST);
   addFieldDetails( ifds::AccountNum,              IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST);
   addFieldDetails( ifds::Fund,                    IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST);
   addFieldDetails( ifds::Class,                   IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST);
   addFieldDetails( ifds::SplitType,               IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST);
   addFieldDetails( ifds::EffectiveDate,           IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST);
   addFieldDetails( ifds::TransNum,                IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST);
   addFieldDetails( ifds::CashSweepBal,            IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST);
   addFieldDetails( ifds::SelectedAmt,             IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST);
   addFieldDetails( ifds::IntInvestId,             IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST);
   addFieldDetails( ifds::GoodBad,                 IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST);
   addFieldDetails( ifds::MatInstrLevel,           IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST);
   addFieldDetails( ifds::TransId,                 IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST);
   addFieldDetails( ifds::ProcType,                IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST);
   addFieldDetails( IsInstrCopyAllowed,            IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST, SUBCLASS_PROCESS);
   addFieldDetails( ifds::FromFundNumber,          IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST);
   addFieldDetails( ifds::InvHisStatus,            IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST, SUBCLASS_PROCESS);

   // instruction details list
   addFieldDetails( ifds::DistribDetlUUID,   IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::IntInvestId,		   IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::RolloverType,	   IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::AccountTo,		   IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::FundTo,			   IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::ClassTo,			   IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::RemainingFleg,	   IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::Currency,		      IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::Percentage,		   IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::PayType,			   IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::PayTypeDesc,		   IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::CommReduction,	   IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::IntInvestType,	   IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::FELAmt,			   IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::IntInvestTerm,	   IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::IntCalcMthd,		   IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::ForcedRate,		   IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::ForcedRateAmt,	   IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::IntCredFreq,		   IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::BusinessType,	   IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::RefNum,			   IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::AddlAmt,			   IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::Amount,			   IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);

   // bank fields:
   addFieldDetails( ifds::BankAcctId,        IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::BankAcctUse,			IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::BankIdType,			IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::BankIdValue,			IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::BankTransitNo,		IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::BankSwiftCode,		IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::BankRefNumber,		IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::InstName,			   IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::BankAddr1,			IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::BankAddr2,			IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::BankAddr3,			IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::BankAddr4,			IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::BankAddr5,			IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::BankPostal,			IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::BankCountry,			IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::BankAcctType,		IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::BankAcctTypeDesc,	IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::BankAcctCurrency,	IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::BankAcctCurrDesc,	IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::BankEffectiveDate,	IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::BankStopDate,		IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::PayMethod,			IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::ACHProcessor,		IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::BankContact,			IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::BankCorrespondent,	IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::Address,				IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::BankId1,				IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::BankAcctNum,			IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::BankAcctName,		IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::IntInvestUUID,        IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::DistribDetlVersion,   IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::BankAcctVersion,      IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::IntInvestVer,         IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   addFieldDetails( ifds::FromFundNumber,       IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
}

//******************************************************************************
MatSweepInstructionsListProcess::~MatSweepInstructionsListProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
//              Protected Methods
//******************************************************************************
SEVERITY MatSweepInstructionsListProcess::readParameters()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("readParameters"));

   getParent()->getParameter (ACCOUNT_NUM, m_strAcctNum);
   getParent()->getParameter (INSTR_TYPE, m_strInstrType);
   getParent()->getParameter (FUND, m_strFund);
   getParent()->getParameter (CLASS, m_strClass);
   getParent()->getParameter (TRANS_NUM, m_strTransNumber);
   getParent()->getParameter (TRANS_ID_VALUE, m_strTransId);
   getParent()->getParameter (INVEST_ID, m_strIntInvestId);
   getParent()->getParameter (INV_PRINCIPAL, m_strPrincipalAmount);
   getParent()->getParameter (INV_ACCRUED, m_strAccuredAmount);

   getParent()->getParameter (CALC_METHOD, m_strCalcMethod);
   getParent()->getParameter (INV_TYPE, m_strInvType);
   getParent()->getParameter (TERM, m_strTerm);
   getParent()->getParameter (FREQEUNCY, m_strFrequency);
   getParent()->getParameter (INV_STATUS, m_strInvStatus);

   getParent()->getParameter (TRADE_LIST_KEY, m_TradeListKey);
   getParent()->getParameter (MFCAN_IP_PARAM::RESET, m_Reset);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MatSweepInstructionsListProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );

   readParameters();

   MFAccount *pMFAccount= dynamic_cast <MFAccount*>(getCBOItem (IFASTBP_PROC::MFACCOUNT, BF::HOST));

   if(pMFAccount != NULL) // erase all of existing ones
      pMFAccount->removeMatSweepInstrList();

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool MatSweepInstructionsListProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_MATSWP_INSTRUCTIONS);
}

//******************************************************************************
bool MatSweepInstructionsListProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );
   bool bRtn = false;

   readParameters();

   if(m_Reset == I_("Y"))
   {
      MFAccount *pMFAccount= dynamic_cast <MFAccount*>(getCBOItem (IFASTBP_PROC::MFACCOUNT, BF::HOST));
      if(pMFAccount != NULL) // reset by reloading
         pMFAccount->removeMatSweepInstrList();
      m_Reset = NULL_STRING;
   }
   try
   {
      setContainer (IFASTBP_PROC::MFACCOUNT, NULL);
      setContainer (IFASTBP_PROC::TRADE, NULL);
      setContainer (IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST, NULL);
      setContainer (IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST, NULL);
      setContainer (SHAREHOLDER_ADDRESS, NULL);

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
bool MatSweepInstructionsListProcess::doOk (GenericInterface* rpGICaller)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, DOOK);

   BFDataGroupId idDataGroup = getDataGroupId();
   MFAccount *pMFAccount = NULL;
   DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   if (pDSTCWorkSession->getMFAccount (idDataGroup, m_strAcctNum, pMFAccount) &&
      pMFAccount && m_strCaller == COA)
   {
      pMFAccount->refreshMe (true); //refresh mfaccount
   }

   return true;
}

//******************************************************************************
E_COMMANDRETURN MatSweepInstructionsListProcess::doProcess()
{
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter (CALLER, m_strCaller);   
      setParameter (ACCOUNT_NUM, m_strAcctNum);  
      setParameter (INSTR_TYPE, m_strInstrType );
      setParameter (TRADE_LIST_KEY, m_TradeListKey);

      
      rtn = invokeCommand( this, CMD_GUI_MATSWP_INSTRUCTIONS, getProcessType(), isModal(), &_rpChildGI );
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
void *MatSweepInstructionsListProcess::getPtrForContainer( const BFContainerId& idContainer,
                                                           const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "getPtrForContainer" ) );

   void *ptr = NULL;
   DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   MFAccount *pMFAccount = NULL;

   try
   {
      if (IFASTBP_PROC::MFACCOUNT == idContainer)
      {
         if (pDSTCWorkSession->getMFAccount (idDataGroup, m_strAcctNum, pMFAccount) <= WARNING && 
            pMFAccount)
         {
            ptr = pMFAccount;
         }
      }
      else if (idContainer == SHAREHOLDER_ADDRESS)
      {
         MatSweepInstrDetails *pMatSweepInstrDetails = 
            dynamic_cast <MatSweepInstrDetails *>(getCBOItem (IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST, idDataGroup));

         if (pMatSweepInstrDetails)
         {
            DString dstrAddrCode;
            DString dstrEffectiveDate; 
            DString dstrShrNum;
            pMatSweepInstrDetails->getField (ifds::MatInstrAddrCode, dstrAddrCode, idDataGroup, false);;

            if (pDSTCWorkSession->getMFAccount (idDataGroup, m_strAcctNum, pMFAccount) <= WARNING &&
               pMFAccount)
            {
               pMFAccount->getField (ifds::ShrNum, dstrShrNum, idDataGroup, false);

               if (!dstrShrNum.empty())
               {
                  Shareholder *pShareholder = NULL;

                  if (pDSTCWorkSession->getShareholder (idDataGroup, dstrShrNum, pShareholder) <= WARNING)
                  {
                     if (!dstrAddrCode.empty())
                     {
                        AddressList *pAddressList = NULL;

                        if (pShareholder->getAddressList (pAddressList, idDataGroup) <= WARNING && pAddressList)
                        {
                           Address *pAddress = NULL;
                           MatSweepInstr *pMatSweepInstr = 
                              dynamic_cast <MatSweepInstr *>(getCBOItem (IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST, idDataGroup));

                           if (pMatSweepInstr)
                           {
                              pMatSweepInstr->getField (ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false);
                           }

                           pAddressList->setField (ifds::AccountNum, m_strAcctNum, idDataGroup, false);
                           pAddressList->getAddress (pAddress, dstrAddrCode, dstrEffectiveDate, idDataGroup);

                           if (pAddress)
                           {
                              ptr = pAddress;
                           }
                        }
                     }
                  }
               }
            }
         }
      }
      else if (IFASTBP_PROC::TRADE == idContainer)
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
      else if (IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST == idContainer)
      {
         MatSweepInstrList *pMatSweepInstrList = NULL;

         if (m_strCaller == COA || m_strCaller == INV_HISTORY)
         {
            DString dstrLevel = m_strCaller == COA ? I_("Acct") : I_("Proc");

            MFAccount *pMFAccount = dynamic_cast <MFAccount*> (getCBOItem (IFASTBP_PROC::MFACCOUNT, idDataGroup));

            if ( pMFAccount && 
                 pMFAccount->getMatSweepInstrList (pMatSweepInstrList,
                                                   m_strInstrType,
                                                   dstrLevel,
                                                   m_strFund,
                                                   m_strClass,
                                                   m_strTransNumber,
                                                   m_strTransId,
                                                   m_strIntInvestId,
                                                   m_strPrincipalAmount,
                                                   m_strAccuredAmount,
                                                   idDataGroup) <= WARNING && 
                 pMatSweepInstrList)
            {
               if (m_strCaller == INV_HISTORY)
               {
                  pMatSweepInstrList->setField (ifds::IntInvestType, m_strInvType, idDataGroup, false);
                  pMatSweepInstrList->setField (ifds::IntCalcMthd, m_strCalcMethod, idDataGroup, false);
                  pMatSweepInstrList->setField (ifds::InvestTerm, m_strTerm, idDataGroup, false);
                  pMatSweepInstrList->setField (ifds::IntCredFreq, m_strFrequency, idDataGroup, false);

                  /* Looping to set the status, investment status should apply all mat/instr records */
                  BFObjIter bfIter(*pMatSweepInstrList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
                  MatSweepInstr *pMatSweepInstr = NULL;
                  while( !bfIter.end() )
                  {
                     pMatSweepInstr = dynamic_cast < MatSweepInstr* > ( bfIter.getObject() );
                     assert( pMatSweepInstr );
                     pMatSweepInstr->setField (ifds::InvHisStatus, m_strInvStatus, idDataGroup, false);
                     pMatSweepInstr->setFieldUpdated(ifds::InvHisStatus, idDataGroup, false);

                     ++bfIter;
                  }
               }

               ptr = pMatSweepInstrList;
            }
         }
         else if (m_strCaller == TRADE)
         {
            Trade *pTrade = dynamic_cast <Trade*> (getCBOItem (IFASTBP_PROC::TRADE, idDataGroup));

            if ( pTrade &&
                 pTrade->getMaturityInstrList (pMatSweepInstrList, idDataGroup) <= WARNING && 
                 pMatSweepInstrList)
            {
               ptr = pMatSweepInstrList;
            }
         }
      }
      else if (IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST == idContainer)
      {
         MatSweepInstr *pMatSweepInstr = 
            dynamic_cast <MatSweepInstr *>(getCBOItem (IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST, idDataGroup));

         if (pMatSweepInstr)
         {
            MatSweepInstrDetailsList *pMatSweepInstrDetailsList = NULL;

            if ( pMatSweepInstr->getMatSweepDetailsList (pMatSweepInstrDetailsList, idDataGroup) <= WARNING &&
                 pMatSweepInstrDetailsList)
            {
               if (m_strCaller == INV_HISTORY)
               {
                  /* Looping to set the status, investment status should apply all mat/instr records */
                  BFObjIter bfIter(*pMatSweepInstrDetailsList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
                  MatSweepInstrDetails *pMatSweepInstrDetails = NULL;
                  while( !bfIter.end() )
                  {
                     pMatSweepInstrDetails = dynamic_cast < MatSweepInstrDetails* > ( bfIter.getObject() );
                     assert( pMatSweepInstrDetails );
                     pMatSweepInstrDetails->setField (ifds::InvHisStatus, m_strInvStatus, idDataGroup, false);   
                     pMatSweepInstrDetails->setFieldUpdated(ifds::InvHisStatus, idDataGroup, false);

                     ++bfIter;
                  }
               }

               ptr = pMatSweepInstrDetailsList;
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
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return ptr;
}

//******************************************************************************
bool MatSweepInstructionsListProcess::doSend ( GenericInterface *rpGICaller,
                                               const I_CHAR  *szMessage)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, DOSEND);

   DString message (szMessage),
      currentKey;
   const BFDataGroupId &idDataGroup = getDataGroupId ();
   DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   getParameter (LIST_KEY_INV, currentKey);
   if (message == I_("Clone"))
   {
      
      MatSweepInstrList *pMatSweepInstrList = 
            dynamic_cast <MatSweepInstrList*> (getCBOList (IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST, idDataGroup));

      if (pMatSweepInstrList)
      {
         pMatSweepInstrList->clone (currentKey, idDataGroup);
      }
   }
   else if (message == I_("RefreshAddress"))
   {
      setContainer (SHAREHOLDER_ADDRESS, NULL);
   }
   else if (message == I_("SetTransId"))
   {
      MatSweepInstrList *pMatSweepInstrList = 
            dynamic_cast <MatSweepInstrList*> (getCBOList (IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST, idDataGroup));

      if (pMatSweepInstrList)
      {
         pMatSweepInstrList->setTransId (m_strTransId, idDataGroup);
      }
   }

   return GETCURRENTHIGHESTSEVERITY() <= WARNING;
}

//******************************************************************************
void MatSweepInstructionsListProcess::doGetField ( const GenericInterface *rpGICaller,
                                                   const BFContainerId &idContainer,
                                                   const BFFieldId &idField,
                                                   const BFDataGroupId &idDataGroup, 
                                                   DString &strValueOut,
                                                   bool bFormatted) const
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, CLASSNAME, I_("doGetField"));

   BFAbstractCBO *rPtr_ = const_cast<MatSweepInstructionsListProcess*> (this)->getCBOItem (idContainer, idDataGroup);
   DSTCWorkSession* pDSTCWorkSession = dynamic_cast<DSTCWorkSession *> (getBFWorkSession());

   if (idContainer == SHAREHOLDER_ADDRESS)
   {
      if (idField == ifds::Name)
      {
         if (rPtr_)
         {
            DString name_;

            rPtr_->getField (ifds::Name1, name_, idDataGroup, bFormatted);
            strValueOut += name_;
            rPtr_->getField (ifds::Name2, name_, idDataGroup, bFormatted);
            strValueOut += name_.empty() ? name_ : DString (I_("\r\n")) + name_;
            if (strValueOut.empty())
            {
               BFAbstractCBO *rpPtrMFAccount = const_cast<MatSweepInstructionsListProcess*> (this)->
                  getCBOItem (IFASTBP_PROC::MFACCOUNT, idDataGroup);
               if (rpPtrMFAccount)
               {
                  DString accountNum;

                  rpPtrMFAccount->getField (ifds::AccountNum, accountNum, idDataGroup, false);
                  if (!accountNum.empty())
                  {
                     pDSTCWorkSession->
                        getFirstSequenced01AccountholderEntityName (idDataGroup, accountNum, strValueOut);
                  }
               }
            }
         }
      }
      else //for other address fields
      {
         if (rPtr_)
         {
            rPtr_->getField ( idField, strValueOut, idDataGroup,  bFormatted);
         }
      }
   }
   else if (idContainer == IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST)
   {
      if (idField == IsInstrCopyAllowed)
      {
         MatSweepInstr *pMatSweepInstr = dynamic_cast <MatSweepInstr*> (rPtr_);

         if (pMatSweepInstr)
         {
            DString dstrDuplicateInstr;

            pMatSweepInstr->checkDuplicateActiveInstr (dstrDuplicateInstr, idDataGroup);
            strValueOut = dstrDuplicateInstr == I_("Y") ? I_("N") : I_("Y");
         }
      }
      else if (idField == ifds::InvHisStatus)
      {
         // will remove for svn check-in.
         strValueOut = m_strInvStatus;
      }
   }
}

//******************************************************************************
SEVERITY MatSweepInstructionsListProcess::doSetField ( const GenericInterface *rpGICaller, 
                                                       const BFContainerId &idContainer, 
                                                       const BFFieldId &idField,
                                                       const BFDataGroupId &idDataGroup, 
                                                       const DString &strValue, 
                                                       bool bFormatted) 
{  
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, CLASSNAME, I_("doSetField"));

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/MatSweepInstructionsListProcess.cpp-arc  $
// 
//    Rev 1.27   Aug 20 2012 19:44:48   kitticha
// IN#2932057 - User should not be able to maintain the instruction when investment is matured.
// 
//    Rev 1.26   Jul 17 2012 15:10:10   kitticha
// IN#2932057 - User should not be able to maintain the instruction when investment is matured.
// 
//    Rev 1.25   May 14 2012 18:28:08   wp040100
// IN 2886441 - Included BayCom/Fund Number 
// 1. Cash Sweep Screen.
// 2. Maturity Interest Instructions Screen.
// 3. GI investment Histroy Screen.
// 
//    Rev 1.24   Apr 11 2012 12:48:52   wp040100
// IN 2886441 - BayCom number display implementation.
// 
//    Rev 1.23   Apr 05 2012 14:11:14   jankovii
// IN 2904085 - Automatin Instructions - For reinvestment, the destination fileds s/s pre-popula
// 
//    Rev 1.22   Apr 04 2012 03:59:02   popescu
// Incident 2889047 - fixed address display issue
// 
//    Rev 1.21   Mar 28 2012 15:23:10   jankovii
// IN 2889383 - P0186477_FN05_Maturity Processing Dsktp issues_LIST 1_Seg_intrnl errr_min issues
// 
//    Rev 1.20   Mar 07 2012 14:17:26   jankovii
// IN 2873354 - P0186477FN03- Deleting Instruction on Processed Investments
// 
//    Rev 1.19   Mar 05 2012 11:19:56   jankovii
// IN 2859411 - P0186477_FN02_Interest Instruction-Err displayed on split type 'Amount' instrctn
// 
//    Rev 1.18   Feb 22 2012 15:27:36   jankovii
// Fixed refresh issue on account details screen.
// 
//    Rev 1.17   Feb 22 2012 09:18:10   if991250
// cleaning the Maturity Instructions list from MFAccount
// 
//    Rev 1.16   Feb 16 2012 17:06:18   if991250
// Trade MatSweep Bank
// 
//    Rev 1.15   Feb 09 2012 13:06:28   jankovii
// IN 2835682 - P0186477FN03 -Database error when accessing Maturity/ Interest Screen
// 
//    Rev 1.14   Feb 03 2012 10:41:08   jankovii
// IN 2813743 - P0186477FN03- Can't Access Maturity Instructions thru Investment Hist
// 
//    Rev 1.13   Jan 31 2012 18:59:34   jankovii
// IN 2826242- Maturity/Interest Instruction on Trading Screen
// 
//    Rev 1.12   Jan 26 2012 19:22:30   jankovii
// IN 2817696 - P0186477FN03-Cash Sweep Configuration Issues
// 
//    Rev 1.11   Jan 20 2012 09:35:48   jankovii
// IN 2813487 - P0186477FN03 - Cash Sweep DSK Issues
// 
//    Rev 1.10   Jan 10 2012 15:46:00   jankovii
// P0186477 FN03- GIA Maturity/Cash Sweep Instructions
// 
//    Rev 1.9   Jan 06 2012 12:15:06   jankovii
// P0186477 FN03- GIA Maturity/Cash Sweep Instructions
// 
//    Rev 1.8   Dec 20 2011 17:39:10   popescu
// P0186477 FN03- GIA Maturity/Cash Sweep Instructions
// 
//    Rev 1.7   Dec 19 2011 20:27:38   jankovii
// P0186477 FN03- GIA Maturity/Cash Sweep Instructions
// 
//    Rev 1.6   Dec 19 2011 13:44:54   popescu
// P0186477 FN03- GIA Maturity/Cash Sweep Instructions
// 
//    Rev 1.5   Dec 16 2011 15:49:54   popescu
// P0186477 FN03- GIA Maturity/Cash Sweep Instructions
 * 
 * 
*/
//******************************************************************************

