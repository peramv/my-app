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
//    Copyright 2004 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : DSTCDailyTransactionsFeesTrxnBuilder.cpp
// ^AUTHOR : Monica Vadeanu
// ^DATE   : Jan 2004
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCDailyTransactionsFeesTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"

#include "dstcdailytransactionsfeestrxnbuilder.hpp"
#include "dstclisttrxnbuilder.hpp"
#include "dailytransactionsfeesrepository.hpp"
#include "dailytransactionsfeelist.hpp"
#include "dailytransactionsfee.hpp"

#include <ifastdataimpl\dse_dstc0285_req.hpp>
#include <ifastdataimpl\dse_dstc0285_reqrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0285_vw.hpp>


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest DAILY_TRANSACTIONS_FEE_LIST_UPDATE;
}

namespace
{
   const I_CHAR* CLASSNAME = I_("DSTCDailyTransactionsFeesTrxnBuilder");
   const I_CHAR* BUILDTRANSACTIONS = I_("buildTransactions");
}


extern BF_OBJ_TYPE OBJ_TYPE_DAILY_TRANSACTIONS_FEE_LIST;


//******************************************************************************
void DSTCDailyTransactionsFeesTrxnBuilder::buildTrxnKey (DString& dstrKey) 
{
}

//******************************************************************************
SEVERITY DSTCDailyTransactionsFeesTrxnBuilder::buildTransactions(
   DSTCWorkSession &workSession,
   BFAbstractCBO *pObj, 
   HostTransactionContainer *pTrCont, 
   BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS);

   DailyTransactionsFeesRepository *pDailyTransactionsFeesRepository = 
      dynamic_cast<DailyTransactionsFeesRepository*>(pObj);

   if (pDailyTransactionsFeesRepository)
   {
      //see whether we have updates
      BFObjIter iter (*pDailyTransactionsFeesRepository, BF::HOST);

      while (!iter.end())
      {
         const BF_OBJ_TYPE &objType = iter.getKey().getType();

         if (objType == OBJ_TYPE_DAILY_TRANSACTIONS_FEE_LIST)
         {
            DailyTransactionsFeeList *pDailyTransactionsFeeList = 
               dynamic_cast<DailyTransactionsFeeList*>(iter.getObject());

            if (pDailyTransactionsFeeList)
            {
               DSTCListTrxnBuilder<DailyTransactionsFee*> dailyTransactionsFeesTrxnBuilder;
               
               TRXNINFO dailyTransactionsFeeTrxnInfo( I_("DailyTransactionsFeeList"), 																		
																		DSTC_REQUEST::DAILY_TRANSACTIONS_FEE_LIST_UPDATE,
																		ifds::DSTC0285_REQ,
																		ifds::DSTC0285_REQRepeat_Record,
																		ifds::DSTC0285_VW );

               dailyTransactionsFeesTrxnBuilder.buildTransactions( workSession, 
																						 pTrCont, 
																						 pDailyTransactionsFeeList, 
																						 dailyTransactionsFeeTrxnInfo);               
            }
         }
			++iter;
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCDailyTransactionsFeesTrxnBuilder.cpp-arc  $
// 
//    Rev 1.2   Nov 14 2004 14:31:54   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.1   Feb 11 2004 11:24:44   VADEANUM
// PET859 FN23 - ADL - First working version.
// 
//    Rev 1.0   Jan 28 2004 14:08:12   popescu
// Initial revision.
// 
 */