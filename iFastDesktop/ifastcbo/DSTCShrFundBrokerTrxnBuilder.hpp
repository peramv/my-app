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
// ^FILE   : DSTCShrFundBrokerTrxnBuilder.hpp
// ^AUTHOR : Monica Vadeanu
// ^DATE   : November, 2004
//
// ^CLASS    : DSTCShrFundBrokerTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

//Forward declaration

class DSTCShrFundBrokerTrxnBuilder
{
public:
   static SEVERITY buildTransactions( DSTCWorkSession &workSession, 
												  BFAbstractCBO* pObj, 
												  HostTransactionContainer* pTrCont,
												  BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE );

   static void buildTrxnKey (DString &strKey);

private:
   DSTCShrFundBrokerTrxnBuilder()
   {};
   //no need for this class to be extended
   ~DSTCShrFundBrokerTrxnBuilder()
   {};
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCShrFundBrokerTrxnBuilder.hpp-arc  $
//
//   Rev 1.1   Nov 14 2004 14:33:44   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.0   Nov 04 2004 17:24:52   VADEANUM
//Initial revision.
//


