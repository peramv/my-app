#pragma once 

//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2005 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : DSTCBulkCancelTrxnBuilder.hpp
// ^AUTHOR : Monica Porteanu
// ^DATE   : November 2005
//
// ^CLASS    : DSTCBulkCancelTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

#include <boost\utility.hpp>

class BFAbstractCBO;
class HostTransactionContainer;

class BulkCancel;
class FundBrokerList;
class TransCancel;

class DSTCBulkCancelTrxnBuilder : private boost::noncopyable
{
public:
   static SEVERITY buildTransactions( DSTCWorkSession &workSession, 
                                      BFAbstractCBO* pBFBase, 
                                      HostTransactionContainer* pTrCont,
                                      BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE );

   static void buildTrxnKey( DString& strKey, BulkCancel* pBulkCancel);
   static int buildIndex;
private:
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCBulkCancelTrxnBuilder.hpp-arc  $
//
//   Rev 1.0   Nov 05 2005 15:08:14   porteanm
//Initial revision.
// 
*/

