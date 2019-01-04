#pragma once

#include <bfutil\bfkernel.hpp>

// Import/Export resolution
#undef BFUTIL_LINKAGE
#ifdef BFUTIL_DLL
   #define BFUTIL_LINKAGE CLASS_EXPORT
#else
   #define BFUTIL_LINKAGE CLASS_IMPORT
#endif

class BFUTIL_LINKAGE ConsoleInput : public BFKernel
{
public:
   virtual ~ConsoleInput();

   int getChar();
private:
   ConsoleInput();

   friend class Console;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfutil/ConsoleInput.hpp-arc  $
//
//   Rev 1.1   Oct 09 2002 17:41:26   PURDYECH
//New PVCS Database
//
//   Rev 1.0   11 Oct 2001 17:51:40   SMITHDAV
//Initial revision.
 */