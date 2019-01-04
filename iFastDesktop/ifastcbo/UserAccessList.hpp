#pragma once

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE UserAccessList : public MFCanBFCbo, private boost::noncopyable
{
public:
   UserAccessList( BFAbstractCBO &parent );
   virtual ~UserAccessList();

   SEVERITY init( const DString& mgmtCoId, const DString& dstrTrack= I_("N"), const DString& dstrPageName = NULL_STRING );
   virtual void getStrKey( DString &strKey, const BFData *data = NULL );

};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/UserAccessList.hpp-arc  $
 * 
 *    Rev 1.10   Nov 14 2004 14:59:14   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.9   Mar 21 2003 18:28:20   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.8   Oct 09 2002 23:55:14   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.7   Aug 29 2002 12:54:00   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.6   22 May 2002 22:22:30   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.5   22 May 2002 18:18:10   PURDYECH
 * BFData Implementation
 */
