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
//    Copyright 2004 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : Shareholder.cpp
// ^AUTHOR : Mike Metzger
// ^DATE   : 3/28/99
//
//********************************************************************************
#include "stdafx.h"

#include "accountmailinglist.hpp"
#include "accshrnumcheck.hpp"
#include "address.hpp"
#include "addresslist.hpp"
#include "demographics.hpp"
#include "directtradingbankinstructionslist.hpp"
#include "ErrMsgRulesList.hpp"
#include "FeeModelList.hpp"
#include "GroupFundList.hpp"
#include "grouplist.hpp"
#include "mfaccount.hpp"
#include "MFAccountHoldingList.hpp"
#include "mfaccountlist.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "remarkslist.hpp"
#include "residency.hpp"
#include "shareholder.hpp"
#include "shareholderbankinstructionslist.hpp"
#include "shralloctypelist.hpp"
#include "shrfundbrokerlist.hpp"
#include "shrfamilylist.hpp"
#include "shrfundsponsoragreementlist.hpp"

#include <ifastdataimpl\dse_dstc0069_vw.hpp>
#include <ifastdataimpl\dse_dstc0069_req.hpp>
#include <ifastdataimpl\dse_dstc0075_req.hpp>
#include <ifastdataimpl\dse_dstc0083_vw.hpp>
#include <ifastdataimpl\dse_dstc0043_vw.hpp>
#include <ifastdataimpl\dse_dstc0113_vw.hpp>
#include <ifastdataimpl\dse_dstc0120_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest SHAREHOLDER;
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const NON_RESIDENT_TAX_JURISD_STOP_PAC;
   extern CLASS_IMPORT I_CHAR * const SHAREHOLDER_TAXJUR_RESPROV_UNASSIGNED;
   //P0186486FN09 - Employee and Agent Account Gap#8A
   extern CLASS_IMPORT I_CHAR * const EMPLOYEE_AGENT_ONLY_APPICABLE_FOR_CLIENT_ACCT; 
   extern CLASS_IMPORT I_CHAR * const EMPLOYEE_AGENT_NOT_ALLOW_FOR_BALANCE_ACCT;
   extern CLASS_IMPORT I_CHAR * const JURISDICTION_NOT_SAME_AS_SHRHLDR_JURISDICTION;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_ ("Shareholder");
   const I_CHAR * const SHRHLDR_NUM_FIELD = I_ ("ShrhlderNum");
   const I_CHAR * const DOVALIDATEFIELD = I_ ("doValidateField");
   const I_CHAR * const DOVALIDATEALL = I_ ("doValidateAll");
   const I_CHAR * const DOAPPLYRELATEDCHANGES = I_ ("doApplyRelatedChanges");
   const I_CHAR * const VALIDVALUESFORSHRNUMCTRL = I_ ("MmCcSs");//for Morgan
   const I_CHAR * const SHAREHOLDER_LEVEL = I_ ("S");
   const I_CHAR * const ACCOUNT_LEVEL = I_ ("A");
   const I_CHAR * const YES = I_ ("Y");   
   const I_CHAR * const NO  = I_ ("N");   
   const I_CHAR * const TFSA_TAX_TYPE = I_("V");
   const I_CHAR * const UNASSIGNED = I_("0000");
   const I_CHAR * const TAX_JURISDICTION = I_("Tax Jurisdiction");
   const I_CHAR * const RESIDENCE_PROVINCE = I_("Residence Province");
   //P0186486FN09 - Employee and Agent Account Gap#8A
   const I_CHAR * const EMPLOYEE				   = I_("08"); 
   const I_CHAR * const AGENT                = I_("09");
   const I_CHAR * const CLIENT				   = I_("Client");
}

extern BF_OBJ_TYPE OBJ_TYPE_MFACCOUNT;
extern BF_OBJ_TYPE OBJ_TYPE_SHR_FUND_SPONSOR_AGREEMENT_LIST;
extern BF_OBJ_TYPE OBJ_TYPE_SHR_FUND_BROKER_LIST;

namespace CND
{
   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
   extern const long ERR_SHAREHOLDER_NUMBER_EXISTS;
   extern const long ERR_SHAREHOLDER_NUM_CANNOT_BE_LEFT_EMPTY;
   extern const long ERR_EFFECTIVE_DATE_BACKWARD;
   extern const long ERR_DATE_FUNCTIONS;
   extern const long ERR_SHAREHOLDER_NUMBER_CANNOT_START_WITH_ZERO;
   extern const long ERR_SHAREHOLDER_NUMBER_EMPTY;
   extern const long ERR_RESIDENCE_PROVINCE_EMPTY;
   extern const long ERR_TAX_JURIS_EMPTY;
   extern const long ERR_INVALID_SHAREHOLDER_NUM;
	extern const long ERR_UNABLE_TO_CHANGE_GROUP;
   extern const long WARN_ENSURE_PAC_IS_ALLOWED;
   extern const long ERR_FEEMODEL_CODE_NOT_SETUP;
   extern const long ERR_FEEMODEL_CODE_NOT_ACTIVE;
   extern const long ERR_ShareholderFeeModelCodeIsRequired;
   extern const long WARN_ShareholerFeeModelCodeIsNeeded;
   extern const long ERR_NON_RESIDENT_TAX_JURISD_STOP_PAC;
   extern const long WARN_NON_RESIDENT_TAX_JURISD_STOP_PAC;
   extern const long ERR_SHAREHOLDER_TAXJUR_RESPROV_UNASSIGNED;
   extern const long WARN_SHAREHOLDER_TAXJUR_RESPROV_UNASSIGNED;
   //P0186486FN09 - Employee and Agent Account Gap#8A
   extern const long ERR_EMPLOYEE_AGENT_ONLY_APPICABLE_FOR_CLIENT_ACCT;
   extern const long ERR_EMPLOYEE_AGENT_NOT_ALLOW_FOR_BALANCE_ACCT;
   extern const long WARN_EMPLOYEE_AGENT_ONLY_APPICABLE_FOR_CLIENT_ACCT;
   extern const long WARN_EMPLOYEE_AGENT_NOT_ALLOW_FOR_BALANCE_ACCT;
   extern const long WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_SICAV;
   extern const long WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_OEIC;
}



namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId DefaultGrp;
   extern CLASS_IMPORT const BFTextFieldId ShrNumCtrl;
   extern CLASS_IMPORT const BFTextFieldId rxGroupCode;
   extern CLASS_IMPORT const BFTextFieldId GroupName;
   extern CLASS_IMPORT const BFTextFieldId DataFound;
	extern CLASS_IMPORT const BFTextFieldId rxFundCode;
	extern CLASS_IMPORT const BFTextFieldId rxClassCode;
   extern CLASS_IMPORT const BFTextFieldId FeeModelCode;
	extern CLASS_IMPORT const BFTextFieldId ProdCode;
	extern CLASS_IMPORT const BFTextFieldId FundCode;
	extern CLASS_IMPORT const BFTextFieldId ClassCode;
	extern CLASS_IMPORT const BFTextFieldId ProductCode;
   extern CLASS_IMPORT const BFTextFieldId LSIFPAC;
	extern CLASS_IMPORT const BFTextFieldId ShrFndSpAgrExists;
   extern CLASS_IMPORT const BFTextFieldId AccountNumList;
   extern CLASS_IMPORT const BFTextFieldId PAC;
   extern CLASS_IMPORT const BFTextFieldId SystemTrsfr;
   extern CLASS_IMPORT const BFTextFieldId TaxJurisUpdateOpt;
   //P0186486FN09 - Employee and Agent Account Gap#8A
   extern CLASS_IMPORT const BFDecimalFieldId AccountBalance;
   extern CLASS_IMPORT const BFTextFieldId FeeWaived;
   extern CLASS_IMPORT const BFTextFieldId EmpAgentAppl;
   extern CLASS_IMPORT const BFTextFieldId rxBankingEntity;
   extern CLASS_IMPORT const BFNumericFieldId rxAcctNum;
   extern CLASS_IMPORT const BFTextFieldId DefaultBankingLevel;
}

namespace BANKENTITY
{
   extern CLASS_IMPORT I_CHAR * const SHAREHOLDER;
   extern CLASS_IMPORT I_CHAR * const ACCOUNT;
}

namespace BANKINGLEVEL
{
   extern CLASS_IMPORT I_CHAR *  const SHAREHOLDER_LEVEL ;
   extern CLASS_IMPORT I_CHAR *  const ACCOUNT_LEVEL ;
   extern CLASS_IMPORT I_CHAR *  const SHAREHOLDER_AND_ACCOUNT_LEVEL ;
}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR *  const SHAREHOLDER ;
   extern CLASS_IMPORT I_CHAR *  const ACCOUNT ;
}

namespace REMARK_FILTER_BY
{
    extern CLASS_EXPORT I_CHAR * const ALL              = I_("00");
    extern CLASS_EXPORT I_CHAR * const ACTIVE           = I_("01");
    extern CLASS_EXPORT I_CHAR * const INACTIVE         = I_("02");
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
//  Field DD Id,					State Flags,			Group Flags 

   {ifds::ShrNum,              BFCBO::REQUIRED,         SHAREHOLDER_GROUPING::SHAREHOLDER_INFO},
   {ifds::ShrNumManual,        BFCBO::NONE,             0},
   {ifds::AcctDesignation,     BFCBO::NONE,             0},
   {ifds::AcctDesignationDesc, BFCBO::NONE,             0},
   {ifds::TaxJurisCode,        BFCBO::REQUIRED,         SHAREHOLDER_GROUPING::SHAREHOLDER_INFO}, 
   {ifds::ResProvCode,         BFCBO::REQUIRED,         SHAREHOLDER_GROUPING::SHAREHOLDER_INFO}, 
   {ifds::GroupCode,           BFCBO::REQUIRED,         SHAREHOLDER_GROUPING::SHAREHOLDER_INFO}, 
   {ifds::FamilyCode,          BFCBO::NONE,             0},
   {ifds::FundRelnCode,        BFCBO::REQUIRED,         SHAREHOLDER_GROUPING::SHAREHOLDER_INFO}, 
   {ifds::EffectiveDate,       BFCBO::REQUIRED,         SHAREHOLDER_GROUPING::SHAREHOLDER_INFO}, 
   {ifds::PrimMstrVer,         BFCBO::NONE,             0},
   {ifds::Name1,               BFCBO::NONE,             0},
   {ifds::Name2,               BFCBO::NONE,             0},
   {ifds::GroupName1,          BFCBO::NONE,             0},
   {ifds::GroupName2,          BFCBO::NONE,             0},
   {ifds::FamilyName,          BFCBO::NONE,             0},
   {ifds::Confidential,        BFCBO::NONE,             0},
   {ifds::Channel,             BFCBO::NONE,             0},
   {ifds::DTAExist,            BFCBO::CALCULATED_FIELD, 0},
   {ifds::FeeModelCode,      BFCBO::NONE,             0},

