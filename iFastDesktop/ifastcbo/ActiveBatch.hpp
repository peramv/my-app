#pragma once

//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2007, By International Financial Data Service`
//
//
//******************************************************************************
//
// ^FILE   : ActiveBatch.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : September, 2007
//
// ^CLASS    : ActiveBatch
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class BFSession;

class IFASTCBO_LINKAGE ActiveBatch : public MFCanBFCbo
{
public:
   ActiveBatch (BFAbstractCBO &parent);
   virtual ~ActiveBatch();

	SEVERITY init (BFSession *session, const BFDataGroupId &idDataGroup);
   void getActiveBatchesList (DString &batchList);
protected:
private:
   void getActiveBatch ( DString &batchName, 
                         const DString &mgmCoId,
                         const BFDataGroupId &idDataGroup);
   DString _batchList;
};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/ActiveBatch.hpp-arc  $
//
//   Rev 1.0   25 Sep 2007 10:32:58   popescu
//Initial revision.
//
//
