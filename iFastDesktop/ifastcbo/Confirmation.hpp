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
// ^FILE   : Confirmation.hpp
// ^AUTHOR : Chin Hsu
// ^DATE   : Nov 9, 1999
//
// ^CLASS    : Confirmation
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE Confirmation : public MFCanBFCbo, private boost::noncopyable
{
public:
   //TODO: enter specific field enumerations
   Confirmation( BFAbstractCBO &parent );
   virtual ~Confirmation();
   SEVERITY init (const BFData &data);
   SEVERITY init ();
};
