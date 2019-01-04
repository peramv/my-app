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
// ^FILE   : DSTCFeeModelTxnBuilder.cpp
// ^AUTHOR : Yingbao  Li
// ^DATE   : August 2004
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCFeeModelTxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"

#include "DSTCFeeModelTxnBuilder.hpp"
#include "dstclisttrxnbuilder.hpp"
#include "FeeModel.hpp"
#include "FeeModelList.hpp"

#include <ifastdataimpl\dse_dstc0306_req.hpp>
#include <ifastdataimpl\dse_dstc0306_reqrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0306_vw.hpp>


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest FEE_MODEL_UPDATE; 
}

namespace
{
   const I_CHAR* CLASSNAME = I_("DSTCFeeModelTxnBuilder");
   const I_CHAR* BUILDTRANSACTIONS = I_("buildTransactions");
}

extern BF_OBJ_TYPE OBJ_TYPE_FEE_MODEL_LIST;

long unsigned int DSTCFeeModelTxnBuilder::s_curTrnNum = 0;

//******************************************************************************
void DSTCFeeModelTxnBuilder::buildTrxnKey (DString& dstrKey) 
{
   dstrKey = I_("FeeModel");

   DString numKey = asString(++DSTCFeeModelTxnBuilder::s_curTrnNum);
   numKey.padLeft(9, '0' );
   dstrKey += numKey;
}

//******************************************************************************
SEVERITY DSTCFeeModelTxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                    BFAbstractCBO *pObj, 
                                                    HostTransactionContainer *pTrCont, 
                                                    BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS);

   FeeModelList *pFeeModelList = NULL;
   pFeeModelList = dynamic_cast<FeeModelList*>(pObj);

   if( NULL != pFeeModelList )
   {
      DString trnxKey;

      DSTCFeeModelTxnBuilder::buildTrxnKey(trnxKey);

      DSTCListTrxnBuilder<FeeModel*> feeModelbuilder;

      TRXNINFO feeModelTrxInfo ( trnxKey, 
                                 DSTC_REQUEST::FEE_MODEL_UPDATE,
                                 ifds::DSTC0306_REQ,
                                 ifds::DSTC0306_REQRepeat_Record,
                                 ifds::DSTC0306_VW );
      feeModelbuilder.buildTransactions ( workSession, 
                                          pTrCont, 
                                          pFeeModelList, 
                                          feeModelTrxInfo ); 

   }	

   return GETCURRENTHIGHESTSEVERITY();
}


//*****************************************************************************
//              Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCFeeModelTxnBuilder.cpp-arc  $
// 
//    Rev 1.1   Nov 14 2004 14:32:24   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.0   Sep 07 2004 14:09:38   YINGBAOL
// Initial revision.
// 