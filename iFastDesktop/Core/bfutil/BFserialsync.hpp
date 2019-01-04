#pragma once

// Import/Export resolution
#undef BFUTIL_LINKAGE
#ifdef BFUTIL_DLL
   #define BFUTIL_LINKAGE CLASS_EXPORT
#else
   #define BFUTIL_LINKAGE CLASS_IMPORT
#endif

class BFSerialSync
{
public:
   /**
    * releases the semaphore
    */
   virtual void leave() = 0;

   /**
    * waits for (grabs) the semaphore
    */
   virtual void enter() = 0;

   /**
    * grabs the semaphore if available otherwise returns false
    */
   virtual bool tryEnter() = 0;
};
