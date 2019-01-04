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
//    Copyright 1999 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : JEntityList.hpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 08/13/2000
//
// ^CLASS    : JEntityList
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

class IFASTCBO_LINKAGE JEntityList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   JEntityList( BFAbstractCBO &parent );
   virtual ~JEntityList( void );

   // Initialize function
   SEVERITY init( DString& dstrAccountNum, 
                  const DString& dstrTrack= I_("N"), 
                  const DString& dstrPageName = NULL_STRING   );

private:
};

///#endif

