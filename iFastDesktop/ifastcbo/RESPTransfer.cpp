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
//    Copyright 2004 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : RESPTransfer.cpp
// ^AUTHOR : 
// ^DATE   : February, 2010
//
// ^CLASS    : RESPTransfer
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "RESPTransfer.hpp"
#include "RESPTransferlist.hpp"
#include "RESPTransferValidation.hpp"
#include "RespTransactionsDetails.hpp"
#include "RespTransactionsList.hpp"
#include "TransactionDetails.hpp"
#include "Entity.hpp"
#include "EntityIdsList.hpp"
#include "mfaccount.hpp"
#include <ifastcbo\errmsgruleslist.hpp>

#include <ifastdataimpl\dse_dstc0004_vw.hpp>
#include <ifastdataimpl\dse_dstc0149_vw.hpp>
#include <ifastdataimpl\dse_dstc0406_req.hpp>
#include <ifastdataimpl\dse_dstc0406_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0406_vw.hpp>
#include <ifastdataimpl\dse_dstc0050_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0409_req.hpp>
#include <ifastdataimpl\dse_dstc0409_vw.hpp>

#include "mgmtco.hpp"

namespace
{
   const I_CHAR * const CLASSNAME         = I_("RESPTransfer");
   const I_CHAR * RESP_BENEFICIARY        = I_( "50" ); 
   const I_CHAR * CALL_TYPE_VALIDATION    = I_( "V" ); 
   const I_CHAR * const BENEF_NAME        = I_("BENNAME");
   const I_CHAR * const PENDPROC          = I_("PENDPROC");
   const I_CHAR * const TRANSNUM          = I_("TRANSNUM");
   const I_CHAR * const NEW               = I_( "New" );
   const I_CHAR * const PENDING           = I_( "Pend" );
   const I_CHAR * const PROCESSED         = I_( "Proc" );
   const I_CHAR * const TRANSFER_LIKE     = I_( "TR,AFTR" );
   const I_CHAR * const SIN               = I_("06");
   const I_CHAR * const DEFAULT_PERCENT   = I_("100");
   const I_CHAR * const ZERO_PERCENT      = I_("0");
   const I_CHAR * const YES               = I_( "Y" );
   const I_CHAR * const NO                = I_( "N" );
   const I_CHAR * const SASKATCHEWAN      = I_("0003");

   const double dSmallValue       = .0000000001;
}

namespace RECORD_LEVEL
{
   extern const I_CHAR *BENEFICIARY; 
   extern const I_CHAR *ACCOUNT; 
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const RESP_TRANSFER;
}

namespace ifds
{   
   extern CLASS_IMPORT const BFTextFieldId RecordType;
   extern CLASS_IMPORT const BFTextFieldId CSSStopSINMatch;
   extern CLASS_IMPORT const BFDecimalFieldId Amount;
   extern CLASS_IMPORT const BFTextFieldId IdType;
   extern CLASS_IMPORT const BFTextFieldId IdValue;
   extern CLASS_IMPORT const BFNumericFieldId HistNonTrustYear;
   extern CLASS_IMPORT const BFTextFieldId TotTransfINDC;
   extern CLASS_IMPORT const BFDateFieldId NonTrustStartDate;
   extern CLASS_IMPORT const BFDateFieldId NonTrustStopDate;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFTextFieldId IsNotionalTaxYearApplicable;
   extern CLASS_IMPORT const BFTextFieldId IsTotTransfINDCApplicable;
   extern CLASS_IMPORT const BFTextFieldId IsNonTrustee;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFTextFieldId IsInNonTrusteeTxfrPeriod;
   extern CLASS_IMPORT const BFTextFieldId RESPTransStat;
   extern CLASS_IMPORT const BFTextFieldId BenefCurrTradeYearFound;
   extern CLASS_IMPORT const BFTextFieldId AnyBenefCurrTradeYear;
   extern CLASS_IMPORT const BFDecimalFieldId QESIPaid;
   extern CLASS_IMPORT const BFTextFieldId AllocAmtType;
   extern CLASS_IMPORT const BFTextFieldId IsResidualCESG;
   extern CLASS_IMPORT const BFTextFieldId GrantAmountNA;
   extern CLASS_IMPORT const BFDecimalFieldId BCTESGGrant;
   extern CLASS_IMPORT const BFTextFieldId Reversal;
}

namespace CND
{  
   extern const long ERR_BENEFICIARY_NOT_EFFECTIVE;
   extern const long ERR_CLB_AMOUNT_CANNOT_BE_TRANSFERED;
   extern const long WARN_CLB_AMOUNT_CANNOT_BE_TRANSFERED;
   extern const long ERR_PERCENT_VALUE_INVALID;
   extern const long ERR_TO_BENEF_IS_MISSING; 
   extern const long ERR_FROM_BENEF_IS_MISSING;
   extern const long ERR_VALUE_BETWEEN_0_AND_100;
   extern const long WARN_ELIGIBLE_TRANSFER_FLAG_CHANGED;
   extern const long WARN_ELIGIBLE_TRANSFER_FILED_IS_NO;
   extern const long ERR_QESI_TOTAL_TRANSFER_FILED_IS_BLANK; 
   extern const long WARN_QESI_TOTAL_TRANSFER_FILED_IS_BLANK;
   extern const long ERR_NON_ASSOCIATED_BENEF_IS_NOT_ALLOWED;
   extern const long WARN_NON_ASSOCIATED_BENEF_IS_NOT_ALLOWED;
   extern const long ERR_BENEF_CURR_TAXYEAR_MANDATORY;
   extern const long ERR_DEL_HIST_TXFR_BENEF_RECORD;
   extern const long ERR_CESG_AMOUNT_MANDATORY ;
   extern const long ERR_UC_AMT_LESS_THAN_RES_AMT;
   extern const long WARN_UC_AMT_LESS_THAN_RES_AMT;
   extern const long ERR_SAGES_ASSISTED_CONTRIBUTION_AMOUNT_IS_ZERO;
   extern const long WARN_SAGES_ASSISTED_CONTRIBUTION_AMOUNT_IS_ZERO;
   extern const long ERR_TRADE_DATE_MUST_BE_EQUAL_OR_GREATER_THAN_SAGESDEFF;
   extern const long WARN_TRADE_DATE_MUST_BE_EQUAL_OR_GREATER_THAN_SAGESDEFF;
   extern const long ERR_NOTIONAL_AMOUNTS_MUST_BE_NEGATIVE;
   extern const long WARN_NOTIONAL_AMOUNTS_MUST_BE_NEGATIVE;    
   extern const long ERR_ACCOUNT_MUST_BE_SIBLING_ONLY_FOR_SAGES;
   extern const long WARN_ACCOUNT_MUST_BE_SIBLING_ONLY_FOR_SAGES;
   extern const long ERR_BENEFICIARY_NOT_SASKATCHEWAN_RESIDENT;
   extern const long WARN_BENEFICIARY_NOT_SASKATCHEWAN_RESIDENT;
   extern const long ERR_NOTIONAL_PAID_BY_OTHER_AMOUNTS_MUST_BE_POSITIVE;
   extern const long WARN_NOTIONAL_PAID_BY_OTHER_AMOUNTS_MUST_BE_POSITIVE;
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const CLB_AMOUNT_CANNOT_BE_TRANSFERED;
   extern CLASS_IMPORT I_CHAR * const QESI_TOTAL_TRANSFER_FILED_IS_BLANK;
   extern CLASS_IMPORT I_CHAR * const NON_ASSOCIATED_BENEF_IS_NOT_ALLOWED;
   extern CLASS_IMPORT I_CHAR * const UC_AMT_LESS_THAN_RES_AMT;
   extern CLASS_IMPORT I_CHAR * const SAGES_ASSISTED_CONTRIBUTION_AMOUNT_IS_ZERO;
   extern CLASS_IMPORT I_CHAR * const TRADE_DATE_MUST_BE_EQUAL_OR_GREATER_THAN_SAGESDEFF;
   extern CLASS_IMPORT I_CHAR * const NOTIONAL_AMOUNTS_MUST_BE_NEGATIVE;     
   extern CLASS_IMPORT I_CHAR * const ACCOUNT_MUST_BE_SIBLING_ONLY_FOR_SAGES;
   extern CLASS_IMPORT I_CHAR * const BENEFICIARY_NOT_SASKATCHEWAN_RESIDENT;
   extern CLASS_IMPORT I_CHAR * const NOTIONAL_PAID_BY_OTHER_AMOUNTS_MUST_BE_POSITIVE;
}
namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest RESP_TRANSFER_BENE_INQUIRY;
}
unsigned int RESPTransfer::si_Counter = 0;

//-------------------------------------------------------------------
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
//    Field DD Id,                     State Flags,      Group Flags
   {ifds::RecordType,                  BFCBO::NONE,         0 },
   {ifds::TransId,                     BFCBO::NONE,         0 },
   {ifds::RecordLevel,                 BFCBO::NONE,         0 },
   {ifds::YTDContr,                    BFCBO::NONE,         0 },
   {ifds::TDContr,                     BFCBO::NONE,         0 },
   {ifds::GrantAmount,                 BFCBO::NONE,         0 },
   {ifds::AdditionalGrant,             BFCBO::NONE,         0 },
   {ifds::CLBAmount,                   BFCBO::NONE,         0 },
   {ifds::PGrantAmount,                BFCBO::NONE,         0 },
   {ifds::TDRedContrib,                BFCBO::NONE,         0 },
   {ifds::TDRedEarning,                BFCBO::NONE,         0 },
   {ifds::RedCESG,                     BFCBO::NONE,         0 },
   {ifds::RedCLB,                      BFCBO::NONE,         0 },
   {ifds::RedPGrant,                   BFCBO::NONE,         0 },
   {ifds::UCAmt,                       BFCBO::NONE,         0 },
   {ifds::ACAmt,                       BFCBO::NONE,         0 },
   {ifds::Pre98ContribAmt,             BFCBO::NONE,         0 },
   {ifds::Pre98RedContribAmt,          BFCBO::NONE,         0 },
   {ifds::RESPBenefIDFrom,             BFCBO::NONE,         0 },
   {ifds::RESPTrfAllocEntityTypeFrom,  BFCBO::NONE,         0 },
   {ifds::RESPTrfEntityTypeSeqFrom,    BFCBO::NONE,         0 },
   {ifds::RESPBenefIDTo,               BFCBO::NONE,         0 },
   {ifds::RESPTrfAllocEntityTypeTo,    BFCBO::NONE,         0 },
   {ifds::RESPTrfEntityTypeSeqTo,      BFCBO::NONE,         0 },
   {ifds::TransferPercent,             BFCBO::NONE,         0 },
   {ifds::QESIUCAmount,                BFCBO::NONE,         0 },
   {ifds::QESIACAmount,                BFCBO::NONE,         0 },
   {ifds::QESIYTDContribution,         BFCBO::NONE,         0 },
   {ifds::QESIBasicGrant,              BFCBO::NONE,         0 },
   {ifds::QESIIncreaseAmt,             BFCBO::NONE,         0 },
   {ifds::Pre98QESIContrib,            BFCBO::NONE,         0 },
   {ifds::RESPAllocPrcnt,              BFCBO::NONE,         0 },
   {ifds::Tainted,                     BFCBO::NONE,         0 },
   {ifds::TaintEndDate,                BFCBO::NONE,         0 },
   {ifds::GrantRequest,                BFCBO::NONE,         0 },
   {ifds::BenefDofB,                   BFCBO::NONE,         0 },
   {ifds::TaxJuris,                    BFCBO::NONE,         0 },
   {ifds::Relation,                    BFCBO::NONE,         0 },
   {ifds::BenefEffectiveDate,          BFCBO::NONE,         0 },
   {ifds::Pre2007QESIContrib,          BFCBO::NONE,         0 },
   {ifds::RESPExtTrDetlUUID,           BFCBO::NONE,         0 },
   {ifds::RESPExtTrDetlVer,            BFCBO::NONE,         0 },
   {ifds::RESPContrDetlUUID,           BFCBO::NONE,         0 },
   {ifds::RESPContrDetlVer,            BFCBO::NONE,         0 },
   {ifds::EligibleTransfer,            BFCBO::NONE,         0 },
   {ifds::HistNonTrustYear,            BFCBO::NONE,         0 },
   {ifds::TotTransfINDC,               BFCBO::NONE,         0 },
   {ifds::IsNotionalTaxYearApplicable, BFCBO::NONE,         0 },
   {ifds::IsTotTransfINDCApplicable,   BFCBO::NONE,         0 },
   {ifds::BenefCurrTradeYearFound,     BFCBO::NONE,         0 },
   {ifds::CESGPaid,                    BFCBO::NONE,         0 },  //P0185010.FN02.R01.02 - CESG Grant paid
   {ifds::QESIPaid,                    BFCBO::NONE,         0 },
   {ifds::IsResidualCESG,              BFCBO::NONE,         0 },
   {ifds::SAGESGrant,				   BFCBO::NONE,         0 },
   {ifds::SAGESUCAmount,			   BFCBO::NONE,         0 },
   {ifds::SAGESACAmount,			   BFCBO::NONE,         0 },
   {ifds::GrantAmountNA,			   BFCBO::NONE,         0 },
   {ifds::BCTESGGrant,				   BFCBO::NONE,         0 },
   {ifds::UCRedAmt,					   BFCBO::NONE,         0 },
   {ifds::ACRedAmt,					   BFCBO::NONE,         0 },
   {ifds::SAGESRedUCAmt,			   BFCBO::NONE,         0 },
   {ifds::SAGESRedACAmt,			   BFCBO::NONE,         0 },
   {ifds::QESIRedUCAmt,				   BFCBO::NONE,         0 },
   {ifds::QESIRedACAmt,				   BFCBO::NONE,         0 },
   {ifds::QESIRedYTDContrib,		   BFCBO::NONE,         0 },
   {ifds::Pre2007QESIRedContrib,	   BFCBO::NONE,         0 },
   {ifds::RedAdditionalGrant,		   BFCBO::NONE,         0 },
   {ifds::RedSAGES,					   BFCBO::NONE,         0 },
   {ifds::QESIRedBasic,				   BFCBO::NONE,         0 },
   {ifds::QESIRedIncrease,			   BFCBO::NONE,         0 },
   {ifds::RedBCTESG,				   BFCBO::NONE,         0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************************
RESPTransfer::RESPTransfer (BFAbstractCBO &parent)
: MFCanBFCbo (parent)
, m_bTransferPrcntApplicable (false)
, m_dstrTradeYear(NULL_STRING)
, m_bIsNonTrustee(false)
, m_bInitNewLoaded (false)
, m_bReset(false)
, m_bFirstLoad(false)
, m_bIsNonTrusteeLoaded(false)
, m_bHistTxfr(false)
, m_bTradeYearApplicable(false)
, m_bNonTrusteeHistTxfr(false)
, m_bInitExisting(false)
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
   
}

