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
// ^FILE   : DSTCMatSweepInstrTrxnBuilder.hpp
// ^AUTHOR : 
// ^DATE   : March 20, 2000
//
// ^CLASS    : DSTCMatSweepInstrTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

//Forward declarations

class DSTCMatSweepInstrTrxnBuilder
{
public:
   static SEVERITY buildTransactions( DSTCWorkSession &workSession, 
                                      BFAbstractCBO* pBFCBO, 
                                      HostTransactionContainer* pTrxnContainer,
                                      BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE);
private:
   DSTCMatSweepInstrTrxnBuilder()
   {};
   //no need for this class to be extended
   ~DSTCMatSweepInstrTrxnBuilder()
   {};

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCMatSweepInstrTrxnBuilder.hpp-arc  $
//
//   Rev 1.1   Dec 14 2011 16:55:02   popescu
//P0186477 FN03- GIA Maturity/Cash Sweep Instructions
 * 
 * P0183989 - Money Market Non Receipt
 * 
*/