   //   COA flags
   {ifds::ConsolEFT,           BFCBO::NONE,             0},
   {ifds::Remarks,             BFCBO::CALCULATED_FIELD, 0},
   {ifds::BankingInstr,        BFCBO::CALCULATED_FIELD, 0},
   {ifds::FamilyCodeExist,     BFCBO::NONE,             0},
   {ifds::GrpCodeLevel,        BFCBO::NONE,             0},
   {ifds::ShrFndSpAgrExists,   BFCBO::NONE,             0},	
   {ifds::AccountNumList,      BFCBO::CALCULATED_FIELD,             0},	
   {ifds::ShrFndBrkExist,      BFCBO::NONE,             0},	
};

static const int NUM_FIELDS = sizeof (classFieldInfo) / sizeof (BFCBO::CLASS_FIELD_INFO);

namespace SHAREHOLDER_GROUPING
{
   const long SHAREHOLDER_INFO = 0x0001;
   const long SHAREHOLDER_ADDRESS = 0x0002;
}

const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = 
{
   // Object Label,                          State Flags,      Group Flags 
   { I_ ("AccountMailingList"),                  BFCBO::NONE,     0},
   { I_ ("AddressList"),                         BFCBO::NONE, SHAREHOLDER_GROUPING::SHAREHOLDER_ADDRESS},
   { I_ ("DemographicsList"),                    BFCBO::NONE,     0},
   { I_ ("RemarksList"),                         BFCBO::NONE,     0},
   { I_ ("MFAccountList"),                       BFCBO::NONE,     0},
   { I_ ("AllocationList"),                      BFCBO::NONE,     0},
   { I_ ("AccountNumberList"),                   BFCBO::NONE,     0},
   { I_ ("ShareholderBankInstructionsList"),     BFCBO::NONE,     0},
   { I_ ("DirectTradingBankInstructionsList"),   BFCBO::NONE,     0},
   { I_ ("ShrFamilyList"),                       BFCBO::NONE,     0},
};

static const int NUM_OBJECTS = sizeof (classObjectInfo) / sizeof (BFCBO::CLASS_OBJECT_INFO);

//*********************************************************************************
SEVERITY Shareholder::validateShrNum (
      DSTCWorkSession &rpDSTCWorkSession, 
      const DString &strShrNum,
      const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (
         CND::IFASTCBO_CONDITION, 
         CLASSNAME, 
         I_("validateShrNum"));

   DString tempShrNum (strShrNum);

   tempShrNum.strip();

   bool bError = tempShrNum.empty () || !tempShrNum.isAllDigits ();
   
   if (!bError)
   {
      AccShrNumCheck checkAccNum (rpDSTCWorkSession);

      if (checkAccNum.initShrNum (strShrNum) <= WARNING)
      {
         DString found;

         checkAccNum.getField (ifds::DataFound, found, 
            idDataGroup, false);
         bError = found.strip () != YES;
      }
   }
   if (bError)
   {
      ADDCONDITIONFROMFILE (CND::ERR_INVALID_SHAREHOLDER_NUM);
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
bool Shareholder::shareholderHasPACWithLSIF (
      DSTCWorkSession &rpDSTCWorkSession,
      const DString &shrNum,
      const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (
         CND::IFASTCBO_CONDITION, 
         CLASSNAME, 
         I_("hasShareholderPACWithLSIF"));
   bool bHasPACWithLSIF = false;
   Shareholder *pShareholder = NULL;
   
   if (rpDSTCWorkSession.getShareholder (idDataGroup, 
            shrNum, pShareholder) <= WARNING &&
      pShareholder)
   {
      MFAccountList *pMFAccountList = NULL;

      if (pShareholder->getMFAccountList (pMFAccountList, idDataGroup) <= WARNING &&
         pMFAccountList)
      {
         BFObjIter iter (*pMFAccountList, idDataGroup);
         while (!iter.end ())
         {
            DString lsifPAC;

            iter.getObject()->getField (ifds::LSIFPAC, lsifPAC, idDataGroup, false);
            lsifPAC.strip();
            bHasPACWithLSIF = lsifPAC == I_("Y");
            if (bHasPACWithLSIF)
            {
               break;
            }
            ++iter;
         }
      }
   }
   return bHasPACWithLSIF;
}

//******************************************************************************
Shareholder::Shareholder (BFAbstractCBO &parent)
: MFCanBFCbo (parent),
_pResponseData (NULL),
_bRefresh (false)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);  
   registerMemberData (NUM_FIELDS, (const CLASS_FIELD_INFO*)&classFieldInfo,
                       NUM_OBJECTS, (const CLASS_OBJECT_INFO*)& classObjectInfo);
}

//******************************************************************************
Shareholder::~Shareholder ()
{
   if (_pResponseData)
   {
      delete _pResponseData;
   }
   TRACE_DESTRUCTOR (CLASSNAME);
}  

//******************************************************************************
SEVERITY Shareholder::init (const BFDataGroupId& idDataGroup, const DString& dstrShrhldrNum)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("init (int)"));

   if (setFieldNoValidate (ifds::ShrNum, dstrShrhldrNum, idDataGroup, true, true) <= WARNING)
   {
      _initShareholderNum = dstrShrhldrNum;
   }
   initWithDefaultValues (idDataGroup);

   DString dstrShrEFTConsol, dstrPacSwpEftConsol;
   if (getWorkSession ().getOption (ifds::ShrEFTConsol, dstrShrEFTConsol, idDataGroup, false) <= WARNING &&
       getWorkSession ().getOption (ifds::PACSWPEFTConsol, dstrPacSwpEftConsol, idDataGroup, false) <= WARNING)
   {
      dstrShrEFTConsol.strip ();
      dstrPacSwpEftConsol.strip ();
      if (dstrShrEFTConsol == I_ ("Y") && dstrPacSwpEftConsol == I_ ("Y"))
         setFieldNoValidate (ifds::ConsolEFT, I_ ("Y"), idDataGroup, true, true);
      else
         setFieldNoValidate (ifds::ConsolEFT, I_ ("N"), idDataGroup, true, true);

      if (dstrShrEFTConsol == I_ ("Y"))
         setFieldReadOnly (ifds::ConsolEFT, idDataGroup, false);
   }

   DString defaultGrp,grpCodeLevel;

   if (getWorkSession ().getOption (ifds::GrpCodeLevel, grpCodeLevel, idDataGroup, false) <= WARNING)
   {

      grpCodeLevel.strip ();
      setFieldNoValidate (ifds::GrpCodeLevel, grpCodeLevel, idDataGroup, true, true);
      if (grpCodeLevel == SHAREHOLDER_LEVEL)
      {
         loadGroupSubstitutionList (idDataGroup);
         defaultGrp.strip ();
         if (getWorkSession ().getOption (ifds::DefaultGrp, defaultGrp, idDataGroup) <= WARNING)
         {
            setFieldNoValidate (ifds::GroupCode, defaultGrp, idDataGroup, true, true);
         }
      }
   }

/*
   if (getWorkSession ().getOption (DBR::DefaultGrp, defaultGrp, idDataGroup, false) <= WARNING)
   {
      defaultGrp.strip ();
      setFieldNoValidate (DBR::GroupCode, defaultGrp, idDataGroup, true, true);
   }*/
   // get the current date from the system configuration
   DString defaultDate;

   if (getWorkSession ().getOption (ifds::CurrBusDate, defaultDate, idDataGroup, false) <= WARNING)
   {
      setFieldNoValidate (ifds::EffectiveDate, defaultDate, idDataGroup, false, true, true);
      _initEffectiveDate = defaultDate;
   }    
   setFieldNoValidate (ifds::Channel,I_ ("7"),idDataGroup,false,true,true);
   if (ACCOUNT_LEVEL == grpCodeLevel)
   {
      setFieldRequired (ifds::GroupCode, idDataGroup, false);

   }
   else if (SHAREHOLDER_LEVEL == grpCodeLevel)
   {
      setFieldRequired (ifds::GroupCode, idDataGroup, true);
   }
   //the business rule is:
   //if shrNumCtrl is M the user HAS TO ENTER a value
   //if is C or S the user might enter a value
   //otherwise we should generate a number
/*   DString shrNumCtrl;

   if (getWorkSession ().getOption (DBR::ShrNumCtrl, shrNumCtrl, idDataGroup) <= WARNING)
   {
      //if is new, maybe checking this here is redundant (isNew ())
      if (isNew () && (shrNumCtrl == I_ ("M") || shrNumCtrl == I_ ("m")))
      {
         //clearout the ShrNum because we have to force the user to enter a number
         //notify the observers, as well and set the field to be invalid
         //setFieldNoValidate (DBR::ShrNum, NULL_STRING, idDataGroup, false, true);
      }
   }
   */
   //set the account designation description
   DString acctDesignationDesc;

   //get the formatted value and set it to the acct designation
   getField (ifds::AcctDesignation, acctDesignationDesc, idDataGroup, true); 
   setFieldNoValidate (ifds::AcctDesignationDesc, acctDesignationDesc, idDataGroup, false, true, true);
   checkForReadOnly (idDataGroup);

   DString strMarket = DSTCommonFunctions::getMarket ();

   if (strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG)
   {
      setFieldReadOnly (ifds::AcctDesignation , idDataGroup, false);
   }
   setDefaultBankInstrSel( idDataGroup);
   clearUpdatedFlags (idDataGroup, false);
   return (GETCURRENTHIGHESTSEVERITY ());
}

//******************************************************************************
SEVERITY Shareholder::init (const DString& dstrShareholderNum,
   const DString& dstrTrack /*= I_ ("N")*/, 
   const DString& dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("init"));

   //set the field DBR::GrpCodeLevel to be used in Dlg
   DString grpCodeLevel;
   if (getWorkSession ().getOption (ifds::GrpCodeLevel, grpCodeLevel, BF::HOST, false) <= WARNING)
   {
      grpCodeLevel.strip ();
      setFieldNoValidate (ifds::GrpCodeLevel, grpCodeLevel, BF::HOST, true, true);
   }

   BFData requestData (ifds::DSTC0069_REQ);   

   DString mgmtCoIdOut;
   requestData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   requestData.setElementValue (ifds::ShrNum, dstrShareholderNum);
   requestData.setElementValue (ifds::NextKey, NULL_STRING);
   requestData.setElementValue (ifds::Track, dstrTrack);
   requestData.setElementValue (ifds::Activity, dstrPageName);
   tempShr = dstrShareholderNum;

   //   AsyncReceiveData (DSTC_REQUEST::SHAREHOLDER, requestData, DBR::DSTC0069_VW, DSTCRequestor (getSecurity ()));

   BFData *receivedData = new BFData (ifds::DSTC0069_VW);

   if (BFDataBroker::getInstance ()->receive (DSTC_REQUEST::SHAREHOLDER, 
      requestData, *receivedData, DSTCRequestor (getSecurity (), true,true)) <= WARNING)
   {
      const BFData& repeat = receivedData->getRepeat (0);

      attachDataObject (*receivedData, true, false);
      attachDataObject (const_cast<BFData&> (repeat), false, false);
      _initShareholderNum = dstrShareholderNum;
      _initShareholderNum.stripLeading ('0').strip ();
      _initEffectiveDate = repeat.getElementValue (ifds::EffectiveDate);
      initFieldsNotInInquiry (BF::HOST);
      checkForReadOnly (BF::HOST);
      clearUpdatedFlags (BF::HOST, false);
      loadGroupSubstitutionList (BF::HOST);
      setDefaultBankInstrSel( BF::HOST);
   }
   else
   {
      delete receivedData;
   }   
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
void Shareholder::donotifyResponse (SEVERITY severity, 
   const Condition *condition, 
   BFData *receivedData, 
   bool moreAvailable, int callBackOption)
{   
   if (severity <= WARNING)
   {
      const BFData& repeat = receivedData->getRepeat (0);
      attachDataObject (const_cast<BFData&> (repeat), true, false);
      _initShareholderNum = tempShr;
      _initShareholderNum.stripLeading ('0').strip ();
      _initEffectiveDate = repeat.getElementValue (ifds::EffectiveDate);
   }
   else
   {
      delete receivedData;
      receivedData=NULL;
   }   
   initFieldsNotInInquiry (BF::HOST);
   checkForReadOnly (BF::HOST);
   clearUpdatedFlags (BF::HOST, false);
}

