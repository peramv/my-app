//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2011 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : AccountCommitmentProcess.cpp
// ^CLASS  : AccountCommitmentProcess
//
//******************************************************************************

#include "stdafx.h"
#include "accountcommitmentprocess.hpp"
#include "accountcommitmentprocessincludes.h"

#include <ifastcbo\accountcommitment.hpp>
#include <ifastcbo\accountcommitmentdetails.hpp>
#include <ifastcbo\accountcommitmentdetailslist.hpp>
#include <ifastcbo\accountcommitmentactivity.hpp>
#include <ifastcbo\accountcommitmentactivitylist.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\commitmentproductlist.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\progressiveintratelist.hpp>
#include <ifastcbo\trade.hpp>
#include <ifastcbo\worksessiontradeslist.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_ACCOUNT_COMMITMENT;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ACCOUNT_COMMITMENT;

#include <bfproc\concreteprocesscreator.hpp>

static ConcreteProcessCreator< AccountCommitmentProcess > processCreator( CMD_BPROC_ACCOUNT_COMMITMENT);

namespace 
{
   const I_CHAR *CLASSNAME = I_("AccountCommitmentProcess");
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace TRADE_VALIDATION_GROUP
{
   extern CLASS_IMPORT const long GIA_ATTRIB;
}

namespace ifds
{
   extern CLASS_IMPORT const BFDecimalFieldId ProgressiveIntRate;
   extern CLASS_IMPORT const BFNumericFieldId ProgressiveInvTerm;
   extern CLASS_IMPORT const BFDateFieldId GIMaturityDate;
   extern CLASS_IMPORT const BFDateFieldId InvestDate;
   extern CLASS_IMPORT const BFDateFieldId MaturDate;
   extern CLASS_IMPORT const BFDecimalFieldId InterestRate;
   extern CLASS_IMPORT const BFDecimalFieldId Principal;
   extern CLASS_IMPORT const BFDecimalFieldId MktValue;
   extern CLASS_IMPORT const BFDecimalFieldId ValueAtMaturity;
   extern CLASS_IMPORT const BFDecimalFieldId AccruedInterest;

   extern CLASS_IMPORT const BFNumericFieldId Selected;
   extern CLASS_IMPORT const BFDecimalFieldId AdminFee;
   extern CLASS_IMPORT const BFTextFieldId AmountType;
   extern CLASS_IMPORT const BFDecimalFieldId PrincRedeemed;
   extern CLASS_IMPORT const BFDecimalFieldId InvHisMVA;
   extern CLASS_IMPORT const BFDecimalFieldId AmountNet;
   extern CLASS_IMPORT const BFDecimalFieldId PaidPACSAmt;
   extern CLASS_IMPORT const BFDecimalFieldId ExpectedAmt;
   extern CLASS_IMPORT const BFDecimalFieldId BonusPercentage;

   extern CLASS_IMPORT const BFDateFieldId LastProcDate;
   extern CLASS_IMPORT const BFDateFieldId NextProcessDate;
   extern CLASS_IMPORT const BFDateFieldId NextDrawDate;

}

//******************************************************************************
//              Public Methods
//******************************************************************************
AccountCommitmentProcess::AccountCommitmentProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand ) 
, _rpChildGI( NULL )
, m_Caller (NULL_STRING)
, m_TradeListKey (NULL_STRING)
, m_accountNum (NULL_STRING)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer (IFASTBP_PROC::MFACCOUNT, false, BF::NullContainerId, true, I_("MFACCOUNT"));
//   addContainer (IFASTBP_PROC::COMMITMENT_PRODUCT_LIST, true, BF::NullContainerId, false, I_("COMMITMENT_PRODUCT_LIST"));
   addContainer (IFASTBP_PROC::ACCOUNT_COMMITMENT, false, IFASTBP_PROC::MFACCOUNT, true, I_("ACCOUNT_COMMITMENT"));
   addContainer (IFASTBP_PROC::ACCOUNT_COMMITMENT_DETAILS_LIST, true, IFASTBP_PROC::ACCOUNT_COMMITMENT, true, I_("ACCOUNT_COMMITMENT_DETAILS_LIST"));
   addContainer (IFASTBP_PROC::ACCOUNT_COMMITMENT_ACTIVITY_LIST, true, IFASTBP_PROC::ACCOUNT_COMMITMENT_DETAILS_LIST, true, I_("ACCOUNT_COMMITMENT_ACTIVITY_LIST"));
   addFieldDetails( ifds::IsDuringNASU, IFASTBP_PROC::ACCOUNT_COMMITMENT, SUBCLASS_PROCESS );
}

