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
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   :  DSTCRESPTransferTrxnBuilder.cpp
// ^AUTHOR : 
// ^DATE   : May 2009
//
// ----------------------------------------------------------
//
// ^CLASS :  DSTCRESPTransferTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  : Create the transaction and put it into the container
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "DSTCRESPTransferTrxnBuilder.hpp"
#include "dstclisttrxnbuilder.hpp"
#include "MFAccount.hpp"
#include "mgmtco.hpp"
#include "RESPTransfer.hpp"
#include "RESPTransferList.hpp"

#include <ifastcbo\resptransactionsdetails.hpp>
#include <ifastcbo\RESPTransactionsList.hpp>

#include <ifastdataimpl\dse_dstc0407_req.hpp>
#include <ifastdataimpl\dse_dstc0407_reqrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0407_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest RESP_TRANSFER_UPDATE;
}
namespace
{
   const I_CHAR* CLASSNAME = I_( "DSTCRESPTransferTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS = I_( "buildTransactions" );
   const I_CHAR* TRANS_NUM = I_( "TransNum" );
}

namespace ifds
{
   // Fields used
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFNumericFieldId EntityId;
}

namespace CND
{
   // Conditions used
   extern const I_CHAR* IFASTCBO_CONDITION;
}

//******************************************************************************
void  DSTCRESPTransferTrxnBuilder::buildTrxnKey( DString& strKey, RESPTransactionsDetails *pRESPTransactionsDetails)
{
   assert( pRESPTransactionsDetails != NULL );
   DString transId;

   pRESPTransactionsDetails->getField( ifds::TransId, transId, BF::HOST, true );
   transId.strip();
}

//******************************************************************************
SEVERITY  DSTCRESPTransferTrxnBuilder::buildTransactions (DSTCWorkSession &workSession,
                                                               BFAbstractCBO* pObj,
                                                               HostTransactionContainer* pTrCont, 
                                                               BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS );

   buildProcTransactions (workSession, pObj, pTrCont, objActivity);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY  DSTCRESPTransferTrxnBuilder::buildProcTransactions ( DSTCWorkSession &workSession,
                                                               BFAbstractCBO* pObj,
                                                               HostTransactionContainer* pTrCont, 
                                                               BF_OBJ_ACTIVITY objActivity)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS );

   SEVERITY severity = SEVERE_ERROR;
   RESPTransactionsList* pRESPTransactionsList (NULL);
   RESPTransactionsDetails* pRESPTransactionsDetails (NULL);
   MFAccount* pMFAccount = dynamic_cast<MFAccount*>(pObj);

   if (pMFAccount != NULL)
   {
      RESPTransferList * pRESPTransferList = 
         dynamic_cast <RESPTransferList*> (pMFAccount->getObject (I_("RESPTransferList"), BF::HOST));

      if (pRESPTransferList)
      {
         std::vector<BFFieldId> fields;

         fields.push_back (ifds::Amount);
         fields.push_back (ifds::EffectiveDate);
         fields.push_back (ifds::TransId);
         fields.push_back (ifds::AccountNum);
         fields.push_back (ifds::AccountTo);
         fields.push_back (ifds::CallType);
         fields.push_back (ifds::TradeType);
         fields.push_back (ifds::FromPlanNum);
         fields.push_back (ifds::ToPlanNum);
         fields.push_back (ifds::NEQ1);
         fields.push_back (ifds::NEQ2);
         fields.push_back (ifds::FromContractId);
         fields.push_back (ifds::ToContractId);
         fields.push_back (ifds::TransType);
         fields.push_back (ifds::DepositType);
         fields.push_back (ifds::RedCode);
         fields.push_back (ifds::RESPLetter);
         fields.push_back (ifds::RESPTransStat);
         fields.push_back (ifds::AcctLvlOverride);
         fields.push_back (ifds::InceptionDate);
         fields.push_back (ifds::TerminationDate);
         fields.push_back (ifds::EligibleTransfer);
         fields.push_back (ifds::HistNonTrustYear);
         fields.push_back (ifds::TotTransfINDC);

         DSTCListTrxnBuilder <RESPTransfer*> respTransferListTrxnBuilder;

         RESPTransferList * pRESPTransferUpdateList = NULL;
         DString strRESPTrxnKey = I_("RESPTransferList");

         // only non-trustee will send updated record
         if( pRESPTransferList->isListOfNonTrusteeTrfx(BF::HOST))
         {
            pRESPTransferList->getUpdatedRecord(pRESPTransferUpdateList,BF::HOST);
            strRESPTrxnKey  = I_("RESPTransferList_Updated");
         }
         else
         {
            pRESPTransferUpdateList = pRESPTransferList;
         }

         TRXNINFO respTransferInfo( strRESPTrxnKey, 
                                    DSTC_REQUEST::RESP_TRANSFER_UPDATE,
                                    ifds::DSTC0407_REQ,
                                    ifds::DSTC0407_REQRepeat_Record,
                                    ifds::DSTC0407_VW,
                                    fields);

         respTransferListTrxnBuilder.buildTransactions( workSession, 
                                                        pTrCont, 
                                                        pRESPTransferUpdateList, 
                                                        respTransferInfo,
                                                        OBJ_ACTIVITY_NONE,
                                                        NULL_STRING,
                                                        true);
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

///******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log::   Y:/VCS/BF iFAST/ifastcbo/DSTCRESPTransferTrxnBuilder.cpp-arc  $
// 
//    Rev 1.6   Jun 28 2011 10:39:48   panatcha
// P0184541_FN01_InvescoQESItrans
// 