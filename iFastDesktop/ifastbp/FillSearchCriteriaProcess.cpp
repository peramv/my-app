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
// ^FILE   : FillSearchCriteriaProcess.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : 21/07/99
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : FillSearchCriteriaProcess
//    This class manages the substitution lists for the GUI search criteria
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"

#include "fillsearchcriteriaprocess.hpp"
#include "fillsearchcriteriaprocessincludes.h"

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FILL_SEARCH_CRITERIA;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< FillSearchCriteriaProcess > processCreator(CMD_BPROC_FILL_SEARCH_CRITERIA);

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_("FillSearchCriteriaProcess");
   const I_CHAR * const LABEL1_MNEMONIC = I_("L1");
   const I_CHAR * const LABEL2_MNEMONIC = I_("L2");
   const I_CHAR * const LABEL3_MNEMONIC = I_("L3");
   const I_CHAR * const COMMA = I_(",");
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace SEARCHCRITERIA
{
   //these are, actually, codes defined in the databroker.bin,
   //they are the substitute codes for the SearchCriteria field
   const I_CHAR* const ACCOUNT_SEARCH              = I_("SC1");
   const I_CHAR* const CHEQUE_SEARCH               = I_("SC2");
   const I_CHAR* const CERTIFICATE_SEARCH          = I_("SC3");
   const I_CHAR* const SHAREHOLDER_INFO_SEARCH     = I_("SC4");
   const I_CHAR* const ACCOUNT_INFO_SEARCH         = I_("SC5");
   const I_CHAR* const ADDRESS_SEARCH              = I_("SC6");
   const I_CHAR* const SYSTEMATICS_SEARCH          = I_("SC7");
   const I_CHAR* const BANKING_SEARCH              = I_("SC8");
   const I_CHAR* const ENTITY_SEARCH               = I_("SC9");
   const I_CHAR* const COA_SEARCH                  = I_("SC10");
   const I_CHAR* const DISTRIBUTIONS_SEARCH        = I_("SC11");
   const I_CHAR* const ALLOCATIONS_SEARCH          = I_("SC12");
   const I_CHAR* const TRADE_SEARCH                = I_("SC13");
   const I_CHAR* const AMSGLOBAL_SEARCH            = I_("SC14");   
   const I_CHAR* const ALLENTITY_SEARCH            = I_("SC15");   
   const I_CHAR* const ACCOUNT_REGULATORY_SEARCH   = I_("SC16");

   const BFFieldId CURRENT_USING_LIST(1);
   const BFFieldId LABEL1(2);
   const BFFieldId LABEL2(3);
   const BFFieldId LABEL3(4);
}

namespace SEARCHACCOUNTUSING
{
   //these are, actually, codes defined in the databroker.bin;
   //they are the substitute codes for the SearchAccountUsing field
   const I_CHAR* const ACCOUNT_NUMBER                    = I_("SC1U01");
   const I_CHAR* const NAME                              = I_("SC1U02");
   const I_CHAR* const TELEPHONE                         = I_("SC1U03");
   const I_CHAR* const SOCIAL_INSURANCE_NUMBER           = I_("SC1U04");
   const I_CHAR* const CREDIT_CARD                       = I_("SC1U05");
   const I_CHAR* const DRIVER_LICENSE                    = I_("SC1U06");
   const I_CHAR* const PASSPORT                          = I_("SC1U07");
   const I_CHAR* const BIRTH_CERTIFICATE                 = I_("SC1U08");
   const I_CHAR* const NATIONAL_ID                       = I_("SC1U09");
   const I_CHAR* const SOCIAL_SECURITY_INSURANCE_CARD    = I_("SC1U10");
   const I_CHAR* const SHAREHOLDER_NUMBER                = I_("SC1U11");
   const I_CHAR* const ALT_ACCOUNT_AND_BROKER_CODE       = I_("SC1U12");
   const I_CHAR* const BROKER_CODE                       = I_("SC1U13");
   const I_CHAR* const ID_OTHER                          = I_("SC1U14");
   const I_CHAR* const BIRTH_NAME                        = I_("SC1U15");
   const I_CHAR* const INTERMEDIARY_CODE                 = I_("SC1U16"); 
   const I_CHAR* const OTHER_REFERENCE_NUMBER            = I_("SC1U17"); 
   const I_CHAR* const BUSINESSNO			               = I_("SC1U18");
   const I_CHAR* const CIF			                        = I_("SC1U19");
   const I_CHAR* const ACCESS_ID                         = I_("SC1U20");
   const I_CHAR* const CLEARING_ID                       = I_("SC1U21"); //MT535/MT536
   const I_CHAR* const HOUSEHOLD                         = I_("SC1U22"); 
   const I_CHAR* const REGISTRATION_AGENT                = I_("SC1U23"); 
   const I_CHAR* const CPFB_NUMBER                       = I_("SC1U24"); 

}  