//******************************************************************************
AccountCommitmentProcess::~AccountCommitmentProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   _rpChildGI = NULL;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************
SEVERITY AccountCommitmentProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );

   try
   {    
      getParameter (CALLER, m_Caller);
      getParameter (ACCOUNT_NUM, m_accountNum);
      getParameter (MFCAN_IP_PARAM::LIST_KEY, m_TradeListKey);

      addFieldDetails( ifds::AcctCommitMstrUUID,    IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::CommitmentUUID,        IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::CommitmentCode,        IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::CommitmentDesc,        IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::CommitDeff,            IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::CommitEndDate,         IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::BeneName,              IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::OrigBeneName,          IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::CommitStatus,          IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::CommitStatusDesc,      IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::CommitAmt,             IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::OrigAccountNum,        IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::CommissionPaid,        IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::SurrChrgApplied,       IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::MaxSurrCharges,        IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::CommittedPACS,         IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::PaidPACS,              IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::MissingPACS,           IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::Username,              IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::ProcessDate,           IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::ModUser,               IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::ModDate,               IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::PACID,                 IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::PACDeff,               IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::PACAmt,                IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::PACStopDate,           IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::InstCode,              IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::SwiftCode,             IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::RefNumber,             IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::TransitNo,             IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::BankAcctNum,           IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::BankAcctName,          IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::SourceOfBankAcct,      IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::BankAcctCurrency,      IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::BankAcctType,          IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::BankType,              IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::BankIdNum,             IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::ACHProcessor,          IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::BankId,                IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::CreditInfoLine1,       IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::CreditInfoLine2,       IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::InstName,              IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::BankAddr1,             IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::BankAddr2,             IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::BankAddr3,             IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::BankAddr4,             IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::BankAddr5,             IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::BankContact,           IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::BankCntry,             IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::BankPstl,              IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::PayReason1,            IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::PayReason2,            IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::PayMethod,             IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::PaidPACSAmt,           IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::LastProcDate,          IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::NextProcessDate,       IFASTBP_PROC::ACCOUNT_COMMITMENT);
      addFieldDetails( ifds::NextDrawDate,          IFASTBP_PROC::ACCOUNT_COMMITMENT);

      addFieldDetails( ifds::DetlDeff,              IFASTBP_PROC::ACCOUNT_COMMITMENT_DETAILS_LIST);
      addFieldDetails( ifds::DetlAmt,               IFASTBP_PROC::ACCOUNT_COMMITMENT_DETAILS_LIST);
      addFieldDetails( ifds::DetlStopDate,          IFASTBP_PROC::ACCOUNT_COMMITMENT_DETAILS_LIST);
      addFieldDetails( ifds::DetlCommClawBack,      IFASTBP_PROC::ACCOUNT_COMMITMENT_DETAILS_LIST);
      addFieldDetails( ifds::ExpectedAmt,           IFASTBP_PROC::ACCOUNT_COMMITMENT_DETAILS_LIST);
      addFieldDetails( ifds::BonusPercentage,       IFASTBP_PROC::ACCOUNT_COMMITMENT_DETAILS_LIST);

      addFieldDetails( ifds::ActivityAmt,           IFASTBP_PROC::ACCOUNT_COMMITMENT_ACTIVITY_LIST);
      addFieldDetails( ifds::ActivityDeff,          IFASTBP_PROC::ACCOUNT_COMMITMENT_ACTIVITY_LIST);
      addFieldDetails( ifds::ActivityCommClawBack,  IFASTBP_PROC::ACCOUNT_COMMITMENT_ACTIVITY_LIST);

      addFieldDetails( ifds::RunMode,  IFASTBP_PROC::ACCOUNT_COMMITMENT);

//      CommitmentProductList *pCommitmentProductList = 
//         (CommitmentProductList*)getCBOItem ( IFASTBP_PROC::COMMITMENT_PRODUCT_LIST, BF::HOST);

   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      throw EXCEPTIONFROMFILE( CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool AccountCommitmentProcess::doModelessChildComplete( const Command &cmd )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_ACCOUNT_COMMITMENT);
}

