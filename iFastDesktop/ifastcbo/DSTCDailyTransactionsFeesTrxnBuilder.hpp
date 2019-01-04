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
// ^FILE   : DSTCDailyTransactionsFeesTrxnBuilder.hpp
// ^AUTHOR : Monica Vadeanu
// ^DATE   : Jan, 2004
//
// ^CLASS    : DSTCDailyTransactionsFeesTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

//Forward declaration

class DSTCDailyTransactionsFeesTrxnBuilder
{
public:
   static SEVERITY buildTransactions (
      DSTCWorkSession &workSession, 
      BFAbstractCBO* pObj, 
      HostTransactionContainer* pTrCont,
      BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE );

   static void buildTrxnKey (DString &strKey);

private:
   DSTCDailyTransactionsFeesTrxnBuilder()
   {};
   //no need for this class to be extended
   ~DSTCDailyTransactionsFeesTrxnBuilder()
   {};
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCDailyTransactionsFeesTrxnBuilder.hpp-arc  $
//
//   Rev 1.1   Nov 14 2004 14:31:56   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.0   Jan 28 2004 14:08:16   popescu
//Initial revision.
// 
 */
