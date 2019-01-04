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
// ^FILE   : DSTCAccountReviewTrxnBuilder.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : DSTCAccountReviewTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

class BFCBO;
class HostTransactionContainer;

class DSTCAccountReviewTrxnBuilder
{
public:
   static SEVERITY buildTransactions( DSTCWorkSession &workSession, 
                                      BFAbstractCBO* pBFCBO, 
                                      HostTransactionContainer* pTrCont,
                                      BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE );
private:
   DSTCAccountReviewTrxnBuilder()
   {};
   //no need for this class to be extended
   ~DSTCAccountReviewTrxnBuilder()
   {};
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCAccountReviewTrxnBuilder.hpp-arc  $
//
//   Rev 1.4   Nov 14 2004 14:31:10   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.3   Oct 09 2002 23:54:14   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.2   Aug 29 2002 12:55:18   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.1   22 May 2002 18:26:48   PURDYECH
//BFData Implementation
//
