#pragma once
#include <bfutil\elementattribute.hpp>

#include <xercesc/sax/AttributeList.hpp>

namespace xp
{

   class BooleanAttribute : public ElementAttribute
   {
   public:

      BooleanAttribute( const DString &tagName, xercesc::AttributeList &attributes, bool defaultValue );
      BooleanAttribute( const DString &tagName, bool boolValue, bool defaultValue );

      virtual const DString &getTagName() const;
      virtual const DString &getValue() const;
      virtual bool hasDefaultValue() const;

      virtual ElementAttribute *clone() const;

      operator bool() const
      {
         return(_boolValue);
      }

   private:
      const DString _tagName;
      const bool _defaultValue;
      bool _boolValue;

   };

}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/xparser/BooleanAttribute.hpp-arc  $
//
//   Rev 1.4   Mar 09 2004 10:59:18   PURDYECH
//PET910 - Xerces2 support.
//
//   Rev 1.3   Oct 09 2002 17:43:06   PURDYECH
//New PVCS Database
//
//   Rev 1.2   Sep 19 2002 09:28:48   IVESPAUL
//Adapted the transaction stats to write results using XML ElementWriter.  Moved ElementAttribute and ElementWriter to BFUtil.
//
//   Rev 1.1   14 May 2002 16:44:06   SMITHDAV
//put xparser code namespace xp.
//
//   Rev 1.0   02 Apr 2002 13:47:40   SMITHDAV
//Initial revision.
 *
 */

