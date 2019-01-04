#pragma once

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
// ^FILE   : DSTCAcctSettlementRuleTrxnBuilder.hpp
// ^AUTHOR : Chatchai Daecha
// ^DATE   : Febuary 2008
//
// ^CLASS    : DSTCAcctSettlementRuleTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

class BFCBO;
class BFData;
class MFAccount;
class AcctLvlSttlmntRule;
class AcctLvlSttlmntRuleList;
class HostTransactionContainer;

class DSTCAcctSettlementRuleTrxnBuilder
{
public:
    static SEVERITY buildTransactions( DSTCWorkSession &workSession, 
                                       BFAbstractCBO* pObj, 
                                       HostTransactionContainer* pTrCont,
                                       BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE );

    static void buildTrxnKey( DString &strKey, MFAccount *pMFAccount,
                              AcctLvlSttlmntRuleList* pAcctLvlSttlmntRuleList );

private:
    DSTCAcctSettlementRuleTrxnBuilder( void ) {}
    virtual ~DSTCAcctSettlementRuleTrxnBuilder( void ) {}

    //static
    //bool isAcctSettlementRuleUpdated ( AcctLvlSttlmntRule* acctSttlmntRule, BF_OBJ_ACTIVITY ObjActivity );
};