namespace SEARCHCHEQUEUSING
{
   //these are, actually, codes defined in the databroker.bin;
   //they are the substitute codes for the SearchChequeUsing field
   const I_CHAR* const CHEQUE_NUMBER   = I_("SC2U01");
   const I_CHAR* const ACCOUNT_NUMBER  = I_("SC2U02");
   const I_CHAR* const BROKER          = I_("SC2U03");
}

namespace SEARCHCERTIFICATEUSING
{
   //these are, actually, codes defined in the databroker.bin;
   //they are the substitute codes for the SearchChequeUsing field
   const I_CHAR* const CERTIFICATE_NUMBER_AND_FUND_CODE  = I_("SC3U01");
   const I_CHAR* const ACCOUNT_NUMBER                    = I_("SC3U02");
}

namespace SEARCHSYSTEMATICSUSING
{
   const I_CHAR* const ACCOUNT_NUMBER  = I_("SC7U01");
}

namespace SEARCHBANKINGUSING
{
   const I_CHAR* const ACCOUNT_NUMBER        = I_("SC8U01");
   const I_CHAR* const BROKER_CODE           = I_("SC8U02");
   const I_CHAR* const BRANCH_CODE           = I_("SC8U03");
   const I_CHAR* const REP_CODE              = I_("SC8U04");
   const I_CHAR* const NEW_ACCOUNT_NUMBER    = I_("SC8U05");
   const I_CHAR* const CLIENT                = I_("SC8U06");
   const I_CHAR* const FUND                  = I_("SC8U07"); 
   const I_CHAR* const FUND_CLASS            = I_("SC8U08"); 
   const I_CHAR* const FUND_GROUP            = I_("SC8U09"); 
   const I_CHAR* const FUND_SPONSOR          = I_("SC8U10");
   const I_CHAR* const REG_AGENT			 = I_("SC8U11");
}

namespace SEARCHENTITYUSING
{
   const I_CHAR* const ACCOUNT_NUMBER                    = I_("SC9U01");
   const I_CHAR* const NAME                              = I_("SC9U02");
   const I_CHAR* const SOCIAL_SECURITY_INSURANCE_CARD    = I_("SC9U03");
   const I_CHAR* const PASSPORT                          = I_("SC9U04");
   const I_CHAR* const DRIVER_LICENSE                    = I_("SC9U05");
   const I_CHAR* const SOCIAL_INSURANCE_NUMBER           = I_("SC9U06");
   const I_CHAR* const CREDIT_CARD                       = I_("SC9U07");
   const I_CHAR* const BIRTH_CERTIFICATE                 = I_("SC9U08");
   const I_CHAR* const NATIONAL_ID                       = I_("SC9U09");
   const I_CHAR* const ENTITY_ID                         = I_("SC9U10");
   const I_CHAR* const CLEARING_ID                       = I_("SC9U11"); //MT535/MT536
   const I_CHAR* const CPFB_ACCT_NUM					 = I_("SC9U12");
   const I_CHAR* const ACCOUNT_MANAGER_UNIQUE_ID         = I_("SC9U13");
}

