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
// ^FILE   : Availabilty.hpp
// ^AUTHOR : Cristina Oltean
// ^DATE   : Jan, 2001
//
// ^CLASS    : Availabilty
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

class IFASTCBO_LINKAGE Availability : public MFCanBFCbo, private boost::noncopyable
{
public:

   Availability( BFAbstractCBO &parent );
   virtual ~Availability();
   void doInitWithDefaultValues( const BFDataGroupId& idDataGroup );

   SEVERITY init( const DString& dstrTrack, const DString& dstrActivity );

};
