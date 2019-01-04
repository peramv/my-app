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
// ^FILE   : DSTCAcctSettlementInstrTrxnBuilder.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : DSTCAcctSettlementInstrTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

//Forward declaration

class DSTCAcctSettlementInstrTrxnBuilder
{
public:
   static SEVERITY buildTransactions( DSTCWorkSession &workSession, 
                                      BFAbstractCBO* pObj, 
                                      HostTransactionContainer* pTrCont,
                                      BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE );

   static void buildTrxnKey( DString &strKey );

private:
   DSTCAcctSettlementInstrTrxnBuilder()   {};
   //no need for this class to be extended
   ~DSTCAcctSettlementInstrTrxnBuilder()
   {};
};

//***********************************************
//R E V I S I O N   C O N T R O L   E N T R I E S
//***********************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCAcctSettlementInstrTrxnBuilder.hpp-arc  $
//
//   Rev 1.1   Nov 14 2004 14:31:20   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.0   Oct 13 2004 13:24:46   VADEANUM
//Initial revision.
//
//   Rev 1.1   Nov 24 2003 18:07:46   HERNANDO
//Next revision.
