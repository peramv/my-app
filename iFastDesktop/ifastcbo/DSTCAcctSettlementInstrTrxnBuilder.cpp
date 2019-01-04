//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : DSTCAcctSettlementInstrTrxnBuilder.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCAcctSettlementInstrTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"

#include "DSTCAcctSettlementInstrTrxnBuilder.hpp"
#include "dstclisttrxnbuilder.hpp"
#include "FundMgmtSettlementInstrList.hpp"
#include "FundMgmtSettlementInstr.hpp"
#include "MFAccount.hpp"
#include "AcctSettlementInstrList.hpp"
#include "AcctSettlementInstr.hpp"


#include <ifastdataimpl\dse_dstc0274_req.hpp>
#include <ifastdataimpl\dse_dstc0274_reqrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0274_vw.hpp>
#include <ifastdataimpl\dse_dstc0318_req.hpp>
#include <ifastdataimpl\dse_dstc0318_reqrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0318_vw.hpp>


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest FUND_MGMT_SETTLEMENT_INSTR_LIST_UPD;
   extern CLASS_IMPORT const DSTCRequest SETTLEMENT_INSTRUCTIONS_LIST_UPDATE;
}

namespace
{
   const I_CHAR* CLASSNAME = I_( "DSTCAcctSettlementInstrTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS = I_( "buildTransactions" );
}

namespace KEYTYPES
{
   extern CLASS_IMPORT I_CHAR * const ACCOUNTNUM;
}

//******************************************************************************
void DSTCAcctSettlementInstrTrxnBuilder::buildTrxnKey( DString& dstrKey ) 
{
}

//******************************************************************************

SEVERITY DSTCAcctSettlementInstrTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                          BFAbstractCBO* pObj,
                                                          HostTransactionContainer* pTrCont, 
                                                          BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS);
   SEVERITY severity = SEVERE_ERROR;
   MFAccount* pMFAccount = dynamic_cast<MFAccount*>(pObj);

   if( pMFAccount != NULL )
   {
      DString dstrAccountNum,dstKeyTypes;
      pMFAccount->getField( ifds::AccountNum, dstrAccountNum, BF::HOST );
      addIDITagValue( dstKeyTypes, KEYTYPES::ACCOUNTNUM, dstrAccountNum );

      std::vector<BFFieldId> fieldsFundMgmtSettlementInstrList;

		fieldsFundMgmtSettlementInstrList.push_back(ifds::AccountNum);
      fieldsFundMgmtSettlementInstrList.push_back(ifds::FundBrokerCode);
      FundMgmtSettlementInstrList *pFundMgmtSettlementInstrList = NULL;
      severity = pMFAccount->getFundMgmtSettlementInstrList( pFundMgmtSettlementInstrList, BF::HOST, false );

      DSTCListTrxnBuilder <FundMgmtSettlementInstr*> fundMgmtSettlementInstrTrxnBuilder;
      TRXNINFO fundMgmtSettlementInstrTrxnInfo( I_("FundMgmtSettlementInstrList"), 
                                                DSTC_REQUEST::FUND_MGMT_SETTLEMENT_INSTR_LIST_UPD,
                                                ifds::DSTC0274_REQ,
                                                ifds::DSTC0274_REQRepeat_Record,
                                                ifds::DSTC0274_VW,
                                                fieldsFundMgmtSettlementInstrList
                                              );

      fundMgmtSettlementInstrTrxnBuilder.buildTransactions ( workSession, 
                                                             pTrCont, 
                                                             pFundMgmtSettlementInstrList, 
                                                             fundMgmtSettlementInstrTrxnInfo, 
                                                             objActivity,
                                                             dstKeyTypes );

      AcctSettlementInstrList *pAcctSettlementInstrList = NULL;
      severity = pMFAccount->getSettlementInstrList( pAcctSettlementInstrList, BF::HOST, false );

      std::vector<BFFieldId> fieldsAcctSettlementInstrList;

		fieldsAcctSettlementInstrList.push_back(ifds::AccountNum);
      DSTCListTrxnBuilder <AcctSettlementInstr*> acctSettlementInstrTrxnBuilder;
      TRXNINFO acctSettlementInstrTrxnInfo( I_("AcctSettlementInstrList"), 
                                            DSTC_REQUEST::SETTLEMENT_INSTRUCTIONS_LIST_UPDATE,
                                            ifds::DSTC0318_REQ,
                                            ifds::DSTC0318_REQRepeat_Record,
                                            ifds::DSTC0318_VW,
                                            fieldsAcctSettlementInstrList
                                          );

      acctSettlementInstrTrxnBuilder.buildTransactions ( workSession, 
                                                         pTrCont, 
                                                         pAcctSettlementInstrList, 
                                                         acctSettlementInstrTrxnInfo, 
                                                         objActivity,
                                                         dstKeyTypes );

   }
   return(GETCURRENTHIGHESTSEVERITY());
}


//***********************************************
//R E V I S I O N   C O N T R O L   E N T R I E S
//***********************************************
// $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCAcctSettlementInstrTrxnBuilder.cpp-arc  $
// 
//    Rev 1.2   Dec 10 2004 19:21:46   vadeanum
// PET1117_FN21: settlement instructions.
// 
//    Rev 1.1   Dec 10 2004 16:14:56   aguilaam
// PET1117_FN21: sync-up settlement instructions from .NET
// 
//    Rev 1.0   Oct 13 2004 13:24:38   VADEANUM
// Initial revision.
// 

//
