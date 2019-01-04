#pragma once 

///******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2005 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : DSTCTransHistDilutionAllocListTrxnBuilder.hpp
// ^AUTHOR : Monica Porteanu
// ^DATE   : December, 2005
//
// ^CLASS    : DSTCTransHistDilutionAllocListTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

//Forward declaration

class DSTCTransHistDilutionAllocListTrxnBuilder
{
public:
   static SEVERITY buildTransactions( DSTCWorkSession &workSession, 
									  BFAbstractCBO* pObj, 
									  HostTransactionContainer* pTrCont,
									  BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE );

   static void buildTrxnKey (DString &strKey);

private:
   DSTCTransHistDilutionAllocListTrxnBuilder()
   {};
   //no need for this class to be extended
   ~DSTCTransHistDilutionAllocListTrxnBuilder()
   {};
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCTransHistDilutionAllocListTrxnBuilder.hpp-arc  $
//
//   Rev 1.0   Dec 13 2005 19:19:14   porteanm
//Initial revision.
//

