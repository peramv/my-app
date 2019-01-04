#pragma once

#include <bfutil\bfexecutioncontext.hpp>
#include <bfutil\bfcritsec.hpp>

#undef BFBASE_LINKAGE
#ifdef BFBASE_DLL
   #define BFBASE_LINKAGE CLASS_EXPORT
#else
   #define BFBASE_LINKAGE CLASS_IMPORT
#endif

class BFBASE_LINKAGE ValidationControl : public BFExecutionContextImpl
{
public:
   static ValidationControl& get();

   void setValidateOnly();
   void unsetValidateOnly();

   bool isValidateOnly() const;

private:
   ValidationControl();
   virtual ~ValidationControl();

   int cProcesses_;     // current count of nested processes
                        // which are in validation-only mode

   mutable BFCritSec cs_;

};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfcbo/validationcontrol.hpp-arc  $
//
//   Rev 1.0   May 26 2003 14:22:08   PURDYECH
//Initial revision.
//
