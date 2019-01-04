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
// ^FILE   : MgmtCoOptions2.hpp
// ^AUTHOR : 
// ^DATE   : 10/14/1999
//
// ^CLASS    : MgmtCoOptions2
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

class IFASTCBO_LINKAGE MgmtCoOptions2 : public MFCanBFCbo, private boost::noncopyable
{
public:

   MgmtCoOptions2( BFAbstractCBO &parent );
   virtual ~MgmtCoOptions2();

   SEVERITY init( const DString& dstrTrack = NULL_STRING , const DString& dstrPageName = NULL_STRING );
   SEVERITY init( const DString& dstrMgmgCo, const DString& dstrTrack = NULL_STRING , const DString& dstrPageName = NULL_STRING);
   SEVERITY initSynch( const DString& dstrMgmgCo, const DString& dstrTrack = NULL_STRING , const DString& dstrPageName = NULL_STRING);
};

