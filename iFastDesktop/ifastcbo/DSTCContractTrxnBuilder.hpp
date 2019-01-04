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
// ^FILE   : DSTCContractTrxnBuilder.hpp
// ^AUTHOR : Celia Zhang
// ^DATE   : May 2000
//
// ^CLASS    : DSTCContractTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : Handle ContractInfo account
//
//
//******************************************************************************

//Forward declaration
class BFBase;
class ContractInfo;
class MFAccount;
class HostTransactionContainer;

class DSTCContractTrxnBuilder
{
public:
   static SEVERITY buildTransactions( DSTCWorkSession &workSession, 
                                      BFAbstractCBO* pBFBase, 
                                      HostTransactionContainer* pTrCont,
                                      BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE );

   //static void buildTrxnKey( DString& strKey, MFAccount* pMFAccount);
   static void buildTrxnKey( DString& strKey, MFAccount* pMFAccount);
private:
   DSTCContractTrxnBuilder()
   {};
   //no need for this class to be extended
   ~DSTCContractTrxnBuilder()
   {};
   bool _bMultiContract;
};

