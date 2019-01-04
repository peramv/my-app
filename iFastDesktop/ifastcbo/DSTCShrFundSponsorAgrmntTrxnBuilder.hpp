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
// ^FILE   : DSTCShrFundSponsorAgrmntTrxnBuilder.hpp
// ^AUTHOR : Monica Vadeanu
// ^DATE   : June, 2004
//
// ^CLASS    : DSTCShrFundSponsorAgrmntTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

//Forward declaration

class DSTCShrFundSponsorAgrmntTrxnBuilder
{
public:
   static SEVERITY buildTransactions( DSTCWorkSession &workSession, 
												  BFAbstractCBO* pObj, 
												  HostTransactionContainer* pTrCont,
												  BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE );

   static void buildTrxnKey (DString &strKey);

private:
   DSTCShrFundSponsorAgrmntTrxnBuilder()
   {};
   //no need for this class to be extended
   ~DSTCShrFundSponsorAgrmntTrxnBuilder()
   {};
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCShrFundSponsorAgrmntTrxnBuilder.hpp-arc  $
//
//   Rev 1.1   Nov 14 2004 14:33:46   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.0   Jul 26 2004 10:18:30   VADEANUM
//Initial revision.
//
