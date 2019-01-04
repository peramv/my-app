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
// ^FILE   : DSTCAcctSplitCommTrxnBuilder.hpp
// ^AUTHOR : 
// ^DATE   : Aug 29, 2001
// ^CLASS  : DSTCAcctSplitComm
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

class BFCBO;
class BFData;
class MFAccount;
class HostTransactionContainer;

class DSTCAcctSplitCommTrxnBuilder
{
public:
   static SEVERITY buildTransactions( DSTCWorkSession &workSession, 
                                      BFAbstractCBO* pObj, 
                                      HostTransactionContainer* pTrCont,
                                      BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE );

   static void buildTrxnKey( DString &strKey, MFAccount *pMFAccount );

private:
   DSTCAcctSplitCommTrxnBuilder() {};

   ~DSTCAcctSplitCommTrxnBuilder() {};   
   static void fillingData( BFCBO* pObj, BFData* data, const BFFieldId fieldIds[], int numFields );
   static int buildIndex;
};

///#endif // ifndef DSTCACCTSPLITCOMMTRXNBUILDER_HPP

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCAcctSplitCommTrxnBuilder.hpp-arc  $ 
//
//   Rev 1.6   Nov 14 2004 14:31:24   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.5   Oct 09 2002 23:54:16   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.4   Aug 29 2002 12:52:10   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.3   22 May 2002 18:21:20   PURDYECH
//BFData Implementation
//
//   Rev 1.2   19 Mar 2002 13:15:34   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.1   Feb 25 2002 18:53:58   PURDYECH
//Phase 1 of BFData Rollout - Base Component Compatibility
//
//   Rev 1.0   30 Aug 2001 16:38:22   HSUCHIN
//Initial revision.
*/