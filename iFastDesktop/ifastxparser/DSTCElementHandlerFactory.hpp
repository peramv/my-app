#pragma once
#include <xparser\elementhandlerfactory.hpp>

// Import/Export resolution
#undef IFASTXPARSER_LINKAGE
#ifdef IFASTXPARSER_DLL
   #define IFASTXPARSER_LINKAGE CLASS_EXPORT
#else
   #define IFASTXPARSER_LINKAGE CLASS_IMPORT
#endif

class IFASTXPARSER_LINKAGE DSTCElementHandlerFactory : public xp::ElementHandlerFactory
{
public:   
   virtual const DString &getRootElementName();
   virtual xp::RootHandler *createRootHandler();
   virtual xp::RootHandler *createRootHandler( xercesc::AttributeList &attributes );

   virtual xp::ProcessHandler *createProcessHandler( xp::ElementHandler *parentHandler,
                                                     const DString &elementName,
                                                     xercesc::AttributeList &attributes );

   virtual xp::CBOHandler *createCBOHandler( xp::ElementHandler *parentHandler,
                                             const DString &elementName,
                                             xercesc::AttributeList &attributes );

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastxparser/DSTCElementHandlerFactory.hpp-arc  $
//
//   Rev 1.4   May 10 2004 18:22:42   PURDYECH
//PET910 - Xerces2 compatibility fixes
//
//   Rev 1.3   Oct 09 2002 23:56:30   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.2   07 Jun 2002 17:08:54   SMITHDAV
//Add support for root level attributes to turn on statistics writing and verbose conditions.
//
//   Rev 1.1   14 May 2002 16:42:40   SMITHDAV
//put xparser code namespace xp.
//
//   Rev 1.0   02 Apr 2002 14:00:42   SMITHDAV
//Initial revision.
 * 
 */

