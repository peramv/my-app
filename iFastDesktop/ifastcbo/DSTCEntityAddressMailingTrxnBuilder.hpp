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
// ^FILE   : DSTCEntityAddressMailingTrxnBuilder.hpp
// ^AUTHOR : 
// ^DATE   : Sept 11, 2002
//
// ^CLASS    : DSTCEntityAddressMailingTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

class BFAbstractCBO;
class HostTransactionContainer;
class DSTCWorkSession;

class DSTCEntityAddressMailingTrxnBuilder
{
public:
   static SEVERITY buildTransactions( DSTCWorkSession &workSession, 
                                      BFAbstractCBO* pObj, 
                                      HostTransactionContainer* pTrCont,
                                      BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE );

   static void buildTrxnKey( DString& strKey, DString& dstrAccountNum );

private:
   DSTCEntityAddressMailingTrxnBuilder() {};   
   ~DSTCEntityAddressMailingTrxnBuilder() {};   
   static void fillingData( BFCBO* pObj, BFData* data, const BFFieldId fieldIds[], int numFields );
   static int buildIndex;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCEntityAddressMailingTrxnBuilder.hpp-arc  $
//
//   Rev 1.2   Nov 14 2004 14:32:14   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.1   Oct 09 2002 23:54:18   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.0   Sep 17 2002 12:14:26   HSUCHIN
//Initial revision.
//
//   Rev 1.0   Sep 17 2002 10:12:00   HSUCHIN
//Initial revision.
*/