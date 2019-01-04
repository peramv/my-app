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
// ^FILE   : AWDHistoryWorkList.hpp
// ^AUTHOR : David Smith
// ^DATE   : Aug 22, 2013
//
// ^CLASS    : AWDHistoryWorkList
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

class IFASTCBO_LINKAGE AWDHistoryWorkList : public MFCanBFCbo, private boost::noncopyable
{
public:
   AWDHistoryWorkList(BFAbstractCBO &parent);
   ~AWDHistoryWorkList(void);

   SEVERITY init ( const Json::Value& data );
   
   DString getImageAuth() {
      return _imageAuth;
   }

private:
   DString _imageAuth;
};
