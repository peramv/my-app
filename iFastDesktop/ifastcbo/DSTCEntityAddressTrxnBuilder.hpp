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
// ^FILE   : DSTCEntityAddressTrxnBuilder.hpp
// ^AUTHOR : Ram Singaram
// ^DATE   : Novemeber 1999
//
// ^CLASS    : DSTCEntityAddressTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

class BFBase;
class Entity;
class EntityAddress;
class HostTransactionContainer;

class DSTCEntityAddressTrxnBuilder
{
public:
   static SEVERITY buildTransactions( DSTCWorkSession &workSession, 
                                      BFAbstractCBO* pBFBase, 
                                      HostTransactionContainer* pTrCont,
                                      BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE );

private:
   DSTCEntityAddressTrxnBuilder()
   {};
   //no need for this class to be extended
   ~DSTCEntityAddressTrxnBuilder()
   {};
};

