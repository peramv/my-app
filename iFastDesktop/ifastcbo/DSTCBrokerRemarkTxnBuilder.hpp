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
//    Copyright 2004, By International Financial Data Service
//
//
//******************************************************************************
//
// ^FILE   : DSTCBrokerRemarkTrxnBuilder.hpp
// ^AUTHOR : Yingbao Li
// ^DATE   : Sept. 15,2004
//
// ^CLASS    : DSTCBrokerRemarkTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

#include <boost\utility.hpp>

class BFAbstractCBO;
class BrokerRemark;
class BrokerRemarkList;
class HostTransactionContainer;

class DSTCBrokerRemarkTrxnBuilder : private boost::noncopyable
{
public:
   static SEVERITY buildTransactions( DSTCWorkSession &workSession, 
                                      BFAbstractCBO* pBFBase, 
                                      HostTransactionContainer* pTrCont,
                                      BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE );

	static void buildTrxnKey( DString& strKey, BrokerRemarkList* pList );
   static int buildIndex;
private:
};
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCBrokerRemarkTxnBuilder.hpp-arc  $
//
//   Rev 1.1   Nov 14 2004 14:31:50   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.0   Sep 24 2004 14:35:24   YINGBAOL
//Initial Revision
// 

* 
*/
