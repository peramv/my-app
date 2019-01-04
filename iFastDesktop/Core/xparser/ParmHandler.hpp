#pragma once

#include <xparser\elementhandler.hpp>
#include <xparser\booleanattribute.hpp>
#include <xparser\cacheattribute.hpp>

namespace xp
{
   //******************************************************************************
   class ParmHandlerList : public ElementHandlerList<class ParmHandler *>
   {
   public:
      void execute( GenericInterfaceContainer& gic, BFDocument &out );
      void executeAndCache( GenericInterfaceContainer& gic, BFDocument &out );
      void executeAndCache( BFDocument &out );
   };

   //******************************************************************************
   class ParmHandler : public ElementHandler
   {
   public:
      ParmHandler( ElementHandler *parentHandler, const DString &elementName, xercesc::AttributeList &attributes );

      void execute( GenericInterfaceContainer& gic, BFDocument &out );
      void executeAndCache( GenericInterfaceContainer& gic, BFDocument &out );
      void executeAndCache( BFDocument &out );

      virtual void appendText( const XMLCh * const chars, const unsigned int length );

      virtual const DString &getText() const;
      virtual ElementAttributeList & getAttributes( ElementAttributeList &attributes ) const;

   private:
      const CacheAttribute _cache;
      const BooleanAttribute _formatted;
      DString _text;
   };

}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/xparser/ParmHandler.hpp-arc  $
//
//   Rev 1.8   May 14 2004 16:15:38   SMITHDAV
//Made changes related to GIC interface changes, and made Process object const correct.
//
//   Rev 1.7   Mar 09 2004 11:01:04   PURDYECH
//PET910 - Xerces2 support.
//
//   Rev 1.6   Mar 02 2004 10:56:32   SMITHDAV
//Change element writers to make them mor robust.
//
//   Rev 1.5   Oct 09 2002 17:43:18   PURDYECH
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

