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
// ^FILE   : DSTCAcctMailingTrxnBuilder.hpp
// ^AUTHOR : Winnie Shiu
// ^DATE   : Demember 1999
//
// ^CLASS    : DSTCAcctMailingTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

//Forward declaration
class BFBase;
class Shareholder;
class AccountMailingInfo;
class HostTransactionContainer;

class DSTCAcctMailingTrxnBuilder
{
public:
   static SEVERITY buildTransactions( DSTCWorkSession &workSession, 
                                      BFAbstractCBO* pObj, 
                                      HostTransactionContainer* pTrCont,
                                      BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE );

   static void buildTrxnKey( DString& strKey, Shareholder* pShareholder, AccountMailingInfo* acctmailing );

private:
   DSTCAcctMailingTrxnBuilder()
   {};
   //no need for this class to be extended
   ~DSTCAcctMailingTrxnBuilder()
   {};

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCAcctMailingTrxnBuilder.hpp-arc  $
 * 
 *    Rev 1.6   Nov 14 2004 14:31:18   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.5   Oct 09 2002 23:54:14   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.4   Aug 29 2002 12:55:20   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.3   19 Mar 2002 13:21:52   PURDYECH
 * Use #pragma once as an include guard
 * Remove compile time "including..." message.
 * 
 *    Rev 1.2   Feb 25 2002 18:55:16   PURDYECH
 * Phase 1 of BFData Rollout - Base Component Compatibility
 * 
 *    Rev 1.1   03 May 2001 14:06:10   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.0   Feb 15 2000 10:59:52   SMITHDAV
 * Initial revision.
// 
//    Rev 1.1   Jan 07 2000 18:20:16   POPESCUS
// fixes in trxns
// 
//    Rev 1.0   Dec 10 1999 16:31:14   WINNIE
// Initial revision.

  */