//******************************************************************************************
RESPTransfer::~RESPTransfer()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//************************************************************************************
SEVERITY RESPTransfer::initNew ( const BFDataGroupId &idDataGroup, 
                                 bool bSetFieldsReadOnly)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("initNew"));

   setObjectNew();
   setFieldNoValidate (ifds::RecordLevel, RECORD_LEVEL::BENEFICIARY, idDataGroup, false);
   
   
   commonInit (bSetFieldsReadOnly, true, idDataGroup);  
   
   DString defaultTransferPercent = m_bTransferPrcntApplicable ? DEFAULT_PERCENT : ZERO_PERCENT;

   setFieldNoValidate (ifds::TransferPercent, defaultTransferPercent, idDataGroup, false, true);
   setFieldNoValidate (ifds::EligibleTransfer, /*NO*/YES, idDataGroup, false);
   setFieldReadOnly (ifds::EligibleTransfer, idDataGroup, false);
   
   initNonTrusteeTxfrFields(idDataGroup);  

   m_bInitNewLoaded = true;

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************************
SEVERITY RESPTransfer::init (const BFData& data,
                             const BFDataGroupId &idDataGroup,
                             bool bSetFieldsReadOnly /*=false*/,
							 bool bSetNotionals /*=false*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   m_bInitExisting = true;

   attachDataObject (const_cast<BFData&>(data), false);

   /*
	   Normally, we enable the fields for the processed trade but for Residual CESG.
	   All the fields should not be allowed for modification. Therefore, they have to be readonly.
	   This has to be overide the readonly flag on the record level as 
	   the ResidualCESG is the flag at the record level.
   */
   RESPTransferList *pRESPTransferList = dynamic_cast<RESPTransferList*>( getParent( ) );   
   DString dstrTradeType, dstrIsResidualCESG;

   if(pRESPTransferList)
   {
	   pRESPTransferList->getField (ifds::TradeType, dstrTradeType, idDataGroup, false);  
   }
   getField(ifds::IsResidualCESG, dstrIsResidualCESG, idDataGroup, false);

   if ( (dstrTradeType == PROCESSED) && (dstrIsResidualCESG == YES) )
	   bSetFieldsReadOnly = true;

   commonInit (bSetFieldsReadOnly, bSetNotionals, idDataGroup);
   setFieldReadOnly (ifds::RESPBenefIDFrom, idDataGroup, true);

   DString dstrRecordLevel;
   getField (ifds::RecordLevel, dstrRecordLevel, idDataGroup, false);
   if (dstrRecordLevel == RECORD_LEVEL::ACCOUNT)
   {
      setFieldReadOnly (ifds::EligibleTransfer, idDataGroup, true);

      setFieldReadOnly (ifds::TotTransfINDC, idDataGroup, true);

      DString strTotTransfINDC(NULL_STRING);
      getField( ifds::TotTransfINDC, strTotTransfINDC, idDataGroup, false );
      if(strTotTransfINDC == NULL_STRING )
      {
         setFieldNoValidate (ifds::TotTransfINDC, I_(""), idDataGroup, true); 
      }

      //IN2672499 - RESP Transfer Information error message
      DString strHistNonTrustYear(NULL_STRING);
      getField( ifds::HistNonTrustYear, strHistNonTrustYear, idDataGroup, false );
      if (strHistNonTrustYear == I_("0") || strHistNonTrustYear == NULL_STRING ) //Entry Trade
      {
         setFieldNoValidate (ifds::HistNonTrustYear, m_dstrTradeYear, idDataGroup, true, false, true, false); 
      }
   }
   else
   {
      //IN2617122
      // fix in case pass in the bene id to read the defaults for it from view 409
      //--- for case, place new trade -> update BENEF (reload default from gui)
      // pre-set contribution year

      DString dstrHistNonTrustYear(NULL_STRING);
      bool bSetReadOnly;

      if(dstrTradeType == NEW)
      {
         setFieldNoValidate (ifds::HistNonTrustYear, m_dstrTradeYear, idDataGroup, false, false, true, false);
         bSetReadOnly = false;
      } 
      else
      {
         getField (ifds::HistNonTrustYear, dstrHistNonTrustYear, idDataGroup, false);
         dstrHistNonTrustYear.stripAll();
         if (dstrHistNonTrustYear == I_("0") || dstrHistNonTrustYear == NULL_STRING ) //Entry Trade
         {
            setFieldNoValidate (ifds::HistNonTrustYear, m_dstrTradeYear, idDataGroup, true, false, true, false); 
         }
         bSetReadOnly = (m_dstrTradeYear != dstrHistNonTrustYear);
         setFieldReadOnly (ifds::HistNonTrustYear, idDataGroup, true); //IN2640270_WO661530
      }
      setFieldReadOnly (ifds::EligibleTransfer, idDataGroup, bSetReadOnly);
      setFieldReadOnly (ifds::TotTransfINDC, idDataGroup, bSetReadOnly);
   }

   m_bReset = true;
   m_bInitExisting = false;

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void RESPTransfer::doInitWithDefaultValues (const BFDataGroupId& idDataGroup)
{
}

//***********************************************************************************
SEVERITY RESPTransfer::commonInit (bool bSetFieldsReadOnly,
								   bool bSetNotionals,
                                   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("commonInit"));

   DString substList;
   DString recordLevel;

   setFieldNoValidate (ifds::RecordType, I_("RESPTrfAlloc"), idDataGroup, false);

   getField (ifds::RecordLevel, recordLevel, idDataGroup, false);

   RESPTransferList *pRESPTransferList = dynamic_cast<RESPTransferList*>( getParent( ) );

   loadNotionalYearList(idDataGroup);

   if (pRESPTransferList)
   {
      pRESPTransferList->getTradeYear(m_dstrTradeYear, idDataGroup);

      m_bNonTrusteeHistTxfr = pRESPTransferList->isNonTrusteeContrib(idDataGroup); //IN2672499 - RESP Transfer Information error message
      doNEQ1RelatedChanges(idDataGroup); //set isShownQESItot  		
   }

   if (pRESPTransferList && recordLevel== RECORD_LEVEL::BENEFICIARY)
   {
      DString dstrEntityId,
         dstrEntityTypeSeq,
         dstrAccountNum,
         dstrAccountTo;

      setFieldNoValidate (ifds::RESPTrfAllocEntityTypeFrom, RESP_BENEFICIARY, idDataGroup, false);
      setFieldNoValidate (ifds::RESPTrfAllocEntityTypeTo, RESP_BENEFICIARY, idDataGroup, false);

      getField (ifds::RESPBenefIDFrom, dstrEntityId, idDataGroup, false);

      pRESPTransferList->getField (ifds::AccountNum, dstrAccountNum, idDataGroup, false);
      pRESPTransferList->getField (ifds::AccountTo, dstrAccountTo, idDataGroup, false);

      bool bNonRespToResp = pRESPTransferList->isNonRespToResp (idDataGroup);

      if (bNonRespToResp)
      {
         dstrAccountNum = dstrAccountTo;
         dstrAccountTo = I_("");
      }

      pRESPTransferList->getBeneficiaryMasterList (substList, dstrAccountNum, idDataGroup);	
      pRESPTransferList->getEntitySeqNumber (dstrEntityId, dstrAccountNum, idDataGroup, dstrEntityTypeSeq);
      setFieldNoValidate (ifds::RESPTrfEntityTypeSeqFrom, dstrEntityTypeSeq, idDataGroup, false);
      setFieldAllSubstituteValues (ifds::RESPBenefIDFrom, idDataGroup, substList ); 

      dstrAccountTo.stripLeading ('0');  

      if (!dstrAccountTo.empty ())
      {
         pRESPTransferList->getBeneficiaryMasterList (substList, dstrAccountTo, idDataGroup, false);	
         setFieldAllSubstituteValues (ifds::RESPBenefIDTo, idDataGroup, substList ); 
      }
	  setResidualCESGRelatedFields(idDataGroup);

	  setFieldReadOnly (ifds::IsResidualCESG, idDataGroup, !(getWorkSession().hasUpdatePermission(UAF::RESP_TRANSFER)));

   }
   else if (pRESPTransferList && recordLevel== RECORD_LEVEL::ACCOUNT)
   {
      setAccountLevelGrantsReadOnly (idDataGroup);
   }

   if (pRESPTransferList)
   {
      bool bReadOnly = pRESPTransferList->initTransferPercent (idDataGroup);

      setFieldReadOnly (ifds::TransferPercent, idDataGroup, bReadOnly);
      m_bTransferPrcntApplicable = !bReadOnly;

	  DString dstrTransType, dstrDepositType;

	  pRESPTransferList->getField (ifds::TransType, dstrTransType, idDataGroup);
	  pRESPTransferList->getField (ifds::DepositType, dstrDepositType, idDataGroup);

	  // Residual trade is only applied to ED-17
	  if( (dstrTransType != I_("ED")) || (dstrDepositType != I_("17")) )
	  {
		  setFieldNoValidate(ifds::IsResidualCESG, NO, idDataGroup, false, true, true);
		  setFieldReadOnly(ifds::IsResidualCESG, idDataGroup, true);
	  }
   }

   if (bSetFieldsReadOnly)
   {
      for (int i = 0; i < NUM_FIELDS; i++)
      {
         BFCBO::CLASS_FIELD_INFO fieldInfo = classFieldInfo [i];
         const BFFieldId &fieldId = fieldInfo.getFieldId();

         setFieldReadOnly (fieldId, idDataGroup, true);
      }
   }

   setFieldNoValidate (ifds::GrantAmountNA, I_(""), idDataGroup, false, true, true);
   setFieldReadOnly (ifds::GrantAmountNA, idDataGroup, true);

   setNotionalBalanceFields (idDataGroup, bSetNotionals);

   m_bFirstLoad = true;

   return GETCURRENTHIGHESTSEVERITY();
}

//***********************************************************************************
SEVERITY RESPTransfer::doValidateField( const BFFieldId &idField,
                                        const DString &strValue,
                                        const BFDataGroupId &idDataGroup)