namespace SEARCHALLENTITYUSING
{
   const I_CHAR* const NAME                              = I_("SC15U01");
   const I_CHAR* const SOCIAL_SECURITY_INSURANCE_CARD    = I_("SC15U02");
   const I_CHAR* const PASSPORT                          = I_("SC15U03");
   const I_CHAR* const DRIVER_LICENSE                    = I_("SC15U04");
   const I_CHAR* const SOCIAL_INSURANCE_NUMBER           = I_("SC15U05");
   const I_CHAR* const CREDIT_CARD                       = I_("SC15U06");
   const I_CHAR* const BIRTH_CERTIFICATE                 = I_("SC15U07");
   const I_CHAR* const NATIONAL_ID                       = I_("SC15U08");
   const I_CHAR* const ENTITY_ID                         = I_("SC15U09");
   const I_CHAR* const WHEREUSE                          = I_("SC15U10");
   const I_CHAR* const CLEARING_ID                       = I_("SC15U11"); //MT535/MT536
   const I_CHAR* const REG_AGENT						 = I_("SC15U12");
}

namespace SEARCHADDRESSUSING
{
   const I_CHAR* const ACCOUNT_NUMBER     = I_("SC6U01");
   const I_CHAR* const SHAREHOLDER_NUMBER = I_("SC6U02");
}

namespace SEARCHCOAUSING
{
   const I_CHAR* const ACCOUNT_NUMBER  = I_("SC10U01");
}

namespace SEARCHDISTRIBUTIONSUSING
{
   const I_CHAR* const ACCOUNT_NUMBER  = I_("SC11U01");
}

namespace SEARCHALLOCATIONSUSING
{
   const I_CHAR* const ACCOUNT_NUMBER  = I_("SC12U01");
}

namespace SEARCHSHAREHOLDERUSING
{
   const I_CHAR* const SHAREHOLDER_NUMBER = I_("SC4U01");
   const I_CHAR* const ACCOUNT_NUMBER     = I_("SC4U02");
}

namespace SEARCHACCOUNTINFOUSING
{
   const I_CHAR* const ACCOUNT_NUMBER  = I_("SC5U01");
}

namespace SEARCHTRADEUSING
{
   const I_CHAR* const ACCOUNT_NUMBER     = I_("SC13U01");
   const I_CHAR* const SHAREHOLDER_NUMBER = I_("SC13U02");
   const I_CHAR* const ACOUNT_BROKER      = I_("SC13U03");
}

namespace SEARCHGLOBALUSING
{
   const I_CHAR* const REBALANCING  = I_("SC14U01");
   const I_CHAR* const REPORT       = I_("SC14U02");
}

namespace SEARCHACCOUNTREGULATORYUSING
{
   const I_CHAR* const ACCOUNT_NUMBER              = I_("SC16U01");
   const I_CHAR* const OTHER_REFERENCE_NUMBER      = I_("SC16U02");
}

//******************************************************************************
//              Public Methods
//******************************************************************************
FillSearchCriteriaProcess::FillSearchCriteriaProcess(GenericInterfaceContainer* pGIC, 
   GenericInterface* pGIParent, const Command& rCommand)
