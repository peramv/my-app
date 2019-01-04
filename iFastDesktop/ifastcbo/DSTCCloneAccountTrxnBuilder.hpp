#pragma once 

//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by IFDS, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 by IFDS, Inc.
//
//
//******************************************************************************
//
// ^FILE   : DSTCCloneAccountTrxnBuilder.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : November, 2006
//
// ^CLASS    : DSTCCloneAccountTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

//Forward declaration
class CloneAccount;

class DSTCCloneAccountTrxnBuilder
{
public:
   static SEVERITY buildTransactions( DSTCWorkSession &workSession, 
												  BFAbstractCBO* pObj, 
												  HostTransactionContainer* pTrCont,
												  BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE);

   static void buildTrxnKey (DString &strKey, CloneAccount *pCloneAccount);

private:
   DSTCCloneAccountTrxnBuilder() {};
   //no need for this class to be extended
   ~DSTCCloneAccountTrxnBuilder() {};
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCCloneAccountTrxnBuilder.hpp-arc  $
//
//   Rev 1.0   Nov 08 2006 22:20:00   popescu
//Initial revision.
//
//
