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
// ^FILE   : SearchProcess.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : 03/08/1999
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : SearchProcess
//    This class defines the search business process
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "searchprocess.hpp"
#include "searchprocessincludes.h"

#include "accinfoprocessincludes.h"
#include "addressprocessincludes.h"
#include "allocationsprocessincludes.h"
#include "amsmstprocessincludes.h"
#include "bankinstructionsprocessincludes.h"
#include "certificateprocessincludes.h"
#include "chequeprocessincludes.h"
#include "coaprocessincludes.h"
#include "entitysearchprocessincludes.h"
#include "fillsearchcriteriaprocessincludes.h"
#include "nasuprocessincludes.h"
#include "shareholderprocessincludes.h"
#include "systematicprocessincludes.h"
#include "mfcaninterprocparam.hpp"


extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ENTITY_SEARCH;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_CHEQUE;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_CERTIFICATE;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_SYSTEMATIC;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_BANK_INSTRUCTIONS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ADDRESSES;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_COA;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_DISTRIBUTION;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ALLOCATIONS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_SHAREHOLDER;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ACCINFO;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_SEARCH;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_AMS_GLOBAL;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ENTITY_ALONE_PROCESS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ACCT_REGIS_MAINT;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< SearchProcess > processCreator(CMD_BPROC_SEARCH);

namespace SRCHLIT
{
   const I_CHAR * const SEARCH_CRITERIA_CODE = I_("SearchCriteriaCode");
   const I_CHAR * const SEARCH_USING_CODE    = I_("SearchUsingCode");
   const I_CHAR * const FIRST_VALUE          = I_("FirstValue");
   const I_CHAR * const SECOND_VALUE         = I_("SecondValue");
   const I_CHAR * const THIRD_VALUE          = I_("ThirdValue");
   const I_CHAR * const FROM_SEARCH          = I_("FromSearch");
   const I_CHAR * const BACKGROUND_SEARCH    = I_("BackgroundSearch");
   const I_CHAR * const ALLENTITY            = I_("AllEntity");
   const I_CHAR * const EXACTSEARCH          = I_("ExactSearch");
   const I_CHAR * const NO_VERIFYSEARCH_IF_ONE_MATCH = I_( "NoVerifySearchIfOneMatch" );
   const I_CHAR * const WHERE_USED_CODE      = I_ ("WhereUsedCode");
}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const DEFAULT;
   extern CLASS_IMPORT I_CHAR * const SHAREHOLDER;
   extern CLASS_IMPORT I_CHAR * const BROKER;
   extern CLASS_IMPORT I_CHAR * const BRANCH;
   extern CLASS_IMPORT I_CHAR * const SALESREP;
   extern CLASS_IMPORT I_CHAR * const FUND;
   extern CLASS_IMPORT I_CHAR * const CLIENT;
   extern CLASS_IMPORT I_CHAR * const TRADE;
   extern CLASS_IMPORT I_CHAR * const PENDING_TRADE;
   extern CLASS_IMPORT I_CHAR * const PENDING;
   extern CLASS_IMPORT I_CHAR * const FUND_CLASS;
   extern CLASS_IMPORT I_CHAR * const FUND_SPONSOR;
   extern CLASS_IMPORT I_CHAR * const SYSTEMATIC;
   extern CLASS_IMPORT I_CHAR * const DISTRIBUTION;
   extern CLASS_IMPORT I_CHAR * const TRANSACTION;
   extern CLASS_IMPORT I_CHAR * const SETTLEMENT;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_("SearchProcess");
   const I_CHAR * const YES = I_("Y");
   const I_CHAR * const NO = I_("N");
}

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319SearchProcess::SearchProcess() : 
SearchProcess::SearchProcess(GenericInterfaceContainer* pGIC, 
   GenericInterface* pGIParent, const Command& rCommand)
: AbstractProcess(pGIC, pGIParent, rCommand)
, _searchCriteria(NULL_STRING)

{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
}

//******************************************************************************

