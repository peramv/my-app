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
// ^FILE   : DSTCFeeModelTxnBuilder.hpp
// ^AUTHOR : yingbao Li
// ^DATE   : August 11, 2004
//
// ^CLASS    : DSTCFeeModelTxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

//Forward declaration

class DSTCFeeModelTxnBuilder
{
public:
   static SEVERITY buildTransactions( DSTCWorkSession &workSession, 
												  BFAbstractCBO* pObj, 
												  HostTransactionContainer* pTrCont,
												  BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE );

   static void buildTrxnKey (DString &strKey);

private:
   DSTCFeeModelTxnBuilder()
   {};
   //no need for this class to be extended
   ~DSTCFeeModelTxnBuilder()
   {};

   static long unsigned int s_curTrnNum;
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCFeeModelTxnBuilder.hpp-arc  $
//
//   Rev 1.1   Nov 14 2004 14:32:26   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.0   Sep 07 2004 14:09:52   YINGBAOL
//Initial revision.
//
//
