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
//    Copyright 2001 by DST Systems, Inc.
//
//******************************************************************************
// ^FILE   : HistoricalSystematicIndexList.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS  : HistoricalSystematicIndexList
// ^PARENT : 
//
// ^CLASS DESCRIPTION :
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

class IFASTCBO_LINKAGE HistoricalSystematicIndexList : public MFCanBFCbo, private boost::noncopyable
{
public:

   HistoricalSystematicIndexList( BFAbstractCBO &parent );
   virtual ~HistoricalSystematicIndexList( void );

   SEVERITY  init( const DString&  dstrTransactionNumber,
                   const DString& dstrTrack=I_("N"),
                   const DString& dstrPageName = NULL_STRING );

   SEVERITY  search( bool bClearPreviousSearch );
   bool    moreRecordsExist();

private:

   BFData    m_queryData;
};

///#endif // HISTORICALSYSTEMATICINDEXLIST_HPP