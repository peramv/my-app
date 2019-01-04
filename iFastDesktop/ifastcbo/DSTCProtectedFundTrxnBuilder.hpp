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
// ^FILE   : DSTCProtectedFundTrxnBuilder.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : January 2003
//
// ^CLASS    : DSTCProtectedFundTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

//Forward declaration

class DSTCProtectedFundTrxnBuilder
{
public:
   static SEVERITY buildTransactions( DSTCWorkSession &workSession, 
                                      BFAbstractCBO* pObj, 
                                      HostTransactionContainer* pTrCont,
                                      BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE );

   static void buildTrxnKey( DString &strKey );

private:
   DSTCProtectedFundTrxnBuilder()   {};
   //no need for this class to be extended
   ~DSTCProtectedFundTrxnBuilder()
   {};
};

