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
//    Copyright 2000 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE      : HistoricalInfo.hpp
// ^AUTHOR    : Serban Popescu
// ^DATE      : January 2003
//
// ^CLASS     : HistoricalInfo
// ^SUBCLASS  :
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

//Forward declarations

class IFASTCBO_LINKAGE HistoricalInfo : public MFCanBFCbo, private boost::noncopyable
{
public:
   HistoricalInfo( BFAbstractCBO &parent );
   virtual ~HistoricalInfo();

   SEVERITY init(const BFData &viewData);
protected:
private:
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/HistoricalInfo.hpp-arc  $
//
//   Rev 1.3   Nov 14 2004 14:43:58   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.2   Jan 28 2003 13:16:10   popescu
//Historical Info feature implementation
//
//   Rev 1.1   Jan 26 2003 16:10:38   popescu
//List and CBO object for the Historical Info feature
//
//   Rev 1.0   Jan 26 2003 15:54:46   popescu
//Initial Revision
 */