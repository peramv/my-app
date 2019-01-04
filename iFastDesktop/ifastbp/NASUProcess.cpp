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
// ^FILE   : NASUProcess.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : 23/06/99
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : NASUProcess
//    This class does NASU
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "accdetailsprocessincludes.h"
#include "accinfoprocessincludes.h"
#include "acctcategoryprocessincludes.h"
#include "acctsplitcommprocessincludes.h"
#include "aspensionplanprocessincludes.h"
#include "coaprocessincludes.h"
#include "contractinfoprocessincludes.h"
#include <ifastcbo\dstcommonfunction.hpp>
#include "entityprocessincludes.h"
#include "esopinfoprocessincludes.h"
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\mgmtco.hpp>
#include "nasuprocess.hpp"
#include "nasuprocessincludes.h"
#include "pensioninfoprocessincludes.h"
#include <ifastcbo\serverdata.hpp>
#include "shareholderprocessincludes.h"
#include "DemographicsProcessincludes.h"
#include <ifastcbo\taxtyperulelist.hpp>
#include <ifastcbo\mgmtcooptions.hpp>
#include <ifastcbo\grouplist.hpp>
#include <ifastcbo\group.hpp>
#include <ifastcbo\shareholder.hpp>
#include "FundSponsorFeeModelProcessinclude.h"
#include "mfcaninterprocparam.hpp"

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_SHAREHOLDER;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ACCINFO;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ENTITY;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ESOPINFO;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ADDRESSES;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_AS_PENSION_PLAN;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_CONTRACTINFO;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ACCT_SPLITCOMM;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_COA;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_PENSION_INFO;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ACCT_CATEGORY;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_NASU;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_DEMOGRAPHICS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_AMSACCTLVL;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FUNDSPONSOR_FEE_MODEL;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_BANK_INSTRUCTIONS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_DISTRIBUTION;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_REG_DOCUMENT_LIST;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_RESP_ACCT_INFO_NASU;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ACCT_GUARNT_GUARD_OPTN;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ACCOUNT_COMMITMENT;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ACCT_REGIS_MAINT;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ENT_REG_MAINT;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ACCT_ROUNDING_RULE;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< NASUProcess > processCreator (CMD_BPROC_NASU);

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME               = I_ ("NASUProcess");
   const I_CHAR * const PERFORMSEARCH           = I_ ("performSearch");
   const I_CHAR * const ACCOUNT_SPLIT_COMM_CODE = I_ ("2");
   const I_CHAR * YES                           = I_ ("Y");
   const I_CHAR * NO                            = I_ ("N");
   const I_CHAR * const ESOP_INVESTMENT         = I_ ("D");
   const I_CHAR * const ESOP_PARTICIPATION      = I_ ("E");
   const I_CHAR * const LRSP                    = I_ ("U");
   const I_CHAR * const LRIF                    = I_ ("L");  
   const I_CHAR * const PRIF                    = I_ ("R");  
   const I_CHAR * const REG_STANDARD            = I_ ("RegulatoryStandard");
   const I_CHAR * const INDIV_RESP_PLAM         = I_ ("9");
   const I_CHAR * const FAMILY_RESP_PLAM        = I_ ("M");
}

const I_CHAR * NASU_BUFFER = I_ ("NASU_BUFFER");

namespace NASULIT //nasu literals
{
   extern CLASS_EXPORT const I_CHAR * const CREATING_ACCOUNT         = I_ ("CreatingAccount");
   extern CLASS_EXPORT const I_CHAR * const CREATING_SHAREHOLDER     = I_ ("CreatingShareholder");
   extern CLASS_EXPORT const I_CHAR * const TRXNS_ERROR              = I_ ("TrxnsError");
   extern CLASS_EXPORT const I_CHAR * const PARM_CALLED_FROM         = I_ ("CalledFrom");
   // Used to store the last command returned from the dialog eg. OK/CANCEL
   extern CLASS_EXPORT const I_CHAR * const COMMANDRETURN            = I_ ("CommandReturn");
   extern CLASS_EXPORT const I_CHAR * const COMMANDCANCEL            = I_ ("CANCEL");
   extern CLASS_EXPORT const I_CHAR * const COMMANDOK                = I_ ("OK");
   extern CLASS_EXPORT const I_CHAR * const CanCelAfterAccountInfo   = I_ ("CanCelAfterAccountInfo");  
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const ACCT_CATEGORY;
   extern CLASS_IMPORT I_CHAR * const ACCOUNT_FEE_MODEL;
   extern CLASS_IMPORT I_CHAR * const BANKING_INSTRUCTION;
   extern CLASS_IMPORT I_CHAR * const DISTRIBUTION;
   extern CLASS_IMPORT I_CHAR * const DEMOGRAPHICS;
   extern CLASS_IMPORT I_CHAR * const DOC_LIST;
   extern CLASS_IMPORT I_CHAR * const ENTITY_REGULATORY_MAINT;
   extern CLASS_IMPORT I_CHAR * const ACCT_CATEGORY_PRIVATE_WEALTH_OPT_OUT;
   extern CLASS_IMPORT I_CHAR * const ACCT_ROUNDING_RULE;
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern CLASS_IMPORT const long WARN_SIBLING_ONLY_BLANK_OR_NO;   
}

namespace ifds
{
    extern CLASS_IMPORT const BFTextFieldId UpdAMSOnNewAcct;
    extern CLASS_IMPORT const BFTextFieldId NASUPopupOptions;
    extern CLASS_IMPORT const BFTextFieldId AcctCategory;

}

const I_CHAR* _shareholderParams[] = 
{
   NASULIT::CREATING_SHAREHOLDER,
   SHRPROC::SHAREHOLDER_NUM,
   SHRPROC::GROUP_CODE,
   '\0',
};

const I_CHAR* _accInfoParams[] = 
{
   NASULIT::CREATING_ACCOUNT,
   NASULIT::CREATING_SHAREHOLDER,
   SHRPROC::SHAREHOLDER_NUM,
   SHRPROC::GROUP_CODE,
   ACCINFOPROC::ACCOUNT_NUM,
   ACCINFOPROC::MODEL_ACCOUNT_NUM,
   '\0',
};

