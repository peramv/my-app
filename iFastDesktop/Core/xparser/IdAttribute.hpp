#pragma once

#include <bfutil\elementattribute.hpp>

#include <xercesc/sax/AttributeList.hpp>

namespace xp
{

   class IdAttribute : public ElementAttribute
   {
   public:

      IdAttribute( xercesc::AttributeList &attributes );
      IdAttribute( const DString &id );

      virtual const DString &getTagName() const;
      virtual const DString &getValue() const;
      virtual bool hasDefaultValue() const;

      virtual ElementAttribute *clone() const;

      operator const DString &() const
      {
         return(_id);
      }

   private:
      DString _id;

   };

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/xparser/IdAttribute.hpp-arc  $
//
//   Rev 1.5   Mar 09 2004 11:00:58   PURDYECH
//PET910 - Xerces2 support.
//
//   Rev 1.4   Mar 05 2004 13:28:30   SMITHDAV
//Fix stupid class initialization bugs.
//
//   Rev 1.3   Oct 09 2002 17:43:16   PURDYECH
//New PVCS Database
//
//   Rev 1.2   Sep 19 2002 09:28:54   IVESPAUL
//Adapted the transaction stats to write results using XML ElementWriter.  Moved ElementAttribute and ElementWriter to BFUtil.
//
//   Rev 1.1   14 May 2002 16:44:10   SMITHDAV
//put xparser code namespace xp.
//
//   Rev 1.0   02 Apr 2002 13:47:44   SMITHDAV
//Initial revision.
 * 
 */

