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
// ^FILE   : COAProcess.cpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 16/04/99
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : COAProcess
//    This class manages the management company and profile selection.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "coaprocess.hpp"
#include "coaprocessincludes.h"
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\coanavig.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastdataimpl\dse_dstcglob_vw.hpp>
#include <ifastcbo\shareholder.hpp>
#include <ifastcbo\MgmtCoOptions.hpp>
#include "nasuprocessincludes.h"
#include "nasuprocess.hpp"
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_COA;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_COA;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< COAProcess > processCreator( CMD_BPROC_COA );
#include <ifastcbo\dstcworksession.hpp>

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME     = I_( "COAProcess" );
   const I_CHAR * const PERFORMSEARCH = I_( "performSearch" );
   const I_CHAR * const YES = I_( "Y" );
   const I_CHAR * const NO = I_( "N" );
}

namespace COALIT
{
   const I_CHAR* const ACCOUNT_NUM          = I_( "AccountNum" );
   const I_CHAR* const CREATING_ACCOUNT     = I_( "CreatingAccount" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern CLASS_IMPORT const long BP_ERR_INVALID_METHOD_CALL;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId COA_Titles_Fld;
   extern CLASS_IMPORT const BFTextFieldId Substitute_Code;
   extern CLASS_IMPORT const BFTextFieldId Yes_NO;
   extern CLASS_IMPORT const BFTextFieldId ChangeView;
   extern CLASS_IMPORT const BFDateFieldId FirstSettleDate;
   extern CLASS_IMPORT const BFTextFieldId ResClient;
   extern CLASS_IMPORT const BFTextFieldId SettlementRuleExist;
   extern CLASS_IMPORT const BFTextFieldId EligExtTrfGainLoss;
   extern CLASS_IMPORT const BFTextFieldId StopReason;
   extern CLASS_IMPORT const BFTextFieldId AdditionalStopReason;

   extern CLASS_IMPORT const BFTextFieldId CompanyId;
   extern CLASS_IMPORT const BFTextFieldId ClientID;
   extern CLASS_IMPORT const BFTextFieldId CompanyName;
   extern CLASS_IMPORT const BFDateFieldId NextMFRProcessDate;
   extern CLASS_IMPORT const BFTextFieldId IARuleSetup;
   extern CLASS_IMPORT const BFTextFieldId IsGWOContractExist;
   extern CLASS_IMPORT const BFTextFieldId NSCCSocialCode;
   extern CLASS_IMPORT const BFTextFieldId OrgType;
   extern CLASS_IMPORT const BFTextFieldId SubOrgType;
   extern CLASS_IMPORT const BFTextFieldId ShrOutputType;
   extern CLASS_IMPORT const BFTextFieldId AcctRegulatoryExist;
   extern CLASS_IMPORT const BFTextFieldId EntRegDetlExist;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const LIF_GAIN_LOSS;
}
//******************************************************************************
//              Public Methods
//******************************************************************************

COAProcess::COAProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( NULL )
{
    TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

    addContainer(  IFASTBP_PROC::COA_MFACCOUNT_CBO,     false, BF::NullContainerId, true );
    addContainer(  IFASTBP_PROC::COA_SHAREHOLDER_CBO,   false, BF::NullContainerId, true );

    addFieldDetails( ifds::AccountNum,   BF::NullContainerId, SUBCLASS_PROCESS );
    addFieldDetails( ifds::ShrNum,       BF::NullContainerId, SUBCLASS_PROCESS );
    addFieldDetails( COAPROC::inNASU,    BF::NullContainerId, SUBCLASS_PROCESS );
    addFieldDetails( COAPROC::AMSOption, BF::NullContainerId, SUBCLASS_PROCESS );

    addFieldDetails( COAPROC::lChange,   BF::NullContainerId, SUBCLASS_PROCESS );
    addFieldDetails( COAPROC::lYes,      BF::NullContainerId, SUBCLASS_PROCESS );
    addFieldDetails( COAPROC::lView,     BF::NullContainerId, SUBCLASS_PROCESS );
    addFieldDetails( COAPROC::lYes_no,   BF::NullContainerId, SUBCLASS_PROCESS );
        
    addSubstituteList(ifds::Yes_NO);
    addSubstituteList(ifds::ChangeView);

    addFieldDetails( ifds::Name1,                  IFASTBP_PROC::COA_SHAREHOLDER_CBO );
    addFieldDetails( ifds::Remarks,                IFASTBP_PROC::COA_SHAREHOLDER_CBO );
    addFieldDetails( ifds::BankingInstr,           IFASTBP_PROC::COA_SHAREHOLDER_CBO );
    addFieldDetails( ifds::FamilyCodeExist,        IFASTBP_PROC::COA_SHAREHOLDER_CBO );
    addFieldDetails( ifds::ShrFndSpAgrExists,      IFASTBP_PROC::COA_SHAREHOLDER_CBO );
    addFieldDetails( ifds::ShrFndBrkExist,         IFASTBP_PROC::COA_SHAREHOLDER_CBO );

    addFieldDetails( ifds::PendingTrade,           IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::Certificates,           IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::StopPurchase,           IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::StopRed,                IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::StopXferOut,            IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::StopXferIn,             IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::SystemTrsfr,            IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::PAC,                    IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::SWP,                    IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::AcctAlloc,              IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::UnsettledTrn,           IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::FeeWaived,              IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::SupEmpConf,             IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::SupConf,                IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::Escrow,                 IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::InTrustFor,             IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::AcctStatus,             IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::Employee,               IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::Unseizable,             IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::BeneficialOwner,        IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::StopFCrebal,            IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::RRIFQualified,          IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::TaxType,                IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::PlanType,               IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::ACBExist,               IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::InterestAccrExist,      IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::DistributionExist,      IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::ChequeExist,            IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::ExistBeneficiary,       IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::ContractExist,          IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::RIFExist,               IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::SavePlanExist,          IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::GSTExempt,              IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::AcctFeesExist,          IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::ApplyPST,               IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::BankChrgs,              IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::ConsolidEFT,            IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::PensionJurisExists,     IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::AcctCommExists,         IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::FirstSettleDate,        IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::AcctAMSExist,           IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::AcctCategoryExist,      IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::DocListExists,          IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::StopAMSRebalancing,     IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::TelFaxAgreement,        IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::SettleLocExist,         IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::ClearingID,             IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::StopReason,             IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::AdditionalStopReason,   IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::Networkcontrolind,      IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::ClearingFirm,           IFASTBP_PROC::COA_MFACCOUNT_CBO   );//, SUBCLASS_PROCESS );
    addFieldDetails( ifds::AgentForFirm,           IFASTBP_PROC::COA_MFACCOUNT_CBO   );//, SUBCLASS_PROCESS );
    addFieldDetails( ifds::TPA,                    IFASTBP_PROC::COA_MFACCOUNT_CBO   );//, SUBCLASS_PROCESS );
    addFieldDetails( ifds::ParticipantID,          IFASTBP_PROC::COA_MFACCOUNT_CBO   );//, SUBCLASS_PROCESS );
    addFieldDetails( ifds::NSCCSocialCode,         IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::FeeModelCode,           IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::MarketMail,             IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::StopRedSettle,          IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::AcctCutOffTimeExists,   IFASTBP_PROC::COA_MFACCOUNT_CBO );
    addFieldDetails( ifds::FundLimitOvrdExist,     IFASTBP_PROC::COA_MFACCOUNT_CBO );
    addFieldDetails( ifds::SiblingOnly,            IFASTBP_PROC::COA_MFACCOUNT_CBO );
    addFieldDetails( ifds::SettlementRuleExist,    IFASTBP_PROC::COA_MFACCOUNT_CBO );
    addFieldDetails( ifds::UnLockDeff,             IFASTBP_PROC::COA_MFACCOUNT_CBO);
    addFieldDetails( ifds::UnLockGrossAmt,         IFASTBP_PROC::COA_MFACCOUNT_CBO/*, SUBCLASS_PROCESS*/);
    addFieldDetails( ifds::AcctIdentifierExist,    IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::RegisteredTransfers,    IFASTBP_PROC::COA_MFACCOUNT_CBO   );

    //to be removed for RLIF&LRSP long term solution
    addFieldDetails( ifds::AcctType,               IFASTBP_PROC::COA_MFACCOUNT_CBO);
    //up to here

    addFieldDetails( ifds::StopNFU,                IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::ExemptPeriod,           IFASTBP_PROC::COA_MFACCOUNT_CBO   );

    addFieldDetails( ifds::NextMFRProcessDate,     IFASTBP_PROC::COA_MFACCOUNT_CBO);
    addFieldDetails( ifds::IsMFRAccount,           IFASTBP_PROC::COA_MFACCOUNT_CBO);

    // Pay fee options 
    addFieldDetails( ifds::MgmtFeePayOption,       IFASTBP_PROC::COA_MFACCOUNT_CBO   );

    // Early redemption and short term transfer fee
    addFieldDetails( ifds::ChargeERFee,            IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    addFieldDetails( ifds::ChargeSTTRFee,          IFASTBP_PROC::COA_MFACCOUNT_CBO   );

    addFieldDetails( ifds::NetworkID,              IFASTBP_PROC::COA_MFACCOUNT_CBO );
    addFieldDetails( ifds::ConsolTypePW,           IFASTBP_PROC::COA_MFACCOUNT_CBO );
    addFieldDetails( ifds::ConsolTypeID,           IFASTBP_PROC::COA_MFACCOUNT_CBO );
    addFieldDetails( ifds::ConsolTypeED,           IFASTBP_PROC::COA_MFACCOUNT_CBO );

    addFieldDetails( COAPROC::RespExists,          IFASTBP_PROC::COA_MFACCOUNT_CBO, SUBCLASS_PROCESS );
    addFieldDetails( ifds::EligExtTrfGainLoss,     IFASTBP_PROC::COA_MFACCOUNT_CBO, SUBCLASS_PROCESS );
    addFieldDetails( ifds::Affluent,               IFASTBP_PROC::COA_MFACCOUNT_CBO);
    addFieldDetails( ifds::HoldDivPymt,            IFASTBP_PROC::COA_MFACCOUNT_CBO);
    addFieldDetails( ifds::IARuleSetup,            IFASTBP_PROC::COA_MFACCOUNT_CBO);
    addFieldDetails( ifds::IsGWOContractExist,     IFASTBP_PROC::COA_MFACCOUNT_CBO);
    addFieldDetails( ifds::AcctGuarGuardExists,    IFASTBP_PROC::COA_MFACCOUNT_CBO);
    addFieldDetails( ifds::GovAmendmentExist,      IFASTBP_PROC::COA_MFACCOUNT_CBO);

    addFieldDetails( ifds::CanHaveCashSweep,       IFASTBP_PROC::COA_MFACCOUNT_CBO);
    addFieldDetails( ifds::CanHaveMatInstr,        IFASTBP_PROC::COA_MFACCOUNT_CBO);
    addFieldDetails( ifds::CashSweepExists,		   IFASTBP_PROC::COA_MFACCOUNT_CBO);
    addFieldDetails( ifds::MatIntExists,           IFASTBP_PROC::COA_MFACCOUNT_CBO);
	 addFieldDetails( ifds::OrgType,				      IFASTBP_PROC::COA_MFACCOUNT_CBO);
	 addFieldDetails( ifds::SubOrgType,             IFASTBP_PROC::COA_MFACCOUNT_CBO);
    addFieldDetails( ifds::NonFinConfirm,          IFASTBP_PROC::COA_MFACCOUNT_CBO);
    addFieldDetails( ifds::SettleCurrency,         IFASTBP_PROC::COA_MFACCOUNT_CBO);
    addFieldDetails( ifds::T5AnniversaryDate,      IFASTBP_PROC::COA_MFACCOUNT_CBO);
    addFieldDetails( ifds::AggregationType,        IFASTBP_PROC::COA_MFACCOUNT_CBO);
    addFieldDetails( ifds::CompanyId,       BF::NullContainerId, SUBCLASS_PROCESS );
    addFieldDetails( ifds::ClientID,        BF::NullContainerId, SUBCLASS_PROCESS );
    addFieldDetails( ifds::CompanyName,     BF::NullContainerId, SUBCLASS_PROCESS );
    //P0186486_FN16_Misc. Enhancements_Stop Adjustment Date
    addFieldDetails( ifds::StopAdjDate,            IFASTBP_PROC::COA_MFACCOUNT_CBO   );
    
    addFieldDetails( COAPROC::AcctOwnershipRecordExist, IFASTBP_PROC::COA_MFACCOUNT_CBO, SUBCLASS_PROCESS );
    addFieldDetails( ifds::AcctFeeModelAssociated,      IFASTBP_PROC::COA_MFACCOUNT_CBO );
    addFieldDetails( ifds::ShrOutputType,          IFASTBP_PROC::COA_MFACCOUNT_CBO );
    addFieldDetails( ifds::AcctRegulatoryExist,    IFASTBP_PROC::COA_MFACCOUNT_CBO );
    addFieldDetails( ifds::EntRegDetlExist,        IFASTBP_PROC::COA_MFACCOUNT_CBO );
    addFieldDetails( COAPROC::MgmtFeePayOptionDefault, IFASTBP_PROC::COA_MFACCOUNT_CBO);

    addFieldDetails( ifds::AccountGroupExist,            IFASTBP_PROC::COA_MFACCOUNT_CBO );
    addFieldDetails( ifds::PrivateWealthAcct,            IFASTBP_PROC::COA_MFACCOUNT_CBO );
    addFieldDetails( ifds::PrivateWealthOptOut,          IFASTBP_PROC::COA_MFACCOUNT_CBO );
    addFieldDetails( ifds::AcctDelState,                 IFASTBP_PROC::COA_MFACCOUNT_CBO );
    addFieldDetails( ifds::InvestorClassification,       IFASTBP_PROC::COA_MFACCOUNT_CBO   );
}

//******************************************************************************

COAProcess::~COAProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   _rpChildGI = NULL;
}
//********************************************************************************
DString COAProcess::getComboValue(const BFFieldId& idField, const DString& strCode) const
{
   DString dstrSubs, dstrReturn(NULL_STRING);
   const BFDataFieldProperties* pProps = BFDataFieldProperties::get( idField );
   pProps->getAllSubstituteValues( dstrSubs, ClientLocaleContext::get() );
   int idx;
   while( ( idx = dstrSubs.find_first_of( I_( "=" ) ) )
          != DString::npos )
   {
      DString code = dstrSubs.substr( 0, idx );
      dstrSubs.erase( 0, idx + 1);   // Skip to description
      if( ( idx = dstrSubs.find_first_of( I_( ";" ) ) )
          == DString::npos )
      {
         break;
      }
      if( strCode == I_("") )
      {
         if( dstrReturn != NULL_STRING )
            dstrReturn +=I_("\n");
         dstrReturn += dstrSubs.substr( 0, idx );
      }
      else
      {
         if( strCode == code )
         {
            dstrReturn = dstrSubs.substr( 0, idx );
            break;
         }
      }
      dstrSubs.erase( 0, idx + 1 );
   }    
   return(dstrReturn);
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

void COAProcess::doGetField(
                           const GenericInterface *rpGICaller,
                           const BFContainerId& idContainer,
                           const BFFieldId& idField,
                           const BFDataGroupId& idDataGroup,
                           DString &strValueOut,
                           bool bFormatted
                           ) const
{
    if( idField == ifds::AccountNum )
        strValueOut = _AccountNum;
    else if( idField == ifds::ShrNum )
        strValueOut = _ShareholderNum;
    else if( idField == COAPROC::inNASU )
        strValueOut = _inNASU;
    else if( idField == COAPROC::lYes_no )
    {
        strValueOut = getComboValue( ifds::Yes_NO );
    }
    else if( idField == COAPROC::lYes )
    {
        strValueOut = getComboValue( ifds::Yes_NO,I_("Y") );    
    }
    else if( idField == COAPROC::lChange )
    {
        strValueOut = getComboValue( ifds::ChangeView,I_("C") );      
    }
    else if( idField == COAPROC::lView )
    {
        strValueOut = getComboValue( ifds::ChangeView,I_("V") );
    }
    else if(idField == COAPROC::AMSOption )
    {
        MFAccount   *pMFAccount = NULL;
        DString     dstrAccountNum;

        SEVERITY sevRtn = dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getMFAccount( getDataGroupId( ), _AccountNum, pMFAccount );
        if( WARNING >= sevRtn )
        {         
            // "Y" if RB and AMS=="Y" or RO only
            strValueOut = (pMFAccount->isAMSAnOption(getDataGroupId( ))) ? I_("Y") : I_("N");
        }
    }
    else if ( idField == ifds::EligExtTrfGainLoss )
    {
       strValueOut = I_("N");
       MFAccount *pMFAccount = NULL;
       DSTCWorkSession *pDSTCWorkSession = dynamic_cast <DSTCWorkSession *> ( getBFWorkSession() );
       if( pDSTCWorkSession->getMFAccount ( getDataGroupId(), _AccountNum, pMFAccount ) <= WARNING &&
           pMFAccount )
       {
          DString dstrEligExtTrfGainLoss;
          pMFAccount->isLIFGainLossEligible( getDataGroupId(), dstrEligExtTrfGainLoss );
          if( dstrEligExtTrfGainLoss.strip() == I_( "Y" ) &&
              hasReadPermission( UAF::LIF_GAIN_LOSS ) )
          {
             strValueOut = I_("Y");
          }
       }
    }
    else if ( idField == COAPROC::RespExists ) {
    //     long lDataGroupId = getMyGroupID ();
        MFAccount *pMFAccount = NULL;
        DSTCWorkSession *pDSTCWorkSession = dynamic_cast <DSTCWorkSession *> ( getBFWorkSession() );
        pDSTCWorkSession->getMFAccount ( idDataGroup, _AccountNum, pMFAccount );
        DString dstrResClient, dstrTaxType;
        pDSTCWorkSession->getOption( ifds::ResClient, dstrResClient, idDataGroup, false );
        pMFAccount->getField ( ifds::TaxType, dstrTaxType, idDataGroup );
        if( dstrResClient == YES && ( dstrTaxType == I_( "9" ) || dstrTaxType == I_( "M" ) ) ) {
            strValueOut = getComboValue( ifds::Yes_NO,YES );
        } else {
            strValueOut = getComboValue( ifds::Yes_NO,NO );
        }
    }
    else if( idField == ifds::EarlyPWFeeElig || idField == ifds::ShortTermTRFeeElig )
    {
        DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
        MgmtCoOptions *pMgmtCoOptions = dstcWorkSession->getMgmtCoOptions();
        if( pMgmtCoOptions )
        {
            pMgmtCoOptions->getField( idField, strValueOut, idDataGroup, true );
        }
        
    }
    else if( ( idField == ifds::CompanyId ) ||
             ( idField == ifds::ClientID )  ||
             ( idField == ifds::CompanyName )
            )
    {
        strValueOut = NULL_STRING;

        DString dstrFieldValue;
        DSTCWorkSession *dstWorkSession =  dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

        if( dstWorkSession != NULL )
        {
            dstWorkSession->getMgmtCo().getField (idField, dstrFieldValue, idDataGroup );
            strValueOut = dstrFieldValue;
        }
    }
    else if ( idField == COAPROC::AcctOwnershipRecordExist )
    {
        MFAccount   *pMFAccount = NULL;

        SEVERITY sevRtn = dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getMFAccount( getDataGroupId( ), _AccountNum, pMFAccount );
        if( WARNING >= sevRtn )
        {         
           strValueOut = (pMFAccount->hasAcctOwnershipAllocationRecord(BF::HOST)) ? I_("Y") : I_("N");
        }
    }
    else if ( idField == COAPROC::MgmtFeePayOptionDefault )
    {
        MFAccount   *pMFAccount = NULL;

        SEVERITY sevRtn = dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getMFAccount( getDataGroupId( ), _AccountNum, pMFAccount );
        if( WARNING >= sevRtn )
        {         
           strValueOut = pMFAccount->getMgmtFeePayOptOvdSetup(BF::HOST);
        }
    }
	
/*
    else if ( idField == ifds::ClearingFirm || idField == ifds::AgentForFirm ||
              idField == ifds::TPA          || idField == ifds::ParticipantID ) 
    {
      //long lDataGroupId = getDataGroupId();
      MFAccount *pMFAccount = NULL;
      DSTCWorkSession *pDSTCWorkSession = dynamic_cast <DSTCWorkSession *> ( getBFWorkSession() );
      pDSTCWorkSession->getMFAccount ( getDataGroupId(), _AccountNum, pMFAccount );
      pMFAccount->getField( idField, strValueOut, getDataGroupId(), true );
    }*/
    /*else if( idField == ifds::UnLockGrossAmt )
    {
       //show a positive number
       BFAbstractCBO *rpPtr = const_cast<COAProcess*> (this)->
                              getCBOItem ( IFASTBP_PROC::COA_MFACCOUNT_CBO, 
                                           idDataGroup);
         if (rpPtr)
         {
			 rpPtr->getField ( idField, strValueOut, idDataGroup, bFormatted);
			 if( !strValueOut.strip().empty() )
			 {
                strValueOut.strip( '-' );
			 }
		 }
   }*/

   else
   {
      assert( 0 );   
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETFIELD,
                      CND::BP_ERR_INVALID_METHOD_CALL );
   }

}

//******************************************************************************

SEVERITY COAProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );

   SEVERITY sevRtn;
   try
   {
      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

      getParameter( COALIT::ACCOUNT_NUM,      _AccountNum );
      getParameter( COALIT::CREATING_ACCOUNT, _inNASU );
      getParameter( I_("LaunchCOA"), _LaunchCOA );

      sevRtn = dstcWorkSession->getMFAccount( getDataGroupId( ), _AccountNum, _pMFAccount, I_("N"), NULL_STRING, true, true );

      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::COA_MFACCOUNT_CBO, _pMFAccount );
         setGlobal( WORK_GLOBAL, ifds::LastActiveAccountNum, _AccountNum );
      }
      else
         return(sevRtn);

      _pMFAccount->getField( ifds::ShrNum, _ShareholderNum, getDataGroupId() );

      sevRtn = dstcWorkSession->getShareholder( getDataGroupId( ), _ShareholderNum, _pShareholder );

      if( WARNING >= sevRtn )
      {
         setContainer( IFASTBP_PROC::COA_SHAREHOLDER_CBO, _pShareholder );
         setGlobal( WORK_GLOBAL, ifds::LastActiveShrNum, _ShareholderNum );
      }
      else
         return(sevRtn);

   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