const I_CHAR* _respAccInfoParams[] = 
{
   NASULIT::CREATING_ACCOUNT,
   NASULIT::CREATING_SHAREHOLDER,
   SHRPROC::SHAREHOLDER_NUM,
   ACCINFOPROC::ACCOUNT_NUM,
   '\0',
};

const I_CHAR* _entityParams[] =
{
   NASULIT::CREATING_SHAREHOLDER,
   NASULIT::CREATING_ACCOUNT,
   NASULIT::COMMANDRETURN,
   ENTPROC::ACCOUNT_NUM,
   ENTPROC::MODEL_ACCOUNT_NUM,
   '\0',
};

const I_CHAR* _addressesParams[] =
{
   NASULIT::CREATING_ACCOUNT,
   SHRPROC::SHAREHOLDER_NUM,
   ACCINFOPROC::ACCOUNT_NUM,
   '\0',
};

const I_CHAR* _coaParams[] = 
{
   NASULIT::CREATING_ACCOUNT,
   COALIT::ACCOUNT_NUM,
   '\0',
};

const I_CHAR* _confParams[] = 
{
   NASULIT::CREATING_SHAREHOLDER,
   NASULIT::TRXNS_ERROR, 
   I_ ("DataGroupID"),
   NASULIT::PARM_CALLED_FROM,
   NASULIT::CREATING_ACCOUNT,
   '\0'
};

const I_CHAR* _contractParams[] = 
{
   CONTRACT::TRANSID_EMPTY,
   //CONTRACT::SHAREHOLD_NUMBER,
   CONTRACT::ACCOUNT_NUMBER,
   NASULIT::CREATING_SHAREHOLDER,
   NASULIT::CREATING_ACCOUNT,
   '\0'
};

const I_CHAR* _pensionParams[] = 
{
   ASPENSIONPLANLIT::ACCOUNT_NUM,
   '\0'
};

const I_CHAR* _esopParams[] = 
{
   ESOP::ACCOUNT_NUMBER,
   '\0'
};

const I_CHAR* _acctSplitComm[] =
{
   NASULIT::CREATING_SHAREHOLDER,
   NASULIT::CREATING_ACCOUNT,
   ACCTSPLIT::ACCOUNT_NUM,
   '\0'
};

const I_CHAR* _acctPensionInfo[] =
{   
   NASULIT::CREATING_SHAREHOLDER,
   NASULIT::CREATING_ACCOUNT,
   PENSION_INFO::ACCOUNT_NUM,
   '\0'
};

const I_CHAR* _categoryParams[] = 
{
   ACCTCATEGORYLIST::ACCOUNT_NUM,
   '\0'
};

const I_CHAR* _demographicsParams[]=
{
   ACCTCATEGORYLIST::ACCOUNT_NUM,
   REG_STANDARD,
   '\0'
};

const I_CHAR* _regDocListParams[]=
{
   ACCTCATEGORYLIST::ACCOUNT_NUM,
   REG_STANDARD,
   '\0'
};

const I_CHAR* _accountAMSParams[] = 
{
   ACCINFOPROC::ACCOUNT_NUM,
   '\0'
};


const I_CHAR* _accountFeeModelParams[] =
{
   FUNDSPONSORFEEMODEL::FROM_SCR,
   FUNDSPONSORFEEMODEL::ACCOUNTNUM,
   '\0'
};

const I_CHAR* _accountBankParams[] = 
{
   ACCINFOPROC::ACCOUNT_NUM,
   MFCAN_IP_PARAM::BANK_TYPE,
   '\0'
};

const I_CHAR* _accountDistributionParams[] = 
{
   ACCINFOPROC::ACCOUNT_NUM,
   '\0'
};

const I_CHAR* _accountGuaranteeGuardParams[] = 
{
   NASULIT::CREATING_ACCOUNT,
   SHRPROC::SHAREHOLDER_NUM,
   ACCINFOPROC::ACCOUNT_NUM,
   '\0'
};

const I_CHAR* _accountRegulatoryDetailsParams[] = 
{
   NASULIT::CREATING_ACCOUNT,
   ACCINFOPROC::ACCOUNT_NUM,
   '\0'
};

const I_CHAR* _entityRegulatoryDetailsParams[] = 
{
   NASULIT::CREATING_ACCOUNT,
   ACCINFOPROC::ACCOUNT_NUM,
   '\0'
};

const I_CHAR* _accountCommitmentParams[] = 
{
   NASULIT::CREATING_ACCOUNT,
   SHRPROC::SHAREHOLDER_NUM,
   ACCINFOPROC::ACCOUNT_NUM,
   '\0'
};

const I_CHAR* _acctRoundingRuleParams[] = 
{  
   NASULIT::CREATING_SHAREHOLDER,
   NASULIT::CREATING_ACCOUNT,
   MFCAN_IP_PARAM::ACCOUNT_NUM,
   '\0'
};

struct _nasu
{
   const I_CHAR* _command;
   const I_CHAR** _params;
   bool _bCheckMgtmCoOption;
   const I_CHAR* _commandCode;
};

namespace BANKENTITY
{
   I_CHAR * const SHAREHOLDER = I_("10");
   I_CHAR * const  ACCOUNT  = I_("14");
}
namespace BANKTYPE
{
   I_CHAR * const SHAREHOLDER = I_("10");
   I_CHAR * const ACCOUNT = I_("14");
}

