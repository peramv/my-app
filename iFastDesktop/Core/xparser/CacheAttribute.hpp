#pragma once
#include <bfutil\elementattribute.hpp>

#include <xercesc/sax/AttributeList.hpp>

namespace xp
{

   class CacheAttribute : public ElementAttribute
   {
   public:

      enum Cache
      {
         CACHE_NONE = 0,
         CACHE_GET,
         CACHE_PUT
      };

      CacheAttribute( xercesc::AttributeList &attributes );
      CacheAttribute( Cache cache );

      virtual const DString &getTagName() const;
      virtual const DString &getValue() const;
      virtual bool hasDefaultValue() const;

      virtual ElementAttribute *clone() const;

      operator Cache() const
      {
         return(_cache);
      }
   private:
      Cache _cache;

   };

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/xparser/CacheAttribute.hpp-arc  $
//
//   Rev 1.4   Mar 09 2004 10:59:22   PURDYECH
//PET910 - Xerces2 support.
//
//   Rev 1.3   Oct 09 2002 17:43:08   PURDYECH
//New PVCS Database
//
//   Rev 1.2   Sep 19 2002 09:28:48   IVESPAUL
//Adapted the transaction stats to write results using XML ElementWriter.  Moved ElementAttribute and ElementWriter to BFUtil.
//
//   Rev 1.1   14 May 2002 16:44:06   SMITHDAV
//put xparser code namespace xp.
//
//   Rev 1.0   02 Apr 2002 13:47:42   SMITHDAV
//Initial revision.
 *
 */

