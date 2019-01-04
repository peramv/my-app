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
//    Copyright 2013, By International Financial Data Service
//
//
//******************************************************************************
//
// ^FILE   : AWDHistorySource.hpp
// ^AUTHOR : David Smith
// ^DATE   : Aug 22, 2013
//
// ^CLASS    : AWDHistorySource
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

namespace Json {
   class Value;
}

class IFASTCBO_LINKAGE AWDHistorySource : public MFCanBFCbo, private boost::noncopyable
{
public:
   AWDHistorySource( BFAbstractCBO &parent );
   ~AWDHistorySource(void);

   SEVERITY init ( const Json::Value& jsonData );
};
