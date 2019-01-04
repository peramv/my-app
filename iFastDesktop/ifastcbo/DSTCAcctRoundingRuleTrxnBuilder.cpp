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
//    Copyright 2008 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : DSTCAcctRoundingRuleTrxnBuilder.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : DSTCAcctRoundingRuleTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "dstclisttrxnbuilder.hpp"
#include "DSTCAcctRoundingRuleTrxnBuilder.hpp"
#include "AcctRoundingRule.hpp"
#include "AcctRoundingRuleList.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"

#include <ifastdataimpl\dse_dstc0481_req.hpp>
#include <ifastdataimpl\dse_dstc0481_reqrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0481_vw.hpp>


namespace DSTC_REQUEST
{
    extern CLASS_IMPORT const DSTCRequest ACCT_ROUNDING_RULE_UPDATE;
}

namespace
{
    const I_CHAR* CLASSNAME          = I_( "DSTCAcctRoundingRuleTrxnBuilder" );
    const I_CHAR* BUILDTRANSACTIONS  = I_( "buildTransactions" );
}

namespace CND
{
    extern const I_CHAR* IFASTCBO_CONDITION;
}

namespace ifds
{
    extern CLASS_IMPORT const BFNumericFieldId AccountNum;
}

namespace KEYTYPES
{
    extern CLASS_IMPORT I_CHAR * const ACCOUNTNUM;
}

//******************************************************************************
void DSTCAcctRoundingRuleTrxnBuilder::buildTrxnKey( DString& strKey, MFAccount *pMFAccount )
{    
}

//******************************************************************************
SEVERITY DSTCAcctRoundingRuleTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                             BFAbstractCBO* pObj, 
                                                             HostTransactionContainer* pTrCont, 
                                                             BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("buildTransactions"));
    MFAccount* pMFAccount = dynamic_cast<MFAccount*>(pObj);	
	  
    if( pMFAccount )
    {        
        DString dstrAccountNum, dstTrnKey, dstKeyTypes;
		AcctRoundingRuleList* pAcctRoundingRuleList = dynamic_cast <AcctRoundingRuleList*> (pMFAccount->getObject (I_( "AcctRoundingRuleList" ), BF::HOST)); 		
				
        if( pAcctRoundingRuleList )
        {   
			pMFAccount->getField(ifds::AccountNum, dstrAccountNum, BF::HOST, false);			
			pAcctRoundingRuleList->setField( ifds::AccountNum, dstrAccountNum, BF::HOST );

			addIDITagValue( dstTrnKey, I_("AcctRoundingRuleList"), dstrAccountNum.stripLeading('0').strip() );
			addIDITagValue( dstKeyTypes, KEYTYPES::ACCOUNTNUM, dstrAccountNum );
			
			std::vector<BFFieldId> fields;
			fields.push_back (ifds::AccountNum);			
					
			TRXNINFO acctRoundingRuleListTrxnInfo( dstTrnKey, 
												   DSTC_REQUEST::ACCT_ROUNDING_RULE_UPDATE,
												   ifds::DSTC0481_REQ,
												   ifds::DSTC0481_REQRepeat_Record,
												   ifds::DSTC0481_VW,
												   fields);

			DSTCListTrxnBuilder<AcctRoundingRule*> acctRoundingRuleTrxnBuilder;

			acctRoundingRuleTrxnBuilder.buildTransactions( workSession, 
														   pTrCont, 
														   pAcctRoundingRuleList, 
														   acctRoundingRuleListTrxnInfo, 
														   OBJ_ACTIVITY_NONE, 
														   dstKeyTypes);               
		}
    }

    return(GETCURRENTHIGHESTSEVERITY());
}
