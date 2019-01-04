#pragma once
#include <xparser\elementhandler.hpp>

// Import/Export resolution
#undef XPARSER_LINKAGE
#ifdef XPARSER_DLL
   #define XPARSER_LINKAGE CLASS_EXPORT
#else
   #define XPARSER_LINKAGE CLASS_IMPORT
#endif

namespace xp
{

   //******************************************************************************
   class XPARSER_LINKAGE CacheEnabledElementHandler : public ElementHandler
   {
   public:
      CacheEnabledElementHandler( ElementHandler *parentHandler, 
                                  const DString &elementName, 
                                  ClassAttribute::ElementClass elementClass );

      CacheEnabledElementHandler( const DString &elementName );

      void setToCache( const DString &name, const DString &text );
      const DString &getFromCache( const DString &name ) const;

   private:
      typedef std::map<DString, DString> Cache;
      typedef Cache::value_type CacheItem;
      Cache _cache;
      CacheEnabledElementHandler *_nextCachingHandler; // next higher level cache
   };

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/xparser/CacheEnabledElementHandler.hpp-arc  $
//
//   Rev 1.3   Oct 09 2002 17:43:08   PURDYECH
//New PVCS Database
//
//   Rev 1.2   Aug 14 2002 12:17:04   SMITHDAV
//Fix class attribute defaulting logic.
//
//   Rev 1.1   14 May 2002 16:44:06   SMITHDAV
//put xparser code namespace xp.
//
//   Rev 1.0   02 Apr 2002 13:47:42   SMITHDAV
//Initial revision.
 * 
 */