: AbstractProcess(pGIC, pGIParent, rCommand)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);

   //main search
   addSubstituteList(ifds::SearchCriteria);
   addSubstituteList(ifds::SearchAccountUsing);
   addSubstituteList(ifds::SearchChequeUsing);
   addSubstituteList(ifds::SearchCertificateUsing);
   addSubstituteList(ifds::SearchSystematicsUsing);
   addSubstituteList(ifds::SearchBankingUsing);
   addSubstituteList(ifds::SearchEntityUsing);
   addSubstituteList(ifds::SearchAddressUsing);
   addSubstituteList(ifds::SearchCOAUsing);
   addSubstituteList(ifds::SearchDistributionsUsing);
   addSubstituteList(ifds::SearchAllocationsUsing);
   addSubstituteList(ifds::SearchShareholderUsing);
   addSubstituteList(ifds::SearchAccountInfoUsing);
   addSubstituteList(ifds::SearchTradeUsing);
   addSubstituteList(ifds::SearchAMSUsing);  
   addSubstituteList(ifds::SearchAllEntityUsing);     
   addSubstituteList(ifds::SearchAccountRegulatoryUsing);
   addSubstituteList(ifds::SearchLabels);
   addFieldDetails(SEARCHCRITERIA::LABEL1, BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails(SEARCHCRITERIA::LABEL2, BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails(SEARCHCRITERIA::LABEL3, BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails(SEARCHCRITERIA::CURRENT_USING_LIST, BF::NullContainerId, SUBCLASS_PROCESS);
}

//******************************************************************************
FillSearchCriteriaProcess::~FillSearchCriteriaProcess()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

void FillSearchCriteriaProcess::doGetField(const GenericInterface *rpGICaller,
   const BFContainerId& idContainer, const BFFieldId& idField,
   const BFDataGroupId& idDataGroup, DString &strValueOut,
   bool bFormatted) const
{
   SEVERITY sevRtn = NO_CONDITION;

   if (idField == SEARCHCRITERIA::CURRENT_USING_LIST)
   {
      strValueOut = _currentUsingList;
   }
   else if (idField == SEARCHCRITERIA::LABEL1)
   {
      strValueOut = _label1;
   }
   else if (idField == SEARCHCRITERIA::LABEL2)
   {
      strValueOut = _label2;
   }
   else if (idField == SEARCHCRITERIA::LABEL3)
   {
      strValueOut = _label3;
   }
   else
   {
// TODO add condition if this code stays
      assert(0);
      throw;
   }
}

//******************************************************************************
SEVERITY FillSearchCriteriaProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, DOINIT);
   SEVERITY sevRtn = SEVERE_ERROR;

   sevRtn = NO_CONDITION;
   return(sevRtn);
}

//******************************************************************************
E_COMMANDRETURN FillSearchCriteriaProcess::doProcess()
{  
   MAKEFRAME2(CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS);
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      rtn = CMD_MODELESS_INPROCESS;
   }
   catch(ConditionException &ce)
   {
      assert(0);
      SETCONDITIONFROMEXCEPTION(ce);
   }
   catch(...)
   {
      assert(0);
      THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS,
                      CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return(rtn);
}

//******************************************************************************
SEVERITY FillSearchCriteriaProcess::doSetField(const GenericInterface *rpGICaller,
   const BFContainerId& idContainer, const BFFieldId& idField,
   const BFDataGroupId& idDataGroup, const DString& strValue,
   bool bFormatted)
{
   SEVERITY sevRtn = NO_CONDITION;

   if (idField == SEARCHCRITERIA::CURRENT_USING_LIST)
   {
      _currentUsingList = strValue;
   }
   else if (idField == SEARCHCRITERIA::LABEL1)
   {
      _label1 = strValue;
   }
   else if (idField == SEARCHCRITERIA::LABEL2)
   {
      _label2 = strValue;
   }
   else if (idField == SEARCHCRITERIA::LABEL3)
   {
      _label3 = strValue;
   }
   else
   {
// TODO add condition if this code stays
      sevRtn = SEVERE_ERROR;
   }
   return(sevRtn);
}

