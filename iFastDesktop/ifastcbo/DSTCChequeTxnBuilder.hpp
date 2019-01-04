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
// ^FILE   : DSTCChequeTxnBuilder.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : DSTCChequeTxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

//Forward declaration

class DSTCChequeTxnBuilder
{
public:
   static SEVERITY buildTransactions( DSTCWorkSession &workSession, 
												  BFAbstractCBO* pObj, 
												  HostTransactionContainer* pTrCont,
												  BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE );

   static void buildTrxnKey (DString &strKey);

private:
   DSTCChequeTxnBuilder()
   {};
   //no need for this class to be extended
   ~DSTCChequeTxnBuilder()
   {};
};



/* $Log::
*/
