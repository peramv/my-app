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
// ^FILE   : DSTCOPCConfirmReprintTrxnBuilder.hpp
// ^AUTHOR : Monica Porteanu
// ^DATE   : May, 2005
//
// ^CLASS    : DSTCOPCConfirmReprintTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

//Forward declaration

class DSTCOPCConfirmReprintTrxnBuilder
{
public:
   static SEVERITY buildTransactions( DSTCWorkSession &workSession, 
									  BFAbstractCBO* pObj, 
									  HostTransactionContainer* pTrCont,
									  BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE );

   static void buildTrxnKey (DString &strKey);

private:
   DSTCOPCConfirmReprintTrxnBuilder()
   {};
   //no need for this class to be extended
   ~DSTCOPCConfirmReprintTrxnBuilder()
   {};
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCOPCConfirmReprintTrxnBuilder.hpp-arc  $
//
//   Rev 1.0   May 06 2005 14:15:36   porteanm
//Initial revision.
//
