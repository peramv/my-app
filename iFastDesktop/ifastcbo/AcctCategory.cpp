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
//    Copyright 1999 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : AcctCategory.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : Jan. 21/2003
//
// ^CLASS    : AcctCategory
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "acctcategory.hpp"
#include "agentlist.hpp"
#include "brokerlist.hpp"
#include "mfaccount.hpp"
#include "pendingtradedetails.hpp"
#include "pendingtradelist.hpp"
#include "mgmtco.hpp"
#include "taxtyperule.hpp"
#include "fundmasterlist.hpp"
#include "broker.hpp"
#include "shareholder.hpp"

#include <ifastdataimpl\dse_dstc0245_vwrepeat_record.hpp>

namespace
{
   const I_CHAR * const CLASSNAME = I_( "AcctCategory" );


   const I_CHAR * const YES                             = I_( "Y" );
   const I_CHAR * const NO                              = I_( "N" );

   const I_CHAR * const CLIENT_ACCT_DESIGNATION         = I_( "1" );  
   const I_CHAR * const NON_REGISTERED_TAX_TYPE         = I_( "0" ); 
   const I_CHAR * const RRSP_TAX_TYPE                   = I_( "1" ); 
   const I_CHAR * const RRIF_TAX_TYPE                   = I_( "2" ); 

   const I_CHAR * const WRAP_VALIDATION                 = I_( "WrapFunds" ); 
   const int FULL_LIST = 0;
   const I_CHAR * const INDIVIDUAL_ACCT_TYPE            = I_( "0" );
   const I_CHAR * const SPOUSAL_ACCT_TYPE               = I_( "1" );
   const I_CHAR * const JOINT_ACCT_TYPE                 = I_( "2" );
   const I_CHAR * const TRUST_ACCT_TYPE                 = I_( "3" );
   const I_CHAR * const CORPORATE_ACCT_TYPE             = I_( "4" );
   const I_CHAR * const LOCKED_IN_ACCT_TYPE             = I_( "5" );
   const I_CHAR * const OMNIBUS_ACCT_TYPE               = I_( "6" );
   const I_CHAR * const PENSION_FUND_ACCT_TYPE          = I_( "7" );
   const I_CHAR * const ESTATE_ACCT_TYPE                = I_( "8" );
   const I_CHAR * const ASSOCIATION_ACCT_TYPE           = I_( "9" );
   const I_CHAR * const FINANCIAL_CORPORATION_ACCT_TYPE = I_( "F" );
   const I_CHAR * const GENERAL_CORPORATION_ACCT_TYPE   = I_( "G" );
   const I_CHAR * const NI_31_103_STMT                  = I_( "NISTMT" );  // statement and confirm   
}

namespace ACCOUNT_CATEGORY
{
   extern CLASS_EXPORT I_CHAR * const LOAN                        = I_( "01" );
   extern CLASS_EXPORT I_CHAR * const MARGIN                      = I_( "02" );
   extern CLASS_EXPORT I_CHAR * const CHEQUE_PRIVILEGE            = I_( "03" );
   extern CLASS_EXPORT I_CHAR * const WRAP                        = I_( "04" );
   extern CLASS_EXPORT I_CHAR * const PRIVATE                     = I_( "36" );
   extern CLASS_EXPORT I_CHAR * const SWIFT_PAYMENT_METHOD        = I_( "38" ); 

   extern CLASS_EXPORT I_CHAR * const MT202                       = I_( "02" );
   extern CLASS_EXPORT I_CHAR * const MT103                       = I_( "01" );
   extern CLASS_EXPORT I_CHAR * const FUND_ON_FUND                = I_( "24" ); //fund on fund
   extern CLASS_EXPORT I_CHAR * const ESTATE                      = I_( "52" );
   extern CLASS_EXPORT I_CHAR * const DEATH_OF_NOTIFICATION       = I_( "51" );
   extern CLASS_EXPORT I_CHAR * const CLIENT_MONTHLY_STATEMENT    = I_( "54" ); // statement and confirm
   extern CLASS_EXPORT I_CHAR * const HST_EXCEPTION               = I_( "56" );
   extern CLASS_EXPORT I_CHAR * const EPA_APP                     = I_( "57" );
   extern CLASS_EXPORT I_CHAR * const MULTI_MANAGER               = I_( "58" );
   extern CLASS_EXPORT I_CHAR * const DEBIT_SWIFT_PAYMENT_METHOD  = I_( "59" );
   extern CLASS_EXPORT I_CHAR * const PRIVATE_WEALTH_OPT_OUT      = I_( "63" );
   extern CLASS_EXPORT I_CHAR * const GARS1                       = I_( "64" );
   extern CLASS_EXPORT I_CHAR * const GARS2                       = I_( "65" );
   extern CLASS_EXPORT I_CHAR * const GARS3                       = I_( "66" );
   extern CLASS_EXPORT I_CHAR * const GARSDA                      = I_( "67" );

}

