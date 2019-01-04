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
//    Copyright 2002 by International Financial.
//
//
//******************************************************************************
//
// ^FILE   : DSTCAMSDeltaTrxnBuilder.hpp
// ^AUTHOR : Thanisorn S.
// ^DATE   : Jan. 18,2018
//
// ^CLASS    : DSTCAMSDeltaTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

#include <boost\utility.hpp>

//Forward declarations
class BFAbstractCBO;
class AmsMstrInfo;
class AMSDeltaAllocList;
class AMSDeltaAlloc;

class HostTransactionContainer;
class DSTCAMSDeltaTrxnBuilder : private boost::noncopyable
{
public:
   static SEVERITY buildTransactions(DSTCWorkSession &workSession,
                                     BFAbstractCBO* pCBO,
                                     HostTransactionContainer* pTrCont,
                                     BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE);

   static void buildTrxnKey(DString& strKey,AMSDeltaAllocList* pAMSDeltaAllocList);

private:

   static int buildIndex;

};