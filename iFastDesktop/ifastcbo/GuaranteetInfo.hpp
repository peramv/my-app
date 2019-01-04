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
// ^FILE   : GuaranteeInfo.hpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 09/03/2000
//
// ^CLASS    : GuaranteeInfo
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

//TODO: add headers that need to be included in the interface class

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE GuaranteeInfo : public MFCanBFCbo, private boost::noncopyable
{
public:
   GuaranteeInfo( BFAbstractCBO &parent );
   virtual ~GuaranteeInfo();
   SEVERITY init( const BFData& data );  
};
