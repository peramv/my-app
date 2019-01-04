#pragma once
#include "xparsercommon.hpp"

#include <bfutil\elementattribute.hpp>

#include <xercesc/sax/AttributeList.hpp>

namespace xp
{

   class CBOActionAttribute : public ElementAttribute
   {
   public:

      CBOActionAttribute( xercesc::AttributeList &attributes );
      CBOActionAttribute( CBOAction action );

      virtual const DString &getTagName() const;
      virtual const DString &getValue() const;
      virtual bool hasDefaultValue() const;

      virtual ElementAttribute *clone() const;

      operator CBOAction() const
      {
         return(_action);
      }
   private:
      CBOAction _action;

   };

}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/xparser/CBOActionAttribute.hpp-arc  $
//
//   Rev 1.5   Jan 27 2005 15:48:12   smithdav
//Add support for collecting execution results, and return them to the server code.
//
//   Rev 1.4   Mar 09 2004 11:00:24   PURDYECH
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