//support for refresh
//******************************************************************************
SEVERITY Shareholder::doPreClearFields ()
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("doPreClearFields"));

   //for now we do refresh only in HOST
   getField (ifds::ShrNum, _reinitShareholderNum, BF::HOST);
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Shareholder::reInit ()
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("reInit"));

   if (!isNew ())
   {
      init (_reinitShareholderNum);
   }
   _bRefresh = false;
   return GETCURRENTHIGHESTSEVERITY ();
}

//*************************************************************************************
bool Shareholder::needsRefresh (const BFDataGroupId& idDataGroup) const
{
   return _bRefresh ? _bRefresh : hasUpdatedFields (idDataGroup);
}

//*************************************************************************************
void Shareholder::refreshMe (bool bRefreshMe)
{
   _bRefresh = bRefreshMe;
}

//*************************************************************************************
SEVERITY Shareholder::doValidateField (const BFFieldId& idField, 
   const DString& strValue, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, DOVALIDATEFIELD);

   if (idField == ifds::ShrNum && idDataGroup != BF::HOST)
   {
      bool shrNumFound = false;

      //check the shareholder number only if the shareholder is new
      if (isNew () && checkTheShareholderNumber (strValue, idDataGroup, shrNumFound) <= WARNING)
      {
         if (shrNumFound)
         {
            ADDCONDITIONFROMFILE (CND::ERR_SHAREHOLDER_NUMBER_EXISTS);
         }
      }
   }
   else if (idField == ifds::EffectiveDate)
   {
      if (!isNew ())
      {
         if ((DSTCommonFunctions::CompareDates (strValue, _initEffectiveDate)) == DSTCommonFunctions::FIRST_EARLIER ||
             (DSTCommonFunctions::CompareDates (strValue, _initEffectiveDate)) == DSTCommonFunctions::EQUAL)
         {
            ADDCONDITIONFROMFILE (CND::ERR_DATE_FUNCTIONS);   // Change to 'Effective date must be after Initial Effective Date.'
         }
      }
   }
   else if (idField == ifds::ResProvCode)
   {
      if (strValue.empty ())
      {
         ADDCONDITIONFROMFILE (CND::ERR_RESIDENCE_PROVINCE_EMPTY);
      }
   }
   else if (idField == ifds::TaxJurisCode)
   {
      if (strValue.empty ())
      {
         ADDCONDITIONFROMFILE (CND::ERR_TAX_JURIS_EMPTY);
      }
      else
      {
         DString shrNum;

         getField (ifds::ShrNum, shrNum, idDataGroup, false);
         if (Shareholder::shareholderHasPACWithLSIF (
            getWorkSession(), 
            shrNum, 
            idDataGroup))
         {
            ADDCONDITIONFROMFILE (CND::WARN_ENSURE_PAC_IS_ALLOWED);
         }

		 //for Canadian clients check for TFSA PAC Exist
         DString strMarket = DSTCommonFunctions::getMarket ();
         if ( !isNew() && strMarket == MARKET_IDS::CANADA )
		 {			
			Residency* residency;
			if( getWorkSession().getResidencyForShareholder( residency, shrNum, strValue, idDataGroup ) <= WARNING && residency )
			{
				if( !residency->isTaxJurisdictionValid() )
				{
					getErrMsg ( IFASTERR::NON_RESIDENT_TAX_JURISD_STOP_PAC,
								CND::ERR_NON_RESIDENT_TAX_JURISD_STOP_PAC,
								CND::WARN_NON_RESIDENT_TAX_JURISD_STOP_PAC,
								idDataGroup,
								NULL_STRING);
				}
			}     
		 }
      }
   }
   else if (idField == ifds::GroupCode)
   {
      if (!isNew ())
      {
         validateGroupCode (strValue, idDataGroup);
      }
   }
   else if ( idField == ifds::FeeModelCode )
   {
      validateModelCode( idDataGroup );
   }
   else if(idField == ifds::FundRelnCode || idField == ifds::AcctDesignation) //P0186486FN09 - Employee and Agent Account Gap#8A
   { 
	   validateEmployeeAgent(idDataGroup);			  
   }
   return (GETCURRENTHIGHESTSEVERITY ());
}

//******************************************************************************
SEVERITY Shareholder::doApplyRelatedChanges (const BFFieldId& idField, 
   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, DOAPPLYRELATEDCHANGES);

   if (idField == ifds::ShrNum)
   {

      //if the value of the shareholder number has changed,
      //flip the ShrNumManual to yes
      DString newShrNum;

      getField (ifds::ShrNum, newShrNum, idDataGroup);
      if (isNew () && _initShareholderNum != NULL_STRING && //only if is new allow the shareholder number manual to be set
          newShrNum != _initShareholderNum) //the shr numbers are different
      {
         //no side effect is needed
         setFieldNoValidate (ifds::ShrNumManual, I_ ("Y"), idDataGroup);
      }
   }
   else if (idField == ifds::ResProvCode)
   {
	   //IN3313412
	   ErrMsgRulesList *pErrMsgRulesList = NULL;

	   if ( getMgmtCo ().getErrMsgRulesList (pErrMsgRulesList) <= WARNING &&
		   pErrMsgRulesList)
	   {
		   DString strErrValue;

		   pErrMsgRulesList->getEWIValue (IFASTERR::JURISDICTION_NOT_SAME_AS_SHRHLDR_JURISDICTION, idDataGroup, strErrValue);
		   if (strErrValue != I_("E"))
		   {
			   DString resProvCode;

			   getField (ifds::ResProvCode, resProvCode, idDataGroup);
			   setField(ifds::TaxJurisCode, resProvCode, idDataGroup, false, true);
		   }
	   }           
   }
   else if (idField == ifds::GroupCode)
   {

      DString groupCode;
      getField (ifds::GroupCode, groupCode, idDataGroup);

      GroupList* pGroupList = NULL;
      if (getMgmtCo ().getGroupList (pGroupList) <= WARNING)
      {
         BFObjIter groupIter (*pGroupList, idDataGroup);

         for (groupIter.begin (); !groupIter.end (); ++groupIter)
         {
            DString groupName, iterGroupCode;

            groupIter.getObject ()->getField (ifds::rxGroupCode, iterGroupCode, idDataGroup);
            if (groupCode == iterGroupCode)
            {
               groupIter.getObject ()->getField (ifds::GroupName, groupName, idDataGroup);
               setFieldNoValidate (ifds::GroupName1, groupName, idDataGroup, true, true, true);
            }
         }
      }
   }
   else if (idField == ifds::AcctDesignation) //set the description
   {
      DString acctDesignationDesc;

      //get the formatted value and set it to the acct designation
      getField (ifds::AcctDesignation, acctDesignationDesc, idDataGroup, true); 
      setFieldNoValidate (ifds::AcctDesignationDesc, acctDesignationDesc, idDataGroup, false, true, true);
   }
   //for the COA flags, reset the updated flag
   else if (idField == ifds::ConsolEFT)
   {
      DString strMarket = DSTCommonFunctions::getMarket ();
      if (strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG)
         setUpdatedFlag (idField, idDataGroup, false);
   }
   else if (idField == ifds::BankingInstr || idField == ifds::Remarks ||
      idField == ifds::FamilyCodeExist || idField == ifds::AccountNumList )
   {
      setUpdatedFlag (idField, idDataGroup, false);
   }
   else if(idField ==ifds::FundRelnCode) //P0186486FN09 - Employee and Agent Account Gap#8A
   {
	   setFeeWaivedforEmployAgent(idDataGroup) ;
   }
   return (GETCURRENTHIGHESTSEVERITY ());
}

//******************************************************************************
// forceViewCall is added to ensure that when allocation dlg is open/ reresh, it make will
// the view call to get the data. this is to fix a problem when use replace as default option
//******************************************************************************
SEVERITY Shareholder::getAllocationList ( ShrAllocTypeList*& pAllocationList, 
                                          const BFDataGroupId& idDataGroup, 
                                          bool inquireDatabase /*= true*/, 
                                          bool forceViewCall /*= false */)

