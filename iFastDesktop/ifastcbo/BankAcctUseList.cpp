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
//    Copyright 2002 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : BankAcctUseList.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 07/03/02
//
// ^CLASS    : BankAcctUseList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include <bfutil\bfguard.hpp>
#include "bankacctuselist.hpp"
#include "bankacctuse.hpp"
#include <ifastdataimpl\dse_dstc0212_req.hpp>
#include <ifastdataimpl\dse_dstc0212_vw.hpp>

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_("BankAcctUseList");
}

namespace BANKENTITY
{
   extern I_CHAR * const CLIENT;
   extern I_CHAR * const BROKER;
   extern I_CHAR * const BRANCH;
   extern I_CHAR * const SALESREP;
   extern I_CHAR * const FUND_CLASS;
   extern I_CHAR * const SHAREHOLDER;
   extern I_CHAR * const FUND;
   extern I_CHAR * const FUND_GROUP;
   extern I_CHAR * const FUND_SPONSOR;
   extern I_CHAR * const REG_AGENT;
   extern I_CHAR * const ACCOUNT;
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest BANK_ACCT_USAGE;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId SysDistrAcctUsageList;
   extern CLASS_IMPORT const BFTextFieldId AllBankAcctUse;
   extern CLASS_IMPORT const BFTextFieldId RepAcctUseCodeSet;
   extern CLASS_IMPORT const BFTextFieldId ClientAcctUseCodeSet;
   extern CLASS_IMPORT const BFTextFieldId FundAcctUseCodeSet;
	extern CLASS_IMPORT const BFTextFieldId TradeAcctUseCode;
}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const SHAREHOLDER;
   extern CLASS_IMPORT I_CHAR * const BROKER;
   extern CLASS_IMPORT I_CHAR * const BRANCH;
   extern CLASS_IMPORT I_CHAR * const SALESREP;
   extern CLASS_IMPORT I_CHAR * const FUND;
   extern CLASS_IMPORT I_CHAR * const CLIENT;
   extern CLASS_IMPORT I_CHAR * const FUND_CLASS;
   extern CLASS_IMPORT I_CHAR * const TRANSACTION;
   extern CLASS_IMPORT I_CHAR * const PENDING_TRADE;
   extern CLASS_IMPORT I_CHAR * const SYSTEMATIC;
   extern CLASS_IMPORT I_CHAR * const RRIF;
   extern CLASS_IMPORT I_CHAR * const TRADE;
   extern CLASS_IMPORT I_CHAR * const SETTLEMENT;
   extern CLASS_IMPORT I_CHAR * const DISTRIBUTION;
   extern CLASS_IMPORT I_CHAR * const DIRECT_TRADING;
   extern CLASS_IMPORT I_CHAR * const FUND_GROUP;
   extern CLASS_IMPORT I_CHAR * const FUND_SPONSOR;
   extern CLASS_IMPORT I_CHAR * const MATURITY_INSTRUCTIONS;
   extern CLASS_IMPORT I_CHAR * const REG_AGENT; 
   extern CLASS_IMPORT I_CHAR * const ACCOUNT; 
}

namespace  CND
{
   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
}
//******************************************************************************
BankAcctUseList::BankAcctUseList(BFAbstractCBO &parent) 
: MFCanBFCbo(parent),
m_strBankingEntity(NULL_STRING)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   setObjectAsList();
}


