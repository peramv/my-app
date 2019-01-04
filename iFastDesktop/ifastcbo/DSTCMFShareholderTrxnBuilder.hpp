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
// ^FILE   : DSTCMFShareholderTrxnBuilder.hpp
// ^AUTHOR : Ram Singaram
// ^DATE   : October 1999
//
// ^CLASS    : DSTCMFShareholderTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

class Shareholder;
class HostTransactionContainer;

class DSTCMFShareholderTrxnBuilder
{
public:
   static SEVERITY buildTransactions( DSTCWorkSession &workSession, 
                                      BFAbstractCBO* pBFBase, 
                                      HostTransactionContainer* pTrCont,
                                      BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE );

   static void buildTrxnKey( DString& strKey, Shareholder* shareholder );
private:
   DSTCMFShareholderTrxnBuilder()
   {};
   //no need for this class to be extended
   ~DSTCMFShareholderTrxnBuilder()
   {};
};

