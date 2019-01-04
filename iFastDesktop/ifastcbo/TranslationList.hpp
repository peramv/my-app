#pragma once
#define DISABLE_MACRO_REDEFINITION_WARNINGS 1
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
//    Copyright 1998 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : TranslationList.hpp
// ^AUTHOR : Mike Metzger
// ^DATE   : March 5, 1999
//
// ^CLASS    : TranslationList
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


class IFASTCBO_LINKAGE TranslationList : public MFCanBFCbo, private boost::noncopyable
{
public:
   TranslationList( BFAbstractCBO &parent );
   virtual ~TranslationList();

   SEVERITY init( const DString& dstrTrack= I_("N"), const DString& dstrPageName = NULL_STRING );

   void getStrKey( DString& strKey, const DString& strLangCode, const DString& strFundCode );
   virtual void getStrKey( DString &strKey, const BFData *data );
private:
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TranslationList.hpp-arc  $
//
//   Rev 1.8   Nov 14 2004 14:58:52   purdyech
//PET910 - .NET Conversion
//
//   Rev 1.7   Mar 21 2003 18:28:08   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.6   Oct 09 2002 23:55:14   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.5   Aug 29 2002 12:54:00   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.4   22 May 2002 18:18:10   PURDYECH
//BFData Implementation
//
//   Rev 1.3   19 Mar 2002 13:19:06   PURDYECH
//Use #pragma once as include guard
//Remove compile time "including..." message
//
//   Rev 1.2   03 May 2001 14:05:08   SMITHDAV
//Session management restructuring.
//
//   Rev 1.1   Jan 18 2001 16:13:10   YINGBAOL
//add etrack
//
//   Rev 1.0   Aug 03 2000 08:57:46   BUZILA
//Initial revision.
 * 
*/