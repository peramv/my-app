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
// ^FILE   : DSTCDistributorRepositoryTrxnBuilder.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : July, 2003
//
// ^CLASS    : DSTCDistributorRepositoryTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

//Forward declaration

class DSTCDistributorRepositoryTrxnBuilder
{
public:
   static void buildTrxnKey(DString &strKey);
   static SEVERITY buildTransactions(DSTCWorkSession &workSession, 
      BFAbstractCBO* pObj, HostTransactionContainer* pTrCont,
      BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE);
   static SEVERITY buildPaymentInstructionsTransactions(
      DSTCWorkSession &workSession, 
      DistributorRepository *pDistributorRepository, 
      HostTransactionContainer* pTrCont);
   static SEVERITY buildPayToEntityTransactions(
      DSTCWorkSession &workSession, 
      DistributorRepository *pDistributorRepository, 
      HostTransactionContainer* pTrCont);
private:
   DSTCDistributorRepositoryTrxnBuilder() 
   {};
   //no need for this class to be extended
   ~DSTCDistributorRepositoryTrxnBuilder() 
   {};
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCDistributorRepositoryTrxnBuilder.hpp-arc  $
//
//   Rev 1.1   Nov 14 2004 14:32:12   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.0   Jul 01 2003 18:17:14   popescu
//Initial revision.
 */