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
// ^FILE   : DSTCAMSTrxnBuilder.hpp
// ^AUTHOR : Yingbao  Li
// ^DATE   : Nov. 13,2002
//
// ^CLASS    : DSTCAMSTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

#include <boost\utility.hpp>

//Forward declarations
class BFAbstractCBO;
class AMSMstrList;
class AmsMstrInfo;
class AmsFundAllocList;
class AmsFundAlloc;

class HostTransactionContainer;
class DSTCAMSTrxnBuilder : private boost::noncopyable
{
public:
   static SEVERITY buildTransactions( DSTCWorkSession &workSession, 
                                      BFAbstractCBO* pCBO, 
                                      HostTransactionContainer* pTrCont,
                                      BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE );

   static void buildTrxnKey( DString& strKey, AmsMstrInfo* amsmstrinfo );
	static bool AMSUpdated ( BFAbstractCBO* pCBO, BF_OBJ_ACTIVITY ObjActivity, bool recursive = false);
private:

	static int buildIndex;

};