//data structures for the new shareholder flow
const struct _nasu _newShareholderNASU[] = 
{
   CMD_BPROC_SHAREHOLDER, _shareholderParams, false, NULL, 
   CMD_BPROC_ACCINFO, _accInfoParams, false, NULL, 
   CMD_BPROC_RESP_ACCT_INFO_NASU,_respAccInfoParams, true, I_("RESPINFO"),
   CMD_BPROC_PENSION_INFO, _acctPensionInfo, false, NULL, 
   CMD_BPROC_ENTITY, _entityParams, false, NULL, 
   CMD_BPROC_ESOPINFO, _esopParams, false, NULL, 
   CMD_BPROC_ADDRESSES, _addressesParams, false, NULL, 
   CMD_BPROC_AS_PENSION_PLAN, _pensionParams, false, NULL, 
   CMD_BPROC_CONTRACTINFO, _contractParams, false, I_("CONTRACTINFO"), 
   CMD_BPROC_ACCOUNT_COMMITMENT, _accountCommitmentParams, false, NULL, 
   CMD_BPROC_ACCT_SPLITCOMM, _acctSplitComm, false, NULL, 
   CMD_BPROC_ACCT_CATEGORY, _categoryParams, true, I_("ACCTCATEGORY"), 
   CMD_BPROC_DEMOGRAPHICS, _demographicsParams, true, I_("KYC"), 
   CMD_BPROC_REG_DOCUMENT_LIST, _regDocListParams, true, I_("DOCLIST"), 
   CMD_BPROC_AMSACCTLVL,_accountAMSParams, false, NULL, 
   CMD_BPROC_FUNDSPONSOR_FEE_MODEL,_accountFeeModelParams, true, I_("FEEMODEL"), 
   CMD_BPROC_BANK_INSTRUCTIONS, _accountBankParams, true, I_("BANK"),
   CMD_BPROC_DISTRIBUTION, _accountDistributionParams, true, I_("DISTRIBUTION"),
   CMD_BPROC_ACCT_GUARNT_GUARD_OPTN, _accountGuaranteeGuardParams, true, I_("ACCTGUARGUARD"),
   CMD_BPROC_ACCT_REGIS_MAINT, _accountRegulatoryDetailsParams, true, I_("ACCTREG"),
   CMD_BPROC_ENT_REG_MAINT, _entityRegulatoryDetailsParams, true, I_("ENTREGDETL"),
   CMD_BPROC_ACCT_ROUNDING_RULE, _acctRoundingRuleParams, true, I_("ACCTROUNDINGRULE"),

   CMD_BPROC_COA, _coaParams, false, NULL, 
   CMD_BPROC_CONFIRMATION, _confParams, false, NULL, 
   '\0', '\0'
};

//data structures for the new account flow
const struct _nasu _newAccountNASU[] = 
{
   CMD_BPROC_ACCINFO, _accInfoParams, false, NULL, 
   CMD_BPROC_RESP_ACCT_INFO_NASU, _respAccInfoParams, true, I_("RESPINFO"),
   CMD_BPROC_PENSION_INFO, _acctPensionInfo, false, NULL, 
   CMD_BPROC_ENTITY, _entityParams, false, NULL, 
   CMD_BPROC_ESOPINFO, _esopParams, false, NULL, 
   CMD_BPROC_AS_PENSION_PLAN, _pensionParams, false, NULL, 
   CMD_BPROC_CONTRACTINFO, _contractParams, false, I_("CONTRACTINFO"), 
   CMD_BPROC_ACCT_SPLITCOMM, _acctSplitComm, false, NULL, 
   CMD_BPROC_ACCT_CATEGORY, _categoryParams, true, I_("ACCTCATEGORY"), 
   CMD_BPROC_DEMOGRAPHICS, _demographicsParams, true, I_ ("KYC"), 
   CMD_BPROC_REG_DOCUMENT_LIST, _regDocListParams, true, I_("DOCLIST"), 
   CMD_BPROC_AMSACCTLVL,_accountAMSParams, false, NULL,
   CMD_BPROC_FUNDSPONSOR_FEE_MODEL,_accountFeeModelParams, true, I_("FEEMODEL"), 
   CMD_BPROC_BANK_INSTRUCTIONS, _accountBankParams, true, I_("BANK"),
   CMD_BPROC_DISTRIBUTION, _accountDistributionParams, true, I_("DISTRIBUTION"),
   CMD_BPROC_ACCT_GUARNT_GUARD_OPTN, _accountGuaranteeGuardParams, true, I_("ACCTGUARGUARD"),
   CMD_BPROC_ACCT_REGIS_MAINT, _accountRegulatoryDetailsParams, true, I_("ACCTREG"),
   CMD_BPROC_ENT_REG_MAINT, _entityRegulatoryDetailsParams, true, I_("ENTREGDETL"),
   CMD_BPROC_ACCT_ROUNDING_RULE, _acctRoundingRuleParams, true, I_("ACCTROUNDINGRULE"),

   CMD_BPROC_COA, _coaParams, false, NULL, 
   CMD_BPROC_CONFIRMATION, _confParams, false, NULL, 
   '\0', '\0'
};

//******************************************************************************
//CP20030319NASUProcess::NASUProcess ()
NASUProcess::NASUProcess (GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand)
: AbstractProcess (pGIC, pGIParent, rCommand),
flowPopupOptions (NULL_STRING)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);

   _pServerData = NULL;
}

//******************************************************************************
NASUProcess::~NASUProcess ()
{
   TRACE_DESTRUCTOR (CLASSNAME);

   if (_pServerData)
      delete _pServerData;
}

//******************************************************************************
SEVERITY NASUProcess::doInit ()
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, DOINIT);
   SEVERITY sevRtn = SEVERE_ERROR;
   DSTCWorkSession *pDSTCWorkSession = 
      dynamic_cast<DSTCWorkSession *> (getBFWorkSession ());
   const BFDataGroupId& idDataGroup = getDataGroupId ();

