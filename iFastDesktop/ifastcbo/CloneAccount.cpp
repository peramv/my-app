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
// ^FILE   : CloneAccount.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : October, 2006
//
// ^CLASS    : CloneAccount
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "cloneaccount.hpp"
#include <ifastdataimpl\dse_dstc0003_req.hpp>
#include <ifastdataimpl\dse_dstc0003_vw.hpp>
#include <ifastdataimpl\dse_dstc0004_vw.hpp>

#include "agent.hpp"
#include "agentlist.hpp"
#include "branch.hpp"
#include "branchlist.hpp"
#include "broker.hpp"
#include "brokerlist.hpp"
#include "demographics.hpp"
#include "grouplist.hpp"
#include "intermediarylist.hpp"
#include "mgmtco.hpp"
#include "mfaccount.hpp"
#include "shareholder.hpp"
#include "taxtyperule.hpp"
#include "taxtyperulelist.hpp"

namespace
{
   const I_CHAR * const CLASSNAME = I_("CloneAccount");
}

namespace ifds
{   
   extern CLASS_IMPORT const BFTextFieldId BrokerCode;
   extern CLASS_IMPORT const BFTextFieldId BranchCode;
   extern CLASS_IMPORT const BFTextFieldId SlsrepCode;
   extern CLASS_IMPORT const BFTextFieldId Slsrep;
   extern CLASS_IMPORT const BFTextFieldId AcctDesignation;
   extern CLASS_IMPORT const BFTextFieldId DuplicateAltAcct;
   extern CLASS_IMPORT const BFTextFieldId AltAccount;
   extern CLASS_IMPORT const BFTextFieldId TaxJurisCode;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFDateFieldId CurrSysDate;
   extern CLASS_IMPORT const BFDateFieldId BirthDate;
   extern CLASS_IMPORT const BFTextFieldId RepByBranch;
   extern CLASS_IMPORT const BFTextFieldId BrokerBranch;
   extern CLASS_IMPORT const BFTextFieldId BrokerName;
   extern CLASS_IMPORT const BFTextFieldId BranchName;
   extern CLASS_IMPORT const BFTextFieldId SlsrepName;
   extern CLASS_IMPORT const BFTextFieldId CreateRep;
//cross - edits
   extern CLASS_IMPORT const BFTextFieldId AcctDesignationTaxType;
}

namespace CND
{  // Conditions used
   extern const long ERR_SALES_CODE_CAN_NOT_LONGER_THAN_6;
   extern const long ERR_SALS_CODE_HAS_TO_BE_5;
   extern const long WAR_SALS_CODE_HAS_TO_BE_5;
   extern const long ERR_ACCT_TYPE_NOT_VALID_FOR_TAX_TYPE;
   extern const long ERR_WRONG_COMBINATION_TAXTYPE_JURISDICTION;
   extern const long ERR_NO_ALLOWED_FOR_AS_PENSION_PLAN;
   extern const long ERR_TAX_TYPE_NOT_FOR_ACCT_DESIGNATION;
   extern const long ERR_ACC_TAX_TYPE_NOT_MATCH;
   extern const long ERR_WARN_WRONG_COMBINATION_TAXTYPE_JURISDICTION;
   extern const long ERR_FEDERAL_JURISDICTION;
   extern const long ERR_NO_DATE_OF_BIRTH;
   extern const long ERR_NO_PENSION_INFORMATION;
   extern const long ERR_CLIENTS_AGE_BEYOND;
   extern const long ERR_NO_TAX_TYPE_RULES;
   extern const long ERR_WARN_DUPLICATE_ALTACCOUNT;
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest SEARCH;
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const SALESREPCODE_SHOULD_ONLY_BE_5_CHARACTERS;
}


//-------------------------------------------------------------------
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,                    State Flags,                  Group Flags    
   { ifds::BrokerCode,	            BFCBO::REQUIRED,              0 },
   { ifds::BranchCode,	            BFCBO::REQUIRED,	            0 },
   { ifds::SlsrepCode,	            BFCBO::REQUIRED,	            0 },
   { ifds::AccountNum,	            BFCBO::REQUIRED,	            0 },
   { ifds::InterCode,               BFCBO::NONE,                  0 },                              
   { ifds::InterAccount,            BFCBO::NONE,                  0 },
   { ifds::AltAccount,              BFCBO::NONE,                  0 },
   { ifds::ShrNum,	               BFCBO::REQUIRED,	            0 },
   { ifds::EffectiveDate,	         BFCBO::REQUIRED,	            0 },
   { ifds::TaxType,                 BFCBO::REQUIRED,              0 },
   { ifds::AcctDesignation,         BFCBO::REQUIRED,              0 },
   { ifds::BrokerName,	            BFCBO::NONE,                  0 },
   { ifds::BranchName,	            BFCBO::NONE,	               0 },
   { ifds::SlsrepName,	            BFCBO::NONE,	               0 },
   { ifds::CreateRep,               BFCBO::CALCULATED_FIELD,      0},  
   { ifds::AcctDesignationTaxType,  BFCBO::NONE,	               0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************************
CloneAccount::CloneAccount( BFAbstractCBO &parent )
: MFCanBFCbo (parent)

{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL );
   addCrossEdit (ifds::AcctDesignationTaxType, ifds::AcctDesignation);
   addCrossEdit (ifds::AcctDesignationTaxType, ifds::TaxType);
}
//******************************************************************************************
CloneAccount::~CloneAccount()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}     

//******************************************************************************************
SEVERITY CloneAccount::init ( const DString &accountNum,
                              const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   setField (ifds::AccountNum, accountNum, idDataGroup, false);
   setFieldNoValidate ( ifds::CreateRep, N, idDataGroup, false, 
                        true, 
                        false, 
                        false);
   DString date;

   getWorkSession().getOption (ifds::CurrBusDate, date, idDataGroup, false);
   setFieldNoValidate (ifds::EffectiveDate, date, idDataGroup, false, true, true);

//copy fields from account
   struct account_fields_to_copy
   {
      BFFieldId _account_field;
      BFFieldId _clone_account_field;
   }
   a_account_fields_to_copy [] = 
   {
      {ifds::ShrNum,          ifds::ShrNum},
      {ifds::AcctDesignation, ifds::AcctDesignation},
      {ifds::TaxType,         ifds::TaxType},
      {ifds::BrokerCode,      ifds::BrokerCode},
      {ifds::BranchCode,      ifds::BranchCode},
      {ifds::Slsrep,          ifds::SlsrepCode},
      {ifds::AltAccount,      ifds::AltAccount},
      {ifds::InterCode,       ifds::InterCode},
      {ifds::InterAccount,    ifds::InterAccount},
   };

   int num_fields = sizeof (a_account_fields_to_copy) / sizeof (account_fields_to_copy);

   for (int i = 0; i < num_fields; i++)
   {
      DString str;

      if (getAccountField ( a_account_fields_to_copy [i]._account_field, 
                            str, 
                            idDataGroup, 
                            false) <= WARNING)
      {
         setFieldNoValidate ( a_account_fields_to_copy [i]._clone_account_field, 
                              str, 
                              idDataGroup, 
                              false, 
                              false, 
                              true,
                              true);
      }
   }

   DString slsepByBranch;

   getWorkSession ().getOption ( ifds::RepByBranch, 
                                 slsepByBranch, 
                                 BF::HOST,
                                 false);
   if (slsepByBranch == N)
   {
      setFieldReadOnly (ifds::BranchCode, idDataGroup, true);
   }

   DString taxTypesList;
   TaxTypeRuleList *ptaxTypeRuleList (NULL);

   if ( getMgmtCo().getTaxTypeRuleList (ptaxTypeRuleList) <= WARNING &&
        ptaxTypeRuleList)
   {
      ptaxTypeRuleList->createTaxTypesList (taxTypesList);
      loadSubstitutionList (ifds::TaxType, idDataGroup, taxTypesList);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//***********************************************************************************
SEVERITY CloneAccount::doValidateField( const BFFieldId &idField,
                                        const DString &strValue,
                                        const BFDataGroupId &idDataGroup)

{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField"));
	
   if (idField == ifds::BrokerCode)
   {
      Broker *pBroker (NULL);

      if ( getBroker (pBroker, idDataGroup) <= WARNING &&
           pBroker)
      {
         DString dstrCurrBusDate;

         getWorkSession().getOption (ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false); 
         pBroker->checkEffective (dstrCurrBusDate, idDataGroup);
      }
   }
   else if (idField == ifds::BranchCode)
   {
      Branch *pBranch (NULL);

      if ( getBranch (pBranch, idDataGroup) <= WARNING &&
           pBranch)
      {
         DString dstrCurrBusDate;

         getWorkSession().getOption (ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false); 
         pBranch->checkEffective (dstrCurrBusDate, idDataGroup);
      }
   }
   else if (idField == ifds::SlsrepCode)
   {
      Agent* pAgent (NULL);

      if ( getAgent (pAgent, idDataGroup) <= WARNING &&
           pAgent)
      {
         if (strValue.size() >= 6)
         {
            getErrMsg ( IFASTERR::SALESREPCODE_SHOULD_ONLY_BE_5_CHARACTERS, 
                        CND::ERR_SALS_CODE_HAS_TO_BE_5, 
                        CND::WAR_SALS_CODE_HAS_TO_BE_5, 
                        idDataGroup); 
         }
	      if (GETCURRENTHIGHESTSEVERITY() <= WARNING && strValue.size() > 6)
	      {
            ADDCONDITIONFROMFILE (CND::ERR_SALES_CODE_CAN_NOT_LONGER_THAN_6);
	      }

         if (GETCURRENTHIGHESTSEVERITY() <= WARNING)
         {      
            DString dstrCurrBusDate;

            getWorkSession().getOption (ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false); 
            pAgent->checkEffective (dstrCurrBusDate, idDataGroup);
         }
      }
   }
   else if (idField == ifds::AcctDesignationTaxType)
   {
      validateAcctDesignationTaxType (idDataGroup);
   }
//validations copied from MFAccount...
   else if (idField == ifds::TaxType)
   {
      if ( strValue == I_("P") && //As pension plan
           DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA)
      {
	      ADDCONDITIONFROMFILE (CND::ERR_NO_ALLOWED_FOR_AS_PENSION_PLAN);
      }
      if (GETCURRENTHIGHESTSEVERITY() <= WARNING)
      {
         validateTaxType (strValue, idDataGroup);
      }
   }
   else if (idField == ifds::AltAccount)
   {
      DString duplicateAltAcct; 

      if ( !strValue.empty() && 
            getWorkSession().getOption (ifds::DuplicateAltAcct, duplicateAltAcct, idDataGroup, false) <= WARNING &&
            duplicateAltAcct == Y)
      {
         DString brokerCode;

         getField (ifds::BrokerCode, brokerCode, idDataGroup);
         brokerCode.strip();

         BFData requestData (ifds::DSTC0003_REQ);
         BFData *responseData = new BFData (ifds::DSTC0003_VW);

         DString mgmtCoIdOut;
         requestData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
         requestData.setElementValue (ifds::AllAccounts, Y);
         requestData.setElementValue (ifds::SortBy, I_("LN"));
         requestData.setElementValue (ifds::SrchAltAcct, strValue);
         requestData.setElementValue (ifds::SrchBroker, brokerCode);

         //should not request all the records for this warning; use 'false' for DSCRequestor
         if( BFDataBroker::getInstance()->receive( DSTC_REQUEST::SEARCH, 
                                                   requestData, 
                                                   *responseData, 
                                                   DSTCRequestor (getSecurity(), false)) <= WARNING)
         {
            DString numOfAcct;

            responseData->getElementValue (ifds::RepeatCount, numOfAcct);
            if (DSTCommonFunctions::convertToDouble (numOfAcct) > 0)
            {
               ADDCONDITIONFROMFILE (CND::ERR_WARN_DUPLICATE_ALTACCOUNT);
            }
            delete responseData;
            responseData = NULL;
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}


//*****************************************************************************************
SEVERITY CloneAccount::doApplyRelatedChanges ( const BFFieldId &idField, 
                                               const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_( "doApplyRelatedChanges"));

   if (idField == ifds::AcctDesignation)
   {
      DString acctDesignation;

      getField (ifds::AcctDesignation, acctDesignation, idDataGroup);
      
      bool bIsAcctDesignation = acctDesignation == I_("3");      
      DString interCodeList (I_( " = ;"));

      if (bIsAcctDesignation) 
      {
         IntermediaryList *pIntermediaryList (NULL);

         if ( getMgmtCo().getIntermediaryList (pIntermediaryList) <= WARNING &&
              pIntermediaryList)
         {
            pIntermediaryList->getInterCodeList (interCodeList, true);
            interCodeList.upperCase();
         }
      }
      setFieldAllSubstituteValues (ifds::InterCode, idDataGroup, interCodeList);
      setFieldRequired (ifds::InterCode, idDataGroup, bIsAcctDesignation);
      setFieldValid (ifds::InterCode, idDataGroup, !bIsAcctDesignation);
      setFieldReadOnly (ifds::InterCode, idDataGroup, !bIsAcctDesignation);
      if (!bIsAcctDesignation)
      {
//clear out the field         
         setFieldNoValidate (ifds::InterCode, NULL_STRING, idDataGroup, false, false, true);
      }
      //setFieldRequired (ifds::InterAccount, idDataGroup, bIsAcctDesignation);
      //setFieldValid (ifds::InterAccount, idDataGroup, !bIsAcctDesignation);
      setFieldReadOnly (ifds::InterAccount, idDataGroup, !bIsAcctDesignation);
      if (!bIsAcctDesignation)
      {
//clear out the field
         setFieldNoValidate (ifds::InterAccount, NULL_STRING, idDataGroup, false, false, true);
      }
   }
   else if (idField == ifds::BrokerCode)
   {
      setValidFlag (ifds::AltAccount, idDataGroup, false);

      setFieldNoValidate (ifds::BranchCode, NULL_STRING, idDataGroup, false, false, true, false);
      setFieldNoValidate (ifds::SlsrepCode, NULL_STRING, idDataGroup, false, false, true, false);
      setFieldNoValidate (ifds::BranchName, NULL_STRING, idDataGroup, false, false, true, false);
      setFieldNoValidate (ifds::SlsrepName, NULL_STRING, idDataGroup, false, false, true, false);

      Broker *pBroker (NULL);

      if ( getBroker (pBroker, idDataGroup) <= WARNING &&
           pBroker)
      {
         DString brokerName;

         pBroker->getField (ifds::BrokerName, brokerName, idDataGroup);
         setFieldNoValidate (ifds::BrokerName, brokerName, idDataGroup, false, false, true);

         DString slsepByBranch,
            brokerBranch,
            branchCode;

         getWorkSession ().getOption ( ifds::RepByBranch, 
                                       slsepByBranch, 
                                       BF::HOST,
                                       false);
         getWorkSession().getOption ( ifds::BrokerBranch, 
                                      brokerBranch, 
                                      BF::HOST, 
                                      false);

         if (slsepByBranch == N)
         {
            if (brokerBranch == Y)
            {
               getField (ifds::BrokerCode, branchCode, idDataGroup, false);
            }
            else
            {
               branchCode = I_("0000");
            }
            setFieldNoValidate (ifds::BranchCode, branchCode, idDataGroup, false, false, true, true);
         }
      }
   }
   else if (idField == ifds::BranchCode)
   {
      setFieldNoValidate (ifds::SlsrepCode, NULL_STRING, idDataGroup, false, false, true, false);
      setFieldNoValidate (ifds::SlsrepName, NULL_STRING, idDataGroup, false, false, true, false);

      Branch *pBranch (NULL);

      if ( getBranch (pBranch, idDataGroup) <= WARNING &&
           pBranch)
      {
         DString branchName;

         pBranch->getField (ifds::BranchName, branchName, idDataGroup);
         setFieldNoValidate (ifds::BranchName, branchName, idDataGroup, false, true, true, false);
      }
   }
   else if (idField == ifds::SlsrepCode)
   {
      Agent* pAgent (NULL);

      if ( getAgent (pAgent, idDataGroup) <= WARNING &&
           pAgent)
      {
         DString slsRepName;

         pAgent->getField (ifds::SlsrepName, slsRepName, idDataGroup);
         setFieldNoValidate (ifds::SlsrepName, slsRepName, idDataGroup, false, true, true, false);
         DString slsepByBranch,
            brokerBranch;

         getWorkSession ().getOption ( ifds::RepByBranch, 
                                       slsepByBranch, 
                                       BF::HOST,
                                       false);
         getWorkSession().getOption ( ifds::BrokerBranch, 
                                      brokerBranch, 
                                      BF::HOST, 
                                      false);
         if (slsepByBranch == N && brokerBranch == N)
         {
            DString branchCode;
            
            pAgent->getField (ifds::BranchCode, branchCode, idDataGroup);
            setFieldNoValidate (ifds::BranchCode, branchCode, idDataGroup, false, false, true, false);
            //also populate the branch name...
            Branch *pBranch (NULL);

            if ( getBranch (pBranch, idDataGroup) <= WARNING &&
                 pBranch)
            {
               DString branchName;

               pBranch->getField (ifds::BranchName, branchName, idDataGroup);
               setFieldNoValidate (ifds::BranchName, branchName, idDataGroup, false, true, true, false);
            }
         }
      }
   }
   else if (idField == ifds::CreateRep)
   {
      DString createRep;

      getField (ifds::CreateRep, createRep, idDataGroup, false);
      if (createRep == Y)
      {
//should re-validate the Slsrep field
         revalidateField (ifds::SlsrepCode, idDataGroup);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY CloneAccount::validateTaxType ( const DString &taxType, 
                                         const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateTaxType"));

   TaxTypeRule *ptaxTypeRule (NULL);

   if ( getTaxTypeRule (ptaxTypeRule, idDataGroup) <= WARNING && 
        ptaxTypeRule)
   {
//validate against account type
      DString acctType;

      if ( getAccountField (ifds::AcctType, acctType, idDataGroup) <= WARNING &&
           !acctType.empty())
      {
// if the account type is not valid account type under the tax type, then give error message
         if (!ptaxTypeRule->validAcctType (acctType, idDataGroup))
         {
            ADDCONDITIONFROMFILE (CND::ERR_ACCT_TYPE_NOT_VALID_FOR_TAX_TYPE) ;
         }
      }
//validate against pension juris
      if (GETCURRENTHIGHESTSEVERITY () <= WARNING)
      {
         if (getWorkSession ().isLIFLike (taxType) || 
			 getWorkSession ().isLIRALike (taxType) || 
			 DSTCommonFunctions::codeInList (taxType, I_("L,R"))) //LIF,LRIF,LIRA,PRIF 
         {
            DString pensionJuris;

            if ( getAccountField (ifds::PensionJuris, pensionJuris, idDataGroup) <= WARNING && 
                 !pensionJuris.empty())
            {
               if (!ptaxTypeRule->isValidPensionJurisdiction (pensionJuris, idDataGroup))
               {
                  ADDCONDITIONFROMFILE (CND::ERR_WRONG_COMBINATION_TAXTYPE_JURISDICTION);
               }
            }
         }
      }
//validate for RESP accts
      if (GETCURRENTHIGHESTSEVERITY () <= WARNING)
      {
         if (DSTCommonFunctions::codeInList (taxType, I_("M,9"))) //family RESP, individual RESP
         {
            GroupList* pGroupList (NULL);
            
            if ( getMgmtCo().getGroupList (pGroupList) <= WARNING && 
                 pGroupList)
            {
               DString acctGroup,
                  groupTaxType;
               
               getAccountField (ifds::AcctGroup, acctGroup, idDataGroup);
               if (pGroupList->getField (acctGroup, ifds::TaxType, groupTaxType, idDataGroup, false) <= WARNING)
               {
                  if (DSTCommonFunctions::codeInList (groupTaxType, I_("M,9")) && taxType != groupTaxType)
                  {
                     ADDCONDITIONFROMFILE (CND::ERR_ACC_TAX_TYPE_NOT_MATCH);
                  }
               }
            }
         }
      }
// check if RRSP or RRIF plan is offered by the province
      if (DSTCommonFunctions::codeInList (taxType, I_("1,2"))) // RRSP, RRIF
      {
         DString taxJurisCode;

         if (getShareholderField (ifds::TaxJurisCode, taxJurisCode, idDataGroup) <= WARNING)
         {
            if (!ptaxTypeRule->isValidPensionJurisdiction (taxJurisCode, idDataGroup))
            {
               DString idiStr, 
                  taxTypeDescr, 
                  pensionJurisName;

               getField (ifds::TaxType, taxTypeDescr, idDataGroup, true);
               getShareholderFieldDescription (ifds::TaxJurisCode, pensionJurisName, idDataGroup);
               addIDITagValue (idiStr, I_("TAXTYPE"), taxTypeDescr);
               addIDITagValue (idiStr, I_("TAXJURIS"), pensionJurisName);
               ADDCONDITIONFROMFILEIDI (CND::ERR_WARN_WRONG_COMBINATION_TAXTYPE_JURISDICTION, idiStr);
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY CloneAccount::validateAcctDesignationTaxType (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateAcctDesignationTaxType"));

   TaxTypeRule *ptaxTypeRule (NULL);

   if ( getTaxTypeRule (ptaxTypeRule, idDataGroup) <= WARNING && 
        ptaxTypeRule)
   {
//validate against account type
      DString taxType,
         acctDesignation;

      getField (ifds::TaxType, taxType, idDataGroup);
      getField (ifds::AcctDesignation, acctDesignation, idDataGroup);
      if (!taxType.empty () && !acctDesignation.empty())
      {
         if (!ptaxTypeRule->validAcctDesignation (acctDesignation, idDataGroup))
         {
            ADDCONDITIONFROMFILE (CND::ERR_TAX_TYPE_NOT_FOR_ACCT_DESIGNATION);
         }
         if (GETCURRENTHIGHESTSEVERITY() <= WARNING)
         {
            if (getWorkSession ().isLIFLike (taxType) || 
				getWorkSession ().isLIRALike (taxType) ||
				DSTCommonFunctions::codeInList (taxType, I_("L,R")) && //LIF,LRIF,LIRA,PRIF 
                 acctDesignation == I_("1")) //client
            {
               //get pensionJuris, fedJurAllowed
               DString pensionJuris,
                  lockedIn, 
                  fedJurisAllowed, 
                  taxTypeRules;

               getAccountField (ifds::PensionJuris, pensionJuris, idDataGroup);
               getAccountField (ifds::LockedIn, lockedIn, idDataGroup);
               getAccountField (ifds::FedJurisAllowed, fedJurisAllowed, idDataGroup);
               getAccountField (ifds::TaxTypeRules, taxTypeRules, idDataGroup);
               pensionJuris.strip().upperCase();
               lockedIn.strip().upperCase();
               fedJurisAllowed.strip().upperCase();
               taxTypeRules.strip().upperCase();

               if ( I_("9999") == pensionJuris && //federal country code
                     Y == lockedIn && 
                     N == fedJurisAllowed)
               {
                  ADDCONDITIONFROMFILE (CND::ERR_FEDERAL_JURISDICTION);
               }
               if ( pensionJuris > I_("0000") && 
                    Y == lockedIn &&
		              !ptaxTypeRule->doesTaxJurisdictionLimitationListExist (idDataGroup))
               {
                  ADDCONDITIONFROMFILE (CND::ERR_NO_TAX_TYPE_RULES);
               }
               if (GETCURRENTHIGHESTSEVERITY() <= WARNING)
               {
                  DString accountNum;
                  
                  getField (ifds::AccountNum, accountNum, idDataGroup, false);
                  if (!accountNum.empty()) 
                  {
                     MFAccount *pMFAccount = NULL;

                     if ( getWorkSession ().getMFAccount ( idDataGroup, 
                                                           accountNum, 
                                                           pMFAccount) <= WARNING && 
                        pMFAccount)
                     {
                        Demographics *pDemographics (NULL);

                        if (pMFAccount->getDemographicsList (pDemographics, idDataGroup) <= WARNING)
                        {
                           DString birthDate;
                           
                           pDemographics->getField (ifds::BirthDate, birthDate, idDataGroup);
                           if (Y == lockedIn && birthDate.empty())
                           {
                              ADDCONDITIONFROMFILE (CND::ERR_NO_DATE_OF_BIRTH);
                           }
                           if (GETCURRENTHIGHESTSEVERITY() <= WARNING)
                           {
                              DString defTaxTypeRules;

                              getAccountField (ifds::DefTaxTypeRules, defTaxTypeRules, idDataGroup);
                              defTaxTypeRules.strip().upperCase();
                              if (taxTypeRules == Y || defTaxTypeRules == Y)
                              {
                                 ADDCONDITIONFROMFILE (CND::ERR_NO_PENSION_INFORMATION);
                              }
                           }
                           if (GETCURRENTHIGHESTSEVERITY() <= WARNING)
                           {
                              DString strCurrentDate;
                              getWorkSession().getOption (ifds::CurrSysDate, strCurrentDate, idDataGroup, false);

                              //get minAge and maxAge
                              DString strMinAge,
                                 strMaxAge;
                              
                              getField (ifds::MinAge, strMinAge, idDataGroup);
                              getField (ifds::MaxAge, strMaxAge, idDataGroup);
                              int minAge = convertToULong (strMinAge),
                                 maxAge = convertToULong (strMaxAge);

                              //calculate age
                              int iAge;
                              DString strAge, 
                                 strMonth;
                              if (DSTCommonFunctions::BuildAge (birthDate, strCurrentDate, strAge, strMonth))
                              {
                                 strAge = NULL_STRING;
                              }
                              iAge = convertToULong (strAge);

                              if (!(minAge <= iAge && iAge <= maxAge))
                              {
                                 ADDCONDITIONFROMFILE (CND::ERR_CLIENTS_AGE_BEYOND);
                              }
                           }
                        }
                     }
                  }
               }
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//helpers
//******************************************************************************
SEVERITY CloneAccount::getAccountField ( const BFFieldId &idField, 
                                         DString &strValue,
                                         const BFDataGroupId &idDataGroup,
                                         bool formatted /*=false*/)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getAccountField"));
   DString accountNum;
   
   getField (ifds::AccountNum, accountNum, idDataGroup, false);
   if (!accountNum.empty()) 
   {
      MFAccount *pMFAccount = NULL;

      if ( getWorkSession ().getMFAccount ( idDataGroup, 
                                            accountNum, 
                                            pMFAccount) <= WARNING && 
           pMFAccount)
      {
         pMFAccount->getField (idField, strValue, idDataGroup, formatted);
      }
   }  
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY CloneAccount::getAccountFieldDescription ( const BFFieldId &idField, 
                                                    DString &value,
                                                    const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getAccountFieldDescription"));

   return getAccountField (idField, value, idDataGroup, true);
}

//******************************************************************************
SEVERITY CloneAccount::getShareholderField ( const BFFieldId &idField, 
                                             DString &strValue,
                                             const BFDataGroupId &idDataGroup,
                                             bool formatted /*=false*/)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getShareholderField"));
   Shareholder *pShareholder;
   DString shrNum;
   
   if ( getAccountField (ifds::ShrNum, shrNum, idDataGroup) <= WARNING &&
        !shrNum.empty())
   {
      if ( getWorkSession ().getShareholder (idDataGroup, shrNum, pShareholder) <= WARNING &&
           pShareholder)
      {
         pShareholder->getField (idField, strValue, idDataGroup, formatted);
      }
   }  
   return GETCURRENTHIGHESTSEVERITY ();
}

//***************************************************************************************************
SEVERITY CloneAccount::getShareholderFieldDescription ( const BFFieldId &idField, 
                                                        DString &strValue,
                                                        const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getShareholderField"));

   return getShareholderField (idField, strValue, idDataGroup, true);
}

//***************************************************************************************************
SEVERITY CloneAccount::getTaxTypeRule ( TaxTypeRule *&pTaxTypeRule, 
                                        const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getTaxTypeRule" ) );

   pTaxTypeRule = NULL;

   DString taxType;  

   getField (ifds::TaxType, taxType, idDataGroup, false );
   taxType.strip().upperCase();
   if (!taxType.empty())
   {      
      BFData data;
      TaxTypeRuleList *pTaxTypeRuleList (NULL);

      data.setElementValue (ifds::TaxType, taxType, true, NULL);
      if ( getMgmtCo().getTaxTypeRuleList (pTaxTypeRuleList) <= WARNING && 
           pTaxTypeRuleList)
      {
         DString positionKey;
         
         pTaxTypeRuleList->getStrKey (positionKey, &data);
         BFObjIter iterTaxType ( const_cast <TaxTypeRuleList &>(*pTaxTypeRuleList), 
                                 BF::HOST, 
                                 false, 
                                 BFObjIter::ITERTYPE::NON_DELETED);
         if (iterTaxType.positionByKey (positionKey))
         {
            pTaxTypeRule = dynamic_cast <TaxTypeRule*> (iterTaxType.getObject());
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY CloneAccount::getBroker ( Broker *&pBroker,
                                   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getBroker"));
   pBroker = NULL;

   DString brokerCode;

   getField (ifds::BrokerCode, brokerCode, idDataGroup, false);
   if (!brokerCode.empty())
   {
      DString strKey (I_("Broker=") + brokerCode);
//look for the list
      BrokerList *pBrokerList = 
            dynamic_cast <BrokerList*> (getObject ( strKey, 
                                                    idDataGroup));
      if (!pBrokerList) //make view call
      {
         pBrokerList = new BrokerList (*this);
         if (pBrokerList->init2 ( brokerCode, 
                                  NULL_STRING, 
                                  I_("L"),  //exact match
                                  NULL_STRING, 
                                  NULL_STRING) <= WARNING)
         {
            setObject ( pBrokerList,
                        strKey,
                        OBJ_ACTIVITY_NONE,
                        idDataGroup);
         }            
         else 
         {
            delete pBrokerList;
            pBrokerList = NULL;
         }
      }
//get the broker
      if (pBrokerList)
      {
         BFObjIter bfIter (*pBrokerList, idDataGroup);

         if (!bfIter.end())
         {
            pBroker = dynamic_cast <Broker*> (bfIter.getObject());
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY CloneAccount::getBranch ( Branch *&pBranch,
                                   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getBranch"));
   pBranch = NULL;

   DString brokerCode, 
      branchCode;

   getField (ifds::BrokerCode, brokerCode, idDataGroup, false);
   getField (ifds::BranchCode, branchCode, idDataGroup, false);
   if ( !brokerCode.empty() && 
        !branchCode.empty())
   {
      DString strKey 
            (I_("Broker=") + brokerCode + I_(";Branch=") + branchCode);

      BranchList* pBranchList = 
            dynamic_cast <BranchList*> (getObject (strKey, idDataGroup));
      if (!pBranchList) //make view call
      {
         pBranchList = new BranchList (*this);
         if (pBranchList->init ( brokerCode, //exact match
                                 branchCode) <= WARNING)
         {
            setObject ( pBranchList, 
                        strKey,
                        OBJ_ACTIVITY_NONE,
                        idDataGroup);
         }
         else 
         {
            delete pBranchList;
            pBranchList = NULL;
         }
      }
//get the branch
      if (pBranchList)
      {
         BFObjIter bfIter (*pBranchList, idDataGroup);

         bfIter.begin();
         if (!bfIter.end())
         {
            pBranch = dynamic_cast <Branch*> (bfIter.getObject());
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY CloneAccount::getAgent ( Agent *&pAgent,
                                  const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getAgent"));
   pAgent = NULL;

   DString brokerCode, 
      branchCode,
      slsrepCode,
      createRep;

   getField (ifds::CreateRep, createRep, idDataGroup, false);
   getField (ifds::BrokerCode, brokerCode, idDataGroup, false);
   getField (ifds::BranchCode, branchCode, idDataGroup, false);
   getField (ifds::SlsrepCode, slsrepCode, idDataGroup, false);
   if ( createRep == N &&
        !brokerCode.empty() && 
        !branchCode.empty() &&
        !slsrepCode.empty())
   {
      DString strKey ( I_("Broker=") + brokerCode + 
                       I_(";Branch=") + branchCode + 
                       I_(";Agent=") + slsrepCode);
      AgentList *pAgentList = dynamic_cast <AgentList*> 
                                      ( getObject ( strKey, 
                                                    idDataGroup));

      if (!pAgentList) //make view call
      {         
         pAgentList = new AgentList (*this);

         if (pAgentList->init ( brokerCode, //exact match
                                branchCode, 
                                slsrepCode) <= WARNING)
         {
            setObject ( pAgentList, 
                        strKey,
                        OBJ_ACTIVITY_NONE,
                        idDataGroup);
         }
         else
         {
            delete pAgentList;
            pAgentList = NULL;
         }
      }
//get the agent
      if (pAgentList)
      {
         BFObjIter bfIter (*pAgentList, idDataGroup);

         bfIter.begin();
         if (!bfIter.end())
         {
            pAgent = dynamic_cast <Agent*> (bfIter.getObject());
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/CloneAccount.cpp-arc  $
// 
//    Rev 1.7   Nov 28 2008 14:02:16   jankovii
// PET 142196 FN01 Federal Restricted LIF and LIRA.
// 
//    Rev 1.6   Nov 25 2008 11:14:46   jankovii
// PET 142196 FN01 Federal Restricted LIF and LIRA.
// 
//    Rev 1.5   Oct 08 2007 12:16:00   smithdav
// IN  1005517,1020252 - LRSP logic
// 
//    Rev 1.4   Dec 20 2006 18:10:22   popescu
// PET 2281/01 - fixed branch code default for env. where slsrepbybranch is turned off
// 
//    Rev 1.3   Dec 19 2006 14:12:26   popescu
// PET 2281/01 - fixed duplicate account warning
// 
//    Rev 1.2   Nov 27 2006 09:49:12   popescu
// Incident# 766137 - let the do apply related changes to take care of locking/unlocking the intermedairy fields
// 
//    Rev 1.1   Nov 10 2006 18:07:42   popescu
// PET 2281/FN 01
// 
//    Rev 1.0   Nov 08 2006 17:32:58   popescu
// Initial revision.
// 
//    Rev 1.10   Oct 20 2006 18:14:58   popescu
*/
