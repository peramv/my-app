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
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : DSTCAcctRoundingRuleTrxnBuilder.hpp
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

//Forward declaration

class DSTCAcctRoundingRuleTrxnBuilder
{
public:
   static SEVERITY buildTransactions( DSTCWorkSession &workSession, 
                                      BFAbstractCBO* pObj, 
                                      HostTransactionContainer* pTrCont,
                                      BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE );

   static void buildTrxnKey( DString &strKey, MFAccount *pMFAccount );

private:
   DSTCAcctRoundingRuleTrxnBuilder()   {};
   //no need for this class to be extended
   ~DSTCAcctRoundingRuleTrxnBuilder()
   {};
};

