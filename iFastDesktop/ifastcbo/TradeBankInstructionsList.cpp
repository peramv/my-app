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
// ^FILE   : TradeBankInstructionsList.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : October 2004
//
// ^CLASS    : TradeBankInstructionsList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "trade.hpp"
#include "tradebankinstructions.hpp"
#include "tradebankinstructionslist.hpp"

#include <ifastdataimpl\dse_dstc0055_vw.hpp>
#include <ifastdataimpl\dse_dstc0055_req.hpp>

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME = I_("TradeBankInstructionsList");
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId BankInstrType;
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest TRANSACTIONBANKINSTR;
}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const TRADE;
}

namespace BANK_TRXN_TYPE
{
   extern I_CHAR * const PENDING_TRADE;
}

//******************************************************************************
TradeBankInstructionsList::TradeBankInstructionsList(BFAbstractCBO &parent) : 
   BankInstructionsExList (parent, 
                           BANKTYPE::TRADE, 
                           ifds::DSTC0115_REQ, 
                           ifds::DSTC0115_REQRepeat_Record)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   setObjectAsList();
}

//******************************************************************************
TradeBankInstructionsList::~TradeBankInstructionsList()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
SEVERITY TradeBankInstructionsList::init ( const DString &accountNum,bool bRebook,                                           
                                           const BFDataGroupId &idDataGroup, 
                                           const DString &dstrTrack /*= I_("N")*/, 
                                           const DString &dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));
   DString mgmtCoIdOut,transId,
      recordId, 
      transType, 
      payType;

   BFData queryData (ifds::DSTC0055_REQ);

   getParent()->getField (ifds::InterDetlRid, recordId, idDataGroup, false);
   getParent()->getField (ifds::TradesTransType, transType, idDataGroup, false);
   getParent()->getField (ifds::TradesPayType, payType, idDataGroup, false);
   getParent()->getField (ifds::TransId, transId, idDataGroup, false);
   if( bRebook )
   {
      queryData.setElementValue (ifds::PendingRid, NULL_STRING);
      queryData.setElementValue (ifds::TransId, transId);   
      queryData.setElementValue (ifds::TransPending, I_("T"));

   }
   else
   {
      queryData.setElementValue (ifds::PendingRid, recordId);
      queryData.setElementValue (ifds::TransId, NULL_STRING);
      queryData.setElementValue (ifds::TransPending, BANK_TRXN_TYPE::PENDING_TRADE);

   }
   queryData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   queryData.setElementValue (ifds::LastBankType, I_("P-") + payType);
   queryData.setElementValue (ifds::Track, dstrTrack);
   queryData.setElementValue (ifds::Activity, dstrPageName);
   ReceiveData ( DSTC_REQUEST::TRANSACTIONBANKINSTR, 
                 queryData, 
                 ifds::DSTC0055_VW, 
                 DSTCRequestor (getSecurity(), true));
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradeBankInstructionsList::doCreateNewObject( BFCBO *&pBase, 
                                                       DString &strKey, 
                                                       const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doCreateNewObject"));
   pBase = NULL;
   TradeBankInstructions *pTradeBankInstructions = NULL;
//get the parent, should be Trade
   Trade *pTrade = dynamic_cast <Trade*> (getParent());

   if (pTrade) //check if we have any default bank instructions
   {
      pTrade->getDefaultBankInstructions ( pBase, 
                                           idDataGroup);
      if (pBase)
      {
         BFData rpBFData0052Repeat (ifds::DSTC0052_VWRepeat_Record);
//this looks like cloning, so do the required steps
         pTradeBankInstructions = new TradeBankInstructions (*this);

         if ( pBase->getData (rpBFData0052Repeat, idDataGroup) > WARNING ||
              pTradeBankInstructions->initBeforeCloning (idDataGroup) > WARNING ||
              pTradeBankInstructions->setData (rpBFData0052Repeat, idDataGroup) > WARNING ||
              pTradeBankInstructions->initNew (idDataGroup, true) > WARNING
            )
         {
            delete pTradeBankInstructions;
            pTradeBankInstructions = NULL;
         }
      }
   }
   if (!pTradeBankInstructions) //default not found
   {
      pTradeBankInstructions = new TradeBankInstructions (*this);
      pTradeBankInstructions->initNew (idDataGroup);
   }
   pBase = pTradeBankInstructions;
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradeBankInstructionsList::doCreateObject ( const BFData &data, 
                                                     BFCBO *&pObjOut)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doCreateObject"));
//the data object is comming from view 55 
   TradeBankInstructions 
      *pTradeBankInstructions = new TradeBankInstructions (*this);
   pTradeBankInstructions->init (data);
   pObjOut = pTradeBankInstructions;
   assert (getParent());

   //set the effective date, this field is not part of view 55, so it should be copied from the parent
   DString effectiveDate;
   if (dynamic_cast <Trade*> (getParent()) != NULL)
   {
      getParent()->getField (ifds::EffectiveDate, effectiveDate, BF::HOST, false);
      pTradeBankInstructions->setField (ifds::EffectiveDate, effectiveDate, BF::HOST, false);
   }  
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TradeBankInstructionsList.cpp-arc  $
// 
//    Rev 1.7   Oct 06 2006 13:39:50   popescu
// Incident# 729080 - refreshed banking once pending trade settle currency gets changed
// 
//    Rev 1.6   Aug 08 2005 09:13:40   Yingbaol
// PET1235,FN01:fix banking issue
// 
//    Rev 1.5   Feb 03 2005 11:51:30   popescu
// PTS 10038553, should copy EffectivDate field from parent Trade, since this field does not exist in view 55
// 
//    Rev 1.4   Dec 11 2004 13:25:34   popescu
// PET 1117/06, more fixes for banking instr in pending mode.
// 
//    Rev 1.3   Dec 11 2004 11:47:58   popescu
// PET 1117/56 more fixes, pending trade mods
// 
//    Rev 1.2   Nov 14 2004 14:57:46   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.1   Nov 06 2004 00:43:04   popescu
// PET 1117/06, synch changes
// 
//    Rev 1.0   Nov 01 2004 12:46:50   popescu
// Initial revision.
// 
// Initial revision.
 */