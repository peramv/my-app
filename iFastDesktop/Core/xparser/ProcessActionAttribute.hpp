#pragma once
#include "xparsercommon.hpp"

#include <bfutil\elementattribute.hpp>

#include <xercesc/sax/AttributeList.hpp>

namespace xp
{

   class ProcessActionAttribute : public ElementAttribute
   {
   public:

      ProcessActionAttribute( xercesc::AttributeList &attributes );
      ProcessActionAttribute( ProcessAction action );

      virtual const DString &getTagName() const;
      virtual const DString &getValue() const;
      virtual bool hasDefaultValue() const;

      virtual ElementAttribute *clone() const;

      operator ProcessAction() const
      {
         return(_action);
      }
   private:
      ProcessAction _action;

   };

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/xparser/ProcessActionAttribute.hpp-arc  $
//
//   Rev 1.5   Jan 27 2005 15:49:26   smithdav
//Add support for collecting execution results, and return them to the server code.
//
//   Rev 1.4   Mar 09 2004 11:01:10   PURDYECH
//PET910 - Xerces2 support.
//
//   Rev 1.3   Oct 09 2002 17:43:18   PURDYECH
//New PVCS Database
//
//   Rev 1.2   Sep 19 2002 09:28:56   IVESPAUL
//Adapted the transaction stats to write results using XML ElementWriter.  Moved ElementAttribute and ElementWriter to BFUtil.
//
//   Rev 1.1   14 May 2002 16:44:12   SMITHDAV
//put xparser code namespace xp.
//
//   Rev 1.0   02 Apr 2002 13:47:46   SMITHDAV
//Initial revision.
 * 
 */