//******************************************************************************
BankAcctUseList::~BankAcctUseList(void)
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
SEVERITY BankAcctUseList::init(const DString& strBankType)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   m_strBankingEntity = getBankingEntity(strBankType);
   if (m_strBankingEntity.strip().empty())
      return(GETCURRENTHIGHESTSEVERITY());

   BFGuard cs(_csBankAcctUseSubList);

   BFObjIter iter(*this, BF::HOST, 0, BFObjIter::ITERTYPE::NON_DELETED);
   BFAbstractCBO *pBFCBO;
   DString str;
   while(!iter.end())
   {
      pBFCBO = iter.getObject();
      pBFCBO->getField(ifds::BankingEntity, str, BF::HOST, false);
      if (str.strip() == m_strBankingEntity)//view has been already called for this bank type
         return(GETCURRENTHIGHESTSEVERITY());
      ++iter;
   }

   BFData requestData(ifds::DSTC0212_REQ);
   DString mgmtCoIdOut, strNextKey = NULL_STRING;
   requestData.setElementValue(ifds::CompanyId, getMgmtCoId(mgmtCoIdOut));
   requestData.setElementValue(ifds::BankingEntity,  m_strBankingEntity );
   requestData.setElementValue(ifds::Track, I_("N"));
   requestData.setElementValue(ifds::Activity, NULL_STRING);
   requestData.setElementValue(ifds::NextKey,  strNextKey);

   if (ReceiveData(DSTC_REQUEST::BANK_ACCT_USAGE, requestData, ifds::DSTC0212_VW, DSTCRequestor(getSecurity(), true, true)) > WARNING)
   {
      int count = CONDITIONCOUNT();
      Condition   *c = NULL;
      for(int i = 0; i < count; i++)
      {
         c = GETCONDITION(i);
         int condCode = c->getCode();
         if (condCode == CND::ERR_DATA_NOT_FOUND)
         {
            CLEARCONDITION(i)
            BFObjectKey objKey;
            BFCBO* pBFCBO = getNewListItem(objKey);
            pBFCBO->setField(ifds::AcctUseCode, NULL_STRING, BF::HOST, false);
            break;
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
DString BankAcctUseList::getBankingEntity(const DString& strBankType)
{
   DString strBankEntity = NULL_STRING;
   DString strBankTypeCopy(strBankType);

   strBankTypeCopy.strip();
   if ( strBankTypeCopy == BANKTYPE::SHAREHOLDER || 
        strBankTypeCopy == BANKTYPE::ACCOUNT ||
        strBankTypeCopy == BANKTYPE::DIRECT_TRADING || 
        strBankTypeCopy == BANKTYPE::MATURITY_INSTRUCTIONS)
   {
      strBankEntity = BANKENTITY::SHAREHOLDER;
   }
   else if (strBankTypeCopy == BANKTYPE::CLIENT)
   {
      strBankEntity = BANKENTITY::CLIENT;
   }
   else if (strBankTypeCopy == BANKTYPE::BROKER)
   {
      strBankEntity = BANKENTITY::BROKER;
   }
   else if (strBankTypeCopy == BANKTYPE::BRANCH)
   {
      strBankEntity = BANKENTITY::BRANCH;
   }
   else if (strBankTypeCopy == BANKTYPE::SALESREP)
   {
      strBankEntity = BANKENTITY::SALESREP;
   }
   else if (strBankTypeCopy == BANKTYPE::FUND)
   {
      strBankEntity = BANKENTITY::FUND;
   }
   else if (strBankTypeCopy == BANKTYPE::FUND_CLASS)
   {
      strBankEntity = BANKENTITY::FUND_CLASS;
   }
   else if( strBankTypeCopy == BANKTYPE::FUND_GROUP)
   {
      strBankEntity = BANKENTITY::FUND_GROUP;
   }
   else if (strBankTypeCopy == BANKTYPE::FUND_SPONSOR)
   {
      strBankEntity = BANKENTITY::FUND_SPONSOR;
   }
   else if (strBankTypeCopy == BANKTYPE::REG_AGENT)
   {
	   strBankEntity = BANKENTITY::REG_AGENT;
   }
   else if ( strBankTypeCopy ==  BANKENTITY::ACCOUNT || 
            strBankTypeCopy ==  BANKENTITY::SHAREHOLDER )
   {
      strBankEntity = BANKENTITY::SHAREHOLDER;
   }
   
   return strBankEntity;
}

//******************************************************************************
DString BankAcctUseList::getAcctUseSubstList (const DString& strBankType)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getAcctUseSubstList"));
   
   init (strBankType);
   return buildSubList (strBankType);

}

//******************************************************************************
DString BankAcctUseList::buildSubList(const DString& strBankType)
{
   m_strBankingEntity = getBankingEntity(strBankType);
   DString strSubstList(NULL_STRING);
   if (!m_strBankingEntity.strip().empty())
   {
      BFGuard cs(_csBankAcctUseSubList);

      BFObjIter iter(*this, BF::HOST, 0, BFObjIter::ITERTYPE::NON_DELETED);
      BFAbstractCBO *pBFCBO;
      DString strBankEntity, strAcctUseCode, strAcctUseDescr;
      while(!iter.end())
      {
         pBFCBO = iter.getObject();
         pBFCBO->getField(ifds::BankingEntity, strBankEntity, BF::HOST, false);
         if (strBankEntity.strip() == m_strBankingEntity)//a match has been found
         {
            pBFCBO->getField(ifds::AcctUseCode, strAcctUseCode, BF::HOST, false);
            if (!strAcctUseCode.strip().empty())
            {
               strSubstList += strAcctUseCode.strip();
               strSubstList += I_("=");
               strAcctUseDescr = DSTCommonFunctions::getDescription(strAcctUseCode, ifds::AllBankAcctUse);
               strSubstList += strAcctUseDescr;
               strSubstList += I_(";");
            }
            else//view returned 'Data not found' - we'll show the old data dictionary substitution
               strSubstList = getDataDictSubst(strBankType);
         }
         ++iter;
      }
   }
   else//no view call is necessary
      strSubstList = getDataDictSubst(strBankType);
   return(strSubstList);
}
//******************************************************************************

SEVERITY BankAcctUseList::doCreateNewObject(BFCBO *& pBase, DString & strKey, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateNewObject"));

   BankAcctUse* pBankAcctUse = new BankAcctUse(*this);
   pBankAcctUse->setField(ifds::BankingEntity, m_strBankingEntity, BF::HOST, false);
   pBase = pBankAcctUse;

//   doCreateObject(NULL, pBase);
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY BankAcctUseList::doCreateObject(const BFData& data, BFCBO *&pObjOut)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateObject"));

   BankAcctUse* pBankAcctUse = new BankAcctUse(*this);
   pBankAcctUse->setField (ifds::BankingEntity, m_strBankingEntity, BF::HOST, false);
   pBankAcctUse->init(data);
   pObjOut = pBankAcctUse;
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
DString BankAcctUseList::getDataDictSubst (const DString& strBankType)
{
   DString strSubstList(NULL_STRING);
   BFFieldId idField = ifds::NullFieldId;
   
   if (strBankType == BANKTYPE::SHAREHOLDER ||
       strBankType == BANKTYPE::ACCOUNT ||
       strBankType == BANKTYPE::RRIF)
   {  
      idField = ifds::AcctUseCode;
   }
	else if (strBankType == BANKTYPE::TRADE ||
            strBankType == BANKTYPE::PENDING_TRADE ||
            strBankType == BANKTYPE::TRANSACTION ||
		      strBankType == BANKTYPE::SETTLEMENT)
   {  
      idField = ifds::TradeAcctUseCode;
   }   
   else if (strBankType == BANKTYPE::DISTRIBUTION)
   {
      idField = ifds::SysDistrAcctUsageList;
   }
   else if (strBankType == BANKTYPE::SYSTEMATIC)
   {
      idField = ifds::SysDistrAcctUsageList;
   }
   else if (strBankType == BANKTYPE::BROKER || 
            strBankType == BANKTYPE::BRANCH ||
            strBankType == BANKTYPE::SALESREP)
   {
      idField = ifds::RepAcctUseCodeSet;
   }
   else if (strBankType == BANKTYPE::CLIENT)
   {
      idField = ifds::ClientAcctUseCodeSet;
   }
   else if (strBankType == BANKTYPE::FUND ||
            strBankType == BANKTYPE::FUND_CLASS ||
            strBankType == BANKTYPE::FUND_GROUP ||
            strBankType == BANKTYPE::FUND_SPONSOR)
   {
      idField = ifds::FundAcctUseCodeSet;
   }
   if (idField != ifds::NullFieldId)
   {
      BFProperties * pProperties = getFieldProperties(idField, BF::HOST);
      pProperties->getAllSubstituteValues(strSubstList);
//quick hack for 57, should be removed in 58
      if (strBankType == BANKTYPE::TRANSACTION) //inquiry only
      {
         strSubstList += I_("16=EFT Dividend;");
      }
   }
   return strSubstList;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/BankAcctUseList.cpp-arc  $
// 
//    Rev 1.17   Apr 03 2012 20:03:04   wp040039
// PETP0187485- Registartion Agent  Banking
// 
//    Rev 1.16   Feb 02 2012 15:04:56   if991250
// Maturity/Interest Instructions banking
// 
//    Rev 1.15   Oct 18 2006 15:53:20   popescu
// PET 2217/26 STP Multiple Debit Accounts - fund sponsor banking
// 
//    Rev 1.14   Sep 21 2004 15:18:46   HERNANDO
// PET1094 FN8 - AdminFee related changes (By Celia)
// 
//    Rev 1.13   Sep 21 2004 13:34:22   HERNANDO
// PET1094 FN06 - Absatzmeldung Files enhancement.
// 
//    Rev 1.12   Jul 22 2004 09:56:16   popescu
// PTS 10027951, acct usage of the banking infor for a CASH ID transaction is displayed as 'EFT Dividend'
// 
//    Rev 1.11   Nov 28 2003 15:31:34   popescu
// Synch-up 1.8.10 PTS 10024361
// 
//    Rev 1.10   Oct 19 2003 16:43:22   popescu
// CIBC, PET809, FN 13 banking work
// 
//    Rev 1.9   Oct 06 2003 12:42:54   popescu
// Added banking support for DirectTrading enhancement
// 
//    Rev 1.8   Jul 31 2003 17:06:10   popescu
// fund/class search work
// 
//    Rev 1.7   Jun 18 2003 17:44:58   popescu
// RRIF Banking Enhancement , business rules, bug fixes 
// 
//    Rev 1.6   May 23 2003 10:04:10   popescu
// Part of bank instructions cleaning up process, moved the bank types into the ifastids project
// 
//    Rev 1.5   Mar 21 2003 18:00:06   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.4   Oct 09 2002 23:54:02   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.3   Sep 30 2002 11:01:12   PURDYECH
// BFFieldId no longer has operator long(), so explicit getId() calls are needed in places.
// 
//    Rev 1.2   Aug 29 2002 12:55:06   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.1   Jul 08 2002 15:19:24   KOVACSRO
// small fix.
// 
//    Rev 1.0   Jul 05 2002 12:02:52   KOVACSRO
// Initial revision.
// 
 * 
 *
*/