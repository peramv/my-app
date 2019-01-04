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
//    Copyright 2000 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : Currency.hpp
// ^AUTHOR : Winnie Shiu
// ^DATE   : May 3,2000
//
// ^CLASS    : Currency
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

class IFASTCBO_LINKAGE Currency : public MFCanBFCbo, private boost::noncopyable
{
public:

   Currency( BFAbstractCBO &parent );
   virtual ~Currency();

   SEVERITY init( const BFDataGroupId& idDataGroup );
   SEVERITY init( const BFData &viewData );

   SEVERITY precisionOkay ( const DString dstrAmount, const BFDataGroupId& idDataGroup );
   bool isEuroCurrency ( const BFDataGroupId& idDataGroup );

private:

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/Currency.hpp-arc  $
// 
//    Rev 1.11   Nov 14 2004 14:30:02   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.10   Mar 21 2003 18:02:10   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.9   Oct 09 2002 23:54:10   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.8   Aug 29 2002 12:52:04   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.7   22 May 2002 18:21:28   PURDYECH
// BFData Implementation
// 
//    Rev 1.6   19 Mar 2002 13:15:30   PURDYECH
// Use #pragma once as include guard
// Remove compile time "including..." message
// 
//    Rev 1.5   09 May 2001 15:11:12   HSUCHIN
// Sync up with SSB
// 
//    Rev 1.4   03 May 2001 14:03:58   SMITHDAV
// Session management restructuring.
// 
//    Rev 1.3   Feb 05 2001 17:51:26   WINNIE
// no change
// 
//    Rev 1.2   Jan 18 2001 11:33:04   WINNIE
// new method to check amount precision
// 
//    Rev 1.1   Nov 02 2000 14:11:26   VASILEAD
// Added workSeesionId parameter for Mgmtco based CBOs
// 
//    Rev 1.0   May 05 2000 10:31:30   WINNIE
// Initial revision.
*/