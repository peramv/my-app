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
// ^FILE   : DSTCDistributorRepositoryTrxnBuilder.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : July, 2003
// ----------------------------------------------------------
//
// ^CLASS : DSTCDistributorRepositoryTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"

#include "dstcdistributorrepositorytrxnbuilder.hpp"
#include "dstcbankinstructionstrxnbuilder.hpp"
#include "distributorrepository.hpp"
#include "dstclisttrxnbuilder.hpp"
#include "paymentinstructions.hpp"
#include "paymentinstructionslist.hpp"
#include "paytoentity.hpp"
#include "paytoentitylist.hpp"
#include <ifastdataimpl\dse_dstc0257_req.hpp>
#include <ifastdataimpl\dse_dstc0257_vw.hpp>
#include <ifastdataimpl\dse_dstc0259_req.hpp>
#include <ifastdataimpl\dse_dstc0259_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest PAY_TO_ENTITY_LIST_UPDATE;
   extern CLASS_IMPORT const DSTCRequest PAYMENT_INSTRUCTIONS_UPDATE;
}

namespace
{
   const I_CHAR* CLASSNAME = I_( "DSTCDistributorRepositoryTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS = I_( "buildTransactions" );
}

extern BF_OBJ_TYPE OBJ_TYPE_PAY_TO_ENTITY_LIST;
extern BF_OBJ_TYPE OBJ_TYPE_PAYMENT_INSTRUCTIONS_LIST;

//******************************************************************************
void DSTCDistributorRepositoryTrxnBuilder::buildTrxnKey(DString &dstrKey) 
{
}

//******************************************************************************
SEVERITY DSTCDistributorRepositoryTrxnBuilder::buildTransactions(DSTCWorkSession &workSession,
   BFAbstractCBO* pObj, HostTransactionContainer* pTrCont, 
   BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS );

   DistributorRepository* pDistributorRepository = 
      dynamic_cast<DistributorRepository*>(pObj);

   buildPayToEntityTransactions(workSession, pDistributorRepository, 
      pTrCont);
   buildPaymentInstructionsTransactions(workSession, pDistributorRepository, 
      pTrCont);
   //call the builder for the banking instructions
   DSTCBankInstructionsTrxnBuilder::buildTransactions(workSession, pObj, pTrCont, objActivity);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DSTCDistributorRepositoryTrxnBuilder::buildPayToEntityTransactions(
   DSTCWorkSession &workSession, 
   DistributorRepository *pDistributorRepository, 
   HostTransactionContainer* pTrCont)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("buildPayToEntityTransactions"));

   BFObjIter iterRep(*pDistributorRepository, BF::HOST);

   iterRep.begin(OBJ_TYPE_PAY_TO_ENTITY_LIST, OBJ_ACTIVITY_NONE);
   while (!iterRep.end())
   {
      if(iterRep.hasTransactionUpdates())
      {
         PayToEntityList *pPayToEntityList = 
            dynamic_cast<PayToEntityList*>(iterRep.getObject());         
         DSTCListTrxnBuilder<PayToEntity*> payToEntityTrxnBuilder;
         TRXNINFO payToEntityTrxnInfo(I_("PayToEntityList"), 
            DSTC_REQUEST::PAY_TO_ENTITY_LIST_UPDATE,
            ifds::DSTC0259_REQ,
            ifds::DSTC0259_REQRepeat_Record,
            ifds::DSTC0259_VW);

         payToEntityTrxnBuilder.buildTransactions(workSession, pTrCont, 
            pPayToEntityList, payToEntityTrxnInfo);
      }
      ++iterRep;
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DSTCDistributorRepositoryTrxnBuilder::buildPaymentInstructionsTransactions(
   DSTCWorkSession &workSession, 
   DistributorRepository *pDistributorRepository, 
   HostTransactionContainer* pTrCont)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("buildPaymentInstructionsTransactions"));

   BFObjIter iterRep(*pDistributorRepository, BF::HOST);

   iterRep.begin(OBJ_TYPE_PAYMENT_INSTRUCTIONS_LIST, OBJ_ACTIVITY_NONE);
   while (!iterRep.end())
   {
      if(iterRep.hasTransactionUpdates())
      {
         PaymentInstructionsList *pPaymentInstructionsList = 
            dynamic_cast<PaymentInstructionsList*>(iterRep.getObject());
         DSTCListTrxnBuilder<PaymentInstructions*> paymentInstructionsTrxnBuilder;
         TRXNINFO paymentInstructionsTrxnInfo(I_("PaymentInstructionsList"), 
            DSTC_REQUEST::PAYMENT_INSTRUCTIONS_UPDATE,
            ifds::DSTC0257_REQ,
            ifds::DSTC0257_REQRepeat_Record,
            ifds::DSTC0257_VW);

         paymentInstructionsTrxnBuilder.buildTransactions(workSession, pTrCont, 
            pPaymentInstructionsList, paymentInstructionsTrxnInfo);
      }
      ++iterRep;
   }
   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCDistributorRepositoryTrxnBuilder.cpp-arc  $
// 
//    Rev 1.2   Nov 14 2004 14:32:12   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.1   Jul 08 2003 13:34:42   popescu
// Used the DSTCListTrxnBuilder.hpp for building the transactions
// 
//    Rev 1.0   Jul 01 2003 18:17:10   popescu
// Initial revision.
 */