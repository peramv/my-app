#pragma once 

//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confIdential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2010 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : DSTCAcctGuaranteeGuardOptTrxnBuilder.hpp
// ^AUTHOR : 
// ^DATE   : Aug 2010
//
// ^CLASS  : DSTCAcctGuaranteeGuardOptTrxnBuilder
// ^INHERITS FROM :
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

//Forward declaration
#include <boost\utility.hpp>

class BFAbstractCBO;
class HostTransactionContainer;

class DSTCAcctGuaranteeGuardOptTrxnBuilder
{
public:
   static SEVERITY buildTransactions (DSTCWorkSession &workSession, 
                                      BFAbstractCBO* pObj, 
                                      HostTransactionContainer* pTrCont,
                                      BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE);

   static void buildTrxnKey ( DString& dstrKey, BFAbstractCBO *pObj) ;

private:
   DSTCAcctGuaranteeGuardOptTrxnBuilder()   {};
   //no need for this class to be extended
   ~DSTCAcctGuaranteeGuardOptTrxnBuilder()
   {};
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCAcctGuaranteeGuardOptTrxnBuilder.hpp-arc  $
//
//   Rev 1.0   Sep 17 2010 04:15:00   kitticha
//Initial revision.
//

