#pragma once

#include <xparser\elementhandler.hpp>
#include <xparser\booleanattribute.hpp>
#include <xparser\cacheattribute.hpp>
#include <bfproc\bfcontainerid.hpp>

class BFData;

namespace xp
{
   //******************************************************************************
   class FieldHandlerList : public ElementHandlerList<class FieldHandler *>
   {
   public:
      void execute( BFData &data, BFDocument &out );
      void executeSet( AbstractProcess *process, const BFContainerId& idContainer);
      void executeSet( AbstractProcess *process, const BFContainerId& idContainer, BFDocument &out );
      void executeGet( AbstractProcess *process, const BFContainerId& idContainer, BFDocument &out );
   };

   //******************************************************************************
   class FieldHandler : public ElementHandler
   {
   public:
      FieldHandler( ElementHandler *parentHandler,
                    const DString &elementName,
                    xercesc::AttributeList &attributes,
                    bool bFieldFormatting );

      void execute( BFData &data, BFDocument &out );
      void executeSet( AbstractProcess *process, const BFContainerId& idContainer);
      void executeSet( AbstractProcess *process, const BFContainerId& idContainer, BFDocument &out );
      void executeGet( AbstractProcess *process, const BFContainerId& idContainer, BFDocument &out );

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
/* $Log:   Y:/VCS/BF Core/xparser/FieldHandler.hpp-arc  $
//
//   Rev 1.10   Mar 09 2004 11:00:54   PURDYECH
//PET910 - Xerces2 support.
//
//   Rev 1.9   Mar 02 2004 10:56:24   SMITHDAV
//Change element writers to make them mor robust.
//
//   Rev 1.8   Jan 06 2003 16:47:36   PURDYECH
//BFContainerId changeover
//
//   Rev 1.7   Oct 09 2002 17:43:16   PURDYECH
//New PVCS Database
//
//   Rev 1.6   Sep 19 2002 09:28:54   IVESPAUL
//Adapted the transaction stats to write results using XML ElementWriter.  Moved ElementAttribute and ElementWriter to BFUtil.
//
//   Rev 1.5   Sep 03 2002 18:03:52   IVESPAUL
//Added "Package Level" attribute fieldFormatting, default is 'yes'.
//
//   Rev 1.4   Aug 02 2002 17:13:44   SMITHDAV
//Major EBF to deal with post-commit data outputs using abstract document model and random access document implementation.
//
//   Rev 1.3   07 Jun 2002 10:55:30   SMITHDAV
//Sync-up with Chris' changes.
//
//   Rev 1.2   14 May 2002 16:44:10   SMITHDAV
//put xparser code namespace xp.
//
//   Rev 1.1   01 May 2002 17:16:52   SMITHDAV
//Simple writer changes. Add TxnStats. And Fix key handling for CBO add and replace ations.
//
//   Rev 1.0   02 Apr 2002 13:47:44   SMITHDAV
//Initial revision.
 *
 */

