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
// ^FILE   : HypotheticalRed.hpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 10/21/99
//
// ^CLASS    : HypotheticalRed
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

class IFASTCBO_LINKAGE HypotheticalRed : public MFCanBFCbo, private boost::noncopyable
{
public:
   // X-structors
   HypotheticalRed( BFAbstractCBO &parent );
   virtual ~HypotheticalRed();

   // Initialize function
   SEVERITY init( DString AccountNum,
                  DString FundCode,
                  DString ClassCode,
                  DString TradeDate,
                  DString GrossOrNet,
                  DString AmountType,
                  DString FullRedem,
                  DString RedCode,
                  DString Amount,
                  DString Baycom,
                  const DString& dstrTrack= I_("N"),
                  const DString& dstrPageName = NULL_STRING );



private:
};

///#endif


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/HypotheticalRed.hpp-arc  $
// 
//    Rev 1.10   Nov 14 2004 14:44:56   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.9   22 Jun 2004 15:33:12   SMITHDAV
// Expose hypothetical redemptions as an API interface.
// 
//    Rev 1.8   Mar 21 2003 18:14:40   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.7   Oct 09 2002 23:54:38   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.6   Aug 29 2002 12:52:42   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.5   22 May 2002 18:20:48   PURDYECH
// BFData Implementation
// 
//    Rev 1.4   19 Mar 2002 13:17:30   PURDYECH
// Use #pragma once as include guard
// Remove compile time "including..." message
// 
//    Rev 1.3   03 May 2001 14:04:20   SMITHDAV
// Session management restructuring.
// 
//    Rev 1.2   Jan 18 2001 16:12:10   YINGBAOL
// add etrack
// 
//    Rev 1.1   May 10 2000 10:07:54   YINGZ
// check in
*/