namespace CND
{  // Conditions used
   extern const long ERR_CANNOT_MODIFY_ACCT_FEATURE;
   extern const long ERR_CLIENT_NON_REG_MARGIN_ACCT;
   extern const long ERR_CLIENT_RRSP_RRIF_LOAN_ACCT;
   extern const long ERR_MARGIN_CANNOT_BE_REMOVED;
   extern const long ERR_MARGIN_ONLY_FOR_NEW_ACCOUNT;
   extern const long ERR_MARGIN_PENDING_NOT_ELIGIBLE;
   extern const long ERR_WRAP_CANNOT_BE_REMOVED;
   extern const long WARN_PRIVATE_ACCOUNT_ACTEGORY_ONLY_FOR_CLIENT;
   extern const long ERR_PRIVATE_ACCOUNT_ACTEGORY_ONLY_FOR_CLIENT;
   //fund on fund
   extern const long ERR_INVALID_FUND_CODE_FOR_ACCT_CATEGORY_FUND_ON_FUND;
   extern const long ERR_REQUIRED_FUND_CODE_FOR_ACCT_CATEGORY_FUND_ON_FUND;
   extern const long WARN_INVALID_FUND_CODE_FOR_ACCT_CATEGORY_FUND_ON_FUND;
   extern const long ERR_SYSTEM_ACCT_CATEGORY;
   // statement and confirm
   extern const long ERR_CLNT_MTH_STMT_FOR_CLIENT_HELD_ACCOUNT;
   extern const long ERR_CLNT_MTH_STMT_NOT_FOR_SEG_ENV;
   extern const long ERR_CLNT_MTH_STMT_FOR_ACCOUNT_BELONG_NISTMT;
   //EPA Auto Settlement
   extern const long ERR_ACCT_CATEGORY_NOT_ALLOWED_FOR_ACCOUNT;
}

namespace ifds
{  
   extern CLASS_IMPORT const BFTextFieldId CreatedToday;
   extern CLASS_IMPORT const BFTextFieldId AcctDesignation;
   extern CLASS_IMPORT const BFTextFieldId TaxType;
   extern CLASS_IMPORT const BFTextFieldId BrokerCode;
   extern CLASS_IMPORT const BFTextFieldId BranchCode;
   extern CLASS_IMPORT const BFTextFieldId Slsrep;
   extern CLASS_IMPORT const BFTextFieldId GoodBad;
   extern CLASS_IMPORT const BFTextFieldId AcctCategory2;
   extern CLASS_IMPORT const BFTextFieldId CompanyCode;
   extern CLASS_IMPORT const BFTextFieldId AcctType;
   extern CLASS_IMPORT const BFTextFieldId PaymentIdMethod;
   extern CLASS_IMPORT const BFTextFieldId FundCode; //fund on fund
   extern CLASS_IMPORT const BFTextFieldId CatValue; //fund on fund
   extern CLASS_IMPORT const BFTextFieldId SegClient;
   extern CLASS_IMPORT const BFTextFieldId BrokerCategoryList;
   extern CLASS_IMPORT const BFTextFieldId Yes_NO;
   extern CLASS_IMPORT const BFTextFieldId EPABroker;
   extern CLASS_IMPORT const BFTextFieldId TFSAAcctCatCodeList;
   extern CLASS_IMPORT const BFTextFieldId RRSPAcctCatCodeList;
   extern CLASS_IMPORT const BFTextFieldId DebitPaymentMethod;
   extern CLASS_IMPORT const BFTextFieldId PymtRoutingMthd;
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const PRIVATE_ACCOUNT_ACTEGORY_ONLY_FOR_CLIENT;
   extern CLASS_IMPORT I_CHAR * const INVALID_FUND_CODE_FOR_ACCT_CATEGORY_FUND_ON_FUND;
}

