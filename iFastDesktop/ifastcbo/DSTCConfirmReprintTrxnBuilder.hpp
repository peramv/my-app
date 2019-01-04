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
// ^FILE   : DSTCConfirmReprintTrxnBuilder.hpp
// ^AUTHOR : Monica Porteanu
// ^DATE   : May, 2005
//
// ^CLASS    : DSTCConfirmReprintTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

//Forward declaration

class DSTCConfirmReprintTrxnBuilder
{
public:
   static SEVERITY buildTransactions( DSTCWorkSession &workSession, 
									  BFAbstractCBO* pObj, 
									  HostTransactionContainer* pTrCont,
									  BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE );
private:
   DSTCConfirmReprintTrxnBuilder() {};
   //no need for this class to be extended
   ~DSTCConfirmReprintTrxnBuilder() {};
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCConfirmReprintTrxnBuilder.hpp-arc  $
//
//   Rev 1.1   May 25 2005 15:02:14   porteanm
//PET OPC Confirm Reprint update support.
//
//   Rev 1.0   May 24 2005 12:33:28   porteanm
//Initial revision.
//

