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
// ^FILE   : DSTCAMSLmtTrxnBuilder.hpp
// ^AUTHOR : May Lin
// ^DATE   : Jul. 11,2003
//
// ^CLASS    : DSTCAMSLmtTrxnBuilder
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
class AmsLmtOverrideList;
class AmsLmtOverride;

class HostTransactionContainer;
class DSTCAMSLmtTrxnBuilder : private boost::noncopyable
{
public:
   static SEVERITY buildTransactions( DSTCWorkSession &workSession, 
                                      BFAbstractCBO* pCBO, 
                                      HostTransactionContainer* pTrCont,
                                      BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE );

   static void buildTrxnKey( DString& strKey, AmsLmtOverride* pAmsLmtOverride );
	static bool AMSUpdated ( BFAbstractCBO* pCBO, BF_OBJ_ACTIVITY ObjActivity, bool recursive = true);
private:

	static int buildIndex;

};

