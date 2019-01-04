#pragma once
#include <bfutil\elementwriter.hpp>

// Import/Export resolution
#undef XPARSER_LINKAGE
#ifdef XPARSER_DLL
   #define XPARSER_LINKAGE CLASS_EXPORT
#else
   #define XPARSER_LINKAGE CLASS_IMPORT
#endif

namespace xp
{

   class XPARSER_LINKAGE ConditionWriter : public ElementWriter
   {
   public:
      ConditionWriter( const Condition& condition, BFDocument &out, bool verbose = false );
      ~ConditionWriter();

      static void setAlternateStyle( bool value = true ) { s_alternateStyle = value;}
      virtual void writeBody();

   protected:

      void writeCode();
      void writeShortCode();
      void writeUniqueCode();
      void writeComponent();
      void writeMessage();
      void writeCorrection();
      void writeFile();
      void writeMethod();
      void writeLine();

   private:

      const Condition &_condition;
      bool _verbose;

      static bool s_alternateStyle;
   };

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/xparser/ConditionWriter.hpp-arc  $
//
//   Rev 1.10   Mar 02 2004 10:56:14   SMITHDAV
//Change element writers to make them mor robust.
//
//   Rev 1.9   Oct 09 2002 17:43:12   PURDYECH
//New PVCS Database
//
//   Rev 1.8   Sep 19 2002 09:28:50   IVESPAUL
//Adapted the transaction stats to write results using XML ElementWriter.  Moved ElementAttribute and ElementWriter to BFUtil.
//
//   Rev 1.7   Sep 18 2002 14:12:00   IVESPAUL
//Changed alternate condition style.
//
//   Rev 1.6   Sep 11 2002 16:04:10   SMITHDAV
//An alternate style of condition has been added for the purposes  of FAST. We use a static settable to invoke the behaviour instead of a more complex project specific specialization technique because, we do not want to support many variations.
//
//   Rev 1.5   Sep 11 2002 14:19:02   SMITHDAV
//Temporary change to meet FAST condition needs.
//
//   Rev 1.4   Aug 02 2002 17:13:42   SMITHDAV
//Major EBF to deal with post-commit data outputs using abstract document model and random access document implementation.
//
//   Rev 1.3   07 Jun 2002 17:09:00   SMITHDAV
//Add support for root level attributes to turn on statistics writing and verbose conditions.
//
//   Rev 1.2   14 May 2002 16:44:08   SMITHDAV
//put xparser code namespace xp.
//
//   Rev 1.1   01 May 2002 17:16:50   SMITHDAV
//Simple writer changes. Add TxnStats. And Fix key handling for CBO add and replace ations.
//
//   Rev 1.0   02 Apr 2002 13:47:42   SMITHDAV
//Initial revision.
 *
 */

