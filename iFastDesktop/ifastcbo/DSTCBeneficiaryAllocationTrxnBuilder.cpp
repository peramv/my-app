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
// ^FILE   :  DSTCBeneficiaryAllocationTrxnBuilder.cpp
// ^AUTHOR : 
// ^DATE   : May 2009
//
// ----------------------------------------------------------
//
// ^CLASS :  DSTCBeneficiaryAllocationTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  : Create the transaction and put it into the container
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "DSTCBeneficiaryAllocationTrxnBuilder.hpp"
#include "dstclisttrxnbuilder.hpp"
#include "MFAccount.hpp"
#include "mgmtco.hpp"
#include "RESPBeneficiaryAllocation.hpp"
#include "RESPBeneficiaryAllocationList.hpp"

#include <ifastcbo\resptransactionsdetails.hpp>
#include <ifastcbo\RESPTransactionsList.hpp>

#include <ifastdataimpl\dse_dstc0403_req.hpp>
#include <ifastdataimpl\dse_dstc0403_reqrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0403_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest RESP_BENEF_ALLOCATION_UPDATE;
}
namespace
{
   const I_CHAR* CLASSNAME = I_( "DSTCBeneficiaryAllocationTrxnBuilder" );
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
void  DSTCBeneficiaryAllocationTrxnBuilder::buildTrxnKey( DString& strKey, RESPTransactionsDetails *pRESPTransactionsDetails)
{
   assert( pRESPTransactionsDetails != NULL );
   DString transId;

   pRESPTransactionsDetails->getField( ifds::TransId, transId, BF::HOST, true );
   transId.strip();
}

//******************************************************************************
SEVERITY  DSTCBeneficiaryAllocationTrxnBuilder::buildTransactions (DSTCWorkSession &workSession,
                                                               BFAbstractCBO* pObj,
                                                               HostTransactionContainer* pTrCont, 
                                                               BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS );

	buildProcTransactions (workSession, pObj, pTrCont, objActivity);

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY  DSTCBeneficiaryAllocationTrxnBuilder::buildProcTransactions (DSTCWorkSession &workSession,
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
      RESPBeneficiaryAllocationList * pRESPBeneficiaryAllocationList = 
         dynamic_cast <RESPBeneficiaryAllocationList*> (pMFAccount->getObject (I_("RESPBeneficiaryAllocationList"), BF::HOST));
     	
		if (pRESPBeneficiaryAllocationList)
		{
			std::vector<BFFieldId> fields;
			
         fields.push_back (ifds::Amount);
			fields.push_back (ifds::EffectiveDate);
			fields.push_back (ifds::TransId);
			fields.push_back (ifds::AccountNum);
			fields.push_back (ifds::CallType);
			fields.push_back (ifds::TradeType);

			DSTCListTrxnBuilder <RESPBeneficiaryAllocation*> respBeneficiaryAllocationListTrxnBuilder;
	
			TRXNINFO respBeneficiaryAllocationInfo( 
                                    I_("RESPBeneficiaryAllocationList"), 
                                    DSTC_REQUEST::RESP_BENEF_ALLOCATION_UPDATE,
                                    ifds::DSTC0403_REQ,
                                    ifds::DSTC0403_REQRepeat_Record,
                                    ifds::DSTC0403_VW,
                                    fields);
		
			respBeneficiaryAllocationListTrxnBuilder.buildTransactions( 
                                                         workSession, 
                                                         pTrCont, 
                                                         pRESPBeneficiaryAllocationList, 
                                                         respBeneficiaryAllocationInfo,
                                                         OBJ_ACTIVITY_NONE);
		}
	}
	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log::   
*/