namespace UAF
{
    extern CLASS_IMPORT I_CHAR * const ACCT_CATEGORY;
    extern CLASS_IMPORT I_CHAR * const ACCT_CATEGORY_PRIVATE_WEALTH_OPT_OUT;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags 
   { ifds::AcctCategory,    BFCBO::REQUIRED,             0 }, 
   { ifds::PaymentIdMethod, BFCBO::NONE,                 0 }, 
   { ifds::CatValue,        BFCBO::NONE,                 0 }, //fund on fund
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//****************************************************************************
AcctCategory::AcctCategory( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );

   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//****************************************************************************
AcctCategory::~AcctCategory()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//****************************************************************************
SEVERITY AcctCategory::init( const BFData& data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject( const_cast<BFData&>(data), false, true );

   overwriteAcctCategorySet();

   DString strCreatedToday(YES);
   DString dstrAcctCategory(NULL_STRING);
   getParentAccount()->getField(ifds::CreatedToday, strCreatedToday, BF::HOST, false);
   getField(ifds::AcctCategory, dstrAcctCategory, BF::HOST, false);
   if ( ( strCreatedToday == NO ) || ( dstrAcctCategory == ACCOUNT_CATEGORY::MARGIN ) || 
        ( dstrAcctCategory == ACCOUNT_CATEGORY::WRAP ) )
      setFieldReadOnly(ifds::AcctCategory, BF::HOST, true);

   if( dstrAcctCategory != ACCOUNT_CATEGORY::SWIFT_PAYMENT_METHOD )
   {
      setFieldReadOnly ( ifds::PaymentIdMethod, BF::HOST, true );
   }

   if ( dstrAcctCategory == ACCOUNT_CATEGORY::SWIFT_PAYMENT_METHOD )
   {
      setFieldReadOnly ( ifds::CatValue, BF::HOST, false );
	  DString outdstrpymtLevelRoutingSet;
	  buildPaymentRoutingSet(BF::HOST, outdstrpymtLevelRoutingSet);
      setFieldAllSubstituteValues(ifds::CatValue, BF::HOST, outdstrpymtLevelRoutingSet);
   }
   else if ( dstrAcctCategory == ACCOUNT_CATEGORY::DEBIT_SWIFT_PAYMENT_METHOD )
   {
      setFieldReadOnly ( ifds::CatValue, BF::HOST, false );
      setFieldSubstituteValues (ifds::CatValue, BF::HOST, ifds::DebitPaymentMethod);
   }
   else if ( dstrAcctCategory == ACCOUNT_CATEGORY::FUND_ON_FUND )
   {
      setFieldReadOnly ( ifds::CatValue, BF::HOST, false );
   }
   else if ( dstrAcctCategory == ACCOUNT_CATEGORY::HST_EXCEPTION )
   {
      setFieldReadOnly ( ifds::CatValue, BF::HOST, false );
      setFieldSubstituteValues (ifds::CatValue, BF::HOST, ifds::Yes_NO );
   }
   else  //fund on fund
   {      
      setFieldReadOnly ( ifds::CatValue, BF::HOST, true );
   }

   if ((dstrAcctCategory == ACCOUNT_CATEGORY::PRIVATE_WEALTH_OPT_OUT && !getWorkSession().hasUpdatePermission(UAF::ACCT_CATEGORY_PRIVATE_WEALTH_OPT_OUT)) || 
       (dstrAcctCategory != ACCOUNT_CATEGORY::PRIVATE_WEALTH_OPT_OUT && !getWorkSession().hasUpdatePermission(UAF::ACCT_CATEGORY)))
   {
       const CLASS_FIELD_INFO* pClassFieldInfo = (const CLASS_FIELD_INFO *)&classFieldInfo;
       for( int i = 0; i < NUM_FIELDS; i++, pClassFieldInfo++ )
       {
           setFieldReadOnly(pClassFieldInfo->m_fieldId, BF::HOST, true);
       }   
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
SEVERITY AcctCategory::initNew( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   overwriteAcctCategorySet();
   setFieldReadOnly ( ifds::PaymentIdMethod, idDataGroup, true );
   //for reset purposes
   DString outdstrpymtLevelRoutingSet;
   buildPaymentRoutingSet(idDataGroup, outdstrpymtLevelRoutingSet);
   setFieldReadOnly ( ifds::PaymentIdMethod, BF::HOST, true );

   //fund on fund
   DString dstrAcctCategory(NULL_STRING);
   getField(ifds::AcctCategory, dstrAcctCategory, BF::HOST, false);

   if ( dstrAcctCategory == ACCOUNT_CATEGORY::SWIFT_PAYMENT_METHOD )   
   {      
      setFieldReadOnly ( ifds::CatValue, idDataGroup, false );      
      setFieldAllSubstituteValues (ifds::CatValue, idDataGroup, outdstrpymtLevelRoutingSet);      
      setFieldRequired ( ifds::CatValue, idDataGroup, true );   
   }
   else if ( dstrAcctCategory == ACCOUNT_CATEGORY::DEBIT_SWIFT_PAYMENT_METHOD )   
   {      
      setFieldReadOnly ( ifds::CatValue, idDataGroup, false );      
      setFieldSubstituteValues (ifds::CatValue, idDataGroup, ifds::DebitPaymentMethod);      
      setFieldRequired ( ifds::CatValue, idDataGroup, true );   
      setFieldNoValidate ( ifds::CatValue, NULL_STRING, idDataGroup, false );
   }
   else if ( dstrAcctCategory == ACCOUNT_CATEGORY::FUND_ON_FUND )   
   {      
      setFieldReadOnly ( ifds::CatValue, idDataGroup, false );      
      setFieldRequired ( ifds::CatValue, idDataGroup, true );   
   }
   else if ( dstrAcctCategory == ACCOUNT_CATEGORY::HST_EXCEPTION )   
   {      
      setFieldReadOnly ( ifds::CatValue, idDataGroup, false );
      setFieldRequired ( ifds::CatValue, idDataGroup, true );
      setFieldSubstituteValues (ifds::CatValue, idDataGroup, ifds::Yes_NO );
   }
   else
   {
       setFieldRequired ( ifds::CatValue, idDataGroup, false );      
       setFieldAllSubstituteValues (ifds::CatValue, idDataGroup, outdstrpymtLevelRoutingSet );  
   }

   BFProperties *pBFProperties = getFieldProperties (ifds::AcctCategory, idDataGroup); 
   DString dstrAcctCategorySet;

   if (pBFProperties)
   {
       pBFProperties->getAllSubstituteValues(dstrAcctCategorySet);
       DString descOfIPW = DSTCommonFunctions::getDescription(ACCOUNT_CATEGORY::PRIVATE_WEALTH_OPT_OUT, dstrAcctCategorySet);

       if (!getWorkSession().hasCreatePermission(UAF::ACCT_CATEGORY) && !descOfIPW.empty()) // Remove all items except private wealth opt out
       {
           dstrAcctCategorySet = (DString)ACCOUNT_CATEGORY::PRIVATE_WEALTH_OPT_OUT + I_("=") + descOfIPW + I_(";");
       }

       if (!getWorkSession().hasCreatePermission(UAF::ACCT_CATEGORY_PRIVATE_WEALTH_OPT_OUT)) // remove private wealth opt out.
       {
           dstrAcctCategorySet = removeItemFromSubtList(dstrAcctCategorySet, ACCOUNT_CATEGORY::PRIVATE_WEALTH_OPT_OUT);
       }

       setFieldAllSubstituteValues(ifds::AcctCategory, idDataGroup, dstrAcctCategorySet);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************

MFAccount* AcctCategory::getParentAccount()
{
   BFCBO *pParent = getParent();
   assert(pParent);
   MFAccount* pMFAccount = dynamic_cast<MFAccount*>(pParent->getParent());
   assert(pMFAccount);
   return pMFAccount;
}

//******************************************************************************
////////////////////////////////VALIDATIONS////////////////////////////////////
//******************************************************************************


SEVERITY AcctCategory::doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

   if (idField == ifds::AcctCategory)
   {
      validateAcctCategory (strValue, idDataGroup);
   }

   //fund on fund
   else if (idField == ifds::CatValue)
   {
      DString strAcctCategory;
      getField(ifds::AcctCategory, strAcctCategory,idDataGroup);

      if (strAcctCategory == ACCOUNT_CATEGORY::FUND_ON_FUND)
      {
        FundMasterList *pFundMasterList;

        if ( !strValue.empty() )
        {
            if ( getMgmtCo().getFundMasterList (pFundMasterList) <= WARNING && 
                pFundMasterList)
            {
                if ( !pFundMasterList->IsFundExist (strValue, idDataGroup) )
                {
                  getErrMsg ( IFASTERR::INVALID_FUND_CODE_FOR_ACCT_CATEGORY_FUND_ON_FUND, 
                              CND::ERR_INVALID_FUND_CODE_FOR_ACCT_CATEGORY_FUND_ON_FUND, 
                              CND::WARN_INVALID_FUND_CODE_FOR_ACCT_CATEGORY_FUND_ON_FUND, 
                              idDataGroup); 
                }
                else
                {
                    return (NO_SEVERITY);
                }
            }
        }
        else if ( strValue.empty())
        {
           ADDCONDITIONFROMFILE ( CND::ERR_REQUIRED_FUND_CODE_FOR_ACCT_CATEGORY_FUND_ON_FUND );
        }
        else
        {
           return (NO_SEVERITY);
        }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY AcctCategory::validateAcctCategory (const DString &strValue, 
                                             const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

   // A) common for all category types: 
   //1.Acct Category field cannot be modified if the account hasn't been created today
   if (strValue == ACCOUNT_CATEGORY::ESTATE || strValue == ACCOUNT_CATEGORY::DEATH_OF_NOTIFICATION)
   {
      ADDCONDITIONFROMFILE( CND::ERR_SYSTEM_ACCT_CATEGORY );
   }
   else if (validateModifyAcctCategory (strValue, idDataGroup) <= WARNING)
   {
      // B) category specific
      if (strValue == ACCOUNT_CATEGORY::MARGIN)
      {
         validateMarginAccount(idDataGroup);
      }
      else if (strValue == ACCOUNT_CATEGORY::LOAN)
      {
         validateLoanAccount(idDataGroup);
      }
      else if (strValue == ACCOUNT_CATEGORY::CHEQUE_PRIVILEGE)
      {
         validateChqPrivAccount(idDataGroup);
      }
      else if (strValue == ACCOUNT_CATEGORY::WRAP)
      {
         validateWRAPAccount(idDataGroup);
      }
      else if (strValue == ACCOUNT_CATEGORY::PRIVATE)
      {
//account should can only be client account.
         DString acctDesignation,
            acctType;

         getParentAccount ()->getField (ifds::AcctType, acctType, idDataGroup, false);
         getParentAccount ()->getField (ifds::AcctDesignation, acctDesignation, idDataGroup, false);
//only allowed for client held accounts
         if (acctType == I_("4") || //corporate account
             acctDesignation != I_("1")) //non-client held accounts
         {
            getErrMsg ( IFASTERR::PRIVATE_ACCOUNT_ACTEGORY_ONLY_FOR_CLIENT, 
                        CND::ERR_PRIVATE_ACCOUNT_ACTEGORY_ONLY_FOR_CLIENT, 
                        CND::WARN_PRIVATE_ACCOUNT_ACTEGORY_ONLY_FOR_CLIENT, 
                        idDataGroup); 
         }
      }
      else if (strValue == ACCOUNT_CATEGORY::CLIENT_MONTHLY_STATEMENT)
      {
         validateClientMonthlyStatement( idDataGroup );
      }
      else if (strValue == ACCOUNT_CATEGORY::EPA_APP)
      {
         validateEPAApplicable( idDataGroup );
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AcctCategory::validateModifyAcctCategory(const DString& strValue, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateModifyAcctCategory" ) );

   //Acct Category field cannot be modified if the account hasn't been created today

   if (isNew())
      return (NO_SEVERITY);

   DString strNewValue(strValue), strCreatedToday(YES), strHostValue(NULL_STRING);
   getParentAccount()->getField(ifds::CreatedToday, strCreatedToday, BF::HOST, false);
   if (strCreatedToday != NO)
      return (NO_SEVERITY);

   getField(ifds::AcctCategory, strHostValue, BF::HOST, false);
   if ( strHostValue.strip() != strNewValue.strip() )
      ADDCONDITIONFROMFILE( CND::ERR_CANNOT_MODIFY_ACCT_FEATURE );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AcctCategory::validateMarginAccount(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateMarginAccount" ) );

   //1. it should be a client account
   DString strAcctDesignation, strTaxType;
   getParentAccount()->getField(ifds::AcctDesignation, strAcctDesignation, idDataGroup, false);
   if (strAcctDesignation != CLIENT_ACCT_DESIGNATION)
   {
      ADDCONDITIONFROMFILE( CND::ERR_CLIENT_NON_REG_MARGIN_ACCT );
      return(GETCURRENTHIGHESTSEVERITY());
   }
   //2. it should be a non registered account
   getParentAccount()->getField(ifds::TaxType, strTaxType, idDataGroup, false);
   if (!getWorkSession().isNonRegLike( strTaxType ))
   {
      ADDCONDITIONFROMFILE( CND::ERR_CLIENT_NON_REG_MARGIN_ACCT );
      return(GETCURRENTHIGHESTSEVERITY());
   }

   /* this logic has to be removed, until the complete validation against pending trades, PACs, SWPs, 
   Distributions, other(?) will be implemented

   //3. the account should be created today (for existing accounts, cannot add Margin feature)
   DString strCreatedToday;
   getParentAccount()->getField(ifds::CreatedToday, strCreatedToday, BF::HOST, false);
   if (strCreatedToday == NO)
   {
      ADDCONDITIONFROMFILE( CND::ERR_MARGIN_ONLY_FOR_NEW_ACCOUNT );
   }
   else if (strCreatedToday == YES)
   {
      //if the account has been created today we allow margin category to be created
      //only if there are no pending trades which are not margin eligible(all funds
      //have to be margin eligible)
      validatePendingTrades();
   }
   instead of No. 3, we'll check if it is new account
   */
   if (!getParentAccount()->isNew())
      ADDCONDITIONFROMFILE( CND::ERR_MARGIN_ONLY_FOR_NEW_ACCOUNT );

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
SEVERITY AcctCategory::validatePendingTrades()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validatePendingTrades" ) );

   MFAccount * pMFAccount = getParentAccount();
   PendingTradeList* pPendingTradeList = NULL;
   //have to get the full pending trade list (which should be fairly small),
   //iterate through it and for good records check if all the funds are margin eligible
   if (pMFAccount->getPendingTradesList(pPendingTradeList, BF::HOST, FULL_LIST)
         <= WARNING && pPendingTradeList)
   {
      BFObjIter iter(*pPendingTradeList, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED);
      while (!iter.end())
      {
         PendingTradeDetails *pPendingTradeDetails = static_cast
            <PendingTradeDetails*>(iter.getObject());
         assert(pPendingTradeDetails);

         DString strGoodBad;
         pPendingTradeDetails->getField(ifds::GoodBad, strGoodBad, BF::HOST, false);
         if (strGoodBad.strip().upperCase() == YES)
         {
            DString strKey = iter.getStringKey();
            pPendingTradeList->getItem(strKey, BF::HOST);
            if (!pPendingTradeDetails->isMarginEligible(BF::HOST))
            {
               ADDCONDITIONFROMFILE( CND::ERR_MARGIN_PENDING_NOT_ELIGIBLE );
               break;
            }
         }
         ++iter;
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AcctCategory::validateLoanAccount(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateLoanAccount" ) );

   //1. it should be a client account
   DString strAcctDesignation, strTaxType;
   getParentAccount()->getField(ifds::AcctDesignation, strAcctDesignation, idDataGroup, false);
   if (strAcctDesignation != CLIENT_ACCT_DESIGNATION)
   {
      ADDCONDITIONFROMFILE( CND::ERR_CLIENT_RRSP_RRIF_LOAN_ACCT );
      return(GETCURRENTHIGHESTSEVERITY());
   }
   //2. it should be either a RRIF or an RRSP account
   getParentAccount()->getField(ifds::TaxType, strTaxType, idDataGroup, false);
   if (strTaxType != RRSP_TAX_TYPE && strTaxType != RRIF_TAX_TYPE)
      ADDCONDITIONFROMFILE( CND::ERR_CLIENT_RRSP_RRIF_LOAN_ACCT );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AcctCategory::validateChqPrivAccount(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateChqPrivAccount" ) );

   //none for now

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AcctCategory::validateWRAPAccount(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateWRAPAccount" ) );

   //have to check if the broker and sales rep are allowed; validation is done by view
   //DString strBrokerCode, strSlsRep, strBranchCode;
   //getParentAccount()->getField(ifds::BrokerCode, strBrokerCode, idDataGroup, false);
   /*BrokerList objBrokerList(*this);
   if (objBrokerList.init2(strBrokerCode, NULL_STRING, I_("L"), NULL_STRING, WRAP_VALIDATION)
            >WARNING)
      return(GETCURRENTHIGHESTSEVERITY());

   getParentAccount()->getField(ifds::Slsrep, strSlsRep, idDataGroup, false);
   getParentAccount()->getField(ifds::BranchCode, strBranchCode, idDataGroup, false);
   AgentList objAgentList(*this);
   objAgentList.init2(strBrokerCode, strBranchCode, strSlsRep, NULL_STRING, 
      NULL_STRING, NULL_STRING, WRAP_VALIDATION);*/

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AcctCategory::validateUserDelete( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateUserDelete" ) );

   if (isNew())
      return (NO_SEVERITY);

   
   DString strAcctCateg, strCreatedToday(YES);
   /*to be consistent, remove "Today" logic for margin account everywhere
   getParentAccount()->getField(ifds::CreatedToday, strCreatedToday, BF::HOST, false);
   if (strCreatedToday != NO)
      return (NO_SEVERITY);*/

   getField(ifds::AcctCategory, strAcctCateg, BF::HOST, false);
   if ( strAcctCateg.strip() == ACCOUNT_CATEGORY::MARGIN ) {
      ADDCONDITIONFROMFILE( CND::ERR_MARGIN_CANNOT_BE_REMOVED );
   } else if ( strAcctCateg.strip() == ACCOUNT_CATEGORY::WRAP ) {
      ADDCONDITIONFROMFILE( CND::ERR_WRAP_CANNOT_BE_REMOVED );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************************
SEVERITY AcctCategory::validateClientMonthlyStatement( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateClientMonthlyStatement" ) );

   // get Account Designation
   DString dstrAcctDesignation;
   getParentAccount()->getField(ifds::AcctDesignation, dstrAcctDesignation, idDataGroup, false);

   // if account is not client held, not allow for this category.
   if (dstrAcctDesignation != CLIENT_ACCT_DESIGNATION)
   {
      ADDCONDITIONFROMFILE( CND::ERR_CLNT_MTH_STMT_FOR_CLIENT_HELD_ACCOUNT );
      return(GETCURRENTHIGHESTSEVERITY());
   }
   DString dstrSegClient;
   getWorkSession().getOption(ifds::SegClient, dstrSegClient, idDataGroup, false);
   // not allow for SEG Client
   if ( dstrSegClient.strip().upperCase() == YES )
   {
      ADDCONDITIONFROMFILE( CND::ERR_CLNT_MTH_STMT_NOT_FOR_SEG_ENV );
      return GETCURRENTHIGHESTSEVERITY();
   }
   // not allow for Broker that's not contain "NISTMT"
   DString dstrBrokerCode;
   Broker* pBroker = NULL;
   getParentAccount()->getField(ifds::BrokerCode, dstrBrokerCode, idDataGroup, false);
   if ( getParentAccount()->getBroker (pBroker, dstrBrokerCode, idDataGroup) <= WARNING &&
        pBroker)
   {
      DString dstrBrokerCategoryList;
      pBroker->getField(ifds::BrokerCategoryList, dstrBrokerCategoryList, idDataGroup, false);
      dstrBrokerCategoryList.strip().upperCase();
      if ( !DSTCommonFunctions::codeInList (NI_31_103_STMT, dstrBrokerCategoryList))
      {
         ADDCONDITIONFROMFILE( CND::ERR_CLNT_MTH_STMT_FOR_ACCOUNT_BELONG_NISTMT );
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AcctCategory::overwriteAcctCategorySet()
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "overwriteAcctCategorySet" ));

//   DString companyCode (NULL_STRING);
//
//   getWorkSession().getOption (ifds::CompanyCode, companyCode, BF::HOST, false);
//   if (companyCode.upperCase() == I_("EPL"))
//   {
//      setFieldSubstituteValues (ifds::AcctCategory, BF::HOST, ifds::AcctCategory2);
//   }

   return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************
SEVERITY AcctCategory::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );
   if( idField == ifds::AcctCategory )
   {
      DString strAcctCategory;
      getField( idField, strAcctCategory, idDataGroup, false );

      //fund on fund
      if ( strAcctCategory == ACCOUNT_CATEGORY::FUND_ON_FUND )
      {
         setFieldReadOnly ( ifds::CatValue, BF::HOST, false ); 
         setFieldSubstituteValues (ifds::CatValue, idDataGroup, ifds::NullFieldId );
      }
      else if ( strAcctCategory == ACCOUNT_CATEGORY::SWIFT_PAYMENT_METHOD )
      {
		 DString outdstrpymtLevelRoutingSet;
         buildPaymentRoutingSet(idDataGroup, outdstrpymtLevelRoutingSet); 
         setFieldAllSubstituteValues (ifds::CatValue, idDataGroup,outdstrpymtLevelRoutingSet);
         setDefaultPayment(idDataGroup);
      }
      else if ( strAcctCategory == ACCOUNT_CATEGORY::DEBIT_SWIFT_PAYMENT_METHOD )   
      {      
         setFieldReadOnly ( ifds::CatValue, idDataGroup, false );      
         setFieldSubstituteValues (ifds::CatValue, idDataGroup, ifds::DebitPaymentMethod);      
         setFieldRequired ( ifds::CatValue, idDataGroup, true );   
         setFieldNoValidate ( ifds::CatValue, NULL_STRING, idDataGroup, false );
      }
      else if ( strAcctCategory == ACCOUNT_CATEGORY::HST_EXCEPTION )
      {
         setFieldReadOnly ( ifds::CatValue, idDataGroup, false );
         setFieldRequired ( ifds::CatValue, idDataGroup, true );
         setFieldSubstituteValues (ifds::CatValue, idDataGroup, ifds::Yes_NO );
      }
      else // old logic
      {
         setDefaultPayment(idDataGroup);
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************

SEVERITY AcctCategory::setDefaultPayment(const BFDataGroupId& idDataGroup)
{
   MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setDefaultPayment" ) );

   DString dstrAcctCategory, 
      dstrAcctType;
   
   getField( ifds::AcctCategory, dstrAcctCategory, idDataGroup );
   if (dstrAcctCategory.strip() == ACCOUNT_CATEGORY::SWIFT_PAYMENT_METHOD)
   {
      setFieldReadOnly (ifds::PaymentIdMethod, idDataGroup, false);
      getParentAccount()->getField(ifds::AcctType, dstrAcctType, idDataGroup, false);

      if (dstrAcctType.strip() == CORPORATE_ACCT_TYPE             ||
          dstrAcctType.strip() == LOCKED_IN_ACCT_TYPE             ||
          dstrAcctType.strip() == OMNIBUS_ACCT_TYPE               ||
          dstrAcctType.strip() == PENSION_FUND_ACCT_TYPE          ||
          dstrAcctType.strip() == ESTATE_ACCT_TYPE                ||
          dstrAcctType.strip() == ASSOCIATION_ACCT_TYPE           ||
          dstrAcctType.strip() == FINANCIAL_CORPORATION_ACCT_TYPE ||
          dstrAcctType.strip() == GENERAL_CORPORATION_ACCT_TYPE)
      {
         setFieldNoValidate (ifds::CatValue, ACCOUNT_CATEGORY::MT202, idDataGroup, false, true, true);
      }
      else if (dstrAcctType.strip() == INDIVIDUAL_ACCT_TYPE  ||
               dstrAcctType.strip() == SPOUSAL_ACCT_TYPE    ||
               dstrAcctType.strip() == JOINT_ACCT_TYPE      ||
               dstrAcctType.strip() == TRUST_ACCT_TYPE)
      {
         setFieldNoValidate (ifds::CatValue, ACCOUNT_CATEGORY::MT103, idDataGroup, false, true, true);
      }
      else
      {
         //what other acount types do we have?
         assert (0);
      }
   }
   else
   {
      setFieldReadOnly (ifds::PaymentIdMethod, idDataGroup, true);
      setFieldNoValidate (ifds::CatValue, NULL_STRING, idDataGroup, false, true, true);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AcctCategory::validateEPAApplicable(const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateEPAApplicable" ));

   DString strMarket = DSTCommonFunctions::getMarket();
   if( strMarket != MARKET_IDS::CANADA )
      return GETCURRENTHIGHESTSEVERITY();

   DString dstrBrokerCode,
      dstrEPABroker;
   Broker* pBroker = NULL;
   getParentAccount()->getField(ifds::BrokerCode, dstrBrokerCode, idDataGroup, false);
   if ( getParentAccount()->getBroker (pBroker, dstrBrokerCode, idDataGroup) <= WARNING &&
        pBroker)
   {
      pBroker->getField(ifds::EPABroker, dstrEPABroker, idDataGroup, false);
      dstrEPABroker.strip().upperCase();

      DString acctDesignation,
         acctType,
         acctTaxType,
         tfsaAcctCatCodeList,
         rrspAcctCatCodeList;

      getParentAccount ()->getField (ifds::AcctType, acctType, idDataGroup, false);
      getParentAccount ()->getField (ifds::AcctDesignation, acctDesignation, idDataGroup, false);
      getParentAccount ()->getField (ifds::TaxType, acctTaxType, idDataGroup, false);
      getWorkSession().getOption(ifds::TFSAAcctCatCodeList, tfsaAcctCatCodeList, idDataGroup, false);
      getWorkSession().getOption(ifds::RRSPAcctCatCodeList, rrspAcctCatCodeList, idDataGroup, false);
      acctType.strip().upperCase();
      acctDesignation.strip().upperCase();
      acctTaxType.strip().upperCase();
      tfsaAcctCatCodeList.strip().upperCase();
      rrspAcctCatCodeList.strip().upperCase();

      bool bAcctCatNotAllowed = false;
      bool bIsAccountNew = getParentAccount ()->isNew();

      if ( DSTCommonFunctions::codeInList (acctType, I_("4,8,3")) || 
          !DSTCommonFunctions::codeInList (acctTaxType, I_("0,1,V") ) )
      {
         //corporate, trust, estate account won't be allowed to use add EPA APP(57)
         bAcctCatNotAllowed = true; 
      }
      else
      {
         if ( DSTCommonFunctions::codeInList (acctTaxType, I_("1,V") ) && 
              dstrEPABroker == I_("Y") && 
              acctDesignation == CLIENT_ACCT_DESIGNATION)
         {
            if ( ( acctTaxType == I_("V") && 
                   DSTCommonFunctions::codeInList (I_("57"),tfsaAcctCatCodeList )) || //TFSA
                 ( acctTaxType == I_("1") && 
                   DSTCommonFunctions::codeInList (I_("57"),rrspAcctCatCodeList )) )  // RRSP
            {
               bAcctCatNotAllowed = false;
            }
         }
         else
         {
            if( acctTaxType == I_("0") && bIsAccountNew &&
                dstrEPABroker == I_("Y") && 
                acctDesignation == CLIENT_ACCT_DESIGNATION ) 
            {
               // new non-register account will be allowed to have 'EPA App'
               // as account category
               bAcctCatNotAllowed = false;
            }
            else
            {
               bAcctCatNotAllowed = true;
            }
         }
      }

      if( bAcctCatNotAllowed )
      {
         ADDCONDITIONFROMFILE( CND::ERR_ACCT_CATEGORY_NOT_ALLOWED_FOR_ACCOUNT );
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}
/******************************************************************************
Input:DataGroupID
OutPut:None
Return:Severity
Functionality:Sets the  Paymentroutingtype	sub list
******************************************************************************/
SEVERITY AcctCategory::buildPaymentRoutingSet(const BFDataGroupId &idDataGroup, DString &outdstrpymtLevelRoutingSet)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("buildPaymentRoutingSet"));
	DString dstrTradelevelOveride,dstrPymtRoutingMthd,dstrPymtRoutingMthdSet;
	getWorkSession ().getOption (ifds::PymtRoutingMthd, dstrPymtRoutingMthd, BF::HOST, false); 
	BFProperties *pBFProperties=
      getFieldProperties (ifds::PaymentIdMethod, idDataGroup); 
    assert (pBFProperties);
    if (pBFProperties)
    {
      pBFProperties->getAllSubstituteValues (dstrPymtRoutingMthdSet);
    } 
	outdstrpymtLevelRoutingSet.stripAll();
	dstrPymtRoutingMthdSet.stripAll();
	if(	! dstrPymtRoutingMthd.empty()  ||
		! dstrPymtRoutingMthdSet.empty() )
   {
    I_CHAR *temp = const_cast<I_CHAR*> (dstrPymtRoutingMthdSet.c_str ());
    do
    {
         DString dstrPymtRoutingMthdSetCode,dstrPymtRoutingMthdSetDescr;   
         temp = parseIdiString (temp, dstrPymtRoutingMthdSetCode, dstrPymtRoutingMthdSetDescr);         
         if (isCodeInList (dstrPymtRoutingMthdSetCode,dstrPymtRoutingMthd))
         {
            outdstrpymtLevelRoutingSet += dstrPymtRoutingMthdSetCode + I_("=") + 
				                          dstrPymtRoutingMthdSetDescr + I_(";");
         }
    } while (temp && temp != NULL_STRING && *temp);
   }
   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctCategory.cpp-arc  $
// 
//    Rev 1.33   Feb 03 2011 11:49:38   dchatcha
// Synch up: IN# 2395138 - EPA App Acct Category does not apply to client name non-reg accounts, new non-register account is allowed.
// 
//    Rev 1.32   Jan 31 2011 18:02:28   dchatcha
// Synch up: P0179308 FN01 - Multi Manager Subscription and Direct Debit Payment.
// 
//    Rev 1.31   Jan 28 2011 19:27:58   dchatcha
// P0176724 FN01 - EPL Company code change
// 
//    Rev 1.30   Jan 24 2011 14:09:36   dchatcha
// IN# 2395138 - EPA App Acct Category does not apply to client name non-reg accounts
// 
//    Rev 1.29   Dec 28 2010 05:30:14   dchatcha
// IN# 2370625 - Can not add Account Category 'EAP App' to TFSA and RRSP account.
// 
//    Rev 1.28   Dec 02 2010 04:34:24   dchatcha
// P0175716 FN02 - Client Name Redemption - EPA Auto Settlement.
// 
//    Rev 1.27   Dec 01 2010 06:29:10   dchatcha
// P0175716 FN02 - Client Name Redemption - EPA Auto Settlement.
// 
//    Rev 1.26   Nov 24 2010 02:10:18   dchatcha
// Restored rev. 1.24 due to P0176724 FN01 - EPL Company code change is moved to R11.3
// 
//    Rev 1.25   Nov 14 2010 21:52:44   dchatcha
// P0176724 FN01 - EPL Company code change.
// 
//    Rev 1.24   Jul 20 2010 05:30:32   dchatcha
// IN# 2187879 - HST - New Exception Account Category.
// 
//    Rev 1.23   Apr 06 2010 12:34:52   kitticha
// PET0169756_FN01_N131-103 Statement and Confirm.
// 
//    Rev 1.22   26 Jun 2009 13:52:06   popescu
// Incident 1741768 - Account Category not auto-populating
// 
//    Rev 1.21   Jan 12 2009 11:11:30   jankovii
// IN 1549377 Estate and Death of Notification acct category can only be added by the system
// 
//    Rev 1.20   Oct 28 2008 06:53:50   daechach
// PET22486FN45 - Fund on Funds Account Report. - Fix Revision Control Entries
// 
//    Rev 1.19   Oct 28 2008 01:34:12   phiwponp
// PET22486FN45 - Fund on Funds Account Report.
//
//    Rev 1.18   06 Oct 2008 13:16:36   kovacsro
// PET142007  FN01 TFSA
// 
//    Rev 1.17   12 Sep 2008 15:40:44   kovacsro
// PET142007.FN01 Tax Free Saving Account - code cleanup for taxType=0
// 
//    Rev 1.16   18 Sep 2007 16:28:48   kovacsro
// IN993614 - added the other account types to default PaymentMethodId
// 
//    Rev 1.15   Aug 17 2007 11:10:00   kovacsro
// PET2388FN01 - PaymentMethodId read only and blank for any other account category but Swift Payment Method
// 
//    Rev 1.14   Aug 16 2007 10:56:56   kovacsro
// PET2388FN01 - Swift Payment method Id - finalized
// 
//    Rev 1.13   Aug 09 2007 14:04:18   jankovii
// PET 2388 FN01 - Swift Payment Method ID.
// 
//    Rev 1.12   28 Jun 2007 16:43:16   popescu
// ncident #847336 - change the way the company code is read and switched to code EPL
// 
//    Rev 1.11   27 Jun 2007 23:58:06   popescu
// PET 2236 - Gap 50 - Private act
// 
//    Rev 1.10   May 30 2007 10:33:26   jankovii
// Bankogk - Incident #847336 - add acct categories for MMF.
// 
//    Rev 1.9   Nov 14 2004 14:25:04   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.8   Mar 21 2003 17:55:50   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.7   Mar 11 2003 14:05:28   HSUCHIN
// fix condition name
// 
//    Rev 1.6   Mar 10 2003 15:40:16   HSUCHIN
// PTS 10014474 - prevent WRAP from being removed/changed
// 
//    Rev 1.5   Mar 04 2003 16:32:50   HSUCHIN
// PTS 10014345 Margin accounts can no longer be changed.
// 
//    Rev 1.4   Feb 21 2003 13:33:12   KOVACSRO
// Removed 'Today' logic for Margin category.
// 
//    Rev 1.3   Feb 12 2003 16:36:04   KOVACSRO
// Added new business rule : when adding margin category for an existing account, created today, check the pending trades if they are Margin eligible.
// 
//    Rev 1.2   Feb 06 2003 13:37:12   KOVACSRO
// Added new business rule: Margin category cannot be setup for an existing account.
// 
//    Rev 1.1   Jan 25 2003 17:00:18   KOVACSRO
// Added validations (business logic)
// 
//    Rev 1.0   Jan 21 2003 14:26:20   KOVACSRO
// Initial revision.

 */