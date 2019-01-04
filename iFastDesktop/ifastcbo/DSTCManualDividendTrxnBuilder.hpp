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
//    Copyright 2003 by IFDS, Inc.
//
//
//******************************************************************************
//
// ^FILE   : DSTCManualDividendTrxnBuilder.hpp
// ^AUTHOR : 
// ^DATE   :
//
// ^CLASS    : DSTCManualDividendTrxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************

//Forward declarations
class BFCBO;
class MFAccount;
class HostTransactionContainer;
class ManualDividend;
class ManualDividendList;
struct FieldPair;

class DSTCManualDividendTrxnBuilder
{
public:

   static SEVERITY buildTransactions( DSTCWorkSession &workSession, 
                                      BFAbstractCBO* pBFCBO, 
                                      HostTransactionContainer* pTrxnContainer,
                                      BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE );

private:

   DSTCManualDividendTrxnBuilder()
   {};
   ~DSTCManualDividendTrxnBuilder()
   {};

   static void fillingData( BFCBO* pObj, BFData* data, FieldPair fields[], int numFields );
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCManualDividendTrxnBuilder.hpp-arc  $
//
//   Rev 1.1   Nov 14 2004 14:32:50   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.0   May 22 2003 17:04:58   HERNANDO
//Initial revision.
*/