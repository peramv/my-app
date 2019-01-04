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
//    Copyright 2000 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : AccountCommitment.cpp
//
// ^CLASS    : AccountCommitment
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "accountcommitment.hpp"
#include "dstcworksession.hpp"
#include "accountcommitmentdetailslist.hpp"
#include "acctcommitbanklist.hpp"
#include "commitmentproductlist.hpp"
#include "mgmtco.hpp"
#include "RESPPACDateCalculator.hpp"
#include "mfaccount.hpp"
#include "DateValidation.hpp"
#include "DynamicSubListHolder.hpp"

#include <ifastdataimpl\dse_dstc0432_vw.hpp>
#include <ifastdataimpl\dse_dstc0432_req.hpp>
#include <ifastdataimpl\dse_dstc0434_req.hpp>

#include <bfutil\bfdate.hpp>

namespace CND
{  // Conditions used
//account
   extern const long ERR_COMMITMENT_PRODUCT_NOT_ACTIVE;
   extern const long ERR_INVALID_DATE;
   extern const long ERR_MATSWP_EFFECTIVE_DATE;
   extern const long ERR_PENDING_OR_UNSETTLED_TRADE_EXISTS;
   extern const long WARN_PENDING_OR_UNSETTLED_TRADE_EXISTS;
   extern const long ERR_DATE_MUST_BE_EQUAL_OR_GREATER_THAN_CURR_DATE_PLUS_3_BUSS_DATE;
   extern const long WARN_DATE_MUST_BE_EQUAL_OR_GREATER_THAN_CURR_DATE_PLUS_3_BUSS_DATE;
   extern const long ERR_DATE_MUST_BE_EQUAL_OR_EARLIER_THAN_2ND_DIPLOMA_COMM_DATE;
   extern const long WARN_DATE_MUST_BE_EQUAL_OR_EARLIER_THAN_2ND_DIPLOMA_COMM_DATE;
   extern const long ERR_NEXT_PROC_DATE_COMPARE_LAST_RUN_DATE;
}

namespace IFASTERR
{
	extern CLASS_IMPORT I_CHAR * const PENDING_OR_UNSETTLED_TRADE_EXISTS;
	extern CLASS_IMPORT I_CHAR * const DATE_MUST_BE_EQUAL_OR_GREATER_THAN_CURR_DATE_PLUS_3_BUSS_DATE;
	extern CLASS_IMPORT I_CHAR * const DATE_MUST_BE_EQUAL_OR_EARLIER_THAN_2ND_DIPLOMA_COMM_DATE;
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ACCT_COMMIT_INQUIRY;
}
namespace ifds
{
   extern CLASS_IMPORT const BFDecimalFieldId PaidPACSAmt;
   extern CLASS_IMPORT const BFDateFieldId LastProcDate;
   extern CLASS_IMPORT const BFDateFieldId NextProcessDate;
   extern CLASS_IMPORT const BFDateFieldId NextDrawDate;
   extern CLASS_IMPORT const BFDateFieldId PACDrawDeff;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFTextFieldId IsDuringNASU;
   extern CLASS_IMPORT const BFTextFieldId HasPACPurchasePending;
   extern CLASS_IMPORT const BFDateFieldId PACLastRunDate;
   extern CLASS_IMPORT const BFTextFieldId ACHPAC;
}

namespace TRADETYPE 
{
   extern CLASS_IMPORT I_CHAR * const PAC;
}

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_( "AccountCommitment" );
   const I_CHAR * const ACCOUNT_COMMITMENT_DETAILS = I_( "AcctCommitDetails" );
   const I_CHAR * const YES					= I_("Y");
   const I_CHAR * const NO					= I_("N");
}

