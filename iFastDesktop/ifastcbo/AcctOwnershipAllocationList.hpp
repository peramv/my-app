#pragma once

//******************************************************************************
//
// COPYRIGHT:
//
// The computer systems, procedures, data bases and
// programs created and maintained by International Financial Data Services,
// are proprietary in nature and as such are confIdential.
// Any unauthorized use or disclosure of such information
// may result in civil liabilities.
//
// Copyright 2012 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : AcctOwnershipAllocationList.hpp
// ^AUTHOR : 
// ^DATE   : Jul, 2012
//
// ^CLASS    : AcctOwnershipAllocationList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE AcctOwnershipAllocationList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   AcctOwnershipAllocationList( BFAbstractCBO &parent );
   virtual ~AcctOwnershipAllocationList(void);

// Initialize function
   SEVERITY init( const DString &acctNum,
                  const BFDataGroupId& idDataGroup
);

   SEVERITY getMore();

protected:
   virtual SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );

private:
   BFData* requestData444;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctOwnershipAllocationList.hpp-arc  $
//
//   Rev 1.0   Jul 24 2012 19:00:32   dchatcha
//Initial revision.
//
