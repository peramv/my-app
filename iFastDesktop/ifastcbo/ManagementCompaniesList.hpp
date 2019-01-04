#pragma once

#include <ifastcbo\mfcancbo.hpp>
#include <boost\utility.hpp>

// Forward declaration of implementation class
class DSTCSecurity;

#undef IFASTCBO_LINKAGE
#ifdef IFASTCBO_DLL
   #define IFASTCBO_LINKAGE CLASS_EXPORT
#else
   #define IFASTCBO_LINKAGE CLASS_IMPORT
#endif

class IFASTCBO_LINKAGE ManagementCompaniesList : public MFCanBFCbo
{
public:
   ManagementCompaniesList( BFAbstractCBO &parent );
   virtual ~ManagementCompaniesList( void );
   //we have to pass here the security object because 
   //the work session id isn't available, yet
   //this is the only exception
   SEVERITY init();
private:
   BFData* _signonData;

};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ManagementCompaniesList.hpp-arc  $
 * 
 *    Rev 1.7   Nov 14 2004 14:49:16   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.6   Oct 09 2002 23:54:44   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.5   Aug 29 2002 12:52:58   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.4   22 May 2002 22:22:22   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.3   22 May 2002 18:20:32   PURDYECH
 * BFData Implementation
 */