namespace DATE_VALIDATION
{
	extern const I_CHAR * const PAC_LEAP_DATE;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,                    State Flags,             Group Flags 
   {ifds::AcctCommitMstrUUID,    BFCBO::READ_ONLY,    0}, 
   {ifds::CommitmentUUID,        BFCBO::REQUIRED,     0}, 
   {ifds::CommitmentCode,        BFCBO::READ_ONLY,    0}, 
   {ifds::CommitmentDesc,        BFCBO::READ_ONLY,    0}, 
   {ifds::CommitDeff,            BFCBO::REQUIRED,     0}, 
   {ifds::CommitEndDate,         BFCBO::READ_ONLY,    0}, 
   {ifds::BeneName,              BFCBO::READ_ONLY,    0}, 
   {ifds::OrigBeneName,          BFCBO::READ_ONLY,    0}, 
   {ifds::CommitStatus,          BFCBO::READ_ONLY,    0}, 
   {ifds::CommitStatusDesc,      BFCBO::READ_ONLY,    0}, 
   {ifds::CommitAmt,             BFCBO::NONE,         0}, 
   {ifds::OrigAccountNum,        BFCBO::READ_ONLY,    0}, 
   {ifds::CommissionPaid,        BFCBO::READ_ONLY,    0}, 
   {ifds::SurrChrgApplied,       BFCBO::READ_ONLY,    0}, 
   {ifds::MaxSurrCharges,        BFCBO::READ_ONLY,    0}, 
   {ifds::CommittedPACS,         BFCBO::READ_ONLY,    0}, 
   {ifds::PaidPACS,              BFCBO::READ_ONLY,    0}, 
   {ifds::MissingPACS,           BFCBO::READ_ONLY,    0}, 
   {ifds::Username,              BFCBO::READ_ONLY,    0}, 
   {ifds::ProcessDate,           BFCBO::READ_ONLY,    0}, 
   {ifds::ModUser,               BFCBO::READ_ONLY,    0}, 
   {ifds::ModDate,               BFCBO::READ_ONLY,    0}, 
   {ifds::PACID,                 BFCBO::READ_ONLY,    0}, 
   {ifds::PACDeff,               BFCBO::READ_ONLY,    0}, 
   {ifds::PACAmt,                BFCBO::READ_ONLY,    0}, 
   {ifds::PACStopDate,           BFCBO::READ_ONLY,    0}, 
   {ifds::InstCode,              BFCBO::READ_ONLY,    0}, 
   {ifds::SwiftCode,             BFCBO::READ_ONLY,    0}, 
   {ifds::RefNumber,             BFCBO::READ_ONLY,    0}, 
   {ifds::TransitNo,             BFCBO::READ_ONLY,    0}, 
   {ifds::BankAcctNum,           BFCBO::READ_ONLY,    0}, 
   {ifds::BankAcctName,          BFCBO::READ_ONLY,    0}, 
   {ifds::SourceOfBankAcct,      BFCBO::READ_ONLY,    0}, 
   {ifds::BankAcctCurrency,      BFCBO::READ_ONLY,    0}, 
   {ifds::BankAcctType,          BFCBO::READ_ONLY,    0}, 
   {ifds::BankType,              BFCBO::READ_ONLY,    0}, 
   {ifds::BankIdNum,             BFCBO::READ_ONLY,    0}, 
   {ifds::ACHProcessor,          BFCBO::READ_ONLY,    0}, 
   {ifds::BankId,                BFCBO::READ_ONLY,    0}, 
   {ifds::CreditInfoLine1,       BFCBO::READ_ONLY,    0}, 
   {ifds::CreditInfoLine2,       BFCBO::READ_ONLY,    0}, 
   {ifds::InstName,              BFCBO::READ_ONLY,    0}, 
   {ifds::BankAddr1,             BFCBO::READ_ONLY,    0}, 
   {ifds::BankAddr2,             BFCBO::READ_ONLY,    0}, 
   {ifds::BankAddr3,             BFCBO::READ_ONLY,    0}, 
   {ifds::BankAddr4,             BFCBO::READ_ONLY,    0}, 
   {ifds::BankAddr5,             BFCBO::READ_ONLY,    0}, 
   {ifds::BankContact,           BFCBO::READ_ONLY,    0}, 
   {ifds::BankCntry,             BFCBO::READ_ONLY,    0}, 
   {ifds::BankPstl,              BFCBO::READ_ONLY,    0}, 
   {ifds::PayReason1,            BFCBO::READ_ONLY,    0}, 
   {ifds::PayReason2,            BFCBO::READ_ONLY,    0}, 
   {ifds::PayMethod,             BFCBO::READ_ONLY,    0}, 
   {ifds::RunMode,               BFCBO::NONE,         0}, 
   {ifds::PaidPACSAmt,           BFCBO::READ_ONLY,    0}, 
   {ifds::LastProcDate,          BFCBO::READ_ONLY,    0}, 
   {ifds::NextProcessDate,       BFCBO::READ_ONLY,    0}, 
   {ifds::NextDrawDate,          BFCBO::NONE,         0}, 
   {ifds::IsDuringNASU,          BFCBO::NOT_ON_HOST,  0},
   {ifds::HasPACPurchasePending, BFCBO::READ_ONLY,    0},
};