{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField"));

   if (idField == ifds::RESPBenefIDFrom)
   {
      DString strRESPBenefIDFrom;
      getField (ifds::RESPBenefIDFrom, strRESPBenefIDFrom, idDataGroup, false);

      if(strRESPBenefIDFrom.empty())
      {
          ADDCONDITIONFROMFILE (CND::ERR_FROM_BENEF_IS_MISSING);
      }
      else 
      {
         bool bFromAccount = false;
         RESPTransferList *pRESPTransferList = dynamic_cast<RESPTransferList*>( getParent( ) );      

         if (pRESPTransferList)
         {
            bFromAccount = pRESPTransferList->isNonRespToResp (idDataGroup);
         }
         
         if(!m_bNonTrusteeHistTxfr)//for non-QESI: default historical with CurrTradeYear 
         {
            validateBeneficiary (strValue, idDataGroup, !bFromAccount); 
         }
         else
         {
            DString dstrTradeType;

            pRESPTransferList->getField (ifds::TradeType, dstrTradeType, idDataGroup, false);
            
            if(dstrTradeType == PROCESSED)
            {
               pRESPTransferList->checkExistingBenf(this,idDataGroup);
            }

         }
      }
   }
   else if (idField == ifds::RESPBenefIDTo)
   {
      validateBeneficiary (strValue, idDataGroup, false);
   }
   else if (idField == ifds::CLBAmount)
   {
      validateCLBGrant (idDataGroup);
   }
   else if (idField == ifds::TransferPercent)
   {
      validateTransferPercent (strValue, idDataGroup);
   }
   else if ( idField == ifds::EligibleTransfer )
   {
      if ( !getWorkSession().isQESIClient() )
         return GETCURRENTHIGHESTSEVERITY(); 

      DString strFieldValue(strValue);
      DString dstrRecordLevel;
      getField (ifds::RecordLevel, dstrRecordLevel, idDataGroup, false);
      strFieldValue.strip().upperCase();

      if ( strFieldValue == NO && 
           dstrRecordLevel == RECORD_LEVEL::BENEFICIARY )
      {
         ADDCONDITIONFROMFILE( CND::WARN_ELIGIBLE_TRANSFER_FILED_IS_NO );
      }
     
      if(m_bNonTrusteeHistTxfr)
      {
         //if EligibleTransfer = 'N', and taxyear < currTradeYear (historical) of BENEF
         //raise error : ERR_DEL_HIST_TXFR_BENEF_RECORD      
         DString dstrEligibleTransfer;

         getField (ifds::EligibleTransfer, dstrEligibleTransfer, idDataGroup);
         if(dstrEligibleTransfer == NO)
         {
            checkHistoricalTrade(idDataGroup);
         }
      }
   }
   else if(idField == ifds::HistNonTrustYear)
   {
      //check if 1st record of BENF added, contrib year must be current trade year 
      //       otherwise, raise erorr msg: Current tax year beneficiary is mandatory
      DString dstrHistNonTrustYear;
      
      getField (ifds::HistNonTrustYear, dstrHistNonTrustYear, idDataGroup);

      if(dstrHistNonTrustYear != m_dstrTradeYear )
      {

         RESPTransferList *pRESPTransferList = dynamic_cast<RESPTransferList*>( getParent( ) );

         if( !pRESPTransferList->checkContribution(this,idDataGroup, true) )
         { 
            clearFieldsForNonTrusteeTxfrGrants(idDataGroup); //greyout thing
            ADDCONDITIONFROMFILE (CND::ERR_BENEF_CURR_TAXYEAR_MANDATORY);  
            return GETCURRENTHIGHESTSEVERITY(); 
         }
      }
   }
   else if(idField == ifds::TotTransfINDC) 
   {
      //if TotTransfINDC = '0', and taxyear < currTradeYear (historical) of BENEF
      //raise error : ERR_DEL_HIST_TXFR_BENEF_RECORD 
      DString dstrTotTransfINDC;
      
      getField (ifds::TotTransfINDC, dstrTotTransfINDC, idDataGroup);
      if(dstrTotTransfINDC == I_("0"))
      {
         checkHistoricalTrade(idDataGroup);
      }
      
      //QESI Total TXFR cannot left BLNK if Eligible and Info Complte flagged 'Y'
      validateQESITotTxfr(idDataGroup);

   }
   /*else if(idField == ifds::GrantAmount)
   {
	   BigDecimal bdGrantAmount = DSTCommonFunctions::convertToBigDecimal(strValue);
	   DString dstrIsResidualCESG;

	   getField(ifds::IsResidualCESG, dstrIsResidualCESG, idDataGroup, false);
	   dstrIsResidualCESG.strip().upperCase();

	   if ( (bdGrantAmount == 0) && (dstrIsResidualCESG == YES) )
	   {
		   DString dstrSAGESGrant;
		   getField(ifds::SAGESGrant, dstrSAGESGrant, idDataGroup, false);
		   BigDecimal bdSAGESGrant = DSTCommonFunctions::convertToBigDecimal(dstrSAGESGrant);
		   bool bResidualGrantForSAGESOnly = getWorkSession().isSAGESClient() && bdSAGESGrant > 0;

		   if ( !bResidualGrantForSAGESOnly)
			   ADDCONDITIONFROMFILE (CND::ERR_CESG_AMOUNT_MANDATORY);  	   
	   }
   }*/
   else if (idField == ifds::SAGESACAmount) 
   {
	   if (validateSAGESUpdate(idField, idDataGroup) <= WARNING)
            validateSAGESACAmount (idDataGroup);
   }
   else if (idField == ifds::SAGESUCAmount)
   {
       validateSAGESUpdate(idField, idDataGroup);
   }
   else if (idField == ifds::SAGESGrant)
   {
       validateSAGESUpdate(idField, idDataGroup);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************************
SEVERITY RESPTransfer::validateSAGESUpdate(const BFFieldId &idField, const BFDataGroupId& idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateSAGESUpdate"));

    DString dstrValue, dstrFromBenefId, dstrTransType;
    DString dstrDepositType, dstrAccountFrom, siblingOnly, dstrTaxJuris;
    BigDecimal bdZero = DSTCommonFunctions::convertToBigDecimal(I_("0.0"));

    getField(idField, dstrValue, idDataGroup, false);
    BigDecimal dValue = DSTCommonFunctions::convertToBigDecimal(dstrValue);

    RESPTransferList *pRESPTransferList = dynamic_cast<RESPTransferList*>(getParent()); 
    MFAccount *pMFAccount = NULL;

    getField(ifds::RESPBenefIDFrom, dstrFromBenefId, idDataGroup, false);
    dstrFromBenefId.stripLeading('0');

    if (pRESPTransferList)
    {
        pRESPTransferList->getField(ifds::TransType, dstrTransType, idDataGroup);
        pRESPTransferList->getField(ifds::DepositType, dstrDepositType, idDataGroup);

        pRESPTransferList->getField(ifds::AccountNum, dstrAccountFrom, idDataGroup, false);

        dstrAccountFrom.stripLeading('0');

        if (getWorkSession().getMFAccount(idDataGroup, dstrAccountFrom, pMFAccount) <= WARNING && pMFAccount)
        {
            pMFAccount->getField(ifds::SiblingOnly, siblingOnly, idDataGroup, false);
            siblingOnly.strip().upperCase();
            DString dstrEff, dstrAllocPrnt, dstrHRDC, dstrDOB;
            pRESPTransferList->getRESPEntityInfo(dstrFromBenefId, 
                                                 idDataGroup, 
                                                 dstrAccountFrom, 
                                                 dstrEff, 
                                                 dstrAllocPrnt, 
                                                 dstrTaxJuris, 
                                                 dstrHRDC, 
                                                 dstrDOB);
        }
    }

    if (!dstrFromBenefId.empty() && 
        dstrTransType == I_("ED") && 
        dstrDepositType == I_("17") &&
        dValue != bdZero)
    {
        if (siblingOnly != Y)
            getErrMsg(IFASTERR::ACCOUNT_MUST_BE_SIBLING_ONLY_FOR_SAGES, 
				      CND::ERR_ACCOUNT_MUST_BE_SIBLING_ONLY_FOR_SAGES,
                      CND::WARN_ACCOUNT_MUST_BE_SIBLING_ONLY_FOR_SAGES,
				      idDataGroup);

        if (dstrTaxJuris != SASKATCHEWAN)
            getErrMsg(IFASTERR::BENEFICIARY_NOT_SASKATCHEWAN_RESIDENT, 
				      CND::ERR_BENEFICIARY_NOT_SASKATCHEWAN_RESIDENT, 
                      CND::WARN_BENEFICIARY_NOT_SASKATCHEWAN_RESIDENT, 
				      idDataGroup);
    }

    return GETHIGHESTSEVERITY();
}

//*****************************************************************************************
SEVERITY RESPTransfer::validateQESITotTxfr (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateQESITotTxfr"));

   DString strRecordLevel;
   DString strIsNonTrustee;
   DString strNEQ1;
   DString strEligibleTransfer;
   DString strRESPTransStat(NULL_STRING);

   getField (ifds::RecordLevel, strRecordLevel, idDataGroup, false);
   getWorkSession ().getOption (ifds::IsNonTrustee, strIsNonTrustee, idDataGroup, false);

   getField( ifds::EligibleTransfer, strEligibleTransfer, idDataGroup, false );

   RESPTransferList *pRESPTransferList = dynamic_cast<RESPTransferList*>( getParent( ) );      

   if (pRESPTransferList)
   {
      pRESPTransferList->getField( ifds::NEQ1, strNEQ1, idDataGroup, false ); // Todo: use m_bIsNonTrustee instead
      pRESPTransferList->getField( ifds::RESPTransStat, strRESPTransStat, idDataGroup, false);


      bool bTradeYearApplicable = isInHistoricalRESPPeriod(idDataGroup);
      bool bIsNonTrusteeFunctionApplicable = strIsNonTrustee == YES;
      bool bEligibleTransfer = strEligibleTransfer == YES;
      bool bRESPTransStat = strRESPTransStat == YES;
      strNEQ1.stripAll().upperCase();
      bool bIsNonTrusteeNEQ = strNEQ1 == I_("0");

      if ( bIsNonTrusteeFunctionApplicable && 
         bTradeYearApplicable && 
         bIsNonTrusteeNEQ )
      {
         if ((strRecordLevel == RECORD_LEVEL::BENEFICIARY )&&
            bEligibleTransfer &&
            bRESPTransStat)
         {
            DString strTotTransfINDC;

            getField (ifds::TotTransfINDC, strTotTransfINDC, idDataGroup);
            if(strTotTransfINDC.empty())


            {
               getErrMsg(IFASTERR::QESI_TOTAL_TRANSFER_FILED_IS_BLANK,
                  CND::ERR_QESI_TOTAL_TRANSFER_FILED_IS_BLANK, 
                  CND::WARN_QESI_TOTAL_TRANSFER_FILED_IS_BLANK,
                  idDataGroup);
            }
         }
      }
      }
  
   return GETCURRENTHIGHESTSEVERITY();
}
//*****************************************************************************************
SEVERITY RESPTransfer::doApplyRelatedChanges (const BFFieldId &idField, 
                                              const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges"));

   if (idField == ifds::RESPBenefIDFrom)
   {
      DString dstrEntityId;

      getField (ifds::RESPBenefIDFrom, dstrEntityId, idDataGroup, false);

      RESPTransferList *pRESPTransferList = dynamic_cast<RESPTransferList*>( getParent( ) );

      if (pRESPTransferList)
      {
         DString dstrEntityTypeSeq;
         DString dstrAccountNum;
         DString dstrAccountTo;

         pRESPTransferList->getField (ifds::AccountNum, dstrAccountNum, idDataGroup, false);
         pRESPTransferList->getField (ifds::AccountTo, dstrAccountTo, idDataGroup, false);

         bool bNonRespToResp = pRESPTransferList->isNonRespToResp (idDataGroup);

         if (bNonRespToResp)
         {
            dstrAccountNum = dstrAccountTo;
         }

         pRESPTransferList->getEntitySeqNumber (dstrEntityId, dstrAccountNum, idDataGroup, dstrEntityTypeSeq);
         setFieldNoValidate (ifds::RESPTrfEntityTypeSeqFrom, dstrEntityTypeSeq, idDataGroup, false);

         m_bChoosingBenef = false;
         
         // only for non-trustee trade
         //Check if the BENF with currTradeYear exists
         //      if YES, Default Eligible + INDC to addingBENF

         if(m_bNonTrusteeHistTxfr)
         {
            //---------------------------
            if(isNew())
            {
               DString defaultTransferPercent = m_bTransferPrcntApplicable ? DEFAULT_PERCENT : ZERO_PERCENT;

               setFieldNoValidate (ifds::TransferPercent, defaultTransferPercent, idDataGroup, false, true);
               //setFieldNoValidate (ifds::EligibleTransfer, NO, idDataGroup, false, false, true, false); 
               setFieldReadOnly (ifds::EligibleTransfer, idDataGroup, false);
            }
            //---------------------------
            
            //!!! check if the BENF has CurrTradeYear
            if( pRESPTransferList->checkContribution(this,idDataGroup, true) )
            {    
               //Default eligible and QESItot with the same BENEF
               DString eligibleTransfer, totTransfINDC; 

               pRESPTransferList->doDefaultWithBenefCurrTradeYear(this, eligibleTransfer, totTransfINDC, idDataGroup);

               setFieldNoValidate( ifds::EligibleTransfer, eligibleTransfer, idDataGroup, false , false, true, true); 
               setFieldNoValidate( ifds::TotTransfINDC, totTransfINDC, idDataGroup, false , false, true, true); 

               setFieldReadOnly (ifds::EligibleTransfer, idDataGroup, true);
               setFieldReadOnly (ifds::TotTransfINDC, idDataGroup, true);

            }
            else
            {
               doEligibleTransferRelatedChanges(idDataGroup);
            }                       
         }         
      }

      doCLBAmountChanges (idDataGroup);	 

   }
   else if (idField == ifds::RESPBenefIDTo)
   {
      DString dstrEntityIdTo;

      getField (ifds::RESPBenefIDTo, dstrEntityIdTo, idDataGroup, false);

      RESPTransferList *pRESPTransferList = dynamic_cast<RESPTransferList*>( getParent( ) );      

      if (pRESPTransferList)
      {
         DString dstrEntityTypeSeqTo;

         DString dstrAccountTo;

         pRESPTransferList->getField (ifds::AccountTo, dstrAccountTo, idDataGroup, false);

         pRESPTransferList->getEntitySeqNumber (dstrEntityIdTo, dstrAccountTo, idDataGroup, dstrEntityTypeSeqTo);
         setFieldNoValidate (ifds::RESPTrfEntityTypeSeqTo, dstrEntityTypeSeqTo, idDataGroup, false);
      }

      doCLBAmountChanges (idDataGroup);

   }
   else if (idField == ifds::TransferPercent)
   {
      doTransferPercentChanges (idDataGroup);
   }
   else if (idField == ifds::CLBAmount)
   {
      //doCLBAmountChanges (idDataGroup);
   }
   else if (idField ==  ifds::IsTotTransfINDCApplicable)
   {
	  doTotTransfINDCRelatedChanges(idDataGroup); //set isShownTaxyear flag
   }
   
   else if(idField == ifds::EligibleTransfer)
   {  
      //if Eligible = N, TotTransfINDC = BLNK, read-only
       //     if Eligible = Y, TotTransfINDC = LIST  
      doEligibleTransferRelatedChanges(idDataGroup);
      doTotTransfINDCRelatedChanges(idDataGroup); //set isShownTaxyear flag
      setFieldValid (ifds::TotTransfINDC, idDataGroup, false); // always validate
      
   }
   else if(idField == ifds::TotTransfINDC)
   { 
      doTotTransfINDCRelatedChanges(idDataGroup); //set isShownTaxyear flag
      setFieldValid (ifds::TotTransfINDC, idDataGroup, false); // always validate
   }
   else if ( idField == ifds::IsTotTransfINDCApplicable)
   {
      doTotTransfINDCRelatedChanges(idDataGroup); //set isShownTaxyear flag
      setFieldValid (ifds::TotTransfINDC, idDataGroup, false); // always validate
   }

   else if(idField ==  ifds::IsNotionalTaxYearApplicable)
   {    
       resetFieldsForNonTrusteeTxfrGrants(idDataGroup);
   }
   else if(idField ==  ifds::HistNonTrustYear)
   { 
      //Clear notional value when switching contrib year
      DString strIsNotionalTaxYearApplicable;
	   getField( ifds::IsNotionalTaxYearApplicable, 
		   strIsNotionalTaxYearApplicable,
		   idDataGroup, false );
		   
	   strIsNotionalTaxYearApplicable.stripAll();

      bool bIsClear = strIsNotionalTaxYearApplicable == I_("Y")? true : false;
      if(bIsClear)
      {
         clearFieldsForNonTrusteeTxfrGrants(idDataGroup);
      }

           
   }
   else if(idField ==  ifds::QESIYTDContribution)//IN2640270_WO661530
   {
      if(m_bNonTrusteeHistTxfr )
      {
         DString dstrHistNonTrustYear(NULL_STRING);
         
         getField (ifds::HistNonTrustYear, dstrHistNonTrustYear, idDataGroup, false);
         dstrHistNonTrustYear.stripAll();
         if(m_dstrTradeYear != dstrHistNonTrustYear)//Historical trade, Note: only passed year provided in the dropdown list
         {
            DString dstrQESIYTDContribution(NULL_STRING);
            
            getField (ifds::QESIYTDContribution, dstrQESIYTDContribution, idDataGroup, false);
                        setFieldNoValidate (ifds::QESIUCAmount, dstrQESIYTDContribution, idDataGroup, true, true, true, true); 
         }
      }     

	  doCalcQESIPre2007Amt (idDataGroup);
   }
   else if(idField == ifds::IsResidualCESG)
   {
	   /*********************************************************************************
	      The IsResidualCESG is the Benef level field, it is readonly for the account,
	      This logic here is automatically applied to benef level as it is readonly on the account.
	   **********************************************************************************/
	   setResidualCESGRelatedFields(idDataGroup);
   }
   else if (idField == ifds::GrantAmount)
   {
	    DString dstrIsResidualCESG;

	    getField(ifds::IsResidualCESG, dstrIsResidualCESG, idDataGroup, false);
		dstrIsResidualCESG.strip().upperCase();

		if (dstrIsResidualCESG == YES)
		{
		    doCalcAsstUnAsstAmt(idDataGroup);
		}
   }
   else if (idField == ifds::SAGESGrant)
   {
	   DString dstrIsResidualCESG;

	   getField(ifds::IsResidualCESG, dstrIsResidualCESG, idDataGroup, false);
	   dstrIsResidualCESG.strip().upperCase();

	   if (dstrIsResidualCESG == YES)
	   {
		   doCalcSAGESAsstUnAsstAmt(idDataGroup);
	   }
   }
   else if (idField == ifds::QESIBasicGrant)
   {
	    DString dstrIsResidualCESG;

	    getField(ifds::IsResidualCESG, dstrIsResidualCESG, idDataGroup, false);
		dstrIsResidualCESG.strip().upperCase();

		if (dstrIsResidualCESG == YES)
		{
		    doCalcQESIAsstUnAsstAmt(idDataGroup);
		}
   }
   else if (idField == ifds::TDContr || 
			idField == ifds::TDRedContrib ||
			idField == ifds::QESIACAmount ||
			idField == ifds::QESIRedACAmt ||
			idField == ifds::QESIUCAmount ||
			idField == ifds::QESIRedUCAmt ||			
			idField == ifds::QESIRedYTDContrib)
   {
	   doCalcQESIPre2007Amt (idDataGroup);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************************
SEVERITY RESPTransfer::doCalcAsstUnAsstAmt (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCalcAsstUnAsstAmt"));

   BigDecimal bdGrantAmt, bdUnAsstAmt, bdAsstAmt;
   DString dstrGrantAmt, dstrUnAsstAmt, dstrAsstAmt;

   getField(ifds::GrantAmount, dstrGrantAmt, idDataGroup, false);   

   bdGrantAmt = DSTCommonFunctions::convertToBigDecimal(dstrGrantAmt);
   bdGrantAmt = bdGrantAmt * 5;		
   bdUnAsstAmt = - bdGrantAmt;
   bdAsstAmt = bdGrantAmt;

   dstrUnAsstAmt = bdUnAsstAmt.asDString();
   dstrAsstAmt = bdAsstAmt.asDString();

   setFieldNoValidate(ifds::UCAmt, dstrUnAsstAmt, idDataGroup, false, true, true, true);
   setFieldNoValidate(ifds::ACAmt, dstrAsstAmt, idDataGroup, false, true, true, true);

   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************************
SEVERITY RESPTransfer::doCalcQESIAsstUnAsstAmt (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCalcQESIAsstUnAsstAmt"));
  
   BigDecimal bdQESIBasicGrant, bdQESIUCAmount, bdQESIACAmount;
   DString dstrQESIBasicGrant, dstrQESIUCAmount, dstrQESIACAmount;

   getField(ifds::QESIBasicGrant, dstrQESIBasicGrant, idDataGroup, false);   

   bdQESIBasicGrant = DSTCommonFunctions::convertToBigDecimal(dstrQESIBasicGrant);
   bdQESIBasicGrant = bdQESIBasicGrant * 10;		
   bdQESIUCAmount = - bdQESIBasicGrant;
   bdQESIACAmount = bdQESIBasicGrant;

   dstrQESIUCAmount = bdQESIUCAmount.asDString();
   dstrQESIACAmount = bdQESIACAmount.asDString();

   setFieldNoValidate(ifds::QESIUCAmount, dstrQESIUCAmount, idDataGroup, false, true, true, true);
   setFieldNoValidate(ifds::QESIACAmount, dstrQESIACAmount, idDataGroup, false, true, true, true);

   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************************
SEVERITY RESPTransfer::doCalcSAGESAsstUnAsstAmt (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCalcSAGESAsstUnAsstAmt"));

   BigDecimal bdSAGESGrant, bdSAGESUCAmount, bdSAGESACAmount;
   DString dstrSAGESGrant, dstrSAGESUCAmount, dstrSAGESACAmount;

   getField(ifds::SAGESGrant, dstrSAGESGrant, idDataGroup, false);   

   bdSAGESGrant = DSTCommonFunctions::convertToBigDecimal(dstrSAGESGrant);
   bdSAGESGrant = bdSAGESGrant * 10;		
   bdSAGESUCAmount = - bdSAGESGrant;
   bdSAGESACAmount = bdSAGESGrant;

   dstrSAGESUCAmount = bdSAGESUCAmount.asDString();
   dstrSAGESACAmount = bdSAGESACAmount.asDString();

   setFieldNoValidate(ifds::SAGESUCAmount, dstrSAGESUCAmount, idDataGroup, false, true, true, true);
   setFieldNoValidate(ifds::SAGESACAmount, dstrSAGESACAmount, idDataGroup, false, true, true, true);

   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************************
SEVERITY RESPTransfer::doTransferPercentChanges (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doTransferPercentChanges"));

   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************************
SEVERITY RESPTransfer::setAccountLevelGrantsReadOnly (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setAccountLevelReadOnly"));

   RESPTransferList *pRESPTransferList = dynamic_cast<RESPTransferList*>( getParent( ) );      

   if (pRESPTransferList)
   {
      DString dstrRecordLevel;
      DString dstrAcctLevelOverride;

      pRESPTransferList->getField (ifds::AcctLvlOverride, dstrAcctLevelOverride, idDataGroup);

      bool bPurchaseLike = pRESPTransferList->isPurchaseLikeTransfer (idDataGroup);;

      if (/*dstrAcctLevelOverride == YES ||*/ !bPurchaseLike)
         return GETCURRENTHIGHESTSEVERITY();

      getField (ifds::RecordLevel, dstrRecordLevel, idDataGroup, false);

      if (dstrRecordLevel == RECORD_LEVEL::ACCOUNT)
      {
         setGrantsReadOnly (true, idDataGroup);
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************************
SEVERITY RESPTransfer::setGrantsReadOnly (bool bReadOnly, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setGrantsReadOnly"));

   DString dstrTradeType, tradeDate, dstrAccountLevelOverride;   

   RESPTransferList *pRESPTransferList = dynamic_cast<RESPTransferList*>( getParent( ) );
   if (pRESPTransferList)
   {			
	   pRESPTransferList->getField (ifds::TradeType, dstrTradeType, idDataGroup, false);
	   pRESPTransferList->getField (ifds::EffectiveDate, tradeDate, idDataGroup);
	   pRESPTransferList->getField (ifds::AcctLvlOverride, dstrAccountLevelOverride, idDataGroup, false);
   }
  
   //bool bIsACESClient = (getWorkSession().isRESPTransformationClient() && getWorkSession().isACESClient(tradeDate)) ? true : false;

   setFieldReadOnly (ifds::YTDContr, idDataGroup, bReadOnly);
   setFieldReadOnly (ifds::TDContr, idDataGroup, bReadOnly);
   setFieldReadOnly (ifds::GrantAmount, idDataGroup, bReadOnly);
   setFieldReadOnly (ifds::AdditionalGrant, idDataGroup, bReadOnly);
   setFieldReadOnly (ifds::CLBAmount, idDataGroup, bReadOnly /*getWorkSession().isRESPTransformationClient() ? false : bReadOnly*/);
   setFieldReadOnly (ifds::PGrantAmount, idDataGroup, /*!bIsACESClient ? true : */bReadOnly);
   setFieldReadOnly (ifds::TDRedContrib, idDataGroup, bReadOnly);
   setFieldReadOnly (ifds::TDRedEarning, idDataGroup, bReadOnly);
   setFieldReadOnly (ifds::RedCESG, idDataGroup, bReadOnly);
   setFieldReadOnly (ifds::RedCLB, idDataGroup, bReadOnly);
   setFieldReadOnly (ifds::RedPGrant, idDataGroup, /*!bIsACESClient ? true : */bReadOnly);
   setFieldReadOnly (ifds::UCAmt, idDataGroup, bReadOnly);
   setFieldReadOnly (ifds::ACAmt, idDataGroup, bReadOnly);
   setFieldReadOnly (ifds::Pre98ContribAmt, idDataGroup, bReadOnly);
   setFieldReadOnly (ifds::Pre98RedContribAmt, idDataGroup, bReadOnly);
   setFieldReadOnly (ifds::QESIUCAmount, idDataGroup, bReadOnly);
   setFieldReadOnly (ifds::QESIACAmount, idDataGroup, bReadOnly);
   setFieldReadOnly (ifds::QESIYTDContribution, idDataGroup, bReadOnly);
   setFieldReadOnly (ifds::QESIBasicGrant, idDataGroup, bReadOnly);
   setFieldReadOnly (ifds::QESIIncreaseAmt, idDataGroup, bReadOnly);
   setFieldReadOnly (ifds::Pre98QESIContrib, idDataGroup, bReadOnly);
   setFieldReadOnly (ifds::Pre2007QESIContrib, idDataGroup, bReadOnly /*(getWorkSession().isRESPTransformationClient() && dstrTradeType != PROCESSED && dstrAccountLevelOverride == YES) ? true : bReadOnly*/);
   setFieldReadOnly (ifds::EligibleTransfer, idDataGroup, bReadOnly);
   setFieldReadOnly (ifds::CESGPaid, idDataGroup, bReadOnly); //P0185010.FN02.R01.02 - CESG Grant paid
   setFieldReadOnly (ifds::QESIPaid, idDataGroup, bReadOnly); 
 
   // IsResidualCESG is only applied to Beneficiary level, readonly for account level.
   //setFieldReadOnly (ifds::IsResidualCESG, idDataGroup, bReadOnly);

   setFieldReadOnly (ifds::SAGESGrant, idDataGroup, bReadOnly);
   setFieldReadOnly (ifds::SAGESUCAmount, idDataGroup, bReadOnly);
   setFieldReadOnly (ifds::SAGESACAmount, idDataGroup, bReadOnly);

   setFieldReadOnly (ifds::GrantAmountNA, idDataGroup, true);
   setFieldReadOnly (ifds::BCTESGGrant, idDataGroup, bReadOnly);
  
   setFieldReadOnly (ifds::UCRedAmt, idDataGroup, bReadOnly);
   setFieldReadOnly (ifds::ACRedAmt, idDataGroup, bReadOnly);
   setFieldReadOnly (ifds::RedAdditionalGrant, idDataGroup, bReadOnly);

   // get 'TransferSplit' rule type value for: SAGES (Grant,AC,UC), QESIB (AC,UC,YTD,Basic), QESII, BCTESG - configured as 'Net' or 'PurRed'
   //bool bSAGESNetBalTransfer  = getWorkSession().isNetBalTransfer(I_("SAGES"), idDataGroup);
   //bool bQESIBNetBalTransfer  = getWorkSession().isNetBalTransfer(I_("QESIB"), idDataGroup);
   //bool bQESIINetBalTransfer  = getWorkSession().isNetBalTransfer(I_("QESII"), idDataGroup);
   //bool bBCTESGNetBalTransfer = getWorkSession().isNetBalTransfer(I_("BCTESG"),idDataGroup);
   
   setFieldReadOnly (ifds::SAGESRedUCAmt, idDataGroup, bReadOnly /*|| bSAGESNetBalTransfer*/);
   setFieldReadOnly (ifds::SAGESRedACAmt, idDataGroup, bReadOnly /*|| bSAGESNetBalTransfer*/);
   setFieldReadOnly (ifds::RedSAGES, idDataGroup, bReadOnly /*|| bSAGESNetBalTransfer*/);
   setFieldReadOnly (ifds::QESIRedUCAmt, idDataGroup, bReadOnly /*|| bQESIBNetBalTransfer*/);
   setFieldReadOnly (ifds::QESIRedACAmt, idDataGroup, bReadOnly /*|| bQESIBNetBalTransfer*/);
   setFieldReadOnly (ifds::QESIRedYTDContrib, idDataGroup, bReadOnly /*|| bQESIBNetBalTransfer*/);
   setFieldReadOnly (ifds::Pre2007QESIRedContrib, idDataGroup, bReadOnly);
   setFieldReadOnly (ifds::QESIRedBasic, idDataGroup, bReadOnly /*|| bQESIBNetBalTransfer*/);
   setFieldReadOnly (ifds::QESIRedIncrease, idDataGroup, bReadOnly /*|| bQESIINetBalTransfer*/);
   setFieldReadOnly (ifds::RedBCTESG, idDataGroup, bReadOnly /*|| bBCTESGNetBalTransfer*/);
   
   return GETCURRENTHIGHESTSEVERITY();
}
//*****************************************************************************************
SEVERITY RESPTransfer::setResidualCESGRelatedFields (const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setResidualCESGRelatedFields"));

	DString dstrIsResidualCESG;

	// all the fields should be readonly except CESG amount
	setFederalFieldsReadOnly(idDataGroup);

	getField(ifds::IsResidualCESG, dstrIsResidualCESG, idDataGroup, false);
	dstrIsResidualCESG.strip().upperCase();

	if ( (dstrIsResidualCESG == YES) && (!m_bInitExisting))
	{
		setFieldValid (ifds::GrantAmount, idDataGroup, false);
	
		setFieldNoValidate (ifds::YTDContr, I_("0"), idDataGroup, false, true, true);
		setFieldNoValidate (ifds::TDContr, I_("0"), idDataGroup, false, true, true);
		setFieldNoValidate (ifds::GrantAmount, I_("0"), idDataGroup, false, false, true);
		setFieldNoValidate (ifds::AdditionalGrant, I_("0"), idDataGroup, false, true, true);
		setFieldNoValidate (ifds::CLBAmount, I_("0"), idDataGroup, false, true, true);
		setFieldNoValidate (ifds::PGrantAmount, I_("0"), idDataGroup, false, true, true);
		setFieldNoValidate (ifds::TDRedContrib, I_("0"), idDataGroup, false, true, true);
		setFieldNoValidate (ifds::TDRedEarning, I_("0"), idDataGroup, false, true, true);
		setFieldNoValidate (ifds::RedCESG, I_("0"), idDataGroup, false, true, true);
		setFieldNoValidate (ifds::RedCLB, I_("0"), idDataGroup, false, true, true);
		setFieldNoValidate (ifds::RedPGrant, I_("0"), idDataGroup, false, true, true);
		setFieldNoValidate (ifds::UCAmt, I_("0"), idDataGroup, false, true, true);
		setFieldNoValidate (ifds::ACAmt, I_("0"), idDataGroup, false, true, true);
		setFieldNoValidate (ifds::Pre98ContribAmt, I_("0"), idDataGroup, false, true, true);
		setFieldNoValidate (ifds::Pre98RedContribAmt, I_("0"), idDataGroup, false, true, true);
		setFieldNoValidate (ifds::CESGPaid, I_("0"), idDataGroup, false, true, true); 
		setFieldNoValidate (ifds::SAGESGrant, I_("0"), idDataGroup, false, true, true); 
		setFieldNoValidate (ifds::SAGESUCAmount, I_("0"), idDataGroup, false, true, true); 
		setFieldNoValidate (ifds::SAGESACAmount, I_("0"), idDataGroup, false, true, true);
		setFieldNoValidate (ifds::BCTESGGrant, I_("0"), idDataGroup, false, true, true);
		setFieldNoValidate (ifds::UCRedAmt, I_("0"), idDataGroup, false, true, true);
		setFieldNoValidate (ifds::ACRedAmt, I_("0"), idDataGroup, false, true, true);
		setFieldNoValidate (ifds::SAGESRedUCAmt, I_("0"), idDataGroup, false, true, true);
		setFieldNoValidate (ifds::SAGESRedACAmt, I_("0"), idDataGroup, false, true, true);
		setFieldNoValidate (ifds::QESIRedUCAmt, I_("0"), idDataGroup, false, true, true);
		setFieldNoValidate (ifds::QESIRedACAmt, I_("0"), idDataGroup, false, true, true);
		setFieldNoValidate (ifds::QESIRedYTDContrib, I_("0"), idDataGroup, false, true, true);		
		setFieldNoValidate (ifds::Pre2007QESIRedContrib, I_("0"), idDataGroup, false, true, true);
		setFieldNoValidate (ifds::RedAdditionalGrant, I_("0"), idDataGroup, false, true, true);
		setFieldNoValidate (ifds::RedSAGES, I_("0"), idDataGroup, false, true, true);
		setFieldNoValidate (ifds::QESIRedBasic, I_("0"), idDataGroup, false, true, true);
		setFieldNoValidate (ifds::QESIRedIncrease, I_("0"), idDataGroup, false, true, true);
		setFieldNoValidate (ifds::RedBCTESG, I_("0"), idDataGroup, false, true, true);
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************************
SEVERITY RESPTransfer::setFederalFieldsReadOnly (const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setFederalFieldsReadOnly"));

	/************************************************************************************
		This method is created for the futher purpose, if there is any new fields on the
		federal tab. We could add to here to make the fields state changed according to the criteria.
		As well as if there are any more criteria impact the field state. 
		We could add here, so the flow will not be Spaghetti.

	************************************************************************************/

	bool bIsRespTransformation = getWorkSession().isRESPTransformationClient ();

	DString dstrIsResidualCESG;
	bool bReadOnly = false;

	if (bIsRespTransformation)
	{
		DString dstrRecordLevel, dstrTransType, dstrDepositType, tradeDate, dstrTradeType, dstrRedCode, dstrAccountLevelOverride;

		getField (ifds::RecordLevel, dstrRecordLevel, idDataGroup, false);
		bool bAcctLevel = (dstrRecordLevel == RECORD_LEVEL::ACCOUNT) ? true : false;

		RESPTransferList *pRESPTransferList = dynamic_cast<RESPTransferList*>( getParent( ) );
		if (pRESPTransferList)
		{
			pRESPTransferList->getField (ifds::TransType, dstrTransType, idDataGroup);
			pRESPTransferList->getField (ifds::DepositType, dstrDepositType, idDataGroup);
			pRESPTransferList->getField (ifds::RedCode, dstrRedCode, idDataGroup);
			pRESPTransferList->getField (ifds::EffectiveDate, tradeDate, idDataGroup);
			pRESPTransferList->getField (ifds::TradeType, dstrTradeType, idDataGroup, false);
			pRESPTransferList->getField (ifds::AcctLvlOverride, dstrAccountLevelOverride, idDataGroup, false);
		}

		if (bAcctLevel)
			bReadOnly = true;
		else
		{
			if ((dstrTradeType == PROCESSED) || (dstrTransType == I_("ED") && dstrDepositType == I_("17")) 
											 ||	(DSTCommonFunctions::codeInList(dstrTransType, I_("AFTR,TR,TI")) && dstrDepositType == I_("17") && DSTCommonFunctions::codeInList(dstrRedCode, I_("01,25,27")))
											 || dstrAccountLevelOverride == YES)
				bReadOnly = false;
			else
				bReadOnly = true;
		}
		
		bool bIsSAGESClient = getWorkSession().isSAGESClient();
		bool bIsQESIClient = getWorkSession().isQESIClient();	
		bool bIsBCTESGClient = getWorkSession().isBCTESGClient();		
		bool bIsACESClient = getWorkSession().isACESClient(tradeDate);

		//bool bSameSIN = false, bDiffSINTransfer = false;
		//bool bPartialTransferRespToResp = (dstrTransType == I_("TR") && dstrDepositType == I_("17") && dstrRedCode == I_("64")) ? true : false;

		//if (bPartialTransferRespToResp) // TR-17/64, different SIN
		//{	
		//	DString dstrBeneficiaryFrom, dstrBeneficiaryTo;

		//	getField (ifds::RESPBenefIDFrom, dstrBeneficiaryFrom, idDataGroup);
		//	getField (ifds::RESPBenefIDTo, dstrBeneficiaryTo, idDataGroup);
		//	dstrBeneficiaryFrom.stripLeading ('0');
		//	dstrBeneficiaryTo.stripLeading ('0');

		//	if (!(dstrBeneficiaryFrom.empty() || dstrBeneficiaryTo.empty()))
		//	{					
		//		isSameSIN (idDataGroup, bSameSIN);
		//		if (!bSameSIN)
		//			bDiffSINTransfer = true;
		//	}
		//}
		
		setFieldReadOnly (ifds::YTDContr, idDataGroup, bReadOnly);
		setFieldReadOnly (ifds::TDContr, idDataGroup, bReadOnly);
		setFieldReadOnly (ifds::GrantAmount, idDataGroup, bReadOnly);		
		setFieldReadOnly (ifds::AdditionalGrant, idDataGroup, bReadOnly);
		setFieldReadOnly (ifds::RedAdditionalGrant, idDataGroup, bReadOnly);
		setFieldReadOnly (ifds::CLBAmount, idDataGroup, bReadOnly);							
		setFieldReadOnly (ifds::TDRedContrib, idDataGroup, bReadOnly);
		setFieldReadOnly (ifds::TDRedEarning, idDataGroup, bReadOnly);
		setFieldReadOnly (ifds::RedCESG, idDataGroup, bReadOnly);
		setFieldReadOnly (ifds::RedCLB, idDataGroup, bReadOnly);		
		setFieldReadOnly (ifds::UCAmt, idDataGroup, bReadOnly);
		setFieldReadOnly (ifds::UCRedAmt, idDataGroup, bReadOnly);
		setFieldReadOnly (ifds::ACAmt, idDataGroup, bReadOnly);
		setFieldReadOnly (ifds::ACRedAmt, idDataGroup, bReadOnly);
		setFieldReadOnly (ifds::Pre98ContribAmt, idDataGroup, bReadOnly);
		setFieldReadOnly (ifds::Pre98RedContribAmt, idDataGroup, bReadOnly);
		setFieldReadOnly (ifds::CESGPaid, idDataGroup, bReadOnly);
 					
		doCLBAmountChanges(idDataGroup, false);	// disable CLB fields for different SIN transfers

		// get 'TransferSplit' rule type value for: SAGES (Grant,AC,UC), QESIB (AC,UC,YTD,Basic), QESII, BCTESG - configured as 'Net' or 'PurRed'
		bool bSAGESNetBalTransfer  = getWorkSession().isNetBalTransfer(I_("SAGES"), idDataGroup);
		bool bQESIBNetBalTransfer  = getWorkSession().isNetBalTransfer(I_("QESIB"), idDataGroup);
		bool bQESIINetBalTransfer  = getWorkSession().isNetBalTransfer(I_("QESII"), idDataGroup);
		bool bBCTESGNetBalTransfer = getWorkSession().isNetBalTransfer(I_("BCTESG"),idDataGroup);		

		// SAGES
		setFieldReadOnly (ifds::SAGESGrant, idDataGroup, bReadOnly || !bIsSAGESClient);
		setFieldReadOnly (ifds::SAGESUCAmount, idDataGroup, bReadOnly || !bIsSAGESClient);
		setFieldReadOnly (ifds::SAGESACAmount, idDataGroup, bReadOnly || !bIsSAGESClient);
		setFieldReadOnly (ifds::SAGESRedUCAmt, idDataGroup, bReadOnly || !bIsSAGESClient || bSAGESNetBalTransfer);
		setFieldReadOnly (ifds::SAGESRedACAmt, idDataGroup, bReadOnly || !bIsSAGESClient || bSAGESNetBalTransfer);
		setFieldReadOnly (ifds::RedSAGES, idDataGroup, bReadOnly || !bIsSAGESClient || bSAGESNetBalTransfer);		

		// QESI
		setFieldReadOnly (ifds::QESIUCAmount, idDataGroup, bReadOnly || !bIsQESIClient);
		setFieldReadOnly (ifds::QESIACAmount, idDataGroup, bReadOnly || !bIsQESIClient);
		setFieldReadOnly (ifds::QESIYTDContribution, idDataGroup, bReadOnly || !bIsQESIClient);
		setFieldReadOnly (ifds::QESIBasicGrant, idDataGroup, bReadOnly || !bIsQESIClient);
		setFieldReadOnly (ifds::QESIIncreaseAmt, idDataGroup, bReadOnly || !bIsQESIClient);
		setFieldReadOnly (ifds::Pre2007QESIContrib, idDataGroup, ((dstrTradeType != PROCESSED && dstrAccountLevelOverride == YES) || !bIsQESIClient) ? true : bReadOnly);		
		setFieldReadOnly (ifds::QESIPaid, idDataGroup, bReadOnly || !bIsQESIClient);
		setFieldReadOnly (ifds::QESIRedUCAmt, idDataGroup, bReadOnly || !bIsQESIClient || bQESIBNetBalTransfer);
		setFieldReadOnly (ifds::QESIRedACAmt, idDataGroup, bReadOnly || !bIsQESIClient || bQESIBNetBalTransfer);		
		setFieldReadOnly (ifds::QESIRedYTDContrib, idDataGroup, bReadOnly || !bIsQESIClient || bQESIBNetBalTransfer);
		setFieldReadOnly (ifds::Pre2007QESIRedContrib, idDataGroup, bReadOnly);	
		setFieldReadOnly (ifds::QESIRedBasic, idDataGroup, bReadOnly || !bIsQESIClient || bQESIBNetBalTransfer);
		setFieldReadOnly (ifds::QESIRedIncrease, idDataGroup, bReadOnly || !bIsQESIClient || bQESIINetBalTransfer);

		// BCTESG
		setFieldReadOnly( ifds::BCTESGGrant, idDataGroup, bReadOnly || !bIsBCTESGClient);
		setFieldReadOnly (ifds::RedBCTESG, idDataGroup, bReadOnly || !bIsBCTESGClient || bBCTESGNetBalTransfer);

		// ACES
		setFieldReadOnly( ifds::PGrantAmount, idDataGroup, !bIsACESClient);
		setFieldReadOnly( ifds::RedPGrant, idDataGroup, !bIsACESClient);
	}
	else
	{

		getField(ifds::IsResidualCESG, dstrIsResidualCESG, idDataGroup, false);
		dstrIsResidualCESG.strip().upperCase();

		if( dstrIsResidualCESG == YES )
			bReadOnly = true;

		setFieldReadOnly (ifds::YTDContr, idDataGroup, bReadOnly);
		setFieldReadOnly (ifds::TDContr, idDataGroup, bReadOnly);
		setFieldReadOnly (ifds::GrantAmount, idDataGroup, false);
		setFieldReadOnly (ifds::AdditionalGrant, idDataGroup, bReadOnly);
		setFieldReadOnly (ifds::CLBAmount, idDataGroup, bReadOnly);
		setFieldReadOnly (ifds::PGrantAmount, idDataGroup, bReadOnly);
		setFieldReadOnly (ifds::TDRedContrib, idDataGroup, bReadOnly);
		setFieldReadOnly (ifds::TDRedEarning, idDataGroup, bReadOnly);
		setFieldReadOnly (ifds::RedCESG, idDataGroup, bReadOnly);
		setFieldReadOnly (ifds::RedCLB, idDataGroup, bReadOnly);
		setFieldReadOnly (ifds::RedPGrant, idDataGroup, bReadOnly);
		setFieldReadOnly (ifds::UCAmt, idDataGroup, bReadOnly);
		setFieldReadOnly (ifds::ACAmt, idDataGroup, bReadOnly);
		setFieldReadOnly (ifds::Pre98ContribAmt, idDataGroup, bReadOnly);
		setFieldReadOnly (ifds::Pre98RedContribAmt, idDataGroup, bReadOnly);
		setFieldReadOnly (ifds::CESGPaid, idDataGroup, bReadOnly); //P0185010.FN02.R01.02 - CESG Grant paid

		// SAGES 
		bool bIsSAGESClient = getWorkSession().isSAGESClient();
		setFieldReadOnly (ifds::SAGESGrant, idDataGroup, !bIsSAGESClient);
		setFieldReadOnly (ifds::SAGESUCAmount, idDataGroup, bReadOnly || !bIsSAGESClient);
		setFieldReadOnly (ifds::SAGESACAmount, idDataGroup, bReadOnly || !bIsSAGESClient);

		DString tradeDate;
		bool bIsBCTESGClient = false, bIsACESClient = false;

		RESPTransferList *pRESPTransferList = dynamic_cast<RESPTransferList*>( getParent( ) );
		if (pRESPTransferList)
		{
			pRESPTransferList->getField (ifds::EffectiveDate, tradeDate, idDataGroup);
		}

		bIsBCTESGClient = getWorkSession().isBCTESGClient();
		bIsACESClient = getWorkSession().isACESClient(tradeDate);

		setFieldReadOnly( ifds::BCTESGGrant, idDataGroup, !bIsBCTESGClient);
		setFieldReadOnly( ifds::PGrantAmount, idDataGroup, !bIsACESClient);
		setFieldReadOnly( ifds::RedPGrant, idDataGroup, !bIsACESClient);
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************************
SEVERITY RESPTransfer::setNotionalBalanceFields (const BFDataGroupId& idDataGroup, bool bSetNotionals)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setNotionalBalanceFields"));

	bool bSameSIN = false;
	bool bIsRespTransformation = getWorkSession().isRESPTransformationClient ();

	if (bIsRespTransformation)
	{			
		DString dstrTransType, dstrDepositType, dstrRedCode, dstrTradeType;

		RESPTransferList *pRESPTransferList = dynamic_cast<RESPTransferList*>( getParent( ) );
		if (pRESPTransferList)
		{
			pRESPTransferList->getField (ifds::TransType, dstrTransType, idDataGroup);
			pRESPTransferList->getField (ifds::DepositType, dstrDepositType, idDataGroup);
			pRESPTransferList->getField (ifds::RedCode, dstrRedCode, idDataGroup);
			pRESPTransferList->getField (ifds::TradeType, dstrTradeType, idDataGroup, false);
			
			bool bExternalTI = (dstrTransType == I_("ED") && dstrDepositType == I_("17")) ? true : false;
			bool bClientToClientTI = (dstrTransType == I_("TI") &&  dstrDepositType == I_("17") && DSTCommonFunctions::codeInList(dstrRedCode, I_("64,65"))) ? true : false;			
			bool bClientToNomineeTIK = (DSTCommonFunctions::codeInList(dstrTransType, I_("AFTR,TR,TI")) && dstrDepositType == I_("17") && DSTCommonFunctions::codeInList(dstrRedCode, I_("01,25,27"))) ? true : false;
			bool bNomineeToClientTI = (dstrTransType == I_("TI") && dstrDepositType == I_("01") && DSTCommonFunctions::codeInList(dstrRedCode, I_("64,65"))) ? true : false;

			bool bTransferIn = bExternalTI || bClientToClientTI || bClientToNomineeTIK || bNomineeToClientTI; // positive purchase/received fields and negative redemption/paid out fields

			bool bApplyNegative = (dstrTradeType == PROCESSED || (dstrTradeType == PENDING && !bSetNotionals)) ? false : true; 
			if (!bTransferIn && !bApplyNegative) // no sign change for processed/pending TO trades
				bTransferIn = true;

			//bool bExternalTO = (dstrTransType == I_("PW") && DSTCommonFunctions::codeInList(dstrRedCode, I_("64,65"))) ? true : false;			
			//bool bInternalTO = (dstrTransType == I_("TO") &&  dstrDepositType == I_("17") && DSTCommonFunctions::codeInList(dstrRedCode, I_("64,65"))) ? true : false;
			//bool bClientToClientTIK  = (DSTCommonFunctions::codeInList(dstrTransType, I_("AFTR,TR")) && dstrDepositType == I_("17") && DSTCommonFunctions::codeInList(dstrRedCode, I_("64,65"))) ? true : false;			
			//bool bNomineeToClientTIK = (DSTCommonFunctions::codeInList(dstrTransType, I_("AFTR,TR")) && dstrDepositType == I_("01") && DSTCommonFunctions::codeInList(dstrRedCode, I_("64,65"))) ? true : false;							

			//bool bSameSIN = false;
			//bool bPartialClientToClientTIK = (dstrTransType == I_("TR") && dstrDepositType == I_("17") && dstrRedCode == I_("64")) ? true : false;

			// one 'TransferSplit' rule type record per notional type: CNTB, P98C, CESG, ADCESG, CLB configured as 'PurRed' for all clients	
			bool bCNTBNetBalTransfer   = getWorkSession().isNetBalTransfer(I_("CNTB"), idDataGroup);
			bool bP98CNetBalTransfer   = getWorkSession().isNetBalTransfer(I_("P98C"), idDataGroup);
			bool bCESGNetBalTransfer   = getWorkSession().isNetBalTransfer(I_("CESG"), idDataGroup);
			bool bADCESGNetBalTransfer = getWorkSession().isNetBalTransfer(I_("ADCESG"), idDataGroup);
			bool bCLBNetBalTransfer	   = getWorkSession().isNetBalTransfer(I_("CLB"),idDataGroup);

			// one 'TransferSplit' rule type record per P2007C notional type configured as 'Net' for all clients
			bool bP2007CNetBalTransfer = getWorkSession().isNetBalTransfer(I_("P2007C"),idDataGroup);

			// one 'TransferSplit' rule type record per notional type: SAGES (Grant,AC,UC), QESIB (AC,UC,YTD,Basic), QESII, BCTESG configured as 'Net' or 'PurRed'
			bool bSAGESNetBalTransfer  = getWorkSession().isNetBalTransfer(I_("SAGES"), idDataGroup);
			bool bQESIBNetBalTransfer  = getWorkSession().isNetBalTransfer(I_("QESIB"), idDataGroup);
			bool bQESIINetBalTransfer  = getWorkSession().isNetBalTransfer(I_("QESII"), idDataGroup);
			bool bBCTESGNetBalTransfer = getWorkSession().isNetBalTransfer(I_("BCTESG"),idDataGroup);					

			// for'PurRed' configuration, populate purchase/received fields with a negative sign and redemption/paid out fields with a positive sign for TO, and positive/negative for TI
			// for 'Net' configuration, populate purchase/received fields with a negative sign for TO and positive sign for TI of the net balance and redemption/paid out fields with zero 

			// 'PurRed' for all clients	
			if (bCNTBNetBalTransfer)
				doCalcNotionalBalanceAmt (idDataGroup, ifds::TDContr, ifds::TDRedContrib, bTransferIn); // Life to Date Contribution
			else
				doCalcPurRedNotionalAmt (idDataGroup, ifds::TDContr, ifds::TDRedContrib, bTransferIn); // Life to Date Contribution

			// 'PurRed' for all clients	
			if (bP98CNetBalTransfer)
				doCalcNotionalBalanceAmt (idDataGroup, ifds::Pre98ContribAmt, ifds::Pre98RedContribAmt, bTransferIn); // Pre-1998 Contribution
			else
				doCalcPurRedNotionalAmt (idDataGroup, ifds::Pre98ContribAmt, ifds::Pre98RedContribAmt, bTransferIn); // Pre-1998 Contribution

			// 'PurRed' for all clients	
			if (bCESGNetBalTransfer)
			{
				doCalcNotionalBalanceAmt (idDataGroup, ifds::UCAmt, ifds::UCRedAmt, bTransferIn); // CESG Unassisted
				doCalcNotionalBalanceAmt (idDataGroup, ifds::ACAmt, ifds::ACRedAmt, bTransferIn); // CESG Assisted							
				doCalcNotionalBalanceAmt (idDataGroup, ifds::GrantAmount, ifds::RedCESG, bTransferIn); // CESG	
			}
			else
			{
				doCalcPurRedNotionalAmt (idDataGroup, ifds::UCAmt, ifds::UCRedAmt, bTransferIn); // CESG Unassisted
				doCalcPurRedNotionalAmt (idDataGroup, ifds::ACAmt, ifds::ACRedAmt, bTransferIn); // CESG Assisted							
				doCalcPurRedNotionalAmt (idDataGroup, ifds::GrantAmount, ifds::RedCESG, bTransferIn); // CESG	
			}

			// 'PurRed' for all clients	
			if (bADCESGNetBalTransfer)
				doCalcNotionalBalanceAmt (idDataGroup, ifds::AdditionalGrant, ifds::RedAdditionalGrant, bTransferIn); // Additional CESG
			else
				doCalcPurRedNotionalAmt (idDataGroup, ifds::AdditionalGrant, ifds::RedAdditionalGrant, bTransferIn); // Additional CESG

			// 'PurRed' for all clients	
			if (bCLBNetBalTransfer)
				doCalcNotionalBalanceAmt (idDataGroup, ifds::CLBAmount, ifds::RedCLB, bTransferIn); // CLB
			else
				doCalcPurRedNotionalAmt (idDataGroup, ifds::CLBAmount, ifds::RedCLB, bTransferIn); // CLB

			//if (bPartialClientToClientTIK) // TR-17/64, different SIN
			//{	
			//	DString dstrBeneficiaryFrom, dstrBeneficiaryTo;

			//	getField (ifds::RESPBenefIDFrom, dstrBeneficiaryFrom, idDataGroup);
			//	getField (ifds::RESPBenefIDTo, dstrBeneficiaryTo, idDataGroup);
			//	dstrBeneficiaryFrom.stripLeading ('0');
			//	dstrBeneficiaryTo.stripLeading ('0');

			//	if (!(dstrBeneficiaryFrom.empty() || dstrBeneficiaryTo.empty()))
			//	{					
			//		isSameSIN (idDataGroup, bSameSIN);	
			//		if (!bSameSIN)
			//		{
			//			setFieldNoValidate (ifds::CLBAmount, I_("0"), idDataGroup);					
			//			setFieldNoValidate (ifds::RedCLB, I_("0"), idDataGroup);	
			//		}
			//	}
			//}

			doCLBAmountChanges(idDataGroup);

			doCalcPurRedNotionalAmt (idDataGroup, ifds::PGrantAmount, ifds::RedPGrant, bTransferIn); // ACES
			//doCalcPurRedNotionalAmt (idDataGroup, ifds::GrantAmountNA, ifds::CESGPaid); // CESG By Other Institution - always positive
			//doCalcPurRedNotionalAmt (idDataGroup, ifds::GrantAmountNA, ifds::QESIPaid); // QESI By Other Institution - always positive

			// 'Net' for all clients			
			doCalcNotionalBalanceAmt (idDataGroup, ifds::Pre2007QESIContrib, ifds::Pre2007QESIRedContrib, bTransferIn); // QESI Pre-Feb 21, 2007			

			// 'Net' or 'PurRed'
			if (bSAGESNetBalTransfer)
			{
				doCalcNotionalBalanceAmt (idDataGroup, ifds::SAGESUCAmount, ifds::SAGESRedUCAmt, bTransferIn); // SAGES Unassisted
				doCalcNotionalBalanceAmt (idDataGroup, ifds::SAGESACAmount, ifds::SAGESRedACAmt, bTransferIn); // SAGES Assisted		
				doCalcNotionalBalanceAmt (idDataGroup, ifds::SAGESGrant, ifds::RedSAGES, bTransferIn); // SAGES		
			}
			else
			{
				doCalcPurRedNotionalAmt (idDataGroup, ifds::SAGESUCAmount, ifds::SAGESRedUCAmt, bTransferIn); // SAGES Unassisted
				doCalcPurRedNotionalAmt (idDataGroup, ifds::SAGESACAmount, ifds::SAGESRedACAmt, bTransferIn); // SAGES Assisted		
				doCalcPurRedNotionalAmt (idDataGroup, ifds::SAGESGrant, ifds::RedSAGES, bTransferIn); // SAGES
			}

			// 'Net' or 'PurRed'
			if (bQESIBNetBalTransfer)
			{			
				doCalcNotionalBalanceAmt (idDataGroup, ifds::QESIYTDContribution, ifds::QESIRedYTDContrib, bTransferIn); // QESI YTD
				doCalcNotionalBalanceAmt (idDataGroup, ifds::QESIACAmount, ifds::QESIRedACAmt, bTransferIn); // QESI Assisted
				doCalcNotionalBalanceAmt (idDataGroup, ifds::QESIUCAmount, ifds::QESIRedUCAmt, bTransferIn); // QESI Unassisted								
				doCalcNotionalBalanceAmt (idDataGroup, ifds::QESIBasicGrant, ifds::QESIRedBasic, bTransferIn); // QESI Basic		
			}
			else
			{
				doCalcPurRedNotionalAmt (idDataGroup, ifds::QESIYTDContribution, ifds::QESIRedYTDContrib, bTransferIn); // QESI YTD
				doCalcPurRedNotionalAmt (idDataGroup, ifds::QESIACAmount, ifds::QESIRedACAmt, bTransferIn); // QESI Assisted
				doCalcPurRedNotionalAmt (idDataGroup, ifds::QESIUCAmount, ifds::QESIRedUCAmt, bTransferIn); // QESI Unassisted				
				doCalcPurRedNotionalAmt (idDataGroup, ifds::QESIBasicGrant, ifds::QESIRedBasic, bTransferIn); // QESI Basic		
			}

			// 'Net' or 'PurRed'
			if (bQESIINetBalTransfer)				 
				doCalcNotionalBalanceAmt (idDataGroup, ifds::QESIIncreaseAmt, ifds::QESIRedIncrease, bTransferIn); // QESI Increase	
			else
				doCalcPurRedNotionalAmt (idDataGroup, ifds::QESIIncreaseAmt, ifds::QESIRedIncrease, bTransferIn); // QESI Increase		

			// 'Net' or 'PurRed'
			if (bBCTESGNetBalTransfer)					
				doCalcNotionalBalanceAmt (idDataGroup, ifds::BCTESGGrant, ifds::RedBCTESG, bTransferIn); // BCTESG							
			else
				doCalcPurRedNotionalAmt (idDataGroup, ifds::BCTESGGrant, ifds::RedBCTESG, bTransferIn);	// BCTESG								
		}
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************************
SEVERITY RESPTransfer::doCalcNotionalBalanceAmt (const BFDataGroupId& idDataGroup, const BFFieldId &idFieldPur, const BFFieldId &idFieldRed, bool bTransferIn)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCalcNotionalBalanceAmt"));

	BigDecimal bdPurAmt(0), bdRedAmt(0), bdTotalPurAmt(0), bdZero = DSTCommonFunctions::convertToBigDecimal(I_("0.0"));
	DString dstrPurAmt, dstrRedAmt;	
	
	getField(idFieldPur, dstrPurAmt, idDataGroup, false);
	dstrPurAmt.stripAll();	

	getField(idFieldRed, dstrRedAmt, idDataGroup, false);
	dstrRedAmt.stripAll();	

	bdPurAmt = DSTCommonFunctions::convertToBigDecimal(dstrPurAmt);
	bdRedAmt = DSTCommonFunctions::convertToBigDecimal(dstrRedAmt);
	
	bdTotalPurAmt = bdPurAmt + bdRedAmt; // (purchase + redemption)
			
	if (bdTotalPurAmt.abs() != bdZero)
	{
		if (bTransferIn)
			// populate purchase/received fields with a positive sign of the net balance 
			setFieldNoValidate(idFieldPur, bdTotalPurAmt.asDString(), idDataGroup, false, true, true, false);
		else
			// populate purchase/received fields with a negative sign of the net balance
			setFieldNoValidate(idFieldPur, (-bdTotalPurAmt).asDString(), idDataGroup, false, true, true, false);
	}
	else
		setFieldNoValidate(idFieldPur, I_("0.00"), idDataGroup, false, true, true, false);

	// populate redemption/paid out fields with zero 
	setFieldNoValidate(idFieldRed, I_("0.00"), idDataGroup, false, true, true, false);
	
	return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************************
SEVERITY RESPTransfer::doCalcPurRedNotionalAmt (const BFDataGroupId& idDataGroup, const BFFieldId &idFieldPur, const BFFieldId &idFieldRed, bool bTransferIn)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCalcPurRedNotionalAmt"));

	BigDecimal bdPurAmt(0), bdRedAmt(0), bdZero = DSTCommonFunctions::convertToBigDecimal(I_("0.0"));
	DString dstrPurAmt, dstrRedAmt;	
	
	getField(idFieldPur, dstrPurAmt, idDataGroup, false);
	dstrPurAmt.stripAll();
	if (dstrPurAmt != I_("")) 
	{		
		bdPurAmt = DSTCommonFunctions::convertToBigDecimal(dstrPurAmt);
		if (bdPurAmt.abs() != bdZero)
		{
			if (bTransferIn)
				// populate purchase/received fields with a positive sign 
				/*setFieldNoValidate(idFieldPur, bdPurAmt.asDString(), idDataGroup, false, true, true, false)*/;	
			else
				// populate purchase/received fields with a negative sign 
				setFieldNoValidate(idFieldPur, (-bdPurAmt).asDString(), idDataGroup, false, true, true, false);	
		}
	}

	getField(idFieldRed, dstrRedAmt, idDataGroup, false);
	dstrRedAmt.stripAll();
	if (dstrRedAmt != I_(""))
	{			
		bdRedAmt = DSTCommonFunctions::convertToBigDecimal(dstrRedAmt);
		if (bdRedAmt.abs() != bdZero)
		{
			if (bTransferIn)
				// populate redemption/paid out fields with a negative sign
				/*setFieldNoValidate(idFieldRed, bdRedAmt.asDString(), idDataGroup, false, true, true, false)*/;	
			else
				// populate redemption/paid out fields with a positive sign
				setFieldNoValidate(idFieldRed, (-bdRedAmt).asDString(), idDataGroup, false, true, true, false);	
		}
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************************
SEVERITY RESPTransfer::doCLBAmountChanges (const BFDataGroupId& idDataGroup, bool bSetValue)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCLBAmountChanges"));

	DString dstrRecordLevel;
	getField (ifds::RecordLevel, dstrRecordLevel, idDataGroup, false);

	if (dstrRecordLevel == RECORD_LEVEL::BENEFICIARY)
	{
		/*RESPTransferList *pRESPTransferList = dynamic_cast<RESPTransferList*>( getParent( ) );

		if (pRESPTransferList)
		{
			pRESPTransferList->setAccountCLBGrant (idDataGroup);		 
		}*/	

		setBeneficiaryCLBAmounts (idDataGroup, bSetValue);
	}	

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RESPTransfer::setBeneficiaryCLBAmounts (const BFDataGroupId &idDataGroup, bool bSetValue)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setBeneficiaryCLBAmounts" ) );


	DString depositType, redCode;

	RESPTransferList *pRESPTransferList = dynamic_cast<RESPTransferList*>( getParent( ) );

	if (pRESPTransferList)
	{
		pRESPTransferList->getField (ifds::DepositType, depositType, idDataGroup, false);
		pRESPTransferList->getField (ifds::RedCode, redCode, idDataGroup, false);

		bool bRespToResp = (depositType == I_("17") && (redCode == I_("64") || redCode == I_("65"))) ? true : false;

		if (!bRespToResp)
			return GETCURRENTHIGHESTSEVERITY();

		ErrMsgRulesList* pErrMsgRulesList = NULL;
		DString dstrCSSStopSINMatch;

		getWorkSession ().getMgmtCo().getErrMsgRulesList( pErrMsgRulesList );
		getWorkSession ().getOption (ifds::CSSStopSINMatch, dstrCSSStopSINMatch, idDataGroup, false);

		if (pErrMsgRulesList)
		{
			DString strErrValue;
			pErrMsgRulesList->getEWIValue (IFASTERR::CLB_AMOUNT_CANNOT_BE_TRANSFERED, idDataGroup, strErrValue );

			strErrValue.strip().upperCase();

			if (strErrValue == I_("E") && dstrCSSStopSINMatch == I_("Y"))
			{         
				bool bSameSIN = false;

				DString dstrBeneficiaryFrom, dstrBeneficiaryTo;

				getField (ifds::RESPBenefIDFrom, dstrBeneficiaryFrom, idDataGroup);
				getField (ifds::RESPBenefIDTo, dstrBeneficiaryTo, idDataGroup);
				dstrBeneficiaryFrom.stripLeading ('0');
				dstrBeneficiaryTo.stripLeading ('0');

				if (!(dstrBeneficiaryFrom.empty() || dstrBeneficiaryTo.empty()))
				{									
					isSameSIN (idDataGroup, bSameSIN);

					if (!bSameSIN && bSetValue)
					{
						setFieldNoValidate (ifds::CLBAmount, I_("0"), idDataGroup);
						setFieldNoValidate (ifds::RedCLB, I_("0"), idDataGroup);

						pRESPTransferList->setAccountCLBAmounts (idDataGroup);
					}

					setFieldReadOnly (ifds::CLBAmount, idDataGroup, !bSameSIN);
					setFieldReadOnly (ifds::RedCLB, idDataGroup, !bSameSIN);
				}
			}
		}
	}	

	return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************************
SEVERITY RESPTransfer::getTransferValidation (RESPTransferValidation *&pRESPTransferValidation,
                                              const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("getTransferValidation"));

   pRESPTransferValidation = NULL;

   DString	dstrTradeType,
      dstrTransId,
      dstrTransType,
      dstrDepositType,
      dstrRedCode,
      dstrAccountNum,
      dstrAccountTo,
      dstrTradeDate,
      dstrAmount,
      dstrRESPBenefName,
      dstrRESPBenefId,
      dstrNEQ1,
      dstrNEQ2,
	  dstrAcctLvlOverride;


   getField (ifds::RESPBenefIDFrom, dstrRESPBenefName, idDataGroup, true);
   getField (ifds::RESPBenefIDFrom, dstrRESPBenefId, idDataGroup, false);

   RESPTransferList *pRESPTransferList = dynamic_cast<RESPTransferList*>( getParent( ) );

   if (pRESPTransferList)
   {
      pRESPTransferList->getField (ifds::TradeType, dstrTradeType, idDataGroup);
      pRESPTransferList->getField (ifds::TransId, dstrTransId, idDataGroup);
      pRESPTransferList->getField (ifds::TransType, dstrTransType, idDataGroup);
      pRESPTransferList->getField (ifds::DepositType, dstrDepositType, idDataGroup);
      pRESPTransferList->getField (ifds::RedCode, dstrRedCode, idDataGroup);
      pRESPTransferList->getField (ifds::AccountNum, dstrAccountNum, idDataGroup);
      pRESPTransferList->getField (ifds::AccountTo, dstrAccountTo, idDataGroup);
      pRESPTransferList->getField (ifds::EffectiveDate, dstrTradeDate, idDataGroup);
      pRESPTransferList->getField (ifds::Amount, dstrAmount, idDataGroup);
      pRESPTransferList->getField (ifds::NEQ1, dstrNEQ1, idDataGroup);
      pRESPTransferList->getField (ifds::NEQ2, dstrNEQ2, idDataGroup);	
      pRESPTransferList->getField (ifds::AcctLvlOverride, dstrAcctLvlOverride, idDataGroup);
   }

   DString strKey;

   RESPTransferValidation::buildKey (dstrRESPBenefId,
                                     dstrTradeDate,
                                     dstrAmount,
                                     dstrNEQ1,
                                     dstrNEQ2,
                                     this,
                                     idDataGroup,
                                     strKey);

   pRESPTransferValidation =  dynamic_cast<RESPTransferValidation *> (BFCBO::getObject (strKey, idDataGroup));

   if (!pRESPTransferValidation)
   {
      pRESPTransferValidation = new RESPTransferValidation (*this);

      if (pRESPTransferValidation->init (CALL_TYPE_VALIDATION,
                                         dstrTradeType,
                                         dstrTransId,
                                         dstrTransType,
                                         dstrDepositType,
                                         dstrRedCode,
                                         dstrAccountNum,
                                         dstrAccountTo,
                                         dstrTradeDate,
                                         dstrAmount,
                                         dstrRESPBenefName,
                                         dstrNEQ1,
                                         dstrNEQ2,
										 dstrAcctLvlOverride,
                                         this,
                                         idDataGroup) <= WARNING)
      {
         setObject (pRESPTransferValidation, strKey, OBJ_ACTIVITY_NONE, idDataGroup);
      }
      else
      {
         delete pRESPTransferValidation;
         pRESPTransferValidation = NULL;
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//***********************************************************************************
SEVERITY RESPTransfer::validateBeneficiary ( const DString &dstrBenefId, 
                                             const BFDataGroupId &idDataGroup, 
                                             bool bFromAccount)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateBeneficiary"));

   DString benefId (dstrBenefId);

   benefId.stripLeading ('0');
   if (!benefId.empty())
   {
      RESPTransferList *pRESPTransferList = dynamic_cast<RESPTransferList*>( getParent( ) );

      if (pRESPTransferList)
      {
         // Duplicate check
         pRESPTransferList->checkDuplicate (this, idDataGroup);

         // is beneficiary effective:
         DString	dstrEffectiveDate,
            dstrTradeDate,
            dstrAccountNum;

         pRESPTransferList->getField (ifds::AccountNum, dstrAccountNum, idDataGroup, false);

         if (!bFromAccount)
         {
            pRESPTransferList->getField (ifds::AccountTo, dstrAccountNum, idDataGroup, false);
         }

         pRESPTransferList->getRESPEntityInfo ( dstrBenefId, 
                                                idDataGroup, 
                                                dstrAccountNum,
                                                dstrEffectiveDate); 	

         pRESPTransferList->getField (ifds::EffectiveDate, dstrTradeDate, idDataGroup);

         if (DSTCommonFunctions::CompareDates (dstrTradeDate, dstrEffectiveDate) == DSTCommonFunctions::FIRST_EARLIER)
         {
            DString idiStr = I_("");
            DString dstrBenName;

            if (bFromAccount)
            {
               getField( ifds::RESPBenefIDFrom, dstrBenName, idDataGroup, true );
            }
            else 
            {
               getField( ifds::RESPBenefIDTo, dstrBenName, idDataGroup, true );
            }
            addIDITagValue (idiStr, BENEF_NAME, dstrBenName );
            if (!dstrBenName.empty ())
            {
               ADDCONDITIONFROMFILEIDI (CND::ERR_BENEFICIARY_NOT_EFFECTIVE, idiStr);
            }
         }
  
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//***********************************************************************************
SEVERITY RESPTransfer::validateBeneficiary (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateBeneficiary"));

   RESPTransferValidation *pRESPTransferValidation (NULL);

   if (getTransferValidation (pRESPTransferValidation, idDataGroup) <= WARNING  && 
       pRESPTransferValidation)
   {
      pRESPTransferValidation->validateBeneficiary (idDataGroup);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//***********************************************************************************
SEVERITY RESPTransfer::validateFromToBeneficiary (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateFromToBeneficiary"));

   RESPTransferList *pRESPTransferList = dynamic_cast<RESPTransferList*>( getParent( ) );      

   if (pRESPTransferList)
   {
      DString transType;
      pRESPTransferList->getField (ifds::TransType, transType, idDataGroup, false);

      bool bInternalTransfer = pRESPTransferList->isInternalTransfer (idDataGroup);

      if (bInternalTransfer)
      {
         DString dstrFromBenefId;
         DString dstrToBenefId;
         DString dstrRecordLevel;

         getField (ifds::RESPBenefIDFrom, dstrFromBenefId, idDataGroup, false);
         getField (ifds::RESPBenefIDTo, dstrToBenefId, idDataGroup, false);
         getField (ifds::RecordLevel, dstrRecordLevel, idDataGroup, false);

         dstrToBenefId.stripLeading ('0');
         dstrFromBenefId.stripLeading ('0');
         dstrRecordLevel.stripAll ();

         if (dstrRecordLevel == RECORD_LEVEL::BENEFICIARY)
         {
            if (dstrFromBenefId.empty ())
            {
               ADDCONDITIONFROMFILE (CND::ERR_FROM_BENEF_IS_MISSING);
            }

            if (DSTCommonFunctions::codeInList (transType, TRANSFER_LIKE))
            {
               if (dstrToBenefId.empty ())
               {
                  ADDCONDITIONFROMFILE (CND::ERR_TO_BENEF_IS_MISSING);
               }
            }
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//***********************************************************************************
SEVERITY RESPTransfer::validateCLBGrant (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateCLBGrant"));

   DString dstrCLBAmount;

   getField (ifds::CLBAmount, dstrCLBAmount, idDataGroup);

   double dCLBAmount = DSTCommonFunctions::convertToDouble (dstrCLBAmount);

   if (dstrCLBAmount.empty () || dCLBAmount == 0)
      return GETCURRENTHIGHESTSEVERITY();

   RESPTransferList *pRESPTransferList = dynamic_cast<RESPTransferList*>( getParent( ) );      

   if (pRESPTransferList)
   {
      bool bInternalTransfer = pRESPTransferList->isInternalTransfer (idDataGroup);

      if (bInternalTransfer )
      {
         validateFromToSIN (idDataGroup);
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************************
SEVERITY RESPTransfer::doValidateAll (const BFDataGroupId &idDataGroup, 
                                      long lValidateGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateAll"));

   RESPTransferList *pRESPTransferList = dynamic_cast<RESPTransferList*>( getParent( ) );

   if (pRESPTransferList)
   {
      //if (pRESPTransferList->isAcctLevelOverrideApplicable (idDataGroup) || pRESPTransferList->isExternalTransferOut (idDataGroup))
      //{
         pRESPTransferList->totalGrants (idDataGroup);
      //}

	  if (isUpdatedForDataGroup ( idDataGroup, false ))
	  {
		  /* DString dstrIsResidualCESG, dstrRecordLevel;

		  getField(ifds::IsResidualCESG, dstrIsResidualCESG, idDataGroup, false);
		  dstrIsResidualCESG.strip().upperCase();

		  if (dstrIsResidualCESG == YES)
		  {
			  DString dstrCalUCAmt;

			  getField(ifds::UCAmt, dstrCalUCAmt, idDataGroup, false);
			  BigDecimal bdExistUCAmt, bdCalUCAmt (dstrCalUCAmt);

			  bdExistUCAmt = getUCAmtLTDForBenef(idDataGroup);

			  // make it to be absolute value for comparison and display.
			  bdCalUCAmt = bdCalUCAmt.abs();
			  dstrCalUCAmt = bdCalUCAmt.asDString();				  

			  if ( bdExistUCAmt < bdCalUCAmt )
			  {
				  DString idiDStr, dstrExistUCAmt (bdExistUCAmt.asDString());
				  BigDecimal bdZero(I_("0"));
				  int precision = 2, iPosE = 0, iPosC = 0;

				  iPosE = dstrExistUCAmt.find_first_of('.');
				  if (iPosE != DString::npos)
					  dstrExistUCAmt = dstrExistUCAmt.left(iPosE + precision + 1);
				  else if(dstrExistUCAmt == bdZero)
					  dstrExistUCAmt = I_("0.00");
				  
				  iPosC = dstrCalUCAmt.find_first_of('.');
				  if (iPosC != DString::npos)
					  dstrCalUCAmt = dstrCalUCAmt.left(iPosC + precision + 1);
				  else if(dstrCalUCAmt == bdZero)
					  dstrCalUCAmt = I_("0.00");

				  addIDITagValue( idiDStr, I_("UC_AMT"), dstrExistUCAmt );
				  addIDITagValue( idiDStr, I_("RES_AMT"), dstrCalUCAmt );

				  getErrMsg( IFASTERR::UC_AMT_LESS_THAN_RES_AMT, 
							 CND::ERR_UC_AMT_LESS_THAN_RES_AMT, 
							 CND::WARN_UC_AMT_LESS_THAN_RES_AMT, 
							 idDataGroup,
							 idiDStr );				  
			  }

		  }	       // if ResidualTrade
		  */

		  if ( isSAGESRelatedFieldsUpdated(idDataGroup) )
		  {
			  DString dstrAccountNum, siblingOnly, dstrDepositType, tradeDate, dstrSAGESDEff;
			  MFAccount *pMFAccount = NULL;
			  bool bSiblingOnly = false;

			  pRESPTransferList->getField (ifds::AccountNum, dstrAccountNum, idDataGroup, false);
			  pRESPTransferList->getField (ifds::DepositType, dstrDepositType, idDataGroup);
			  pRESPTransferList->getField (ifds::EffectiveDate, tradeDate, idDataGroup);

			  if (getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING && pMFAccount)
			  {
				  pMFAccount->getField (ifds::SiblingOnly, siblingOnly, idDataGroup, false);
				  if (siblingOnly == Y)
					  bSiblingOnly = true;

				  if ( bSiblingOnly && dstrDepositType == I_("17") ) 
				  {
					  getWorkSession().getOption (ifds::SAGESDeff, dstrSAGESDEff, BF::HOST, false);
					  dstrSAGESDEff.stripAll();
					  tradeDate.stripAll();

					  //Trade date must be equal or greater than 01Jan2013 (SAGES effective date)
					  if ( !dstrSAGESDEff.empty() && DSTCommonFunctions::CompareDates (tradeDate, dstrSAGESDEff) == DSTCommonFunctions::FIRST_EARLIER )
					  {
						  getErrMsg ( IFASTERR::TRADE_DATE_MUST_BE_EQUAL_OR_GREATER_THAN_SAGESDEFF, 
							  CND::ERR_TRADE_DATE_MUST_BE_EQUAL_OR_GREATER_THAN_SAGESDEFF, 
							  CND::WARN_TRADE_DATE_MUST_BE_EQUAL_OR_GREATER_THAN_SAGESDEFF, 
							  idDataGroup); 
					  }
				  }
			  }
		  }
	  }		// if updated for datagroup
   }

   validateBeneficiary (idDataGroup);
   validateCLBGrant (idDataGroup);
   validateTransferInNotionals (idDataGroup);

   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
BigDecimal RESPTransfer::getUCAmtLTDForBenef(const BFDataGroupId &idDataGroup)
{     

	/**************************************************************************************
	   Currently, we only implement to get the LTD notional and the value required is UCAmt.

	   Future modification, if required any other information or solution. We can make
	   a changes here according to future requirement.

	***************************************************************************************/
	RESPTransfer *pRESPTransferNotional (NULL);

	if (getRESPTransferNotional (pRESPTransferNotional, idDataGroup) <= WARNING && pRESPTransferNotional)
	{
		DString dstrUCAmt (I_("0"));
		pRESPTransferNotional->getField( ifds::UCAmt, dstrUCAmt, idDataGroup, false); 		  

		return DSTCommonFunctions::convertToBigDecimal (dstrUCAmt);
	}

	return 0;	
}
//******************************************************************************
SEVERITY RESPTransfer::getRESPTransferNotional (RESPTransfer *& pRESPTransfer, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getRESPTransferNotional" ) );

	/***************************************************************************************
	   The purpose is to reduce the time whenever the V409 get called.
	   We don't want to call v409 anytime for the validation or any situation. 
	   If any benef info get called, store it in the mapping by setObject.
	***************************************************************************************/
	// should always have a list.
    RESPTransferList *pRESPTransferList = dynamic_cast<RESPTransferList*>( getParent( ) );

	if (pRESPTransferList)
	{
		DString dstrKey, dstrBenefId;

		getField(ifds::RESPBenefIDFrom, dstrBenefId, idDataGroup, false);
		dstrKey = I_("NotionalBenef=") + dstrBenefId + I_(";");
		pRESPTransfer = dynamic_cast <RESPTransfer *>(getObject (dstrKey, idDataGroup));

		if (!pRESPTransfer)
		{
			BFData requestData (ifds::DSTC0409_REQ),
				*receivedData = new BFData (ifds::DSTC0409_VW);

			pRESPTransferList->populateRequestData (requestData, idDataGroup);			

			requestData.setElementValue (ifds::RESPBenefId, dstrBenefId);
			requestData.setElementValue (ifds::TransferPercent, I_("0"));
			requestData.setElementValue (ifds::RecordLevel, RECORD_LEVEL::BENEFICIARY);
			requestData.setElementValue (ifds::IsResidualCESG, YES);

			if (BFDataBroker::getInstance( )->receive( DSTC_REQUEST::RESP_TRANSFER_BENE_INQUIRY,
													   requestData, 
													   *receivedData, 
													   DSTCRequestor (getSecurity(), false, false), 
													   false) <= WARNING)
			{
				/* 
					set the Notional information to be child of the transfer, 
					to store it to memory, also it can avoid
				    process getting it to display.
				*/

                BFAbstractCBO& rThis = dynamic_cast<BFAbstractCBO&>(*this);
				pRESPTransfer = new RESPTransfer (rThis);

				if( pRESPTransfer->init (*receivedData, idDataGroup, false) <= WARNING )
				{
					setObject (pRESPTransfer, dstrKey,  OBJ_ACTIVITY_NONE, idDataGroup);
				}
				else 
				{
					delete pRESPTransfer;
					pRESPTransfer = NULL;
				}
			}
		}
	}

   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY RESPTransfer::validateTransferPercent (const DString &dstrTransferPercent, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateTransferPercent" ) );

   double dec_percent = DSTCommonFunctions::convertToDouble (dstrTransferPercent);

   if (dec_percent < 0 - dSmallValue || dec_percent > 100 + dSmallValue)
   {
      ADDCONDITIONFROMFILE (CND::ERR_VALUE_BETWEEN_0_AND_100);
   }

   DString dstrRecordLevel;
   getField (ifds::RecordLevel, dstrRecordLevel, idDataGroup, false);

   if ( dstrRecordLevel == RECORD_LEVEL::BENEFICIARY )
   {
      if( !isFieldReadOnly( ifds::TransferPercent, idDataGroup ) && 
           isFieldUpdated( ifds::TransferPercent, idDataGroup )) // field is dirty
      {
         // TransferPercent is in 'updated' state after calling view 409
         ADDCONDITIONFROMFILE( CND::WARN_ELIGIBLE_TRANSFER_FLAG_CHANGED );
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RESPTransfer::validateFromToSIN (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateFromToSIN"));

   DString dstrBeneficiaryFrom;
   DString dstrBeneficiaryTo;
   DString dstrCSSStopSINMatch;

   getField (ifds::RESPBenefIDFrom, dstrBeneficiaryFrom, idDataGroup);
   getField (ifds::RESPBenefIDTo, dstrBeneficiaryTo, idDataGroup);

   dstrBeneficiaryFrom.stripLeading ('0');
   dstrBeneficiaryTo.stripLeading ('0');

   getWorkSession ().getOption (ifds::CSSStopSINMatch, dstrCSSStopSINMatch, idDataGroup, false);

   if (dstrCSSStopSINMatch == I_("N") || 
      (dstrBeneficiaryFrom.empty () || dstrBeneficiaryTo.empty ()))
      return GETCURRENTHIGHESTSEVERITY();

   DString dstrBenefFromSIN = NULL_STRING;
   DString dstrBenefToSIN = NULL_STRING;
   Entity *pFromEntity = NULL;
   Entity *pToEntity = NULL;

   SEVERITY fromSEVERITY = getWorkSession().getEntity (idDataGroup, dstrBeneficiaryFrom, pFromEntity);
   SEVERITY toSEVERITY = getWorkSession().getEntity (idDataGroup, dstrBeneficiaryTo, pToEntity);

   if (fromSEVERITY <= WARNING && pFromEntity && toSEVERITY <= WARNING && pToEntity)
   {
      EntityIdsList *pFromEntityIdsList = NULL; 
      EntityIdsList *pToEntityIdsList = NULL;

      if (pFromEntity->getEntityIdsList (pFromEntityIdsList, idDataGroup) <= WARNING &&
         pFromEntityIdsList)
      {
         getSIN (dstrBenefFromSIN, pFromEntityIdsList, idDataGroup);
      }

      if (pToEntity->getEntityIdsList (pToEntityIdsList, idDataGroup) <= WARNING &&
         pToEntityIdsList)
      {
         getSIN (dstrBenefToSIN, pToEntityIdsList, idDataGroup);
      }
   }

   if (dstrBenefFromSIN != dstrBenefToSIN)
   {
      getErrMsg (IFASTERR::CLB_AMOUNT_CANNOT_BE_TRANSFERED, 
                 CND::ERR_CLB_AMOUNT_CANNOT_BE_TRANSFERED, 
                 CND::WARN_CLB_AMOUNT_CANNOT_BE_TRANSFERED, 
                 idDataGroup);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RESPTransfer::isSameSIN (const BFDataGroupId &idDataGroup, bool &bSameSIN)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("isSameSIN"));

   bSameSIN = false;
   DString dstrBeneficiaryFrom;
   DString dstrBeneficiaryTo;
   DString dstrCSSStopSINMatch;

   getField (ifds::RESPBenefIDFrom, dstrBeneficiaryFrom, idDataGroup);
   getField (ifds::RESPBenefIDTo, dstrBeneficiaryTo, idDataGroup);


   DString dstrBenefFromSIN = NULL_STRING;
   DString dstrBenefToSIN = NULL_STRING;
   Entity *pFromEntity = NULL;
   Entity *pToEntity = NULL;

   SEVERITY fromSEVERITY = getWorkSession().getEntity (idDataGroup, dstrBeneficiaryFrom, pFromEntity);
   SEVERITY toSEVERITY = getWorkSession().getEntity (idDataGroup, dstrBeneficiaryTo, pToEntity);

   if (fromSEVERITY <= WARNING && pFromEntity && toSEVERITY <= WARNING && pToEntity)
   {
      EntityIdsList *pFromEntityIdsList = NULL; 
      EntityIdsList *pToEntityIdsList = NULL;

      if (pFromEntity->getEntityIdsList (pFromEntityIdsList, idDataGroup) <= WARNING &&
         pFromEntityIdsList)
      {
         getSIN (dstrBenefFromSIN, pFromEntityIdsList, idDataGroup);
      }

      if (pToEntity->getEntityIdsList (pToEntityIdsList, idDataGroup) <= WARNING &&
         pToEntityIdsList)
      {
         getSIN (dstrBenefToSIN, pToEntityIdsList, idDataGroup);
      }
   }

   bSameSIN = dstrBenefFromSIN == dstrBenefToSIN ? true : false;

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RESPTransfer::getSIN (DString &dstrSIN, 
                               EntityIdsList *&pEntityIdsList,
                               const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getSIN"));

   BFObjIter iter (*pEntityIdsList, idDataGroup);

   while (!iter.end())
   {
      DString idType;

      iter.getObject()->getField (ifds::IdType, idType, idDataGroup);

      if (idType == SIN)
      {
         iter.getObject()->getField (ifds::IdValue, dstrSIN, idDataGroup);
         break;
      }

      ++iter;
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool RESPTransfer::isRESPRelatedFieldsUpdated(const BFDataGroupId &idDataGroup)
{
   if( isFieldUpdated (ifds::QESIACAmount, idDataGroup) ||
       isFieldUpdated (ifds::QESIUCAmount, idDataGroup) ||
       isFieldUpdated (ifds::QESIYTDContribution, idDataGroup) ||
       isFieldUpdated (ifds::EligibleTransfer, idDataGroup) ||
       isFieldUpdated (ifds::QESIBasicGrant, idDataGroup) ||
       isFieldUpdated (ifds::QESIIncreaseAmt, idDataGroup) ||
       isFieldUpdated (ifds::HistNonTrustYear, idDataGroup) ||
       isFieldUpdated (ifds::TotTransfINDC, idDataGroup))
   {
      return true;
   }

   return false;
}
//******************************************************************************
SEVERITY RESPTransfer::loadNotionalYearList(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("loadNotionalYearList"));

   DString dstrNonTrustStartDate(NULL_STRING), dstrNonTrustStopDate(NULL_STRING);

   getWorkSession().getOption (ifds::NonTrustStartDate, dstrNonTrustStartDate, BF::HOST, false);
   getWorkSession().getOption (ifds::NonTrustStopDate, dstrNonTrustStopDate, BF::HOST, false);

   DString dstrNotionalYearList(NULL_STRING);
   DString dstrYear(NULL_STRING);	

   int nStartYear = 2007; // start year of Non-QESI Trustee requirement
   int nStopYear = 2007;

   //if( !dstrNonTrustStartDate.strip().empty() )
   //{
   //   nStartYear = DSTCommonFunctions::getYearFromUnFormattedDate( dstrNonTrustStartDate );
   //}
   
   if( !dstrNonTrustStopDate.strip().empty() )
   {
      nStopYear = DSTCommonFunctions::getYearFromUnFormattedDate( dstrNonTrustStopDate );
   }

   for(int i=nStartYear; i <= nStopYear; i++)
   {
      convertIntToString( i, dstrYear );
      dstrNotionalYearList += dstrYear + I_('=') + dstrYear + I_(';');
   }

   if( !dstrNotionalYearList.empty() )
   {
      setFieldAllSubstituteValues (ifds::HistNonTrustYear, idDataGroup, dstrNotionalYearList );
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void RESPTransfer::getStrKey( DString &strKey, const BFData *data )
{
   unsigned int iCurrentCounter = RESPTransfer::getCurrentCounter();
   strKey = DString::asString( iCurrentCounter ).padLeft( 10, '0' );
   RESPTransfer::incCurrentCounter();
}

//*****************************************************************************************
SEVERITY RESPTransfer::clearFieldsForNonTrusteeTxfrGrants ( const BFDataGroupId& idDataGroup)
{

   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "clearFieldsForNonTrusteeTxfrGrants"));

   if (isNew())
   {
	   DString strValue(I_("0"));

	   setFieldNoValidate (ifds::YTDContr, strValue, idDataGroup, true);
	   setFieldNoValidate (ifds::TDContr, strValue, idDataGroup, true);
	   setFieldNoValidate (ifds::GrantAmount, strValue, idDataGroup, true);
	   setFieldNoValidate (ifds::AdditionalGrant, strValue, idDataGroup, true);
	   setFieldNoValidate (ifds::CLBAmount, strValue, idDataGroup, true);
	   setFieldNoValidate (ifds::PGrantAmount, strValue, idDataGroup, true);
	   setFieldNoValidate (ifds::TDRedContrib, strValue, idDataGroup, true);
	   setFieldNoValidate (ifds::TDRedEarning, strValue, idDataGroup, true);
	   setFieldNoValidate (ifds::RedCESG, strValue, idDataGroup, true);
	   setFieldNoValidate (ifds::RedCLB, strValue, idDataGroup, true);
	   setFieldNoValidate (ifds::RedPGrant, strValue, idDataGroup, true);
	   setFieldNoValidate (ifds::UCAmt, strValue, idDataGroup, true);
	   setFieldNoValidate (ifds::ACAmt, strValue, idDataGroup, true);
	   setFieldNoValidate (ifds::Pre98ContribAmt, strValue, idDataGroup, true);
	   setFieldNoValidate (ifds::Pre98RedContribAmt, strValue, idDataGroup, true);
	   setFieldNoValidate (ifds::QESIUCAmount, strValue, idDataGroup, true);
	   setFieldNoValidate (ifds::QESIACAmount, strValue, idDataGroup, true);
	   setFieldNoValidate (ifds::CESGPaid, strValue, idDataGroup, true); //P0185010.FN02.R01.02 - CESG Grant paid

	   setFieldNoValidate (ifds::QESIBasicGrant, strValue, idDataGroup, true);
	   setFieldNoValidate (ifds::QESIIncreaseAmt, strValue, idDataGroup, true);
	   setFieldNoValidate (ifds::Pre98QESIContrib, strValue, idDataGroup, true);
	   setFieldNoValidate (ifds::Pre2007QESIContrib, strValue, idDataGroup, true);

	   setFieldNoValidate (ifds::QESIYTDContribution, strValue, idDataGroup, false); 

	   setFieldNoValidate (ifds::SAGESGrant, strValue, idDataGroup, false); 
	   setFieldNoValidate (ifds::SAGESUCAmount, strValue, idDataGroup, false); 
	   setFieldNoValidate (ifds::SAGESACAmount, strValue, idDataGroup, false); 

	   setFieldNoValidate (ifds::BCTESGGrant, I_(""), idDataGroup, false);

	   setFieldNoValidate (ifds::UCRedAmt, strValue, idDataGroup, false);
	   setFieldNoValidate (ifds::ACRedAmt, strValue, idDataGroup, false);
	   setFieldNoValidate (ifds::SAGESRedUCAmt, strValue, idDataGroup, false);
	   setFieldNoValidate (ifds::SAGESRedACAmt, strValue, idDataGroup, false);
	   setFieldNoValidate (ifds::QESIRedUCAmt, strValue, idDataGroup, false);
	   setFieldNoValidate (ifds::QESIRedACAmt, strValue, idDataGroup, false);
	   setFieldNoValidate (ifds::QESIRedYTDContrib, strValue, idDataGroup, false);	 
	   setFieldNoValidate (ifds::Pre2007QESIRedContrib, strValue, idDataGroup, false);
	   setFieldNoValidate (ifds::RedAdditionalGrant, strValue, idDataGroup, false);
	   setFieldNoValidate (ifds::RedSAGES, strValue, idDataGroup, false);
	   setFieldNoValidate (ifds::QESIRedBasic, strValue, idDataGroup, false);
	   setFieldNoValidate (ifds::QESIRedIncrease, strValue, idDataGroup, false);
	   setFieldNoValidate (ifds::RedBCTESG, strValue, idDataGroup, false); 
   }

   return GETCURRENTHIGHESTSEVERITY();
}
//*****************************************************************************************
SEVERITY RESPTransfer::resetFieldsForNonTrusteeTxfrGrants ( const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "resetFieldsForNonTrusteeTxfrGrants"));

   DString strNEQ1(NULL_STRING);
   RESPTransferList *pRESPTransferList = dynamic_cast<RESPTransferList*>( getParent( ) );      

   if (pRESPTransferList)
   {
      pRESPTransferList->getField( ifds::NEQ1, strNEQ1, idDataGroup, false );
      strNEQ1.stripAll().upperCase();
   }

   bool bIsNonTrustee = strNEQ1 == I_("0")? true : false;


   DString isNotionalTaxYearApplicable;
   getField (ifds::IsNotionalTaxYearApplicable, isNotionalTaxYearApplicable, idDataGroup, false);

   if(bIsNonTrustee) //trustee -> nontrustee
   {
      
      if(isNotionalTaxYearApplicable == YES)  
      {
         if(m_bInitNewLoaded || m_bReset)
         {
            setFieldNoValidate (ifds::HistNonTrustYear, m_dstrTradeYear, idDataGroup, false, false, true, true); 
            clearFieldsForNonTrusteeTxfrGrants(idDataGroup);
         }
      }
      else
      {
         if(m_bInitNewLoaded || m_bReset)//Not set if existing trade
         {
            setFieldNoValidate (ifds::HistNonTrustYear, m_dstrTradeYear, idDataGroup, false, false, true, true); 			
            m_bReset = true; // for new trade
         }
      }
      m_bIsNonTrusteeLoaded = true;
   }
   else // nontrustee -> trustee
   {
      if(m_bIsNonTrusteeLoaded) // only reset if nontrus to trus
      {
         setFieldNoValidate (ifds::HistNonTrustYear, m_dstrTradeYear, idDataGroup, true, false, true, false); 

         //setFieldNoValidate (ifds::EligibleTransfer, NO, idDataGroup, false, false, true, false); 
         setFieldNoValidate (ifds::TotTransfINDC, I_(""), idDataGroup, true, false, true, false);
         clearFieldsForNonTrusteeTxfrGrants(idDataGroup);
      }
      m_bIsNonTrusteeLoaded = false;
   }


   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RESPTransfer::initNonTrusteeTxfrFields(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initNonTrusteeTxfrFields"));

   DString dstrRecordLevel;
   bool bIsNonTrustee(false);

   getField (ifds::RecordLevel, dstrRecordLevel, idDataGroup, false);

   RESPTransferList *pRESPTransferList = dynamic_cast<RESPTransferList*>( getParent( ) );      

   if (pRESPTransferList)
   {
      bIsNonTrustee = pRESPTransferList->isNonTrustee(idDataGroup);
   }


   if( bIsNonTrustee)
   {
      if (dstrRecordLevel == RECORD_LEVEL::BENEFICIARY)
      { 
         setFieldNoValidate (ifds::HistNonTrustYear, m_dstrTradeYear, idDataGroup, false, false, true, false);
         setFieldReadOnly (ifds::HistNonTrustYear, idDataGroup, false);   

      }
      else if(dstrRecordLevel == RECORD_LEVEL::ACCOUNT)
      {
         setFieldNoValidate (ifds::TotTransfINDC, I_(""), idDataGroup, true); 
         setFieldNoValidate (ifds::HistNonTrustYear, m_dstrTradeYear, idDataGroup, false, false, true, false);
         setFieldReadOnly (ifds::TotTransfINDC, idDataGroup, true);		   
         setFieldReadOnly (ifds::HistNonTrustYear, idDataGroup, true);
      }
   }
   else//!bIsNonTrustee
   {
      setFieldNoValidate (ifds::HistNonTrustYear, m_dstrTradeYear, idDataGroup, true, false, true, false);
      setFieldReadOnly (ifds::TotTransfINDC, idDataGroup, true);		   
      setFieldReadOnly (ifds::HistNonTrustYear, idDataGroup, true);
   }


   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RESPTransfer::doTotTransfINDCRelatedChanges(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doTotTransfINDCRelatedChanges"));

   DString strIsTotTransfINDCApplic;
   DString strTotTransfINDC;
   DString strEligibleTransfer;

   getField( ifds::IsTotTransfINDCApplicable, strIsTotTransfINDCApplic, idDataGroup, false );
   getField( ifds::EligibleTransfer, strEligibleTransfer, idDataGroup, false );
   getField( ifds::TotTransfINDC, strTotTransfINDC, idDataGroup, false );

   bool bIsNotionalTaxYearApplicable = 
      strIsTotTransfINDCApplic == YES && 
      strTotTransfINDC.strip().upperCase() == I_("1") && 
      strEligibleTransfer == YES;

   setFieldNoValidate( ifds::IsNotionalTaxYearApplicable,
      bIsNotionalTaxYearApplicable ? YES: NO, idDataGroup, false);

   setFieldValid( ifds::IsNotionalTaxYearApplicable, idDataGroup, true);
   setFieldUpdated( ifds::IsNotionalTaxYearApplicable, idDataGroup,false );
   

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RESPTransfer::doNEQ1RelatedChanges(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doNEQ1RelatedChanges"));

   DString strIsNonTrustee(NULL_STRING);
   DString strHistYear(NULL_STRING);
   bool bIsNonTrustee(false);

   getWorkSession ().getOption (ifds::IsNonTrustee, strIsNonTrustee, idDataGroup, false);
   
   bool bTradeYearApplicable = isInHistoricalRESPPeriod(idDataGroup);
   bool bIsNonTrusteeFunctionApplicable = strIsNonTrustee ==I_("Y")? true:false;
  
   RESPTransferList *pRESPTransferList = dynamic_cast<RESPTransferList*>( getParent( ) );      
   DString NEQ1(NULL_STRING);
   DString dstrRecordLevel(NULL_STRING);
   DString dstrTradeType(NULL_STRING);
   getField (ifds::RecordLevel, dstrRecordLevel, idDataGroup, false);
   
   if (pRESPTransferList)
   {
      bIsNonTrustee = pRESPTransferList->isNonTrustee(idDataGroup); 
      //For New trade, NEQ1 sent from Vew406 is BLANK
      //this fix Trade Entry ACCT LVL vew406 sends BLANK for new trade
      if(dstrRecordLevel == RECORD_LEVEL::ACCOUNT)
      {
         pRESPTransferList->getField (ifds::NEQ1, NEQ1, idDataGroup, false);
         pRESPTransferList->getField (ifds::TradeType, dstrTradeType, idDataGroup, false);
         if(dstrTradeType == NEW &&
            bTradeYearApplicable &&
            bIsNonTrusteeFunctionApplicable &&
            (NEQ1 == I_("")))
         {
            bIsNonTrustee = true;

         }
      }
   }

   
   if( bIsNonTrustee &&  
       bTradeYearApplicable && 
       bIsNonTrusteeFunctionApplicable )
   {
      setFieldNoValidate( ifds::IsTotTransfINDCApplicable,
         I_("Y"), 
         idDataGroup, false );
      //setFieldValid (ifds::TotTransfINDC, idDataGroup, false);
   }
   else
   {
      setFieldNoValidate( ifds::IsTotTransfINDCApplicable,
         I_("N"), 
         idDataGroup, false );
      //setFieldValid (ifds::TotTransfINDC, idDataGroup, true); 
   }

   setFieldValid( ifds::IsTotTransfINDCApplicable, idDataGroup, true);
   setFieldUpdated( ifds::IsTotTransfINDCApplicable, idDataGroup,false );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool RESPTransfer::isInHistoricalRESPPeriod(const BFDataGroupId& idDataGroup)
{
   DString strStartHistDate,
      strStopHistDate,
      strEffectiveDate;

   RESPTransferList *pRESPTransferList = dynamic_cast<RESPTransferList*>( getParent( ) ); 

   bool bReturn = false;

   if (pRESPTransferList)
   {
      pRESPTransferList->getField( ifds::EffectiveDate, strEffectiveDate, idDataGroup, false );
      getWorkSession ().getOption (ifds::NonTrustStartDate, strStartHistDate, idDataGroup, false);
      getWorkSession ().getOption (ifds::NonTrustStopDate, strStopHistDate, idDataGroup, false);

      bReturn  = DSTCommonFunctions::IsDateBetween( strStartHistDate, 
                                                    strStopHistDate, 
                                                    strEffectiveDate);
   }
   else
   {
      bReturn = false;
   }

   return bReturn;
}

//******************************************************************************
SEVERITY RESPTransfer::getEffectiveYear(DString& strEffectiveYear,const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getEffectiveYear"));

   RESPTransferList *pRESPTransferList = dynamic_cast<RESPTransferList*>( getParent( ) ); 

   if( pRESPTransferList )
   {
      DString strEffectiveDate;
      pRESPTransferList->getField( ifds::EffectiveDate, strEffectiveDate, idDataGroup, false);

      int year_pos = DSTCommonFunctions::getYearPosition();
      strEffectiveYear.assign(strEffectiveDate,year_pos,4);
   }

   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY RESPTransfer::doEligibleTransferRelatedChanges(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doEligibleTransferRelatedChanges"));

   //IN#2591262 - the transfer beneficiary of record 2011 is mandatory
   DString strEligibleTransfer(NULL_STRING);
   DString dstrRecordLevel;

   getField (ifds::RecordLevel, dstrRecordLevel, idDataGroup, false);

   getField( ifds::EligibleTransfer, strEligibleTransfer, idDataGroup, false );
   strEligibleTransfer.stripAll();


   if (dstrRecordLevel == RECORD_LEVEL::BENEFICIARY)
   {
      if(strEligibleTransfer == YES) //when copy from currTradeYear BENEF
      {
         if(isNew())
         {
            setFieldNoValidate (ifds::TotTransfINDC, I_(""), idDataGroup, false, false, true, false); 
         }
         setFieldReadOnly (ifds::TotTransfINDC, idDataGroup, false);
      }
      else // default 'N'
      {
         if(isNew())
         {
            setFieldNoValidate (ifds::TotTransfINDC, I_(""), idDataGroup, true, false, true, false); 
         }
         setFieldReadOnly (ifds::TotTransfINDC, idDataGroup, true);
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY RESPTransfer::checkHistoricalTrade(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "checkHistoricalTrade"));

   RESPTransferList *pRESPTransferList = dynamic_cast<RESPTransferList*>( getParent( ) );

   if(pRESPTransferList)
   {
      if( pRESPTransferList->checkContribution(this,idDataGroup, false) )
      {
         ADDCONDITIONFROMFILE (CND::ERR_DEL_HIST_TXFR_BENEF_RECORD);  
         return GETCURRENTHIGHESTSEVERITY();        
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY RESPTransfer::initClone (const BFData& data, const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("initClone"));

   //attachDataObject (const_cast<BFData&>(data), false, true );
   setDataNoValidate(data,idDataGroup,true);
   
   for ( int i = 0; i < NUM_FIELDS; i++ )
   {
      setFieldUpdated( classFieldInfo[i].m_fieldId,idDataGroup,true );
      i++;
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//***********************************************************************************
SEVERITY RESPTransfer::validateSAGESACAmount (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateSAGESACAmount"));

	//Validates SAGES Assisted Contribution Amount and raises a warning when SAGES amount is entered but SAGES Assisted Contribution is left zero.

	DString dstrSAGESGrant, dstrSAGESACAmount;
	getField (ifds::SAGESGrant, dstrSAGESGrant, idDataGroup, false);
	getField (ifds::SAGESACAmount, dstrSAGESACAmount, idDataGroup, false);
	dstrSAGESGrant.strip();
	dstrSAGESACAmount.strip();
	
	BigDecimal bdSAGESGrant = DSTCommonFunctions::convertToBigDecimal(dstrSAGESGrant);  
	BigDecimal bdSAGESACAmount = DSTCommonFunctions::convertToBigDecimal(dstrSAGESACAmount);  
	BigDecimal bdZero = DSTCommonFunctions::convertToBigDecimal(I_("0.0"));
	
	if (bdSAGESGrant > 0 && bdSAGESACAmount == bdZero) 
	{
		getErrMsg( IFASTERR::SAGES_ASSISTED_CONTRIBUTION_AMOUNT_IS_ZERO, 
				   CND::ERR_SAGES_ASSISTED_CONTRIBUTION_AMOUNT_IS_ZERO, 
				   CND::WARN_SAGES_ASSISTED_CONTRIBUTION_AMOUNT_IS_ZERO, 
				   idDataGroup);
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool RESPTransfer::isSAGESRelatedFieldsUpdated(const BFDataGroupId &idDataGroup)
{
   if( isFieldUpdated (ifds::SAGESGrant, idDataGroup) ||
       isFieldUpdated (ifds::SAGESUCAmount, idDataGroup) ||
       isFieldUpdated (ifds::SAGESACAmount, idDataGroup) )
   {
      return true;
   }

   return false;
}

//***********************************************************************************
SEVERITY RESPTransfer::validateTransferInNotionals (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateTransferInNotionals"));

	bool bIsRespTransformation = getWorkSession().isRESPTransformationClient ();

	DString dstrRecordLevel;
	getField (ifds::RecordLevel, dstrRecordLevel, idDataGroup);

	if (bIsRespTransformation && dstrRecordLevel == RECORD_LEVEL::BENEFICIARY)		
	{
		DString dstrTransType, dstrDepositType, dstrCESGPaid, dstrRedCode, dstrTradeType;

		RESPTransferList *pRESPTransferList = dynamic_cast<RESPTransferList*>( getParent( ) );
		if (pRESPTransferList)
		{			
			pRESPTransferList->getField (ifds::TransType, dstrTransType, idDataGroup);
			pRESPTransferList->getField (ifds::DepositType, dstrDepositType, idDataGroup);
			pRESPTransferList->getField (ifds::RedCode, dstrRedCode, idDataGroup);
			pRESPTransferList->getField (ifds::TradeType, dstrTradeType, idDataGroup);	

			// if the transaction is a RESP Transfer-In, the redemption/ paid out columns can only be negative 
			// with the exception of CESG By Other Institution (CESGPaid) and QESI By Other Institution (QESIPaid) which are always positive for transfer in/out
			if ( (dstrTransType == I_("ED") && dstrDepositType == I_("17")) || (DSTCommonFunctions::codeInList(dstrTransType, I_("AFTR,TR,TI")) && dstrDepositType == I_("17") && DSTCommonFunctions::codeInList(dstrRedCode, I_("01,25,27"))) )
			{
				// stop the user from entering positive values in the redemption and paid out columns
				validateTransferInNotionalAmt (idDataGroup, ifds::TDRedContrib); // Life to Date Contribution - Redemption
				validateTransferInNotionalAmt (idDataGroup, ifds::Pre98RedContribAmt); // Pre-1998 Contribution - Redemption
				validateTransferInNotionalAmt (idDataGroup, ifds::UCRedAmt); // CESG Unassisted - Redemption
				validateTransferInNotionalAmt (idDataGroup, ifds::ACRedAmt); // CESG Assisted - Redemption
				validateTransferInNotionalAmt (idDataGroup, ifds::SAGESRedUCAmt); // SAGES Unassisted - Redemption	
				validateTransferInNotionalAmt (idDataGroup, ifds::SAGESRedACAmt); // SAGES Assisted - Redemption
				validateTransferInNotionalAmt (idDataGroup, ifds::QESIRedYTDContrib); // QESI YTD - Redemption
				validateTransferInNotionalAmt (idDataGroup, ifds::QESIRedACAmt); // QESI Assisted - Redemption
				validateTransferInNotionalAmt (idDataGroup, ifds::QESIRedUCAmt); // QESI Unassisted - Redemption				
				//validateTransferInNotionalAmt (idDataGroup, ifds::Pre2007QESIRedContrib); // QESI Pre-Feb 21, 2007 - Redemption

				validateTransferInNotionalAmt (idDataGroup, ifds::RedCESG); // CESG - Paid Out
				validateTransferInNotionalAmt (idDataGroup, ifds::RedAdditionalGrant); // Additional CESG - Paid Out				
				validateTransferInNotionalAmt (idDataGroup, ifds::RedCLB); // CLB - Paid Out
				validateTransferInNotionalAmt (idDataGroup, ifds::RedSAGES); // SAGES - Paid Out
				validateTransferInNotionalAmt (idDataGroup, ifds::RedBCTESG); // BCTESG - Paid Out	
				validateTransferInNotionalAmt (idDataGroup, ifds::RedPGrant); // ACES - Paid Out
				validateTransferInNotionalAmt (idDataGroup, ifds::QESIRedBasic); // QESI Basic - Paid Out	
				validateTransferInNotionalAmt (idDataGroup, ifds::QESIRedIncrease); // QESI Increase - Paid Out				
			}

			validateTransferInNotionalAmt (idDataGroup, ifds::CESGPaid, dstrTradeType); // CESG By Other Institution
			validateTransferInNotionalAmt (idDataGroup, ifds::QESIPaid, dstrTradeType); // QESI By Other Institution
		}
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//***********************************************************************************
SEVERITY RESPTransfer::validateTransferInNotionalAmt (const BFDataGroupId &idDataGroup, const BFFieldId &idField)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateTransferInNotionalAmt"));

	DString dstrNotionalAmt;
	getField (idField, dstrNotionalAmt, idDataGroup, false);  
	dstrNotionalAmt.strip();

	BigDecimal bdNotionalAmt = DSTCommonFunctions::convertToBigDecimal(dstrNotionalAmt);  
	BigDecimal bdZero = DSTCommonFunctions::convertToBigDecimal(I_("0.0"));

	if ( bdNotionalAmt > bdZero ) 
	{	
		// 1759 - Enter amounts with negative sign (-) on redemption and paid out column.
		getErrMsg( IFASTERR::NOTIONAL_AMOUNTS_MUST_BE_NEGATIVE, 
				   CND::ERR_NOTIONAL_AMOUNTS_MUST_BE_NEGATIVE, 
				   CND::WARN_NOTIONAL_AMOUNTS_MUST_BE_NEGATIVE, 
				   idDataGroup); 
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************************
SEVERITY RESPTransfer::doCalcQESIPre2007Amt (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCalcQESIPre2007Amt"));
   
   if ( !(getWorkSession().isRESPTransformationClient () && getWorkSession().isQESIClient()) )
         return GETCURRENTHIGHESTSEVERITY(); 

   BigDecimal bdPurLTDAmt(0), bdRedLTDAmt(0), bdQESIACAmt(0),  bdQESIRedACAmt(0), bdQESIUCAmt(0), bdQESIRedUCAmt(0), bdQESIYTDAmt(0), bdQESIRedYTDAmt(0), bdPre2007QESIContribAmt(0);
   DString dstrRecordLevel, dstrAccountLevelOverride, dstPurLTDAmt, dstrRedLTDAmt, dstQESIACAmt, dstrQESIRedACAmt, dstrQESIUCAmt, dstrQESIRedUCAmt, dstrQESIYTDAmt, dstrQESIRedYTDAmt, dstrPre2007QESIContribAmt;

   RESPTransferList *pRESPTransferList = dynamic_cast<RESPTransferList*>( getParent( ) );
   if (pRESPTransferList)
   {				   
	   pRESPTransferList->getField (ifds::AcctLvlOverride, dstrAccountLevelOverride, idDataGroup, false);
	   getField (ifds::RecordLevel, dstrRecordLevel, idDataGroup, false);
	   dstrRecordLevel.stripAll ();

	   if (dstrRecordLevel == RECORD_LEVEL::BENEFICIARY && dstrAccountLevelOverride == YES)
	   {	
		   DString dstrAccountFrom, dstrFromBenefId, dstrTaxJuris, dstrEff, dstrAllocPrnt, dstrHRDC, dstrDOB;
		   MFAccount *pMFAccount = NULL;

		   pRESPTransferList->getField(ifds::AccountNum, dstrAccountFrom, idDataGroup, false);
		   dstrAccountFrom.stripLeading('0');

		   getField(ifds::RESPBenefIDFrom, dstrFromBenefId, idDataGroup, false);
		   dstrFromBenefId.stripLeading('0');
		   
		   if (getWorkSession().getMFAccount(idDataGroup, dstrAccountFrom, pMFAccount) <= WARNING && pMFAccount)
		   {			 			 
			   pRESPTransferList->getRESPEntityInfo( dstrFromBenefId, 
													 idDataGroup, 
													 dstrAccountFrom, 
													 dstrEff, 
													 dstrAllocPrnt, 
													 dstrTaxJuris, 
													 dstrHRDC, 
													 dstrDOB);
       
			   if (dstrTaxJuris == I_("0006")) // Quebec
			   {
				   // Life to Date Contribution
				   getField(ifds::TDContr, dstPurLTDAmt, idDataGroup, false);
				   getField(ifds::TDRedContrib, dstrRedLTDAmt, idDataGroup, false);	
				   bdPurLTDAmt = bdPurLTDAmt + DSTCommonFunctions::convertToBigDecimal(dstPurLTDAmt.stripAll());
				   bdRedLTDAmt = bdRedLTDAmt + DSTCommonFunctions::convertToBigDecimal(dstrRedLTDAmt.stripAll());

				   // QESI AC, QESI UC, QESI YTD. 
				   getField(ifds::QESIACAmount, dstQESIACAmt, idDataGroup, false);
				   getField(ifds::QESIRedACAmt, dstrQESIRedACAmt, idDataGroup, false);
				   getField(ifds::QESIUCAmount, dstrQESIUCAmt, idDataGroup, false);
				   getField(ifds::QESIRedUCAmt, dstrQESIRedUCAmt, idDataGroup, false);
				   getField(ifds::QESIYTDContribution, dstrQESIYTDAmt, idDataGroup, false);
				   getField(ifds::QESIRedYTDContrib, dstrQESIRedYTDAmt, idDataGroup, false);
				   bdQESIACAmt = bdQESIACAmt + DSTCommonFunctions::convertToBigDecimal(dstQESIACAmt.stripAll());
				   bdQESIRedACAmt = bdQESIRedACAmt + DSTCommonFunctions::convertToBigDecimal(dstrQESIRedACAmt.stripAll());
				   bdQESIUCAmt = bdQESIUCAmt + DSTCommonFunctions::convertToBigDecimal(dstrQESIUCAmt.stripAll());
				   bdQESIRedUCAmt = bdQESIRedUCAmt + DSTCommonFunctions::convertToBigDecimal(dstrQESIRedUCAmt.stripAll());
				   bdQESIYTDAmt = bdQESIYTDAmt + DSTCommonFunctions::convertToBigDecimal(dstrQESIYTDAmt.stripAll());
				   bdQESIRedYTDAmt = bdQESIRedYTDAmt + DSTCommonFunctions::convertToBigDecimal(dstrQESIRedYTDAmt.stripAll());

				   // QESI Pre Feb 2007 = 'Net of LTD' - 'Net of QESI AC' - 'Net of QESI UC' - Net of QESI YTD'
				   bdPre2007QESIContribAmt = bdPurLTDAmt + bdRedLTDAmt - bdQESIACAmt - bdQESIRedACAmt - bdQESIUCAmt - bdQESIRedUCAmt - bdQESIYTDAmt - bdQESIRedYTDAmt;
				   dstrPre2007QESIContribAmt = bdPre2007QESIContribAmt.asDString();
				   setFieldNoValidate(ifds::Pre2007QESIContrib, dstrPre2007QESIContribAmt, idDataGroup, false, true, true, true); 
			   }
		   }
	   }
   }
   
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY RESPTransfer::validateTransferInNotionalAmt (const BFDataGroupId &idDataGroup, const BFFieldId &idField, const DString &dstrTradeType)
{  
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateTransferUpdate"));

	DString dstrAccountNum, dstrTransId, dstrEffectiveDate, dstrReversal;
	bool bReversal = false;
	MFAccount *pMFAccount = NULL;

	getField (ifds::AccountNum, dstrAccountNum, idDataGroup, false);
	dstrAccountNum.strip ().stripLeading ('0');

	getField (ifds::TransId, dstrTransId, idDataGroup);	
	getField (ifds::EffectiveDate, dstrEffectiveDate, idDataGroup);
	
	if (getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING && pMFAccount && !(dstrTransId.stripAll().empty()) && (dstrTradeType == PROCESSED))
	{	 
		RESPTransactionsList *pRESPTransactionsList (NULL);

		if (pMFAccount->getRESPTransactionsList (pRESPTransactionsList, 
												 I_("H"), 			// HistoryPending
												 dstrTransId,		// ReqTransid
												 NULL, 				// RESPBenefId
												 I_("ALL"),			// BeneName
												 dstrEffectiveDate, // FromDate
												 dstrEffectiveDate, // ToDate
												 I_("ALL"),	 		// TransType
												 I_("A"),			// TfrStat
												 I_("A"),			// RepHRDC
												 idDataGroup) <= WARNING && pRESPTransactionsList)
		{						
			BFObjIter iter( *pRESPTransactionsList, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED );
			iter.begin();

			while (!iter.end())
			{			
				RESPTransactionsDetails *pRESPTransactionsDetails = dynamic_cast<RESPTransactionsDetails*>(iter.getObject());

				TransactionDetails *pTransactionDetails (NULL);

				if (pRESPTransactionsDetails->getTransactionDetails (pTransactionDetails, idDataGroup) <= WARNING && pTransactionDetails)
				{												
					pTransactionDetails->getField( ifds::Reversal, dstrReversal, idDataGroup, false );

					if( dstrReversal == YES )
					{							
						// CESG By Other Institution and QESI By Other Institution must be negative for reversal transactions
						validateTransferInNotionalAmt (idDataGroup, idField); // 1759 - Enter amounts with negative sign (-) on redemption and paid out column.						

						bReversal = true;
						break;
					}
				}				

				++iter;
			}			
		}		
	}

	// CESG By Other Institution and QESI By Other Institution must be positive for non reversal transactions
	if (!bReversal)
	{
		DString dstrNotionalAmt;
		getField (idField, dstrNotionalAmt, idDataGroup, false);  
		dstrNotionalAmt.strip();

		BigDecimal bdNotionalAmt = DSTCommonFunctions::convertToBigDecimal(dstrNotionalAmt);  
		BigDecimal bdZero = DSTCommonFunctions::convertToBigDecimal(I_("0.0"));

		if ( bdNotionalAmt < bdZero ) 
		{	
			// 1979 - Paid By Other Institution is a balance and must be positive.				
			getErrMsg( IFASTERR::NOTIONAL_PAID_BY_OTHER_AMOUNTS_MUST_BE_POSITIVE, 
					   CND::ERR_NOTIONAL_PAID_BY_OTHER_AMOUNTS_MUST_BE_POSITIVE, 
					   CND::WARN_NOTIONAL_PAID_BY_OTHER_AMOUNTS_MUST_BE_POSITIVE, 
					   idDataGroup);
		}
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log::   Y:/VCS/BF iFAST/ifastcbo/RESPTransfer.cpp-arc  $
// 
//    Rev 1.40   Oct 31 2011 04:44:00   wutipong
// IN2442518 Contribution Year does not display on Benef Lv. -- Sync Up
// 
//    Rev 1.39   Oct 25 2011 05:01:38   wutipong
// IN#2625408 - Disable eligible transfer on non-QESI client
// 
//    Rev 1.38   Oct 06 2011 10:36:08   panatcha
// P0185010FN01 - Beneficiary Allocations, EAP, LLP Withdrawals
// 
//    Rev 1.37   Oct 05 2011 00:59:50   panatcha
// IN2672499 - RESP Transfer Information error message
// 
//    Rev 1.36   Sep 23 2011 18:15:42   popescu
// Incident 2646349 - P0184541Fn01- Non QESI Desktop Issues
// 
//    Rev 1.35   Aug 29 2011 12:25:06   panatcha
// IN2640270_WO661530 - P0184541FN01- RESP Transfer and Notional Issues
// 
//    Rev 1.34   Aug 29 2011 04:38:38   panatcha
// IN2640270_WO661530 - P0184541FN01- RESP Transfer and Notional Issues
// 
//    Rev 1.33   Aug 16 2011 03:48:58   panatcha
// IN2617122 - set updateablility for Eligible and QESI Total TxFr
// 
//    Rev 1.32   Jul 29 2011 07:39:58   panatcha
// fix IN5285248 and IN2591262
// 
//    Rev 1.31   Jul 25 2011 07:12:22   panatcha
// P0184541_FN01_InvescoQESItrans incidents
// 
//    Rev 1.30   Jul 14 2011 08:11:10   panatcha
// DRAFT - IN2584478, IN5285248, IN2591262 
// 
//    Rev 1.29   Jul 11 2011 05:24:54   dchatcha
// IN# 2587585 - P0184541FN01- Error when accessing RESP TRFR notl in trading screen
// 
//    Rev 1.28   Jun 30 2011 00:29:20   panatcha
// P0184541_FN01_InvescoQESItrans
// 
//    Rev 1.27   Jun 28 2011 10:30:28   panatcha
// P0184541_FN01_InvescoQESItrans
// 
//    Rev 1.26   Jan 25 2011 04:50:56   kitticha
// IN#2390728 - There is no warning message when modifying 'QESI Basic' and 'QESI Increase' on Transfer Info Screen.
// 
//    Rev 1.25   Oct 29 2010 05:32:58   kitticha
// PET0165541 FN03 - QESI Phase3.
// 
//    Rev 1.24   Sep 03 2010 05:26:18   dchatcha
// IN# 2231991 - No warning message when changing the Transfer%
// 
//    Rev 1.23   Aug 18 2010 15:50:26   jankovii
// IN 2215054 - PET165541FN05 - Eligible transfer field defaults back to "NO" rel 100
// 
//    Rev 1.22   Aug 17 2010 16:35:54   jankovii
// Sync up: IN 2200243 - Invesco Trimark Parent Cycle CY1287 {27 JULY 2010}
// 
//    Rev 1.21   Aug 13 2010 12:07:48   jankovii
// Sync up: IN 2200243 - Invesco Trimark Parent Cycle CY1287 {27 JULY 2010}
// 
//    Rev 1.20   Jul 21 2010 23:26:42   dchatcha
// PET0165541 FN09 QESI RESP phase2B - SOC04 - Eligible Transfer on RESP Transfer screen, code review, remove no longer required (more)pieces.
// 
//    Rev 1.19   Jul 21 2010 22:40:40   dchatcha
// PET0165541 FN09 QESI RESP phase2B - SOC04 - Eligible Transfer on RESP Transfer screen, code review, remove no longer required pieces.
// 
//    Rev 1.18   Jul 21 2010 01:35:38   dchatcha
// PET0165541 FN09 QESI RESP phase2B - SOC04 - Eligible Transfer on RESP Transfer screen, code review, logic will be more simpler.
// 
//    Rev 1.17   Jun 29 2010 02:58:34   dchatcha
// PET0165541 FN09 QESI RESP phase2B - SOC04 - Eligible Transfer on RESP Transfer screen, code review.
// 
//    Rev 1.16   Jun 24 2010 07:49:58   dchatcha
// PET0165541 FN09 QESI RESP phase2B - SOC04 - Eligible Transfer on RESP Transfer screen.
// 