//******************************************************************************
//this method is overriden because it sets the current using list,
//and the current using labels
void FillSearchCriteriaProcess::setCurrentListItem(const GenericInterface *rpGICaller,
   const BFContainerId& idList, const DString& strListItemKey)
{
   AbstractProcess::setCurrentListItem(rpGICaller, idList, strListItemKey);
   DString searchCriteriaCode,
      currentUsingList;

   getField(this, idList, ifds::Substitute_Code, searchCriteriaCode);
   if (idList == BFContainerId(ifds::SearchCriteria.getId())) //set the current using list to be used
   {

      if (searchCriteriaCode == SEARCHCRITERIA::ACCOUNT_SEARCH)
      {
         currentUsingList = DString::asString(ifds::SearchAccountUsing.getId());
      }
      else if (searchCriteriaCode == SEARCHCRITERIA::CHEQUE_SEARCH)
      {
         currentUsingList = DString::asString(ifds::SearchChequeUsing.getId());
      }
      else if (searchCriteriaCode == SEARCHCRITERIA::CERTIFICATE_SEARCH)
      {
         currentUsingList = DString::asString(ifds::SearchCertificateUsing.getId());
      }
      else if (searchCriteriaCode == SEARCHCRITERIA::SHAREHOLDER_INFO_SEARCH)
      {
         currentUsingList = DString::asString(ifds::SearchShareholderUsing.getId());
      }
      else if (searchCriteriaCode == SEARCHCRITERIA::ACCOUNT_INFO_SEARCH)
      {
         currentUsingList = DString::asString(ifds::SearchAccountInfoUsing.getId());
      }
      else if (searchCriteriaCode == SEARCHCRITERIA::ADDRESS_SEARCH)
      {
         currentUsingList = DString::asString(ifds::SearchAddressUsing.getId());
      }
      else if (searchCriteriaCode == SEARCHCRITERIA::SYSTEMATICS_SEARCH)
      {
         currentUsingList = DString::asString(ifds::SearchSystematicsUsing.getId());
      }
      else if (searchCriteriaCode == SEARCHCRITERIA::BANKING_SEARCH)
      {
         currentUsingList = DString::asString(ifds::SearchBankingUsing.getId());
      }
      else if (searchCriteriaCode == SEARCHCRITERIA::ENTITY_SEARCH)
      {
         currentUsingList = DString::asString(ifds::SearchEntityUsing.getId());
      }
      else if (searchCriteriaCode == SEARCHCRITERIA::COA_SEARCH)
      {
         currentUsingList = DString::asString(ifds::SearchCOAUsing.getId());
      }
      else if (searchCriteriaCode == SEARCHCRITERIA::DISTRIBUTIONS_SEARCH)
      {
         currentUsingList = DString::asString(ifds::SearchDistributionsUsing.getId());
      }
      else if (searchCriteriaCode == SEARCHCRITERIA::ALLOCATIONS_SEARCH)
      {
         currentUsingList = DString::asString(ifds::SearchAllocationsUsing.getId());
      }
      else if (searchCriteriaCode == SEARCHCRITERIA::TRADE_SEARCH)
      {
         currentUsingList = DString::asString(ifds::SearchTradeUsing.getId());
      }
		else if (searchCriteriaCode == SEARCHCRITERIA::AMSGLOBAL_SEARCH)
		{		
		    currentUsingList = DString::asString(ifds::SearchAMSUsing.getId());
		}

		else if (searchCriteriaCode == SEARCHCRITERIA::ALLENTITY_SEARCH )
		{		
		    currentUsingList = DString::asString(ifds::SearchAllEntityUsing.getId());
		}
      else if (searchCriteriaCode == SEARCHCRITERIA::ACCOUNT_REGULATORY_SEARCH )
      {
         currentUsingList = DString::asString(ifds::SearchAccountRegulatoryUsing.getId());
      }

      setField(this, SEARCHCRITERIA::CURRENT_USING_LIST, currentUsingList);
   }
   else if (idList == BFContainerId(ifds::SearchAccountUsing.getId()) || 
      idList == BFContainerId(ifds::SearchChequeUsing.getId()) ||
      idList == BFContainerId(ifds::SearchCertificateUsing.getId()) ||
      idList == BFContainerId(ifds::SearchShareholderUsing.getId()) ||
      idList == BFContainerId(ifds::SearchAccountInfoUsing.getId()) || 
      idList == BFContainerId(ifds::SearchAddressUsing.getId()) ||
      idList == BFContainerId(ifds::SearchSystematicsUsing.getId()) ||
      idList == BFContainerId(ifds::SearchBankingUsing.getId()) ||
      idList == BFContainerId(ifds::SearchEntityUsing.getId()) ||
      idList == BFContainerId(ifds::SearchCOAUsing.getId()) ||
      idList == BFContainerId(ifds::SearchDistributionsUsing.getId()) ||
      idList == BFContainerId(ifds::SearchAllocationsUsing.getId()) || 
      idList == BFContainerId(ifds::SearchTradeUsing.getId() ) || 
      idList == BFContainerId(ifds::SearchAMSUsing.getId())  ||
      idList == BFContainerId(ifds::SearchAllEntityUsing.getId()) ||
      idList == BFContainerId(ifds::SearchAccountRegulatoryUsing.getId())
      )
   {
      assignSearchLabels(idList, BFContainerId(ifds::SearchLabels.getId()));
   }
      

}

