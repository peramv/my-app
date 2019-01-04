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
// ^FILE   : DSTCChequeTxnBuilder.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCChequeTxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"

#include "DSTCChequeTxnBuilder.hpp"
#include "dstclisttrxnbuilder.hpp"
#include "Cheque.hpp"
#include "ChequeList.hpp"

#include <ifastdataimpl\dse_dstc0391_req.hpp>
#include <ifastdataimpl\dse_dstc0391_reqrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0391_vw.hpp>


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest CHEQUE_MAINTENANCE; 
}

namespace
{
   const I_CHAR* CLASSNAME = I_("DSTCFeeModelTxnBuilder");
   const I_CHAR* BUILDTRANSACTIONS = I_("buildTransactions");
}


extern BF_OBJ_TYPE OBJ_TYPE_CHEQUE_LIST;


//******************************************************************************
void DSTCChequeTxnBuilder::buildTrxnKey (DString& dstrKey) 
{
}

//******************************************************************************
SEVERITY DSTCChequeTxnBuilder::buildTransactions( DSTCWorkSession &workSession,
																					  BFAbstractCBO *pObj, 
																					  HostTransactionContainer *pTrCont, 
																					  BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS);

   ChequeList *pChequeList = NULL;
   pChequeList = dynamic_cast<ChequeList*>(pObj);
	
   if( NULL != pChequeList )
   {
 
			DSTCListTrxnBuilder<Cheque*> chequeModelbuilder;
               
			 TRXNINFO chequeTrxInfo( I_("Cheque"), 																		
									DSTC_REQUEST::CHEQUE_MAINTENANCE,
									ifds::DSTC0391_REQ,
									ifds::DSTC0391_REQRepeat_Record,
									ifds::DSTC0391_VW );
			 chequeModelbuilder.buildTransactions( workSession, 
			  									 pTrCont, 
												 pChequeList, 
  												 chequeTrxInfo ); 

			
      
   }	

   return GETCURRENTHIGHESTSEVERITY();
}


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCChequeTxnBuilder.cpp-arc  $
// 
//    Rev 1.0   Sep 08 2008 15:40:38   jankovii
// Initial revision.
// 
//    Rev 1.1   Nov 14 2004 14:32:24   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.0   Sep 07 2004 14:09:38   YINGBAOL
// Initial revision.
// 