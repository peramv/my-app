#pragma once

#include <bfutil\elementattribute.hpp>

namespace xp
{

   class SeverityAttribute : public ElementAttribute
   {
   public:
      SeverityAttribute( SEVERITY severity );

      virtual const DString &getTagName() const;
      virtual const DString &getValue() const;
      virtual bool hasDefaultValue() const;

      virtual ElementAttribute *clone() const;

      operator SEVERITY() const
      {
         return(_severity);
      }


   private:
      SEVERITY _severity;

   };

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/xparser/SeverityAttribute.hpp-arc  $
//
//   Rev 1.2   Oct 09 2002 17:43:22   PURDYECH
//New PVCS Database
//
//   Rev 1.1   14 May 2002 16:44:14   SMITHDAV
//put xparser code namespace xp.
//
//   Rev 1.0   02 Apr 2002 13:47:48   SMITHDAV
//Initial revision.
 * 
 */