//   setMyGroupID (idDataGroup); //setting a idDataGroup for the process
   try
   {
      DString creatingShareholder, creatingAccount, calledFrom;

      getParameter (NASULIT::CREATING_SHAREHOLDER, creatingShareholder);
      getParameter (NASULIT::CREATING_ACCOUNT, creatingAccount);
      getParameter (NASULIT::PARM_CALLED_FROM, calledFrom);

      _nasuParams.setParameter (NASULIT::CREATING_SHAREHOLDER, creatingShareholder);
      _nasuParams.setParameter (NASULIT::CREATING_ACCOUNT, creatingAccount);
      _nasuParams.setParameter (NASULIT::TRXNS_ERROR, NO);
      _nasuParams.setParameter (NASULIT::PARM_CALLED_FROM, calledFrom);
      _nasuParams.setParameter (CONTRACT::TRANSID_EMPTY, YES);
      _nasuParams.setParameter (ACCINFOPROC::ACCOUNT_NUM, NULL_STRING);
      _nasuParams.setParameter (FUNDSPONSORFEEMODEL::FROM_SCR, I_("Account"));
      // set the banking type during nasu based on the environment
      // _nasuParams.setParameter (MFCAN_IP_PARAM::BANK_TYPE, I_("Shareholder"));
      DString dstrDefaultBankingLevel;
      pDSTCWorkSession->getOption (ifds::DefaultBankingLevel, dstrDefaultBankingLevel, getParent()->getDataGroupId(), false);
      if(BANKENTITY::ACCOUNT == dstrDefaultBankingLevel)
         _nasuParams.setParameter (MFCAN_IP_PARAM::BANK_TYPE, I_("Account"));
      else
         _nasuParams.setParameter (MFCAN_IP_PARAM::BANK_TYPE, I_("Shareholder"));
      if (creatingShareholder == NO && creatingAccount == YES)
      {
         DString strShrNum, modelAccountNum,  entityId;

         getParameter (ACCINFOPROC::SHAREHOLDER_NUM, strShrNum);
         getParameter (ACCINFOPROC::MODEL_ACCOUNT_NUM, modelAccountNum);
         _nasuParams.setParameter (SHRPROC::SHAREHOLDER_NUM, strShrNum);
         _nasuParams.setParameter (ACCINFOPROC::MODEL_ACCOUNT_NUM, modelAccountNum);
      }

      DString temp;
      getParameter (NASU_BUFFER, temp);

      if (temp != NULL_STRING)
      {
         _pServerData = new ServerData (*getBFWorkSession ());
         sevRtn = _pServerData->init (temp);
         if (WARNING >= sevRtn)
         {
            //setContainer (SERVER_DATA_CBO, _pServerData);
         }
      }

      //read management company options, popup option
      pDSTCWorkSession->getMgmtCoOptions ()->getField ( ifds::NASUPopupOptions,
                                                        flowPopupOptions, 
                                                        BF::HOST, 
                                                        false);
      flowPopupOptions.strip ().upperCase ();
   }
   catch (ConditionException &ce)
   {
      SETCONDITIONFROMEXCEPTION (ce);
   }
   catch (...)
   {
      assert (0);
      THROWFROMFILE2 (CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return NO_CONDITION;
}

//******************************************************************************
ServerData* NASUProcess::getServerData (void)
{  
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS);

   return (_pServerData);
}

