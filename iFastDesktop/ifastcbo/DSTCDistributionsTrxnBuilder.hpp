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
// ^FILE   : DSTCDistributionsTrxnBuilder.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : October 1999
//
// ^CLASS    : DSTCDistributionsTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

#include <boost\utility.hpp>

//Forward declaration
class BFAbstractCBO;
class AccountDistribution;
class HostTransactionContainer;
class MFAccount;

class DSTCDistributionsTrxnBuilder : private boost::noncopyable
{
public:
   static SEVERITY buildTransactions( DSTCWorkSession &workSession, 
                                      BFAbstractCBO* pBFBase, 
                                      HostTransactionContainer* pTrCont,
                                      BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE );

   static void buildTrxnKey( DString& strKey, AccountDistribution* accountDistribution, MFAccount* mfAccount );
private:

   static bool DistribUpdated ( AccountDistribution* acctDistrib, BF_OBJ_ACTIVITY ObjActivity );
   static int buildIndex;

};

