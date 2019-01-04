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
//    Copyright 2003 by International Financial.
//
//
//******************************************************************************
//
// ^FILE   : DSTCMktIndexValuesTrxnBuilder.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : 
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

#include <boost\utility.hpp>

//Forward declarations

class BFAbstractCBO;
class MktIndexValues;
class MktIndexValuesList;
class MktIndexFunds;
class MktIndexFundsList;

class HostTransactionContainer;
class DSTCMktIndexValuesTrxnBuilder : private boost::noncopyable
{
public:

   static SEVERITY buildTransactions( DSTCWorkSession &workSession, 
                                      BFAbstractCBO* pCBO, 
                                      HostTransactionContainer* pTrCont,
                                      BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE );

   static void buildTrxnKey( DString& strKey, MktIndexValues* MktIndexValues );
	static bool MktIndexUpdated( BFAbstractCBO* pCBO, BF_OBJ_ACTIVITY ObjActivity, bool recursive = true);

private:

	static int buildIndex;
};

