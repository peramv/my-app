#pragma once
#include <bfutil\elementwriter.hpp>
#include <bfutil\bfhrtimer.hpp>

namespace xp
{

   class TxnStatWriter
   {
   public:
      TxnStatWriter( BFDocument &out, bool quiet );
      ~TxnStatWriter();

   private:
      BFDocument &out_;
      bool quiet_;
   };

   class ElementTimeWriter
   {
   public:
      ElementTimeWriter( BFDocument &out, bool quiet );
      ~ElementTimeWriter();

   private:
      BFHRTimer timer_;
      BFDocument &out_;
      bool quiet_;
   };

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/xparser/TxnStatWriter.hpp-arc  $
//
//   Rev 1.6   Oct 09 2002 17:43:24   PURDYECH
//New PVCS Database
//
//   Rev 1.5   Sep 19 2002 09:28:44   IVESPAUL
//Adapted the transaction stats to write results using XML ElementWriter.  Moved ElementAttribute and ElementWriter to BFUtil.
//
//   Rev 1.4   Aug 02 2002 17:13:42   SMITHDAV
//Major EBF to deal with post-commit data outputs using abstract document model and random access document implementation.
//
//   Rev 1.3   07 Jun 2002 17:09:00   SMITHDAV
//Add support for root level attributes to turn on statistics writing and verbose conditions.
//
//   Rev 1.2   07 Jun 2002 10:55:30   SMITHDAV
//Sync-up with Chris' changes.
//
//   Rev 1.1   14 May 2002 16:43:00   SMITHDAV
//put xparser code namespace xp.
//
//   Rev 1.0   01 May 2002 17:18:10   SMITHDAV
//Initial revision.
 *
 */

