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
// ^FILE   : DSTCFundBrokerSettlementInstrTrxnBuilder.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCFundBrokerSettlementInstrTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"

#include "DSTCFundBrokerSettlementInstrTrxnBuilder.hpp"
#include "dstclisttrxnbuilder.hpp"
#include "FundMgmtSettlementInstrList.hpp"
#include "FundMgmtSettlementInstr.hpp"
#include "FundBroker.hpp"
#include "FundBrokerSettlementInstrList.hpp"
#include "FundBrokerSettlementInstr.hpp"

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
   const I_CHAR* CLASSNAME = I_( "DSTCFundBrokerSettlementInstrTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS = I_( "buildTransactions" );
}

namespace KEYTYPES
{
   extern CLASS_IMPORT I_CHAR * const ACCOUNTNUM;
}

//******************************************************************************
void DSTCFundBrokerSettlementInstrTrxnBuilder::buildTrxnKey( DString& dstrKey ) 
{
}

//******************************************************************************

SEVERITY DSTCFundBrokerSettlementInstrTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                          BFAbstractCBO* pObj,
                                                          HostTransactionContainer* pTrCont, 
                                                          BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS);
   SEVERITY severity = SEVERE_ERROR;


   FundBroker *pFundBroker = dynamic_cast<FundBroker*>(pObj);
   
   if( pFundBroker != NULL )
   {      
	  DString dstrFundBroker;
	  pFundBroker->getField( ifds::FundBrokerCode, dstrFundBroker, BF::HOST );

      std::vector<BFFieldId> fieldsFundMgmtSettlementInstrList;		      
      fieldsFundMgmtSettlementInstrList.push_back( ifds::FundBrokerCode );

      FundMgmtSettlementInstrList *pFundMgmtSettlementInstrList = NULL;
      severity = pFundBroker->getFndMgmtSettlementInstrList( pFundMgmtSettlementInstrList, BF::HOST, false );

      DSTCListTrxnBuilder <FundMgmtSettlementInstr*> fundMgmtSettlementInstrTrxnBuilder;     
	  DString dstrMgmtSettlementInstrListForFundBrokerKey = I_("MgmtSettlementInstrListForFundBroker") + dstrFundBroker;
      TRXNINFO fundMgmtSettlementInstrTrxnInfo( dstrMgmtSettlementInstrListForFundBrokerKey, 
                                                DSTC_REQUEST::FUND_MGMT_SETTLEMENT_INSTR_LIST_UPD,
                                                ifds::DSTC0274_REQ,
                                                ifds::DSTC0274_REQRepeat_Record,
                                                ifds::DSTC0274_VW,
                                                fieldsFundMgmtSettlementInstrList );

      fundMgmtSettlementInstrTrxnBuilder.buildTransactions ( workSession, 
                                                             pTrCont, 
                                                             pFundMgmtSettlementInstrList, 
                                                             fundMgmtSettlementInstrTrxnInfo,
                                                             objActivity );

   

      FundBrokerSettlementInstrList *pFundBrokerSettlementInstrList = NULL;
      severity = pFundBroker->getSettlementInstrList( pFundBrokerSettlementInstrList, BF::HOST, false );

      std::vector<BFFieldId> fieldsFundBrokerSettlementInstrList;

		fieldsFundBrokerSettlementInstrList.push_back(ifds::FundBrokerCode);
      DSTCListTrxnBuilder <FundBrokerSettlementInstr*> FundBrokerSettlementInstrTrxnBuilder;
	  DString dstrSettlementInstrListForFundBrokerKey = I_("SettlementInstrListForFundBroker") + dstrFundBroker;
      TRXNINFO FundBrokerSettlementInstrTrxnInfo( dstrSettlementInstrListForFundBrokerKey, 
                                            DSTC_REQUEST::SETTLEMENT_INSTRUCTIONS_LIST_UPDATE,
                                            ifds::DSTC0318_REQ,
                                            ifds::DSTC0318_REQRepeat_Record,
                                            ifds::DSTC0318_VW,
                                            fieldsFundBrokerSettlementInstrList );

      FundBrokerSettlementInstrTrxnBuilder.buildTransactions ( workSession, 
                                                               pTrCont, 
                                                               pFundBrokerSettlementInstrList, 
                                                               FundBrokerSettlementInstrTrxnInfo,
                                                               objActivity );

   }
   return(GETCURRENTHIGHESTSEVERITY());
}


//***********************************************
//R E V I S I O N   C O N T R O L   E N T R I E S
//***********************************************
// $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCFundBrokerSettlementInstrTrxnBuilder.cpp-arc  $
// 
//    Rev 1.3   Jan 28 2005 11:24:22   porteanm
// PTS 10038420 - Settlement Instructions for new Fund Brokers not saved.
// 
//    Rev 1.2   Dec 10 2004 17:22:42   vadeanum
// PET117_FN21: settlement instructions enhancement.
// 
//    Rev 1.1   Dec 10 2004 12:58:00   vadeanum
// PET1117 FN21 - Set flag to No (no view call) when invoking the lists.
// 
//    Rev 1.0   Nov 29 2004 18:49:20   aguilaam
// Initial revision.
// 

//