static const int NUM_FIELDS = sizeof (classFieldInfo) / sizeof (BFCBO::CLASS_FIELD_INFO);
//******************************************************************************
// Constructors
//******************************************************************************

AccountCommitment::AccountCommitment( BFAbstractCBO &parent )
: MFCanBFCbo( parent ) 
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData ( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo,0,NULL);

}

//******************************************************************************

AccountCommitment::~AccountCommitment( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY AccountCommitment::init(const DString& dstrAccountNum)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );   

	BFData requestData (ifds::DSTC0432_REQ);
   DString mgmtCoIdOut;	
	requestData.setElementValue(ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );

   requestData.setElementValue (ifds::AccountNum, dstrAccountNum);
	
	ReceiveData (DSTC_REQUEST::ACCT_COMMIT_INQUIRY, requestData, ifds::DSTC0432_VW, DSTCRequestor (getSecurity(), true));


   setFieldReadOnly(ifds::BeneName, BF::HOST, true);
   setFieldReadOnly(ifds::OrigBeneName, BF::HOST, true);
   setFieldReadOnly(ifds::CommitDeff, BF::HOST, true);
   setFieldReadOnly(ifds::CommitmentUUID, BF::HOST, true);
   setFieldValid(ifds::BankAcctNum, BF::HOST, false);
   setFieldRequired(ifds::BankAcctNum, BF::HOST, true);
   
   setFieldNoValidate(ifds::RunMode, I_("Mod"), BF::HOST, false);

   AccountCommitmentDetailsList *pAccountCommitmentDetailsList;
   getCommitmentDetails(pAccountCommitmentDetailsList, BF::HOST);

   CommitmentProductList *pCommitmentProductList;
   if (getCommitmentProductList (pCommitmentProductList) <= WARNING && 
      pCommitmentProductList)
   {
      DString dstrSubstitutionList;
      pCommitmentProductList->getSubstitutionList(dstrSubstitutionList);

      setFieldAllSubstituteValues(ifds::CommitmentUUID, BF::HOST, dstrSubstitutionList);
   }
   //DString dstrCommitDeff;
   //getField(ifds::CommitDeff, dstrCommitDeff, BF::HOST, false);
   DString dstrNextProcessDate;
   getField(ifds::NextProcessDate, dstrNextProcessDate, BF::HOST, false);
   setFieldNoValidate(ifds::NextDrawDate, dstrNextProcessDate, BF::HOST, false, true, false, false);

   DString dstrCommitStatus;
   getField(ifds::CommitStatus, dstrCommitStatus, BF::HOST, false);

   if(dstrCommitStatus != I_("01"))
   {
      setFieldReadOnly(ifds::NextDrawDate, BF::HOST, true);
   }

   getNextPACLeapDate(_nextPACLeapDate, BF::HOST);
   loadFileProcessor(BF::HOST);
   return(GETCURRENTHIGHESTSEVERITY()); 
}

