#pragma once

#include <dstring.hpp>

#undef BFUTIL_LINKAGE
#ifdef BFUTIL_DLL
   #define BFUTIL_LINKAGE CLASS_EXPORT
#else
   #define BFUTIL_LINKAGE CLASS_IMPORT
#endif

class BFDocument;

class BFUTIL_LINKAGE TxnStatElement
{
public:
   virtual ~TxnStatElement() = 0 {};
   virtual const DString& getName() const = 0;
   virtual DString getAsIDIString() const = 0;
   virtual void writeXML( BFDocument& out ) = 0;

protected:
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   //db3n5j11/d/scc/ifds/core/archives/bfutil/txnstatelement.hpp-arc  $
//
//   Rev 1.4   Oct 09 2002 17:41:34   PURDYECH
//New PVCS Database
//
//   Rev 1.3   Sep 19 2002 09:28:16   IVESPAUL
//Adapted the transaction stats to write results using XML ElementWriter.  Moved ElementAttribute and ElementWriter to BFUtil.
//