E_COMMANDRETURN COAProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      rtn = invokeCommand( this, CMD_GUI_COA, getProcessType(), isModal(), &_rpChildGI );
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

bool COAProcess::doRefresh( GenericInterface *rpGICaller, 
                            const I_CHAR *szOriginalCommand )
{
   TRACE_METHOD( CLASSNAME, DOREFRESH );
   return(true);
}

//******************************************************************************

SEVERITY COAProcess::doSetField(
                               const GenericInterface *rpGICaller,
                               const BFContainerId& idContainer,
                               const BFFieldId& idField,
                               const BFDataGroupId& idDataGroup,
                               const DString& strValue,
                               bool  bFormatted
                               )
{
   SEVERITY sevRtn = NO_CONDITION;
   return(sevRtn);
}

//******************************************************************************

SEVERITY COAProcess::performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, 
                                    E_SEARCHACTION eSearchAction )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, PERFORMSEARCH );
   SEVERITY sevRtn = SEVERE_ERROR;
   return(sevRtn); 
}

//******************************************************************************

void COAProcess::cboSetParameter(const DString& elementName, const DString& value )
{
   TRACE_METHOD( CLASSNAME, I_("SetParameter") );
}

//******************************************************************************
SEVERITY COAProcess::reload()
{  

   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("reload") );
   SEVERITY sevRtn;
   getParameter( COALIT::ACCOUNT_NUM, _AccountNum );

   sevRtn = dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getMFAccount( getDataGroupId( ), _AccountNum, _pMFAccount );

   if( WARNING >= sevRtn )
      setContainer( IFASTBP_PROC::COA_MFACCOUNT_CBO, _pMFAccount );
   else
      return(sevRtn);

   _pMFAccount->getField( ifds::ShrNum, _ShareholderNum, getDataGroupId() );

   return(GETCURRENTHIGHESTSEVERITY());

}