//******************************************************************************
E_COMMANDRETURN NASUProcess::doProcess ()
{  
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS);
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      DString creatingShareholder, creatingAccount;

      creatingShareholder = _nasuParams.getParameter (DString (NASULIT::CREATING_SHAREHOLDER));
      creatingAccount = _nasuParams.getParameter (DString (NASULIT::CREATING_ACCOUNT));
      if (creatingShareholder == YES && creatingAccount == YES) //NASU flow for new shareholder and accounts
      {
         rtn = doFlow (_newShareholderNASU);
      }
      else if (creatingAccount == YES && creatingShareholder == NO) //NASU flow for new accounts
      {
         rtn = doFlow (_newAccountNASU);
      }
      else
      {
         rtn = CMD_OK;//simply return and die
      }
   }
   catch (ConditionException &ce)
   {
      assert (0);
      SETCONDITIONFROMEXCEPTION (ce);
   }
   catch (...)
   {
      assert (0);
      THROWFROMFILE2 (CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS,
                      CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return (rtn);
}

//******************************************************************************
E_COMMANDRETURN NASUProcess::doFlow (const struct _nasu flow[])
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTBP_CONDITION, CLASSNAME, DOPROCESS);

   E_COMMANDRETURN rtn= CMD_FAILURE;
   DString strMarket = DSTCommonFunctions::getMarket ();
   const I_CHAR* command = NULL;
   int cmdndx = 0;

   while (cmdndx >= 0 && ( (command = flow[ cmdndx ]._command) != '\0'))
   {
      //should we pop-up the next dialog, check the system options
      if (!flow[ cmdndx ]._bCheckMgtmCoOption ||
         flowPopupOptions.find (flow[ cmdndx ]._commandCode) != DString::npos)
      {
         setFlowParams (flow[ cmdndx ]._params);
         if (command == CMD_BPROC_CONTRACTINFO)
         {
            if (isSegFund () && strMarket == MARKET_IDS::CANADA)
            {  //invoke ContractInfo only if it is a seg fund
               rtn = invokeCommand (this, command, getProcessType (), true /*modal*/, NULL);
            }
         }
         else if (command == CMD_BPROC_ACCOUNT_COMMITMENT)
         {
            if (isCommitmentApplicable ())
            {
               rtn = invokeCommand (this, command, getProcessType (), true /*modal*/, NULL);
            }
         }
         else if (command == CMD_BPROC_COA)
         {
            if (_pServerData == NULL)//skip COA process if called from BPServer
            {
               rtn = invokeCommand (this, command, getProcessType (), true /*modal*/, NULL);
            }
         }
         else if (command == CMD_BPROC_AS_PENSION_PLAN)
         {
            if (strMarket == MARKET_IDS::LUXEMBOURG && isAsPensionPlanType ())
            {
               rtn = invokeCommand (this, command, getProcessType (), true /*modal*/, NULL);
            }
         }
         else if (command == CMD_BPROC_ACCT_SPLITCOMM)
         {
            if (strMarket == MARKET_IDS::CANADA && hasAccountSplitComm ())
            {
               rtn = invokeCommand (this, command, getProcessType (), true /*modal*/, NULL);
            }
         }
         else if (command == CMD_BPROC_ESOPINFO)
         {
            if (strMarket == MARKET_IDS::LUXEMBOURG && isESoPPlanType ())
            {
               rtn = invokeCommand (this, command, getProcessType (), true /*modal*/, NULL);
            }
         }
         else if (command == CMD_BPROC_PENSION_INFO)
         {
            if (strMarket == MARKET_IDS::CANADA && hasPensionInfo ())
            {
               rtn = invokeCommand (this, command, getProcessType (), true /*modal*/, NULL);
            }
         }
         else if (command == CMD_BPROC_ACCT_CATEGORY)
         {
             if (hasCreatePermission (UAF::ACCT_CATEGORY) || hasCreatePermission (UAF::ACCT_CATEGORY_PRIVATE_WEALTH_OPT_OUT))
            {
               rtn = invokeCommand (this, command, getProcessType (), true /*modal*/, NULL);
            }
         }
         else if (command == CMD_BPROC_FUNDSPONSOR_FEE_MODEL)
         {
            if (hasCreatePermission (UAF::ACCOUNT_FEE_MODEL))
            {
               rtn = invokeCommand (this, command, getProcessType (), true /*modal*/, NULL);
            }
         }
         else if (command == CMD_BPROC_AMSACCTLVL) 
         {
            if (isAcctAMSPartOfNASU ())
            {
               rtn = invokeCommand (this, command, getProcessType (), true /*modal*/, NULL);		
            }
         }
         else if ( command == CMD_BPROC_BANK_INSTRUCTIONS)
         {
            if (hasCreatePermission (UAF::BANKING_INSTRUCTION))
            {
               rtn = invokeCommand (this, command, getProcessType (), true /*modal*/, NULL);
            }
         }
         else if (command == CMD_BPROC_DISTRIBUTION)
         {
            if (hasCreatePermission (UAF::DISTRIBUTION))
            {
               rtn = invokeCommand (this, command, getProcessType (), true /*modal*/, NULL);		
            }
         }
         else if (command == CMD_BPROC_RESP_ACCT_INFO_NASU)
         {
            if (strMarket == MARKET_IDS::CANADA && isNewRESPTaxType ())
            {
               rtn = invokeCommand (this, command, getProcessType (), true /*modal*/, NULL);
            }
         }
         else if (command == CMD_BPROC_ACCT_GUARNT_GUARD_OPTN)
         {
			if(strMarket == MARKET_IDS::CANADA && isGuarGuardAllowed())
            {
				rtn = invokeCommand (this, command, getProcessType (), true /*modal*/, NULL);
            }
         }
         else if (command == CMD_BPROC_ENT_REG_MAINT)
         {
			if(hasCreatePermission (UAF::ENTITY_REGULATORY_MAINT))
            {
				setParameter (I_("Caller"), I_("NASU"));
				rtn = invokeCommand (this, command, getProcessType (), true /*modal*/, NULL);
            }
         }
		 else if (command == CMD_BPROC_ACCT_ROUNDING_RULE)
		 {
			 if(hasCreatePermission (UAF::ACCT_ROUNDING_RULE))
			 {
				 setParameter (I_("Caller"), I_("NASU"));
				 rtn = invokeCommand (this, command, getProcessType (), true /*modal*/, NULL);
			 }
		 }
         else
         {
            DString strNewShareholder, strNewAccount;

            strNewShareholder = _nasuParams.getParameter (NASULIT::CREATING_SHAREHOLDER);
            strNewAccount = _nasuParams.getParameter (NASULIT::CREATING_ACCOUNT);

            setParameter (NASULIT::CREATING_SHAREHOLDER, strNewShareholder);
            setParameter (NASULIT::CREATING_ACCOUNT, strNewAccount);

            //set as parent this process
            rtn = invokeCommand (this, command, getProcessType (), true /*modal*/, NULL);
         }
         //get the params in the next process' params area
         //basically save the params
         getFlowParams (flow[ cmdndx ]._params);
      }
      if (rtn == CMD_CANCEL) //return to the previous process, if not errors
      {
         // set the COMMANDRETURN parameter so that we know what the last command was 
         // in NASU.
         _nasuParams.setParameter (NASULIT::COMMANDRETURN, NASULIT::COMMANDCANCEL);
         if (flow[ cmdndx - 1 ]._command == CMD_BPROC_ACCINFO)
         {
            setParameter (NASULIT::CanCelAfterAccountInfo,I_ ("Y"));
         }


         if (flow[ cmdndx ]._command == CMD_BPROC_CONFIRMATION)
         {
            DString trxnsError;

            trxnsError = _nasuParams.getParameter (NASULIT::TRXNS_ERROR);
            if (trxnsError == I_ ("Y"))
               break; //exit the flow, if errors after confirmation
         }
         --cmdndx;
      }
      else if (rtn == CMD_OK || (rtn == CMD_MODELESS_INPROCESS && !isEndOfNASU (flow, cmdndx)))
      {
         _nasuParams.setParameter (NASULIT::COMMANDRETURN, NASULIT::COMMANDOK);
         //move to the next one
         ++cmdndx;
      }
      else
      {
         break; //exit the flow
      }
   }
   return rtn;
}

//******************************************************************************
//this method will get the params from the nasu process and set them to the
//work session process which is the parent of the nasu process
void NASUProcess::setFlowParams (const I_CHAR* params[])
{
   const I_CHAR* param = NULL;

   for (int paramsndx = 0; (param = params[ paramsndx ]) != '\0'; ++paramsndx)
   {
      DString value = _nasuParams.getParameter (DString (param));

      if (value != NULL_STRING) //do not clear the params
      {
         setParameter (param, value);
      }
   }
}

//******************************************************************************
//this method will get the params from the parent of the nasu process which is the
//work session process and set them to the nasu process
void NASUProcess::getFlowParams (const I_CHAR* params[])
{
   const I_CHAR* param = NULL;

   for (int paramsndx = 0; (param = params[ paramsndx ]) != '\0'; ++paramsndx)
   {
      DString value;

      //try and get the params from the work session process
      getParameter (param, value);
      if (value != NULL_STRING) //do not clear the params
      {
         _nasuParams.setParameter (param, value);
      }
   }
}

//******************************************************************************
bool NASUProcess::isEndOfNASU (const struct _nasu flow[], int nasundx)
{
   const I_CHAR* command = NULL;

   int i = 0;
   for (i = 0; (command = flow[ i ]._command) != '\0'; i++)
      ;
   return (i <= nasundx);
}