SearchProcess::~SearchProcess()
{
   TRACE_DESTRUCTOR(CLASSNAME);

}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY SearchProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, DOINIT);
   SEVERITY sevRtn = SEVERE_ERROR;

   try
   {
      getParameter(SRCHLIT::SEARCH_CRITERIA_CODE, _searchCriteria);
      getParameter(SRCHLIT::SEARCH_USING_CODE, _searchUsing);
      getParameter(SRCHLIT::FIRST_VALUE, _firstValue);
      getParameter(SRCHLIT::SECOND_VALUE, _secondValue);
      getParameter(SRCHLIT::THIRD_VALUE, _thirdValue);
      getParameter(SRCHLIT::BACKGROUND_SEARCH, _backgroundSearch);
      getParameter(SRCHLIT::ALLENTITY, _allEntity);
      getParameter(SRCHLIT::EXACTSEARCH, _exactSearch);
      getParameter(SRCHLIT::NO_VERIFYSEARCH_IF_ONE_MATCH, _noVerifySearchIfOneMatch);
      getParameter(SRCHLIT::WHERE_USED_CODE, _whereUsedCode);
      getParameter (I_("ShowSameEntityMultipleTimes"), _showSameEntityMultipleTimes);

      sevRtn = NO_CONDITION;
   }
   catch(ConditionException &ce)
   {
      SETCONDITIONFROMEXCEPTION(ce);
   }
   catch(...)
   {
      assert(0);
      THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return(sevRtn);
}

