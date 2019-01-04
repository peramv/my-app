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
// ^FILE   : RESPInfo.hpp
// ^AUTHOR : Dan Petolescu
// ^DATE   : January 12, 2000
//
// ^CLASS    : RESPInfo
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>
///#endif

class RESPInfoBeneficiary;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE RESPInfo : public MFCanBFCbo, private boost::noncopyable
{
public:
   RESPInfo( BFAbstractCBO &parent );
   virtual ~RESPInfo();

   SEVERITY init( DString& accountNum,
                  const DString& dstrTrack= I_("N"),
                  const DString& dstrPageName = NULL_STRING  );

   SEVERITY initNew( DString& accountNum );
   SEVERITY doCreateObject( const BFData& data, BFCBO *&pObjOut );
private:
   DString _accountNum;
   BFData _respInfoXchg;
};

///#endif

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RESPInfo.hpp-arc  $
 * 
 *    Rev 1.9   Nov 14 2004 14:52:20   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.8   Mar 21 2003 18:22:04   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.7   Oct 09 2002 23:54:52   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.6   Aug 29 2002 12:53:18   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.5   22 May 2002 18:20:12   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.4   19 Mar 2002 13:18:10   PURDYECH
 * Use #pragma once as include guard
 * Remove compile time "including..." message
 * 
 *    Rev 1.3   03 May 2001 14:04:44   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.2   Jan 18 2001 16:12:24   YINGBAOL
 * add etrack
 * 
 *    Rev 1.1   Mar 22 2000 09:02:30   PETOLESC
 * Added Tax Rates and RESP dialogs.
// 
//    Rev 1.1   Feb 16 2000 10:18:00   PETOLESC
// This is the file formerly called InfoGlobalList.
 *
 * 
 *
 */