//******************************************************************************
bool NASUProcess::isSegFund ()
{
   TRACE_METHOD (CLASSNAME, I_ ("isSegFund"));
   DString strSegClient, 
      strCotClient,
      dstrPorfolioIsRequried;

   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *> (getBFWorkSession ());
   bool bIsSegFund = false;

   dstcWorkSession->getOption (ifds::SegClient, strSegClient, BF::HOST);
   dstcWorkSession->getOption (ifds::CotClient, strCotClient, BF::HOST);
   dstcWorkSession->getOption (ifds::PorfolioIsRequried, dstrPorfolioIsRequried, BF::HOST, false);
   bIsSegFund = strSegClient == YES && strCotClient == YES;

   if (bIsSegFund && dstrPorfolioIsRequried == YES)
   {
      DString dstrAccountNum;

      getParameter (ACCINFOPROC::ACCOUNT_NUM, dstrAccountNum);

      MFAccount* pMFAccount (NULL);
      const BFDataGroupId& idDataGroup = getDataGroupId ();

      if (dstcWorkSession->getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING &&
          pMFAccount)
      {
         bIsSegFund = pMFAccount->hasSegFundsWithinPortfolio (idDataGroup);
      }
   }  
   return bIsSegFund;
}

//******************************************************************************
bool NASUProcess::isCommitmentApplicable ()
{
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *> (getBFWorkSession ());
   bool bIsCommitmentApplicable = false;
   DString dstrAccountNum;

   getParameter (ACCINFOPROC::ACCOUNT_NUM, dstrAccountNum);

   MFAccount* pMFAccount (NULL);
   const BFDataGroupId& idDataGroup = getDataGroupId ();

   if (dstcWorkSession->getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING &&
       pMFAccount)
   {
      bIsCommitmentApplicable = pMFAccount->isCommitmentApplicable (idDataGroup);
   }
   return bIsCommitmentApplicable;
}

//******************************************************************************
bool NASUProcess::isGuarGuardAllowed ()
{
   TRACE_METHOD (CLASSNAME, I_ ("isGuarGuardAllowed"));
   
   bool bIsAllowed = false;

   if (isSegFund ())
   {
      // checking Guarantee Guard control on, view149
      DString dstrGuaranteeGuardOn;
      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *> (getBFWorkSession ());
      dstcWorkSession->getOption (ifds::GuaranteeGuardOn, dstrGuaranteeGuardOn, BF::HOST, false);
      dstrGuaranteeGuardOn.strip().upperCase();

      if(dstrGuaranteeGuardOn == YES)
      {
         // get Current shareholder object
         Shareholder *pShareholder;
         DString dstrGroupCode, dstrShrNum;

         dstrShrNum = _nasuParams.getParameter (DString (SHRPROC::SHAREHOLDER_NUM));
         dstcWorkSession->getShareholder ( getDataGroupId(), dstrShrNum, pShareholder, false );
         pShareholder->getField( ifds::GroupCode, dstrGroupCode, getDataGroupId(), false);
         dstrGroupCode.strip().upperCase();

         // check with HasGWOContract from view 88
         GroupList* pGroupList;
         if( dstcWorkSession->getMgmtCo().getGroupList( pGroupList ) <= WARNING )
         {			   
            BFObjIter glIter( *pGroupList, getDataGroupId() );
            if( glIter.positionByKey( dstrGroupCode ) )
            {
               Group* pGroup;
               if( pGroup = dynamic_cast<Group*>( glIter.getObject() ) )
               {
                  DString dstrHasGWOContract;
                  pGroup->getField(ifds::HasGWOContract, dstrHasGWOContract, getDataGroupId(), false);
                  dstrHasGWOContract.strip().upperCase();

                  if(dstrHasGWOContract == YES) 
                     bIsAllowed = true;
               }
            }
         }
      }
   }

   return bIsAllowed;
}

//******************************************************************************
bool NASUProcess::isAsPensionPlanType ()
{
   TRACE_METHOD (CLASSNAME, I_ ("isAsPensionPlanType"));

   DString dstrAccountNum;

   getParameter (ACCINFOPROC::ACCOUNT_NUM, dstrAccountNum);

   MFAccount* pMFAccount;
   TaxTypeRuleList *pTaxTypeRuleList;
   DString dstrAcctTaxType, dstrTaxType, dstrAcctType;

   const BFDataGroupId& idDataGroup = getDataGroupId ();

   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *> (getBFWorkSession ());

   if (dstcWorkSession->getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING)
   {
      pMFAccount->getField (ifds::TaxType, dstrAcctTaxType, idDataGroup, false);

      if (dstrAcctTaxType == I_ ("P"))
      {
         dstcWorkSession->getMgmtCo ().getTaxTypeRuleList (pTaxTypeRuleList);

         if (pTaxTypeRuleList)
         {
            BFObjIter iterTaxType (const_cast<TaxTypeRuleList &> (*pTaxTypeRuleList), idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED);

            for (iterTaxType.begin (); !iterTaxType.end (); ++iterTaxType)
            {
               iterTaxType.getObject ()->getField (ifds::TaxType, dstrTaxType, getDataGroupId (), false);

               if (dstrTaxType == dstrAcctTaxType)
                  break;
            }
         }
      }
   }
   return dstrTaxType == dstrAcctTaxType;
}

//******************************************************************************
bool NASUProcess::hasAccountSplitComm ()
{
   TRACE_METHOD (CLASSNAME, I_ ("hasAccountSplitComm"));
   DString dstrCommissionType;
   DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession*> (getBFWorkSession ());

   pDSTCWorkSession->getOption (ifds::CommissionType, dstrCommissionType, getDataGroupId (), false);
   return dstrCommissionType == ACCOUNT_SPLIT_COMM_CODE;
}

//******************************************************************************
bool NASUProcess::isESoPPlanType ()
{
   TRACE_METHOD (CLASSNAME, I_ ("isESoPPlanType"));

   DString dstrAccountNum, dstrAcctTaxType;
   bool bRetVal = false;

   getParameter (ACCINFOPROC::ACCOUNT_NUM, dstrAccountNum);

   MFAccount* pMFAccount;
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *> (getBFWorkSession ());

   if (!dstrAccountNum.strip ().empty () && 
      dstcWorkSession->getMFAccount (getDataGroupId (), dstrAccountNum, pMFAccount) <= WARNING)
   {
      pMFAccount->getField (ifds::TaxType, dstrAcctTaxType, getDataGroupId (), false);
      bRetVal = dstrAcctTaxType == ESOP_INVESTMENT || dstrAcctTaxType == ESOP_PARTICIPATION;
   }

   return (bRetVal); 

}

