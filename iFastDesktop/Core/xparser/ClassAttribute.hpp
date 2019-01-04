#pragma once
#include <bfutil\elementattribute.hpp>

#include <xercesc/sax/AttributeList.hpp>

namespace xp
{

   class ClassAttribute : public ElementAttribute
   {
   public:

      enum ElementClass
      {
         ROOT = 0,
         BATCH,
         PARM,
         PROCESS,
         CBO,
         KEY,
         FIELD
      };

      ClassAttribute();
      ClassAttribute( xercesc::AttributeList &attributes, ElementClass parentClass );
      ClassAttribute( ElementClass elementClass, ElementClass parentClass );

      virtual const DString &getTagName() const;
      virtual const DString &getValue() const;
      virtual bool hasDefaultValue() const;

      virtual ElementAttribute *clone() const;

      operator ElementClass() const
      {
         return(_elementClass);
      }


   private:
      void init( xercesc::AttributeList &attributes );

      const ElementClass _defaultValue;
      ElementClass _elementClass;

   };

}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/xparser/ClassAttribute.hpp-arc  $
//
//   Rev 1.7   Mar 09 2004 11:00:34   PURDYECH
//PET910 - Xerces2 support.
//
//   Rev 1.6   Oct 09 2002 17:43:12   PURDYECH
//New PVCS Database
//
//   Rev 1.5   Sep 19 2002 09:28:50   IVESPAUL
//Adapted the transaction stats to write results using XML ElementWriter.  Moved ElementAttribute and ElementWriter to BFUtil.
//
//   Rev 1.4   Aug 14 2002 12:17:04   SMITHDAV
//Fix class attribute defaulting logic.
//
//   Rev 1.3   Jul 04 2002 15:22:42   SMITHDAV
//Class default handling and minor interface changes.
//
//   Rev 1.2   04 Jun 2002 10:41:46   SMITHDAV
//Add default handling for ClassAttribute.
//
//   Rev 1.1   14 May 2002 16:44:08   SMITHDAV
//put xparser code namespace xp.
//
//   Rev 1.0   02 Apr 2002 13:47:42   SMITHDAV
//Initial revision.
 *
 */

