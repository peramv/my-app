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
// ^FILE   : TaxRatesList.hpp
// ^AUTHOR : Dan Petolescu
// ^DATE   : 12/13/99
//
// ^CLASS    : TaxRatesList
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

class IFASTCBO_LINKAGE TaxRatesList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   TaxRatesList( BFAbstractCBO &parent );
   virtual ~TaxRatesList();

   // Initialize function
   SEVERITY init( const DString& dstrTrack= I_("N"), const DString& dstrPageName = NULL_STRING );
   SEVERITY getMore();

   SEVERITY doCreateObject( const BFData& data, BFCBO*& pObjOut );
private:

   BFData _requestData;

};

///#endif

/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TaxRatesList.hpp-arc  $
 * 
 *    Rev 1.10   Nov 14 2004 14:57:08   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.9   Mar 21 2003 18:26:14   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.8   Oct 09 2002 23:55:06   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.7   Aug 29 2002 12:53:48   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.6   22 May 2002 18:19:16   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.5   19 Mar 2002 13:18:50   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.4   03 May 2001 14:05:00   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.3   Jan 18 2001 16:12:50   YINGBAOL
 * add etrack
 * 
 *    Rev 1.2   Dec 04 2000 15:08:26   OLTEANCR
 * new method: doCreateObject
 * 
 *    Rev 1.1   Mar 22 2000 09:02:38   PETOLESC
 * Added Tax Rates and RESP dialogs.
 * 
 *    Rev 1.0   Feb 15 2000 10:59:24   SMITHDAV
 * Initial revision.
// 
//    Rev 1.0   Dec 29 1999 17:25:48   PETOLESC
// Initial revision.
 * 
 *
 */