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
//    Copyright 2004 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : DSTCAMSAcctLvlTrxnBuilder.cpp
// ^AUTHOR : Monica Porteanu
// ^DATE   : June 2007
//
//******************************************************************************

//Forward declaration

class DSTCAMSAcctLvlTrxnBuilder
{
public:
   static SEVERITY buildTransactions( DSTCWorkSession &workSession, 
												  BFAbstractCBO* pObj, 
												  HostTransactionContainer* pTrCont,
												  BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE );

   static void buildTrxnKey (DString &strKey);

private:
   DSTCAMSAcctLvlTrxnBuilder()
   {};
   //no need for this class to be extended
   ~DSTCAMSAcctLvlTrxnBuilder()
   {};
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCAMSAcctLvlTrxnBuilder.hpp-arc  $
//
//   Rev 1.2   14 Sep 2007 10:59:40   popescu
//Incident 1003183 (GAP2360/02) - fixed AMS allocations
//
//   Rev 1.1   Jun 22 2007 14:20:26   porteanm
//PET 2360 FN02 - AMS - work in progress.
//
//   Rev 1.0   Jun 21 2007 13:16:54   porteanm
//Initial revision.
//

