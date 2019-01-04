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
//    Copyright 2009 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : DSTCInvestorAuthorizationTrxnBuilder.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : June 2009
//
// ^CLASS  : DSTCInvestorAuthorizationTrxnBuilder
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

class DSTCInvestorAuthorizationTrxnBuilder
{
public:
   static SEVERITY buildTransactions (DSTCWorkSession &workSession, 
                                      BFAbstractCBO* pObj, 
                                      HostTransactionContainer* pTrCont,
                                      BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE);

   static void buildTrxnKey( DString &strKey );

private:
   DSTCInvestorAuthorizationTrxnBuilder()   {};
   //no need for this class to be extended
   ~DSTCInvestorAuthorizationTrxnBuilder()
   {};
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCInvestorAuthorizationTrxnBuilder.hpp-arc  $
//
//   Rev 1.1   Jul 09 2009 15:49:16   dchatcha
//PET156681 FN14 H36 Investor Authorization.
//
//   Rev 1.0   29 Jun 2009 16:27:22   popescu
//Initial revision.
//
 */