//******************************************************************************
void FillSearchCriteriaProcess::assignSearchLabels(const BFContainerId &usingList, 
   const BFContainerId &searchLabelList)
{
   DString searchUsingCode;

   //resetting the labels
   setField(this, SEARCHCRITERIA::LABEL1, NULL_STRING);
   setField(this, SEARCHCRITERIA::LABEL2, NULL_STRING);
   setField(this, SEARCHCRITERIA::LABEL3, NULL_STRING);
   getField(this, usingList, ifds::Substitute_Code, searchUsingCode);
   //based on the 'using' code we need to search into the SearchLabels list and retrieve the
   //right labels; the labels contain in their code the 'using' code
   DString labelsKey = getFirstListItemKey(this, searchLabelList);

   do
   {
      DString fullLabelCode;
      DString labelDescription;

      getField(NULL, searchLabelList, ifds::Substitute_Code, fullLabelCode);

      //find the pos of the searchUsingCode
      DString::size_type labelPos = fullLabelCode.find(searchUsingCode);

      if (labelPos != DString::npos)
      {
         DString labelCode = fullLabelCode.substr(labelPos);
         DString::size_type commaPos = labelCode.find(COMMA);

         if (commaPos != DString::npos)
         {
            labelCode = labelCode.substr(0, commaPos);
         }
         getField(NULL, searchLabelList, ifds::Substitute_Description, labelDescription);
         if (labelCode.find(LABEL1_MNEMONIC) != DString::npos)
         {
            setField(this, SEARCHCRITERIA::LABEL1, labelDescription);
         }
         else if (labelCode.find(LABEL2_MNEMONIC) != DString::npos)
         {
            setField(this, SEARCHCRITERIA::LABEL2, labelDescription);
         }
         else if (labelCode.find(LABEL3_MNEMONIC) != DString::npos)
         {
            setField(this, SEARCHCRITERIA::LABEL3, labelDescription );
            break;
         }
      }
   }
   while((labelsKey = getNextListItemKey(NULL, searchLabelList)) != NULL_STRING);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/FillSearchCriteriaProcess.cpp-arc  $
 * 
 *    Rev 1.34   Apr 16 2012 17:25:34   if991250
 * CPF Account Setup
 * 
 *    Rev 1.33   Apr 04 2012 23:19:42   wp040039
 * PETP0187485-Entity Maintenance
 * 
 *    Rev 1.32   Apr 04 2012 11:25:10   wp040039
 * PETP0187485-Registration Agent  Banking
 * 
 *    Rev 1.31   Mar 29 2012 21:01:20   wp040039
 * PPETP0187485.FN01- CPF - Agent bank and CPFB 
 * Added Registration Agent 
 * 
 *    Rev 1.30   Oct 27 2011 07:27:54   popescu
 * P0188902 - DYN Household Project - added new search criteria to look for accounts based on a household
 * 
 *    Rev 1.29   Dec 15 2008 02:26:52   phiwponp
 * PET0007773_FN01_MT535-MT536 Enhancement.
 * 
 *    Rev 1.28   Sep 08 2008 15:56:34   jankovii
 * PET 5517 FN71 - Stale Cheque.
 * 
 *    Rev 1.27   12 Jul 2007 18:41:12   popescu
 * GAP 6 - CIF - added two new search types on the main screen - by CIF and by AccessID
 * 
 *    Rev 1.26   Oct 18 2006 15:53:12   popescu
 * PET 2217/26 STP Multiple Debit Accounts - fund sponsor banking
 * 
 *    Rev 1.25   Apr 18 2005 09:20:44   yingbaol
 * Incident 288575: add new search type:where use
 * 
 *    Rev 1.24   Mar 09 2005 16:07:58   yingbaol
 * PET1171,FN01:EU saving entity update
 * 
 *    Rev 1.23   Sep 21 2004 11:39:32   HERNANDO
 * PET1094 FN06 - Added SEARCHBANKINGUSING::FUND_GROUP.
 * 
 *    Rev 1.22   Aug 10 2004 11:12:02   FENGYONG
 * PET117 FN5 - Client Condition Fee
 * 
 *    Rev 1.21   Jul 16 2003 15:51:34   FENGYONG
 * Add Account search using businessno
 * 
 *    Rev 1.20   Jun 27 2003 18:12:24   popescu
 * Pay To Entity feature, dialog, process and CBO
 * 
 *    Rev 1.19   Mar 21 2003 17:39:52   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.18   Dec 27 2002 11:15:42   linmay
 * added Rebalancing and report for Global Plan
 * 
 *    Rev 1.17   Nov 25 2002 10:03:12   YINGBAOL
 * add search AMS Global criteria
 * 
 *    Rev 1.16   Oct 09 2002 23:53:14   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.15   Oct 09 2002 15:58:12   PURDYECH
 * BFFieldId fixups
 * 
 *    Rev 1.14   Sep 30 2002 11:01:02   PURDYECH
 * BFFieldId no longer has operator long(), so explicit getId() calls are needed in places.
 * 
 *    Rev 1.13   Aug 29 2002 16:44:54   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.12   Aug 29 2002 12:54:20   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.11   24 May 2002 15:19:14   KOVACSRO
 * Fund and Client bank.
 * 
 *    Rev 1.10   22 May 2002 18:24:16   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.9   27 Mar 2002 19:54:52   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.8   Jul 30 2001 14:04:34   YINGBAOL
 * take out hard code string
 * 
 *    Rev 1.7   Mar 22 2001 09:59:08   YINGBAOL
 * implement searching other reference number
 * 
 *    Rev 1.6   07 Mar 2001 15:41:58   BUZILAMI
 * Broker, Branch, SlsRep Bank Instructions changes
 * 
 *    Rev 1.5   Feb 22 2001 15:24:36   BUZILAMI
 * added search for bank using Broker, Branch and sales Rep
 * 
 *    Rev 1.4   15 Dec 2000 12:43:28   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.3   Aug 29 2000 15:17:04   YINGBAOL
 * add search account using intermediary code and account 
 * 
 *    Rev 1.2   Aug 16 2000 15:00:54   YINGBAOL
 * implement fundction "search for Trade"
 * 
 *    Rev 1.1   Aug 02 2000 15:32:00   BUZILA
 * "locale" changes
 * 
 *    Rev 1.0   Feb 15 2000 10:59:34   SMITHDAV
 * Initial revision.
// 
//    Rev 1.12   Dec 07 1999 12:29:24   DT24433
// added idDataGroup to doGetField/doSetField parms
// 
//    Rev 1.11   Oct 29 1999 11:24:40   DT24433
// removed doOk
// 
//    Rev 1.10   Oct 18 1999 15:16:10   POPESCUS
// 
//    Rev 1.9   Oct 18 1999 09:47:34   POPESCUS
// 
//    Rev 1.8   24 Sep 1999 16:52:54   HUANGSHA
// fixed bug
// 
//    Rev 1.7   24 Sep 1999 16:24:04   HUANGSHA
// Added search for Address Book
// 
//    Rev 1.6   Aug 31 1999 09:49:16   DT24433
// changed dogetfield/dosetfield parms
 * 
 */