//******************************************************************************
bool NASUProcess::hasPensionInfo ()
{
   TRACE_METHOD (CLASSNAME, I_ ("hasPensionInfo"));
   DString dstrAccountNum, dstrAcctTaxType;
   bool bRetVal = false;

   getParameter (ACCINFOPROC::ACCOUNT_NUM, dstrAccountNum);

   MFAccount* pMFAccount;
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *> (getBFWorkSession ());

   if (!dstrAccountNum.strip ().empty () && dstcWorkSession->getMFAccount (getDataGroupId (), 
      dstrAccountNum, pMFAccount) <= WARNING)
   {
      pMFAccount->getField (ifds::TaxType, dstrAcctTaxType, getDataGroupId (), false);
      dstrAcctTaxType.strip ().upperCase ();
      bRetVal = dstcWorkSession->isLIFLike (dstrAcctTaxType) || 
         dstcWorkSession->isLIRALike (dstrAcctTaxType) ||
         dstrAcctTaxType == LRIF || 
         dstrAcctTaxType == PRIF;
   }
   return bRetVal; 
}

//*******************************************************************************
bool NASUProcess::isAcctAMSPartOfNASU ()
{
   DString dstrUpdAMSOnNewAcct;

   DSTCWorkSession *dstcWorkSession = 
      dynamic_cast<DSTCWorkSession *> (getBFWorkSession ());

   dstcWorkSession->getMgmtCoOptions ()->getField (ifds::UpdAMSOnNewAcct, dstrUpdAMSOnNewAcct,getDataGroupId (), false);
   dstrUpdAMSOnNewAcct.strip ().upperCase ();

   return dstrUpdAMSOnNewAcct == YES;
}

//*******************************************************************************
bool NASUProcess::isNewRESPTaxType ()
{
   TRACE_METHOD (CLASSNAME, I_ ("isNewRESPTaxType"));
   DString dstrAccountNum, dstrAcctTaxType;
   bool bRetVal = false;

   getParameter (ACCINFOPROC::ACCOUNT_NUM, dstrAccountNum);

   MFAccount* pMFAccount;
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *> (getBFWorkSession ());

   if (!dstrAccountNum.strip ().empty () && dstcWorkSession->getMFAccount (getDataGroupId (), 
        dstrAccountNum, pMFAccount) <= WARNING)
   {
      pMFAccount->getField (ifds::TaxType, dstrAcctTaxType, getDataGroupId (), false);
      dstrAcctTaxType.strip ().upperCase ();

      bRetVal = dstrAcctTaxType == INDIV_RESP_PLAM || 
                dstrAcctTaxType == FAMILY_RESP_PLAM;
   }

   return bRetVal;
}

//*******************************************************************************
NasuParams::NasuParams()
{
}

//*******************************************************************************
NasuParams::~NasuParams()
{
   _mapParms.erase (_mapParms.begin(), _mapParms.end());
}

//*******************************************************************************
void NasuParams::setParameter (const DString &name, const DString &value)
{
   DString t (value);

   t.stripTrailing();
   _mapParms [name] = t;
}

