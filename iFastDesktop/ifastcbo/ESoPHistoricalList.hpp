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
//******************************************************************************
// ^FILE   : ESopHistoricalList.hpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : September 19, 2001
//
// ^CLASS  : ESopHistoricalList
// ^PARENT : MFCanCbo
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

class IFASTCBO_LINKAGE ESoPHistoricalList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   ESoPHistoricalList( BFAbstractCBO &parent );
   virtual ~ESoPHistoricalList( void );

   // Initialize function
   SEVERITY init( const DString& dstrTrack=I_("N"),
                  const DString& dstrPageName = NULL_STRING );

private:

};

///#endif // ESOPHISTORICALLIST_HPP