//******************************************************************************
bool COAProcess::setCommitDataGroupAsHost()
{
   getParameter( I_("LaunchCOA"), _LaunchCOA );
   if ( _LaunchCOA ==  I_("LaunchFromAcctInfo")  ) 
      return false;
   else
      return(dynamic_cast<NASUProcess*>(getParent())==NULL  );
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/COAProcess.cpp-arc  $
 * 
 * History:
 * 07-Mar-2014 Supareuk Sukjaitham P0221545 FN01 DFT0030180 T54906
 *             - Call getMgmtFeePayOptOvdSetup
 *             - Added a new field MgmtFeePayOptionDefault
 *             - Recheck with the new task T54906
 *
 *    Rev 1.84   Aug 09 2012 14:16:32   dchatcha
 * IN#3051211 - P0179630 FN01 - FATCA - Acct Ownership Allocation option is not refreshed
 * 
 *    Rev 1.83   Jul 24 2012 19:12:56   dchatcha
 * P0179630 FN01 FATCA Project - Acct Ownership Allocation
 * 
 *    Rev 1.82   May 14 2012 10:08:56   kitticha
 * P0186477 FN06 - T5 Processing.
 * 
 *    Rev 1.81   May 14 2012 04:18:38   panatcha
 * P0186486_FN16_Misc. Enhancements_Stop Adjustment Date
 * 
 *    Rev 1.80   Apr 16 2012 17:25:00   if991250
 * CPF Account Setup
 * 
 *    Rev 1.79   Jan 16 2012 14:45:28   wp040027
 * P0188394_Performance Fees - ERISA Functionality
 * 
 *    Rev 1.78   Dec 05 2011 15:00:40   jankovii
 * P0186477 FN03 - Maturity Cash Sweep Instrucitons.
 * 
 *    Rev 1.77   Oct 07 2011 14:24:44   dchatcha
 * P0191592 FN01 - NSCC Social Code
 * 
 *    Rev 1.76   Jan 31 2011 18:18:40   dchatcha
 * P0179308 FN01 - Multi Manager Subscription and Direct Debit Payment.
 * 
 *    Rev 1.75   Oct 29 2010 07:16:58   dchatcha
 * PET0165541 FN03 - QESI Phase3.
 * 
 *    Rev 1.74   Sep 17 2010 07:23:12   kitticha
 * PETP0173756 FN02 Don't Bust the Rules.
 * 
 *    Rev 1.73   Jul 09 2009 14:21:46   dchatcha
 * PET156681 FN14 H36 Investor Authorization.
 * 
 *    Rev 1.72   Apr 24 2009 11:35:58   jankovii
 * PET 157825 FN18 - MF and MFR Day 2.
 * 
 *    Rev 1.71   Apr 07 2009 10:26:22   jankovii
 * PET 157825 FN18 - MF and MFR Day 2.
 * 
 *    Rev 1.70   Dec 24 2008 10:13:24   jankovii
 * PET 142007 FN03 TFSA Phase 2.
 * 
 *    Rev 1.69   Nov 05 2008 14:38:30   jankovii
 * PET 5517 FN71 Unclaimed Property Phase 2.
 * 
 *    Rev 1.68   28 Aug 2008 11:43:02   kovacsro
 * PET142196FN01 Federal LockedIn RRSP - short term solution
 * 
 *    Rev 1.67   Jul 16 2008 10:21:36   jankovii
 * PET 59888 - AML Enhancemement.
 * 
 *    Rev 1.66   Jun 23 2008 14:35:16   jankovii
 * PET 59888 FN01 - AML Enhancement.
 * 
 *    Rev 1.65   05 May 2008 14:52:20   kovacsro
 * PET2255-FN47 New LIF - moved 'Gain/Loss' from RIF screen into COA
 * 
 *    Rev 1.64   Apr 16 2008 18:29:28   daechach
 * PET2385 FN02&07 - 
 * 
 *    Rev 1.63   Mar 11 2008 19:07:32   daechach
 * PET2385FN02&07 - Account Level Settlement Periods and Currency Holiday - Check in for Build.
 * 
 *    Rev 1.62   Dec 06 2007 19:40:52   smithdav
 * PET1200 FN02 - Dividend Processing enhancement.
 * 
 *    Rev 1.61   Sep 07 2007 14:15:10   smithdav
 * IN 978610 - add logic to look t the AcctAMSExist flag on the account ro COA display.
 * 
 *    Rev 1.60   Aug 14 2007 17:45:40   popescu
 * Incident# 962948 - made the afluent flag available in the COA dialog box
 * 
 *    Rev 1.59   Aug 08 2007 18:01:16   kovacsro
 * PET2360 FN29 - RESP
 * 
 *    Rev 1.58   Jan 24 2007 16:46:40   ZHANGCEL
 * PET2306 FN02 -- Add new fileds for Consolidation ID and PW
 * 
 *    Rev 1.57   Oct 30 2006 16:11:52   fengyong
 * PET 2185 FN02 - Add field FundLimitOvrdExist
 * 
 *    Rev 1.56   Aug 31 2006 13:45:14   ZHANGCEL
 * PET 2212 FN 10 -- Added new field ConsolType 
 * 
 *    Rev 1.55   Feb 21 2006 10:32:24   zhengcon
 * PET 2017_FN02--Partnerworld MT515 and Acct Level Default
 * 
 *    Rev 1.54   Jul 06 2005 14:11:10   hernando
 * PET1250 FN01 - Added AcctCutOffTimeExists.
 * 
 *    Rev 1.53   Jul 06 2005 10:56:32   ZHANGCEL
 * PET1141 - FN05 -- NSCC Broker enhancement
 * 
 *    Rev 1.52   Dec 21 2004 17:31:38   aguilaam
 * PTS 10037090 - add Market Mailing under Misc/COA Screen
 * 
 *    Rev 1.51   Nov 11 2004 16:14:24   vadeanum
 * PET1117 FN08 - Shareholder Fund Broker support.
 * 
 *    Rev 1.50   Sep 01 2004 15:56:38   WINNIE
 * PET 1117 FN05 Fee Model Code missing causes crash
 * 
 *    Rev 1.49   Jul 29 2004 14:05:56   YINGBAOL
 * PET1124:Add Stop redemption settlement field
 * 
 *    Rev 1.48   Jul 29 2004 10:04:12   VADEANUM
 * PET1117 FN01 - Shareholder Static Data support.
 * 
 *    Rev 1.47   Apr 05 2004 17:35:52   FENGYONG
 * PET944FN01, release 56.1 NSCC Broker
 * 
 *    Rev 1.46   Nov 27 2003 10:40:10   HERNANDO
 * PET892 FN1 - Added Settlement Location.
 * 
 *    Rev 1.45   Aug 21 2003 09:25:32   linmay
 * added TelFaxAgreement
 * 
 *    Rev 1.44   May 13 2003 16:08:46   HERNANDO
 * PET792.FN04.3 - Added StopAMSRebalancing.
 * 
 *    Rev 1.43   May 02 2003 16:27:14   sanchez
 * don't need instead of ShortTermTRFeeElig amd EarlyPWFeeElig fields here
 * 
 *    Rev 1.42   Apr 15 2003 10:57:12   linmay
 * Sync up with 1.34.2.0
 * 
 *    Rev 1.41   Apr 07 2003 16:18:32   sanchez
 * Add fields details and get field values for EarlyPWFeeElig and ShortTermTRFeeElig
 * 
 *    Rev 1.40   Apr 04 2003 13:21:34   sanchez
 * Added fields ChargeERFee and ChargeSTTRFee
 * 
 *    Rev 1.39   Apr 02 2003 16:40:32   linmay
 * clean for security
 * 
 *    Rev 1.38   Apr 02 2003 11:49:32   sanchez
 * Changed IFASTBP_PROC::COA_PROC_GEN_LIST to BF::NullContainerId.  Original (preconversion) code specified that this constant was 0.
 * 
 *    Rev 1.37   Apr 01 2003 15:13:34   sanchez
 * added fields EarlyPWFeeElig and ShortTermTRFeeElig
 * 
 *    Rev 1.36   Mar 21 2003 17:38:02   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.35   Mar 14 2003 08:37:12   sanchez
 * Added ChargeSTTRFee and ChargeERFee fields
 * 
 *    Rev 1.34   Jan 29 2003 13:41:52   sanchez
 * Add new check for field AMSOption. strValueOut is "Y" if RB and AMS=="Y" or RO only
 * 
 *    Rev 1.33   Jan 25 2003 16:53:18   KOVACSRO
 * Added AccountCategoryExist
 * 
 *    Rev 1.32   Jan 13 2003 17:55:34   sanchez
 * Changes for Shareholer
 * 
 *    Rev 1.31   Jan 08 2003 14:21:10   sanchez
 * Target Asset Mix implementation (Account Level).  Added field details for AMSROCode.
 * 
 *    Rev 1.30   Dec 30 2002 10:24:18   sanchez
 *   - Added MgmtFeePayOptionSet the field details
 * 
 *    Rev 1.29   Nov 26 2002 17:39:30   HERNANDO
 * Added AMSCode.
 * 
 *    Rev 1.28   Nov 22 2002 15:25:00   KOVACSRO
 * Added FirstSettleDate field.
 * 
 *    Rev 1.27   Oct 09 2002 23:53:08   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.26   Oct 09 2002 15:57:24   PURDYECH
 * BFFieldId fixups
 * 
 *    Rev 1.25   Sep 30 2002 11:01:00   PURDYECH
 * BFFieldId no longer has operator long(), so explicit getId() calls are needed in places.
 * 
 *    Rev 1.24   Aug 29 2002 16:44:50   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.23   Aug 29 2002 12:54:16   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.22   Jul 11 2002 16:54:06   HSUCHIN
 * added account level split commission option
 * 
 *    Rev 1.21   Jun 15 2002 12:44:54   HSUCHIN
 * added PensionJurisexists
 * 
 *    Rev 1.20   31 May 2002 12:18:52   KOVACSRO
 * added 2 new fields
 * 
 *    Rev 1.19   22 May 2002 18:24:10   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.18   27 Mar 2002 19:54:46   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.17   Mar 18 2002 14:36:14   YINGBAOL
 * add PSTexempt
 * 
 *    Rev 1.16   Feb 04 2002 15:44:16   JANKAREN
 * Added GSTExempt
 * 
 *    Rev 1.15   05 Jun 2001 16:06:00   YINGZ
 * for others to compile
 * 
 *    Rev 1.14   14 May 2001 13:58:14   YINGZ
 * code sync up
 * 
 *    Rev 1.13   03 May 2001 14:05:20   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.12   Apr 06 2001 19:07:22   YINGZ
 * Mihai fix the century bug
 * 
 *    Rev 1.11   Feb 16 2001 15:28:54   YINGBAOL
 * put some hardcode strings into DD
 * 
 *    Rev 1.10   Jan 05 2001 11:11:56   ZHANGCEL
 * Synchronization to C2/C3: added a new field - RIFExist
 * 
 *    Rev 1.9   15 Dec 2000 12:43:24   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.8   Nov 08 2000 16:51:52   ZHANGCEL
 * Added new field ContractExist
 * 
 *    Rev 1.7   Oct 27 2000 17:37:00   ZHANGCEL
 * Added field ExistBeneficiary
 * 
 *    Rev 1.6   Oct 18 2000 11:32:50   ZHANGCEL
 * Added new fileds
 * 
 *    Rev 1.5   Oct 05 2000 13:41:56   YINGBAOL
 * add Plan type field
 * 
 *    Rev 1.4   Sep 20 2000 14:22:24   ZHANGCEL
 * Debug
 * 
 *    Rev 1.3   Aug 02 2000 15:32:00   BUZILA
 * "locale" changes
 * 
 *    Rev 1.2   Aug 01 2000 12:41:16   PETOLESC
 * Added a few more fields.
 * 
 *    Rev 1.1   Feb 28 2000 15:31:08   PRAGERYA
 * Check-in For Mihai
 * 
 *    Rev 1.0   Feb 15 2000 10:59:32   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.21   Jan 22 2000 15:18:56   BUZILA
 * fixes
 * 
 *    Rev 1.20   Jan 14 2000 18:08:52   POPESCUS
 * set the last active account num
 * 
 *    Rev 1.19   Jan 06 2000 18:04:08   BUZILA
 * took off the call to loadTitleSubstitutions() in doProcess(). because of dataGroup problems
 * 
 *    Rev 1.18   Dec 24 1999 15:37:02   BUZILA
 * we don't need anymore COAlist
 * 
 *    Rev 1.17   Dec 23 1999 14:13:42   BUZILA
 * added Employee field
 * 
 *    Rev 1.16   Dec 22 1999 18:02:10   BUZILA
 * changes due to COA flags movament
 * 
 *    Rev 1.15   Dec 10 1999 18:47:34   BUZILA
 * implemented collapse, search, filtering
 * 
 *    Rev 1.14   Dec 08 1999 12:17:08   BUZILA
 * added idDataGroup parameter to doGetField and doSetField
 * 
 *    Rev 1.13   Nov 30 1999 18:24:46   POPESCUS
 * changes related to the NASU flow
 * 
 *    Rev 1.12   Nov 25 1999 15:12:56   BUZILA
 * fixes
 * 
 *    Rev 1.11   Nov 20 1999 19:39:18   BUZILA
 * fixes
 * 
 *    Rev 1.10   Oct 28 1999 18:05:30   DT24433
 * removed doOk/doCancel
 * 
 *    Rev 1.9   Oct 17 1999 12:12:34   POPESCUS
 * namespace fixes
 * 
 *    Rev 1.8   Aug 31 1999 10:22:40   DT24433
 * changed dogetfield/dosetfield parms
 * 
 *    Rev 1.7   Aug 17 1999 16:37:04   DT24433
 * removed static FieldDetails array
 * 
 *    Rev 1.6   Aug 12 1999 15:40:48   BUZILA
 * ch
 * 
 *    Rev 1.5.1.0   Aug 12 1999 15:26:48   BUZILA
 * Branch for Increment 2
 * 
 *    Rev 1.5   Aug 05 1999 11:52:48   BUZILA
 * 1
 * 
 *    Rev 1.4   Jul 27 1999 16:01:46   BUZILA
 * Increment M2
 * 
 *    Rev 1.3   Jul 26 1999 10:37:38   BUZILA
 * changed doGetField
 * 
 *    Rev 1.2   Jul 20 1999 11:13:58   VASILEAD
 * New conditions update
 * 
 *    Rev 1.1   Jul 08 1999 10:01:56   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */

