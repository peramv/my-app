//******************************************************************************
//
// COPYRIGHT:
//
// The computer systems, procedures, data bases and
// programs created and maintained by International Financial Data Services,
// are proprietary in nature and as such are confIdential.
// Any unauthorized use or disclosure of such information
// may result in civil liabilities.
//
// Copyright 2009 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : InvestorAuthorization.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : June, 2009
//
// ^CLASS    : InvestorAuthorization
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "InvestorAuthorization.hpp"
#include <ifastdataimpl\dse_dstc0004_vw.hpp>

#include <ifastdataimpl\dse_dstc0395_req.hpp>
#include <ifastdataimpl\dse_dstc0395_vw.hpp>

#include "agent.hpp"
#include "agentlist.hpp"
#include "branch.hpp"
#include "branchlist.hpp"
#include "broker.hpp"
#include "brokerlist.hpp"
#include "mfaccount.hpp"
#include "shareholder.hpp"
#include "shareholderbankinstructionslist.hpp"

#include <algorithm>

namespace
{
   const I_CHAR * const CLASSNAME               = I_( "InvestorAuthorization" );
   const I_CHAR * const NO                      = I_( "N" );
   const I_CHAR * const YES                     = I_( "Y" );
   const I_CHAR * const NON_REGISTERED_TAX_TYPE = I_ ("0");
   const I_CHAR * const CLIENT_ACCOUNT_TYPE     = I_ ("1");
}

namespace ifds
{
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFDateFieldId CurrSysDate;
   extern CLASS_IMPORT const BFTextFieldId DirectDepositBankApplicable;
   extern CLASS_IMPORT const BFTextFieldId RepByBranch;
   extern CLASS_IMPORT const BFTextFieldId BrokerBranch;
   extern CLASS_IMPORT const BFTextFieldId BrokerName;
   extern CLASS_IMPORT const BFTextFieldId BranchName;
   extern CLASS_IMPORT const BFTextFieldId SlsrepName;
   extern CLASS_IMPORT const BFTextFieldId CreateRep;
   extern CLASS_IMPORT const BFTextFieldId AcctUseCode;
   extern CLASS_IMPORT const BFTextFieldId EffectiveStopDate;
   extern CLASS_IMPORT const BFTextFieldId TaxType;
   extern CLASS_IMPORT const BFTextFieldId AcctType;
   extern CLASS_IMPORT const BFTextFieldId AcctDesignation;
}

namespace CND
{  // Conditions used
   extern const long ERR_INVALID_AUTH_VALUE;
   extern const long WARN_IA_BRK_BRNCH_SLSREP_NOT_SAME_WITH_ACCOUNT;
   extern const long ERR_SALES_CODE_CAN_NOT_LONGER_THAN_6;
   extern const long ERR_SALS_CODE_HAS_TO_BE_5;
   extern const long WAR_SALS_CODE_HAS_TO_BE_5;
   extern const long ERR_STOP_DATE_LESS_THAN_DEFF;
   extern const long ERR_DUPLICATE_RECORD;

   extern CLASS_IMPORT const long ERR_NO_BRANCH_FOUND;
   extern const long ERR_AGENT_NOT_FOUND_FOR_BROKER_BRANCH;
   extern const long WARN_DIRECT_DEPOSIT_BNK_INFO_MISSING;
   extern const long ERR_DIRECT_DEPOSIT_BNK_INFO_MISSING;
   extern const long ERR_INVESTOR_AUTHORIZATION_BEFORE_ACCT_EFFDATE;
   extern const long ERR_INVESTOR_AUTHORIZATION_INFO_FOR_CLNT_NON_REGIS_ONLY;
   extern const long ERR_INVESTOR_AUTHORIZATION_INFO_MISSING;
   extern const long WARN_INVESTOR_AUTHORIZATION_INFO_MISSING;
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const SALESREPCODE_SHOULD_ONLY_BE_5_CHARACTERS;
   extern CLASS_IMPORT I_CHAR * const DIRECT_DEPOSIT_BANK_FOR_INVESTOR_AUTHORIZE_MISSING;
   extern CLASS_IMPORT I_CHAR * const INVESTOR_AUTHORIZE_FOR_DIRECT_DEPOSIT_BANK_MISSING;
}

namespace AcctUseCode
{
   extern const I_CHAR * const DIRECT_DEPOSIT;
}

//-------------------------------------------------------------------
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
   // Field DD Id,                     State Flags,          Group Flags 
   { ifds::BrokerCode               , BFCBO::REQUIRED,            0 },
   { ifds::BranchCode               , BFCBO::NONE,                0 },
   { ifds::SlsrepCode               , BFCBO::REQUIRED,            0 },
   { ifds::EffectiveDate            , BFCBO::REQUIRED,            0 },
   { ifds::AccountNum               , BFCBO::REQUIRED,            0 },
   { ifds::IAFundIndicator          , BFCBO::NONE,                0 },
   { ifds::StopDate                 , BFCBO::NONE,                0 },
   { ifds::BrokerName               , BFCBO::NONE,                0 },
   { ifds::BranchName               , BFCBO::NONE,                0 },
   { ifds::SlsrepName               , BFCBO::NONE,                0 },
   { ifds::ProcessDate              , BFCBO::NONE,                0 },
   { ifds::Username                 , BFCBO::NONE,                0 },
   { ifds::ModDate                  , BFCBO::NONE,                0 },
   { ifds::ModUser                  , BFCBO::NONE,                0 },
   { ifds::AcctAuthVer              , BFCBO::NONE,                0 },
   { ifds::AcctAuthRid              , BFCBO::NONE,                0 },
   { ifds::CreateRep                , BFCBO::CALCULATED_FIELD,    0 },
   { ifds::EffectiveStopDate        , BFCBO::IMMEDIATE_VALIDATION,0 },

};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
struct BankingEffectivePeriod
{
   DString strEffectiveDate;
   DString strStopDate;
};

typedef std::vector<BankingEffectivePeriod> vBankingEffectivePeriod;

//******************************************************************************
bool InvestorAuthorization::sortByEffectiveDate(const BankingEffectivePeriod& input1, 
                                                const BankingEffectivePeriod& input2)
{
   DString strEffDate1 = input1.strEffectiveDate;
   DString strEffDate2 = input2.strEffectiveDate;

   DSTCommonFunctions::DATE_ORDER result = 
      DSTCommonFunctions::CompareDates( strEffDate1, strEffDate2 );

   if( result == DSTCommonFunctions::FIRST_EARLIER )
   {
      return true;
   }
   else if ( result == DSTCommonFunctions::EQUAL )
   {
      DString strStopDate1 = input1.strStopDate;
      DString strStopDate2 = input2.strStopDate;
      
      DSTCommonFunctions::DATE_ORDER result2 = 
         DSTCommonFunctions::CompareDates( strStopDate1, strStopDate2 );

      if( result2 == DSTCommonFunctions::FIRST_EARLIER )
      {
         return true;
      }
      else
      {
         return false;
      }
   }
   else
   {
      return false;
   }
}

//******************************************************************************************
InvestorAuthorization::InvestorAuthorization( BFAbstractCBO &parent )
: MFCanBFCbo( parent )

{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL );
   addCrossEdit (ifds::EffectiveStopDate, ifds::EffectiveDate);
   addCrossEdit (ifds::EffectiveStopDate, ifds::StopDate);
}

//******************************************************************************************
InvestorAuthorization::~InvestorAuthorization()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************************
SEVERITY InvestorAuthorization::init( const DString &accountNum )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   commonInit  ( accountNum, BF::HOST );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************************
SEVERITY InvestorAuthorization::init( const DString &accountNum, 
                                      const BFData& data)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   setField (ifds::AccountNum, accountNum, BF::HOST, false);
   setFieldNoValidate ( ifds::CreateRep, N, BF::HOST, false, 
                        true, 
                        false, 
                        false);

   DString slsepByBranch;

   getWorkSession ().getOption ( ifds::RepByBranch, 
                                 slsepByBranch, 
                                 BF::HOST,
                                 false);
   if (slsepByBranch == N)
   {
      setFieldReadOnly (ifds::BranchCode, BF::HOST, true);
   }

   attachDataObject( const_cast< BFData& >( data ), false, true );
   DString strBrokerCode, 
      strBranchCode, 
      strSlsrepCode;

//to force setting the names...   
   data.getElementValue (ifds::BrokerCode, strBrokerCode);
   data.getElementValue (ifds::BranchCode, strBranchCode);
   data.getElementValue (ifds::SlsrepCode, strSlsrepCode);
   
   strBrokerCode.strip();
   strBranchCode.strip();
   strSlsrepCode.strip();
   setFieldNoValidate (ifds::BrokerCode, strBrokerCode, BF::HOST, false, true, true, true);
   setFieldNoValidate (ifds::BranchCode, strBranchCode, BF::HOST, false, true, true, true);
   setFieldNoValidate (ifds::SlsrepCode, strSlsrepCode, BF::HOST, false, true, true, true); 
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************************
SEVERITY InvestorAuthorization::initNew ( const DString &accountNum,
                                          const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   commonInit ( accountNum, idDataGroup );
   setNonDummyFlag ();
   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************************
SEVERITY InvestorAuthorization::commonInit ( const DString &accountNum,
                                             const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("commonInit"));

   setField (ifds::AccountNum, accountNum, idDataGroup, false);
   setFieldNoValidate ( ifds::CreateRep, N, idDataGroup, false, 
                        true, 
                        false, 
                        false);
   
   setFieldNoValidate (ifds::IAFundIndicator, I_("A"), 
                       idDataGroup, 
                       false, 
                       true, 
                       true, 
                       false);
   DString date;

   getWorkSession().getOption (ifds::CurrBusDate, date, idDataGroup, false);
   setFieldNoValidate (ifds::EffectiveDate, date, idDataGroup, false, true, true);

   //stop date
   DString stopDate;

   getField (ifds::StopDate, stopDate, idDataGroup, false);
   if (stopDate.empty())
   {
      getWorkSession ().getDateInHostFormat ( stopDate, 
                                              DSTCWorkSession::DATE_TYPE::DAY12319999, 
                                              idDataGroup);
      setFieldNoValidate (ifds::StopDate, stopDate, idDataGroup, false, true, true);
   }
   
   //copy fields from account
   struct account_fields_to_copy
   {
      BFFieldId _account_field;
      BFFieldId _clone_account_field;
   }
   a_account_fields_to_copy [] = 
   {
      {ifds::BrokerCode,      ifds::BrokerCode},
      {ifds::BranchCode,      ifds::BranchCode},
      {ifds::Slsrep,          ifds::SlsrepCode},
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

   return GETCURRENTHIGHESTSEVERITY();
}

//***********************************************************************************
SEVERITY InvestorAuthorization::doValidateField( const BFFieldId& idField, 
                                                 const DString& strValue, 
                                                 const BFDataGroupId& idDataGroup )

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField" ));
   
   if (idField == ifds::BrokerCode)
   {
      Broker *pBroker (NULL);

      if ( getBroker (pBroker, idDataGroup) <= WARNING &&
           pBroker)
      {
         DString strEffectiveDate;

         getField( ifds::EffectiveDate, strEffectiveDate, idDataGroup, false );
         pBroker->checkEffective (strEffectiveDate, idDataGroup);
      }
   }
   else if (idField == ifds::BranchCode)
   {
      Branch *pBranch (NULL);

      if ( getBranch (pBranch, idDataGroup) <= WARNING &&
           pBranch)
      {
         DString strEffectiveDate;

         getField( ifds::EffectiveDate, strEffectiveDate, idDataGroup, false );
         pBranch->checkEffective (strEffectiveDate, idDataGroup);
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
            DString strEffectiveDate;

            getField (ifds::EffectiveDate, strEffectiveDate, idDataGroup, false);
            pAgent->checkEffective (strEffectiveDate, idDataGroup);
         }
      }
   }
   else if ( idField == ifds::EffectiveDate )
   {
      validateEffectiveDate( idDataGroup );
   }
   else if ( idField == ifds::StopDate )
   {
      validateStopDate( idDataGroup );
   }
   else if (idField == ifds::EffectiveStopDate)  //cross edit
   {
      DString effectiveDate, 
         stopDate;

      getField (ifds::StopDate, stopDate, idDataGroup, false);
      getField (ifds::EffectiveDate, effectiveDate, idDataGroup, false);

      if (DSTCommonFunctions::CompareDates (stopDate, effectiveDate) == DSTCommonFunctions::FIRST_EARLIER)
      {
         ADDCONDITIONFROMFILE (CND::ERR_STOP_DATE_LESS_THAN_DEFF);
      }
      if (GETCURRENTHIGHESTSEVERITY() <= WARNING)
      {
         //check for overlapped records
         assert (getParent ());
         if (getParent () != NULL)
         {
            BFObjIter iterList (*getParent (), idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED);

            while (!iterList.end ())
            {
               InvestorAuthorization *pInvestorAuthorization = 
                  dynamic_cast <InvestorAuthorization*> (iterList.getObject ());

               if (pInvestorAuthorization && pInvestorAuthorization != this)
               {
                  DString _effectiveDate, 
                     _stopDate;

                  pInvestorAuthorization->getField (ifds::EffectiveDate, _effectiveDate, idDataGroup, false);
                  pInvestorAuthorization->getField (ifds::StopDate, _stopDate, idDataGroup, false);
                  if (DSTCommonFunctions::CompareDates (stopDate, _effectiveDate) == DSTCommonFunctions::FIRST_EARLIER ||
                      DSTCommonFunctions::CompareDates (_stopDate, effectiveDate) == DSTCommonFunctions::FIRST_EARLIER)
                  {
                     ; //no overlapping
                  }
                  else
                  {
                     ADDCONDITIONFROMFILE (CND::ERR_DUPLICATE_RECORD);
                     break;
                  }
               }
               ++iterList;
            }
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************************
SEVERITY InvestorAuthorization::doApplyRelatedChanges( const BFFieldId& idField, 
                                                       const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_( "doApplyRelatedChanges"));

   if (idField == ifds::BrokerCode)
   {
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
   else if (idField == ifds::EffectiveDate || idField == ifds::StopDate)
   {
//invalidate the broker branch and sls rep
      setFieldValid (ifds::BrokerCode, idDataGroup, false);
      setFieldValid (ifds::BranchCode, idDataGroup, false);
      setFieldValid (ifds::SlsrepCode, idDataGroup, false);
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************************
SEVERITY InvestorAuthorization::validateEffectiveDate( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "validateEffectiveDate" ) );

   DString strEffectiveDate,strAcctEffDate;

   getField( ifds::EffectiveDate, strEffectiveDate, idDataGroup, false ); 
   getAccountField( ifds::EffectiveDate, strAcctEffDate, idDataGroup, false );
   
   if ( DSTCommonFunctions::CompareDates( strEffectiveDate, strAcctEffDate ) == 
        DSTCommonFunctions::FIRST_EARLIER )
   {
      ADDCONDITIONFROMFILE (CND::ERR_INVESTOR_AUTHORIZATION_BEFORE_ACCT_EFFDATE);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************************
SEVERITY InvestorAuthorization::validateStopDate( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "validateStopDate" ) );
                          
   return(GETCURRENTHIGHESTSEVERITY());
}

//helpers
//******************************************************************************
SEVERITY InvestorAuthorization::getAccountField ( const BFFieldId &idField, 
                                                  DString &strValue,
                                                  const BFDataGroupId &idDataGroup,
                                                  bool formatted /*=false*/)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getAccountField"));
   DString accountNum;

   getField ( ifds::AccountNum, accountNum, idDataGroup, false );
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
SEVERITY InvestorAuthorization::getBroker ( Broker *&pBroker,
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
SEVERITY InvestorAuthorization::getBranch ( Branch *&pBranch,
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
SEVERITY InvestorAuthorization::getAgent ( Agent *&pAgent,
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
      else // agent is not found 
      {
         int count = CONDITIONCOUNT();
         Condition   *c = NULL;
         for( int i = 0; i < count; i++ )
         {
            c = GETCONDITION( i );
            int condCode = c->getCode();
            if ( condCode == CND::ERR_NO_BRANCH_FOUND )
            {
               CLEARCONDITION( i );
               break;
            }
         }

         DString idiStr;
         addIDITagValue( idiStr, I_("AGENT"), slsrepCode.upperCase() );
         addIDITagValue( idiStr, I_("BROKER"), brokerCode.upperCase() );
         addIDITagValue( idiStr, I_("BRANCH"), branchCode.upperCase() );
         ADDCONDITIONFROMFILEIDI( CND::ERR_AGENT_NOT_FOUND_FOR_BROKER_BRANCH, idiStr.c_str() ); 
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY InvestorAuthorization::doValidateAll( const BFDataGroupId& idDataGroup, 
                                               long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doValidateAll"));
                           
   DString dstrDirectDepositBankApplicable,
            dstrAcctUseCode;
   getWorkSession ().getOption ( ifds::DirectDepositBankApplicable, 
                                 dstrDirectDepositBankApplicable, 
                                 BF::HOST, false);


   // validate account related , only client/non-register allowed to 
   // setup investor authorization
   DString strAcctDesignation, strAcctTaxType;
   getAccountField (ifds::AcctDesignation, strAcctDesignation, idDataGroup, false);
   getAccountField (ifds::TaxType, strAcctTaxType, idDataGroup, false);

   if ( strAcctTaxType != NON_REGISTERED_TAX_TYPE || strAcctDesignation != CLIENT_ACCOUNT_TYPE )
   {
      ADDCONDITIONFROMFILE( CND::ERR_INVESTOR_AUTHORIZATION_INFO_FOR_CLNT_NON_REGIS_ONLY );
      return GETCURRENTHIGHESTSEVERITY ();
   }

   DString effectiveDate, stopDate, currBusDate;

   getWorkSession().getOption (ifds::CurrBusDate, currBusDate, idDataGroup, false);
   getField (ifds::EffectiveDate, effectiveDate, idDataGroup, false);
   getField (ifds::StopDate, stopDate, idDataGroup, false);

   //if the record is active perform the following checks...
   if (DSTCommonFunctions::IsDateBetween (effectiveDate, stopDate, currBusDate))
   {
      DString acctBroker,
         acctBranch,
         acctSlsRep,
         broker,
         branch,
         slsrep;
      
      getField (ifds::BrokerCode, broker, idDataGroup, false);
      getField (ifds::BranchCode, branch, idDataGroup, false);
      getField (ifds::SlsrepCode, slsrep, idDataGroup, false);
   //account level fields
      
      if ( getAccountField (ifds::BrokerCode, acctBroker, idDataGroup, false) <= WARNING &&
           getAccountField (ifds::BranchCode, acctBranch, idDataGroup, false) <= WARNING &&
           getAccountField (ifds::Slsrep, acctSlsRep, idDataGroup, false) <= WARNING)
      {
         if (broker != acctBroker || 
             branch != acctBranch ||
             slsrep != acctSlsRep)
         { 
            //PET 156681.FN14.R03
            //raise warning that the investor authorization dealer codes are different then the account ones.
            ADDCONDITIONFROMFILE (CND::WARN_IA_BRK_BRNCH_SLSREP_NOT_SAME_WITH_ACCOUNT);
         }
      }

      //if the record is active then check if there are banking instructions active, 
      //if not raise warning depnd on system severity setup.
      validateAgainstDDBankEffPeriod(idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY InvestorAuthorization::validateAgainstDDBankEffPeriod(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateAgainstDDBankEffPeriod"));

   DString shrNum, strIAEffDate, strIAStopDate,currBusDate;;

   getField( ifds::EffectiveDate, strIAEffDate, idDataGroup, false );
   getField( ifds::StopDate, strIAStopDate, idDataGroup, false );
   getWorkSession().getOption (ifds::CurrBusDate, currBusDate, idDataGroup, false);

   if (getAccountField (ifds::ShrNum, shrNum, idDataGroup, false) <= WARNING)
   {
      Shareholder *pShareholder = NULL;

      if ( getWorkSession().getShareholder (idDataGroup, shrNum, pShareholder) <= WARNING && 
            pShareholder)
      {
         ShareholderBankInstructionsList *pShareholderBankInstructionsList = NULL;
         bool bDirectDepositBankInstructions = false;
         bool bMisingIA = false;

         std::vector<DString> vDateList;
         if ( pShareholder->getShareholderBankInstructionsList ( pShareholderBankInstructionsList, 
                                                                  idDataGroup) <= WARNING &&
               pShareholderBankInstructionsList)
         {
            BFObjIter iter ( *pShareholderBankInstructionsList, 
                              idDataGroup);

            if ( iter.getNumberOfItemsInList() == 0)
            {
               vDateList.push_back( strIAEffDate );
            }
            else
            {
               vBankingEffectivePeriod bankingEffectivePeriods;
               bool bDirectDepositBankInstructions = false;

               while (!iter.end())
               {
                  DString strBankEffDate, strBankStopDate, bankAcctUseCode_;
                  iter.getObject()->getField( ifds::EffectiveDate, strBankEffDate, idDataGroup, false );
                  iter.getObject()->getField (ifds::StopDate, strBankStopDate, idDataGroup, false);
                  iter.getObject()->getField (ifds::AcctUseCode, bankAcctUseCode_, idDataGroup, false);

                  if ( bankAcctUseCode_ == AcctUseCode::DIRECT_DEPOSIT ) //is direct deposit 
                  {
                     BankingEffectivePeriod newElement;
                     newElement.strEffectiveDate = strBankEffDate;
                     newElement.strStopDate = strBankStopDate;

                     bankingEffectivePeriods.push_back(newElement);
                     bDirectDepositBankInstructions = true;
                  }
                  ++iter;
               }

               if ( iter.getNumberOfItemsInList() > 1)
               {
                  sort(bankingEffectivePeriods.begin(), 
                     bankingEffectivePeriods.end(), 
                     InvestorAuthorization::sortByEffectiveDate );
               }

               if ( bDirectDepositBankInstructions )
               {
                  vBankingEffectivePeriod::iterator iterBankingEffectivePeriods = 
                     bankingEffectivePeriods.begin();

                  // make long period
                  while( iterBankingEffectivePeriods     != bankingEffectivePeriods.end() &&
                        iterBankingEffectivePeriods + 1 != bankingEffectivePeriods.end() )
                  {
                     DString strBankEffDate, strBankStopDate, strBankNxtEffDate, strBankNxtStopDate;

                     BankingEffectivePeriod bankEffPeriod = *(iterBankingEffectivePeriods);
                     BankingEffectivePeriod bankNxtEffPeriod = *(iterBankingEffectivePeriods+1);

                     strBankEffDate = bankEffPeriod.strEffectiveDate;
                     strBankStopDate = bankEffPeriod.strStopDate;
                     strBankNxtEffDate = bankNxtEffPeriod.strEffectiveDate;
                     strBankNxtStopDate = bankNxtEffPeriod.strStopDate;

                     DString strTestDate;
                     DSTCommonFunctions::addDays(strBankStopDate,strTestDate,1);
                     if( DSTCommonFunctions::CompareDates( strTestDate, strBankNxtEffDate ) == 
                           DSTCommonFunctions::EQUAL )
                     {
                        iterBankingEffectivePeriods->strEffectiveDate = strBankEffDate;
                        iterBankingEffectivePeriods->strStopDate = strBankNxtStopDate;
                        bankingEffectivePeriods.erase(iterBankingEffectivePeriods+1);

                        continue;
                     }
                     ++iterBankingEffectivePeriods;
                  }

                  iterBankingEffectivePeriods = bankingEffectivePeriods.begin();
                  while( iterBankingEffectivePeriods != bankingEffectivePeriods.end() )
                  {
                     DString strBankEffDate, strBankStopDate, strBankNextStopDate;

                     BankingEffectivePeriod bankEffPeriod = *(iterBankingEffectivePeriods);

                     strBankEffDate = bankEffPeriod.strEffectiveDate;
                     strBankStopDate = bankEffPeriod.strStopDate;

                     if ( DSTCommonFunctions::IsDateBetween( strIAEffDate, strIAStopDate, strBankEffDate ) && 
                           DSTCommonFunctions::CompareDates( strIAEffDate, strBankEffDate ) == 
                           DSTCommonFunctions::FIRST_EARLIER )
                     {
                        vDateList.push_back( strIAEffDate );
                        bMisingIA = false;
                        break;
                     }
                     else if ( DSTCommonFunctions::IsDateBetween( strIAEffDate, strIAStopDate, strBankStopDate ) && 
                                 DSTCommonFunctions::CompareDates( strIAStopDate, strBankStopDate ) == 
                                 DSTCommonFunctions::SECOND_EARLIER )
                     {
                        DSTCommonFunctions::addDays(strBankStopDate,strBankNextStopDate,1);
                        vDateList.push_back( strBankNextStopDate );
                        bMisingIA = false;
                        break;
                     }
                     else if ( DSTCommonFunctions::IsDateBetween( strBankEffDate, strBankStopDate, strIAEffDate ) && 
                                 DSTCommonFunctions::CompareDates( strIAEffDate, strBankEffDate ) == 
                                 DSTCommonFunctions::SECOND_EARLIER )
                     {
                        vDateList.push_back( strBankEffDate );
                        bMisingIA = true;
                        break;
                     }

                     ++iterBankingEffectivePeriods;
                  }
               }
               else
               {
                  // account has shareholder banking instruction list
                  // but none of them is direct deposit banking 
                  // therefore error would be riased
                  vDateList.clear();
                  vDateList.push_back( strIAEffDate );
               }
            }
         }

         // after cleaning, if there is still date existing in list 
         // it should be displayed as begining of gap, logic is similar with banking part
         if ( vDateList.size() > 0 )
         {
            //PET156681.FN14.R03.2
            // soft warning message should be displayed when modifying 
            // an Investor Authorization record with an inactive Bank Instruction.
            std::vector<DString>::iterator itDateLists = vDateList.begin();

            DString strErrorDateFmt = *(itDateLists); // get only first of list to display
            DSTCommonFunctions::FormatDate(strErrorDateFmt);
            DString dstrIDI;
            addIDITagValue (dstrIDI, I_("DATE"), strErrorDateFmt);
            if ( !bMisingIA )
            {
               getErrMsg ( IFASTERR::DIRECT_DEPOSIT_BANK_FOR_INVESTOR_AUTHORIZE_MISSING, 
                           CND::ERR_DIRECT_DEPOSIT_BNK_INFO_MISSING, 
                           CND::WARN_DIRECT_DEPOSIT_BNK_INFO_MISSING, 
                           idDataGroup, 
                           dstrIDI);
            }
            else
            {
               getErrMsg ( IFASTERR::INVESTOR_AUTHORIZE_FOR_DIRECT_DEPOSIT_BANK_MISSING, 
                           CND::ERR_INVESTOR_AUTHORIZATION_INFO_MISSING, 
                           CND::WARN_INVESTOR_AUTHORIZATION_INFO_MISSING, 
                           idDataGroup, 
                           dstrIDI);
            }
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
bool InvestorAuthorization::isResetRecord(const BFDataGroupId& idDataGroup)
{
   DString strBrokerCode,
           strBranchCode,
           strSlsrepCode,
           strIAFundIndicator,
           strEffectiveDate,
           strStopDate,
           strAcctAuthVer,
           strAcctAuthRid;

   getField (ifds::BrokerCode,strBrokerCode,idDataGroup,false);
   getField (ifds::BranchCode,strBranchCode,idDataGroup,false);
   getField (ifds::SlsrepCode,strSlsrepCode,idDataGroup,false);
   getField (ifds::IAFundIndicator,strIAFundIndicator,idDataGroup,false);
   getField (ifds::EffectiveDate,strEffectiveDate,idDataGroup,false);
   getField (ifds::StopDate,strStopDate,idDataGroup,false);
   getField (ifds::AcctAuthVer,strAcctAuthVer,idDataGroup,false);
   getField (ifds::AcctAuthRid,strAcctAuthRid,idDataGroup,false);
   strBrokerCode.strip().upperCase();
   strBranchCode.strip().upperCase();
   strSlsrepCode.strip().upperCase();
   strIAFundIndicator.strip().upperCase();
   strAcctAuthVer.strip().upperCase();
   strAcctAuthRid.strip().upperCase();
   
   if ( strBrokerCode.empty() && strSlsrepCode.empty() && 
        strIAFundIndicator == I_("A") && 
        strEffectiveDate.empty() && strStopDate.empty() && 
        ( strAcctAuthVer.empty() || (!strAcctAuthVer.empty() && strAcctAuthVer == I_("0"))) && 
        ( strAcctAuthRid.empty() || (!strAcctAuthRid.empty() && strAcctAuthRid == I_("0"))) )
   {
      return true;
   }
   else
   {
      return false;
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/InvestorAuthorization.cpp-arc  $
// 
//    Rev 1.12   Nov 20 2009 02:03:04   dchatcha
// IN# 1896780 - Inactive Banking Warning Message. More cases.
// 
//    Rev 1.11   Nov 17 2009 14:50:04   dchatcha
// IN# 1896780 - Inactive Banking Warning Message, this logic 'd display IA effective date.
// 
//    Rev 1.10   Nov 16 2009 05:49:08   dchatcha
// IN# 1896780 - Inactive Banking Warning Message
// 
//    Rev 1.9   Oct 19 2009 04:06:00   dchatcha
// IN# 1864779 - Rel95_PET156681_dlr_rep code, Fix issue found when reset button is pressed
// 
//    Rev 1.8   Oct 09 2009 04:26:54   dchatcha
// IN# 1864779 - Rel95_PET156681_dlr_rep code, Code review.
// 
//    Rev 1.7   Oct 08 2009 10:34:54   dchatcha
// IN# 1864779 - Rel95_PET156681_dlr_rep code.
// 
//    Rev 1.6   23 Jul 2009 12:58:30   popescu
// PET156681 FN14 H36 Investor Authorization, some more fixes
// 
//    Rev 1.5   22 Jul 2009 18:06:12   popescu
// PET156681 FN14 H36 Investor Authorization - clean-up various fixes.
// 
//    Rev 1.4   Jul 22 2009 08:50:04   dchatcha
// PET156681 FN14 H36 Investor Authorization, Code review. 
// 
//    Rev 1.3   Jul 16 2009 19:42:34   dchatcha
// PET156681 FN14 H36 Investor Authorization, Integration issues.
// 
//    Rev 1.2   Jul 09 2009 23:38:10   dchatcha
// PET156681 FN14 H36 Investor Authorization,Fix compile error.
// 
//    Rev 1.1   Jul 09 2009 15:47:30   dchatcha
// PET156681 FN14 H36 Investor Authorization.
// 
//    Rev 1.0   29 Jun 2009 16:25:52   popescu
// Initial revision.
*/
