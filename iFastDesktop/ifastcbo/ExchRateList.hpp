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
// ^FILE   : ExchRateList.hpp
// ^AUTHOR : Winnie Shiu
// ^DATE   : April 28, 2000
//
// ^CLASS    : ExchRateList
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


class IFASTCBO_LINKAGE ExchRateList : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   ExchRateList( BFAbstractCBO &parent );
   virtual ~ExchRateList();

   // Initialize function
   SEVERITY init();
   virtual void getStrKey( DString &strKey, const BFData *data );
   void getStrKey ( DString& strKey, 
                    const DString&  dstFromCurrency, 
                    const DString&  dstToCurrency, 
                    const DString&  dstEffectiveDate );


   double getExchRate ( const DString& dstrFromCurrency, 
                        const DString& dstrToCurrency, 
                        DString &AsofDate, 
                        const BFDataGroupId& idDataGroup,
                        const DString& dstrTrack= I_("N"),
                        const DString& dstrPageName = NULL_STRING,
                        const DString& exactDate = I_("Y"));

private:
};

///#endif


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ExchRateList.hpp-arc  $
// 
//    Rev 1.12   16 Jun 2008 16:20:30   popescu
// Incident# 1315311 - param the Exact Date input field for view 134 that reads the exchange rates
// 
//    Rev 1.11   Nov 14 2004 14:39:58   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.10   Mar 21 2003 18:08:50   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.9   Oct 09 2002 23:54:28   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.8   Aug 29 2002 12:52:24   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.7   22 May 2002 18:21:10   PURDYECH
// BFData Implementation
// 
//    Rev 1.6   19 Mar 2002 13:17:00   PURDYECH
// Use #pragma once as include guard
// Remove compile time "including..." message
// 
//    Rev 1.5   03 May 2001 14:04:08   SMITHDAV
// Session management restructuring.
// 
//    Rev 1.4   Feb 05 2001 17:50:30   WINNIE
// remove parameters from the init method
// 
//    Rev 1.3   Jan 25 2001 13:56:54   YINGBAOL
// add etrack
// 
//    Rev 1.2   Jan 18 2001 16:11:58   YINGBAOL
// add etrack
// 
//    Rev 1.1   May 05 2000 10:57:14   WINNIE
// Get Exchange Rate
// 
//    Rev 1.0   May 01 2000 11:21:52   WINNIE
// Initial revision.
*/