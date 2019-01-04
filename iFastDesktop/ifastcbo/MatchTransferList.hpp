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
// ^FILE   : MatchTransferList.hpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 08/13/2001
//
// ^CLASS    : MatchTransferList
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

class IFASTCBO_LINKAGE MatchTransferList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   MatchTransferList( BFAbstractCBO &parent );
   virtual ~MatchTransferList( void );

   SEVERITY getMore();

   SEVERITY init( const DString& TransId,
                  const DString& dstrTrack=I_("N"),
                  const DString& dstrPageName = NULL_STRING );
   SEVERITY init2(const BFData& recData );

private:
};

///#endif

/* $Log:   Y:/VCS/BF iFAST/ifastcbo/MatchTransferList.hpp-arc  $
//
//   Rev 1.6   Nov 14 2004 14:49:34   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.5   Mar 21 2003 18:18:16   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.4   Oct 09 2002 23:54:44   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.3   Aug 29 2002 12:53:00   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.2   22 May 2002 18:20:22   PURDYECH
//BFData Implementation
//
//   Rev 1.1   19 Mar 2002 13:17:56   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.0   Aug 16 2001 13:32:22   ZHANGCEL
//Initial revision.
 * 
 *
 */