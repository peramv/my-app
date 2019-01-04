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
// ^FILE   : DSTCAccountEntityTrxnBuilder.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : October 1999
//
// ^CLASS    : DSTCAccountEntityTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

class BFAbstractCBO;
class HostTransactionContainer;
class MFAccount;
class DSTCWorkSession;

class DSTCAccountEntityTrxnBuilder
{
public:
   static SEVERITY buildTransactions( DSTCWorkSession &workSession, 
                                      BFAbstractCBO* pObj, 
                                      HostTransactionContainer* pTrCont,
                                      BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE );

   static void buildTrxnKey( DString& strKey, MFAccount* mfAccount );
private:
   DSTCAccountEntityTrxnBuilder()
   {};
   //no need for this class to be extended
   ~DSTCAccountEntityTrxnBuilder()
   {};
   static int buildIndex;
};