{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("getAllocationList"));

   //check cbobase to see if we've already built it
   //otherwise, create and store with base
   DString strKey = I_("AllocationList");
   
   pAllocationList = dynamic_cast< ShrAllocTypeList* > (getObject (strKey, idDataGroup));
   DString shrNum;

   bool bNeedSetObject = false;

   BFDataGroupId idWorkingDataGroup = idDataGroup;
   if (!pAllocationList)
   {
      if (isNew ()) //check if the shareholder is new
      {
         pAllocationList = new ShrAllocTypeList (*this);
         pAllocationList->initNew (idDataGroup);

         bNeedSetObject = true;
      }
      else if (inquireDatabase || forceViewCall)
      {
         idWorkingDataGroup = BF::HOST;
         pAllocationList = new ShrAllocTypeList (*this);
         pAllocationList->initExisting ();
         //if we inquire the database the group id should be the host			
         bNeedSetObject = true;
      }
   }
   else
   {
      if (forceViewCall)
      {
         // the existing pAllocationList will be cleared automatically in setObject
         idWorkingDataGroup = BF::HOST;
         pAllocationList = new ShrAllocTypeList (*this);
         pAllocationList->initExisting ();
         //if we inquire the database the group id should be the host			
         bNeedSetObject = true;
      }
   }

   if (bNeedSetObject && pAllocationList)
   {
      if (GETCURRENTHIGHESTSEVERITY () <= WARNING)
      {
         setObject (pAllocationList, strKey, OBJ_ACTIVITY_NONE, idWorkingDataGroup); 
      }
      else
      {
         delete pAllocationList;
         pAllocationList = NULL;
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//*******************************************************************************
Address *Shareholder::getCurrentMailingAddress (DString &strAccountNum, 
   const BFFieldId& mailFieldId, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("getCurrentMailingAddress"));

   Address *address = NULL;

   AccountMailingList *pAcctMailList = NULL;
   DString strAddrCode;

   if (getAccountMailingList (pAcctMailList, idDataGroup) <= WARNING && 
       pAcctMailList != NULL)
   {
      BFObjIter iter (*pAcctMailList, idDataGroup);

      strAccountNum.stripLeading ('0');
      if (iter.positionByKey (strAccountNum))
      {
         iter.getObject ()->getField (mailFieldId, strAddrCode, idDataGroup);
         strAddrCode.strip ();

         AddressList* pAddrList = NULL;

         getAddressList (pAddrList, idDataGroup);

         BFObjIter itAddrList (*pAddrList, idDataGroup);

         while (!itAddrList.end ())
         {
            DString strAddrCodeObj, strCurDate, effDate, stopDate;

            itAddrList.getObject ()->getField (ifds::AddrCode, strAddrCodeObj, idDataGroup, false);
            strAddrCodeObj.strip ();

            getWorkSession ().getMgmtCoOptions ()->getField (ifds::CurrBusDate, strCurDate, idDataGroup);
            itAddrList.getObject ()->getField (ifds::EffectiveDate, effDate, idDataGroup);
            itAddrList.getObject ()->getField (ifds::StopDate, stopDate, idDataGroup);
            effDate.strip ();
            stopDate.strip ();
            strCurDate.strip ();
            if (DSTCommonFunctions::IsDateBetween (effDate, stopDate, strCurDate))
            {
               address = dynamic_cast<Address*> (itAddrList.getObject ());    
            }
         }
      }
   }

   return (address);
}

//******************************************************************************
//moved to Account level since CIBC KYC enhancement
/*SEVERITY Shareholder::getDemographicsList (Demographics*& pDemographics, 
   const BFDataGroupId& idDataGroup, bool inquireDatabase)  //=true
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("getDemographicsList"));

   return getList_X (I_ ("DemographicsList"), pDemographics, idDataGroup, inquireDatabase);
}*/

//******************************************************************************
//yingbao move AddressList from MfAccount to Shareholder
SEVERITY Shareholder::getAddressList (AddressList*& pAddressList, 
   const BFDataGroupId& idDataGroup, bool ignoreDataNotFound /*=true*/, 
   bool inquireDatabase /*= true*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("getAddressList"));
   pAddressList = dynamic_cast< AddressList* > (BFCBO::getObject (I_ ("AddressList"), idDataGroup));
   BFDataGroupId idWorkingDataGroup = idDataGroup;
   if (!pAddressList)
   {
      DString shrNum;

      getField (ifds::ShrNum, shrNum, idDataGroup);
      shrNum.stripLeading ('0');
      shrNum.strip ();

      if (isNew ()) //checks if the shareholder is new
      {
         pAddressList = new AddressList (*this);
         pAddressList->initNew (shrNum);
      }
      else if (inquireDatabase)
      {
         pAddressList = new AddressList (*this);
         pAddressList->init (shrNum, ignoreDataNotFound);
         //if we inquire the database the group id should be the host
         idWorkingDataGroup = BF::HOST;
      }
      if (pAddressList) //make the view call
      {
         if (GETCURRENTHIGHESTSEVERITY () <= WARNING)
         {
            setObject (pAddressList, I_ ("AddressList"), OBJ_ACTIVITY_NONE, idWorkingDataGroup); 
         }
         else
         {
            delete pAddressList;
            pAddressList = NULL;
         }
      }
   }
   return (GETCURRENTHIGHESTSEVERITY ());
}


//********************************************************************************
SEVERITY Shareholder::getDirectTradingBankInstructionsList (
   DirectTradingBankInstructionsList *&pDirectTradingBankInstructionsList, 
   const BFDataGroupId& idDataGroup, bool inquireDatabase /*= true*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, 
      I_ ("getDirectTradingBankInstructionsList"));

   return getList_X (I_ ("DirectTradingBankInstructionsList"), 
      pDirectTradingBankInstructionsList, idDataGroup, inquireDatabase);
}

//********************************************************************************
SEVERITY Shareholder::getShareholderBankInstructionsList (
   ShareholderBankInstructionsList*& pShareholderBankInstructionsList,
   const BFDataGroupId& idDataGroup, bool inquireDatabase /*=true*/, const DString dstrAcctNum /*= NULL_STRING*/ )
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("getShareholderBankInstructionsList"));
   I_CHAR* i_charname = I_ ("ShareholderBankInstructionsList");
   BFDataGroupId idWorkingDataGroup = idDataGroup;
   DString shrNum;
   getField (ifds::ShrNum, shrNum, idDataGroup);
   shrNum.stripLeading ('0');
   shrNum.strip ();
   //assumed logic ..the share holder level  banking instructions is always called first..or will break..
   pShareholderBankInstructionsList = dynamic_cast< ShareholderBankInstructionsList* > (BFCBO::getObject (i_charname, idDataGroup));
   if (!pShareholderBankInstructionsList)
   {
      if (isNew ())
      {
         //new empty list
         pShareholderBankInstructionsList = new ShareholderBankInstructionsList (*this);
         pShareholderBankInstructionsList->initNew (shrNum, idWorkingDataGroup);
      }
      else if (inquireDatabase)//always call the Shareholder banking instructions 
      {
         pShareholderBankInstructionsList = new ShareholderBankInstructionsList (*this);
         pShareholderBankInstructionsList->init (shrNum,I_("N"), NULL_STRING, BANKENTITY::SHAREHOLDER);
         //if we inquire the database the group id should be the host
         idWorkingDataGroup = BF::HOST;
      }
      if (pShareholderBankInstructionsList)
      {
         if (GETCURRENTHIGHESTSEVERITY () <= WARNING)
         {
            setObject (pShareholderBankInstructionsList, i_charname, OBJ_ACTIVITY_NONE, idWorkingDataGroup);
         }
         else 
         {
            delete pShareholderBankInstructionsList; 
            pShareholderBankInstructionsList = NULL;
         }
      }
    }
    //we have a shareholder banking list created..Attach the account ones to it...
    DString dstrBankingConfig;
    bool bAcctLevelbankingAppl = false;
    if( pShareholderBankInstructionsList )
    {
        pShareholderBankInstructionsList->getBankingConfiguration(dstrBankingConfig, idDataGroup);
        bAcctLevelbankingAppl = BANKINGLEVEL::SHAREHOLDER_LEVEL == dstrBankingConfig ? false : true;
    }
    if(pShareholderBankInstructionsList && bAcctLevelbankingAppl)
    {
       BFDataGroupId idWorkingDataGroup = idDataGroup;
       DString dstrAcct = dstrAcctNum;
       dstrAcct.stripLeading(I_('0'));
       dstrAcct.stripAll();
       
       //if not found in the list call the 54 view with the entity Id as 14 and accountnumber
       if( !dstrAcct.empty() ) 
       {
          if (isNew () && pShareholderBankInstructionsList)
          {
            //don't create new list...use the exsiitng one which we created
            //pShareholderBankInstructionsList = new ShareholderBankInstructionsList (*this);
            pShareholderBankInstructionsList->initNew (dstrAcct, idWorkingDataGroup);
          }
           //assumed logic ..the share holder level  banking instructions is always called first..or will break..
          else if ( pShareholderBankInstructionsList && inquireDatabase && 
                    pShareholderBankInstructionsList->isNotInAccountBankingInstrMap(dstrAcct, idDataGroup))
          {
             //don't create new list...use the exsiitng one which we created
             //pShareholderBankInstructionsList = new ShareholderBankInstructionsList (*this);
             pShareholderBankInstructionsList->init (dstrAcctNum, I_("N"), NULL_STRING, BANKENTITY::ACCOUNT);
             //if we inquire the database the group id should be the host
             idWorkingDataGroup = BF::HOST;
             //if the view return is less than warning add the account and instructions to the map 
             //if error don't do anything we have a shareholder list alreday created..
             //don't destroy it or you are in trouble..  
             if (GETCURRENTHIGHESTSEVERITY () <= WARNING )
             {
               pShareholderBankInstructionsList->insertToAccountBankingInstrMap(dstrAcct); 
             } 
          }       
       }            
    }    
   return GETCURRENTHIGHESTSEVERITY ();
}

