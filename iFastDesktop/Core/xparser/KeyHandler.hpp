#pragma once

#include <xparser\elementhandler.hpp>
#include <xparser\fieldhandler.hpp>
#include <bfproc\bfcontainerid.hpp>

namespace xp
{

   class KeyHandler : public ElementHandler
   {
   public:
      KeyHandler( ElementHandler *parentHandler, const DString &elementName );

      bool executeLookup( AbstractProcess *process, const BFContainerId& idContainer, BFDocument &out );
      void executeSet( AbstractProcess *process, const BFContainerId& idContainer, BFDocument &out );
      void executeSet( AbstractProcess *process, const BFContainerId& idContainer );

      virtual void addHandler( FieldHandler *handler );

      virtual ElementAttributeList & getAttributes( ElementAttributeList &attributes ) const;

   private:
      FieldHandlerList _fieldList;
   };

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/xparser/KeyHandler.hpp-arc  $
//
//   Rev 1.7   Mar 02 2004 10:56:28   SMITHDAV
//Change element writers to make them mor robust.
//
//   Rev 1.6   Jan 06 2003 16:47:42   PURDYECH
//BFContainerId changeover
//
//   Rev 1.5   Oct 09 2002 17:43:16   PURDYECH
//New PVCS Database
//
//   Rev 1.4   Sep 19 2002 09:28:54   IVESPAUL
//Adapted the transaction stats to write results using XML ElementWriter.  Moved ElementAttribute and ElementWriter to BFUtil.
//
//   Rev 1.3   Aug 02 2002 17:13:44   SMITHDAV
//Major EBF to deal with post-commit data outputs using abstract document model and random access document implementation.
//
//   Rev 1.2   14 May 2002 16:44:12   SMITHDAV
//put xparser code namespace xp.
//
//   Rev 1.1   01 May 2002 17:16:52   SMITHDAV
//Simple writer changes. Add TxnStats. And Fix key handling for CBO add and replace ations.
//
//   Rev 1.0   02 Apr 2002 13:47:46   SMITHDAV
//Initial revision.
 *
 */

