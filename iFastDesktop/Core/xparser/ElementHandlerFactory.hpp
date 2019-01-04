#pragma once

// Import/Export resolution
#undef XPARSER_LINKAGE
#ifdef XPARSER_DLL
   #define XPARSER_LINKAGE CLASS_EXPORT
#else
   #define XPARSER_LINKAGE CLASS_IMPORT
#endif

#include <xercesc/sax/AttributeList.hpp>

namespace xp
{

   class ElementHandler;
   class CacheEnabledElementHandler;
   class RootHandler;
   class ProcessHandler;
   class CBOHandler;

   class XPARSER_LINKAGE ElementHandlerFactory
   {
   public:

      static void registerInstance(ElementHandlerFactory *instance);
      static void killInstance();
      static ElementHandlerFactory *getInstance();

      virtual const DString &getRootElementName() = 0;
      virtual RootHandler *createRootHandler() = 0;
      virtual RootHandler *createRootHandler( xercesc::AttributeList &attributes ) = 0;

      virtual ProcessHandler *createProcessHandler( ElementHandler *parentHandler,
                                                    const DString &elementName,
                                                    xercesc::AttributeList &attributes ) { return(NULL);}

      virtual CBOHandler *createCBOHandler( ElementHandler *parentHandler,
                                            const DString &elementName,
                                            xercesc::AttributeList &attributes ) { return(NULL);}

   private:
      static ElementHandlerFactory *s_instance;
   };

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/xparser/ElementHandlerFactory.hpp-arc  $
//
//   Rev 1.4   Mar 09 2004 11:00:50   PURDYECH
//PET910 - Xerces2 support.
//
//   Rev 1.3   Oct 09 2002 17:43:14   PURDYECH
//New PVCS Database
//
//   Rev 1.2   07 Jun 2002 17:09:00   SMITHDAV
//Add support for root level attributes to turn on statistics writing and verbose conditions.
//
//   Rev 1.1   14 May 2002 16:44:10   SMITHDAV
//put xparser code namespace xp.
//
//   Rev 1.0   02 Apr 2002 13:47:44   SMITHDAV
//Initial revision.
 * 
 */

