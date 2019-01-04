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
// ^FILE   : HistoricalAccountList.hpp
// ^AUTHOR : Chin Hsu
// ^DATE   : October 14, 1999
//
// ^CLASS  : HistoricalAccountList
// ^PARENT : ListBase
//
// ^CLASS DESCRIPTION :
//    ements a map from the STL to hold fully instantiated BFBase objects
//    that are created from Data objects stored in the inherited ListBase class 
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

class IFASTCBO_LINKAGE HistoricalAccountList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   HistoricalAccountList( BFAbstractCBO &parent );
   virtual ~HistoricalAccountList( void );

   // Initialize function
   SEVERITY init( const DString&  strAccountNumber,
                  const DString& dstrTrack=I_("N"),
                  const DString& dstrPageName = NULL_STRING );

   SEVERITY search( bool bClearPreviousSearch );
   bool moreRecordsExist();
private:
   BFData _queryData;
};

///#endif // HISTORICALACCOUNTLIST_HPP