//******************************************************************************
bool AccountCommitmentProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.

   bool bRtn = false;

   if( isValidModelessInterface( _rpChildGI ) )
   {  // Only if child still exists
      bRtn = _rpChildGI->refresh( this, NULL );
      bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
   }

   return(bRtn);
}
//******************************************************************************
E_COMMANDRETURN AccountCommitmentProcess::doProcess()
{  
   MAKEFRAME2( CND::IFASTBP_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter (CALLER, m_Caller);   
      setParameter (ACCOUNT_NUM, m_accountNum);   
      rtn = invokeCommand( this, CMD_GUI_ACCOUNT_COMMITMENT, PROC_NO_TYPE, isModal(), &_rpChildGI );
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

   return( rtn );
}
//******************************************************************************
void *AccountCommitmentProcess::getPtrForContainer( const BFContainerId& idContainer,
                                               const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, I_( "getPtrForContainer" ) );
   
   void *ptr = NULL;
   DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
	MFAccount *pMFAccount = NULL;
   MgmtCo &mgmtCoOut = pDSTCWorkSession->getMgmtCo( );

   try
   {
		if (IFASTBP_PROC::MFACCOUNT == idContainer)
		{			
			if (pDSTCWorkSession->getMFAccount (idDataGroup, m_accountNum, pMFAccount) <= WARNING && 
             pMFAccount)
         {
            ptr = pMFAccount;
         }
		}
   //if (IFASTBP_PROC::COMMITMENT_PRODUCT_LIST == idContainer)
   //{			
   //    CommitmentProductList *pCommitmentProductList;
   //	   if (mgmtCoOut.getCommitmentProductList (pCommitmentProductList) <= WARNING && 
   //       pCommitmentProductList)
   //    {
   //       ptr = pCommitmentProductList;
   //    }
   //}
   //    else 
         if(IFASTBP_PROC::ACCOUNT_COMMITMENT == idContainer)
		{			
			MFAccount *pMFAccount = (MFAccount*)getCBOItem ( IFASTBP_PROC::MFACCOUNT, idDataGroup);
         if(pMFAccount != NULL)
         {
            AccountCommitment* pAccountCommitment = NULL;
            pMFAccount->getAccountCommitment(pAccountCommitment, idDataGroup, true);
            if(pAccountCommitment != NULL)
               ptr = pAccountCommitment;
         }
      }
      else if(IFASTBP_PROC::ACCOUNT_COMMITMENT_DETAILS_LIST == idContainer)
      {
         AccountCommitment* pAccountCommitment = (AccountCommitment*)getCBOItem ( IFASTBP_PROC::ACCOUNT_COMMITMENT, idDataGroup);
         if(pAccountCommitment != NULL)
         {
            AccountCommitmentDetailsList *pAccountCommitmentDetailsList = NULL;
            pAccountCommitment->getCommitmentDetails(pAccountCommitmentDetailsList, idDataGroup);
            if(pAccountCommitmentDetailsList != NULL)
               ptr = pAccountCommitmentDetailsList;
         }
      }
      else if(IFASTBP_PROC::ACCOUNT_COMMITMENT_ACTIVITY_LIST == idContainer)
      {
         AccountCommitmentDetails *pAccountCommitmentDetails = (AccountCommitmentDetails*)getCBOItem ( IFASTBP_PROC::ACCOUNT_COMMITMENT_DETAILS_LIST, idDataGroup);
         if(pAccountCommitmentDetails != NULL)
         {
            AccountCommitmentActivityList *pAccountCommitmentActivityList = NULL;
            pAccountCommitmentDetails->getAccountCommitmentActivityList(pAccountCommitmentActivityList);
            if(pAccountCommitmentActivityList != NULL)
               ptr = pAccountCommitmentActivityList;
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
   return ptr;  
}

//******************************************************************************
bool AccountCommitmentProcess::doOk (GenericInterface *rpGICaller)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, I_( "doOk" ) );

   return GETCURRENTHIGHESTSEVERITY () <= WARNING;
}

//******************************************************************************
bool AccountCommitmentProcess::doSend ( GenericInterface *rpGICaller,
                                        const I_CHAR  *szMessage)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, DOSEND);

   DString message (szMessage);
   const BFDataGroupId &idDataGroup = getDataGroupId ();
   
   return GETCURRENTHIGHESTSEVERITY() <= WARNING;
}