//********************************************************************************
SEVERITY Shareholder::getAccountMailingList (AccountMailingList*& pAccountMailingList, 
   const BFDataGroupId& idDataGroup, bool inquireDatabase /*=true*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("getAccountMailingList"));

   return getList_X (I_ ("AccountMailingList"), pAccountMailingList, idDataGroup, inquireDatabase);
}

//********************************************************************************
SEVERITY Shareholder::getRemarksList (RemarksList*& pRemarksList, 
   const BFDataGroupId& idDataGroup, bool inquireDatabase /*=true*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("getRemarksList"));

   return getList_X (I_ ("RemarksList"), pRemarksList, idDataGroup, inquireDatabase);
}

//********************************************************************************
SEVERITY Shareholder::getShrFamilyList (ShrFamilyList *&pShrFamilyList, 
   const BFDataGroupId& idDataGroup, bool inquireDatabase /*= true*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("getShrFamilyList"));

   return getList_X (I_ ("ShrFamilyList"), pShrFamilyList, idDataGroup, inquireDatabase);
}
/****************************************************************************/
SEVERITY Shareholder::getMFAccountList (MFAccountList*& pMFAccountList, 
   const BFDataGroupId& idDataGroup, bool inquireDatabase /*= true*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("getMFAccountList"));

   return getList_X (I_ ("MFAccountList"), pMFAccountList, idDataGroup, inquireDatabase);
}

//******************************************************************************
SEVERITY Shareholder::getAccountNumberList (AccShrNumCheck *&pAccShrNumCheck, 
   const BFDataGroupId& idDataGroup, bool inquireDatabase /*= true*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("getAccountNumberList"));

   return getList_X (I_ ("AccountNumberList"), pAccShrNumCheck, idDataGroup, inquireDatabase);
}

//******************************************************************************
SEVERITY Shareholder::getShrFundSponsorAgreementList( ShrFundSponsorAgreementList *&pShrFundSponsorAgreementList, 
																	   const DString &dstrFundGroup, 
																		const BFDataGroupId& idDataGroup, 
																		bool bInquireDatabase /*= true*/	)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("getShrFundSponsorAgreementList"));

   // The View takes 2 parameters, ShareholderNum and FundGroup. For now only ShareholderNum is used.
	// However, for consistency, pass both paramters. This leads to not using the template _X.

	DString dstrShrNum;
   getField (ifds::ShrNum, dstrShrNum, idDataGroup);
   dstrShrNum.stripLeading ('0');
   dstrShrNum.strip ();

	DString dstrKey = I_( "ShrFundSponsorAgreementList" ) + dstrShrNum + I_( ";" ) + dstrFundGroup;
	
	//check cbobase to see if we've already built it, otherwise, create and store with base
   pShrFundSponsorAgreementList = dynamic_cast<ShrFundSponsorAgreementList*>(BFCBO::getObject( dstrKey, idDataGroup ) );
   
	if( NULL == pShrFundSponsorAgreementList )
   {
      BFDataGroupId idWorkingDataGroup = idDataGroup;
      
      if( isNew () )
      {
         //new empty list
         pShrFundSponsorAgreementList = new ShrFundSponsorAgreementList (*this);
         pShrFundSponsorAgreementList->initNew( dstrShrNum, 
														      idWorkingDataGroup );
      }
      else if( bInquireDatabase )
      {
         pShrFundSponsorAgreementList = new ShrFundSponsorAgreementList (*this);
         //if we inquire the database the group id should be the host         
			idWorkingDataGroup = BF::HOST;

			pShrFundSponsorAgreementList->init( dstrFundGroup, 
														   idWorkingDataGroup );         
      }

      if( NULL != pShrFundSponsorAgreementList )
      {
         if( GETCURRENTHIGHESTSEVERITY () <= WARNING )
         {
            setObject( pShrFundSponsorAgreementList, 
					        dstrKey, 
							  OBJ_ACTIVITY_NONE, 
							  idWorkingDataGroup, 
							  OBJ_TYPE_SHR_FUND_SPONSOR_AGREEMENT_LIST );
         }
         else
         {
            delete pShrFundSponsorAgreementList;
            pShrFundSponsorAgreementList = NULL;
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Shareholder::getShrFundBrokerList( ShrFundBrokerList *&pShrFundBrokerList, 
									  					  const DString &dstrFund, 
														  const DString &dstrFundBroker,
														  const BFDataGroupId& idDataGroup, 
														  const DString &dstrDuplicateCheck,   //I_( "N" ) 											 
														  bool bInquireDatabase  /*true*/	)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("getShrFundBrokerList"));

   pShrFundBrokerList = NULL;
	
	DString dstrShrNum;
   getField (ifds::ShrNum, dstrShrNum, idDataGroup);
   dstrShrNum.stripLeading ('0');
   dstrShrNum.strip ();

	DString dstrKey = I_( "ShrFundBrokerList" ) + dstrShrNum + I_( ";" ) + dstrFund + I_( ";" ) + dstrFundBroker;
		
	//check cbobase to see if we've already built it, otherwise, create and store with base
	pShrFundBrokerList = dynamic_cast<ShrFundBrokerList*>(BFCBO::getObject( dstrKey, idDataGroup ) );
	   
	if( NULL == pShrFundBrokerList )
   {
      BFDataGroupId idWorkingDataGroup = idDataGroup;
      
      if( isNew () )
      {
         //new empty list
         pShrFundBrokerList = new ShrFundBrokerList (*this);
         pShrFundBrokerList->initNew( dstrShrNum, 
												  idWorkingDataGroup );
      }
      else if ( bInquireDatabase )		
      {
         pShrFundBrokerList = new ShrFundBrokerList (*this);
         //if we inquire the database the group id should be the host         
			//idWorkingDataGroup = BF::HOST;

			pShrFundBrokerList->init( dstrShrNum,
                                   dstrFund, 
											  dstrFundBroker,
											  dstrDuplicateCheck, 
											  idWorkingDataGroup );         
      }

      if( NULL != pShrFundBrokerList )
      {
         if( GETCURRENTHIGHESTSEVERITY () <= WARNING )
         {
            setObject( pShrFundBrokerList, 
					        dstrKey, 
							  OBJ_ACTIVITY_NONE, 
							  idWorkingDataGroup, 
							  OBJ_TYPE_SHR_FUND_BROKER_LIST );
         }
         else
         {
            delete pShrFundBrokerList;
            pShrFundBrokerList = NULL;
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
template <class _X> 
   SEVERITY Shareholder::getList_X (const I_CHAR* i_charname, _X*& pListOut, 
         const BFDataGroupId& idDataGroup, bool inquireDatabase /*= true*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("getList_X"));

   //check cbobase to see if we've already built it
   //otherwise, create and store with base
   pListOut = dynamic_cast< _X* > (BFCBO::getObject (i_charname, idDataGroup));
   if (!pListOut)
   {
      BFDataGroupId idWorkingDataGroup = idDataGroup;
      DString shrNum;

      getField (ifds::ShrNum, shrNum, idDataGroup);
      shrNum.stripLeading ('0');
      shrNum.strip ();
      if (isNew ())
      {
         //new empty list
         pListOut = new _X (*this);
         pListOut->initNew (shrNum, idWorkingDataGroup);
      }
      else if (inquireDatabase)
      {
         pListOut = new _X (*this);
         pListOut->init (shrNum);
         //if we inquire the database the group id should be the host
         idWorkingDataGroup = BF::HOST;
      }
      if (pListOut)
      {
         if (GETCURRENTHIGHESTSEVERITY () <= WARNING)
         {
            setObject (pListOut, i_charname, OBJ_ACTIVITY_NONE, idWorkingDataGroup);
         }
         else
         {
            delete pListOut;
            pListOut = NULL;
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Shareholder::checkTheShareholderNumber (const DString& shrNum,
   const BFDataGroupId& idDataGroup, bool &found)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("checkTheAccountNumber"));

   AccShrNumCheck acctShrNumCheck (*this);
   DString strFound, tempShrNum (shrNum);

   if (shrNum != NULL_STRING && shrNum[ 0 ] == '0')
   {
      ADDCONDITIONFROMFILE (CND::ERR_SHAREHOLDER_NUMBER_CANNOT_START_WITH_ZERO);
   }
   else
   {
      found = false;
      //we should do that here since setting the shrnum to NULL_STRING if the
      //ShrNumCtrl is either M or m, will format the ShrNum to 0;
      tempShrNum.stripLeading ('0').strip ();
      if (tempShrNum != NULL_STRING)
      {
         //checks for the validity of the shareholder number, by making a view call.
         if (acctShrNumCheck.initCheck (tempShrNum, NULL_STRING) <= WARNING)
         {
            acctShrNumCheck.getField (ifds::DataFound, strFound, idDataGroup);
            found = strFound == I_ ("Y");
         }
      }
      else //null string
      {
         ADDCONDITIONFROMFILE (CND::ERR_SHAREHOLDER_NUMBER_EMPTY);
      }
   }
   return (GETCURRENTHIGHESTSEVERITY ());
}

//********************************************************************************
SEVERITY Shareholder::checkForReadOnly (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("checkForReadOnly"));

   DString shrNumCtrl;
   DString validShrNumCtrl (VALIDVALUESFORSHRNUMCTRL);

   //if it is not manual do not allow the shareholder num to be changed
   if (getWorkSession ().getOption (ifds::ShrNumCtrl, shrNumCtrl, idDataGroup) <= WARNING && 
       validShrNumCtrl.find (shrNumCtrl.c_str ()) == DString::npos)
   {
      if (isNew () && shrNumCtrl.strip () == I_ ("m"))
      {
         setFieldReadOnly (ifds::ShrNum, idDataGroup, false);
      }
      else
      {
         setFieldReadOnly (ifds::ShrNum, idDataGroup, true);
      }
   }
   // set AcctDesignation field to be read only field
   setFieldReadOnly (ifds::AcctDesignation, idDataGroup, true);
   
   // Tax jurisdiction is always readonly for existing account.
   //IN3308549
   //if ( (!isNew()) && (DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA) )
   if (!isNew())
   {
	   setFieldReadOnly (ifds::TaxJurisCode, idDataGroup, true);	
   }

   return (GETCURRENTHIGHESTSEVERITY ());
}

//********************************************************************************
SEVERITY Shareholder::initFieldsNotInInquiry (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("initFieldsNotInInquiry"));

   if (!isNew ())
   {
      setFieldNoValidate (ifds::ShrNumManual, I_ ("N"), idDataGroup, false);
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//********************************************************************************
SEVERITY Shareholder::attachAccountToMFAccountList (MFAccount *pMFAccount, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("attachAccountToMFAccountList"));

   MFAccountList *pMFAccountList = NULL;

   if (getMFAccountList (pMFAccountList, idDataGroup) <= WARNING)
   {
      DString strKey;

      pMFAccountList->getStrKey (strKey, NULL);
      BFObjectKey bfObjKey (strKey, idDataGroup, OBJ_ACTIVITY_ADDED, OBJ_TYPE_MFACCOUNT);

      pMFAccountList->setObject (bfObjKey, pMFAccount);
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//********************************************************************************
SEVERITY Shareholder::detachAccountFromMFAccountList (MFAccount *pMFAccount, 
   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("detachAccountFromMFAccountList"));

   MFAccountList *pMFAccountList = NULL;

   if (getMFAccountList (pMFAccountList, idDataGroup) <= WARNING)
   {
      for (BFObjIter mfAcctIter (*pMFAccountList, idDataGroup); !mfAcctIter.end (); ++mfAcctIter)
      {
         if (mfAcctIter.getObject () == pMFAccount)
         {
            //do not delete the instance of the object because 
            //this is not own by the MFAccountList
            mfAcctIter.removeObjectFromMap (false);
            break;
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//*******************************************************************************
inline BFAbstractCBO *Shareholder::getTopLevelAncestor () 
{
   return this;
}

//********************************************************************************
void Shareholder::doPopulateField (const BFFieldId& idField, 
   DString& strValue, bool formattedReturn)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("doPopulateField"));

   strValue = NULL_STRING;
   DString strShrNum;

   if (!_pResponseData)
   {
      _pResponseData = new BFData (ifds::DSTC0069_VW);
   }
   if (idField != ifds::ShrNum && 
       BFData::exists (_pResponseData->getRepeatId (), idField))
   {
      BFCBO::getField (ifds::ShrNum, strShrNum, BF::HOST, false);

      if (init (strShrNum) <= WARNING)
      {
         BFCBO::getField (idField, strValue, BF::HOST, formattedReturn);
      }
   }
}

//*********************************************************************************
SEVERITY Shareholder::loadGroupSubstitutionList (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("loadGroupSubstitutionList"));

   GroupList*  pGroupList= NULL;
   DString dstSubstList = NULL_STRING;

   if (getMgmtCo ().getGroupList (pGroupList)  <= WARNING)
   {
      pGroupList->getGroupSubstList (dstSubstList, true);
      dstSubstList.upperCase ();
      setFieldAllSubstituteValues (ifds::GroupCode, idDataGroup, dstSubstList);
   }

   return (GETCURRENTHIGHESTSEVERITY ());
}

//*********************************************************************************
SEVERITY Shareholder::validateGroupCode (const DString& strValue, const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("validateGroupCode"));
	MFAccountList *pMFAccountList;
	MFAccount *pMFAccount = NULL;
	MFAccountHoldingList *pMFAccountHoldingList=NULL;
	DString strAccNum, dstrFundCode, dstrClassCode;
	if (getMFAccountList (pMFAccountList, idDataGroup)<=WARNING && pMFAccountList)
	{
		BFObjIter iterMFAcct (*pMFAccountList, idDataGroup);
		while (!iterMFAcct.end ())
		{
			pMFAccount = dynamic_cast<MFAccount*> (iterMFAcct.getObject ());
			if (pMFAccount)
			{
				if (pMFAccount->getAccountHoldingList (pMFAccountHoldingList, idDataGroup) <= WARNING && pMFAccountHoldingList)
            {
					BFObjIter iterAcctHolder (*pMFAccountHoldingList, idDataGroup);
					while (!iterAcctHolder.end ())
					{
						iterAcctHolder.getObject ()->getField (ifds::rxFundCode, dstrFundCode, idDataGroup, false);
						dstrFundCode.strip ().upperCase ();
						iterAcctHolder.getObject ()->getField (ifds::rxClassCode, dstrClassCode, idDataGroup, false);
						dstrClassCode.strip ().upperCase ();
						
						if (dstrFundCode != I_ ("CASH") && ! (isFundClassExit (pMFAccount, strValue, dstrFundCode, dstrClassCode,idDataGroup)))
						{
							ADDCONDITIONFROMFILE (CND::ERR_UNABLE_TO_CHANGE_GROUP);
							return (GETCURRENTHIGHESTSEVERITY ());  
						}
						else
						{
							++iterAcctHolder;
						}
					} // while (!iterAcctHolder.end ())
				}
			} // if (pMFAccount)
			++iterMFAcct;
		} // while (!iterMFAcct.end ())
	}
	return (GETCURRENTHIGHESTSEVERITY ());
}


//*********************************************************************************
bool Shareholder::isFundClassExit (MFAccount *pMFAccount, const DString& strGroupCode,
											  const DString& dstrFundCode, const DString& dstrClassCode,
											  const BFDataGroupId& idDataGroup)
{
	DString strCopy (strGroupCode);
	strCopy.strip ().upperCase ();
	DString dstrProdCode, dstrFundCodeInGroup, dstrClassCodeInCroup,dstrProductCodeInGroup ;
	pMFAccount->getField (ifds::ProdCode, dstrProdCode, idDataGroup);
   GroupFundList *pGroupFundList = NULL;
   if (pMFAccount->getGroupFundListFromGroup (strCopy, dstrFundCode, idDataGroup, pGroupFundList) <= WARNING)
   {
      if (pGroupFundList != NULL)  // If there's a problem with getting a Group Fund List (View 88), we'll return false
      {
         BFObjIter iter (*pGroupFundList,idDataGroup);
     
         while (!iter.end ())
		   {
			   iter.getObject ()->getField (ifds::FundCode, dstrFundCodeInGroup, idDataGroup, false);
			   dstrFundCodeInGroup.strip ().upperCase ();
			   iter.getObject ()->getField (ifds::ClassCode, dstrClassCodeInCroup, idDataGroup, false);
			   dstrClassCodeInCroup.strip ().upperCase ();
			   iter.getObject ()->getField (ifds::ProductCode, dstrProductCodeInGroup, idDataGroup, false);
			   dstrProductCodeInGroup.strip ().upperCase ();
			   if (dstrFundCode == dstrFundCodeInGroup && dstrClassCode == dstrClassCodeInCroup &&
				     dstrProdCode == dstrProductCodeInGroup)
			   {
				   /*if ( pGroupFundList )
					   delete pGroupFundList;*/

				   return true;
			   }
			   else
			   {
				   ++iter;
			   }
		   }
      }
	}

    /*if ( pGroupFundList)
		delete pGroupFundList;*/

	return false;
}

//*********************************************************************************
SEVERITY Shareholder::validateModelCode( const BFDataGroupId& idDataGroup  )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( " validateModelCode " ) );

	DString dstrFeeModelCode;
	getField( ifds::FeeModelCode, dstrFeeModelCode,idDataGroup,false);
	dstrFeeModelCode.stripAll();
	if( NULL_STRING == dstrFeeModelCode )
	{
	   ErrMsgRulesList *pErrMsgRulesList = NULL;

      getMgmtCo().getErrMsgRulesList( pErrMsgRulesList );

		DString strErrValue;
		if( pErrMsgRulesList )
		{
			pErrMsgRulesList->getEWIValue (I_("423"), idDataGroup,strErrValue);
			strErrValue.strip().upperCase();
			long Id = 0;
			if( strErrValue == I_("E") )
			{
				Id = CND::ERR_ShareholderFeeModelCodeIsRequired;
			}
			else if( strErrValue == I_("W") )
			{
				Id = CND::WARN_ShareholerFeeModelCodeIsNeeded;			
			}
			if( Id!=0)
			{
			      ADDCONDITIONFROMFILE (Id);
					return (GETCURRENTHIGHESTSEVERITY() );					

			}	
		}
	}
	else
	{
		FeeModelList* pFeeModelList;

		if (getFeeModelInfo (pFeeModelList, dstrFeeModelCode, idDataGroup) <= WARNING &&
            pFeeModelList)
		{
			DString dstrCurrBusDate;
			getWorkSession ().getOption (ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false);

			int ret = pFeeModelList->isValidFeeModelCode(idDataGroup, dstrFeeModelCode, dstrCurrBusDate);
 
			if(ret == 1)
			{
				DString dstrTemp;                 
				addIDITagValue( dstrTemp, I_("FEEMODELCODE"), dstrFeeModelCode );
				ADDCONDITIONFROMFILEIDI( CND::ERR_FEEMODEL_CODE_NOT_SETUP, dstrTemp);	
			}
			if(ret == 2 )
			{
				DString dstrTemp;                 
				addIDITagValue( dstrTemp, I_("FEEMODELCODE"), dstrFeeModelCode );
            addIDITagValue( dstrTemp, I_("DATE"), dstrCurrBusDate );
				ADDCONDITIONFROMFILEIDI( CND::ERR_FEEMODEL_CODE_NOT_ACTIVE, dstrTemp);	
			}
 
		}
	}
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY Shareholder::doValidateAll ( const BFDataGroupId& idDataGroup, long lValidateGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("doValidateAll"));

	DString dstrTaxJurisdiciton;
	DString dstrResidenceProvince;
	DString dstrTaxJurisUpdateOpt;

	
	if( !isNew()&& isUpdatedForDataGroup (idDataGroup) )
	{//for new shareholder no need to display the warning
	MFAccountList *pMFAccountList;
	MFAccount *pMFAccount = NULL;
	 if (getMFAccountList (pMFAccountList, idDataGroup)<=WARNING && pMFAccountList)
	 {
		BFObjIter iterMFAcct (*pMFAccountList, idDataGroup);
		while (!iterMFAcct.end ())
		{
			pMFAccount = dynamic_cast<MFAccount*> (iterMFAcct.getObject ());
			if (pMFAccount)
			{
				DString dstrShareholderNum,dstrCurrShrNumber;
				pMFAccount->getField( ifds::ShrNum, dstrShareholderNum, idDataGroup );
				dstrShareholderNum.strip().stripLeading( I_CHAR( '0' ) );
				if(!dstrShareholderNum.empty()&& _initShareholderNum != NULL_STRING
				   && dstrShareholderNum ==  _initShareholderNum )
				{
				 {	
					bool bDisplyWarnSICAV ,bDisplyWarnOEIC;
					pMFAccount->displayEnvXrefWarningOnUpdate(idDataGroup, bDisplyWarnSICAV, bDisplyWarnOEIC);
					if(bDisplyWarnSICAV)
						ADDCONDITIONFROMFILE (CND::WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_SICAV);
					if(bDisplyWarnOEIC)
						ADDCONDITIONFROMFILE (CND::WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_OEIC);
				 }  
				break;
				}
			}
			++iterMFAcct;
		}
	 }
	}
   
	getWorkSession().getOption(ifds::TaxJurisUpdateOpt, dstrTaxJurisUpdateOpt, idDataGroup, false);

	if(dstrTaxJurisUpdateOpt == NO)
		return(GETCURRENTHIGHESTSEVERITY());

	getField (ifds::ResProvCode, dstrResidenceProvince, idDataGroup, false);
	getField (ifds::TaxJurisCode, dstrTaxJurisdiciton, idDataGroup, false);

	if (dstrResidenceProvince == UNASSIGNED)
	{
		DString idiStr;

		addIDITagValue (idiStr, I_("STR"), RESIDENCE_PROVINCE);

	    getErrMsg (IFASTERR::SHAREHOLDER_TAXJUR_RESPROV_UNASSIGNED,
                   CND::ERR_SHAREHOLDER_TAXJUR_RESPROV_UNASSIGNED, 
                   CND::WARN_SHAREHOLDER_TAXJUR_RESPROV_UNASSIGNED, 
                   idDataGroup, idiStr);
	}

	if (dstrTaxJurisdiciton == UNASSIGNED)
	{
		DString idiStr;

		addIDITagValue (idiStr, I_("STR"), TAX_JURISDICTION);

	    getErrMsg (IFASTERR::SHAREHOLDER_TAXJUR_RESPROV_UNASSIGNED,
                   CND::ERR_SHAREHOLDER_TAXJUR_RESPROV_UNASSIGNED, 
                   CND::WARN_SHAREHOLDER_TAXJUR_RESPROV_UNASSIGNED, 
                   idDataGroup, idiStr);
	}

	return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************************