//******************************************************************************
E_COMMANDRETURN SearchProcess::doProcess()
{  
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS);
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      getParent()->setParameter(SRCHLIT::FROM_SEARCH, YES);
      //retrieveing the search parameter
      if(_searchCriteria == SEARCHCRITERIA::ACCOUNT_SEARCH)
      {
         getParent()->setParameter (ENTSRCHLIT::SEARCH_CODE, _searchUsing);
         getParent()->setParameter (ENTSRCHLIT::FIRST_VALUE, _firstValue);
         getParent()->setParameter (ENTSRCHLIT::SECOND_VALUE, _secondValue);
         getParent()->setParameter (SRCHLIT::BACKGROUND_SEARCH, _backgroundSearch);
         getParent()->setParameter (SRCHLIT::NO_VERIFYSEARCH_IF_ONE_MATCH, _noVerifySearchIfOneMatch);
         getParent()->setParameter (SRCHLIT::ALLENTITY, _allEntity);
         getParent()->setParameter (I_("ShowSameEntityMultipleTimes"), _showSameEntityMultipleTimes);
         getParent()->setParameter (SRCHLIT::EXACTSEARCH, _exactSearch);
         getParent()->setParameter (SRCHLIT::WHERE_USED_CODE, _whereUsedCode);
         rtn = invokeCommand( getParent(), 
                              CMD_BPROC_ENTITY_SEARCH, 
                              getProcessType(), 
                              true, 
                              NULL);
      }
      else if(_searchCriteria == SEARCHCRITERIA::CHEQUE_SEARCH)
      {
         if(_searchUsing == SEARCHCHEQUEUSING::CHEQUE_NUMBER)
            getParent()->setParameter(CHQPROC::IN_CHEQ_NUM_VALUE, 
                                       _firstValue);
         else if(_searchUsing == SEARCHCHEQUEUSING::ACCOUNT_NUMBER)
		 {
            getParent()->setParameter(CHQPROC::ACCOUNT_NUM_VALUE, _firstValue);
            getParent()->setParameter(CHQPROC::STATUS_VALUE, _secondValue);
		 }
		 else if(_searchUsing == SEARCHCHEQUEUSING::BROKER)
		 {
            getParent()->setParameter(CHQPROC::BROKER_VALUE, _firstValue);
            getParent()->setParameter(CHQPROC::STATUS_VALUE, _secondValue);
		 }
         //invoking the cheque business process
         getParent()->setParameter(CERTLIT::IGNOREDNF, NO);
         rtn = invokeCommand(getParent(), CMD_BPROC_CHEQUE, PROC_NO_TYPE, 
                              false, NULL);
      }
      else if(_searchCriteria == SEARCHCRITERIA::CERTIFICATE_SEARCH)
      {
         if(_searchUsing == SEARCHCERTIFICATEUSING::CERTIFICATE_NUMBER_AND_FUND_CODE)
         {
            getParent()->setParameter(CERTLIT::INCERTNUM, _firstValue);
            getParent()->setParameter(CERTLIT::INFUND, _secondValue);            
         }
         else if(_searchUsing == SEARCHCERTIFICATEUSING::ACCOUNT_NUMBER)
            getParent()->setParameter(CERTLIT::INACCTNUM, _firstValue);
         getParent()->setParameter(CERTLIT::IGNOREDNF, NO);
         getParent()->setParameter(CERTLIT::IGNORENOTENINFO, NO);
         //invoking the certificate business process
         rtn = invokeCommand(getParent(), CMD_BPROC_CERTIFICATE, PROC_NO_TYPE, 
                              false, NULL);
      }
      else if(_searchCriteria == SEARCHCRITERIA::SYSTEMATICS_SEARCH)
      {
         if(_searchUsing == SEARCHSYSTEMATICSUSING::ACCOUNT_NUMBER)
            getParent()->setParameter(SYSTEMATICLIT::ACCOUNT_NUM, _firstValue);
         //invoking the systematic business process
         rtn = invokeCommand(getParent(), CMD_BPROC_SYSTEMATIC, PROC_NO_TYPE, 
                              false, NULL);
      }
      else if(_searchCriteria == SEARCHCRITERIA::BANKING_SEARCH)
      {
         if(_searchUsing == SEARCHBANKINGUSING::ACCOUNT_NUMBER ||
             _searchUsing == SEARCHBANKINGUSING::NEW_ACCOUNT_NUMBER)
         {
            getParent()->setParameter(MFCAN_IP_PARAM::BANK_TYPE, BANKTYPE::SHAREHOLDER);
            getParent()->setParameter(MFCAN_IP_PARAM::ACCOUNT_NUM, _firstValue);
         }
         else if(_searchUsing == SEARCHBANKINGUSING::BROKER_CODE)
         {
            getParent()->setParameter(MFCAN_IP_PARAM::BANK_TYPE, BANKTYPE::BROKER);
            getParent()->setParameter(MFCAN_IP_PARAM::BROKER_CODE, _firstValue);

         }
         else if(_searchUsing == SEARCHBANKINGUSING::BRANCH_CODE)
         {
            getParent()->setParameter(MFCAN_IP_PARAM::BANK_TYPE, BANKTYPE::BRANCH);
            getParent()->setParameter(MFCAN_IP_PARAM::BROKER_CODE, _firstValue);
            getParent()->setParameter(MFCAN_IP_PARAM::BRANCH_CODE, _secondValue);
         }
         else if(_searchUsing == SEARCHBANKINGUSING::REP_CODE)
         {
            getParent()->setParameter(MFCAN_IP_PARAM::BANK_TYPE, BANKTYPE::SALESREP);
            getParent()->setParameter(MFCAN_IP_PARAM::BROKER_CODE, _firstValue);
            getParent()->setParameter(MFCAN_IP_PARAM::BRANCH_CODE, _secondValue);
            getParent()->setParameter(MFCAN_IP_PARAM::SALES_REP_CODE, _thirdValue);
         }
         else if(_searchUsing == SEARCHBANKINGUSING::CLIENT)
         {
            getParent()->setParameter(MFCAN_IP_PARAM::BANK_TYPE, BANKTYPE::CLIENT);
            //getParent()->setParameter(MFCAN_IP_PARAM::BANK_TYPE_CLIENT, _firstValue);
         }
         else if (_searchUsing == SEARCHBANKINGUSING::FUND)
         {
            getParent()->setParameter(MFCAN_IP_PARAM::BANK_TYPE, BANKTYPE::FUND);
            //should change the name the param, here, use a namespace
            getParent()->setParameter(MFCAN_IP_PARAM::FUND_CODE, _firstValue);
         }
         else if (_searchUsing == SEARCHBANKINGUSING::FUND_CLASS)
         {
            getParent()->setParameter(MFCAN_IP_PARAM::BANK_TYPE, BANKTYPE::FUND_CLASS);
            getParent()->setParameter(MFCAN_IP_PARAM::FUND_CODE, _firstValue);
            getParent()->setParameter(MFCAN_IP_PARAM::CLASS_CODE, _secondValue);
         }
         else if (_searchUsing == SEARCHBANKINGUSING::FUND_GROUP)
         {
            getParent()->setParameter(MFCAN_IP_PARAM::BANK_TYPE, BANKTYPE::FUND_GROUP);
            getParent()->setParameter(MFCAN_IP_PARAM::FUND_GROUP, _firstValue);
         }
         else if (_searchUsing == SEARCHBANKINGUSING::FUND_SPONSOR)
         {
            getParent()->setParameter (MFCAN_IP_PARAM::BANK_TYPE, BANKTYPE::FUND_SPONSOR);
            getParent()->setParameter (MFCAN_IP_PARAM::FUNDSPONSOR, _firstValue);
         }
		 else if(_searchUsing == SEARCHBANKINGUSING::REG_AGENT)
		 {

			 getParent()->setParameter (MFCAN_IP_PARAM::BANK_TYPE, BANKTYPE::REG_AGENT);
			 getParent()->setParameter (MFCAN_IP_PARAM::REGAGENT, _firstValue);
		 }

         getParent()->setParameter(MFCAN_IP_PARAM::ID_VALUE, _firstValue);
         //invoking the banking business process
         rtn = invokeCommand(getParent(), CMD_BPROC_BANK_INSTRUCTIONS, PROC_NO_TYPE, false, NULL);
      }
      else if(_searchCriteria == SEARCHCRITERIA::ENTITY_SEARCH)
      {
         getParent()->setParameter(ENTSRCHLIT::SEARCH_CODE, _searchUsing);
         getParent()->setParameter(ENTSRCHLIT::FIRST_VALUE, _firstValue);
         getParent()->setParameter(ENTSRCHLIT::SECOND_VALUE, _secondValue);
         getParent()->setParameter(ENTSRCHLIT::ENTITY_SEARCH, YES);
         getParent()->setParameter(SRCHLIT::BACKGROUND_SEARCH, _backgroundSearch);
         getParent()->setParameter(SRCHLIT::ALLENTITY, _allEntity);
         getParent()->setParameter(SRCHLIT::EXACTSEARCH, _exactSearch);
         getParent()->setParameter (SRCHLIT::WHERE_USED_CODE, _whereUsedCode);
         rtn = invokeCommand(getParent(), CMD_BPROC_ENTITY_SEARCH, getProcessType(), true, NULL);
      }
      else if(_searchCriteria == SEARCHCRITERIA::ALLENTITY_SEARCH)
      {
         getParent()->setParameter(ENTSRCHLIT::SEARCH_CODE, _searchUsing);
         getParent()->setParameter(ENTSRCHLIT::FIRST_VALUE, _firstValue);
         getParent()->setParameter(ENTSRCHLIT::SECOND_VALUE, _secondValue);
         getParent()->setParameter(ENTSRCHLIT::ENTITY_SEARCH, YES);
         rtn = invokeCommand(getParent(), CMD_BPROC_ENTITY_ALONE_PROCESS,PROC_NO_TYPE, false, NULL);
      }
      else if(_searchCriteria == SEARCHCRITERIA::ADDRESS_SEARCH)
      {
         if(_searchUsing == SEARCHADDRESSUSING::ACCOUNT_NUMBER)
         {
            getParent()->setParameter(ADDRLIT::ACCOUNT_NUM, _firstValue);
         }
         else if(_searchUsing == SEARCHADDRESSUSING::SHAREHOLDER_NUMBER)
         {
            getParent()->setParameter(ADDRLIT::SHAREHOLDER_NUM, _firstValue);
         }
         //invoking the addresses business process
         rtn = invokeCommand(getParent(), CMD_BPROC_ADDRESSES, PROC_NO_TYPE, false, NULL);
      }
      else if(_searchCriteria == SEARCHCRITERIA::COA_SEARCH)
      {
         if(_searchUsing == SEARCHCOAUSING::ACCOUNT_NUMBER)
            getParent()->setParameter(COALIT::ACCOUNT_NUM, _firstValue);
         //invoking the coa business process
         rtn = invokeCommand(getParent(), CMD_BPROC_COA, PROC_NO_TYPE, true, 
                              NULL);
      }
      else if(_searchCriteria == SEARCHCRITERIA::DISTRIBUTIONS_SEARCH)
      {
         if(_searchUsing == SEARCHDISTRIBUTIONSUSING::ACCOUNT_NUMBER)
         {
            //TODO fixme
            getParent()->setParameter(I_("AccountNum"), _firstValue);
            //getParent()->setParameter(ACCDISTRIBLIT::ACCOUNT_NUM, _firstValue);
         }
         //invoking the distributions business process
         rtn = invokeCommand(getParent(), CMD_BPROC_DISTRIBUTION, PROC_NO_TYPE, 
                              false, NULL);
      }
      else if(_searchCriteria == SEARCHCRITERIA::ALLOCATIONS_SEARCH)
      {
         assert(_searchUsing == SEARCHALLOCATIONSUSING::ACCOUNT_NUMBER);
         setParameter(ALLOCATIONSPROC::ACCOUNT_NUM, _firstValue);
         setParameter(ALLOCATIONSPROC::ALLOCATION_TYPE, 
                       ALLOCATIONSPROC::SHAREHOLDER_DEFAULT);
         setParameter(MFCAN_IP_PARAM::CALLER, I_("SearchDefault"));
         //invoking the allocations business process
         rtn = invokeCommand(getParent(), CMD_BPROC_ALLOCATIONS, PROC_NO_TYPE, 
                              false, NULL);
      }
      else if(_searchCriteria == SEARCHCRITERIA::SHAREHOLDER_INFO_SEARCH)
      {
         if(_searchUsing == SEARCHSHAREHOLDERUSING::ACCOUNT_NUMBER)
            getParent()->setParameter(SHRPROC::ACCOUNT_NUM, _firstValue);
         else if(_searchUsing == SEARCHSHAREHOLDERUSING::SHAREHOLDER_NUMBER)
            getParent()->setParameter(SHRPROC::SHAREHOLDER_NUM, _firstValue);
         //not a NASU process
         getParent()->setParameter(NASULIT::CREATING_SHAREHOLDER, NO);
         //invoking the shareholder business process
         rtn = invokeCommand(getParent(), CMD_BPROC_SHAREHOLDER, PROC_NO_TYPE, 
                              false, NULL);
      }
      else if(_searchCriteria == SEARCHCRITERIA::ACCOUNT_INFO_SEARCH)
      {
         if(_searchUsing == SEARCHACCOUNTINFOUSING::ACCOUNT_NUMBER)
         {
            getParent()->setParameter(ACCINFOPROC::ACCOUNT_NUM, _firstValue);
            //not a NASU process
            getParent()->setParameter(NASULIT::CREATING_ACCOUNT, NO);
            getParent()->setParameter(NASULIT::CREATING_SHAREHOLDER, NO);
         }
         else
            assert(0);
         //invoking the account info business process
         rtn = invokeCommand(getParent(), CMD_BPROC_ACCINFO, PROC_NO_TYPE, 
                              false, NULL);
      }
      else if(_searchCriteria == SEARCHCRITERIA::TRADE_SEARCH)
      {
         getParent()->setParameter(ENTSRCHLIT::SEARCH_CODE, _searchUsing);
         getParent()->setParameter(ENTSRCHLIT::FIRST_VALUE, _firstValue);
         getParent()->setParameter(ENTSRCHLIT::SECOND_VALUE, _secondValue);
         getParent()->setParameter(ENTSRCHLIT::TRADE_SEARCH, YES);
         rtn = invokeCommand(getParent(), CMD_BPROC_ENTITY_SEARCH, 
            getProcessType(), true, NULL);                          
      }
      else if(_searchCriteria == SEARCHCRITERIA::AMSGLOBAL_SEARCH)
	   {
         if(_searchUsing == SEARCHGLOBALUSING::REBALANCING)
         {
            getParent()->setParameter(AMS_Para::AMS_TYPE, I_("RB"));
         }
         else if (_searchUsing == SEARCHGLOBALUSING::REPORT)
         {
            getParent()->setParameter(AMS_Para::AMS_TYPE, I_("RO"));
         }
         getParent()->setParameter(AMS_Para::AMS_CODE, _firstValue);
         rtn = invokeCommand(getParent(), CMD_BPROC_AMS_GLOBAL, PROC_NO_TYPE, 
            false, NULL);				
      }
      else if(_searchCriteria == SEARCHCRITERIA::ACCOUNT_REGULATORY_SEARCH )
      {
         setParameter (I_("AcctExsistencySearch"),I_("Y"));
         if(_searchUsing == SEARCHACCOUNTREGULATORYUSING::ACCOUNT_NUMBER)
         {
            setParameter (ENTSRCHLIT::SEARCH_CODE, SEARCHACCOUNTUSING::ACCOUNT_NUMBER);
            setParameter (ENTSRCHLIT::FIRST_VALUE, _firstValue);
         }
         else if(_searchUsing == SEARCHACCOUNTREGULATORYUSING::OTHER_REFERENCE_NUMBER)
         {
            setParameter (ENTSRCHLIT::SEARCH_CODE, SEARCHACCOUNTUSING::OTHER_REFERENCE_NUMBER);
            setParameter (ENTSRCHLIT::FIRST_VALUE, _firstValue);
         }

         rtn = invokeCommand( this, 
                              CMD_BPROC_ENTITY_SEARCH, 
                              getProcessType(), 
                              true, 
                              NULL);

         if(rtn == CMD_OK)
         {
            DString searchAcctNum;
            getParameter(ACCDETLIT::ACCOUNT_NUMBER_FIELD, searchAcctNum);
            getParent()->setParameter(MFCAN_IP_PARAM::ACCOUNT_NUM,searchAcctNum);
            getParent()->setParameter(MFCAN_IP_PARAM::CALLER, I_("MainSearch"));
            rtn = invokeCommand(getParent(), 
                                CMD_BPROC_ACCT_REGIS_MAINT,
                                PROC_NO_TYPE, 
                                false, 
                                NULL);
         }
      }
      else
      {
         assert(0);
         throw;
      }
   }
   catch(ConditionException &)
   {
      throw;
   }
   catch(...)
   {
      assert(0);
      THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS, CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   //tell to the container to delete the search process
   if(rtn == CMD_MODELESS_INPROCESS)
   {
      rtn = CMD_OK;
   }
   return(rtn);
}

