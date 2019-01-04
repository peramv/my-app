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
// ^FILE   : NomineeInterAddr.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 08/08/2000
//
// ^CLASS    : NomineeInterAddr
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

class IFASTCBO_LINKAGE NomineeInterAddr : public MFCanBFCbo, private boost::noncopyable
{
public:
   NomineeInterAddr( BFAbstractCBO &parent );
   virtual ~NomineeInterAddr();
   SEVERITY init (const BFData &InstData);
private:
};

