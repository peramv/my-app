//******************************************************************************
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
// ^FILE   : BankInstructions4TrxnList.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : October, 2003
//
// ^CLASS    : BankInstructions4TrxnList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "bankinstructions.hpp"
#include "bankinstructions4trxn.hpp"
#include "bankinstructions4trxnlist.hpp"
#include "trade.hpp"
//for view call
#include <ifastdataimpl\dse_dstc0055_vw.hpp>
#include <ifastdataimpl\dse_dstc0055_req.hpp>

namespace ifds
{
   //the type of the bank
   extern CLASS_IMPORT const BFTextFieldId BankInstrType;
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFDateFieldId TradeDate;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest TRANSACTIONBANKINSTR;
}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const TRANSACTION;
   extern CLASS_IMPORT I_CHAR * const PENDING_TRADE;
}

namespace BANK_TRXN_TYPE
{
   extern I_CHAR * const TRANSACTION         = I_("T");
   extern I_CHAR * const PENDING_TRADE       = I_("P");
   extern I_CHAR * const LAST_PENDING_TRADE  = I_("L");
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const REDEMPTION;
}

namespace
{
   const I_CHAR * const CLASSNAME = I_("BankInstructions4TrxnList");
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//   Field DD Id,             State Flags,      Group Flags
   { ifds::BankInstrType,     BFCBO::NONE,           0 }, 
   { ifds::AccountNum,        BFCBO::NONE,           0 }, 
   { ifds::TransType,         BFCBO::NONE,           0 }, 
   { ifds::EffectiveDate,     BFCBO::NONE,           0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//************************************************************************************
BankInstructions4TrxnList::BankInstructions4TrxnList (BFAbstractCBO &parent,
   const DString &dstrBankType) : MFCanBFCbo(parent),
_dstrBankType (dstrBankType)
{
   TRACE_CONSTRUCTOR(CLASSNAME , NULL_STRING);
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0, NULL/*(const CLASS_OBJECT_INFO *)&classObjectInfo*/ );
   setObjectAsList();
}

//*************************************************************************************
BankInstructions4TrxnList::~BankInstructions4TrxnList()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
SEVERITY BankInstructions4TrxnList::init ( const DString &accountNum,
                                           const DString &recordId, 
                                           const DString &transType, 
                                           const DString &type, 
                                           const DString &lastBankType,
                                           const DString &currency,
                                           const DString &effectiveDate,
                                           const DString &dstrTrack /*=I_("N")*/, 
                                           const DString &dstrPageName /*=NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));
   setFieldNoValidate (ifds::BankInstrType, _dstrBankType, BF::HOST, false, true, true);
   setFieldNoValidate (ifds::TransType, transType, BF::HOST, false, true, true);
   setFieldNoValidate (ifds::AccountNum, accountNum, BF::HOST, false, true, true);
   setFieldNoValidate (ifds::EffectiveDate, effectiveDate, BF::HOST, false, true, true);

   _dstrPayType = lastBankType;
   if ( transType == TRADETYPE::REDEMPTION )
   {
      _dstrPayType = _dstrPayType.right( _dstrPayType.size() - 2);
   }
   else
   {
      _dstrPayType = _dstrPayType.right(1);
   }

   DString mgmtCoIdOut;
   BFData queryData (ifds::DSTC0055_REQ);

   queryData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   if (type == BANK_TRXN_TYPE::TRANSACTION) //transaction history
   {
      queryData.setElementValue (ifds::TransId, recordId);
      queryData.setElementValue (ifds::PendingRid, NULL_STRING);
   }
   else if (type == BANK_TRXN_TYPE::PENDING_TRADE) //pending transaction
   {
      queryData.setElementValue (ifds::PendingRid, recordId);
      queryData.setElementValue (ifds::TransId, NULL_STRING);
   }
   else if (type == BANK_TRXN_TYPE::LAST_PENDING_TRADE) //last eft pending transaction
   {
      queryData.setElementValue (ifds::PendingRid, NULL_STRING);
      queryData.setElementValue (ifds::TransId, NULL_STRING);
      queryData.setElementValue (ifds::AccountNum, accountNum);
      queryData.setElementValue (ifds::Currency, currency);
   }
   queryData.setElementValue (ifds::TransPending, type);
   queryData.setElementValue (ifds::LastBankType, lastBankType);
   queryData.setElementValue (ifds::Track, dstrTrack);
   queryData.setElementValue (ifds::Activity, dstrPageName);
   ReceiveData ( DSTC_REQUEST::TRANSACTIONBANKINSTR, 
                 queryData, 
                 ifds::DSTC0055_VW, 
                 DSTCRequestor (getSecurity(), true, type != BANK_TRXN_TYPE::LAST_PENDING_TRADE));
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY BankInstructions4TrxnList::doCreateObject ( const BFData &data, 
                                                     BFCBO *&pObjOut)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doCreateObject"));

   DString transType, payType;

   getField (ifds::TransType, transType, BF::HOST, false);   

   BankInstructions4Trxn *pBankInstructions4Trxn = 
      new BankInstructions4Trxn (*this, transType, _dstrPayType);

   pBankInstructions4Trxn->init (data, _dstrBankType);
   pObjOut = pBankInstructions4Trxn;

   //set the effective date, only if the parent is not trade
   DString tradeDate, payMethod, fileProcessor;

   if (dynamic_cast <Trade*> (getParent()) == NULL)
   {
      getParent()->getField (ifds::TradeDate, tradeDate, BF::HOST, false);
	  getParent()->getField (ifds::PayMethod, payMethod, BF::HOST, false); 
	  getParent()->getField (ifds::ACHProcessor, fileProcessor, BF::HOST, false); 
   }
   else
   {
      getField (ifds::EffectiveDate, tradeDate, BF::HOST, false);
   }
   pBankInstructions4Trxn->setField (ifds::EffectiveDate, tradeDate, BF::HOST, false);
   pBankInstructions4Trxn->setField (ifds::PayMethod, payMethod, BF::HOST, false);
   pBankInstructions4Trxn->setFieldReadOnly (ifds::PayMethod, BF::HOST, true);
   pBankInstructions4Trxn->setField (ifds::ACHProcessor, fileProcessor, BF::HOST, false);
   pBankInstructions4Trxn->setFieldReadOnly (ifds::ACHProcessor, BF::HOST, true);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/BankInstructions4TrxnList.cpp-arc  $
// 
//    Rev 1.7   Jul 16 2009 19:15:16   dchatcha
// PET156681 FN14 H36 Investor Authorization, Integration issues.
// 
//    Rev 1.6   27 Jul 2007 15:40:32   popescu
// Incident 948449 - disabled the last EFT banking records call
// 
//    Rev 1.5   Dec 11 2004 13:25:30   popescu
// PET 1117/06, more fixes for banking instr in pending mode.
// 
//    Rev 1.4   Dec 10 2004 17:13:46   popescu
// Code formatting
// 
//    Rev 1.3   Nov 14 2004 14:28:14   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.2   Nov 04 2004 17:37:12   popescu
// PET 1117/06, Trade processing
// 
//    Rev 1.1   Jan 13 2004 13:45:46   popescu
// PET 910, System Integration Testing, Rel_55.0.0.2
// Transaction Banking returns Data Not Found, if no data available
// 
//    Rev 1.0   Nov 10 2003 14:55:04   popescu
// Initial revision.
// 
//    Rev 1.2   Oct 30 2003 17:26:14   FENGYONG
// add paytype as an parameter
// 
//    Rev 1.1   Oct 28 2003 10:37:40   FENGYONG
// Add bankType parameter
// 
//    Rev 1.0   Oct 19 2003 19:08:34   popescu
// Initial revision.
// 
*/
