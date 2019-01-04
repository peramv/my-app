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
//    Copyright 2002 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : DSTCPensionInfoTrxnBuilder.hpp
// ^AUTHOR : 
// ^DATE   : May 30, 2002
// ^CLASS  : 
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

class DSTCPensionInfoTrxnBuilder
{
public:
   static SEVERITY buildTransactions( DSTCWorkSession &workSession, 
                                      BFAbstractCBO* pObj, 
                                      HostTransactionContainer* pTrCont,
                                      BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE );

   static void buildTrxnKey( DString &strKey, MFAccount *pMFAccount );

private:
   DSTCPensionInfoTrxnBuilder() {};

   ~DSTCPensionInfoTrxnBuilder() {};   
   static void fillingData( BFCBO* pObj, BFData* data, const BFFieldId fieldIds[], int numFields );
   static int buildIndex;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCPensionInfoTrxnBuilder.hpp-arc  $
//
//   Rev 1.3   Nov 14 2004 14:33:12   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.2   Oct 09 2002 23:54:22   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.1   Aug 29 2002 12:52:12   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.0   Jun 03 2002 09:55:12   HSUCHIN
//Initial revision.
*/