//******************************************************************************
SEVERITY AccountCommitment::initNew(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );   
   setObjectNew( );

   setFieldReadOnly(ifds::BeneName, idDataGroup, true);
   setFieldReadOnly(ifds::OrigBeneName, idDataGroup, true);
   setFieldReadOnly(ifds::CommitDeff, idDataGroup, false);
   setFieldValid(ifds::CommitDeff, idDataGroup, false);
   setFieldRequired(ifds::CommitDeff, idDataGroup, true);
   setFieldValid(ifds::CommitDeff, idDataGroup, false);
   setFieldRequired(ifds::CommitDeff, idDataGroup, true);
   setFieldValid(ifds::BankAcctNum, idDataGroup, false);
   setFieldRequired(ifds::BankAcctNum, idDataGroup, true);

   setFieldValid(ifds::InstCode, idDataGroup, false);
   setFieldRequired(ifds::InstCode, idDataGroup, true);
   setFieldValid(ifds::TransitNo, idDataGroup, false);
   setFieldRequired(ifds::TransitNo, idDataGroup, true);

   setFieldNoValidate(ifds::RunMode, I_("Add"), idDataGroup, false);

   AccountCommitmentDetailsList *pAccountCommitmentDetailsList = new AccountCommitmentDetailsList(*this);
   setObject(pAccountCommitmentDetailsList, ACCOUNT_COMMITMENT_DETAILS, OBJ_ACTIVITY_ADDED, idDataGroup);

   CommitmentProductList *pCommitmentProductList;
   if (getCommitmentProductList (pCommitmentProductList) <= WARNING && 
      pCommitmentProductList)
   {
      DString dstrSubstitutionList;
      pCommitmentProductList->getSubstitutionList(dstrSubstitutionList);
      setFieldAllSubstituteValues(ifds::CommitmentUUID, idDataGroup, dstrSubstitutionList);
      DString commitmentUUID;
      pCommitmentProductList->getActiveCommitment(commitmentUUID, idDataGroup);
      setFieldNoValidate(ifds::CommitmentUUID, commitmentUUID, idDataGroup, false);
      setFieldReadOnly(ifds::CommitmentUUID, idDataGroup, true);
   }
 //DString dstrCurrentBusinessDate;
 //  getWorkSession().getDateInHostFormat(dstrCurrentBusinessDate, DSTCWorkSession::DATE_TYPE::CURRENT_BUSINESS_DAY, idDataGroup);
 //  setField(ifds::CommitDeff, dstrCurrentBusinessDate, idDataGroup, false);
      setFieldReadOnly(ifds::NextDrawDate, idDataGroup, true);
   loadFileProcessor(idDataGroup);
   return(GETCURRENTHIGHESTSEVERITY());
}

SEVERITY AccountCommitment::getCommitmentProductList(CommitmentProductList *&pCommitmentProductList)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getCommitmentProductList") );   

   DSTCWorkSession & dstcWorkSession = getWorkSession();
   MgmtCo &mgmtCoOut = dstcWorkSession.getMgmtCo( );
   if (mgmtCoOut.getCommitmentProductList (pCommitmentProductList) > WARNING)
      pCommitmentProductList = NULL;

   return(GETCURRENTHIGHESTSEVERITY());
}

