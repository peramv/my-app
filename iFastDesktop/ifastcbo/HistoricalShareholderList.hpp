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
// ^FILE   : HistoricalShareholderList.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS  : HistoricalShareholderList
// ^PARENT : 
//
// ^CLASS DESCRIPTION :
//    ements a map from the STL to hold fully instantiated BFBase objects
//    that are created from Data objects stored in the inherited ListBase class 
//******************************************************************************


#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE HistoricalShareholderList : public MFCanBFCbo, private boost::noncopyable
{
public:

   HistoricalShareholderList( BFAbstractCBO &parent );
   virtual ~HistoricalShareholderList( void );

   SEVERITY init( const DString& dstrShareholderNumber,
                  const DString& dstrTrack=I_("N"),
                  const DString& dstrPageName = NULL_STRING );

   SEVERITY search( bool bClearPreviousSearch );
   bool moreRecordsExist();

private:

   BFData m_queryData;
};

