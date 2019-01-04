/*//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Canada, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2001 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : BankTransactionList.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : 3/30/01
//
// ^CLASS    : BankTransactionList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "banktransactionlist.hpp"
#include "banktransaction.hpp"
#include <dataimpl\dse_dstc0055_vw.hpp>
#include <dataimpl\dse_dstc0055_req.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest TRANSACTIONBANKINSTR;
}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const TRANSACTION;
   extern CLASS_IMPORT I_CHAR * const PENDING_TRADE;
}

namespace
{
   const I_CHAR * const CLASSNAME = I_("BankTransactionList");
}

//************************************************************************************
BankTransactionList::BankTransactionList(BFAbstractCBO &parent)
: MFCanBFCbo(parent),
m_strBankType(NULL_STRING)
{
   TRACE_CONSTRUCTOR(CLASSNAME , NULL_STRING);
   setObjectAsList();
}

//*************************************************************************************
BankTransactionList::~BankTransactionList()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//*************************************************************************************
SEVERITY BankTransactionList::init(const DString& strTransId, const DString& strPendingRid,
   const DString& strTransPending, const DString& dstrTradeDate, 
   const DString& dstrTrack, const DString& dstrPageName) 
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   BFData queryData(ifds::DSTC0055_REQ);

   m_dstrTradeDate =  dstrTradeDate;
   if(strTransPending == I_("T"))
   {
      m_strBankType = BANKTYPE::TRANSACTION;
   }
   else if(strTransPending == I_("P"))
   {
      m_strBankType = BANKTYPE::PENDING_TRADE;
   }
   else 
   {
      assert(0);//??
   }

   DString mgmtCoIdOut;

   queryData.setElementValue(ifds::CompanyId, getMgmtCoId(mgmtCoIdOut));
   queryData.setElementValue(ifds::TransId, strTransId );
   queryData.setElementValue(ifds::PendingRid, strPendingRid);
   queryData.setElementValue(ifds::TransPending, strTransPending );
   queryData.setElementValue(ifds::Track, dstrTrack);
   queryData.setElementValue(ifds::Activity, dstrPageName);
   ReceiveData(DSTC_REQUEST::TRANSACTIONBANKINSTR, queryData, 
      ifds::DSTC0055_VW, DSTCRequestor(getSecurity(),true));
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
SEVERITY BankTransactionList::doCreateObject(const BFData& data, BFCBO *&pObjOut)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateObject"));
   pObjOut = new BankTransaction(*this);
   dynamic_cast< BankTransaction * >(pObjOut)->init(data, m_dstrTradeDate, m_strBankType);
   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************
SEVERITY BankTransactionList::doCreateNewObject(BFCBO *& pBase, DString & strKey, 
   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateNewObject"));

   pBase = new BankTransaction(*this);
   dynamic_cast< BankTransaction * >(pBase)->initNew(m_dstrTradeDate, m_strBankType, idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/BankTransactionList.cpp-arc  $
// 
//    Rev 1.12   Nov 14 2004 14:29:10   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.11   Oct 19 2003 16:44:12   popescu
// CIBC, PET809, FN 13 banking work
// 
//    Rev 1.10   Sep 26 2003 13:59:40   popescu
// Fixed the occurence of wrong choices in the acctusage field for pending trade banking; this under PTS 10020130; 
// 
//    Rev 1.9   May 23 2003 10:04:18   popescu
// Part of bank instructions cleaning up process, moved the bank types into the ifastids project
// 
//    Rev 1.8   Mar 21 2003 18:00:46   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.7   Oct 09 2002 23:54:06   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.6   Aug 29 2002 12:55:08   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.5   Jul 05 2002 11:56:22   KOVACSRO
// Added bankType
// 
//    Rev 1.4   Jun 16 2002 17:03:46   KOVACSRO
// removed init2
// 
//    Rev 1.3   22 May 2002 18:26:32   PURDYECH
// BFData Implementation
// 
//    Rev 1.2   09 May 2001 15:05:10   HSUCHIN
// Sync up with SSB
// 
//    Rev 1.1   03 May 2001 14:06:02   SMITHDAV
// Session management restructuring.
// 
//    Rev 1.0   Apr 02 2001 16:53:52   YINGBAOL
// Initial revision.
// 


*/
