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
// ^FILE   : DSTCAllocationTrxnBuilder.hpp
// ^AUTHOR : Winnie Shiu
// ^DATE   : January 2000
//
// ^CLASS    : DSTCBankInstructionsTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : Handle Shareholder/Account Default Allocation
//
//
//******************************************************************************

//Forward declaration
class BFCBO;
class Shareholder;
class ShrAllocTypeList;
class HostTransactionContainer;

class DSTCAllocationTrxnBuilder
{
public:
   static SEVERITY buildTransactions( DSTCWorkSession &workSession, 
                                      BFAbstractCBO* pBFCBO, 
                                      HostTransactionContainer* pTrCont,
                                      BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE );

   static void buildTrxnKey (DString& strKey, BFAbstractCBO *pBFCBO);

private:
   DSTCAllocationTrxnBuilder()   {};
   //no need for this class to be extended
   ~DSTCAllocationTrxnBuilder()   {};
   static void buildTransactions ( DSTCWorkSession &workSession,
                                   const DString &shrNum,
                                   ShrAllocTypeList *pShrLvlAllocList, 
                                   BFAbstractCBO *pObj, 
                                   HostTransactionContainer *pTrCont);

   static void buildAllocRepeat (int &count, BFData* req, BFCBO* pAlloc, BF_OBJ_ACTIVITY listObjActivity);

   //static bool AllocUpdated ( Allocation* allocation, BF_OBJ_ACTIVITY ObjActivity );
   //static void buildAllocRepeat ( int &count, Data* req, Allocation* allocation, BF_OBJ_ACTIVITY listObjActivity );
   static int buildIndex;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCAllocationTrxnBuilder.hpp-arc  $
 * 
 *    Rev 1.11   14 Sep 2007 10:59:32   popescu
 * Incident 1003183 (GAP2360/02) - fixed AMS allocations
 * 
 *    Rev 1.10   Nov 14 2004 14:31:30   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.9   Oct 09 2002 23:54:16   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.8   Aug 29 2002 12:55:22   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.7   22 May 2002 18:27:08   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.6   22 Apr 2002 10:14:22   KOVACSRO
 * Rel. 47 : new design for allocations.
 * 
 *    Rev 1.5   19 Mar 2002 13:21:54   PURDYECH
 * Use #pragma once as an include guard
 * Remove compile time "including..." message.
 * 
 *    Rev 1.4   Feb 25 2002 18:55:20   PURDYECH
 * Phase 1 of BFData Rollout - Base Component Compatibility
 * 
 *    Rev 1.3   03 May 2001 14:06:12   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.2   Feb 15 2000 18:57:36   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.1   Feb 15 2000 13:48:10   MCNABBGL
 * changed comment format
// * 
// *    Rev 1.0   Feb 15 2000 10:59:54   SMITHDAV
// * Initial revision.
// 
//    Rev 1.1   Jan 20 2000 18:03:42   WINNIE
// Change default allocation builder for new structure
// 
//    Rev 1.0   Jan 11 2000 16:43:10   WINNIE
// Initial revision.
*/