SEVERITY Shareholder::getFeeModelInfo (FeeModelList *&pFeeModelList, 
									   const DString &dstrFeeModelCode,
									   const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getFeeModelInfo" ) );

	DString strKey = I_("FeeModelList") + dstrFeeModelCode;
	strKey.stripAll();

	pFeeModelList = dynamic_cast <FeeModelList*> (BFCBO::getObject (strKey, idDataGroup));
   
	if (!pFeeModelList)
	{
      
		pFeeModelList = new FeeModelList (*this);
		pFeeModelList->init (dstrFeeModelCode, idDataGroup); 
	  
		if (pFeeModelList)
		{
			if (GETCURRENTHIGHESTSEVERITY() <= WARNING)
			{
				setObject (pFeeModelList, strKey, OBJ_ACTIVITY_NONE, idDataGroup); 
			}
			else
			{
			   delete pFeeModelList;
				pFeeModelList = NULL;
			}
		}
	}	 
	
	return GETCURRENTHIGHESTSEVERITY();
}
//*********************************************************************************
//P0186486FN09 - Employee and Agent Account Gap#8A
bool Shareholder::isAccountBalance (const BFDataGroupId& idDataGroup)
{
	
	MFAccountList *pMFAccountList;
	MFAccount *pMFAccount = NULL;
	bool ret(false);
	
	if (getMFAccountList (pMFAccountList, idDataGroup)<=WARNING && pMFAccountList)
	{
		BFObjIter iterMFAcct (*pMFAccountList, idDataGroup);
		while (!iterMFAcct.end ())
		{
			pMFAccount = dynamic_cast<MFAccount*> (iterMFAcct.getObject ());
			if (pMFAccount)
			{
				DString dstrAcctBalance;

				pMFAccount->getField(ifds::AccountBalance, dstrAcctBalance, idDataGroup);
				if( dstrAcctBalance.asInteger() > 0 )
				{
					ret = true;
					break;
				}
				
			} // if (pMFAccount)

			++iterMFAcct;
		} // while (!iterMFAcct.end ())
		
	}
	return ret;
}
//********************************************************************************
SEVERITY Shareholder::validateEmployeeAgent(const BFDataGroupId& idDataGroup)
{//P0186486FN09 - Employee and Agent Account Gap#8A
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("validateEmployeeAgent"));

	DString preFundRelCodePre, currFundRelCode;

	getField (ifds::FundRelnCode, preFundRelCodePre, BF::HOST, false);
	getField (ifds::FundRelnCode, currFundRelCode, idDataGroup, false);

	if (currFundRelCode == AGENT || currFundRelCode == EMPLOYEE)
	{
		DString acctDesignation;

		getField (ifds::AcctDesignation, acctDesignation, idDataGroup, true); 

		//only Client account is allowed
		if(!acctDesignation.empty() && acctDesignation != CLIENT) //DSC: Client
		{
			//MSG:Only Client account is applicable to set up Employee/Agent indicator.
			getErrMsg (IFASTERR::EMPLOYEE_AGENT_ONLY_APPICABLE_FOR_CLIENT_ACCT, 
				CND::ERR_EMPLOYEE_AGENT_ONLY_APPICABLE_FOR_CLIENT_ACCT, 
				CND::WARN_EMPLOYEE_AGENT_ONLY_APPICABLE_FOR_CLIENT_ACCT, 
				idDataGroup);
		}

   }

   if(!isNew()) //existing account - only no balance is allowed to set up Employee/Agent relationship
   {
      if(isAccountBalance(idDataGroup))
      {  
         if((currFundRelCode == AGENT) || (currFundRelCode == EMPLOYEE))
         {
            //Fund relationship cannot be changed to agent/employee when account balance > 0
            DString strIDI;
            if(currFundRelCode == EMPLOYEE)
            {
               addIDITagValue( strIDI, I_("ACCOUNT_TYPE"), I_("Employee") );
            }
            else
            {
               addIDITagValue( strIDI, I_("ACCOUNT_TYPE"), I_("Agent") );
            }

            getErrMsg ( IFASTERR::EMPLOYEE_AGENT_NOT_ALLOW_FOR_BALANCE_ACCT,
               CND::ERR_EMPLOYEE_AGENT_NOT_ALLOW_FOR_BALANCE_ACCT, 
               CND::WARN_EMPLOYEE_AGENT_NOT_ALLOW_FOR_BALANCE_ACCT, 
               idDataGroup,
               strIDI);
         }  
      }

   }

	
	return (GETCURRENTHIGHESTSEVERITY ());
}
//********************************************************************************
//P0186486FN09 - Employee and Agent Account Gap#8A
SEVERITY Shareholder::setFeeWaivedforEmployAgent(const BFDataGroupId& idDataGroup) 
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setFeeWaivedforEmployAgent"));

	DString empAgentAppl(NULL_STRING);

	getWorkSession().getOption(ifds::EmpAgentAppl, empAgentAppl, idDataGroup, false);
   empAgentAppl.strip().upperCase();

	if(empAgentAppl == I_("Y"))
	{
	   MFAccountList *pMFAccountList;
      MFAccount *pMFAccount = NULL;
		DString fundRelCode;

      getField (ifds::FundRelnCode, fundRelCode, idDataGroup, false);

      if (getMFAccountList (pMFAccountList, idDataGroup)<=WARNING && pMFAccountList)
      {
         BFObjIter iterMFAcct (*pMFAccountList, idDataGroup);
         while (!iterMFAcct.end ())
         {
            pMFAccount = dynamic_cast<MFAccount*> (iterMFAcct.getObject ());
            if (pMFAccount)
            {
               if (fundRelCode == AGENT || fundRelCode == EMPLOYEE)
               {
                  pMFAccount->setField (ifds::FeeWaived, I_("Y"), idDataGroup);
               }

            } // if (pMFAccount)

            ++iterMFAcct;
         } // while (!iterMFAcct.end ())

      }


	}

	return (GETCURRENTHIGHESTSEVERITY ());
}
//********************************************************************************
bool Shareholder::hasBankingInstr(const BFDataGroupId& idDataGroup, const DString&  dstrAcctnum )
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "hasBankingInstr"));

   int numBankingInstr = 0;
   ShareholderBankInstructionsList *pShareholderBankInstructionsList = NULL;
   DString dstrSearchBankingFor;
   dstrSearchBankingFor = dstrAcctnum == NULL_STRING ? BANKENTITY::SHAREHOLDER:BANKENTITY::ACCOUNT;
   if(getShareholderBankInstructionsList( pShareholderBankInstructionsList , idDataGroup, true,dstrAcctnum) <= WARNING)
   {
     BFObjIter iterBankInstructionsList (*pShareholderBankInstructionsList, idDataGroup);
     
     while (!iterBankInstructionsList.end ())
     { 
        DString dstrBankingEntity;
        (iterBankInstructionsList.getObject())->getField(ifds::rxBankingEntity, dstrBankingEntity,BF::HOST);       
        if( BANKENTITY::SHAREHOLDER == dstrSearchBankingFor && 
            dstrSearchBankingFor == dstrBankingEntity   )
        {
            numBankingInstr = 1;
            break;
        }
        if( dstrSearchBankingFor == dstrBankingEntity && 
            BANKENTITY::ACCOUNT == dstrSearchBankingFor )
        {
            DString dstrAcctNumFromList;
            (iterBankInstructionsList.getObject())->getField(ifds::rxAcctNum, dstrAcctNumFromList,BF::HOST); 
            if( dstrAcctnum ==  dstrAcctNumFromList ) 
            {     
              numBankingInstr = 1;
              break;
            }
        }
        ++iterBankInstructionsList;
      }
   }    
  return( numBankingInstr );
}	
//********************************************************************************
void  Shareholder::setDefaultBankInstrSel( const BFDataGroupId& idDataGroup )
{

  MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setDefaultBankInstrSel"));

  DString dstrDefaultBankingLevel;
  getWorkSession ().getOption (ifds::DefaultBankingLevel, dstrDefaultBankingLevel ,idDataGroup, false);
  m_dstrCurrentBankingSel = BANKENTITY::ACCOUNT == dstrDefaultBankingLevel ? 
                                                        BANKTYPE::ACCOUNT : BANKTYPE::SHAREHOLDER;  
}
//********************************************************************************
//              Revision Control Entries
//********************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/Shareholder.cpp-arc  $
 * 
 *    Rev 1.84   May 21 2012 14:14:04   dchatcha
 * P0186479 FN10 -Gap 14G - Block Service Unit Transfers, revise code.
 * 
 *    Rev 1.83   May 16 2012 18:34:58   dchatcha
 * P0186479 FN10 -Gap 14G - Block Service Unit Transfers, refreshing remark list after change compensation agent.
 * 
 *    Rev 1.82   May 16 2012 05:10:36   panatcha
 * IN2929301 -  Agent and Employee
 * 
 *    Rev 1.81   Apr 14 2012 11:29:42   panatcha
 * P0186486FN09 - Employee and Agent Account Gap#8A
 * 
 *    Rev 1.80   Apr 10 2012 05:06:52   panatcha
 * P0186486FN09 - Employee and Agent Account Gap#8A
 * 
 *    Rev 1.79   Jan 11 2011 10:44:24   jankovii
 * IN 2350361 - iFast performance issue
 * 
 *    Rev 1.78   Mar 06 2009 11:44:58   jankovii
 * IN 1549352 - RESIDENCE PROVINCE AND TAX JURISDICTION
 * 
 *    Rev 1.77   12 Nov 2008 17:09:50   popescu
 * Incident#  1476692 - fixed object required issue in shareholder
 * 
 *    Rev 1.76   29 Oct 2008 13:07:12   kovacsro
 * IN#1461514 - TFSA- chg addr to Non-Res with active pac
 * 
 *    Rev 1.75   06 Oct 2008 13:19:52   kovacsro
 * PET142007  FN01 TFSA
 * 
 *    Rev 1.74   14 Sep 2007 09:55:40   popescu
 * GAP 2/2360 - a bit of a cleanup
 * 
 *    Rev 1.73   Oct 25 2005 12:51:44   popescu
 * Incident# 434042 - removed the deletes of the group fund list. since now is cached at the mgmt co leve.
 * 
 *    Rev 1.72   Mar 13 2005 17:16:20   winnie
 * Restore the previous version. No longer have a pointer in Group object for GroupFundList but instead have the object which create it delete the GroupFundList as soon as finish using it.
 * 
 *    Rev 1.71   Mar 11 2005 14:08:58   smithdav
 * Fixed bug in Group::getGroupFundListByFund function where BPS threads clashed the function call concurrently.
 * 
 *    Rev 1.70   Feb 15 2005 20:24:46   winnie
 * PTS 237768 : Get Group Fund by Fund Code to speed up the performance. 
 * 
 *    Rev 1.69   Nov 28 2004 14:05:46   vadeanum
 * PET1117 FN08 - Shareholder Fund Broker support 
 * 
 *    Rev 1.68   Nov 25 2004 17:51:36   vadeanum
 * PET1117 FN08 - Shareholder Fund Broker.
 * 
 *    Rev 1.67   Nov 14 2004 16:30:32   purdyech
 * Synch 1.65.1.0
 * 
 *    Rev 1.65.1.0   Nov 11 2004 16:42:14   vadeanum
 * PET1117 FN08 - Shareholder Fund Broker - work in progress.
 * 
 *    Rev 1.65   Oct 21 2004 17:50:20   FENGYONG
 * PTS10034976 - Error message of Fee ModelCode not active
 * 
 *    Rev 1.64   Oct 20 2004 18:02:24   YINGBAOL
 * PTS10034800:change validate FeeModelCode
 * 
 *    Rev 1.63   Sep 29 2004 17:05:40   FENGYONG
 * set updateflag false for field AccountNumList
 * 
 *    Rev 1.62   Sep 21 2004 16:06:24   YINGBAOL
 * PET1117 FN05:correct spelling mistake
 * 
 *    Rev 1.61   Sep 21 2004 14:25:52   YINGBAOL
 * PET1117 FN05: FeeModelCode is mandatory based on the error set up
 * 
 *    Rev 1.60   Sep 02 2004 12:31:12   FENGYONG
 * Add Conditions for PET1117 FN5
 * 
 *    Rev 1.59   Aug 31 2004 17:30:12   FENGYONG
 * change Field names
 * 
 *    Rev 1.58   Aug 11 2004 18:37:48   FENGYONG
 * Temp check in  PET 117 FN5  for other enhancement compiling
 * 
 *    Rev 1.57   Jul 27 2004 16:10:14   VADEANUM
 * PET1117 FN01 - Shareholder Static Data - Added ShrFndSpAgrExists to Class Field Info.
 * 
 *    Rev 1.56   Jul 26 2004 17:54:24   VADEANUM
 * PET1117 FN01 - Shareholder Static Data support.
 * 
 *    Rev 1.55   May 18 2004 17:15:06   popescu
 * PET 985, FN 01, Shareholder Tax Jurisdiction Warning
 * 
 *    Rev 1.54   Dec 31 2003 11:54:16   popescu
 * PTS 10025659, force a refresh of the Sahreholder object at host level if we have Demographics updates
 * 
 *    Rev 1.53   Oct 31 2003 14:47:32   FENGYONG
 * Add calculate field DTAExist
 * 
 *    Rev 1.52   Oct 06 2003 12:44:12   popescu
 * Added banking support for DirectTrading enhancement
 * 
 *    Rev 1.51   Oct 02 2003 14:13:58   HERNANDO
 * PTS 10022353 - Missing Group Code List was causing internal error; handle NULL pointer.
 * 
 *    Rev 1.50   Sep 09 2003 14:04:32   HERNANDO
 * Sync'd with 1.46.1.0; PTS 10019537.
 * 
 *    Rev 1.49   Aug 21 2003 14:26:38   linmay
 * set default value for Channel to 7
 * 
 *    Rev 1.48   Aug 21 2003 09:28:22   linmay
 * added field Confidential and channel
 * 
 *    Rev 1.47   Jul 11 2003 16:03:46   FENGYONG
 * move demographic from shareholder to MFAccount
 * 
 *    Rev 1.46   May 31 2003 11:55:28   popescu
 * RRIF bank work
 * 
 *    Rev 1.45   May 27 2003 18:29:56   popescu
 * due to several memory leaks found in some list getters at the DSTCWorkSession level caused by copy/paste, I've created a common template function to retrieve the dependent objects
 * 
 *    Rev 1.44   May 22 2003 14:13:12   popescu
 * Replaced name 'BankInstr' with 'BankInstructions'; 
 * simplified child lists getters for the Shareholder object
 * 
 *    Rev 1.43   Mar 21 2003 18:24:30   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.42   Jan 25 2003 12:31:10   KOVACSRO
 * For FamilyCodeExist setUpdatedFlag false.
 * 
 *    Rev 1.41   Jan 13 2003 18:02:02   sanchez
 * Changes for Shareholer
 * 
 *    Rev 1.40   Nov 18 2002 10:54:36   PURDYECH
 * BFObjectKey changes.
 * 
 *    Rev 1.39   Oct 09 2002 23:55:00   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.38   Aug 29 2002 12:56:40   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.37   Aug 06 2002 15:21:32   HERNANDO
 * PTS 10009268 - Revised Shareholder date edit check.  Effective date must be after initial effective date.
 * 
 *    Rev 1.36   22 May 2002 18:29:50   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.35   22 Apr 2002 10:05:08   KOVACSRO
 * Rel.47 : new design for Allocations.
 * 
 *    Rev 1.34   Feb 25 2002 19:11:00   PURDYECH
 * Phase 1 of BFData Rollout - Base Component Compatibility
 * 
 *    Rev 1.33   18 Feb 2002 10:16:42   KOVACSRO
 * Added more logic in validateShrNum ().
 * 
 *    Rev 1.32   08 Feb 2002 17:12:22   KOVACSRO
 * Added validateShrNum static method.
 * 
 *    Rev 1.31   20 Nov 2001 10:33:06   KOVACSRO
 * code clean up.
 * 
 *    Rev 1.30   19 Nov 2001 09:55:04   KOVACSRO
 * delete response data if receive failed.
 * 
 *    Rev 1.29   Nov 14 2001 15:36:28   YINGBAOL
 * code clean up
 * 
 *    Rev 1.28   14 Nov 2001 09:20:08   KOVACSRO
 * If something goes wrong in doPopulateField, promote the error and don't try to get the field's value.
 * 
 *    Rev 1.27   15 Oct 2001 12:17:48   KOVACSRO
 * init will not call view 69 anymore. View 69 will be called by doPopulateField whenever it is necessary.
 * 
 *    Rev 1.26   Sep 18 2001 17:16:22   YINGBAOL
 * fix memory leak
 * 
 *    Rev 1.25   Aug 16 2001 16:45:20   YINGBAOL
 * fix bug
 * 
 *    Rev 1.24   Aug 02 2001 01:19:34   YINGBAOL
 * fix datagroup issues for getShareholder
 * 
 *    Rev 1.23   Jul 12 2001 15:26:50   JANKAREN
 * new logic for Consolidate EFT
 * 
 *    Rev 1.22   Jun 07 2001 08:59:54   JANKAREN
 * Sync up SSB (1.19.1.4)
 * 
 *    Rev 1.21   11 May 2001 09:08:50   HSUCHIN
 * Sync up with SSB (1.19.1.3)
 * 
 *    Rev 1.20   03 May 2001 14:07:06   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.19   Apr 02 2001 13:38:04   YINGZ
 * fix mem leak
 * 
 *    Rev 1.18   Mar 30 2001 11:05:14   DINACORN
 * Used DSTCommonFunctions MARKET_IDS constants
 * 
 *    Rev 1.17   Mar 27 2001 10:29:54   YINGZ
 * bug fixing
 * 
 *    Rev 1.16   Mar 23 2001 13:03:24   YINGZ
 * remove async for now
 * 
 *    Rev 1.15   Feb 21 2001 16:06:46   BUZILAMI
 * changed BankAcct*.?pp => BankInstr*.?pp
 * 
 *    Rev 1.14   Feb 21 2001 10:39:28   BUZILAMI
 * Bank Acct changes
 * 
 *    Rev 1.13   Feb 14 2001 10:36:44   HSUCHIN
 * added async receive
 * 
 *    Rev 1.12   Jan 18 2001 16:09:44   YINGBAOL
 * add eTracker
 * 
 *    Rev 1.11   Jan 17 2001 12:08:20   VASILEAD
 * Added workSessionId param for MgmtCo::getMgmtCoOptions ()
 * 
 *    Rev 1.10   Jan 16 2001 15:03:08   OLTEANCR
 * changed to use new data brokering system
 * 
 *    Rev 1.9   Dec 17 2000 20:24:28   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.8   Nov 02 2000 14:11:38   VASILEAD
 * Added workSeesionId parameter for Mgmtco based CBOs
 * 
 *    Rev 1.7   Oct 24 2000 11:46:36   YINGBAOL
 * fix refresh issue
 * 
 *    Rev 1.6   Sep 29 2000 13:27:12   YINGZ
 * change market from cfds - canada to canada
 * 
 *    Rev 1.5   Sep 06 2000 14:49:12   YINGBAOL
 * change sync.
 * 
 *    Rev 1.4   Aug 16 2000 10:40:24   DINACORN
 * Set the field GrpCodeLevel to be used in Dlg
 * 
 *    Rev 1.3   Jul 24 2000 14:31:16   DINACORN
 * Make AcctDesignation updatable
 * 
 *    Rev 1.2   Mar 31 2000 14:29:40   HSUCHIN
 * M2 sync up
 * 
 *    Rev 1.1   Mar 08 2000 09:58:04   HSUCHIN
 * added Canadian stuff
 * 
 *    Rev 1.0   Feb 15 2000 11:00:06   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.70   Feb 03 2000 09:09:02   BUZILA
 * Marked non updatable COA flags as CALCULATED_FIELD
 * 
 *    Rev 1.69   Feb 01 2000 14:36:28   BUZILA
 * added lValidateGroup parameter to doValidateAll method
 * 
 *    Rev 1.68   Feb 01 2000 13:35:14   POPESCUS
 * quick fix
 * 
 *    Rev 1.67   Feb 01 2000 12:57:42   POPESCUS
 * fix showing the Accdesignation descr after COA in NASU
 * 
 *    Rev 1.66   Feb 01 2000 12:34:12   POPESCUS
 * remove the account from the shareholder mfaccount list when rolling back
 * 
 *    Rev 1.65   Jan 28 2000 15:20:48   POPESCUS
 * fixes to SIT's
 * 
 *    Rev 1.64   Jan 27 2000 17:56:04   VASILEAD
 * quick fix for demographics
 * 
 *    Rev 1.63   Jan 26 2000 19:48:38   POPESCUS
 * quick fix
 * 
 *    Rev 1.62   Jan 26 2000 19:44:58   POPESCUS
 * fixes for th release
 * 
 *    Rev 1.61   Jan 25 2000 17:14:34   POPESCUS
 * fixes for validation of a new account
 * 
 *    Rev 1.60   Jan 23 2000 18:48:44   POPESCUS
 * changes related to creating a slsrep on the fly
 * 
 *    Rev 1.59   Jan 21 2000 16:44:34   YINGBAOL
 * change the way access other list
 * 
 *    Rev 1.58   Jan 21 2000 11:40:52   POPESCUS
 * fixes to the validation for the number
 * 
 *    Rev 1.57   Jan 21 2000 11:11:52   POPESCUS
 * the user can change the account number and the shareholder number
 * 
 *    Rev 1.56   Jan 19 2000 15:51:32   POPESCUS
 * validation
 * 
 *    Rev 1.55   Jan 17 2000 14:00:22   POPESCUS
 * support for refresh and misc
 * 
 *    Rev 1.54   Jan 16 2000 16:59:50   POPESCUS
 * changes to the children lists
 * 
 *    Rev 1.53   Jan 14 2000 15:06:56   YINGBAOL
 * add getCurrentAddress, acctDesignation  etc.
 * 
 *    Rev 1.52   Jan 10 2000 17:49:02   YINGBAOL
 * fix
 * 
 *    Rev 1.51   Jan 10 2000 13:59:40   POPESCUS
 * some fixes
 * 
 *    Rev 1.50   Jan 08 2000 14:33:06   POPESCUS
 * added the datagroupid when quering for children lists
 * 
 *    Rev 1.49   Jan 07 2000 12:09:34   ZHANGCEL
 * Change CLASS_FIELD_INFO and CLASS_OBJECT_INFO and misc
 * 
 *    Rev 1.48   Jan 06 2000 12:32:00   YINGBAOL
 * change
 * 
 *    Rev 1.47   Jan 05 2000 12:07:30   POPESCUS
 * changes..
 * 
 *    Rev 1.46   Jan 05 2000 11:51:26   POPESCUS
 * changes..
 * 
 *    Rev 1.45   Jan 05 2000 10:35:24   POPESCUS
 * changes related to the latest bfbase modifications
 * 
 *    Rev 1.44   Dec 31 1999 11:50:08   WINNIE
 * intialization for shrnummanual
 * 
 *    Rev 1.43   Dec 31 1999 09:35:34   YINGBAOL
 * added validation
 * 
 *    Rev 1.42   Dec 22 1999 18:00:40   BUZILA
 * added COA flags
 * 
 *    Rev 1.41   Dec 20 1999 11:06:48   BUZILA
 * added getTopLevelAncestor () method
 * 
 *    Rev 1.40   Dec 16 1999 17:04:06   PRAGERYA
 * Allocations initialization modified
 * 
 *    Rev 1.39   Dec 15 1999 11:08:14   POPESCUS
 * added new boolean param to the lists accessor methods; whether to inquire the database or not
 * 
 *    Rev 1.38   Dec 15 1999 10:38:20   PRAGERYA
 * Allocations stuff further modified
 * 
 *    Rev 1.37   Dec 13 1999 12:19:08   PRAGERYA
 * Allocation stuff modified, to pass in the work session ID and data group ID
 * 
 *    Rev 1.36   Dec 12 1999 16:25:56   POPESCUS
 * Xchgdata issue; create and delete the object in the CBO
 * 
 *    Rev 1.35   Dec 12 1999 15:24:48   PRAGERYA
 * Allocation stuff changed
 * 
 *    Rev 1.34   Dec 09 1999 10:43:40   POPESCUS
 * Fixed some memory leaks
*/