//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/SearchProcess.cpp-arc  $
 * 
 *    Rev 1.35   Apr 27 2012 09:52:02   if991250
 * CPF - Account Setup & Settlement 
 * 
 *    Rev 1.34   Apr 04 2012 11:35:28   wp040039
 * PETP0187485-Registration Agent  Banking
 * 
 *    Rev 1.33   26 Jan 2009 12:07:50   popescu
 * Incident 1559745 - find clearing platform entities whether they were linked or not to an account - 
 * 
 *    Rev 1.32   Sep 08 2008 15:54:20   jankovii
 * PET 5517 FN71 - Stale Cheque.
 * 
 *    Rev 1.31   Oct 18 2006 15:53:18   popescu
 * PET 2217/26 STP Multiple Debit Accounts - fund sponsor banking
 * 
 *    Rev 1.30   May 11 2006 16:16:20   popescu
 * Incident #588425 -Process should die for any callers, but search
 * 
 *    Rev 1.29   Jan 04 2006 10:03:26   fengyong
 * Incident #503893: add parameter "_exactsearch" for account search.
 * 
 *    Rev 1.28   Apr 14 2005 11:07:02   popescu
 * Incident #262507, Multiple a/c with same alternate a/c
 * 
 *    Rev 1.27   Mar 09 2005 16:08:02   yingbaol
 * PET1171,FN01:EU saving entity update
 * 
 *    Rev 1.26   Dec 07 2004 02:45:02   popescu
 * PET 1117/56, verify search won't pop-up if alt acct/other ref # search returns one match
 * 
 *    Rev 1.25   Nov 05 2004 16:25:38   FENGYONG
 * PET1117 FN54 Fund Broker Static : Add AllEntityField and ExactSearch 
 * 
 *    Rev 1.24   Sep 21 2004 13:20:14   HERNANDO
 * PET1094 FN06 - Absatcmeldung Files enhancement.
 * 
 *    Rev 1.23   Aug 10 2004 11:13:46   FENGYONG
 * PET117 FN5 - Client Condition Fee
 * 
 *    Rev 1.22   Sep 03 2003 17:16:04   popescu
 * fixes regarding calling the allocation screen, seems that more places that originally thought are using the allocation screen
 * 
 *    Rev 1.21   Jul 01 2003 13:04:08   popescu
 * removed the broker features search from this process to the broker features search process...
 * 
 *    Rev 1.20   Jun 30 2003 16:56:28   popescu
 * added historical info search to the Broker Features search;
 * moved some param names to the mfcaniterprocparam namespace
 * 
 *    Rev 1.19   Jun 27 2003 18:13:08   popescu
 * Pay To Entity feature, dialog, process and CBO
 * 
 *    Rev 1.18   Jun 09 2003 17:39:54   popescu
 * Added support for fund and class search, still stopped at the Gui level, because it shouldn't be functional yet; do not know the id for the bank entity when seraching for bank using fund and class
 * 
 *    Rev 1.17   May 31 2003 11:54:38   popescu
 * RRIF bank work
 * 
 *    Rev 1.16   May 23 2003 10:04:08   popescu
 * Part of bank instructions cleaning up process, moved the bank types into the ifastids project
 * 
 *    Rev 1.15   May 22 2003 14:11:42   popescu
 * Replaced name 'BankInstr' with 'BankInstructions'; 
 * simplified child lists getters for the Shareholder object
 * 
 *    Rev 1.14   Mar 21 2003 17:47:46   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.13   Dec 27 2002 11:17:34   linmay
 * modified doProcess method for AMSType support
 * 
 *    Rev 1.12   Nov 25 2002 10:03:56   YINGBAOL
 * add logic for launching AMS Global screen
 * 
 *    Rev 1.11   Oct 09 2002 23:53:36   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.10   Aug 29 2002 16:45:14   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.9   24 May 2002 15:41:08   KOVACSRO
 * Fund and Client bank.
 * 
 *    Rev 1.8   22 May 2002 18:25:02   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.7   27 Mar 2002 19:55:40   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.6   09 Mar 2001 18:20:58   BUZILAMI
 * search for Bankinstructions
 * 
 *    Rev 1.5   07 Mar 2001 15:41:58   BUZILAMI
 * Broker, Branch, SlsRep Bank Instructions changes
 * 
 *    Rev 1.4   Feb 22 2001 15:24:36   BUZILAMI
 * added search for bank using Broker, Branch and sales Rep
 * 
 *    Rev 1.3   15 Dec 2000 12:43:48   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.2   Aug 16 2000 15:00:56   YINGBAOL
 * implement fundction "search for Trade"
 * 
 *    Rev 1.1   Jun 03 2000 15:33:56   BUZILA
 * Certificate fix: search for certificate using an inexistent account
 * 
 *    Rev 1.0   Feb 15 2000 10:59:38   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.22   Dec 15 1999 10:44:10   VASILEAD
 * Implemented background search for Entity screen
 * 
 *    Rev 1.21   Dec 02 1999 17:56:48   POPESCUS
 * Fixed crashes in search
 * 
 *    Rev 1.20   Nov 28 1999 14:10:28   PRAGERYA
 * A parameter for Allocations search added
 * 
 *    Rev 1.19   Nov 24 1999 18:57:34   BUZILA
 * fix COA must be launched modal
 * 
 *    Rev 1.18   Nov 23 1999 18:05:40   POPESCUS
 * NASU flow
 * 
 *    Rev 1.17   Nov 12 1999 12:00:50   PRAGERYA
 * Namespace for Allocations changed
 * 
 *    Rev 1.16   Nov 12 1999 09:37:02   POPESCUS
 * Fixed compiling error related to the allocation process
 * 
 *    Rev 1.15   Nov 11 1999 16:54:20   PRAGERYA
 * namespace for allocations changed
 * 
 *    Rev 1.14   Nov 08 1999 13:43:14   PRAGERYA
 * SetParameter for AccInfo process added
 * 
 *    Rev 1.13   Oct 29 1999 12:20:20   DT24433
 * removed doOk/doCancel
 * 
 *    Rev 1.12   Oct 18 1999 15:16:12   POPESCUS
 * 
 *    Rev 1.11   Oct 18 1999 09:47:34   POPESCUS
 * 
 *    Rev 1.10   24 Sep 1999 16:24:18   HUANGSHA
 * Added search for Address Book
 * 
 *    Rev 1.9   Aug 26 1999 16:08:42   PRAGERYA
 * Implementing Search for Shareholder and Account Info
 * 
 *    Rev 1.8   Aug 20 1999 08:51:02   DT24433
 * removed static FieldDetails array
 * 
 *    Rev 1.7   Jul 28 1999 13:16:04   POPESCUS
 * Added a new process for entity search
 * 
 *    Rev 1.6   Jul 23 1999 10:22:30   POPESCUS
 * Added a new Process that will fill in the dstc front end combos
 * 
 *    Rev 1.5   Jul 20 1999 13:37:36   POPESCUS
 * Add param Nt to igNre data Nt found
 * 
 *    Rev 1.4   Jul 20 1999 11:14:12   VASILEAD
 * New conditions update
 * 
 *    Rev 1.3   Jul 16 1999 11:50:40   POPESCUS
 * The SearchProcess should return CMD_OK to be removed from the container if the children return CMD_MODELESS
 * 
 *    Rev 1.2   Jul 14 1999 17:07:40   POPESCUS
 * Added a new param to the certificate process
 * 
 *    Rev 1.1   Jul 08 1999 10:02:10   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
