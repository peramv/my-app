#pragma once


//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Canada, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2001 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : RSPReceipts.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : RSPReceipts
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

class IFASTCBO_LINKAGE RSPReceipts : public MFCanBFCbo, private boost::noncopyable
{
public:
   /**
    * Constructor
    */
   RSPReceipts( BFAbstractCBO &parent );

   /**
    * Destructor
    */
   ~RSPReceipts();

   /**
    * Initializes the CBO based on the data object passed in.
    * @param   const Data& data - data passed in from the list class
    * @param   bool bBaseDelete - flag to determine who deletes the CBO
    */
   SEVERITY init( const BFData& data, bool bBaseDelete = false );

private:
};

///#endif

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RSPReceipts.hpp-arc  $
//
//   Rev 1.6   Nov 14 2004 14:53:36   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.5   Oct 09 2002 23:54:56   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.4   Aug 29 2002 12:53:32   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.3   22 May 2002 18:20:08   PURDYECH
//BFData Implementation
//
//   Rev 1.2   19 Mar 2002 13:18:22   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.1   20 Aug 2001 14:07:34   HSUCHIN
//added comments
//
//   Rev 1.0   01 Aug 2001 14:29:44   HSUCHIN
//Initial revision.
*/
