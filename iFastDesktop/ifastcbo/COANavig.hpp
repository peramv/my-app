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
//    Copyright 1997 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : COANavig.hpp
// ^AUTHOR : Adrian Vasile
// ^DATE   : Feb 18, 1999
//
// ^CLASS    : COANavig
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE 
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT 
#else 
   #define IFASTCBO_LINKAGE CLASS_IMPORT 
#endif

class IFASTCBO_LINKAGE COANavig : public MFCanBFCbo, private boost::noncopyable
{
public:
   COANavig( BFAbstractCBO &parent );
   virtual ~COANavig();
   SEVERITY init( const DString& AccountNum,
                  const DString& dstrTrack = I_("N"),
                  const DString& dstrPageName = NULL_STRING);

   SEVERITY init();

private:
};

