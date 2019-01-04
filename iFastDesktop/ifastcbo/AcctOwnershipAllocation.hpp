#pragma once

//******************************************************************************
//
// COPYRIGHT:
//
// The computer systems, procedures, data bases and
// programs created and maintained by International Financial Data Services, Inc.,
// are proprietary in nature and as such are confIdential.
// Any unauthorized use or disclosure of such information
// may result in civil liabilities.
//
// Copyright 2012 by International Financial Data Services, Inc.
//
//
//******************************************************************************
//
// ^FILE   : AcctOwnershipAllocation.hpp
// ^AUTHOR : 
// ^DATE   : Jul, 2012
//
// ^CLASS    : AcctOwnershipAllocation
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <boost\utility.hpp>
#include <ifastcbo\mfcancbo.hpp>


#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE AcctOwnershipAllocation : public MFCanBFCbo, private boost::noncopyable
{
public:

   AcctOwnershipAllocation( BFAbstractCBO &parent );
   virtual ~AcctOwnershipAllocation();

   SEVERITY init (const BFData& data );

protected:

private:

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// 
// $Log:   Y:/VCS/BF iFAST/ifastcbo/AcctOwnershipAllocation.hpp-arc  $
//
//   Rev 1.0   Jul 24 2012 18:59:52   dchatcha
//Initial revision.
//
