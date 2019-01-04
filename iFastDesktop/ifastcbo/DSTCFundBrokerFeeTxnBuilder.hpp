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
//    Copyright 2004 by International Financial.
//
//
//******************************************************************************
//
// ^FILE   : DSTCFundBrokerFeeTxnBuilder.hpp
// ^AUTHOR : 
// ^DATE   : August 11, 2004
//
// ^CLASS    : DSTCFundBrokerFeeTxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

#include <boost\utility.hpp>

class BFCBO;
class HostTransactionContainer;


class DSTCFundBrokerFeeTxnBuilder : private boost::noncopyable
{
public:
   static SEVERITY buildTransactions( DSTCWorkSession &workSession, 
                                      BFAbstractCBO* pBFBase, 
                                      HostTransactionContainer* pTrCont,
                                      BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE );


   static void buildTrxnKey( DString& strKey,BFCBO* pParent, BFCBO* pObj  );

private:
	static int buildIndex;

};