//*******************************************************************************
DString NasuParams::getParameter (const DString &name)
{
   ParmMap::const_iterator itParms = _mapParms.find (name);
   DString valueOut = NULL_STRING;

   if (itParms != _mapParms.end())
   {
      valueOut = (*itParms).second;
   }
   return valueOut;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/NASUProcess.cpp-arc  $
 * 
 *    Rev 1.68   Feb 24 2012 16:06:06   popescu
 * NASU - Added commitment.
 * 
 *    Rev 1.67   Feb 07 2012 18:08:38   dchatcha
 * IN# 2837678 - REL12.2-PET0186484- New INA Contract Information screen issues as on 6 Feb 2012
 * 
 *    Rev 1.66   Dec 26 2011 22:27:14   dchatcha
 * P0186484 - FN 05 - work on Contract Information Screen
 * 
 *    Rev 1.65   Dec 19 2011 23:31:54   popescu
 * P0186484 - FN 05 - work on Contract Information Screen
 * 
 *    Rev 1.64   Jun 29 2011 14:37:04   wutipong
 * IN#2556973 Unable to change shareholder group
 * 
 *    Rev 1.63   Sep 17 2010 07:17:16   kitticha
 * PETP0173756 FN02 Don't Bust the Rules.
 * 
 *    Rev 1.62   Jun 10 2010 16:09:26   popescu
 * Incident 2149355 - look at GC NasuPopup to check if we should pop the RESP Account Info screen or not.
 * 
 *    Rev 1.61   Apr 09 2010 21:07:52   popescu
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.60   Apr 06 2010 06:24:46   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU, force warning message box to be pop up in case that use select taxtype M and doesn't touch any field on RESP account info screen.
 * 
 *    Rev 1.59   Apr 03 2010 02:32:10   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.58   Mar 26 2010 09:31:46   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.57   Mar 12 2010 14:25:18   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.56   Apr 24 2009 04:26:28   dchatcha
 * IN 1653090 - The KYC screen need to made mandatory in the NASU process.
 * 
 *    Rev 1.55   Nov 28 2008 13:51:12   jankovii
 * PET 142196 FN01 Federal Restricted LIF and LIRA.
 * 
 *    Rev 1.54   Nov 25 2008 11:10:34   jankovii
 * PET 142196 FN01 Federal Restricted LIF and LIRA.
 * 
 *    Rev 1.53   Jul 25 2008 14:17:14   jankovii
 * PET 59888 - AML Enhancement.
 * 
 *    Rev 1.52   Oct 08 2007 12:15:08   smithdav
 * IN  1005517,1020252 - LRSP logic
 * 
 *    Rev 1.51   01 May 2007 13:55:18   popescu
 * Incident: ? (got raised by Lux - C.Rigot) account# is invalid for acct cut off times trxn sent, and acct category
 * 
 *    Rev 1.50   Nov 09 2006 17:49:52   ZHANGCEL
 * PET 2286 FN01 -- Add Bank and Distribution in NASU flow
 * 
 *    Rev 1.49   Sep 20 2004 11:12:00   YINGBAOL
 * PET1117:FN05 FeeModel at account/shareholder level can be part of NASU
 * 
 *    Rev 1.48   Aug 11 2004 11:59:54   AGUILAAM
 * PET1117_FN02:  Account Static enhancement for SSBG - added new acct categories, and contact person, registrationinfo fields
 * 
 *    Rev 1.47   Feb 23 2004 14:33:10   popescu
 * PTS 10027142, Changed the nasuParams object from a BFData object to a map of strings, keyed by the name of  a parameter
 * 
 *    Rev 1.46   Feb 16 2004 09:29:44   YINGBAOL
 * PTS10027142   When there is a transaction error, NASU flow should not continue
 * 
 *    Rev 1.45   Dec 04 2003 16:58:04   popescu
 * PTS 10024286, if NasuPopupOptions has the command codes in  (i.e. KYC) then display the screen. Otherwise skip it. Previous version was coded the other way around.
 * 
 *    Rev 1.44   Nov 24 2003 13:35:02   popescu
 * PTS 10024286, read the NASUPopupOptions a generic control  setting that allows a management compnay to skip specific screens, during NASU flow
 * 
 *    Rev 1.43   Aug 19 2003 14:24:26   YINGBAOL
 * fix if condition
 * 
 *    Rev 1.42   Aug 18 2003 16:01:46   YINGBAOL
 * account level AMS will be part of the NASU flow
 * 
 *    Rev 1.41   Jul 11 2003 16:11:12   FENGYONG
 * show KYC screen
 * 
 *    Rev 1.40   Mar 21 2003 17:45:38   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.39   Jan 25 2003 17:13:54   KOVACSRO
 * Added Account Category.
 * 
 *    Rev 1.38   Dec 06 2002 10:56:06   YINGBAOL
 * PRIF Enhancement
 * 
 *    Rev 1.37   Oct 09 2002 23:53:30   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.36   Aug 29 2002 16:45:10   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.35   Aug 29 2002 12:54:36   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.34   Jul 26 2002 15:28:14   YINGBAOL
 * fix PTS10009161
 * 
 *    Rev 1.33   Jul 03 2002 16:18:06   HSUCHIN
 * bug fix for pension info not showing up for LRIF
 * 
 *    Rev 1.32   Jun 02 2002 17:52:44   HSUCHIN
 * added pension info
 * 
 *    Rev 1.31   22 May 2002 18:24:52   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.30   27 Mar 2002 19:55:32   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.29   11 Dec 2001 09:12:54   KOVACSRO
 * Moved ESoP after Entity.
 * 
 *    Rev 1.28   23 Nov 2001 11:03:26   HSUCHIN
 * passing NASU params to AcctSplitCommProcess
 * 
 *    Rev 1.27   21 Nov 2001 10:08:52   HSUCHIN
 * added COMMANDRETURN parameter to store the last command during NASU process
 * 
 *    Rev 1.26   19 Sep 2001 14:55:10   KOVACSRO
 * Added ESOP.
 * 
 *    Rev 1.25   Sep 12 2001 11:12:06   ZHANGCEL
 * Added a new paramer: MODEL_ACCOUNT_NUM in _entityParams{}
 * 
 *    Rev 1.24   03 Sep 2001 13:23:40   HSUCHIN
 * added Account level split commission
 * 
 *    Rev 1.23   Aug 23 2001 16:06:08   JANKAREN
 * Added As Pension Plan
 * 
 *    Rev 1.22   15 May 2001 15:38:50   YINGZ
 * data group id clean up
 * 
 *    Rev 1.21   03 May 2001 14:05:36   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.20   Apr 06 2001 17:15:40   YINGZ
 * make group id work
 * 
 *    Rev 1.19   Mar 29 2001 15:53:00   DINACORN
 * Used DSTCommonFunctions MARKET_IDS constants
 * 
 *    Rev 1.18   Feb 13 2001 13:39:06   YINGZ
 * export NASULIT
 * 
 *    Rev 1.17   Feb 12 2001 14:57:36   YINGBAOL
 * take out contract info from NASU if it is Japan
 * 
 *    Rev 1.16   Jan 19 2001 17:49:10   KOVACSRO
 * Bug fixed for skipping COA from BPServer.
 * 
 *    Rev 1.15   Jan 18 2001 09:39:12   KOVACSRO
 * Forced a null string value for AccountNum in doInit ().
 * 
 *    Rev 1.14   Jan 17 2001 17:28:48   KOVACSRO
 * Modified doFlow ().
 * 
 *    Rev 1.13   Jan 04 2001 09:41:16   ZHANGCEL
 * Added a new parameter CREATEING_ACCOUNT
 * 
 *    Rev 1.12   Dec 28 2000 17:05:36   KOVACSRO
 * Bug fixed. Clear the AccountNum every time ShareholderProcess is invoked.
 * 
 *    Rev 1.11   15 Dec 2000 12:43:44   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.10   Oct 19 2000 17:14:08   KOVACSRO
 * Deleted a param for ContractInfo Process.
 * 
 *    Rev 1.9   Oct 19 2000 16:46:18   VASILEAD
 * Skipped COA process for BPServer
 * 
 *    Rev 1.8   Oct 18 2000 11:01:22   KOVACSRO
 * Modified doFlow () to keep the original design.
 * 
 *    Rev 1.7   Oct 17 2000 15:39:38   KOVACSRO
 * ContractInfo is invoked now every time for a seg fund.
 * 
 *    Rev 1.6   Oct 17 2000 13:34:04   KOVACSRO
 * Added ContractInfo to the flow, for SegFunds.
 * 
 *    Rev 1.5   Oct 11 2000 14:12:00   KOVACSRO
 * Added parameter 'CalledFrom'.
 * 
 *    Rev 1.4   Oct 11 2000 11:55:10   VASILEAD
 * Added server updates support
 * 
 *    Rev 1.2   Oct 03 2000 11:19:46   VASILEAD
 * Added NASU server support
 * 
 *    Rev 1.1   Apr 04 2000 17:45:04   DT24433
 * removed use of _workSession and added revision block
 *
 */