//******************************************************************************
SEVERITY AccountCommitmentProcess::doSetField( const GenericInterface *rpGICaller,
                                          const BFContainerId& idContainer,
                                          const BFFieldId& idField,
                                          const BFDataGroupId& idDataGroup,
                                          const DString& strValue,
                                          bool bFormatted )
{
   if( idField == ifds::IsDuringNASU)
   {
      DString strIsDuringNasu(strValue);
      strIsDuringNasu.strip().upperCase();


      setField(this, IFASTBP_PROC::ACCOUNT_COMMITMENT, ifds::IsDuringNASU, strIsDuringNasu, false);
   }
   return(NO_CONDITION);
}

//******************************************************************************
void AccountCommitmentProcess::doGetField( const GenericInterface *rpGICaller,
                                      const BFContainerId& idContainer,
                                      const BFFieldId& idField,
                                      const BFDataGroupId& idDataGroup,
                                      DString &strValueOut,
                                      bool bFormatted
                                    ) const
{

    if( idField == ifds::IsDuringNASU )
    {
        AccountCommitment *pAccountCommitment = dynamic_cast < AccountCommitment * >( const_cast <AccountCommitmentProcess*> (this)->getCBOItem( IFASTBP_PROC::ACCOUNT_COMMITMENT, idDataGroup ) );
        if( pAccountCommitment && pAccountCommitment->isNew() )
        strValueOut = I_("Y");
        else
        strValueOut = I_("N");
    }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AccountCommitmentProcess.cpp-arc  $
// 
//    Rev 1.10   Jun 27 2012 10:34:44   if991250
// next draw date validation, display last proc date
// 
//    Rev 1.9   Jun 22 2012 13:10:34   if991250
// INA: PAC Draw Date
// 
//    Rev 1.8   Apr 30 2012 15:32:48   popescu
// 2902002 - P0186480FN02 - Diploma DSK Validation
// 
//    Rev 1.7   Mar 23 2012 10:43:48   if991250
// IN  2885402 - PAC-EFT Systematic readonly for active commitments, Added Insured and Policy number
// 
//    Rev 1.6   Mar 08 2012 09:55:52   if991250
// Account Commitment
// 
//    Rev 1.5   Mar 02 2012 12:55:36   if991250
// Account Commitment in NASU
// 
//    Rev 1.4   Feb 27 2012 15:33:08   if991250
// NASU, Commitment Id
// 
//    Rev 1.3   Feb 24 2012 18:39:18   if991250
// Account Commitment
// 
//    Rev 1.2   Feb 22 2012 16:55:44   if991250
// Account Commitment
// 
//    Rev 1.1   Feb 17 2012 10:33:56   if991250
// Account Commitment
// 
//    Rev 1.0   Jan 20 2012 16:20:50   if991250
// Initial revision.
// 
 * 
*/