SEVERITY AccountCommitment::getCommitmentDetails( AccountCommitmentDetailsList *&pAccountCommitmentDetailsList, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getAccountCommitmentDetails" ) );
   pAccountCommitmentDetailsList = dynamic_cast<AccountCommitmentDetailsList*>(getObject(ACCOUNT_COMMITMENT_DETAILS, idDataGroup ));
   if (!pAccountCommitmentDetailsList)
   {
      DString dstrAcctCommitMstrUUID;
      getField(ifds::AcctCommitMstrUUID, dstrAcctCommitMstrUUID, idDataGroup, false);
      pAccountCommitmentDetailsList = new AccountCommitmentDetailsList(*this);
      if (pAccountCommitmentDetailsList->init(dstrAcctCommitMstrUUID)<=WARNING)
         setObject(pAccountCommitmentDetailsList, ACCOUNT_COMMITMENT_DETAILS, OBJ_ACTIVITY_NONE, idDataGroup );
      else
      {
         delete pAccountCommitmentDetailsList;
         pAccountCommitmentDetailsList = NULL;
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AccountCommitment::getBankInstructionsList(AcctCommitBankList *&pAcctCommitBankList, 
   const BFDataGroupId& idDataGroup, bool bCreate /*= true*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getBankInstructionsList"));
   
   BFObjectKey objKey(I_("AcctCommitBankList"), idDataGroup, OBJ_ACTIVITY_NONE, OBJ_TYPE_NONE);

   pAcctCommitBankList = NULL;
   pAcctCommitBankList = dynamic_cast<AcctCommitBankList*>(findObject(objKey));
   if (!pAcctCommitBankList && bCreate)
   {
      pAcctCommitBankList = new AcctCommitBankList(*this);
      if (pAcctCommitBankList)
      {
         DString dstrAccountNum;

         getField(ifds::AccountNum, dstrAccountNum, idDataGroup, false);

         SEVERITY severity = isNew() ? 
            pAcctCommitBankList->initNew(dstrAccountNum, idDataGroup) : 
            pAcctCommitBankList->init(dstrAccountNum, idDataGroup);

         if (severity <= WARNING)
         {
            setObject(objKey, pAcctCommitBankList);
         }
         else
         {
            delete pAcctCommitBankList;
            pAcctCommitBankList = NULL;
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

SEVERITY AccountCommitment::doValidateField( const BFFieldId &fieldId,
                                                   const DString& strValue,
                                                   const BFDataGroupId& idDataGroup )
{ 
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

   if( fieldId == ifds::CommitmentUUID) 
   {
      CommitmentProductList *pCommitmentProductList;
      if (getCommitmentProductList (pCommitmentProductList) <= WARNING && 
         pCommitmentProductList)
      {
         if(isNew() && pCommitmentProductList->isCommitmentProductEnded(strValue, idDataGroup))
         {
            ADDCONDITIONFROMFILE (CND::ERR_COMMITMENT_PRODUCT_NOT_ACTIVE);
         };
      }

   } 
   else if( fieldId == ifds::NextDrawDate) 
   {
      validateNextDrawDate(idDataGroup);
   }
   else if( fieldId == ifds::CommitDeff) 
   {
       // Validte "Commitment Effective Date" only in NASU.
       if (isNew())
       {
           DString dstrPACLastRunDate, dstrPACLastRunDate_Formatted;
           getWorkSession().getOption(ifds::PACLastRunDate, dstrPACLastRunDate, idDataGroup, false);
           getWorkSession().getOption(ifds::PACLastRunDate, dstrPACLastRunDate_Formatted, idDataGroup, true);

           if (DSTCommonFunctions::CompareDates(dstrPACLastRunDate, strValue) != DSTCommonFunctions::FIRST_EARLIER)
           {
               DString idiStr;
               addIDITagValue(idiStr, I_("LAST_RUN_DATE"), dstrPACLastRunDate_Formatted);
               ADDCONDITIONFROMFILEIDI(CND::ERR_NEXT_PROC_DATE_COMPARE_LAST_RUN_DATE, idiStr);
           }
       }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

SEVERITY AccountCommitment::validateEffectiveDate( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateEffectiveDate" ) ); 
   DString dstrAccountNum;
   getField(ifds::AccountNum, dstrAccountNum, idDataGroup, false);
   MFAccount* pMFAccount = NULL;
   pMFAccount = dynamic_cast<MFAccount*> (getParent());
   if(pMFAccount)
   {
      DString dstrAcctEffDate;
      pMFAccount->getField(ifds::EffectiveDate, dstrAcctEffDate, idDataGroup, false);
      DString dstrCommitEffDate;
      getField(ifds::CommitDeff, dstrCommitEffDate, idDataGroup, false);
      if(DSTCommonFunctions::CompareDates(dstrAcctEffDate, dstrCommitEffDate) == DSTCommonFunctions::SECOND_EARLIER)
      {
         ADDCONDITIONFROMFILE (CND::ERR_MATSWP_EFFECTIVE_DATE);
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

SEVERITY AccountCommitment::validateNextDrawDate( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateMgmtFeePayOption" ) ); 

   if(!isNew())
   {
	   if (hasProcessedPAC(idDataGroup)) // PAC has already been processed.
	   {
		   DString dstrCurrBusDate;
		   getWorkSession ().getOption (ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false);

		   DString dstrPACDrawDeff;
		   getField(ifds::NextDrawDate, dstrPACDrawDeff, idDataGroup, false);

		   BFDate bfCurrBusDate(dstrCurrBusDate, BFDate::DATE_FORMAT::DF_HOST);
		   BFDate bfPACDrawDeff(dstrPACDrawDeff, BFDate::DATE_FORMAT::DF_HOST);

		   BFDate bfMaxBussDate(bfCurrBusDate); 
		   bfMaxBussDate.setDay(1);
		   bfMaxBussDate.addMonths(2);

		   if((bfCurrBusDate > bfPACDrawDeff || bfMaxBussDate <= bfPACDrawDeff)) 
		   {
			   ADDCONDITIONFROMFILE (CND::ERR_INVALID_DATE);
		   };
	   }
	   else
	   {
		   DString dstrNextDrawDate, dstrHasPACPurchasePending, dstrCurrBusDate, dstrCommitDeff;
		   DString maxDate;

		   getField(ifds::NextDrawDate, dstrNextDrawDate, idDataGroup);
		   getField(ifds::CommitDeff, dstrCommitDeff, idDataGroup);
		   getField(ifds::HasPACPurchasePending, dstrHasPACPurchasePending, idDataGroup);
		   getWorkSession().getOption(ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false);

		   // Maximum Date = The end of 2nd month from the NextDrawDate date
		   // Ex. NextDrawDate: 17/08/2013, The Maximum Date is 30/09/2013
		   BFDate bfNextDrawDate(dstrNextDrawDate, BFDate::DATE_FORMAT::DF_HOST);
		   BFDate bfMaxNextDrawDate(dstrCommitDeff, BFDate::DATE_FORMAT::DF_HOST);

		   bfMaxNextDrawDate.setDay(1);
		   bfMaxNextDrawDate.addMonths(2);

		   if (dstrHasPACPurchasePending == YES)
		   {
			   getErrMsg(IFASTERR::PENDING_OR_UNSETTLED_TRADE_EXISTS,
				   CND::ERR_PENDING_OR_UNSETTLED_TRADE_EXISTS, 
				   CND::WARN_PENDING_OR_UNSETTLED_TRADE_EXISTS, 
				   idDataGroup);
		   }   
		   else if (DSTCommonFunctions::CompareDates(dstrNextDrawDate, dstrCurrBusDate) == DSTCommonFunctions::FIRST_EARLIER)
		   {
			   ADDCONDITIONFROMFILE(CND::ERR_INVALID_DATE);
		   }
		   else if (DSTCommonFunctions::CompareDates(dstrNextDrawDate, _nextPACLeapDate) == DSTCommonFunctions::FIRST_EARLIER)
		   {   // The date of this error message should depend on Generic Control named "System PACs"
			   getErrMsg(IFASTERR::DATE_MUST_BE_EQUAL_OR_GREATER_THAN_CURR_DATE_PLUS_3_BUSS_DATE,
						 CND::ERR_DATE_MUST_BE_EQUAL_OR_GREATER_THAN_CURR_DATE_PLUS_3_BUSS_DATE, 
						 CND::WARN_DATE_MUST_BE_EQUAL_OR_GREATER_THAN_CURR_DATE_PLUS_3_BUSS_DATE, 
						 idDataGroup);
		   }
		   else if (bfNextDrawDate >= bfMaxNextDrawDate)
		   {  
			   getErrMsg(IFASTERR::DATE_MUST_BE_EQUAL_OR_EARLIER_THAN_2ND_DIPLOMA_COMM_DATE,
						 CND::ERR_DATE_MUST_BE_EQUAL_OR_EARLIER_THAN_2ND_DIPLOMA_COMM_DATE, 
						 CND::WARN_DATE_MUST_BE_EQUAL_OR_EARLIER_THAN_2ND_DIPLOMA_COMM_DATE, 
						 idDataGroup);
		   }
	   }
       //As the PAC's Effective Date is drived by Next Draw Date, error message for PAC's effective date -
       //should be displayed here.
       RESPPACDateCalculator rRESPPACDateCalculator(*this);
       DString dstrPACDeff, dstrPACDrawDeff, dstrAcctCommitMstrUUID, dstrPACLastRunDate, dstrPACLastRunDate_Formatted;

       getWorkSession().getOption(ifds::PACLastRunDate, dstrPACLastRunDate, idDataGroup, false);
       getWorkSession().getOption(ifds::PACLastRunDate, dstrPACLastRunDate_Formatted, idDataGroup, true);

       getField(ifds::PACDeff, dstrPACDeff, idDataGroup);
       getField(ifds::NextDrawDate, dstrPACDrawDeff, idDataGroup);
       getField(ifds::AcctCommitMstrUUID, dstrAcctCommitMstrUUID, idDataGroup);

       if (rRESPPACDateCalculator.init(dstrAcctCommitMstrUUID, dstrPACDeff, dstrPACDrawDeff) <= WARNING)
       {
           rRESPPACDateCalculator.getField(ifds::PACDeff, _dstrNewPACDeff, idDataGroup, false);
           rRESPPACDateCalculator.getField(ifds::NextProcessDate, _dstrNewPACDrawDeff, idDataGroup, false);

           if (DSTCommonFunctions::CompareDates(dstrPACLastRunDate, _dstrNewPACDrawDeff) != DSTCommonFunctions::FIRST_EARLIER)
           {
               DString idiStr;
               addIDITagValue(idiStr, I_("LAST_RUN_DATE"), dstrPACLastRunDate_Formatted);
               ADDCONDITIONFROMFILEIDI(CND::ERR_NEXT_PROC_DATE_COMPARE_LAST_RUN_DATE, idiStr);
           }
       }
   }

   return( GETCURRENTHIGHESTSEVERITY() );
}

//******************************************************************************
SEVERITY AccountCommitment::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

   if (idField == ifds::NextDrawDate)
   {
       setField(ifds::PACDeff, _dstrNewPACDeff, idDataGroup, false, true);
       setField(ifds::NextProcessDate, _dstrNewPACDrawDeff, idDataGroup, false, true);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AccountCommitment::loadFileProcessor(const BFDataGroupId& idDataGroup)
{
  MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("loadFileProcessor"));
  DString dstrPayMethod, dstrAchControl;

  getWorkSession().getOption2(ifds::ACHPAC, dstrAchControl, idDataGroup, false );

  if(dstrAchControl == I_("Y"))
  {
    DynamicSubListHolder* pDynamicSubListHolder = getMgmtCo().getDynamicSubListHolder();
    
    DString dstrPayMethod, dstrCurrency, dstrSubsList;

    if(DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA)
      dstrPayMethod = I_("EFT");

    getField (ifds::BankAcctCurrency, dstrCurrency, idDataGroup, false);
    dstrCurrency.strip();

    dstrSubsList = pDynamicSubListHolder->getFileProcSubList(TRADETYPE::PAC, dstrPayMethod, dstrCurrency);
    setFieldAllSubstituteValues (ifds::ACHProcessor, idDataGroup, dstrSubsList);
  }
  return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void AccountCommitment::getNextPACLeapDate(DString &dstrNextPACLeapDate, const BFDataGroupId& idDataGroup)
{
	DateValidation pDateValidation(*this);

	getWorkSession().getOption(ifds::CurrBusDate, dstrNextPACLeapDate, idDataGroup, false);

	SEVERITY sevRtn = pDateValidation.init(DATE_VALIDATION::PAC_LEAP_DATE, 
											NULL_STRING,		
											NULL_STRING,		
											dstrNextPACLeapDate,	
											NULL_STRING,
											NULL_STRING,
											NULL_STRING,
											NULL_STRING,
											NULL_STRING,
											NULL_STRING,
											NULL_STRING,
											NULL_STRING,
											NO,			
											NULL_STRING,
											NULL_STRING,
											NULL_STRING,
											NULL_STRING,
											NULL_STRING,
											NULL_STRING,
											NULL_STRING,
											NULL_STRING,
											NULL_STRING,
											NULL_STRING,
											NULL_STRING,
											NO,         
											NULL_STRING);

	if (sevRtn <= WARNING)
	{
		pDateValidation.getField(ifds::EffectiveDate, dstrNextPACLeapDate, idDataGroup, false);
	}
	else
	{
		dstrNextPACLeapDate = NULL_STRING;
	}
}


//******************************************************************************
bool AccountCommitment::hasProcessedPAC(const BFDataGroupId& idDataGroup)
{
	DString dstrPaidPACS;
	getField(ifds::PaidPACS, dstrPaidPACS, idDataGroup);
	BigDecimal bdPaidPACs(dstrPaidPACS);

	return (bdPaidPACs >= 1);
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AccountCommitment.cpp-arc  $
// 
//    Rev 1.15   08 Aug 2012 14:23:04   if991250
// IN 3038139 do not validate the old commitment expiry for existing contracts
// 
//    Rev 1.14   Jul 06 2012 15:20:30   if991250
// Defaulting Next Draw date  to Next Proc Date
// 
//    Rev 1.13   Jun 28 2012 14:19:42   if991250
// Next Draw date doesn't need to be validated in NASU
// 
//    Rev 1.12   Jun 27 2012 10:34:32   if991250
// next draw date validation, display last proc date
// 
//    Rev 1.11   Jun 26 2012 17:35:08   if991250
// PAC Draw Date
// 
//    Rev 1.10   Jun 22 2012 13:09:56   if991250
// INA: PAC Draw Date
// 
//    Rev 1.9   Apr 30 2012 15:31:04   popescu
// 2902002 - P0186480FN02 - Diploma DSK Validation
// 
//    Rev 1.8   Apr 25 2012 16:19:16   if991250
// Commitment eff date needs to be empty for new shareholder
// 
//    Rev 1.7   Mar 08 2012 09:56:02   if991250
// Account Commitment
// 
//    Rev 1.6   Mar 02 2012 12:55:26   if991250
// Account Commitment in NASU
// 
//    Rev 1.5   Feb 27 2012 15:33:24   if991250
// NASU, Commitment Id
// 
//    Rev 1.4   Feb 24 2012 18:40:06   if991250
// Account Commitment
// 
//    Rev 1.3   Feb 22 2012 16:56:12   if991250
// Account Commitment
// 
//    Rev 1.1   Feb 17 2012 10:24:58   if991250
// Account Commitment
// 
//    Rev 1.0   Feb 14 2012 13:26:12   if991250
// Initial revision.
 * 
 *
 */