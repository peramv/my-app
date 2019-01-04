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
// Copyright 2011 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : FamilyCode.hpp
// ^AUTHOR : 
// ^DATE   : Oct, 2011
//
// ^CLASS    : FamilyCode
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

class IFASTCBO_LINKAGE FamilyCode : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   FamilyCode( BFAbstractCBO &parent );
   virtual ~FamilyCode(void);

// Initialize function
   SEVERITY init(const BFData& data);

protected:

private:
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/FamilyCode.hpp-arc  $
//
//   Rev 1.0   Nov 08 2011 11:46:24   dchatcha
//Initial revision.
//
