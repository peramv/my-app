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
//    Copyright 2000 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : DSTCRRIFInfoTrxnBuilder.hpp
// ^AUTHOR : Dan Petolescu
// ^DATE   : May 2000
//
// ^CLASS    : DSTCRRIFInfoTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

#include <boost\utility.hpp>

//Forward declaration
class BFBase;
class RRIF_LIF_LRIF_Info;
class HostTransactionContainer;
class MFAccount;
class FundAllocList;
class DSTCRRIFInfoTrxnBuilder : private boost::noncopyable
{
public:
   static SEVERITY buildTransactions( DSTCWorkSession &workSession, 
                                      BFAbstractCBO* pBFBase, 
                                      HostTransactionContainer* pTrCont,
                                      BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE );

   static void buildTrxnKey( DString& strKey, 
                             RRIF_LIF_LRIF_Info* pRRIF_LIF_LRIF_Info, 
                             MFAccount* mfAccount, 
                             const BFDataGroupId& idDataGroup );

private:
   static bool RRIFUpdated ( BFAbstractCBO* pRRIF, BF_OBJ_ACTIVITY ObjActivity, bool recursive = true );
	static SEVERITY builAllocation(RRIF_LIF_LRIF_Info* pRRIFInfo, 
		FundAllocList* pAllocList,BFData* pDataReq, bool bRRIFUpdated, bool bDelToAlloc = false );
   static int buildIndex;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCRRIFInfoTrxnBuilder.hpp-arc  $
// 
//    Rev 1.13   Nov 14 2004 14:33:24   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.12   Jun 27 2003 10:14:18   YINGBAOL
// change code due to view's requirement.
// 
//    Rev 1.11   Jun 12 2003 16:50:42   YINGBAOL
// chage buildallocation
// 
//    Rev 1.10   Jun 09 2003 11:48:36   YINGBAOL
// RRIF enhancement
// 
//    Rev 1.9   Mar 21 2003 18:06:48   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.8   Oct 09 2002 23:54:22   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.7   Aug 29 2002 12:55:34   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.6   22 May 2002 18:27:58   PURDYECH
// BFData Implementation
// 
//    Rev 1.5   19 Mar 2002 13:21:58   PURDYECH
// Use #pragma once as an include guard
// Remove compile time "including..." message.
// 
//    Rev 1.4   Feb 25 2002 18:55:36   PURDYECH
// Phase 1 of BFData Rollout - Base Component Compatibility
// 
//    Rev 1.3   03 May 2001 14:06:20   SMITHDAV
// Session management restructuring.
// 
//    Rev 1.2   09 Mar 2001 18:03:54   BUZILAMI
// XchgData elimination fixes
// 
//    Rev 1.1   Jun 09 2000 18:01:28   PETOLESC
// Save work.
// 
//    Rev 1.0   May 04 2000 13:46:04   PETOLESC
// Initial revision.
 *
 *
 */