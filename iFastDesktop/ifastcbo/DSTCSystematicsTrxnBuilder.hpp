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
// ^FILE   : DSTCSystematicsTrxnBuilder.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : October 1999
//
// ^CLASS    : DSTCSystematicsTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

#include <boost\utility.hpp>

//Forward declarations
class BFAbstractCBO;
class MFAccount;
class Systematic;
class SysAllocation;
class HostTransactionContainer;
class SplitCommission;

class DSTCSystematicsTrxnBuilder : private boost::noncopyable
{
public:
   static SEVERITY buildTransactions( DSTCWorkSession &workSession, 
                                      BFAbstractCBO* pCBO, 
                                      HostTransactionContainer* pTrCont,
                                      BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE );

   static void buildTrxnKey( DString& strKey, Systematic* systematic, MFAccount* mfAccount);

   static bool OkToSend ( BFAbstractCBO* systemalloc, BF_OBJ_ACTIVITY &objActivity, bool IsUpdated );
   static bool OkToSendSplitComm ( int nEffectedItems, BF_OBJ_ACTIVITY &fundAllocActivity,
                                   const BF_OBJ_ACTIVITY &splitCommActivity, bool bRecordExistInDB,
                                   SplitCommission* pSplitCommission, DString& splitCommRunmode );
private:
   static bool IsATAllocUpdated ( BFAbstractCBO* allocation, BF_OBJ_ACTIVITY& ObjActivity, bool bSetAsDefault);

   DSTCSystematicsTrxnBuilder()
   {};
   //no need for this class to be extended
   ~DSTCSystematicsTrxnBuilder()
   {};

   static void fillingData( BFAbstractCBO* pObj, BFData* data, const BFFieldId fieldIds[], int numFields );
};

